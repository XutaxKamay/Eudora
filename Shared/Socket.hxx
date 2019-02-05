#ifndef _SOCKET
#define _SOCKET
#pragma once

#include "Lib.hxx"
#include "Compressor.hxx"

#define KEYSIZE 0x1000

class C_SocketHandleClient;

typedef DWORD( __stdcall*SocketRoutine )( C_SocketHandleClient* );

SocketBuffer* RecvDataSocket( SOCKET &Socket , size_t SizeOfBuffer );
bool SendDataSocket( SOCKET &Socket , SocketBuffer *buf );
SocketBuffer* RecvDataSecureSocket( CryptoPP::AutoSeededRandomPool &RSA_Rng , CryptoPP::RSA::PrivateKey &RSA_PrivateKey , SOCKET &Socket , size_t SizeOfBuffer );
bool SendDataSecureSocket( CryptoPP::RSA::PublicKey &RSA_PublicKeySend , SOCKET &Socket , SocketBuffer *buf );
bool SendPublicKeySocket( CryptoPP::RSA::PublicKey &RSA_PublicKey , SOCKET &Socket );
bool RecvPublicKeySocket( CryptoPP::RSA::PublicKey &RSA_PublicKey , SOCKET &Socket );

class C_SocketHandleClient
{
public:

    SocketBuffer * RecvData( size_t SizeOfBuffer );
    bool SendData( SocketBuffer *buf );
    SocketBuffer* RecvDataSecure( size_t SizeOfBuffer );
    bool SendDataSecure( SocketBuffer *buf );
    bool CloseListennerForSocket();
    bool SendPublicKey();
    bool RecvPublicKey();

    void DebugKeys()
    {
    #ifndef NODEBUGSTRINGS
        const CryptoPP::Integer& nr = RSA_PublicKeyRemote.GetModulus();
        const CryptoPP::Integer& er = RSA_PublicKeyRemote.GetPublicExponent();

        const CryptoPP::Integer& np = RSA_PrivateKeyKeep.GetModulus();
        const CryptoPP::Integer& epub = RSA_PrivateKeyKeep.GetPublicExponent();
        const CryptoPP::Integer& epriv = RSA_PrivateKeyKeep.GetPrivateExponent();

        std::stringstream snr;
        snr << std::hex << nr;

        std::stringstream ser;
        ser << std::hex << er;

        std::stringstream snp;
        snp << std::hex << np;

        std::stringstream sepub;
        sepub << std::hex << epub;

        std::stringstream sepriv;
        sepriv << std::hex << epriv;

        CONSOLEColorDEBUG( FOREGROUND_ROSE , TEXT( "RSA Remote:\ne: %s\npub: %s\n" ) , AutoConvertS( ser.str().c_str() ) , AutoConvertS( snr.str().c_str() ) );

        CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "RSA Private:\ne: %s\n" ) , AutoConvertS( sepub.str().c_str() ) );
        CONSOLEColorDEBUG( FOREGROUND_WHITE , TEXT( "priv: %s\n" ) , AutoConvertS( sepriv.str().c_str() ) );
        CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "pub: %s\n" ) , AutoConvertS( snp.str().c_str() ) );

    #endif
    }

    SOCKET Socket;
    Pointer pThread;
    sockaddr addr;
    int sizeaddr = sizeof( addr );
    CryptoPP::RSA::PrivateKey RSA_PrivateKeyKeep;
    CryptoPP::RSA::PublicKey RSA_PublicKeyLocal;
    CryptoPP::RSA::PublicKey RSA_PublicKeyRemote;
    CryptoPP::AutoSeededRandomPool RSA_Rng;
    CryptoPP::InvertibleRSAFunction RSA_Params;
};

class C_SocketHandleServer
{
public:

    C_SocketHandleServer( std::string sPort = "443" )
    {
        m_sPort = sPort;
    }

    std::string m_sPort;
};

class C_SocketServer
{
public:

    C_SocketServer()
    {
        m_pClientRoutine = nullptr;
        HandleServer = nullptr;
        m_pMainThread = nullptr;
        bTakeDown = false;
    }

    bool OpenListenner( SocketRoutine pRoutine , std::string sPort = "443" , bool bWaitForMainThread = false );
    static DWORD __stdcall MainSocketThread( C_SocketServer* SocketServer );

    SocketRoutine m_pClientRoutine;
    C_SocketHandleServer *HandleServer;
    Pointer m_pMainThread;
    bool bTakeDown;
};

class C_SocketClient
{
public:

    C_SocketClient( std::string sIP = "127.0.0.1" , std::string sPort = "443" )
    {
        m_sPort = sPort;
        m_sIP = sIP;
    }

    bool OpenConnection();
    SocketBuffer* RecvData( size_t SizeOfBuffer );
    bool SendData( SocketBuffer *buf );
    SocketBuffer* RecvDataSecure( size_t SizeOfBuffer );
    bool SendDataSecure( SocketBuffer *buf );
    bool CloseConnection();
    bool SendPublicKey();
    bool RecvPublicKey();

    void DebugKeys()
    {
    #ifndef NODEBUGSTRINGS
        const CryptoPP::Integer& nr = RSA_PublicKeyRemote.GetModulus();
        const CryptoPP::Integer& er = RSA_PublicKeyRemote.GetPublicExponent();

        const CryptoPP::Integer& np = RSA_PrivateKeyKeep.GetModulus();
        const CryptoPP::Integer& epub = RSA_PrivateKeyKeep.GetPublicExponent();
        const CryptoPP::Integer& epriv = RSA_PrivateKeyKeep.GetPrivateExponent();

        std::stringstream snr;
        snr << std::hex << nr;

        std::stringstream ser;
        ser << std::hex << er;

        std::stringstream snp;
        snp << std::hex << np;

        std::stringstream sepub;
        sepub << std::hex << epub;

        std::stringstream sepriv;
        sepriv << std::hex << epriv;

        CONSOLEColorDEBUG( FOREGROUND_ROSE , TEXT( "RSA Remote:\ne: %s\npub: %s\n" ) , AutoConvertS( ser.str().c_str() ) , AutoConvertS( snr.str().c_str() ) );

        CONSOLEColorDEBUG( FOREGROUND_CYAN , TEXT( "RSA Private:\ne: %s\n" ) , AutoConvertS( sepub.str().c_str() ) );
        CONSOLEColorDEBUG( FOREGROUND_WHITE , TEXT( "priv: %s\n" ) , AutoConvertS( sepriv.str().c_str() ) );
        CONSOLEColorDEBUG( FOREGROUND_GREEN , TEXT( "pub: %s\n" ) , AutoConvertS( snp.str().c_str() ) );

    #endif
    }

    std::string m_sPort , m_sIP;
    SOCKET ConnectSocket = INVALID_SOCKET;
    CryptoPP::RSA::PrivateKey RSA_PrivateKeyKeep;
    CryptoPP::RSA::PublicKey RSA_PublicKeyLocal;
    CryptoPP::RSA::PublicKey RSA_PublicKeyRemote;
    CryptoPP::AutoSeededRandomPool RSA_Rng;
    CryptoPP::InvertibleRSAFunction RSA_Params;
};

class C_Encryptor
{
public:
    static SocketBuffer* GenIV();
    static SocketBuffer* GenKey();
    static constexpr size_t IVSize = CryptoPP::AES::BLOCKSIZE;
    static constexpr size_t KeySize = CryptoPP::AES::MAX_KEYLENGTH;
    static unsigned int iSeed;
};

#endif