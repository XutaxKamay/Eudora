///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CCSGameRulesProxy
#define SDK_CCSGameRulesProxy
#pragma once

class CCSGameRulesProxy
{
 public:

   class DT_CSGameRulesProxy
   {
    public:

      class DT_CSGameRules
      {
       public:

         template<typename T = unsigned long> __forceinline static T bFreezePeriod() { return ( T ) 0x20; }
         template<typename T = unsigned long> __forceinline static T bMatchWaitingForResume() { return ( T ) 0x40; }
         template<typename T = unsigned long> __forceinline static T bWarmupPeriod() { return ( T ) 0x21; }
         template<typename T = unsigned long> __forceinline static T fWarmupPeriodEnd() { return ( T ) 0x24; }
         template<typename T = unsigned long> __forceinline static T fWarmupPeriodStart() { return ( T ) 0x28; }
         template<typename T = unsigned long> __forceinline static T bTerroristTimeOutActive() { return ( T ) 0x2C; }
         template<typename T = unsigned long> __forceinline static T bCTTimeOutActive() { return ( T ) 0x2D; }
         template<typename T = unsigned long> __forceinline static T flTerroristTimeOutRemaining() { return ( T ) 0x30; }
         template<typename T = unsigned long> __forceinline static T flCTTimeOutRemaining() { return ( T ) 0x34; }
         template<typename T = unsigned long> __forceinline static T nTerroristTimeOuts() { return ( T ) 0x38; }
         template<typename T = unsigned long> __forceinline static T nCTTimeOuts() { return ( T ) 0x3C; }
         template<typename T = unsigned long> __forceinline static T iRoundTime() { return ( T ) 0x44; }
         template<typename T = unsigned long> __forceinline static T gamePhase() { return ( T ) 0x60; }
         template<typename T = unsigned long> __forceinline static T totalRoundsPlayed() { return ( T ) 0x64; }
         template<typename T = unsigned long> __forceinline static T nOvertimePlaying() { return ( T ) 0x68; }
         template<typename T = unsigned long> __forceinline static T timeUntilNextPhaseStarts() { return ( T ) 0x5C; }
         template<typename T = unsigned long> __forceinline static T flCMMItemDropRevealStartTime() { return ( T ) 0x870; }
         template<typename T = unsigned long> __forceinline static T flCMMItemDropRevealEndTime() { return ( T ) 0x874; }
         template<typename T = unsigned long> __forceinline static T fRoundStartTime() { return ( T ) 0x4C; }
         template<typename T = unsigned long> __forceinline static T bGameRestart() { return ( T ) 0x54; }
         template<typename T = unsigned long> __forceinline static T flRestartRoundTime() { return ( T ) 0x50; }
         template<typename T = unsigned long> __forceinline static T flGameStartTime() { return ( T ) 0x58; }
         template<typename T = unsigned long> __forceinline static T iHostagesRemaining() { return ( T ) 0x6C; }
         template<typename T = unsigned long> __forceinline static T bAnyHostageReached() { return ( T ) 0x70; }
         template<typename T = unsigned long> __forceinline static T bMapHasBombTarget() { return ( T ) 0x71; }
         template<typename T = unsigned long> __forceinline static T bMapHasRescueZone() { return ( T ) 0x72; }
         template<typename T = unsigned long> __forceinline static T bMapHasBuyZone() { return ( T ) 0x73; }
         template<typename T = unsigned long> __forceinline static T bIsQueuedMatchmaking() { return ( T ) 0x74; }
         template<typename T = unsigned long> __forceinline static T bIsValveDS() { return ( T ) 0x75; }
         template<typename T = unsigned long> __forceinline static T bIsQuestEligible() { return ( T ) 0x879; }
         template<typename T = unsigned long> __forceinline static T bLogoMap() { return ( T ) 0x76; }
         template<typename T = unsigned long> __forceinline static T iNumGunGameProgressiveWeaponsCT() { return ( T ) 0x78; }
         template<typename T = unsigned long> __forceinline static T iNumGunGameProgressiveWeaponsT() { return ( T ) 0x7C; }
         template<typename T = unsigned long> __forceinline static T iSpectatorSlotCount() { return ( T ) 0x80; }
         template<typename T = unsigned long> __forceinline static T bBombDropped() { return ( T ) 0x99C; }
         template<typename T = unsigned long> __forceinline static T bBombPlanted() { return ( T ) 0x99D; }
         template<typename T = unsigned long> __forceinline static T iRoundWinStatus() { return ( T ) 0x9A0; }
         template<typename T = unsigned long> __forceinline static T eRoundWinReason() { return ( T ) 0x9A4; }
         template<typename T = unsigned long> __forceinline static T flDMBonusStartTime() { return ( T ) 0x44C; }
         template<typename T = unsigned long> __forceinline static T flDMBonusTimeLength() { return ( T ) 0x450; }
         template<typename T = unsigned long> __forceinline static T unDMBonusWeaponLoadoutSlot() { return ( T ) 0x454; }
         template<typename T = unsigned long> __forceinline static T bDMBonusActive() { return ( T ) 0x456; }
         template<typename T = unsigned long> __forceinline static T bTCantBuy() { return ( T ) 0x9A8; }
         template<typename T = unsigned long> __forceinline static T bCTCantBuy() { return ( T ) 0x9A9; }
         template<typename T = unsigned long> __forceinline static T flGuardianBuyUntilTime() { return ( T ) 0x9AC; }

         class m_iMatchStats_RoundResults
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x9B0; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x9B4; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x9B8; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x9BC; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x9C0; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x9C4; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x9C8; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x9CC; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x9D0; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x9D4; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x9D8; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x9DC; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x9E0; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x9E4; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x9E8; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x9EC; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x9F0; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x9F4; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x9F8; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x9FC; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA00; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA04; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA08; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA0C; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA10; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA14; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA18; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA1C; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA20; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA24; }
         };

         class m_iMatchStats_PlayersAlive_T
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xAA0; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xAA4; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xAA8; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xAAC; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xAB0; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xAB4; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xAB8; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xABC; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xAC0; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xAC4; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xAC8; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xACC; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xAD0; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xAD4; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xAD8; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xADC; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xAE0; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xAE4; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xAE8; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xAEC; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xAF0; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xAF4; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xAF8; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xAFC; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xB00; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xB04; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xB08; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xB0C; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xB10; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xB14; }
         };

         class m_iMatchStats_PlayersAlive_CT
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA28; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA2C; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA30; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA34; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA38; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA3C; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA40; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA44; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA48; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA4C; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xA50; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xA54; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xA58; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xA5C; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xA60; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xA64; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xA68; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xA6C; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xA70; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xA74; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xA78; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xA7C; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xA80; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xA84; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xA88; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xA8C; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xA90; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xA94; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xA98; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xA9C; }
         };

         class m_GGProgressiveWeaponOrderCT
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x84; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x88; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x8C; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x90; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x94; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x98; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x9C; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA0; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xA4; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xA8; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xAC; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xB0; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xB4; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xB8; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xBC; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xC0; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xC4; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xC8; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xCC; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xD0; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xD4; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xD8; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xDC; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xE0; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xE4; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xE8; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xEC; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xF0; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xF4; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xF8; }
            template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xFC; }
            template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0x100; }
            template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0x104; }
            template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0x108; }
            template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0x10C; }
            template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0x110; }
            template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0x114; }
            template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0x118; }
            template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0x11C; }
            template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0x120; }
            template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0x124; }
            template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0x128; }
            template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0x12C; }
            template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0x130; }
            template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0x134; }
            template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0x138; }
            template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0x13C; }
            template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0x140; }
            template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0x144; }
            template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0x148; }
            template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0x14C; }
            template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0x150; }
            template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0x154; }
            template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0x158; }
            template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0x15C; }
            template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0x160; }
            template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0x164; }
            template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0x168; }
            template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0x16C; }
            template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0x170; }
         };

         class m_GGProgressiveWeaponOrderT
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x174; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x178; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x17C; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x180; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x184; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x188; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x18C; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x190; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x194; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x198; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x19C; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x1A0; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x1A4; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x1A8; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x1AC; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x1B0; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x1B4; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x1B8; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x1BC; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x1C0; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x1C4; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x1C8; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x1CC; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x1D0; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0x1D4; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0x1D8; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0x1DC; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0x1E0; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0x1E4; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0x1E8; }
            template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0x1EC; }
            template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0x1F0; }
            template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0x1F4; }
            template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0x1F8; }
            template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0x1FC; }
            template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0x200; }
            template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0x204; }
            template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0x208; }
            template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0x20C; }
            template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0x210; }
            template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0x214; }
            template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0x218; }
            template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0x21C; }
            template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0x220; }
            template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0x224; }
            template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0x228; }
            template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0x22C; }
            template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0x230; }
            template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0x234; }
            template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0x238; }
            template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0x23C; }
            template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0x240; }
            template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0x244; }
            template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0x248; }
            template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0x24C; }
            template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0x250; }
            template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0x254; }
            template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0x258; }
            template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0x25C; }
            template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0x260; }
         };

         class m_GGProgressiveWeaponKillUpgradeOrderCT
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x264; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x268; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x26C; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x270; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x274; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x278; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x27C; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x280; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x284; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x288; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x28C; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x290; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x294; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x298; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x29C; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x2A0; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x2A4; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x2A8; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x2AC; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x2B0; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x2B4; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x2B8; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x2BC; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x2C0; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0x2C4; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0x2C8; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0x2CC; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0x2D0; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0x2D4; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0x2D8; }
            template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0x2DC; }
            template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0x2E0; }
            template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0x2E4; }
            template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0x2E8; }
            template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0x2EC; }
            template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0x2F0; }
            template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0x2F4; }
            template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0x2F8; }
            template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0x2FC; }
            template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0x300; }
            template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0x304; }
            template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0x308; }
            template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0x30C; }
            template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0x310; }
            template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0x314; }
            template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0x318; }
            template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0x31C; }
            template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0x320; }
            template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0x324; }
            template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0x328; }
            template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0x32C; }
            template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0x330; }
            template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0x334; }
            template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0x338; }
            template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0x33C; }
            template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0x340; }
            template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0x344; }
            template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0x348; }
            template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0x34C; }
            template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0x350; }
         };

         class m_GGProgressiveWeaponKillUpgradeOrderT
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x354; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x358; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x35C; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x360; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x364; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x368; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x36C; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x370; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x374; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x378; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x37C; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x380; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x384; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x388; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x38C; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x390; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x394; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x398; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x39C; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x3A0; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x3A4; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x3A8; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x3AC; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x3B0; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0x3B4; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0x3B8; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0x3BC; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0x3C0; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0x3C4; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0x3C8; }
            template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0x3CC; }
            template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0x3D0; }
            template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0x3D4; }
            template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0x3D8; }
            template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0x3DC; }
            template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0x3E0; }
            template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0x3E4; }
            template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0x3E8; }
            template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0x3EC; }
            template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0x3F0; }
            template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0x3F4; }
            template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0x3F8; }
            template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0x3FC; }
            template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0x400; }
            template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0x404; }
            template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0x408; }
            template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0x40C; }
            template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0x410; }
            template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0x414; }
            template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0x418; }
            template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0x41C; }
            template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0x420; }
            template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0x424; }
            template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0x428; }
            template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0x42C; }
            template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0x430; }
            template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0x434; }
            template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0x438; }
            template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0x43C; }
            template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0x440; }
         };

         template<typename T = unsigned long> __forceinline static T MatchDevice() { return ( T ) 0x444; }
         template<typename T = unsigned long> __forceinline static T bHasMatchStarted() { return ( T ) 0x448; }

         class m_TeamRespawnWaveTimes
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xB18; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xB1C; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xB20; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xB24; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xB28; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xB2C; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xB30; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xB34; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xB38; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xB3C; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xB40; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xB44; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xB48; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xB4C; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xB50; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xB54; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xB58; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xB5C; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xB60; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xB64; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xB68; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xB6C; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xB70; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xB74; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xB78; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xB7C; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xB80; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xB84; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xB88; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xB8C; }
            template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xB90; }
            template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xB94; }
         };

         class m_flNextRespawnWave
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xB98; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xB9C; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xBA0; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xBA4; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xBA8; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xBAC; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xBB0; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xBB4; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xBB8; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xBBC; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xBC0; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xBC4; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xBC8; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xBCC; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xBD0; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xBD4; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xBD8; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xBDC; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xBE0; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xBE4; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xBE8; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xBEC; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xBF0; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xBF4; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xBF8; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xBFC; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xC00; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xC04; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xC08; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xC0C; }
            template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xC10; }
            template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xC14; }
         };

         template<typename T = unsigned long> __forceinline static T nNextMapInMapgroup() { return ( T ) 0x458; }

         class m_nEndMatchMapGroupVoteTypes
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xC20; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xC24; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xC28; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xC2C; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xC30; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xC34; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xC38; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xC3C; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xC40; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xC44; }
         };

         class m_nEndMatchMapGroupVoteOptions
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xC48; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xC4C; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xC50; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xC54; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xC58; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xC5C; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xC60; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xC64; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xC68; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xC6C; }
         };

         template<typename T = unsigned long> __forceinline static T nEndMatchMapVoteWinner() { return ( T ) 0xC70; }
         template<typename T = unsigned long> __forceinline static T bIsDroppingItems() { return ( T ) 0x878; }
         template<typename T = unsigned long> __forceinline static T iActiveAssassinationTargetMissionID() { return ( T ) 0xC18; }
         template<typename T = unsigned long> __forceinline static T fMatchStartTime() { return ( T ) 0x48; }
         template<typename T = unsigned long> __forceinline static T szTournamentEventName() { return ( T ) 0x45C; }
         template<typename T = unsigned long> __forceinline static T szTournamentEventStage() { return ( T ) 0x560; }
         template<typename T = unsigned long> __forceinline static T szTournamentPredictionsTxt() { return ( T ) 0x768; }
         template<typename T = unsigned long> __forceinline static T nTournamentPredictionsPct() { return ( T ) 0x86C; }
         template<typename T = unsigned long> __forceinline static T szMatchStatTxt() { return ( T ) 0x664; }
         template<typename T = unsigned long> __forceinline static T nGuardianModeWaveNumber() { return ( T ) 0x87C; }
         template<typename T = unsigned long> __forceinline static T nGuardianModeSpecialKillsRemaining() { return ( T ) 0x880; }
         template<typename T = unsigned long> __forceinline static T nGuardianModeSpecialWeaponNeeded() { return ( T ) 0x884; }
         template<typename T = unsigned long> __forceinline static T nHalloweenMaskListSeed() { return ( T ) 0x998; }
         template<typename T = unsigned long> __forceinline static T numGlobalGiftsGiven() { return ( T ) 0x890; }
         template<typename T = unsigned long> __forceinline static T numGlobalGifters() { return ( T ) 0x894; }
         template<typename T = unsigned long> __forceinline static T numGlobalGiftsPeriodSeconds() { return ( T ) 0x898; }

         class m_arrFeaturedGiftersAccounts
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x89C; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x8A0; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x8A4; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x8A8; }
         };

         class m_arrFeaturedGiftersGifts
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x8AC; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x8B0; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x8B4; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x8B8; }
         };

         class m_arrProhibitedItemIndices
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x8BC; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x8BE; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x8C0; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x8C2; }
            template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x8C4; }
            template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x8C6; }
            template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x8C8; }
            template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x8CA; }
            template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x8CC; }
            template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x8CE; }
            template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x8D0; }
            template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x8D2; }
            template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x8D4; }
            template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x8D6; }
            template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x8D8; }
            template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x8DA; }
            template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x8DC; }
            template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x8DE; }
            template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x8E0; }
            template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x8E2; }
            template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x8E4; }
            template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x8E6; }
            template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x8E8; }
            template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x8EA; }
            template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0x8EC; }
            template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0x8EE; }
            template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0x8F0; }
            template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0x8F2; }
            template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0x8F4; }
            template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0x8F6; }
            template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0x8F8; }
            template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0x8FA; }
            template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0x8FC; }
            template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0x8FE; }
            template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0x900; }
            template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0x902; }
            template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0x904; }
            template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0x906; }
            template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0x908; }
            template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0x90A; }
            template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0x90C; }
            template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0x90E; }
            template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0x910; }
            template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0x912; }
            template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0x914; }
            template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0x916; }
            template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0x918; }
            template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0x91A; }
            template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0x91C; }
            template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0x91E; }
            template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0x920; }
            template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0x922; }
            template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0x924; }
            template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0x926; }
            template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0x928; }
            template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0x92A; }
            template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0x92C; }
            template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0x92E; }
            template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0x930; }
            template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0x932; }
            template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0x934; }
            template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0x936; }
            template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0x938; }
            template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0x93A; }
            template<typename T = unsigned long> __forceinline static T _064() { return ( T ) 0x93C; }
            template<typename T = unsigned long> __forceinline static T _065() { return ( T ) 0x93E; }
            template<typename T = unsigned long> __forceinline static T _066() { return ( T ) 0x940; }
            template<typename T = unsigned long> __forceinline static T _067() { return ( T ) 0x942; }
            template<typename T = unsigned long> __forceinline static T _068() { return ( T ) 0x944; }
            template<typename T = unsigned long> __forceinline static T _069() { return ( T ) 0x946; }
            template<typename T = unsigned long> __forceinline static T _070() { return ( T ) 0x948; }
            template<typename T = unsigned long> __forceinline static T _071() { return ( T ) 0x94A; }
            template<typename T = unsigned long> __forceinline static T _072() { return ( T ) 0x94C; }
            template<typename T = unsigned long> __forceinline static T _073() { return ( T ) 0x94E; }
            template<typename T = unsigned long> __forceinline static T _074() { return ( T ) 0x950; }
            template<typename T = unsigned long> __forceinline static T _075() { return ( T ) 0x952; }
            template<typename T = unsigned long> __forceinline static T _076() { return ( T ) 0x954; }
            template<typename T = unsigned long> __forceinline static T _077() { return ( T ) 0x956; }
            template<typename T = unsigned long> __forceinline static T _078() { return ( T ) 0x958; }
            template<typename T = unsigned long> __forceinline static T _079() { return ( T ) 0x95A; }
            template<typename T = unsigned long> __forceinline static T _080() { return ( T ) 0x95C; }
            template<typename T = unsigned long> __forceinline static T _081() { return ( T ) 0x95E; }
            template<typename T = unsigned long> __forceinline static T _082() { return ( T ) 0x960; }
            template<typename T = unsigned long> __forceinline static T _083() { return ( T ) 0x962; }
            template<typename T = unsigned long> __forceinline static T _084() { return ( T ) 0x964; }
            template<typename T = unsigned long> __forceinline static T _085() { return ( T ) 0x966; }
            template<typename T = unsigned long> __forceinline static T _086() { return ( T ) 0x968; }
            template<typename T = unsigned long> __forceinline static T _087() { return ( T ) 0x96A; }
            template<typename T = unsigned long> __forceinline static T _088() { return ( T ) 0x96C; }
            template<typename T = unsigned long> __forceinline static T _089() { return ( T ) 0x96E; }
            template<typename T = unsigned long> __forceinline static T _090() { return ( T ) 0x970; }
            template<typename T = unsigned long> __forceinline static T _091() { return ( T ) 0x972; }
            template<typename T = unsigned long> __forceinline static T _092() { return ( T ) 0x974; }
            template<typename T = unsigned long> __forceinline static T _093() { return ( T ) 0x976; }
            template<typename T = unsigned long> __forceinline static T _094() { return ( T ) 0x978; }
            template<typename T = unsigned long> __forceinline static T _095() { return ( T ) 0x97A; }
            template<typename T = unsigned long> __forceinline static T _096() { return ( T ) 0x97C; }
            template<typename T = unsigned long> __forceinline static T _097() { return ( T ) 0x97E; }
            template<typename T = unsigned long> __forceinline static T _098() { return ( T ) 0x980; }
            template<typename T = unsigned long> __forceinline static T _099() { return ( T ) 0x982; }
         };

         template<typename T = unsigned long> __forceinline static T numBestOfMaps() { return ( T ) 0x994; }

         class m_arrTournamentActiveCasterAccounts
         {
          public:

            template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x984; }
            template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x988; }
            template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x98C; }
            template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x990; }
         };
      };
   };
};

#endif
