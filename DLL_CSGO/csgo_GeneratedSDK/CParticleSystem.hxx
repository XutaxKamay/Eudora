///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CParticleSystem
#define SDK_CParticleSystem
#pragma once

class CParticleSystem
{
 public:

   class DT_ParticleSystem
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x134; }
      template<typename T = unsigned long> __forceinline static T fEffects() { return ( T ) 0xEC; }
      template<typename T = unsigned long> __forceinline static T hOwnerEntity() { return ( T ) 0x148; }
      template<typename T = unsigned long> __forceinline static T moveparent() { return ( T ) 0x144; }
      template<typename T = unsigned long> __forceinline static T iParentAttachment() { return ( T ) 0x2E8; }
      template<typename T = unsigned long> __forceinline static T angRotation() { return ( T ) 0x128; }
      template<typename T = unsigned long> __forceinline static T iEffectIndex() { return ( T ) 0x9D8; }
      template<typename T = unsigned long> __forceinline static T bActive() { return ( T ) 0x9E0; }
      template<typename T = unsigned long> __forceinline static T nStopType() { return ( T ) 0x9DC; }
      template<typename T = unsigned long> __forceinline static T flStartTime() { return ( T ) 0x9E4; }
      template<typename T = unsigned long> __forceinline static T szSnapshotFileName() { return ( T ) 0x9E8; }

      class m_vServerControlPoints
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xAEC; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xAF8; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xB04; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xB10; }
      };

      class m_iServerControlPointAssignments
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xB1C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xB1D; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xB1E; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xB1F; }
      };

      class m_hControlPointEnts
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xB30; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xB34; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xB38; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xB3C; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xB40; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xB44; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xB48; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xB4C; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xB50; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xB54; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xB58; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xB5C; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xB60; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xB64; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xB68; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xB6C; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xB70; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xB74; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xB78; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xB7C; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xB80; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xB84; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xB88; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xB8C; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xB90; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xB94; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xB98; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xB9C; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xBA0; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xBA4; }
         template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xBA8; }
         template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xBAC; }
         template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xBB0; }
         template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xBB4; }
         template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xBB8; }
         template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xBBC; }
         template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xBC0; }
         template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xBC4; }
         template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xBC8; }
         template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xBCC; }
         template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xBD0; }
         template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xBD4; }
         template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xBD8; }
         template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xBDC; }
         template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xBE0; }
         template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xBE4; }
         template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xBE8; }
         template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xBEC; }
         template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xBF0; }
         template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xBF4; }
         template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xBF8; }
         template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xBFC; }
         template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xC00; }
         template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xC04; }
         template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xC08; }
         template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xC0C; }
         template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xC10; }
         template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0xC14; }
         template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0xC18; }
         template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0xC1C; }
         template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0xC20; }
         template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0xC24; }
         template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0xC28; }
      };

      class m_iControlPointParents
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xC2C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xC2D; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xC2E; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xC2F; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xC30; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xC31; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xC32; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xC33; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xC34; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xC35; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xC36; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xC37; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xC38; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xC39; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xC3A; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xC3B; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xC3C; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xC3D; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xC3E; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xC3F; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xC40; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xC41; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xC42; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xC43; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xC44; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xC45; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xC46; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xC47; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xC48; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xC49; }
         template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xC4A; }
         template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xC4B; }
         template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xC4C; }
         template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xC4D; }
         template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xC4E; }
         template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xC4F; }
         template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xC50; }
         template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xC51; }
         template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xC52; }
         template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xC53; }
         template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xC54; }
         template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xC55; }
         template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xC56; }
         template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xC57; }
         template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xC58; }
         template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xC59; }
         template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xC5A; }
         template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xC5B; }
         template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xC5C; }
         template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xC5D; }
         template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xC5E; }
         template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xC5F; }
         template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xC60; }
         template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xC61; }
         template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xC62; }
         template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xC63; }
         template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xC64; }
         template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0xC65; }
         template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0xC66; }
         template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0xC67; }
         template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0xC68; }
         template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0xC69; }
         template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0xC6A; }
      };
   };
};

#endif
