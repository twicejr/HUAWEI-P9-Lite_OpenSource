/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEmmMrrcConnEst.c
    Description : 定义了EMM-MRRC模块在上行数据过程中处理RRC连接建立
                  或在已经建立的RRC链路上发送上行数据的过程
    History     :
      1.  zangyalan 57968  2008-09-10  Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasEmmGIMComm.h"
#include  "NasEmmMrrc.h"
#include  "NasEmmAttDetInclude.h"
#if (FEATURE_LPP == FEATURE_ON)
#include  "NasEmmLppMsgProc.h"
#include  "NasEmmSsMsgProc.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMMRRCCONNEST_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMMRRCCONNEST_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

NAS_EMM_MRRC_MGMT_DATA_STRU     g_stEmmMrrcMgmtData[NAS_LMM_RRC_SAVE_MSG_MAX_NUM];

VOS_UINT32              g_ulSaveMsgNum = 0;

static  VOS_UINT32              gulMmRrcOpId = 0;


/*RRC发送上行直传NAS消息结果处理表 */
NAS_LMM_SEND_MSG_RESULT_ACT_STRU  gstEmmMrrcSendMsgResultActTbl[]=
{
    {NAS_EMM_MSG_ATTACH_REQ,                NAS_EMM_SndAttachReqFailProc,           VOS_NULL_PTR},
    {NAS_EMM_MSG_ATTACH_CMP,                NAS_EMM_SndAttachCmpFailProc,           NAS_EMM_SndAttachCmpSuccProc},
    {NAS_EMM_MSG_DETACH_REQ,                NAS_EMM_SndDetachReqFailProc,           NAS_EMM_SndDetachReqSuccProc},
    {NAS_EMM_MSG_DETACH_ACP,                NAS_EMM_SndMtDetachAccFailProc,         VOS_NULL_PTR},
    {NAS_EMM_MSG_LOAD_BALANCING_TAU,        NAS_EMM_SndTauReqFailProc,              VOS_NULL_PTR},
    {NAS_EMM_MSG_NOT_LOAD_BALANCING_TAU,    NAS_EMM_SndTauReqFailProc,              VOS_NULL_PTR},
    {NAS_EMM_MSG_TAU_CMP,                   NAS_EMM_SndTauCompleteFailProc,         NAS_EMM_SndTauCmpSuccProc},
    {NAS_EMM_MSG_SMC_COMPL,                 NAS_EMM_SndCommonProcedureMsgFailProc,  VOS_NULL_PTR},
    {NAS_EMM_MAS_SMC_REJ,                   NAS_EMM_SndCommonProcedureMsgFailProc,  VOS_NULL_PTR},
    {NAS_EMM_MSG_AUTH_RSP,                  NAS_EMM_SndCommonProcedureMsgFailProc,  VOS_NULL_PTR},
    {NAS_EMM_MSG_AUTH_FAIL,                 NAS_EMM_SndCommonProcedureMsgFailProc,  VOS_NULL_PTR},
    {NAS_EMM_MSG_IDEN_RSP,                  NAS_EMM_SndCommonProcedureMsgFailProc,  VOS_NULL_PTR},
    {NAS_EMM_NAS_UPLINK_NAS_TRANSPORT,      NAS_EMM_SndSmsdataFailProc,             VOS_NULL_PTR},
    {NAS_EMM_MSG_GUTI_CMP,                  NAS_EMM_SndCommonProcedureMsgFailProc,  VOS_NULL_PTR},
    {NAS_EMM_MSG_SERVICE_REQ,               NAS_EMM_SndServiceReqFailProc,          VOS_NULL_PTR},
    {NAS_EMM_MSG_EXTENDED_SERVICE_REQ,      NAS_EMM_SndExtendedServiceReqFailProc,  NAS_EMM_SndExtendedServiceReqSuccProc},
    #if (FEATURE_LPP == FEATURE_ON)
    {NAS_EMM_NAS_UPLINK_GENERIC_NAS_TRANSPORT, NAS_EMM_SndUplinkGenericTransportFailProc, NAS_EMM_SndUplinkGenericTransportSuccProc},
    #endif
    {NAS_EMM_MSG_ESM,                       NAS_EMM_SndEsmMsgFailProc,              NAS_EMM_SndEsmMsgSuccProc}
};
VOS_UINT32        g_ulSendMsgResultActTblLen = sizeof(gstEmmMrrcSendMsgResultActTbl)
                                                / sizeof(NAS_LMM_SEND_MSG_RESULT_ACT_STRU);
/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_EMM_MrrcInit
 Discription    : MRRC模块初始化函数
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968 2008-10-16  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_MrrcInit(VOS_VOID)
{
    /*调用建链和释放链路模块的初始化函数 */
    NAS_EMM_MrrcEstInit();
    NAS_EMM_MrrcRelInit();
    NAS_EMM_MrrcMgmtDataInit();
    NAS_EMM_INIT_MM_RRC_OPID();
    return;
}


VOS_VOID  NAS_EMM_FreeMrrcDyn( VOS_VOID )
{
    /* 暂时为空 */
    return;
}


/*****************************************************************************
 Function Name  : NAS_EMM_MrrcEstInit
 Discription    : MRRC 建链模块初始化函数
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968 2008-10-16  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_MrrcEstInit(VOS_VOID)
{
    /*清资源*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);

    return;
}
/*****************************************************************************
 Function Name  : NAS_EMM_MrrcConnectFailInd
 Discription    : 发送内部消息MRRC_CONNECT_FAIL_IND
 Input          :
 Output         : None
 Return         : None
 History:
      1.zangyalan   57968    2008-09-23  Draft Enact
      2.zhengjunyan 00148421 2009.03.09  add rel cause
      3.X00148705            2009-09-23  修改为转发内部的CONNECT_FAIL
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_EMM_MrrcConnectFailInd(LRRC_LNAS_EST_RESULT_ENUM_UINT32 enEstResult)
{
    NAS_EMM_MRRC_CONNECT_FAIL_IND_STRU            *pstMrrcConnectFailIndMsg;
    VOS_UINT32                                    ulMsgLen;

    /*计算长度*/
    ulMsgLen  = NAS_EMM_MRRC_CONNECT_FAIL_IND_LEN;

    /*获取内部消息地址*/
    pstMrrcConnectFailIndMsg = (NAS_EMM_MRRC_CONNECT_FAIL_IND_STRU *)NAS_LMM_GetSendIntraMsgBuffAddr(ulMsgLen);
    if(NAS_EMM_NULL_PTR == pstMrrcConnectFailIndMsg)
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_MrrcConnectFailInd: Alloc Msg Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MrrcConnectFailInd_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*打包VOS消息头*/
    NAS_EMM_INTRA_MSG_HEADER(pstMrrcConnectFailIndMsg, ulMsgLen);

    /*赋值消息 ID*/
    pstMrrcConnectFailIndMsg->ulMsgId = ID_NAS_LMM_INTRA_MRRC_CONNECT_FAIL_IND;

    /*赋值连接建立失败的原因*/
    pstMrrcConnectFailIndMsg->enEstResult = enEstResult;

    /* 发送内部消息入队列 */
    NAS_EMM_SEND_INTRA_MSG(             pstMrrcConnectFailIndMsg);

    return;
}

/*****************************************************************************
 Function Name  : NAS_EMM_ChangeRrcConnStateToEstSignal
 Discription    : 把RRC连接状态改为连接状态
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968  2008-11-27  Draft Enact
      2.  zhengjunyan 00148421 2011-5-09 MOD
*****************************************************************************/
VOS_VOID  NAS_EMM_ChangeRrcConnStateToEstSignal( VOS_VOID )
{
    /*判断当前连接状态为NOT_EXIST，则上报MMC进入信令连接态*/
    if(MMC_LMM_CONNECTED_SIG != NAS_EMM_GetConnState())
    {
        NAS_EMM_SendMmcStatusInd(       MMC_LMM_STATUS_TYPE_CONN_STATE,
                                        MMC_LMM_CONNECTED_SIG);
    }

    /*把RRC连接状态改为连接状态*/
    /* coverity[mixed_enums] */
    NAS_EMM_SetConnState(NAS_EMM_CONN_SIG);
}

/*****************************************************************************
 Function Name  : NAS_EMM_ChangeRrcConnStateToEsting
 Discription    : 把RRC连接状态改为连接状态
 Input          :
 Output         : None
 Return         : None
 History:
      1.  leili 00132387  2009-07-08  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ChangeRrcConnStateToEsting( VOS_VOID )
{
    /*判断当前连接状态为NOT_EXIST，则上报MMC进入信令连接态*/
    if(MMC_LMM_CONN_ESTING != NAS_EMM_GetConnState())
    {
        NAS_EMM_SendMmcStatusInd(       MMC_LMM_STATUS_TYPE_CONN_STATE,
                                        MMC_LMM_CONN_ESTING);
    }

    /*把RRC连接状态改为连接状态*/
    /* coverity[mixed_enums] */
    NAS_EMM_SetConnState(NAS_EMM_CONN_ESTING);
}

/*****************************************************************************
 Function Name  : NAS_EMM_ChangeRrcConnStateToEstData
 Discription    : 把RRC连接状态改为连接状态
 Input          :
 Output         : None
 Return         : None
 History:
      1.  leili 00132387  2011-06-16  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ChangeRrcConnStateToEstData( VOS_VOID )
{
    /*判断当前连接状态为DATA，则上报MMC进入数据连接态*/
    if(NAS_EMM_CONN_DATA != NAS_EMM_GetConnState())
    {
        NAS_EMM_SendMmcStatusInd(       MMC_LMM_STATUS_TYPE_CONN_STATE,
                                        MMC_LMM_CONNECTED_DATA);
    }

    /*把RRC连接状态改为连接状态*/
    NAS_EMM_SetConnState( NAS_EMM_CONN_DATA );
}

/*****************************************************************************
 Function Name  : NAS_EMM_SndUplinkNasMsg
 Discription    : 给LRRC发送上行消息
 Input          :
 Output         : None
 Return         : None
 History:
      1.  leili 00132387  2012-09-12  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_SndUplinkNasMsg
(
    VOS_VOID *pMsgStru
)
{
    NAS_EMM_MRRC_DATA_REQ_STRU         *pstMrrcDataRqMsg = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulMmRrcOpId = NAS_LMM_RRC_OPID_NOT_VAILID;

#if(VOS_WIN32 == VOS_OS_VER)
    #ifdef PS_ITT_PC_TEST_NAS_ST
    VOS_UINT32                          ulRslt = VOS_FALSE;
    #endif
#endif

    NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_SndUplinkNasMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SndUplinkNasMsg_ENUM,LNAS_ENTRY);

    /* 入参检查 */
    if ( NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_SndUplinkNasMsg:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndUplinkNasMsg_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* 结构转化 */
    pstMrrcDataRqMsg = (NAS_EMM_MRRC_DATA_REQ_STRU *)pMsgStru;

    /* 打印空口消息 */
    NAS_LMM_PrintCnMsgAndData(           &(pstMrrcDataRqMsg->stNasMsg));

    /* 如果处于释放过程中，不再给RRC发建链消息，改为给自己发内部建链失败 */
    if((NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState()))
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_SndUplinkNasMsg:Releasing,rrc is cell searching,can't est.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndUplinkNasMsg_ENUM,LNAS_EMM_CANT_EST);

        /*发MRRC_CONNECT_FAIL_IND*/
        NAS_EMM_MrrcConnectFailInd(LRRC_EST_CELL_SEARCHING);
        return;
    }




    /* 在做加密和完整性保护之前，如果是信令连接态或者是数据连接态，
    则缓存未加密的上行直传消息,加密会使NAS COUNT加1 */
    if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()) ||
        (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
    {
        ulMmRrcOpId                 = NAS_EMM_MrrcAllocMmRrcOpId();

        NAS_EMM_SaveMrrcDataReqMsg(pstMrrcDataRqMsg, ulMmRrcOpId);
    }

    /* 对空口消息加保护:输入待发送的内部消息*/
    if( NAS_EMM_SMC_OPEN == g_ulSmcControl)
    {
        if(NAS_EMM_FAIL == NAS_EMM_SecuProtect(pstMrrcDataRqMsg))
        {
            NAS_EMM_GIM_ERROR_LOG("NAS_EMM_SndUplinkNasMsg:PROT ERR.");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndUplinkNasMsg_ENUM,LNAS_ERROR);
            return;
        }
    }

    /* 察看RRC连接是否存在 */
    if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()) ||
        (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
    {
        NAS_EMM_RrcDataReq(pstMrrcDataRqMsg, ulMmRrcOpId);
    }
    else if(NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_SndUplinkNasMsg: WAIT_SYS_INFO");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndUplinkNasMsg_ENUM,LNAS_FUNCTION_LABEL1);
    }
    else
    {
        NAS_EMM_IntraEstReq(pstMrrcDataRqMsg);
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_EMM_CcoInterSystemSuccProc
 Discription    : GU->L CCO成功处理
 Input          :
 Output         : None
 Return         : None
 History:
      1.  leili 00132387  2012-03-16  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_CcoInterSystemSuccProc( VOS_VOID )
{
    NAS_MML_PS_BEARER_CONTEXT_STRU  *pstPsBearerCtx = NAS_EMM_NULL_PTR;

    if (NAS_EMM_CCO_CHANGE_TIN_VALID == NAS_LMM_GetEmmInfoTinChagFlag())
    {

        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_CcoInterSystemSuccProc:GET PS BEARER INFO");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_CcoInterSystemSuccProc_ENUM,LNAS_ENTRY);

        pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();
        NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);

        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
        NAS_LMM_SetTempEmmInfoTinType(MMC_LMM_TIN_BUTT);
        NAS_LMM_SetEmmInfoTinChagFlag(NAS_EMM_CCO_CHANGE_TIN_INVALID);


    }
    return;
}

/*****************************************************************************
 Function Name  : NAS_EMM_CcoInterSystemFailProc
 Discription    : GU->L CCO失败处理
 Input          :
 Output         : None
 Return         : None
 History:
      1.  leili 00132387  2012-03-16  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_CcoInterSystemFailProc( VOS_VOID )
{
    NAS_MML_PS_BEARER_CONTEXT_STRU *pstPsBearerCtx;
    pstPsBearerCtx   =  NAS_EMM_GetPsBearerCtx();
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_CcoInterSystemFailProc is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CcoInterSystemFailProc_ENUM,LNAS_ENTRY);

    if (NAS_EMM_CCO_CHANGE_TIN_VALID == NAS_LMM_GetEmmInfoTinChagFlag())
    {
        NAS_EMM_SetTinType(NAS_LMM_GetTempEmmInfoTinType());
        NAS_LMM_SetTempEmmInfoTinType(MMC_LMM_TIN_BUTT);
        NAS_LMM_SetEmmInfoTinChagFlag(NAS_EMM_CCO_CHANGE_TIN_INVALID);

        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_CcoInterSystemFailProc: UPDATE MML PS BEARER INFO:");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_CcoInterSystemFailProc_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
    }

    return;
}



/*****************************************************************************
 Function Name  : NAS_EMM_PreProcMsgRrcMmEstCnf
 Discription    : EMM在需要建链的场景下，状态收到RRC_MM_EST_CNF时,
                  使用该函数处理。
 Input          : 消息
 Output         : None
 Return         : None
 History:
      1.zangyalan   57968    2008-09-10  Draft Enact
      2.zhengjunyan 00148421 2009.03.09  access barred
      3.lifuxin     00253982 2014.10.28  LNAS建链流程重构
      4.leixiantiao 00258641 2015-07-09  fix DTS2015062509266
*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgRrcMmEstCnf(MsgBlock * pMsg)
{
    LRRC_LMM_EST_CNF_STRU                *pstEstCnfMsg;
    VOS_UINT32                           ulResult;

    NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_PreProcMsgRrcMmEstCnf is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcMmEstCnf_ENUM,LNAS_ENTRY);

    /* sunbing 00265702 begin for DTS2015100600547 关机不等网络释放*/
    /* delete 无用的入参检查 */
    /* sunbing 00265702 end for DTS2015100600547 关机不等网络释放*/
    /*检查建链是否成功*/

    pstEstCnfMsg = (VOS_VOID *)pMsg;
    ulResult = pstEstCnfMsg->enResult;

    /*问题背景:主叫走CSFB流程被用户快速挂断电话，此时走CSFB回退流程，
    回退到L的时候，由于TA在TALIST里面，所以不会发起TAU跟网侧交互，但是
    此时核心网PS域已经开始往2/3G迁移，这样会导致被叫不通，或者收不到短信
    改动:增加标识维护识别上面的这种场景，在回到L的时候保证发起TAU*/
    /*建链成功一定会把ESR发送到网侧，CONN FAIL ESR可能发送成功，在这种两种
      场景下设置标志，其他的原因值，ESR没有发送到网络侧，不需要记录*/
    if((EMM_MS_SER_INIT == NAS_LMM_GetEmmCurFsmMS())
      && ((LRRC_EST_SUCCESS == ulResult)
      || (LRRC_EST_EST_CONN_FAIL == ulResult))
      && (PS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
      /*有可能在释放过程中打电话，这种情况需要过滤*/
      && (NAS_EMM_CONN_WAIT_SYS_INFO != NAS_EMM_GetConnState()))
    {
        NAS_EMM_SetCsfbProcedureFlag(PS_TRUE);
    }

    switch (ulResult)
    {
        case LRRC_EST_SUCCESS:
        case LRRC_EST_PRESENT:
            NAS_EMM_ChangeRrcConnStateToEstSignal();
            NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3412);
            /*通知GU模T3412停止*/
            NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3412, LMM_MMC_TIMER_STOP);

            NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3423);

            /*通知GU模T3423停止*/
            NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3423, LMM_MMC_TIMER_STOP);

            NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);
            /*NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_DELETE);*/
            NAS_EMM_ClearBarResouce();
            NAS_EMM_CcoInterSystemSuccProc();

            /* 发送ATTACH成功，将注册状态设置为ATTACH已发送等网络侧响应 */
            if((EMM_MS_REG_INIT == NAS_LMM_GetEmmCurFsmMS())
                &&(EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF ==NAS_LMM_GetEmmCurFsmSS()))
            {
                NAS_EMM_GLO_AD_SetAttClRegStatus(MMC_LMM_CL_REG_STATUS_ATTACH_SEND_WAIT_CN_RSP);
                /* 大数据: 记录ATTACH EST SUCC时间 */
                NAS_LMM_SaveAttachEstSuccTimeStamp();
            }
            /* 大数据: 记录Ser Est Succ时间 */
            if((EMM_MS_SER_INIT == NAS_LMM_GetEmmCurFsmMS())
                &&(EMM_SS_SER_WAIT_CN_SER_CNF == NAS_LMM_GetEmmCurFsmSS()))
            {
                NAS_EMM_SaveSerEstSuccTimeStamp();
                /* ESR建链成功,通知LRRC CSFB流程启动,LRRC收到该消息后会启动定时器,当定时器超时之前未收到网侧释放
                   消息,LRRC主动释放,用于解决CSFB流程网侧不下发重定向释放的问题*/
                if(PS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
                {
                    NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_START);
                }
            }

            /* sunbing 00265702 begin for DTS2015100600547 关机不等网络释放*/
            /*关机状态下，只要网络受到detach请求，则直接走关机流程，不用等网络的释放*/
            if ((EMM_MS_NULL == NAS_LMM_GetEmmCurFsmMS())
              &&(EMM_SS_NULL_WAIT_SWITCH_OFF == NAS_LMM_GetEmmCurFsmSS()))
            {
                /* 停止TI_NAS_EMM_PTL_SWITCH_OFF_TIMER */
                NAS_LMM_StopPtlTimer(               TI_NAS_EMM_PTL_SWITCH_OFF_TIMER);

                #if (FEATURE_ON == FEATURE_DSDS)
                /*发送end notify消息给RRC，通知RRC释放资源*/
                NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
                #endif

                NAS_EMM_ProcLocalStop();
            }
            /* sunbing 00265702 end for DTS2015100600547 关机不等网络释放*/
            break;

        case LRRC_EST_ESTING:
            NAS_EMM_GIM_WARNING_LOG("MRRC:LRRC_EST_ESTING is ignore!");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_PreProcMsgRrcMmEstCnf_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_EMM_ChangeRrcConnStateToEsting();
            break;

        default:
            NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);

            NAS_EMM_SecuCurrentContextUpNasCountBack();
            #if (FEATURE_PTM == FEATURE_ON)
            NAS_EMM_ProcErrlogEstCnfOrDataCnfFail((VOS_VOID*)pstEstCnfMsg, EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL);
            #endif

            /*发MRRC_CONNECT_FAIL_IND*/
            NAS_EMM_MrrcConnectFailInd(ulResult);
            break;
    }

     return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name  : NAS_EMM_PreProcMsgTIWaitRrcConnTO
 Discription    : MRRC等待RRC连接建立的定时器TI_NAS_EMM_WAIT_RRC_CONN超时,
                  认为建链失败,给请求源模块发送MRRC_REL_IND消息
 Input          : 消息ID,消息
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968  2008-09-10  Draft Enact
      2.  lifuxin   00253982 2014.10.28  建链流程重构
*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgTIWaitRrcConnTO(MsgBlock * pMsg)
{

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcMsgTIWaitRrcConnTO is entered.");
    TLPS_PRINT2LAYER_WARNING(NAS_EMM_PreProcMsgTIWaitRrcConnTO_ENUM,LNAS_ENTRY);

    (VOS_VOID)(pMsg);

    NAS_EMM_SecuCurrentContextUpNasCountBack();

    /*发MRRC_CONNECT_FAIL_IND*/
    NAS_EMM_MrrcConnectFailInd(LRRC_EST_EST_CONN_FAIL);

    if (NAS_EMM_IS_SUSPEND != NAS_EMM_IsSuspended())
    {
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }
    else
    {
        NAS_EMM_SetConnState(NAS_EMM_CONN_IDLE);
    }

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name  : NAS_EMM_IntraEstReq
 Discription    : 收到public发来的mrrc est req消息后,压栈,发rrc_mm_est_req
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968  2008-09-10  Draft Enact
      2.  lifuxin   00253982 2014.10.28  建链流程重构
*****************************************************************************/
VOS_VOID NAS_EMM_IntraEstReq(const NAS_EMM_MRRC_DATA_REQ_STRU *pMsg)
{

    /*发送RRC_MM_EST_REQ*/
    NAS_EMM_RrcEstReq(pMsg);

    NAS_EMM_ChangeRrcConnStateToEsting();

    /*启动定时器*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);

    return ;
}

/*****************************************************************************
 Function Name  : NAS_EMM_RrcEstReq
 Discription    : 发送RRC_MM_EST_REQ
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968  2008-09-10  Draft Enact
      2.  niezhouyu 00108792  2009-05-20 使用命令控制NAS安全特性的打开和关闭
      3.  X00148705           2009-10-20 直接调用NAS_EMM_SEND_MSG发送消息
      4.  z00148421        2010-03-17  安全模块重构:改变了加保护的调用位置
*****************************************************************************/
VOS_VOID    NAS_EMM_RrcEstReq(const NAS_EMM_MRRC_DATA_REQ_STRU *pMsg)
{
    LRRC_LMM_EST_REQ_STRU              *pstEstReqMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEstReqLenNoHeader;

    /* 记录空口消息的类型，在消息传输失败时判断使用*/
    NAS_LMM_GetLastAirMsgType() = pMsg->stNasMsg.aucNasMsg[NAS_EMM_PLAIN_MSG_TYPE_POS];

    /*计算长度*/
    ulEstReqLenNoHeader             = (sizeof(LRRC_LMM_EST_REQ_STRU)+
                                    (pMsg->stNasMsg.ulNasMsgSize-NAS_EMM_4BYTES_LEN))-
                                    NAS_EMM_LEN_VOS_MSG_HEADER;
    /* 分配内存*/
    pstEstReqMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(ulEstReqLenNoHeader + NAS_EMM_LEN_VOS_MSG_HEADER);
    if(NAS_EMM_NULL_PTR == pstEstReqMsg)
    {
        /* 打印内存分配失败log */
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_RrcEstReq: Alloc Msg ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_RrcEstReq_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*填充VOS消息头*/
    NAS_EMM_GIM_RRC_MSG_HEADER(pstEstReqMsg, ulEstReqLenNoHeader);

    /*填充消息ID*/
    pstEstReqMsg->enMsgId    = ID_LRRC_LMM_EST_REQ;

    /*填充请求建链原因*/
    pstEstReqMsg->enEstCause = pMsg->enEstCaue;
    pstEstReqMsg->enCallType = pMsg->enCallType;
    /*填充 NAS建链信息*/

    NAS_LMM_MEM_SET_S(  &(pstEstReqMsg->stEstInfo),
                        sizeof(LRRC_LNAS_EST_INFO_STRU),
                        0,
                        sizeof(LRRC_LNAS_EST_INFO_STRU));

    NAS_EMM_FillEstInfo(pstEstReqMsg, pMsg->enEmmMsgType);

    /*填充消息体*/
    pstEstReqMsg->stFirstNasMsg.ulNasMsgSize = pMsg->stNasMsg.ulNasMsgSize;

    NAS_LMM_MEM_CPY_S(  pstEstReqMsg->stFirstNasMsg.aucNasMsg,
                        pMsg->stNasMsg.ulNasMsgSize,
                        pMsg->stNasMsg.aucNasMsg,
                        pMsg->stNasMsg.ulNasMsgSize);


    /*发送RRC_MM_EST_REQ*/
    NAS_LMM_SEND_MSG(pstEstReqMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_FillEstInfo
 Description     : 为LRRC_LMM_EST_REQ消息填充 EstInfo
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-5-12  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_FillEstInfo(
                                LRRC_LMM_EST_REQ_STRU              *pstEstReqMsg,
                                NAS_EMM_MSG_TYPE_ENUM_UINT32        enEmmMsgType )
{
    NAS_EMM_UEID_STRU                  *pstMmUeId = VOS_NULL_PTR;
    NAS_LMM_NETWORK_INFO_STRU           *pMmNetInfo = VOS_NULL_PTR;
    NAS_MM_TA_STRU                      stCurTa;
    NAS_MM_TA_LIST_STRU                 stTaiList;
    NAS_LMM_GUTI_STRU                    stMappedGuti;
    VOS_UINT32                          ulRslt;

    NAS_LMM_MEM_SET_S(  &stMappedGuti,
                        sizeof(NAS_LMM_GUTI_STRU),
                        0,
                        sizeof(NAS_LMM_GUTI_STRU));

    /*获取 UE 标识*/
    pstMmUeId                           = NAS_LMM_GetEmmInfoUeidAddr();

    /*TIN = P-TMSI:
      如果存在 mapped GUTI,则从 mapped GUTI中获取 GUMMEI;
      如果不存在 mapped GUTI,则既不携带S_TMSI,也不携带GUMMEI*/
    if(NAS_LMM_SUCC ==  NAS_EMM_CheckMutiModeSupport())
    {
        if (MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())
        {
            if(NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity())
            {
                NAS_EMM_DeriveMappedGuti(&stMappedGuti);
                pstEstReqMsg->stEstInfo.ucBitOpRegGummei = NAS_EMM_BIT_SLCT;
                pstEstReqMsg->stEstInfo.stRegGummei.ucMmec = stMappedGuti.stMmeCode.ucMmeCode;
                pstEstReqMsg->stEstInfo.stRegGummei.usMmeGi = ((stMappedGuti.stMmeGroupId.ucGroupId<< 8)
                                                      | (stMappedGuti.stMmeGroupId.ucGroupIdCnt));

                if (NAS_RELEASE_CTRL)
                {
                    pstEstReqMsg->stEstInfo.stRegGummei.enGummeiType = LRRC_LNAS_GUMMEI_TYPE_MAPPED;
                }

                NAS_LMM_MEM_CPY_S(  &(pstEstReqMsg->stEstInfo.stRegGummei.stPlmnId),
                                    sizeof(NAS_MM_PLMN_ID_STRU),
                                    &(stMappedGuti.stPlmnId),
                                    sizeof(NAS_MM_PLMN_ID_STRU));

            }

            return;
        }
    }

    /*TIN != P-TMSI*/
    if(NAS_EMM_MSG_LOAD_BALANCING_TAU != enEmmMsgType)
    {
        NAS_LMM_MEM_SET_S(&stTaiList, sizeof(NAS_MM_TA_LIST_STRU), 0, sizeof(NAS_MM_TA_LIST_STRU));
        NAS_LMM_MEM_SET_S(&stCurTa, sizeof(NAS_MM_TA_STRU), 0, sizeof(NAS_MM_TA_STRU));

        pMmNetInfo                          = NAS_LMM_GetEmmInfoNetInfoAddr();

        /*Current TA*/
        NAS_LMM_MEM_CPY_S(  &(stCurTa.stPlmnId),
                            sizeof(NAS_MM_PLMN_ID_STRU),
                            &(pMmNetInfo->stPresentNetId.stPlmnId),
                            sizeof(NAS_MM_PLMN_ID_STRU));
        NAS_LMM_MEM_CPY_S(  &(stCurTa.stTac),
                            sizeof(NAS_MM_TAC_STRU),
                            &(pMmNetInfo->stPresentNetId.stTac),
                            sizeof(NAS_MM_TAC_STRU));
        /*获取上次注册的TA List*/
        NAS_LMM_MEM_CPY_S(  &(stTaiList),
                            sizeof(NAS_MM_TA_LIST_STRU),
                            &(pMmNetInfo->stTaiList),
                            sizeof(NAS_MM_TA_LIST_STRU));

        ulRslt = NAS_LMM_TaMatchTaList(&stCurTa, &stTaiList);

        /*lint -e701*/

        /*当前TA属于注册的TA，并且当前流程不是attach流程
          (detach之后没有删除ta list，所以ta list只在注册态下是有效的)*/
        if((NAS_LMM_MATCH_SUCCESS == ulRslt)
            && (NAS_EMM_MSG_ATTACH_REQ != enEmmMsgType))
        {
            NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_RrcEstReq:provide S-TMSI to RRC ");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_FillEstInfo_ENUM,LNAS_FUNCTION_LABEL1);
            pstEstReqMsg->stEstInfo.ucBitOpSTmsi = pstMmUeId->bitOpGuti;
            pstEstReqMsg->stEstInfo.stStmsi.ucMmec = pstMmUeId->stGuti.stMmeCode.ucMmeCode;
            pstEstReqMsg->stEstInfo.stStmsi.ulMTmsi = (pstMmUeId->stGuti.stMTmsi.ucMTmsi<<24)
                                            |(pstMmUeId->stGuti.stMTmsi.ucMTmsiCnt1<<16)
                                            |(pstMmUeId->stGuti.stMTmsi.ucMTmsiCnt2<<8)
                                            |(pstMmUeId->stGuti.stMTmsi.ucMTmsiCnt3);

        }
        else
        {
            NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_RrcEstReq:provide GUMMEI to RRC");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_FillEstInfo_ENUM,LNAS_FUNCTION_LABEL2);
            pstEstReqMsg->stEstInfo.ucBitOpRegGummei = pstMmUeId->bitOpGuti;
            pstEstReqMsg->stEstInfo.stRegGummei.ucMmec = pstMmUeId->stGuti.stMmeCode.ucMmeCode;
            pstEstReqMsg->stEstInfo.stRegGummei.usMmeGi = ((pstMmUeId->stGuti.stMmeGroupId.ucGroupId<< 8)
                                                  | (pstMmUeId->stGuti.stMmeGroupId.ucGroupIdCnt));
            if (NAS_RELEASE_CTRL)
            {
                pstEstReqMsg->stEstInfo.stRegGummei.enGummeiType = LRRC_LNAS_GUMMEI_TYPE_NATIVE;
            }

            NAS_LMM_MEM_CPY_S(  &(pstEstReqMsg->stEstInfo.stRegGummei.stPlmnId),
                                sizeof(NAS_MM_PLMN_ID_STRU),
                                &(pstMmUeId->stGuti.stPlmnId),
                                sizeof(NAS_MM_PLMN_ID_STRU));
        }

        /*lint +e701*/


    }
}

/*****************************************************************************
 Function Name  : NAS_EMM_RrcDataReq
 Discription    : 发送RRC_MM_DATA_REQ
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968  2008-09-10  Draft Enact
      2.  X00148705        2009-10-20  直接调用NAS_EMM_SEND_MSG发送消息
      3.  z00148421        2010-03-17  安全模块重构:改变了加保护的调用位置
*****************************************************************************/
VOS_VOID    NAS_EMM_RrcDataReq(         const NAS_EMM_MRRC_DATA_REQ_STRU *pMsg,
                                        VOS_UINT32  ulMmRrcOpId)
{
    LRRC_LMM_DATA_REQ_STRU               *pstDataReqMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRrcMmDataReqMsgLen;

    /* 记录空口消息的类型，在消息传输失败时判断使用*/
    NAS_LMM_GetLastAirMsgType() = pMsg->stNasMsg.aucNasMsg[NAS_EMM_PLAIN_MSG_TYPE_POS];
    ulRrcMmDataReqMsgLen = (sizeof(LRRC_LMM_DATA_REQ_STRU)+
                           pMsg->stNasMsg.ulNasMsgSize)-
                           NAS_EMM_4BYTES_LEN;

    /*分配内存*/
    pstDataReqMsg   = (VOS_VOID *)NAS_LMM_ALLOC_MSG(ulRrcMmDataReqMsgLen);
    if(NAS_EMM_NULL_PTR == pstDataReqMsg)
    {
        /* 打印内存分配失败log */
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_RrcDataReq: NAS_LMM_ALLOC_MSG ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_RrcDataReq_ENUM,LNAS_NULL_PTR);

        return;
    }

    /*填充VOS消息头*/
    NAS_EMM_GIM_RRC_MSG_HEADER(pstDataReqMsg,(ulRrcMmDataReqMsgLen-NAS_EMM_LEN_VOS_MSG_HEADER));

    /*填充消息ID*/
    pstDataReqMsg->enMsgId  = ID_LRRC_LMM_DATA_REQ;

    /*填充OpId*/
    pstDataReqMsg->ulOpId   = ulMmRrcOpId;

    /*填充enDataReqCnf*/
    pstDataReqMsg->enDataCnf = pMsg->enDataCnf;

    /*填充消息体 */
    pstDataReqMsg->stNasMsg.ulNasMsgSize = pMsg->stNasMsg.ulNasMsgSize;

    NAS_LMM_MEM_CPY_S(  pstDataReqMsg->stNasMsg.aucNasMsg,
                        pMsg->stNasMsg.ulNasMsgSize,
                        pMsg->stNasMsg.aucNasMsg,
                        pMsg->stNasMsg.ulNasMsgSize);

    NAS_EMM_GIM_INFO_LOG2("NAS_EMM_RrcDataReq,MmRrcOpId ,enDataCnf ",
                                        ulMmRrcOpId,
                                        pMsg->enDataCnf);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_RrcDataReq_ENUM,LNAS_FUNCTION_LABEL1,
                                        ulMmRrcOpId,
                                        pMsg->enDataCnf);

    /* 发送RRC_MM_DATA_REQ */
    NAS_LMM_SEND_MSG(pstDataReqMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SaveMrrcDataReqMsg
 Description     : 将需要缓存的消息存入缓存区域
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181 2013-03-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SaveMrrcDataReqMsg
(
    const NAS_EMM_MRRC_DATA_REQ_STRU        *pstMsg,
    VOS_UINT32                              ulMmRrcOpId
)
{
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;



    pEmmMrrcMgmtData = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();

    if ((pstMsg->stNasMsg.ulNasMsgSize > NAS_LMM_MRRC_NAS_MSG_MAX_LEN)
        || (NAS_EMM_NULL == pstMsg->stNasMsg.ulNasMsgSize))
    {
        NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_SaveMrrcDataReqMsg:NAS MSG LENGTH ERROR!,MaxLen: MsgLen:",
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN, pstMsg->stNasMsg.ulNasMsgSize);
        TLPS_PRINT2LAYER_INFO2(NAS_EMM_SaveMrrcDataReqMsg_ENUM,LNAS_FUNCTION_LABEL1,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN, pstMsg->stNasMsg.ulNasMsgSize);
        return;
    }

    /*TC消息不记录 */
    if (pstMsg->enEmmMsgType != NAS_EMM_MSG_TC)
    {
        /* 如果缓存的消息条数达到可以缓存的最大值,将后面的消息一次前移*/
        if (NAS_LMM_RRC_SAVE_MSG_MAX_NUM == g_ulSaveMsgNum)
        {
            /* 将消息依次前移，需要存储的放在末尾 */
            NAS_LMM_MEM_CPY_S(  pEmmMrrcMgmtData,
                                (sizeof(NAS_EMM_MRRC_MGMT_DATA_STRU))*(NAS_LMM_RRC_SAVE_MSG_MAX_NUM -1),
                                (pEmmMrrcMgmtData+1),
                                (sizeof(NAS_EMM_MRRC_MGMT_DATA_STRU))*(NAS_LMM_RRC_SAVE_MSG_MAX_NUM -1));

            pEmmMrrcMgmtData = (pEmmMrrcMgmtData +  NAS_LMM_RRC_SAVE_MSG_MAX_NUM) -1;
        }
        else
        {
            pEmmMrrcMgmtData = pEmmMrrcMgmtData +  g_ulSaveMsgNum;
        }

        /*保存OpId */
        pEmmMrrcMgmtData->ulEsmMmOpId = pstMsg->ulEsmMmOpId;
        NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_SaveMrrcDataReqMsg EmmEsmOpId, RrcLmmOpId",
                                pEmmMrrcMgmtData->ulEsmMmOpId, ulMmRrcOpId);
        TLPS_PRINT2LAYER_INFO2(NAS_EMM_SaveMrrcDataReqMsg_ENUM,LNAS_FUNCTION_LABEL2,
                                pEmmMrrcMgmtData->ulEsmMmOpId, ulMmRrcOpId);

        pEmmMrrcMgmtData->ulMmRrcOpId = ulMmRrcOpId;
        #if (FEATURE_LPP == FEATURE_ON)
        pEmmMrrcMgmtData->ulEmmLppOrSsOpId  = pstMsg->ulEmmLppOrSsOpId;
        pEmmMrrcMgmtData->ulLppSsFlag       = pstMsg->ulLppSsFlag;
        #endif

        /*保存NAS空口消息ID以及内容 */
        pEmmMrrcMgmtData->enLastMsgId = pstMsg->enEmmMsgType;

        pEmmMrrcMgmtData->ulNasMsgLength = pstMsg->stNasMsg.ulNasMsgSize;

        NAS_LMM_MEM_CPY_S(  pEmmMrrcMgmtData->aucNasMsgContent,
                            NAS_LMM_MRRC_NAS_MSG_MAX_LEN,
                            pstMsg->stNasMsg.aucNasMsg,
                            pstMsg->stNasMsg.ulNasMsgSize);

        if (NAS_LMM_RRC_SAVE_MSG_MAX_NUM != g_ulSaveMsgNum)
        {
            g_ulSaveMsgNum ++;
        }

        NAS_EMM_PUBU_LOG2_INFO(      "NAS_EMM_SaveMrrcDataReqMsg,MmRrcOpId , enEmmMsgType",
                            ulMmRrcOpId, pstMsg->enEmmMsgType);
        TLPS_PRINT2LAYER_INFO2(NAS_EMM_SaveMrrcDataReqMsg_ENUM,LNAS_FUNCTION_LABEL3,
                            ulMmRrcOpId, pstMsg->enEmmMsgType);

        NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_SaveMrrcDataReqMsg,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_SaveMrrcDataReqMsg_ENUM,LNAS_FUNCTION_LABEL4,
                            g_ulSaveMsgNum);

    }
    return;
}

VOS_VOID  NAS_EMM_MrrcMgmtDataInit( VOS_VOID )
{
    VOS_UINT32                           ulIndex = 0;

    for (ulIndex = 0; ulIndex < NAS_LMM_RRC_SAVE_MSG_MAX_NUM; ulIndex++)
    {
        g_stEmmMrrcMgmtData[ulIndex].ulMmRrcOpId = NAS_LMM_RRC_OPID_NOT_VAILID;
        g_stEmmMrrcMgmtData[ulIndex].ulEsmMmOpId = NAS_LMM_OPID;
        g_stEmmMrrcMgmtData[ulIndex].enLastMsgId = NAS_EMM_CN_MT_BUTT;
        g_stEmmMrrcMgmtData[ulIndex].ulNasMsgLength = NAS_EMM_NULL;
        g_stEmmMrrcMgmtData[ulIndex].ulHoWaitSysInfoFlag = VOS_FALSE;
        /* 清除NO RF上行直传重传标志 */
        g_stEmmMrrcMgmtData[ulIndex].ulNoRfWaitSysInfoFlag = VOS_FALSE;
        g_stEmmMrrcMgmtData[ulIndex].ulConnRelWaitSysInfoFlag = VOS_FALSE;
        g_stEmmMrrcMgmtData[ulIndex].ulIsEsmMsgEmcType        = VOS_FALSE;

        NAS_LMM_MEM_SET_S(  g_stEmmMrrcMgmtData[ulIndex].aucNasMsgContent,
                            NAS_LMM_MRRC_NAS_MSG_MAX_LEN,
                            NAS_EMM_NULL,
                            NAS_LMM_MRRC_NAS_MSG_MAX_LEN);
    }

    g_ulSaveMsgNum = 0;

}


VOS_UINT32  NAS_EMM_MrrcAllocMmRrcOpId( VOS_VOID )
{
    gulMmRrcOpId++;
    if(gulMmRrcOpId                     == NAS_LMM_RRC_OPID_NOT_VAILID)
    {
        gulMmRrcOpId                    = 0;
    }
    return(                             gulMmRrcOpId);
}

/*****************************************************************************
 Function Name   : NAS_EMM_FindMsgInDataReqBuffer
 Description     : 根据DATA CNF携带的OPID查找在缓存消息内存中对应的消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : wangchen  00209181   2013-03-30  Draft Enact

*****************************************************************************/
NAS_EMM_MRRC_MGMT_DATA_STRU* NAS_EMM_FindMsgInDataReqBuffer(VOS_UINT32 ulOpId)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRslt = NAS_EMM_FAIL;
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;

    pEmmMrrcMgmtData = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();

    for (ulIndex = 0; ulIndex <g_ulSaveMsgNum; ulIndex++)
    {
        if (ulOpId == pEmmMrrcMgmtData->ulMmRrcOpId)
        {
            ulRslt = NAS_EMM_SUCC;
            break;
        }
        else
        {
            pEmmMrrcMgmtData++;
        }
    }
    if (NAS_EMM_FAIL == ulRslt)
    {
        return NAS_EMM_NULL_PTR;
    }
    return pEmmMrrcMgmtData;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ClrDataReqBufferMsg
 Description     : 清除单条缓存消息,将后面的消息依次前移
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen  00209181    2013-04-01  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ClrDataReqBufferMsg
(
    VOS_UINT32                          ulMmRrcOpId
)
{
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRrcMmDataReqMsgLen;
    VOS_UINT32                          ulLogIndex;

    NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_ClrDataReqBufferMsg,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrDataReqBufferMsg_ENUM,LNAS_FUNCTION_LABEL1,
                            g_ulSaveMsgNum);

    pEmmMrrcMgmtData = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();

    for (ulIndex = 0; ulIndex < g_ulSaveMsgNum; ulIndex++)
    {
        if (ulMmRrcOpId == pEmmMrrcMgmtData->ulMmRrcOpId)
        {
            /* 如果当前已经存储6条，且需要删除的不是放在数组的末尾，
            需要消息前移，将最末尾的消息清空 */
            if ((g_ulSaveMsgNum - 1)!=ulIndex)
            {
                ulRrcMmDataReqMsgLen = (sizeof(NAS_EMM_MRRC_MGMT_DATA_STRU))*(g_ulSaveMsgNum - (ulIndex+1));

                NAS_LMM_MEM_CPY_S(  pEmmMrrcMgmtData,
                                    ulRrcMmDataReqMsgLen,
                                    (pEmmMrrcMgmtData+1),
                                    ulRrcMmDataReqMsgLen);
            }

            /* 将当前指针指向缓存数组的末尾 */
            pEmmMrrcMgmtData = pEmmMrrcMgmtData + (g_ulSaveMsgNum - (ulIndex+1));

            pEmmMrrcMgmtData->enLastMsgId = NAS_EMM_CN_MT_BUTT;
            pEmmMrrcMgmtData->ulEsmMmOpId = NAS_LMM_OPID;
            pEmmMrrcMgmtData->ulMmRrcOpId = NAS_LMM_RRC_OPID_NOT_VAILID;
            pEmmMrrcMgmtData->ulHoWaitSysInfoFlag = VOS_FALSE;
            /* 清除标志 */
            pEmmMrrcMgmtData->ulNoRfWaitSysInfoFlag = VOS_FALSE;
            pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag = VOS_FALSE;
            pEmmMrrcMgmtData->ulIsEsmMsgEmcType        = VOS_FALSE;
            pEmmMrrcMgmtData->ulNasMsgLength = NAS_EMM_NULL;

            NAS_LMM_MEM_SET_S(  pEmmMrrcMgmtData->aucNasMsgContent,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN,
                                NAS_EMM_NULL,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN);

            g_ulSaveMsgNum--;


            NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_ClrDataReqBufferMsg,g_ulSaveMsgNum =",
                                    g_ulSaveMsgNum);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrDataReqBufferMsg_ENUM,LNAS_FUNCTION_LABEL2,
                                    g_ulSaveMsgNum);

            for (ulLogIndex = 0; ulLogIndex < g_ulSaveMsgNum; ulLogIndex++)
            {
                NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrDataReqBufferMsg,g_stEmmMrrcMgmtData[].enLastMsgId =",
                                       g_stEmmMrrcMgmtData[ulLogIndex].enLastMsgId);
                TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrDataReqBufferMsg_ENUM,LNAS_FUNCTION_LABEL3,
                                       g_stEmmMrrcMgmtData[ulLogIndex].enLastMsgId);

                NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrDataReqBufferMsg,g_stEmmMrrcMgmtData[].ulMmRrcOpId =",
                                       g_stEmmMrrcMgmtData[ulLogIndex].ulMmRrcOpId);
                TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrDataReqBufferMsg_ENUM,LNAS_FUNCTION_LABEL4,
                                       g_stEmmMrrcMgmtData[ulLogIndex].ulMmRrcOpId);

                NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrDataReqBufferMsg,g_stEmmMrrcMgmtData[].ulHoWaitSysInfoFlag =",
                                       g_stEmmMrrcMgmtData[ulLogIndex].ulHoWaitSysInfoFlag);
                TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrDataReqBufferMsg_ENUM,LNAS_FUNCTION_LABEL5,
                                       g_stEmmMrrcMgmtData[ulLogIndex].ulHoWaitSysInfoFlag);
            }


            return;
        }
        pEmmMrrcMgmtData++;
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_ClrHoWaitSysInfoBufferMsg
 Description     : 清除HoWaitSysInfo标识存在的缓存消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen  00209181    2013-04-01  Draft Enact
    2.leixiantiao 00258641  2015-02-04
*****************************************************************************/
VOS_UINT32  NAS_EMM_ClrWaitSysInfoBufferMsg( VOS_VOID )
{
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulCurSaveNum;
    VOS_UINT32                          ulRslt = NAS_EMM_FAIL;
    VOS_UINT32                          ulRrcMmDataReqMsgLen;

    NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_ClrHoWaitSysInfoBufferMsg,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrWaitSysInfoBufferMsg_ENUM,LNAS_FUNCTION_LABEL1,
                            g_ulSaveMsgNum);

    ulCurSaveNum = g_ulSaveMsgNum;

    pEmmMrrcMgmtData = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();

    for (ulIndex = 0; ulIndex < ulCurSaveNum; ulIndex++)
    {
        if ((VOS_TRUE == pEmmMrrcMgmtData->ulHoWaitSysInfoFlag)
            || (VOS_TRUE == pEmmMrrcMgmtData->ulNoRfWaitSysInfoFlag)
            || (VOS_TRUE == pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag))
        {
#if (FEATURE_LPP == FEATURE_ON)
            if ((VOS_TRUE == pEmmMrrcMgmtData->ulHoWaitSysInfoFlag)
                && (NAS_EMM_NAS_UPLINK_GENERIC_NAS_TRANSPORT == pEmmMrrcMgmtData->enLastMsgId))
            {
                if (0 == pEmmMrrcMgmtData->ulLppSsFlag)
                {
                    NAS_EMM_SendLppDataCnf( LMM_LPP_SEND_RSLT_LOW_LAYER_FAIL,
                                            pEmmMrrcMgmtData->ulEmmLppOrSsOpId);
                }
                else
                {
                    NAS_EMM_SndLcsDataCnf(   LMM_LCS_SEND_RSLT_FAIL_LOW_LAYER,
                                            pEmmMrrcMgmtData->ulEmmLppOrSsOpId);
                }
            }
#endif

            /* 如果当前已经存储6条，且需要删除的是放在数组的末尾，
            不需要消息前移，直接删除即可*/
            if ((ulCurSaveNum - 1)!=ulIndex)
            {
                ulRrcMmDataReqMsgLen = (sizeof(NAS_EMM_MRRC_MGMT_DATA_STRU))*(ulCurSaveNum - (ulIndex+1));

                NAS_LMM_MEM_CPY_S(  pEmmMrrcMgmtData,
                                    ulRrcMmDataReqMsgLen,
                                    (pEmmMrrcMgmtData+1),
                                    ulRrcMmDataReqMsgLen);
            }
            /* 将当前指针指向缓存数组的末尾 */
            pEmmMrrcMgmtData = pEmmMrrcMgmtData + (ulCurSaveNum - (ulIndex+1));

            pEmmMrrcMgmtData->enLastMsgId = NAS_EMM_CN_MT_BUTT;
            pEmmMrrcMgmtData->ulEsmMmOpId = NAS_LMM_OPID;
            pEmmMrrcMgmtData->ulMmRrcOpId = NAS_LMM_RRC_OPID_NOT_VAILID;
            pEmmMrrcMgmtData->ulHoWaitSysInfoFlag = VOS_FALSE;
            /* 清除NO RF上行直传重传标志 */
            pEmmMrrcMgmtData->ulNoRfWaitSysInfoFlag = VOS_FALSE;
            pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag = VOS_FALSE;
            pEmmMrrcMgmtData->ulIsEsmMsgEmcType        = VOS_FALSE;
            pEmmMrrcMgmtData->ulNasMsgLength = NAS_EMM_NULL;

            NAS_LMM_MEM_SET_S(  pEmmMrrcMgmtData->aucNasMsgContent,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN,
                                NAS_EMM_NULL,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN);

            pEmmMrrcMgmtData = pEmmMrrcMgmtData - (ulCurSaveNum - (ulIndex+1));

            g_ulSaveMsgNum--;

            ulRslt = NAS_EMM_SUCC;

        }
        else
        {
            pEmmMrrcMgmtData++;
        }

    }

    NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_ClrHoWaitSysInfoBufferMsg,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrWaitSysInfoBufferMsg_ENUM,LNAS_FUNCTION_LABEL2,
                            g_ulSaveMsgNum);

    for (ulIndex = 0; ulIndex < g_ulSaveMsgNum; ulIndex++)
    {
        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrHoWaitSysInfoBufferMsg,g_stEmmMrrcMgmtData[].enLastMsgId =",
                               g_stEmmMrrcMgmtData[ulIndex].enLastMsgId);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrWaitSysInfoBufferMsg_ENUM,LNAS_FUNCTION_LABEL3,
                               g_stEmmMrrcMgmtData[ulIndex].enLastMsgId);

        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrHoWaitSysInfoBufferMsg,g_stEmmMrrcMgmtData[].ulMmRrcOpId =",
                               g_stEmmMrrcMgmtData[ulIndex].ulMmRrcOpId);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrWaitSysInfoBufferMsg_ENUM,LNAS_FUNCTION_LABEL4,
                               g_stEmmMrrcMgmtData[ulIndex].ulMmRrcOpId);

        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrHoWaitSysInfoBufferMsg,g_stEmmMrrcMgmtData[].ulHoWaitSysInfoFlag =",
                               g_stEmmMrrcMgmtData[ulIndex].ulHoWaitSysInfoFlag);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrWaitSysInfoBufferMsg_ENUM,LNAS_FUNCTION_LABEL5,
                               g_stEmmMrrcMgmtData[ulIndex].ulHoWaitSysInfoFlag);
    }

    return ulRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ClrAllUlDataReqBufferMsg
 Description     : 清除所有缓存消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen  00209181    2013-04-01  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ClrAllUlDataReqBufferMsg( VOS_VOID )
{
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulIndex;

    NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_ClrAllUlDataReqBufferMsg,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsg_ENUM,LNAS_FUNCTION_LABEL1,
                            g_ulSaveMsgNum);

    pEmmMrrcMgmtData                    = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();

    for (ulIndex = 0; ulIndex < g_ulSaveMsgNum; ++ulIndex)
    {
        pEmmMrrcMgmtData->enLastMsgId = NAS_EMM_CN_MT_BUTT;
        pEmmMrrcMgmtData->ulEsmMmOpId = NAS_LMM_OPID;
        pEmmMrrcMgmtData->ulMmRrcOpId = NAS_LMM_RRC_OPID_NOT_VAILID;
        pEmmMrrcMgmtData->ulHoWaitSysInfoFlag = VOS_FALSE;
        /* 清除NO RF上行直传重传标志 */
        pEmmMrrcMgmtData->ulNoRfWaitSysInfoFlag = VOS_FALSE;
        pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag = VOS_FALSE;
        pEmmMrrcMgmtData->ulIsEsmMsgEmcType        = VOS_FALSE;
        pEmmMrrcMgmtData->ulNasMsgLength = NAS_EMM_NULL;

        NAS_LMM_MEM_SET_S(  pEmmMrrcMgmtData->aucNasMsgContent,
                            NAS_LMM_MRRC_NAS_MSG_MAX_LEN,
                            NAS_EMM_NULL,
                            NAS_LMM_MRRC_NAS_MSG_MAX_LEN);
    }
    g_ulSaveMsgNum = 0;

    NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_ClrAllUlDataReqBufferMsg,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsg_ENUM,LNAS_FUNCTION_LABEL2,
                            g_ulSaveMsgNum);
}
/*****************************************************************************
 Function Name   : NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc
 Description     : 清除除去DETACH ACP消息外的所有缓存消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen  00209181    2013-04-01  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc( VOS_VOID )
{
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulCurSaveNum;
    VOS_UINT32                          ulRrcMmDataReqMsgLen;

    NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc_ENUM,LNAS_FUNCTION_LABEL1,
                            g_ulSaveMsgNum);

    ulCurSaveNum = g_ulSaveMsgNum;

    pEmmMrrcMgmtData = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();

    for (ulIndex = 0; ulIndex < ulCurSaveNum; ulIndex++)
    {
        if (NAS_EMM_MSG_DETACH_ACP != pEmmMrrcMgmtData->enLastMsgId)
        {
            /* 如果当前已经存储6条，且需要删除的是放在数组的末尾，
            不需要消息前移，直接删除即可*/
            if ((ulCurSaveNum - 1)!=ulIndex)
            {
                ulRrcMmDataReqMsgLen = (sizeof(NAS_EMM_MRRC_MGMT_DATA_STRU))*(ulCurSaveNum - (ulIndex+1));

                NAS_LMM_MEM_CPY_S(  pEmmMrrcMgmtData,
                                    ulRrcMmDataReqMsgLen,
                                    (pEmmMrrcMgmtData+1),
                                    ulRrcMmDataReqMsgLen);
            }
            /* 将当前指针指向缓存数组的末尾 */
            pEmmMrrcMgmtData = pEmmMrrcMgmtData + (ulCurSaveNum - (ulIndex+1));

            pEmmMrrcMgmtData->enLastMsgId = NAS_EMM_CN_MT_BUTT;
            pEmmMrrcMgmtData->ulEsmMmOpId = NAS_LMM_OPID;
            pEmmMrrcMgmtData->ulMmRrcOpId = NAS_LMM_RRC_OPID_NOT_VAILID;
            pEmmMrrcMgmtData->ulHoWaitSysInfoFlag = VOS_FALSE;
            /* 清除NO RF上行直传重传标志 */
            pEmmMrrcMgmtData->ulNoRfWaitSysInfoFlag = VOS_FALSE;
            pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag = VOS_FALSE;
            pEmmMrrcMgmtData->ulIsEsmMsgEmcType        = VOS_FALSE;
            pEmmMrrcMgmtData->ulNasMsgLength = NAS_EMM_NULL;

            NAS_LMM_MEM_SET_S(  pEmmMrrcMgmtData->aucNasMsgContent,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN,
                                NAS_EMM_NULL,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN);

            pEmmMrrcMgmtData = pEmmMrrcMgmtData - (ulCurSaveNum - (ulIndex+1));

            g_ulSaveMsgNum--;

        }
        else
        {
            pEmmMrrcMgmtData++;
        }

    }
    NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc_ENUM,LNAS_FUNCTION_LABEL2,
                            g_ulSaveMsgNum);

    for (ulIndex = 0; ulIndex < g_ulSaveMsgNum; ulIndex++)
    {
        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc,g_stEmmMrrcMgmtData[].enLastMsgId =",
                               g_stEmmMrrcMgmtData[ulIndex].enLastMsgId);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc_ENUM,LNAS_FUNCTION_LABEL3,
                                g_stEmmMrrcMgmtData[ulIndex].enLastMsgId);

        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc,g_stEmmMrrcMgmtData[].ulMmRrcOpId =",
                               g_stEmmMrrcMgmtData[ulIndex].ulMmRrcOpId);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc_ENUM,LNAS_FUNCTION_LABEL4,
                               g_stEmmMrrcMgmtData[ulIndex].ulMmRrcOpId);

        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc,g_stEmmMrrcMgmtData[].ulHoWaitSysInfoFlag =",
                               g_stEmmMrrcMgmtData[ulIndex].ulHoWaitSysInfoFlag);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc_ENUM,LNAS_FUNCTION_LABEL5,
                               g_stEmmMrrcMgmtData[ulIndex].ulHoWaitSysInfoFlag);
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg
 Description     : 在RRC发送REL_IND之前有上行直传由于链路释放而发送失败的消息，需要在收到系统消息后再重发，
                   因此收到REL_IND时不把这些缓存消息删除
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.chengmin 00285307    2015-09-01  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg( VOS_VOID )
{
    NAS_EMM_MRRC_MGMT_DATA_STRU        *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulCurSaveNum;
    VOS_UINT32                          ulRrcMmDataReqMsgLen;

    ulCurSaveNum = g_ulSaveMsgNum;

    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg_ENUM,LNAS_FUNCTION_LABEL1,
                            g_ulSaveMsgNum);

    pEmmMrrcMgmtData = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();

    for (ulIndex = 0; ulIndex < ulCurSaveNum; ulIndex++)
    {
        if (VOS_TRUE != pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag)
        {
            /* 如果当前已经存储6条，且需要删除的是放在数组的末尾，
            不需要消息前移，直接删除即可*/
            if ((ulCurSaveNum - 1)!=ulIndex)
            {
                ulRrcMmDataReqMsgLen = (sizeof(NAS_EMM_MRRC_MGMT_DATA_STRU))*(ulCurSaveNum - (ulIndex+1));

                NAS_LMM_MEM_CPY_S(  pEmmMrrcMgmtData,
                                    ulRrcMmDataReqMsgLen,
                                    (pEmmMrrcMgmtData+1),
                                    ulRrcMmDataReqMsgLen);
            }
            /* 将当前指针指向缓存数组的末尾 */
            pEmmMrrcMgmtData = pEmmMrrcMgmtData + (ulCurSaveNum - (ulIndex+1));

            pEmmMrrcMgmtData->enLastMsgId                   = NAS_EMM_CN_MT_BUTT;
            pEmmMrrcMgmtData->ulEsmMmOpId                   = NAS_LMM_OPID;
            pEmmMrrcMgmtData->ulMmRrcOpId                   = NAS_LMM_RRC_OPID_NOT_VAILID;
            pEmmMrrcMgmtData->ulHoWaitSysInfoFlag           = VOS_FALSE;
            pEmmMrrcMgmtData->ulNoRfWaitSysInfoFlag         = VOS_FALSE;
            pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag      = VOS_FALSE;
            pEmmMrrcMgmtData->ulIsEsmMsgEmcType             = VOS_FALSE;
            pEmmMrrcMgmtData->ulNasMsgLength                = NAS_EMM_NULL;

            NAS_LMM_MEM_SET_S(  pEmmMrrcMgmtData->aucNasMsgContent,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN,
                                NAS_EMM_NULL,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN);

            pEmmMrrcMgmtData = pEmmMrrcMgmtData - (ulCurSaveNum - (ulIndex+1));

            g_ulSaveMsgNum--;

        }
        else
        {
            pEmmMrrcMgmtData++;
        }

    }


    /* 打印缓存中的关键参数 */
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg_ENUM,LNAS_FUNCTION_LABEL2,
                            g_ulSaveMsgNum);

    for (ulIndex = 0; ulIndex < g_ulSaveMsgNum; ulIndex++)
    {
        NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg,enLastMsgId,ulMmRrcOpId:",
                               g_stEmmMrrcMgmtData[ulIndex].enLastMsgId, g_stEmmMrrcMgmtData[ulIndex].ulMmRrcOpId);
        TLPS_PRINT2LAYER_INFO2(NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg_ENUM,LNAS_FUNCTION_LABEL3,
                                g_stEmmMrrcMgmtData[ulIndex].enLastMsgId, g_stEmmMrrcMgmtData[ulIndex].ulMmRrcOpId);

        NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg,ulConnRelWaitSysInfoFlag,ulIsEsmMsgEmcType:",
                               g_stEmmMrrcMgmtData[ulIndex].ulConnRelWaitSysInfoFlag, g_stEmmMrrcMgmtData[ulIndex].ulIsEsmMsgEmcType);
        TLPS_PRINT2LAYER_INFO2(NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg_ENUM,LNAS_FUNCTION_LABEL4,
                               g_stEmmMrrcMgmtData[ulIndex].ulConnRelWaitSysInfoFlag, g_stEmmMrrcMgmtData[ulIndex].ulIsEsmMsgEmcType);
    }
}




/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgRabmDrbSetupInd
 Description     : 收到ID_EMM_ERABM_DRB_SETUP_IND，通知MMC进入数据连接态,
                   然后再进入状态机处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-5-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgRabmDrbSetupInd( MsgBlock * pMsg )
{
    (VOS_VOID)pMsg;
    NAS_EMM_GIM_INFO_LOG("NAS_EMM_PreProcMsgRabmDrbSetupInd entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRabmDrbSetupInd_ENUM,LNAS_ENTRY);

    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        return NAS_LMM_MSG_HANDLED;
    }
    else
    {
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);
    }

    /*做保护,只在RRC链路为信令连接态时,将链路状态切换到数据连接态 */
    if (NAS_EMM_NO == NAS_LMM_IsRrcConnectStatusIdle())
    {
        NAS_EMM_ChangeRrcConnStateToEstData();
    }
    else
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_PreProcMsgRabmDrbSetupInd: idle.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PreProcMsgRabmDrbSetupInd_ENUM,LNAS_FUNCTION_LABEL1);
    }

    return NAS_LMM_MSG_DISCARD;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


/* end of 子系统+模块+文件名.c */
