///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEExplosion
#define SDK_CTEExplosion
#pragma once

class CTEExplosion
{
 public:

   class DT_TEExplosion
   {
    public:

      class DT_TEParticleSystem
      {
       public:

         template<typename T = unsigned long> __forceinline static T vecOrigin_0() { return ( T ) 0x10; }
         template<typename T = unsigned long> __forceinline static T vecOrigin_1() { return ( T ) 0x14; }
         template<typename T = unsigned long> __forceinline static T vecOrigin_2() { return ( T ) 0x18; }
      };

      template<typename T = unsigned long> __forceinline static T nModelIndex() { return ( T ) 0x1C; }
      template<typename T = unsigned long> __forceinline static T fScale() { return ( T ) 0x20; }
      template<typename T = unsigned long> __forceinline static T nFrameRate() { return ( T ) 0x24; }
      template<typename T = unsigned long> __forceinline static T nFlags() { return ( T ) 0x28; }
      template<typename T = unsigned long> __forceinline static T vecNormal() { return ( T ) 0x2C; }
      template<typename T = unsigned long> __forceinline static T chMaterialType() { return ( T ) 0x38; }
      template<typename T = unsigned long> __forceinline static T nRadius() { return ( T ) 0x3C; }
      template<typename T = unsigned long> __forceinline static T nMagnitude() { return ( T ) 0x40; }
   };
};

#endif
