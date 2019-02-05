///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTeam
#define SDK_CTeam
#pragma once

class CTeam
{
 public:

   class DT_Team
   {
    public:

      template<typename T = unsigned long> __forceinline static T iTeamNum() { return ( T ) 0xB68; }
      template<typename T = unsigned long> __forceinline static T bSurrendered() { return ( T ) 0xB6C; }
      template<typename T = unsigned long> __forceinline static T scoreTotal() { return ( T ) 0xB40; }
      template<typename T = unsigned long> __forceinline static T scoreFirstHalf() { return ( T ) 0xB44; }
      template<typename T = unsigned long> __forceinline static T scoreSecondHalf() { return ( T ) 0xB48; }
      template<typename T = unsigned long> __forceinline static T scoreOvertime() { return ( T ) 0xB4C; }
      template<typename T = unsigned long> __forceinline static T iClanID() { return ( T ) 0xB58; }
      template<typename T = unsigned long> __forceinline static T szTeamname() { return ( T ) 0x9EC; }
      template<typename T = unsigned long> __forceinline static T szClanTeamname() { return ( T ) 0xA0C; }
      template<typename T = unsigned long> __forceinline static T szTeamFlagImage() { return ( T ) 0xA2C; }
      template<typename T = unsigned long> __forceinline static T szTeamLogoImage() { return ( T ) 0xA34; }
      template<typename T = unsigned long> __forceinline static T szTeamMatchStat() { return ( T ) 0xA3C; }
      template<typename T = unsigned long> __forceinline static T nGGLeaderEntIndex_CT() { return ( T ) 0xB50; }
      template<typename T = unsigned long> __forceinline static T nGGLeaderEntIndex_T() { return ( T ) 0xB54; }
      template<typename T = unsigned long> __forceinline static T numMapVictories() { return ( T ) 0xB70; }
   };
};

#endif
