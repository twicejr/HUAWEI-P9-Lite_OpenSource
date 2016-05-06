/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaSndTaf.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年10月10日
  最近修改   :
  功能描述   : TafMmaSndTaf.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月10日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _TAF_MMA_SND_TAF_H_
#define _TAF_MMA_SND_TAF_H_
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasStkInterface.h"
#include "MmaMsccInterface.h"

#include "TafMmaInterface.h"

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
VOS_VOID TAF_MMA_SndPowerIndMsg(VOS_VOID);

VOS_VOID TAF_MMA_SndSpmServiceStatusChangeNotify(VOS_VOID);
VOS_VOID TAF_MMA_SndSpmNetworkCapabilityChangeNotify(VOS_VOID);
VOS_VOID TAF_MMA_SndSpmRatChangeNotify(VOS_VOID);

VOS_VOID TAF_MMA_SndMsgCsServiceChangeNotify(
    TAF_CS_SERVICE_ENUM_UINT32          enCsState
);

VOS_VOID MN_PH_SndMsgUsimStatus(VOS_UINT32  ulUsimSta);

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-31, begin */
#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID TAF_MMA_SndSpmImsVoiceCapInd(
    VOS_UINT8                           ucAvail
);

#endif
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-31, end */

VOS_VOID TAF_MMA_SndPowerOnIndMsg(VOS_VOID);


VOS_VOID TAF_MMA_SndTaf1XServiceStatusInd(
    VOS_UINT32                          ulExist1XService
);




VOS_VOID TAF_MMA_SndApsEpdszidInfoInd(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid,
    VOS_UINT8                           ucPzid
);

VOS_VOID TAF_MMA_SndPrefPlmnSetCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt
);

VOS_VOID TAF_MMA_SndPrefPlmnQueryCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt,
    MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU                      *pstRcvMsg
);

VOS_VOID TAF_MMA_SndPrefPlmnTestCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt,
    MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU                      *pstRcvMsg
);

VOS_VOID TAF_MMA_SndTafCLServiceStatusInd(
    MMA_TAF_CL_STATUS_ENUM_UINT32       enClStatus,
    VOS_UINT8                           ucIsNewSession
);


VOS_VOID TAF_MMA_SndTafHrpdDataCallSysAcqInd(
    MMA_TAF_HRPD_DATA_CALL_SYS_ACQ_RST_ENUM_UINT32          enHrpdSysAcqRst,
    NAS_MSCC_PIF_PS_RAT_TYPE_ENUM_UINT32                    enRatType
);


VOS_VOID TAF_MMA_SndTafSysCfgInfoInd(
    TAF_MMA_RAT_ORDER_STRU             *pstOldRatOrder,
    TAF_MMA_RAT_ORDER_STRU             *pstNewRatOrder
);

VOS_VOID TAF_MMA_SndSrvAcqCnf(
    TAF_MMA_SRV_ACQ_RESULT_ENUM_UINT8   enResult
);

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

#endif /* end of TafMmaSndTaf.h */

