#ifndef BACKTRACK
#define BACKTRACK
#pragma once

#define MAX_LAYER_SLOTS 2
#define MAX_LAYER_RECORDS 15
#define MAXSTUDIOBONES_PLAYER MAXSTUDIOBONES
#define MAXSTUDIOPOSEPARAM	24
#define INVALID_SIMULATION -1.0f
#define INVALID_DELTA -2.0f

extern int MAX_HISTORY_BACKTRACK;

constexpr int MAX_SEEDS = 256;

class C_AnimationLayer
{
public:
	Byte pad[ 0x14 ];
	int nOrder;
	int nSequence;
	float flPrevCycle;
	float flWeight;
	float flWeightDeltaRate;
	float flPlayBackRate;
	float flCycle;
};

struct LayerRecord
{
	int m_sequence;
	float m_cycle;
	float m_weight;
	int m_order;

	LayerRecord()
	{
		Clear();
	}

	LayerRecord( const LayerRecord& src )
	{
		m_sequence = src.m_sequence;
		m_cycle = src.m_cycle;
		m_weight = src.m_weight;
		m_order = src.m_order;
	}

	void Clear()
	{
		m_sequence = 0;
		m_cycle = 0;
		m_weight = 0;
		m_order = 0;
	}
};

struct LagRecord
{
public:

	// In case it gets overwritten by valvo
	LagRecord()
	{
		/*m_RenderMatrix = new Matrix3x4[ MAXSTUDIOBONES ];
		pOldAllocatedMatrix1 = m_RenderMatrix;

		m_RenderInfo.pModelToWorld = new Matrix3x4();
		pOldAllocatedMatrix2 = m_RenderInfo.pModelToWorld;

		m_DrawState.m_pModelToWorld = new Matrix3x4();
		pOldAllocatedMatrix3 = m_DrawState.m_pModelToWorld;*/
	}

	// Player position, orientation and bbox
	Vector					m_vecOrigin;
	Angle					m_vecAngles;
	Vector					m_vecMins;
	Vector					m_vecMaxs;
	float                   m_flSimulationTime;

	// Player animation details, so we can get the legs in the right spot.
	LayerRecord				m_layerRecords[ MAX_LAYER_SLOTS ][ MAX_LAYER_RECORDS ];
	int						m_masterSequence;
	float					m_masterCycle;
	float                   m_flposeParameters[ MAXSTUDIOPOSEPARAM ];
	Matrix3x4               m_RenderMatrix[ MAXSTUDIOBONES_PLAYER ];
};

class CPlayerBacktrack
{
public:
	CPlayerBacktrack( int MAX_HISTORY )
	{
		iMaxLagRecords = -1;
		flOldSimulationTime = -1.0f;
		bIsShowModel = false;
		bIsUpdatingVars = false;
		iHistoryShowModel = false;
		iCurrentIndexHistory = 0;
		LagRecords = new LagRecord[ MAX_HISTORY ];
		flSimulationTimes = new float[ MAX_HISTORY_BACKTRACK ];
		bIsValid = new bool[ MAX_HISTORY_BACKTRACK ];

		for ( int iSlot = 0; iSlot < MAX_HISTORY_BACKTRACK; iSlot++ )
		{
			flSimulationTimes[ iSlot ] = INVALID_SIMULATION;
			bIsValid[ iSlot ] = false;
		}

		MDLRenderingInstance = MODEL_INSTANCE_INVALID;
	}

	~CPlayerBacktrack()
	{
		Free();
	}

	void Free()
	{
		if ( LagRecords != nullptr )
		{
			delete[] LagRecords;
			LagRecords = nullptr;
		}

		if ( flSimulationTimes != nullptr )
		{
			delete[] flSimulationTimes;
			flSimulationTimes = nullptr;
		}

		if ( bIsValid != nullptr )
		{
			delete[] bIsValid;
			bIsValid = nullptr;
		}

		flOldSimulationTime = -1.0f;
		bIsShowModel = false;
		bIsUpdatingVars = false;
		iHistoryShowModel = false;
		iMaxLagRecords = -1;
		iCurrentIndexHistory = 0;
		MDLRenderingInstance = MODEL_INSTANCE_INVALID;
	}

	bool IsValid( int &iSlot )
	{
		return bIsValid && ( iSlot != -1 );
	}

	LagRecord* LagRecords;
	float flOldSimulationTime;
	bool bIsShowModel;
	bool bIsUpdatingVars;
	int iHistoryShowModel;
	int iMaxLagRecords;
	int iCurrentIndexHistory;
	float* flSimulationTimes;
	Vector vOldOrigin;
	bool bIsAlive;
	bool *bIsValid;
	Matrix3x4 mCurrentShowedMatrix;
	ModelInstanceHandle_t MDLRenderingInstance;
};

class CSimulateBullets
{
public:
	std::vector<Vector> v_History_Bullets[ MAX_SEEDS ];
};

class CBacktrack
{
public:

	CBacktrack();

	~CBacktrack();

	void PushBack();

	void PushBackLag( C_BasePlayer *pPlayer , int index );

	int GetHistorySlot( int iEntIndex , int iSlot )
	{
		if ( iSlot >= MAX_HISTORY_BACKTRACK )
			return -1;

		if ( iSlot < 0 )
			return -1;

		int iHistorySlot = PlayerRecord[ iEntIndex ]->iCurrentIndexHistory - iSlot;

		if ( iHistorySlot < 0 )
			iHistorySlot += MAX_HISTORY_BACKTRACK;

		return iHistorySlot;
	}

	void UpdateHistorySlots( int iEntIndex )
	{
		CPlayerBacktrack* CurrentPlayerRecord = PlayerRecord[ iEntIndex ];

		CurrentPlayerRecord->iCurrentIndexHistory++;

		if ( CurrentPlayerRecord->iCurrentIndexHistory == MAX_HISTORY_BACKTRACK )
			CurrentPlayerRecord->iCurrentIndexHistory = 0;

		if ( CurrentPlayerRecord->iMaxLagRecords < MAX_HISTORY_BACKTRACK )
			CurrentPlayerRecord->iMaxLagRecords++;
	}

	int GetHistorySlot( C_BasePlayer *pPlayer , int iSlot )
	{
		int iEntIndex = pPlayer->entindex();

		return GetHistorySlot( iEntIndex , iSlot );
	}

	void UpdateHistorySlots( C_BasePlayer* pPlayer )
	{
		int iPlayerIndex = pPlayer->entindex();

		UpdateHistorySlots( iPlayerIndex );
	}

	//void ShowModels();

	void AdjustTickCount( CUserCmd *Cmd );

	void ApplyRecordToPlayer( C_BasePlayer *pPlayer , LagRecord *LRecord );

	void BackUpRecordToPlayer( C_BasePlayer *pPlayer , LagRecord *LRecord , int index = -1 );

	bool CanBacktrack( int iTickCount );

	float CalculateDeltaTime( int iTickCount );

	void UpdateMaxHistory( int iEntIndex );

	void UpdateMaxHistory( C_BasePlayer* pPlayer );

	bool IsReadyForBacktrack( C_BasePlayer* pPlayer );

	void UpdateLerpTime();

	float GetLerpTime();

	int GetPredictedServerTick();

	void PreRender( C_BasePlayer* pPlayer , DrawModelState_t &State , ModelRenderInfo_t &Info , LagRecord* LRecord , int loopindex , bool &bCanRender );

	void PostRender( C_BasePlayer* pPlayer , DrawModelState_t &State , ModelRenderInfo_t &Info );

	CPlayerBacktrack *PlayerRecord[ MAX_PLAYERS + 1 ];

	float LerpTime;
	int iAdjustedPlayerIndex;
	int iAdjustedPlayerHistory;
};

extern CBacktrack *Backtrack;

#endif