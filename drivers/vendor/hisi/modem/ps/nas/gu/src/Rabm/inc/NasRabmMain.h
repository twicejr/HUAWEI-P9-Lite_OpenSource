/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasRabmMain.h
  版 本 号   : 初稿
  作    者   : anhuiqing / 00165503
  生成日期   : 2011年03月30日
  最近修改   :
  功能描述   : NasRabmMain.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年03月30日
    作    者   : anhuiqing / 00165503
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_RABM_MAIN_H_
#define _NAS_RABM_MAIN_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "AtRabmInterface.h"
#include "NVIM_Interface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define NAS_RABM_GetProFuncTblAddr(enSysMode)                   (g_pstNasRabmProcFuncTbl[enSysMode])
#define NAS_RABM_SetProFuncTblAddr(enSysMode, pstProcFucTbl)    (g_pstNasRabmProcFuncTbl[enSysMode] = (pstProcFucTbl))

#define NAS_RABM_GetCurrentSysMode()                (g_enNasRabmSysMode)
#define NAS_RABM_SetSysMode(enMode)                 (g_enNasRabmSysMode = (enMode))

/*define AP Status Mask*/
#define VP_AGPS_STATUS_MASK             (0x00000002)
#define VP_MMS_STATUS_MASK              (0x00000004)
#define VP_TETHERING_STATUS_MASK        (0x00000010)
#define VP_WIFI_HOTSPOT_STATUS_MASK     (0x00000020)
#define VP_BT_SHARING_STATUS_MASK       (0x00000040)
#define VP_SCREEN_STATUS_MASK           (0x00000080)
#define VP_ENABLE_MASK                  (0x00000100)

/* 重新查询 GMM 最大次数*/
#define VP_REQRY_GMM_MAX_TIMES          (1)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern GMM_RABM_NET_RAT_ENUM_UINT32              g_enNasRabmSysMode;


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

typedef VOS_VOID (*NAS_RABM_SYS_MODE_CHG_PROC_FUNC)(VOS_VOID);

typedef VOS_VOID (*NAS_RABM_SM_ACTIVATE_IND_PROC_FUNC)(VOS_VOID *pMsg);
typedef VOS_VOID (*NAS_RABM_SM_DEACTIVATE_IND_PROC_FUNC)(VOS_VOID *pMsg);
typedef VOS_VOID (*NAS_RABM_SM_MODIFY_IND_PROC_FUNC)(VOS_VOID *pMsg);

typedef VOS_VOID (*NAS_RABM_GMM_REESTABLISH_CNF_PROC_FUNC)(VOS_VOID *pMsg);
typedef VOS_VOID (*NAS_RABM_DATA_SUSPEND_IND_FUNC)(VOS_BOOL bRatChangeFlg);
typedef VOS_VOID (*NAS_RABM_DATA_RESUME_IND_FUNC)(VOS_UINT8 ucRebuildRabFlag);

typedef VOS_VOID (*NAS_RABM_SYS_MODE_CHG_IND_FUNC)(GMM_RABM_NET_RAT_ENUM_UINT32 enOldSysMode, GMM_RABM_NET_RAT_ENUM_UINT32 enNewSysMode);
typedef VOS_VOID (*NAS_RABM_TASK_ENTRY_FUNC)(struct MsgCB* pMsg);

/*****************************************************************************
 结构名    : NAS_RABM_PROC_FUNC_TBL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RABM消息处理函数表结构
*****************************************************************************/
typedef struct
{
    NAS_RABM_SM_ACTIVATE_IND_PROC_FUNC      pSmActivateIndProcFunc;
    NAS_RABM_SM_DEACTIVATE_IND_PROC_FUNC    pSmDeactivateIndProcFunc;
    NAS_RABM_SM_MODIFY_IND_PROC_FUNC        pSmModifyIndProcFunc;

    NAS_RABM_GMM_REESTABLISH_CNF_PROC_FUNC  pGmmReestablishCnfProcFunc;

    NAS_RABM_DATA_SUSPEND_IND_FUNC          pDataSuspendIndProcFunc;
    NAS_RABM_DATA_RESUME_IND_FUNC           pDataResumeIndProcFunc;
    NAS_RABM_SYS_MODE_CHG_IND_FUNC          pSysModeChgIndProcFunc;

    NAS_RABM_TASK_ENTRY_FUNC                pTaskEntry;

}NAS_RABM_PROC_FUNC_TBL_STRU;

/*****************************************************************************
 结构名    : NAS_RABM_SYS_CHG_TBL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  模式改变处理函数表结构
*****************************************************************************/
typedef struct
{
    GMM_RABM_NET_RAT_ENUM_UINT32        enOldMode;
    GMM_RABM_NET_RAT_ENUM_UINT32        enNewMode;
    NAS_RABM_SYS_MODE_CHG_PROC_FUNC     pSysModeChgProcFunc;

} NAS_RABM_SYS_CHG_TBL_STRU;

/*****************************************************************************
 结构名    : NAS_RABM_VOICEPREFER_CTX_STRU
 结构说明  : RABM中保存与VP相关的参数
 1.日    期   : 2014年12月26日
   作    者   : s00273135
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulApVoicePreferStatusMask;                   /* Ap侧VP生效开关 */
    VOS_UINT32 ulVoiceCallExsitFlag;                        /* 语音业务存在标志 */
    VOS_UINT32 ulCurCampMcc;                                /* 当前手机注册的十六进制BCD格式的PLMN:MCC*/
    VOS_UINT32 ulCurCampMnc;                                /* 当前手机注册的十六进制BCD格式的PLMN:MNC*/

    VOS_UINT32 ulCpVoicePreferActiveFlag;                   /* 经判决VP生效标志0:未激活;1:激活 */
    VOS_UINT32 ulReceiveApVoicePreferStopFlag;              /* 收到AP 设置停止VoicePrefer*/

    VOS_UINT32 ulNvTestMcc;                                 /* 从NV获取 用于测试的十进制PLMN:MCC*/
    VOS_UINT32 ulNvTestMnc;                                 /* 从NV获取用于测试的十进制PLMN:MNC*/

    VOS_UINT8 ucVoicePreferReQryGmmCnt;                     /* VP生效判决已经重试查询GMM的次数 */
    VOS_UINT8 ucVoicePreferNvimEnableFlag;                  /* NV 使能VP*/
    VOS_UINT8 ucReserve[2];

}NAS_RABM_VOICEPREFER_CTX_STRU;

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
 函 数 名  : NAS_RABM_RegProcFuncTbl
 功能描述  : 注册指定系统模式下的RABM函数处理表
 输入参数  : enSysMode      - 系统模式
             pstProcFucTbl  - 函数处理表
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_RegProcFuncTbl(
    GMM_RABM_NET_RAT_ENUM_UINT32        enSysMode,
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstProcFucTbl
);


/*****************************************************************************
 函 数 名  : NAS_RABM_CtxInit
 功能描述  : RABM初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_CtxInit(VOS_VOID);


/*****************************************************************************
 函 数 名  : NAS_RABM_MsgProc
 功能描述  : 处理RABM消息, 根据消息类型调用相应的处理函数
 输入参数  : struct MsgCB                       *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_MsgProc(
    struct MsgCB                       *pMsg
);


/*****************************************************************************
 函 数 名  : NAS_RABM_RcvSmMsg
 功能描述  : 处理SM消息, 根据消息类型调用对应处理函数
 输入参数  : struct MsgCB                       *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSmMsg(
    struct MsgCB                       *pMsg
);


/*****************************************************************************
 函 数 名  : NAS_RABM_ProcessGmmMsg
 功能描述  : 处理GMM消息, 根据消息类型调用对应处理函数
 输入参数  : struct MsgCB                       *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvGmmMsg(
    struct MsgCB                       *pMsg
);


/*****************************************************************************
 函 数 名  : NAS_RABM_RcvSmActivateInd
 功能描述  : 处理ID_SM_RABM_ACTIVATE_IND原语
 输入参数  : pstSmActivateInd - ID_SM_RABM_ACTIVATE_IND消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSmActivateInd(
    RABMSM_ACTIVATE_IND_STRU           *pstSmActivateInd
);


/*****************************************************************************
 函 数 名  : NAS_RABM_RcvSmDeactivateInd
 功能描述  : 处理RABMSM_DEACTIVATE_IND原语
 输入参数  : pstSmDeactivateInd - RABMSM_DEACTIVATE_IND消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSmDeactivateInd(
    RABMSM_DEACTIVATE_IND_STRU         *pstSmDeactivateInd
);


/*****************************************************************************
 函 数 名  : NAS_RABM_RcvSmModifyInd
 功能描述  : 处理RABMSM_MODIFY_IND原语
 输入参数  : pstSmModifyInd - RABMSM_MODIFY_IND消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSmModifyInd(
    RABMSM_MODIFY_IND_STRU             *pstSmModifyInd
);

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : NAS_RABM_RcvSmBearerActivateInd
 功能描述  : 处理ID_SM_RABM_BEARER_MODIFY_IND原语
 输入参数  : pstSmBearerActivateInd - ID_SM_RABM_BEARER_ACTIVATE_IND消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSmBearerActivateInd(
    SM_RABM_BEARER_ACTIVATE_IND_STRU   *pstSmBearerActivateInd
);


/*****************************************************************************
 函 数 名  : NAS_RABM_RcvSmBearerModifyInd
 功能描述  : 处理ID_SM_RABM_BEARER_DEACTIVATE_IND原语
 输入参数  : pstSmBearerModifyInd - ID_SM_RABM_BEARER_MODIFY_IND消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSmBearerModifyInd(
    SM_RABM_BEARER_MODIFY_IND_STRU     *pstSmBearerModifyInd
);


/*****************************************************************************
 函 数 名  : NAS_RABM_RcvSmBearerDeactivateInd
 功能描述  : 处理RABMSM_PDP_DEACTIVATE_IND原语
 输入参数  : pstSmBearerDeactivateInd - ID_SM_RABM_BEARER_DEACTIVATE_IND消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSmBearerDeactivateInd(
    SM_RABM_BEARER_DEACTIVATE_IND_STRU *pstSmBearerDeactivateInd
);

#endif

/*****************************************************************************
 函 数 名  : NAS_RABM_RcvGmmReestablishCnf
 功能描述  : 处理ID_GMM_RABM_REESTABLISH_CNF原语
 输入参数  : pstGmmReestablishCnf   - ID_GMM_RABM_REESTABLISH_CNF消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvGmmReestablishCnf(
    GMMRABM_REESTABLISH_CNF_STRU       *pstGmmReestablishCnf
);


/*****************************************************************************
 函 数 名  : NAS_RABM_ProcSysSrvChangeInd
 功能描述  : 处理系统状态改变指示消息, 包含系统模式和服务状态
 输入参数  : pstGmmSysSrvChgInd - ID_GMM_RABM_SYS_SRV_CHG_IND消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvGmmSysSrvChgInd(
    GMM_RABM_SYS_SRV_CHG_IND_STRU      *pstGmmSysSrvChgInd
);


/*****************************************************************************
 函 数 名  : NAS_RABM_RcvDataSuspendInd
 功能描述  : 处理挂起指示
 输入参数  : bRatChangeFlg - 异系统切换标志
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvDataSuspendInd(
    VOS_BOOL                            bRatChangeFlg
);

/*****************************************************************************
 函 数 名  : NAS_RABM_RcvDataResumeInd
 功能描述  : 处理恢复指示
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvDataResumeInd(
    VOS_UINT8                           ucRebuildRabFlag
);


/*****************************************************************************
 函 数 名  : NAS_RABM_RcvSysModeChgInd
 功能描述  : 处理系统模式改变
 输入参数  : enNewSysMode - 新的系统模式
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSysModeChgInd(
    GMM_RABM_NET_RAT_ENUM_UINT32        enNewSysMode
);


/*****************************************************************************
 函 数 名  : NAS_RABM_ProcessCommMsg
 功能描述  :
 输入参数  : struct MsgCB                       *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvCommMsg(
    struct MsgCB                       *pMsg
);

extern VOS_VOID NAS_RABM_RcvAtMsg(
    struct MsgCB                       *pMsg
);

VOS_VOID NAS_RABM_RcvCdsMsg(
    struct MsgCB                       *pMsg
);

VOS_VOID NAS_RABM_RcvCdsServiceInd(
    CDS_RABM_SERVICE_IND_STRU          *pstCdsServiceInd
);



VOS_UINT32 NAS_RABM_IsDataServiceRequestPending(VOS_VOID);
VOS_UINT32 NAS_RABM_IsRabReestablishPending(VOS_VOID);
VOS_VOID NAS_RABM_MNTN_TracePktLostEvt(
    NAS_RABM_PKT_FLOW_DIR_ENUM_UINT8    enPtkFlowDir,
    VOS_UINT8                           ucPoint
);

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
VOS_UINT32 NAS_RABM_VoicePreferGetVpStatus(VOS_VOID);
VOS_VOID NAS_RABM_VoicePreferSetVpStatus(VOS_UINT32 ulVpStatus);
VOS_UINT8 NAS_RABM_VoicePreferGetNvEnableFlag(VOS_VOID);
VOS_UINT8 NAS_RABM_VoicePreferGetReQryGmmCnt(VOS_VOID);
VOS_VOID  NAS_RABM_VoicePreferClrReQryGmmCnt(VOS_VOID);
VOS_VOID NAS_RABM_VoicePreferIncReQryGmmCnt(VOS_VOID);
VOS_UINT32 NAS_RABM_VoicePreferGetVoiceCallExsitFlag(VOS_VOID);
VOS_UINT32 NAS_RABM_VoicePreferGetStopVpFlag(VOS_VOID);
VOS_VOID NAS_RABM_VoicePreferSetStopVpFlag(VOS_UINT32 ulStopVpFlag);
VOS_UINT32 NAS_RABM_VoicePreferGetApStatusMask(VOS_VOID);
VOS_VOID NAS_RABM_VoicePreferSetApStatusMask(VOS_UINT32 ulApStatusMask);
VOS_VOID NAS_RABM_InitVoicePreferCtx(VOS_VOID);
VOS_VOID NAS_RABM_ReadVoicePreferNvim(VOS_VOID);
VOS_VOID NAS_RABM_RcvSetVoicePreferParaReq(AT_RABM_SET_VOICEPREFER_PARA_REQ_STRU *pstVoicePreferPara);
VOS_VOID NAS_RABM_RcvGetVoicePreferParaReq(
    AT_RABM_QRY_VOICEPREFER_PARA_REQ_STRU *pstVoicePreferPara);
VOS_VOID NAS_RABM_RcvVoicePreferCsExistInd(VOS_VOID *pstMsg);
VOS_UINT32 NAS_RABM_VoicePreferIsPdpActive(VOS_VOID);
VOS_UINT32 NAS_RABM_VoicePreferApStatusMatch(VOS_VOID);
VOS_UINT32 NAS_RABM_VoicePreferPlmnMatch(VOS_VOID);
VOS_UINT32 NAS_RABM_IsVpActivateMatchInStepOne(VOS_VOID);
VOS_VOID NAS_RABM_VoicePreferActivateJudgeStepOne(VOS_VOID);
VOS_VOID NAS_RABM_VoicePreferActivateJudgeStepTwo(VOS_VOID);
VOS_VOID NAS_RABM_VoicePreferDelayExpired(VOS_VOID);
VOS_VOID NAS_RABM_VoicePreferReQryGmmDelayExpired(VOS_VOID);
VOS_VOID NAS_RABM_RcvGmmVoicePreferMmlProcStatusQryCnf(
    struct MsgCB                       *pstMsg
);

#endif

#if (FEATURE_ON == FEATURE_BASTET)
VOS_VOID NAS_RABM_RcvBastetMsg(
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

#endif

