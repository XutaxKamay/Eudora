///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEWorldDecal
#define SDK_CTEWorldDecal
#pragma once

class CTEWorldDecal
{
 public:

   class DT_TEWorldDecal
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T nIndex() { return ( T ) 0x1C; }
   };
};

#endif
