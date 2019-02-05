#include "Includes.hxx"
#include "Main.hxx"

#define FCVAR_MINE FCVAR_ARCHIVE | FCVAR_CLIENTDLL | FCVAR_SERVER_CANNOT_QUERY

CSavedServerCvars* SavedServerCvars = new CSavedServerCvars();
ConSave* CSave = new ConSave();

String sPathConfig[] = AutoConvertC( TEXT( "C:\\CSGO_Configs\\configs.1337" ) );

ConVar *Cvars[ Cvars_MAX ] =
{
    nullptr , nullptr , nullptr , nullptr ,
    nullptr , nullptr , nullptr , nullptr ,
    nullptr , nullptr , nullptr , nullptr ,
    nullptr , nullptr , nullptr , nullptr ,
    nullptr , nullptr , nullptr , nullptr ,
    nullptr , nullptr , nullptr , nullptr ,
    nullptr , nullptr , nullptr , nullptr ,
    nullptr , nullptr , nullptr , nullptr ,
    nullptr , nullptr , nullptr , nullptr ,
    nullptr , nullptr ,
};

ConCommand *Commands[ Commands_MAX ] =
{
    nullptr , nullptr , nullptr , nullptr ,
    nullptr , nullptr , nullptr , nullptr ,
    nullptr , nullptr , nullptr , nullptr ,
    //nullptr
};

#define NewCvar( cvarname , value , help ) Cvars[ cvarname ] = new ConVar( AutoConvertC(TEXT( #cvarname )) , AutoConvertC(TEXT( value )) , FCVAR_MINE , AutoConvertC(TEXT( help )) );
#define NewCommand( commandname , value , help ) Commands[ commandname ] = new ConCommand( AutoConvertC(TEXT( #commandname )) , value , AutoConvertC(TEXT( help )) );

void PredictCallBack( IConVar *var , const char *pOldValue , float flOldValue )
{
    var->SetValue( "1" );
    flOldValue = 1;
}

void RemoveRestrictionCvars()
{
    // Iterate all commands, and remove the flags.

    ICvar::Iterator IT( Cvar.pClass );
    for ( IT.SetFirst(); IT.IsValid(); IT.Next() )
    {
        ConCommandBase *cmd = IT.Get();

        if ( cmd == nullptr )
            continue;

        cmd->m_nFlags &= ~FCVAR_CHEAT;
        cmd->m_nFlags &= ~FCVAR_PROTECTED;
        cmd->m_nFlags &= ~FCVAR_HIDDEN;
        cmd->m_nFlags &= ~FCVAR_DEVELOPMENTONLY;
    }

    //Cvar->FindVar( "host_timescale" )->RemoveFlags( FCVAR_CHEAT | FCVAR_REPLICATED );
    Cvar->FindVar( "cl_threaded_bone_setup" )->SetValue( 1 );
    Cvar->FindVar( "cl_threaded_init" )->SetValue( 1 );
    Cvar->FindVar( "cl_clockdrift_max_ms_threadmode" )->SetValue( 1 );
    Cvar->FindVar( "r_threaded_shadow_clip" )->SetValue( 1 );
    Cvar->FindVar( "snd_mix_async" )->SetValue( 1 );
    Cvar->FindVar( "mat_queue_mode" )->SetValue( 2 );
    //Cvar->FindVar( "host_thread_mode" )->SetValue( 2 );
    Cvar->FindVar( "host_threaded_sound" )->SetValue( 1 );
    Cvar->FindVar( "mat_queue_mode_force_allow" )->SetValue( 1 );
    Cvar->FindVar( "r_drawallrenderables" )->SetValue( 1 );
    Cvar->FindVar( "glow_outline_effect_enable" )->SetValue( 0 );
	Cvar->FindVar( "cl_interp" )->SetValue( "0.1" );
    //host_threaded_sound

    /*ConVar* cl_interpolate = ( ConVar* ) ( _GetModule( TEXT( "engine.dll" ) , 0x57A788 ) );
    cl_interpolate->SetValue( 0 );

    cl_interpolate = ( ConVar* ) ( _GetModule( TEXT( "engine.dll" ) , 0x5796C8 ) );
    cl_interpolate->SetValue( 0 );*/
}

void CMrSetFileName( const CCommand &args )
{
    if ( args.ArgC() < 2 || !strcmp( args.Arg( 1 ) , "" ) )
    {
        return;
    }

    MovementRecorder->sFileName = AutoConvertS( args.Arg( 1 ) );
}

void CMrSetTmpFileName( const CCommand &args )
{
    if ( args.ArgC() < 2 || !strcmp( args.Arg( 1 ) , "" ) )
    {
        return;
    }

    MovementRecorder->sTmpFileName = AutoConvertS( args.Arg( 1 ) );
}

void CMrPlay()
{
    MovementRecorder->iState = MR_State::MR_Play;
}

void CMrRecord()
{
    MovementRecorder->iState = MR_State::MR_Record;
}

void CMrStop()
{
    MovementRecorder->iState = MR_State::MR_Stop;
}

void CMrPause()
{
    if ( MovementRecorder->iState == MR_State::MR_Pause )
        MovementRecorder->iState = MovementRecorder->iOldState;
    else
        MovementRecorder->iState = MR_State::MR_Pause;
}

void CMrLoad( const CCommand &args )
{
    CMrSetFileName( args );
    MovementRecorder->RunLoad();
}

void CMrSave( const CCommand &args )
{
    CMrSetFileName( args );
    MovementRecorder->RunSave();
}

void CCommandSaveServerCvars( const CCommand &args )
{
    if ( !( args.ArgC() < 2 || !strcmp( args.Arg( 1 ) , "" ) ) )
    {
        Cvars[ hack_path_server_config ]->SetValue( args.Arg( 1 ) );
    }

    SavedServerCvars->Generate();
}

void CGetPosAng( const CCommand &args )
{
    if ( args.ArgC() < 2 || !strcmp( args.Arg( 1 ) , "" ) )
    {
        return;
    }

    size_t sTick = ( size_t ) atoi( args.Arg( 1 ) );

    if ( sTick > MovementRecorder->GetFinalTick() )
    {
        Offsets->Msg( AutoConvertC( TEXT( "No valid tick.\n" ) ) );
        return;
    }

    CMovementRecord *MR = &MovementRecorder->v_mrs[ sTick ];

    char buf[ 0xFF ];
    sprintf_s( buf , AutoConvertC( TEXT( "setpos %f %f %f; setang %f %f %f;\n" ) ) , MR->m_PlayerRecord.m_vecOrigin.x , MR->m_PlayerRecord.m_vecOrigin.y , MR->m_PlayerRecord.m_vecOrigin.z ,
               MR->m_cmd.viewangles.x , MR->m_cmd.viewangles.y , MR->m_cmd.viewangles.z );

    Offsets->Msg( buf );

    SetClipBoard( AutoConvertS( buf ) );
}

void CSaveConfig( const CCommand &args )
{
    if ( !( args.ArgC() < 2 || !strcmp( args.Arg( 1 ) , "" ) ) )
        Cvars[ hack_mr_path_record ]->SetValue( args.Arg( 1 ) );

    CSave->SaveSettings();
}

void CLoadConfig( const CCommand &args )
{
    if ( !( args.ArgC() < 2 || !strcmp( args.Arg( 1 ) , "" ) ) )
        Cvars[ hack_mr_path_record ]->SetValue( args.Arg( 1 ) );

    CSave->LoadSettings();
}

void CComputeEndZone( const CCommand &args )
{
    MovementRecorder->EndZone.ZoneStage = Zone_Computing_Start;
}

void RegisterCvars()
{
    NewCvar( hack_esp_glow , "1" , "[ESP] Draws glow on entities. 1) Enemies only 2) Players 3) Everything possible. " );
    NewCvar( hack_esp_glow_mode , "1" , "[ESP] Mode for glow on entities. 0) Normal 1) Zbuffered " );
    NewCvar( hack_esp_glow_bloom_amount , "2.5" , "[ESP] Bloom amount on glowing entities." );
    NewCvar( hack_esp_glow_stencil_mode , "0" , "[ESP]\n\t0: Draws partially occluded glows in a more 3d-esque way, making them look more like they're actually surrounding the model."
             "\n\t1: Draws partially occluded glows in a more 2d-esque way, which can make them more visible."
             "\n\tSee https://i.imgur.com/OJQkXei.gif" );
    NewCvar( hack_show_server_queries_cvars , "0" , "[MISC] Shows the cvars that the server ask from your game." );
    NewCvar( hack_mr_key , "Megauberhax2407L33tYay" , "[MR] Key encryption of your record." );
    NewCvar( hack_mr_savetmprecord , "1" , "[MR] Save a temporary record everytime you stop recording." );
    //Cvars[ hack_timescale ] = new ConVar( TEXT( "hack_timescale" ) , TEXT( "1.0" ) , FCVAR_MINE , TEXT( "[MISC] Timescale hack based on air stuck." ) , true , 0.0f , true , 1.0f );
    NewCvar( hack_mr_path_record , "C:\\CSGO_Records" , "[MR] Folder path of recording." );
    NewCvar( hack_path_server_config , "C:\\CSGO_Configs\\servers" , "[MR] Folder path of the active server commands saved." );
    NewCvar( hack_backtrack , "3" , "[MISC] Backtrack players, exploit from lag compensation. 1) Simple backtrack. 2) Backtrack and show only best target 3) Backtrack and show all targets and best one." );
    NewCvar( hack_backtrack_server_has_posfix , "0" , "[MISC] Backtrack on previous position of localplayer. (useful for servers that has posfix bug)" );
    NewCvar( hack_backtrack_check_sqr , "1" , "[MISC] Backtrack check teleportations" );
    NewCvar( hack_backtrack_team_check , "1" , "[MISC] Backtrack check teams" );
    NewCvar( hack_autobhop , "0" , "[MISC] \n\t0: Perfect autobhop undetected on most anti cheats. (smac etc..)\n\t1: Custom autobhop should be fine in every servers that has scroll (safe), ask a config in forums.\n" );
    NewCvar( hack_autobhop_ground_dist_min , "20.0" , "[MISC] Minimum ground distance to simulate scroll in air." );
    NewCvar( hack_autobhop_ground_dist_max , "25.0" , "[MISC] Maximum ground distance to simulate scroll in air." );
    NewCvar( hack_autobhop_inair_minwait , "1" , "[MISC] Minimum ticks to wait before jumping in air." );
    NewCvar( hack_autobhop_inair_maxwait , "4" , "[MISC] Maximum ticks to wait before jumping in air." );
    NewCvar( hack_autobhop_onground_minwait , "0" , "[MISC] Minimum ticks to wait before jumping on ground." );
    NewCvar( hack_autobhop_onground_maxwait , "2" , "[MISC] Maximum ticks to wait before jumping on ground." );
    NewCvar( hack_autobhop_perf_min , "1" , "[MISC] Minimum perfect jumps in a row." );
    NewCvar( hack_autobhop_perf_max , "10" , "[MISC] Maximum perfect jumps in a row." );
    NewCvar( hack_edgejump , "0" , "[MISC] Jumps automatically when about to fall." );
    NewCvar( hack_angelstrafe , "0" , "[MISC] Fake angel strafe." );
    NewCvar( hack_mr_endzone_draw , "0" , "[MR] Draws the endzone." );
    NewCvar( hack_mr_endzone_enable , "0" , "[MR] Enable the endzone. If enabled , your recording will stop once getting into the zone." );

    Cvars[ hack_backtrack_f_model_a ] = new ConVar( AutoConvertC( TEXT( "hack_backtrack_f_model_a" ) ) , AutoConvertC( TEXT( "1.0" ) )
                                                    , FCVAR_MINE , AutoConvertC( TEXT( "[MISC] Backtrack: Color of the best target found (alpha)." ) ) , true , 0.0f , true , 1.0f );
    Cvars[ hack_backtrack_f_model_r ] = new ConVar( AutoConvertC( TEXT( "hack_backtrack_f_model_r" ) ) , AutoConvertC( TEXT( "0.0" ) )
                                                    , FCVAR_MINE , AutoConvertC( TEXT( "[MISC] Backtrack: Color of the best target found (red)." ) ) , true , 0.0f , true , 1.0f );
    Cvars[ hack_backtrack_f_model_g ] = new ConVar( AutoConvertC( TEXT( "hack_backtrack_f_model_g" ) ) , AutoConvertC( TEXT( "1.0" ) )
                                                    , FCVAR_MINE , AutoConvertC( TEXT( "[MISC] Backtrack: Color of the best target found (blue)." ) ) , true , 0.0f , true , 1.0f );
    Cvars[ hack_backtrack_f_model_b ] = new ConVar( AutoConvertC( TEXT( "hack_backtrack_f_model_b" ) ) , AutoConvertC( TEXT( "0.0" ) )
                                                    , FCVAR_MINE , AutoConvertC( TEXT( "[MISC] Backtrack: Color of the best target found (green)." ) ) , true , 0.0f , true , 1.0f );

    Cvars[ hack_backtrack_model_a ] = new ConVar( AutoConvertC( TEXT( "hack_backtrack_model_a" ) ) , AutoConvertC( TEXT( "1.0" ) )
                                                  , FCVAR_MINE , AutoConvertC( TEXT( "[MISC] Backtrack: Color of all players that could be backtracked from history (alpha)." ) ) , true , 0.0f , true , 1.0f );
    Cvars[ hack_backtrack_model_r ] = new ConVar( AutoConvertC( TEXT( "hack_backtrack_model_r" ) ) , AutoConvertC( TEXT( "1.0" ) )
                                                  , FCVAR_MINE , AutoConvertC( TEXT( "[MISC] Backtrack: Color of all players that could be backtracked from history (red)." ) ) , true , 0.0f , true , 1.0f );
    Cvars[ hack_backtrack_model_g ] = new ConVar( AutoConvertC( TEXT( "hack_backtrack_model_g" ) ) , AutoConvertC( TEXT( "1.0" ) )
                                                  , FCVAR_MINE , AutoConvertC( TEXT( "[MISC] Backtrack: Color of all players that could be backtracked from history (blue)." ) ) , true , 0.0f , true , 1.0f );
    Cvars[ hack_backtrack_model_b ] = new ConVar( AutoConvertC( TEXT( "hack_backtrack_model_b" ) ) , AutoConvertC( TEXT( "1.0" ) )
                                                  , FCVAR_MINE , AutoConvertC( TEXT( "[MISC] Backtrack: Color of all players that could be backtracked from history (green)." ) ) , true , 0.0f , true , 1.0f );

    Cvars[ hack_mr_endzone_a ] = new ConVar( AutoConvertC( TEXT( "hack_mr_endzone_a" ) ) , AutoConvertC( TEXT( "1.0" ) )
                                             , FCVAR_MINE , AutoConvertC( TEXT( "[MR] EndZone color (alpha)." ) ) , true , 0.0f , true , 1.0f );
    Cvars[ hack_mr_endzone_r ] = new ConVar( AutoConvertC( TEXT( "hack_mr_endzone_r" ) ) , AutoConvertC( TEXT( "1.0" ) )
                                             , FCVAR_MINE , AutoConvertC( TEXT( "[MR] EndZone color (red)." ) ) , true , 0.0f , true , 1.0f );
    Cvars[ hack_mr_endzone_g ] = new ConVar( AutoConvertC( TEXT( "hack_mr_endzone_g" ) ) , AutoConvertC( TEXT( "1.0" ) )
                                             , FCVAR_MINE , AutoConvertC( TEXT( "[MR] EndZone color (blue)." ) ) , true , 0.0f , true , 1.0f );
    Cvars[ hack_mr_endzone_b ] = new ConVar( AutoConvertC( TEXT( "hack_mr_endzone_b" ) ) , AutoConvertC( TEXT( "1.0" ) )
                                             , FCVAR_MINE , AutoConvertC( TEXT( "[MR] EndZone color (green)." ) ) , true , 0.0f , true , 1.0f );

    //NewCommand( hack_mr_togglepause , CMrPause , "[MR] Toggle pause recording/playing." );
    NewCommand( hack_mr_stop , CMrStop , "[MR] Stop recording/playing." );
    NewCommand( hack_mr_record , CMrRecord , "[MR] Start the recording." );
    NewCommand( hack_mr_play , CMrPlay , "[MR] Play the recording." );
    NewCommand( hack_mr_load , CMrLoad , "[MR] Load a record." );
    NewCommand( hack_mr_save , CMrSave , "[MR] Save a record." );
    NewCommand( hack_mr_filename , CMrSetFileName , "[MR] Set the file name of the record." );
    NewCommand( hack_mr_tmpfilename , CMrSetTmpFileName , "[MR] When stopping a record, it saves your record in your folder, so you can get an history of your records (works when hack_mr_tmpsaverecord on 1)." );
    NewCommand( hack_mr_computeendzone , CComputeEndZone , "[MR] Compute your end zone, so you don't have to execute the command for stopping the recording." );
    NewCommand( hack_save_server_cvars , CCommandSaveServerCvars , "[MISC] Save all server's cvars into the desired path." );
    NewCommand( hack_mr_getposang , CGetPosAng , "[MR] Get setpos and setang of the tick asked on the record." );
    NewCommand( hack_save_config , CSaveConfig , "[MR] Save config into the desired path." );
    NewCommand( hack_load_config , CLoadConfig , "[MR] Load config into the desired path." );

    for ( int i = 0; i < Cvars_MAX; i++ )
    {
        if ( Cvars[ i ] != nullptr )
        {
            Cvar->RegisterConCommand( Cvars[ i ] );
        }
    }

    for ( int i = 0; i < Commands_MAX; i++ )
    {
        if ( Commands[ i ] != nullptr )
        {
            Cvar->RegisterConCommand( Commands[ i ] );
        }
    }
}

void UnRegisterCvars()
{
    for ( int i = 0; i < Cvars_MAX; i++ )
    {
        if ( Cvars[ i ] != nullptr )
        {
            Cvar->UnregisterConCommand( Cvars[ i ] );
            delete Cvars[ i ];
            Cvars[ i ] = nullptr;
        }
    }

    for ( int i = 0; i < Commands_MAX; i++ )
    {
        if ( Commands[ i ] != nullptr )
        {
            Cvar->UnregisterConCommand( Commands[ i ] );
            delete Commands[ i ];
            Commands[ i ] = nullptr;
        }
    }
}

ConSave::ConSave()
{
    sBuffer.clear();
}

constexpr String* sKeyValue = TEXT( "->\"" );

void ConSave::SaveSettings()
{
	stdString sFullPath = sPathConfig;

    sBuffer = TEXT( "Don't change touch on the characters -> or your settings can't be loaded! , also do not forget \"\" for setting the cvar value after ->.\n" );

    for ( int i = 0; i < Cvars_MAX; i++ )
    {
        if ( Cvars[ i ] == nullptr )
            continue;

        sBuffer += stdString( TEXT( "\n" ) ) + AutoConvertS( Cvars[ i ]->GetHelpText() ) + TEXT( "\n\n" );
        sBuffer += AutoConvertS( Cvars[ i ]->m_pszName );
        sBuffer += stdString( sKeyValue ) + AutoConvertS( Cvars[ i ]->GetString() ) + TEXT( "\"\n" );
    }

    size_t nPos = sFullPath.rfind( TEXT( "\\" ) );

    stdString sPath = sFullPath.substr( 0 , nPos );

    if ( N_FileSystem::CreateFolder( sPath ) )
    {
        N_FileSystem::ClearFile( sFullPath );
        N_FileSystem::WriteFile( sFullPath , sBuffer );
    }
}

bool ConSave::LoadSettings()
{
	stdString sPath = sPathConfig;

    HEX sSize = -1;
    Pointer pConfigBuffer = N_FileSystem::ReadFile( sPath , &sSize );
    if ( sSize == -1 )
        return false;

    sBuffer = stdString( ( String* ) pConfigBuffer , sSize );

    for ( int i = 0; i < Cvars_MAX; i++ )
    {
        if ( Cvars[ i ] == nullptr )
            continue;

        size_t sPos = sBuffer.find( AutoConvertS( Cvars[ i ]->GetName() ) );
        if ( sPos != stdString::npos )
        {
            sPos = sBuffer.find( sKeyValue , sPos );
            sPos += ( sizeof( sKeyValue ) / sizeof( String ) ) - 1;
            size_t sPos2 = sBuffer.find( TEXT( "\"" ) , sPos );
            sPos2 -= sPos;
            stdString sCvarValue = sBuffer.substr( sPos , sPos2 );
            Cvars[ i ]->SetValue( AutoConvertC( sCvarValue.c_str() ) );
        }
    }

    return true;
}

CSavedServerCvar&CSavedServerCvar::operator=( const ConVar& src )
{
    char sBufValue[ 0xFF ] , sBufName[ 0xFF ] , sBufHelp[ 0xFFF ];

    strcpy_s( sBufName , src.m_pszName );
    strcpy_s( sBufValue , src.GetString() );
    strcpy_s( sBufHelp , src.GetHelpText() );

    sName = sBufName;
    sValue = sBufValue;
    sHelp = sBufHelp;

    return *this;
}

void CSavedServerCvars::GenerateServerCvars()
{
    ServerCvars.clear();

    ICvar::Iterator IT( Cvar.pClass );
    for ( IT.SetFirst(); IT.IsValid(); IT.Next() )
    {
        ConCommandBase *cmd = IT.Get();

        if ( cmd == nullptr )
            continue;

        ConVar* cvar = ( ConVar* ) Cvar->FindVar( cmd->m_pszName );

        if ( cvar != nullptr )
        {
            if ( ( cvar->GetFlags() & FCVAR_MATERIAL_THREAD_MASK )
                 || ( strstr( cvar->GetName() , "cl_" ) != nullptr ) )
                continue;

            if (
                ( ( cvar->GetFlags() & FCVAR_REPLICATED )
                || ( cvar->GetFlags() & FCVAR_PROTECTED )
                || ( cvar->GetFlags() & FCVAR_GAMEDLL )
                || ( cvar->GetFlags() == 0 )
                || ( cvar->GetFlags() & FCVAR_NOTIFY )
                || ( cvar->GetFlags() & FCVAR_RELEASE ) ) )
            {
                ServerCvars.push_back( *cvar );
            }
        }
    }

    auto compareNoCase = [] ( CSavedServerCvar first , CSavedServerCvar second )
    {
        size_t i = 0;
        while ( ( i < first.sName.length() ) && ( i < second.sName.length() ) )
        {
            if ( tolower( first.sName[ i ] ) < tolower( second.sName[ i ] ) ) return true;
            else if ( tolower( first.sName[ i ] ) > tolower( second.sName[ i ] ) ) return false;
            i++;
        }

        if ( first.sName.length() < second.sName.length() ) return true;
        else return false;
    };

    std::sort( ServerCvars.begin() , ServerCvars.end() , compareNoCase );
}

void CSavedServerCvars::GenServerCFG()
{
    sFinalBuffer.clear();

    for ( auto it = ServerCvars.begin(); it != ServerCvars.end(); it++ )
    {
        it->sHelp = " //  " + it->sHelp;

        bool bBreak = false;
        size_t nPos = 0;

        while ( !bBreak )
        {
            nPos = it->sHelp.find( "\n" , nPos );

            if ( nPos != stdString::npos && ( it->sHelp.size() > nPos + 4 ) )
            {
                nPos += 1;
                it->sHelp.insert( nPos , "//" );
            }
            else
                bBreak = true;
        }

        sFinalBuffer += stdString( AutoConvertS( it->sHelp ) ) + TEXT( "\n" );
        sFinalBuffer += stdString( AutoConvertS( it->sName ) ) + TEXT( " \"" ) + AutoConvertS( it->sValue ) + TEXT( "\"" );
        sFinalBuffer += TEXT( "\n\n" );
    }

    sMap = AutoConvertS( EngineClient->GetLevelName() );
    sServerName = AutoConvertS( Cvar->FindVar( AutoConvertC( TEXT( "hostname" ) ) )->GetString() );

    size_t nPos = sMap.find( TEXT( "maps\\" ) );

    if ( nPos != stdString::npos )
    {
        sMap.erase( sMap.begin() + nPos , sMap.begin() + nPos + 6 );
    }

    stdString sFullPath = stdString( AutoConvertS( Cvars[ hack_path_server_config ]->GetString() ) ) + TEXT( "\\" ) + sServerName;

    if ( N_FileSystem::CreateFolder( sFullPath ) )
    {
        sFullPath += TEXT( "\\Gen_" ) + sMap + TEXT( ".cfg" );
        N_FileSystem::ClearFile( sFullPath );
        N_FileSystem::WriteFile( sFullPath , sFinalBuffer );
    }
}

void CSavedServerCvars::Generate()
{
    GenerateServerCvars();
    GenServerCFG();
}