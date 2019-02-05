///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CFogController
#define SDK_CFogController
#pragma once

class CFogController
{
 public:

   class DT_FogController
   {
    public:

      template<typename T = unsigned long> __forceinline static T fog_enable() { return ( T ) 0xA1C; }
      template<typename T = unsigned long> __forceinline static T fog_blend() { return ( T ) 0xA1D; }
      template<typename T = unsigned long> __forceinline static T fog_dirPrimary() { return ( T ) 0x9DC; }
      template<typename T = unsigned long> __forceinline static T fog_colorPrimary() { return ( T ) 0x9E8; }
      template<typename T = unsigned long> __forceinline static T fog_colorSecondary() { return ( T ) 0x9EC; }
      template<typename T = unsigned long> __forceinline static T fog_start() { return ( T ) 0x9F8; }
      template<typename T = unsigned long> __forceinline static T fog_end() { return ( T ) 0x9FC; }
      template<typename T = unsigned long> __forceinline static T fog_farz() { return ( T ) 0xA00; }
      template<typename T = unsigned long> __forceinline static T fog_maxdensity() { return ( T ) 0xA04; }
      template<typename T = unsigned long> __forceinline static T fog_colorPrimaryLerpTo() { return ( T ) 0x9F0; }
      template<typename T = unsigned long> __forceinline static T fog_colorSecondaryLerpTo() { return ( T ) 0x9F4; }
      template<typename T = unsigned long> __forceinline static T fog_startLerpTo() { return ( T ) 0xA08; }
      template<typename T = unsigned long> __forceinline static T fog_endLerpTo() { return ( T ) 0xA0C; }
      template<typename T = unsigned long> __forceinline static T fog_maxdensityLerpTo() { return ( T ) 0xA10; }
      template<typename T = unsigned long> __forceinline static T fog_lerptime() { return ( T ) 0xA14; }
      template<typename T = unsigned long> __forceinline static T fog_duration() { return ( T ) 0xA18; }
      template<typename T = unsigned long> __forceinline static T fog_HDRColorScale() { return ( T ) 0xA24; }
      template<typename T = unsigned long> __forceinline static T fog_ZoomFogScale() { return ( T ) 0xA20; }
   };
};

#endif
