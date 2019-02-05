#ifndef UTLSYMBOL
#define UTLSYMBOL
#pragma once

//-----------------------------------------------------------------------------
// forward declarations
//-----------------------------------------------------------------------------
class CUtlSymbolTable;
class CUtlSymbolTableMT;

//-----------------------------------------------------------------------------
// This is a symbol, which is a easier way of dealing with strings.
//-----------------------------------------------------------------------------
typedef unsigned short UtlSymId_t;

#define UTL_INVAL_SYMBOL  ((UtlSymId_t)~0)

class CUtlSymbol
{
public:
    // constructor, destructor
    CUtlSymbol() : m_Id( UTL_INVAL_SYMBOL )
    {}
    CUtlSymbol( UtlSymId_t id ) : m_Id( id )
    {}
    CUtlSymbol( const char* pStr );
    CUtlSymbol( CUtlSymbol const& sym ) : m_Id( sym.m_Id )
    {}

    // operator=
    CUtlSymbol& operator=( CUtlSymbol const& src )
    {
        m_Id = src.m_Id; return *this;
    }

    // operator==
    bool operator==( CUtlSymbol const& src ) const
    {
        return m_Id == src.m_Id;
    }
    bool operator==( const char* pStr ) const;

    // Is valid?
    bool IsValid() const
    {
        return m_Id != UTL_INVAL_SYMBOL;
    }

    // Gets at the symbol
    operator UtlSymId_t const( ) const
    {
        return m_Id;
    }

    // Gets the string associated with the symbol
    const char* String() const;

    // Modules can choose to disable the static symbol table so to prevent accidental use of them.
    static void DisableStaticSymbolTable();

protected:
    UtlSymId_t   m_Id;

    // Initializes the symbol table
    static void Initialize();

    // returns the current symbol table
    static CUtlSymbolTableMT* CurrTable();

    // The standard global symbol table
    static CUtlSymbolTableMT* s_pSymbolTable;

    static bool s_bAllowStaticSymbolTable;

    friend class CCleanupUtlSymbolTable;
};

#endif