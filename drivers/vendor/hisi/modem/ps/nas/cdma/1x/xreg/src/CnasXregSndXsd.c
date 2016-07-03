

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



