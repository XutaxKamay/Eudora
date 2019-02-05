///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTESpriteSpray
#define SDK_CTESpriteSpray
#pragma once

class CTESpriteSpray
{
 public:

   class DT_TESpriteSpray
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T vecDirection() { return ( T ) 0x1C; }
      template<typename T = unsigned long> __forceinline static T nModelIndex() { return ( T ) 0x28; }
      template<typename T = unsigned long> __forceinline static T fNoise() { return ( T ) 0x30; }
      template<typename T = unsigned long> __forceinline static T nCount() { return ( T ) 0x34; }
      template<typename T = unsigned long> __forceinline static T nSpeed() { return ( T ) 0x2C; }
   };
};

#endif
