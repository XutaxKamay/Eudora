#include "Includes.hxx"
#include "Main.hxx"

__pragma( warning( push ) )
__pragma( warning( disable:4100 ) )

void __fastcall new_StartLagCompensation( _FASTCALLD , C_BasePlayer* pPlayer , int lagCompensationType , const Vector& weaponPos , const Angle &weaponAngles , float weaponRange )
{
    _CallFunction<void , e_thiscall , Pointer , Pointer , int , const Vector& , const Angle& , float >
        ( DetouredFunctions[ D_StartLagCompensation ]->pOld , ThisPTR , pPlayer , lagCompensationType , weaponPos , weaponAngles , weaponRange );

    CUserCmd *Cmd = *( CUserCmd** ) ( ( HEX ) pPlayer + 0xF60 );
    CGlobalVars *GlobalsServer = *( CGlobalVars** ) ( _GetModule( TEXT( "server.dll" ) ) + 0x922DC4 );

    if ( GlobalsServer != nullptr )
        EngineClient->Con_NPrintf( _CallFunction<int , e_thiscall , Pointer>( _GetModule<Pointer>( TEXT( "server.dll" ) , 0x13E790 ) , pPlayer )
                                   , "Server %i Client %i %f %i" , TIME_TO_TICKS( GlobalsServer->curtime ) , Cmd->tick_count , *( float* ) ( ( HEX ) pPlayer + 0xBF4 )
                                   , _CallVirtualFunction<int>( pPlayer , 0x7D4 / 4 ) );
}

__pragma( warning( pop ) )