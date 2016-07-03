

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "AtRabmInterface.h"
#include "NasRabmFastdorm.h"
#include "NasRabmMain.h"
#include "rabmdef.h"
#include "NasMmlCtx.h"
#include "TafNvInterface.h"
#include "NasComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_RABM_FASTDORM_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

NAS_RABM_FASTDORM_CTX_STRU              g_stNasRabmFastDormCtx;

/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_VOID NAS_RABM_RcvAtFastDormStartReq(
    AT_RABM_SET_FASTDORM_PARA_REQ_STRU *pstFastDormPara
)
{
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* 获取当前所处网络 */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();

    /* 设置FD激活标志 */
    NAS_RABM_SET_FD_ACT_FLG(VOS_TRUE);

    /* 由于FAST DORMANCY为W下特性，如果在W网络下，且存在PDP实体激活，则需要维护FD状态 */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrentSysMode)
    {
        if (NAS_RABM_FASTDORM_INIT == NAS_RABM_GET_FD_STATUS())
        {
            /* 根据PDP RAB状态切换FD状态 */
            if (VOS_TRUE == NAS_RABM_CheckPdpRbStatus())
            {
                NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_DETECT);
                /* FD数据计数器清零 */
                NAS_RABM_CLR_FD_ULDATA_CNT();
                NAS_RABM_CLR_FD_DLDATA_CNT();
                /* 无流量时长计数清0 */
                NAS_RABM_SET_FD_CURR_NOFLUX_CNT(0);

                /* 启动周期性流量检测定时器 */
                NAS_RabmStartTimer( RABM_TIMER_NAME_FD_FLUX_DETECT, RABM_TIMER_FASTDORM_FLUX_DETECT );
            }
        }
    }

    /* 回复给AT ID_RABM_AT_FASTDORM_START_CNF */
    NAS_RABM_SndAtSetFastDormParaCnf(pstFastDormPara->usClientId,
                                     pstFastDormPara->ucOpId,
                                     AT_RABM_PARA_SET_RSLT_SUCC);

    NAS_RABM_SndOmFastdormStatus();
}



VOS_VOID NAS_RABM_RcvAtFastDormStopReq(
    AT_RABM_SET_FASTDORM_PARA_REQ_STRU *pstFastDormPara
)
{
    if (VOS_TRUE == NAS_RABM_GET_FD_ACT_FLG())
    {
        /* 还原fd的工作过程中使用的各种变量和定时器 */
        NAS_RABM_RevertFastDormEnv();

        /* 设置为FD功能没有激活 */
        NAS_RABM_SET_FD_ACT_FLG(VOS_FALSE);
        NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_INIT);

        NAS_RABM_SndOmFastdormStatus();
    }

    /* 回复给AT ID_RABM_AT_SET_FASTDORM_PARA_CNF */
    NAS_RABM_SndAtSetFastDormParaCnf(pstFastDormPara->usClientId,
                                     pstFastDormPara->ucOpId,
                                     AT_RABM_PARA_SET_RSLT_SUCC);

    return;
}


VOS_VOID NAS_RABM_RcvSetFastDormParaReq(
    AT_RABM_SET_FASTDORM_PARA_REQ_STRU *pstFastDormPara
)
{
    /*lint -e958 */
    NAS_RABM_NVIM_FASTDORM_ENABLE_FLG_STRU                  stEnableFlg;
    VOS_UINT32                                              ulLength;

    ulLength                 = 0;
    stEnableFlg.ucEnableFlag = VOS_FALSE;

    /* 读NV失败，认为不允许Fastdormancy */
    (VOS_VOID)NV_GetLength(en_NV_Item_Fastdorm_Enable_Flag, &ulLength);

    if (NV_OK != NV_Read(en_NV_Item_Fastdorm_Enable_Flag, &stEnableFlg,
                          ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_RABM_RcvSetFastDormParaReq:WARNING:NV_Read faild!");
    }

    /* 不允许Fastdormancy */
    if (VOS_FALSE == stEnableFlg.ucEnableFlag)
    {
        /* 回复给AT ID_RABM_AT_FASTDORM_START_CNF */
        NAS_RABM_SndAtSetFastDormParaCnf(pstFastDormPara->usClientId,
                                         pstFastDormPara->ucOpId,
                                         AT_RABM_PARA_SET_RSLT_FAIL);

        return;
    }

    /* 保存用户设置的参数 */
    NAS_RABM_SET_FD_OPERATION_TYPE(pstFastDormPara->stFastDormPara.enFastDormOperationType);
    NAS_RABM_SET_FD_USER_DEF_NOFLUX_CNT(pstFastDormPara->stFastDormPara.ulTimeLen);

    if (AT_RABM_FASTDORM_STOP_FD_ASCR == pstFastDormPara->stFastDormPara.enFastDormOperationType)
    {
        /* 调用函数，停止FAST DORMANCY */
        NAS_RABM_RcvAtFastDormStopReq(pstFastDormPara);
    }
    else
    {
        /* 调用函数 启动或者设置FAST DORMANCY */
        NAS_RABM_RcvAtFastDormStartReq(pstFastDormPara);
    }
    /*lint +e958 */
}


VOS_VOID NAS_RABM_RcvGetFastDormParaReq(
    AT_RABM_QRY_FASTDORM_PARA_REQ_STRU *pstFastDormPara
)
{
    /*lint -e958 */
    NAS_RABM_NVIM_FASTDORM_ENABLE_FLG_STRU                  stEnableFlag;
    VOS_UINT32                                              ulLength;

    ulLength                  = 0;
    stEnableFlag.ucEnableFlag = VOS_FALSE;

    /* 读NV失败，认为不允许Fastdormancy */
    (VOS_VOID)NV_GetLength(en_NV_Item_Fastdorm_Enable_Flag, &ulLength);

    if (NV_OK != NV_Read(en_NV_Item_Fastdorm_Enable_Flag, &stEnableFlag,
                          ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_RABM_RcvGetFastDormParaReq:WARNING:NV_Read faild!");
    }

    /* 回复查询结果 */
    NAS_RABM_SndAtQryFastDormParaCnf(pstFastDormPara->usClientId,
                                     pstFastDormPara->ucOpId,
                                     stEnableFlag.ucEnableFlag);

    /*lint +e958 */
}


VOS_VOID NAS_RABM_SysModeChgProcFastDorm(
    GMM_RABM_NET_RAT_ENUM_UINT32        enOldSysMode,
    GMM_RABM_NET_RAT_ENUM_UINT32        enNewSysMode
)
{
    /* 系统变化，判定如果当前从W模到其他模，挂起FAST DORMANCY */
    if ( (NAS_MML_NET_RAT_TYPE_WCDMA == enOldSysMode)
      && (NAS_MML_NET_RAT_TYPE_WCDMA != enNewSysMode)
      && (NAS_MML_NET_RAT_TYPE_BUTT != enNewSysMode))
    {
        NAS_RABM_SuspendFastDorm();
    }

    /* 系统变化，判定如果当前从其他模到W模，恢复FAST DORMANCY */
    if ( (NAS_MML_NET_RAT_TYPE_WCDMA != enOldSysMode)
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enNewSysMode) )
    {
        NAS_RABM_ResumeFastDorm();
    }

}


VOS_VOID NAS_RABM_SuspendFastDorm(VOS_VOID)
{
    /* 如果当前FD功能没有激活则不处理 */
    if (VOS_TRUE != NAS_RABM_GET_FD_ACT_FLG())
    {
        return;
    }

    /* 还原fd的工作过程中使用的各种变量和定时器 */
    NAS_RABM_RevertFastDormEnv();

    /* 设置为NAS_RABM_FASTDORM_INIT状态 */
    NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_INIT);
    NAS_RABM_SndOmFastdormStatus();

    return;
}


VOS_VOID NAS_RABM_ResumeFastDorm(VOS_VOID)
{
    /* 如果当前FD功能没有激活则不处理 */
    if (VOS_TRUE != NAS_RABM_GET_FD_ACT_FLG())
    {
        return;
    }

    NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_INIT);

    /* 根据PDP RB状态切换FD状态 */
    if (VOS_TRUE == NAS_RABM_CheckPdpRbStatus())
    {
        NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_DETECT);
        /* FD数据计数器清零 */
        NAS_RABM_CLR_FD_ULDATA_CNT();
        NAS_RABM_CLR_FD_DLDATA_CNT();

        /* 启动周期性流量检测定时器 */
        NAS_RabmStartTimer( RABM_TIMER_NAME_FD_FLUX_DETECT, RABM_TIMER_FASTDORM_FLUX_DETECT );
    }

    return;
}


VOS_UINT8 NAS_RABM_CheckPdpRbStatus(VOS_VOID)
{
    VOS_UINT8                               ucEntId;

    for ( ucEntId = 0; ucEntId < RABM_PS_MAX_ENT_NUM; ucEntId++ )
    {
        if (g_aRabmPsEnt[ucEntId].ucState == RABM_NSAPI_ACTIVE_WITH_RAB)
        {
            break;
        }
    }

    if (ucEntId >= RABM_PS_MAX_ENT_NUM)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT8 NAS_RABM_CheckGmmAndRabmStatus(
    GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU    *pstProcStatus
)
{
    VOS_UINT8                               ucEntId;

    /* 检查GMM的状态 若存在短信、cs域信令面或者其他特殊的gmm流程，则不能发起FD*/
    if ( (VOS_TRUE == pstProcStatus->stMmlProcStatus.bitOpGmmSpecificProcedure)
      || (VOS_TRUE == pstProcStatus->stMmlProcStatus.bitOpPsSmsService)
      || (VOS_TRUE == pstProcStatus->stMmlProcStatus.bitOpCsSignal) )
    {
        return VOS_FALSE;
    }

    /* 检查各PDP实体状态，只要存在pdp实体在做pdp激活或rb重建，则不能发起FD */
    for ( ucEntId = 0; ucEntId < RABM_PS_MAX_ENT_NUM; ucEntId++ )
    {
        if ((g_aRabmPsEnt[ucEntId].ucState == RABM_NSAPI_ACTIVE_PENDING)
         || (NAS_RABM_GetWPsEntRabReestFlg(ucEntId) == VOS_TRUE))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


VOS_VOID NAS_RABM_ConvertAtFasTDormTypeToWrrFasTDormType(
    AT_RABM_FASTDORM_OPERATION_ENUM_UINT32                enAtFastDormType,
    RRC_FASTDORM_START_TYPE_ENUM_UINT32                 *penWrrFastDormType
)
{
    switch(enAtFastDormType)
    {
        case AT_RABM_FASTDORM_START_FD_ONLY:
            *penWrrFastDormType = RRC_FASTDORM_START_TYPE_FD;
            break;

        case AT_RABM_FASTDORM_START_ASCR_ONLY:
            *penWrrFastDormType = RRC_FASTDORM_START_TYPE_ASCR;
            break;

        case AT_RABM_FASTDORM_START_FD_ASCR:
            *penWrrFastDormType = RRC_FASTDORM_START_TYPE_FD_ASCR;
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_RABM,
                        "NAS_RABM_ConvertAtFasTDormTypeToWrrFasTDormType: Wrong Type.");

            break;

    }
}


VOS_VOID NAS_RABM_RcvWasFastDormInfoInd(
    struct MsgCB                       *pMsg
)
{
    RRRABM_FASTDORM_INFO_IND_STRU      *pstInfoInd;

    pstInfoInd = (RRRABM_FASTDORM_INFO_IND_STRU*)pMsg;

    if (NAS_RABM_FASTDORM_EXEC == NAS_RABM_GET_FD_STATUS())
    {
        if (RRRABM_FASTDORM_INFO_NEED_RETRY == pstInfoInd->enInfoType)
        {
            /* 启动RABM_TIMER_FASTDORM_RETRY定时器 */
            NAS_RabmStartTimer( RABM_TIMER_NAME_FD_RETRY, RABM_TIMER_FASTDORM_RETRY );
            NAS_RABM_SndOmFastdormStatus();
        }
        else
        {
            /* 设置FD在NAS_RABM_FASTDORM_INIT状态 */;
            NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_INIT);
            NAS_RABM_SndOmFastdormStatus();
        }

        return;
    }

    /* 存在FD切换到INIT状态后，wrr又回复retry消息 */
    if ((NAS_RABM_FASTDORM_INIT == NAS_RABM_GET_FD_STATUS())
     && (VOS_TRUE == NAS_RABM_GET_FD_ACT_FLG())
     && (RRRABM_FASTDORM_INFO_NEED_RETRY == pstInfoInd->enInfoType))
    {
        /* 设置FD在NAS_RABM_FASTDORM_EXEC状态 */;
        NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_EXEC);
        NAS_RABM_SndOmFastdormStatus();

        /* 启动RABM_TIMER_FASTDORM_RETRY定时器 */
        NAS_RabmStartTimer( RABM_TIMER_NAME_FD_RETRY, RABM_TIMER_FASTDORM_RETRY );
    }

    return;
}


VOS_VOID NAS_RABM_ProcFastDormStatusInTransfer( VOS_VOID )
{
    if (VOS_TRUE == NAS_RABM_GET_FD_ACT_FLG())
    {
        if (NAS_RABM_FASTDORM_DETECT != NAS_RABM_GET_FD_STATUS())
        {
            /* 还原fd的工作过程中使用的各种变量和定时器 */
            NAS_RABM_RevertFastDormEnv();

            /* 设置为NAS_RABM_FASTDORM_DETECT状态 */
            NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_DETECT);
            NAS_RabmStartTimer(RABM_TIMER_NAME_FD_FLUX_DETECT,RABM_TIMER_FASTDORM_FLUX_DETECT);

            NAS_RABM_SndOmFastdormStatus();
        }
    }

    return;
}


VOS_VOID NAS_RABM_RevertFastDormEnv(VOS_VOID)
{
    /* 向WAS发送RRRABM_FASTDORM_STOP_REQ */
    NAS_RABM_SndWasFastDormStopReq();

    /* 停止定时器RABM_TIMER_FASTDORM_FLUX_DETECT */
    /* 停止定时器RABM_TIMER_FASTDORM_RETRY */
    /* 停止定时器RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT*/
    NAS_RabmStopTimer(RABM_TIMER_NAME_FD_FLUX_DETECT,RABM_TIMER_FASTDORM_FLUX_DETECT);
    NAS_RabmStopTimer(RABM_TIMER_NAME_FD_RETRY,RABM_TIMER_FASTDORM_RETRY);
    NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON,RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT);

    /* 清空上下行流量数据 */
    NAS_RABM_CLR_FD_ULDATA_CNT();
    NAS_RABM_CLR_FD_DLDATA_CNT();

    /* 无流量时长计数清0 */
    NAS_RABM_SET_FD_CURR_NOFLUX_CNT(0);

    /* 清除释放RRC标识 */
    NAS_RABM_CLR_FD_REL_RRC_EXEC_FLG();

    return;
}


VOS_VOID NAS_RABM_AbortRelRrcProcedure(VOS_VOID)
{
    /* FD功能开启时, 以FD的处理流程为准 */
    if (VOS_TRUE == NAS_RABM_GET_FD_ACT_FLG())
    {
        return;
    }

    if (VOS_TRUE == NAS_RABM_GET_FD_REL_RRC_EXEC_FLG())
    {
        NAS_RABM_CLR_FD_REL_RRC_EXEC_FLG();
        NAS_RABM_SndWasFastDormStopReq();
    }

    return;
}


VOS_VOID NAS_RABM_RcvReleaseRrcReq(
    AT_RABM_RELEASE_RRC_REQ_STRU *pstMsg
)
{
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* 获取当前所处网络 */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();

    /* 如果不在W网络下，则不能释放RRC连接 */
    if (NAS_MML_NET_RAT_TYPE_WCDMA != enCurrentSysMode)
    {
        NAS_RABM_SndAtReleaseRrcCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR);
    }
    else
    {
        /* 直接回复rrc释放成功 */
        NAS_RABM_SndAtReleaseRrcCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_OK);

        /* 向GMM发送查询消息 */
        NAS_RABM_SndGmmMmlProcStatusQryReq(RABM_RELEASE_RRC_ENUM);

    }

    return;
}


VOS_VOID NAS_RABM_InitFastDormCtx(VOS_VOID)
{
    g_stNasRabmFastDormCtx.enCurrFastDormStatus    = NAS_RABM_FASTDORM_INIT;
    g_stNasRabmFastDormCtx.ulCurrNoFluxCnt         = 0;
    g_stNasRabmFastDormCtx.enFastDormOperationType = AT_RABM_FASTDORM_STOP_FD_ASCR;
    g_stNasRabmFastDormCtx.ulUserDefNoFluxCnt      = 0;

    g_stNasRabmFastDormCtx.ulDlDataCnt             = 0;
    g_stNasRabmFastDormCtx.ulUlDataCnt             = 0;

    g_stNasRabmFastDormCtx.ulRelRrcExecFlg         = VOS_FALSE;

    g_stNasRabmFastDormCtx.ulActiveFlg             = VOS_FALSE; /* 默认FD功能没有激活 */

    g_ulNasRabmFDFluxDetectTimer                   = NAS_RABM_TIMER_STATUS_STOP;
    g_ulNasRabmFDRetryTimer                        = NAS_RABM_TIMER_STATUS_STOP;
    g_ulNasRabmFDWaitGmmQryRsltTimer               = NAS_RABM_TIMER_STATUS_STOP;
}


VOS_VOID NAS_RABM_FastDormFluxDetectExpired(VOS_VOID)
{
    VOS_UINT32                              ulUserDefNoFluxCnt;
    VOS_UINT32                              ulCurrNoFluxCnt;
    VOS_UINT32                              ulUlDataCnt;
    VOS_UINT32                              ulDlDataCnt;

    if (NAS_RABM_FASTDORM_DETECT == NAS_RABM_GET_FD_STATUS())
    {
        ulUlDataCnt = NAS_RABM_GET_FD_ULDATA_CNT();
        ulDlDataCnt = NAS_RABM_GET_FD_DLDATA_CNT();

        /* 存在数据传输时清空无流量时长，继续等待流量统计定时器超时 */
        if ((ulUlDataCnt > 0) || (ulDlDataCnt > 0))
        {
            /*流量计数清零*/
            NAS_RABM_CLR_FD_ULDATA_CNT();
            NAS_RABM_CLR_FD_DLDATA_CNT();
            /* 无流量时长计数值清0 */
            NAS_RABM_SET_FD_CURR_NOFLUX_CNT(0);

            return;
        }

        ulUserDefNoFluxCnt = NAS_RABM_GET_FD_USER_DEF_NOFLUX_CNT();
        ulCurrNoFluxCnt    = NAS_RABM_GET_FD_CURR_NOFLUX_CNT();

        ulCurrNoFluxCnt += 1;

        /* 无流量时长达到用户设置的无流量时长，切换FD状态为NAS_RABM_FASTDORM_EXEC，停止流量统计定时器 */
        if (ulCurrNoFluxCnt >= ulUserDefNoFluxCnt)
        {
            NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_EXEC);
            NAS_RabmStopTimer(RABM_TIMER_NAME_FD_FLUX_DETECT,RABM_TIMER_FASTDORM_FLUX_DETECT);

            NAS_RABM_CLR_FD_ULDATA_CNT();
            NAS_RABM_CLR_FD_DLDATA_CNT();

            NAS_RABM_SET_FD_CURR_NOFLUX_CNT(0);

            /* 向GMM发送查询消息 */
            NAS_RABM_SndGmmMmlProcStatusQryReq(RABM_FASTDORM_ENUM);

            /* 启动定时器TI_NAS_RABM_FASTDORM_WAIT_GMM_QRY_RESULT */
            NAS_RabmStartTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT );
            NAS_RABM_SndOmFastdormStatus();

            return;
        }

        /* 存储当前的无流量计数值 */
        NAS_RABM_SET_FD_CURR_NOFLUX_CNT(ulCurrNoFluxCnt);
    }

    return;

}


VOS_VOID NAS_RABM_FastDormRetryExpired(VOS_VOID)
{
    /* 把retry定时器的状态设置为stop */
    g_ulNasRabmFDRetryTimer = NAS_RABM_TIMER_STATUS_STOP;

    if (NAS_RABM_FASTDORM_EXEC == NAS_RABM_GET_FD_STATUS())
    {
        /* 向GMM发送查询消息 */
        NAS_RABM_SndGmmMmlProcStatusQryReq(RABM_FASTDORM_ENUM);
        /* 启动定时器RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT */
        NAS_RabmStartTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT );

        NAS_RABM_SndOmFastdormStatus();
    }

    return;
}


VOS_VOID NAS_RABM_FastDormWaitGmmProcQryRsltExpired(VOS_VOID)
{
    /* 把定时器状态置为stop */
    g_ulNasRabmFDWaitGmmQryRsltTimer = NAS_RABM_TIMER_STATUS_STOP;

    if (NAS_RABM_FASTDORM_EXEC == NAS_RABM_GET_FD_STATUS())
    {
        /* 设置FD功能没有激活 */
        NAS_RABM_RevertFastDormEnv();
        NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_INIT);

        NAS_RABM_SndOmFastdormStatus();
    }

    return;
}


VOS_VOID NAS_RABM_RcvGmmFastDormMmlProcStatusQryCnf(
    struct MsgCB                       *pstMsg
)
{
    GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU    *pstProcStatus;

    pstProcStatus = (GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU*)pstMsg;

    NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT );

    if (NAS_RABM_FASTDORM_EXEC == NAS_RABM_GET_FD_STATUS())
    {
        /*if (当前可以给WAS发送FAST DORM)*/
        if (VOS_TRUE == NAS_RABM_CheckGmmAndRabmStatus(pstProcStatus))
        {
            /* 向WAS发送RRRABM_FASTDORM_START_REQ */
            NAS_RABM_SndWasFastDormStartReq(RABM_FASTDORM_ENUM);
        }
        else
        {
            /* 启动定时器RABM_TIMER_FASTDORM_RETRY */
            NAS_RabmStartTimer( RABM_TIMER_NAME_FD_RETRY, RABM_TIMER_FASTDORM_RETRY );
        }
    }

    NAS_RABM_SndOmFastdormStatus();
    return;
}


VOS_VOID NAS_RABM_RcvGmmMmlProcStatusQryCnf(
    struct MsgCB                       *pstMsg
)
{
    GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU    *pstProcStatus;

    pstProcStatus = (GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU*)pstMsg;

    if (RABM_RELEASE_RRC_ENUM == pstProcStatus->stMmlProcStatus.enOptFlag)
    {
        NAS_RABM_RcvGmmReleaseRrcMmlProcStatusQryCnf(pstMsg);
    }

    if (RABM_FASTDORM_ENUM == pstProcStatus->stMmlProcStatus.enOptFlag)
    {
        NAS_RABM_RcvGmmFastDormMmlProcStatusQryCnf(pstMsg);
    }

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
    if (RABM_VOICEPREFER_ENUM == pstProcStatus->stMmlProcStatus.enOptFlag)
    {
        NAS_RABM_RcvGmmVoicePreferMmlProcStatusQryCnf(pstMsg);
    }
#endif

    return;
}


VOS_VOID NAS_RABM_RcvGmmReleaseRrcMmlProcStatusQryCnf(
    struct MsgCB                       *pstMsg
)
{
    GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU    *pstProcStatus;

    pstProcStatus = (GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU*)pstMsg;

    if (VOS_TRUE == NAS_RABM_CheckGmmAndRabmStatus(pstProcStatus))
    {
        /* 设置释放RRC标识 */
        NAS_RABM_SET_FD_REL_RRC_EXEC_FLG();

        /* 向WAS发送RRRABM_FASTDORM_START_REQ */
        NAS_RABM_SndWasFastDormStartReq(RABM_RELEASE_RRC_ENUM);
    }

    return;
}


VOS_VOID NAS_RABM_SndWasFastDormStartReq(
    RABM_RELRRC_OPERATE_ENUM_UINT32     enOptFlag
)
{
    VOS_UINT32                              ulRet;                              /* 定义调用VOS发送函数的返回值 */
    RRRABM_FASTDORM_START_REQ_STRU         *pstMsg = VOS_NULL_PTR;              /* 定义原语类型指针 */
    RRC_FASTDORM_START_TYPE_ENUM_UINT32     enWrrFastDormStartType;


    enWrrFastDormStartType = RRC_FASTDORM_START_TYPE_BUTT;


    /* 申请内存  */
    pstMsg = (RRRABM_FASTDORM_START_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RRRABM_FASTDORM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* 内存申请失败 */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndWasFastDormStartReq:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* 填写相关参数 */
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_WRR;
    pstMsg->MsgHeader.ulLength          = sizeof(RRRABM_FASTDORM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = RRRABM_FASTDORM_START_REQ;

    /* 将AT的操作类型转换成Wrr对应的操作类型 */
    if (RABM_FASTDORM_ENUM == enOptFlag)
    {
        NAS_RABM_ConvertAtFasTDormTypeToWrrFasTDormType(NAS_RABM_GET_FD_OPERATION_TYPE(),
                                                        &enWrrFastDormStartType);
    }
    else
    {
        /* release rrc 命令同时开启FD和ASCR */
        NAS_RABM_ConvertAtFasTDormTypeToWrrFasTDormType(AT_RABM_FASTDORM_START_FD_ASCR,
                                                        &enWrrFastDormStartType);
    }

    pstMsg->enStartType                 = enWrrFastDormStartType;

    /* 调用VOS发送原语 */
     ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_RABM, (struct MsgCB **)&pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndWasFastDormStartReq:ERROR:PS_SEND_MSG ");
        return ;
    }

}



VOS_VOID NAS_RABM_SndWasFastDormStopReq(VOS_VOID)
{
    VOS_UINT32                          ulRet;                                  /* 定义调用VOS发送函数的返回值 */
    RRRABM_FASTDORM_STOP_REQ_STRU     *pstMsg = VOS_NULL_PTR;                  /* 定义原语类型指针 */

    /* 申请内存  */
    pstMsg = (RRRABM_FASTDORM_STOP_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RRRABM_FASTDORM_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* 内存申请失败 */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndWasFastDormStopReq:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* 填写相关参数 */
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_WRR;
    pstMsg->MsgHeader.ulLength          = sizeof(RRRABM_FASTDORM_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = RRRABM_FASTDORM_STOP_REQ;

    /* 调用VOS发送原语 */
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_RABM, (struct MsgCB **)&pstMsg);

    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndWasFastDormStopReq:ERROR:PS_SEND_MSG ");
        return ;
    }

}



VOS_VOID NAS_RABM_SndGmmMmlProcStatusQryReq(
    RABM_RELRRC_OPERATE_ENUM_UINT32     enOptFlag
)
{
    VOS_UINT32                                  ulRet;                                  /* 定义调用VOS发送函数的返回值 */
    RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU      *pstMsg = VOS_NULL_PTR;                  /* 定义原语类型指针 */

    /* 申请内存  */
    pstMsg = (RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* 内存申请失败 */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndGmmMmlProcStatusQryReq:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* 填写相关参数 */
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulLength          = sizeof(RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = ID_RABM_GMM_MML_PROC_STATUS_QRY_REQ;

    pstMsg->enOptFlag                     = enOptFlag;

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG(WUEPS_PID_RABM, pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndGmmMmlProcStatusQryReq:ERROR:PS_SEND_MSG ");
        return ;
    }

}

/*lint -e958 */

VOS_VOID NAS_RABM_SndAtSetFastDormParaCnf(
    MN_CLIENT_ID_T                      usClientId,                             /* AT发消息给RABM所带的ClientId */
    MN_OPERATION_ID_T                   ucOpId,                                 /* AT发消息给RABM所带的OpId */
    AT_RABM_PARA_SET_RSLT_ENUM_UINT32   enRslt
)
{
    /* 向AT发送设置结果 */
    VOS_UINT32                          ulRet;                                  /* 定义调用VOS发送函数的返回值 */
    RABM_AT_SET_FASTDORM_PARA_CNF_STRU *pstMsg = VOS_NULL_PTR;                  /* 定义原语类型指针 */

    /* 申请内存  */
    pstMsg = (RABM_AT_SET_FASTDORM_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RABM_AT_SET_FASTDORM_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* 内存申请失败 */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtSetFastDormParaCnf:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* 填写相关参数 */
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_AT;
    pstMsg->stMsgHeader.ulLength          = sizeof(RABM_AT_SET_FASTDORM_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = ID_RABM_AT_SET_FASTDORM_PARA_CNF;
    pstMsg->enRslt                        = enRslt;
    pstMsg->usClientId                    = usClientId;
    pstMsg->ucOpId                        = ucOpId;

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG(WUEPS_PID_RABM, pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtSetFastDormParaCnf:ERROR:PS_SEND_MSG ");
        return ;
    }

    return ;
}
/*lint +e958 */


VOS_VOID NAS_RABM_SndAtQryFastDormParaCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT8                           ucRslt
)
{
    /* 向AT发送查询结果 */
    VOS_UINT32                          ulRet;                                  /* 定义调用VOS发送函数的返回值 */
    RABM_AT_QRY_FASTDORM_PARA_CNF_STRU *pstMsg = VOS_NULL_PTR;                  /* 定义原语类型指针 */

    /* 申请内存  */
    pstMsg = (RABM_AT_QRY_FASTDORM_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RABM_AT_QRY_FASTDORM_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* 内存申请失败 */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtQryFastDormParaCnf:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* 填写相关参数 */
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_AT;
    pstMsg->stMsgHeader.ulLength          = sizeof(RABM_AT_QRY_FASTDORM_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = ID_RABM_AT_QRY_FASTDORM_PARA_CNF;
    pstMsg->usClientId                    = usClientId;
    pstMsg->ucOpId                        = ucOpId;
    pstMsg->ucRslt                        = ucRslt;

    pstMsg->stFastDormPara.enFastDormOperationType = NAS_RABM_GET_FD_OPERATION_TYPE();
    pstMsg->stFastDormPara.ulTimeLen               = NAS_RABM_GET_FD_USER_DEF_NOFLUX_CNT();

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG(WUEPS_PID_RABM, pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtQryFastDormParaCnf:ERROR:PS_SEND_MSG ");
        return ;
    }

    return ;
}



VOS_VOID  NAS_RABM_SndOmFastdormStatus(VOS_VOID)
{
    NAS_RABM_LOG_FASTDORM_INFO_STRU    *pstMsg;

    pstMsg = (NAS_RABM_LOG_FASTDORM_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_RABM,
                             sizeof(NAS_RABM_LOG_FASTDORM_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_RABM_SndOmFastdormStatus:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId           = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid               = WUEPS_PID_RABM;
    pstMsg->stMsgHeader.ulReceiverPid             = WUEPS_PID_RABM;

    pstMsg->stMsgHeader.ulLength                  = sizeof(NAS_RABM_LOG_FASTDORM_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName                 = NAS_RABM_OM_MSG_FASTDORM_STATUS;
    pstMsg->stFastDormCtx.enCurrFastDormStatus    = NAS_RABM_GET_FD_STATUS();
    pstMsg->stFastDormCtx.enFastDormOperationType = NAS_RABM_GET_FD_OPERATION_TYPE();
    pstMsg->stFastDormCtx.ulUserDefNoFluxCnt      = NAS_RABM_GET_FD_USER_DEF_NOFLUX_CNT();
    pstMsg->stFastDormCtx.ulCurrNoFluxCnt         = NAS_RABM_GET_FD_CURR_NOFLUX_CNT();

    pstMsg->stFastDormCtx.ulActiveFlg             = NAS_RABM_GET_FD_ACT_FLG();
    pstMsg->stFastDormCtx.ulDlDataCnt             = NAS_RABM_GET_FD_DLDATA_CNT();
    pstMsg->stFastDormCtx.ulUlDataCnt             = NAS_RABM_GET_FD_ULDATA_CNT();

    pstMsg->aenTimerState[0]                      = NAS_RABM_CheckTimerStatus(RABM_TIMER_NAME_FD_FLUX_DETECT,RABM_TIMER_FASTDORM_FLUX_DETECT);
    pstMsg->aenTimerState[1]                      = NAS_RABM_CheckTimerStatus(RABM_TIMER_NAME_COMMON, RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT);
    pstMsg->aenTimerState[2]                      = NAS_RABM_CheckTimerStatus(RABM_TIMER_NAME_FD_RETRY,RABM_TIMER_FASTDORM_RETRY);
    pstMsg->ucReserved                            = 0;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_RABM, pstMsg);

}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

