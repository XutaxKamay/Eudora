#ifndef OFFSETSMANAGER
#define OFFSETSMANAGER
#pragma once

// https://developer.valvesoftware.com/wiki/Networking_Entities
// Okay, every entities, have something called Networked Variables;
// Those variables are shared between server and client, where the server does the modifications on it, and the client predicting it/using it.
// There is multiples entities (baseentity, baseplayer, baseanim..), and every of them contains tables, wich contains all the networked variables:
// Tables usually start by DT. For example DT_BaseEntity.
// Then inside these tables, you have all the members of the entities (classes), wich all of them, atleast mostly all of them, start by m_ .

enum
{};

struct S_NetVar
{
    S_NetVar( HEX HexOffset = -1 , stdString sName = TEXT( "" ) , stdString sTable = TEXT( "" ) , stdString sClassName = TEXT( "" ) , stdString sPrevNetVar = TEXT( "" ) )
    {
        this->sName = sName;
        this->sTable = sTable;
        this->sClassName = sClassName;
        this->sPrevNetVar = sPrevNetVar;
        this->HexOffset = HexOffset;
    }

    ~S_NetVar()
    {
        sName.clear();
        sTable.clear();
        sClassName.clear();
        sPrevNetVar.clear();
        HexOffset = -1;
    }

    void Clear()
    {
        sName.clear();
        sTable.clear();
        sClassName.clear();
        sPrevNetVar.clear();
        HexOffset = -1;
    }

    HEX HexOffset;
    stdString sName , sTable , sClassName , sPrevNetVar;
};

class NetVarsManager
{
public:

    NetVarsManager()
    {
        bCreateOnceFolder = false;
        sBufferGeneratedHeader.clear();
        sBufferIncludeAllHeaders.clear();
        pOldHookProps.clear();
        iCountChildTables = 0;
    }

    ~NetVarsManager()
    {
        bCreateOnceFolder = false;
        sBufferGeneratedHeader.clear();
        sBufferIncludeAllHeaders.clear();
        iCountChildTables = 0;
    }

    void MakeHeader();
    void MakeHeaderProps( RecvTable* RTable , int iLastOffset = 0 , stdString sPrevNetVar = TEXT( "" ) );
    void MakeHeaderConstructNetVar( stdString sName , int iOffset , stdString sBufferBack = TEXT( "" ) );
    void GenerateStringHeader( const String* sMessage , ... );
    void WriteFileHeader( String* sName );
    void HookProp( String* sNetworkName , String*sTableName , String* sName );

    stdString sBufferGeneratedHeader , sBufferIncludeAllHeaders;
    int iCountChildTables;
    bool bCreateOnceFolder;
    std::vector<Pointer> pOldHookProps;
};

extern NetVarsManager* NetVars;

struct OffsetsManager
{
    OffsetsManager();

    SigScanningFile Scan( std::vector<Byte> Bytes , const String* sName , const String*sDLL )
    {
        SigScanningFile SigScan( ( Pointer ) GetCurrentProcess() , sName );
        SigScan.Scan( Bytes , sDLL );
        SigScan.PrintAllOffsets();
        return SigScan;
    }

    //Pointer pCUserCmdDeconstructor;
    CUserCmd*( __thiscall*CUserCmdOverLoadedEqual )( CUserCmd* );
    Pointer pCUserCmdOverLoadedEqual_ReturnAddress_CreateMove;
    Pointer( __thiscall*C_BaseAnimatingOverlay_GetAnimLayer )( Pointer , int , char );
    Pointer pC_BaseEntity_BaseInterpolate1;
    pByte   pbShouldInterpolate;
    Pointer pInterpolateServerEntities;
    CGlowObjectManager_CSGO* GlowObjectManager;
    void( *UpdateClientSideAnimations )( );
    void( __thiscall*CalcAbsolutePosition )( Pointer );
    void( __thiscall*CalcAbsoluteVelocity )( Pointer );
    int *iModelBoneCounter;
    void( __thiscall*C_BaseEntity_InvalidatePhysicsRecursive )( Pointer , int );
    void( __thiscall*C_BaseAnimating_LockStudioHdr )( Pointer );
    void( __thiscall*C_BaseAnimating_UnLockStudioHdr )( Pointer );
    pByte pbAbsRecomputationEnabled;
    pByte pbAbsQueriesValid;
    pByte pbEnableInvalidateBoneCache;
    bool( __thiscall*C_BaseAnimating_HitboxToWorldTransforms )( Pointer , Matrix3x4** );
    bool( __thiscall*C_BaseAnimating_SetupBones )( Pointer , Matrix3x4* , int , int , float );
    void( __thiscall*C_BaseAnimating_GetBoneTransform )( int , Matrix3x4& );
    void( __thiscall*KeyValues_Constructor )( KeyValues* , const char* );
    KeyValues*( __thiscall*KeyValues_FindKey )( KeyValues* , const char* , bool );
    void( __thiscall*KeyValues_SetString )( KeyValues* , const char* );
    void( __thiscall*KeyValues_LoadFromBuffer )( KeyValues* , const char* , const char* , Pointer , const char* , Pointer );
    void( *SendMove )( );
    void( __thiscall*SendDataGram )( Pointer , bf_write* );
    Pointer pClientState;
    void( __thiscall*RunSimulation )( Pointer , int , CUserCmd* , C_BasePlayer* );
    void( __thiscall*C_BaseEntity_SetAbsVelocity )( Pointer , const Vector& );
    void( __thiscall*RunCommand )( Pointer , C_BasePlayer* , CUserCmd* , IMoveHelper* );
    bool( __thiscall*SendNetMsg )( Pointer , INetMessage& , bool , bool );
    IMoveHelper *MoveHelper;
    C_BasePlayer* pPlayerPrediction;
    pPointer pGameRules;
	Pointer pInput_AdjustPitch;

    void( *Msg )( const char* , ... );
    void( *DMsg )( const String * , int , const String * , ... );

    void( *RandomSeed )( int );
    int( *RandomInt )( int , int );
    float( *RandomFloat )( float , float );
    float( *RandomFloatExp )( float , float , float );
    float( *RandomGaussianFloat )( float , float );
    bool( __thiscall*Buf_WriteString )( Pointer , const char* );
};

extern OffsetsManager* Offsets;

#endif