///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CFEPlayerDecal
#define SDK_CFEPlayerDecal
#pragma once

class CFEPlayerDecal
{
 public:

   class DT_FEPlayerDecal
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

      template<typename T = unsigned long> __forceinline static T nUniqueID() { return ( T ) 0x9D8; }
      template<typename T = unsigned long> __forceinline static T unAccountID() { return ( T ) 0x9DC; }
      template<typename T = unsigned long> __forceinline static T unTraceID() { return ( T ) 0x9E0; }
      template<typename T = unsigned long> __forceinline static T rtGcTime() { return ( T ) 0x9E4; }
      template<typename T = unsigned long> __forceinline static T vecEndPos() { return ( T ) 0x9E8; }
      template<typename T = unsigned long> __forceinline static T vecStart() { return ( T ) 0x9F4; }
      template<typename T = unsigned long> __forceinline static T vecRight() { return ( T ) 0xA00; }
      template<typename T = unsigned long> __forceinline static T vecNormal() { return ( T ) 0xA0C; }
      template<typename T = unsigned long> __forceinline static T nEntity() { return ( T ) 0xA1C; }
      template<typename T = unsigned long> __forceinline static T nPlayer() { return ( T ) 0xA18; }
      template<typename T = unsigned long> __forceinline static T nHitbox() { return ( T ) 0xA20; }
      template<typename T = unsigned long> __forceinline static T nTintID() { return ( T ) 0xA24; }
      template<typename T = unsigned long> __forceinline static T flCreationTime() { return ( T ) 0xA28; }
      template<typename T = unsigned long> __forceinline static T nVersion() { return ( T ) 0xA2C; }

      class m_ubSignature
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA2D; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA2E; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA2F; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA30; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA31; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA32; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA33; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA34; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA35; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA36; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA37; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA38; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA39; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA3A; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA3B; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA3C; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA3D; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA3E; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA3F; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA40; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA41; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA42; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA43; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA44; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA45; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA46; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA47; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA48; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA49; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA4A; }
         template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xA4B; }
         template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xA4C; }
         template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xA4D; }
         template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xA4E; }
         template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xA4F; }
         template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xA50; }
         template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xA51; }
         template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xA52; }
         template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xA53; }
         template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xA54; }
         template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xA55; }
         template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xA56; }
         template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xA57; }
         template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xA58; }
         template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xA59; }
         template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xA5A; }
         template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xA5B; }
         template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xA5C; }
         template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xA5D; }
         template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xA5E; }
         template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xA5F; }
         template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xA60; }
         template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xA61; }
         template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xA62; }
         template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xA63; }
         template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xA64; }
         template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xA65; }
         template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0xA66; }
         template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0xA67; }
         template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0xA68; }
         template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0xA69; }
         template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0xA6A; }
         template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0xA6B; }
         template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0xA6C; }
         template<typename T = unsigned long> __forceinline static T _064() { return ( T ) 0xA6D; }
         template<typename T = unsigned long> __forceinline static T _065() { return ( T ) 0xA6E; }
         template<typename T = unsigned long> __forceinline static T _066() { return ( T ) 0xA6F; }
         template<typename T = unsigned long> __forceinline static T _067() { return ( T ) 0xA70; }
         template<typename T = unsigned long> __forceinline static T _068() { return ( T ) 0xA71; }
         template<typename T = unsigned long> __forceinline static T _069() { return ( T ) 0xA72; }
         template<typename T = unsigned long> __forceinline static T _070() { return ( T ) 0xA73; }
         template<typename T = unsigned long> __forceinline static T _071() { return ( T ) 0xA74; }
         template<typename T = unsigned long> __forceinline static T _072() { return ( T ) 0xA75; }
         template<typename T = unsigned long> __forceinline static T _073() { return ( T ) 0xA76; }
         template<typename T = unsigned long> __forceinline static T _074() { return ( T ) 0xA77; }
         template<typename T = unsigned long> __forceinline static T _075() { return ( T ) 0xA78; }
         template<typename T = unsigned long> __forceinline static T _076() { return ( T ) 0xA79; }
         template<typename T = unsigned long> __forceinline static T _077() { return ( T ) 0xA7A; }
         template<typename T = unsigned long> __forceinline static T _078() { return ( T ) 0xA7B; }
         template<typename T = unsigned long> __forceinline static T _079() { return ( T ) 0xA7C; }
         template<typename T = unsigned long> __forceinline static T _080() { return ( T ) 0xA7D; }
         template<typename T = unsigned long> __forceinline static T _081() { return ( T ) 0xA7E; }
         template<typename T = unsigned long> __forceinline static T _082() { return ( T ) 0xA7F; }
         template<typename T = unsigned long> __forceinline static T _083() { return ( T ) 0xA80; }
         template<typename T = unsigned long> __forceinline static T _084() { return ( T ) 0xA81; }
         template<typename T = unsigned long> __forceinline static T _085() { return ( T ) 0xA82; }
         template<typename T = unsigned long> __forceinline static T _086() { return ( T ) 0xA83; }
         template<typename T = unsigned long> __forceinline static T _087() { return ( T ) 0xA84; }
         template<typename T = unsigned long> __forceinline static T _088() { return ( T ) 0xA85; }
         template<typename T = unsigned long> __forceinline static T _089() { return ( T ) 0xA86; }
         template<typename T = unsigned long> __forceinline static T _090() { return ( T ) 0xA87; }
         template<typename T = unsigned long> __forceinline static T _091() { return ( T ) 0xA88; }
         template<typename T = unsigned long> __forceinline static T _092() { return ( T ) 0xA89; }
         template<typename T = unsigned long> __forceinline static T _093() { return ( T ) 0xA8A; }
         template<typename T = unsigned long> __forceinline static T _094() { return ( T ) 0xA8B; }
         template<typename T = unsigned long> __forceinline static T _095() { return ( T ) 0xA8C; }
         template<typename T = unsigned long> __forceinline static T _096() { return ( T ) 0xA8D; }
         template<typename T = unsigned long> __forceinline static T _097() { return ( T ) 0xA8E; }
         template<typename T = unsigned long> __forceinline static T _098() { return ( T ) 0xA8F; }
         template<typename T = unsigned long> __forceinline static T _099() { return ( T ) 0xA90; }
         template<typename T = unsigned long> __forceinline static T _100() { return ( T ) 0xA91; }
         template<typename T = unsigned long> __forceinline static T _101() { return ( T ) 0xA92; }
         template<typename T = unsigned long> __forceinline static T _102() { return ( T ) 0xA93; }
         template<typename T = unsigned long> __forceinline static T _103() { return ( T ) 0xA94; }
         template<typename T = unsigned long> __forceinline static T _104() { return ( T ) 0xA95; }
         template<typename T = unsigned long> __forceinline static T _105() { return ( T ) 0xA96; }
         template<typename T = unsigned long> __forceinline static T _106() { return ( T ) 0xA97; }
         template<typename T = unsigned long> __forceinline static T _107() { return ( T ) 0xA98; }
         template<typename T = unsigned long> __forceinline static T _108() { return ( T ) 0xA99; }
         template<typename T = unsigned long> __forceinline static T _109() { return ( T ) 0xA9A; }
         template<typename T = unsigned long> __forceinline static T _110() { return ( T ) 0xA9B; }
         template<typename T = unsigned long> __forceinline static T _111() { return ( T ) 0xA9C; }
         template<typename T = unsigned long> __forceinline static T _112() { return ( T ) 0xA9D; }
         template<typename T = unsigned long> __forceinline static T _113() { return ( T ) 0xA9E; }
         template<typename T = unsigned long> __forceinline static T _114() { return ( T ) 0xA9F; }
         template<typename T = unsigned long> __forceinline static T _115() { return ( T ) 0xAA0; }
         template<typename T = unsigned long> __forceinline static T _116() { return ( T ) 0xAA1; }
         template<typename T = unsigned long> __forceinline static T _117() { return ( T ) 0xAA2; }
         template<typename T = unsigned long> __forceinline static T _118() { return ( T ) 0xAA3; }
         template<typename T = unsigned long> __forceinline static T _119() { return ( T ) 0xAA4; }
         template<typename T = unsigned long> __forceinline static T _120() { return ( T ) 0xAA5; }
         template<typename T = unsigned long> __forceinline static T _121() { return ( T ) 0xAA6; }
         template<typename T = unsigned long> __forceinline static T _122() { return ( T ) 0xAA7; }
         template<typename T = unsigned long> __forceinline static T _123() { return ( T ) 0xAA8; }
         template<typename T = unsigned long> __forceinline static T _124() { return ( T ) 0xAA9; }
         template<typename T = unsigned long> __forceinline static T _125() { return ( T ) 0xAAA; }
         template<typename T = unsigned long> __forceinline static T _126() { return ( T ) 0xAAB; }
         template<typename T = unsigned long> __forceinline static T _127() { return ( T ) 0xAAC; }
      };
   };
};

#endif
