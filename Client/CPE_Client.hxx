#ifndef _CPECLIENT
#define _CPECLIENT
#pragma once

#include "CPE_Minimal.hxx"
#include "Socket.hxx"

struct S_DataClient : public S_DataShared
{
    void Reset()
    {
        m_ModulesToLoad.clear();
    }

    std::vector<S_ModuleToLoad> m_ModulesToLoad;
};

class C_CConstructPEClient : public C_CConstructPE
{
public:

    C_CConstructPEClient()
    {
        m_DataClient.Reset();
    }

    ~C_CConstructPEClient()
    {
        m_DataClient.Reset();
    }

    //SocketBuffer* MakeLogin( std::string GAME , std::string HWID , std::string Password , std::string User );
    void LoadModulesInfo( N_Process::Process* pProcess , SocketBuffer& buf );
    SocketBuffer* MakeInjectionInfo( N_Process::Process* pProcess , N_VirtualMemory::VirtualBuffer& VirtualBuffer );
    void ProcessCPEMinimal( N_Process::Process* pProcess , N_VirtualMemory::VirtualBuffer& VirtualBuffer , SocketBuffer& buf );
    C_CPEMinimal* ConstructMinimal( SocketBuffer *buf );
    bool ProcessProcedure();

    S_DataClient m_DataClient;

    std::string m_IP = AutoConvertC( TEXT( "127.0.0.1" ) );
    std::string m_PORT = AutoConvertC( TEXT( "2407" ) );
};

extern C_CConstructPEClient g_CConstructPEClient;

#endif