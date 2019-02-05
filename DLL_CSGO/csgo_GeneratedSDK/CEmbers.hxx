///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CEmbers
#define SDK_CEmbers
#pragma once

class CEmbers
{
 public:

   class DT_Embers
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

      template<typename T = unsigned long> __forceinline static T nDensity() { return ( T ) 0x9D8; }
      template<typename T = unsigned long> __forceinline static T nLifetime() { return ( T ) 0x9DC; }
      template<typename T = unsigned long> __forceinline static T nSpeed() { return ( T ) 0x9E0; }
      template<typename T = unsigned long> __forceinline static T bEmit() { return ( T ) 0x9E4; }
   };
};

#endif
