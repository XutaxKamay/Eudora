///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CRopeKeyframe
#define SDK_CRopeKeyframe
#pragma once

class CRopeKeyframe
{
 public:

   class DT_RopeKeyframe
   {
    public:

      template<typename T = unsigned long> __forceinline static T nChangeCount() { return ( T ) 0xCCC; }
      template<typename T = unsigned long> __forceinline static T iRopeMaterialModelIndex() { return ( T ) 0xA14; }
      template<typename T = unsigned long> __forceinline static T hStartPoint() { return ( T ) 0xCAC; }
      template<typename T = unsigned long> __forceinline static T hEndPoint() { return ( T ) 0xCB0; }
      template<typename T = unsigned long> __forceinline static T iStartAttachment() { return ( T ) 0xCB4; }
      template<typename T = unsigned long> __forceinline static T iEndAttachment() { return ( T ) 0xCB6; }
      template<typename T = unsigned long> __forceinline static T fLockedPoints() { return ( T ) 0xCC8; }
      template<typename T = unsigned long> __forceinline static T Slack() { return ( T ) 0xCC0; }
      template<typename T = unsigned long> __forceinline static T RopeLength() { return ( T ) 0xCBC; }
      template<typename T = unsigned long> __forceinline static T RopeFlags() { return ( T ) 0xA10; }
      template<typename T = unsigned long> __forceinline static T TextureScale() { return ( T ) 0xCC4; }
      template<typename T = unsigned long> __forceinline static T nSegments() { return ( T ) 0xCA8; }
      template<typename T = unsigned long> __forceinline static T bConstrainBetweenEndpoints() { return ( T ) 0xD50; }
      template<typename T = unsigned long> __forceinline static T Subdiv() { return ( T ) 0xCB8; }
      template<typename T = unsigned long> __forceinline static T Width() { return ( T ) 0xCD0; }
      template<typename T = unsigned long> __forceinline static T flScrollSpeed() { return ( T ) 0xA0C; }
      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x134; }
      template<typename T = unsigned long> __forceinline static T moveparent() { return ( T ) 0x144; }
      template<typename T = unsigned long> __forceinline static T iParentAttachment() { return ( T ) 0x2E8; }
      template<typename T = unsigned long> __forceinline static T iDefaultRopeMaterialModelIndex() { return ( T ) 0xA18; }
      template<typename T = unsigned long> __forceinline static T nMinCPULevel() { return ( T ) 0x984; }
      template<typename T = unsigned long> __forceinline static T nMaxCPULevel() { return ( T ) 0x985; }
      template<typename T = unsigned long> __forceinline static T nMinGPULevel() { return ( T ) 0x986; }
      template<typename T = unsigned long> __forceinline static T nMaxGPULevel() { return ( T ) 0x987; }
   };
};

#endif
