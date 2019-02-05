#include "Includes.hxx"
#include "Main.hxx"

Pointer _RoutineHack( S_Routine *SRoutine )
{
	// Initialize networked variables and offsets.
	Offsets = new OffsetsManager();
	NetVars = new NetVarsManager();

	// Cvars stuffs.
	RegisterCvars();
	RemoveRestrictionCvars();

	InitCustomMaterials();

	NetVars->MakeHeader();

	CSave->LoadSettings();
	Gui->CreateFonts();

	ProcessHooks();

	/*HANDLE hSimulateBulletsThread = CreateThread( nullptr , 0 , ( LPTHREAD_START_ROUTINE ) ( Pointer ) Backtrack->_SimulateAllBullets , ( Pointer ) &Backtrack->SimulatedBullets , 0 , nullptr );

	SetThreadPriority( hSimulateBulletsThread , MAX_PRIORITY );
	SetThreadPriorityBoost( hSimulateBulletsThread , true );*/

	//HackServer->Create();

	bool bExitThread = false;

	while ( !bExitThread )
	{
		Sleep( 100 );
		// UnInject;
		if ( GetAsyncKeyState( VK_INSERT ) )
		{
			CSave->SaveSettings();

			//TerminateThread( hSimulateBulletsThread , 1 );
			//HackServer->Delete();

			for ( int i = 0; i < D_MAX; i++ )
			{
				if ( DetouredFunctions[ i ] == nullptr )
					continue;

				DetouredFunctions[ i ]->UnHook();
			}

			Sleep( 200 );
			N_Hook::UnInit();
			Sleep( 200 );
			N_Console::Close();
			Sleep( 200 );
			N_Console::WriteLog();
			Sleep( 200 );
			UnRegisterCvars();
			Sleep( 200 );
			delete Backtrack;
			delete NetVars;
			delete Offsets;
			delete MovementRecorder;
			bExitThread = true;
		}
	}

	if ( SRoutine->bManualMapped )
		return ( Pointer ) 1;
	else
	{
		FreeLibraryAndExitThread( ( HMODULE ) SRoutine->pModule , 0 );
	}
}