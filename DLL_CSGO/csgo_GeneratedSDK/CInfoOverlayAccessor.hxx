///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CInfoOverlayAccessor
#define SDK_CInfoOverlayAccessor
#pragma once

class CInfoOverlayAccessor
{
 public:

   class DT_InfoOverlayAccessor
   {
    public:

      template<typename T = unsigned long> __forceinline static T iTextureFrameIndex() { return ( T ) 0x988; }
      template<typename T = unsigned long> __forceinline static T iOverlayID() { return ( T ) 0x9D8; }
   };
};

#endif
