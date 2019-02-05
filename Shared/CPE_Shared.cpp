#include "Includes.hxx"
#include "CPE_Shared.hxx"

/*
const char* C_CurlLib::GetIP()
{
    MemoryStruct *TempMemory = new MemoryStruct();

    CURLcode curl_code = curl_global_init( CURL_GLOBAL_ALL );

    if ( curl_code == CURLE_OK )
    {
        CURL *curl_handle = curl_easy_init();

        // curl_easy_setopt( curl_handle , CURLOPT_VERBOSE , 1L );

        curl_easy_setopt( curl_handle , CURLOPT_URL , "https://xutaxkamay.com/hacks/getip.php" );

        curl_easy_setopt( curl_handle , CURLOPT_WRITEFUNCTION , WriteMemoryCallback );

        curl_easy_setopt( curl_handle , CURLOPT_WRITEDATA , ( void* ) TempMemory );

        curl_easy_setopt( curl_handle , CURLOPT_USERAGENT , "libcurl-agent/1.0" );

        CURLcode res = curl_easy_perform( curl_handle );

        if ( res != CURLcode::CURLE_OK )
        {
            CONSOLEDEBUG( TEXT( "Couldn't retrive IP\n" ) );
        }

        curl_easy_cleanup( curl_handle );

        curl_global_cleanup();

        return ( const char* ) TempMemory->cMemory;
    }
    else
    {
        auto cNoIP = "UNKNOWNIP";
        return cNoIP;
    }
}

size_t C_CurlLib::WriteMemoryCallback( void *contents , size_t size , size_t nmemb , void *userp )
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = ( struct MemoryStruct * )userp;

    mem->cMemory = ( Byte* ) realloc( mem->cMemory , mem->Size + realsize + 1 );

    if ( mem->cMemory == NULL )
    {
        printf( "not enough memory (realloc returned NULL)\n" );
        return 0;
    }

    memcpy( &( mem->cMemory[ mem->Size ] ) , contents , realsize );
    mem->Size += realsize;
    mem->cMemory[ mem->Size ] = 0;

    return realsize;
}

void C_CurlLib::RequestHack( std::string Game , std::string User , std::string Password , std::string HWID )
{
    std::string IP( GetIP() );
    SocketBuffer buf( 0 );

    auto Size = IP.size();

    buf.Add( &Size , sizeof( Size ) );
    buf.Add( IP.data() , Size );

    Size = HWID.size();

    buf.Add( &Size , sizeof( Size ) );
    buf.Add( HWID.data() , Size );

    Size = Password.size();

    buf.Add( &Size , sizeof( Size ) );
    buf.Add( Password.data() , Size );

    Size = User.size();

    buf.Add( &Size , sizeof( Size ) );
    buf.Add( User.data() , Size );

    Size = Game.size();

    buf.Add( &Size , sizeof( Size ) );
    buf.Add( Game.data() , Size );
}

*/