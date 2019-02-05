#ifndef HOOKS
#define HOOKS
#pragma once

#include "Hooking.hxx"

#ifndef _DEBUG
#pragma comment(lib,"..\\Release\\Detour.lib")
#else
#pragma comment(lib,"..\\Debug\\Detour.lib")
#endif

#define _FASTCALLD Pointer ThisPTR , Pointer EDX

void __fastcall new_FrameStageNotify( _FASTCALLD , ClientFrameStage_t eStage );
CUserCmd* __fastcall new_CUserCmd_OverLoadedEqual( _FASTCALLD , CUserCmd* Cmd );
int __fastcall new_BaseInterpolatePart1( _FASTCALLD , float &currentTime , Vector &oldOrigin , Angle &oldAngles , int &bNoMoreChanges );
void new_InterpolateServerEntities();
void __fastcall new_PaintTraverse( _FASTCALLD , unsigned int iPanel , bool bForceRePaint , bool bAllowForce );
bool __fastcall new_DoPostScreenSpaceEffects( _FASTCALLD , CViewSetup *pSetup );
bool __fastcall new_C_BaseAnimating_SetupBones( _FASTCALLD , Matrix3x4* pBoneToWorldOut , int nMaxBones , int boneMask , float currentTime );
void __fastcall new_StartLagCompensation( _FASTCALLD , C_BasePlayer* pPlayer , int lagCompensationType , const Vector& weaponPos , const Angle &weaponAngles , float weaponRange );
void __fastcall new_RunSimulation( CPrediction* ThisPTR , Pointer EDX , int current_command , CUserCmd *cmd , C_BasePlayer *localPlayer );
void __fastcall new_Prediction_Update( _FASTCALLD , int startframe , bool validframe , int incoming_acknowledged , int outgoing_command );
void __fastcall new_FinishMove( _FASTCALLD , C_BasePlayer *player , CUserCmd *ucmd , CMoveData *move );
CUserCmd* __fastcall new_GetUserCmd( _FASTCALLD , int iSlot , int sequence_number );
void __fastcall new_CreateMove( _FASTCALLD , int sequence_number , float input_sample_frametime , bool active );
bool __fastcall new_SendNetMsg( _FASTCALLD , INetMessage &msg , bool bForceReliable = false , bool bVoice = false );
bool __fastcall new_WriteUserCmdDeltaBuffer( _FASTCALLD , int unknown , bf_write *buf , int from , int to , bool isnewcommand );
void __fastcall new_DrawModelExecute( _FASTCALLD , IMatRenderContext* ctx , DrawModelState_t& state , ModelRenderInfo_t& pInfo , Matrix3x4* pCustomBoneToWorld );
void __fastcall new_RunCommand( CPrediction* ThisPTR , Pointer EDX , C_BasePlayer* pPlayer , CUserCmd* cmd , IMoveHelper* MoveHelper );
void __fastcall new_SceneEnd( _FASTCALLD );
bool __fastcall new_Buf_WriteString( _FASTCALLD , const char* cString );
bool __fastcall new_C_CreateMove( _FASTCALLD , float , CUserCmd* );
float __fastcall new_DeterminateSpeedKey( _FASTCALLD , Pointer pArg );
void __fastcall new_ApplyMouse( _FASTCALLD , int , Angle& viewangles , CUserCmd *cmd , float mouse_x , float mouse_y );
void ProcessHooks();

enum N_DetouredFunctions
{
	D_FrameStageNotify ,
	D_CUserCmd_OverLoadedEqual ,
	D_C_BaseEntity_BaseInterpolate1 ,
	D_InterpolateServerEntities ,
	D_PaintTraverse ,
	D_DoPostScreenSpaceEffects ,
	D_C_BaseAnimating_SetupBones ,
	D_ApplyMouse ,
	D_DeterminateSpeedKey ,
	D_StartLagCompensation ,
	D_Prediction_Update ,
	D_RunSimulation ,
	D_FinishMove ,
	D_GetUserCmd ,
	D_CreateMove ,
	D_SendNetMsg ,
	D_WriteUserCmdDeltaBuffer ,
	D_DrawModelExecute ,
	D_RunCommand ,
	D_SceneEnd ,
	D_Buf_WriteString ,
	D_C_CreateMove ,
	D_MAX ,
};

extern N_Hook::DetourFunction *DetouredFunctions[ D_MAX ];

extern CCLCMsg_ClientInfo *MsgClientInfo;
extern CCLCMsg_VoiceData *MsgVoiceData;
#endif