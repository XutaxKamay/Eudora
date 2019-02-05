#include "Includes.hxx"
#include "Lib.hxx"

#ifdef ENVIRONMENT32
#define DllMain DllMain32
#else
#define DllMain DllMain64
#endif

CUSTOM_SECTION_START( .test )

/*

static uHEX32 RoutineStart( DllMain* Main )
{
    //return ( ( uHEX32( __stdcall* )( uHEX , uHEX32 , uHEX ) ) Main->EntryPoint ) ( Main->Module , Main->Reason , Main->Reserved );
    return _CallFunction<uHEX32 , e_stdcall , uHEX , uHEX32 , uHEX >( ( Pointer ) Main->EntryPoint , Main->Module , Main->Reason , Main->Reserved );
}

*/

/*
static uHEX32 __stdcall RoutineStart( sWinMainExe<Pointer> *pWinMainExe )
{
    return _CallFunction<int , e_stdcall , Pointer , Pointer , Pointer , int>
        ( pWinMainExe->pEntryPoint , pWinMainExe->pInstance , pWinMainExe->pPrevInstance , pWinMainExe->pCmdLine , pWinMainExe->nCmdShow );
}
*/

static uHEX32 __stdcall RoutineStart( s_InitStaticTls<uHEX> *pInitStaticTls )
{
    return _CallFunction<NTSTATUS , e_thiscall , Pointer>( reinterpret_cast< Pointer >( pInitStaticTls->pLdrpHandleTlsData ) , &pInitStaticTls->EntryBase );
}

/*
static uHEX32 RoutineStart( N_Process::sLoadLib* pRoutine )
{
    pRoutine->pReturnAddress = ( uHEX64 ) ( uHEX ) _CallFunction<Pointer , e_stdcall , Pointer>( ( Pointer ) pRoutine->pAddress , ( Pointer ) pRoutine->pDLLPath );

    if ( pRoutine->pReturnAddress != 0 )
        return 1;
    else
        return 0;
}
*/

/*

#ifdef ENVIRONMENT32
static uHEX32 RoutineStart( uHEX64* p )
{
    *p = *( uHEX32 *) __readfsdword( 0x2C );

    return 1;
}
#else
static uHEX32 RoutineStart( uHEX64* p )
{
    *p = *( uHEX64 * ) __readgsqword( 0x58 );

    return 1;
}
#endif

*/

CUSTOM_SECTION_END()

int WINAPI wWinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , PWSTR pCmdLine , int nCmdShow )
{
    N_Console::Open();

    N_Console::Print( TEXT( "0x%p\n" ) , RoutineStart );

    N_Console::Pause();

    return 0;
}