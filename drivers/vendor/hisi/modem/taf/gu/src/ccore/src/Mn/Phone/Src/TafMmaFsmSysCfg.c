/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaFsmSysCfg.c
  版 本 号   : 初稿
  作    者   : l00301449
  生成日期   : 2015年04月07日
  功能描述   : Sys Cfg状态机
  函数列表   :
  修改历史   :
  1.日    期   : 2015年04月07日
    作    者   : l00301449
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafMmaFsmSysCfg.h"
#include "TafMmaFsmSysCfgTbl.h"
#include "TafMmaCtx.h"
#include "TafMmaSndApp.h"
#include "TafAppMma.h"
#include "TafMmaSndInternalMsg.h"
#include "TafMmaSndMscc.h"
#include "TafMmaSndTaf.h"
#include "Taf_Status.h"
#include "TafMmaComFunc.h"
#include "TafMmaSndMtc.h"

#include "TafLog.h"

#include "NasComm.h"


#include "NasMsccPifInterface.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_MMA_FSM_SYS_CFG_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
extern STATUS_CONTEXT_STRU              g_StatusContext;

extern TAF_MMA_GLOBAL_VALUE_ST          gstMmaValue;

TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU g_astOperTypeFromGULToCLTab[TAF_MMA_GUL_RAT_SUBMODE_BUTT][TAF_MMA_CL_RAT_SUBMODE_BUTT] =
{
    /**********************************************************************************************
                    |     BYTE 1     |      BYTE 2     |       BYTE 3     | BYTE 4  |
                    {detach operation, attach operation, sys cfg operation, reserved}

     注:  1) L->1X/HRPD/L之间RAT变化，在g_stOperTypeFromCLtoCLTab表中完成，这里全0
          2) G/U/L->L之间的RAT变化，属于GUL之间的RAT变化，表里全0
     **********************************************************************************************/
                       /*  to 1X   ,    to  HRPD ,      to L   ,      to C   ,   to 1X&L   ,  to HRPD&L  ,    to C&L  */
    /* from G   */     {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {1, 0, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}},
    /* from U   */     {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {1, 0, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}},
    /* from L   */     {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {1, 0, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}},
    /* from GU  */     {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {1, 0, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}},
    /* from GL  */     {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {1, 0, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}},
    /* from UL  */     {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {1, 0, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}},
    /* from GUL */     {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {1, 0, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}}
};

TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU g_astOperTypeFromCLToGULTab[TAF_MMA_CL_RAT_SUBMODE_BUTT][TAF_MMA_GUL_RAT_SUBMODE_BUTT] =
{
    /**********************************************************************************************
                    |     BYTE 1     |      BYTE 2     |       BYTE 3     | BYTE 4  |
                    {detach operation, attach operation, sys cfg operation, reserved}

     注:  1) L->G/U/L之间RAT变化，属于GUL之间的变化，表里全0
          2) 1X/HRPD/L->L之间的变化，在g_stOperTypeFromCLtoCLTab表中完成，这里全0
     **********************************************************************************************/

                       /*  to G    ,     to U    ,      to L   ,     to GU   ,     to GL   ,     to UL   ,   to GUL  */
    /* from 1X      */ {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}},
    /* from HRPD    */ {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}},
    /* from L       */ {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    /* from C       */ {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}},
    /* from 1X&L    */ {{1, 1, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}},
    /* from HRPD&L  */ {{1, 1, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}},
    /* from C&L     */ {{1, 1, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}}
};

TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU g_astOperTypeFromCLtoCLTab[TAF_MMA_CL_RAT_SUBMODE_BUTT][TAF_MMA_CL_RAT_SUBMODE_BUTT] =
{
    /**********************************************************************************************
     |     BYTE 1     |      BYTE 2     |       BYTE 3     | BYTE 4  |
     {detach operation, attach operation, sys cfg operation, reserved}

     注:  1) 如果仅RAT顺序发生变化，而RAT本身没有新增与减少，这里全填0，如1X&L->L&1X, 1X&HRPD->HRPD&1X
     **********************************************************************************************/

                       /*  to 1X   ,    to  HRPD ,      to L   ,     to C   ,    to 1X&L   ,   to HRPD&L ,  to C&L   */
    /* from 1X      */ {{0, 0, 0, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}},
    /* from HRPD    */ {{0, 0, 1, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}},
    /* from L       */ {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {1, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
    /* from C       */ {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}},
    /* from 1X&L    */ {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
    /* from HRPD&L  */ {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}},
    /* from C&L     */ {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}
};

/* 移该数组到TafMmaComFunc.c文件 */

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvSysCfgSetReq_SysCfg_Init
 功能描述  : 在TAF_MMA_SYS_CFG_STA_INIT状态收到ID_TAF_MMA_SYS_CFG_SET_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月8日
    作    者   : l00301449
    修改内容   : 新生成函数
  2.日    期   : 2015年12月3日
    作    者   : w00176964
    修改内容   : DTS2015061601845:增加原始SYSCFG触发的操作类型

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvSysCfgSetReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_SYS_CFG_REQ_STRU                               *pstRcvMsg        = VOS_NULL_PTR;
    TAF_MMA_SYS_CFG_OPER_TYPE                               usOperType;
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8                         enDetachReason;
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                    *pstLastSyscfgSet = VOS_NULL_PTR;

    /* 保存入口消息 */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    pstRcvMsg        = (TAF_MMA_SYS_CFG_REQ_STRU *)pstMsg;

    /* 在状态机上下文中保存syscfg的参数。注: 该设置不要随意移动位置 */
    TAF_MMA_SetSysCfgPara_SysCfg(&(pstRcvMsg->stSysCfgPara));

    usOperType       = TAF_MMA_SYS_CFG_NONE_SET;

    enDetachReason   = TAF_MMA_DETACH_CAUSE_BUTT;

    TAF_MMA_GetSysCfgOperType_SysCfg(&(pstRcvMsg->stSysCfgPara),
                                     &usOperType,
                                     &enDetachReason);

    /* 无需设置直接上报成功 */
    if (TAF_MMA_SYS_CFG_NONE_SET == usOperType)
    {
        pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();

        TAF_MMA_SndSysCfgSetCnf(&(pstRcvMsg->stCtrl), TAF_ERR_NO_ERROR);

        /* 不设置的情况需要将接入优先级写入NVIM中 */
        TAF_MMA_UpdatePrioAccessMode(&(pstRcvMsg->stSysCfgPara), pstLastSyscfgSet);

        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_SUCC, VOS_FALSE);

        /* 退出状态机 */
        TAF_MMA_FSM_QuitSubFsm();

        return VOS_TRUE;
    }

    /* 在状态机上下文中记录操作类型 */
    TAF_MMA_SetSysCfgOperType_SysCfg(usOperType);

    TAF_MMA_SaveSysCfgOrigOperType_SysCfg(usOperType);

    /* 根据操作类型执行操作，并返回结果 */
    TAF_MMA_ProcSysCfgOper_SysCfg(&(pstRcvMsg->stSysCfgPara),
                                  usOperType,
                                  enDetachReason);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvInterSysCfgSetReq_SysCfg_Init
 功能描述  : 在TAF_MMA_SYS_CFG_STA_INIT状态收到MMA_MMA_INTER_SYS_CFG_SET_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : l00301449
    修改内容   : 新生成函数
  2.日    期   : 2015年12月3日
    作    者   : w00176964
    修改内容   : DTS2015061601845:增加原始SYSCFG触发的操作类型

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvInterSysCfgSetReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_INTER_SYS_CFG_SET_REQ_STRU *pstRcvMsg = VOS_NULL_PTR;
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType;
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8     enDetachReason;

    /* 保存入口消息 */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    pstRcvMsg        = (TAF_MMA_INTER_SYS_CFG_SET_REQ_STRU *)pstMsg;

    usOperType       = TAF_MMA_SYS_CFG_NONE_SET;

    enDetachReason   = TAF_MMA_DETACH_CAUSE_BUTT;

    TAF_MMA_GetSysCfgOperType_SysCfg(&(pstRcvMsg->stSysCfgPara), &usOperType, &enDetachReason);

    /* 无需设置直接上报成功 */
    if (TAF_MMA_SYS_CFG_NONE_SET == usOperType)
    {
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_SUCC, VOS_FALSE);

        /* 退出状态机 */
        TAF_MMA_FSM_QuitSubFsm();
    }
    else
    {
        /* 在状态机上下文中记录操作类型 */
        TAF_MMA_SetSysCfgOperType_SysCfg(usOperType);

        TAF_MMA_SaveSysCfgOrigOperType_SysCfg(usOperType);

        /* 在状态机上下文中保存syscfg的参数 */
        TAF_MMA_SetSysCfgPara_SysCfg(&(pstRcvMsg->stSysCfgPara));

        /* 根据操作类型执行操作，并返回结果 */
        TAF_MMA_ProcSysCfgOper_SysCfg(&(pstRcvMsg->stSysCfgPara),
                                      usOperType,
                                      enDetachReason);

    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvAttachReq_SysCfg_Init
 功能描述  : 在TAF_MMA_SYS_CFG_STA_INIT状态收到TAF_MSG_MMA_ATTACH消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : l00301449
    修改内容   : 新生成函数
  2.日    期   : 2015年12月3日
    作    者   : w00176964
    修改内容   : DTS2015061601845:增加原始SYSCFG触发的操作类型

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAttachReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucOpID;
    TAF_MMA_ATTACH_REQ_STRU                                *pstAttachReqMsg = VOS_NULL_PTR;
    TAF_MMA_SYS_CFG_OPER_TYPE                               usOperType;
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32                    enMsccAttachType;

    /* 保存入口消息 */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    pstAttachReqMsg     = (TAF_MMA_ATTACH_REQ_STRU *)pstMsg;

    ucOpID              = TAF_MMA_GetAttachOpId();

    usOperType          = TAF_MMA_SYS_CFG_NONE_SET;

    enMsccAttachType    = NAS_MSCC_PIF_ATTACH_TYPE_BUTT;

    TAF_MMA_GetAttachOperType_SysCfg(pstAttachReqMsg->enAttachType, &usOperType);

    if (VOS_OK == TAF_MMA_ConvertAttachTypeToMscc(pstAttachReqMsg->enAttachType, &enMsccAttachType))
    {
        (VOS_VOID)TAF_MMA_SndMsccAttachReq(ucOpID, enMsccAttachType, TAF_MMA_ATTACH_REASON_INITIAL);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvAttachReq_SysCfg_Init():Wrong AttachType!");
    }

    /* 启动保护定时器 */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_ATTACH_CNF, TI_TAF_MMA_WAIT_MSCC_ATTACH_CNF_LEN);

    /* 迁到TAF_MMA_SYS_CFG_STA_WAIT_ATTACH_CNF状态 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_SYS_CFG_STA_WAIT_ATTACH_CNF);

    TAF_MMA_SetAttachAllowFlg(pstAttachReqMsg->enAttachType);

    /* 状态机上下文中保存attach请求的Op Id */
    TAF_MMA_SetAttachOpId_SysCfg(ucOpID);

    /* 状态机上下文中保存操作类型 */
    TAF_MMA_SetSysCfgOperType_SysCfg(usOperType);

    TAF_MMA_SaveSysCfgOrigOperType_SysCfg(usOperType);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvDetachReq_SysCfg_Init
 功能描述  : 在TAF_MMA_SYS_CFG_STA_INIT状态收到ID_TAF_MMA_DETACH_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : l00301449
    修改内容   : 新生成函数
  2.日    期   : 2015年4月13日
    作    者   : h00313353
    修改内容   : SysCfg重构
  3.日    期   : 2015年12月3日
    作    者   : w00176964
    修改内容   : DTS2015061601845:增加原始SYSCFG触发的操作类型
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvDetachReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_DETACH_REQ_STRU                                *pstDetachReqMsg = VOS_NULL_PTR;
    NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32                    enMsccDetachType;
    TAF_MMA_SYS_CFG_OPER_TYPE                               usOperType;
    TAF_MMA_DETACH_TYPE_ENUM_UINT8                          enDetachType;

    /* 初始化 */
    pstDetachReqMsg     = (TAF_MMA_DETACH_REQ_STRU *)pstMsg;
    usOperType          = TAF_MMA_SYS_CFG_NONE_SET;
    enMsccDetachType    = NAS_MSCC_PIF_DETACH_TYPE_BUTT;

    /* 保存入口消息 */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 获取Detach操作标识 */
    usOperType      = TAF_MMA_GetDetachOperType_SysCfg(pstDetachReqMsg->stDetachPara.enDetachDomain);

    /* 获取DetachType */
    enDetachType    = TAF_MMA_GetDetachTypeFromSysCfgOperType_SysCfg(usOperType);

    (VOS_VOID)TAF_MMA_ConvertDetachTypeToMscc(enDetachType, &enMsccDetachType);

    /* 向MSCC发送Detach Req消息 */
    (VOS_VOID)TAF_MMA_SndMsccDetachReq(pstDetachReqMsg->stCtrl.ucOpId,
                                       enMsccDetachType,
                                       TAF_MMA_DETACH_CAUSE_USER_DETACH);

    /* 启动外部模块初始化保护定时器 */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_DETACH_CNF, TI_TAF_MMA_WAIT_MSCC_DETACH_CNF_LEN);

    /* 设置状态机状态 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_SYS_CFG_STA_WAIT_DETACH_CNF);

    /* 在状态机上下文中记录操作类型 */
    TAF_MMA_SetSysCfgOperType_SysCfg(usOperType);

    TAF_MMA_SaveSysCfgOrigOperType_SysCfg(usOperType);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcDetachCnfTriggeredByDetachReq_SysCfg
 功能描述  : 在TAF_MMA_SYS_CFG_STA_WAIT_DETACH_CNF状态收到ID_MSCC_MMA_DETACH_CNF且入口消息为DETACH REQ的处理
 输入参数  : MSCC_MMA_DETACH_CNF_STRU           *pstDetachCnf
             TAF_MMA_CTRL_STRU                  *pstCtrl
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月14日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ProcDetachCnfTriggeredByDetachReq_SysCfg(
    MSCC_MMA_DETACH_CNF_STRU           *pstDetachCnf,
    TAF_MMA_CTRL_STRU                  *pstCtrl
)
{
    TAF_MMA_FSM_SYS_CFG_CTX_STRU       *pstSysCfgCtx = VOS_NULL_PTR;
    TAF_ERROR_CODE_ENUM_UINT32          enPhoneError;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enDetachRslt;
    TAF_MMA_SYS_CFG_RSLT_ENUM_UINT8     enSysCfgRslt;

    /* 获取当前状态机的上下文 */
    pstSysCfgCtx = &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx);

    enDetachRslt = TAF_MMA_APP_OPER_RESULT_SUCCESS;
    enSysCfgRslt = TAF_MMA_SYS_CFG_RSLT_DETACH_SUCCESS;
    enPhoneError = TAF_ERR_NO_ERROR;

    if (NAS_MSCC_PIF_OPER_RESULT_REJECT == pstDetachCnf->enOperRslt)
    {
        enSysCfgRslt = TAF_MMA_SYS_CFG_RSLT_DETACH_FAIL;

         /* 停止保护定时器 */
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_DETACH_CNF);

        TAF_MMA_SndDetachCnf(pstCtrl, TAF_MMA_APP_OPER_RESULT_REJECT, TAF_MMA_SYS_CFG_RSLT_DETACH_FAIL);

        /* 发送状态机退出结果消息 */
        TAF_MMA_SndSysCfgRsltInd(enSysCfgRslt, FALSE);

        /* 退出状态机 */
        TAF_MMA_FSM_QuitSubFsm();

        return;
    }

    /* 上报detach结果 */
    /* 只上报当前有效的域状态 */
    if (NAS_MSCC_PIF_SRVDOMAIN_CS == pstDetachCnf->enCnDomainId)
    {
        /* 服务状态上报，统一放到Sta_ServiceStatusInd()处理,attach cnf 和 detach cnf不再做处理 */

        /*增加判断DETACH结果的原因值*/
        if (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == pstDetachCnf->enServiceStatus)
        {
            enPhoneError = TAF_ERR_PHONE_DETACH_FORBIDDEN;
        }

        /*清除CS DETACH标志*/
        pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_CS_DETACH_SET;

        TAF_SDC_SetCsAttachAllowFlg(VOS_FALSE);
    }

    if (NAS_MSCC_PIF_SRVDOMAIN_PS == pstDetachCnf->enCnDomainId)
    {
        /* 服务状态上报，统一放到Sta_ServiceStatusInd()处理,attach cnf 和 detach cnf不再做处理 */

        /*增加判断DETACH结果的原因值*/
        if (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == pstDetachCnf->enServiceStatus)
        {
            enPhoneError = TAF_ERR_PHONE_DETACH_FORBIDDEN;
        }

        /*清除PS DETACH标志*/
        pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_PS_DETACH_SET;

        TAF_SDC_SetPsAttachAllowFlg(VOS_FALSE);
    }

    if (NAS_MSCC_PIF_SRVDOMAIN_CS_PS == pstDetachCnf->enCnDomainId)
    {
        /*清除CS DETACH标志*/
        pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_CS_DETACH_SET;

        /*清除PS DETACH标志*/
        pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_PS_DETACH_SET;

        TAF_SDC_SetCsAttachAllowFlg(VOS_FALSE);
        TAF_SDC_SetPsAttachAllowFlg(VOS_FALSE);
    }
    /* Modified by w00167002 for L-C互操作项目, 2014-2-19, begin */

    /* 已经完成DETACH请求的任务 */
    if (TAF_MMA_SYS_CFG_NONE_SET == (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED))
    {
        /* 停止保护定时器 */
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_DETACH_CNF);

        if (TAF_ERR_NO_ERROR != enPhoneError)
        {
            enDetachRslt = TAF_MMA_APP_OPER_RESULT_FAILURE;
            enSysCfgRslt = TAF_MMA_SYS_CFG_RSLT_DETACH_FAIL;
        }

        TAF_MMA_SndDetachCnf(pstCtrl, enDetachRslt, enPhoneError);

        /* 发送状态机退出结果消息 */
        TAF_MMA_SndSysCfgRsltInd(enSysCfgRslt, VOS_FALSE);

        /* 退出状态机 */
        TAF_MMA_FSM_QuitSubFsm();
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcDetachCnfTriggeredBySysCfgReq_SysCfg
 功能描述  : 在TAF_MMA_SYS_CFG_STA_WAIT_DETACH_CNF状态收到ID_MSCC_MMA_DETACH_CNF且入口消息为SYSCFG REQ的处理
 输入参数  : MSCC_MMA_DETACH_CNF_STRU           *pstDetachCnf
             VOS_UINT32                          ulSndAppRsltFlg,
             TAF_MMA_CTRL_STRU                  *pstCtrl
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月10日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ProcDetachCnfTriggeredBySysCfgReq_SysCfg(
    MSCC_MMA_DETACH_CNF_STRU           *pstDetachCnf,
    VOS_UINT32                          ulSndAppRsltFlg,
    TAF_MMA_CTRL_STRU                  *pstCtrl
)
{
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32                    enMsccAttachType;
    TAF_MMA_FSM_SYS_CFG_CTX_STRU                           *pstSysCfgCtx = VOS_NULL_PTR;
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                          enAttachType;
    VOS_UINT8                                               ucOpID;
    VOS_UINT8                                               ucOnlyRoamParaChanged;
    VOS_UINT8                                               ucIsNeedAttachPs;
    TAF_PH_MS_CLASS_TYPE                                    ucClassType;

    ucOnlyRoamParaChanged    = VOS_FALSE;
    ucIsNeedAttachPs         = VOS_FALSE;

    /* 获取当前状态机的上下文 */
    pstSysCfgCtx = &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx);

    /* CS DETACH结果上报 */
    if (NAS_MSCC_PIF_SRVDOMAIN_CS == pstDetachCnf->enCnDomainId)
    {
        TAF_MMA_NotifyCsServiceChange_SysCfg(pstSysCfgCtx->usOperType);

        /*清除CS DETACH标志*/
        pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_CS_DETACH_SET;
    }

    /* PS DETACH结果上报 */
    if (NAS_MSCC_PIF_SRVDOMAIN_PS == pstDetachCnf->enCnDomainId)
    {
        /*清除PS DETACH标志*/
        pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_PS_DETACH_SET;
    }

    if (TAF_MMA_SYS_CFG_NONE_SET != (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED))
    {
        /* 有Detach消息标志时继续等待  */
        return;
    }

    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_DETACH_CNF);

    /* 需要向底层发送SYS CFG请求 */
    if (TAF_MMA_SYS_CFG_NONE_SET != (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_SET_REQ_REQUIRED))
    {
        /* 需要向底层发送SYS CFG请求，后续不需要发送ATTACH的场景，需要发送mode change */
        if (TAF_MMA_SYS_CFG_NONE_SET == (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED))
        {
            MMA_ChangeSrv2Class(pstSysCfgCtx->stSysCfgPara.enSrvDomain, &ucClassType);

            TAF_MMA_SndMsccModeChangeReq((NAS_MSCC_PIF_MS_MODE_ENUM_UINT32)ucClassType);
        }

        ucOnlyRoamParaChanged    = TAF_MMA_IsOnlyRoamParaChangeFlgFromSysCfgOperType_SysCfg(pstSysCfgCtx->usOperType);
        ucIsNeedAttachPs         = TAF_MMA_IsNeedAttachPsFlgFromSysCfgOperType_SysCfg(pstSysCfgCtx->usOperType);
        TAF_MMA_SndMsccSysCfgReq(&(pstSysCfgCtx->stSysCfgPara), ucOnlyRoamParaChanged, ucIsNeedAttachPs);

        /* 启动保护定时器 */
        TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF, TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF_LEN);

        /* 迁到TAF_MMA_SYS_CFG_STA_WAIT_DETACH_CNF状态 */
        TAF_MMA_FSM_SetCurrState(TAF_MMA_SYS_CFG_STA_WAIT_SYS_CFG_CNF);
    }
    /* 不需要向底层发送SYS CFG请求，有ATTACH标志存在 */
    else if (TAF_MMA_SYS_CFG_NONE_SET != (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED))
    {
        MMA_ChangeSrv2Class(pstSysCfgCtx->stSysCfgPara.enSrvDomain, &ucClassType);

        TAF_MMA_SndMsccModeChangeReq((NAS_MSCC_PIF_MS_MODE_ENUM_UINT32)ucClassType);

        enAttachType = TAF_MMA_GetAttachTypeFromSysCfgOperType_SysCfg(pstSysCfgCtx->usOperType);

        if (VOS_OK == TAF_MMA_ConvertAttachTypeToMscc(enAttachType, &enMsccAttachType))
        {
            TAF_MMA_NotifyCsServiceChange_SysCfg(pstSysCfgCtx->usOperType);

            ucOpID = TAF_MMA_GetAttachOpId();

            /* Modified by b00269685 for L-C互操作项目, 2014-2-17, begin */
            (VOS_VOID)TAF_MMA_SndMsccAttachReq(ucOpID, enMsccAttachType, TAF_MMA_ATTACH_REASON_INITIAL);
            /* Modified by b00269685 for L-C互操作项目, 2014-2-17, end */
        }

        if (VOS_TRUE == ulSndAppRsltFlg)
        {
            TAF_MMA_SndSysCfgSetCnf(pstCtrl, TAF_ERR_NO_ERROR);
        }

        /* 发送状态机退出结果消息 */
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_SUCC, VOS_FALSE);

        /* 退出状态机 */
        TAF_MMA_FSM_QuitSubFsm();

    }
    else
    {
        MMA_ChangeSrv2Class(pstSysCfgCtx->stSysCfgPara.enSrvDomain, &ucClassType);

        TAF_MMA_SndMsccModeChangeReq((NAS_MSCC_PIF_MS_MODE_ENUM_UINT32)ucClassType);

        if (VOS_TRUE == ulSndAppRsltFlg)
        {
            TAF_MMA_SndSysCfgSetCnf(pstCtrl, TAF_ERR_NO_ERROR);
        }

        TAF_MMA_NotifyCsServiceChange_SysCfg(pstSysCfgCtx->usOperType);

        /* 发送状态机退出结果消息 */
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_SUCC, VOS_FALSE);

        /* 退出状态机 */
        TAF_MMA_FSM_QuitSubFsm();
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvDetachCnf_SysCfg_WaitDetachCnf
 功能描述  : 在TAF_MMA_SYS_CFG_STA_WAIT_DETACH_CNF状态收到ID_MSCC_MMA_DETACH_CNF的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvDetachCnf_SysCfg_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_DETACH_CNF_STRU           *pstDetachCnf;
    VOS_UINT32                          ulEntryMsgId;
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;
    TAF_MMA_CTRL_STRU                   stCtrl;

    /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg     = TAF_MMA_GetCurrFsmMsgAddr();

    ulEntryMsgId    = TAF_MMA_GetCurrFsmEntryMsgId_SysCfg();

    pstDetachCnf    = (MSCC_MMA_DETACH_CNF_STRU*)pstMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_MMA_CTRL_STRU));

    /* 入口消息为ID_TAF_MMA_DETACH_REQ的处理 */
    if (ID_TAF_MMA_DETACH_REQ == ulEntryMsgId)
    {
        stCtrl = ((TAF_MMA_DETACH_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl;

        TAF_MMA_ProcDetachCnfTriggeredByDetachReq_SysCfg(pstDetachCnf, &stCtrl);
    }
    else if (ID_TAF_MMA_SYS_CFG_SET_REQ == ulEntryMsgId)
    {
        stCtrl = ((TAF_MMA_SYS_CFG_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl;

        /* 需要向APP返回结果 */
        TAF_MMA_ProcDetachCnfTriggeredBySysCfgReq_SysCfg(pstDetachCnf, VOS_TRUE, &stCtrl);
    }
    else if (MMA_MMA_INTER_SYS_CFG_SET_REQ == ulEntryMsgId)
    {
        /* 不需要向APP返回结果 */
        TAF_MMA_ProcDetachCnfTriggeredBySysCfgReq_SysCfg(pstDetachCnf, VOS_FALSE, &stCtrl);
    }
    else
    {
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTiWaitDetachCnfExpired_SysCfg_WaitDetachCnf
 功能描述  : 等待MsccDetachCnf中定时器超时消息的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月13日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitDetachCnfExpired_SysCfg_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulEntryMsgId;
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;
    TAF_MMA_CTRL_STRU                   stCtrl;
    MSCC_MMA_DETACH_CNF_STRU            stDetachCnf;
    TAF_MMA_FSM_SYS_CFG_CTX_STRU       *pstSysCfgCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulSndAppRsltFlg;

    /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg     = TAF_MMA_GetCurrFsmMsgAddr();

    ulEntryMsgId    = TAF_MMA_GetCurrFsmEntryMsgId_SysCfg();

    /* 获取当前状态机的上下文 */
    pstSysCfgCtx    = &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx);

    ulSndAppRsltFlg = VOS_FALSE;

    PS_MEM_SET(&stDetachCnf, 0, sizeof(MSCC_MMA_DETACH_CNF_STRU));

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_MMA_CTRL_STRU));

    if (ID_TAF_MMA_SYS_CFG_SET_REQ == ulEntryMsgId)
    {
        ulSndAppRsltFlg = VOS_TRUE;

        stCtrl = ((TAF_MMA_SYS_CFG_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl;
    }

    if ((ID_TAF_MMA_SYS_CFG_SET_REQ == ulEntryMsgId)
     || (MMA_MMA_INTER_SYS_CFG_SET_REQ == ulEntryMsgId))
    {
        /* 未收到detach cnf消息，认为detach成功，构造假的detach cnf消息 */
        if ((TAF_MMA_SYS_CFG_CS_DETACH_SET == (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_CS_DETACH_SET))
         && (TAF_MMA_SYS_CFG_PS_DETACH_SET == (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_PS_DETACH_SET)))
        {
            stDetachCnf.enCnDomainId    = NAS_MSCC_PIF_SRVDOMAIN_CS;
            stDetachCnf.enServiceStatus = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;

            /* 需要向APP返回结果 */
            TAF_MMA_ProcDetachCnfTriggeredBySysCfgReq_SysCfg(&stDetachCnf, ulSndAppRsltFlg, &stCtrl);

            stDetachCnf.enCnDomainId    = NAS_MSCC_PIF_SRVDOMAIN_PS;
            stDetachCnf.enServiceStatus = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;

            /* 需要向APP返回结果 */
            TAF_MMA_ProcDetachCnfTriggeredBySysCfgReq_SysCfg(&stDetachCnf, ulSndAppRsltFlg, &stCtrl);
        }
        else if(TAF_MMA_SYS_CFG_CS_DETACH_SET == (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_CS_DETACH_SET))
        {
            stDetachCnf.enCnDomainId    = NAS_MSCC_PIF_SRVDOMAIN_CS;
            stDetachCnf.enServiceStatus = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;

            /* 需要向APP返回结果 */
            TAF_MMA_ProcDetachCnfTriggeredBySysCfgReq_SysCfg(&stDetachCnf, ulSndAppRsltFlg, &stCtrl);
        }
        else if (TAF_MMA_SYS_CFG_PS_DETACH_SET == (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_PS_DETACH_SET))
        {
            stDetachCnf.enCnDomainId    = NAS_MSCC_PIF_SRVDOMAIN_PS;
            stDetachCnf.enServiceStatus = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;

            /* 需要向APP返回结果 */
            TAF_MMA_ProcDetachCnfTriggeredBySysCfgReq_SysCfg(&stDetachCnf, ulSndAppRsltFlg, &stCtrl);
        }
        else
        {
        }
    }
    else if (ID_TAF_MMA_DETACH_REQ == ulEntryMsgId)
    {
        /* 直接给APP回复失败 */
        TAF_MMA_SndDetachCnf(&(((TAF_MMA_DETACH_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl),
                             TAF_MMA_APP_OPER_RESULT_FAILURE,
                             TAF_ERR_TIME_OUT);

        /* 发送状态机退出结果消息 */
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_DETACH_FAIL, VOS_FALSE);

        /* 退出状态机 */
        TAF_MMA_FSM_QuitSubFsm();
    }
    else
    {
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvAbortInd_SysCfg_WaitDetachCnf
 功能描述  : 等待MsccDetachCnf中收到内部Abort消息
 输入参数  : ulEventType
            *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月13日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAbortInd_SysCfg_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgId;

    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_DETACH_CNF);

    /* 获取缓存消息 */
    pstEntryMsg                         = TAF_MMA_GetCurrFsmMsgAddr();
    ulMsgId                             = TAF_MMA_GetCurrFsmEntryMsgId_SysCfg();

    /* 根据缓存消息类型上报结果 */
    if (ID_TAF_MMA_SYS_CFG_SET_REQ == ulMsgId)
    {
        TAF_MMA_SndSysCfgSetCnf(&(((TAF_MMA_SYS_CFG_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl),
                                TAF_ERR_ERROR);

        /* 发送状态机退出结果消息 */
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_FAIL, VOS_FALSE);
    }
    else if (ID_TAF_MMA_DETACH_REQ == ulMsgId)
    {
        TAF_MMA_SndDetachCnf(&(((TAF_MMA_DETACH_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl),
                             TAF_MMA_APP_OPER_RESULT_FAILURE,
                             TAF_ERR_ERROR);

        /* 发送状态机退出结果消息 */
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_DETACH_FAIL, VOS_FALSE);
    }
    else
    {
        /* 发送状态机退出结果消息 */
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_BUTT, VOS_FALSE);
    }

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvAttachCnf_SysCfg_WaitAttachCnf
 功能描述  : 在TAF_MMA_SYS_CFG_STA_WAIT_ATTACH_CNF状态收到ID_MSCC_MMA_ATTACH_CNF的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : l00301449
    修改内容   : 新生成函数
  2.日    期   : 2015年4月14日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAttachCnf_SysCfg_WaitAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_ATTACH_CNF_STRU                               *pstAttachCnf    = VOS_NULL_PTR;
    TAF_MMA_FSM_SYS_CFG_CTX_STRU                           *pstSysCfgCtx    = VOS_NULL_PTR;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                     enAttachRslt;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enCsSrvStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enPsSrvStatus;
    VOS_UINT16                                              usPhoneError;

    /* 初始化 */
    pstAttachCnf    = (MSCC_MMA_ATTACH_CNF_STRU *)pstMsg;
    pstSysCfgCtx    = &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx);
    enPsSrvStatus   = TAF_SDC_GetPsServiceStatus();
    enCsSrvStatus   = TAF_SDC_GetCsServiceStatus();
    enAttachRslt    = TAF_MMA_APP_OPER_RESULT_SUCCESS;
    usPhoneError    = TAF_ERR_NO_ERROR;

    /* 检查OpId是否匹配 */
    if (pstSysCfgCtx->ucAttachOpId != (VOS_UINT8)pstAttachCnf->ulOpID)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvAttachCnf_SysCfg_WaitAttachCnf():Wrong OpId!");

        return VOS_TRUE;
    }

    /* 根据Service Domain清除标志并更新服务域状态 */
    switch (pstAttachCnf->enCnDomainId)
    {
        case NAS_MSCC_PIF_SRVDOMAIN_CS:
            /* 清除CS ATTACH标志 */
            pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_CS_ATTACH_SET;

            /* 如还有未收到的消息，继续等待 */
            if (TAF_MMA_SYS_CFG_NONE_SET != (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED))
            {
                return VOS_TRUE;
            }

            /* 获取当前的服务域状态 */
            if (NAS_MSCC_PIF_SERVICE_STATUS_NO_CHANGE != pstAttachCnf->enServiceStatus)
            {
                enCsSrvStatus = (TAF_SDC_SERVICE_STATUS_ENUM_UINT8)pstAttachCnf->enServiceStatus;
            }

            break;

        case NAS_MSCC_PIF_SRVDOMAIN_PS:
            /* 清除PS ATTACH标志 */
            pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_PS_ATTACH_SET;

            /* 如还有未收到的消息，继续等待 */
            if (TAF_MMA_SYS_CFG_NONE_SET != (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED))
            {
                return VOS_TRUE;
            }

            /* 获取当前的服务域状态 */
            if (NAS_MSCC_PIF_SERVICE_STATUS_NO_CHANGE != pstAttachCnf->enServiceStatus)
            {
                enPsSrvStatus = (TAF_SDC_SERVICE_STATUS_ENUM_UINT8)pstAttachCnf->enServiceStatus;
            }

            break;

        case NAS_MSCC_PIF_SRVDOMAIN_CS_PS:
            /* 清除PS_CS ATTACH标志 */
            pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED;

            /* 获取当前的服务域状态 */
            if (NAS_MSCC_PIF_SERVICE_STATUS_NO_CHANGE != pstAttachCnf->enServiceStatus)
            {
                enPsSrvStatus = (TAF_SDC_SERVICE_STATUS_ENUM_UINT8)pstAttachCnf->enServiceStatus;
                enCsSrvStatus = (TAF_SDC_SERVICE_STATUS_ENUM_UINT8)pstAttachCnf->enServiceStatus;
            }

            break;

        default:
            /* 域错误，不处理 */
            return VOS_TRUE;
    }

    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_ATTACH_CNF);

    /* 根据请求的Attach类型,判断Attach结果 */
    TAF_MMA_GetAttachRsltFromServiceStatus_SysCfg(enCsSrvStatus, enPsSrvStatus, &enAttachRslt, &usPhoneError);

    /* 根据消息请求类型上报结果 */
    TAF_MMA_SndAttachCnf(&(((TAF_MMA_ATTACH_REQ_STRU *)(TAF_MMA_GetCurrFsmMsgAddr()->aucEntryMsgBuffer))->stCtrl),
                         enAttachRslt,
                         usPhoneError);

    /* 发送状态机退出结果消息 */
    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == enAttachRslt)
    {
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_ATTACH_SUCCESS, VOS_FALSE);
    }
    else
    {
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_ATTACH_FAIL, VOS_FALSE);
    }

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTiWaitAttachCnfExpired_SysCfg_WaitAttachCnf
 功能描述  : 等待AttachCnf超时消息的处理
 输入参数  : VOS_UINT32 ulEventType
             struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月14日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitAttachCnfExpired_SysCfg_WaitAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 根据缓存消息类型上报结果 */
    TAF_MMA_SndAttachCnf(&(((TAF_MMA_ATTACH_REQ_STRU *)(TAF_MMA_GetCurrFsmMsgAddr()->aucEntryMsgBuffer))->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE,
                          TAF_ERR_TIME_OUT);

    /* 发送状态机退出结果消息 */
    TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_ATTACH_FAIL, VOS_FALSE);

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvAbortInd_SysCfg_WaitAttachCnf
 功能描述  : 等待AttachCnf时收到Abort消息的处理
 输入参数  : VOS_UINT32 ulEventType
             struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月14日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAbortInd_SysCfg_WaitAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_ATTACH_CNF);

    /* 根据缓存消息类型上报结果 */
    TAF_MMA_SndAttachCnf(&(((TAF_MMA_ATTACH_REQ_STRU *)(TAF_MMA_GetCurrFsmMsgAddr()->aucEntryMsgBuffer))->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE,
                          TAF_ERR_ERROR);

    /* 发送状态机退出结果消息 */
    TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_ATTACH_FAIL, VOS_FALSE);

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetRatListBasedOnSysmode_SysCfg
 功能描述  : 根据sysmode来获取rat的列表
 输入参数  : TAF_SDC_SYS_MODE_ENUM_UINT8         enstSysCfgPara
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月12日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_GetRatListBasedOnSysmode_SysCfg(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode,
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
)
{
    switch (enSysMode)
    {
        case TAF_SDC_SYS_MODE_GSM:
            pstRatOrder->ucRatOrderNum  = 1;
            pstRatOrder->aenRatOrder[0] = TAF_MMA_RAT_GSM;
            break;

        case TAF_SDC_SYS_MODE_WCDMA:
            pstRatOrder->ucRatOrderNum  = 1;
            pstRatOrder->aenRatOrder[0] = TAF_MMA_RAT_WCDMA;
            break;

        case TAF_SDC_SYS_MODE_LTE:
            pstRatOrder->ucRatOrderNum  = 1;
            pstRatOrder->aenRatOrder[0] = TAF_MMA_RAT_LTE;
            break;

        case TAF_SDC_SYS_MODE_CDMA_1X:
            pstRatOrder->ucRatOrderNum  = 1;
            pstRatOrder->aenRatOrder[0] = TAF_MMA_RAT_1X;
            break;

        case TAF_SDC_SYS_MODE_EVDO:
            pstRatOrder->ucRatOrderNum  = 1;
            pstRatOrder->aenRatOrder[0] = TAF_MMA_RAT_HRPD;
            break;

        case TAF_SDC_SYS_MODE_HYBRID:
            pstRatOrder->ucRatOrderNum  = 2;
            pstRatOrder->aenRatOrder[0] = TAF_MMA_RAT_1X;
            pstRatOrder->aenRatOrder[1] = TAF_MMA_RAT_HRPD;
            break;

        case TAF_SDC_SYS_MODE_SVLTE:
            pstRatOrder->ucRatOrderNum  = 2;
            pstRatOrder->aenRatOrder[0] = TAF_MMA_RAT_1X;
            pstRatOrder->aenRatOrder[1] = TAF_MMA_RAT_LTE;
            break;

        default :
            pstRatOrder->ucRatOrderNum  = 0;
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsConfigCMode_SysCfg
 功能描述  : 收到SYS CNF成功的处理
 输入参数  : TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月28日
    作    者   : h00313353
    修改内容   : 1X 锁网锁卡

*****************************************************************************/
VOS_UINT8 TAF_MMA_IsConfigCMode_SysCfg(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          i;

    for (i = 0; i < TAF_SDC_MIN(TAF_PH_MAX_GUL_RAT_NUM, pstRatOrder->ucRatOrderNum); i++)
    {
        if ((TAF_MMA_RAT_1X   == pstRatOrder->aenRatOrder[i])
         || (TAF_MMA_RAT_HRPD == pstRatOrder->aenRatOrder[i]))
        {
            TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_IsConfigCMode_SysCfg: TRUE!");

            return VOS_TRUE;
        }
    }
#endif
    TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_IsConfigCMode_SysCfg: FLASE!");

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcSysCfgCnfSucc_SysCfg
 功能描述  : 收到SYS CNF成功的处理
 输入参数  : TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ProcSysCfgCnfSucc_SysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
{
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                    *pstLastSyscfgSet = VOS_NULL_PTR;
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;
    TAF_MMA_RAT_ORDER_STRU                                  stRatOrder;
    VOS_UINT32                                              ulSysModeSupportFlg;
    VOS_UINT8                                               i;

    enSysMode        = TAF_SDC_GetSysMode();
    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();

    TAF_MMA_SndTafSysCfgInfoInd(&(pstLastSyscfgSet->stRatPrioList), &(pstSysCfgPara->stRatOrder));

    if (ID_TAF_MMA_SYS_CFG_SET_REQ == TAF_MMA_GetCurrFsmEntryMsgId_SysCfg())
    {
         /* 更新当前设置成功的接入技术 */
        TAF_MMA_UpdateSysCfgPara(pstSysCfgPara);
    }
    else
    {
        /* 只更新全局变量 */
        pstLastSyscfgSet->stRatPrioList = pstSysCfgPara->stRatOrder;
    }

    PS_MEM_SET(&stRatOrder, 0x00, sizeof(stRatOrder));
    ulSysModeSupportFlg = VOS_FALSE;

    TAF_MMA_GetRatListBasedOnSysmode_SysCfg(enSysMode, &stRatOrder);

    for (i = 0; i < TAF_SDC_MIN(TAF_PH_MAX_GUL_RAT_NUM, stRatOrder.ucRatOrderNum); i++)
    {
        if (VOS_TRUE == MN_MMA_IsSpecRatSupported(stRatOrder.aenRatOrder[i]) )
        {
            ulSysModeSupportFlg = VOS_TRUE;
            break;
        }
    }

    /* 当前的接入技术，是否在新的接入技术列表中, 不在RAT列表中时，上报 Mode:0,0*/
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    if ((VOS_FALSE == ulSysModeSupportFlg)
     && (TAF_SDC_SYS_MODE_BUTT != enSysMode))
    {
        /* CMDA宏打开的情况下，在退状态机的时候，处理SYSMODE */
#if (FEATURE_OFF == FEATURE_UE_MODE_CDMA)
        TAF_SDC_SetSysMode(TAF_SDC_SYS_MODE_BUTT);
        TAF_SDC_SetSysSubMode(TAF_SDC_SYS_SUBMODE_NONE);

        Sta_ModeChangeEventReport(TAF_PH_INFO_NONE_RAT, TAF_SYS_SUBMODE_NONE);
#endif

        /* Added by l00198894 for V9R1 干扰控制, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* 给MTC模块上报当前接入模式 */
        /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
        TAF_MMA_SndMtcRatModeInd(TAF_SDC_SYS_MODE_BUTT, NAS_UTRANCTRL_GetCurrUtranMode());
        /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */
        TAF_MMA_SndMtcRatCfgInd(&(pstSysCfgPara->stRatOrder));
#endif
        /* Added by l00198894 for V9R1 干扰控制, 2013/08/19, end */

    }

}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvSysCfgCnf_SysCfg_WaitSysCfgCnf
 功能描述  : 在TAF_MMA_SYS_CFG_STA_WAIT_SYS_CFG_CNF状态收到ID_MSCC_MMA_SYS_CFG_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : l00301449
    修改内容   : 新生成函数
  2.日    期   : 2015年12月3日
    作    者   : w00176964
    修改内容   : DTS2015061601845:SYSCFG设置失败时,回退相应的操作

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvSysCfgCnf_SysCfg_WaitSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_ERROR_CODE_ENUM_UINT32                              enErrorCode;
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32                    enMsccAttachType;
    MSCC_MMA_SYS_CFG_SET_CNF_STRU                          *pstSysCfgCnf;
    TAF_MMA_FSM_SYS_CFG_CTX_STRU                           *pstSysCfgCtx = VOS_NULL_PTR;
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg    = VOS_NULL_PTR;
    VOS_UINT32                                              ulEntryMsgId;
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                          enAttachType;
    TAF_MMA_CTRL_STRU                                       stCtrl;
    TAF_PH_MS_CLASS_TYPE                                    ucClassType;
    TAF_MMA_SYS_CFG_OPER_TYPE                               usOperType;
    VOS_UINT8                                               ucIsOrigCfgCMode;
    VOS_UINT8                                               ucIsNeedChkLock;        /* 是否需要重新进行锁网锁卡检查标志 */

    ucIsNeedChkLock                                         = VOS_FALSE;
    ucIsOrigCfgCMode                                        = VOS_FALSE;

    /* 获取当前状态机的上下文 */
    pstSysCfgCtx    = &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx);

    /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg      = TAF_MMA_GetCurrFsmMsgAddr();

    ulEntryMsgId     = TAF_MMA_GetCurrFsmEntryMsgId_SysCfg();

    pstSysCfgCnf     = (MSCC_MMA_SYS_CFG_SET_CNF_STRU*)pstMsg;

    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF);

    ucClassType  = TAF_PH_MS_CLASS_NULL;
    enAttachType = TAF_MMA_ATTACH_TYPE_NULL;
    usOperType   = TAF_MMA_SYS_CFG_RAT_NONE_SET;

    /* 需要向底层发送ATTACH请求 */
    if (VOS_TRUE == TAF_MMA_IsNeedAttachAfterSyscfgSet_SysCfg(pstSysCfgCnf->enRst, &enAttachType, &ucClassType, &usOperType))
    {
        TAF_MMA_SndMsccModeChangeReq((NAS_MSCC_PIF_MS_MODE_ENUM_UINT32)ucClassType);

        if (VOS_OK == TAF_MMA_ConvertAttachTypeToMscc(enAttachType, &enMsccAttachType))
        {
            TAF_MMA_NotifyCsServiceChange_SysCfg(usOperType);

            /* Modified by b00269685 for L-C互操作项目, 2014-2-17, begin */
            (VOS_VOID)TAF_MMA_SndMsccAttachReq(TAF_MMA_GetAttachOpId(), enMsccAttachType, TAF_MMA_ATTACH_REASON_INITIAL);
            /* Modified by b00269685 for L-C互操作项目, 2014-2-17, end */
        }
    }

    if (NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS == pstSysCfgCnf->enRst)
    {
        enErrorCode = TAF_ERR_NO_ERROR;

        ucIsOrigCfgCMode = TAF_MMA_IsConfigCMode_SysCfg(&(TAF_MMA_GetLastSyscfgSetAddr()->stRatPrioList));

        if (ucIsOrigCfgCMode != TAF_MMA_IsConfigCMode_SysCfg(&(pstSysCfgCtx->stSysCfgPara.stRatOrder)))
        {
            ucIsNeedChkLock = VOS_TRUE;

            TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvSysCfgCnf_SysCfg_WaitSysCfgCnf: Need Chk Lock!");
        }

        TAF_MMA_ProcSysCfgCnfSucc_SysCfg(&(pstSysCfgCtx->stSysCfgPara));
    }
    else if (NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_CS_SERV_EXIST == pstSysCfgCnf->enRst)
    {
        enErrorCode = TAF_ERR_SYSCFG_CS_SERV_EXIST;

        /* 如果是4F36refresh触发的SYSCFG失败，需要启动TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING定时器 */
        if (MMA_MMA_INTER_SYS_CFG_SET_REQ == ulEntryMsgId)
        {
            TAF_MMA_ProcInterSysCfgCnfFail_SysCfg();
        }
    }
    else
    {
        enErrorCode = TAF_ERR_ERROR;

        /* 如果是4F36refresh触发的SYSCFG失败，需要启动TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING定时器 */
        if (MMA_MMA_INTER_SYS_CFG_SET_REQ == ulEntryMsgId)
        {
            TAF_MMA_ProcInterSysCfgCnfFail_SysCfg();
        }
    }

    if (ID_TAF_MMA_SYS_CFG_SET_REQ == ulEntryMsgId)
    {
        stCtrl = ((TAF_MMA_SYS_CFG_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl;

        /* Modified by w00167002 for L-C互操作项目, 2014-2-14, begin */
        TAF_MMA_SndSysCfgSetCnf(&stCtrl, enErrorCode);
        /* Modified by w00167002 for L-C互操作项目, 2014-2-14, end */
    }

    /* 发送状态机退出结果消息 */
    if (TAF_ERR_NO_ERROR == enErrorCode)
    {
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_SUCC, ucIsNeedChkLock);
    }
    else
    {
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_FAIL, ucIsNeedChkLock);
    }

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTiWaitSysCfgCnfExpired_SysCfg_WaitSysCfgCnf
 功能描述  : 等待SysCfgCnf超时消息的处理
 输入参数  : VOS_UINT32 ulEventType
             struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月14日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitSysCfgCnfExpired_SysCfg_WaitSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgId;

    /* 获取缓存消息 */
    pstEntryMsg                         = TAF_MMA_GetCurrFsmMsgAddr();
    ulMsgId                             = TAF_MMA_GetCurrFsmEntryMsgId_SysCfg();

    /* 根据缓存消息类型上报结果 */
    if (ID_TAF_MMA_SYS_CFG_SET_REQ == ulMsgId)
    {
        TAF_MMA_SndSysCfgSetCnf(&(((TAF_MMA_SYS_CFG_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl),
                                TAF_ERR_TIME_OUT);
    }

    /* 发送状态机退出结果消息 */
    TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_FAIL, VOS_FALSE);

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_RcvAbortInd_SysCfg_WaitSysCfgCnf
 功能描述  : 等待SysCfg时收到Abort消息的处理
 输入参数  : VOS_UINT32 ulEventType
             struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月14日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAbortInd_SysCfg_WaitSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgId;

    /* 获取缓存消息 */
    pstEntryMsg                         = TAF_MMA_GetCurrFsmMsgAddr();
    ulMsgId                             = TAF_MMA_GetCurrFsmEntryMsgId_SysCfg();

    /* 根据缓存消息类型上报结果 */
    if (ID_TAF_MMA_SYS_CFG_SET_REQ == ulMsgId)
    {
        TAF_MMA_SndSysCfgSetCnf(&(((TAF_MMA_SYS_CFG_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl),
                                TAF_ERR_ERROR);
    }

    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF);

    /* 发送状态机退出结果消息 */
    TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_FAIL, VOS_FALSE);

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcInterSysCfgCnfFail_SysCfg_WaitSysCfgCnf
 功能描述  : 内部触发的SYSCFG设置失败的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月9日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ProcInterSysCfgCnfFail_SysCfg(VOS_VOID)
{
    /* TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING定时器正在运行，返回 */
    if (MMA_TIMER_RUN == TAF_MMA_GetTiTryingPeriodRatBalancingStatus())
    {
        return;
    }

    /* 如果是4F36refresh触发的SYSCFG失败，需要启动TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING定时器 */
    TAF_MMA_StartTimer(TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING, TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING_LEN);

    TAF_MMA_SetTiTryingPeriodRatBalancingStatus(MMA_TIMER_RUN);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetOperTypeFromGULToCL
 功能描述  : 获取RAT设置从GUL到CL操作类型
 输入参数  : enLastGULRatType -- 上次GUL RAT类型
             enCurrCLRatType  -- 当前CL RAT类型

 输出参数  : 无
 返 回 值  : TAF_MMA_MODE_CHANGE_OPER_TYPE_STRU -- 操作类型

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU *TAF_MMA_GetOperTypeFromGULToCL(
    TAF_MMA_GUL_RAT_SUBMODE_TYPE_ENUM_UINT8     enLastGULSubmodeType,
    TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM_UINT8      enCurrCLSubmodeType
)
{
    return &(g_astOperTypeFromGULToCLTab[enLastGULSubmodeType][enCurrCLSubmodeType]);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetOperTypeFromCLToGUL
 功能描述  : 获取RAT设置从CL到GUL操作类型
 输入参数  : enLastCLRatType  -- CL RAT类型
             enCurrGULRatType -- GUL RAT类型

 输出参数  : 无
 返 回 值  : TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU -- 操作类型

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU *TAF_MMA_GetOperTypeFromCLToGUL(
    TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM_UINT8      enLastCLSubModeType,
    TAF_MMA_GUL_RAT_SUBMODE_TYPE_ENUM_UINT8     enCurrGULSubModeType
)
{
    return &(g_astOperTypeFromCLToGULTab[enLastCLSubModeType][enCurrGULSubModeType]);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetOperTypeFromCLToCL
 功能描述  : 获取RAT设置从CL到GUL操作类型
 输入参数  : enLastCLRatType -- 上次CL RAT类型
             enCurrCLRatType -- 当前CL RAT类型

 输出参数  : 无
 返 回 值  : TAF_MMA_MODE_CHANGE_OPER_TYPE_STRU -- 操作类型

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU *TAF_MMA_GetOperTypeFromCLToCL(
    TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM_UINT8     enLastCLSubModeType,
    TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM_UINT8     enCurrCLSubModeType
)
{
    return &(g_astOperTypeFromCLtoCLTab[enLastCLSubModeType][enCurrCLSubModeType]);
}

/* 移当前函数到TafMmaComFunc.c文件 */

/*****************************************************************************
 函 数 名  : TAF_MMA_CovertGULRatOrderToGULSubMode
 功能描述  : 转换GUL RAT order到GUL子模式
 输入参数  : pstRatOrder -- RAT顺序

 输出参数  : 无
 返 回 值  : VOS_TRUE  -- RAT发生变化
             VOS_FALSE -- RAT未发生变化
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_GUL_RAT_SUBMODE_TYPE_ENUM_UINT8 TAF_MMA_CovertGULRatOrderToGULSubMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
)
{
    /* 当前RAT个数为最大个数，一定是GUL类型  */
    if (TAF_MMA_THREE_RAT_NUM == pstRatOrder->ucRatOrderNum)
    {
        return TAF_MMA_GUL_RAT_SUBMODE_GUL;
    }

    if (TAF_MMA_TWO_RAT_NUM == pstRatOrder->ucRatOrderNum)
    {
        if (TAF_MMA_RAT_GSM == pstRatOrder->aenRatOrder[0])
        {
            if (TAF_MMA_RAT_WCDMA == pstRatOrder->aenRatOrder[1])
            {
                return TAF_MMA_GUL_RAT_SUBMODE_GU;
            }

            return TAF_MMA_GUL_RAT_SUBMODE_GL;
        }

        if (TAF_MMA_RAT_WCDMA == pstRatOrder->aenRatOrder[0])
        {
            if (TAF_MMA_RAT_GSM == pstRatOrder->aenRatOrder[1])
            {
                return TAF_MMA_GUL_RAT_SUBMODE_GU;
            }

            return TAF_MMA_GUL_RAT_SUBMODE_UL;
        }

        if (TAF_MMA_RAT_GSM == pstRatOrder->aenRatOrder[1])
        {
            return TAF_MMA_GUL_RAT_SUBMODE_GL;
        }

        return TAF_MMA_GUL_RAT_SUBMODE_UL;
    }

    if (TAF_MMA_RAT_GSM == pstRatOrder->aenRatOrder[0])
    {
        return TAF_MMA_GUL_RAT_SUBMODE_G;
    }

    if (TAF_MMA_RAT_WCDMA == pstRatOrder->aenRatOrder[0])
    {
        return TAF_MMA_GUL_RAT_SUBMODE_U;
    }

    return TAF_MMA_GUL_RAT_SUBMODE_L;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_MMA_CovertCLRatOrderToCLSubMode
 功能描述  : 转换CL RAT order到CL子模式
 输入参数  : pstRatOrder -- RAT顺序

 输出参数  : 无
 返 回 值  : VOS_TRUE  -- RAT发生变化
             VOS_FALSE -- RAT未发生变化
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM_UINT8 TAF_MMA_CovertCLRatOrderToCLSubMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
)
{
    /* 当前RAT个数为最大个数，一定是CL类型  */
    if (TAF_MMA_THREE_RAT_NUM == pstRatOrder->ucRatOrderNum)
    {
        return TAF_MMA_CL_RAT_SUBMODE_CL;
    }

    if (TAF_MMA_TWO_RAT_NUM == pstRatOrder->ucRatOrderNum)
    {
        if (TAF_MMA_RAT_1X == pstRatOrder->aenRatOrder[0])
        {
            if (TAF_MMA_RAT_HRPD == pstRatOrder->aenRatOrder[1])
            {
                return TAF_MMA_CL_RAT_SUBMODE_C;
            }

            return TAF_MMA_CL_RAT_SUBMODE_1XL;
        }

        if (TAF_MMA_RAT_HRPD == pstRatOrder->aenRatOrder[0])
        {
            if (TAF_MMA_RAT_1X == pstRatOrder->aenRatOrder[1])
            {
                return TAF_MMA_CL_RAT_SUBMODE_C;
            }

            return TAF_MMA_CL_RAT_SUBMODE_HRPDL;
        }

        if (TAF_MMA_RAT_1X == pstRatOrder->aenRatOrder[1])
        {
            return TAF_MMA_CL_RAT_SUBMODE_1XL;
        }

        return TAF_MMA_CL_RAT_SUBMODE_HRPDL;
    }

    if (TAF_MMA_RAT_1X == pstRatOrder->aenRatOrder[0])
    {
        return TAF_MMA_CL_RAT_SUBMODE_1X;
    }

    if (TAF_MMA_RAT_HRPD == pstRatOrder->aenRatOrder[0])
    {
        return TAF_MMA_CL_RAT_SUBMODE_HRPD;
    }

    return TAF_MMA_CL_RAT_SUBMODE_L;
}
#endif

/* 移当前函数到TafMmaComFunc.c文件 */

/*****************************************************************************
 函 数 名  : TAF_MMA_CovertSrvDomainToSysCfgOperType
 功能描述  : 转服务域到操作类型
 输入参数  : enRatModeChange -- RAT模式

 输出参数  : pstRatOperType -- 返回RAT操作类型
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_CovertSrvDomainToSysCfgOperType(VOS_VOID)
{
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8   enSrvDomain;
    TAF_MMA_SYS_CFG_OPER_TYPE           usSysCfgOperType;
    TAF_MMA_SYS_CFG_PARA_STRU          *pstCurSysCfgPara = VOS_NULL_PTR;

    usSysCfgOperType = TAF_MMA_SYS_CFG_NONE_SET;

    pstCurSysCfgPara = TAF_MMA_GetSysCfgPara_SysCfg();

    if (TAF_MMA_SERVICE_DOMAIN_NOCHANGE == pstCurSysCfgPara->enSrvDomain)
    {
        /* 如果当前用户设置的服务域为no change，使用上次保存的服务域 */
        enSrvDomain = MN_MMA_GetServiceDomain();
    }
    else
    {
        /* 如果当前用户设置的服务域不为no change，使用当前设置的服务域 */
        enSrvDomain = pstCurSysCfgPara->enSrvDomain;
    }

    switch (enSrvDomain)
    {
        case TAF_MMA_SERVICE_DOMAIN_ANY:
        case TAF_MMA_SERVICE_DOMAIN_CS:
            usSysCfgOperType |= TAF_MMA_SYS_CFG_CS_ATTACH_SET;
            break;

        case TAF_MMA_SERVICE_DOMAIN_PS:
            usSysCfgOperType |= TAF_MMA_SYS_CFG_PS_ATTACH_SET;
            break;

        case TAF_MMA_SERVICE_DOMAIN_CS_PS:
            usSysCfgOperType |= TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED;
            break;

        default:
            break;
    }

    return usSysCfgOperType;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_CovertRatOperTypeToSysCfgOperType
 功能描述  : 根据RAT触发的操作类型转换为系统配置操作类型
 输入参数  : enRatModeChange -- RAT模式

 输出参数  : pstRatOperType -- 返回RAT操作类型
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_CovertRatOperTypeToSysCfgOperType(
    TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8    enRatModeChange,
    TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU  *pstRatOperType
)
{
    TAF_MMA_SYS_CFG_OPER_TYPE           usSysCfgOperType;

    usSysCfgOperType = TAF_MMA_SYS_CFG_NONE_SET;

    switch (enRatModeChange)
    {
        case TAF_MMA_RAT_MODE_GUL_TO_CL:
            if (VOS_TRUE == pstRatOperType->ucDetachOperation)
            {
                /* GUL->CL, 强制detach CS/PS */
                usSysCfgOperType |= (TAF_MMA_SYS_CFG_CS_DETACH_SET|TAF_MMA_SYS_CFG_PS_DETACH_SET);
            }

            if (VOS_TRUE == pstRatOperType->ucAttachOperation)
            {
                /* GUL->CL, 根据当前服务域设置attach类型 */
                usSysCfgOperType |= TAF_MMA_CovertSrvDomainToSysCfgOperType();
            }
            break;

        case TAF_MMA_RAT_MODE_CL_TO_GUL:
            if (VOS_TRUE == pstRatOperType->ucDetachOperation)
            {
                /* CL->GUL, detach CS/PS */
                usSysCfgOperType |= (TAF_MMA_SYS_CFG_CS_DETACH_SET|TAF_MMA_SYS_CFG_PS_DETACH_SET);
            }

            if (VOS_TRUE == pstRatOperType->ucAttachOperation)
            {
                /* CL->GUL, 根据当前服务域设置attach类型 */
                usSysCfgOperType |= TAF_MMA_CovertSrvDomainToSysCfgOperType();
            }
            break;

        case TAF_MMA_RAT_MODE_CL_TO_CL:
            if (VOS_TRUE == pstRatOperType->ucDetachOperation)
            {
                /* CL->CL, detach CS/PS */
                usSysCfgOperType |= (TAF_MMA_SYS_CFG_CS_DETACH_SET|TAF_MMA_SYS_CFG_PS_DETACH_SET);
            }

            if (VOS_TRUE == pstRatOperType->ucAttachOperation)
            {
                /* CL->CL, 根据当前服务域设置attach类型 */
                usSysCfgOperType |= TAF_MMA_CovertSrvDomainToSysCfgOperType();
            }
            break;

        case TAF_MMA_RAT_MODE_GUL_TO_GUL:
            /* GUL->GUL场景不进该函数 */
        default:
            break;
    }

    if (VOS_TRUE == pstRatOperType->ucSysCfgOperation)
    {
        usSysCfgOperType |= TAF_MMA_SYS_CFG_MODE_SET;
    }

    return usSysCfgOperType;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetOperTypeTriggerredByRatChanges
 功能描述  : 返回SYSCFG的操作类型
 输入参数  : pstSysCfg  -- 当前系统配置参数
             pstLastRat -- 上次设置的RAT

 输出参数  : penRatType -- 返回RAT类型
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_GetOperTypeTriggerredByRatChanges(
    TAF_MMA_RAT_ORDER_STRU             *pstCurrRat,
    TAF_MMA_RAT_ORDER_STRU             *pstLastRat,
    TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8   *penRatType
)
{
    TAF_MMA_SYS_CFG_OPER_TYPE                               usOperType;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU                      *pstOperType = VOS_NULL_PTR;
    TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM_UINT8                  enCurrRatType;
    TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM_UINT8                  enLastRatType;
#endif

    usOperType = TAF_MMA_SYS_CFG_NONE_SET;

    /* get RAT mode change type */
    *penRatType = TAF_MMA_GetRatModeChangeType(pstCurrRat, pstLastRat);

    /* RAT is unchange, no opertion is required  */
    if (VOS_FALSE == TAF_MMA_IsRatOrderChange(pstCurrRat, pstLastRat))
    {
        return usOperType;
    }

    if (TAF_MMA_RAT_MODE_GUL_TO_GUL == *penRatType)
    {
        /* GUL之间的RAT变化，仅需要发送sys cfg set请求 */
        usOperType |= TAF_MMA_SYS_CFG_MODE_SET;

        return usOperType;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (TAF_MMA_RAT_MODE_GUL_TO_CL == *penRatType)
    {
        /* covert current RAT type */
        enCurrRatType = TAF_MMA_CovertCLRatOrderToCLSubMode(pstCurrRat);

        /* covert last RAT type */
        enLastRatType = TAF_MMA_CovertGULRatOrderToGULSubMode(pstLastRat);


        pstOperType = TAF_MMA_GetOperTypeFromGULToCL(enLastRatType, enCurrRatType);
    }
    else if (TAF_MMA_RAT_MODE_CL_TO_GUL == *penRatType)
    {
        /* covert current RAT type */
        enCurrRatType = TAF_MMA_CovertGULRatOrderToGULSubMode(pstCurrRat);

        /* covert last RAT type */
        enLastRatType = TAF_MMA_CovertCLRatOrderToCLSubMode(pstLastRat);


        pstOperType = TAF_MMA_GetOperTypeFromCLToGUL(enLastRatType, enCurrRatType);
    }
    else
    {
        /* covert current RAT type */
        enCurrRatType = TAF_MMA_CovertCLRatOrderToCLSubMode(pstCurrRat);

        /* covert last RAT type */
        enLastRatType = TAF_MMA_CovertCLRatOrderToCLSubMode(pstLastRat);

        pstOperType = TAF_MMA_GetOperTypeFromCLToCL(enLastRatType, enCurrRatType);
    }

    usOperType = TAF_MMA_CovertRatOperTypeToSysCfgOperType(*penRatType, pstOperType);
#endif
    return usOperType;
}

/*****************************************************************************
 函 数 名  :TAF_MMA_IsUserSettedGuBandChanged_SysCfg
 功能描述  :判断用户设置syscfg的GU频段参数与原设置是否发生了改变
 输入参数  :pstGuBand     - 用户设置的syscfg GU频段
            pstOrigGuBand - 原syscfg 设置的GU频段
 输出参数  :无
 返 回 值  :VOS_TRUE  - 用户设置syscfg的GU频段与原设置发生改变
            VOS_FALSE - 用户设置syscfg的GU频段与原设置未发生改变
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月15日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsUserSettedGuBandChanged_SysCfg(
    TAF_USER_SET_PREF_BAND64            *pstGuBand,
    TAF_MMA_USER_BAND_SET_UN            *pstOrigGuBand

)
{
    TAF_MMA_USER_BAND_SET_UN             uGuBand;

    if ((TAF_PH_BAND_NO_CHANGE != pstGuBand->ulBandLow)
     || (0                     != pstGuBand->ulBandHigh))
    {
        MN_MMA_Convert64BitBandTo32Bit(pstGuBand, &uGuBand.ulPrefBand);
        MN_MMA_ConvertGUFrequencyBand(&uGuBand.ulPrefBand);

        if (uGuBand.ulPrefBand != pstOrigGuBand->ulPrefBand)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  :TAF_MMA_IsUserRoamSettingChange_SysCfg
 功能描述  :判断用户设置syscfg中漫游设置改变
 输入参数  :ucCurrRoam - sys cfg设置的漫游值
            ucLastRoam - 上次用户设置的漫游值
 输出参数  :无
 返 回 值  :VOS_TRUE  - 漫游值改变
            VOS_FALSE - 漫游值未改变
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsUserRoamSettingChange_SysCfg(
    TAF_MMA_ROAM_MODE_ENUM_UINT8        enCurrRoam,
    TAF_MMA_ROAM_MODE_ENUM_UINT8        enLastRoam
)
{
    NAS_NVIM_ROAM_CFG_INFO_STRU         stRoamFeature;

    PS_MEM_SET(&stRoamFeature, 0x00, sizeof(stRoamFeature));

    if (NV_OK != NV_Read(en_NV_Item_Roam_Capa, &stRoamFeature, sizeof(stRoamFeature)))
    {
        MN_ERR_LOG("TAF_MMA_IsUserRoamSettingChange_SysCfg: Read en_NV_Item_Roam_Capa Nvim Error");
        return VOS_FALSE;
    }

    /* 漫游特性NV未激活时，0表示不支持漫游，1表示可以漫游，2表示不改变 */
    if (NAS_MSCC_PIF_ROAM_FEATURE_OFF == stRoamFeature.ucRoamFeatureFlg)
    {
        if ((enLastRoam                                != enCurrRoam)
         && (2 != enCurrRoam))
        {
            return VOS_TRUE;
        }
    }
    else
    {
        /******************************************************************************************************
        漫游特性NV激活时，
        TAF_MMA_ROAM_NATIONAL_ON_INTERNATIONAL_ON,                                    开启国内国际漫游
        TAF_MMA_ROAM_NATIONAL_ON_INTERNATIONAL_OFF,                                   开启国内漫游，关闭国际漫游
        TAF_MMA_ROAM_NATIONAL_OFF_INTERNATIONAL_ON,                                   关闭国内漫游，开启国际漫游
        TAF_MMA_ROAM_NATIONAL_OFF_INTERNATIONAL_OFF,                                  关闭国内国际漫游
        *******************************************************************************************************/
        if ((enLastRoam            != enCurrRoam)
            && (TAF_MMA_ROAM_UNCHANGE != enCurrRoam))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetOperTypeTriggerredBySrvDomain
 功能描述  : 系统配置命令设置处理服务域参数预处理
 输入参数  : enSrvDomain -- 服务域

 输出参数  : penDetachReason -- 如果需要detach操作，返回detach原因
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月21日
    作    者   : luojian id:107747
    修改内容   : 新生成函数
  2.日    期   : 2015年4月9日
    作    者   : h00313353
    修改内容   : SrvDomain宏定义改为枚举
  3.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_GetOperTypeTriggerredBySrvDomain(
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8    enSrvDomain,
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8     *penDetachReason
)
{
    TAF_PH_MS_CLASS_TYPE                ucNewMsClass;
    TAF_PH_MS_CLASS_TYPE                ucCurMsClass;
    MMA_CLASS_CHANGE_INDEX_ENUM         enClassChnageIndex;
    TAF_MMA_SYS_CFG_OPER_TYPE           usSrvDomainSetFlg;

    MMA_ChangeSrv2Class(enSrvDomain, &ucNewMsClass);

    ucCurMsClass = gstMmaValue.stSetMsClass.MsClassType;

    gstMmaValue.stSetMsClass.NewMsClassType = ucNewMsClass;

    /*根据当前手机类型判断需要ATTACH还是DETACH过程*/
    enClassChnageIndex = (MMA_CLASS_CHANGE_INDEX_ENUM)(((ucCurMsClass << 4) & 0xf0)
                                                     | (ucNewMsClass & 0x0f));

    usSrvDomainSetFlg = TAF_MMA_SYS_CFG_NONE_SET;

    switch (enClassChnageIndex)
    {
            /*NULL->A*/
        case MMA_NULL2A:
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_CS_ATTACH_SET;
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_PS_ATTACH_SET;
            break;

            /*CG->A*/
        case MMA_CG2A:

            /*NULL->CC*/
        case MMA_NULL2CC:
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_CS_ATTACH_SET;
            break;

            /*NULL->CG*/
        case MMA_NULL2CG:

            /*CC->A*/
        case MMA_CC2A:
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_PS_ATTACH_SET;
            break;

            /*只有DETACH情况的类型切换*/
            /*CC->NULL*/
        case MMA_CC2NULL:

            /*A->CG*/
        case MMA_A2CG:
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_CS_DETACH_SET;
            break;

            /*CG->NULL*/
        case MMA_CG2NULL:

            /*A->CC*/
        case MMA_A2CC:
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_PS_DETACH_SET;
            break;

            /*A->NULL*/
        case MMA_A2NULL:
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_CS_DETACH_SET;
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_PS_DETACH_SET;
            break;

            /*CG->CC*/
        case MMA_CG2CC:
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_PS_DETACH_SET;
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_CS_ATTACH_SET;
            break;

            /*CC->CG*/
        case MMA_CC2CG:
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_CS_DETACH_SET;
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_PS_ATTACH_SET;
            break;

        default:
            break;
    }

    if (0 != (TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED & usSrvDomainSetFlg))
    {
        *penDetachReason = TAF_MMA_DETACH_CAUSE_SRV_DOMAIN_DETACH;
    }

    return usSrvDomainSetFlg;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsUserSrvDomainSettingChange_SysCfg
 功能描述  : check service domain setting change
 输入参数  : ucCurrSrvDomain -- 当前用户设置的服务域
             ucLastSrvDomain -- 上次用户设置的服务域
 输出参数  : VOS_VOID
 返 回 值  : VOS_TRUE  -- 服务域发生变化
             VOS_FALSE -- 服务域未发生变化
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsUserSrvDomainSettingChange_SysCfg(
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8     ucCurrSrvDomain,
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8     ucLastSrvDomain
)
{
    if (TAF_MMA_SERVICE_DOMAIN_NOCHANGE != ucCurrSrvDomain)
    {
        if (ucCurrSrvDomain != ucLastSrvDomain)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_MMA_NeedDetachAttach_CampOnGUMode
 功能描述  : 是否从当前驻留GU模设置为Lonly或只有L的频段,
              或从当前有L模式，设置为没有L模式
 输入参数  : pstSysCfgPara 当前SYSCFG设置
 输出参数  : 无
 返 回 值  : VOS_TRUE:GU to L Only;VOS_FALSE:非GU to L only
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月15日
    作    者   : l00130025
    修改内容   : DTS2012041002516: SYSCFG触发L和GU模之间模式切换时，
                 需要发起Detach和Attach操作
  2.日    期   : 2012年6月15日
    作    者   : l00130025
    修改内容   : DTS2012061502460:L only 到其他模式，或其他模式到L only需要发起Detach/Attach
  3.日    期   : 2013年4月3日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  4.日    期   : 2014年2月13日
    作    者   : w00167002
    修改内容   : L-C互操作项目:调整SYSCFG的设置查询接口
  5.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
  6.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
/* Modified by w00167002 for L-C互操作项目, 2014-2-13, begin */
VOS_UINT32  TAF_MMA_NeedDetachAttach_CampOnGUMode(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
/* Modified by w00167002 for L-C互操作项目, 2014-2-13, end */
{
    VOS_UINT32                          ulPrefBand;
    VOS_UINT32                          ulNeedAttachDetachFlag;
    VOS_UINT32                          ulNewRatLteExistFlag;
    VOS_UINT32                          ulOldRatLteExistFlag;
    TAF_USER_SET_PREF_BAND64           *pstOldLteBand = VOS_NULL_PTR;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    TAF_SDC_SYS_MODE_ENUM_UINT8         enCurRatType;

    enCurRatType = TAF_SDC_GetSysMode();
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

    ulPrefBand             = 0;
    ulNeedAttachDetachFlag = VOS_FALSE;

    /* 将GU频段 pstSysCfgPara->stGuBand 64位转换为32位的 */
    MN_MMA_Convert64BitBandTo32Bit(&pstSysCfgPara->stGuBand, &ulPrefBand);
    MN_MMA_ConvertGUFrequencyBand(&ulPrefBand);

    /* 获取用户设置的LBand */
    TAF_MMA_ConvertLteFrequencyBand(&pstSysCfgPara->stLBand);

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    if ((TAF_SDC_SYS_MODE_WCDMA == enCurRatType)
     || (TAF_SDC_SYS_MODE_GSM == enCurRatType))
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
    {
        /* 当前驻留GU模，新设置的模式为L only */
        if ((VOS_TRUE == MN_MMA_IsLOnlyMode(&(pstSysCfgPara->stRatOrder)))
         || (0 == ulPrefBand))
        {
            ulNeedAttachDetachFlag = VOS_TRUE;

            return ulNeedAttachDetachFlag;
        }


        /* 当前驻留GU模，模式从支持L到没有L的场景,需要做Detach/Attach */

        pstOldLteBand = TAF_MMA_GetUserSetLteBandAddr();

        if ((VOS_TRUE == MN_MMA_IsSpecRatSupported(TAF_MMA_RAT_LTE))
         && ((0 != pstOldLteBand->ulBandHigh)
         ||  (0 != pstOldLteBand->ulBandLow)))
        {
            ulOldRatLteExistFlag = VOS_TRUE;
        }
        else
        {
            ulOldRatLteExistFlag = VOS_FALSE;
        }

        if ( (VOS_TRUE ==  MN_MMA_IsSpecRatInRatList(TAF_MMA_RAT_LTE, &(pstSysCfgPara->stRatOrder)))
         && ((0 != pstSysCfgPara->stLBand.ulBandHigh)
          || (0 != pstSysCfgPara->stLBand.ulBandLow)))
        {
            ulNewRatLteExistFlag = VOS_TRUE;
        }
        else
        {
            ulNewRatLteExistFlag = VOS_FALSE;
        }

        if ((VOS_TRUE  == ulOldRatLteExistFlag)
         && (VOS_FALSE == ulNewRatLteExistFlag))
        {
            ulNeedAttachDetachFlag = VOS_TRUE;
        }

    }

    return ulNeedAttachDetachFlag;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_NeedDetachAttach_CampOnLMode
 功能描述  : 是否从当前驻留L模设置为GU only或只有GU的频段
 输入参数  : pstSysCfgPara 当前SYSCFG设置
 输出参数  : 无
 返 回 值  : VOS_TRUE: L to GU Only;VOS_FALSE:非L to GU Only
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月15日
    作    者   : l00130025
    修改内容   : DTS2012041002516: SYSCFG触发L和GU模之间模式切换时，
                 需要发起Detach和Attach操作
  2.日    期   : 2012年6月15日
    作    者   : l00130025
    修改内容   : DTS2012061502460:L only 到其他模式，或其他模式到L only需要发起Detach/Attach
  3.日    期   : 2013年4月3日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  4.日    期   : 2014年2月13日
    作    者   : w00167002
    修改内容   : L-C互操作项目:调整SYSCFG的设置查询接口
  5.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
  6.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
/* Modified by w00167002 for L-C互操作项目, 2014-2-13, begin */
VOS_UINT32  TAF_MMA_NeedDetachAttach_CampOnLMode(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
/* Modified by w00167002 for L-C互操作项目, 2014-2-13, end */
{
    VOS_UINT32                          ulDetachAttachFlag;
    VOS_UINT32                          ulOldRatOnlyLteFlag;
    VOS_UINT32                          ulNewRatOnlyLteFlag;
    VOS_UINT32                          ulPrefBand;
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstOldUserSetBand = VOS_NULL_PTR;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    TAF_SDC_SYS_MODE_ENUM_UINT8          enCurRatType;

    enCurRatType  = TAF_SDC_GetSysMode();
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

    ulDetachAttachFlag  = VOS_FALSE;

    /* 将GU频段 pstSysCfgPara->stGuBand 64位转换为32位的 */
    MN_MMA_Convert64BitBandTo32Bit(&pstSysCfgPara->stGuBand, &ulPrefBand);
    MN_MMA_ConvertGUFrequencyBand(&ulPrefBand);

    /* 获取用户设置的LBand */
    TAF_MMA_ConvertLteFrequencyBand(&pstSysCfgPara->stLBand);

    pstOldUserSetBand = TAF_MMA_GetSyscfgUserSetBandAddr();

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    if (TAF_SDC_SYS_MODE_LTE == enCurRatType)
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
    {
        /* 目标模式设置为GU时，需要发起Detach/Attach */
        if ((VOS_FALSE == MN_MMA_IsSpecRatInRatList(TAF_MMA_RAT_LTE, &(pstSysCfgPara->stRatOrder)))
         || ((0 == pstSysCfgPara->stLBand.ulBandHigh)
          && (0 == pstSysCfgPara->stLBand.ulBandLow)))
        {
            ulDetachAttachFlag = VOS_TRUE;

            return ulDetachAttachFlag;
        }


        /* 从Lonly到非L only时，或者从非Lonly到L only时,需要发起Detach/Attach */

        /* 老的设置是否LTE only */
        if ((VOS_TRUE == MN_MMA_IsLOnlyMode(TAF_MMA_GetRatPrioListAddr()))
         || (0 == pstOldUserSetBand->uUserSetGuBand.ulPrefBand))
        {
            ulOldRatOnlyLteFlag = VOS_TRUE;
        }
        else
        {
            ulOldRatOnlyLteFlag = VOS_FALSE;
        }

        /* 新的设置是否LTE only */
        if ((VOS_TRUE == MN_MMA_IsLOnlyMode(&(pstSysCfgPara->stRatOrder)))
         || (0 == ulPrefBand))
        {
            ulNewRatOnlyLteFlag = VOS_TRUE;
        }
        else
        {
            ulNewRatOnlyLteFlag = VOS_FALSE;
        }

        if (ulOldRatOnlyLteFlag != ulNewRatOnlyLteFlag)
        {
            ulDetachAttachFlag = VOS_TRUE;
        }


    }

    return ulDetachAttachFlag;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateRatTrigedAttachPara
 功能描述  : 根据RAT变化,更新服务域的Attach类型和SetFlag
 输入参数  : ucNewMsClassType,新设置的Ms类型
 输出参数  : pusSetFlg     当前SYSCFG设置触发的设置标志
             pucAttachType 当前SYSCFG设置触发的Attach类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月15日
    作    者   : l00130025
    修改内容   : DTS2012041002516: SYSCFG触发L和GU模之间模式切换时，
                 需要发起Detach和Attach操作
  2.日    期   : 2014年3月25日
    作    者   : s00217060
    修改内容   : DTS2014032101534:at^cgcatt=0,1,再设SYSCFG由LUG变为UG时，不需要attach ps
  3.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_UpdateRatTrigedAttachPara(
    TAF_PH_MS_CLASS_TYPE                ucNewMsClassType
)
{
    /* Attach操作与当前的服务域类型相同:
     PS Only时,触发PS attach,CS_PS时,触发 CS_PS Attach,CS only触发CS Attach */
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucPsAttachAllow;
    VOS_UINT8                           ucSndPsAttach;
    VOS_UINT8                           ucSndCsAttach;
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType;

    usOperType = TAF_MMA_SYS_CFG_NONE_SET;

    ucSndPsAttach       = VOS_TRUE;
    ucSndCsAttach       = VOS_TRUE;
    ucCsAttachAllow     = TAF_SDC_GetCsAttachAllowFlg();
    ucPsAttachAllow     = TAF_SDC_GetPsAttachAllowFlg();

    /* 如果本次syscfg需要PS attach, 当前的手机模式肯定是支持PS域的
       1.如果syscfg之前的手机模式是支持PS域的，并且ps不允许注册，那么可能是at^cgcatt=0,1导致的ps detach,不需要给MSCC发attach req
       2.如果syscfg之前的手机模式是支持PS域的，并且PS允许注册，需要给MSCC发attach req
       3.如果syscfg之前的手机模式是不支持PS域的，现在设置为支持，需要给MSCC发attach req */
    /* CS域处理相同 */

    /* 之前的模式支持PS域，但PS不允许注册，不需要发ps attach */
    if ( (VOS_TRUE  == TAF_MMA_IsPsServDomainAvail(gstMmaValue.stSetMsClass.MsClassType))
      && (VOS_FALSE == ucPsAttachAllow) )
    {
        ucSndPsAttach   = VOS_FALSE;
    }

    /* 之前的模式支持CS域，但CS不允许注册，不需要发cs attach */
    if ( (VOS_TRUE  == TAF_MMA_IsCsServDomainAvail(gstMmaValue.stSetMsClass.MsClassType))
      && (VOS_FALSE == ucCsAttachAllow) )
    {
        ucSndCsAttach   = VOS_FALSE;
    }

    if (TAF_PH_MS_CLASS_A == ucNewMsClassType)
    {
        /* 如果CS、PS都不需要attach,直接返回 */
        if ( (VOS_FALSE == ucSndCsAttach)
          && (VOS_FALSE == ucSndPsAttach) )
        {
            return usOperType;
        }

        /* CS、PS域中只有一个需要attach时，修改相应的pusSetFlg和pucAttachType */
        if (ucSndCsAttach != ucSndPsAttach)
        {
            if (VOS_TRUE == ucSndCsAttach)
            {
                usOperType |= TAF_MMA_SYS_CFG_CS_ATTACH_SET;
            }
            else
            {
                usOperType |= TAF_MMA_SYS_CFG_PS_ATTACH_SET;
            }
        }
        else
        {
            /* 两个域都需要attach */
            usOperType |= TAF_MMA_SYS_CFG_CS_ATTACH_SET;
            usOperType |= TAF_MMA_SYS_CFG_PS_ATTACH_SET;
        }
    }
    else if (TAF_PH_MS_CLASS_CG == ucNewMsClassType)
    {
        /* 不需要ps attach时不设标志 */
        if (VOS_FALSE == ucSndPsAttach)
        {
            return usOperType;
        }

        usOperType |= TAF_MMA_SYS_CFG_PS_ATTACH_SET;
    }
    else
    {
        /* 不需要cs attach时不设标志 */
        if (VOS_FALSE == ucSndCsAttach)
        {
            return usOperType;
        }

        usOperType |= TAF_MMA_SYS_CFG_CS_ATTACH_SET;
    }

    return usOperType;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateRatTrigedSrvDomianPara
 功能描述  : 根据RAT变化,更新服务域的Detach,Attach类型和SetFlag
 输入参数  : pstSysCfgPara 当前SYSCFG设置
 输出参数  : 无
 返 回 值  : TAF_MMA_SYS_CFG_OPER_TYPE --返回操作类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月15日
    作    者   : l00130025
    修改内容   : DTS2012041002516: SYSCFG触发L和GU模之间模式切换时，
                 需要发起Detach和Attach操作
  2.日    期   : 2012年6月15日
    作    者   : l00130025
    修改内容   : DTS2012061502460:L only 到其他模式，或其他模式到L only需要发起Detach/Attach
  3.日    期   : 2014年2月13日
    作    者   : w00167002
    修改内容   : L-C互操作项目:调整SYSCFG的设置查询接口
  4.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
/* Modified by w00167002 for L-C互操作项目, 2014-2-13, begin */
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_UpdateRatTrigedSrvDomianPara(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
/* Modified by w00167002 for L-C互操作项目, 2014-2-13, end */
{
    TAF_MMA_SYS_CFG_OPER_TYPE          usOperType;

    usOperType = TAF_MMA_SYS_CFG_NONE_SET;


    /* 1)  当前驻留在GU模，设置为L模Only或只有L的频段时，
        根据当前的SrvDomain触发Detach操作
        (CS Only，PS Only或CS_PS时,都触发PS Detach)*/
    if (VOS_TRUE == TAF_MMA_NeedDetachAttach_CampOnGUMode(pstSysCfgPara))
    {
        usOperType |= TAF_MMA_SYS_CFG_PS_DETACH_SET;
    }

    /* 2)  当前驻留在L模，设置为GU模或频段只有GU的频段时，
        根据当前的SrvDomain触发Detach操作
        (PS Only触发PS Detach ,CS_PS时,触发CS_PS Detach) */
    if (VOS_TRUE == TAF_MMA_NeedDetachAttach_CampOnLMode(pstSysCfgPara))
    {
        if (TAF_PH_MS_CLASS_A == gstMmaValue.stSetMsClass.MsClassType)
        {
            usOperType |= TAF_MMA_SYS_CFG_PS_DETACH_SET;
            usOperType |= TAF_MMA_SYS_CFG_CS_DETACH_SET;
        }
        else
        {
            usOperType |= TAF_MMA_SYS_CFG_PS_DETACH_SET;
        }

    }

    /* RAT变化不触发Detach时也不会触发Attach，直接返回 */
    if (TAF_MMA_SYS_CFG_NONE_SET == usOperType)
    {
        return usOperType;
    }

    /* 更新当前的Attach设置变量 */
    usOperType |= TAF_MMA_UpdateRatTrigedAttachPara(gstMmaValue.stSetMsClass.NewMsClassType);

    return usOperType;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_GetSysCfgOperType
 功能描述  : 返回SYSCFG的操作类型
 输入参数  : TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg
 输出参数  : TAF_MMA_SYS_CFG_OPER_TYPE          *pusOperType,
             TAF_MMA_DETACH_CAUSE_ENUM_UINT8    *penDetachReason
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月8日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_GetSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg,
    TAF_MMA_SYS_CFG_OPER_TYPE          *pusOperType,
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8    *penDetachReason
)
{
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                    *pstLastSyscfgSet = VOS_NULL_PTR;
    TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8                        enRatChangeType;

    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();

    enRatChangeType  = TAF_MMA_RAT_MODE_BUTT;

    /* 1. 获取由RAT触发的操作类型 */
    *pusOperType |= TAF_MMA_GetOperTypeTriggerredByRatChanges(&(pstSysCfg->stRatOrder),
                                                              &(pstLastSyscfgSet->stRatPrioList),
                                                              &enRatChangeType);

    switch (enRatChangeType)
    {
        case TAF_MMA_RAT_MODE_GUL_TO_GUL:
        case TAF_MMA_RAT_MODE_CL_TO_GUL:
            {
                /* GU频段参数发生了改变 */
                if (VOS_TRUE == TAF_MMA_IsUserSettedGuBandChanged_SysCfg(&pstSysCfg->stGuBand,
                                                                         &pstLastSyscfgSet->stUserSetBand.uUserSetGuBand))
                {
                    *pusOperType |= TAF_MMA_SYS_CFG_BAND_SET;
                }

                /* GU漫游指示发生了改变 */
                if (VOS_TRUE == TAF_MMA_IsUserRoamSettingChange_SysCfg(pstSysCfg->enRoam,
                                                                       pstLastSyscfgSet->enRoam))
                {
                    *pusOperType |= TAF_MMA_SYS_CFG_ROAM_SET;
                }

                /* 服务域发生了改变 */
                if (VOS_TRUE == TAF_MMA_IsUserSrvDomainSettingChange_SysCfg(pstSysCfg->enSrvDomain,
                                                                            pstLastSyscfgSet->enSrvDomain))
                {
                    *pusOperType  |= TAF_MMA_GetOperTypeTriggerredBySrvDomain(pstSysCfg->enSrvDomain,
                                                                              penDetachReason);
                }

#if (FEATURE_ON == FEATURE_LTE)
                if (TAF_MMA_RAT_MODE_GUL_TO_GUL == enRatChangeType)
                {
                    /* RAT和Band有变化时，更新 */
                    if ((0 != (*pusOperType & TAF_MMA_SYS_CFG_MODE_SET))
                     || (0 != (*pusOperType & TAF_MMA_SYS_CFG_BAND_SET)))
                    {
                        *pusOperType |= TAF_MMA_UpdateRatTrigedSrvDomianPara(pstSysCfg);
                    }
                }
#endif
            }
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case TAF_MMA_RAT_MODE_CL_TO_CL:
            {
                if (VOS_TRUE == TAF_MMA_IsLteExistInBothCurSysCfgAndOldSysCfg(pstSysCfg, pstLastSyscfgSet))
                {
                    /* 服务域发生了改变 */
                    if (VOS_TRUE == TAF_MMA_IsUserSrvDomainSettingChange_SysCfg(pstSysCfg->enSrvDomain,
                                                                                pstLastSyscfgSet->enSrvDomain))
                    {
                        *pusOperType  |= TAF_MMA_GetOperTypeTriggerredBySrvDomain(pstSysCfg->enSrvDomain,
                                                                                  penDetachReason);
                    }
                }
            }
            break;
#endif

        default:
            break;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* L频段参数发生改变 */
    if (VOS_TRUE == TAF_MMA_IsUserSettedLBandChanged(&pstSysCfg->stLBand,
                                                     &pstLastSyscfgSet->stUserSetBand.stUserSetLteBand))
    {
        *pusOperType |= TAF_MMA_SYS_CFG_BAND_SET;
    }
#endif

    /* 如果服务域没有触发detach操作，如果当前有detach操作，都认为是sys cfg触发的detach */
    if ((TAF_MMA_DETACH_CAUSE_SRV_DOMAIN_DETACH != *penDetachReason)
     && (0                                      != (*pusOperType & TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED)))
    {
        *penDetachReason = TAF_MMA_DETACH_CAUSE_RAT_OR_BAND_DETACH;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdatePrioAccessMode
 功能描述  : 更新接入优先级
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月11日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID TAF_MMA_UpdatePrioAccessMode(
    TAF_MMA_SYS_CFG_PARA_STRU                              *pstCurrSysCfg,
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                    *pstLastSysCfg
)
{
    VOS_UINT32                          ucWriteAccessPrio;
    VOS_UINT16                          i;

    /* 不支持L模时需要写入 */
    ucWriteAccessPrio = VOS_TRUE;

    for ( i = 0 ; i < pstLastSysCfg->stRatPrioList.ucRatOrderNum; i++ )
    {
        if ( TAF_MMA_RAT_LTE == pstLastSysCfg->stRatPrioList.aenRatOrder[i])
        {
            ucWriteAccessPrio = VOS_FALSE;
        }
    }

    if ( (VOS_TRUE                       == ucWriteAccessPrio)
      && (pstCurrSysCfg->enUserPrio      != pstLastSysCfg->enPrioRat)
      && (TAF_MMA_USER_SET_PRIO_NOCHANGE != pstCurrSysCfg->enUserPrio))
    {
        pstLastSysCfg->enPrioRat = pstCurrSysCfg->enUserPrio;

        TAF_MMA_WritePrioAccessModeToNvim();
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetDetachOperType_SysCfg
 功能描述  : 获取Detach操作类型
 输入参数  : enDetachDomain -- detach域

 输出参数  : VOS_UINT16                                             *pusOperType,
             NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32                   *penDetachType

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月13日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_GetDetachOperType_SysCfg(
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8                       enDetachDomain
)
{
    switch (enDetachDomain)
    {
        case TAF_MMA_SERVICE_DOMAIN_CS:
            return TAF_MMA_SYS_CFG_CS_DETACH_SET;

        case TAF_MMA_SERVICE_DOMAIN_PS:
            return TAF_MMA_SYS_CFG_PS_DETACH_SET;

        /* 预处理中已经对参数有效性检查 */
        case TAF_MMA_SERVICE_DOMAIN_CS_PS:
        default:
            return (TAF_MMA_SYS_CFG_PS_DETACH_SET | TAF_MMA_SYS_CFG_CS_DETACH_SET);
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetAttachOperType_SysCfg
 功能描述  : 根据服务域返回attach类型和操作类型
 输入参数  : TAF_MMA_ATTACH_TYPE_ENUM_UINT8                          enAttachType,
 输出参数  : TAF_MMA_SYS_CFG_OPER_TYPE                              *pusOperType
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : l301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_GetAttachOperType_SysCfg(
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                          enAttachType,
    TAF_MMA_SYS_CFG_OPER_TYPE                              *pusOperType
)
{
    switch (enAttachType)
    {
        case TAF_MMA_ATTACH_TYPE_IMSI:
            *pusOperType               |= TAF_MMA_SYS_CFG_CS_ATTACH_SET;
            break;

        case TAF_MMA_ATTACH_TYPE_GPRS:
            *pusOperType               |= TAF_MMA_SYS_CFG_PS_ATTACH_SET;
            break;

        /* 预处理中已经对参数有效性检查 */
        case TAF_MMA_ATTACH_TYPE_GPRS_IMSI:
        default:
            *pusOperType               |= (TAF_MMA_SYS_CFG_PS_ATTACH_SET | TAF_MMA_SYS_CFG_CS_ATTACH_SET);
            break;

    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_WriteAccessModeToNvim
 功能描述  : 将AccessMode写入NVIM
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年05月20日
    作    者   : m00217266
    修改内容   : nv项拆分

*****************************************************************************/
VOS_VOID TAF_MMA_WritePrioAccessModeToNvim(VOS_VOID)
{
    NAS_MMA_NVIM_ACCESS_MODE_STRU                            stAccessMode;
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                     *pstLastSyscfgSet    = VOS_NULL_PTR;
    VOS_UINT32                                               ulLength;

    pstLastSyscfgSet     = TAF_MMA_GetLastSyscfgSetAddr();
    ulLength             = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_MMA_AccessMode, &ulLength);
    if (ulLength > sizeof(NAS_MMA_NVIM_ACCESS_MODE_STRU))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_MMA_AccessMode ,
                         &stAccessMode,
                         ulLength))

    {
        MN_WARN_LOG("TAF_MMA_WritePrioAccessModeToNvim:Read:NV_Read runs failed");
        return ;
    }

    stAccessMode.aucAccessMode[1] = pstLastSyscfgSet->enPrioRat;
    if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_MMA_AccessMode,
                                           &stAccessMode,
                                           (VOS_UINT16)ulLength))
    {
        MN_ERR_LOG("TAF_MMA_WritePrioAccessModeToNvim():WARNING:NVIM_Write en_NV_Item_MMA_AccessMode failed");
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetAttachRsltFromServiceStatus_SysCfg
 功能描述  : 根据AttachType和服务域状态判断attach结果
 输入参数  : enCsSrvStatus:Cs域状态
             enPsSrvStatus:Ps域状态
 输出参数  : *penAttachRslt:Attach结果
             *pusPhoneError:错误类型
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_GetAttachRsltFromServiceStatus_SysCfg(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enCsSrvStatus,
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enPsSrvStatus,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                    *penAttachRslt,
    VOS_UINT16                                             *pusPhoneError
)
{
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8      enAttachType;

    /* 获取缓存的请求消息中的AttachType */
    enAttachType = ((TAF_MMA_ATTACH_REQ_STRU *)(TAF_MMA_GetCurrFsmMsgAddr()->aucEntryMsgBuffer))->enAttachType;

    switch(enAttachType)
    {
        case TAF_MMA_ATTACH_TYPE_GPRS:
            if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enPsSrvStatus)
            {
                *penAttachRslt  = TAF_MMA_APP_OPER_RESULT_FAILURE;
                *pusPhoneError  = TAF_ERR_PHONE_ATTACH_FORBIDDEN;
            }
            break;

        case TAF_MMA_ATTACH_TYPE_IMSI:
            if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enCsSrvStatus)
            {
                *penAttachRslt  = TAF_MMA_APP_OPER_RESULT_FAILURE;
                *pusPhoneError  = TAF_ERR_PHONE_ATTACH_FORBIDDEN;
            }
            break;

        case TAF_MMA_ATTACH_TYPE_GPRS_IMSI:
            /* 增加判断CS+PS ATTACH结果的原因值：只有两个域都不能正常服务时，才给AT上报ERROR */
            if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enPsSrvStatus)
             && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enCsSrvStatus))
            {
                *penAttachRslt  = TAF_MMA_APP_OPER_RESULT_FAILURE;
                *pusPhoneError  = TAF_ERR_PHONE_ATTACH_FORBIDDEN;
            }
            break;

        default:
            /* AttachType错误 */
            TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_GetAttachRsltFromServiceStatus_SysCfg():Wrong AttachType!");
            *penAttachRslt  = TAF_MMA_APP_OPER_RESULT_FAILURE;
            *pusPhoneError  = TAF_ERR_PHONE_ATTACH_FORBIDDEN;
            break;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcSysCfgOper_SysCfg
 功能描述  : 根据操作类型执行操作并返回结果
 输入参数  : TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg
             TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
             TAF_MMA_DETACH_CAUSE_ENUM_UINT8     enDetachReason
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月10日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ProcSysCfgOper_SysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg,
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType,
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8     enDetachReason
)
{
    VOS_UINT32                                              ulNeedSendMsccSysCfgFlag;
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                          enAttachType;
    TAF_MMA_DETACH_TYPE_ENUM_UINT8                          enDetachType;
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32                    enMsccAttachType;
    NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32                    enMsccDetachType;
    VOS_UINT8                                               ucOnlyRoamParaChanged;
    VOS_UINT8                                               ucIsNeedAttachPs;
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg = VOS_NULL_PTR;
    VOS_UINT8                                               ucClassType;

    ucOnlyRoamParaChanged    = VOS_FALSE;
    ucIsNeedAttachPs         = VOS_FALSE;

    ulNeedSendMsccSysCfgFlag = VOS_FALSE;

    enMsccAttachType         = NAS_MSCC_PIF_ATTACH_TYPE_BUTT;
    enMsccDetachType         = NAS_MSCC_PIF_DETACH_TYPE_BUTT;

    enDetachType             = TAF_MMA_GetDetachTypeFromSysCfgOperType_SysCfg(usOperType);
    enAttachType             = TAF_MMA_GetAttachTypeFromSysCfgOperType_SysCfg(usOperType);

    pstEntryMsg              = TAF_MMA_GetCurrFsmMsgAddr();

    /* 漫游设置,接入模式设置,频带设置参数有发生改变，需要向底层发送SYSCFG请求 */
    if (TAF_MMA_SYS_CFG_NONE_SET != (usOperType & TAF_MMA_SYS_CFG_SET_REQ_REQUIRED))
    {
        ulNeedSendMsccSysCfgFlag = VOS_TRUE;
    }

    /* 如果需要DETACH，先进行DETACH */
    if (TAF_MMA_SYS_CFG_NONE_SET != (usOperType & TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED))
    {
        if (VOS_OK == TAF_MMA_ConvertDetachTypeToMscc(enDetachType, &enMsccDetachType))
        {
            /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
            (VOS_VOID)TAF_MMA_SndMsccDetachReq(STA_OPID_INSIDE, enMsccDetachType, enDetachReason);
            /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

            /* 启动保护定时器 */
            TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_DETACH_CNF, TI_TAF_MMA_WAIT_MSCC_SYSCFG_DETACH_CNF_LEN);

            /* 迁到TAF_MMA_SYS_CFG_STA_WAIT_DETACH_CNF状态 */
            TAF_MMA_FSM_SetCurrState(TAF_MMA_SYS_CFG_STA_WAIT_DETACH_CNF);
        }
    }
    /* 如果不需要DETACH */
    else if (TAF_MMA_SYS_CFG_NONE_SET != (usOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED))
    {
        /* 如果需要和MSCC进行交互设置syscfg参数,attach放在设置结束后再做 */
        if ((VOS_OK == TAF_MMA_ConvertAttachTypeToMscc(enAttachType, &enMsccAttachType))
         && (VOS_FALSE == ulNeedSendMsccSysCfgFlag))
        {
            TAF_MMA_NotifyCsServiceChange_SysCfg(usOperType);

            /*ATTACH消息需要先发送MODE CHANGE消息*/
            MMA_ChangeSrv2Class(pstSysCfg->enSrvDomain, &ucClassType);
            TAF_MMA_SndMsccModeChangeReq((NAS_MSCC_PIF_MS_MODE_ENUM_UINT32)ucClassType);

            /* Modified by b00269685 for L-C互操作项目, 2014-2-17, begin */
            (VOS_VOID)TAF_MMA_SndMsccAttachReq(TAF_MMA_GetAttachOpId(), enMsccAttachType, TAF_MMA_ATTACH_REASON_INITIAL);
            /* Modified by b00269685 for L-C互操作项目, 2014-2-17, end */
        }
    }
    else
    {
    }

    /* 需要通知MSCC SYSCFG参数 */
    if (VOS_TRUE == ulNeedSendMsccSysCfgFlag)
    {
        /* 没有DETACH则直接通知，否则等待DETACH结果 */
        if (TAF_MMA_DETACH_TYPE_NULL == enDetachType)
        {
            ucOnlyRoamParaChanged    = TAF_MMA_IsOnlyRoamParaChangeFlgFromSysCfgOperType_SysCfg(usOperType);
            ucIsNeedAttachPs         = TAF_MMA_IsNeedAttachPsFlgFromSysCfgOperType_SysCfg(usOperType);
            TAF_MMA_SndMsccSysCfgReq(pstSysCfg, ucOnlyRoamParaChanged, ucIsNeedAttachPs);

            /* 启动保护定时器 */
            TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF, TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF_LEN);

            /* 迁到TAF_MMA_SYS_CFG_STA_WAIT_SYS_CFG_CNF状态 */
            TAF_MMA_FSM_SetCurrState(TAF_MMA_SYS_CFG_STA_WAIT_SYS_CFG_CNF);
        }
    }
    /* 不需要通知MSCC SYSCFG参数 */
    else
    {
        if (ID_TAF_MMA_SYS_CFG_SET_REQ == TAF_MMA_GetCurrFsmEntryMsgId_SysCfg())
        {
            /* 更新NV */
            TAF_MMA_UpdateSysCfgPara(pstSysCfg);
        }

        /* 不需要DETACH */
        if (TAF_MMA_DETACH_TYPE_NULL == enDetachType)
        {
            if (ID_TAF_MMA_SYS_CFG_SET_REQ == TAF_MMA_GetCurrFsmEntryMsgId_SysCfg())
            {
                TAF_MMA_SndSysCfgSetCnf(&(((TAF_MMA_DETACH_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl),
                                        TAF_ERR_NO_ERROR);
            }

            /* 发送状态机退出结果消息 */
            TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_SUCC, VOS_FALSE);

            /* 退出状态机 */
            TAF_MMA_FSM_QuitSubFsm();
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetCurrFsmEntryMsgId_SysCfg
 功能描述  : 获取SYSCFG状态机的入口消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月10日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetCurrFsmEntryMsgId_SysCfg(VOS_VOID)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgId;

    /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg     = TAF_MMA_GetCurrFsmMsgAddr();

    ulMsgId         = TAF_MMA_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType);

    return ulMsgId;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetCsStateFromSyscfgOperType_SysCfg
 功能描述  : 根据SYSCFG操作类型返回CS域状态
 输入参数  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 输出参数  : 无
 返 回 值  : TAF_CS_SERVICE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月11日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
TAF_CS_SERVICE_ENUM_UINT32  TAF_MMA_GetCsStateFromSyscfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    /* 不支持SVLTE，不需要通知MSG和STK,认为无变化 */
    if (VOS_FALSE == TAF_SDC_GetSvlteSupportFlag())
    {
        return TAF_CS_SERVICE_BUTT;
    }

    /* syscfg设置标志新的CS域能力不可用 */
    if (TAF_MMA_SYS_CFG_CS_DETACH_SET
        == (usOperType & TAF_MMA_SYS_CFG_CS_DETACH_SET))
    {
        return TAF_CS_OFF;
    }

    /* syscfg设置标志新的CS域能力可用 */
    if (TAF_MMA_SYS_CFG_CS_ATTACH_SET
        == (usOperType & TAF_MMA_SYS_CFG_CS_ATTACH_SET))
    {
        return TAF_CS_ON;
    }

    /* 其他情况默认不需要发送 */
    return TAF_CS_SERVICE_BUTT;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetDetachTypeFromSysCfgOperType_SysCfg
 功能描述  : 根据操作类型返回detach的类型
 输入参数  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 输出参数  : 无
 返 回 值  : TAF_MMA_DETACH_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月10日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_DETACH_TYPE_ENUM_UINT8 TAF_MMA_GetDetachTypeFromSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    if((TAF_MMA_SYS_CFG_CS_DETACH_SET == (usOperType & TAF_MMA_SYS_CFG_CS_DETACH_SET))
    && (TAF_MMA_SYS_CFG_PS_DETACH_SET == (usOperType & TAF_MMA_SYS_CFG_PS_DETACH_SET)))
    {
        return TAF_MMA_DETACH_TYPE_GPRS_IMSI;
    }
    else if(TAF_MMA_SYS_CFG_CS_DETACH_SET == (usOperType & TAF_MMA_SYS_CFG_CS_DETACH_SET))
    {
        return TAF_MMA_DETACH_TYPE_IMSI;
    }
    else if(TAF_MMA_SYS_CFG_PS_DETACH_SET == (usOperType & TAF_MMA_SYS_CFG_PS_DETACH_SET))
    {
        return TAF_MMA_DETACH_TYPE_GPRS;
    }
    else
    {
        return TAF_MMA_DETACH_TYPE_NULL;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetAttachTypeFromSysCfgOperType_SysCfg
 功能描述  : 根据操作类型返回attach的类型
 输入参数  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 输出参数  : 无
 返 回 值  : TAF_MMA_ATTACH_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月10日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_ATTACH_TYPE_ENUM_UINT8 TAF_MMA_GetAttachTypeFromSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    if((TAF_MMA_SYS_CFG_CS_ATTACH_SET == (usOperType & TAF_MMA_SYS_CFG_CS_ATTACH_SET))
    && (TAF_MMA_SYS_CFG_PS_ATTACH_SET == (usOperType & TAF_MMA_SYS_CFG_PS_ATTACH_SET)))
    {
        return TAF_MMA_ATTACH_TYPE_GPRS_IMSI;
    }
    else if(TAF_MMA_SYS_CFG_CS_ATTACH_SET == (usOperType & TAF_MMA_SYS_CFG_CS_ATTACH_SET))
    {
        return TAF_MMA_ATTACH_TYPE_IMSI;
    }
    else if(TAF_MMA_SYS_CFG_PS_ATTACH_SET == (usOperType & TAF_MMA_SYS_CFG_PS_ATTACH_SET))
    {
        return TAF_MMA_ATTACH_TYPE_GPRS;
    }
    else
    {
        return TAF_MMA_ATTACH_TYPE_NULL;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsOnlyRoamParaChangeFlgFromSysCfgOperType_SysCfg
 功能描述  : 根据操作类型获取是否只有漫游参数改变标志
 输入参数  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月16日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_IsOnlyRoamParaChangeFlgFromSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    if ((TAF_MMA_SYS_CFG_MODE_SET != (usOperType & TAF_MMA_SYS_CFG_MODE_SET))
     && (TAF_MMA_SYS_CFG_BAND_SET != (usOperType & TAF_MMA_SYS_CFG_BAND_SET))
     && (TAF_MMA_SYS_CFG_ROAM_SET == (usOperType & TAF_MMA_SYS_CFG_ROAM_SET)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsNeedAttachPsFlgFromSysCfgOperType_SysCfg
 功能描述  : 根据操作类型获取是否只有漫游参数改变标志
 输入参数  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月16日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_IsNeedAttachPsFlgFromSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    if (TAF_MMA_SYS_CFG_PS_ATTACH_SET == (usOperType & TAF_MMA_SYS_CFG_PS_ATTACH_SET))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_NotifyCsServiceChange_SysCfg
 功能描述  : SYSCFG状态机中通知CS服务改变
 输入参数  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月16日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_NotifyCsServiceChange_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    TAF_CS_SERVICE_ENUM_UINT32          enCsState;

    enCsState = TAF_MMA_GetCsStateFromSyscfgOperType_SysCfg(usOperType);

    if (TAF_CS_SERVICE_BUTT != enCsState)
    {
        TAF_MMA_SndStkCsServiceChangeNotify(enCsState);
        TAF_MMA_SndMsgCsServiceChangeNotify(enCsState);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsLteExistInBothCurSysCfgAndOldSysCfg
 功能描述  : 当前的与上次的系统配置中LTE都存在
 输入参数  : pstCurSysCfg -- 当前的系统RAT配置
             pstOldSyscfg -- 上次的系统RAT配置
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- LTE在当前的与上次的都设置了
             VOS_FALSE -- LTE在当前的与上次的设置没有同时存在
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月4日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsLteExistInBothCurSysCfgAndOldSysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU           *pstCurSysCfg,
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *pstOldSyscfg
)
{
    VOS_UINT32                          ulCurLteSysCfg;

    ulCurLteSysCfg = MN_MMA_IsSpecRatInRatList(TAF_MMA_RAT_LTE, &pstCurSysCfg->stRatOrder);

    if ((VOS_TRUE == MN_MMA_IsSpecRatInRatList(TAF_MMA_RAT_LTE, &pstOldSyscfg->stRatPrioList))
     && (VOS_TRUE == ulCurLteSysCfg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  :TAF_MMA_IsNeedAttachAfterSyscfgSet_SysCfg
 功能描述  :判断SYSCFG设置完成后是否需要触发attach操作
 输入参数  :enRst---syscfg设置结果
 输出参数  :penAttachType----需要进行attach时的attach类型
            pucClassType-----需要进行attach时的服务域
 返 回 值  :VOS_TRUE  - 需要触发attach
            VOS_FALSE - 不需要触发attach
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月3日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedAttachAfterSyscfgSet_SysCfg(
    NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM_UINT32             enRst,
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                         *penAttachType,
    TAF_PH_MS_CLASS_TYPE                                   *pucClassType,
    TAF_MMA_SYS_CFG_OPER_TYPE                              *pusOperType
)
{
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType;
    TAF_MMA_SYS_CFG_OPER_TYPE           usOrigOperType;
    TAF_MMA_FSM_SYS_CFG_CTX_STRU       *pstSysCfgCtx = VOS_NULL_PTR;

    /* 获取当前状态机的上下文 */
    pstSysCfgCtx = &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx);

    usOperType      = pstSysCfgCtx->usOperType;
    usOrigOperType  = TAF_MMA_GetSysCfgOrigOperType_SysCfg();

    *pucClassType  = TAF_PH_MS_CLASS_NULL;

    MMA_ChangeSrv2Class(pstSysCfgCtx->stSysCfgPara.enSrvDomain, pucClassType);

    *penAttachType = TAF_MMA_GetAttachTypeFromSysCfgOperType_SysCfg(pstSysCfgCtx->usOperType);

    *pusOperType   = pstSysCfgCtx->usOperType;

    /* 1) syscfg设置触发DETACH-SYSCFG设置-ATTACH请求时，syscfg设置完成后,
            无论设置成功或失败,都需要发送attach请求; */
    if ((TAF_MMA_SYS_CFG_NONE_SET  != (usOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED))
     && (TAF_MMA_SYS_CFG_NONE_SET  != (usOrigOperType & TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED))
     && (TAF_MMA_SYS_CFG_NONE_SET  != (usOrigOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED)))
    {
        return VOS_TRUE;
    }

    /*
    2) syscfg设置触发DETACH-syscfg设置,如果syscfg设置失败,需要重新发送attach请求;
    */
    if ((TAF_MMA_SYS_CFG_NONE_SET         != (usOrigOperType & TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED))
     && (TAF_MMA_SYS_CFG_NONE_SET         == (usOperType & TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED))
     && (NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS != enRst))
    {
        /* detach哪个域,这个时候attach就用哪个域 */
        *penAttachType = TAF_MMA_GetDetachTypeFromSysCfgOperType_SysCfg(usOrigOperType);

        /* SYSCFG失败,恢复时使用之前的class type */
        *pucClassType  = gstMmaValue.stSetMsClass.MsClassType;

        *pusOperType  = TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED;

        return VOS_TRUE;
    }

    /*
    3) syscfg设置触发ATTACH-syscfg设置,如果syscfg设置成功,需要发送attach请求;
    */
    if ((TAF_MMA_SYS_CFG_NONE_SET         != (usOrigOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED))
     && (TAF_MMA_SYS_CFG_NONE_SET         != (usOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED))
     && (NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS == enRst))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*lint -restore*/


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





