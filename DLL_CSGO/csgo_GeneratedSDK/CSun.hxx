///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CSun
#define SDK_CSun
#pragma once

class CSun
{
 public:

   class DT_Sun
   {
    public:

      template<typename T = unsigned long> __forceinline static T clrRender() { return ( T ) 0x70; }
      template<typename T = unsigned long> __forceinline static T clrOverlay() { return ( T ) 0xB30; }
      template<typename T = unsigned long> __forceinline static T vDirection() { return ( T ) 0xB3C; }
      template<typename T = unsigned long> __forceinline static T bOn() { return ( T ) 0xB48; }
      template<typename T = unsigned long> __forceinline static T nSize() { return ( T ) 0xB34; }
      template<typename T = unsigned long> __forceinline static T nOverlaySize() { return ( T ) 0xB38; }
      template<typename T = unsigned long> __forceinline static T nMaterial() { return ( T ) 0xB4C; }
      template<typename T = unsigned long> __forceinline static T nOverlayMaterial() { return ( T ) 0xB50; }
   };
};

#endif
