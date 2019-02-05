#ifndef SDK_FULL
#define SDK_FULL
#pragma once

#include "Lib.hxx"

#pragma warning(disable:4263)
#pragma warning(disable:4264)

#define MULTIPLAYER_BACKUP			150
#define MAX_PLAYERS 64
#define DLL_IMPORT				extern "C" __declspec( dllimport )
#define DBG_INTERFACE	DLL_IMPORT

class C_Weapon;
class ConCommandBase;
class ConCommand;
class ConVar;
class IConVar;
class RecvTable;
class RecvProp;
class CBasePlayer;
class CBaseEntity;
class IClientEntity;
class IClientUnknown;
class IClientNetworkable;
class IClientRenderable;
class CBaseHandle;
class CGameTrace;
class CRecvProxyData;
class IHandleEntity;
class IClientModelRenderable;
class C_BaseEntity;
class C_BasePlayer;
class IClientAlphaProperty;
class bf_read;
class CPhysCollide;
class IVirtualMeshEvent;
class ClientClass;
class ICollideable;
class IMaterial;
class CSentence;
class CAudioSource;
class IMaterialSystem;
class IAchievementMgr;
class CGamestatsData;
class KeyValues;
struct DmxElementUnpackStructure_t;
class CDmxElement;
class Panel;
class SurfaceBase;
class SurfacePlat;
class HScheme;
class Matrix3x4;
class studiohdr_t;
class C_BaseAnimating;
class CStudioHdr;
enum ButtonCode_t;
struct AudioState_t;
enum ClientFrameStage_t;
class CUserCmd;
class Vector;
class Angle;
class Matrix3x4;
class CViewSetup;
struct RenderableInstance_t;
class IMatRenderContext;
struct DrawModelState_t;
struct ModelRenderInfo_t;
class C_BasePlayer;
class bf_write;
class CMoveData;
struct mstudiobbox_t;
struct mstudiohitboxset_t;
class CUtlString;
class CUtlInplaceBuffer;
class CUtlBuffer;
class CUtlBinaryBlock;

#include "Mathematics.hxx"
#include "csgo_GeneratedSDK\SDKGen.hxx"

enum AppSystemTier_t
{
    APP_SYSTEM_TIER0 = 0 ,
    APP_SYSTEM_TIER1 ,
    APP_SYSTEM_TIER2 ,
    APP_SYSTEM_TIER3 ,
    APP_SYSTEM_TIER_OTHER ,
};

enum InitReturnVal_t
{
    INIT_FAILED = 0 ,
    INIT_OK ,
    INIT_LAST_VAL ,
};

typedef void* ( *CreateInterfaceFn )( const char *pName , int *pReturnCode );

struct AppSystemInfo_t
{
    const char *m_pModuleName;
    const char *m_pInterfaceName;
};

class IAppSystem
{
public:
    // Here's where the app systems get to learn about each other
    virtual bool Connect( CreateInterfaceFn factory ) = 0;

    virtual void Disconnect() = 0;

    // Here's where systems can access other interfaces implemented by this object
    // Returns NULL if it doesn't implement the requested interface
    virtual void* QueryInterface( const char* pInterfaceName ) = 0;

    // Init, shutdown
    virtual InitReturnVal_t Init() = 0;

    virtual void Shutdown() = 0;

    // Returns all dependent libraries
    virtual const AppSystemInfo_t* GetDependencies() = 0;

    // Returns the tier
    virtual AppSystemTier_t GetTier() = 0;

    // Reconnect to a particular interface
    virtual void Reconnect( CreateInterfaceFn factory , const char* pInterfaceName ) = 0;

    // Returns whether or not the app system is a singleton
    virtual bool IsSingleton() = 0;
};

typedef unsigned int VPANEL;

//-----------------------------------------------------------------------------
// Methods to invoke the constructor, copy constructor, and destructor
//-----------------------------------------------------------------------------

template <class T>
inline T* Construct( T* pMemory )
{
    return ::new( pMemory ) T;
}

template <class T , typename ARG1>
inline T* Construct( T* pMemory , ARG1 a1 )
{
    return ::new( pMemory ) T( a1 );
}

template <class T , typename ARG1 , typename ARG2>
inline T* Construct( T* pMemory , ARG1 a1 , ARG2 a2 )
{
    return ::new( pMemory ) T( a1 , a2 );
}

template <class T , typename ARG1 , typename ARG2 , typename ARG3>
inline T* Construct( T* pMemory , ARG1 a1 , ARG2 a2 , ARG3 a3 )
{
    return ::new( pMemory ) T( a1 , a2 , a3 );
}

template <class T , typename ARG1 , typename ARG2 , typename ARG3 , typename ARG4>
inline T* Construct( T* pMemory , ARG1 a1 , ARG2 a2 , ARG3 a3 , ARG4 a4 )
{
    return ::new( pMemory ) T( a1 , a2 , a3 , a4 );
}

template <class T , typename ARG1 , typename ARG2 , typename ARG3 , typename ARG4 , typename ARG5>
inline T* Construct( T* pMemory , ARG1 a1 , ARG2 a2 , ARG3 a3 , ARG4 a4 , ARG5 a5 )
{
    return ::new( pMemory ) T( a1 , a2 , a3 , a4 , a5 );
}

template <class T>
inline T* CopyConstruct( T* pMemory , T const& src )
{
    return ::new( pMemory ) T( src );
}

template <class T>
inline void Destruct( T* pMemory )
{
    pMemory->~T();
}

#include "UtlMemory.hxx"
#include "UtlBuffer.hxx"
#include "UtlString.hxx"
#include "UtlVector.hxx"
#include "UtlSymbol.hxx"
#include "CRC32.hxx"
#include "MD5.hxx"
#include "Color.hxx"
#include "ValveMemory.hxx"
#include "GlobalsVars.hxx"
#include "ConVar.hxx"
#include "ClientDLL.hxx"
#include "Entity.hxx"
#include "UserCmd.hxx"
#include "Input.hxx"
#include "Engine.hxx"
#include "Panel.hxx"
#include "RenderView.hxx"
#include "ModelInfo.hxx"
#include "DebugOverlay.hxx"
#include "MaterialSystem.hxx"
#include "ModelRender.hxx"
#include "ViewRender.hxx"
#include "KeyValues.hxx"
#include "MeshBuilder.hxx"
#include "RenderUtils.hxx"
#include "StudioRender.hxx"
#include "Prediction.hxx"
#include "Weapon.hxx"
#include "MDLCache.hxx"
#include "FileSystem.hxx"

#endif