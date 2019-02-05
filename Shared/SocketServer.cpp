#include "Includes.hxx"
#include "Socket.hxx"

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms737889(v=vs.85).aspx

bool C_SocketServer::OpenListenner( SocketRoutine pRoutine , std::string sPort , bool bWaitForMainThread )
{
    m_pClientRoutine = pRoutine;
    HandleServer = new C_SocketHandleServer( sPort );

    m_pMainThread = CreateThread( 0 , 0 , ( LPTHREAD_START_ROUTINE ) MainSocketThread , this , 0 , 0 );

    if ( bWaitForMainThread )
    {
        WaitForSingleObject( m_pMainThread , INFINITE );

        DWORD dwResult;
        GetExitCodeThread( m_pMainThread , &dwResult );

        return ( bool ) dwResult;
    }

    return GetLastError() == ERROR_SUCCESS;
}

DWORD __stdcall C_SocketServer::MainSocketThread( C_SocketServer* SocketServer )
{
    WSADATA wsaData;
    // Initialize Winsock
    int iResult = WSAStartup( MAKEWORD( 2 , 2 ) , &wsaData );

    if ( iResult != 0 )
    {
        CONSOLEDEBUG( TEXT( "WSAStartup failed with error: %d\n" ) , iResult );
        return 0;
    }

    struct addrinfo hints;
    ZeroMemory( &hints , sizeof( hints ) );
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *result = nullptr;

    // Resolve the server address and port
    iResult = getaddrinfo( nullptr , SocketServer->HandleServer->m_sPort.c_str() , &hints , &result );

    if ( iResult != 0 )
    {
        CONSOLEDEBUG( TEXT( "getaddrinfo failed with error: %d\n" ) , iResult );
        WSACleanup();
        return 0;
    }

    // Create a SOCKET for connecting to server
    SOCKET ListenSocket = socket( result->ai_family , result->ai_socktype , result->ai_protocol );

    if ( ListenSocket == INVALID_SOCKET )
    {
        CONSOLEDEBUG( TEXT( "socket failed with error: %ld\n" ) , WSAGetLastError() );
        freeaddrinfo( result );
        WSACleanup();

        return 0;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket , result->ai_addr , ( int ) result->ai_addrlen );

    if ( iResult == SOCKET_ERROR )
    {
        CONSOLEDEBUG( TEXT( "bind failed with error: %d\n" ) , WSAGetLastError() );
        freeaddrinfo( result );
        closesocket( ListenSocket );
        WSACleanup();

        return 0;
    }

    freeaddrinfo( result );

    iResult = listen( ListenSocket , SOMAXCONN );

    if ( iResult == SOCKET_ERROR )
    {
        CONSOLEDEBUG( TEXT( "listen failed with error: %d\n" ) , WSAGetLastError() );
        closesocket( ListenSocket );
        WSACleanup();

        return 0;
    }

    // Accept a client socket
    while ( !SocketServer->bTakeDown )
    {
        C_SocketHandleClient *HandleClient = new C_SocketHandleClient();

        HandleClient->addr.sa_family = AF_INET;

        HandleClient->Socket = accept( ListenSocket , &HandleClient->addr , &HandleClient->sizeaddr );

        if ( HandleClient->Socket != INVALID_SOCKET )
        {
            HandleClient->RSA_Params.GenerateRandomWithKeySize( HandleClient->RSA_Rng , KEYSIZE );

            HandleClient->RSA_PrivateKeyKeep = HandleClient->RSA_Params;
            HandleClient->RSA_PublicKeyLocal = HandleClient->RSA_PrivateKeyKeep;

            struct sockaddr_in* pV4Addr = ( struct sockaddr_in* )&HandleClient->addr;
            struct in_addr ipAddr = pV4Addr->sin_addr;

            char sIP[ INET_ADDRSTRLEN ];
            inet_ntop( AF_INET , &ipAddr , sIP , INET_ADDRSTRLEN );

            CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "Client: %s Connected\n" ) , AutoConvertS( sIP ) );

            HandleClient->pThread = CreateThread( nullptr , 0
                                                  , ( LPTHREAD_START_ROUTINE ) SocketServer->m_pClientRoutine , HandleClient , 0 , 0 );
        }
        else
        {
            delete HandleClient;
        }
    }

    // No longer need server socket
    closesocket( ListenSocket );
    WSACleanup();

    return 1;
}

bool C_SocketHandleClient::CloseListennerForSocket()
{
    // shutdown the connection since we're done
    int iResult = shutdown( Socket , SD_SEND );

    if ( iResult == SOCKET_ERROR )
    {
        CONSOLEDEBUG( TEXT( "shutdown failed with error: %d\n" ) , WSAGetLastError() );
        closesocket( Socket );;
        return false;
    }

    // cleanup
    closesocket( Socket );

    return true;
}

bool C_SocketHandleClient::SendDataSecure( SocketBuffer *buf )
{
    return SendDataSecureSocket( RSA_PublicKeyRemote , Socket , buf );
}

SocketBuffer* C_SocketHandleClient::RecvDataSecure( size_t SizeOfBuffer )
{
    return RecvDataSecureSocket( RSA_Rng , RSA_PrivateKeyKeep , Socket , SizeOfBuffer );
}

bool C_SocketHandleClient::SendData( SocketBuffer *buf )
{
    return SendDataSocket( Socket , buf );
}

SocketBuffer* C_SocketHandleClient::RecvData( size_t SizeOfBuffer )
{
    return RecvDataSocket( Socket , SizeOfBuffer );
}

bool C_SocketHandleClient::SendPublicKey()
{
    return SendPublicKeySocket( RSA_PublicKeyLocal , Socket );
}

bool C_SocketHandleClient::RecvPublicKey()
{
    return RecvPublicKeySocket( RSA_PublicKeyRemote , Socket );
}