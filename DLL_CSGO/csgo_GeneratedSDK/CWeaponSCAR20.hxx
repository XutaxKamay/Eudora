///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CWeaponSCAR20
#define SDK_CWeaponSCAR20
#pragma once

class CWeaponSCAR20
{
 public:

   class DT_WeaponSCAR20
   {
    public:

      class DT_WeaponCSBaseGun
      {
       public:

         class DT_WeaponCSBase
         {
          public:

            class DT_BaseCombatWeapon
            {
             public:

               class DT_EconEntity
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

                  class DT_AttributeContainer
                  {
                   public:

                     template<typename T = unsigned long> __forceinline static T hOuter() { return ( T ) 0x2D8C; }
                     template<typename T = unsigned long> __forceinline static T ProviderType() { return ( T ) 0x2D94; }
                     template<typename T = unsigned long> __forceinline static T iReapplyProvisionParity() { return ( T ) 0x2D88; }

                     class DT_ScriptCreatedItem
                     {
                      public:

                        template<typename T = unsigned long> __forceinline static T iItemDefinitionIndex() { return ( T ) 0x2F9A; }
                        template<typename T = unsigned long> __forceinline static T iEntityLevel() { return ( T ) 0x2FA0; }
                        template<typename T = unsigned long> __forceinline static T iItemIDHigh() { return ( T ) 0x2FB0; }
                        template<typename T = unsigned long> __forceinline static T iItemIDLow() { return ( T ) 0x2FB4; }
                        template<typename T = unsigned long> __forceinline static T iAccountID() { return ( T ) 0x2FB8; }
                        template<typename T = unsigned long> __forceinline static T iEntityQuality() { return ( T ) 0x2F9C; }
                        template<typename T = unsigned long> __forceinline static T bInitialized() { return ( T ) 0x2FC4; }
                        template<typename T = unsigned long> __forceinline static T szCustomName() { return ( T ) 0x302C; }

                        class DT_AttributeList
                        {
                         public:

                           class _ST_m_Attributes_32
                           {
                            public:

                              class _LPT_m_Attributes_32
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T lengthprop32() { return ( T ) 0x3010; }
                              };

                              class DT_ScriptCreatedAttribute_000
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3018; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x301C; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x301C; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3020; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3024; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3028; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_000() { return ( T ) 0x3014; }

                              class DT_ScriptCreatedAttribute_001
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x301C; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3020; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3020; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3024; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3028; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x302C; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_001() { return ( T ) 0x3018; }

                              class DT_ScriptCreatedAttribute_002
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3020; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3024; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3024; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3028; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x302C; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3030; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_002() { return ( T ) 0x301C; }

                              class DT_ScriptCreatedAttribute_003
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3024; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3028; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3028; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x302C; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3030; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3034; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_003() { return ( T ) 0x3020; }

                              class DT_ScriptCreatedAttribute_004
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3028; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x302C; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x302C; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3030; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3034; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3038; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_004() { return ( T ) 0x3024; }

                              class DT_ScriptCreatedAttribute_005
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x302C; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3030; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3030; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3034; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3038; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x303C; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_005() { return ( T ) 0x3028; }

                              class DT_ScriptCreatedAttribute_006
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3030; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3034; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3034; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3038; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x303C; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3040; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_006() { return ( T ) 0x302C; }

                              class DT_ScriptCreatedAttribute_007
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3034; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3038; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3038; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x303C; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3040; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3044; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_007() { return ( T ) 0x3030; }

                              class DT_ScriptCreatedAttribute_008
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3038; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x303C; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x303C; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3040; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3044; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3048; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_008() { return ( T ) 0x3034; }

                              class DT_ScriptCreatedAttribute_009
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x303C; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3040; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3040; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3044; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3048; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x304C; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_009() { return ( T ) 0x3038; }

                              class DT_ScriptCreatedAttribute_010
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3040; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3044; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3044; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3048; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x304C; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3050; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_010() { return ( T ) 0x303C; }

                              class DT_ScriptCreatedAttribute_011
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3044; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3048; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3048; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x304C; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3050; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3054; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_011() { return ( T ) 0x3040; }

                              class DT_ScriptCreatedAttribute_012
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3048; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x304C; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x304C; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3050; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3054; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3058; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_012() { return ( T ) 0x3044; }

                              class DT_ScriptCreatedAttribute_013
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x304C; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3050; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3050; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3054; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3058; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x305C; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_013() { return ( T ) 0x3048; }

                              class DT_ScriptCreatedAttribute_014
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3050; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3054; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3054; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3058; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x305C; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3060; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_014() { return ( T ) 0x304C; }

                              class DT_ScriptCreatedAttribute_015
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3054; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3058; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3058; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x305C; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3060; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3064; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_015() { return ( T ) 0x3050; }

                              class DT_ScriptCreatedAttribute_016
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3058; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x305C; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x305C; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3060; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3064; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3068; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_016() { return ( T ) 0x3054; }

                              class DT_ScriptCreatedAttribute_017
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x305C; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3060; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3060; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3064; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3068; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x306C; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_017() { return ( T ) 0x3058; }

                              class DT_ScriptCreatedAttribute_018
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3060; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3064; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3064; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3068; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x306C; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3070; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_018() { return ( T ) 0x305C; }

                              class DT_ScriptCreatedAttribute_019
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3064; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3068; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3068; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x306C; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3070; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3074; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_019() { return ( T ) 0x3060; }

                              class DT_ScriptCreatedAttribute_020
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3068; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x306C; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x306C; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3070; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3074; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3078; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_020() { return ( T ) 0x3064; }

                              class DT_ScriptCreatedAttribute_021
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x306C; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3070; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3070; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3074; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3078; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x307C; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_021() { return ( T ) 0x3068; }

                              class DT_ScriptCreatedAttribute_022
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3070; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3074; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3074; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3078; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x307C; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3080; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_022() { return ( T ) 0x306C; }

                              class DT_ScriptCreatedAttribute_023
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3074; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3078; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3078; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x307C; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3080; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3084; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_023() { return ( T ) 0x3070; }

                              class DT_ScriptCreatedAttribute_024
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3078; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x307C; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x307C; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3080; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3084; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3088; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_024() { return ( T ) 0x3074; }

                              class DT_ScriptCreatedAttribute_025
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x307C; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3080; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3080; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3084; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3088; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x308C; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_025() { return ( T ) 0x3078; }

                              class DT_ScriptCreatedAttribute_026
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3080; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3084; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3084; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3088; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x308C; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3090; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_026() { return ( T ) 0x307C; }

                              class DT_ScriptCreatedAttribute_027
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3084; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3088; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3088; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x308C; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3090; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3094; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_027() { return ( T ) 0x3080; }

                              class DT_ScriptCreatedAttribute_028
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3088; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x308C; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x308C; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3090; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3094; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x3098; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_028() { return ( T ) 0x3084; }

                              class DT_ScriptCreatedAttribute_029
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x308C; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3090; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3090; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3094; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x3098; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x309C; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_029() { return ( T ) 0x3088; }

                              class DT_ScriptCreatedAttribute_030
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3090; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3094; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3094; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x3098; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x309C; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x30A0; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_030() { return ( T ) 0x308C; }

                              class DT_ScriptCreatedAttribute_031
                              {
                               public:

                                 template<typename T = unsigned long> __forceinline static T iAttributeDefinitionIndex() { return ( T ) 0x3094; }
                                 template<typename T = unsigned long> __forceinline static T iRawValue32() { return ( T ) 0x3098; }
                                 template<typename T = unsigned long> __forceinline static T flValue() { return ( T ) 0x3098; }
                                 template<typename T = unsigned long> __forceinline static T iRawInitialValue32() { return ( T ) 0x309C; }
                                 template<typename T = unsigned long> __forceinline static T nRefundableCurrency() { return ( T ) 0x30A0; }
                                 template<typename T = unsigned long> __forceinline static T bSetBonus() { return ( T ) 0x30A4; }
                              };

                              template<typename T = unsigned long> __forceinline static T _ST_Attributes_32_031() { return ( T ) 0x3090; }
                           };
                        };
                     };
                  };

                  template<typename T = unsigned long> __forceinline static T OriginalOwnerXuidLow() { return ( T ) 0x31A0; }
                  template<typename T = unsigned long> __forceinline static T OriginalOwnerXuidHigh() { return ( T ) 0x31A4; }
                  template<typename T = unsigned long> __forceinline static T nFallbackPaintKit() { return ( T ) 0x31A8; }
                  template<typename T = unsigned long> __forceinline static T nFallbackSeed() { return ( T ) 0x31AC; }
                  template<typename T = unsigned long> __forceinline static T flFallbackWear() { return ( T ) 0x31B0; }
                  template<typename T = unsigned long> __forceinline static T nFallbackStatTrak() { return ( T ) 0x31B4; }
               };

               class DT_LocalWeaponData
               {
                public:

                  template<typename T = unsigned long> __forceinline static T iPrimaryAmmoType() { return ( T ) 0x322C; }
                  template<typename T = unsigned long> __forceinline static T iSecondaryAmmoType() { return ( T ) 0x3230; }
                  template<typename T = unsigned long> __forceinline static T nViewModelIndex() { return ( T ) 0x3204; }
                  template<typename T = unsigned long> __forceinline static T bFlipViewModel() { return ( T ) 0x3294; }
                  template<typename T = unsigned long> __forceinline static T iWeaponOrigin() { return ( T ) 0x3298; }
                  template<typename T = unsigned long> __forceinline static T iWeaponModule() { return ( T ) 0x321C; }
               };

               class DT_LocalActiveWeaponData
               {
                public:

                  template<typename T = unsigned long> __forceinline static T flNextPrimaryAttack() { return ( T ) 0x3208; }
                  template<typename T = unsigned long> __forceinline static T flNextSecondaryAttack() { return ( T ) 0x320C; }
                  template<typename T = unsigned long> __forceinline static T nNextThinkTick() { return ( T ) 0xF8; }
                  template<typename T = unsigned long> __forceinline static T flTimeWeaponIdle() { return ( T ) 0x3244; }
               };

               template<typename T = unsigned long> __forceinline static T iViewModelIndex() { return ( T ) 0x3210; }
               template<typename T = unsigned long> __forceinline static T iWorldModelIndex() { return ( T ) 0x3214; }
               template<typename T = unsigned long> __forceinline static T iWorldDroppedModelIndex() { return ( T ) 0x3218; }
               template<typename T = unsigned long> __forceinline static T iState() { return ( T ) 0x3228; }
               template<typename T = unsigned long> __forceinline static T hOwner() { return ( T ) 0x3200; }
               template<typename T = unsigned long> __forceinline static T iClip1() { return ( T ) 0x3234; }
               template<typename T = unsigned long> __forceinline static T iClip2() { return ( T ) 0x3238; }
               template<typename T = unsigned long> __forceinline static T iPrimaryReserveAmmoCount() { return ( T ) 0x323C; }
               template<typename T = unsigned long> __forceinline static T iSecondaryReserveAmmoCount() { return ( T ) 0x3240; }
               template<typename T = unsigned long> __forceinline static T hWeaponWorldModel() { return ( T ) 0x3224; }
               template<typename T = unsigned long> __forceinline static T iNumEmptyAttacks() { return ( T ) 0x3220; }
            };

            template<typename T = unsigned long> __forceinline static T weaponMode() { return ( T ) 0x32DC; }
            template<typename T = unsigned long> __forceinline static T fAccuracyPenalty() { return ( T ) 0x32E0; }
            template<typename T = unsigned long> __forceinline static T fLastShotTime() { return ( T ) 0x333C; }
            template<typename T = unsigned long> __forceinline static T iRecoilIndex() { return ( T ) 0x32EC; }
            template<typename T = unsigned long> __forceinline static T flRecoilIndex() { return ( T ) 0x32F0; }
            template<typename T = unsigned long> __forceinline static T hPrevOwner() { return ( T ) 0x3318; }
            template<typename T = unsigned long> __forceinline static T bBurstMode() { return ( T ) 0x32F4; }
            template<typename T = unsigned long> __forceinline static T flPostponeFireReadyTime() { return ( T ) 0x32F8; }
            template<typename T = unsigned long> __forceinline static T bReloadVisuallyComplete() { return ( T ) 0x32FC; }
            template<typename T = unsigned long> __forceinline static T bSilencerOn() { return ( T ) 0x32FD; }
            template<typename T = unsigned long> __forceinline static T flDoneSwitchingSilencer() { return ( T ) 0x3300; }
            template<typename T = unsigned long> __forceinline static T iOriginalTeamNumber() { return ( T ) 0x3308; }
            template<typename T = unsigned long> __forceinline static T iIronSightMode() { return ( T ) 0x3358; }
         };

         template<typename T = unsigned long> __forceinline static T zoomLevel() { return ( T ) 0x3360; }
         template<typename T = unsigned long> __forceinline static T iBurstShotsRemaining() { return ( T ) 0x3364; }
      };
   };
};

#endif
