#include "Includes.hxx"
#include "Lib.hxx"

// Let's put all strings into a vector (buffer)
//stdString N_Console::sAllStrings;

// If console is openned
//bool N_Console::bOpenned;
//bool N_Console::bClearedLogs;

void N_Console::Open()
{
    // If the console is openned correctly we set our variable
    if ( AllocConsole() )
    {
        bOpenned = true;
    }
}

void N_Console::Close()
{
    // If the console didn't close correctly don't do anything.
    if ( FreeConsole() )
    {
        bOpenned = false;
    }
}

// Set attributes manually
void N_Console::SetAttributes( WORD wAttributes )
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , wAttributes );
}

//Print white text in case that we're using something else that Print function

void N_Console::ResetAttributes()
{
    SetAttributes( FOREGROUND_WHITE | FOREGROUND_INTENSITY );
}

void N_Console::NewLine()
{
    WriteConsole( GetStdHandle( STD_OUTPUT_HANDLE ) , TEXT( "\n" ) , 1 , NULL , NULL );
}

void N_Console::Space()
{
    WriteConsole( GetStdHandle( STD_OUTPUT_HANDLE ) , TEXT( " " ) , 1 , NULL , NULL );
}

void N_Console::Star()
{
    WriteConsole( GetStdHandle( STD_OUTPUT_HANDLE ) , TEXT( "*" ) , 1 , NULL , NULL );
}

void N_Console::PrintBytes( Bytes bytes , HEX HexSize , const stdString &swName )
{
    Print<FOREGROUND_YELLOW>( TEXT( "Byte %s[] = { " ) , swName.c_str() );

    for ( HEX i = 0; i < HexSize; i++ )
    {
        if ( i == HexSize - 1 )
            Print<FOREGROUND_ROSE>( TEXT( "0x%02X" ) , bytes[ i ] );
        else
            Print<FOREGROUND_ROSE>( TEXT( "0x%02X , " ) , bytes[ i ] );
    }

    Print<FOREGROUND_GREEN>( TEXT( " };" ) );

    /*Print<FOREGROUND_GREEN>( TEXT( " };\nString: " ) );

    for ( HEX i = 0; i < HexSize; i++ )
    {
        Print<FOREGROUND_CYAN>( TEXT( "%c" ) , bytes[ i ] );
    }*/

    NewLine();
}

void N_Console::PrintBytesDebug( Bytes bytes , HEX HexSize , const stdString &swName )
{
    if ( HexSize > 0xFF )
    {
        PrintDebug( TEXT( "%s was too long to print.\n" ) , swName.c_str() );
        return;
    }

    PrintDebug<FOREGROUND_YELLOW>( TEXT( "Byte %s[] = { " ) , swName.c_str() );

    for ( HEX i = 0; i < HexSize; i++ )
    {
        if ( i == HexSize - 1 )
            PrintDebug<FOREGROUND_ROSE>( TEXT( "0x%02X" ) , bytes[ i ] );
        else
            PrintDebug<FOREGROUND_ROSE>( TEXT( "0x%02X , " ) , bytes[ i ] );
    }

    PrintDebug<FOREGROUND_GREEN>( TEXT( " };\n" ) );
}

void N_Console::WriteLog()
{
    String ModulePath[ MAX_PATH ];
    GetModuleFileName( 0 , ModulePath , MAX_PATH );
    ModulePath[ StrLen( ModulePath ) - 3 ] = 0;
    StrCat_S( ModulePath , MAX_PATH , TEXT( "log" ) );

    if ( !bClearedLogs )
    {
        N_FileSystem::ClearFile( ModulePath );
        bClearedLogs = true;
    }

    N_FileSystem::WriteFile( ModulePath , sAllStrings.c_str() );
}