#ifndef GLOBALSVAR
#define GLOBALSVAR
#pragma once

#define TICK_INTERVAL			(Globals->interval_per_tick)

#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )		( TICK_INTERVAL *( t ) )
#define ROUND_TO_TICKS( t )		( TICK_INTERVAL * TIME_TO_TICKS( t ) )
#define TICK_NEVER_THINK		(-1)

//-----------------------------------------------------------------------------
// Purpose: Global variables used by shared code
//-----------------------------------------------------------------------------
class CGlobalVarsBase
{
public:

    CGlobalVarsBase( bool bIsClient );

    // This can be used to filter debug output or to catch the client or server in the act.
    bool IsClient() const;

    bool IsRemoteClient() const;

    // for encoding m_flSimulationTime, m_flAnimTime
    int GetNetworkBase( int nTick , int nEntity );

    // Absolute time (per frame still - Use Plat_FloatTime() for a high precision real time
    //  perf clock, but not that it doesn't obey host_timescale/host_framerate)
    float			realtime;
    // Absolute frame counter - continues to increase even if game is paused
    int				framecount;
    // Non-paused frametime
    float			absoluteframetime;

    float			absoluteframestarttimestddev;

    // Current time
    //
    // On the client, this (along with tickcount) takes a different meaning based on what
    // piece of code you're in:
    //
    //   - While receiving network packets (like in PreDataUpdate/PostDataUpdate and proxies),
    //     this is set to the SERVER TICKCOUNT for that packet. There is no interval between
    //     the server ticks.
    //     [server_current_Tick * tick_interval]
    //
    //   - While rendering, this is the exact client clock
    //     [client_current_tick * tick_interval + interpolation_amount]
    //
    //   - During prediction, this is based on the client's current tick:
    //     [client_current_tick * tick_interval]
    float			curtime;

    // Time spent on last server or client frame (has nothing to do with think intervals)
    float			frametime;
    // current maxplayers setting
    int				maxClients;

    // Simulation ticks - does not increase when game is paused
    int				tickcount;

    // Simulation tick interval
    float			interval_per_tick;

    // interpolation amount ( client-only ) based on fraction of next tick which has elapsed
    float			interpolation_amount;
    int				simTicksThisFrame;

    int				network_protocol;

    // current saverestore data
    Pointer         pSaveData;

    // Set to true in client code.
    bool			m_bClient;

    bool			m_bRemoteClient;

    // 100 (i.e., tickcount is rounded down to this base and then the "delta" from this base is networked
    int				nTimestampNetworkingBase;
    // 32 (entindex() % nTimestampRandomizeWindow ) is subtracted from gpGlobals->tickcount to set the networking basis, prevents
    //  all of the entities from forcing a new PackedEntity on the same tick (i.e., prevents them from getting lockstepped on this)
    int				nTimestampRandomizeWindow;
};

enum MapLoadType_t
{
    MapLoad_NewGame = 0 ,
    MapLoad_LoadGame ,
    MapLoad_Transition ,
    MapLoad_Background ,
};

class CGlobalVars : public CGlobalVarsBase
{
public:

    CGlobalVars( bool bIsClient );

public:

    // Current map
    int		        mapname;
    int		        mapGroupName;
    int				mapversion;
    int		        startspot;
    MapLoadType_t	eLoadType;		// How the current map was loaded
    bool			bMapLoadFailed;	// Map has failed to load, we need to kick back to the main menu

                                    // game specific flags
    bool			deathmatch;
    bool			coop;
    bool			teamplay;
    // current maxentities
    int				maxEntities;

    int				serverCount;
    Pointer			pEdicts;
};

#endif