#include "Includes.hxx"
#include "Main.hxx"

inline CBaseHandle::CBaseHandle( void )
{
    m_Index = INVALID_EHANDLE_INDEX;
}

inline CBaseHandle::CBaseHandle( const CBaseHandle &other )
{
    m_Index = other.m_Index;
}

inline CBaseHandle::CBaseHandle( unsigned long value )
{
    m_Index = value;
}

inline CBaseHandle::CBaseHandle( int iEntry , int iSerialNumber )
{
    Init( iEntry , iSerialNumber );
}

inline void CBaseHandle::Init( int iEntry , int iSerialNumber )
{
    m_Index = iEntry | ( iSerialNumber << NUM_ENT_ENTRY_BITS );
}

inline void CBaseHandle::Term()
{
    m_Index = INVALID_EHANDLE_INDEX;
}

inline bool CBaseHandle::IsValid() const
{
    return m_Index != INVALID_EHANDLE_INDEX;
}

inline int CBaseHandle::GetEntryIndex() const
{
    return m_Index & ENT_ENTRY_MASK;
}

inline int CBaseHandle::GetSerialNumber() const
{
    return m_Index >> NUM_ENT_ENTRY_BITS;
}

inline int CBaseHandle::ToInt() const
{
    return ( int ) m_Index;
}

inline bool CBaseHandle::operator !=( const CBaseHandle &other ) const
{
    return m_Index != other.m_Index;
}

inline bool CBaseHandle::operator ==( const CBaseHandle &other ) const
{
    return m_Index == other.m_Index;
}

inline bool CBaseHandle::operator ==( const IHandleEntity* pEnt ) const
{
    return Get() == pEnt;
}

inline bool CBaseHandle::operator !=( const IHandleEntity* pEnt ) const
{
    return Get() != pEnt;
}

inline bool CBaseHandle::operator <( const CBaseHandle &other ) const
{
    return m_Index < other.m_Index;
}

inline bool CBaseHandle::operator <( const IHandleEntity *pEntity ) const
{
    unsigned long otherIndex = ( pEntity ) ? pEntity->GetRefEHandle().m_Index : INVALID_EHANDLE_INDEX;
    return m_Index < otherIndex;
}

inline const CBaseHandle& CBaseHandle::operator=( const IHandleEntity *pEntity )
{
    return Set( pEntity );
}

inline const CBaseHandle& CBaseHandle::Set( const IHandleEntity *pEntity )
{
    if ( pEntity )
    {
        *this = pEntity->GetRefEHandle();
    }
    else
    {
        m_Index = INVALID_EHANDLE_INDEX;
    }

    return *this;
}

IHandleEntity* CBaseHandle::Get() const
{
    return ClientEntityList->GetClientEntityFromHandle( *this );
}

CStudioHdr* C_BaseAnimating::GetStudioHDR()
{
    CStudioHdr* pStudioHDR = _Offset( 0x293C , CStudioHdr* );

    if ( pStudioHDR == nullptr && GetModel() != nullptr )
        Offsets->C_BaseAnimating_LockStudioHdr( this->GetClientRenderable() );

    if ( pStudioHDR != nullptr && pStudioHDR->m_pStudioHdr != nullptr )
        return pStudioHDR;

    return nullptr;
}

bool C_BaseAnimating::_SetupBones( Matrix3x4 *pBoneToWorldOut , int nMaxBones , int boneMask , float currentTime )
{
    float frametime = Globals->frametime;
    Globals->frametime = FLT_MAX;

    *Offsets->pbAbsQueriesValid = 0;
    *Offsets->pbAbsRecomputationEnabled = 1;

    *( int* ) ( ( uintptr_t ) this + 0xA30 ) = Globals->framecount; //we'll skip occlusion checks now
    *( int* ) ( ( uintptr_t ) this + 0xA28 ) = 0;//clear occlusion flags

    InvalidateBoneCache();

    bool bSetupBones = SetupBones( pBoneToWorldOut , nMaxBones , boneMask , currentTime );

    Globals->frametime = frametime;

    return bSetupBones;
}

bool C_BaseAnimating::HitboxToWorldTransforms( Matrix3x4** pBoneToWorldOut )
{
    return Offsets->C_BaseAnimating_HitboxToWorldTransforms( this , pBoneToWorldOut );
}

void C_BaseAnimating::InvalidateBoneCache()
{
    *( int* ) ( ( HEX ) this->GetClientRenderable() + 0x267C ) = *Offsets->iModelBoneCounter - 1;
    *( float* ) ( ( HEX ) this->GetClientRenderable() + 0x2910 ) = -FLT_MAX;
    *( int * ) ( ( HEX ) this->GetClientRenderable() + 0x2698 ) = 0;
    *( int * ) ( ( HEX ) this->GetClientRenderable() + 0x269C ) = 0;
}

studiohdr_t* C_BaseAnimating::GetStudiohdr()
{
    IClientRenderable* Renderable = GetClientRenderable();

    if ( Renderable == nullptr )
        return nullptr;

    const model_t *model = Renderable->GetModel();

    if ( model == nullptr )
        return nullptr;

    studiohdr_t* hdr = ModelInfo->GetStudioModel( model );

    if ( hdr == nullptr )
        return nullptr;

    return hdr;
}

mstudiohitboxset_t* C_BaseAnimating::GetHitboxSet()
{
    studiohdr_t* hdr = GetStudiohdr();

    if ( hdr == nullptr )
        return nullptr;

    return hdr->GetHitboxSet( _Offset( CBaseAnimating::DT_BaseAnimating::nHitboxSet() , int ) );
}

mstudiobbox_t *C_BaseAnimating::GetBox( int iNum )
{
    mstudiohitboxset_t *Set = GetHitboxSet();
    if ( Set == nullptr )
        return nullptr;

    return Set->GetHitbox( iNum );
}

mstudiobbox_t *C_BaseAnimating::GetBox( const char* sName )
{
    mstudiohitboxset_t *Set = GetHitboxSet();

    if ( Set == nullptr )
        return nullptr;

    for ( int i = 0; i < Set->numhitboxes; i++ )
    {
        mstudiobbox_t *Box = Set->GetHitbox( i );

        if ( !strcmp( Box->GetName() , sName ) )
            return Box;
    }

    return nullptr;
}

int C_BaseAnimating::GetNumHitboxes()
{
    mstudiohitboxset_t *Set = GetHitboxSet();
    if ( Set == nullptr )
        return 0;

    return Set->numhitboxes;
}

int C_BaseAnimating::GetNumBones()
{
    studiohdr_t* hdr = GetStudiohdr();

    if ( hdr == nullptr )
        return 0;

    return hdr->numbones;
}

void C_BaseAnimating::CopyBoneCache( Matrix3x4* pBoneToWorldOut , int iNumBonesToCopy )
{
    Pointer pRenderable = ( Pointer ) this->GetClientRenderable();

    if ( pRenderable == nullptr )
        return;

    int iNumBones = _OffsetManualthis( 0x2908 , int , pRenderable );
    const Pointer pCachedBones = _OffsetManualthis( 0x28FC , pPointer , pRenderable );

    if ( pCachedBones == nullptr )
        return;

    if ( iNumBonesToCopy >= iNumBones )
    {
        memcpy( pBoneToWorldOut , pCachedBones , sizeof( Matrix3x4 ) * iNumBones );
    }
}

void C_BaseEntity::InvalidatePhysicsRecursive( int nChangeFlags )
{
    Offsets->C_BaseEntity_InvalidatePhysicsRecursive( ( Pointer ) this , nChangeFlags );
}

bool C_BaseEntity::HasAttachement()
{
    C_BaseEntity *pAttachment = FirstMoveChild();

    bool bHasAttachement = false;

    while ( pAttachment != nullptr )
    {
        if ( pAttachment == this )
            bHasAttachement = true;

        pAttachment = pAttachment->NextMovePeer();
    }

    return bHasAttachement;
}

bool C_BaseEntity::IsLocalPlayer( bool bAttachements )
{
    C_BaseEntity* LocalPlayer = GetLocalPlayer();

    if ( LocalPlayer != nullptr )
    {
        bool bLocalPlayer = this == LocalPlayer || entindex() == LocalPlayer->entindex();

        if ( bAttachements )
        {
            C_BaseEntity *pAttachment = LocalPlayer->FirstMoveChild();

            bool bHasAttachement = false;

            while ( pAttachment != nullptr )
            {
                if ( pAttachment == this || pAttachment->entindex() == entindex() )
                    bHasAttachement = true;

                pAttachment = pAttachment->NextMovePeer();
            }

            return bLocalPlayer || bHasAttachement;
        }
        else
        {
            return bLocalPlayer;
        }
    }
    else
    {
        return false;
    }
}

void C_BaseEntity::SetAbsVelocity( const Vector& vAbsVelocity )
{
    Offsets->C_BaseEntity_SetAbsVelocity( this , vAbsVelocity );
}

bool C_BaseEntity::IsPlayer()
{
    return entindex() > 0
        && entindex() <= Globals->maxClients;
}

C_Weapon* C_BasePlayer::GetWeapon()
{
    return ( C_Weapon* ) _Offset( CBasePlayer::DT_BasePlayer::DT_BaseCombatCharacter::hActiveWeapon() , CBaseHandle ).Get();
}

C_BaseEntity* C_BaseEntity::GetOwnerEntity()
{
    return ( C_BaseEntity* ) _Offset( CBaseEntity::DT_BaseEntity::hOwnerEntity() , CBaseHandle ).Get();
}

bool C_BaseEntity::ShouldCollide( int collisionGroup , int contentsMask )
{
    if ( _Offset( CBaseEntity::DT_BaseEntity::CollisionGroup() , int ) == COLLISION_GROUP_DEBRIS )
    {
        if ( !( contentsMask & CONTENTS_DEBRIS ) )
            return false;
    }
    return true;
}