#ifndef CLIENTDLL
#define CLIENTDLL
#pragma once

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2
#define	IN_LOOKSPIN		(1 << 25)

//-----------------------------------------------------------------------------
// Purpose: The engine reports to the client DLL what stage it's entering so the DLL can latch events
//  and make sure that certain operations only happen during the right stages.
// The value for each stage goes up as you move through the frame so you can check ranges of values
//  and if new stages get added in-between, the range is still valid.
//-----------------------------------------------------------------------------

enum ClientFrameStage_t
{
    FRAME_UNDEFINED = -1 ,			// (haven't run any frames yet)
    FRAME_START ,

    // A network packet is being Recvd
    FRAME_NET_UPDATE_START ,
    // Data has been Recvd and we're going to start calling PostDataUpdate
    FRAME_NET_UPDATE_POSTDATAUPDATE_START ,
    // Data has been Recvd and we've called PostDataUpdate on all data recipients
    FRAME_NET_UPDATE_POSTDATAUPDATE_END ,
    // We've Recvd all packets, we can now do interpolation, prediction, etc..
    FRAME_NET_UPDATE_END ,

    // We're about to start rendering the scene
    FRAME_RENDER_START ,
    // We've finished rendering the scene.
    FRAME_RENDER_END
};

enum SendPropType
{
    DPT_Int = 0 ,
    DPT_Float ,
    DPT_Vector ,
    DPT_VectorXY ,
    DPT_String ,
    DPT_Array ,
    DPT_DataTable ,
    DPT_Int64 ,
    DPT_NUMSendPropTypes
};

//-----------------------------------------------------------------------------
// pStruct = the base structure of the datatable this variable is in (like C_BaseEntity)
// pOut    = the variable that this this proxy represents (like C_BaseEntity::m_SomeValue).
//
// Convert the network-standard-type value in m_Value into your own format in pStruct/pOut.
//-----------------------------------------------------------------------------
typedef void( *RecvVarProxyFn )( const CRecvProxyData *pData , void *pStruct , void *pOut );

// ------------------------------------------------------------------------ //
// ArrayLengthRecvProxies are optionally used to Get the length of the
// incoming array when it changes.
// ------------------------------------------------------------------------ //
typedef void( *ArrayLengthRecvProxyFn )( void *pStruct , int objectID , int currentArrayLength );

// NOTE: DataTable Recv proxies work differently than the other proxies.
// pData points at the object + the recv table's offset.
// pOut should be Set to the location of the object to unpack the data table into.
// If the parent object just contains the child object, the default proxy just does *pOut = pData.
// If the parent object points at the child object, you need to dereference the pointer here.
// NOTE: don't ever return null from a DataTable Recv proxy function. Bad things will happen.
typedef void( *DataTableRecvVarProxyFn )( const RecvProp *pProp , void **pOut , void *pData , int objectID );

typedef void( *EnsureCapacityFn )( void *pVoid , int offsetToUtlVector , int len );
typedef void( *ResizeUtlVectorFn )( void *pVoid , int offsetToUtlVector , int len );

class CRecvPropExtra_UtlVector
{
public:
    DataTableRecvVarProxyFn m_DataTableProxyFn;	// If it's a datatable, then this is the proxy they specified.
    RecvVarProxyFn m_ProxyFn;				// If it's a non-datatable, then this is the proxy they specified.
    ResizeUtlVectorFn m_ResizeFn;			// The function used to resize the CUtlVector.
    EnsureCapacityFn m_EnsureCapacityFn;
    int m_ElementStride;					// Distance between each element in the array.
    int m_Offset;							// Offset of the CUtlVector from its parent structure.
    int m_nMaxElements;						// For debugging...
};

class DVariant
{
public:
    union
    {
        float	  m_Float;
        long	  m_Int;
        char*     m_pString;
        void*     m_pData;
        float	  m_Vector[ 3 ];
        __int64   m_Int64;
    };
    SendPropType  m_Type;
};

class CRecvProxyData
{
public:
    const RecvProp*     m_pRecvProp;        // The property it's receiving.
    DVariant		    m_Value;            // The value given to you to store.
    int				    m_iElement;         // Which array element you're getting.
    int				    m_ObjectID;         // The object being referred to.
};

class RecvProp
{
public:
    const char              *m_pVarName;
    SendPropType			m_RecvType;
    int						m_Flags;
    int						m_StringBufferSize;
    bool					m_bInsideArray;		// Set to true by the engine if this property sits inside an array.

                                                // Extra data that certain special property types bind to the property here.
    const void *m_pExtraData;

    // If this is an array (DPT_Array).
    RecvProp				*m_pArrayProp;
    ArrayLengthRecvProxyFn	m_ArrayLengthProxy;

    RecvVarProxyFn			m_ProxyFn;
    DataTableRecvVarProxyFn	m_DataTableProxyFn;	// For RDT_DataTable.

    RecvTable				*m_pDataTable;		// For RDT_DataTable.
    int						m_Offset;

    int						m_ElementStride;
    int						m_nElements;

    // If it's one of the numbered "000", "001", etc properties in an array, then
    // these can be used to get its array property name for debugging.
    const char				*m_pParentArrayPropName;
};

class RecvTable
{
public:
    // Properties described in a table.
    RecvProp * m_pProps;
    int				m_nProps;

    // The decoder. NOTE: this covers each RecvTable AND all its children (ie: its children
    // will have their own decoders that include props for all their children).
    Pointer     	m_pDecoder;

    const char		*m_pNetTableName;	// The name matched between client and server.

    bool			m_bInitialized;
    bool			m_bInMainList;
};

class ClientClass
{
public:
    CreateClientClassFn		m_pCreateFn;
    CreateEventFn			m_pCreateEventFn;	// Only called for event objects.
    const char				*m_pNetworkName;
    RecvTable				*m_pRecvTable;
    ClientClass				*m_pNext;
    int						 m_ClassID;	// Managed by the engine.
};

class IBaseClientDLL
{
public:
    // Called once when the client DLL is loaded
    virtual int				Init( CreateInterfaceFn appSystemFactory ,
                                  CreateInterfaceFn physicsFactory ,
                                  CGlobalVarsBase *pGlobals ) = 0;

    virtual void			PostInit() = 0;

    // Called once when the client DLL is being unloaded
    virtual void			Shutdown( void ) = 0;

    // Called once the client is initialized to setup client-side replay interface pointers
    virtual bool			ReplayInit( CreateInterfaceFn replayFactory ) = 0;
    virtual bool			ReplayPostInit() = 0;

    // Called at the start of each level change
    virtual void			LevelInitPreEntity( char const* pMapName ) = 0;
    // Called at the start of a new level, after the entities have been Recvd and created
    virtual void			LevelInitPostEntity() = 0;
    // Called at the end of a level
    virtual void			LevelShutdown( void ) = 0;

    // Request a pointer to the list of client datatable classes
    virtual ClientClass		*GetAllClasses( void ) = 0;

    // Called once per level to re-initialize any hud element drawing stuff
    virtual int				HudVidInit( void ) = 0;
    // Called by the engine when gathering user input
    virtual void			HudProcessInput( bool bActive ) = 0;
    // Called oncer per frame to allow the hud elements to think
    virtual void			HudUpdate( bool bActive ) = 0;
    // Reset the hud elements to their initial states
    virtual void			HudReset( void ) = 0;
    // Display a hud text message
    virtual void			HudText( const char * message ) = 0;

    // Mouse Input Interfaces
    // Activate the mouse (hides the cursor and locks it to the center of the screen)
    virtual void			IN_ActivateMouse( void ) = 0;
    // Deactivates the mouse (shows the cursor and unlocks it)
    virtual void			IN_DeactivateMouse( void ) = 0;
    // This is only called during extra sound updates and just accumulates mouse x, y offets and recenters the mouse.
    //  This call is used to try to prevent the mouse from appearing out of the side of a windowed version of the engine if
    //  rendering or other processing is taking too long
    virtual void			IN_Accumulate( void ) = 0;
    // Reset all key and mouse states to their initial, unpressed state
    virtual void			IN_ClearStates( void ) = 0;
    // If key is found by name, returns whether it's being held down in isdown, otherwise function returns false
    virtual bool			IN_IsKeyDown( const char *name , bool& isdown ) = 0;
    // Notify the client that the mouse was wheeled while in game - called prior to executing any bound commands.
    virtual void			IN_OnMouseWheeled( int nDelta ) = 0;
    // Raw keyboard signal, if the client .dll returns 1, the engine processes the key as usual, otherwise,
    //  if the client .dll returns 0, the key is swallowed.
    virtual int				IN_KeyEvent( int eventcode , int keynum , const char *pszCurrentBinding ) = 0;

    // This function is called once per tick to create the player CUserCmd (used for prediction/physics simulation of the player)
    // Because the mouse can be sampled at greater than the tick interval, there is a separate input_sample_frametime, which
    //  specifies how much additional mouse / keyboard simulation to perform.
    virtual void			CreateMove(
        int sequence_number ,			// sequence_number of this cmd
        float input_sample_frametime ,	// Frametime for mouse input sampling
        bool active ) = 0;				// True if the player is active (not paused)

                                        // If the game is running faster than the tick_interval framerate, then we do extra mouse sampling to avoid jittery input
                                        //  This code path is much like the normal move creation code, except no move is created
    virtual void			ExtraMouseSample( float frametime , bool active ) = 0;

    // Encode the delta (changes) between the CUserCmd in slot from vs the one in slot to.  The game code will have
    //  matching logic to read the delta.
    virtual bool			WriteUsercmdDeltaToBuffer( Pointer buf , int from , int to , bool isnewcommand ) = 0;
    // Demos need to be able to encode/decode CUserCmds to memory buffers, so these functions wrap that
    virtual void			EncodeUserCmdToBuffer( HEX& buf , int slot ) = 0;
    virtual void			DecodeUserCmdFromBuffer( HEX& buf , int slot ) = 0;

    // Set up and render one or more views (e.g., rear view window, etc.).  This called into RenderView below
    virtual void			View_Render( Pointer *rect ) = 0;

    // Allow engine to expressly render a view (e.g., during timerefresh)
    // See IVRenderView.h, PushViewFlags_t for nFlags values
    virtual void			RenderView( const HEX &view , int nClearFlags , int whatToDraw ) = 0;

    // Apply screen fade directly from engine
    virtual void			View_Fade( Pointer *pSF ) = 0;

    // The engine has parsed a crosshair angle message, this function is called to dispatch the new crosshair angle
    virtual void			SetCrosshairAngle( const Angle& angle ) = 0;

    // Sprite (.spr) model handling code
    // Load a .spr file by name
    virtual void			InitSprite( Pointer pSprite , const char *loadname ) = 0;
    // Shutdown a .spr file
    virtual void			ShutdownSprite( Pointer pSprite ) = 0;
    // Returns sizeof( CEngineSprite ) so the engine can allocate appropriate memory
    virtual int				GetSpriteSize( void ) const = 0;

    // Called when a player starts or stops talking.
    // entindex is -1 to represent the local client talking (before the data comes back from the server).
    // entindex is -2 to represent the local client's voice being acked by the server.
    // entindex is GetPlayer() when the server acknowledges that the local client is talking.
    virtual void			VoiceStatus( int entindex , int bTalking ) = 0;

    // Networked string table definitions have arrived, allow client .dll to
    //  hook string changes with a callback function ( see INetworkStringTableClient.h )
    virtual void			InstallStringTableCallback( char const *tableName ) = 0;

    // Notification that we're moving into another stage during the frame.
    virtual void			FrameStageNotify( ClientFrameStage_t curStage ) = 0;

    // The engine has Recvd the specified user message, this code is used to dispatch the message handler
    virtual bool			DispatchUserMessage( int msg_type , HEX &msg_data ) = 0;

    // Save/restore system hooks
    virtual Pointer         PointerSaveInit( int size ) = 0;
    virtual void			SaveWriteFields( Pointer , const char * , void * , Pointer , Pointer , int ) = 0;
    virtual void			SaveReadFields( Pointer , const char * , void * , Pointer , Pointer , int ) = 0;
    virtual void			PreSave( Pointer ) = 0;
    virtual void			Save( Pointer ) = 0;
    virtual void			WriteSaveHeaders( Pointer ) = 0;
    virtual void			ReadRestoreHeaders( Pointer ) = 0;
    virtual void			Restore( Pointer , bool ) = 0;
    virtual void			DispatchOnRestore() = 0;

    // Hand over the StandardRecvProxies in the client DLL's module.
    virtual Pointer         GetStandardRecvProxies() = 0;

    // save game screenshot writing
    virtual void			WriteSaveGameScreenshot( const char *pFilename ) = 0;

    // Given a list of "S(wavname) S(wavname2)" tokens, look up the localized text and emit
    //  the appropriate close caption if running with closecaption = 1
    virtual void			EmitSentenceCloseCaption( char const *tokenstream ) = 0;
    // Emits a regular close caption by token name
    virtual void			EmitCloseCaption( char const *captionname , float duration ) = 0;

    // Returns true if the client can start recording a demo now.  If the client returns false,
    // an error message of up to length bytes should be returned in errorMsg.
    virtual bool			CanRecordDemo( char *errorMsg , int length ) const = 0;

    // Give the Client a chance to do setup/cleanup.
    virtual void			OnDemoRecordStart( char const* pDemoBaseName ) = 0;
    virtual void			OnDemoRecordStop() = 0;
    virtual void			OnDemoPlaybackStart( char const* pDemoBaseName ) = 0;
    virtual void			OnDemoPlaybackStop() = 0;

    // Draw the console overlay?
    virtual bool			ShouldDrawDropdownConsole() = 0;

    // Get client screen dimensions
    virtual int				GetScreenWidth() = 0;
    virtual int				GetScreenHeight() = 0;

    // Added interface

    // save game screenshot writing
    virtual void			WriteSaveGameScreenshotOfSize( const char *pFilename , int width , int height , bool bCreatePowerOf2Padded = false , bool bWriteVTF = false ) = 0;

    // Gets the current view
    virtual bool			GetPlayerView( HEX &playerView ) = 0;

    // Matchmaking
    virtual void			SetupGameProperties( HEX &contexts , HEX &properties ) = 0;
    virtual uHEX			GetPresenceID( const char *pIDName ) = 0;
    virtual const char		*GetPropertyIdString( const uHEX id ) = 0;
    virtual void			GetPropertyDisplayString( uHEX id , uHEX value , char *pOutput , int nBytes ) = 0;

#ifdef WIN32
    virtual void			StartStatsReporting( HANDLE handle , bool bArbitrated ) = 0;
#endif

    virtual void			InvalidateMdlCache() = 0;

    virtual void			IN_SetSampleTime( float frametime ) = 0;

    // For sv_pure mode. The filesystem figures out which files the client needs to reload to be "pure" ala the server's preferences.
    virtual void			ReloadFilesInList( Pointer pFilesToReload ) = 0;
#ifdef POSIX
    // AR: Same as above win32 defn but down here at the end of the vtable for back compat
    virtual void			StartStatsReporting( HANDLE handle , bool bArbitrated ) = 0;
#endif

    // Let the client handle UI toggle - if this function returns false, the UI will toggle, otherwise it will not.
    virtual bool			HandleUiToggle() = 0;

    // Allow the console to be shown?
    virtual bool			ShouldAllowConsole() = 0;

    // Get renamed recv tables
    virtual Pointer GetRenamedRecvTableInfos() = 0;

    // Get the mouthinfo for the sound being played inside UI panels
    virtual Pointer GetClientUIMouthInfo() = 0;

    // Notify the client that a file has been Recvd from the game server
    virtual void			FileRecvd( const char * fileName , unsigned int transferID ) = 0;

    virtual const char* TranslateEffectForVisionFilter( const char *pchEffectType , const char *pchEffectName ) = 0;

    // Give the client a chance to modify sound settings however they want before the sound plays. This is used for
    // things like adjusting pitch of voice lines in Pyroland in TF2.
    virtual void			ClientAdjustStartSoundParams( struct StartSoundParams_t& params ) = 0;

    // Returns true if the disconnect command has been handled by the client
    virtual bool DisconnectAttempt( void ) = 0;

    virtual bool IsConnectedUserInfoChangeAllowed( IConVar *pCvar ) = 0;
};

class IClientMode
{
    // Misc.
public:

    virtual			~IClientMode()
    {}

   // Called before the HUD is initialized.
    virtual void	InitViewport() = 0;

    // One time init when .dll is first loaded.
    virtual void	Init() = 0;

    // Called when vgui is shutting down.
    virtual void	VGui_Shutdown() = 0;

    // One time call when dll is shutting down
    virtual void	Shutdown() = 0;

    // Called when switching from one IClientMode to another.
    // This can re-layout the view and such.
    // Note that Enable and Disable are called when the DLL initializes and shuts down.
    virtual void	Enable() = 0;
    virtual void	EnableWithRootPanel( VPANEL pRoot ) = 0;

    // Called when it's about to go into another client mode.
    virtual void	Disable() = 0;

    // Called when initializing or when the view changes.
    // This should move the viewport into the correct position.
    virtual void	Layout( bool bForce = false ) = 0;

    // Gets at the viewport, if there is one...
    virtual Pointer *GetViewport() = 0;

    // Gets a panel hierarchically below the viewport by name like so "ASWHudInventoryMode/SuitAbilityPanel/ItemPanel1"...
    virtual Pointer *GetPanelFromViewport( const char *pchNamePath ) = 0;

    // Gets at the viewports vgui panel animation controller, if there is one...
    virtual Pointer GetViewportAnimationController() = 0;

    // called every time shared client dll/engine data gets changed,
    // and gives the cdll a chance to modify the data.
    virtual void	ProcessInput( bool bActive ) = 0;

    // The mode can choose to draw/not draw entities.
    virtual bool	ShouldDrawDetailObjects() = 0;
    virtual bool	ShouldDrawEntity( C_BaseEntity *pEnt ) = 0;
    virtual bool	ShouldDrawLocalPlayer( C_BasePlayer *pPlayer ) = 0;
    virtual bool	ShouldDrawParticles() = 0;

    // The mode can choose to not draw fog
    virtual bool	ShouldDrawFog( void ) = 0;

    virtual void	OverrideView( CViewSetup *pSetup ) = 0;
    virtual void	OverrideAudioState( AudioState_t *pAudioState ) = 0;
    virtual int		KeyInput( int down , ButtonCode_t keynum , const char *pszCurrentBinding ) = 0;
    virtual void	StartMessageMode( int iMessageModeType ) = 0;
    virtual Pointer *GetMessagePanel() = 0;
    virtual void	OverrideMouseInput( float *x , float *y ) = 0;
    virtual bool	CreateMove( float flInputSampleTime , CUserCmd *cmd ) = 0;

    virtual void	LevelInit( const char *newmap ) = 0;
    virtual void	LevelShutdown( void ) = 0;

    // Certain modes hide the view model
    virtual bool	ShouldDrawViewModel( void ) = 0;
    virtual bool	ShouldDrawCrosshair( void ) = 0;

    // Let mode override viewport for engine
    virtual void	AdjustEngineViewport( int& x , int& y , int& width , int& height ) = 0;

    // Called before rendering a view.
    virtual void	PreRender( CViewSetup *pSetup ) = 0;

    // Called after everything is rendered.
    virtual void	PostRender( void ) = 0;

    virtual void	PostRenderVGui() = 0;

    virtual void	ActivateInGameVGuiContext( Pointer *pPanel ) = 0;
    virtual void	DeactivateInGameVGuiContext() = 0;
    virtual float	GetViewModelFOV( void ) = 0;

    virtual bool	CanRecordDemo( char *errorMsg , int length ) const = 0;

    virtual void	OnColorCorrectionWeightsReset( void ) = 0;
    virtual float	GetColorCorrectionScale( void ) const = 0;

    virtual int		HudElementKeyInput( int down , ButtonCode_t keynum , const char *pszCurrentBinding ) = 0;

    virtual void	DoPostScreenSpaceEffects( const CViewSetup *pSetup ) = 0;

    // Updates.
public:

    // Called every frame.
    virtual void	Update() = 0;

    virtual void	SetBlurFade( float scale ) = 0;
    virtual float	GetBlurFade( void ) = 0;
};

#endif