///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEDynamicLight
#define SDK_CTEDynamicLight
#pragma once

class CTEDynamicLight
{
 public:

   class DT_TEDynamicLight
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T r() { return ( T ) 0x20; }
      template<typename T = unsigned long> __forceinline static T g() { return ( T ) 0x24; }
      template<typename T = unsigned long> __forceinline static T b() { return ( T ) 0x28; }
      template<typename T = unsigned long> __forceinline static T exponent() { return ( T ) 0x2C; }
      template<typename T = unsigned long> __forceinline static T fRadius() { return ( T ) 0x1C; }
      template<typename T = unsigned long> __forceinline static T fTime() { return ( T ) 0x30; }
      template<typename T = unsigned long> __forceinline static T fDecay() { return ( T ) 0x34; }
   };
};

#endif
