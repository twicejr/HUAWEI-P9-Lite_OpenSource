/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallProcTaf.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年04月26日
  最近修改   :
  功能描述   : 处理TAF发送给CALL模块的消息
  函数列表   :

  修改历史   :
  1.日    期   : 2014年04月26日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "MnCallProcTaf.h"
#include "MnCallMgmt.h"
#include "TafSdcCtx.h"
#include "MnCallSendApp.h"
#include "MnCallReqProc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_MN_CALL_PROC_TAF_C

/*****************************************************************************
   2 变量定义
*****************************************************************************/


/*****************************************************************************
   3 函数实现
*****************************************************************************/
/*lint -save -e958 */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 函 数 名  : TAF_CALL_RelAllNormalCall
 功能描述  : 释放所有正常呼叫
 
 输入参数  : pstMsg   - 消息地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月26日
    作    者   : y00245242
    修改内容   : 为eCall feature增加
  2.日    期   : 2015年10月10日
    作    者   : c00318887
    修改内容   : DTS2015090607329
*****************************************************************************/
VOS_VOID TAF_CALL_RelAllNormalCall(
    TAF_CALL_TAF_REL_CALL_REQ_STRU     *pstMsg
)
{
    VOS_UINT8                                               i;
    VOS_UINT32                                              ulNumOfCalls;
    MN_CALL_ID_T                                            aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_SUPS_PARAM_STRU                                 stSupsParam;

    MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);

    /* 异常保护，该场景不应该出现, 否则CS呼叫存在标志维护异常了 */
    if (0 == ulNumOfCalls)
    {
        /* 清除CS呼叫存在标记 */
        TAF_CALL_SetCsCallExistFlg(VOS_FALSE, MN_CALL_TYPE_BUTT);

        /* 发送确认消息给SPM */
        TAF_CALL_SendTafRelCallCnf(pstMsg->usClientId, pstMsg->ucOpId, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    for (i = 0; i < ulNumOfCalls; i++)
    {
        /* 如果当前有紧急呼，跳出循环 */
        if (VOS_TRUE == TAF_CALL_IsCallTypeEmgencyCall(aCallIds[i]))
        {
            /* 当前有紧急呼存在，禁止当前操作 */
            TAF_CALL_SendTafRelCallCnf(pstMsg->usClientId, pstMsg->ucOpId, TAF_CS_CAUSE_NOT_ALLOW);

            return;
        }
    } 

    /* 设置内部挂机操作为TRUE */
    TAF_CALL_SetInternalHangUpFlag(VOS_TRUE);

    PS_MEM_SET(&stSupsParam, 0, sizeof(MN_CALL_SUPS_PARAM_STRU));
    
    stSupsParam.enCallSupsCmd = MN_CALL_SUPS_CMD_REL_ALL_CALL;
    
    /* 释放所有normal呼叫 */    
    MN_CALL_CallSupsCmdRelAllCallReqProc(pstMsg->usClientId, pstMsg->ucOpId, &stSupsParam);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_CALL_RcvTafRelCallReq
 功能描述  : 处理TAF发送释放呼叫请求消息
 
 输入参数  : pstMsg   - 消息地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月26日
    作    者   : y00245242
    修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_CALL_RcvTafRelCallReq(
    TAF_CALL_TAF_REL_CALL_REQ_STRU                  *pstMsg
)
{
    if (TAF_CALL_REL_CALL_ALL_NORMAL == pstMsg->enRelType)
    {
        TAF_CALL_RelAllNormalCall(pstMsg);
    }
}
#endif
/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



