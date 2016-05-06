/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdFsmSysAcq.h
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年12月9日
  最近修改   :
  功能描述   : CnasHsdFsmSysAcq.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月9日
    作    者   : h00300778
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_HSD_FSM_SYS_ACQ_H__
#define __CNAS_HSD_FSM_SYS_ACQ_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasHsdCtx.h"
#include  "cas_hrpd_airlinkmgmt_nas_pif.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BIT_N(num)          ((VOS_UINT32)0x01 << (num))

#define CNAS_HSD_POWER_ON_SYS_ACQ           (0) /* 收到MSCC发的开机搜网请求 */

#define CNAS_HSD_HIGH_PRI_SYS_ACQ           (1) /* 收到MSCC发的高优先级搜网请求 */

#define CNAS_HSD_OTHER_SYS_ACQ              (2) /* 收到MSCC发的other搜网请求 */

#define CNAS_HSD_SYS_ACQ_1X_SYS_ACQ         (4) /* 收到1X上报的的搜网结果 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CNAS_HSD_SYS_ACQ_STATUS_ENUM
 枚举说明  : 定义当前在混合模式下收到MMA搜网和1X搜网结果上报的状态
 1.日    期   : 2014年12月16日
   作    者   : h00300778
   修改内容   : 新建
*****************************************************************************/
enum CNAS_HSD_SYS_ACQ_STATUS_ENUM
{
    CNAS_HSD_SYS_ACQ_NULL                   = VOS_NULL,
    CNAS_HSD_SYS_ACQ_POWER_ON_RCV           = BIT_N(CNAS_HSD_POWER_ON_SYS_ACQ),
    CNAS_HSD_SYS_ACQ_HIGH_PRI_RCV           = BIT_N(CNAS_HSD_HIGH_PRI_SYS_ACQ),
    CNAS_HSD_SYS_ACQ_OTHER_RCV              = BIT_N(CNAS_HSD_OTHER_SYS_ACQ),
    CNAS_HSD_SYS_ACQ_1X_SYS_ACQ_RCV         = BIT_N(CNAS_HSD_SYS_ACQ_1X_SYS_ACQ),
};

typedef VOS_UINT32 CNAS_HSD_SYS_ACQ_STATUS_ENUM_UINT32;



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


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_VOID CNAS_HSD_SndSysAcqAbortRlst(VOS_VOID);
extern VOS_UINT32  CNAS_HSD_RcvMsccSysAcqReq_SysAcq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvHsdSysAcqReq_SysAcq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasSysSyncCnf_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvTiWaitCasSysSyncCnfExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasStopSysSyncCnf_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvTiWaitCasStopSysSyncCnfExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasOverheadInd_SysAcq_WaitCasInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvTiWaitCasOhmIndExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasRedirectionInd_SysAcq_WaitCasInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvTiAvailableTimerExpired_WaitMru0(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasIndProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID CNAS_HSD_QuitFsmSysAcq_SysAcq(VOS_VOID);

extern VOS_VOID CNAS_HSD_SetSysAcqStatusByBit(VOS_UINT32 ulBit);

extern CNAS_HSD_SYS_ACQ_STATUS_ENUM_UINT32 CNAS_HSD_GetSysAcqStatus(VOS_VOID);

extern VOS_VOID  CNAS_HSD_CleanSysAcqStatus(VOS_VOID);

extern VOS_VOID  CNAS_HSD_ClearSysAcqStatusBit(VOS_UINT32 ulBit);

extern CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_HSD_GetCurSysAcqScene_SysAcq(VOS_VOID);

extern VOS_UINT32 CNAS_HSD_CasSysAcqVaildFreqCheck(CAS_CNAS_HRPD_SYSTEM_SYNC_CNF_STRU *pstSyncCnf);

extern VOS_UINT32 CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitCasInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasPilotSearchStopInd_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasPilotSearchStopInd_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasPilotSearchStopInd_SysAcq_WaitCasInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitCasInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvSessionNegRsltInd_SysAcq_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvTiWaitSessionNegIndExpired_SysAcq_WaitSessionNegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitSessionIndProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasRedirectionInd_SysAcq_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasNoRf_SysAcq_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasOhmInd_SysAcq_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID CNAS_HSD_ProcCasSyncCnfSucc_SysAcq(
    CAS_CNAS_HRPD_SYSTEM_SYNC_CNF_STRU *pstSyncCnf
);

extern VOS_VOID CNAS_HSD_ProcCasSyncCnfFail_SysAcq(
    CAS_CNAS_HRPD_SYSTEM_SYNC_CNF_STRU *pstSyncCnf
);

VOS_VOID CNAS_HSD_ProcCasSyncCnfNoRf_SysAcq(CAS_CNAS_HRPD_SYSTEM_SYNC_CNF_STRU *pstSyncCnf);


extern VOS_UINT32 CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSD_RcvCasNoRf_SysAcq_WaitCasInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSD_RcvCasSyncCnf_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID  CNAS_HSD_ClearHrpdSysAcqStatusBits(VOS_VOID);

extern VOS_UINT32 CNAS_HSD_RcvHsmConnOpenInd_WaitSessionInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CnasHsdFsmSysAcq.h */

