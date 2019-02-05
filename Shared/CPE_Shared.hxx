#ifndef _CPESHARED
#define _CPESHARED
#pragma once

#include "CPE.hxx"

struct S_ModuleToLoad
{
    S_ModuleToLoad( std::string sModuleName )
    {
        m_sModuleName = sModuleName;
    }

    ~S_ModuleToLoad()
    {
        m_sModuleName.clear();
    }

    void Reset()
    {
        m_sModuleName.clear();
    }

    std::string m_sModuleName;
};

struct S_DataShared
{
    void Reset()
    {
        m_bNeedsForwardingDLLs = true;
        m_hSizeOfImage = 0;
    }

    uHEX32 m_hSizeOfImage;
    bool m_bNeedsForwardingDLLs;
};

/*
struct MemoryStruct
{
    Byte *cMemory;
    size_t Size;
};

class C_CurlLib
{
public:

    static size_t WriteMemoryCallback( void *contents , size_t size , size_t nmemb , void *userp );
    static const char* GetIP();
    static void RequestHack( std::string Game , std::string User , std::string Password , std::string HWID );
};

*/

#endif