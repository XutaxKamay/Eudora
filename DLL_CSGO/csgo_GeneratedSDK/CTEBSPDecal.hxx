///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEBSPDecal
#define SDK_CTEBSPDecal
#pragma once

class CTEBSPDecal
{
 public:

   class DT_TEBSPDecal
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T nEntity() { return ( T ) 0x1C; }
      template<typename T = unsigned long> __forceinline static T nIndex() { return ( T ) 0x20; }
   };
};

#endif
