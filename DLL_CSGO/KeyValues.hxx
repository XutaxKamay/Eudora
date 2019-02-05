//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//

#ifndef KEYVALUES_H
#define KEYVALUES_H
#pragma once

// #include <vgui/VGUI.h>

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#define FOR_EACH_SUBKEY( kvRoot, kvSubKey ) \
	for ( KeyValues * kvSubKey = kvRoot->GetFirstSubKey(); kvSubKey != NULL; kvSubKey = kvSubKey->GetNextKey() )

#define FOR_EACH_TRUE_SUBKEY( kvRoot, kvSubKey ) \
	for ( KeyValues * kvSubKey = kvRoot->GetFirstTrueSubKey(); kvSubKey != NULL; kvSubKey = kvSubKey->GetNextTrueSubKey() )

#define FOR_EACH_VALUE( kvRoot, kvValue ) \
	for ( KeyValues * kvValue = kvRoot->GetFirstValue(); kvValue != NULL; kvValue = kvValue->GetNextValue() )

class IBaseFileSystem;
class CUtlBuffer;
class Color;
typedef void * FileHandle_t;
class CKeyValuesGrowableStringTable;

// handle to a KeyValues key name symbol
typedef int HKeySymbol;
#define INVALID_KEY_SYMBOL (-1)

class IBaseFileSystem;

//-----------------------------------------------------------------------------
// Purpose: Interface to shared data repository for KeyValues (included in vgui_controls.lib)
//			allows for central data storage point of KeyValues symbol table
//-----------------------------------------------------------------------------
class IKeyValuesSystem
{
public:
    // registers the size of the KeyValues in the specified instance
    // so it can build a properly sized memory pool for the KeyValues objects
    // the sizes will usually never differ but this is for versioning safety
    virtual void RegisterSizeofKeyValues( int size ) = 0;

    // allocates/frees a KeyValues object from the shared mempool
    virtual void *AllocKeyValuesMemory( int size ) = 0;
    virtual void FreeKeyValuesMemory( void *pMem ) = 0;

    // symbol table access (used for key names)
    virtual HKeySymbol GetSymbolForString( const char *name , bool bCreate = true ) = 0;
    virtual const char *GetStringForSymbol( HKeySymbol symbol ) = 0;

    // for debugging, adds KeyValues record into global list so we can track memory leaks
    virtual void AddKeyValuesToMemoryLeakList( void *pMem , HKeySymbol name ) = 0;
    virtual void RemoveKeyValuesFromMemoryLeakList( void *pMem ) = 0;

    // maintain a cache of KeyValues we load from disk. This saves us quite a lot of time on app startup.
    virtual void AddFileKeyValuesToCache( const KeyValues* _kv , const char *resourceName , const char *pathID ) = 0;
    virtual bool LoadFileKeyValuesFromCache( KeyValues* _outKv , const char *resourceName , const char *pathID , IBaseFileSystem *filesystem ) const = 0;
    virtual void InvalidateCache() = 0;
    virtual void InvalidateCacheForFile( const char *resourceName , const char *pathID ) = 0;
};

//-----------------------------------------------------------------------------
// Purpose: Simple recursive data access class
//			Used in vgui for message parameters and resource files
//			Destructor deletes all child KeyValues nodes
//			Data is stored in key (string names) - (string/int/float)value pairs called nodes.
//
//	About KeyValues Text File Format:

//	It has 3 control characters '{', '}' and '"'. Names and values may be quoted or
//	not. The quote '"' character must not be used within name or values, only for
//	quoting whole tokens. You may use escape sequences wile parsing and add within a
//	quoted token a \" to add quotes within your name or token. When using Escape
//	Sequence the parser must now that by setting KeyValues::UsesEscapeSequences( true ),
//	which it's off by default. Non-quoted tokens ends with a whitespace, '{', '}' and '"'.
//	So you may use '{' and '}' within quoted tokens, but not for non-quoted tokens.
//  An open bracket '{' after a key name indicates a list of subkeys which is finished
//  with a closing bracket '}'. Subkeys use the same definitions recursively.
//  Whitespaces are space, return, newline and tabulator. Allowed Escape sequences
//	are \n, \t, \\, \n and \". The number character '#' is used for macro purposes
//	(eg #include), don't use it as first character in key names.
//-----------------------------------------------------------------------------
class KeyValues
{
public:

    KeyValues( const char* sName );
    Pointer operator new( size_t );
    void operator delete( Pointer );

    //	By default, the KeyValues class uses a string table for the key names that is
    //	limited to 4MB. The game will exit in error if this space is exhausted. In
    //	general this is preferable for game code for performance and memory fragmentation
    //	reasons.
    //
    //	If this is not acceptable, you can use this call to switch to a table that can grow
    //	arbitrarily. This call must be made before any KeyValues objects are allocated or it
    //	will result in undefined behavior. If you use the growable string table, you cannot
    //	share KeyValues pointers directly with any other module. You can serialize them across
    //	module boundaries. These limitations are acceptable in the Steam backend code
    //	this option was written for, but may not be in other situations. Make sure to
    //	understand the implications before using this.

    // gets the name as a unique int
    int GetNameSymbol() const
    {
        return m_iKeyName;
    }

    // Find a keyValue, create it if it is not found.
    // Set bCreate to true to create the key if it doesn't already exist (which ensures a valid pointer will be returned)
    KeyValues *FindKey( const char *keyName , bool bCreate = false );
                                            //
                                            // NOTE: GetFirstSubKey/GetNextKey will iterate keys AND values. Use the functions
                                            // below if you want to iterate over just the keys or just the values.
                                            //
    KeyValues *GetFirstSubKey()
    {
        return m_pSub;
    }	// returns the first subkey in the list
    KeyValues *GetNextKey()
    {
        return m_pPeer;
    }		// returns the next subkey
    const KeyValues *GetNextKey() const
    {
        return m_pPeer;
    }		// returns the next subkey

    // Key writing
    void SetString( const char *keyName , const char *value );
    void SetInt( const char *keyName , int value );
    void SetBool( const char *keyName , bool value )
    {
        SetInt( keyName , value ? 1 : 0 );
    }

    void LoadFromBuffer( const char * resourceName , const char * pBuffer
                         , Pointer pFileSystem = nullptr , const char * pPathID = nullptr , Pointer pfnEvaluateSymbolProc = nullptr );

    // Data type
    enum types_t
    {
        TYPE_NONE = 0 ,
        TYPE_STRING ,
        TYPE_INT ,
        TYPE_FLOAT ,
        TYPE_PTR ,
        TYPE_WSTRING ,
        TYPE_COLOR ,
        TYPE_UINT64 ,
        TYPE_NUMTYPES ,
    };

    int m_iKeyName;	// keyname is a symbol defined in KeyValuesSystem

                    // These are needed out of the union because the API returns string pointers
    char *m_sValue;
    wchar_t *m_wsValue;

    // we don't delete these
    union
    {
        int m_iValue;
        float m_flValue;
        void *m_pValue;
        unsigned char m_Color[ 4 ];
    };

    char	   m_iDataType;
    char	   m_bHasEscapeSequences; // true, if while parsing this KeyValue, Escape Sequences are used (default false)
    char	   m_bEvaluateConditionals; // true, if while parsing this KeyValue, conditionals blocks are evaluated (default true)
    char	   unused[ 1 ];

    KeyValues *m_pPeer;	// pointer to next key in list
    KeyValues *m_pSub;	// pointer to Start of a new sub key list
    KeyValues *m_pChain;// Search here if it's not in our list
    Pointer pSomething;
};

#endif // KEYVALUES_H