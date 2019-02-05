#include "Includes.hxx"
#include "Lib.hxx"

DllMain64::DllMain64( uHEX64 _EntryPoint , uHEX64 _Module , uHEX32 _Reason , uHEX64 _Reserved )
{
    EntryPoint = _EntryPoint;
    Module = _Module;
    Reason = _Reason;
    Reserved = _Reserved;
}

DllMain32::DllMain32( uHEX32 _EntryPoint , uHEX32 _Module , uHEX32 _Reason , uHEX32 _Reserved )
{
    EntryPoint = _EntryPoint;
    Module = _Module;
    Reason = _Reason;
    Reserved = _Reserved;
}

// Copy a string into another string.
void CopyString( String*dest , HEX destsize , const String* src )
{
#ifdef _UNICODE
    wcscpy_s( dest , destsize , src );
#else
    strcpy_s( dest , destsize , src );
#endif
}

// Open a file
void Open_S( FILE** _Stream , String const* _FileName , String const* _Mode )
{
#ifdef _UNICODE
    _wfopen_s( _Stream , _FileName , _Mode );
#else
    fopen_s( _Stream , _FileName , _Mode );
#endif
}

// Get length of a string
HEX StrLen( String const*Str )
{
#ifdef _UNICODE
    return lstrlenW( Str );
#else
    return strlen( Str );
#endif
}

// Add a string into another string
void StrCat_S( String *Str , HEX MaxSize , String* const cStr )
{
#ifdef _UNICODE
    wcscat_s( Str , MaxSize , cStr );
#else
    strcat_s( Str , MaxSize , cStr );
#endif
}

HEX StringPos( String* sBuf , String* sBuf2 , HEX Size )
{
    HEX iDest = 0;

    do
    {
        const Pointer pDest = ( Pointer ) ( ( HEX ) sBuf + iDest );

        if ( memcmp( pDest , sBuf2 , Size ) == 0 )
        {
            return iDest;
        }

        iDest++;
    } while ( iDest < Size );

    return -1;
}

// Put variables into a buffer.
void SPrintf_S( String*buf , HEX Size , const String* str , va_list list )
{
#ifdef _UNICODE
    vswprintf_s( buf , Size , str , list );
#else
    vsprintf_s( buf , Size , str , list );
#endif
}

void SPrintf_S( String*buf , HEX Size , const String* str , ... )
{
    va_list list;
    va_start( list , str );
#ifdef _UNICODE
    vswprintf_s( buf , Size , str , list );
#else
    vsprintf_s( buf , Size , str , list );
#endif
    va_end( list );
}

void ToLower( String*str , HEX Size )
{
#ifdef _UNICODE
    for ( int i = 0; i < Size; i++ )
    {
        str[ i ] = static_cast< String >( towlower( str[ i ] ) );
    }
#else
    for ( int i = 0; i < Size; i++ )
    {
        str[ i ] = static_cast< String >( tolower( str[ i ] ) );
    }
#endif
}

bool StrHasOnlyDigits( const stdString &str )
{
    return std::all_of( str.begin() , str.end() , ::isdigit ) && !str.empty();
}

// Relative Virtual Address (Rva-> offset located temporary on the cache of the disk) _ (RawData -> offset on the disk)
// Sections have VirtualAddress as name for addresses, but it should be called Rva since it's just an offset.

uHEX32 RvaToRawOffset( PIMAGE_NT_HEADERS NtHeaders , uHEX32 Rva , PIMAGE_SECTION_HEADER *SectionHeaderF )
{
    //Get the first section of the image (of the executable or dll)
    PIMAGE_SECTION_HEADER SectionHeader = IMAGE_FIRST_SECTION( NtHeaders );

    //Iterate all sections.
    for ( WORD i = 0; i < NtHeaders->FileHeader.NumberOfSections; i++ )
    {
        //If the virtual address offset is higher or equal to the virtual address of the section, good to go. (Va = 0x30001) >= ( SectionHeader[ i ].VirtualAddress = 0x30000 )
        if ( Rva >= ( uHEX32 ) SectionHeader[ i ].VirtualAddress )
        {
            //Loop until we reached the maximum size of the virtual address of the section, otherwhise we go on the next section.
            if ( ( Rva - SectionHeader[ i ].VirtualAddress ) < SectionHeader[ i ].Misc.VirtualSize )
            {
                if ( SectionHeaderF != nullptr )
                    *SectionHeaderF = &SectionHeader[ i ];

                /*

                Example:
                (Va = 0x30001) - ( SectionHeader[ i ].VirtualAddress = 0x30000 ) + (SectionHeader[ i ].PointerToRawData = 0x25000 )
                = 0x25001
                That would be for example the offset in the file.
                To check it you can open it with any hexadecimal editor, and go to that address.

                */

                return ( uHEX32 ) ( Rva - SectionHeader[ i ].VirtualAddress ) + SectionHeader[ i ].PointerToRawData;
            }
        }
    }

    return 0x0;
}

// Works the same as above, we just invert the roles between VirtualAddress to PointerToRawData (the firsts addresses of the section) and VirtualSize and SizeOfRawData.
uHEX32 RawToRvaOffset( PIMAGE_NT_HEADERS NtHeaders , uHEX32 Raw , PIMAGE_SECTION_HEADER *SectionHeaderF )
{
    PIMAGE_SECTION_HEADER SectionHeader = IMAGE_FIRST_SECTION( NtHeaders );

    for ( WORD i = 0; i < NtHeaders->FileHeader.NumberOfSections; i++ )
    {
        if ( Raw >= ( uHEX32 ) SectionHeader[ i ].PointerToRawData )
        {
            if ( ( Raw - SectionHeader[ i ].PointerToRawData ) < SectionHeader[ i ].SizeOfRawData )
            {
                if ( SectionHeaderF != nullptr )
                    *SectionHeaderF = &SectionHeader[ i ];

                return ( uHEX32 ) ( Raw - SectionHeader[ i ].PointerToRawData ) + SectionHeader[ i ].VirtualAddress;
            }
        }
    }

    return 0x0;
}

uHEX32 RvaToRaw32( pNTHeaders32 NtHeaders , uHEX32 Rva , PIMAGE_SECTION_HEADER *SectionHeaderF )
{
    auto SectionHeader = IMAGE_FIRST_SECTION32( NtHeaders );

    for ( WORD i = 0; i < NtHeaders->Parent.FileHeader.NumberOfSections; i++ )
    {
        if ( Rva >= ( uHEX32 ) SectionHeader[ i ].VirtualAddress )
        {
            if ( ( Rva - SectionHeader[ i ].VirtualAddress ) < SectionHeader[ i ].Misc.VirtualSize )
            {
                if ( SectionHeaderF != nullptr )
                    *SectionHeaderF = &SectionHeader[ i ];

                return ( uHEX32 ) ( Rva - SectionHeader[ i ].VirtualAddress ) + SectionHeader[ i ].PointerToRawData;
            }
        }
    }

    return 0x0;
}

uHEX32 RawToRva32( pNTHeaders32 NtHeaders , uHEX32 Raw , PIMAGE_SECTION_HEADER *SectionHeaderF )
{
    PIMAGE_SECTION_HEADER SectionHeader = IMAGE_FIRST_SECTION32( NtHeaders );

    for ( WORD i = 0; i < NtHeaders->Parent.FileHeader.NumberOfSections; i++ )
    {
        if ( Raw >= ( uHEX32 ) SectionHeader[ i ].PointerToRawData )
        {
            if ( ( Raw - SectionHeader[ i ].PointerToRawData ) < SectionHeader[ i ].SizeOfRawData )
            {
                if ( SectionHeaderF != nullptr )
                    *SectionHeaderF = &SectionHeader[ i ];

                return ( uHEX32 ) ( Raw - SectionHeader[ i ].PointerToRawData ) + SectionHeader[ i ].VirtualAddress;
            }
        }
    }

    return 0x0;
}

uHEX32 RvaToRaw64( pNTHeaders64 NtHeaders , uHEX32 Rva , PIMAGE_SECTION_HEADER *SectionHeaderF )
{
    auto SectionHeader = IMAGE_FIRST_SECTION64( NtHeaders );

    for ( WORD i = 0; i < NtHeaders->Parent.FileHeader.NumberOfSections; i++ )
    {
        if ( Rva >= ( uHEX32 ) SectionHeader[ i ].VirtualAddress )
        {
            if ( ( Rva - SectionHeader[ i ].VirtualAddress ) < SectionHeader[ i ].Misc.VirtualSize )
            {
                if ( SectionHeaderF != nullptr )
                    *SectionHeaderF = &SectionHeader[ i ];

                return ( uHEX32 ) ( Rva - SectionHeader[ i ].VirtualAddress ) + SectionHeader[ i ].PointerToRawData;
            }
        }
    }

    return 0x0;
}

uHEX32 RawToRva64( pNTHeaders64 NtHeaders , uHEX32 Raw , PIMAGE_SECTION_HEADER *SectionHeaderF )
{
    PIMAGE_SECTION_HEADER SectionHeader = IMAGE_FIRST_SECTION64( NtHeaders );

    for ( WORD i = 0; i < NtHeaders->Parent.FileHeader.NumberOfSections; i++ )
    {
        if ( Raw >= ( uHEX32 ) SectionHeader[ i ].PointerToRawData )
        {
            if ( ( Raw - SectionHeader[ i ].PointerToRawData ) < SectionHeader[ i ].SizeOfRawData )
            {
                if ( SectionHeaderF != nullptr )
                    *SectionHeaderF = &SectionHeader[ i ];

                return ( uHEX32 ) ( Raw - SectionHeader[ i ].PointerToRawData ) + SectionHeader[ i ].VirtualAddress;
            }
        }
    }

    return 0x0;
}

void SetClipBoard( const stdString &s )
{
    OpenClipboard( 0 );
    EmptyClipboard();

    HGLOBAL hg = GlobalAlloc( GMEM_MOVEABLE , s.size() );

    if ( !hg )
    {
        CloseClipboard();
        return;
    }

    memcpy( GlobalLock( hg ) , s.c_str() , s.size() );

    GlobalUnlock( hg );
    SetClipboardData( CF_TEXT , hg );
    CloseClipboard();
    GlobalFree( hg );
}

stdString sTime()
{
    time_t     now = time( 0 );
    struct tm  tstruct;
    String buf[ 0xFF ];
    localtime_s( &tstruct , &now );

    SPrintf_S( buf , sizeof( buf ) , TEXT( " year_%i - mon_%i - day_%i - hour_%i - min_%i sec_%i" )
               , 1900 + tstruct.tm_year , tstruct.tm_mon , tstruct.tm_mday , tstruct.tm_hour , tstruct.tm_min , tstruct.tm_sec );

    return buf;
}

CTimer::CTimer()
{
    QueryPerformanceFrequency( &lgFrequency );

    QueryPerformanceCounter( &lgt1 );
}

void CTimer::Clear()
{
    dElapsedTime = 0.0;
}

void CTimer::Start()
{
    QueryPerformanceFrequency( &lgFrequency );

    QueryPerformanceCounter( &lgt1 );
}

void CTimer::End()
{
    QueryPerformanceCounter( &lgt2 );

    dElapsedTime = ( lgt2.QuadPart - lgt1.QuadPart ) * 1000.0 / lgFrequency.QuadPart;
}

#define INRANGE(x,a,b)    (x >= a && x <= b)
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

uintptr_t FindPattern( std::string moduleName , std::string pattern )
{
    const char* pat = pattern.c_str();
    uintptr_t firstMatch = 0;
    uintptr_t rangeStart = ( uintptr_t ) GetModuleHandleA( moduleName.c_str() );
    MODULEINFO miModInfo; GetModuleInformation( GetCurrentProcess() , ( HMODULE ) rangeStart , &miModInfo , sizeof( MODULEINFO ) );
    uintptr_t rangeEnd = rangeStart + miModInfo.SizeOfImage;
    for ( uintptr_t pCur = rangeStart; pCur < rangeEnd; pCur++ )
    {
        if ( !*pat )
            return firstMatch;

        if ( *( PBYTE ) pat == '\?' || *( BYTE* ) pCur == getByte( pat ) )
        {
            if ( !firstMatch )
                firstMatch = pCur;

            if ( !pat[ 2 ] )
                return firstMatch;

            if ( *( PWORD ) pat == '\?\?' || *( PBYTE ) pat != '\?' )
                pat += 3;

            else
                pat += 2;    //one ?
        }
        else
        {
            pat = pattern.c_str();
            firstMatch = 0;
        }
    }
    return 0;
}

std::wstring GetCompileTimeDateW()
{
    return StringConverter::from_bytes( __TIMESTAMP__ );
}

std::string GetCompileTimeDateA()
{
    return __TIMESTAMP__;
}

stdString GetCompileTimeDate()
{
#ifdef _UNICODE
    return GetCompileTimeDateW();
#else
    return GetCompileTimeDateA();
#endif
}

stdString GetVarName( e_Types Type )
{
    switch ( Type )
    {
        case Type_8:
            return TEXT( "Type_8" );
        case Type_16:
            return TEXT( "Type_16" );
        case Type_32:
            return TEXT( "Type_32" );
        case Type_64:
            return TEXT( "Type_64" );
        case Type_Pointer:
            return TEXT( "Type_Pointer" );
        case Type_Array:
            return TEXT( "Type_Array" );
        case Type_Size:
            return TEXT( "Type_Size" );
        default:
            return TEXT( "Type_Unknown" );
    }
}