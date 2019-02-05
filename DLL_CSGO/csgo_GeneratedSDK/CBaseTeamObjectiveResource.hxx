///If a function contains _ at its start, it means that the networked variable/function was referenced twice but might be different offset.

#ifndef SDK_CBaseTeamObjectiveResource
#define SDK_CBaseTeamObjectiveResource
#pragma once

class CBaseTeamObjectiveResource
{
 public:

   class DT_BaseTeamObjectiveResource
   {
    public:

      template<typename T = unsigned long> __forceinline static T iTimerToShowInHUD() { return ( T ) 0x9D8; }
      template<typename T = unsigned long> __forceinline static T iStopWatchTimer() { return ( T ) 0x9DC; }
      template<typename T = unsigned long> __forceinline static T iNumControlPoints() { return ( T ) 0x9E0; }
      template<typename T = unsigned long> __forceinline static T bPlayingMiniRounds() { return ( T ) 0x9E8; }
      template<typename T = unsigned long> __forceinline static T bControlPointsReset() { return ( T ) 0x9E9; }
      template<typename T = unsigned long> __forceinline static T iUpdateCapHudParity() { return ( T ) 0x9EC; }
      template<typename T = unsigned long> __forceinline static T vCPPositions_0() { return ( T ) 0x9F4; }

      class m_bCPIsVisible
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA54; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA55; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA56; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA57; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA58; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA59; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA5A; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA5B; }
      };

      class m_flLazyCapPerc
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA5C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xA60; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xA64; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xA68; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xA6C; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xA70; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xA74; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xA78; }
      };

      class m_iTeamIcons
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xA9C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xAA0; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xAA4; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xAA8; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xAAC; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xAB0; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xAB4; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xAB8; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xABC; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xAC0; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xAC4; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xAC8; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xACC; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xAD0; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xAD4; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xAD8; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xADC; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xAE0; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xAE4; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xAE8; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xAEC; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xAF0; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xAF4; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xAF8; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xAFC; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xB00; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xB04; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xB08; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xB0C; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xB10; }
         template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xB14; }
         template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xB18; }
         template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xB1C; }
         template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xB20; }
         template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xB24; }
         template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xB28; }
         template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xB2C; }
         template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xB30; }
         template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xB34; }
         template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xB38; }
         template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xB3C; }
         template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xB40; }
         template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xB44; }
         template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xB48; }
         template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xB4C; }
         template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xB50; }
         template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xB54; }
         template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xB58; }
         template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xB5C; }
         template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xB60; }
         template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xB64; }
         template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xB68; }
         template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xB6C; }
         template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xB70; }
         template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xB74; }
         template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xB78; }
         template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xB7C; }
         template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0xB80; }
         template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0xB84; }
         template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0xB88; }
         template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0xB8C; }
         template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0xB90; }
         template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0xB94; }
         template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0xB98; }
      };

      class m_iTeamOverlays
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xB9C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xBA0; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xBA4; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xBA8; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xBAC; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xBB0; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xBB4; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xBB8; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xBBC; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xBC0; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xBC4; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xBC8; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xBCC; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xBD0; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xBD4; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xBD8; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xBDC; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xBE0; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xBE4; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xBE8; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xBEC; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xBF0; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xBF4; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xBF8; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xBFC; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xC00; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xC04; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xC08; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xC0C; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xC10; }
         template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xC14; }
         template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xC18; }
         template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xC1C; }
         template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xC20; }
         template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xC24; }
         template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xC28; }
         template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xC2C; }
         template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xC30; }
         template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xC34; }
         template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xC38; }
         template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xC3C; }
         template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xC40; }
         template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xC44; }
         template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xC48; }
         template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xC4C; }
         template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xC50; }
         template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xC54; }
         template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xC58; }
         template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xC5C; }
         template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xC60; }
         template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xC64; }
         template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xC68; }
         template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xC6C; }
         template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xC70; }
         template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xC74; }
         template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xC78; }
         template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xC7C; }
         template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0xC80; }
         template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0xC84; }
         template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0xC88; }
         template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0xC8C; }
         template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0xC90; }
         template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0xC94; }
         template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0xC98; }
      };

      class m_iTeamReqCappers
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xC9C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xCA0; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xCA4; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xCA8; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xCAC; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xCB0; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xCB4; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xCB8; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xCBC; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xCC0; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xCC4; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xCC8; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xCCC; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xCD0; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xCD4; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xCD8; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xCDC; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xCE0; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xCE4; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xCE8; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xCEC; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xCF0; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xCF4; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xCF8; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xCFC; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xD00; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xD04; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xD08; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xD0C; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xD10; }
         template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xD14; }
         template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xD18; }
         template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xD1C; }
         template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xD20; }
         template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xD24; }
         template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xD28; }
         template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xD2C; }
         template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xD30; }
         template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xD34; }
         template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xD38; }
         template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xD3C; }
         template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xD40; }
         template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xD44; }
         template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xD48; }
         template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xD4C; }
         template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xD50; }
         template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xD54; }
         template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xD58; }
         template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xD5C; }
         template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xD60; }
         template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xD64; }
         template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xD68; }
         template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xD6C; }
         template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xD70; }
         template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xD74; }
         template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xD78; }
         template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xD7C; }
         template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0xD80; }
         template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0xD84; }
         template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0xD88; }
         template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0xD8C; }
         template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0xD90; }
         template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0xD94; }
         template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0xD98; }
      };

      class m_flTeamCapTime
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xD9C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xDA0; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xDA4; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xDA8; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xDAC; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xDB0; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xDB4; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xDB8; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xDBC; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xDC0; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xDC4; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xDC8; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xDCC; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xDD0; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xDD4; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xDD8; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xDDC; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xDE0; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xDE4; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xDE8; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xDEC; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xDF0; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xDF4; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xDF8; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xDFC; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xE00; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xE04; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xE08; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xE0C; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xE10; }
         template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xE14; }
         template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xE18; }
         template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xE1C; }
         template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xE20; }
         template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xE24; }
         template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xE28; }
         template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xE2C; }
         template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xE30; }
         template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xE34; }
         template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xE38; }
         template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xE3C; }
         template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xE40; }
         template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xE44; }
         template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xE48; }
         template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xE4C; }
         template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xE50; }
         template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xE54; }
         template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xE58; }
         template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xE5C; }
         template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xE60; }
         template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xE64; }
         template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xE68; }
         template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xE6C; }
         template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xE70; }
         template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xE74; }
         template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xE78; }
         template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xE7C; }
         template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0xE80; }
         template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0xE84; }
         template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0xE88; }
         template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0xE8C; }
         template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0xE90; }
         template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0xE94; }
         template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0xE98; }
      };

      class m_iPreviousPoints
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0xE9C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0xEA0; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0xEA4; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0xEA8; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0xEAC; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0xEB0; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0xEB4; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0xEB8; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0xEBC; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0xEC0; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0xEC4; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0xEC8; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0xECC; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0xED0; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0xED4; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0xED8; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0xEDC; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0xEE0; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0xEE4; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0xEE8; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0xEEC; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0xEF0; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0xEF4; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0xEF8; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0xEFC; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0xF00; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0xF04; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0xF08; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0xF0C; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0xF10; }
         template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0xF14; }
         template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0xF18; }
         template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0xF1C; }
         template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0xF20; }
         template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0xF24; }
         template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0xF28; }
         template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0xF2C; }
         template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0xF30; }
         template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0xF34; }
         template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0xF38; }
         template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0xF3C; }
         template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0xF40; }
         template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0xF44; }
         template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0xF48; }
         template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0xF4C; }
         template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0xF50; }
         template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0xF54; }
         template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0xF58; }
         template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0xF5C; }
         template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0xF60; }
         template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0xF64; }
         template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0xF68; }
         template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0xF6C; }
         template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0xF70; }
         template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0xF74; }
         template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0xF78; }
         template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0xF7C; }
         template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0xF80; }
         template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0xF84; }
         template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0xF88; }
         template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0xF8C; }
         template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0xF90; }
         template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0xF94; }
         template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0xF98; }
         template<typename T = unsigned long> __forceinline static T _064() { return ( T ) 0xF9C; }
         template<typename T = unsigned long> __forceinline static T _065() { return ( T ) 0xFA0; }
         template<typename T = unsigned long> __forceinline static T _066() { return ( T ) 0xFA4; }
         template<typename T = unsigned long> __forceinline static T _067() { return ( T ) 0xFA8; }
         template<typename T = unsigned long> __forceinline static T _068() { return ( T ) 0xFAC; }
         template<typename T = unsigned long> __forceinline static T _069() { return ( T ) 0xFB0; }
         template<typename T = unsigned long> __forceinline static T _070() { return ( T ) 0xFB4; }
         template<typename T = unsigned long> __forceinline static T _071() { return ( T ) 0xFB8; }
         template<typename T = unsigned long> __forceinline static T _072() { return ( T ) 0xFBC; }
         template<typename T = unsigned long> __forceinline static T _073() { return ( T ) 0xFC0; }
         template<typename T = unsigned long> __forceinline static T _074() { return ( T ) 0xFC4; }
         template<typename T = unsigned long> __forceinline static T _075() { return ( T ) 0xFC8; }
         template<typename T = unsigned long> __forceinline static T _076() { return ( T ) 0xFCC; }
         template<typename T = unsigned long> __forceinline static T _077() { return ( T ) 0xFD0; }
         template<typename T = unsigned long> __forceinline static T _078() { return ( T ) 0xFD4; }
         template<typename T = unsigned long> __forceinline static T _079() { return ( T ) 0xFD8; }
         template<typename T = unsigned long> __forceinline static T _080() { return ( T ) 0xFDC; }
         template<typename T = unsigned long> __forceinline static T _081() { return ( T ) 0xFE0; }
         template<typename T = unsigned long> __forceinline static T _082() { return ( T ) 0xFE4; }
         template<typename T = unsigned long> __forceinline static T _083() { return ( T ) 0xFE8; }
         template<typename T = unsigned long> __forceinline static T _084() { return ( T ) 0xFEC; }
         template<typename T = unsigned long> __forceinline static T _085() { return ( T ) 0xFF0; }
         template<typename T = unsigned long> __forceinline static T _086() { return ( T ) 0xFF4; }
         template<typename T = unsigned long> __forceinline static T _087() { return ( T ) 0xFF8; }
         template<typename T = unsigned long> __forceinline static T _088() { return ( T ) 0xFFC; }
         template<typename T = unsigned long> __forceinline static T _089() { return ( T ) 0x1000; }
         template<typename T = unsigned long> __forceinline static T _090() { return ( T ) 0x1004; }
         template<typename T = unsigned long> __forceinline static T _091() { return ( T ) 0x1008; }
         template<typename T = unsigned long> __forceinline static T _092() { return ( T ) 0x100C; }
         template<typename T = unsigned long> __forceinline static T _093() { return ( T ) 0x1010; }
         template<typename T = unsigned long> __forceinline static T _094() { return ( T ) 0x1014; }
         template<typename T = unsigned long> __forceinline static T _095() { return ( T ) 0x1018; }
         template<typename T = unsigned long> __forceinline static T _096() { return ( T ) 0x101C; }
         template<typename T = unsigned long> __forceinline static T _097() { return ( T ) 0x1020; }
         template<typename T = unsigned long> __forceinline static T _098() { return ( T ) 0x1024; }
         template<typename T = unsigned long> __forceinline static T _099() { return ( T ) 0x1028; }
         template<typename T = unsigned long> __forceinline static T _100() { return ( T ) 0x102C; }
         template<typename T = unsigned long> __forceinline static T _101() { return ( T ) 0x1030; }
         template<typename T = unsigned long> __forceinline static T _102() { return ( T ) 0x1034; }
         template<typename T = unsigned long> __forceinline static T _103() { return ( T ) 0x1038; }
         template<typename T = unsigned long> __forceinline static T _104() { return ( T ) 0x103C; }
         template<typename T = unsigned long> __forceinline static T _105() { return ( T ) 0x1040; }
         template<typename T = unsigned long> __forceinline static T _106() { return ( T ) 0x1044; }
         template<typename T = unsigned long> __forceinline static T _107() { return ( T ) 0x1048; }
         template<typename T = unsigned long> __forceinline static T _108() { return ( T ) 0x104C; }
         template<typename T = unsigned long> __forceinline static T _109() { return ( T ) 0x1050; }
         template<typename T = unsigned long> __forceinline static T _110() { return ( T ) 0x1054; }
         template<typename T = unsigned long> __forceinline static T _111() { return ( T ) 0x1058; }
         template<typename T = unsigned long> __forceinline static T _112() { return ( T ) 0x105C; }
         template<typename T = unsigned long> __forceinline static T _113() { return ( T ) 0x1060; }
         template<typename T = unsigned long> __forceinline static T _114() { return ( T ) 0x1064; }
         template<typename T = unsigned long> __forceinline static T _115() { return ( T ) 0x1068; }
         template<typename T = unsigned long> __forceinline static T _116() { return ( T ) 0x106C; }
         template<typename T = unsigned long> __forceinline static T _117() { return ( T ) 0x1070; }
         template<typename T = unsigned long> __forceinline static T _118() { return ( T ) 0x1074; }
         template<typename T = unsigned long> __forceinline static T _119() { return ( T ) 0x1078; }
         template<typename T = unsigned long> __forceinline static T _120() { return ( T ) 0x107C; }
         template<typename T = unsigned long> __forceinline static T _121() { return ( T ) 0x1080; }
         template<typename T = unsigned long> __forceinline static T _122() { return ( T ) 0x1084; }
         template<typename T = unsigned long> __forceinline static T _123() { return ( T ) 0x1088; }
         template<typename T = unsigned long> __forceinline static T _124() { return ( T ) 0x108C; }
         template<typename T = unsigned long> __forceinline static T _125() { return ( T ) 0x1090; }
         template<typename T = unsigned long> __forceinline static T _126() { return ( T ) 0x1094; }
         template<typename T = unsigned long> __forceinline static T _127() { return ( T ) 0x1098; }
         template<typename T = unsigned long> __forceinline static T _128() { return ( T ) 0x109C; }
         template<typename T = unsigned long> __forceinline static T _129() { return ( T ) 0x10A0; }
         template<typename T = unsigned long> __forceinline static T _130() { return ( T ) 0x10A4; }
         template<typename T = unsigned long> __forceinline static T _131() { return ( T ) 0x10A8; }
         template<typename T = unsigned long> __forceinline static T _132() { return ( T ) 0x10AC; }
         template<typename T = unsigned long> __forceinline static T _133() { return ( T ) 0x10B0; }
         template<typename T = unsigned long> __forceinline static T _134() { return ( T ) 0x10B4; }
         template<typename T = unsigned long> __forceinline static T _135() { return ( T ) 0x10B8; }
         template<typename T = unsigned long> __forceinline static T _136() { return ( T ) 0x10BC; }
         template<typename T = unsigned long> __forceinline static T _137() { return ( T ) 0x10C0; }
         template<typename T = unsigned long> __forceinline static T _138() { return ( T ) 0x10C4; }
         template<typename T = unsigned long> __forceinline static T _139() { return ( T ) 0x10C8; }
         template<typename T = unsigned long> __forceinline static T _140() { return ( T ) 0x10CC; }
         template<typename T = unsigned long> __forceinline static T _141() { return ( T ) 0x10D0; }
         template<typename T = unsigned long> __forceinline static T _142() { return ( T ) 0x10D4; }
         template<typename T = unsigned long> __forceinline static T _143() { return ( T ) 0x10D8; }
         template<typename T = unsigned long> __forceinline static T _144() { return ( T ) 0x10DC; }
         template<typename T = unsigned long> __forceinline static T _145() { return ( T ) 0x10E0; }
         template<typename T = unsigned long> __forceinline static T _146() { return ( T ) 0x10E4; }
         template<typename T = unsigned long> __forceinline static T _147() { return ( T ) 0x10E8; }
         template<typename T = unsigned long> __forceinline static T _148() { return ( T ) 0x10EC; }
         template<typename T = unsigned long> __forceinline static T _149() { return ( T ) 0x10F0; }
         template<typename T = unsigned long> __forceinline static T _150() { return ( T ) 0x10F4; }
         template<typename T = unsigned long> __forceinline static T _151() { return ( T ) 0x10F8; }
         template<typename T = unsigned long> __forceinline static T _152() { return ( T ) 0x10FC; }
         template<typename T = unsigned long> __forceinline static T _153() { return ( T ) 0x1100; }
         template<typename T = unsigned long> __forceinline static T _154() { return ( T ) 0x1104; }
         template<typename T = unsigned long> __forceinline static T _155() { return ( T ) 0x1108; }
         template<typename T = unsigned long> __forceinline static T _156() { return ( T ) 0x110C; }
         template<typename T = unsigned long> __forceinline static T _157() { return ( T ) 0x1110; }
         template<typename T = unsigned long> __forceinline static T _158() { return ( T ) 0x1114; }
         template<typename T = unsigned long> __forceinline static T _159() { return ( T ) 0x1118; }
         template<typename T = unsigned long> __forceinline static T _160() { return ( T ) 0x111C; }
         template<typename T = unsigned long> __forceinline static T _161() { return ( T ) 0x1120; }
         template<typename T = unsigned long> __forceinline static T _162() { return ( T ) 0x1124; }
         template<typename T = unsigned long> __forceinline static T _163() { return ( T ) 0x1128; }
         template<typename T = unsigned long> __forceinline static T _164() { return ( T ) 0x112C; }
         template<typename T = unsigned long> __forceinline static T _165() { return ( T ) 0x1130; }
         template<typename T = unsigned long> __forceinline static T _166() { return ( T ) 0x1134; }
         template<typename T = unsigned long> __forceinline static T _167() { return ( T ) 0x1138; }
         template<typename T = unsigned long> __forceinline static T _168() { return ( T ) 0x113C; }
         template<typename T = unsigned long> __forceinline static T _169() { return ( T ) 0x1140; }
         template<typename T = unsigned long> __forceinline static T _170() { return ( T ) 0x1144; }
         template<typename T = unsigned long> __forceinline static T _171() { return ( T ) 0x1148; }
         template<typename T = unsigned long> __forceinline static T _172() { return ( T ) 0x114C; }
         template<typename T = unsigned long> __forceinline static T _173() { return ( T ) 0x1150; }
         template<typename T = unsigned long> __forceinline static T _174() { return ( T ) 0x1154; }
         template<typename T = unsigned long> __forceinline static T _175() { return ( T ) 0x1158; }
         template<typename T = unsigned long> __forceinline static T _176() { return ( T ) 0x115C; }
         template<typename T = unsigned long> __forceinline static T _177() { return ( T ) 0x1160; }
         template<typename T = unsigned long> __forceinline static T _178() { return ( T ) 0x1164; }
         template<typename T = unsigned long> __forceinline static T _179() { return ( T ) 0x1168; }
         template<typename T = unsigned long> __forceinline static T _180() { return ( T ) 0x116C; }
         template<typename T = unsigned long> __forceinline static T _181() { return ( T ) 0x1170; }
         template<typename T = unsigned long> __forceinline static T _182() { return ( T ) 0x1174; }
         template<typename T = unsigned long> __forceinline static T _183() { return ( T ) 0x1178; }
         template<typename T = unsigned long> __forceinline static T _184() { return ( T ) 0x117C; }
         template<typename T = unsigned long> __forceinline static T _185() { return ( T ) 0x1180; }
         template<typename T = unsigned long> __forceinline static T _186() { return ( T ) 0x1184; }
         template<typename T = unsigned long> __forceinline static T _187() { return ( T ) 0x1188; }
         template<typename T = unsigned long> __forceinline static T _188() { return ( T ) 0x118C; }
         template<typename T = unsigned long> __forceinline static T _189() { return ( T ) 0x1190; }
         template<typename T = unsigned long> __forceinline static T _190() { return ( T ) 0x1194; }
         template<typename T = unsigned long> __forceinline static T _191() { return ( T ) 0x1198; }
      };

      class m_bTeamCanCap
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x119C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x119D; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x119E; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x119F; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x11A0; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x11A1; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x11A2; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x11A3; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x11A4; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x11A5; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x11A6; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x11A7; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x11A8; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x11A9; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x11AA; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x11AB; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x11AC; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x11AD; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x11AE; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x11AF; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x11B0; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x11B1; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x11B2; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x11B3; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0x11B4; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0x11B5; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0x11B6; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0x11B7; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0x11B8; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0x11B9; }
         template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0x11BA; }
         template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0x11BB; }
         template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0x11BC; }
         template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0x11BD; }
         template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0x11BE; }
         template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0x11BF; }
         template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0x11C0; }
         template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0x11C1; }
         template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0x11C2; }
         template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0x11C3; }
         template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0x11C4; }
         template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0x11C5; }
         template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0x11C6; }
         template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0x11C7; }
         template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0x11C8; }
         template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0x11C9; }
         template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0x11CA; }
         template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0x11CB; }
         template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0x11CC; }
         template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0x11CD; }
         template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0x11CE; }
         template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0x11CF; }
         template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0x11D0; }
         template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0x11D1; }
         template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0x11D2; }
         template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0x11D3; }
         template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0x11D4; }
         template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0x11D5; }
         template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0x11D6; }
         template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0x11D7; }
         template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0x11D8; }
         template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0x11D9; }
         template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0x11DA; }
         template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0x11DB; }
      };

      class m_iTeamBaseIcons
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x11DC; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x11E0; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x11E4; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x11E8; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x11EC; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x11F0; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x11F4; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x11F8; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x11FC; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x1200; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x1204; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x1208; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x120C; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x1210; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x1214; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x1218; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x121C; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x1220; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x1224; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x1228; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x122C; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x1230; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x1234; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x1238; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0x123C; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0x1240; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0x1244; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0x1248; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0x124C; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0x1250; }
         template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0x1254; }
         template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0x1258; }
      };

      class m_iBaseControlPoints
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x125C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x1260; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x1264; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x1268; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x126C; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x1270; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x1274; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x1278; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x127C; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x1280; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x1284; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x1288; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x128C; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x1290; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x1294; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x1298; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x129C; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x12A0; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x12A4; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x12A8; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x12AC; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x12B0; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x12B4; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x12B8; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0x12BC; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0x12C0; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0x12C4; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0x12C8; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0x12CC; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0x12D0; }
         template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0x12D4; }
         template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0x12D8; }
      };

      class m_bInMiniRound
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x12DC; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x12DD; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x12DE; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x12DF; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x12E0; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x12E1; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x12E2; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x12E3; }
      };

      class m_iWarnOnCap
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x12E4; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x12E8; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x12EC; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x12F0; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x12F4; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x12F8; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x12FC; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x1300; }
      };

      template<typename T = unsigned long> __forceinline static T iszWarnSound_0() { return ( T ) 0x1304; }

      class m_flPathDistance
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x1AFC; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x1B00; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x1B04; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x1B08; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x1B0C; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x1B10; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x1B14; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x1B18; }
      };

      class m_iNumTeamMembers
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x1B1C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x1B20; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x1B24; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x1B28; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x1B2C; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x1B30; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x1B34; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x1B38; }
         template<typename T = unsigned long> __forceinline static T _008() { return ( T ) 0x1B3C; }
         template<typename T = unsigned long> __forceinline static T _009() { return ( T ) 0x1B40; }
         template<typename T = unsigned long> __forceinline static T _010() { return ( T ) 0x1B44; }
         template<typename T = unsigned long> __forceinline static T _011() { return ( T ) 0x1B48; }
         template<typename T = unsigned long> __forceinline static T _012() { return ( T ) 0x1B4C; }
         template<typename T = unsigned long> __forceinline static T _013() { return ( T ) 0x1B50; }
         template<typename T = unsigned long> __forceinline static T _014() { return ( T ) 0x1B54; }
         template<typename T = unsigned long> __forceinline static T _015() { return ( T ) 0x1B58; }
         template<typename T = unsigned long> __forceinline static T _016() { return ( T ) 0x1B5C; }
         template<typename T = unsigned long> __forceinline static T _017() { return ( T ) 0x1B60; }
         template<typename T = unsigned long> __forceinline static T _018() { return ( T ) 0x1B64; }
         template<typename T = unsigned long> __forceinline static T _019() { return ( T ) 0x1B68; }
         template<typename T = unsigned long> __forceinline static T _020() { return ( T ) 0x1B6C; }
         template<typename T = unsigned long> __forceinline static T _021() { return ( T ) 0x1B70; }
         template<typename T = unsigned long> __forceinline static T _022() { return ( T ) 0x1B74; }
         template<typename T = unsigned long> __forceinline static T _023() { return ( T ) 0x1B78; }
         template<typename T = unsigned long> __forceinline static T _024() { return ( T ) 0x1B7C; }
         template<typename T = unsigned long> __forceinline static T _025() { return ( T ) 0x1B80; }
         template<typename T = unsigned long> __forceinline static T _026() { return ( T ) 0x1B84; }
         template<typename T = unsigned long> __forceinline static T _027() { return ( T ) 0x1B88; }
         template<typename T = unsigned long> __forceinline static T _028() { return ( T ) 0x1B8C; }
         template<typename T = unsigned long> __forceinline static T _029() { return ( T ) 0x1B90; }
         template<typename T = unsigned long> __forceinline static T _030() { return ( T ) 0x1B94; }
         template<typename T = unsigned long> __forceinline static T _031() { return ( T ) 0x1B98; }
         template<typename T = unsigned long> __forceinline static T _032() { return ( T ) 0x1B9C; }
         template<typename T = unsigned long> __forceinline static T _033() { return ( T ) 0x1BA0; }
         template<typename T = unsigned long> __forceinline static T _034() { return ( T ) 0x1BA4; }
         template<typename T = unsigned long> __forceinline static T _035() { return ( T ) 0x1BA8; }
         template<typename T = unsigned long> __forceinline static T _036() { return ( T ) 0x1BAC; }
         template<typename T = unsigned long> __forceinline static T _037() { return ( T ) 0x1BB0; }
         template<typename T = unsigned long> __forceinline static T _038() { return ( T ) 0x1BB4; }
         template<typename T = unsigned long> __forceinline static T _039() { return ( T ) 0x1BB8; }
         template<typename T = unsigned long> __forceinline static T _040() { return ( T ) 0x1BBC; }
         template<typename T = unsigned long> __forceinline static T _041() { return ( T ) 0x1BC0; }
         template<typename T = unsigned long> __forceinline static T _042() { return ( T ) 0x1BC4; }
         template<typename T = unsigned long> __forceinline static T _043() { return ( T ) 0x1BC8; }
         template<typename T = unsigned long> __forceinline static T _044() { return ( T ) 0x1BCC; }
         template<typename T = unsigned long> __forceinline static T _045() { return ( T ) 0x1BD0; }
         template<typename T = unsigned long> __forceinline static T _046() { return ( T ) 0x1BD4; }
         template<typename T = unsigned long> __forceinline static T _047() { return ( T ) 0x1BD8; }
         template<typename T = unsigned long> __forceinline static T _048() { return ( T ) 0x1BDC; }
         template<typename T = unsigned long> __forceinline static T _049() { return ( T ) 0x1BE0; }
         template<typename T = unsigned long> __forceinline static T _050() { return ( T ) 0x1BE4; }
         template<typename T = unsigned long> __forceinline static T _051() { return ( T ) 0x1BE8; }
         template<typename T = unsigned long> __forceinline static T _052() { return ( T ) 0x1BEC; }
         template<typename T = unsigned long> __forceinline static T _053() { return ( T ) 0x1BF0; }
         template<typename T = unsigned long> __forceinline static T _054() { return ( T ) 0x1BF4; }
         template<typename T = unsigned long> __forceinline static T _055() { return ( T ) 0x1BF8; }
         template<typename T = unsigned long> __forceinline static T _056() { return ( T ) 0x1BFC; }
         template<typename T = unsigned long> __forceinline static T _057() { return ( T ) 0x1C00; }
         template<typename T = unsigned long> __forceinline static T _058() { return ( T ) 0x1C04; }
         template<typename T = unsigned long> __forceinline static T _059() { return ( T ) 0x1C08; }
         template<typename T = unsigned long> __forceinline static T _060() { return ( T ) 0x1C0C; }
         template<typename T = unsigned long> __forceinline static T _061() { return ( T ) 0x1C10; }
         template<typename T = unsigned long> __forceinline static T _062() { return ( T ) 0x1C14; }
         template<typename T = unsigned long> __forceinline static T _063() { return ( T ) 0x1C18; }
      };

      class m_iCappingTeam
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x1C1C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x1C20; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x1C24; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x1C28; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x1C2C; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x1C30; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x1C34; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x1C38; }
      };

      class m_iTeamInZone
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x1C3C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x1C40; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x1C44; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x1C48; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x1C4C; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x1C50; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x1C54; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x1C58; }
      };

      class m_bBlocked
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x1C5C; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x1C5D; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x1C5E; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x1C5F; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x1C60; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x1C61; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x1C62; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x1C63; }
      };

      class m_iOwner
      {
       public:

         template<typename T = unsigned long> __forceinline static T _000() { return ( T ) 0x1C64; }
         template<typename T = unsigned long> __forceinline static T _001() { return ( T ) 0x1C68; }
         template<typename T = unsigned long> __forceinline static T _002() { return ( T ) 0x1C6C; }
         template<typename T = unsigned long> __forceinline static T _003() { return ( T ) 0x1C70; }
         template<typename T = unsigned long> __forceinline static T _004() { return ( T ) 0x1C74; }
         template<typename T = unsigned long> __forceinline static T _005() { return ( T ) 0x1C78; }
         template<typename T = unsigned long> __forceinline static T _006() { return ( T ) 0x1C7C; }
         template<typename T = unsigned long> __forceinline static T _007() { return ( T ) 0x1C80; }
      };

      template<typename T = unsigned long> __forceinline static T pszCapLayoutInHUD() { return ( T ) 0x1CEC; }
   };
};

#endif
