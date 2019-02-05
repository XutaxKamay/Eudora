#ifndef MESHBUILDER
#define MESHBUILDER
#pragma once

class IVertexBuffer;
class IIndexBuffer;
struct MeshInstanceData_t;
struct ShaderStencilState_t;

//-----------------------------------------------------------------------------
// Helper methods to create various standard index buffer types
//-----------------------------------------------------------------------------
extern void GenerateSequentialIndexBuffer( unsigned short* pIndices , int nIndexCount , int nFirstVertex );

extern void GenerateQuadIndexBuffer( unsigned short* pIndices , int nIndexCount , int nFirstVertex );

extern void GeneratePolygonIndexBuffer( unsigned short* pIndices , int nIndexCount , int nFirstVertex );

extern void GenerateLineStripIndexBuffer( unsigned short* pIndices , int nIndexCount , int nFirstVertex );

extern void GenerateLineLoopIndexBuffer( unsigned short* pIndices , int nIndexCount , int nFirstVertex );

class IRefCounted
{
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

class IMatRenderContext : public IRefCounted
{
public:
    virtual void				BeginRender() = 0;
    virtual void				EndRender() = 0;
    virtual void				Flush( bool flushHardware = false ) = 0;
    virtual void				BindLocalCubemap( ITexture *pTexture ) = 0;
    // pass in an ITexture (that is build with "rendertarget" "1") or
    // pass in NULL for the regular backbuffer.
    virtual void				SetRenderTarget( ITexture *pTexture ) = 0;
    virtual ITexture *			GetRenderTarget( void ) = 0;
    virtual void				GetRenderTargetDimensions( int &width , int &height ) const = 0;
    // Bind a material is current for rendering.
    virtual void				Bind( IMaterial *material , void *proxyData = 0 ) = 0;
    // Bind a lightmap page current for rendering.  You only have to
    // do this for materials that require lightmaps.
    virtual void				BindLightmapPage( int lightmapPageID ) = 0; // 10
                                                                            // inputs are between 0 and 1
    virtual void				DepthRange( float zNear , float zFar ) = 0;
    virtual void				ClearBuffers( bool bClearColor , bool bClearDepth , bool bClearStencil = false ) = 0;
    // read to a unsigned char rgb image.
    virtual void				ReadPixels( int x , int y , int width , int height , unsigned char* data , ImageFormat dstFormat ) = 0;
    virtual void				ReadPixelsAsync( int x , int y , int width , int height , unsigned char* data , ImageFormat dstFormat , ITexture* texture , Pointer threadEvent ) = 0;
    virtual int					ReadPixelsAsyncGetResult( int x , int y , int width , int height , unsigned char* data , ImageFormat dstFormat , Pointer threadEvent ) = 0;
    // Sets lighting
    virtual void				SetLightingState( const MaterialLightingState_t& state ) = 0;
    virtual void				SetLights( int nCount , const LightDesc_t *pLights ) = 0;
    // The faces of the cube are specified in the same order as cubemap textures
    virtual void				SetAmbientLightCube( Vector4D cube[ 6 ] ) = 0;
    // Blit the backbuffer to the framebuffer texture
    virtual void				CopyRenderTargetToTexture( ITexture *pTexture ) = 0;
    // Set the current texture that is a copy of the framebuffer.
    virtual void				SetFrameBufferCopyTexture( ITexture *pTexture , int textureIndex = 0 ) = 0; // 20
    virtual ITexture		   *GetFrameBufferCopyTexture( int textureIndex ) = 0;
    // end vertex array api

    // matrix api
    virtual void				MatrixMode( MaterialMatrixMode_t matrixMode ) = 0;
    virtual void				PushMatrix( void ) = 0;
    virtual void				PopMatrix( void ) = 0;
    virtual void				LoadMatrix( VMatrix const& matrix ) = 0;
    virtual void				LoadMatrix( Matrix3x4 const& matrix ) = 0;
    virtual void				MultMatrix( VMatrix const& matrix ) = 0;
    virtual void				MultMatrix( Matrix3x4 const& matrix ) = 0;
    virtual void				MultMatrixLocal( VMatrix const& matrix ) = 0;
    virtual void				MultMatrixLocal( Matrix3x4 const& matrix ) = 0; // 30
    virtual void				GetMatrix( MaterialMatrixMode_t matrixMode , VMatrix *matrix ) = 0;
    virtual void				GetMatrix( MaterialMatrixMode_t matrixMode , Matrix3x4 *matrix ) = 0;
    virtual void				LoadIdentity( void ) = 0;
    virtual void				Ortho( double left , double top , double right , double bottom , double zNear , double zFar ) = 0;
    virtual void				PerspectiveX( double fovx , double aspect , double zNear , double zFar ) = 0;
    virtual void				PickMatrix( int x , int y , int width , int height ) = 0;
    virtual void				Rotate( float angle , float x , float y , float z ) = 0;
    virtual void				Translate( float x , float y , float z ) = 0;
    virtual void				Scale( float x , float y , float z ) = 0;
    // end matrix api

    // Sets/gets the viewport
    virtual void				Viewport( int x , int y , int width , int height ) = 0; //40
    virtual void				GetViewport( int& x , int& y , int& width , int& height ) const = 0; //41
                                                                                                  // The cull mode
    virtual void				CullMode( MaterialCullMode_t cullMode ) = 0;
    virtual void				FlipCullMode( void ) = 0; //CW->CCW or CCW->CW, intended for mirror support where the view matrix is flipped horizontally
    virtual void				BeginGeneratingCSMs( void ) = 0;
    virtual void				EndGeneratingCSMs( void ) = 0;
    virtual void				PerpareForCascadeDraw( int some_int , float some_float1 , float some_float2 );
    // end matrix api

    // This could easily be extended to a general user clip plane
    virtual void				SetHeightClipMode( MaterialHeightClipMode_t nHeightClipMode ) = 0;
    // garymcthack : fog z is always used for heightclipz for now.
    virtual void				SetHeightClipZ( float z ) = 0;
    // Fog methods...
    virtual void				FogMode( MaterialFogMode_t fogMode ) = 0;
    virtual void				FogStart( float fStart ) = 0; // 50
    virtual void				FogEnd( float fEnd ) = 0;
    virtual void				SetFogZ( float fogZ ) = 0;
    virtual MaterialFogMode_t	GetFogMode( void ) = 0;
    virtual void				FogColor3f( float r , float g , float b ) = 0;
    virtual void				FogColor3fv( float const* rgb ) = 0;
    virtual void				FogColor3ub( unsigned char r , unsigned char g , unsigned char b ) = 0;
    virtual void				FogColor3ubv( unsigned char const* rgb ) = 0;
    virtual void				GetFogColor( unsigned char *rgb ) = 0;
    // Sets the number of bones for skinning
    virtual void				SetNumBoneWeights( int numBones ) = 0;
    // Creates/destroys Mesh
    virtual IMesh* CreateStaticMesh( VertexFormat_t fmt , const char *pTextureBudgetGroup , IMaterial * pMaterial = NULL , VertexStreamSpec_t *pStreamSpec = NULL ) = 0;
    virtual void DestroyStaticMesh( IMesh* mesh ) = 0; // 61
                                                       // Gets the dynamic mesh associated with the currently bound material
                                                       // note that you've got to render the mesh before calling this function
                                                       // a second time. Clients should *not* call DestroyStaticMesh on the mesh
                                                       // returned by this call.
                                                       // Use buffered = false if you want to not have the mesh be buffered,
                                                       // but use it instead in the following pattern:
                                                       //		meshBuilder.Begin
                                                       //		meshBuilder.End
                                                       //		Draw partial
                                                       //		Draw partial
                                                       //		Draw partial
                                                       //		meshBuilder.Begin
                                                       //		meshBuilder.End
                                                       //		etc
                                                       // Use Vertex or Index Override to supply a static vertex or index buffer
                                                       // to use in place of the dynamic buffers.
                                                       //
                                                       // If you pass in a material in pAutoBind, it will automatically bind the
                                                       // material. This can be helpful since you must bind the material you're
                                                       // going to use BEFORE calling GetDynamicMesh.
    virtual IMesh* GetDynamicMesh( bool buffered = true , IMesh* pVertexOverride = 0 , IMesh* pIndexOverride = 0 , IMaterial *pAutoBind = 0 ) = 0;
    // ------------ New Vertex/Index Buffer interface ----------------------------
    // Do we need support for bForceTempMesh and bSoftwareVertexShader?
    // I don't think we use bSoftwareVertexShader anymore. .need to look into bForceTempMesh.
    virtual IVertexBuffer *CreateStaticVertexBuffer( VertexFormat_t fmt , int nVertexCount , const char *pTextureBudgetGroup ) = 0;
    virtual IIndexBuffer *CreateStaticIndexBuffer( MaterialIndexFormat_t fmt , int nIndexCount , const char *pTextureBudgetGroup ) = 0;
    virtual void DestroyVertexBuffer( IVertexBuffer * ) = 0;
    virtual void DestroyIndexBuffer( IIndexBuffer * ) = 0;
    // Do we need to specify the stream here in the case of locking multiple dynamic VBs on different streams?
    virtual IVertexBuffer *GetDynamicVertexBuffer( int streamID , VertexFormat_t vertexFormat , bool bBuffered = true ) = 0;
    virtual IIndexBuffer *GetDynamicIndexBuffer() = 0;
    virtual void BindVertexBuffer( int streamID , IVertexBuffer *pVertexBuffer , int nOffsetInBytes , int nFirstVertex , int nVertexCount , VertexFormat_t fmt , int nRepetitions = 1 ) = 0;
    virtual void BindIndexBuffer( IIndexBuffer *pIndexBuffer , int nOffsetInBytes ) = 0; // 70
    virtual void Draw( MaterialPrimitiveType_t primitiveType , int firstIndex , int numIndices ) = 0; // 71
                                                                                                    // ------------ End ----------------------------
                                                                                                    // Selection mode methods
    virtual int  SelectionMode( bool selectionMode ) = 0;
    virtual void SelectionBuffer( unsigned int* pBuffer , int size ) = 0;
    virtual void ClearSelectionNames() = 0;
    virtual void LoadSelectionName( int name ) = 0;
    virtual void PushSelectionName( int name ) = 0;
    virtual void PopSelectionName() = 0; // 77
                                         // Sets the Clear Color for ClearBuffer....
    virtual void ClearColor3ub( unsigned char r , unsigned char g , unsigned char b ) = 0;
    virtual void ClearColor4ub( unsigned char r , unsigned char g , unsigned char b , unsigned char a ) = 0;
    // Allows us to override the depth buffer setting of a material
    virtual void OverrideDepthEnable( bool bEnable , bool bDepthEnable , bool bSomething = true ) = 0; // 80
                                                                             // FIXME: This is a hack required for NVidia/XBox, can they fix in drivers?
    virtual void DrawScreenSpaceQuad( IMaterial* pMaterial ) = 0;
    // For debugging and building recording files. This will stuff a token into the recording file,
    // then someone doing a playback can watch for the token.
    virtual void SyncToken( const char *pToken ) = 0;
    // FIXME: REMOVE THIS FUNCTION!
    // The only reason why it's not gone is because we're a week from ship when I found the bug in it
    // and everything's tuned to use it.
    // It's returning values which are 2x too big (it's returning sphere diameter x2)
    // Use ComputePixelDiameterOfSphere below in all new code instead.
    virtual float ComputePixelWidthOfSphere( const Vector& origin , float flRadius ) = 0;

    // Occlusion query support
    // Allocate and delete query objects.
    virtual OcclusionQueryObjectHandle_t CreateOcclusionQueryObject( void ) = 0;
    virtual void DestroyOcclusionQueryObject( OcclusionQueryObjectHandle_t ) = 0;
    // Bracket drawing with begin and end so that we can get counts next frame.
    virtual void BeginOcclusionQueryDrawing( OcclusionQueryObjectHandle_t ) = 0;
    virtual void EndOcclusionQueryDrawing( OcclusionQueryObjectHandle_t ) = 0;
    // Get the number of pixels rendered between begin and end on an earlier frame.
    // Calling this in the same frame is a huge perf hit!
    virtual int OcclusionQuery_GetNumPixelsRendered( OcclusionQueryObjectHandle_t ) = 0;
    virtual void SetFlashlightMode( bool bEnable ) = 0;
    virtual void SetFlashlightState( const Pointer state , const VMatrix &worldToTexture ) = 0; // 90
    virtual bool IsCascadedShadowMapping() const = 0;
    virtual void SetCascadedShadowMapping( bool bEnable ) = 0;
    virtual void SetCascadedShadowMappingState( const Pointer state , ITexture *pDepthTextureAtlas ) = 0;
    // Gets the current height clip mode
    virtual MaterialHeightClipMode_t GetHeightClipMode() = 0;
    // This returns the diameter of the sphere in pixels based on
    // the current model, view, + projection matrices and viewport.
    virtual float ComputePixelDiameterOfSphere( const Vector& vecAbsOrigin , float flRadius ) = 0;
    // By default, the material system applies the VIEW and PROJECTION matrices	to the user clip
    // planes (which are specified in world space) to generate projection-space user clip planes
    // Occasionally (for the particle system in hl2, for example), we want to override that
    // behavior and explictly specify a ViewProj transform for user clip planes
    virtual void EnableUserClipTransformOverride( bool bEnable ) = 0;
    virtual void UserClipTransform( const VMatrix &worldToView ) = 0;
    virtual bool GetFlashlightMode() const = 0;
    virtual bool IsCullingEnabledForSinglePassFlashlight() const = 0;
    virtual void EnableCullingForSinglePassFlashlight( bool bEnable ) = 0; // 100
                                                                           // Used to make the handle think it's never had a successful query before
    virtual void ResetOcclusionQueryObject( OcclusionQueryObjectHandle_t ) = 0;
    // Creates/destroys morph data associated w/ a particular material
    virtual IMorph *CreateMorph( MorphFormat_t format , const char *pDebugName ) = 0;
    virtual void DestroyMorph( IMorph *pMorph ) = 0;
    // Binds the morph data for use in rendering
    virtual void BindMorph( IMorph *pMorph ) = 0;
    // Sets flexweights for rendering
    virtual void SetFlexWeights( int nFirstWeight , int nCount , const Pointer pWeights ) = 0;
    // Allocates temp render data. Renderdata goes out of scope at frame end in multicore
    // Renderdata goes out of scope after refcount goes to zero in singlecore.
    // Locking/unlocking increases + decreases refcount
    virtual void* LockRenderData( int nSizeInBytes ) = 0;
    virtual void UnlockRenderData( void *pData ) = 0;
    // Typed version. If specified, pSrcData is copied into the locked memory.
    template<class T> T*  LockRenderDataTyped( int nCount , const T* pSrcData = NULL );
    // Temp render data gets immediately freed after it's all unlocked in single core.
    // This prevents it from being freed
    virtual void			AddRefRenderData() = 0;
    virtual void			ReleaseRenderData() = 0;
    // Returns whether a pointer is render data. NOTE: passing NULL returns true
    virtual bool			IsRenderData( const void *pData ) const = 0; // 110
                                                                         // Read w/ stretch to a host-memory buffer
    virtual void ReadPixelsAndStretch( Rect_t *pSrcRect , Rect_t *pDstRect , unsigned char *pBuffer , ImageFormat dstFormat , int nDstStride ) = 0;
    // Gets the window size
    virtual void GetWindowSize( int &width , int &height ) const = 0;
    // This function performs a texture map from one texture map to the render destination, doing
    // all the necessary pixel/texel coordinate fix ups. fractional values can be used for the
    // src_texture coordinates to get linear sampling - integer values should produce 1:1 mappings
    // for non-scaled operations.
    virtual void DrawScreenSpaceRectangle(
        IMaterial *pMaterial ,
        int destx , int desty ,
        int width , int height ,
        float src_texture_x0 , float src_texture_y0 ,	// which texel you want to appear at destx/y
        float src_texture_x1 , float src_texture_y1 ,	// which texel you want to appear at destx+width-1, desty+height-1
        int src_texture_width , int src_texture_height , // needed for fixup
        void *pClientRenderable = NULL ,
        int nXDice = 1 ,
        int nYDice = 1 ) = 0;

    virtual void LoadBoneMatrix( int boneIndex , const Matrix3x4& matrix ) = 0;
    // This version will push the current rendertarget + current viewport onto the stack
    virtual void PushRenderTargetAndViewport() = 0;
    // This version will push a new rendertarget + a maximal viewport for that rendertarget onto the stack
    virtual void PushRenderTargetAndViewport( ITexture *pTexture ) = 0;
    // This version will push a new rendertarget + a specified viewport onto the stack
    virtual void PushRenderTargetAndViewport( ITexture *pTexture , int nViewX , int nViewY , int nViewW , int nViewH ) = 0;
    // This version will push a new rendertarget + a specified viewport onto the stack
    virtual void PushRenderTargetAndViewport( ITexture *pTexture , ITexture *pDepthTexture , int nViewX , int nViewY , int nViewW , int nViewH ) = 0;
    // This will pop a rendertarget + viewport
    virtual void PopRenderTargetAndViewport( void ) = 0;
    // Binds a particular texture as the current lightmap
    virtual void BindLightmapTexture( ITexture *pLightmapTexture ) = 0; // 120
                                                                        // Blit a subrect of the current render target to another texture
    virtual void CopyRenderTargetToTextureEx( ITexture *pTexture , int nRenderTargetID , Rect_t *pSrcRect , Rect_t *pDstRect = NULL ) = 0;
    virtual void CopyTextureToRenderTargetEx( int nRenderTargetID , ITexture *pTexture , Rect_t *pSrcRect , Rect_t *pDstRect = NULL ) = 0;
    // Special off-center perspective matrix for DoF, MSAA jitter and poster rendering
    virtual void PerspectiveOffCenterX( double fovx , double aspect , double zNear , double zFar , double bottom , double top , double left , double right ) = 0;
    // Rendering parameters control special drawing modes withing the material system, shader
    // system, shaders, and engine. renderparm.h has their definitions.
    virtual void SetFloatRenderingParameter( int parm_number , float value ) = 0;
    virtual void SetIntRenderingParameter( int parm_number , int value ) = 0;
    virtual void SetVectorRenderingParameter( int parm_number , Vector const &value ) = 0;
    // stencil buffer operations.
    virtual void SetStencilState( const ShaderStencilState_t &state ) = 0; //127
    virtual void ClearStencilBufferRectangle( int xmin , int ymin , int xmax , int ymax , int value ) = 0;
    virtual void SetRenderTargetEx( int nRenderTargetID , ITexture *pTexture ) = 0;
    // rendering clip planes, beware that only the most recently pushed plane will actually be used in a sizeable chunk of hardware configurations
    // and that changes to the clip planes mid-frame while UsingFastClipping() is true will result unresolvable depth inconsistencies
    virtual void PushCustomClipPlane( const float *pPlane ) = 0; // 130
    virtual void PopCustomClipPlane( void ) = 0;
    // Returns the number of vertices + indices we can render using the dynamic mesh
    // Passing true in the second parameter will return the max # of vertices + indices
    // we can use before a flush is provoked and may return different values
    // if called multiple times in succession.
    // Passing false into the second parameter will return
    // the maximum possible vertices + indices that can be rendered in a single batch
    virtual void GetMaxToRender( IMesh *pMesh , bool bMaxUntilFlush , int *pMaxVerts , int *pMaxIndices ) = 0;
    // Returns the max possible vertices + indices to render in a single draw call
    virtual int GetMaxVerticesToRender( IMaterial *pMaterial ) = 0;
    virtual int GetMaxIndicesToRender() = 0;
    virtual void DisableAllLocalLights() = 0;
    virtual int CompareMaterialCombos( IMaterial *pMaterial1 , IMaterial *pMaterial2 , int lightMapID1 , int lightMapID2 ) = 0;
    virtual IMesh *GetFlexMesh() = 0;
    virtual void SetFlashlightStateEx( const Pointer state , const VMatrix &worldToTexture , ITexture *pFlashlightDepthTexture ) = 0;
    // Returns the currently bound local cubemap
    virtual ITexture *GetLocalCubemap() = 0;
    // This is a version of clear buffers which will only clear the buffer at pixels which pass the stencil test
    virtual void ClearBuffersObeyStencil( bool bClearColor , bool bClearDepth ) = 0;
    //enables/disables all entered clipping planes, returns the input from the last time it was called.
    virtual bool EnableClipping( bool bEnable ) = 0;
    //get fog distances entered with FogStart(), FogEnd(), and SetFogZ()
    virtual void GetFogDistances( float *fStart , float *fEnd , float *fFogZ ) = 0;
    // Hooks for firing PIX events from outside the Material System...
    virtual void BeginPIXEvent( unsigned long color , const char *szName ) = 0; // 142?
    virtual void EndPIXEvent() = 0;
    virtual void SetPIXMarker( unsigned long color , const char *szName ) = 0;

    // Batch API
    // from changelist 166623:
    // - replaced obtuse material system batch usage with an explicit and easier to thread API
    virtual void BeginBatch( IMesh* pIndices ) = 0;
    virtual void BindBatch( IMesh* pVertices , IMaterial *pAutoBind = NULL ) = 0;
    virtual void DrawBatch( MaterialPrimitiveType_t primType , int firstIndex , int numIndices ) = 0;
    virtual void EndBatch() = 0;

    // Raw access to the call queue, which can be NULL if not in a queued mode
    virtual Pointer GetCallQueue() = 0;

    // Returns the world-space camera position
    virtual void GetWorldSpaceCameraPosition( Vector *pCameraPos ) = 0;
    virtual void GetWorldSpaceCameraVectors( Vector *pVecForward , Vector *pVecRight , Vector *pVecUp ) = 0;

    // Set a linear vector color scale for all 3D rendering.
    // A value of [1.0f, 1.0f, 1.0f] should match non-tone-mapped rendering.
    virtual void				SetToneMappingScaleLinear( const Vector &scale ) = 0;
    virtual Vector				GetToneMappingScaleLinear( void ) = 0;

    virtual void				SetShadowDepthBiasFactors( float fSlopeScaleDepthBias , float fDepthBias ) = 0;

    // Apply stencil operations to every pixel on the screen without disturbing depth or color buffers
    virtual void				PerformFullScreenStencilOperation( void ) = 0;

    // Sets lighting origin for the current model (needed to convert directional lights to points)
    virtual void				SetLightingOrigin( Vector vLightingOrigin ) = 0;

    virtual void				PushScissorRect( int nLeft , int nTop , int nRight , int nBottom ) = 0;
    virtual void				PopScissorRect( void ) = 0;

    // Methods used to build the morph accumulator that is read from when HW morphing is enabled.
    virtual void				BeginMorphAccumulation() = 0;
    virtual void				EndMorphAccumulation() = 0;
    virtual void				AccumulateMorph( IMorph* pMorph , int nMorphCount , const Pointer pWeights ) = 0;

    virtual void				PushDeformation( Pointer const Deformation ) = 0;
    virtual void				PopDeformation() = 0;
    virtual int					GetNumActiveDeformations() const = 0;

    virtual bool				GetMorphAccumulatorTexCoord( Vector2D *pTexCoord , IMorph *pMorph , int nVertex ) = 0;

    // Version of get dynamic mesh that specifies a specific vertex format
    virtual IMesh*				GetDynamicMeshEx( VertexFormat_t vertexFormat , bool bBuffered = true ,
                                                  IMesh* pVertexOverride = 0 , IMesh* pIndexOverride = 0 , IMaterial *pAutoBind = 0 ) = 0;

    virtual void				FogMaxDensity( float flMaxDensity ) = 0;

#if defined( _X360 )
    //Seems best to expose GPR allocation to scene rendering code. 128 total to split between vertex/pixel shaders (pixel will be set to 128 - vertex). Minimum value of 16. More GPR's = more threads.
    virtual void				PushVertexShaderGPRAllocation( int iVertexShaderCount = 64 ) = 0;
    virtual void				PopVertexShaderGPRAllocation( void ) = 0;

    virtual void				FlushHiStencil() = 0;

    virtual void				Begin360ZPass( int nNumDynamicIndicesNeeded ) = 0;
    virtual void				End360ZPass() = 0;
#endif

    virtual void AntiAliasingHint( int a1 ) = 0;

    virtual IMaterial *GetCurrentMaterial() = 0;
    virtual int  GetCurrentNumBones() const = 0;
    virtual void *GetCurrentProxy() = 0;

    // Color correction related methods..
    // Client cannot call IColorCorrectionSystem directly because it is not thread-safe
    // FIXME: Make IColorCorrectionSystem threadsafe?
    virtual void EnableColorCorrection( bool bEnable ) = 0;
    virtual int AddLookup( const char *pName ) = 0;
    virtual bool RemoveLookup( int handle ) = 0;
    virtual void LockLookup( int handle ) = 0;
    virtual void LoadLookup( int handle , const char *pLookupName ) = 0;
    virtual void UnlockLookup( int handle ) = 0;
    virtual void SetLookupWeight( int handle , float flWeight ) = 0;
    virtual void ResetLookupWeights() = 0;
    virtual void SetResetable( int handle , bool bResetable ) = 0;

    //There are some cases where it's simply not reasonable to update the full screen depth texture (mostly on PC).
    //Use this to mark it as invalid and use a dummy texture for depth reads.
    virtual void SetFullScreenDepthTextureValidityFlag( bool bIsValid ) = 0;

    virtual void SetNonInteractiveLogoTexture( ITexture *pTexture , float flNormalizedX , float flNormalizedY , float flNormalizedW , float flNormalizedH ) = 0;

    // A special path used to tick the front buffer while loading on the 360
    virtual void SetNonInteractivePacifierTexture( ITexture *pTexture , float flNormalizedX , float flNormalizedY , float flNormalizedSize ) = 0;
    virtual void SetNonInteractiveTempFullscreenBuffer( ITexture *pTexture , MaterialNonInteractiveMode_t mode ) = 0;
    virtual void EnableNonInteractiveMode( MaterialNonInteractiveMode_t mode ) = 0;
    virtual void RefreshFrontBufferNonInteractive() = 0;

    // Flip culling state (swap CCW <-> CW)
    virtual void FlipCulling( bool bFlipCulling ) = 0;

    virtual void SetTextureRenderingParameter( int parm_number , ITexture *pTexture ) = 0;

    //only actually sets a bool that can be read in from shaders, doesn't do any of the legwork
    virtual void EnableSinglePassFlashlightMode( bool bEnable ) = 0;
    virtual bool SinglePassFlashlightModeEnabled() const = 0;

    // Draws instances with different meshes
    virtual void DrawInstances( int nInstanceCount , const MeshInstanceData_t *pInstance ) = 0;

    // Allows us to override the color/alpha write settings of a material
    virtual void pad2() = 0;
    virtual void OverrideAlphaWriteEnable( bool bOverrideEnable , bool bAlphaWriteEnable ) = 0;
    virtual void OverrideColorWriteEnable( bool bOverrideEnable , bool bColorWriteEnable ) = 0;

    virtual void ClearBuffersObeyStencilEx( bool bClearColor , bool bClearAlpha , bool bClearDepth ) = 0;

    // Subdivision surface interface
    virtual int GetSubDBufferWidth() = 0;
    virtual float* LockSubDBuffer( int nNumRows ) = 0;
    virtual void UnlockSubDBuffer() = 0;

    // Update current frame's game time for the shader api.
    virtual void UpdateGameTime( float flTime ) = 0;

    virtual void			PrintfVA( char *fmt , va_list vargs ) = 0;
    virtual void			Printf( char *fmt , ... ) = 0;
    virtual float			Knob( char *knobname , float *setvalue = NULL ) = 0;

    virtual void SetScaleformSlotViewport( int slot , int x , int y , int w , int h ) = 0;
    virtual void RenderScaleformSlot( int slot ) = 0;
    virtual void ForkRenderScaleformSlot( int slot ) = 0;
    virtual void JoinRenderScaleformSlot( int slot ) = 0;
    virtual void SetScaleformCursorViewport( int x , int y , int w , int h ) = 0;
    virtual void RenderScaleformCursor() = 0;

    virtual void AdvanceAndRenderScaleformSlot( int slot ) = 0;
    virtual void AdvanceAndRenderScaleformCursor( void ) = 0;

    virtual void SetRenderingPaint( bool bEnable ) = 0;
    virtual int FindLookup( const char *a1 ) = 0;

    virtual float GetFloatRenderingParameter( int param ) = 0;
    virtual int	 GetIntRenderingParameter( int param ) = 0;
    virtual ITexture* GetTextureRenderingParameter( int param ) = 0;
    virtual Vector GetVectorRenderingParameter( int param ) = 0;

    virtual void SwapBuffers() = 0;
    virtual void SetCurrentMaterialInternal( void* material ) = 0;
    virtual void* GetCurrentMaterialInternal( void );
    // ....
};

//==== Copyright © 1996-2005, Valve Corporation, All rights reserved. =======//
//
// Purpose:
//
//===========================================================================//

#ifndef IMESH_H
#define IMESH_H

#ifdef _WIN32
#pragma once
#endif

// SINGLE_INHERITANCE restricts the size of CBaseEntity pointers-to-member-functions to 4 bytes
struct inputdata_t;

#define Assert(x)
#define INVALID_TIME (FLT_MAX * -1.0) // Special value not rebased on save/load

typedef enum _fieldtypes
{
    FIELD_VOID = 0 ,			// No type or value
    FIELD_FLOAT ,			// Any floating point value
    FIELD_STRING ,			// A string ID (return from ALLOC_STRING)
    FIELD_VECTOR ,			// Any vector, QAngle, or AngularImpulse
    FIELD_QUATERNION ,		// A quaternion
    FIELD_INTEGER ,			// Any integer or enum
    FIELD_BOOLEAN ,			// boolean, implemented as an int, I may use this as a hint for compression
    FIELD_SHORT ,			// 2 byte integer
    FIELD_CHARACTER ,		// a byte
    FIELD_COLOR32 ,			// 8-bit per channel r,g,b,a (32bit color)
    FIELD_EMBEDDED ,			// an embedded object with a datadesc, recursively traverse and embedded class/structure based on an additional typedescription
    FIELD_CUSTOM ,			// special type that contains function pointers to it's read/write/parse functions
    FIELD_CLASSPTR ,			// CBaseEntity *
    FIELD_EHANDLE ,			// Entity handle
    FIELD_EDICT ,			// edict_t *
    FIELD_POSITION_VECTOR ,	// A world coordinate (these are fixed up across level transitions automagically)
    FIELD_TIME ,				// a floating point time (these are fixed up automatically too!)
    FIELD_TICK ,				// an integer tick count( fixed up similarly to time)
    FIELD_MODELNAME ,		// Engine string that is a model name (needs precache)
    FIELD_SOUNDNAME ,		// Engine string that is a sound name (needs precache)
    FIELD_INPUT ,			// a list of inputed data fields (all derived from CMultiInputVar)
    FIELD_FUNCTION ,			// A class function pointer (Think, Use, etc)
    FIELD_VMATRIX ,			// a vmatrix (output coords are NOT worldspace)
                            // NOTE: Use float arrays for local transformations that don't need to be fixed up.
                            FIELD_VMATRIX_WORLDSPACE ,// A VMatrix that maps some local space to world space (translation is fixed up on level transitions)
                            FIELD_MATRIX3X4_WORLDSPACE ,	// Matrix3x4 that maps some local space to world space (translation is fixed up on level transitions)
                            FIELD_INTERVAL ,			// a start and range floating point interval ( e.g., 3.2->3.6 == 3.2 and 0.4 )
                            FIELD_MODELINDEX ,		// a model index
                            FIELD_MATERIALINDEX ,	// a material index (using the material precache string table)
                            FIELD_VECTOR2D ,			// 2 floats
                            FIELD_INTEGER64 ,		// 64bit integer
                            FIELD_VECTOR4D ,			// 4 floats
                            FIELD_TYPECOUNT ,		// MUST BE LAST
} fieldtype_t;

//-----------------------------------------------------------------------------
// Field sizes...
//-----------------------------------------------------------------------------
template <int FIELD_TYPE>
class CDatamapFieldSizeDeducer
{
public:
    enum
    {
        SIZE = 0
    };

    static int FieldSize()
    {
        return 0;
    }
};

#define DECLARE_FIELD_SIZE( _fieldType, _fieldSize )	\
	template< > class CDatamapFieldSizeDeducer<_fieldType> { public: enum { SIZE = _fieldSize }; static int FieldSize() { return _fieldSize; } };
#define FIELD_SIZE( _fieldType )	CDatamapFieldSizeDeducer<_fieldType>::SIZE
#define FIELD_BITS( _fieldType )	(FIELD_SIZE( _fieldType ) * 8)

DECLARE_FIELD_SIZE( FIELD_FLOAT , sizeof( float ) )
DECLARE_FIELD_SIZE( FIELD_STRING , sizeof( int ) )
DECLARE_FIELD_SIZE( FIELD_VECTOR , 3 * sizeof( float ) )
DECLARE_FIELD_SIZE( FIELD_VECTOR2D , 2 * sizeof( float ) )
DECLARE_FIELD_SIZE( FIELD_VECTOR4D , 4 * sizeof( float ) )
DECLARE_FIELD_SIZE( FIELD_QUATERNION , 4 * sizeof( float ) )
DECLARE_FIELD_SIZE( FIELD_INTEGER , sizeof( int ) )
DECLARE_FIELD_SIZE( FIELD_INTEGER64 , sizeof( __int64 ) )
DECLARE_FIELD_SIZE( FIELD_BOOLEAN , sizeof( char ) )
DECLARE_FIELD_SIZE( FIELD_SHORT , sizeof( short ) )
DECLARE_FIELD_SIZE( FIELD_CHARACTER , sizeof( char ) )
DECLARE_FIELD_SIZE( FIELD_COLOR32 , sizeof( int ) )
DECLARE_FIELD_SIZE( FIELD_CLASSPTR , sizeof( int ) )
DECLARE_FIELD_SIZE( FIELD_EHANDLE , sizeof( int ) )
DECLARE_FIELD_SIZE( FIELD_EDICT , sizeof( int ) )
DECLARE_FIELD_SIZE( FIELD_POSITION_VECTOR , 3 * sizeof( float ) )
DECLARE_FIELD_SIZE( FIELD_TIME , sizeof( float ) )
DECLARE_FIELD_SIZE( FIELD_TICK , sizeof( int ) )
DECLARE_FIELD_SIZE( FIELD_MODELNAME , sizeof( int ) )
DECLARE_FIELD_SIZE( FIELD_SOUNDNAME , sizeof( int ) )
DECLARE_FIELD_SIZE( FIELD_INPUT , sizeof( int ) )
DECLARE_FIELD_SIZE( FIELD_FUNCTION , sizeof( int * ) )
DECLARE_FIELD_SIZE( FIELD_VMATRIX , 16 * sizeof( float ) )
DECLARE_FIELD_SIZE( FIELD_VMATRIX_WORLDSPACE , 16 * sizeof( float ) )
DECLARE_FIELD_SIZE( FIELD_MATRIX3X4_WORLDSPACE , 12 * sizeof( float ) )
DECLARE_FIELD_SIZE( FIELD_INTERVAL , 2 * sizeof( float ) )  // NOTE:  Must match interval.h definition
DECLARE_FIELD_SIZE( FIELD_MODELINDEX , sizeof( int ) )
DECLARE_FIELD_SIZE( FIELD_MATERIALINDEX , sizeof( int ) )

#define ARRAYSIZE2D(p)		(sizeof(p)/sizeof(p[0][0]))
#define SIZE_OF_ARRAY(p)	_ARRAYSIZE(p)

#define _FIELD(name,fieldtype,count,flags,mapname,tolerance)		{ fieldtype, #name, offsetof(classNameTypedef, name), count, flags, mapname, NULL, NULL, NULL, sizeof( ((classNameTypedef *)0)->name ), NULL, 0, tolerance }
#define DEFINE_FIELD_NULL	{ FIELD_VOID,0,0,0,0,0,0,0,0}
#define DEFINE_FIELD(name,fieldtype)			_FIELD(name, fieldtype, 1,  FTYPEDESC_SAVE, NULL, 0 )
#define DEFINE_FIELD_NOT_SAVED(name,fieldtype)			_FIELD(name, fieldtype, 1, 0, NULL, 0 )

#define DEFINE_KEYFIELD(name,fieldtype, mapname) _FIELD(name, fieldtype, 1,  FTYPEDESC_KEY | FTYPEDESC_SAVE, mapname, 0 )
#define DEFINE_KEYFIELD_NOT_SAVED(name,fieldtype, mapname)_FIELD(name, fieldtype, 1,  FTYPEDESC_KEY, mapname, 0 )
#define DEFINE_AUTO_ARRAY(name,fieldtype)		_FIELD(name, fieldtype, SIZE_OF_ARRAY(((classNameTypedef *)0)->name), FTYPEDESC_SAVE, NULL, 0 )
#define DEFINE_AUTO_ARRAY_KEYFIELD(name,fieldtype,mapname)		_FIELD(name, fieldtype, SIZE_OF_ARRAY(((classNameTypedef *)0)->name), FTYPEDESC_SAVE, mapname, 0 )
#define DEFINE_ARRAY(name,fieldtype, count)		_FIELD(name, fieldtype, count, FTYPEDESC_SAVE, NULL, 0 )
#define DEFINE_ARRAY_NOT_SAVED(name,fieldtype, count)		_FIELD(name, fieldtype, count, 0, NULL, 0 )
#define DEFINE_ENTITY_FIELD(name,fieldtype)			_FIELD(edict_t, name, fieldtype, 1,  FTYPEDESC_KEY | FTYPEDESC_SAVE, #name, 0 )
#define DEFINE_ENTITY_GLOBAL_FIELD(name,fieldtype)	_FIELD(edict_t, name, fieldtype, 1,  FTYPEDESC_KEY | FTYPEDESC_SAVE | FTYPEDESC_GLOBAL, #name, 0 )
#define DEFINE_GLOBAL_FIELD(name,fieldtype)	_FIELD(name, fieldtype, 1,  FTYPEDESC_GLOBAL | FTYPEDESC_SAVE, NULL, 0 )
#define DEFINE_GLOBAL_KEYFIELD(name,fieldtype, mapname)	_FIELD(name, fieldtype, 1,  FTYPEDESC_GLOBAL | FTYPEDESC_KEY | FTYPEDESC_SAVE, mapname, 0 )
#define DEFINE_CUSTOM_FIELD(name,datafuncs)	{ FIELD_CUSTOM, #name, offsetof(classNameTypedef, name), 1, FTYPEDESC_SAVE, NULL, datafuncs, NULL }
#define DEFINE_CUSTOM_KEYFIELD(name,datafuncs,mapname)	{ FIELD_CUSTOM, #name, offsetof(classNameTypedef, name), 1, FTYPEDESC_SAVE | FTYPEDESC_KEY, mapname, datafuncs, NULL }
#define DEFINE_AUTO_ARRAY2D(name,fieldtype)		_FIELD(name, fieldtype, ARRAYSIZE2D(((classNameTypedef *)0)->name), FTYPEDESC_SAVE, NULL, 0 )
// Used by byteswap datadescs
#define DEFINE_BITFIELD(name,fieldtype,bitcount)	DEFINE_ARRAY(name,fieldtype,((bitcount+FIELD_BITS(fieldtype)-1)&~(FIELD_BITS(fieldtype)-1)) / FIELD_BITS(fieldtype) )
#define DEFINE_INDEX(name,fieldtype)			_FIELD(name, fieldtype, 1,  FTYPEDESC_INDEX, NULL, 0 )

#define DEFINE_EMBEDDED( name )						\
	{ FIELD_EMBEDDED, #name, offsetof(classNameTypedef, name), 1, FTYPEDESC_SAVE, NULL, NULL, NULL, &(((classNameTypedef *)0)->name.m_DataMap), sizeof( ((classNameTypedef *)0)->name ), NULL, 0, 0.0f }

#define DEFINE_EMBEDDED_OVERRIDE( name, overridetype )	\
	{ FIELD_EMBEDDED, #name, offsetof(classNameTypedef, name), 1, FTYPEDESC_SAVE, NULL, NULL, NULL, &((overridetype *)0)->m_DataMap, sizeof( ((classNameTypedef *)0)->name ), NULL, 0, 0.0f }

#define DEFINE_EMBEDDEDBYREF( name )					\
	{ FIELD_EMBEDDED, #name, offsetof(classNameTypedef, name), 1, FTYPEDESC_SAVE | FTYPEDESC_PTR, NULL, NULL, NULL, &(((classNameTypedef *)0)->name->m_DataMap), sizeof( *(((classNameTypedef *)0)->name) ), NULL, 0, 0.0f }

#define DEFINE_EMBEDDED_ARRAY( name, count )			\
	{ FIELD_EMBEDDED, #name, offsetof(classNameTypedef, name), count, FTYPEDESC_SAVE, NULL, NULL, NULL, &(((classNameTypedef *)0)->name->m_DataMap), sizeof( ((classNameTypedef *)0)->name[0] ), NULL, 0, 0.0f  }

#define DEFINE_EMBEDDED_AUTO_ARRAY( name )			\
	{ FIELD_EMBEDDED, #name, offsetof(classNameTypedef, name), SIZE_OF_ARRAY( ((classNameTypedef *)0)->name ), FTYPEDESC_SAVE, NULL, NULL, NULL, &(((classNameTypedef *)0)->name->m_DataMap), sizeof( ((classNameTypedef *)0)->name[0] ), NULL, 0, 0.0f  }

#ifndef NO_ENTITY_PREDICTION

// FTYPEDESC_KEY tells the prediction copy system to report the full nameof the field when reporting errors
#define DEFINE_PRED_TYPEDESCRIPTION( name, fieldtype )						\
	{ FIELD_EMBEDDED, #name, offsetof(classNameTypedef, name), 1, FTYPEDESC_SAVE | FTYPEDESC_KEY, NULL, NULL, NULL, &fieldtype::m_PredMap }

#define DEFINE_PRED_TYPEDESCRIPTION_PTR( name, fieldtype )						\
	{ FIELD_EMBEDDED, #name, offsetof(classNameTypedef, name), 1, FTYPEDESC_SAVE | FTYPEDESC_PTR | FTYPEDESC_KEY, NULL, NULL, NULL, &fieldtype::m_PredMap }

#else

#define DEFINE_PRED_TYPEDESCRIPTION( name, fieldtype )		DEFINE_FIELD_NULL
#define DEFINE_PRED_TYPEDESCRIPTION_PTR( name, fieldtype )	DEFINE_FIELD_NULL

#endif

// Extensions to datamap.h macros for predicted entities only
#define DEFINE_PRED_FIELD(name,fieldtype, flags)			_FIELD(name, fieldtype, 1,  flags, NULL, 0.0f )
#define DEFINE_PRED_ARRAY(name,fieldtype, count,flags)		_FIELD(name, fieldtype, count, flags, NULL, 0.0f )
#define DEFINE_FIELD_NAME(localname,netname,fieldtype)		_FIELD(localname, fieldtype, 1,  0, #netname, 0.0f )
// Predictable macros, which include a tolerance for floating point values...
#define DEFINE_PRED_FIELD_TOL(name,fieldtype, flags,tolerance)			_FIELD(name, fieldtype, 1,  flags, NULL, tolerance )
#define DEFINE_PRED_ARRAY_TOL(name,fieldtype, count,flags,tolerance)		_FIELD(name, fieldtype, count, flags, NULL, tolerance)
#define DEFINE_FIELD_NAME_TOL(localname,netname,fieldtolerance)		_FIELD(localname, fieldtype, 1,  0, #netname, tolerance )

//#define DEFINE_DATA( name, fieldextname, flags ) _FIELD(name, fieldtype, 1,  flags, extname )

// INPUTS
#define DEFINE_INPUT( name, fieldtype, inputname ) { fieldtype, #name, offsetof(classNameTypedef, name), 1, FTYPEDESC_INPUT | FTYPEDESC_SAVE | FTYPEDESC_KEY,	inputname, NULL, NULL, NULL, sizeof( ((classNameTypedef *)0)->name ) }
#define DEFINE_INPUTFUNC( fieldtype, inputname, inputfunc ) { fieldtype, #inputfunc, NULL, 1, FTYPEDESC_INPUT, inputname, NULL, static_cast <inputfunc_t> (&classNameTypedef::inputfunc) }

// OUTPUTS
// the variable 'name' MUST BE derived from CBaseOutput
// we know the output type from the variable itself, so it doesn't need to be specified here
class ISaveRestoreOps;
#define DEFINE_OUTPUT( name, outputname )	{ FIELD_CUSTOM, #name, offsetof(classNameTypedef, name), 1, FTYPEDESC_OUTPUT | FTYPEDESC_SAVE | FTYPEDESC_KEY, outputname, eventFuncs }

// replaces EXPORT table for portability and non-DLL based systems (xbox)
#define DEFINE_FUNCTION_RAW( function, func_type )			{ FIELD_VOID, nameHolder.GenerateName(#function), NULL, 1, FTYPEDESC_FUNCTIONTABLE, NULL, NULL, (inputfunc_t)((func_type)(&classNameTypedef::function)) }
#define DEFINE_FUNCTION( function )			DEFINE_FUNCTION_RAW( function, inputfunc_t )

#define FTYPEDESC_GLOBAL			0x0001		// This field is masked for global entity save/restore
#define FTYPEDESC_SAVE				0x0002		// This field is saved to disk
#define FTYPEDESC_KEY				0x0004		// This field can be requested and written to by string name at load time
#define FTYPEDESC_INPUT				0x0008		// This field can be written to by string name at run time, and a function called
#define FTYPEDESC_OUTPUT			0x0010		// This field propogates it's value to all targets whenever it changes
#define FTYPEDESC_FUNCTIONTABLE		0x0020		// This is a table entry for a member function pointer
#define FTYPEDESC_PTR				0x0040		// This field is a pointer, not an embedded object
#define FTYPEDESC_OVERRIDE			0x0080		// The field is an override for one in a base class (only used by prediction system for now)

// Flags used by other systems (e.g., prediction system)
#define FTYPEDESC_INSENDTABLE		0x0100		// This field is present in a network SendTable
#define FTYPEDESC_PRIVATE			0x0200		// The field is local to the client or server only (not referenced by prediction code and not replicated by networking)
#define FTYPEDESC_NOERRORCHECK		0x0400		// The field is part of the prediction typedescription, but doesn't get compared when checking for errors

#define FTYPEDESC_MODELINDEX		0x0800		// The field is a model index (used for debugging output)

#define FTYPEDESC_INDEX				0x1000		// The field is an index into file data, used for byteswapping.

// These flags apply to C_BasePlayer derived objects only
#define FTYPEDESC_VIEW_OTHER_PLAYER		0x2000		// By default you can only view fields on the local player (yourself),
//   but if this is set, then we allow you to see fields on other players
#define FTYPEDESC_VIEW_OWN_TEAM			0x4000		// Only show this data if the player is on the same team as the local player
#define FTYPEDESC_VIEW_NEVER			0x8000		// Never show this field to anyone, even the local player (unusual)

#define TD_MSECTOLERANCE		0.001f		// This is a FIELD_FLOAT and should only be checked to be within 0.001 of the networked info

struct typedescription_t;

class ISaveRestoreOps;

//
// Function prototype for all input handlers.
//
typedef void ( CBaseEntity::*inputfunc_t )( inputdata_t &data );

struct datamap_t;
struct typedescription_t;

enum
{
    PC_NON_NETWORKED_ONLY = 0 ,
    PC_NETWORKED_ONLY ,

    PC_COPYTYPE_COUNT ,
    PC_EVERYTHING = PC_COPYTYPE_COUNT ,
};

enum
{
    TD_OFFSET_NORMAL = 0 ,
    TD_OFFSET_PACKED = 1 ,

    // Must be last
    TD_OFFSET_COUNT ,
};

struct typedescription_t
{
    fieldtype_t			fieldType;
    const char			*fieldName;
    int					fieldOffset; // Local offset value
    unsigned short		fieldSize;
    short				flags;
    // the name of the variable in the map/fgd data, or the name of the action
    const char			*externalName;
    // pointer to the function set for save/restoring of custom data types
    ISaveRestoreOps		*pSaveRestoreOps;
    // for associating function with string names
    inputfunc_t			inputFunc;
    // For embedding additional datatables inside this one
    datamap_t			*td;

    // Stores the actual member variable size in bytes
    int					fieldSizeInBytes;

    // FTYPEDESC_OVERRIDE point to first baseclass instance if chains_validated has occurred
    struct typedescription_t *override_field;

    // Used to track exclusion of baseclass fields
    int					override_count;

    // Tolerance for field errors for float fields
    float				fieldTolerance;

    // For raw fields (including children of embedded stuff) this is the flattened offset
    int					flatOffset[ TD_OFFSET_COUNT ];
    unsigned short		flatGroup;
};

// See predictioncopy.h for implementation and notes
struct optimized_datamap_t;

//-----------------------------------------------------------------------------
// Purpose: stores the list of objects in the hierarchy
//			used to iterate through an object's data descriptions
//-----------------------------------------------------------------------------
struct datamap_t
{
    typedescription_t	*dataDesc;
    int					dataNumFields;
    char const			*dataClassName;
    datamap_t			*baseMap;

    int					m_nPackedSize;
    optimized_datamap_t	*m_pOptimizedDataMap;
};

//-----------------------------------------------------------------------------
//
// Macros used to implement datadescs
//
#define DECLARE_FRIEND_DATADESC_ACCESS()	\
	template <typename T> friend void DataMapAccess(T *, datamap_t **p); \
	template <typename T> friend datamap_t *DataMapInit(T *);

#define DECLARE_SIMPLE_DATADESC() \
	static datamap_t m_DataMap; \
	static datamap_t *GetBaseMap(); \
	template <typename T> friend void DataMapAccess(T *, datamap_t **p); \
	template <typename T> friend datamap_t *DataMapInit(T *);

#define DECLARE_SIMPLE_DATADESC_INSIDE_NAMESPACE() \
	static datamap_t m_DataMap; \
	static datamap_t *GetBaseMap(); \
	template <typename T> friend void ::DataMapAccess(T *, datamap_t **p); \
	template <typename T> friend datamap_t *::DataMapInit(T *);

#define	DECLARE_DATADESC() \
	DECLARE_SIMPLE_DATADESC() \
	virtual datamap_t *GetDataDescMap( void );

#define BEGIN_DATADESC( className ) \
	datamap_t className::m_DataMap = { 0, 0, #className, NULL }; \
	datamap_t *className::GetDataDescMap( void ) { return &m_DataMap; } \
	datamap_t *className::GetBaseMap() { datamap_t *pResult; DataMapAccess((BaseClass *)NULL, &pResult); return pResult; } \
	BEGIN_DATADESC_GUTS( className )

#define BEGIN_DATADESC_NO_BASE( className ) \
	datamap_t className::m_DataMap = { 0, 0, #className, NULL }; \
	datamap_t *className::GetDataDescMap( void ) { return &m_DataMap; } \
	datamap_t *className::GetBaseMap() { return NULL; } \
	BEGIN_DATADESC_GUTS( className )

#define BEGIN_SIMPLE_DATADESC( className ) \
	datamap_t className::m_DataMap = { 0, 0, #className, NULL }; \
	datamap_t *className::GetBaseMap() { return NULL; } \
	BEGIN_DATADESC_GUTS( className )

#define BEGIN_SIMPLE_DATADESC_( className, BaseClass ) \
	datamap_t className::m_DataMap = { 0, 0, #className, NULL }; \
	datamap_t *className::GetBaseMap() { datamap_t *pResult; DataMapAccess((BaseClass *)NULL, &pResult); return pResult; } \
	BEGIN_DATADESC_GUTS( className )

#define BEGIN_DATADESC_GUTS( className ) \
	template <typename T> datamap_t *DataMapInit(T *); \
	template <> datamap_t *DataMapInit<className>( className * ); \
	namespace className##_DataDescInit \
	{ \
		datamap_t *g_DataMapHolder = DataMapInit( (className *)NULL ); /* This can/will be used for some clean up duties later */ \
	} \
	\
	template <> datamap_t *DataMapInit<className>( className * ) \
	{ \
		typedef className classNameTypedef; \
		static CDatadescGeneratedNameHolder nameHolder(#className); \
		className::m_DataMap.baseMap = className::GetBaseMap(); \
		static typedescription_t dataDesc[] = \
		{ \
		{ FIELD_VOID,0,0,0,0,0,0,0,0}, /* so you can define "empty" tables */

#define BEGIN_DATADESC_GUTS_NAMESPACE( className, nameSpace ) \
	template <typename T> datamap_t *nameSpace::DataMapInit(T *); \
	template <> datamap_t *nameSpace::DataMapInit<className>( className * ); \
	namespace className##_DataDescInit \
	{ \
		datamap_t *g_DataMapHolder = nameSpace::DataMapInit( (className *)NULL ); /* This can/will be used for some clean up duties later */ \
	} \
	\
	template <> datamap_t *nameSpace::DataMapInit<className>( className * ) \
	{ \
		typedef className classNameTypedef; \
		static CDatadescGeneratedNameHolder nameHolder(#className); \
		className::m_DataMap.baseMap = className::GetBaseMap(); \
		static typedescription_t dataDesc[] = \
		{ \
		{ FIELD_VOID,0,0,0,0,0,0,0,0}, /* so you can define "empty" tables */

#define END_DATADESC() \
		}; \
		\
		if ( sizeof( dataDesc ) > sizeof( dataDesc[0] ) ) \
		{ \
			classNameTypedef::m_DataMap.dataNumFields = SIZE_OF_ARRAY( dataDesc ) - 1; \
			classNameTypedef::m_DataMap.dataDesc 	  = &dataDesc[1]; \
		} \
		else \
		{ \
			classNameTypedef::m_DataMap.dataNumFields = 1; \
			classNameTypedef::m_DataMap.dataDesc 	  = dataDesc; \
		} \
		return &classNameTypedef::m_DataMap; \
	}

// used for when there is no data description
#define IMPLEMENT_NULL_SIMPLE_DATADESC( derivedClass ) \
	BEGIN_SIMPLE_DATADESC( derivedClass ) \
	END_DATADESC()

#define IMPLEMENT_NULL_SIMPLE_DATADESC_( derivedClass, baseClass ) \
	BEGIN_SIMPLE_DATADESC_( derivedClass, baseClass ) \
	END_DATADESC()

#define IMPLEMENT_NULL_DATADESC( derivedClass ) \
	BEGIN_DATADESC( derivedClass ) \
	END_DATADESC()

// helps get the offset of a bitfield
#define BEGIN_BITFIELD( name ) \
	union \
	{ \
		char name; \
		struct \
		{
#define END_BITFIELD() \
		}; \
	};

//-----------------------------------------------------------------------------
// Forward compatability with potential seperate byteswap datadescs

#define DECLARE_BYTESWAP_DATADESC() DECLARE_SIMPLE_DATADESC()
#define BEGIN_BYTESWAP_DATADESC(name) BEGIN_SIMPLE_DATADESC(name)
#define BEGIN_BYTESWAP_DATADESC_(name,base) BEGIN_SIMPLE_DATADESC_(name,base)
#define END_BYTESWAP_DATADESC() END_DATADESC()

//-----------------------------------------------------------------------------

template <typename T>
inline void DataMapAccess( T *ignored , datamap_t **p )
{
    *p = &T::m_DataMap;
}

//-----------------------------------------------------------------------------
// Material system interface version
//-----------------------------------------------------------------------------

// For now, vertex compression is simply "on or off" (for the sake of simplicity
// and MeshBuilder perf.), but later we may support multiple flavours.
enum VertexCompressionType_t
{
    // This indicates an uninitialized VertexCompressionType_t value
    VERTEX_COMPRESSION_INVALID = 0xFFFFFFFF ,

    // 'VERTEX_COMPRESSION_NONE' means that no elements of a vertex are compressed
    VERTEX_COMPRESSION_NONE = 0 ,

    // Currently (more stuff may be added as needed), 'VERTEX_COMPRESSION_ON' means:
    //  - if a vertex contains VERTEX_ELEMENT_NORMAL, this is compressed
    //    (see CVertexBuilder::CompressedNormal3f)
    //  - if a vertex contains VERTEX_ELEMENT_USERDATA4 (and a normal - together defining a tangent
    //    frame, with the binormal reconstructed in the vertex shader), this is compressed
    //    (see CVertexBuilder::CompressedUserData)
    //  - if a vertex contains VERTEX_ELEMENT_BONEWEIGHTSx, this is compressed
    //    (see CVertexBuilder::CompressedBoneWeight3fv)
    VERTEX_COMPRESSION_ON = 1
};

enum CSMQualityMode_t
{
    CSMQUALITY_VERY_LOW ,
    CSMQUALITY_LOW ,
    CSMQUALITY_MEDIUM ,
    CSMQUALITY_HIGH ,
    CSMQUALITY_TOTAL_MODES
};

enum CSMShaderMode_t
{
    CSMSHADERMODE_LOW_OR_VERY_LOW ,
    CSMSHADERMODE_MEDIUM ,
    CSMSHADERMODE_HIGH ,
    CSMSHADERMODE_ATIFETCH4 ,
    CSMSHADERMODE_TOTAL_MODES
};

enum ShadowFilterMode_t
{
    SHADOWFILTERMODE_DEFAULT ,
    NVIDIA_PCF = 0 ,
    ATI_NO_PCF_FETCH4 ,
    NVIDIA_PCF_CHEAP ,
    ATI_NOPCF ,
    GAMECONSOLE_NINE_TAP_PCF = 0 ,
    GAMECONSOLE_SINGLE_TAP_PCF ,
    SHADOWFILTERMODE_FIRST_CHEAP_MODE
};

// use DEFCONFIGMETHOD to define time-critical methods that we want to make just return constants
// on the 360, so that the checks will happen at compile time. Not all methods are defined this way
// - just the ones that I perceive as being called often in the frame interval.
#ifdef _X360
#define DEFCONFIGMETHOD( ret_type, method, xbox_return_value )		\
FORCEINLINE ret_type method const 									\
{																	\
	return xbox_return_value;										\
}

#else
#define DEFCONFIGMETHOD( ret_type, method, xbox_return_value )	\
virtual ret_type method const = 0;
#endif

//-----------------------------------------------------------------------------
// Material system configuration
//-----------------------------------------------------------------------------
class IMaterialSystemHardwareConfig
{
public:
    virtual int	 GetFrameBufferColorDepth() const = 0;
    virtual int  GetSamplerCount() const = 0;
    virtual bool HasSetDeviceGammaRamp() const = 0;
    virtual bool SupportsStaticControlFlow() const = 0;
    virtual VertexCompressionType_t SupportsCompressedVertices() const = 0;
    virtual int  MaximumAnisotropicLevel() const = 0;	// 0 means no anisotropic filtering
    virtual int  MaxTextureWidth() const = 0;
    virtual int  MaxTextureHeight() const = 0;
    virtual int	 TextureMemorySize() const = 0;
    virtual bool SupportsMipmappedCubemaps() const = 0;

    virtual int	 NumVertexShaderConstants() const = 0;
    virtual int	 NumPixelShaderConstants() const = 0;
    virtual int	 MaxNumLights() const = 0;
    virtual int	 MaxTextureAspectRatio() const = 0;
    virtual int	 MaxVertexShaderBlendMatrices() const = 0;
    virtual int	 MaxUserClipPlanes() const = 0;
    virtual bool UseFastClipping() const = 0;

    // This here should be the major item looked at when checking for compat
    // from anywhere other than the material system	shaders
    DEFCONFIGMETHOD( int , GetDXSupportLevel() , 98 );
    virtual const char *GetShaderDLLName() const = 0;

    virtual bool ReadPixelsFromFrontBuffer() const = 0;

    // Are dx dynamic textures preferred?
    virtual bool PreferDynamicTextures() const = 0;

    DEFCONFIGMETHOD( bool , SupportsHDR() , true );

    virtual bool NeedsAAClamp() const = 0;
    virtual bool NeedsATICentroidHack() const = 0;

    // This is the max dx support level supported by the card
    virtual int	 GetMaxDXSupportLevel() const = 0;

    // Does the card specify fog color in linear space when sRGBWrites are enabled?
    virtual bool SpecifiesFogColorInLinearSpace() const = 0;

    // Does the card support sRGB reads/writes?
    DEFCONFIGMETHOD( bool , SupportsSRGB() , true );

    virtual bool FakeSRGBWrite() const = 0;

    virtual bool CanDoSRGBReadFromRTs() const = 0;

    virtual bool SupportsGLMixedSizeTargets() const = 0;

    virtual bool IsAAEnabled() const = 0;	// Is antialiasing being used?

                                            // NOTE: Anything after this was added after shipping HL2.
    virtual int GetVertexSamplerCount() const = 0;
    virtual int GetMaxVertexTextureDimension() const = 0;

    virtual int  MaxTextureDepth() const = 0;

    virtual HDRType_t GetHDRType() const = 0;
    virtual HDRType_t GetHardwareHDRType() const = 0;

    virtual bool SupportsStreamOffset() const = 0;

    virtual int StencilBufferBits() const = 0;
    virtual int MaxViewports() const = 0;

    virtual void OverrideStreamOffsetSupport( bool bOverrideEnabled , bool bEnableSupport ) = 0;

    virtual ShadowFilterMode_t GetShadowFilterMode( bool bForceLowQualityShadows , bool bPS30 ) const = 0;

    virtual int NeedsShaderSRGBConversion() const = 0;

    DEFCONFIGMETHOD( bool , UsesSRGBCorrectBlending() , true );

    virtual bool HasFastVertexTextures() const = 0;
    virtual int MaxHWMorphBatchCount() const = 0;

    virtual bool SupportsHDRMode( HDRType_t nHDRMode ) const = 0;

    virtual bool GetHDREnabled( void ) const = 0;
    virtual void SetHDREnabled( bool bEnable ) = 0;

    virtual bool SupportsBorderColor( void ) const = 0;
    virtual bool SupportsFetch4( void ) const = 0;

    virtual float GetShadowDepthBias() const = 0;
    virtual float GetShadowSlopeScaleDepthBias() const = 0;

    virtual bool PreferZPrepass() const = 0;

    virtual bool SuppressPixelShaderCentroidHackFixup() const = 0;
    virtual bool PreferTexturesInHWMemory() const = 0;
    virtual bool PreferHardwareSync() const = 0;
    virtual bool ActualHasFastVertexTextures() const = 0;

    virtual bool SupportsShadowDepthTextures( void ) const = 0;
    virtual ImageFormat GetShadowDepthTextureFormat( void ) const = 0;
    virtual ImageFormat GetHighPrecisionShadowDepthTextureFormat( void ) const = 0;
    virtual ImageFormat GetNullTextureFormat( void ) const = 0;
    virtual int	GetMinDXSupportLevel() const = 0;
    virtual bool IsUnsupported() const = 0;

    // Backward compat for stdshaders
#if defined ( STDSHADER_DBG_DLL_EXPORT ) || defined( STDSHADER_DX9_DLL_EXPORT )
    inline bool SupportsPixelShaders_2_b() const
    {
        return GetDXSupportLevel() >= 92;
    }
#endif

    virtual float GetLightMapScaleFactor() const = 0;
    virtual bool SupportsCascadedShadowMapping() const = 0;
    virtual CSMQualityMode_t GetCSMQuality() const = 0;
    virtual bool SupportsBilinearPCFSampling() const = 0;
    virtual CSMShaderMode_t GetCSMShaderMode( CSMQualityMode_t nQualityLevel ) const = 0;
};

#include <float.h>
#include <string.h>

#ifdef OSX
// leaving this disabled while we test out EXT_vertex_array_bgra on 10.6.4 drivers
//#define	OPENGL_SWAP_COLORS	defined
#endif

//-----------------------------------------------------------------------------
// forward declarations
//-----------------------------------------------------------------------------

template <class T>
class CBaseAutoPtr
{
public:
    CBaseAutoPtr() : m_pObject( 0 )
    {}
    CBaseAutoPtr( T *pFrom ) : m_pObject( pFrom )
    {}

    operator const void *( ) const
    {
        return m_pObject;
    }
    operator void *( )
    {
        return m_pObject;
    }

    operator const T *( ) const
    {
        return m_pObject;
    }
    operator const T *( )
    {
        return m_pObject;
    }
    operator T *( )
    {
        return m_pObject;
    }

    int			operator=( int i )
    {
        m_pObject = 0; return 0;
    }
    T *			operator=( T *p )
    {
        m_pObject = p; return p;
    }

    bool        operator !() const
    {
        return ( !m_pObject );
    }
    bool        operator!=( int i ) const
    {
        return ( m_pObject != NULL );
    }
    bool		operator==( const void *p ) const
    {
        return ( m_pObject == p );
    }
    bool		operator!=( const void *p ) const
    {
        return ( m_pObject != p );
    }
    bool		operator==( T *p ) const
    {
        return operator==( ( void * ) p );
    }
    bool		operator!=( T *p ) const
    {
        return operator!=( ( void * ) p );
    }
    bool		operator==( const CBaseAutoPtr<T> &p ) const
    {
        return operator==( ( const void * ) p );
    }
    bool		operator!=( const CBaseAutoPtr<T> &p ) const
    {
        return operator!=( ( const void * ) p );
    }

    T *  		operator->()
    {
        return m_pObject;
    }
    T &  		operator *()
    {
        return *m_pObject;
    }
    T ** 		operator &()
    {
        return &m_pObject;
    }

    const T *   operator->() const
    {
        return m_pObject;
    }
    const T &   operator *() const
    {
        return *m_pObject;
    }
    T * const * operator &() const
    {
        return &m_pObject;
    }

protected:
    CBaseAutoPtr( const CBaseAutoPtr<T> &from ) : m_pObject( from.m_pObject )
    {}
    void operator=( const CBaseAutoPtr<T> &from )
    {
        m_pObject = from.m_pObject;
    }

    T *m_pObject;
};

template <class T>
class CRefPtr : public CBaseAutoPtr<T>
{
    typedef CBaseAutoPtr<T> BaseClass;
public:
    CRefPtr()
    {}
    CRefPtr( T *pInit ) : BaseClass( pInit )
    {}
    CRefPtr( const CRefPtr<T> &from ) : BaseClass( from )
    {}
    ~CRefPtr()
    {
        if ( BaseClass::m_pObject ) BaseClass::m_pObject->Release();
    }

    void operator=( const CRefPtr<T> &from )
    {
        BaseClass::operator=( from );
    }

    int operator=( int i )
    {
        return BaseClass::operator=( i );
    }
    T *operator=( T *p )
    {
        return BaseClass::operator=( p );
    }

    operator bool() const
    {
        return !BaseClass::operator!();
    }
    operator bool()
    {
        return !BaseClass::operator!();
    }

    void SafeRelease()
    {
        if ( BaseClass::m_pObject ) BaseClass::m_pObject->Release(); BaseClass::m_pObject = 0;
    }
    void AssignAddRef( T *pFrom )
    {
        SafeRelease(); if ( pFrom ) pFrom->AddRef(); BaseClass::m_pObject = pFrom;
    }
    void AddRefAssignTo( T *&pTo )
    {
        ::SafeRelease( pTo ); if ( BaseClass::m_pObject ) BaseClass::m_pObject->AddRef(); pTo = BaseClass::m_pObject;
    }
};
class CMatRenderContextPtr : public CRefPtr < IMatRenderContext >
{
    typedef CRefPtr<IMatRenderContext> BaseClass;
public:
    CMatRenderContextPtr()
    {}

    CMatRenderContextPtr( IMatRenderContext *pInit ) : BaseClass( pInit )
    {
        if ( BaseClass::m_pObject )
            BaseClass::m_pObject->BeginRender();
    }

    CMatRenderContextPtr( IMaterialSystem *pFrom ) : BaseClass( pFrom->GetRenderContext() )
    {
        if ( BaseClass::m_pObject )
            BaseClass::m_pObject->BeginRender();
    }

    ~CMatRenderContextPtr()
    {
        if ( BaseClass::m_pObject )
            BaseClass::m_pObject->EndRender();
    }

    IMatRenderContext *operator=( IMatRenderContext *p )
    {
        if ( p )
            p->BeginRender();
        return BaseClass::operator=( p );
    }

    void SafeRelease()
    {
        if ( BaseClass::m_pObject )
            BaseClass::m_pObject->EndRender();
        BaseClass::SafeRelease();
    }

    void AssignAddRef( IMatRenderContext *pFrom )
    {
        if ( BaseClass::m_pObject )
            BaseClass::m_pObject->EndRender();
        BaseClass::AssignAddRef( pFrom );
        BaseClass::m_pObject->BeginRender();
    }

    void GetFrom( IMaterialSystem *pFrom )
    {
        AssignAddRef( pFrom->GetRenderContext() );
    }

    void SetStencilEnable( bool bEnable )
    {
        ShaderStencilState_t stencilState;
        stencilState.m_bEnable = bEnable;
        BaseClass::m_pObject->SetStencilState( stencilState );
    }

private:
    CMatRenderContextPtr( const CMatRenderContextPtr &from );
    void operator=( const CMatRenderContextPtr &from );
};

class IMaterial;
class CMeshBuilder;
class IMaterialVar;
typedef uint64 VertexFormat_t;

//-----------------------------------------------------------------------------
// The Vertex Buffer interface
//-----------------------------------------------------------------------------
enum
{
    VERTEX_MAX_TEXTURE_COORDINATES = 8 ,
    BONE_MATRIX_INDEX_INVALID = 255
};

// Internal maximums for sizes. Don't use directly, use IMaterialSystem::GetMaxToRender()
enum
{
    INDEX_BUFFER_SIZE = 32768 ,
    DYNAMIC_VERTEX_BUFFER_MEMORY = ( 1024 + 512 ) * 1024 ,
    DYNAMIC_VERTEX_BUFFER_MEMORY_SMALL = 384 * 1024 , // Only allocate this much during map transitions
};

// Vertex fields must be written in well-defined order to achieve write combining,
// which is a perf booster
enum WriteCombineOrdering_t
{
    MB_FIELD_NONE = -1 ,
    MB_FIELD_POSITION = 0 ,
    MB_FIELD_BONE_WEIGHTS ,
    MB_FIELD_BONE_INDEX ,
    MB_FIELD_NORMAL ,
    MB_FIELD_COLOR ,
    MB_FIELD_SPECULAR ,
    MB_FIELD_TEXCOORD_FIRST ,
    MB_FIELD_TEXCOORD_LAST = MB_FIELD_TEXCOORD_FIRST + VERTEX_MAX_TEXTURE_COORDINATES - 1 ,
    MB_FIELD_TANGENT_S ,
    MB_FIELD_TANGENT_T ,
    MB_FIELD_USERDATA ,
};

#define MB_FIELD_TEXCOORD( nStage ) ( MB_FIELD_TEXCOORD_FIRST + ( nStage ) )

struct VertexDesc_t
{
    // These can be set to zero if there are pointers to dummy buffers, when the
    // actual buffer format doesn't contain the data but it needs to be safe to
    // use all the CMeshBuilder functions.
    int	m_VertexSize_Position;
    int m_VertexSize_BoneWeight;
    int m_VertexSize_BoneMatrixIndex;
    int	m_VertexSize_Normal;
    int	m_VertexSize_Color;
    int	m_VertexSize_Specular;
    int m_VertexSize_TexCoord[ VERTEX_MAX_TEXTURE_COORDINATES ];
    int m_VertexSize_TangentS;
    int m_VertexSize_TangentT;
    int m_VertexSize_Wrinkle;

    int m_VertexSize_UserData;

    int m_ActualVertexSize;	// Size of the vertices.. Some of the m_VertexSize_ elements above
                            // are set to this value and some are set to zero depending on which
                            // fields exist in a buffer's vertex format.

                            // The type of compression applied to this vertex data
    VertexCompressionType_t m_CompressionType;

    // Number of bone weights per vertex...
    int m_NumBoneWeights;

    // Pointers to our current vertex data
    float			*m_pPosition;

    float			*m_pBoneWeight;

#ifndef NEW_SKINNING
    unsigned char	*m_pBoneMatrixIndex;
#else
    float			*m_pBoneMatrixIndex;
#endif

    float			*m_pNormal;

    unsigned char	*m_pColor;
    unsigned char	*m_pSpecular;
    float			*m_pTexCoord[ VERTEX_MAX_TEXTURE_COORDINATES ];

    // Tangent space *associated with one particular set of texcoords*
    float			*m_pTangentS;
    float			*m_pTangentT;

    float			*m_pWrinkle;

    // user data
    float			*m_pUserData;

    // The first vertex index (used for buffered vertex buffers, or cards that don't support stream offset)
    short	m_nFirstVertex;

    // The offset in bytes of the memory we're writing into
    // from the start of the D3D buffer (will be 0 for static meshes)
    unsigned int	m_nOffset;
};

struct IndexDesc_t
{
    // Pointers to the index data
    unsigned short	*m_pIndices;

    // The offset in bytes of the memory we're writing into
    // from the start of the D3D buffer (will be 0 for static meshes)
    unsigned int	m_nOffset;

    // The first index (used for buffered index buffers, or cards that don't support stream offset)
    unsigned int	m_nFirstIndex;

    // 1 if the device is active, 0 if the device isn't active.
    // Faster than doing if checks for null m_pIndices if someone is
    // trying to write the m_pIndices while the device is inactive.
    unsigned short	m_nIndexSize;
};

//-----------------------------------------------------------------------------
// The Mesh memory descriptor
//-----------------------------------------------------------------------------
struct MeshDesc_t : public VertexDesc_t , public IndexDesc_t
{};

//-----------------------------------------------------------------------------
// Standard vertex formats for models
//-----------------------------------------------------------------------------
struct ModelVertexDX8_t
{
    Vector			m_vecPosition;
    Vector			m_vecNormal;
    Vector2D		m_vecTexCoord;
    Vector4D		m_vecUserData;
};

//---------------------------------------------------------------------------------------
// Thin Vertex format for use with ATI tessellator in quad mode
//---------------------------------------------------------------------------------------
struct QuadTessVertex_t
{
    Vector4D	m_vTangent;		// last component is Binormal flip and Wrinkle weight
    Vector4D	m_vUV01;		// UV coordinates for points Interior (0), and Parametric V Edge (1)
    Vector4D	m_vUV23;		// UV coordinates for points Parametric U Edge (2), and Corner (3)
};

struct MeshBoneRemap_t   // see BoneStateChangeHeader_t
{
    DECLARE_BYTESWAP_DATADESC();
    int m_nActualBoneIndex;
    int m_nSrcBoneIndex;
};

struct MeshInstanceData_t
{
    int						m_nIndexOffset;
    int						m_nIndexCount;
    int						m_nBoneCount;
    MeshBoneRemap_t *		m_pBoneRemap;		// there are bone count of these, they index into pose to world
    Matrix3x4	*			m_pPoseToWorld;	// transforms for the *entire* model, indexed into by m_pBoneIndex. Potentially more than bone count of these
    const ITexture *		m_pEnvCubemap;
    MaterialLightingState_t *m_pLightingState;
    MaterialPrimitiveType_t m_nPrimType;
    const IVertexBuffer	*	m_pVertexBuffer;
    int						m_nVertexOffsetInBytes;
    const IIndexBuffer *	m_pIndexBuffer;
    const IVertexBuffer	*	m_pColorBuffer;
    int						m_nColorVertexOffsetInBytes;
    ShaderStencilState_t *	m_pStencilState;
    Vector4D				m_DiffuseModulation;
};

struct MeshBuffersAllocationSettings_t
{
    uint32 m_uiIbUsageFlags;
};

//-----------------------------------------------------------------------------
// Utility methods for buffer builders
//-----------------------------------------------------------------------------
inline float *OffsetFloatPointer( float *pBufferPointer , int nVertexCount , int vertexSize )
{
    return reinterpret_cast< float * >(
        reinterpret_cast< unsigned char * >( pBufferPointer ) +
        nVertexCount * vertexSize );
}

inline const float *OffsetFloatPointer( const float *pBufferPointer , int nVertexCount , int vertexSize )
{
    return reinterpret_cast< const float* >(
        reinterpret_cast< unsigned char const* >( pBufferPointer ) +
        nVertexCount * vertexSize );
}

inline void IncrementFloatPointer( float* &pBufferPointer , int vertexSize )
{
    pBufferPointer = reinterpret_cast< float* >( reinterpret_cast< unsigned char* >( pBufferPointer ) + vertexSize );
}

//-----------------------------------------------------------------------------
// Used in lists of indexed primitives.
//-----------------------------------------------------------------------------
class CPrimList
{
public:
    CPrimList();
    CPrimList( int nFirstIndex , int nIndexCount );

    int			m_FirstIndex;
    int			m_NumIndices;
};

inline CPrimList::CPrimList()
{}

inline CPrimList::CPrimList( int nFirstIndex , int nIndexCount )
{
    m_FirstIndex = nFirstIndex;
    m_NumIndices = nIndexCount;
}

class IVertexBuffer
{
public:
    // NOTE: The following two methods are only valid for static vertex buffers
    // Returns the number of vertices and the format of the vertex buffer
    virtual int VertexCount() const = 0;
    virtual VertexFormat_t GetVertexFormat() const = 0;

    // Is this vertex buffer dynamic?
    virtual bool IsDynamic() const = 0;

    // NOTE: For dynamic vertex buffers only!
    // Casts the memory of the dynamic vertex buffer to the appropriate type
    virtual void BeginCastBuffer( VertexFormat_t format ) = 0;
    virtual void EndCastBuffer() = 0;

    // Returns the number of vertices that can still be written into the buffer
    virtual int GetRoomRemaining() const = 0;

    virtual bool Lock( int nVertexCount , bool bAppend , VertexDesc_t &desc ) = 0;
    virtual void Unlock( int nVertexCount , VertexDesc_t &desc ) = 0;

    // Spews the mesh data
    virtual void Spew( int nVertexCount , const VertexDesc_t &desc ) = 0;

    // Call this in debug mode to make sure our data is good.
    virtual void ValidateData( int nVertexCount , const VertexDesc_t & desc ) = 0;
};

class IIndexBuffer
{
public:
    // NOTE: The following two methods are only valid for static index buffers
    // Returns the number of indices and the format of the index buffer
    virtual int IndexCount() const = 0;
    virtual MaterialIndexFormat_t IndexFormat() const = 0;

    // Is this index buffer dynamic?
    virtual bool IsDynamic() const = 0;

    // NOTE: For dynamic index buffers only!
    // Casts the memory of the dynamic index buffer to the appropriate type
    virtual void BeginCastBuffer( MaterialIndexFormat_t format ) = 0;
    virtual void EndCastBuffer() = 0;

    // Returns the number of indices that can still be written into the buffer
    virtual int GetRoomRemaining() const = 0;

    // Locks, unlocks the index buffer
    virtual bool Lock( int nMaxIndexCount , bool bAppend , IndexDesc_t &desc ) = 0;
    virtual void Unlock( int nWrittenIndexCount , IndexDesc_t &desc ) = 0;

    // FIXME: Remove this!! Here only for backward compat on IMesh
    // Locks, unlocks the index buffer for modify
    virtual void ModifyBegin( bool bReadOnly , int nFirstIndex , int nIndexCount , IndexDesc_t& desc ) = 0;
    virtual void ModifyEnd( IndexDesc_t& desc ) = 0;

    // Spews the mesh data
    virtual void Spew( int nIndexCount , const IndexDesc_t &desc ) = 0;

    // Ensures the data in the index buffer is valid
    virtual void ValidateData( int nIndexCount , const IndexDesc_t &desc ) = 0;

    // For backward compat to IMesh
    virtual IMesh* GetMesh() = 0;
};

class ICachedPerFrameMeshData
{
public:
    virtual void Free() = 0;
};

//-----------------------------------------------------------------------------
// Interface to the mesh - needs to contain an IVertexBuffer and an IIndexBuffer to emulate old mesh behavior
//-----------------------------------------------------------------------------
class IMesh : public IVertexBuffer , public IIndexBuffer
{
public:
    // -----------------------------------

    // Sets/gets the primitive type
    virtual void SetPrimitiveType( MaterialPrimitiveType_t type ) = 0;

    // Draws the mesh
    virtual void Draw( int firstIndex = -1 , int numIndices = 0 ) = 0;

    virtual void SetColorMesh( IMesh *pColorMesh , int nVertexOffset ) = 0;

    // Draw a list of (lists of) primitives. Batching your lists together that use
    // the same lightmap, material, vertex and index buffers with multipass shaders
    // can drastically reduce state-switching overhead.
    // NOTE: this only works with STATIC meshes.
    virtual void Draw( CPrimList *pLists , int nLists ) = 0;

    // Copy verts and/or indices to a mesh builder. This only works for temp meshes!
    virtual void CopyToMeshBuilder(
        int iStartVert ,		// Which vertices to copy.
        int nVerts ,
        int iStartIndex ,	// Which indices to copy.
        int nIndices ,
        int indexOffset ,	// This is added to each index.
        CMeshBuilder &builder ) = 0;

    // Spews the mesh data
    virtual void Spew( int numVerts , int numIndices , const MeshDesc_t &desc ) = 0;

    // Call this in debug mode to make sure our data is good.
    virtual void ValidateData( int numVerts , int numIndices , const MeshDesc_t &desc ) = 0;

    // New version
    // Locks/unlocks the mesh, providing space for numVerts and numIndices.
    // numIndices of -1 means don't lock the index buffer...
    virtual void LockMesh( int numVerts , int numIndices , MeshDesc_t &desc , MeshBuffersAllocationSettings_t *pSettings ) = 0;
    virtual void ModifyBegin( int firstVertex , int numVerts , int firstIndex , int numIndices , MeshDesc_t& desc ) = 0;
    virtual void ModifyEnd( MeshDesc_t& desc ) = 0;
    virtual void UnlockMesh( int numVerts , int numIndices , MeshDesc_t &desc ) = 0;

    virtual void ModifyBeginEx( bool bReadOnly , int firstVertex , int numVerts , int firstIndex , int numIndices , MeshDesc_t &desc ) = 0;

    virtual void SetFlexMesh( IMesh *pMesh , int nVertexOffset ) = 0;

    virtual void DisableFlexMesh() = 0;

    virtual void MarkAsDrawn() = 0;

    // NOTE: I chose to create this method strictly because it's 2 days to code lock
    // and I could use the DrawInstances technique without a larger code change
    // Draws the mesh w/ modulation.
    virtual void DrawModulated( const Vector4D &vecDiffuseModulation , int firstIndex = -1 , int numIndices = 0 ) = 0;

    virtual unsigned int ComputeMemoryUsed() = 0;

    virtual void *AccessRawHardwareDataStream( uint8 nRawStreamIndex , uint32 numBytes , uint32 uiFlags , void *pvContext ) = 0;

    virtual ICachedPerFrameMeshData *GetCachedPerFrameMeshData() = 0;
    virtual void ReconstructFromCachedPerFrameMeshData( ICachedPerFrameMeshData *pData ) = 0;
};

inline VertexCompressionType_t CompressionType( VertexFormat_t vertexFormat )
{
    // This is trivial now, but we may add multiple flavors of compressed vertex later on
    if ( vertexFormat & VERTEX_FORMAT_COMPRESSED )
        return VERTEX_COMPRESSION_ON;
    else
        return VERTEX_COMPRESSION_NONE;
}

//-----------------------------------------------------------------------------
// This is used to read vertex and index data out of already-created meshes.
// xbox uses this a lot so it doesn't have to store sysmem backups of the
// vertex data.
//-----------------------------------------------------------------------------
class CBaseMeshReader : protected MeshDesc_t
{
    // Initialization.
public:

    CBaseMeshReader();
    ~CBaseMeshReader();

    // Use BeginRead/EndRead to initialize the mesh reader.
    void BeginRead(
        IMesh* pMesh ,
        int firstVertex = 0 ,
        int numVertices = 0 ,
        int firstIndex = 0 ,
        int numIndices = 0 );

    void EndRead();

    // PC can use this if it stores its own copy of meshes around, in case
    // locking static buffers is too costly.
    void BeginRead_Direct( const MeshDesc_t &desc , int numVertices , int nIndices );

    // Resets the mesh builder so it points to the start of everything again
    void Reset();

protected:
    IMesh * m_pMesh;
    int m_MaxVertices;
    int m_MaxIndices;
};

// A bunch of accessors for the data that CBaseMeshReader sets up.
class CMeshReader : public CBaseMeshReader
{
public:
    // Access to vertex data.
public:
    int NumIndices() const;
    unsigned short Index( int index ) const;

    const Vector& Position( int iVertex ) const;

    unsigned int Color( int iVertex ) const;

    const float *TexCoord( int iVertex , int stage ) const;
    void TexCoord2f( int iVertex , int stage , float &s , float &t ) const;
    const Vector2D& TexCoordVector2D( int iVertex , int stage ) const;

    int NumBoneWeights() const;
    float Wrinkle( int iVertex ) const;

    const Vector &Normal( int iVertex ) const;
    void Normal( int iVertex , Vector &vNormal ) const;

    const Vector &TangentS( int iVertex ) const;
    const Vector &TangentT( int iVertex ) const;
    float BoneWeight( int iVertex ) const;

#ifdef NEW_SKINNING
    float* BoneMatrix( int iVertex ) const;
#else
    unsigned char* BoneMatrix( int iVertex ) const;
#endif
};

//-----------------------------------------------------------------------------
// CBaseMeshReader implementation.
//-----------------------------------------------------------------------------

inline CBaseMeshReader::CBaseMeshReader()
{
    m_pMesh = NULL;
}

inline CBaseMeshReader::~CBaseMeshReader()
{
    Assert( !m_pMesh );
}

inline void CBaseMeshReader::BeginRead(
    IMesh* pMesh ,
    int firstVertex ,
    int numVertices ,
    int firstIndex ,
    int numIndices )
{
    Assert( pMesh && ( !m_pMesh ) );

    if ( numVertices < 0 )
    {
        numVertices = pMesh->VertexCount();
    }

    if ( numIndices < 0 )
    {
        numIndices = pMesh->IndexCount();
    }

    m_pMesh = pMesh;
    m_MaxVertices = numVertices;
    m_MaxIndices = numIndices;

    // Locks mesh for modifying
    pMesh->ModifyBeginEx( true , firstVertex , numVertices , firstIndex , numIndices , *this );

    // Point to the start of the buffers..
    Reset();
}

inline void CBaseMeshReader::EndRead()
{
    Assert( m_pMesh );
    m_pMesh->ModifyEnd( *this );
    m_pMesh = NULL;
}

inline void CBaseMeshReader::BeginRead_Direct( const MeshDesc_t &desc , int nVertices , int nIndices )
{
    MeshDesc_t *pThis = this;
    *pThis = desc;
    m_MaxVertices = nVertices;
    m_MaxIndices = nIndices;

    // UNDONE: support reading from compressed verts if necessary
    Assert( desc.m_CompressionType == VERTEX_COMPRESSION_NONE );
}

inline void CBaseMeshReader::Reset()
{}

// -------------------------------------------------------------------------------------- //
// CMeshReader implementation.
// -------------------------------------------------------------------------------------- //

inline int CMeshReader::NumIndices() const
{
    return m_MaxIndices;
}

inline unsigned short CMeshReader::Index( int index ) const
{
    Assert( ( index >= 0 ) && ( index < m_MaxIndices ) );
    return m_pIndices[ index * m_nIndexSize ];
}

inline const Vector& CMeshReader::Position( int iVertex ) const
{
    Assert( iVertex >= 0 && iVertex < m_MaxVertices );
    return *( Vector* ) ( ( char* ) m_pPosition + iVertex * m_VertexSize_Position );
}

inline unsigned int CMeshReader::Color( int iVertex ) const
{
    Assert( iVertex >= 0 && iVertex < m_MaxVertices );
    unsigned char *pColor = m_pColor + iVertex * m_VertexSize_Color;
    return ( pColor[ 0 ] << 16 ) | ( pColor[ 1 ] << 8 ) | ( pColor[ 2 ] ) | ( pColor[ 3 ] << 24 );
}

inline const float *CMeshReader::TexCoord( int iVertex , int iStage ) const
{
    Assert( iVertex >= 0 && iVertex < m_MaxVertices );
    return ( float* ) ( ( char* ) m_pTexCoord[ iStage ] + iVertex * m_VertexSize_TexCoord[ iStage ] );
}

inline void CMeshReader::TexCoord2f( int iVertex , int iStage , float &s , float &t ) const
{
    Assert( iVertex >= 0 && iVertex < m_MaxVertices );
    float *p = ( float* ) ( ( char* ) m_pTexCoord[ iStage ] + iVertex * m_VertexSize_TexCoord[ iStage ] );
    s = p[ 0 ];
    t = p[ 1 ];
}

inline const Vector2D& CMeshReader::TexCoordVector2D( int iVertex , int iStage ) const
{
    Assert( iVertex >= 0 && iVertex < m_MaxVertices );
    Vector2D *p = ( Vector2D* ) ( ( char* ) m_pTexCoord[ iStage ] + iVertex * m_VertexSize_TexCoord[ iStage ] );
    return *p;
}

inline float CMeshReader::Wrinkle( int iVertex ) const
{
    Assert( iVertex >= 0 && iVertex < m_MaxVertices );
    return *( float* ) ( ( char* ) m_pWrinkle + iVertex * m_VertexSize_Wrinkle );
}

inline int CMeshReader::NumBoneWeights() const
{
    return m_NumBoneWeights;
}

inline const Vector &CMeshReader::Normal( int iVertex ) const
{
    Assert( iVertex >= 0 && iVertex < m_MaxVertices );
    return *( const Vector * ) ( const float* ) ( ( char* ) m_pNormal + iVertex * m_VertexSize_Normal );
}

inline void CMeshReader::Normal( int iVertex , Vector &vNormal ) const
{
    Assert( iVertex >= 0 && iVertex < m_MaxVertices );
    const float *p = ( const float* ) ( ( char* ) m_pNormal + iVertex * m_VertexSize_Normal );
    vNormal.Init( p[ 0 ] , p[ 1 ] , p[ 2 ] );
}

inline const Vector &CMeshReader::TangentS( int iVertex ) const
{
    Assert( iVertex >= 0 && iVertex < m_MaxVertices );
    return *( const Vector* ) ( ( char* ) m_pTangentS + iVertex * m_VertexSize_TangentS );
}

inline const Vector &CMeshReader::TangentT( int iVertex ) const
{
    Assert( iVertex >= 0 && iVertex < m_MaxVertices );
    return *( const Vector* ) ( ( char* ) m_pTangentT + iVertex * m_VertexSize_TangentT );
}

inline float CMeshReader::BoneWeight( int iVertex ) const
{
    Assert( iVertex >= 0 && iVertex < m_MaxVertices );
    float *p = ( float* ) ( ( char* ) m_pBoneWeight + iVertex * m_VertexSize_BoneWeight );
    return *p;
}

#define INVALID_BUFFER_OFFSET 0xFFFFFFFFUL

// flags for advancevertex optimization
#define VTX_HAVEPOS 1
#define VTX_HAVENORMAL 2
#define VTX_HAVECOLOR 4
#define VTX_HAVEALL ( VTX_HAVEPOS | VTX_HAVENORMAL | VTX_HAVECOLOR )

//-----------------------------------------------------------------------------
//
// Helper class used to define vertex buffers
//
//-----------------------------------------------------------------------------
class CVertexBuilder : private VertexDesc_t
{
public:
    CVertexBuilder();
    CVertexBuilder( IVertexBuffer *pVertexBuffer , VertexFormat_t fmt = 0 );
    ~CVertexBuilder();

    // Begins, ends modification of the index buffer (returns true if the lock succeeded)
    // A lock may not succeed if append is set to true and there isn't enough room
    // NOTE: Append is only used with dynamic index buffers; it's ignored for static buffers
    bool Lock( int nMaxIndexCount , bool bAppend = false );
    void Unlock();

    // Spews the current data
    // NOTE: Can only be called during a lock/unlock block
    void SpewData();

    // Returns the number of indices we can fit into the buffer without needing to discard
    int GetRoomRemaining() const;

    // Binds this vertex buffer
    void Bind( IMatRenderContext *pContext , int nStreamID , VertexFormat_t usage = 0 );

    // Returns the byte offset
    int Offset() const;

    // This must be called before Begin, if a vertex buffer with a compressed format is to be used
    void SetCompressionType( VertexCompressionType_t compressionType );
    void ValidateCompressionType();

    void Begin( IVertexBuffer *pVertexBuffer , int nVertexCount , int *nFirstVertex );
    void Begin( IVertexBuffer *pVertexBuffer , int nVertexCount );

    // Use this when you're done writing
    // Set bDraw to true to call m_pMesh->Draw automatically.
    void End( bool bSpewData = false );

    // Locks the vertex buffer to modify existing data
    // Passing nVertexCount == -1 says to lock all the vertices for modification.
    void BeginModify( IVertexBuffer *pVertexBuffer , int nFirstVertex = 0 , int nVertexCount = -1 );
    void EndModify( bool bSpewData = false );

    // returns the number of vertices
    int VertexCount() const;

    // Returns the total number of vertices across all Locks()
    int TotalVertexCount() const;

    // Resets the mesh builder so it points to the start of everything again
    void Reset();

    // Returns the size of the vertex
    int VertexSize()
    {
        return m_ActualVertexSize;
    }

    // returns the data size of a given texture coordinate
    int TextureCoordinateSize( int nTexCoordNumber )
    {
        return m_VertexSize_TexCoord[ nTexCoordNumber ];
    }

    // Returns the base vertex memory pointer
    void* BaseVertexData();

    // Selects the nth Vertex and Index
    void SelectVertex( int idx );

    // Advances the current vertex and index by one
    void AdvanceVertex( void );
    template<int nFlags , int nNumTexCoords> void AdvanceVertexF( void );
    void AdvanceVertices( int nVerts );

    int GetCurrentVertex() const;
    int GetFirstVertex() const;

    // Data retrieval...
    const float *Position() const;

    const float *Normal() const;

    unsigned int Color() const;

    unsigned char *Specular() const;

    const float *TexCoord( int stage ) const;

    const float *TangentS() const;
    const float *TangentT() const;

    const float *BoneWeight() const;
    float Wrinkle() const;

    int NumBoneWeights() const;
#ifndef NEW_SKINNING
    unsigned char *BoneMatrix() const;
#else
    float *BoneMatrix() const;
#endif

    // position setting
    void Position3f( float x , float y , float z );
    void Position3fv( const float *v );

    // normal setting
    void Normal3f( float nx , float ny , float nz );
    void Normal3fv( const float *n );
    void NormalDelta3fv( const float *n );
    void NormalDelta3f( float nx , float ny , float nz );
    // normal setting (templatized for code which needs to support compressed vertices)
    template <VertexCompressionType_t T> void CompressedNormal3f( float nx , float ny , float nz );
    template <VertexCompressionType_t T> void CompressedNormal3fv( const float *n );

    // color setting
    void Color3f( float r , float g , float b );
    void Color3fv( const float *rgb );
    void Color4f( float r , float g , float b , float a );
    void Color4fv( const float *rgba );

    // Faster versions of color
    void Color3ub( unsigned char r , unsigned char g , unsigned char b );
    void Color3ubv( unsigned char const* rgb );
    void Color4ub( unsigned char r , unsigned char g , unsigned char b , unsigned char a );
    void Color4ubv( unsigned char const* rgba );
    void Color4Packed( int packedColor );
    int PackColor4( unsigned char r , unsigned char g , unsigned char b , unsigned char a );

    // specular color setting
    void Specular3f( float r , float g , float b );
    void Specular3fv( const float *rgb );
    void Specular4f( float r , float g , float b , float a );
    void Specular4fv( const float *rgba );

    // Faster version of specular
    void Specular3ub( unsigned char r , unsigned char g , unsigned char b );
    void Specular3ubv( unsigned char const *c );
    void Specular4ub( unsigned char r , unsigned char g , unsigned char b , unsigned char a );
    void Specular4ubv( unsigned char const *c );

    // texture coordinate setting
    void TexCoord1f( int stage , float s );
    void TexCoord2f( int stage , float s , float t );
    void TexCoord2fv( int stage , const float *st );
    void TexCoord3f( int stage , float s , float t , float u );
    void TexCoord3fv( int stage , const float *stu );
    void TexCoord4f( int stage , float s , float t , float u , float w );
    void TexCoord4fv( int stage , const float *stuv );

    void TexCoordSubRect2f( int stage , float s , float t , float offsetS , float offsetT , float scaleS , float scaleT );
    void TexCoordSubRect2fv( int stage , const float *st , const float *offset , const float *scale );

    // tangent space
    void TangentS3f( float sx , float sy , float sz );
    void TangentS3fv( const float* s );

    void TangentT3f( float tx , float ty , float tz );
    void TangentT3fv( const float* t );

    // Wrinkle
    void Wrinkle1f( float flWrinkle );

    // bone weights
    void BoneWeight( int idx , float weight );
    void BoneWeights2( float weight1 , float weight2 );

    // bone weights (templatized for code which needs to support compressed vertices)
    template <VertexCompressionType_t T> void CompressedBoneWeight3fv( const float * pWeights );

    // bone matrix index
    void BoneMatrix( int idx , int matrixIndex );
    void BoneMatrices4( int matrixIdx0 , int matrixIdx1 , int matrixIdx2 , int matrixIdx3 );

    // Generic per-vertex data
    void UserData( const float* pData );
    // Generic per-vertex data (templatized for code which needs to support compressed vertices)
    template <VertexCompressionType_t T> void CompressedUserData( const float* pData );

    // Fast Vertex! No need to call advance vertex, and no random access allowed.
    // WARNING - these are low level functions that are intended only for use
    // in the software vertex skinner.
    void FastVertex( const ModelVertexDX8_t &vertex );
    void FastVertexSSE( const ModelVertexDX8_t &vertex );
    void FastQuadVertexSSE( const QuadTessVertex_t &vertex );

    // Add number of verts and current vert since FastVertex routines do not update.
    void FastAdvanceNVertices( int n );

#if defined( _X360 )
    void VertexDX8ToX360( const ModelVertexDX8_t &vertex );
#endif

    // FIXME: Remove! Backward compat so we can use this from a CMeshBuilder.
    void AttachBegin( IMesh* pMesh , int nMaxVertexCount , const MeshDesc_t &desc );
    void AttachEnd();
    void AttachBeginModify( IMesh* pMesh , int nVertexCount , const MeshDesc_t &desc );
    void AttachEndModify();

private:
    // The vertex buffer we're modifying
    IVertexBuffer * m_pVertexBuffer;

    // Used to make sure Begin/End calls and BeginModify/EndModify calls match.
    bool m_bModify;

    // Max number of indices and vertices
    int m_nMaxVertexCount;

    // Number of indices and vertices
    int m_nVertexCount;

    // The current vertex and index
    mutable int m_nCurrentVertex;

    // Optimization: Pointer to the current pos, norm, texcoord, and color
    mutable float			*m_pCurrPosition;
    mutable float			*m_pCurrNormal;
    mutable unsigned char	*m_pCurrColor;
    mutable float			*m_pCurrTexCoord[ VERTEX_MAX_TEXTURE_COORDINATES ];

    // Total number of vertices appended
    int m_nTotalVertexCount;

    // First vertex buffer offset + index
    unsigned int m_nBufferOffset;
    unsigned int m_nBufferFirstVertex;

#if ( COMPRESSED_NORMALS_TYPE == COMPRESSED_NORMALS_COMBINEDTANGENTS_UBYTE4 )
    // Debug checks to make sure we write userdata4/tangents AFTER normals
    bool m_bWrittenNormal : 1;
    bool m_bWrittenUserData : 1;
#endif

    friend class CMeshBuilder;
};

//-----------------------------------------------------------------------------
//
// Inline methods of CVertexBuilder
//
//-----------------------------------------------------------------------------
inline CVertexBuilder::CVertexBuilder()
{
    m_pVertexBuffer = NULL;
    m_nBufferOffset = INVALID_BUFFER_OFFSET;
    m_nBufferFirstVertex = 0;
    m_nVertexCount = 0;
    m_nCurrentVertex = 0;
    m_nMaxVertexCount = 0;
    m_nTotalVertexCount = 0;
    m_CompressionType = VERTEX_COMPRESSION_INVALID;
}

inline CVertexBuilder::CVertexBuilder( IVertexBuffer *pVertexBuffer , VertexFormat_t fmt )
{
    m_pVertexBuffer = pVertexBuffer;
    m_nBufferOffset = INVALID_BUFFER_OFFSET;
    m_nBufferFirstVertex = 0;
    m_nVertexCount = 0;
    m_nCurrentVertex = 0;
    m_nMaxVertexCount = 0;
    m_nTotalVertexCount = 0;
    m_CompressionType = VERTEX_COMPRESSION_INVALID;

    if ( m_pVertexBuffer->IsDynamic() )
    {
        m_pVertexBuffer->BeginCastBuffer( fmt );
    }
    else
    {
        Assert( m_pVertexBuffer->GetVertexFormat() == fmt );
    }
}

inline CVertexBuilder::~CVertexBuilder()
{
    if ( m_pVertexBuffer && m_pVertexBuffer->IsDynamic() )
    {
        m_pVertexBuffer->EndCastBuffer();
    }
}

//-----------------------------------------------------------------------------
// Begins, ends modification of the index buffer
//-----------------------------------------------------------------------------
inline bool CVertexBuilder::Lock( int nMaxVertexCount , bool bAppend )
{
    Assert( m_pVertexBuffer );
    m_bModify = false;
    m_nMaxVertexCount = nMaxVertexCount;
    bool bFirstLock = ( m_nBufferOffset == INVALID_BUFFER_OFFSET );
    if ( bFirstLock )
    {
        bAppend = false;
    }
    if ( !bAppend )
    {
        m_nTotalVertexCount = 0;
    }

    // Lock the vertex buffer
    if ( !m_pVertexBuffer->Lock( m_nMaxVertexCount , bAppend , *this ) )
    {
        m_nMaxVertexCount = 0;
        return false;
    }

    Reset();

    if ( bFirstLock )
    {
        m_nBufferOffset = m_nOffset;
        m_nBufferFirstVertex = m_nFirstVertex;
    }

    return true;
}

inline void CVertexBuilder::Unlock()
{
    Assert( !m_bModify && m_pVertexBuffer );

    m_pVertexBuffer->Unlock( m_nVertexCount , *this );
    m_nTotalVertexCount += m_nVertexCount;

    m_nMaxVertexCount = 0;
}

inline void CVertexBuilder::SpewData()
{
    m_pVertexBuffer->Spew( m_nVertexCount , *this );
}

//-----------------------------------------------------------------------------
// Binds this vertex buffer
//-----------------------------------------------------------------------------
inline void CVertexBuilder::Bind( IMatRenderContext *pContext , int nStreamID , VertexFormat_t usage )
{
    if ( m_pVertexBuffer && ( m_nBufferOffset != INVALID_BUFFER_OFFSET ) )
    {
        pContext->BindVertexBuffer( nStreamID , m_pVertexBuffer , m_nBufferOffset ,
                                    m_nFirstVertex , m_nTotalVertexCount , usage ? usage : m_pVertexBuffer->GetVertexFormat() );
    }
    else
    {
        pContext->BindVertexBuffer( nStreamID , NULL , 0 , 0 , 0 , 0 );
    }
}

//-----------------------------------------------------------------------------
// Returns the byte offset
//-----------------------------------------------------------------------------
inline int CVertexBuilder::Offset() const
{
    return m_nBufferOffset;
}

inline int CVertexBuilder::GetFirstVertex() const
{
    return m_nBufferFirstVertex;
}

//-----------------------------------------------------------------------------
// Specify the type of vertex compression that this CMeshBuilder will perform
//-----------------------------------------------------------------------------
inline void CVertexBuilder::SetCompressionType( VertexCompressionType_t compressionType )
{
    // The real purpose of this method is to allow us to emit a Warning in Begin()
    m_CompressionType = compressionType;
}

inline void CVertexBuilder::ValidateCompressionType()
{}

inline void CVertexBuilder::Begin( IVertexBuffer *pVertexBuffer , int nVertexCount )
{
    Assert( pVertexBuffer && ( !m_pVertexBuffer ) );

    m_pVertexBuffer = pVertexBuffer;
    m_bModify = false;

    m_nMaxVertexCount = nVertexCount;
    m_nVertexCount = 0;

    // Make sure SetCompressionType was called correctly, if this VB is compressed
    ValidateCompressionType();

    // Lock the vertex and index buffer
    m_pVertexBuffer->Lock( m_nMaxVertexCount , false , *this );

    // Point to the start of the buffers..
    Reset();
}

//-----------------------------------------------------------------------------
// Use this when you're done modifying the mesh
//-----------------------------------------------------------------------------
inline void CVertexBuilder::End( bool bSpewData )
{
    // Make sure they called Begin()
    Assert( !m_bModify );

    if ( bSpewData )
    {
        m_pVertexBuffer->Spew( m_nVertexCount , *this );
    }

    // Unlock our buffers
    m_pVertexBuffer->Unlock( m_nVertexCount , *this );

    m_pVertexBuffer = 0;
    m_nMaxVertexCount = 0;

    m_CompressionType = VERTEX_COMPRESSION_INVALID;
}

//-----------------------------------------------------------------------------
// FIXME: Remove! Backward compat so we can use this from a CMeshBuilder.
//-----------------------------------------------------------------------------
inline void CVertexBuilder::AttachBegin( IMesh* pMesh , int nMaxVertexCount , const MeshDesc_t &desc )
{
    m_pVertexBuffer = pMesh;
    memcpy( static_cast< VertexDesc_t* >( this ) , static_cast< const VertexDesc_t* >( &desc ) , sizeof( VertexDesc_t ) );
    m_nMaxVertexCount = nMaxVertexCount;
    m_NumBoneWeights = m_NumBoneWeights == 0 ? 0 : 2;	// Two weights if any
    m_nVertexCount = 0;
    m_bModify = false;

    // Make sure SetCompressionType was called correctly, if this VB is compressed
    ValidateCompressionType();

    if ( m_nBufferOffset == INVALID_BUFFER_OFFSET )
    {
        m_nTotalVertexCount = 0;
        m_nBufferOffset = static_cast< const VertexDesc_t* >( &desc )->m_nOffset;
        m_nBufferFirstVertex = desc.m_nFirstVertex;
    }
}

inline void CVertexBuilder::AttachEnd()
{
    // Make sure they called Begin()
    Assert( !m_bModify );

    m_nMaxVertexCount = 0;
    m_pVertexBuffer = NULL;

    m_CompressionType = VERTEX_COMPRESSION_INVALID;
}

inline void CVertexBuilder::AttachBeginModify( IMesh* pMesh , int nVertexCount , const MeshDesc_t &desc )
{
    Assert( pMesh && ( !m_pVertexBuffer ) );

    m_pVertexBuffer = pMesh;
    memcpy( static_cast< VertexDesc_t* >( this ) , static_cast< const VertexDesc_t* >( &desc ) , sizeof( VertexDesc_t ) );
    m_nMaxVertexCount = m_nVertexCount = nVertexCount;
    m_NumBoneWeights = m_NumBoneWeights == 0 ? 0 : 2;	// Two weights if any
    m_bModify = true;

    // Make sure SetCompressionType was called correctly, if this VB is compressed
    ValidateCompressionType();
}

inline void CVertexBuilder::AttachEndModify()
{
    Assert( m_pVertexBuffer );
    Assert( m_bModify );	// Make sure they called BeginModify.

    m_pVertexBuffer = 0;
    m_nMaxVertexCount = 0;

    m_CompressionType = VERTEX_COMPRESSION_INVALID;
}

//-----------------------------------------------------------------------------
// Computes the first min non-null address
//-----------------------------------------------------------------------------
inline unsigned char* FindMinAddress( void *pAddress1 , void *pAddress2 , int nAddress2Size )
{
    if ( nAddress2Size == 0 )
        return ( unsigned char* ) pAddress1;
    if ( !pAddress1 )
        return ( unsigned char* ) pAddress2;
    return ( pAddress1 < pAddress2 ) ? ( unsigned char* ) pAddress1 : ( unsigned char* ) pAddress2;
}

// number of elements in an array of static size
#define NELEMS(x) ((sizeof(x))/sizeof(x[0]))

//-----------------------------------------------------------------------------
// Resets the vertex buffer builder so it points to the start of everything again
//-----------------------------------------------------------------------------
inline void CVertexBuilder::Reset()
{
    m_nCurrentVertex = 0;

    m_pCurrPosition = m_pPosition;
    m_pCurrNormal = m_pNormal;
    for ( size_t i = 0; i < NELEMS( m_pCurrTexCoord ); i++ )
    {
        m_pCurrTexCoord[ i ] = m_pTexCoord[ i ];
    }
    m_pCurrColor = m_pColor;
}

//-----------------------------------------------------------------------------
// returns the number of vertices
//-----------------------------------------------------------------------------
inline int CVertexBuilder::VertexCount() const
{
    return m_nVertexCount;
}

//-----------------------------------------------------------------------------
// Returns the total number of vertices across all Locks()
//-----------------------------------------------------------------------------
inline int CVertexBuilder::TotalVertexCount() const
{
    return m_nTotalVertexCount;
}

//-----------------------------------------------------------------------------
// Returns the base vertex memory pointer
//-----------------------------------------------------------------------------
inline void* CVertexBuilder::BaseVertexData()
{
    // FIXME: If there's no position specified, we need to find
    // the base address
    Assert( m_pPosition );
    return m_pPosition;
}

//-----------------------------------------------------------------------------
// Selects the current vertex
//-----------------------------------------------------------------------------
inline void CVertexBuilder::SelectVertex( int nIndex )
{
    // NOTE: This index is expected to be relative
    Assert( ( nIndex >= 0 ) && ( nIndex < m_nMaxVertexCount ) );
    m_nCurrentVertex = nIndex;

    m_pCurrPosition = OffsetFloatPointer( m_pPosition , m_nCurrentVertex , m_VertexSize_Position );
    m_pCurrNormal = OffsetFloatPointer( m_pNormal , m_nCurrentVertex , m_VertexSize_Normal );

    m_pCurrTexCoord[ 0 ] = OffsetFloatPointer( m_pTexCoord[ 0 ] , m_nCurrentVertex , m_VertexSize_TexCoord[ 0 ] );
    m_pCurrTexCoord[ 1 ] = OffsetFloatPointer( m_pTexCoord[ 1 ] , m_nCurrentVertex , m_VertexSize_TexCoord[ 1 ] );
    m_pCurrTexCoord[ 2 ] = OffsetFloatPointer( m_pTexCoord[ 2 ] , m_nCurrentVertex , m_VertexSize_TexCoord[ 2 ] );
    m_pCurrTexCoord[ 3 ] = OffsetFloatPointer( m_pTexCoord[ 3 ] , m_nCurrentVertex , m_VertexSize_TexCoord[ 3 ] );
    m_pCurrTexCoord[ 4 ] = OffsetFloatPointer( m_pTexCoord[ 4 ] , m_nCurrentVertex , m_VertexSize_TexCoord[ 4 ] );
    m_pCurrTexCoord[ 5 ] = OffsetFloatPointer( m_pTexCoord[ 5 ] , m_nCurrentVertex , m_VertexSize_TexCoord[ 5 ] );
    m_pCurrTexCoord[ 6 ] = OffsetFloatPointer( m_pTexCoord[ 6 ] , m_nCurrentVertex , m_VertexSize_TexCoord[ 6 ] );
    m_pCurrTexCoord[ 7 ] = OffsetFloatPointer( m_pTexCoord[ 7 ] , m_nCurrentVertex , m_VertexSize_TexCoord[ 7 ] );
    m_pCurrColor = m_pColor + m_nCurrentVertex * m_VertexSize_Color;
}

//-----------------------------------------------------------------------------
// Advances vertex after you're done writing to it.
//-----------------------------------------------------------------------------
__pragma( warning( push ) )
__pragma( warning( disable:4127 ) )

template<int nFlags , int nNumTexCoords> FORCEINLINE void CVertexBuilder::AdvanceVertexF()
{
    if ( ++m_nCurrentVertex > m_nVertexCount )
    {
        m_nVertexCount = m_nCurrentVertex;
    }

    if ( nFlags & VTX_HAVEPOS )
        IncrementFloatPointer( m_pCurrPosition , m_VertexSize_Position );
    if ( nFlags & VTX_HAVENORMAL )
        IncrementFloatPointer( m_pCurrNormal , m_VertexSize_Normal );
    if ( nFlags & VTX_HAVECOLOR )
        m_pCurrColor += m_VertexSize_Color;

    if ( nNumTexCoords > 0 )
        IncrementFloatPointer( m_pCurrTexCoord[ 0 ] , m_VertexSize_TexCoord[ 0 ] );
    if ( nNumTexCoords > 1 )
        IncrementFloatPointer( m_pCurrTexCoord[ 1 ] , m_VertexSize_TexCoord[ 1 ] );
    if ( nNumTexCoords > 2 )
        IncrementFloatPointer( m_pCurrTexCoord[ 2 ] , m_VertexSize_TexCoord[ 2 ] );
    if ( nNumTexCoords > 3 )
        IncrementFloatPointer( m_pCurrTexCoord[ 3 ] , m_VertexSize_TexCoord[ 3 ] );
    if ( nNumTexCoords > 4 )
        IncrementFloatPointer( m_pCurrTexCoord[ 4 ] , m_VertexSize_TexCoord[ 4 ] );
    if ( nNumTexCoords > 5 )
        IncrementFloatPointer( m_pCurrTexCoord[ 5 ] , m_VertexSize_TexCoord[ 5 ] );
    if ( nNumTexCoords > 6 )
        IncrementFloatPointer( m_pCurrTexCoord[ 6 ] , m_VertexSize_TexCoord[ 6 ] );
    if ( nNumTexCoords > 7 )
        IncrementFloatPointer( m_pCurrTexCoord[ 7 ] , m_VertexSize_TexCoord[ 7 ] );
}

__pragma( warning( pop ) )

inline void CVertexBuilder::AdvanceVertex()
{
    AdvanceVertexF<VTX_HAVEALL , 8>();
}

inline void CVertexBuilder::AdvanceVertices( int nVerts )
{
    m_nCurrentVertex += nVerts;
    if ( m_nCurrentVertex > m_nVertexCount )
    {
        m_nVertexCount = m_nCurrentVertex;
    }

    IncrementFloatPointer( m_pCurrPosition , m_VertexSize_Position*nVerts );
    IncrementFloatPointer( m_pCurrNormal , m_VertexSize_Normal*nVerts );

    IncrementFloatPointer( m_pCurrTexCoord[ 0 ] , m_VertexSize_TexCoord[ 0 ] * nVerts );
    IncrementFloatPointer( m_pCurrTexCoord[ 1 ] , m_VertexSize_TexCoord[ 1 ] * nVerts );
    IncrementFloatPointer( m_pCurrTexCoord[ 2 ] , m_VertexSize_TexCoord[ 2 ] * nVerts );
    IncrementFloatPointer( m_pCurrTexCoord[ 3 ] , m_VertexSize_TexCoord[ 3 ] * nVerts );
    IncrementFloatPointer( m_pCurrTexCoord[ 4 ] , m_VertexSize_TexCoord[ 4 ] * nVerts );
    IncrementFloatPointer( m_pCurrTexCoord[ 5 ] , m_VertexSize_TexCoord[ 5 ] * nVerts );
    IncrementFloatPointer( m_pCurrTexCoord[ 6 ] , m_VertexSize_TexCoord[ 6 ] * nVerts );
    IncrementFloatPointer( m_pCurrTexCoord[ 7 ] , m_VertexSize_TexCoord[ 7 ] * nVerts );
    m_pCurrColor += m_VertexSize_Color * nVerts;
}

//-----------------------------------------------------------------------------
// For use with the FastVertex methods, advances the current vertex by N
//-----------------------------------------------------------------------------
inline void CVertexBuilder::FastAdvanceNVertices( int n )
{
    m_nCurrentVertex += n;
    m_nVertexCount = m_nCurrentVertex;
}

inline void CVertexBuilder::FastVertex( const ModelVertexDX8_t &vertex )
{
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE ); // FIXME: support compressed verts if needed
    Assert( m_nCurrentVertex < m_nMaxVertexCount );

#if defined( _WIN32 ) && !defined( _X360 )
    const void *pRead = &vertex;
    void *pCurrPos = m_pCurrPosition;
    __asm
    {
        mov esi , pRead
        mov edi , pCurrPos

        movq mm0 , [ esi + 0 ]
        movq mm1 , [ esi + 8 ]
        movq mm2 , [ esi + 16 ]
        movq mm3 , [ esi + 24 ]
        movq mm4 , [ esi + 32 ]
        movq mm5 , [ esi + 40 ]

        movntq[ edi + 0 ] , mm0
        movntq[ edi + 8 ] , mm1
        movntq[ edi + 16 ] , mm2
        movntq[ edi + 24 ] , mm3
        movntq[ edi + 32 ] , mm4
        movntq[ edi + 40 ] , mm5

        emms
    }
#elif defined(GNUC)
    const void *pRead = &vertex;
    void *pCurrPos = m_pCurrPosition;
    __asm__ __volatile__(
        "movq (%0), %%mm0\n"
        "movq 8(%0), %%mm1\n"
        "movq 16(%0), %%mm2\n"
        "movq 24(%0), %%mm3\n"
        "movq 32(%0), %%mm4\n"
        "movq 40(%0), %%mm5\n"
        "movq 48(%0), %%mm6\n"
        "movq 56(%0), %%mm7\n"
        "movntq %%mm0, (%1)\n"
        "movntq %%mm1, 8(%1)\n"
        "movntq %%mm2, 16(%1)\n"
        "movntq %%mm3, 24(%1)\n"
        "movntq %%mm4, 32(%1)\n"
        "movntq %%mm5, 40(%1)\n"
        "movntq %%mm6, 48(%1)\n"
        "movntq %%mm7, 56(%1)\n"
        "emms\n"
        :: "r" ( pRead ) , "r" ( pCurrPos ) : "memory" );
#else
    Error( "Implement CMeshBuilder::FastVertex(dx8)" );
#endif

    IncrementFloatPointer( m_pCurrPosition , m_VertexSize_Position );
    //	m_nVertexCount = ++m_nCurrentVertex;
}

inline void CVertexBuilder::FastVertexSSE( const ModelVertexDX8_t &vertex )
{
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE ); // FIXME: support compressed verts if needed
    Assert( m_nCurrentVertex < m_nMaxVertexCount );

#if defined( _WIN32 ) && !defined( _X360 )
    const void *pRead = &vertex;
    void *pCurrPos = m_pCurrPosition;
    __asm
    {
        mov esi , pRead
        mov edi , pCurrPos

        movaps xmm0 , [ esi + 0 ]
        movaps xmm1 , [ esi + 16 ]
        movaps xmm2 , [ esi + 32 ]

        movntps[ edi + 0 ] , xmm0
        movntps[ edi + 16 ] , xmm1
        movntps[ edi + 32 ] , xmm2
    }
#elif defined(GNUC)
    const void *pRead = &vertex;
    void *pCurrPos = m_pCurrPosition;
    __asm__ __volatile__(
        "movaps (%0), %%xmm0\n"
        "movaps 16(%0), %%xmm1\n"
        "movaps 32(%0), %%xmm2\n"
        "movaps 48(%0), %%xmm3\n"
        "movntps %%xmm0, (%1)\n"
        "movntps %%xmm1, 16(%1)\n"
        "movntps %%xmm2, 32(%1)\n"
        "movntps %%xmm3, 48(%1)\n"
        :: "r" ( pRead ) , "r" ( pCurrPos ) : "memory" );
#else
    Error( "Implement CMeshBuilder::FastVertexSSE((dx8)" );
#endif

    IncrementFloatPointer( m_pCurrPosition , m_VertexSize_Position );
    //	m_nVertexCount = ++m_nCurrentVertex;
}

inline void CVertexBuilder::FastQuadVertexSSE( const QuadTessVertex_t &vertex )
{
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE ); // FIXME: support compressed verts if needed
    Assert( m_nCurrentVertex < m_nMaxVertexCount );

#if defined( _WIN32 ) && !defined( _X360 )
    const void *pRead = &vertex;
    void *pCurrPos = m_pCurrPosition;
    __asm
    {
        mov esi , pRead
        mov edi , pCurrPos

        movaps xmm0 , [ esi + 0 ]
        movaps xmm1 , [ esi + 16 ]
        movaps xmm2 , [ esi + 32 ]

        movntps[ edi + 0 ] , xmm0
        movntps[ edi + 16 ] , xmm1
        movntps[ edi + 32 ] , xmm2
    }
#endif

    IncrementFloatPointer( m_pCurrPosition , m_VertexSize_Position );
    //	m_nVertexCount = ++m_nCurrentVertex;
}

//-----------------------------------------------------------------------------
// Returns the current vertex
//-----------------------------------------------------------------------------
inline int CVertexBuilder::GetCurrentVertex() const
{
    return m_nCurrentVertex;
}

//-----------------------------------------------------------------------------
// Copies a vertex into the x360 format
//-----------------------------------------------------------------------------
#if defined( _X360 )
inline void CVertexBuilder::VertexDX8ToX360( const ModelVertexDX8_t &vertex )
{
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE ); // FIXME: support compressed verts if needed
    Assert( m_nCurrentVertex < m_nMaxVertexCount );

    // get the start of the data
    unsigned char *pDst = ( unsigned char* ) m_pCurrPosition;

    Assert( m_VertexSize_Position > 0 ); // Assume position is always present
    Assert( GetVertexElementSize( VERTEX_ELEMENT_POSITION , VERTEX_COMPRESSION_NONE ) == sizeof( vertex.m_vecPosition ) );
    memcpy( pDst , vertex.m_vecPosition.Base() , sizeof( vertex.m_vecPosition ) );
    pDst += sizeof( vertex.m_vecPosition );

    if ( m_VertexSize_Normal )
    {
        Assert( GetVertexElementSize( VERTEX_ELEMENT_NORMAL , VERTEX_COMPRESSION_NONE ) == sizeof( vertex.m_vecNormal ) );
        memcpy( pDst , vertex.m_vecNormal.Base() , sizeof( vertex.m_vecNormal ) );
        pDst += sizeof( vertex.m_vecNormal );
    }

    if ( m_VertexSize_TexCoord[ 0 ] )
    {
        Assert( GetVertexElementSize( VERTEX_ELEMENT_TEXCOORD2D_0 , VERTEX_COMPRESSION_NONE ) == sizeof( vertex.m_vecTexCoord ) );
        memcpy( pDst , vertex.m_vecTexCoord.Base() , sizeof( vertex.m_vecTexCoord ) );
        pDst += sizeof( vertex.m_vecTexCoord );
    }

    if ( m_VertexSize_UserData )
    {
        Assert( GetVertexElementSize( VERTEX_ELEMENT_USERDATA4 , VERTEX_COMPRESSION_NONE ) == sizeof( vertex.m_vecUserData ) );
        memcpy( pDst , vertex.m_vecUserData.Base() , sizeof( vertex.m_vecUserData ) );
        pDst += sizeof( vertex.m_vecUserData );
    }

    // ensure code is synced with the mesh builder that established the offsets
    Assert( pDst - ( unsigned char* ) m_pCurrPosition == m_VertexSize_Position );

    IncrementFloatPointer( m_pCurrPosition , m_VertexSize_Position );
}
#endif

//-----------------------------------------------------------------------------
// Data retrieval...
//-----------------------------------------------------------------------------
inline const float* CVertexBuilder::Position() const
{
    // FIXME: add a templatized accessor (return type varies to ensure calling code is updated appropriately)
    //        for code that needs to access compressed data (and/or a return-by-value templatized accessor)
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE );
    Assert( m_nCurrentVertex < m_nMaxVertexCount );
    return m_pCurrPosition;
}

inline const float* CVertexBuilder::Normal() const
{
    // FIXME: add a templatized accessor (return type varies to ensure calling code is updated appropriately)
    //        for code that needs to access compressed data (and/or a return-by-value templatized accessor)
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE );
    Assert( m_nCurrentVertex < m_nMaxVertexCount );
    return m_pCurrNormal;
}

inline unsigned int CVertexBuilder::Color() const
{
    // FIXME: add a templatized accessor (return type varies to ensure calling code is updated appropriately)
    //        for code that needs to access compressed data (and/or a return-by-value templatized accessor)
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE );
    // Swizzle it so it returns the same format as accepted by Color4ubv - rgba
    Assert( m_nCurrentVertex < m_nMaxVertexCount );
    unsigned int color = ( m_pCurrColor[ 3 ] << 24 ) | ( m_pCurrColor[ 0 ] << 16 ) | ( m_pCurrColor[ 1 ] << 8 ) | ( m_pCurrColor[ 2 ] );
    return color;
}

inline unsigned char *CVertexBuilder::Specular() const
{
    // FIXME: add a templatized accessor (return type varies to ensure calling code is updated appropriately)
    //        for code that needs to access compressed data (and/or a return-by-value templatized accessor)
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE );
    Assert( m_nCurrentVertex < m_nMaxVertexCount );
    return m_pSpecular + m_nCurrentVertex * m_VertexSize_Specular;
}

inline const float* CVertexBuilder::TexCoord( int stage ) const
{
    // FIXME: add a templatized accessor (return type varies to ensure calling code is updated appropriately)
    //        for code that needs to access compressed data (and/or a return-by-value templatized accessor)
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE );
    Assert( m_nCurrentVertex < m_nMaxVertexCount );
    return m_pCurrTexCoord[ stage ];
}

inline const float* CVertexBuilder::TangentS() const
{
    // FIXME: add a templatized accessor (return type varies to ensure calling code is updated appropriately)
    //        for code that needs to access compressed data (and/or a return-by-value templatized accessor)
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE );
    Assert( m_nCurrentVertex < m_nMaxVertexCount );
    return OffsetFloatPointer( m_pTangentS , m_nCurrentVertex , m_VertexSize_TangentS );
}

inline const float* CVertexBuilder::TangentT() const
{
    // FIXME: add a templatized accessor (return type varies to ensure calling code is updated appropriately)
    //        for code that needs to access compressed data (and/or a return-by-value templatized accessor)
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE );
    Assert( m_nCurrentVertex < m_nMaxVertexCount );
    return OffsetFloatPointer( m_pTangentT , m_nCurrentVertex , m_VertexSize_TangentT );
}

inline float CVertexBuilder::Wrinkle() const
{
    // FIXME: add a templatized accessor (return type varies to ensure calling code is updated appropriately)
    //        for code that needs to access compressed data (and/or a return-by-value templatized accessor)
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE );
    Assert( m_nCurrentVertex < m_nMaxVertexCount );
    return *OffsetFloatPointer( m_pWrinkle , m_nCurrentVertex , m_VertexSize_Wrinkle );
}

inline const float* CVertexBuilder::BoneWeight() const
{
    // FIXME: add a templatized accessor (return type varies to ensure calling code is updated appropriately)
    //        for code that needs to access compressed data (and/or a return-by-value templatized accessor)
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE );
    Assert( m_nCurrentVertex < m_nMaxVertexCount );
    return OffsetFloatPointer( m_pBoneWeight , m_nCurrentVertex , m_VertexSize_BoneWeight );
}

inline int CVertexBuilder::NumBoneWeights() const
{
    return m_NumBoneWeights;
}

#ifndef NEW_SKINNING
inline unsigned char* CVertexBuilder::BoneMatrix() const
{
    // FIXME: add a templatized accessor (return type varies to ensure calling code is updated appropriately)
    //        for code that needs to access compressed data (and/or a return-by-value templatized accessor)
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE );
    Assert( m_nCurrentVertex < m_nMaxVertexCount );
    return m_pBoneMatrixIndex + m_nCurrentVertex * m_VertexSize_BoneMatrixIndex;
}
#else
inline float* CVertexBuilder::BoneMatrix() const
{
    // FIXME: add a templatized accessor (return type varies to ensure calling code is updated appropriately)
    //        for code that needs to access compressed data (and/or a return-by-value templatized accessor)
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE );
    Assert( m_nCurrentVertex < m_nMaxVertexCount );
    return m_pBoneMatrixIndex + m_nCurrentVertex * m_VertexSize_BoneMatrixIndex;
}
#endif

//-----------------------------------------------------------------------------
// Position setting methods
//-----------------------------------------------------------------------------
inline void	CVertexBuilder::Position3f( float x , float y , float z )
{
    Assert( m_pPosition && m_pCurrPosition );
    Assert( IsFinite( x ) && IsFinite( y ) && IsFinite( z ) );
    float *pDst = m_pCurrPosition;
    *pDst++ = x;
    *pDst++ = y;
    *pDst = z;
}

inline void	CVertexBuilder::Position3fv( const float *v )
{
    Assert( v );
    Assert( m_pPosition && m_pCurrPosition );

    float *pDst = m_pCurrPosition;
    *pDst++ = *v++;
    *pDst++ = *v++;
    *pDst = *v;
}

//-----------------------------------------------------------------------------
// Normal setting methods
//-----------------------------------------------------------------------------
inline void	CVertexBuilder::Normal3f( float nx , float ny , float nz )
{
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE ); // Use the templatized version if you want to support compression
    Assert( m_pNormal );
    Assert( IsFinite( nx ) && IsFinite( ny ) && IsFinite( nz ) );
    Assert( nx >= -1.05f && nx <= 1.05f );
    Assert( ny >= -1.05f && ny <= 1.05f );
    Assert( nz >= -1.05f && nz <= 1.05f );

    float *pDst = m_pCurrNormal;
    *pDst++ = nx;
    *pDst++ = ny;
    *pDst = nz;
}

inline void	CVertexBuilder::Normal3fv( const float *n )
{
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE ); // Use the templatized version if you want to support compression
    Assert( n );
    Assert( m_pNormal && m_pCurrNormal );
    Assert( IsFinite( n[ 0 ] ) && IsFinite( n[ 1 ] ) && IsFinite( n[ 2 ] ) );
    Assert( n[ 0 ] >= -1.05f && n[ 0 ] <= 1.05f );
    Assert( n[ 1 ] >= -1.05f && n[ 1 ] <= 1.05f );
    Assert( n[ 2 ] >= -1.05f && n[ 2 ] <= 1.05f );

    float *pDst = m_pCurrNormal;
    *pDst++ = *n++;
    *pDst++ = *n++;
    *pDst = *n;
}

inline void	CVertexBuilder::NormalDelta3f( float nx , float ny , float nz )
{
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE ); // Use the templatized version if you want to support compression
    Assert( m_pNormal );
    Assert( IsFinite( nx ) && IsFinite( ny ) && IsFinite( nz ) );

    float *pDst = m_pCurrNormal;
    *pDst++ = nx;
    *pDst++ = ny;
    *pDst = nz;
}

inline void	CVertexBuilder::NormalDelta3fv( const float *n )
{
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE ); // Use the templatized version if you want to support compression
    Assert( n );
    Assert( m_pNormal && m_pCurrNormal );
    Assert( IsFinite( n[ 0 ] ) && IsFinite( n[ 1 ] ) && IsFinite( n[ 2 ] ) );

    float *pDst = m_pCurrNormal;
    *pDst++ = *n++;
    *pDst++ = *n++;
    *pDst = *n;
}

//-----------------------------------------------------------------------------
// Templatized normal setting methods which support compressed vertices
//-----------------------------------------------------------------------------
template <VertexCompressionType_t T> inline void CVertexBuilder::CompressedNormal3f( float nx , float ny , float nz )
{
    Assert( T == m_CompressionType );
    Assert( m_pNormal && m_pCurrNormal );
    Assert( IsFinite( nx ) && IsFinite( ny ) && IsFinite( nz ) );
    Assert( nx >= -1.05f && nx <= 1.05f );
    Assert( ny >= -1.05f && ny <= 1.05f );
    Assert( nz >= -1.05f && nz <= 1.05f );
    // FIXME: studiorender is passing in non-unit normals
    //float lengthSqd = nx*nx + ny*ny + nz*nz;
    //Assert( lengthSqd >= 0.95f && lengthSqd <= 1.05f );

    if ( T == VERTEX_COMPRESSION_ON )
    {
    #if		( COMPRESSED_NORMALS_TYPE == COMPRESSED_NORMALS_SEPARATETANGENTS_SHORT2 )
        PackNormal_SHORT2( nx , ny , nz , ( unsigned int * ) m_pCurrNormal );

    #else //( COMPRESSED_NORMALS_TYPE == COMPRESSED_NORMALS_COMBINEDTANGENTS_UBYTE4 )
            // NOTE: write the normal into the lower 16 bits of a word, clearing the top 16 bits - a userdata4
            //       tangent must be written into the upper 16 bits by CompressedUserData() *AFTER* this.
        PackNormal_UBYTE4( nx , ny , nz , ( unsigned int * ) m_pCurrNormal );
    #endif
    }
    else
    {
        float *pDst = m_pCurrNormal;
        *pDst++ = nx;
        *pDst++ = ny;
        *pDst = nz;
    }
}

template <VertexCompressionType_t T> inline void CVertexBuilder::CompressedNormal3fv( const float *n )
{
    Assert( n );
    CompressedNormal3f<T>( n[ 0 ] , n[ 1 ] , n[ 2 ] );
}

//-----------------------------------------------------------------------------
// Color setting methods
//-----------------------------------------------------------------------------
inline void	CVertexBuilder::Color3f( float r , float g , float b )
{
    Assert( m_pColor && m_pCurrColor );
    Assert( IsFinite( r ) && IsFinite( g ) && IsFinite( b ) );
    Assert( ( r >= 0.0 ) && ( g >= 0.0 ) && ( b >= 0.0 ) );
    Assert( ( r <= 1.0 ) && ( g <= 1.0 ) && ( b <= 1.0 ) );

    int col = ( FastFToC( b ) ) | ( FastFToC( g ) << 8 ) | ( FastFToC( r ) << 16 ) | 0xFF000000;
    *( int* ) m_pCurrColor = col;
}

inline void	CVertexBuilder::Color3fv( const float *rgb )
{
    Assert( rgb );
    Assert( m_pColor && m_pCurrColor );
    Assert( IsFinite( rgb[ 0 ] ) && IsFinite( rgb[ 1 ] ) && IsFinite( rgb[ 2 ] ) );
    Assert( ( rgb[ 0 ] >= 0.0 ) && ( rgb[ 1 ] >= 0.0 ) && ( rgb[ 2 ] >= 0.0 ) );
    Assert( ( rgb[ 0 ] <= 1.0 ) && ( rgb[ 1 ] <= 1.0 ) && ( rgb[ 2 ] <= 1.0 ) );

    int col = ( FastFToC( rgb[ 2 ] ) ) | ( FastFToC( rgb[ 1 ] ) << 8 ) | ( FastFToC( rgb[ 0 ] ) << 16 ) | 0xFF000000;
    *( int* ) m_pCurrColor = col;
}

inline void	CVertexBuilder::Color4f( float r , float g , float b , float a )
{
    Assert( m_pColor && m_pCurrColor );
    Assert( IsFinite( r ) && IsFinite( g ) && IsFinite( b ) && IsFinite( a ) );
    Assert( ( r >= 0.0 ) && ( g >= 0.0 ) && ( b >= 0.0 ) && ( a >= 0.0 ) );
    Assert( ( r <= 1.0 ) && ( g <= 1.0 ) && ( b <= 1.0 ) && ( a <= 1.0 ) );

    int col = ( FastFToC( b ) ) | ( FastFToC( g ) << 8 ) | ( FastFToC( r ) << 16 ) | ( FastFToC( a ) << 24 );
    *( int* ) m_pCurrColor = col;
}

inline void	CVertexBuilder::Color4fv( const float *rgba )
{
    Assert( rgba );
    Assert( m_pColor && m_pCurrColor );
    Assert( IsFinite( rgba[ 0 ] ) && IsFinite( rgba[ 1 ] ) && IsFinite( rgba[ 2 ] ) && IsFinite( rgba[ 3 ] ) );
    Assert( ( rgba[ 0 ] >= 0.0 ) && ( rgba[ 1 ] >= 0.0 ) && ( rgba[ 2 ] >= 0.0 ) && ( rgba[ 3 ] >= 0.0 ) );
    Assert( ( rgba[ 0 ] <= 1.0 ) && ( rgba[ 1 ] <= 1.0 ) && ( rgba[ 2 ] <= 1.0 ) && ( rgba[ 3 ] <= 1.0 ) );

    int col = ( FastFToC( rgba[ 2 ] ) ) | ( FastFToC( rgba[ 1 ] ) << 8 ) | ( FastFToC( rgba[ 0 ] ) << 16 ) | ( FastFToC( rgba[ 3 ] ) << 24 );
    *( int* ) m_pCurrColor = col;
}

//-----------------------------------------------------------------------------
// Faster versions of color
//-----------------------------------------------------------------------------

// note that on the OSX target (OpenGL) whenever there is vertex data being written as bytes - they need to be written in R,G,B,A memory order

inline void CVertexBuilder::Color3ub( unsigned char r , unsigned char g , unsigned char b )
{
    Assert( m_pColor && m_pCurrColor );
#ifdef OPENGL_SWAP_COLORS
    int col = r | ( g << 8 ) | ( b << 16 ) | 0xFF000000;	// r, g, b, a in memory
#else
    int col = b | ( g << 8 ) | ( r << 16 ) | 0xFF000000;
#endif

    *( int* ) m_pCurrColor = col;
}

inline void CVertexBuilder::Color3ubv( unsigned char const* rgb )
{
    Assert( rgb );
    Assert( m_pColor && m_pCurrColor );
#ifdef OPENGL_SWAP_COLORS
    int col = rgb[ 0 ] | ( rgb[ 1 ] << 8 ) | ( rgb[ 2 ] << 16 ) | 0xFF000000;	// r, g, b, a in memory
#else
    int col = rgb[ 2 ] | ( rgb[ 1 ] << 8 ) | ( rgb[ 0 ] << 16 ) | 0xFF000000;
#endif

    *( int* ) m_pCurrColor = col;
}

inline void CVertexBuilder::Color4ub( unsigned char r , unsigned char g , unsigned char b , unsigned char a )
{
    Assert( m_pColor && m_pCurrColor );
#ifdef OPENGL_SWAP_COLORS
    int col = r | ( g << 8 ) | ( b << 16 ) | ( a << 24 );	// r, g, b, a in memory
#else
    int col = b | ( g << 8 ) | ( r << 16 ) | ( a << 24 );
#endif

    *( int* ) m_pCurrColor = col;
}

inline void CVertexBuilder::Color4ubv( unsigned char const* rgba )
{
    Assert( rgba );
    Assert( m_pColor && m_pCurrColor );
#ifdef OPENGL_SWAP_COLORS
    int col = rgba[ 0 ] | ( rgba[ 1 ] << 8 ) | ( rgba[ 2 ] << 16 ) | ( rgba[ 3 ] << 24 );	// r, g, b, a in memory
#else
    int col = rgba[ 2 ] | ( rgba[ 1 ] << 8 ) | ( rgba[ 0 ] << 16 ) | ( rgba[ 3 ] << 24 );
#endif
    *( int* ) m_pCurrColor = col;
}

FORCEINLINE void CVertexBuilder::Color4Packed( int packedColor )
{
    *( int* ) m_pCurrColor = packedColor;
}

FORCEINLINE int CVertexBuilder::PackColor4( unsigned char r , unsigned char g , unsigned char b , unsigned char a )
{
    return b | ( g << 8 ) | ( r << 16 ) | ( a << 24 );
}

inline void	CVertexBuilder::Specular3f( float r , float g , float b )
{
    Assert( m_pSpecular );
    Assert( IsFinite( r ) && IsFinite( g ) && IsFinite( b ) );
    Assert( ( r >= 0.0 ) && ( g >= 0.0 ) && ( b >= 0.0 ) );
    Assert( ( r <= 1.0 ) && ( g <= 1.0 ) && ( b <= 1.0 ) );

    unsigned char* pSpecular = &m_pSpecular[ m_nCurrentVertex * m_VertexSize_Specular ];
    int col = ( FastFToC( b ) ) | ( FastFToC( g ) << 8 ) | ( FastFToC( r ) << 16 ) | 0xFF000000;
    *( int* ) pSpecular = col;
}

inline void	CVertexBuilder::Specular3fv( const float *rgb )
{
    Assert( rgb );
    Assert( m_pSpecular );
    Assert( IsFinite( rgb[ 0 ] ) && IsFinite( rgb[ 1 ] ) && IsFinite( rgb[ 2 ] ) );
    Assert( ( rgb[ 0 ] >= 0.0 ) && ( rgb[ 1 ] >= 0.0 ) && ( rgb[ 2 ] >= 0.0 ) );
    Assert( ( rgb[ 0 ] <= 1.0 ) && ( rgb[ 1 ] <= 1.0 ) && ( rgb[ 2 ] <= 1.0 ) );

    unsigned char* pSpecular = &m_pSpecular[ m_nCurrentVertex * m_VertexSize_Specular ];
    int col = ( FastFToC( rgb[ 2 ] ) ) | ( FastFToC( rgb[ 1 ] ) << 8 ) | ( FastFToC( rgb[ 0 ] ) << 16 ) | 0xFF000000;
    *( int* ) pSpecular = col;
}

inline void	CVertexBuilder::Specular4f( float r , float g , float b , float a )
{
    Assert( m_pSpecular );
    Assert( IsFinite( r ) && IsFinite( g ) && IsFinite( b ) && IsFinite( a ) );
    Assert( ( r >= 0.0 ) && ( g >= 0.0 ) && ( b >= 0.0 ) && ( a >= 0.0 ) );
    Assert( ( r <= 1.0 ) && ( g <= 1.0 ) && ( b <= 1.0 ) && ( a <= 1.0f ) );

    unsigned char* pSpecular = &m_pSpecular[ m_nCurrentVertex * m_VertexSize_Specular ];
    int col = ( FastFToC( b ) ) | ( FastFToC( g ) << 8 ) | ( FastFToC( r ) << 16 ) | ( FastFToC( a ) << 24 );
    *( int* ) pSpecular = col;
}

inline void	CVertexBuilder::Specular4fv( const float *rgb )
{
    Assert( rgb );
    Assert( m_pSpecular );
    Assert( IsFinite( rgb[ 0 ] ) && IsFinite( rgb[ 1 ] ) && IsFinite( rgb[ 2 ] ) && IsFinite( rgb[ 3 ] ) );
    Assert( ( rgb[ 0 ] >= 0.0 ) && ( rgb[ 1 ] >= 0.0 ) && ( rgb[ 2 ] >= 0.0 ) && ( rgb[ 3 ] >= 0.0 ) );
    Assert( ( rgb[ 0 ] <= 1.0 ) && ( rgb[ 1 ] <= 1.0 ) && ( rgb[ 2 ] <= 1.0 ) && ( rgb[ 3 ] <= 1.0 ) );

    unsigned char* pSpecular = &m_pSpecular[ m_nCurrentVertex * m_VertexSize_Specular ];
    int col = ( FastFToC( rgb[ 2 ] ) ) | ( FastFToC( rgb[ 1 ] ) << 8 ) | ( FastFToC( rgb[ 0 ] ) << 16 ) | ( FastFToC( rgb[ 3 ] ) << 24 );
    *( int* ) pSpecular = col;
}

inline void CVertexBuilder::Specular3ub( unsigned char r , unsigned char g , unsigned char b )
{
    Assert( m_pSpecular );
    unsigned char *pSpecular = &m_pSpecular[ m_nCurrentVertex * m_VertexSize_Specular ];

#ifdef OPENGL_SWAP_COLORS
    int col = r | ( g << 8 ) | ( b << 16 ) | 0xFF000000;	// r, g, b, a in memory
#else
    int col = b | ( g << 8 ) | ( r << 16 ) | 0xFF000000;
#endif

    *( int* ) pSpecular = col;
}

inline void CVertexBuilder::Specular3ubv( unsigned char const *c )
{
    Assert( m_pSpecular );
    unsigned char *pSpecular = &m_pSpecular[ m_nCurrentVertex * m_VertexSize_Specular ];

#ifdef OPENGL_SWAP_COLORS
    int col = c[ 0 ] | ( c[ 1 ] << 8 ) | ( c[ 2 ] << 16 ) | 0xFF000000;	// r, g, b, a in memory
#else
    int col = c[ 2 ] | ( c[ 1 ] << 8 ) | ( c[ 0 ] << 16 ) | 0xFF000000;
#endif

    *( int* ) pSpecular = col;
}

inline void CVertexBuilder::Specular4ub( unsigned char r , unsigned char g , unsigned char b , unsigned char a )
{
    Assert( m_pSpecular );
    unsigned char *pSpecular = &m_pSpecular[ m_nCurrentVertex * m_VertexSize_Specular ];

#ifdef OPENGL_SWAP_COLORS
    int col = r | ( g << 8 ) | ( b << 16 ) | ( a << 24 );	// r, g, b, a in memory
#else
    int col = b | ( g << 8 ) | ( r << 16 ) | ( a << 24 );
#endif

    *( int* ) pSpecular = col;
}

inline void CVertexBuilder::Specular4ubv( unsigned char const *c )
{
    Assert( m_pSpecular );
    unsigned char *pSpecular = &m_pSpecular[ m_nCurrentVertex * m_VertexSize_Specular ];

#ifdef OPENGL_SWAP_COLORS
    int col = c[ 0 ] | ( c[ 1 ] << 8 ) | ( c[ 2 ] << 16 ) | ( c[ 3 ] << 24 );
#else
    int col = c[ 2 ] | ( c[ 1 ] << 8 ) | ( c[ 0 ] << 16 ) | ( c[ 3 ] << 24 );
#endif

    *( int* ) pSpecular = col;
}

//-----------------------------------------------------------------------------
// Texture coordinate setting methods
//-----------------------------------------------------------------------------
inline void CVertexBuilder::TexCoord1f( int nStage , float s )
{
    Assert( m_pTexCoord[ nStage ] && m_pCurrTexCoord[ nStage ] );
    Assert( IsFinite( s ) );

    float *pDst = m_pCurrTexCoord[ nStage ];
    *pDst = s;
}

inline void	CVertexBuilder::TexCoord2f( int nStage , float s , float t )
{
    Assert( m_pTexCoord[ nStage ] && m_pCurrTexCoord[ nStage ] );
    Assert( IsFinite( s ) && IsFinite( t ) );

    float *pDst = m_pCurrTexCoord[ nStage ];
    *pDst++ = s;
    *pDst = t;
}

inline void	CVertexBuilder::TexCoord2fv( int nStage , const float *st )
{
    Assert( st );
    Assert( m_pTexCoord[ nStage ] && m_pCurrTexCoord[ nStage ] );
    Assert( IsFinite( st[ 0 ] ) && IsFinite( st[ 1 ] ) );

    float *pDst = m_pCurrTexCoord[ nStage ];
    *pDst++ = *st++;
    *pDst = *st;
}

inline void	CVertexBuilder::TexCoord3f( int stage , float s , float t , float u )
{
    // Tried to add too much!
    Assert( m_pTexCoord[ stage ] && m_pCurrTexCoord[ stage ] );
    Assert( IsFinite( s ) && IsFinite( t ) && IsFinite( u ) );
    float *pDst = m_pCurrTexCoord[ stage ];
    *pDst++ = s;
    *pDst++ = t;
    *pDst = u;
}

inline void	CVertexBuilder::TexCoord3fv( int stage , const float *stu )
{
    Assert( stu );
    Assert( m_pTexCoord[ stage ] && m_pCurrTexCoord[ stage ] );
    Assert( IsFinite( stu[ 0 ] ) && IsFinite( stu[ 1 ] ) && IsFinite( stu[ 2 ] ) );

    float *pDst = m_pCurrTexCoord[ stage ];
    *pDst++ = *stu++;
    *pDst++ = *stu++;
    *pDst = *stu;
}

inline void	CVertexBuilder::TexCoord4f( int stage , float s , float t , float u , float v )
{
    // Tried to add too much!
    Assert( m_pTexCoord[ stage ] && m_pCurrTexCoord[ stage ] );
    Assert( IsFinite( s ) && IsFinite( t ) && IsFinite( u ) );
    float *pDst = m_pCurrTexCoord[ stage ];
    *pDst++ = s;
    *pDst++ = t;
    *pDst++ = u;
    *pDst = v;
}

inline void	CVertexBuilder::TexCoord4fv( int stage , const float *stuv )
{
    Assert( stuv );
    Assert( m_pTexCoord[ stage ] && m_pCurrTexCoord[ stage ] );
    Assert( IsFinite( stuv[ 0 ] ) && IsFinite( stuv[ 1 ] ) && IsFinite( stuv[ 2 ] ) );

    float *pDst = m_pCurrTexCoord[ stage ];
    *pDst++ = *stuv++;
    *pDst++ = *stuv++;
    *pDst++ = *stuv++;
    *pDst = *stuv;
}

inline void CVertexBuilder::TexCoordSubRect2f( int stage , float s , float t , float offsetS , float offsetT , float scaleS , float scaleT )
{
    Assert( m_pTexCoord[ stage ] && m_pCurrTexCoord[ stage ] );
    Assert( IsFinite( s ) && IsFinite( t ) );

    float *pDst = m_pCurrTexCoord[ stage ];
    *pDst++ = ( s * scaleS ) + offsetS;
    *pDst = ( t * scaleT ) + offsetT;
}

inline void CVertexBuilder::TexCoordSubRect2fv( int stage , const float *st , const float *offset , const float *scale )
{
    Assert( st );
    Assert( m_pTexCoord[ stage ] && m_pCurrTexCoord[ stage ] );
    Assert( IsFinite( st[ 0 ] ) && IsFinite( st[ 1 ] ) );

    float *pDst = m_pCurrTexCoord[ stage ];
    *pDst++ = ( *st++ * *scale++ ) + *offset++;
    *pDst = ( *st * *scale ) + *offset;
}

//-----------------------------------------------------------------------------
// Tangent space setting methods
//-----------------------------------------------------------------------------
inline void CVertexBuilder::TangentS3f( float sx , float sy , float sz )
{
    Assert( m_pTangentS );
    Assert( IsFinite( sx ) && IsFinite( sy ) && IsFinite( sz ) );

    float* pTangentS = OffsetFloatPointer( m_pTangentS , m_nCurrentVertex , m_VertexSize_TangentS );
    *pTangentS++ = sx;
    *pTangentS++ = sy;
    *pTangentS = sz;
}

inline void CVertexBuilder::TangentS3fv( const float* s )
{
    Assert( s );
    Assert( m_pTangentS );
    Assert( IsFinite( s[ 0 ] ) && IsFinite( s[ 1 ] ) && IsFinite( s[ 2 ] ) );

    float* pTangentS = OffsetFloatPointer( m_pTangentS , m_nCurrentVertex , m_VertexSize_TangentS );
    *pTangentS++ = *s++;
    *pTangentS++ = *s++;
    *pTangentS = *s;
}

inline void CVertexBuilder::TangentT3f( float tx , float ty , float tz )
{
    Assert( m_pTangentT );
    Assert( IsFinite( tx ) && IsFinite( ty ) && IsFinite( tz ) );

    float* pTangentT = OffsetFloatPointer( m_pTangentT , m_nCurrentVertex , m_VertexSize_TangentT );
    *pTangentT++ = tx;
    *pTangentT++ = ty;
    *pTangentT = tz;
}

inline void CVertexBuilder::TangentT3fv( const float* t )
{
    Assert( t );
    Assert( m_pTangentT );
    Assert( IsFinite( t[ 0 ] ) && IsFinite( t[ 1 ] ) && IsFinite( t[ 2 ] ) );

    float* pTangentT = OffsetFloatPointer( m_pTangentT , m_nCurrentVertex , m_VertexSize_TangentT );
    *pTangentT++ = *t++;
    *pTangentT++ = *t++;
    *pTangentT = *t;
}

//-----------------------------------------------------------------------------
// Wrinkle setting methods
//-----------------------------------------------------------------------------
inline void CVertexBuilder::Wrinkle1f( float flWrinkle )
{
    Assert( m_pWrinkle );
    Assert( IsFinite( flWrinkle ) );

    float *pWrinkle = OffsetFloatPointer( m_pWrinkle , m_nCurrentVertex , m_VertexSize_Wrinkle );
    *pWrinkle = flWrinkle;
}

//-----------------------------------------------------------------------------
// Bone weight setting methods
//-----------------------------------------------------------------------------
inline void CVertexBuilder::BoneWeight( int idx , float weight )
{
    Assert( m_pBoneWeight );
    Assert( IsFinite( weight ) );
    Assert( idx >= 0 );
    Assert( m_NumBoneWeights == 2 );

    // This test is here because we store N-1 bone weights (the Nth is computed in
    // the vertex shader as "1 - C", where C is the sum of the (N-1) other weights)
    if ( idx < m_NumBoneWeights )
    {
        float* pBoneWeight = OffsetFloatPointer( m_pBoneWeight , m_nCurrentVertex , m_VertexSize_BoneWeight );
        pBoneWeight[ idx ] = weight;
    }
}

inline void CVertexBuilder::BoneWeights2( float weight1 , float weight2 )
{
    Assert( m_pBoneWeight );
    Assert( IsFinite( weight1 ) && IsFinite( weight2 ) );

    // This test is here because we store N-1 bone weights (the Nth is computed in
    // the vertex shader as "1 - C", where C is the sum of the (N-1) other weights)
    float* pBoneWeight = OffsetFloatPointer( m_pBoneWeight , m_nCurrentVertex , m_VertexSize_BoneWeight );
    pBoneWeight[ 0 ] = weight1;
    pBoneWeight[ 1 ] = weight2;
}

inline void CVertexBuilder::BoneMatrix( int idx , int matrixIdx )
{
    Assert( m_pBoneMatrixIndex );
    Assert( idx >= 0 );
    Assert( idx < 4 );

    // garymcthack
    if ( matrixIdx == BONE_MATRIX_INDEX_INVALID )
    {
        matrixIdx = 0;
    }
    Assert( ( matrixIdx >= 0 ) && ( matrixIdx < 53 ) );

#ifndef NEW_SKINNING
    unsigned char* pBoneMatrix = &m_pBoneMatrixIndex[ m_nCurrentVertex * m_VertexSize_BoneMatrixIndex ];
    pBoneMatrix[ idx ] = ( unsigned char ) matrixIdx;
#else
    float* pBoneMatrix = &m_pBoneMatrixIndex[ m_nCurrentVertex * m_VertexSize_BoneMatrixIndex ];
    pBoneMatrix[ idx ] = matrixIdx;
#endif
}

inline void CVertexBuilder::BoneMatrices4( int matrixIdx0 , int matrixIdx1 , int matrixIdx2 , int matrixIdx3 )
{
    Assert( m_pBoneMatrixIndex );

    // garymcthack
    Assert( matrixIdx0 != BONE_MATRIX_INDEX_INVALID );
    Assert( matrixIdx1 != BONE_MATRIX_INDEX_INVALID );
    Assert( matrixIdx2 != BONE_MATRIX_INDEX_INVALID );
    Assert( matrixIdx3 != BONE_MATRIX_INDEX_INVALID );

#ifndef NEW_SKINNING
    int nVal = matrixIdx0 | ( matrixIdx1 << 8 ) | ( matrixIdx2 << 16 ) | ( matrixIdx3 << 24 );
    int* pBoneMatrix = ( int* ) ( &m_pBoneMatrixIndex[ m_nCurrentVertex * m_VertexSize_BoneMatrixIndex ] );
    *pBoneMatrix = nVal;
#else
    float* pBoneMatrix = &m_pBoneMatrixIndex[ m_nCurrentVertex * m_VertexSize_BoneMatrixIndex ];
    pBoneMatrix[ 0 ] = matrixIdx0;
    pBoneMatrix[ 1 ] = matrixIdx1;
    pBoneMatrix[ 2 ] = matrixIdx2;
    pBoneMatrix[ 3 ] = matrixIdx3;
#endif
}

//-----------------------------------------------------------------------------
// Templatized bone weight setting methods which support compressed vertices
//-----------------------------------------------------------------------------
template <VertexCompressionType_t T> inline void CVertexBuilder::CompressedBoneWeight3fv( const float * pWeights )
{
    Assert( T == m_CompressionType );
    Assert( m_pBoneWeight );
    Assert( pWeights );

    float *pDestWeights = OffsetFloatPointer( m_pBoneWeight , m_nCurrentVertex , m_VertexSize_BoneWeight );

    if ( T == VERTEX_COMPRESSION_ON )
    {
        // Quantize to 15 bits per weight (we use D3DDECLTYPE_SHORT2)
        // NOTE: we perform careful normalization (weights sum to 1.0f in the vertex shader), so
        // as to avoid cracking at boundaries between meshes with different numbers of weights
        // per vertex. For example, (1) needs to yield the same normalized weights as (1,0),
        // and (0.5,0.49) needs to normalize the same normalized weights as (0.5,0.49,0).
        // The key is that values which are *computed* in the shader (e.g. the second weight
        // in a 2-weight mesh) must exactly equal values which are *read* from the vertex
        // stream (e.g. the second weight in a 3-weight mesh).

        // Only 1 or 2 weights (SHORT2N) supported for compressed verts so far
        Assert( m_NumBoneWeights <= 2 );

        const int WEIGHT0_SHIFT = IsX360() ? 16 : 0;
        const int WEIGHT1_SHIFT = IsX360() ? 0 : 16;
        unsigned int *weights = ( unsigned int * ) pDestWeights;

        // We scale our weights so that they sum to 32768, then subtract 1 (which gets added
        // back in the shader), because dividing by 32767 introduces nasty rounding issues.
        Assert( IsFinite( pWeights[ 0 ] ) && ( pWeights[ 0 ] >= 0.0f ) && ( pWeights[ 0 ] <= 1.0f ) );
        unsigned int weight0 = Float2Int( pWeights[ 0 ] * 32768.0f );
        *weights = ( 0x0000FFFF & ( weight0 - 1 ) ) << WEIGHT0_SHIFT;

        if ( m_NumBoneWeights > 1 )
        {
            // This path for 3 weights per vert (2 are stored and the 3rd is computed
            // in the shader - we do post-quantization normalization here in such a
            // way as to avoid mesh-boundary cracking)
            Assert( m_NumBoneWeights == 2 );
            Assert( IsFinite( pWeights[ 1 ] ) && ( pWeights[ 1 ] >= 0.0f ) && ( pWeights[ 1 ] <= 1.0f ) );
            Assert( IsFinite( pWeights[ 2 ] ) && ( pWeights[ 2 ] >= 0.0f ) && ( pWeights[ 2 ] <= 1.0f ) );
            unsigned int weight1 = Float2Int( pWeights[ 1 ] * 32768.0f );
            unsigned int weight2 = Float2Int( pWeights[ 2 ] * 32768.0f );
            Assert( ( weight0 + weight1 + weight2 ) <= 32768 );
            unsigned int residual = 32768 - ( weight0 + weight1 + weight2 );
            weight1 += residual; // Normalize
            *weights |= ( 0x0000FFFF & ( weight1 - 1 ) ) << WEIGHT1_SHIFT;
        }
    }
    else	// Uncompressed path
    {
        pDestWeights[ 0 ] = pWeights[ 0 ];
        pDestWeights[ 1 ] = pWeights[ 1 ];
    }
}

//-----------------------------------------------------------------------------
// Generic per-vertex data setting method
//-----------------------------------------------------------------------------
inline void CVertexBuilder::UserData( const float* pData )
{
    Assert( m_CompressionType == VERTEX_COMPRESSION_NONE ); // Use the templatized version if you want to support compression
    Assert( pData );

    int userDataSize = 4; // garymcthack
    float *pUserData = OffsetFloatPointer( m_pUserData , m_nCurrentVertex , m_VertexSize_UserData );
    memcpy( pUserData , pData , sizeof( float ) * userDataSize );
}

//-----------------------------------------------------------------------------
// Templatized generic per-vertex data setting method which supports compressed vertices
//-----------------------------------------------------------------------------
template <VertexCompressionType_t T> inline void CVertexBuilder::CompressedUserData( const float* pData )
{
    Assert( T == m_CompressionType );
    Assert( pData );
    // This is always in fact a tangent vector, not generic 'userdata'
    Assert( IsFinite( pData[ 0 ] ) && IsFinite( pData[ 1 ] ) && IsFinite( pData[ 2 ] ) );
    Assert( pData[ 0 ] >= -1.05f && pData[ 0 ] <= 1.05f );
    Assert( pData[ 1 ] >= -1.05f && pData[ 1 ] <= 1.05f );
    Assert( pData[ 2 ] >= -1.05f && pData[ 2 ] <= 1.05f );
    Assert( pData[ 3 ] == +1.0f || pData[ 3 ] == -1.0f );
    // FIXME: studiorender is passing in non-unit normals
    //float lengthSqd = pData[0]*pData[0] + pData[1]*pData[1] + pData[2]*pData[2];
    //Assert( lengthSqd >= 0.95f && lengthSqd <= 1.05f );

    if ( T == VERTEX_COMPRESSION_ON )
    {
        float binormalSign = pData[ 3 ];

    #if		( COMPRESSED_NORMALS_TYPE == COMPRESSED_NORMALS_SEPARATETANGENTS_SHORT2 )
        float *pUserData = OffsetFloatPointer( m_pUserData , m_nCurrentVertex , m_VertexSize_UserData );
        PackNormal_SHORT2( pData , ( unsigned int * ) pUserData , binormalSign );
    #else //( COMPRESSED_NORMALS_TYPE == COMPRESSED_NORMALS_COMBINEDTANGENTS_UBYTE4 )
            // FIXME: add a combined CompressedNormalAndTangent() accessor, to avoid reading back from write-combined memory here
            // The normal should have already been written into the lower 16
            // bits - here, we OR in the tangent into the upper 16 bits
        unsigned int existingNormalData = *( unsigned int * ) m_pCurrNormal;
        Assert( ( existingNormalData & 0xFFFF0000 ) == 0 );
        bool bIsTangent = true;
        unsigned int tangentData = 0;
        PackNormal_UBYTE4( pData , &tangentData , bIsTangent , binormalSign );
        *( unsigned int * ) m_pCurrNormal = existingNormalData | tangentData;
    #endif
    }
    else
    {
        int userDataSize = 4; // garymcthack
        float *pUserData = OffsetFloatPointer( m_pUserData , m_nCurrentVertex , m_VertexSize_UserData );
        memcpy( pUserData , pData , sizeof( float ) * userDataSize );
    }
}

//-----------------------------------------------------------------------------
//
// Helper class used to define index buffers
//
//-----------------------------------------------------------------------------
class CIndexBuilder : private IndexDesc_t
{
public:
    CIndexBuilder();
    CIndexBuilder( IIndexBuffer *pIndexBuffer , MaterialIndexFormat_t fmt = MATERIAL_INDEX_FORMAT_UNKNOWN );
    ~CIndexBuilder();

    // Begins, ends modification of the index buffer (returns true if the lock succeeded)
    // A lock may not succeed if append is set to true and there isn't enough room
    // NOTE: Append is only used with dynamic index buffers; it's ignored for static buffers
    bool Lock( int nMaxIndexCount , short nIndexOffset , bool bAppend = false );
    void Unlock();

    // Spews the current data
    // NOTE: Can only be called during a lock/unlock block
    void SpewData();

    // Returns the number of indices we can fit into the buffer without needing to discard
    int GetRoomRemaining() const;

    // Binds this index buffer
    void Bind( IMatRenderContext *pContext );

    // Returns the byte offset
    int Offset() const;

    // Begins, ends modification of the index buffer
    // NOTE: IndexOffset is the number to add to all indices written into the buffer;
    // useful when using dynamic vertex buffers.
    void Begin( IIndexBuffer *pIndexBuffer , int nMaxIndexCount , short nIndexOffset = 0 );
    void End( bool bSpewData = false );

    // Locks the index buffer to modify existing data
    // Passing nVertexCount == -1 says to lock all the vertices for modification.
    // Pass 0 for numIndices to not lock the index buffer.
    void BeginModify( IIndexBuffer *pIndexBuffer , int firstIndex = 0 , int numIndices = 0 , short nIndexOffset = 0 );
    void EndModify( bool bSpewData = false );

    // returns the number of indices
    int	IndexCount() const;

    // Returns the total number of indices across all Locks()
    int TotalIndexCount() const;

    // Resets the mesh builder so it points to the start of everything again
    void Reset();

    // Selects the nth Index
    void SelectIndex( int nBufferIndex );

    // Advances the current index by one
    void AdvanceIndex();
    void AdvanceIndices( int numIndices );

    int GetCurrentIndex();
    int GetFirstIndex() const;

    unsigned short const* Index() const;

    // Used to define the indices (only used if you aren't using primitives)
    void Index( unsigned short nIndex );

    // Fast Index! No need to call advance index, and no random access allowed
    void FastIndex( unsigned short nIndex );

    // NOTE: This version is the one you really want to achieve write-combining;
    // Write combining only works if you write in 4 bytes chunks.
    void FastIndex2( unsigned short nIndex1 , unsigned short nIndex2 );

    // Generates indices for a particular primitive type
    void GenerateIndices( MaterialPrimitiveType_t primitiveType , int numIndices );

    // FIXME: Remove! Backward compat so we can use this from a CMeshBuilder.
    void AttachBegin( IMesh* pMesh , int nMaxIndexCount , const MeshDesc_t &desc );
    void AttachEnd();
    void AttachBeginModify( IMesh* pMesh , int numIndices , const MeshDesc_t &desc );
    void AttachEndModify();

    void FastTriangle( unsigned short startVert );
    void FastQuad( unsigned short startVert );
    void FastPolygon( unsigned short startVert , unsigned short numTriangles );
    void FastPolygonList( unsigned short startVert , short *pVertexCount , short polygonCount );
    void FastIndexList( const unsigned short *pIndexList , short startVert , int indexCount );

private:
    // The mesh we're modifying
    IIndexBuffer * m_pIndexBuffer;

    // Max number of indices
    int				m_nMaxIndexCount;

    // Number of indices
    int				m_nIndexCount;

    // Offset to add to each index as it's written into the buffer
    short			m_nIndexOffset;

    // The current index
    mutable int		m_nCurrentIndex;

    // Total number of indices appended
    int				m_nTotalIndexCount;

    // First index buffer offset + first index
    unsigned int	m_nBufferOffset;
    unsigned int	m_nBufferFirstIndex;

    // Used to make sure Begin/End calls and BeginModify/EndModify calls match.
    bool			m_bModify;
};

//-----------------------------------------------------------------------------
//
// Inline methods related to CIndexBuilder
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
inline CIndexBuilder::CIndexBuilder() : m_pIndexBuffer( 0 ) , m_nMaxIndexCount( 0 ) ,
m_nIndexCount( 0 ) , m_nCurrentIndex( 0 )
{
    m_nTotalIndexCount = 0;
    m_nBufferOffset = INVALID_BUFFER_OFFSET;
    m_nBufferFirstIndex = 0;
}

inline CIndexBuilder::CIndexBuilder( IIndexBuffer *pIndexBuffer , MaterialIndexFormat_t fmt )
{
    m_pIndexBuffer = pIndexBuffer;
    m_nBufferOffset = INVALID_BUFFER_OFFSET;
    m_nBufferFirstIndex = 0;
    m_nIndexCount = 0;
    m_nCurrentIndex = 0;
    m_nMaxIndexCount = 0;
    m_nTotalIndexCount = 0;
    if ( m_pIndexBuffer->IsDynamic() )
    {
        m_pIndexBuffer->BeginCastBuffer( fmt );
    }
    else
    {
        Assert( m_pIndexBuffer->IndexFormat() == fmt );
    }
}

inline CIndexBuilder::~CIndexBuilder()
{
    if ( m_pIndexBuffer && m_pIndexBuffer->IsDynamic() )
    {
        m_pIndexBuffer->EndCastBuffer();
    }
}

//-----------------------------------------------------------------------------
// Begins, ends modification of the index buffer
//-----------------------------------------------------------------------------
inline bool CIndexBuilder::Lock( int nMaxIndexCount , short nIndexOffset , bool bAppend )
{
    Assert( m_pIndexBuffer );
    m_bModify = false;
    m_nIndexOffset = nIndexOffset;
    m_nMaxIndexCount = nMaxIndexCount;
    m_nIndexCount = 0;
    bool bFirstLock = ( m_nBufferOffset == INVALID_BUFFER_OFFSET );
    if ( bFirstLock )
    {
        bAppend = false;
    }
    if ( !bAppend )
    {
        m_nTotalIndexCount = 0;
    }
    Reset();

    // Lock the index buffer
    if ( !m_pIndexBuffer->Lock( m_nMaxIndexCount , bAppend , *this ) )
    {
        m_nMaxIndexCount = 0;
        return false;
    }

    if ( bFirstLock )
    {
        m_nBufferOffset = m_nOffset;
        m_nBufferFirstIndex = m_nFirstIndex;
    }

    return true;
}

inline void CIndexBuilder::Unlock()
{
    Assert( !m_bModify && m_pIndexBuffer );

    m_pIndexBuffer->Unlock( m_nIndexCount , *this );
    m_nTotalIndexCount += m_nIndexCount;

    m_nMaxIndexCount = 0;
}

inline void CIndexBuilder::SpewData()
{
    m_pIndexBuffer->Spew( m_nIndexCount , *this );
}

//-----------------------------------------------------------------------------
// Binds this index buffer
//-----------------------------------------------------------------------------
inline void CIndexBuilder::Bind( IMatRenderContext *pContext )
{
    if ( m_pIndexBuffer && ( m_nBufferOffset != INVALID_BUFFER_OFFSET ) )
    {
        pContext->BindIndexBuffer( m_pIndexBuffer , m_nBufferOffset );
    }
    else
    {
        pContext->BindIndexBuffer( NULL , 0 );
    }
}

//-----------------------------------------------------------------------------
// Returns the byte offset
//-----------------------------------------------------------------------------
inline int CIndexBuilder::Offset() const
{
    return m_nBufferOffset;
}

inline int CIndexBuilder::GetFirstIndex() const
{
    return m_nBufferFirstIndex;
}

//-----------------------------------------------------------------------------
// Begins, ends modification of the index buffer
//-----------------------------------------------------------------------------
inline void CIndexBuilder::Begin( IIndexBuffer *pIndexBuffer , int nMaxIndexCount , short nIndexOffset )
{
    Assert( pIndexBuffer && ( !m_pIndexBuffer ) );

    m_pIndexBuffer = pIndexBuffer;
    m_nIndexCount = 0;
    m_nMaxIndexCount = nMaxIndexCount;
    m_nIndexOffset = nIndexOffset;

    m_bModify = false;

    // Lock the index buffer
    m_pIndexBuffer->Lock( m_nMaxIndexCount , false , *this );

    // Point to the start of the buffers..
    Reset();
}

inline void CIndexBuilder::End( bool bSpewData )
{
    // Make sure they called Begin()
    Assert( !m_bModify );

    if ( bSpewData )
    {
        m_pIndexBuffer->Spew( m_nIndexCount , *this );
    }

    // Unlock our buffers
    m_pIndexBuffer->Unlock( m_nIndexCount , *this );

    m_pIndexBuffer = 0;
    m_nMaxIndexCount = 0;
}

//-----------------------------------------------------------------------------
// Begins, ends modification of an existing index buffer which has already been filled out
//-----------------------------------------------------------------------------
inline void CIndexBuilder::BeginModify( IIndexBuffer* pIndexBuffer , int nFirstIndex , int nIndexCount , short nIndexOffset )
{
    m_pIndexBuffer = pIndexBuffer;
    m_nIndexCount = nIndexCount;
    m_nMaxIndexCount = nIndexCount;
    m_nIndexOffset = nIndexOffset;
    m_bModify = true;

    // Lock the vertex and index buffer
    m_pIndexBuffer->ModifyBegin( false , nFirstIndex , nIndexCount , *this );

    // Point to the start of the buffers..
    Reset();
}

inline void CIndexBuilder::EndModify( bool bSpewData )
{
    Assert( m_pIndexBuffer );
    Assert( m_bModify );	// Make sure they called BeginModify.

    if ( bSpewData )
    {
        m_pIndexBuffer->Spew( m_nIndexCount , *this );
    }

    // Unlock our buffers
    m_pIndexBuffer->ModifyEnd( *this );

    m_pIndexBuffer = 0;
    m_nMaxIndexCount = 0;
}

//-----------------------------------------------------------------------------
// FIXME: Remove! Backward compat so we can use this from a CMeshBuilder.
//-----------------------------------------------------------------------------
inline void CIndexBuilder::AttachBegin( IMesh* pMesh , int nMaxIndexCount , const MeshDesc_t &desc )
{
    m_pIndexBuffer = pMesh;
    m_nIndexCount = 0;
    m_nMaxIndexCount = nMaxIndexCount;

    m_bModify = false;

    // Copy relevant data from the mesh desc
    m_nIndexOffset = desc.m_nFirstVertex;
    m_pIndices = desc.m_pIndices;
    m_nIndexSize = desc.m_nIndexSize;

    // Point to the start of the buffers..
    Reset();
}

inline void CIndexBuilder::AttachEnd()
{
    Assert( m_pIndexBuffer );
    Assert( !m_bModify );	// Make sure they called AttachBegin.

    m_pIndexBuffer = 0;
    m_nMaxIndexCount = 0;
}

inline void CIndexBuilder::AttachBeginModify( IMesh* pMesh , int nIndexCount , const MeshDesc_t &desc )
{
    m_pIndexBuffer = pMesh;
    m_nIndexCount = nIndexCount;
    m_nMaxIndexCount = nIndexCount;
    m_bModify = true;

    // Copy relevant data from the mesh desc
    m_nIndexOffset = desc.m_nFirstVertex;
    m_pIndices = desc.m_pIndices;
    m_nIndexSize = desc.m_nIndexSize;

    // Point to the start of the buffers..
    Reset();
}

inline void CIndexBuilder::AttachEndModify()
{
    Assert( m_pIndexBuffer );
    Assert( m_bModify );	// Make sure they called AttachBeginModify.

    m_pIndexBuffer = 0;
    m_nMaxIndexCount = 0;
}

//-----------------------------------------------------------------------------
// Resets the index buffer builder so it points to the start of everything again
//-----------------------------------------------------------------------------
inline void CIndexBuilder::Reset()
{
    m_nCurrentIndex = 0;
}

//-----------------------------------------------------------------------------
// returns the number of indices
//-----------------------------------------------------------------------------
inline int CIndexBuilder::IndexCount() const
{
    return m_nIndexCount;
}

//-----------------------------------------------------------------------------
// Returns the total number of indices across all Locks()
//-----------------------------------------------------------------------------
inline int CIndexBuilder::TotalIndexCount() const
{
    return m_nTotalIndexCount;
}

//-----------------------------------------------------------------------------
// Advances the current index
//-----------------------------------------------------------------------------
inline void CIndexBuilder::AdvanceIndex()
{
    m_nCurrentIndex += m_nIndexSize;
    if ( m_nCurrentIndex > m_nIndexCount )
    {
        m_nIndexCount = m_nCurrentIndex;
    }
}

inline void CIndexBuilder::AdvanceIndices( int nIndices )
{
    m_nCurrentIndex += nIndices * m_nIndexSize;
    if ( m_nCurrentIndex > m_nIndexCount )
    {
        m_nIndexCount = m_nCurrentIndex;
    }
}

//-----------------------------------------------------------------------------
// Returns the current index
//-----------------------------------------------------------------------------
inline int CIndexBuilder::GetCurrentIndex()
{
    return m_nCurrentIndex;
}

inline unsigned short const* CIndexBuilder::Index() const
{
    Assert( m_nCurrentIndex < m_nMaxIndexCount );
    return &m_pIndices[ m_nCurrentIndex ];
}

inline void CIndexBuilder::SelectIndex( int nIndex )
{
    Assert( ( nIndex >= 0 ) && ( nIndex < m_nIndexCount ) );
    m_nCurrentIndex = nIndex * m_nIndexSize;
}

//-----------------------------------------------------------------------------
// Used to write data into the index buffer
//-----------------------------------------------------------------------------
inline void CIndexBuilder::Index( unsigned short nIndex )
{
    Assert( m_pIndices );
    Assert( m_nCurrentIndex < m_nMaxIndexCount );
    m_pIndices[ m_nCurrentIndex ] = ( unsigned short ) ( m_nIndexOffset + nIndex );
}

// Fast Index! No need to call advance index
inline void CIndexBuilder::FastIndex( unsigned short nIndex )
{
    Assert( m_pIndices );
    Assert( m_nCurrentIndex < m_nMaxIndexCount );
    m_pIndices[ m_nCurrentIndex ] = ( unsigned short ) ( m_nIndexOffset + nIndex );
    m_nCurrentIndex += m_nIndexSize;
    m_nIndexCount = m_nCurrentIndex;
}

FORCEINLINE void CIndexBuilder::FastTriangle( unsigned short startVert )
{
    startVert += m_nIndexOffset;
    unsigned short *pIndices = &m_pIndices[ m_nCurrentIndex ];
    *pIndices++ = startVert++;
    *pIndices++ = startVert++;
    *pIndices++ = startVert;
    AdvanceIndices( 3 );
}

FORCEINLINE void CIndexBuilder::FastQuad( unsigned short startVert )
{
    startVert += m_nIndexOffset;
    unsigned short *pIndices = &m_pIndices[ m_nCurrentIndex ];
    *pIndices++ = startVert++;
    *pIndices++ = startVert++;
    *pIndices++ = startVert;

    *pIndices++ = startVert - 2;
    *pIndices++ = startVert++;
    *pIndices++ = startVert;
    AdvanceIndices( 6 );
}

inline void CIndexBuilder::FastPolygon( unsigned short startVert , unsigned short triangleCount )
{
    unsigned short *pIndex = &m_pIndices[ m_nCurrentIndex ];
    startVert += m_nIndexOffset;
    // NOTE: IndexSize is 1 or 0 (0 for alt-tab)
    // This prevents us from writing into bogus memory
    Assert( m_nIndexSize == 0 || m_nIndexSize == 1 );
    triangleCount *= m_nIndexSize;
    for ( short v = 0; v < triangleCount; ++v )
    {
        *pIndex++ = startVert;
        *pIndex++ = startVert + v + 1;
        *pIndex++ = startVert + v + 2;
    }
    AdvanceIndices( triangleCount * 3 );
}

inline void CIndexBuilder::FastPolygonList( unsigned short startVert , short *pVertexCount , short polygonCount )
{
    unsigned short *pIndex = &m_pIndices[ m_nCurrentIndex ];
    startVert += m_nIndexOffset;
    int indexOut = 0;
    // NOTE: IndexSize is 1 or 0 (0 for alt-tab)
    // This prevents us from writing into bogus memory
    Assert( m_nIndexSize == 0 || m_nIndexSize == 1 );
    polygonCount *= m_nIndexSize;

    for ( int i = 0; i < polygonCount; i++ )
    {
        short vertexCount = pVertexCount[ i ];
        short triangleCount = vertexCount - 2;
        for ( short v = 0; v < triangleCount; ++v )
        {
            *pIndex++ = startVert;
            *pIndex++ = startVert + v + 1;
            *pIndex++ = startVert + v + 2;
        }
        startVert += vertexCount;
        indexOut += triangleCount * 3;
    }
    AdvanceIndices( indexOut );
}

inline void CIndexBuilder::FastIndexList( const unsigned short *pIndexList , short startVert , int indexCount )
{
    unsigned short *pIndexOut = &m_pIndices[ m_nCurrentIndex ];
    startVert += m_nIndexOffset;
    Assert( m_nIndexSize == 0 || m_nIndexSize == 1 );
    indexCount *= m_nIndexSize;
    for ( int i = 0; i < indexCount; ++i )
    {
        pIndexOut[ i ] = startVert + pIndexList[ i ];
    }
    AdvanceIndices( indexCount );
}

//-----------------------------------------------------------------------------
// NOTE: This version is the one you really want to achieve write-combining;
// Write combining only works if you write in 4 bytes chunks.
//-----------------------------------------------------------------------------
inline void CIndexBuilder::FastIndex2( unsigned short nIndex1 , unsigned short nIndex2 )
{
    Assert( m_pIndices );
    Assert( m_nCurrentIndex < m_nMaxIndexCount - 1 );
    //	Assert( ( (int)( &m_pIndices[m_nCurrentIndex] ) & 0x3 ) == 0 );

#ifndef _X360
    unsigned int nIndices = ( ( unsigned int ) nIndex1 + m_nIndexOffset ) | ( ( ( unsigned int ) nIndex2 + m_nIndexOffset ) << 16 );
#else
    unsigned int nIndices = ( ( unsigned int ) nIndex2 + m_nIndexOffset ) | ( ( ( unsigned int ) nIndex1 + m_nIndexOffset ) << 16 );
#endif

    *( int* ) ( &m_pIndices[ m_nCurrentIndex ] ) = nIndices;
    m_nCurrentIndex += m_nIndexSize + m_nIndexSize;
    m_nIndexCount = m_nCurrentIndex;
}

//-----------------------------------------------------------------------------
// Generates indices for a particular primitive type
//-----------------------------------------------------------------------------
inline void CIndexBuilder::GenerateIndices( MaterialPrimitiveType_t primitiveType , int nIndexCount )
{
    // FIXME: How to make this work with short vs int sized indices?
    // Don't generate indices if we've got an empty buffer
    if ( m_nIndexSize == 0 )
        return;

    int nMaxIndices = m_nMaxIndexCount - m_nCurrentIndex;
    nIndexCount = min( nMaxIndices , nIndexCount );
    if ( nIndexCount == 0 )
        return;

    unsigned short *pIndices = &m_pIndices[ m_nCurrentIndex ];

    switch ( primitiveType )
    {
        case MATERIAL_INSTANCED_QUADS:
            Assert( 0 ); // Shouldn't get here (this primtype is unindexed)
            break;
        case MATERIAL_QUADS:
            GenerateQuadIndexBuffer( pIndices , nIndexCount , m_nIndexOffset );
            break;
        case MATERIAL_POLYGON:
            GeneratePolygonIndexBuffer( pIndices , nIndexCount , m_nIndexOffset );
            break;
        case MATERIAL_LINE_STRIP:
            GenerateLineStripIndexBuffer( pIndices , nIndexCount , m_nIndexOffset );
            break;
        case MATERIAL_LINE_LOOP:
            GenerateLineLoopIndexBuffer( pIndices , nIndexCount , m_nIndexOffset );
            break;
        case MATERIAL_POINTS:
            Assert( 0 ); // Shouldn't get here (this primtype is unindexed)
            break;
        case MATERIAL_SUBD_QUADS_EXTRA:
        case MATERIAL_SUBD_QUADS_REG:
        default:
            GenerateSequentialIndexBuffer( pIndices , nIndexCount , m_nIndexOffset );
            break;
    }

    AdvanceIndices( nIndexCount );
}

//-----------------------------------------------------------------------------
//
// Helper class used to define meshes
//
//-----------------------------------------------------------------------------
//class CMeshBuilder : private MeshDesc_t
// hack fixme
class CMeshBuilder : public MeshDesc_t
{
public:
    CMeshBuilder();
    ~CMeshBuilder()
    {
        Assert( !m_pMesh );
    }		// if this fires you did a Begin() without an End()

    operator CIndexBuilder&( )
    {
        return m_IndexBuilder;
    }

    // This must be called before Begin, if a vertex buffer with a compressed format is to be used
    void SetCompressionType( VertexCompressionType_t compressionType );

    // Locks the vertex buffer
    // (*cannot* use the Index() call below)
    void Begin( IMesh *pMesh , MaterialPrimitiveType_t type , int numPrimitives );

    // Locks the vertex buffer, can specify arbitrary index lists
    // (must use the Index() call below)
    void Begin( IMesh *pMesh , MaterialPrimitiveType_t type , int nVertexCount , int nIndexCount , int *nFirstVertex );
    void Begin( IMesh *pMesh , MaterialPrimitiveType_t type , int nVertexCount , int nIndexCount );

    // Use this when you're done writing
    // Set bDraw to true to call m_pMesh->Draw automatically.
    void End( bool bSpewData = false , bool bDraw = false );

    // Locks the vertex buffer to modify existing data
    // Passing nVertexCount == -1 says to lock all the vertices for modification.
    // Pass 0 for nIndexCount to not lock the index buffer.
    void BeginModify( IMesh *pMesh , int nFirstVertex = 0 , int nVertexCount = -1 , int nFirstIndex = 0 , int nIndexCount = 0 );
    void EndModify( bool bSpewData = false );

    // A helper method since this seems to be done a whole bunch.
    void DrawQuad( IMesh* pMesh , const float *v1 , const float *v2 ,
                   const float *v3 , const float *v4 , unsigned char const *pColor , bool wireframe = false );

    // returns the number of indices and vertices
    int VertexCount() const;
    int	IndexCount() const;

    // Resets the mesh builder so it points to the start of everything again
    void Reset();

    // Returns the size of the vertex
    int VertexSize()
    {
        return m_ActualVertexSize;
    }

    // returns the data size of a given texture coordinate
    int TextureCoordinateSize( int nTexCoordNumber )
    {
        return m_VertexSize_TexCoord[ nTexCoordNumber ];
    }

    // Returns the base vertex memory pointer
    void* BaseVertexData();

    // Selects the nth Vertex and Index
    void SelectVertex( int idx );
    void SelectIndex( int idx );

    // Given an index, point to the associated vertex
    void SelectVertexFromIndex( int idx );

    // Advances the current vertex and index by one
    void AdvanceVertex();
    template<int nFlags , int nNumTexCoords> void AdvanceVertexF();
    void AdvanceVertices( int nVerts );
    void AdvanceIndex();
    void AdvanceIndices( int nIndices );

    int GetCurrentVertex();
    int GetCurrentIndex();

    // Data retrieval...
    const float *Position() const;

    const float *Normal() const;

    unsigned int Color() const;

    unsigned char *Specular() const;

    const float *TexCoord( int stage ) const;

    const float *TangentS() const;
    const float *TangentT() const;

    const float *BoneWeight() const;
    float Wrinkle() const;

    int NumBoneWeights() const;
#ifndef NEW_SKINNING
    unsigned char *BoneMatrix() const;
#else
    float *BoneMatrix() const;
#endif
    unsigned short const *Index() const;

    // position setting
    void Position3f( float x , float y , float z );
    void Position3fv( const float *v );

    // normal setting
    void Normal3f( float nx , float ny , float nz );
    void Normal3fv( const float *n );
    void NormalDelta3fv( const float *n );
    void NormalDelta3f( float nx , float ny , float nz );

    // normal setting (templatized for code which needs to support compressed vertices)
    template <VertexCompressionType_t T> void CompressedNormal3f( float nx , float ny , float nz );
    template <VertexCompressionType_t T> void CompressedNormal3fv( const float *n );

    // color setting
    void Color3f( float r , float g , float b );
    void Color3fv( const float *rgb );
    void Color4f( float r , float g , float b , float a );
    void Color4fv( const float *rgba );

    // Faster versions of color
    void Color3ub( unsigned char r , unsigned char g , unsigned char b );
    void Color3ubv( unsigned char const* rgb );
    void Color4ub( unsigned char r , unsigned char g , unsigned char b , unsigned char a );
    void Color4ubv( unsigned char const* rgba );
    void Color4Packed( int packedColor );
    int PackColor4( unsigned char r , unsigned char g , unsigned char b , unsigned char a );

    // specular color setting
    void Specular3f( float r , float g , float b );
    void Specular3fv( const float *rgb );
    void Specular4f( float r , float g , float b , float a );
    void Specular4fv( const float *rgba );

    // Faster version of specular
    void Specular3ub( unsigned char r , unsigned char g , unsigned char b );
    void Specular3ubv( unsigned char const *c );
    void Specular4ub( unsigned char r , unsigned char g , unsigned char b , unsigned char a );
    void Specular4ubv( unsigned char const *c );

    // texture coordinate setting
    void TexCoord1f( int stage , float s );
    void TexCoord2f( int stage , float s , float t );
    void TexCoord2fv( int stage , const float *st );
    void TexCoord3f( int stage , float s , float t , float u );
    void TexCoord3fv( int stage , const float *stu );
    void TexCoord4f( int stage , float s , float t , float u , float w );
    void TexCoord4fv( int stage , const float *stuv );

    void TexCoordSubRect2f( int stage , float s , float t , float offsetS , float offsetT , float scaleS , float scaleT );
    void TexCoordSubRect2fv( int stage , const float *st , const float *offset , const float *scale );

    // tangent space
    void TangentS3f( float sx , float sy , float sz );
    void TangentS3fv( const float *s );

    void TangentT3f( float tx , float ty , float tz );
    void TangentT3fv( const float *t );

    // Wrinkle
    void Wrinkle1f( float flWrinkle );

    // bone weights
    void BoneWeight( int idx , float weight );
    void BoneWeights2( float weight1 , float weight2 );

    // bone weights (templatized for code which needs to support compressed vertices)
    template <VertexCompressionType_t T> void CompressedBoneWeight3fv( const float * pWeights );

    // bone matrix index
    void BoneMatrix( int idx , int matrixIndex );
    void BoneMatrices4( int matrixIdx0 , int matrixIdx1 , int matrixIdx2 , int matrixIdx3 );

    // Generic per-vertex data
    void UserData( const float *pData );
    // Generic per-vertex data (templatized for code which needs to support compressed vertices)
    template <VertexCompressionType_t T> void CompressedUserData( const float* pData );

    // Used to define the indices (only used if you aren't using primitives)
    void Index( unsigned short index );

    // NOTE: Use this one to get write combining! Much faster than the other version of FastIndex
    // Fast Index! No need to call advance index, and no random access allowed
    void FastIndex2( unsigned short nIndex1 , unsigned short nIndex2 );

    // Fast Index! No need to call advance index, and no random access allowed
    void FastIndex( unsigned short index );
    void FastQuad( unsigned short index );

    // Fast Vertex! No need to call advance vertex, and no random access allowed.
    // WARNING - these are low level functions that are intended only for use
    // in the software vertex skinner.
    void FastVertex( const ModelVertexDX8_t &vertex );
    void FastVertexSSE( const ModelVertexDX8_t &vertex );
    void FastQuadVertexSSE( const QuadTessVertex_t &vertex );

    // Add number of verts and current vert since FastVertexxx routines do not update.
    void FastAdvanceNVertices( int n );

#if defined( _X360 )
    void VertexDX8ToX360( const ModelVertexDX8_t &vertex );
#endif

    // this low level function gets you a pointer to the vertex output data. It is dangerous - any
    // caller using it must understand the vertex layout that it is building. It is for optimized
    // meshbuilding loops like particle drawing that use special shaders. After writing to the output
    // data, you shuodl call FastAdvanceNVertices
    FORCEINLINE void *GetVertexDataPtr( int nWhatSizeIThinkItIs )
    {
        if ( m_VertexBuilder.m_VertexSize_Position != nWhatSizeIThinkItIs )
            return NULL;
        return m_VertexBuilder.m_pCurrPosition;
    }

private:
    // Computes number of verts and indices
    void ComputeNumVertsAndIndices( int *pMaxVertices , int *pMaxIndices ,
                                    MaterialPrimitiveType_t type , int nPrimitiveCount );
    int IndicesFromVertices( MaterialPrimitiveType_t type , int nVertexCount );

    // The mesh we're modifying
    IMesh *m_pMesh;

    MaterialPrimitiveType_t m_Type;

    // Generate indices?
    bool m_bGenerateIndices;

    CIndexBuilder	m_IndexBuilder;
    CVertexBuilder	m_VertexBuilder;
};

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
inline CMeshBuilder::CMeshBuilder() : m_pMesh( 0 ) , m_bGenerateIndices( false )
{}

//-----------------------------------------------------------------------------
// Computes the number of verts and indices based on primitive type and count
//-----------------------------------------------------------------------------
inline void CMeshBuilder::ComputeNumVertsAndIndices( int *pMaxVertices , int *pMaxIndices ,
                                                     MaterialPrimitiveType_t type , int nPrimitiveCount )
{
    switch ( type )
    {
        case MATERIAL_POINTS:
            *pMaxVertices = *pMaxIndices = nPrimitiveCount;
            break;

        case MATERIAL_LINES:
            *pMaxVertices = *pMaxIndices = nPrimitiveCount * 2;
            break;

        case MATERIAL_LINE_STRIP:
            *pMaxVertices = nPrimitiveCount + 1;
            *pMaxIndices = nPrimitiveCount * 2;
            break;

        case MATERIAL_LINE_LOOP:
            *pMaxVertices = nPrimitiveCount;
            *pMaxIndices = nPrimitiveCount * 2;
            break;

        case MATERIAL_TRIANGLES:
            *pMaxVertices = *pMaxIndices = nPrimitiveCount * 3;
            break;

        case MATERIAL_TRIANGLE_STRIP:
            *pMaxVertices = *pMaxIndices = nPrimitiveCount + 2;
            break;

        case MATERIAL_QUADS:
            *pMaxVertices = nPrimitiveCount * 4;
            *pMaxIndices = nPrimitiveCount * 6;
            break;

        case MATERIAL_INSTANCED_QUADS:
            *pMaxVertices = nPrimitiveCount;
            *pMaxIndices = 0; // This primtype is unindexed
            break;

        case MATERIAL_POLYGON:
            *pMaxVertices = nPrimitiveCount;
            *pMaxIndices = ( nPrimitiveCount - 2 ) * 3;
            break;

        default:
            Assert( 0 );
    }

    // FIXME: need to get this from meshdx8.cpp, or move it to somewhere common
    Assert( *pMaxVertices <= 32768 );
    Assert( *pMaxIndices <= 32768 );
}

inline int CMeshBuilder::IndicesFromVertices( MaterialPrimitiveType_t type , int nVertexCount )
{
    switch ( type )
    {
        case MATERIAL_QUADS:
            Assert( ( nVertexCount & 0x3 ) == 0 );
            return ( nVertexCount * 6 ) / 4;

        case MATERIAL_INSTANCED_QUADS:
            // This primtype is unindexed
            return 0;

        case MATERIAL_POLYGON:
            Assert( nVertexCount >= 3 );
            return ( nVertexCount - 2 ) * 3;

        case MATERIAL_LINE_STRIP:
            Assert( nVertexCount >= 2 );
            return ( nVertexCount - 1 ) * 2;

        case MATERIAL_LINE_LOOP:
            Assert( nVertexCount >= 3 );
            return nVertexCount * 2;

        default:
            return nVertexCount;
    }
}

//-----------------------------------------------------------------------------
// Specify the type of vertex compression that this CMeshBuilder will perform
//-----------------------------------------------------------------------------
inline void CMeshBuilder::SetCompressionType( VertexCompressionType_t vertexCompressionType )
{
    m_CompressionType = vertexCompressionType;
    m_VertexBuilder.SetCompressionType( vertexCompressionType );
}

//-----------------------------------------------------------------------------
// Begins modifying the mesh
//-----------------------------------------------------------------------------
inline void CMeshBuilder::Begin( IMesh *pMesh , MaterialPrimitiveType_t type , int numPrimitives )
{
    Assert( pMesh && ( !m_pMesh ) );
    Assert( type != MATERIAL_HETEROGENOUS );

    m_pMesh = pMesh;
    m_bGenerateIndices = true;
    m_Type = type;

    int nMaxVertexCount , nMaxIndexCount;
    ComputeNumVertsAndIndices( &nMaxVertexCount , &nMaxIndexCount , type , numPrimitives );

    switch ( type )
    {
        case MATERIAL_INSTANCED_QUADS:
            m_pMesh->SetPrimitiveType( MATERIAL_INSTANCED_QUADS );
            break;

        case MATERIAL_QUADS:
        case MATERIAL_POLYGON:
            m_pMesh->SetPrimitiveType( MATERIAL_TRIANGLES );
            break;

        case MATERIAL_LINE_STRIP:
        case MATERIAL_LINE_LOOP:
            m_pMesh->SetPrimitiveType( MATERIAL_LINES );
            break;

        default:
            m_pMesh->SetPrimitiveType( type );
    }

    // Lock the mesh
    m_pMesh->LockMesh( nMaxVertexCount , nMaxIndexCount , *this , NULL );

    m_IndexBuilder.AttachBegin( pMesh , nMaxIndexCount , *this );
    m_VertexBuilder.AttachBegin( pMesh , nMaxVertexCount , *this );

    // Point to the start of the index and vertex buffers
    Reset();
}

inline void CMeshBuilder::Begin( IMesh *pMesh , MaterialPrimitiveType_t type , int nVertexCount , int nIndexCount , int *nFirstVertex )
{
    Begin( pMesh , type , nVertexCount , nIndexCount );

    *nFirstVertex = m_VertexBuilder.m_nFirstVertex * m_VertexBuilder.VertexSize();
}

inline void CMeshBuilder::Begin( IMesh* pMesh , MaterialPrimitiveType_t type , int nVertexCount , int nIndexCount )
{
    Assert( pMesh && ( !m_pMesh ) );

    // NOTE: We can't specify the indices when we use quads, polygons, or
    // linestrips; they aren't actually directly supported by
    // the material system
    Assert( ( type != MATERIAL_QUADS ) && ( type != MATERIAL_INSTANCED_QUADS ) && ( type != MATERIAL_POLYGON ) &&
        ( type != MATERIAL_LINE_STRIP ) && ( type != MATERIAL_LINE_LOOP ) );

    // Dx8 doesn't support indexed points...
    Assert( type != MATERIAL_POINTS );

    m_pMesh = pMesh;
    m_bGenerateIndices = false;
    m_Type = type;

    // Set the primitive type
    m_pMesh->SetPrimitiveType( type );

    // Lock the vertex and index buffer
    m_pMesh->LockMesh( nVertexCount , nIndexCount , *this , NULL );

    m_IndexBuilder.AttachBegin( pMesh , nIndexCount , *this );
    m_VertexBuilder.AttachBegin( pMesh , nVertexCount , *this );

    // Point to the start of the buffers..
    Reset();
}

//-----------------------------------------------------------------------------
// Use this when you're done modifying the mesh
//-----------------------------------------------------------------------------
inline void CMeshBuilder::End( bool bSpewData , bool bDraw )
{
    if ( m_bGenerateIndices )
    {
        int nIndexCount = IndicesFromVertices( m_Type , m_VertexBuilder.VertexCount() );
        m_IndexBuilder.GenerateIndices( m_Type , nIndexCount );
    }

    if ( bSpewData )
    {
        m_pMesh->Spew( m_VertexBuilder.VertexCount() , m_IndexBuilder.IndexCount() , *this );
    }

    // Unlock our buffers
    m_pMesh->UnlockMesh( m_VertexBuilder.VertexCount() , m_IndexBuilder.IndexCount() , *this );

    m_IndexBuilder.AttachEnd();
    m_VertexBuilder.AttachEnd();

    if ( bDraw )
    {
        m_pMesh->Draw();
    }

    m_pMesh = 0;
}

//-----------------------------------------------------------------------------
// Locks the vertex buffer to modify existing data
//-----------------------------------------------------------------------------
inline void CMeshBuilder::BeginModify( IMesh* pMesh , int nFirstVertex , int nVertexCount , int nFirstIndex , int nIndexCount )
{
    Assert( pMesh && ( !m_pMesh ) );

    if ( nVertexCount < 0 )
    {
        nVertexCount = pMesh->VertexCount();
    }

    m_pMesh = pMesh;
    m_bGenerateIndices = false;

    // Locks mesh for modifying
    pMesh->ModifyBeginEx( false , nFirstVertex , nVertexCount , nFirstIndex , nIndexCount , *this );

    m_IndexBuilder.AttachBeginModify( pMesh , nIndexCount , *this );
    m_VertexBuilder.AttachBeginModify( pMesh , nVertexCount , *this );

    // Point to the start of the buffers..
    Reset();
}

inline void CMeshBuilder::EndModify( bool bSpewData )
{
    Assert( m_pMesh );

    if ( bSpewData )
    {
        m_pMesh->Spew( m_VertexBuilder.VertexCount() , m_IndexBuilder.IndexCount() , *this );
    }

    // Unlocks mesh
    m_pMesh->ModifyEnd( *this );
    m_pMesh = 0;

    m_IndexBuilder.AttachEndModify();
    m_VertexBuilder.AttachEndModify();
}

//-----------------------------------------------------------------------------
// Resets the mesh builder so it points to the start of everything again
//-----------------------------------------------------------------------------
inline void CMeshBuilder::Reset()
{
    m_IndexBuilder.Reset();
    m_VertexBuilder.Reset();
}

//-----------------------------------------------------------------------------
// Selects the current Vertex and Index
//-----------------------------------------------------------------------------
FORCEINLINE void CMeshBuilder::SelectVertex( int nIndex )
{
    m_VertexBuilder.SelectVertex( nIndex );
}

inline void CMeshBuilder::SelectVertexFromIndex( int idx )
{
    // NOTE: This index is expected to be relative
    int vertIdx = idx - m_nFirstVertex;
    SelectVertex( vertIdx );
}

FORCEINLINE void CMeshBuilder::SelectIndex( int idx )
{
    m_IndexBuilder.SelectIndex( idx );
}

//-----------------------------------------------------------------------------
// Advances the current vertex and index by one
//-----------------------------------------------------------------------------
template<int nFlags , int nNumTexCoords> FORCEINLINE void CMeshBuilder::AdvanceVertexF()
{
    m_VertexBuilder.AdvanceVertexF<nFlags , nNumTexCoords>();
}
FORCEINLINE void CMeshBuilder::AdvanceVertex()
{
    m_VertexBuilder.AdvanceVertex();
}

FORCEINLINE void CMeshBuilder::AdvanceVertices( int nVertexCount )
{
    m_VertexBuilder.AdvanceVertices( nVertexCount );
}

FORCEINLINE void CMeshBuilder::AdvanceIndex()
{
    m_IndexBuilder.AdvanceIndex();
}

FORCEINLINE void CMeshBuilder::AdvanceIndices( int nIndices )
{
    m_IndexBuilder.AdvanceIndices( nIndices );
}

FORCEINLINE int CMeshBuilder::GetCurrentVertex()
{
    return m_VertexBuilder.GetCurrentVertex();
}

FORCEINLINE int CMeshBuilder::GetCurrentIndex()
{
    return m_IndexBuilder.GetCurrentIndex();
}

//-----------------------------------------------------------------------------
// A helper method since this seems to be done a whole bunch.
//-----------------------------------------------------------------------------
inline void CMeshBuilder::DrawQuad( IMesh* pMesh , const float* v1 , const float* v2 ,
                                    const float* v3 , const float* v4 , unsigned char const* pColor , bool wireframe )
{
    if ( !wireframe )
    {
        Begin( pMesh , MATERIAL_TRIANGLE_STRIP , 2 );

        Position3fv( v1 );
        Color4ubv( pColor );
        AdvanceVertexF<VTX_HAVEPOS | VTX_HAVECOLOR , 0>();

        Position3fv( v2 );
        Color4ubv( pColor );
        AdvanceVertexF<VTX_HAVEPOS | VTX_HAVECOLOR , 0>();

        Position3fv( v4 );
        Color4ubv( pColor );
        AdvanceVertexF<VTX_HAVEPOS | VTX_HAVECOLOR , 0>();

        Position3fv( v3 );
        Color4ubv( pColor );
        AdvanceVertexF<VTX_HAVEPOS | VTX_HAVECOLOR , 0>();
    }
    else
    {
        Begin( pMesh , MATERIAL_LINE_LOOP , 4 );
        Position3fv( v1 );
        Color4ubv( pColor );
        AdvanceVertexF<VTX_HAVEPOS | VTX_HAVECOLOR , 0>();

        Position3fv( v2 );
        Color4ubv( pColor );
        AdvanceVertexF<VTX_HAVEPOS | VTX_HAVECOLOR , 0>();

        Position3fv( v3 );
        Color4ubv( pColor );
        AdvanceVertexF<VTX_HAVEPOS | VTX_HAVECOLOR , 0>();

        Position3fv( v4 );
        Color4ubv( pColor );
        AdvanceVertexF<VTX_HAVEPOS | VTX_HAVECOLOR , 0>();
    }

    End();
    pMesh->Draw();
}

//-----------------------------------------------------------------------------
// returns the number of indices and vertices
//-----------------------------------------------------------------------------
FORCEINLINE int CMeshBuilder::VertexCount() const
{
    return m_VertexBuilder.VertexCount();
}

FORCEINLINE int CMeshBuilder::IndexCount() const
{
    return m_IndexBuilder.IndexCount();
}

//-----------------------------------------------------------------------------
// Returns the base vertex memory pointer
//-----------------------------------------------------------------------------
FORCEINLINE void* CMeshBuilder::BaseVertexData()
{
    return m_VertexBuilder.BaseVertexData();
}

//-----------------------------------------------------------------------------
// Data retrieval...
//-----------------------------------------------------------------------------
FORCEINLINE const float* CMeshBuilder::Position() const
{
    return m_VertexBuilder.Position();
}

FORCEINLINE const float* CMeshBuilder::Normal()	const
{
    return m_VertexBuilder.Normal();
}

FORCEINLINE unsigned int CMeshBuilder::Color() const
{
    return m_VertexBuilder.Color();
}

FORCEINLINE unsigned char *CMeshBuilder::Specular() const
{
    return m_VertexBuilder.Specular();
}

FORCEINLINE const float* CMeshBuilder::TexCoord( int nStage ) const
{
    return m_VertexBuilder.TexCoord( nStage );
}

FORCEINLINE const float* CMeshBuilder::TangentS() const
{
    return m_VertexBuilder.TangentS();
}

FORCEINLINE const float* CMeshBuilder::TangentT() const
{
    return m_VertexBuilder.TangentT();
}

FORCEINLINE float CMeshBuilder::Wrinkle() const
{
    return m_VertexBuilder.Wrinkle();
}

FORCEINLINE const float* CMeshBuilder::BoneWeight() const
{
    return m_VertexBuilder.BoneWeight();
}

FORCEINLINE int CMeshBuilder::NumBoneWeights() const
{
    return m_VertexBuilder.NumBoneWeights();
}

FORCEINLINE unsigned short const* CMeshBuilder::Index() const
{
    return m_IndexBuilder.Index();
}

//-----------------------------------------------------------------------------
// Index
//-----------------------------------------------------------------------------
FORCEINLINE void CMeshBuilder::Index( unsigned short idx )
{
    m_IndexBuilder.Index( idx );
}

//-----------------------------------------------------------------------------
// Fast Index! No need to call advance index
//-----------------------------------------------------------------------------
FORCEINLINE void CMeshBuilder::FastIndex( unsigned short idx )
{
    m_IndexBuilder.FastIndex( idx );
}

// NOTE: Use this one to get write combining! Much faster than the other version of FastIndex
// Fast Index! No need to call advance index, and no random access allowed
FORCEINLINE void CMeshBuilder::FastIndex2( unsigned short nIndex1 , unsigned short nIndex2 )
{
    m_IndexBuilder.FastIndex2( nIndex1 , nIndex2 );
}

FORCEINLINE void CMeshBuilder::FastQuad( unsigned short nIndex )
{
    m_IndexBuilder.FastQuad( nIndex );
}

//-----------------------------------------------------------------------------
// For use with the FastVertex methods, advances the current vertex by N
//-----------------------------------------------------------------------------
FORCEINLINE void CMeshBuilder::FastAdvanceNVertices( int nVertexCount )
{
    m_VertexBuilder.FastAdvanceNVertices( nVertexCount );
}

//-----------------------------------------------------------------------------
// Fast Vertex! No need to call advance vertex, and no random access allowed
//-----------------------------------------------------------------------------
FORCEINLINE void CMeshBuilder::FastVertex( const ModelVertexDX8_t &vertex )
{
    m_VertexBuilder.FastVertex( vertex );
}

FORCEINLINE void CMeshBuilder::FastVertexSSE( const ModelVertexDX8_t &vertex )
{
    m_VertexBuilder.FastVertexSSE( vertex );
}

FORCEINLINE void CMeshBuilder::FastQuadVertexSSE( const QuadTessVertex_t &vertex )
{
    m_VertexBuilder.FastQuadVertexSSE( vertex );
}

//-----------------------------------------------------------------------------
// Copies a vertex into the x360 format
//-----------------------------------------------------------------------------
#if defined( _X360 )
inline void CMeshBuilder::VertexDX8ToX360( const ModelVertexDX8_t &vertex )
{
    m_VertexBuilder.VertexDX8ToX360( vertex );
}
#endif

//-----------------------------------------------------------------------------
// Vertex field setting methods
//-----------------------------------------------------------------------------
FORCEINLINE void CMeshBuilder::Position3f( float x , float y , float z )
{
    m_VertexBuilder.Position3f( x , y , z );
}

FORCEINLINE void CMeshBuilder::Position3fv( const float *v )
{
    m_VertexBuilder.Position3fv( v );
}

FORCEINLINE void CMeshBuilder::Normal3f( float nx , float ny , float nz )
{
    m_VertexBuilder.Normal3f( nx , ny , nz );
}

FORCEINLINE void CMeshBuilder::Normal3fv( const float *n )
{
    m_VertexBuilder.Normal3fv( n );
}

FORCEINLINE void CMeshBuilder::NormalDelta3f( float nx , float ny , float nz )
{
    m_VertexBuilder.NormalDelta3f( nx , ny , nz );
}

FORCEINLINE void CMeshBuilder::NormalDelta3fv( const float *n )
{
    m_VertexBuilder.NormalDelta3fv( n );
}

FORCEINLINE void CMeshBuilder::Color3f( float r , float g , float b )
{
    m_VertexBuilder.Color3f( r , g , b );
}

FORCEINLINE void CMeshBuilder::Color3fv( const float *rgb )
{
    m_VertexBuilder.Color3fv( rgb );
}

FORCEINLINE void CMeshBuilder::Color4f( float r , float g , float b , float a )
{
    m_VertexBuilder.Color4f( r , g , b , a );
}

FORCEINLINE void CMeshBuilder::Color4fv( const float *rgba )
{
    m_VertexBuilder.Color4fv( rgba );
}

FORCEINLINE void CMeshBuilder::Color3ub( unsigned char r , unsigned char g , unsigned char b )
{
    m_VertexBuilder.Color3ub( r , g , b );
}

FORCEINLINE void CMeshBuilder::Color3ubv( unsigned char const* rgb )
{
    m_VertexBuilder.Color3ubv( rgb );
}

FORCEINLINE void CMeshBuilder::Color4ub( unsigned char r , unsigned char g , unsigned char b , unsigned char a )
{
    m_VertexBuilder.Color4ub( r , g , b , a );
}

FORCEINLINE void CMeshBuilder::Color4ubv( unsigned char const* rgba )
{
    m_VertexBuilder.Color4ubv( rgba );
}

FORCEINLINE void CMeshBuilder::Color4Packed( int packedColor )
{
    m_VertexBuilder.Color4Packed( packedColor );
}

FORCEINLINE int CMeshBuilder::PackColor4( unsigned char r , unsigned char g , unsigned char b , unsigned char a )
{
    return m_VertexBuilder.PackColor4( r , g , b , a );
}

FORCEINLINE void CMeshBuilder::Specular3f( float r , float g , float b )
{
    m_VertexBuilder.Specular3f( r , g , b );
}

FORCEINLINE void CMeshBuilder::Specular3fv( const float *rgb )
{
    m_VertexBuilder.Specular3fv( rgb );
}

FORCEINLINE void CMeshBuilder::Specular4f( float r , float g , float b , float a )
{
    m_VertexBuilder.Specular4f( r , g , b , a );
}

FORCEINLINE void CMeshBuilder::Specular4fv( const float *rgba )
{
    m_VertexBuilder.Specular4fv( rgba );
}

FORCEINLINE void CMeshBuilder::Specular3ub( unsigned char r , unsigned char g , unsigned char b )
{
    m_VertexBuilder.Specular3ub( r , g , b );
}

FORCEINLINE void CMeshBuilder::Specular3ubv( unsigned char const *c )
{
    m_VertexBuilder.Specular3ubv( c );
}

FORCEINLINE void CMeshBuilder::Specular4ub( unsigned char r , unsigned char g , unsigned char b , unsigned char a )
{
    m_VertexBuilder.Specular4ub( r , g , b , a );
}

FORCEINLINE void CMeshBuilder::Specular4ubv( unsigned char const *c )
{
    m_VertexBuilder.Specular4ubv( c );
}

FORCEINLINE void CMeshBuilder::TexCoord1f( int nStage , float s )
{
    m_VertexBuilder.TexCoord1f( nStage , s );
}

FORCEINLINE void CMeshBuilder::TexCoord2f( int nStage , float s , float t )
{
    m_VertexBuilder.TexCoord2f( nStage , s , t );
}

FORCEINLINE void CMeshBuilder::TexCoord2fv( int nStage , const float *st )
{
    m_VertexBuilder.TexCoord2fv( nStage , st );
}

FORCEINLINE void CMeshBuilder::TexCoord3f( int nStage , float s , float t , float u )
{
    m_VertexBuilder.TexCoord3f( nStage , s , t , u );
}

FORCEINLINE void CMeshBuilder::TexCoord3fv( int nStage , const float *stu )
{
    m_VertexBuilder.TexCoord3fv( nStage , stu );
}

FORCEINLINE void CMeshBuilder::TexCoord4f( int nStage , float s , float t , float u , float v )
{
    m_VertexBuilder.TexCoord4f( nStage , s , t , u , v );
}

FORCEINLINE void CMeshBuilder::TexCoord4fv( int nStage , const float *stuv )
{
    m_VertexBuilder.TexCoord4fv( nStage , stuv );
}

FORCEINLINE void CMeshBuilder::TexCoordSubRect2f( int nStage , float s , float t , float offsetS , float offsetT , float scaleS , float scaleT )
{
    m_VertexBuilder.TexCoordSubRect2f( nStage , s , t , offsetS , offsetT , scaleS , scaleT );
}

FORCEINLINE void CMeshBuilder::TexCoordSubRect2fv( int nStage , const float *st , const float *offset , const float *scale )
{
    m_VertexBuilder.TexCoordSubRect2fv( nStage , st , offset , scale );
}

FORCEINLINE void CMeshBuilder::TangentS3f( float sx , float sy , float sz )
{
    m_VertexBuilder.TangentS3f( sx , sy , sz );
}

FORCEINLINE void CMeshBuilder::TangentS3fv( const float* s )
{
    m_VertexBuilder.TangentS3fv( s );
}

FORCEINLINE void CMeshBuilder::TangentT3f( float tx , float ty , float tz )
{
    m_VertexBuilder.TangentT3f( tx , ty , tz );
}

FORCEINLINE void CMeshBuilder::TangentT3fv( const float* t )
{
    m_VertexBuilder.TangentT3fv( t );
}

FORCEINLINE void CMeshBuilder::Wrinkle1f( float flWrinkle )
{
    m_VertexBuilder.Wrinkle1f( flWrinkle );
}

FORCEINLINE void CMeshBuilder::BoneWeight( int nIndex , float flWeight )
{
    m_VertexBuilder.BoneWeight( nIndex , flWeight );
}

FORCEINLINE void CMeshBuilder::BoneWeights2( float weight1 , float weight2 )
{
    m_VertexBuilder.BoneWeights2( weight1 , weight2 );
}

template <VertexCompressionType_t T> FORCEINLINE void CMeshBuilder::CompressedBoneWeight3fv( const float * pWeights )
{
    m_VertexBuilder.CompressedBoneWeight3fv<T>( pWeights );
}

FORCEINLINE void CMeshBuilder::BoneMatrix( int nIndex , int nMatrixIdx )
{
    m_VertexBuilder.BoneMatrix( nIndex , nMatrixIdx );
}

FORCEINLINE void CMeshBuilder::BoneMatrices4( int matrixIdx0 , int matrixIdx1 , int matrixIdx2 , int matrixIdx3 )
{
    m_VertexBuilder.BoneMatrices4( matrixIdx0 , matrixIdx1 , matrixIdx2 , matrixIdx3 );
}

FORCEINLINE void CMeshBuilder::UserData( const float* pData )
{
    m_VertexBuilder.UserData( pData );
}

template <VertexCompressionType_t T> FORCEINLINE void CMeshBuilder::CompressedUserData( const float* pData )
{
    m_VertexBuilder.CompressedUserData<T>( pData );
}

//-----------------------------------------------------------------------------
// Templatized vertex field setting methods which support compression
//-----------------------------------------------------------------------------

template <VertexCompressionType_t T> FORCEINLINE void CMeshBuilder::CompressedNormal3f( float nx , float ny , float nz )
{
    m_VertexBuilder.CompressedNormal3f<T>( nx , ny , nz );
}

template <VertexCompressionType_t T> FORCEINLINE void CMeshBuilder::CompressedNormal3fv( const float *n )
{
    m_VertexBuilder.CompressedNormal3fv<T>( n );
}

#endif // IMESH_H

#endif