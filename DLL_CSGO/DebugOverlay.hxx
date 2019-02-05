#ifndef DEBUGOVERLAY
#define DEBUGOVERLAY
#pragma once

class OverlayText_t;

class IVDebugOverlay
{
public:
    virtual void            AddEntityTextOverlay( int ent_index , int line_offset , float duration , int r , int g , int b , int a , const char *format , ... ) = 0;
    virtual void            AddBoxOverlay( const Vector& origin , const Vector& mins , const Vector& max , Angle const& orientation , int r , int g , int b , int a , float duration ) = 0;
    virtual void            AddSphereOverlay( const Vector& vOrigin , float flRadius , int nTheta , int nPhi , int r , int g , int b , int a , float flDuration ) = 0;
    virtual void            AddTriangleOverlay( const Vector& p1 , const Vector& p2 , const Vector& p3 , int r , int g , int b , int a , bool noDepthTest , float duration ) = 0;
    virtual void            AddLineOverlay( const Vector& origin , const Vector& dest , int r , int g , int b , bool noDepthTest , float duration ) = 0;
    virtual void            AddTextOverlay( const Vector& origin , float duration , const char *format , ... ) = 0;
    virtual void            AddTextOverlay( const Vector& origin , int line_offset , float duration , const char *format , ... ) = 0;
    virtual void            AddScreenTextOverlay( float flXPos , float flYPos , float flDuration , int r , int g , int b , int a , const char *text ) = 0;
    virtual void            AddSweptBoxOverlay( const Vector& start , const Vector& end , const Vector& mins , const Vector& max , const Angle & angles , int r , int g , int b , int a , float flDuration ) = 0;
    virtual void            AddGridOverlay( const Vector& origin ) = 0;
    virtual void            AddCoordFrameOverlay( const Matrix3x4& frame , float flScale , int vColorTable[ 3 ][ 3 ] = NULL ) = 0;
    virtual int             ScreenPosition( const Vector& point , Vector& screen ) = 0;
    virtual int             ScreenPosition( float flXPos , float flYPos , Vector& screen ) = 0;
    virtual OverlayText_t*  GetFirst( void ) = 0;
    virtual OverlayText_t*  GetNext( OverlayText_t *current ) = 0;
    virtual void            ClearDeadOverlays( void ) = 0;
    virtual void            ClearAllOverlays( void ) = 0;
    virtual void            AddTextOverlayRGB( const Vector& origin , int line_offset , float duration , float r , float g , float b , float alpha , const char *format , ... ) = 0;
    virtual void            AddTextOverlayRGB( const Vector& origin , int line_offset , float duration , int r , int g , int b , int a , const char *format , ... ) = 0;
    virtual void            AddLineOverlayAlpha( const Vector& origin , const Vector& dest , int r , int g , int b , int a , bool noDepthTest , float duration ) = 0;
    virtual void            AddBoxOverlay2( const Vector& origin , const Vector& mins , const Vector& max , Angle const& orientation , const uint8_t* faceColor , const uint8_t* edgeColor , float duration ) = 0;
    virtual void			AddLineOverlay( const Vector& origin , const Vector& dest , int r , int g , int b , int a , float , float ) = 0;
    virtual void            PurgeTextOverlays() = 0;
    void AddCapsuleOverlay( Vector& mins , Vector& maxs , float pillradius , int r , int g , int b , int a , float duration )
    {
        ( ( void( __thiscall* )( void* , Vector& , Vector& , float& , int , int , int , int , float ) ) _VTable( this )[ 24 ] )( this , mins , maxs , pillradius , r , g , b , a , duration );
    }
};

#endif