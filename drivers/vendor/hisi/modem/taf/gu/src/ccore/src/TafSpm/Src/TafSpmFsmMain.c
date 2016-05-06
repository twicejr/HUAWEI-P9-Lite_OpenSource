/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmFsmMain.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年5月8日
  最近修改   :
  功能描述   : TafSpmFsmMain.C文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月7日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "AtMnInterface.h"
#include "TafTypeDef.h"
#include "TafSpmCtx.h"
#include "TafSpmFsmMain.h"
#include "TafSpmFsmMainTbl.h"
#include "SsInclude.h"
#include "TafSpmFsmServiceCtrlTbl.h"
#include "TafSpmSndInternalMsg.h"
#include "MnErrorCode.h"
#include "TafLog.h"
#include "AtMnInterface.h"

/* Modified by z00161729 for V9R1 STK升级, 2013-7-24, begin */
#include "NasStkInterface.h"
/* Modified by z00161729 for V9R1 STK升级, 2013-7-24, end */
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-09, begin */
#include "MnCallMnccProc.h"
/* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-09-18, begin */
/* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-09-18, end */
#include "TafSpmServiceDomainSelProc.h"
#include "TafSdcLib.h"
#include "MnCallApi.h"
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-09, end */

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-18, begin */
#include "TafAgentInterface.h"
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-18, end */

#include "TafSpmRedial.h"
#include "TafSpmComFunc.h"
#include "TafSpmServiceDomainSelProc.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_FSM_MAIN_C

/*lint -save -e958 */

/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-31, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAtSSReqMsg_Main
 功能描述  : MAIN状态机初始化状态收到AT的注册SS业务的消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月7日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年07月23日
   作    者   : y00245242
   修改内容   : VOLTE开发, 把main状态下的FDN与call control检查移到service状态
                机下控制
 3.日    期   : 2013年12月30日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppReqMsg_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           ucIdleFsmIndex;

    (VOS_VOID)TAF_SPM_GetClientIdWithAppMsg(pstMsg, &usClientId);
    TAF_SPM_GetOpIdWithAppMsg(pstMsg, &ucOpId);

    /* 判断是否有存在空闲状态机 */
    ucIdleFsmIndex = TAF_SPM_GetIdleEntityFsmIndex();

    if (TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX == ucIdleFsmIndex)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvAppReqMsg_Main():WARNING: No Idle Entiy Fsm Exist!");
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-30, begin */
        /* 临时响应改为正式响应 */
        TAF_SPM_SendServiceRequetFail_Main(ulEventType, pstMsg, MN_ERR_CLASS_SPM_BEYOND_CONCURRENCY_CAPABILITY);
        /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-30, end */

#if (FEATURE_ON == FEATURE_IMS)
        TAF_SPM_SetEconfPreRslt(TAF_CS_CAUSE_UNKNOWN);

        TAF_SPM_ReportEconfCheckRslt();
#endif
    }
    else
    {
        /* 设置当前状态机的索引 */
        TAF_SPM_SetCurrEntityFsmAddr(ucIdleFsmIndex);

        /* 设置当前client ID实体状态机的client ID */
        TAF_SPM_SetCurrEntityFsmClientId(usClientId);

        /* 启动service ctrl状态机,进行fdn&CALL control检查 */
        TAF_SPM_FSM_InitEntityFsm(TAF_SPM_FSM_SERVICE_CTRL,
                                      TAF_SPM_GetServiceCtrlFsmDescAddr(),
                                      TAF_SPM_SERVICE_CTRL_STA_INIT);
    }

    return VOS_TRUE;
}
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-31, end */

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvSpmServiceCtrlResultInd_Main
 功能描述  : MAIN状态机初始化状态收到TAF_SPM_INTERNAL_SERVICE_CTRL_RESULT_IND的消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月7日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年07月30日
   作    者   : y00245242
   修改内容   : VOLTE开发, 增加IMS域选择处理
 3.日    期   : 2013年12月30日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvSpmServiceCtrlResultInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SERVICE_CTRL_RSLT_STRU                         *pstServiceCtrlRslt = VOS_NULL_PTR;
    VOS_UINT8                                               ucOpId;
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, begin */
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulAppEventType;
    struct MsgCB                                           *pstAppMsg          = VOS_NULL_PTR;
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;

    ulRet   = VOS_TRUE;
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, end */

    pstServiceCtrlRslt = (TAF_SPM_SERVICE_CTRL_RSLT_STRU*)pstMsg;

    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-30, begin */
    TAF_SPM_GetOpIdWithAppMsg((struct MsgCB*)pstServiceCtrlRslt->stEntryMsg.aucEntryMsgBuffer, &ucOpId);

    pstAppMsg      = (struct MsgCB*)&(pstServiceCtrlRslt->stEntryMsg.aucEntryMsgBuffer[0]);
    ulAppEventType = pstServiceCtrlRslt->stEntryMsg.ulEventType;

    /* 检查结果为失败 */
    if (TAF_SPM_SERVICE_CTRL_FAIL == pstServiceCtrlRslt->enResult)
    {
        /* 向AT或STK发送失败结果,携带cause,临时响应修改为正式响应 */
        TAF_SPM_SendServiceRequetFail_Main(ulAppEventType, pstAppMsg, pstServiceCtrlRslt->ulCause);

        return VOS_TRUE;
    }
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-30, end */

    enDomainSelRslt = TAF_SPM_ProcServiceRequestDomainSelection(ulAppEventType, pstAppMsg);

    ulRet           = TAF_SPM_ProcInitialDomainSelectionResult(ulAppEventType, pstAppMsg, enDomainSelRslt);

    if (VOS_TRUE == ulRet)
    {
        return VOS_TRUE;
    }

    /* 检查结果为成功设置更新入口消息标记并保存修改后的入口消息到全局变量中 */
    TAF_SPM_UpdateServiceCtrlEntryMsg(ulAppEventType, pstAppMsg);

    TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

    return VOS_FALSE;
}

/* 删除 */


/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, begin */
/* 对IMSA消息的处理放到预处理中实现 */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, end */


/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-30, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_SendServiceRequetFail_Main
 功能描述  : 根据业务类型给AT/STK回复失败

 输入参数  : ulEventType -- 消息事件类型
             pstMsg      -- 消息指针
             ulCause     -- 失败原因值

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月31日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SendServiceRequetFail_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    VOS_UINT32                          ulCause
)
{
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSrvReqType;

    enSrvReqType = TAF_SPM_GetServiceRequestType(pstMsg);

    switch (enSrvReqType)
    {
        case TAF_SPM_SRV_REQ_TYPE_CALL:
            TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, ulCause);
            break;

        case TAF_SPM_SRV_REQ_TYPE_SMS:
            TAF_SPM_SendSmsServiceRequetFail(ulEventType, pstMsg, ulCause);
            break;

        case TAF_SPM_SRV_REQ_TYPE_SS:
            TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)ulCause);
            break;

        default:
            break;

    }

    return;
}

/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-30, end */

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

