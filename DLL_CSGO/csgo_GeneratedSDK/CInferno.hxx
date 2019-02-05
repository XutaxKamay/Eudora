///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CInferno
#define SDK_CInferno
#pragma once

class CInferno
{
 public:

   class DT_Inferno
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

      class m_fireXDelta
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x9E4; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x9E8; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x9EC; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x9F0; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x9F4; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x9F8; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x9FC; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA00; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA04; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA08; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA0C; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA10; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA14; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA18; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA1C; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA20; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA24; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA28; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA2C; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA30; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA34; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA38; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA3C; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA40; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA44; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA48; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA4C; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA50; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA54; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA58; }
         template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xA5C; }
         template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xA60; }
         template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xA64; }
         template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xA68; }
         template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xA6C; }
         template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xA70; }
         template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xA74; }
         template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xA78; }
         template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xA7C; }
         template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xA80; }
         template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xA84; }
         template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xA88; }
         template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xA8C; }
         template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xA90; }
         template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xA94; }
         template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xA98; }
         template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xA9C; }
         template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xAA0; }
         template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xAA4; }
         template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xAA8; }
         template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xAAC; }
         template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xAB0; }
         template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xAB4; }
         template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xAB8; }
         template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xABC; }
         template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xAC0; }
         template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xAC4; }
         template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0xAC8; }
         template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0xACC; }
         template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0xAD0; }
         template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0xAD4; }
         template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0xAD8; }
         template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0xADC; }
         template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0xAE0; }
         template<typename T = unsigned long> __forceinline static T _064() { return ( T ) 0xAE4; }
         template<typename T = unsigned long> __forceinline static T _065() { return ( T ) 0xAE8; }
         template<typename T = unsigned long> __forceinline static T _066() { return ( T ) 0xAEC; }
         template<typename T = unsigned long> __forceinline static T _067() { return ( T ) 0xAF0; }
         template<typename T = unsigned long> __forceinline static T _068() { return ( T ) 0xAF4; }
         template<typename T = unsigned long> __forceinline static T _069() { return ( T ) 0xAF8; }
         template<typename T = unsigned long> __forceinline static T _070() { return ( T ) 0xAFC; }
         template<typename T = unsigned long> __forceinline static T _071() { return ( T ) 0xB00; }
         template<typename T = unsigned long> __forceinline static T _072() { return ( T ) 0xB04; }
         template<typename T = unsigned long> __forceinline static T _073() { return ( T ) 0xB08; }
         template<typename T = unsigned long> __forceinline static T _074() { return ( T ) 0xB0C; }
         template<typename T = unsigned long> __forceinline static T _075() { return ( T ) 0xB10; }
         template<typename T = unsigned long> __forceinline static T _076() { return ( T ) 0xB14; }
         template<typename T = unsigned long> __forceinline static T _077() { return ( T ) 0xB18; }
         template<typename T = unsigned long> __forceinline static T _078() { return ( T ) 0xB1C; }
         template<typename T = unsigned long> __forceinline static T _079() { return ( T ) 0xB20; }
         template<typename T = unsigned long> __forceinline static T _080() { return ( T ) 0xB24; }
         template<typename T = unsigned long> __forceinline static T _081() { return ( T ) 0xB28; }
         template<typename T = unsigned long> __forceinline static T _082() { return ( T ) 0xB2C; }
         template<typename T = unsigned long> __forceinline static T _083() { return ( T ) 0xB30; }
         template<typename T = unsigned long> __forceinline static T _084() { return ( T ) 0xB34; }
         template<typename T = unsigned long> __forceinline static T _085() { return ( T ) 0xB38; }
         template<typename T = unsigned long> __forceinline static T _086() { return ( T ) 0xB3C; }
         template<typename T = unsigned long> __forceinline static T _087() { return ( T ) 0xB40; }
         template<typename T = unsigned long> __forceinline static T _088() { return ( T ) 0xB44; }
         template<typename T = unsigned long> __forceinline static T _089() { return ( T ) 0xB48; }
         template<typename T = unsigned long> __forceinline static T _090() { return ( T ) 0xB4C; }
         template<typename T = unsigned long> __forceinline static T _091() { return ( T ) 0xB50; }
         template<typename T = unsigned long> __forceinline static T _092() { return ( T ) 0xB54; }
         template<typename T = unsigned long> __forceinline static T _093() { return ( T ) 0xB58; }
         template<typename T = unsigned long> __forceinline static T _094() { return ( T ) 0xB5C; }
         template<typename T = unsigned long> __forceinline static T _095() { return ( T ) 0xB60; }
         template<typename T = unsigned long> __forceinline static T _096() { return ( T ) 0xB64; }
         template<typename T = unsigned long> __forceinline static T _097() { return ( T ) 0xB68; }
         template<typename T = unsigned long> __forceinline static T _098() { return ( T ) 0xB6C; }
         template<typename T = unsigned long> __forceinline static T _099() { return ( T ) 0xB70; }
      };

      class m_fireYDelta
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xB74; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xB78; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xB7C; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xB80; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xB84; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xB88; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xB8C; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xB90; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xB94; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xB98; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xB9C; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xBA0; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xBA4; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xBA8; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xBAC; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xBB0; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xBB4; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xBB8; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xBBC; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xBC0; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xBC4; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xBC8; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xBCC; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xBD0; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xBD4; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xBD8; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xBDC; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xBE0; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xBE4; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xBE8; }
         template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xBEC; }
         template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xBF0; }
         template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xBF4; }
         template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xBF8; }
         template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xBFC; }
         template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xC00; }
         template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xC04; }
         template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xC08; }
         template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xC0C; }
         template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xC10; }
         template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xC14; }
         template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xC18; }
         template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xC1C; }
         template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xC20; }
         template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xC24; }
         template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xC28; }
         template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xC2C; }
         template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xC30; }
         template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xC34; }
         template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xC38; }
         template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xC3C; }
         template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xC40; }
         template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xC44; }
         template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xC48; }
         template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xC4C; }
         template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xC50; }
         template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xC54; }
         template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0xC58; }
         template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0xC5C; }
         template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0xC60; }
         template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0xC64; }
         template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0xC68; }
         template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0xC6C; }
         template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0xC70; }
         template<typename T = unsigned long> __forceinline static T _064() { return ( T ) 0xC74; }
         template<typename T = unsigned long> __forceinline static T _065() { return ( T ) 0xC78; }
         template<typename T = unsigned long> __forceinline static T _066() { return ( T ) 0xC7C; }
         template<typename T = unsigned long> __forceinline static T _067() { return ( T ) 0xC80; }
         template<typename T = unsigned long> __forceinline static T _068() { return ( T ) 0xC84; }
         template<typename T = unsigned long> __forceinline static T _069() { return ( T ) 0xC88; }
         template<typename T = unsigned long> __forceinline static T _070() { return ( T ) 0xC8C; }
         template<typename T = unsigned long> __forceinline static T _071() { return ( T ) 0xC90; }
         template<typename T = unsigned long> __forceinline static T _072() { return ( T ) 0xC94; }
         template<typename T = unsigned long> __forceinline static T _073() { return ( T ) 0xC98; }
         template<typename T = unsigned long> __forceinline static T _074() { return ( T ) 0xC9C; }
         template<typename T = unsigned long> __forceinline static T _075() { return ( T ) 0xCA0; }
         template<typename T = unsigned long> __forceinline static T _076() { return ( T ) 0xCA4; }
         template<typename T = unsigned long> __forceinline static T _077() { return ( T ) 0xCA8; }
         template<typename T = unsigned long> __forceinline static T _078() { return ( T ) 0xCAC; }
         template<typename T = unsigned long> __forceinline static T _079() { return ( T ) 0xCB0; }
         template<typename T = unsigned long> __forceinline static T _080() { return ( T ) 0xCB4; }
         template<typename T = unsigned long> __forceinline static T _081() { return ( T ) 0xCB8; }
         template<typename T = unsigned long> __forceinline static T _082() { return ( T ) 0xCBC; }
         template<typename T = unsigned long> __forceinline static T _083() { return ( T ) 0xCC0; }
         template<typename T = unsigned long> __forceinline static T _084() { return ( T ) 0xCC4; }
         template<typename T = unsigned long> __forceinline static T _085() { return ( T ) 0xCC8; }
         template<typename T = unsigned long> __forceinline static T _086() { return ( T ) 0xCCC; }
         template<typename T = unsigned long> __forceinline static T _087() { return ( T ) 0xCD0; }
         template<typename T = unsigned long> __forceinline static T _088() { return ( T ) 0xCD4; }
         template<typename T = unsigned long> __forceinline static T _089() { return ( T ) 0xCD8; }
         template<typename T = unsigned long> __forceinline static T _090() { return ( T ) 0xCDC; }
         template<typename T = unsigned long> __forceinline static T _091() { return ( T ) 0xCE0; }
         template<typename T = unsigned long> __forceinline static T _092() { return ( T ) 0xCE4; }
         template<typename T = unsigned long> __forceinline static T _093() { return ( T ) 0xCE8; }
         template<typename T = unsigned long> __forceinline static T _094() { return ( T ) 0xCEC; }
         template<typename T = unsigned long> __forceinline static T _095() { return ( T ) 0xCF0; }
         template<typename T = unsigned long> __forceinline static T _096() { return ( T ) 0xCF4; }
         template<typename T = unsigned long> __forceinline static T _097() { return ( T ) 0xCF8; }
         template<typename T = unsigned long> __forceinline static T _098() { return ( T ) 0xCFC; }
         template<typename T = unsigned long> __forceinline static T _099() { return ( T ) 0xD00; }
      };

      class m_fireZDelta
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xD04; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xD08; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xD0C; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xD10; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xD14; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xD18; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xD1C; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xD20; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xD24; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xD28; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xD2C; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xD30; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xD34; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xD38; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xD3C; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xD40; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xD44; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xD48; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xD4C; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xD50; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xD54; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xD58; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xD5C; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xD60; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xD64; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xD68; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xD6C; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xD70; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xD74; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xD78; }
         template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xD7C; }
         template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xD80; }
         template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xD84; }
         template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xD88; }
         template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xD8C; }
         template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xD90; }
         template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xD94; }
         template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xD98; }
         template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xD9C; }
         template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xDA0; }
         template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xDA4; }
         template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xDA8; }
         template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xDAC; }
         template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xDB0; }
         template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xDB4; }
         template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xDB8; }
         template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xDBC; }
         template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xDC0; }
         template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xDC4; }
         template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xDC8; }
         template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xDCC; }
         template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xDD0; }
         template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xDD4; }
         template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xDD8; }
         template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xDDC; }
         template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xDE0; }
         template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xDE4; }
         template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0xDE8; }
         template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0xDEC; }
         template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0xDF0; }
         template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0xDF4; }
         template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0xDF8; }
         template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0xDFC; }
         template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0xE00; }
         template<typename T = unsigned long> __forceinline static T _064() { return ( T ) 0xE04; }
         template<typename T = unsigned long> __forceinline static T _065() { return ( T ) 0xE08; }
         template<typename T = unsigned long> __forceinline static T _066() { return ( T ) 0xE0C; }
         template<typename T = unsigned long> __forceinline static T _067() { return ( T ) 0xE10; }
         template<typename T = unsigned long> __forceinline static T _068() { return ( T ) 0xE14; }
         template<typename T = unsigned long> __forceinline static T _069() { return ( T ) 0xE18; }
         template<typename T = unsigned long> __forceinline static T _070() { return ( T ) 0xE1C; }
         template<typename T = unsigned long> __forceinline static T _071() { return ( T ) 0xE20; }
         template<typename T = unsigned long> __forceinline static T _072() { return ( T ) 0xE24; }
         template<typename T = unsigned long> __forceinline static T _073() { return ( T ) 0xE28; }
         template<typename T = unsigned long> __forceinline static T _074() { return ( T ) 0xE2C; }
         template<typename T = unsigned long> __forceinline static T _075() { return ( T ) 0xE30; }
         template<typename T = unsigned long> __forceinline static T _076() { return ( T ) 0xE34; }
         template<typename T = unsigned long> __forceinline static T _077() { return ( T ) 0xE38; }
         template<typename T = unsigned long> __forceinline static T _078() { return ( T ) 0xE3C; }
         template<typename T = unsigned long> __forceinline static T _079() { return ( T ) 0xE40; }
         template<typename T = unsigned long> __forceinline static T _080() { return ( T ) 0xE44; }
         template<typename T = unsigned long> __forceinline static T _081() { return ( T ) 0xE48; }
         template<typename T = unsigned long> __forceinline static T _082() { return ( T ) 0xE4C; }
         template<typename T = unsigned long> __forceinline static T _083() { return ( T ) 0xE50; }
         template<typename T = unsigned long> __forceinline static T _084() { return ( T ) 0xE54; }
         template<typename T = unsigned long> __forceinline static T _085() { return ( T ) 0xE58; }
         template<typename T = unsigned long> __forceinline static T _086() { return ( T ) 0xE5C; }
         template<typename T = unsigned long> __forceinline static T _087() { return ( T ) 0xE60; }
         template<typename T = unsigned long> __forceinline static T _088() { return ( T ) 0xE64; }
         template<typename T = unsigned long> __forceinline static T _089() { return ( T ) 0xE68; }
         template<typename T = unsigned long> __forceinline static T _090() { return ( T ) 0xE6C; }
         template<typename T = unsigned long> __forceinline static T _091() { return ( T ) 0xE70; }
         template<typename T = unsigned long> __forceinline static T _092() { return ( T ) 0xE74; }
         template<typename T = unsigned long> __forceinline static T _093() { return ( T ) 0xE78; }
         template<typename T = unsigned long> __forceinline static T _094() { return ( T ) 0xE7C; }
         template<typename T = unsigned long> __forceinline static T _095() { return ( T ) 0xE80; }
         template<typename T = unsigned long> __forceinline static T _096() { return ( T ) 0xE84; }
         template<typename T = unsigned long> __forceinline static T _097() { return ( T ) 0xE88; }
         template<typename T = unsigned long> __forceinline static T _098() { return ( T ) 0xE8C; }
         template<typename T = unsigned long> __forceinline static T _099() { return ( T ) 0xE90; }
      };

      class m_bFireIsBurning
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xE94; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xE95; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xE96; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xE97; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xE98; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xE99; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xE9A; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xE9B; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xE9C; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xE9D; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xE9E; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xE9F; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xEA0; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xEA1; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xEA2; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xEA3; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xEA4; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xEA5; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xEA6; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xEA7; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xEA8; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xEA9; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xEAA; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xEAB; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xEAC; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xEAD; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xEAE; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xEAF; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xEB0; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xEB1; }
         template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xEB2; }
         template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xEB3; }
         template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xEB4; }
         template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xEB5; }
         template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xEB6; }
         template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xEB7; }
         template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xEB8; }
         template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xEB9; }
         template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xEBA; }
         template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xEBB; }
         template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xEBC; }
         template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xEBD; }
         template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xEBE; }
         template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xEBF; }
         template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xEC0; }
         template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xEC1; }
         template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xEC2; }
         template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xEC3; }
         template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xEC4; }
         template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xEC5; }
         template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xEC6; }
         template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xEC7; }
         template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xEC8; }
         template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xEC9; }
         template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xECA; }
         template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xECB; }
         template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xECC; }
         template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0xECD; }
         template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0xECE; }
         template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0xECF; }
         template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0xED0; }
         template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0xED1; }
         template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0xED2; }
         template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0xED3; }
         template<typename T = unsigned long> __forceinline static T _064() { return ( T ) 0xED4; }
         template<typename T = unsigned long> __forceinline static T _065() { return ( T ) 0xED5; }
         template<typename T = unsigned long> __forceinline static T _066() { return ( T ) 0xED6; }
         template<typename T = unsigned long> __forceinline static T _067() { return ( T ) 0xED7; }
         template<typename T = unsigned long> __forceinline static T _068() { return ( T ) 0xED8; }
         template<typename T = unsigned long> __forceinline static T _069() { return ( T ) 0xED9; }
         template<typename T = unsigned long> __forceinline static T _070() { return ( T ) 0xEDA; }
         template<typename T = unsigned long> __forceinline static T _071() { return ( T ) 0xEDB; }
         template<typename T = unsigned long> __forceinline static T _072() { return ( T ) 0xEDC; }
         template<typename T = unsigned long> __forceinline static T _073() { return ( T ) 0xEDD; }
         template<typename T = unsigned long> __forceinline static T _074() { return ( T ) 0xEDE; }
         template<typename T = unsigned long> __forceinline static T _075() { return ( T ) 0xEDF; }
         template<typename T = unsigned long> __forceinline static T _076() { return ( T ) 0xEE0; }
         template<typename T = unsigned long> __forceinline static T _077() { return ( T ) 0xEE1; }
         template<typename T = unsigned long> __forceinline static T _078() { return ( T ) 0xEE2; }
         template<typename T = unsigned long> __forceinline static T _079() { return ( T ) 0xEE3; }
         template<typename T = unsigned long> __forceinline static T _080() { return ( T ) 0xEE4; }
         template<typename T = unsigned long> __forceinline static T _081() { return ( T ) 0xEE5; }
         template<typename T = unsigned long> __forceinline static T _082() { return ( T ) 0xEE6; }
         template<typename T = unsigned long> __forceinline static T _083() { return ( T ) 0xEE7; }
         template<typename T = unsigned long> __forceinline static T _084() { return ( T ) 0xEE8; }
         template<typename T = unsigned long> __forceinline static T _085() { return ( T ) 0xEE9; }
         template<typename T = unsigned long> __forceinline static T _086() { return ( T ) 0xEEA; }
         template<typename T = unsigned long> __forceinline static T _087() { return ( T ) 0xEEB; }
         template<typename T = unsigned long> __forceinline static T _088() { return ( T ) 0xEEC; }
         template<typename T = unsigned long> __forceinline static T _089() { return ( T ) 0xEED; }
         template<typename T = unsigned long> __forceinline static T _090() { return ( T ) 0xEEE; }
         template<typename T = unsigned long> __forceinline static T _091() { return ( T ) 0xEEF; }
         template<typename T = unsigned long> __forceinline static T _092() { return ( T ) 0xEF0; }
         template<typename T = unsigned long> __forceinline static T _093() { return ( T ) 0xEF1; }
         template<typename T = unsigned long> __forceinline static T _094() { return ( T ) 0xEF2; }
         template<typename T = unsigned long> __forceinline static T _095() { return ( T ) 0xEF3; }
         template<typename T = unsigned long> __forceinline static T _096() { return ( T ) 0xEF4; }
         template<typename T = unsigned long> __forceinline static T _097() { return ( T ) 0xEF5; }
         template<typename T = unsigned long> __forceinline static T _098() { return ( T ) 0xEF6; }
         template<typename T = unsigned long> __forceinline static T _099() { return ( T ) 0xEF7; }
      };

      template<typename T = unsigned long> __forceinline static T fireCount() { return ( T ) 0x13A8; }
   };
};

#endif
