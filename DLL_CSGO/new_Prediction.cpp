#include "Includes.hxx"
#include "Main.hxx"

__pragma( warning( push ) )
__pragma( warning( disable:4100 ) )

void __fastcall new_RunSimulation( CPrediction* ThisPTR , Pointer EDX , int current_command , CUserCmd *cmd , C_BasePlayer *localPlayer )
{
    _CallFunction<void , e_thiscall , CPrediction* , int , CUserCmd* , C_BasePlayer*>( DetouredFunctions[ D_RunSimulation ]->pOld , ThisPTR , current_command , cmd , localPlayer );
}

void __fastcall new_Prediction_Update( _FASTCALLD , int startframe , bool validframe , int incoming_acknowledged , int outgoing_command )
{
    _CallFunction<void , e_thiscall , Pointer , int , bool , int , int>( DetouredFunctions[ D_Prediction_Update ]->pOld , ThisPTR , startframe , validframe , incoming_acknowledged , outgoing_command );
}

void __fastcall new_FinishMove( _FASTCALLD , C_BasePlayer *player , CUserCmd *ucmd , CMoveData *move )
{
    player->SetAbsVelocity( move->m_vecVelocity + _OffsetManualthis( CBasePlayer::DT_BasePlayer::DT_LocalPlayerExclusive::vecBaseVelocity() , Vector , player ) );
    _CallFunction<void , e_thiscall , Pointer , Pointer , Pointer , Pointer>( DetouredFunctions[ D_FinishMove ]->pOld , ThisPTR , player , ucmd , move );
}

void __fastcall new_RunCommand( CPrediction* ThisPTR , Pointer EDX , C_BasePlayer* pPlayer , CUserCmd* cmd , IMoveHelper* MoveHelper )
{

    _CallFunction<void , e_thiscall , Pointer , Pointer , Pointer , Pointer>( DetouredFunctions[ D_RunCommand ]->pOld , ThisPTR , pPlayer , cmd , MoveHelper );

    /*if ( HackPrediction->bPredicting )
    {
        if ( Globals->frametime > 0.0f )
            *pPlayer->TickBase() -= 1;
    }*/
}

__pragma( warning( pop ) )