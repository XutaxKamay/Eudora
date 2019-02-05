#ifndef LIB_PROCESS
#define LIB_PROCESS
#pragma once

#define THREAD_CREATE_FLAGS_CREATE_SUSPENDED 0x00000001
#define THREAD_CREATE_FLAGS_SKIP_THREAD_ATTACH 0x00000002 // ?
#define THREAD_CREATE_FLAGS_HIDE_FROM_DEBUGGER 0x00000004
#define THREAD_CREATE_FLAGS_HAS_SECURITY_DESCRIPTOR 0x00000010 // ?
#define THREAD_CREATE_FLAGS_ACCESS_CHECK_IN_TARGET 0x00000020 // ?
#define THREAD_CREATE_FLAGS_INITIAL_THREAD 0x00000080
#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)

typedef struct _PS_ATTRIBUTE
{
    ULONG Attribute;
    SIZE_T Size;
    union
    {
        ULONG Value;
        PVOID ValuePtr;
    };
    PSIZE_T ReturnLength;
} PS_ATTRIBUTE , *PPS_ATTRIBUTE;

typedef struct _PS_ATTRIBUTE_LIST
{
    SIZE_T TotalLength;
    PS_ATTRIBUTE Attributes[ 1 ];
} PS_ATTRIBUTE_LIST , *PPS_ATTRIBUTE_LIST;

typedef struct _API_SET_NAMESPACE
{
    ULONG Version;
    ULONG Size;
    ULONG Flags;
    ULONG Count;
    ULONG EntryOffset;
    ULONG HashOffset;
    ULONG HashFactor;
} API_SET_NAMESPACE , *PAPI_SET_NAMESPACE;

typedef struct _API_SET_HASH_ENTRY
{
    ULONG Hash;
    ULONG Index;
} API_SET_HASH_ENTRY , *PAPI_SET_HASH_ENTRY;

typedef struct _API_SET_NAMESPACE_ENTRY
{
    ULONG Flags;
    ULONG NameOffset;
    ULONG NameLength;
    ULONG HashedLength;
    ULONG ValueOffset;
    ULONG ValueCount;
} API_SET_NAMESPACE_ENTRY , *PAPI_SET_NAMESPACE_ENTRY;

typedef struct _API_SET_VALUE_ENTRY
{
    ULONG Flags;
    ULONG NameOffset;
    ULONG NameLength;
    ULONG ValueOffset;
    ULONG ValueLength;
} API_SET_VALUE_ENTRY , *PAPI_SET_VALUE_ENTRY;

namespace N_Process
{
    class Module
    {
    public:

        Module( stdString sName , HEX hA )
        {
            m_sName = sName;
            m_hA = hA;
        }

        ~Module()
        {
            m_sName.clear();
            m_hA = 0;
        }

        stdString m_sName;
        HEX m_hA;
    };

    struct sLoadLib
    {
        uHEX64 pReturnAddress;
        uHEX64 pDLLPath;
        uHEX64 pAddress;
    };

    class Process
    {
    public:

        // Constructors of the class process;
        // Here we initialize proc id, the handle of the process, and the process path (exe's path).
        // We can get it by PID or Path in directory, or just the handle of it.
        // GetModuleBaseName stands getting for the exe's name in task manager for example.
        Process( Pointer _pProcess = GetCurrentProcess() );

        Process( HEX _HexProcessID );

        Process( stdString _swProcessName );

        // Deconstructor, free our memory allocated, etc...
        ~Process();

        // Get the process handle.
        Pointer Get();

        std::vector<Pointer> GetThreads();

        Pointer GetTEB( Pointer pThread );

        // Find a module by name.
        Pointer FindModule( stdString DLLName );

        // Find the module path from the module address , GetModuleFileNameEx can do it
        stdString FindModulePath( Pointer pModuleAddress );

        void PrintAllModules();

        void RefreshGetModules();

        void GetInformations();

        stdString &GetName();

        HEX &GetID();

        void Free();

        bool SetAllAccess();

        Pointer CreateRemotlyThread( Pointer pRoutine , Pointer pArguments , unsigned long *pULRetThread = nullptr );

        uHEX GetFunctionReadPE( const PCHAR pcFunctionName , const stdString &sModuleName );

        bool ForceLoadLibrary( const stdString &sModuleName );

        bool ForceFreeLibrary( const stdString &sModuleName );

        bool FreeForcedLibraries();

        N_VirtualMemory::VirtualBuffer* VirtualAlloc( size_t Size , uHEX32 hFlag = PAGE_EXECUTE_READWRITE , Pointer pAllocAddr = nullptr )
        {
            return new N_VirtualMemory::VirtualBuffer( Size , hFlag , pAllocAddr , pProcess );
        }

        bool VirtualFreeAlloc( N_VirtualMemory::VirtualBuffer* vBuffer )
        {
            if ( vBuffer->pProcess == pProcess )
            {
                vBuffer->Free();
            }
            else
            {
                CONSOLEColorDEBUG( FOREGROUND_RED , TEXT( "[%s]->VirtualFreeAlloc process handle wasn't the same, in result we can't free the memory here\n" ) );
            }
        }

        Pointer VirtualAllocSecond( size_t Size , uHEX32 hFlag = PAGE_EXECUTE_READWRITE , uHEX32 hAllocType = MEM_COMMIT | MEM_RESERVE , Pointer pAllocAddr = nullptr )
        {
            return VirtualAllocEx( pProcess , pAllocAddr , Size , hAllocType , hFlag );
        }

        bool VirtualFreeAllocSecond( Pointer pVirtualAddr )
        {
            return VirtualFreeEx( pProcess , pVirtualAddr , 0 , MEM_RELEASE );
        }

        bool VirtualWriteMemory( Pointer pBufferAddress , Pointer pBuffer , size_t Size )
        {
            uHEX32 hOldFlag;
            VirtualProtectEx( pProcess , pBufferAddress , Size , PAGE_EXECUTE_READWRITE , &hOldFlag );
            SIZE_T NbOfBW = 0;

            if ( !WriteProcessMemory( pProcess , pBufferAddress , pBuffer , Size , &NbOfBW ) )
            {
                CONSOLEDEBUG( TEXT( "[%s]->VirtualWriteMemory error: 0x%p\n" ) , sName.c_str() , GetLastError() );
                VirtualProtectEx( pProcess , pBufferAddress , Size , hOldFlag , &hOldFlag );
                return false;

            }

            VirtualProtectEx( pProcess , pBufferAddress , Size , hOldFlag , &hOldFlag );

            return true;
        }

        bool VirtualReadMemory( Pointer pBufferAddress , Pointer pBuffer , size_t Size , bool bRemoveFlags = false )
        {
            uHEX32 hOldFlag;
            if ( bRemoveFlags )
                VirtualProtectEx( pProcess , pBufferAddress , Size , PAGE_EXECUTE_READWRITE , &hOldFlag );

            SIZE_T NbOfBR = 0;

            if ( !ReadProcessMemory( pProcess , pBufferAddress , pBuffer , Size , &NbOfBR ) )
            {
                CONSOLEDEBUG( TEXT( "[%s]->VirtualReadMemory error: 0x%p\n" ) , sName.c_str() , GetLastError() );
                if ( bRemoveFlags )
                    VirtualProtectEx( pProcess , pBufferAddress , Size , hOldFlag , &hOldFlag );
                return false;

            }

            if ( bRemoveFlags )
                VirtualProtectEx( pProcess , pBufferAddress , Size , hOldFlag , &hOldFlag );

            return true;
        }

        // Name of the process
        stdString sName;
        stdString sProcessPath;

        // Number of modules of the process
        std::vector<Module> vshModules;

         // The handle of the process, and its address in memory.
        Pointer pProcess , pAddress;

        // Process ID.
        HEX HexProcessID;

        // The number of modules that were forced by LoadLibrary.
        std::list<Module> psForcedModules;

        bool bIsWow64;
    };
};

#endif