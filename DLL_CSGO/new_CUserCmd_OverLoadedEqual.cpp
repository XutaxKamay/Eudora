#include "Includes.hxx"
#include "Main.hxx"

__pragma( warning( push ) )
__pragma( warning( disable:4100 ) )

// Another way to modify commands by using createmove; but we validate another time vcmd->m_crc again, so it's not really that good.
// We can use the CUserCmd overloaded operator instead just before the buffer that gets validated.
// https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/mp/src/game/client/in_main.cpp#L1283
// Just there.
// So we just add some codes

CUserCmd* __fastcall new_CUserCmd_OverLoadedEqual( _FASTCALLD , CUserCmd* Cmd )
{
    if ( _ReturnAddress() == Offsets->pCUserCmdOverLoadedEqual_ReturnAddress_CreateMove )
    {
        volatile uHEX hEBP;
        __asm mov hEBP , ebp;
        bool *bSendPacket = ( bool* ) ( *( uHEX* ) hEBP - 0x1C );

        C_BasePlayer* LocalPlayer = GetLocalPlayer();

        if ( LocalPlayer != nullptr )
        {
            C_Weapon *Weapon = LocalPlayer->GetWeapon();

            if ( Weapon != nullptr )
            {
                int ID = *Weapon->GetID();

                if ( WeaponInfos[ ID ] == nullptr )
                {
                    WeaponInfos[ ID ] = new WeaponInfo_t( *Weapon->WeaponInfo() );
                }
            }
        }

        HackUserCommands->bSendPacket = *bSendPacket;

        HackUserCommands->ModifyAndUpdate( GetLocalPlayer() , Cmd );

        *bSendPacket = HackUserCommands->bSendPacket;

        *( CUserCmd* ) ThisPTR = *Cmd;
    }
    else
        *( CUserCmd* ) ThisPTR = *Cmd;

    return ( CUserCmd* ) ThisPTR;
}

__pragma( warning( pop ) )