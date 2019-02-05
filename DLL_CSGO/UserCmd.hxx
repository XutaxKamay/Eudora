#ifndef USERCMD
#define USERCMD
#pragma once

class CUserCmd
{
public:

    virtual ~CUserCmd()
    {}

    CUserCmd()
    {
        Reset();
    }

    void Reset()
    {
        command_number = 0;
        tick_count = 0;
        viewangles.Init();
        aimdirection.Init();
        forwardmove = 0.0f;
        sidemove = 0.0f;
        upmove = 0.0f;
        buttons = 0;
        impulse = 0;
        weaponselect = 0;
        weaponsubtype = 0;
        random_seed = 0;
        mousedx = 0;
        mousedy = 0;
        hasbeenpredicted = false;
        // TrackIR
        headangles.Init();
        headoffset.Init();
        // TrackIR
    }

    CUserCmd&operator=( const CUserCmd& src )
    {
        command_number = src.command_number;
        tick_count = src.tick_count;
        viewangles = src.viewangles;
        forwardmove = src.forwardmove;
        sidemove = src.sidemove;
        upmove = src.upmove;
        buttons = src.buttons;
        impulse = src.impulse;
        weaponselect = src.weaponselect;
        weaponsubtype = src.weaponsubtype;
        random_seed = src.random_seed;
        mousedx = src.mousedx;
        mousedy = src.mousedy;
        hasbeenpredicted = src.hasbeenpredicted;
        headangles = src.headangles;
        headoffset = src.headoffset;

        return *this;
    }

    CUserCmd( const CUserCmd& src )
    {
        *this = src;
    }

    CRC32_t GetChecksum( void ) const
    {
        CRC32_t crc;
        CRC32_Init( &crc );

        CRC32_ProcessBuffer( &crc , &command_number , sizeof( command_number ) );
        CRC32_ProcessBuffer( &crc , &tick_count , sizeof( tick_count ) );
        CRC32_ProcessBuffer( &crc , &viewangles , sizeof( viewangles ) );
        CRC32_ProcessBuffer( &crc , &aimdirection , sizeof( aimdirection ) );
        CRC32_ProcessBuffer( &crc , &forwardmove , sizeof( forwardmove ) );
        CRC32_ProcessBuffer( &crc , &sidemove , sizeof( sidemove ) );
        CRC32_ProcessBuffer( &crc , &upmove , sizeof( upmove ) );
        CRC32_ProcessBuffer( &crc , &buttons , sizeof( buttons ) );
        CRC32_ProcessBuffer( &crc , &impulse , sizeof( impulse ) );
        CRC32_ProcessBuffer( &crc , &weaponselect , sizeof( weaponselect ) );
        CRC32_ProcessBuffer( &crc , &weaponsubtype , sizeof( weaponsubtype ) );
        CRC32_ProcessBuffer( &crc , &random_seed , sizeof( random_seed ) );
        CRC32_ProcessBuffer( &crc , &mousedx , sizeof( mousedx ) );
        CRC32_ProcessBuffer( &crc , &mousedy , sizeof( mousedy ) );
        //CRC32_ProcessBuffer( &crc , &headangles , sizeof( headangles ) );
        //CRC32_ProcessBuffer( &crc , &headoffset , sizeof( headoffset ) );

        CRC32_Final( &crc );
        return crc;
    }

    // For matching server and client commands for debugging
    int		command_number;

    // the tick the client created this command
    int		tick_count;

    // Player instantaneous view angles.
    Angle	viewangles;

    Vector	aimdirection;

    // Intended velocities
    //	forward velocity.
    float	forwardmove;
    //  sideways velocity.
    float	sidemove;
    //  upward velocity.
    float	upmove;
    // Attack button states
    int		buttons;
    // Impulse command issued.
    byte    impulse;
    // Current weapon id
    int		weaponselect;
    int		weaponsubtype;

    int		random_seed;	// For shared random functions

    short	mousedx;		// mouse accum in x from create move
    short	mousedy;		// mouse accum in y from create move

                            // Client only, tracks whether we've predicted this command at least once
    bool	hasbeenpredicted;

    Angle   headangles;
    Vector  headoffset;
};

#endif