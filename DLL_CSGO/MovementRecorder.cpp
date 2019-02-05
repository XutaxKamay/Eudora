#include "Includes.hxx"
#include "Main.hxx"

constexpr byte bIV[ CryptoPP::AES::BLOCKSIZE ] = TEXT( "XutaxKamay`2407" );
constexpr size_t SizeKey = CryptoPP::AES::MAX_KEYLENGTH;
constexpr size_t MRSize = sizeof( CMovementRecord );
constexpr size_t EndZoneSize = sizeof( CZone );
float MAX_ZONE_TRACE = 500.0f;

CMovementRecorder* MovementRecorder = new CMovementRecorder();

HEX __stdcall CMovementRecorder::SaveRoutine( Pointer pTmpFile )
{
    MovementRecorder->SaveRecording( ( bool ) pTmpFile );

    return true;
}

HEX __stdcall CMovementRecorder::LoadRoutine( Pointer pArg )
{
    MovementRecorder->LoadRecording();

    return true;
}

CPlayerRecord& CPlayerRecord::operator=( C_BasePlayer *pPlayer )
{
    m_vecOrigin = _OffsetManualthis( CBaseEntity::DT_BaseEntity::vecOrigin() , Vector , pPlayer );
    m_fFlags = _OffsetManualthis( CBasePlayer::DT_BasePlayer::fFlags() , int , pPlayer );
    m_vecMins = _OffsetManualthis( CBaseEntity::DT_BaseEntity::DT_CollisionProperty::vecMins() , Vector , pPlayer );
    m_vecMaxs = _OffsetManualthis( CBaseEntity::DT_BaseEntity::DT_CollisionProperty::vecMaxs() , Vector , pPlayer );
    m_flCycle = _OffsetManualthis( CBaseAnimating::DT_BaseAnimating::DT_ServerAnimationData::flCycle() , float , pPlayer );
    m_iSequence = _OffsetManualthis( CBaseAnimating::DT_BaseAnimating::nSequence() , int , pPlayer );
    m_vecAngles = _OffsetManualthis( CBaseEntity::DT_BaseEntity::angRotation() , Angle , pPlayer );

    for ( char iSlot = 0; iSlot < MAX_LAYER_SLOTS; iSlot++ )
    {
        for ( int iLayer = 0; iLayer < MAX_LAYER_RECORDS; iLayer++ )
        {
            C_AnimationLayer* AnimLayer = ( C_AnimationLayer* ) Offsets->C_BaseAnimatingOverlay_GetAnimLayer( pPlayer , iLayer , iSlot );

            if ( AnimLayer == nullptr ) continue;

            m_LayerRecords[ iSlot ][ iLayer ].m_cycle = AnimLayer->flCycle;
            m_LayerRecords[ iSlot ][ iLayer ].m_order = AnimLayer->nOrder;
            m_LayerRecords[ iSlot ][ iLayer ].m_sequence = AnimLayer->nSequence;
            m_LayerRecords[ iSlot ][ iLayer ].m_weight = AnimLayer->flWeight;
        }
    }

    memcpy( m_flPoseParameters , &_OffsetManualthis( CBaseAnimating::DT_BaseAnimating::m_flPoseParameter::_000() , float , pPlayer ) , sizeof( m_flPoseParameters ) );

    //pPlayer->SetupBones( Matrix , MAXSTUDIOBONES , BONE_USED_BY_ANYTHING , Globals->curtime );

    return *this;
}

void CMovementRecorder::SaveRecording( bool bIsTmp )
{
    if ( !CanThink() )
        return;

    if ( v_mrs.size() <= 0 )
        return;

    bIsSaving = true;

    CTimer *Timer = new CTimer();
    Timer->Start();

    byte *bkey = new byte[ SizeKey ];
    memset( bkey , 0 , SizeKey );
    size_t RealSizeKey = strlen( Cvars[ hack_mr_key ]->GetString() );
    memcpy( bkey , Cvars[ hack_mr_key ]->GetString() , RealSizeKey );

    size_t SizeNbTicks = v_mrs.size();
    size_t SizeBuffer = ( SizeNbTicks * MRSize ) + EndZoneSize;

    CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "Saving record (%i ticks): size before compression %f megabytes\n" ) , SizeNbTicks , ( ( double ) SizeBuffer / ( double ) 1048576 ) );

    Pointer pBuffer = Alloc( SizeBuffer );
    HEX hFinalBuffer = ( HEX ) pBuffer;

    for ( size_t sTick = 0; sTick < v_mrs.size(); sTick++ )
    {
        memcpy( ( Pointer ) ( hFinalBuffer + sTick * MRSize ) , &v_mrs[ sTick ] , MRSize );
    }

    size_t iIndexZone = ( SizeBuffer - EndZoneSize );
    HEX hZoneBuffer = hFinalBuffer + iIndexZone;
    memcpy( ( Pointer ) hZoneBuffer , &EndZone , EndZoneSize );

    CryptoPP::ZlibCompressor Compressed;
    Compressed.SetDeflateLevel( CryptoPP::Deflator::MAX_DEFLATE_LEVEL );

    CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "Compressing record...\n" ) );

    Compressed.PutModifiable( ( Bytes ) hFinalBuffer , SizeBuffer );
    Compressed.MessageEnd();

    Pointer pCompressedBuffer = Alloc( ( HEX ) Compressed.MaxRetrievable() );

    size_t CompressedSize = Compressed.Get( ( Bytes ) pCompressedBuffer , ( size_t ) Compressed.MaxRetrievable() );

    CryptoPP::SecByteBlock key( bkey , SizeKey );
    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cfbEncryption( key , key.size() , bIV );

    CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "Encrypting record...\n" ) );

    cfbEncryption.ProcessData( ( Bytes ) pCompressedBuffer , ( Bytes ) pCompressedBuffer , CompressedSize );

    if ( N_FileSystem::CreateFolder( AutoConvertS( Cvars[ hack_mr_path_record ]->GetString() ) ) )
    {
        stdString _sTmpFileName = sTmpFileName;
        _sTmpFileName += TEXT( "_" ) + sTime();
        stdString sPathToFile( stdString( AutoConvertS( Cvars[ hack_mr_path_record ]->GetString() ) ) + TEXT( "\\" ) + ( bIsTmp ? _sTmpFileName : sFileName ) );
        N_FileSystem::ClearFile( sPathToFile );
        N_FileSystem::WriteFile( sPathToFile , ( Pointer ) pCompressedBuffer , ( HEX ) CompressedSize );

        Timer->End();

        CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "Saving record (%i ticks): size after compression %f megabytes (took %f ms) \n" )
                           , SizeNbTicks , ( ( double ) CompressedSize / ( double ) 1048576 ) , Timer->dElapsedTime );
    }

    FreeAlloc( pBuffer );
    FreeAlloc( pCompressedBuffer );
    delete[] bkey;
    delete Timer;

    bIsSaving = false;
}

void CMovementRecorder::LoadRecording()
{
    if ( !CanThink() )
        return;

    bIsLoading = true;

    CTimer *Timer = new CTimer();
    Timer->Start();

    v_mrs.clear();

    stdString sPathToFile( stdString( AutoConvertS( Cvars[ hack_mr_path_record ]->GetString() ) ) + TEXT( "\\" ) + sFileName );

    HEX SizeBuffer = 0;
    Pointer pBuffer = N_FileSystem::ReadFile( sPathToFile.c_str() , &SizeBuffer );

    if ( SizeBuffer <= 0 )
    {
        CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "Loading: File doesn't exist!\n" ) );
        return;
    }

    CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "Loading record... %f megabytes\n" ) , ( ( double ) SizeBuffer / ( double ) 1048576 ) );

    byte *bkey = new byte[ SizeKey ];
    memset( bkey , 0 , SizeKey );
    size_t RealSizeKey = strlen( Cvars[ hack_mr_key ]->GetString() );
    memcpy( bkey , Cvars[ hack_mr_key ]->GetString() , RealSizeKey );
    CryptoPP::SecByteBlock key( bkey , SizeKey );
    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption cfbDecryption( key , key.size() , bIV );

    CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "Decrypting record... %f megabytes\n" ) , ( ( double ) SizeBuffer / ( double ) 1048576 ) );

    cfbDecryption.ProcessData( ( Bytes ) pBuffer , ( Bytes ) pBuffer , SizeBuffer );

    CryptoPP::ZlibDecompressor Decompressed;

    CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "Decompressing record... %f megabytes\n" ) , ( ( double ) SizeBuffer / ( double ) 1048576 ) );

    Decompressed.PutModifiable( ( Bytes ) pBuffer , SizeBuffer );
    Decompressed.MessageEnd();

    Pointer pDecompressedBuffer = Alloc( ( size_t ) Decompressed.MaxRetrievable() );
    size_t DecompressedSize = Decompressed.Get( ( Bytes ) pDecompressedBuffer , ( size_t ) Decompressed.MaxRetrievable() );

    size_t sIndexZone = ( DecompressedSize - EndZoneSize );
    Pointer pZoneBuffer = ( Pointer ) ( ( HEX ) pDecompressedBuffer + sIndexZone );
    memcpy( &EndZone , pZoneBuffer , EndZoneSize );

    size_t TotalPlayerRecords = sIndexZone / MRSize;

    CMovementRecord *MovementRecords = new CMovementRecord[ TotalPlayerRecords ];

    for ( size_t sTick = 0; sTick < TotalPlayerRecords; sTick++ )
    {
        memcpy( ( Pointer ) &MovementRecords[ sTick ] , ( Pointer ) ( ( HEX ) pDecompressedBuffer + sTick * MRSize ) , MRSize );
    }

    for ( size_t sTick = 0; sTick < TotalPlayerRecords; sTick++ )
    {
        v_mrs.push_back( MovementRecords[ sTick ] );
    }

    Timer->End();

    CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "Loaded record! (%i ticks) %f megabytes (took %f ms)\n" ) , TotalPlayerRecords , ( ( double ) DecompressedSize / ( double ) 1048576 ) , Timer->dElapsedTime );

    delete[] MovementRecords;
    FreeAlloc( pBuffer );
    FreeAlloc( pDecompressedBuffer );
    delete[] bkey;
    delete Timer;

    bIsLoading = false;
}

void CMovementRecorder::Recording( CUserCmd* cmd , C_BasePlayer* pPlayer )
{
    if ( iCurrentTick == 0 )
    {
        v_mrs.clear();
    }

    /*if ( cmd->tick_count == TICKCOUNT_PAUSE )
        return;*/

    v_mrs.resize( iCurrentTick + 1 );
    v_mrs[ iCurrentTick ] = CMovementRecord( pPlayer , *cmd );
}

void CMovementRecorder::Playing( CUserCmd* cmd )
{
    if ( iCurrentTick >= GetFinalTick() )
    {
        iState = MR_State::MR_Stop;
        return;
    }

    /*if ( cmd->tick_count == TICKCOUNT_PAUSE )
        return;*/

    CUserRecordCmd *current_cmd = &v_mrs[ iCurrentTick ].m_cmd;

    cmd->viewangles = current_cmd->viewangles;
    cmd->forwardmove = current_cmd->movements.x;
    cmd->sidemove = current_cmd->movements.y;
    cmd->upmove = current_cmd->movements.z;
    cmd->buttons = current_cmd->buttons;
    cmd->headangles = current_cmd->headangles;
    cmd->headoffset = current_cmd->headoffset;
    cmd->mousedx = current_cmd->mousedx;
    cmd->mousedy = current_cmd->mousedy;
    cmd->impulse = current_cmd->impulse;
    cmd->weaponselect = current_cmd->weaponselect;
    cmd->weaponsubtype = current_cmd->weaponsubtype;
}

/*
void CMovementRecorder::Pause( CUserCmd* cmd , C_BasePlayer* pPlayer )
{
    cmd->tick_count = TICKCOUNT_PAUSE;
}
*/

// Ran before anything.
void CMovementRecorder::PreThink( CUserCmd* cmd , C_BasePlayer* pPlayer )
{
    if ( !CanThink( false ) )
        return;

    if ( iState == MR_State::MR_Stop )
    {
        if ( ( iCurrentTick > 0 )
             && ( iOldState == MR_Record )
             && Cvars[ hack_mr_savetmprecord ]->GetBool() )
        {
            RunSave( true );
        }

        iCurrentTick = 0;
        return;
    }
}

// Should be ran only before prediction.
void CMovementRecorder::Think( CUserCmd* cmd , C_BasePlayer* pPlayer )
{
    if ( !CanThink( false ) )
        return;

    if ( iState == MR_Play )
    {
        Playing( cmd );
    }
    /*else if ( iState == MR_Pause )
    {
        Pause( cmd , pPlayer );
    }*/
}

// Should be ran after prediction.
void CMovementRecorder::PostThink( CUserCmd* cmd , C_BasePlayer* pPlayer )
{
    if ( !CanThink( false ) )
        return;

    switch ( iState )
    {
        case MR_Record:
            Recording( cmd , pPlayer );
            break;
        /*case MR_Pause:
            Pause( cmd , pPlayer );
            break;*/
    }

    if ( Cvars[ hack_mr_endzone_enable ]->GetBool() )
    {
        if ( EndZone.IsInZone( pPlayer->GetAbsOrigin() , _OffsetManualthis( CBaseEntity::DT_BaseEntity::DT_CollisionProperty::vecMins() , Vector , pPlayer ) ,
             _OffsetManualthis( CBaseEntity::DT_BaseEntity::DT_CollisionProperty::vecMaxs() , Vector , pPlayer )
             , pPlayer->GetAbsAngles() ) )
        {
            iState = MR_Stop;
        }
    }

    if ( iState > MR_Pause )
    {
        iOldState = iState;
        iCurrentTick++;
    }
}

void CMovementRecorder::RunSave( bool bIsTmp )
{
    if ( !CanThink() )
        return;

    CreateThread( nullptr , 0 , ( LPTHREAD_START_ROUTINE ) SaveRoutine , ( Pointer ) bIsTmp , 0 , nullptr );
}

void CMovementRecorder::RunLoad()
{
    if ( !CanThink() )
        return;

    CreateThread( nullptr , 0 , ( LPTHREAD_START_ROUTINE ) LoadRoutine , nullptr , 0 , nullptr );
}

bool CZone::IsInZone( const Vector& vPos2 , const Vector& vHullMin , const Vector &vHullMax , const Angle aRotation )
{
    if ( Vector() == vHullMax && Vector() == vHullMin )
    {
        return BoxZone.IsPointInBox( vPos2 );
    }
    else
    {
        CBBox BoxCollideWith( vPos2 , vHullMin , vHullMax , aRotation );

        return BoxZone.CollideWith( &BoxCollideWith );
    }
}

void CZone::RenderZone( const Color& cColor )
{
    RenderWireframeBox( BoxZone.vPos , BoxZone.aRotation , BoxZone.vMin , BoxZone.vMax
                        , cColor , false );
}

void CZone::ComputePosFromView( C_BasePlayer* pPlayer , const Angle& aView )
{
    MAX_ZONE_TRACE += GetAsyncKeyState( VK_NUMPAD8 ) ? 1.0f : 0.0f;
    MAX_ZONE_TRACE -= GetAsyncKeyState( VK_NUMPAD2 ) ? 1.0f : 0.0f;
    MAX_ZONE_TRACE = clamp( MAX_ZONE_TRACE , 0.0f , 8192.0f );

    Angle aPointTo = aView;
    aPointTo.Normalize180();

    AngleToVectors( aPointTo , &vForward );
    vStart = pPlayer->GetEyePosition();
    vForward *= MAX_ZONE_TRACE;
    vForward += vStart;

    CTraceFilterWorldOnly TraceWorldOnly;
    Ray ray;
    ray.Init( vStart , vForward );
    EngineTrace->TraceRay( ray , MASK_SOLID , &TraceWorldOnly , &tr );
}

void CZone::RenderTrace( const Color& cColor )
{
    RenderLine( vStart , BoxZone.vWorldTransformedMax , cColor , false );
}

void CZone::ComputeBox( C_BasePlayer* pPlayer , const Angle& aView )
{
    static bool bAllowComputing = false;
    static Vector vMinTrace;

    if ( ZoneStage == Zone_Computing_Start )
    {
        ComputePosFromView( pPlayer , aView );
        vMinTrace = tr.endpos;
        //BoxZone.aRotation.Init();
        bAllowComputing = true;
    }

    if ( bAllowComputing )
    {
        ComputePosFromView( pPlayer , aView );

        if ( ZoneStage == Zone_Computing_Start )
        {
            ZoneStage = Zone_Computing_MinMax;
        }
        else if ( ZoneStage == Zone_Computing_MinMax )
        {
            BoxZone.vPos = ( tr.endpos + vMinTrace ) / 2.0f;
            BoxZone.vMin = vMinTrace - BoxZone.vPos;
            BoxZone.vMax = tr.endpos - BoxZone.vPos;

            //BoxZone.aRotation.y -= GetAsyncKeyState( VK_NUMPAD4 ) ? 0.1f : 0.0f;
            //BoxZone.aRotation.y += GetAsyncKeyState( VK_NUMPAD6 ) ? 0.1f : 0.0f;
            //BoxZone.aRotation.Normalize180();
        }

        BoxZone.Transform();

        if ( GetAsyncKeyState( VK_SUBTRACT ) )
        {
            ZoneStage += 1;
        }

        if ( GetAsyncKeyState( VK_ADD ) )
        {
            ZoneStage = Zone_Computing_Nothing;
        }

        ZoneStage = clamp( ZoneStage , Zone_Computing_MinMax , Zone_Computing_Nothing );

        if ( ZoneStage == Zone_Computing_Nothing )
        {
            bAllowComputing = false;
        }
    }
}