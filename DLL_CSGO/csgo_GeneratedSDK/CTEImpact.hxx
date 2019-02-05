///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEImpact
#define SDK_CTEImpact
#pragma once

class CTEImpact
{
 public:

   class DT_TEImpact
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T vecNormal() { return ( T ) 0x1C; }
      template<typename T = unsigned long> __forceinline static T iType() { return ( T ) 0x28; }
      template<typename T = unsigned long> __forceinline static T ucFlags() { return ( T ) 0x2C; }
   };
};

#endif
