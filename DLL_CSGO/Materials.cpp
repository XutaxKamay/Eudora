#include "Includes.hxx"
#include "Main.hxx"

#define FULL_FRAME_TEXTURE "_rt_FullFrameFB"

// If you've added IMatRenderContext::OverrideDepthFunc (see ::DrawGlowOccluded below),
// then you can enable this and have single-pass glows for "glow when occluded" outlines.
// ***PLEASE*** increment MATERIAL_SYSTEM_INTERFACE_VERSION when you add this!
#define ADDED_OVERRIDE_DEPTH_FUNC 0

// If you've fixed IMatRenderContext::CopyTextureToRenderTargetEx
// (see CGlowObjectManager::RenderGlowModels below), then you can enable this and have
// code that's a bit cleaner. Also, then you won't have to ship debug/debugfbtexture1.
#define FIXED_COPY_TEXTURE_TO_RENDER_TARGET 0

IMaterial* Mat_VertexGhost = nullptr;
IMaterial* Mat_VertexGhostIgnoreZ = nullptr;
IMaterial* Mat_VertexGhostSelectedIgnoreZ = nullptr;
IMaterial* Mat_Glow = nullptr;
IMaterial *Mat_HaloAddToScreen = nullptr;
IMaterial *Mat_Downsample = nullptr;
IMaterial *Mat_BlurX = nullptr;
IMaterial *Mat_BlurY = nullptr;
IMaterial *Mat_DebugTexture = nullptr;
IMaterial *Mat_Wireframe = nullptr;
IMaterial *Mat_WireframeIgnoreZ = nullptr;
IMaterial *Mat_VertexColor = nullptr;
IMaterial *Mat_VertexColorIgnoreZ = nullptr;

ITexture *Text_FullFrame = nullptr;
ITexture *Text_QuarterSize0 = nullptr;
ITexture *Text_QuarterSize1 = nullptr;

static bool s_bFirstPass = false;

static void SetRenderTargetAndViewPort( ITexture *rt , int w , int h )
{
    CMatRenderContextPtr pRenderContext( MaterialSystem.pClass );
    pRenderContext->SetRenderTarget( rt );
    pRenderContext->Viewport( 0 , 0 , w , h );
}

CGlowObjectManager g_GlowObjectManager;

IMaterial *_CreateMaterial( const char*sMaterialName , const char* sMaterialType , const char* sBufferKeyValuesTmp )
{
    KeyValues *pVMTKeyValues = new KeyValues( AutoConvertC( TEXT( "TempKeyValues" ) ) );

    char sCreatedMaterialVMT[ 0xFFF ];

    sprintf_s( sCreatedMaterialVMT , "\"%s\"\n{%s\n}\n" , sMaterialType , sBufferKeyValuesTmp );

    Offsets->KeyValues_Constructor( pVMTKeyValues , sMaterialType );

    pVMTKeyValues->LoadFromBuffer( sMaterialName , sCreatedMaterialVMT );

    return MaterialSystem->CreateMaterial( sMaterialName , pVMTKeyValues );
}

IMaterial *_CreateMaterial( const char*sMaterialName ,
                            KeyValues *pVMTKeyValues )
{
    return MaterialSystem->CreateMaterial( sMaterialName , pVMTKeyValues );
}

#define CreateMaterial(sMat,sType,sBuf) sMat = _CreateMaterial(#sMat,sType,sBuf)
#define CreateMaterialFromKey(sMat,pKeyValues) sMat = _CreateMaterial(#sMat,pKeyValues);

KeyValues *CreateKeyValues( const char* sMaterialType )
{
    return new KeyValues( sMaterialType );
}

void InitCustomMaterials()
{
    /*
    models/player/ct_fbi/ct_fbi_glass - platinum
    models/inventory_items/cologne_prediction/cologne_prediction_glass - glass
    models/inventory_items/trophy_majors/crystal_clear - crystal
    models/inventory_items/trophy_majors/gold - gold
    models/gibs/glass/glass - dark chrome
    models/inventory_items/trophy_majors/gloss - plastic/glass
    vgui/achievements/glow - glow
    */

    /*static char sBufferVertexGlow[] =
    {
    "\
    \n$baseTexture \"detail\\dt_metal1\"\
    \n$color \"[ .05 .05 .05 ]\"\
    \n$additive 1\
    \n$ignorez 1\
    \n$halflambert 1\
    \n$selfillum 1\
    \n$envmap \"Editor\\cube_vertigo\"\
    \n$envmaptint \"[.6 .6 .6]\"\
    "
    };

    CreateMaterial( Mat_VertexGlow , "VertexLitGeneric" , sBufferVertexGlow );*/

    /*static char sBufferVertexGhost[] =
    {
    "\
    \n$baseTexture \"detail\\dt_metal1\"\
    \n$color \"[ .05 .05 .05 ]\"\
    \n$additive 1\
    \n$ignorez 0\
    \n$halflambert 1\
    \n$selfillum 1\
    \n$envmap \"Editor\\cube_vertigo\"\
    \n$envmaptint \"[.6 .6 .6]\"\
    "
    };

    CreateMaterial( Mat_VertexGhost , "VertexLitGeneric" , sBufferVertexGhost );

    static char sBufferVertexGhostIgnoreZ[] =
    {
    "\
    \n$baseTexture \"detail\\dt_metal1\"\
    \n$color \"[ .05 .05 .05 ]\"\
    \n$additive 1\
    \n$ignorez 1\
    \n$halflambert 1\
    \n$selfillum 1\
    \n$envmap \"Editor\\cube_vertigo\"\
    \n$envmaptint \"[.6 .6 .6]\"\
    "
    };

    CreateMaterial( Mat_VertexGhostIgnoreZ , "VertexLitGeneric" , sBufferVertexGhostIgnoreZ );*/

    KeyValues *pVMTKeyValues = new KeyValues( "VertexLitGeneric" );
    pVMTKeyValues->SetString( "$basetexture" , "vgui\\white_additive" );
    pVMTKeyValues->SetString( "$vertexcolor" , "1" );
    pVMTKeyValues->SetString( "$vertexalpha" , "1" );
    pVMTKeyValues->SetString( "$color" , "[ 0.05 0.05 0.05 ]" );
    pVMTKeyValues->SetString( "$additive" , "1" );
    pVMTKeyValues->SetString( "$envmap" , "Editor\\cube_vertigo" );
    pVMTKeyValues->SetString( "$envmaptint" , "[ 0.6 0.6 0.6 ]" );
    pVMTKeyValues->SetString( "$ignorez" , "0" );
    pVMTKeyValues->SetString( "$halflambert" , "1" );
    pVMTKeyValues->SetString( "$selfillum" , "1" );
    CreateMaterialFromKey( Mat_VertexGhostIgnoreZ , pVMTKeyValues );

    pVMTKeyValues = new KeyValues( "VertexLitGeneric" );
    pVMTKeyValues->SetString( "$basetexture" , "detail\\dt_metal1" );
    pVMTKeyValues->SetString( "$color" , "[ 0.05 0.05 0.05 ]" );
    pVMTKeyValues->SetString( "$additive" , "1" );
    pVMTKeyValues->SetString( "$envmap" , "Editor\\cube_vertigo" );
    pVMTKeyValues->SetString( "$envmaptint" , "[ 0.6 0.6 0.6 ]" );
    pVMTKeyValues->SetString( "$halflambert" , "1" );
    pVMTKeyValues->SetString( "$selfillum" , "1" );
    CreateMaterialFromKey( Mat_VertexGhost , pVMTKeyValues );

    pVMTKeyValues = new KeyValues( "VertexLitGeneric" );
    pVMTKeyValues->SetString( "$basetexture" , "vgui\\white_additive" );
    pVMTKeyValues->SetString( "$vertexcolor" , "1" );
    pVMTKeyValues->SetString( "$vertexalpha" , "1" );
    pVMTKeyValues->SetString( "$additive" , "1" );
    pVMTKeyValues->SetString( "$ignorez" , "0" );
    pVMTKeyValues->SetString( "$halflambert" , "1" );
    pVMTKeyValues->SetString( "$selfillum" , "1" );
    CreateMaterialFromKey( Mat_VertexGhostSelectedIgnoreZ , pVMTKeyValues );

    pVMTKeyValues = new KeyValues( "UnlitGeneric" );
    pVMTKeyValues->SetString( "$basetexture" , "_rt_FullFrameFB1" );
    pVMTKeyValues->SetString( "$noToolTexture" , "1" );
    CreateMaterialFromKey( Mat_DebugTexture , pVMTKeyValues );

    Mat_Glow = MaterialSystem->FindMaterial( "dev/glow_color" , TEXTURE_GROUP_OTHER , true );
    //Mat_Glow->SetMaterialVarFlag( MaterialVarFlags_t::MATERIAL_VAR_ADDITIVE , 0 );
    //Mat_Glow->SetMaterialVarFlag( MaterialVarFlags_t::MATERIAL_VAR_HALFLAMBERT , 1 );
    //Mat_Glow->SetMaterialVarFlag( MaterialVarFlags_t::MATERIAL_VAR_SELFILLUM , 1 );
    //Mat_Glow->SetMaterialVarFlag( MaterialVarFlags_t::MATERIAL_VAR_NOFOG , 1 );
    //Mat_Glow->SetMaterialVarFlag( MaterialVarFlags_t::MATERIAL_VAR_NOCULL , 1 );

    //Mat_HaloAddToScreen = MaterialSystem->FindMaterial( "dev/halo_add_to_screen" , TEXTURE_GROUP_OTHER , true );

    pVMTKeyValues = new KeyValues( "screenspace_general" );
    pVMTKeyValues->SetString( "$basetexture" , "_rt_FullFrameFB" );
    pVMTKeyValues->SetString( "$PIXSHADER" , "haloaddoutline_ps20" );
    pVMTKeyValues->SetString( "$ALPHA_BLEND_COLOR_OVERLAY" , "1" );
    pVMTKeyValues->SetString( "$ignorez" , "1" );
    pVMTKeyValues->SetString( "$linearread_basetexture" , "1" );
    pVMTKeyValues->SetString( "$linearwrite" , "1" );
    CreateMaterialFromKey( Mat_HaloAddToScreen , pVMTKeyValues );

    pVMTKeyValues = new KeyValues( "wireframe" );
    pVMTKeyValues->SetInt( "$vertexcolor" , 1 );
    CreateMaterialFromKey( Mat_Wireframe , pVMTKeyValues );

    pVMTKeyValues = new KeyValues( "wireframe" );
    pVMTKeyValues->SetInt( "$vertexcolor" , 1 );
    pVMTKeyValues->SetInt( "$vertexalpha" , 1 );
    pVMTKeyValues->SetInt( "$ignorez" , 1 );
    CreateMaterialFromKey( Mat_WireframeIgnoreZ , pVMTKeyValues );

    pVMTKeyValues = new KeyValues( "unlitgeneric" );
    pVMTKeyValues->SetInt( "$vertexcolor" , 1 );
    pVMTKeyValues->SetInt( "$vertexalpha" , 1 );
    CreateMaterialFromKey( Mat_VertexColor , pVMTKeyValues );

    pVMTKeyValues = new KeyValues( "unlitgeneric" );
    pVMTKeyValues->SetInt( "$vertexcolor" , 1 );
    pVMTKeyValues->SetInt( "$vertexalpha" , 1 );
    pVMTKeyValues->SetInt( "$ignorez" , 1 );
    CreateMaterialFromKey( Mat_VertexColorIgnoreZ , pVMTKeyValues );

    // Get material and texture pointers
    Mat_Downsample = MaterialSystem->FindMaterial( "dev/glow_downsample" , TEXTURE_GROUP_OTHER , true );

    Mat_BlurX = MaterialSystem->FindMaterial( "dev/glow_blur_x" , TEXTURE_GROUP_OTHER , true );
    Mat_BlurY = MaterialSystem->FindMaterial( "dev/glow_blur_y" , TEXTURE_GROUP_OTHER , true );

    Text_FullFrame = MaterialSystem->FindTexture( FULL_FRAME_TEXTURE , TEXTURE_GROUP_RENDER_TARGET );
    Text_QuarterSize0 = MaterialSystem->FindTexture( "_rt_SmallFB0" , TEXTURE_GROUP_RENDER_TARGET );
    Text_QuarterSize1 = MaterialSystem->FindTexture( "_rt_SmallFB1" , TEXTURE_GROUP_RENDER_TARGET );

    /*

    "UnlitGeneric"
    {
    "$basetexture" "glow_strong"
    "$vertexcolor"  "1"
    "$vertexalpha"  "1"
    "$translucent"  "1"
    "$model"        "1"
    "$additive"     "1"
    }
    */
}

void CGlowObjectManager::RenderGlowEffects( const CViewSetup *pSetup )
{
    CMatRenderContextPtr pRenderContext( MaterialSystem.pClass );

    int nX , nY , nWidth , nHeight;
    pRenderContext->GetViewport( nX , nY , nWidth , nHeight );

    if ( !Cvars[ hack_esp_glow_mode ]->GetBool() )
        ApplyEntityGlowEffects( pSetup , pRenderContext , Cvars[ hack_esp_glow_bloom_amount ]->GetFloat() , nX , nY , nWidth , nHeight );
    else
        ApplyEntityCustomGlowEffects( pSetup , pRenderContext , Cvars[ hack_esp_glow_bloom_amount ]->GetFloat() , nX , nY , nWidth , nHeight );
}

void CGlowObjectManager::ApplyEntityCustomGlowEffects( const CViewSetup *pSetup , CMatRenderContextPtr &pRenderContext , float flBloomScale , int x , int y , int w , int h )
{
    for ( int i = 0; i < MAX_EDICTS; i++ )
    {
        bShouldRenderInOccluded[ i ] = true;
        bShouldRenderInUnOccluded[ i ] = false;
    }

    ApplyEntityGlowEffects( pSetup , pRenderContext , flBloomScale , x , y , w , h );

    for ( int i = 0; i < MAX_EDICTS; i++ )
    {
        bShouldRenderInOccluded[ i ] = false;
        bShouldRenderInUnOccluded[ i ] = true;
    }

    ApplyEntityGlowEffects( pSetup , pRenderContext , flBloomScale , x , y , w , h );
}

void CGlowObjectManager::DrawGlowAlways( CMatRenderContextPtr& pRenderContext )
{
    ShaderStencilState_t stencilState;
    stencilState.m_bEnable = true;
    stencilState.m_nReferenceValue = 1;
    stencilState.m_CompareFunc = SHADER_STENCILFUNC_ALWAYS;
    stencilState.m_PassOp = SHADER_STENCILOP_SET_TO_REFERENCE;
    stencilState.m_FailOp = SHADER_STENCILOP_KEEP;
    stencilState.m_ZFailOp = SHADER_STENCILOP_SET_TO_REFERENCE;
    pRenderContext->SetStencilState( stencilState );

    pRenderContext->OverrideDepthEnable( false , false );
    RenderView->SetBlend( 1 );

    for ( int i = 0; i < MAX_EDICTS; i++ )
    {
        C_BaseEntity* pEntity = ( C_BaseEntity* ) ClientEntityList->GetClientEntity( i );

        if ( pEntity == nullptr )
            continue;

        int iEntIndex = pEntity->entindex();

        if ( !bShouldRender[ iEntIndex ] )
            continue;

        if ( !bShouldRenderInOccluded[ iEntIndex ] || !bShouldRenderInUnOccluded[ iEntIndex ] )
            continue;

        bUnOccluding[ iEntIndex ] = true;
        bOccluding[ iEntIndex ] = true;

        const Vector vGlowColor = vColorOccluded[ iEntIndex ] * flAlpha[ iEntIndex ];
        RenderView->SetColorModulation( vGlowColor.Base() ); // This only sets rgb, not alpha

        DrawModel( pEntity );
    }
}

void CGlowObjectManager::DrawGlowOccluded( CMatRenderContextPtr& pRenderContext )
{
#if ADDED_OVERRIDE_DEPTH_FUNC	// Enable this when the TF2 team has added IMatRenderContext::OverrideDepthFunc or similar.
    ShaderStencilState_t stencilState;
    stencilState.m_bEnable = true;
    stencilState.m_nReferenceValue = 1;
    stencilState.m_CompareFunc = SHADER_STENCILFUNC_ALWAYS;
    stencilState.m_PassOp = glow_outline_effect_stencil_mode.GetBool() ? SHADER_STENCILOP_KEEP : SHADER_STENCILOP_SET_TO_REFERENCE;
    stencilState.m_FailOp = SHADER_STENCILOP_KEEP;
    stencilState.m_ZFailOp = SHADER_STENCILOP_SET_TO_REFERENCE;
    pRenderContext->SetStencilState( stencilState );

    pRenderContext->OverrideDepthEnable( true , false );

    // Not implemented, we need this feature to be able to do this in 1 pass. Otherwise,
    // we'd have to do 2 passes, 1st to mark on the stencil where the depth test failed,
    // 2nd to actually utilize that information and draw color there.
    pRenderContext->OverrideDepthFunc( true , SHADER_DEPTHFUNC_NEARER );

    for ( int i = 0; i < MAX_EDICTS; i++ )
    {
        C_BaseEntity* pEntity = ( C_BaseEntity* ) ClientEntityList->GetClientEntity( i );

        if ( pEntity == nullptr )
            continue;

        int iEntIndex = pEntity->entindex();

        bOccluding[ iEntIndex ] = false;

        if ( !bShouldRender[ iEntIndex ] )
            continue;

        if ( !bShouldRenderInOccluded[ iEntIndex ] || bShouldRenderInUnOccluded[ iEntIndex ] )
            continue;

        bUnOccluding[ iEntIndex ] = true;

        const Vector vGlowColor = vColorOccluded[ iEntIndex ] * flAlpha[ iEntIndex ];
        RenderView->SetColorModulation( vGlowColor.Base() ); // This only sets rgb, not alpha

        DrawModel( pEntity );
    }

    pRenderContext->OverrideDepthFunc( false , SHADER_DEPTHFUNC_NEAREROREQUAL )
    #else	// 2-pass as a proof of concept so I can take a nice screenshot.
    pRenderContext->OverrideDepthEnable( true , false );

    ShaderStencilState_t stencilState;
    stencilState.m_bEnable = true;
    stencilState.m_nReferenceValue = 2;
    stencilState.m_nWriteMask = 2;
    stencilState.m_CompareFunc = SHADER_STENCILFUNC_ALWAYS;
    stencilState.m_PassOp = SHADER_STENCILOP_SET_TO_REFERENCE;
    stencilState.m_FailOp = SHADER_STENCILOP_KEEP;
    stencilState.m_ZFailOp = SHADER_STENCILOP_KEEP;
    pRenderContext->SetStencilState( stencilState );

    // Draw depthtest-passing pixels to the stencil buffer
    {
        RenderView->SetBlend( 0 );
        pRenderContext->OverrideAlphaWriteEnable( true , false );
        pRenderContext->OverrideColorWriteEnable( true , false );

        for ( int i = 0; i < MAX_EDICTS; i++ )
        {
            C_BaseEntity* pEntity = ( C_BaseEntity* ) ClientEntityList->GetClientEntity( i );

            if ( pEntity == nullptr )
                continue;

            int iEntIndex = pEntity->entindex();

            bOccluding[ iEntIndex ] = false;

            if ( !bShouldRender[ iEntIndex ] )
                continue;

            if ( !bShouldRenderInOccluded[ iEntIndex ] || bShouldRenderInUnOccluded[ iEntIndex ] )
                continue;

            bUnOccluding[ iEntIndex ] = true;

            const Vector vGlowColor = vColorOccluded[ iEntIndex ] * flAlpha[ iEntIndex ];
            RenderView->SetColorModulation( vGlowColor.Base() ); // This only sets rgb, not alpha

            DrawModel( pEntity );
        }
    }

    pRenderContext->OverrideAlphaWriteEnable( false , true );
    pRenderContext->OverrideColorWriteEnable( false , true );

    pRenderContext->OverrideDepthEnable( false , false );

    stencilState.m_bEnable = true;
    stencilState.m_nReferenceValue = 3;
    stencilState.m_nTestMask = 2;
    stencilState.m_nWriteMask = 1;
    stencilState.m_CompareFunc = SHADER_STENCILFUNC_NOTEQUAL;
    stencilState.m_PassOp = SHADER_STENCILOP_SET_TO_REFERENCE;
    stencilState.m_ZFailOp = SHADER_STENCILOP_SET_TO_REFERENCE;
    stencilState.m_FailOp = Cvars[ hack_esp_glow_stencil_mode ]->GetBool() ? SHADER_STENCILOP_KEEP : SHADER_STENCILOP_SET_TO_REFERENCE;
    pRenderContext->SetStencilState( stencilState );

    // Draw color+alpha, stenciling out pixels from the first pass
    RenderView->SetBlend( 1 );

    for ( int i = 0; i < MAX_EDICTS; i++ )
    {
        C_BaseEntity* pEntity = ( C_BaseEntity* ) ClientEntityList->GetClientEntity( i );

        if ( pEntity == nullptr )
            continue;

        int iEntIndex = pEntity->entindex();

        bOccluding[ iEntIndex ] = false;

        if ( !bShouldRender[ iEntIndex ] )
            continue;

        if ( !bShouldRenderInOccluded[ iEntIndex ] || bShouldRenderInUnOccluded[ iEntIndex ] )
            continue;

        bOccluding[ iEntIndex ] = true;

        const Vector vGlowColor = vColorOccluded[ iEntIndex ] * flAlpha[ iEntIndex ];
        RenderView->SetColorModulation( vGlowColor.Base() ); // This only sets rgb, not alpha

        DrawModel( pEntity );
    }

#endif
}

void CGlowObjectManager::DrawGlowVisible( CMatRenderContextPtr& pRenderContext )
{
    ShaderStencilState_t stencilState;
    stencilState.m_bEnable = true;
    stencilState.m_nReferenceValue = 1;
    stencilState.m_CompareFunc = SHADER_STENCILFUNC_ALWAYS;
    stencilState.m_PassOp = SHADER_STENCILOP_SET_TO_REFERENCE;
    stencilState.m_FailOp = SHADER_STENCILOP_KEEP;
    stencilState.m_ZFailOp = Cvars[ hack_esp_glow_stencil_mode ]->GetBool() ? SHADER_STENCILOP_KEEP : SHADER_STENCILOP_SET_TO_REFERENCE;

    pRenderContext->SetStencilState( stencilState );

    pRenderContext->OverrideDepthEnable( true , false );
    RenderView->SetBlend( 1 );

    for ( int i = 0; i < MAX_EDICTS; i++ )
    {
        C_BaseEntity* pEntity = ( C_BaseEntity* ) ClientEntityList->GetClientEntity( i );

        if ( pEntity == nullptr )
            continue;

        int iEntIndex = pEntity->entindex();

        bUnOccluding[ iEntIndex ] = false;

        if ( !bShouldRender[ iEntIndex ] )
            continue;

        if ( bShouldRenderInOccluded[ iEntIndex ] || !bShouldRenderInUnOccluded[ iEntIndex ] )
            continue;

        bUnOccluding[ iEntIndex ] = true;

        const Vector vGlowColor = vColorUnOccluded[ iEntIndex ] * flAlpha[ iEntIndex ];
        RenderView->SetColorModulation( vGlowColor.Base() ); // This only sets rgb, not alpha

        DrawModel( pEntity );
    }
}

void CGlowObjectManager::ApplyEntityGlowEffects( const CViewSetup *pSetup , CMatRenderContextPtr &pRenderContext , float flBloomScale , int x , int y , int w , int h )
{
    static ITexture* const pRtFullFrameFB0 = MaterialSystem.pClass->FindTexture( "_rt_FullFrameFB" , TEXTURE_GROUP_RENDER_TARGET );
    static ITexture* const pRtFullFrameFB1 = MaterialSystem.pClass->FindTexture( "_rt_FullFrameFB1" , TEXTURE_GROUP_RENDER_TARGET );

    pRenderContext->PushRenderTargetAndViewport();

    // Set backbuffer + hardware depth as MRT 0. We CANNOT CHANGE RENDER TARGETS after this point!!!
    // In CShaderAPIDx8::CreateDepthTexture all depth+stencil buffers are created with the "discard"
    // flag set to TRUE. Not sure about OpenGL, but according to
    // https://msdn.microsoft.com/en-us/library/windows/desktop/bb174356(v=vs.85).aspx, if you change
    // the depth+stencil buffer away from a buffer that has discard=TRUE, the contents become garbage.

    pRenderContext->SetRenderTargetEx( 0 , nullptr );

    // Save current backbuffer to _rt_FullFrameFB1
    pRenderContext->CopyRenderTargetToTexture( pRtFullFrameFB1 );

    // Clear backbuffer color and stencil, keep depth for testing
    pRenderContext->ClearColor3ub( 0 , 0 , 0 );
    pRenderContext->ClearBuffers( true , false );

    // Draw glow models
    {
        // Save modulation color and blend
        Vector vOrigColor;
        RenderView->GetColorModulation( vOrigColor.Base() );
        const float flOrigBlend = RenderView->GetBlend();

        // Set override material for glow color
        ModelRender->ForcedMaterialOverride( Mat_Glow );
        pRenderContext->OverrideColorWriteEnable( true , true );
        pRenderContext->OverrideAlphaWriteEnable( true , true );

        // Draw "glow when visible" objects
        DrawGlowVisible( pRenderContext );

        // Draw "glow when occluded" objects
        DrawGlowOccluded( pRenderContext );

        // Draw "glow always" objects
        DrawGlowAlways( pRenderContext );

        // Unset override material
        ModelRender->ForcedMaterialOverride( NULL );

        // Restore modulation color and blend
        RenderView->SetColorModulation( vOrigColor.Base() );
        RenderView->SetBlend( flOrigBlend );
        pRenderContext->OverrideDepthEnable( false , false );
    }

    // Copy MSAA'd glow models to _rt_FullFrameFB0
    pRenderContext->CopyRenderTargetToTexture( pRtFullFrameFB0 );

    ITexture* const pRtQuarterSize1 = Text_QuarterSize1;

    // Move original contents of the backbuffer from _rt_FullFrameFB1 to the backbuffer
    {
    #if FIXED_COPY_TEXTURE_TO_RENDER_TARGET	// Coordinates don't seem to be mapped 1:1 properly, screen becomes slightly blurry
        pRenderContext->CopyTextureToRenderTargetEx( 0 , pRtFullFrameFB1 , nullptr );
    #else
        pRenderContext.SetStencilEnable( false );

        IMaterial* const pFullFrameFB1 = Mat_DebugTexture;
        pFullFrameFB1->AddRef();
        pRenderContext->Bind( pFullFrameFB1 );

        const int nSrcWidth = pSetup->width;
        const int nSrcHeight = pSetup->height;
        int nViewportX , nViewportY , nViewportWidth , nViewportHeight;
        pRenderContext->GetViewport( nViewportX , nViewportY , nViewportWidth , nViewportHeight );

        pRenderContext->OverrideDepthEnable( true , false );
        {
            pRenderContext->DrawScreenSpaceRectangle( pFullFrameFB1 ,
                                                      0 , 0 , nViewportWidth , nViewportHeight ,
                                                      0 , 0 , ( float ) nSrcWidth - 1 , ( float ) nSrcHeight - 1 ,
                                                      pRtFullFrameFB1->GetActualWidth() , pRtFullFrameFB1->GetActualHeight() );
        }
        pRenderContext->OverrideDepthEnable( false , false );

        pFullFrameFB1->Release();
    #endif
    }

    // Get viewport
    int nSrcWidth = pSetup->width;
    int nSrcHeight = pSetup->height;
    int nViewportX , nViewportY , nViewportWidth , nViewportHeight;
    pRenderContext->GetViewport( nViewportX , nViewportY , nViewportWidth , nViewportHeight );

    // Get material and texture pointers
    IMaterial *pMatDownsample = Mat_Downsample;
    IMaterial *pMatBlurX = Mat_BlurX;
    IMaterial *pMatBlurY = Mat_BlurY;

    ITexture *pRtFullFrame = Text_FullFrame;
    ITexture *pRtQuarterSize0 = Text_QuarterSize0;

    //============================================
    // Downsample _rt_FullFrameFB to _rt_SmallFB0
    //============================================

    // First clear the full target to black if we're not going to touch every pixel
    if ( ( pRtQuarterSize0->GetActualWidth() != ( pSetup->width / 4 ) ) || ( pRtQuarterSize0->GetActualHeight() != ( pSetup->height / 4 ) ) )
    {
        SetRenderTargetAndViewPort( pRtQuarterSize0 , pRtQuarterSize0->GetActualWidth() , pRtQuarterSize0->GetActualHeight() );
        pRenderContext->ClearColor3ub( 0 , 0 , 0 );
        pRenderContext->ClearBuffers( true , false , false );
    }

    // Set the viewport
    SetRenderTargetAndViewPort( pRtQuarterSize0 , pSetup->width / 4 , pSetup->height / 4 );

    IMaterialVar *pbloomexpvar = pMatDownsample->FindVar( "$bloomexp" , 0 );
    if ( pbloomexpvar != NULL )
    {
        pbloomexpvar->SetFloatValue( 2.5f );
    }

    IMaterialVar *pbloomsaturationvar = pMatDownsample->FindVar( "$bloomsaturation" , 0 );
    if ( pbloomsaturationvar != NULL )
    {
        pbloomsaturationvar->SetFloatValue( 1.0f );
    }

    // note the -2's below. Thats because we are downsampling on each axis and the shader
    // accesses pixels on both sides of the source coord
    int nFullFbWidth = nSrcWidth;
    int nFullFbHeight = nSrcHeight;

    pRenderContext->DrawScreenSpaceRectangle( pMatDownsample , 0 , 0 , nSrcWidth / 4 , nSrcHeight / 4 ,
                                              0 , 0 , ( float ) nFullFbWidth - 4 , ( float ) nFullFbHeight - 4 ,
                                              pRtFullFrame->GetActualWidth() , pRtFullFrame->GetActualHeight() );

    //============================//
    // Guassian blur x rt0 to rt1 //
    //============================//

    // First clear the full target to black if we're not going to touch every pixel
    if ( s_bFirstPass || ( pRtQuarterSize1->GetActualWidth() != ( pSetup->width / 4 ) ) || ( pRtQuarterSize1->GetActualHeight() != ( pSetup->height / 4 ) ) )
    {
        // On the first render, this viewport may require clearing
        s_bFirstPass = false;
        SetRenderTargetAndViewPort( pRtQuarterSize1 , pRtQuarterSize1->GetActualWidth() , pRtQuarterSize1->GetActualHeight() );
        pRenderContext->ClearColor3ub( 0 , 0 , 0 );
        pRenderContext->ClearBuffers( true , false , false );
    }

    // Set the viewport
    SetRenderTargetAndViewPort( pRtQuarterSize1 , pSetup->width / 4 , pSetup->height / 4 );

    pRenderContext->DrawScreenSpaceRectangle( pMatBlurX , 0 , 0 , nSrcWidth / 4 , nSrcHeight / 4 ,
                                              0 , 0 , ( float ) nSrcWidth / 4 - 1 , ( float ) nSrcHeight / 4 - 1 ,
                                              pRtQuarterSize0->GetActualWidth() , pRtQuarterSize0->GetActualHeight() );

    //============================//
    // Gaussian blur y rt1 to rt0 //
    //============================//
    SetRenderTargetAndViewPort( pRtQuarterSize0 , pSetup->width / 4 , pSetup->height / 4 );
    IMaterialVar *pBloomAmountVar = pMatBlurY->FindVar( "$bloomamount" , NULL );
    pBloomAmountVar->SetFloatValue( flBloomScale );
    pRenderContext->DrawScreenSpaceRectangle( pMatBlurY , 0 , 0 , nSrcWidth / 4 , nSrcHeight / 4 ,
                                              0 , 0 , ( float ) nSrcWidth / 4 - 1 , ( float ) nSrcHeight / 4 - 1 ,
                                              pRtQuarterSize1->GetActualWidth() , pRtQuarterSize1->GetActualHeight() );

    // Pop RT
    pRenderContext->PopRenderTargetAndViewport();

    {
        //=======================================================================================================//
        // At this point, pRtQuarterSize0 is filled with the fully colored glow around everything as solid glowy //
        // blobs. Now we need to stencil out the original objects by only writing pixels that have no            //
        // stencil bits set in the range we care about.                                                          //
        //=======================================================================================================//
        static IMaterial *pMatHaloAddToScreen = MaterialSystem->FindMaterial( "dev/halo_add_to_screen" , TEXTURE_GROUP_OTHER , true );

        // Do not fade the glows out at all (weight = 1.0)
        IMaterialVar *pDimVar = pMatHaloAddToScreen->FindVar( "$C0_X" , NULL );
        pDimVar->SetFloatValue( 1.0f );

        ShaderStencilState_t stencilState;
        stencilState.m_bEnable = true;
        stencilState.m_nWriteMask = 0; // We're not changing stencil
        stencilState.m_nReferenceValue = 1;
        stencilState.m_nTestMask = 1;
        stencilState.m_CompareFunc = SHADER_STENCILFUNC_NOTEQUAL;
        stencilState.m_PassOp = SHADER_STENCILOP_KEEP;
        stencilState.m_FailOp = SHADER_STENCILOP_KEEP;
        stencilState.m_ZFailOp = SHADER_STENCILOP_KEEP;
        pRenderContext->SetStencilState( stencilState );

        // Draw quad
        pRenderContext->DrawScreenSpaceRectangle( pMatHaloAddToScreen , 0 , 0 , nViewportWidth , nViewportHeight ,
                                                  0.0f , -0.5f , ( float ) nSrcWidth / 4 - 1 , ( float ) nSrcHeight / 4 - 1 ,
                                                  pRtQuarterSize1->GetActualWidth() ,
                                                  pRtQuarterSize1->GetActualHeight() );
    }

    // Done with all of our "advanced" 3D rendering.
    pRenderContext.SetStencilEnable( false );
}

void CGlowObjectManager::DrawModel( C_BaseEntity* pEntity )
{
    int iEntIndex = pEntity->entindex();

    bGlowingEntities[ iEntIndex ] = false;

    if ( !pEntity->ShouldDraw() )
        return;

    bGlowingEntities[ iEntIndex ] = true;

    RenderableInstance_t instance;
    instance.m_nAlpha = ( uint8 ) ( flAlpha[ iEntIndex ] * 255.0f );

    pEntity->DrawModel( STUDIO_RENDER | STUDIO_NOSHADOWS | STUDIO_TRANSPARENCY | STUDIO_SKIP_FLEXES | STUDIO_DONOTMODIFYSTENCILSTATE
                        | STUDIO_NOLIGHTING_OR_CUBEMAP | STUDIO_SKIP_DECALS , instance );

    C_BaseEntity *pAttachment = pEntity->FirstMoveChild();

    while ( pAttachment != NULL )
    {
        int iEntAttachementIndex = pAttachment->entindex();

        if ( pAttachment->ShouldDraw() )
        {
            bGlowingEntities[ iEntAttachementIndex ] = true;

            pAttachment->DrawModel( STUDIO_RENDER | STUDIO_NOSHADOWS | STUDIO_TRANSPARENCY | STUDIO_SKIP_FLEXES | STUDIO_DONOTMODIFYSTENCILSTATE
                                    | STUDIO_NOLIGHTING_OR_CUBEMAP | STUDIO_SKIP_DECALS , instance );
        }

        pAttachment = pAttachment->NextMovePeer();
    }
}