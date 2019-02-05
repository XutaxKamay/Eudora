///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTestTraceline
#define SDK_CTestTraceline
#pragma once

class CTestTraceline
{
 public:

   class DT_TestTraceline
   {
    public:

      template<typename T = unsigned long> __forceinline static T clrRender() { return ( T ) 0x70; }
      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x134; }
      template<typename T = unsigned long> __forceinline static T angRotation_0() { return ( T ) 0x128; }
      template<typename T = unsigned long> __forceinline static T angRotation_1() { return ( T ) 0x12C; }
      template<typename T = unsigned long> __forceinline static T angRotation_2() { return ( T ) 0x130; }
      template<typename T = unsigned long> __forceinline static T moveparent() { return ( T ) 0x144; }
   };
};

#endif
