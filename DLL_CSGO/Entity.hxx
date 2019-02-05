#ifndef ENTITY
#define ENTITY
#pragma once

/* Defines */

enum
{
    EF_BONEMERGE = 0x001 ,	// Performs bone merge on client side
    EF_BRIGHTLIGHT = 0x002 ,	// DLIGHT centered at entity origin
    EF_DIMLIGHT = 0x004 ,	// player flashlight
    EF_NOINTERP = 0x008 ,	// don't interpolate the next frame
    EF_NOSHADOW = 0x010 ,	// Don't cast no shadow
    EF_NODRAW = 0x020 ,	// don't draw entity
    EF_NORecvSHADOW = 0x040 ,	// Don't Recv no shadow
    EF_BONEMERGE_FASTCULL = 0x080 ,	// For use with EF_BONEMERGE. If this is set, then it places this ent's origin at its
                                    // parent and uses the parent's bbox + the max extents of the aiment.
                                    // Otherwise, it sets up the parent's bones every frame to figure out where to place
                                    // the aiment, which is inefficient because it'll setup the parent's bones even if
                                    // the parent is not in the PVS.
                                    EF_ITEM_BLINK = 0x100 ,	// blink an item so that the user notices it.
                                    EF_PARENT_ANIMATES = 0x200 ,	// always assume that the parent entity is animating
                                    EF_MAX_BITS = 10
};

#define MAX_VIEW_MODELS 2

// Entity flags that only exist on the client.
#define ENTCLIENTFLAG_GETTINGSHADOWRENDERBOUNDS	0x0001		// Tells us if we're getting the real ent render bounds or the shadow render bounds.
#define ENTCLIENTFLAG_DONTUSEIK					0x0002		// Don't use IK on this entity even if its model has IK.
#define ENTCLIENTFLAG_ALWAYS_INTERPOLATE		0x0004		// Used by view models.

// This is the default, see shareddefs.h for mod-specific value, which can override this
#define DEFAULT_TICK_INTERVAL	(0.015)				// 15 msec is the default
#define MINIMUM_TICK_INTERVAL   (0.001)
#define MAXIMUM_TICK_INTERVAL	(0.1)

// This is the max # of players the engine can handle
#define ABSOLUTE_PLAYER_LIMIT 255  // not 256, so we can send the limit as a byte
#define ABSOLUTE_PLAYER_LIMIT_DW	( (ABSOLUTE_PLAYER_LIMIT/32) + 1 )

// a player name may have 31 chars + 0 on the PC.
// the 360 only allows 15 char + 0, but stick with the larger PC size for cross-platform communication
#define MAX_PLAYER_NAME_LENGTH		32

#ifdef _X360
#define MAX_PLAYERS_PER_CLIENT		XUSER_MAX_COUNT	// Xbox 360 supports 4 players per console
#else
#define MAX_PLAYERS_PER_CLIENT		1	// One player per PC
#endif

// Max decorated map name, with things like workshop/cp_foo.ugc123456
#define MAX_MAP_NAME				96

// Max name used in save files. Needs to be left at 32 for SourceSDK compatibility.
#define MAX_MAP_NAME_SAVE			32

// Max non-decorated map name for e.g. server browser (just cp_foo)
#define MAX_DISPLAY_MAP_NAME		32

#define	MAX_NETWORKID_LENGTH		64  // num chars for a network (i.e steam) ID

// BUGBUG: Reconcile with or derive this from the engine's internal definition!
// FIXME: I added an extra bit because I needed to make it signed
#define SP_MODEL_INDEX_BITS			13

// How many bits to use to encode an edict.
#define	MAX_EDICT_BITS				11			// # of bits needed to represent max edicts
// Max # of edicts in a level
#define	MAX_EDICTS					(1<<MAX_EDICT_BITS)

// How many bits to use to encode an server class index
#define MAX_SERVER_CLASS_BITS		9
// Max # of networkable server classes
#define MAX_SERVER_CLASSES			(1<<MAX_SERVER_CLASS_BITS)

#define SIGNED_GUID_LEN 32 // Hashed CD Key (32 hex alphabetic chars + 0 terminator )

// Used for networking ehandles.
#define NUM_ENT_ENTRY_BITS		(MAX_EDICT_BITS + 1)
#define NUM_ENT_ENTRIES			(1 << NUM_ENT_ENTRY_BITS)
#define ENT_ENTRY_MASK			(NUM_ENT_ENTRIES - 1)
#define INVALID_EHANDLE_INDEX	0xFFFFFFFF

#define NUM_SERIAL_NUM_BITS		(32 - NUM_ENT_ENTRY_BITS)

// Networked ehandles use less bits to encode the serial number.
#define NUM_NETWORKED_EHANDLE_SERIAL_NUMBER_BITS	10
#define NUM_NETWORKED_EHANDLE_BITS					(MAX_EDICT_BITS + NUM_NETWORKED_EHANDLE_SERIAL_NUMBER_BITS)
#define INVALID_NETWORKED_EHANDLE_VALUE				((1 << NUM_NETWORKED_EHANDLE_BITS) - 1)

// This is the maximum amount of data a PackedEntity can have. Having a limit allows us
// to use static arrays sometimes instead of allocating memory all over the place.
#define MAX_PACKEDENTITY_DATA	(16384)

// This is the maximum number of properties that can be delta'd. Must be evenly divisible by 8.
#define MAX_PACKEDENTITY_PROPS	(4096)

// a client can have up to 4 customization files (logo, sounds, models, txt).
#define MAX_CUSTOM_FILES		4		// max 4 files
#define MAX_CUSTOM_FILE_SIZE	524288	// Half a megabyte

//
// Constants shared by the engine and dlls
// This header file included by engine files and DLL files.
// Most came from server.h

// CBaseEntity::m_fFlags
// PLAYER SPECIFIC FLAGS FIRST BECAUSE WE USE ONLY A FEW BITS OF NETWORK PRECISION
// This top block is for singleplayer games only....no HL2:DM (which defines HL2_DLL)
#if !defined( HL2MP ) && ( defined( PORTAL ) || defined( HL2_EPISODIC ) || defined ( HL2_DLL ) || defined( HL2_LOSTCOAST ) )
#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define	FL_WATERJUMP			(1<<2)	// player jumping out of water
#define FL_ONTRAIN				(1<<3) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<4)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<5) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<6) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<7)	// Is a player
#define FL_FAKECLIENT			(1<<8)	// Fake client, simulated server side; don't send network messages to them
// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
#define	FL_INWATER				(1<<9)	// In water

// NOTE if you move things up, make sure to change this value
#define PLAYER_FLAG_BITS		10

#define	FL_FLY					(1<<10)	// Changes the SV_Movestep() behavior to not need to be on ground
#define	FL_SWIM					(1<<11)	// Changes the SV_Movestep() behavior to not need to be on ground (but stay in water)
#define	FL_CONVEYOR				(1<<12)
#define	FL_NPC					(1<<13)
#define	FL_GODMODE				(1<<14)
#define	FL_NOTARGET				(1<<15)
#define	FL_AIMTARGET			(1<<16)	// set if the crosshair needs to aim onto the entity
#define	FL_PARTIALGROUND		(1<<17)	// not all corners are valid
#define FL_STATICPROP			(1<<18)	// Eetsa static prop!
#define FL_GRAPHED				(1<<19) // worldgraph has this ent listed as something that blocks a connection
#define FL_GRENADE				(1<<20)
#define FL_STEPMOVEMENT			(1<<21)	// Changes the SV_Movestep() behavior to not do any processing
#define FL_DONTTOUCH			(1<<22)	// Doesn't generate touch functions, generates Untouch() for anything it was touching when this flag was set
#define FL_BASEVELOCITY			(1<<23)	// Base velocity has been applied this frame (used to convert base velocity into momentum)
#define FL_WORLDBRUSH			(1<<24)	// Not moveable/removeable brush entity (really part of the world, but represented as an entity for transparency or something)
#define FL_OBJECT				(1<<25) // Terrible name. This is an object that NPCs should see. Missiles, for example.
#define FL_KILLME				(1<<26)	// This entity is marked for death -- will be freed by game DLL
#define FL_ONFIRE				(1<<27)	// You know...
#define FL_DISSOLVING			(1<<28) // We're dissolving!
#define FL_TRANSRAGDOLL			(1<<29) // In the process of turning into a client side ragdoll.
#define FL_UNBLOCKABLE_BY_PLAYER (1<<30) // pusher that can't be blocked by the player
#else
#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define FL_ANIMDUCKING			(1<<2)	// Player flag -- Player is in the process of crouching or uncrouching but could be in transition
// examples:                                   Fully ducked:  FL_DUCKING &  FL_ANIMDUCKING
//           Previously fully ducked, unducking in progress:  FL_DUCKING & !FL_ANIMDUCKING
//                                           Fully unducked: !FL_DUCKING & !FL_ANIMDUCKING
//           Previously fully unducked, ducking in progress: !FL_DUCKING &  FL_ANIMDUCKING
#define	FL_WATERJUMP			(1<<3)	// player jumping out of water
#define FL_ONTRAIN				(1<<4) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<5)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<6) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<7) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<8)	// Is a player
#define FL_FAKECLIENT			(1<<9)	// Fake client, simulated server side; don't send network messages to them
// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
#define	FL_INWATER				(1<<10)	// In water

// NOTE if you move things up, make sure to change this value
#define PLAYER_FLAG_BITS		11

#define	FL_FLY					(1<<11)	// Changes the SV_Movestep() behavior to not need to be on ground
#define	FL_SWIM					(1<<12)	// Changes the SV_Movestep() behavior to not need to be on ground (but stay in water)
#define	FL_CONVEYOR				(1<<13)
#define	FL_NPC					(1<<14)
#define	FL_GODMODE				(1<<15)
#define	FL_NOTARGET				(1<<16)
#define	FL_AIMTARGET			(1<<17)	// set if the crosshair needs to aim onto the entity
#define	FL_PARTIALGROUND		(1<<18)	// not all corners are valid
#define FL_STATICPROP			(1<<19)	// Eetsa static prop!
#define FL_GRAPHED				(1<<20) // worldgraph has this ent listed as something that blocks a connection
#define FL_GRENADE				(1<<21)
#define FL_STEPMOVEMENT			(1<<22)	// Changes the SV_Movestep() behavior to not do any processing
#define FL_DONTTOUCH			(1<<23)	// Doesn't generate touch functions, generates Untouch() for anything it was touching when this flag was set
#define FL_BASEVELOCITY			(1<<24)	// Base velocity has been applied this frame (used to convert base velocity into momentum)
#define FL_WORLDBRUSH			(1<<25)	// Not moveable/removeable brush entity (really part of the world, but represented as an entity for transparency or something)
#define FL_OBJECT				(1<<26) // Terrible name. This is an object that NPCs should see. Missiles, for example.
#define FL_KILLME				(1<<27)	// This entity is marked for death -- will be freed by game DLL
#define FL_ONFIRE				(1<<28)	// You know...
#define FL_DISSOLVING			(1<<29) // We're dissolving!
#define FL_TRANSRAGDOLL			(1<<30) // In the process of turning into a client side ragdoll.
#define FL_UNBLOCKABLE_BY_PLAYER (1<<31) // pusher that can't be blocked by the player
#endif

// m_lifeState values
#define	LIFE_ALIVE				0 // alive
#define	LIFE_DYING				1 // playing death animation or still falling off of a ledge waiting to hit ground
#define	LIFE_DEAD				2 // dead. lying still.
#define LIFE_RESPAWNABLE		3
#define LIFE_DISCARDBODY		4

#define EF_PARITY_BITS	3
#define EF_PARITY_MASK  ((1<<EF_PARITY_BITS)-1)

// How many bits does the muzzle flash parity thing get?
#define EF_MUZZLEFLASH_BITS 2

// plats
#define	PLAT_LOW_TRIGGER	1

// Trains
#define	SF_TRAIN_WAIT_RETRIGGER	1
#define SF_TRAIN_PASSABLE		8		// Train is not solid -- used to make water trains

// view angle update types for CPlayerState::fixangle
#define FIXANGLE_NONE			0
#define FIXANGLE_ABSOLUTE		1
#define FIXANGLE_RELATIVE		2

// Break Model Defines

#define BREAK_GLASS		0x01
#define BREAK_METAL		0x02
#define BREAK_FLESH		0x04
#define BREAK_WOOD		0x08

#define BREAK_SMOKE		0x10
#define BREAK_TRANS		0x20
#define BREAK_CONCRETE	0x40

// If this is set, then we share a lighting origin with the last non-slave breakable sent down to the client
#define BREAK_SLAVE		0x80

// Colliding temp entity sounds

#define BOUNCE_GLASS	BREAK_GLASS
#define	BOUNCE_METAL	BREAK_METAL
#define BOUNCE_FLESH	BREAK_FLESH
#define BOUNCE_WOOD		BREAK_WOOD
#define BOUNCE_SHRAP	0x10
#define BOUNCE_SHELL	0x20
#define	BOUNCE_CONCRETE BREAK_CONCRETE
#define BOUNCE_SHOTSHELL 0x80

// Temp entity bounce sound types
#define TE_BOUNCE_NULL		0
#define TE_BOUNCE_SHELL		1
#define TE_BOUNCE_SHOTSHELL	2

#define SOUND_NORMAL_CLIP_DIST	1000.0f

// How many networked area portals do we allow?
#define MAX_AREA_STATE_BYTES		32
#define MAX_AREA_PORTAL_STATE_BYTES 24

// user message max payload size (note, this value is used by the engine, so MODs cannot change it)
#define MAX_USER_MSG_DATA 255
#define MAX_ENTITY_MSG_DATA 255

enum InvalidatePhysicsBits_t
{
    POSITION_CHANGED = 0x1 ,
    ANGLES_CHANGED = 0x2 ,
    VELOCITY_CHANGED = 0x4 ,
    ANIMATION_CHANGED = 0x8 ,		// Means cycle has changed, or any other event which would cause render-to-texture shadows to need to be rerendeded
    BOUNDS_CHANGED = 0x10 ,		// Means render bounds have changed, so shadow decal projection is required, etc.
    SEQUENCE_CHANGED = 0x20 ,		// Means sequence has changed, only interesting when surrounding bounds depends on sequence
};

// Rendering constants
// if this is changed, update common/MaterialSystem/Sprite.cpp
enum RenderMode_t
{
    kRenderNormal = 0 ,		// src
    kRenderTransColor ,		// c*a+dest*(1-a)
    kRenderTransTexture ,	// src*a+dest*(1-a)
    kRenderGlow ,			// src*a+dest -- No Z buffer checks -- Fixed size in screen space
    kRenderTransAlpha ,		// src*srca+dest*(1-srca)
    kRenderTransAdd ,		// src*a+dest
    kRenderEnvironmental ,	// not drawn, used for environmental effects
    kRenderTransAddFrameBlend , // use a fractional frame value to blend between animation frames
    kRenderTransAlphaAdd ,	// src + dest*(1-a)
    kRenderWorldGlow ,		// Same as kRenderGlow but not fixed size in screen space
    kRenderNone ,			// Don't render.

    kRenderModeCount ,		// must be last
};

enum RenderFx_t
{
    kRenderFxNone = 0 ,
    kRenderFxPulseSlow ,
    kRenderFxPulseFast ,
    kRenderFxPulseSlowWide ,
    kRenderFxPulseFastWide ,
    kRenderFxFadeSlow ,
    kRenderFxFadeFast ,
    kRenderFxSolidSlow ,
    kRenderFxSolidFast ,
    kRenderFxStrobeSlow ,
    kRenderFxStrobeFast ,
    kRenderFxStrobeFaster ,
    kRenderFxFlickerSlow ,
    kRenderFxFlickerFast ,
    kRenderFxNoDissipation ,
    kRenderFxDistort ,			// Distort/scale/translate flicker
    kRenderFxHologram ,			// kRenderFxDistort + distance fade
    kRenderFxExplode ,			// Scale up really big!
    kRenderFxGlowShell ,			// Glowing Shell
    kRenderFxClampMinScale ,		// Keep this sprite from getting very small (SPRITES only!)
    kRenderFxEnvRain ,			// for environmental rendermode, make rain
    kRenderFxEnvSnow ,			//  "        "            "    , make snow
    kRenderFxSpotlight ,			// TEST CODE for experimental spotlight
    kRenderFxRagdoll ,			// HACKHACK: TEST CODE for signalling death of a ragdoll character
    kRenderFxPulseFastWider ,
    kRenderFxMax
};

enum ShadowType_t
{
    SHADOWS_NONE = 0 ,
    SHADOWS_SIMPLE ,
    SHADOWS_RENDER_TO_TEXTURE ,
    SHADOWS_RENDER_TO_TEXTURE_DYNAMIC ,	// the shadow is always changing state
    SHADOWS_RENDER_TO_DEPTH_TEXTURE ,
};

enum ShouldTransmitState_t
{
    SHOULDTRANSMIT_START = 0 ,	// The entity is starting to be transmitted (maybe it entered the PVS).

    SHOULDTRANSMIT_END		// Called when the entity isn't being transmitted by the server.
                            // This signals a good time to hide the entity until next time
                            // the server wants to transmit its state.
};

// NOTE: All of these are commented out; NotifyShouldTransmit actually
// has all these in them. Left it as an enum in case we want to go back though
enum DataUpdateType_t
{
    DATA_UPDATE_CREATED = 0 ,	// indicates it was created +and+ entered the pvs
                                //	DATA_UPDATE_ENTERED_PVS,
                                DATA_UPDATE_DATATABLE_CHANGED ,
                                //	DATA_UPDATE_LEFT_PVS,
                                //	DATA_UPDATE_DESTROYED,		// FIXME: Could enable this, but it's a little worrying
                                // since it changes a bunch of existing code
};

// Spectator Movement modes
enum
{
    OBS_MODE_NONE = 0 ,	// not in spectator mode
    OBS_MODE_DEATHCAM ,	// special mode for death cam animation
    OBS_MODE_FREEZECAM ,	// zooms to a target, and freeze-frames on them
    OBS_MODE_FIXED ,		// view from a fixed camera position
    OBS_MODE_IN_EYE ,	// follow a player in first person view
    OBS_MODE_CHASE ,		// follow a player in third person view
    OBS_MODE_POI ,		// PASSTIME point of interest - game objective, big fight, anything interesting; added in the middle of the enum due to tons of hard-coded "<ROAMING" enum compares
    OBS_MODE_ROAMING ,	// free roaming

    NUM_OBSERVER_MODES ,
};

enum ClientAlphaDistanceFadeMode_t
{
    CLIENT_ALPHA_DISTANCE_FADE_USE_CENTER = 0 ,
    CLIENT_ALPHA_DISTANCE_FADE_USE_NEAREST_BBOX ,

    CLIENT_ALPHA_DISTANCE_FADE_MODE_COUNT ,
};

enum ModelDataCategory_t
{
    MODEL_DATA_LIGHTING_MODEL ,	// data type returned is a RenderableLightingModel_t
    MODEL_DATA_STENCIL ,			// data type returned is a ShaderStencilState_t

    MODEL_DATA_CATEGORY_COUNT ,
};

typedef unsigned short ClientShadowHandle_t;
typedef unsigned short ClientRenderHandle_t;
typedef unsigned short ModelInstanceHandle_t;
typedef unsigned char uint8;

enum
{
    CLIENTSHADOW_INVALID_HANDLE = ( ClientShadowHandle_t ) ~0
};

typedef enum
{
    LEGANIM_9WAY ,		// Legs use a 9-way blend, with "move_x" and "move_y" pose parameters.
    LEGANIM_8WAY ,		// Legs use an 8-way blend with "move_yaw" pose param.
    LEGANIM_GOLDSRC	// Legs always point in the direction he's running and the torso rotates.
} LegAnimType_t;

class IPlayerAnimState
{
public:
    virtual void Release() = 0;

    // Update() and DoAnimationEvent() together maintain the entire player's animation state.
    //
    // Update() maintains the the lower body animation (the player's m_nSequence)
    // and the upper body overlay based on the player's velocity and look direction.
    //
    // It also modulates these based on events triggered by DoAnimationEvent.
    virtual void Update( float eyeYaw , float eyePitch ) = 0;

    // This is called by the client when a new player enters the PVS to clear any events
    // the dormant version of the entity may have been playing.
    virtual void ClearAnimationState() = 0;

    // The client uses this to figure out what angles to render the entity with (since as the guy turns,
    // it will change his body_yaw pose parameter before changing his rendered angle).
    virtual const Angle& GetRenderAngles() = 0;
};

class CBoneAccessor
{
    // Only used in the client DLL for debug verification.
    C_BaseAnimating* m_pAnimating;

    Matrix3x4 *m_pBones;

    int m_ReadableBones;		// Which bones can be read.
    int m_WritableBones;		// Which bones can be written.
};

class CStudioHdr
{
public:
    mutable studiohdr_t		*m_pStudioHdr;
    mutable void	        *m_pVModel;

    mutable CUtlVector< studiohdr_t * > m_pStudioHdrCache;
};

// This provides a way for entities to know when they've entered or left the PVS.
// Normally, server entities can use NotifyShouldTransmit to get this info, but client-only
// entities can use this. Store a CPVSNotifyInfo in your
//
// When bInPVS=true, it's being called DURING rendering. It might be after rendering any
// number of views.
//
// If no views had the entity, then it is called with bInPVS=false after rendering.
class IPVSNotify
{
public:
    virtual void OnPVSStatusChanged( bool bInPVS ) = 0;
};

class IHandleEntity
{
public:
    virtual ~IHandleEntity()
    {}
    virtual void SetRefEHandle( const CBaseHandle &handle ) = 0;
    virtual const CBaseHandle& GetRefEHandle() const = 0;
};

class CEntInfo
{
public:
    IHandleEntity * m_pEntity;
    int				m_SerialNumber;
    CEntInfo		*m_pPrev;
    CEntInfo		*m_pNext;
};

class CBaseHandle
{
public:
    CBaseHandle( void );
    CBaseHandle( const CBaseHandle &other );
    CBaseHandle( unsigned long value );
    CBaseHandle( int iEntry , int iSerialNumber );

    void Init( int iEntry , int iSerialNumber );
    void Term();

    // Even if this returns true, Get() still can return return a non-null value.
    // This just tells if the handle has been initted with any values.
    bool IsValid() const;

    int GetEntryIndex() const;
    int GetSerialNumber() const;

    int ToInt() const;
    bool operator !=( const CBaseHandle &other ) const;
    bool operator ==( const CBaseHandle &other ) const;
    bool operator ==( const IHandleEntity* pEnt ) const;
    bool operator !=( const IHandleEntity* pEnt ) const;
    bool operator <( const CBaseHandle &other ) const;
    bool operator <( const IHandleEntity* pEnt ) const;

    // Assign a value to the handle.
    const CBaseHandle& operator=( const IHandleEntity *pEntity );
    const CBaseHandle& Set( const IHandleEntity *pEntity );

    // Use this to dereference the handle.
    // Note: this is implemented in game code (ehandle.h)
    //TODO: Get address of Get() or do similar stuff.
    IHandleEntity* Get() const;

    // The low NUM_SERIAL_BITS hold the index. If this value is less than MAX_EDICTS, then the entity is networkable.
    // The high NUM_SERIAL_NUM_BITS bits are the serial number.
    unsigned long	m_Index;
};

template< class T >
class CHandle : public CBaseHandle
{
public:

    CHandle();
    CHandle( int iEntry , int iSerialNumber );
    CHandle( const CBaseHandle &handle );
    CHandle( T *pVal );

    // The index should have come from a call to ToInt(). If it hasn't, you're in trouble.
    static CHandle<T> FromIndex( int index );

    T*		Get() const;
    void	Set( const T* pVal );

    operator T*( );
    operator T*( ) const;

    bool	operator !() const;
    bool	operator==( T *val ) const;
    bool	operator!=( T *val ) const;
    const CBaseHandle& operator=( const T *val );

    T*		operator->() const;
};

class IClientThinkable
{
public:
    // Gets at the containing class...
    virtual IClientUnknown*		GetIClientUnknown() = 0;

    virtual void				ClientThink() = 0;

    // Called when you're added to the think list.
    // GetThinkHandle's return value must be initialized to INVALID_THINK_HANDLE.
    virtual Pointer	            GetThinkHandle() = 0;
    virtual void				SetThinkHandle( Pointer hThink ) = 0;

    // Called by the client when it deletes the entity.
    virtual void				Release() = 0;
};

struct RenderableInstance_t
{
    uint8_t m_nAlpha;
};

struct model_t;

class IClientRenderable
{
public:
    // Gets at the containing class...
    virtual IClientUnknown*	GetIClientUnknown() = 0;

    // Data accessors
    virtual Vector const&			GetRenderOrigin( void ) = 0;
    virtual Angle const&			GetRenderAngles( void ) = 0;
    virtual bool					ShouldDraw( void ) = 0;
    virtual int					    GetRenderFlags( void ) = 0; // ERENDERFLAGS_xxx
    virtual void					Unused( void ) const
    {}

    virtual ClientShadowHandle_t	GetShadowHandle() const = 0;

    // Used by the leaf system to store its render handle.
    virtual ClientRenderHandle_t&	RenderHandle() = 0;

    // Render baby!
    virtual const model_t*			GetModel() const = 0;
    virtual int						DrawModel( int flags , const RenderableInstance_t &instance ) = 0;

    // Get the body parameter
    virtual int		GetBody() = 0;

    // Determine the color modulation amount
    virtual void	GetColorModulation( float* color ) = 0;

    // Returns false if the entity shouldn't be drawn due to LOD.
    // (NOTE: This is no longer used/supported, but kept in the vtable for backwards compat)
    virtual bool	LODTest() = 0;

    // Call this to get the current bone transforms for the model.
    // currentTime parameter will affect interpolation
    // nMaxBones specifies how many matrices pBoneToWorldOut can hold. (Should be greater than or
    // equal to studiohdr_t::numbones. Use MAXSTUDIOBONES to be safe.)
    virtual bool	SetupBones( Matrix3x4 *pBoneToWorldOut , int nMaxBones , int boneMask , float currentTime ) = 0;

    virtual void	SetupWeights( const Matrix3x4 *pBoneToWorld , int nFlexWeightCount , float *pFlexWeights , float *pFlexDelayedWeights ) = 0;
    virtual void	DoAnimationEvents( void ) = 0;

    // Return this if you want PVS notifications. See IPVSNotify for more info.
    // Note: you must always return the same value from this function. If you don't,
    // undefined things will occur, and they won't be good.
    virtual IPVSNotify* GetPVSNotifyInterface() = 0;

    // Returns the bounds relative to the origin (render bounds)
    virtual void	GetRenderBounds( Vector& mins , Vector& maxs ) = 0;

    // returns the bounds as an AABB in worldspace
    virtual void	GetRenderBoundsWorldspace( Vector& mins , Vector& maxs ) = 0;

    // These normally call through to GetRenderAngles/GetRenderBounds, but some entities custom implement them.
    virtual void	GetShadowRenderBounds( Vector &mins , Vector &maxs , ShadowType_t shadowType ) = 0;

    // Should this object be able to have shadows cast onto it?
    virtual bool	ShouldRecvProjectedTextures( int flags ) = 0;

    // These methods return true if we want a per-renderable shadow cast direction + distance
    virtual bool	GetShadowCastDistance( float *pDist , ShadowType_t shadowType ) const = 0;
    virtual bool	GetShadowCastDirection( Vector *pDirection , ShadowType_t shadowType ) const = 0;

    // Other methods related to shadow rendering
    virtual bool	IsShadowDirty() = 0;
    virtual void	MarkShadowDirty( bool bDirty ) = 0;

    // Iteration over shadow hierarchy
    virtual IClientRenderable *GetShadowParent() = 0;
    virtual IClientRenderable *FirstShadowChild() = 0;
    virtual IClientRenderable *NextShadowPeer() = 0;

    // Returns the shadow cast type
    virtual ShadowType_t ShadowCastType() = 0;

    // Create/get/destroy model instance
    virtual void CreateModelInstance() = 0;
    virtual ModelInstanceHandle_t GetModelInstance() = 0;

    // Returns the transform from RenderOrigin/RenderAngles to world
    virtual const Matrix3x4 &RenderableToWorldTransform() = 0;

    // Attachments
    virtual int LookupAttachment( const char *pAttachmentName ) = 0;
    virtual	bool GetAttachment( int number , Vector &origin , Angle &angles ) = 0;
    virtual bool GetAttachment( int number , Matrix3x4 &matrix ) = 0;

    // Rendering clip plane, should be 4 floats, return value of NULL indicates a disabled render clip plane
    virtual float *GetRenderClipPlane( void ) = 0;

    // Get the skin parameter
    virtual int		GetSkin() = 0;

    virtual void	OnThreadedDrawSetup() = 0;

    virtual bool	UsesFlexDelayedWeights() = 0;

    virtual void	RecordToolMessage() = 0;
    virtual bool	ShouldDrawForSplitScreenUser( int nSlot ) = 0;

    // NOTE: This is used by renderables to override the default alpha modulation,
    // not including fades, for a renderable. The alpha passed to the function
    // is the alpha computed based on the current renderfx.
    virtual uint8	OverrideAlphaModulation( uint8 nAlpha ) = 0;

    // NOTE: This is used by renderables to override the default alpha modulation,
    // not including fades, for a renderable's shadow. The alpha passed to the function
    // is the alpha computed based on the current renderfx + any override
    // computed in OverrideAlphaModulation
    virtual uint8	OverrideShadowAlphaModulation( uint8 nAlpha ) = 0;
};

class IClientNetworkable
{
public:
    // Gets at the containing class...
    virtual IClientUnknown*	GetIClientUnknown() = 0;

    // Called by the engine when the server deletes the entity.
    virtual void			Release() = 0;

    // Supplied automatically by the IMPLEMENT_CLIENTCLASS macros.
    virtual ClientClass*	GetClientClass() = 0;

    // This tells the entity what the server says for ShouldTransmit on this entity.
    // Note: This used to be EntityEnteredPVS/EntityRemainedInPVS/EntityLeftPVS.
    virtual void			NotifyShouldTransmit( ShouldTransmitState_t state ) = 0;

    //
    // NOTE FOR ENTITY WRITERS:
    //
    // In 90% of the cases, you should hook OnPreDataChanged/OnDataChanged instead of
    // PreDataUpdate/PostDataUpdate.
    //
    // The DataChanged events are only called once per frame whereas Pre/PostDataUpdate
    // are called once per packet (and sometimes multiple times per frame).
    //
    // OnDataChanged is called during simulation where entity origins are correct and
    // attachments can be used. whereas PostDataUpdate is called while parsing packets
    // so attachments and other entity origins may not be valid yet.
    //

    virtual void			OnPreDataChanged( DataUpdateType_t updateType ) = 0;
    virtual void			OnDataChanged( DataUpdateType_t updateType ) = 0;

    // Called when data is being updated across the network.
    // Only low-level entities should need to know about these.
    virtual void			PreDataUpdate( DataUpdateType_t updateType ) = 0;
    virtual void			PostDataUpdate( DataUpdateType_t updateType ) = 0;

    virtual void             pad_0( void ) = 0;

    // Objects become dormant on the client if they leave the PVS on the server.
    virtual bool			IsDormant( void ) = 0;

    // Ent Index is the server handle used to reference this entity.
    // If the index is < 0, that indicates the entity is not known to the server
    virtual int				entindex( void ) const = 0;

    // Server to client entity message Recvd
    virtual void			RecvMessage( int classID , bf_read &msg ) = 0;

    // Get the base pointer to the networked data that GetClientClass->m_pRecvTable starts at.
    // (This is usually just the "this" pointer).
    virtual void*			GetDataTableBasePtr() = 0;

    // Tells the entity that it's about to be destroyed due to the client receiving
    // an uncompressed update that's caused it to destroy all entities & recreate them.
    virtual void			SetDestroyedOnRecreateEntities( void ) = 0;

    virtual void			OnDataUnchangedInPVS() = 0;
};

class IClientModelRenderable
{
public:
    virtual bool GetRenderData( void *pData , ModelDataCategory_t nCategory ) = 0;
};

class IClientAlphaProperty
{
public:
    // Gets at the containing class...
    virtual IClientUnknown*	GetIClientUnknown() = 0;

    // Sets a constant alpha modulation value
    virtual void SetAlphaModulation( uint8_t a ) = 0;

    // Sets an FX function
    // NOTE: kRenderFxFadeSlow, kRenderFxFadeFast, kRenderFxSolidSlow, kRenderFxSolidFast all need a start time only.
    // kRenderFxFadeIn/kRenderFxFadeOut needs start time + duration
    // All other render fx require no parameters
    virtual void SetRenderFX( RenderFx_t nRenderFx , RenderMode_t nRenderMode , float flStartTime = FLT_MAX , float flDuration = 0.0f ) = 0;

    // Sets fade parameters
    virtual void SetFade( float flGlobalFadeScale , float flDistFadeStart , float flDistFadeEnd ) = 0;

    // Sets desync offset, used to make sine waves not match
    virtual void SetDesyncOffset( int nOffset ) = 0;

    // Allows the owner to override alpha.
    // The method IClientRenderable::OverrideAlphaModulation will be called
    // to allow the owner to optionally return a different alpha modulation
    virtual void EnableAlphaModulationOverride( bool bEnable ) = 0;

    // Allows the owner to override projected shadow alpha.
    // The method IClientRenderable::OverrideShadowAlphaModulation will be called
    // to allow the owner to optionally return a different alpha modulation for the shadow
    virtual void EnableShadowAlphaModulationOverride( bool bEnable ) = 0;

    // Sets the distance fade mode
    virtual void SetDistanceFadeMode( ClientAlphaDistanceFadeMode_t nFadeMode ) = 0;
};

class IClientUnknown : public IHandleEntity
{
public:
    virtual ICollideable*		    GetCollideable() = 0;
    virtual IClientNetworkable*	    GetClientNetworkable() = 0;
    virtual IClientRenderable*	    GetClientRenderable() = 0;
    virtual IClientEntity*		    GetIClientEntity() = 0;
    virtual C_BaseEntity*		    GetBaseEntity() = 0;
    virtual IClientThinkable*	    GetClientThinkable() = 0;
    virtual IClientAlphaProperty*	GetClientAlphaProperty() = 0;
};

class IClientEntity : public IClientUnknown , public IClientRenderable , public IClientNetworkable , public IClientThinkable
{
public:
    // Delete yourself.
    virtual void			Release( void ) = 0;

    // Network origin + angles
    virtual const Vector&	GetAbsOrigin( void ) const = 0;
    virtual const Angle&	GetAbsAngles( void ) const = 0;

    virtual Pointer		GetMouth( void ) = 0;

    // Retrieve sound spatialization info for the specified sound on this entity
    // Return false to indicate sound is not audible
    virtual bool			GetSoundSpatialization( int& info ) = 0;

    virtual bool			IsBlurred( void ) = 0;
};

class IClientEntityList
{
public:
    // Get IClientNetworkable interface for specified entity
    virtual IClientNetworkable*	GetClientNetworkable( int entnum ) = 0;
    virtual IClientNetworkable*	GetClientNetworkableFromHandle( CBaseHandle hEnt ) = 0;
    virtual IClientUnknown*		GetClientUnknownFromHandle( CBaseHandle hEnt ) = 0;

    // NOTE: This function is only a convenience wrapper.
    // It returns GetClientNetworkable( entnum )->GetIClientEntity().
    virtual IClientEntity*		GetClientEntity( int entnum ) = 0;
    virtual IClientEntity*		GetClientEntityFromHandle( CBaseHandle hEnt ) = 0;

    // Returns number of entities currently in use
    virtual int					NumberOfEntities( bool bIncludeNonNetworkable ) = 0;

    // Returns highest index actually used
    virtual int					GetHighestEntityIndex( void ) = 0;

    // Sizes entity list to specified size
    virtual void				SetMaxEntities( int maxents ) = 0;
    virtual int					GetMaxEntities() = 0;
};

// ----------------------------------------------------------------------- //
// Inlines.
// ----------------------------------------------------------------------- //

template<class T>
CHandle<T>::CHandle()
{}

template<class T>
CHandle<T>::CHandle( int iEntry , int iSerialNumber )
{
    Init( iEntry , iSerialNumber );
}

template<class T>
CHandle<T>::CHandle( const CBaseHandle &handle )
    : CBaseHandle( handle )
{}

template<class T>
CHandle<T>::CHandle( T *pObj )
{
    Term();
    Set( pObj );
}

template<class T>
inline CHandle<T> CHandle<T>::FromIndex( int index )
{
    CHandle<T> ret;
    ret.m_Index = index;
    return ret;
}

template<class T>
inline T* CHandle<T>::Get() const
{
    return ( T* ) CBaseHandle::Get();
}

template<class T>
inline CHandle<T>::operator T *( )
{
    return Get();
}

template<class T>
inline CHandle<T>::operator T *( ) const
{
    return Get();
}

template<class T>
inline bool CHandle<T>::operator !() const
{
    return !Get();
}

template<class T>
inline bool CHandle<T>::operator==( T *val ) const
{
    return Get() == val;
}

template<class T>
inline bool CHandle<T>::operator!=( T *val ) const
{
    return Get() != val;
}

template<class T>
void CHandle<T>::Set( const T* pVal )
{
    CBaseHandle::Set( reinterpret_cast< const IHandleEntity* >( pVal ) );
}

template<class T>
inline const CBaseHandle& CHandle<T>::operator=( const T *val )
{
    Set( val );
    return *this;
}

template<class T>
T* CHandle<T>::operator -> () const
{
    return Get();
}

class C_BaseEntity : public IClientEntity
{
public:

    void InvalidatePhysicsRecursive( int nChangeFlags );

    void InvalidateAllPhysicsRecursive()
    {
        for ( int i = 1; i <= 32; i *= 2 )
        {
            InvalidatePhysicsRecursive( i );
        }
    }

    bool IsDormant()
    {
        return this->GetClientNetworkable()->IsDormant() && ( entindex() != -1 );
    }

    void ResetLatched()
    {
        _CallVirtualFunction( this , 111 );
    }

    bool HasAttachement();

    bool IsPlayer();

    bool IsLocalPlayer( bool bAttachements = false );

    void SetAbsVelocity( const Vector& vAbsVelocity );

    C_BaseEntity* FirstMoveChild()
    {
        return _Offset( 0x304 , CHandle<C_BaseEntity> ).Get();
    }

    C_BaseEntity* NextMovePeer()
    {
        return _Offset( 0x308 , CHandle<C_BaseEntity> ).Get();
    }

    C_BaseEntity* GetOwnerEntity();
    bool ShouldCollide( int collisionGroup , int contentsMask );
};

class C_BaseAnimating : public C_BaseEntity
{
public:

    float *flLastBoneSetupTime()
    {
        return _POffsetManualthis( 0x2910 , float , this->GetClientRenderable() );
    }

    int *MostRecentBoneCounter()
    {
        return _POffsetManualthis( 0x267C , int , this->GetClientRenderable() );
    }

    Vector *GetLocalOrigin()
    {
        return _POffset( CBaseEntity::DT_BaseEntity::vecOrigin() , Vector );
    }

    Angle *GetLocalAngles()
    {
        return _POffset( CBaseEntity::DT_BaseEntity::angRotation() , Angle );
    }

    void SetLocalOrigin( const Vector &origin )
    {
        InvalidatePhysicsRecursive( POSITION_CHANGED );
        *GetLocalOrigin() = origin;
    }

    void SetLocalAngles( const Angle &angle )
    {
        InvalidatePhysicsRecursive( ANGLES_CHANGED );
        *GetLocalAngles() = angle;
    }

    bool _SetupBones( Matrix3x4 *pBoneToWorldOut , int nMaxBones , int boneMask , float currentTime );

    CStudioHdr* GetStudioHDR();

    bool HitboxToWorldTransforms( Matrix3x4** pBoneToWorldOut );

    void InvalidateBoneCache();

    void CopyBoneCache( Matrix3x4* pBoneToWorldOut , int iNumBonesToCopy );

    FORCEINLINE int GetCachedNumBones()
    {
        return _OffsetManualthis( 0x2908 , int , this->GetClientRenderable() );
    }

    int GetNumBones();

    mstudiobbox_t *GetBox( int iNum );

    mstudiobbox_t *GetBox( const char* sName );

    int GetNumHitboxes();

    mstudiohitboxset_t *GetHitboxSet();

    studiohdr_t* GetStudiohdr();
};

class C_BasePlayer : public C_BaseAnimating
{
public:

    IPlayerAnimState * GetPlayerAnimState()
    {
        return *( IPlayerAnimState** ) ( ( HEX ) this + 0x3874 );
    }

    int *TickBase()
    {
        return _POffset( CBasePlayer::DT_BasePlayer::DT_LocalPlayerExclusive::nTickBase() , int );
    }

    int *FinalTickBase()
    {
        return _POffset( CBasePlayer::DT_BasePlayer::DT_LocalPlayerExclusive::nTickBase() + 4 , int );
    }

    Vector GetEyePosition()
    {
        Vector vEyePosition = GetAbsOrigin();
        vEyePosition += _Offset( CBasePlayer::DT_BasePlayer::DT_LocalPlayerExclusive::vecViewOffset_0() , Vector );
        return vEyePosition;
    }

    Angle *PunchAngles()
    {
        return _POffset( CBasePlayer::DT_BasePlayer::DT_LocalPlayerExclusive::DT_Local::aimPunchAngle() , Angle );
    }

    C_Weapon* GetWeapon();
};

template<typename T = C_BasePlayer>T *GetLocalPlayer()
{
    return  ( T* ) ClientEntityList->GetClientEntity( EngineClient->GetLocalPlayer() );
}

#endif