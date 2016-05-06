

#ifndef __CSSNVINTERFACE_H__
#define __CSSNVINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/

#define CSS_NV_MAX_COMM_BAND_NUM           (22)

/*目前LRRC预置频点为16个，最大个数也设为16；
  WAS预置频点9个，最大个数16；
  GAS预置频段5个，最大8个，预置频点0个，最大16个*/

#define CSS_NV_MAX_PREF_MNC_NUM            (45)
#define CSS_NV_MAX_PREF_ARFCN_NUM          (5)





/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名     : CSS_BAND_PARA_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : 配置的BAND，以及该BAND对应的接入技术
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           bitOpLteSupport: 1;
    VOS_UINT8                           bitOpTdsSupport: 1;
    VOS_UINT8                           bitOpWcdmaSupport: 1;
    VOS_UINT8                           bitOpGsmSupport: 1;
    VOS_UINT8                           bitOpSpare: 4;

    VOS_UINT8                           ucBandInd;
    VOS_UINT8                           aucReserved[2];
} CSS_BAND_PARA_STRU;

/*****************************************************************************
 结构名     : CSS_NV_COMM_BAND_CONFIG_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : 配置的COMM BAND信息时
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBandNum;
    VOS_UINT8                           aucRsv[3];
    CSS_BAND_PARA_STRU                  astBand[CSS_NV_MAX_COMM_BAND_NUM];
} CSS_NV_COMM_BAND_CONFIG_STRU;

/*****************************************************************************
 结构名     : CSS_NV_RAT_RSSI_THRESHOLD_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : 各接入技术对应的可驻留门限以及高能量门限
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   sGHighRssiThresHold;/* G模对应的高能量门限值 */
    VOS_INT16                                   sGLowRssiThresHold;/* G模对应的可驻留能量门限值 */
    VOS_INT16                                   sWHighRssiThresHold;/* W模对应的高能量门限值 */
    VOS_INT16                                   sWLowRssiThresHold;/* W模对应的可驻留能量门限值 */
    VOS_INT16                                   sLHighRssiThresHold;/* L模对应的高能量门限值 */
    VOS_INT16                                   sLLowRssiThresHold;/* L模对应的可驻留能量门限值 */
} CSS_NV_RAT_RSSI_THRESHOLD_STRU;


/*****************************************************************************
 结构名     : CSS_NV_CLOUD_STRATEGY_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : 云通信的策略是否使能
*****************************************************************************/
typedef struct
{

    VOS_UINT8                                     ucEnable;              /* 云通信功能是否打开 */

    VOS_UINT8                                     ucCssPrefFreq;         /* 云通信功能打开时，CSS运营商频点是否从云端获取 */

    VOS_UINT8                                     ucLtePrefFreq;         /* 云通信功能打开时，LTE运营商频点是否从云端获取 */

    VOS_UINT8                                     ucWcdmaPrefFreq;       /* 云通信功能打开时，WCDMA运营商频点是否从云端获取 */

    VOS_UINT8                                     ucGsmPrefFreq;         /* 云通信功能打开时，GSM运营商频点是否从云端获取 */

    VOS_UINT8                                     ucLtePrefBand;         /* 云通信功能打开时，LRRC预置band是否从云端获取 */

    VOS_UINT8                                     ucWcdmaPrefBand;       /* 云通信功能打开时，WCDMA预置band是否从云端获取 */

    VOS_UINT8                                     ucGsmPrefBand;         /* 云通信功能打开时，GSM预置band是否从云端获取 */

    VOS_UINT8                                     ucRsv1;
    VOS_UINT8                                     ucRsv2;
    VOS_UINT8                                     ucRsv3;
    VOS_UINT8                                     ucRsv4;
    VOS_UINT8                                     ucRsv5;
    VOS_UINT8                                     ucRsv6;
    VOS_UINT8                                     ucRsv7;
    VOS_UINT8                                     ucRsv8;
}CSS_NV_CLOUD_STRATEGY_STRU;


/*****************************************************************************
 结构名     : CSS_NV_PREF_ARFCN_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : 预置频点的结构，当多个离散的频点连续时，为了节省空间，组成段的结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                    ulArfcnBegin;
    VOS_UINT32                                    ulArfcnEnd;
}CSS_NV_PREF_ARFCN_STRU;

/*****************************************************************************
 结构名     : CSS_NV_PREF_MNC_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : 预置MNC的结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    bitMncDigit1: 4;/* MCC digit 1 */
    VOS_UINT16                                    bitMncDigit2: 4;/* MCC digit 2 */
    VOS_UINT16                                    bitMncDigit3: 4;/* MCC digit 3 */
    VOS_UINT16                                    bitRat      : 4;/* 制式。0:GSM 1:WCDMA 2:LTE */

    VOS_UINT8                                     ucBandInd; /* BAND指示 */
    VOS_UINT8                                     ucArfcnNum;/* 预置频点个数 */
    CSS_NV_PREF_ARFCN_STRU                        astArfcn[CSS_NV_MAX_PREF_ARFCN_NUM];
}CSS_NV_PREF_MNC_STRU;


/*****************************************************************************
 结构名     : CSS_NV_PREF_MCC_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : 预置MCC的结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    bitMccDigit1: 4;/* MCC digit 1 */
    VOS_UINT16                                    bitMccDigit2: 4;/* MCC digit 2 */
    VOS_UINT16                                    bitMccDigit3: 4;/* MCC digit 3 */
    VOS_UINT16                                    bitSpare    : 4;
    VOS_UINT16                                    usMncNum;  /* MNC个数 */
    CSS_NV_PREF_MNC_STRU                          astMnc[CSS_NV_MAX_PREF_MNC_NUM];
}CSS_NV_PREF_MCC_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CssNvInterface.h */




