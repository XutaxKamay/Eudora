///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CBaseViewModel
#define SDK_CBaseViewModel
#pragma once

class CBaseViewModel
{
 public:

   class DT_BaseViewModel
   {
    public:

      template<typename T = unsigned long> __forceinline static T nModelIndex() { return ( T ) 0x254; }
      template<typename T = unsigned long> __forceinline static T hWeapon() { return ( T ) 0x29B8; }
      template<typename T = unsigned long> __forceinline static T nSkin() { return ( T ) 0xA1C; }
      template<typename T = unsigned long> __forceinline static T nBody() { return ( T ) 0xA20; }
      template<typename T = unsigned long> __forceinline static T nSequence() { return ( T ) 0x28AC; }
      template<typename T = unsigned long> __forceinline static T nViewModelIndex() { return ( T ) 0x29B0; }
      template<typename T = unsigned long> __forceinline static T flPlaybackRate() { return ( T ) 0xA18; }
      template<typename T = unsigned long> __forceinline static T fEffects() { return ( T ) 0xEC; }
      template<typename T = unsigned long> __forceinline static T nAnimationParity() { return ( T ) 0x29B4; }
      template<typename T = unsigned long> __forceinline static T hOwner() { return ( T ) 0x29BC; }
      template<typename T = unsigned long> __forceinline static T nNewSequenceParity() { return ( T ) 0xA38; }
      template<typename T = unsigned long> __forceinline static T nResetEventsParity() { return ( T ) 0xA3C; }
      template<typename T = unsigned long> __forceinline static T nMuzzleFlashParity() { return ( T ) 0xA58; }
      template<typename T = unsigned long> __forceinline static T bShouldIgnoreOffsetAndAccuracy() { return ( T ) 0x2980; }
   };
};

#endif
