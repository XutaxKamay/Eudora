///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CCSPlayer
#define SDK_CCSPlayer
#pragma once

class CCSPlayer
{
 public:

   class DT_CSPlayer
   {
    public:

      class DT_BasePlayer
      {
       public:

         class DT_BaseCombatCharacter
         {
          public:

            class DT_BaseFlex
            {
             public:

               class DT_BaseAnimatingOverlay
               {
                public:

                  class DT_BaseAnimating
                  {
                   public:

                     class DT_BaseEntity
                     {
                      public:

                        class DT_AnimTimeMustBeFirst
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T flAnimTime() { return ( T ) 0x25C; }
                        };

                        template<typename T = unsigned long> __forceinline static T flSimulationTime() { return ( T ) 0x264; }
                        template<typename T = unsigned long> __forceinline static T cellbits() { return ( T ) 0x74; }
                        template<typename T = unsigned long> __forceinline static T cellX() { return ( T ) 0x7C; }
                        template<typename T = unsigned long> __forceinline static T cellY() { return ( T ) 0x80; }
                        template<typename T = unsigned long> __forceinline static T cellZ() { return ( T ) 0x84; }
                        template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x134; }
                        template<typename T = unsigned long> __forceinline static T angRotation() { return ( T ) 0x128; }
                        template<typename T = unsigned long> __forceinline static T nModelIndex() { return ( T ) 0x254; }
                        template<typename T = unsigned long> __forceinline static T fEffects() { return ( T ) 0xEC; }
                        template<typename T = unsigned long> __forceinline static T nRenderMode() { return ( T ) 0x257; }
                        template<typename T = unsigned long> __forceinline static T nRenderFX() { return ( T ) 0x256; }
                        template<typename T = unsigned long> __forceinline static T clrRender() { return ( T ) 0x70; }
                        template<typename T = unsigned long> __forceinline static T iTeamNum() { return ( T ) 0xF0; }
                        template<typename T = unsigned long> __forceinline static T iPendingTeamNum() { return ( T ) 0xF4; }
                        template<typename T = unsigned long> __forceinline static T CollisionGroup() { return ( T ) 0x470; }
                        template<typename T = unsigned long> __forceinline static T flElasticity() { return ( T ) 0x398; }
                        template<typename T = unsigned long> __forceinline static T flShadowCastDistance() { return ( T ) 0x39C; }
                        template<typename T = unsigned long> __forceinline static T hOwnerEntity() { return ( T ) 0x148; }
                        template<typename T = unsigned long> __forceinline static T hEffectEntity() { return ( T ) 0x994; }
                        template<typename T = unsigned long> __forceinline static T moveparent() { return ( T ) 0x144; }
                        template<typename T = unsigned long> __forceinline static T iParentAttachment() { return ( T ) 0x2E8; }
                        template<typename T = unsigned long> __forceinline static T iName() { return ( T ) 0x150; }

                        class DT_CollisionProperty
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T vecMins() { return ( T ) 0x320; }
                           template<typename T = unsigned long> __forceinline static T vecMaxs() { return ( T ) 0x32C; }
                           template<typename T = unsigned long> __forceinline static T nSolidType() { return ( T ) 0x33A; }
                           template<typename T = unsigned long> __forceinline static T usSolidFlags() { return ( T ) 0x338; }
                           template<typename T = unsigned long> __forceinline static T nSurroundType() { return ( T ) 0x342; }
                           template<typename T = unsigned long> __forceinline static T triggerBloat() { return ( T ) 0x33B; }
                           template<typename T = unsigned long> __forceinline static T vecSpecifiedSurroundingMins() { return ( T ) 0x344; }
                           template<typename T = unsigned long> __forceinline static T vecSpecifiedSurroundingMaxs() { return ( T ) 0x350; }
                        };

                        template<typename T = unsigned long> __forceinline static T iTextureFrameIndex() { return ( T ) 0x988; }
                        template<typename T = unsigned long> __forceinline static T bSimulatedEveryTick() { return ( T ) 0x936; }
                        template<typename T = unsigned long> __forceinline static T bAnimatedEveryTick() { return ( T ) 0x937; }
                        template<typename T = unsigned long> __forceinline static T bAlternateSorting() { return ( T ) 0x938; }
                        template<typename T = unsigned long> __forceinline static T bSpotted() { return ( T ) 0x939; }

                        class m_bSpottedBy
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x93A; }
                           template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x93B; }
                           template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x93C; }
                           template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x93D; }
                           template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x93E; }
                           template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x93F; }
                           template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x940; }
                           template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x941; }
                           template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x942; }
                           template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x943; }
                           template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x944; }
                           template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x945; }
                           template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x946; }
                           template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x947; }
                           template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x948; }
                           template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x949; }
                           template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x94A; }
                           template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x94B; }
                           template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x94C; }
                           template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x94D; }
                           template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x94E; }
                           template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x94F; }
                           template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x950; }
                           template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x951; }
                           template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0x952; }
                           template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0x953; }
                           template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0x954; }
                           template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0x955; }
                           template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0x956; }
                           template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0x957; }
                           template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0x958; }
                           template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0x959; }
                           template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0x95A; }
                           template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0x95B; }
                           template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0x95C; }
                           template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0x95D; }
                           template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0x95E; }
                           template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0x95F; }
                           template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0x960; }
                           template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0x961; }
                           template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0x962; }
                           template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0x963; }
                           template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0x964; }
                           template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0x965; }
                           template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0x966; }
                           template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0x967; }
                           template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0x968; }
                           template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0x969; }
                           template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0x96A; }
                           template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0x96B; }
                           template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0x96C; }
                           template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0x96D; }
                           template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0x96E; }
                           template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0x96F; }
                           template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0x970; }
                           template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0x971; }
                           template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0x972; }
                           template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0x973; }
                           template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0x974; }
                           template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0x975; }
                           template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0x976; }
                           template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0x977; }
                           template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0x978; }
                           template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0x979; }
                           template<typename T = unsigned long> __forceinline static T _064() { return ( T ) 0x97A; }
                        };

                        class m_bSpottedByMask
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x97C; }
                           template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x980; }
                        };

                        template<typename T = unsigned long> __forceinline static T bIsAutoaimTarget() { return ( T ) 0x60; }
                        template<typename T = unsigned long> __forceinline static T fadeMinDist() { return ( T ) 0x2F0; }
                        template<typename T = unsigned long> __forceinline static T fadeMaxDist() { return ( T ) 0x2F4; }
                        template<typename T = unsigned long> __forceinline static T flFadeScale() { return ( T ) 0x2F8; }
                        template<typename T = unsigned long> __forceinline static T nMinCPULevel() { return ( T ) 0x984; }
                        template<typename T = unsigned long> __forceinline static T nMaxCPULevel() { return ( T ) 0x985; }
                        template<typename T = unsigned long> __forceinline static T nMinGPULevel() { return ( T ) 0x986; }
                        template<typename T = unsigned long> __forceinline static T nMaxGPULevel() { return ( T ) 0x987; }
                        template<typename T = unsigned long> __forceinline static T flUseLookAtAngle() { return ( T ) 0x2C8; }
                        template<typename T = unsigned long> __forceinline static T flLastMadeNoiseTime() { return ( T ) 0x20; }
                     };

                     template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0x28AC; }
                     template<typename T = unsigned long> __forceinline static T nForceBone() { return ( T ) 0x267C; }
                     template<typename T = unsigned long> __forceinline static T vecForce() { return ( T ) 0x2670; }
                     template<typename T = unsigned long> __forceinline static T nSkin() { return ( T ) 0xA1C; }
                     template<typename T = unsigned long> __forceinline static T nBody() { return ( T ) 0xA20; }
                     template<typename T = unsigned long> __forceinline static T nHitboxSet() { return ( T ) 0x9FC; }
                     template<typename T = unsigned long> __forceinline static T flModelScale() { return ( T ) 0x2738; }

                     class m_flPoseParameter
                     {
                      public:

                        template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x2764; }
                        template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x2768; }
                        template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x276C; }
                        template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x2770; }
                        template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x2774; }
                        template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x2778; }
                        template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x277C; }
                        template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x2780; }
                        template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x2784; }
                        template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x2788; }
                        template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x278C; }
                        template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x2790; }
                        template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x2794; }
                        template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x2798; }
                        template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x279C; }
                        template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x27A0; }
                        template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x27A4; }
                        template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x27A8; }
                        template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x27AC; }
                        template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x27B0; }
                        template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x27B4; }
                        template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x27B8; }
                        template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x27BC; }
                        template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x27C0; }
                     };

                     template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0xA18; }

                     class m_flEncodedController
                     {
                      public:

                        template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA48; }
                        template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA4C; }
                        template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA50; }
                        template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA54; }
                     };

                     template<typename T = unsigned long> __forceinline static T bClientSideAnimation() { return ( T ) 0x288C; }
                     template<typename T = unsigned long> __forceinline static T bClientSideFrameReset() { return ( T ) 0x26B0; }
                     template<typename T = unsigned long> __forceinline static T bClientSideRagdoll() { return ( T ) 0x275; }
                     template<typename T = unsigned long> __forceinline static T nNewSequenceParity() { return ( T ) 0xA38; }
                     template<typename T = unsigned long> __forceinline static T nResetEventsParity() { return ( T ) 0xA3C; }
                     template<typename T = unsigned long> __forceinline static T nMuzzleFlashParity() { return ( T ) 0xA58; }
                     template<typename T = unsigned long> __forceinline static T hLightingOrigin() { return ( T ) 0x2934; }

                     class DT_ServerAnimationData
                     {
                      public:

                        template<typename T = unsigned long> __forceinline static T flCycle() { return ( T ) 0xA14; }
                     };

                     template<typename T = unsigned long> __forceinline static T flFrozen() { return ( T ) 0x26E8; }
                     template<typename T = unsigned long> __forceinline static T ScaleType() { return ( T ) 0x273C; }
                     template<typename T = unsigned long> __forceinline static T bSuppressAnimSounds() { return ( T ) 0x293A; }
                  };

                  class DT_OverlayVars
                  {
                   public:

                     class _ST_m_AnimOverlay_15
                     {
                      public:

                        class _LPT_m_AnimOverlay_15
                        {
                         public:
                        };

                        class DT_Animationlayer_000
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0x2988; }
                           template<typename T = unsigned long> __forceinline static T flCycle() { return ( T ) 0x299C; }
                           template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0x2998; }
                           template<typename T = unsigned long> __forceinline static T flPrevCycle() { return ( T ) 0x298C; }
                           template<typename T = unsigned long> __forceinline static T flWeight() { return ( T ) 0x2990; }
                           template<typename T = unsigned long> __forceinline static T flWeightDeltaRate() { return ( T ) 0x2994; }
                           template<typename T = unsigned long> __forceinline static T nOrder() { return ( T ) 0x2984; }
                        };

                        template<typename T = unsigned long> __forceinline static T _ST_AnimOverlay_15_000() { return ( T ) 0x2970; }

                        class DT_Animationlayer_001
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0x52F8; }
                           template<typename T = unsigned long> __forceinline static T flCycle() { return ( T ) 0x530C; }
                           template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0x5308; }
                           template<typename T = unsigned long> __forceinline static T flPrevCycle() { return ( T ) 0x52FC; }
                           template<typename T = unsigned long> __forceinline static T flWeight() { return ( T ) 0x5300; }
                           template<typename T = unsigned long> __forceinline static T flWeightDeltaRate() { return ( T ) 0x5304; }
                           template<typename T = unsigned long> __forceinline static T nOrder() { return ( T ) 0x52F4; }
                        };

                        template<typename T = unsigned long> __forceinline static T _ST_AnimOverlay_15_001() { return ( T ) 0x52E0; }

                        class DT_Animationlayer_002
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0x7C68; }
                           template<typename T = unsigned long> __forceinline static T flCycle() { return ( T ) 0x7C7C; }
                           template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0x7C78; }
                           template<typename T = unsigned long> __forceinline static T flPrevCycle() { return ( T ) 0x7C6C; }
                           template<typename T = unsigned long> __forceinline static T flWeight() { return ( T ) 0x7C70; }
                           template<typename T = unsigned long> __forceinline static T flWeightDeltaRate() { return ( T ) 0x7C74; }
                           template<typename T = unsigned long> __forceinline static T nOrder() { return ( T ) 0x7C64; }
                        };

                        template<typename T = unsigned long> __forceinline static T _ST_AnimOverlay_15_002() { return ( T ) 0x7C50; }

                        class DT_Animationlayer_003
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0xA5D8; }
                           template<typename T = unsigned long> __forceinline static T flCycle() { return ( T ) 0xA5EC; }
                           template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0xA5E8; }
                           template<typename T = unsigned long> __forceinline static T flPrevCycle() { return ( T ) 0xA5DC; }
                           template<typename T = unsigned long> __forceinline static T flWeight() { return ( T ) 0xA5E0; }
                           template<typename T = unsigned long> __forceinline static T flWeightDeltaRate() { return ( T ) 0xA5E4; }
                           template<typename T = unsigned long> __forceinline static T nOrder() { return ( T ) 0xA5D4; }
                        };

                        template<typename T = unsigned long> __forceinline static T _ST_AnimOverlay_15_003() { return ( T ) 0xA5C0; }

                        class DT_Animationlayer_004
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0xCF48; }
                           template<typename T = unsigned long> __forceinline static T flCycle() { return ( T ) 0xCF5C; }
                           template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0xCF58; }
                           template<typename T = unsigned long> __forceinline static T flPrevCycle() { return ( T ) 0xCF4C; }
                           template<typename T = unsigned long> __forceinline static T flWeight() { return ( T ) 0xCF50; }
                           template<typename T = unsigned long> __forceinline static T flWeightDeltaRate() { return ( T ) 0xCF54; }
                           template<typename T = unsigned long> __forceinline static T nOrder() { return ( T ) 0xCF44; }
                        };

                        template<typename T = unsigned long> __forceinline static T _ST_AnimOverlay_15_004() { return ( T ) 0xCF30; }

                        class DT_Animationlayer_005
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0xF8B8; }
                           template<typename T = unsigned long> __forceinline static T flCycle() { return ( T ) 0xF8CC; }
                           template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0xF8C8; }
                           template<typename T = unsigned long> __forceinline static T flPrevCycle() { return ( T ) 0xF8BC; }
                           template<typename T = unsigned long> __forceinline static T flWeight() { return ( T ) 0xF8C0; }
                           template<typename T = unsigned long> __forceinline static T flWeightDeltaRate() { return ( T ) 0xF8C4; }
                           template<typename T = unsigned long> __forceinline static T nOrder() { return ( T ) 0xF8B4; }
                        };

                        template<typename T = unsigned long> __forceinline static T _ST_AnimOverlay_15_005() { return ( T ) 0xF8A0; }

                        class DT_Animationlayer_006
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0x12228; }
                           template<typename T = unsigned long> __forceinline static T flCycle() { return ( T ) 0x1223C; }
                           template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0x12238; }
                           template<typename T = unsigned long> __forceinline static T flPrevCycle() { return ( T ) 0x1222C; }
                           template<typename T = unsigned long> __forceinline static T flWeight() { return ( T ) 0x12230; }
                           template<typename T = unsigned long> __forceinline static T flWeightDeltaRate() { return ( T ) 0x12234; }
                           template<typename T = unsigned long> __forceinline static T nOrder() { return ( T ) 0x12224; }
                        };

                        template<typename T = unsigned long> __forceinline static T _ST_AnimOverlay_15_006() { return ( T ) 0x12210; }

                        class DT_Animationlayer_007
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0x14B98; }
                           template<typename T = unsigned long> __forceinline static T flCycle() { return ( T ) 0x14BAC; }
                           template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0x14BA8; }
                           template<typename T = unsigned long> __forceinline static T flPrevCycle() { return ( T ) 0x14B9C; }
                           template<typename T = unsigned long> __forceinline static T flWeight() { return ( T ) 0x14BA0; }
                           template<typename T = unsigned long> __forceinline static T flWeightDeltaRate() { return ( T ) 0x14BA4; }
                           template<typename T = unsigned long> __forceinline static T nOrder() { return ( T ) 0x14B94; }
                        };

                        template<typename T = unsigned long> __forceinline static T _ST_AnimOverlay_15_007() { return ( T ) 0x14B80; }

                        class DT_Animationlayer_008
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0x17508; }
                           template<typename T = unsigned long> __forceinline static T flCycle() { return ( T ) 0x1751C; }
                           template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0x17518; }
                           template<typename T = unsigned long> __forceinline static T flPrevCycle() { return ( T ) 0x1750C; }
                           template<typename T = unsigned long> __forceinline static T flWeight() { return ( T ) 0x17510; }
                           template<typename T = unsigned long> __forceinline static T flWeightDeltaRate() { return ( T ) 0x17514; }
                           template<typename T = unsigned long> __forceinline static T nOrder() { return ( T ) 0x17504; }
                        };

                        template<typename T = unsigned long> __forceinline static T _ST_AnimOverlay_15_008() { return ( T ) 0x174F0; }

                        class DT_Animationlayer_009
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0x19E78; }
                           template<typename T = unsigned long> __forceinline static T flCycle() { return ( T ) 0x19E8C; }
                           template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0x19E88; }
                           template<typename T = unsigned long> __forceinline static T flPrevCycle() { return ( T ) 0x19E7C; }
                           template<typename T = unsigned long> __forceinline static T flWeight() { return ( T ) 0x19E80; }
                           template<typename T = unsigned long> __forceinline static T flWeightDeltaRate() { return ( T ) 0x19E84; }
                           template<typename T = unsigned long> __forceinline static T nOrder() { return ( T ) 0x19E74; }
                        };

                        template<typename T = unsigned long> __forceinline static T _ST_AnimOverlay_15_009() { return ( T ) 0x19E60; }

                        class DT_Animationlayer_010
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0x1C7E8; }
                           template<typename T = unsigned long> __forceinline static T flCycle() { return ( T ) 0x1C7FC; }
                           template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0x1C7F8; }
                           template<typename T = unsigned long> __forceinline static T flPrevCycle() { return ( T ) 0x1C7EC; }
                           template<typename T = unsigned long> __forceinline static T flWeight() { return ( T ) 0x1C7F0; }
                           template<typename T = unsigned long> __forceinline static T flWeightDeltaRate() { return ( T ) 0x1C7F4; }
                           template<typename T = unsigned long> __forceinline static T nOrder() { return ( T ) 0x1C7E4; }
                        };

                        template<typename T = unsigned long> __forceinline static T _ST_AnimOverlay_15_010() { return ( T ) 0x1C7D0; }

                        class DT_Animationlayer_011
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0x1F158; }
                           template<typename T = unsigned long> __forceinline static T flCycle() { return ( T ) 0x1F16C; }
                           template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0x1F168; }
                           template<typename T = unsigned long> __forceinline static T flPrevCycle() { return ( T ) 0x1F15C; }
                           template<typename T = unsigned long> __forceinline static T flWeight() { return ( T ) 0x1F160; }
                           template<typename T = unsigned long> __forceinline static T flWeightDeltaRate() { return ( T ) 0x1F164; }
                           template<typename T = unsigned long> __forceinline static T nOrder() { return ( T ) 0x1F154; }
                        };

                        template<typename T = unsigned long> __forceinline static T _ST_AnimOverlay_15_011() { return ( T ) 0x1F140; }

                        class DT_Animationlayer_012
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0x21AC8; }
                           template<typename T = unsigned long> __forceinline static T flCycle() { return ( T ) 0x21ADC; }
                           template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0x21AD8; }
                           template<typename T = unsigned long> __forceinline static T flPrevCycle() { return ( T ) 0x21ACC; }
                           template<typename T = unsigned long> __forceinline static T flWeight() { return ( T ) 0x21AD0; }
                           template<typename T = unsigned long> __forceinline static T flWeightDeltaRate() { return ( T ) 0x21AD4; }
                           template<typename T = unsigned long> __forceinline static T nOrder() { return ( T ) 0x21AC4; }
                        };

                        template<typename T = unsigned long> __forceinline static T _ST_AnimOverlay_15_012() { return ( T ) 0x21AB0; }

                        class DT_Animationlayer_013
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0x24438; }
                           template<typename T = unsigned long> __forceinline static T flCycle() { return ( T ) 0x2444C; }
                           template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0x24448; }
                           template<typename T = unsigned long> __forceinline static T flPrevCycle() { return ( T ) 0x2443C; }
                           template<typename T = unsigned long> __forceinline static T flWeight() { return ( T ) 0x24440; }
                           template<typename T = unsigned long> __forceinline static T flWeightDeltaRate() { return ( T ) 0x24444; }
                           template<typename T = unsigned long> __forceinline static T nOrder() { return ( T ) 0x24434; }
                        };

                        template<typename T = unsigned long> __forceinline static T _ST_AnimOverlay_15_013() { return ( T ) 0x24420; }

                        class DT_Animationlayer_014
                        {
                         public:

                           template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0x26DA8; }
                           template<typename T = unsigned long> __forceinline static T flCycle() { return ( T ) 0x26DBC; }
                           template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0x26DB8; }
                           template<typename T = unsigned long> __forceinline static T flPrevCycle() { return ( T ) 0x26DAC; }
                           template<typename T = unsigned long> __forceinline static T flWeight() { return ( T ) 0x26DB0; }
                           template<typename T = unsigned long> __forceinline static T flWeightDeltaRate() { return ( T ) 0x26DB4; }
                           template<typename T = unsigned long> __forceinline static T nOrder() { return ( T ) 0x26DA4; }
                        };

                        template<typename T = unsigned long> __forceinline static T _ST_AnimOverlay_15_014() { return ( T ) 0x26D90; }
                     };
                  };
               };

               class m_flexWeight
               {
                public:

                  template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x2A18; }
                  template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x2A1C; }
                  template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x2A20; }
                  template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x2A24; }
                  template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x2A28; }
                  template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x2A2C; }
                  template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x2A30; }
                  template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x2A34; }
                  template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x2A38; }
                  template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x2A3C; }
                  template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x2A40; }
                  template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x2A44; }
                  template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x2A48; }
                  template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x2A4C; }
                  template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x2A50; }
                  template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x2A54; }
                  template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x2A58; }
                  template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x2A5C; }
                  template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x2A60; }
                  template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x2A64; }
                  template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x2A68; }
                  template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x2A6C; }
                  template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x2A70; }
                  template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x2A74; }
                  template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0x2A78; }
                  template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0x2A7C; }
                  template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0x2A80; }
                  template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0x2A84; }
                  template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0x2A88; }
                  template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0x2A8C; }
                  template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0x2A90; }
                  template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0x2A94; }
                  template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0x2A98; }
                  template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0x2A9C; }
                  template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0x2AA0; }
                  template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0x2AA4; }
                  template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0x2AA8; }
                  template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0x2AAC; }
                  template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0x2AB0; }
                  template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0x2AB4; }
                  template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0x2AB8; }
                  template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0x2ABC; }
                  template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0x2AC0; }
                  template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0x2AC4; }
                  template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0x2AC8; }
                  template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0x2ACC; }
                  template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0x2AD0; }
                  template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0x2AD4; }
                  template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0x2AD8; }
                  template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0x2ADC; }
                  template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0x2AE0; }
                  template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0x2AE4; }
                  template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0x2AE8; }
                  template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0x2AEC; }
                  template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0x2AF0; }
                  template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0x2AF4; }
                  template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0x2AF8; }
                  template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0x2AFC; }
                  template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0x2B00; }
                  template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0x2B04; }
                  template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0x2B08; }
                  template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0x2B0C; }
                  template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0x2B10; }
                  template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0x2B14; }
                  template<typename T = unsigned long> __forceinline static T _064() { return ( T ) 0x2B18; }
                  template<typename T = unsigned long> __forceinline static T _065() { return ( T ) 0x2B1C; }
                  template<typename T = unsigned long> __forceinline static T _066() { return ( T ) 0x2B20; }
                  template<typename T = unsigned long> __forceinline static T _067() { return ( T ) 0x2B24; }
                  template<typename T = unsigned long> __forceinline static T _068() { return ( T ) 0x2B28; }
                  template<typename T = unsigned long> __forceinline static T _069() { return ( T ) 0x2B2C; }
                  template<typename T = unsigned long> __forceinline static T _070() { return ( T ) 0x2B30; }
                  template<typename T = unsigned long> __forceinline static T _071() { return ( T ) 0x2B34; }
                  template<typename T = unsigned long> __forceinline static T _072() { return ( T ) 0x2B38; }
                  template<typename T = unsigned long> __forceinline static T _073() { return ( T ) 0x2B3C; }
                  template<typename T = unsigned long> __forceinline static T _074() { return ( T ) 0x2B40; }
                  template<typename T = unsigned long> __forceinline static T _075() { return ( T ) 0x2B44; }
                  template<typename T = unsigned long> __forceinline static T _076() { return ( T ) 0x2B48; }
                  template<typename T = unsigned long> __forceinline static T _077() { return ( T ) 0x2B4C; }
                  template<typename T = unsigned long> __forceinline static T _078() { return ( T ) 0x2B50; }
                  template<typename T = unsigned long> __forceinline static T _079() { return ( T ) 0x2B54; }
                  template<typename T = unsigned long> __forceinline static T _080() { return ( T ) 0x2B58; }
                  template<typename T = unsigned long> __forceinline static T _081() { return ( T ) 0x2B5C; }
                  template<typename T = unsigned long> __forceinline static T _082() { return ( T ) 0x2B60; }
                  template<typename T = unsigned long> __forceinline static T _083() { return ( T ) 0x2B64; }
                  template<typename T = unsigned long> __forceinline static T _084() { return ( T ) 0x2B68; }
                  template<typename T = unsigned long> __forceinline static T _085() { return ( T ) 0x2B6C; }
                  template<typename T = unsigned long> __forceinline static T _086() { return ( T ) 0x2B70; }
                  template<typename T = unsigned long> __forceinline static T _087() { return ( T ) 0x2B74; }
                  template<typename T = unsigned long> __forceinline static T _088() { return ( T ) 0x2B78; }
                  template<typename T = unsigned long> __forceinline static T _089() { return ( T ) 0x2B7C; }
                  template<typename T = unsigned long> __forceinline static T _090() { return ( T ) 0x2B80; }
                  template<typename T = unsigned long> __forceinline static T _091() { return ( T ) 0x2B84; }
                  template<typename T = unsigned long> __forceinline static T _092() { return ( T ) 0x2B88; }
                  template<typename T = unsigned long> __forceinline static T _093() { return ( T ) 0x2B8C; }
                  template<typename T = unsigned long> __forceinline static T _094() { return ( T ) 0x2B90; }
                  template<typename T = unsigned long> __forceinline static T _095() { return ( T ) 0x2B94; }
               };

               template<typename T = unsigned long> __forceinline static T blinktoggle() { return ( T ) 0x2BC4; }
               template<typename T = unsigned long> __forceinline static T viewtarget() { return ( T ) 0x29E0; }
            };

            class DT_BCCLocalPlayerExclusive
            {
             public:

               template<typename T = unsigned long> __forceinline static T flNextAttack() { return ( T ) 0x2D60; }
            };

            class DT_BCCNonLocalPlayerExclusive
            {
             public:

               class m_hMyWeapons
               {
                public:

                  template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x2DE8; }
                  template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x2DEC; }
                  template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x2DF0; }
                  template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x2DF4; }
                  template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x2DF8; }
                  template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x2DFC; }
                  template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x2E00; }
                  template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x2E04; }
                  template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x2E08; }
                  template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x2E0C; }
                  template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x2E10; }
                  template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x2E14; }
                  template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x2E18; }
                  template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x2E1C; }
                  template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x2E20; }
                  template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x2E24; }
                  template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x2E28; }
                  template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x2E2C; }
                  template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x2E30; }
                  template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x2E34; }
                  template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x2E38; }
                  template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x2E3C; }
                  template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x2E40; }
                  template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x2E44; }
                  template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0x2E48; }
                  template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0x2E4C; }
                  template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0x2E50; }
                  template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0x2E54; }
                  template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0x2E58; }
                  template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0x2E5C; }
                  template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0x2E60; }
                  template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0x2E64; }
                  template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0x2E68; }
                  template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0x2E6C; }
                  template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0x2E70; }
                  template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0x2E74; }
                  template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0x2E78; }
                  template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0x2E7C; }
                  template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0x2E80; }
                  template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0x2E84; }
                  template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0x2E88; }
                  template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0x2E8C; }
                  template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0x2E90; }
                  template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0x2E94; }
                  template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0x2E98; }
                  template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0x2E9C; }
                  template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0x2EA0; }
                  template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0x2EA4; }
                  template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0x2EA8; }
                  template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0x2EAC; }
                  template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0x2EB0; }
                  template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0x2EB4; }
                  template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0x2EB8; }
                  template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0x2EBC; }
                  template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0x2EC0; }
                  template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0x2EC4; }
                  template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0x2EC8; }
                  template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0x2ECC; }
                  template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0x2ED0; }
                  template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0x2ED4; }
                  template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0x2ED8; }
                  template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0x2EDC; }
                  template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0x2EE0; }
                  template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0x2EE4; }
               };
            };

            template<typename T = unsigned long> __forceinline static T LastHitGroup() { return ( T ) 0x2D64; }
            template<typename T = unsigned long> __forceinline static T hActiveWeapon() { return ( T ) 0x2EE8; }
            template<typename T = unsigned long> __forceinline static T flTimeOfLastInjury() { return ( T ) 0x2EEC; }
            template<typename T = unsigned long> __forceinline static T nRelativeDirectionOfLastInjury() { return ( T ) 0x2EF0; }

            class m_hMyWeapons
            {
             public:

               template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x2DE8; }
               template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x2DEC; }
               template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x2DF0; }
               template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x2DF4; }
               template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x2DF8; }
               template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x2DFC; }
               template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x2E00; }
               template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x2E04; }
               template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x2E08; }
               template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x2E0C; }
               template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x2E10; }
               template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x2E14; }
               template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x2E18; }
               template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x2E1C; }
               template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x2E20; }
               template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x2E24; }
               template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x2E28; }
               template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x2E2C; }
               template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x2E30; }
               template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x2E34; }
               template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x2E38; }
               template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x2E3C; }
               template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x2E40; }
               template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x2E44; }
               template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0x2E48; }
               template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0x2E4C; }
               template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0x2E50; }
               template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0x2E54; }
               template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0x2E58; }
               template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0x2E5C; }
               template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0x2E60; }
               template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0x2E64; }
               template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0x2E68; }
               template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0x2E6C; }
               template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0x2E70; }
               template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0x2E74; }
               template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0x2E78; }
               template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0x2E7C; }
               template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0x2E80; }
               template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0x2E84; }
               template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0x2E88; }
               template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0x2E8C; }
               template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0x2E90; }
               template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0x2E94; }
               template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0x2E98; }
               template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0x2E9C; }
               template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0x2EA0; }
               template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0x2EA4; }
               template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0x2EA8; }
               template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0x2EAC; }
               template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0x2EB0; }
               template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0x2EB4; }
               template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0x2EB8; }
               template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0x2EBC; }
               template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0x2EC0; }
               template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0x2EC4; }
               template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0x2EC8; }
               template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0x2ECC; }
               template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0x2ED0; }
               template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0x2ED4; }
               template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0x2ED8; }
               template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0x2EDC; }
               template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0x2EE0; }
               template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0x2EE4; }
            };

            class m_hMyWearables
            {
             public:

               template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x2EF4; }
            };
         };

         class DT_LocalPlayerExclusive
         {
          public:

            class DT_Local
            {
             public:

               class m_chAreaBits
               {
                public:

                  template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x2FB0; }
                  template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x2FB1; }
                  template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x2FB2; }
                  template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x2FB3; }
                  template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x2FB4; }
                  template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x2FB5; }
                  template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x2FB6; }
                  template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x2FB7; }
                  template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x2FB8; }
                  template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x2FB9; }
                  template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x2FBA; }
                  template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x2FBB; }
                  template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x2FBC; }
                  template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x2FBD; }
                  template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x2FBE; }
                  template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x2FBF; }
                  template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x2FC0; }
                  template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x2FC1; }
                  template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x2FC2; }
                  template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x2FC3; }
                  template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x2FC4; }
                  template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x2FC5; }
                  template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x2FC6; }
                  template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x2FC7; }
                  template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0x2FC8; }
                  template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0x2FC9; }
                  template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0x2FCA; }
                  template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0x2FCB; }
                  template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0x2FCC; }
                  template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0x2FCD; }
                  template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0x2FCE; }
                  template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0x2FCF; }
               };

               class m_chAreaPortalBits
               {
                public:

                  template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x2FD0; }
                  template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x2FD1; }
                  template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x2FD2; }
                  template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x2FD3; }
                  template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x2FD4; }
                  template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x2FD5; }
                  template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x2FD6; }
                  template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x2FD7; }
                  template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x2FD8; }
                  template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x2FD9; }
                  template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x2FDA; }
                  template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x2FDB; }
                  template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x2FDC; }
                  template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x2FDD; }
                  template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x2FDE; }
                  template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x2FDF; }
                  template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x2FE0; }
                  template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x2FE1; }
                  template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x2FE2; }
                  template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x2FE3; }
                  template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x2FE4; }
                  template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x2FE5; }
                  template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x2FE6; }
                  template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x2FE7; }
               };

               template<typename T = unsigned long> __forceinline static T iHideHUD() { return ( T ) 0x2FF4; }
               template<typename T = unsigned long> __forceinline static T flFOVRate() { return ( T ) 0x2FF0; }
               template<typename T = unsigned long> __forceinline static T bDucked() { return ( T ) 0x3034; }
               template<typename T = unsigned long> __forceinline static T bDucking() { return ( T ) 0x3035; }
               template<typename T = unsigned long> __forceinline static T flLastDuckTime() { return ( T ) 0x3038; }
               template<typename T = unsigned long> __forceinline static T bInDuckJump() { return ( T ) 0x303C; }
               template<typename T = unsigned long> __forceinline static T nDuckTimeMsecs() { return ( T ) 0x2FF8; }
               template<typename T = unsigned long> __forceinline static T nDuckJumpTimeMsecs() { return ( T ) 0x2FFC; }
               template<typename T = unsigned long> __forceinline static T nJumpTimeMsecs() { return ( T ) 0x3000; }
               template<typename T = unsigned long> __forceinline static T flFallVelocity() { return ( T ) 0x3004; }
               template<typename T = unsigned long> __forceinline static T viewPunchAngle() { return ( T ) 0x3010; }
               template<typename T = unsigned long> __forceinline static T aimPunchAngle() { return ( T ) 0x301C; }
               template<typename T = unsigned long> __forceinline static T aimPunchAngleVel() { return ( T ) 0x3028; }
               template<typename T = unsigned long> __forceinline static T bDrawViewmodel() { return ( T ) 0x303D; }
               template<typename T = unsigned long> __forceinline static T bWearingSuit() { return ( T ) 0x303E; }
               template<typename T = unsigned long> __forceinline static T bPoisoned() { return ( T ) 0x303F; }
               template<typename T = unsigned long> __forceinline static T flStepSize() { return ( T ) 0x300C; }
               template<typename T = unsigned long> __forceinline static T bAllowAutoMovement() { return ( T ) 0x3040; }
               template<typename T = unsigned long> __forceinline static T skybox3d_scale() { return ( T ) 0x30E0; }
               template<typename T = unsigned long> __forceinline static T skybox3d_origin() { return ( T ) 0x30E4; }
               template<typename T = unsigned long> __forceinline static T skybox3d_area() { return ( T ) 0x30F0; }
               template<typename T = unsigned long> __forceinline static T skybox3d_fog_enable() { return ( T ) 0x3138; }
               template<typename T = unsigned long> __forceinline static T skybox3d_fog_blend() { return ( T ) 0x3139; }
               template<typename T = unsigned long> __forceinline static T skybox3d_fog_dirPrimary() { return ( T ) 0x30F8; }
               template<typename T = unsigned long> __forceinline static T skybox3d_fog_colorPrimary() { return ( T ) 0x3104; }
               template<typename T = unsigned long> __forceinline static T skybox3d_fog_colorSecondary() { return ( T ) 0x3108; }
               template<typename T = unsigned long> __forceinline static T skybox3d_fog_start() { return ( T ) 0x3114; }
               template<typename T = unsigned long> __forceinline static T skybox3d_fog_end() { return ( T ) 0x3118; }
               template<typename T = unsigned long> __forceinline static T skybox3d_fog_maxdensity() { return ( T ) 0x3120; }
               template<typename T = unsigned long> __forceinline static T skybox3d_fog_HDRColorScale() { return ( T ) 0x3140; }
               template<typename T = unsigned long> __forceinline static T audio_localSound_0() { return ( T ) 0x3148; }
               template<typename T = unsigned long> __forceinline static T audio_localSound_1() { return ( T ) 0x3154; }
               template<typename T = unsigned long> __forceinline static T audio_localSound_2() { return ( T ) 0x3160; }
               template<typename T = unsigned long> __forceinline static T audio_localSound_3() { return ( T ) 0x316C; }
               template<typename T = unsigned long> __forceinline static T audio_localSound_4() { return ( T ) 0x3178; }
               template<typename T = unsigned long> __forceinline static T audio_localSound_5() { return ( T ) 0x3184; }
               template<typename T = unsigned long> __forceinline static T audio_localSound_6() { return ( T ) 0x3190; }
               template<typename T = unsigned long> __forceinline static T audio_localSound_7() { return ( T ) 0x319C; }
               template<typename T = unsigned long> __forceinline static T audio_soundscapeIndex() { return ( T ) 0x31A8; }
               template<typename T = unsigned long> __forceinline static T audio_localBits() { return ( T ) 0x31AC; }
               template<typename T = unsigned long> __forceinline static T audio_entIndex() { return ( T ) 0x31B0; }
            };

            template<typename T = unsigned long> __forceinline static T vecViewOffset_0() { return ( T ) 0x104; }
            template<typename T = unsigned long> __forceinline static T vecViewOffset_1() { return ( T ) 0x108; }
            template<typename T = unsigned long> __forceinline static T vecViewOffset_2() { return ( T ) 0x10C; }
            template<typename T = unsigned long> __forceinline static T flFriction() { return ( T ) 0x140; }
            template<typename T = unsigned long> __forceinline static T fOnTarget() { return ( T ) 0x3304; }
            template<typename T = unsigned long> __forceinline static T nTickBase() { return ( T ) 0x3404; }
            template<typename T = unsigned long> __forceinline static T nNextThinkTick() { return ( T ) 0xF8; }
            template<typename T = unsigned long> __forceinline static T hLastWeapon() { return ( T ) 0x32D8; }
            template<typename T = unsigned long> __forceinline static T vecVelocity_0() { return ( T ) 0x110; }
            template<typename T = unsigned long> __forceinline static T vecVelocity_1() { return ( T ) 0x114; }
            template<typename T = unsigned long> __forceinline static T vecVelocity_2() { return ( T ) 0x118; }
            template<typename T = unsigned long> __forceinline static T vecBaseVelocity() { return ( T ) 0x11C; }
            template<typename T = unsigned long> __forceinline static T hConstraintEntity() { return ( T ) 0x3320; }
            template<typename T = unsigned long> __forceinline static T vecConstraintCenter() { return ( T ) 0x3324; }
            template<typename T = unsigned long> __forceinline static T flConstraintRadius() { return ( T ) 0x3330; }
            template<typename T = unsigned long> __forceinline static T flConstraintWidth() { return ( T ) 0x3334; }
            template<typename T = unsigned long> __forceinline static T flConstraintSpeedFactor() { return ( T ) 0x3338; }
            template<typename T = unsigned long> __forceinline static T bConstraintPastRadius() { return ( T ) 0x333C; }
            template<typename T = unsigned long> __forceinline static T flDeathTime() { return ( T ) 0x3398; }
            template<typename T = unsigned long> __forceinline static T flNextDecalTime() { return ( T ) 0x339C; }
            template<typename T = unsigned long> __forceinline static T fForceTeam() { return ( T ) 0x33A0; }
            template<typename T = unsigned long> __forceinline static T flLaggedMovementValue() { return ( T ) 0x3568; }
            template<typename T = unsigned long> __forceinline static T hTonemapController() { return ( T ) 0x31BC; }
         };

         class DT_PlayerState
         {
          public:

            template<typename T = unsigned long> __forceinline static T deadflag() { return ( T ) 0x31C4; }
         };

         template<typename T = unsigned long> __forceinline static T iFOV() { return ( T ) 0x31D4; }
         template<typename T = unsigned long> __forceinline static T iFOVStart() { return ( T ) 0x31D8; }
         template<typename T = unsigned long> __forceinline static T flFOVTime() { return ( T ) 0x31F8; }
         template<typename T = unsigned long> __forceinline static T iDefaultFOV() { return ( T ) 0x330C; }
         template<typename T = unsigned long> __forceinline static T hZoomOwner() { return ( T ) 0x3230; }
         template<typename T = unsigned long> __forceinline static T afPhysicsFlags() { return ( T ) 0x32D0; }
         template<typename T = unsigned long> __forceinline static T hVehicle() { return ( T ) 0x32D4; }
         template<typename T = unsigned long> __forceinline static T hUseEntity() { return ( T ) 0x3308; }
         template<typename T = unsigned long> __forceinline static T hGroundEntity() { return ( T ) 0x14C; }
         template<typename T = unsigned long> __forceinline static T iHealth() { return ( T ) 0xFC; }
         template<typename T = unsigned long> __forceinline static T lifeState() { return ( T ) 0x25B; }

         class m_iAmmo
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x2D68; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x2D6C; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x2D70; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x2D74; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x2D78; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x2D7C; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x2D80; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x2D84; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x2D88; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x2D8C; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x2D90; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x2D94; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x2D98; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x2D9C; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x2DA0; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x2DA4; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x2DA8; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x2DAC; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x2DB0; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x2DB4; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x2DB8; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x2DBC; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x2DC0; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x2DC4; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0x2DC8; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0x2DCC; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0x2DD0; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0x2DD4; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0x2DD8; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0x2DDC; }
            template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0x2DE0; }
            template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0x2DE4; }
         };

         template<typename T = unsigned long> __forceinline static T iBonusProgress() { return ( T ) 0x3224; }
         template<typename T = unsigned long> __forceinline static T iBonusChallenge() { return ( T ) 0x3228; }
         template<typename T = unsigned long> __forceinline static T flMaxspeed() { return ( T ) 0x322C; }
         template<typename T = unsigned long> __forceinline static T fFlags() { return ( T ) 0x100; }
         template<typename T = unsigned long> __forceinline static T iObserverMode() { return ( T ) 0x334C; }
         template<typename T = unsigned long> __forceinline static T bActiveCameraMan() { return ( T ) 0x3350; }
         template<typename T = unsigned long> __forceinline static T bCameraManXRay() { return ( T ) 0x3351; }
         template<typename T = unsigned long> __forceinline static T bCameraManOverview() { return ( T ) 0x3352; }
         template<typename T = unsigned long> __forceinline static T bCameraManScoreBoard() { return ( T ) 0x3353; }
         template<typename T = unsigned long> __forceinline static T uCameraManGraphs() { return ( T ) 0x3354; }
         template<typename T = unsigned long> __forceinline static T iDeathPostEffect() { return ( T ) 0x3348; }
         template<typename T = unsigned long> __forceinline static T hObserverTarget() { return ( T ) 0x3360; }
         template<typename T = unsigned long> __forceinline static T hViewModel_0() { return ( T ) 0x32DC; }
         template<typename T = unsigned long> __forceinline static T iCoachingTeam() { return ( T ) 0x2F40; }
         template<typename T = unsigned long> __forceinline static T szLastPlaceName() { return ( T ) 0x3588; }
         template<typename T = unsigned long> __forceinline static T vecLadderNormal() { return ( T ) 0x3214; }
         template<typename T = unsigned long> __forceinline static T ladderSurfaceProps() { return ( T ) 0x31F0; }
         template<typename T = unsigned long> __forceinline static T ubEFNoInterpParity() { return ( T ) 0x35AC; }
         template<typename T = unsigned long> __forceinline static T hPostProcessCtrl() { return ( T ) 0x377C; }
         template<typename T = unsigned long> __forceinline static T hColorCorrectionCtrl() { return ( T ) 0x3780; }
         template<typename T = unsigned long> __forceinline static T PlayerFog_hCtrl() { return ( T ) 0x3788; }
         template<typename T = unsigned long> __forceinline static T vphysicsCollisionState() { return ( T ) 0x3240; }
         template<typename T = unsigned long> __forceinline static T hViewEntity() { return ( T ) 0x3318; }
         template<typename T = unsigned long> __forceinline static T bShouldDrawPlayerWhileUsingViewEntity() { return ( T ) 0x331C; }
         template<typename T = unsigned long> __forceinline static T flDuckAmount() { return ( T ) 0x2F9C; }
         template<typename T = unsigned long> __forceinline static T flDuckSpeed() { return ( T ) 0x2FA0; }
         template<typename T = unsigned long> __forceinline static T nWaterLevel() { return ( T ) 0x25A; }
      };

      class DT_CSLocalPlayerExclusive
      {
       public:

         template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x134; }
         template<typename T = unsigned long> __forceinline static T vecOrigin_2() { return ( T ) 0x13C; }
         template<typename T = unsigned long> __forceinline static T flStamina() { return ( T ) 0xA2B8; }
         template<typename T = unsigned long> __forceinline static T iDirection() { return ( T ) 0xA2BC; }
         template<typename T = unsigned long> __forceinline static T iShotsFired() { return ( T ) 0xA2C0; }
         template<typename T = unsigned long> __forceinline static T nNumFastDucks() { return ( T ) 0xA2C4; }
         template<typename T = unsigned long> __forceinline static T bDuckOverride() { return ( T ) 0xA2C8; }
         template<typename T = unsigned long> __forceinline static T flVelocityModifier() { return ( T ) 0xA2CC; }

         class m_bPlayerDominated
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xB380; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xB381; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xB382; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xB383; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xB384; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xB385; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xB386; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xB387; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xB388; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xB389; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xB38A; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xB38B; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xB38C; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xB38D; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xB38E; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xB38F; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xB390; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xB391; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xB392; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xB393; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xB394; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xB395; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xB396; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xB397; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xB398; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xB399; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xB39A; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xB39B; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xB39C; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xB39D; }
            template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xB39E; }
            template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xB39F; }
            template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xB3A0; }
            template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xB3A1; }
            template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xB3A2; }
            template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xB3A3; }
            template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xB3A4; }
            template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xB3A5; }
            template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xB3A6; }
            template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xB3A7; }
            template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xB3A8; }
            template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xB3A9; }
            template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xB3AA; }
            template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xB3AB; }
            template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xB3AC; }
            template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xB3AD; }
            template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xB3AE; }
            template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xB3AF; }
            template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xB3B0; }
            template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xB3B1; }
            template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xB3B2; }
            template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xB3B3; }
            template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xB3B4; }
            template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xB3B5; }
            template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xB3B6; }
            template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xB3B7; }
            template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xB3B8; }
            template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0xB3B9; }
            template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0xB3BA; }
            template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0xB3BB; }
            template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0xB3BC; }
            template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0xB3BD; }
            template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0xB3BE; }
            template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0xB3BF; }
            template<typename T = unsigned long> __forceinline static T _064() { return ( T ) 0xB3C0; }
         };

         class m_bPlayerDominatingMe
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xB3C1; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xB3C2; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xB3C3; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xB3C4; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xB3C5; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xB3C6; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xB3C7; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xB3C8; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xB3C9; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xB3CA; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xB3CB; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xB3CC; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xB3CD; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xB3CE; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xB3CF; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xB3D0; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xB3D1; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xB3D2; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xB3D3; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xB3D4; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xB3D5; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xB3D6; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xB3D7; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xB3D8; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xB3D9; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xB3DA; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xB3DB; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xB3DC; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xB3DD; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xB3DE; }
            template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xB3DF; }
            template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xB3E0; }
            template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xB3E1; }
            template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xB3E2; }
            template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xB3E3; }
            template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xB3E4; }
            template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xB3E5; }
            template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xB3E6; }
            template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xB3E7; }
            template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xB3E8; }
            template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xB3E9; }
            template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xB3EA; }
            template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xB3EB; }
            template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xB3EC; }
            template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xB3ED; }
            template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xB3EE; }
            template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xB3EF; }
            template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xB3F0; }
            template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xB3F1; }
            template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xB3F2; }
            template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xB3F3; }
            template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xB3F4; }
            template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xB3F5; }
            template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xB3F6; }
            template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xB3F7; }
            template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xB3F8; }
            template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xB3F9; }
            template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0xB3FA; }
            template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0xB3FB; }
            template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0xB3FC; }
            template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0xB3FD; }
            template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0xB3FE; }
            template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0xB3FF; }
            template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0xB400; }
            template<typename T = unsigned long> __forceinline static T _064() { return ( T ) 0xB401; }
         };

         class m_iWeaponPurchasesThisRound
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xB404; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xB408; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xB40C; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xB410; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xB414; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xB418; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xB41C; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xB420; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xB424; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xB428; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xB42C; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xB430; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xB434; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xB438; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xB43C; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xB440; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xB444; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xB448; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xB44C; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xB450; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xB454; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xB458; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xB45C; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xB460; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xB464; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xB468; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xB46C; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xB470; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xB474; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xB478; }
            template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xB47C; }
            template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xB480; }
            template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xB484; }
            template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xB488; }
            template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xB48C; }
            template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xB490; }
            template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xB494; }
            template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xB498; }
            template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xB49C; }
            template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xB4A0; }
            template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xB4A4; }
            template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xB4A8; }
            template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xB4AC; }
            template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xB4B0; }
            template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xB4B4; }
            template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xB4B8; }
            template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xB4BC; }
            template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xB4C0; }
            template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xB4C4; }
            template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xB4C8; }
            template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xB4CC; }
            template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xB4D0; }
            template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xB4D4; }
            template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xB4D8; }
            template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xB4DC; }
            template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xB4E0; }
            template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xB4E4; }
            template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0xB4E8; }
            template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0xB4EC; }
            template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0xB4F0; }
            template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0xB4F4; }
            template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0xB4F8; }
            template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0xB4FC; }
            template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0xB500; }
            template<typename T = unsigned long> __forceinline static T _064() { return ( T ) 0xB504; }
            template<typename T = unsigned long> __forceinline static T _065() { return ( T ) 0xB508; }
            template<typename T = unsigned long> __forceinline static T _066() { return ( T ) 0xB50C; }
            template<typename T = unsigned long> __forceinline static T _067() { return ( T ) 0xB510; }
            template<typename T = unsigned long> __forceinline static T _068() { return ( T ) 0xB514; }
            template<typename T = unsigned long> __forceinline static T _069() { return ( T ) 0xB518; }
            template<typename T = unsigned long> __forceinline static T _070() { return ( T ) 0xB51C; }
            template<typename T = unsigned long> __forceinline static T _071() { return ( T ) 0xB520; }
            template<typename T = unsigned long> __forceinline static T _072() { return ( T ) 0xB524; }
            template<typename T = unsigned long> __forceinline static T _073() { return ( T ) 0xB528; }
            template<typename T = unsigned long> __forceinline static T _074() { return ( T ) 0xB52C; }
            template<typename T = unsigned long> __forceinline static T _075() { return ( T ) 0xB530; }
            template<typename T = unsigned long> __forceinline static T _076() { return ( T ) 0xB534; }
            template<typename T = unsigned long> __forceinline static T _077() { return ( T ) 0xB538; }
            template<typename T = unsigned long> __forceinline static T _078() { return ( T ) 0xB53C; }
            template<typename T = unsigned long> __forceinline static T _079() { return ( T ) 0xB540; }
            template<typename T = unsigned long> __forceinline static T _080() { return ( T ) 0xB544; }
            template<typename T = unsigned long> __forceinline static T _081() { return ( T ) 0xB548; }
            template<typename T = unsigned long> __forceinline static T _082() { return ( T ) 0xB54C; }
            template<typename T = unsigned long> __forceinline static T _083() { return ( T ) 0xB550; }
            template<typename T = unsigned long> __forceinline static T _084() { return ( T ) 0xB554; }
            template<typename T = unsigned long> __forceinline static T _085() { return ( T ) 0xB558; }
            template<typename T = unsigned long> __forceinline static T _086() { return ( T ) 0xB55C; }
            template<typename T = unsigned long> __forceinline static T _087() { return ( T ) 0xB560; }
            template<typename T = unsigned long> __forceinline static T _088() { return ( T ) 0xB564; }
            template<typename T = unsigned long> __forceinline static T _089() { return ( T ) 0xB568; }
            template<typename T = unsigned long> __forceinline static T _090() { return ( T ) 0xB56C; }
            template<typename T = unsigned long> __forceinline static T _091() { return ( T ) 0xB570; }
            template<typename T = unsigned long> __forceinline static T _092() { return ( T ) 0xB574; }
            template<typename T = unsigned long> __forceinline static T _093() { return ( T ) 0xB578; }
            template<typename T = unsigned long> __forceinline static T _094() { return ( T ) 0xB57C; }
            template<typename T = unsigned long> __forceinline static T _095() { return ( T ) 0xB580; }
            template<typename T = unsigned long> __forceinline static T _096() { return ( T ) 0xB584; }
            template<typename T = unsigned long> __forceinline static T _097() { return ( T ) 0xB588; }
            template<typename T = unsigned long> __forceinline static T _098() { return ( T ) 0xB58C; }
            template<typename T = unsigned long> __forceinline static T _099() { return ( T ) 0xB590; }
            template<typename T = unsigned long> __forceinline static T _100() { return ( T ) 0xB594; }
            template<typename T = unsigned long> __forceinline static T _101() { return ( T ) 0xB598; }
            template<typename T = unsigned long> __forceinline static T _102() { return ( T ) 0xB59C; }
            template<typename T = unsigned long> __forceinline static T _103() { return ( T ) 0xB5A0; }
            template<typename T = unsigned long> __forceinline static T _104() { return ( T ) 0xB5A4; }
            template<typename T = unsigned long> __forceinline static T _105() { return ( T ) 0xB5A8; }
            template<typename T = unsigned long> __forceinline static T _106() { return ( T ) 0xB5AC; }
            template<typename T = unsigned long> __forceinline static T _107() { return ( T ) 0xB5B0; }
            template<typename T = unsigned long> __forceinline static T _108() { return ( T ) 0xB5B4; }
            template<typename T = unsigned long> __forceinline static T _109() { return ( T ) 0xB5B8; }
            template<typename T = unsigned long> __forceinline static T _110() { return ( T ) 0xB5BC; }
            template<typename T = unsigned long> __forceinline static T _111() { return ( T ) 0xB5C0; }
            template<typename T = unsigned long> __forceinline static T _112() { return ( T ) 0xB5C4; }
            template<typename T = unsigned long> __forceinline static T _113() { return ( T ) 0xB5C8; }
            template<typename T = unsigned long> __forceinline static T _114() { return ( T ) 0xB5CC; }
            template<typename T = unsigned long> __forceinline static T _115() { return ( T ) 0xB5D0; }
            template<typename T = unsigned long> __forceinline static T _116() { return ( T ) 0xB5D4; }
            template<typename T = unsigned long> __forceinline static T _117() { return ( T ) 0xB5D8; }
            template<typename T = unsigned long> __forceinline static T _118() { return ( T ) 0xB5DC; }
            template<typename T = unsigned long> __forceinline static T _119() { return ( T ) 0xB5E0; }
            template<typename T = unsigned long> __forceinline static T _120() { return ( T ) 0xB5E4; }
            template<typename T = unsigned long> __forceinline static T _121() { return ( T ) 0xB5E8; }
            template<typename T = unsigned long> __forceinline static T _122() { return ( T ) 0xB5EC; }
            template<typename T = unsigned long> __forceinline static T _123() { return ( T ) 0xB5F0; }
            template<typename T = unsigned long> __forceinline static T _124() { return ( T ) 0xB5F4; }
            template<typename T = unsigned long> __forceinline static T _125() { return ( T ) 0xB5F8; }
            template<typename T = unsigned long> __forceinline static T _126() { return ( T ) 0xB5FC; }
            template<typename T = unsigned long> __forceinline static T _127() { return ( T ) 0xB600; }
            template<typename T = unsigned long> __forceinline static T _128() { return ( T ) 0xB604; }
            template<typename T = unsigned long> __forceinline static T _129() { return ( T ) 0xB608; }
            template<typename T = unsigned long> __forceinline static T _130() { return ( T ) 0xB60C; }
            template<typename T = unsigned long> __forceinline static T _131() { return ( T ) 0xB610; }
            template<typename T = unsigned long> __forceinline static T _132() { return ( T ) 0xB614; }
            template<typename T = unsigned long> __forceinline static T _133() { return ( T ) 0xB618; }
            template<typename T = unsigned long> __forceinline static T _134() { return ( T ) 0xB61C; }
            template<typename T = unsigned long> __forceinline static T _135() { return ( T ) 0xB620; }
            template<typename T = unsigned long> __forceinline static T _136() { return ( T ) 0xB624; }
            template<typename T = unsigned long> __forceinline static T _137() { return ( T ) 0xB628; }
            template<typename T = unsigned long> __forceinline static T _138() { return ( T ) 0xB62C; }
            template<typename T = unsigned long> __forceinline static T _139() { return ( T ) 0xB630; }
            template<typename T = unsigned long> __forceinline static T _140() { return ( T ) 0xB634; }
            template<typename T = unsigned long> __forceinline static T _141() { return ( T ) 0xB638; }
            template<typename T = unsigned long> __forceinline static T _142() { return ( T ) 0xB63C; }
            template<typename T = unsigned long> __forceinline static T _143() { return ( T ) 0xB640; }
            template<typename T = unsigned long> __forceinline static T _144() { return ( T ) 0xB644; }
            template<typename T = unsigned long> __forceinline static T _145() { return ( T ) 0xB648; }
            template<typename T = unsigned long> __forceinline static T _146() { return ( T ) 0xB64C; }
            template<typename T = unsigned long> __forceinline static T _147() { return ( T ) 0xB650; }
            template<typename T = unsigned long> __forceinline static T _148() { return ( T ) 0xB654; }
            template<typename T = unsigned long> __forceinline static T _149() { return ( T ) 0xB658; }
            template<typename T = unsigned long> __forceinline static T _150() { return ( T ) 0xB65C; }
            template<typename T = unsigned long> __forceinline static T _151() { return ( T ) 0xB660; }
            template<typename T = unsigned long> __forceinline static T _152() { return ( T ) 0xB664; }
            template<typename T = unsigned long> __forceinline static T _153() { return ( T ) 0xB668; }
            template<typename T = unsigned long> __forceinline static T _154() { return ( T ) 0xB66C; }
            template<typename T = unsigned long> __forceinline static T _155() { return ( T ) 0xB670; }
            template<typename T = unsigned long> __forceinline static T _156() { return ( T ) 0xB674; }
            template<typename T = unsigned long> __forceinline static T _157() { return ( T ) 0xB678; }
            template<typename T = unsigned long> __forceinline static T _158() { return ( T ) 0xB67C; }
            template<typename T = unsigned long> __forceinline static T _159() { return ( T ) 0xB680; }
            template<typename T = unsigned long> __forceinline static T _160() { return ( T ) 0xB684; }
            template<typename T = unsigned long> __forceinline static T _161() { return ( T ) 0xB688; }
            template<typename T = unsigned long> __forceinline static T _162() { return ( T ) 0xB68C; }
            template<typename T = unsigned long> __forceinline static T _163() { return ( T ) 0xB690; }
            template<typename T = unsigned long> __forceinline static T _164() { return ( T ) 0xB694; }
            template<typename T = unsigned long> __forceinline static T _165() { return ( T ) 0xB698; }
            template<typename T = unsigned long> __forceinline static T _166() { return ( T ) 0xB69C; }
            template<typename T = unsigned long> __forceinline static T _167() { return ( T ) 0xB6A0; }
            template<typename T = unsigned long> __forceinline static T _168() { return ( T ) 0xB6A4; }
            template<typename T = unsigned long> __forceinline static T _169() { return ( T ) 0xB6A8; }
            template<typename T = unsigned long> __forceinline static T _170() { return ( T ) 0xB6AC; }
            template<typename T = unsigned long> __forceinline static T _171() { return ( T ) 0xB6B0; }
            template<typename T = unsigned long> __forceinline static T _172() { return ( T ) 0xB6B4; }
            template<typename T = unsigned long> __forceinline static T _173() { return ( T ) 0xB6B8; }
            template<typename T = unsigned long> __forceinline static T _174() { return ( T ) 0xB6BC; }
            template<typename T = unsigned long> __forceinline static T _175() { return ( T ) 0xB6C0; }
            template<typename T = unsigned long> __forceinline static T _176() { return ( T ) 0xB6C4; }
            template<typename T = unsigned long> __forceinline static T _177() { return ( T ) 0xB6C8; }
            template<typename T = unsigned long> __forceinline static T _178() { return ( T ) 0xB6CC; }
            template<typename T = unsigned long> __forceinline static T _179() { return ( T ) 0xB6D0; }
            template<typename T = unsigned long> __forceinline static T _180() { return ( T ) 0xB6D4; }
            template<typename T = unsigned long> __forceinline static T _181() { return ( T ) 0xB6D8; }
            template<typename T = unsigned long> __forceinline static T _182() { return ( T ) 0xB6DC; }
            template<typename T = unsigned long> __forceinline static T _183() { return ( T ) 0xB6E0; }
            template<typename T = unsigned long> __forceinline static T _184() { return ( T ) 0xB6E4; }
            template<typename T = unsigned long> __forceinline static T _185() { return ( T ) 0xB6E8; }
            template<typename T = unsigned long> __forceinline static T _186() { return ( T ) 0xB6EC; }
            template<typename T = unsigned long> __forceinline static T _187() { return ( T ) 0xB6F0; }
            template<typename T = unsigned long> __forceinline static T _188() { return ( T ) 0xB6F4; }
            template<typename T = unsigned long> __forceinline static T _189() { return ( T ) 0xB6F8; }
            template<typename T = unsigned long> __forceinline static T _190() { return ( T ) 0xB6FC; }
            template<typename T = unsigned long> __forceinline static T _191() { return ( T ) 0xB700; }
            template<typename T = unsigned long> __forceinline static T _192() { return ( T ) 0xB704; }
            template<typename T = unsigned long> __forceinline static T _193() { return ( T ) 0xB708; }
            template<typename T = unsigned long> __forceinline static T _194() { return ( T ) 0xB70C; }
            template<typename T = unsigned long> __forceinline static T _195() { return ( T ) 0xB710; }
            template<typename T = unsigned long> __forceinline static T _196() { return ( T ) 0xB714; }
            template<typename T = unsigned long> __forceinline static T _197() { return ( T ) 0xB718; }
            template<typename T = unsigned long> __forceinline static T _198() { return ( T ) 0xB71C; }
            template<typename T = unsigned long> __forceinline static T _199() { return ( T ) 0xB720; }
            template<typename T = unsigned long> __forceinline static T _200() { return ( T ) 0xB724; }
            template<typename T = unsigned long> __forceinline static T _201() { return ( T ) 0xB728; }
            template<typename T = unsigned long> __forceinline static T _202() { return ( T ) 0xB72C; }
            template<typename T = unsigned long> __forceinline static T _203() { return ( T ) 0xB730; }
            template<typename T = unsigned long> __forceinline static T _204() { return ( T ) 0xB734; }
            template<typename T = unsigned long> __forceinline static T _205() { return ( T ) 0xB738; }
            template<typename T = unsigned long> __forceinline static T _206() { return ( T ) 0xB73C; }
            template<typename T = unsigned long> __forceinline static T _207() { return ( T ) 0xB740; }
            template<typename T = unsigned long> __forceinline static T _208() { return ( T ) 0xB744; }
            template<typename T = unsigned long> __forceinline static T _209() { return ( T ) 0xB748; }
            template<typename T = unsigned long> __forceinline static T _210() { return ( T ) 0xB74C; }
            template<typename T = unsigned long> __forceinline static T _211() { return ( T ) 0xB750; }
            template<typename T = unsigned long> __forceinline static T _212() { return ( T ) 0xB754; }
            template<typename T = unsigned long> __forceinline static T _213() { return ( T ) 0xB758; }
            template<typename T = unsigned long> __forceinline static T _214() { return ( T ) 0xB75C; }
            template<typename T = unsigned long> __forceinline static T _215() { return ( T ) 0xB760; }
            template<typename T = unsigned long> __forceinline static T _216() { return ( T ) 0xB764; }
            template<typename T = unsigned long> __forceinline static T _217() { return ( T ) 0xB768; }
            template<typename T = unsigned long> __forceinline static T _218() { return ( T ) 0xB76C; }
            template<typename T = unsigned long> __forceinline static T _219() { return ( T ) 0xB770; }
            template<typename T = unsigned long> __forceinline static T _220() { return ( T ) 0xB774; }
            template<typename T = unsigned long> __forceinline static T _221() { return ( T ) 0xB778; }
            template<typename T = unsigned long> __forceinline static T _222() { return ( T ) 0xB77C; }
            template<typename T = unsigned long> __forceinline static T _223() { return ( T ) 0xB780; }
            template<typename T = unsigned long> __forceinline static T _224() { return ( T ) 0xB784; }
            template<typename T = unsigned long> __forceinline static T _225() { return ( T ) 0xB788; }
            template<typename T = unsigned long> __forceinline static T _226() { return ( T ) 0xB78C; }
            template<typename T = unsigned long> __forceinline static T _227() { return ( T ) 0xB790; }
            template<typename T = unsigned long> __forceinline static T _228() { return ( T ) 0xB794; }
            template<typename T = unsigned long> __forceinline static T _229() { return ( T ) 0xB798; }
            template<typename T = unsigned long> __forceinline static T _230() { return ( T ) 0xB79C; }
            template<typename T = unsigned long> __forceinline static T _231() { return ( T ) 0xB7A0; }
            template<typename T = unsigned long> __forceinline static T _232() { return ( T ) 0xB7A4; }
            template<typename T = unsigned long> __forceinline static T _233() { return ( T ) 0xB7A8; }
            template<typename T = unsigned long> __forceinline static T _234() { return ( T ) 0xB7AC; }
            template<typename T = unsigned long> __forceinline static T _235() { return ( T ) 0xB7B0; }
            template<typename T = unsigned long> __forceinline static T _236() { return ( T ) 0xB7B4; }
            template<typename T = unsigned long> __forceinline static T _237() { return ( T ) 0xB7B8; }
            template<typename T = unsigned long> __forceinline static T _238() { return ( T ) 0xB7BC; }
            template<typename T = unsigned long> __forceinline static T _239() { return ( T ) 0xB7C0; }
            template<typename T = unsigned long> __forceinline static T _240() { return ( T ) 0xB7C4; }
            template<typename T = unsigned long> __forceinline static T _241() { return ( T ) 0xB7C8; }
            template<typename T = unsigned long> __forceinline static T _242() { return ( T ) 0xB7CC; }
            template<typename T = unsigned long> __forceinline static T _243() { return ( T ) 0xB7D0; }
            template<typename T = unsigned long> __forceinline static T _244() { return ( T ) 0xB7D4; }
            template<typename T = unsigned long> __forceinline static T _245() { return ( T ) 0xB7D8; }
            template<typename T = unsigned long> __forceinline static T _246() { return ( T ) 0xB7DC; }
            template<typename T = unsigned long> __forceinline static T _247() { return ( T ) 0xB7E0; }
            template<typename T = unsigned long> __forceinline static T _248() { return ( T ) 0xB7E4; }
            template<typename T = unsigned long> __forceinline static T _249() { return ( T ) 0xB7E8; }
            template<typename T = unsigned long> __forceinline static T _250() { return ( T ) 0xB7EC; }
            template<typename T = unsigned long> __forceinline static T _251() { return ( T ) 0xB7F0; }
            template<typename T = unsigned long> __forceinline static T _252() { return ( T ) 0xB7F4; }
            template<typename T = unsigned long> __forceinline static T _253() { return ( T ) 0xB7F8; }
            template<typename T = unsigned long> __forceinline static T _254() { return ( T ) 0xB7FC; }
            template<typename T = unsigned long> __forceinline static T _255() { return ( T ) 0xB800; }
         };

         template<typename T = unsigned long> __forceinline static T nQuestProgressReason() { return ( T ) 0xB204; }
      };

      class DT_CSNonLocalPlayerExclusive
      {
       public:

         template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x134; }
         template<typename T = unsigned long> __forceinline static T vecOrigin_2() { return ( T ) 0x13C; }
      };

      class DT_CSTeamExclusive
      {
       public:

         class m_iWeaponPurchasesThisMatch
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA964; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA968; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA96C; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA970; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA974; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA978; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA97C; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA980; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA984; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA988; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA98C; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA990; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA994; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA998; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA99C; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA9A0; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA9A4; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA9A8; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA9AC; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA9B0; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA9B4; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA9B8; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA9BC; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA9C0; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA9C4; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA9C8; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA9CC; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA9D0; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA9D4; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA9D8; }
            template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xA9DC; }
            template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xA9E0; }
            template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xA9E4; }
            template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xA9E8; }
            template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xA9EC; }
            template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xA9F0; }
            template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xA9F4; }
            template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xA9F8; }
            template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xA9FC; }
            template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xAA00; }
            template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xAA04; }
            template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xAA08; }
            template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xAA0C; }
            template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xAA10; }
            template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xAA14; }
            template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xAA18; }
            template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xAA1C; }
            template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xAA20; }
            template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xAA24; }
            template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xAA28; }
            template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xAA2C; }
            template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xAA30; }
            template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xAA34; }
            template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xAA38; }
            template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xAA3C; }
            template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xAA40; }
            template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xAA44; }
            template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0xAA48; }
            template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0xAA4C; }
            template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0xAA50; }
            template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0xAA54; }
            template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0xAA58; }
            template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0xAA5C; }
            template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0xAA60; }
            template<typename T = unsigned long> __forceinline static T _064() { return ( T ) 0xAA64; }
            template<typename T = unsigned long> __forceinline static T _065() { return ( T ) 0xAA68; }
            template<typename T = unsigned long> __forceinline static T _066() { return ( T ) 0xAA6C; }
            template<typename T = unsigned long> __forceinline static T _067() { return ( T ) 0xAA70; }
            template<typename T = unsigned long> __forceinline static T _068() { return ( T ) 0xAA74; }
            template<typename T = unsigned long> __forceinline static T _069() { return ( T ) 0xAA78; }
            template<typename T = unsigned long> __forceinline static T _070() { return ( T ) 0xAA7C; }
            template<typename T = unsigned long> __forceinline static T _071() { return ( T ) 0xAA80; }
            template<typename T = unsigned long> __forceinline static T _072() { return ( T ) 0xAA84; }
            template<typename T = unsigned long> __forceinline static T _073() { return ( T ) 0xAA88; }
            template<typename T = unsigned long> __forceinline static T _074() { return ( T ) 0xAA8C; }
            template<typename T = unsigned long> __forceinline static T _075() { return ( T ) 0xAA90; }
            template<typename T = unsigned long> __forceinline static T _076() { return ( T ) 0xAA94; }
            template<typename T = unsigned long> __forceinline static T _077() { return ( T ) 0xAA98; }
            template<typename T = unsigned long> __forceinline static T _078() { return ( T ) 0xAA9C; }
            template<typename T = unsigned long> __forceinline static T _079() { return ( T ) 0xAAA0; }
            template<typename T = unsigned long> __forceinline static T _080() { return ( T ) 0xAAA4; }
            template<typename T = unsigned long> __forceinline static T _081() { return ( T ) 0xAAA8; }
            template<typename T = unsigned long> __forceinline static T _082() { return ( T ) 0xAAAC; }
            template<typename T = unsigned long> __forceinline static T _083() { return ( T ) 0xAAB0; }
            template<typename T = unsigned long> __forceinline static T _084() { return ( T ) 0xAAB4; }
            template<typename T = unsigned long> __forceinline static T _085() { return ( T ) 0xAAB8; }
            template<typename T = unsigned long> __forceinline static T _086() { return ( T ) 0xAABC; }
            template<typename T = unsigned long> __forceinline static T _087() { return ( T ) 0xAAC0; }
            template<typename T = unsigned long> __forceinline static T _088() { return ( T ) 0xAAC4; }
            template<typename T = unsigned long> __forceinline static T _089() { return ( T ) 0xAAC8; }
            template<typename T = unsigned long> __forceinline static T _090() { return ( T ) 0xAACC; }
            template<typename T = unsigned long> __forceinline static T _091() { return ( T ) 0xAAD0; }
            template<typename T = unsigned long> __forceinline static T _092() { return ( T ) 0xAAD4; }
            template<typename T = unsigned long> __forceinline static T _093() { return ( T ) 0xAAD8; }
            template<typename T = unsigned long> __forceinline static T _094() { return ( T ) 0xAADC; }
            template<typename T = unsigned long> __forceinline static T _095() { return ( T ) 0xAAE0; }
            template<typename T = unsigned long> __forceinline static T _096() { return ( T ) 0xAAE4; }
            template<typename T = unsigned long> __forceinline static T _097() { return ( T ) 0xAAE8; }
            template<typename T = unsigned long> __forceinline static T _098() { return ( T ) 0xAAEC; }
            template<typename T = unsigned long> __forceinline static T _099() { return ( T ) 0xAAF0; }
            template<typename T = unsigned long> __forceinline static T _100() { return ( T ) 0xAAF4; }
            template<typename T = unsigned long> __forceinline static T _101() { return ( T ) 0xAAF8; }
            template<typename T = unsigned long> __forceinline static T _102() { return ( T ) 0xAAFC; }
            template<typename T = unsigned long> __forceinline static T _103() { return ( T ) 0xAB00; }
            template<typename T = unsigned long> __forceinline static T _104() { return ( T ) 0xAB04; }
            template<typename T = unsigned long> __forceinline static T _105() { return ( T ) 0xAB08; }
            template<typename T = unsigned long> __forceinline static T _106() { return ( T ) 0xAB0C; }
            template<typename T = unsigned long> __forceinline static T _107() { return ( T ) 0xAB10; }
            template<typename T = unsigned long> __forceinline static T _108() { return ( T ) 0xAB14; }
            template<typename T = unsigned long> __forceinline static T _109() { return ( T ) 0xAB18; }
            template<typename T = unsigned long> __forceinline static T _110() { return ( T ) 0xAB1C; }
            template<typename T = unsigned long> __forceinline static T _111() { return ( T ) 0xAB20; }
            template<typename T = unsigned long> __forceinline static T _112() { return ( T ) 0xAB24; }
            template<typename T = unsigned long> __forceinline static T _113() { return ( T ) 0xAB28; }
            template<typename T = unsigned long> __forceinline static T _114() { return ( T ) 0xAB2C; }
            template<typename T = unsigned long> __forceinline static T _115() { return ( T ) 0xAB30; }
            template<typename T = unsigned long> __forceinline static T _116() { return ( T ) 0xAB34; }
            template<typename T = unsigned long> __forceinline static T _117() { return ( T ) 0xAB38; }
            template<typename T = unsigned long> __forceinline static T _118() { return ( T ) 0xAB3C; }
            template<typename T = unsigned long> __forceinline static T _119() { return ( T ) 0xAB40; }
            template<typename T = unsigned long> __forceinline static T _120() { return ( T ) 0xAB44; }
            template<typename T = unsigned long> __forceinline static T _121() { return ( T ) 0xAB48; }
            template<typename T = unsigned long> __forceinline static T _122() { return ( T ) 0xAB4C; }
            template<typename T = unsigned long> __forceinline static T _123() { return ( T ) 0xAB50; }
            template<typename T = unsigned long> __forceinline static T _124() { return ( T ) 0xAB54; }
            template<typename T = unsigned long> __forceinline static T _125() { return ( T ) 0xAB58; }
            template<typename T = unsigned long> __forceinline static T _126() { return ( T ) 0xAB5C; }
            template<typename T = unsigned long> __forceinline static T _127() { return ( T ) 0xAB60; }
            template<typename T = unsigned long> __forceinline static T _128() { return ( T ) 0xAB64; }
            template<typename T = unsigned long> __forceinline static T _129() { return ( T ) 0xAB68; }
            template<typename T = unsigned long> __forceinline static T _130() { return ( T ) 0xAB6C; }
            template<typename T = unsigned long> __forceinline static T _131() { return ( T ) 0xAB70; }
            template<typename T = unsigned long> __forceinline static T _132() { return ( T ) 0xAB74; }
            template<typename T = unsigned long> __forceinline static T _133() { return ( T ) 0xAB78; }
            template<typename T = unsigned long> __forceinline static T _134() { return ( T ) 0xAB7C; }
            template<typename T = unsigned long> __forceinline static T _135() { return ( T ) 0xAB80; }
            template<typename T = unsigned long> __forceinline static T _136() { return ( T ) 0xAB84; }
            template<typename T = unsigned long> __forceinline static T _137() { return ( T ) 0xAB88; }
            template<typename T = unsigned long> __forceinline static T _138() { return ( T ) 0xAB8C; }
            template<typename T = unsigned long> __forceinline static T _139() { return ( T ) 0xAB90; }
            template<typename T = unsigned long> __forceinline static T _140() { return ( T ) 0xAB94; }
            template<typename T = unsigned long> __forceinline static T _141() { return ( T ) 0xAB98; }
            template<typename T = unsigned long> __forceinline static T _142() { return ( T ) 0xAB9C; }
            template<typename T = unsigned long> __forceinline static T _143() { return ( T ) 0xABA0; }
            template<typename T = unsigned long> __forceinline static T _144() { return ( T ) 0xABA4; }
            template<typename T = unsigned long> __forceinline static T _145() { return ( T ) 0xABA8; }
            template<typename T = unsigned long> __forceinline static T _146() { return ( T ) 0xABAC; }
            template<typename T = unsigned long> __forceinline static T _147() { return ( T ) 0xABB0; }
            template<typename T = unsigned long> __forceinline static T _148() { return ( T ) 0xABB4; }
            template<typename T = unsigned long> __forceinline static T _149() { return ( T ) 0xABB8; }
            template<typename T = unsigned long> __forceinline static T _150() { return ( T ) 0xABBC; }
            template<typename T = unsigned long> __forceinline static T _151() { return ( T ) 0xABC0; }
            template<typename T = unsigned long> __forceinline static T _152() { return ( T ) 0xABC4; }
            template<typename T = unsigned long> __forceinline static T _153() { return ( T ) 0xABC8; }
            template<typename T = unsigned long> __forceinline static T _154() { return ( T ) 0xABCC; }
            template<typename T = unsigned long> __forceinline static T _155() { return ( T ) 0xABD0; }
            template<typename T = unsigned long> __forceinline static T _156() { return ( T ) 0xABD4; }
            template<typename T = unsigned long> __forceinline static T _157() { return ( T ) 0xABD8; }
            template<typename T = unsigned long> __forceinline static T _158() { return ( T ) 0xABDC; }
            template<typename T = unsigned long> __forceinline static T _159() { return ( T ) 0xABE0; }
            template<typename T = unsigned long> __forceinline static T _160() { return ( T ) 0xABE4; }
            template<typename T = unsigned long> __forceinline static T _161() { return ( T ) 0xABE8; }
            template<typename T = unsigned long> __forceinline static T _162() { return ( T ) 0xABEC; }
            template<typename T = unsigned long> __forceinline static T _163() { return ( T ) 0xABF0; }
            template<typename T = unsigned long> __forceinline static T _164() { return ( T ) 0xABF4; }
            template<typename T = unsigned long> __forceinline static T _165() { return ( T ) 0xABF8; }
            template<typename T = unsigned long> __forceinline static T _166() { return ( T ) 0xABFC; }
            template<typename T = unsigned long> __forceinline static T _167() { return ( T ) 0xAC00; }
            template<typename T = unsigned long> __forceinline static T _168() { return ( T ) 0xAC04; }
            template<typename T = unsigned long> __forceinline static T _169() { return ( T ) 0xAC08; }
            template<typename T = unsigned long> __forceinline static T _170() { return ( T ) 0xAC0C; }
            template<typename T = unsigned long> __forceinline static T _171() { return ( T ) 0xAC10; }
            template<typename T = unsigned long> __forceinline static T _172() { return ( T ) 0xAC14; }
            template<typename T = unsigned long> __forceinline static T _173() { return ( T ) 0xAC18; }
            template<typename T = unsigned long> __forceinline static T _174() { return ( T ) 0xAC1C; }
            template<typename T = unsigned long> __forceinline static T _175() { return ( T ) 0xAC20; }
            template<typename T = unsigned long> __forceinline static T _176() { return ( T ) 0xAC24; }
            template<typename T = unsigned long> __forceinline static T _177() { return ( T ) 0xAC28; }
            template<typename T = unsigned long> __forceinline static T _178() { return ( T ) 0xAC2C; }
            template<typename T = unsigned long> __forceinline static T _179() { return ( T ) 0xAC30; }
            template<typename T = unsigned long> __forceinline static T _180() { return ( T ) 0xAC34; }
            template<typename T = unsigned long> __forceinline static T _181() { return ( T ) 0xAC38; }
            template<typename T = unsigned long> __forceinline static T _182() { return ( T ) 0xAC3C; }
            template<typename T = unsigned long> __forceinline static T _183() { return ( T ) 0xAC40; }
            template<typename T = unsigned long> __forceinline static T _184() { return ( T ) 0xAC44; }
            template<typename T = unsigned long> __forceinline static T _185() { return ( T ) 0xAC48; }
            template<typename T = unsigned long> __forceinline static T _186() { return ( T ) 0xAC4C; }
            template<typename T = unsigned long> __forceinline static T _187() { return ( T ) 0xAC50; }
            template<typename T = unsigned long> __forceinline static T _188() { return ( T ) 0xAC54; }
            template<typename T = unsigned long> __forceinline static T _189() { return ( T ) 0xAC58; }
            template<typename T = unsigned long> __forceinline static T _190() { return ( T ) 0xAC5C; }
            template<typename T = unsigned long> __forceinline static T _191() { return ( T ) 0xAC60; }
            template<typename T = unsigned long> __forceinline static T _192() { return ( T ) 0xAC64; }
            template<typename T = unsigned long> __forceinline static T _193() { return ( T ) 0xAC68; }
            template<typename T = unsigned long> __forceinline static T _194() { return ( T ) 0xAC6C; }
            template<typename T = unsigned long> __forceinline static T _195() { return ( T ) 0xAC70; }
            template<typename T = unsigned long> __forceinline static T _196() { return ( T ) 0xAC74; }
            template<typename T = unsigned long> __forceinline static T _197() { return ( T ) 0xAC78; }
            template<typename T = unsigned long> __forceinline static T _198() { return ( T ) 0xAC7C; }
            template<typename T = unsigned long> __forceinline static T _199() { return ( T ) 0xAC80; }
            template<typename T = unsigned long> __forceinline static T _200() { return ( T ) 0xAC84; }
            template<typename T = unsigned long> __forceinline static T _201() { return ( T ) 0xAC88; }
            template<typename T = unsigned long> __forceinline static T _202() { return ( T ) 0xAC8C; }
            template<typename T = unsigned long> __forceinline static T _203() { return ( T ) 0xAC90; }
            template<typename T = unsigned long> __forceinline static T _204() { return ( T ) 0xAC94; }
            template<typename T = unsigned long> __forceinline static T _205() { return ( T ) 0xAC98; }
            template<typename T = unsigned long> __forceinline static T _206() { return ( T ) 0xAC9C; }
            template<typename T = unsigned long> __forceinline static T _207() { return ( T ) 0xACA0; }
            template<typename T = unsigned long> __forceinline static T _208() { return ( T ) 0xACA4; }
            template<typename T = unsigned long> __forceinline static T _209() { return ( T ) 0xACA8; }
            template<typename T = unsigned long> __forceinline static T _210() { return ( T ) 0xACAC; }
            template<typename T = unsigned long> __forceinline static T _211() { return ( T ) 0xACB0; }
            template<typename T = unsigned long> __forceinline static T _212() { return ( T ) 0xACB4; }
            template<typename T = unsigned long> __forceinline static T _213() { return ( T ) 0xACB8; }
            template<typename T = unsigned long> __forceinline static T _214() { return ( T ) 0xACBC; }
            template<typename T = unsigned long> __forceinline static T _215() { return ( T ) 0xACC0; }
            template<typename T = unsigned long> __forceinline static T _216() { return ( T ) 0xACC4; }
            template<typename T = unsigned long> __forceinline static T _217() { return ( T ) 0xACC8; }
            template<typename T = unsigned long> __forceinline static T _218() { return ( T ) 0xACCC; }
            template<typename T = unsigned long> __forceinline static T _219() { return ( T ) 0xACD0; }
            template<typename T = unsigned long> __forceinline static T _220() { return ( T ) 0xACD4; }
            template<typename T = unsigned long> __forceinline static T _221() { return ( T ) 0xACD8; }
            template<typename T = unsigned long> __forceinline static T _222() { return ( T ) 0xACDC; }
            template<typename T = unsigned long> __forceinline static T _223() { return ( T ) 0xACE0; }
            template<typename T = unsigned long> __forceinline static T _224() { return ( T ) 0xACE4; }
            template<typename T = unsigned long> __forceinline static T _225() { return ( T ) 0xACE8; }
            template<typename T = unsigned long> __forceinline static T _226() { return ( T ) 0xACEC; }
            template<typename T = unsigned long> __forceinline static T _227() { return ( T ) 0xACF0; }
            template<typename T = unsigned long> __forceinline static T _228() { return ( T ) 0xACF4; }
            template<typename T = unsigned long> __forceinline static T _229() { return ( T ) 0xACF8; }
            template<typename T = unsigned long> __forceinline static T _230() { return ( T ) 0xACFC; }
            template<typename T = unsigned long> __forceinline static T _231() { return ( T ) 0xAD00; }
            template<typename T = unsigned long> __forceinline static T _232() { return ( T ) 0xAD04; }
            template<typename T = unsigned long> __forceinline static T _233() { return ( T ) 0xAD08; }
            template<typename T = unsigned long> __forceinline static T _234() { return ( T ) 0xAD0C; }
            template<typename T = unsigned long> __forceinline static T _235() { return ( T ) 0xAD10; }
            template<typename T = unsigned long> __forceinline static T _236() { return ( T ) 0xAD14; }
            template<typename T = unsigned long> __forceinline static T _237() { return ( T ) 0xAD18; }
            template<typename T = unsigned long> __forceinline static T _238() { return ( T ) 0xAD1C; }
            template<typename T = unsigned long> __forceinline static T _239() { return ( T ) 0xAD20; }
            template<typename T = unsigned long> __forceinline static T _240() { return ( T ) 0xAD24; }
            template<typename T = unsigned long> __forceinline static T _241() { return ( T ) 0xAD28; }
            template<typename T = unsigned long> __forceinline static T _242() { return ( T ) 0xAD2C; }
            template<typename T = unsigned long> __forceinline static T _243() { return ( T ) 0xAD30; }
            template<typename T = unsigned long> __forceinline static T _244() { return ( T ) 0xAD34; }
            template<typename T = unsigned long> __forceinline static T _245() { return ( T ) 0xAD38; }
            template<typename T = unsigned long> __forceinline static T _246() { return ( T ) 0xAD3C; }
            template<typename T = unsigned long> __forceinline static T _247() { return ( T ) 0xAD40; }
            template<typename T = unsigned long> __forceinline static T _248() { return ( T ) 0xAD44; }
            template<typename T = unsigned long> __forceinline static T _249() { return ( T ) 0xAD48; }
            template<typename T = unsigned long> __forceinline static T _250() { return ( T ) 0xAD4C; }
            template<typename T = unsigned long> __forceinline static T _251() { return ( T ) 0xAD50; }
            template<typename T = unsigned long> __forceinline static T _252() { return ( T ) 0xAD54; }
            template<typename T = unsigned long> __forceinline static T _253() { return ( T ) 0xAD58; }
            template<typename T = unsigned long> __forceinline static T _254() { return ( T ) 0xAD5C; }
            template<typename T = unsigned long> __forceinline static T _255() { return ( T ) 0xAD60; }
            template<typename T = unsigned long> __forceinline static T _256() { return ( T ) 0xAD64; }
            template<typename T = unsigned long> __forceinline static T _257() { return ( T ) 0xAD68; }
            template<typename T = unsigned long> __forceinline static T _258() { return ( T ) 0xAD6C; }
            template<typename T = unsigned long> __forceinline static T _259() { return ( T ) 0xAD70; }
            template<typename T = unsigned long> __forceinline static T _260() { return ( T ) 0xAD74; }
            template<typename T = unsigned long> __forceinline static T _261() { return ( T ) 0xAD78; }
            template<typename T = unsigned long> __forceinline static T _262() { return ( T ) 0xAD7C; }
            template<typename T = unsigned long> __forceinline static T _263() { return ( T ) 0xAD80; }
            template<typename T = unsigned long> __forceinline static T _264() { return ( T ) 0xAD84; }
            template<typename T = unsigned long> __forceinline static T _265() { return ( T ) 0xAD88; }
            template<typename T = unsigned long> __forceinline static T _266() { return ( T ) 0xAD8C; }
            template<typename T = unsigned long> __forceinline static T _267() { return ( T ) 0xAD90; }
            template<typename T = unsigned long> __forceinline static T _268() { return ( T ) 0xAD94; }
            template<typename T = unsigned long> __forceinline static T _269() { return ( T ) 0xAD98; }
            template<typename T = unsigned long> __forceinline static T _270() { return ( T ) 0xAD9C; }
            template<typename T = unsigned long> __forceinline static T _271() { return ( T ) 0xADA0; }
            template<typename T = unsigned long> __forceinline static T _272() { return ( T ) 0xADA4; }
            template<typename T = unsigned long> __forceinline static T _273() { return ( T ) 0xADA8; }
            template<typename T = unsigned long> __forceinline static T _274() { return ( T ) 0xADAC; }
            template<typename T = unsigned long> __forceinline static T _275() { return ( T ) 0xADB0; }
            template<typename T = unsigned long> __forceinline static T _276() { return ( T ) 0xADB4; }
            template<typename T = unsigned long> __forceinline static T _277() { return ( T ) 0xADB8; }
            template<typename T = unsigned long> __forceinline static T _278() { return ( T ) 0xADBC; }
            template<typename T = unsigned long> __forceinline static T _279() { return ( T ) 0xADC0; }
            template<typename T = unsigned long> __forceinline static T _280() { return ( T ) 0xADC4; }
            template<typename T = unsigned long> __forceinline static T _281() { return ( T ) 0xADC8; }
            template<typename T = unsigned long> __forceinline static T _282() { return ( T ) 0xADCC; }
            template<typename T = unsigned long> __forceinline static T _283() { return ( T ) 0xADD0; }
            template<typename T = unsigned long> __forceinline static T _284() { return ( T ) 0xADD4; }
            template<typename T = unsigned long> __forceinline static T _285() { return ( T ) 0xADD8; }
            template<typename T = unsigned long> __forceinline static T _286() { return ( T ) 0xADDC; }
            template<typename T = unsigned long> __forceinline static T _287() { return ( T ) 0xADE0; }
            template<typename T = unsigned long> __forceinline static T _288() { return ( T ) 0xADE4; }
            template<typename T = unsigned long> __forceinline static T _289() { return ( T ) 0xADE8; }
            template<typename T = unsigned long> __forceinline static T _290() { return ( T ) 0xADEC; }
            template<typename T = unsigned long> __forceinline static T _291() { return ( T ) 0xADF0; }
            template<typename T = unsigned long> __forceinline static T _292() { return ( T ) 0xADF4; }
            template<typename T = unsigned long> __forceinline static T _293() { return ( T ) 0xADF8; }
            template<typename T = unsigned long> __forceinline static T _294() { return ( T ) 0xADFC; }
            template<typename T = unsigned long> __forceinline static T _295() { return ( T ) 0xAE00; }
            template<typename T = unsigned long> __forceinline static T _296() { return ( T ) 0xAE04; }
            template<typename T = unsigned long> __forceinline static T _297() { return ( T ) 0xAE08; }
            template<typename T = unsigned long> __forceinline static T _298() { return ( T ) 0xAE0C; }
            template<typename T = unsigned long> __forceinline static T _299() { return ( T ) 0xAE10; }
            template<typename T = unsigned long> __forceinline static T _300() { return ( T ) 0xAE14; }
            template<typename T = unsigned long> __forceinline static T _301() { return ( T ) 0xAE18; }
            template<typename T = unsigned long> __forceinline static T _302() { return ( T ) 0xAE1C; }
            template<typename T = unsigned long> __forceinline static T _303() { return ( T ) 0xAE20; }
            template<typename T = unsigned long> __forceinline static T _304() { return ( T ) 0xAE24; }
            template<typename T = unsigned long> __forceinline static T _305() { return ( T ) 0xAE28; }
            template<typename T = unsigned long> __forceinline static T _306() { return ( T ) 0xAE2C; }
            template<typename T = unsigned long> __forceinline static T _307() { return ( T ) 0xAE30; }
            template<typename T = unsigned long> __forceinline static T _308() { return ( T ) 0xAE34; }
            template<typename T = unsigned long> __forceinline static T _309() { return ( T ) 0xAE38; }
            template<typename T = unsigned long> __forceinline static T _310() { return ( T ) 0xAE3C; }
            template<typename T = unsigned long> __forceinline static T _311() { return ( T ) 0xAE40; }
            template<typename T = unsigned long> __forceinline static T _312() { return ( T ) 0xAE44; }
            template<typename T = unsigned long> __forceinline static T _313() { return ( T ) 0xAE48; }
            template<typename T = unsigned long> __forceinline static T _314() { return ( T ) 0xAE4C; }
            template<typename T = unsigned long> __forceinline static T _315() { return ( T ) 0xAE50; }
            template<typename T = unsigned long> __forceinline static T _316() { return ( T ) 0xAE54; }
            template<typename T = unsigned long> __forceinline static T _317() { return ( T ) 0xAE58; }
            template<typename T = unsigned long> __forceinline static T _318() { return ( T ) 0xAE5C; }
            template<typename T = unsigned long> __forceinline static T _319() { return ( T ) 0xAE60; }
            template<typename T = unsigned long> __forceinline static T _320() { return ( T ) 0xAE64; }
            template<typename T = unsigned long> __forceinline static T _321() { return ( T ) 0xAE68; }
            template<typename T = unsigned long> __forceinline static T _322() { return ( T ) 0xAE6C; }
            template<typename T = unsigned long> __forceinline static T _323() { return ( T ) 0xAE70; }
            template<typename T = unsigned long> __forceinline static T _324() { return ( T ) 0xAE74; }
            template<typename T = unsigned long> __forceinline static T _325() { return ( T ) 0xAE78; }
            template<typename T = unsigned long> __forceinline static T _326() { return ( T ) 0xAE7C; }
            template<typename T = unsigned long> __forceinline static T _327() { return ( T ) 0xAE80; }
            template<typename T = unsigned long> __forceinline static T _328() { return ( T ) 0xAE84; }
            template<typename T = unsigned long> __forceinline static T _329() { return ( T ) 0xAE88; }
            template<typename T = unsigned long> __forceinline static T _330() { return ( T ) 0xAE8C; }
            template<typename T = unsigned long> __forceinline static T _331() { return ( T ) 0xAE90; }
            template<typename T = unsigned long> __forceinline static T _332() { return ( T ) 0xAE94; }
            template<typename T = unsigned long> __forceinline static T _333() { return ( T ) 0xAE98; }
            template<typename T = unsigned long> __forceinline static T _334() { return ( T ) 0xAE9C; }
            template<typename T = unsigned long> __forceinline static T _335() { return ( T ) 0xAEA0; }
            template<typename T = unsigned long> __forceinline static T _336() { return ( T ) 0xAEA4; }
            template<typename T = unsigned long> __forceinline static T _337() { return ( T ) 0xAEA8; }
            template<typename T = unsigned long> __forceinline static T _338() { return ( T ) 0xAEAC; }
            template<typename T = unsigned long> __forceinline static T _339() { return ( T ) 0xAEB0; }
            template<typename T = unsigned long> __forceinline static T _340() { return ( T ) 0xAEB4; }
            template<typename T = unsigned long> __forceinline static T _341() { return ( T ) 0xAEB8; }
            template<typename T = unsigned long> __forceinline static T _342() { return ( T ) 0xAEBC; }
            template<typename T = unsigned long> __forceinline static T _343() { return ( T ) 0xAEC0; }
            template<typename T = unsigned long> __forceinline static T _344() { return ( T ) 0xAEC4; }
            template<typename T = unsigned long> __forceinline static T _345() { return ( T ) 0xAEC8; }
            template<typename T = unsigned long> __forceinline static T _346() { return ( T ) 0xAECC; }
            template<typename T = unsigned long> __forceinline static T _347() { return ( T ) 0xAED0; }
            template<typename T = unsigned long> __forceinline static T _348() { return ( T ) 0xAED4; }
            template<typename T = unsigned long> __forceinline static T _349() { return ( T ) 0xAED8; }
            template<typename T = unsigned long> __forceinline static T _350() { return ( T ) 0xAEDC; }
            template<typename T = unsigned long> __forceinline static T _351() { return ( T ) 0xAEE0; }
            template<typename T = unsigned long> __forceinline static T _352() { return ( T ) 0xAEE4; }
            template<typename T = unsigned long> __forceinline static T _353() { return ( T ) 0xAEE8; }
            template<typename T = unsigned long> __forceinline static T _354() { return ( T ) 0xAEEC; }
            template<typename T = unsigned long> __forceinline static T _355() { return ( T ) 0xAEF0; }
            template<typename T = unsigned long> __forceinline static T _356() { return ( T ) 0xAEF4; }
            template<typename T = unsigned long> __forceinline static T _357() { return ( T ) 0xAEF8; }
            template<typename T = unsigned long> __forceinline static T _358() { return ( T ) 0xAEFC; }
            template<typename T = unsigned long> __forceinline static T _359() { return ( T ) 0xAF00; }
            template<typename T = unsigned long> __forceinline static T _360() { return ( T ) 0xAF04; }
            template<typename T = unsigned long> __forceinline static T _361() { return ( T ) 0xAF08; }
            template<typename T = unsigned long> __forceinline static T _362() { return ( T ) 0xAF0C; }
            template<typename T = unsigned long> __forceinline static T _363() { return ( T ) 0xAF10; }
            template<typename T = unsigned long> __forceinline static T _364() { return ( T ) 0xAF14; }
            template<typename T = unsigned long> __forceinline static T _365() { return ( T ) 0xAF18; }
            template<typename T = unsigned long> __forceinline static T _366() { return ( T ) 0xAF1C; }
            template<typename T = unsigned long> __forceinline static T _367() { return ( T ) 0xAF20; }
            template<typename T = unsigned long> __forceinline static T _368() { return ( T ) 0xAF24; }
            template<typename T = unsigned long> __forceinline static T _369() { return ( T ) 0xAF28; }
            template<typename T = unsigned long> __forceinline static T _370() { return ( T ) 0xAF2C; }
            template<typename T = unsigned long> __forceinline static T _371() { return ( T ) 0xAF30; }
            template<typename T = unsigned long> __forceinline static T _372() { return ( T ) 0xAF34; }
            template<typename T = unsigned long> __forceinline static T _373() { return ( T ) 0xAF38; }
            template<typename T = unsigned long> __forceinline static T _374() { return ( T ) 0xAF3C; }
            template<typename T = unsigned long> __forceinline static T _375() { return ( T ) 0xAF40; }
            template<typename T = unsigned long> __forceinline static T _376() { return ( T ) 0xAF44; }
            template<typename T = unsigned long> __forceinline static T _377() { return ( T ) 0xAF48; }
            template<typename T = unsigned long> __forceinline static T _378() { return ( T ) 0xAF4C; }
            template<typename T = unsigned long> __forceinline static T _379() { return ( T ) 0xAF50; }
            template<typename T = unsigned long> __forceinline static T _380() { return ( T ) 0xAF54; }
            template<typename T = unsigned long> __forceinline static T _381() { return ( T ) 0xAF58; }
            template<typename T = unsigned long> __forceinline static T _382() { return ( T ) 0xAF5C; }
            template<typename T = unsigned long> __forceinline static T _383() { return ( T ) 0xAF60; }
            template<typename T = unsigned long> __forceinline static T _384() { return ( T ) 0xAF64; }
            template<typename T = unsigned long> __forceinline static T _385() { return ( T ) 0xAF68; }
            template<typename T = unsigned long> __forceinline static T _386() { return ( T ) 0xAF6C; }
            template<typename T = unsigned long> __forceinline static T _387() { return ( T ) 0xAF70; }
            template<typename T = unsigned long> __forceinline static T _388() { return ( T ) 0xAF74; }
            template<typename T = unsigned long> __forceinline static T _389() { return ( T ) 0xAF78; }
            template<typename T = unsigned long> __forceinline static T _390() { return ( T ) 0xAF7C; }
            template<typename T = unsigned long> __forceinline static T _391() { return ( T ) 0xAF80; }
            template<typename T = unsigned long> __forceinline static T _392() { return ( T ) 0xAF84; }
            template<typename T = unsigned long> __forceinline static T _393() { return ( T ) 0xAF88; }
            template<typename T = unsigned long> __forceinline static T _394() { return ( T ) 0xAF8C; }
            template<typename T = unsigned long> __forceinline static T _395() { return ( T ) 0xAF90; }
            template<typename T = unsigned long> __forceinline static T _396() { return ( T ) 0xAF94; }
            template<typename T = unsigned long> __forceinline static T _397() { return ( T ) 0xAF98; }
            template<typename T = unsigned long> __forceinline static T _398() { return ( T ) 0xAF9C; }
            template<typename T = unsigned long> __forceinline static T _399() { return ( T ) 0xAFA0; }
            template<typename T = unsigned long> __forceinline static T _400() { return ( T ) 0xAFA4; }
            template<typename T = unsigned long> __forceinline static T _401() { return ( T ) 0xAFA8; }
            template<typename T = unsigned long> __forceinline static T _402() { return ( T ) 0xAFAC; }
            template<typename T = unsigned long> __forceinline static T _403() { return ( T ) 0xAFB0; }
            template<typename T = unsigned long> __forceinline static T _404() { return ( T ) 0xAFB4; }
            template<typename T = unsigned long> __forceinline static T _405() { return ( T ) 0xAFB8; }
            template<typename T = unsigned long> __forceinline static T _406() { return ( T ) 0xAFBC; }
            template<typename T = unsigned long> __forceinline static T _407() { return ( T ) 0xAFC0; }
            template<typename T = unsigned long> __forceinline static T _408() { return ( T ) 0xAFC4; }
            template<typename T = unsigned long> __forceinline static T _409() { return ( T ) 0xAFC8; }
            template<typename T = unsigned long> __forceinline static T _410() { return ( T ) 0xAFCC; }
            template<typename T = unsigned long> __forceinline static T _411() { return ( T ) 0xAFD0; }
            template<typename T = unsigned long> __forceinline static T _412() { return ( T ) 0xAFD4; }
            template<typename T = unsigned long> __forceinline static T _413() { return ( T ) 0xAFD8; }
            template<typename T = unsigned long> __forceinline static T _414() { return ( T ) 0xAFDC; }
            template<typename T = unsigned long> __forceinline static T _415() { return ( T ) 0xAFE0; }
            template<typename T = unsigned long> __forceinline static T _416() { return ( T ) 0xAFE4; }
            template<typename T = unsigned long> __forceinline static T _417() { return ( T ) 0xAFE8; }
            template<typename T = unsigned long> __forceinline static T _418() { return ( T ) 0xAFEC; }
            template<typename T = unsigned long> __forceinline static T _419() { return ( T ) 0xAFF0; }
            template<typename T = unsigned long> __forceinline static T _420() { return ( T ) 0xAFF4; }
            template<typename T = unsigned long> __forceinline static T _421() { return ( T ) 0xAFF8; }
            template<typename T = unsigned long> __forceinline static T _422() { return ( T ) 0xAFFC; }
            template<typename T = unsigned long> __forceinline static T _423() { return ( T ) 0xB000; }
            template<typename T = unsigned long> __forceinline static T _424() { return ( T ) 0xB004; }
            template<typename T = unsigned long> __forceinline static T _425() { return ( T ) 0xB008; }
            template<typename T = unsigned long> __forceinline static T _426() { return ( T ) 0xB00C; }
            template<typename T = unsigned long> __forceinline static T _427() { return ( T ) 0xB010; }
            template<typename T = unsigned long> __forceinline static T _428() { return ( T ) 0xB014; }
            template<typename T = unsigned long> __forceinline static T _429() { return ( T ) 0xB018; }
            template<typename T = unsigned long> __forceinline static T _430() { return ( T ) 0xB01C; }
            template<typename T = unsigned long> __forceinline static T _431() { return ( T ) 0xB020; }
            template<typename T = unsigned long> __forceinline static T _432() { return ( T ) 0xB024; }
            template<typename T = unsigned long> __forceinline static T _433() { return ( T ) 0xB028; }
            template<typename T = unsigned long> __forceinline static T _434() { return ( T ) 0xB02C; }
            template<typename T = unsigned long> __forceinline static T _435() { return ( T ) 0xB030; }
            template<typename T = unsigned long> __forceinline static T _436() { return ( T ) 0xB034; }
            template<typename T = unsigned long> __forceinline static T _437() { return ( T ) 0xB038; }
            template<typename T = unsigned long> __forceinline static T _438() { return ( T ) 0xB03C; }
            template<typename T = unsigned long> __forceinline static T _439() { return ( T ) 0xB040; }
            template<typename T = unsigned long> __forceinline static T _440() { return ( T ) 0xB044; }
            template<typename T = unsigned long> __forceinline static T _441() { return ( T ) 0xB048; }
            template<typename T = unsigned long> __forceinline static T _442() { return ( T ) 0xB04C; }
            template<typename T = unsigned long> __forceinline static T _443() { return ( T ) 0xB050; }
            template<typename T = unsigned long> __forceinline static T _444() { return ( T ) 0xB054; }
            template<typename T = unsigned long> __forceinline static T _445() { return ( T ) 0xB058; }
            template<typename T = unsigned long> __forceinline static T _446() { return ( T ) 0xB05C; }
            template<typename T = unsigned long> __forceinline static T _447() { return ( T ) 0xB060; }
            template<typename T = unsigned long> __forceinline static T _448() { return ( T ) 0xB064; }
            template<typename T = unsigned long> __forceinline static T _449() { return ( T ) 0xB068; }
            template<typename T = unsigned long> __forceinline static T _450() { return ( T ) 0xB06C; }
            template<typename T = unsigned long> __forceinline static T _451() { return ( T ) 0xB070; }
            template<typename T = unsigned long> __forceinline static T _452() { return ( T ) 0xB074; }
            template<typename T = unsigned long> __forceinline static T _453() { return ( T ) 0xB078; }
            template<typename T = unsigned long> __forceinline static T _454() { return ( T ) 0xB07C; }
            template<typename T = unsigned long> __forceinline static T _455() { return ( T ) 0xB080; }
            template<typename T = unsigned long> __forceinline static T _456() { return ( T ) 0xB084; }
            template<typename T = unsigned long> __forceinline static T _457() { return ( T ) 0xB088; }
            template<typename T = unsigned long> __forceinline static T _458() { return ( T ) 0xB08C; }
            template<typename T = unsigned long> __forceinline static T _459() { return ( T ) 0xB090; }
            template<typename T = unsigned long> __forceinline static T _460() { return ( T ) 0xB094; }
            template<typename T = unsigned long> __forceinline static T _461() { return ( T ) 0xB098; }
            template<typename T = unsigned long> __forceinline static T _462() { return ( T ) 0xB09C; }
            template<typename T = unsigned long> __forceinline static T _463() { return ( T ) 0xB0A0; }
            template<typename T = unsigned long> __forceinline static T _464() { return ( T ) 0xB0A4; }
            template<typename T = unsigned long> __forceinline static T _465() { return ( T ) 0xB0A8; }
            template<typename T = unsigned long> __forceinline static T _466() { return ( T ) 0xB0AC; }
            template<typename T = unsigned long> __forceinline static T _467() { return ( T ) 0xB0B0; }
            template<typename T = unsigned long> __forceinline static T _468() { return ( T ) 0xB0B4; }
            template<typename T = unsigned long> __forceinline static T _469() { return ( T ) 0xB0B8; }
            template<typename T = unsigned long> __forceinline static T _470() { return ( T ) 0xB0BC; }
            template<typename T = unsigned long> __forceinline static T _471() { return ( T ) 0xB0C0; }
            template<typename T = unsigned long> __forceinline static T _472() { return ( T ) 0xB0C4; }
            template<typename T = unsigned long> __forceinline static T _473() { return ( T ) 0xB0C8; }
            template<typename T = unsigned long> __forceinline static T _474() { return ( T ) 0xB0CC; }
            template<typename T = unsigned long> __forceinline static T _475() { return ( T ) 0xB0D0; }
            template<typename T = unsigned long> __forceinline static T _476() { return ( T ) 0xB0D4; }
            template<typename T = unsigned long> __forceinline static T _477() { return ( T ) 0xB0D8; }
            template<typename T = unsigned long> __forceinline static T _478() { return ( T ) 0xB0DC; }
            template<typename T = unsigned long> __forceinline static T _479() { return ( T ) 0xB0E0; }
            template<typename T = unsigned long> __forceinline static T _480() { return ( T ) 0xB0E4; }
            template<typename T = unsigned long> __forceinline static T _481() { return ( T ) 0xB0E8; }
            template<typename T = unsigned long> __forceinline static T _482() { return ( T ) 0xB0EC; }
            template<typename T = unsigned long> __forceinline static T _483() { return ( T ) 0xB0F0; }
            template<typename T = unsigned long> __forceinline static T _484() { return ( T ) 0xB0F4; }
            template<typename T = unsigned long> __forceinline static T _485() { return ( T ) 0xB0F8; }
            template<typename T = unsigned long> __forceinline static T _486() { return ( T ) 0xB0FC; }
            template<typename T = unsigned long> __forceinline static T _487() { return ( T ) 0xB100; }
            template<typename T = unsigned long> __forceinline static T _488() { return ( T ) 0xB104; }
            template<typename T = unsigned long> __forceinline static T _489() { return ( T ) 0xB108; }
            template<typename T = unsigned long> __forceinline static T _490() { return ( T ) 0xB10C; }
            template<typename T = unsigned long> __forceinline static T _491() { return ( T ) 0xB110; }
            template<typename T = unsigned long> __forceinline static T _492() { return ( T ) 0xB114; }
            template<typename T = unsigned long> __forceinline static T _493() { return ( T ) 0xB118; }
            template<typename T = unsigned long> __forceinline static T _494() { return ( T ) 0xB11C; }
            template<typename T = unsigned long> __forceinline static T _495() { return ( T ) 0xB120; }
            template<typename T = unsigned long> __forceinline static T _496() { return ( T ) 0xB124; }
            template<typename T = unsigned long> __forceinline static T _497() { return ( T ) 0xB128; }
            template<typename T = unsigned long> __forceinline static T _498() { return ( T ) 0xB12C; }
         };

         class m_EquippedLoadoutItemDefIndices
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xB13C; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xB13E; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xB140; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xB142; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xB144; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xB146; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xB148; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xB14A; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xB14C; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xB14E; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xB150; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xB152; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xB154; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xB156; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xB158; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xB15A; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xB15C; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xB15E; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xB160; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xB162; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xB164; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xB166; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xB168; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xB16A; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xB16C; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xB16E; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xB170; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xB172; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xB174; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xB176; }
            template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xB178; }
            template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xB17A; }
            template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xB17C; }
            template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xB17E; }
            template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xB180; }
            template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xB182; }
            template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xB184; }
            template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xB186; }
            template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xB188; }
            template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xB18A; }
            template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xB18C; }
            template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xB18E; }
            template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xB190; }
            template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xB192; }
            template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xB194; }
            template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xB196; }
            template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xB198; }
            template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xB19A; }
            template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xB19C; }
            template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xB19E; }
            template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xB1A0; }
            template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xB1A2; }
            template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xB1A4; }
            template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xB1A6; }
            template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xB1A8; }
            template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xB1AA; }
            template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xB1AC; }
         };
      };

      template<typename T = unsigned long> __forceinline static T angEyeAngles_0() { return ( T ) 0xB250; }
      template<typename T = unsigned long> __forceinline static T angEyeAngles_1() { return ( T ) 0xB254; }
      template<typename T = unsigned long> __forceinline static T iAddonBits() { return ( T ) 0xA2A4; }
      template<typename T = unsigned long> __forceinline static T iPrimaryAddon() { return ( T ) 0xA2A8; }
      template<typename T = unsigned long> __forceinline static T iSecondaryAddon() { return ( T ) 0xA2AC; }
      template<typename T = unsigned long> __forceinline static T iThrowGrenadeCounter() { return ( T ) 0x38C8; }
      template<typename T = unsigned long> __forceinline static T bWaitForNoAttack() { return ( T ) 0x38CC; }
      template<typename T = unsigned long> __forceinline static T bIsRespawningForDMBonus() { return ( T ) 0x38CD; }
      template<typename T = unsigned long> __forceinline static T iPlayerState() { return ( T ) 0x3894; }
      template<typename T = unsigned long> __forceinline static T iAccount() { return ( T ) 0xB238; }
      template<typename T = unsigned long> __forceinline static T iStartAccount() { return ( T ) 0xA2D4; }
      template<typename T = unsigned long> __forceinline static T totalHitsOnServer() { return ( T ) 0xA2D8; }
      template<typename T = unsigned long> __forceinline static T bInBombZone() { return ( T ) 0x38C4; }
      template<typename T = unsigned long> __forceinline static T bInBuyZone() { return ( T ) 0x38C5; }
      template<typename T = unsigned long> __forceinline static T bInNoDefuseArea() { return ( T ) 0x38C6; }
      template<typename T = unsigned long> __forceinline static T bKilledByTaser() { return ( T ) 0x38DD; }
      template<typename T = unsigned long> __forceinline static T iMoveState() { return ( T ) 0x38E0; }
      template<typename T = unsigned long> __forceinline static T iClass() { return ( T ) 0xB248; }
      template<typename T = unsigned long> __forceinline static T ArmorValue() { return ( T ) 0xB24C; }
      template<typename T = unsigned long> __forceinline static T angEyeAngles() { return ( T ) 0xB250; }
      template<typename T = unsigned long> __forceinline static T bHasDefuser() { return ( T ) 0xB25C; }
      template<typename T = unsigned long> __forceinline static T bNightVisionOn() { return ( T ) 0xA2C9; }
      template<typename T = unsigned long> __forceinline static T bHasNightVision() { return ( T ) 0xA2CA; }
      template<typename T = unsigned long> __forceinline static T bInHostageRescueZone() { return ( T ) 0xB25D; }
      template<typename T = unsigned long> __forceinline static T bIsDefusing() { return ( T ) 0x3898; }
      template<typename T = unsigned long> __forceinline static T bIsGrabbingHostage() { return ( T ) 0x3899; }
      template<typename T = unsigned long> __forceinline static T bIsScoped() { return ( T ) 0x388E; }
      template<typename T = unsigned long> __forceinline static T bIsWalking() { return ( T ) 0x388F; }
      template<typename T = unsigned long> __forceinline static T bResumeZoom() { return ( T ) 0x3890; }
      template<typename T = unsigned long> __forceinline static T fImmuneToGunGameDamageTime() { return ( T ) 0x389C; }
      template<typename T = unsigned long> __forceinline static T bGunGameImmunity() { return ( T ) 0x38A4; }
      template<typename T = unsigned long> __forceinline static T bHasMovedSinceSpawn() { return ( T ) 0x38A5; }
      template<typename T = unsigned long> __forceinline static T bMadeFinalGunGameProgressiveKill() { return ( T ) 0x38A6; }
      template<typename T = unsigned long> __forceinline static T iGunGameProgressiveWeaponIndex() { return ( T ) 0x38A8; }
      template<typename T = unsigned long> __forceinline static T iNumGunGameTRKillPoints() { return ( T ) 0x38AC; }
      template<typename T = unsigned long> __forceinline static T iNumGunGameKillsWithCurrentWeapon() { return ( T ) 0x38B0; }
      template<typename T = unsigned long> __forceinline static T iNumRoundKills() { return ( T ) 0x38B4; }
      template<typename T = unsigned long> __forceinline static T fMolotovUseTime() { return ( T ) 0x38BC; }
      template<typename T = unsigned long> __forceinline static T fMolotovDamageTime() { return ( T ) 0x38C0; }
      template<typename T = unsigned long> __forceinline static T szArmsModel() { return ( T ) 0x38E7; }
      template<typename T = unsigned long> __forceinline static T hCarriedHostage() { return ( T ) 0xA2E4; }
      template<typename T = unsigned long> __forceinline static T hCarriedHostageProp() { return ( T ) 0xA2E8; }
      template<typename T = unsigned long> __forceinline static T bIsRescuing() { return ( T ) 0x389A; }
      template<typename T = unsigned long> __forceinline static T flGroundAccelLinearFracLastTime() { return ( T ) 0xA2D0; }
      template<typename T = unsigned long> __forceinline static T bCanMoveDuringFreezePeriod() { return ( T ) 0x38E4; }
      template<typename T = unsigned long> __forceinline static T isCurrentGunGameLeader() { return ( T ) 0x38E5; }
      template<typename T = unsigned long> __forceinline static T isCurrentGunGameTeamLeader() { return ( T ) 0x38E6; }
      template<typename T = unsigned long> __forceinline static T flGuardianTooFarDistFrac() { return ( T ) 0x38D0; }
      template<typename T = unsigned long> __forceinline static T flDetectedByEnemySensorTime() { return ( T ) 0x38D4; }

      class m_iMatchStats_Kills
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA34C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA350; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA354; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA358; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA35C; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA360; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA364; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA368; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA36C; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA370; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA374; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA378; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA37C; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA380; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA384; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA388; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA38C; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA390; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA394; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA398; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA39C; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA3A0; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA3A4; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA3A8; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA3AC; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA3B0; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA3B4; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA3B8; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA3BC; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA3C0; }
      };

      class m_iMatchStats_Damage
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA3C4; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA3C8; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA3CC; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA3D0; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA3D4; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA3D8; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA3DC; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA3E0; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA3E4; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA3E8; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA3EC; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA3F0; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA3F4; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA3F8; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA3FC; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA400; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA404; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA408; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA40C; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA410; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA414; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA418; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA41C; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA420; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA424; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA428; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA42C; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA430; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA434; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA438; }
      };

      class m_iMatchStats_EquipmentValue
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA43C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA440; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA444; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA448; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA44C; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA450; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA454; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA458; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA45C; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA460; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA464; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA468; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA46C; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA470; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA474; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA478; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA47C; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA480; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA484; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA488; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA48C; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA490; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA494; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA498; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA49C; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA4A0; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA4A4; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA4A8; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA4AC; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA4B0; }
      };

      class m_iMatchStats_MoneySaved
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA4B4; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA4B8; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA4BC; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA4C0; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA4C4; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA4C8; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA4CC; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA4D0; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA4D4; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA4D8; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA4DC; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA4E0; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA4E4; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA4E8; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA4EC; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA4F0; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA4F4; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA4F8; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA4FC; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA500; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA504; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA508; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA50C; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA510; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA514; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA518; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA51C; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA520; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA524; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA528; }
      };

      class m_iMatchStats_KillReward
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA52C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA530; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA534; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA538; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA53C; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA540; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA544; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA548; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA54C; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA550; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA554; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA558; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA55C; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA560; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA564; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA568; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA56C; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA570; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA574; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA578; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA57C; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA580; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA584; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA588; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA58C; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA590; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA594; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA598; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA59C; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA5A0; }
      };

      class m_iMatchStats_LiveTime
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA5A4; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA5A8; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA5AC; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA5B0; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA5B4; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA5B8; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA5BC; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA5C0; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA5C4; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA5C8; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA5CC; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA5D0; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA5D4; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA5D8; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA5DC; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA5E0; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA5E4; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA5E8; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA5EC; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA5F0; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA5F4; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA5F8; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA5FC; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA600; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA604; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA608; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA60C; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA610; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA614; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA618; }
      };

      class m_iMatchStats_Deaths
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA61C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA620; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA624; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA628; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA62C; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA630; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA634; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA638; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA63C; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA640; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA644; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA648; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA64C; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA650; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA654; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA658; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA65C; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA660; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA664; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA668; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA66C; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA670; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA674; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA678; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA67C; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA680; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA684; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA688; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA68C; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA690; }
      };

      class m_iMatchStats_Assists
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA694; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA698; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA69C; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA6A0; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA6A4; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA6A8; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA6AC; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA6B0; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA6B4; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA6B8; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA6BC; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA6C0; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA6C4; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA6C8; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA6CC; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA6D0; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA6D4; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA6D8; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA6DC; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA6E0; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA6E4; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA6E8; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA6EC; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA6F0; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA6F4; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA6F8; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA6FC; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA700; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA704; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA708; }
      };

      class m_iMatchStats_HeadShotKills
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA70C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA710; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA714; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA718; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA71C; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA720; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA724; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA728; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA72C; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA730; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA734; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA738; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA73C; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA740; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA744; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA748; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA74C; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA750; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA754; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA758; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA75C; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA760; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA764; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA768; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA76C; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA770; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA774; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA778; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA77C; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA780; }
      };

      class m_iMatchStats_Objective
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA784; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA788; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA78C; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA790; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA794; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA798; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA79C; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA7A0; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA7A4; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA7A8; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA7AC; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA7B0; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA7B4; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA7B8; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA7BC; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA7C0; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA7C4; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA7C8; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA7CC; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA7D0; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA7D4; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA7D8; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA7DC; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA7E0; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA7E4; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA7E8; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA7EC; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA7F0; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA7F4; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA7F8; }
      };

      class m_iMatchStats_CashEarned
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA7FC; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA800; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA804; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA808; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA80C; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA810; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA814; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA818; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA81C; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA820; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA824; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA828; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA82C; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA830; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA834; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA838; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA83C; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA840; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA844; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA848; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA84C; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA850; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA854; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA858; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA85C; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA860; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA864; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA868; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA86C; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA870; }
      };

      class m_iMatchStats_UtilityDamage
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA874; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA878; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA87C; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA880; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA884; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA888; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA88C; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA890; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA894; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA898; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA89C; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA8A0; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA8A4; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA8A8; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA8AC; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA8B0; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA8B4; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA8B8; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA8BC; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA8C0; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA8C4; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA8C8; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA8CC; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA8D0; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA8D4; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA8D8; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA8DC; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA8E0; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA8E4; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA8E8; }
      };

      class m_iMatchStats_EnemiesFlashed
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA8EC; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA8F0; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA8F4; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA8F8; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA8FC; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA900; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA904; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA908; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA90C; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA910; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA914; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA918; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA91C; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA920; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA924; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA928; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA92C; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA930; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA934; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA938; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA93C; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA940; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA944; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA948; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA94C; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA950; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA954; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA958; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA95C; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA960; }
      };

      class m_rank
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xB210; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xB214; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xB218; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xB21C; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xB220; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xB224; }
      };

      template<typename T = unsigned long> __forceinline static T unMusicID() { return ( T ) 0xB228; }
      template<typename T = unsigned long> __forceinline static T bHasHelmet() { return ( T ) 0xB240; }
      template<typename T = unsigned long> __forceinline static T bHasHeavyArmor() { return ( T ) 0xB241; }
      template<typename T = unsigned long> __forceinline static T nHeavyAssaultSuitCooldownRemaining() { return ( T ) 0xB244; }
      template<typename T = unsigned long> __forceinline static T flFlashDuration() { return ( T ) 0xA308; }
      template<typename T = unsigned long> __forceinline static T flFlashMaxAlpha() { return ( T ) 0xA304; }
      template<typename T = unsigned long> __forceinline static T iProgressBarDuration() { return ( T ) 0xA2B0; }
      template<typename T = unsigned long> __forceinline static T flProgressBarStartTime() { return ( T ) 0xA2B4; }
      template<typename T = unsigned long> __forceinline static T hRagdoll() { return ( T ) 0xA2E0; }
      template<typename T = unsigned long> __forceinline static T cycleLatch() { return ( T ) 0xB378; }
      template<typename T = unsigned long> __forceinline static T unCurrentEquipmentValue() { return ( T ) 0xB208; }
      template<typename T = unsigned long> __forceinline static T unRoundStartEquipmentValue() { return ( T ) 0xB20A; }
      template<typename T = unsigned long> __forceinline static T unFreezetimeEndEquipmentValue() { return ( T ) 0xB20C; }
      template<typename T = unsigned long> __forceinline static T bIsControllingBot() { return ( T ) 0xB8AA; }
      template<typename T = unsigned long> __forceinline static T bHasControlledBotThisRound() { return ( T ) 0xB8B8; }
      template<typename T = unsigned long> __forceinline static T bCanControlObservedBot() { return ( T ) 0xB8AB; }
      template<typename T = unsigned long> __forceinline static T iControlledBotEntIndex() { return ( T ) 0xB8AC; }
      template<typename T = unsigned long> __forceinline static T bIsAssassinationTarget() { return ( T ) 0xB8A9; }
      template<typename T = unsigned long> __forceinline static T bHud_MiniScoreHidden() { return ( T ) 0xB27E; }
      template<typename T = unsigned long> __forceinline static T bHud_RadarHidden() { return ( T ) 0xB27F; }
      template<typename T = unsigned long> __forceinline static T nLastKillerIndex() { return ( T ) 0xB280; }
      template<typename T = unsigned long> __forceinline static T nLastConcurrentKilled() { return ( T ) 0xB284; }
      template<typename T = unsigned long> __forceinline static T nDeathCamMusic() { return ( T ) 0xB288; }
      template<typename T = unsigned long> __forceinline static T bIsHoldingLookAtWeapon() { return ( T ) 0xB80D; }
      template<typename T = unsigned long> __forceinline static T bIsLookingAtWeapon() { return ( T ) 0xB80C; }
      template<typename T = unsigned long> __forceinline static T iNumRoundKillsHeadshots() { return ( T ) 0x38B8; }
      template<typename T = unsigned long> __forceinline static T flLowerBodyYawTarget() { return ( T ) 0x39EC; }
      template<typename T = unsigned long> __forceinline static T bStrafing() { return ( T ) 0x39F0; }
      template<typename T = unsigned long> __forceinline static T flThirdpersonRecoil() { return ( T ) 0xB858; }
   };
};

#endif
