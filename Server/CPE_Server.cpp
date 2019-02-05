#include "Includes.hxx"
#include "CPE_Server.hxx"

C_CConstructPEServer g_CConstructPEServer;

void C_CConstructPEServer::MakeListForwardedDLL( std::list<std::string> &m_ListImportModules , const PCHAR pcFunctionName , const stdString &sModuleName )
{
    int SlotModule = -1;

    for ( size_t i = 0; i < InjectionInfo.m_Modules.size(); i++ )
    {
        if ( !_stricmp( InjectionInfo.m_Modules[ i ].sModuleName.c_str() , AutoConvertC( sModuleName.c_str() ) ) )
        {
            SlotModule = ( int ) i;
        }
    }

    if ( SlotModule == -1 )
    {
        m_DataServer.m_bNeedsForwardingDLLs = true;
        CONSOLEDEBUG( TEXT( "MakeListForwardedDLL: Couldn't find %s for module %s\n" ) , AutoConvertS( pcFunctionName ) , sModuleName.c_str() );
        return;
    }

    auto pDosHeader = ( PIMAGE_DOS_HEADER ) InjectionInfo.m_Modules[ SlotModule ].m_Buffer.m_pData;

    auto pParentNtHeaders = GetParentNtHeaders( pDosHeader );

    if ( InjectionInfo.m_bisWow64 )
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

                        m_ListImportModules.push_back( AutoConvertC( sModule ) );

                        MakeListForwardedDLL( m_ListImportModules , ( PCHAR ) sfFuncName.substr( sdotPos + 1 , sfFuncName.size() ).c_str() , sModule );
                    }
                }
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

                                m_ListImportModules.push_back( AutoConvertC( sModule ) );

                                MakeListForwardedDLL( m_ListImportModules , ( PCHAR ) sfFuncName.substr( sdotPos + 1 , sfFuncName.size() ).c_str() , sModule );
                            }
                        }
                    }
                }
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

                        m_ListImportModules.push_back( AutoConvertC( sModule ) );

                        MakeListForwardedDLL( m_ListImportModules , ( PCHAR ) sfFuncName.substr( sdotPos + 1 , sfFuncName.size() ).c_str() , sModule );
                    }
                }
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

                                m_ListImportModules.push_back( AutoConvertC( sModule ) );

                                MakeListForwardedDLL( m_ListImportModules , ( PCHAR ) sfFuncName.substr( sdotPos + 1 , sfFuncName.size() ).c_str() , sModule );
                            }
                        }
                    }
                }
            }
        }
    }

    m_ListImportModules.unique();
}

SocketBuffer* C_CConstructPEServer::MakeModulesInfos( C_CPE* CPE )
{
    SocketBuffer *buf = new SocketBuffer( 0 );

    m_DataServer.m_hSizeOfImage = CPE->m_ImageSize;

    buf->AddVar( CPE->m_ListImportModules.size() );

    for ( auto &&it : CPE->m_ListImportModules )
    {
        buf->AddVar<Type_Array>( it.data() , it.size() );
    }

    buf->AddVar<Type_32>( m_DataServer.m_hSizeOfImage );
    buf->AddVar<Type_8>( m_DataServer.m_bNeedsForwardingDLLs );

    return buf;
}

SocketBuffer* C_CConstructPEServer::MakeModulesInfosForwarded( C_CPE* CPE )
{
    m_DataServer.m_bNeedsForwardingDLLs = false;

    for ( auto &&i : CPE->m_Imports )
    {
        MakeListForwardedDLL( CPE->m_ListImportModules , ( PCHAR ) i.m_sFunctionName.c_str() , AutoConvertS( i.m_sModuleName ) );
    }

    return MakeModulesInfos( CPE );
}

bool C_CConstructPEServer::ProcessInjectionInfo( SocketBuffer &buf )
{
    InjectionInfo.Reset();

    InjectionInfo.m_bisWow64 = buf.ReadVar<Type_8>();
    InjectionInfo.pRelocateAddress = buf.ReadVar<Type_Pointer>();
    InjectionInfo.NumberOfModules = buf.ReadVar();

    for ( decltype( InjectionInfo.NumberOfModules ) i = 0; i != InjectionInfo.NumberOfModules; i++ )
    {
        CMemoryModulesRecvd Module;

        Module.pModuleAddress = buf.ReadVar<Type_Pointer>();

        size_t LenModuleName = 0;
        auto pModuleName = buf.ReadVar<Type_Array>( &LenModuleName );

        Module.sModuleName = std::string( ( char* ) pModuleName , LenModuleName );

        size_t SizeOfModule = 0;
        auto pModule = buf.ReadVar<Type_Array>( &SizeOfModule );

        Module.m_Buffer = SocketBuffer( pModule , SizeOfModule );;
        InjectionInfo.m_Modules.push_back( Module );
    }

    return true;
}

SocketBuffer* C_CConstructPEServer::MakeCPEMinimal( C_CPE* CPE )
{
    if ( CPE->RelocateSections( InjectionInfo.pRelocateAddress ) == CPE_Relocated )
    {
        C_CPEMinimalServer* CPEServer = ToMinimalServer( CPE );

        if ( CPEServer->ResolveImports() )
        {
            SocketBuffer* buf = ChangeToMinimal( CPEServer );

            delete CPEServer;

            return buf;
        }

        delete CPEServer;
    }

    return nullptr;
}