/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasLppFsm.c
  版 本 号   : 初稿
  作    者   : XiaoJun
  生成日期   : 2015年9月8日
  最近修改   :
  功能描述   : NAS lpp的状态机
  函数列表   :
  修改历史   :
  1.日    期   : 2015年9月8日
    作    者   : XiaoJun
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "NasLppPublic.h"
#include  "PsLogdef.h"
#include  "NasFileId.h"
#include  "NasLppIntraInterface.h"


#define    THIS_FILE_ID            PS_FILE_ID_NASLPPFSM_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPFSM_C


#if (FEATURE_LPP == FEATURE_ON)
extern VOS_VOID  NAS_LPP_OmStateChgInd
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndex,
    VOS_UINT8                           ucTransIndex,
    NAS_LPP_MAIN_STATE_ENUM_UINT32      enOldMsState,
    NAS_LPP_SUB_STATE_ENUM_UINT32       enOldSubState,
    NAS_LPP_MAIN_STATE_ENUM_UINT32      enNewMsState,
    NAS_LPP_SUB_STATE_ENUM_UINT32       enNewSubState
);
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
NAS_LPP_ACTION_FUN  g_afJustFsmMsgBuffByState[LPP_MS_BUTT] =
    {
        NAS_LPP_NULL_PTR,
        NAS_LPP_JustMsgBuffInCapState,
        NAS_LPP_JustMsgBuffInAssistState,
        NAS_LPP_JustMsgBuffInLocState
    };


NAS_LPP_FSM_ACT_STRU g_astLppIdleStateTbl[] =
{
    {PS_PID_MM,  ID_LMM_LPP_DATA_IND }
};

/*Capability主状态的状态机表*/
NAS_LPP_FSM_ACT_STRU g_astLppMsCapSsCapReqWaitCnfTbl[] =
{
    {UEPS_PID_MTA,  ID_MTA_LPP_GNSS_CAP_CNF }
};
NAS_LPP_FSM_ACT_STRU g_astLppMsCapSsCapProvideWaitCnAckTbl[] =
{
    {PS_PID_MM,    ID_LMM_LPP_DATA_IND},
    {PS_PID_LPP,  ID_NAS_LPP_INTRA_DATA_CNF }
};
NAS_LPP_FSM_ACT_STRU g_astLppMsCapSsCapWaitAbortCnAckTbl[] =
{
    {PS_PID_MM,   ID_LMM_LPP_DATA_IND }
};

NAS_LPP_FSM_ACT_STRU g_astLppMsCapSsWaitIntraDataCnfTbl[] =
{
    {PS_PID_LPP,  ID_NAS_LPP_INTRA_DATA_CNF }
};
NAS_LPP_FSM_ACT_STRU g_astLppMsCapSsWaitIntraDataCnfOfUpLppAckTbl[] =
{
    {PS_PID_LPP,  ID_NAS_LPP_INTRA_DATA_CNF }
};

/*Assist data主状态的状态机表*/
NAS_LPP_FSM_ACT_STRU g_astLppMsAssisSsReqWaitCnAckTbl[] =
{
    {PS_PID_MM,  ID_LMM_LPP_DATA_IND }
};
NAS_LPP_FSM_ACT_STRU g_astLppMsAssisSsWaitCnCnfTbl[] =
{
    {PS_PID_MM,  ID_LMM_LPP_DATA_IND }
};
NAS_LPP_FSM_ACT_STRU g_astLppMsAssisSsAbortWaitCnAckTbl[] =
{
    {PS_PID_MM,  ID_LMM_LPP_DATA_IND }
};

NAS_LPP_FSM_ACT_STRU g_astLppMsAssisSsWaitIntraDataTbl[] =
{
    {PS_PID_LPP, ID_NAS_LPP_INTRA_DATA_CNF  }
};


NAS_LPP_FSM_ACT_STRU g_astLppMsAssisSsWaitIntraDataOfUpLppAckTbl[] =
{
    {PS_PID_LPP, ID_NAS_LPP_INTRA_DATA_CNF  }
};

/*location主状态的状态机表*/


/*在等待辅助信息的过程中可以处理ECID的LRRC CNF*/
NAS_LPP_FSM_ACT_STRU g_astLppMsLocReqSsWaitAssistRcvCmplTbl[] =
{
    {PS_PID_ERRC,  ID_LRRC_LPP_ECID_MEAS_CNF }
};
NAS_LPP_FSM_ACT_STRU g_astLppMsLocReqSsWaitAssistReqProcCmplTbl[] =
{
    /* wait for confirm */
    {PS_PID_ERRC,  ID_LRRC_LPP_ECID_MEAS_CNF },
    {PS_PID_LPP,  ID_NAS_LPP_INTRA_DATA_CNF }
};

NAS_LPP_FSM_ACT_STRU g_astLppMsLocReqSsWaitLrrcMeasCnfTbl[] =
{
    {PS_PID_ERRC,  ID_LRRC_LPP_ECID_MEAS_CNF },
    {PS_PID_ERRC,  ID_LRRC_LPP_OTDOA_MEAS_CNF },
    {PS_PID_LPP,  ID_NAS_LPP_INTRA_DATA_CNF }
};

NAS_LPP_FSM_ACT_STRU g_astLppMsLocReqSsWaitReleaseLrrcMeasCnfTbl[] =
{
    {PS_PID_ERRC,  ID_LRRC_LPP_ECID_MEAS_CNF },
    {PS_PID_ERRC,  ID_LRRC_LPP_OTDOA_MEAS_CNF },
    {PS_PID_LPP,  ID_NAS_LPP_INTRA_DATA_CNF }
};


NAS_LPP_FSM_ACT_STRU g_astLppMsLocReqSsWaitLocCnAckTbl[] =
{
    {PS_PID_MM,  ID_LMM_LPP_DATA_IND },
    {PS_PID_LPP,  ID_NAS_LPP_INTRA_DATA_CNF }
};
NAS_LPP_FSM_ACT_STRU g_astLppMsLocReqSsWaitLocAbortCnAckTbl[] =
{
    {PS_PID_MM,  ID_LMM_LPP_DATA_IND }
};

NAS_LPP_FSM_ACT_STRU g_astLppMsLocReqSsWaitIntraDataCnfTbl[] =
{
    {PS_PID_LPP,  ID_NAS_LPP_INTRA_DATA_CNF }
};
NAS_LPP_FSM_ACT_STRU g_astLppMsLocReqSsWaitIntraDataCnfOfUpLppAckTbl[] =
{
    {PS_PID_LPP,  ID_NAS_LPP_INTRA_DATA_CNF }
};

NAS_LPP_FSM_ACT_STRU g_astLppMsLocReqSsWaitMeasIndTbl[] =
{
    {PS_PID_ERRC,  ID_LRRC_LPP_ECID_MEAS_IND },
    {PS_PID_ERRC,  ID_LRRC_LPP_OTDOA_MEAS_IND },
    {PS_PID_LPP,   ID_NAS_LPP_INTRA_DATA_CNF }
};



/*LPP的状态机表
排序要求，1、按照主状态的大小有小向大排； 2、每个主状态内部，按照子状态由小到大的排序。
最后的排序结果是，按照NAS_LPP_COMP_STATE组合的值由小向大的排*/
NAS_LPP_FSM_STRU  g_astNasLppFsm[] =
{
    {NAS_LPP_COMP_STATE(LPP_MS_IDLE,LPP_SS_IDLE),                               0,NAS_LPP_NULL_PTR},

    /*capability主状态的存在的状态组合*/
    {NAS_LPP_COMP_STATE(LPP_MS_CAPABILITY,LPP_SS_CAP_REQ_WAIT_CNF),             NAS_LPP_STATE_TBL_SIZE(g_astLppMsCapSsCapReqWaitCnfTbl),        g_astLppMsCapSsCapReqWaitCnfTbl},
    {NAS_LPP_COMP_STATE(LPP_MS_CAPABILITY,LPP_SS_CAP_PRIVIDE_WAIT_CN_ACK),      NAS_LPP_STATE_TBL_SIZE(g_astLppMsCapSsCapProvideWaitCnAckTbl),  g_astLppMsCapSsCapProvideWaitCnAckTbl},
    {NAS_LPP_COMP_STATE(LPP_MS_CAPABILITY,LPP_SS_CAP_WAIT_ABORT_CN_ACK),        NAS_LPP_STATE_TBL_SIZE(g_astLppMsCapSsCapWaitAbortCnAckTbl),    g_astLppMsCapSsCapWaitAbortCnAckTbl},
    {NAS_LPP_COMP_STATE(LPP_MS_CAPABILITY,LPP_SS_WAIT_INTRA_DATA_CNF),          NAS_LPP_STATE_TBL_SIZE(g_astLppMsCapSsWaitIntraDataCnfTbl),     g_astLppMsCapSsWaitIntraDataCnfTbl},
    {NAS_LPP_COMP_STATE(LPP_MS_CAPABILITY,LPP_SS_WAIT_INTRA_DATA_CNF_OF_UP_LPP_ACK),NAS_LPP_STATE_TBL_SIZE(g_astLppMsCapSsWaitIntraDataCnfOfUpLppAckTbl), g_astLppMsCapSsWaitIntraDataCnfOfUpLppAckTbl},

    /*assistant主状态的存在的状态组合*/
    {NAS_LPP_COMP_STATE(LPP_MS_ASSISTDATA,LPP_SS_ASSISTDATA_REQ_WAIT_CN_ACK),   NAS_LPP_STATE_TBL_SIZE(g_astLppMsAssisSsReqWaitCnAckTbl),       g_astLppMsAssisSsReqWaitCnAckTbl   },
    {NAS_LPP_COMP_STATE(LPP_MS_ASSISTDATA,LPP_SS_ASSISTDATA_WAIT_CN_CNF),       NAS_LPP_STATE_TBL_SIZE(g_astLppMsAssisSsWaitCnCnfTbl),          g_astLppMsAssisSsWaitCnCnfTbl   },
    {NAS_LPP_COMP_STATE(LPP_MS_ASSISTDATA,LPP_SS_ASSISTDATA_WAIT_ABORT_CN_ACK), NAS_LPP_STATE_TBL_SIZE(g_astLppMsAssisSsAbortWaitCnAckTbl),     g_astLppMsAssisSsAbortWaitCnAckTbl   },
    {NAS_LPP_COMP_STATE(LPP_MS_ASSISTDATA,LPP_SS_WAIT_INTRA_DATA_CNF),          NAS_LPP_STATE_TBL_SIZE(g_astLppMsAssisSsWaitIntraDataTbl),      g_astLppMsAssisSsWaitIntraDataTbl},
    {NAS_LPP_COMP_STATE(LPP_MS_ASSISTDATA,LPP_SS_WAIT_INTRA_DATA_CNF_OF_UP_LPP_ACK),NAS_LPP_STATE_TBL_SIZE(g_astLppMsAssisSsWaitIntraDataOfUpLppAckTbl), g_astLppMsAssisSsWaitIntraDataOfUpLppAckTbl},

    /*location主状态的存在的状态组合*/
    {NAS_LPP_COMP_STATE(LPP_MS_LOCATION,LPP_SS_WAIT_ASSISTDATA_RCV_CMP),        NAS_LPP_STATE_TBL_SIZE(g_astLppMsLocReqSsWaitAssistRcvCmplTbl), g_astLppMsLocReqSsWaitAssistRcvCmplTbl},
    {NAS_LPP_COMP_STATE(LPP_MS_LOCATION,LPP_SS_WAIT_ASSISTDATA_REQ_PROCESS_CMP),NAS_LPP_STATE_TBL_SIZE(g_astLppMsLocReqSsWaitAssistReqProcCmplTbl),   g_astLppMsLocReqSsWaitAssistReqProcCmplTbl},
    {NAS_LPP_COMP_STATE(LPP_MS_LOCATION,LPP_SS_WAIT_LRRC_MEAS_CNF),             NAS_LPP_STATE_TBL_SIZE(g_astLppMsLocReqSsWaitLrrcMeasCnfTbl),   g_astLppMsLocReqSsWaitLrrcMeasCnfTbl  },
    {NAS_LPP_COMP_STATE(LPP_MS_LOCATION,LPP_SS_WAIT_RELEASE_LRRC_MEAS_CNF),     NAS_LPP_STATE_TBL_SIZE(g_astLppMsLocReqSsWaitReleaseLrrcMeasCnfTbl),   g_astLppMsLocReqSsWaitReleaseLrrcMeasCnfTbl  },
    {NAS_LPP_COMP_STATE(LPP_MS_LOCATION,LPP_SS_WAIT_LOCATION_CN_ACK),           NAS_LPP_STATE_TBL_SIZE(g_astLppMsLocReqSsWaitLocCnAckTbl),      g_astLppMsLocReqSsWaitLocCnAckTbl },
    {NAS_LPP_COMP_STATE(LPP_MS_LOCATION,LPP_SS_WAIT_LOCATION_ABORT_CN_ACK),     NAS_LPP_STATE_TBL_SIZE(g_astLppMsLocReqSsWaitLocAbortCnAckTbl), g_astLppMsLocReqSsWaitLocAbortCnAckTbl },
    {NAS_LPP_COMP_STATE(LPP_MS_LOCATION,LPP_SS_WAIT_INTRA_DATA_CNF),            NAS_LPP_STATE_TBL_SIZE(g_astLppMsLocReqSsWaitIntraDataCnfTbl),  g_astLppMsLocReqSsWaitIntraDataCnfTbl},
    {NAS_LPP_COMP_STATE(LPP_MS_LOCATION,LPP_SS_WAIT_INTRA_DATA_CNF_OF_UP_LPP_ACK),NAS_LPP_STATE_TBL_SIZE(g_astLppMsLocReqSsWaitIntraDataCnfOfUpLppAckTbl), g_astLppMsLocReqSsWaitIntraDataCnfOfUpLppAckTbl},
    {NAS_LPP_COMP_STATE(LPP_MS_LOCATION,LPP_SS_WAIT_MEAS_IND),                  NAS_LPP_STATE_TBL_SIZE(g_astLppMsLocReqSsWaitMeasIndTbl),       g_astLppMsLocReqSsWaitMeasIndTbl},

};

NAS_LPP_SUB_STATE_TIME_STRU g_astLppSubStateTime[LPP_SS_BUTT] =
{
    { LPP_SS_IDLE                           ,TI_NAS_LPP_TIMER_PARA_BUTT,       {0,0,0}},
    { LPP_SS_CAP_REQ_WAIT_CNF               ,TI_NAS_LPP_WAIT_GNSS_CAP_CNF,     {0,0,0}},
    { LPP_SS_CAP_PRIVIDE_WAIT_CN_ACK        ,TI_NAS_LPP_UPLINK_MSG_RETRANS,    {0,0,0}},
    { LPP_SS_CAP_WAIT_ABORT_CN_ACK          ,TI_NAS_LPP_UPLINK_MSG_RETRANS,    {0,0,0}},
    { LPP_SS_ASSISTDATA_REQ_WAIT_CN_ACK     ,TI_NAS_LPP_UPLINK_MSG_RETRANS,    {0,0,0}},
    { LPP_SS_ASSISTDATA_WAIT_CN_CNF         ,TI_NAS_LPP_WAIT_CN_ASSIST_DATA,   {0,0,0}},
    { LPP_SS_ASSISTDATA_WAIT_ABORT_CN_ACK   ,TI_NAS_LPP_UPLINK_MSG_RETRANS,    {0,0,0}},
    { LPP_SS_WAIT_ASSISTDATA_RCV_CMP        ,TI_NAS_LPP_TIMER_PARA_BUTT,       {0,0,0}},
    { LPP_SS_WAIT_ASSISTDATA_REQ_PROCESS_CMP,TI_NAS_LPP_TIMER_PARA_BUTT,       {0,0,0}},
    { LPP_SS_WAIT_LRRC_MEAS_CNF             ,TI_NAS_LPP_WAIT_LRRC_MEAS_CNF,    {0,0,0}},
    { LPP_SS_WAIT_RELEASE_LRRC_MEAS_CNF     ,TI_NAS_LPP_WAIT_LRRC_MEAS_CNF,    {0,0,0}},
    { LPP_SS_WAIT_LOCATION_CN_ACK           ,TI_NAS_LPP_UPLINK_MSG_RETRANS,    {0,0,0}},
    { LPP_SS_WAIT_LOCATION_ABORT_CN_ACK     ,TI_NAS_LPP_UPLINK_MSG_RETRANS,    {0,0,0}},
    { LPP_SS_WAIT_INTRA_DATA_CNF            ,TI_NAS_LPP_WAIT_INTRA_DATE_CNF,   {0,0,0}},
    { LPP_SS_WAIT_INTRA_DATA_CNF_OF_UP_LPP_ACK,TI_NAS_LPP_WAIT_INTRA_DATE_CNF, {0,0,0}},
    { LPP_SS_WAIT_MEAS_IND                  ,TI_NAS_LPP_TIMER_PARA_BUTT,       {0,0,0}}
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/


/*****************************************************************************
 Function Name  :
 Discription    : 事件比较函数，在对事件处理表进行快速排序时用到.从RRC_FSM_ActCompare移植。
 Input          : 事件1 事件2
 Output         : None
 Return         : 0  -- 事件1和事件2相等
                  -1 -- 事件1小于事件2
                  1  -- 事件1大于事件2
 History:
      1.  Wang Yangcai 49178  2008-02-19 移植代码

*****************************************************************************/
VOS_INT32 NAS_LPP_FsmStaCompare( const VOS_VOID *arg1, const VOS_VOID *arg2 )
{
    NAS_LPP_FSM_STRU *pAct1;
    NAS_LPP_FSM_STRU *pAct2;

    pAct1 = (NAS_LPP_FSM_STRU*) arg1;
    pAct2 = (NAS_LPP_FSM_STRU*) arg2;

    /*  如果事件1小于事件2,返回-1 */
    if (pAct1->ulState < pAct2->ulState)
    {
        return -1;
    }

    /*  如果事件1等于事件2,返回0 */
    if (pAct1->ulState == pAct2->ulState)
    {
        return 0;
    }

    /*  如果事件1大于事件2,返回0 */
    return 1;
}

/*****************************************************************************
 Function Name   : NAS_LPP_FsmFind
 Description     : 从状态机查找状态，移植于RRC_FSM_FindAct
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-23  Draft Enact

*****************************************************************************/
NAS_LPP_FSM_STRU * NAS_LPP_FsmFind(NAS_LPP_MAIN_STATE_ENUM_UINT32 enLppMainState, NAS_LPP_SUB_STATE_ENUM_UINT32 enLppSubState)
{
    VOS_UINT32 ulState;
    NAS_LPP_FSM_STRU *pstFsm = NAS_LPP_NULL_PTR;

    ulState = NAS_LPP_COMP_STATE(enLppMainState,enLppSubState);

    /* 调用C语言的库函数bsearch在状态转移表中查找相应的事件处理表 */
    pstFsm = (NAS_LPP_FSM_STRU*) bsearch(  &ulState,
                                           g_astNasLppFsm,
                                           sizeof(g_astNasLppFsm)/sizeof(NAS_LPP_FSM_STRU),
                                           sizeof(NAS_LPP_FSM_STRU),
                                           (NAS_LPP_FSM_COMP_FUNC)NAS_LPP_FsmStaCompare );

    if (NAS_LPP_NULL_PTR == pstFsm)
    {
        NAS_LPP_ERR_LOG2("not find in fsm, MainState, subState", enLppMainState, enLppSubState);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_FsmFind_ENUM, LNAS_LPP_MAIN_STATE, enLppMainState);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_FsmFind_ENUM, LNAS_LPP_SUB_STATE, enLppSubState);

    }

    return pstFsm;
}


/*****************************************************************************
 Function Name   : NAS_LPP_JustMsgBuffInCapState
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-25  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_JustMsgBuffInCapState( VOS_UINT32 ulSubState, VOS_VOID *pMsg )
{
    return NAS_LPP_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_LPP_JustMsgBuffInAssistState
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-25  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_JustMsgBuffInAssistState( VOS_UINT32 ulSubState, VOS_VOID *pMsg )
{
    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LPP_JustMsgBuffInLocState
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-25  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_JustMsgBuffInLocState( VOS_UINT32 ulSubState, VOS_VOID *pMsg )
{
    //PS_MSG_HEADER_STRU             *pstMsg;

    //pstMsg = (PS_MSG_HEADER_STRU *)pMsg;

    /*TO DO*/
    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LPP_JustFsmMsgToBuff
 Description     : 判断当前状态，此消息是否缓存
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_JustFsmMsgToBuff
(
    NAS_LPP_MAIN_STATE_ENUM_UINT32  enLppMainState,
    NAS_LPP_SUB_STATE_ENUM_UINT32   enLppSubState,
    PS_MSG_HEADER_STRU             *pstMsg
)
{
    NAS_LPP_ACTION_FUN pfFun;

    if ( enLppMainState >= LPP_MS_BUTT )
    {
        NAS_LPP_ERR_LOG1("Just fsm msg wrong ms", enLppMainState);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_JustFsmMsgToBuff_ENUM, LNAS_LPP_MAIN_STATE, enLppMainState);
        return;
    }

    pfFun = g_afJustFsmMsgBuffByState[enLppMainState];
    if (NAS_LPP_SUCCESS != pfFun( (VOS_UINT32)enLppSubState,(VOS_VOID *)pstMsg ) )
    {
        NAS_LPP_ERR_LOG("Just fsm msg fail");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_JustFsmMsgToBuff_ENUM, LNAS_LPP_FsmMsgFail);
    }
}

/*****************************************************************************
 Function Name   : NAS_LPP_TransFsmCheck
 Description     : 检查transaction
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-21  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_TransFsmCheck
(
    NAS_LPP_MAIN_STATE_ENUM_UINT32  enLppMainState,
    NAS_LPP_SUB_STATE_ENUM_UINT32   enLppSubState,
    PS_MSG_HEADER_STRU             *pstMsg
)
{
    NAS_LPP_FSM_STRU               *pstFsm = NAS_LPP_NULL_PTR;
    NAS_LPP_FSM_ACT_STRU           *pstAct = NAS_LPP_NULL_PTR;
    VOS_UINT32                      ulLoop,ulRslt = NAS_LPP_FSM_NOT_MATCH;
    VOS_UINT32                      ulSendPid;
    VOS_UINT32                      ulMsgId;

    ulSendPid = pstMsg->ulSenderPid;
    ulMsgId = pstMsg->ulMsgName;

    pstFsm = NAS_LPP_FsmFind(enLppMainState,enLppSubState);
    if ( NAS_LPP_NULL_PTR == pstFsm )
    {
        return NAS_LPP_FSM_NOT_MATCH;
    }

    pstAct = pstFsm->pfFsmActTbl;

    if ( NAS_LPP_NULL_PTR == pstAct )
    {
        return NAS_LPP_FSM_NOT_MATCH;
    }

    for ( ulLoop = 0 ; ulLoop < pstFsm->ulSize; ulLoop++ )
    {
        if ( (pstAct[ulLoop].ulSendPid == ulSendPid) && (pstAct[ulLoop].ulMsgId == ulMsgId) )
        {
            ulRslt = NAS_LPP_SUCCESS;
            break;
        }
    }

    if ( NAS_LPP_FSM_NOT_MATCH == ulRslt )
    {
        /*判断在当前的状态，哪些消息需要缓存*/
        NAS_LPP_JustFsmMsgToBuff(enLppMainState,enLppSubState,pstMsg);
    }

    return ulRslt;
}
/*****************************************************************************
 Function Name   : NAS_LPP_FsmInit
 Description     :  NAS_LPP 状态机初始化
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_FsmInit( VOS_VOID )
{

}


/*****************************************************************************
 Function Name   : NAS_LPP_GetTimeNameBySubState
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-22  Draft Enact

*****************************************************************************/
NAS_LPP_TIMER_PARA_ENUM_UINT8  NAS_LPP_GetTimeNameBySubState
(
    NAS_LPP_SUB_STATE_ENUM_UINT32       enLppSubState
)
{
    if (enLppSubState >= LPP_SS_BUTT)
    {
        return TI_NAS_LPP_TIMER_PARA_BUTT;
    }

    return (g_astLppSubStateTime[enLppSubState].enTimeName);
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetWaitAckSubState
 Description     : 收到intra data cnf后，确定下面的状态
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-22  Draft Enact

*****************************************************************************/
NAS_LPP_SUB_STATE_ENUM_UINT32  NAS_LPP_GetWaitAckSubState
(
    NAS_LPP_AIR_MSG_ENUM_UINT32         ulUpLppMsgId,
    NAS_LPP_MAIN_STATE_ENUM_UINT32      enMainState
)
{
    NAS_LPP_SUB_STATE_ENUM_UINT32 enSubState;

    switch ( ulUpLppMsgId )
    {
        case NAS_LPP_AIR_MSG_PROVIDE_CAP :
        {
            enSubState = LPP_SS_CAP_PRIVIDE_WAIT_CN_ACK;
            break;
        }
        case NAS_LPP_AIR_MSG_REQUEST_ASSIST_DATA :
        {
            enSubState =  LPP_SS_ASSISTDATA_REQ_WAIT_CN_ACK;
            break;
        }
        case NAS_LPP_AIR_MSG_UP_ABORT :
        {
            if ( LPP_MS_CAPABILITY == enMainState )
            {
                enSubState =  LPP_SS_CAP_WAIT_ABORT_CN_ACK;
            }
            else if ( LPP_MS_ASSISTDATA == enMainState )
            {
                enSubState =  LPP_SS_ASSISTDATA_WAIT_ABORT_CN_ACK;
            }
            else if ( LPP_MS_LOCATION == enMainState )
            {
                enSubState =  LPP_SS_WAIT_LOCATION_ABORT_CN_ACK;
            }
            else
            {
                NAS_LPP_ERR_LOG1("wrong lpp main state id:",enMainState);
                TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetWaitAckSubState_ENUM, LNAS_LPP_MAIN_STATE, enMainState);
                enSubState =  LPP_SS_BUTT;
            }
            break;
        }
        case NAS_LPP_AIR_MSG_PROVIDE_LOCATION_INFO :
        {
            enSubState =  LPP_SS_WAIT_LOCATION_CN_ACK;
            break;
        }
        default:
        {
            NAS_LPP_ERR_LOG1("wrong up lpp msg id:",ulUpLppMsgId);
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_GetWaitAckSubState_ENUM, LNAS_LPP_WrongUpLppMsgId);
            enSubState =  LPP_SS_BUTT;
            break;
        }
    }

    return enSubState;
}

/*****************************************************************************
 Function Name   : NAS_LPP_BuffFsmMsg
 Description     :   缓存消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-24  Draft Enact

*****************************************************************************/
/*VOS_VOID  NAS_LPP_PushBuffFsmMsg
(
    PS_MSG_HEADER_STRU                         *pstMsg,
    VOS_UINT32                                  ulSize,
    VOS_UINT8                                   ucTransIndex,
    NAS_LPP_BUFF_FSM_MSG_PRIORITY_ENUM_UINT8    enMsgPriority
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElement;
    VOS_VOID *pBuff;

    pstTransElement = NAS_LPP_GetTransElementByIndex(ucTransIndex);
    if ( NAS_LPP_NULL_PTR == pstTransElement)
    {
        NAS_LPP_ERR_LOG1("buff fsm msg with wrong trans index", ucTransIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_PushBuffFsmMsg_ENUM, LNAS_LPP_TransIndex, ucTransIndex);
        return;
    }

    if ( NAS_LPP_BUFF_FSM_MSG_PRIORITY_HIGH == enMsgPriority )
    {
        if ( pstTransElement->stFsmBuff.ucHighNum >= NAS_LPP_MAX_HIGH_FSM_MSG_BUFF_NUM )
        {
            NAS_LPP_ERR_LOG1("buff high fsm msg overlfow with  trans index", ucTransIndex);
            TLPS_PRINT2LAYER_ERROR1(NAS_LPP_PushBuffFsmMsg_ENUM, LNAS_LPP_TransIndex1, ucTransIndex);
            return;
        }
    }
    else
    {
        if ( pstTransElement->stFsmBuff.ucLowNum >= NAS_LPP_MAX_LOW_FSM_MSG_BUFF_NUM )
        {
            NAS_LPP_ERR_LOG1("buff low fsm msg overlfow with trans index", ucTransIndex);
            TLPS_PRINT2LAYER_ERROR1(NAS_LPP_PushBuffFsmMsg_ENUM, LNAS_LPP_TransIndex2, ucTransIndex);
            return;
        }
    }

    pBuff = NAS_LPP_MEM_ALLOC(ulSize);
    if ( NAS_LPP_NULL_PTR == pBuff)
    {
        NAS_LPP_ERR_LOG("buff fsm msg malloc buf fail");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_PushBuffFsmMsg_ENUM, LNAS_LPP_BuffFsmMallocBufFail);
        return;
    }

    NAS_LPP_MEM_CPY_S(pBuff, (VOS_UINT8 *)pstMsg, ulSize);

    if ( NAS_LPP_BUFF_FSM_MSG_PRIORITY_HIGH == enMsgPriority )
    {
        pstTransElement->stFsmBuff.astHighMsg[pstTransElement->stFsmBuff.ucHighNum].pMsg = pBuff;
        pstTransElement->stFsmBuff.astHighMsg[pstTransElement->stFsmBuff.ucHighNum].ulMsgId = pstMsg->ulMsgName;
        pstTransElement->stFsmBuff.astHighMsg[pstTransElement->stFsmBuff.ucHighNum].ulSenderPid = pstMsg->ulSenderPid;
        pstTransElement->stFsmBuff.ucHighNum++;
    }
    else
    {
        pstTransElement->stFsmBuff.astLowMsg[pstTransElement->stFsmBuff.ucLowNum].pMsg = pBuff;
        pstTransElement->stFsmBuff.astLowMsg[pstTransElement->stFsmBuff.ucLowNum].ulMsgId = pstMsg->ulMsgName;
        pstTransElement->stFsmBuff.astLowMsg[pstTransElement->stFsmBuff.ucLowNum].ulSenderPid = pstMsg->ulSenderPid;
        pstTransElement->stFsmBuff.ucLowNum++;
    }
}*/
/*****************************************************************************
 Function Name   : NAS_LPP_PopFsmMsg
 Description     : 弹出消息
 Input           : None
 Output          : None
 Return          : 按照先进先出的顺序弹出

 History         :
    1.XiaoJun      2015-8-25  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_PopFsmMsg
(
    VOS_UINT8                                   ucTransIndex,
    NAS_LPP_BUFF_FSM_MSG_PRIORITY_ENUM_UINT8    enMsgPriority
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElement;
    NAS_LPP_FSM_MSG_BUFF_STRU               *pstFsmMsgBuff;
    PS_MSG_HEADER_STRU                      *pstMsg,*pstSndMsg;

    pstTransElement = NAS_LPP_GetTransElementByIndex(ucTransIndex);
    if ( NAS_LPP_NULL_PTR == pstTransElement)
    {
        NAS_LPP_ERR_LOG1("pop fsm msg with wrong trans index", ucTransIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_PopFsmMsg_ENUM, LNAS_LPP_TransIndex, ucTransIndex);
        return NAS_LPP_FAILURE;
    }

    if ( NAS_LPP_BUFF_FSM_MSG_PRIORITY_HIGH == enMsgPriority )
    {
        if (0 == pstTransElement->stFsmBuff.ucHighNum)
        {
            NAS_LPP_INFO_LOG("no high lpp fsm msg pop");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_PopFsmMsg_ENUM, LNAS_LPP_NoHighLppFsmMsgPop);
            return NAS_LPP_FSM_MSG_BUFF_EMPTY;
        }

        if (pstTransElement->stFsmBuff.ucHighNum > NAS_LPP_MAX_HIGH_FSM_MSG_BUFF_NUM)
        {
            NAS_LPP_ERR_LOG1("nas lpp pop high fsm msg overlfow,ucHighNum", pstTransElement->stFsmBuff.ucHighNum);
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_PopFsmMsg_ENUM, LNAS_LPP_HighFsmMsgOverFlow);
            return NAS_LPP_FAILURE;
        }

        /*先弹出先进来的消息*/
        pstFsmMsgBuff = &pstTransElement->stFsmBuff.astHighMsg[0];
        pstTransElement->stFsmBuff.ucHighNum--;

        /*后面的向队列前移动*/
        NAS_LPP_MEM_CPY_S(  &pstTransElement->stFsmBuff.astHighMsg[0],
                            pstTransElement->stFsmBuff.ucHighNum * sizeof(NAS_LPP_FSM_MSG_BUFF_STRU),
                            &pstTransElement->stFsmBuff.astHighMsg[1],
                            pstTransElement->stFsmBuff.ucHighNum * sizeof(NAS_LPP_FSM_MSG_BUFF_STRU));

    }
    else
    {
        if (0 == pstTransElement->stFsmBuff.ucLowNum)
        {
            NAS_LPP_INFO_LOG("no low lpp fsm msg pop");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_PopFsmMsg_ENUM, LNAS_LPP_NoLowLppFsmMsgPop);
            return NAS_LPP_FSM_MSG_BUFF_EMPTY;
        }

        if (pstTransElement->stFsmBuff.ucLowNum > NAS_LPP_MAX_LOW_FSM_MSG_BUFF_NUM)
        {
            NAS_LPP_ERR_LOG1("nas lpp pop low fsm msg overlfow,ucLowNum", pstTransElement->stFsmBuff.ucLowNum);
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_PopFsmMsg_ENUM, LNAS_LPP_PopLowFsmMsgOverflow);
            return NAS_LPP_FAILURE;
        }

        /*先弹出先进来的消息*/
        pstFsmMsgBuff = &pstTransElement->stFsmBuff.astLowMsg[0];
        pstTransElement->stFsmBuff.ucLowNum--;

        /*后面的向队列前移动*/
        NAS_LPP_MEM_CPY_S(  &pstTransElement->stFsmBuff.astLowMsg[0],
                            pstTransElement->stFsmBuff.ucLowNum * sizeof(NAS_LPP_FSM_MSG_BUFF_STRU),
                            &pstTransElement->stFsmBuff.astLowMsg[1],
                            pstTransElement->stFsmBuff.ucLowNum * sizeof(NAS_LPP_FSM_MSG_BUFF_STRU));

    }


    pstMsg = (PS_MSG_HEADER_STRU *)pstFsmMsgBuff->pMsg;
    pstSndMsg = (PS_MSG_HEADER_STRU *)NAS_LPP_ALLOC_MSG(pstMsg->ulLength + VOS_MSG_HEAD_LENGTH);
    if (NAS_LPP_NULL_PTR == pstSndMsg)
    {
        NAS_LPP_ERR_LOG("POP FSM msg alloc msg fail");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_PopFsmMsg_ENUM, LNAS_LPP_PopFsmMsgAllocMsgFail);

        NAS_LPP_MEM_FREE(pstMsg);
        return NAS_LPP_FAILURE;
    }

    NAS_LPP_MEM_CPY_S(  pstSndMsg,
                        (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH),
                        pstMsg,
                        (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH) );
    NAS_LPP_SND_MSG(pstSndMsg);
    NAS_LPP_MEM_FREE(pstMsg);

    return NAS_LPP_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_LPP_JustFsmMsgToPop
 Description     : 根据目标状态，确定是否需要弹出缓存的消息来处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_JustFsmMsgToPop
(
    VOS_UINT8                           ucTransIndx,
    NAS_LPP_MAIN_STATE_ENUM_UINT32      enLppMainState,
    NAS_LPP_SUB_STATE_ENUM_UINT32       enLppSubState
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity;
    VOS_UINT32 ulRslt;

    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);

    if ( NAS_LPP_NULL_PTR == pstTransEntity )
    {
        NAS_LPP_ERR_LOG1("wrong ucTransIndx for POP MSG",ucTransIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_JustFsmMsgToPop_ENUM, LNAS_LPP_TransIndex, ucTransIndx);
        return;
    }

    switch ( enLppSubState )
    {
        case LPP_SS_IDLE :
        case LPP_SS_WAIT_MEAS_IND :
        {
            ulRslt = NAS_LPP_PopFsmMsg(ucTransIndx,NAS_LPP_BUFF_FSM_MSG_PRIORITY_HIGH);
            if (NAS_LPP_FSM_MSG_BUFF_EMPTY == ulRslt)
            {
                ulRslt = NAS_LPP_PopFsmMsg(ucTransIndx,NAS_LPP_BUFF_FSM_MSG_PRIORITY_LOW);
                if (NAS_LPP_FSM_MSG_BUFF_EMPTY != ulRslt)
                {
                    NAS_LPP_INFO_LOG("POP NAS LPP LOW MSG");
                    TLPS_PRINT2LAYER_INFO(NAS_LPP_JustFsmMsgToPop_ENUM, LNAS_LPP_PopNasLppLowMsg);
                }
            }
            break;
        }
        default:

            break;
    }
}


/*****************************************************************************
 Function Name   : NAS_LPP_ChangeTransFsmSubState
 Description     : 修改子状态
 Input           : ucSessionIndx---在session entity pool里的位置,
                   ucSessionTransIndx-- ucTransIndx在session entity里aucTransElementIdx[NAS_LPP_MAX_TRANS_COUNT]的位置
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-7-21  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_ChangeTransFsmState
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    NAS_LPP_MAIN_STATE_ENUM_UINT32      enLppMainState,
    NAS_LPP_SUB_STATE_ENUM_UINT32       enLppSubState
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU *pstSessionEntity;
    VOS_UINT8 ucTransIndx;
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName;

    NAS_LPP_WARN_LOG("NAS_LPP_ChangeTransFsmState!!");
    TLPS_PRINT2LAYER_ERROR(NAS_LPP_ChangeTransFsmState_ENUM, LNAS_LPP_Func_Enter);

    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if ( NAS_LPP_NULL_PTR == pstSessionEntity )
    {
        NAS_LPP_ERR_LOG1("wrong session index for change State",ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ChangeTransFsmState_ENUM, LNAS_LPP_SessionIndex, ucSessionIndx);

        return;
    }

    if ( (enLppMainState >= LPP_MS_BUTT) || (enLppSubState >= LPP_SS_BUTT) )
    {
        NAS_LPP_ERR_LOG2("wrong main state and substate for change State",enLppMainState, enLppSubState);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ChangeTransFsmState_ENUM, LNAS_LPP_MAIN_STATE, enLppMainState);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ChangeTransFsmState_ENUM, LNAS_LPP_SUB_STATE, enLppSubState);
        return;
    }


    ucTransIndx = pstSessionEntity->stLppTrans.aucTransElementIdx[ucSessionTransIndx];

    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);

    if ( NAS_LPP_NULL_PTR == pstTransEntity )
    {
        NAS_LPP_ERR_LOG1("wrong ucSessionTransIndx for change State",ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ChangeTransFsmState_ENUM, LNAS_LPP_SessionTransIndex, ucSessionTransIndx);
        return;
    }

    /*当前状态的定时器名称*/
    enTimeName = NAS_LPP_GetTimeNameBySubState(pstTransEntity->enLppSubState );

    if ( NAS_LPP_NULL_PTR != pstTransEntity->stLppTimer.hTimer )
    {
        NAS_LPP_TimerStop(ucSessionIndx, ucSessionTransIndx, enTimeName);
    }

    NAS_LPP_OmStateChgInd(ucSessionIndx,
                          ucSessionTransIndx,
                          ucTransIndx,
                          pstTransEntity->enLppMainState,
                          pstTransEntity->enLppSubState,
                          enLppMainState,
                          enLppSubState);

    pstTransEntity->enLppSubState = enLppSubState;
    pstTransEntity->enLppMainState = enLppMainState;

    /*目标状态的定时器名称*/
    enTimeName = NAS_LPP_GetTimeNameBySubState(pstTransEntity->enLppSubState );
    if ( enTimeName < TI_NAS_LPP_TIMER_PARA_BUTT)
    {
        NAS_LPP_TimerStart(ucSessionIndx, ucSessionTransIndx, enTimeName);
    }

    /*根据目标状态，如果是平稳态，从trans里取出缓存的消息处理*/
    NAS_LPP_JustFsmMsgToPop(ucTransIndx,enLppMainState,enLppSubState);

}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppMainState
 Description    : 获取当前的主状态
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT8

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_GetLppMainState
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx
)
{
    VOS_UINT8                                   ucTransIndex = 0;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransElementEntity = NAS_LPP_NULL_PTR;

    /*取出session中transaction实体中存储单元的index*/
    ucTransIndex = (VOS_UINT8)NAS_LPP_GetTransIdIndex(ucSessionIndx, ucSessionTransIndx);

    /*根据index去得到内存池中的transaction实体*/
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndex);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        return PS_NULL_UINT32;
    }

    return (pstTransElementEntity->enLppMainState);
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppSubState
 Description    : 获取当前的子状态
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT8

 History        :
      1.lifuxin 00253982 2015-7-20  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_GetLppSubState
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndex
)
{
    VOS_UINT8                                   ucTransIndex            = 0;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransElementEntity   = NAS_LPP_NULL_PTR;

    /*取出session中transaction实体中存储单元的index*/
    ucTransIndex = (VOS_UINT8)NAS_LPP_GetTransIdIndex(ucSessionIndx, ucSessionTransIndex);

    /*根据index去得到内存池中的transaction实体*/
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndex);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        return PS_NULL_UINT32;
    }

    return (pstTransElementEntity->enLppSubState);
}



#endif //#if (FEATURE_LPP == FEATURE_ON)








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

