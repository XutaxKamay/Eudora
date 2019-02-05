#ifndef MATERIALSYSTEM
#define MATERIALSYSTEM
#pragma once

// These are given to FindMaterial to reference the texture groups that show up on the
#define TEXTURE_GROUP_LIGHTMAP						"Lightmaps"
#define TEXTURE_GROUP_WORLD							"World textures"
#define TEXTURE_GROUP_MODEL							"Model textures"
#define TEXTURE_GROUP_VGUI							"VGUI textures"
#define TEXTURE_GROUP_PARTICLE						"Particle textures"
#define TEXTURE_GROUP_DECAL							"Decal textures"
#define TEXTURE_GROUP_SKYBOX						"SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				"ClientEffect textures"
#define TEXTURE_GROUP_OTHER							"Other textures"
#define TEXTURE_GROUP_PRECACHED						"Precached"				// TODO: assign texture groups to the precached materials
#define TEXTURE_GROUP_CUBE_MAP						"CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					"RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED					"Unaccounted textures"	// Textures that weren't assigned a texture group.
//#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER		"Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			"Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		"Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	"Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	"World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	"Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	"Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			"Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			"Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER					"DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL					"ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS					"Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS				"Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			"RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS					"Morph Targets"

class IMaterialVar;
class ITexture;
class IMaterialProxy;
class Vector;
class IMaterial;
class IMatRenderContext;
class GPUMemoryStats;
class IFileList;
class IClientMaterialSystem;
class IPaintMapTextureManager;
class IPaintMapDataManager;
struct Rect_t;
struct MaterialSystem_Config_t;
struct ApplicationPerformanceCountersInfo_t;
struct ApplicationInstantCountersInfo_t;

typedef unsigned __int64 uint64;
typedef uint64 VertexFormat_t;

//-----------------------------------------------------------------------------
// allowed stencil operations. These match the d3d operations
//-----------------------------------------------------------------------------
enum ShaderStencilOp_t
{
#if !defined( _X360 )
    SHADER_STENCILOP_KEEP = 1 ,
    SHADER_STENCILOP_ZERO = 2 ,
    SHADER_STENCILOP_SET_TO_REFERENCE = 3 ,
    SHADER_STENCILOP_INCREMENT_CLAMP = 4 ,
    SHADER_STENCILOP_DECREMENT_CLAMP = 5 ,
    SHADER_STENCILOP_INVERT = 6 ,
    SHADER_STENCILOP_INCREMENT_WRAP = 7 ,
    SHADER_STENCILOP_DECREMENT_WRAP = 8 ,
#else
    SHADER_STENCILOP_KEEP = D3DSTENCILOP_KEEP ,
    SHADER_STENCILOP_ZERO = D3DSTENCILOP_ZERO ,
    SHADER_STENCILOP_SET_TO_REFERENCE = D3DSTENCILOP_REPLACE ,
    SHADER_STENCILOP_INCREMENT_CLAMP = D3DSTENCILOP_INCRSAT ,
    SHADER_STENCILOP_DECREMENT_CLAMP = D3DSTENCILOP_DECRSAT ,
    SHADER_STENCILOP_INVERT = D3DSTENCILOP_INVERT ,
    SHADER_STENCILOP_INCREMENT_WRAP = D3DSTENCILOP_INCR ,
    SHADER_STENCILOP_DECREMENT_WRAP = D3DSTENCILOP_DECR ,
#endif
    SHADER_STENCILOP_FORCE_DWORD = 0x7fffffff
};

enum ShaderStencilFunc_t
{
#if !defined( _X360 )
    SHADER_STENCILFUNC_NEVER = 1 ,
    SHADER_STENCILFUNC_LESS = 2 ,
    SHADER_STENCILFUNC_EQUAL = 3 ,
    SHADER_STENCILFUNC_LEQUAL = 4 ,
    SHADER_STENCILFUNC_GREATER = 5 ,
    SHADER_STENCILFUNC_NOTEQUAL = 6 ,
    SHADER_STENCILFUNC_GEQUAL = 7 ,
    SHADER_STENCILFUNC_ALWAYS = 8 ,
#else
    SHADER_STENCILFUNC_NEVER = D3DCMP_NEVER ,
    SHADER_STENCILFUNC_LESS = D3DCMP_LESS ,
    SHADER_STENCILFUNC_EQUAL = D3DCMP_EQUAL ,
    SHADER_STENCILFUNC_LEQUAL = D3DCMP_LESSEQUAL ,
    SHADER_STENCILFUNC_GREATER = D3DCMP_GREATER ,
    SHADER_STENCILFUNC_NOTEQUAL = D3DCMP_NOTEQUAL ,
    SHADER_STENCILFUNC_GEQUAL = D3DCMP_GREATEREQUAL ,
    SHADER_STENCILFUNC_ALWAYS = D3DCMP_ALWAYS ,
#endif

    SHADER_STENCILFUNC_FORCE_DWORD = 0x7fffffff
};

class CMatRenderContextPtr;
class IMatRenderContext;

struct ShaderStencilState_t
{
    bool m_bEnable;
    ShaderStencilOp_t m_FailOp;
    ShaderStencilOp_t m_ZFailOp;
    ShaderStencilOp_t m_PassOp;
    ShaderStencilFunc_t m_CompareFunc;
    int m_nReferenceValue;
    uint32 m_nTestMask;
    uint32 m_nWriteMask;

#if defined( _X360 )
    bool m_bHiStencilEnable;
    bool m_bHiStencilWriteEnable;
    ShaderHiStencilFunc_t m_HiStencilCompareFunc;
    int m_nHiStencilReferenceValue;
#endif

    ShaderStencilState_t()
    {
        m_bEnable = false;
        m_PassOp = m_FailOp = m_ZFailOp = SHADER_STENCILOP_KEEP;
        m_CompareFunc = SHADER_STENCILFUNC_ALWAYS;
        m_nReferenceValue = 0;
        m_nTestMask = m_nWriteMask = 0xFFFFFFFF;

    #if defined( _X360 )
        m_bHiStencilEnable = false;
        m_bHiStencilWriteEnable = false;
        m_HiStencilCompareFunc = SHADER_HI_STENCILFUNC_EQUAL;
        m_nHiStencilReferenceValue = 0;
    #endif
    }
};

//-----------------------------------------------------------------------------
// important enumeration
//-----------------------------------------------------------------------------

enum ImageFormat
{
    IMAGE_FORMAT_UNKNOWN = -1 ,
    IMAGE_FORMAT_RGBA8888 = 0 ,
    IMAGE_FORMAT_ABGR8888 ,
    IMAGE_FORMAT_RGB888 ,
    IMAGE_FORMAT_BGR888 ,
    IMAGE_FORMAT_RGB565 ,
    IMAGE_FORMAT_I8 ,
    IMAGE_FORMAT_IA88 ,
    IMAGE_FORMAT_P8 ,
    IMAGE_FORMAT_A8 ,
    IMAGE_FORMAT_RGB888_BLUESCREEN ,
    IMAGE_FORMAT_BGR888_BLUESCREEN ,
    IMAGE_FORMAT_ARGB8888 ,
    IMAGE_FORMAT_BGRA8888 ,
    IMAGE_FORMAT_DXT1 ,
    IMAGE_FORMAT_DXT3 ,
    IMAGE_FORMAT_DXT5 ,
    IMAGE_FORMAT_BGRX8888 ,
    IMAGE_FORMAT_BGR565 ,
    IMAGE_FORMAT_BGRX5551 ,
    IMAGE_FORMAT_BGRA4444 ,
    IMAGE_FORMAT_DXT1_ONEBITALPHA ,
    IMAGE_FORMAT_BGRA5551 ,
    IMAGE_FORMAT_UV88 ,
    IMAGE_FORMAT_UVWQ8888 ,
    IMAGE_FORMAT_RGBA16161616F ,
    IMAGE_FORMAT_RGBA16161616 ,
    IMAGE_FORMAT_UVLX8888 ,
    IMAGE_FORMAT_R32F ,			// Single-channel 32-bit floating point
    IMAGE_FORMAT_RGB323232F ,	// NOTE: D3D9 does not have this format
    IMAGE_FORMAT_RGBA32323232F ,
    IMAGE_FORMAT_RG1616F ,
    IMAGE_FORMAT_RG3232F ,
    IMAGE_FORMAT_RGBX8888 ,

    IMAGE_FORMAT_NULL ,			// Dummy format which takes no video memory

                                // Compressed normal map formats
                                IMAGE_FORMAT_ATI2N ,			// One-surface ATI2N / DXN format
                                IMAGE_FORMAT_ATI1N ,			// Two-surface ATI1N format

                                IMAGE_FORMAT_RGBA1010102 ,	// 10 bit-per component render targets
                                IMAGE_FORMAT_BGRA1010102 ,
                                IMAGE_FORMAT_R16F ,			// 16 bit FP format

                                                            // Depth-stencil texture formats
                                                            IMAGE_FORMAT_D16 ,
                                                            IMAGE_FORMAT_D15S1 ,
                                                            IMAGE_FORMAT_D32 ,
                                                            IMAGE_FORMAT_D24S8 ,
                                                            IMAGE_FORMAT_LINEAR_D24S8 ,
                                                            IMAGE_FORMAT_D24X8 ,
                                                            IMAGE_FORMAT_D24X4S4 ,
                                                            IMAGE_FORMAT_D24FS8 ,
                                                            IMAGE_FORMAT_D16_SHADOW ,	// Specific formats for shadow mapping
                                                            IMAGE_FORMAT_D24X8_SHADOW ,	// Specific formats for shadow mapping

                                                                                        // supporting these specific formats as non-tiled for procedural cpu access (360-specific)
                                                                                        IMAGE_FORMAT_LINEAR_BGRX8888 ,
                                                                                        IMAGE_FORMAT_LINEAR_RGBA8888 ,
                                                                                        IMAGE_FORMAT_LINEAR_ABGR8888 ,
                                                                                        IMAGE_FORMAT_LINEAR_ARGB8888 ,
                                                                                        IMAGE_FORMAT_LINEAR_BGRA8888 ,
                                                                                        IMAGE_FORMAT_LINEAR_RGB888 ,
                                                                                        IMAGE_FORMAT_LINEAR_BGR888 ,
                                                                                        IMAGE_FORMAT_LINEAR_BGRX5551 ,
                                                                                        IMAGE_FORMAT_LINEAR_I8 ,
                                                                                        IMAGE_FORMAT_LINEAR_RGBA16161616 ,

                                                                                        IMAGE_FORMAT_LE_BGRX8888 ,
                                                                                        IMAGE_FORMAT_LE_BGRA8888 ,

                                                                                        NUM_IMAGE_FORMATS
};

enum ShaderParamType_t
{
    SHADER_PARAM_TYPE_TEXTURE ,
    SHADER_PARAM_TYPE_INTEGER ,
    SHADER_PARAM_TYPE_COLOR ,
    SHADER_PARAM_TYPE_VEC2 ,
    SHADER_PARAM_TYPE_VEC3 ,
    SHADER_PARAM_TYPE_VEC4 ,
    SHADER_PARAM_TYPE_ENVMAP ,	// obsolete
    SHADER_PARAM_TYPE_FLOAT ,
    SHADER_PARAM_TYPE_BOOL ,
    SHADER_PARAM_TYPE_FOURCC ,
    SHADER_PARAM_TYPE_MATRIX ,
    SHADER_PARAM_TYPE_MATERIAL ,
    SHADER_PARAM_TYPE_STRING ,
};

enum MaterialMatrixMode_t
{
    MATERIAL_VIEW = 0 ,
    MATERIAL_PROJECTION ,

    MATERIAL_MATRIX_UNUSED0 ,
    MATERIAL_MATRIX_UNUSED1 ,
    MATERIAL_MATRIX_UNUSED2 ,
    MATERIAL_MATRIX_UNUSED3 ,
    MATERIAL_MATRIX_UNUSED4 ,
    MATERIAL_MATRIX_UNUSED5 ,
    MATERIAL_MATRIX_UNUSED6 ,
    MATERIAL_MATRIX_UNUSED7 ,

    MATERIAL_MODEL ,

    // Total number of matrices
    NUM_MATRIX_MODES = MATERIAL_MODEL + 1 ,
};

// FIXME: How do I specify the actual number of matrix modes?
const int NUM_MODEL_TRANSFORMS = 53;
const int MATERIAL_MODEL_MAX = MATERIAL_MODEL + NUM_MODEL_TRANSFORMS;

enum MaterialPrimitiveType_t
{
    MATERIAL_POINTS = 0x0 ,
    MATERIAL_LINES ,
    MATERIAL_TRIANGLES ,
    MATERIAL_TRIANGLE_STRIP ,
    MATERIAL_LINE_STRIP ,
    MATERIAL_LINE_LOOP ,	// a single line loop
    MATERIAL_POLYGON ,	// this is a *single* polygon
    MATERIAL_QUADS ,
    MATERIAL_SUBD_QUADS_EXTRA , // Extraordinary sub-d quads
    MATERIAL_SUBD_QUADS_REG ,   // Regular sub-d quads
    MATERIAL_INSTANCED_QUADS , // (X360) like MATERIAL_QUADS, but uses vertex instancing

                               // This is used for static meshes that contain multiple types of
                               // primitive types.	When calling draw, you'll need to specify
                               // a primitive type.
                               MATERIAL_HETEROGENOUS
};

enum TessellationMode_t
{
    TESSELLATION_MODE_DISABLED = 0 ,
    TESSELLATION_MODE_ACC_PATCHES_EXTRA ,
    TESSELLATION_MODE_ACC_PATCHES_REG
};

enum MaterialPropertyTypes_t
{
    MATERIAL_PROPERTY_NEEDS_LIGHTMAP = 0 ,					// bool
    MATERIAL_PROPERTY_OPACITY ,								// int (enum MaterialPropertyOpacityTypes_t)
    MATERIAL_PROPERTY_REFLECTIVITY ,							// vec3_t
    MATERIAL_PROPERTY_NEEDS_BUMPED_LIGHTMAPS				// bool
};

// acceptable property values for MATERIAL_PROPERTY_OPACITY
enum MaterialPropertyOpacityTypes_t
{
    MATERIAL_ALPHATEST = 0 ,
    MATERIAL_OPAQUE ,
    MATERIAL_TRANSLUCENT
};

enum MaterialBufferTypes_t
{
    MATERIAL_FRONT = 0 ,
    MATERIAL_BACK
};

enum MaterialCullMode_t
{
    MATERIAL_CULLMODE_CCW ,	// this culls polygons with counterclockwise winding
    MATERIAL_CULLMODE_CW	// this culls polygons with clockwise winding
};

enum MaterialIndexFormat_t
{
    MATERIAL_INDEX_FORMAT_UNKNOWN = -1 ,
    MATERIAL_INDEX_FORMAT_16BIT = 0 ,
    MATERIAL_INDEX_FORMAT_32BIT ,
};

enum MaterialFogMode_t
{
    MATERIAL_FOG_NONE ,
    MATERIAL_FOG_LINEAR ,
    MATERIAL_FOG_LINEAR_BELOW_FOG_Z ,
};

enum MaterialHeightClipMode_t
{
    MATERIAL_HEIGHTCLIPMODE_DISABLE ,
    MATERIAL_HEIGHTCLIPMODE_RENDER_ABOVE_HEIGHT ,
    MATERIAL_HEIGHTCLIPMODE_RENDER_BELOW_HEIGHT
};

enum MaterialNonInteractiveMode_t
{
    MATERIAL_NON_INTERACTIVE_MODE_NONE = -1 ,
    MATERIAL_NON_INTERACTIVE_MODE_STARTUP = 0 ,
    MATERIAL_NON_INTERACTIVE_MODE_LEVEL_LOAD ,

    MATERIAL_NON_INTERACTIVE_MODE_COUNT ,
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

enum MaterialThreadMode_t
{
    MATERIAL_SINGLE_THREADED ,
    MATERIAL_QUEUED_SINGLE_THREADED ,
    MATERIAL_QUEUED_THREADED
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

enum MaterialContextType_t
{
    MATERIAL_HARDWARE_CONTEXT ,
    MATERIAL_QUEUED_CONTEXT ,
    MATERIAL_NULL_CONTEXT
};

enum
{
    MATERIAL_MAX_LIGHT_COUNT = 4 ,
};

#define CREATERENDERTARGETFLAGS_HDR				0x00000001
#define CREATERENDERTARGETFLAGS_AUTOMIPMAP		0x00000002
#define CREATERENDERTARGETFLAGS_UNFILTERABLE_OK 0x00000004
// XBOX ONLY:
#define CREATERENDERTARGETFLAGS_NOEDRAM			0x00000008 // inhibit allocation in 360 EDRAM
#define CREATERENDERTARGETFLAGS_TEMP			0x00000010 // only allocates memory upon first resolve, destroyed at level end

//-----------------------------------------------------------------------------
// Enumeration for the various fields capable of being morphed
//-----------------------------------------------------------------------------
enum MorphFormatFlags_t
{
    MORPH_POSITION = 0x0001 ,	// 3D
    MORPH_NORMAL = 0x0002 ,	// 3D
    MORPH_WRINKLE = 0x0004 ,	// 1D
    MORPH_SPEED = 0x0008 ,	// 1D
    MORPH_SIDE = 0x0010 ,	// 1D
};

//-----------------------------------------------------------------------------
// The morph format type
//-----------------------------------------------------------------------------
typedef unsigned int MorphFormat_t;

//-----------------------------------------------------------------------------
// Standard lightmaps
//-----------------------------------------------------------------------------
enum StandardLightmap_t
{
    MATERIAL_SYSTEM_LIGHTMAP_PAGE_WHITE = -1 ,
    MATERIAL_SYSTEM_LIGHTMAP_PAGE_WHITE_BUMP = -2 ,
    MATERIAL_SYSTEM_LIGHTMAP_PAGE_USER_DEFINED = -3
};

enum
{
    TEXTUREFLAGS_POINTSAMPLE = 0x00000001 ,
    TEXTUREFLAGS_TRILINEAR = 0x00000002 ,
    TEXTUREFLAGS_CLAMPS = 0x00000004 ,
    TEXTUREFLAGS_CLAMPT = 0x00000008 ,
    TEXTUREFLAGS_ANISOTROPIC = 0x00000010 ,
    TEXTUREFLAGS_HINT_DXT5 = 0x00000020 ,
    TEXTUREFLAGS_NOCOMPRESS = 0x00000040 ,
    TEXTUREFLAGS_NORMAL = 0x00000080 ,
    TEXTUREFLAGS_NOMIP = 0x00000100 ,
    TEXTUREFLAGS_NOLOD = 0x00000200 ,
    TEXTUREFLAGS_MINMIP = 0x00000400 ,
    TEXTUREFLAGS_PROCEDURAL = 0x00000800 ,
    TEXTUREFLAGS_ONEBITALPHA = 0x00001000 ,
    TEXTUREFLAGS_EIGHTBITALPHA = 0x00002000 ,
    TEXTUREFLAGS_ENVMAP = 0x00004000 ,
    TEXTUREFLAGS_RENDERTARGET = 0x00008000 ,
    TEXTUREFLAGS_DEPTHRENDERTARGET = 0x00010000 ,
    TEXTUREFLAGS_NODEBUGOVERRIDE = 0x00020000 ,
    TEXTUREFLAGS_SINGLECOPY = 0x00040000 ,
    TEXTUREFLAGS_ONEOVERMIPLEVELINALPHA = 0x00080000 ,
    TEXTUREFLAGS_PREMULTCOLORBYONEOVERMIPLEVEL = 0x00100000 ,
    TEXTUREFLAGS_NORMALTODUDV = 0x00200000 ,
    TEXTUREFLAGS_ALPHATESTMIPGENERATION = 0x00400000 ,
    TEXTUREFLAGS_NODEPTHBUFFER = 0x00800000 ,
    TEXTUREFLAGS_NICEFILTERED = 0x01000000 ,
    TEXTUREFLAGS_CLAMPU = 0x02000000
};

struct MaterialSystem_SortInfo_t
{
    IMaterial	*material;
    int			lightmapPageID;
};

struct AspectRatioInfo_t
{
    bool m_bIsWidescreen;
    bool m_bIsHidef;
    float m_flFrameBufferAspectRatio;
    float m_flPhysicalAspectRatio;
    float m_flFrameBuffertoPhysicalScalar;
    float m_flPhysicalToFrameBufferScalar;
    bool m_bInitialized;
};

// HDRFIXME NOTE: must match common_ps_fxc.h
enum HDRType_t
{
    HDR_TYPE_NONE ,
    HDR_TYPE_INTEGER ,
    HDR_TYPE_FLOAT ,
};

#define MAX_FB_TEXTURES 4

//-----------------------------------------------------------------------------
// Information about each adapter
//-----------------------------------------------------------------------------
enum
{
    MATERIAL_ADAPTER_NAME_LENGTH = 512
};

struct MaterialAdapterInfo_t
{
    char m_pDriverName[ MATERIAL_ADAPTER_NAME_LENGTH ];
    unsigned int m_VendorID;
    unsigned int m_DeviceID;
    unsigned int m_SubSysID;
    unsigned int m_Revision;
    int m_nDXSupportLevel;			// This is the *preferred* dx support level
    int m_nMinDXSupportLevel;
    int m_nMaxDXSupportLevel;
    unsigned int m_nDriverVersionHigh;
    unsigned int m_nDriverVersionLow;
};

//-----------------------------------------------------------------------------
// Video mode info..
//-----------------------------------------------------------------------------
struct MaterialVideoMode_t
{
    int m_Width;			// if width and height are 0 and you select
    int m_Height;			// windowed mode, it'll use the window size
    ImageFormat m_Format;	// use ImageFormats (ignored for windowed mode)
    int m_RefreshRate;		// 0 == default (ignored for windowed mode)
};

//-----------------------------------------------------------------------------
// Flags to be used with the Init call
//-----------------------------------------------------------------------------
enum MaterialInitFlags_t
{
    MATERIAL_INIT_ALLOCATE_FULLSCREEN_TEXTURE = 0x2 ,
    MATERIAL_INIT_REFERENCE_RASTERIZER = 0x4 ,
};

//-----------------------------------------------------------------------------
// Flags to specify type of depth buffer used with RT
//-----------------------------------------------------------------------------

// GR - this is to add RT with no depth buffer bound

enum MaterialRenderTargetDepth_t
{
    MATERIAL_RT_DEPTH_SHARED = 0x0 ,
    MATERIAL_RT_DEPTH_SEPARATE = 0x1 ,
    MATERIAL_RT_DEPTH_NONE = 0x2 ,
    MATERIAL_RT_DEPTH_ONLY = 0x3 ,
};

//-----------------------------------------------------------------------------
// A function to be called when we need to release all vertex buffers
// NOTE: The restore function will tell the caller if all the vertex formats
// changed so that it can flush caches, etc. if it needs to (for dxlevel support)
//-----------------------------------------------------------------------------
enum RestoreChangeFlags_t
{
    MATERIAL_RESTORE_VERTEX_FORMAT_CHANGED = 0x1 ,
    MATERIAL_RESTORE_RELEASE_MANAGED_RESOURCES = 0x2 ,
};

// NOTE: All size modes will force the render target to be smaller than or equal to
// the size of the framebuffer.
enum RenderTargetSizeMode_t
{
    RT_SIZE_NO_CHANGE = 0 ,			// Only allowed for render targets that don't want a depth buffer
                                    // (because if they have a depth buffer, the render target must be less than or equal to the size of the framebuffer).
                                    RT_SIZE_DEFAULT = 1 ,				// Don't play with the specified width and height other than making sure it fits in the framebuffer.
                                    RT_SIZE_PICMIP = 2 ,				// Apply picmip to the render target's width and height.
                                    RT_SIZE_HDR = 3 ,					// frame_buffer_width / 4
                                    RT_SIZE_FULL_FRAME_BUFFER = 4 ,	// Same size as frame buffer, or next lower power of 2 if we can't do that.
                                    RT_SIZE_OFFSCREEN = 5 ,			// Target of specified size, don't mess with dimensions
                                    RT_SIZE_FULL_FRAME_BUFFER_ROUNDED_UP = 6 // Same size as the frame buffer, rounded up if necessary for systems that can't do non-power of two textures.
};

typedef void( *MaterialBufferReleaseFunc_t )( int nChangeFlags );	// see RestoreChangeFlags_t
typedef void( *MaterialBufferRestoreFunc_t )( int nChangeFlags );	// see RestoreChangeFlags_t
typedef void( *ModeChangeCallbackFunc_t )( void );
typedef void( *EndFrameCleanupFunc_t )( void );
typedef bool( *EndFramePriorToNextContextFunc_t )( void );
typedef void( *OnLevelShutdownFunc_t )( void *pUserData );

//typedef int VertexBufferHandle_t;
typedef unsigned short MaterialHandle_t;

DECLARE_POINTER_HANDLE( OcclusionQueryObjectHandle_t );
#define INVALID_OCCLUSION_QUERY_OBJECT_HANDLE ( (OcclusionQueryObjectHandle_t)0 )

class IMaterialProxyFactory;
class ITexture;
class IMaterialSystemHardwareConfig;
class CShadowMgr;

DECLARE_POINTER_HANDLE( MaterialLock_t );

//-----------------------------------------------------------------------------
// Information about a material texture
//-----------------------------------------------------------------------------

struct MaterialTextureInfo_t
{
    // Exclude information:
    //		-1	texture is not subject to exclude-handling
    //		 0	texture is completely excluded
    //		>0	texture is clamped according to exclude-instruction
    int iExcludeInformation;
};

struct ApplicationPerformanceCountersInfo_t
{
    float msMain;
    float msMST;
    float msGPU;
    float msFlip;
    float msTotal;
};

struct ApplicationInstantCountersInfo_t
{
    UINT m_nCpuActivityMask;
    UINT m_nDeferredWordsAllocated;
};

struct MaterialSystemHardwareIdentifier_t
{
    char *m_pCardName;
    unsigned int m_nVendorID;
    unsigned int m_nDeviceID;
};

//-----------------------------------------------------------------------------
// Flags for GetVertexFormat
//-----------------------------------------------------------------------------
enum VertexFormatFlags_t
{
    // Indicates an uninitialized VertexFormat_t value
    VERTEX_FORMAT_INVALID = 0xFFFFFFFFFFFFFFFFull ,

    VERTEX_POSITION = 0x0001 ,
    VERTEX_NORMAL = 0x0002 ,
    VERTEX_COLOR = 0x0004 ,
    VERTEX_SPECULAR = 0x0008 ,

    VERTEX_TANGENT_S = 0x0010 ,
    VERTEX_TANGENT_T = 0x0020 ,
    VERTEX_TANGENT_SPACE = VERTEX_TANGENT_S | VERTEX_TANGENT_T ,

    // Indicates we're using wrinkle
    VERTEX_WRINKLE = 0x0040 ,

    // Indicates we're using bone indices
    VERTEX_BONE_INDEX = 0x0080 ,

    // Indicates this expects a color stream on stream 1
    VERTEX_COLOR_STREAM_1 = 0x0100 ,

    // Indicates this format shouldn't be bloated to cache align it
    // (only used for VertexUsage)
    VERTEX_FORMAT_USE_EXACT_FORMAT = 0x0200 ,

    // Indicates that compressed vertex elements are to be used (see also VertexCompressionType_t)
    VERTEX_FORMAT_COMPRESSED = 0x400 ,

    // Position or normal (if present) should be 4D not 3D
    VERTEX_FORMAT_PAD_POS_NORM = 0x800 ,

    // Update this if you add or remove bits...
    VERTEX_LAST_BIT = 11 ,

    VERTEX_BONE_WEIGHT_BIT = VERTEX_LAST_BIT + 1 ,
    USER_DATA_SIZE_BIT = VERTEX_LAST_BIT + 4 ,
    TEX_COORD_SIZE_BIT = VERTEX_LAST_BIT + 7 ,

    VERTEX_BONE_WEIGHT_MASK = ( 0x7 << VERTEX_BONE_WEIGHT_BIT ) ,
    USER_DATA_SIZE_MASK = ( 0x7 << USER_DATA_SIZE_BIT ) ,

    VERTEX_FORMAT_FIELD_MASK = 0x0FF ,

    // If everything is off, it's an unknown vertex format
    VERTEX_FORMAT_UNKNOWN = 0 ,
};

//-----------------------------------------------------------------------------
// Macros for construction..
//-----------------------------------------------------------------------------
#define VERTEX_BONEWEIGHT( _n )				((_n) << VERTEX_BONE_WEIGHT_BIT)
#define VERTEX_USERDATA_SIZE( _n )			((_n) << USER_DATA_SIZE_BIT)
#define VERTEX_TEXCOORD_MASK( _coord )		(( 0x7ULL ) << ( TEX_COORD_SIZE_BIT + 3 * (_coord) ))

inline VertexFormat_t VERTEX_TEXCOORD_SIZE( int nIndex , int nNumCoords )
{
    uint64 n64 = nNumCoords;
    uint64 nShift = TEX_COORD_SIZE_BIT + ( 3 * nIndex );
    return n64 << nShift;
}

//-----------------------------------------------------------------------------
// Gets at various vertex format info...
//-----------------------------------------------------------------------------
inline int VertexFlags( VertexFormat_t vertexFormat )
{
    return static_cast< int > ( vertexFormat & ( ( 1 << ( VERTEX_LAST_BIT + 1 ) ) - 1 ) );
}

inline int NumBoneWeights( VertexFormat_t vertexFormat )
{
    return static_cast< int > ( ( vertexFormat >> VERTEX_BONE_WEIGHT_BIT ) & 0x7 );
}

inline int UserDataSize( VertexFormat_t vertexFormat )
{
    return static_cast< int > ( ( vertexFormat >> USER_DATA_SIZE_BIT ) & 0x7 );
}

inline int TexCoordSize( int nTexCoordIndex , VertexFormat_t vertexFormat )
{
    return static_cast< int > ( ( vertexFormat >> ( TEX_COORD_SIZE_BIT + 3 * nTexCoordIndex ) ) & 0x7 );
}

//-----------------------------------------------------------------------------
// VertexElement_t (enumerates all usable vertex elements)
//-----------------------------------------------------------------------------
// FIXME: unify this with VertexFormat_t (i.e. construct the lower bits of VertexFormat_t with "1 << (VertexElement_t)element")
enum VertexElement_t
{
    VERTEX_ELEMENT_NONE = -1 ,

    // Deliberately explicitly numbered so it's a pain in the ass to change, so you read this:
    // #!#!#NOTE#!#!# update GetVertexElementSize, VertexElementToDeclType and
    //                CVBAllocTracker (elementTable) when you update this!
    VERTEX_ELEMENT_POSITION = 0 ,
    VERTEX_ELEMENT_POSITION4D = 1 ,
    VERTEX_ELEMENT_NORMAL = 2 ,
    VERTEX_ELEMENT_NORMAL4D = 3 ,
    VERTEX_ELEMENT_COLOR = 4 ,
    VERTEX_ELEMENT_SPECULAR = 5 ,
    VERTEX_ELEMENT_TANGENT_S = 6 ,
    VERTEX_ELEMENT_TANGENT_T = 7 ,
    VERTEX_ELEMENT_WRINKLE = 8 ,
    VERTEX_ELEMENT_BONEINDEX = 9 ,
    VERTEX_ELEMENT_BONEWEIGHTS1 = 10 ,
    VERTEX_ELEMENT_BONEWEIGHTS2 = 11 ,
    VERTEX_ELEMENT_BONEWEIGHTS3 = 12 ,
    VERTEX_ELEMENT_BONEWEIGHTS4 = 13 ,
    VERTEX_ELEMENT_USERDATA1 = 14 ,
    VERTEX_ELEMENT_USERDATA2 = 15 ,
    VERTEX_ELEMENT_USERDATA3 = 16 ,
    VERTEX_ELEMENT_USERDATA4 = 17 ,
    VERTEX_ELEMENT_TEXCOORD1D_0 = 18 ,
    VERTEX_ELEMENT_TEXCOORD1D_1 = 19 ,
    VERTEX_ELEMENT_TEXCOORD1D_2 = 20 ,
    VERTEX_ELEMENT_TEXCOORD1D_3 = 21 ,
    VERTEX_ELEMENT_TEXCOORD1D_4 = 22 ,
    VERTEX_ELEMENT_TEXCOORD1D_5 = 23 ,
    VERTEX_ELEMENT_TEXCOORD1D_6 = 24 ,
    VERTEX_ELEMENT_TEXCOORD1D_7 = 25 ,
    VERTEX_ELEMENT_TEXCOORD2D_0 = 26 ,
    VERTEX_ELEMENT_TEXCOORD2D_1 = 27 ,
    VERTEX_ELEMENT_TEXCOORD2D_2 = 28 ,
    VERTEX_ELEMENT_TEXCOORD2D_3 = 29 ,
    VERTEX_ELEMENT_TEXCOORD2D_4 = 30 ,
    VERTEX_ELEMENT_TEXCOORD2D_5 = 31 ,
    VERTEX_ELEMENT_TEXCOORD2D_6 = 32 ,
    VERTEX_ELEMENT_TEXCOORD2D_7 = 33 ,
    VERTEX_ELEMENT_TEXCOORD3D_0 = 34 ,
    VERTEX_ELEMENT_TEXCOORD3D_1 = 35 ,
    VERTEX_ELEMENT_TEXCOORD3D_2 = 36 ,
    VERTEX_ELEMENT_TEXCOORD3D_3 = 37 ,
    VERTEX_ELEMENT_TEXCOORD3D_4 = 38 ,
    VERTEX_ELEMENT_TEXCOORD3D_5 = 39 ,
    VERTEX_ELEMENT_TEXCOORD3D_6 = 40 ,
    VERTEX_ELEMENT_TEXCOORD3D_7 = 41 ,
    VERTEX_ELEMENT_TEXCOORD4D_0 = 42 ,
    VERTEX_ELEMENT_TEXCOORD4D_1 = 43 ,
    VERTEX_ELEMENT_TEXCOORD4D_2 = 44 ,
    VERTEX_ELEMENT_TEXCOORD4D_3 = 45 ,
    VERTEX_ELEMENT_TEXCOORD4D_4 = 46 ,
    VERTEX_ELEMENT_TEXCOORD4D_5 = 47 ,
    VERTEX_ELEMENT_TEXCOORD4D_6 = 48 ,
    VERTEX_ELEMENT_TEXCOORD4D_7 = 49 ,

    VERTEX_ELEMENT_NUMELEMENTS = 50
};

// We're testing 2 normal compression methods
// One compressed normals+tangents into a SHORT2 each (8 bytes total)
// The other compresses them together, into a single UBYTE4 (4 bytes total)
// FIXME: pick one or the other, compare lighting quality in important cases
#define COMPRESSED_NORMALS_SEPARATETANGENTS_SHORT2	0
#define COMPRESSED_NORMALS_COMBINEDTANGENTS_UBYTE4	1
//#define COMPRESSED_NORMALS_TYPE						COMPRESSED_NORMALS_SEPARATETANGENTS_SHORT2
#define COMPRESSED_NORMALS_TYPE						COMPRESSED_NORMALS_COMBINEDTANGENTS_UBYTE4

//-----------------------------------------------------------------------------
// Shader state flags can be read from the FLAGS materialvar
// Also can be read or written to with the Set/GetMaterialVarFlags() call
// Also make sure you add/remove a string associated with each flag below to CShaderSystem::ShaderStateString in ShaderSystem.cpp
//-----------------------------------------------------------------------------
enum MaterialVarFlags_t
{
    MATERIAL_VAR_DEBUG = ( 1 << 0 ) ,
    MATERIAL_VAR_NO_DEBUG_OVERRIDE = ( 1 << 1 ) ,
    MATERIAL_VAR_NO_DRAW = ( 1 << 2 ) ,
    MATERIAL_VAR_USE_IN_FILLRATE_MODE = ( 1 << 3 ) ,

    MATERIAL_VAR_VERTEXCOLOR = ( 1 << 4 ) ,
    MATERIAL_VAR_VERTEXALPHA = ( 1 << 5 ) ,
    MATERIAL_VAR_SELFILLUM = ( 1 << 6 ) ,
    MATERIAL_VAR_ADDITIVE = ( 1 << 7 ) ,
    MATERIAL_VAR_ALPHATEST = ( 1 << 8 ) ,
    //	MATERIAL_VAR_UNUSED					  = (1 << 9),
    MATERIAL_VAR_ZNEARER = ( 1 << 10 ) ,
    MATERIAL_VAR_MODEL = ( 1 << 11 ) ,
    MATERIAL_VAR_FLAT = ( 1 << 12 ) ,
    MATERIAL_VAR_NOCULL = ( 1 << 13 ) ,
    MATERIAL_VAR_NOFOG = ( 1 << 14 ) ,
    MATERIAL_VAR_IGNOREZ = ( 1 << 15 ) ,
    MATERIAL_VAR_DECAL = ( 1 << 16 ) ,
    MATERIAL_VAR_ENVMAPSPHERE = ( 1 << 17 ) , // OBSOLETE
                                              //	MATERIAL_VAR_UNUSED					  = (1 << 18),
                                              MATERIAL_VAR_ENVMAPCAMERASPACE = ( 1 << 19 ) , // OBSOLETE
                                              MATERIAL_VAR_BASEALPHAENVMAPMASK = ( 1 << 20 ) ,
                                              MATERIAL_VAR_TRANSLUCENT = ( 1 << 21 ) ,
                                              MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = ( 1 << 22 ) ,
                                              MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = ( 1 << 23 ) , // OBSOLETE
                                              MATERIAL_VAR_OPAQUETEXTURE = ( 1 << 24 ) ,
                                              MATERIAL_VAR_ENVMAPMODE = ( 1 << 25 ) , // OBSOLETE
                                              MATERIAL_VAR_SUPPRESS_DECALS = ( 1 << 26 ) ,
                                              MATERIAL_VAR_HALFLAMBERT = ( 1 << 27 ) ,
                                              MATERIAL_VAR_WIREFRAME = ( 1 << 28 ) ,
                                              MATERIAL_VAR_ALLOWALPHATOCOVERAGE = ( 1 << 29 ) ,
                                              MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = ( 1 << 30 ) ,
                                              MATERIAL_VAR_VERTEXFOG = ( 1 << 31 ) ,

                                              // NOTE: Only add flags here that either should be read from
                                              // .vmts or can be set directly from client code. Other, internal
                                              // flags should to into the flag enum in IMaterialInternal.h
};

//-----------------------------------------------------------------------------
// Internal flags not accessible from outside the material system. Stored in Flags2
//-----------------------------------------------------------------------------
enum MaterialVarFlags2_t
{
    // NOTE: These are for $flags2!!!!!
    //	UNUSED											= (1 << 0),

    MATERIAL_VAR2_LIGHTING_UNLIT = 0 ,
    MATERIAL_VAR2_LIGHTING_VERTEX_LIT = ( 1 << 1 ) ,
    MATERIAL_VAR2_LIGHTING_LIGHTMAP = ( 1 << 2 ) ,
    MATERIAL_VAR2_LIGHTING_BUMPED_LIGHTMAP = ( 1 << 3 ) ,
    MATERIAL_VAR2_LIGHTING_MASK =
    ( MATERIAL_VAR2_LIGHTING_VERTEX_LIT |
      MATERIAL_VAR2_LIGHTING_LIGHTMAP |
      MATERIAL_VAR2_LIGHTING_BUMPED_LIGHTMAP ) ,

    // FIXME: Should this be a part of the above lighting enums?
    MATERIAL_VAR2_DIFFUSE_BUMPMAPPED_MODEL = ( 1 << 4 ) ,
    MATERIAL_VAR2_USES_ENV_CUBEMAP = ( 1 << 5 ) ,
    MATERIAL_VAR2_NEEDS_TANGENT_SPACES = ( 1 << 6 ) ,
    MATERIAL_VAR2_NEEDS_SOFTWARE_LIGHTING = ( 1 << 7 ) ,
    // GR - HDR path puts lightmap alpha in separate texture...
    MATERIAL_VAR2_BLEND_WITH_LIGHTMAP_ALPHA = ( 1 << 8 ) ,
    MATERIAL_VAR2_NEEDS_BAKED_LIGHTING_SNAPSHOTS = ( 1 << 9 ) ,
    MATERIAL_VAR2_USE_FLASHLIGHT = ( 1 << 10 ) ,
    MATERIAL_VAR2_USE_FIXED_FUNCTION_BAKED_LIGHTING = ( 1 << 11 ) ,
    MATERIAL_VAR2_NEEDS_FIXED_FUNCTION_FLASHLIGHT = ( 1 << 12 ) ,
    MATERIAL_VAR2_USE_EDITOR = ( 1 << 13 ) ,
    MATERIAL_VAR2_NEEDS_POWER_OF_TWO_FRAME_BUFFER_TEXTURE = ( 1 << 14 ) ,
    MATERIAL_VAR2_NEEDS_FULL_FRAME_BUFFER_TEXTURE = ( 1 << 15 ) ,
    MATERIAL_VAR2_IS_SPRITECARD = ( 1 << 16 ) ,
    MATERIAL_VAR2_USES_VERTEXID = ( 1 << 17 ) ,
    MATERIAL_VAR2_SUPPORTS_HW_SKINNING = ( 1 << 18 ) ,
    MATERIAL_VAR2_SUPPORTS_FLASHLIGHT = ( 1 << 19 ) ,
    MATERIAL_VAR2_USE_GBUFFER0 = ( 1 << 20 ) ,
    MATERIAL_VAR2_USE_GBUFFER1 = ( 1 << 21 ) ,
    MATERIAL_VAR2_SELFILLUMMASK = ( 1 << 22 ) ,
    MATERIAL_VAR2_SUPPORTS_TESSELLATION = ( 1 << 23 )
};

//-----------------------------------------------------------------------------
// Preview image return values
//-----------------------------------------------------------------------------
enum PreviewImageRetVal_t
{
    MATERIAL_PREVIEW_IMAGE_BAD = 0 ,
    MATERIAL_PREVIEW_IMAGE_OK ,
    MATERIAL_NO_PREVIEW_IMAGE ,
};

//-----------------------------------------------------------------------------
// material interface
//-----------------------------------------------------------------------------
class IMaterial
{
public:
    // Get the name of the material.  This is a full path to
    // the vmt file starting from "hl2/materials" (or equivalent) without
    // a file extension.
    virtual const char *	GetName() const = 0;
    virtual const char *	GetTextureGroupName() const = 0;

    // Get the preferred size/bitDepth of a preview image of a material.
    // This is the sort of image that you would use for a thumbnail view
    // of a material, or in WorldCraft until it uses materials to render.
    // separate this for the tools maybe
    virtual PreviewImageRetVal_t GetPreviewImageProperties( int *width , int *height ,
                                                            ImageFormat *imageFormat , bool* isTranslucent ) const = 0;

    // Get a preview image at the specified width/height and bitDepth.
    // Will do resampling if necessary.(not yet!!! :) )
    // Will do color format conversion. (works now.)
    virtual PreviewImageRetVal_t GetPreviewImage( unsigned char *data ,
                                                  int width , int height ,
                                                  ImageFormat imageFormat ) const = 0;
    //
    virtual int				GetMappingWidth() = 0;
    virtual int				GetMappingHeight() = 0;

    virtual int				GetNumAnimationFrames() = 0;

    // For material subrects (material pages).  Offset(u,v) and scale(u,v) are normalized to texture.
    virtual bool			InMaterialPage( void ) = 0;
    virtual	void			GetMaterialOffset( float *pOffset ) = 0;
    virtual void			GetMaterialScale( float *pScale ) = 0;
    virtual IMaterial		*GetMaterialPage( void ) = 0;

    // find a vmt variable.
    // This is how game code affects how a material is rendered.
    // The game code must know about the params that are used by
    // the shader for the material that it is trying to affect.
    virtual IMaterialVar *	FindVar( const char *varName , bool *found , bool complain = true ) = 0;

    // The user never allocates or deallocates materials.  Reference counting is
    // used instead.  Garbage collection is done upon a call to
    // IMaterialSystem::UncacheUnusedMaterials.
    virtual void			IncrementReferenceCount( void ) = 0;
    virtual void			DecrementReferenceCount( void ) = 0;

    inline void AddRef()
    {
        IncrementReferenceCount();
    }
    inline void Release()
    {
        DecrementReferenceCount();
    }

    // Each material is assigned a number that groups it with like materials
    // for sorting in the application.
    virtual int 			GetEnumerationID( void ) const = 0;

    virtual void			GetLowResColorSample( float s , float t , float *color ) const = 0;

    // This computes the state snapshots for this material
    virtual void			RecomputeStateSnapshots() = 0;

    // Are we translucent?
    virtual bool			IsTranslucent() = 0;

    // Are we alphatested?
    virtual bool			IsAlphaTested() = 0;

    // Are we vertex lit?
    virtual bool			IsVertexLit() = 0;

    // Gets the vertex format
    virtual VertexFormat_t	GetVertexFormat() const = 0;

    // returns true if this material uses a material proxy
    virtual bool			HasProxy( void ) const = 0;

    virtual bool			UsesEnvCubemap( void ) = 0;

    virtual bool			NeedsTangentSpace( void ) = 0;

    virtual bool			NeedsPowerOfTwoFrameBufferTexture( bool bCheckSpecificToThisFrame = true ) = 0;
    virtual bool			NeedsFullFrameBufferTexture( bool bCheckSpecificToThisFrame = true ) = 0;

    // returns true if the shader doesn't do skinning itself and requires
    // the data that is sent to it to be preskinned.
    virtual bool			NeedsSoftwareSkinning( void ) = 0;

    // Apply constant color or alpha modulation
    virtual void			AlphaModulate( float alpha ) = 0;
    virtual void			ColorModulate( float r , float g , float b ) = 0;

    // Material Var flags...
    virtual void			SetMaterialVarFlag( MaterialVarFlags_t flag , bool on ) = 0;
    virtual bool			GetMaterialVarFlag( MaterialVarFlags_t flag ) const = 0;

    // Gets material reflectivity
    virtual void			GetReflectivity( Vector& reflect ) = 0;

    // Gets material property flags
    virtual bool			GetPropertyFlag( MaterialPropertyTypes_t type ) = 0;

    // Is the material visible from both sides?
    virtual bool			IsTwoSided() = 0;

    // Sets the shader associated with the material
    virtual void			SetShader( const char *pShaderName ) = 0;

    // Can't be const because the material might have to precache itself.
    virtual int				GetNumPasses( void ) = 0;

    // Can't be const because the material might have to precache itself.
    virtual int				GetTextureMemoryBytes( void ) = 0;

    // Meant to be used with materials created using CreateMaterial
    // It updates the materials to reflect the current values stored in the material vars
    virtual void			Refresh() = 0;

    // GR - returns true is material uses lightmap alpha for blending
    virtual bool			NeedsLightmapBlendAlpha( void ) = 0;

    // returns true if the shader doesn't do lighting itself and requires
    // the data that is sent to it to be prelighted
    virtual bool			NeedsSoftwareLighting( void ) = 0;

    // Gets at the shader parameters
    virtual int				ShaderParamCount() const = 0;
    virtual IMaterialVar	**GetShaderParams( void ) = 0;

    // Returns true if this is the error material you get back from IMaterialSystem::FindMaterial if
    // the material can't be found.
    virtual bool			IsErrorMaterial() const = 0;

    virtual void			Unused() = 0;

    // Gets the current alpha modulation
    virtual float			GetAlphaModulation() = 0;
    virtual void			GetColorModulation( float *r , float *g , float *b ) = 0;

    // Is this translucent given a particular alpha modulation?
    virtual bool			IsTranslucentUnderModulation( float fAlphaModulation = 1.0f ) const = 0;

    // fast find that stores the index of the found var in the string table in local cache
    virtual IMaterialVar *	FindVarFast( char const *pVarName , unsigned int *pToken ) = 0;

    // Sets new VMT shader parameters for the material
    virtual void			SetShaderAndParams( KeyValues *pKeyValues ) = 0;
    virtual const char *	GetShaderName() const = 0;

    virtual void			DeleteIfUnreferenced() = 0;

    virtual bool			IsSpriteCard() = 0;

    virtual void			CallBindProxy( void *proxyData ) = 0;

    virtual void			RefreshPreservingMaterialVars() = 0;

    virtual bool			WasReloadedFromWhitelist() = 0;

    virtual bool			SetTempExcluded( bool bSet , int nExcludedDimensionLimit ) = 0;

    virtual int				GetReferenceCount() const = 0;
};

inline bool IsErrorMaterial( IMaterial *pMat )
{
    return !pMat || pMat->IsErrorMaterial();
}

//
// Vertex stream specifications
//

struct VertexStreamSpec_t
{
    enum StreamSpec_t
    {
        STREAM_DEFAULT ,		// stream 0: with position, normal, etc.
        STREAM_SPECULAR1 ,	// stream 1: following specular vhv lighting
        STREAM_FLEXDELTA ,	// stream 2: flex deltas
        STREAM_MORPH ,		// stream 3: morph
        STREAM_UNIQUE_A ,	// unique stream 4
        STREAM_UNIQUE_B ,	// unique stream 5
        STREAM_UNIQUE_C ,	// unique stream 6
        STREAM_UNIQUE_D ,	// unique stream 7
        STREAM_SUBDQUADS ,	// stream 8: quad buffer for subd's
    };

    enum
    {
        MAX_UNIQUE_STREAMS = 4
    };

    VertexFormatFlags_t iVertexDataElement;
    StreamSpec_t iStreamSpec;
};

inline VertexStreamSpec_t * FindVertexStreamSpec( VertexFormat_t iElement , VertexStreamSpec_t *arrVertexStreamSpec )
{
    for ( ; arrVertexStreamSpec &&
          arrVertexStreamSpec->iVertexDataElement != VERTEX_FORMAT_UNKNOWN;
          ++arrVertexStreamSpec )
    {
        if ( arrVertexStreamSpec->iVertexDataElement == iElement )
            return arrVertexStreamSpec;
    }
    return NULL;
}

class IMaterialSystem : public IAppSystem
{
public:

    //Placeholder for API revision
    //virtual bool Connect( CreateInterfaceFn factory ) = 0;
    //virtual void Disconnect() = 0;
    //virtual void *QueryInterface( const char *pInterfaceName ) = 0;
    //virtual InitReturnVal_t Init() = 0;
    //virtual void Shutdown() = 0;

    // Call this to initialize the material system
    // returns a method to create interfaces in the shader dll
    virtual CreateInterfaceFn	Init( char const* pShaderAPIDLL ,
                                      IMaterialProxyFactory *pMaterialProxyFactory ,
                                      CreateInterfaceFn fileSystemFactory ,
                                      CreateInterfaceFn cvarFactory = NULL ) = 0;
    // Call this to set an explicit shader version to use
    // Must be called before Init().
    virtual void				SetShaderAPI( char const *pShaderAPIDLL ) = 0;
    // Must be called before Init(), if you're going to call it at all...
    virtual void				SetAdapter( int nAdapter , int nFlags ) = 0;
    // Call this when the mod has been set up, which may occur after init
    // At this point, the game + gamebin paths have been set up
    virtual void				ModInit() = 0;
    virtual void				ModShutdown() = 0;
    virtual void				SetThreadMode( MaterialThreadMode_t mode , int nServiceThread = -1 ) = 0;
    virtual MaterialThreadMode_t GetThreadMode() = 0;
    virtual bool				IsRenderThreadSafe() = 0;
    virtual void				ExecuteQueued() = 0;
    virtual void				OnDebugEvent( const char *pEvent ) = 0;
    virtual IMaterialSystemHardwareConfig *GetHardwareConfig( const char *pVersion , int *returnCode ) = 0;
    // Call this before rendering each frame with the current config for the material system.
    // Will do whatever is necessary to get the material system into the correct state
    // upon configuration change. .doesn't much else otherwise.
    virtual bool				UpdateConfig( bool bForceUpdate ) = 0;
    // Force this to be the config; update all material system convars to match the state return true if lightmaps need to be redownloaded
    virtual bool				OverrideConfig( const MaterialSystem_Config_t &config , bool bForceUpdate ) = 0;
    // Get the current config for this video card (as last set by UpdateConfig)
    virtual const MaterialSystem_Config_t &GetCurrentConfigForVideoCard() const = 0;
    // Gets *recommended* configuration information associated with the display card,
    // given a particular dx level to run under.
    // Use dxlevel 0 to use the recommended dx level.
    // The function returns false if an invalid dxlevel was specified
    virtual bool				GetRecommendedConfigurationInfo( int nDXLevel , KeyValues * pKeyValues ) = 0;
    // Gets the number of adapters...
    virtual int					GetDisplayAdapterCount() const = 0;
    // Returns the current adapter in use
    virtual int					GetCurrentAdapter() const = 0;
    // Returns info about each adapter
    virtual void				GetDisplayAdapterInfo( int adapter , MaterialAdapterInfo_t& info ) const = 0;
    // Returns the number of modes
    virtual int					GetModeCount( int adapter ) const = 0;
    // Returns mode information
    virtual void				GetModeInfo( int adapter , int mode , MaterialVideoMode_t& info ) const = 0;
    virtual void				AddModeChangeCallBack( ModeChangeCallbackFunc_t func ) = 0;
    // Returns the mode info for the current display device
    virtual void				GetDisplayMode( MaterialVideoMode_t& mode ) const = 0; //21
                                                                                       // Sets the mode
    virtual bool				SetMode( void* hwnd , const MaterialSystem_Config_t &config ) = 0;
    virtual bool				SupportsMSAAMode( int nMSAAMode ) = 0;
    // FIXME: REMOVE! Get video card identitier
    virtual const MaterialSystemHardwareIdentifier_t &GetVideoCardIdentifier( void ) const = 0;
    // Use this to spew information about the 3D layer
    virtual void				SpewDriverInfo() const = 0;
    // Get the image format of the back buffer. . useful when creating render targets, etc.
    virtual void				GetBackBufferDimensions( int &width , int &height ) const = 0;
    virtual ImageFormat			GetBackBufferFormat() const = 0;
    virtual const AspectRatioInfo_t &GetAspectRatioInfo() const = 0;
    virtual bool				SupportsHDRMode( HDRType_t nHDRModede ) = 0;
    // Creates/ destroys a child window
    virtual bool				AddView( void* hwnd ) = 0;
    virtual void				RemoveView( void* hwnd ) = 0; // 31
                                                              // Sets the view
    virtual void				SetView( void* hwnd ) = 0;
    virtual void				BeginFrame( float frameTime ) = 0;
    virtual void				EndFrame() = 0;
    virtual void				Flush( bool flushHardware = false ) = 0;
    virtual unsigned int		GetCurrentFrameCount() = 0;
    /// FIXME: This stuff needs to be cleaned up and abstracted.
    // Stuff that gets exported to the launcher through the engine
    virtual void				SwapBuffers() = 0;
    // Flushes managed textures from the texture cacher
    virtual void				EvictManagedResources() = 0;
    virtual void				ReleaseResources( void ) = 0;
    virtual void				ReacquireResources( void ) = 0;
    // Installs a function to be called when we need to release vertex buffers + textures
    virtual void				AddReleaseFunc( MaterialBufferReleaseFunc_t func ) = 0; // 41
    virtual void				RemoveReleaseFunc( MaterialBufferReleaseFunc_t func ) = 0;
    // Installs a function to be called when we need to restore vertex buffers
    virtual void				AddRestoreFunc( MaterialBufferRestoreFunc_t func ) = 0;
    virtual void				RemoveRestoreFunc( MaterialBufferRestoreFunc_t func ) = 0;
    // Installs a function to be called when we need to delete objects at the end of the render frame
    virtual void				AddEndFrameCleanupFunc( EndFrameCleanupFunc_t func ) = 0;
    virtual void				RemoveEndFrameCleanupFunc( EndFrameCleanupFunc_t func ) = 0;
    virtual void				OnLevelShutdown() = 0;
    virtual bool				AddOnLevelShutdownFunc( OnLevelShutdownFunc_t func , void *pUserData ) = 0;
    virtual bool				RemoveOnLevelShutdownFunc( OnLevelShutdownFunc_t func , void *pUserData ) = 0;
    virtual void				OnLevelLoadingComplete() = 0;
    // Release temporary HW memory...
    virtual void				ResetTempHWMemory( bool bExitingLevel = false ) = 0; // 51
                                                                                     // For dealing with device lost in cases where SwapBuffers isn't called all the time (Hammer)
    virtual void				HandleDeviceLost() = 0;
    // Used to iterate over all shaders for editing purposes
    // GetShaders returns the number of shaders it actually found
    virtual int					ShaderCount() const = 0;
    virtual int					GetShaders( int nFirstShader , int nMaxCount , Pointer *ppShaderList ) const = 0;
    // Returns shader flag names for editors to be able to edit them
    virtual int					ShaderFlagCount() const = 0;
    virtual const char *		ShaderFlagName( int nIndex ) const = 0;
    // Gets the actual shader fallback for a particular shader
    virtual void				GetShaderFallback( const char *pShaderName , char *pFallbackShader , int nFallbackLength ) = 0;
    virtual IMaterialProxyFactory *GetMaterialProxyFactory() = 0;
    // Sets the material proxy factory. Calling this causes all materials to be uncached.
    virtual void				SetMaterialProxyFactory( IMaterialProxyFactory* pFactory ) = 0;
    // Used to enable editor materials. Must be called before Init.
    virtual void				EnableEditorMaterials() = 0;
    virtual void                EnableGBuffers() = 0; // 61
                                                      // Force it to ignore Draw calls.
    virtual void				SetInStubMode( bool bInStubMode ) = 0;
    // Debug support
    virtual void				DebugPrintUsedMaterials( const char *pSearchSubString , bool bVerbose ) = 0;
    virtual void				DebugPrintUsedTextures( void ) = 0;
    virtual void				ToggleSuppressMaterial( char const* pMaterialName ) = 0;
    virtual void				ToggleDebugMaterial( char const* pMaterialName ) = 0;

    //---------------------------------------------------------
    // Misc features
    //---------------------------------------------------------
    //returns whether fast clipping is being used or not - needed to be exposed for better per-object clip behavior
    virtual bool				UsingFastClipping( void ) = 0;

    virtual int					StencilBufferBits( void ) = 0; //number of bits per pixel in the stencil buffer

                                                               //---------------------------------------------------------
                                                               // Material and texture management
                                                               //---------------------------------------------------------

                                                               // uncache all materials. .  good for forcing reload of materials.
    virtual void				UncacheAllMaterials() = 0;

    // Remove any materials from memory that aren't in use as determined
    // by the IMaterial's reference count.
    virtual void				UncacheUnusedMaterials( bool bRecomputeStateSnapshots = false ) = 0;

    // Load any materials into memory that are to be used as determined
    // by the IMaterial's reference count.
    virtual void				CacheUsedMaterials() = 0; // 71

                                                          // Force all textures to be reloaded from disk.
    virtual void				ReloadTextures() = 0;

    // Reloads materials
    virtual void				ReloadMaterials( const char *pSubString = NULL ) = 0;

    // Create a procedural material. The keyvalues looks like a VMT file
    virtual IMaterial *			CreateMaterial( const char *pMaterialName , KeyValues *pVMTKeyValues ) = 0;

    // Find a material by name.
    // The name of a material is a full path to
    // the vmt file starting from "hl2/materials" (or equivalent) without
    // a file extension.
    // eg. "dev/dev_bumptest" refers to somethign similar to:
    // "d:/hl2/hl2/materials/dev/dev_bumptest.vmt"
    // Most of the texture groups for pTextureGroupName are listed in texture_group_names.h.
    // Note: if the material can't be found, this returns a checkerboard material. You can
    // find out if you have that material by calling IMaterial::IsErrorMaterial().
    // (Or use the global IsErrorMaterial function, which checks if it's null too).
    // 83rd virtual
    virtual IMaterial*			FindMaterial( char const* pMaterialName , const char *pTextureGroupName , bool complain = true , const char *pComplainPrefix = NULL ) = 0;

    virtual void				LoadKeyValuesFromVMTFile( KeyValues& values , const char* name , bool somebool ) const = 0;
    //---------------------------------
    // This is the interface for knowing what materials are available
    // is to use the following functions to get a list of materials.  The
    // material names will have the full path to the material, and that is the
    // only way that the directory structure of the materials will be seen through this
    // interface.
    // NOTE:  This is mostly for worldcraft to get a list of materials to put
    // in the "texture" browser.in Worldcraft
    virtual MaterialHandle_t	FirstMaterial() const = 0;

    // returns InvalidMaterial if there isn't another material.
    // WARNING: you must call GetNextMaterial until it returns NULL,
    // otherwise there will be a memory leak.
    virtual MaterialHandle_t	NextMaterial( MaterialHandle_t h ) const = 0;

    // This is the invalid material
    virtual MaterialHandle_t	InvalidMaterial() const = 0;

    // Returns a particular material
    virtual IMaterial*			GetMaterial( MaterialHandle_t h ) const = 0;

    // Get the total number of materials in the system.  These aren't just the used
    // materials, but the complete collection.
    virtual int					GetNumMaterials() const = 0;

    //---------------------------------

    virtual ITexture *			FindTexture( char const* pTextureName , const char *pTextureGroupName , bool complain = true , bool bSomething = false ) = 0;

    // Checks to see if a particular texture is loaded
    virtual bool				IsTextureLoaded( char const* pTextureName ) const = 0; // 90

                                                                                       // Creates a procedural texture
    virtual ITexture *			CreateProceduralTexture( const char	*pTextureName ,
                                                         const char *pTextureGroupName ,
                                                         int w ,
                                                         int h ,
                                                         ImageFormat fmt ,
                                                         int nFlags ) = 0;

    //
    // Render targets
    //
    virtual void				BeginRenderTargetAllocation() = 0;
    virtual void				EndRenderTargetAllocation() = 0; // Simulate an Alt-Tab in here, which causes a release/restore of all resources

                                                                 // Creates a render target
                                                                 // If depth == true, a depth buffer is also allocated. If not, then
                                                                 // the screen's depth buffer is used.
                                                                 // Creates a texture for use as a render target
    virtual ITexture *			CreateRenderTargetTexture( int w ,
                                                           int h ,
                                                           RenderTargetSizeMode_t sizeMode ,	// Controls how size is generated (and regenerated on video mode change).
                                                           ImageFormat	format ,
                                                           MaterialRenderTargetDepth_t depth = MATERIAL_RT_DEPTH_SHARED ) = 0;

    virtual ITexture *			CreateNamedRenderTargetTextureEx( const char *pRTName ,				// Pass in NULL here for an unnamed render target.
                                                                  int w ,
                                                                  int h ,
                                                                  RenderTargetSizeMode_t sizeMode ,	// Controls how size is generated (and regenerated on video mode change).
                                                                  ImageFormat format ,
                                                                  MaterialRenderTargetDepth_t depth = MATERIAL_RT_DEPTH_SHARED ,
                                                                  unsigned int textureFlags = TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT ,
                                                                  unsigned int renderTargetFlags = 0 ) = 0;

    virtual ITexture *			CreateNamedRenderTargetTexture( const char *pRTName ,
                                                                int w ,
                                                                int h ,
                                                                RenderTargetSizeMode_t sizeMode ,	// Controls how size is generated (and regenerated on video mode change).
                                                                ImageFormat format ,
                                                                MaterialRenderTargetDepth_t depth = MATERIAL_RT_DEPTH_SHARED ,
                                                                bool bClampTexCoords = true ,
                                                                bool bAutoMipMap = false ) = 0;

    // Must be called between the above Begin-End calls!
    virtual ITexture *			CreateNamedRenderTargetTextureEx2( const char *pRTName ,				// Pass in NULL here for an unnamed render target.
                                                                   int w ,
                                                                   int h ,
                                                                   RenderTargetSizeMode_t sizeMode ,	// Controls how size is generated (and regenerated on video mode change).
                                                                   ImageFormat format ,
                                                                   MaterialRenderTargetDepth_t depth = MATERIAL_RT_DEPTH_SHARED ,
                                                                   unsigned int textureFlags = TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT ,
                                                                   unsigned int renderTargetFlags = 0 ) = 0;

    // -----------------------------------------------------------
    // Lightmaps
    // -----------------------------------------------------------

    // To allocate lightmaps, sort the whole world by material twice.
    // The first time through, call AllocateLightmap for every surface.
    // that has a lightmap.
    // The second time through, call AllocateWhiteLightmap for every
    // surface that expects to use shaders that expect lightmaps.
    virtual void				BeginLightmapAllocation() = 0;
    virtual void				EndLightmapAllocation() = 0;

    virtual void				CleanupLightmaps() = 0; // 100

                                                        // returns the sorting id for this surface
    virtual int 				AllocateLightmap( int width , int height ,
                                                  int offsetIntoLightmapPage[ 2 ] ,
                                                  IMaterial *pMaterial ) = 0;
    // returns the sorting id for this surface
    virtual int					AllocateWhiteLightmap( IMaterial *pMaterial ) = 0;

    // lightmaps are in linear color space
    // lightmapPageID is returned by GetLightmapPageIDForSortID
    // lightmapSize and offsetIntoLightmapPage are returned by AllocateLightmap.
    // You should never call UpdateLightmap for a lightmap allocated through
    // AllocateWhiteLightmap.
    virtual void				UpdateLightmap( int lightmapPageID , int lightmapSize[ 2 ] ,
                                                int offsetIntoLightmapPage[ 2 ] ,
                                                float *pFloatImage , float *pFloatImageBump1 ,
                                                float *pFloatImageBump2 , float *pFloatImageBump3 ) = 0;
    virtual int					GetNumSortIDs() = 0;
    virtual void				GetSortInfo( MaterialSystem_SortInfo_t *sortInfoArray ) = 0;
    // Read the page size of an existing lightmap by sort id (returned from AllocateLightmap())
    virtual void				GetLightmapPageSize( int lightmap , int *width , int *height ) const = 0;
    virtual void				ResetMaterialLightmapPageInfo() = 0;
    virtual bool				IsStereoSupported() = 0;
    virtual bool				IsStereoActiveThisFrame() const = 0;
    virtual void				NVStereoUpdate() = 0;
    virtual void				ClearBuffers( bool bClearColor , bool bClearDepth , bool bClearStencil = false ) = 0;
    virtual void				SpinPresent( unsigned int nFrames ) = 0;

    // -----------------------------------------------------------
    // Access the render contexts
    // -----------------------------------------------------------

    //IMatRenderContext* GetContext()
    //{
    //	typedef IMatRenderContext*(__thiscall* OriginalFn)(PVOID);
    //	return getvfunc<OriginalFn>(this, 114)(this);
    //}

    virtual IMatRenderContext*	GetRenderContext() = 0; // 114
    virtual void				BeginUpdateLightmaps( void ) = 0;
    virtual void				EndUpdateLightmaps( void ) = 0;
    // -----------------------------------------------------------
    // Methods to force the material system into non-threaded, non-queued mode
    // -----------------------------------------------------------
    virtual MaterialLock_t		Lock() = 0;
    virtual void				Unlock( MaterialLock_t ) = 0;
    // Create a custom render context. Cannot be used to create MATERIAL_HARDWARE_CONTEXT
    virtual IMatRenderContext *CreateRenderContext( MaterialContextType_t type ) = 0;
    // Set a specified render context to be the global context for the thread. Returns the prior context.
    virtual IMatRenderContext *SetRenderContext( IMatRenderContext * ) = 0;
    virtual bool				SupportsCSAAMode( int nNumSamples , int nQualityLevel ) = 0;
    virtual void				RemoveModeChangeCallBack( ModeChangeCallbackFunc_t func ) = 0;
    // Finds or create a procedural material.
    virtual IMaterial *			FindProceduralMaterial( const char *pMaterialName , const char *pTextureGroupName , KeyValues *pVMTKeyValues ) = 0;
    virtual void				AddTextureAlias( const char *pAlias , const char *pRealName ) = 0;
    virtual void				RemoveTextureAlias( const char *pAlias ) = 0;
    // returns a lightmap page ID for this allocation, -1 if none available
    // frameID is a number that should be changed every frame to prevent locking any textures that are
    // being used to draw in the previous frame
    virtual int					AllocateDynamicLightmap( int lightmapSize[ 2 ] , int *pOutOffsetIntoPage , int frameID ) = 0;
    virtual void				SetExcludedTextures( const char *pScriptName , bool bUsingWeaponModelCache ) = 0;
    virtual void				UpdateExcludedTextures( void ) = 0;
    virtual bool				IsInFrame() const = 0;
    virtual void				CompactMemory() = 0;
    virtual void				GetGPUMemoryStats( GPUMemoryStats &stats ) = 0;
    // For sv_pure mode. The filesystem figures out which files the client needs to reload to be "pure" ala the server's preferences.
    virtual void				ReloadFilesInList( IFileList *pFilesToReload ) = 0;
    // Get information about the texture for texture management tools
    virtual bool				GetTextureInformation( char const *szTextureName , MaterialTextureInfo_t &info ) const = 0;
    // call this once the render targets are allocated permanently at the beginning of the game
    virtual void				FinishRenderTargetAllocation( void ) = 0;
    virtual void				ReEnableRenderTargetAllocation_IRealizeIfICallThisAllTexturesWillBeUnloadedAndLoadTimeWillSufferHorribly( void ) = 0;
    virtual	bool				AllowThreading( bool bAllow , int nServiceThread ) = 0;
    virtual bool				GetRecommendedVideoConfig( KeyValues *pKeyValues ) = 0;
    virtual IClientMaterialSystem*	GetClientMaterialSystemInterface() = 0;
    virtual bool				CanDownloadTextures() const = 0;
    virtual int					GetNumLightmapPages() const = 0;
    virtual IPaintMapTextureManager *RegisterPaintMapDataManager( IPaintMapDataManager *pDataManager ) = 0; //You supply an interface we can query for bits, it gives back an interface you can use to drive updates
    virtual void				BeginUpdatePaintmaps() = 0;
    virtual void				EndUpdatePaintmaps() = 0;
    virtual void				UpdatePaintmap( int paintmap , unsigned char *pPaintData , int numRects , Rect_t *pRects ) = 0;
    virtual ITexture			*CreateNamedMultiRenderTargetTexture( const char *pRTName , int w , int h , RenderTargetSizeMode_t sizeMode ,
                                                                      ImageFormat format , MaterialRenderTargetDepth_t depth , unsigned int textureFlags , unsigned int renderTargetFlags ) = 0;
    virtual void				RefreshFrontBufferNonInteractive() = 0;
    virtual uint32_t			GetFrameTimestamps( ApplicationPerformanceCountersInfo_t &apci , ApplicationInstantCountersInfo_t &aici ) = 0;
    virtual void				DoStartupShaderPreloading() = 0;
    virtual void				AddEndFramePriorToNextContextFunc( EndFramePriorToNextContextFunc_t func ) = 0;
    virtual void				RemoveEndFramePriorToNextContextFunc( EndFramePriorToNextContextFunc_t func ) = 0;
};

class IMaterial;
class VMatrix;
class ITexture;

#define MAKE_MATERIALVAR_FOURCC(ch0, ch1, ch2, ch3)             \
		((unsigned long)(ch0) | ((unsigned long)(ch1) << 8) |   \
		((unsigned long)(ch2) << 16) | ((unsigned long)(ch3) << 24 ))

// This fourcc is reserved.
#define FOURCC_UNKNOWN	MAKE_MATERIALVAR_FOURCC('U','N','K','N')

//-----------------------------------------------------------------------------
// Various material var types
//-----------------------------------------------------------------------------
enum MaterialVarType_t
{
    MATERIAL_VAR_TYPE_FLOAT = 0 ,
    MATERIAL_VAR_TYPE_STRING ,
    MATERIAL_VAR_TYPE_VECTOR ,
    MATERIAL_VAR_TYPE_TEXTURE ,
    MATERIAL_VAR_TYPE_INT ,
    MATERIAL_VAR_TYPE_FOURCC ,
    MATERIAL_VAR_TYPE_UNDEFINED ,
    MATERIAL_VAR_TYPE_MATRIX ,
    MATERIAL_VAR_TYPE_MATERIAL ,
};

typedef unsigned short MaterialVarSym_t;

class IMaterialVar
{
public:
    typedef unsigned long FourCC;

protected:
    // base data and accessors
    char* m_pStringVal;
    int m_intVal;
    Vector4D m_VecVal;

    // member data. total = 4 bytes
    uint8 m_Type : 4;
    uint8 m_nNumVectorComps : 3;
    uint8 m_bFakeMaterialVar : 1;
    uint8 m_nTempIndex;
    CUtlSymbol m_Name;

public:
    // class factory methods
    static IMaterialVar* Create( IMaterial* pMaterial , char const* pKey , VMatrix const& matrix );
    static IMaterialVar* Create( IMaterial* pMaterial , char const* pKey , char const* pVal );
    static IMaterialVar* Create( IMaterial* pMaterial , char const* pKey , float* pVal , int numcomps );
    static IMaterialVar* Create( IMaterial* pMaterial , char const* pKey , float val );
    static IMaterialVar* Create( IMaterial* pMaterial , char const* pKey , int val );
    static IMaterialVar* Create( IMaterial* pMaterial , char const* pKey );
    static void Destroy( IMaterialVar* pVar );
#undef GetSymbol
    static MaterialVarSym_t	GetSymbol( char const* pName );
    static MaterialVarSym_t	FindSymbol( char const* pName );
    static bool SymbolMatches( char const* pName , MaterialVarSym_t symbol );
    static void DeleteUnreferencedTextures( bool enable );

    virtual ITexture		*GetTextureValue( void ) = 0;

    virtual char const *	GetName( void ) const = 0;
    virtual MaterialVarSym_t	GetNameAsSymbol() const = 0;

    virtual void pad() = 0;

    virtual void			SetFloatValue( float val ) = 0;

    virtual void			SetIntValue( int val ) = 0;

    virtual void			SetStringValue( char const *val ) = 0;
    virtual char const *	GetStringValue( void ) const = 0;

    // Use FourCC values to pass app-defined data structures between
    // the proxy and the shader. The shader should ignore the data if
    // its FourCC type not correct.
    virtual void			SetFourCCValue( FourCC type , void *pData ) = 0;
    virtual void			GetFourCCValue( FourCC *type , void **ppData ) = 0;

    // Vec (dim 2-4)
    virtual void			SetVecValue( float const* val , int numcomps ) = 0;
    virtual void			SetVecValue( float x , float y ) = 0;
    virtual void			SetVecValue( float x , float y , float z ) = 0;
    virtual void			SetVecValue( float x , float y , float z , float w ) = 0;
    virtual void			GetLinearVecValue( float *val , int numcomps ) const = 0;

    // revisit: is this a good interface for textures?
    virtual void			SetTextureValue( ITexture * ) = 0;

    virtual IMaterial *		GetMaterialValue( void ) = 0;
    virtual void			SetMaterialValue( IMaterial * ) = 0;

    virtual bool			IsDefined() const = 0;
    virtual void			SetUndefined() = 0;

    // Matrix
    virtual void			SetMatrixValue( VMatrix const& matrix ) = 0;
    virtual const VMatrix  &GetMatrixValue() = 0;
    virtual bool			MatrixIsIdentity() const = 0;

    // Copy....
    virtual void			CopyFrom( IMaterialVar *pMaterialVar ) = 0;

    virtual void			SetValueAutodetectType( char const *val ) = 0;

    virtual IMaterial *		GetOwningMaterial() = 0;

    //set just 1 component
    virtual void			SetVecComponentValue( float fVal , int nComponent ) = 0;

protected:
    virtual int				GetIntValueInternal( void ) const = 0;
    virtual float			GetFloatValueInternal( void ) const = 0;
    virtual float const*	GetVecValueInternal() const = 0;
    virtual void			GetVecValueInternal( float *val , int numcomps ) const = 0;
    virtual int				VectorSizeInternal() const = 0;

public:
    FORCEINLINE MaterialVarType_t GetType( void ) const
    {
        return ( MaterialVarType_t ) m_Type;
    }

    FORCEINLINE bool IsTexture() const
    {
        return m_Type == MATERIAL_VAR_TYPE_TEXTURE;
    }

    FORCEINLINE operator ITexture*( )
    {
        return GetTextureValue();
    }

    // NOTE: Fast methods should only be called in thread-safe situations
    FORCEINLINE int GetIntValueFast( void ) const
    {
        // Set methods for float and vector update this
        return m_intVal;
    }

    FORCEINLINE float GetFloatValueFast( void ) const
    {
        return m_VecVal[ 0 ];
    }

    FORCEINLINE float const* GetVecValueFast() const
    {
        return m_VecVal.Base();
    }

    FORCEINLINE void GetVecValueFast( float *val , int numcomps ) const
    {
        for ( int i = 0; i < numcomps; i++ )
        {
            val[ i ] = m_VecVal[ i ];
        }
    }

    FORCEINLINE int VectorSizeFast() const
    {
        return m_nNumVectorComps;
    }

#ifdef FAST_MATERIALVAR_ACCESS
    FORCEINLINE int GetIntValue( void ) const
    {
        return GetIntValueFast();
    }

    FORCEINLINE float GetFloatValue( void ) const
    {
        return GetFloatValueFast();
    }

    FORCEINLINE float const* GetVecValue() const
    {
        return GetVecValueFast();
    }

    FORCEINLINE void GetVecValue( float *val , int numcomps ) const
    {
        GetVecValueFast( val , numcomps );
    }

    FORCEINLINE int VectorSize() const
    {
        return VectorSizeFast();
    }
#else // !FAST_MATERIALVAR_ACCESS
    FORCEINLINE int GetIntValue( void ) const
    {
        return GetIntValueInternal();
    }

    FORCEINLINE float GetFloatValue( void ) const
    {
        return GetFloatValueInternal();
    }

    FORCEINLINE float const* GetVecValue() const
    {
        return GetVecValueInternal();
    }

    FORCEINLINE void GetVecValue( float *val , int numcomps ) const
    {
        return GetVecValueInternal( val , numcomps );
    }

    FORCEINLINE int VectorSize() const
    {
        return VectorSizeInternal();
    }
#endif

private:
    FORCEINLINE void SetTempIndex( uint8 nIndex )
    {
        m_nTempIndex = nIndex;
    }

    friend void EnableThreadedMaterialVarAccess( bool bEnable , IMaterialVar **ppParams , int nVarCount );
};

class IVTFTexture;
class ITexture;
struct Rect_t;

//-----------------------------------------------------------------------------
// This will get called on procedural textures to re-fill the textures
// with the appropriate bit pattern. Calling Download() will also
// cause this interface to be called. It will also be called upon
// mode switch, or on other occasions where the bits are discarded.
//-----------------------------------------------------------------------------
class ITextureRegenerator
{
public:
    // This will be called when the texture bits need to be regenerated.
    // Use the VTFTexture interface, which has been set up with the
    // appropriate texture size + format
    // The rect specifies which part of the texture needs to be updated
    // You can choose to update all of the bits if you prefer
    virtual void RegenerateTextureBits( ITexture *pTexture , IVTFTexture *pVTFTexture , Rect_t *pRect ) = 0;

    // This will be called when the regenerator needs to be deleted
    // which will happen when the texture is destroyed
    virtual void Release() = 0;
};

class ITexture
{
public:
    // Various texture polling methods
    virtual const char *GetName( void ) const = 0;
    virtual int GetMappingWidth() const = 0;
    virtual int GetMappingHeight() const = 0;
    virtual int GetActualWidth() const = 0;
    virtual int GetActualHeight() const = 0;
    virtual int GetNumAnimationFrames() const = 0;
    virtual bool IsTranslucent() const = 0;
    virtual bool IsMipmapped() const = 0;

    virtual void GetLowResColorSample( float s , float t , float *color ) const = 0;

    // Gets texture resource data of the specified type.
    // Params:
    //		eDataType		type of resource to retrieve.
    //		pnumBytes		on return is the number of bytes available in the read-only data buffer or is undefined
    // Returns:
    //		pointer to the resource data, or NULL
    virtual void *GetResourceData( uint32 eDataType , size_t *pNumBytes ) const = 0;

    // Methods associated with reference count
    virtual void IncrementReferenceCount( void ) = 0;
    virtual void DecrementReferenceCount( void ) = 0;

    inline void AddRef()
    {
        IncrementReferenceCount();
    }
    inline void Release()
    {
        DecrementReferenceCount();
    }

    // Used to modify the texture bits (procedural textures only)
    virtual void SetTextureRegenerator( ITextureRegenerator *pTextureRegen , bool releaseExisting = true ) = 0;

    // Reconstruct the texture bits in HW memory

    // If rect is not specified, reconstruct all bits, otherwise just
    // reconstruct a subrect.
    virtual void Download( Rect_t *pRect = 0 ) = 0;

    // Uses for stats. . .get the approximate size of the texture in it's current format.
    virtual int GetApproximateVidMemBytes( void ) const = 0;

    // Returns true if the texture data couldn't be loaded.
    virtual bool IsError() const = 0;

    // NOTE: Stuff after this is added after shipping HL2.

    // For volume textures
    virtual bool IsVolumeTexture() const = 0;
    virtual int GetMappingDepth() const = 0;
    virtual int GetActualDepth() const = 0;

    virtual ImageFormat GetImageFormat() const = 0;

    // Various information about the texture
    virtual bool IsRenderTarget() const = 0;
    virtual bool IsCubeMap() const = 0;
    virtual bool IsNormalMap() const = 0;
    virtual bool IsProcedural() const = 0;

    virtual void DeleteIfUnreferenced() = 0;

#if defined( _X360 )
    virtual bool ClearTexture( int r , int g , int b , int a ) = 0;
    virtual bool CreateRenderTargetSurface( int width , int height , ImageFormat format , bool bSameAsTexture , RTMultiSampleCount360_t multiSampleCount = RT_MULTISAMPLE_NONE ) = 0;
#endif

    // swap everything except the name with another texture
    virtual void SwapContents( ITexture *pOther ) = 0;

    // Retrieve the vtf flags mask
    virtual unsigned int GetFlags( void ) const = 0;

    // Force LOD override (automatically downloads the texture)
    virtual void ForceLODOverride( int iNumLodsOverrideUpOrDown ) = 0;

    // Force exclude override (automatically downloads the texture)
    virtual void ForceExcludeOverride( int iExcludeOverride ) = 0;
};

inline bool IsErrorTexture( ITexture *pTex )
{
    return !pTex || pTex->IsError();
}

#endif