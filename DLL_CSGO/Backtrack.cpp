#include "Includes.hxx"
#include "Main.hxx"

// Where everything has started on backtracking: https://github.com/alliedmodders/hl2sdk/blob/d5480b033f080b2363310392fe905d27e6342966/game/server/player_lagcompensation.cpp#L261
// Adjust the tick_count that we send to server, perfectly. (it makes allows us even to be able to fix some parts of the lag compensation).
#define LC_ALIVE			(1<<0)

CBacktrack *Backtrack = new CBacktrack();

int MAX_HISTORY_BACKTRACK = -1;
int OLD_MAX_HISTORY_BACKTRACK = -1;
constexpr float LAG_COMPENSATION_TELEPORTED_DISTANCE_SQR = ( 64.0f * 64.0f );

CBacktrack::CBacktrack()
{
	for ( int players = 0; players <= MAX_PLAYERS; players++ )
	{
		PlayerRecord[ players ] = nullptr;
	}
}

CBacktrack::~CBacktrack()
{
	for ( int players = 0; players <= MAX_PLAYERS; players++ )
	{
		if ( PlayerRecord[ players ] != nullptr )
			delete PlayerRecord[ players ];

		PlayerRecord[ players ] = nullptr;
	}
}

void CBacktrack::PushBack()
{
	MAX_HISTORY_BACKTRACK = TIME_TO_TICKS( 1.0f ); //One sec max

	if ( MAX_HISTORY_BACKTRACK != OLD_MAX_HISTORY_BACKTRACK )
	{
		for ( int players = 0; players <= MAX_PLAYERS; players++ )
		{
			if ( PlayerRecord[ players ] != nullptr )
			{
				delete PlayerRecord[ players ];
				PlayerRecord[ players ] = nullptr;
			}

			PlayerRecord[ players ] = new CPlayerBacktrack( MAX_HISTORY_BACKTRACK );
		}

		EngineClient->Con_NPrintf( 0 , AutoConvertC( TEXT( "Re-calculated tickrate for backtrack history" ) ) );
	}

	for ( HEX i = Globals->maxClients; i != 0; i-- )
	{
		C_BasePlayer *pPlayer = ( C_BasePlayer* ) ClientEntityList->GetClientEntity( i );

		if ( pPlayer != nullptr )
		{
			if ( pPlayer->IsLocalPlayer() )
				continue;

			int iPlayerIndex = pPlayer->entindex();

			if ( ( _OffsetManualthis( CBasePlayer::DT_BasePlayer::iObserverMode() , int , pPlayer ) == OBS_MODE_NONE )
				 && !pPlayer->IsDormant()
				 && ( ( _OffsetManualthis( CBaseEntity::DT_BaseEntity::iTeamNum() , int , pPlayer )
				 != _OffsetManualthis( CBaseEntity::DT_BaseEntity::iTeamNum() , int , GetLocalPlayer() ) ) || !Cvars[ hack_backtrack_team_check ]->GetBool() ) )
			{
				float flSimulationTime = _OffsetManualthis( CBaseEntity::DT_BaseEntity::flSimulationTime() , float , pPlayer );

					// As lag compensation is doing: https://github.com/alliedmodders/hl2sdk/blob/d5480b033f080b2363310392fe905d27e6342966/game/server/player_lagcompensation.cpp#L388
					// If the simulation time was the same, it means that the player choked. If the player choked, we need to ignore that data,
					// because lag compensation won't take into account this position.

				if ( flSimulationTime > PlayerRecord[ iPlayerIndex ]->flOldSimulationTime )
				{
					PushBackLag( pPlayer , i );
				}

				PlayerRecord[ iPlayerIndex ]->flOldSimulationTime = flSimulationTime;
			}

			Backtrack->UpdateMaxHistory( iPlayerIndex );

		}
	}

	OLD_MAX_HISTORY_BACKTRACK = MAX_HISTORY_BACKTRACK;
}

void CBacktrack::BackUpRecordToPlayer( C_BasePlayer *pPlayer , LagRecord *LRecord , int index )
{
	//pPlayer->CopyBoneCache( LRecord->m_RenderMatrix , sizeof( LRecord->m_RenderMatrix ) / sizeof( Matrix3x4 ) );
	pPlayer->_SetupBones( LRecord->m_RenderMatrix , sizeof( LRecord->m_RenderMatrix ) / sizeof( Matrix3x4 ) , BONE_USED_BY_ANYTHING , Globals->curtime );
	LRecord->m_vecOrigin = _OffsetManualthis( CBaseEntity::DT_BaseEntity::vecOrigin() , Vector , pPlayer );
	LRecord->m_vecMins = _OffsetManualthis( CBaseEntity::DT_BaseEntity::DT_CollisionProperty::vecMins() , Vector , pPlayer );
	LRecord->m_vecMaxs = _OffsetManualthis( CBaseEntity::DT_BaseEntity::DT_CollisionProperty::vecMaxs() , Vector , pPlayer );
	LRecord->m_masterCycle = _OffsetManualthis( CBaseAnimating::DT_BaseAnimating::DT_ServerAnimationData::flCycle() , float , pPlayer );
	LRecord->m_masterSequence = _OffsetManualthis( CBaseAnimating::DT_BaseAnimating::nSequence() , int , pPlayer );
	LRecord->m_vecAngles = _OffsetManualthis( CBaseEntity::DT_BaseEntity::angRotation() , Angle , pPlayer );
	LRecord->m_flSimulationTime = _OffsetManualthis( CBaseEntity::DT_BaseEntity::flSimulationTime() , float , pPlayer );

	for ( char iSlot = MAX_LAYER_SLOTS - 1; iSlot != -1; iSlot-- )
	{
		for ( int iLayer = MAX_LAYER_RECORDS - 1; iLayer != -1; iLayer-- )
		{
			C_AnimationLayer* AnimLayer = ( C_AnimationLayer* ) Offsets->C_BaseAnimatingOverlay_GetAnimLayer( pPlayer , iLayer , iSlot );

			if ( AnimLayer == nullptr ) continue;

			LRecord->m_layerRecords[ iSlot ][ iLayer ].m_cycle = AnimLayer->flCycle;
			LRecord->m_layerRecords[ iSlot ][ iLayer ].m_order = AnimLayer->nOrder;
			LRecord->m_layerRecords[ iSlot ][ iLayer ].m_sequence = AnimLayer->nSequence;
			LRecord->m_layerRecords[ iSlot ][ iLayer ].m_weight = AnimLayer->flWeight;
		}
	}

	memcpy( LRecord->m_flposeParameters , &_OffsetManualthis( CBaseAnimating::DT_BaseAnimating::m_flPoseParameter::_000() , float , pPlayer ) , sizeof( LRecord->m_flposeParameters ) );
}

void CBacktrack::ApplyRecordToPlayer( C_BasePlayer *pPlayer , LagRecord *LRecord )
{
	int iPlayerIndex = pPlayer->entindex();

	// Whooops no records here
	if ( !IsReadyForBacktrack( pPlayer ) )
		return;

	bool bOldAbsQueriesValid = *Offsets->pbAbsQueriesValid;

	*Offsets->pbAbsQueriesValid = 0;
	*Offsets->pbAbsRecomputationEnabled = 1;

	PlayerRecord[ iPlayerIndex ]->bIsUpdatingVars = true;

	pPlayer->OnPreDataChanged( DATA_UPDATE_DATATABLE_CHANGED );
	pPlayer->PreDataUpdate( DATA_UPDATE_DATATABLE_CHANGED );

	bool bShouldUpdate = false;

	if ( _OffsetManualthis( CBaseEntity::DT_BaseEntity::vecOrigin() , Vector , pPlayer ) != LRecord->m_vecOrigin )
	{
		_OffsetManualthis( CBaseEntity::DT_BaseEntity::vecOrigin() , Vector , pPlayer ) = LRecord->m_vecOrigin;
		bShouldUpdate = true;
	}

	if ( _OffsetManualthis( CBaseEntity::DT_BaseEntity::DT_CollisionProperty::vecMins() , Vector , pPlayer ) != LRecord->m_vecMins )
	{
		_OffsetManualthis( CBaseEntity::DT_BaseEntity::DT_CollisionProperty::vecMins() , Vector , pPlayer ) = LRecord->m_vecMins;
		bShouldUpdate = true;
	}

	if ( _OffsetManualthis( CBaseEntity::DT_BaseEntity::DT_CollisionProperty::vecMaxs() , Vector , pPlayer ) != LRecord->m_vecMaxs )
	{
		_OffsetManualthis( CBaseEntity::DT_BaseEntity::DT_CollisionProperty::vecMaxs() , Vector , pPlayer ) = LRecord->m_vecMaxs;
		bShouldUpdate = true;
	}

	if ( _OffsetManualthis( CBaseAnimating::DT_BaseAnimating::DT_ServerAnimationData::flCycle() , float , pPlayer ) != LRecord->m_masterCycle )
	{
		_OffsetManualthis( CBaseAnimating::DT_BaseAnimating::DT_ServerAnimationData::flCycle() , float , pPlayer ) = LRecord->m_masterCycle;
		bShouldUpdate = true;
	}

	if ( _OffsetManualthis( CBaseAnimating::DT_BaseAnimating::nSequence() , int , pPlayer ) != LRecord->m_masterSequence )
	{
		_OffsetManualthis( CBaseAnimating::DT_BaseAnimating::nSequence() , int , pPlayer ) = LRecord->m_masterSequence;
		bShouldUpdate = true;
	}

	if ( _OffsetManualthis( CBaseEntity::DT_BaseEntity::angRotation() , Angle , pPlayer ) != LRecord->m_vecAngles )
	{
		_OffsetManualthis( CBaseEntity::DT_BaseEntity::angRotation() , Angle , pPlayer ) = LRecord->m_vecAngles;
		bShouldUpdate = true;
	}

	if ( _OffsetManualthis( CBaseEntity::DT_BaseEntity::flSimulationTime() , float , pPlayer ) != LRecord->m_flSimulationTime )
	{
		_OffsetManualthis( CBaseEntity::DT_BaseEntity::flSimulationTime() , float , pPlayer ) = LRecord->m_flSimulationTime;
		bShouldUpdate = true;
	}

	for ( char iSlot = MAX_LAYER_SLOTS - 1; iSlot != -1; iSlot-- )
	{
		for ( int iLayer = MAX_LAYER_RECORDS - 1; iLayer != -1; iLayer-- )
		{
			C_AnimationLayer* AnimLayer = ( C_AnimationLayer* ) Offsets->C_BaseAnimatingOverlay_GetAnimLayer( pPlayer , iLayer , iSlot );

			if ( AnimLayer == nullptr ) continue;

			if ( AnimLayer->flCycle != LRecord->m_layerRecords[ iSlot ][ iLayer ].m_cycle )
			{
				AnimLayer->flCycle = LRecord->m_layerRecords[ iSlot ][ iLayer ].m_cycle;
				bShouldUpdate = true;
			}

			if ( AnimLayer->nOrder != LRecord->m_layerRecords[ iSlot ][ iLayer ].m_order )
			{
				AnimLayer->nOrder = LRecord->m_layerRecords[ iSlot ][ iLayer ].m_order;
				bShouldUpdate = true;
			}

			if ( AnimLayer->nSequence != LRecord->m_layerRecords[ iSlot ][ iLayer ].m_sequence )
			{
				AnimLayer->nSequence = LRecord->m_layerRecords[ iSlot ][ iLayer ].m_sequence;
				bShouldUpdate = true;
			}

			if ( AnimLayer->flWeight != LRecord->m_layerRecords[ iSlot ][ iLayer ].m_weight )
			{
				AnimLayer->flWeight = LRecord->m_layerRecords[ iSlot ][ iLayer ].m_weight;
				bShouldUpdate = true;
			}
		}
	}

	for ( char iPose = MAXSTUDIOPOSEPARAM - 1; iPose != -1; iPose-- )
	{
		if ( _OffsetManualthis( ( CBaseAnimating::DT_BaseAnimating::m_flPoseParameter::_000() + ( HEX ) ( iPose * sizeof( float ) ) ) , float , pPlayer ) != LRecord->m_flposeParameters[ iPose ] )
		{
			_OffsetManualthis( ( CBaseAnimating::DT_BaseAnimating::m_flPoseParameter::_000() + ( HEX ) ( iPose * sizeof( float ) ) ) , float , pPlayer ) = LRecord->m_flposeParameters[ iPose ];
			bShouldUpdate = true;
		}
	}

	if ( !bShouldUpdate ) return;

	pPlayer->OnDataChanged( DATA_UPDATE_DATATABLE_CHANGED );
	pPlayer->PostDataUpdate( DATA_UPDATE_DATATABLE_CHANGED );

	*Offsets->pbAbsQueriesValid = bOldAbsQueriesValid;
	*Offsets->pbAbsRecomputationEnabled = 0;

	PlayerRecord[ iPlayerIndex ]->bIsUpdatingVars = false;
}

void CBacktrack::AdjustTickCount( CUserCmd*Cmd )
{
	if ( Cvars[ hack_backtrack ]->GetInt() <= 0 )
		return;

	C_BasePlayer *LocalPlayer = GetLocalPlayer();
	if ( LocalPlayer == nullptr )
		return;

	C_Weapon *Weapon = LocalPlayer->GetWeapon();
	if ( Weapon == nullptr )
		return;

	Vector vEyePos;
	if ( Cvars[ hack_backtrack_server_has_posfix ]->GetBool() )
		vEyePos = HackPrediction->vecOldEyePos;
	else
		vEyePos = LocalPlayer->GetEyePosition();

	float flClosestHitboxes = FLT_MAX;
	float flNewTimeCount = Globals->curtime;

	Vector vecDir;
	AngleToVectors( Cmd->viewangles + ( *LocalPlayer->PunchAngles() * 2.0f ) , &vecDir );

	int iChosenI = 0;

	for ( HEX i = Globals->maxClients; i != 0; i-- )
	{
		C_BasePlayer* pPlayer = ( C_BasePlayer* ) ClientEntityList->GetClientEntity( i );

		if ( pPlayer != nullptr )
		{
			int iEntIndex = pPlayer->entindex();

			if ( !Backtrack->IsReadyForBacktrack( pPlayer ) )
				continue;

			CPlayerBacktrack* _PlayerRecord = Backtrack->PlayerRecord[ iEntIndex ];

			int iNumHitboxes = pPlayer->GetNumHitboxes();

			if ( iNumHitboxes == 0 )
				continue;

			for ( int iHistory = MAX_HISTORY_BACKTRACK - 1; iHistory != -1; iHistory-- )
			{
				int iSlot = GetHistorySlot( iEntIndex , iHistory );

				if ( !_PlayerRecord->IsValid( iSlot ) )
					continue;

				LagRecord *LRecord = &_PlayerRecord->LagRecords[ iSlot ];

				for ( int iBox = iNumHitboxes - 1; iBox != -1; iBox-- )
				{
					mstudiobbox_t* Box = pPlayer->GetBox( iBox );

					if ( Box == nullptr )
						continue;

					if ( Box->group != HITGROUP_HEAD )
						continue;

					Vector vMins = Box->bbmin , vMaxs = Box->bbmax;

					if ( IsBoxCapsule( Box ) )
					{
						vMins -= Box->m_flRadius;
						vMaxs += Box->m_flRadius;
					}

					Vector vecPoint = ( vMins + vMaxs ) * 0.5f;

					Vector vPointToWorld;
					VectorTransform( vecPoint
									 , LRecord->m_RenderMatrix[ Box->bone ]
									 , vPointToWorld );

					Vector vDir = vPointToWorld - vEyePos;
					Angle aDir;
					VectorToAngles( vDir , aDir );
					aDir.Normalize180();

					Angle aDif = ( Cmd->viewangles - aDir );
					aDif.Normalize180();
					aDif.x = abs( aDif.x );
					aDif.y = abs( aDif.y );
					aDif.z = abs( aDif.z );

					float flLength = vDir.Length();

					Vector vOpposeDist( sin( DEGTORAD( aDif.x ) ) * flLength , sin( DEGTORAD( aDif.y ) ) * flLength , sin( DEGTORAD( aDif.z ) ) * flLength );

					float fLengthOpposite = vOpposeDist.Length();

					if ( flClosestHitboxes > fLengthOpposite )
					{
						flNewTimeCount = LRecord->m_flSimulationTime;
						flClosestHitboxes = fLengthOpposite;
						iAdjustedPlayerIndex = iEntIndex;
						iAdjustedPlayerHistory = iHistory;
						iChosenI = i;
					}
				}
			}
		}
	}


	float lerp_remainder = fmodf( GetLerpTime() , Globals->interval_per_tick );

	// Get real simulation time and calculate interp fraction
	float real_target_time = flNewTimeCount;

	float frac = 0.f;

	if ( lerp_remainder > 0.f )
	{
		real_target_time += Globals->interval_per_tick - lerp_remainder;
		// Trigger float inaccuracies (if there is any) and get same frac as the server
		frac = ( real_target_time - flNewTimeCount ) / Globals->interval_per_tick;
	}

	// Apply correct tick_count
	Cmd->tick_count = TIME_TO_TICKS( real_target_time + GetLerpTime() );

	/*if ( Cmd->buttons & IN_ATTACK && iChosenI != 0 )
	{
		C_BasePlayer* pPlayer = ( C_BasePlayer* ) ClientEntityList->GetClientEntity( iChosenI );

		CPlayerBacktrack* pRecord = PlayerRecord[ pPlayer->entindex() ];

		EngineClient->Con_NPrintf( 1 , "%f %f %f - %f %f %f" , _OffsetManualthis( CBaseEntity::DT_BaseEntity::vecOrigin() , Vector , pPlayer ).x ,
								   _OffsetManualthis( CBaseEntity::DT_BaseEntity::vecOrigin() , Vector , pPlayer ).y ,
								   _OffsetManualthis( CBaseEntity::DT_BaseEntity::vecOrigin() , Vector , pPlayer ).z
		, pRecord->LagRecords[ GetHistorySlot(pPlayer,0) ].m_vecOrigin.x
		, pRecord->LagRecords[ GetHistorySlot( pPlayer , 0 ) ].m_vecOrigin.y
		, pRecord->LagRecords[ GetHistorySlot( pPlayer , 0 ) ].m_vecOrigin.z );
	}*/

	//EngineClient->Con_NPrintf( 1 , "%f" , CalculateDeltaTime( Cmd->tick_count ) );
}

void CBacktrack::PushBackLag( C_BasePlayer* pPlayer , int index )
{
	int iPlayerIndex = pPlayer->entindex();

	Backtrack->UpdateHistorySlots( iPlayerIndex );

	int iSlot = GetHistorySlot( iPlayerIndex , 0 );

	int iPrevSlot = GetHistorySlot( iPlayerIndex , 0 );

	/*int iSlot = PlayerRecord[ iPlayerIndex ]->iCurrentIndexHistory;

	if ( iSlot < 0 )
		iSlot += MAX_HISTORY_BACKTRACK - 1;

	int iPrevSlot = PlayerRecord[ iPlayerIndex ]->iCurrentIndexHistory - 1;

	if ( iPrevSlot < 0 )
		iPrevSlot += MAX_HISTORY_BACKTRACK - 1;*/

	CPlayerBacktrack* CurrentPlayerRecord = PlayerRecord[ iPlayerIndex ];
	BackUpRecordToPlayer( pPlayer , &CurrentPlayerRecord->LagRecords[ iSlot ] , index );

	CurrentPlayerRecord->flSimulationTimes[ iSlot ] = _OffsetManualthis( CBaseEntity::DT_BaseEntity::flSimulationTime() , float , pPlayer );
	CurrentPlayerRecord->bIsAlive = _OffsetManualthis( CBasePlayer::DT_BasePlayer::lifeState() , int , pPlayer ) == LIFE_ALIVE;

	Vector vDeltaOrigin = CurrentPlayerRecord->LagRecords[ iSlot ].m_vecOrigin - CurrentPlayerRecord->LagRecords[ iPrevSlot ].m_vecOrigin;

	if ( Cvars[ hack_backtrack_check_sqr ]->GetBool() )
	{
		if ( vDeltaOrigin.Length() > LAG_COMPENSATION_TELEPORTED_DISTANCE_SQR )
		{
			for ( int iClearSlot = 0; iClearSlot < MAX_HISTORY_BACKTRACK; iClearSlot++ )
			{
				CurrentPlayerRecord->flSimulationTimes[ iClearSlot ] = INVALID_SIMULATION;
			}
		}
	}

	if ( !CurrentPlayerRecord->bIsAlive )
	{
		for ( int iClearSlot = 0; iClearSlot < MAX_HISTORY_BACKTRACK; iClearSlot++ )
		{
			CurrentPlayerRecord->flSimulationTimes[ iClearSlot ] = INVALID_SIMULATION;
		}
	}
}

bool CBacktrack::CanBacktrack( int iTickCount )
{
	return fabs( CalculateDeltaTime( iTickCount ) ) <= 0.2f;
}

float CBacktrack::CalculateDeltaTime( int iTickCount )
{
	INetChannelInfo *nci = EngineClient->GetNetChannelInfo();

	// NOTE:  do these computations in float time, not ticks, to avoid big roundoff error accumulations in the math
	// add view interpolation latency see C_BaseEntity::GetInterpolationAmount()
	float correct = GetLerpTime();

	if ( nci != nullptr )
	{
		// add network latency
		correct += nci->GetLatency( FLOW_OUTGOING );
	}

	// check bounds [0,sv_maxunlag]

	static ConVar *maxunlag = Cvar->FindVar( "sv_maxunlag" );

	correct = clamp( correct , 0.0f , maxunlag->GetFloat() );

	// correct tick send by player
	float flTargetTime = TICKS_TO_TIME( iTickCount );

	// calculate difference between tick sent by player and our latency based tick
	float deltaTime = correct - ( TICKS_TO_TIME( GetPredictedServerTick() ) - flTargetTime );

	return fabs( deltaTime );
}

// Let's check approximativly the server tick count.
int CBacktrack::GetPredictedServerTick()
{
	static int iPredictedTick = 0;

	C_BasePlayer *pLocalPlayer = GetLocalPlayer();

	if ( pLocalPlayer != nullptr )
	{
		iPredictedTick = *GetLocalPlayer()->TickBase();
	}

	return iPredictedTick;
}

void CBacktrack::UpdateLerpTime()
{
    static ConVar* interp = Cvar->FindVar( "cl_interp" );

	static ConVar* updaterate = Cvar->FindVar( "cl_updaterate" );
	int UpdateRate = updaterate->GetInt();

	static const ConVar *pMinUpdateRate = Cvar->FindVar( "sv_minupdaterate" );
	static const ConVar *pMaxUpdateRate = Cvar->FindVar( "sv_maxupdaterate" );
	if ( pMinUpdateRate && pMaxUpdateRate )
		UpdateRate = ( int ) clamp( UpdateRate , pMinUpdateRate->GetFloat() , pMaxUpdateRate->GetFloat() );

	static ConVar* interp_ratio = Cvar->FindVar( "cl_interp_ratio" );
	float flLerpRatio = interp_ratio->GetFloat();
	if ( flLerpRatio == 0 )
		flLerpRatio = 1.0f;

	float flLerpAmount = interp->GetFloat();

	static const ConVar *pMin = Cvar->FindVar( "sv_client_min_interp_ratio" );
	static const ConVar *pMax = Cvar->FindVar( "sv_client_max_interp_ratio" );
	if ( pMin && pMax && pMin->GetFloat() != -1 )
	{
		flLerpRatio = clamp( flLerpRatio , pMin->GetFloat() , pMax->GetFloat() );
	}
	else
	{
		if ( flLerpRatio == 0 )
			flLerpRatio = 1.0f;
	}

	LerpTime = max( flLerpAmount , flLerpRatio / UpdateRate );
}

float CBacktrack::GetLerpTime()
{
	return LerpTime;
}

bool CBacktrack::IsReadyForBacktrack( C_BasePlayer* pPlayer )
{
	CPlayerBacktrack* CurrentPlayerRecord = PlayerRecord[ pPlayer->entindex() ];

	if ( CurrentPlayerRecord == nullptr )
		return false;

	if ( pPlayer->IsLocalPlayer() )
		return false;

	return ( _OffsetManualthis( CBasePlayer::DT_BasePlayer::iObserverMode() , int , pPlayer ) == OBS_MODE_NONE )
		&& !pPlayer->IsDormant()
		&& ( ( _OffsetManualthis( CBaseEntity::DT_BaseEntity::iTeamNum() , int , pPlayer )
			 != _OffsetManualthis( CBaseEntity::DT_BaseEntity::iTeamNum() , int , GetLocalPlayer() ) ) || !Cvars[ hack_backtrack_team_check ]->GetBool() );
}

void CBacktrack::UpdateMaxHistory( int iEntIndex )
{
	// Check as lag compensation code does.

	CPlayerBacktrack *_PlayerRecord = PlayerRecord[ iEntIndex ];

	for ( int iHistory = MAX_HISTORY_BACKTRACK - 1; iHistory != -1; iHistory-- )
	{
		_PlayerRecord->bIsValid[ iHistory ] = false;

		int iSlot = GetHistorySlot( iEntIndex , iHistory );

		if ( iSlot == -1 )
			continue;

		if ( _PlayerRecord->flSimulationTimes[ iSlot ] == INVALID_SIMULATION )
			continue;

		if ( CanBacktrack( TIME_TO_TICKS( _PlayerRecord->flSimulationTimes[ iSlot ] ) ) )
		{
			_PlayerRecord->bIsValid[ iSlot ] = true;
		}
	}
}

void CBacktrack::UpdateMaxHistory( C_BasePlayer* pPlayer )
{
	int iPlayerIndex = pPlayer->entindex();

	// Check as lag compensation code does.
	UpdateMaxHistory( iPlayerIndex );
}

void CBacktrack::PreRender( C_BasePlayer* pPlayer , DrawModelState_t &State , ModelRenderInfo_t &Info , LagRecord* LRecord , int loopindex , bool &bCanRender )
{
	bCanRender = false;

	IClientRenderable* ClientRenderable = pPlayer->GetClientRenderable();

	if ( ClientRenderable != nullptr )
	{
		CPlayerBacktrack* _PlayerRecord = PlayerRecord[ pPlayer->entindex() ];

		const model_t *Model = pPlayer->GetModel();

		if ( Model != nullptr )
		{
			if ( Model->studio != mod_bad )
			{
				studiohdr_t *hdr = MDLCache->GetStudioHdr( Model->studio );

				if ( hdr != nullptr )
				{
					if ( hdr->numbodyparts != 0 )
					{
						studiohwdata_t* hwdata = MDLCache->GetHardwareData( Model->studio );

						if ( hwdata != nullptr )
						{
							ModelInstanceHandle_t MDLInst = pPlayer->GetModelInstance();

							_PlayerRecord->MDLRenderingInstance = MODEL_INSTANCE_INVALID;

							if ( MDLInst == MODEL_INSTANCE_INVALID )
							{
								_PlayerRecord->MDLRenderingInstance = MDLInst = ModelRender->CreateInstance( ClientRenderable );
							}

							if ( MDLInst != MODEL_INSTANCE_INVALID )
							{
								_PlayerRecord->bIsShowModel = true;
								Info.pRenderable = ClientRenderable;
								Info.angles = LRecord->m_vecAngles;
								Info.body = pPlayer->GetBody();
								Info.skin = _CallVirtualFunction<int , Pointer>( Info.pRenderable , 38 );
								Info.entity_index = loopindex;
								Info.hitboxset = _OffsetManualthis( CBaseAnimating::DT_BaseAnimating::nHitboxSet() , int , pPlayer );
								Info.flags = STUDIO_RENDER;
								Info.origin = LRecord->m_vecOrigin;
								Info.pLightingOffset = nullptr;
								Info.pLightingOrigin = nullptr;
								Info.pModel = Model;
								AngleMatrix( Info.angles , Info.origin , _PlayerRecord->mCurrentShowedMatrix );
								Info.pModelToWorld = &_PlayerRecord->mCurrentShowedMatrix;
								Info.instance = MDLInst;

								State.m_decals = STUDIORENDER_DECAL_INVALID;

								State.m_drawFlags = STUDIORENDER_DRAW_ENTIRE_MODEL;

								if ( Info.flags & STUDIO_TWOPASS )
								{
									if ( Info.flags & STUDIO_TRANSPARENCY )
									{
										State.m_drawFlags = STUDIORENDER_DRAW_TRANSLUCENT_ONLY;
									}
									else
									{
										State.m_drawFlags = STUDIORENDER_DRAW_OPAQUE_ONLY;
									}
								}
								if ( Info.flags & STUDIO_STATIC_LIGHTING )
								{
									State.m_drawFlags |= STUDIORENDER_DRAW_STATIC_LIGHTING;
								}

								if ( Info.flags & STUDIO_ITEM_BLINK )
								{
									State.m_drawFlags |= STUDIORENDER_DRAW_ITEM_BLINK;
								}

								if ( Info.flags & STUDIO_WIREFRAME )
								{
									State.m_drawFlags |= STUDIORENDER_DRAW_WIREFRAME;
								}

								if ( Info.flags & STUDIO_NOSHADOWS )
								{
									State.m_drawFlags |= STUDIORENDER_DRAW_NO_SHADOWS;
								}

								if ( Info.flags & STUDIO_SHADOWDEPTHTEXTURE )
								{
									State.m_drawFlags |= STUDIORENDER_SHADOWDEPTHTEXTURE;
								}

								State.m_lod = 0;
								State.m_pModelToWorld = &_PlayerRecord->mCurrentShowedMatrix;
								State.m_pRenderable = ClientRenderable;
								State.m_pStudioHdr = hdr;
								State.m_pStudioHWData = hwdata;

								bCanRender = true;
							}
						}
					}
				}
			}
		}
	}
}

void CBacktrack::PostRender( C_BasePlayer* pPlayer , DrawModelState_t &State , ModelRenderInfo_t &Info )
{
	CPlayerBacktrack* _PlayerRecord = PlayerRecord[ pPlayer->entindex() ];

	if ( _PlayerRecord->MDLRenderingInstance != MODEL_INSTANCE_INVALID )
	{
		ModelRender->DestroyInstance( _PlayerRecord->MDLRenderingInstance );
		_PlayerRecord->MDLRenderingInstance = MODEL_INSTANCE_INVALID;
	}

	_PlayerRecord->bIsShowModel = false;
}