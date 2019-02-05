#include "Includes.hxx"
#include "Lib.hxx"

SigScanningFile::SigScanningFile( stdString _sProcessName , stdString _sName )
{
    sName = _sName;
    pProcess = new N_Process::Process( _sProcessName );
    pFirstOffset = nullptr;
}

SigScanningFile::SigScanningFile( HEX _HexProcID , stdString _sName )
{
    sName = _sName;
    pProcess = new N_Process::Process( _HexProcID );
    pFirstOffset = nullptr;
}

SigScanningFile::SigScanningFile( Pointer _pProcess , stdString _sName )
{
    sName = _sName;
    pProcess = new N_Process::Process( _pProcess );
    pFirstOffset = nullptr;
}

SigScanningFile::SigScanningFile( Pointer _pProcess , std::vector<Byte> bytes , stdString Module , stdString _sName )
{
    sName = _sName;
    pProcess = new N_Process::Process( _pProcess );
    pFirstOffset = nullptr;
    Scan( bytes , Module );
}

SigScanningFile::~SigScanningFile()
{
    OffsetsFound.clear();
    sName.clear();
    pFirstOffset = nullptr;
}

void SigScanningFile::FindOffsets( stdString sModuleName , Pointer pAddress , Pointer pTemp , HEX Size , std::vector<Byte> bytes , bool *pbFoundAOnce )
{
    // Set to false by first so we can tell we didn't find anything.

    if ( pbFoundAOnce != nullptr )
    {
        *pbFoundAOnce = false;
    }

    PIMAGE_DOS_HEADER pImageDosHeader = ( PIMAGE_DOS_HEADER ) pTemp;

    if ( pImageDosHeader == nullptr )
    {
        return;
    }

    PIMAGE_NT_HEADERS pImageNtHeaders = ( PIMAGE_NT_HEADERS ) ( ( HEX ) pImageDosHeader + pImageDosHeader->e_lfanew );

    if ( pImageNtHeaders == nullptr )
    {
        return;
    }

    // Size of module.

    HEX iDest = 0;

    // The signature.
    Bytes pbData = bytes.data();

    // The size of the signature.
    const HEX DataSize = bytes.size();

    // All the offsets found.

    std::vector<Pointer> pOffsetsFound;

    HEX StartAddress = pImageNtHeaders->OptionalHeader.ImageBase + IMAGE_FIRST_SECTION( pImageNtHeaders )[ 0 ].VirtualAddress;
    HEX EndAddress = pImageNtHeaders->OptionalHeader.ImageBase + pImageNtHeaders->OptionalHeader.SizeOfImage;

    HEX HexData = 0;
    HEX iData = 0;

    bool bFoundSignature = true;

    do
    {
        // Iterate byte by byte until we find the signature into our module.

        bFoundSignature = true;

        for ( iData = 0; iData < DataSize; iData++ )
        {
            HexData = *( pHEX ) &pbData[ iData ];

            if ( HexData >= StartAddress
                 && HexData < EndAddress
                 && ( DataSize - iData ) >= sizeof( HEX ) )
            {
                iData += sizeof( HEX ) - 1;
            }
            else
            {
                if ( ( ( Bytes ) ( ( HEX ) pTemp + iDest ) )[ iData ] != pbData[ iData ] )
                {
                    bFoundSignature = false;
                    break;
                }
            }
        }

        if ( bFoundSignature )
        {
            // If we found it, we get the address from the file, and convert it into a virtual address
            // So we can get the address while it's still in memory.

            HEX RvaAddress = RawToRvaOffset( ImageNtHeader( pTemp ) , ( uHEX32 ) iDest );

            // Check if somehow it wasn't into the sections.. (Shouldn't happen)

            if ( RvaAddress != 0 )
            {
                // Add the address found.

                if ( pFirstOffset == nullptr )
                    pFirstOffset = ( Pointer ) ( ( HEX ) pAddress + RvaAddress );

                pOffsetsFound.push_back( ( Pointer ) ( ( HEX ) pAddress + RvaAddress ) );
            }
        }

        iDest++;		// Increment the size by a byte so we can go on the next address of the module.

    } while ( iDest < Size );

    // Emplace all addresses found into its module name.

    sOffsetsFound TmpOffsetsFound;
    TmpOffsetsFound.sModuleName = sModuleName;
    TmpOffsetsFound.pOffsets = pOffsetsFound;
    TmpOffsetsFound.pModuleAddress = pAddress;
    OffsetsFound.push_back( TmpOffsetsFound );

    // We found atleast one address, so it's good.

    if ( ( pbFoundAOnce != nullptr ) && OffsetsFound.size() > 0 )
    {
        *pbFoundAOnce = true;
    }
}

void SigScanningFile::Scan( std::vector<Byte> bytes , stdString Module )
{
    pFirstOffset = nullptr;

    // Refresh every modules from the process to be sure we didn't miss anything.

    pProcess->RefreshGetModules();

    if ( Module != TEXT( "NoModules" ) )
    {
        // If the name of the module is given, search the signature.

        Pointer pModuleAddress = pProcess->FindModule( Module );

        if ( pModuleAddress != nullptr )
        {
            // Get the module path from its address.

            stdString sPathModule = pProcess->FindModulePath( ( Pointer ) pModuleAddress );

            // Read the file from the module path.

            HEX Size = 0;
            Pointer pTempModule = N_FileSystem::ReadFile( sPathModule , &Size );

            // Count how much time it took to get the address of the given signature. (benchmark)

            CTimer *Timer = new CTimer();

            FindOffsets( sPathModule , pModuleAddress , pTempModule , Size , bytes );

            Timer->End();

            FreeAlloc( pTempModule );

            CONSOLEColorDEBUG( FOREGROUND_ROSE , TEXT( "%s -> Found offsets in: %f ms (Path: %s, Size: %i)\n" ) , sName.c_str() , Timer->dElapsedTime , sPathModule.c_str() , Size );

            delete Timer;
        }
    }
    else
    {
        // Otherwhise iterates all modules and search the given signature.

        for ( auto it = pProcess->vshModules.begin(); it != pProcess->vshModules.end(); it++ )
        {
            // Get the module path from its address.

            stdString sPathModule = pProcess->FindModulePath( ( Pointer ) it->m_hA );

            // Read the file from the module path.

            HEX Size = 0;
            Pointer pTempModule = N_FileSystem::ReadFile( sPathModule , &Size );

            // Count how much time it took to get the address of the given signature. (benchmark)

            CTimer *Timer = new CTimer();

            FindOffsets( sPathModule , ( Pointer ) it->m_hA , pTempModule , Size , bytes );

            Timer->End();

            FreeAlloc( pTempModule );

            CONSOLEColorDEBUG( FOREGROUND_ROSE , TEXT( "%s -> Found offsets in: %f ms (Path: %s, Size: %i)\n" ) , sName.c_str() , Timer->dElapsedTime , sPathModule.c_str() , Size );

            delete Timer;
        }
    }

    if ( pFirstOffset == nullptr )
    {
        __debugbreak();
    }
}

void SigScanningFile::PrintAllOffsets()
{
    for ( auto it = OffsetsFound.begin(); it != OffsetsFound.end(); it++ )
    {
        for ( uHEX i = 0; i < it->pOffsets.size(); i++ )
        {
            N_Console::Print<FOREGROUND_CYAN>( TEXT( "Module: %s (%p) Offset: %p\n" ) , it->sModuleName.c_str()
                                               , it->pModuleAddress , ( HEX ) it->pOffsets[ i ] - ( HEX ) it->pModuleAddress );
        }
    }
}

void SigScanningFile::Scan( Pointer pData , HEX Size , stdString Module )
{
    std::vector<Byte> bytes( Size );
    memcpy( bytes.data() , pData , Size );
    Scan( bytes , Module );
}

void SigScanningFile::Scan( std::string sBytes , stdString Module )
{}


void CSigScan_V2::Scan( std::string sPattern , stdString sModule )
{
    if ( sModule.empty() )
        return;

    IMAGE_DOS_HEADER DosHeader;
    uHEX32 SizeOfImage = 0;

    Pointer pModule = m_pProcess->FindModule( sModule );

    if ( !m_pProcess->VirtualReadMemory( pModule , &DosHeader , sizeof( IMAGE_DOS_HEADER ) ) )
        return;

    uintptr_t SizeOfImageOffset = DosHeader.e_lfanew;

    if ( !m_pProcess->bIsWow64 )
    {
        SizeOfImageOffset += OffsetOf( &NTHeaders64::OptionalHeader ) + OffsetOf( &IMAGE_OPTIONAL_HEADER64::SizeOfImage );
    }
    else
    {
        SizeOfImageOffset += OffsetOf( &NTHeaders32::OptionalHeader ) + OffsetOf( &IMAGE_OPTIONAL_HEADER32::SizeOfImage );
    }

    if ( !m_pProcess->VirtualReadMemory( reinterpret_cast< Pointer >( reinterpret_cast< uintptr_t >( pModule ) + SizeOfImageOffset )
         , &SizeOfImage , sizeof( SizeOfImage ) ) )
        return;

    auto pModuleCopy = Alloc( SizeOfImage );

    if ( !m_pProcess->VirtualReadMemory( pModule , pModuleCopy , SizeOfImage ) )
    {
        FreeAlloc( pModuleCopy );
        return;
    }

    auto lambda_Solve = [] ( char c1 , char c2 )
    {
        auto validatec = [] ( char &c )
        {
            c = __ascii_toupper( c );

            if ( ( c > 57 && c < 65 ) || ( c < 48 || c > 71 ) )
            {
                return false;
            }

            // 48 49 50 51 52 53 54 55 56 57 65 66 67 68 69 70 71
            // 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  G 
            // 65 - 10
            if ( c > 57 )
                c -= 55;
            else
                c -= 48;

            return true;
        };

        if ( !validatec( c2 ) || !validatec( c1 ) )
            throw( "Not a hex code." );

        return static_cast< Byte >( c2 + c1 * 0x10 );
    };

    for ( uintptr_t Addr = 0; Addr != SizeOfImage; )
    {
        pByte pBModule = reinterpret_cast< pByte >( reinterpret_cast< uintptr_t >( pModuleCopy ) + Addr );

        for ( size_t sPatternIndex = 0; sPatternIndex < sPattern.length(); sPatternIndex += 3 )
        {
            if ( sPattern[ sPatternIndex ] != '?' && sPattern[ sPatternIndex + 1 ] != '?' )
            {
                auto solvedByte = lambda_Solve( sPattern[ sPatternIndex ] , sPattern[ sPatternIndex + 1 ] );

                if ( *pBModule != solvedByte )
                    goto DontMatch;
            }

            pBModule++;
        }

        m_pAddress.uptr = reinterpret_cast< uintptr_t >( pModule ) + Addr;
        break;

DontMatch:

        Addr++;
    }

    FreeAlloc( pModuleCopy );

}