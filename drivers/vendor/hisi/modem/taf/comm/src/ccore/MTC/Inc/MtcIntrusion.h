/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtcIntrusion.h
  版 本 号   : 初稿
  作    者   : l00198894
  生成日期   : 2013年8月13日
  最近修改   :
  功能描述   : MTC模块频段干扰控制裁决相关数据结构定义及函数声明
  函数列表   :
  修改历史   :
  1.日    期   : 2013年8月13日
    作    者   : l00198894
    修改内容   : V9R1 干扰项目新增

******************************************************************************/

#ifndef __MTCINTRUSION_H__
#define __MTCINTRUSION_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "MtcComm.h"
#include "MtcCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MTC_BAND_B3_BIT                 (2)
#define MTC_BAND_B8_BIT                 (7)
#define MTC_BAND_B31_BIT                (30)
#define MTC_BAND_B32_BIT                (31)
#define MTC_BAND_B39_BIT                (6)
#define MTC_BAND_B40_BIT                (7)
#define MTC_BAND_WITHOUT_B3             (0x3FFFFFFB)
#define MTC_BAND_B34_BIT                (1)

#ifndef FUNC_VOID
typedef void (*func_void_t)(void);
#define FUNC_VOID func_void_t
#endif

#define MTC_BAND_MASK_B39               (MTC_SET_BIT64(38))

#define MTC_BAND_CHECK64(band1, band2)\
            (((VOS_UINT64)(band1) & (VOS_UINT64)(band2)) ? VOS_TRUE : VOS_FALSE)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : MTC_INTRUSION_GSM_BAND_STATE_ENUM
 枚举说明  : 当前Modem1上GSM驻留频段

  1.日    期   : 2013年08月12日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
enum MTC_INTRUSION_GSM_BAND_STATE_ENUM
{
    MTC_INTRUSION_GSM_BAND_NONE         = 0x00,                                 /* 无任何频段信息(丢网) */
    MTC_INTRUSION_GSM_BAND_B31,                                                 /* 仅存在B31 */
    MTC_INTRUSION_GSM_BAND_B32,                                                 /* 仅存在B32 */
    MTC_INTRUSION_GSM_BAND_B3,                                                  /* 存在B3(B31 B32) */
    MTC_INTRUSION_GSM_BAND_OTHER,                                               /* 存在非B3 */
    MTC_INTRUSION_GSM_BAND_B31_OTHER,                                           /* 存在B31及非B3 */
    MTC_INTRUSION_GSM_BAND_B32_OTHER,                                           /* 存在B32及非B3 */
    MTC_INTRUSION_GSM_BAND_B3_OTHER,                                            /* 存在B3(B31 B32)及非B3 */

    MTC_INTRUSION_GSM_BAND_STATE_BUTT
};
typedef VOS_UINT8 MTC_INTRUSION_GSM_BAND_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MTC_INTRUSION_TL_BAND_STATE_ENUM
 枚举说明  : 当前Modem0上LTE TDS驻留频段

  1.日    期   : 2013年08月12日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
enum MTC_INTRUSION_TL_BAND_STATE_ENUM
{
    MTC_INTRUSION_TL_BAND_NONE          = 0x00,                                 /* 无任何频段信息(丢网) */
    MTC_INTRUSION_TL_BAND_WITH_B39,                                             /* 存在B39频段 */
    MTC_INTRUSION_TL_BAND_WITHOUT_B39,                                          /* 不存在B39频段 */

    MTC_INTRUSION_TL_BAND_STATE_BUTT
};
typedef VOS_UINT8 MTC_INTRUSION_TL_BAND_STATE_ENUM_UINT8;


/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : MTC_INTRUSION_RULING_STRATEGY_STRU
 结构说明  : 干扰控制裁决策略结构体

  1.日    期   : 2013年08月12日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
typedef struct
{
    MTC_INTRUSION_GSM_BAND_STATE_ENUM_UINT8         enGsmBandState;             /* modem1 GSM启用频段状态 */
    MTC_INTRUSION_TL_BAND_STATE_ENUM_UINT8          enTLBandState;              /* modem0 TDS与LTE启用频段状态 */
    MTC_CS_SERVICE_STATE_ENUM_UINT8                 enCsSrvState;               /* modem1 CS域业务状态 */
    FUNC_VOID                                       pFunc;                      /* 裁决结果执行函数 */
} MTC_INTRUSION_RULING_STRATEGY_STRU;

/*****************************************************************************
 结构名    : MTC_INTRUSION_GSM_BAND_STATE_STRU
 结构说明  : GSM频段转枚举对应表结构体

  1.日    期   : 2013年08月20日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       ucBand31;                   /* Band31启用状态 */
    VOS_UINT8                                       ucBand32;                   /* Band32启用状态 */
    VOS_UINT8                                       ucBandOther;                /* 非Band3启用状态 */
    MTC_INTRUSION_GSM_BAND_STATE_ENUM_UINT8         enGsmBandState;             /* 对应的GSM频段状态枚举值 */
} MTC_INTRUSION_GSM_BAND_STATE_STRU;

/*****************************************************************************
  5 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  6 函数声明
*****************************************************************************/
VOS_VOID MTC_SndRrcIntrusionActionSetReq(
    VOS_UINT32                          ulRecvPid,
    PS_BOOL_ENUM_UINT8                  enEnableFlag
);

VOS_VOID MTC_SndModem0IntrusionActionSetReq(
    PS_BOOL_ENUM_UINT8                  enEnableFlg
);

VOS_VOID MTC_SndModem1IntrusionActionSetReq(
    PS_BOOL_ENUM_UINT8                  enEnableFlg
);

VOS_VOID MTC_SndRrcIntrusionBandSetReq(
    VOS_UINT32                          ulRecvPid,
    RRC_MTC_MS_BAND_INFO_STRU          *pstForbiddenBandInfo
);

VOS_VOID MTC_IntrusionDisableB39(VOS_VOID);

VOS_VOID MTC_IntrusionDisableB3(VOS_VOID);

VOS_VOID MTC_IntrusionEnableB39(VOS_VOID);

VOS_VOID MTC_IntrusionEnableB3(VOS_VOID);

VOS_VOID MTC_IntrusionEnableB3B39(VOS_VOID);

VOS_VOID MTC_ProcIntrusionStrategy(VOS_VOID);

/* Modified by l00198894 for V9R1 Notch Bypass项目, 2013-12-21, begin */
VOS_VOID MTC_SndIntrusionActionSetReq(
    MODEM_ID_ENUM_UINT16                enModemId,
    PS_BOOL_ENUM_UINT8                  enEnableFlg
);

VOS_VOID MTC_IntrusionModemPowerStateChange(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enPowerState
);
/* Modified by l00198894 for V9R1 Notch Bypass项目, 2013-12-21, end */

MTC_INTRUSION_GSM_BAND_STATE_ENUM_UINT8 MTC_GetModem1GsmBandState(VOS_VOID);

MTC_INTRUSION_TL_BAND_STATE_ENUM_UINT8 MTC_GetModem0TLBandState(VOS_VOID);

VOS_VOID MTC_RcvIntrusionActionSetCnf(VOS_VOID * pMsg);

VOS_VOID MTC_RcvIntrusionBandSetCnf(VOS_VOID * pMsg);

VOS_VOID MTC_RcvIntrusionBandInfoInd(VOS_VOID * pMsg);

PS_BOOL_ENUM_UINT8 MTC_CheckM1GsmWithB3(VOS_VOID);
PS_BOOL_ENUM_UINT8 MTC_CheckM0TLWithB34B39(VOS_VOID);
VOS_VOID MTC_ProcNotchStrategy(VOS_VOID);
VOS_VOID MTC_ChangeNotchState(PS_BOOL_ENUM_UINT8 enEnableFlag);
VOS_VOID MTC_SndRrcNotchChannelInd(
    VOS_UINT32                          ulRecvPid,
    PS_BOOL_ENUM_UINT8                  enEnableFlag
);

PS_BOOL_ENUM_UINT8 MTC_CheckGsmWithB31(
    RRC_MTC_MS_BAND_INFO_STRU          *pulBandInfo
);
PS_BOOL_ENUM_UINT8 MTC_CheckGsmWithB32(
    RRC_MTC_MS_BAND_INFO_STRU          *pulBandInfo
);
VOS_VOID MTC_SndRrcBandCfgInd(
    VOS_UINT32                          ulRecvPid,
    PS_BOOL_ENUM_UINT8                  enEnableFlag
);
VOS_VOID MTC_ChangeNarrowBandDcsState(
    PS_BOOL_ENUM_UINT8                  enEnableFlag
);
VOS_VOID MTC_ProcNarrowDcsStrategy(VOS_VOID);



VOS_VOID MTC_SndI1GasRrcTdsLteRfCtrlInd(PS_BOOL_ENUM_UINT8 enUplinkCloseFlag);

VOS_VOID MTC_SndRrcRseCfgInd(
    VOS_UINT32                          ulRcvPid,
    PS_BOOL_ENUM_UINT8                  enRseOnFlag
);

VOS_VOID MTC_ProcRseStrategy(VOS_VOID);


PS_BOOL_ENUM_UINT8 MTC_ProcB39B32IntrusionStrategy(VOS_VOID);
VOS_VOID MTC_ProcB39B32Intrusion(VOS_VOID);

MTC_INTRUSION_TL_BAND_STATE_ENUM_UINT8 MTC_GetModem0NCellTLBandState(VOS_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif



