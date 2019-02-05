#include "Includes.hxx"
#include "Lib.hxx"

constexpr String* globalString = TEXT( "\\\\?\\globalroot" );

N_Process::Process::Process( Pointer _pProcess )
{
    pProcess = _pProcess;

    if ( IsWow64Process( pProcess , ( PBOOL ) &bIsWow64 ) )
    {
    }

    HexProcessID = ( HEX ) GetProcessId( pProcess );

    String wBuf[ UNICODE_STRING_MAX_CHARS ];
    GetModuleBaseName( pProcess , 0 , wBuf , sizeof( wBuf ) );

    sName = stdString( wBuf );

    GetInformations();

    String sProcessPathTmp[ MAX_PATH ];
    if ( GetMappedFileName( pProcess , nullptr , sProcessPathTmp , MAX_PATH ) )
    {
        sProcessPath = globalString + stdString( sProcessPathTmp );
    }

    CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "[%s->Initialized]\n" ) , sName.c_str() );
}

N_Process::Process::Process( HEX _HexProcessID )
{
    //Open the process to get the handle of it, with maximum rights.

    pProcess = OpenProcess( PROCESS_ALL_ACCESS , false , ( DWORD ) _HexProcessID );

    if ( IsWow64Process( pProcess , ( PBOOL ) &bIsWow64 ) )
    {
    }

    HexProcessID = _HexProcessID;

    String wBuf[ UNICODE_STRING_MAX_CHARS ];
    GetModuleBaseName( pProcess , 0 , wBuf , sizeof( wBuf ) );

    sName = stdString( wBuf );

    GetInformations();

    String sProcessPathTmp[ MAX_PATH ];
    if ( GetMappedFileName( pProcess , nullptr , sProcessPathTmp , MAX_PATH ) )
    {
        sProcessPath = globalString + stdString( sProcessPathTmp );
    }

    CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "[%s->Initialized]\n" ) , sName.c_str() );
}

N_Process::Process::Process( stdString _swProcessName )
{
    pAddress = nullptr;
    sName = _swProcessName;

    //Snapshots, are what they are, they take "screenshots" of every processes

    PROCESSENTRY32 ProcessEntry;
    ProcessEntry.dwSize = sizeof( PROCESSENTRY32 );

    // Create our snapshop to capture processes
    Pointer SnapShot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS , 0 );

    // We must check if a process is encountered first before getting the others , so we don't make useless loops.

    if ( Process32First( SnapShot , &ProcessEntry ) )
    {
        // Capture the rest of the processes.

        while ( Process32Next( SnapShot , &ProcessEntry ) )
        {
            // Compare if our string contains the name of the exe we captured from the struct PROCESSENTRY32

            if ( StrCmp( ProcessEntry.szExeFile , _swProcessName.c_str() ) == 0 )
            {
                // Open the process to get the handle of it, with maximum rights.

                pProcess = OpenProcess( PROCESS_ALL_ACCESS , false , ProcessEntry.th32ProcessID );

                /*if ( GetLastError() != ERROR_SUCCESS )
                {
                    CONSOLEDEBUG( TEXT( "Couldn't open correctly process %s (0x%p)\n" ) , _swProcessName.c_str() , GetLastError() );
                }*/

                if ( IsWow64Process( pProcess , ( PBOOL ) &bIsWow64 ) )
                {
                }

                HexProcessID = ProcessEntry.th32ProcessID;
            }
        }
    }

    CloseHandle( SnapShot );

    GetInformations();

    String sProcessPathTmp[ MAX_PATH ];
    if ( GetMappedFileName( pProcess , nullptr , sProcessPathTmp , MAX_PATH ) )
    {
        sProcessPath = globalString + stdString( sProcessPathTmp );
    }

    CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "[%s->Initialized]\n" ) , sName.c_str() );
}

// Deconstructor, free our memory allocated, etc...
N_Process::Process::~Process()
{
    Free();
}

// Get the process handle.
Pointer N_Process::Process::Get()
{
    return pProcess;
}

// Find a module by name.
Pointer N_Process::Process::FindModule( stdString DLLName )
{
    // First let's refresh the list of the modules loaded into the prcess before comparing them.
    RefreshGetModules();

    // Loop until we find.
    Pointer pModuleAddress = nullptr;

    for ( auto it = vshModules.begin(); it != vshModules.end(); it++ )
    {
        if ( StrCmpI( ( String* ) it->m_sName.c_str() , DLLName.c_str() ) == false )
        {
            pModuleAddress = ( Pointer ) it->m_hA;
            goto Found;
        }
    }

    for ( auto it = psForcedModules.begin(); it != psForcedModules.end(); it++ )
    {
        if ( StrCmpI( ( String* ) it->m_sName.c_str() , DLLName.c_str() ) == false )
        {
            pModuleAddress = ( Pointer ) it->m_hA;
            goto Found;
        }
    }

Found:
    return pModuleAddress;
}

// Find the module path from the module address , GetMappedFileName can do it
stdString N_Process::Process::FindModulePath( Pointer pModuleAddress )
{
    String PathToDLL[ UNICODE_STRING_MAX_CHARS ];
    GetMappedFileName( pProcess , ( HMODULE ) pModuleAddress , PathToDLL , sizeof( PathToDLL ) );

    return globalString + stdString( PathToDLL );
}

void N_Process::Process::PrintAllModules()
{
    RefreshGetModules();

    for ( auto it = vshModules.begin(); it != vshModules.end(); it++ )
    {
        N_Console::Print<FOREGROUND_GREEN>( TEXT( "[%s->PrintAllModules] Module: %s - 0x%p\n" ) , it->m_sName.c_str() , it->m_hA );
    }
}

void N_Process::Process::RefreshGetModules()
{
    // Let's clear all our previous
    vshModules.clear();

    // Temp buffer to get modules addresses.
    std::vector<Pointer> vswMods( 0xFFF );

    // Let's enumerate all modules.

    // Just a random stuff that windows needs (didn't look at it yet what it truely means).
    DWORD dwNeeded;

    if ( EnumProcessModulesEx( pProcess , ( HMODULE* ) vswMods.data() , ( DWORD ) vswMods.size() , &dwNeeded , LIST_MODULES_ALL ) )
    {
        // Buffer of module name
        TCHAR szModName[ MAX_PATH ];

        for ( DWORD i = 0; i < ( dwNeeded / sizeof( HMODULE ) ); i++ )
        {
            if ( GetModuleBaseName( pProcess , ( HMODULE ) vswMods[ i ] , szModName , MAX_PATH ) )
            {
                // Emplace for each module name its address.
                // Same as mshModules[ szModName ] = ( HEX ) vswMods[ i ];
                vshModules.push_back( Module( szModName , ( HEX ) vswMods[ i ] ) );
            }
        }
    }

    vswMods.clear();
}

void N_Process::Process::GetInformations()
{
    RefreshGetModules();

    for ( auto it = vshModules.begin(); it != vshModules.end(); it++ )
    {
        String *StrFound = StrStrI( ( String* ) it->m_sName.c_str() , sName.c_str() );

        if ( StrFound != nullptr )  //If we found the process, print it cyan otherwhise just green.
        {
            CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "[%s->GetInformations] Found: %s -> 0x%p\n" ) , sName.c_str() , it->m_sName.c_str() , it->m_hA );
            pAddress = ( Pointer ) it->m_hA;
            sName = it->m_sName;
        }
        else
            CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "[%s->GetInformations] Module: %s -> 0x%p\n" ) , sName.c_str() , it->m_sName.c_str() , it->m_hA );
    }

    if ( pAddress == nullptr ) //We couldn't find the process something that should never happen?
        CONSOLEDEBUG( TEXT( "[%s->GetInformations] Failed to find the base address of the process\n" ) , sName.c_str() );
}

stdString &N_Process::Process::GetName()
{
    return sName;
}

HEX &N_Process::Process::GetID()
{
    return HexProcessID;
}

void N_Process::Process::Free()
{
    CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "[%s->Uninitialized]\n" ) , sName.c_str() );

    if ( pProcess != nullptr )
    {
        CloseHandle( pProcess );
        pProcess = nullptr;
    }

    HexProcessID = 0;
    sName.clear();
    vshModules.clear();
}

bool N_Process::Process::SetAllAccess()
{
    // Get a token for our process to adjust privileges to all access.

    Pointer pToken;
    if ( !OpenProcessToken( pProcess , TOKEN_ALL_ACCESS , &pToken ) )
    {
        return false;
    }

    // Set the token privileges to debug.

    TOKEN_PRIVILEGES tp;
    tp.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;
    tp.PrivilegeCount = 1;
    LUID luid;

    if ( !LookupPrivilegeValue( 0 , SE_DEBUG_NAME , &luid ) )
    {
        CloseHandle( pToken );
        return false;
    }

    tp.Privileges[ 0 ].Luid = luid;

    //Adjust the token privileges for setting the process to all access.

    if ( !AdjustTokenPrivileges( pToken , false , &tp , sizeof( TOKEN_PRIVILEGES ) , nullptr , nullptr ) )
    {
        CloseHandle( pToken );
        return false;
    }

    if ( GetLastError() != ERROR_SUCCESS )
    {
        CloseHandle( pToken );
        return false;
    }

    CloseHandle( pToken );

    return true;
}

Pointer N_Process::Process::CreateRemotlyThread( Pointer pRoutine , Pointer pArguments , unsigned long *pULRetThread )
{
    // Open with ida pro and search for RtlCreateUserThread

    // Same as CreateRemoteThread, just undocumented version.

    // It creates a thread remotly to the process, so we can call LoadLibrary or other api functions or routines.

    // Calls -> RtlpCreateUserThreadEx -> NtCreateThreadEx

#ifndef _DEBUG
    typedef
        NTSTATUS
        ( NTAPI * tNtCreateThreadEx )(
        _Out_ PHANDLE ThreadHandle ,
        _In_ ACCESS_MASK DesiredAccess ,
        _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes ,
        _In_ HANDLE ProcessHandle ,
        _In_ PVOID StartRoutine , // PUSER_THREAD_START_ROUTINE
        _In_opt_ PVOID Argument ,
        _In_ ULONG CreateFlags , // THREAD_CREATE_FLAGS_*
        _In_ SIZE_T ZeroBits ,
        _In_ SIZE_T StackSize ,
        _In_ SIZE_T MaximumStackSize ,
        _In_opt_ PPS_ATTRIBUTE_LIST AttributeList
        );

    HANDLE hRemotedThread = nullptr;

    tNtCreateThreadEx NtCreateThreadEx = ( tNtCreateThreadEx ) GetProcAddress( LoadLibrary( TEXT( "ntdll.dll" ) ) , "NtCreateThreadEx" );

    if ( NtCreateThreadEx != nullptr )
    {
        OBJECT_ATTRIBUTES ObjAttributes;
        InitializeObjectAttributes( &ObjAttributes ,
                                    nullptr ,
                                    OBJ_KERNEL_HANDLE | OBJ_FORCE_ACCESS_CHECK ,
                                    nullptr ,
                                    nullptr );

        NTSTATUS NtStatus = NtCreateThreadEx( &hRemotedThread , THREAD_ALL_ACCESS , &ObjAttributes
                                              , pProcess
                                              , ( LPTHREAD_START_ROUTINE ) pRoutine
                                              , pArguments
                                              , THREAD_CREATE_FLAGS_HIDE_FROM_DEBUGGER
                                              , 0 , 0 , 0 , 0 );

        if ( pULRetThread != nullptr )
        {
            *pULRetThread = NtStatus;
        }
    }


    return hRemotedThread;
#else
    return CreateRemoteThread( pProcess , 0 , 0 , ( LPTHREAD_START_ROUTINE ) pRoutine , pArguments , 0 , 0 );
#endif

    /*typedef NTSTATUS
    ( NTAPI * tRtlCreateUserThread )(
        IN HANDLE               ProcessHandle ,
        IN PSECURITY_DESCRIPTOR SecurityDescriptor OPTIONAL ,
        IN BOOLEAN              CreateSuspended ,
        IN ULONG                StackZeroBits ,
        IN OUT PULONG           StackReserved ,
        IN OUT PULONG           StackCommit ,
        IN PVOID                StartAddress ,
        IN PVOID                StartParameter OPTIONAL ,
        OUT PHANDLE             ThreadHandle ,
        OUT _CLIENT_ID_T<PVOID>* ClientID );

    tRtlCreateUserThread RtlCreateUserThread = ( tRtlCreateUserThread ) ( Pointer ) GetProcAddress( LoadLibrary( TEXT( "ntdll.dll" ) ) , "RtlCreateUserThread" );

    if ( RtlCreateUserThread != nullptr )
    {
        Pointer pRemotedThread = nullptr;

        //SECURITY_DESCRIPTOR Security;
        //InitializeSecurityDescriptor( &Security , SECURITY_DESCRIPTOR_REVISION );

        //ACL acl;
        //acl.AclRevision = ACL_REVISION_DS;
        //acl.AclSize = sizeof( acl );
        //acl.Sbz1 = 0x24;
        //acl.Sbz2 = 0x37;
        //PSID sid;
        //SID_IDENTIFIER_AUTHORITY SIDIA;
        //Byte bSecAuth[] = SECURITY_NT_AUTHORITY;
        //memcpy( &SIDIA.Value , bSecAuth , sizeof( bSecAuth ) );
        //AllocateAndInitializeSid( &SIDIA , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , &sid );
        //SetSecurityDescriptorDacl( &Security , true , &acl , true );
        //SetSecurityDescriptorGroup( &Security , sid , true );
        //SetSecurityDescriptorOwner( &Security , sid , true );
        //SetSecurityDescriptorRMControl( &Security , nullptr );
        //SetSecurityDescriptorSacl( &Security , true , &acl , true );

        NTSTATUS ULRetCode = RtlCreateUserThread( pProcess , nullptr , false , 0 , nullptr , nullptr , pRoutine , pArguments , &pRemotedThread , nullptr );

        if ( pULRetThread != nullptr )
        {
            *pULRetThread = ULRetCode;
        }

        return pRemotedThread;
    }

    return nullptr;*/
}

uHEX N_Process::Process::GetFunctionReadPE( const PCHAR pcFunctionName , const stdString & sModuleName )
{
    HEX HexOffset = 0;

    bool bIsForwarded = false;

    // The module should be loaded in every cases into the other process, so we find the address of it.
    Pointer pRemotedModuleAddress = FindModule( sModuleName.c_str() );

    if ( pRemotedModuleAddress == nullptr )
    {
        ForceLoadLibrary( sModuleName );
        RefreshGetModules();
    }

    pRemotedModuleAddress = FindModule( sModuleName.c_str() );

    // Gotcha.
    if ( pRemotedModuleAddress != nullptr )
    {
        // Now we have the module address of the remoted process, we can get its full path in the disk.
        stdString sPathToDLL = FindModulePath( pRemotedModuleAddress );

        // Module in disk got deleted instantly just before LoadLibrary was called? No it should really never happen. But who knows.
        if ( sPathToDLL.empty() )
        {
            CONSOLEDEBUG( TEXT( "[%s->GetFunction] couldn't resolve path for module %s\n" ) , sName.c_str() , sModuleName.c_str() );
            return 0;
        }

        HEX hSize = -1;
        auto pDosHeader = ( PIMAGE_DOS_HEADER ) N_FileSystem::ReadFile( sPathToDLL , &hSize );

        if ( hSize <= 0 )
        {
            CONSOLEDEBUG( TEXT( "[%s->GetFunction] couldn't read from path for module %s\n" ) , sName.c_str() , sModuleName.c_str() );
            return 0;
        }

        auto pParentNtHeaders = GetParentNtHeaders( pDosHeader );

        if ( bIsWow64 )
        {
            auto pNtHeaders = ( pNTHeaders32 ) pParentNtHeaders;

            uHEX32 EntryRVA = pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ].VirtualAddress;
            uHEX32 EntrySize = pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ].Size;

            auto pExportDirectory = ( PIMAGE_EXPORT_DIRECTORY ) ( ( HEX ) pDosHeader
                                                                  + ( HEX ) RvaToRaw32( pNtHeaders
                                                                  , EntryRVA ) );

            if ( pExportDirectory != nullptr )
            {
                puHEX32 pFunctions = ( puHEX32 ) ( ( HEX ) pDosHeader
                                                   + ( HEX ) RvaToRaw32( pNtHeaders
                                                   , pExportDirectory->AddressOfFunctions ) );

                puHEX32 pNames = ( puHEX32 ) ( ( HEX ) pDosHeader
                                               + ( HEX ) RvaToRaw32( pNtHeaders
                                               , pExportDirectory->AddressOfNames ) );

                PWORD pOrdinals = ( PWORD ) ( ( HEX ) pDosHeader
                                              + ( HEX ) RvaToRaw32( pNtHeaders
                                              , pExportDirectory->AddressOfNameOrdinals ) );

                std::string str = pcFunctionName;

                if ( std::all_of( str.begin() , str.end() , ::isdigit ) )
                {
                    uHEX32 hWishOrdinal = ( uHEX32 ) atoi( pcFunctionName );

                    uHEX32 hRVAFunction = pFunctions[ hWishOrdinal - pExportDirectory->Base ];

                    // Forwarded.
                    if ( hRVAFunction > EntryRVA && hRVAFunction < EntryRVA + EntrySize )
                    {
                        std::string sfFuncName = ( PCHAR ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw32( pNtHeaders , hRVAFunction ) );

                        size_t sdotPos = sfFuncName.find( "." );

                        if ( sdotPos != std::string::npos )
                        {
                            stdString sModule( AutoConvertS( sfFuncName.substr( 0 , sdotPos + 1 ) ) );

                            sModule.resize( sModule.size() + 3 );
                            sModule[ sdotPos + 1 ] = TEXT( 'D' );
                            sModule[ sdotPos + 2 ] = TEXT( 'L' );
                            sModule[ sdotPos + 3 ] = TEXT( 'L' );

                            std::string sRealFuncName = sfFuncName.substr( sdotPos + 1 , sfFuncName.size() );

                            HexOffset = GetFunctionReadPE( ( PCHAR ) sRealFuncName.c_str() , sModule.c_str() );

                            bIsForwarded = true;
                        }
                    }
                    else
                    {
                        Pointer pFunctionAddress = ( Pointer ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw32( pNtHeaders , hRVAFunction ) );

                        HexOffset = ( HEX ) RawToRva32( pNtHeaders , ( uHEX32 ) ( ( HEX ) pFunctionAddress - ( HEX ) pDosHeader ) );
                    }

                    goto FoundExport;
                }
                else
                {
                    for ( uHEX32 i = 0; i != pExportDirectory->NumberOfNames; i++ )
                    {
                        const PCHAR sFuncName = ( PCHAR ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw32( pNtHeaders , pNames[ i ] ) );

                        if ( !_stricmp( sFuncName , str.c_str() ) )
                        {
                            uHEX32 hReadOrdinal = ( uHEX32 ) pOrdinals[ i ];

                            uHEX32 hRVAFunction = pFunctions[ hReadOrdinal ];

                            // Forwarded.
                            if ( hRVAFunction > EntryRVA && hRVAFunction < EntryRVA + EntrySize )
                            {
                                std::string sfFuncName = ( PCHAR ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw32( pNtHeaders , hRVAFunction ) );

                                size_t sdotPos = sfFuncName.find( "." );

                                if ( sdotPos != std::string::npos )
                                {
                                    stdString sModule( AutoConvertS( sfFuncName.substr( 0 , sdotPos + 1 ) ) );

                                    sModule.resize( sModule.size() + 3 );
                                    sModule[ sdotPos + 1 ] = TEXT( 'D' );
                                    sModule[ sdotPos + 2 ] = TEXT( 'L' );
                                    sModule[ sdotPos + 3 ] = TEXT( 'L' );

                                    std::string sRealFuncName = sfFuncName.substr( sdotPos + 1 , sfFuncName.size() );

                                    HexOffset = GetFunctionReadPE( ( PCHAR ) sRealFuncName.c_str() , sModule.c_str() );

                                    bIsForwarded = true;
                                }
                            }
                            else
                            {
                                Pointer pFunctionAddress = ( Pointer ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw32( pNtHeaders , hRVAFunction ) );

                                HexOffset = ( HEX ) RawToRva32( pNtHeaders , ( uHEX32 ) ( ( HEX ) pFunctionAddress - ( HEX ) pDosHeader ) );
                            }

                            goto FoundExport;
                        }
                    }

                    CONSOLEDEBUG( TEXT( "GetFunctionReadPE: Couldn't find %s for module %s\n" ) , AutoConvertS( pcFunctionName ) , sModuleName.c_str() );

                    return 0;
                }
            }
        }
        else
        {
            auto pNtHeaders = ( pNTHeaders64 ) pParentNtHeaders;

            uHEX32 EntryRVA = pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ].VirtualAddress;
            uHEX32 EntrySize = pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ].Size;

            auto pExportDirectory = ( PIMAGE_EXPORT_DIRECTORY ) ( ( HEX ) pDosHeader
                                                                  + ( HEX ) RvaToRaw64( pNtHeaders
                                                                  , EntryRVA ) );

            if ( pExportDirectory != nullptr )
            {
                puHEX32 pFunctions = ( puHEX32 ) ( ( HEX ) pDosHeader
                                                   + ( HEX ) RvaToRaw64( pNtHeaders
                                                   , pExportDirectory->AddressOfFunctions ) );

                puHEX32 pNames = ( puHEX32 ) ( ( HEX ) pDosHeader
                                               + ( HEX ) RvaToRaw64( pNtHeaders
                                               , pExportDirectory->AddressOfNames ) );

                PWORD pOrdinals = ( PWORD ) ( ( HEX ) pDosHeader
                                              + ( HEX ) RvaToRaw64( pNtHeaders
                                              , pExportDirectory->AddressOfNameOrdinals ) );

                std::string str = pcFunctionName;

                if ( std::all_of( str.begin() , str.end() , ::isdigit ) )
                {
                    uHEX32 hWishOrdinal = ( uHEX32 ) atoi( pcFunctionName );

                    uHEX32 hRVAFunction = pFunctions[ hWishOrdinal - pExportDirectory->Base ];

                    // Forwarded.
                    if ( hRVAFunction > EntryRVA && hRVAFunction < EntryRVA + EntrySize )
                    {
                        std::string sfFuncName = ( PCHAR ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw64( pNtHeaders , hRVAFunction ) );

                        size_t sdotPos = sfFuncName.find( "." );

                        if ( sdotPos != std::string::npos )
                        {
                            stdString sModule( AutoConvertS( sfFuncName.substr( 0 , sdotPos + 1 ) ) );

                            sModule.resize( sModule.size() + 3 );
                            sModule[ sdotPos + 1 ] = TEXT( 'D' );
                            sModule[ sdotPos + 2 ] = TEXT( 'L' );
                            sModule[ sdotPos + 3 ] = TEXT( 'L' );

                            std::string sRealFuncName = sfFuncName.substr( sdotPos + 1 , sfFuncName.size() );

                            HexOffset = GetFunctionReadPE( ( PCHAR ) sRealFuncName.c_str() , sModule.c_str() );

                            bIsForwarded = true;
                        }
                    }
                    else
                    {
                        Pointer pFunctionAddress = ( Pointer ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw64( pNtHeaders , hRVAFunction ) );

                        HexOffset = ( HEX ) RawToRva64( pNtHeaders , ( uHEX32 ) ( ( HEX ) pFunctionAddress - ( HEX ) pDosHeader ) );
                    }

                    goto FoundExport;
                }
                else
                {
                    for ( uHEX32 i = 0; i != pExportDirectory->NumberOfNames; i++ )
                    {
                        const PCHAR sFuncName = ( PCHAR ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw64( pNtHeaders , pNames[ i ] ) );

                        if ( !_stricmp( sFuncName , str.c_str() ) )
                        {
                            uHEX32 hReadOrdinal = ( uHEX32 ) pOrdinals[ i ];

                            uHEX32 hRVAFunction = pFunctions[ hReadOrdinal ];

                            // Forwarded.
                            if ( hRVAFunction > EntryRVA && hRVAFunction < EntryRVA + EntrySize )
                            {
                                std::string sfFuncName = ( PCHAR ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw64( pNtHeaders , hRVAFunction ) );

                                size_t sdotPos = sfFuncName.find( "." );

                                if ( sdotPos != std::string::npos )
                                {
                                    stdString sModule( AutoConvertS( sfFuncName.substr( 0 , sdotPos + 1 ) ) );

                                    sModule.resize( sModule.size() + 3 );
                                    sModule[ sdotPos + 1 ] = TEXT( 'D' );
                                    sModule[ sdotPos + 2 ] = TEXT( 'L' );
                                    sModule[ sdotPos + 3 ] = TEXT( 'L' );

                                    std::string sRealFuncName = sfFuncName.substr( sdotPos + 1 , sfFuncName.size() );

                                    HexOffset = GetFunctionReadPE( ( PCHAR ) sRealFuncName.c_str() , sModule.c_str() );

                                    bIsForwarded = true;
                                }
                            }
                            else
                            {
                                Pointer pFunctionAddress = ( Pointer ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw64( pNtHeaders , hRVAFunction ) );

                                HexOffset = ( HEX ) RawToRva64( pNtHeaders , ( uHEX32 ) ( ( HEX ) pFunctionAddress - ( HEX ) pDosHeader ) );
                            }

                            goto FoundExport;
                        }
                    }

                    CONSOLEDEBUG( TEXT( "GetFunctionReadPE: Couldn't find %s for module %s\n" ) , AutoConvertS( pcFunctionName ) , sModuleName.c_str() );

                    return 0;
                }
            }
        }

FoundExport:

        uHEX hFinal;

        if ( !bIsForwarded )
            hFinal = ( ( uHEX ) pRemotedModuleAddress + HexOffset );
        else
            hFinal = ( uHEX ) HexOffset;

        CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "Resolved: %s for module %s (0x%p)\n" ) , AutoConvertS( pcFunctionName ) , sModuleName.c_str() , hFinal );

        FreeAlloc( pDosHeader );

        return hFinal;
    }
    else
    {
        CONSOLEDEBUG( TEXT( "[%s->GetFunction] couldn't find module %s from process\n" ) , sName.c_str() , sModuleName.c_str() );
        return 0;
    }
}

std::vector<Pointer> N_Process::Process::GetThreads()
{
    std::vector<Pointer> m_Threads;
    Pointer pToolHelp32 = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD , 0 );

    if ( pToolHelp32 == INVALID_HANDLE_VALUE )
        return m_Threads;

    THREADENTRY32 te32;

    te32.dwSize = sizeof( THREADENTRY32 );

    if ( !Thread32First( pToolHelp32 , &te32 ) )
        return m_Threads;

    // Loop through all threads in every process. 
    do
    {
        // Only current process, please. 
        if ( te32.th32OwnerProcessID != GetProcessId( pProcess ) )
            continue;

        // Open a handle to the thread. 
        m_Threads.push_back( OpenThread( GENERIC_ALL , false , te32.th32ThreadID ) );

    } while ( Thread32Next( pToolHelp32 , &te32 ) );

    CloseHandle( pToolHelp32 );

    return m_Threads;
}

Pointer N_Process::Process::GetTEB( Pointer pThread )
{
    _THREAD_BASIC_INFORMATION_T<uHEX64> info;

    NTSTATUS status = NtQueryInformationThread( pThread , ( THREADINFOCLASS ) ThreadBasicInformation , &info , sizeof( info ) , 0 );

    if ( !NT_SUCCESS( status ) )
        return nullptr;

    return ( Pointer ) info.TebBaseAddress;
}

bool N_Process::Process::ForceLoadLibrary( const stdString &sModuleName )
{

#ifdef _UNICODE
    Pointer pLoadLibrary = ( Pointer ) GetFunctionReadPE( "LoadLibraryW" , TEXT( "KERNEL32.DLL" ) );
#else
    Pointer pLoadLibrary = ( Pointer ) GetFunctionReadPE( "LoadLibraryA" , TEXT( "KERNEL32.DLL" ) );
#endif

    if ( pLoadLibrary == nullptr )
        return false;

    HEX hSize = sModuleName.size() * sizeof( String );

    N_VirtualMemory::VirtualBuffer VForcedModule( hSize , PAGE_EXECUTE_READWRITE , nullptr , pProcess , TEXT( "Forcing_" ) + sModuleName , ( Pointer ) sModuleName.data() );

    Buffer<Byte> bufRoutine( 0 );

    if ( bIsWow64 )
    {
        Byte bRoutine[] =
        {
              0x66 , 0x90 , 0x56 , 0x8B , 0x74 , 0x24 , 0x08 , 0xFF , 0x76 , 0x08 , 0x8B , 0x46 , 0x10 , 0xFF , 0xD0 , 0x89 , 0x06 , 0x83 , 0xC8 ,
              0x00 , 0xC7 , 0x46 , 0x04 , 0x00 , 0x00 , 0x00 , 0x00 , 0x5E , 0x74 , 0x06 , 0xB8 , 0x01 , 0x00 , 0x00 , 0x00 , 0xC3 , 0x33 , 0xC0 , 0xC3
        };

        bufRoutine.Add( ( Pointer ) bRoutine , sizeof( bRoutine ) );
    }
    else
    {
        Byte bRoutine[] =
        {
              0x40 , 0x53 , 0x48 , 0x83 , 0xEC , 0x20 , 0x48 , 0x8B , 0x41 , 0x10 , 0x48 , 0x8B , 0xD9 , 0x48 , 0x8B , 0x49 , 0x08 , 0xFF , 0xD0
            , 0x33 , 0xC9 , 0x48 , 0x89 , 0x03 , 0x48 , 0x85 , 0xC0 , 0x0F , 0x95 , 0xC1 , 0x8B , 0xC1 , 0x48 , 0x83 , 0xC4 , 0x20 , 0x5B , 0xC3
        };

        bufRoutine.Add( ( Pointer ) bRoutine , sizeof( bRoutine ) );
    }

    N_VirtualMemory::VirtualBuffer VRoutine( bufRoutine.m_Size , PAGE_EXECUTE_READWRITE , nullptr , pProcess , TEXT( "ForcingRoutine_" ) + sModuleName , ( Pointer ) bufRoutine.m_pData );

    sLoadLib _LoadLibrary;

    _LoadLibrary.pAddress = ( uHEX64 ) ( uHEX ) pLoadLibrary;
    _LoadLibrary.pDLLPath = ( uHEX64 ) ( uHEX ) VForcedModule.pAddress;
    _LoadLibrary.pReturnAddress = 0;

    N_VirtualMemory::VirtualBuffer VParams( sizeof( _LoadLibrary ) , PAGE_EXECUTE_READWRITE , nullptr , pProcess , TEXT( "ForcingParams_" ) + sModuleName , ( Pointer ) & _LoadLibrary );

    Pointer pThread = CreateRemotlyThread( VRoutine.pAddress , VParams.pAddress );

    WaitForSingleObject( pThread , INFINITE );

    VParams.TransferToProcess();

    std::unique_ptr<uHEX32> hExitCode( new uHEX32 );
    GetExitCodeThread( pThread , hExitCode.get() );

    CloseHandle( pThread );

    VForcedModule.Free();
    VRoutine.Free();

    if ( *hExitCode == 0 )
        return false;

    RefreshGetModules();

    sLoadLib *RetreivedLoadLibrary = ( sLoadLib* ) VParams.pAddress;

    bool bFound = false;

    for ( size_t it = 0; it != vshModules.size(); it++ )
    {
        if ( vshModules[ it ].m_hA == ( HEX ) RetreivedLoadLibrary->pReturnAddress )
        {
            psForcedModules.push_back( Module( sModuleName , vshModules[ it ].m_hA ) );
            bFound = true;
            break;
        }
    }

    return bFound;
}

bool N_Process::Process::ForceFreeLibrary( const stdString &sModuleName )
{
    Pointer pModuleAddress = FindModule( sModuleName );

    if ( pModuleAddress != nullptr )
    {
        Pointer pFreeLibrary = ( Pointer ) GetFunctionReadPE( "FreeLibrary" , TEXT( "KERNEL32.DLL" ) );

        if ( pFreeLibrary == nullptr )
            return false;

        Pointer pThread = CreateRemotlyThread( pFreeLibrary , pModuleAddress );

        WaitForSingleObject( pThread , INFINITE );

        uHEX32 hExitCode;
        GetExitCodeThread( pThread , &hExitCode );

        CloseHandle( pThread );

        if ( hExitCode != ERROR_SUCCESS )
            return false;

        return true;
    }

    return false;
}

bool N_Process::Process::FreeForcedLibraries()
{
    bool bReturn = true;

    for ( auto &&it : psForcedModules )
    {
        if ( !ForceFreeLibrary( it.m_sName.c_str() ) )
            bReturn = false;
    }

    return bReturn;
}



NTSTATUS NTAPI NtQueryInformationThread(
    IN HANDLE ThreadHandle ,
    IN THREADINFOCLASS ThreadInformationClass ,
    OUT PVOID ThreadInformation ,
    IN ULONG ThreadInformationLength ,
    OUT PULONG ReturnLength OPTIONAL
)
{
    return _CallFunction<NTSTATUS , e_stdcall , Pointer , THREADINFOCLASS , Pointer , uHEX32 , puHEX32>
        ( GetProcAddress( GetModuleHandle( TEXT( "ntdll.dll" ) ) , AutoConvertC( TEXT( "NtQueryInformationThread" ) ) ) ,
          ThreadHandle , ThreadInformationClass , ThreadInformation , ThreadInformationLength , ReturnLength );
}