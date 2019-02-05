#ifndef MODELRENDER
#define MODELRENDER
#pragma once

enum DrawModelFlags_t
{
    STUDIO_NONE = 0x00000000 ,
    STUDIO_RENDER = 0x00000001 ,
    STUDIO_VIEWXFORMATTACHMENTS = 0x00000002 ,
    STUDIO_DRAWTRANSLUCENTSUBMODELS = 0x00000004 ,
    STUDIO_TWOPASS = 0x00000008 ,
    STUDIO_STATIC_LIGHTING = 0x00000010 ,
    STUDIO_WIREFRAME = 0x00000020 ,
    STUDIO_ITEM_BLINK = 0x00000040 ,
    STUDIO_NOSHADOWS = 0x00000080 ,
    STUDIO_WIREFRAME_VCOLLIDE = 0x00000100 ,
    STUDIO_NOLIGHTING_OR_CUBEMAP = 0x00000200 ,
    STUDIO_SKIP_FLEXES = 0x00000400 ,
    STUDIO_DONOTMODIFYSTENCILSTATE = 0x00000800 ,
    // Not a studio flag, but used to flag model as a non-sorting brush model
    STUDIO_TRANSPARENCY = 0x80000000 ,
    // Not a studio flag, but used to flag model as using shadow depth material override
    STUDIO_SHADOWDEPTHTEXTURE = 0x40000000 ,
    // Not a studio flag, but used to flag model as doing custom rendering into shadow texture
    STUDIO_SHADOWTEXTURE = 0x20000000 ,
    STUDIO_SKIP_DECALS = 0x10000000 ,
};

DECLARE_POINTER_HANDLE( StudioDecalHandle_t );
#define STUDIORENDER_DECAL_INVALID  ( (StudioDecalHandle_t)0 )

//-----------------------------------------------------------------------------
// forward declarations
//-----------------------------------------------------------------------------
struct mstudioanimdesc_t;
struct mstudioseqdesc_t;
struct model_t;
class IClientRenderable;
class Vector;
class IMaterial;
class CStudioHdr;
struct MaterialLightingState_t;
class IMesh;
class IMorph;
typedef unsigned short ModelInstanceHandle_t;
typedef void* LightCacheHandle_t;
struct ColorMeshInfo_t;
struct DataCacheHandle_t;

enum
{
    ADDDECAL_TO_ALL_LODS = -1
};

//-----------------------------------------------------------------------------
// What kind of material override is it?
//-----------------------------------------------------------------------------
enum OverrideType_t
{
    OVERRIDE_NORMAL = 0 ,
    OVERRIDE_BUILD_SHADOWS ,
    OVERRIDE_DEPTH_WRITE ,
};

namespace OptimizedModel
{
    struct StripHeader_t;
}

// ----------------------------------------------------------
// Runtime stuff
// ----------------------------------------------------------

struct studiomeshgroup_t
{
    IMesh			*m_pMesh;
    int				m_NumStrips;
    int				m_Flags;			// see studiomeshgroupflags_t
    OptimizedModel::StripHeader_t	*m_pStripData;
    unsigned short	*m_pGroupIndexToMeshIndex;
    int				m_NumVertices;
    int				*m_pUniqueFaces;	// for performance measurements
    unsigned short	*m_pIndices;
    unsigned short	*m_pTopologyIndices;
    bool			m_MeshNeedsRestore;
    short			m_ColorMeshID;
    IMorph			*m_pMorph;

    inline unsigned short MeshIndex( int i ) const
    {
        return m_pGroupIndexToMeshIndex[ m_pIndices[ i ] ];
    }
};

// studio model data
struct studiomeshdata_t
{
    int					m_NumGroup;
    studiomeshgroup_t*	m_pMeshGroup;
};

struct studioloddata_t
{
    // not needed - this is really the same as studiohwdata_t.m_NumStudioMeshes
    //int					m_NumMeshes;
    studiomeshdata_t	*m_pMeshData; // there are studiohwdata_t.m_NumStudioMeshes of these.
    float				m_SwitchPoint;
    // one of these for each lod since we can switch to simpler materials on lower lods.
    int					numMaterials;
    IMaterial			**ppMaterials; /* will have studiohdr_t.numtextures elements allocated */
                                       // hack - this needs to go away.
    int					*pMaterialFlags; /* will have studiohdr_t.numtextures elements allocated */

                                         // For decals on hardware morphing, we must actually do hardware skinning
                                         // For this to work, we have to hope that the total # of bones used by
                                         // hw flexed verts is < than the max possible for the dx level we're running under
    int					*m_pHWMorphDecalBoneRemap;
    int					m_nDecalBoneCount;
};

struct studiohwdata_t
{
    int					m_RootLOD;	// calced and clamped, nonzero for lod culling
    int					m_NumLODs;
    studioloddata_t		*m_pLODs;
    int					m_NumStudioMeshes;

    inline float LODMetric( float unitSphereSize ) const
    {
        return ( unitSphereSize != 0.0f ) ? ( 100.0f / unitSphereSize ) : 0.0f;
    }
    inline int GetLODForMetric( float lodMetric ) const
    {
        if ( !m_NumLODs )
            return 0;

        // shadow lod is specified on the last lod with a negative switch
        // never consider shadow lod as viable candidate
        int numLODs = ( m_pLODs[ m_NumLODs - 1 ].m_SwitchPoint < 0.0f ) ? m_NumLODs - 1 : m_NumLODs;

        for ( int i = m_RootLOD; i < numLODs - 1; i++ )
        {
            if ( m_pLODs[ i + 1 ].m_SwitchPoint > lodMetric )
                return i;
        }

        return numLODs - 1;
    }
};

//-----------------------------------------------------------------------------
// Model rendering state
//-----------------------------------------------------------------------------
struct DrawModelState_t
{
    studiohdr_t*			m_pStudioHdr;
    studiohwdata_t*			m_pStudioHWData;
    IClientRenderable*		m_pRenderable;
    Matrix3x4		        *m_pModelToWorld;
    StudioDecalHandle_t		m_decals;
    int						m_drawFlags;
    int						m_lod;
};

typedef unsigned short ModelInstanceHandle_t;

enum
{
    MODEL_INSTANCE_INVALID = ( ModelInstanceHandle_t ) ~0
};

struct ModelRenderInfo_t
{
    Vector origin;
    Angle angles;
    char pad[ 4 ];
    IClientRenderable *pRenderable;
    const model_t *pModel;
    Matrix3x4 *pModelToWorld;
    Matrix3x4 *pLightingOffset;
    Vector *pLightingOrigin;
    int flags;
    int entity_index;
    int skin;
    int body;
    int hitboxset;
    ModelInstanceHandle_t instance;

    ModelRenderInfo_t()
    {
        pModelToWorld = nullptr;
        pLightingOffset = nullptr;
        pLightingOrigin = nullptr;
    }
};

struct StaticPropRenderInfo_t
{
    const Matrix3x4		*pModelToWorld;
    const model_t			*pModel;
    IClientRenderable		*pRenderable;
    Vector					*pLightingOrigin;
    ModelInstanceHandle_t	instance;
    uint8					skin;
    uint8					alpha;
};

struct LightingQuery_t
{
    Vector m_LightingOrigin;
    ModelInstanceHandle_t m_InstanceHandle;
    bool m_bAmbientBoost;
};

struct StaticLightingQuery_t : public LightingQuery_t
{
    IClientRenderable *m_pRenderable;
};

// ---------------------------------------------------------------------------- -
// Light structure
//-----------------------------------------------------------------------------
enum LightType_t
{
    MATERIAL_LIGHT_DISABLE = 0 ,
    MATERIAL_LIGHT_POINT ,
    MATERIAL_LIGHT_DIRECTIONAL ,
    MATERIAL_LIGHT_SPOT ,
};

enum LightType_OptimizationFlags_t
{
    LIGHTTYPE_OPTIMIZATIONFLAGS_HAS_ATTENUATION0 = 1 ,
    LIGHTTYPE_OPTIMIZATIONFLAGS_HAS_ATTENUATION1 = 2 ,
    LIGHTTYPE_OPTIMIZATIONFLAGS_HAS_ATTENUATION2 = 4 ,
    LIGHTTYPE_OPTIMIZATIONFLAGS_DERIVED_VALUES_CALCED = 8 ,
};

struct LightDesc_t
{
    LightType_t m_Type;										//< MATERIAL_LIGHT_xxx
    Vector m_Color;											//< color+intensity
    Vector m_Position;										//< light source center position
    Vector m_Direction;										//< for SPOT, direction it is pointing
    float  m_Range;											//< distance range for light.0=infinite
    float m_Falloff;										//< angular falloff exponent for spot lights
    float m_Attenuation0;									//< constant distance falloff term
    float m_Attenuation1;									//< linear term of falloff
    float m_Attenuation2;									//< quadatic term of falloff

                                                            // NOTE: theta and phi are *half angles*
    float m_Theta;											//< inner cone angle. no angular falloff
                                                            //< within this cone
    float m_Phi;											//< outer cone angle

                                                            // the values below are derived from the above settings for optimizations
                                                            // These aren't used by DX8. . used for software lighting.

                                                            // NOTE: These dots are cos( m_Theta ), cos( m_Phi )
    float m_ThetaDot;
    float m_PhiDot;
    float m_OneOverThetaDotMinusPhiDot;
    unsigned int m_Flags;
protected:
    float m_RangeSquared;
};

struct MaterialLightingState_t
{
    Vector			m_vecAmbientCube[ 6 ];		// ambient, and lights that aren't in locallight[]
    Vector			m_vecLightingOrigin;		// The position from which lighting state was computed
    int				m_nLocalLightCount;
    LightDesc_t		m_pLocalLightDesc[ MATERIAL_MAX_LIGHT_COUNT ];

    MaterialLightingState_t &operator=( const MaterialLightingState_t &src )
    {
        memcpy( this , &src , sizeof( MaterialLightingState_t ) - MATERIAL_MAX_LIGHT_COUNT * sizeof( LightDesc_t ) );
        memcpy( m_pLocalLightDesc , &src.m_pLocalLightDesc , src.m_nLocalLightCount * sizeof( LightDesc_t ) );
        return *this;
    }
};

struct DrawModelInfo_t
{
    studiohdr_t		*m_pStudioHdr;
    studiohwdata_t	*m_pHardwareData;
    StudioDecalHandle_t m_Decals;
    int				m_Skin;
    int				m_Body;
    int				m_HitboxSet;
    void			*m_pClientEntity;
    int				m_Lod;
    ColorMeshInfo_t	*m_pColorMeshes;
    bool			m_bStaticLighting;
    MaterialLightingState_t	m_LightingState;
};

// UNDONE: Move this to hud export code, subsume previous functions
class IVModelRender
{
public:
    virtual int                     DrawModel( int flags , IClientRenderable *pRenderable , ModelInstanceHandle_t instance , int entity_index , const model_t *model , Vector const& origin , Angle const& angles , int skin , int body , int hitboxset , const Matrix3x4 *modelToWorld = NULL , const Matrix3x4 *pLightingOffset = NULL ) = 0;
    virtual void                    ForcedMaterialOverride( IMaterial *newMaterial , OverrideType_t nOverrideType = OverrideType_t::OVERRIDE_NORMAL , int nOverrides = 0 ) = 0;
    virtual bool                    IsForcedMaterialOverride( void ) = 0;
    virtual void                    SetViewTarget( const CStudioHdr *pStudioHdr , int nBodyIndex , const Vector& target ) = 0;
    virtual ModelInstanceHandle_t   CreateInstance( IClientRenderable *pRenderable , LightCacheHandle_t *pCache = NULL ) = 0;
    virtual void                    DestroyInstance( ModelInstanceHandle_t handle ) = 0;
    virtual void                    SetStaticLighting( ModelInstanceHandle_t handle , LightCacheHandle_t* pHandle ) = 0;
    virtual LightCacheHandle_t      GetStaticLighting( ModelInstanceHandle_t handle ) = 0;
    virtual bool                    ChangeInstance( ModelInstanceHandle_t handle , IClientRenderable *pRenderable ) = 0;
    virtual void                    AddDecal( ModelInstanceHandle_t handle , Ray const& ray , Vector const& decalUp , int decalIndex , int body , bool noPokeThru , int maxLODToDecal ) = 0;
    virtual void                    RemoveAllDecals( ModelInstanceHandle_t handle ) = 0;
    virtual bool                    ModelHasDecals( ModelInstanceHandle_t handle ) = 0;
    virtual void                    RemoveAllDecalsFromAllModels() = 0;
    virtual Matrix3x4*              DrawModelShadowSetup( IClientRenderable *pRenderable , int body , int skin , DrawModelInfo_t *pInfo , Matrix3x4 *pCustomBoneToWorld = NULL ) = 0;
    virtual void                    DrawModelShadow( IClientRenderable *pRenderable , const DrawModelInfo_t &info , Matrix3x4 *pCustomBoneToWorld = NULL ) = 0;
    virtual bool                    RecomputeStaticLighting( ModelInstanceHandle_t handle ) = 0;
    virtual void                    ReleaseAllStaticPropColorData( void ) = 0;
    virtual void                    RestoreAllStaticPropColorData( void ) = 0;
    virtual int                     DrawModelEx( ModelRenderInfo_t &pInfo ) = 0;
    virtual int                     DrawModelExStaticProp( ModelRenderInfo_t &pInfo ) = 0;
    virtual bool                    DrawModelSetup( IMatRenderContext* ctx , ModelRenderInfo_t &pInfo , DrawModelState_t *pState , Matrix3x4 **ppBoneToWorldOut ) = 0;
    virtual void                    DrawModelExecute( IMatRenderContext* ctx , const DrawModelState_t& state , const ModelRenderInfo_t& pInfo , Matrix3x4* pCustomBoneToWorld = NULL ) = 0;
    virtual void                    SetupLighting( const Vector &vecCenter ) = 0;
    virtual int                     DrawStaticPropArrayFast( StaticPropRenderInfo_t *pProps , int count , bool bShadowDepth ) = 0;
    virtual void                    SuppressEngineLighting( bool bSuppress ) = 0;
    virtual void                    SetupColorMeshes( int nTotalVerts ) = 0;
    virtual void                    SetupLightingEx( const Vector &vecCenter , ModelInstanceHandle_t handle ) = 0;
    virtual bool                    GetBrightestShadowingLightSource( const Vector &vecCenter , Vector& lightPos , Vector& lightBrightness , bool bAllowNonTaggedLights ) = 0;
    virtual void                    ComputeLightingState( int nCount , const LightingQuery_t *pQuery , MaterialLightingState_t *pState , ITexture **ppEnvCubemapTexture ) = 0;
    virtual void                    GetModelDecalHandles( StudioDecalHandle_t *pDecals , int nDecalStride , int nCount , const ModelInstanceHandle_t *pHandles ) = 0;
    virtual void                    ComputeStaticLightingState( int nCount , const StaticLightingQuery_t *pQuery , MaterialLightingState_t *pState , MaterialLightingState_t *pDecalState , ColorMeshInfo_t **ppStaticLighting , ITexture **ppEnvCubemapTexture , DataCacheHandle_t *pColorMeshHandles ) = 0;
    virtual void                    CleanupStaticLightingState( int nCount , DataCacheHandle_t *pColorMeshHandles ) = 0;
};

#endif