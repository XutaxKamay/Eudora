#ifndef FILESYSTEM
#define FILESYSTEM
#pragma once

#define FRAGMENT_BITS		8
#define FRAGMENT_SIZE		(1<<FRAGMENT_BITS)
#define MAX_FILE_SIZE_BITS	26
#define MAX_FILE_SIZE		((1<<MAX_FILE_SIZE_BITS)-1)	// maximum transferable size is	64MB
#define BYTES2FRAGMENTS(i) ((i+FRAGMENT_SIZE-1)/FRAGMENT_SIZE)
#define FILESYSTEM_INVALID_HANDLE	( FileHandle_t )0

enum FileSystemSeek_t
{
    FILESYSTEM_SEEK_HEAD = SEEK_SET ,
    FILESYSTEM_SEEK_CURRENT = SEEK_CUR ,
    FILESYSTEM_SEEK_TAIL = SEEK_END ,
};

typedef Pointer FileHandle_t;

//-----------------------------------------------------------------------------
// File system allocation functions. Client must free on failure
//-----------------------------------------------------------------------------
typedef void *( *FSAllocFunc_t )( const char *pszFilename , unsigned nBytes );

//-----------------------------------------------------------------------------
// Used to display dirty disk error functions
//-----------------------------------------------------------------------------
typedef void( *FSDirtyDiskReportFunc_t )( );

typedef struct dataFragments_s
{
    FileHandle_t	file;			// open file handle
    char			filename[ MAX_PATH ]; // filename
    char*			buffer;			// if NULL it's a file
    unsigned int	bytes;			// size in bytes
    unsigned int	bits;			// size in bits
    unsigned int	transferID;		// only for files
    bool			isCompressed;	// true if data is bzip compressed
    unsigned int	nUncompressedSize; // full size in bytes
    bool			asTCP;			// send as TCP stream
    bool            isDemo;         // is demo?
    int				numFragments;	// number of total fragments
    int				ackedFragments; // number of fragments send & acknowledged
    int				pendingFragments; // number of fragments send, but not acknowledged yet
} dataFragments_t;

class IBaseFileSystem
{
public:
    virtual int				Read( void* pOutput , int size , FileHandle_t file ) = 0;
    virtual int				Write( void const* pInput , int size , FileHandle_t file ) = 0;

    // if pathID is NULL, all paths will be searched for the file
    virtual FileHandle_t	Open( const char *pFileName , const char *pOptions , const char *pathID = 0 ) = 0;
    virtual void			Close( FileHandle_t file ) = 0;

    virtual void			Seek( FileHandle_t file , int pos , FileSystemSeek_t seekType ) = 0;
    virtual unsigned int	Tell( FileHandle_t file ) = 0;
    virtual unsigned int	Size( FileHandle_t file ) = 0;
    virtual unsigned int	Size( const char *pFileName , const char *pPathID = 0 ) = 0;

    virtual void			Flush( FileHandle_t file ) = 0;
    virtual bool			Precache( const char *pFileName , const char *pPathID = 0 ) = 0;

    virtual bool			FileExists( const char *pFileName , const char *pPathID = 0 ) = 0;
    virtual bool			IsFileWritable( char const *pFileName , const char *pPathID = 0 ) = 0;
    virtual bool			SetFileWritable( char const *pFileName , bool writable , const char *pPathID = 0 ) = 0;

    virtual long			GetFileTime( const char *pFileName , const char *pPathID = 0 ) = 0;

    //--------------------------------------------------------
    // Reads/writes files to utlbuffers. Use this for optimal read performance when doing open/read/close
    //--------------------------------------------------------
    virtual bool			ReadFile( const char *pFileName , const char *pPath , CUtlBuffer &buf , int nMaxBytes = 0 , int nStartingByte = 0 , FSAllocFunc_t pfnAlloc = NULL ) = 0;
    virtual bool			WriteFile( const char *pFileName , const char *pPath , CUtlBuffer &buf ) = 0;
    virtual bool			UnzipFile( const char *pFileName , const char *pPath , const char *pDestination ) = 0;
};

#endif