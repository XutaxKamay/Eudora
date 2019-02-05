#ifndef _CPEMINIMAL
#define _CPEMINIMAL
#pragma once

#include "CPE_Shared.hxx"
#include "Compressor.hxx"

class C_CSectionMinimal
{
public:

    C_CSectionMinimal( uHEX32 hRVA , uHEX32 VirtualSize , SocketBuffer &Buffer , uHEX32 hFlags )
    {
        m_hRVA = hRVA;
        m_VirtualSize = VirtualSize;
        m_Buffer = Buffer;
        m_hFlags = hFlags;
    }

    uHEX32 GetVirtualFlags();

    uHEX32 m_hFlags;
    uHEX32 m_hRVA;
    uHEX32 m_VirtualSize;
    SocketBuffer m_Buffer;
};

class C_CPEMinimal
{
public:

    C_CPEMinimal()
    {
        Reset();
    }

    ~C_CPEMinimal()
    {
        Reset();
    }

    void Reset()
    {
        m_Sections.clear();
        m_TlsCBs.clear();
        m_RoutineArgs.Free();
        bDLL_Main_Start.Free();
        pVRemotedArguments = nullptr;
        pVRoutine = nullptr;
        pMainThread = nullptr;
        iMachineType = iArchitecture = -1;
        m_ImageSize = m_hEntryPoint = 0;
    }

    bool InitStaticTls( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *Process );
    bool CopySections( N_VirtualMemory::VirtualBuffer &VirtualBuffer );
    bool CallTlsCBs( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *pProcess );
    bool CallRoutine( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *pProcess );
    bool EndTlsCBs( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *pProcess );
    bool FreeRoutine( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *pProcess );

    std::vector<C_CSectionMinimal> m_Sections;
    std::vector<C_CTlsCB> m_TlsCBs;
    C_CStaticTls m_StaticTls;

    int iMachineType , iArchitecture;
    uHEX32 m_hEntryPoint;
    Pointer pMainThread;
    N_VirtualMemory::VirtualBuffer *pVRoutine;
    N_VirtualMemory::VirtualBuffer *pVRemotedArguments;
    SocketBuffer bDLL_Main_Start;
    SocketBuffer m_RoutineArgs;
    uHEX32 m_ImageSize;
};

#endif