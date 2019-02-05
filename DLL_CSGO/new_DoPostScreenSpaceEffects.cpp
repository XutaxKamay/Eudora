#include "Includes.hxx"
#include "Main.hxx"

__pragma( warning( push ) )
__pragma( warning( disable:4100 ) )

bool __fastcall new_DoPostScreenSpaceEffects( _FASTCALLD , CViewSetup *pSetup )
{
	{
		if ( !EngineClient->IsTakingScreenshot() )
		{
			if ( Cvars[ hack_backtrack ]->GetBool() )
			{
				int iPlayerAdjusted = -1 , iPlayerChosenHistory = -1 , iLastChosenI = -1;

				for ( HEX i = Globals->maxClients; i != 0; i-- )
				{
					C_BasePlayer* pPlayer = ( C_BasePlayer* ) ClientEntityList->GetClientEntity( i );

					if ( pPlayer == nullptr )
						continue;

					if ( !Backtrack->IsReadyForBacktrack( pPlayer ) )
						continue;

					int iPlayerIndex = pPlayer->entindex();

					CPlayerBacktrack* PlayerRecord = Backtrack->PlayerRecord[ iPlayerIndex ];

					for ( int iHistory = MAX_HISTORY_BACKTRACK - 1; iHistory != 0; iHistory-- )
					{
						int iSlot = Backtrack->GetHistorySlot( iPlayerIndex , iHistory );

						if ( iSlot == -1 )
							continue;

						if ( !PlayerRecord->bIsValid[ iSlot ] )
							continue;

						if ( iHistory == Backtrack->iAdjustedPlayerHistory
							 && Backtrack->iAdjustedPlayerIndex == iPlayerIndex )
						{
							iPlayerAdjusted = Backtrack->iAdjustedPlayerIndex;
							iPlayerChosenHistory = iSlot;
							iLastChosenI = i;
							continue;
						}

						LagRecord *LRecord = &PlayerRecord->LagRecords[ iSlot ];

						bool bCanContinue = false;
						ModelRenderInfo_t Info;
						DrawModelState_t State;
						Backtrack->PreRender( pPlayer , State , Info , LRecord , i , bCanContinue );

						if ( bCanContinue )
						{
							IMatRenderContext* RenderContext = MaterialSystem->GetRenderContext();

							if ( RenderContext == nullptr )
								continue;

							if ( Cvars[ hack_backtrack ]->GetInt() > 2 )
							{
								float color[] = { Cvars[ hack_backtrack_model_r ]->GetFloat() ,  Cvars[ hack_backtrack_model_g ]->GetFloat() ,  Cvars[ hack_backtrack_model_b ]->GetFloat() };
								RenderView->SetColorModulation( color );
								RenderView->SetBlend( Cvars[ hack_backtrack_model_a ]->GetFloat() );
								ModelRender->ForcedMaterialOverride( Mat_VertexGhostIgnoreZ );
								ModelRender->DrawModelExecute( RenderContext , State , Info , LRecord->m_RenderMatrix );
								ModelRender->ForcedMaterialOverride( nullptr );
							}

							Backtrack->PostRender( pPlayer , State , Info );
						}
					}
				}

				if ( iLastChosenI != -1 )
				{
					C_BasePlayer* pPlayer = ( C_BasePlayer* ) ClientEntityList->GetClientEntity( iLastChosenI );

					if ( pPlayer != nullptr )
					{
						CPlayerBacktrack* _PlayerRecord = Backtrack->PlayerRecord[ iPlayerAdjusted ];

						int iSlot = iPlayerChosenHistory;

						if ( iSlot != -1 )
						{
							if ( _PlayerRecord->bIsValid[ iSlot ] )
							{
								LagRecord *LRecord = &_PlayerRecord->LagRecords[ iSlot ];

								if ( LRecord != nullptr )
								{
									bool bCanContinue = false;
									ModelRenderInfo_t Info;
									DrawModelState_t State;

									Backtrack->PreRender( pPlayer , State , Info , LRecord , iLastChosenI , bCanContinue );

									if ( bCanContinue )
									{
										IMatRenderContext* RenderContext = MaterialSystem->GetRenderContext();

										if ( RenderContext != nullptr )
										{
											float color[] = { Cvars[ hack_backtrack_f_model_r ]->GetFloat() ,  Cvars[ hack_backtrack_f_model_g ]->GetFloat() ,  Cvars[ hack_backtrack_f_model_b ]->GetFloat() };
											RenderView->SetColorModulation( color );

											RenderView->SetBlend( Cvars[ hack_backtrack_f_model_a ]->GetFloat() );
											ModelRender->ForcedMaterialOverride( Mat_VertexGhostSelectedIgnoreZ );
											ModelRender->DrawModelExecute( RenderContext , State , Info , LRecord->m_RenderMatrix );

											ModelRender->ForcedMaterialOverride( nullptr );
										}

										Backtrack->PostRender( pPlayer , State , Info );
									}
								}
							}
						}
					}
				}
			}

			if ( Cvars[ hack_esp_glow ]->GetBool() )
			{
				g_GlowObjectManager.RenderGlowEffects( pSetup );

				/*CGlowObjectManager_CSGO* GlowObjectManager = Offsets->GlowObjectManager;

				for ( int i = 0; i < GlowObjectManager->m_GlowObjectDefinitions.Count(); i++ )
				{
				CGlowObjectManager_CSGO::GlowObjectDefinition_t* GlowEntity = &GlowObjectManager->m_GlowObjectDefinitions[ i ];
				C_BaseEntity* pEntity = GlowEntity->getEnt();

				if ( pEntity == nullptr )
				continue;

				int iIndex = pEntity->entindex();

				if ( iIndex > 0 && iIndex <= MAX_PLAYERS )
				{
				int iTeam = _OffsetManualthis( CBaseEntity::DT_BaseEntity::iTeamNum() , int , pEntity );

				if ( iTeam == 2 )
				{
				GlowEntity->Set( 1 , 0.5f , 0 , 1 );
				}
				else if ( iTeam == 3 )
				{
				GlowEntity->Set( 0 , 0.5f , 1 , 1 );
				}
				else
				{
				GlowEntity->Set( 1 , 1 , 1 , 1 );
				}
				}
				else
				GlowEntity->Set( 1 , 1 , 1 , 1 );
				}*/
			}
		}
	}

	bool bSetup = _CallFunction<bool , e_thiscall , Pointer , CViewSetup *>( DetouredFunctions[ D_DoPostScreenSpaceEffects ]->pOld , ThisPTR , pSetup );

	return bSetup;
}

__pragma( warning( pop ) )