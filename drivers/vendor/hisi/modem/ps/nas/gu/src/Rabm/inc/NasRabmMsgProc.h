/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasRabmMsgProc.h
  版 本 号   : 初稿
  作    者   : anhuiqing / 00165503
  生成日期   : 2011年03月30日
  最近修改   :
  功能描述   : NasRabmMgr.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年03月30日
    作    者   : anhuiqing / 00165503
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_RABM_MSG_PROC_H_
#define _NAS_RABM_MSG_PROC_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define NAS_RABM_GetWProFuncTblAddr()               (&g_stNasRabmWProcFuncTbl)
#define NAS_RABM_GetGProFuncTblAddr()               (&g_stNasRabmGProcFuncTbl)
#if (FEATURE_ON == FEATURE_LTE)
#define NAS_RABM_GetLProFuncTblAddr()               (&g_stNasRabmLProcFuncTbl)
#endif

#define NAS_RABM_GetDataSuspendFlg()                (g_bNasRabmDataSuspendFlg)
#define NAS_RABM_SetDataSuspendFlg()                (g_bNasRabmDataSuspendFlg = VOS_TRUE)
#define NAS_RABM_ClearDataSuspendFlg()              (g_bNasRabmDataSuspendFlg = VOS_FALSE)

#define NAS_RABM_GetSysModeChgTblSize()             ((sizeof(g_astRabmSysModeChgTbl) / sizeof(NAS_RABM_SYS_CHG_TBL_STRU)))
#define NAS_RABM_GetSysModeChgTblAddr(ulIndex)      (&g_astRabmSysModeChgTbl[ulIndex])
#define NAS_RABM_GetSysModeChgTblOldMode(ulIndex)   (NAS_RABM_GetSysModeChgTblAddr(ulIndex)->enOldMode)
#define NAS_RABM_GetSysModeChgTblNewMode(ulIndex)   (NAS_RABM_GetSysModeChgTblAddr(ulIndex)->enNewMode)
#define NAS_RABM_GetSysModeChgTblProcFunc(ulIndex)  (NAS_RABM_GetSysModeChgTblAddr(ulIndex)->pSysModeChgProcFunc)

#define NAS_RABM_GetGPsEntAddr(ucEntId)             (&gastRabm2GEntity[ucEntId])
#define NAS_RABM_GetGPsEntState(ucEntId)            (NAS_RABM_GetGPsEntAddr(ucEntId)->State)

#define NAS_RABM_GetWPsEntAddr(ucEntId)             (&g_aRabmPsEnt[ucEntId])
#define NAS_RABM_GetWPsEntState(ucEntId)            (NAS_RABM_GetWPsEntAddr(ucEntId)->ucState)
#define NAS_RABM_GetWPsEntDlData(ucEntId)           (NAS_RABM_GetWPsEntAddr(ucEntId)->DlDataSave)
#define NAS_RABM_GetWPsEntUlData(ucEntId)           (NAS_RABM_GetWPsEntAddr(ucEntId)->UlDataSave)
#define NAS_RABM_GetWPsEntRabReestFlg(ucEntId)      (NAS_RABM_GetWPsEntAddr(ucEntId)->ucReEstFlg)
#define NAS_RABM_SetWPsEntRabReestFlg(ucEntId)      (NAS_RABM_GetWPsEntAddr(ucEntId)->ucReEstFlg = VOS_TRUE)
#define NAS_RABM_ClearWPsEntRabReestFlg(ucEntId)    (NAS_RABM_GetWPsEntAddr(ucEntId)->ucReEstFlg = VOS_FALSE)

#define NAS_RABM_GetCsEntAddr(ucEntId)              (&g_aRabmCsEnt[ucEntId])

#define NAS_RABM_GetRabRsestTimerFlg()              (g_ucReestTimerFlg)
#define NAS_RABM_SetRabRsestTimerFlg()              (g_ucReestTimerFlg = VOS_TRUE)
#define NAS_RABM_ClearRabRsestTimerFlg()            (g_ucReestTimerFlg = VOS_FALSE)

#define NAS_RABM_GetRauT1Flg()                      (gRabmRAT1Switch)
#define NAS_RABM_SetRauT1Flg()                      (gRabmRAT1Switch = RABM_ROUTING_AREA_UPDATE_T1_ON)
#define NAS_RABM_ClearRauT1Flg()                    (gRabmRAT1Switch = RABM_ROUTING_AREA_UPDATE_T1_OFF)

#define NAS_RABM_GetW2GT3Flg()                      (gRabm3GTo2GT3Switch)
#define NAS_RABM_SetW2GT3Flg()                      (gRabm3GTo2GT3Switch = RABM_3G_TO_2G_T3_ON)
#define NAS_RABM_ClearW2GT3Flg()                    (gRabm3GTo2GT3Switch = RABM_3G_TO_2G_T3_OFF)

#define NAS_RABM_ClearSiMapEnt()                    PS_MEM_SET(g_aucSiMapEnt, (VOS_CHAR)0xFF, sizeof(g_aucSiMapEnt))

#define NAS_RABM_GetG2WDataResumeFlg()              (gRabm2GTo3GDataResume)
#define NAS_RABM_ClearG2WDataResumeFlg()            (gRabm2GTo3GDataResume = VOS_FALSE)

#if (FEATURE_ON == FEATURE_LTE)
#define NAS_RABM_GetL2GFlg()                        (g_ulNasRabmL2GFlg)
#define NAS_RABM_SetL2GFlg()                        (g_ulNasRabmL2GFlg = VOS_TRUE)
#define NAS_RABM_ClearL2GFlg()                      (g_ulNasRabmL2GFlg = VOS_FALSE)
#endif

#define NAS_RABM_GET_RAB_PENDING_TMR_LEN()          (g_ulNasRabmRabPendingTmrLen)
#define NAS_RABM_SET_RAB_PENDING_TMR_LEN(ulTmrLen)  (g_ulNasRabmRabPendingTmrLen = (ulTmrLen))


/*****************************************************************************
  3 枚举定义
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

/*****************************************************************************
 函 数 名  : NAS_RABM_ProcSysModeChgInd
 功能描述  : WCDMA系统模式处理系统模式改变指示
 输入参数  : enOldSysMode   - RABM旧的系统模式
             enNewSysMode   - RABM新的系统模式
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_ProcSysModeChgInd(
    GMM_RABM_NET_RAT_ENUM_UINT32        enOldSysMode,
    GMM_RABM_NET_RAT_ENUM_UINT32        enNewSysMode
);


/*****************************************************************************
 函 数 名  : NAS_RABM_WProcSysModeChgToGprs
 功能描述  : 处理W模切换至G模的RABM实体状态转换
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_WProcSysModeChangeToGprs(VOS_VOID);


/*****************************************************************************
 函 数 名  : NAS_RABM_WProcSysModeChgToLte
 功能描述  : 处理W模切换至L模的RABM实体状态转换
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_WProcSysModeChangeToLte(VOS_VOID);


/*****************************************************************************
 函 数 名  : NAS_RABM_WProcDataSuspendInd
 功能描述  : WCDMA系统模式下处理挂起指示
 输入参数  : bRatChangeFlg  - 异系统切换标志
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_WProcDataSuspendInd(
    VOS_BOOL                            bRatChangeFlg
);

/*****************************************************************************
 函 数 名  : NAS_RABM_WProcDataResumeInd
 功能描述  : WCDMA系统模式下处理恢复指示
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011年7月13日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII阶段调整，向RABM指示RAB是否需要重?
*****************************************************************************/
VOS_VOID NAS_RABM_WProcDataResumeInd(
    VOS_UINT8                           ucRebuildRabFlag
);


/*****************************************************************************
 函 数 名  : NAS_RABM_GProcSysModeChgToWcdma
 功能描述  : 处理G模切换至W模的RABM实体状态转换
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_GProcSysModeChangeToWcdma(VOS_VOID);


/*****************************************************************************
 函 数 名  : NAS_RABM_GProcSysModeChgToLte
 功能描述  : 处理G模切换至L模的RABM实体状态转换
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_GProcSysModeChangeToLte(VOS_VOID);


/*****************************************************************************
 函 数 名  : NAS_RABM_GProcDataSuspendInd
 功能描述  : GPRS系统模式下处理挂起指示
 输入参数  : bRatChangeFlg  - 异系统切换标志
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_GProcDataSuspendInd(
    VOS_BOOL                            bRatChangeFlg
);


/*****************************************************************************
 函 数 名  : NAS_RABM_GProcDataResumeInd
 功能描述  : GPRS系统模式下处理恢复指示
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011年7月13日
   作    者   : w00176964
   修改内容   : V7R1 PhaseII阶段调整，向RABM指示RAB是否需要重建
*****************************************************************************/
VOS_VOID NAS_RABM_GProcDataResumeInd(
    VOS_UINT8                           ucRebuildRabFlag
);


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_RABM_LProcSysModeChgToGprs
 功能描述  : 处理W模切换至G模的RABM实体状态转换
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_LProcSysModeChangeToWcdma(VOS_VOID);


/*****************************************************************************
 函 数 名  : NAS_RABM_LProcSysModeChgToLte
 功能描述  :
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_LProcSysModeChangeToGprs(VOS_VOID);


/*****************************************************************************
 函 数 名  : NAS_RABM_LProcDataSuspendInd
 功能描述  : LTE系统模式下处理挂起指示
 输入参数  : bRatChangeFlg  - 异系统切换标志
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_LProcDataSuspendInd(
    VOS_BOOL                            bRatChangeFlg
);


/*****************************************************************************
 函 数 名  : NAS_RABM_LProcDataResumeInd
 功能描述  : LTE系统模式下处理恢复指示
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史
 1. 日    期   : 2011年7月13日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII阶段调整，向RABM指示RAB是否需要重建
*****************************************************************************/
VOS_VOID NAS_RABM_LProcDataResumeInd(
    VOS_UINT8                           ucRebuildRabFlag
);



/*****************************************************************************
 函 数 名  : NAS_RABM_LProcCommMsg
 功能描述  : LTE模式下处理WRR的消息
 输入参数  : struct MsgCB                       *pMsg
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_LProcCommMsg(
    struct MsgCB                       *pMsg
);

#endif


/*****************************************************************************
 函 数 名  : NAS_RABM_InitWProcFuncTbl
 功能描述  : 初始化WCDMA处理函数列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_InitWProcFuncTbl(VOS_VOID);


/*****************************************************************************
 函 数 名  : NAS_RABM_InitGProcFuncTbl
 功能描述  : 初始化GPRS处理函数列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_InitGProcFuncTbl(VOS_VOID);


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_RABM_InitLProcFuncTbl
 功能描述  : 初始化LTE处理函数列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_InitLProcFuncTbl(VOS_VOID);
#endif

/*****************************************************************************
 函 数 名  : NAS_RABM_InitProcFuncTbl
 功能描述  : 初始化和注册各个系统模式的处理函数表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月27日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_RABM_InitProcFuncTbl(VOS_VOID);


/*****************************************************************************
 函 数 名  : NAS_RABM_ClearRabInfo
 功能描述  : 清除指定实体ID的W模RAB信息
 输入参数  : ucEntId    - 实体ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabInfo(
    VOS_UINT8                           ucEntId
);


/*****************************************************************************
 函 数 名  : NAS_RABM_ClearRabmWPsEnt
 功能描述  : 清除指定实体ID的W模PS域实体信息
 输入参数  : VOS_UINT8                           ucEntId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabmWPsEnt(
    VOS_UINT8                           ucEntId
);


/*****************************************************************************
 函 数 名  : NAS_RABM_ClearRabmGPsEnt
 功能描述  : 清除指定实体ID的G模PS域实体信息
 输入参数  : VOS_UINT8                           ucEntId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabmGPsEnt(
    VOS_UINT8                           ucEntId
);


/*****************************************************************************
 函 数 名  : NAS_RABM_ClearRabmCsEnt
 功能描述  : 清除指定CS域实体信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabmCsEnt(VOS_VOID);


/*****************************************************************************
 函 数 名  : NAS_RABM_ClearRabReestFlg
 功能描述  : 停止RAB重建定时器, 清除RAB重建标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabReestFlg(VOS_VOID);


/*****************************************************************************
 函 数 名  : NAS_RABM_StopGprsRaT1Timer
 功能描述  : 停止rout.area.update.T1定时器
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_StopGprsRaT1Timer(VOS_VOID);


/*****************************************************************************
 函 数 名  : NAS_RABM_Stop3GTo2GT3Timer
 功能描述  : 关闭Rabm.sys.3To2.T3定时器
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_Stop3GTo2GT3Timer(VOS_VOID);


/*****************************************************************************
 函 数 名  : NAS_RABM_UpdateWPsEntFromGPsEnt
 功能描述  : PS域实体信息转换, G->W
 输入参数  : VOS_UINT8                           ucEntId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_UpdateWPsEntFromGPsEnt(
    VOS_UINT8                           ucEntId
);


/*****************************************************************************
 函 数 名  : NAS_RABM_UpdateGPsEntFromWPsEnt
 功能描述  : PS域实体信息转换, W->G
 输入参数  : VOS_UINT8                           ucEntId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_UpdateGPsEntFromWPsEnt(
    VOS_UINT8                           ucEntId
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

