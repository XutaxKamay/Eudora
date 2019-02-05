#ifndef HACK_USERCOMMANDS
#define HACK_USERCOMMANDS
#pragma once

#include "Main.hxx"

class CHackUserCommands
{
public:

    void Update( C_BasePlayer* pPlayer , CUserCmd* Cmd );
    void ModifyAndUpdate( C_BasePlayer* pPlayer , CUserCmd* Cmd );
    void Modify( C_BasePlayer* pPlayer , CUserCmd *Cmd );
    void AutoBhop( C_BasePlayer* pPlayer , CUserCmd *Cmd );
    void EdgeJump( C_BasePlayer* pPlayer , CUserCmd *Cmd );
    void TimeScale( C_BasePlayer* pPlayer , CUserCmd *Cmd );
    void AngelStrafe( C_BasePlayer* pPlayer , CUserCmd* Cmd );
    void MovementFix( C_BasePlayer* pPlayer , CUserCmd* Cmd );

    bool bIsPredicted;
    bool bSendPacket;
    bool bShouldInvertTimeScale;
    bool bTimeScale;
    int iTicksRemainderTimeScale;
    bool bPausing;
    CUserCmd old_cmd;
    Angle a_AngelAngle;
    Angle a_FixAngle;
};

extern CHackUserCommands *HackUserCommands;

#endif