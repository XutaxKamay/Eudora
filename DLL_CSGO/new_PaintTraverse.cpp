#include "Includes.hxx"
#include "Main.hxx"

__pragma( warning( push ) )
__pragma( warning( disable:4100 ) )

void __fastcall new_PaintTraverse( _FASTCALLD , unsigned int iPanel , bool bForceRePaint , bool bAllowForce )
{
    _CallFunction<void , e_thiscall , Pointer , unsigned int , bool , bool>( DetouredFunctions[ D_PaintTraverse ]->pOld , ThisPTR , iPanel , bForceRePaint , bAllowForce );

    if ( EngineClient->IsTakingScreenshot() )
        return;
}

__pragma( warning( pop ) )