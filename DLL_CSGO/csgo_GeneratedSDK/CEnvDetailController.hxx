///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CEnvDetailController
#define SDK_CEnvDetailController
#pragma once

class CEnvDetailController
{
 public:

   class DT_DetailController
   {
    public:

      template<typename T = unsigned long> __forceinline static T flFadeStartDist() { return ( T ) 0x9D8; }
      template<typename T = unsigned long> __forceinline static T flFadeEndDist() { return ( T ) 0x9DC; }
   };
};

#endif
