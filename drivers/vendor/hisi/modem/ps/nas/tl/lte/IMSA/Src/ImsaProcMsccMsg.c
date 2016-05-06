/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaProcMsccMsg.c
  Description     : 该C文件实现MSCC消息处理和MSCC消息发送
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact
     2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "PsTypeDef.h"
#include "ImsaProcMsccMsg.h"
#include "ImsaEntity.h"
#include "ImsaPublic.h"
#include "ImsaServiceManagement.h"
#include "ImsaImsAdaption.h"
#include "ImsaMain.h"
#include "ImsaImsApi.h"
#include "ImsaProcSpmMsg.h"
#include "ImsaConnManagement.h"


/*lint -e767*/
#define    THIS_FILE_ID       PS_FILE_ID_IMSAPROCMSCCMSG_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/


/*****************************************************************************
  3 Function
*****************************************************************************/

/*lint -e961*/
/*****************************************************************************
 Function Name  : IMSA_ProcMsccMsg()
 Description    : MSCC消息处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_ProcMsccMsg(const VOS_VOID *pRcvMsg )
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_MSCC_IMSA_START_REQ:
            IMSA_ProcMsccMsgStartReq();
            break;

        case ID_MSCC_IMSA_STOP_REQ:
            IMSA_ProcMsccMsgStopReq(pRcvMsg);
            break;

        case ID_MSCC_IMSA_DEREG_REQ:
            IMSA_ProcMsccMsgDeregReq();
            break;

        case ID_MSCC_IMSA_SERVICE_CHANGE_IND:
            IMSA_ProcMsccMsgServiceChangeInd(pRcvMsg);
            break;

        case ID_MSCC_IMSA_CAMP_INFO_CHANGE_IND:
            IMSA_ProcMsccMsgCampInfoChangeInd(pRcvMsg);
            break;
        case ID_MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND:
            IMSA_ProcMsccMsgVoiceDomainChangeInd(pRcvMsg);
            break;
        default:
            break;
    }
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsccMsgStartReq()
 Description    : MSCC开机消息处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_ProcMsccMsgStartReq(VOS_VOID  )
{
    IMSA_CONTROL_MANAGER_STRU  *pstControlManager;
    static VOS_UINT8            ucD2ImsTaskStart = 0;

    pstControlManager = IMSA_GetControlManagerAddress();

    if(ucD2ImsTaskStart == 0)
    {
        /*初始化D2协议栈*/
        (VOS_VOID)IMSA_ImsInit();

        ucD2ImsTaskStart ++;
    }

    /*判断开机状态，如果已开机，则回复开机成功*/
    if(pstControlManager->enImsaStatus == IMSA_STATUS_STARTED)
    {
        IMSA_SndMsccMsgStartCnf();
        return;
    }

    /*已处于开机过程状态，则丢弃*/
    if(pstControlManager->enImsaStatus == IMSA_STATUS_STARTING)
    {
        IMSA_WARN_LOG("IMSA_ProcMsccMsgStartReq: Status is Starting!");
        TLPS_PRINT2LAYER_WARNING(IMSA_ProcMsccMsgStartReq_ENUM, IMSA_PRINT_STATUS_STARTING);
        return;
    }

    IMSA_StopTimer(&pstControlManager->stProtectTimer);

    /*初始化*/

    /*读取NV*/
    IMSA_ReadImsaNV();

    /*通知IMS开机，转状态*/
    pstControlManager->enImsaStatus = IMSA_STATUS_STARTING;

    IMSA_SndImsMsgStartReq();

    IMSA_StartTimer(&pstControlManager->stProtectTimer);

    /*卡在位，则读取卡信息*/
    if(pstControlManager->enImsaIsimStatus == IMSA_ISIM_STATUS_AVAILABLE)
    {
        IMSA_INFO_LOG("IMSA_ProcMsccMsgStartReq: ISIM is available!");
        TLPS_PRINT2LAYER_INFO(IMSA_ProcMsccMsgStartReq_ENUM, 2);
        IMSA_ReadIsimFile();
    }
}

/*****************************************************************************
 Function Name  : IMSA_SndMsccMsgStartCnf()
 Description    : 给MSCC发送开机回复消息
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-26  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_SndMsccMsgStartCnf(VOS_VOID  )
{
    IMSA_MSCC_START_CNF_STRU           *pstImsaMsccStartCnf;

    /*分配空间并检验分配是否成功*/
    pstImsaMsccStartCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_MSCC_START_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstImsaMsccStartCnf)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SndMsccMsgStartCnf:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndMsccMsgStartCnf_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstImsaMsccStartCnf),
                    IMSA_GET_MSG_LENGTH(pstImsaMsccStartCnf),
                    0,
                    IMSA_GET_MSG_LENGTH(pstImsaMsccStartCnf));

    /*填写消息头*/
    IMSA_WRITE_MSCC_MSG_HEAD(pstImsaMsccStartCnf, ID_IMSA_MSCC_START_CNF);

    /*调用消息发送函数 */
    IMSA_SND_MSG(pstImsaMsccStartCnf);
}




/*****************************************************************************
 Function Name  : IMSA_ProcMsccMsgStopReq()
 Description    : MSCC关机消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_ProcMsccMsgStopReq
(
    const VOS_VOID                     *pRcvMsg
)
{
    IMSA_CONTROL_MANAGER_STRU *pstControlManager;

    MSCC_IMSA_STOP_REQ_STRU            *pstMsccImsaStopReq = VOS_NULL_PTR;

    pstMsccImsaStopReq = (MSCC_IMSA_STOP_REQ_STRU*) pRcvMsg;
    IMSA_INFO_LOG("IMSA_ProcMsccMsgStopReq: enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcMsccMsgStopReq_ENUM, LNAS_ENTRY);

    pstControlManager = IMSA_GetControlManagerAddress();

    /* SRVCC异常(例如关机，DEREG REQ，状态迁离CONN+REG)，清缓存 */
    IMSA_SrvccAbormalClearBuff(IMSA_SRVCC_ABNORMAL_STOP_REQ);

    /*判断状态，如果已关机，则回复关机成功*/
    if(pstControlManager->enImsaStatus == IMSA_STATUS_NULL)
    {
        IMSA_SndMsccMsgStopCnf();
        return;
    }

    /*已处于关机状态，则丢弃*/
    if(pstControlManager->enImsaStatus == IMSA_STATUS_STOPING)
    {
        IMSA_WARN_LOG("IMSA_ProcMsccMsgStopReq: Status is Stoping!");
        TLPS_PRINT2LAYER_WARNING(IMSA_ProcMsccMsgStopReq_ENUM, IMSA_PRINT_STATUS_STOPING);
        return;
    }

    /*停止开关机保护定时器*/
    IMSA_StopTimer(&pstControlManager->stProtectTimer);
    /* 记录关机请求类型。如果关机请求类型是ims动态关闭，则需要在收到IMS关机结果后释放现有承载 */
    pstControlManager->enStopType = pstMsccImsaStopReq->enStopType;

    /*通知IMS关机，转状态*/
    pstControlManager->enImsaStatus = IMSA_STATUS_STOPING;

    /*关机后，卡在位时，需要将卡状态置为有效，因为可能有卡无效的场景，需要关机后清除状态*/
    if(pstControlManager->enImsaIsimStatus != IMSA_ISIM_STATUS_ABSENT)
    {
        pstControlManager->enImsaIsimStatus = IMSA_ISIM_STATUS_AVAILABLE;
    }

    /*启动开关机保护定时器*/
    IMSA_StartTimer(&pstControlManager->stProtectTimer);

    /* 如果当前状态时IDLE+DEREG，则直接通知IMS关机，不需要申请资源 */
    #if (FEATURE_ON == FEATURE_DSDS)
    if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
    {
        if (IMSA_TRUE == IMSA_SRV_IsNotNeedNwDereg())
        {
            IMSA_SndImsMsgStopReq();
            return;
        }
    }
    #endif
    /* 需要根据当前的注册状态，判断是否需要申请资源 */
    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:

            IMSA_SndImsMsgStopReq();
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF,
                                                 RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF,
                                          VOS_FALSE,
                                          VOS_FALSE);

            IMSA_SndImsMsgStopReq();
            break;

        case  IMSA_RESOURCE_STATUS_NULL:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF,
                                          VOS_FALSE,
                                          VOS_FALSE);

            //IMSA_DsdsSaveMoSmsMsg(pstRpDataReq);
            break;

        case IMSA_RESOURCE_STATUS_APPLYING:
            /* 如果当前状态为pending，则取消任务的注册，然后通知IMS本地去注册，然后直接关机 */
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_POWER_OFF,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            break;

        case IMSA_RESOURCE_STATUS_WAIT_STATUS_IND:

            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

            IMSA_SRV_ProcStopMsgWhenNoRf();

            IMSA_SndImsMsgStopReq();
            break;
        #endif
        default:
            break;
    }

    //IMSA_SndImsMsgStopReq();
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsccMsgStopReq()
 Description    : MSCC关机消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_ProcStopResourceApplyCnf
(
    VOS_VOID
)
{
    IMSA_SndImsMsgStopReq();
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsccMsgStopReq()
 Description    : MSCC关机消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_ProcStopResourceApplyTimerExp
(
    VOS_VOID
)
{
    /* 先通知IMS本地去注册 */
    IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREG);

    /* 然后在通知关机 */
    IMSA_SndImsMsgStopReq();

}


/*****************************************************************************
 Function Name  : IMSA_SndMsccMsgStopCnf()
 Description    : 给MSCC发送开机回复消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_SndMsccMsgStopCnf(VOS_VOID  )
{
    IMSA_MSCC_STOP_CNF_STRU           *pstImsaMsccStopCnf;

    IMSA_INFO_LOG("IMSA_SndMsccMsgStopCnf:enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_SndMsccMsgStopCnf_ENUM, LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstImsaMsccStopCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_MSCC_STOP_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstImsaMsccStopCnf)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SndMsccMsgStopCnf:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndMsccMsgStopCnf_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstImsaMsccStopCnf),
                    IMSA_GET_MSG_LENGTH(pstImsaMsccStopCnf),
                    0,
                    IMSA_GET_MSG_LENGTH(pstImsaMsccStopCnf));

    /*填写消息头*/
    IMSA_WRITE_MSCC_MSG_HEAD(pstImsaMsccStopCnf, ID_IMSA_MSCC_STOP_CNF);

    /*调用消息发送函数 */
    IMSA_SND_MSG(pstImsaMsccStopCnf);
}



/*****************************************************************************
 Function Name  : IMSA_ProcMsccMsgDeregReq()
 Description    : MSCC去注册消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_ProcMsccMsgDeregReq(VOS_VOID )
{
    /* SRVCC异常(例如关机，DEREG REQ，状态迁离CONN+REG)，清缓存 */
    IMSA_SrvccAbormalClearBuff(IMSA_SRVCC_ABNORMAL_DEREG_REQ);

    IMSA_SRV_ProcDeregReq(IMSA_SRV_DEREG_CAUSE_MSCC_DEREG_REQ);

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsccMsgDeregReq()
 Description    : MSCC SERVICE CHANGE IND消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_ProcMsccMsgServiceChangeInd
(
    const VOS_VOID                     *pRcvMsg
)
{
    IMSA_SRV_ProcServiceChangeInd((MSCC_IMSA_SERVICE_CHANGE_IND_STRU*)pRcvMsg);

    return ;
}

/*****************************************************************************
 Description    : MMA RAOMING CHANGE IND消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-27  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_ProcMsccMsgCampInfoChangeInd
(
    const VOS_VOID                     *pRcvMsg
)
{
    IMSA_SRV_ProcCampInfoChangeInd((MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU*)pRcvMsg);

    return ;
}


/*****************************************************************************
 Function Name  : IMSA_SndMsccMsgDeregCnf()
 Description    : 给MSCC发送去注册回复消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-26  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_SndMsccMsgDeregCnf(VOS_VOID )
{
    IMSA_MSCC_DEREGISTER_CNF_STRU           *pstImsaMsccDeregCnf;

    /*分配空间并检验分配是否成功*/
    pstImsaMsccDeregCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_MSCC_DEREGISTER_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstImsaMsccDeregCnf)
    {
        /*打印异常信息*/
        IMSA_ERR_LOG("IMSA_SndMsccMsgDeregCnf:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndMsccMsgDeregCnf_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstImsaMsccDeregCnf),
                    IMSA_GET_MSG_LENGTH(pstImsaMsccDeregCnf),
                    0,
                    IMSA_GET_MSG_LENGTH(pstImsaMsccDeregCnf));

    /*填写消息头*/
    IMSA_WRITE_MSCC_MSG_HEAD(pstImsaMsccDeregCnf, ID_IMSA_MSCC_DEREG_CNF);

    /*调用消息发送函数 */
    IMSA_SND_MSG(pstImsaMsccDeregCnf);
}
/*****************************************************************************
 Description    : MMA VOICE DOMAIN CHANGE IND消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-02-26  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcMsccMsgVoiceDomainChangeInd
(
    const VOS_VOID                     *pRcvMsg
)
{
    IMSA_SRV_ProcVoiceDomainChangeInd((MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU*)pRcvMsg);

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_ProcImsMsgStartOrStopCnf()
 Description    : 处理IMS开机或者关机结果
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-24  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_ProcImsMsgStartOrStopCnf(VOS_VOID)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlManager;
    IMSA_NORMAL_CONN_STRU              *pstNormalConn      = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn         = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid             = IMSA_NULL;
    VOS_UINT32                          ulLoop             = IMSA_NULL;

    IMSA_NORM_LOG("IMSA_ProcImsMsgStartOrStopCnf: Enter!");
    TLPS_PRINT2LAYER_ERROR(IMSA_ProcImsMsgStartOrStopCnf_ENUM, LNAS_ENTRY);

    pstControlManager = IMSA_GetControlManagerAddress();

    /*停止开关机保护定时器*/
    IMSA_StopTimer(&pstControlManager->stProtectTimer);

    /*关机流程*/
    if(pstControlManager->enImsaStatus == IMSA_STATUS_STOPING)
    {
        /* 如果是IMS动态关闭类型的关机，则释放链接 */
        if (pstControlManager->enStopType == MSCC_IMSA_STOP_TYPE_IMS_SWITCH_OFF)
        {
            pstEmcConn      = IMSA_CONN_GetEmcConnAddr();
            if (IMSA_CONN_STATUS_IDLE != pstEmcConn->enImsaConnStatus)
            {
                /* 请求APS释放连接 */
                IMSA_WARN_LOG("IMSA_ProcImsMsgStartOrStopCnf:releasing emc conn!");
                TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgStartOrStopCnf_ENUM, IMSA_EMERGENCY);
                /* 如果在CONNING态，则请求释放正在建立的信令承载和已经激活的信令承载 */
                if (IMSA_CONN_STATUS_CONNING == pstEmcConn->enImsaConnStatus)
                {
                    /* 产生OPID并存储 */
                    IMSA_CONN_AssignOpid(IMSA_CONN_TYPE_EMC, &ucOpid);
                    if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                                    pstEmcConn->stSelSdfPara.ucCid))
                    {
                        IMSA_WARN_LOG("IMSA_ProcImsMsgStartOrStopCnf:EMC,conninig,CallEnd failed!");
                        TLPS_PRINT2LAYER_ERROR1(IMSA_ProcImsMsgStartOrStopCnf_ENUM, IMSA_CALL_API_ERROR, 1);
                    }
                }

                else
                {
                    /* 产生OPID并存储 */
                    IMSA_CONN_AssignOpid(IMSA_CONN_TYPE_EMC, &ucOpid);

                    if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                                    (VOS_UINT8)pstEmcConn->stSipSignalPdp.ucCid))
                    {
                        IMSA_WARN_LOG("IMSA_ProcImsMsgStartOrStopCnf:IMS Swtich off,conn,CallEnd failed!");
                        TLPS_PRINT2LAYER_ERROR1(IMSA_ProcImsMsgStartOrStopCnf_ENUM, IMSA_CALL_API_ERROR, 2);
                    }
                    IMSA_CONN_SndCdsSetImsBearerReq();
                }
            }
            pstNormalConn      = IMSA_CONN_GetNormalConnAddr();
            if (IMSA_CONN_STATUS_IDLE != pstNormalConn->enImsaConnStatus)
            {
                /* 请求APS释放连接 */
                IMSA_WARN_LOG("IMSA_ProcImsMsgStartOrStopCnf:releasing normal conn!");
                TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgStartOrStopCnf_ENUM, IMSA_NORMAL);
                /* 如果在CONNING态，则请求释放正在建立的信令承载和已经激活的信令承载 */
                if (IMSA_CONN_STATUS_CONNING == pstNormalConn->enImsaConnStatus)
                {
                    /* 产生OPID并存储 */
                    IMSA_CONN_AssignOpid(IMSA_CONN_TYPE_NORMAL, &ucOpid);

                    if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                                    pstNormalConn->stSelSdfPara.ucCid))
                    {
                        IMSA_WARN_LOG("IMSA_ProcImsMsgStartOrStopCnf:IMS Swtich off,normal,conninig,CallEnd failed!");
                        TLPS_PRINT2LAYER_ERROR1(IMSA_ProcImsMsgStartOrStopCnf_ENUM, IMSA_CALL_API_ERROR, 3);
                    }
                }

                if (0 == pstNormalConn->ulSipSignalPdpNum)
                {
                    IMSA_WARN_LOG("IMSA_ProcImsMsgStartOrStopCnf:IMS Swtich off,normal,conning,no active pdp!");
                    TLPS_PRINT2LAYER_ERROR(IMSA_ProcImsMsgStartOrStopCnf_ENUM, IMSA_NO_ACTIVE_PDP);
                }
                else
                {
                    /* 如果建立了多个承载，需要逐个释放 */
                    for (ulLoop = 0 ; ulLoop < pstNormalConn->ulSipSignalPdpNum ; ulLoop ++)
                    {
                        /* 产生OPID并存储 */
                        IMSA_CONN_AssignOpid(IMSA_CONN_TYPE_NORMAL, &ucOpid);
                        if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                                    pstNormalConn->astSipSignalPdpArray[ulLoop].ucCid))
                        {
                            IMSA_WARN_LOG("IMSA_ProcImsMsgStartOrStopCnf:IMS Swtich off,normal,CallEnd failed!");
                            TLPS_PRINT2LAYER_ERROR1(IMSA_ProcImsMsgStartOrStopCnf_ENUM, IMSA_CALL_API_ERROR, 4);
                        }
                    }
                    IMSA_CONN_SndCdsSetImsBearerReq();
               }
            }
        }
        /*清除资源*/
        IMSA_ClearResource();

        /*进入等待开机状态*/
        pstControlManager->enImsaStatus = IMSA_STATUS_NULL;

        IMSA_SndMsccMsgStopCnf();
    }
    else if(pstControlManager->enImsaStatus == IMSA_STATUS_STARTING)
    {
        /*进入开机状态*/
        pstControlManager->enImsaStatus = IMSA_STATUS_STARTED;

        IMSA_SndMsccMsgStartCnf();

        /* 给IMS配置UE能力 */
        IMSA_ConfigUeCapabilityInfo2Ims();

        if ((IMSA_OP_TRUE == pstControlManager->stImsaCommonInfo.stImsaUeId.bitOpImpi)
            && (IMSA_OP_TRUE == pstControlManager->stImsaCommonInfo.stImsaUeId.bitOpTImpu)
            && (IMSA_OP_TRUE == pstControlManager->stImsaCommonInfo.bitOpHomeNetDomainName))
        {
            /* config account info to ims */
            IMSA_ConfigAccoutInfo2Ims(IMSA_REG_TYPE_NORMAL);

            /* config account info to ims */
            IMSA_ConfigAccoutInfo2Ims(IMSA_REG_TYPE_EMC);
        }

        /* set imei */
        IMSA_ConfigImei2Ims();

        /* set retry time */
        IMSA_ConfigTimerLength2Ims();

        IMSA_ConfigSipPort2Ims();

        /* 给IMS配置SIP信息 */
        IMSA_ConfigSipInfo2Ims();

        IMSA_ConfigVoipInfo2Ims();

        IMSA_ConfigCodeInfo2Ims();

        IMSA_ConfigSsConfInfo2Ims();

        IMSA_ConfigSecurityInfo2Ims();

        IMSA_ConfigMediaParmInfo2Ims();

        IMSA_ConfigNvUeCapabilityInfo2Ims();

    }
    else
    {
        IMSA_WARN_LOG("IMSA_ProcImsMsgStartOrStopCnf: err stat!");
        TLPS_PRINT2LAYER_WARNING(IMSA_ProcImsMsgStartOrStopCnf_ENUM, IMSA_STATE_ERROR);
    }


}


 /*****************************************************************************
 Function Name  : IMSA_SndMsccMsgImsVoiceCapNotify()
 Description    : 给MSCC发送ID_IMSA_MSCC_IMS_VOICE_CAP_NOTIFY消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.l00132387      2013-12-17  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
 VOS_VOID IMSA_SndMsccMsgImsVoiceCapNotify
 (
    MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8   enImsVoiceCap,
    VOS_UINT32                          ucIsExistPersistentBearer
 )
 {
     IMSA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU     *pstImsaMsccImsVoiceCap;

     /*分配空间并检验分配是否成功*/
     pstImsaMsccImsVoiceCap = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU));

     /*检测是否分配成功*/
     if (VOS_NULL_PTR == pstImsaMsccImsVoiceCap)
     {
         /*打印异常信息*/
         IMSA_ERR_LOG("IMSA_SndMsccMsgImsVoiceCapNotify:ERROR:Alloc Msg fail!");
         TLPS_PRINT2LAYER_ERROR(IMSA_SndMsccMsgImsVoiceCapNotify_ENUM, LNAS_NULL_PTR);
         return ;
     }

     /*清空*/
     IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstImsaMsccImsVoiceCap),
                     IMSA_GET_MSG_LENGTH(pstImsaMsccImsVoiceCap),
                     0,
                     IMSA_GET_MSG_LENGTH(pstImsaMsccImsVoiceCap));

     /*填写消息头*/
     IMSA_WRITE_MSCC_MSG_HEAD(pstImsaMsccImsVoiceCap, ID_IMSA_MSCC_IMS_VOICE_CAP_NOTIFY);


     pstImsaMsccImsVoiceCap->enImsVoiceCap = enImsVoiceCap;

    pstImsaMsccImsVoiceCap->ucIsExistPersistentBearer = (VOS_UINT8)ucIsExistPersistentBearer;

    /*调用消息发送函数 */
     IMSA_SND_MSG(pstImsaMsccImsVoiceCap);
 }

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 Function Name  : IMSA_ProcTimerMsgWaitPowerOffRfExp()
 Description    : 等待关机资源定时器超时的处理
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-12-08  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcTimerMsgWaitPowerOffRfExp(const VOS_VOID *pRcvMsg)
{
    /* 通知RRM模块释放资源 */
    IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

    /* 需要先根据当前的注册状态，通知IMS本地去注册，然后再通知IMS关机 */
    IMSA_SRV_ProcStopMsgWhenNoRf();
    IMSA_SndImsMsgStopReq();
}
#endif
/*lint +e961*/


#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaProcMmaMsg.c */



