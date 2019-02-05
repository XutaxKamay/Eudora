///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEFizz
#define SDK_CTEFizz
#pragma once

class CTEFizz
{
 public:

   class DT_TEFizz
   {
    public:

      template<typename T = unsigned long> __forceinline static T nEntity() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T nModelIndex() { return ( T ) 0x14; }
      template<typename T = unsigned long> __forceinline static T nDensity() { return ( T ) 0x18; }
      template<typename T = unsigned long> __forceinline static T nCurrent() { return ( T ) 0x1C; }
   };
};

#endif
