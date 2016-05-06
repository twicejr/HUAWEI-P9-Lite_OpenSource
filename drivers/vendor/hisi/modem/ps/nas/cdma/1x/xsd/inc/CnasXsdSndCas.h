/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdSndCas.h
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2014年7月7日
  最近修改   :
  功能描述   : CnasXsdSndCas.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月7日
    作    者   : h00246512
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XSD_SND_CAS_H__
#define __CNAS_XSD_SND_CAS_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasXsdCtx.h"
#include  "cas_1x_control_initialstate_nas_pif.h"
#include  "cas_1x_control_main_nas_pif.h"
#include  "CnasXsdCtx.h"

#include "PsRrmInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


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


VOS_VOID CNAS_XSD_SndCasPowerOffReq(VOS_VOID);

VOS_VOID CNAS_XSD_SndCasStartReq(
    MSCC_XSD_START_REQ_STRU            *pstRcvMsg
);

VOS_VOID CNAS_XSD_SndCasSysSyncReq(
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreqList
);


VOS_VOID CNAS_XSD_SndCasStopSysSyncReq(VOS_VOID);


VOS_VOID CNAS_XSD_SndCas1xCampSyncedChannelNtf(VOS_VOID);

VOS_UINT32 CNAS_XSD_SndCasCdmaCsqSetReq(
    VOS_UINT8                                               ucRssiRptThreshold,
    VOS_UINT8                                               ucEcIoRptThreshold,
    VOS_UINT8                                               ucTimeInterval
);
VOS_UINT32 CNAS_XSD_SndCasCFreqLockNtf(MSCC_XSD_CFREQ_LOCK_NTF_STRU   *pstMmaXsdCFreqLockNtf);

VOS_VOID CNAS_XSD_SndCasSysCfgReq(
    MSCC_XSD_SYS_CFG_REQ_STRU          *pstRcvMsg
);

VOS_VOID CNAS_XSD_SndCasSuspendReq(VOS_VOID);

VOS_VOID CNAS_XSD_SndRrmRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType
);

VOS_VOID CNAS_XSD_SndRrmDeRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType
);

VOS_VOID CNAS_XSD_SndCasBeginSessionNotify(
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType
);

VOS_VOID CNAS_XSD_SndCasEndSessionNotify(
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType
);

VOS_VOID CNAS_XSD_SndCasAvailableCampQueryCnf(
    VOS_UINT16                          usOpId,
    PS_BOOL_ENUM_UINT8                  enIsCurSysCanCamp
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

#endif /* end of CnasXsdSndMscc.h */
