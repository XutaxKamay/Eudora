#include "Includes.hxx"
#include "Main.hxx"

// #define BB_PROFILING

// Precalculated bit masks for WriteUBitLong. Using these tables instead of
// doing the calculations gives a 33% speedup in WriteUBitLong.
unsigned long g_BitWriteMasks[ 32 ][ 33 ];

// (1 << i) - 1
unsigned long g_ExtraMasks[ 32 ];

#define BITS_PER_INT		32
#define	COORD_INTEGER_BITS			14
#define COORD_FRACTIONAL_BITS		5
#define COORD_DENOMINATOR			(1<<(COORD_FRACTIONAL_BITS))
#define COORD_RESOLUTION			(1.0/(COORD_DENOMINATOR))

inline int GetBitForBitnum( int bitNum )
{
    static int bitsForBitnum[] =
    {
        ( 1 << 0 ),
        ( 1 << 1 ),
        ( 1 << 2 ),
        ( 1 << 3 ),
        ( 1 << 4 ),
        ( 1 << 5 ),
        ( 1 << 6 ),
        ( 1 << 7 ),
        ( 1 << 8 ),
        ( 1 << 9 ),
        ( 1 << 10 ),
        ( 1 << 11 ),
        ( 1 << 12 ),
        ( 1 << 13 ),
        ( 1 << 14 ),
        ( 1 << 15 ),
        ( 1 << 16 ),
        ( 1 << 17 ),
        ( 1 << 18 ),
        ( 1 << 19 ),
        ( 1 << 20 ),
        ( 1 << 21 ),
        ( 1 << 22 ),
        ( 1 << 23 ),
        ( 1 << 24 ),
        ( 1 << 25 ),
        ( 1 << 26 ),
        ( 1 << 27 ),
        ( 1 << 28 ),
        ( 1 << 29 ),
        ( 1 << 30 ),
        ( 1 << 31 ),
    };

    return bitsForBitnum[ ( bitNum ) & ( BITS_PER_INT - 1 ) ];
}

inline int BitForBitnum( int bitnum )
{
    return GetBitForBitnum( bitnum );
}

class CBitWriteMasksInit
{
public:
    CBitWriteMasksInit()
    {
        for ( unsigned int startbit = 0; startbit < 32; startbit++ )
        {
            for ( unsigned int nBitsLeft = 0; nBitsLeft < 33; nBitsLeft++ )
            {
                unsigned int endbit = startbit + nBitsLeft;
                g_BitWriteMasks[ startbit ][ nBitsLeft ] = BitForBitnum( startbit ) - 1;
                if ( endbit < 32 )
                    g_BitWriteMasks[ startbit ][ nBitsLeft ] |= ~( BitForBitnum( endbit ) - 1 );
            }
        }

        for ( unsigned int maskBit = 0; maskBit < 32; maskBit++ )
            g_ExtraMasks[ maskBit ] = BitForBitnum( maskBit ) - 1;
    }
};
CBitWriteMasksInit g_BitWriteMasksInit;

void bf_write::WriteShort( int val )
{
    WriteSBitLong( val , sizeof( short ) << 3 );
}

void bf_write::WriteFloat( float val )
{
    // Pre-swap the float, since WriteBits writes raw data
    LittleFloat( &val , &val );

    WriteBits( &val , sizeof( val ) << 3 );
}

// Sign bit comes first
void bf_write::WriteSBitLong( int data , int numbits )
{
    // Do we have a valid # of bits to encode with?
    Assert( numbits >= 1 );

    // Note: it does this wierdness here so it's bit-compatible with regular integer data in the buffer.
    // (Some old code writes direct integers right into the buffer).
    if ( data < 0 )
    {
        WriteUBitLong( ( unsigned int ) ( 0x80000000 + data ) , numbits - 1 , false );
        WriteOneBit( 1 );
    }
    else
    {
        WriteUBitLong( ( unsigned int ) data , numbits - 1 );
        WriteOneBit( 0 );
    }
}

bool bf_write::WriteBits( const void *pInData , int nBits )
{
    unsigned char *pOut = ( unsigned char* ) pInData;
    int nBitsLeft = nBits;

    // Bounds checking..
    if ( ( m_iCurBit + nBits ) > m_nDataBits )
    {
        SetOverflowFlag();
        CallErrorHandler( BITBUFERROR_BUFFER_OVERRUN , GetDebugName() );
        return false;
    }

    // Align output to dword boundary
    while ( ( ( unsigned long ) pOut & 3 ) != 0 && nBitsLeft >= 8 )
    {
        WriteUBitLong( *pOut , 8 , false );
        ++pOut;
        nBitsLeft -= 8;
    }

    if ( ( nBitsLeft >= 32 ) && ( m_iCurBit & 7 ) == 0 )
    {
        // current bit is byte aligned, do block copy
        int numbytes = nBitsLeft >> 3;
        int numbits = numbytes << 3;

        memcpy( m_pData + ( m_iCurBit >> 3 ) , pOut , numbytes );
        pOut += numbytes;
        nBitsLeft -= numbits;
        m_iCurBit += numbits;
    }

    // X360TBD: Can't write dwords in WriteBits because they'll get swapped
    if ( nBitsLeft >= 32 )
    {
        unsigned long iBitsRight = ( m_iCurBit & 31 );
        unsigned long iBitsLeft = 32 - iBitsRight;
        unsigned long bitMaskLeft = g_BitWriteMasks[ iBitsRight ][ 32 ];
        unsigned long bitMaskRight = g_BitWriteMasks[ 0 ][ iBitsRight ];

        unsigned long *pData = &( ( unsigned long* ) m_pData )[ m_iCurBit >> 5 ];

        // Read dwords.
        while ( nBitsLeft >= 32 )
        {
            unsigned long curData = *( unsigned long* ) pOut;
            pOut += sizeof( unsigned long );

            *pData &= bitMaskLeft;
            *pData |= curData << iBitsRight;

            pData++;

            if ( iBitsLeft < 32 )
            {
                curData >>= iBitsLeft;
                *pData &= bitMaskRight;
                *pData |= curData;
            }

            nBitsLeft -= 32;
            m_iCurBit += 32;
        }
    }

    // write remaining bytes
    while ( nBitsLeft >= 8 )
    {
        WriteUBitLong( *pOut , 8 , false );
        ++pOut;
        nBitsLeft -= 8;
    }

    // write remaining bits
    if ( nBitsLeft )
    {
        WriteUBitLong( *pOut , nBitsLeft , false );
    }

    return !IsOverflowed();
}

void bf_write::WriteBitVec3Coord( const Vector& fa )
{
    int		xflag , yflag , zflag;

    xflag = ( fa[ 0 ] >= COORD_RESOLUTION ) || ( fa[ 0 ] <= -COORD_RESOLUTION );
    yflag = ( fa[ 1 ] >= COORD_RESOLUTION ) || ( fa[ 1 ] <= -COORD_RESOLUTION );
    zflag = ( fa[ 2 ] >= COORD_RESOLUTION ) || ( fa[ 2 ] <= -COORD_RESOLUTION );

    WriteOneBit( xflag );
    WriteOneBit( yflag );
    WriteOneBit( zflag );

    if ( xflag )
        WriteBitCoord( fa[ 0 ] );
    if ( yflag )
        WriteBitCoord( fa[ 1 ] );
    if ( zflag )
        WriteBitCoord( fa[ 2 ] );
}

void bf_write::WriteBitCoord( const float f )
{
    int		signbit = ( f <= -COORD_RESOLUTION );
    int		intval = ( int ) fabs( f );
    int		fractval = abs( ( int ) ( f*COORD_DENOMINATOR ) ) & ( COORD_DENOMINATOR - 1 );

    // Send the bit flags that indicate whether we have an integer part and/or a fraction part.
    WriteOneBit( intval );
    WriteOneBit( fractval );

    if ( intval || fractval )
    {
        // Send the sign bit
        WriteOneBit( signbit );

        // Send the integer if we have one.
        if ( intval )
        {
            // Adjust the integers from [1..MAX_COORD_VALUE] to [0..MAX_COORD_VALUE-1]
            intval--;
            WriteUBitLong( ( unsigned int ) intval , COORD_INTEGER_BITS );
        }

        // Send the fraction if we have one
        if ( fractval )
        {
            WriteUBitLong( ( unsigned int ) fractval , COORD_FRACTIONAL_BITS );
        }
    }
}

void bf_write::WriteBitAngle( float fAngle , int numbits )
{
    int d;
    unsigned int mask;
    unsigned int shift;

    shift = BitForBitnum( numbits );
    mask = shift - 1;

    d = ( int ) ( ( fAngle / 360.0 ) * shift );
    d &= mask;

    WriteUBitLong( ( unsigned int ) d , numbits );
}

bool bf_write::WriteString( const char *pStr )
{
    if ( pStr )
    {
        do
        {
            WriteChar( *pStr );
            ++pStr;
        }
        while ( *( pStr - 1 ) != 0 );
    }
    else
    {
        WriteChar( 0 );
    }

    return !IsOverflowed();
}

void bf_write::WriteChar( int val )
{
    WriteSBitLong( val , sizeof( char ) << 3 );
}

void bf_write::WriteLong( long val )
{
    WriteSBitLong( val , sizeof( long ) << 3 );
}

void bf_write::Reset()
{
    m_iCurBit = 0;
    m_bOverflow = false;
}

bool bf_write::WriteBytes( const void *pBuf , int nBytes )
{
    return WriteBits( pBuf , nBytes << 3 );
}

bf_write::bf_write()
{
    m_pData = NULL;
    m_nDataBytes = 0;
    m_nDataBits = -1; // set to -1 so we generate overflow on any operation
    m_iCurBit = 0;
    m_bOverflow = false;
    m_bAssertOnOverflow = true;
    m_pDebugName = NULL;
}

bf_write::bf_write( void *pData , int nBytes , int nMaxBits )
{
    m_bAssertOnOverflow = true;
    m_pDebugName = NULL;
    StartWriting( pData , nBytes , 0 , nMaxBits );
}

bf_write::bf_write( const char *pDebugName , void *pData , int nBytes , int nMaxBits )
{
    m_bAssertOnOverflow = true;
    m_pDebugName = pDebugName;
    StartWriting( pData , nBytes , 0 , nMaxBits );
}

void bf_write::StartWriting( void *pData , int nBytes , int iStartBit , int nMaxBits )
{
    // Make sure it's dword aligned and padded.
    Assert( ( nBytes % 4 ) == 0 );
    Assert( ( ( unsigned long ) pData & 3 ) == 0 );

    // The writing code will overrun the end of the buffer if it isn't dword aligned, so truncate to force alignment
    nBytes &= ~3;

    m_pData = ( unsigned char* ) pData;
    m_nDataBytes = nBytes;

    if ( nMaxBits == -1 )
    {
        m_nDataBits = nBytes << 3;
    }
    else
    {
        Assert( nMaxBits <= nBytes * 8 );
        m_nDataBits = nMaxBits;
    }

    m_iCurBit = iStartBit;
    m_bOverflow = false;
}