#include "Includes.hxx"
#include "Main.hxx"

// Entry point of the dll : https://msdn.microsoft.com/fr-fr/library/windows/desktop/ms682596(v=vs.85).aspx

BOOL WINAPI DllMain(
    Pointer pModule ,  // Address of the current module
    HEX HexReason ,     // Obvious
    Pointer pReserved )  // Something that is useless. Wich we can use for a manual mapper for example.
{

    DisableThreadLibraryCalls( ( HMODULE ) pModule );
    // If the dll is attached to the processus we can start doing things.
    // We must create a thread inside the dll because the loader of the dll would be stuck in some cases, it would be waiting for the thread finishing so we avoid that.
    HANDLE hThread = nullptr;

    if ( HexReason == DLL_PROCESS_ATTACH )
    {
        S_Routine *SRoutine = new S_Routine( pModule , pReserved );

        N_Console::Open();

        if ( !SRoutine->bManualMapped )
            hThread = CreateThread( nullptr , 0 , ( LPTHREAD_START_ROUTINE ) ( Pointer ) _RoutineHack , ( Pointer ) SRoutine , 0 , nullptr );
        else
            return  ( BOOL ) _RoutineHack( SRoutine );

        return TRUE;
    }

    return TRUE;
}

/* TODO: mac entry point here */