#include "Includes.hxx"
#include "Main.hxx"

inline bool CGameTrace::DidHit() const
{
    return fraction < 1 || allsolid || startsolid;
}

int GetSplitScreenPlayerSlot()
{
    IClientPanel* pClientModeViewPort = *( IClientPanel ** ) ( ( HEX ) ClientMode.pAddress + 0x18 );

    int nSplitScreenPlayerSlot = Panel->GetMessageContextId( pClientModeViewPort->GetVPanel() );

    return nSplitScreenPlayerSlot;
}

C_BaseEntity* EntityFromEntityHandle( const IHandleEntity* pHandleEntity )
{
    IClientUnknown *pUnk = ( IClientUnknown* ) pHandleEntity;
    return pUnk->GetBaseEntity();
}

bool StandardFilterRules( IHandleEntity *pHandleEntity , int fContentsMask )
{
    C_BaseEntity *pCollide = EntityFromEntityHandle( pHandleEntity );

    // Static prop case...
    if ( !pCollide )
        return true;

    SolidType_t solid = _OffsetManualthis( CBaseEntity::DT_BaseEntity::DT_CollisionProperty::nSolidType() , SolidType_t , pCollide );
    const model_t *pModel = pCollide->GetModel();

    if ( ( pModel->studio != mod_brush ) || ( solid != SOLID_BSP && solid != SOLID_VPHYSICS ) )
    {
        if ( ( fContentsMask & CONTENTS_MONSTER ) == 0 )
            return false;
    }

    // This code is used to cull out tests against see-thru entities
    if ( !( fContentsMask & CONTENTS_WINDOW ) )
    {
        bool bIsTranslucent = ModelInfo->IsTranslucent( pModel );
        bool bIsTwoPass = ModelInfo->IsTranslucentTwoPass( pModel );
        if ( bIsTranslucent && !bIsTwoPass )
            return false;
    }

    // FIXME: this is to skip BSP models that are entities that can be
    // potentially moved/deleted, similar to a monster but doors don't seem to
    // be flagged as monsters
    // FIXME: the FL_WORLDBRUSH looked promising, but it needs to be set on
    // everything that's actually a worldbrush and it currently isn't
    if ( !( fContentsMask & CONTENTS_MOVEABLE ) && ( _OffsetManualthis( 0x258 , unsigned short , pCollide ) == MOVETYPE_PUSH ) )// !(touch->flags & FL_WORLDBRUSH) )
        return false;

    return true;
}

bool PassServerEntityFilter( const IHandleEntity *pTouch , const IHandleEntity *pPass )
{
    if ( !pPass )
        return true;

    if ( pTouch == pPass )
        return false;

    C_BaseEntity *pEntTouch = EntityFromEntityHandle( pTouch );
    C_BaseEntity *pEntPass = EntityFromEntityHandle( pPass );

    if ( !pEntTouch || !pEntPass )
        return true;

    // don't clip against own missiles
    if ( pEntTouch->GetOwnerEntity() == pEntPass )
        return false;

    // don't clip against owner
    if ( pEntPass->GetOwnerEntity() == pEntTouch )
        return false;

    return true;
}

bool ShouldCollide( int collisionGroup0 , int collisionGroup1 )
{
    if ( collisionGroup0 > collisionGroup1 )
    {
        // swap so that lowest is always first
        std::swap( collisionGroup0 , collisionGroup1 );
    }

    if ( ( collisionGroup0 == COLLISION_GROUP_PLAYER || collisionGroup0 == COLLISION_GROUP_PLAYER_MOVEMENT ) &&
         collisionGroup1 == COLLISION_GROUP_PUSHAWAY )
    {
        return false;
    }

    if ( collisionGroup0 == COLLISION_GROUP_DEBRIS && collisionGroup1 == COLLISION_GROUP_PUSHAWAY )
    {
        // let debris and multiplayer objects collide
        return true;
    }

    // Only let projectile blocking debris collide with projectiles
    if ( collisionGroup0 == COLLISION_GROUP_PROJECTILE && collisionGroup1 == COLLISION_GROUP_DEBRIS_BLOCK_PROJECTILE )
        return true;

    if ( collisionGroup0 == COLLISION_GROUP_DEBRIS_BLOCK_PROJECTILE || collisionGroup1 == COLLISION_GROUP_DEBRIS_BLOCK_PROJECTILE )
        return false;

    // --------------------------------------------------------------------------
    // NOTE: All of this code assumes the collision groups have been sorted!!!!
    // NOTE: Don't change their order without rewriting this code !!!
    // --------------------------------------------------------------------------

    // Don't bother if either is in a vehicle...
    if ( ( collisionGroup0 == COLLISION_GROUP_IN_VEHICLE ) || ( collisionGroup1 == COLLISION_GROUP_IN_VEHICLE ) )
        return false;

    if ( ( collisionGroup1 == COLLISION_GROUP_DOOR_BLOCKER ) && ( collisionGroup0 != COLLISION_GROUP_NPC ) )
        return false;

    if ( ( collisionGroup0 == COLLISION_GROUP_PLAYER ) && ( collisionGroup1 == COLLISION_GROUP_PASSABLE_DOOR ) )
        return false;

    if ( collisionGroup0 == COLLISION_GROUP_DEBRIS || collisionGroup0 == COLLISION_GROUP_DEBRIS_TRIGGER )
    {
        // put exceptions here, right now this will only collide with COLLISION_GROUP_NONE
        return false;
    }

    // Dissolving guys only collide with COLLISION_GROUP_NONE
    if ( ( collisionGroup0 == COLLISION_GROUP_DISSOLVING ) || ( collisionGroup1 == COLLISION_GROUP_DISSOLVING ) )
    {
        if ( collisionGroup0 != COLLISION_GROUP_NONE )
            return false;
    }

    // doesn't collide with other members of this group
    // or debris, but that's handled above
    if ( collisionGroup0 == COLLISION_GROUP_INTERACTIVE_DEBRIS && collisionGroup1 == COLLISION_GROUP_INTERACTIVE_DEBRIS )
        return false;

    // This change was breaking HL2DM
    // Adrian: TEST! Interactive Debris doesn't collide with the player.
    if ( collisionGroup0 == COLLISION_GROUP_INTERACTIVE_DEBRIS && ( collisionGroup1 == COLLISION_GROUP_PLAYER_MOVEMENT || collisionGroup1 == COLLISION_GROUP_PLAYER ) )
        return false;

    if ( collisionGroup0 == COLLISION_GROUP_BREAKABLE_GLASS && collisionGroup1 == COLLISION_GROUP_BREAKABLE_GLASS )
        return false;

    // interactive objects collide with everything except debris & interactive debris
    if ( collisionGroup1 == COLLISION_GROUP_INTERACTIVE && collisionGroup0 != COLLISION_GROUP_NONE )
        return false;

    // Projectiles hit everything but debris, weapons, + other projectiles
    if ( collisionGroup1 == COLLISION_GROUP_PROJECTILE )
    {
        if ( collisionGroup0 == COLLISION_GROUP_DEBRIS ||
             collisionGroup0 == COLLISION_GROUP_WEAPON ||
             collisionGroup0 == COLLISION_GROUP_PROJECTILE )
        {
            return false;
        }
    }

    // Don't let vehicles collide with weapons
    // Don't let players collide with weapons...
    // Don't let NPCs collide with weapons
    // Weapons are triggers, too, so they should still touch because of that
    if ( collisionGroup1 == COLLISION_GROUP_WEAPON )
    {
        if ( collisionGroup0 == COLLISION_GROUP_VEHICLE ||
             collisionGroup0 == COLLISION_GROUP_PLAYER ||
             collisionGroup0 == COLLISION_GROUP_NPC )
        {
            return false;
        }
    }

    // collision with vehicle clip entity??
    if ( collisionGroup0 == COLLISION_GROUP_VEHICLE_CLIP || collisionGroup1 == COLLISION_GROUP_VEHICLE_CLIP )
    {
        // yes then if it's a vehicle, collide, otherwise no collision
        // vehicle sorts lower than vehicle clip, so must be in 0
        if ( collisionGroup0 == COLLISION_GROUP_VEHICLE )
            return true;
        // vehicle clip against non-vehicle, no collision
        return false;
    }

    return true;
}

bool CTraceFilterSimple::ShouldHitEntity( IHandleEntity *pHandleEntity , int contentsMask )
{
    if ( !StandardFilterRules( pHandleEntity , contentsMask ) )
        return false;

    if ( m_pPassEnt )
    {
        if ( !PassServerEntityFilter( pHandleEntity , m_pPassEnt ) )
        {
            return false;
        }
    }

    // Don't test if the game code tells us we should ignore this collision...
    C_BaseEntity *pEntity = EntityFromEntityHandle( pHandleEntity );
    if ( !pEntity )
        return false;

    if ( !pEntity->ShouldCollide( m_collisionGroup , contentsMask ) )
        return false;

    if ( ShouldCollide( m_collisionGroup , _OffsetManualthis( CBaseEntity::DT_BaseEntity::CollisionGroup() , int , pEntity ) ) )
        return false;

    if ( m_pExtraShouldHitCheckFunction != nullptr )
    {
        if (
            ( !( m_pExtraShouldHitCheckFunction( pHandleEntity , contentsMask ) ) ) )
            return false;
    }

    return true;
}