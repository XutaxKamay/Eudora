///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEEffectDispatch
#define SDK_CTEEffectDispatch
#pragma once

class CTEEffectDispatch
{
 public:

   class DT_TEEffectDispatch
   {
    public:

      class DT_EffectData
      {
       public:

         template<typename T = unsigned long> __forceinline static T vOrigin_x() { return ( T ) 0x10; }
         template<typename T = unsigned long> __forceinline static T vOrigin_y() { return ( T ) 0x14; }
         template<typename T = unsigned long> __forceinline static T vOrigin_z() { return ( T ) 0x18; }
         template<typename T = unsigned long> __forceinline static T vStart_x() { return ( T ) 0x1C; }
         template<typename T = unsigned long> __forceinline static T vStart_y() { return ( T ) 0x20; }
         template<typename T = unsigned long> __forceinline static T vStart_z() { return ( T ) 0x24; }
         template<typename T = unsigned long> __forceinline static T vAngles() { return ( T ) 0x34; }
         template<typename T = unsigned long> __forceinline static T vNormal() { return ( T ) 0x28; }
         template<typename T = unsigned long> __forceinline static T fFlags() { return ( T ) 0x40; }
         template<typename T = unsigned long> __forceinline static T flMagnitude() { return ( T ) 0x4C; }
         template<typename T = unsigned long> __forceinline static T flScale() { return ( T ) 0x48; }
         template<typename T = unsigned long> __forceinline static T nAttachmentIndex() { return ( T ) 0x54; }
         template<typename T = unsigned long> __forceinline static T nSurfaceProp() { return ( T ) 0x58; }
         template<typename T = unsigned long> __forceinline static T iEffectName() { return ( T ) 0x70; }
         template<typename T = unsigned long> __forceinline static T nMaterial() { return ( T ) 0x5C; }
         template<typename T = unsigned long> __forceinline static T nDamageType() { return ( T ) 0x60; }
         template<typename T = unsigned long> __forceinline static T nHitBox() { return ( T ) 0x64; }
         template<typename T = unsigned long> __forceinline static T entindex() { return ( T ) 0x10; }
         template<typename T = unsigned long> __forceinline static T nOtherEntIndex() { return ( T ) 0x68; }
         template<typename T = unsigned long> __forceinline static T nColor() { return ( T ) 0x6C; }
         template<typename T = unsigned long> __forceinline static T flRadius() { return ( T ) 0x50; }
         template<typename T = unsigned long> __forceinline static T bPositionsAreRelativeToEntity() { return ( T ) 0x6D; }
      };
   };
};

#endif
