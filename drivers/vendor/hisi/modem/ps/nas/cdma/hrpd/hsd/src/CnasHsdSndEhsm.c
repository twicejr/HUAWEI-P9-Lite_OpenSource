/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdSndEhsm.c
  版 本 号   : 初稿
  作    者   : z00316370
  生成日期   : 2015年06月03日
  最近修改   :
  功能描述   : HSD发送给EHSM的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年06月03日
    作    者   : z00316370
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasMain.h"
#include  "CnasHsdSndEhsm.h"
#include  "cas_hrpd_airlinkmgmt_nas_pif.h"
#include  "PsCommonDef.h"
#include  "CnasMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_SND_EHSM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_SndHsmStartReq
 功能描述  : 向EHSM发送开机请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月04日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndEhsmStartReq(
    MSCC_HSD_START_REQ_STRU            *pstMsg
)
{
    HSD_EHSM_START_REQ_STRU            *pstStartMsg;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          i;

    i                                   = 0;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen        = sizeof(HSD_EHSM_START_REQ_STRU);

    pstStartMsg  = (HSD_EHSM_START_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstStartMsg)
    {
        return;
    }

    /* 填充消息 */
    pstStartMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstStartMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstStartMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstStartMsg->ulReceiverPid               = UEPS_PID_EHSM;
    pstStartMsg->enMsgId                     = ID_HSD_EHSM_START_REQ;
    pstStartMsg->usOpId                      = 0;
    pstStartMsg->ulLength                    = sizeof(HSD_EHSM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstStartMsg->enModemId                   = pstMsg->enModemId;

    /* 初始化RatMode = BUTT */
    for (i = NAS_MSCC_PIF_MAX_RAT_NUM; i < VOS_RATMODE_BUTT; i++)
    {
        pstStartMsg->aenRatMode[i]  = VOS_RATMODE_BUTT;
    }

    PS_MEM_CPY(pstStartMsg->aenRatMode,
               pstMsg->aenRatMode,
               NAS_MSCC_PIF_MAX_RAT_NUM * sizeof(VOS_RATMODE_ENUM_UINT32));

    /* 发送内部消息 */
    (VOS_VOID)CNAS_SndInternalMsg(pstStartMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndEhsmPowerOffReq
 功能描述  : 向EHSM发送关机请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月04日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndEhsmPowerOffReq(
    EHSM_HSD_POWER_OFF_CAUSE_ENUM_UINT32                    enCause
)
{
    HSD_EHSM_POWER_OFF_REQ_STRU        *pstMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(HSD_EHSM_POWER_OFF_REQ_STRU);

    pstMsg  = (HSD_EHSM_POWER_OFF_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_EHSM;

    pstMsg->enMsgId                     = ID_HSD_EHSM_POWER_OFF_REQ;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_EHSM_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enCause                     = enCause;

    /* 发送内部消息 */
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);

    return;
}

/*lint -restore*/
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
