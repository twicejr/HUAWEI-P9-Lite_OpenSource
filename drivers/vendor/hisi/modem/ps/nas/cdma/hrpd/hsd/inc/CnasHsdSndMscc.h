/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdSndMscc.h
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年12月7日
  最近修改   :
  功能描述   : CnasHsdSndMscc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月17日
    作    者   : h00300778
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_HSD_SND_MSCC_H__
#define __CNAS_HSD_SND_MSCC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "hsd_mscc_pif.h"

#include  "cas_hrpd_overheadmsg_nas_pif.h"

#include  "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "CnasPrlParse.h"



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

extern VOS_VOID CNAS_HSD_SndMsccPowerOffCnf(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndMsccStartCnf(HSD_MSCC_START_RESULT_ENUM_UINT32 enRslt);

extern VOS_VOID CNAS_HSD_SndMsccSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32 enRslt);

extern VOS_VOID CNAS_HSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32 enRslt);

extern VOS_VOID CNAS_HSD_SndMsccSysAcqStartInd(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndMsccHrpdIratToLteNtf(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32 enRslt);

extern VOS_VOID CNAS_HSD_SndMsccSessionNegRsltInd(
    VOS_UINT8                                   ucNegRslt,
    VOS_UINT8                                   ucIsNewSession,
    HSD_MSCC_SESSION_RELEASE_TYPE_ENUM_UINT32   enCurrSessionRelType,
    VOS_UINT8                                   ucIsEhrpdSupport
);

extern VOS_VOID CNAS_HSD_SndMsccOverheadMsgInd(
    CAS_CNAS_HRPD_OVERHEAD_MSG_IND_STRU                    *pstCasOhmMsg,
    CNAS_PRL_HRPD_SYSTEM_STRU                              *pstHrpdSys
);

extern VOS_VOID CNAS_HSD_SndMsccSysCfgCnf(
    CAS_CNAS_HRPD_SYS_CFG_CNF_STRU     *pstRcvMsg
);

extern VOS_VOID CNAS_HSD_SndMsccHrpdCasStatusInd(
    HSD_MSCC_HRPD_CAS_STATUS_ENUM_UINT16                    enHrpdCasStatus
);

extern VOS_VOID CNAS_HSD_SndMsccPowerSaveCnf(
    NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM_UINT8               enRslt
);

extern VOS_VOID CNAS_HSD_SndMsccBgSearchCnf(
    CAS_CNAS_HRPD_BSR_LTE_CNF_STRU     *pstMsg
);

extern VOS_VOID CNAS_HSD_SndMsccHrpdSysInfoCnf(
    VOS_UINT8                            ucHrpdSysNum,
    MSCC_HSD_HRPD_SYS_INFO_STRU         *pstHrpdSysInfoList
);

extern VOS_VOID CNAS_HSD_SndMsccStopBgSearchCnf(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndMsccSystemSyncInd(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndMsccInterSysStartInd(
    VOS_RATMODE_ENUM_UINT32                                 enOrignRatMode,
    VOS_RATMODE_ENUM_UINT32                                 enDestRatMode,
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enInterSysCause
);

extern VOS_VOID CNAS_HSD_SndMsccInterSysEndInd(
    VOS_RATMODE_ENUM_UINT32             enCurrRatMode
);

extern VOS_VOID CNAS_HSD_SndMsccRfAvailInd(
    VOS_UINT8                           ucRfAvail
);

VOS_VOID CNAS_HSD_SndMsccHrpdNoSrvInd(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndMsccHdrCsqSetCnf(
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8      enRslt
);

VOS_VOID CNAS_HSD_SndMsccHdrCsqQualityInd(
    VOS_INT16                            sHrpdRssi,
    VOS_INT16                            sHrpdSnr,
    VOS_INT16                            sHrpdEcio
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

#endif /* end of CnasHsdSndMscc.h */

