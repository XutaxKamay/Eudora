//====== Copyright © 1996-2005, Valve Corporation, All rights reserved. =======//
//
// Purpose:
//
// $NoKeywords: $
//
// Serialization/unserialization buffer
//=============================================================================//
#ifndef UTLBUFFER
#define UTLBUFFER
#pragma once

#pragma warning(disable:4100)

#pragma warning(disable:4127) //conditional operation is constant
#define IsX360() (0)

struct characterset_t
{
    char Set[ 256 ];
};

// This is essentially a strpbrk() using a precalculated lookup table
//-----------------------------------------------------------------------------
// Purpose: builds a simple lookup table of a group of important characters
// Input  : *pSetBuffer - pointer to the buffer for the group
//			*pSetString - list of characters to flag
//-----------------------------------------------------------------------------
extern void CharacterSetBuild( characterset_t *pSetBuffer , const char *pSetString );

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *pSetBuffer - pre-build group buffer
//			character - character to lookup
// Output : int - 1 if the character was in the Set
//-----------------------------------------------------------------------------
#define IN_CHARACTERSET( SetBuffer, character )		((SetBuffer).Set[(character)])

//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
struct typedescription_t;
struct datamap_t;

class CByteswap
{
public:
    CByteswap()
    {
        // Default behavior sets the target endian to match the machine native endian (no swap).
        SetTargetBigEndian( IsMachineBigEndian() );
    }

    //-----------------------------------------------------------------------------
    // Write a single field.
    //-----------------------------------------------------------------------------
    void SwapFieldToTargetEndian( void* pOutputBuffer , void *pData , typedescription_t *pField );

    //-----------------------------------------------------------------------------
    // Write a block of fields.  Works a bit like the saverestore code.
    //-----------------------------------------------------------------------------
    void SwapFieldsToTargetEndian( void *pOutputBuffer , void *pBaseData , datamap_t *pDataMap );

    // Swaps fields for the templated type to the output buffer.
    template<typename T> inline void SwapFieldsToTargetEndian( T* pOutputBuffer , void *pBaseData , unsigned int objectCount = 1 )
    {
        for ( unsigned int i = 0; i < objectCount; ++i , ++pOutputBuffer )
        {
            SwapFieldsToTargetEndian( ( void* ) pOutputBuffer , pBaseData , &T::m_DataMap );
            pBaseData = ( uint8_t* ) pBaseData + sizeof( T );
        }
    }

    // Swaps fields for the templated type in place.
    template<typename T> inline void SwapFieldsToTargetEndian( T* pOutputBuffer , unsigned int objectCount = 1 )
    {
        SwapFieldsToTargetEndian<T>( pOutputBuffer , ( void* ) pOutputBuffer , objectCount );
    }

    //-----------------------------------------------------------------------------
    // True if the current machine is detected as big endian.
    // (Endienness is effectively detected at compile time when optimizations are
    // enabled)
    //-----------------------------------------------------------------------------
    static bool IsMachineBigEndian()
    {
        short nIsBigEndian = 1;

        // if we are big endian, the first uint8_t will be a 0, if little endian, it will be a one.
        return ( bool ) ( 0 == *( char * ) &nIsBigEndian );
    }

    //-----------------------------------------------------------------------------
    // Sets the target uint8_t ordering we are swapping to or from.
    //
    // Braindead Endian Reference:
    //		x86 is LITTLE Endian
    //		PowerPC is BIG Endian
    //-----------------------------------------------------------------------------
    inline void SetTargetBigEndian( bool bigEndian )
    {
        m_bBigEndian = bigEndian;
        m_bSwapBytes = IsMachineBigEndian() != bigEndian;
    }

    // Changes target endian
    inline void FlipTargetEndian( void )
    {
        m_bSwapBytes = !m_bSwapBytes;
        m_bBigEndian = !m_bBigEndian;
    }

    // Forces uint8_t swapping state, regardless of endianess
    inline void ActivateByteSwapping( bool bActivate )
    {
        SetTargetBigEndian( IsMachineBigEndian() != bActivate );
    }

    //-----------------------------------------------------------------------------
    // Returns true if the target machine is the same as this one in endianness.
    //
    // Used to determine when a byteswap needs to take place.
    //-----------------------------------------------------------------------------
    inline bool IsSwappingBytes( void )	// Are bytes being swapped?
    {
        return m_bSwapBytes;
    }

    inline bool IsTargetBigEndian( void )	// What is the current target endian?
    {
        return m_bBigEndian;
    }

    //-----------------------------------------------------------------------------
    // IsByteSwapped()
    //
    // When supplied with a chunk of input data and a constant or magic number
    // (in native format) determines the endienness of the current machine in
    // relation to the given input data.
    //
    // Returns:
    //		1  if input is the same as nativeConstant.
    //		0  if input is byteswapped relative to nativeConstant.
    //		-1 if input is not the same as nativeConstant and not byteswapped either.
    //
    // ( This is useful for detecting byteswapping in magic numbers in structure
    // headers for example. )
    //-----------------------------------------------------------------------------
    template<typename T> inline int SourceIsNativeEndian( T input , T nativeConstant )
    {
        // If it's the same, it isn't byteswapped:
        if ( input == nativeConstant )
            return 1;

        int output;
        LowLevelByteSwap<T>( &output , &input );
        if ( output == nativeConstant )
            return 0;

        assert( 0 );		// if we Get here, input is neither a swapped nor unswapped version of nativeConstant.
        return -1;
    }

    //-----------------------------------------------------------------------------
    // Swaps an input buffer full of type T into the given output buffer.
    //
    // Swaps [count] items from the inputBuffer to the outputBuffer.
    // If inputBuffer is omitted or NULL, then it is assumed to be the same as
    // outputBuffer - effectively swapping the contents of the buffer in place.
    //-----------------------------------------------------------------------------
    template<typename T> inline void SwapBuffer( T* outputBuffer , T* inputBuffer = NULL , int count = 1 )
    {
        assert( count >= 0 );
        assert( outputBuffer );

        // Fail gracefully in release:
        if ( count <= 0 || !outputBuffer )
            return;

        // Optimization for the case when we are swapping in place.
        if ( inputBuffer == NULL )
        {
            inputBuffer = outputBuffer;
        }

        // Swap everything in the buffer:
        for ( int i = 0; i < count; i++ )
        {
            LowLevelByteSwap<T>( &outputBuffer[ i ] , &inputBuffer[ i ] );
        }
    }

    //-----------------------------------------------------------------------------
    // Swaps an input buffer full of type T into the given output buffer.
    //
    // Swaps [count] items from the inputBuffer to the outputBuffer.
    // If inputBuffer is omitted or NULL, then it is assumed to be the same as
    // outputBuffer - effectively swapping the contents of the buffer in place.
    //-----------------------------------------------------------------------------
    template<typename T> inline void SwapBufferToTargetEndian( T* outputBuffer , T* inputBuffer = NULL , int count = 1 )
    {
        assert( count >= 0 );
        assert( outputBuffer );

        // Fail gracefully in release:
        if ( count <= 0 || !outputBuffer )
            return;

        // Optimization for the case when we are swapping in place.
        if ( inputBuffer == NULL )
        {
            inputBuffer = outputBuffer;
        }

        // Are we already the correct endienness? ( or are we swapping 1 uint8_t items? )
        if ( !m_bSwapBytes || ( sizeof( T ) == 1 ) )
        {
// If we were just going to swap in place then return.
            if ( !inputBuffer )
                return;

            // Otherwise copy the inputBuffer to the outputBuffer:
            memcpy( outputBuffer , inputBuffer , count * sizeof( T ) );
            return;
        }

        // Swap everything in the buffer:
        for ( int i = 0; i < count; i++ )
        {
            LowLevelByteSwap<T>( &outputBuffer[ i ] , &inputBuffer[ i ] );
        }
    }

private:
    //-----------------------------------------------------------------------------
    // The lowest level uint8_t swapping workhorse of doom.  output always contains the
    // swapped version of input.  ( Doesn't compare machine to target endianness )
    //-----------------------------------------------------------------------------
    template<typename T> static void LowLevelByteSwap( T *output , T *input )
    {
        T temp = *output;
    #if defined( _X360 )
            // Intrinsics need the source type to be fixed-point
        DWORD* word = ( DWORD* ) input;
        switch ( sizeof( T ) )
        {
            case 8:
            {
                __storewordbytereverse( *word , 0 , &temp );
                __storewordbytereverse( *( word + 1 ) , 4 , &temp );
            }
            break;

            case 4:
                __storewordbytereverse( *word , 0 , &temp );
                break;

            case 2:
                __storeshortbytereverse( *input , 0 , &temp );
                break;

            default:
                assert( "Invalid size in CByteswap::LowLevelByteSwap" && 0 );
        }
    #else
        for ( int i = 0; i < sizeof( T ); i++ )
        {
            ( ( unsigned char* ) &temp )[ i ] = ( ( unsigned char* ) input )[ sizeof( T ) - ( i + 1 ) ];
        }
    #endif
        memcpy( output , &temp , sizeof( T ) );
    }

    unsigned int m_bSwapBytes : 1;
    unsigned int m_bBigEndian : 1;
};

//-----------------------------------------------------------------------------
// Description of character conversions for string output
// Here's an example of how to use the macros to define a character conversion
// BEGIN_CHAR_CONVERSION( CStringConversion, '\\' )
//	{ '\n', "n" },
//	{ '\t', "t" }
// END_CHAR_CONVERSION( CStringConversion, '\\' )
//-----------------------------------------------------------------------------
class CUtlCharConversion
{
public:
    struct ConversionArray_t
    {
        char m_nActualChar;
        char *m_pReplacementString;
    };

    CUtlCharConversion( char nEscapeChar , const char *pDelimiter , int nCount , ConversionArray_t *pArray );
    char GetEscapeChar() const;
    const char *GetDelimiter() const;
    int GetDelimiterLength() const;

    const char *GetConversionString( char c ) const;
    int GetConversionLength( char c ) const;
    int MaxConversionLength() const;

    // Finds a conversion for the passed-in string, returns length
    virtual char FindConversion( const char *pString , int *pLength );

protected:
    struct ConversionInfo_t
    {
        int m_nLength;
        char *m_pReplacementString;
    };

    char m_nEscapeChar;
    const char *m_pDelimiter;
    int m_nDelimiterLength;
    int m_nCount;
    int m_nMaxConversionLength;
    char m_pList[ 255 ];
    ConversionInfo_t m_pReplacements[ 255 ];
};

#define BEGIN_CHAR_CONVERSION( _name, _delimiter, _escapeChar )	\
	static CUtlCharConversion::ConversionArray_t s_pConversionArray ## _name[] = {
#define END_CHAR_CONVERSION( _name, _delimiter, _escapeChar ) \
	}; \
	CUtlCharConversion _name( _escapeChar, _delimiter, sizeof( s_pConversionArray ## _name ) / sizeof( CUtlCharConversion::ConversionArray_t ), s_pConversionArray ## _name )

#define BEGIN_CUSTOM_CHAR_CONVERSION( _className, _name, _delimiter, _escapeChar ) \
	static CUtlCharConversion::ConversionArray_t s_pConversionArray ## _name[] = {
#define END_CUSTOM_CHAR_CONVERSION( _className, _name, _delimiter, _escapeChar ) \
	}; \
	_className _name( _escapeChar, _delimiter, sizeof( s_pConversionArray ## _name ) / sizeof( CUtlCharConversion::ConversionArray_t ), s_pConversionArray ## _name )

//-----------------------------------------------------------------------------
// Character conversions for C strings
//-----------------------------------------------------------------------------
CUtlCharConversion *GetCStringCharConversion();

//-----------------------------------------------------------------------------
// Character conversions for quoted strings, with no escape sequences
//-----------------------------------------------------------------------------
CUtlCharConversion *GetNoEscCharConversion();

//-----------------------------------------------------------------------------
// Macro to Set overflow functions easily
//-----------------------------------------------------------------------------
#define SetUtlBufferOverflowFuncs( _get, _put )	\
	SetOverflowFuncs( static_cast <UtlBufferOverflowFunc_t>( _get ), static_cast <UtlBufferOverflowFunc_t>( _put ) )

//-----------------------------------------------------------------------------
// Command parsing..
//-----------------------------------------------------------------------------
class CUtlBuffer
{
public:
    enum SeekType_t
    {
        SEEK_HEAD = 0 ,
        SEEK_CURRENT ,
        SEEK_TAIL
    };

    // flags
    enum BufferFlags_t
    {
        TEXT_BUFFER = 0x1 ,			// Describes how Get + put work (as strings, or binary)
        EXTERNAL_GROWABLE = 0x2 ,	// This is used w/ external buffers and causes the utlbuf to switch to reallocatable memory if an overflow happens when Putting.
        CONTAINS_CRLF = 0x4 ,		// For text buffers only, does this contain \n or \n\r?
        READ_ONLY = 0x8 ,			// For external buffers; prevents null termination from happening.
        AUTO_TABS_DISABLED = 0x10 ,	// Used to disable/enable push/pop tabs
    };

    // Overflow functions when a Get or put overflows
    typedef bool ( CUtlBuffer::*UtlBufferOverflowFunc_t )( int nSize );

    // Constructors for growable + external buffers for serialization/unserialization
    CUtlBuffer( int growSize = 0 , int initSize = 0 , int nFlags = 0 );
    CUtlBuffer( const void* pBuffer , int size , int nFlags = 0 );
    // This one isn't actually defined so that we catch contructors that are trying to pass a bool in as the third param.
    CUtlBuffer( const void *pBuffer , int size , bool crap );

    unsigned char	GetFlags() const;

    // NOTE: This will assert if you attempt to recast it in a way that
    // is not compatible. The only valid conversion is binary-> text w/CRLF
    void			SetBufferType( bool bIsText , bool bContainsCRLF );

    // Makes sure we've got at least this much memory
    void			EnsureCapacity( int num );

    // Attaches the buffer to external memory....
    void			SetExternalBuffer( void* pMemory , int nSize , int nInitialPut , int nFlags = 0 );
    bool			IsExternallyAllocated() const;
    void			AssumeMemory( void *pMemory , int nSize , int nInitialPut , int nFlags = 0 );

    __forceinline void ActivateByteSwappingIfBigEndian( void )
    {
        if ( IsX360() )
            ActivateByteSwapping( true );
    }

    // Controls endian-ness of binary utlbufs - default matches the current platform
    void			ActivateByteSwapping( bool bActivate );
    void			SetBigEndian( bool bigEndian );
    bool			IsBigEndian( void );

    // Resets the buffer; but doesn't free memory
    void			Clear();

    // Clears out the buffer; frees memory
    void			Purge();

    // Read stuff out.
    // Binary mode: it'll just read the bits directly in, and characters will be
    //		read for strings until a null character is reached.
    // Text mode: it'll parse the file, turning text #s into real numbers.
    //		GetString will read a string until a space is reached
    char			GetChar();
    unsigned char	GetUnsignedChar();
    short			GetShort();
    unsigned short	GetUnsignedShort();
    int				GetInt();
    int				GetIntHex();
    unsigned int	GetUnsignedInt();
    float			GetFloat();
    double			GetDouble();
    void			GetString( char* pString , int nMaxChars = 0 );
    void			Get( void* pMem , int size );
    void			GetLine( char* pLine , int nMaxChars = 0 );

    // Used for getting objects that have a byteswap datadesc defined
    template <typename T> void GetObjects( T *dest , int count = 1 );

    // This will Get at least 1 uint8_t and up to nSize bytes.
    // It will return the number of bytes actually read.
    int				GetUpTo( void *pMem , int nSize );

    // This version of GetString converts \" to \\ and " to \, etc.
    // It also reads a " at the beginning and end of the string
    void			GetDelimitedString( CUtlCharConversion *pConv , char *pString , int nMaxChars = 0 );
    char			GetDelimitedChar( CUtlCharConversion *pConv );

    // This will return the # of characters of the string about to be read out
    // NOTE: The count will *include* the terminating 0!!
    // In binary mode, it's the number of characters until the next 0
    // In text mode, it's the number of characters until the next space.
    int				PeekStringLength();

    // This version of PeekStringLength converts \" to \\ and " to \, etc.
    // It also reads a " at the beginning and end of the string
    // NOTE: The count will *include* the terminating 0!!
    // In binary mode, it's the number of characters until the next 0
    // In text mode, it's the number of characters between "s (checking for \")
    // Specifying false for bActualSize will return the pre-translated number of characters
    // including the delimiters and the escape characters. So, \n counts as 2 characters when bActualSize == false
    // and only 1 character when bActualSize == true
    int				PeekDelimitedStringLength( CUtlCharConversion *pConv , bool bActualSize = true );

    // Just like scanf, but doesn't work in binary mode
    int				Scanf( const char* pFmt , ... );
    int				VaScanf( const char* pFmt , va_list list );

    // Eats white space, advances Get index
    void			EatWhiteSpace();

    // Eats C++ style comments
    bool			EatCPPComment();

    // (For text buffers only)
    // Parse a token from the buffer:
    // Grab all text that lies between a starting delimiter + ending delimiter
    // (skipping whitespace that leads + trails both delimiters).
    // If successful, the Get index is advanced and the function returns true,
    // otherwise the index is not advanced and the function returns false.
    bool			ParseToken( const char *pStartingDelim , const char *pEndingDelim , char* pString , int nMaxLen );

    // Advance the Get index until after the particular string is found
    // Do not eat whitespace before starting. Return false if it failed
    // String test is case-insensitive.
    bool			GetToken( const char *pToken );

    // Parses the next token, given a Set of character breaks to stop at
    // Returns the length of the token parsed in bytes (-1 if none parsed)
    int				ParseToken( characterset_t *pBreaks , char *pTokenBuf , int nMaxLen , bool bParseComments = true );

    // Write stuff in
    // Binary mode: it'll just write the bits directly in, and strings will be
    //		written with a null terminating character
    // Text mode: it'll convert the numbers to text versions
    //		PutString will not write a terminating character
    void			PutChar( char c );
    void			PutUnsignedChar( unsigned char uc );
    void			PutShort( short s );
    void			PutUnsignedShort( unsigned short us );
    void			PutInt( int i );
    void			PutUnsignedInt( unsigned int u );
    void			PutFloat( float f );
    void			PutDouble( double d );
    void			PutString( const char* pString );
    void			Put( const void* pMem , int size );

    // Used for putting objects that have a byteswap datadesc defined
    template <typename T> void PutObjects( T *src , int count = 1 );

    // This version of PutString converts \ to \\ and " to \", etc.
    // It also places " at the beginning and end of the string
    void			PutDelimitedString( CUtlCharConversion *pConv , const char *pString );
    void			PutDelimitedChar( CUtlCharConversion *pConv , char c );

    // Just like printf, writes a terminating zero in binary mode
    void			Printf( const char* pFmt , ... );
    void			VaPrintf( const char* pFmt , va_list list );

    // What am I writing (put)/reading (Get)?
    void* PeekPut( int offset = 0 );
    const void* PeekGet( int offset = 0 ) const;
    const void* PeekGet( int nMaxSize , int nOffset );

    // Where am I writing (put)/reading (Get)?
    int TellPut() const;
    int TellGet() const;

    // What's the most I've ever written?
    int TellMaxPut() const;

    // How many bytes remain to be read?
    // NOTE: This is not accurate for streaming text files; it overshoots
    int GetBytesRemaining() const;

    // Change where I'm writing (put)/reading (Get)
    void SeekPut( SeekType_t type , int offset );
    void SeekGet( SeekType_t type , int offset );

    // Buffer base
    const void* Base() const;
    void* Base();

    // memory allocation size, does *not* reflect size written or read,
    //	use TellPut or TellGet for that
    int Size() const;

    // Am I a text buffer?
    bool IsText() const;

    // Can I grow if I'm externally allocated?
    bool IsGrowable() const;

    // Am I valid? (overflow or underflow error), Once invalid it stays invalid
    bool IsValid() const;

    // Do I contain carriage return/linefeeds?
    bool ContainsCRLF() const;

    // Am I read-only
    bool IsReadOnly() const;

    // Converts a buffer from a CRLF buffer to a CR buffer (and back)
    // Returns false if no conversion was necessary (and outBuf is left untouched)
    // If the conversion occurs, outBuf will be cleared.
    bool ConvertCRLF( CUtlBuffer &outBuf );

    // Push/pop pretty-printing tabs
    void PushTab();
    void PopTab();

    // Temporarily disables pretty print
    void EnableTabs( bool bEnable );

protected:
    // error flags
    enum
    {
        PUT_OVERFLOW = 0x1 ,
        GET_OVERFLOW = 0x2 ,
        MAX_ERROR_FLAG = GET_OVERFLOW ,
    };

    void SetOverflowFuncs( UtlBufferOverflowFunc_t getFunc , UtlBufferOverflowFunc_t putFunc );

    bool OnPutOverflow( int nSize );
    bool OnGetOverflow( int nSize );

protected:
    // Checks if a Get/put is ok
    bool CheckPut( int size );
    bool CheckGet( int size );

    void AddNullTermination();

    // Methods to help with pretty-printing
    bool WasLastCharacterCR();
    void PutTabs();

    // Help with delimited stuff
    char GetDelimitedCharInternal( CUtlCharConversion *pConv );
    void PutDelimitedCharInternal( CUtlCharConversion *pConv , char c );

    // Default overflow funcs
    bool PutOverflow( int nSize );
    bool GetOverflow( int nSize );

    // Does the next bytes of the buffer match a pattern?
    bool PeekStringMatch( int nOffset , const char *pString , int nLen );

    // Peek size of line to come, check memory bound
    int	PeekLineLength();

    // How much whitespace should I skip?
    int PeekWhiteSpace( int nOffset );

    // Checks if a peek Get is ok
    bool CheckPeekGet( int nOffset , int nSize );

    // Call this to peek arbitrarily long into memory. It doesn't fail unless
    // it can't read *anything* new
    bool CheckArbitraryPeekGet( int nOffset , int &nIncrement );

    template <typename T> void GetType( T& dest , const char *pszFmt );
    template <typename T> void GetTypeBin( T& dest );
    template <typename T> void GetObject( T *src );

    template <typename T> void PutType( T src , const char *pszFmt );
    template <typename T> void PutTypeBin( T src );
    template <typename T> void PutObject( T *src );

    CUtlMemory<unsigned char> m_Memory;
    int m_Get;
    int m_Put;

    unsigned char m_Error;
    unsigned char m_Flags;
    unsigned char m_Reserved;
#if defined( _X360 )
    unsigned char pad;
#endif

    int m_nTab;
    int m_nMaxPut;
    int m_nOffset;

    UtlBufferOverflowFunc_t m_GetOverflowFunc;
    UtlBufferOverflowFunc_t m_PutOverflowFunc;

    CByteswap	m_Byteswap;
};

// Stream style output operators for CUtlBuffer
inline CUtlBuffer &operator<<( CUtlBuffer &b , char v )
{
    b.PutChar( v );
    return b;
}

inline CUtlBuffer &operator<<( CUtlBuffer &b , unsigned char v )
{
    b.PutUnsignedChar( v );
    return b;
}

inline CUtlBuffer &operator<<( CUtlBuffer &b , short v )
{
    b.PutShort( v );
    return b;
}

inline CUtlBuffer &operator<<( CUtlBuffer &b , unsigned short v )
{
    b.PutUnsignedShort( v );
    return b;
}

inline CUtlBuffer &operator<<( CUtlBuffer &b , int v )
{
    b.PutInt( v );
    return b;
}

inline CUtlBuffer &operator<<( CUtlBuffer &b , unsigned int v )
{
    b.PutUnsignedInt( v );
    return b;
}

inline CUtlBuffer &operator<<( CUtlBuffer &b , float v )
{
    b.PutFloat( v );
    return b;
}

inline CUtlBuffer &operator<<( CUtlBuffer &b , double v )
{
    b.PutDouble( v );
    return b;
}

inline CUtlBuffer &operator<<( CUtlBuffer &b , const char *pv )
{
    b.PutString( pv );
    return b;
}

inline CUtlBuffer &operator<<( CUtlBuffer &b , const Vector &v )
{
    b << v.x << " " << v.y << " " << v.z;
    return b;
}

inline CUtlBuffer &operator<<( CUtlBuffer &b , const Vector2D &v )
{
    b << v.x << " " << v.y;
    return b;
}

class CUtlInplaceBuffer : public CUtlBuffer
{
public:
    CUtlInplaceBuffer( int growSize = 0 , int initSize = 0 , int nFlags = 0 );

    //
    // Routines returning buffer-inplace-pointers
    //
public:
    //
    // Upon success, determines the line length, fills out the pointer to the
    // beginning of the line and the line length, advances the "Get" pointer
    // offset by the line length and returns "true".
    //
    // If end of file is reached or upon error returns "false".
    //
    // Note:	the returned length of the line is at least one character because the
    //			trailing newline characters are also included as part of the line.
    //
    // Note:	the pointer returned points into the local memory of this buffer, in
    //			case the buffer gets relocated or destroyed the pointer becomes invalid.
    //
    // e.g.:	-------------
    //
    //			char *pszLine;
    //			int nLineLen;
    //			while ( pUtlInplaceBuffer->InplaceGetLinePtr( &pszLine, &nLineLen ) )
    //			{
    //				...
    //			}
    //
    //			-------------
    //
    // @param	ppszInBufferPtr		on return points into this buffer at start of line
    // @param	pnLineLength		on return holds num bytes accessible via (*ppszInBufferPtr)
    //
    // @returns	true				if line was successfully read
    //			false				when EOF is reached or error occurs
    //
    bool InplaceGetLinePtr( /* out */ char **ppszInBufferPtr , /* out */ int *pnLineLength );

    //
    // Determines the line length, advances the "Get" pointer offset by the line length,
    // replaces the newline character with null-terminator and returns the initial pointer
    // to now null-terminated line.
    //
    // If end of file is reached or upon error returns NULL.
    //
    // Note:	the pointer returned points into the local memory of this buffer, in
    //			case the buffer gets relocated or destroyed the pointer becomes invalid.
    //
    // e.g.:	-------------
    //
    //			while ( char *pszLine = pUtlInplaceBuffer->InplaceGetLinePtr() )
    //			{
    //				...
    //			}
    //
    //			-------------
    //
    // @returns	ptr-to-zero-terminated-line		if line was successfully read and buffer modified
    //			NULL							when EOF is reached or error occurs
    //
    char * InplaceGetLinePtr( void );
};

//-----------------------------------------------------------------------------
// Where am I reading?
//-----------------------------------------------------------------------------
inline int CUtlBuffer::TellGet() const
{
    return m_Get;
}

//-----------------------------------------------------------------------------
// How many bytes remain to be read?
//-----------------------------------------------------------------------------
inline int CUtlBuffer::GetBytesRemaining() const
{
    return m_nMaxPut - TellGet();
}

//-----------------------------------------------------------------------------
// What am I reading?
//-----------------------------------------------------------------------------
inline const void* CUtlBuffer::PeekGet( int offset ) const
{
    return &m_Memory[ m_Get + offset - m_nOffset ];
}

//-----------------------------------------------------------------------------
// Unserialization
//-----------------------------------------------------------------------------

template <typename T>
inline void CUtlBuffer::GetObject( T *dest )
{
    if ( CheckGet( sizeof( T ) ) )
    {
        if ( !m_Byteswap.IsSwappingBytes() || ( sizeof( T ) == 1 ) )
        {
            *dest = *( T * ) PeekGet();
        }
        else
        {
            m_Byteswap.SwapFieldsToTargetEndian<T>( dest , ( T* ) PeekGet() );
        }
        m_Get += sizeof( T );
    }
    else
    {
        Q_memset( &dest , 0 , sizeof( T ) );
    }
}

template <typename T>
inline void CUtlBuffer::GetObjects( T *dest , int count )
{
    for ( int i = 0; i < count; ++i , ++dest )
    {
        GetObject<T>( dest );
    }
}

template <typename T>
inline void CUtlBuffer::GetTypeBin( T &dest )
{
    if ( CheckGet( sizeof( T ) ) )
    {
        if ( !m_Byteswap.IsSwappingBytes() || ( sizeof( T ) == 1 ) )
        {
            dest = *( T * ) PeekGet();
        }
        else
        {
            m_Byteswap.SwapBufferToTargetEndian<T>( &dest , ( T* ) PeekGet() );
        }
        m_Get += sizeof( T );
    }
    else
    {
        dest = 0;
    }
}

template <>
inline void CUtlBuffer::GetTypeBin< float >( float &dest )
{
    if ( CheckGet( sizeof( float ) ) )
    {
        unsigned int pData = ( unsigned int ) PeekGet();
        if ( IsX360() && ( pData & 0x03 ) )
        {
// handle unaligned read
            ( ( unsigned char* ) &dest )[ 0 ] = ( ( unsigned char* ) pData )[ 0 ];
            ( ( unsigned char* ) &dest )[ 1 ] = ( ( unsigned char* ) pData )[ 1 ];
            ( ( unsigned char* ) &dest )[ 2 ] = ( ( unsigned char* ) pData )[ 2 ];
            ( ( unsigned char* ) &dest )[ 3 ] = ( ( unsigned char* ) pData )[ 3 ];
        }
        else
        {
             // aligned read
            dest = *( float * ) pData;
        }
        if ( m_Byteswap.IsSwappingBytes() )
        {
            m_Byteswap.SwapBufferToTargetEndian< float >( &dest , &dest );
        }
        m_Get += sizeof( float );
    }
    else
    {
        dest = 0;
    }
}

template <typename T>
inline void CUtlBuffer::GetType( T &dest , const char *pszFmt )
{
    if ( !IsText() )
    {
        GetTypeBin( dest );
    }
    else
    {
        dest = 0;
        Scanf( pszFmt , &dest );
    }
}

inline char CUtlBuffer::GetChar()
{
    char c;
    GetType( c , "%c" );
    return c;
}

inline unsigned char CUtlBuffer::GetUnsignedChar()
{
    unsigned char c;
    GetType( c , "%u" );
    return c;
}

inline short CUtlBuffer::GetShort()
{
    short s;
    GetType( s , "%d" );
    return s;
}

inline unsigned short CUtlBuffer::GetUnsignedShort()
{
    unsigned short s;
    GetType( s , "%u" );
    return s;
}

inline int CUtlBuffer::GetInt()
{
    int i;
    GetType( i , "%d" );
    return i;
}

inline int CUtlBuffer::GetIntHex()
{
    int i;
    GetType( i , "%x" );
    return i;
}

inline unsigned int CUtlBuffer::GetUnsignedInt()
{
    unsigned int u;
    GetType( u , "%u" );
    return u;
}

inline float CUtlBuffer::GetFloat()
{
    float f;
    GetType( f , "%f" );
    return f;
}

inline double CUtlBuffer::GetDouble()
{
    double d;
    GetType( d , "%f" );
    return d;
}

//-----------------------------------------------------------------------------
// Where am I writing?
//-----------------------------------------------------------------------------
inline unsigned char CUtlBuffer::GetFlags() const
{
    return m_Flags;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
inline bool CUtlBuffer::IsExternallyAllocated() const
{
    return m_Memory.IsExternallyAllocated();
}

//-----------------------------------------------------------------------------
// Where am I writing?
//-----------------------------------------------------------------------------
inline int CUtlBuffer::TellPut() const
{
    return m_Put;
}

//-----------------------------------------------------------------------------
// What's the most I've ever written?
//-----------------------------------------------------------------------------
inline int CUtlBuffer::TellMaxPut() const
{
    return m_nMaxPut;
}

//-----------------------------------------------------------------------------
// What am I reading?
//-----------------------------------------------------------------------------
inline void* CUtlBuffer::PeekPut( int offset )
{
    return &m_Memory[ m_Put + offset - m_nOffset ];
}

//-----------------------------------------------------------------------------
// Various put methods
//-----------------------------------------------------------------------------

template <typename T>
inline void CUtlBuffer::PutObject( T *src )
{
    if ( CheckPut( sizeof( T ) ) )
    {
        if ( !m_Byteswap.IsSwappingBytes() || ( sizeof( T ) == 1 ) )
        {
            *( T * ) PeekPut() = *src;
        }
        else
        {
            m_Byteswap.SwapFieldsToTargetEndian<T>( ( T* ) PeekPut() , src );
        }
        m_Put += sizeof( T );
        AddNullTermination();
    }
}

template <typename T>
inline void CUtlBuffer::PutObjects( T *src , int count )
{
    for ( int i = 0; i < count; ++i , ++src )
    {
        PutObject<T>( src );
    }
}

template <typename T>
inline void CUtlBuffer::PutTypeBin( T src )
{
    if ( CheckPut( sizeof( T ) ) )
    {
        if ( !m_Byteswap.IsSwappingBytes() || ( sizeof( T ) == 1 ) )
        {
            *( T * ) PeekPut() = src;
        }
        else
        {
            m_Byteswap.SwapBufferToTargetEndian<T>( ( T* ) PeekPut() , &src );
        }
        m_Put += sizeof( T );
        AddNullTermination();
    }
}

template <typename T>
inline void CUtlBuffer::PutType( T src , const char *pszFmt )
{
    if ( !IsText() )
    {
        PutTypeBin( src );
    }
    else
    {
        Printf( pszFmt , src );
    }
}

//-----------------------------------------------------------------------------
// Methods to help with pretty-printing
//-----------------------------------------------------------------------------
inline bool CUtlBuffer::WasLastCharacterCR()
{
    if ( !IsText() || ( TellPut() == 0 ) )
        return false;
    return ( *( const char * ) PeekPut( -1 ) == '\n' );
}

inline void CUtlBuffer::PutTabs()
{
    int nTabCount = ( m_Flags & AUTO_TABS_DISABLED ) ? 0 : m_nTab;
    for ( int i = nTabCount; --i >= 0; )
    {
        PutTypeBin<char>( '\t' );
    }
}

//-----------------------------------------------------------------------------
// Push/pop pretty-printing tabs
//-----------------------------------------------------------------------------
inline void CUtlBuffer::PushTab()
{
    ++m_nTab;
}

inline void CUtlBuffer::PopTab()
{
    if ( --m_nTab < 0 )
    {
        m_nTab = 0;
    }
}

//-----------------------------------------------------------------------------
// Temporarily disables pretty print
//-----------------------------------------------------------------------------
inline void CUtlBuffer::EnableTabs( bool bEnable )
{
    if ( bEnable )
    {
        m_Flags &= ~AUTO_TABS_DISABLED;
    }
    else
    {
        m_Flags |= AUTO_TABS_DISABLED;
    }
}

inline void CUtlBuffer::PutChar( char c )
{
    if ( WasLastCharacterCR() )
    {
        PutTabs();
    }

    PutTypeBin( c );
}

inline void CUtlBuffer::PutUnsignedChar( unsigned char c )
{
    PutType( c , "%u" );
}

inline void  CUtlBuffer::PutShort( short s )
{
    PutType( s , "%d" );
}

inline void CUtlBuffer::PutUnsignedShort( unsigned short s )
{
    PutType( s , "%u" );
}

inline void CUtlBuffer::PutInt( int i )
{
    PutType( i , "%d" );
}

inline void CUtlBuffer::PutUnsignedInt( unsigned int u )
{
    PutType( u , "%u" );
}

inline void CUtlBuffer::PutFloat( float f )
{
    PutType( f , "%f" );
}

inline void CUtlBuffer::PutDouble( double d )
{
    PutType( d , "%f" );
}

//-----------------------------------------------------------------------------
// Am I a text buffer?
//-----------------------------------------------------------------------------
inline bool CUtlBuffer::IsText() const
{
    return ( m_Flags & TEXT_BUFFER ) != 0;
}

//-----------------------------------------------------------------------------
// Can I grow if I'm externally allocated?
//-----------------------------------------------------------------------------
inline bool CUtlBuffer::IsGrowable() const
{
    return ( m_Flags & EXTERNAL_GROWABLE ) != 0;
}

//-----------------------------------------------------------------------------
// Am I valid? (overflow or underflow error), Once invalid it stays invalid
//-----------------------------------------------------------------------------
inline bool CUtlBuffer::IsValid() const
{
    return m_Error == 0;
}

//-----------------------------------------------------------------------------
// Do I contain carriage return/linefeeds?
//-----------------------------------------------------------------------------
inline bool CUtlBuffer::ContainsCRLF() const
{
    return IsText() && ( ( m_Flags & CONTAINS_CRLF ) != 0 );
}

//-----------------------------------------------------------------------------
// Am I read-only
//-----------------------------------------------------------------------------
inline bool CUtlBuffer::IsReadOnly() const
{
    return ( m_Flags & READ_ONLY ) != 0;
}

//-----------------------------------------------------------------------------
// Buffer base and size
//-----------------------------------------------------------------------------
inline const void* CUtlBuffer::Base() const
{
    return m_Memory.Base();
}

inline void* CUtlBuffer::Base()
{
    return m_Memory.Base();
}

inline int CUtlBuffer::Size() const
{
    return m_Memory.NumAllocated();
}

//-----------------------------------------------------------------------------
// Clears out the buffer; frees memory
//-----------------------------------------------------------------------------
inline void CUtlBuffer::Clear()
{
    m_Get = 0;
    m_Put = 0;
    m_Error = 0;
    m_nOffset = 0;
    m_nMaxPut = -1;
    AddNullTermination();
}

inline void CUtlBuffer::Purge()
{
    m_Get = 0;
    m_Put = 0;
    m_nOffset = 0;
    m_nMaxPut = 0;
    m_Error = 0;
    m_Memory.Purge();
}
#pragma warning(default:4127) //conditional operation is constant

//-----------------------------------------------------------------------------
// Forward declarations.
//-----------------------------------------------------------------------------

class Vector;
class QAngle;

//-----------------------------------------------------------------------------
// You can define a handler function that will be called in case of
// out-of-range values and overruns here.
//
// NOTE: the handler is only called in debug mode.
//
// Call SetBitBufErrorHandler to install a handler.
//-----------------------------------------------------------------------------

typedef enum
{
    BITBUFERROR_VALUE_OUT_OF_RANGE = 0 ,		// Tried to write a value with too few bits.
    BITBUFERROR_BUFFER_OVERRUN ,				// Was about to overrun a buffer.

    BITBUFERROR_NUM_ERRORS
} BitBufErrorType;

typedef void( *BitBufErrorHandler )( BitBufErrorType errorType , const char *pDebugName );

#define CallErrorHandler( errorType, pDebugName )

// Use this to install the error handler. Call with NULL to uninstall your error handler.
void SetBitBufErrorHandler( BitBufErrorHandler fn );

//-----------------------------------------------------------------------------
// Helpers.
//-----------------------------------------------------------------------------

inline int BitByte( int bits )
{
    // return PAD_NUMBER( bits, 8 ) >> 3;
    return ( bits + 7 ) >> 3;
}

//-----------------------------------------------------------------------------
enum EBitCoordType
{
    kCW_None ,
    kCW_LowPrecision ,
    kCW_Integral
};

//-----------------------------------------------------------------------------
// Used for serialization
//-----------------------------------------------------------------------------

class bf_write
{
public:
    bf_write();

    // nMaxBits can be used as the number of bits in the buffer.
    // It must be <= nBytes*8. If you leave it at -1, then it's set to nBytes * 8.
    bf_write( void *pData , int nBytes , int nMaxBits = -1 );
    bf_write( const char *pDebugName , void *pData , int nBytes , int nMaxBits = -1 );

    // Start writing to the specified buffer.
    // nMaxBits can be used as the number of bits in the buffer.
    // It must be <= nBytes*8. If you leave it at -1, then it's set to nBytes * 8.
    void			StartWriting( void *pData , int nBytes , int iStartBit = 0 , int nMaxBits = -1 );

    // Restart buffer writing.
    void			Reset();

    // Get the base pointer.
    unsigned char*	GetBasePointer()
    {
        return m_pData;
    }

    // Enable or disable assertion on overflow. 99% of the time, it's a bug that we need to catch,
    // but there may be the occasional buffer that is allowed to overflow gracefully.
    void			SetAssertOnOverflow( bool bAssert );

    // This can be set to assign a name that gets output if the buffer overflows.
    const char*		GetDebugName();
    void			SetDebugName( const char *pDebugName );

    // Seek to a specific position.
public:

    void			SeekToBit( int bitPos );

    // Bit functions.
public:

    void			WriteOneBit( int nValue );
    void			WriteOneBitNoCheck( int nValue );
    void			WriteOneBitAt( int iBit , int nValue );

    // Write signed or unsigned. Range is only checked in debug.
    void			WriteUBitLong( unsigned int data , int numbits , bool bCheckRange = true );
    void			WriteSBitLong( int data , int numbits );

    // Tell it whether or not the data is unsigned. If it's signed,
    // cast to unsigned before passing in (it will cast back inside).
    void			WriteBitLong( unsigned int data , int numbits , bool bSigned );

    // Write a list of bits in.
    bool			WriteBits( const void *pIn , int nBits );

    // writes an unsigned integer with variable bit length
    void			WriteUBitVar( unsigned int data );

    void			WriteVarInt32( uint32 data );
    int				ByteSizeVarInt32( uint32 data );

    // Copy the bits straight out of pIn. This seeks pIn forward by nBits.
    // Returns an error if this buffer or the read buffer overflows.
    bool			WriteBitsFromBuffer( class bf_read *pIn , int nBits );

    void			WriteBitAngle( float fAngle , int numbits );
    void			WriteBitCoord( const float f );
    void			WriteBitCoordMP( const float f , EBitCoordType coordType );
    void 			WriteBitCellCoord( const float f , int bits , EBitCoordType coordType );
    void			WriteBitFloat( float val );
    void			WriteBitVec3Coord( const Vector& fa );
    void			WriteBitNormal( float f );
    void			WriteBitVec3Normal( const Vector& fa );
    void			WriteBitAngles( const QAngle& fa );

    // Byte functions.
public:

    void			WriteChar( int val );
    void			WriteByte( unsigned int val );
    void			WriteShort( int val );
    void			WriteWord( unsigned int val );
    void			WriteLong( long val );
    void			WriteLongLong( int64 val );
    void			WriteFloat( float val );
    bool			WriteBytes( const void *pBuf , int nBytes );

    // Returns false if it overflows the buffer.
    bool			WriteString( const char *pStr );
    bool			WriteString( const wchar_t *pStr );

    // Status.
public:

    // How many bytes are filled in?
    int				GetNumBytesWritten();
    int				GetNumBitsWritten();
    int				GetMaxNumBits();
    int				GetNumBitsLeft();
    int				GetNumBytesLeft();
    unsigned char*	GetData();

    // Has the buffer overflowed?
    bool			CheckForOverflow( int nBits );
    inline bool		IsOverflowed() const
    {
        return m_bOverflow;
    }

    inline void		SetOverflowFlag();

public:
    // The current buffer.
    unsigned char*	m_pData;
    int				m_nDataBytes;
    int				m_nDataBits;

    // Where we are in the buffer.
    int				m_iCurBit;

private:

    // Errors?
    bool			m_bOverflow;

    bool			m_bAssertOnOverflow;
    const char		*m_pDebugName;
};

//-----------------------------------------------------------------------------
// Inlined methods
//-----------------------------------------------------------------------------

// How many bytes are filled in?
inline int bf_write::GetNumBytesWritten()
{
    return BitByte( m_iCurBit );
}

inline int bf_write::GetNumBitsWritten()
{
    return m_iCurBit;
}

inline int bf_write::GetMaxNumBits()
{
    return m_nDataBits;
}

inline int bf_write::GetNumBitsLeft()
{
    return m_nDataBits - m_iCurBit;
}

inline int bf_write::GetNumBytesLeft()
{
    return GetNumBitsLeft() >> 3;
}

inline unsigned char* bf_write::GetData()
{
    return m_pData;
}

inline bool bf_write::CheckForOverflow( int nBits )
{
    if ( m_iCurBit + nBits > m_nDataBits )
    {
        SetOverflowFlag();
        CallErrorHandler( BITBUFERROR_BUFFER_OVERRUN , GetDebugName() );
    }

    return m_bOverflow;
}

inline void bf_write::SetOverflowFlag()
{
    m_bOverflow = true;
}

inline void bf_write::WriteOneBitNoCheck( int nValue )
{
    if ( nValue )
        m_pData[ m_iCurBit >> 3 ] |= ( 1 << ( m_iCurBit & 7 ) );
    else
        m_pData[ m_iCurBit >> 3 ] &= ~( 1 << ( m_iCurBit & 7 ) );

    ++m_iCurBit;
}

inline void bf_write::WriteOneBit( int nValue )
{
    if ( !CheckForOverflow( 1 ) )
        WriteOneBitNoCheck( nValue );
}

inline void	bf_write::WriteOneBitAt( int iBit , int nValue )
{
    if ( iBit + 1 > m_nDataBits )
    {
        SetOverflowFlag();
        CallErrorHandler( BITBUFERROR_BUFFER_OVERRUN , GetDebugName() );
        return;
    }

    if ( nValue )
        m_pData[ iBit >> 3 ] |= ( 1 << ( iBit & 7 ) );
    else
        m_pData[ iBit >> 3 ] &= ~( 1 << ( iBit & 7 ) );
}

inline void bf_write::WriteUBitLong( unsigned int curData , int numbits , bool bCheckRange )
{
    extern unsigned long g_BitWriteMasks[ 32 ][ 33 ];

    // Bounds checking..
    if ( ( m_iCurBit + numbits ) > m_nDataBits )
    {
        m_iCurBit = m_nDataBits;
        SetOverflowFlag();
        CallErrorHandler( BITBUFERROR_BUFFER_OVERRUN , GetDebugName() );
        return;
    }

    int nBitsLeft = numbits;
    int iCurBit = m_iCurBit;

    // Mask in a dword.
    unsigned int iDWord = iCurBit >> 5;

    unsigned long iCurBitMasked = iCurBit & 31;

    uint32 dword = LoadLittleDWord( ( unsigned long* ) m_pData , iDWord );

    dword &= g_BitWriteMasks[ iCurBitMasked ][ nBitsLeft ];
    dword |= curData << iCurBitMasked;

    // write to stream (lsb to msb ) properly
    StoreLittleDWord( ( unsigned long* ) m_pData , iDWord , dword );

    // Did it span a dword?
    int nBitsWritten = 32 - iCurBitMasked;
    if ( nBitsWritten < nBitsLeft )
    {
        nBitsLeft -= nBitsWritten;
        curData >>= nBitsWritten;

        // read from stream (lsb to msb) properly
        dword = LoadLittleDWord( ( unsigned long* ) m_pData , iDWord + 1 );

        dword &= g_BitWriteMasks[ 0 ][ nBitsLeft ];
        dword |= curData;

        // write to stream (lsb to msb) properly
        StoreLittleDWord( ( unsigned long* ) m_pData , iDWord + 1 , dword );
    }

    m_iCurBit += numbits;
}

//-----------------------------------------------------------------------------
// This is useful if you just want a buffer to write into on the stack.
//-----------------------------------------------------------------------------

template<int SIZE>
class old_bf_write_static : public bf_write
{
public:
    inline old_bf_write_static() : bf_write( m_StaticData , SIZE )
    {}

    char	m_StaticData[ SIZE ];
};

//-----------------------------------------------------------------------------
// Used for unserialization
//-----------------------------------------------------------------------------

class old_bf_read
{
public:
    old_bf_read();

    // nMaxBits can be used as the number of bits in the buffer.
    // It must be <= nBytes*8. If you leave it at -1, then it's set to nBytes * 8.
    old_bf_read( const void *pData , int nBytes , int nBits = -1 );
    old_bf_read( const char *pDebugName , const void *pData , int nBytes , int nBits = -1 );

    // Start reading from the specified buffer.
    // pData's start address must be dword-aligned.
    // nMaxBits can be used as the number of bits in the buffer.
    // It must be <= nBytes*8. If you leave it at -1, then it's set to nBytes * 8.
    void			StartReading( const void *pData , int nBytes , int iStartBit = 0 , int nBits = -1 );

    // Restart buffer reading.
    void			Reset();

    // Enable or disable assertion on overflow. 99% of the time, it's a bug that we need to catch,
    // but there may be the occasional buffer that is allowed to overflow gracefully.
    void			SetAssertOnOverflow( bool bAssert );

    // This can be set to assign a name that gets output if the buffer overflows.
    const char*		GetDebugName();
    void			SetDebugName( const char *pName );

    void			ExciseBits( int startbit , int bitstoremove );

    // Bit functions.
public:

    // Returns 0 or 1.
    int				ReadOneBit();

protected:

    unsigned int	CheckReadUBitLong( int numbits );		// For debugging.
    int				ReadOneBitNoCheck();				// Faster version, doesn't check bounds and is inlined.
    bool			CheckForOverflow( int nBits );

public:

    // Get the base pointer.
    const unsigned char*	GetBasePointer()
    {
        return m_pData;
    }

    FORCEINLINE int TotalBytesAvailable( void ) const
    {
        return m_nDataBytes;
    }

    // Read a list of bits in..
    void            ReadBits( void *pOut , int nBits );

    float			ReadBitAngle( int numbits );

    unsigned int	ReadUBitLong( int numbits );
    unsigned int	PeekUBitLong( int numbits );
    int				ReadSBitLong( int numbits );

    // reads an unsigned integer with variable bit length
    unsigned int	ReadUBitVar();

    // You can read signed or unsigned data with this, just cast to
    // a signed int if necessary.
    unsigned int	ReadBitLong( int numbits , bool bSigned );

    float			ReadBitCoord();
    float			ReadBitCoordMP( EBitCoordType coordType );
    float 			ReadBitCellCoord( int bits , EBitCoordType coordType );
    float			ReadBitFloat();
    float			ReadBitNormal();
    void			ReadBitVec3Coord( Vector& fa );
    void			ReadBitVec3Normal( Vector& fa );
    void			ReadBitAngles( QAngle& fa );

    // Byte functions (these still read data in bit-by-bit).
public:

    int				ReadChar();
    int				ReadByte();
    int				ReadShort();
    int				ReadWord();
    long			ReadLong();
    int64			ReadLongLong();
    float			ReadFloat();
    bool			ReadBytes( void *pOut , int nBytes );

    // Returns false if bufLen isn't large enough to hold the
    // string in the buffer.
    //
    // Always reads to the end of the string (so you can read the
    // next piece of data waiting).
    //
    // If bLine is true, it stops when it reaches a '\n' or a null-terminator.
    //
    // pStr is always null-terminated (unless bufLen is 0).
    //
    // pOutNumChars is set to the number of characters left in pStr when the routine is
    // complete (this will never exceed bufLen-1).
    //
    bool			ReadString( char *pStr , int bufLen , bool bLine = false , int *pOutNumChars = NULL );
    bool			ReadWString( wchar_t *pStr , int bufLen , bool bLine = false , int *pOutNumChars = NULL );

    // Reads a string and allocates memory for it. If the string in the buffer
    // is > 2048 bytes, then pOverflow is set to true (if it's not NULL).
    char*			ReadAndAllocateString( bool *pOverflow = 0 );

    // Status.
public:
    int				GetNumBytesLeft();
    int				GetNumBytesRead();
    int				GetNumBitsLeft();
    int				GetNumBitsRead() const;

    // Has the buffer overflowed?
    inline bool		IsOverflowed() const
    {
        return m_bOverflow;
    }

    inline bool		Seek( int iBit );					// Seek to a specific bit.
    inline bool		SeekRelative( int iBitDelta );	// Seek to an offset from the current position.

                                                    // Called when the buffer is overflowed.
    inline void		SetOverflowFlag();

public:

    // The current buffer.
    const unsigned char*	m_pData;
    int						m_nDataBytes;
    int						m_nDataBits;

    // Where we are in the buffer.
    int				m_iCurBit;

private:
    // used by varbit reads internally
    inline int CountRunOfZeros();

    // Errors?
    bool			m_bOverflow;

    // For debugging..
    bool			m_bAssertOnOverflow;

    const char		*m_pDebugName;
};

//-----------------------------------------------------------------------------
// Inlines.
//-----------------------------------------------------------------------------

inline int old_bf_read::GetNumBytesRead()
{
    return BitByte( m_iCurBit );
}

inline int old_bf_read::GetNumBitsLeft()
{
    return m_nDataBits - m_iCurBit;
}

inline int old_bf_read::GetNumBytesLeft()
{
    return GetNumBitsLeft() >> 3;
}

inline int old_bf_read::GetNumBitsRead() const
{
    return m_iCurBit;
}

inline void old_bf_read::SetOverflowFlag()
{
    m_bOverflow = true;
}

inline bool old_bf_read::Seek( int iBit )
{
    if ( iBit < 0 || iBit > m_nDataBits )
    {
        SetOverflowFlag();
        m_iCurBit = m_nDataBits;
        return false;
    }
    else
    {
        m_iCurBit = iBit;
        return true;
    }
}

// Seek to an offset from the current position.
inline bool	old_bf_read::SeekRelative( int iBitDelta )
{
    return Seek( m_iCurBit + iBitDelta );
}

inline bool old_bf_read::CheckForOverflow( int nBits )
{
    if ( m_iCurBit + nBits > m_nDataBits )
    {
        SetOverflowFlag();
        CallErrorHandler( BITBUFERROR_BUFFER_OVERRUN , GetDebugName() );
    }

    return m_bOverflow;
}

inline int old_bf_read::ReadOneBitNoCheck()
{
    int value = m_pData[ m_iCurBit >> 3 ] & ( 1 << ( m_iCurBit & 7 ) );
    ++m_iCurBit;
    return !!value;
}

inline int old_bf_read::ReadOneBit()
{
    return ( !CheckForOverflow( 1 ) ) ? ReadOneBitNoCheck() : 0;
}

inline float old_bf_read::ReadBitFloat()
{
    long val;

    if ( CheckForOverflow( 32 ) )
        return 0.0f;

    int bit = m_iCurBit & 0x7;
    int byte = m_iCurBit >> 3;
    val = m_pData[ byte ] >> bit;
    val |= ( ( int ) m_pData[ byte + 1 ] ) << ( 8 - bit );
    val |= ( ( int ) m_pData[ byte + 2 ] ) << ( 16 - bit );
    val |= ( ( int ) m_pData[ byte + 3 ] ) << ( 24 - bit );
    if ( bit != 0 )
        val |= ( ( int ) m_pData[ byte + 4 ] ) << ( 32 - bit );
    m_iCurBit += 32;
    return *( ( float* ) &val );
}

inline unsigned int old_bf_read::ReadUBitLong( int numbits )
{
    extern unsigned long g_ExtraMasks[ 32 ];

    if ( ( m_iCurBit + numbits ) > m_nDataBits )
    {
        m_iCurBit = m_nDataBits;
        SetOverflowFlag();
        return 0;
    }

    // Read the current dword.
    int idword1 = m_iCurBit >> 5;
    unsigned int dword1 = LoadLittleDWord( ( unsigned long* ) m_pData , idword1 );

    dword1 >>= ( m_iCurBit & 31 ); // Get the bits we're interested in.

    m_iCurBit += numbits;
    unsigned int ret = dword1;

    // Does it span this dword?
    if ( ( m_iCurBit - 1 ) >> 5 == idword1 )
    {
        if ( numbits != 32 )
            ret &= g_ExtraMasks[ numbits ];
    }
    else
    {
        int nExtraBits = m_iCurBit & 31;
        unsigned int dword2 = LoadLittleDWord( ( unsigned long* ) m_pData , idword1 + 1 );

        dword2 &= g_ExtraMasks[ nExtraBits ];

        // No need to mask since we hit the end of the dword.
        // Shift the second dword's part into the high bits.
        ret |= ( dword2 << ( numbits - nExtraBits ) );
    }

    return ret;
}

class CBitBuffer
{
public:
    char const * m_pDebugName;
    bool m_bOverflow;
    int m_nDataBits;
    size_t m_nDataBytes;

    void SetDebugName( char const *pName )
    {
        m_pDebugName = pName;
    }

    CBitBuffer( void )
    {
        m_bOverflow = false;
        m_pDebugName = NULL;
        m_nDataBits = -1;
        m_nDataBytes = 0;
    }

    FORCEINLINE void SetOverflowFlag( void )
    {
        m_bOverflow = true;
    }

    FORCEINLINE bool IsOverflowed( void ) const
    {
        return m_bOverflow;
    }

    static const uint32 s_nMaskTable[ 33 ];							// 0 1 3 7 15 ..
};

class CBitWrite : public CBitBuffer
{
    uint32 m_nOutBufWord;
    int m_nOutBitsAvail;
    uint32 *m_pDataOut;
    uint32 *m_pBufferEnd;
    uint32 *m_pData;
    bool m_bFlushed;

public:
    void StartWriting( void *pData , int nBytes , int iStartBit = 0 , int nMaxBits = -1 );

    CBitWrite( void *pData , int nBytes , int nBits = -1 )
    {
        m_bFlushed = false;
        StartWriting( pData , nBytes , 0 , nBits );
    }

    CBitWrite( const char *pDebugName , void *pData , int nBytes , int nBits = -1 )
    {
        m_bFlushed = false;
        SetDebugName( pDebugName );
        StartWriting( pData , nBytes , 0 , nBits );
    }

    CBitWrite( void )
    {
        m_bFlushed = false;
    }

    ~CBitWrite( void )
    {
        TempFlush();
    }
    FORCEINLINE int GetNumBitsLeft( void ) const
    {
        return m_nOutBitsAvail + ( 32 * ( m_pBufferEnd - m_pDataOut - 1 ) );
    }

    FORCEINLINE void Reset( void )
    {
        m_bOverflow = false;
        m_nOutBitsAvail = 32;
        m_pDataOut = m_pData;
        m_nOutBufWord = 0;
    }

    FORCEINLINE void TempFlush( void )
    {
        // someone wants to know how much data we have written, or the pointer to it, so we'd better make
        // sure we write our data
        if ( m_nOutBitsAvail != 32 )
        {
            if ( m_pDataOut == m_pBufferEnd )
            {
                SetOverflowFlag();
            }
            else
            {
                StoreLittleDWord( ( unsigned long * ) m_pDataOut , 0 , ( LoadLittleDWord( ( unsigned long * ) m_pDataOut , 0 ) & ~s_nMaskTable[ 32 - m_nOutBitsAvail ] ) | m_nOutBufWord );
            }
        }
        m_bFlushed = true;
    }

    FORCEINLINE unsigned char *GetBasePointer()
    {
        TempFlush();
        return reinterpret_cast< unsigned char * >( m_pData );
    }

    FORCEINLINE unsigned char *GetData()
    {
        return GetBasePointer();
    }

    FORCEINLINE void Finish();
    FORCEINLINE void Flush();
    FORCEINLINE void FlushNoCheck();
    FORCEINLINE void WriteOneBit( int nValue );
    FORCEINLINE void WriteOneBitNoCheck( int nValue );
    FORCEINLINE void WriteUBitLong( unsigned int data , int numbits , bool bCheckRange = true );
    FORCEINLINE void WriteSBitLong( int data , int numbits );
    FORCEINLINE void WriteUBitVar( unsigned int data );
    FORCEINLINE void WriteBitFloat( float flValue );
    FORCEINLINE void WriteFloat( float flValue );
    bool WriteBits( const void *pInData , int nBits );
    void WriteBytes( const void *pBuf , int nBytes );
    void SeekToBit( int nSeekPos );

    FORCEINLINE int GetNumBitsWritten( void ) const
    {
        return ( 32 - m_nOutBitsAvail ) + ( 32 * ( m_pDataOut - m_pData ) );
    }

    FORCEINLINE int GetNumBytesWritten( void ) const
    {
        return ( GetNumBitsWritten() + 7 ) >> 3;
    }

    FORCEINLINE void WriteLong( long val )
    {
        WriteSBitLong( val , 32 );
    }

    FORCEINLINE void WriteChar( int val )
    {
        WriteSBitLong( val , sizeof( char ) << 3 );
    }

    FORCEINLINE void WriteByte( int val )
    {
        WriteUBitLong( val , sizeof( unsigned char ) << 3 , false );
    }

    FORCEINLINE void WriteShort( int val )
    {
        WriteSBitLong( val , sizeof( short ) << 3 );
    }

    FORCEINLINE void WriteWord( int val )
    {
        WriteUBitLong( val , sizeof( unsigned short ) << 3 );
    }

    bool WriteString( const char *pStr );
    bool WriteString( const wchar_t *pStr );

    void WriteLongLong( int64 val );

    void WriteBitAngle( float fAngle , int numbits );
    void WriteBitCoord( const float f );
    void WriteBitCoordMP( const float f , EBitCoordType coordType );
    void WriteBitCellCoord( const float f , int bits , EBitCoordType coordType );
    void WriteBitVec3Coord( const Vector& fa );
    void WriteBitNormal( float f );
    void WriteBitVec3Normal( const Vector& fa );
    void WriteBitAngles( const QAngle& fa );

    // Copy the bits straight out of pIn. This seeks pIn forward by nBits.
    // Returns an error if this buffer or the read buffer overflows.
    bool WriteBitsFromBuffer( class bf_read *pIn , int nBits );
};

void CBitWrite::Finish( void )
{
    if ( m_nOutBitsAvail != 32 )
    {
        if ( m_pDataOut == m_pBufferEnd )
        {
            SetOverflowFlag();
        }
        StoreLittleDWord( ( unsigned long* ) m_pDataOut , 0 , m_nOutBufWord );
    }
}

void CBitWrite::FlushNoCheck( void )
{
    StoreLittleDWord( ( unsigned long* ) m_pDataOut++ , 0 , m_nOutBufWord );
    m_nOutBitsAvail = 32;
    m_nOutBufWord = 0;										// ugh - I need this because of 32 bit writes. a<<=32 is a nop
}
void CBitWrite::Flush( void )
{
    if ( m_pDataOut == m_pBufferEnd )
    {
        SetOverflowFlag();
    }
    else
    {
        StoreLittleDWord( ( unsigned long* ) m_pDataOut++ , 0 , m_nOutBufWord );
    }
    m_nOutBufWord = 0;										// ugh - I need this because of 32 bit writes. a<<=32 is a nop
    m_nOutBitsAvail = 32;
}
void CBitWrite::WriteOneBitNoCheck( int nValue )
{
    m_nOutBufWord |= ( nValue & 1 ) << ( 32 - m_nOutBitsAvail );
    if ( --m_nOutBitsAvail == 0 )
    {
        FlushNoCheck();
    }
}

void CBitWrite::WriteOneBit( int nValue )
{
    m_nOutBufWord |= ( nValue & 1 ) << ( 32 - m_nOutBitsAvail );
    if ( --m_nOutBitsAvail == 0 )
    {
        Flush();
    }
}

FORCEINLINE void CBitWrite::WriteUBitLong( unsigned int nData , int nNumBits , bool bCheckRange )
{
    if ( nNumBits <= m_nOutBitsAvail )
    {
        if ( bCheckRange )
            m_nOutBufWord |= ( nData ) << ( 32 - m_nOutBitsAvail );
        else
            m_nOutBufWord |= ( nData & s_nMaskTable[ nNumBits ] ) << ( 32 - m_nOutBitsAvail );
        m_nOutBitsAvail -= nNumBits;
        if ( m_nOutBitsAvail == 0 )
        {
            Flush();
        }
    }
    else
    {
        // split dwords case
        int nOverflowBits = ( nNumBits - m_nOutBitsAvail );
        m_nOutBufWord |= ( nData & s_nMaskTable[ m_nOutBitsAvail ] ) << ( 32 - m_nOutBitsAvail );
        Flush();
        m_nOutBufWord = ( nData >> ( nNumBits - nOverflowBits ) );
        m_nOutBitsAvail = 32 - nOverflowBits;
    }
}

FORCEINLINE void CBitWrite::WriteSBitLong( int nData , int nNumBits )
{
    WriteUBitLong( ( uint32 ) nData , nNumBits , false );
}

FORCEINLINE void CBitWrite::WriteUBitVar( unsigned int n )
{
    if ( n < 16 )
        WriteUBitLong( n , 6 );
    else
        if ( n < 256 )
            WriteUBitLong( ( n & 15 ) | 16 | ( ( n & ( 128 | 64 | 32 | 16 ) ) << 2 ) , 10 );
        else
            if ( n < 4096 )
                WriteUBitLong( ( n & 15 ) | 32 | ( ( n & ( 2048 | 1024 | 512 | 256 | 128 | 64 | 32 | 16 ) ) << 2 ) , 14 );
            else
            {
                WriteUBitLong( ( n & 15 ) | 48 , 6 );
                WriteUBitLong( ( n >> 4 ) , 32 - 4 );
            }
}

FORCEINLINE void CBitWrite::WriteBitFloat( float flValue )
{
    WriteUBitLong( *( ( uint32 * ) &flValue ) , 32 );
}

#define LittleFloat( pOut, pIn )	( *pOut = *pIn )

FORCEINLINE void CBitWrite::WriteFloat( float flValue )
{
    // Pre-swap the float, since WriteBits writes raw data
    LittleFloat( &flValue , &flValue );
    WriteUBitLong( *( ( uint32 * ) &flValue ) , 32 );
}

class CBitRead : public CBitBuffer
{
public:
    uint32 m_nInBufWord;
    int m_nBitsAvail;
    uint32_t const *m_pDataIn;
    uint32_t const *m_pBufferEnd;
    uint32_t const *m_pData;

public:
    CBitRead( const void *pData , int nBytes , int nBits = -1 )
    {
        StartReading( pData , nBytes , 0 , nBits );
    }

    CBitRead( const char *pDebugName , const void *pData , int nBytes , int nBits = -1 )
    {
        SetDebugName( pDebugName );
        StartReading( pData , nBytes , 0 , nBits );
    }

    CBitRead( void ) : CBitBuffer()
    {}

    FORCEINLINE int Tell( void ) const
    {
        return GetNumBitsRead();
    }

    FORCEINLINE size_t TotalBytesAvailable( void ) const
    {
        return m_nDataBytes;
    }

    FORCEINLINE int GetNumBitsLeft() const
    {
        return m_nDataBits - Tell();
    }

    FORCEINLINE int GetNumBytesLeft() const
    {
        return GetNumBitsLeft() >> 3;
    }

    bool Seek( int nPosition );

    FORCEINLINE bool SeekRelative( int nOffset )
    {
        return Seek( GetNumBitsRead() + nOffset );
    }

    FORCEINLINE unsigned char const * GetBasePointer()
    {
        return reinterpret_cast< unsigned char const * >( m_pData );
    }

    void StartReading( const void *pData , int nBytes , int iStartBit = 0 , int nBits = -1 );

    FORCEINLINE int GetNumBitsRead( void ) const;

    FORCEINLINE void GrabNextDWord( bool bOverFlowImmediately = false );
    FORCEINLINE void FetchNext( void );
    FORCEINLINE unsigned int ReadUBitLong( int numbits );
    FORCEINLINE int ReadSBitLong( int numbits );
    FORCEINLINE unsigned int ReadUBitVar( void );
    FORCEINLINE unsigned int PeekUBitLong( int numbits );
    FORCEINLINE float ReadBitFloat( void );
    float ReadBitCoord();
    float ReadBitCoordMP( EBitCoordType coordType );
    float ReadBitCellCoord( int bits , EBitCoordType coordType );
    float ReadBitNormal();
    void ReadBitVec3Coord( Vector& fa );
    void ReadBitVec3Normal( Vector& fa );
    void ReadBitAngles( QAngle& fa );
    bool ReadBytes( void *pOut , int nBytes );
    float ReadBitAngle( int numbits );

    // Returns 0 or 1.
    FORCEINLINE int	ReadOneBit( void );
    FORCEINLINE int ReadLong( void );
    FORCEINLINE int ReadChar( void );
    FORCEINLINE int ReadByte( void );
    FORCEINLINE int ReadShort( void );
    FORCEINLINE int ReadWord( void );
    FORCEINLINE float ReadFloat( void );
    void ReadBits( void *pOut , int nBits );

    // Returns false if bufLen isn't large enough to hold the
    // string in the buffer.
    //
    // Always reads to the end of the string (so you can read the
    // next piece of data waiting).
    //
    // If bLine is true, it stops when it reaches a '\n' or a null-terminator.
    //
    // pStr is always null-terminated (unless bufLen is 0).
    //
    // pOutN<umChars is set to the number of characters left in pStr when the routine is
    // complete (this will never exceed bufLen-1).
    //
    bool ReadString( char *pStr , int bufLen , bool bLine = false , int *pOutNumChars = NULL );
    bool ReadWString( wchar_t *pStr , int bufLen , bool bLine = false , int *pOutNumChars = NULL );
    char* ReadAndAllocateString( bool *pOverflow = 0 );

    int64 ReadLongLong( void );
};

FORCEINLINE int CBitRead::GetNumBitsRead( void ) const
{
    if ( !m_pData )									   // pesky null ptr bitbufs. these happen.
        return 0;
    int nCurOfs = ( 32 - m_nBitsAvail ) + ( 8 * sizeof( m_pData[ 0 ] ) * ( m_pDataIn - m_pData - 1 ) );
    int nAdjust = 8 * ( m_nDataBytes & 3 );
    return min( nCurOfs + nAdjust , m_nDataBits );
}

FORCEINLINE void CBitRead::GrabNextDWord( bool bOverFlowImmediately )
{
    if ( m_pDataIn == m_pBufferEnd )
    {
        m_nBitsAvail = 1;									// so that next read will run out of words
        m_nInBufWord = 0;
        m_pDataIn++;										// so seek count increments like old
        if ( bOverFlowImmediately )
            SetOverflowFlag();
    }
    else
        if ( m_pDataIn > m_pBufferEnd )
        {
            SetOverflowFlag();
            m_nInBufWord = 0;
        }
        else
        {
            m_nInBufWord = LittleDWord( *( m_pDataIn++ ) );
        }
}

FORCEINLINE void CBitRead::FetchNext( void )
{
    m_nBitsAvail = 32;
    GrabNextDWord( false );
}

int CBitRead::ReadOneBit( void )
{
    int nRet = m_nInBufWord & 1;
    if ( --m_nBitsAvail == 0 )
    {
        FetchNext();
    }
    else
        m_nInBufWord >>= 1;
    return nRet;
}

unsigned int CBitRead::ReadUBitLong( int numbits )
{
    if ( m_nBitsAvail >= numbits )
    {
        unsigned int nRet = m_nInBufWord & s_nMaskTable[ numbits ];
        m_nBitsAvail -= numbits;
        if ( m_nBitsAvail )
        {
            m_nInBufWord >>= numbits;
        }
        else
        {
            FetchNext();
        }
        return nRet;
    }
    else
    {
        // need to merge words
        unsigned int nRet = m_nInBufWord;
        numbits -= m_nBitsAvail;
        GrabNextDWord( true );
        if ( m_bOverflow )
            return 0;
        nRet |= ( ( m_nInBufWord & s_nMaskTable[ numbits ] ) << m_nBitsAvail );
        m_nBitsAvail = 32 - numbits;
        m_nInBufWord >>= numbits;
        return nRet;
    }
}

FORCEINLINE unsigned int CBitRead::PeekUBitLong( int numbits )
{
    int nSaveBA = m_nBitsAvail;
    int nSaveW = m_nInBufWord;
    uint32 const *pSaveP = m_pDataIn;
    unsigned int nRet = ReadUBitLong( numbits );
    m_nBitsAvail = nSaveBA;
    m_nInBufWord = nSaveW;
    m_pDataIn = pSaveP;
    return nRet;
}

FORCEINLINE int CBitRead::ReadSBitLong( int numbits )
{
    int nRet = ReadUBitLong( numbits );
    // sign extend
    return ( nRet << ( 32 - numbits ) ) >> ( 32 - numbits );
}

FORCEINLINE int CBitRead::ReadLong( void )
{
    return ( int ) ReadUBitLong( sizeof( long ) << 3 );
}

FORCEINLINE float CBitRead::ReadFloat( void )
{
    uint32 nUval = ReadUBitLong( sizeof( long ) << 3 );
    return *( ( float * ) &nUval );
}

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4715)								// disable warning on not all cases
// returning a value. throwing default:
// in measurably reduces perf in bit
// packing benchmark
#endif
FORCEINLINE unsigned int CBitRead::ReadUBitVar( void )
{
    unsigned int ret = ReadUBitLong( 6 );
    switch ( ret & ( 16 | 32 ) )
    {
        case 16:
            ret = ( ret & 15 ) | ( ReadUBitLong( 4 ) << 4 );
            break;

        case 32:
            ret = ( ret & 15 ) | ( ReadUBitLong( 8 ) << 4 );
            break;
        case 48:
            ret = ( ret & 15 ) | ( ReadUBitLong( 32 - 4 ) << 4 );
            break;
    }
    return ret;
}
#ifdef _WIN32
#pragma warning(pop)
#endif

FORCEINLINE float CBitRead::ReadBitFloat( void )
{
    uint32 nvalue = ReadUBitLong( 32 );
    return *( ( float * ) &nvalue );
}

int CBitRead::ReadChar( void )
{
    return ReadSBitLong( sizeof( char ) << 3 );
}

int CBitRead::ReadByte( void )
{
    return ReadUBitLong( sizeof( unsigned char ) << 3 );
}

int CBitRead::ReadShort( void )
{
    return ReadSBitLong( sizeof( short ) << 3 );
}

int CBitRead::ReadWord( void )
{
    return ReadUBitLong( sizeof( unsigned short ) << 3 );
}

#define WRAP_READ( bc ) 																									  \
class bf_read : public bc																									  \
{																															  \
public:																														  \
    FORCEINLINE bf_read( void ) : bc(  )																								  \
	{																														  \
	}																														  \
																															  \
	FORCEINLINE bf_read( const void *pData, int nBytes, int nBits = -1 ) : bc( pData, nBytes, nBits )									  \
	{																														  \
	}																														  \
																															  \
	FORCEINLINE bf_read( const char *pDebugName, const void *pData, int nBytes, int nBits = -1 ) : bc( pDebugName, pData, nBytes, nBits ) \
	{																														  \
	}																														  \
};

#if 0
#define DELEGATE0( t, m )	t m()					\
{												\
		Check(); \
	t nOld = old1.m();						\
	t nNew = new1.m();						\
	Assert( nOld == nNew );						\
	Check();									\
	return nOld;								\
}
#define DELEGATE1( t, m, t1 )	t m( t1 x)					\
{												\
		Check(); \
	t nOld = old1.m( x);						\
	t nNew = new1.m( x );						\
	Assert( nOld == nNew );						\
	Check();									\
	return nOld;								\
}
#define DELEGATE0I( m )	DELEGATE0( int, m )
#define DELEGATE0LL( m ) DELEGATE0( int64, m )
class bf_read
{
    old_bf_read old1;
    CBitRead new1;
    void Check( void ) const
    {
        int n = new1.GetNumBitsRead();
        int o = old1.GetNumBitsRead();
        Assert( n == o );
        Assert( old1.IsOverflowed() == new1.IsOverflowed() );
    }
public:
    FORCEINLINE bf_read( void ) : old1() , new1()
    {}
    FORCEINLINE bf_read( const void *pData , int nBytes , int nBits = -1 ) : old1( pData , nBytes , nBits ) , new1( pData , nBytes , nBits )
    {}
    FORCEINLINE bf_read( const char *pDebugName , const void *pData , int nBytes , int nBits = -1 ) : old1( pDebugName , pData , nBytes , nBits ) , new1( pDebugName , pData , nBytes , nBits )
    {}
    FORCEINLINE bool IsOverflowed( void ) const
    {
        bool bOld = old1.IsOverflowed();
        bool bNew = new1.IsOverflowed();
        Assert( bOld == bNew );
        Check();
        return bOld;
    }
    void ReadBits( void *pOut , int nBits )
    {
        old1.ReadBits( pOut , nBits );
        void *mem = stackalloc( 1 + ( nBits / 8 ) );
        new1.ReadBits( mem , nBits );
        Assert( memcmp( mem , pOut , nBits / 8 ) == 0 );
    }
    bool ReadBytes( void *pOut , int nBytes )
    {
        ReadBits( pOut , nBytes << 3 );
        return !IsOverflowed();
    }
    unsigned int ReadUBitLong( int numbits )
    {
        unsigned int nOld = old1.ReadUBitLong( numbits );
        unsigned int nNew = new1.ReadUBitLong( numbits );
        Assert( nOld == nNew );
        Check();
        return nOld;
    }
    unsigned const char*	GetBasePointer()
    {
        Assert( old1.GetBasePointer() == new1.GetBasePointer() );
        Check();
        return old1.GetBasePointer();
    }
    void SetDebugName( const char *pDebugName )
    {
        old1.SetDebugName( pDebugName );
        new1.SetDebugName( pDebugName );
        Check();
    }
    void StartReading( const void *pData , int nBytes , int iStartBit = 0 , int nBits = -1 )
    {
        old1.StartReading( pData , nBytes , iStartBit , nBits );
        new1.StartReading( pData , nBytes , iStartBit , nBits );
        Check();
    }
    void SetAssertOnOverflow( bool bAssert )
    {
        old1.SetAssertOnOverflow( bAssert );
        //		new1.SetAssertOnOverflow( bAssert );
        Check();
    }
    DELEGATE0I( ReadOneBit );
    DELEGATE0I( ReadByte );
    DELEGATE0I( ReadWord );
    DELEGATE0I( ReadLong );
    DELEGATE0I( GetNumBytesLeft );
    DELEGATE0I( ReadShort );
    DELEGATE1( int , PeekUBitLong , int );
    DELEGATE0I( ReadChar );
    DELEGATE0I( GetNumBitsRead );
    DELEGATE0LL( ReadLongLong );
    DELEGATE0( float , ReadFloat );
    DELEGATE0( unsigned int , ReadUBitVar );
    DELEGATE0( float , ReadBitCoord );
    DELEGATE2( float , ReadBitCoordMP , bool , bool );
    DELEGATE0( float , ReadBitFloat );
    DELEGATE0( float , ReadBitNormal );
    DELEGATE1( bool , Seek , int );
    DELEGATE1( float , ReadBitAngle , int );
    DELEGATE1( bool , SeekRelative , int );
    DELEGATE0I( GetNumBitsLeft );
    DELEGATE0I( TotalBytesAvailable );
    void SetOverflowFlag()
    {
        old1.SetOverflowFlag();
        new1.SetOverflowFlag();
        Check();
    }
    bool ReadString( char *pStr , int bufLen , bool bLine = false , int *pOutNumChars = NULL )
    {
        Check();
        int oldn , newn;
        bool bOld = old1.ReadString( pStr , bufLen , bLine , &oldn );
        bool bNew = new1.ReadString( pStr , bufLen , bLine , &newn );
        Assert( bOld == bNew );
        Assert( oldn == newn );
        if ( pOutNumChars )
            *pOutNumChars = oldn;
        Check();
        return bOld;
    }
    bool ReadWString( wchar_t *pStr , int bufLen , bool bLine = false , int *pOutNumChars = NULL )
    {
        Check();
        int oldn , newn;
        bool bOld = old1.ReadWString( pStr , bufLen , bLine , &oldn );
        bool bNew = new1.ReadWString( pStr , bufLen , bLine , &newn );
        Assert( bOld == bNew );
        Assert( oldn == newn );
        if ( pOutNumChars )
            *pOutNumChars = oldn;
        Check();
        return bOld;
    }
    void ReadBitVec3Coord( Vector& fa )
    {
        Check();
        old1.ReadBitVec3Coord( fa );
        Vector test;
        new1.ReadBitVec3Coord( test );
        Assert( VectorsAreEqual( fa , test ) );
        Check();
    }
    void ReadBitVec3Normal( Vector& fa )
    {
        Check();
        old1.ReadBitVec3Coord( fa );
        Vector test;
        new1.ReadBitVec3Coord( test );
        Assert( VectorsAreEqual( fa , test ) );
        Check();
    }

    char* ReadAndAllocateString( bool *pOverflow = NULL )
    {
        Check();
        bool bold , bnew;
        char *pold = old1.ReadAndAllocateString( &bold );
        char *pnew = new1.ReadAndAllocateString( &bnew );
        Assert( bold == bnew );
        Assert( strcmp( pold , pnew ) == 0 );
        delete[] pnew;
        Check();
        if ( pOverflow )
            *pOverflow = bold;
        return pold;
    }
    DELEGATE1( int , ReadSBitLong , int );
};
#endif

WRAP_READ( CBitRead );

#endif