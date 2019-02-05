///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CRagdollManager
#define SDK_CRagdollManager
#pragma once

class CRagdollManager
{
 public:

   class DT_RagdollManager
   {
    public:

      template<typename T = unsigned long> __forceinline static T iCurrentMaxRagdollCount() { return ( T ) 0x9D8; }
   };
};

#endif
