#include "Includes.hxx"
#include "Main.hxx"

template<typename T = IMemAlloc * > T GetMemAlloc()
{
    static Pointer pMemAlloc = *( pPointer ) GetProcAddress( _GetModule<HMODULE>( TEXT( "tier0.dll" ) ) , "g_pMemAlloc" );

    return ( T ) pMemAlloc;
}

Interface<IMemAlloc> MemAllocValve = Interface<IMemAlloc>( GetMemAlloc<Pointer>() , AutoConvertC( TEXT( "GetMemAlloc()" ) ) , TEXT( "tier0.dll" ) );

static void *AllocUnattributed( size_t nSize )
{
    return GetMemAlloc()->Alloc( nSize );
}

void *__cdecl operator new( size_t nSize )
{
    return AllocUnattributed( nSize );
}

void *__cdecl operator new( size_t nSize , int nBlockUse , const char *pFileName , int nLine )
{
    return GetMemAlloc()->Alloc( nSize , pFileName , nLine );
}

void __cdecl operator delete( void *pMem )
{
    GetMemAlloc()->Free( pMem );
}

void *__cdecl operator new[] ( size_t nSize )
{
    return AllocUnattributed( nSize );
}

void *__cdecl operator new[] ( size_t nSize , int nBlockUse , const char *pFileName , int nLine )
{
    return GetMemAlloc()->Alloc( nSize , pFileName , nLine );
}

void __cdecl operator delete[] ( void *pMem )
{
    GetMemAlloc()->Free( pMem );
}