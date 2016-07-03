

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "MnMsgInclude.h"
#include  "TafSdcCtx.h"

#include "MnMsgSendSpm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_TIMERPROC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
  2 类型定义
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId;
}MN_MSG_TIMER_HANDLE_STRU;

/* 超时处理函数的类型定义 */
typedef VOS_VOID (* MN_MSG_TIMEOUT_PROC_FUNC)(VOS_UINT32 ulParam);

/* 定时器信息结构 */
typedef struct
{
    VOS_UINT32                          ulTimeout;
    MN_MSG_TIMEOUT_PROC_FUNC            pfnTimeoutProc;
} MN_MSG_TIMER_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT32                          ulTimeLen;
}MN_MSG_TIMER_OPERATION_STRU;

LOCAL MN_CLIENT_ID_T                    g_clientId;
LOCAL MN_OPERATION_ID_T                 g_opId;
LOCAL VOS_UINT32                        g_ulLeftReportNum;
LOCAL MN_MSG_LIST_PARM_STRU             g_stList;

/*****************************************************************************
  3 函数声明
*****************************************************************************/
LOCAL VOS_VOID  MSG_GetEfCnfTimeout(
    VOS_UINT32                          ulParam
);

LOCAL VOS_VOID  MSG_LinkCtrlTimeout(
    VOS_UINT32                          ulParam
);

LOCAL VOS_VOID MSG_WaitUsimTimeout(
    VOS_UINT32                          ulParam
);

LOCAL VOS_VOID MSG_WaitRetryPeriodTimeout(
    VOS_UINT32                          ulParam
);

LOCAL VOS_VOID MSG_WaitRetryIntervalTimeout(
    VOS_UINT32                          ulParam
);


LOCAL VOS_VOID MSG_WaitFdnCheckTimeout(
    VOS_UINT32                          ulParam
);


LOCAL VOS_VOID  MSG_WaitSmsMoControlCheckTimeout(
    VOS_UINT32                          ulParam
);

/*****************************************************************************
  4 变量定义
*****************************************************************************/
/* 所有可用的定时器资源 */
MN_MSG_TIMER_HANDLE_STRU                f_astMsgTimerHandle[MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG];

/*定时器信息表，该表中记录了每种定时器的超时时间和超时处理函数 */
MN_MSG_TIMER_INFO_STRU                  f_astMsgTimerInfoTbl[MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG] = {
    {60000, MSG_GetEfCnfTimeout},
    {3500, MSG_LinkCtrlTimeout},
    {10000,MSG_WaitUsimTimeout},
    {30000,MSG_WaitRetryPeriodTimeout},
    {5000,MSG_WaitRetryIntervalTimeout},
    {5000, MSG_WaitFdnCheckTimeout},
    {5000, MSG_WaitSmsMoControlCheckTimeout},
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    {60000,  TAF_CBA_RcvTiWaitGetCbEfRspTimerExpired},
#if (FEATURE_ON == FEATURE_ETWS)
    {600000, TAF_CBA_RcvTiEtwsTempEnableCbsTimerExpired}                        /* 收到主通知时临时使能CBS的定时器 */
#endif
#endif
};

/*lint -save -e958 */

/*****************************************************************************
  5 函数实现
*****************************************************************************/

VOS_VOID MN_MSG_PrintTimerInfo(VOS_VOID)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); ulLoop++)
    {
        MN_INFO_LOG1("MN_MSG_PrintTimerInfo:Timer No           ", (VOS_INT32)ulLoop);
        MN_INFO_LOG1("MN_MSG_PrintTimerInfo:Timer handle id    ", (VOS_INT32)f_astMsgTimerHandle[ulLoop].enTimerId);
        MN_INFO_LOG1("MN_MSG_PrintTimerInfo:Timer handle hTimer", (VOS_INT32)f_astMsgTimerHandle[ulLoop].hTimer);
        MN_INFO_LOG1("MN_MSG_PrintTimerInfo:Timer Table Length ", (VOS_INT32)f_astMsgTimerInfoTbl[ulLoop].ulTimeout);
        MN_INFO_LOG1("MN_MSG_PrintTimerInfo:Timer Table handle ", (VOS_INT32)f_astMsgTimerInfoTbl[ulLoop].pfnTimeoutProc);
    }
}


VOS_VOID MSG_GetEfSmsTimerout(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    MN_MSG_USIM_EFUST_INFO_STRU         stUstInfo;
    VOS_UINT8                           ucCurrRec;
    VOS_UINT32                          ulFileId[2];

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId[0]    = USIMM_USIM_EFSMS_ID;
        ulFileId[1]    = USIMM_USIM_EFSMSR_ID;
    }
    else
    {
        ulFileId[0]    = USIMM_TELE_EFSMS_ID;
        ulFileId[1]    = USIMM_TELE_EFSMSR_ID;
    }

    PS_MEM_SET(&stUstInfo, 0, sizeof(stUstInfo));

    /*获取下一条记录*/
    ucCurrRec = MN_MSG_GetSmCurrRecFromUsim();
    if (ucCurrRec < MN_MSG_GetSmCapacity(MN_MSG_MEM_STORE_SIM))
    {
        /*lint -e961*/
        MN_MSG_SetSmCurrRecFromUsim(++ucCurrRec);
        /*lint +e961*/
        ulRet = MN_MSG_SndUsimGetFileReq((VOS_UINT16)ulFileId[0], ucCurrRec);
        if (USIMM_API_SUCCESS == ulRet)
        {
            return;
        }
    }
    else
    {
        MN_MSG_SetSmCurrRecFromUsim(0);
    }

    MN_MSG_ReadUstInfo(&stUstInfo);
    if (VOS_TRUE == stUstInfo.bEfSmsrFlag)
    {
        ulRet =  MN_MSG_SndUsimGetFileReq((VOS_UINT16)ulFileId[1], 0);;
        if (USIMM_API_SUCCESS == ulRet)
        {
            return;
        }
    }

    /*无文件需要读取,置为上电完成*/
    MN_MSG_UpdateUsimStateInfo(MN_MSG_USIM_POWER_ON);

    /*向应用上报初始化完成*/
    MN_MSG_SmInitFinish(MN_CLIENT_ALL);
}


LOCAL VOS_VOID MSG_LinkCtrlTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_MSG_LINK_CTRL_U8                 enLinkCtrl;
    MN_MSG_MO_STATE_ENUM_U8             enMoState;

    enMoState = MN_MSG_GetMoState();
    enLinkCtrl = MN_MSG_GetLinkCtrlParam();
    if ((MN_MSG_LINK_CTRL_ONEOFF_ENABLE == enLinkCtrl)
     && (MN_MSG_MO_STATE_WAIT_REPORT_IND != enMoState))
    {
        (VOS_VOID)MN_MSG_UpdateLinkCtrlParam(MN_MSG_LINK_CTRL_DISABLE);
    }

    MN_MSG_SendSmsCpAckReq();
    return;
}


LOCAL VOS_VOID MSG_WaitUsimTimeout(
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          ulRealRec;
    VOS_BOOL                            bNeedSendUsim[255];
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT32                          ulTotalNum = 0;
    VOS_BOOL                            bNeedStartTimer = VOS_FALSE;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;

    enSimType = TAF_SDC_GetSimType();

    PS_MEM_SET(bNeedSendUsim, 0, sizeof(bNeedSendUsim));

    MN_MSG_GetNeedSendUsim(&ulRealRec, bNeedSendUsim);
    for (i = 0; i < ulRealRec; i++)
    {
        if (VOS_TRUE == bNeedSendUsim[i])
        {
            PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
            ulRet = MN_MSG_ReadSmsInfo(MN_MSG_MEM_STORE_SIM,i,aucSmContent);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                MN_MSG_UpdateNeedSendUsim(i,VOS_FALSE);
                continue;
            }
            if (EF_SMS_STATUS_MT_READ != (aucSmContent[0] & 0x03))
            {
                MN_MSG_UpdateNeedSendUsim(i,VOS_FALSE);
                continue;
            }
            aucSmContent[0] = EF_SMS_STATUS_MT_READ;

            if (TAF_SDC_SIM_TYPE_SIM == enSimType)
            {
                ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMS_ID, aucSmContent, MN_MSG_EFSMS_LEN, (VOS_UINT8)(i + 1));
            }
            else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
            {
                ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMS_ID, aucSmContent, MN_MSG_EFSMS_LEN, (VOS_UINT8)(i + 1));
            }
            else
            {
                ulRet = USIMM_API_FAILED;
            }

            if (USIMM_API_SUCCESS != ulRet)
            {
                MN_WARN_LOG("MSG_WaitUsimTimeout:Add Usim Node Failed");
                bNeedStartTimer = VOS_TRUE;
                break;
            }
            ulTotalNum++;
            MN_MSG_UpdateNeedSendUsim(i,VOS_FALSE);
        }
        if (ulTotalNum >=  MN_MSG_MAX_CHG_SM_STATE_NUM)
        {
            break;
        }
    }

    if ( (i + 1) < ulRealRec)
    {
        bNeedStartTimer = VOS_TRUE;
    }

    if (VOS_TRUE == bNeedStartTimer)
    {
        MN_MSG_StartTimer(MN_MSG_TID_WAIT_USIM,0);
    }
}


LOCAL VOS_VOID  MSG_GetEfCnfTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;

    MN_MSG_GetUsimPowerState(&enPowerState);
    switch (enPowerState)
    {
        case MN_MSG_USIM_POWER_WAIT_EFSMSS:
            MN_NORM_LOG("MSG_GetEfCnfTimeout:WAIT EFSMSS");
            /*获取EFSMSP文件的内容*/
            if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
            {
                MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMSP_ID);
            }
            else
            {
                MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMSP_ID);
            }
            break;
        case MN_MSG_USIM_POWER_WAIT_EFSMSP:
            /* 上报EFSMSP文件读取完成 */
            MN_MSG_SmspInitFinish(MN_CLIENT_ALL);
            MN_NORM_LOG("MSG_GetEfCnfTimeout:WAIT EFSMSP");
            /*获取EFSMS文件的内容*/
            if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
            {
                MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMS_ID);
            }
            else
            {
                MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMS_ID);
            }
            break;
        case MN_MSG_USIM_POWER_WAIT_EFSMSREC:
            MN_NORM_LOG("MSG_GetEfCnfTimeout:WAIT EFSMSREC");
            /*获取EFSMSR文件的内容*/
            if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
            {
                MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMSR_ID);
            }
            else
            {
                MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMSR_ID);
            }
            break;
        case MN_MSG_USIM_POWER_WAIT_EFSMS:
            MN_NORM_LOG("MSG_GetEfCnfTimeout:WAIT EFSMS");
            MSG_GetEfSmsTimerout();
            break;
        case MN_MSG_USIM_POWER_WAIT_EFSMSR:
            MN_NORM_LOG("MSG_GetEfCnfTimeout:WAIT EFSMSR");
            /*上报初始化完成*/
            MN_MSG_GetUsimParmReq(USIMM_DEF_FILEID_BUTT);
            break;
        default:
            MN_WARN_LOG("MSG_GetEfCnfTimeout:Invalid enPowerState");
            break;
    }
}


LOCAL VOS_VOID MSG_WaitRetryPeriodTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_INFO_LOG("MSG_WaitRetryPeriodTimeout:RetryPeriodTimeout");
}


VOS_VOID MSG_GetRetrySendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain,
    MN_MSG_SEND_DOMAIN_ENUM_U8         *penSendDomain
)
{
    /* 此处修改:
       修改前: 只有CS域有重发功能,PS域不存在此功能
       修改后: 支持在CS域和PS域重发 */
    *penSendDomain = MN_MSG_SEND_DOMAIN_NO;

    if ((MN_MSG_SEND_DOMAIN_CS == enHopeSendDomain)
     || (MN_MSG_SEND_DOMAIN_CS_PREFERRED == enHopeSendDomain)
     || (MN_MSG_SEND_DOMAIN_PS_PREFERRED == enHopeSendDomain))
    {
        MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_CS, penSendDomain);
    }

    if (MN_MSG_SEND_DOMAIN_NO != *penSendDomain)
    {
        return;
    }

    if ((MN_MSG_SEND_DOMAIN_PS == enHopeSendDomain)
     || (MN_MSG_SEND_DOMAIN_CS_PREFERRED == enHopeSendDomain)
     || (MN_MSG_SEND_DOMAIN_PS_PREFERRED == enHopeSendDomain))
    {
        MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_PS, penSendDomain);
    }

    return;
}


LOCAL VOS_VOID MSG_WaitRetryIntervalTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    VOS_UINT32                          ulRet;
    SMR_SMT_MO_REPORT_STRU              stRpErrInfo;

    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));
    MN_MSG_GetMoEntity(&stMoEntity);

    PS_MEM_SET(&stRpErrInfo, 0, sizeof(stRpErrInfo));

    /* 当前不是发送短信过程中 */
    if (MN_MSG_MO_STATE_WAIT_REPORT_IND != stMoEntity.enSmaMoState)
    {
        MN_WARN_LOG("MSG_WaitRetryIntervalTimeout:Mo State is NULL");
        return;
    }

    MSG_GetRetrySendDomain(stMoEntity.enHopeSendDomain, &stMoEntity.enSendDomain);

    if (MN_MSG_SEND_DOMAIN_NO != stMoEntity.enSendDomain)
    {
        /* TAF层重发的SUBMIT短信TP-RD应该修改为1，指示短信中心拒绝接收重复短信 */
        MN_MSG_SetTpRd(&stMoEntity);

        /*将一条完整的RP-Data发送给NAS层的SMS模块*/
        ulRet = MN_MSG_SendSmsRpDataReq(stMoEntity.enSendDomain,
                                        stMoEntity.aucRpDataInfo,
                                        stMoEntity.ucRpDataLen,
                                        stMoEntity.enMsgSignallingType);        
        
        if (VOS_OK == ulRet)
        {
            /* 更新MO变量 */
            MN_MSG_CreateMoInfo(&stMoEntity);
            return;
        }

    }

    /* 上报发送短信失败 */
    MN_MSG_GetRpErrInfo(&stRpErrInfo);
    MN_MSG_RcvSmsRpRpt(&stRpErrInfo);

    /*  还需要停止定时器 */
    MN_MSG_StopTimer(MN_MSG_ID_WAIT_RETRY_PERIOD);
}


LOCAL VOS_VOID MSG_WaitFdnCheckTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulIndex;
    VOS_BOOL                            bBufferEntity;

    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));
    /* 获取等待FDN检查结果的MO实体或缓存 */
    ulRet = MN_MSG_GetSpecificStatusMoEntity(MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP,
                                             &bBufferEntity,
                                             &ulIndex,
                                             &stMoEntity);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_WaitSmsMoControlCheckTimeout: discard SMS MO CONTROL RESPONSE.");
        return;
    }

    /* MO状态不匹配: 没有等待SMS MO CONTROL RESPONSE消息 */
    if (MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP != stMoEntity.enSmaMoState)
    {
        MN_WARN_LOG("MSG_WaitFdnCheckTimeout: Mo State is invalid.");
        return;
    }

    /*
    等待USIM模块的FDN消息超时:
            通知APP短信发送请求被拒绝；
            释放短信发送实体；
    */
    MN_WARN_LOG("MSG_WaitFdnCheckTimeout: wait for FDN check response timeout.");
    MN_SendClientResponse(stMoEntity.clientId,
                          stMoEntity.opId,
                          MN_ERR_CLASS_SMS_INTERNAL);

    /* 销毁等待FDN检查结果的MO实体或缓存 */
    MN_MSG_DestroySpecificMoEntity(bBufferEntity, ulIndex);

    /* 通知SPM检查结果 */
    TAF_MSG_SendSpmMsgCheckResultInd(stMoEntity.clientId, stMoEntity.opId,TAF_MSG_ERROR_FDN_CHECK_TIMEROUT);

    return;

}


VOS_VOID  MN_MSG_InitAllTimers(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i=0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
        f_astMsgTimerHandle[i].hTimer = VOS_NULL_PTR;
        f_astMsgTimerHandle[i].enTimerId = MN_MSG_TID_MAX;
    }
}


VOS_VOID  MN_MSG_StartTimer(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId,
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;

    if (enTimerId >= MN_MSG_TID_MAX)
    {
        MN_WARN_LOG("MN_MSG_StartTimer: Invalid enTimerId. ");
        return;
    }

    /* 寻找空闲的定时器句柄 */
    for (i=0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
        if (VOS_NULL_PTR == f_astMsgTimerHandle[i].hTimer)
        {
            break;
        }
    }

    if (i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG))
    {
        /* 启动VOS定时器 */
        ulRet = NAS_StartRelTimer(&f_astMsgTimerHandle[i].hTimer,
                                  WUEPS_PID_TAF,
                                  f_astMsgTimerInfoTbl[enTimerId - MN_TIMER_CLASS_MSG].ulTimeout,
                                  (VOS_UINT32)enTimerId,
                                  ulParam,
                                  VOS_RELTIMER_NOLOOP);
        if (VOS_OK == ulRet)
        {
            /* 记录超时处理函数 */
            f_astMsgTimerHandle[i].enTimerId = enTimerId;
        }
        else
        {
            MN_WARN_LOG("MN_MSG_StartTimer: VOS_StartRelTimer failed.");
        }
    }
    else
    {
        MN_WARN_LOG("MN_MSG_StartTimer: Can not find free timer handle.");
    }
}


VOS_VOID MN_MSG_StopTimer(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;

    if (enTimerId >= MN_MSG_TID_MAX)
    {
        return;
    }

    /* 寻找entityId和enTimerId与输入匹配的句柄 */
    for (i = 0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
      if (enTimerId == f_astMsgTimerHandle[i].enTimerId)
      {
          break;
      }
    }

    if (i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG))
    {
        /* 停止VOS定时器 */
        ulRet = NAS_StopRelTimer(WUEPS_PID_TAF, enTimerId, &f_astMsgTimerHandle[i].hTimer);
        if (VOS_OK == ulRet)
        {
            f_astMsgTimerHandle[i].hTimer = VOS_NULL_PTR;
            f_astMsgTimerHandle[i].enTimerId = MN_MSG_TID_MAX;
        }
        else
        {
            MN_WARN_LOG("MN_MSG_StopTimer: NAS_StopRelTimer failed.");
        }
    }
    else
    {
        MN_WARN_LOG("MN_MSG_StopTimer: Can not find the timer handle.");
    }
}


VOS_VOID  MN_MSG_StopAllRunningTimer(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i = 0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
        if ( (VOS_NULL_PTR      != f_astMsgTimerHandle[i].hTimer)
          && (MN_MSG_TID_MAX    != f_astMsgTimerHandle[i].enTimerId) )
        {
             /* 停止VOS定时器 */
            if (VOS_OK == NAS_StopRelTimer(WUEPS_PID_TAF,
                                 f_astMsgTimerHandle[i].enTimerId,
                                 &f_astMsgTimerHandle[i].hTimer))
            {
                f_astMsgTimerHandle[i].hTimer    = VOS_NULL_PTR;
                f_astMsgTimerHandle[i].enTimerId = MN_MSG_TID_MAX;
            }
            else
            {
                MN_WARN_LOG("MN_MSG_StopAllRunningTimer: NAS_StopRelTimer failed.");
            }
        }
    }

    return;
}




VOS_UINT32  MN_MSG_IsTimerStarting(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId
)
{
    VOS_UINT32                          i;

    if (enTimerId >= MN_MSG_TID_MAX)
    {
        return VOS_FALSE;
    }

    for (i = 0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
      if (enTimerId == f_astMsgTimerHandle[i].enTimerId)
      {
          break;
      }
    }

    if (i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG))
    {
        if (VOS_NULL_PTR != f_astMsgTimerHandle[i].hTimer)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32  MN_MSG_GetTimerRemainTime(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId
)
{
    VOS_UINT32                          ulTick;
    VOS_UINT32                          i;

    if (enTimerId >= MN_MSG_TID_MAX)
    {
        return 0;
    }
    for (i = 0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
      if (enTimerId == f_astMsgTimerHandle[i].enTimerId)
      {
          break;
      }
    }
    if ( i >= (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG))
    {
        return 0;
    }

    ulTick = 0;

    /* hTimer 为空时，说明此定时器已超时或停止 */
    if (VOS_NULL_PTR != f_astMsgTimerHandle[i].hTimer)
    {
        if (VOS_OK != VOS_GetRelTmRemainTime(&(f_astMsgTimerHandle[i].hTimer), &ulTick))
        {
            ulTick = 0;
        }
    }
    return ulTick * MN_MSG_TIMER_TICK;
}


VOS_VOID MN_MSG_UpdateRetryPeriod(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId,
    VOS_UINT32                          ulTimerLen
)
{
    VOS_UINT32                          i = (VOS_UINT32)(enTimerId - MN_TIMER_CLASS_MSG);

    if ( i >= (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG) )
    {
        MN_WARN_LOG("MN_MSG_UpdateRetryPeriod: Can not find the timer Id.");
        return;
    }
    f_astMsgTimerInfoTbl[i].ulTimeout = ulTimerLen;
}



VOS_VOID  MN_MSG_UpdateListInfo(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulLeftReportNum,
    const MN_MSG_LIST_PARM_STRU         *pstList
)
{
    g_clientId = clientId;
    g_opId = opId;
    g_ulLeftReportNum = ulLeftReportNum;
    PS_MEM_CPY(&g_stList,pstList,sizeof(g_stList));

}


VOS_VOID TAF_MSG_ListLeftMsg(VOS_VOID)
{
    MN_MSG_LIST_EVT_INFO_STRU           *pstListEvt;


    pstListEvt = (MN_MSG_LIST_EVT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_LIST_EVT_INFO_STRU));
    if (VOS_NULL_PTR == pstListEvt)
    {
        MN_ERR_LOG("TAF_MSG_ListLeftMsg:ALLOC MEM FAIL");
        return;
    }
    else
    {
        pstListEvt->bSuccess = VOS_TRUE;
        pstListEvt->bLastListEvt = VOS_TRUE;
        pstListEvt->bFirstListEvt = VOS_FALSE;

        PS_MEM_CPY( &(pstListEvt->stReceivedListPara), &g_stList, sizeof(MN_MSG_LIST_PARM_STRU) );
    }

    if (0 == g_ulLeftReportNum)
    {
        pstListEvt->ulReportNum = 0;
        pstListEvt->ulFailCause = MN_ERR_NO_ERROR;
        MN_MSG_ReportListEvent(g_clientId,g_opId,pstListEvt,MN_MSG_EVT_LIST);
    }
    else
    {
        /* 调用函数分段上报需列表个数 */
        MN_MSG_RptMsg(g_clientId, g_opId, g_ulLeftReportNum, &g_stList, pstListEvt);
    }
    PS_MEM_FREE(WUEPS_PID_TAF, pstListEvt);
}



VOS_VOID  MN_MSG_ProcTimeoutMsg(
    REL_TIMER_MSG                       * pTmrMsg
)
{
    MN_MSG_TIMER_HANDLE_STRU            *pstHandle;
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          i;

    enTimerId = (MN_MSG_TIMER_ID_ENUM_U32)pTmrMsg->ulName;
    if (enTimerId < MN_TIMER_CLASS_MSG)
    {
        return;
    }
    else
    {
        for (i=0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
        {
            if (enTimerId == f_astMsgTimerHandle[i].enTimerId)
            {
                break;
            }
        }

        if ( i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG) )
        {
            ulIndex = enTimerId - MN_TIMER_CLASS_MSG;

        }
        else
        {
            MN_WARN_LOG1("MN_MSG_ProcTimeoutMsg:Invalid Timer ID", (VOS_INT32)enTimerId);
            return;
        }
    }

    MN_NORM_LOG1("TAF SMA Timer expired.", (VOS_INT32)enTimerId);

    /* 由ulName得到定时器句柄 将该句柄复位 */
    pstHandle = (MN_MSG_TIMER_HANDLE_STRU *)&f_astMsgTimerHandle[i];
    pstHandle->hTimer = VOS_NULL_PTR;
    pstHandle->enTimerId = MN_MSG_TID_MAX;

    /* 调用Timer ID对应的超时处理函数 */
    f_astMsgTimerInfoTbl[ulIndex].pfnTimeoutProc(pTmrMsg->ulPara);
}


LOCAL VOS_VOID  MSG_WaitSmsMoControlCheckTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulIndex;
    VOS_BOOL                            bBufferEntity;

    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));
    /* 获取等待FDN检查结果的MO实体或缓存 */
    ulRet = MN_MSG_GetSpecificStatusMoEntity(MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP,
                                             &bBufferEntity,
                                             &ulIndex,
                                             &stMoEntity);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_WaitSmsMoControlCheckTimeout: discard SMS MO CONTROL RESPONSE.");
        return;
    }

    /*
    等待USIM模块的SMS MO CONTROL RESPONSE消息超时:
            通知APP短信发送请求被拒绝；
            释放短信发送实体；
    */
    MN_WARN_LOG("MSG_WaitSmsMoControlCheckTimeout: wait for SMS MO CONTROL RESPONSE timeout.");
    MN_SendClientResponse(stMoEntity.clientId,
                          stMoEntity.opId,
                          MN_ERR_CLASS_SMS_INTERNAL);

    /* 销毁等待SMS MO CONTROL检查结果的MO实体或缓存 */
    MN_MSG_DestroySpecificMoEntity(bBufferEntity, ulIndex);

    /* 通知SPM检查结果 */
    TAF_MSG_SendSpmMsgCheckResultInd(stMoEntity.clientId, stMoEntity.opId,TAF_MSG_ERROR_CTRL_CHECK_TIMEOUT);

    return;

}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

