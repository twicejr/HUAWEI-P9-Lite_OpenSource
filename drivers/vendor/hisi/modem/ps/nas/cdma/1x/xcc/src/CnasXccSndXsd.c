

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




