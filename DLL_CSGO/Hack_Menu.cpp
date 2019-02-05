#include "Includes.hxx"
#include "Main.hxx"

CGUI *Gui = new CGUI();

void CGUI::CreateFonts()
{
    Font_Debug = Surface->CreateFont();
    Surface->SetFontGlyphSet( Font_Debug , "Malgun Gothic Semilight" , 12 , 650 , 1 , 0 , FONTFLAG_OUTLINE | FONTFLAG_GAUSSIANBLUR | FONTFLAG_DROPSHADOW | FONTFLAG_ITALIC );
}

void CGUI::DeleteFonts()
{
    Font_Debug = 0;
}