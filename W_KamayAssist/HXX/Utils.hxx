#ifndef LIB_UTILS
#define LIB_UTILS
#pragma once

#define DO_ONCE_SCOPE(Code) \
{\
static bool bCodeRun = false; \
if(!bCodeRun) \
{ \
  Code; \
  bCodeRun = true; \
} \
} \

#define DO_ONCE(Code) \
static bool bCodeRun = false; \
if(!bCodeRun) \
{ \
  Code; \
  bCodeRun = true; \
} \

#define EXTERN extern

#define CUSTOM_SECTION_START(section)\
__pragma ( code_seg( push ) )\
__pragma ( code_seg( #section ) )\

#define CUSTOM_SECTION_END() __pragma ( code_seg( pop ) )

#define BUFSIZE 512

#define IMAGE_FIRST_SECTION32( ntheader ) ((PIMAGE_SECTION_HEADER)        \
    ((ULONG_PTR)(ntheader) +                                            \
     FIELD_OFFSET( IMAGE_NT_HEADERS32, OptionalHeader ) +                 \
     ((ntheader))->Parent.FileHeader.SizeOfOptionalHeader   \
    ))

#define IMAGE_FIRST_SECTION64( ntheader ) ((PIMAGE_SECTION_HEADER)        \
    ((ULONG_PTR)(ntheader) +                                            \
     FIELD_OFFSET( IMAGE_NT_HEADERS64, OptionalHeader ) +                 \
     ((ntheader))->Parent.FileHeader.SizeOfOptionalHeader   \
    ))

#define GetParentNtHeaders( pDosHeader ) ( ( pParentNTHeaders ) ( ( HEX ) pDosHeader + pDosHeader->e_lfanew ) )

/* Defines */
#define FOREGROUND_CYAN FOREGROUND_GREEN | FOREGROUND_BLUE
#define FOREGROUND_ROSE FOREGROUND_RED | FOREGROUND_BLUE
#define FOREGROUND_YELLOW FOREGROUND_RED | FOREGROUND_GREEN
#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define BACKGROUND_CYAN BACKGROUND_GREEN | BACKGROUND_BLUE
#define BACKGROUND_ROSE BACKGROUND_RED | BACKGROUND_BLUE
#define BACKGROUND_YELLOW BACKGROUND_RED | BACKGROUND_GREEN
#define BACKGROUND_WHITE BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
#define CONSOLE_UNDERLINED COMMOLVB_UNDERSCORE
#define CONSOLE_BOX COMMOLVB_GRID_HORIZONTAL | COMMOLVB_GRID_RVERTICAL | COMMOLVB_REVERSE_VIDEO
#define CONSOLE_REVERSE COMMOLVB_REVERSE_VIDEO
#define MINSIZEVIRTUALMEMORY  0x1000
#define UNINITIALIZED 0xFFFFFFFF

//https://people.freebsd.org/~wpaul/pe/pe_var.h
#define IMR_RELTYPE(x)				((x >> 12) & 0xF)
#define IMR_RELOFFSET(x)			(x & 0xFFF)

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

#define _FunctionOffset(offset) (*(HEX*)(*(HEX*)this + offset))
#define _FunctionManualthisOffset(offset,thiss) (*(HEX*)(*(HEX*)thiss + offset))
#define _Offset(offset,type) (*(type*)((HEX)this + offset))
#define _POffset(offset,type) ((type*)((HEX)this + offset))
#define _OffsetManualthis(offset,type,thiss) (*(type*)((HEX)thiss + offset))
#define _POffsetManualthis(offset,type,thiss) ((type*)((HEX)thiss + offset))

/* Typedefs */

typedef void* Pointer;
typedef void** pPointer;

#ifdef ENVIRONMENT32
typedef unsigned long uHEX;
typedef signed long HEX;
#else
typedef unsigned long long uHEX;
typedef signed long long HEX;
#endif
typedef uHEX *puHEX;
typedef HEX *pHEX;

typedef unsigned char Byte;
typedef Byte* pByte;
typedef pByte Bytes;

typedef unsigned short Word;
typedef Word* pWord;
typedef pWord Words;

typedef unsigned long uHEX32;
typedef signed long HEX32;
typedef uHEX32 *puHEX32;
typedef HEX32 *pHEX32;
typedef unsigned long long uHEX64;
typedef signed long long HEX64;
typedef uHEX64 *puHEX64;
typedef HEX64 *pHEX64;

typedef struct _ParentNTHeaders
{
    DWORD Signature;
    IMAGE_FILE_HEADER FileHeader;
} ParentNTHeaders , *pParentNTHeaders;

typedef struct _NTHeaders32
{
    ParentNTHeaders Parent;
    IMAGE_OPTIONAL_HEADER32 OptionalHeader;
} NTHeaders32 , *pNTHeaders32;

typedef struct _NTHeaders64
{
    ParentNTHeaders Parent;
    IMAGE_OPTIONAL_HEADER64 OptionalHeader;
} NTHeaders64 , *pNTHeaders64;

__pragma( warning( push ) )
__pragma( warning( disable:4244 ) )

class StringConverter
{
public:

    static std::wstring from_bytes( std::string str )
    {
        return { str.begin(), str.end() };
    }

    static std::string to_bytes( std::wstring str )
    {
        return { str.begin(), str.end() };
    }
};

__pragma( warning( pop ) )

// Auto convert was meant to be portable on projects settings for acsii and unicode
#ifdef _UNICODE
typedef wchar_t String;
typedef std::wstring stdString;
#define AutoConvertS(s) StringConverter::from_bytes(s).c_str()
#define AutoConvertW(s) s
#define AutoConvertC(s) StringConverter::to_bytes(s).c_str()
#else
typedef char String;
typedef std::string stdString;
#define AutoConvertS(s) s
#define AutoConvertW(s) StringConverter::to_bytes(s).c_str()
#define AutoConvertC(s) s
#endif

// Copy a string into another string.
void CopyString( String*dest , HEX destsize , const String* src );

// Open a file
void Open_S( FILE** _Stream , String const* _FileName , String const* _Mode );

// Get length of a string
HEX StrLen( String const*Str );

// Add a string into another string
void StrCat_S( String *Str , HEX MaxSize , String* const cStr );

HEX StringPos( String* sBuf , String* sBuf2 , HEX Size );

// Put variables into a buffer.
void SPrintf_S( String*buf , HEX Size , const String* str , va_list list );

void SPrintf_S( String*buf , HEX Size , const String* str , ... );

void ToLower( String*str , HEX Size );

bool StrHasOnlyDigits( const stdString &str );

void SetClipBoard( const stdString &s );

// Allocating memory (not forcely virtual)
template<typename T = Pointer> constexpr __forceinline T Alloc( size_t Size )
{
    return ( T )::operator new( Size );
}

template<typename T = Pointer> constexpr __forceinline std::unique_ptr<T> AllocUnique( size_t Size )
{
    return std::unique_ptr<T>( ( T )::operator new( Size ) );
}

template<typename T = Pointer> constexpr __forceinline std::shared_ptr<T> AllocShared( size_t Size )
{
    return std::shared_ptr<T>( ( T )::operator new( Size ) );
}

// Freeing memory (not forcely virtual)
template<typename T = Pointer> constexpr __forceinline void FreeAlloc( T pBuf )
{
    ::operator delete( ( Pointer ) pBuf );
}

template<typename T = Pointer> constexpr __forceinline void FreeAllocSecure( T &pBuf )
{
    if ( ( Pointer ) pBuf != nullptr )
    {
        ::operator delete( ( Pointer ) pBuf );
        pBuf = nullptr;
    }
}

template<typename T = Pointer> __forceinline bool memctn( T pSource , T pDest , size_t sizeToCompare )
{
    while ( sizeToCompare-- != 0 )
    {
        if ( reinterpret_cast< uint8_t* >( pSource )[ sizeToCompare ] != reinterpret_cast< uint8_t* >( pDest )[ sizeToCompare ] )
            return false;
    }

    return true;
}

// Relative Virtual Address (Rva-> offset located temporary on the cache of the disk) _ (RawData -> offset on the disk)
// Sections have VirtualAddress as name for addresses, but it should be called Rva since it's just an offset.

uHEX32 RvaToRawOffset( PIMAGE_NT_HEADERS NtHeaders , uHEX32 Rva , PIMAGE_SECTION_HEADER* SectionHeaderF = nullptr );

// Works the same as above, we just invert the roles between VirtualAddress to PointerToRawData (the firsts addresses of the section) and VirtualSize and SizeOfRawData.
uHEX32 RawToRvaOffset( PIMAGE_NT_HEADERS NtHeaders , uHEX32 Raw , PIMAGE_SECTION_HEADER* SectionHeaderF = nullptr );

uHEX32 RvaToRaw32( pNTHeaders32 NtHeaders , uHEX32 Rva , PIMAGE_SECTION_HEADER* SectionHeaderF = nullptr );
uHEX32 RawToRva32( pNTHeaders32 NtHeaders , uHEX32 Raw , PIMAGE_SECTION_HEADER* SectionHeaderF = nullptr );
uHEX32 RvaToRaw64( pNTHeaders64 NtHeaders , uHEX32 Rva , PIMAGE_SECTION_HEADER* SectionHeaderF = nullptr );
uHEX32 RawToRva64( pNTHeaders64 NtHeaders , uHEX32 Raw , PIMAGE_SECTION_HEADER* SectionHeaderF = nullptr );


template<typename T , typename U>
constexpr inline size_t OffsetOf( U T::*member )
{
    return reinterpret_cast< size_t >( &( reinterpret_cast< T* >( nullptr )->*member ) );
}

template<typename T = HEX> constexpr __forceinline T _GetModule( const String* sModuleName , HEX HexAddressToAdd = 0 )
{
    return ( T ) ( ( HEX ) GetModuleHandle( sModuleName ) + HexAddressToAdd );
}

template<typename T = pPointer> constexpr __forceinline T _VTable( Pointer pAddress )
{
    return *( T* ) ( pAddress );
}

template<typename T = Pointer> constexpr __forceinline T _VirtualFunction( Pointer pAddress , int iIndex )
{
    return ( T ) ( _VTable( pAddress )[ iIndex ] );
}

template< typename RetType = void , typename P = Pointer , typename ... vArgs > constexpr __forceinline RetType _CallVirtualFunction( P pAddress , int iIndex , vArgs ... pArgs )
{
    return ( ( RetType( __thiscall* )( P , vArgs ... ) ) _VTable( pAddress )[ iIndex ] ) ( pAddress , pArgs ... );
}

template<typename T = Pointer> constexpr __forceinline T _Function( Pointer pAddress )
{
    return ( T ) ( pAddress );
}

enum E_CallingConvention
{
    e_thiscall ,
    e_fastcall ,
    e_stdcall ,
    e_nothing
};

template< typename RetType = void , E_CallingConvention CallingConvention = e_nothing , typename ... vArgs > constexpr  __forceinline RetType _CallFunction( Pointer pAddress , vArgs ... pArgs )
{
    if constexpr ( CallingConvention == e_thiscall )
    {
        return ( ( RetType( __thiscall* )( vArgs ... ) ) pAddress ) ( pArgs ... );
    }

    if constexpr ( CallingConvention == e_fastcall )
    {
        return ( ( RetType( __fastcall* )( vArgs ... ) ) pAddress ) ( pArgs ... );
    }

    if constexpr ( CallingConvention == e_stdcall )
    {
        return ( ( RetType( __stdcall* )( vArgs ... ) ) pAddress ) ( pArgs ... );
    }

    if constexpr ( CallingConvention == e_nothing )
    {
        return ( ( RetType( __cdecl* )( vArgs ... ) ) pAddress ) ( pArgs ... );
    }
}

template<typename T = Pointer> constexpr __forceinline  T _Cast( Pointer pTemp )
{
    return ( T ) ( pTemp );
}

enum e_Types
{
    Type_Pointer ,
    Type_Float ,
    Type_Double ,
    Type_Size ,
    Type_32 ,
    Type_64 ,
    Type_16 ,
    Type_8 ,
    Type_Array ,
    Type_ALL
};

template <typename T>
struct Type_Wrapper
{
    using Type = T;
};

template <typename T>
inline constexpr Type_Wrapper<T> _Type{};

template <e_Types Type> inline constexpr auto _GetVarType()
{
    if constexpr ( Type == Type_Size )
        return _Type<uHEX>;
    else if constexpr ( Type == Type_8 )
        return _Type<Byte>;
    else if constexpr ( Type == Type_16 )
        return _Type<Word>;
    else if constexpr ( Type == Type_32 )
        return _Type<uHEX32>;
    else if constexpr ( Type == Type_64 )
        return _Type<uHEX64>;
    else if constexpr ( Type == Type_Pointer )
        return _Type<Pointer>;
    else if constexpr ( Type == Type_Array )
        return _Type<Bytes>;
    else if constexpr ( Type == Type_Float )
        return _Type<float>;
    else if constexpr ( Type == Type_Double )
        return _Type<double>;
    else
        return _Type<void>;
};

template<e_Types _Type>
using GetVarType_t = decltype( _GetVarType<_Type>() );

#define GetVarType( _Type ) GetVarType_t<_Type>::Type

template<e_Types Type> constexpr auto GetVarSize()
{
    return sizeof( GetVarType( Type ) );
};

/*
template<e_Types Type> constexpr auto _GetVarType()
{
    if constexpr( Type == Type_8 )
        return ( Byte ) 0;
    if constexpr( Type == Type_16 )
        return ( Word ) 0;
    if constexpr( Type == Type_32 )
        return ( HEX32 ) 0;
    if constexpr( Type == Type_64 )
        return ( HEX64 ) 0;
    if constexpr( Type == Type_Pointer )
        return ( Pointer ) 0;
    if constexpr( Type == Type_Size )
        return ( size_t ) 0;
    if constexpr( Type == Type_Array )
        return ( Bytes ) 0;
}

stdString GetVarName( e_Types Type );

#define GetVarType(type) decltype( _GetVarType<type>() )
#define GetVarTypeArray GetVarType( Type_Array )
#define GetVarType8 GetVarType( Type_8 )
#define GetVarType16 GetVarType( Type_16 )
#define GetVarType32 GetVarType( Type_32 )
#define GetVarType64 GetVarType( Type_64 )
#define GetVarTypePointer GetVarType( Type_Pointer )
#define GetVarTypeSize GetVarType( Type_Size )
*/

stdString GetVarName( e_Types Type );

// Just a class to call our entrypoint later in manual mapping.
// So we can pass it as the argument when we create a thread remotly to call the entrypoint with that.

class DllMain64
{
public:

    DllMain64( uHEX64 _EntryPoint , uHEX64 _Module , uHEX32 _Reason , uHEX64 _Reserved );

    uHEX64 EntryPoint;
    uHEX64 Module , Reserved;
    uHEX32 Reason;
};

class DllMain32
{
public:

    DllMain32( uHEX32 _EntryPoint , uHEX32 _Module , uHEX32 _Reason , uHEX32 _Reserved );

    uHEX32 EntryPoint;
    uHEX32 Module , Reason , Reserved;
};

stdString sTime();

class CTimer
{
public:

    CTimer();

    void Clear();

    void Start();

    void End();

    LARGE_INTEGER lgFrequency;
    LARGE_INTEGER lgt1 , lgt2;
    double dElapsedTime;
};

template<typename T = Byte , typename pT = T * >
class Buffer
{
public:

    Buffer( size_t Size = 0 ) : m_pData( nullptr ) , m_Size( 0 )
    {
        if ( Size == 0 )
        {
            m_pData = nullptr;
            m_Size = 0;
        }
        else
        {
            m_pData = Alloc<pT>( Size );
            m_Size = Size;
        }
    }

    Buffer( Pointer pData , size_t Size ) : m_pData( nullptr ) , m_Size( 0 )
    {
        if ( Size == 0 )
        {
            m_pData = nullptr;
            m_Size = 0;
        }
        else
        {
            m_pData = Alloc<pT>( Size );
            m_Size = Size;
            memcpy( m_pData , pData , Size );
        }
    }

    ~Buffer()
    {
        Free();
    }

    void Free()
    {
        if ( m_pData != nullptr )
        {
            FreeAlloc<pT>( m_pData );
        }

        m_pData = nullptr;
        m_Size = 0;
    }

    Buffer( const Buffer<T>& src ) : m_pData( nullptr ) , m_Size( 0 )
    {
        *this = src;
    }

    Buffer<T>& operator=( const Buffer<T>& src )
    {
        Free();

        if ( src.m_Size == 0 )
            return *this;
        else
        {
            m_Size = src.m_Size;
            m_pData = Alloc<pT>( m_Size );
            memcpy( m_pData , src.m_pData , src.m_Size );
            return *this;
        }
    }

    Buffer<T>& Copy( const Buffer<T>& src )
    {
        return Copy( src.m_pData , src.m_Size );
    }

    Buffer<T>& Copy( Pointer pData , size_t Size )
    {
        memcpy( m_pData , pData , Size );
        return *this;
    }

    Buffer<T>& Add( const Buffer<T>& src )
    {
        return Add( src.m_pData , src.m_Size );
    }

    Buffer<T>& Add( Pointer pData , size_t Size )
    {
        Buffer<T> nBuffer( Size + m_Size );

        if ( m_Size != 0 && m_pData != nullptr )
        {
            memcpy( nBuffer.m_pData , m_pData , m_Size );
            memcpy( nBuffer.P( m_Size ) , pData , Size );
        }
        else
        {
            memcpy( nBuffer.m_pData , pData , Size );
        }

        Free();
        *this = nBuffer;
        return *this;
    }

    T& GetSlot( size_t Slot )
    {
        return *( T * ) ( ( size_t ) m_pData + Slot );
    }

    T& operator[]( size_t Slot )
    {
        return GetSlot( Slot );
    }

    pT P( size_t Slot = 0 )
    {
        return ( pT ) ( ( size_t ) m_pData + Slot );
    }

    size_t SizeType()
    {
        return sizeof( T );
    }

    pT m_pData;
    size_t m_Size;
};

template<typename T>
class CEncVar
{
public:

    CEncVar( T Value = 0 ) : m_x0rValue( nullptr ) , m_EncValue( nullptr )
    {
        Alloc();
        *m_EncValue = Value;
        GenRand();
    }

    void Alloc()
    {
        m_x0rValue = new T;
        m_EncValue = new T;
    }

    void GenRand()
    {
        std::srand( ( unsigned int ) std::time( 0 ) );

        for ( int i = 0; i < sizeof( T ); i++ )
        {
            int iNew = ( sizeof( T ) - 1 ) - i;

            ( ( Byte* ) m_x0rValue )[ iNew ] = ( std::rand() + iNew ) % 0xFF;

            ( ( Byte* ) m_EncValue )[ iNew ] ^= ( ( Byte* ) m_x0rValue )[ iNew ];
        }
    }

    T Get()
    {
        T Value = 0;

        for ( int i = 0; i < sizeof( T ); i++ )
        {
            int iNew = ( sizeof( T ) - 1 ) - i;

            ( ( Byte* ) &Value )[ iNew ] = ( ( Byte* ) m_EncValue )[ iNew ] ^ ( ( Byte* ) m_x0rValue )[ iNew ];
        }

        Free();
        Alloc();

        *m_EncValue = Value;

        GenRand();

        return Value;
    }

    void Set( T Value )
    {
        Free();
        Alloc();
        *m_EncValue = Value;
        GenRand();
    }

    CEncVar<T>& operator=( CEncVar<T>& src )
    {
        Set( src.Get() );
        return *this;
    }

    void Free()
    {
        if ( m_EncValue != nullptr )
            memset( m_EncValue , 0 , sizeof( T ) );
        if ( m_x0rValue != nullptr )
            memset( m_x0rValue , 0 , sizeof( T ) );

        FreeAllocSecure( m_x0rValue );
        FreeAllocSecure( m_EncValue );
    }

    ~CEncVar()
    {
        Free();
    }

    T *m_EncValue;
    T *m_x0rValue;
};

class CEncBuffer
{
public:

    CEncBuffer( size_t Size = 0 ) : m_Buffer( nullptr ) , m_Size( 0 )
    {
        m_Size.Set( Size );

        if ( Size != 0 )
            m_Buffer = new CEncVar<Byte>[ Size ];
    }

    CEncBuffer( Pointer pData , size_t Size ) : m_Buffer( nullptr ) , m_Size( 0 )
    {
        Add( pData , Size );
    }

    CEncBuffer& operator=( CEncBuffer& src )
    {
        Free();

        size_t SizeSrc = src.m_Size.Get();

        if ( SizeSrc == 0 )
            return *this;
        else
        {
            m_Size = src.m_Size;

            m_Buffer = new CEncVar<Byte>[ m_Size.Get() ];

            for ( size_t i = 0; i < m_Size.Get(); i++ )
            {
                m_Buffer[ i ] = src.m_Buffer[ i ];
            }

            return *this;
        }
    }

    CEncBuffer& Add( CEncBuffer& buf )
    {
        CEncBuffer nBuffer( buf.m_Size.Get() + m_Size.Get() );

        if ( m_Size.Get() != 0 )
        {
            for ( size_t i = 0; i < m_Size.Get(); i++ )
            {
                nBuffer.m_Buffer[ i ] = m_Buffer[ i ];
            }
        }

        for ( size_t i = 0; i < buf.m_Size.Get(); i++ )
        {
            nBuffer.m_Buffer[ m_Size.Get() + i ].Set( buf.m_Buffer[ i ].Get() );
        }

        Free();
        *this = nBuffer;
        return *this;
    }

    CEncBuffer& Add( Pointer pData , size_t Size )
    {
        CEncBuffer nBuffer( Size + m_Size.Get() );

        if ( m_Size.Get() != 0 )
        {
            for ( size_t i = 0; i < m_Size.Get(); i++ )
            {
                nBuffer.m_Buffer[ i ] = m_Buffer[ i ];
            }
        }

        for ( size_t i = 0; i < Size; i++ )
        {
            nBuffer.m_Buffer[ m_Size.Get() + i ].Set( ( ( Byte* ) pData )[ i ] );
        }

        Free();
        *this = nBuffer;
        return *this;
    }

    CEncVar<Byte>* P( size_t Slot = 0 )
    {
        return &m_Buffer[ Slot ];
    }

    void Free()
    {
        FreeAllocSecure( m_Buffer );
        m_Size.Free();
    }

    std::unique_ptr<Buffer<Byte>> Read( size_t Size , size_t Slot = 0 )
    {
        std::unique_ptr<Buffer<Byte>> buf( new Buffer<Byte>( Size ) );

        if ( Size + Slot <= m_Size.Get() )
        {
            for ( size_t i = 0; i < Size; i++ )
            {
                *buf->P( i ) = m_Buffer[ i + Slot ].Get();
            }
        }

        return buf;
    }

    ~CEncBuffer()
    {
        Free();
    }

    CEncVar<Byte> *m_Buffer;
    CEncVar<size_t> m_Size;
};

class SocketBuffer : public Buffer<Byte>
{
public:

    SocketBuffer( size_t Size = 0 ) : Buffer<Byte>( Size ) , m_Slot( 0 )
    {
        ResetSlot();
    }

    SocketBuffer( Pointer pData , size_t Size ) : Buffer<Byte>( pData , Size ) , m_Slot( 0 )
    {
        ResetSlot();
    }

    ~SocketBuffer()
    {
        Init();
    }

    void Init()
    {
        Free();
        ResetSlot();
    }

    void ResetSlot()
    {
        m_Slot = 0;
    }

    SocketBuffer& AddType( e_Types Type )
    {
        Add( &Type , sizeof( Type ) );
        return *this;
    }

    template<e_Types Type = Type_Size , typename VarType = GetVarType( Type )>
    SocketBuffer& AddVar( VarType _Value , size_t Size = 0 )
    {
        AddType( Type );

        if constexpr ( Type == Type_Array )
        {
            Add( &Size , sizeof( Size ) );
            m_Slot += sizeof( Size );

            Add( _Value , Size );
            m_Slot += Size;
        }
        else
        {
            Add( &_Value , sizeof( _Value ) );
            m_Slot += sizeof( _Value );
        }

        return *this;
    }

    template<e_Types Type = Type_Size>
    auto _ReadVar( size_t *pSize = nullptr )
    {
        size_t VarSize = 0;

        if constexpr ( Type == Type_Array )
        {
            VarSize = *( size_t* ) P( m_Slot );

            m_Slot += sizeof( VarSize );

            if ( pSize != nullptr )
                *pSize = VarSize;

            auto Var = ( GetVarType( Type ) )P( m_Slot );

            m_Slot += VarSize;

            return Var;
        }
        else
        {
            VarSize = sizeof( GetVarType( Type ) );

            if ( pSize != nullptr )
                *pSize = VarSize;

            auto Var = *( GetVarType( Type )* )P( m_Slot );

            m_Slot += VarSize;

            return Var;
        }
    }

    template<e_Types ExpectedType = Type_Size>
    auto ReadVar( size_t *pSize = nullptr )
    {
        auto Type = *( e_Types* ) P( m_Slot );
        m_Slot += sizeof( Type );

        if ( Type == ExpectedType )
        {
            return _ReadVar<ExpectedType>( pSize );
        }
        else
        {
            //CONSOLEDEBUG( TEXT( "Error: real type: %s\n" ) , GetVarName( Type ).c_str() );
            return ( GetVarType( ExpectedType ) )0;
        }
    }

    void AddSignature()
    {
        SocketBuffer FinalBuf( 0 );

        std::string SignatureCheck( Signature );

        CryptoPP::SecByteBlock Block( ( Bytes ) sAESKeySignature.data() , CryptoPP::AES::MAX_KEYLENGTH );
        CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cbfEncryption( Block , Block.size() , ( Bytes ) sAESIVSignature.data() );
        cbfEncryption.ProcessData( ( Bytes ) SignatureCheck.data() , ( Bytes ) SignatureCheck.data() , SignatureCheck.size() );

        FinalBuf.Add( SignatureCheck.data() , SignatureCheck.size() );
        FinalBuf.AddVar( m_Size );
        FinalBuf.AddVar<Type_Array>( m_pData , m_Size );

        *this = FinalBuf;
    }

    bool ValidMsg()
    {
        if ( m_Size < Signature.size() )
            return false;

        std::string SignatureCheck( ( char* ) m_pData , Signature.size() );

        CryptoPP::SecByteBlock Block( ( Bytes ) sAESKeySignature.data() , CryptoPP::AES::MAX_KEYLENGTH );
        CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption cfbDecryption( Block , Block.size() , ( Bytes ) sAESIVSignature.data() );
        cfbDecryption.ProcessData( ( Bytes ) SignatureCheck.data() , ( Bytes ) SignatureCheck.data() , SignatureCheck.size() );

        if ( SignatureCheck.find( Signature ) == std::string::npos )
            return false;

        m_Slot += SignatureCheck.size();

        auto SizeOfData = ReadVar();

        if ( SizeOfData >= m_Size )
            return false;

        size_t SizeOfArray = 0;
        auto pData = ReadVar<Type_Array>( &SizeOfArray );

        if ( SizeOfArray == SizeOfData )
        {
            SocketBuffer Buffer( pData , SizeOfArray );
            *this = Buffer;
            return true;
        }
        else
        {
            return false;
        }
    }

    size_t m_Slot;
    std::string Signature = AutoConvertC(
        TEXT( "XK_NET_MSG_" ) );

    std::string sAESKeySignature = AutoConvertC(
        TEXT( "Q8;b$'^r_q59]&Fa^t#ap@GSRZD8{'Y?" ) );

    std::string sAESIVSignature = AutoConvertC(
        TEXT( ":QyS,-:HbFv.x4T" ) );
};


enum POOL_TYPE
{
    NonPagedPool ,
    PagedPool ,
    NonPagedPoolMustSucceed ,
    DontUseThisType ,
    NonPagedPoolCacheAligned ,
    PagedPoolCacheAligned ,
    NonPagedPoolCacheAlignedMustS
};

template <typename T>
struct _LIST_ENTRY_T
{
    T Flink;
    T Blink;
};

template <typename T>
struct _UNICODE_STRING_T
{
    using type = T;

    uint16_t Length;
    uint16_t MaximumLength;
    T Buffer;
};

template <typename T>
struct _NT_TIB_T
{
    T ExceptionList;
    T StackBase;
    T StackLimit;
    T SubSystemTib;
    T FiberData;
    T ArbitraryUserPointer;
    T Self;
};

template <typename T>
struct _CLIENT_ID_T
{
    T UniqueProcess;
    T UniqueThread;
};

template <typename T>
struct _GDI_TEB_BATCH_T
{
    uint32_t Offset;
    T HDC;
    uint32_t Buffer[ 310 ];
};

template <typename T>
struct _TEB_T
{
    using type = T;

    _NT_TIB_T<T> NtTib;
    T EnvironmentPointer;
    _CLIENT_ID_T<T> ClientId;
    T ActiveRpcHandle;
    T ThreadLocalStoragePointer;
    T ProcessEnvironmentBlock;
    uint32_t LastErrorValue;
    uint32_t CountOfOwnedCriticalSections;
    T CsrClientThread;
    T Win32ThreadInfo;
    uint32_t User32Reserved[ 26 ];
    T UserReserved[ 5 ];
    T WOW32Reserved;
    uint32_t CurrentLocale;
    uint32_t FpSoftwareStatusRegister;
    T SystemReserved1[ 54 ];
    uint32_t ExceptionCode;
    T ActivationContextStackPointer;
    uint8_t SpareBytes[ 36 ];
    uint32_t TxFsContext;
    _GDI_TEB_BATCH_T<T> GdiTebBatch;
    _CLIENT_ID_T<T> RealClientId;
    T GdiCachedProcessHandle;
    uint32_t GdiClientPID;
    uint32_t GdiClientTID;
    T GdiThreadLocalInfo;
    T Win32ClientInfo[ 62 ];
    T glDispatchTable[ 233 ];
    T glReserved1[ 29 ];
    T glReserved2;
    T glSectionInfo;
    T glSection;
    T glTable;
    T glCurrentRC;
    T glContext;
    uint32_t LastStatusValue;
    _UNICODE_STRING_T<T> StaticUnicodeString;
    wchar_t StaticUnicodeBuffer[ 261 ];
    T DeallocationStack;
    T TlsSlots[ 64 ];
    _LIST_ENTRY_T<T> TlsLinks;
    T Vdm;
    T ReservedForNtRpc;
    T DbgSsReserved[ 2 ];
    uint32_t HardErrorMode;
    T Instrumentation[ 11 ];
    _GUID ActivityId;
    T SubProcessTag;
    T PerflibData;
    T EtwTraceData;
    T WinSockData;
    uint32_t GdiBatchCount;             // TEB64 pointer
    uint32_t IdealProcessorValue;
    uint32_t GuaranteedStackBytes;
    T ReservedForPerf;
    T ReservedForOle;
    uint32_t WaitingOnLoaderLock;
    T SavedPriorityState;
    T ReservedForCodeCoverage;
    T ThreadPoolData;
    T TlsExpansionSlots;
    T DeallocationBStore;
    T BStoreLimit;
    uint32_t MuiGeneration;
    uint32_t IsImpersonating;
    T NlsCache;
    T pShimData;
    uint16_t HeapVirtualAffinity;
    uint16_t LowFragHeapDataSlot;
    T CurrentTransactionHandle;
    T ActiveFrame;
    T FlsData;
    T PreferredLanguages;
    T UserPrefLanguages;
    T MergedPrefLanguages;
    uint32_t MuiImpersonation;
    uint16_t CrossTebFlags;
    uint16_t SameTebFlags;
    T TxnScopeEnterCallback;
    T TxnScopeExitCallback;
    T TxnScopeContext;
    uint32_t LockCount;
    uint32_t SpareUlong0;
    T ResourceRetValue;
    T ReservedForWdf;
};

template<typename T>
struct _PEB_T
{
    using type = T;
    using const34 = std::integral_constant<int , 34>;
    using const60 = std::integral_constant<int , 60>;
    using is32Bit = std::integral_constant<bool , std::is_same_v<T , uint32_t>>;
    using BufferSize_t = std::conditional_t<is32Bit::value , const34 , const60>;

    uint8_t InheritedAddressSpace;
    uint8_t ReadImageFileExecOptions;
    uint8_t BeingDebugged;
    union u1
    {
        uint8_t BitField;
        struct s
        {
            uint8_t ImageUsesLargePages : 1;
            uint8_t IsProtectedProcess : 1;
            uint8_t IsImageDynamicallyRelocated : 1;
            uint8_t SkipPatchingUser32Forwarders : 1;
            uint8_t IsPackagedProcess : 1;
            uint8_t IsAppContainer : 1;
            uint8_t IsProtectedProcessLight : 1;
            uint8_t SpareBits : 1;
        };
    };
    T Mutant;
    T ImageBaseAddress;
    T Ldr;
    T ProcessParameters;
    T SubSystemData;
    T ProcessHeap;
    T FastPebLock;
    T AtlThunkSListPtr;
    T IFEOKey;
    union u2
    {
        T CrossProcessFlags;
        struct s
        {
            uint32_t ProcessInJob : 1;
            uint32_t ProcessInitializing : 1;
            uint32_t ProcessUsingVEH : 1;
            uint32_t ProcessUsingVCH : 1;
            uint32_t ProcessUsingFTH : 1;
            uint32_t ReservedBits0 : 27;
        };
    };
    union
    {
        T KernelCallbackTable;
        T UserSharedInfoPtr;
    };
    uint32_t SystemReserved;
    uint32_t AtlThunkSListPtr32;
    T ApiSetMap;
    union
    {
        uint32_t TlsExpansionCounter;
        T Padding2;
    };
    T TlsBitmap;
    uint32_t TlsBitmapBits[ 2 ];
    T ReadOnlySharedMemoryBase;
    T SparePvoid0;
    T ReadOnlyStaticServerData;
    T AnsiCodePageData;
    T OemCodePageData;
    T UnicodeCaseTableData;
    uint32_t NumberOfProcessors;
    uint32_t NtGlobalFlag;
    LARGE_INTEGER CriticalSectionTimeout;
    T HeapSegmentReserve;
    T HeapSegmentCommit;
    T HeapDeCommitTotalFreeThreshold;
    T HeapDeCommitFreeBlockThreshold;
    uint32_t NumberOfHeaps;
    uint32_t MaximumNumberOfHeaps;
    T ProcessHeaps;
    T GdiSharedHandleTable;
    T ProcessStarterHelper;
    union
    {
        uint32_t GdiDCAttributeList;
        T Padding3;
    };
    T LoaderLock;
    uint32_t OSMajorVersion;
    uint32_t OSMinorVersion;
    uint16_t OSBuildNumber;
    uint16_t OSCSDVersion;
    uint32_t OSPlatformId;
    uint32_t ImageSubsystem;
    uint32_t ImageSubsystemMajorVersion;
    union
    {
        uint32_t ImageSubsystemMinorVersion;
        T Padding4;
    };
    T ActiveProcessAffinityMask;
    uint32_t GdiHandleBuffer[ BufferSize_t::value ];
    T PostProcessInitRoutine;
    T TlsExpansionBitmap;
    uint32_t TlsExpansionBitmapBits[ 32 ];
    union
    {
        uint32_t SessionId;
        T Padding5;
    };
    ULARGE_INTEGER AppCompatFlags;
    ULARGE_INTEGER AppCompatFlagsUser;
    T pShimData;
    T AppCompatInfo;
    _UNICODE_STRING_T<T> CSDVersion;
    T ActivationContextData;
    T ProcessAssemblyStorageMap;
    T SystemDefaultActivationContextData;
    T SystemAssemblyStorageMap;
    T MinimumStackCommit;
    T FlsCallback;
    _LIST_ENTRY_T<T> FlsListHead;
    T FlsBitmap;
    uint32_t FlsBitmapBits[ 4 ];
    uint32_t FlsHighIndex;
    T WerRegistrationData;
    T WerShipAssertPtr;
    T pUnused;
    T pImageHeaderHash;
    union u3
    {
        uint64_t TracingFlags;
        struct s
        {
            uint32_t HeapTracingEnabled : 1;
            uint32_t CritSecTracingEnabled : 1;
            uint32_t LibLoaderTracingEnabled : 1;
            uint32_t SpareTracingBits : 29;
        };
    };
    T CsrServerReadOnlySharedMemoryBase;
};

#pragma warning(default : 4201)

template<typename T>
struct _ACTCTXW_T
{
    uint32_t  cbSize;
    uint32_t  dwFlags;
    T      lpSource;
    uint16_t wProcessorArchitecture;
    LANGID wLangId;
    T      lpAssemblyDirectory;
    T      lpResourceName;
    T      lpApplicationName;
    T      hModule;
};

template<typename T>
struct _PROCESS_BASIC_INFORMATION_T
{
    NTSTATUS ExitStatus;
    uint32_t    Reserved0;
    T	     PebBaseAddress;
    T	     AffinityMask;
    LONG	 BasePriority;
    ULONG	 Reserved1;
    T	     uUniqueProcessId;
    T	     uInheritedFromUniqueProcessId;
};

template<typename T>
struct _SECTION_BASIC_INFORMATION_T
{
    T             Base;
    uint32_t         Attributes;
    LARGE_INTEGER Size;
};

template<typename T>
struct _PROCESS_EXTENDED_BASIC_INFORMATION_T
{
    T Size;  // Must be set to structure size on input
    _PROCESS_BASIC_INFORMATION_T<T> BasicInfo;
    struct
    {
        uint32_t IsProtectedProcess : 1;
        uint32_t IsWow64Process : 1;
        uint32_t IsProcessDeleting : 1;
        uint32_t IsCrossSessionCreate : 1;
        uint32_t IsFrozen : 1;
        uint32_t IsBackground : 1;
        uint32_t IsStronglyNamed : 1;
        uint32_t SpareBits : 25;
    }Flags;
};

template<typename T>
struct _THREAD_BASIC_INFORMATION_T
{
    NTSTATUS ExitStatus;
    T TebBaseAddress;
    _CLIENT_ID_T<T> ClientID;
    T AffinityMask;
    LONG Priority;
    LONG BasePriority;
};

template<typename T>
struct _VM_COUNTERS_T
{
    T PeakVirtualSize;
    T VirtualSize;
    uint32_t PageFaultCount;
    T PeakWorkingSetSize;
    T WorkingSetSize;
    T QuotaPeakPagedPoolUsage;
    T QuotaPagedPoolUsage;
    T QuotaPeakNonPagedPoolUsage;
    T QuotaNonPagedPoolUsage;
    T PagefileUsage;
    T PeakPagefileUsage;
};

template<typename T>
struct _SYSTEM_THREAD_INFORMATION_T
{
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER CreateTime;
    uint32_t WaitTime;
    T StartAddress;
    _CLIENT_ID_T<T> ClientId;
    LONG Priority;
    LONG BasePriority;
    uint32_t ContextSwitches;
    uint32_t ThreadState;
    uint32_t WaitReason;
};

template<typename T>
struct _SYSTEM_EXTENDED_THREAD_INFORMATION_T
{
    _SYSTEM_THREAD_INFORMATION_T<T> ThreadInfo;
    T StackBase;
    T StackLimit;
    T Win32StartAddress;
    T TebBase;
    T Reserved[ 3 ];
};

template<typename T>
struct _SYSTEM_PROCESS_INFORMATION_T
{
    uint32_t NextEntryOffset;
    uint32_t NumberOfThreads;
    LARGE_INTEGER WorkingSetPrivateSize;
    uint32_t HardFaultCount;
    uint32_t NumberOfThreadsHighWatermark;
    ULONGLONG CycleTime;
    LARGE_INTEGER CreateTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER KernelTime;
    _UNICODE_STRING_T<T> ImageName;
    LONG BasePriority;
    T UniqueProcessId;
    T InheritedFromUniqueProcessId;
    uint32_t HandleCount;
    uint32_t SessionId;
    T UniqueProcessKey;
    _VM_COUNTERS_T<T> VmCounters;
    T PrivatePageCount;
    IO_COUNTERS IoCounters;
    _SYSTEM_EXTENDED_THREAD_INFORMATION_T<T> Threads[ 1 ];
};

template<typename T>
struct _SYSTEM_HANDLE_T
{
    uint32_t ProcessId;
    uint8_t ObjectTypeNumber;
    uint8_t Flags;
    uint16_t Handle;
    T Object;
    ACCESS_MASK GrantedAccess;
};

template<typename T>
struct _SYSTEM_HANDLE_INFORMATION_T
{
    uint32_t HandleCount;
    _SYSTEM_HANDLE_T<T> Handles[ 1 ];
};

template<typename T>
struct _OBJECT_TYPE_INFORMATION_T
{
    _UNICODE_STRING_T<T> Name;
    uint32_t TotalNumberOfObjects;
    uint32_t TotalNumberOfHandles;
    uint32_t TotalPagedPoolUsage;
    uint32_t TotalNonPagedPoolUsage;
    uint32_t TotalNamePoolUsage;
    uint32_t TotalHandleTableUsage;
    uint32_t HighWaterNumberOfObjects;
    uint32_t HighWaterNumberOfHandles;
    uint32_t HighWaterPagedPoolUsage;
    uint32_t HighWaterNonPagedPoolUsage;
    uint32_t HighWaterNamePoolUsage;
    uint32_t HighWaterHandleTableUsage;
    uint32_t InvalidAttributes;
    GENERIC_MAPPING GenericMapping;
    uint32_t ValidAccess;
    BOOLEAN SecurityRequired;
    BOOLEAN MaintainHandleCount;
    uint16_t MaintainTypeList;
    POOL_TYPE PoolType;
    uint32_t PagedPoolUsage;
    uint32_t NonPagedPoolUsage;
};

template<typename T>
struct _OBJECT_ATTRIBUTES_T
{
    uint32_t Length;
    T RootDirectory;
    T ObjectName;
    uint32_t Attributes;
    T SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
    T SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
};

struct _XSAVE_FORMAT64
{
    uint16_t ControlWord;
    uint16_t StatusWord;
    uint8_t TagWord;
    uint8_t Reserved1;
    uint16_t ErrorOpcode;
    uint32_t ErrorOffset;
    uint16_t ErrorSelector;
    uint16_t Reserved2;
    uint32_t DataOffset;
    uint16_t DataSelector;
    uint16_t Reserved3;
    uint32_t MxCsr;
    uint32_t MxCsr_Mask;
    _M128A FloatRegisters[ 8 ];
    _M128A XmmRegisters[ 16 ];
    uint8_t Reserved4[ 96 ];
};

template<typename T>
struct _CONTEXT_T;

template<>
struct _CONTEXT_T<uint32_t>
{
    uint32_t ContextFlags;
    uint32_t Dr0;
    uint32_t Dr1;
    uint32_t Dr2;
    uint32_t Dr3;
    uint32_t Dr6;
    uint32_t Dr7;
    WOW64_FLOATING_SAVE_AREA FloatSave;
    uint32_t SegGs;
    uint32_t SegFs;
    uint32_t SegEs;
    uint32_t SegDs;
    uint32_t Edi;
    uint32_t Esi;
    uint32_t Ebx;
    uint32_t Edx;
    uint32_t Ecx;
    uint32_t Eax;
    uint32_t Ebp;
    uint32_t Eip;
    uint32_t SegCs;              // MUST BE SANITIZED
    uint32_t EFlags;             // MUST BE SANITIZED
    uint32_t Esp;
    uint32_t SegSs;
    uint8_t  ExtendedRegisters[ WOW64_MAXIMUM_SUPPORTED_EXTENSION ];
};

template<>
struct _CONTEXT_T<uint64_t>
{
    uint64_t P1Home;
    uint64_t P2Home;
    uint64_t P3Home;
    uint64_t P4Home;
    uint64_t P5Home;
    uint64_t P6Home;
    uint32_t ContextFlags;
    uint32_t MxCsr;
    uint16_t SegCs;
    uint16_t SegDs;
    uint16_t SegEs;
    uint16_t SegFs;
    uint16_t SegGs;
    uint16_t SegSs;
    uint32_t EFlags;
    uint64_t Dr0;
    uint64_t Dr1;
    uint64_t Dr2;
    uint64_t Dr3;
    uint64_t Dr6;
    uint64_t Dr7;
    uint64_t Rax;
    uint64_t Rcx;
    uint64_t Rdx;
    uint64_t Rbx;
    uint64_t Rsp;
    uint64_t Rbp;
    uint64_t Rsi;
    uint64_t Rdi;
    uint64_t R8;
    uint64_t R9;
    uint64_t R10;
    uint64_t R11;
    uint64_t R12;
    uint64_t R13;
    uint64_t R14;
    uint64_t R15;
    uint64_t Rip;
    _XSAVE_FORMAT64 FltSave;
    _M128A Header[ 2 ];
    _M128A Legacy[ 8 ];
    _M128A Xmm0;
    _M128A Xmm1;
    _M128A Xmm2;
    _M128A Xmm3;
    _M128A Xmm4;
    _M128A Xmm5;
    _M128A Xmm6;
    _M128A Xmm7;
    _M128A Xmm8;
    _M128A Xmm9;
    _M128A Xmm10;
    _M128A Xmm11;
    _M128A Xmm12;
    _M128A Xmm13;
    _M128A Xmm14;
    _M128A Xmm15;
    _M128A VectorRegister[ 26 ];
    uint64_t VectorControl;
    uint64_t DebugControl;
    uint64_t LastBranchToRip;
    uint64_t LastBranchFromRip;
    uint64_t LastExceptionToRip;
    uint64_t LastExceptionFromRip;

    _CONTEXT_T<uint64_t>& FromCtx32( const _CONTEXT_T<uint32_t>& ctx32 )
    {
        ContextFlags = ctx32.ContextFlags;
        Dr0 = ctx32.Dr0;
        Dr1 = ctx32.Dr1;
        Dr2 = ctx32.Dr2;
        Dr3 = ctx32.Dr3;
        Dr6 = ctx32.Dr6;
        Dr7 = ctx32.Dr7;
        SegGs = static_cast< uint16_t >( ctx32.SegGs );
        SegFs = static_cast< uint16_t >( ctx32.SegFs );
        SegEs = static_cast< uint16_t >( ctx32.SegEs );
        SegDs = static_cast< uint16_t >( ctx32.SegDs );
        SegCs = static_cast< uint16_t >( ctx32.SegCs );
        SegSs = static_cast< uint16_t >( ctx32.SegSs );
        Rdi = ctx32.Edi;
        Rsi = ctx32.Esi;
        Rbx = ctx32.Ebx;
        Rdx = ctx32.Edx;
        Rcx = ctx32.Ecx;
        Rax = ctx32.Eax;
        Rbp = ctx32.Ebp;
        Rip = ctx32.Eip;
        Rsp = ctx32.Esp;
        EFlags = ctx32.EFlags;

        return *this;
    }
    };

#ifndef CONTEXT_AMD64
#define CONTEXT_AMD64 0x100000
#endif

#define CONTEXT64_CONTROL (CONTEXT_AMD64 | 0x1L)
#define CONTEXT64_INTEGER (CONTEXT_AMD64 | 0x2L)
#define CONTEXT64_SEGMENTS (CONTEXT_AMD64 | 0x4L)
#define CONTEXT64_FLOATING_POINT  (CONTEXT_AMD64 | 0x8L)
#define CONTEXT64_DEBUG_REGISTERS (CONTEXT_AMD64 | 0x10L)
#define CONTEXT64_FULL (CONTEXT64_CONTROL | CONTEXT64_INTEGER | CONTEXT64_FLOATING_POINT)
#define CONTEXT64_ALL (CONTEXT64_CONTROL | CONTEXT64_INTEGER | CONTEXT64_SEGMENTS | CONTEXT64_FLOATING_POINT | CONTEXT64_DEBUG_REGISTERS)
#define CONTEXT64_XSTATE (CONTEXT_AMD64 | 0x20L)

template<typename T>
struct _PEB_LDR_DATA2_T
{
    uint32_t Length;
    uint8_t Initialized;
    T SsHandle;
    _LIST_ENTRY_T<T> InLoadOrderModuleList;
    _LIST_ENTRY_T<T> InMemoryOrderModuleList;
    _LIST_ENTRY_T<T> InInitializationOrderModuleList;
    T EntryInProgress;
    uint8_t ShutdownInProgress;
    T ShutdownThreadId;
};

template<typename T>
struct _LDR_DATA_TABLE_ENTRY_BASE_T
{
    _LIST_ENTRY_T<T> InLoadOrderLinks;
    _LIST_ENTRY_T<T> InMemoryOrderLinks;
    _LIST_ENTRY_T<T> InInitializationOrderLinks;
    T DllBase;
    T EntryPoint;
    uint32_t SizeOfImage;
    _UNICODE_STRING_T<T> FullDllName;
    _UNICODE_STRING_T<T> BaseDllName;
    uint32_t Flags;
    uint16_t LoadCount;
    uint16_t TlsIndex;
    _LIST_ENTRY_T<T> HashLinks;
    uint32_t TimeDateStamp;
    T EntryPointActivationContext;
    T PatchInformation;
};

template<typename T>
struct _RTL_INVERTED_FUNCTION_TABLE_ENTRY
{
    T     ExceptionDirectory;   // PIMAGE_RUNTIME_FUNCTION_ENTRY
    T     ImageBase;
    uint32_t ImageSize;
    uint32_t SizeOfTable;
};

using _UNICODE_STRING32 = _UNICODE_STRING_T<uint32_t>;
using _UNICODE_STRING64 = _UNICODE_STRING_T<uint64_t>;
using UNICODE_STRING_T = _UNICODE_STRING_T<uintptr_t>;

using _PEB32 = _PEB_T<uint32_t>;
using _PEB64 = _PEB_T<uint64_t>;
using PEB_T = _PEB_T<uintptr_t>;

using _TEB32 = _TEB_T<uint32_t>;
using _TEB64 = _TEB_T<uint64_t>;
using TEB_T = _TEB_T<uintptr_t>;

using _PEB_LDR_DATA232 = _PEB_LDR_DATA2_T<uint32_t>;
using _PEB_LDR_DATA264 = _PEB_LDR_DATA2_T<uint64_t>;
using PEB_LDR_DATA_T = _PEB_LDR_DATA2_T<uintptr_t>;

using _LDR_DATA_TABLE_ENTRY_BASE32 = _LDR_DATA_TABLE_ENTRY_BASE_T<uint32_t>;
using _LDR_DATA_TABLE_ENTRY_BASE64 = _LDR_DATA_TABLE_ENTRY_BASE_T<uint64_t>;
using LDR_DATA_TABLE_ENTRY_BASE_T = _LDR_DATA_TABLE_ENTRY_BASE_T<uintptr_t>;

using _CONTEXT32 = _CONTEXT_T<uint32_t>;
using _CONTEXT64 = _CONTEXT_T<uint64_t>;
using CONTEXT_T = _CONTEXT_T<uintptr_t>;

using _SECTION_BASIC_INFORMATION32 = _SECTION_BASIC_INFORMATION_T<uint32_t>;
using _SECTION_BASIC_INFORMATION64 = _SECTION_BASIC_INFORMATION_T<uint64_t>;
using SECTION_BASIC_INFORMATION_T = _SECTION_BASIC_INFORMATION_T<uintptr_t>;

using _SYSTEM_HANDLE_INFORMATION32 = _SYSTEM_HANDLE_INFORMATION_T<uint32_t>;
using _SYSTEM_HANDLE_INFORMATION64 = _SYSTEM_HANDLE_INFORMATION_T<uint64_t>;
using SYSTEM_HANDLE_INFORMATION_T = _SYSTEM_HANDLE_INFORMATION_T<uintptr_t>;

using _OBJECT_TYPE_INFORMATION32 = _OBJECT_TYPE_INFORMATION_T<uint32_t>;
using _OBJECT_TYPE_INFORMATION64 = _OBJECT_TYPE_INFORMATION_T<uint64_t>;
using OBJECT_TYPE_INFORMATION_T = _OBJECT_TYPE_INFORMATION_T<uintptr_t>;

using _OBJECT_ATTRIBUTES32 = _OBJECT_ATTRIBUTES_T<uint32_t>;
using _OBJECT_ATTRIBUTES64 = _OBJECT_ATTRIBUTES_T<uint64_t>;
using OBJECT_ATTRIBUTES_T = _OBJECT_ATTRIBUTES_T<uintptr_t>;

using _ACTCTXW32 = _ACTCTXW_T<uint32_t>;
using _ACTCTXW64 = _ACTCTXW_T<uint64_t>;
using ACTCTXW_T = _ACTCTXW_T<uintptr_t>;

typedef enum TIC
{
    ThreadBasicInformation ,
    ThreadTimes ,
    ThreadPriority ,
    ThreadBasePriority ,
    ThreadAffinityMask ,
    ThreadImpersonationToken ,
    ThreadDescriptorTableEntry ,
    ThreadEnableAlignmentFaultFixup ,
    ThreadEventPair ,
    ThreadQuerySetWin32StartAddress ,
    ThreadZeroTlsCell ,
    ThreadPerformanceCount ,
    ThreadAmILastThread ,
    ThreadIdealProcessor ,
    ThreadPriorityBoost ,
    ThreadSetTlsArrayAddress ,
    ThreadHideFromDebugger = 17
};

template<typename T>
struct s_InitStaticTls
{
    _LDR_DATA_TABLE_ENTRY_BASE_T<T> EntryBase;
    T pLdrpHandleTlsData;
};

template<typename T>
struct sWinMainExe
{
    sWinMainExe( T pInstance , T pPrevInstance , T pCmdLine , int nCmdShow , T pEntryPoint )
    {
        this->pInstance = pInstance;
        this->pPrevInstance = pPrevInstance;
        this->pCmdLine = pCmdLine;
        this->nCmdShow = nCmdShow;
        this->pEntryPoint = pEntryPoint;
    }

    T pInstance;
    T pPrevInstance;
    T pCmdLine;
    int nCmdShow;
    T pEntryPoint;
};

uintptr_t FindPattern( std::string moduleName , std::string pattern );

std::wstring GetCompileTimeDateW();
std::string GetCompileTimeDateA();
stdString GetCompileTimeDate();

//https://www.codeproject.com/Tips/139349/Getting-the-address-of-a-function-in-a-DLL-loaded

//-----------------------------------------------------------------------------

/* PE Library */

/*#include "../libs/pe_lib/pe_bliss.h"
#ifndef _DEBUG
#ifdef ENVIRONMENT64
#pragma comment(lib,"..\\x64\\Release\\pe_bliss.lib")
#else
#pragma comment(lib,"..\\Release\\pe_bliss.lib")
#endif
#else
#ifdef ENVIRONMENT64
#pragma comment(lib,"..\\x64\\Debug\\pe_bliss.lib")
#else
#pragma comment(lib,"..\\Debug\\pe_bliss.lib")
#endif
#endif*/

#endif 