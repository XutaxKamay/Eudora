#include "Includes.hxx"
#include "Main.hxx"

void WriteUsercmd( bf_write *buf , CUserCmd *to , CUserCmd *from )
{
    if ( to->command_number != ( from->command_number + 1 ) )
    {
        buf->WriteOneBit( 1 );
        buf->WriteUBitLong( to->command_number , 32 );
    }
    else
    {
        buf->WriteOneBit( 0 );
    }

    if ( to->tick_count != ( from->tick_count + 1 ) )
    {
        buf->WriteOneBit( 1 );
        buf->WriteUBitLong( to->tick_count , 32 );
    }
    else
    {
        buf->WriteOneBit( 0 );
    }

    if ( to->viewangles[ 0 ] != from->viewangles[ 0 ] )
    {
        buf->WriteOneBit( 1 );
        buf->WriteFloat( to->viewangles[ 0 ] );
    }
    else
    {
        buf->WriteOneBit( 0 );
    }

    if ( to->viewangles[ 1 ] != from->viewangles[ 1 ] )
    {
        buf->WriteOneBit( 1 );
        buf->WriteFloat( to->viewangles[ 1 ] );
    }
    else
    {
        buf->WriteOneBit( 0 );
    }

    if ( to->viewangles[ 2 ] != from->viewangles[ 2 ] )
    {
        buf->WriteOneBit( 1 );
        buf->WriteFloat( to->viewangles[ 2 ] );
    }
    else
    {
        buf->WriteOneBit( 0 );
    }

    if ( to->aimdirection[ 0 ] != from->aimdirection[ 0 ] )
    {
        buf->WriteOneBit( 1 );
        buf->WriteFloat( to->aimdirection[ 0 ] );
    }
    else
    {
        buf->WriteOneBit( 0 );
    }

    if ( to->aimdirection[ 1 ] != from->aimdirection[ 1 ] )
    {
        buf->WriteOneBit( 1 );
        buf->WriteFloat( to->aimdirection[ 1 ] );
    }
    else
    {
        buf->WriteOneBit( 0 );
    }

    if ( to->aimdirection[ 2 ] != from->aimdirection[ 2 ] )
    {
        buf->WriteOneBit( 1 );
        buf->WriteFloat( to->aimdirection[ 2 ] );
    }
    else
    {
        buf->WriteOneBit( 0 );
    }

    if ( to->forwardmove != from->forwardmove )
    {
        buf->WriteOneBit( 1 );
        buf->WriteFloat( to->forwardmove );
    }
    else
    {
        buf->WriteOneBit( 0 );
    }

    if ( to->sidemove != from->sidemove )
    {
        buf->WriteOneBit( 1 );
        buf->WriteFloat( to->sidemove );
    }
    else
    {
        buf->WriteOneBit( 0 );
    }

    if ( to->upmove != from->upmove )
    {
        buf->WriteOneBit( 1 );
        buf->WriteFloat( to->upmove );
    }
    else
    {
        buf->WriteOneBit( 0 );
    }

    if ( to->buttons != from->buttons )
    {
        buf->WriteOneBit( 1 );
        buf->WriteUBitLong( to->buttons , 32 );
    }
    else
    {
        buf->WriteOneBit( 0 );
    }

    if ( to->impulse != from->impulse )
    {
        buf->WriteOneBit( 1 );
        buf->WriteUBitLong( to->impulse , 8 );
    }
    else
    {
        buf->WriteOneBit( 0 );
    }

    if ( to->weaponselect != from->weaponselect )
    {
        buf->WriteOneBit( 1 );
        buf->WriteUBitLong( to->weaponselect , MAX_EDICT_BITS );

        if ( to->weaponsubtype != from->weaponsubtype )
        {
            buf->WriteOneBit( 1 );
            buf->WriteUBitLong( to->weaponsubtype , 6 );
        }
        else
        {
            buf->WriteOneBit( 0 );
        }
    }
    else
    {
        buf->WriteOneBit( 0 );
    }

    // TODO: Can probably get away with fewer bits.
    if ( to->mousedx != from->mousedx )
    {
        buf->WriteOneBit( 1 );
        buf->WriteShort( to->mousedx );
    }
    else
    {
        buf->WriteOneBit( 0 );
    }

    if ( to->mousedy != from->mousedy )
    {
        buf->WriteOneBit( 1 );
        buf->WriteShort( to->mousedy );
    }
    else
    {
        buf->WriteOneBit( 0 );
    }
}

bool __fastcall new_WriteUserCmdDeltaBuffer( _FASTCALLD , int unknown , bf_write *buf , int from , int to , bool isnewcommand )
{
    CInput *_Input = ( CInput* ) ThisPTR;

    /*

    .text:202B0993                 mov     edx, edi
    .text:202B0995                 push    esi
    .text:202B0996                 mov     ecx, ebx
    .text:202B0998                 call    sub_20312540
    .text:202B099D ; 45:   if ( !*(_BYTE *)(a3 + 16) )
    .text:202B099D                 add     esp, 4
    */

    CUserCmd nullcmd;

    CUserCmd *f = nullptr , *t = nullptr;

    if ( from == -1 )
    {
        f = &nullcmd;
    }
    else
    {
        f = &_Input->m_pCommands[ from % MULTIPLAYER_BACKUP ];

        if ( !f )
        {
            f = &nullcmd;
        }
    }

    t = &_Input->m_pCommands[ to % MULTIPLAYER_BACKUP ];

    if ( !t )
    {
        t = &nullcmd;
    }

    /*int LastGoing = _OffsetManualthis( 0x4CAC , int , Offsets->pClientState ) + _OffsetManualthis( 0x4CB0 , int , Offsets->pClientState ) + 1;

    EngineClient->Con_NPrintf( 1 , "%i" , LastGoing );

    if ( from >= LastGoing )
        t->tick_count = TICKCOUNT_PAUSE;*/

    WriteUsercmd( buf , t , f );

    /*static Pointer pWriteUserCmd = _GetModule<Pointer>( TEXT( "client.dll" ) , 0x312540 );

    _asm
    {
        mov edx , t
        push f
        mov ecx , [ ebp + 0xC ]
        call pWriteUserCmd
        add esp , 4
    }*/

    //bool bOverflowed = ( bool ) _CallFunction<bool , Pointer , int , Pointer , int , int , bool>( e_thiscall , DetouredFunctions[ D_WriteUserCmdDeltaBuffer ]->pOld , _Input , unknown , buf , from , to , isnewcommand );

    return true;
}