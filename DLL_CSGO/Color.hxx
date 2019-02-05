#ifndef COLOR
#define COLOR
#pragma once

typedef struct color32_s
{
    bool operator!=( const struct color32_s &other ) const;
    byte r , g , b , a;

    // assign and copy by using the whole register rather
    // than byte-by-byte copy. (No, the compiler is not
    // smart enough to do this for you. /FAcs if you
    // don't believe me.)
    inline unsigned* asInt( void )
    {
        return reinterpret_cast< unsigned* >( this );
    }
    inline unsigned long* asDword( void )
    {
        return reinterpret_cast< unsigned long* >( this );
    }
    inline const unsigned* asInt( void ) const
    {
        return reinterpret_cast< const unsigned* >( this );
    }
// This thing is in a union elsewhere, and union members can't have assignment
// operators, so you have to explicitly assign using this, or be slow. SUCK.
    inline void Copy( const color32_s &rhs )
    {
        *asInt() = *rhs.asInt();
    }
} color32;

class Color
{
public:
    // constructors
    Color()
    {
        *( ( int * ) this ) = 0;
    }
    Color( int color32 )
    {
        *( ( int * ) this ) = color32;
    }
    Color( int _r , int _g , int _b )
    {
        SetColor( _r , _g , _b , 255 );
    }
    Color( int _r , int _g , int _b , int _a )
    {
        SetColor( _r , _g , _b , _a );
    }

    // set the color
    // r - red component (0-255)
    // g - green component (0-255)
    // b - blue component (0-255)
    // a - alpha component, controls transparency (0 - transparent, 255 - opaque);
    void SetColor( int _r , int _g , int _b , int _a = 255 )
    {
        _color[ 0 ] = ( unsigned char ) _r;
        _color[ 1 ] = ( unsigned char ) _g;
        _color[ 2 ] = ( unsigned char ) _b;
        _color[ 3 ] = ( unsigned char ) _a;
    }

    void GetColor( int &_r , int &_g , int &_b , int &_a ) const
    {
        _r = _color[ 0 ];
        _g = _color[ 1 ];
        _b = _color[ 2 ];
        _a = _color[ 3 ];
    }

    void SetRawColor( int color32 )
    {
        *( ( int* ) this ) = color32;
    }

    int GetRawColor() const
    {
        return *( ( int* ) this );
    }

    int GetD3DColor() const
    {
        return ( ( int ) ( ( ( ( _color[ 3 ] ) & 0xff ) << 24 ) | ( ( ( _color[ 0 ] ) & 0xff ) << 16 ) | ( ( ( _color[ 1 ] ) & 0xff ) << 8 ) | ( ( _color[ 2 ] ) & 0xff ) ) );
    }

    inline unsigned char r() const
    {
        return _color[ 0 ];
    }
    inline unsigned char g() const
    {
        return _color[ 1 ];
    }
    inline unsigned char b() const
    {
        return _color[ 2 ];
    }
    inline unsigned char a() const
    {
        return _color[ 3 ];
    }

    inline float rBase() const
    {
        return _color[ 0 ] / 255.0f;
    }
    inline float gBase() const
    {
        return _color[ 1 ] / 255.0f;
    }
    inline float bBase() const
    {
        return _color[ 2 ] / 255.0f;
    }
    inline float aBase() const
    {
        return _color[ 3 ] / 255.0f;
    }

    unsigned char &operator[]( int index )
    {
        return _color[ index ];
    }

    const unsigned char &operator[]( int index ) const
    {
        return _color[ index ];
    }

    bool operator == ( const Color &rhs ) const
    {
        return ( *( ( int * ) this ) == *( ( int * ) &rhs ) );
    }

    bool operator != ( const Color &rhs ) const
    {
        return !( operator==( rhs ) );
    }

    Color &operator=( const Color &rhs )
    {
        SetRawColor( rhs.GetRawColor() );
        return *this;
    }

    Color &operator=( const color32 &rhs )
    {
        _color[ 0 ] = rhs.r;
        _color[ 1 ] = rhs.g;
        _color[ 2 ] = rhs.b;
        _color[ 3 ] = rhs.a;
        return *this;
    }

    color32 ToColor32() const
    {
        color32 newColor;
        newColor.r = _color[ 0 ];
        newColor.g = _color[ 1 ];
        newColor.b = _color[ 2 ];
        newColor.a = _color[ 3 ];
        return newColor;
    }

    float* Base()
    {
        float clr[ 3 ];

        clr[ 0 ] = _color[ 0 ] / 255.0f;
        clr[ 1 ] = _color[ 1 ] / 255.0f;
        clr[ 2 ] = _color[ 2 ] / 255.0f;

        return &clr[ 0 ];
    }

    float Hue() const
    {
        if ( _color[ 0 ] == _color[ 1 ] && _color[ 1 ] == _color[ 2 ] )
        {
            return 0.0f;
        }

        float r = _color[ 0 ] / 255.0f;
        float g = _color[ 1 ] / 255.0f;
        float b = _color[ 2 ] / 255.0f;

        float max = r > g ? r : g > b ? g : b ,
            min = r < g ? r : g < b ? g : b;
        float delta = max - min;
        float hue = 0.0f;

        if ( r == max )
        {
            hue = ( g - b ) / delta;
        }
        else if ( g == max )
        {
            hue = 2 + ( b - r ) / delta;
        }
        else if ( b == max )
        {
            hue = 4 + ( r - g ) / delta;
        }
        hue *= 60;

        if ( hue < 0.0f )
        {
            hue += 360.0f;
        }
        return hue;
    }

    float Saturation() const
    {
        float r = _color[ 0 ] / 255.0f;
        float g = _color[ 1 ] / 255.0f;
        float b = _color[ 2 ] / 255.0f;

        float max = r > g ? r : g > b ? g : b ,
            min = r < g ? r : g < b ? g : b;
        float l , s = 0;

        if ( max != min )
        {
            l = ( max + min ) / 2;
            if ( l <= 0.5f )
                s = ( max - min ) / ( max + min );
            else
                s = ( max - min ) / ( 2 - max - min );
        }
        return s;
    }

    float Brightness() const
    {
        float r = _color[ 0 ] / 255.0f;
        float g = _color[ 1 ] / 255.0f;
        float b = _color[ 2 ] / 255.0f;

        float max = r > g ? r : g > b ? g : b ,
            min = r < g ? r : g < b ? g : b;
        return ( max + min ) / 2;
    }

    Color FromHSB( float hue , float saturation , float brightness )
    {
        float h = hue == 1.0f ? 0 : hue * 6.0f;
        float f = h - ( int ) h;
        float p = brightness * ( 1.0f - saturation );
        float q = brightness * ( 1.0f - saturation * f );
        float t = brightness * ( 1.0f - ( saturation * ( 1.0f - f ) ) );

        if ( h < 1 )
        {
            return Color(
                ( unsigned char ) ( brightness * 255 ) ,
                ( unsigned char ) ( t * 255 ) ,
                ( unsigned char ) ( p * 255 )
            );
        }
        else if ( h < 2 )
        {
            return Color(
                ( unsigned char ) ( q * 255 ) ,
                ( unsigned char ) ( brightness * 255 ) ,
                ( unsigned char ) ( p * 255 )
            );
        }
        else if ( h < 3 )
        {
            return Color(
                ( unsigned char ) ( p * 255 ) ,
                ( unsigned char ) ( brightness * 255 ) ,
                ( unsigned char ) ( t * 255 )
            );
        }
        else if ( h < 4 )
        {
            return Color(
                ( unsigned char ) ( p * 255 ) ,
                ( unsigned char ) ( q * 255 ) ,
                ( unsigned char ) ( brightness * 255 )
            );
        }
        else if ( h < 5 )
        {
            return Color(
                ( unsigned char ) ( t * 255 ) ,
                ( unsigned char ) ( p * 255 ) ,
                ( unsigned char ) ( brightness * 255 )
            );
        }
        else
        {
            return Color(
                ( unsigned char ) ( brightness * 255 ) ,
                ( unsigned char ) ( p * 255 ) ,
                ( unsigned char ) ( q * 255 )
            );
        }
    }

    static Color Red()
    {
        return Color( 255 , 0 , 0 );
    }
    static Color Green()
    {
        return Color( 0 , 255 , 0 );
    }
    static Color Blue()
    {
        return Color( 0 , 0 , 255 );
    }
    static Color LightBlue()
    {
        return Color( 100 , 100 , 255 );
    }
    static Color Grey()
    {
        return Color( 128 , 128 , 128 );
    }
    static Color DarkGrey()
    {
        return Color( 45 , 45 , 45 );
    }
    static Color Black()
    {
        return Color( 0 , 0 , 0 );
    }
    static Color White()
    {
        return Color( 255 , 255 , 255 );
    }
    static Color Purple()
    {
        return Color( 220 , 0 , 220 );
    }

public:
    unsigned char _color[ 4 ];
};

#endif