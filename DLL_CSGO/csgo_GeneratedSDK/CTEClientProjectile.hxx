///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEClientProjectile
#define SDK_CTEClientProjectile
#pragma once

class CTEClientProjectile
{
 public:

   class DT_TEClientProjectile
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T vecVelocity() { return ( T ) 0x1C; }
      template<typename T = unsigned long> __forceinline static T nModelIndex() { return ( T ) 0x28; }
      template<typename T = unsigned long> __forceinline static T nLifeTime() { return ( T ) 0x2C; }
      template<typename T = unsigned long> __forceinline static T hOwner() { return ( T ) 0x30; }
   };
};

#endif
