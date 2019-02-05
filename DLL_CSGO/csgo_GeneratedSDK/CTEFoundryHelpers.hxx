///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEFoundryHelpers
#define SDK_CTEFoundryHelpers
#pragma once

class CTEFoundryHelpers
{
 public:

   class DT_TEFoundryHelpers
   {
    public:

      template<typename T = unsigned long> __forceinline static T iEntity() { return ( T ) 0x10; }
   };
};

#endif
