///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CParticleFire
#define SDK_CParticleFire
#pragma once

class CParticleFire
{
 public:

   class DT_ParticleFire
   {
    public:

      template<typename T = unsigned long> __forceinline static T vOrigin() { return ( T ) 0xACC; }
      template<typename T = unsigned long> __forceinline static T vDirection() { return ( T ) 0xAD8; }
   };
};

#endif
