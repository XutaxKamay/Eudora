///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CBeam
#define SDK_CBeam
#pragma once

class CBeam
{
 public:

   class DT_Beam
   {
    public:

      template<typename T = unsigned long> __forceinline static T nBeamType() { return ( T ) 0x9F4; }
      template<typename T = unsigned long> __forceinline static T nBeamFlags() { return ( T ) 0x9F8; }
      template<typename T = unsigned long> __forceinline static T nNumBeamEnts() { return ( T ) 0x9E8; }

      class m_hAttachEntity
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x9FC; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA00; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA04; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA08; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA0C; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA10; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA14; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA18; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA1C; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA20; }
      };

      class m_nAttachIndex
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA24; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA28; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA2C; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA30; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA34; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA38; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA3C; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA40; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA44; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA48; }
      };

      template<typename T = unsigned long> __forceinline static T nHaloIndex() { return ( T ) 0x9F0; }
      template<typename T = unsigned long> __forceinline static T fHaloScale() { return ( T ) 0xA58; }
      template<typename T = unsigned long> __forceinline static T fWidth() { return ( T ) 0xA4C; }
      template<typename T = unsigned long> __forceinline static T fEndWidth() { return ( T ) 0xA50; }
      template<typename T = unsigned long> __forceinline static T fFadeLength() { return ( T ) 0xA54; }
      template<typename T = unsigned long> __forceinline static T fAmplitude() { return ( T ) 0xA5C; }
      template<typename T = unsigned long> __forceinline static T fStartFrame() { return ( T ) 0xA60; }
      template<typename T = unsigned long> __forceinline static T fSpeed() { return ( T ) 0xA64; }
      template<typename T = unsigned long> __forceinline static T flFrameRate() { return ( T ) 0x9D8; }
      template<typename T = unsigned long> __forceinline static T flHDRColorScale() { return ( T ) 0x9DC; }
      template<typename T = unsigned long> __forceinline static T clrRender() { return ( T ) 0x70; }
      template<typename T = unsigned long> __forceinline static T nRenderFX() { return ( T ) 0x256; }
      template<typename T = unsigned long> __forceinline static T nRenderMode() { return ( T ) 0x257; }
      template<typename T = unsigned long> __forceinline static T flFrame() { return ( T ) 0xA68; }
      template<typename T = unsigned long> __forceinline static T nClipStyle() { return ( T ) 0xA6C; }
      template<typename T = unsigned long> __forceinline static T vecEndPos() { return ( T ) 0xA70; }
      template<typename T = unsigned long> __forceinline static T nModelIndex() { return ( T ) 0x254; }
      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x134; }
      template<typename T = unsigned long> __forceinline static T moveparent() { return ( T ) 0x144; }
   };
};

#endif
