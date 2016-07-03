
#include "SmInclude.h"
#include "NasSmComm.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SM_RCVTAF_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


VOS_VOID NAS_SM_ProcTafPdpActiveReq(
    SMREG_PDP_ACTIVATE_REQ_STRU        *pstMsg
)
{
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucCntxtIndex;

    ucCr         = pstMsg->ucConnectId;                                         /* 取CR的实际值                             */
    ucCntxtIndex = g_CrMapToNsapi[ucCr];                                        /* 根据Cr获取ucCntxtIndex                   */

    if ( 0xff == ucCntxtIndex )
    {                                                                           /* 为MS发起的请求(Cr映射的NSAPI无效)        */
        if ( SM_RETURN_OK == SM_PdpAddrApnComp(pstMsg) )
        {                                                                       /* PDP context存在,并且PDP address和APN相同 */
            SM_SndTafSmPdpActivateRej(ucCr, SM_TAF_CAUSE_SM_DUPLICATE, VOS_NULL_PTR);
        }
        else
        {
            NAS_SM_ProcTafPdpCnxtActReq_S00(pstMsg);
        }
    }
    else
    {                                                                           /* network发起的请求,状态为非空的处理       */
        switch(g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
        {
        case SM_PDP_INACTIVE:
            NAS_SM_ProcTafPdpCnxtActReq_S05(pstMsg);

            break;
        case SM_PDP_ACTIVE_PENDING:
        case SM_PDP_ACTIVE:
        case SM_PDP_MODIFY_PENDING:
        case SM_PDP_INACTIVE_PENDING:
        case SM_PDP_NW_MODIFY:
            SM_SndTafSmPdpActivateRej(ucCr,
                                      SM_TAF_CAUSE_SM_INVALID_NSAPI,
                                      VOS_NULL_PTR);

            break;
        default:
            break;
        }
    }

    return;
}

/*******************************************************************************
  Module:   SM_ProcTafPdpActiveRej
  Function: TAFSM_PDP_ACTIVATE_REJ_RSP的消息分发
  Input:    SMREG_PDP_ACTIVATE_REJ_RSP_STRU     *pstMsg
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   郑 伟   2003.12.09   新规作成
*******************************************************************************/
VOS_VOID NAS_SM_ProcTafPdpActiveRej(
    SMREG_PDP_ACTIVATE_REJ_RSP_STRU     *pstMsg
)
{
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucCntxtIndex;

    ucCr         = pstMsg->ucConnectId;                                         /* 取CR的实际值                             */
    ucCntxtIndex = g_CrMapToNsapi[ucCr];                                        /* 根据Cr获取ucCntxtIndex                   */

    if ( 0xff == ucCntxtIndex )
    {                                                                           /* 状态为SM_PDP_INACTIVE                    */
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvNwReqPdpCnxtActMsg_S02:WARNING:0xff == ucCntxtIndex ");
        return;
    }

    if ( SM_PDP_INACTIVE == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {                                                                           /* 状态为SM_PDP_NW_ACTIVE                   */
        SM_TimerStop(ucCntxtIndex);                                         /* 停止Timer                                */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;   /* 状态切换到SM_PDP_INACTIVE                */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpCnxtActRejRsp:NORMAL:SM state: SM_PDP_INACTIVE ==> SM_PDP_INACTIVE");

        PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpCnxtActRejRsp:NORMAL: Destroy SM entity(index):", ucCntxtIndex);
        SM_SndReqPdpActRejMsg(pstMsg, g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi);  /* 发送REJECT消息                           */
        SM_ComDelNsapiFromAddr(
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex,
            ucCntxtIndex);                                                  /* 维护ADDR和APN实体                        */
        g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi] = 0xff; /* 初始化Ti列表                             */
        g_CrMapToNsapi[ucCr] = 0xff;                                        /* 初始化Cr列表                             */
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvTafPdpCnxtActRejRsp:WARNING:APP->SM: Message type not compatible with the state  !");
    }
    return;
}


VOS_VOID NAS_SM_ProcTafPdpDeActiveReq(
    SMREG_PDP_DEACTIVATE_REQ_STRU      *pstMsg
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucLinkNsapi;

    ucCr         = pstMsg->ucConnectId;                                         /* 取CR的实际值                             */
    ucCntxtIndex = g_CrMapToNsapi[ucCr];                                        /* 根据Cr获取ucCntxtIndex                   */

    if ( 0xff == ucCntxtIndex )
    {                                                                           /* 状态为SM_PDP_INACTIVE                    */
        SM_SndTafSmPdpDeActInd (
            ucCr,
            SM_TAF_CAUSE_SM_NW_MSG_NOT_COMPATIBLE,
            SM_FALSE);                                                          /* 发送TAFSM_PDP_DEACTIVATE_IND             */
        return;
    }
    ucAddrIndex  = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;

    if ( SM_PDP_INACTIVE_PENDING
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {                                                                           /* 状态为SM_PDP_INACTIVE_PENDING            */
        ;
    }
    else
    {
        if((SM_TRUE == pstMsg->bitOpTearDownInd) && (SM_TRUE == pstMsg->ucTearDownInd))
        {                                                                       /* 包含Tear down indicator IE并且 requested */
            SM_SndRabmSmDeactivateInd(
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt,
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi);             /* 通知RABM去激活Nsapi列表:                 */
            for (i=0;i<g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt;i++)
            {                                                                   /* Nsapi列表                                */
                ucLinkNsapi
                    = g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[i];
                SM_ComClearPdpCntxt(ucLinkNsapi);                               /* 释放实体                                 */
                g_SmEntity.aPdpCntxtList[ucLinkNsapi].ucState=SM_PDP_INACTIVE;  /* 状态切换到SM_PDP_INACTIVE                */

                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpCnxtDeActReq:NORMAL: SM state = SM_PDP_INACTIVE");
                if ( ucLinkNsapi != ucCntxtIndex )
                {
                    g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucLinkNsapi].ucTi]
                        = 0xFF;
                    g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucLinkNsapi].ucCr]
                        = 0xFF;
                }
            }
            SM_ComClearPdpAddrApn(ucAddrIndex);                                 /* 清除Addr Apn实体                         */
        }
        else
        {                                                                       /* 不包含Tear down  或者not requested       */
            SM_ComClearPdpCntxt(ucCntxtIndex);                                  /* 清除实体                                 */
            SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex);                   /* 维护Addr和Apn实体                        */
            SM_SndRabmSmDeactivateInd(1,&ucCntxtIndex);                         /* 通知RABM去激活Nsapi                      */
        }

        if ((SM_TRUE == pstMsg->bitOpPcpTaCause) && (SM_TRUE == pstMsg->enPcpTaCause))
        {
            NAS_SM_BeginSession();

            SM_SndPdpDeActReqMsg(pstMsg, ucCntxtIndex);                             /* 发送DEACTIVATE PDP CONTEXT REQUEST       */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes = 0;     /* Timr 超时次数清0                         */
            SM_TimerStart(ucCntxtIndex,SM_T3390_LENGTH,SM_TIMER_TYPE_T3390);        /* 启动T3390                                */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState=SM_PDP_INACTIVE_PENDING; /* 状态切换到SM_PDP_INACTIVE_PENDING        */

            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "SM_RcvTafPdpCnxtDeActReq: SM state = SM_PDP_INACTIVE_PENDING");
        }
        else
        {   /*本地释放资源*/
            /*停止Timer;释放申请的APN内存;去激活RABM;释放Qos内存;释放缓存的重发消息 */

            SM_SndRabmSmDeactivateInd(1, &ucCntxtIndex);
            SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex);

            SM_ComClearPdpCntxt(ucCntxtIndex);

            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;

            g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr]=0xff;
            g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi]=0xff;

            PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                    "SM Local Release :  ==> SM_PDP_INACTIVE");

        }
    }
    return;
}


VOS_VOID NAS_SM_ProcTafPdpModifyRsp(
    SMREG_PDP_MODIFY_RSP_STRU          *pstMsg
)
{
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucCntxtIndex;

    ucCr         = pstMsg->ucConnectId;                                         /* 取CR的实际值                             */
    ucCntxtIndex = g_CrMapToNsapi[ucCr];                                        /* 根据Cr获取ucCntxtIndex                   */

    if ( 0xff != ucCntxtIndex )
    {                                                                           /* 状态不为SM_PDP_INACTIVE                  */
        if ( SM_PDP_NW_MODIFY == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
        {                                                                       /* 当前的状态为SM_PDP_NW_MODIFY             */
            SM_TimerStop(ucCntxtIndex);                                         /* 停止Timer                                */
            SM_SndPdpModAccMsg(pstMsg, ucCntxtIndex);                           /* 向network发送MODIFY PDP CONTEXT ACCEP    */
            SM_SndRabmSmModifyInd(ucCntxtIndex);                                /* 通知RABM修改成功                         */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE;     /* 状态切换到SM_PDP_ACTIVE                  */

            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpModifyRsp:NORMAL:SM state: SM_PDP_NW_MODIFY ==> SM_PDP_ACTIVE");

            NAS_SM_SndGmmPdpModifyInd(ucCntxtIndex + SM_NSAPI_OFFSET);

            NAS_SM_EndSession();
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvTafPdpModifyRsp:WARNING:APP->SM: Message type not compatible with the state  !");
        }
    }
    return;
}


VOS_VOID NAS_SM_ProcTafPdpModifyRejRsp(
    SMREG_PDP_MODIFY_REJ_RSP_STRU       *pstMsg
)
{
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucCntxtIndex;

    /* 根据Cr获取ucCntxtIndex */
    ucCr         = pstMsg->ucConnectId;
    ucCntxtIndex = g_CrMapToNsapi[ucCr];

    if (0xFF != ucCntxtIndex)
    {
        if (SM_PDP_NW_MODIFY == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
        {
            SM_TimerStop(ucCntxtIndex);

            /* 发送MODIFY_PDP_CONTEXT_REJECT消息到网侧 */
            NAS_SM_SndPdpModRejMsg(pstMsg, ucCntxtIndex);

            /* 状态切换到SM_PDP_ACTIVE */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE;

            NAS_NORMAL_LOG(WUEPS_PID_SM,
                "NAS_SM_ProcTafPdpModifyRejRsp:NORMAL:SM state: SM_PDP_NW_MODIFY ==> SM_PDP_ACTIVE");

            NAS_SM_EndSession();
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_SM,
                "NAS_SM_ProcTafPdpModifyRejRsp:WARNING:APP->SM: Message type not compatible with the state  !");
        }
    }

    return;
}


VOS_VOID NAS_SM_ProcTafPdpModifyReq(
    SMREG_PDP_MODIFY_REQ_STRU          *pstMsg
)
{
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucCntxtIndex;
    VOS_INT8                            ue_revision;

    ucCr         = pstMsg->ucConnectId;                                         /* 取CR的实际值                             */
    ucCntxtIndex = g_CrMapToNsapi[ucCr];                                        /* 根据Cr获取ucCntxtIndex                   */

    /* 终端可配置需求:如果当前版本为PS_PTL_VER_PRE_R99，收到上层用户发来的PDP MODIFY请求，
                       直接回复拒绝，Cause: TAF_SM_REJ_CAUSE_INSUFF_RESOURCE */
    ue_revision = NAS_Common_Get_Supported_3GPP_Version(SM_MM_COM_SRVDOMAIN_PS);
    if (PS_PTL_VER_PRE_R99 == ue_revision)
    {
        SM_SndTafSmPdpModifyRej(SM_TAF_CAUSE_SM_NW_INSUFFICIENT_RESOURCES, ucCr);
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvTafPdpCntxtModifyReq:WARNING:ue_revision is PS_PTL_VER_PRE_R99,modify PDP req is rejected!");
        return;
    }

    if ( 0xff != ucCntxtIndex )
    {                                                                           /* 状态不为SM_PDP_INACTIVE                  */
        if ( SM_PDP_ACTIVE == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
        {                                                                       /* 当前的状态为SM_PDP_ACTIVE                */
            NAS_SM_BeginSession();


            SM_SndPdpModReqMsg(pstMsg, ucCntxtIndex);                           /* 向network发送 REQUEST                    */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes = 0; /* Timr 超时次数清0                         */
            SM_TimerStart(ucCntxtIndex,SM_T3381_LENGTH,SM_TIMER_TYPE_T3381);    /* 启动T3381                                */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
                = SM_PDP_MODIFY_PENDING;                                        /* 状态切换到SM_PDP_MODIFY_PENDING          */

            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpCntxtModifyReq:NORMAL:SM state: SM_PDP_ACTIVE ==> SM_PDP_MODIFY_PENDING");
        }
        else if (SM_PDP_MODIFY_PENDING
                 == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
        {
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvTafPdpCntxtModifyReq:WARNING:APP->SM: Message type not compatible with the state  !");
        }
        else if (SM_PDP_NW_MODIFY
                 == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
        {
            SM_SndTafSmPdpModifyRej(SM_TAF_CAUSE_SM_MODIFY_COLLISION,
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);
        }
        else
        {
            SM_SndTafSmPdpModifyRej(SM_TAF_CAUSE_SM_NW_MSG_NOT_COMPATIBLE,
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);
        }
    }
    else
    {
        SM_SndTafSmPdpModifyRej(SM_TAF_CAUSE_SM_NW_MSG_NOT_COMPATIBLE, ucCr);                                                     /* 回拒绝消息                               */
    }

    return;
}


VOS_VOID NAS_SM_ProcTafPdpActiveSecReq(
    SMREG_PDP_ACTIVATE_SEC_REQ_STRU    *pstMsg
)
{
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucLinkCntxtIndex;
    VOS_INT8                            ue_revision;

    ucCr         = pstMsg->ucConnectId;                                         /* 取CR的实际值                             */
    ucCntxtIndex = g_CrMapToNsapi[ucCr];                                        /* 根据Cr获取ucCntxtIndex                   */

    /* 终端可配置需求:如果当前版本为PS_PTL_VER_PRE_R99，收到上层用户发来的PDP二次激活请求,
                       直接回复拒绝，Cause: TAF_SM_REJ_CAUSE_INSUFF_RESOURCE */
    ue_revision = NAS_Common_Get_Supported_3GPP_Version(SM_MM_COM_SRVDOMAIN_PS);
    if (PS_PTL_VER_PRE_R99 == ue_revision)
    {
        SM_SndTafSmPdpActSecRej(ucCr, SM_TAF_CAUSE_SM_NW_INSUFFICIENT_RESOURCES);
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvTafPdpCnxtActSecReq:WARNING:ue_revision is PS_PTL_VER_PRE_R99,active secondary PDP req is rejected!");
        return;
    }

    ucLinkCntxtIndex = (pstMsg->ucPrimNsapi - SM_NSAPI_OFFSET);                 /* 获得ucLinkCntxtIndex                     */
    if ( 0xff != ucCntxtIndex )
    {                                                                           /* 状态不为SM_PDP_INACTIVE                  */
        SM_SndTafSmPdpActSecRej(ucCr, SM_TAF_CAUSE_SM_INVALID_NSAPI);
    }
    else
    {
        switch ( g_SmEntity.aPdpCntxtList[ucLinkCntxtIndex].ucState )
        {                                                                       /* ucLinkCntxtIndex状态为已经激活           */
            case SM_PDP_ACTIVE:
            case SM_PDP_MODIFY_PENDING:
            case SM_PDP_NW_MODIFY:
            case SM_PDP_ACTIVE_PENDING:
                NAS_SM_ProcTafPdpActiveSecReq_S00(pstMsg);
                break;
            default:
                SM_SndTafSmPdpActSecRej(ucCr, SM_TAF_CAUSE_SM_NW_UKNOWN_PDP_CONTEXT);
                break;
        }
    }
    return;
}


VOS_VOID NAS_SM_ProcTafPdpActiveSecReq_S00(
    SMREG_PDP_ACTIVATE_SEC_REQ_STRU    *pstMsg
)
{
    VOS_UINT16                          i;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucTiFlg;
    VOS_UINT8                           ucNsapiCnt;
    VOS_UINT8                           ucCr;

    ucTi = 0;
    ucCr = pstMsg->ucConnectId;                                                 /* 取CR的实际值                             */
    ucTiFlg = SM_FALSE;
    ucCntxtIndex = SM_MAX_NSAPI_NUM;
    for ( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
    {
        if ( SM_PDP_INACTIVE == g_SmEntity.aPdpCntxtList[i].ucState )
        {
            ucCntxtIndex = (VOS_UINT8)i;                                        /* 获取实体的索引                           */
            break;
        }
    }

    for ( i = 0x80; i <= (SM_MAX_TI_NUM - 1); i++ )
    {
        if ( 0xff == g_TiMapToNsapi[i] )
        {                                                                       /* 申请没有使用的TI                         */
            ucTi = (VOS_UINT8)i;                                                  /* 获取TI                                   */
            ucTiFlg = SM_TRUE;
            break;
        }
    }

    if ( (SM_MAX_NSAPI_NUM != ucCntxtIndex)&&(SM_FALSE != ucTiFlg) )
    {                                                                           /* 申请 实体,PDP Addr,Ti成功                */
        PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpCnxtActSecReq_S00:NORMAL: Create SM entity(index):", ucCntxtIndex);

        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTiFlg = SM_TI_MS_ORG;          /* 设定实体的发起标志 MS发起                */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr = ucCr;                     /* 存储CR                                   */
        g_CrMapToNsapi[ucCr] = ucCntxtIndex;                                    /* 维护Cr和NSAPI的映射                      */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi = ucTi;                     /* 存储TI                                   */
        g_TiMapToNsapi[ucTi] = ucCntxtIndex;                                    /* 维护Ti和NSAPI的映射                      */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength
            = pstMsg->stRequestedQos.ulQosLen;                                  /* 设定Qos的数据长度                        */
        PS_MEM_CPY(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
                   pstMsg->stRequestedQos.aucQos,
                   pstMsg->stRequestedQos.ulQosLen);                            /* 存储Qos数据                              */
        ucAddrIndex = g_SmEntity.aPdpCntxtList
            [pstMsg->ucPrimNsapi - SM_NSAPI_OFFSET].ucAddrIndex;                /* 获得ucAddrIndex                          */
        ucNsapiCnt = g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt;
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[ucNsapiCnt]
            = ucCntxtIndex;                                                     /* 存储Nsapi                                */
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt++;                  /* 维护Nsapi                                */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex = ucAddrIndex;
        NAS_SM_BeginSession();
        SM_SndPdpActSecReqMsg(pstMsg, ucCntxtIndex);                            /* 向network发送SECONDARY ACTIVE REQUEST    */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes = 0;     /* Timr 超时次数清0                         */
        SM_TimerStart(ucCntxtIndex,SM_T3380_LENGTH,SM_TIMER_TYPE_T3380);        /* 启动T3381                                */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
            = SM_PDP_ACTIVE_PENDING;                                            /* 状态切换到SM_PDP_ACTIVE_PENDING          */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpCnxtActSecReq_S00:NORMAL:SM state: SM_PDP_INACTIVE ==> SM_PDP_ACTIVE_PENDING");
        NAS_SM_SndGmmPdpStatusInd();
        SM_SndRabmSmActivateInd(ucCntxtIndex, RABMSM_ACT_MSG_1);                /* 通知RABM已经激活Nsapi                    */
    }
    else
    {
        SM_SndTafSmPdpActSecRej(ucCr, SM_TAF_CAUSE_SM_NW_INSUFFICIENT_RESOURCES);  /* 回拒绝消息                               */
    }

    return;
}


VOS_VOID NAS_SM_ProcTafPdpCnxtActReq_S00(
    SMREG_PDP_ACTIVATE_REQ_STRU        *pstMsg
)
{
    VOS_UINT16                          i;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucTiFlg;
    VOS_UINT8                           ucCr;

    ucTi = 0;
    ucCr = pstMsg->ucConnectId;
    ucTiFlg = SM_FALSE;
    ucCntxtIndex = SM_MAX_NSAPI_NUM;

    for ( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
    {
        if ( SM_PDP_INACTIVE == g_SmEntity.aPdpCntxtList[i].ucState )
        {
            ucCntxtIndex = (VOS_UINT8)i;                                        /* 获取实体的索引                           */
            break;
        }
    }

    for ( i = 0x80; i <= (SM_MAX_TI_NUM - 1); i++ )
    {
        if ( 0xff == g_TiMapToNsapi[i] )
        {                                                                       /* 申请没有使用的TI                         */
            ucTi = (VOS_UINT8)i;                                                /* 获取TI                                   */
            ucTiFlg = SM_TRUE;
            break;
        }
    }

    ucAddrIndex = SM_ComFindNullAddrApn();                                      /* 申请未使用的Addr                         */
    if (( SM_MAX_NSAPI_NUM != ucCntxtIndex )
      &&( SM_FALSE != ucTiFlg )
      &&( SM_MAX_NSAPI_NUM!= ucAddrIndex))
    {                                                                           /* 申请 实体,PDP Addr,Ti成功                */
        PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpCnxtActReq_S00:NORMAL:Create SM entity(index):", ucCntxtIndex);

        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTiFlg = SM_TI_MS_ORG;          /* 设定实体的发起标志 MS发起                */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr = ucCr;                     /* 存储CR                                   */
        g_CrMapToNsapi[ucCr]= ucCntxtIndex;                                     /* 维护Cr和NSAPI的映射                      */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi = ucTi;                     /* 存储TI                                   */
        g_TiMapToNsapi[ucTi]= ucCntxtIndex;                                     /* 维护Ti和NSAPI的映射                      */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex = ucAddrIndex;       /* 设定ucAddrIndex                          */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength
            = pstMsg->stReqQos.ulQosLen;                                        /* 设定Qos的数据长度                        */
        PS_MEM_CPY(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
                   pstMsg->stReqQos.aucQos,
                   pstMsg->stReqQos.ulQosLen);                                  /* 存储Qos数据                              */
        g_SmPdpAddrApn.usPdpAddrFlg |= (VOS_UINT16)((VOS_UINT32)0x0001<<ucAddrIndex);
        SM_MemCpy(
              g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.aucAddrValue,
              pstMsg->stReqPdpAddr.aucPdpAddr,
              pstMsg->stReqPdpAddr.ulPdpAddrLen);                               /* 存储PDP Addr数据                         */
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.ulAddrLength
            = pstMsg->stReqPdpAddr.ulPdpAddrLen;                                /* 设定PDP Addr 长度                        */
        if ( SM_TRUE == pstMsg->bitOpAcsPointName )
        {                                                                       /* APN存在                                  */
            g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.ulApnLength
                = pstMsg->stAcsPointName.ulApnLen;                              /* 设定AcsPointName数据长度                 */
            PS_MEM_CPY(g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.aucApnValue,
                       pstMsg->stAcsPointName.aucApnAddr,
                       pstMsg->stAcsPointName.ulApnLen);                        /* 存储AcsPointName数据                     */
        }
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt = 1;                /* 设定Nsapi个数                            */
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[0] = ucCntxtIndex;    /* 存储NSAPI                                */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE_PENDING; /* 状态切换到SM_PDP_ACTIVE_PENDING          */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvTafPdpCnxtActReq_S00:NORMAL:SM state: SM_PDP_INACTIVE ==> SM_PDP_ACTIVE_PENDING ");

        NAS_SM_BeginSession();
        SM_SndPdpActReqMsg(pstMsg, ucCntxtIndex);                               /* 发送消息REQUEST                          */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes = 0;     /* 超时次数清0                              */
        SM_TimerStart(ucCntxtIndex,SM_T3380_LENGTH,SM_TIMER_TYPE_T3380);        /* 启动T3380                                */
        NAS_SM_SndGmmPdpStatusInd();
        SM_SndRabmSmActivateInd(ucCntxtIndex, RABMSM_ACT_MSG_1);                /* 通知RABM已经激活Nsapi                    */
    }
    else
    {
        SM_SndTafSmPdpActivateRej(ucCr,
                                  SM_TAF_CAUSE_SM_NW_INSUFFICIENT_RESOURCES,
                                  VOS_NULL_PTR);                                /* 回拒绝消息                               */
    }

    return;
}


VOS_VOID NAS_SM_ProcTafPdpCnxtActReq_S05(
    SMREG_PDP_ACTIVATE_REQ_STRU        *pstMsg
)
{
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucCr;

    ucCr = pstMsg->ucConnectId;
    ucCntxtIndex = g_CrMapToNsapi[ucCr];

    SM_TimerStop(ucCntxtIndex);                                                 /* 停止Network发起PDP Active保护Timer       */

    ucAddrIndex = SM_ComFindNullAddrApn();                                      /* 申请未使用的Addr                         */
    if ( SM_MAX_NSAPI_NUM != ucAddrIndex )
    {                                                                           /* 申请 PDP Addr成功                        */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex = ucAddrIndex;       /* 设定ucAddrIndex                          */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength
            = pstMsg->stReqQos.ulQosLen;                                        /* 设定Qos的数据长度                        */
        PS_MEM_CPY(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
                   pstMsg->stReqQos.aucQos,
                   pstMsg->stReqQos.ulQosLen);                                  /* 存储Qos数据                              */
        g_SmPdpAddrApn.usPdpAddrFlg |= (VOS_UINT16)((VOS_UINT32)0x0001<<ucAddrIndex);
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt = 1;                /* 设定Nsapi个数                            */
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[0] = ucCntxtIndex;    /* 存储NSAPI                                */
        SM_MemCpy(
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.aucAddrValue,
                pstMsg->stReqPdpAddr.aucPdpAddr,
                pstMsg->stReqPdpAddr.ulPdpAddrLen);                             /* 存储PDP Addr数据                         */
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.ulAddrLength
            = pstMsg->stReqPdpAddr.ulPdpAddrLen;                                /* 设定PDP Addr 长度                        */
        if ( SM_TRUE == pstMsg->bitOpAcsPointName )
        {                                                                       /* APN存在                                  */
            g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.ulApnLength
                = pstMsg->stAcsPointName.ulApnLen;                              /* 设定AcsPointName数据长度                 */
            PS_MEM_CPY(g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.aucApnValue,
                       pstMsg->stAcsPointName.aucApnAddr,
                       pstMsg->stAcsPointName.ulApnLen);                        /* 存储AcsPointName数据                     */
        }

        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE_PENDING; /* 状态切换到SM_PDP_ACTIVE_PENDING          */

        NAS_SM_BeginSession();

        SM_SndPdpActReqMsg(pstMsg, ucCntxtIndex);                               /* 发送消息REQUEST                          */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes = 0;     /* 超时次数清0                              */
        SM_TimerStart(ucCntxtIndex,SM_T3380_LENGTH,SM_TIMER_TYPE_T3380);        /* 启动T3380                                */
        NAS_SM_SndGmmPdpStatusInd();
        SM_SndRabmSmActivateInd(ucCntxtIndex, RABMSM_ACT_MSG_1);                /* 通知RABM已经激活Nsapi                    */
    }
    else
    {
        SM_SndTafSmPdpActivateRej(
            ucCr,
            SM_TAF_CAUSE_SM_NW_INSUFFICIENT_RESOURCES,
            VOS_NULL_PTR);
    }

    return;
}


VOS_VOID NAS_SM_RcvTafPdpCnxtActReq(
    SMREG_PDP_ACTIVATE_REQ_STRU        *pstMsg
)
{
    VOS_UINT32                          ulIndex;
    VOS_VOID                           *pHoldMsg;

    if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg)
    {
        /* 调用接收D_PMC_SMREG_PDP_ACT_REQ的处理 */
        NAS_SM_ProcTafPdpActiveReq(pstMsg);
    }
    else
    {
        for (ulIndex = 0; ulIndex < SM_MAX_NSAPI_NUM; ulIndex++)
        {
            if (VOS_NULL_PTR == g_SmEntity.aHoldMsg[ulIndex].pHoldRcvMsg)
            {
                /* 申请缓存消息 */
                pHoldMsg = SM_Malloc(sizeof(SMREG_PDP_ACTIVATE_REQ_STRU));
                if (VOS_NULL_PTR == pHoldMsg)
                {
                    PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_SM_RcvTafPdpCnxtActReq: ERROR: ALLOC MSG FAIL");
                    return;
                }

                /* 拷贝缓存消息 */
                PS_MEM_CPY(pHoldMsg, (VOS_VOID *)pstMsg, sizeof(SMREG_PDP_ACTIVATE_REQ_STRU));

                g_SmEntity.aHoldMsg[ulIndex].pHoldRcvMsg = pHoldMsg;
                break;
            }
        }

        if (SM_PS_NOTREGISTER == g_SmEntity.ucRegisterFlg)
        {
            /* 向GMM发送注册请求 */
            NAS_SM_SndGmmEstablishReq();

            /* 启动定时器 80s */
            SM_TimerStart(SM_REGISTER_TIMER_ID, SM_T0001_LENGTH, SM_TIMER_TYPE_T0001);

            g_SmEntity.ucRegisterFlg = SM_PS_REGISTERING;
        }
    }
}


VOS_VOID NAS_SM_RcvTafPdpCnxtActRejRsp(
    SMREG_PDP_ACTIVATE_REJ_RSP_STRU     *pstMsg
)
{
    if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg)
    {
        NAS_SM_ProcTafPdpActiveRej(pstMsg);
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_SM_RcvTafPdpCnxtActRejRsp:WARNING: PS not Registered !");
    }
}


VOS_VOID NAS_SM_RcvTafPdpCntxtModifyReq(
    SMREG_PDP_MODIFY_REQ_STRU          *pstMsg
)
{
    if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg)
    {
        NAS_SM_ProcTafPdpModifyReq(pstMsg);
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_SM_RcvTafPdpCntxtModifyReq:WARNING: PS not Registered !");
    }
}


VOS_VOID NAS_SM_RcvTafPdpCnxtDeActReq(
    SMREG_PDP_DEACTIVATE_REQ_STRU       *pstMsg
)
{
    VOS_UINT32                          ulIndex;
    VOS_VOID                           *pHoldMsg;

    if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg)
    {
        NAS_SM_ProcTafPdpDeActiveReq(pstMsg);
    }
    else if (SM_PS_REGISTERING == g_SmEntity.ucRegisterFlg)
    {
        for (ulIndex = 0; ulIndex < SM_MAX_NSAPI_NUM; ulIndex++)
        {
            if (VOS_NULL_PTR == g_SmEntity.aHoldMsg[ulIndex].pHoldRcvMsg)
            {
                /* 申请缓存消息 */
                pHoldMsg = SM_Malloc(sizeof(SMREG_PDP_DEACTIVATE_REQ_STRU));
                if (VOS_NULL_PTR == pHoldMsg)
                {
                    PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_SM_RcvTafPdpCnxtDeActReq: ERROR: ALLOC MSG FAIL");
                    return;
                }

                /* 拷贝缓存消息 */
                PS_MEM_CPY(pHoldMsg, (VOS_VOID *)pstMsg, sizeof(SMREG_PDP_DEACTIVATE_REQ_STRU));

                g_SmEntity.aHoldMsg[ulIndex].pHoldRcvMsg = pHoldMsg;
                break;
            }
        }
    }
    else
    {
    }
}


VOS_VOID NAS_SM_RcvTafPdpCnxtActSecReq(
    SMREG_PDP_ACTIVATE_SEC_REQ_STRU *pstMsg
)
{
    if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg)
    {
        NAS_SM_ProcTafPdpActiveSecReq(pstMsg);
    }
    else
    {
        /* GMM未注册，回拒绝消息 */
        SM_SndTafSmPdpActSecRej(pstMsg->ucConnectId, SM_TAF_CAUSE_SM_UNKNOWN);
    }
}


VOS_VOID NAS_SM_RcvTafPdpModifyRsp(
    SMREG_PDP_MODIFY_RSP_STRU           *pstMsg
)
{
    if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg)
    {
        NAS_SM_ProcTafPdpModifyRsp(pstMsg);
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_SM_RcvTafPdpModifyRsp:WARNING: PS not Registered !");
    }
}


VOS_VOID NAS_SM_RcvTafPdpModifyRejRsp(
    SMREG_PDP_MODIFY_REJ_RSP_STRU       *pstMsg
)
{
    if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg)
    {
        NAS_SM_ProcTafPdpModifyRejRsp(pstMsg);
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_SM,
            "NAS_SM_RcvTafPdpModifyRejRsp:WARNING: PS not Registered !");
    }
}


VOS_UINT8 SM_PdpAddrApnComp(
    SMREG_PDP_ACTIVATE_REQ_STRU        *pstMsg
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucRet;
    VOS_UINT8                           ucResult1;
    VOS_UINT8                           ucResult2;

    ucRet     = SM_RETURN_NG;
    ucResult1 = 0xFF;
    ucResult2 = 0xFF;
    if(( SM_FALSE == pstMsg->bitOpAcsPointName )
        ||( pstMsg->stReqPdpAddr.ulPdpAddrLen <= 2 ))
    {                                                                           /* 不可以比较                               */
    }
    else
    {
        for(i = 0; i < SM_MAX_NSAPI_NUM; i++)
        {
            if(0 != (g_SmPdpAddrApn.usPdpAddrFlg & (VOS_UINT16)((VOS_UINT32)0x01 << i)))
            {                                                                   /* AddrApn存在                              */
                if(( g_SmPdpAddrApn.aPdpAddrlist[i].PdpApn.ulApnLength
                    == pstMsg->stAcsPointName.ulApnLen )
                    &&(g_SmPdpAddrApn.aPdpAddrlist[i].PdpAddrInfo.ulAddrLength
                    == pstMsg->stReqPdpAddr.ulPdpAddrLen ))
                {                                                               /* 数据的长度相同                           */
                    ucResult1 = SM_MemCmp(
                        g_SmPdpAddrApn.aPdpAddrlist[i].PdpApn.aucApnValue,
                        pstMsg->stAcsPointName.aucApnAddr,
                        pstMsg->stAcsPointName.ulApnLen);                       /* 调用内存比较函数                         */
                    ucResult2 = SM_MemCmp(
                        g_SmPdpAddrApn.aPdpAddrlist[i].PdpAddrInfo.aucAddrValue,
                        pstMsg->stReqPdpAddr.aucPdpAddr,
                        pstMsg->stReqPdpAddr.ulPdpAddrLen);                     /* 调用内存比较函数                         */
                    if(( 0 == ucResult1 )
                        &&( 0 == ucResult2 ))
                    {                                                           /* APN和Addr相同                            */
                        ucRet = SM_RETURN_OK;                                   /* 设定返回值OK                             */
                        break;
                    }
                }
            }
        }
    }
    return ucRet;
}


VOS_VOID NAS_SM_StopRegisterProcedure(VOS_VOID)
{
    VOS_UINT8                           i;

    /* 检查当前是否存在缓存的消息 */
    for (i = 0; i < SM_MAX_NSAPI_NUM; i++)
    {
        if (VOS_NULL_PTR != g_SmEntity.aHoldMsg[i].pHoldRcvMsg)
        {
            return;
        }
    }

    /* 检查当前是否存在激活过程中的PDP */
    for (i = 0; i < SM_MAX_NSAPI_NUM; i++)
    {
        if (SM_PDP_ACTIVE_PENDING == g_SmEntity.aPdpCntxtList[i].ucState)
        {
            return;
        }
    }

    /* 更新SM注册状态和停止注册定时器 */
    if (SM_PS_REGISTERING == NAS_SM_GET_REGISTER_FLG())
    {
        NAS_SM_SET_REGISTER_FLG(SM_PS_NOTREGISTER);
        SM_TimerStop(SM_REGISTER_TIMER_ID);
    }

    return;
}


VOS_VOID NAS_SM_ClearHoldMsgByConnectId(VOS_UINT8 ucConnectId)
{
    MSG_HEADER_STRU                    *pstHoldMsg;
    VOS_UINT8                           i;

    for (i = 0; i < SM_MAX_NSAPI_NUM; i++)
    {
        if (VOS_NULL_PTR != g_SmEntity.aHoldMsg[i].pHoldRcvMsg)
        {
            pstHoldMsg = (MSG_HEADER_STRU *)g_SmEntity.aHoldMsg[i].pHoldRcvMsg;

            if ( (ID_SMREG_PDP_ACTIVATE_REQ == pstHoldMsg->ulMsgName)
              && (ucConnectId == ((SMREG_PDP_ACTIVATE_REQ_STRU *)pstHoldMsg)->ucConnectId) )
            {
                break;
            }

            if ( (ID_SMREG_PDP_DEACTIVATE_REQ == pstHoldMsg->ulMsgName)
              && (ucConnectId == ((SMREG_PDP_DEACTIVATE_REQ_STRU *)pstHoldMsg)->ucConnectId) )
            {
                break;
            }
        }
    }

    if (i < SM_MAX_NSAPI_NUM)
    {
        SM_ComClearPdpCntxt(i);
        SM_Free(g_SmEntity.aHoldMsg[i].pHoldRcvMsg);
        g_SmEntity.aHoldMsg[i].pHoldRcvMsg = SM_NULL;
    }

    return;
}


VOS_VOID NAS_SM_RcvTafPdpAbortReq(
    SMREG_PDP_ABORT_REQ_STRU           *pstPdpAbortReq
)
{
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucPdpCtxIndex;
    VOS_UINT8                           ucAddrIndex;
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo;

    /* 根据ConnectId提取CR(PDPID) */
    ucCr            = pstPdpAbortReq->ucConnectId;

    /* 获取TI对应的PDP CONTEXT索引 */
    ucPdpCtxIndex   = NAS_SM_GetNsapiFromCrMap(ucCr);

    /* 检查PDP CONTEXT索引有效性 */
    if (0xFF == ucPdpCtxIndex)
    {
        /* 清除缓存的消息 */
        NAS_SM_ClearHoldMsgByConnectId(pstPdpAbortReq->ucConnectId);

        /* 刷新SM注册状态和停止定时器 */
        NAS_SM_StopRegisterProcedure();

        NAS_SM_EndSession();

        return;
    }

    /* 获取当前PDP CONTEXT内容地址 */
    pstPdpCtxInfo   = NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex);

    /* 获取PDP ADDRESS索引 */
    ucAddrIndex     = NAS_SM_GetPdpAddrIndex(ucPdpCtxIndex);

    switch (pstPdpCtxInfo->ucState)
    {
        case SM_PDP_ACTIVE_PENDING:
        case SM_PDP_INACTIVE_PENDING:

            /* 将SM实体状态置为INACTIVE */
            pstPdpCtxInfo->ucState  = SM_PDP_INACTIVE;

            /* 清除TI与PDP INDEX的映射关系 */
            NAS_SM_ClearNsapiToTiMap(pstPdpCtxInfo->ucTi);

            /* 清除CR与PDP INDEX的映射关系 */
            NAS_SM_ClearNsapiToCrMap(ucCr);

            /* 清除对应的PDP实体信息 */
            SM_ComClearPdpCntxt(ucPdpCtxIndex);
            SM_ComDelNsapiFromAddr(ucAddrIndex, ucPdpCtxIndex);

            /* 通知GMM更新PDP CONTEXT状态 */
            NAS_SM_SndGmmPdpStatusInd();

            /* 通知RABM更新状态 */
            SM_SndRabmSmDeactivateInd(1, &ucPdpCtxIndex);

            /* 通知GMM清除SM缓存 */
            NAS_SM_SndGmmAbortReq();

            NAS_SM_SndGmmPdpDeactivatedInd();

            break;

        case SM_PDP_MODIFY_PENDING:

            /* 将SM实体状态置为ACTIVE */
            pstPdpCtxInfo->ucState  = SM_PDP_ACTIVE;

            SM_TimerStop(ucPdpCtxIndex);

            break;

        case SM_PDP_ACTIVE:

             /* 将SM实体状态置为INACTIVE */
            pstPdpCtxInfo->ucState  = SM_PDP_INACTIVE;

            /* 清除TI与PDP INDEX的映射关系 */
            NAS_SM_ClearNsapiToTiMap(pstPdpCtxInfo->ucTi);

            /* 清除CR与PDP INDEX的映射关系 */
            NAS_SM_ClearNsapiToCrMap(ucCr);

            /* 清除对应的PDP实体信息 */
            SM_ComClearPdpCntxt(ucPdpCtxIndex);
            SM_ComDelNsapiFromAddr(ucAddrIndex, ucPdpCtxIndex);

            /* 通知GMM更新PDP CONTEXT状态 */
            NAS_SM_SndGmmPdpStatusInd();
            NAS_SM_SndGmmPdpDeactivatedInd();

            /* 通知RABM更新状态 */
            SM_SndRabmSmDeactivateInd(1, &ucPdpCtxIndex);

            break;

        default:
            NAS_NORMAL_LOG(WUEPS_PID_SM,
                "NAS_SM_RcvTafPdpAbortReq: Wrong state!");
            break;
    }

    NAS_SM_EndSession();

    return;
}


VOS_VOID NAS_SM_RcvTafPdpLocalDeactivateReq(
    SMREG_PDP_LOCAL_DEACTIVATE_REQ_STRU    *pstPdpLocalDeactivateReq
)
{
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucPdpCtxIndex;
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo;
    VOS_UINT8                           ucAddrIndex;

    /* 根据ConnectId提取CR(PDPID) */
    ucCr            = pstPdpLocalDeactivateReq->ucConnectId;

    /* 获取TI对应的PDP CONTEXT索引 */
    ucPdpCtxIndex   = NAS_SM_GetNsapiFromCrMap(ucCr);

    /* 检查PDP CONTEXT索引有效性 */
    if (0xFF == ucPdpCtxIndex)
    {
        return;
    }

    /* 获取当前PDP CONTEXT内容地址 */
    pstPdpCtxInfo   = NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex);

    /* 将SM实体状态置为INACTIVE */
    pstPdpCtxInfo->ucState  = SM_PDP_INACTIVE;

    /* 获取PDP ADDRESS索引 */
    ucAddrIndex     = NAS_SM_GetPdpAddrIndex(ucPdpCtxIndex);

    /* 清除TI与PDP INDEX的映射关系 */
    NAS_SM_ClearNsapiToTiMap(pstPdpCtxInfo->ucTi);

    /* 清除CR与PDP INDEX的映射关系 */
    NAS_SM_ClearNsapiToCrMap(ucCr);

    /* 清除对应的PDP实体信息 */
    SM_ComClearPdpCntxt(ucPdpCtxIndex);
    SM_ComDelNsapiFromAddr(ucAddrIndex, ucPdpCtxIndex);

    /* 通知GMM更新PDP CONTEXT状态 */
    NAS_SM_SndGmmPdpStatusInd();

    /* 通知RABM更新状态 */
    SM_SndRabmSmDeactivateInd(1, &ucPdpCtxIndex);

    /* 通知GMM清除SM缓存 */
    NAS_SM_SndGmmAbortReq();

    NAS_SM_SndGmmPdpDeactivatedInd();

    NAS_SM_EndSession();
    return;
}


VOS_VOID NAS_SM_BeginSession(VOS_VOID)
{
    SM_ENTITY_STRU                     *pstSmEntity = VOS_NULL_PTR;

    pstSmEntity = NAS_SM_GetSmEntity();

    pstSmEntity->ulSessionBeginFlg = PS_TRUE;
    NAS_SM_SndGmmBeginSessionNotify(GMMSM_SESSION_TYPE_SUBSCRIB_TRAFFIC_CALL);

    return;
}


VOS_VOID NAS_SM_EndSession(VOS_VOID)
{
    SM_ENTITY_STRU                     *pstSmEntity = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstSmEntity = NAS_SM_GetSmEntity();

    /* 检查当前是否有信令流程存在 */
    for (i = 0; i < SM_MAX_NSAPI_NUM; i++)
    {
        if ( (VOS_NULL_PTR != pstSmEntity->aHoldMsg[i].pHoldRcvMsg)
          || (SM_PDP_ACTIVE_PENDING == pstSmEntity->aPdpCntxtList[i].ucState)
          || (SM_PDP_INACTIVE_PENDING == pstSmEntity->aPdpCntxtList[i].ucState)
          || (SM_PDP_MODIFY_PENDING == pstSmEntity->aPdpCntxtList[i].ucState)
          || (SM_PDP_NW_MODIFY == pstSmEntity->aPdpCntxtList[i].ucState) )
        {
            return;
        }
    }

    /* 释放资源 */
    if (PS_TRUE == pstSmEntity->ulSessionBeginFlg)
    {
        pstSmEntity->ulSessionBeginFlg = PS_FALSE;
        NAS_SM_SndGmmEndSessionNotify(GMMSM_SESSION_TYPE_SUBSCRIB_TRAFFIC_CALL);
    }

    return;
}




/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

