///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEBeamRing
#define SDK_CTEBeamRing
#pragma once

class CTEBeamRing
{
 public:

   class DT_TEBeamRing
   {
    public:

      class DT_BaseBeam
      {
       public:

         template<typename T = unsigned long> __forceinline static T nModelIndex() { return ( T ) 0x10; }
         template<typename T = unsigned long> __forceinline static T nHaloIndex() { return ( T ) 0x14; }
         template<typename T = unsigned long> __forceinline static T nStartFrame() { return ( T ) 0x18; }
         template<typename T = unsigned long> __forceinline static T nFrameRate() { return ( T ) 0x1C; }
         template<typename T = unsigned long> __forceinline static T fLife() { return ( T ) 0x20; }
         template<typename T = unsigned long> __forceinline static T fWidth() { return ( T ) 0x24; }
         template<typename T = unsigned long> __forceinline static T fEndWidth() { return ( T ) 0x28; }
         template<typename T = unsigned long> __forceinline static T nFadeLength() { return ( T ) 0x2C; }
         template<typename T = unsigned long> __forceinline static T fAmplitude() { return ( T ) 0x30; }
         template<typename T = unsigned long> __forceinline static T nSpeed() { return ( T ) 0x44; }
         template<typename T = unsigned long> __forceinline static T r() { return ( T ) 0x34; }
         template<typename T = unsigned long> __forceinline static T g() { return ( T ) 0x38; }
         template<typename T = unsigned long> __forceinline static T b() { return ( T ) 0x3C; }
         template<typename T = unsigned long> __forceinline static T a() { return ( T ) 0x40; }
         template<typename T = unsigned long> __forceinline static T nFlags() { return ( T ) 0x48; }
      };

      template<typename T = unsigned long> __forceinline static T nStartEntity() { return ( T ) 0x4C; }
      template<typename T = unsigned long> __forceinline static T nEndEntity() { return ( T ) 0x50; }
   };
};

#endif
