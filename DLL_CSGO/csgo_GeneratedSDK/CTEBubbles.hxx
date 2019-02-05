///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEBubbles
#define SDK_CTEBubbles
#pragma once

class CTEBubbles
{
 public:

   class DT_TEBubbles
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecMins() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T vecMaxs() { return ( T ) 0x1C; }
      template<typename T = unsigned long> __forceinline static T nModelIndex() { return ( T ) 0x2C; }
      template<typename T = unsigned long> __forceinline static T fHeight() { return ( T ) 0x28; }
      template<typename T = unsigned long> __forceinline static T nCount() { return ( T ) 0x30; }
      template<typename T = unsigned long> __forceinline static T fSpeed() { return ( T ) 0x34; }
   };
};

#endif
