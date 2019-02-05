///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEMuzzleFlash
#define SDK_CTEMuzzleFlash
#pragma once

class CTEMuzzleFlash
{
 public:

   class DT_TEMuzzleFlash
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T vecAngles() { return ( T ) 0x1C; }
      template<typename T = unsigned long> __forceinline static T flScale() { return ( T ) 0x28; }
      template<typename T = unsigned long> __forceinline static T nType() { return ( T ) 0x2C; }
   };
};

#endif
