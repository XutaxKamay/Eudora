#include "Includes.hxx"
#include "Lib.hxx"
#include "Hooking.hxx"

#ifndef _DEBUG
#pragma comment(lib,"..\\x64\\Release\\Detour.lib")
#else
#pragma comment(lib,"..\\x64\\Debug\\Detour.lib")
#endif

N_Hook::DetourFunction *D_Reputation;
N_Hook::DetourFunction *D_Nitrous;

N_Hook::DetourFunction *D_send;
N_Hook::DetourFunction *D_recv;
N_Hook::DetourFunction *D_sendto;
N_Hook::DetourFunction *D_ReadFile;

N_Hook::DetourFunction *D_U;
N_Hook::DetourFunction *D_U1;
N_Hook::DetourFunction *D_U2;
N_Hook::DetourFunction *D_U3;

bool sending_rep = false;

#define BUFSIZE 512
#pragma warning(disable:4100)

#define OFFSET_SCRIPTCONTEXT	0x140262AA0
#define OFFSET_EXECUTESCRIPT		0x140263110
#define OFFSET_EXECUTESTRING 0x140263250

typedef bool( __thiscall* tScriptContext_ExecuteScriptFile )( PVOID lpThis , const char* pszFileName , bool mustExist , PVOID pFileSystem , PVOID msgOut );
tScriptContext_ExecuteScriptFile lpExecuteScript = ( tScriptContext_ExecuteScriptFile ) ( OFFSET_EXECUTESCRIPT );
typedef bool( __thiscall* tScriptContext_ExecuteString )( PVOID lpThis , const char* pszCommand , int size , const char* errormsg , const char* , bool );
tScriptContext_ExecuteString lpExecuteString = ( tScriptContext_ExecuteString ) ( OFFSET_EXECUTESTRING );

namespace fb
{
    class ScriptContext
    {
    public:
        PVOID vt;

        static ScriptContext* GetInstance()
        {
            return ( ScriptContext* ) _CallFunction<UINT_PTR>( ( Pointer ) OFFSET_SCRIPTCONTEXT );
        }
    };
}

void new_exit( int nop )
{
    N_Console::Print( TEXT( "%p\n" ) , _ReturnAddress() );
}

BOOL __stdcall new_TerminateProcess( HANDLE pProcess , UINT uCode )
{
    N_Console::Print( TEXT( "%p\n" ) , _ReturnAddress() );
    return true;
}

BOOL __stdcall new_ExitProcess( UINT uCode )
{
    N_Console::Print( TEXT( "%p\n" ) , _ReturnAddress() );
    return true;
}

const String* GetFileNameFromHandle( HANDLE hFile )
{
    BOOL bSuccess = FALSE;
    TCHAR pszFilename[ MAX_PATH + 1 ];
    HANDLE hFileMap;

    // Get the file size.
    DWORD dwFileSizeHi = 0;
    DWORD dwFileSizeLo = GetFileSize( hFile , &dwFileSizeHi );

    if ( dwFileSizeLo == 0 && dwFileSizeHi == 0 )
    {
        return FALSE;
    }

    // Create a file mapping object.
    hFileMap = CreateFileMapping( hFile ,
                                  NULL ,
                                  PAGE_READONLY ,
                                  0 ,
                                  1 ,
                                  NULL );

    if ( hFileMap )
    {
        // Create a file mapping to get the file name.
        void* pMem = MapViewOfFile( hFileMap , FILE_MAP_READ , 0 , 0 , 1 );

        if ( pMem )
        {
            if ( GetMappedFileName( GetCurrentProcess() ,
                 pMem ,
                 pszFilename ,
                 MAX_PATH ) )
            {
                // Translate path with device name to drive letters.
                TCHAR szTemp[ BUFSIZE ];
                szTemp[ 0 ] = '\0';

                if ( GetLogicalDriveStrings( BUFSIZE - 1 , szTemp ) )
                {
                    TCHAR szName[ MAX_PATH ];
                    TCHAR szDrive[ 3 ] = TEXT( " :" );
                    BOOL bFound = FALSE;
                    TCHAR* p = szTemp;

                    do
                    {
                        // Copy the drive letter to the template string
                        *szDrive = *p;

                        // Look up each device name
                        if ( QueryDosDevice( szDrive , szName , MAX_PATH ) )
                        {
                            size_t uNameLen = StrLen( szName );

                            if ( uNameLen < MAX_PATH )
                            {
                                bFound = StrStrI( pszFilename , szName ) == 0
                                    && *( pszFilename + uNameLen ) == TEXT( '\\' );

                                if ( bFound )
                                {
                                    // Reconstruct pszFilename using szTempFile
                                    // Replace device path with DOS path
                                    TCHAR szTempFile[ MAX_PATH ];
                                    StringCchPrintf( szTempFile ,
                                                     MAX_PATH ,
                                                     TEXT( "%s%s" ) ,
                                                     szDrive ,
                                                     pszFilename + uNameLen );
                                    StringCchCopyN( pszFilename , MAX_PATH + 1 , szTempFile , StrLen( szTempFile ) );
                                }
                            }
                        }

                        // Go to the next NULL character.
                        while ( *p++ );
                    } while ( !bFound && *p ); // end of string
                }
            }
            bSuccess = TRUE;
            UnmapViewOfFile( pMem );
        }

        CloseHandle( hFileMap );
    }

    return stdString( pszFilename ).c_str();
}

BOOL WINAPI new_ReadFile(
    _In_        HANDLE       hFile ,
    _Out_       LPVOID       lpBuffer ,
    _In_        DWORD        nNumberOfBytesToRead ,
    _Out_opt_   LPDWORD      lpNumberOfBytesRead ,
    _Inout_opt_ LPOVERLAPPED lpOverlapped
)
{
    String pFilePath[ MAX_PATH + 1 ] = TEXT( "" );

    GetFinalPathNameByHandle( hFile , pFilePath , MAX_PATH , 0 );

    stdString spFilePath = pFilePath;

    size_t s_PosFound = spFilePath.find( TEXT( "initfs_Win32" ) );

    if ( s_PosFound != stdString::npos )
    {
        spFilePath[ s_PosFound ] = TEXT( '2' );
        N_Console::Print( TEXT( "Found: %s %p\n" ) , spFilePath.c_str() , ( DWORD64 ) _ReturnAddress() );
        CloseHandle( hFile );
        hFile = ( HANDLE ) CreateFile( spFilePath.c_str() , GENERIC_ALL , FILE_SHARE_READ | FILE_SHARE_WRITE
                                       | FILE_SHARE_DELETE , nullptr , OPEN_ALWAYS , FILE_ATTRIBUTE_NORMAL , 0 );
        DWORD Size = GetFileSize( hFile , 0 );
        _CallFunction<bool , e_stdcall , HANDLE , LPVOID , DWORD , LPDWORD , LPOVERLAPPED>( D_ReadFile->pOld , hFile , lpBuffer , Size , lpNumberOfBytesRead , lpOverlapped );

        return true;
    }
    else
        return _CallFunction<bool , e_stdcall , HANDLE , LPVOID , DWORD , LPDWORD , LPOVERLAPPED>( D_ReadFile->pOld , hFile , lpBuffer , nNumberOfBytesToRead , lpNumberOfBytesRead , lpOverlapped );
}

int __stdcall new_sendto( SOCKET s , const char * buf , int len , int flags , const struct sockaddr *to , int tolen )
{
    int iRet = len;

    iRet = _CallFunction<int , e_stdcall , SOCKET , const char* , int , int , const struct sockaddr* , int>( D_sendto->pOld , s , buf , len , flags , to , tolen );

    N_Console::Print<FOREGROUND_BLUE>( TEXT( "sendto-------------------------------------------------STARTING PACKET-------------------------------------------------\n" ) );
    N_Console::Print<FOREGROUND_BLUE>( TEXT( "addr:%p ret:%i len: %i flags: %i ->\n" ) , _ReturnAddress() , iRet , len , flags );
    for ( int i = 0; i < len; i++ )
    {
        N_Console::Print<FOREGROUND_BLUE>( TEXT( "%c" ) , buf[ i ] );
    }
    N_Console::NewLine();
    N_Console::PrintBytes( ( Bytes ) buf , len );
    N_Console::Print<FOREGROUND_BLUE>( TEXT( "sendto-------------------------------------------------ENDING PACKET-------------------------------------------------\n" ) );

    return iRet;
}

int __stdcall new_send( SOCKET s , const char * buf , int len , int flags )
{
    int iRet = len;

    if ( !GetAsyncKeyState( VK_F3 ) )
    {
        iRet = _CallFunction<int , e_stdcall , SOCKET , const char* , int , int>( D_send->pOld , s , buf , len , flags );
    }

/*if ( GetAsyncKeyState( VK_F1 ) )
{
    for ( int i = 1; i < 10; i++ )
    {
        iRet = !GetAsyncKeyState( VK_F3 ) ? ( _CallFunction<int , SOCKET , const char* , int , int>( e_thiscall , D_send->pOld , s , buf , len , flags ) )
            : ( _CallFunction<int , SOCKET , const char* , int , int>( e_thiscall , D_send->pOld , s , ( const char* ) pTemp , len , flags ) );
        Sleep( 100 );
    }
}*/

    N_Console::Print<FOREGROUND_BLUE>( TEXT( "send-------------------------------------------------STARTING PACKET-------------------------------------------------\n" ) );
    N_Console::Print<FOREGROUND_BLUE>( TEXT( "addr:%p ret:%i len: %i flags: %i ->\n" ) , _ReturnAddress() , iRet , len , flags );
    for ( int i = 0; i < len; i++ )
    {
        N_Console::Print<FOREGROUND_BLUE>( TEXT( "%lc" ) , buf[ i ] );
    }
    N_Console::NewLine();
    N_Console::PrintBytes( ( Bytes ) buf , len );
    N_Console::Print<FOREGROUND_BLUE>( TEXT( "send-------------------------------------------------ENDING PACKET-------------------------------------------------\n" ) );

    return iRet;
}

int __stdcall new_recv( SOCKET s , char * buf , int len , int flags )
{
    Pointer pTemp = Alloc( len );
    memcpy( pTemp , buf , len );

    int iRet = len;
    if ( !GetAsyncKeyState( VK_F3 ) )
        iRet = _CallFunction<int , e_stdcall , SOCKET , char* , int , int>( D_recv->pOld , s , buf , len , flags );

    N_Console::Print<FOREGROUND_BLUE>( TEXT( "recv-------------------------------------------------STARTING PACKET-------------------------------------------------\n" ) );
    N_Console::Print<FOREGROUND_BLUE>( TEXT( "addr:%p ret:%i len: %i flags: %i ->\n" ) , _ReturnAddress() , iRet , len , flags );
    for ( int i = 0; i < len; i++ )
    {
        N_Console::Print<FOREGROUND_BLUE>( TEXT( "%lc" ) , buf[ i ] );
    }
    N_Console::NewLine();
    N_Console::PrintBytes( ( Bytes ) buf , len );
    N_Console::Print<FOREGROUND_BLUE>( TEXT( "recv-------------------------------------------------ENDING PACKET-------------------------------------------------\n" ) );

    FreeAlloc( pTemp );

    return iRet;
}

__int64 __fastcall new_Nitrous( __int64 a1 , float a2 )
{
    *( float * ) ( a1 + 544 ) = FLT_MAX;

    __int64 iRet = _CallFunction<__int64 , e_fastcall , __int64 , float>( D_Nitrous->pOld , a1 , a2 );

    return iRet;
}

__int64 rep_slot1 = 0 , rep_slot2 = 0 , rep_slot3 = 0;
void __fastcall new_Reputation( __int64 a1 , int a2 , __int64 a3 , __int64 a4 )
{
    rep_slot1 = a1;
    rep_slot2 = a3;
    rep_slot3 = a4;
    //N_Console::Print( TEXT( "%i %i %i %i\n" ) , a1 , a2 , a3 , a4 );
    _CallFunction<void , e_fastcall , __int64 , int , __int64 , __int64>( D_Reputation->pOld , a1 , a2 , a3 , a4 );
}

bool bClosing = false;
static bool bPrintOnce = false;

Pointer __stdcall RepThread()
{
    while ( true )
    {

        sending_rep = true;
        //if ( rep_slot1 != 0 && rep_slot2 != 0 && rep_slot3 != 0 )
            //_CallFunction<void , e_fastcall , __int64 , int , __int64 , __int64 >( D_Reputation->pOld , rep_slot1 , 1070000 , rep_slot2 , rep_slot3 );

        if ( rep_slot1 != 0 && rep_slot2 != 0 && rep_slot3 != 0 )
        {
            _CallFunction<void , e_fastcall , __int64 , int , __int64 , __int64 >( D_Reputation->pOld , rep_slot1 , 1070000 , rep_slot2 , rep_slot3 );

            /*_asm
            {
                mov r9 , rep_slot3
                mov r8 , rep_slot2
                mov edx , iAdd
                mov rcx , rep_slot1
                call pRep
            }*/
        }

       // if ( ia1 != 0 )
         //   _CallFunction< __int64 , __int64 >( e_fastcall , D_U->pOld , ia1 );

        //N_Console::Print<FOREGROUND_GREEN>( TEXT( "Added reputation...\n" ) );

        Sleep( 10000 );


        if ( bClosing )
        {
            break;
        }
    }

    return nullptr;
}

struct S_Routine
{
    S_Routine( Pointer pModule , bool bManualMapped = false )
    {
        this->pModule = pModule;
        this->bManualMapped = bManualMapped;
    }

    ~S_Routine()
    {
        pModule = nullptr;
        bManualMapped = false;
    }

    Pointer pModule;
    bool bManualMapped;
};

Pointer _RoutineHack( S_Routine *SRoutine )
{
    // _int64 *__fastcall sub_14027B010(_QWORD *a1, _BYTE *a2, char a3)
   // _CallFunction<__int64* , __int64* , const char* , bool>( e_fastcall , ( Pointer ) 0x14027B010 , ( __int64* ) fb::ScriptContext::GetInstance() , "allowCommandlineSettings true" , 1 );
   // _CallFunction<__int64* , __int64* , const char* , bool>( e_fastcall , ( Pointer ) 0x14027B010 , ( __int64* ) fb::ScriptContext::GetInstance() , "Render.DebugInfoEnable true" , 1 );

    /*bool bLoaded = lpExecuteScript( fb::ScriptContext::GetInstance() , "Scripts/Game/Startup.lua" , true , NULL , NULL );
    if ( bLoaded )
    {
        N_Console::Print( TEXT( "Loaded1!\n" ) );
    }*/

   /* bLoaded = lpExecuteScript( fb::ScriptContext::GetInstance() , "Scripts/Game/DebugSettings.lua" , true , NULL , NULL );
    if ( bLoaded )
    {
        N_Console::Print( TEXT( "Loaded1!\n" ) );
    }
    bLoaded = lpExecuteScript( fb::ScriptContext::GetInstance() , "Scripts/Game/Configure.lua" , true , NULL , NULL );
    if ( bLoaded )
    {
        N_Console::Print( TEXT( "Loaded2!\n" ) );
    }
    bLoaded = lpExecuteScript( fb::ScriptContext::GetInstance() , "Scripts/Packages/Frost/Core.lua" , true , NULL , NULL );
    if ( bLoaded )
    {
        N_Console::Print( TEXT( "Loaded3!\n" ) );
    }
    bLoaded = lpExecuteScript( fb::ScriptContext::GetInstance() , "Scripts/Packages/Frost/Logging.lua" , true , NULL , NULL );
    if ( bLoaded )
    {
        N_Console::Print( TEXT( "Loaded4!\n" ) );
    }
    bLoaded = lpExecuteScript( fb::ScriptContext::GetInstance() , "user/profile/settings/overrideAutodetect.lua" , true , NULL , NULL );

    if ( bLoaded )
    {
        N_Console::Print( TEXT( "Loaded5!\n" ) );
    }*/

    N_Hook::Init();

    Pointer pNitrousFunction = ( Pointer ) FindPattern( "NeedForSpeedPayback.exe" , "48 83 EC 58 48 8B 81 E0 01 00 00 48 89 5C 24 60" );

    PDETOUR_FUNCTION( D_Nitrous , new_Nitrous , pNitrousFunction );

    Pointer pRepFunction = ( Pointer ) FindPattern( "NeedForSpeedPayback.exe" , "85 D2 0F 8E 2A 02 00 00 4C 89 44 24 18 89 54 24" );

    PDETOUR_FUNCTION( D_Reputation , new_Reputation , pRepFunction );

    //PDETOUR_FUNCTION( D_send , new_send , GetProcAddress( _GetModule<HMODULE>( TEXT( "WS2_32.dll" ) ) , "send" ) );

    //PDETOUR_FUNCTION( D_ReadFile , new_ReadFile , GetProcAddress( _GetModule<HMODULE>( TEXT( "KernelBase.dll" ) ) , "ReadFile" ) );

   // PDETOUR_FUNCTION( D_sendto , new_sendto , GetProcAddress( _GetModule<HMODULE>( TEXT( "WS2_32.dll" ) ) , "sendto" ) );

   // PDETOUR_FUNCTION( D_recv , new_recv , GetProcAddress( _GetModule<HMODULE>( TEXT( "WS2_32.dll" ) ) , "recv" ) );

    //sub_14026AC80
    //PDETOUR_FUNCTION( D_U , new_exit , GetProcAddress( _GetModule<HMODULE>( TEXT( "ucrtbase" ) ) , "exit" ) );
    //PDETOUR_FUNCTION( D_U1 , new_TerminateProcess , GetProcAddress( _GetModule<HMODULE>( TEXT( "KERNEL32" ) ) , "TerminateProcess" ) );
    //PDETOUR_FUNCTION( D_U2 , new_ExitProcess , GetProcAddress( _GetModule<HMODULE>( TEXT( "KERNEL32" ) ) , "ExitProcess" ) );

    Pointer pUnlock = ( Pointer ) 0x141315D13;

    DWORD dwOld;
    VirtualProtect( pUnlock , 6 , PAGE_EXECUTE_READWRITE , &dwOld );
    for(int i = 0; i < 6; i++ )
    ( ( Byte* ) pUnlock )[ i ] = 0x90;
    VirtualProtect( pUnlock , 6 , dwOld , &dwOld );

    N_Hook::ApplyHooks();

    HANDLE hThread = CreateThread( 0 , 0 , ( LPTHREAD_START_ROUTINE ) ( Pointer ) RepThread , nullptr , 0 , 0 );

    bool bExitThread = false;

    while ( !bExitThread )
    {
        if ( GetAsyncKeyState( VK_INSERT ) )
        {
            bClosing = true;
            CONSOLEDEBUG( TEXT( "EXITING Thread\n" ) );
            WaitForSingleObject( hThread , INFINITE );
           // D_U->UnHook();
            D_Nitrous->UnHook();
            D_Reputation->UnHook();
            //D_send->UnHook();
            //D_U->UnHook();
            //D_U1->UnHook();
            //D_U2->UnHook();
           // D_sendto->UnHook();
           // D_recv->UnHook();
            N_Hook::UnInit();
            N_Console::Close();
            N_Console::WriteLog();
            bExitThread = true;
        }

        Sleep( 100 );
    }

    if ( SRoutine->bManualMapped )
        return ( Pointer ) 1;
    else
    {
        FreeLibraryAndExitThread( ( HMODULE ) SRoutine->pModule , 0 );
        return ( Pointer ) 0;
    }
}

// Entry point of the dll : https://msdn.microsoft.com/fr-fr/library/windows/desktop/ms682596(v=vs.85).aspx

Pointer WINAPI DllMain(
    Pointer pModule ,  // Address of the current module
    HEX HexReason ,     // Obvious
    Pointer pReserved )  // Something that is useless. Wich we can use for a manual mapper for example.
{
    //DisableThreadLibraryCalls( ( HMODULE ) pModule );
    // If the dll is attached to the processus we can start doing things.
    // We must create a thread inside the dll because the loader of the dll would be stuck in some cases, it would be waiting for the thread finishing so we avoid that.
    HANDLE hThread = nullptr;

    S_Routine *SRoutine = new S_Routine( pModule , pReserved );

    if ( HexReason == DLL_PROCESS_ATTACH )
    {
        N_Console::Open();

        if ( !SRoutine->bManualMapped )
            hThread = CreateThread( nullptr , 0 , ( LPTHREAD_START_ROUTINE ) ( Pointer ) _RoutineHack , ( Pointer ) SRoutine , 0 , nullptr );
        else
            return  _RoutineHack( SRoutine );

        return nullptr;
    }

    return nullptr;
}

/* TODO: mac entry point here */