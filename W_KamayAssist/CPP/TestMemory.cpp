#include "Includes.hxx"
#include "Lib.hxx"

int WINAPI wWinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , PWSTR pCmdLine , int nCmdShow )
{
	N_Console::Open();

	N_Console::Print( TEXT( "%p %p %p %p\n" ) , hInstance , hPrevInstance , pCmdLine , nCmdShow );

	auto pText = TEXT( "THIS PROGRAM SUCKS." );
	HEX Size = StrLen( pText ) * sizeof( String );
	N_Process::Process *pProcess = new N_Process::Process( ( Pointer ) GetCurrentProcess() );

	if ( pProcess->pProcess == nullptr )
		return 0;

	N_VirtualMemory::VirtualBuffer pVRemotedPathToDll = N_VirtualMemory::VirtualBuffer( ( HEX ) Size ,
																						PAGE_EXECUTE_READWRITE
																						, nullptr , pProcess->pProcess , TEXT( "pVRemotedPathToDll" ) );
	pVRemotedPathToDll.WriteToProcessFromCurrent( ( Pointer ) pText , Size );

	N_VirtualMemory::VirtualBuffer pVPathToDll = N_VirtualMemory::VirtualBuffer();

	if ( ( pVPathToDll = &pVRemotedPathToDll ) )
	{
		if ( pVPathToDll == &pVRemotedPathToDll )
		{
			N_Console::Print<FOREGROUND_CYAN>( TEXT( "Same bytes1\n" ) );
		}
		else
		{
			N_Console::Print<FOREGROUND_CYAN>( TEXT( "Not same bytes1\n" ) );
		}

		if ( ( pVPathToDll += &pVRemotedPathToDll ) )
		{
			pVPathToDll.PrintBytes();

			if ( pVPathToDll == &pVRemotedPathToDll )
			{
				N_Console::Print<FOREGROUND_CYAN>( TEXT( "Same bytes2\n" ) );
			}
			else
			{
				N_Console::Print<FOREGROUND_CYAN>( TEXT( "Not same bytes2\n" ) );
			}

			pVPathToDll.TransferToProcess();

			if ( pVPathToDll.pProcess == GetCurrentProcess() )
			{
				pVPathToDll.TransferToProcess( pVRemotedPathToDll.pProcess );

				N_Console::Print<FOREGROUND_CYAN>( TEXT( "Successfully transfered twice!\n" ) );

				pVPathToDll.PrintBytes();

				if ( pVPathToDll == &pVRemotedPathToDll )
				{
					N_Console::Print<FOREGROUND_CYAN>( TEXT( "Same bytes2\n" ) );
				}
				else
				{
					N_Console::Print<FOREGROUND_CYAN>( TEXT( "Not same bytes2\n" ) );
				}

				if ( ( pVPathToDll -= Size ) )
				{
					pVPathToDll.PrintBytes();

					pVPathToDll += stdString( TEXT( "." ) );
					pVPathToDll += std::vector<Byte>{ 0x53 , 0x8 };
					pVPathToDll -= stdString( TEXT( "." ) );
					pVPathToDll -= std::vector<Byte>{ 0x53 , 0x8 };

					if ( pVRemotedPathToDll.Find( &pVPathToDll ) != -1 )
					{
						N_Console::Print<FOREGROUND_CYAN>( TEXT( "Found pVPathToDll\n" ) );

						const String* sHello = TEXT( "Hello" );

						pVRemotedPathToDll += sHello;

						N_VirtualMemory::VirtualBuffer pTempTest( pVRemotedPathToDll.pAddress , pVRemotedPathToDll.HexSize , pVRemotedPathToDll.Flags );
						pTempTest[ 6 ] = 0x53;

						if ( pVRemotedPathToDll -= &pVPathToDll )
						{
							pVRemotedPathToDll[ 5 ] = 0x53;

							pVRemotedPathToDll.PrintBytes();
						}

						SigScanningFile *SigScan = new SigScanningFile( ( Pointer ) GetCurrentProcess() );

						SigScan->Scan( std::vector<Byte>{ 0x8B , 0xFF , 0x55 , 0x8B , 0xEC , 0x51 , 0xA1 , 0x10 , 0x01 , 0x8A , 0x6B , 0x33 , 0xC5 , 0x89 , 0x45 , 0xFC ,
									   0x8B , 0x45 , 0x28 , 0x53 , 0x56 , 0x57 , 0x85 , 0xC0 , 0x74 , 0x65 , 0x8B , 0x4D , 0x0C , 0x8B , 0x7D , 0x20 ,
									   0x8B , 0x5D , 0x1C , 0x8B , 0x55 , 0x10 , 0x83 , 0xE9 , 0x00 , 0x74 , 0x2A , 0x83 , 0xE9 , 0x01 , 0x75 , 0x28 } ); //KERNEL32.dll @ __TlgEnableCallback.

						SigScan->PrintAllOffsets();
					}
				}
			}
		}
	}

	while ( true )
	{
	}

	delete pProcess;
	N_Console::Pause();

	return 1;
}