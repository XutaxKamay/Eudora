#include "Includes.hxx"
#include "Main.hxx"

__pragma( warning( push ) )
__pragma( warning( disable:4100 ) )

// We disable interpolation only for others players.
// We need to disable it for now to use the simulation time of players on the tick count that is managed by lag compensation, so we can get accurate hits.

int __fastcall new_BaseInterpolatePart1( _FASTCALLD , float &currentTime , Vector &oldOrigin , Angle &oldAngles , int &bNoMoreChanges )
{
    *Offsets->pbShouldInterpolate = true;

    if ( Cvars[ hack_backtrack ]->GetBool() )
    {
        C_BaseEntity *Entity = ( C_BaseEntity* ) ThisPTR;

        C_BasePlayer *LocalPlayer = GetLocalPlayer();

        if ( LocalPlayer != nullptr )
        {
            if ( _OffsetManualthis( CBasePlayer::DT_BasePlayer::iObserverMode() , int , LocalPlayer ) == OBS_MODE_NONE )
            {
                if ( Entity->IsPlayer() && !Entity->IsLocalPlayer() )
                {
                    C_BasePlayer* pPlayer = ( C_BasePlayer* ) Entity;

                    if ( Backtrack->IsReadyForBacktrack( pPlayer ) )
                    {
                        *Offsets->pbShouldInterpolate = false;
                    }
                }
            }
        }
    }

    int iRet = _CallFunction<int , e_thiscall , Pointer , float& , Vector& , Angle& , int&>
        ( DetouredFunctions[ D_C_BaseEntity_BaseInterpolate1 ]->pOld , ThisPTR , currentTime , oldOrigin , oldAngles , bNoMoreChanges );

    return iRet;
}

__pragma( warning( pop ) )