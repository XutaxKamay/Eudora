#ifndef LIB_CONSOLE
#define LIB_CONSOLE
#pragma once

__pragma( warning( push ) )
__pragma( warning( disable:4127 ) )

#ifdef NDEBUG
#define NODEBUGSTRINGS
#endif

namespace N_Console
{
    EXTERN bool bClearOnceLogFile;

    // Let's put all strings into a vector (buffer)
    EXTERN stdString sAllStrings;

    // If console is openned
    EXTERN bool bOpenned;
    EXTERN bool bClearedLogs;

    void Open();

    void Close();

    // Set attributes manually
    void SetAttributes( WORD wAttributes );

    void NewLine();

    void Space();

    void Star();

    void PrintBytes( Bytes bytes , HEX HexSize , const stdString &swName = TEXT( "TmpBuffer" ) );

    void PrintBytesDebug( Bytes bytes , HEX HexSize , const stdString &swName = TEXT( "TmpBuffer" ) );

    //Print white text in case that we're using something else that Print function

    void ResetAttributes();

    template<WORD wAttributes = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY> void Pause()
    {
        SetAttributes( wAttributes );
        system( "pause" );
    }
            // Print to Console
    template<WORD wAttributes = 0x0 , bool bShouldSaveString = true> void Print( const String* sMessage , ... )
    {
        va_list list;
        va_start( list , sMessage );
        String sBuffer[ UNICODE_STRING_MAX_CHARS ];
        SPrintf_S( sBuffer , UNICODE_STRING_MAX_CHARS , sMessage , list );
        va_end( list );

        if ( bShouldSaveString )
            sAllStrings += sBuffer;

        if ( bOpenned )
        {
            if ( wAttributes != 0 )
                SetAttributes( wAttributes | FOREGROUND_INTENSITY );
            WriteConsole( GetStdHandle( STD_OUTPUT_HANDLE ) , sBuffer , ( DWORD ) StrLen( sBuffer ) , 0 , 0 );
        }
    }

    template<WORD wAttributes = FOREGROUND_RED , bool bShouldSaveString = true> void PrintDebug( const String* sMessage , ... )
    {
        String ModulePath[ MAX_PATH ];
        GetModuleFileName( 0 , ModulePath , MAX_PATH );
        ModulePath[ StrLen( ModulePath ) - 3 ] = 0;
        StrCat_S( ModulePath , MAX_PATH , TEXT( "log" ) );

        if ( !bClearOnceLogFile )
        {
            N_FileSystem::ClearFile( ModulePath ); bClearOnceLogFile = true;
        }

        va_list list;
        va_start( list , sMessage );
        String sBuffer[ UNICODE_STRING_MAX_CHARS ];
        SPrintf_S( sBuffer , UNICODE_STRING_MAX_CHARS , sMessage , list );
        va_end( list );

        if ( bShouldSaveString )
            sAllStrings += sBuffer;

        if ( bOpenned )
        {
            if ( wAttributes != 0 )
                SetAttributes( wAttributes | FOREGROUND_INTENSITY );
            WriteConsole( GetStdHandle( STD_OUTPUT_HANDLE ) , sBuffer , ( DWORD ) StrLen( sBuffer ) , 0 , 0 );
        }

        N_FileSystem::WriteFile( ModulePath , sBuffer );
    }

    void WriteLog();

    /* https://github.com/google-code-export/znc-msvc/blob/master/main/znc-msvc/win32/src/znc_msvc.cpp */

    template<WORD wAttributes = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY> stdString Input( const stdString prompt = TEXT( "Enter something\n" ) , bool bHide = false )
    {
        SetAttributes( wAttributes );

        // Get input handle of the console

        HANDLE in = GetStdHandle( STD_INPUT_HANDLE );

        // Get output handle of the console

        HANDLE out = GetStdHandle( STD_OUTPUT_HANDLE );

        stdString result;
        DWORD count;

        if ( in == INVALID_HANDLE_VALUE || out == INVALID_HANDLE_VALUE )
        {
            return NULL;
        }

        // Let's write into the console the given input string

        if ( WriteConsole( out , prompt.c_str() , ( DWORD ) prompt.length() , &count , NULL ) )
        {
            int istty = ( GetFileType( in ) == FILE_TYPE_CHAR );

            DWORD old_mode = 0;
            String c;

            if ( istty )
            {
                //Set console mode to input instead of output

                if ( GetConsoleMode( in , &old_mode ) )
                {
                    SetConsoleMode( in , old_mode & ~( ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT ) );
                }
                else
                {
                    istty = 0;
                }
            }

            // Read the keys until enter is pressed

            while ( ReadConsole( in , &c , 1 , &count , NULL ) && ( c != '\r' ) && ( c != '\n' ) )
            {
                // If backspace is pressed, we remove the last character

                if ( c == '\b' )
                {
                    if ( !result.empty() )
                    {
                        WriteConsole( out , TEXT( "\b \b" ) , 3 , &count , NULL );
                        result.erase( result.end() - 1 );
                    }
                }
                else
                {
                    // If we must hide the words written by the user (password for ex) we write * instead of the words typed.

                    if ( !bHide )
                        WriteConsole( out , &c , 1 , &count , NULL );
                    else
                        WriteConsole( out , TEXT( "*" ) , 1 , &count , NULL );

                    // Push back calls from the input (keyboard).

                    result += c;
                }
            }

            NewLine();

            //Push back the previous console mode.
            if ( istty )
            {
                SetConsoleMode( in , old_mode );
            }
        }

        return result;
    }
};

__pragma( warning( pop ) )

#ifndef NODEBUGSTRINGS
#define CONSOLEDEBUGBYTES(Data,Size,Name) N_Console::PrintBytesDebug((Bytes)Data,Size,Name)
#define CONSOLEDEBUG(Text,...) N_Console::PrintDebug(Text,__VA_ARGS__ )
#define CONSOLEColorDEBUG(Color2_,Text,...) N_Console::PrintDebug<Color2_>(Text,__VA_ARGS__ )
#else
#define CONSOLEDEBUGBYTES(Data,Bytes,Name) (void)0
#define CONSOLEDEBUG(Text,...) (void)0
#define CONSOLEColorDEBUG(Color2_,Text,...) (void)0
#endif

#endif