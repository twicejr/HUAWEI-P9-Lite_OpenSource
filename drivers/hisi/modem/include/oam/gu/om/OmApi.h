

/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : OmApi.h
  版 本 号   : 初稿
  作    者   : 甘兰 47350
  生成日期   : 2011年9月29日
  最近修改   :
  功能描述   : OM对外接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年1月7日
    作    者   : 甘兰 47350
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OMAPI_H__
#define __OMAPI_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "phyoaminterface.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum SPY_DATA_DOWNGRADE_RESULT_ENUM
{
    SPY_DATA_DOWNGRADE_CONTINUE              = 0,
    SPY_DATA_DOWNGRADE_FINISH                = 1,
    SPY_DATA_DOWNGRADE_RESULT_BUTT
};
typedef VOS_UINT32 SPY_DATA_DOWNGRADE_RESULT_ENUM_UINT32;

enum SPY_DATA_UPGRADE_RESULT_ENUM
{
    SPY_DATA_UPGRADE_CONTINUE              = 0,
    SPY_DATA_UPGRADE_FINISH                = 1,
    SPY_DATA_UPGRADE_RESULT_BUTT
};
typedef VOS_UINT32 SPY_DATA_UPGRADE_RESULT_ENUM_UINT32;

enum SPY_TEMPROTECT_SWITCH_STATE_ENUM
{
    SPY_TEMPROTECT_SWITCH_OFF              = 0,
    SPY_TEMPROTECT_SWITCH_ON               = 1,
    SPY_TEMPROTECT_SWITCHT_BUTT
};
typedef VOS_UINT32 SPY_TEMPROTECT_SWITCH_STATE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : TEMPPRT_AT_MSG_ID_ENUM
 结构说明  : SPY与AT消息接口枚举
*****************************************************************************/
enum TEMPPRT_AT_MSG_ID_ENUM
{
    /* SPY -> AT */
    ID_TEMPPRT_AT_EVENT_IND = 0 ,   /* _H2ASN_MsgChoice TEMP_PROTECT_EVENT_AT_IND_STRU */

    ID_TEMPPRT_STATUS_AT_EVENT_IND, /* _H2ASN_MsgChoice TEMP_PROTECT_EVENT_AT_IND_STRU */

    ID_TEMPPRT_AT_MSG_ID_BUTT

};
typedef VOS_UINT32 TEMPPRT_AT_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : SLEEP_SYSTEM_STATE_ENUM
 枚举说明  : 系统状态

  1.日    期   : 2012年07月31日
    作    者   : g47350
    修改内容   : V900R001 MSP拆分和可维可测项目新增
*****************************************************************************/
enum SLEEP_SYSTEM_STATE_ENUM
{
    SLEEP_NORMAL_STATE = 0,                             /* 正常状态 */
    SLEEP_MASTER_TEMP_LP_STATE,                         /* 主模低功耗状态(暂态) */
    SLEEP_MASTER_LP_STATE,                              /* 主模低功耗状态 */
    SLEEP_TEMP_NORMAL_STATE,                            /* 正常状态(暂态) */
    SLEEP_SLAVE_LP_STATE,                               /* 从模低功耗状态 */
    SLEEP_STATE_BUTT
};
typedef VOS_UINT32 SLEEP_SYSTEM_STATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : SLEEP_BBE16_SYSTEM_STATE_ENUM
 枚举说明  : 系统状态

  1.日    期   : 2015年08月27日
    作    者   : s00207770
    修改内容   : C模低功耗新增
*****************************************************************************/
enum SLEEP_BBE16_SYSTEM_STATE_ENUM
{
    SLEEP_BBE16_NORMAL_STATE = 0,                       /* 正常状态 */
    SLEEP_BBE16_MASTER_HALT_STATE,                      /* 主模HALT状态 */
    SLEEP_BBE16_MASTER_LP_STATE,                        /* 主模低功耗状态 */
    SLEEP_BBE16_MASTER_WAKE_STATE,                      /* 主模唤醒状态 */
    SLEEP_BBE16_MASTER_TEMP_NORMAL_STATE,               /* 主模正常状态(暂态) */
    SLEEP_BBE16_SLAVE_HALT_STATE,                       /* 从模HALT状态 */
    SLEEP_BBE16_SLAVE_LP_STATE,                         /* 从模低功耗状态 */
    SLEEP_BBE16_SLAVE_WAKE_STATE,                       /* 从模唤醒状态 */
    SLEEP_BBE16_SLAVE_TEMP_NORMAL_STATE,                /* 从模正常状态(暂态) */
    SLEEP_BBE16_STATE_BUTT
};
typedef VOS_UINT32 SLEEP_BBE16_SYSTEM_STATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    :SLEEP_MSG_ID_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  :SLEEP消息ID枚举
*****************************************************************************/
enum SLEEP_MSG_ID_ENUM
{
    ID_SLEEP_NOTIFY_STATUS_IND = 0,                         /* 进入从模低功耗，通知注册PID */

    ID_SLEEP_MSG_ID_BUTT
};
typedef VOS_UINT32 SLEEP_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    :SLEEP_LOWPOWER_STATE_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  :低功耗开关状态
*****************************************************************************/
enum SLEEP_LOWPOWER_STATE_ENUM
{
    SLEEP_LOWPOWER_STATE_OFF = 0,
    SLEEP_LOWPOWER_STATE_ON,
    SLEEP_LOWPOWER_STATE_BUTT
};
typedef VOS_UINT32 SLEEP_LOWPOWER_STATE_ENUM_UINT32;

enum OM_PCV_CHANNEL_EUNM
{
    OM_PCV_CHANNEL_OPEN = 0,
    OM_PCV_CHANNEL_CLOSE,
    OM_PCV_CHANNEL_SWITCH,
    OM_PCV_CHANNEL_BUTT
};

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef SPY_DATA_DOWNGRADE_RESULT_ENUM_UINT32 (*SPY_DOWNGRADE_PROC_FUNC)(VOS_VOID);
typedef SPY_DATA_UPGRADE_RESULT_ENUM_UINT32 (*SPY_UPGRADE_PROC_FUNC)(VOS_VOID);
typedef VOS_VOID (*SPY_RESTORE_PROC_FUNC)(VOS_VOID);

/*****************************************************************************
 结构名    : TEMP_PROTECT_EVENT_AT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SPY给AT上报的消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgId;
    VOS_UINT32                  ulTempProtectEvent;
    VOS_UINT32                  ulTempProtectParam;
} TEMP_PROTECT_EVENT_AT_IND_STRU;

/*****************************************************************************
 结构名    : SLEEP_NOTIFY_STATUS_MSG_STRU
 协议表格  : 无
 结构说明  : SLEEP进入从模低功耗，向注册PID发送状态通知

 修改历史      :
  1.日    期   : 2014年3月14日
    作    者   : L00256032
    修改内容   : V8R1 LowPower&NV_Expand项目新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ulSenderPid: WUEPS_PID_SLEEP */
    SLEEP_MSG_ID_ENUM_UINT32            enMsgId;
    VOS_RATMODE_ENUM_UINT32             enRatMode;
    SLEEP_SYSTEM_STATE_ENUM_UINT32      enState;            /* 目前固定填写SLEEP_SLAVE_LP_STATE */
    SLEEP_LOWPOWER_STATE_ENUM_UINT32    enLPState;
} SLEEP_NOTIFY_STATUS_MSG_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

extern VOS_VOID Spy_DownGradeRegister(SPY_DOWNGRADE_PROC_FUNC pFnDowngradeProcFunc);

extern VOS_VOID Spy_UpGradeRegister(SPY_UPGRADE_PROC_FUNC pFnUpgradeProcFunc);

extern VOS_VOID Spy_RestoreRegister(SPY_RESTORE_PROC_FUNC pFnRestoreProcFunc);

extern VOS_VOID GUSLEEP_MasterAwakeSlave(VOS_VOID);

extern VOS_VOID TLSLEEP_MasterAwakeSlave(VOS_VOID);

extern VOS_UINT32 SLEEP_NotifyStateReg(VOS_UINT32 ulRcvPid, VOS_RATMODE_ENUM_UINT32 enRatMode);

extern VOS_UINT32 SLEEP_NotifyStateUnreg(VOS_UINT32 ulRcvPid);

extern VOS_VOID OM_SetDrxTimerWakeSrc(MODEM_ID_ENUM_UINT16 enModem);

extern VOS_VOID OM_DelDrxTimerWakeSrc(MODEM_ID_ENUM_UINT16 enModem);

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

#endif /* end of OmApi.h */
