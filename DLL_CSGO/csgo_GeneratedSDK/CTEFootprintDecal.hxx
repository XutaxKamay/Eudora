///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTEFootprintDecal
#define SDK_CTEFootprintDecal
#pragma once

class CTEFootprintDecal
{
 public:

   class DT_TEFootprintDecal
   {
    public:

      template<typename T = unsigned long> __forceinline static T vecOrigin() { return ( T ) 0x10; }
      template<typename T = unsigned long> __forceinline static T vecDirection() { return ( T ) 0x1C; }
      template<typename T = unsigned long> __forceinline static T nEntity() { return ( T ) 0x34; }
      template<typename T = unsigned long> __forceinline static T nIndex() { return ( T ) 0x38; }
      template<typename T = unsigned long> __forceinline static T chMaterialType() { return ( T ) 0x3C; }
   };
};

#endif
