#ifndef MATERIALS
#define MATERIALS
#pragma once

extern IMaterial* Mat_VertexGhost;
extern IMaterial* Mat_VertexGhostIgnoreZ;
extern IMaterial* Mat_VertexGhostSelectedIgnoreZ;
extern IMaterial* Mat_Glow;
extern IMaterial *Mat_Wireframe;
extern IMaterial *Mat_WireframeIgnoreZ;
extern IMaterial *Mat_VertexColor;
extern IMaterial *Mat_VertexColorIgnoreZ;

void InitCustomMaterials();

class C_BaseEntity;
class CViewSetup;
class CMatRenderContextPtr;

constexpr int nSlipScreenSlotInvalid = -1;

class CGlowObjectManager
{
public:

    CGlowObjectManager()
    {
        for ( int i = 0; i < MAX_EDICTS; i++ )
        {
            bShouldRender[ i ] = false;
            bGlowingEntities[ i ] = false;
            bShouldRenderInOccluded[ i ] = false;
            bShouldRenderInUnOccluded[ i ] = false;
            vColorOccluded[ i ].Init();
            vColorUnOccluded[ i ].Init();
            flAlpha[ i ] = 0.0f;
        }
    }

    void SetEntity( int iEntIndex , const Vector& _vColorOccluded , const Vector& _vColorUnOccluded , float _flAlpha , bool bOccluded , bool bUnOccluded , bool bCanRender = true )
    {
        this->vColorOccluded[ iEntIndex ] = _vColorOccluded;
        this->vColorUnOccluded[ iEntIndex ] = _vColorUnOccluded;
        this->flAlpha[ iEntIndex ] = _flAlpha;
        this->bShouldRenderInOccluded[ iEntIndex ] = bOccluded;
        this->bShouldRenderInUnOccluded[ iEntIndex ] = bUnOccluded;
        this->bShouldRender[ iEntIndex ] = bCanRender;
    }

    void SetShouldRender( int iEntIndex , bool bCanRender )
    {
        this->bShouldRender[ iEntIndex ] = bCanRender;
    }

    void ApplyEntityGlowEffects( const CViewSetup *pSetup , CMatRenderContextPtr &pRenderContext , float flBloomScale , int x , int y , int w , int h );
    void RenderGlowEffects( const CViewSetup *pSetup );
    void DrawGlowVisible( CMatRenderContextPtr& pRenderContext );
    void DrawGlowOccluded( CMatRenderContextPtr& pRenderContext );
    void DrawGlowAlways( CMatRenderContextPtr& pRenderContext );
    void ApplyEntityCustomGlowEffects( const CViewSetup *pSetup , CMatRenderContextPtr &pRenderContext , float flBloomScale , int x , int y , int w , int h );
    void DrawModel( C_BaseEntity* pEntity );

    bool bShouldRender[ MAX_EDICTS ];
    bool bGlowingEntities[ MAX_EDICTS ];
    bool bOccluding[ MAX_EDICTS ];
    bool bUnOccluding[ MAX_EDICTS ];
    bool bShouldRenderInOccluded[ MAX_EDICTS ];
    bool bShouldRenderInUnOccluded[ MAX_EDICTS ];
    Vector vColorOccluded[ MAX_EDICTS ];
    Vector vColorUnOccluded[ MAX_EDICTS ];
    float flAlpha[ MAX_EDICTS ];
};

extern CGlowObjectManager g_GlowObjectManager;

#endif