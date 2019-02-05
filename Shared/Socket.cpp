#include "Includes.hxx"
#include "Socket.hxx"

bool SendDataSecureSocket( CryptoPP::RSA::PublicKey &RSA_PublicKey , SOCKET &Socket , SocketBuffer *buf )
{
    SocketBuffer *Compressed = C_Compressor::Compress( *buf );

    SocketBuffer *Key = C_Encryptor::GenKey();
    SocketBuffer *IV = C_Encryptor::GenIV();

    CryptoPP::SecByteBlock Block( Key->m_pData , Key->m_Size );
    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cfbEncryption( Block , Block.size() , IV->m_pData );
    cfbEncryption.ProcessData( Compressed->m_pData , Compressed->m_pData , Compressed->m_Size );

    SocketBuffer AESKey( 0 );

    AESKey.AddVar<Type_Array>( Key->m_pData , Key->m_Size );
    AESKey.AddVar<Type_Array>( IV->m_pData , IV->m_Size );

    CryptoPP::Integer Integer( AESKey.m_pData , AESKey.m_Size );
    CryptoPP::Integer IntegerApplied = RSA_PublicKey.ApplyFunction( Integer );
    SocketBuffer AESKeyEncrypted( IntegerApplied.MinEncodedSize() );
    IntegerApplied.Encode( AESKeyEncrypted.m_pData , AESKeyEncrypted.m_Size );

    SocketBuffer FinalBuffer( 0 );

    FinalBuffer.AddVar<Type_Array>( Compressed->m_pData , Compressed->m_Size );
    FinalBuffer.AddVar<Type_Array>( AESKeyEncrypted.m_pData , AESKeyEncrypted.m_Size );

    delete Compressed;
    delete IV;
    delete Key;

    return SendDataSocket( Socket , &FinalBuffer );
}

SocketBuffer* RecvDataSecureSocket( CryptoPP::AutoSeededRandomPool &RSA_Rng , CryptoPP::RSA::PrivateKey &RSA_PrivateKey , SOCKET &Socket , size_t SizeOfBuffer )
{
    SocketBuffer* Recv = RecvDataSocket( Socket , SizeOfBuffer );

    if ( Recv == nullptr )
    {
        delete Recv;
        return nullptr;
    }

    size_t SizeOfCompressedData = 0;
    auto Compressed = Recv->ReadVar<Type_Array>( &SizeOfCompressedData );

    SocketBuffer SockerCompressed( Compressed , SizeOfCompressedData );

    size_t SizeOfAESKeyEncrypted = 0;
    auto AESKeyEncrypted = Recv->ReadVar<Type_Array>( &SizeOfAESKeyEncrypted );

    CryptoPP::Integer Integer( AESKeyEncrypted , SizeOfAESKeyEncrypted );
    CryptoPP::Integer IntegerApplied = RSA_PrivateKey.CalculateInverse( RSA_Rng , Integer );

    SocketBuffer AESKeyDecrypted( IntegerApplied.MinEncodedSize() );
    IntegerApplied.Encode( AESKeyDecrypted.m_pData , AESKeyDecrypted.m_Size );

    size_t IVSize = 0 , KeySize = 0;
    auto AESKey = AESKeyDecrypted.ReadVar<Type_Array>( &KeySize );
    auto AESIV = AESKeyDecrypted.ReadVar<Type_Array>( &IVSize );

    CryptoPP::SecByteBlock Block( AESKey , KeySize );
    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption cfbDecryption( Block , Block.size() , AESIV );
    cfbDecryption.ProcessData( SockerCompressed.m_pData , SockerCompressed.m_pData , SockerCompressed.m_Size );

    delete Recv;

    return C_Compressor::Decompress( SockerCompressed );
}

bool SendDataSocket( SOCKET &Socket , SocketBuffer *buf )
{
    SocketBuffer* Compressed = C_Compressor::Compress( *buf );

    CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "Sending: 0x%p , size %i\n" ) , Compressed->m_pData , Compressed->m_Size );

    Compressed->AddSignature();

    // Send an initial buffer
    int iResult = send( Socket , ( char* ) Compressed->m_pData , ( int ) Compressed->m_Size , 0 );

    if ( iResult == SOCKET_ERROR )
    {
        delete Compressed;
        CONSOLEDEBUG( TEXT( "send failed with error: %d\n" ) , WSAGetLastError() );
        return false;
    }

    delete Compressed;
    return true;
}

SocketBuffer* RecvDataSocket( SOCKET &Socket , size_t SizeOfBuffer )
{
    // Recv until the peer shuts down the connection
    int iResult = 0;
    SocketBuffer buf( SizeOfBuffer );

    do
    {
        iResult = recv( Socket , ( char* ) buf.m_pData , ( int ) buf.m_Size , 0 );

        if ( iResult < 0 )
        {
            CONSOLEDEBUG( TEXT( "recv failed with error: %d\n" ) , WSAGetLastError() );
            return nullptr;
        }
        else
        {
            if ( iResult == 0 )
            {
                CONSOLEDEBUG( TEXT( "Closing connection..\n" ) );
            }
            else
            {
                CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "Received: 0x%p , size %i\n" ) , buf.m_pData , iResult );
            }

            break;
        }
    }
    while ( true );

    buf.m_Size = iResult;

    if ( buf.ValidMsg() )
    {
        return C_Compressor::Decompress( buf );
    }
    else
    {
        return nullptr;
    }
}

bool SendPublicKeySocket( CryptoPP::RSA::PublicKey &RSA_PublicKey , SOCKET &Socket )
{
    CryptoPP::Integer n = RSA_PublicKey.GetModulus();
    CryptoPP::Integer e = RSA_PublicKey.GetPublicExponent();

    SocketBuffer Exponent( e.MinEncodedSize() );
    SocketBuffer Modulus( n.MinEncodedSize() );

    n.Encode( Modulus.m_pData , Modulus.m_Size );
    e.Encode( Exponent.m_pData , Exponent.m_Size );

    SocketBuffer PublicKey( 0 );
    PublicKey.AddVar<Type_Array>( Modulus.m_pData , Modulus.m_Size );
    PublicKey.AddVar<Type_Array>( Exponent.m_pData , Exponent.m_Size );

    return SendDataSocket( Socket , &PublicKey );
}

bool RecvPublicKeySocket( CryptoPP::RSA::PublicKey &RSA_PublicKey , SOCKET &Socket )
{
    SocketBuffer *PublicKey = RecvDataSocket( Socket , 65536 );

    if ( PublicKey == nullptr )
    {
        return false;
    }

    size_t ModulusSize = 0;
    auto Modulus = PublicKey->ReadVar<Type_Array>( &ModulusSize );

    size_t ExponentSize = 0;
    auto Exponent = PublicKey->ReadVar<Type_Array>( &ExponentSize );

    CryptoPP::Integer e( Exponent , ExponentSize );
    CryptoPP::Integer n( Modulus , ModulusSize );

    RSA_PublicKey.Initialize( n , e );

    delete PublicKey;

    return true;
}

unsigned int C_Encryptor::iSeed = 0;

SocketBuffer* C_Encryptor::GenIV()
{
    SocketBuffer* bIV = new SocketBuffer( IVSize );

    std::srand( ( unsigned int ) std::time( 0 ) + iSeed );

    for ( size_t i = 0; i != IVSize; i++ )
    {
        bIV->m_pData[ i ] = std::rand() % 0x100;
    }

    iSeed++;

    return bIV;
}

SocketBuffer* C_Encryptor::GenKey()
{
    SocketBuffer* bKey = new SocketBuffer( KeySize );

    std::srand( ( unsigned int ) std::time( 0 ) + iSeed );

    for ( size_t i = 0; i != KeySize; i++ )
    {
        bKey->m_pData[ i ] = std::rand() % 0x100;
    }

    iSeed++;

    return bKey;
}