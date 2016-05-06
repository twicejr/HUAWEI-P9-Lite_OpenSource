/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMsccComFunc.h
  版 本 号   : 初稿
  作    者   : W00176964
  生成日期   : 2015年4月4日
  最近修改   :
  功能描述   : NasMsccMscc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月4日
    作    者   : W00176964
    修改内容   : 创建文件

******************************************************************************/

#ifndef __NAS_MSCC_COM_FUNC_H__
#define __NAS_MSCC_COM_FUNC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasCommDef.h"
#include "NasMsccCtx.h"
#include "NasMsccMlplMsplApi.h"
#include "MsccMmcInterface.h"
#include "NasMsccSndInternalMsg.h"
#include "NasNvInterface.h"
#include "NasMsccProcNvim.h"
#include "xsd_mscc_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MSCC_CONVERT_BYTES_TO_BITS(x)                   ((x) * 8)

#define NAS_MSCC_SIM_PLMN_ID_LEN                            (3)     /* SIM卡中PLMN ID的长度 */
#define NAS_MSCC_SIM_FILE_LEN_VALID                         (0x00)  /* SIM卡文件长度合法         */
#define NAS_MSCC_PLMN_WITH_RAT_UNIT_LEN                     (5)     /* sim卡中带接入技术网络的基本元素长度，如6F62文件的基本长度单元为5 */


/* for Reboot */
#define NAS_MSCC_SoftReBoot(ulRebootScene,ulPid) NAS_MSCC_SoftReBoot_WithLineNoAndFileID( (__LINE__), (THIS_FILE_ID), (ulRebootScene),(ulPid))

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*******************************************************************************
 * Name        : NAS_MSCC_REBOOT_SCEAN_ENUM
 * Description : Reboot Scene in MSCC
 * Modify History:
 *   1)  Date    :   2015-04-13
 *       Author  :   m00270891
 *       Modify content :    Create
 *   2)  Date    :   2015-11-11
 *       Author  :   y00346957
 *       Modify content :    DTS2015070910837 增加2个异系统导致复位的枚举
 *******************************************************************************/
enum NAS_MSCC_REBOOT_SCEAN_ENUM
{
    NAS_MSCC_REBOOT_SCENE_MSCC_WAIT_XSD_POWER_SAVE_CNF_EXPIRED                   = 0X00,
    NAS_MSCC_REBOOT_SCENE_MSCC_WAIT_HSD_POWER_SAVE_CNF_EXPIRED                   = 0X01,
    NAS_MSCC_REBOOT_SCENE_MSCC_WAIT_MMC_POWER_SAVE_CNF_EXPIRED                   = 0X02,

    NAS_MSCC_REBOOT_SCENE_MSCC_WAIT_CL_INTERSYS_END_L2C_EXPIRED                  = 0X03,
    NAS_MSCC_REBOOT_SCENE_MSCC_WAIT_CL_INTERSYS_END_C2L_EXPIRED                  = 0X04,
    NAS_MSCC_REBOOT_SCENE_MSCC_WAIT_CL_INTERSYS_MMC_POWER_SAVE_CNF_L2C_EXPIRED   = 0X05,

    NAS_MSCC_REBOOT_SCENE_MSCC_BUTT                                              = 0xFF
};
typedef VOS_UINT8 NAS_MSCC_REBOOT_SCENE_ENUM_UINT8;

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


typedef struct
{
    VOS_UINT8                           aucSimPlmn[NAS_MSCC_SIM_FORMAT_PLMN_LEN];
    VOS_UINT8                           aucRsv[1];
}NAS_MSCC_SIM_FORMAT_PLMN_ID_STRU;

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
VOS_UINT32 NAS_MSCC_IsNeedPerformCLSysAcq(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetBsrTimerLen(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsNeedStartBsrTimer(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsNeedRestartBsrTimer(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsCampOnHighestPrioritySystem(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsBgSearchHighPriSysAllowed(VOS_VOID);

VOS_VOID NAS_MSCC_StartBsrTimer(VOS_VOID);

NAS_MSCC_SERVICE_STATUS_ENUM_UINT8 NAS_MSCC_Convert1xServiceStatusToMsccFormat(
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 en1xPsServiceStatus
);

NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8 NAS_MSCC_ConvertHsdSysPriClassToMsccFormat(
    MSCC_HSD_PRI_CLASS_ENUM_UINT8       enPriClass
);



VOS_VOID NAS_MSCC_Update1xSysInfo(
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU               *pst1xSrvInfoInd
);

VOS_VOID NAS_MSCC_UpdateHrpdSysInfo(
    HSD_MSCC_OVERHEAD_MSG_IND_STRU     *pstHsdOverHeadInd
);

VOS_VOID NAS_MSCC_GetHighPriSysInfoInHrpdSysInfoListWithPriClass(
    VOS_UINT8                                               ucHrpdSysNum,
    MSCC_HSD_HRPD_SYS_INFO_STRU                            *pstHrpdSysInfoList,
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enSysPriClass,
    NAS_MSCC_HIGH_PRIORITY_SYSTEM_INFO_STRU                *pstHighPriSysInfo
);

VOS_UINT32 NAS_MSCC_GetCurrentCampedSysMsplIndex(
    VOS_UINT8                          *pucMatchedMsplIndex,
    VOS_UINT8                          *pucDefMsplRec
);

VOS_VOID NAS_MSCC_GetPlmnListAccordingtoSpecMsplIndex(
    VOS_UINT8                                               ucOrigSysMsplIndex,
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstSrcPlmnList,
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstDestPlmnList
);


#endif

VOS_UINT32 NAS_MSCC_IsHrpdAndLteBothSupported(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsGULModeConfigured(VOS_VOID);

VOS_VOID  NAS_MSCC_ConvertSimPlmnToNasPlmn(
    NAS_MSCC_SIM_FORMAT_PLMN_ID_STRU   *pstSimPlmn,
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstNasPlmn
);

VOS_RATMODE_ENUM_UINT32 NAS_MSCC_ConvertNvPlatformRatToMsccType(
    PLATFORM_RAT_TYPE_ENUM_UINT16       enNvPlatformRatCap
);

VOS_UINT8 NAS_MSCC_IsPlmnIdValid(
    NAS_MSCC_PIF_PLMN_ID_STRU                              *pstPlmnId
);

VOS_UINT8 NAS_MSCC_ComparePlmn(
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstSrcPlmn,
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstDesPlmn
);

NAS_MSCC_SERVICE_STATUS_ENUM_UINT8 NAS_MSCC_ConvertMmcServiceStatusToMsccFormat(
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enMmcPsServiceStatus
);

NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8 NAS_MSCC_ConvertMmcSysPriClassToMsccFormat(
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPriClass
);

VOS_UINT32 NAS_MSCC_IsLtePlmnIdChanged(VOS_VOID);

VOS_VOID NAS_MSCC_SaveSysAcqTimerCfg(
    NAS_NVIM_MSCC_SYS_ACQ_TIMER_CFG_STRU                   *pstNvimSysAcqTimerCfg,
    NAS_MSCC_SYSACQ_TIMER_CFG_STRU                         *pstSysAcqTimerCfgInfo
);

VOS_VOID NAS_MSCC_UpdateLocationInfoToNvim(VOS_VOID);

MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32 NAS_MSCC_ConvertMmcPlmnSelRsltToMmaSysAcqRlst(
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM_UINT32          enMmcPlmnSelRslt
);

VOS_VOID NAS_MSCC_Update3gppSysInfo(
    MMC_MSCC_SYS_INFO_IND_STRU         *pstMmcSysInfo
);

VOS_VOID NAS_MSCC_GetPlmnListInPlmnPriClassListWithPriClass(
    NAS_MSCC_PIF_PLMN_PRI_CLASS_LIST_INFO_STRU             *pstPlmnPriClassListInfo,
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enSysPriClass,
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstDestPlmnList
);

VOS_UINT32 NAS_MSCC_IsPlmnPriClassMatchMsplSysPriClass(
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPriClass,
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enSysPriClass
);

VOS_RATMODE_ENUM_UINT32 NAS_MSCC_TransferMsccToVosRat(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8         enRatType
);

VOS_UINT32 NAS_MSCC_Is3gppNormalService(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsHrpdNormalService(VOS_VOID);

VOS_UINT32 NAS_MSCC_Is1xNormalService(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsNeedAcqLteFrist(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsNeedStartScanTimerUponSyscfg(VOS_VOID);

NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8 NAS_MSCC_ConvertMsplPriClassToPIfFormat(
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8   enPriClass
);

VOS_VOID NAS_MSCC_SoftReBoot_WithLineNoAndFileID(
    VOS_UINT32                          ulLineNO,
    VOS_UINT32                          ulFileID,
    NAS_MSCC_REBOOT_SCENE_ENUM_UINT8    ucResetScene,
    VOS_UINT32                          ulPid
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

#endif /* end of NasMsccComFunc.h */
