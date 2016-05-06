/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXregSndXsd.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年07月03日
  功能描述   : 1X REG(register)发给XSD的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : l60609
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXregSndXsd.h"
#include  "CnasMain.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_SND_XSD_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XREG_SndXsdStartCnf
 功能描述  : 给XSD模块发送ID_XREG_XSD_START_CNF消息
 输入参数  : XREG_XSD_START_RESULT_ENUM_UINT32   enRslt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月4日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_SndXsdStartCnf(
    XREG_XSD_START_RESULT_ENUM_UINT32   enRslt
)
{
    XREG_XSD_START_CNF_STRU            *pstInternalMsg = VOS_NULL_PTR;

    pstInternalMsg  = (XREG_XSD_START_CNF_STRU*)CNAS_GetIntMsgSendBuf(UEPS_PID_XREG,
                                                        sizeof(XREG_XSD_START_CNF_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid     = UEPS_PID_XREG;

    pstInternalMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid   = UEPS_PID_XSD;

    pstInternalMsg->ulLength
        = sizeof(XREG_XSD_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->enMsgId         = ID_XREG_XSD_START_CNF;
    pstInternalMsg->usOpId          = 0;

    pstInternalMsg->enRslt          = enRslt;

    CNAS_SndInternalMsg(pstInternalMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SndXsdPowerOffCnf
 功能描述  : 给XSD模块发送ID_XREG_XSD_POWER_OFF_CNF消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月3日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_SndXsdPowerOffCnf(VOS_VOID)
{
    XREG_XSD_POWER_OFF_CNF_STRU        *pstInternalMsg = VOS_NULL_PTR;

    pstInternalMsg  = (XREG_XSD_POWER_OFF_CNF_STRU*)CNAS_GetIntMsgSendBuf(UEPS_PID_XREG,
                                                        sizeof(XREG_XSD_POWER_OFF_CNF_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid     = UEPS_PID_XREG;

    pstInternalMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid   = UEPS_PID_XSD;

    pstInternalMsg->ulLength
        = sizeof(XREG_XSD_POWER_OFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->enMsgId         = ID_XREG_XSD_POWER_OFF_CNF;
    pstInternalMsg->usOpId          = 0;

    CNAS_SndInternalMsg(pstInternalMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XREG_SndXsdPowerOffCnf
 功能描述  : 给XSD模块发送ID_XREG_XSD_POWER_OFF_CNF消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月5日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XREG_SndXsdRegSuccessInd(VOS_VOID)
{
    XREG_XSD_REG_SUCCESS_IND_STRU        *pstInternalMsg = VOS_NULL_PTR;

    pstInternalMsg  = (XREG_XSD_REG_SUCCESS_IND_STRU*)CNAS_GetIntMsgSendBuf(UEPS_PID_XREG,
                                                        sizeof(XREG_XSD_REG_SUCCESS_IND_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid     = UEPS_PID_XREG;

    pstInternalMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid   = UEPS_PID_XSD;

    pstInternalMsg->ulLength
        = sizeof(XREG_XSD_REG_SUCCESS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->enMsgId         = ID_XREG_XSD_REG_SUCCESS_IND;
    pstInternalMsg->usOpId          = 0;

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



