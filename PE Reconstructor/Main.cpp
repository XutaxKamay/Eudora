#include "Includes.hxx"
#include "CPE.hxx"

int WINAPI wWinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , PWSTR pCmdLine , int nCmdShow )
{
    Buffer<Byte> BufferKey( CryptoPP::AES::MAX_KEYLENGTH );
    char test[] = "1323";
    BufferKey.Copy( test , sizeof( test ) );

    N_Console::Open();

    N_Process::Process CurProcess( GetCurrentProcess() );
    CurProcess.SetAllAccess();

    N_Process::Process Process( N_Console::Input<FOREGROUND_WHITE>( TEXT( "Process name?\n" ) ) );

    if ( Process.pAddress == nullptr )
        goto Pause;

    int iArgs;
    wchar_t** listArgs = CommandLineToArgvW( pCmdLine , &iArgs );

#ifdef _DEBUG
    Process.ForceLoadLibrary( AutoConvertW( listArgs[ 0 ] ) );
#else
    {
        HEX Size;
        auto pDosHeader = ( PIMAGE_DOS_HEADER ) N_FileSystem::ReadFile( AutoConvertW( listArgs[ 0 ] ) , &Size );

        auto CPE = g_CConstructPE.Reconstruct( pDosHeader );

        if ( CPE != nullptr )
        {
            N_VirtualMemory::VirtualBuffer pNewImage( CPE->m_ImageSize , PAGE_EXECUTE_READWRITE , CPE->m_pImageBase , Process.pProcess );

            if ( CPE->ProcessImports( &Process )
                 && CPE->RelocateSections( pNewImage.pAddress ) == CPE_Relocated
                 && CPE->CopySections( pNewImage )
                 && CPE->ProcessStaticTls( pNewImage , &Process )
                 && CPE->CallTlsCBs( pNewImage , &Process )
                 && CPE->CallRoutine( pNewImage , &Process )
                 && CPE->FreeRoutine( pNewImage , &Process )
                 && CPE->EndTlsCBs( pNewImage , &Process ) )
            {
                N_Console::Print<FOREGROUND_GREEN>( TEXT( "Successful processing!\n" ) );
            }

            pNewImage.Free();
        }
    }
#endif

Pause:

    N_Console::Pause();

    return 1;
}