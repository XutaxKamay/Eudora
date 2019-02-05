///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEShowLine
#define SDK_CTEShowLine
#pragma once

class CTEShowLine
{
 public:

   class DT_TEShowLine
   {
    public:

      class DT_TEParticleSystem
      {
       public:

         template<typename T = unsigned long> __forceinline static T vecOrigin_0() { return ( T ) 0x10; }
         template<typename T = unsigned long> __forceinline static T vecOrigin_1() { return ( T ) 0x14; }
         template<typename T = unsigned long> __forceinline static T vecOrigin_2() { return ( T ) 0x18; }
      };

      template<typename T = unsigned long> __forceinline static T vecEnd() { return ( T ) 0x1C; }
   };
};

#endif
