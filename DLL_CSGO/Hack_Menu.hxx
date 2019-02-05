#ifndef HACK_MENU
#define HACK_MENU
#pragma once

class CGUI
{
public:

    CGUI()
    {
        Font_Debug = 0;
    }

    void CreateFonts();
    void DeleteFonts();

    template<int r = 255 , int g = 255 , int b = 255 , int a = 255 , bool bShouldLog = false> void PrintDebug( int x , int y , const wchar_t* cString , ... )
    {
        va_list list;
        va_start( list , cString );
        wchar_t sBuffer[ UNICODE_STRING_MAX_CHARS ];
        vswprintf_s( sBuffer , UNICODE_STRING_MAX_CHARS , cString , list );
        va_end( list );

        if ( bShouldLog )
        {
            sDebugAllStrings += sBuffer;
        }

        Surface->DrawSetTextFont( Font_Debug );
        Surface->DrawSetTextColor( Color( r , g , b , a ) );
        Surface->DrawSetTextPos( x , y );
        Surface->DrawPrintText( sBuffer , lstrlenW( sBuffer ) + 1 , FONT_DRAW_NONADDITIVE );
    }

    HFont Font_Debug;
    std::wstring sDebugAllStrings;
};

extern CGUI *Gui;

#endif