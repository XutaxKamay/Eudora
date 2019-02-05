#include "Includes.hxx"
#include "CPE_Server.hxx"

C_SocketServer Server;
wchar_t** listArgs = nullptr;

DWORD __stdcall ClientRoutine( C_SocketHandleClient* Client )
{
    if ( Client->RecvPublicKey() && Client->SendPublicKey() )
    {
        HEX Size;
        auto pDosHeader = ( PIMAGE_DOS_HEADER ) N_FileSystem::ReadFile( AutoConvertW( listArgs[ 0 ] ) , &Size );

        C_CPE* CPE = g_CConstructPE.Reconstruct( pDosHeader );

        int iResult = 0;
        bool bFirstTime = true;

        C_CConstructPEServer ServerPE;

        auto ModulesToLoad = ServerPE.MakeModulesInfos( CPE );

        if ( Client->SendDataSecure( ModulesToLoad ) )
        {
            Client->DebugKeys();
            //system( "pause" );

            delete ModulesToLoad;

            auto InjectionInfos = Client->RecvDataSecure( 0x10000000 );

            if ( InjectionInfos != nullptr && ServerPE.ProcessInjectionInfo( *InjectionInfos ) )
            {
                delete InjectionInfos;

                while ( ServerPE.m_DataServer.m_bNeedsForwardingDLLs || bFirstTime )
                {
                    bFirstTime = false;

                    SocketBuffer* ModulesForwardedToLoad = ServerPE.MakeModulesInfosForwarded( CPE );

                    if ( Client->SendDataSecure( ModulesForwardedToLoad ) )
                    {
                        if ( !ServerPE.m_DataServer.m_bNeedsForwardingDLLs )
                            break;

                        auto InjectionInfosForwarded = Client->RecvDataSecure( 0x10000000 );

                        if ( InjectionInfosForwarded != nullptr )
                        {
                            ServerPE.ProcessInjectionInfo( *InjectionInfosForwarded );
                            delete InjectionInfosForwarded;
                        }
                        else
                            break;
                    }
                    else
                        break;

                    delete ModulesForwardedToLoad;
                }

                auto CPEMinimal = ServerPE.MakeCPEMinimal( CPE );

                if ( CPEMinimal != nullptr )
                {
                    if ( Client->SendDataSecure( CPEMinimal ) )
                    {
                        if ( Client->CloseListennerForSocket() )
                        {
                            iResult = 1;
                        }
                    }
                }

                delete CPEMinimal;
            }
        }

        delete CPE;
        delete pDosHeader;

        return iResult;
    }

    return 0;
}

int WINAPI wWinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , PWSTR pCmdLine , int nCmdShow )
{
    N_Console::Open();

    int iArgs;
    listArgs = CommandLineToArgvW( pCmdLine , &iArgs );

    if ( iArgs < 1 )
    {
        N_Console::Print<FOREGROUND_RED>( TEXT( "Not enough args.\n" ) );
        return 0;
    }

    Server.OpenListenner( ClientRoutine , "2407" , true );

    N_Console::Pause();

    return 0;
}