#ifndef _CENCRYPT
#define _CENCRYPT
#pragma once

#include "CPE_Shared.hxx"

class C_Compressor
{
public:
    static SocketBuffer* Compress( SocketBuffer &bBuffer );
    static SocketBuffer* Decompress( SocketBuffer &bBuffer );

    /*
    static SocketBuffer* GenIV();
    static SocketBuffer* GenKey();
    static constexpr size_t IVSize = CryptoPP::AES::BLOCKSIZE;
    static constexpr size_t KeySize = CryptoPP::AES::MAX_KEYLENGTH;
    static unsigned int iSeed;
    */
};

#endif