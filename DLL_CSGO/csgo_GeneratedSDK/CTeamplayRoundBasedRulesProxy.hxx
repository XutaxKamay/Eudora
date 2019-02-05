///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CTeamplayRoundBasedRulesProxy
#define SDK_CTeamplayRoundBasedRulesProxy
#pragma once

class CTeamplayRoundBasedRulesProxy
{
 public:

   class DT_TeamplayRoundBasedRulesProxy
   {
    public:

      class DT_TeamplayRoundBasedRules
      {
       public:

         template<typename T = unsigned long> __forceinline static T iRoundState() { return ( T ) 0x28; }
         template<typename T = unsigned long> __forceinline static T bInWaitingForPlayers() { return ( T ) 0x38; }
         template<typename T = unsigned long> __forceinline static T iWinningTeam() { return ( T ) 0x30; }
         template<typename T = unsigned long> __forceinline static T bInOvertime() { return ( T ) 0x2C; }
         template<typename T = unsigned long> __forceinline static T bInSetup() { return ( T ) 0x2D; }
         template<typename T = unsigned long> __forceinline static T bSwitchedTeamsThisRound() { return ( T ) 0x2E; }
         template<typename T = unsigned long> __forceinline static T bAwaitingReadyRestart() { return ( T ) 0x39; }
         template<typename T = unsigned long> __forceinline static T flRestartRoundTime() { return ( T ) 0x3C; }
         template<typename T = unsigned long> __forceinline static T flMapResetTime() { return ( T ) 0x40; }

         class m_flNextRespawnWave
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x44; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x48; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x4C; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x50; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x54; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x58; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x5C; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x60; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x64; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x68; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x6C; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x70; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x74; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x78; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x7C; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x80; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x84; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x88; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x8C; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x90; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x94; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x98; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x9C; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA0; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA4; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA8; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xAC; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xB0; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xB4; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xB8; }
            template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xBC; }
            template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xC0; }
         };

         class m_TeamRespawnWaveTimes
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xE8; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xEC; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xF0; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xF4; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xF8; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xFC; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x100; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x104; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x108; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x10C; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x110; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x114; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x118; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x11C; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x120; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x124; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x128; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x12C; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x130; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x134; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x138; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x13C; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x140; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x144; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0x148; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0x14C; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0x150; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0x154; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0x158; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0x15C; }
            template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0x160; }
            template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0x164; }
         };

         class m_bTeamReady
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xC4; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xC5; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xC6; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xC7; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xC8; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xC9; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xCA; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xCB; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xCC; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xCD; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xCE; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xCF; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xD0; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xD1; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xD2; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xD3; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xD4; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xD5; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xD6; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xD7; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xD8; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xD9; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xDA; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xDB; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xDC; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xDD; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xDE; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xDF; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xE0; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xE1; }
            template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xE2; }
            template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xE3; }
         };

         template<typename T = unsigned long> __forceinline static T bStopWatch() { return ( T ) 0xE4; }
      };
   };
};

#endif
