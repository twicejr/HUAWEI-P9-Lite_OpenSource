
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsSndNd.c　
  版 本 号   : 初稿
  作    者   : A00165503
  生成日期   : 2011年12月31日
  最近修改   :
  功能描述   : MMC发给ND Client的消息的处理
  函数列表   :

  修改历史   :
  1.日    期   : 2011年12月31日
    作    者   : A00165503
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "PsTypeDef.h"

#include "TafLog.h"
#include "Taf_Aps.h"

#include "ApsNdInterface.h"
#include "TafApsSndNd.h"



#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_ND_C

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/


/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
*****************************************************************************/


/******************************************************************************
   5 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_APS_SndNdPdpActInd
 功能描述  : 向ND Client发送ID_APS_NDCLIENT_PDP_ACT_IND消息
 输入参数  : ucRabId                    - RAB ID
             pucIpv6Addr                - IPv6地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月31日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndNdPdpActInd(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                          *pucIpv6Addr
)
{
    APS_NDCLIENT_PDP_ACT_IND           *pstNdPdpActInd;

    /* 构造消息 */
    pstNdPdpActInd = (APS_NDCLIENT_PDP_ACT_IND*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_NDCLIENT_PDP_ACT_IND));
    if (VOS_NULL_PTR == pstNdPdpActInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndNdPdpActInd: Memory alloc failed.");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstNdPdpActInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(APS_NDCLIENT_PDP_ACT_IND) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstNdPdpActInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstNdPdpActInd->ulReceiverPid   = UEPS_PID_NDCLIENT;
    pstNdPdpActInd->ulMsgId         = ID_APS_NDCLIENT_PDP_ACT_IND;

    /* 填写消息内容 */
    pstNdPdpActInd->ucRabId         = ucRabId;
    PS_MEM_CPY(pstNdPdpActInd->aucIpv6InterfacId,
               pucIpv6Addr + (TAF_IPV6_ADDR_LEN - APS_NDCLIENT_IPV6_IFID_LENGTH),
               APS_NDCLIENT_IPV6_IFID_LENGTH);

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstNdPdpActInd))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndNdPdpActInd: Send message failed.");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndNdPdpDeactInd
 功能描述  : 向ND Client发送ID_APS_NDCLIENT_PDP_DEACT_IND消息
 输入参数  : ucRabId                    - RAB ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月31日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndNdPdpDeactInd(
    VOS_UINT8                           ucRabId
)
{
    APS_NDCLIENT_PDP_DEACT_IND         *pstNdPdpDeactInd;

    /* 构造消息 */
    pstNdPdpDeactInd = (APS_NDCLIENT_PDP_DEACT_IND*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_NDCLIENT_PDP_DEACT_IND));
    if (VOS_NULL_PTR == pstNdPdpDeactInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndNdPdpDeactInd: Memory alloc failed.");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstNdPdpDeactInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(APS_NDCLIENT_PDP_DEACT_IND) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstNdPdpDeactInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstNdPdpDeactInd->ulReceiverPid   = UEPS_PID_NDCLIENT;
    pstNdPdpDeactInd->ulMsgId         = ID_APS_NDCLIENT_PDP_DEACT_IND;

    /* 填写消息内容 */
    pstNdPdpDeactInd->ucRabId         = ucRabId;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstNdPdpDeactInd))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndNdPdpDeactInd: Send message failed.");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndNdRelInd
 功能描述  : 向ND Client发送ID_APS_NDCLIENT_REL_IND消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月31日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndNdRelInd(VOS_VOID)
{
    APS_NDCLIENT_REL_IND_STRU          *pstNdRelInd;

    /* 构造消息 */
    pstNdRelInd = (APS_NDCLIENT_REL_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_NDCLIENT_REL_IND_STRU));
    if (VOS_NULL_PTR == pstNdRelInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndNdRelInd: Memory alloc failed.");
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstNdRelInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(APS_NDCLIENT_REL_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstNdRelInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstNdRelInd->ulReceiverPid   = UEPS_PID_NDCLIENT;
    pstNdRelInd->ulMsgId         = ID_APS_NDCLIENT_REL_IND;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstNdRelInd))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndNdRelInd: Send message failed.");
        return;
    }

    return;
}

/*lint +e958*/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



