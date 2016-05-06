

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsCommonDef.h"
#include  "NasMsccSndInternalMsg.h"
#include  "NasMsccCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_SND_INTERNAL_MSG_C



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 -e429 -e830 */

VOS_VOID NAS_MSCC_SndSwitchOnRslt(
    VOS_UINT32                          ulResult
)
{
    NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU                  *pstMsg = VOS_NULL_PTR;

    /* Alloc the memory for Switch On result Message */
    pstMsg  = (NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                                                    sizeof(NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU));

    /* Return if malloc fails */
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* Construct the internal message */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->ulLength                    = sizeof(NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->enRslt                      = ulResult;

    NAS_MSCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

}




VOS_VOID NAS_MSCC_SndPowerOffRslt(
    NAS_MSCC_POWEROFF_RSLT_ENUM_UINT32  enRslt
)
{
    NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU                  *pstMsg = VOS_NULL_PTR;

    /* Alloc the memory for Power off result structure */
    pstMsg  = (NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                                                    sizeof(NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU));

    /* Return if malloc fails */
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* Construct the internal message structure */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->ulLength                    = sizeof(NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF;
    pstMsg->usOpId                      = 0;

    pstMsg->enRslt                      = enRslt;


    /* 发送内部消息 */
    NAS_MSCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}


VOS_VOID NAS_MSCC_SndSysCfgRslt(
    NAS_MSCC_SYS_CFG_RESULT_ENUM_UINT32      ulResult
)
{
    NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU                  *pstMsg = VOS_NULL_PTR;

    /* Alloc the memory for Systsm config result Message */
    pstMsg  = (NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                                                  sizeof(NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU));

    /* Return if malloc fails */
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* Construct the internal message */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->ulLength                    = sizeof(NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF;
    pstMsg->enRslt                      = ulResult;

    NAS_MSCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

    return;
}




VOS_VOID NAS_MSCC_SndAbortFsmReq(VOS_VOID)
{
    NAS_MSCC_MSCC_ABORT_FSM_REQ_STRU   *pstMsg = VOS_NULL_PTR;

    pstMsg  = (NAS_MSCC_MSCC_ABORT_FSM_REQ_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                                               sizeof(NAS_MSCC_MSCC_ABORT_FSM_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* Construct the internal message */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->enMsgId                     = ID_NAS_MSCC_MSCC_ABORT_FSM_REQ;
    pstMsg->ulLength                    = sizeof(NAS_MSCC_MSCC_ABORT_FSM_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    NAS_MSCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
Function Name   :   NAS_MSCC_SndInternalSysAcqReq
Description     :   Funcion is used to send internal system acquire reqeust message in MSCC.
Input parameters:   None
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
    2)  Date    :   2015-12-30
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE新增搜索类型
*****************************************************************************/
VOS_VOID NAS_MSCC_SndInternalSysAcqReq(
    NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene,
    NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM_UINT32               enLteSrchType
)
{
    NAS_MSCC_MSCC_SYS_ACQ_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg  = (NAS_MSCC_MSCC_SYS_ACQ_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                                         sizeof(NAS_MSCC_MSCC_SYS_ACQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* Construct the internal message */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->enMsgId                     = ID_NAS_MSCC_MSCC_SYS_ACQ_REQ;
    pstMsg->ulLength                    = sizeof(NAS_MSCC_MSCC_SYS_ACQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enSysAcqScene               = enSysAcqScene;

    pstMsg->enLteSrchType               = enLteSrchType;

    NAS_MSCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

}


VOS_VOID NAS_MSCC_SndInternalSysAcqRsltCnf(
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enRslt,
    VOS_UINT8                                               ucSearchLteFlag,
    VOS_UINT8                                               ucSearchHrpdFlag
)
{
    NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU                    *pstMsg = VOS_NULL_PTR;

    pstMsg  = (NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                                                  sizeof(NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* Construct the internal message */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->enMsgId                     = ID_NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF;
    pstMsg->ulLength                    = sizeof(NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enRslt                      = enRslt;

    pstMsg->ucSearchLteFlag             = ucSearchLteFlag;
    pstMsg->ucSearchHrpdFlag            = ucSearchHrpdFlag;

    NAS_MSCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

}



VOS_VOID NAS_MSCC_SndBsrResult(
    NAS_MSCC_BSR_RESULT_ENUM_UINT16     enBsrRslt,
    NAS_MSCC_BSR_ACQ_SYS_ENUM_UINT8     enIsNeedAcqSys,
    NAS_MSCC_BSR_RETRY_TIMER_ENUM_UINT8 enIsNeedStartRetryTimer
)
{
    NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg  = (NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                                             sizeof(NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU));

    /* Construct the internal message */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->enMsgId                     = ID_NAS_MSCC_MSCC_BSR_RSLT_CNF;
    pstMsg->ulLength                    = sizeof(NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enRslt                      = enBsrRslt;
    pstMsg->enIsNeedAcqSys              = enIsNeedAcqSys;
    pstMsg->enIsNeedStartRetryTimer     = enIsNeedStartRetryTimer;

    NAS_MSCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)


VOS_VOID NAS_MSCC_SndCLInterSysRsltCnf(
    NAS_MSCC_CL_INTERSYS_RESULT_ENUM_UINT32                 enCLInterSysRslt
)
{
    NAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg  = (NAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                                             sizeof(NAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF_STRU));

    /* Construct the internal message */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_MSCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_MSCC;
    pstMsg->enMsgId                     = ID_NAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF;
    pstMsg->ulLength                    = sizeof(NAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enRslt                      = enCLInterSysRslt;

    NAS_MSCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}
#endif

/*lint -restore*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




