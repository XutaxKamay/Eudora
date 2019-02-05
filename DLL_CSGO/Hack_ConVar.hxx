#ifndef HACK_CONVARS
#define HACK_CONVARS
#pragma once

class ConVar;

extern void RemoveRestrictionCvars();
extern void RegisterCvars();
extern void UnRegisterCvars();

enum eCvars
{
	hack_mr_key ,
	hack_mr_savetmprecord ,
	hack_mr_path_record ,
	hack_mr_endzone_r ,
	hack_mr_endzone_g ,
	hack_mr_endzone_b ,
	hack_mr_endzone_a ,
	hack_mr_endzone_draw ,
	hack_mr_endzone_enable ,
	hack_esp_glow ,
	hack_esp_glow_mode ,
	hack_esp_glow_bloom_amount ,
	hack_esp_glow_stencil_mode ,
	hack_path_server_config ,
	hack_show_server_queries_cvars ,
	hack_backtrack ,
	hack_backtrack_team_check ,
	hack_backtrack_server_has_posfix ,
	hack_backtrack_check_sqr ,
	hack_backtrack_model_r ,
	hack_backtrack_model_g ,
	hack_backtrack_model_b ,
	hack_backtrack_model_a ,
	hack_backtrack_f_model_r ,
	hack_backtrack_f_model_g ,
	hack_backtrack_f_model_b ,
	hack_backtrack_f_model_a ,
	hack_autobhop ,
	hack_autobhop_onground_minwait ,
	hack_autobhop_onground_maxwait ,
	hack_autobhop_inair_minwait ,
	hack_autobhop_inair_maxwait ,
	hack_autobhop_perf_min ,
	hack_autobhop_perf_max ,
	hack_autobhop_ground_dist_min ,
	hack_autobhop_ground_dist_max ,
	hack_edgejump ,
	hack_angelstrafe ,
	Cvars_MAX
};

extern ConVar *Cvars[ Cvars_MAX ];

enum eCommands
{
	hack_mr_play ,
	hack_mr_stop ,
	hack_mr_record ,
	hack_mr_load ,
	hack_mr_filename ,
	hack_mr_tmpfilename ,
	hack_mr_save ,
	hack_mr_getposang ,
	hack_mr_computeendzone ,
	hack_save_server_cvars ,
	hack_save_config ,
	hack_load_config ,
	Commands_MAX
};

extern ConCommand* Commands[ Commands_MAX ];

class ConSave
{
public:

	ConSave();

	void SaveSettings();
	bool LoadSettings();

	stdString sBuffer;
};

extern ConSave* CSave;

class CSavedServerCvar
{
public:

	CSavedServerCvar()
	{
		sName.clear();
		sValue.clear();
	}

	CSavedServerCvar( const ConVar& src )
	{
		*this = src;
	}

	~CSavedServerCvar()
	{
		sName.clear();
		sValue.clear();
	}

	CSavedServerCvar&operator=( const ConVar& );

	std::string sName , sValue , sHelp;
};

class CSavedServerCvars
{
public:

	CSavedServerCvars()
	{
		sFinalBuffer.clear();
		sMap.clear();
		sServerName.clear();
		ServerCvars.clear();
	}

	void GenerateServerCvars();
	void GenServerCFG();
	void Generate();

	stdString sMap , sServerName;
	stdString sFinalBuffer;
	std::vector<CSavedServerCvar> ServerCvars;
};

extern CSavedServerCvars *SavedServerCvars;

#endif