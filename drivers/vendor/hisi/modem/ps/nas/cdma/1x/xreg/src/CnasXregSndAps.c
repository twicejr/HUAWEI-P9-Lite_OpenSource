

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXregSndAps.h"
#include  "xreg_aps_pif.h"
#include  "CnasXregProcess.h"
#include  "CnasCcb.h"
#include  "CnasMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_SND_APS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_VOID CNAS_XREG_SndApsRegBeginInd(VOS_VOID)
{
    XREG_APS_REG_BEGIN_IND_STRU        *pstMsg;
    VOS_UINT8                          *pucContent;
    CNAS_XREG_SYS_MSG_CONTENT_STRU     *pstSysMsgCont;

    /*申请消息*/
    pstMsg  = (XREG_APS_REG_BEGIN_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_XREG,
                        sizeof(XREG_APS_REG_BEGIN_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pucContent = (VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET(pucContent, 0, sizeof(XREG_APS_REG_BEGIN_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /*填写参数*/
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->enMsgId         = ID_XREG_APS_REG_BEGIN_IND;

    pstSysMsgCont = CNAS_XREG_GetSysMsgAddr();

    pstMsg->usSid           = pstSysMsgCont->stSysInfo.usSid;

    pstMsg->usNid           = pstSysMsgCont->stSysInfo.usNid;
    pstMsg->ucPzid          = pstSysMsgCont->stSysInfo.ucPacketZoneId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*发送消息*/
    PS_SEND_MSG(UEPS_PID_XREG, pstMsg);

    return;
}

/*lint -restore*/
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



