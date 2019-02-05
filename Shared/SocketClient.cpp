#include "Includes.hxx"
#include "Socket.hxx"

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms737889(v=vs.85).aspx

bool C_SocketClient::CloseConnection()
{
    // shutdown the connection since no more data will be sent
    int iResult = shutdown( ConnectSocket , SD_SEND );

    if ( iResult == SOCKET_ERROR )
    {
        CONSOLEDEBUG( TEXT( "shutdown failed with error: %d\n" ) , WSAGetLastError() );
        closesocket( ConnectSocket );
        WSACleanup();
        return false;
    }

    // cleanup
    closesocket( ConnectSocket );
    WSACleanup();

    return true;
}

bool C_SocketClient::OpenConnection()
{
    WSADATA wsaData;

    // Initialize Winsock
    int iResult = WSAStartup( MAKEWORD( 2 , 2 ) , &wsaData );

    if ( iResult != 0 )
    {
        CONSOLEDEBUG( TEXT( "WSAStartup failed with error: %d\n" ) , iResult );
        return false;
    }

    struct addrinfo hints;
    ZeroMemory( &hints , sizeof( hints ) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    struct addrinfo *result = nullptr;

    // Resolve the server address and port
    iResult = getaddrinfo( m_sIP.c_str() , m_sPort.c_str() , &hints , &result );

    if ( iResult != 0 )
    {
        CONSOLEDEBUG( TEXT( "getaddrinfo failed with error: %d\n" ) , iResult );
        WSACleanup();
        return false;
    }

    // Attempt to connect to an address until one succeeds
    for ( struct addrinfo* ptr = result; ptr != nullptr; ptr = ptr->ai_next )
    {
        // Create a SOCKET for connecting to server
        ConnectSocket = socket( ptr->ai_family , ptr->ai_socktype , ptr->ai_protocol );

        if ( ConnectSocket == INVALID_SOCKET )
        {
            CONSOLEDEBUG( TEXT( "socket failed with error: %ld\n" ) , WSAGetLastError() );
            WSACleanup();
            return false;
        }

        // Connect to server.
        iResult = connect( ConnectSocket , ptr->ai_addr , ( int ) ptr->ai_addrlen );

        if ( iResult == SOCKET_ERROR )
        {
            closesocket( ConnectSocket );
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo( result );

    if ( ConnectSocket == INVALID_SOCKET )
    {
        CONSOLEDEBUG( TEXT( "Unable to connect to server!\n" ) );
        WSACleanup();
        return false;
    }

    RSA_Params.GenerateRandomWithKeySize( RSA_Rng , KEYSIZE );

    RSA_PrivateKeyKeep = RSA_Params;
    RSA_PublicKeyLocal = RSA_PrivateKeyKeep;

    return true;
}

bool C_SocketClient::SendDataSecure( SocketBuffer *buf )
{
    return SendDataSecureSocket( RSA_PublicKeyRemote , ConnectSocket , buf );
}

SocketBuffer* C_SocketClient::RecvDataSecure( size_t SizeOfBuffer )
{
    return RecvDataSecureSocket( RSA_Rng , RSA_PrivateKeyKeep , ConnectSocket , SizeOfBuffer );
}

bool C_SocketClient::SendData( SocketBuffer *buf )
{
    return SendDataSocket( ConnectSocket , buf );
}

SocketBuffer* C_SocketClient::RecvData( size_t SizeOfBuffer )
{
    return RecvDataSocket( ConnectSocket , SizeOfBuffer );
}

bool C_SocketClient::SendPublicKey()
{
    return SendPublicKeySocket( RSA_PublicKeyLocal , ConnectSocket );
}

bool C_SocketClient::RecvPublicKey()
{
    return RecvPublicKeySocket( RSA_PublicKeyRemote , ConnectSocket );
}