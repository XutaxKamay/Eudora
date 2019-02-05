#include "Includes.hxx"
#include "Main.hxx"

__pragma( warning( push ) )
__pragma( warning( disable:4100 ) )

CUserCmd* __fastcall new_GetUserCmd( _FASTCALLD , int iSlot , int sequence_number )
{
    CInput *_Input = ( CInput* ) ThisPTR;
    return &_Input->m_pCommands[ sequence_number % MULTIPLAYER_BACKUP ];
}

__pragma( warning( pop ) )