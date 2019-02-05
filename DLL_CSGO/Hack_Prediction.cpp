#include "Includes.hxx"
#include "Main.hxx"

CHackPrediction* HackPrediction = new CHackPrediction();

void CHackPrediction::PreThink( C_BasePlayer* pPlayer , CUserCmd* Cmd )
{
    vecOldEyePos = pPlayer->GetEyePosition();

    Offsets->MoveHelper->SetHost( ( CBaseEntity* ) pPlayer );

    eiSequenceNumber = Cmd->command_number;

    oldframetime = Globals->frametime;
    oldcurtime = Globals->curtime;

    Globals->frametime = EngineClient->IsPaused() ? 0.0f : Globals->interval_per_tick;

    iOldTickBase = *pPlayer->TickBase();
    *pPlayer->TickBase() = GetPredictedServerTick();

    currentcurtime = Globals->curtime = GetPredictedServerTick() * Globals->frametime;

    //Offsets->pPlayerPrediction = pPlayer;
    //_OffsetManualthis( 0x3314 , CUserCmd* , pPlayer ) = Cmd;
}

void CHackPrediction::Think( C_BasePlayer*pPlayer , CUserCmd*Cmd )
{
    bPredicting = true;

    if ( _OffsetManualthis( CBasePlayer::DT_BasePlayer::fFlags() , int , pPlayer ) & FL_FROZEN )
        return;

    Offsets->RunCommand( Prediction.pAddress , pPlayer , Cmd , Offsets->MoveHelper );
    //Prediction.CallVirtualFunction<void , Pointer , Pointer , Pointer , Pointer>( 20 , pPlayer , Cmd , Offsets->MoveHelper , &movedata );
    //GameMovement->ProcessMovement( ( CBasePlayer* ) pPlayer , &movedata );
    //new_FinishMove( Prediction.pAddress , nullptr , pPlayer , Cmd , &movedata );
}

void CHackPrediction::PostThink( C_BasePlayer*pPlayer )
{
    //_OffsetManualthis( 0x3314 , CUserCmd* , pPlayer ) = nullptr;
    //Offsets->pPlayerPrediction = nullptr;

    // Don't mess with the next prediction who will be called after.
    Offsets->MoveHelper->SetHost( nullptr );
    *pPlayer->TickBase() = iOldTickBase;

    Globals->frametime = oldframetime;
    Globals->curtime = oldcurtime;

    bPredicting = false;
}

int CHackPrediction::GetPredictedServerTick()
{
    static int iPredictedTick = 0;

    C_BasePlayer *pLocalPlayer = GetLocalPlayer();

    if ( pLocalPlayer != nullptr )
    {
        iPredictedTick = *GetLocalPlayer()->TickBase();
    }

    return iPredictedTick;
}