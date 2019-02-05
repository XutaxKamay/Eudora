///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEFireBullets
#define SDK_CTEFireBullets
#pragma once

class CTEFireBullets
{
 public:

   class DT_TEFireBullets
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x18; }
      template<typename T = unsigned long> __forceinline static T vecAngles_0() { return ( T ) 0x24; }
      template<typename T = unsigned long> __forceinline static T vecAngles_1() { return ( T ) 0x28; }
      template<typename T = unsigned long> __forceinline static T iWeaponID() { return ( T ) 0x34; }
      template<typename T = unsigned long> __forceinline static T weapon() { return ( T ) 0x30; }
      template<typename T = unsigned long> __forceinline static T iMode() { return ( T ) 0x38; }
      template<typename T = unsigned long> __forceinline static T iSeed() { return ( T ) 0x3C; }
      template<typename T = unsigned long> __forceinline static T iPlayer() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T fInaccuracy() { return ( T ) 0x40; }
      template<typename T = unsigned long> __forceinline static T fSpread() { return ( T ) 0x48; }
      template<typename T = unsigned long> __forceinline static T nItemDefIndex() { return ( T ) 0x14; }
      template<typename T = unsigned long> __forceinline static T iSoundType() { return ( T ) 0x4C; }
      template<typename T = unsigned long> __forceinline static T flRecoilIndex() { return ( T ) 0x44; }
   };
};

#endif
