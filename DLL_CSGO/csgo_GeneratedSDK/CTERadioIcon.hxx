///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTERadioIcon
#define SDK_CTERadioIcon
#pragma once

class CTERadioIcon
{
 public:

   class DT_TERadioIcon
   {
    public:

      template<typename T = unsigned long> __forceinline static T iAttachToClient() { return ( T ) 0x10; }
   };
};

#endif
