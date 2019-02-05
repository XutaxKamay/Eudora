///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CBaseWeaponWorldModel
#define SDK_CBaseWeaponWorldModel
#pragma once

class CBaseWeaponWorldModel
{
 public:

   class DT_BaseWeaponWorldModel
   {
    public:

      template<typename T = unsigned long> __forceinline static T nModelIndex() { return ( T ) 0x254; }
      template<typename T = unsigned long> __forceinline static T nBody() { return ( T ) 0xA20; }
      template<typename T = unsigned long> __forceinline static T fEffects() { return ( T ) 0xEC; }
      template<typename T = unsigned long> __forceinline static T moveparent() { return ( T ) 0x144; }
      template<typename T = unsigned long> __forceinline static T hCombatWeaponParent() { return ( T ) 0x29E0; }
   };
};

#endif
