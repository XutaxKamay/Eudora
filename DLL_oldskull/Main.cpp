#include "Includes.hxx"
#include "Lib.hxx"

void Routine( Pointer pModule )
{
    N_Process::Process CurProcess( GetCurrentProcess() );

    CurProcess.SetAllAccess();

    N_Console::Open();

    N_Console::Print<FOREGROUND_CYAN>( TEXT( "bruteforcing...\n" ) );

    auto pWindowHandle1 = *_GetModule<HWND*>( TEXT( "oldskull.exe" ) , 0xC034 );
    auto pWindowHandle2 = *_GetModule<HWND*>( TEXT( "oldskull.exe" ) , 0xC038 );
    auto pWindowHandle3 = *_GetModule<HWND*>( TEXT( "oldskull.exe" ) , 0xC03C );
    auto pWindowHandle4 = *_GetModule<HWND*>( TEXT( "oldskull.exe" ) , 0xC040 );
    auto pWindowHandleOutput = *_GetModule<HWND*>( TEXT( "oldskull.exe" ) , 0xC048 );
    auto pWindowHandleFinalFlag = *_GetModule<HWND*>( TEXT( "oldskull.exe" ) , 0xC044 );
    auto pRunCheckCode = _GetModule<Pointer>( TEXT( "oldskull.exe" ) , 0x17D5 );

    uint16_t iHexCode1 = 0x0 , iHexCode2 = 0x0 , iHexCode3 = 0x0 , iHexCode4 = 0x0;
    char bufIn1[ 32 ] , bufIn2[ 32 ] , bufIn3[ 32 ] , bufIn4[ 32 ] , bufOut[ 256 ];

    sprintf_s( bufIn2 , "%X" , iHexCode2 );
    sprintf_s( bufIn3 , "%X" , iHexCode3 );
    sprintf_s( bufIn4 , "%X" , iHexCode4 );
    SetWindowTextA( pWindowHandle2 , bufIn2 );
    SetWindowTextA( pWindowHandle3 , bufIn3 );
    SetWindowTextA( pWindowHandle4 , bufIn4 );

    //in Temp//oldskull_checker.exe in the entrypoint you have a char array xored.
    //: DrgnS{WaaayTooEZ!!1}

    SetWindowTextA( pWindowHandleFinalFlag , "DrgnS{WaaayTooEZ!!1}" );

    while ( true )
    {
        sprintf_s( bufIn1 , "%X" , iHexCode1 );
        SetWindowTextA( pWindowHandle1 , bufIn1 );

        _CallFunction( pRunCheckCode );

        GetWindowTextA( pWindowHandleOutput , bufOut , sizeof( bufOut ) );

        if ( strcmp( bufOut , "Wrong Code 1." ) )
        {
            N_Console::Print<FOREGROUND_GREEN>( TEXT( "Found: 0x%X\n" ) , iHexCode1 );
            break;
        }

        iHexCode1++;
    }

    while ( true )
    {
        sprintf_s( bufIn2 , "%X" , iHexCode2 );
        SetWindowTextA( pWindowHandle2 , bufIn2 );

        _CallFunction( pRunCheckCode );

        GetWindowTextA( pWindowHandleOutput , bufOut , sizeof( bufOut ) );

        if ( strcmp( bufOut , "Wrong Code 2." ) )
        {
            N_Console::Print<FOREGROUND_GREEN>( TEXT( "Found: 0x%X\n" ) , iHexCode2 );
            break;
        }

        iHexCode2++;
    }

    while ( true )
    {
        sprintf_s( bufIn3 , "%X" , iHexCode3 );
        SetWindowTextA( pWindowHandle3 , bufIn3 );

        _CallFunction( pRunCheckCode );

        GetWindowTextA( pWindowHandleOutput , bufOut , sizeof( bufOut ) );

        if ( strcmp( bufOut , "Wrong Code 3." ) )
        {
            N_Console::Print<FOREGROUND_GREEN>( TEXT( "Found: 0x%X\n" ) , iHexCode3 );
            break;
        }

        iHexCode3++;
    }

    while ( true )
    {
        sprintf_s( bufIn4 , "%X" , iHexCode4 );
        SetWindowTextA( pWindowHandle4 , bufIn4 );

        _CallFunction( pRunCheckCode );

        GetWindowTextA( pWindowHandleOutput , bufOut , sizeof( bufOut ) );

        if ( strcmp( bufOut , "Wrong Code 4." ) )
        {
            N_Console::Print<FOREGROUND_GREEN>( TEXT( "Found: 0x%X\n" ) , iHexCode4 );
            break;
        }

        iHexCode4++;
    }

    N_Console::Print<FOREGROUND_GREEN>( TEXT( "Code1: 0x%X Code2: 0x%X Code3: 0x%X Code4: 0x%X\n" ) , iHexCode1 , iHexCode2 , iHexCode3 , iHexCode4 );
    
}

uHEX32 WINAPI DllMain(
    Pointer pModule ,  // Address of the current module
    HEX HexReason ,     // Obvious
    Pointer pReserved )  // Something that is useless. Wich we can use for a manual mapper for example.
{
    DisableThreadLibraryCalls( ( HMODULE ) pModule );

    if ( HexReason == DLL_PROCESS_ATTACH )
    {
        CreateThread( 0 , 0 , ( LPTHREAD_START_ROUTINE ) Routine , pModule , 0 , 0 );
        N_Console::Print( TEXT( "Quitting\n" ) );
    }

    return 1;
}