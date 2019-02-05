#include "Includes.hxx"
#include "Main.hxx"

__pragma( warning( push ) )
__pragma( warning( disable:4100 ) )

bool g_bIsCreateMove = false;

void __fastcall new_CreateMove( _FASTCALLD , int sequence_number , float input_sample_frametime , bool active )
{
    Prediction->Update( _OffsetManualthis( 0x174 , int , Offsets->pClientState )
                        , _OffsetManualthis( 0x174 , int , Offsets->pClientState ) > 0
                        , _OffsetManualthis( 0x4CB4 , int , Offsets->pClientState )
                        , sequence_number - 1 );

    g_bIsCreateMove = true;
    //sequence_number += 1;
    //Backtrack->UpdateLerpTime();
    // Setup again our commands after predicting for our next position used for making accurate aimbots? (due to PostThink called after runcommand)
    _CallFunction<void , e_thiscall , Pointer , int , float , bool>( DetouredFunctions[ D_CreateMove ]->pOld , ThisPTR , sequence_number , input_sample_frametime , active );

    g_bIsCreateMove = false;
}

bool __fastcall new_C_CreateMove( _FASTCALLD , float flTime , CUserCmd* Cmd )
{
    if ( !Cmd->command_number )
    {
        return _CallFunction<bool , e_thiscall , Pointer , float , CUserCmd*>( DetouredFunctions[ D_C_CreateMove ]->pOld , ThisPTR , flTime , Cmd );
    }

    puHEX pEBP;
    __asm mov pEBP , ebp;
    bool& bSendPacket = *( bool* ) ( *pEBP - 0x1C );
    bSendPacket = false;

    return _CallFunction<bool , e_thiscall , Pointer , float , CUserCmd*>( DetouredFunctions[ D_C_CreateMove ]->pOld , ThisPTR , flTime , Cmd );
}

float g_flSpeed = -1.0f;

float __fastcall new_DeterminateSpeedKey( _FASTCALLD , Pointer pArg )
{
    float flSpeed = _CallFunction<float , e_thiscall , Pointer , Pointer>( DetouredFunctions[ D_DeterminateSpeedKey ]->pOld , ThisPTR , pArg );

    __asm
    {
        movss g_flSpeed , xmm0;
    }

    return flSpeed;
}

void __fastcall new_ApplyMouse( _FASTCALLD , int iSlot , Angle& viewangles , CUserCmd *cmd , float mouse_x , float mouse_y )
{
	/*
    static ConVar* m_yaw = Cvar->FindVar( "m_yaw" );
    static ConVar* sv_friction = Cvar->FindVar( "sv_friction" );

    static float flPerfectDifAIRAngleGain = -1.0f;

    static int iButtons = 0;

    if ( g_bIsCreateMove )
    {
        C_BasePlayer* pLocalPlayer = GetLocalPlayer();

        if ( pLocalPlayer != nullptr )
        {
            Vector vecVelocity = _OffsetManualthis( CBasePlayer::DT_BasePlayer::DT_LocalPlayerExclusive::vecVelocity_0() , Vector , pLocalPlayer );

            flPerfectDifAIRAngleGain = AngNormalize<180>( RADTODEG( atan2f( 30.0f , vecVelocity.Length2D() ) ) );

            iButtons = Input->GetButtonBits( 0 );
        }
    }

	if ( flPerfectDifAIRAngleGain != -1.0f && ( iButtons & IN_JUMP ) )
	{
		float realmouse_x = mouse_x * m_yaw->GetFloat();
		float gainmouse_x = flPerfectDifAIRAngleGain * g_flSpeed;

		if ( abs( realmouse_x ) > abs( gainmouse_x ) )
		{
			mouse_x = gainmouse_x;
		}
	}
	*/

    _CallFunction<void , e_thiscall , Pointer , int , Angle& , CUserCmd* , float , float>( DetouredFunctions[ D_ApplyMouse ]->pOld , ThisPTR , iSlot , viewangles , cmd , mouse_x , mouse_y );
}

__pragma( warning( pop ) )