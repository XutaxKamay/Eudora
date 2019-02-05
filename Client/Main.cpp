#include "Includes.hxx"
#include "CPE_Client.hxx"

int WINAPI wWinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , PWSTR pCmdLine , int nCmdShow )
{
    N_Console::Open();

    g_CConstructPEClient.ProcessProcedure();

    N_Console::Pause();

    return 1;
}