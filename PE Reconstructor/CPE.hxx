#ifndef _CPE
#define _CPE
#pragma once

#include "Lib.hxx"
//#include "curl.h"

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

/*
#ifdef _M_IX86
#ifdef _DEBUG
#pragma comment(lib,"../../Open Source Library/curl/build/Win32/VC15/LIB Debug - LIB wolfSSL/libcurld.lib")
#else
#pragma comment(lib,"../../Open Source Library/curl/build/Win32/VC15/LIB Release - LIB wolfSSL/libcurl.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib,"../../Open Source Library/curl/build/Win64/VC15/LIB Debug - LIB wolfSSL/libcurld.lib")
#else
#pragma comment(lib,"../../Open Source Library/curl/build/Win64/VC15/LIB Release - LIB wolfSSL/libcurl.lib")
#endif
#endif

#ifdef _M_IX86
#ifdef _DEBUG
#pragma comment(lib,"../../Open Source Library/wolfssl/build/Win32/VC15/LIB Debug/wolfssl.lib")
#else
#pragma comment(lib,"../../Open Source Library/wolfssl/build/Win32/VC15/LIB Release/wolfssl.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib,"../../Open Source Library/wolfssl/build/Win64/VC15/LIB Debug/wolfssl.lib")
#else
#pragma comment(lib,"../../Open Source Library/wolfssl/build/Win64/VC15/LIB Release/wolfssl.lib")
#endif
#endif
*/

class C_CSection;
class C_CPEMinimal;
class C_CPEMinimalServer;

enum
{
    reloc_UNKNOWN ,
    reloc_ABSOLUTE ,
    reloc_32 ,
    reloc_64 ,
};

enum
{
    M_x86 ,
    M_x64 ,
};

enum
{
    M_DLL ,
    M_EXE
};

enum
{
    CPE_RelocsFailed ,
    CPE_Relocated
};

const String* GetRelocationName( int iType );

struct FunctionImport32
{
    union
    {
        uHEX32 m_hOrdinal;
        uHEX32 m_hData;
        uHEX32 m_hFunction;
        uHEX32 m_hRVAString;
    }u;
};

typedef FunctionImport32* pFunctionImport32;

struct FunctionImport64
{
    union
    {
        uHEX64 m_hOrdinal;
        uHEX64 m_hData;
        uHEX64 m_hFunction;
        uHEX64 m_hRVAString;
    }u;
};

typedef FunctionImport64* pFunctionImport64;

class C_CImport
{
public:

    C_CImport( std::string sFunctionName , std::string sModuleName , Pointer pFileOffset )
    {
        m_pFileOffset = pFileOffset;
        m_sFunctionName = sFunctionName;
        m_sModuleName = sModuleName;
    }

    ~C_CImport()
    {
        m_pFileOffset = nullptr;
        m_sFunctionName.clear();
        m_sModuleName.clear();
    }

public:
    std::string m_sFunctionName , m_sModuleName;
    Pointer m_pFileOffset;
};

class C_CExcept
{
public:

    C_CExcept( Pointer pFileStart , Pointer pFileEnd , uHEX32 hRVAStart , uHEX32 hRVAEnd , uHEX32 unWind , uHEX32 hRVARunTFunc , uHEX32 hIndex )
    {
        m_pFileStart = pFileStart;
        m_pFileEnd = pFileEnd;
        m_hRVAStart = hRVAStart;
        m_hRVAEnd = hRVAEnd;
        this->unWind.Data = this->unWind.Info = unWind;
        m_hRVARunTFunc = hRVARunTFunc;
        m_hIndex = hIndex;
    }

    ~C_CExcept()
    {
        m_pFileStart = m_pFileEnd = nullptr;
        m_hRVARunTFunc = this->unWind.Data = this->unWind.Info = m_hRVAStart = m_hRVAEnd = 0;
        m_hIndex = 0;
    }

    Pointer m_pFileStart , m_pFileEnd;
    uHEX32 m_hRVAStart , m_hRVAEnd;
    uHEX32 m_hRVARunTFunc;
    uHEX32 m_hIndex;

    union u_unWind
    {
        uHEX32 Info;
        uHEX32 Data;
    };

    u_unWind unWind;
};

class C_CReloc
{
public:

    C_CReloc( Pointer pValue , Pointer pFileOffset , int iType )
    {
        m_pValue = pValue;
        m_pFileOffset = pFileOffset;
        m_iType = iType;
    }

    ~C_CReloc()
    {
        m_pValue = nullptr;
        m_pFileOffset = nullptr;
        m_iType = -1;
    }

    FORCEINLINE const String* GetSType()
    {
        return GetRelocationName( m_iType );
    }

public:
    Pointer m_pFileOffset;
    Pointer m_pValue;
    int m_iType;
};

class C_CSection
{
public:

    C_CSection( uHEX32 hRVA , uHEX32 VirtualSize , uHEX32 hFileOffset , uHEX32 FileSize , std::string sName , SocketBuffer &Buffer , uHEX32 hFlags )
    {
        m_hRVA = hRVA;
        m_VirtualSize = VirtualSize;
        m_hFileOffset = hFileOffset;
        m_FileSize = FileSize;
        m_sName = sName;
        m_OriginalData = m_Buffer = Buffer;
        m_hFlags = hFlags;
    }

    ~C_CSection()
    {
        m_hFileOffset = m_hRVA = 0;
        m_VirtualSize = m_FileSize = 0;
        m_sName.clear();
        m_Buffer.Free();
        m_OriginalData.Free();
        m_hFlags = 0;
    }

    uHEX32 GetVirtualFlags();

public:
    uHEX32 m_hRVA;
    uHEX32 m_hFileOffset;
    uHEX32 m_FileSize , m_VirtualSize;
    std::string m_sName;
    SocketBuffer m_Buffer;
    SocketBuffer m_OriginalData;
    uHEX32 m_hFlags;
};

class C_CTlsCB
{
public:

    C_CTlsCB( Pointer pRVA )
    {
        m_pRVA = pRVA;
    }

    ~C_CTlsCB()
    {
        m_pTlsDetach = m_pTlsAttach = m_pRVA = nullptr;
        pVRoutine = nullptr;
        pVRemotedArguments = nullptr;
        hResultDetach = hResultAttach = 0;
    }

    Pointer m_pRVA;
    Pointer m_pTlsAttach;
    Pointer m_pTlsDetach;
    uHEX32 hResultAttach;
    uHEX32 hResultDetach;
    N_VirtualMemory::VirtualBuffer* pVRemotedArguments;
    N_VirtualMemory::VirtualBuffer* pVRoutine;
};

class C_CStaticTls
{
public:

    C_CStaticTls()
    {
        m_RVATlsDir = m_RVATlsDirSize = 0;
    }

    ~C_CStaticTls()
    {
        m_RVATlsDir = m_RVATlsDirSize = 0;
    }

    uHEX32 m_RVATlsDir , m_RVATlsDirSize;
};

class C_CPE
{
public:

    C_CPE()
    {
        Reset();
    }

    ~C_CPE()
    {
        Reset();
    }

    void Reset()
    {
        m_Imports.clear();
        m_Relocs.clear();
        m_Sections.clear();
        m_Exceptions.clear();
        m_TlsCBs.clear();
        m_ListImportModules.clear();
        m_pImageBase = nullptr;
        m_hEntryPoint = 0;
        m_ImageSize = 0;
        pMainThread = nullptr;
        pVRoutine = nullptr;
        pVRemotedArguments = nullptr;
        iMachineType = iArchitecture = -1;
    }

    Pointer GetAFromSections( Pointer pFileOffset );

    int RelocateSections( Pointer pNewImageBase );
    bool ProcessExceptions( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *pProcess );
    bool ProcessImports( N_Process::Process *pProcess );
    bool ProcessStaticTls( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *pProcess );
    bool CopySections( N_VirtualMemory::VirtualBuffer &VirtualBuffer );
    bool CallTlsCBs( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *pProcess );
    bool CallRoutine( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *pProcess );
    bool EndTlsCBs( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *pProcess );
    bool FreeRoutine( N_VirtualMemory::VirtualBuffer &VirtualBuffer , N_Process::Process *pProcess );

    bool Construct( PIMAGE_DOS_HEADER DosHeader );
    bool ConstructRelocs( PIMAGE_DOS_HEADER DosHeader );
    bool _ConstructRelocs( PIMAGE_DOS_HEADER pDosHeader , uHEX &hNumberOfRelocations , PWORD &pwRelocationAddress , Bytes &bRelocationBlock );
    bool ConstructIATs( PIMAGE_DOS_HEADER DosHeader );
    //bool ConstructDebug( PIMAGE_DOS_HEADER DosHeader );
    bool ConstructExceptions( PIMAGE_DOS_HEADER DosHeader );
    bool ConstructSections( PIMAGE_DOS_HEADER DosHeader );
    bool ConstructTls( PIMAGE_DOS_HEADER DosHeader );

public:

    std::vector<C_CImport> m_Imports;
    std::vector<C_CReloc> m_Relocs;
    std::vector<C_CSection> m_Sections;
    std::vector<C_CTlsCB> m_TlsCBs;
    C_CStaticTls m_StaticTls;
    std::vector<C_CExcept> m_Exceptions;
    std::list<std::string> m_ListImportModules;

    Pointer m_pImageBase;
    uHEX32 m_hEntryPoint;
    uHEX32 m_ImageSize;
    int iMachineType , iArchitecture;
    Pointer pMainThread , pThreadLocalStorage;
    N_VirtualMemory::VirtualBuffer *pVRoutine;
    N_VirtualMemory::VirtualBuffer *pVRemotedArguments;
};

class C_CConstructPE
{
public:

    C_CPE * Reconstruct( PIMAGE_DOS_HEADER DosHeader );
};

extern C_CConstructPE g_CConstructPE;

#endif