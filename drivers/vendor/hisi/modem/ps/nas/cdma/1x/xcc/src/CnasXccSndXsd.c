/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccSndXsd.c
  版 本 号   : 初稿
  作    者   : y00213812
  生成日期   : 2014年07月03日
  功能描述   : 1X CC发给XSD的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : y00213812
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXccSndXsd.h"
#include  "CnasMain.h"
#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_SND_XSD_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXsdStartCnf
 功能描述  : 给XSD模块发送ID_XCC_XSD_START_CNF消息
 输入参数  : XCC_XSD_START_RESULT_ENUM_UINT32    enRslt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月3日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXsdStartCnf(
    XCC_XSD_START_RESULT_ENUM_UINT32    enRslt
)
{
    XCC_XSD_START_CNF_STRU             *pstInternalMsg = VOS_NULL_PTR;

    pstInternalMsg = (XCC_XSD_START_CNF_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_XCC,
                                                    sizeof(XCC_XSD_START_CNF_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid     = UEPS_PID_XCC;

    pstInternalMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid   = UEPS_PID_XSD;

    pstInternalMsg->ulLength
        = sizeof(XCC_XSD_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->enMsgId         = ID_XCC_XSD_START_CNF;
    pstInternalMsg->usOpId          = 0;

    pstInternalMsg->enRslt          = enRslt;

    CNAS_SndInternalMsg(pstInternalMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXsdPowerOffCnf
 功能描述  : 给XSD模块发送ID_XCC_XSD_POWER_OFF_CNF消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月3日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXsdPowerOffCnf(
    XCC_XSD_POWER_OFF_RESULT_ENUM_UINT32    enRslt
)
{
    XCC_XSD_POWER_OFF_CNF_STRU        *pstInternalMsg = VOS_NULL_PTR;

    pstInternalMsg  = (XCC_XSD_POWER_OFF_CNF_STRU*)CNAS_GetIntMsgSendBuf(UEPS_PID_XCC,
                                                        sizeof(XCC_XSD_POWER_OFF_CNF_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid     = UEPS_PID_XCC;

    pstInternalMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid   = UEPS_PID_XSD;

    pstInternalMsg->ulLength
        = sizeof(XCC_XSD_POWER_OFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->enMsgId         = ID_XCC_XSD_POWER_OFF_CNF;
    pstInternalMsg->usOpId          = 0;

    pstInternalMsg->enRslt          = enRslt;

    CNAS_SndInternalMsg(pstInternalMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndXsdDeregisterInd
 功能描述  : 给XSD模块发送关机去注册指示
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXsdDeregisterInd(
    XSD_XCC_DEREGISTER_REASON_ENUM_UINT8                    enCause
)
{
    XCC_XSD_DEREGISTER_IND_STRU        *pstInternalMsg = VOS_NULL_PTR;

    pstInternalMsg  = (XCC_XSD_DEREGISTER_IND_STRU*)CNAS_GetIntMsgSendBuf(UEPS_PID_XCC,
                                                        sizeof(XCC_XSD_DEREGISTER_IND_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid     = UEPS_PID_XCC;

    pstInternalMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid   = UEPS_PID_XSD;

    pstInternalMsg->ulLength
        = sizeof(XCC_XSD_DEREGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->enMsgId         = ID_XCC_XSD_DEREGISTER_IND;
    pstInternalMsg->usOpId          = 0;
    pstInternalMsg->enCause         = enCause;

    NAS_MEM_SET_S(pstInternalMsg->aucRsv, sizeof(pstInternalMsg->aucRsv), 0x0, sizeof(VOS_UINT8) * 3);

    CNAS_SndInternalMsg(pstInternalMsg);

    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




