

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasMntn.h"
#include "NasMsccSndRrm.h"
#include "NasComm.h"
#include "NasMsccCtx.h"
#include "NasMmlCtx.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_SND_RRM_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/


#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))


VOS_VOID NAS_MSCC_SndRrmRatCombModeInd(VOS_VOID)
{
    PS_RRM_RAT_COMBINED_MODE_IND_STRU  *pstMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucIsCLmode;

    pstMsg = (PS_RRM_RAT_COMBINED_MODE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  UEPS_PID_MSCC,
                                                  sizeof(PS_RRM_RAT_COMBINED_MODE_IND_STRU));
    /* 内存申请失败 */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "NAS_MSCC_SndRrmRatCombModeInd:ERROR: Memory Alloc Error for pMsg");

        /* 返回失败 */
        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                 sizeof(PS_RRM_RAT_COMBINED_MODE_IND_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_RAT_COMBINED_MODE_IND;
    pstMsg->enModemId                       = VOS_GetModemIDFromPid(UEPS_PID_MSCC);

    ucIsCLmode = NAS_MSCC_IsCLCombinedModeWithRatPrio(NAS_MSCC_GetRatPrioList());
    if (VOS_TRUE == ucIsCLmode)
    {
        pstMsg->enRatCombMode               = PS_RRM_RAT_COMBINED_MODE_CL;
    }
    else
    {
        pstMsg->enRatCombMode               = PS_RRM_RAT_COMBINED_MODE_GUL;
    }

    /*发送消息*/
    PS_SEND_MSG(UEPS_PID_MSCC, pstMsg);

    return;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



