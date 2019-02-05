#include "Includes.hxx"
#include "Lib.hxx"

N_VirtualMemory::VirtualMemoryFlags &N_VirtualMemory::FillVirtualMemoryFlags( size_t sSize , uHEX32 hFlags )
{
    std::vector<uHEX32> vhFlags( sSize );

    for ( auto &&i : vhFlags )
        i = hFlags;

    return *new N_VirtualMemory::VirtualMemoryFlags( vhFlags );
}

bool N_VirtualMemory::VirtualModifyProtectionFlags( Pointer pAddress
                                                    , Pointer pProcess
                                                    , HEX HexSize
                                                    , uHEX32 HexProtectionFlags
                                                    , puHEX32 pHexOldProtectionFlags )
{
    uHEX32 OldProtectionFlags;
    bool bReturn = VirtualProtectEx( pProcess , pAddress , HexSize , HexProtectionFlags , &OldProtectionFlags );

    if ( pHexOldProtectionFlags != nullptr )
    {
        *pHexOldProtectionFlags = OldProtectionFlags;
    }

    return bReturn;
}

bool N_VirtualMemory::VirtualModifyProtectionFlags( Pointer pAddress
                                                    , Pointer pProcess
                                                    , VirtualMemoryFlags& Flags )
{
    bool bReturn = true;

    size_t sRememberSlot = 0;
    uHEX32 hFirstFlag = Flags.m_hFlags[ sRememberSlot ];

    class RememberVirtualFlags
    {
    public:

        RememberVirtualFlags( uHEX32 hFlags , size_t start , size_t end )
        {
            m_hFlags = hFlags;
            m_start = start;
            m_end = end;
        }

        uHEX32 m_hFlags;
        size_t m_start , m_end;
    };

    std::vector<RememberVirtualFlags> RVF;

    for ( size_t i = 0; i != Flags.m_hFlags.size(); i++ )
    {
        if ( hFirstFlag != Flags.m_hFlags[ i ] )
        {
            RVF.push_back( RememberVirtualFlags( hFirstFlag , sRememberSlot , i - sRememberSlot ) );
            sRememberSlot = i;
            hFirstFlag = Flags.m_hFlags[ i ];
        }

        if ( i + 1 == Flags.m_hFlags.size() )
        {
            RVF.push_back( RememberVirtualFlags( Flags.m_hFlags[ i ] , sRememberSlot , i - sRememberSlot + 1 ) );
        }
    }

    for ( auto &&it : RVF )
    {
        if ( !VirtualModifyProtectionFlags( ( Pointer ) ( ( HEX ) pAddress + ( HEX ) it.m_start ) , pProcess , ( HEX ) it.m_end , it.m_hFlags ) )
        {
            CONSOLEDEBUG( TEXT( "[VirtualModifyProtectionFlags] Failed. (0x%p)\n" ) , GetLastError() );
            bReturn = false;
        }
    }

    return bReturn;
}

// Allocate virtual memory.
Pointer N_VirtualMemory::VirtualAllocation( HEX HexSize
                                            , VirtualMemoryFlags& Flags
                                            , Pointer pProcess
                                            , Pointer pAllocationAddress )
{
    Pointer pAddress = VirtualAllocEx( pProcess , pAllocationAddress , HexSize , MEM_COMMIT | MEM_RESERVE , PAGE_EXECUTE_READWRITE );

    if ( pAddress != nullptr )
    {
        if ( VirtualModifyProtectionFlags( pAddress , pProcess , Flags ) )
            return pAddress;
        else
            return nullptr;
    }

    return nullptr;
}

Pointer N_VirtualMemory::VirtualAllocation( HEX HexSize
                                            , uHEX32 HexFlag
                                            , Pointer pProcess
                                            , Pointer pAllocationAddress )
{
    return VirtualAllocEx( pProcess , pAllocationAddress , HexSize , MEM_COMMIT | MEM_RESERVE , HexFlag );
}

// Free virtual memory.
bool N_VirtualMemory::FreeVirtualAllocation( Pointer pAddress , Pointer pProcess , bool bLastCall )
{
    bool bReturn = VirtualFreeEx( pProcess , pAddress , 0 , MEM_RELEASE );

    if ( !bReturn && !bLastCall )
    {
        Pointer pNewAddress = &pAddress;
        bReturn = FreeVirtualAllocation( pNewAddress , pProcess , true );
    }

    return bReturn;
}

// Read virtual memory.
bool N_VirtualMemory::VirtualReadMemory( Pointer pAddress , Pointer pRead , HEX HexSize
                                         , VirtualMemoryFlags& Flags
                                         , Pointer pProcess , pHEX pHexNbOfReadBytes , bool bLastCall )
{
    bool bReturn = false;

    // Let us use read memory please
    if ( VirtualModifyProtectionFlags( pAddress , pProcess , HexSize , PAGE_EXECUTE_READWRITE ) )
    {
        HEX HexNbOfReadBytes = 0;
        if ( ReadProcessMemory( pProcess , pAddress , pRead , HexSize , ( SIZE_T* ) &HexNbOfReadBytes ) )
        {
            if ( pHexNbOfReadBytes != nullptr )
            {
                *pHexNbOfReadBytes = HexNbOfReadBytes;
            }

            if ( VirtualModifyProtectionFlags( pAddress , pProcess , Flags ) )
            {
                bReturn = true;
            }
        }
    }

    if ( !bReturn && !bLastCall )
    {
        Pointer pNewAddress = &pAddress;
        Pointer pNewRead = &pRead;

        bReturn = VirtualReadMemory( pNewAddress , pNewRead , HexSize , Flags , pProcess , pHexNbOfReadBytes , true );
    }

    return bReturn;
}

// Write virtual memory.
bool N_VirtualMemory::VirtualWriteMemory( Pointer pAddress , Pointer pWrite , HEX HexSize
                                          , VirtualMemoryFlags& Flags
                                          , Pointer pProcess
                                          , pHEX pHexNbOfWriteBytes , bool bLastCall )
{
    bool bReturn = false;

    // Let us use write memory please
    if ( VirtualModifyProtectionFlags( pAddress , pProcess , HexSize , PAGE_EXECUTE_READWRITE ) )
    {
        HEX HexNbOfWriteBytes = 0;
        if ( WriteProcessMemory( pProcess , pAddress , pWrite , HexSize , ( SIZE_T* ) &HexNbOfWriteBytes ) )
        {
            if ( pHexNbOfWriteBytes != nullptr )
            {
                *pHexNbOfWriteBytes = HexNbOfWriteBytes;
            }

            if ( VirtualModifyProtectionFlags( pAddress , pProcess , Flags ) )
            {
                bReturn = true;
            }
        }
    }

    if ( !bReturn && !bLastCall )
    {
        Pointer pNewAddress = &pAddress;
        Pointer pNewWrite = &pWrite;

        bReturn = VirtualReadMemory( pNewAddress , pNewWrite , HexSize , Flags , pProcess , pHexNbOfWriteBytes , true );
    }

    return bReturn;
}

// Get virtual memory information.

void N_VirtualMemory::VirtualQueryMBI( Pointer pAddress
                                       , HEX HexSize
                                       , PMEMORY_BASIC_INFORMATION pMBI
                                       , Pointer pProcess
                                       , HEX *_HexNbBuffer )
{
    HEX HexNbBuffer = ( HEX ) ( VirtualQueryEx( pProcess , pAddress , pMBI , ( SIZE_T ) HexSize ) );

    if ( _HexNbBuffer != nullptr )
    {
        *_HexNbBuffer = HexNbBuffer;
    }
}

HEX N_VirtualMemory::VirtualQueryProtectionFlags( Pointer pAddress , HEX HexSize , Pointer pProcess )
{
    HEX HexNbBuffer;

    MEMORY_BASIC_INFORMATION MBI;
    VirtualQueryMBI( pAddress , HexSize , &MBI , pProcess , &HexNbBuffer );

    if ( HexNbBuffer == 0 )
    {
        CONSOLEDEBUG( TEXT( "[Query] ProtectionFlags failed. (0x%p)\n" ) , pAddress );
        return 0;
    }

    return MBI.AllocationProtect;
}

HEX N_VirtualMemory::VirtualQuerySize( Pointer pAddress , HEX HexSize , Pointer pProcess )
{
    HEX HexNbBuffer;

    MEMORY_BASIC_INFORMATION MBI;
    VirtualQueryMBI( pAddress , HexSize , &MBI , pProcess , &HexNbBuffer );

    if ( HexNbBuffer == 0 )
    {
        CONSOLEDEBUG( TEXT( "[Query] Size failed. (0x%p)\n" ) , pAddress );
        return 0;
    }

    return ( HEX ) MBI.RegionSize;
}

HEX N_VirtualMemory::VirtualQueryState( Pointer pAddress , HEX HexSize , Pointer pProcess )
{
    HEX HexNbBuffer;

    MEMORY_BASIC_INFORMATION MBI;
    VirtualQueryMBI( pAddress , HexSize , &MBI , pProcess , &HexNbBuffer );

    if ( HexNbBuffer == 0 )
    {
        CONSOLEDEBUG( TEXT( "[Query] State failed. (0x%p)\n" ) , pAddress );
        return 0;
    }

    return ( HEX ) MBI.State;
}

HEX N_VirtualMemory::VirtualQueryType( Pointer pAddress , HEX HexSize , Pointer pProcess )
{
    HEX HexNbBuffer;

    MEMORY_BASIC_INFORMATION MBI;
    VirtualQueryMBI( pAddress , HexSize , &MBI , pProcess , &HexNbBuffer );

    if ( HexNbBuffer == 0 )
    {
        CONSOLEDEBUG( TEXT( "[Query] Type failed. (0x%p)\n" ) , pAddress );
        return 0;
    }

    return MBI.Type;
}

Pointer N_VirtualMemory::VirtualQueryBaseAddress( Pointer pAddress , HEX HexSize , Pointer pProcess )
{
    HEX HexNbBuffer;

    MEMORY_BASIC_INFORMATION MBI;
    VirtualQueryMBI( pAddress , HexSize , &MBI , pProcess , &HexNbBuffer );

    if ( HexNbBuffer == 0 )
    {
        CONSOLEDEBUG( TEXT( "[Query] BaseAddress failed. (0x%p)\n" ) , pAddress );
        return 0;
    }

    return MBI.BaseAddress;
}

HEX N_VirtualMemory::VirtualQueryAllocationProtect( Pointer pAddress , HEX HexSize , Pointer pProcess )
{
    HEX HexNbBuffer;

    MEMORY_BASIC_INFORMATION MBI;
    VirtualQueryMBI( pAddress , HexSize , &MBI , pProcess , &HexNbBuffer );

    if ( HexNbBuffer == 0 )
    {
        CONSOLEDEBUG( TEXT( "[Query] AllocationProtect failed. (0x%p)\n" ) , pAddress );
        return 0;
    }

    return ( HEX ) MBI.AllocationProtect;
}

Pointer N_VirtualMemory::VirtualQueryAllocationBase( Pointer pAddress , HEX HexSize , Pointer pProcess )
{
    HEX HexNbBuffer;

    MEMORY_BASIC_INFORMATION MBI;
    VirtualQueryMBI( pAddress , HexSize , &MBI , pProcess , &HexNbBuffer );

    if ( HexNbBuffer == 0 )
    {
        CONSOLEDEBUG( TEXT( "[Query] AllocationBase failed. (0x%p)\n" ) , pAddress );
        return 0;
    }

    return MBI.AllocationBase;
}

// Write virtual memory from the current process
bool N_VirtualMemory::WriteVirtualMemoryFromCurrentProcess_S( Pointer pAddressDestination , Pointer pAddressSource
                                                              , HEX &HexSizeOfDestination , HEX HexSizeOfSource
                                                              , VirtualMemoryFlags& Flags
                                                              , Pointer pProcessDestination
                                                              , Pointer pRebaseAddressDestination )
{
    Pointer pOldAddressDestination = pAddressDestination;

    CONSOLEDEBUGBYTES( ( Bytes ) pAddressSource , HexSizeOfSource , TEXT( "pTempSource_WVMs" ) );

    // If the write size is higher than our allocated image, we need to realloc it at the same address, if not, then allocate somewhere else.

    if ( HexSizeOfDestination < HexSizeOfSource )
    {
        if ( !FreeVirtualAllocation( pAddressDestination , pProcessDestination ) )
        {
            CONSOLEDEBUG( TEXT( "[WVMs] Failed to free virtual memory: (LastError: 0x%p) 0x%p\n" ) , GetLastError() , pAddressDestination );
            return false;
        }

        pAddressDestination = VirtualAllocation( HexSizeOfSource , Flags , pProcessDestination , pOldAddressDestination );

        if ( pAddressDestination == nullptr )
        {
            CONSOLEDEBUG( TEXT( "[WVMs] Failed to allocate virtual memory for destination buffer on the same base address\n" ) );

            pAddressDestination = VirtualAllocation( HexSizeOfSource , Flags , pProcessDestination , pRebaseAddressDestination );

            if ( pAddressDestination == nullptr )
            {
                CONSOLEDEBUG( TEXT( "[WVMs] Failed to allocate virtual memory for destination buffer on the asked base address\n" ) );

                pAddressDestination = VirtualAllocation( HexSizeOfSource , Flags , pProcessDestination );

                if ( pAddressDestination == nullptr )
                {
                    CONSOLEDEBUG( TEXT( "[WVMs] Failed to allocate virtual memory for the destination buffer\n" ) );
                    return false;
                }
            }
        }

        HexSizeOfDestination = HexSizeOfSource;
    }

    if ( !VirtualWriteMemory( pAddressDestination , pAddressSource , HexSizeOfSource , Flags , pProcessDestination ) )
    {
        CONSOLEDEBUG( TEXT( "[WVMs] Failed to write virtual memory for the destination buffer\n" ) );
        return false;
    }

    return true;
}

// Copy virtual memory from a process, to another process.
bool N_VirtualMemory::CopyVirtualMemory_S( Pointer pAddressDestination , HEX &HexSizeOfDestination
                                           , Pointer pAddressSource , HEX HexSizeOfSource
                                           , Pointer pProcessDestination , Pointer pProcessSource
                                           , VirtualMemoryFlags& FlagsDestination
                                           , VirtualMemoryFlags& FlagsSource
                                           , Pointer pRebaseAddressDestination )
{
    Pointer pTempSource = Alloc( HexSizeOfSource );

    if ( !VirtualReadMemory( pAddressSource , pTempSource , HexSizeOfSource , FlagsSource , pProcessSource ) )
    {
        FreeAlloc( pTempSource );
        CONSOLEDEBUG( TEXT( "[CopyVMs] Failed to read virtual memory: (Source) 0x%p\n" ) , pAddressSource );
    }

    CONSOLEDEBUGBYTES( ( Bytes ) pTempSource , HexSizeOfSource , TEXT( "pTempSource_CopyVMs" ) );

    // If the write size is higher than our allocated image size, we need to realloc it at the same address, if not, then allocate somewhere else.

    FlagsDestination = FlagsSource;

    if ( HexSizeOfDestination < HexSizeOfSource )
    {
        Pointer pOldAddressDestination = pAddressDestination;

        if ( !FreeVirtualAllocation( pAddressDestination , pProcessDestination ) )
        {
            FreeAlloc( pTempSource );
            CONSOLEDEBUG( TEXT( "[CopyVMs] Failed to free virtual memory: (Destination) 0x%p\n" ) , pAddressDestination );
            return false;
        }

        pAddressDestination = VirtualAllocation( HexSizeOfSource , FlagsDestination , pProcessDestination , pOldAddressDestination );

        if ( pAddressDestination == nullptr )
        {
            CONSOLEDEBUG( TEXT( "[CopyVMs] Failed to allocate virtual memory for destination buffer on the same base address\n" ) );

            pAddressDestination = VirtualAllocation( HexSizeOfSource , FlagsDestination , pProcessDestination , pRebaseAddressDestination );

            if ( pAddressDestination == nullptr )
            {
                CONSOLEDEBUG( TEXT( "[CopyVMs] Failed to allocate virtual memory for destination buffer on the asked base address\n" ) );

                pAddressDestination = VirtualAllocation( HexSizeOfSource , FlagsDestination , pProcessDestination );

                if ( pAddressDestination == nullptr )
                {
                    FreeAlloc( pTempSource );
                    CONSOLEDEBUG( TEXT( "[CopyVMs] Failed to allocate virtual memory for the destination buffer\n" ) );
                    return false;
                }
            }
        }
    }

    if ( !VirtualWriteMemory( pAddressDestination , pTempSource , HexSizeOfSource , FlagsSource , pProcessDestination ) )
    {
        FreeAlloc( pTempSource );
        CONSOLEDEBUG( TEXT( "[CopyVMs] Failed to write virtual memory for the destination buffer\n" ) );
        return false;
    }

    HexSizeOfDestination = HexSizeOfSource;

    FreeAlloc( pTempSource );

    return true;
}

// Compare how much the data is not corresponding.

HEX N_VirtualMemory::CompareVirtualMemory_S( Pointer pAddressDestination , HEX HexSizeOfDestination , Pointer pAddressSource , HEX HexSizeOfSource
                                             , VirtualMemoryFlags& FlagsDestination
                                             , VirtualMemoryFlags& FlagsSource
                                             , Pointer pProcessDestination , Pointer pProcessSource , bool *bFailed )
{
    *bFailed = false;

    // Read both virtual memories, and we use memcmp to compare by how many bytes is shifted between the Destination by the Source.

    Pointer pTempDestination = Alloc( HexSizeOfDestination );
    if ( !VirtualReadMemory( pAddressDestination , pTempDestination , HexSizeOfDestination , FlagsDestination , pProcessDestination ) )
    {
        *bFailed = true;
        FreeAlloc( pTempDestination );
        CONSOLEDEBUG( TEXT( "[CompareVMs] Failed to read virtual memory: (Destination) 0x%p\n" ) , pAddressDestination );
        return 0;
    }

    Pointer pTempSource = Alloc( HexSizeOfSource );
    if ( !VirtualReadMemory( pAddressSource , pTempSource , HexSizeOfSource , FlagsSource , pProcessSource ) )
    {
        *bFailed = true;
        FreeAlloc( pTempSource );
        FreeAlloc( pTempDestination );
        CONSOLEDEBUG( TEXT( "[CompareVMs] Failed to read virtual memory: (Source) 0x%p\n" ) , pAddressSource );
        return 0;
    }

    CONSOLEDEBUGBYTES( ( Bytes ) pTempSource , HexSizeOfSource , TEXT( "pTempSource_CompareVMs" ) );
    CONSOLEDEBUGBYTES( ( Bytes ) pTempDestination , HexSizeOfDestination , TEXT( "pTempDestination_CompareVMs" ) );

    HEX HexRetCode = 0;

    if ( HexSizeOfSource < HexSizeOfDestination )
        HexRetCode = ( HEX ) memcmp( pTempSource , pTempDestination , HexSizeOfDestination );
    else
        HexRetCode = ( HEX ) memcmp( pTempSource , pTempDestination , HexSizeOfSource );

    FreeAlloc( pTempSource );
    FreeAlloc( pTempDestination );

    return HexRetCode;
}

// Find the offset in the virtual memory, from a process, to another.
// We could use aternativly memcmp though.
// Same code as in SigScanning.h +/-

HEX N_VirtualMemory::FindOffsetVirtualMemory_s( Pointer pAddressDestination , HEX HexSizeOfDestination
                                                , Pointer pAddressSource , HEX HexSizeOfSource
                                                , VirtualMemoryFlags& FlagsDestination
                                                , VirtualMemoryFlags& FlagsSource
                                                , Pointer pProcessDestination , Pointer pProcessSource
                                                , bool *bFailed )
{
    if ( bFailed != nullptr )
        *bFailed = false;

    if ( HexSizeOfDestination < HexSizeOfSource )
    {
        CONSOLEDEBUG( TEXT( "[FindOffsetVMs] The source size is too high!\n" ) , pAddressDestination );

        if ( bFailed != nullptr )
            *bFailed = true;

        return 0;
    }

    Pointer pTempDestination = Alloc( HexSizeOfDestination );
    if ( !VirtualReadMemory( pAddressDestination , pTempDestination , HexSizeOfDestination , FlagsDestination , pProcessDestination ) )
    {
        FreeAlloc( pTempDestination );
        CONSOLEDEBUG( TEXT( "[FindOffsetVMs] Failed to read virtual memory: (Destination) 0x%p\n" ) , pAddressDestination );

        if ( bFailed != nullptr )
            *bFailed = true;

        return 0;
    }

    Pointer pTempSource = Alloc( HexSizeOfSource );
    if ( !VirtualReadMemory( pAddressSource , pTempSource , HexSizeOfSource , FlagsSource , pProcessSource ) )
    {
        FreeAlloc( pTempSource );
        FreeAlloc( pTempDestination );
        CONSOLEDEBUG( TEXT( "[FindOffsetVMs] Failed to read virtual memory: (Source) 0x%p\n" ) , pAddressSource );

        if ( bFailed != nullptr )
            *bFailed = true;

        return 0;
    }

    CONSOLEDEBUGBYTES( ( Bytes ) pTempSource , HexSizeOfSource , TEXT( "pTempSource_FindOffsetVMs" ) );
    CONSOLEDEBUGBYTES( ( Bytes ) pTempDestination , HexSizeOfDestination , TEXT( "pTempDestination_FindOffsetVMs" ) );

    HEX iDest = 0;
    bool bBreakCalled = false;

    do
    {
        if ( memcmp( ( Pointer ) ( ( HEX ) pTempDestination + iDest ) , pTempSource , HexSizeOfSource ) == 0 )
        {
            bBreakCalled = true;
        }

        iDest++;
    } while ( iDest < HexSizeOfDestination && !bBreakCalled );

    FreeAlloc( pTempSource );
    FreeAlloc( pTempDestination );

    if ( bFailed != nullptr )
        *bFailed = !bBreakCalled;

    if ( bBreakCalled )
    {
        return iDest - 1;
    }
    else
    {
        return 0;
    }
}

bool N_VirtualMemory::RemoveVirtualMemory_S( Pointer pAddress , HEX &HexSize , HEX pFromAddress , HEX HexSizeToRemove
                                             , VirtualMemoryFlags& Flags
                                             , Pointer pProcess
                                             , Pointer pRebaseAddressDestination )
{
    if ( HexSizeToRemove > HexSize )
    {
        CONSOLEDEBUG( TEXT( "[RemoveVMs] too much virtual memory to remove\n" ) );
        return false;
    }

    if ( pFromAddress < 0 )
    {
        CONSOLEDEBUG( TEXT( "[RemoveVMs] from address is negative\n" ) );
        return false;
    }

    if ( pFromAddress > HexSize )
    {
        CONSOLEDEBUG( TEXT( "[RemoveVMs] from address is too high\n" ) );
        return false;
    }

    // HexSize = 255
    // pFromAddress = 254
    // HexSizeToRemove = 2
    // 255 - ( ( 254 - 255 ) + 2 )
    // = -1  -> Too much to remove

    //  if ( HexSizeToRemove > HexSize ) already covered so it's fine.

    HEX HexDifToRemove = HexSize - ( ( pFromAddress - HexSize ) + HexSizeToRemove );

    if ( HexDifToRemove < 0 )
    {
        CONSOLEDEBUG( TEXT( "[RemoveVMs] Virtual memory from that address to remove is out of buffer! (Max: 0x%p, Requested From: 0x%p To: 0x%p)\n" )
                      , ( ( HEX ) pAddress + HexSize )
                      , ( ( HEX ) pAddress + pFromAddress )
                      , ( ( HEX ) pAddress + pFromAddress + HexSizeToRemove ) );
        return false;
    }

    Pointer pTemp = Alloc( HexSize );

    if ( !VirtualReadMemory( pAddress , pTemp , HexSize , Flags , pProcess ) )
    {
        FreeAlloc( pTemp );
        CONSOLEDEBUG( TEXT( "[RemoveVMs] Failed to read virtual memory: (LastError: 0x%p) 0x%p\n" ) , GetLastError() , pAddress );
        return false;
    }

    CONSOLEDEBUGBYTES( ( Bytes ) pTemp , HexSize , TEXT( "pTempOriginal_RemoveVMCPs" ) );

    Pointer pOldAddress = pAddress;

    HEX HexNewSize = HexSize - HexSizeToRemove;
    HEX HexBytesToMove = HexSize - ( pFromAddress + HexSizeToRemove );

    if ( HexBytesToMove > 0 )
    {
        Flags.m_hFlags.erase( Flags.m_hFlags.begin() + pFromAddress , Flags.m_hFlags.begin() + pFromAddress + HexSizeToRemove );
    }
    else
    {
        Flags.m_hFlags.erase( Flags.m_hFlags.begin() + HexNewSize , Flags.m_hFlags.end() );
    }

    if ( !FreeVirtualAllocation( pAddress , pProcess ) )
    {
        FreeAlloc( pTemp );
        CONSOLEDEBUG( TEXT( "[RemoveVMs] Failed to free virtual memory: (LastError: 0x%p) 0x%p\n" ) , GetLastError() , pAddress );
        return false;
    }

    // Realloc memory to remove the bytes needed.

    pAddress = VirtualAllocation( HexNewSize , Flags , pProcess , pOldAddress );

    if ( pAddress == nullptr )
    {
        CONSOLEDEBUG( TEXT( "[RemoveVMs] Failed to allocate virtual memory for destination buffer on the same base address\n" ) );

        pAddress = VirtualAllocation( HexNewSize , Flags , pProcess , pRebaseAddressDestination );

        if ( pAddress == nullptr )
        {
            CONSOLEDEBUG( TEXT( "[RemoveVMs] Failed to allocate virtual memory for destination buffer on the asked base address\n" ) );

            pAddress = VirtualAllocation( HexNewSize , Flags , pProcess );

            if ( pAddress == nullptr )
            {
                FreeAlloc( pTemp );
                CONSOLEDEBUG( TEXT( "[RemoveVMs] Failed to allocate virtual memory for the destination buffer\n" ) );
                return false;
            }
        }
    }

    Bytes pbStart = ( Bytes ) ( ( HEX ) pTemp + ( HEX ) pFromAddress );
    Bytes pbToMove = ( Bytes ) ( ( HEX ) pTemp + ( pFromAddress + HexSizeToRemove ) );

    // Move the bytes so we don't loose data that is after the size to remove.
    // DATA = ○ , DATATOREMOVE = •
    // ○ ○ ○ ○ ○ • • • ○ ○
    // Becomes -> ○ ○ ○ ○ ○ ○ ○ Instead of ○ ○ ○ ○ ○ nullbyte nullbyte nullbyte ○ ○
    // This is better like this (for examples in strings)

    if ( HexBytesToMove > 0 )
    {
        for ( HEX i = 0; i < HexBytesToMove; i++ )
        {
            pbStart[ i ] = pbToMove[ i ];
        }
    }

    CONSOLEDEBUGBYTES( ( Bytes ) pTemp , HexNewSize , TEXT( "pTempNew_RemoveVMs" ) );

    if ( !VirtualWriteMemory( pAddress , pTemp , HexNewSize , Flags , pProcess ) )
    {
        FreeAlloc( pTemp );
        CONSOLEDEBUG( TEXT( "[RemoveVMs] Failed to write virtual memory for the destination buffer\n" ) );
        return false;
    }

    HexSize = HexNewSize;

    FreeAlloc( pTemp );

    return true;
}

bool N_VirtualMemory::ReplaceVirtualMemory_S( Pointer pFromAddress , Pointer pAddressDestination , Pointer pAddressSource
                                              , HEX &HexSizeOfDestination , HEX HexSizeOfSource
                                              , Pointer pProcessDestination
                                              , Pointer pProcessSource
                                              , VirtualMemoryFlags& FlagsDestination
                                              , VirtualMemoryFlags& FlagsSource
                                              , Pointer pRebaseAddressDestination )
{
    if ( HexSizeOfSource <= 0 )
    {
        CONSOLEDEBUG( TEXT( "[ReplaceVMs] Nothing to replace\n" ) );
        return false;
    }

    HEX HexNewSize = HexSizeOfDestination;

    HEX HexMaxSizeToWrite = ( HEX ) pFromAddress + HexSizeOfSource;

    if ( HexMaxSizeToWrite > HexSizeOfDestination )
    {
        HexNewSize = HexMaxSizeToWrite;
    }

    Pointer pTempSource = Alloc( HexSizeOfSource );

    if ( !VirtualReadMemory( pAddressSource , pTempSource , HexSizeOfSource , FlagsSource , pProcessSource ) )
    {
        FreeAlloc( pTempSource );
        CONSOLEDEBUG( TEXT( "[ReplaceVMs] Failed to read virtual memory: (LastError: 0x%p) 0x%p\n" ) , GetLastError() , pAddressSource );
        return false;
    }

    Pointer pTempDestination = Alloc( HexNewSize );

    if ( !VirtualReadMemory( pAddressDestination , pTempDestination , HexSizeOfDestination , FlagsDestination , pProcessDestination ) )
    {
        FreeAlloc( pTempSource );
        FreeAlloc( pTempDestination );
        CONSOLEDEBUG( TEXT( "[ReplaceVMs] Failed to read virtual memory: (LastError: 0x%p) 0x%p\n" ) , GetLastError() , pAddressDestination );
        return false;
    }

    CONSOLEDEBUGBYTES( ( Bytes ) pTempSource , HexSizeOfSource , TEXT( "pTempSource_ReplaceVMs" ) );
    CONSOLEDEBUGBYTES( ( Bytes ) pTempDestination , HexSizeOfDestination , TEXT( "pTempDestination_ReplaceVMs" ) );

    FlagsDestination.m_hFlags.resize( HexNewSize );

    if ( HexMaxSizeToWrite > HexSizeOfDestination )
    {
        for ( HEX i = HexSizeOfDestination; i != HexNewSize; i++ )
        {
            FlagsDestination.m_hFlags[ i ] = FlagsSource.m_hFlags[ i - HexSizeOfDestination ];
        }
    }

    Pointer pOldAddressDestination = pAddressDestination;

    if ( !FreeVirtualAllocation( pAddressDestination , pProcessDestination ) )
    {
        FreeAlloc( pTempSource );
        FreeAlloc( pTempDestination );
        CONSOLEDEBUG( TEXT( "[ReplaceVMs] Failed to free virtual memory: (LastError: 0x%p) 0x%p\n" ) , GetLastError() , pAddressDestination );
        return false;
    }

    pAddressDestination = VirtualAllocation( HexNewSize , FlagsDestination , pProcessDestination , pOldAddressDestination );

    if ( pAddressDestination == nullptr )
    {
        CONSOLEDEBUG( TEXT( "[ReplaceVMs] Failed to allocate virtual memory for destination buffer on the same base address\n" ) );

        pAddressDestination = VirtualAllocation( HexNewSize , FlagsDestination , pProcessDestination , pRebaseAddressDestination );

        if ( pAddressDestination == nullptr )
        {
            CONSOLEDEBUG( TEXT( "[ReplaceVMs] Failed to allocate virtual memory for destination buffer on the asked base address\n" ) );

            pAddressDestination = VirtualAllocation( HexNewSize , FlagsDestination , pProcessDestination );

            if ( pAddressDestination == nullptr )
            {
                FreeAlloc( pTempSource );
                FreeAlloc( pTempDestination );
                CONSOLEDEBUG( TEXT( "[ReplaceVMs] Failed to allocate virtual memory for the destination buffer\n" ) );
                return false;
            }
        }
    }

    memcpy( ( Pointer ) ( ( HEX ) pTempDestination + ( HEX ) pFromAddress ) , pTempSource , HexSizeOfSource );

    CONSOLEDEBUGBYTES( ( Bytes ) pTempDestination , HexNewSize , TEXT( "pTempFinalDestination_ReplaceVMs" ) );

    if ( !VirtualWriteMemory( pAddressDestination , pTempDestination , HexNewSize , FlagsDestination , pProcessDestination ) )
    {
        FreeAlloc( pTempSource );
        FreeAlloc( pTempDestination );
        CONSOLEDEBUG( TEXT( "[ReplaceVMs] Failed to write virtual memory for the destination buffer\n" ) );
        return false;
    }

    HexSizeOfDestination = HexNewSize;

    FreeAlloc( pTempSource );
    FreeAlloc( pTempDestination );

    return true;
}

// First we just add virtual memory in where we want to and move the saved bytes from where it has been written.
bool N_VirtualMemory::AddVirtualMemory_S( Pointer pFromAddress , Pointer pAddressDestination , Pointer pAddressSource
                                          , HEX &HexSizeOfDestination , HEX HexSizeOfSource
                                          , Pointer pProcessDestination
                                          , Pointer pProcessSource
                                          , VirtualMemoryFlags& FlagsDestination
                                          , VirtualMemoryFlags& FlagsSource
                                          , Pointer pRebaseAddressDestination )
{
    if ( HexSizeOfSource <= 0 )
    {
        CONSOLEDEBUG( TEXT( "[AddVMs] Nothing to add\n" ) );
        return false;
    }

    HEX HexSizeToAddAtEnd = ( HEX ) pFromAddress - HexSizeOfDestination;
    HEX HexNewSize = HexSizeOfDestination + HexSizeOfSource;

    if ( HexSizeToAddAtEnd > 0 )
        HexNewSize += HexSizeToAddAtEnd;

    Pointer pTempSource = Alloc( HexSizeOfSource );

    if ( !VirtualReadMemory( pAddressSource , pTempSource , HexSizeOfSource , FlagsSource , pProcessSource ) )
    {
        FreeAlloc( pTempSource );
        CONSOLEDEBUG( TEXT( "[AddVMs] Failed to read virtual memory: (LastError: 0x%p) 0x%p\n" ) , GetLastError() , pAddressSource );
        return false;
    }

    Pointer pTempDestination = Alloc( HexNewSize );

    if ( !VirtualReadMemory( pAddressDestination , pTempDestination , HexSizeOfDestination , FlagsDestination , pProcessDestination ) )
    {
        FreeAlloc( pTempSource );
        FreeAlloc( pTempDestination );
        CONSOLEDEBUG( TEXT( "[AddVMs] Failed to read virtual memory: (LastError: 0x%p) 0x%p\n" ) , GetLastError() , pAddressDestination );
        return false;
    }

    CONSOLEDEBUGBYTES( ( Bytes ) pTempSource , HexSizeOfSource , TEXT( "pTempSource_AddVMs" ) );
    CONSOLEDEBUGBYTES( ( Bytes ) pTempDestination , HexSizeOfDestination , TEXT( "pTempDestination_AddVMs" ) );

    Pointer pOldAddressDestination = pAddressDestination;

    if ( !FreeVirtualAllocation( pAddressDestination , pProcessDestination ) )
    {
        FreeAlloc( pTempSource );
        FreeAlloc( pTempDestination );
        CONSOLEDEBUG( TEXT( "[AddVMs] Failed to free virtual memory: (LastError: 0x%p) 0x%p\n" ) , GetLastError() , pAddressDestination );
        return false;
    }

    FlagsDestination.m_hFlags.resize( HexNewSize );

    for ( HEX i = HexSizeOfDestination; i != HexNewSize; i++ )
    {
        FlagsDestination.m_hFlags[ i + HexSizeToAddAtEnd ] = FlagsSource.m_hFlags[ i - HexSizeOfDestination ];
    }

    pAddressDestination = VirtualAllocation( HexNewSize , FlagsDestination , pProcessDestination , pOldAddressDestination );

    if ( pAddressDestination == nullptr )
    {
        CONSOLEDEBUG( TEXT( "[AddVMs] Failed to allocate virtual memory for destination buffer on the same base address\n" ) );

        pAddressDestination = VirtualAllocation( HexNewSize , FlagsDestination , pProcessDestination , pRebaseAddressDestination );

        if ( pAddressDestination == nullptr )
        {
            CONSOLEDEBUG( TEXT( "[AddVMs] Failed to allocate virtual memory for destination buffer on the asked base address\n" ) );

            pAddressDestination = VirtualAllocation( HexNewSize , FlagsDestination , pProcessDestination );

            if ( pAddressDestination == nullptr )
            {
                FreeAlloc( pTempSource );
                FreeAlloc( pTempDestination );
                CONSOLEDEBUG( TEXT( "[AddVMs] Failed to allocate virtual memory for the destination buffer\n" ) );
                return false;
            }
        }
    }

    Bytes pTempModifyEnd = ( Bytes ) ( ( HEX ) pTempDestination + ( HEX ) pFromAddress + HexSizeOfSource );
    Bytes pTempModify = ( Bytes ) ( ( HEX ) pTempDestination + ( HEX ) pFromAddress );
    HEX HexSizeToMove = HexSizeOfDestination - ( HEX ) pFromAddress;

    if ( HexSizeToMove > 0 )
    {
        Pointer pCopiedTemp = Alloc( HexSizeOfDestination );
        memcpy( pCopiedTemp , pTempDestination , HexSizeOfDestination );
        pCopiedTemp = ( Pointer ) ( ( HEX ) pCopiedTemp + ( HEX ) pFromAddress );
        memcpy( pTempModifyEnd , pCopiedTemp , HexSizeToMove );
        FreeAlloc( pCopiedTemp );
    }

    memcpy( pTempModify , pTempSource , HexSizeOfSource );

    CONSOLEDEBUGBYTES( ( Bytes ) pTempDestination , HexNewSize , TEXT( "pTempFinalDestination_AddVMs" ) );

    if ( !VirtualWriteMemory( pAddressDestination , pTempDestination , HexNewSize , FlagsDestination , pProcessDestination ) )
    {
        FreeAlloc( pTempSource );
        FreeAlloc( pTempDestination );
        CONSOLEDEBUG( TEXT( "[AddVMs] Failed to write virtual memory for the destination buffer\n" ) );
        return false;
    }

    HexSizeOfDestination = HexNewSize;

    FreeAlloc( pTempSource );
    FreeAlloc( pTempDestination );

    return true;
}

 // Constructor allocate virtual memory for our buffer, and set the protection flags correctly to that allocated virtual memory.
N_VirtualMemory::VirtualBuffer::VirtualBuffer( HEX HexSize
                                               , uHEX32 HexFlag
                                               , Pointer pAllocationAddress
                                               , Pointer pProcess
                                               , const stdString& sName
                                               , Pointer pAddressToCopy )
{
    this->HexSize = HexSize;
    this->pProcess = pProcess;
    this->sName = sName;
    this->pAllocationAddress = pAllocationAddress;

    pAddress = VirtualAllocation( this->HexSize , HexFlag , this->pProcess , this->pAllocationAddress );

    bInitialized = true;

    if ( pAddress == nullptr )
    {
        bInitialized = false;

        pAddress = VirtualAllocation( this->HexSize , HexFlag , this->pProcess );

        bInitialized = true;

        if ( pAddress == nullptr )
        {
            CONSOLEDEBUG( TEXT( "Couldn't initialize Virtual Buffer: %s LastError: %p \n" ) , sName.c_str() , GetLastError() );
            bInitialized = false;
        }
    }

    Flags = FillVirtualMemoryFlags( HexSize , HexFlag );

    if ( !bInitialized ) return;

    CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "Initialized Virtual Buffer: %s (Address: 0x%p HexSize: %i, Process: 0x%p, AllocationAddress: 0x%p)\n" )
                       , this->sName.c_str()
                       , this->pAddress
                       , this->HexSize
                       , this->pProcess
                       , this->pAllocationAddress );

    if ( pAddressToCopy != nullptr )
    {
        if ( !WriteToProcessFromCurrent( pAddressToCopy , this->HexSize ) )
        {
            CONSOLEDEBUG( TEXT( "Couldn't copy data to initialize Virtual Buffer: %s\n" ) , sName.c_str() );
        }
    }
}

N_VirtualMemory::VirtualBuffer::VirtualBuffer( Pointer pAddress
                                               , HEX HexSize
                                               , VirtualMemoryFlags& SourceFlags
                                               , Pointer pProcess
                                               , const stdString& sName )
{
    this->pAddress = pAddress;
    this->HexSize = HexSize;
    this->pProcess = pProcess;
    this->sName = sName;
    this->pAllocationAddress = nullptr;

    Flags = SourceFlags;

    RefreshFlags();

    bInitialized = true;

    if ( !bInitialized ) return;

    CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "Initialized Virtual Buffer: %s (Address: 0x%p HexSize: %i, Process: 0x%p, AllocationAddress: 0x%p)\n" )
                       , this->sName.c_str()
                       , this->pAddress
                       , this->HexSize
                       , this->pProcess
                       , this->pAllocationAddress );
}

// In case we want to copy another buffer.
N_VirtualMemory::VirtualBuffer::VirtualBuffer( VirtualBuffer *pVBuf )
{
    Flags = pVBuf->Flags;
    HexSize = pVBuf->HexSize;
    pProcess = pVBuf->pProcess;
    sName = pVBuf->sName;
    pAllocationAddress = pVBuf->pAllocationAddress;
    pAddress = VirtualAllocation( HexSize , PAGE_EXECUTE_READWRITE , pProcess , pAllocationAddress );

    bInitialized = true;

    if ( pAddress == nullptr )
    {
        bInitialized = false;

        pAddress = VirtualAllocation( HexSize , PAGE_EXECUTE_READWRITE , pProcess );

        bInitialized = true;

        if ( pAddress == nullptr )
        {
            CONSOLEDEBUG( TEXT( "Couldn't initialize Virtual Buffer: %s\n" ) , sName.c_str() );
            bInitialized = false;
        }
    }

    if ( !bInitialized ) return;

    CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "Initialized Virtual Buffer: %s (Address: 0x%p HexSize: %i, Process: 0x%p, AllocationAddress: 0x%p)\n" )
                       , sName.c_str()
                       , pAddress
                       , HexSize
                       , pProcess
                       , pAllocationAddress );

    if ( RefreshFlags() )
    {
        if ( !Copy( pVBuf ) )
        {
            CONSOLEDEBUG( TEXT( "Couldn't copy Virtual Buffer: %s -> %s\n" ) , sName.c_str() , pVBuf->sName.c_str() );
        }
        else
        {
            CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "Copied Virtual Buffer: %s -> %s\n" ) , sName.c_str() , pVBuf->sName.c_str() );
        }
    }
}

// Free the buffer.
N_VirtualMemory::VirtualBuffer::~VirtualBuffer()
{
    Free();
}

// If our buffer is valid.
bool N_VirtualMemory::VirtualBuffer::IsValid()
{
    return ( pAddress != nullptr )
        && ( HexSize > 0 )
        && ( Flags.m_hFlags.size() > 0 )
        && ( pProcess != nullptr )
        && bInitialized;
}

void N_VirtualMemory::VirtualBuffer::PrintBytes()
{
    if ( !IsValid() )
    {
        CONSOLEColorDEBUG( FOREGROUND_BLUE , TEXT( "[%s->PrintBytes] is not valid!\n" ) , sName.c_str() );
        return;
    }

    Pointer pTemp = Alloc( HexSize );

    if ( !VirtualReadMemory( pAddress , pTemp , HexSize , Flags , pProcess ) )
    {
        CONSOLEDEBUG( TEXT( "[%s->PrintBytes] Failed to read virtual memory: 0x%p\n" ) , sName.c_str() , pAddress );
        return;
    }

    N_Console::PrintBytes( ( Bytes ) pTemp , HexSize , sName.c_str() );

    FreeAlloc( pTemp );
}

bool N_VirtualMemory::VirtualBuffer::RefreshFlags()
{
    return VirtualModifyProtectionFlags( pAddress , pProcess , Flags );
}

// In case we want to read the virtual memory and allocate somewhere to the current process to modify like we want more easily.
Pointer N_VirtualMemory::VirtualBuffer::GetLocal()
{
    Pointer pTemp = Alloc( HexSize );

    if ( !VirtualReadMemory( pAddress , pTemp , HexSize , Flags , pProcess ) )
    {
        CONSOLEDEBUG( TEXT( "[%s->GetLocal] Failed to read virtual memory: 0x%p\n" ) , sName.c_str() , pAddress );
        return nullptr;
    }

    return pTemp;
}

// Copy buffer to another.
bool N_VirtualMemory::VirtualBuffer::Copy( VirtualBuffer* pVBuf )
{
    if ( !IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->%s->Copy] is not valid!\n" ) , sName.c_str() , pVBuf->sName.c_str() );
        return false;
    }

    if ( !pVBuf->IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->%s->Copy] is not valid!\n" ) , sName.c_str() , pVBuf->sName.c_str() );
        return false;
    }

    if ( CopyVirtualMemory_S( pAddress , HexSize , pVBuf->pAddress , pVBuf->HexSize , pProcess , pVBuf->pProcess
         , Flags
         , pVBuf->Flags
         , pAllocationAddress ) )
    {
        CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "[%s->%s->Copy] copied memory size: %i\n" ) , sName.c_str() , pVBuf->sName.c_str() , pVBuf->HexSize );
        return true;
    }

    CONSOLEDEBUG( TEXT( "[%s->%s->Copy] failed to copy memory size: %i\n" ) , sName.c_str() , pVBuf->sName.c_str() , pVBuf->HexSize );

    return false;
}

// Replace virtual memory from a process to another process.
bool N_VirtualMemory::VirtualBuffer::Replace( Pointer pAddressDestination , HEX SizeOfDestination , Pointer pProcessDestination
                                              , VirtualMemoryFlags& FlagsDestination
                                              , Pointer pFromAddress )
{
    if ( !IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->Replace] is not valid!\n" ) , sName.c_str() );
        return false;
    }

    bool bReturn = ReplaceVirtualMemory_S( pFromAddress , pAddress , pAddressDestination
                                           , HexSize , SizeOfDestination
                                           , pProcess , pProcessDestination
                                           , FlagsDestination
                                           , Flags
                                           , pAllocationAddress );

    if ( bReturn )
    {
        CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "[%s->Replace] added size: %i\n" ) , sName.c_str() , SizeOfDestination );
        return true;
    }

    CONSOLEDEBUG( TEXT( "[%s->Replace] couldn't add size: %i\n" ) , sName.c_str() , SizeOfDestination );

    return false;
}

// Same as above, but with a buffer.
bool N_VirtualMemory::VirtualBuffer::Replace( VirtualBuffer* pVBuf , Pointer pFromAddress )
{
    if ( !IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->%s->Replace] is not valid!\n" ) , sName.c_str() , pVBuf->sName.c_str() );
        return false;
    }

    if ( !pVBuf->IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->%s->Replace] is not valid!\n" ) , sName.c_str() , pVBuf->sName.c_str() );
        return false;
    }

    bool bReturn = ReplaceVirtualMemory_S( pFromAddress , pAddress , pVBuf->pAddress
                                           , HexSize , pVBuf->HexSize
                                           , pProcess , pVBuf->pProcess
                                           , Flags
                                           , pVBuf->Flags
                                           , pAllocationAddress );

    if ( bReturn )
    {
        CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "[%s->%s->Replace] added size: %i\n" ) , sName.c_str() , pVBuf->sName.c_str() , pVBuf->HexSize );
        return true;
    }

    CONSOLEDEBUG( TEXT( "[%s->%s->Replace] couldn't add size: %i\n" ) , sName.c_str() , pVBuf->sName.c_str() , pVBuf->HexSize );

    return false;
}

// Add virtual memory from a process to another process.
bool N_VirtualMemory::VirtualBuffer::Add( Pointer pAddressDestination , HEX SizeOfDestination , Pointer pProcessDestination
                                          , VirtualMemoryFlags& FlagsDestination
                                          , Pointer pFromAddress )
{
    if ( !IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->Add] is not valid!\n" ) , sName.c_str() );
        return false;
    }

    bool bReturn = AddVirtualMemory_S( pFromAddress , pAddress , pAddressDestination
                                       , HexSize , SizeOfDestination
                                       , pProcess , pProcessDestination
                                       , FlagsDestination
                                       , Flags
                                       , pAllocationAddress );

    if ( bReturn )
    {
        CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "[%s->Add] added size: %i\n" ) , sName.c_str() , SizeOfDestination );
        return true;
    }

    CONSOLEDEBUG( TEXT( "[%s->Add] couldn't add size: %i\n" ) , sName.c_str() , SizeOfDestination );

    return false;
}

// Same as above, but with a buffer.
bool N_VirtualMemory::VirtualBuffer::Add( VirtualBuffer* pVBuf , Pointer pFromAddress )
{
    if ( !IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->%s->Add] is not valid!\n" ) , sName.c_str() , pVBuf->sName.c_str() );
        return false;
    }

    if ( !pVBuf->IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->%s->Add] is not valid!\n" ) , sName.c_str() , pVBuf->sName.c_str() );
        return false;
    }

    bool bReturn = AddVirtualMemory_S( pFromAddress , pAddress , pVBuf->pAddress
                                       , HexSize , pVBuf->HexSize
                                       , pProcess , pVBuf->pProcess
                                       , Flags
                                       , pVBuf->Flags
                                       , pAllocationAddress );

    if ( bReturn )
    {
        CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "[%s->%s->Add] added size: %i\n" ) , sName.c_str() , pVBuf->sName.c_str() , pVBuf->HexSize );
        return true;
    }

    CONSOLEDEBUG( TEXT( "[%s->%s->Add] couldn't add size: %i\n" ) , sName.c_str() , pVBuf->sName.c_str() , pVBuf->HexSize );

    return false;
}

// Remove virtual memory from a buffer.
bool N_VirtualMemory::VirtualBuffer::Remove( VirtualBuffer* pVBuf )
{
    if ( !IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->%s->Remove] is not valid!\n" ) , sName.c_str() , pVBuf->sName.c_str() );
        return false;
    }

    if ( !pVBuf->IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->%s->Remove] is not valid!\n" ) , sName.c_str() , pVBuf->sName.c_str() );
        return false;
    }

    HEX HexReturn = Find( pVBuf );

    if ( HexReturn == -1 )
    {
        CONSOLEDEBUG( TEXT( "[%s->%s->Remove] couldn't find offset! (Bytes not found)\n" ) , sName.c_str() , pVBuf->sName.c_str() );
        return false;
    }

    bool bReturned = RemoveLocal( ( HEX ) HexReturn , pVBuf->HexSize );

    if ( bReturned )
    {
        CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "[%s->%s->Remove] removed size: %i\n" ) , sName.c_str() , pVBuf->sName.c_str() , pVBuf->HexSize );
        return true;
    }

    CONSOLEDEBUG( TEXT( "[%s->%s->Remove] couldn't remove size: %i\n" ) , sName.c_str() , pVBuf->sName.c_str() , pVBuf->HexSize );

    return false;
}

// Add bytes from a current process to the buffer.
bool N_VirtualMemory::VirtualBuffer::AddLocal( Pointer pAddressAdd , HEX pFromAddress , HEX HexSizeToAdd )
{
    if ( !IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->AddLocal] is not valid!\n" ) , sName.c_str() );
        return false;
    }

    bool bReturned = AddVirtualMemory_S( ( Pointer ) pFromAddress , pAddress , pAddressAdd
                                         , HexSize , HexSizeToAdd
                                         , pProcess , GetCurrentProcess()
                                         , Flags , FillVirtualMemoryFlags( HexSizeToAdd , PAGE_EXECUTE_READWRITE ) , pAllocationAddress );

    if ( bReturned )
    {
        CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "[%s->AddLocal] added size: %i\n" ) , sName.c_str() , HexSizeToAdd );
        return true;
    }

    CONSOLEDEBUG( TEXT( "[%s->AddLocal] added size: %i\n" ) , sName.c_str() , HexSizeToAdd );

    return false;
}

// Replaces bytes from a current process to the buffer.
bool N_VirtualMemory::VirtualBuffer::ReplaceLocal( Pointer pAddressAdd , HEX pFromAddress , HEX HexSizeToAdd )
{
    if ( !IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->ReplaceLocal] is not valid!\n" ) , sName.c_str() );
        return false;
    }

    bool bReturned = ReplaceVirtualMemory_S( ( Pointer ) pFromAddress , pAddress , pAddressAdd
                                             , HexSize , HexSizeToAdd
                                             , pProcess , GetCurrentProcess()
                                             , Flags , FillVirtualMemoryFlags( HexSizeToAdd , PAGE_EXECUTE_READWRITE ) , pAllocationAddress );

    if ( bReturned )
    {
        CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "[%s->ReplaceLocal] added size: %i\n" ) , sName.c_str() , HexSizeToAdd );
        return true;
    }

    CONSOLEDEBUG( TEXT( "[%s->ReplaceLocal] added size: %i\n" ) , sName.c_str() , HexSizeToAdd );

    return false;
}

// Remove bytes from a current process to the buffer.
bool N_VirtualMemory::VirtualBuffer::RemoveLocal( HEX pFromAddress , HEX HexSizeToRemove )
{
    if ( !IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->RemoveLocal] is not valid!\n" ) , sName.c_str() );
        return false;
    }

    bool bReturned = RemoveVirtualMemory_S( pAddress , HexSize , pFromAddress , HexSizeToRemove , Flags , pProcess , pAllocationAddress );

    if ( bReturned )
    {
        CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "[%s->RemoveLocal] removed size: %i\n" ) , sName.c_str() , HexSizeToRemove );
        return true;
    }

    CONSOLEDEBUG( TEXT( "[%s->RemoveLocal] couldn't remove size: %i\n" ) , sName.c_str() , HexSizeToRemove );

    return false;
}

// Write bytes from a current process to the buffer.
bool N_VirtualMemory::VirtualBuffer::WriteToProcessFromCurrent( Pointer pAddressLocalData , HEX HexSizeOfSource )
{
    bool bReturned = WriteVirtualMemoryFromCurrentProcess_S( pAddress , pAddressLocalData , HexSize , HexSizeOfSource , Flags , pProcess , pAllocationAddress );

    if ( bReturned )
    {
        CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "[%s->WriteToProcessFromCurrent] wrote memory re-sized: %i\n" )
                           , sName.c_str() , HexSizeOfSource );
        return true;
    }

    CONSOLEDEBUG( TEXT( "[%s->WriteToProcessFromCurrent] couldn't write memory (re-sized: %i) \n" )
                  , sName.c_str() , HexSizeOfSource );

    return false;
}

// Transfer buffer to another process.
bool N_VirtualMemory::VirtualBuffer::TransferToProcess( Pointer pChangedProcess )
{
    VirtualMemoryFlags TempFlags;
    TempFlags.m_hFlags = Flags.m_hFlags;

    Pointer pTempAddress = VirtualAllocation( HexSize , TempFlags );

    if ( !CopyVirtualMemory_S( pTempAddress , HexSize , pAddress , HexSize , GetCurrentProcess() , pProcess , TempFlags , Flags , pAllocationAddress ) )
    {
        CONSOLEDEBUG( TEXT( "[%s->TransferToProcess] couldn't write temp memory\n" ) , sName.c_str() );
        return false;
    }

    if ( !FreeVirtualAllocation( pAddress , pProcess ) )
    {
        CONSOLEDEBUG( TEXT( "[%s->TransferToProcess] couldn't free memory. 1\n" ) , sName.c_str() );
        return false;
    }

    pAddress = VirtualAllocation( HexSize , Flags , pChangedProcess , pAllocationAddress );

    if ( !WriteVirtualMemoryFromCurrentProcess_S( pAddress , pTempAddress , HexSize , HexSize , Flags , pChangedProcess , pAllocationAddress ) )
    {
        if ( !FreeVirtualAllocation( pTempAddress , pChangedProcess ) )
        {
            CONSOLEDEBUG( TEXT( "[%s->TransferToProcess] couldn't free memory. 2\n" ) , sName.c_str() );
            return false;
        }

        CONSOLEDEBUG( TEXT( "[%s->TransferToProcess] couldn't write memory\n" ) , sName.c_str() );

        return false;
    }

    if ( !FreeVirtualAllocation( pTempAddress ) )
    {
        CONSOLEDEBUG( TEXT( "[%s->TransferToProcess] couldn't free current memory. 2\n" ) , sName.c_str() );
        return false;
    }

    CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "[%s->TransferToProcess] wrote current memory from process: 0x%p to process  0x%p\n" ) , sName.c_str() , pProcess , pChangedProcess );

    pProcess = pChangedProcess;

    return true;
}

// Compare size to another buffer.
HEX N_VirtualMemory::VirtualBuffer::Compare( VirtualBuffer* pVBuf )
{
    if ( !IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->%s->Compare] is not valid!\n" ) , sName.c_str() , pVBuf->sName.c_str() );
        return 0;
    }

    if ( !pVBuf->IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->%s->Compare]is not valid!\n" ) , sName.c_str() , pVBuf->sName.c_str() );
        return 0;
    }

    bool bFailed;
    HEX HEXRet = CompareVirtualMemory_S( pVBuf->pAddress , pVBuf->HexSize , pAddress , HexSize
                                         , pVBuf->Flags , Flags , pVBuf->pProcess , pProcess , &bFailed );

    if ( bFailed )
    {
        CONSOLEDEBUG( TEXT( "[%s->%s->Compare] has failed to compare!\n" ) , sName.c_str() , pVBuf->sName.c_str() );
    }
    else
    {
        CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "[%s->%s->Compare] difference: %i\n" ) , sName.c_str() , pVBuf->sName.c_str() , HEXRet );
    }

    return HEXRet;
}

// Find the offset into the buffer.
HEX N_VirtualMemory::VirtualBuffer::Find( VirtualBuffer*pVBuf )
{
    if ( !IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->%s->Find] is not valid!\n" ) , sName.c_str() , pVBuf->sName.c_str() );
        return 0;
    }

    if ( !pVBuf->IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->%s->Find] is not valid!\n" ) , sName.c_str() , pVBuf->sName.c_str() );
        return 0;
    }

    bool bFailed = false;
    HEX HexReturned = FindOffsetVirtualMemory_s( pAddress , HexSize
                                                 , pVBuf->pAddress
                                                 , pVBuf->HexSize , pVBuf->Flags , Flags , pProcess , pVBuf->pProcess , &bFailed );

    if ( !bFailed )
    {
        CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "[%s->%s->Find] offset: %i\n" ) , sName.c_str() , pVBuf->sName.c_str() , HexReturned );
        return HexReturned;
    }

    CONSOLEDEBUG( TEXT( "[%s->%s->Find] couldn't find offset!\n" ) , sName.c_str() , pVBuf->sName.c_str() );

    return 0;
}

// Find the offset with bytes or local data (current process).
HEX N_VirtualMemory::VirtualBuffer::FindLocal( Pointer pAddressSource , HEX HexSizeOfSource )
{
    if ( !IsValid() )
    {
        CONSOLEDEBUG( TEXT( "[%s->FindLocal] is not valid!\n" ) , sName.c_str() );
        return 0;
    }

    bool bFailed = false;
    HEX HexReturned = FindOffsetVirtualMemory_s( pAddress , HexSize , pAddressSource , HexSizeOfSource , FillVirtualMemoryFlags( HexSizeOfSource , PAGE_EXECUTE_READWRITE )
                                                 , Flags , pProcess , GetCurrentProcess() , &bFailed );
    if ( !bFailed )
    {
        CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "[%s->FindLocal] offset: %i\n" ) , sName.c_str() , HexReturned );
        return HexReturned;
    }

    CONSOLEDEBUG( TEXT( "[%s->FindLocal] couldn't find offset!\n" ) , sName.c_str() );
    return 0;
}

void N_VirtualMemory::VirtualBuffer::Free()
{
    if ( pAddress != nullptr &&  pProcess != nullptr )
    {
        FreeVirtualAllocation( pAddress , pProcess );
        CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "[%s->Uninitialized]\n" ) , sName.c_str() );
    }

    HexSize = 0;
    pProcess = 0;
    Flags.Reset();
    pAllocationAddress = 0;
    sName.clear();
}

bool N_VirtualMemory::VirtualBuffer::operator>( VirtualBuffer *pVBuf )
{
    return ( Compare( pVBuf ) > 0 );
}

bool N_VirtualMemory::VirtualBuffer::operator<( VirtualBuffer *pVBuf )
{
    return ( Compare( pVBuf ) < 0 );
}

bool N_VirtualMemory::VirtualBuffer::operator==( VirtualBuffer *pVBuf )
{
    return ( Compare( pVBuf ) == 0 );
}

bool N_VirtualMemory::VirtualBuffer::operator>=( VirtualBuffer *pVBuf )
{
    return ( Compare( pVBuf ) >= 0 );
}

bool N_VirtualMemory::VirtualBuffer::operator<=( VirtualBuffer *pVBuf )
{
    return ( Compare( pVBuf ) <= 0 );
}

bool N_VirtualMemory::VirtualBuffer::operator!=( VirtualBuffer *pVBuf )
{
    return ( Compare( pVBuf ) != 0 );
}

bool N_VirtualMemory::VirtualBuffer::operator>( HEX _HexSize )
{
    return ( HexSize > _HexSize );
}

bool N_VirtualMemory::VirtualBuffer::operator<( HEX _HexSize )
{
    return ( HexSize < _HexSize );
}

bool N_VirtualMemory::VirtualBuffer::operator==( HEX _HexSize )
{
    return ( HexSize == _HexSize );
}

HEX N_VirtualMemory::VirtualBuffer::operator==( std::vector<Byte> Value )
{
    return FindLocal( ( Pointer ) Value.data() , Value.size() * sizeof( Byte ) );
}

HEX N_VirtualMemory::VirtualBuffer::operator==( stdString Value )
{
    return FindLocal( ( Pointer ) Value.data() , Value.size() * sizeof( String ) );
}

bool N_VirtualMemory::VirtualBuffer::operator<=( HEX _HexSize )
{
    return ( HexSize <= _HexSize );
}

bool N_VirtualMemory::VirtualBuffer::operator>=( HEX _HexSize )
{
    return ( HexSize >= _HexSize );
}

bool N_VirtualMemory::VirtualBuffer::operator!=( HEX _HexSize )
{
    return ( HexSize != _HexSize );
}

bool N_VirtualMemory::VirtualBuffer::operator=( VirtualBuffer *pVBuf )
{
    return Copy( pVBuf );
}

bool N_VirtualMemory::VirtualBuffer::operator+=( VirtualBuffer *pVBuf )
{
    return Add( pVBuf , ( Pointer ) HexSize );
}

bool N_VirtualMemory::VirtualBuffer::operator-=( VirtualBuffer *pVBuf )
{
    return Remove( pVBuf );
}

bool N_VirtualMemory::VirtualBuffer::operator+=( std::vector<Byte> Value )
{
    return AddLocal( Value.data() , HexSize , Value.size() * sizeof( Byte ) );
}

bool N_VirtualMemory::VirtualBuffer::operator+=( stdString Value )
{
    return AddLocal( ( Pointer ) Value.data() , HexSize , Value.size() * sizeof( String ) );
}

bool N_VirtualMemory::VirtualBuffer::operator-=( std::vector<Byte> Value )
{
    HEX Offset = FindLocal( ( Pointer ) Value.data() , Value.size() * sizeof( Byte ) );

    if ( Offset != -1 )
    {
        return RemoveLocal( Offset , Value.size() * sizeof( Byte ) );
    }
    else
    {
        CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "[%s->operator-=] Couldn't find offset\n" ) , sName.c_str() );
    }

    return false;
}

bool N_VirtualMemory::VirtualBuffer::operator-=( stdString Value )
{
    HEX Offset = FindLocal( ( Pointer ) Value.data() , Value.size() * sizeof( String ) );

    if ( Offset != -1 )
    {
        return RemoveLocal( Offset , Value.size() * sizeof( String ) );
    }
    else
    {
        CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "[%s->operator-=] Couldn't find offset\n" ) , sName.c_str() );
    }

    return false;
}

bool N_VirtualMemory::VirtualBuffer::operator-=( HEX _HexSize )
{
    return RemoveLocal( HexSize , _HexSize );
}

bool N_VirtualMemory::VirtualBuffer::operator=( std::vector<Byte> Value )
{
    bool bRet = false;

    if ( HexSlot != -1 )
    {
        bRet = ReplaceLocal( ( Pointer ) Value.data() , HexSlot , Value.size() * sizeof( Byte ) );
        HexSlot = -1;
    }

    return bRet;
}

bool N_VirtualMemory::VirtualBuffer::operator=( Byte Value )
{
    bool bRet = false;

    if ( HexSlot != -1 )
    {
        bRet = ReplaceLocal( ( Pointer ) Value , HexSlot , 1 );
        HexSlot = -1;
    }

    return bRet;
}

bool N_VirtualMemory::VirtualBuffer::operator=( stdString Value )
{
    bool bRet = false;

    if ( HexSlot != -1 )
    {
        bRet = ReplaceLocal( ( Pointer ) Value.data() , HexSlot , Value.size() * sizeof( String ) );
        HexSlot = -1;
    }

    return bRet;
}

bool N_VirtualMemory::VirtualBuffer::UnProtect()
{
    return VirtualModifyProtectionFlags( pAddress , pProcess , FillVirtualMemoryFlags( HexSize , PAGE_EXECUTE_READWRITE ) );
}

N_VirtualMemory::VirtualBuffer &N_VirtualMemory::VirtualBuffer::operator[]( HEX HexValue )
{
    HexSlot = HexValue;
    return *this;
}

Pointer N_VirtualMemory::VirtualBuffer::operator[]( HEX HexValue ) const
{
    return ( Pointer ) ( ( HEX ) pAddress + HexValue );
}