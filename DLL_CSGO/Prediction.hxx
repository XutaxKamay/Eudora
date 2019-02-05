#ifndef PREDICTION
#define PREDICTION
#pragma once

#define GAMEMOVEMENT_DUCK_TIME				1000		// ms
#define GAMEMOVEMENT_JUMP_TIME				510			// ms approx - based on the 21 unit height jump
#define GAMEMOVEMENT_JUMP_HEIGHT			21.0f		// units
#define GAMEMOVEMENT_TIME_TO_UNDUCK_MSECS			( TIME_TO_UNDUCK_MSECS )		// ms
#define GAMEMOVEMENT_TIME_TO_UNDUCK_MSECS_INV		( GAMEMOVEMENT_DUCK_TIME - GAMEMOVEMENT_TIME_TO_UNDUCK_MSECS )

typedef CBaseHandle EntityHandle_t;

//
// Enumerations for setting player animation.
//
enum PLAYER_ANIM
{
    PLAYER_IDLE ,
    PLAYER_WALK ,
    PLAYER_JUMP ,
    PLAYER_SUPERJUMP ,
    PLAYER_DIE ,
    PLAYER_ATTACK1 ,
    PLAYER_IN_VEHICLE ,

    // TF Player animations
    PLAYER_RELOAD ,
    PLAYER_START_AIMING ,
    PLAYER_LEAVE_AIMING ,
};

enum soundlevel_t
{
    SNDLVL_NONE = 0 ,

    SNDLVL_20dB = 20 ,			// rustling leaves
    SNDLVL_25dB = 25 ,			// whispering
    SNDLVL_30dB = 30 ,			// library
    SNDLVL_35dB = 35 ,
    SNDLVL_40dB = 40 ,
    SNDLVL_45dB = 45 ,			// refrigerator

    SNDLVL_50dB = 50 ,	// 3.9	// average home
    SNDLVL_55dB = 55 ,	// 3.0

    SNDLVL_IDLE = 60 ,	// 2.0
    SNDLVL_60dB = 60 ,	// 2.0	// normal conversation, clothes dryer

    SNDLVL_65dB = 65 ,	// 1.5	// washing machine, dishwasher
    SNDLVL_STATIC = 66 ,	// 1.25

    SNDLVL_70dB = 70 ,	// 1.0	// car, vacuum cleaner, mixer, electric sewing machine

    SNDLVL_NORM = 75 ,
    SNDLVL_75dB = 75 ,	// 0.8	// busy traffic

    SNDLVL_80dB = 80 ,	// 0.7	// mini-bike, alarm clock, noisy restaurant, office tabulator, outboard motor, passing snowmobile
    SNDLVL_TALKING = 80 ,	// 0.7
    SNDLVL_85dB = 85 ,	// 0.6	// average factory, electric shaver
    SNDLVL_90dB = 90 ,	// 0.5	// screaming child, passing motorcycle, convertible ride on frw
    SNDLVL_95dB = 95 ,
    SNDLVL_100dB = 100 ,	// 0.4	// subway train, diesel truck, woodworking shop, pneumatic drill, boiler shop, jackhammer
    SNDLVL_105dB = 105 ,			// helicopter, power mower
    SNDLVL_110dB = 110 ,			// snowmobile drvrs seat, inboard motorboat, sandblasting
    SNDLVL_120dB = 120 ,			// auto horn, propeller aircraft
    SNDLVL_130dB = 130 ,			// air raid siren

    SNDLVL_GUNFIRE = 140 ,	// 0.27	// THRESHOLD OF PAIN, gunshot, jet engine
    SNDLVL_140dB = 140 ,	// 0.2

    SNDLVL_150dB = 150 ,	// 0.2

    SNDLVL_180dB = 180 ,			// rocket launching

                                    // NOTE: Valid soundlevel_t values are 0-255.
                                    //       256-511 are reserved for sounds using goldsrc compatibility attenuation.
};

class CMoveData
{
public:
    bool			m_bFirstRunOfFunctions : 1;
    bool			m_bGameCodeMovedPlayer : 1;
    bool			m_bNoAirControl : 1;

    int	            m_nPlayerHandle;	// edict index on server, client entity handle on client

    int				m_nImpulseCommand;	// Impulse command issued.
    Angle			m_vecViewAngles;	// Command view angles (local space)
    Angle			m_vecAbsViewAngles;	// Command view angles (world space)
    int				m_nButtons;			// Attack buttons.
    int				m_nOldButtons;		// From host_client->oldbuttons;
    float			m_flForwardMove;
    float			m_flSideMove;
    float			m_flUpMove;

    float			m_flMaxSpeed;
    float			m_flClientMaxSpeed;

    // Variables from the player edict (sv_player) or entvars on the client.
    // These are copied in here before calling and copied out after calling.
    Vector			m_vecVelocity;		// edict::velocity		// Current movement direction.
    Angle			m_vecAngles;		// edict::angles
    Angle			m_vecOldAngles;

    // Output only
    float			m_outStepHeight;	// how much you climbed this move
    Vector			m_outWishVel;		// This is where you tried
    Vector			m_outJumpVel;		// This is your jump velocity

                                        // Movement constraints	(radius 0 means no constraint)
    Vector			m_vecConstraintCenter;
    float			m_flConstraintRadius;
    float			m_flConstraintWidth;
    float			m_flConstraintSpeedFactor;
    bool			m_bConstraintPastRadius;		///< If no, do no constraining past Radius.  If yes, cap them to SpeedFactor past radius
    float            m_flUnknown[ 4 ];

    Vector			m_vecAbsOrigin;		// edict::origin
};

class IGameMovement
{
public:
    virtual			~IGameMovement( void )
    {}

   // Process the current movement command
    virtual void	ProcessMovement( CBasePlayer *pPlayer , CMoveData *pMove ) = 0;
    virtual void	Reset( void ) = 0;
    virtual void	StartTrackPredictionErrors( CBasePlayer *pPlayer ) = 0;
    virtual void	FinishTrackPredictionErrors( CBasePlayer *pPlayer ) = 0;
    virtual void	DiffPrint( char const *fmt , ... ) = 0;

    // Allows other parts of the engine to find out the normal and ducked player bbox sizes
    virtual Vector const&	GetPlayerMins( bool ducked ) const = 0;
    virtual Vector const&	GetPlayerMaxs( bool ducked ) const = 0;
    virtual Vector const&   GetPlayerViewOffset( bool ducked ) const = 0;

    virtual bool		IsMovingPlayerStuck( void ) const = 0;
    virtual CBasePlayer *GetMovingPlayer( void ) const = 0;
    virtual void		UnblockPusher( CBasePlayer *pPlayer , CBaseEntity *pPusher ) = 0;

    virtual void SetupMovementBounds( CMoveData *pMove ) = 0;
};

class CGameMovement : public IGameMovement
{
public:
    CBasePlayer * player;
    // Input/Output for this movement
    CMoveData * mv;

    int				m_nOldWaterLevel;
    float			m_flWaterEntryTime;
    int				m_nOnLadder;

    Vector			m_vecForward;
    Vector			m_vecRight;
    Vector			m_vecUp;

    typedef enum
    {
        GROUND = 0 ,
        STUCK ,
        LADDER ,
        LADDER_WEDGE
    } IntervalType_t;

    enum
    {
        // eyes, waist, feet points (since they are all deterministic
        MAX_PC_CACHE_SLOTS = 3 ,
    };

    // Cache used to remove redundant calls to GetPointContents() for water.
    int m_CachedGetPointContents[ MAX_PLAYERS ][ MAX_PC_CACHE_SLOTS ];
    Vector m_CachedGetPointContentsPoint[ MAX_PLAYERS ][ MAX_PC_CACHE_SLOTS ];

    //private:
    bool			m_bSpeedCropped;

    bool			m_bProcessingMovement;
    bool			m_bInStuckTest;

    float			m_flStuckCheckTime[ MAX_PLAYERS + 1 ][ 2 ]; // Last time we did a full test

    ITraceListData	*m_pTraceListData;

    int				m_nTraceCount;
};

class IMoveHelper
{
public:
    // Methods associated with a particular entity
    virtual	char const*		GetName( EntityHandle_t handle ) const = 0;

    // sets the entity being moved
    virtual void	SetHost( CBaseEntity *host ) = 0;

    // Adds the trace result to touch list, if contact is not already in list.
    virtual void	ResetTouchList( void ) = 0;
    virtual bool	AddToTouched( const CGameTrace& tr , const Vector& impactvelocity ) = 0;
    virtual void	ProcessImpacts( void ) = 0;

    // Numbered line printf
    virtual void	Con_NPrintf( int idx , char const* fmt , ... ) = 0;

    // These have separate server vs client impementations
    virtual void	StartSound( const Vector& origin , int channel , char const* sample , float volume , soundlevel_t soundlevel , int fFlags , int pitch ) = 0;
    virtual void	StartSound( const Vector& origin , const char *soundname ) = 0;
    virtual void	PlaybackEventFull( int flags , int clientindex , unsigned short eventindex , float delay , Vector& origin , Vector& angles , float fparam1 , float fparam2 , int iparam1 , int iparam2 , int bparam1 , int bparam2 ) = 0;

    // Apply falling damage to m_pHostPlayer based on m_pHostPlayer->m_flFallVelocity.
    virtual bool	PlayerFallingDamage( void ) = 0;

    // Apply falling damage to m_pHostPlayer based on m_pHostPlayer->m_flFallVelocity.
    virtual void	PlayerSetAnimation( PLAYER_ANIM playerAnim ) = 0;

    virtual IPhysicsSurfaceProps *GetSurfaceProps( void ) = 0;

    virtual bool IsWorldEntity( const CBaseHandle &handle ) = 0;
};

class IPrediction
{
public:
    virtual			~IPrediction( void )
    {};

    virtual void	Init( void ) = 0;
    virtual void	Shutdown( void ) = 0;

    // Run prediction
    virtual void	Update
    (
        int startframe ,				// World update ( un-modded ) most recently Recvd
        bool validframe ,			// Is frame data valid
        int incoming_acknowledged ,	// Last command acknowledged to have been run by server (un-modded)
        int outgoing_command		// Last command (most recent) sent to server (un-modded)
    ) = 0;

    // We are about to get a network update from the server.  We know the update #, so we can pull any
    //  data purely predicted on the client side and transfer it to the new from data state.
    virtual void	PreEntityPacketRecvd( int commands_acknowledged , int current_world_update_packet ) = 0;
    virtual void	PostEntityPacketRecvd( void ) = 0;
    virtual void	PostNetworkDataRecvd( int commands_acknowledged ) = 0;

    virtual void	OnRecvdUncompressedPacket( void ) = 0;

    // The engine needs to be able to access a few predicted values
    virtual void	GetViewOrigin( Vector& org ) = 0;
    virtual void	SetViewOrigin( Vector& org ) = 0;
    virtual void	GetViewAngles( Angle& ang ) = 0;
    virtual void	SetViewAngles( Angle& ang ) = 0;
    virtual void	GetLocalViewAngles( Angle& ang ) = 0;
    virtual void	SetLocalViewAngles( Angle& ang ) = 0;
};

class CPrediction : public IPrediction
{
public:

    bool *FirstTimePredicted()
    {
        return _POffset( 0x48 , bool );
    }

    bool *IsInPrediction()
    {
        return _POffset( 0x8 , bool );
    }
};

#endif