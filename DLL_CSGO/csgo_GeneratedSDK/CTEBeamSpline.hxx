///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEBeamSpline
#define SDK_CTEBeamSpline
#pragma once

class CTEBeamSpline
{
 public:

   class DT_TEBeamSpline
   {
    public:

      template<typename T = unsigned long> __forceinline static T nPoints() { return ( T ) 0xD0; }
      template<typename T = unsigned long> __forceinline static T vecPoints_0() { return ( T ) 0x10; }
   };
};

#endif
