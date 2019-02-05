///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CFish
#define SDK_CFish
#pragma once

class CFish
{
 public:

   class DT_CFish
   {
    public:

      template<typename T = unsigned long> __forceinline static T poolOrigin() { return ( T ) 0x29D0; }
      template<typename T = unsigned long> __forceinline static T x() { return ( T ) 0x29B8; }
      template<typename T = unsigned long> __forceinline static T y() { return ( T ) 0x29BC; }
      template<typename T = unsigned long> __forceinline static T z() { return ( T ) 0x29C0; }
      template<typename T = unsigned long> __forceinline static T angle() { return ( T ) 0x29C8; }
      template<typename T = unsigned long> __forceinline static T nModelIndex() { return ( T ) 0x254; }
      template<typename T = unsigned long> __forceinline static T lifeState() { return ( T ) 0x25B; }
      template<typename T = unsigned long> __forceinline static T waterLevel() { return ( T ) 0x29DC; }
   };
};

#endif
