#include "Includes.hxx"
#include "Main.hxx"

__pragma( warning( push ) )
__pragma( warning( disable:4100 ) )

CCLCMsg_ClientInfo *MsgClientInfo = nullptr;
CCLCMsg_VoiceData *MsgVoiceData = nullptr;

bool __fastcall new_SendNetMsg( _FASTCALLD , INetMessage &msg , bool bForceReliable , bool bVoice )
{
    auto msgName = msg.GetName();

    if ( !strcmp( "CNETMsg_SetConVar" , msgName ) )
    {
        Backtrack->UpdateLerpTime();

        if ( Cvars[ hack_show_server_queries_cvars ]->GetInt() )
			N_Console::Print( TEXT( "%s\n" ) , msg.ToString() );

        /*CNETMsg_SetConVar *convar = ( CNETMsg_SetConVar* ) &msg;

        for ( int i = 0; i < convar->m_ConVars.m_Size; i++ )
        {
            if ( !strcmp( convar->m_ConVars[ i ].name , "cl_interpolate" ) )
            {
                strcpy_s( convar->m_ConVars[ i ].value , "0" );
            }
        }*/
    }

   /* if ( !strcmp( "CCLCMsg_ClientMessage" , msg.GetName() ) )
    {
        N_Console::Print<FOREGROUND_RED>( TEXT( "%s %p \n" ) , msg.ToString() , &msg );
    }

    if ( !strcmp( "CCLCMsg_ServerStatus" , msg.GetName() ) )
    {
        N_Console::Print<FOREGROUND_RED>( TEXT( "%s %p \n" ) , msg.ToString() , &msg );
    }

    if ( strcmp( "CCLCMsg_Move" , msg.GetName() ) && strcmp( "CNETMsg_Tick" , msg.GetName() ) )
        N_Console::Print<FOREGROUND_RED>( TEXT( "%s %p %s \n" ) , msg.ToString() , &msg , msg.GetName() );

    if ( !strcmp( "CCLCMsg_RequestPause" , msg.GetName() ) )
    {
        N_Console::Print<FOREGROUND_RED>( TEXT( "%s %p \n" ) , msg.ToString() , &msg );
    }

    if ( !strcmp( "CCLCMsg_ClientInfo" , msg.GetName() ) )
    {
        //N_Console::Print<FOREGROUND_RED>( TEXT( "%s %p \n" ) , msg.ToString() , &msg );

        DO_ONCE( MsgClientInfo = ( CCLCMsg_ClientInfo* ) Alloc( msg.GetSize() );

        memcpy( MsgClientInfo , &msg , msg.GetSize() ););
    }

    //CCLCMsg_ServerStatus
    if ( !strcmp( "CCLCMsg_VoiceData" , msg.GetName() ) )
    {
        CCLCMsg_VoiceData *voicedata = ( CCLCMsg_VoiceData* ) &msg;
        strcpy( voicedata->sPlayerName , "" );
        strcpy( voicedata->sSteamID , "" );

        DO_ONCE( MsgVoiceData = ( CCLCMsg_VoiceData* ) Alloc( msg.GetSize() );
        memcpy( MsgVoiceData , &msg , msg.GetSize() ););
    }*/

    if ( !strcmp( "CCLCMsg_ClientInfo" , msg.GetName() ) )
    {
        char buf[ 32 ];
        sprintf_s( buf , "cl_interp %f" , Globals->interval_per_tick );
        EngineClient->ExecuteClientCmd( buf );
    }

    if ( !strcmp( "CCLCMsg_RespondCvarValue" , msgName ) )
    {
        CCLCMsg_RespondCvarValue* cvarmsg = ( CCLCMsg_RespondCvarValue* ) &msg;

        if ( Cvars[ hack_show_server_queries_cvars ]->GetInt() )
        {
            N_Console::Print( TEXT( "%s\n" ) , msg.ToString() );
        }

        ConVar *FoundCvar = nullptr;
        FoundCvar = Cvar->FindVar( cvarmsg->sCvarName );

        if ( FoundCvar != nullptr )
        {
            if ( !( FoundCvar->GetFlags() & FCVAR_REPLICATED ) )
            {
                if ( strcmp( "m_yaw" , cvarmsg->sCvarName )
                     && strcmp( "m_pitch" , cvarmsg->sCvarName )
                     && strcmp( "sensitivity" , cvarmsg->sCvarName )
                     && strcmp( "m_rawinput" , cvarmsg->sCvarName )
                     && strcmp( "m_customaccel" , cvarmsg->sCvarName )
                     && strcmp( "mat_dxlevel" , cvarmsg->sCvarName ) )
                {
                    if ( FoundCvar != nullptr )
                    {
                        strcpy( cvarmsg->sCvarValue , FoundCvar->m_pszDefaultValue );
                    }
                }
                else
                {
                    if ( !strcmp( "m_customaccel" , cvarmsg->sCvarName ) )
                    {
                        strcpy( cvarmsg->sCvarValue , "2" );
                    }
                    else if ( !strcmp( "mat_dxlevel" , cvarmsg->sCvarName ) )
                    {
                        strcpy( cvarmsg->sCvarValue , "95" );
                    }
                }

                if ( Cvars[ hack_show_server_queries_cvars ]->GetInt() )
                {
                    CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "%s\n" ) , msg.ToString() );
                }
            }
        }
    }

    return _CallFunction<bool , e_thiscall , Pointer , INetMessage& , bool , bool>( DetouredFunctions[ D_SendNetMsg ]->pOld , ThisPTR , msg , bForceReliable , bVoice );
}

__pragma( warning( pop ) )