///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEBreakModel
#define SDK_CTEBreakModel
#pragma once

class CTEBreakModel
{
 public:

   class DT_TEBreakModel
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T angRotation_0() { return ( T ) 0x1C; }
      template<typename T = unsigned long> __forceinline static T angRotation_1() { return ( T ) 0x20; }
      template<typename T = unsigned long> __forceinline static T angRotation_2() { return ( T ) 0x24; }
      template<typename T = unsigned long> __forceinline static T vecSize() { return ( T ) 0x28; }
      template<typename T = unsigned long> __forceinline static T vecVelocity() { return ( T ) 0x34; }
      template<typename T = unsigned long> __forceinline static T nModelIndex() { return ( T ) 0x44; }
      template<typename T = unsigned long> __forceinline static T nRandomization() { return ( T ) 0x40; }
      template<typename T = unsigned long> __forceinline static T nCount() { return ( T ) 0x48; }
      template<typename T = unsigned long> __forceinline static T fTime() { return ( T ) 0x4C; }
      template<typename T = unsigned long> __forceinline static T nFlags() { return ( T ) 0x50; }
   };
};

#endif
