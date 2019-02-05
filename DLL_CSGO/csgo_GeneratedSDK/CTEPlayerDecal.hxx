///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEPlayerDecal
#define SDK_CTEPlayerDecal
#pragma once

class CTEPlayerDecal
{
 public:

   class DT_TEPlayerDecal
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x14; }
      template<typename T = unsigned long> __forceinline static T vecStart() { return ( T ) 0x20; }
      template<typename T = unsigned long> __forceinline static T vecRight() { return ( T ) 0x2C; }
      template<typename T = unsigned long> __forceinline static T nEntity() { return ( T ) 0x38; }
      template<typename T = unsigned long> __forceinline static T nPlayer() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T nHitbox() { return ( T ) 0x3C; }
   };
};

#endif
