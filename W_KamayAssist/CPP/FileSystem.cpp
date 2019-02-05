#include "Includes.hxx"
#include "Lib.hxx"

// To understand what means "rb" etc : https://msdn.microsoft.com/fr-fr/library/z5hh6ee9.aspx

Pointer N_FileSystem::ReadFile( stdString path , HEX *psize , stdString sFlag )
{
    // Open the file
    FILE* File;
    Open_S( &File , path.c_str() , sFlag.c_str() );

    if ( File == nullptr )
        return nullptr;

    // Get size of the file
    fseek( File , 0 , SEEK_END );
    HEX size = ( HEX ) ftell( File );
    rewind( File );

    // Allocate temp memory for our file
    Pointer pTemp = Alloc( size );

    fread_s( pTemp , size , 1 , size , File );
    fclose( File );

    if ( psize != nullptr )
    {
        *psize = size;
    }

    return pTemp;
}

void N_FileSystem::WriteFile( stdString path , std::vector<Byte> bytes , stdString sFlag )
{
    FILE* File;
    Open_S( &File , path.c_str() , sFlag.c_str() );

    if ( File == nullptr )
        return;

    fwrite( bytes.data() , sizeof( Byte ) , bytes.size() , File );

    fclose( File );
}

void N_FileSystem::WriteFile( stdString path , stdString sString , stdString sFlag )
{
    FILE* File;
    Open_S( &File , path.c_str() , sFlag.c_str() );

    if ( File == nullptr )
        return;

    fwrite( sString.data() , sizeof( String ) , sString.size() , File );

    fclose( File );
}

void N_FileSystem::WriteFile( stdString path , Pointer pAddress , HEX HexSize , stdString sFlag )
{
    FILE* File;
    Open_S( &File , path.c_str() , sFlag.c_str() );

    if ( File == nullptr )
        return;

    fwrite( pAddress , sizeof( Byte ) , HexSize , File );

    fclose( File );
}

void N_FileSystem::ClearFile( stdString path )
{
    FILE* File;
    Open_S( &File , path.c_str() , TEXT( "w" ) );

    if ( File == nullptr )
        return;

    fclose( File );
}

bool N_FileSystem::CreateFolder( stdString path )
{
    uHEX32 hResult = SHCreateDirectoryEx( 0 , path.c_str() , 0 );

    return hResult == ERROR_SUCCESS || hResult == ERROR_ALREADY_EXISTS;
}