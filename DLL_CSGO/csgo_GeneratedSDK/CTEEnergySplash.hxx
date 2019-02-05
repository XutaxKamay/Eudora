///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEEnergySplash
#define SDK_CTEEnergySplash
#pragma once

class CTEEnergySplash
{
 public:

   class DT_TEEnergySplash
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecPos() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T vecDir() { return ( T ) 0x1C; }
      template<typename T = unsigned long> __forceinline static T bExplosive() { return ( T ) 0x28; }
   };
};

#endif
