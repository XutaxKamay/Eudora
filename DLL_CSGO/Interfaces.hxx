#ifndef INTERFACES
#define INTERFACES
#pragma once

class ICvar;
class IBaseClientDLL;
class IClientEntityList;
class CInput;
class CGlobalVars;
class IEngineTrace;

// Interfaces in valve games, are used to share dynamically the classes, between DLLs. So each DLLs can modify interfaces and their members.
// Warning: you can't get all interfaces that the game created with only one DLL, so you need to know the DLL name wich has created the interface.
// Each interfaces is linked to a string that is used to find interfaces for example, VEngineCvar.
// Each interfaces have a number at the end of the string, for example for VEngineCvar001, the last number is the version of the interface.
// Every DLL of valve, have a function exported called CreateInterface (it's used for getting interfaces, but also creating one, we could even create ours!)
// Valve simply pass the already definied string for getting the interface, but here, we will brutefacing it!
template<typename T = Pointer> T GetInterface( const char* sInterfaceName , const char* sDll , bool bAdd = false )
{
    char sBuffer[ 0xFF ];

    CreateInterfaceFn CreateInterface = ( CreateInterfaceFn ) ( Pointer ) ( GetProcAddress( _GetModule<HMODULE>( AutoConvertS( sDll ) ) , AutoConvertC( TEXT( "CreateInterface" ) ) ) );

    if ( CreateInterface == nullptr )
    {
        CONSOLEColorDEBUG( FOREGROUND_RED , TEXT( "[CreateInterface] Couldn't get proc adress from dll: %s\n" ) , AutoConvertS( sDll ) );
        return nullptr;
    }

    if ( CreateInterface != nullptr )
    {
        if ( bAdd )
        {
            int iIndex = 0;
            do
            {
                if ( iIndex <= 10 )
                {
                    sprintf_s( sBuffer , sizeof( sBuffer ) , AutoConvertC( TEXT( "%s00%i" ) ) , sInterfaceName , iIndex );
                }

                if ( iIndex >= 10 )
                {
                    sprintf_s( sBuffer , sizeof( sBuffer ) , AutoConvertC( TEXT( "%s0%i" ) ) , sInterfaceName , iIndex );
                }

                if ( iIndex >= 100 )
                {
                    sprintf_s( sBuffer , sizeof( sBuffer ) , AutoConvertC( TEXT( "%s%i" ) ) , sInterfaceName , iIndex );
                }

                if ( CreateInterface( sBuffer , 0 ) )
                {
                    break;
                }

                iIndex++;
            }
            while ( iIndex <= 0xFF );
        }
        else
        {
            int iIndex = 0xFF;
            do
            {
                if ( iIndex <= 10 )
                {
                    sprintf_s( sBuffer , sizeof( sBuffer ) , AutoConvertC( TEXT( "%s00%i" ) ) , sInterfaceName , iIndex );
                }

                if ( iIndex >= 10 )
                {
                    sprintf_s( sBuffer , sizeof( sBuffer ) , AutoConvertC( TEXT( "%s0%i" ) ) , sInterfaceName , iIndex );
                }

                if ( iIndex >= 100 )
                {
                    sprintf_s( sBuffer , sizeof( sBuffer ) , AutoConvertC( TEXT( "%s%i" ) ) , sInterfaceName , iIndex );
                }

                if ( CreateInterface( sBuffer , 0 ) )
                {
                    break;
                }

                iIndex--;
            }
            while ( iIndex >= 0 );
        }

        T HexAddress = ( T ) ( CreateInterface( sBuffer , 0 ) );

        if ( HexAddress != 0 )
            return HexAddress;
        else
            return 0;
    }

    return 0;
}

// Temp class for interfaces.
// Class template will be for wich class is used for the interface.
// Mostly every interfaces have virtual functions, wich make our lifes easier to get the addresses of functions.
template<typename Class> class Interface
{
public:

    Interface()
    {
        pAddress = pClass = nullptr;
        pVTable = nullptr;
        sName.clear(); sDLL.clear();
    }

    Interface( bool bProcAddress , int iNumCast , const char* sName , const String* sDLL , bool bAdd = false )
    {
        pAddress = nullptr;

        if ( bProcAddress )
            pAddress = GetProcAddress( _GetModule<HMODULE>( sDLL ) , sName );
        else
            pAddress = GetInterface( sName , AutoConvertC( sDLL ) , bAdd );

        for ( int i = 0; i < iNumCast; i++ )
            pAddress = *( pPointer ) pAddress;

        pClass = ( Class* ) pAddress;
        this->pAddress = pAddress;
        this->sName = sName;
        this->sDLL = sDLL;

        if ( pAddress != nullptr )
        {
            pVTable = _VTable( pAddress );
            CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "[Interface] %s initialized (0x%p - ModuleBase: 0x%p).\n" ) , sName , pAddress , _GetModule( sDLL ) );
        }
        else
        {
            CONSOLEColorDEBUG( FOREGROUND_RED , TEXT( "[Interface] %s couldn't initialize (0x%p - ModuleBase: 0x%p).\n" ) , sName , pAddress , _GetModule( sDLL ) );
            delete this;
        }
    }

    Interface( Pointer pAddress , const char* sName , const String* sDLL = TEXT( "" ) )
    {
        if ( pAddress != nullptr )
        {
            pClass = ( Class* ) pAddress;
            this->pAddress = pAddress;
            this->sName = sName;
            this->sDLL = sDLL;
            pVTable = _VTable( pAddress );
            CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "[Interface] %s initialized (0x%p - ModuleBase: 0x%p).\n" ) , sName , pAddress , _GetModule( sDLL ) );
        }
        else
        {
            CONSOLEColorDEBUG( FOREGROUND_RED , TEXT( "[Interface] %s couldn't initialize (0x%p - ModuleBase: 0x%p).\n" ) , sName , pAddress , _GetModule( sDLL ) );
        }
    }

    ~Interface()
    {
        CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "[Interface] %s uninitializing (0x%p - ModuleBase: 0x%p).\n" ) , sName.c_str() , pAddress , _GetModule( sDLL.c_str() ) );
        pAddress = pClass = nullptr;
        pVTable = nullptr;
        sName.clear(); sDLL.clear();
    }

    template<typename T = Pointer> __forceinline T VirtualFunction( int iIndex )
    {
        return ( T ) pVTable[ iIndex ];
    }

    template< typename RetType = void , typename ... vArgs > __forceinline RetType CallVirtualFunction( int iIndex , vArgs ... pArgs )
    {
        return _CallVirtualFunction< RetType , Pointer , vArgs ... >( pAddress , iIndex , pArgs ... );
    }

    template<typename T = pPointer> __forceinline T GetVTable()
    {
        return ( T ) pVTable;
    }

    template<typename _Class = Class> _Class* operator->()
    {
        return ( _Class* ) pClass;
    }

    Class *pClass;
    Pointer pAddress;
    std::string sName;
    stdString sDLL;
    pPointer pVTable;
};

extern Interface<ICvar> Cvar;
extern Interface<IBaseClientDLL> BaseClient;
extern Interface<IMemAlloc> MemAllocValve;
extern Interface<IClientEntityList> ClientEntityList;
extern Interface<CInput> Input;
extern Interface<CGlobalVars> Globals;
extern Interface<IEngineTrace> EngineTrace;
extern Interface<IVEngineClient> EngineClient;
extern Interface<IPanel> Panel;
extern Interface<IVRenderView> RenderView;
extern Interface<IVModelInfo> ModelInfo;
extern Interface<IVDebugOverlay> DebugOverlay;
extern Interface<IMaterialSystem> MaterialSystem;
extern Interface<IVModelRender> ModelRender;
extern Interface<IViewRender> ViewRender;
extern Interface<IClientMode> ClientMode;
extern Interface<IKeyValuesSystem> KeyValuesSystem;
extern Interface<IStudioRender> StudioRender;
extern Interface<IPhysicsSurfaceProps> PhysicsSurfaceProps;
extern Interface<CPrediction> Prediction;
extern Interface<CGameMovement> GameMovement;
extern Interface<IMDLCache> MDLCache;
extern Interface<IBaseFileSystem> FileSystem;
extern Interface<ISurface> Surface;

#endif