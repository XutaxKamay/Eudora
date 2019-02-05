#include "Includes.hxx"
#include "Main.hxx"
#include <direct.h>

OffsetsManager *Offsets = nullptr;
NetVarsManager *NetVars = nullptr;

bool bWasInNetVarConstructor = false;

void NetVarsManager::MakeHeader()
{
	sBufferIncludeAllHeaders.clear();
	sBufferGeneratedHeader.clear();

	// Get all classes of networked variables.
	ClientClass *CClass = BaseClient->GetAllClasses();
	sBufferIncludeAllHeaders = TEXT( "#ifndef SDK_GENERATOR\n" );
	sBufferIncludeAllHeaders += TEXT( "#define SDK_GENERATOR\n\n" );
	sBufferIncludeAllHeaders += TEXT( "#pragma once\n\n" );

	while ( CClass != nullptr )
	{
		bWasInNetVarConstructor = false;

		sBufferGeneratedHeader += TEXT( "///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.\n" );

		// Generate class name.
		GenerateStringHeader( TEXT( "\n#ifndef SDK_%s\n#define SDK_%s\n#pragma once\n\nclass %s\n{\n public:\n" ) , AutoConvertS( CClass->m_pNetworkName )
							  , AutoConvertS( CClass->m_pNetworkName )
							  , AutoConvertS( CClass->m_pNetworkName ) );

		// Generate all networked variables.
		if ( CClass->m_pRecvTable != nullptr )
			MakeHeaderProps( CClass->m_pRecvTable );

		// Generate end class name.
		GenerateStringHeader( TEXT( "};\n\n#endif\n" ) );

		String sBuf[ 0xFF ];
		CopyString( sBuf , sizeof( sBuf ) , AutoConvertS( CClass->m_pNetworkName ) );
		WriteFileHeader( sBuf );

		sBufferGeneratedHeader.clear();

		sBufferIncludeAllHeaders += TEXT( "#include \"" ) + stdString( AutoConvertS( CClass->m_pNetworkName ) ) + TEXT( ".hxx\"\n" );

		// Go on the next class.
		CClass = CClass->m_pNext;
	}

	sBufferIncludeAllHeaders += TEXT( "\n#endif" );

	String ModulePath[ MAX_PATH ];
	GetModuleFileName( 0 , ModulePath , MAX_PATH );
	ModulePath[ StrLen( ModulePath ) - 4 ] = 0;
	StrCat_S( ModulePath , MAX_PATH , TEXT( "_GeneratedSDK\\" ) );
	StrCat_S( ModulePath , MAX_PATH , TEXT( "SDKGen.hxx" ) );

	N_FileSystem::ClearFile( ModulePath );
	N_FileSystem::WriteFile( ModulePath , sBufferIncludeAllHeaders.c_str() );
}

void NetVarsManager::MakeHeaderConstructNetVar( stdString sName , int iOffset , stdString sBufferBack )
{
	// Useless netvar.
	if ( iOffset == 0 )
		return;

	if ( StrHasOnlyDigits( sName ) )
	{
		sName = TEXT( "_" ) + sName;
	}
	else
	{
		// Now let's make the c++ compiler able to read the networked variables header, if you don't want to end up with big errors when you compile...
		int iPos;

		// Replace [ by _.
		while ( true )
		{
			iPos = sName.find( TEXT( "[" ) );

			if ( iPos != stdString::npos )
			{
				sName[ iPos ] = TEXT( '_' );
			}
			else
			{
				break;
			}
		}

		// delete ] from networked variables
		while ( true )
		{
			iPos = sName.find( TEXT( "]" ) );

			if ( iPos != stdString::npos )
			{
				sName.erase( iPos );
			}
			else
			{
				break;
			}
		}

		// delete . from networked variables.
		while ( true )
		{
			iPos = sName.find( TEXT( "." ) );

			if ( iPos != stdString::npos )
			{
				sName[ iPos ] = TEXT( '_' );
			}
			else
			{
				break;
			}
		}

		// delete " from networked variables.
		while ( true )
		{
			iPos = sName.find( TEXT( "\"" ) );

			if ( iPos != stdString::npos )
			{
				sName[ iPos ] = TEXT( '_' );
			}
			else
			{
				break;
			}
		}

		// delete m_ from networked variables (Useless and it can be confusing in a c++ header).
		while ( true )
		{
			iPos = sName.find( TEXT( "m_" ) );

			if ( iPos != stdString::npos )
			{
				sName.erase( iPos , 2 );
			}
			else
			{
				break;
			}
		}
	}

	GenerateStringHeader( TEXT( "\n%s   template<typename T = unsigned long> __forceinline static T %s() { return ( T ) 0x%X; }" ) , sBufferBack.c_str() , sName.c_str() , iOffset );

	bWasInNetVarConstructor = true;
}

void NetVarsManager::MakeHeaderProps( RecvTable* RTable , int iLastOffset , stdString sPrevNetVar )
{
	// Check if there is networked variables (Props) into the table.
	if ( RTable->m_nProps > 0 && RTable->m_pProps != nullptr )
	{
		if ( bWasInNetVarConstructor )
		{
			GenerateStringHeader( TEXT( "\n" ) );
			bWasInNetVarConstructor = false;
		}

		iCountChildTables++;

		stdString sBufferBack;

		int i = 0;
		while ( i != iCountChildTables )
		{
			sBufferBack += TEXT( "   " );
			i++;
		}

		if ( sPrevNetVar.empty() || !StrHasOnlyDigits( sPrevNetVar ) ) // I wonder if we should really ignore these... Because their last offsets is always 0.
			GenerateStringHeader( TEXT( "\n%sclass %s\n%s{\n %spublic:\n" ) , sBufferBack.c_str() , AutoConvertS( RTable->m_pNetTableName )
								  , sBufferBack.c_str() , sBufferBack.c_str() );
		else
			GenerateStringHeader( TEXT( "\n%sclass %s\n%s{\n %spublic:\n" ) , sBufferBack.c_str()
								  , stdString( stdString( AutoConvertS( RTable->m_pNetTableName ) ) + TEXT( "_" ) + sPrevNetVar ).c_str() , sBufferBack.c_str() , sBufferBack.c_str() );

		// Iterate through all networked variables.
		for ( int iProp = 0; iProp < RTable->m_nProps; iProp++ )
		{
			RecvProp *recvProp = &RTable->m_pProps[ iProp ];

			if ( recvProp->m_pDataTable != nullptr )
			{
				MakeHeaderProps( recvProp->m_pDataTable , recvProp->m_Offset + iLastOffset , AutoConvertS( recvProp->m_pVarName ) );
			}
			else
			{
				MakeHeaderConstructNetVar( AutoConvertS( recvProp->m_pVarName ) , recvProp->m_Offset + iLastOffset , sBufferBack.c_str() );
			}

			if ( recvProp->m_pExtraData != nullptr )
			{
				if ( StrHasOnlyDigits( AutoConvertS( recvProp->m_pVarName ) ) )
				{
					MakeHeaderConstructNetVar( stdString( AutoConvertS( RTable->m_pNetTableName ) ) + TEXT( "_" ) + AutoConvertS( recvProp->m_pVarName ) , iLastOffset , sBufferBack.c_str() );
				}

				iLastOffset += ( ( CRecvPropExtra_UtlVector* ) recvProp->m_pExtraData )->m_Offset;
			}
		}

		if ( bWasInNetVarConstructor )
		{
			GenerateStringHeader( TEXT( "\n" ) );
			bWasInNetVarConstructor = false;
		}

		GenerateStringHeader( TEXT( "%s};\n" ) , sBufferBack.c_str() );

		iCountChildTables--;
	}
}

void NetVarsManager::GenerateStringHeader( const String* sMessage , ... )
{
	va_list list;
	va_start( list , sMessage );
	String sBuffer[ UNICODE_STRING_MAX_CHARS ];
	SPrintf_S( sBuffer , UNICODE_STRING_MAX_CHARS , sMessage , list );
	va_end( list );

	sBufferGeneratedHeader += sBuffer;
}

void NetVarsManager::WriteFileHeader( String* sName )
{
	String ModulePath[ MAX_PATH ];
	GetModuleFileName( 0 , ModulePath , MAX_PATH );
	ModulePath[ StrLen( ModulePath ) - 4 ] = 0;
	StrCat_S( ModulePath , MAX_PATH , TEXT( "_GeneratedSDK\\" ) );

	if ( !bCreateOnceFolder )
	{
		_mkdir( AutoConvertC( ModulePath ) );
		bCreateOnceFolder = true;
	}

	StrCat_S( ModulePath , MAX_PATH , sName );
	StrCat_S( ModulePath , MAX_PATH , TEXT( ".hxx" ) );

	N_FileSystem::ClearFile( ModulePath );
	N_FileSystem::WriteFile( ModulePath , sBufferGeneratedHeader.c_str() );
}

OffsetsManager::OffsetsManager()
{
	/*

	StringRef: (mapname)

	.text:10230D69 A1 20 7C ED 14                                mov     eax, dword_14ED7C20
	.text:10230D6E B9 20 7C ED 14                                mov     ecx, offset dword_14ED7C20
	.text:10230D73 57                                            push    edi
	.text:10230D74 FF 90 C0 00 00 00                             call    dword ptr [eax+0C0h]
	dword_14ED7C20 = CInput

	*/

	SigScanningFile SigScan = Scan( { 0x57 , 0xFF , 0x90 , 0xC0 , 0x00 , 0x00 , 0x00 , 0xA1 , 0x50 , 0xA8 , 0xAB , 0x10 }
	, TEXT( "pInput" ) , TEXT( "client.dll" ) );

	if ( SigScan.pFirstOffset != nullptr )
	{
		Pointer pInput = *( pPointer ) ( ( HEX ) SigScan.pFirstOffset - sizeof( HEX ) );
		Input = *new Interface<CInput>( pInput , AutoConvertC( TEXT( "Input" ) ) , TEXT( "client.dll" ) );
	}

	/*

	Ref: String: overflow buffer -> first xref -> xref of function -> goto third virtual function from table.

	.text:10295990 55                                            push    ebp
	.text:10295991 8B EC                                         mov     ebp, esp
	.text:10295993                               ; 2:   if ( this != a2 )
	.text:10295993 8B 55 08                                      mov     edx, [ebp+arg_0]
	.text:10295996 3B CA                                         cmp     ecx, edx
	.text:10295998 0F 84 9C 00 00 00                             jz      loc_10295A3A
	.text:1029599E                               ; 4:     *(_DWORD *)(this + 4) = *(_DWORD *)(a2 + 4);

	*/

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x8B , 0x55 , 0x08 , 0x3B , 0xCA , 0x0F , 0x84 , 0x9C , 0x00 , 0x00 , 0x00 , 0x8B , 0x42 , 0x04 , 0x89 , 0x41
					, 0x04 , 0x8B , 0x42 , 0x08 , 0x89 , 0x41 , 0x08 , 0x8B , 0x42 , 0x0C , 0x89 , 0x41 , 0x0C }
	, TEXT( "CUserCmdOverLoadedEqual" ) , TEXT( "client.dll" ) );

	CUserCmdOverLoadedEqual = ( CUserCmd*( __thiscall* )( CUserCmd* ) )SigScan.pFirstOffset;

	SigScan = Scan( { 0x8B , 0xCF , 0xE8 , 0xE0 , 0x0C , 0x00 , 0x00 , 0x5F , 0x89
					, 0x46 , 0x64 , 0x5E , 0x5B , 0x8B , 0xE5 , 0x5D , 0xC2 , 0x0C , 0x00 , 0xCC , 0xCC , 0xCC , 0xCC }
	, TEXT( "pCUserCmdOverLoadedEqual_ReturnAddress_CreateMove" ) , TEXT( "client.dll" ) );

	pCUserCmdOverLoadedEqual_ReturnAddress_CreateMove = SigScan.pFirstOffset;

	SigScan = Scan( { 0x5E , 0x8B , 0x40 , 0x10 , 0x89 , 0x83 , 0x24 , 0x01 , 0x00 , 0x00 , 0x5F , 0x5B , 0x8B , 0xE5 , 0x5D , 0xC3 } , TEXT( "Globals" ) , TEXT( "client.dll" ) );

	if ( SigScan.pFirstOffset != nullptr )
	{
		Pointer pGlobals = *( pPointer ) ( *( pPointer ) ( ( HEX ) SigScan.pFirstOffset - sizeof( HEX ) ) );
		Globals = *new Interface<CGlobalVars>( pGlobals , AutoConvertC( TEXT( "Globals" ) ) , TEXT( "client.dll" ) );

		N_Console::Print<FOREGROUND_BLUE>( TEXT( "Globals test: %f\n" ) , Globals->interval_per_tick );
	}

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x57 , 0x8B , 0xF9 , 0x8B , 0x97 , 0x7C , 0x29 , 0x00 , 0x00 , 0x85 , 0xD2 , 0x75 , 0x07 }
	, TEXT( "C_BaseAnimatingOverlay_GetAnimLayer" ) , TEXT( "client.dll" ) );

	C_BaseAnimatingOverlay_GetAnimLayer = ( Pointer( __thiscall* )( Pointer , int , char ) )SigScan.pFirstOffset;

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x51 , 0x8B , 0x45 , 0x14 , 0x56 , 0x8B , 0xF1 , 0xC7 , 0x00 , 0x01 , 0x00 , 0x00 , 0x00 }
	, TEXT( "pC_BaseEntity_BaseInterpolate1" ) , TEXT( "client.dll" ) );

	pC_BaseEntity_BaseInterpolate1 = SigScan.pFirstOffset;

	SigScan = Scan( { 0x82 , 0x85 , 0xA6 , 0x10 , 0x33 , 0xC9 , 0xD9 , 0x5D , 0xF8 , 0xF3 , 0x0F , 0x10 , 0x45 , 0xF8 }
	, TEXT( "pbShouldInterpolate" ) , TEXT( "client.dll" ) );

	if ( SigScan.pFirstOffset != nullptr )
	{
		Pointer pShouldInterpolate = *( pPointer ) SigScan.pFirstOffset;
		pbShouldInterpolate = ( pByte ) pShouldInterpolate;
	}

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x83 , 0xEC , 0x1C , 0x8B , 0x0D , 0xB4 , 0xE3 , 0x86 , 0x10 }
	, TEXT( "pInterpolateServerEntities" ) , TEXT( "client.dll" ) );

	pInterpolateServerEntities = SigScan.pFirstOffset;

	SigScan = Scan( { 0x0F , 0x11 , 0x05 , 0x60 , 0x9D , 0xFA , 0x14 , 0x83 , 0xC8 , 0x01 , 0xC7 , 0x05 , 0x84 , 0x9D , 0xFA , 0x14 , 0x00 , 0x00 , 0x00 , 0x00 }
	, TEXT( "GlowObjectManager" ) , TEXT( "client.dll" ) );

	if ( SigScan.pFirstOffset != nullptr )
	{
		Pointer pGlowObjectManager = ( *( pPointer ) ( ( HEX ) SigScan.pFirstOffset + 3 ) );
		GlowObjectManager = ( CGlowObjectManager_CSGO* ) pGlowObjectManager;
	}

	SigScan = Scan( { 0x8B , 0x0D , 0xB0 , 0xE3 , 0x86 , 0x10 , 0x53 , 0x56 , 0x57 , 0x8B , 0x99 , 0x0C , 0x10 , 0x00 , 0x00 }
	, TEXT( "UpdateClientSideAnimations" ) , TEXT( "client.dll" ) );

	UpdateClientSideAnimations = ( void( *)( ) )SigScan.pFirstOffset;

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x83 , 0xE4 , 0xF0 , 0x83 , 0xEC , 0x68 , 0x80 , 0x3D , 0x81 , 0x85 , 0xA6 , 0x10 , 0x00 }
	, TEXT( "CalcAbsolutePosition" ) , TEXT( "client.dll" ) );

	CalcAbsolutePosition = ( void( __thiscall* )( Pointer ) )SigScan.pFirstOffset;

	if ( SigScan.pFirstOffset != nullptr )
	{
		Pointer pAbsRecomputationEnabled = ( *( pPointer ) ( ( HEX ) SigScan.pFirstOffset + 11 ) );
		pbAbsRecomputationEnabled = ( pByte ) pAbsRecomputationEnabled;
		pbAbsQueriesValid = ( pByte ) ( ( HEX ) pAbsRecomputationEnabled - 1 );
	}

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x83 , 0xE4 , 0xF8 , 0x83 , 0xEC , 0x1C , 0x53 , 0x56 , 0x57 , 0x8B , 0xF9 , 0xF7 , 0x87 }
	, TEXT( "CalcAbsoluteVelocity" ) , TEXT( "client.dll" ) );

	CalcAbsoluteVelocity = ( void( __thiscall* )( Pointer ) )SigScan.pFirstOffset;

	SigScan = Scan( { 0x8B , 0x0D , 0xC4 , 0x6C , 0xF7 , 0x14 , 0x49 , 0xC7 , 0x80 , 0x14 , 0x29 , 0x00 , 0x00 , 0xFF , 0xFF , 0x7F , 0xFF }
	, TEXT( "iModelBoneCounter" ) , TEXT( "client.dll" ) );

	if ( SigScan.pFirstOffset != nullptr )
	{
		Pointer piModelBoneCounter = ( *( pPointer ) ( ( HEX ) SigScan.pFirstOffset + 2 ) );
		iModelBoneCounter = ( int* ) piModelBoneCounter;
	}

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x83 , 0xE4 , 0xF8 , 0x83 , 0xEC , 0x0C , 0x53 , 0x8B , 0x5D , 0x08 , 0x8B , 0xC3 , 0x56 }
	, TEXT( "C_BaseEntity_InvalidatePhysicsRecursive" ) , TEXT( "client.dll" ) );

	C_BaseEntity_InvalidatePhysicsRecursive = ( void( __thiscall* )( Pointer , int ) )SigScan.pFirstOffset;

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x51 , 0x53 , 0x8B , 0xD9 , 0x56 , 0x57 , 0x8D , 0xB3 , 0x44 , 0x29 , 0x00 , 0x00 }
	, TEXT( "C_BaseAnimating_LockStudioHdr" ) , TEXT( "client.dll" ) );

	C_BaseAnimating_LockStudioHdr = ( void( __thiscall* )( Pointer ) )SigScan.pFirstOffset;

	SigScan = Scan( { 0x51 , 0x56 , 0x8B , 0x35 , 0x08 , 0x30 , 0xF8 , 0x14 , 0x57 , 0x8B , 0xF9 , 0x8B , 0xCE , 0x8B , 0x06 }
	, TEXT( "C_BaseAnimating_UnLockStudioHdr" ) , TEXT( "client.dll" ) );

	C_BaseAnimating_UnLockStudioHdr = ( void( __thiscall* )( Pointer ) )SigScan.pFirstOffset;

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x53 , 0x56 , 0x57 , 0x8B , 0xF9 , 0x8B , 0x87 , 0x80 , 0x26 , 0x00 , 0x00 , 0x3B , 0x05 }
	, TEXT( "C_BaseAnimating_HitboxToWorldTransforms" ) , TEXT( "client.dll" ) );

	C_BaseAnimating_HitboxToWorldTransforms = ( bool( __thiscall* )( Pointer , Matrix3x4** ) )SigScan.pFirstOffset;

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x83 , 0xE4 , 0xF0 , 0xB8 , 0xD8 , 0x1C , 0x00 , 0x00 }

	, TEXT( "C_BaseAnimating_SetupBones" ) , TEXT( "client.dll" ) );

	C_BaseAnimating_SetupBones = ( bool( __thiscall* )( Pointer , Matrix3x4* , int , int , float ) )SigScan.pFirstOffset;

	SigScan = Scan( { 0x55, 0x8B, 0xEC, 0x83, 0xE4, 0xF8, 0x56, 0x8B, 0xF1, 0x57, 0x83, 0xBE, 0x3C, 0x29, 0x00, 0x00 }
	, TEXT( "C_BaseAnimating_GetBoneTransform" ) , TEXT( "client.dll" ) );

	C_BaseAnimating_GetBoneTransform = ( void( __thiscall* )( int , Matrix3x4& ) )SigScan.pFirstOffset;

	SigScan = Scan( { 0x30 , 0x2B , 0xEC , 0x14 , 0xC7 , 0x05 , 0x28 , 0x2E , 0xEC , 0x14 , 0xCD , 0xCC , 0xCC , 0x3D , 0xC7
					, 0x05 , 0x84 , 0x2F , 0xEC , 0x14 , 0x00 , 0x00 , 0x00 , 0x00 , 0xC7 , 0x05 , 0xF0 , 0x2F , 0xEC , 0x14
					, 0x00 , 0x00 , 0x00 , 0x00 , 0xC7 , 0x05 , 0x88 , 0x2F , 0xEC , 0x14 , 0x00 , 0x00 , 0x00 , 0x00 , 0xC6
					, 0x05 , 0x80 , 0x2C , 0xEC , 0x14 , 0x00 , 0xC7 , 0x05 , 0xA0 , 0x2C , 0xEC , 0x14 , 0x00 , 0x00 , 0x80
					, 0x3F , 0xC7 , 0x05 , 0xA4 , 0x2C , 0xEC , 0x14 , 0x00 , 0x00 , 0x80 , 0x3F , 0xC7 , 0x05 , 0xA8 , 0x2C
					, 0xEC , 0x14 , 0x00 , 0x00 , 0x00 , 0x00 , 0xC7 , 0x05 , 0xB8 , 0x30 , 0xEC , 0x14 , 0x00 , 0x00 , 0x00
					, 0x00 , 0xC3 , 0xCC , 0xCC , 0xCC , 0xCC }

	, TEXT( "ViewRender" ) , TEXT( "client.dll" ) );

	if ( SigScan.pFirstOffset != nullptr )
	{
		Pointer pViewRender = *( pPointer ) SigScan.pFirstOffset;
		ViewRender = *new Interface<IViewRender>( pViewRender , AutoConvertC( TEXT( "ViewRender" ) ) , TEXT( "client.dll" ) );
	}

	SigScan = Scan( { 0x88 , 0x2A , 0xA5 , 0x10 , 0x00 , 0x0F , 0x28 , 0xC2 , 0x56 , 0xF3 , 0x0F , 0x11 , 0x45 , 0xFC , 0x8B , 0xF1 } , TEXT( "pbEnableInvalidateBoneCache" ) , TEXT( "client.dll" ) );

	if ( SigScan.pFirstOffset != nullptr )
	{
		pbEnableInvalidateBoneCache = *( pByte* ) SigScan.pFirstOffset;
	}

	SigScan = Scan( { 0x00 , 0xF2 , 0xF0 , 0x14 , 0x33 , 0xC0 , 0xFF , 0x74 , 0x24 , 0x28 , 0x84 , 0xDB , 0x88 , 0x9F , 0x4F , 0x33 , 0x00 , 0x00 , 0x6A , 0x00 }
	, TEXT( "ClientMode" ) , TEXT( "client.dll" ) );

	if ( SigScan.pFirstOffset != nullptr )
	{
		ClientMode = *new Interface<IClientMode>( **( pPointer* ) SigScan.pFirstOffset , AutoConvertC( TEXT( "ClientMode" ) ) , TEXT( "client.dll" ) );
	}

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x51 , 0x33 , 0xC0 , 0xC7 , 0x45 }

	, TEXT( "KeyValues_Constructor" ) , TEXT( "client.dll" ) );

	KeyValues_Constructor = ( void( __thiscall* )( KeyValues* , const char* ) )SigScan.pFirstOffset;

	/*
	KeyValues::FindKey: 0x6D3ED0
	KeyValues::SetString: 0x2D7500
	*/

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x83 , 0xEC , 0x1C , 0x53 , 0x8B , 0xD9 , 0x85 , 0xDB , 0x75 , 0x09 , 0x33 , 0xC0 , 0x5B }
	, TEXT( "KeyValues_FindKey" ) , TEXT( "client.dll" ) );

	KeyValues_FindKey = ( KeyValues*( __thiscall* )( KeyValues* , const char* , bool ) )SigScan.pFirstOffset;

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0xA1 , 0xBC , 0xC3 , 0x85 , 0x10 , 0x53 , 0x56 , 0x57 , 0x8B , 0xF9 , 0x8B , 0x08 , 0x8B }
	, TEXT( "KeyValues_SetString" ) , TEXT( "client.dll" ) );

	KeyValues_SetString = ( void( __thiscall* )( KeyValues* , const char* ) )SigScan.pFirstOffset;

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x83 , 0xE4 , 0xF8 , 0x83 , 0xEC , 0x34 , 0x53 , 0x8B , 0x5D , 0x0C , 0x89 , 0x4C , 0x24 , 0x04 }
	, TEXT( "KeyValues_LoadFromBuffer" ) , TEXT( "client.dll" ) );

	KeyValues_LoadFromBuffer = ( void( __thiscall* )( KeyValues* , const char* , const char* , Pointer , const char* , Pointer ) )SigScan.pFirstOffset;

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0xA1 , 0x4C , 0xD8 , 0x57 , 0x10 , 0x81 , 0xEC , 0xFC
					, 0x0F , 0x00 , 0x00 , 0xB9 , 0x48 , 0xD8 , 0x57 , 0x10 , 0x53 , 0x8B , 0x98
					, 0xAC , 0x4C , 0x00 , 0x00 , 0x56 , 0x8B , 0xB0 , 0xB0 , 0x4C , 0x00 }
	, TEXT( "SendMove" ) , TEXT( "engine.dll" ) );

	SendMove = ( void( *)( ) ) SigScan.pFirstOffset;

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x83 , 0xE4 , 0xF0 , 0xB8 , 0x38 , 0x01 , 0x04 }
	, TEXT( "SendDataGram" ) , TEXT( "engine.dll" ) );

	SendDataGram = ( void( __thiscall* )( Pointer , bf_write* ) ) SigScan.pFirstOffset;

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x83 , 0xEC , 0x08 , 0x53 , 0x8B , 0x5D , 0x10 , 0x56 , 0x57 , 0xFF , 0x75 , 0x0C , 0x8B
					, 0xF1 , 0xF3 , 0x0F , 0x11 , 0x55 , 0xF8 , 0x8D , 0x8B , 0xD4 , 0x34 , 0x00 , 0x00 , 0x89 , 0x75 , 0xFC , 0xC6 }
	, TEXT( "RunSimulation" ) , TEXT( "client.dll" ) );

	RunSimulation = ( void( __thiscall* )( Pointer , int , CUserCmd* , C_BasePlayer* ) ) SigScan.pFirstOffset;

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x83 , 0xE4 , 0xF8 , 0x83 , 0xEC , 0x0C , 0x53 , 0x56 , 0x57 , 0x8B , 0x7D , 0x08 , 0x8B
					, 0xF1 , 0xF3 , 0x0F , 0x10 , 0x07 , 0x0F , 0x2E , 0x86 , 0x94 , 0x00 , 0x00 , 0x00 , 0x9F , 0xF6 , 0xC4 , 0x44 }
	, TEXT( "C_BaseEntity_SetAbsVelocity" ) , TEXT( "client.dll" ) );

	C_BaseEntity_SetAbsVelocity = ( void( __thiscall* )( Pointer , const Vector& ) ) SigScan.pFirstOffset;

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x83 , 0xE4 , 0xC0 , 0x83 , 0xEC , 0x34 , 0x53 , 0x56 , 0x8B , 0x75 , 0x08 , 0x8B , 0xD9 }
	, TEXT( "RunCommand" ) , TEXT( "client.dll" ) );

	RunCommand = ( void( __thiscall* )( Pointer , C_BasePlayer* , CUserCmd* , IMoveHelper* ) ) SigScan.pFirstOffset;

	SigScan = Scan( { 0x8B , 0x0D , 0x90 , 0xA4 , 0xF7 , 0x14 , 0x52 , 0xF3 , 0x0F , 0x10 , 0x80 , 0xAC }
	, TEXT( "MoveHelper" ) , TEXT( "client.dll" ) );

	if ( SigScan.pFirstOffset != nullptr )
	{
		MoveHelper = **( IMoveHelper*** ) ( ( HEX ) SigScan.pFirstOffset + 2 );
	}

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x83 , 0xEC , 0x08 , 0x56 , 0x8B , 0xF1 , 0x8B , 0x86 , 0xC4 , 0x00 , 0x00 , 0x00 }
	, TEXT( "SendNetMsg" ) , TEXT( "engine.dll" ) );

	SendNetMsg = ( bool( __thiscall* )( Pointer , INetMessage& , bool , bool ) )SigScan.pFirstOffset;

	SigScan = Scan( { 0x44 , 0xC8 , 0x57 , 0x10 , 0x0F , 0x5B , 0xDB , 0xF3 , 0x0F , 0x5E , 0xE6 , 0xF3 , 0x0F , 0x59 }
	, TEXT( "ClientState" ) , TEXT( "engine.dll" ) );

	pClientState = **( pPointer* ) SigScan.pFirstOffset;

	SigScan = Scan( { 0x2C , 0x81 , 0xF7 , 0x14 , 0xF3 , 0x0F , 0x10 , 0x48 , 0x20 , 0xF3 , 0x0F , 0x59 }
	, TEXT( "PlayerPrediction" ) , TEXT( "client.dll" ) );

	pPlayerPrediction = **( C_BasePlayer*** ) SigScan.pFirstOffset;

	SigScan = Scan( { 0x7C , 0xB4 , 0xF7 , 0x14 , 0xFF , 0xB3 , 0x70 , 0x04 , 0x00 , 0x00 , 0xFF , 0x77 , 0x08 , 0x8B
					, 0x01 , 0x8B , 0x40 , 0x70 , 0xFF , 0xD0 , 0x84 , 0xC0 , 0x74 , 0x14 }
	, TEXT( "CSGO_GameRules" ) , TEXT( "client.dll" ) );

	pGameRules = *( pPointer* ) SigScan.pFirstOffset;

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x56 , 0x8B , 0x75 , 0x08 , 0x57 , 0x8B , 0xF9 , 0x85 , 0xF6 , 0x74 , 0x24 , 0x66 , 0x90 }
	, TEXT( "Buf_WriteString" ) , TEXT( "engine.dll" ) );

	Buf_WriteString = ( bool( __thiscall* )( Pointer , const char* ) ) SigScan.pFirstOffset;

	SigScan = Scan( { 0x55 , 0x8B , 0xEC , 0x51 , 0xF6 , 0x05 , 0xA4 , 0x47 , 0xEC , 0x12 , 0x01 , 0x56 , 0x57 , 0x8B , 0x7D , 0x0C }
	, TEXT( "Input_AdjustPitch" ) , TEXT( "client.dll" ) );

	pInput_AdjustPitch = SigScan.pFirstOffset;

	HMODULE hvstdlib = _GetModule<HMODULE>( TEXT( "vstdlib.dll" ) );

	RandomSeed = ( void( *)( int ) )( Pointer )GetProcAddress( hvstdlib , AutoConvertC( TEXT( "RandomSeed" ) ) );
	RandomInt = ( int( *)( int , int ) )( Pointer )GetProcAddress( hvstdlib , AutoConvertC( TEXT( "RandomInt" ) ) );
	RandomFloat = ( float( *)( float , float ) )( Pointer )GetProcAddress( hvstdlib , AutoConvertC( TEXT( "RandomFloat" ) ) );
	RandomFloatExp = ( float( *)( float , float , float ) )( Pointer )GetProcAddress( hvstdlib , AutoConvertC( TEXT( "RandomFloatExp" ) ) );
	RandomGaussianFloat = ( float( *)( float , float ) )( Pointer )GetProcAddress( hvstdlib , AutoConvertC( TEXT( "RandomGaussianFloat" ) ) );

	HMODULE htier0 = _GetModule<HMODULE>( TEXT( "tier0.dll" ) );

	Msg = ( void( *)( const char* , ... ) )( Pointer )GetProcAddress( htier0 , AutoConvertC( TEXT( "Msg" ) ) );
	DMsg = ( void( *)( const String * , int , const String * , ... ) )( Pointer )GetProcAddress( htier0 , AutoConvertC( TEXT( "DMsg" ) ) );

	/*SigScan.sName = TEXT( "pCUserCmdDeconstructor" );
	SigScan.Scan( { 0x55, 0x8B, 0xEC, 0x56, 0x8B, 0xF1, 0x8B, 0x4D, 0x08, 0xF6, 0xC1, 0x02, 0x74, 0x3E, 0x8B, 0x46, 0xFC,
					0x57, 0x8D, 0x7E, 0xFC, 0x6B, 0xD0, 0x64, 0x03, 0xD6, 0x85, 0xC0 }, TEXT("client.dll") );

	pCUserCmdDeconstructor = SigScan.pFirstOffset;*/
}