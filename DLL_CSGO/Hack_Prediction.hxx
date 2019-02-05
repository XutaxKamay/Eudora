#ifndef HACK_PREDICTION
#define HACK_PREDICTION
#pragma once

class CHackPrediction
{
public:

    CHackPrediction()
    {
        eiSequenceNumber = 0;
        oldcurtime = -1.0f;
        oldframetime = -1.0f;
    }

    void PreThink( C_BasePlayer* pPlayer , CUserCmd* Cmd );
    void Think( C_BasePlayer*pPlayer , CUserCmd*Cmd );
    void PostThink( C_BasePlayer*pPlayer );

    int GetPredictedServerTick();

    int eiSequenceNumber;
    float oldcurtime;
    float oldframetime;
    float currentcurtime;
    bool bPredicting;
    int iOldTickBase;
    CMoveData movedata;
    Vector vecOldEyePos;
};

extern CHackPrediction* HackPrediction;

#endif