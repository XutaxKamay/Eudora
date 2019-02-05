#include "Includes.hxx"
#include "CPE.hxx"
#include "CPE_Minimal.hxx"

C_CConstructPE g_CConstructPE;

const String* GetRelocationName( int iType )
{
    switch ( iType )
    {
        case reloc_32:
            return TEXT( "reloc_32" );
            break;
        case reloc_64:
            return TEXT( "reloc_64" );
            break;
        case reloc_ABSOLUTE:
            return TEXT( "reloc_ABSOLUTE" );
            break;
    }

    return TEXT( "reloc_UNKNOWN" );
}

Pointer C_CPE::GetAFromSections( Pointer pFileOffset )
{
    for ( auto &&it : m_Sections )
    {
        if ( ( size_t ) pFileOffset >= ( size_t ) it.m_hFileOffset
             && ( size_t ) pFileOffset < ( ( size_t ) it.m_hFileOffset + ( size_t ) it.m_FileSize ) )
            return ( Pointer ) ( ( HEX ) it.m_Buffer.P( ( ( HEX ) pFileOffset - ( HEX ) it.m_hFileOffset ) ) );
    }

    return nullptr;
}

uHEX32 C_CSection::GetVirtualFlags()
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

bool C_CPE::ConstructSections( PIMAGE_DOS_HEADER pDosHeader )
{
    auto pParentNtHeaders = GetParentNtHeaders( pDosHeader );

    auto pSection = IMAGE_FIRST_SECTION( pParentNtHeaders );

    for ( auto i = 0; i < pParentNtHeaders->FileHeader.NumberOfSections; i++ )
    {
        auto CurSection = pSection[ i ];

        auto FileSize = CurSection.SizeOfRawData;

        if ( CurSection.PointerToRawData == 0 )
            CurSection.SizeOfRawData = 0;

        if ( CurSection.Misc.VirtualSize == 0 )
            CurSection.Misc.VirtualSize = CurSection.SizeOfRawData;
        else
        {
            if ( CurSection.SizeOfRawData > CurSection.Misc.VirtualSize )
            {
                CurSection.SizeOfRawData = CurSection.Misc.VirtualSize;
            }
        }

        auto pFileOffset = ( Pointer ) ( ( HEX ) pDosHeader + CurSection.PointerToRawData );

        SocketBuffer bsSection( pFileOffset , ( size_t ) FileSize );

        C_CSection CSection( CurSection.VirtualAddress
                             , CurSection.Misc.VirtualSize
                             , CurSection.PointerToRawData , FileSize , std::string( ( PCHAR ) CurSection.Name , sizeof( CurSection.Name ) ) , bsSection , CurSection.Characteristics );

        /*
        if ( CurSection.SizeOfRawData < CurSection.Misc.VirtualSize )
        {
            CSection.m_Buffer.resize( CurSection.Misc.VirtualSize );
            CSection.m_Buffer.assign( CSection.m_Buffer.size() , 0 );
        }
        */

        m_Sections.push_back( CSection );

        CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "Construct section: %s at 0x%p , Raw: 0x%p , Rva: 0x%p , VirtualSize: 0x%p , FileSize: 0x%p\n" )
                           , AutoConvertS( CSection.m_sName.c_str() ) , ( m_Sections.end() - 1 )->m_Buffer.P()
                           , CSection.m_hFileOffset , CSection.m_hRVA , CSection.m_VirtualSize , CSection.m_FileSize );
    }

    return true;
}

bool C_CPE::ConstructExceptions( PIMAGE_DOS_HEADER pDosHeader )
{
    auto pParentNtHeaders = GetParentNtHeaders( pDosHeader );

    if ( iArchitecture == M_x86 )
    {
        auto pNtHeaders = ( pNTHeaders32 ) pParentNtHeaders;

        auto NbOfEntries = pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXCEPTION ].Size / sizeof( IMAGE_RUNTIME_FUNCTION_ENTRY );

        if ( NbOfEntries == 0 )
            goto NoExceptions;

        auto pRuntimeFunctionEntry = ( PIMAGE_RUNTIME_FUNCTION_ENTRY )
            ( ( HEX ) pDosHeader
              + ( HEX ) RvaToRaw32( pNtHeaders
              , ( uHEX32 ) pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXCEPTION ].VirtualAddress ) );

        for ( decltype( NbOfEntries ) i = 0; i < NbOfEntries; i++ )
        {
            m_Exceptions.push_back( C_CExcept( ( Pointer ) ( HEX64 ) ( RvaToRaw32( pNtHeaders , pRuntimeFunctionEntry[ NbOfEntries ].BeginAddress ) ) ,
                ( Pointer ) ( HEX64 ) ( RvaToRaw32( pNtHeaders , pRuntimeFunctionEntry[ NbOfEntries ].EndAddress ) )
                                    , pRuntimeFunctionEntry[ NbOfEntries ].BeginAddress
                                    , pRuntimeFunctionEntry[ NbOfEntries ].EndAddress
                                    , pRuntimeFunctionEntry[ NbOfEntries ].UnwindData
                                    , ( uHEX32 ) ( ( HEX ) &pRuntimeFunctionEntry[ NbOfEntries ] - ( HEX ) pDosHeader ) , ( uHEX32 ) i ) );
        }
    }
    else
    {
        auto pNtHeaders = ( pNTHeaders64 ) pParentNtHeaders;

        auto NbOfEntries = pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXCEPTION ].Size / sizeof( IMAGE_RUNTIME_FUNCTION_ENTRY );

        if ( NbOfEntries == 0 )
            goto NoExceptions;

        auto pRuntimeFunctionEntry = ( PIMAGE_RUNTIME_FUNCTION_ENTRY )
            ( ( HEX ) pDosHeader
              + ( HEX ) RvaToRaw64( pNtHeaders
              , ( uHEX32 ) pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXCEPTION ].VirtualAddress ) );

        for ( decltype( NbOfEntries ) i = 0; i < NbOfEntries; i++ )
        {
            m_Exceptions.push_back( C_CExcept( ( Pointer ) ( HEX64 ) ( RvaToRaw64( pNtHeaders , pRuntimeFunctionEntry[ NbOfEntries ].BeginAddress ) ) ,
                ( Pointer ) ( HEX64 ) ( RvaToRaw64( pNtHeaders , pRuntimeFunctionEntry[ NbOfEntries ].EndAddress ) )
                                    , pRuntimeFunctionEntry[ NbOfEntries ].BeginAddress
                                    , pRuntimeFunctionEntry[ NbOfEntries ].EndAddress
                                    , pRuntimeFunctionEntry[ NbOfEntries ].UnwindData
                                    , ( uHEX32 ) ( ( HEX ) &pRuntimeFunctionEntry[ NbOfEntries ] - ( HEX ) pDosHeader ) , ( uHEX32 ) i ) );
        }
    }

    CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "Constructed exceptions: %i\n" ) , m_Exceptions.size() );

NoExceptions:
    return true;
}

//bool C_CPE::ConstructDebug( PIMAGE_DOS_HEADER pDosHeader )
//{
//	auto pParentNtHeaders = GetParentNtHeaders( pDosHeader );
//
//	if ( iArchitecture == M_x86 )
//	{
//
//	}
//	else
//	{
//		auto pNtHeaders = ( pNTHeaders64 ) pParentNtHeaders;
//
//		if ( pParentNtHeaders->FileHeader.Characteristics & IMAGE_FILE_DEBUG_STRIPPED )
//		{
//			HEX DbgSize = pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_DEBUG ].Size / sizeof( IMAGE_DEBUG_DIRECTORY );
//
//			if ( DbgSize == 0 )
//				goto NoDebug;
//
//			auto pDebugDirectory = ( PIMAGE_DEBUG_DIRECTORY ) ( ( HEX ) pDosHeader
//																+ RawToRva64( pNtHeaders
//																, ( uHEX32 ) pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_DEBUG ].VirtualAddress ) );
//
//			PIMAGE_DEBUG_MISC DebugMisc = ( PIMAGE_DEBUG_MISC ) ( ( HEX ) pDosHeader + ( HEX ) pDebugDirectory->PointerToRawData );
//
//			if ( DbgSize != 1
//				 || pDebugDirectory->Type != IMAGE_DEBUG_TYPE_MISC
//				 || DebugMisc->DataType != IMAGE_DEBUG_MISC_EXENAME )
//			{
//				goto NoDebug;
//			}
//			else
//			{
//				if ( !DebugMisc->Unicode )
//				{
//					std::string DbgName = std::string( ( const char* ) DebugMisc->Data );
//				}
//				else
//				{
//					std::wstring DbgName = std::wstring( ( const wchar_t* ) DebugMisc->Data );
//				}
//
//			}
//		}
//		else
//		{
//			auto pSection = IMAGE_FIRST_SECTION64( pNtHeaders );
//		}
//	}
//
//NoDebug:
//	return true;
//}

bool C_CPE::ConstructIATs( PIMAGE_DOS_HEADER pDosHeader )
{
    auto pParentNtHeaders = GetParentNtHeaders( pDosHeader );

    PIMAGE_SECTION_HEADER FoundSection = nullptr;

    if ( iArchitecture == M_x86 )
    {
        auto pNtHeaders = ( pNTHeaders32 ) pParentNtHeaders;

        auto pImportDescriptor = ( PIMAGE_IMPORT_DESCRIPTOR )
            ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw32( pNtHeaders
              , ( uHEX32 ) pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_IMPORT ].VirtualAddress , &FoundSection ) );

        if ( pImportDescriptor != nullptr )
        {
            while ( pImportDescriptor->Name != 0 )
            {
                auto pModuleName = ( Pointer ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw32( pNtHeaders , ( uHEX32 ) pImportDescriptor->Name ) );

                auto pcModuleNameInMem = ( PCHAR ) GetAFromSections( ( Pointer ) ( ( HEX ) pModuleName - ( HEX ) pDosHeader ) );

                auto lenModule = strlen( pcModuleNameInMem );

                memset( pcModuleNameInMem , 0xCC , lenModule );

                auto sModuleName = std::string( ( PCHAR ) pModuleName );

                m_ListImportModules.push_back( sModuleName );

                if ( pImportDescriptor->FirstThunk != 0 )
                {
                    auto pThunkData = ( PIMAGE_THUNK_DATA32 ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw32( pNtHeaders
                                                                , ( uHEX32 ) pImportDescriptor->FirstThunk ) );

                    while ( pThunkData != nullptr && pThunkData->u1.AddressOfData != 0 )
                    {
                        if ( IMAGE_SNAP_BY_ORDINAL32( pThunkData->u1.Ordinal ) )
                        {
                            uHEX OrdinalNb = ( uHEX ) ( uHEX ) IMAGE_ORDINAL32( pThunkData->u1.Ordinal );

                            char buf[ 16 ];

                            sprintf_s( buf , "%I64i" , OrdinalNb );

                            std::string sFunctionOrdinalName( buf );

                            //auto pcFunctionOrdinalNameInMem = ( PCHAR ) GetAFromSections( ( Pointer ) ( ( HEX ) IMAGE_ORDINAL32( pThunkData->u1.Ordinal ) - ( HEX ) pDosHeader ) );

                            //auto lenFunctionOrdinalName = strlen( pcFunctionOrdinalNameInMem );

                            //memset( pcFunctionOrdinalNameInMem , 0xCC , lenFunctionOrdinalName );

                            C_CImport CImport( sFunctionOrdinalName , sModuleName , ( Pointer ) ( ( HEX ) pThunkData - ( HEX ) pDosHeader ) );

                            m_Imports.push_back( CImport );

                            CONSOLEColorDEBUG( FOREGROUND_ROSE , TEXT( "Construct import function ordinal: %i , module: %s (Raw: 0x%p, Mem: 0x%p)\n" ) , AutoConvertS( sFunctionOrdinalName.c_str() )
                                               , AutoConvertS( sModuleName.c_str() ) , CImport.m_pFileOffset , GetAFromSections( CImport.m_pFileOffset ) );
                        }
                        else
                        {
                            PIMAGE_IMPORT_BY_NAME ImportByName = ( PIMAGE_IMPORT_BY_NAME ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw32( pNtHeaders
                                                                                             , ( uHEX32 ) pThunkData->u1.AddressOfData ) );

                            std::string sFunctionName( ( PCHAR ) ImportByName->Name );

                            auto pcFunctionNameInMem = ( PCHAR ) GetAFromSections( ( Pointer ) ( ( HEX ) ImportByName->Name - ( HEX ) pDosHeader ) );

                            auto lenFunctionName = strlen( pcFunctionNameInMem );

                            memset( pcFunctionNameInMem , 0xCC , lenFunctionName );

                            C_CImport CImport( sFunctionName , sModuleName , ( Pointer ) ( ( HEX ) pThunkData - ( HEX ) pDosHeader ) );

                            m_Imports.push_back( CImport );

                            CONSOLEColorDEBUG( FOREGROUND_ROSE , TEXT( "Construct import function: %s , module: %s (Raw: 0x%p, Mem: 0x%p)\n" ) , AutoConvertS( sFunctionName.c_str() )
                                               , AutoConvertS( sModuleName.c_str() ) , CImport.m_pFileOffset , GetAFromSections( CImport.m_pFileOffset ) );
                        }

                        pThunkData++;
                    }
                }

                pImportDescriptor++;
            }
        }
    }
    else
    {
        auto pNtHeaders = ( pNTHeaders64 ) pParentNtHeaders;

        auto pImportDescriptor = ( PIMAGE_IMPORT_DESCRIPTOR )
            ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw64( pNtHeaders
              , ( uHEX32 ) pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_IMPORT ].VirtualAddress , &FoundSection ) );

        if ( pImportDescriptor != nullptr )
        {
            while ( pImportDescriptor->Name != 0 )
            {
                auto pModuleName = ( Pointer ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw64( pNtHeaders , ( uHEX32 ) pImportDescriptor->Name ) );

                auto pcModuleNameInMem = ( PCHAR ) GetAFromSections( ( Pointer ) ( ( HEX ) pModuleName - ( HEX ) pDosHeader ) );

                auto lenModule = strlen( pcModuleNameInMem );

                memset( pcModuleNameInMem , 0xCC , lenModule );

                auto sModuleName = std::string( ( PCHAR ) pModuleName );

                m_ListImportModules.push_back( sModuleName );

                if ( pImportDescriptor->FirstThunk != 0 )
                {
                    auto pThunkData = ( PIMAGE_THUNK_DATA64 ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw64( pNtHeaders
                                                                , ( uHEX32 ) pImportDescriptor->FirstThunk ) );

                    while ( pThunkData != nullptr && pThunkData->u1.AddressOfData != 0 )
                    {
                        if ( IMAGE_SNAP_BY_ORDINAL64( pThunkData->u1.Ordinal ) )
                        {
                            uHEX OrdinalNb = ( uHEX ) ( uHEX ) IMAGE_ORDINAL64( pThunkData->u1.Ordinal );

                            char buf[ 16 ];

                            sprintf_s( buf , "%I64i" , OrdinalNb );

                            std::string sFunctionOrdinalName( buf );

                            //auto pcFunctionOrdinalNameInMem = ( PCHAR ) GetAFromSections( ( Pointer ) ( ( HEX ) IMAGE_ORDINAL64( pThunkData->u1.Ordinal ) - ( HEX ) pDosHeader ) );

                            //auto lenFunctionOrdinalName = strlen( pcFunctionOrdinalNameInMem );

                            //memset( pcFunctionOrdinalNameInMem , 0xCC , lenFunctionOrdinalName );

                            C_CImport CImport( sFunctionOrdinalName , sModuleName , ( Pointer ) ( ( HEX ) pThunkData - ( HEX ) pDosHeader ) );

                            m_Imports.push_back( CImport );

                            CONSOLEColorDEBUG( FOREGROUND_ROSE , TEXT( "Construct import function ordinal: %i , module: %s (Raw: 0x%p, Mem: 0x%p)\n" ) , AutoConvertS( sFunctionOrdinalName.c_str() )
                                               , AutoConvertS( sModuleName.c_str() ) , CImport.m_pFileOffset , GetAFromSections( CImport.m_pFileOffset ) );
                        }
                        else
                        {
                            PIMAGE_IMPORT_BY_NAME ImportByName = ( PIMAGE_IMPORT_BY_NAME ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw64( pNtHeaders
                                                                                             , ( uHEX32 ) pThunkData->u1.AddressOfData ) );

                            std::string sFunctionName( ( PCHAR ) ImportByName->Name );

                            auto pcFunctionNameInMem = ( PCHAR ) GetAFromSections( ( Pointer ) ( ( HEX ) ImportByName->Name - ( HEX ) pDosHeader ) );

                            auto lenFunctionName = strlen( pcFunctionNameInMem );

                            memset( pcFunctionNameInMem , 0xCC , lenFunctionName );

                            C_CImport CImport( sFunctionName , sModuleName , ( Pointer ) ( ( HEX ) pThunkData - ( HEX ) pDosHeader ) );

                            m_Imports.push_back( CImport );

                            CONSOLEColorDEBUG( FOREGROUND_ROSE , TEXT( "Construct import function: %s , module: %s (Raw: 0x%p, Mem: 0x%p)\n" ) , AutoConvertS( sFunctionName.c_str() )
                                               , AutoConvertS( sModuleName.c_str() ) , CImport.m_pFileOffset , GetAFromSections( CImport.m_pFileOffset ) );
                        }

                        pThunkData++;
                    }
                }

                pImportDescriptor++;
            }
        }
    }

#ifdef _UNICODE
    auto CompareNoCase = [] ( C_CImport first , C_CImport second )
    {
        size_t i = 0;

        while ( ( i < first.m_sFunctionName.length() ) && ( i < second.m_sFunctionName.length() ) )
        {
            if ( towlower( first.m_sFunctionName[ i ] ) < towlower( second.m_sFunctionName[ i ] ) )
                return true;
            else if ( towlower( first.m_sFunctionName[ i ] ) > towlower( second.m_sFunctionName[ i ] ) )
                return false;

            i++;
        }

        if ( first.m_sFunctionName.length() < second.m_sFunctionName.length() )
            return true;
        else
            return false;
    };
#else
    auto CompareNoCase = [] ( C_CImport first , C_CImport second )
    {
        size_t i = 0;

        while ( ( i < first.m_sFunctionName.length() ) && ( i < second.m_sFunctionName.length() ) )
        {
            if ( tolower( first.m_sFunctionName[ i ] ) < tolower( second.m_sFunctionName[ i ] ) )
                return true;
            else if ( tolower( first.m_sFunctionName[ i ] ) > tolower( second.m_sFunctionName[ i ] ) )
                return false;

            i++;
        }

        if ( first.m_sFunctionName.length() < second.m_sFunctionName.length() )
            return true;
        else
            return false;
    };
#endif

    std::sort( m_Imports.begin() , m_Imports.end() , CompareNoCase );

    m_ListImportModules.unique();

    return true;
}

bool C_CPE::_ConstructRelocs( PIMAGE_DOS_HEADER pDosHeader , uHEX &hNumberOfRelocations , PWORD &pwRelocationAddress , Bytes &bRelocationBlock )
{
    for ( uHEX i = 0; i < hNumberOfRelocations; i++ )
    {
        int iType = reloc_UNKNOWN;
        Pointer pFileOffset = nullptr;
        Pointer pValue = nullptr;

        WORD wType = IMR_RELTYPE( *pwRelocationAddress );

        switch ( wType )
        {
            case IMAGE_REL_BASED_ABSOLUTE:
            {
                iType = reloc_ABSOLUTE;
                break;
            }
            case IMAGE_REL_BASED_HIGHLOW:
            {
                uHEX hRawAdr = ( uHEX ) ( ( uHEX ) bRelocationBlock + IMR_RELOFFSET( *pwRelocationAddress ) );
                pFileOffset = ( Pointer ) ( hRawAdr - ( HEX64 ) pDosHeader );
                iType = reloc_32;
                CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "Construct reloc_32: Mem: 0x%p , Raw: 0x%p\n" ) , GetAFromSections( pFileOffset ) , pFileOffset );
                break;
            }
            case IMAGE_REL_BASED_DIR64:
            {
                uHEX hRawAdr = ( uHEX ) ( ( uHEX ) bRelocationBlock + IMR_RELOFFSET( *pwRelocationAddress ) );
                pFileOffset = ( Pointer ) ( hRawAdr - ( HEX64 ) pDosHeader );
                iType = reloc_64;
                CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "Construct reloc_64: Mem: 0x%p , Raw: 0x%p\n" ) , GetAFromSections( pFileOffset ) , pFileOffset );
                break;
            }
            default:
            {
                uHEX hRawAdr = ( uHEX ) ( ( uHEX ) bRelocationBlock + IMR_RELOFFSET( *pwRelocationAddress ) );
                pFileOffset = ( Pointer ) ( hRawAdr - ( HEX64 ) pDosHeader );
                iType = reloc_UNKNOWN;
                CONSOLEDEBUG( TEXT( "Construct: unknown relocation! ( Type: %i )\n" ) , wType );
                break;
            }
        }

        if ( pFileOffset != nullptr )
        {
            pValue = *( pPointer ) GetAFromSections( pFileOffset );
        }

        m_Relocs.push_back( C_CReloc( pValue , pFileOffset , iType ) );

        ++pwRelocationAddress;
    }

    return true;
}

bool C_CPE::ConstructRelocs( PIMAGE_DOS_HEADER pDosHeader )
{
    auto pParentNtHeaders = GetParentNtHeaders( pDosHeader );

    if ( !( pParentNtHeaders->FileHeader.Characteristics & IMAGE_FILE_RELOCS_STRIPPED ) )
    {
        PIMAGE_SECTION_HEADER FoundSection;

        if ( iArchitecture == M_x86 )
        {
            auto pNtHeaders = ( pNTHeaders32 ) pParentNtHeaders;

            auto pImageBaseRelocation = ( PIMAGE_BASE_RELOCATION )
                ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw32( pNtHeaders , ( uHEX32 ) pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_BASERELOC ].VirtualAddress , &FoundSection ) );

            auto HexSizeOfRelocation = pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_BASERELOC ].Size;

            if ( HexSizeOfRelocation > 0 && pImageBaseRelocation != nullptr )
            {
                auto HexEndOfRelocation = ( HEX ) pImageBaseRelocation + ( HEX ) HexSizeOfRelocation;

                while ( ( HEX ) pImageBaseRelocation < HexEndOfRelocation )
                {
                    auto NumberOfRelocations = ( pImageBaseRelocation->SizeOfBlock - ( DWORD ) sizeof( IMAGE_BASE_RELOCATION ) ) / sizeof( WORD );

                    auto pwRelocationAddress = ( PWORD ) ( pImageBaseRelocation + 1 );

                    auto bRelocationBlock = ( Bytes ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw32( pNtHeaders , ( uHEX32 ) pImageBaseRelocation->VirtualAddress ) );

                    if ( !_ConstructRelocs( pDosHeader , NumberOfRelocations , pwRelocationAddress , bRelocationBlock ) )
                        goto FailedRelocs;

                    pImageBaseRelocation = ( PIMAGE_BASE_RELOCATION ) pwRelocationAddress;
                }
            }
        }
        else
        {
            auto pNtHeaders = ( pNTHeaders64 ) pParentNtHeaders;

            auto pImageBaseRelocation = ( PIMAGE_BASE_RELOCATION )
                ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw64( pNtHeaders , ( uHEX32 ) pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_BASERELOC ].VirtualAddress , &FoundSection ) );

            auto HexSizeOfRelocation = pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_BASERELOC ].Size;

            if ( HexSizeOfRelocation > 0 && pImageBaseRelocation != nullptr )
            {
                auto HexEndOfRelocation = ( HEX ) pImageBaseRelocation + ( HEX ) HexSizeOfRelocation;

                while ( ( HEX ) pImageBaseRelocation < HexEndOfRelocation )
                {
                    auto NumberOfRelocations = ( pImageBaseRelocation->SizeOfBlock - ( DWORD ) sizeof( IMAGE_BASE_RELOCATION ) ) / sizeof( WORD );

                    auto pwRelocationAddress = ( PWORD ) ( pImageBaseRelocation + 1 );

                    auto bRelocationBlock = ( Bytes ) ( ( HEX ) pDosHeader + ( HEX ) RvaToRaw64( pNtHeaders , ( uHEX32 ) pImageBaseRelocation->VirtualAddress ) );

                    if ( !_ConstructRelocs( pDosHeader , NumberOfRelocations , pwRelocationAddress , bRelocationBlock ) )
                        goto FailedRelocs;

                    pImageBaseRelocation = ( PIMAGE_BASE_RELOCATION ) pwRelocationAddress;
                }
            }
        }

        for ( auto &&i : m_Sections )
        {
            if ( i.m_hFileOffset == FoundSection->PointerToRawData )
            {
                memset( i.m_Buffer.m_pData , 0xCC , i.m_Buffer.m_Size );
            }
        }

        auto SortByLowerToHigher = [] ( C_CReloc reloc1 , C_CReloc reloc2 )
        {
            if ( ( HEX ) reloc1.m_pFileOffset > ( HEX ) reloc2.m_pFileOffset )
                return true;
            else
                return false;
        };

        std::sort( m_Relocs.begin() , m_Relocs.end() , SortByLowerToHigher );
    }

    return true;

FailedRelocs:

    CONSOLEDEBUG( TEXT( "Relocations Failed.\n" ) );
    return false;
}

bool C_CPE::ConstructTls( PIMAGE_DOS_HEADER pDosHeader )
{
    PIMAGE_SECTION_HEADER FoundSection;

    auto pParentNtHeaders = GetParentNtHeaders( pDosHeader );

    if ( iArchitecture == M_x86 )
    {
        auto pNtHeaders = ( pNTHeaders32 ) pParentNtHeaders;

        if ( pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_TLS ].Size == 0 )
            return true;

        m_StaticTls.m_RVATlsDir = pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_TLS ].VirtualAddress;
        m_StaticTls.m_RVATlsDirSize = pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_TLS ].Size;

        auto pTlsDir = ( PIMAGE_TLS_DIRECTORY32 ) ( ( HEX ) pDosHeader
                                                    + ( HEX ) RvaToRaw32( pNtHeaders
                                                    , ( uHEX32 ) pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_TLS ].VirtualAddress , &FoundSection ) );

        if ( pTlsDir != nullptr )
        {
            auto hImageBase = ( uHEX64 ) m_pImageBase;

            if ( pTlsDir->AddressOfCallBacks != 0 )
            {
                auto hTlsCallbacksRva = ( uHEX32 ) ( ( uHEX64 ) pTlsDir->AddressOfCallBacks - hImageBase );

                auto hTlsCallbacksRaw = ( HEX ) RvaToRaw32( pNtHeaders , hTlsCallbacksRva );

                auto pTlsCallbacks = ( puHEX32 ) ( ( HEX ) pDosHeader + hTlsCallbacksRaw );

                size_t i = 0;

                while ( pTlsCallbacks[ i ] != 0 )
                {
                    auto hTlsCallBackRVA = ( uHEX32 ) ( ( uHEX64 ) pTlsCallbacks[ i ] - hImageBase );

                    C_CTlsCB CTlsCB( ( Pointer ) ( uHEX64 ) hTlsCallBackRVA );

                    m_TlsCBs.push_back( CTlsCB );

                    CONSOLEColorDEBUG( FOREGROUND_YELLOW , TEXT( "TlsCallBack: Rva: 0x%p , Raw: 0x%p , Mem: 0x%p\n" ) , CTlsCB.m_pRVA
                                       , ( Pointer ) ( HEX ) RvaToRaw32( pNtHeaders , hTlsCallBackRVA )
                                       , GetAFromSections( ( Pointer ) ( HEX ) RvaToRaw32( pNtHeaders , hTlsCallBackRVA ) ) );

                    i++;
                }
            }
        }
    }
    else
    {
        auto pNtHeaders = ( pNTHeaders64 ) pParentNtHeaders;

        if ( pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_TLS ].Size == 0 )
            return true;

        m_StaticTls.m_RVATlsDir = pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_TLS ].VirtualAddress;
        m_StaticTls.m_RVATlsDirSize = pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_TLS ].Size;

        auto pTlsDir = ( PIMAGE_TLS_DIRECTORY64 ) ( ( HEX ) pDosHeader
                                                    + ( HEX ) RvaToRaw64( pNtHeaders
                                                    , ( uHEX32 ) pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_TLS ].VirtualAddress , &FoundSection ) );

        if ( pTlsDir != nullptr )
        {
            auto hImageBase = ( uHEX64 ) m_pImageBase;

            if ( pTlsDir->AddressOfCallBacks != 0 )
            {
                auto hTlsCallbacksRva = ( uHEX32 ) ( pTlsDir->AddressOfCallBacks - hImageBase );

                auto hTlsCallbacksRaw = ( HEX ) RvaToRaw64( pNtHeaders , hTlsCallbacksRva );

                auto pTlsCallbacks = ( puHEX64 ) ( ( HEX ) pDosHeader + hTlsCallbacksRaw );

                size_t i = 0;

                while ( pTlsCallbacks[ i ] )
                {
                    auto hTlsCallBackRVA = ( uHEX32 ) ( pTlsCallbacks[ i ] - hImageBase );

                    C_CTlsCB CTlsCB( ( Pointer ) ( uHEX64 ) hTlsCallBackRVA );

                    m_TlsCBs.push_back( CTlsCB );

                    CONSOLEColorDEBUG( FOREGROUND_YELLOW , TEXT( "TlsCallBack: Rva: 0x%p , Raw: 0x%p , Mem: 0x%p\n" ) , CTlsCB.m_pRVA
                                       , ( Pointer ) ( HEX ) RvaToRaw64( pNtHeaders , hTlsCallBackRVA )
                                       , GetAFromSections( ( Pointer ) ( HEX ) RvaToRaw64( pNtHeaders , hTlsCallBackRVA ) ) );

                    i++;
                }
            }
        }
    }

    //m_SectionsToRemove.push_back( FoundSection );

    return true;
}

bool C_CPE::Construct( PIMAGE_DOS_HEADER pDosHeader )
{
    if ( pDosHeader->e_magic != IMAGE_DOS_SIGNATURE )
        return false;

    auto pParentNtHeaders = GetParentNtHeaders( pDosHeader );

    if ( pParentNtHeaders->FileHeader.Machine == IMAGE_FILE_MACHINE_I386 )
    {
        iArchitecture = M_x86;
    }
    else
    {
        iArchitecture = M_x64;
    }

    if ( pParentNtHeaders->FileHeader.Characteristics & IMAGE_FILE_DLL )
    {
        iMachineType = M_DLL;
    }
    else
    {
        iMachineType = M_EXE;
    }

    if ( iArchitecture == M_x64 )
    {
        auto pNtHeaders = ( pNTHeaders64 ) pParentNtHeaders;

        m_pImageBase = ( Pointer ) pNtHeaders->OptionalHeader.ImageBase;
        m_hEntryPoint = pNtHeaders->OptionalHeader.AddressOfEntryPoint;
        m_ImageSize = pNtHeaders->OptionalHeader.SizeOfImage;
    }
    else
    {
        auto pNtHeaders = ( pNTHeaders32 ) pParentNtHeaders;

        m_pImageBase = ( Pointer ) ( uHEX64 ) pNtHeaders->OptionalHeader.ImageBase;
        m_hEntryPoint = pNtHeaders->OptionalHeader.AddressOfEntryPoint;
        m_ImageSize = pNtHeaders->OptionalHeader.SizeOfImage;
    }

    if (
        !ConstructSections( pDosHeader )
        || !ConstructExceptions( pDosHeader )
        || !ConstructTls( pDosHeader )
        || !ConstructIATs( pDosHeader )
        || !ConstructRelocs( pDosHeader ) )
    {
        return false;
    }

    CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "Initialized: ImageBase: 0x%p, EntryPoint: 0x%p, ImageSize: 0x%p\n" ) , m_pImageBase , m_hEntryPoint , m_ImageSize );

    return true;
}

bool C_CPE::ProcessExceptions( N_VirtualMemory::VirtualBuffer& VirtualBuffer , N_Process::Process *Process )
{
    if ( m_Exceptions.empty() )
    {
        CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "No exceptions.\n" ) );
        return true;
    }

    /*
    for ( auto &&it : m_Exceptions )
    {
        if ( !RtlAddFunctionTable( ( PRUNTIME_FUNCTION ) ( ( HEX ) VirtualBuffer.pAddress + it.m_hRVARunTFunc ) , it.m_hIndex , ( DWORD64 ) VirtualBuffer.pAddress ) )
            return false;
    }
    */

    return true;
}

int C_CPE::RelocateSections( Pointer pNewImageBase )
{
    // No relocations
    if ( m_Relocs.empty() )
        return CPE_Relocated;

    HEX hDelta = ( HEX ) pNewImageBase - ( HEX ) m_pImageBase;

    if ( hDelta == 0x0 )
        return CPE_Relocated;

    int iCount = 0;

    for ( auto &&it : m_Relocs )
    {
        if ( it.m_pFileOffset == 0 )
        {
            if ( it.m_iType != reloc_ABSOLUTE )
            {
                CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "No file offset? Type: %s\n" ) , it.GetSType() );
            }

            continue;
        }

        Pointer pMemAddress = GetAFromSections( it.m_pFileOffset );

        if ( pMemAddress == nullptr )
        {
            CONSOLEColorDEBUG( FOREGROUND_RED , TEXT( "Relocation was stripped from memory? file offset: 0x%p type: %s\n" ) , it.m_pFileOffset , it.GetSType() );
            return CPE_RelocsFailed;
        }

        switch ( it.m_iType )
        {
            case reloc_32:
            {
                uHEX32 hBackup = ( uHEX32 ) ( uHEX ) it.m_pValue;
                *( puHEX32 ) pMemAddress = hBackup + ( uHEX32 ) hDelta;
                CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "RelocType: reloc_32: 0x%p -> 0x%p\n" ) , hBackup , *( puHEX32 ) pMemAddress );
                break;
            }
            case reloc_64:
            {
                Pointer pBackup = it.m_pValue;
                *( puHEX ) pMemAddress = ( uHEX ) pBackup + hDelta;
                CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "RelocType: reloc_64: 0x%p -> 0x%p\n" ) , pBackup , *( pPointer ) pMemAddress );
                break;
            }
            default:
            {
                CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "Unknown relocation! Mem: 0x%p Raw: 0x%p -> index: %i\n" ) , pMemAddress , it.m_pFileOffset , iCount );
                break;
            }
        }

        iCount++;
    }

    return CPE_Relocated;
}

bool C_CPE::ProcessImports( N_Process::Process *pProcess )
{
    if ( m_Imports.empty() )
        return false;

    for ( auto &&it : m_Imports )
    {
        if ( iArchitecture == M_x64 )
        {
            auto pFI = ( pFunctionImport64 ) GetAFromSections( it.m_pFileOffset );

            pFI->u.m_hFunction = ( uHEX64 ) pProcess->GetFunctionReadPE( ( PCHAR ) it.m_sFunctionName.c_str()
                                                                         , AutoConvertS( it.m_sModuleName.c_str() ) );

            if ( pFI->u.m_hFunction == 0 )
            {
                CONSOLEDEBUG( TEXT( "Failed to import function: %s from module: %s\n" ) , AutoConvertS( it.m_sFunctionName.c_str() )
                              , AutoConvertS( it.m_sModuleName.c_str() ) );
                return false;
            }
        }

        if ( iArchitecture == M_x86 )
        {
            auto pFI = ( pFunctionImport32 ) GetAFromSections( it.m_pFileOffset );

            pFI->u.m_hFunction = ( uHEX32 ) pProcess->GetFunctionReadPE( ( PCHAR ) it.m_sFunctionName.c_str()
                                                                         , AutoConvertS( it.m_sModuleName.c_str() ) );

            if ( pFI->u.m_hFunction == 0 )
            {
                CONSOLEDEBUG( TEXT( "Failed to import function: %s from module: %s\n" ) , AutoConvertS( it.m_sFunctionName.c_str() )
                              , AutoConvertS( it.m_sModuleName.c_str() ) );
                return false;
            }
        }
    }

    return true;
}

bool C_CPE::CopySections( N_VirtualMemory::VirtualBuffer &VirtualBuffer )
{
    for ( auto &&it : m_Sections )
    {
        if ( it.m_hFlags & IMAGE_SCN_MEM_DISCARDABLE || it.m_FileSize == 0 )
            continue;

        if ( !VirtualBuffer.ReplaceLocal( it.m_Buffer.P() , ( HEX ) it.m_hRVA , ( HEX ) it.m_FileSize ) )
            return false;
    }

    for ( auto &&it : m_Sections )
    {
        VirtualBuffer.Flags.ChangeInRange( it.m_hRVA , it.m_hRVA + it.m_VirtualSize , it.GetVirtualFlags() );
    }

    if ( !VirtualBuffer.RefreshFlags() )
        return false;

    return true;
}


bool C_CPE::ProcessStaticTls( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *Process )
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

bool C_CPE::CallTlsCBs( N_VirtualMemory::VirtualBuffer& VirtualBuffer , N_Process::Process *Process )
{
    if ( m_TlsCBs.empty() )
        return true;

    for ( auto &&it : m_TlsCBs )
    {
        Pointer pCallTls = ( Pointer ) ( ( HEX ) VirtualBuffer.pAddress + ( HEX ) it.m_pRVA );

        if ( iArchitecture == M_x86 )
        {
            Byte Start[] =
            {
                0x8B , 0x44 , 0x24 , 0x04 , 0xFF , 0x70 , 0x0C , 0x8B , 0x08 ,
                0xFF , 0x70 , 0x08 , 0xFF , 0x70 , 0x04 , 0xFF , 0xD1 , 0xC3
            };

            DllMain32 DllArgs( ( uHEX32 ) ( uHEX64 ) pCallTls
                               , ( uHEX32 ) ( uHEX64 ) VirtualBuffer.pAddress , DLL_PROCESS_ATTACH , 1 );

            it.pVRemotedArguments = new N_VirtualMemory::VirtualBuffer( sizeof( DllArgs ) , PAGE_READONLY
                                                                        , nullptr , Process->pProcess , TEXT( "pVRemotedArguments" ) , &DllArgs );

            if ( it.pVRemotedArguments->pAddress == nullptr )
                return false;

            it.pVRoutine = new N_VirtualMemory::VirtualBuffer( sizeof( Start ) , PAGE_EXECUTE
                                                               , nullptr , Process->pProcess , TEXT( "pVRoutine" ) , ( Pointer ) Start );

            if ( it.pVRoutine->pAddress == nullptr )
                return false;

            it.m_pTlsAttach = Process->CreateRemotlyThread( it.pVRoutine->pAddress , it.pVRemotedArguments->pAddress );
        }
        else
        {
            Byte Start[] =
            {
                0x48 , 0x8B , 0x01 , 0x4C , 0x8B , 0x41 , 0x10 , 0x8B ,
                0x51 , 0x18 , 0x48 , 0x8B , 0x49 , 0x08 , 0x48 , 0xFF , 0xE0
            };

            DllMain64 DllArgs( ( uHEX64 ) pCallTls
                               , ( uHEX64 ) VirtualBuffer.pAddress , DLL_PROCESS_ATTACH , 1 );

            it.pVRemotedArguments = new N_VirtualMemory::VirtualBuffer( sizeof( DllArgs ) , PAGE_READONLY
                                                                        , nullptr , Process->pProcess , TEXT( "pVRemotedArguments" ) , &DllArgs );

            if ( it.pVRemotedArguments->pAddress == nullptr )
                return false;

            it.pVRoutine = new N_VirtualMemory::VirtualBuffer( sizeof( Start ) , PAGE_EXECUTE
                                                               , nullptr , Process->pProcess , TEXT( "pVRoutine" ) , ( Pointer ) Start );

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

bool C_CPE::CallRoutine( N_VirtualMemory::VirtualBuffer& VirtualBuffer , N_Process::Process *Process )
{
    if ( iMachineType == M_DLL )
    {
        if ( iArchitecture == M_x86 )
        {
            Byte Start[] =
            {
                0x8B , 0x44 , 0x24 , 0x04 , 0xFF , 0x70 , 0x0C , 0x8B , 0x08 ,
                0xFF , 0x70 , 0x08 , 0xFF , 0x70 , 0x04 , 0xFF , 0xD1 , 0xC3
            };

            DllMain32 DllArgs( ( uHEX32 ) ( ( uHEX64 ) VirtualBuffer.pAddress + m_hEntryPoint )
                               , ( uHEX32 ) ( uHEX64 ) VirtualBuffer.pAddress , DLL_PROCESS_ATTACH , 1 );

            pVRemotedArguments = new N_VirtualMemory::VirtualBuffer( sizeof( DllArgs ) , PAGE_READONLY
                                                                     , nullptr , Process->pProcess , TEXT( "pVRemotedArguments" ) , &DllArgs );

            if ( pVRemotedArguments->pAddress == nullptr )
                return false;

            pVRoutine = new N_VirtualMemory::VirtualBuffer( sizeof( Start ) , PAGE_EXECUTE
                                                            , nullptr , Process->pProcess , TEXT( "pVRoutine" ) , ( Pointer ) Start );

            if ( pVRoutine->pAddress == nullptr )
                return false;

            pMainThread = Process->CreateRemotlyThread( pVRoutine->pAddress , pVRemotedArguments->pAddress );
        }
        else
        {
            Byte Start[] =
            {
                0x48 , 0x8B , 0x01 , 0x4C , 0x8B , 0x41 , 0x10 , 0x8B ,
                0x51 , 0x18 , 0x48 , 0x8B , 0x49 , 0x08 , 0x48 , 0xFF , 0xE0
            };

            DllMain64 DllArgs( ( ( uHEX64 ) VirtualBuffer.pAddress + m_hEntryPoint )
                               , ( uHEX64 ) VirtualBuffer.pAddress , DLL_PROCESS_ATTACH , 1 );

            pVRemotedArguments = new N_VirtualMemory::VirtualBuffer( sizeof( DllArgs ) , PAGE_READONLY
                                                                     , nullptr , Process->pProcess , TEXT( "pVRemotedArguments" ) , &DllArgs );

            if ( pVRemotedArguments->pAddress == nullptr )
                return false;

            pVRoutine = new N_VirtualMemory::VirtualBuffer( sizeof( Start ) , PAGE_EXECUTE
                                                            , nullptr , Process->pProcess , TEXT( "pVRoutine" ) , ( Pointer ) Start );

            if ( pVRoutine->pAddress == nullptr )
                return false;

            pMainThread = Process->CreateRemotlyThread( pVRoutine->pAddress , pVRemotedArguments->pAddress );
        }
    }
    else
    {
        if ( iArchitecture == M_x86 )
        {
            sWinMainExe<uHEX32> sWinMainExe( ( uHEX32 ) ( uHEX ) VirtualBuffer.pAddress , 0 , 0 , 0 , ( ( uHEX32 ) ( uHEX ) VirtualBuffer.pAddress + m_hEntryPoint ) );

            pVRemotedArguments = Process->VirtualAlloc( sizeof( sWinMainExe ) );

            if ( !pVRemotedArguments->ReplaceLocal( &sWinMainExe , 0 , sizeof( sWinMainExe ) ) )
                return false;

            Byte Start[] =
            {
                0x8B , 0x44 , 0x24 , 0x04 , 0xFF , 0x70 , 0x0C , 0x8B , 0x48 , 0x10 , 0xFF , 0x70 , 0x08 , 0xFF , 0x70 , 0x04,
                0xFF , 0x30 , 0xFF , 0xD1 , 0xC2 , 0x04
            };

            pVRoutine = Process->VirtualAlloc( sizeof( Start ) );

            if ( !pVRoutine->ReplaceLocal( &Start , 0 , sizeof( Start ) ) )
                return false;

            pMainThread = Process->CreateRemotlyThread( pVRoutine->pAddress , pVRemotedArguments->pAddress );
        }
        else
        {
            sWinMainExe<uHEX64> sWinMainExe( ( uHEX64 ) ( uHEX ) VirtualBuffer.pAddress , 0 , 0 , 0 , ( ( uHEX64 ) ( uHEX ) VirtualBuffer.pAddress + m_hEntryPoint ) );

            pVRemotedArguments = Process->VirtualAlloc( sizeof( sWinMainExe ) );

            if ( !pVRemotedArguments->ReplaceLocal( &sWinMainExe , 0 , sizeof( sWinMainExe ) ) )
                return false;

            Byte Start[] =
            {
                0x48 , 0x8B , 0x41 , 0x20 , 0x44 , 0x8B , 0x49 , 0x18 , 0x4C , 0x8B , 0x41 , 0x10 , 0x48 , 0x8B , 0x51 , 0x08,
                0x48 , 0x8B , 0x09 , 0x48 , 0xFF , 0xE0
            };

            pVRoutine = Process->VirtualAlloc( sizeof( Start ) );

            if ( !pVRoutine->ReplaceLocal( &Start , 0 , sizeof( Start ) ) )
                return false;

            pMainThread = Process->CreateRemotlyThread( pVRoutine->pAddress , pVRemotedArguments->pAddress );
        }
    }

    return true;
}

bool C_CPE::FreeRoutine( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *Process )
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

bool C_CPE::EndTlsCBs( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *Process )
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

            if ( !it.pVRemotedArguments->ReplaceLocal( &DllArgs , 0 , sizeof( DllArgs ) ) )
                return false;

            if ( it.pVRemotedArguments->pAddress == nullptr )
                return false;

            it.m_pTlsDetach = Process->CreateRemotlyThread( it.pVRoutine->pAddress , it.pVRemotedArguments->pAddress );
        }
        else
        {
            DllMain64 DllArgs( ( uHEX64 ) pCallTls
                               , ( uHEX64 ) VirtualBuffer.pAddress , DLL_PROCESS_DETACH , 1 );

            if ( !it.pVRemotedArguments->ReplaceLocal( &DllArgs , 0 , sizeof( DllArgs ) ) )
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

C_CPE* C_CConstructPE::Reconstruct( PIMAGE_DOS_HEADER pDosHeader )
{
    C_CPE *CPE = new C_CPE();

    if ( CPE != nullptr )
    {
        if ( CPE->Construct( pDosHeader ) )
        {
            N_Console::Print<FOREGROUND_GREEN>( TEXT( "Constructed own PE. ( 0x%p )\n" ) , pDosHeader );
        }
        else
        {
            N_Console::Print<FOREGROUND_RED>( TEXT( "Couldn't Construct own PE. ( 0x%p )\n" ) , pDosHeader );
            delete CPE;
            return nullptr;
        }
    }

    return CPE;
}