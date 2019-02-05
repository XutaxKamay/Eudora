#ifndef _CPESERVER
#define _CPESERVER
#pragma once

#include "CPE_Minimal.hxx"
#include "Socket.hxx"

class CMemoryModulesRecvd
{
public:

    CMemoryModulesRecvd()
    {
        Reset();
    }

    ~CMemoryModulesRecvd()
    {
        Reset();
    }

    void Reset()
    {
        m_Buffer.Free();
        sModuleName.clear();
        pModuleAddress = nullptr;
    }

    SocketBuffer m_Buffer;
    std::string sModuleName;
    Pointer pModuleAddress;
};

class C_InjectionInfo
{
public:

    void Reset()
    {
        m_Modules.clear();
        NumberOfModules = 0;
        pRelocateAddress = nullptr;
    }

    std::vector<CMemoryModulesRecvd> m_Modules;
    bool m_bisWow64;
    size_t NumberOfModules;
    Pointer pRelocateAddress;
};

class C_CPEMinimalServer : public C_CPEMinimal
{
public:

    bool ResolveImports();
    Pointer GetAFromSections( Pointer pFileOffset );
    uHEX GetFunctionReadPEFromMem( const PCHAR pcFunctionName , const stdString &sModuleName );

    Pointer m_pImageBase;
    std::vector<C_CImport> m_Imports;
    std::vector<Pointer> m_SectionsOffsets;
    C_InjectionInfo InjectionInfo;
};

class C_CConstructPEServer : public C_CConstructPE
{
public:

    C_CConstructPEServer()
    {
        m_DataServer.Reset();
        InjectionInfo.Reset();
    }

    ~C_CConstructPEServer()
    {
        m_DataServer.Reset();
        InjectionInfo.Reset();
    }

    //bool ProcessLogin( SocketBuffer& buf );
    SocketBuffer* MakeModulesInfos( C_CPE* CPE );
    SocketBuffer* MakeCPEMinimal( C_CPE* CPE );
    bool ProcessInjectionInfo( SocketBuffer &buf );
    SocketBuffer* MakeModulesInfosForwarded( C_CPE* CPE );

    void MakeListForwardedDLL( std::list<std::string> &m_ListImportModules
                               , const PCHAR pcFunctionName , const stdString &sModuleName );
    SocketBuffer *ChangeToMinimal( C_CPEMinimalServer* CPE );
    C_CPEMinimalServer* ToMinimalServer( C_CPE* CPE );

    S_DataShared m_DataServer;
    C_InjectionInfo InjectionInfo;
};

extern C_CConstructPEServer g_CConstructPEServer;

#endif