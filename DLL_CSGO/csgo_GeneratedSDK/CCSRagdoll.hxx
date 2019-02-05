///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CCSRagdoll
#define SDK_CCSRagdoll
#pragma once

class CCSRagdoll
{
 public:

   class DT_CSRagdoll
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x134; }
      template<typename T = unsigned long> __forceinline static T vecRagdollOrigin() { return ( T ) 0x29FC; }
      template<typename T = unsigned long> __forceinline static T hPlayer() { return ( T ) 0x29E0; }
      template<typename T = unsigned long> __forceinline static T nModelIndex() { return ( T ) 0x254; }
      template<typename T = unsigned long> __forceinline static T nForceBone() { return ( T ) 0x267C; }
      template<typename T = unsigned long> __forceinline static T vecForce() { return ( T ) 0x2670; }
      template<typename T = unsigned long> __forceinline static T vecRagdollVelocity() { return ( T ) 0x29F0; }
      template<typename T = unsigned long> __forceinline static T iDeathPose() { return ( T ) 0x2A08; }
      template<typename T = unsigned long> __forceinline static T iDeathFrame() { return ( T ) 0x2A0C; }
      template<typename T = unsigned long> __forceinline static T iTeamNum() { return ( T ) 0xF0; }
      template<typename T = unsigned long> __forceinline static T bClientSideAnimation() { return ( T ) 0x288C; }
      template<typename T = unsigned long> __forceinline static T flDeathYaw() { return ( T ) 0x2A10; }
      template<typename T = unsigned long> __forceinline static T flAbsYaw() { return ( T ) 0x2A14; }
   };
};

#endif
