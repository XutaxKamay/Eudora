///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEBloodSprite
#define SDK_CTEBloodSprite
#pragma once

class CTEBloodSprite
{
 public:

   class DT_TEBloodSprite
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T vecDirection() { return ( T ) 0x1C; }
      template<typename T = unsigned long> __forceinline static T r() { return ( T ) 0x28; }
      template<typename T = unsigned long> __forceinline static T g() { return ( T ) 0x2C; }
      template<typename T = unsigned long> __forceinline static T b() { return ( T ) 0x30; }
      template<typename T = unsigned long> __forceinline static T a() { return ( T ) 0x34; }
      template<typename T = unsigned long> __forceinline static T nSprayModel() { return ( T ) 0x3C; }
      template<typename T = unsigned long> __forceinline static T nDropModel() { return ( T ) 0x38; }
      template<typename T = unsigned long> __forceinline static T nSize() { return ( T ) 0x40; }
   };
};

#endif
