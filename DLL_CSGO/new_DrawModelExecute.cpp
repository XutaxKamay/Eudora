#include "Includes.hxx"
#include "Main.hxx"

void __fastcall new_DrawModelExecute( _FASTCALLD , IMatRenderContext* ctx , DrawModelState_t& state , ModelRenderInfo_t& pInfo , Matrix3x4* pCustomBoneToWorld )
{
    //C_BasePlayer* LocalPlayer = GetLocalPlayer();

    //if ( pInfo.flags == STUDIO_RENDER && LocalPlayer != nullptr )
    //{
    //    IClientUnknown* pUnknown = state.m_pRenderable->GetIClientUnknown();

    //    if ( pUnknown != nullptr )
    //    {
    //        C_BaseEntity* pEntity = pUnknown->GetBaseEntity();

    //        if ( pEntity != nullptr
    //             && pEntity->IsPlayer() )
    //        {
    //            if ( _OffsetManualthis( CBaseEntity::DT_BaseEntity::iTeamNum() , int , pEntity ) != _OffsetManualthis( CBaseEntity::DT_BaseEntity::iTeamNum() , int , GetLocalPlayer() ) )
    //            {
    //                float color[] = { 0.0f , 0.0f , 0.0f };
    //                RenderView->SetColorModulation( color );
    //                RenderView->SetBlend( 1.0f );

    //                ModelRender->ForcedMaterialOverride( Mat_VertexGhostSelectedIgnoreZ , OverrideType_t::OVERRIDE_NORMAL , 0 );

    //                _CallFunction<void , Pointer , Pointer , DrawModelState_t& , ModelRenderInfo_t& , Matrix3x4*>( e_thiscall , DetouredFunctions[ D_DrawModelExecute ]->pOld , ThisPTR , ctx , state , pInfo , pCustomBoneToWorld );

    //                ModelRender->ForcedMaterialOverride( nullptr , OverrideType_t::OVERRIDE_NORMAL , 0 );
    //            }
    //        }
    //    }
    //}

    _CallFunction<void , e_thiscall , Pointer , Pointer , DrawModelState_t& , ModelRenderInfo_t& , Matrix3x4*>( DetouredFunctions[ D_DrawModelExecute ]->pOld , ThisPTR , ctx , state , pInfo , pCustomBoneToWorld );

    if ( Cvars[ hack_backtrack ]->GetInt() > 1 )
    {
        bool bCanRender = false;

        if ( pInfo.flags == STUDIO_RENDER )
        {
            bCanRender = true;
        }

        if ( bCanRender &&  pInfo.pRenderable->GetIClientUnknown() != nullptr )
        {
            C_BaseEntity* pEntity = ( C_BaseEntity* ) pInfo.pRenderable->GetIClientUnknown()->GetBaseEntity();

            if ( pEntity != nullptr )
            {
                if ( pEntity->IsPlayer() )
                {
                    if ( Backtrack->IsReadyForBacktrack( ( C_BasePlayer* ) pEntity ) )
                    {
                        if ( ctx != nullptr )
                        {
                            int iPlayerIndex = pEntity->entindex();

                            CPlayerBacktrack* _PlayerRecord = Backtrack->PlayerRecord[ iPlayerIndex ];

                            if ( Cvars[ hack_backtrack ]->GetInt() > 2 )
                            {
                                for ( int iHistory = MAX_HISTORY_BACKTRACK - 1; iHistory != -1; iHistory-- )
                                {
                                    int iSlot = Backtrack->GetHistorySlot( iPlayerIndex , iHistory );

                                    if ( iSlot <= 0 )
                                        continue;

                                    if ( !_PlayerRecord->bIsValid[ iSlot ] )
                                        continue;

									LagRecord *LRecord = &_PlayerRecord->LagRecords[ iSlot ];

                                    if ( !( iHistory == Backtrack->iAdjustedPlayerHistory
                                         &&  Backtrack->iAdjustedPlayerIndex == iPlayerIndex ) )
                                    {
                                        _PlayerRecord->bIsShowModel = true;

                                        float color[] = { Cvars[ hack_backtrack_model_r ]->GetFloat() ,  Cvars[ hack_backtrack_model_g ]->GetFloat() ,  Cvars[ hack_backtrack_model_b ]->GetFloat() };
                                        RenderView->SetColorModulation( color );
                                        RenderView->SetBlend( Cvars[ hack_backtrack_model_a ]->GetFloat() );

                                        ModelRender->ForcedMaterialOverride( Mat_VertexGhostIgnoreZ );

                                        _CallFunction<void , e_thiscall , Pointer , Pointer , DrawModelState_t& , ModelRenderInfo_t& , Matrix3x4*>( DetouredFunctions[ D_DrawModelExecute ]->pOld , ThisPTR , ctx , state , pInfo , LRecord->m_RenderMatrix );

                                        ModelRender->ForcedMaterialOverride( nullptr );

                                        _PlayerRecord->bIsShowModel = false;
                                    }
                                }
                            }

                            if ( Backtrack->iAdjustedPlayerIndex != -1 && Backtrack->iAdjustedPlayerHistory != -1 )
                            {
                                int iSlot = Backtrack->GetHistorySlot( Backtrack->iAdjustedPlayerIndex , Backtrack->iAdjustedPlayerHistory );

                                if ( iSlot == -1 )
                                    return;

                                if ( !_PlayerRecord->bIsValid[ iSlot ] )
                                    return;

                                CPlayerBacktrack* _PlayerRecord = Backtrack->PlayerRecord[ Backtrack->iAdjustedPlayerIndex ];

                                LagRecord *LRecord = &_PlayerRecord->LagRecords[ iSlot ];

                                if ( LRecord != nullptr )
                                {
                                    _PlayerRecord->bIsShowModel = true;

                                    float color[] = { Cvars[ hack_backtrack_f_model_r ]->GetFloat() ,  Cvars[ hack_backtrack_f_model_g ]->GetFloat() ,  Cvars[ hack_backtrack_f_model_b ]->GetFloat() };
                                    RenderView->SetColorModulation( color );
                                    RenderView->SetBlend( Cvars[ hack_backtrack_f_model_a ]->GetFloat() );

                                    ModelRender->ForcedMaterialOverride( Mat_VertexGhostSelectedIgnoreZ );

                                    _CallFunction<void , e_thiscall , Pointer , Pointer , DrawModelState_t& , ModelRenderInfo_t& , Matrix3x4*>( DetouredFunctions[ D_DrawModelExecute ]->pOld , ThisPTR , ctx , state , pInfo , LRecord->m_RenderMatrix );

                                    ModelRender->ForcedMaterialOverride( nullptr );

                                    _PlayerRecord->bIsShowModel = false;
                                }
                            }
                        }
                    }
                }
            }
        }

        if ( pInfo.flags == ( STUDIO_RENDER | STUDIO_NOSHADOWS | STUDIO_TRANSPARENCY | STUDIO_SKIP_FLEXES | STUDIO_DONOTMODIFYSTENCILSTATE
             | STUDIO_NOLIGHTING_OR_CUBEMAP | STUDIO_SKIP_DECALS ) )
        {
            ModelRender->ForcedMaterialOverride( Mat_Glow );
        }
    }
}