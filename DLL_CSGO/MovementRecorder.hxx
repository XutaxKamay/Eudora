#ifndef MOVEMENTRECORDER
#define MOVEMENTRECORDER
#pragma once

extern float MAX_ZONE_TRACE;
#define TICKCOUNT_PAUSE 0xFFFFFFF

enum MR_State
{
    MR_Stop ,
    MR_Pause ,
    MR_Record ,
    MR_Play ,
};

class CBBox
{
public:

    CBBox()
    {
        Init();
    }

    CBBox( const Vector& vPos , const Vector& vMin , const Vector &vMax , const Angle &aRotation = Angle() )
    {
        this->vMin = vMin;
        this->vMax = vMax;
        this->aRotation = aRotation;
        this->vPos = vPos;
        Transform();
    }

    void Transform()
    {
        Vector vOldMin = vMin , vOldMax = vMax;

        for ( int i = 0; i < 3; i++ )
        {
            vMin[ i ] = min( vOldMin[ i ] , vOldMax[ i ] );
        }

        for ( int i = 0; i < 3; i++ )
        {
            vMax[ i ] = max( vOldMin[ i ] , vOldMax[ i ] );
        }

        vWorldMin = vPos + vMin;
        vWorldMax = vPos + vMax;
        AngleMatrix( aRotation , vPos , Matrix );
        VectorTransform( vMin , Matrix , vWorldTransformedMin );
        VectorTransform( vMax , Matrix , vWorldTransformedMax );
    }

    void Init()
    {
        Matrix.Clear();
        vMin.Init();
        vMax.Init();
    }

    bool CollideWith( CBBox* BoxCollideWith )
    {
        return IsOBBIntersectingOBB( vPos , aRotation , vMin , vMax , BoxCollideWith->vPos , BoxCollideWith->aRotation , BoxCollideWith->vMin , BoxCollideWith->vMax );
    }

    bool IsPointInBox( const Vector& vPoint )
    {
        return IsOBBIntersectingOBB( vPos , aRotation , vMin , vMax , vPoint , Angle() , Vector() , Vector() );
    }

    Vector vMin , vMax , vWorldMin , vWorldMax , vWorldTransformedMin , vWorldTransformedMax , vPos;
    Matrix3x4 Matrix;
    Angle aRotation;
};

enum ZoneCompute
{
    Zone_Computing_MinMax ,
    Zone_Computing_Start ,
    Zone_Computing_Nothing
};

class CZone
{
public:

    CZone()
    {
        Clear();
    }

    void Clear()
    {
        BoxZone.Init();
        vStart.Init();
        vForward.Init();
        ZoneStage = Zone_Computing_Nothing;
    }

    CZone( const Vector& vPos , const Vector& vMin , const Vector &vMax , const Angle &aRotation = Angle() )
    {
        BoxZone = CBBox( vPos , vMin , vMax , aRotation );
        ZoneStage = Zone_Computing_Nothing;
    }

    void RenderZone( const Color& cColor );

    bool IsInZone( const Vector& vPos , const Vector& vHullMin = Vector() , const Vector &vHullMax = Vector() , const Angle aRotation = Angle() );

    void ComputePosFromView( C_BasePlayer* pPlayer , const Angle& aView );

    void RenderTrace( const Color& cColor );

    void ComputeBox( C_BasePlayer* pPlayer , const Angle& aView );

    CBBox BoxZone;
    trace_t tr , tr_trans;
    Vector vForward , vStart;
    int ZoneStage;
};

class CPlayerRecord
{
public:

    CPlayerRecord()
    {
        Reset();
    }

    void Reset()
    {
        m_iSequence = m_fFlags = 0;
        m_vecOrigin.Init();
        m_vecAngles.Init();
        m_vecMins.Init();
        m_vecMaxs.Init();

        m_flCycle = 0.0f;

        memset( m_LayerRecords , 0 , sizeof( m_LayerRecords ) );

        memset( m_flPoseParameters , 0 , sizeof( m_flPoseParameters ) );

        //memset( Matrix , 0 , sizeof( Matrix ) );
    }

    CPlayerRecord&operator=( const CPlayerRecord&src )
    {
        memcpy( this , &src , sizeof( CPlayerRecord ) );
        //memcpy( Matrix , src.Matrix , sizeof( Matrix ) );

        return *this;
    }

    CPlayerRecord&operator=( C_BasePlayer *pPlayer );

    CPlayerRecord( const CPlayerRecord& src )
    {
        *this = src;
    }

    CPlayerRecord( C_BasePlayer *pPlayer )
    {
        *this = pPlayer;
    }

    int m_fFlags;
    Vector m_vecOrigin;
    Angle m_vecAngles;
    Vector m_vecMins;
    Vector m_vecMaxs;
    LayerRecord	m_LayerRecords[ 2 ][ MAX_LAYER_RECORDS ];
    int	m_iSequence;
    float m_flCycle;
    float m_flPoseParameters[ MAXSTUDIOPOSEPARAM ];
    //Matrix3x4 Matrix[ MAXSTUDIOBONES ];
};

enum eMovements
{
    em_forward ,
    em_side ,
    em_up ,
    em_all
};

class CUserRecordCmd
{
public:

    CUserRecordCmd()
    {
        Reset();
    }

    void Reset()
    {
        viewangles.Init();
        aimdirection.Init();
        movements.Init();
        buttons = 0;
        impulse = 0;
        weaponselect = 0;
        weaponsubtype = 0;
        random_seed = 0;
        mousedx = 0;
        mousedy = 0;
        headangles.Init();
        headoffset.Init();
    }

    CUserRecordCmd&operator=( const CUserCmd& src )
    {
        viewangles = src.viewangles;
        movements.x = src.forwardmove;
        movements.y = src.sidemove;
        movements.z = src.upmove;
        buttons = src.buttons;
        impulse = src.impulse;
        weaponselect = src.weaponselect;
        weaponsubtype = src.weaponsubtype;
        random_seed = src.random_seed;
        mousedx = src.mousedx;
        mousedy = src.mousedy;
        headangles = src.headangles;
        headoffset = src.headoffset;

        return *this;
    }

    CUserRecordCmd&operator=( const CUserRecordCmd& src )
    {
        viewangles = src.viewangles;
        movements = src.movements;
        buttons = src.buttons;
        impulse = src.impulse;
        weaponselect = src.weaponselect;
        weaponsubtype = src.weaponsubtype;
        random_seed = src.random_seed;
        mousedx = src.mousedx;
        mousedy = src.mousedy;
        headangles = src.headangles;
        headoffset = src.headoffset;

        return *this;
    }

    CUserRecordCmd( const CUserRecordCmd& src )
    {
        *this = src;
    }

    CUserRecordCmd( const CUserCmd& src )
    {
        *this = src;
    }

    Vector movements , aimdirection , headoffset;
    Angle viewangles , headangles;
    int buttons , random_seed , weaponselect , weaponsubtype;
    byte impulse;
    short mousedx , mousedy;
};

class CMovementRecord
{
public:

    CMovementRecord()
    {
        m_cmd.Reset();
        m_PlayerRecord.Reset();
    }

    CMovementRecord&operator=( const CUserCmd& cmdsrc )
    {
        m_cmd = cmdsrc;

        return *this;
    }

    CMovementRecord&operator=( C_BasePlayer* pPlayer )
    {
        m_PlayerRecord = pPlayer;

        return *this;
    }

    CMovementRecord&operator=( const CMovementRecord& src )
    {
        m_cmd = src.m_cmd;
        m_PlayerRecord = src.m_PlayerRecord;

        return *this;
    }

    CMovementRecord( const CUserCmd& src )
    {
        *this = src;
    }

    CMovementRecord( C_BasePlayer* src )
    {
        *this = src;
    }

    CMovementRecord( const CMovementRecord& src )
    {
        *this = src;
    }

    CMovementRecord( C_BasePlayer* playersrc , const CUserCmd& cmdsrc )
    {
        *this = playersrc;
        *this = cmdsrc;
    }

    CMovementRecord( const CUserCmd& cmdsrc , C_BasePlayer* playersrc )
    {
        *this = playersrc;
        *this = cmdsrc;
    }

    CUserRecordCmd m_cmd;
    CPlayerRecord m_PlayerRecord;
};

//typedef std::vector<CMovementRecord> v_mr;

class CMovementRecorder
{
public:

    CMovementRecorder()
    {
        iOldState = iState = MR_State::MR_Stop;
        /*iSlot =*/ iCurrentTick = 0;
        v_mrs.clear();
        sTmpFileName = sFileName = TEXT( "test" );
        sTmpFileName += TEXT( "tmp" );
        EndZone.Clear();
    }

    void SaveRecording( bool bIsTmp = false );
    void LoadRecording();

    void PreThink( CUserCmd* , C_BasePlayer* pPlayer = GetLocalPlayer() );
    void PostThink( CUserCmd* , C_BasePlayer* pPlayer = GetLocalPlayer() );
    void Think( CUserCmd* , C_BasePlayer* pPlayer = GetLocalPlayer() );
    void Recording( CUserCmd* , C_BasePlayer* pPlayer = GetLocalPlayer() );
    void Playing( CUserCmd* );
    //void Pause( CUserCmd* , C_BasePlayer* pPlayer = GetLocalPlayer() );

    void RunSave( bool bTmp = false );
    void RunLoad();

    bool CanThink( bool StopCheck = true )
    {
        return !bIsLoading && !bIsSaving && ( ( MR_State::MR_Stop == iState ) || !StopCheck );
    }

    size_t GetFinalTick()
    {
        return v_mrs.size();
    }

    static HEX __stdcall SaveRoutine( Pointer );
    static HEX __stdcall LoadRoutine( Pointer );

    std::vector<CMovementRecord> v_mrs;
    stdString  sFileName , sTmpFileName;
    MR_State iState;
    MR_State iOldState;
    size_t iCurrentTick;
    bool bIsSaving;
    bool bIsLoading;
    CZone EndZone;
    //size_t iSlot;
};

extern CMovementRecorder* MovementRecorder;

#endif