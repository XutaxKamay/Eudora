///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEPlayerAnimEvent
#define SDK_CTEPlayerAnimEvent
#pragma once

class CTEPlayerAnimEvent
{
 public:

   class DT_TEPlayerAnimEvent
   {
    public:

      template<typename T = unsigned long> __forceinline static T hPlayer() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T iEvent() { return ( T ) 0x14; }
      template<typename T = unsigned long> __forceinline static T nData() { return ( T ) 0x18; }
   };
};

#endif
