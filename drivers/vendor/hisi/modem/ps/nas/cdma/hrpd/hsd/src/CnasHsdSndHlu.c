/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdSndHlu.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年12月10日
  最近修改   :
  功能描述   : HSD发送给HLU的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月10日
    作    者   : h00300778
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "hsd_hlu_pif.h"
#include  "CnasMain.h"
#include  "CnasHsdSndHlu.h"
#include  "cas_hrpd_airlinkmgmt_nas_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_SND_HLU_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_SndHluStartReq
 功能描述  : 向HLU发送开机请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndHluStartReq(VOS_VOID)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, begin */
    HSD_HLU_START_REQ_STRU             *pstInternalMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(HSD_HLU_START_REQ_STRU);

    pstInternalMsg  = (HSD_HLU_START_REQ_STRU*)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);
    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    /* 填充消息 */
    pstInternalMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstInternalMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid               = UEPS_PID_HLU;

    pstInternalMsg->enMsgId                     = ID_HSD_HLU_START_REQ;
    pstInternalMsg->usOpId                      = 0;
    pstInternalMsg->ulLength                    = sizeof(HSD_HLU_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送内部消息 */
    CNAS_SndInternalMsg(pstInternalMsg);
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, end */

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndHluPowerOffReq
 功能描述  : 向HLU发送关机请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndHluPowerOffReq(VOS_VOID)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, begin */
    HSD_HLU_POWER_OFF_REQ_STRU         *pstInternalMsg;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(HSD_HLU_POWER_OFF_REQ_STRU);

    pstInternalMsg  = (HSD_HLU_POWER_OFF_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);
    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    /* 填充消息 */

    pstInternalMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstInternalMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid               = UEPS_PID_HLU;

    pstInternalMsg->enMsgId                     = ID_HSD_HLU_POWER_OFF_REQ;
    pstInternalMsg->usOpId                      = 0;
    pstInternalMsg->ulLength                    = sizeof(HSD_HLU_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送内部消息 */
    CNAS_SndInternalMsg(pstInternalMsg);
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, end */

    return;
}
/*lint -restore*/
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
