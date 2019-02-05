///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CLightGlow
#define SDK_CLightGlow
#pragma once

class CLightGlow
{
 public:

   class DT_LightGlow
   {
    public:

      template<typename T = unsigned long> __forceinline static T clrRender() { return ( T ) 0x70; }
      template<typename T = unsigned long> __forceinline static T nHorizontalSize() { return ( T ) 0x9D8; }
      template<typename T = unsigned long> __forceinline static T nVerticalSize() { return ( T ) 0x9DC; }
      template<typename T = unsigned long> __forceinline static T nMinDist() { return ( T ) 0x9E0; }
      template<typename T = unsigned long> __forceinline static T nMaxDist() { return ( T ) 0x9E4; }
      template<typename T = unsigned long> __forceinline static T nOuterMaxDist() { return ( T ) 0x9E8; }
      template<typename T = unsigned long> __forceinline static T spawnflags() { return ( T ) 0x9EC; }
      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x134; }
      template<typename T = unsigned long> __forceinline static T angRotation() { return ( T ) 0x128; }
      template<typename T = unsigned long> __forceinline static T moveparent() { return ( T ) 0x144; }
      template<typename T = unsigned long> __forceinline static T flGlowProxySize() { return ( T ) 0xAC0; }
   };
};

#endif
