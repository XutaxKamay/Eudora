#include "Includes.hxx"
#include "Main.hxx"

__pragma( warning( push ) )
__pragma( warning( disable:4100 ) )

bool __fastcall new_C_BaseAnimating_SetupBones( _FASTCALLD , Matrix3x4* pBoneToWorldOut , int nMaxBones , int boneMask , float currentTime )
{
	IClientRenderable *ClientRenderable = ( IClientRenderable* ) ThisPTR;
	C_BaseAnimating *BaseAnimating = ( C_BaseAnimating* ) ClientRenderable->GetIClientUnknown()->GetBaseEntity();

	_OffsetManualthis( 0x64 , unsigned short , ClientRenderable ) |= ENTCLIENTFLAG_DONTUSEIK;
	if ( _OffsetManualthis( 0x265C , Pointer , ClientRenderable ) != nullptr )
	{
		MemAllocValve->Free( _OffsetManualthis( 0x265C , Pointer , ClientRenderable ) );
		_OffsetManualthis( 0x265C , Pointer , ClientRenderable ) = nullptr;
	}

	//*Prediction->IsInPrediction() = false;

	C_BasePlayer* LocalPlayer = GetLocalPlayer();

	if ( Cvars[ hack_backtrack ]->GetBool() )
	{
		if ( LocalPlayer != nullptr
			 && ( _OffsetManualthis( CBasePlayer::DT_BasePlayer::iObserverMode() , int , LocalPlayer ) == OBS_MODE_NONE ) )
		{
			if ( Globals->frametime != FLT_MAX && BaseAnimating->IsPlayer() && Backtrack->IsReadyForBacktrack( ( C_BasePlayer* ) BaseAnimating ) )
				*BaseAnimating->MostRecentBoneCounter() = *Offsets->iModelBoneCounter;
		}
	}

	//float frametime = Globals->frametime;
	//Globals->frametime = FLT_MAX;

	bool bRet = _CallFunction<bool , e_thiscall , Pointer , Matrix3x4* , int , int , float>( DetouredFunctions[ D_C_BaseAnimating_SetupBones ]->pOld
																							 , ThisPTR , pBoneToWorldOut , nMaxBones , boneMask , currentTime );
	//Globals->frametime = frametime;

	return bRet;
}

__pragma( warning( pop ) )