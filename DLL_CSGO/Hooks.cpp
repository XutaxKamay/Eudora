#include "Includes.hxx"
#include "Main.hxx"

N_Hook::DetourFunction *DetouredFunctions[ D_MAX ] =
{
  nullptr , nullptr , nullptr , nullptr , nullptr , nullptr
, nullptr , nullptr , nullptr , nullptr , nullptr , nullptr
, nullptr , nullptr , nullptr , nullptr , nullptr , nullptr
, nullptr , nullptr , nullptr
};

void ProcessHooks()
{
    // Initialize hooks.
    N_Hook::Init();

    // Detours the functions that we want to modify.
    PDETOUR_FUNCTION( DetouredFunctions[ D_FrameStageNotify ] , new_FrameStageNotify , BaseClient.VirtualFunction( 37 ) );
    PDETOUR_FUNCTION( DetouredFunctions[ D_CUserCmd_OverLoadedEqual ] , new_CUserCmd_OverLoadedEqual , Offsets->CUserCmdOverLoadedEqual );
    PDETOUR_FUNCTION( DetouredFunctions[ D_C_BaseEntity_BaseInterpolate1 ] , new_BaseInterpolatePart1 , Offsets->pC_BaseEntity_BaseInterpolate1 );
    PDETOUR_FUNCTION( DetouredFunctions[ D_InterpolateServerEntities ] , new_InterpolateServerEntities , Offsets->pInterpolateServerEntities );
    //PDETOUR_FUNCTION( DetouredFunctions[ D_PaintTraverse ] , new_PaintTraverse , Panel.VirtualFunction( 41 ) );
    PDETOUR_FUNCTION( DetouredFunctions[ D_DoPostScreenSpaceEffects ] , new_DoPostScreenSpaceEffects , ClientMode.VirtualFunction( 44 ) );
    PDETOUR_FUNCTION( DetouredFunctions[ D_C_BaseAnimating_SetupBones ] , new_C_BaseAnimating_SetupBones , Offsets->C_BaseAnimating_SetupBones );
    //PDETOUR_FUNCTION( DetouredFunctions[ D_Prediction_Update ] , new_Prediction_Update , Prediction.VirtualFunction( 3 ) );
    //PDETOUR_FUNCTION( DetouredFunctions[ D_RunSimulation ] , new_RunSimulation , Offsets->RunSimulation );
    PDETOUR_FUNCTION( DetouredFunctions[ D_FinishMove ] , new_FinishMove , Prediction.VirtualFunction( 21 ) );
    PDETOUR_FUNCTION( DetouredFunctions[ D_GetUserCmd ] , new_GetUserCmd , Input.VirtualFunction( 8 ) );
    PDETOUR_FUNCTION( DetouredFunctions[ D_CreateMove ] , new_CreateMove , Input.VirtualFunction( 3 ) );
    PDETOUR_FUNCTION( DetouredFunctions[ D_SendNetMsg ] , new_SendNetMsg , Offsets->SendNetMsg );
    PDETOUR_FUNCTION( DetouredFunctions[ D_WriteUserCmdDeltaBuffer ] , new_WriteUserCmdDeltaBuffer , Input.VirtualFunction( 5 ) );
    //PDETOUR_FUNCTION( DetouredFunctions[ D_DrawModelExecute ] , new_DrawModelExecute , ModelRender.VirtualFunction( 21 ) );
    //PDETOUR_FUNCTION( DetouredFunctions[ D_RunCommand ] , new_RunCommand , Offsets->RunCommand );
    PDETOUR_FUNCTION( DetouredFunctions[ D_SceneEnd ] , new_SceneEnd , RenderView.VirtualFunction( 9 ) );
    //PDETOUR_FUNCTION( DetouredFunctions[ D_DeterminateSpeedKey ] , new_DeterminateSpeedKey , _GetModule<Pointer>( TEXT( "client.dll" ) , 0x2B3870 ) );
    //PDETOUR_FUNCTION( DetouredFunctions[ D_ApplyMouse ] , new_ApplyMouse , Input.VirtualFunction( 55 ) );
    //PDETOUR_FUNCTION( DetouredFunctions[ D_Buf_WriteString ] , new_Buf_WriteString , Offsets->Buf_WriteString );
    //PDETOUR_FUNCTION( DetouredFunctions[ D_C_CreateMove ] , new_C_CreateMove , ClientMode.VirtualFunction( 24 ) );

    // Apply the detours.
    N_Hook::ApplyHooks();
}