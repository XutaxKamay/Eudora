#include "Includes.hxx"
#include "Main.hxx"

template<typename T>
T *KVStringAlloc( size_t nLength )
{
    return reinterpret_cast< T* >( MemAllocValve->Alloc( sizeof( T ) * nLength ) );
}

void KVStringDelete( void* pMem )
{
    MemAllocValve->Free( pMem );
}

KeyValues::KeyValues( const char* sName )
{
    Offsets->KeyValues_Constructor( this , sName );
}

Pointer KeyValues::operator new( size_t Size )
{
    return KeyValuesSystem->AllocKeyValuesMemory( Size );
}

void KeyValues::operator delete( Pointer pAddress )
{
    KeyValuesSystem->FreeKeyValuesMemory( pAddress );
}

void KeyValues::SetInt( const char *keyName , int value )
{
    KeyValues *dat = FindKey( keyName , true );

    if ( dat )
    {
        dat->m_iValue = value;
        dat->m_iDataType = TYPE_INT;
    }
}

//-----------------------------------------------------------------------------
// Purpose: Set the string value of a keyName.
//-----------------------------------------------------------------------------
void KeyValues::SetString( const char *keyName , const char *value )
{
    KeyValues *dat = FindKey( keyName , true );

    if ( dat )
    {
        Offsets->KeyValues_SetString( dat , value );
    }
}

KeyValues *KeyValues::FindKey( const char *keyName , bool bCreate )
{
    return Offsets->KeyValues_FindKey( this , keyName , bCreate );
}

void KeyValues::LoadFromBuffer( const char * resourceName , const char * pBuffer
                                , Pointer pFileSystem , const char * pPathID , Pointer pfnEvaluateSymbolProc )
{
    Offsets->KeyValues_LoadFromBuffer( this , resourceName , pBuffer , pFileSystem , pPathID , pfnEvaluateSymbolProc );
}