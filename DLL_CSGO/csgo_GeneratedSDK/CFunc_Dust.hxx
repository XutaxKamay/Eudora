///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CFunc_Dust
#define SDK_CFunc_Dust
#pragma once

class CFunc_Dust
{
 public:

   class DT_Func_Dust
   {
    public:

      template<typename T = unsigned long> __forceinline static T Color() { return ( T ) 0x9D8; }
      template<typename T = unsigned long> __forceinline static T SpawnRate() { return ( T ) 0x9DC; }
      template<typename T = unsigned long> __forceinline static T flSizeMin() { return ( T ) 0x9E0; }
      template<typename T = unsigned long> __forceinline static T flSizeMax() { return ( T ) 0x9E4; }
      template<typename T = unsigned long> __forceinline static T LifetimeMin() { return ( T ) 0x9EC; }
      template<typename T = unsigned long> __forceinline static T LifetimeMax() { return ( T ) 0x9F0; }
      template<typename T = unsigned long> __forceinline static T DustFlags() { return ( T ) 0xA00; }
      template<typename T = unsigned long> __forceinline static T SpeedMax() { return ( T ) 0x9E8; }
      template<typename T = unsigned long> __forceinline static T DistMax() { return ( T ) 0x9F4; }
      template<typename T = unsigned long> __forceinline static T nModelIndex() { return ( T ) 0x254; }
      template<typename T = unsigned long> __forceinline static T FallSpeed() { return ( T ) 0x9F8; }
      template<typename T = unsigned long> __forceinline static T bAffectedByWind() { return ( T ) 0x9FC; }

      class DT_CollisionProperty
      {
       public:

         template<typename T = unsigned long> __forceinline static T vecMins() { return ( T ) 0x320; }
         template<typename T = unsigned long> __forceinline static T vecMaxs() { return ( T ) 0x32C; }
         template<typename T = unsigned long> __forceinline static T nSolidType() { return ( T ) 0x33A; }
         template<typename T = unsigned long> __forceinline static T usSolidFlags() { return ( T ) 0x338; }
         template<typename T = unsigned long> __forceinline static T nSurroundType() { return ( T ) 0x342; }
         template<typename T = unsigned long> __forceinline static T triggerBloat() { return ( T ) 0x33B; }
         template<typename T = unsigned long> __forceinline static T vecSpecifiedSurroundingMins() { return ( T ) 0x344; }
         template<typename T = unsigned long> __forceinline static T vecSpecifiedSurroundingMaxs() { return ( T ) 0x350; }
      };
   };
};

#endif
