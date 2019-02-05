///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEBloodStream
#define SDK_CTEBloodStream
#pragma once

class CTEBloodStream
{
 public:

   class DT_TEBloodStream
   {
    public:

      class DT_TEParticleSystem
      {
       public:

         template<typename T = unsigned long> __forceinline static T vecOrigin_0() { return ( T ) 0x10; }
         template<typename T = unsigned long> __forceinline static T vecOrigin_1() { return ( T ) 0x14; }
         template<typename T = unsigned long> __forceinline static T vecOrigin_2() { return ( T ) 0x18; }
      };

      template<typename T = unsigned long> __forceinline static T vecDirection() { return ( T ) 0x1C; }
      template<typename T = unsigned long> __forceinline static T r() { return ( T ) 0x28; }
      template<typename T = unsigned long> __forceinline static T g() { return ( T ) 0x2C; }
      template<typename T = unsigned long> __forceinline static T b() { return ( T ) 0x30; }
      template<typename T = unsigned long> __forceinline static T a() { return ( T ) 0x34; }
      template<typename T = unsigned long> __forceinline static T nAmount() { return ( T ) 0x38; }
   };
};

#endif
