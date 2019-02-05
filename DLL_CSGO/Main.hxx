#ifndef MAINDLL
#define MAINDLL
#pragma once

#include "SDK.hxx"
#include "OffsetManager.hxx"
#include "Interfaces.hxx"
#include "Hack_ConVar.hxx"
#include "Hack_LagServer.hxx"
#include "Hack_Prediction.hxx"
#include "Hack_Menu.hxx"
#include "Backtrack.hxx"
#include "Materials.hxx"
#include "UserCommands.hxx"
#include "MovementRecorder.hxx"
#include "Hooks.hxx"
#include "../Shared/Socket.hxx"

struct S_Routine
{
    S_Routine( Pointer pModule , bool bManualMapped = false )
    {
        this->pModule = pModule;
        this->bManualMapped = bManualMapped;
    }

    ~S_Routine()
    {
        pModule = nullptr;
        bManualMapped = false;
    }

    Pointer pModule;
    bool bManualMapped;
};

Pointer _RoutineHack( S_Routine *SRoutine );

#ifdef _M_IX86
#ifdef _DEBUG
#pragma comment(lib,"../../Open Source Library/cryptopp/Win32/Output/Debug/cryptlib.lib")
#else
#pragma comment(lib,"../../Open Source Library/cryptopp/Win32/Output/Release/cryptlib.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib,"../../Open Source Library/cryptopp/x64/Output/Debug/cryptlib.lib")
#else
#pragma comment(lib,"../../Open Source Library/cryptopp/x64/Output/Release/cryptlib.lib")
#endif
#endif

#endif