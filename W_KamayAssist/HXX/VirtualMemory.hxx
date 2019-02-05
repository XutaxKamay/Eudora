#ifndef LIB_VIRTUALMEMORY
#define LIB_VIRTUALMEMORY
#pragma once

// Protection flags
namespace N_VirtualMemory
{
    class VirtualMemoryFlags
    {
    public:

        VirtualMemoryFlags()
        {
            m_hFlags.clear();
        }

        VirtualMemoryFlags( std::vector<uHEX32> &hFlags )
        {
            m_hFlags = hFlags;
        }

        VirtualMemoryFlags( size_t sSize , uHEX32 hFlags )
        {
            m_hFlags.clear();
            m_hFlags.resize( sSize );

            for ( auto &&i : m_hFlags )
                i = hFlags;
        }

        VirtualMemoryFlags& operator=( VirtualMemoryFlags& Flags )
        {
            m_hFlags = Flags.m_hFlags;
            return *this;
        }

        VirtualMemoryFlags& operator=( std::vector<uHEX32> hFlags )
        {
            m_hFlags = hFlags;
        }

        void ChangeInRange( size_t iStart , size_t iEnd , uHEX32 hFlag )
        {
            for ( auto it = iStart + m_hFlags.begin(); it < iEnd + m_hFlags.begin(); it++ )
                *it = hFlag;
        }

        void Reset()
        {
            m_hFlags.clear();
        }

        std::vector<uHEX32> m_hFlags;
    };

    VirtualMemoryFlags &FillVirtualMemoryFlags( size_t sSize , uHEX32 hFlags );

    // Modify protection flags
    bool VirtualModifyProtectionFlags( Pointer pAddress
                                       , Pointer pProcess = ( Pointer ) GetCurrentProcess
                                       , VirtualMemoryFlags& Flags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE ) );

    bool VirtualModifyProtectionFlags( Pointer pAddress
                                       , Pointer pProcess = ( Pointer ) GetCurrentProcess()
                                       , HEX HexSize = MINSIZEVIRTUALMEMORY
                                       , uHEX32 HexProtectionFlags = PAGE_EXECUTE_READWRITE
                                       , puHEX32 pHexOldProtectionFlags = nullptr );

    // Allocate virtual memory.
    Pointer VirtualAllocation( HEX HexSize = MINSIZEVIRTUALMEMORY
                               , VirtualMemoryFlags& Flags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                               , Pointer pProcess = ( Pointer ) GetCurrentProcess()
                               , Pointer pAllocationAddress = nullptr );

    Pointer VirtualAllocation( HEX HexSize = MINSIZEVIRTUALMEMORY
                               , uHEX32 HexFlag = PAGE_EXECUTE_READWRITE
                               , Pointer pProcess = ( Pointer ) GetCurrentProcess()
                               , Pointer pAllocationAddress = nullptr );

    // Free virtual memory.
    bool FreeVirtualAllocation( Pointer pAddress , Pointer pProcess = ( Pointer ) GetCurrentProcess() , bool bLastCall = false );

    // Read virtual memory.
    bool VirtualReadMemory( Pointer pAddress , Pointer pRead , HEX HexSize = MINSIZEVIRTUALMEMORY
                            , VirtualMemoryFlags& Flags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                            , Pointer pProcess = ( Pointer ) GetCurrentProcess() , pHEX pHexNbOfReadBytes = nullptr , bool bLastCall = false );

    // Write virtual memory.
    bool VirtualWriteMemory( Pointer pAddress , Pointer pWrite , HEX HexSize = MINSIZEVIRTUALMEMORY
                             , VirtualMemoryFlags& Flags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                             , Pointer pProcess = ( Pointer ) GetCurrentProcess()
                             , pHEX pHexNbOfReadBytes = nullptr , bool bLastCall = false );

    // Get virtual memory information.

    void VirtualQueryMBI( Pointer pAddress
                          , HEX HexSize = MINSIZEVIRTUALMEMORY
                          , PMEMORY_BASIC_INFORMATION pMBI = nullptr
                          , Pointer pProcess = ( Pointer ) GetCurrentProcess()
                          , HEX *_HexNbBuffer = nullptr );

    HEX VirtualQueryProtectionFlags( Pointer pAddress , HEX HexSize = MINSIZEVIRTUALMEMORY , Pointer pProcess = ( Pointer ) GetCurrentProcess() );

    HEX VirtualQuerySize( Pointer pAddress , HEX HexSize = MINSIZEVIRTUALMEMORY , Pointer pProcess = ( Pointer ) GetCurrentProcess() );

    HEX VirtualQueryState( Pointer pAddress , HEX HexSize = MINSIZEVIRTUALMEMORY , Pointer pProcess = ( Pointer ) GetCurrentProcess() );

    HEX VirtualQueryType( Pointer pAddress , HEX HexSize = MINSIZEVIRTUALMEMORY , Pointer pProcess = ( Pointer ) GetCurrentProcess() );

    Pointer VirtualQueryBaseAddress( Pointer pAddress , HEX HexSize = MINSIZEVIRTUALMEMORY , Pointer pProcess = ( Pointer ) GetCurrentProcess() );

    HEX VirtualQueryAllocationProtect( Pointer pAddress , HEX HexSize = MINSIZEVIRTUALMEMORY , Pointer pProcess = ( Pointer ) GetCurrentProcess() );

    Pointer VirtualQueryAllocationBase( Pointer pAddress , HEX HexSize = MINSIZEVIRTUALMEMORY , Pointer pProcess = ( Pointer ) GetCurrentProcess() );

    // Write virtual memory from the current process
    bool WriteVirtualMemoryFromCurrentProcess_S( Pointer pAddressDestination , Pointer pAddressSource
                                                 , HEX &HexSizeOfDestination , HEX HexSizeOfSource
                                                 , VirtualMemoryFlags& Flags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                                                 , Pointer pProcessDestination = ( Pointer ) GetCurrentProcess()
                                                 , Pointer pRebaseAddressDestination = nullptr );

    // Copy virtual memory from a process, to another process.
    bool CopyVirtualMemory_S( Pointer pAddressDestination , HEX &HexSizeOfDestination
                              , Pointer pAddressSource , HEX HexSizeOfSource
                              , Pointer pProcessDestination = ( Pointer ) GetCurrentProcess() , Pointer pProcessSource = ( Pointer ) GetCurrentProcess()
                              , VirtualMemoryFlags& DestinationFlags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                              , VirtualMemoryFlags& SourceFlags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                              , Pointer pRebaseAddressDestination = nullptr );

    // Compare how much the data is not corresponding.

    HEX CompareVirtualMemory_S( Pointer pAddressDestination , HEX HexSizeOfDestination , Pointer pAddressSource , HEX HexSizeOfSource
                                , VirtualMemoryFlags& DestinationFlags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                                , VirtualMemoryFlags& SourceFlags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                                , Pointer pProcessDestination = ( Pointer ) GetCurrentProcess() , Pointer pProcessSource = ( Pointer ) GetCurrentProcess() , bool *bFailed = false );

    // Find the offset in the virtual memory, from a process, to another.
    // We could use aternativly memcmp though.
    // Same code as in SigScanning.h +/-

    HEX FindOffsetVirtualMemory_s( Pointer pAddressDestination , HEX HexSizeOfDestination
                                   , Pointer pAddressSource , HEX HexSizeOfSource
                                   , VirtualMemoryFlags& DestinationFlags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                                   , VirtualMemoryFlags& SourceFlags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                                   , Pointer pProcessDestination = ( Pointer ) GetCurrentProcess() , Pointer pProcessSource = ( Pointer ) GetCurrentProcess()
                                   , bool *bFailed = nullptr );

    bool RemoveVirtualMemory_S( Pointer pAddress , HEX &HexSize , HEX pFromAddress , HEX HexSizeToRemove
                                , VirtualMemoryFlags& Flags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                                , Pointer pProcess = ( Pointer ) GetCurrentProcess()
                                , Pointer pRebaseAddressDestination = nullptr );

    bool ReplaceVirtualMemory_S( Pointer pFromAddress , Pointer pAddressDestination , Pointer pAddressSource
                                 , HEX &HexSizeOfDestination , HEX HexSizeOfSource
                                 , Pointer pProcessDestination = ( Pointer ) GetCurrentProcess()
                                 , Pointer pProcessSource = ( Pointer ) GetCurrentProcess()
                                 , VirtualMemoryFlags& DestinationFlags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                                 , VirtualMemoryFlags& SourceFlags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                                 , Pointer pRebaseAddressDestination = nullptr );

    // First we just add virtual memory in where we want to and move the saved bytes from where it has been written.
    bool AddVirtualMemory_S( Pointer pFromAddress , Pointer pAddressDestination , Pointer pAddressSource
                             , HEX &HexSizeOfDestination , HEX HexSizeOfSource
                             , Pointer pProcessDestination = ( Pointer ) GetCurrentProcess()
                             , Pointer pProcessSource = ( Pointer ) GetCurrentProcess()
                             , VirtualMemoryFlags& DestinationFlags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                             , VirtualMemoryFlags& SourceFlags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                             , Pointer pRebaseAddressDestination = nullptr );

    class VirtualBuffer
    {
    public:

        // Constructor allocate virtual memory for our buffer, and set the protection flags correctly to that allocated virtual memory.
        VirtualBuffer( HEX HexSize = MINSIZEVIRTUALMEMORY
                       , uHEX32 HexFlag = PAGE_EXECUTE_READWRITE
                       , Pointer pAllocationAddress = nullptr
                       , Pointer pProcess = ( Pointer ) GetCurrentProcess()
                       , const stdString& sName = TEXT( "TempVirtualBuffer" )
                       , Pointer pAddressToCopy = nullptr );

        VirtualBuffer( Pointer pAddress
                       , HEX HexSize
                       , VirtualMemoryFlags& SourceFlags = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                       , Pointer pProcess = ( Pointer ) GetCurrentProcess()
                       , const stdString& sName = TEXT( "TempVirtualBuffer" ) );

        // In case we want to copy another buffer.
        VirtualBuffer( VirtualBuffer *pVBuf );

        // Free the buffer.
        ~VirtualBuffer();

        // If our buffer is valid.
        bool IsValid();

        void PrintBytes();

        bool RefreshFlags();

        // In case we want to read the virtual memory and allocate somewhere to the current process to modify like we want more easily.
        Pointer GetLocal();

        // Copy buffer to another.
        bool Copy( VirtualBuffer* pVBuf );

        // Replace virtual memory from a process to another process.
        bool Replace( Pointer pAddressDestination , HEX SizeOfDestination , Pointer pProcessDestination = ( Pointer ) GetCurrentProcess()
                      , VirtualMemoryFlags& FlagsDestination = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                      , Pointer pFromAddress = nullptr );

        // Same as above, but with a buffer.
        bool Replace( VirtualBuffer* pVBuf , Pointer pFromAddress = nullptr );

        // Add virtual memory from a process to another process.
        bool Add( Pointer pAddressDestination , HEX SizeOfDestination , Pointer pProcessDestination = ( Pointer ) GetCurrentProcess()
                  , VirtualMemoryFlags& FlagsDestination = FillVirtualMemoryFlags( MINSIZEVIRTUALMEMORY , PAGE_EXECUTE_READWRITE )
                  , Pointer pFromAddress = nullptr );

        // Same as above, but with a buffer.
        bool Add( VirtualBuffer* pVBuf , Pointer pFromAddress = nullptr );

        // Remove virtual memory from a buffer.
        bool Remove( VirtualBuffer* pVBuf );

        // Add bytes from a current process to the buffer.
        bool AddLocal( Pointer pAddressAdd , HEX pFromAddress , HEX HexSizeToAdd );

        // Replaces bytes from a current process to the buffer.
        bool ReplaceLocal( Pointer pAddressAdd , HEX pFromAddress , HEX HexSizeToAdd );

        // Remove bytes from a current process to the buffer.
        bool RemoveLocal( HEX pFromAddress , HEX HexSizeToRemove );

        // Write bytes from a current process to the buffer.
        bool WriteToProcessFromCurrent( Pointer pAddressLocalData , HEX HexSizeOfSource );

        // Transfer buffer to another process.
        bool TransferToProcess( Pointer pChangedProcess = ( Pointer ) GetCurrentProcess() );

        // Compare size to another buffer.
        HEX Compare( VirtualBuffer* pVBuf );

        // Find the offset into the buffer.
        HEX Find( VirtualBuffer*pVBuf );

        // Find the offset with bytes or local data (current process).
        HEX FindLocal( Pointer pAddressSource , HEX HexSizeOfSource );

        void Free();

        bool operator>( VirtualBuffer *pVBuf );

        bool operator<( VirtualBuffer *pVBuf );

        bool operator==( VirtualBuffer *pVBuf );

        bool operator>=( VirtualBuffer *pVBuf );

        bool operator<=( VirtualBuffer *pVBuf );

        bool operator!=( VirtualBuffer *pVBuf );

        bool operator>( HEX _HexSize );

        bool operator<( HEX _HexSize );

        bool operator==( HEX _HexSize );

        HEX operator==( std::vector<Byte> Value );

        HEX operator==( stdString Value );

        template<typename T = Byte>HEX operator==( Buffer<T> &Value )
        {
            return FindLocal( ( Pointer ) Value.P() , Value.m_Size );
        }

        bool operator<=( HEX _HexSize );

        bool operator>=( HEX _HexSize );

        bool operator!=( HEX _HexSize );

        bool operator=( VirtualBuffer *pVBuf );

        bool operator+=( VirtualBuffer *pVBuf );

        bool operator-=( VirtualBuffer *pVBuf );

        bool operator+=( std::vector<Byte> Value );

        bool operator+=( stdString Value );

        bool operator-=( std::vector<Byte> Value );

        bool operator-=( stdString Value );

        template<typename T = Byte>bool operator+=( Buffer<T> &Value )
        {
            return AddLocal( ( Pointer ) Value.P() , HexSize , Value.m_Size );
        }

        template<typename T = Byte>bool operator-=( Buffer<T> &Value )
        {
            HEX Offset = FindLocal( ( Pointer ) Value.P() , Value.m_Size );

            if ( Offset != -1 )
            {
                return RemoveLocal( Offset , Value.m_Size );
            }
            else
            {
                CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "[%s->operator-=] Couldn't find offset\n" ) , sName.c_str() );
            }
        }

        template<typename T = Byte>bool operator=( Buffer<T> &Value )
        {
            bool bRet = false;

            if ( HexSlot != -1 )
            {
                bRet = ReplaceLocal( ( Pointer ) Value.P() , HexSlot , Value.m_Size );
                HexSlot = -1;
            }

            return bRet;
        }

        bool operator-=( HEX _HexSize );

        bool operator=( std::vector<Byte> Value );

        bool operator=( Byte Value );

        bool operator=( stdString Value );

        bool UnProtect();

        VirtualBuffer &operator[]( HEX HexValue );

        Pointer operator[]( HEX HexValue ) const;

    public:

        // pAllocationAddress is where we want to allocate virtual memory.
        // pProcess is wich process the virtual memory is allocated for.
        // pAddress is the address of the buffer.
        Pointer pAddress , pProcess , pAllocationAddress;

        // Size of buffer
        HEX HexSize;

        HEX HexSlot = -1;

        // Name of buffer
        stdString sName;

        //Initialized buffer
        bool bInitialized = false;

        //Table of protection flags.
        VirtualMemoryFlags Flags;
    };
};

#endif