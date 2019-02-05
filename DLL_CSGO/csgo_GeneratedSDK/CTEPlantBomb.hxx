///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEPlantBomb
#define SDK_CTEPlantBomb
#pragma once

class CTEPlantBomb
{
 public:

   class DT_TEPlantBomb
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x14; }
      template<typename T = unsigned long> __forceinline static T iPlayer() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T option() { return ( T ) 0x20; }
   };
};

#endif
