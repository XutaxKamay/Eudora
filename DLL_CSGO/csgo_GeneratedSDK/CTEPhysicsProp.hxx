///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEPhysicsProp
#define SDK_CTEPhysicsProp
#pragma once

class CTEPhysicsProp
{
 public:

   class DT_TEPhysicsProp
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T angRotation_0() { return ( T ) 0x1C; }
      template<typename T = unsigned long> __forceinline static T angRotation_1() { return ( T ) 0x20; }
      template<typename T = unsigned long> __forceinline static T angRotation_2() { return ( T ) 0x24; }
      template<typename T = unsigned long> __forceinline static T vecVelocity() { return ( T ) 0x28; }
      template<typename T = unsigned long> __forceinline static T nModelIndex() { return ( T ) 0x34; }
      template<typename T = unsigned long> __forceinline static T nFlags() { return ( T ) 0x3C; }
      template<typename T = unsigned long> __forceinline static T nSkin() { return ( T ) 0x38; }
      template<typename T = unsigned long> __forceinline static T nEffects() { return ( T ) 0x40; }
      template<typename T = unsigned long> __forceinline static T clrRender() { return ( T ) 0x44; }
   };
};

#endif
