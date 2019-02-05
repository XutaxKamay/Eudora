#include "Includes.hxx"
#include "Main.hxx"

__pragma( warning( push ) )
__pragma( warning( disable:4100 ) )

// We do that so we can have the lowest lerp possible.
// Check https://github.com/alliedmodders/hl2sdk/blob/3957adff10fe20d38a62fa8c018340bf2618742b/game/server/gameinterface.cpp#L2844
// To have this: https://github.com/alliedmodders/hl2sdk/blob/d5480b033f080b2363310392fe905d27e6342966/game/server/player_lagcompensation.cpp#L273 , lowest as possible.
// So we have more backtracking time. I've might read wrong, but anyway we could still invert the thing, by setting to cl_interpolate 1 and increase lerp time by playing with
// cl_interp etc, so we have more backtracking time.
// Actual function: https://github.com/alliedmodders/hl2sdk/blob/d5480b033f080b2363310392fe905d27e6342966/game/client/c_baseentity.cpp#L3475

void new_InterpolateServerEntities()
{
    /*static float fCountedTime = 0.0f;
    if ( Globals->curtime > fCountedTime )
    {
        Cvar->FindVar( "sv_client_min_interp_ratio" )->SetValue( -1 );
        Cvar->FindVar( "sv_maxupdaterate" )->SetValue( 10000000 );
        Cvar->FindVar( "sv_minupdaterate" )->SetValue( -1 );

        Cvar->FindVar( "cl_updaterate" )->m_bHasMax = false;
        Cvar->FindVar( "cl_updaterate" )->m_bHasMin = false;
        Cvar->FindVar( "cl_updaterate" )->SetValue( 10000000 );

        Cvar->FindVar( "cl_interp" )->m_bHasMax = false;
        Cvar->FindVar( "cl_interp" )->m_bHasMin = false;
        Cvar->FindVar( "cl_interp" )->SetValue( -1.0f );

        Cvar->FindVar( "cl_interp_ratio" )->m_bHasMax = false;
        Cvar->FindVar( "cl_interp_ratio" )->m_bHasMin = false;
        Cvar->FindVar( "cl_interp_ratio" )->SetValue( 1 );

        fCountedTime = Globals->curtime + 1.0f;
    }*/

    //Cvar->FindVar( "cl_interpolate" )->SetValue( 1 );
    *Offsets->pbShouldInterpolate = false;
    _CallFunction<void>( DetouredFunctions[ D_InterpolateServerEntities ]->pOld );
    //Cvar->FindVar( "cl_interpolate" )->SetValue( 0 );
}

__pragma( warning( pop ) )