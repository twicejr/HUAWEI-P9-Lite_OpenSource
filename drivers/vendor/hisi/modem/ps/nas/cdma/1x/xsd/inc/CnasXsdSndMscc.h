/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdSndMscc.h
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2014年7月7日
  最近修改   :
  功能描述   : CnasXsdSndMma.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月7日
    作    者   : h00246512
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XSD_SND_MSCC_H__
#define __CNAS_XSD_SND_MSCC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "xsd_mscc_pif.h"
#include  "cas_1x_idlectrl_proc_nas_pif.h"


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

VOS_VOID CNAS_XSD_SndMsccPowerOffCnf(VOS_VOID);
VOS_VOID CNAS_XSD_SndMsccStartCnf(
    XSD_MSCC_START_RESULT_ENUM_UINT32    enRslt
);


VOS_VOID CNAS_XSD_SndMsccSysAcqCnf(
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32    enRslt
);

VOS_VOID CNAS_XSD_SndMsccSysAcqInd(
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32    enRslt
);

VOS_VOID CNAS_XSD_SndMsccSysSrvInfoInd(
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU  *pstSysInfo
);

VOS_VOID CNAS_XSD_SndMsccSysAcqStartInd(VOS_VOID);

VOS_VOID CNAS_XSD_BuildMsccSysInfoInd(
    CAS_CNAS_1X_OHM_IND_STRU           *pstCasCnas1xOhmInd,
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU  *pstXsdMmaSysInfo
);

VOS_VOID CNAS_XSD_SndMscc1xSysTimeInd(
    NAS_MSCC_PIF_1X_SYS_TIME_STRU      *pst1xSysTimeInfo
);
VOS_VOID CNAS_XSD_SndCdmaCsqSetCnf(
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8    enRslt
);

VOS_VOID CNAS_XSD_SndCdmaCsqInd(
    VOS_INT16                           sCdmaRssi,
    VOS_INT16                           sCdmaEcIo
);
VOS_VOID CNAS_XSD_SndMsccSysCfgCnf(
    CAS_CNAS_1X_SYS_CFG_CNF_STRU       *pstRcvMsg
);


VOS_VOID CNAS_XSD_SndMsccPowerSaveCnf(
    NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM_UINT8               enResult
);

extern VOS_VOID CNAS_XSD_SndMsccHandSetInfoCnf(
    XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU *pstHandSetInfo
);

VOS_VOID CNAS_XSD_SndMsccRfAvailInd(
    VOS_UINT8                           ucRfAvail
);

VOS_VOID CNAS_XSD_SndMsccSrvAcqCnf(
    NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM_UINT8                  enResult
);

VOS_VOID CNAS_XSD_SndMsccEmcCallBackInd(
    MSCC_XSD_EMC_CALLBACK_MODE_ENUM_UINT32                  enCallBackState
);

VOS_VOID CNAS_XSD_SndMsccSetCSidListCnf(
    VOS_UINT32                                              ulResult
);

VOS_VOID CNAS_XSD_SndMsccSidNidInd(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid
);

VOS_VOID CNAS_XSD_SndMsccSyncServiceAvailableInd(
    XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU               *pstSrvInfo
);

VOS_VOID CNAS_XSD_SndMsccUeStatusInd(
    VOS_UINT8                           ucUeMainState,
    VOS_UINT8                           ucUeSubState
);


VOS_VOID CNAS_XSD_SndMscc1xNoSrvInd(VOS_VOID);
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
