#ifndef PANEL
#define PANEL
#pragma once

#ifdef CreateFont
#undef CreateFont
#endif

enum ImageFormat;

// returns true if the surface supports minimize & maximize capabilities
// Numbered this way to prevent interface change in surface.
enum FontFeature_t
{
    FONT_FEATURE_ANTIALIASED_FONTS = 1 ,
    FONT_FEATURE_DROPSHADOW_FONTS = 2 ,
    FONT_FEATURE_OUTLINE_FONTS = 6 ,
};

// adds to the font
enum FontFlags_t
{
    FONTFLAG_NONE ,
    FONTFLAG_ITALIC = 0x001 ,
    FONTFLAG_UNDERLINE = 0x002 ,
    FONTFLAG_STRIKEOUT = 0x004 ,
    FONTFLAG_SYMBOL = 0x008 ,
    FONTFLAG_ANTIALIAS = 0x010 ,
    FONTFLAG_GAUSSIANBLUR = 0x020 ,
    FONTFLAG_ROTARY = 0x040 ,
    FONTFLAG_DROPSHADOW = 0x080 ,
    FONTFLAG_ADDITIVE = 0x100 ,
    FONTFLAG_OUTLINE = 0x200 ,
    FONTFLAG_CUSTOM = 0x400 ,		// custom generated font - never fall back to asian compatibility mode
    FONTFLAG_BITMAP = 0x800 ,		// compiled bitmap font - no fallbacks
};

enum FontDrawType_t
{
    // Use the "additive" value from the scheme file
    FONT_DRAW_DEFAULT = 0 ,

    // Overrides
    FONT_DRAW_NONADDITIVE ,
    FONT_DRAW_ADDITIVE ,

    FONT_DRAW_TYPE_COUNT = 2 ,
};

struct FontVertex_t
{
    FontVertex_t()
    {}
    FontVertex_t( const Vector2D &pos , const Vector2D &coord = Vector2D( 0 , 0 ) )
    {
        m_Position = pos;
        m_TexCoord = coord;
    }
    void Init( const Vector2D &pos , const Vector2D &coord = Vector2D( 0 , 0 ) )
    {
        m_Position = pos;
        m_TexCoord = coord;
    }

    Vector2D m_Position;
    Vector2D m_TexCoord;
};

typedef unsigned long FontHandle_t;
typedef unsigned long HCursor;
typedef unsigned long HTexture;

struct FontCharRenderInfo
{
    // Text pos
    int				x , y;
    // Top left and bottom right
    // This is now a pointer to an array maintained by the surface, to avoid copying the data on the 360
    FontVertex_t	*verts;
    int				textureId;
    int				abcA;
    int				abcB;
    int				abcC;
    int				fontTall;
    FontHandle_t	currentFont;
    // In:
    FontDrawType_t	drawType;
    wchar_t			ch;

    // Out
    bool			valid;
    // In/Out (true by default)
    bool			shouldclip;
};

struct IntRect
{
    int x0;
    int y0;
    int x1;
    int y1;
};

struct DrawTexturedRectParms_t
{
    DrawTexturedRectParms_t()
    {
        s0 = t0 = 0;
        s1 = t1 = 1.0f;
        alpha_ul = alpha_ur = alpha_lr = alpha_ll = 255;
        angle = 0;
    }

    int x0;
    int	y0;
    int x1;
    int y1;

    float s0;
    float t0;
    float s1;
    float t1;

    unsigned char alpha_ul;
    unsigned char alpha_ur;
    unsigned char alpha_lr;
    unsigned char alpha_ll;

    float angle;
};

typedef FontHandle_t HFont;
typedef FontVertex_t Vertex_t;

//-----------------------------------------------------------------------------
// Purpose: Interface from vgui panels -> Client panels
//			This interface cannot be changed without rebuilding all vgui projects
//			Primarily this interface handles dispatching messages from core vgui to controls
//			The additional functions are all their for debugging or optimization reasons
//			To add to this later, use QueryInterface() to see if they support new interfaces
//-----------------------------------------------------------------------------
class IClientPanel
{
public:
    virtual VPANEL GetVPanel() = 0;

    // straight interface to Panel functions
    virtual void Think() = 0;
    virtual void PerformApplySchemeSettings() = 0;
    virtual void PaintTraverse( bool forceRepaint , bool allowForce ) = 0;
    virtual void Repaint() = 0;
    virtual VPANEL IsWithinTraverse( int x , int y , bool traversePopups ) = 0;
    virtual void GetInset( int &top , int &left , int &right , int &bottom ) = 0;
    virtual void GetClipRect( int &x0 , int &y0 , int &x1 , int &y1 ) = 0;
    virtual void OnChildAdded( VPANEL child ) = 0;
    virtual void OnSizeChanged( int newWide , int newTall ) = 0;

    virtual void InternalFocusChanged( bool lost ) = 0;
    virtual bool RequestInfo( KeyValues *outputData ) = 0;
    virtual void RequestFocus( int direction ) = 0;
    virtual bool RequestFocusPrev( VPANEL existingPanel ) = 0;
    virtual bool RequestFocusNext( VPANEL existingPanel ) = 0;
    virtual void OnMessage( const KeyValues *params , VPANEL ifromPanel ) = 0;
    virtual VPANEL GetCurrentKeyFocus() = 0;
    virtual int GetTabPosition() = 0;

    // for debugging purposes
    virtual const char *GetName() = 0;
    virtual const char *_GetClassName() = 0;

    // get scheme handles from panels
    virtual HScheme GetScheme() = 0;
    // gets whether or not this panel should scale with screen resolution
    virtual bool IsProportional() = 0;
    // auto-deletion
    virtual bool IsAutoDeleteSet() = 0;
    // deletes this
    virtual void DeletePanel() = 0;

    // interfaces
    virtual void *QueryInterface( EInterfaceID id ) = 0;

    // returns a pointer to the vgui controls baseclass Panel *
    virtual Pointer GetPanel() = 0;

    // returns the name of the module this panel is part of
    virtual const char *GetModuleName() = 0;

    virtual void OnTick() = 0;
};

class IPanel : public IBaseInterface
{
public:
    virtual void Init( VPANEL vguiPanel , IClientPanel *panel ) = 0;

    // methods
    virtual void SetPos( VPANEL vguiPanel , int x , int y ) = 0;
    virtual void GetPos( VPANEL vguiPanel , int &x , int &y ) = 0;
    virtual void SetSize( VPANEL vguiPanel , int wide , int tall ) = 0;
    virtual void GetSize( VPANEL vguiPanel , int &wide , int &tall ) = 0;
    virtual void SetMinimumSize( VPANEL vguiPanel , int wide , int tall ) = 0;
    virtual void GetMinimumSize( VPANEL vguiPanel , int &wide , int &tall ) = 0;
    virtual void SetZPos( VPANEL vguiPanel , int z ) = 0;
    virtual int  GetZPos( VPANEL vguiPanel ) = 0;

    virtual void GetAbsPos( VPANEL vguiPanel , int &x , int &y ) = 0;
    virtual void GetClipRect( VPANEL vguiPanel , int &x0 , int &y0 , int &x1 , int &y1 ) = 0;
    virtual void SetInset( VPANEL vguiPanel , int left , int top , int right , int bottom ) = 0;
    virtual void GetInset( VPANEL vguiPanel , int &left , int &top , int &right , int &bottom ) = 0;

    virtual void SetVisible( VPANEL vguiPanel , bool state ) = 0;
    virtual bool IsVisible( VPANEL vguiPanel ) = 0;
    virtual void SetParent( VPANEL vguiPanel , VPANEL newParent ) = 0;
    virtual int GetChildCount( VPANEL vguiPanel ) = 0;
    virtual VPANEL GetChild( VPANEL vguiPanel , int index ) = 0;
    virtual CUtlVector< VPANEL > &GetChildren( VPANEL vguiPanel ) = 0;
    virtual VPANEL GetParent( VPANEL vguiPanel ) = 0;
    virtual void MoveToFront( VPANEL vguiPanel ) = 0;
    virtual void MoveToBack( VPANEL vguiPanel ) = 0;
    virtual bool HasParent( VPANEL vguiPanel , VPANEL potentialParent ) = 0;
    virtual bool IsPopup( VPANEL vguiPanel ) = 0;
    virtual void SetPopup( VPANEL vguiPanel , bool state ) = 0;
    virtual bool IsFullyVisible( VPANEL vguiPanel ) = 0;

    // gets the scheme this panel uses
    virtual HScheme GetScheme( VPANEL vguiPanel ) = 0;
    // gets whether or not this panel should scale with screen resolution
    virtual bool IsProportional( VPANEL vguiPanel ) = 0;
    // returns true if auto-deletion flag is set
    virtual bool IsAutoDeleteSet( VPANEL vguiPanel ) = 0;
    // deletes the Panel * associated with the vpanel
    virtual void DeletePanel( VPANEL vguiPanel ) = 0;

    // input interest
    virtual void SetKeyBoardInputEnabled( VPANEL vguiPanel , bool state ) = 0;
    virtual void SetMouseInputEnabled( VPANEL vguiPanel , bool state ) = 0;
    virtual bool IsKeyBoardInputEnabled( VPANEL vguiPanel ) = 0;
    virtual bool IsMouseInputEnabled( VPANEL vguiPanel ) = 0;

    // calculates the panels current position within the hierarchy
    virtual void Solve( VPANEL vguiPanel ) = 0;

    // gets names of the object (for debugging purposes)
    virtual const char *GetName( VPANEL vguiPanel ) = 0;
    virtual const char *_GetClassName( VPANEL vguiPanel ) = 0;

    // delivers a message to the panel
    virtual void _SendMessage( VPANEL vguiPanel , KeyValues *params , VPANEL ifromPanel ) = 0;

    // these pass through to the IClientPanel
    virtual void Think( VPANEL vguiPanel ) = 0;
    virtual void PerformApplySchemeSettings( VPANEL vguiPanel ) = 0;
    virtual void PaintTraverse( VPANEL vguiPanel , bool forceRepaint , bool allowForce = true ) = 0;
    virtual void Repaint( VPANEL vguiPanel ) = 0;
    virtual VPANEL IsWithinTraverse( VPANEL vguiPanel , int x , int y , bool traversePopups ) = 0;
    virtual void OnChildAdded( VPANEL vguiPanel , VPANEL child ) = 0;
    virtual void OnSizeChanged( VPANEL vguiPanel , int newWide , int newTall ) = 0;

    virtual void InternalFocusChanged( VPANEL vguiPanel , bool lost ) = 0;
    virtual bool RequestInfo( VPANEL vguiPanel , KeyValues *outputData ) = 0;
    virtual void RequestFocus( VPANEL vguiPanel , int direction = 0 ) = 0;
    virtual bool RequestFocusPrev( VPANEL vguiPanel , VPANEL existingPanel ) = 0;
    virtual bool RequestFocusNext( VPANEL vguiPanel , VPANEL existingPanel ) = 0;
    virtual VPANEL GetCurrentKeyFocus( VPANEL vguiPanel ) = 0;
    virtual int GetTabPosition( VPANEL vguiPanel ) = 0;

    // used by ISurface to store platform-specific data
    virtual SurfacePlat *Plat( VPANEL vguiPanel ) = 0;
    virtual void SetPlat( VPANEL vguiPanel , SurfacePlat *Plat ) = 0;

    // returns a pointer to the vgui controls baseclass Panel *
    // destinationModule needs to be passed in to verify that the returned Panel * is from the same module
    // it must be from the same module since Panel * vtbl may be different in each module
    virtual Pointer GetPanel( VPANEL vguiPanel , const char *destinationModule ) = 0;

    virtual bool IsEnabled( VPANEL vguiPanel ) = 0;
    virtual void SetEnabled( VPANEL vguiPanel , bool state ) = 0;

    // Used by the drag/drop manager to always draw on top
    virtual bool IsTopmostPopup( VPANEL vguiPanel ) = 0;
    virtual void SetTopmostPopup( VPANEL vguiPanel , bool state ) = 0;

    virtual void SetMessageContextId( VPANEL vguiPanel , int nContextId ) = 0;
    virtual int GetMessageContextId( VPANEL vguiPanel ) = 0;

    virtual const DmxElementUnpackStructure_t *GetUnpackStructure( VPANEL vguiPanel ) const = 0;
    virtual void OnUnserialized( VPANEL vguiPanel , CDmxElement *pElement ) = 0;

    // sibling pins
    virtual void SetSiblingPin( VPANEL vguiPanel , VPANEL newSibling , byte iMyCornerToPin = 0 , byte iSiblingCornerToPinTo = 0 ) = 0;
};

//-----------------------------------------------------------------------------
// Purpose: Wraps contextless windows system functions
//-----------------------------------------------------------------------------
class ISurface : public IAppSystem
{
public:
    // frame
    virtual void RunFrame() = 0;

    // hierarchy root
    virtual VPANEL GetEmbeddedPanel() = 0;
    virtual void SetEmbeddedPanel( VPANEL pPanel ) = 0;

    // drawing context
    virtual void PushMakeCurrent( VPANEL panel , bool useInsets ) = 0;
    virtual void PopMakeCurrent( VPANEL panel ) = 0;

    // rendering functions
    virtual void DrawSetColor( int r , int g , int b , int a ) = 0;
    virtual void DrawSetColor( Color col ) = 0;

    virtual void DrawFilledRect( int x0 , int y0 , int x1 , int y1 ) = 0;
    virtual void DrawFilledRectArray( IntRect *pRects , int numRects ) = 0;
    virtual void DrawOutlinedRect( int x0 , int y0 , int x1 , int y1 ) = 0;

    virtual void DrawLine( int x0 , int y0 , int x1 , int y1 ) = 0;
    virtual void DrawPolyLine( int *px , int *py , int numPoints ) = 0;

    virtual void DrawSetApparentDepth( float f ) = 0;
    virtual void DrawClearApparentDepth( void ) = 0;

    virtual void DrawSetTextFont( HFont font ) = 0;
    virtual void DrawSetTextColor( int r , int g , int b , int a ) = 0;
    virtual void DrawSetTextColor( Color col ) = 0;
    virtual void DrawSetTextPos( int x , int y ) = 0;
    virtual void DrawGetTextPos( int& x , int& y ) = 0;
    virtual void DrawPrintText( const wchar_t *text , int textLen , FontDrawType_t drawType = FONT_DRAW_DEFAULT ) = 0;
    virtual void DrawUnicodeChar( wchar_t wch , FontDrawType_t drawType = FONT_DRAW_DEFAULT ) = 0;

    virtual void DrawFlushText() = 0;		// flushes any buffered text (for rendering optimizations)
    virtual Pointer CreateHTMLWindow( Pointer events , VPANEL context ) = 0;
    virtual void PaintHTMLWindow( Pointer htmlwin ) = 0;
    virtual void DeleteHTMLWindow( Pointer htmlwin ) = 0;

    virtual int	 DrawGetTextureId( char const *filename ) = 0;
    virtual bool DrawGetTextureFile( int id , char *filename , int maxlen ) = 0;
    virtual void DrawSetTextureFile( int id , const char *filename , int hardwareFilter , bool forceReload ) = 0;
    virtual void DrawSetTextureRGBA( int id , const unsigned char *rgba , int wide , int tall ) = 0;
    virtual void DrawSetTexture( int id ) = 0;
    virtual void DeleteTextureByID( int id ) = 0;
    virtual void DrawGetTextureSize( int id , int &wide , int &tall ) = 0;
    virtual void DrawTexturedRect( int x0 , int y0 , int x1 , int y1 ) = 0;
    virtual bool IsTextureIDValid( int id ) = 0;

    virtual int CreateNewTextureID( bool procedural = false ) = 0;

    virtual void GetScreenSize( int &wide , int &tall ) = 0;
    virtual void SetAsTopMost( VPANEL panel , bool state ) = 0;
    virtual void BringToFront( VPANEL panel ) = 0;
    virtual void SetForegroundWindow( VPANEL panel ) = 0;
    virtual void SetPanelVisible( VPANEL panel , bool state ) = 0;
    virtual void SetMinimized( VPANEL panel , bool state ) = 0;
    virtual bool IsMinimized( VPANEL panel ) = 0;
    virtual void FlashWindow( VPANEL panel , bool state ) = 0;
    virtual void SetTitle( VPANEL panel , const wchar_t *title ) = 0;
    virtual void SetAsToolBar( VPANEL panel , bool state ) = 0;		// removes the window's task bar entry (for context menu's, etc.)

                                                                    // windows stuff
    virtual void CreatePopup( VPANEL panel , bool minimised , bool showTaskbarIcon = true , bool disabled = false , bool mouseInput = true , bool kbInput = true ) = 0;
    virtual void SwapBuffers( VPANEL panel ) = 0;
    virtual void Invalidate( VPANEL panel ) = 0;
    virtual void SetCursor( HCursor cursor ) = 0;
    virtual bool IsCursorVisible() = 0;
    virtual void ApplyChanges() = 0;
    virtual bool IsWithin( int x , int y ) = 0;
    virtual bool HasFocus() = 0;

    // returns true if the surface supports minimize & maximize capabilities
    enum SurfaceFeature_t
    {
        ANTIALIASED_FONTS = FONT_FEATURE_ANTIALIASED_FONTS ,
        DROPSHADOW_FONTS = FONT_FEATURE_DROPSHADOW_FONTS ,
        ESCAPE_KEY = 3 ,
        OPENING_NEW_HTML_WINDOWS = 4 ,
        FRAME_MINIMIZE_MAXIMIZE = 5 ,
        OUTLINE_FONTS = FONT_FEATURE_OUTLINE_FONTS ,
        DIRECT_HWND_RENDER = 7 ,
    };
    virtual bool SupportsFeature( SurfaceFeature_t feature ) = 0;

    // restricts what gets drawn to one panel and it's children
    // currently only works in the game
    virtual void RestrictPaintToSinglePanel( VPANEL panel , bool bForceAllowNonModalSurface = false ) = 0;

    // these two functions obselete, use IInput::SetAppModalSurface() instead
    virtual void SetModalPanel( VPANEL ) = 0;
    virtual VPANEL GetModalPanel() = 0;

    virtual void UnlockCursor() = 0;
    virtual void LockCursor() = 0;
    virtual void SetTranslateExtendedKeys( bool state ) = 0;
    virtual VPANEL GetTopmostPopup() = 0;

    // engine-only focus handling (replacing WM_FOCUS windows handling)
    virtual void SetTopLevelFocus( VPANEL panel ) = 0;

    // fonts
    // creates an empty handle to a vgui font.  windows fonts can be add to this via SetFontGlyphSet().
    virtual HFont CreateFont() = 0;

    virtual bool SetFontGlyphSet( HFont font , const char *windowsFontName , int tall , int weight , int blur , int scanlines , int flags , int nRangeMin = 0 , int nRangeMax = 0 ) = 0;

    // adds a custom font file (only supports true type font files (.ttf) for now)
    virtual bool AddCustomFontFile( const char *fontFileName ) = 0;

    // returns the details about the font
    virtual int GetFontTall( HFont font ) = 0;
    virtual int GetFontAscent( HFont font , wchar_t wch ) = 0;
    virtual bool IsFontAdditive( HFont font ) = 0;
    virtual void GetCharABCwide( HFont font , int ch , int &a , int &b , int &c ) = 0;
    virtual int GetCharacterWidth( HFont font , int ch ) = 0;
    virtual void GetTextSize( HFont font , const wchar_t *text , int &wide , int &tall ) = 0;

    // notify icons?!?
    virtual VPANEL GetNotifyPanel() = 0;
    virtual void SetNotifyIcon( VPANEL context , HTexture icon , VPANEL panelToRecvMessages , const char *text ) = 0;

    // plays a sound
    virtual void PlaySound( const char *fileName ) = 0;

    //!! these functions should not be accessed directly, but only through other vgui items
    //!! need to move these to seperate interface
    virtual int GetPopupCount() = 0;
    virtual VPANEL GetPopup( int index ) = 0;
    virtual bool ShouldPaintChildPanel( VPANEL childPanel ) = 0;
    virtual bool RecreateContext( VPANEL panel ) = 0;
    virtual void AddPanel( VPANEL panel ) = 0;
    virtual void ReleasePanel( VPANEL panel ) = 0;
    virtual void MovePopupToFront( VPANEL panel ) = 0;
    virtual void MovePopupToBack( VPANEL panel ) = 0;

    virtual void SolveTraverse( VPANEL panel , bool forceApplySchemeSettings = false ) = 0;
    virtual void PaintTraverse( VPANEL panel ) = 0;

    virtual void EnableMouseCapture( VPANEL panel , bool state ) = 0;

    // returns the size of the workspace
    virtual void GetWorkspaceBounds( int &x , int &y , int &wide , int &tall ) = 0;

    // gets the absolute coordinates of the screen (in windows space)
    virtual void GetAbsoluteWindowBounds( int &x , int &y , int &wide , int &tall ) = 0;

    // gets the base resolution used in proportional mode
    virtual void GetProportionalBase( int &width , int &height ) = 0;

    virtual void CalculateMouseVisible() = 0;
    virtual bool NeedKBInput() = 0;

    virtual bool HasCursorPosFunctions() = 0;
    virtual void SurfaceGetCursorPos( int &x , int &y ) = 0;
    virtual void SurfaceSetCursorPos( int x , int y ) = 0;

    // SRC only functions!!!
    virtual void DrawTexturedLine( const Vertex_t &a , const Vertex_t &b ) = 0;
    virtual void DrawOutlinedCircle( int x , int y , int radius , int segments ) = 0;
    virtual void DrawTexturedPolyLine( const Vertex_t *p , int n ) = 0; // (Note: this connects the first and last points).
    virtual void DrawTexturedSubRect( int x0 , int y0 , int x1 , int y1 , float texs0 , float text0 , float texs1 , float text1 ) = 0;
    virtual void DrawTexturedPolygon( int n , Vertex_t *pVertice , bool bClipVertices = true ) = 0;
    virtual const wchar_t *GetTitle( VPANEL panel ) = 0;
    virtual bool IsCursorLocked( void ) const = 0;
    virtual void SetWorkspaceInsets( int left , int top , int right , int bottom ) = 0;

    // squarish comic book word bubble with pointer, rect params specify the space inside the bubble
    virtual void DrawWordBubble( int x0 , int y0 , int x1 , int y1 , int nBorderThickness , Color rgbaBackground , Color rgbaBorder ,
                                 bool bPointer = false , int nPointerX = 0 , int nPointerY = 0 , int nPointerBaseThickness = 16 ) = 0;

    // Lower level char drawing code, call DrawGet then pass in info to DrawRender
    virtual bool DrawGetUnicodeCharRenderInfo( wchar_t ch , FontCharRenderInfo& info ) = 0;
    virtual void DrawRenderCharFromInfo( const FontCharRenderInfo& info ) = 0;

    // global alpha setting functions
    // affect all subsequent draw calls - shouldn't normally be used directly, only in Panel::PaintTraverse()
    virtual void DrawSetAlphaMultiplier( float alpha /* [0..1] */ ) = 0;
    virtual float DrawGetAlphaMultiplier() = 0;

    // web browser
    virtual void SetAllowHTMLJavaScript( bool state ) = 0;

    // video mode changing
    virtual void OnScreenSizeChanged( int nOldWidth , int nOldHeight ) = 0;

    virtual HCursor CreateCursorFromFile( char const *curOrAniFile , char const *pPathID = 0 ) = 0;

    // create IVguiMatInfo object ( IMaterial wrapper in VguiMatSurface, NULL in CWin32Surface )
    virtual Pointer DrawGetTextureMatInfoFactory( int id ) = 0;

    virtual void PaintTraverseEx( VPANEL panel , bool paintPopups = false ) = 0;

    virtual float GetZPos() const = 0;

    // From the Xbox
    virtual void SetPanelForInput( VPANEL vpanel ) = 0;
    virtual void DrawFilledRectFastFade( int x0 , int y0 , int x1 , int y1 , int fadeStartPt , int fadeEndPt , unsigned int alpha0 , unsigned int alpha1 , bool bHorizontal ) = 0;
    virtual void DrawFilledRectFade( int x0 , int y0 , int x1 , int y1 , unsigned int alpha0 , unsigned int alpha1 , bool bHorizontal ) = 0;
    virtual void DrawSetTextureRGBAEx( int id , const unsigned char *rgba , int wide , int tall , ImageFormat imageFormat ) = 0;
    virtual void DrawSetTextScale( float sx , float sy ) = 0;
    virtual bool SetBitmapFontGlyphSet( HFont font , const char *windowsFontName , float scalex , float scaley , int flags ) = 0;
    // adds a bitmap font file
    virtual bool AddBitmapFontFile( const char *fontFileName ) = 0;
    // sets a symbol for the bitmap font
    virtual void SetBitmapFontName( const char *pName , const char *pFontFilename ) = 0;
    // gets the bitmap font filename
    virtual const char *GetBitmapFontName( const char *pName ) = 0;
    virtual void ClearTemporaryFontCache( void ) = 0;

    virtual Pointer GetIconImageForFullPath( char const *pFullPath ) = 0;
    virtual void DrawUnicodeString( const wchar_t *pwString , FontDrawType_t drawType = FONT_DRAW_DEFAULT ) = 0;
    virtual void PrecacheFontCharacters( HFont font , wchar_t *pCharacters ) = 0;
    // Console-only.  Get the string to use for the current video mode for layout files.
    virtual const char *GetResolutionKey( void ) const = 0;

    virtual const char *GetFontName( HFont font ) = 0;

    virtual bool ForceScreenSizeOverride( bool bState , int wide , int tall ) = 0;
    // LocalToScreen, ParentLocalToScreen fixups for explicit PaintTraverse calls on Panels not at 0, 0 position
    virtual bool ForceScreenPosOffset( bool bState , int x , int y ) = 0;
    virtual void OffsetAbsPos( int &x , int &y ) = 0;

    virtual void SetAbsPosForContext( int id , int x , int y ) = 0;
    virtual void GetAbsPosForContext( int id , int &x , int& y ) = 0;

    // Causes fonts to get reloaded, etc.
    virtual void ResetFontCaches() = 0;

    virtual bool IsScreenSizeOverrideActive( void ) = 0;
    virtual bool IsScreenPosOverrideActive( void ) = 0;

    virtual void DestroyTextureID( int id ) = 0;

    virtual int GetTextureNumFrames( int id ) = 0;
    virtual void DrawSetTextureFrame( int id , int nFrame , unsigned int *pFrameCache ) = 0;

    virtual void GetClipRect( int &x0 , int &y0 , int &x1 , int &y1 ) = 0;
    virtual void SetClipRect( int x0 , int y0 , int x1 , int y1 ) = 0;

    virtual void DrawTexturedRectEx( DrawTexturedRectParms_t *pDrawParms ) = 0;
};

#endif