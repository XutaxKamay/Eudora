#ifndef MATHEMATICS
#define MATHEMATICS
#pragma once

#include <amp_math.h>

#define DECL_ALIGN(x) __declspec(align(x))
#define ALIGN4 DECL_ALIGN(4)
#define ALIGN8 DECL_ALIGN(8)
#define ALIGN16 DECL_ALIGN(16)
#define ALIGN32 DECL_ALIGN(32)
#define ALIGN128 DECL_ALIGN(128)
#define ALIGN4_POST DECL_ALIGN(4)
#define ALIGN8_POST DECL_ALIGN(8)
#define ALIGN16_POST DECL_ALIGN(16)
#define ALIGN32_POST DECL_ALIGN(32)
#define ALIGN128_POST DECL_ALIGN(128)

#define LittleDWord( val )			( val )

FORCEINLINE unsigned long LoadLittleDWord( const unsigned long *base , unsigned int dwordIndex )
{
    return LittleDWord( base[ dwordIndex ] );
}

FORCEINLINE void StoreLittleDWord( unsigned long *base , unsigned int dwordIndex , unsigned long dword )
{
    base[ dwordIndex ] = LittleDWord( dword );
}

// https://youtu.be/nXaxk27zwlk?t=56m34s

FORCEINLINE int fast_mod( const int& input , const int& ceil )
{
	// apply the modulo operator only when needed
	// (i.e. when the input is greater than the ceiling)
	return input >= ceil ? input % ceil : input;
	// NB: the assumption here is that the numbers are positive
}

typedef int int32;
typedef __int64 int64;
typedef uint32_t uint32;

typedef float Real;

inline float FloatMakePositive( float f )
{
    return fabsf( f );
}

inline unsigned long& FloatBits( Real & f )
{
    return *reinterpret_cast< unsigned long* >( &f );
}

inline unsigned long const& FloatBits( Real const& f )
{
    return *reinterpret_cast< unsigned long const* >( &f );
}

inline unsigned long FloatAbsBits( Real f )
{
    return FloatBits( f ) & 0x7FFFFFFF;
}

typedef int SideType;

template<typename TypeReal = Real> constexpr TypeReal Pi = static_cast< TypeReal >( 3.14159265358979323846 );

// Used to represent sides of things like planes.
#define	SIDE_FRONT	0
#define	SIDE_BACK	1
#define	SIDE_ON		2

#define VP_EPSILON	0.01f

#define clamp(val, min, max) (((val) > (max)) ? (max) : (((val) < (min)) ? (min) : (val)))

template<typename TypeReal = Real> constexpr TypeReal ConvDEG = static_cast< TypeReal >( ( TypeReal )180.0 ) / Pi<TypeReal>;
template<typename TypeReal = Real> constexpr TypeReal ConvRAD = Pi<TypeReal> / static_cast< TypeReal >( ( TypeReal )180.0 );

template<typename TypeReal = Real> TypeReal DEGTORAD( TypeReal value )
{
    return static_cast< TypeReal >( ( value * ConvRAD< TypeReal > ) );
}

template<typename TypeReal = Real> TypeReal RADTODEG( TypeReal value )
{
    return static_cast< TypeReal >( ( value * ConvDEG< TypeReal > ) );
}

template<int Norm> Real AngNormalize( Real value )
{
    value = fmod( value + ( Real ) Norm , ( Real ) 360 );

    if ( value < 0 )
        value += ( Real ) 360;

    value -= ( Real ) Norm;

    return value;
}

template<typename TypeReal = Real> void SinCos( TypeReal angle , TypeReal *a , TypeReal *b )
{
    *a = ( TypeReal ) sin( ( TypeReal ) angle );
    *b = ( TypeReal ) cos( ( TypeReal ) angle );
}

inline double __declspec ( naked ) __fastcall fastsqrt( double )
{
    _asm
    {
        fld qword ptr[ esp + 4 ]
        fsqrt
        ret 8
    }
}

enum
{
    vX ,
    vY ,
    vZ
};

enum
{
    Pitch ,
    Yaw ,
    Roll ,
    aX = 0 ,
    aY = 1 ,
    aZ = 2
};

struct ALIGN16 intx4
{
    int32 m_i32[ 4 ];

    inline int & operator[]( int which )
    {
        return m_i32[ which ];
    }

    inline const int & operator[]( int which ) const
    {
        return m_i32[ which ];
    }

    inline int32 *Base()
    {
        return m_i32;
    }

    inline const int32 *Base() const
    {
        return m_i32;
    }

    inline const bool operator==( const intx4 &other ) const
    {
        return m_i32[ 0 ] == other.m_i32[ 0 ] &&
            m_i32[ 1 ] == other.m_i32[ 1 ] &&
            m_i32[ 2 ] == other.m_i32[ 2 ] &&
            m_i32[ 3 ] == other.m_i32[ 3 ];
    }
} ALIGN16_POST;

extern const ALIGN16 uint32 g_SIMD_ComponentMask[ 4 ][ 4 ];

typedef union
{
    float  m128_f32[ 4 ];
    uint32 m128_u32[ 4 ];
    __m128 m;
} fltx4;

typedef fltx4 i32x4;
typedef fltx4 u32x4;

class Matrix3x4
{
public:

    void Clear()
    {
        flMatVal[ 0 ][ 0 ] = 0;
        flMatVal[ 0 ][ 1 ] = 0;
        flMatVal[ 0 ][ 2 ] = 0;
        flMatVal[ 0 ][ 3 ] = 0;

        flMatVal[ 1 ][ 0 ] = 0;
        flMatVal[ 1 ][ 1 ] = 0;
        flMatVal[ 1 ][ 2 ] = 0;
        flMatVal[ 1 ][ 3 ] = 0;

        flMatVal[ 2 ][ 0 ] = 0;
        flMatVal[ 2 ][ 1 ] = 0;
        flMatVal[ 2 ][ 2 ] = 0;
        flMatVal[ 2 ][ 3 ] = 0;
    }

    Real flMatVal[ 3 ][ 4 ];

    Real *operator[]( int i )
    {
        return flMatVal[ i ];
    }
    const Real *operator[]( int i ) const
    {
        return flMatVal[ i ];
    }

    Matrix3x4 operator=( const Matrix3x4 &MatrixToCopy )
    {
        flMatVal[ 0 ][ 0 ] = MatrixToCopy.flMatVal[ 0 ][ 0 ];
        flMatVal[ 0 ][ 1 ] = MatrixToCopy.flMatVal[ 0 ][ 1 ];
        flMatVal[ 0 ][ 2 ] = MatrixToCopy.flMatVal[ 0 ][ 2 ];
        flMatVal[ 0 ][ 3 ] = MatrixToCopy.flMatVal[ 0 ][ 3 ];

        flMatVal[ 1 ][ 0 ] = MatrixToCopy.flMatVal[ 1 ][ 0 ];
        flMatVal[ 1 ][ 1 ] = MatrixToCopy.flMatVal[ 1 ][ 1 ];
        flMatVal[ 1 ][ 2 ] = MatrixToCopy.flMatVal[ 1 ][ 2 ];
        flMatVal[ 1 ][ 3 ] = MatrixToCopy.flMatVal[ 1 ][ 3 ];

        flMatVal[ 2 ][ 0 ] = MatrixToCopy.flMatVal[ 2 ][ 0 ];
        flMatVal[ 2 ][ 1 ] = MatrixToCopy.flMatVal[ 2 ][ 1 ];
        flMatVal[ 2 ][ 2 ] = MatrixToCopy.flMatVal[ 2 ][ 2 ];
        flMatVal[ 2 ][ 3 ] = MatrixToCopy.flMatVal[ 2 ][ 3 ];

        return *this;
    }
};

class VMatrix
{
public:
    Real flMatVal[ 4 ][ 4 ];

    Real *operator[]( int i )
    {
        return flMatVal[ i ];
    }
    const Real *operator[]( int i ) const
    {
        return flMatVal[ i ];
    }
};

class Vector2D
{
public:

    Vector2D( const Real& _x = 0 , const Real& _y = 0 )
    {
        x = _x;
        y = _y;
    }

    void Init( const Real& _x = 0 , const Real& _y = 0 )
    {
        x = _x;
        y = _y;
    }

    bool operator!=( const Vector2D& vVector2D )
    {
        if ( x != vVector2D.x || y != vVector2D.y )
            return true;

        return false;
    }

    bool operator==( const Vector2D& vVector2D )
    {
        if ( x == vVector2D.x && y == vVector2D.y )
            return true;

        return false;
    }

    void operator=( const Vector2D&  vVector2D )
    {
        x = vVector2D.x;
        y = vVector2D.y;
    }

    void operator-=( const Vector2D&  vVector2D )
    {
        x -= vVector2D.x;
        y -= vVector2D.y;
    }

    void operator+=( const Vector2D&  vVector2D )
    {
        x += vVector2D.x;
        y += vVector2D.y;
    }

    void operator/=( const Vector2D&  vVector2D )
    {
        x /= vVector2D.x;
        y /= vVector2D.y;
    }

    void operator*=( const Vector2D&  vVector2D )
    {
        x *= vVector2D.x;
        y *= vVector2D.y;
    }

    void operator-=( const Real& fFactor )
    {
        x -= fFactor;
        y -= fFactor;
    }

    void operator+=( const Real& fFactor )
    {
        x += fFactor;
        y += fFactor;
    }

    void operator/=( const Real& fFactor )
    {
        x /= fFactor;
        y /= fFactor;
    }

    void operator*=( const Real& fFactor )
    {
        x *= fFactor;
        y *= fFactor;
    }

    Vector2D operator+( const Vector2D& vVector2D )
    {
        Vector2D v;
        v.x = x + vVector2D.x;
        v.y = y + vVector2D.y;

        return v;
    }

    Vector2D operator-( const Vector2D& vVector2D )
    {
        Vector2D v;
        v.x = x - vVector2D.x;
        v.y = y - vVector2D.y;

        return v;
    }

    Vector2D operator/( const Vector2D& vVector2D )
    {
        Vector2D v;
        v.x = x / vVector2D.x;
        v.y = y / vVector2D.y;

        return v;
    }

    Vector2D operator*( const Vector2D& vVector2D )
    {
        Vector2D v;
        v.x = x * vVector2D.x;
        v.y = y * vVector2D.y;

        return v;
    }

    Vector2D operator+( const Real& fFactor )
    {
        Vector2D v;
        v.x = x + fFactor;
        v.y = y + fFactor;

        return v;
    }

    Vector2D operator-( const Real& fFactor )
    {
        Vector2D v;
        v.x = x - fFactor;
        v.y = y - fFactor;

        return v;
    }

    Vector2D operator/( const Real& fFactor )
    {
        Vector2D v;
        v.x = x / fFactor;
        v.y = y / fFactor;

        return v;
    }

    Vector2D operator*( const Real& fFactor )
    {
        Vector2D v;
        v.x = x * fFactor;
        v.y = y * fFactor;

        return v;
    }

    Real &operator[]( int iValue )
    {
        return ( ( Real* ) this )[ iValue ];
    }

    Real operator[]( int iValue ) const
    {
        return ( ( Real* ) this )[ iValue ];
    }

    Real *Base()
    {
        return ( ( Real* ) this );
    }

    Real *Base() const
    {
        return ( ( Real* ) this );
    }

    Real Normalize()
    {
        Real fLength = Length();
        *this /= fLength;
        return fLength;
    }

    void FastNormalize()
    {
        *this *= ( Real )1.0 / Length();
    }

    Real Length()
    {
        return ( Real ) fastsqrt( ( x*x ) + ( y*y ) );
    }

    Real x , y;
};

class Vector
{
public:

    Vector( const Real& _x = 0 , const Real& _y = 0 , const Real& _z = 0 )
    {
        x = _x;
        y = _y;
        z = _z;
    }

    void Init( const Real& _x = 0 , const Real& _y = 0 , const Real& _z = 0 )
    {
        x = _x;
        y = _y;
        z = _z;
    }

    bool operator!=( const Vector& vVector ) const
    {
        if ( x != vVector.x || y != vVector.y || z != vVector.z )
            return true;

        return false;
    }

    bool operator==( const Vector& vVector )
    {
        if ( x == vVector.x && y == vVector.y && z == vVector.z )
            return true;

        return false;
    }

    void operator=( const Vector&  vVector )
    {
        x = vVector.x;
        y = vVector.y;
        z = vVector.z;
    }

    void operator-=( const Vector&  vVector )
    {
        x -= vVector.x;
        y -= vVector.y;
        z -= vVector.z;
    }

    void operator+=( const Vector&  vVector )
    {
        x += vVector.x;
        y += vVector.y;
        z += vVector.z;
    }

    void operator/=( const Vector&  vVector )
    {
        x /= vVector.x;
        y /= vVector.y;
        z /= vVector.z;
    }

    void operator*=( const Vector&  vVector )
    {
        x *= vVector.x;
        y *= vVector.y;
        z *= vVector.z;
    }

    void operator-=( const Real& fFactor )
    {
        x -= fFactor;
        y -= fFactor;
        z -= fFactor;
    }

    void operator+=( const Real& fFactor )
    {
        x += fFactor;
        y += fFactor;
        z += fFactor;
    }

    void operator/=( const Real& fFactor )
    {
        x /= fFactor;
        y /= fFactor;
        z /= fFactor;
    }

    void operator*=( const Real& fFactor )
    {
        x *= fFactor;
        y *= fFactor;
        z *= fFactor;
    }

    Vector operator+( const Vector& vVector )
    {
        Vector v;
        v.x = x + vVector.x;
        v.y = y + vVector.y;
        v.z = z + vVector.z;

        return v;
    }

    Vector operator-( const Vector& vVector )
    {
        Vector v;
        v.x = x - vVector.x;
        v.y = y - vVector.y;
        v.z = z - vVector.z;

        return v;
    }

    Vector operator/( const Vector& vVector )
    {
        Vector v;
        v.x = x / vVector.x;
        v.y = y / vVector.y;
        v.z = z / vVector.z;

        return v;
    }

    Vector operator*( const Vector& vVector )
    {
        Vector v;
        v.x = x * vVector.x;
        v.y = y * vVector.y;
        v.z = z * vVector.z;

        return v;
    }

    Vector operator+( const Real& fFactor )
    {
        Vector v;
        v.x = x + fFactor;
        v.y = y + fFactor;
        v.z = z + fFactor;

        return v;
    }

    Vector operator-( const Real& fFactor )
    {
        Vector v;
        v.x = x - fFactor;
        v.y = y - fFactor;
        v.z = z - fFactor;

        return v;
    }

    Vector operator/( const Real& fFactor )
    {
        Vector v;
        v.x = x / fFactor;
        v.y = y / fFactor;
        v.z = z / fFactor;

        return v;
    }

    Vector operator*( const Real& fFactor )
    {
        Vector v;
        v.x = x * fFactor;
        v.y = y * fFactor;
        v.z = z * fFactor;

        return v;
    }

    Real &operator[]( int iValue )
    {
        return ( ( Real* ) this )[ iValue ];
    }

    Real operator[]( int iValue ) const
    {
        return ( ( Real* ) this )[ iValue ];
    }

    Real *Base()
    {
        return ( ( Real* ) this );
    }

    Real *Base() const
    {
        return ( ( Real* ) this );
    }

    Real Normalize()
    {
        Real fLength = Length();
        *this /= fLength;
        return fLength;
    }

    void FastNormalize()
    {
        *this *= ( Real )1.0 / Length();
    }

    Real Length()
    {
        return ( Real ) fastsqrt( ( x*x ) + ( y*y ) + ( z*z ) );
    }

    Real LengthSQR()
    {
        return ( x*x ) + ( y*y ) + ( z*z );
    }

    Real Length2D()
    {
        return ( Real ) fastsqrt( ( x*x ) + ( y*y ) );
    }

    Vector2D To2D()
    {
        return Vector2D( x , y );
    }

    Real x , y , z;
};

class Vector4D
{
public:

    Vector4D( const Real& _x = 0 , const Real& _y = 0 , const Real& _z = 0 , const Real& _w = 0 )
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    void Init( const Real& _x = 0 , const Real& _y = 0 , const Real& _z = 0 , const Real& _w = 0 )
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    bool operator!=( const Vector4D& vVector4D )
    {
        if ( x != vVector4D.x || y != vVector4D.y || z != vVector4D.z || w != vVector4D.w )
            return true;

        return false;
    }

    bool operator==( const Vector4D& vVector4D )
    {
        if ( x == vVector4D.x && y == vVector4D.y && z == vVector4D.z && w == vVector4D.w )
            return true;

        return false;
    }

    void operator=( const Vector4D&  vVector4D )
    {
        x = vVector4D.x;
        y = vVector4D.y;
        z = vVector4D.z;
        w = vVector4D.w;
    }

    void operator-=( const Vector4D&  vVector4D )
    {
        x -= vVector4D.x;
        y -= vVector4D.y;
        z -= vVector4D.z;
        w -= vVector4D.w;
    }

    void operator+=( const Vector4D&  vVector4D )
    {
        x += vVector4D.x;
        y += vVector4D.y;
        z += vVector4D.z;
        w += vVector4D.w;
    }

    void operator/=( const Vector4D&  vVector4D )
    {
        x /= vVector4D.x;
        y /= vVector4D.y;
        z /= vVector4D.z;
        w /= vVector4D.w;
    }

    void operator*=( const Vector4D&  vVector4D )
    {
        x *= vVector4D.x;
        y *= vVector4D.y;
        z *= vVector4D.z;
        w *= vVector4D.w;
    }

    void operator+=( const Real& fFactor )
    {
        x += fFactor;
        y += fFactor;
        z += fFactor;
        w += fFactor;
    }

    void operator-=( const Real& fFactor )
    {
        x -= fFactor;
        y -= fFactor;
        z -= fFactor;
        w -= fFactor;
    }

    void operator/=( const Real& fFactor )
    {
        x /= fFactor;
        y /= fFactor;
        z /= fFactor;
        w /= fFactor;
    }

    void operator*=( const Real& fFactor )
    {
        x *= fFactor;
        y *= fFactor;
        z *= fFactor;
        w *= fFactor;
    }

    Vector4D operator+( const Vector4D& vVector4D )
    {
        Vector4D v;
        v.x = x + vVector4D.x;
        v.y = y + vVector4D.y;
        v.z = z + vVector4D.z;
        v.w = w + vVector4D.w;

        return v;
    }

    Vector4D operator-( const Vector4D& vVector4D )
    {
        Vector4D v;
        v.x = x - vVector4D.x;
        v.y = y - vVector4D.y;
        v.z = z - vVector4D.z;
        v.w = w - vVector4D.w;

        return v;
    }

    Vector4D operator/( const Vector4D& vVector4D )
    {
        Vector4D v;
        v.x = x / vVector4D.x;
        v.y = y / vVector4D.y;
        v.z = z / vVector4D.z;
        v.w = w / vVector4D.w;

        return v;
    }

    Vector4D operator*( const Vector4D& vVector4D )
    {
        Vector4D v;
        v.x = x * vVector4D.x;
        v.y = y * vVector4D.y;
        v.z = z * vVector4D.z;
        v.w = w * vVector4D.w;

        return v;
    }

    Vector4D operator+( const Real& fFactor )
    {
        Vector4D v;
        v.x = x + fFactor;
        v.y = y + fFactor;
        v.z = z + fFactor;
        v.w = w + fFactor;

        return v;
    }

    Vector4D operator-( const Real& fFactor )
    {
        Vector4D v;
        v.x = x - fFactor;
        v.y = y - fFactor;
        v.z = z - fFactor;
        v.w = w - fFactor;

        return v;
    }

    Vector4D operator/( const Real& fFactor )
    {
        Vector4D v;
        v.x = x / fFactor;
        v.y = y / fFactor;
        v.z = z / fFactor;
        v.w = w / fFactor;

        return v;
    }

    Vector4D operator*( const Real& fFactor )
    {
        Vector4D v;
        v.x = x * fFactor;
        v.y = y * fFactor;
        v.z = z * fFactor;
        v.w = w * fFactor;

        return v;
    }

    Real &operator[]( int iValue )
    {
        return ( ( Real* ) this )[ iValue ];
    }

    Real operator[]( int iValue ) const
    {
        return ( ( Real* ) this )[ iValue ];
    }

    Real *Base()
    {
        return ( ( Real* ) this );
    }

    Real *Base() const
    {
        return ( ( Real* ) this );
    }

    Real Normalize()
    {
        Real fLength = Length();
        *this /= fLength;
        return fLength;
    }

    void FastNormalize()
    {
        *this *= ( Real ) 1.0 / Length();
    }

    Real Length()
    {
        return ( Real ) fastsqrt( ( x*x ) + ( y*y ) + ( z*z ) + ( w*w ) );
    }

    Real Length3D()
    {
        return ( Real ) fastsqrt( ( x*x ) + ( y*y ) + ( z*z ) );
    }

    Real Length2D()
    {
        return ( Real ) fastsqrt( ( x*x ) + ( y*y ) );
    }

    Vector To3D()
    {
        return Vector( x , y , z );
    }

    Vector2D To2D()
    {
        return Vector2D( x , y );
    }

    Real x , y , z , w;
};

class Angle2D
{
public:

    Angle2D( const Real& _x = 0 , const Real& _y = 0 )
    {
        x = _x;
        y = _y;
    }

    void Init( const Real& _x = 0 , const Real& _y = 0 )
    {
        x = _x;
        y = _y;
    }

    bool operator!=( const Angle2D& aAngle2D )
    {
        if ( x != aAngle2D.x || y != aAngle2D.y )
            return true;

        return false;
    }

    bool operator==( const Angle2D& aAngle2D )
    {
        if ( x == aAngle2D.x && y == aAngle2D.y )
            return true;

        return false;
    }

    void operator=( const Angle2D&  aAngle2D )
    {
        x = aAngle2D.x;
        y = aAngle2D.y;
    }

    void operator-=( const Angle2D&  aAngle2D )
    {
        x -= aAngle2D.x;
        y -= aAngle2D.y;
    }

    void operator+=( const Angle2D&  aAngle2D )
    {
        x += aAngle2D.x;
        y += aAngle2D.y;
    }

    void operator/=( const Angle2D& aAngle2D )
    {
        x /= aAngle2D.x;
        y /= aAngle2D.y;
    }

    void operator*=( const Angle2D& aAngle2D )
    {
        x *= aAngle2D.x;
        y *= aAngle2D.y;
    }

    void operator+=( const Real& fFactor )
    {
        x += fFactor;
        y += fFactor;
    }

    void operator-=( const Real& fFactor )
    {
        x -= fFactor;
        y -= fFactor;
    }

    void operator/=( const Real& fFactor )
    {
        x /= fFactor;
        y /= fFactor;
    }

    void operator*=( const Real& fFactor )
    {
        x *= fFactor;
        y *= fFactor;
    }

    Angle2D operator+( const Angle2D& aAngle2D )
    {
        Angle2D v;
        v.x = x + aAngle2D.x;
        v.y = y + aAngle2D.y;

        return v;
    }

    Angle2D operator-( const Angle2D& aAngle2D )
    {
        Angle2D v;
        v.x = x - aAngle2D.x;
        v.y = y - aAngle2D.y;

        return v;
    }

    Angle2D operator/( const Angle2D& aAngle2D )
    {
        Angle2D v;
        v.x = x / aAngle2D.x;
        v.y = y / aAngle2D.y;

        return v;
    }

    Angle2D operator*( const Angle2D& aAngle2D )
    {
        Angle2D v;
        v.x = x * aAngle2D.x;
        v.y = y * aAngle2D.y;

        return v;
    }

    Angle2D operator+( const Real& fFactor )
    {
        Angle2D v;
        v.x = x + fFactor;
        v.y = y + fFactor;

        return v;
    }

    Angle2D operator-( const Real& fFactor )
    {
        Angle2D v;
        v.x = x - fFactor;
        v.y = y - fFactor;

        return v;
    }

    Angle2D operator/( const Real& fFactor )
    {
        Angle2D v;
        v.x = x / fFactor;
        v.y = y / fFactor;

        return v;
    }

    Angle2D operator*( const Real& fFactor )
    {
        Angle2D v;
        v.x = x * fFactor;
        v.y = y * fFactor;

        return v;
    }

    Real &operator[]( int iValue )
    {
        return ( ( Real* ) this )[ iValue ];
    }

    Real operator[]( int iValue ) const
    {
        return ( ( Real* ) this )[ iValue ];
    }

    Real *Base()
    {
        return ( ( Real* ) this );
    }

    Real *Base() const
    {
        return ( ( Real* ) this );
    }

    Real Normalize()
    {
        Real fLength = Length();
        *this /= fLength;
        return fLength;
    }

    void FastNormalize()
    {
        *this *= ( Real )1.0 / Length();
    }

    Real Length()
    {
        return ( Real ) fastsqrt( ( x*x ) + ( y*y ) );
    }

    void Normalize180()
    {
        x = fmod( x + ( Real ) 180 , ( Real ) 360 );
        if ( x < 0 )
            x += ( Real ) 360;

        x -= ( Real ) 180;

        y = fmod( y + ( Real ) 180 , ( Real ) 360 );
        if ( y < 0 )
            y += ( Real ) 360;

        y -= ( Real ) 180;
    }

    void Normalize360()
    {
        x = fmod( x , ( Real ) 360 );

        if ( x < 0 )
            x += ( Real ) 360;

        y = fmod( y , ( Real ) 360 );

        if ( y < 0 )
            y += ( Real ) 360;
    }

    Real x , y;
};

class Angle
{
public:

    Angle( const Real& _x = 0 , const Real& _y = 0 , const Real& _z = 0 )
    {
        x = _x;
        y = _y;
        z = _z;
    }

    void Init( const Real& _x = 0 , const Real& _y = 0 , const Real& _z = 0 )
    {
        x = _x;
        y = _y;
        z = _z;
    }

    bool operator!=( const Angle& aAngle )
    {
        if ( x != aAngle.x || y != aAngle.y || z != aAngle.z )
            return true;

        return false;
    }

    bool operator==( const Angle& aAngle )
    {
        if ( x == aAngle.x && y == aAngle.y && z == aAngle.z )
            return true;

        return false;
    }

    void operator=( const Angle&  aAngle )
    {
        x = aAngle.x;
        y = aAngle.y;
        z = aAngle.z;
    }

    void operator-=( const Angle&  aAngle )
    {
        x -= aAngle.x;
        y -= aAngle.y;
        z -= aAngle.z;
    }

    void operator+=( const Angle&  aAngle )
    {
        x += aAngle.x;
        y += aAngle.y;
        z += aAngle.z;
    }

    void operator/=( const Angle&  aAngle )
    {
        x /= aAngle.x;
        y /= aAngle.y;
        z /= aAngle.z;
    }

    void operator*=( const Angle&  aAngle )
    {
        x *= aAngle.x;
        y *= aAngle.y;
        z *= aAngle.z;
    }

    void operator+=( const Real& fFactor )
    {
        x += fFactor;
        y += fFactor;
        z += fFactor;
    }

    void operator-=( const Real& fFactor )
    {
        x -= fFactor;
        y -= fFactor;
        z -= fFactor;
    }

    void operator/=( const Real& fFactor )
    {
        x /= fFactor;
        y /= fFactor;
        z /= fFactor;
    }

    void operator*=( const Real& fFactor )
    {
        x *= fFactor;
        y *= fFactor;
        z *= fFactor;
    }

    Angle operator+( const Angle& aAngle )
    {
        Angle v;
        v.x = x + aAngle.x;
        v.y = y + aAngle.y;
        v.z = z + aAngle.z;

        return v;
    }

    Angle operator-( const Angle& aAngle )
    {
        Angle v;
        v.x = x - aAngle.x;
        v.y = y - aAngle.y;
        v.z = z - aAngle.z;

        return v;
    }

    Angle operator/( const Angle& aAngle )
    {
        Angle v;
        v.x = x / aAngle.x;
        v.y = y / aAngle.y;
        v.z = z / aAngle.z;

        return v;
    }

    Angle operator*( const Angle& aAngle )
    {
        Angle v;
        v.x = x * aAngle.x;
        v.y = y * aAngle.y;
        v.z = z * aAngle.z;

        return v;
    }

    Angle operator+( const Real& fFactor )
    {
        Angle v;
        v.x = x + fFactor;
        v.y = y + fFactor;
        v.z = z + fFactor;

        return v;
    }

    Angle operator-( const Real& fFactor )
    {
        Angle v;
        v.x = x - fFactor;
        v.y = y - fFactor;
        v.z = z - fFactor;

        return v;
    }

    Angle operator/( const Real& fFactor )
    {
        Angle v;
        v.x = x / fFactor;
        v.y = y / fFactor;
        v.z = z / fFactor;

        return v;
    }

    Angle operator*( const Real& fFactor )
    {
        Angle v;
        v.x = x * fFactor;
        v.y = y * fFactor;
        v.z = z * fFactor;

        return v;
    }

    Real &operator[]( int iValue )
    {
        return ( ( Real* ) this )[ iValue ];
    }

    Real operator[]( int iValue ) const
    {
        return ( ( Real* ) this )[ iValue ];
    }

    Real *Base()
    {
        return ( ( Real* ) this );
    }

    Real *Base() const
    {
        return ( ( Real* ) this );
    }

    Real Normalize()
    {
        Real fLength = Length();
        *this /= fLength;
        return fLength;
    }

    void FastNormalize()
    {
        *this *= ( Real )1.0 / Length();
    }

    Real Length()
    {
        return ( Real ) fastsqrt( ( x*x ) + ( y*y ) + ( z*z ) );
    }

    Real Length2D()
    {
        return ( Real ) fastsqrt( ( x*x ) + ( y*y ) );
    }

    Angle2D To2D()
    {
        return Angle2D( x , y );
    }

    void Normalize180()
    {
        x = fmod( x + ( Real ) 180 , ( Real ) 360 );
        if ( x < 0 )
            x += ( Real ) 360;

        x -= ( Real ) 180;

        y = fmod( y + ( Real ) 180 , ( Real ) 360 );
        if ( y < 0 )
            y += ( Real ) 360;

        y -= ( Real ) 180;

        z = fmod( z + ( Real ) 180 , ( Real ) 360 );
        if ( z < 0 )
            z += ( Real ) 360;

        z -= ( Real ) 180;
    }

    void Normalize360()
    {
        x = fmod( x , ( Real ) 360 );

        if ( x < 0 )
            x += ( Real ) 360;

        y = fmod( y , ( Real ) 360 );

        if ( y < 0 )
            y += ( Real ) 360;

        z = fmod( z , ( Real ) 360 );

        if ( z < 0 )
            z += ( Real ) 360;
    }

    Real x , y , z;
};

class VectorAligned : public Vector
{
public:

    VectorAligned( const Real& _x = 0 , const Real& _y = 0 , const Real& _z = 0 , const Real& _w = 0 )
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    VectorAligned( const Vector &vVector )
    {
        this->x = vVector.x;
        this->y = vVector.y;
        this->z = vVector.z;
    }

    void operator=( const VectorAligned &vVectorAligned )
    {
        x = vVectorAligned.x;
        y = vVectorAligned.y;
        z = vVectorAligned.z;
        w = vVectorAligned.w;
    }

    Real &operator[]( int iValue )
    {
        return ( ( Real* ) this )[ iValue ];
    }

    Real operator[]( int iValue ) const
    {
        return ( ( Real* ) this )[ iValue ];
    }

    float w;
};

class VPlane
{
public:
    Vector		m_Normal;
    Real		m_Dist;
};

class CustomRay
{
public:
    CustomRay( const Vector &orig , const Vector &dir ) : orig( orig ) , dir( dir )
    {
        invdir.Init( 1 , 1 , 1 );
        invdir /= dir;
        sign[ 0 ] = ( invdir.x < 0 );
        sign[ 1 ] = ( invdir.y < 0 );
        sign[ 2 ] = ( invdir.z < 0 );
    }

    Vector orig , dir;       // ray orig and dir
    Vector invdir;
    int sign[ 3 ];
};

void VectorToAngles( const Vector& forward , Angle &angles );
void VectorToAngles( const Vector &forward , const Vector &pseudoup , Angle &angles );
void CrossProduct( const Vector& a , const Vector& b , Vector& result );
void AngleToVectors( const Angle &angles , Vector *forward = nullptr , Vector *right = nullptr , Vector *up = nullptr );
void AngleToVectorsTranspose( const Angle &angles , Vector *forward = nullptr , Vector *right = nullptr , Vector *up = nullptr );
Real DotProduct( const Real *v1 , const Real *v2 );
void VectorTransform( const float *in1 , const Matrix3x4& in2 , float *out );
void VectorTransform( const Vector& in1 , const Matrix3x4 &in2 , Vector &out );
void MatrixAngles( const Matrix3x4 &matrix , Angle &angles , Vector &position );
void AngleMatrix( const Angle &angles , const Vector &position , Matrix3x4& matrix );
void AngleMatrix( const Angle &angles , Matrix3x4& matrix );
void VectorRotate( const Vector& in1 , const Matrix3x4 &in2 , Vector &out );
void MatrixGetColumn( const Matrix3x4& in , int column , Vector &out );
unsigned char FastFToC( float c );
void VectorMA( const Vector& start , float scale , const Vector& direction , Vector& dest );
void VectorSubtract( const Vector& a , const Vector& b , Vector& c );
void VectorAdd( const Vector& a , const Vector& b , Vector& c );
Real DotProduct( const Vector& a , const Vector& b );
float FLerp( float f1 , float f2 , float i1 , float i2 , float x );
void VectorIRotate( const Vector& in1 , const Matrix3x4& in2 , Vector& out );
void VectorITransform( const Vector &in1 , const Matrix3x4& in2 , Vector &out );
bool IntersectBox( const Vector& vPos , const Vector& vMins , const Vector& vMaxs );
bool RayIntersectBox( const Vector& vEye , const Vector& vDir , const Vector& vMins , const Vector& vMaxs );
bool RayIntersectCapsule( Vector eyePos , Vector myDir , Vector capsuleA , Vector capsuleB , float radius );
bool WorldToScreen( const Vector &Origin , Vector &Screen );
bool IsBoxCapsule( mstudiobbox_t* Box );
bool IsOBBIntersectingOBB( const Vector &vecOrigin1 , const Angle &vecAngles1 , const Vector& boxMin1 , const Vector& boxMax1 ,
                           const Vector &vecOrigin2 , const Angle &vecAngles2 , const Vector& boxMin2 , const Vector& boxMax2 , float flTolerance = 0.0f );
#endif