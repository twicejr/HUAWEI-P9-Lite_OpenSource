/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsSndXcall.c
  版 本 号   : 初稿
  作    者   : C00299064
  生成日期   : 2015年10月14日
  功能描述   : 1X SMS(Short Message Service)给XCALL发消息
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月14日
    作    者   : C00299064
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXsmsSndXcall.h"
#include "PsLogdef.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_SND_XCALL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_XSMS_SndXcallMsgSendCnf
 功能描述  : 将XCALL的DBM 发送结果发送給XCALL
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月14日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_SndXcallMsgSendCnf(
    XSMS_XCALL_SEND_RESULT_ENUM_UINT8   enRslt,
    VOS_UINT16                          usOpId
)
{
    XSMS_XCALL_KMC_MSG_SEND_CNF_STRU     *pstSendCnf;

    pstSendCnf = (XSMS_XCALL_KMC_MSG_SEND_CNF_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                               (sizeof(XSMS_XCALL_KMC_MSG_SEND_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    if (VOS_NULL_PTR == pstSendCnf)
    {
        return VOS_ERR;
    }

    VOS_MemSet((VOS_UINT8*)pstSendCnf + VOS_MSG_HEAD_LENGTH, 0, sizeof(XSMS_XCALL_KMC_MSG_SEND_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSendCnf->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstSendCnf->ulSenderPid         = UEPS_PID_XSMS;
    pstSendCnf->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstSendCnf->ulReceiverPid       = WUEPS_PID_TAF;
    pstSendCnf->ulLength            = sizeof(XSMS_XCALL_KMC_MSG_SEND_CNF_STRU) - VOS_MSG_HEAD_LENGTH;


    pstSendCnf->enMsgId             = ID_XSMS_XCALL_KMC_MSG_SEND_CNF;
    pstSendCnf->usOpId              = usOpId;
    pstSendCnf->enRslt              = enRslt;

    PS_SEND_MSG(UEPS_PID_XSMS, pstSendCnf);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_SndXcallDataInd
 功能描述  : 收到短信的XCALL相关的DBM 給XCALL
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月14日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_SndXcallDataInd(
    VOS_UINT32                          ulUserDataLen,
    VOS_UINT8                          *pucData
)
{
    XSMS_XCALL_KMC_MSG_RCV_IND_STRU    *pstDataInd;
    VOS_UINT32                          ulMsgLen;

    ulMsgLen    = sizeof(XSMS_XCALL_KMC_MSG_RCV_IND_STRU) + ulUserDataLen - 4 - VOS_MSG_HEAD_LENGTH;

    pstDataInd  = (XSMS_XCALL_KMC_MSG_RCV_IND_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                                 ulMsgLen);

    if (VOS_NULL_PTR == pstDataInd)
    {
        return VOS_ERR;
    }

    VOS_MemSet((VOS_UINT8*)pstDataInd + VOS_MSG_HEAD_LENGTH, 0, ulMsgLen);

    pstDataInd->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstDataInd->ulSenderPid         = UEPS_PID_XSMS;
    pstDataInd->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstDataInd->ulReceiverPid       = WUEPS_PID_TAF;
    pstDataInd->ulLength            = ulMsgLen;


    pstDataInd->enMsgId             = ID_XSMS_XCALL_KMC_MSG_RCV_IND;
    pstDataInd->usDataLen           = (VOS_UINT8)ulUserDataLen;

    PS_MEM_CPY(pstDataInd->aucData, pucData, ulUserDataLen);

    PS_SEND_MSG(UEPS_PID_XSMS, pstDataInd);

    return VOS_OK;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



