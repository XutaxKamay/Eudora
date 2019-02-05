#include "Includes.hxx"
#include "CPE_Client.hxx"

C_CConstructPEClient g_CConstructPEClient;

void C_CConstructPEClient::LoadModulesInfo( N_Process::Process *pProcess , SocketBuffer &buf )
{
    m_DataClient.m_ModulesToLoad.clear();

    auto NumberOfModules = buf.ReadVar();

    for ( decltype( NumberOfModules ) i = 0; i != NumberOfModules; i++ )
    {
        size_t LenModuleName = 0;
        char *ModuleName = ( char* ) buf.ReadVar<Type_Array>( &LenModuleName );

        m_DataClient.m_ModulesToLoad.push_back( S_ModuleToLoad( std::string( ModuleName , LenModuleName ) ) );
    }

    m_DataClient.m_hSizeOfImage = buf.ReadVar<Type_32>();
    m_DataClient.m_bNeedsForwardingDLLs = buf.ReadVar<Type_8>();

    if ( !m_DataClient.m_bNeedsForwardingDLLs )
        return;

    for ( auto &&i : m_DataClient.m_ModulesToLoad )
    {
        pProcess->ForceLoadLibrary( AutoConvertS( i.m_sModuleName ) );
    }

    pProcess->RefreshGetModules();
}

SocketBuffer* C_CConstructPEClient::MakeInjectionInfo( N_Process::Process* pProcess , N_VirtualMemory::VirtualBuffer& VirtualBuffer )
{
    SocketBuffer *buf = new SocketBuffer( 0 );

    buf->AddVar<Type_8>( pProcess->bIsWow64 );
    buf->AddVar<Type_Pointer>( VirtualBuffer.pAddress );
    buf->AddVar( m_DataClient.m_ModulesToLoad.size() );

    for ( auto &&i : m_DataClient.m_ModulesToLoad )
    {
        Pointer pRemoteAddress = pProcess->FindModule( AutoConvertS( i.m_sModuleName ) );

        if ( pRemoteAddress == nullptr )
            goto Failed;

        stdString sModulePath = pProcess->FindModulePath( pRemoteAddress );

        if ( !sModulePath.empty() )
        {
            HEX hSize = -1;
            Pointer pBuffer = N_FileSystem::ReadFile( sModulePath , &hSize );

            if ( hSize == -1 )
                goto Failed;

            buf->AddVar<Type_Pointer>( pRemoteAddress );
            buf->AddVar<Type_Array>( i.m_sModuleName.data() , i.m_sModuleName.size() );
            buf->AddVar<Type_Array>( pBuffer , hSize );
        }
        else
        {
            goto Failed;
        }
    }

    CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "Injection info: 0x%p , size %i\n" ) , buf->m_pData , buf->m_Size );

    return buf;

Failed:

    delete buf;
    CONSOLEDEBUG( TEXT( "Failed to construct modules.\n" ) );

    return nullptr;
}

void C_CConstructPEClient::ProcessCPEMinimal( N_Process::Process* pProcess , N_VirtualMemory::VirtualBuffer& VirtualBuffer , SocketBuffer &buf )
{
    C_CPEMinimal *CPEMinimal = ConstructMinimal( &buf );

    if ( CPEMinimal != nullptr
         && CPEMinimal->CopySections( VirtualBuffer )
         && CPEMinimal->InitStaticTls( VirtualBuffer , pProcess )
         && CPEMinimal->CallTlsCBs( VirtualBuffer , pProcess )
         && CPEMinimal->CallRoutine( VirtualBuffer , pProcess )
         && CPEMinimal->FreeRoutine( VirtualBuffer , pProcess )
         && CPEMinimal->EndTlsCBs( VirtualBuffer , pProcess ) )
    {
        CONSOLEDEBUG( TEXT( "Done processing!\n" ) );
    }
}

C_CPEMinimal* C_CConstructPEClient::ConstructMinimal( SocketBuffer* buf )
{
    C_CPEMinimal* CPEMinimal = new C_CPEMinimal();

    auto hImageSize = buf->ReadVar<Type_32>();

    auto iMachType = buf->ReadVar<Type_32>();
    auto iArchType = buf->ReadVar<Type_32>();
    auto hEntryPoint = buf->ReadVar<Type_32>();
    auto NumberOfTls = buf->ReadVar();

    for ( decltype( NumberOfTls ) i = 0; i != NumberOfTls; i++ )
    {
        CPEMinimal->m_TlsCBs.push_back( C_CTlsCB( buf->ReadVar<Type_Pointer>() ) );
    }

    auto NumberOfSections = buf->ReadVar();

    for ( decltype( NumberOfSections ) i = 0; i != NumberOfSections; i++ )
    {
        auto hFlags = buf->ReadVar<Type_32>();

        auto hVirtualSize = buf->ReadVar<Type_32>();

        auto hRVA = buf->ReadVar<Type_32>();

        size_t SizeSection = 0;
        auto pSection = buf->ReadVar<Type_Array>( &SizeSection );

        SocketBuffer Section( pSection , SizeSection );

        CPEMinimal->m_Sections.push_back( C_CSectionMinimal( hRVA , hVirtualSize , Section , hFlags ) );
    }

    size_t RoutineArgsSize = 0;
    auto pRoutineArgs = buf->ReadVar<Type_Array>( &RoutineArgsSize );

    CPEMinimal->m_RoutineArgs = SocketBuffer( pRoutineArgs , RoutineArgsSize );

    size_t SizeRoutineStart = 0;
    auto pRoutineStart = buf->ReadVar<Type_Array>( &SizeRoutineStart );

    CPEMinimal->bDLL_Main_Start = SocketBuffer( pRoutineStart , SizeRoutineStart );

    CPEMinimal->m_StaticTls.m_RVATlsDir = buf->ReadVar<Type_32>();
    CPEMinimal->m_StaticTls.m_RVATlsDirSize = buf->ReadVar<Type_32>();

    N_Console::Print( TEXT( "Reading was successful!\n" ) );

    CPEMinimal->iArchitecture = iArchType;
    CPEMinimal->iMachineType = iMachType;
    CPEMinimal->m_hEntryPoint = hEntryPoint;
    CPEMinimal->m_ImageSize = hImageSize;

    return CPEMinimal;
}

bool C_CConstructPEClient::ProcessProcedure()
{
    C_SocketClient Client( m_IP.c_str() , m_PORT.c_str() );

    bool bResult = 0;

    if ( Client.OpenConnection() )
    {
        if ( Client.SendPublicKey() && Client.RecvPublicKey() )
        {
            Client.DebugKeys();

            bool bFirstTime = true;

            auto ModulesToLoad = Client.RecvDataSecure( 0x100000 );

            if ( ModulesToLoad != nullptr )
            {
                N_Process::Process Process( GetCurrentProcess() );

                LoadModulesInfo( &Process , *ModulesToLoad );

                N_VirtualMemory::VirtualBuffer HackModule( m_DataClient.m_hSizeOfImage , PAGE_EXECUTE_READWRITE , nullptr , Process.pProcess );

                auto InjectionInfo = MakeInjectionInfo( &Process , HackModule );

                if ( InjectionInfo != nullptr && Client.SendDataSecure( InjectionInfo ) )
                {
                    while ( m_DataClient.m_bNeedsForwardingDLLs || bFirstTime )
                    {
                        bFirstTime = false;

                        auto ModulesToLoadForwarded = Client.RecvDataSecure( 0x100000 );

                        if ( ModulesToLoadForwarded != nullptr )
                        {
                            LoadModulesInfo( &Process , *ModulesToLoadForwarded );

                            if ( !m_DataClient.m_bNeedsForwardingDLLs )
                                break;

                            auto InjectionInfoForwarded = MakeInjectionInfo( &Process , HackModule );

                            if ( InjectionInfoForwarded != nullptr )
                            {
                                if ( !Client.SendDataSecure( InjectionInfoForwarded ) )
                                {
                                    break;
                                }
                            }
                            else
                                break;
                        }
                        else
                            break;
                    }

                    auto buf = Client.RecvDataSecure( 0x10000000 );

                    if ( buf != nullptr )
                    {
                        ProcessCPEMinimal( &Process , HackModule , *buf );
                        bResult = 1;
                    }
                }
            }
        }
    }

    return bResult;
}