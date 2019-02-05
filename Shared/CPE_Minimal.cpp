#include "Includes.hxx"
#include "CPE_Minimal.hxx"

bool C_CPEMinimal::CopySections( N_VirtualMemory::VirtualBuffer &VirtualBuffer )
{
    for ( auto &&it : m_Sections )
    {
        if ( it.m_Buffer.m_Size == 0 )
            continue;

        if ( !VirtualBuffer.ReplaceLocal( it.m_Buffer.P() , ( HEX ) it.m_hRVA , ( HEX ) it.m_Buffer.m_Size ) )
            return false;
    }

    for ( auto &&it : m_Sections )
    {
        VirtualBuffer.Flags.ChangeInRange( it.m_hRVA , it.m_hRVA + it.m_VirtualSize , it.m_hFlags );
    }

    if ( !VirtualBuffer.RefreshFlags() )
        return false;

    return true;
}

bool C_CPEMinimal::CallTlsCBs( N_VirtualMemory::VirtualBuffer& VirtualBuffer , N_Process::Process *Process )
{
    if ( m_TlsCBs.empty() )
        return true;

    for ( auto &&it : m_TlsCBs )
    {
        Pointer pCallTls = ( Pointer ) ( ( HEX ) VirtualBuffer.pAddress + ( HEX ) it.m_pRVA );

        if ( iArchitecture == M_x86 )
        {
            std::vector<Byte> bTls_Main_Start = { 0x8B , 0x44 , 0x24 , 0x04 , 0xFF , 0x70 , 0x0C , 0x8B , 0x08 , 0xFF , 0x70 , 0x08
                , 0xFF , 0x70 , 0x04 , 0xFF , 0xD1 , 0xC3 , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC };

            DllMain32 DllArgs( ( uHEX32 ) ( uHEX64 ) pCallTls
                                                , ( uHEX32 ) ( uHEX64 ) VirtualBuffer.pAddress , DLL_PROCESS_ATTACH , 1 );

            it.pVRemotedArguments = new N_VirtualMemory::VirtualBuffer( sizeof( DllArgs ) , PAGE_READONLY
                                                                        , nullptr , Process->pProcess , TEXT( "pVRemotedArguments" ) , &DllArgs );

            if ( it.pVRemotedArguments->pAddress == nullptr )
                return false;

            it.pVRoutine = new N_VirtualMemory::VirtualBuffer( bTls_Main_Start.size() , PAGE_EXECUTE
                                                               , nullptr , Process->pProcess , TEXT( "pVRoutine" ) , ( Pointer ) bTls_Main_Start.data() );

            if ( it.pVRoutine->pAddress == nullptr )
                return false;

            it.m_pTlsAttach = Process->CreateRemotlyThread( it.pVRoutine->pAddress , it.pVRemotedArguments->pAddress );
        }
        else
        {
            std::vector<Byte> bTls_Main_Start = { 0x48 , 0x8B , 0x01 , 0x4C , 0x8B , 0x41 , 0x10 , 0x8B , 0x51 , 0x18 , 0x48 , 0x8B ,
                0x49 , 0x08 , 0x48 , 0xFF , 0xE0 , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC
                , 0xCC , 0xCC , 0xCC };

            DllMain64 DllArgs( ( uHEX64 ) pCallTls
                                                , ( uHEX64 ) VirtualBuffer.pAddress , DLL_PROCESS_ATTACH , 1 );

            it.pVRemotedArguments = new N_VirtualMemory::VirtualBuffer( sizeof( DllMain64 ) , PAGE_READONLY
                                                                        , nullptr , Process->pProcess , TEXT( "pVRemotedArguments" ) , &DllArgs );

            if ( it.pVRemotedArguments->pAddress == nullptr )
                return false;

            it.pVRoutine = new N_VirtualMemory::VirtualBuffer( bTls_Main_Start.size() , PAGE_EXECUTE
                                                               , nullptr , Process->pProcess , TEXT( "pVRoutine" ) , ( Pointer ) bTls_Main_Start.data() );

            if ( it.pVRoutine->pAddress == nullptr )
                return false;

            it.m_pTlsAttach = Process->CreateRemotlyThread( it.pVRoutine->pAddress , it.pVRemotedArguments->pAddress );
        }

        WaitForSingleObject( it.m_pTlsAttach , INFINITE );

        GetExitCodeThread( it.m_pTlsAttach , ( LPDWORD ) &it.hResultAttach );

        CloseHandle( it.m_pTlsAttach );
    }

    return true;
}

bool C_CPEMinimal::CallRoutine( N_VirtualMemory::VirtualBuffer& VirtualBuffer , N_Process::Process *Process )
{
    if ( iArchitecture == M_x86 )
    {
        pVRemotedArguments = new N_VirtualMemory::VirtualBuffer( m_RoutineArgs.m_Size , PAGE_READONLY
                                                                 , nullptr , Process->pProcess , TEXT( "pVRemotedArguments" ) , m_RoutineArgs.m_pData );

        if ( pVRemotedArguments->pAddress == nullptr )
            return false;

        pVRoutine = new N_VirtualMemory::VirtualBuffer( bDLL_Main_Start.m_Size , PAGE_EXECUTE
                                                        , nullptr , Process->pProcess , TEXT( "pVRoutine" ) , bDLL_Main_Start.m_pData );

        if ( pVRoutine->pAddress == nullptr )
            return false;

        pMainThread = Process->CreateRemotlyThread( pVRoutine->pAddress , pVRemotedArguments->pAddress );

        return true;
    }
    else
    {
        pVRemotedArguments = new N_VirtualMemory::VirtualBuffer( m_RoutineArgs.m_Size , PAGE_READONLY
                                                                 , nullptr , Process->pProcess , TEXT( "pVRemotedArguments" ) , m_RoutineArgs.m_pData );

        if ( pVRemotedArguments->pAddress == nullptr )
            return false;

        pVRoutine = new N_VirtualMemory::VirtualBuffer( bDLL_Main_Start.m_Size , PAGE_EXECUTE
                                                        , nullptr , Process->pProcess , TEXT( "pVRoutine" ) , bDLL_Main_Start.m_pData );

        if ( pVRoutine->pAddress == nullptr )
            return false;

        pMainThread = Process->CreateRemotlyThread( pVRoutine->pAddress , pVRemotedArguments->pAddress );

        return true;
    }
}

bool C_CPEMinimal::FreeRoutine( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *Process )
{
    WaitForSingleObject( pMainThread , INFINITE );

    bool bAllThreadsTerminated = false;

    while ( !bAllThreadsTerminated )
    {
        bAllThreadsTerminated = true;

        for ( auto &&i : Process->GetThreads() )
        {
            Pointer pStartRoutine = nullptr;

            NTSTATUS NtStatus = NtQueryInformationThread( i , ( THREADINFOCLASS ) ThreadQuerySetWin32StartAddress , &pStartRoutine , sizeof( pStartRoutine ) , 0 );

            if ( !NT_SUCCESS( NtStatus )
                 || pStartRoutine == nullptr )
            {
                CloseHandle( i );
                continue;
            }

            if ( ( ( uHEX ) pStartRoutine ) > ( uHEX ) VirtualBuffer.pAddress
                 && ( ( uHEX ) pStartRoutine ) <= ( ( uHEX ) VirtualBuffer.pAddress + m_ImageSize ) )
            {
                WaitForSingleObject( i , INFINITE );
            }

            CloseHandle( i );
        }
    }

    HEX32 hResult;
    GetExitCodeThread( pMainThread , ( LPDWORD ) &hResult );

    CloseHandle( pMainThread );

    delete pVRemotedArguments;
    delete pVRoutine;

    return true;
}

bool C_CPEMinimal::EndTlsCBs( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *Process )
{
    if ( m_TlsCBs.empty() )
        return true;

    for ( auto &&it : m_TlsCBs )
    {
        Pointer pCallTls = ( Pointer ) ( ( HEX ) VirtualBuffer.pAddress + ( HEX ) it.m_pRVA );

        if ( iArchitecture == M_x86 )
        {
            DllMain32 DllArgs( ( uHEX32 ) ( uHEX64 ) pCallTls
                                                , ( uHEX32 ) ( uHEX64 ) VirtualBuffer.pAddress , DLL_PROCESS_DETACH , 1 );

            if ( !it.pVRemotedArguments->ReplaceLocal( &DllArgs , 0 , sizeof( DllMain32 ) ) )
                return false;

            if ( it.pVRemotedArguments->pAddress == nullptr )
                return false;

            it.m_pTlsDetach = Process->CreateRemotlyThread( it.pVRoutine->pAddress , it.pVRemotedArguments->pAddress );
        }
        else
        {
            DllMain64 DllArgs( ( uHEX64 ) pCallTls
                                                , ( uHEX64 ) VirtualBuffer.pAddress , DLL_PROCESS_DETACH , 1 );

            if ( !it.pVRemotedArguments->ReplaceLocal( &DllArgs , 0 , sizeof( DllMain64 ) ) )
                return false;

            if ( it.pVRemotedArguments->pAddress == nullptr )
                return false;

            it.m_pTlsDetach = Process->CreateRemotlyThread( it.pVRoutine->pAddress , it.pVRemotedArguments->pAddress );
        }

        WaitForSingleObject( it.m_pTlsDetach , INFINITE );

        GetExitCodeThread( it.m_pTlsDetach , ( LPDWORD ) &it.hResultAttach );

        CloseHandle( it.m_pTlsDetach );

        delete it.pVRoutine;
        delete it.pVRemotedArguments;
    }

    return true;
}

bool C_CPEMinimal::InitStaticTls( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *Process )
{
    if ( m_StaticTls.m_RVATlsDirSize == 0 )
        return true;

    IMAGE_DOS_HEADER DosHeaderGenerated;
    memset( &DosHeaderGenerated , 0 , sizeof( DosHeaderGenerated ) );

    DosHeaderGenerated.e_lfanew = sizeof( IMAGE_DOS_HEADER );
    DosHeaderGenerated.e_magic = IMAGE_DOS_SIGNATURE;

    CSigScan_V2 LdrpHandleTlsData( Process );

    if ( !Process->bIsWow64 )
    {
        LdrpHandleTlsData.Scan( "74 33 44 8D 43 09" , TEXT( "ntdll.dll" ) );
        LdrpHandleTlsData.m_pAddress.uptr -= 0x44;
    }
    else
    {
        LdrpHandleTlsData.Scan( "8B C1 8D 4D AC 51" , TEXT( "ntdll.dll" ) );
        LdrpHandleTlsData.m_pAddress.uptr -= 0x18;
    }

    if ( !VirtualBuffer.ReplaceLocal( &DosHeaderGenerated , 0 , sizeof( DosHeaderGenerated ) ) )
        goto FailedTls;

    if ( iArchitecture == M_x86 )
    {
        s_InitStaticTls<uHEX32> InitSTLS;
        memset( &InitSTLS , 0 , sizeof( InitSTLS ) );
        InitSTLS.EntryBase.DllBase = ( uHEX32 ) ( uHEX ) VirtualBuffer.pAddress;
        InitSTLS.pLdrpHandleTlsData = ( uHEX32 ) LdrpHandleTlsData.m_pAddress.uptr;

        N_VirtualMemory::VirtualBuffer *pVRemoteArg = Process->VirtualAlloc( sizeof( InitSTLS ) );

        if ( !pVRemoteArg->ReplaceLocal( &InitSTLS , 0 , sizeof( InitSTLS ) ) )
            goto FailedTls;

        Byte bLdrpHandleTlsDataRoutine[] =
        {
            0x8B , 0x4C , 0x24 , 0x04 , 0x8B , 0x41 , 0x50 , 0xFF , 0xD0 , 0xC2 , 0x04
        };

        N_VirtualMemory::VirtualBuffer *pVRoutineInitTls = Process->VirtualAlloc( sizeof( bLdrpHandleTlsDataRoutine ) );

        if ( !pVRoutineInitTls->ReplaceLocal( bLdrpHandleTlsDataRoutine , 0 , sizeof( bLdrpHandleTlsDataRoutine ) ) )
            goto FailedTls;

        NTHeaders32 NTHeadersGen;
        memset( &NTHeadersGen , 0 , sizeof( NTHeadersGen ) );

        NTHeadersGen.Parent.Signature = IMAGE_NT_SIGNATURE;
        NTHeadersGen.OptionalHeader.Magic = IMAGE_NT_OPTIONAL_HDR32_MAGIC;
        NTHeadersGen.OptionalHeader.SizeOfImage = m_ImageSize;
        NTHeadersGen.OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_TLS ].VirtualAddress = m_StaticTls.m_RVATlsDir;
        NTHeadersGen.OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_TLS ].Size = m_StaticTls.m_RVATlsDirSize;
        NTHeadersGen.OptionalHeader.NumberOfRvaAndSizes = INFINITE;

        if ( !VirtualBuffer.ReplaceLocal( &NTHeadersGen , sizeof( IMAGE_DOS_HEADER ) , sizeof( NTHeadersGen ) ) )
            goto FailedTls;

        Pointer pThread = Process->CreateRemotlyThread( pVRoutineInitTls->pAddress , pVRemoteArg->pAddress );

        WaitForSingleObject( pThread , INFINITE );

        NTSTATUS NtStatus;
        GetExitCodeThread( pThread , ( LPDWORD ) &NtStatus );

        memset( &NTHeadersGen , 0 , sizeof( NTHeadersGen ) );

        if ( !VirtualBuffer.ReplaceLocal( &NTHeadersGen , sizeof( IMAGE_DOS_HEADER ) , sizeof( NTHeadersGen ) ) )
            goto FailedTls;

        if ( !NT_SUCCESS( NtStatus ) )
            goto FailedTls;
    }
    else
    {
        s_InitStaticTls<uHEX64> InitSTLS;
        memset( &InitSTLS , 0 , sizeof( InitSTLS ) );
        InitSTLS.EntryBase.DllBase = ( uHEX64 ) ( uHEX ) VirtualBuffer.pAddress;
        InitSTLS.pLdrpHandleTlsData = ( uHEX64 ) LdrpHandleTlsData.m_pAddress.uptr;

        N_VirtualMemory::VirtualBuffer *pVRemoteArg = Process->VirtualAlloc( sizeof( InitSTLS ) );

        if ( !pVRemoteArg->ReplaceLocal( &InitSTLS , 0 , sizeof( InitSTLS ) ) )
            goto FailedTls;

        Byte bLdrpHandleTlsDataRoutine[] =
        {
            0x48 , 0x8B , 0x81 , 0x98 , 0x00 , 0x00 , 0x00 , 0x48 , 0xFF , 0xE0
        };

        N_VirtualMemory::VirtualBuffer *pVRoutineInitTls = Process->VirtualAlloc( sizeof( bLdrpHandleTlsDataRoutine ) );

        if ( !pVRoutineInitTls->ReplaceLocal( bLdrpHandleTlsDataRoutine , 0 , sizeof( bLdrpHandleTlsDataRoutine ) ) )
            goto FailedTls;

        NTHeaders64 NTHeadersGen;
        memset( &NTHeadersGen , 0 , sizeof( NTHeadersGen ) );

        NTHeadersGen.Parent.Signature = IMAGE_NT_SIGNATURE;
        NTHeadersGen.OptionalHeader.Magic = IMAGE_NT_OPTIONAL_HDR64_MAGIC;
        NTHeadersGen.OptionalHeader.SizeOfImage = m_ImageSize;
        NTHeadersGen.OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_TLS ].VirtualAddress = m_StaticTls.m_RVATlsDir;
        NTHeadersGen.OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_TLS ].Size = m_StaticTls.m_RVATlsDirSize;
        NTHeadersGen.OptionalHeader.NumberOfRvaAndSizes = INFINITE;

        if ( !VirtualBuffer.ReplaceLocal( &NTHeadersGen , sizeof( IMAGE_DOS_HEADER ) , sizeof( NTHeadersGen ) ) )
            goto FailedTls;

        Pointer pThread = Process->CreateRemotlyThread( pVRoutineInitTls->pAddress , pVRemoteArg->pAddress );

        WaitForSingleObject( pThread , INFINITE );

        NTSTATUS NtStatus;
        GetExitCodeThread( pThread , ( LPDWORD ) &NtStatus );

        memset( &NTHeadersGen , 0 , sizeof( NTHeadersGen ) );

        if ( !VirtualBuffer.ReplaceLocal( &NTHeadersGen , sizeof( IMAGE_DOS_HEADER ) , sizeof( NTHeadersGen ) ) )
            goto FailedTls;

        if ( !NT_SUCCESS( NtStatus ) )
            goto FailedTls;
    }

    memset( &DosHeaderGenerated , 0 , sizeof( DosHeaderGenerated ) );

    return VirtualBuffer.ReplaceLocal( &DosHeaderGenerated , 0 , sizeof( DosHeaderGenerated ) );

FailedTls:

    memset( &DosHeaderGenerated , 0 , sizeof( DosHeaderGenerated ) );

    return VirtualBuffer.ReplaceLocal( &DosHeaderGenerated , 0 , sizeof( DosHeaderGenerated ) );
}
