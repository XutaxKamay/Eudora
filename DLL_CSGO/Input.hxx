#ifndef INPUT
#define INPUT
#pragma once

#define MAX_SPLITSCREEN_PLAYERS 1

// Standard maximum +/- value of a joystick axis
#define MAX_BUTTONSAMPLE			32768

#if !defined( _X360 )
#define INVALID_USER_ID		-1
#else
#define INVALID_USER_ID		XBX_INVALID_USER_ID
#endif

#define DECLARE_POINTER_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name

DECLARE_POINTER_HANDLE( InputContextHandle_t );

enum
{
    MAX_JOYSTICKS = 1 ,
    MOUSE_BUTTON_COUNT = 5 ,
    MAX_NOVINT_DEVICES = 2 ,
};

#if defined( LINUX )
// Linux has a slightly different mapping order on the joystick axes
enum JoystickAxis_t
{
    JOY_AXIS_X = 0 ,
    JOY_AXIS_Y ,
    JOY_AXIS_Z ,
    JOY_AXIS_U ,
    JOY_AXIS_R ,
    JOY_AXIS_V ,
    MAX_JOYSTICK_AXES ,
};
#else
enum JoystickAxis_t
{
    JOY_AXIS_X = 0 ,
    JOY_AXIS_Y ,
    JOY_AXIS_Z ,
    JOY_AXIS_R ,
    JOY_AXIS_U ,
    JOY_AXIS_V ,
    MAX_JOYSTICK_AXES ,
};
#endif

//-----------------------------------------------------------------------------
// Extra mouse codes
//-----------------------------------------------------------------------------
enum
{
    MS_WM_XBUTTONDOWN = 0x020B ,
    MS_WM_XBUTTONUP = 0x020C ,
    MS_WM_XBUTTONDBLCLK = 0x020D ,
    MS_MK_BUTTON4 = 0x0020 ,
    MS_MK_BUTTON5 = 0x0040 ,
};

//-----------------------------------------------------------------------------
// Events
//-----------------------------------------------------------------------------
enum InputEventType_t
{
    IE_ButtonPressed = 0 ,	// m_nData contains a ButtonCode_t
    IE_ButtonReleased ,		// m_nData contains a ButtonCode_t
    IE_ButtonDoubleClicked ,	// m_nData contains a ButtonCode_t
    IE_AnalogValueChanged ,	// m_nData contains an AnalogCode_t, m_nData2 contains the value

    IE_FirstSystemEvent = 100 ,
    IE_Quit = IE_FirstSystemEvent ,
    IE_ControllerInserted ,	// m_nData contains the controller ID
    IE_ControllerUnplugged ,	// m_nData contains the controller ID

    IE_FirstVguiEvent = 1000 ,	// Assign ranges for other systems that post user events here
    IE_FirstAppEvent = 2000 ,
};

enum
{
    JOYSTICK_MAX_BUTTON_COUNT = 32 ,
    JOYSTICK_POV_BUTTON_COUNT = 4 ,
    JOYSTICK_AXIS_BUTTON_COUNT = MAX_JOYSTICK_AXES * 2 ,
};

#define JOYSTICK_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_BUTTON + ((_joystick) * JOYSTICK_MAX_BUTTON_COUNT) + (_button) )
#define JOYSTICK_POV_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_POV_BUTTON + ((_joystick) * JOYSTICK_POV_BUTTON_COUNT) + (_button) )
#define JOYSTICK_AXIS_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_AXIS_BUTTON + ((_joystick) * JOYSTICK_AXIS_BUTTON_COUNT) + (_button) )

#define JOYSTICK_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_BUTTON_INTERNAL( _joystick, _button ) )
#define JOYSTICK_POV_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_POV_BUTTON_INTERNAL( _joystick, _button ) )
#define JOYSTICK_AXIS_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_AXIS_BUTTON_INTERNAL( _joystick, _button ) )

enum ButtonCode_t
{
    BUTTON_CODE_INVALID = -1 ,
    BUTTON_CODE_NONE = 0 ,

    KEY_FIRST = 0 ,

    KEY_NONE = KEY_FIRST ,
    KEY_0 ,
    KEY_1 ,
    KEY_2 ,
    KEY_3 ,
    KEY_4 ,
    KEY_5 ,
    KEY_6 ,
    KEY_7 ,
    KEY_8 ,
    KEY_9 ,
    KEY_A ,
    KEY_B ,
    KEY_C ,
    KEY_D ,
    KEY_E ,
    KEY_F ,
    KEY_G ,
    KEY_H ,
    KEY_I ,
    KEY_J ,
    KEY_K ,
    KEY_L ,
    KEY_M ,
    KEY_N ,
    KEY_O ,
    KEY_P ,
    KEY_Q ,
    KEY_R ,
    KEY_S ,
    KEY_T ,
    KEY_U ,
    KEY_V ,
    KEY_W ,
    KEY_X ,
    KEY_Y ,
    KEY_Z ,
    KEY_PAD_0 ,
    KEY_PAD_1 ,
    KEY_PAD_2 ,
    KEY_PAD_3 ,
    KEY_PAD_4 ,
    KEY_PAD_5 ,
    KEY_PAD_6 ,
    KEY_PAD_7 ,
    KEY_PAD_8 ,
    KEY_PAD_9 ,
    KEY_PAD_DIVIDE ,
    KEY_PAD_MULTIPLY ,
    KEY_PAD_MINUS ,
    KEY_PAD_PLUS ,
    KEY_PAD_ENTER ,
    KEY_PAD_DECIMAL ,
    KEY_LBRACKET ,
    KEY_RBRACKET ,
    KEY_SEMICOLON ,
    KEY_APOSTROPHE ,
    KEY_BACKQUOTE ,
    KEY_COMMA ,
    KEY_PERIOD ,
    KEY_SLASH ,
    KEY_BACKSLASH ,
    KEY_MINUS ,
    KEY_EQUAL ,
    KEY_ENTER ,
    KEY_SPACE ,
    KEY_BACKSPACE ,
    KEY_TAB ,
    KEY_CAPSLOCK ,
    KEY_NUMLOCK ,
    KEY_ESCAPE ,
    KEY_SCROLLLOCK ,
    KEY_INSERT ,
    KEY_DELETE ,
    KEY_HOME ,
    KEY_END ,
    KEY_PAGEUP ,
    KEY_PAGEDOWN ,
    KEY_BREAK ,
    KEY_LSHIFT ,
    KEY_RSHIFT ,
    KEY_LALT ,
    KEY_RALT ,
    KEY_LCONTROL ,
    KEY_RCONTROL ,
    KEY_LWIN ,
    KEY_RWIN ,
    KEY_APP ,
    KEY_UP ,
    KEY_LEFT ,
    KEY_DOWN ,
    KEY_RIGHT ,
    KEY_F1 ,
    KEY_F2 ,
    KEY_F3 ,
    KEY_F4 ,
    KEY_F5 ,
    KEY_F6 ,
    KEY_F7 ,
    KEY_F8 ,
    KEY_F9 ,
    KEY_F10 ,
    KEY_F11 ,
    KEY_F12 ,
    KEY_CAPSLOCKTOGGLE ,
    KEY_NUMLOCKTOGGLE ,
    KEY_SCROLLLOCKTOGGLE ,

    KEY_LAST = KEY_SCROLLLOCKTOGGLE ,
    KEY_COUNT = KEY_LAST - KEY_FIRST + 1 ,

    // Mouse
    MOUSE_FIRST = KEY_LAST + 1 ,

    MOUSE_LEFT = MOUSE_FIRST ,
    MOUSE_RIGHT ,
    MOUSE_MIDDLE ,
    MOUSE_4 ,
    MOUSE_5 ,
    MOUSE_WHEEL_UP ,		// A fake button which is 'pressed' and 'released' when the wheel is moved up
    MOUSE_WHEEL_DOWN ,	// A fake button which is 'pressed' and 'released' when the wheel is moved down

    MOUSE_LAST = MOUSE_WHEEL_DOWN ,
    MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1 ,

    // Joystick
    JOYSTICK_FIRST = MOUSE_LAST + 1 ,

    JOYSTICK_FIRST_BUTTON = JOYSTICK_FIRST ,
    JOYSTICK_LAST_BUTTON = JOYSTICK_BUTTON_INTERNAL( MAX_JOYSTICKS - 1 , JOYSTICK_MAX_BUTTON_COUNT - 1 ) ,
    JOYSTICK_FIRST_POV_BUTTON ,
    JOYSTICK_LAST_POV_BUTTON = JOYSTICK_POV_BUTTON_INTERNAL( MAX_JOYSTICKS - 1 , JOYSTICK_POV_BUTTON_COUNT - 1 ) ,
    JOYSTICK_FIRST_AXIS_BUTTON ,
    JOYSTICK_LAST_AXIS_BUTTON = JOYSTICK_AXIS_BUTTON_INTERNAL( MAX_JOYSTICKS - 1 , JOYSTICK_AXIS_BUTTON_COUNT - 1 ) ,

    JOYSTICK_LAST = JOYSTICK_LAST_AXIS_BUTTON ,

#if !defined ( _X360 )
    NOVINT_FIRST = JOYSTICK_LAST + 2 , // plus 1 missing key. +1 seems to cause issues on the first button.

    NOVINT_LOGO_0 = NOVINT_FIRST ,
    NOVINT_TRIANGLE_0 ,
    NOVINT_BOLT_0 ,
    NOVINT_PLUS_0 ,
    NOVINT_LOGO_1 ,
    NOVINT_TRIANGLE_1 ,
    NOVINT_BOLT_1 ,
    NOVINT_PLUS_1 ,

    NOVINT_LAST = NOVINT_PLUS_1 ,
#endif

    BUTTON_CODE_LAST ,
    BUTTON_CODE_COUNT = BUTTON_CODE_LAST - KEY_FIRST + 1 ,

    // Helpers for XBox 360
    KEY_XBUTTON_UP = JOYSTICK_FIRST_POV_BUTTON ,	// POV buttons
    KEY_XBUTTON_RIGHT ,
    KEY_XBUTTON_DOWN ,
    KEY_XBUTTON_LEFT ,

    KEY_XBUTTON_A = JOYSTICK_FIRST_BUTTON ,		// Buttons
    KEY_XBUTTON_B ,
    KEY_XBUTTON_X ,
    KEY_XBUTTON_Y ,
    KEY_XBUTTON_LEFT_SHOULDER ,
    KEY_XBUTTON_RIGHT_SHOULDER ,
    KEY_XBUTTON_BACK ,
    KEY_XBUTTON_START ,
    KEY_XBUTTON_STICK1 ,
    KEY_XBUTTON_STICK2 ,

    KEY_XSTICK1_RIGHT = JOYSTICK_FIRST_AXIS_BUTTON ,	// XAXIS POSITIVE
    KEY_XSTICK1_LEFT ,							// XAXIS NEGATIVE
    KEY_XSTICK1_DOWN ,							// YAXIS POSITIVE
    KEY_XSTICK1_UP ,								// YAXIS NEGATIVE
    KEY_XBUTTON_LTRIGGER ,						// ZAXIS POSITIVE
    KEY_XBUTTON_RTRIGGER ,						// ZAXIS NEGATIVE
    KEY_XSTICK2_RIGHT ,							// UAXIS POSITIVE
    KEY_XSTICK2_LEFT ,							// UAXIS NEGATIVE
    KEY_XSTICK2_DOWN ,							// VAXIS POSITIVE
    KEY_XSTICK2_UP ,								// VAXIS NEGATIVE
};

struct CameraThirdData_t
{
    float	m_flPitch;
    float	m_flYaw;
    float	m_flDist;
    float	m_flLag;
    Vector	m_vecHullMin;
    Vector	m_vecHullMax;
};

struct InputEvent_t
{
    int m_nType;				// Type of the event (see InputEventType_t)
    int m_nTick;				// Tick on which the event occurred
    int m_nData;				// Generic 32-bit data, what it contains depends on the event
    int m_nData2;				// Generic 32-bit data, what it contains depends on the event
    int m_nData3;				// Generic 32-bit data, what it contains depends on the event
};

struct kbutton_t
{
    // key nums holding it down
    int		down[ 2 ];
    // low bit is down state
    int		state;
};

class IInput
{
public:
    // Initialization/shutdown of the subsystem
    virtual	void		Init_All( void ) = 0;
    virtual void		Shutdown_All( void ) = 0;
    // Latching button states
    virtual int			GetButtonBits( bool bResetState ) = 0;
    // Create movement command
    virtual void		CreateMove( int sequence_number , float input_sample_frametime , bool active ) = 0;
    virtual void		ExtraMouseSample( float frametime , bool active ) = 0;
    virtual bool		WriteUsercmdDeltaToBuffer( int nSlot , bf_write *buf , int from , int to , bool isnewcommand ) = 0;
    virtual void		EncodeUserCmdToBuffer( int nSlot , bf_write& buf , int slot ) = 0;
    virtual void		DecodeUserCmdFromBuffer( int nSlot , bf_read& buf , int slot ) = 0;

    virtual CUserCmd	*GetUserCmd( int nSlot , int sequence_number ) = 0;

    virtual void		MakeWeaponSelection( CBaseCombatWeapon *weapon ) = 0;

    // Retrieve key state
    virtual float		KeyState( kbutton_t *key ) = 0;
    // Issue key event
    virtual int			KeyEvent( int eventcode , ButtonCode_t keynum , const char *pszCurrentBinding ) = 0;
    // Look for key
    virtual kbutton_t	*FindKey( const char *name ) = 0;

    // Issue commands from controllers
    virtual void		ControllerCommands( void ) = 0;
    // Extra initialization for some joysticks
    virtual bool		ControllerModeActive() = 0;
    virtual void		Joystick_Advanced( bool bSilent ) = 0;
    virtual void		Joystick_SetSampleTime( float frametime ) = 0;
    virtual void		IN_SetSampleTime( float frametime ) = 0;

    // Accumulate mouse delta
    virtual void		AccumulateMouse( int nSlot ) = 0;
    // Activate/deactivate mouse
    virtual void		ActivateMouse( void ) = 0;
    virtual void		DeactivateMouse( void ) = 0;

    // Clear mouse state data
    virtual void		ClearStates( void ) = 0;
    // Retrieve lookspring setting
    virtual float		GetLookSpring( void ) = 0;

    // Retrieve mouse position
    virtual void		GetFullscreenMousePos( int *mx , int *my , int *unclampedx = 0 , int *unclampedy = 0 ) = 0;
    virtual void		SetFullscreenMousePos( int mx , int my ) = 0;
    virtual void		ResetMouse() = 0;
    virtual	float		GetLastForwardMove( void ) = 0;

    // Third Person camera ( TODO/FIXME:  Move this to a separate interface? )
    virtual void		CAM_Think( void ) = 0;
    virtual int			CAM_IsThirdPerson( int nSlot = -1 ) = 0;
    virtual void		CAM_GetCameraOffset( Vector& ofs ) = 0;
    virtual void		CAM_ToThirdPerson( void ) = 0;
    virtual void		CAM_ToFirstPerson( void ) = 0;
    virtual void		CAM_ToThirdPersonShoulder( void ) = 0;
    virtual void		CAM_StartMouseMove( void ) = 0;
    virtual void		CAM_EndMouseMove( void ) = 0;
    virtual void		CAM_StartDistance( void ) = 0;
    virtual void		CAM_EndDistance( void ) = 0;
    virtual int			CAM_InterceptingMouse( void ) = 0;
    virtual	void		CAM_Command( int command ) = 0;

    // orthographic camera info	( TODO/FIXME:  Move this to a separate interface? )
    virtual void		CAM_ToOrthographic() = 0;
    virtual	bool		CAM_IsOrthographic() const = 0;
    virtual	void		CAM_OrthographicSize( float& w , float& h ) const = 0;

#if defined( HL2_CLIENT_DLL )
    // IK back channel info
    virtual void		AddIKGroundContactInfo( int entindex , float minheight , float maxheight ) = 0;
#endif

    virtual void		LevelInit( void ) = 0;

    // Causes an input to have to be re-pressed to become active
    virtual void		ClearInputButton( int bits ) = 0;

    virtual	void		CAM_SetCameraThirdData( CameraThirdData_t *pCameraData , const Angle &vecCameraOffset ) = 0;
    virtual void		CAM_CameraThirdThink( void ) = 0;
};

class CKeyboardKey
{
public:
    // Name for key
    char				name[ 32 ];
    // Pointer to the underlying structure
    kbutton_t			*pkey;
    // Next key in key list.
    CKeyboardKey		*next;
};

class CVerifiedUserCmd
{
public:
    CUserCmd	m_cmd;
    CRC32_t		m_crc;
};

class CThreadFastMutex
{
    volatile uint32_t m_ownerID;
    int				m_depth;
};

class CInput : public ::IInput
{
    // Interface
public:

    virtual		void		Init_All( void );
    virtual		void		Shutdown_All( void );
    virtual		int			GetButtonBits( bool bResetState );
    virtual		void		CreateMove( int sequence_number , float input_sample_frametime , bool active );
    virtual		void		ExtraMouseSample( float frametime , bool active );
    virtual		bool		WriteUsercmdDeltaToBuffer( int nSlot , bf_write *buf , int from , int to , bool isnewcommand );
    virtual		void		EncodeUserCmdToBuffer( int nSlot , bf_write& buf , int slot );
    virtual		void		DecodeUserCmdFromBuffer( int nSlot , bf_read& buf , int slot );

    virtual		CUserCmd	*GetUserCmd( int nSlot , int sequence_number );

    virtual		void		MakeWeaponSelection( CBaseCombatWeapon *weapon );

    virtual		float		KeyState( kbutton_t *key );
    virtual		int			KeyEvent( int down , int keynum , const char *pszCurrentBinding );
    virtual		kbutton_t	*FindKey( const char *name );

    virtual		void		ControllerCommands( void );
    virtual		void		Joystick_Advanced( bool bSilent );
    virtual		void		Joystick_SetSampleTime( float frametime );
    virtual		void		IN_SetSampleTime( float frametime );

    virtual		void		AccumulateMouse( int nSlot );
    virtual		void		ActivateMouse( void );
    virtual		void		DeactivateMouse( void );

    virtual		void		ClearStates( void );
    virtual		float		GetLookSpring( void );

    virtual		void		GetFullscreenMousePos( int *mx , int *my , int *unclampedx = NULL , int *unclampedy = NULL );
    virtual		void		SetFullscreenMousePos( int mx , int my );
    virtual		void		ResetMouse( void );

    //	virtual		bool		IsNoClipping( void );
    virtual		float		GetLastForwardMove( void );
    virtual		void		ClearInputButton( int bits );

    virtual		void		CAM_Think( void );
    virtual		int			CAM_IsThirdPerson( int nSlot = -1 );
    virtual		void		CAM_GetCameraOffset( Vector& ofs );
    virtual		void		CAM_ToThirdPerson( void );
    virtual		void		CAM_ToFirstPerson( void );
    virtual		void		CAM_ToThirdPersonShoulder( void );
    virtual		void		CAM_StartMouseMove( void );
    virtual		void		CAM_EndMouseMove( void );
    virtual		void		CAM_StartDistance( void );
    virtual		void		CAM_EndDistance( void );
    virtual		int			CAM_InterceptingMouse( void );
    virtual		void		CAM_Command( int command );

    // orthographic camera info
    virtual		void		CAM_ToOrthographic();
    virtual		bool		CAM_IsOrthographic() const;
    virtual		void		CAM_OrthographicSize( float& w , float& h ) const;

    virtual		void		LevelInit( void );

    virtual		void		CAM_SetCameraThirdData( CameraThirdData_t *pCameraData , const Angle &vecCameraOffset );
    virtual		void		CAM_CameraThirdThink( void );

    virtual		void		CheckPaused( CUserCmd *cmd );
    virtual		void		CheckSplitScreenMimic( int nSlot , CUserCmd *cmd , CUserCmd *pPlayer0Command );

    // Implementation specific initialization
    virtual void		Init_Camera( void );
    virtual void		ApplyMouse( int nSlot , Angle& viewangles , CUserCmd *cmd , float mouse_x , float mouse_y );
    virtual void	JoyStickMove( float frametime , CUserCmd *cmd );

    virtual bool	ControllerModeActive( void );
    virtual bool	JoyStickActive();
    virtual void	JoyStickSampleAxes( float &forward , float &side , float &pitch , float &yaw , bool &bAbsoluteYaw , bool &bAbsolutePitch );
    virtual void	JoyStickThirdPersonPlatformer( CUserCmd *cmd , float &forward , float &side , float &pitch , float &yaw );
    virtual void	JoyStickTurn( CUserCmd *cmd , float &yaw , float &pitch , float frametime , bool bAbsoluteYaw , bool bAbsolutePitch );
    virtual void	JoyStickForwardSideControl( float forward , float side , float &joyForwardMove , float &joySideMove );
    virtual void	JoyStickApplyMovement( CUserCmd *cmd , float joyForwardMove , float joySideMove );
    virtual void GetWindowCenter( int&x , int& y );

    typedef struct
    {
        unsigned int AxisFlags;
        unsigned int AxisMap;
        unsigned int ControlMap;
    } joy_axis_t;

    enum
    {
        GAME_AXIS_NONE = 0 ,
        GAME_AXIS_FORWARD ,
        GAME_AXIS_PITCH ,
        GAME_AXIS_SIDE ,
        GAME_AXIS_YAW ,
        MAX_GAME_AXES
    };

    enum
    {
        CAM_COMMAND_NONE = 0 ,
        CAM_COMMAND_TOTHIRDPERSON = 1 ,
        CAM_COMMAND_TOFIRSTPERSON = 2
    };

    enum
    {
        MOUSE_ACCEL_THRESHHOLD1 = 0 ,	// if mouse moves > this many mickey's double it
        MOUSE_ACCEL_THRESHHOLD2 ,		// if mouse moves > this many mickey's double it a second time
        MOUSE_SPEED_FACTOR ,				// 1 - 20 (default 10) scale factor to accelerated mouse setting

        NUM_MOUSE_PARAMS ,
    };

    bool m_fTrackIRAvailable;			// 0x04
    bool m_fMouseInitialized;			// 0x05
    bool m_fMouseActive;				// 0x06
    bool m_fJoystickAdvancedInit;		// 0x07
    char pad_0x08[ 0x2C ];				// 0x08
    CKeyboardKey *m_pKeys;				// 0x34
    char pad_0x38[ 0x64 ];				// 0x38
    bool m_fCameraInterceptingMouse;	// 0x9C
    bool m_fCameraInThirdPerson;		// 0x9D
    bool m_fCameraMovingWithMouse;		// 0x9E
    Vector m_vecCameraOffset;			// 0xA0
    bool m_fCameraDistanceMove;			// 0xAC
    int m_nCameraOldX;					// 0xB0
    int m_nCameraOldY;					// 0xB4
    int m_nCameraX;						// 0xB8
    int m_nCameraY;						// 0xBC
    bool m_CameraIsOrthographic;		// 0xC0
    Angle m_angPreviousViewAngles;		// 0xC4
    Angle m_angPreviousViewAnglesTilt;	// 0xD0
    float m_flLastForwardMove;			// 0xDC
    int m_nClearInputState;				// 0xE0
    char pad_0xE4[ 0x8 ];					// 0xE4
    CUserCmd* m_pCommands;				// 0xEC
    CVerifiedUserCmd* m_pVerifiedCommands; // 0xF0
};

#endif