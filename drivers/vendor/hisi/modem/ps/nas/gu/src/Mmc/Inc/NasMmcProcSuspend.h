/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcProcSuspend.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年8月03日
  最近修改   :
  功能描述   : NasMmcProcSuspend.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年8月03日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __NAS_MMC_PROC_SUSPEND_H__
#define __NAS_MMC_PROC_SUSPEND_H__


#include  "vos.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "Nasrrcinterface.h"
#include "NasMmlCtx.h"
#include "NasMmcCtx.h"



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

VOS_VOID    NAS_MMC_SndSuspendRsp(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRC_NAS_SUSPEND_RESULT_ENUM_UINT8   enSuspendRslt
);

VOS_VOID    NAS_MMC_SndResumeRsp(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);




VOS_VOID    NAS_MMC_BulidResumeMsg(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRMM_RESUME_IND_ST                 *pstMsg
);

NAS_MML_NET_RAT_TYPE_ENUM_UINT8    NAS_MMC_GetSuspendOrigenRatType(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
);

NAS_MML_NET_RAT_TYPE_ENUM_UINT8    NAS_MMC_GetSuspendDestinationRatType(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
);

MMC_SUSPEND_CAUSE_ENUM_UINT8       NAS_MMC_GetSuspendCause(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
);

/* Added by s00246516 for L-C互操作项目, 2014-02-19, Begin */
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE)))
VOS_UINT32 NAS_MMC_IsInterSysReselectToHrpd(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
);

MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32 NAS_MMC_ConvertMsccInterSysCauseToMmcFormat(
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enMsccSuspendCause
);
#endif
/* Added by s00246516 for L-C互操作项目, 2014-02-19, End */

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_ConvertLmmSysChngDirToMmcType(
    MMC_LMM_SYS_CHNG_DIR_ENUM_UINT32    ulSysChngDir,
    MMC_SUSPEND_DESTINATION_UINT8      *penSuspendDestination,
    MMC_SUSPEND_ORIGEN_UINT8           *penSuspendOrigen
);


VOS_VOID NAS_MMC_ConvertLmmSysChngTypeToMmcType(
    MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32   enSysChngType,
    MMC_SUSPEND_CAUSE_ENUM_UINT8       *penSuspendCause
);

VOS_VOID NAS_MMC_ConvertLmmSuspendMsgToGUtype(
    LMM_MMC_SUSPEND_IND_STRU           *pstLmmSuspendIndMsg,
    RRMM_SUSPEND_IND_ST                *pstGuSuspendIndMsg
);

VOS_VOID NAS_MMC_SndLmmEquPlmn_InterSysChangeLte(VOS_VOID);

#endif

VOS_UINT32 NAS_MMC_StartResumeTimer_InterSysCellResel(VOS_VOID);

VOS_UINT32 NAS_MMC_ProcResumeRspFromLteToHrpd_InterSysCellResel(VOS_VOID);

NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32 NAS_MMC_ConvertMmcInterSysCauseToMsccFormat(
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enMmcSuspendCause
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

#endif

