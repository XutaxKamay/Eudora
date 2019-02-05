#include "Includes.hxx"
#include "Main.hxx"

__pragma( warning( push ) )
__pragma( warning( disable:4100 ) )

void __fastcall new_SceneEnd( _FASTCALLD )
{
    _CallFunction<void , e_thiscall , Pointer>( DetouredFunctions[ D_SceneEnd ]->pOld , ThisPTR );

    C_BasePlayer* pLocalPlayer = GetLocalPlayer();
    if ( pLocalPlayer != nullptr )
    {
        if ( MovementRecorder->EndZone.ZoneStage < Zone_Computing_Nothing )
        {
            Angle vView;
            EngineClient->GetViewAngles( vView );
            MovementRecorder->EndZone.ComputeBox( pLocalPlayer , vView );
            //MovementRecorder->EndZone.RenderTrace( Color( 255 , 255 , 255 , 255 ) );
        }

        if ( MovementRecorder->EndZone.BoxZone.vPos != Vector()
             && Cvars[ hack_mr_endzone_draw ]->GetBool() )
        {
            MovementRecorder->EndZone.RenderZone( Color( 255 , 255 , 255 , 255 ) );
        }
    }
}

__pragma( warning( pop ) )