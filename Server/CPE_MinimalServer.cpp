#include "Includes.hxx"
#include "CPE_Server.hxx"

uHEX32 C_CSectionMinimal::GetVirtualFlags()
{
    uHEX32 hVirtualFlags = 0;

    if ( m_hFlags & IMAGE_SCN_MEM_EXECUTE )
    {
        if ( m_hFlags & IMAGE_SCN_MEM_READ )
        {
            if ( m_hFlags & IMAGE_SCN_MEM_WRITE )
            {
                hVirtualFlags |= PAGE_EXECUTE_READWRITE;
            }
            else
            {
                hVirtualFlags |= PAGE_EXECUTE_READ;
            }
        }
        else if ( m_hFlags & IMAGE_SCN_MEM_WRITE )
        {
            hVirtualFlags |= PAGE_EXECUTE_WRITECOPY;
        }
        else
        {
            hVirtualFlags |= PAGE_EXECUTE;
        }
    }
    else if ( m_hFlags & IMAGE_SCN_MEM_READ )
    {
        if ( m_hFlags & IMAGE_SCN_MEM_WRITE )
        {
            hVirtualFlags |= PAGE_READWRITE;
        }
        else
        {
            hVirtualFlags |= PAGE_READONLY;
        }
    }
    else if ( m_hFlags & IMAGE_SCN_MEM_WRITE )
    {
        hVirtualFlags |= PAGE_WRITECOPY;
    }
    else
        hVirtualFlags |= PAGE_NOACCESS;

    if ( m_hFlags & IMAGE_SCN_MEM_NOT_CACHED )
    {
        hVirtualFlags |= PAGE_NOCACHE;
    }

    return hVirtualFlags;
}

C_CPEMinimalServer* C_CConstructPEServer::ToMinimalServer( C_CPE* CPE )
{
    C_CPEMinimalServer* CPEServer = new C_CPEMinimalServer();

    CPEServer->iArchitecture = CPE->iArchitecture;
    CPEServer->iMachineType = CPE->iMachineType;
    CPEServer->m_hEntryPoint = CPE->m_hEntryPoint;
    CPEServer->m_Imports = CPE->m_Imports;

    for ( auto &&it : CPE->m_Sections )
    {
        if ( it.m_hFlags & IMAGE_SCN_MEM_DISCARDABLE || it.m_Buffer.m_Size == 0 )
            continue;

        CPEServer->m_Sections.push_back( C_CSectionMinimal( it.m_hRVA , it.m_VirtualSize , it.m_Buffer , it.m_hFlags ) );
        CPEServer->m_SectionsOffsets.push_back( ( Pointer ) ( uHEX ) it.m_hFileOffset );
    }

    CPEServer->m_TlsCBs = CPE->m_TlsCBs;

    if ( CPEServer->iArchitecture == M_x86 )
    {
        DllMain32 Main( ( uHEX32 ) ( ( HEX ) InjectionInfo.pRelocateAddress + CPEServer->m_hEntryPoint )
                                           , ( uHEX32 ) ( uHEX64 ) InjectionInfo.pRelocateAddress , DLL_PROCESS_ATTACH , 1 );

        Byte Start[] =
        {
              0x8B , 0x44 , 0x24 , 0x04 , 0xFF , 0x70 , 0x0C , 0x8B , 0x08
            , 0xFF , 0x70 , 0x08 , 0xFF , 0x70 , 0x04 , 0xFF , 0xD1 , 0xC3
        };

        CPEServer->bDLL_Main_Start.Add( Start , sizeof( Start ) );

        CPEServer->m_RoutineArgs.Add( &Main , sizeof( Main ) );
    }
    else
    {
        DllMain64 Main( ( ( HEX ) InjectionInfo.pRelocateAddress + CPEServer->m_hEntryPoint )
                                           , ( uHEX64 ) InjectionInfo.pRelocateAddress , DLL_PROCESS_ATTACH , 1 );

        Byte Start[] =
        {
            0x48 , 0x8B , 0x01 , 0x4C , 0x8B , 0x41 , 0x10 , 0x8B ,
            0x51 , 0x18 , 0x48 , 0x8B , 0x49 , 0x08 , 0x48 , 0xFF , 0xE0
        };

        CPEServer->bDLL_Main_Start.Add( Start , sizeof( Start ) );

        CPEServer->m_RoutineArgs.Add( &Main , sizeof( Main ) );
    }

    CPEServer->InjectionInfo.m_bisWow64 = InjectionInfo.m_bisWow64;
    CPEServer->InjectionInfo.m_Modules = InjectionInfo.m_Modules;
    CPEServer->InjectionInfo.NumberOfModules = InjectionInfo.NumberOfModules;
    CPEServer->InjectionInfo.pRelocateAddress = InjectionInfo.pRelocateAddress;

    CPEServer->m_StaticTls.m_RVATlsDir = CPE->m_StaticTls.m_RVATlsDir;
    CPEServer->m_StaticTls.m_RVATlsDirSize = CPE->m_StaticTls.m_RVATlsDirSize;

    CPEServer->m_pImageBase = CPE->m_pImageBase;
    CPEServer->m_ImageSize = CPE->m_ImageSize;

    return CPEServer;
}

SocketBuffer *C_CConstructPEServer::ChangeToMinimal( C_CPEMinimalServer* CPE )
{
    SocketBuffer *buf = new SocketBuffer( 0 );

    buf->AddVar<Type_32>( CPE->m_ImageSize );
    buf->AddVar<Type_32>( CPE->iMachineType );
    buf->AddVar<Type_32>( CPE->iArchitecture );
    buf->AddVar<Type_32>( CPE->m_hEntryPoint );
    buf->AddVar( CPE->m_TlsCBs.size() );

    for ( auto &&it : CPE->m_TlsCBs )
    {
        buf->AddVar<Type_Pointer>( it.m_pRVA );
    }

    buf->AddVar( CPE->m_Sections.size() );

    for ( auto &&it : CPE->m_Sections )
    {
        buf->AddVar<Type_32>( it.GetVirtualFlags() );
        buf->AddVar<Type_32>( it.m_VirtualSize );
        buf->AddVar<Type_32>( it.m_hRVA );
        buf->AddVar<Type_Array>( it.m_Buffer.m_pData , it.m_Buffer.m_Size );
    }

    buf->AddVar<Type_Array>( CPE->m_RoutineArgs.m_pData , CPE->m_RoutineArgs.m_Size );
    buf->AddVar<Type_Array>( CPE->bDLL_Main_Start.m_pData , CPE->bDLL_Main_Start.m_Size );
    buf->AddVar<Type_32>( CPE->m_StaticTls.m_RVATlsDir );
    buf->AddVar<Type_32>( CPE->m_StaticTls.m_RVATlsDirSize );

    return buf;
}

uHEX C_CPEMinimalServer::GetFunctionReadPEFromMem( const PCHAR pcFunctionName , const stdString &sModuleName )
{
    HEX HexOffset = 0;

    bool bIsForwarded = false;

    Pointer pRemotedModuleAddress = nullptr;

    int SlotModule = -1;

    for ( size_t i = 0; i < InjectionInfo.m_Modules.size(); i++ )
    {
        if ( !_stricmp( InjectionInfo.m_Modules[ i ].sModuleName.c_str() , AutoConvertC( sModuleName.c_str() ) ) )
        {
            pRemotedModuleAddress = InjectionInfo.m_Modules[ i ].pModuleAddress;
            SlotModule = ( int ) i;
        }
    }

    if ( SlotModule == -1 )
    {
        CONSOLEDEBUG( TEXT( "GetFunctionReadPE: Couldn't find %s for module %s\n" ) , AutoConvertS( pcFunctionName ) , sModuleName.c_str() );
        return 0;
    }

    // Gotcha.
    if ( pRemotedModuleAddress != nullptr )
    {
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

                            HexOffset = GetFunctionReadPEFromMem( ( PCHAR ) sRealFuncName.c_str() , sModule.c_str() );

                            bIsForwarded = true;
                        }
                    }
                    else
                    {
                        Pointer pFunctionAddress = ( Pointer ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw32( pNtHeaders , hRVAFunction ) );

                        HexOffset = ( HEX ) RawToRva32( pNtHeaders , ( uHEX32 ) ( ( HEX ) pFunctionAddress - ( HEX ) pDosHeader ) );
                    }

                    goto FoundExport;

                    return 0;
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

                                    HexOffset = GetFunctionReadPEFromMem( ( PCHAR ) sRealFuncName.c_str() , sModule.c_str() );

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

                            HexOffset = GetFunctionReadPEFromMem( ( PCHAR ) sRealFuncName.c_str() , sModule.c_str() );

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

                                    HexOffset = GetFunctionReadPEFromMem( ( PCHAR ) sRealFuncName.c_str() , sModule.c_str() );

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

        return hFinal;
    }
    else
    {
        CONSOLEDEBUG( TEXT( "Couldn't find module %s from process\n" ) , sModuleName.c_str() );
        return 0;
    }
}

Pointer C_CPEMinimalServer::GetAFromSections( Pointer pFileOffset )
{
    size_t Slot = 0;
    for ( auto &&it : m_Sections )
    {
        if ( ( size_t ) pFileOffset >= it.m_Buffer.m_Size
             && ( size_t ) pFileOffset < ( ( size_t ) m_SectionsOffsets[ Slot ] + it.m_Buffer.m_Size ) )
            return ( Pointer ) ( ( HEX ) it.m_Buffer.P( ( ( HEX ) pFileOffset - ( HEX ) m_SectionsOffsets[ Slot ] ) ) );

        Slot++;
    }

    return nullptr;
}

bool C_CPEMinimalServer::ResolveImports()
{
    if ( m_Imports.empty() )
        return false;

    for ( auto &&it : m_Imports )
    {
        if ( iArchitecture == M_x64 )
        {
            auto pFI = ( pFunctionImport64 ) GetAFromSections( it.m_pFileOffset );

            pFI->u.m_hFunction = ( uHEX64 ) GetFunctionReadPEFromMem( ( PCHAR ) it.m_sFunctionName.c_str()
                                                                      , AutoConvertS( it.m_sModuleName.c_str() ) );

            if ( pFI->u.m_hFunction == 0 )
            {
                CONSOLEDEBUG( TEXT( "Failed to import function: %s from module: %s\n" ) , AutoConvertS( it.m_sFunctionName.c_str() )
                              , AutoConvertS( it.m_sModuleName.c_str() ) );
                return false;
            }
        }
        else if ( iArchitecture == M_x86 )
        {
            auto pFI = ( pFunctionImport32 ) GetAFromSections( it.m_pFileOffset );

            pFI->u.m_hFunction = ( uHEX32 ) GetFunctionReadPEFromMem( ( PCHAR ) it.m_sFunctionName.c_str()
                                                                      , AutoConvertS( it.m_sModuleName.c_str() ) );

            if ( pFI->u.m_hFunction == 0 )
            {
                CONSOLEDEBUG( TEXT( "Failed to import function: %s from module: %s\n" ) , AutoConvertS( it.m_sFunctionName.c_str() )
                              , AutoConvertS( it.m_sModuleName.c_str() ) );
                return false;
            }
        }
        else
            return false;
    }

    return true;
}