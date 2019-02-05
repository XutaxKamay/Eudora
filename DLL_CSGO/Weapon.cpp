#include "Includes.hxx"
#include "Main.hxx"

WeaponInfo_t *WeaponInfos[ WEAPON_MAX ];

//Copy pasted autowall yey. Until I make this one better...

//n0xius thanks.
bool IsArmored( C_BasePlayer* Entity , int ArmorValue , int Hitgroup )
{
    bool result = false;

    if ( ArmorValue > 0 )
    {
        switch ( Hitgroup )
        {
            case HITGROUP_GENERIC:
            case HITGROUP_CHEST:
            case HITGROUP_STOMACH:
            case HITGROUP_LEFTARM:
            case HITGROUP_RIGHTARM:
                result = true;
                break;
            case HITGROUP_HEAD:
                result = _OffsetManualthis( CCSPlayer::DT_CSPlayer::bHasHelmet() , bool , Entity ); // DT_CSPlayer -> m_bHasHelmet
                break;
        }
    }

    return result;
}

float ScaleDamage( C_BasePlayer* Entity , float Damage , float WeaponArmorRatio , int Hitgroup )
{
    // NOTE: the Guardian/Coop Missions/Gamemode have bots with heavy armor which has a less damage modifier
    auto HeavyArmor = _OffsetManualthis( CCSPlayer::DT_CSPlayer::bHasHeavyArmor() , bool , Entity ); // DT_CSPlayer -> m_bHasHeavyArmor
    auto ArmorValue = _OffsetManualthis( CCSPlayer::DT_CSPlayer::ArmorValue() , int , Entity ); // DT_CSPlayer -> m_ArmorValue

    switch ( Hitgroup )
    {
        case HITGROUP_HEAD:
            if ( HeavyArmor )
                Damage = ( Damage * 4.f ) * 0.5f;
            else
                Damage *= 4.f;
            break;
        case HITGROUP_STOMACH:
            Damage *= 1.25f;
            break;
        case HITGROUP_LEFTLEG:
        case HITGROUP_RIGHTLEG:
            Damage *= 0.75f;
            break;
    }

    if ( IsArmored( Entity , ArmorValue , Hitgroup ) )
    {
        float v47 = 1.f , ArmorBonusRatio = 0.5f , ArmorRatio = WeaponArmorRatio * 0.5f;

        if ( HeavyArmor )
        {
            ArmorBonusRatio = 0.33f;
            ArmorRatio = ( WeaponArmorRatio * 0.5f ) * 0.5f;
            v47 = 0.33f;
        }

        auto NewDamage = Damage * ArmorRatio;

        if ( HeavyArmor )
            NewDamage *= 0.85f;

        if ( ( ( Damage - ( Damage * ArmorRatio ) ) * ( v47 * ArmorBonusRatio ) ) > ArmorValue )
            NewDamage = Damage - ( ArmorValue / ArmorBonusRatio );

        Damage = NewDamage;
    }

    return Damage;
}

WeaponInfo_t* C_Weapon::WeaponInfo()
{
    return _CallVirtualFunction<WeaponInfo_t*>( this , 447 );
}

std::vector<Vector> C_Weapon::GetBulletsVectors( Angle aLocalView , int iSequence , int iAddSeed )
{
    std::vector<Vector> vecBullets;

    int iID = *GetID();

    Vector vecDirShooting , vecRight , vecUp;
    aLocalView += *GetLocalPlayer()->PunchAngles() * 2.0f;
    AngleToVectors( aLocalView , &vecDirShooting , &vecRight , &vecUp );

    WeaponInfo_t* WeaponInfo = WeaponInfos[ iID ];

    if ( WeaponInfo != nullptr )
    {
        for ( int iBullet = 0; iBullet < WeaponInfo->iBullets; iBullet++ )
        {
            Offsets->RandomSeed( ( iAddSeed + ( MD5_PseudoRandom( iSequence ) + 1 ) ) & 0xFF );

            constexpr float _pi = 6.28319f;
            float B = Offsets->RandomFloat( 0.f , _pi );
            float C = Offsets->RandomFloat( 0.0f , 1.0f );
            float D = Offsets->RandomFloat( 0.f , _pi );

            float fSpread = C * GetSpread();

            if ( iID == WEAPON_REVOLVER )
            {
                if ( _Offset( CBaseCombatWeapon::DT_BaseCombatWeapon::DT_LocalActiveWeaponData::flNextSecondaryAttack() , float ) <= Globals->curtime )
                    C = 1.0f - ( C * C );
            }

            float fInaccuracy = C * GetInaccuracy();

            Vector vecSpread( ( cos( B ) * fSpread ) + ( cos( D ) * fInaccuracy ) , ( sin( B ) * fSpread ) + ( sin( D ) * fInaccuracy ) );

            Vector vecSpreadDir = vecDirShooting + ( vecRight * vecSpread ) + ( vecUp * vecSpread );

            vecSpreadDir.FastNormalize();

            vecBullets.push_back( vecSpreadDir );
        }
    }

    return vecBullets;
}