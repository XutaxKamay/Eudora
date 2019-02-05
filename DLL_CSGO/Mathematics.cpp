#include "Includes.hxx"
#include "Main.hxx"

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/mathlib/mathlib_base.cpp

const uint32 ALIGN16 g_SIMD_ComponentMask[ 4 ][ 4 ] =
{
    { 0xFFFFFFFF, 0, 0, 0 },{ 0, 0xFFFFFFFF, 0, 0 },{ 0, 0, 0xFFFFFFFF, 0 },{ 0, 0, 0, 0xFFFFFFFF }
};

void CrossProduct( const Vector& a , const Vector& b , Vector& result )
{
    result.x = a.y*b.z - a.z*b.y;
    result.y = a.z*b.x - a.x*b.z;
    result.z = a.x*b.y - a.y*b.x;
}

void VectorToAngles( const Vector& forward , Angle &angles )
{
    Real tmp , yaw , pitch;

    if ( forward[ 1 ] == 0.0f && forward[ 0 ] == 00.0f )
    {
        yaw = 0;
        if ( forward[ 2 ] > 0.0f )
            pitch = 270;
        else
            pitch = 90;
    }
    else
    {
        yaw = RADTODEG( atan2( forward[ 1 ] , forward[ 0 ] ) );
        if ( yaw < 0 )
            yaw += 360;

        tmp = sqrt( forward[ 0 ] * forward[ 0 ] + forward[ 1 ] * forward[ 1 ] );
        pitch = RADTODEG( atan2( -forward[ 2 ] , tmp ) );
        if ( pitch < 0 )
            pitch += 360;
    }

    angles[ 0 ] = pitch;
    angles[ 1 ] = yaw;
    angles[ 2 ] = 0;
}

void VectorToAngles( const Vector &forward , const Vector &pseudoup , Angle &angles )
{
    Vector left;

    CrossProduct( pseudoup , forward , left );
    left.Normalize();

    Real xyDist = sqrt( forward[ 0 ] * forward[ 0 ] + forward[ 1 ] * forward[ 1 ] );

    // enough here to get angles?
    if ( xyDist > 0.001f )
    {
        // (yaw)	y = ATAN( forward.y, forward.x );		-- in our space, forward is the X axis
        angles[ 1 ] = RADTODEG( atan2( forward[ 1 ] , forward[ 0 ] ) );

        // The engine does pitch inverted from this, but we always end up negating it in the DLL
        // UNDONE: Fix the engine to make it consistent
        // (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
        angles[ 0 ] = RADTODEG( atan2( -forward[ 2 ] , xyDist ) );

        Real up_z = ( left[ 1 ] * forward[ 0 ] ) - ( left[ 0 ] * forward[ 1 ] );

        // (roll)	z = ATAN( left.z, up.z );
        angles[ 2 ] = RADTODEG( atan2( left[ 2 ] , up_z ) );
    }
    else	// forward is mostly Z, gimbal lock-
    {
        // (yaw)	y = ATAN( -left.x, left.y );			-- forward is mostly z, so use right for yaw
        angles[ 1 ] = RADTODEG( atan2( -left[ 0 ] , left[ 1 ] ) ); //This was originally copied from the "void MatrixAngles( const Matrix3x4& matrix, Real *angles )" code, and it's 180 degrees off, negated the values and it all works now (Dave Kircher)

                                                                   // The engine does pitch inverted from this, but we always end up negating it in the DLL
                                                                   // UNDONE: Fix the engine to make it consistent
                                                                   // (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
        angles[ 0 ] = RADTODEG( atan2( -forward[ 2 ] , xyDist ) );

        // Assume no roll in this case as one degree of freedom has been lost (i.e. yaw == roll)
        angles[ 2 ] = 0;
    }
}

void AngleToVectors( const Angle &angles , Vector *forward , Vector *right , Vector *up )
{
    Real sr , sp , sy , cr , cp , cy;

    SinCos( DEGTORAD( angles[ 1 ] ) , &sy , &cy );
    SinCos( DEGTORAD( angles[ 0 ] ) , &sp , &cp );
    SinCos( DEGTORAD( angles[ 2 ] ) , &sr , &cr );

    if ( forward != nullptr )
    {
        forward->x = cp * cy;
        forward->y = cp * sy;
        forward->z = -sp;
    }

    if ( right != nullptr )
    {
        right->x = ( -1 * sr*sp*cy + -1 * cr*-sy );
        right->y = ( -1 * sr*sp*sy + -1 * cr*cy );
        right->z = -1 * sr*cp;
    }

    if ( up != nullptr )
    {
        up->x = ( cr*sp*cy + -sr * -sy );
        up->y = ( cr*sp*sy + -sr * cy );
        up->z = cr * cp;
    }
}

void AngleToVectorsTranspose( const Angle &angles , Vector *forward , Vector *right , Vector *up )
{
    float sr , sp , sy , cr , cp , cy;

    SinCos( DEGTORAD( angles[ 1 ] ) , &sy , &cy );
    SinCos( DEGTORAD( angles[ 0 ] ) , &sp , &cp );
    SinCos( DEGTORAD( angles[ 2 ] ) , &sr , &cr );

    if ( forward != nullptr )
    {
        forward->x = cp * cy;
        forward->y = ( sr*sp*cy + cr * -sy );
        forward->z = ( cr*sp*cy + -sr * -sy );
    }

    if ( right != nullptr )
    {
        right->x = cp * sy;
        right->y = ( sr*sp*sy + cr * cy );
        right->z = ( cr*sp*sy + -sr * cy );
    }

    if ( up != nullptr )
    {
        up->x = -sp;
        up->y = sr * cp;
        up->z = cr * cp;
    }
}

Real DotProduct( const Real *v1 , const Real *v2 )
{
    return v1[ 0 ] * v2[ 0 ] + v1[ 1 ] * v2[ 1 ] + v1[ 2 ] * v2[ 2 ];
}

void VectorTransform( const float *in1 , const Matrix3x4& in2 , float *out )
{
    out[ 0 ] = DotProduct( in1 , in2[ 0 ] ) + in2[ 0 ][ 3 ];
    out[ 1 ] = DotProduct( in1 , in2[ 1 ] ) + in2[ 1 ][ 3 ];
    out[ 2 ] = DotProduct( in1 , in2[ 2 ] ) + in2[ 2 ][ 3 ];
}

void VectorTransform( const Vector& in1 , const Matrix3x4 &in2 , Vector &out )
{
    VectorTransform( &in1.x , in2 , &out.x );
}

void MatrixGetColumn( const Matrix3x4& in , int column , Vector &out )
{
    out.x = in[ 0 ][ column ];
    out.y = in[ 1 ][ column ];
    out.z = in[ 2 ][ column ];
}

void MatrixPosition( const Matrix3x4 &matrix , Vector &position )
{
    MatrixGetColumn( matrix , 3 , position );
}

void MatrixAngles( const Matrix3x4& matrix , float *angles )
{
    float forward[ 3 ];
    float left[ 3 ];
    float up[ 3 ];

    //
    // Extract the basis vectors from the matrix. Since we only need the Z
    // component of the up vector, we don't get X and Y.
    //
    forward[ 0 ] = matrix[ 0 ][ 0 ];
    forward[ 1 ] = matrix[ 1 ][ 0 ];
    forward[ 2 ] = matrix[ 2 ][ 0 ];
    left[ 0 ] = matrix[ 0 ][ 1 ];
    left[ 1 ] = matrix[ 1 ][ 1 ];
    left[ 2 ] = matrix[ 2 ][ 1 ];
    up[ 2 ] = matrix[ 2 ][ 2 ];

    float xyDist = sqrtf( forward[ 0 ] * forward[ 0 ] + forward[ 1 ] * forward[ 1 ] );

    // enough here to get angles?
    if ( xyDist > 0.001f )
    {
        // (yaw)	y = ATAN( forward.y, forward.x );		-- in our space, forward is the X axis
        angles[ 1 ] = RADTODEG( atan2f( forward[ 1 ] , forward[ 0 ] ) );

        // (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
        angles[ 0 ] = RADTODEG( atan2f( -forward[ 2 ] , xyDist ) );

        // (roll)	z = ATAN( left.z, up.z );
        angles[ 2 ] = RADTODEG( atan2f( left[ 2 ] , up[ 2 ] ) );
    }
    else	// forward is mostly Z, gimbal lock-
    {
        // (yaw)	y = ATAN( -left.x, left.y );			-- forward is mostly z, so use right for yaw
        angles[ 1 ] = RADTODEG( atan2f( -left[ 0 ] , left[ 1 ] ) );

        // (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
        angles[ 0 ] = RADTODEG( atan2f( -forward[ 2 ] , xyDist ) );

        // Assume no roll in this case as one degree of freedom has been lost (i.e. yaw == roll)
        angles[ 2 ] = 0;
    }
}

void MatrixAngles( const Matrix3x4 &matrix , Angle &angles )
{
    MatrixAngles( matrix , &angles.x );
}

void MatrixAngles( const Matrix3x4 &matrix , Angle &angles , Vector &position )
{
    MatrixAngles( matrix , angles );
    MatrixPosition( matrix , position );
}

void AngleMatrix( const Angle &angles , Matrix3x4& matrix )
{
    float sr , sp , sy , cr , cp , cy;

    SinCos( DEGTORAD( angles[ Yaw ] ) , &sy , &cy );
    SinCos( DEGTORAD( angles[ Pitch ] ) , &sp , &cp );
    SinCos( DEGTORAD( angles[ Roll ] ) , &sr , &cr );

    // matrix = (YAW * PITCH) * ROLL
    matrix[ 0 ][ 0 ] = cp * cy;
    matrix[ 1 ][ 0 ] = cp * sy;
    matrix[ 2 ][ 0 ] = -sp;

    float crcy = cr * cy;
    float crsy = cr * sy;
    float srcy = sr * cy;
    float srsy = sr * sy;
    matrix[ 0 ][ 1 ] = sp * srcy - crsy;
    matrix[ 1 ][ 1 ] = sp * srsy + crcy;
    matrix[ 2 ][ 1 ] = sr * cp;

    matrix[ 0 ][ 2 ] = ( sp*crcy + srsy );
    matrix[ 1 ][ 2 ] = ( sp*crsy - srcy );
    matrix[ 2 ][ 2 ] = cr * cp;

    matrix[ 0 ][ 3 ] = 0.0f;
    matrix[ 1 ][ 3 ] = 0.0f;
    matrix[ 2 ][ 3 ] = 0.0f;
}

void MatrixSetColumn( const Vector &in , int column , Matrix3x4& out )
{
    out[ 0 ][ column ] = in.x;
    out[ 1 ][ column ] = in.y;
    out[ 2 ][ column ] = in.z;
}

void AngleMatrix( const Angle &angles , const Vector &position , Matrix3x4& matrix )
{
    AngleMatrix( angles , matrix );
    MatrixSetColumn( position , 3 , matrix );
}

unsigned char FastFToC( float c )
{
    volatile float dc;

    // ieee trick
    dc = c * 255.0f + ( float ) ( 1 << 23 );

    // return the lsb
#if defined( _X360 )
    return ( ( unsigned char* ) &dc )[ 3 ];
#else
    return *( unsigned char* ) &dc;
#endif
}

void VectorRotate( const float *in1 , const Matrix3x4& in2 , float *out )
{
    out[ 0 ] = DotProduct( in1 , in2[ 0 ] );
    out[ 1 ] = DotProduct( in1 , in2[ 1 ] );
    out[ 2 ] = DotProduct( in1 , in2[ 2 ] );
}

void VectorRotate( const Vector& in1 , const Matrix3x4 &in2 , Vector &out )
{
    VectorRotate( &in1.x , in2 , &out.x );
}

void VectorMAInline( const float* start , float scale , const float* direction , float* dest )
{
    dest[ 0 ] = start[ 0 ] + direction[ 0 ] * scale;
    dest[ 1 ] = start[ 1 ] + direction[ 1 ] * scale;
    dest[ 2 ] = start[ 2 ] + direction[ 2 ] * scale;
}

void VectorMAInline( const Vector& start , float scale , const Vector& direction , Vector& dest )
{
    dest.x = start.x + direction.x*scale;
    dest.y = start.y + direction.y*scale;
    dest.z = start.z + direction.z*scale;
}

void VectorMA( const Vector& start , float scale , const Vector& direction , Vector& dest )
{
    VectorMAInline( start , scale , direction , dest );
}

void VectorSubtract( const Real *a , const Real *b , Real *c )
{
    c[ 0 ] = a[ 0 ] - b[ 0 ];
    c[ 1 ] = a[ 1 ] - b[ 1 ];
    c[ 2 ] = a[ 2 ] - b[ 2 ];
}

void VectorSubtract( const Vector& a , const Vector& b , Vector& c )
{
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
}

void VectorAdd( const Vector& a , const Vector& b , Vector& c )
{
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
}

Real DotProduct( const Vector& a , const Vector& b )
{
    return( a.x*b.x + a.y*b.y + a.z*b.z );
}

float FLerp( float f1 , float f2 , float i1 , float i2 , float x )
{
    return f1 + ( f2 - f1 )*( x - i1 ) / ( i2 - i1 );
}

// rotate by the inverse of the matrix
void VectorIRotate( const Vector& in1 , const Matrix3x4& in2 , Vector& out )
{
    out[ 0 ] = in1[ 0 ] * in2[ 0 ][ 0 ] + in1[ 1 ] * in2[ 1 ][ 0 ] + in1[ 2 ] * in2[ 2 ][ 0 ];
    out[ 1 ] = in1[ 0 ] * in2[ 0 ][ 1 ] + in1[ 1 ] * in2[ 1 ][ 1 ] + in1[ 2 ] * in2[ 2 ][ 1 ];
    out[ 2 ] = in1[ 0 ] * in2[ 0 ][ 2 ] + in1[ 1 ] * in2[ 1 ][ 2 ] + in1[ 2 ] * in2[ 2 ][ 2 ];
}

// assuming the matrix is orthonormal, transform in1 by the transpose (also the inverse in this case) of in2.
void VectorITransform( const Vector &in1 , const Matrix3x4& in2 , Vector &out )
{
    float in1t[ 3 ];

    in1t[ 0 ] = in1[ 0 ] - in2[ 0 ][ 3 ];
    in1t[ 1 ] = in1[ 1 ] - in2[ 1 ][ 3 ];
    in1t[ 2 ] = in1[ 2 ] - in2[ 2 ][ 3 ];

    out[ 0 ] = in1t[ 0 ] * in2[ 0 ][ 0 ] + in1t[ 1 ] * in2[ 1 ][ 0 ] + in1t[ 2 ] * in2[ 2 ][ 0 ];
    out[ 1 ] = in1t[ 0 ] * in2[ 0 ][ 1 ] + in1t[ 1 ] * in2[ 1 ][ 1 ] + in1t[ 2 ] * in2[ 2 ][ 1 ];
    out[ 2 ] = in1t[ 0 ] * in2[ 0 ][ 2 ] + in1t[ 1 ] * in2[ 1 ][ 2 ] + in1t[ 2 ] * in2[ 2 ][ 2 ];
}

bool WorldToScreen( const Vector &Origin , Vector &Screen )
{
    bool Result = false;
    const VMatrix& WorldToScreen = EngineClient->WorldToScreenMatrix();

    float w = WorldToScreen[ 3 ][ 0 ] * Origin[ 0 ] + WorldToScreen[ 3 ][ 1 ] * Origin[ 1 ] + WorldToScreen[ 3 ][ 2 ] * Origin[ 2 ] + WorldToScreen[ 3 ][ 3 ];
    Screen[ 2 ] = 0.0f;

    if ( w > 0.001f )
    {
        float invw = 1.0f / w;

        int ScreenSize[ 2 ];
        EngineClient->GetScreenSize( ScreenSize[ 0 ] , ScreenSize[ 1 ] );

        Screen[ 0 ] = ( ScreenSize[ 0 ] / 2.0f ) + ( ( ( ( WorldToScreen[ 0 ][ 0 ] * Origin[ 0 ] + WorldToScreen[ 0 ][ 1 ] * Origin[ 1 ] + WorldToScreen[ 0 ][ 2 ] * Origin[ 2 ] + WorldToScreen[ 0 ][ 3 ] ) * invw ) / 2.0f ) * ScreenSize[ 0 ] + 0.5f );
        Screen[ 1 ] = ( ScreenSize[ 1 ] / 2.0f ) - ( ( ( ( WorldToScreen[ 1 ][ 0 ] * Origin[ 0 ] + WorldToScreen[ 1 ][ 1 ] * Origin[ 1 ] + WorldToScreen[ 1 ][ 2 ] * Origin[ 2 ] + WorldToScreen[ 1 ][ 3 ] ) * invw ) / 2.0f ) * ScreenSize[ 1 ] + 0.5f );
        Result = true;
    }

    return Result;
}

bool IsBoxCapsule( mstudiobbox_t* Box )
{
    return ( Box->m_flRadius != -1.0f );
}

bool IntersectBox( const Vector &vPos , const Vector &vMins , const Vector& vMaxs )
{
    return ( vPos.x >= vMins.x && vPos.x <= vMaxs.x ) &&
        ( vPos.y >= vMins.y && vPos.y <= vMaxs.y ) &&
        ( vPos.z >= vMins.z && vPos.z <= vMaxs.z );
}

FORCEINLINE fltx4 LoadUnalignedSIMD( const void *pSIMD )
{
    return *( reinterpret_cast< const fltx4 * > ( pSIMD ) );
}

FORCEINLINE float SubFloat( const fltx4 & a , int idx )
{
    return a.m128_f32[ idx ];
}

FORCEINLINE float & SubFloat( fltx4 & a , int idx )
{
    return a.m128_f32[ idx ];
}

FORCEINLINE uint32 SubInt( const fltx4 & a , int idx )
{
    return a.m128_u32[ idx ];
}

FORCEINLINE uint32 & SubInt( fltx4 & a , int idx )
{
    return a.m128_u32[ idx ];
}

FORCEINLINE fltx4 SplatXSIMD( const fltx4 & a )
{
    fltx4 retVal;
    SubFloat( retVal , 0 ) = SubFloat( a , 0 );
    SubFloat( retVal , 1 ) = SubFloat( a , 0 );
    SubFloat( retVal , 2 ) = SubFloat( a , 0 );
    SubFloat( retVal , 3 ) = SubFloat( a , 0 );
    return retVal;
}

FORCEINLINE fltx4 SplatYSIMD( fltx4 a )
{
    fltx4 retVal;
    SubFloat( retVal , 0 ) = SubFloat( a , 1 );
    SubFloat( retVal , 1 ) = SubFloat( a , 1 );
    SubFloat( retVal , 2 ) = SubFloat( a , 1 );
    SubFloat( retVal , 3 ) = SubFloat( a , 1 );
    return retVal;
}

FORCEINLINE fltx4 SplatZSIMD( fltx4 a )
{
    fltx4 retVal;
    SubFloat( retVal , 0 ) = SubFloat( a , 2 );
    SubFloat( retVal , 1 ) = SubFloat( a , 2 );
    SubFloat( retVal , 2 ) = SubFloat( a , 2 );
    SubFloat( retVal , 3 ) = SubFloat( a , 2 );
    return retVal;
}

FORCEINLINE fltx4 MulSIMD( const fltx4 & a , const fltx4 & b )				// a*b
{
    fltx4 x4;
    x4.m = _mm_mul_ps( a.m , b.m );
    return x4;
};

FORCEINLINE fltx4 AddSIMD( const fltx4 & a , const fltx4 & b )				// a+b
{
    fltx4 x4;
    x4.m = _mm_add_ps( a.m , b.m );
    return x4;
};

FORCEINLINE fltx4 AndSIMD( const fltx4 & a , const fltx4 & b )				// a & b
{
    fltx4 x4;
    x4.m = _mm_and_ps( a.m , b.m );
    return x4;
}

FORCEINLINE void StoreUnalignedSIMD( float *pSIMD , const fltx4 & a )
{
    *( reinterpret_cast< fltx4 * > ( pSIMD ) ) = a;
}

void ConcatTransforms( const Matrix3x4& in1 , const Matrix3x4& in2 , Matrix3x4& out )
{
    fltx4 lastMask = *( fltx4 * ) ( &g_SIMD_ComponentMask[ 3 ] );
    fltx4 rowA0 = LoadUnalignedSIMD( in1.flMatVal[ 0 ] );
    fltx4 rowA1 = LoadUnalignedSIMD( in1.flMatVal[ 1 ] );
    fltx4 rowA2 = LoadUnalignedSIMD( in1.flMatVal[ 2 ] );

    fltx4 rowB0 = LoadUnalignedSIMD( in2.flMatVal[ 0 ] );
    fltx4 rowB1 = LoadUnalignedSIMD( in2.flMatVal[ 1 ] );
    fltx4 rowB2 = LoadUnalignedSIMD( in2.flMatVal[ 2 ] );

    // now we have the rows of m0 and the columns of m1
    // first output row
    fltx4 A0 = SplatXSIMD( rowA0 );
    fltx4 A1 = SplatYSIMD( rowA0 );
    fltx4 A2 = SplatZSIMD( rowA0 );
    fltx4 mul00 = MulSIMD( A0 , rowB0 );
    fltx4 mul01 = MulSIMD( A1 , rowB1 );
    fltx4 mul02 = MulSIMD( A2 , rowB2 );
    fltx4 out0 = AddSIMD( mul00 , AddSIMD( mul01 , mul02 ) );

    // second output row
    A0 = SplatXSIMD( rowA1 );
    A1 = SplatYSIMD( rowA1 );
    A2 = SplatZSIMD( rowA1 );
    fltx4 mul10 = MulSIMD( A0 , rowB0 );
    fltx4 mul11 = MulSIMD( A1 , rowB1 );
    fltx4 mul12 = MulSIMD( A2 , rowB2 );
    fltx4 out1 = AddSIMD( mul10 , AddSIMD( mul11 , mul12 ) );

    // third output row
    A0 = SplatXSIMD( rowA2 );
    A1 = SplatYSIMD( rowA2 );
    A2 = SplatZSIMD( rowA2 );
    fltx4 mul20 = MulSIMD( A0 , rowB0 );
    fltx4 mul21 = MulSIMD( A1 , rowB1 );
    fltx4 mul22 = MulSIMD( A2 , rowB2 );
    fltx4 out2 = AddSIMD( mul20 , AddSIMD( mul21 , mul22 ) );

    // add in translation vector
    A0 = AndSIMD( rowA0 , lastMask );
    A1 = AndSIMD( rowA1 , lastMask );
    A2 = AndSIMD( rowA2 , lastMask );
    out0 = AddSIMD( out0 , A0 );
    out1 = AddSIMD( out1 , A1 );
    out2 = AddSIMD( out2 , A2 );

    // write to output
    StoreUnalignedSIMD( out.flMatVal[ 0 ] , out0 );
    StoreUnalignedSIMD( out.flMatVal[ 1 ] , out1 );
    StoreUnalignedSIMD( out.flMatVal[ 2 ] , out2 );
}

static inline void ComputeAbsMatrix( const Matrix3x4& in , Matrix3x4& out )
{
    FloatBits( out[ 0 ][ 0 ] ) = FloatAbsBits( in[ 0 ][ 0 ] );
    FloatBits( out[ 0 ][ 1 ] ) = FloatAbsBits( in[ 0 ][ 1 ] );
    FloatBits( out[ 0 ][ 2 ] ) = FloatAbsBits( in[ 0 ][ 2 ] );
    FloatBits( out[ 1 ][ 0 ] ) = FloatAbsBits( in[ 1 ][ 0 ] );
    FloatBits( out[ 1 ][ 1 ] ) = FloatAbsBits( in[ 1 ][ 1 ] );
    FloatBits( out[ 1 ][ 2 ] ) = FloatAbsBits( in[ 1 ][ 2 ] );
    FloatBits( out[ 2 ][ 0 ] ) = FloatAbsBits( in[ 2 ][ 0 ] );
    FloatBits( out[ 2 ][ 1 ] ) = FloatAbsBits( in[ 2 ][ 1 ] );
    FloatBits( out[ 2 ][ 2 ] ) = FloatAbsBits( in[ 2 ][ 2 ] );
}

inline float MatrixRowDotProduct( const Matrix3x4 &in1 , int row , const Vector& in2 )
{
    return DotProduct( in1[ row ] , in2.Base() );
}

FORCEINLINE void VectorCopy( const Real *a , Real *b )
{
    b[ 0 ] = a[ 0 ];
    b[ 1 ] = a[ 1 ];
    b[ 2 ] = a[ 2 ];
}

inline float MatrixColumnDotProduct( const Matrix3x4 &in1 , int col , const Vector& in2 )
{
    return in1[ 0 ][ col ] * in2[ 0 ] + in1[ 1 ][ col ] * in2[ 1 ] + in1[ 2 ][ col ] * in2[ 2 ];
}

void CrossProduct( const float* v1 , const float* v2 , float* cross )
{
    cross[ 0 ] = v1[ 1 ] * v2[ 2 ] - v1[ 2 ] * v2[ 1 ];
    cross[ 1 ] = v1[ 2 ] * v2[ 0 ] - v1[ 0 ] * v2[ 2 ];
    cross[ 2 ] = v1[ 0 ] * v2[ 1 ] - v1[ 1 ] * v2[ 0 ];
}

//-----------------------------------------------------------------------------
// Compute a separating plane between two boxes (expensive!)
// Returns false if no separating plane exists
//-----------------------------------------------------------------------------
static bool ComputeSeparatingPlane( const Matrix3x4 &worldToBox1 , const Matrix3x4 &box2ToWorld ,
                                    const Vector& box1Size , const Vector& box2Size , float tolerance , cplane_t* pPlane )
{
    // The various separating planes can be either
    // 1) A plane parallel to one of the box face planes
    // 2) A plane parallel to the cross-product of an edge from each box

    // First, compute the basis of second box in the space of the first box
    // NOTE: These basis place the origin at the centroid of each box!
    Matrix3x4 box2ToBox1;
    ConcatTransforms( worldToBox1 , box2ToWorld , box2ToBox1 );

    // We're going to be using the origin of box2 in the space of box1 alot,
    // lets extract it from the matrix....
    Vector box2Origin;
    MatrixGetColumn( box2ToBox1 , 3 , box2Origin );

    // Next get the absolute values of these entries and store in absbox2ToBox1.
    Matrix3x4 absBox2ToBox1;
    ComputeAbsMatrix( box2ToBox1 , absBox2ToBox1 );

    // There are 15 tests to make.  The first 3 involve trying planes parallel
    // to the faces of the first box.

    // NOTE: The algorithm here involves finding the projections of the two boxes
    // onto a particular line. If the projections on the line do not overlap,
    // that means that there's a plane perpendicular to the line which separates
    // the two boxes; and we've therefore found a separating plane.

    // The way we check for overlay is we find the projections of the two boxes
    // onto the line, and add them up. We compare the sum with the projection
    // of the relative center of box2 onto the same line.

    Vector tmp;
    float boxProjectionSum;
    float originProjection;

    // NOTE: For these guys, we're taking advantage of the fact that the ith
    // row of the box2ToBox1 is the direction of the box1 (x,y,z)-axis
    // transformed into the space of box2.

    // First side of box 1
    boxProjectionSum = box1Size.x + MatrixRowDotProduct( absBox2ToBox1 , 0 , box2Size );
    originProjection = FloatMakePositive( box2Origin.x ) + tolerance;
    if ( FloatBits( originProjection ) > FloatBits( boxProjectionSum ) )
    {
        VectorCopy( worldToBox1[ 0 ] , pPlane->normal.Base() );
        return true;
    }

    // Second side of box 1
    boxProjectionSum = box1Size.y + MatrixRowDotProduct( absBox2ToBox1 , 1 , box2Size );
    originProjection = FloatMakePositive( box2Origin.y ) + tolerance;
    if ( FloatBits( originProjection ) > FloatBits( boxProjectionSum ) )
    {
        VectorCopy( worldToBox1[ 1 ] , pPlane->normal.Base() );
        return true;
    }

    // Third side of box 1
    boxProjectionSum = box1Size.z + MatrixRowDotProduct( absBox2ToBox1 , 2 , box2Size );
    originProjection = FloatMakePositive( box2Origin.z ) + tolerance;
    if ( FloatBits( originProjection ) > FloatBits( boxProjectionSum ) )
    {
        VectorCopy( worldToBox1[ 2 ] , pPlane->normal.Base() );
        return true;
    }

    // The next three involve checking splitting planes parallel to the
    // faces of the second box.

    // NOTE: For these guys, we're taking advantage of the fact that the 0th
    // column of the box2ToBox1 is the direction of the box2 x-axis
    // transformed into the space of box1.
    // Here, we're determining the distance of box2's center from box1's center
    // by projecting it onto a line parallel to box2's axis

    // First side of box 2
    boxProjectionSum = box2Size.x + MatrixColumnDotProduct( absBox2ToBox1 , 0 , box1Size );
    originProjection = FloatMakePositive( MatrixColumnDotProduct( box2ToBox1 , 0 , box2Origin ) ) + tolerance;
    if ( FloatBits( originProjection ) > FloatBits( boxProjectionSum ) )
    {
        MatrixGetColumn( box2ToWorld , 0 , pPlane->normal );
        return true;
    }

    // Second side of box 2
    boxProjectionSum = box2Size.y + MatrixColumnDotProduct( absBox2ToBox1 , 1 , box1Size );
    originProjection = FloatMakePositive( MatrixColumnDotProduct( box2ToBox1 , 1 , box2Origin ) ) + tolerance;
    if ( FloatBits( originProjection ) > FloatBits( boxProjectionSum ) )
    {
        MatrixGetColumn( box2ToWorld , 1 , pPlane->normal );
        return true;
    }

    // Third side of box 2
    boxProjectionSum = box2Size.z + MatrixColumnDotProduct( absBox2ToBox1 , 2 , box1Size );
    originProjection = FloatMakePositive( MatrixColumnDotProduct( box2ToBox1 , 2 , box2Origin ) ) + tolerance;
    if ( FloatBits( originProjection ) > FloatBits( boxProjectionSum ) )
    {
        MatrixGetColumn( box2ToWorld , 2 , pPlane->normal );
        return true;
    }

    // Next check the splitting planes which are orthogonal to the pairs
    // of edges, one from box1 and one from box2.  As only direction matters,
    // there are 9 pairs since each box has 3 distinct edge directions.

    // Here, we take advantage of the fact that the edges from box 1 are all
    // axis aligned; therefore the crossproducts are simplified. Let's walk through
    // the example of b1e1 x b2e1:

    // In this example, the line to check is perpendicular to b1e1 + b2e2
    // we can compute this line by taking the cross-product:
    //
    // [  i  j  k ]
    // [  1  0  0 ] = - ez j + ey k = l1
    // [ ex ey ez ]

    // Where ex, ey, ez is the components of box2's x axis in the space of box 1,
    // which is == to the 0th column of of box2toBox1

    // The projection of box1 onto this line = the absolute dot product of the box size
    // against the line, which =
    // AbsDot( box1Size, l1 ) = abs( -ez * box1.y ) + abs( ey * box1.z )

    // To compute the projection of box2 onto this line, we'll do it in the space of box 2
    //
    // [  i  j  k ]
    // [ fx fy fz ] = fz j - fy k = l2
    // [  1  0  0 ]

    // Where fx, fy, fz is the components of box1's x axis in the space of box 2,
    // which is == to the 0th row of of box2toBox1

    // The projection of box2 onto this line = the absolute dot product of the box size
    // against the line, which =
    // AbsDot( box2Size, l2 ) = abs( fz * box2.y ) + abs ( fy * box2.z )

    // The projection of the relative origin position on this line is done in the
    // space of box 1:
    //
    // originProjection = DotProduct( <-ez j + ey k>, box2Origin ) =
    //		-ez * box2Origin.y + ey * box2Origin.z

    // NOTE: These checks can be bogus if both edges are parallel. The if
    // checks at the beginning of each block are designed to catch that case

    // b1e1 x b2e1
    if ( absBox2ToBox1[ 0 ][ 0 ] < 1.0f - 1e-3f )
    {
        boxProjectionSum =
            box1Size.y * absBox2ToBox1[ 2 ][ 0 ] + box1Size.z * absBox2ToBox1[ 1 ][ 0 ] +
            box2Size.y * absBox2ToBox1[ 0 ][ 2 ] + box2Size.z * absBox2ToBox1[ 0 ][ 1 ];
        originProjection = FloatMakePositive( -box2Origin.y * box2ToBox1[ 2 ][ 0 ] + box2Origin.z * box2ToBox1[ 1 ][ 0 ] ) + tolerance;
        if ( FloatBits( originProjection ) > FloatBits( boxProjectionSum ) )
        {
            MatrixGetColumn( box2ToWorld , 0 , tmp );
            CrossProduct( worldToBox1[ 0 ] , tmp.Base() , pPlane->normal.Base() );
            return true;
        }
    }

    // b1e1 x b2e2
    if ( absBox2ToBox1[ 0 ][ 1 ] < 1.0f - 1e-3f )
    {
        boxProjectionSum =
            box1Size.y * absBox2ToBox1[ 2 ][ 1 ] + box1Size.z * absBox2ToBox1[ 1 ][ 1 ] +
            box2Size.x * absBox2ToBox1[ 0 ][ 2 ] + box2Size.z * absBox2ToBox1[ 0 ][ 0 ];
        originProjection = FloatMakePositive( -box2Origin.y * box2ToBox1[ 2 ][ 1 ] + box2Origin.z * box2ToBox1[ 1 ][ 1 ] ) + tolerance;
        if ( FloatBits( originProjection ) > FloatBits( boxProjectionSum ) )
        {
            MatrixGetColumn( box2ToWorld , 1 , tmp );
            CrossProduct( worldToBox1[ 0 ] , tmp.Base() , pPlane->normal.Base() );
            return true;
        }
    }

    // b1e1 x b2e3
    if ( absBox2ToBox1[ 0 ][ 2 ] < 1.0f - 1e-3f )
    {
        boxProjectionSum =
            box1Size.y * absBox2ToBox1[ 2 ][ 2 ] + box1Size.z * absBox2ToBox1[ 1 ][ 2 ] +
            box2Size.x * absBox2ToBox1[ 0 ][ 1 ] + box2Size.y * absBox2ToBox1[ 0 ][ 0 ];
        originProjection = FloatMakePositive( -box2Origin.y * box2ToBox1[ 2 ][ 2 ] + box2Origin.z * box2ToBox1[ 1 ][ 2 ] ) + tolerance;
        if ( FloatBits( originProjection ) > FloatBits( boxProjectionSum ) )
        {
            MatrixGetColumn( box2ToWorld , 2 , tmp );
            CrossProduct( worldToBox1[ 0 ] , tmp.Base() , pPlane->normal.Base() );
            return true;
        }
    }

    // b1e2 x b2e1
    if ( absBox2ToBox1[ 1 ][ 0 ] < 1.0f - 1e-3f )
    {
        boxProjectionSum =
            box1Size.x * absBox2ToBox1[ 2 ][ 0 ] + box1Size.z * absBox2ToBox1[ 0 ][ 0 ] +
            box2Size.y * absBox2ToBox1[ 1 ][ 2 ] + box2Size.z * absBox2ToBox1[ 1 ][ 1 ];
        originProjection = FloatMakePositive( box2Origin.x * box2ToBox1[ 2 ][ 0 ] - box2Origin.z * box2ToBox1[ 0 ][ 0 ] ) + tolerance;
        if ( FloatBits( originProjection ) > FloatBits( boxProjectionSum ) )
        {
            MatrixGetColumn( box2ToWorld , 0 , tmp );
            CrossProduct( worldToBox1[ 1 ] , tmp.Base() , pPlane->normal.Base() );
            return true;
        }
    }

    // b1e2 x b2e2
    if ( absBox2ToBox1[ 1 ][ 1 ] < 1.0f - 1e-3f )
    {
        boxProjectionSum =
            box1Size.x * absBox2ToBox1[ 2 ][ 1 ] + box1Size.z * absBox2ToBox1[ 0 ][ 1 ] +
            box2Size.x * absBox2ToBox1[ 1 ][ 2 ] + box2Size.z * absBox2ToBox1[ 1 ][ 0 ];
        originProjection = FloatMakePositive( box2Origin.x * box2ToBox1[ 2 ][ 1 ] - box2Origin.z * box2ToBox1[ 0 ][ 1 ] ) + tolerance;
        if ( FloatBits( originProjection ) > FloatBits( boxProjectionSum ) )
        {
            MatrixGetColumn( box2ToWorld , 1 , tmp );
            CrossProduct( worldToBox1[ 1 ] , tmp.Base() , pPlane->normal.Base() );
            return true;
        }
    }

    // b1e2 x b2e3
    if ( absBox2ToBox1[ 1 ][ 2 ] < 1.0f - 1e-3f )
    {
        boxProjectionSum =
            box1Size.x * absBox2ToBox1[ 2 ][ 2 ] + box1Size.z * absBox2ToBox1[ 0 ][ 2 ] +
            box2Size.x * absBox2ToBox1[ 1 ][ 1 ] + box2Size.y * absBox2ToBox1[ 1 ][ 0 ];
        originProjection = FloatMakePositive( box2Origin.x * box2ToBox1[ 2 ][ 2 ] - box2Origin.z * box2ToBox1[ 0 ][ 2 ] ) + tolerance;
        if ( FloatBits( originProjection ) > FloatBits( boxProjectionSum ) )
        {
            MatrixGetColumn( box2ToWorld , 2 , tmp );
            CrossProduct( worldToBox1[ 1 ] , tmp.Base() , pPlane->normal.Base() );
            return true;
        }
    }

    // b1e3 x b2e1
    if ( absBox2ToBox1[ 2 ][ 0 ] < 1.0f - 1e-3f )
    {
        boxProjectionSum =
            box1Size.x * absBox2ToBox1[ 1 ][ 0 ] + box1Size.y * absBox2ToBox1[ 0 ][ 0 ] +
            box2Size.y * absBox2ToBox1[ 2 ][ 2 ] + box2Size.z * absBox2ToBox1[ 2 ][ 1 ];
        originProjection = FloatMakePositive( -box2Origin.x * box2ToBox1[ 1 ][ 0 ] + box2Origin.y * box2ToBox1[ 0 ][ 0 ] ) + tolerance;
        if ( FloatBits( originProjection ) > FloatBits( boxProjectionSum ) )
        {
            MatrixGetColumn( box2ToWorld , 0 , tmp );
            CrossProduct( worldToBox1[ 2 ] , tmp.Base() , pPlane->normal.Base() );
            return true;
        }
    }

    // b1e3 x b2e2
    if ( absBox2ToBox1[ 2 ][ 1 ] < 1.0f - 1e-3f )
    {
        boxProjectionSum =
            box1Size.x * absBox2ToBox1[ 1 ][ 1 ] + box1Size.y * absBox2ToBox1[ 0 ][ 1 ] +
            box2Size.x * absBox2ToBox1[ 2 ][ 2 ] + box2Size.z * absBox2ToBox1[ 2 ][ 0 ];
        originProjection = FloatMakePositive( -box2Origin.x * box2ToBox1[ 1 ][ 1 ] + box2Origin.y * box2ToBox1[ 0 ][ 1 ] ) + tolerance;
        if ( FloatBits( originProjection ) > FloatBits( boxProjectionSum ) )
        {
            MatrixGetColumn( box2ToWorld , 1 , tmp );
            CrossProduct( worldToBox1[ 2 ] , tmp.Base() , pPlane->normal.Base() );
            return true;
        }
    }

    // b1e3 x b2e3
    if ( absBox2ToBox1[ 2 ][ 2 ] < 1.0f - 1e-3f )
    {
        boxProjectionSum =
            box1Size.x * absBox2ToBox1[ 1 ][ 2 ] + box1Size.y * absBox2ToBox1[ 0 ][ 2 ] +
            box2Size.x * absBox2ToBox1[ 2 ][ 1 ] + box2Size.y * absBox2ToBox1[ 2 ][ 0 ];
        originProjection = FloatMakePositive( -box2Origin.x * box2ToBox1[ 1 ][ 2 ] + box2Origin.y * box2ToBox1[ 0 ][ 2 ] ) + tolerance;
        if ( FloatBits( originProjection ) > FloatBits( boxProjectionSum ) )
        {
            MatrixGetColumn( box2ToWorld , 2 , tmp );
            CrossProduct( worldToBox1[ 2 ] , tmp.Base() , pPlane->normal.Base() );
            return true;
        }
    }
    return false;
}

//-----------------------------------------------------------------------------
// Compute a matrix that has the correct orientation but which has an origin at
// the center of the bounds
//-----------------------------------------------------------------------------
static void ComputeCenterMatrix( const Vector& origin , const Angle& angles ,
                                 const Vector& mins , const Vector& maxs , Matrix3x4& matrix )
{
    Vector centroid;
    VectorAdd( mins , maxs , centroid );
    centroid *= 0.5f;
    AngleMatrix( angles , matrix );

    Vector worldCentroid;
    VectorRotate( centroid , matrix , worldCentroid );
    worldCentroid += origin;
    MatrixSetColumn( worldCentroid , 3 , matrix );
}

void AngleIMatrix( const Angle& angles , Matrix3x4& matrix )
{
    Assert( s_bMathlibInitialized );
    float		sr , sp , sy , cr , cp , cy;

    SinCos( DEGTORAD( angles[ 1 ] ) , &sy , &cy );
    SinCos( DEGTORAD( angles[ 0 ] ) , &sp , &cp );
    SinCos( DEGTORAD( angles[ 2 ] ) , &sr , &cr );

    // matrix = (YAW * PITCH) * ROLL
    matrix[ 0 ][ 0 ] = cp * cy;
    matrix[ 0 ][ 1 ] = cp * sy;
    matrix[ 0 ][ 2 ] = -sp;
    matrix[ 1 ][ 0 ] = sr * sp*cy + cr * -sy;
    matrix[ 1 ][ 1 ] = sr * sp*sy + cr * cy;
    matrix[ 1 ][ 2 ] = sr * cp;
    matrix[ 2 ][ 0 ] = ( cr*sp*cy + -sr * -sy );
    matrix[ 2 ][ 1 ] = ( cr*sp*sy + -sr * cy );
    matrix[ 2 ][ 2 ] = cr * cp;
    matrix[ 0 ][ 3 ] = 0.f;
    matrix[ 1 ][ 3 ] = 0.f;
    matrix[ 2 ][ 3 ] = 0.f;
}

void AngleIMatrix( const Angle &angles , const Vector &position , Matrix3x4 &mat )
{
    AngleIMatrix( angles , mat );

    Vector vecTranslation;
    VectorRotate( position , mat , vecTranslation );
    vecTranslation *= -1.0f;
    MatrixSetColumn( vecTranslation , 3 , mat );
}

static void ComputeCenterIMatrix( const Vector& origin , const Angle& angles ,
                                  const Vector& mins , const Vector& maxs , Matrix3x4& matrix )
{
    Vector centroid;
    VectorAdd( mins , maxs , centroid );
    centroid *= -0.5f;
    AngleIMatrix( angles , matrix );

    // For the translational component here, note that the origin in world space
    // is T = R * C + O, (R = rotation matrix, C = centroid in local space, O = origin in world space)
    // The IMatrix translation = - transpose(R) * T = -C - transpose(R) * 0
    Vector localOrigin;
    VectorRotate( origin , matrix , localOrigin );
    centroid -= localOrigin;
    MatrixSetColumn( centroid , 3 , matrix );
}

//-----------------------------------------------------------------------------
// Compute a separating plane between two boxes (expensive!)
// Returns false if no separating plane exists
//-----------------------------------------------------------------------------
bool ComputeSeparatingPlane( const Vector& org1 , const Angle& angles1 , const Vector& min1 , const Vector& max1 ,
                             const Vector& org2 , const Angle& angles2 , const Vector& min2 , const Vector& max2 ,
                             float tolerance , cplane_t* pPlane )
{
    Matrix3x4 worldToBox1 , box2ToWorld;
    ComputeCenterIMatrix( org1 , angles1 , min1 , max1 , worldToBox1 );
    ComputeCenterMatrix( org2 , angles2 , min2 , max2 , box2ToWorld );

    // Then compute the size of the two boxes
    Vector box1Size , box2Size;
    VectorSubtract( max1 , min1 , box1Size );
    VectorSubtract( max2 , min2 , box2Size );
    box1Size *= 0.5f;
    box2Size *= 0.5f;

    return ComputeSeparatingPlane( worldToBox1 , box2ToWorld , box1Size , box2Size , tolerance , pPlane );
}

bool IsOBBIntersectingOBB( const Vector &vecOrigin1 , const Angle &vecAngles1 , const Vector& boxMin1 , const Vector& boxMax1 ,
                           const Vector &vecOrigin2 , const Angle &vecAngles2 , const Vector& boxMin2 , const Vector& boxMax2 , float flTolerance )
{
    cplane_t plane;
    return !ComputeSeparatingPlane( vecOrigin1 , vecAngles1 , boxMin1 , boxMax1 ,
                                    vecOrigin2 , vecAngles2 , boxMin2 , boxMax2 , flTolerance , &plane );
}

//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection

bool RayIntersectBox( const Vector& origin , const Vector& dir , const Vector& min , const Vector& max )
{
    Real tmin , tmax , tymin , tymax , tzmin , tzmax;

    if ( dir.x >= 0 )
    {
        tmin = ( min.x - origin.x ) / dir.x;
        tmax = ( max.x - origin.x ) / dir.x;
    }
    else
    {
        tmin = ( max.x - origin.x ) / dir.x;
        tmax = ( min.x - origin.x ) / dir.x;
    }

    if ( dir.y >= 0 )
    {
        tymin = ( min.y - origin.y ) / dir.y;
        tymax = ( max.y - origin.y ) / dir.y;
    }
    else
    {
        tymin = ( max.y - origin.y ) / dir.y;
        tymax = ( min.y - origin.y ) / dir.y;
    }

    if ( tmin > tymax || tymin > tmax )
        return false;

    if ( tymin > tmin )
        tmin = tymin;

    if ( tymax < tmax )
        tmax = tymax;

    if ( dir.z >= 0 )
    {
        tzmin = ( min.z - origin.z ) / dir.z;
        tzmax = ( max.z - origin.z ) / dir.z;
    }
    else
    {
        tzmin = ( max.z - origin.z ) / dir.z;
        tzmax = ( min.z - origin.z ) / dir.z;
    }

    if ( tmin > tzmax || tzmin > tmax )
        return false;

    //behind us
    if ( tmin < 0 || tmax < 0 )
        return false;

    return true;
}

// http://geomalgorithms.com/a07-_distance.html

#define SMALL_NUM   0.00000001 // anything that avoids division overflow
// dot product (3D) which allows vector operations in arguments
#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)
#define norm(v)    sqrt(dot(v,v))  // norm = length of  vector
#define d(u,v)     norm(u-v)        // distance = norm of difference
#define abs(x)     ((x) >= 0 ? (x) : -(x))   //  absolute value

float dist_Segment_to_Segment( Vector& s1 , Vector& s2 , Vector& k1 , Vector& k2 )
{
    Vector   u = s2 - s1;
    Vector   v = k2 - k1;
    Vector   w = s1 - k1;
    float    a = dot( u , u );
    float    b = dot( u , v );
    float    c = dot( v , v );
    float    d = dot( u , w );
    float    e = dot( v , w );
    float    D = a * c - b * b;
    float    sc , sN , sD = D;
    float    tc , tN , tD = D;

    if ( D < SMALL_NUM )
    {
        sN = 0.0;
        sD = 1.0;
        tN = e;
        tD = c;
    }
    else
    {
        sN = ( b*e - c * d );
        tN = ( a*e - b * d );
        if ( sN < 0.0 )
        {
            sN = 0.0;
            tN = e;
            tD = c;
        }
        else if ( sN > sD )
        {
            sN = sD;
            tN = e + b;
            tD = c;
        }
    }

    if ( tN < 0.0 )
    {
        tN = 0.0;

        if ( -d < 0.0 )
            sN = 0.0;
        else if ( -d > a )
            sN = sD;
        else
        {
            sN = -d;
            sD = a;
        }
    }
    else if ( tN > tD )
    {
        tN = tD;

        if ( ( -d + b ) < 0.0 )
            sN = 0;
        else if ( ( -d + b ) > a )
            sN = sD;
        else
        {
            sN = ( -d + b );
            sD = a;
        }
    }

    sc = ( abs( sN ) < SMALL_NUM ? ( Real )0.0 : sN / sD );
    tc = ( abs( tN ) < SMALL_NUM ? ( Real )0.0 : tN / tD );

    Vector  dP = w + ( u * sc ) - ( v * tc );

    return dP.Normalize();
}

bool RayIntersectCapsule( Vector eyePos , Vector myDir , Vector capsuleA , Vector capsuleB , float radius )
{
    auto dist = dist_Segment_to_Segment( eyePos , myDir , capsuleA , capsuleB );

    return dist < radius;
}