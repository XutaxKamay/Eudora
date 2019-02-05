#include "Includes.hxx"
#include "Main.hxx"

// This function is called everytime a client frame stage is finished.
// It can be also used for storing networked variables, or hooking them, depending on wich stage we are.

__pragma( warning( push ) )
__pragma( warning( disable:4100 ) )

void __fastcall new_FrameStageNotify( _FASTCALLD , ClientFrameStage_t eStage )
{
    // https://www.unknowncheats.me/forum/counterstrike-global-offensive/211594-fix-inaccurate-setupbones-target-player-pvs-fix.html

    /*if ( Cvars[ hack_backtrack ]->GetBool() )
    {
        for ( int i = 1; i <= Globals->maxClients; i++ )
        {
            C_BasePlayer* pCurEntity = ( C_BasePlayer* ) ClientEntityList->GetClientEntity( i );
            if ( pCurEntity == nullptr ) continue;

            if ( pCurEntity->IsPlayer() && !pCurEntity->IsLocalPlayer() )
            {
                *( int* ) ( ( uintptr_t ) pCurEntity + 0xA30 ) = Globals->framecount; //we'll skip occlusion checks now
                *( int* ) ( ( uintptr_t ) pCurEntity + 0xA28 ) = 0;//clear occlusion flags
            }
        }

        *Offsets->pbAbsQueriesValid = 0;
        *Offsets->pbAbsRecomputationEnabled = 1;
    }*/

    if ( eStage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_END )
    {
        if ( Cvars[ hack_backtrack ]->GetBool() )
        {
            // Log as soon as we Recvd all the packets from all the networked entities.
            Backtrack->PushBack();
        }

        if ( Cvars[ hack_esp_glow ]->GetBool() )
        {
            C_BasePlayer* pLocalPlayer = GetLocalPlayer();

            if ( pLocalPlayer != nullptr )
            {
                for ( HEX i = MAX_EDICTS; i != -1; i-- )
                {
                    C_BaseEntity *pEntity = ( C_BaseEntity* ) ClientEntityList->GetClientEntity( i );

                    if ( pEntity == nullptr )
                        continue;

					int iEntIndex = pEntity->entindex();

					g_GlowObjectManager.SetShouldRender( iEntIndex , false );

                    ClientClass *ClientC = pEntity->GetClientClass();

                    if ( ClientC == nullptr )
                        continue;

                    if ( ClientC->m_ClassID == ClassId_CBaseViewModel
                         || ClientC->m_ClassID == ClassId_CPredictedViewModel )
                        continue;

                    if ( pEntity->IsLocalPlayer( true ) )
                    {
                        continue;
                    }

                    if ( Cvars[ hack_esp_glow ]->GetInt() == 1 )
                    {
                        if ( _OffsetManualthis( CBaseEntity::DT_BaseEntity::iTeamNum() , int , pEntity )
                             == _OffsetManualthis( CBaseEntity::DT_BaseEntity::iTeamNum() , int , pLocalPlayer ) )
                            continue;
                    }

                    if ( pEntity->IsPlayer() && !pEntity->HasAttachement() )
                    {
                        if ( _OffsetManualthis( CBaseEntity::DT_BaseEntity::iTeamNum() , int , pEntity ) == 3 )
                        {
                            g_GlowObjectManager.SetEntity( iEntIndex , Vector( 0 , 0 , 1 ) , Vector( 0 , 1 , 1 ) , 1.0f , true , false );
                        }
                        else if ( _OffsetManualthis( CBaseEntity::DT_BaseEntity::iTeamNum() , int , pEntity ) == 2 )
                        {
                            g_GlowObjectManager.SetEntity( iEntIndex , Vector( 1 , 0 , 0 ) , Vector( 1 , 1 , 0 ) , 1.0f , true , false );
                        }
                        else
                        {
                            g_GlowObjectManager.SetEntity( iEntIndex , Vector( 1 , 1 , 1 ) , Vector( 1 , 1 , 1 ) , 1.0f , true , false );
                        }
                    }
                    else
                    {
                        if ( Cvars[ hack_esp_glow ]->GetInt() >= 3 )
                            g_GlowObjectManager.SetEntity( iEntIndex , Vector( 1 , 0 , 1 ) , Vector( 1 , 1 , 1 ) , 1.0f , true , false );
                    }
                }
            }
        }
    }

    _CallFunction<void , e_thiscall , Pointer , ClientFrameStage_t>( DetouredFunctions[ D_FrameStageNotify ]->pOld , ThisPTR , eStage );
}

__pragma( warning( pop ) )