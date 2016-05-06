/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdSndXcc.c
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2014年7月7日
  最近修改   :
  功能描述   : XSD发送给XCC的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月7日
    作    者   : h00246512
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasMain.h"
#include "CnasXsdSndXcc.h"
#include "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_SND_XCC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XSD_SndXccStartReq
 功能描述  : 向XCC发送开机请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月7日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_SndXccStartReq(VOS_VOID)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, begin */
    XSD_XCC_START_REQ_STRU             *pstInternalMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(XSD_XCC_START_REQ_STRU);

    pstInternalMsg  = (XSD_XCC_START_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_XSD, ulLen);
    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    /* 填充消息 */

    pstInternalMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstInternalMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid               = UEPS_PID_XCC;

    pstInternalMsg->enMsgId                     = ID_XSD_XCC_START_REQ;
    pstInternalMsg->usOpId                      = 0;
    pstInternalMsg->ulLength                    = sizeof(XSD_XCC_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 发送内部消息 */
    CNAS_SndInternalMsg(pstInternalMsg);
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, end */

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SndXccPowerOffReq
 功能描述  : 向XCC发送关机回复
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月7日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_SndXccPowerOffReq(
    XCC_XSD_POWER_OFF_REASON_ENUM_UINT32                    enPowerOffReason
)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, begin */
    XSD_XCC_POWER_OFF_REQ_STRU         *pstInternalMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(XSD_XCC_POWER_OFF_REQ_STRU);

    pstInternalMsg  = (XSD_XCC_POWER_OFF_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_XSD, ulLen);
    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    /* 填充消息 */

    pstInternalMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstInternalMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid               = UEPS_PID_XCC;

    pstInternalMsg->enMsgId                     = ID_XSD_XCC_POWER_OFF_REQ;
    pstInternalMsg->usOpId                      = 0;
    pstInternalMsg->ulLength                    = sizeof(XSD_XCC_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInternalMsg->enPowerOffReason            = enPowerOffReason;
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-6, end */

    /* 发送内部消息 */
    CNAS_SndInternalMsg(pstInternalMsg);

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SndXccNdssResultInd
 功能描述  : 向XCC发送NDSS结果
 输入参数  : enNsddResult - NDSS结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月8日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_SndXccNdssResultInd(
    XSD_XCC_NDSS_RESULT_ENUM_UINT8      enNsddResult
)
{
    XSD_XCC_NDSS_RESULT_IND_STRU       *pstNdssResultInd  = VOS_NULL_PTR;

    pstNdssResultInd  = (XSD_XCC_NDSS_RESULT_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_XSD,
                                                                              sizeof(XSD_XCC_NDSS_RESULT_IND_STRU));

    if (VOS_NULL_PTR == pstNdssResultInd)
    {
        return;
    }

    NAS_MEM_SET_S(pstNdssResultInd, sizeof(XSD_XCC_NDSS_RESULT_IND_STRU), 0, sizeof(XSD_XCC_NDSS_RESULT_IND_STRU));

    /* 填充消息 */
    pstNdssResultInd->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstNdssResultInd->ulReceiverPid    = UEPS_PID_XCC;
    pstNdssResultInd->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstNdssResultInd->ulSenderPid      = UEPS_PID_XSD;
    pstNdssResultInd->ulLength         = sizeof(XSD_XCC_NDSS_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstNdssResultInd->enMsgId                = ID_XSD_XCC_NDSS_RESULT_IND;
    pstNdssResultInd->enNsddResult           = enNsddResult;

    /* 发送消息 */
    CNAS_SndInternalMsg(pstNdssResultInd);
}

/*lint -restore*/
#endif








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

