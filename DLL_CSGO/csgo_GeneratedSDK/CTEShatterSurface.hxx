///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEShatterSurface
#define SDK_CTEShatterSurface
#pragma once

class CTEShatterSurface
{
 public:

   class DT_TEShatterSurface
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T vecAngles() { return ( T ) 0x1C; }
      template<typename T = unsigned long> __forceinline static T vecForce() { return ( T ) 0x28; }
      template<typename T = unsigned long> __forceinline static T vecForcePos() { return ( T ) 0x34; }
      template<typename T = unsigned long> __forceinline static T flWidth() { return ( T ) 0x40; }
      template<typename T = unsigned long> __forceinline static T flHeight() { return ( T ) 0x44; }
      template<typename T = unsigned long> __forceinline static T flShardSize() { return ( T ) 0x48; }
      template<typename T = unsigned long> __forceinline static T nSurfaceType() { return ( T ) 0x50; }
      template<typename T = unsigned long> __forceinline static T uchFrontColor_0() { return ( T ) 0x54; }
      template<typename T = unsigned long> __forceinline static T uchFrontColor_1() { return ( T ) 0x55; }
      template<typename T = unsigned long> __forceinline static T uchFrontColor_2() { return ( T ) 0x56; }
      template<typename T = unsigned long> __forceinline static T uchBackColor_0() { return ( T ) 0x57; }
      template<typename T = unsigned long> __forceinline static T uchBackColor_1() { return ( T ) 0x58; }
      template<typename T = unsigned long> __forceinline static T uchBackColor_2() { return ( T ) 0x59; }
   };
};

#endif
