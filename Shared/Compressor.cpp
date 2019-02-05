#include "Includes.hxx"
#include "Compressor.hxx"

SocketBuffer *C_Compressor::Decompress( SocketBuffer& buf )
{
    CryptoPP::ZlibDecompressor ZDecompressed;
    ZDecompressed.PutModifiable( buf.m_pData , buf.m_Size );
    ZDecompressed.MessageEnd();

    SocketBuffer *bufDecompressed = new SocketBuffer( ( size_t ) ZDecompressed.MaxRetrievable() );
    bufDecompressed->m_Size = ZDecompressed.Get( bufDecompressed->m_pData , bufDecompressed->m_Size );

    /*
    CryptoPP::SecByteBlock Block( bKey.m_pData , bKey.m_Size );
    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption cfbDecryption( Block , Block.size() , IV );
    cfbDecryption.ProcessData( bufDecompressed.m_pData , bufDecompressed.m_pData , bufDecompressed.m_Size );

    CryptoPP::ZlibDecompressor ZreDecompressed;
    ZreDecompressed.PutModifiable( bufDecompressed.m_pData , bufDecompressed.m_Size );
    ZreDecompressed.MessageEnd();

    SocketBuffer *bufFullyCompressed = new SocketBuffer( ( size_t ) ZreDecompressed.MaxRetrievable() );

    bufFullyCompressed->m_Size = ZreDecompressed.Get( bufFullyCompressed->m_pData , bufFullyCompressed->m_Size );

    return bufFullyCompressed;
    */

    return bufDecompressed;
}

SocketBuffer *C_Compressor::Compress( SocketBuffer& buf )
{
    CryptoPP::ZlibCompressor ZCompressed;
    ZCompressed.SetDeflateLevel( CryptoPP::Deflator::MAX_DEFLATE_LEVEL );
    ZCompressed.PutModifiable( buf.m_pData , buf.m_Size );
    ZCompressed.MessageEnd();

    SocketBuffer *bufCompressed = new SocketBuffer( ( size_t ) ZCompressed.MaxRetrievable() );

    bufCompressed->m_Size = ZCompressed.Get( bufCompressed->m_pData , bufCompressed->m_Size );

    /*CryptoPP::SecByteBlock Block( bKey.m_pData , bKey.m_Size );
    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cfbEncryption( Block , Block.size() , IV );
    cfbEncryption.ProcessData( bufCompressed.m_pData , bufCompressed.m_pData , bufCompressed.m_Size );

    CryptoPP::ZlibCompressor ZreCompressed;
    ZreCompressed.SetDeflateLevel( CryptoPP::Deflator::MAX_DEFLATE_LEVEL );
    ZreCompressed.PutModifiable( bufCompressed.m_pData , bufCompressed.m_Size );
    ZreCompressed.MessageEnd();

    SocketBuffer *bufreCompressed = new SocketBuffer( ( size_t ) ZreCompressed.MaxRetrievable() );
    bufreCompressed->m_Size = ZreCompressed.Get( bufreCompressed->m_pData , bufreCompressed->m_Size );

    return bufreCompressed;
    */

    return bufCompressed;
}