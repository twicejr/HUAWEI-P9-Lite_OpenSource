/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.
 ******************************************************************************
    File name   : NasEmmMrrcRel.c
    Description :
    History     :
      1.  zangyalan 57968  2008-09-10  Draft Enact
      2.  qilili 00145085  20090117    增加对SM和RABM异常的处理函数
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmGIMComm.h"
#include    "NasEmmMrrc.h"
#include    "NasEmmAttDetInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMMRRCREL_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMMRRCREL_C
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
NAS_EMM_MRRC_CTRL_STRU                  g_stEmmMrrcCtrl;


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_EMM_MrrcRelInit
 Discription    : MRRC 建链模块初始化函数
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968 2008-10-16  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_MrrcRelInit(VOS_VOID)
{
    g_stEmmMrrcCtrl.ulRelCause = NAS_EMM_NORMALSERVICE_REL_CAUSE_NULL;

    /*清资源*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

    /*改变连接状态,同时断开安全连接*/
    NAS_EMM_MrrcChangeRrcStatusToIdle();

    return;
}
/*****************************************************************************
 Function Name  : NAS_EMM_SndRrcRelReq
 Discription    : 给RRC模块发送NAS_EMM_SndRrcRelReq
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968  2008-09-24  Draft Enact
      2.  X00148705        2009-10-20  直接调用NAS_EMM_SEND_MSG发送消息
      3.  sunbing 49683    2009-03-09  修改函数名
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID    NAS_EMM_SndRrcRelReq(NAS_LMM_BARRED_IND_ENUM_UINT32 enBarStatus)
{
    LRRC_LMM_REL_REQ_STRU                *pRelReqMsg;

    /* 分配内存*/
    pRelReqMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_REL_REQ_STRU));
    if(NAS_EMM_NULL_PTR == pRelReqMsg)
    {
        /* 打印内存分配失败log */
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_SndRrcRelReq:Alloc Msg Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndRrcRelReq_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*填充VOS消息头*/
    NAS_EMM_GIM_RRC_MSG_HEADER(pRelReqMsg, (sizeof(LRRC_LMM_REL_REQ_STRU) - NAS_EMM_VOS_HEADER_LEN));

    /*填充消息ID*/
    pRelReqMsg->enMsgId    = ID_LRRC_LMM_REL_REQ;

    /*填充内容*/
    pRelReqMsg->enBarInd   = enBarStatus;

    /*发送RRC_MM_EST_REQ*/
    NAS_LMM_SEND_MSG(pRelReqMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_WaitNetworkRelInd
 Description     : 状态压栈，启3440定时器，等待网侧释放
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181       2012-8-1  Draft Enact
    2.lifuxin  00253982       2014-12-08 释放逻辑重构
    以前的逻辑在等待网络侧释放启动3440，需要将状态转成REL_INIT+WAIT_RRC_REL_CNF
    现在逻辑不再压栈，直接在原有状态启动3440，等待网络侧释放链路
*****************************************************************************/
VOS_VOID NAS_EMM_WaitNetworkRelInd(VOS_VOID)
{
    /* 察看RRC连接是否已经释放 */
    if (NAS_EMM_YES == NAS_LMM_IsRrcConnectStatusIdle())
    {
        /*打印已经释放*/
        NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_WaitNetworkRelInd:Rrc Conn release already");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_WaitNetworkRelInd_ENUM,LNAS_FUNCTION_LABEL1);

        /*转发内部的REL IND*/
        NAS_EMM_CommProcConn2Ilde();
        /*通知 RABM:RRC_CONN_REL_IND*/
        NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_NULL);
    }
    else
    {
        /*启动定时器TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
        NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_T3440);
    }
    return ;
}

/*****************************************************************************
 Function Name  : NAS_EMM_IntraRelReq
 Discription    : 处理Public给RRC发送的mrrc_rel_req
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968  2008-09-10  Draft Enact
      2.  X00148705        2009-09-21  判断RRC链路是否已经释放
      3.  lifuxin 00253982  2014.11.18 释放流程重构
*****************************************************************************/
VOS_VOID NAS_EMM_RelReq(NAS_LMM_BARRED_IND_ENUM_UINT32 enBarStatus)
{
    /* 察看RRC连接是否已经释放 */
    if (NAS_EMM_YES == NAS_LMM_IsRrcConnectStatusIdle())
    {
        /*打印已经释放*/
        NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_RelReq:Rrc Conn release already");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RelReq_ENUM,LNAS_FUNCTION_LABEL1);

        /*转发内部的REL IND*/
        NAS_EMM_CommProcConn2Ilde();
        /*通知 RABM:RRC_CONN_REL_IND*/
        NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_NULL);
    }
    else
    {
        /*发送RRC_MM_REL_REQ*/
        NAS_EMM_SndRrcRelReq(enBarStatus);

        /* 给RRC发释放后，连接状态改为释放过程中 */
        NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        /*启动定时器TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
        NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);
    }

    return ;
}


/*****************************************************************************
 Function Name  : NAS_EMM_PreProcMsgRrcMmRelCnf
 Discription    : 处理RRC_MM_REL_CNF消息
 Input          :
 Output         : None
 Return         : None
 History:
      1. zangyalan   57968  2008-09-10  Draft Enact
      2. zhengjunyan 148421 2009.01.23  MOD BA8D00936
      3. lifuxin     00253982   2014.11.18 释放重构

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgRrcMmRelCnf(MsgBlock * pMsg)
{
    VOS_UINT32                          ulCurEmmStat;

    /* 打印进入该函数，INFO_LEVEL */
    NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_PreProcMsgRrcMmRelCnf is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcMmRelCnf_ENUM,LNAS_ENTRY);

    /*入参检查*/
    if ( NAS_EMM_NULL_PTR == pMsg)
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_PreProcMsgRrcMmRelCnf:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PreProcMsgRrcMmRelCnf_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        return NAS_LMM_MSG_HANDLED;
    }
    /* 由LRRC释放时关闭CIPHER时钟转移到LMM释放时关闭:解决由于任务优先级低，当LMM在使用CIPHER的时候，
       任务抢占，LRRC把CIPHER时钟关闭，导致LMM DATA ABORT问题 */
    #if (VOS_OS_VER != VOS_WIN32)
    /*低功耗方案为了省功耗，在LTE模LNAS收到LRRC释放的时候调底软接口关掉 cipher 时钟以及投票是否关pll，
     协议栈只看到这一个接口，版本共分支由底软在此接口内部进行封装*/
    (VOS_VOID)LDRV_CIPHER_DISABLE();
    #endif
    /*停止定时器*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

    /* 主动释放需要通知ERABM,解决LMM主动释放而ERABM RB状态维护不一致,导致CDS还认为当前处于数据连接态问题 */
    NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_NULL);

    if (EMM_MS_AUTH_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        /* AUTH失败次数清零*/
        NAS_EMM_GetAuthFailTimes() = 0;

        /* 状态出栈*/
        NAS_EMM_FSM_PopState();

        ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                                    NAS_EMM_CUR_SUB_STAT);

        /* 3次卡鉴权失败后主动释放, 收到Rel Cnf, 状态出栈后, 需要做相应处理(同Auth Init态下收到Rel IND)
           解决:卡3次鉴权失败后, LNAS主动释放, 只退出Auth Init状态, 而未对当前流程做相应处理, 从而导致
           状态异常, 如:注册过程中3次鉴权失败后, LMM主动释放后还处于Attach Init状态, 而实际链路已经释放了*/
        switch(ulCurEmmStat)
        {
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
                    NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgRrcRelInd(LRRC_LNAS_REL_CAUSE_OTHER_REASON);
                    break;
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_LIMITED_SERVICE):
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):
                    NAS_EMM_MsRegSsNmlSrvProcMsgRrcRelInd(LRRC_LNAS_REL_CAUSE_OTHER_REASON);
                    break;
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
                    NAS_EMM_ProcMsRegImsiDetachInitMsgRrcRelInd(LRRC_LNAS_REL_CAUSE_OTHER_REASON);
                    break;
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
                    NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd(LRRC_LNAS_REL_CAUSE_OTHER_REASON);
                    break;
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):
                    NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgRrcRelInd(LRRC_LNAS_REL_CAUSE_OTHER_REASON);
                    break;
            case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG_INIT, EMM_SS_DETACH_WAIT_CN_DETACH_CNF):
                    NAS_EMM_MsDrgInitSsWtCnDetCnfProcMsgRrcRelInd(LRRC_LNAS_REL_CAUSE_OTHER_REASON);
                    break;
            default:
                    NAS_EMM_CommProcConn2Ilde();
                    break;
        }
        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_CommProcConn2Ilde();
    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name  : NAS_EMM_MsRrcConnRelInitSsWaitRrcRelCnfMsgRrcMmRelInd
 Discription    : 处理RRC_MM_REL_IND消息
 Input          :
 Output         : None
 Return         : None
 History:
      1. zhengjunyan 148421 new draft BA8D00936
*****************************************************************************/
VOS_VOID  NAS_EMM_MsAuthInitEnterIdleProc(VOS_UINT32 ulCause)
{
    if (EMM_MS_REG_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgRrcRelInd(ulCause);
    }
    else if (EMM_MS_TAU_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd(ulCause);
    }
    else if (EMM_MS_SER_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgRrcRelInd(ulCause);
    }
    else if (EMM_MS_DEREG_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        NAS_EMM_MsDrgInitSsWtCnDetCnfProcMsgRrcRelInd(ulCause);
    }
    else if (EMM_MS_REG == NAS_LMM_GetEmmCurFsmMS())
    {
        if (EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF == NAS_LMM_GetEmmCurFsmSS())
        {
            NAS_EMM_ProcMsRegImsiDetachInitMsgRrcRelInd(ulCause);
        }
        else if (EMM_SS_REG_NORMAL_SERVICE == NAS_LMM_GetEmmCurFsmSS())
        {
            NAS_EMM_MsRegSsNmlSrvProcMsgRrcRelInd(ulCause);
        }
        else if (EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM == NAS_LMM_GetEmmCurFsmSS())
        {
            NAS_EMM_MsRegSsRegAttemptUpdateMmProcMsgRrcRelInd(ulCause);
        }
        else
        {
            return ;
        }
    }
    else
    {
        return ;
    }
}




/*****************************************************************************
 Function Name  : NAS_EMM_PreProcMsgTiWaitRrcRelTO
 Discription    : 定时器TI_NAS_EMM_WAIT_RRC_REL超时的处理函数
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968    2008-09-10  Draft Enact
      2.  zhengjunyan 148421 2009.01.23  MOD BA8D00936
      3.  lifuxin   00253982 2014.11.18  释放流程重构
*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgTiWaitRrcRelTO(MsgBlock * pMsg)
{
    /* 打印进入该函数，INFO_LEVEL */
    NAS_EMM_GIM_INFO_LOG("NAS_EMM_PreProcMsgTiWaitRrcRelTO is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgTiWaitRrcRelTO_ENUM,LNAS_ENTRY);

    /*入参检查*/
    if ( NAS_EMM_NULL_PTR == pMsg)
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_PreProcMsgTiWaitRrcRelTO:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PreProcMsgTiWaitRrcRelTO_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /*停止定时器*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

    NAS_EMM_CommProcConn2Ilde();
    /* RABM:RRC_CONN_REL_IND*/
    NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_NULL);
    if (EMM_MS_AUTH_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        /* AUTH失败次数清零*/
        NAS_EMM_GetAuthFailTimes() = 0;

        /* 状态出栈*/
        NAS_EMM_FSM_PopState();

        NAS_EMM_MsAuthInitEnterIdleProc(LRRC_LNAS_REL_CAUSE_OTHER_REASON);
    }
    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgWaitRrcRel3440TO
 Description     : 定时器3440超时的处理函数
 Input           : ulMsgId；pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181       2012-8-1  Draft Enact
    2.lifuxin  00253982       2014.11.18    释放重构
*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgWaitRrcRel3440TO(MsgBlock * pMsg)
{
    /* 打印进入该函数，INFO_LEVEL */
    NAS_EMM_GIM_INFO_LOG("NAS_EMM_PreProcMsgWaitRrcRel3440TO is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgWaitRrcRel3440TO_ENUM,LNAS_ENTRY);

    /*入参检查*/
    if ( NAS_EMM_NULL_PTR == pMsg)
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_PreProcMsgWaitRrcRel3440TO:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PreProcMsgWaitRrcRel3440TO_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /*发送RRC_MM_REL_REQ*/
    NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

    NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

    /*启动定时器TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgWaitRrcRelReAttachDelayTO
 Description     : 定时器延时发送reattach定时器超时的处理函数
 Input           : pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.niuxiufan 00181501       2013-5-4  Draft Enact
    2.lifuxin   00253982       2014-12-09  链路释放重构
*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgReAttachDelayTO(MsgBlock * pMsg)
{
    (VOS_VOID)pMsg;

    /* 紧急状态下处理暂不考虑,待紧急TAU及Service合入后修改 */

    /* 停止T3440定时器 */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

    NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

    /*发内部attach请求 */
    (VOS_VOID)NAS_EMM_SendIntraAttachReq();

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgTcDataReq
 Description     : 在REL_init+WAIT_REL_CNF状态下收到ETC
                   EMM_ETC_DATA_REQ消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

  History             :
     1.wangchen 00209181    2012-08-30  Draft Enact
     2.wangchen 00209181    2014-09-04  Modify:R11
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgTcDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    EMM_ETC_DATA_REQ_STRU              *pstTcdataReq = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulStaAtStackTop = NAS_EMM_NULL;

    (VOS_VOID)ulMsgId;
    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_GIM_NORMAL_LOG( "NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgTcDataReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgTcDataReq_ENUM,LNAS_ENTRY);

    /*入参检查*/
    if ( NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgTcDataReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgTcDataReq_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    pstTcdataReq = (EMM_ETC_DATA_REQ_STRU*)pMsgStru;

    ulStaAtStackTop = NAS_LMM_FSM_GetStaAtStackTop(NAS_LMM_PARALLEL_FSM_EMM);

    if ((ulStaAtStackTop == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE))
         ||(ulStaAtStackTop == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM)))
    {
        if(NAS_EMM_CONN_RELEASING != NAS_EMM_GetConnState())
        {
            if (NAS_RELEASE_R11)
            {
                return NAS_LMM_STORE_HIGH_PRIO_MSG;
            }
            else
            {
                /* 透传TC消息 */
                NAS_EMM_SER_SendMrrcDataReq_Tcdata(pstTcdataReq);
            }
        }
    }
    return NAS_LMM_MSG_HANDLED;
}

VOS_UINT32  NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgRabmRelReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulStaAtStackTop = NAS_EMM_NULL;

    (VOS_VOID)ulMsgId;
    NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgRabmRelReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgRabmRelReq_ENUM,LNAS_ENTRY);

    /*检查状态是否匹配，若不匹配，退出*/
    if ( NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgRabmRelReq:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgRabmRelReq_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    ulStaAtStackTop = NAS_LMM_FSM_GetStaAtStackTop(NAS_LMM_PARALLEL_FSM_EMM);

    if ((ulStaAtStackTop == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_NORMAL_SERVICE))
         ||(ulStaAtStackTop == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM)))
    {
        if (NAS_EMM_CONN_RELEASING != NAS_EMM_GetConnState())
        {
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

            /*启动定时器TI_NAS_EMM_MRRC_WAIT_RRC_REL*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

            /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
            NAS_EMM_SndRrcRelReq(NAS_LMM_NOT_BARRED);

            /* 设置连接状态为释放过程中 */
            NAS_EMM_SetConnState(NAS_EMM_CONN_RELEASING);

        }
    }
    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRrcRelInitSsWaitRelCnfMsgMmcCoverageLostInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-5-21  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRrcRelInitSsWaitRelCnfMsgMmcCoverageLostInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg)
{
    NAS_EMM_GIM_INFO_LOG("NAS_EMM_MsRrcRelInitSsWaitRelCnfMsgMmcCoverageLostInd: Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsRrcRelInitSsWaitRelCnfMsgMmcCoverageLostInd_ENUM,LNAS_ENTRY);

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsg);

    /* 停止当前的压栈流程 */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF);

    /* 出栈 */
    NAS_EMM_FSM_PopState();


    /* EMM给EMM自己发送AREA LOST消息，以给压栈前的流程处理 */
    NAS_EMMC_SendEmmCoverageLostInd();
    if (EMM_MS_AUTH_INIT == NAS_LMM_GetEmmCurFsmMS())
    {
        /* AUTH失败次数清零*/
        NAS_EMM_GetAuthFailTimes() = 0;

        /* 状态出栈*/
        NAS_EMM_FSM_PopState();

        NAS_EMM_MsAuthInitEnterIdleProc(LRRC_LNAS_REL_CAUSE_OTHER_REASON);
    }
    return  NAS_LMM_MSG_HANDLED;
}


VOS_VOID  NAS_EMM_MrrcChangeRrcStatusToIdle( VOS_VOID )
{
    NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_MrrcChangeRrcStatusToIdle is enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MrrcChangeRrcStatusToIdle_ENUM,LNAS_ENTRY);

    /*如果当前连接状态不是IDLE，则向 MMC上报*/
    if(NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
    {
        NAS_EMM_SendMmcStatusInd(       MMC_LMM_STATUS_TYPE_CONN_STATE,
                                        MMC_LMM_CONN_IDLE);
    }

    /*把RRC连接状态改为非连接状态*/
    NAS_EMM_SetConnState( NAS_EMM_CONN_IDLE);

    /*连接态从CONN进入IDLE，导致当前安全上下文状态变化*/
    NAS_EMM_ConnToIdleTransSecuSta();

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ProcDeregMmcRelReq
 Description     : 在ATTACH过程中收到MMC_LMM_REL_REQ消息后，状态迁移到
                    DEREG+PLMN_SEARCH,上报attach结果
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-6-2  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcDeregMmcRelReq(VOS_VOID )
{
    NAS_EMM_FSM_STATE_STRU              EmmState;

    NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_ProcDeregMmcRelReq is enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcDeregMmcRelReq_ENUM,LNAS_ENTRY);

    /* 停止ATTACH定时器 */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3410);
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_ESM_BEARER_CNF);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_ESM_PDN_RSP);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_WAIT_RRC_DATA_CNF);
    /*NAS_LMM_StopStateTimer(TI_NAS_EMM_T3421);*/
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3416);

    /* 将EMM状态转移至MS_DEREG + SS_PLMN_SEARCH状态 */
    EmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
    EmmState.enMainState                = EMM_MS_DEREG;
    EmmState.enSubState                 = EMM_SS_DEREG_PLMN_SEARCH;
    EmmState.enStaTId                   = TI_NAS_EMM_STATE_NO_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_PUB_SendEsmStatusInd(       EMM_ESM_ATTACH_STATUS_DETACHED);

    /*给MMC上报attach结果*/
    NAS_EMM_AppSendAttOtherType(MMC_LMM_ATT_RSLT_FAILURE);

    /*向RRC发送RRC_MM_REL_REQ消息*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcDetachMmcRelReq
 Description     : 在DETACH过程中收到MMC_LMM_REL_REQ消息后，状态迁移到
                    DEREG+PLMN_SEARCH,上报detach结果
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2012-11-22  Draft Enact
    2.lihong00150010      2012-12-17  Modify:Emergency

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcDetachMmcRelReq(VOS_VOID )
{
    NAS_EMM_FSM_STATE_STRU              EmmState;

    NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_ProcDetachMmcRelReq is enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcDetachMmcRelReq_ENUM,LNAS_ENTRY);

    /* 停止detach定时器 */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3421);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    if (VOS_TRUE == NAS_EMM_GLO_AD_GetUsimPullOutFlag())
    {
        /* 将EMM状态转移至MS_DEREG + SS_PLMN_SEARCH状态 */
        EmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
        EmmState.enMainState                = EMM_MS_DEREG;
        EmmState.enSubState                 = EMM_SS_DEREG_NO_IMSI;
        EmmState.enStaTId                   = TI_NAS_EMM_STATE_NO_TIMER;
        NAS_LMM_StaTransProc(EmmState);

        /* 给MMC回复LMM_MMC_USIM_STATUS_CNF */
        NAS_EMM_SendMmcUsimStatusCnf();

        /* 清除拔卡标识 */
        NAS_EMM_GLO_AD_GetUsimPullOutFlag() = VOS_FALSE;
    }
    else
    {
        /* 将EMM状态转移至MS_DEREG + SS_PLMN_SEARCH状态 */
        EmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
        EmmState.enMainState                = EMM_MS_DEREG;
        EmmState.enSubState                 = EMM_SS_DEREG_NORMAL_SERVICE;
        EmmState.enStaTId                   = TI_NAS_EMM_STATE_NO_TIMER;
        NAS_LMM_StaTransProc(EmmState);
    }

    /*向ESM发送ID_EMM_ESM_STATUS_IND消息*/
    NAS_EMM_PUB_SendEsmStatusInd(       EMM_ESM_ATTACH_STATUS_DETACHED);

    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);

    /* 本地DETACH释放资源:动态内存、赋初值 */
    NAS_LMM_DeregReleaseResource();

    /*向RRC发送RRC_MM_REL_REQ消息*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return;
}




/*****************************************************************************
 Function Name   : NAS_EMM_ProcRegMmcRelReq
 Description     : 在TAU或SERVICE过程中收到MMC_LMM_REL_REQ消息后，状态迁移到
                    REG+WAIT_MRRC_REL_CNF
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-6-2  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ProcRegMmcRelReq(VOS_VOID )
{
    NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_ProcRegMmcRelReq is enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcRegMmcRelReq_ENUM,LNAS_ENTRY);

    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);
    /*NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);
    /*NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3416);*/

    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /* 释放缓存的ESM消息*/
    NAS_EMM_SerClearEsmDataBuf();

    /* 清空接入Bar信息*/
    NAS_EMM_ClearBarResouce();


    /* 将状态转移至MS_REG + SS_REG_PLMN_SEARCH状态 */
    /*
    EmmState.enFsmId                    = NAS_LMM_PARALLEL_FSM_EMM;
    EmmState.enMainState                = EMM_MS_REG;
    EmmState.enSubState                 = EMM_SS_REG_PLMN_SEARCH;
    EmmState.enStaTId                   = TI_NAS_EMM_STATE_NO_TIMER;
    NAS_LMM_StaTransProc(EmmState);
    */
    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ProcRegMmcRelReqWhileTauInit
 Description     : 在TauInit状态收到MMC释放连接请求的处理
 Input           : None
 Output          : None
 Return          : None

 History         :
    1.liuhua 00212067      2013-03-05  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_ProcRegMmcRelReqWhileTauInit(VOS_VOID)
{
    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ProcRegMmcRelReqWhileTauInit");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcRegMmcRelReqWhileTauInit_ENUM,LNAS_ENTRY);

    /*释放处理*/
    NAS_EMM_ProcRegMmcRelReq();

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_EMM_TAU_SendRrcDsdsEndNotify();
    #endif

    /*按照TAU异常的流程来处理*/
    NAS_EMM_TAU_GetEmmTAUAttemptCnt()++;
    NAS_EMM_TAU_ProcAbnormal();
    /* 向MMC发送LMM_MMC_TAU_RESULT_IND消息在冲突内部处理 */
    NAS_EMM_TAU_RelIndCollisionProc(NAS_EMM_MmcSendTauActionResultIndFailWithPara,
                                    (VOS_VOID*)NAS_EMM_NULL_PTR);

    /*向RRC发送RRC_MM_REL_REQ消息*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
}


/*****************************************************************************
 Function Name   : NAS_EMM_ProcRegMmcRelReqWhileSerInit
 Description     : 在SerInit状态收到MMC释放连接请求的处理
 Input           : None
 Output          : None
 Return          : None

 History         :
    1.liuhua 00212067      2013-03-05  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_ProcRegMmcRelReqWhileSerInit(VOS_VOID)
{
    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ProcRegMmcRelReqWhileSerInit");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcRegMmcRelReqWhileSerInit_ENUM,LNAS_ENTRY);

    /*释放处理*/
    NAS_EMM_ProcRegMmcRelReq();

    /*转换状态*/
    NAS_EMM_TranStateRegNormalServiceOrRegUpdateMm();

    /*向RRC发送RRC_MM_REL_REQ消息*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
}

/*****************************************************************************
 Function Name   : NAS_EMM_ProcRegMmcRelReqWhileImsiDetach
 Description     : 在ImsiDetach状态收到MMC释放连接请求的处理
 Input           : None
 Output          : None
 Return          : None

 History         :
    1.liuhua 00212067      2013-03-05  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_ProcRegMmcRelReqWhileImsiDetach(VOS_VOID)
{
    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ProcRegMmcRelReqWhileImsiDetach");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcRegMmcRelReqWhileImsiDetach_ENUM,LNAS_ENTRY);

    /*对IMSI detach进行处理*/
    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    NAS_EMM_SendDetRslt(MMC_LMM_DETACH_RSLT_SUCCESS);
    NAS_LMM_ImsiDetachReleaseResource();

    #if (FEATURE_ON == FEATURE_DSDS)
    /*发送end notify消息给RRC，通知RRC释放资源*/
    NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
    #endif

    /*主动RRC发送连接释放*/
    NAS_EMM_ProcRegMmcRelReq();

    /*转换状态*/
    NAS_EMM_TranStateRegNormalServiceOrRegUpdateMm();

    /*向RRC发送RRC_MM_REL_REQ消息*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

}
/*lint +e961*/
/*lint +e960*/




/***************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of 子系统+模块+文件名.c */
