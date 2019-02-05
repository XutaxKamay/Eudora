///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEKillPlayerAttachments
#define SDK_CTEKillPlayerAttachments
#pragma once

class CTEKillPlayerAttachments
{
 public:

   class DT_TEKillPlayerAttachments
   {
    public:

      template<typename T = unsigned long> __forceinline static T nPlayer() { return ( T ) 0x10; }
   };
};

#endif
