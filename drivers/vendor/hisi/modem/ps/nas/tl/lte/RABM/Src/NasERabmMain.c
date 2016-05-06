/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : RabmMain.c
  Description     : 该C文件给出了RABM_MAIN模块的实现
  History         :
  1.杨茜惠 00135146       2008-9-1  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmMain.h"
#include  "LRrcLNasInterface.h"
#include  "NasERabmAppMsgProc.h"
#include  "NasERabmETcMsgProc.h"
#include  "NasIpInterface.h"
#include  "NasERabmIpFilter.h"
#include  "NasERabmIpfOm.h"
#include  "NasERabmCdsMsgProc.h"
#include  "CdsErabmInterface.h"
#include  "PsRrmInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMMAIN_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMMAIN_C
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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
NAS_ERABM_EHRPD_ENTITY_STRU             g_stNasERabmEhrpdEntity;   /*RABM的EHRPD承载管理实体定义*/
#endif

NAS_ERABM_ENTITY_STRU   g_stNasERabmEntity;                /*RABM实体定义*/
NAS_ERABM_ENTITY_STRU   *pg_stNasERabmEntity = &g_stNasERabmEntity;
VOS_UINT8              g_aucERabmIpData[NAS_ERABM_IP_HEADER_BUFFER_LEN] = {0};        /* 用于存储转化格式后的IP包头 */
NAS_ERABM_SERVICE_STATE_ENUM_UINT32 g_enERabmSrState;           /*通知EMM发起Service req流程标识*/
EMM_ERABM_UP_DATA_PENDING_ENUM_UINT32    g_enERabmUlDataPending = EMM_ERABM_NO_UP_DATA_PENDING;
VOS_UINT32             g_ulERabmBufTimerLength  = 60000;   /* 环回缓存定时器，初始化为60秒 */

NAS_COMM_PRINT_LIST_STRU g_astERabmRrcMsgIdArray[] =
{
    {   ID_LRRC_LRABM_QOS_UPDATE_REQ      ,
            "MSG:  ID_LRRC_LRABM_QOS_UPDATE_REQ                      ",
        VOS_NULL_PTR},
    {   ID_LRRC_LRABM_RAB_RSP             ,
            "MSG:  ID_LRRC_LRABM_RAB_RSP                             ",
        VOS_NULL_PTR},
    {   ID_LRRC_LRABM_RAB_IND             ,
            "MSG:  ID_LRRC_LRABM_RAB_IND                             ",
        NAS_ERABM_PrintRabmRrcRabInd},
    {   ID_LRRC_LRABM_STATUS_IND          ,
            "MSG:  ID_LRRC_LRABM_STATUS_IND                          ",
        NAS_ERABM_PrintRabmRrcStatusInd},
    {   ID_LRRC_LRABM_STATUS_RSP          ,
            "MSG:  ID_LRRC_LRABM_STATUS_RSP                          ",
        VOS_NULL_PTR}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astERabmStateTimerArray[] =
{
    {   NAS_ERABM_WAIT_EPSB_ACT_TIMER               ,
            "STATE TI:  NAS_ERABM_WAIT_EPSB_ACT_TIMER                           "},
    {   NAS_ERABM_WAIT_RB_REEST_TIMER               ,
            "STATE TI:  NAS_ERABM_WAIT_RB_REEST_TIMER                           "}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astERabmAppMsgIdArray[] =
{
    {   ID_APP_ERABM_DATA_TRANS_REQ               ,
            "MSG:  ID_APP_ERABM_DATA_TRANS_REQ                           "},
    {   ID_APP_ERABM_DATA_TRANS_CNF               ,
            "MSG:  ID_APP_ERABM_DATA_TRANS_CNF                           "},
    {   ID_APP_ERABM_SERVICE_REQ                  ,
            "MSG:  ID_APP_ERABM_SERVICE_REQ                              "}
};

/* CDS-RABM 消息打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astERabmCdsMsgIdArray[] =
{
    {   ID_CDS_ERABM_SERVICE_NOTIFY               ,
            "MSG:  ID_CDS_ERABM_SERVICE_NOTIFY                           "},
    {   ID_ERABM_CDS_SEND_BUFF_DATA_IND               ,
            "MSG:  ID_ERABM_CDS_SEND_BUFF_DATA_IND                       "},
    {   ID_ERABM_CDS_FREE_BUFF_DATA_IND                  ,
            "MSG:  ID_ERABM_CDS_FREE_BUFF_DATA_IND                       "},
    {   ID_QOS_FC_ERABM_RAB_CREATE_IND                  ,
            "MSG:  ID_QOS_FC_ERABM_RAB_CREATE_IND                       "},
    {   ID_QOS_FC_ERABM_RAB_RELEASE_IND                  ,
            "MSG:  ID_QOS_FC_ERABM_RAB_RELEASE_IND                       "}


};
NAS_ERABM_IPV4_SEGMENT_BUFF_STRU        g_stErabmIpv4SegBuff  = {NAS_ERABM_NULL};


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_ERABM_TaskEntry
 Description     : RABM模块TASK入口处理,根据接收到的消息的所属模块,将消息分发给处理该模块消息的子模块.
 Input           : struct MsgCB* pMsg---------消息指针
 Output          : VOS_VOID
 Return          : VOS_VOID

 History         :
 杨茜惠 00135146         2008-9-1  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ERABM_TaskEntry( MsgBlock* pMsg )
{
    PS_MSG_HEADER_STRU       *pHeader = VOS_NULL_PTR;              /*定义消息头指针*/

    /* 判断入口参数是否合法*/
    if (VOS_NULL_PTR == pMsg)
    {
        /*报告错误消息*/
        NAS_ERABM_WARN_LOG("NAS_ERABM_TaskEntry:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TaskEntry_ENUM, LNAS_ERABM_NoMsg);
        return;
    }

#if (VOS_WIN32 != VOS_OS_VER)
    TLPS_ExcLog_SaveMsgList(pMsg);
#endif


    pHeader = (PS_MSG_HEADER_STRU *)pMsg;          /* 获取消息头指针*/

    NAS_ERABM_PrintRabmRevMsg(pHeader,NAS_COMM_GET_ESM_PRINT_BUF());

    /*判断接收到的消息,进行分发处理*/
    switch (pHeader->ulSenderPid)
    {
        /*如果是SM消息，调用SM分发函数*/
        case PS_PID_ESM:
            NAS_ERABM_EsmMsgDistr(pMsg);
            break;

        /*如果是EMM消息，调用EMM分发函数*/
        case PS_PID_MM:
            NAS_ERABM_EmmMsgDistr(pMsg);
            break;

        /*如果是RRC消息，调用RRC分发函数*/
        case PS_PID_ERRC:
            NAS_ERABM_RrcMsgDistr(pMsg);
            break;

        /*如果是Timer消息，调用Timer溢出分发函数*/
        case VOS_PID_TIMER:
            NAS_ERABM_TimerMsgDistr(pMsg);
            break;

        /*如果是APP消息，调用APP分发函数*/
        case PS_PID_APP:
            NAS_ERABM_AppMsgDistr(pMsg);
            break;

        case PS_PID_TC:
            NAS_ERABM_TcMsgDistr(pMsg);
            break;
        case UEPS_PID_CDS:
            NAS_ERABM_CdsMsgDistr(pMsg);
            break;
        /* 新增RRM消息处理 */
        case UEPS_PID_RRM:
            NAS_ERABM_RrmMsgDistr(pMsg);
            break;
        /*发送对象错误，报警*/
        default:
            NAS_ERABM_LOG1("NAS_ERABM_TaskEntry:NORM: Error SenderPid :",(VOS_INT32)pHeader->ulSenderPid);
            TLPS_PRINT2LAYER_INFO1(NAS_ERABM_TaskEntry_ENUM, LNAS_ERABM_ErrorSenderPid, (VOS_INT32)pHeader->ulSenderPid);
            break;
    }
    /* RABM消息处理完推送打印 */
    TLPS_SendPrintBufferInfo();

}

/*******************************************************************************
 Function Name  : NAS_ERABM_TimerStart()
 Description    : RABM定时器启动函数
 Input          : VOS_UINT32  ulTimerLen    Timer的时长
                  VOS_UINT8   ecTimerName   Timer的名字
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
  1.杨茜惠 00135146      2008-09-3  Draft Enact
  2.lihong 00150010      2012-12-14 Modify:Emergency
*******************************************************************************/
VOS_VOID NAS_ERABM_TimerStart
(
    VOS_UINT32                          ulTimerLen,
    NAS_ERABM_TIMER_NAME_ENUM_UINT8     enTimerName,
    VOS_UINT32                          ulTimerPara
)
{
    NAS_ERABM_START_TIMER_STRU       *pstTimerInfo = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_TimerStart is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStart_ENUM, LNAS_ENTRY);

    /*获取RABM实体中的定时器结构地址指针*/
    pstTimerInfo = NAS_ERABM_GetRbTimer(enTimerName);

    if ( VOS_NULL_PTR == pstTimerInfo )
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_TimerStart: pstStateTimer NULL.");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TimerStart_ENUM, LNAS_ERABM_StateTimerIsNULL);
        return ;
    }

    /*判断定时器是否打开，打开则关闭*/
    if (VOS_NULL_PTR != pstTimerInfo->stHTimer)
    {
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->stHTimer)))
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_TimerStart: start reltimer error1 ");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL1);
            return;
        }

        NAS_ERABM_LOG1("(TimerType) Timer not close!", (VOS_INT32)enTimerName);
        TLPS_PRINT2LAYER_INFO1(NAS_ERABM_TimerStart_ENUM, LNAS_ERABM_TimerName, (VOS_INT32)enTimerName);
    }

    if(NAS_ERABM_NULL == ulTimerLen)
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_TimerStart:WARN: TimerLen = 0");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL2);
        return;
    }
    /*设定定时器LENGTH和NAME，打开失败则报警返回*/
    if (VOS_OK !=
            PS_START_REL_TIMER(&(pstTimerInfo->stHTimer),PS_PID_RABM,
                                ulTimerLen,(VOS_UINT32)enTimerName, ulTimerPara,
                                VOS_RELTIMER_NOLOOP))
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_TimerStart:WARN: start reltimer error2");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL3);
        return;
    }

    /*钩出当前的定时器信息 */
    NAS_ERABM_SndOmErabmTimerStatus(NAS_ERABM_TIMER_RUNNING, enTimerName, ulTimerLen);


    /*更新定时器开启信息和定时器类别*/
    pstTimerInfo->enName   = enTimerName;

    /*根据定时器的不同类型,打印相应信息*/
    switch (enTimerName)
    {
        case NAS_ERABM_WAIT_EPSB_ACT_TIMER:
            NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStart:NORM:RABM TimerStart: NAS_ERABM_RB_WAIT_EPSB_ACT_TIMER");
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL5);
            break;

        case NAS_ERABM_WAIT_RB_REEST_TIMER:
            NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStart:NORM:RABM TimerStart: NAS_ERABM_WAIT_RB_REEST_TIMER");
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL6);
            break;

        case NAS_ERABM_WAIT_RB_RESUME_TIMER:
            NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStart:NORM:RABM TimerStart: NAS_ERABM_WAIT_RB_RESUME_TIMER");
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL7);
            break;

        case NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER:
            NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStart:NORM:RABM TimerStart: NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER");
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL8);
            break;
        case NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER:
            NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStart:NORM:RABM TimerStart: NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER");
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL9);
            break;
        default:
            NAS_ERABM_ERR_LOG("NAS_ERABM_TimerStart:ERROR: start unreasonable reltimer.");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL10);
            break;
    }
}

/*******************************************************************************
 Function Name  : NAS_ERABM_TimerStop()
 Description    : RABM定时器停止函数
 Input          : VOS_UINT8 ecTimerName
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
  1.杨茜惠  00135146      2008-09-3  Draft Enact
  2.杨茜惠  00135146      2009-9-19  BN8D01065   Modify
*******************************************************************************/
VOS_VOID NAS_ERABM_TimerStop( NAS_ERABM_TIMER_NAME_ENUM_UINT8 enTimerName )
{
    NAS_ERABM_START_TIMER_STRU       *pstTimerInfo = VOS_NULL_PTR;
    VOS_UINT32                        ulTimerRemainLen;

    /*如果ucTimerName对应的定时器处于启动状态，则停止；否则，忽略*/
    pstTimerInfo = NAS_ERABM_GetRbTimer(enTimerName);

    if ( VOS_NULL_PTR == pstTimerInfo )
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_TimerStop: pstStateTimer NULL.");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TimerStop_ENUM, LNAS_ERABM_StateTimerIsNULL);
        return ;
    }

    if (VOS_NULL_PTR != pstTimerInfo->stHTimer)
    {
        /* 获取当前定时器的剩余时间 */
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstTimerInfo->stHTimer), &ulTimerRemainLen ))
        {
            ulTimerRemainLen = 0;
        }

        /*关闭失败，则报警返回*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->stHTimer)))
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_TimerStop: stop reltimer fail ");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_TimerStop_ENUM, LNAS_FUNCTION_LABEL1);
            return;
        }

        /*更新定时器超时次数*/
        pstTimerInfo->ucExpireTimes = 0;


        /*钩出当前的定时器信息 */
        NAS_ERABM_SndOmErabmTimerStatus(NAS_ERABM_TIMER_STOPED, enTimerName, ulTimerRemainLen);


        /*根据定时器的不同类型,打印相应信息*/
        switch (enTimerName)
        {
            case NAS_ERABM_WAIT_EPSB_ACT_TIMER:
                NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStop:NORM:RABM TimerStop: NAS_ERABM_RB_WAIT_EPSB_ACT_TIMER");
                TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStop_ENUM, LNAS_FUNCTION_LABEL2);
                break;

            case NAS_ERABM_WAIT_RB_REEST_TIMER:
                NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStop:NORM:RABM TimerStop: NAS_ERABM_WAIT_RB_REEST_TIMER");
                TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStop_ENUM, LNAS_FUNCTION_LABEL3);
                break;

            case NAS_ERABM_WAIT_RB_RESUME_TIMER:
                NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStop:NORM:RABM TimerStop: NAS_ERABM_WAIT_RB_RESUME_TIMER");
                TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStop_ENUM, LNAS_FUNCTION_LABEL4);
                break;

            case NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER:
                NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStop:NORM:RABM TimerStop: NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER");
                TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStop_ENUM, LNAS_FUNCTION_LABEL5);
                break;
            case NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER:
                NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStop:NORM:RABM TimerStop: NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER");
                TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStop_ENUM, LNAS_FUNCTION_LABEL6);
                break;
            default:
                NAS_ERABM_ERR_LOG("NAS_ERABM_TimerStop:ERROR: stop unreasonable reltimer.");
                TLPS_PRINT2LAYER_ERROR(NAS_ERABM_TimerStop_ENUM, LNAS_FUNCTION_LABEL7);
                break;
        }
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_IsTimerRunning
 Description     : 查询定时器是否在运行
 Input           : None
 Output          : None
 Return          : NAS_ERABM_TIMER_STATE_ENUM_UINT32

 History         :
    1.sunbing49683      2010-9-20  Draft Enact

*****************************************************************************/
NAS_ERABM_TIMER_STATE_ENUM_UINT32  NAS_ERABM_IsTimerRunning( NAS_ERABM_TIMER_NAME_ENUM_UINT8 enTimerName )
{
    NAS_ERABM_START_TIMER_STRU       *pstTimerInfo = VOS_NULL_PTR;

    /*如果ucTimerName对应的定时器处于启动状态，则停止；否则，忽略*/
    pstTimerInfo = NAS_ERABM_GetRbTimer(enTimerName);

    if ( VOS_NULL_PTR == pstTimerInfo )
    {
        NAS_ERABM_NORM_LOG("NAS_ERABM_IsTimerRunning: pstStateTimer NULL.");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_IsTimerRunning_ENUM, LNAS_ERABM_StateTimerIsNULL);
        return NAS_ERABM_TIMER_STATE_BUTT;
    }

    /*检查该状态定时器是否在运行*/
    if ( VOS_NULL_PTR != pstTimerInfo->stHTimer )
    {
        return NAS_ERABM_TIMER_STATE_RUNNING;
    }
    else
    {
        return NAS_ERABM_TIMER_STATE_STOPED;
    }

}

/*******************************************************************************
 Function Name  : NAS_ERABM_Init()
 Description    : RABM模块初始化函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
  1.杨茜惠 00135146      2008-09-5  Draft Enact
  2.杨茜惠 00135146      2009-9-19  BN8D01065   Modify

*****************************************************************************/
VOS_VOID NAS_ERABM_Init(VOS_VOID)
{
    VOS_UINT8                     ucTimerIndex  = 0;
    VOS_UINT32                    ulEpsbId      = 0;
    VOS_UINT32                    ulLoop        = 0;
    APP_ESM_IP_ADDR_STRU         *pstPdnAddr    = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM                          START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_Init_ENUM, LNAS_ENTRY);

    /*初始化RABM实体*/
    NAS_ERABM_MEM_SET_S((VOS_VOID*)NAS_ERABM_Entity(), sizeof(NAS_ERABM_ENTITY_STRU),NAS_ERABM_NULL, sizeof(NAS_ERABM_ENTITY_STRU));

    /* 初始化RABM统计信息 */
    NAS_ERABM_DebugInit();

    /*设置SERVICE流程没有启动状态*/
    NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_TERMIN);

    /*设置RABM没有等待EPS承载激活消息*/
    NAS_ERABM_SetWaitEpsBActSign(NAS_ERABM_NOT_WAIT_EPSB_ACT_MSG);

    /*设置L MODE的状态为SUSPENDED*/
    NAS_ERABM_SetLModeStatus(NAS_ERABM_L_MODE_STATUS_SUSPENDED);

    /*设置RRC请求建立RB的个数为0*/
    NAS_ERABM_SetRbNumInfo(0);

    /*设置唯一激活且没有TFT的承载号为NAS_ERABM_ILL_EPSB_ID*/
    NAS_ERABM_GetOnlyActiveAndNoUlTftEpsbId() = NAS_ERABM_ILL_EPSB_ID;

    /*设置不存在上行数据阻塞*/
    NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);

    /*初始化定时器信息*/
    for ( ucTimerIndex = 0; ucTimerIndex < NAS_NAS_ERABM_TIMER_NAME_BUTT; ucTimerIndex++ )
    {
        NAS_ERABM_TimerStop(ucTimerIndex);
    }

    /*初始化EPS承载列表*/
    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId <= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        pstPdnAddr = NAS_ERABM_GetEpsbPdnAddr(ulEpsbId);
        NAS_ERABM_SetEpsbIdInfo(ulEpsbId, ulEpsbId);
        NAS_ERABM_SetEpsbRbIdInfo(ulEpsbId, NAS_ERABM_ILL_RB_ID);
        NAS_ERABM_SetRbStateInfo(ulEpsbId, NAS_ERABM_RB_DISCONNECTED);
        NAS_ERABM_MEM_SET_S(pstPdnAddr,sizeof(APP_ESM_IP_ADDR_STRU), NAS_ERABM_NULL, sizeof(APP_ESM_IP_ADDR_STRU));
        NAS_ERABM_ClearEpsbResource(ulEpsbId);
    }

    /*初始化RB建立临时表信息*/
    for (ulLoop = 0; ulLoop < NAS_ERABM_MAX_EPSB_NUM; ulLoop++)
    {
        NAS_ERABM_SetRbSetupEpsbIdInfo(ulLoop, NAS_ERABM_ILL_EPSB_ID);
        NAS_ERABM_SetRbSetupRbIdInfo(ulLoop, NAS_ERABM_ILL_RB_ID);
    }

    /*初始化RABM灌包相关信息*/
    NAS_ERABM_StAppDataBitIpv4(NAS_ERABM_OP_FALSE);
    NAS_ERABM_StAppDataBitIpv6(NAS_ERABM_OP_FALSE);
    NAS_ERABM_SetAppDataRmtPortIpv4(NAS_ERABM_NULL);
    NAS_ERABM_SetAppDataRmtPortIpv6(NAS_ERABM_NULL);
    NAS_ERABM_SetAppDataOperateType(APP_ERABM_DATA_TRANS_OPERATE_BUTT);
    NAS_ERABM_MEM_SET_S(NAS_ERABM_GetAppDataRemoteIpv4Addr(),
                        sizeof(NAS_ERABM_GetAppDataRemoteIpv4Addr())/sizeof(VOS_UINT8),
                        NAS_ERABM_NULL,
                        sizeof(NAS_ERABM_GetAppDataRemoteIpv4Addr())/sizeof(VOS_UINT8));
    NAS_ERABM_MEM_SET_S(NAS_ERABM_GetAppDataRemoteIpv6Addr(),
                        sizeof(NAS_ERABM_GetAppDataRemoteIpv6Addr())/sizeof(VOS_UINT8),
                        NAS_ERABM_NULL,
                        sizeof(NAS_ERABM_GetAppDataRemoteIpv6Addr())/sizeof(VOS_UINT8));

    NAS_ERABM_MEM_SET_S(NAS_ERABM_GET_IP_HEADER_BUFFER(),
                        NAS_ERABM_IP_HEADER_BUFFER_LEN,
                        NAS_ERABM_NULL,
                        NAS_ERABM_IP_HEADER_BUFFER_LEN);

    NAS_ERABM_MEM_SET_S(  NAS_ERABM_GetIpv4SegBuffAddr(),
                        sizeof(NAS_ERABM_IPV4_SEGMENT_BUFF_STRU),
                        NAS_ERABM_NULL,
                        sizeof(NAS_ERABM_IPV4_SEGMENT_BUFF_STRU));


    /* 初始化上行NDIS Filter有效 */
    NAS_ERABM_SetUlNdisFilterValidFlag(NAS_ERABM_UL_NDIS_FILTER_INVALID);

    /* 初始化上行NDIS需要使用的IP Filter定义 */
    NAS_ERABM_IpfUlNdisFilterInit();

    /* 初始化IPF统计信息 */
    NAS_ERABM_IpfOmInit();

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 初始化EHRPD实体信息 */
    NAS_ERABM_InitEhrpdEntity();
    #endif

}

/*****************************************************************************
 Function Name  : NAS_ERABM_PidInit
 Discription    : RABM的PID初始化函数
 Input          :
 Output         : None
 Return Value   : None

 History:
      1.yangqianhui 00135146      2008-09-23  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ERABM_PidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch ( ip )
    {
        case    VOS_IP_LOAD_CONFIG:
                {
                    NAS_ERABM_Init();
                }
                break;

        case    VOS_IP_FARMALLOC:
        case    VOS_IP_INITIAL:
        case    VOS_IP_ENROLLMENT:
        case    VOS_IP_LOAD_DATA:
        case    VOS_IP_FETCH_DATA:
        case    VOS_IP_STARTUP:
        case    VOS_IP_RIVAL:
        case    VOS_IP_KICKOFF:
        case    VOS_IP_STANDBY:
        case    VOS_IP_BROADCAST_STATE:
        case    VOS_IP_RESTART:
        case    VOS_IP_BUTT:
                break;

        default:
                break;
    }

    return VOS_OK;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_SetEmmSrState
 Description     : 设置Service流程发起标识
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2010-9-16  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_SetEmmSrState( NAS_ERABM_SERVICE_STATE_ENUM_UINT32 enSrState )
{

    VOS_INT32     intLockLevel;

    if(enSrState >= NAS_ERABM_SERVICE_STATE_BUTT )
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_SetEmmSrState: Para is err.");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_SetEmmSrState_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    intLockLevel = VOS_SplIMP();

    g_enERabmSrState = enSrState;

    VOS_Splx(intLockLevel);

}

/*****************************************************************************
 Function Name   : NAS_ERABM_GetEmmSrState
 Description     : 获取Service流程发起标识
 Input           : None
 Output          : None
 Return          : NAS_ERABM_SERVICE_STATE_ENUM_UINT32

 History         :
    1.sunbing49683      2010-9-16  Draft Enact

*****************************************************************************/
NAS_ERABM_SERVICE_STATE_ENUM_UINT32  NAS_ERABM_GetEmmSrState( VOS_VOID )
{
    return g_enERabmSrState;
}


/*****************************************************************************
 Function Name   : NAS_ERABM_ClearEsmResource
 Description     : 清空RABM资源
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

  History        :
  1.杨茜惠 00135146      2008-09-5  Draft Enact
  2.杨茜惠 00135146      2009-9-19  BN8D01065   Modify
*****************************************************************************/
VOS_VOID NAS_ERABM_ClearRabmResource( VOS_VOID )
{
    VOS_UINT8                     ucTimerIndex  = NAS_ERABM_NULL;
    VOS_UINT32                    ulLoop        = NAS_ERABM_NULL;
    VOS_UINT32                    ulEpsbId      = NAS_ERABM_NULL;
    APP_ESM_IP_ADDR_STRU        *pstPdnAddr    = VOS_NULL_PTR;
    NAS_ERABM_L_MODE_STATUS_ENUM_UINT8 ucLModeStatus = NAS_ERABM_L_MODE_STATUS_BUTT;
    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_ClearRabmResource is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_ClearRabmResource_ENUM, LNAS_ENTRY);

    /* 停止已经启动的定时器 */
    for (ucTimerIndex = 0; ucTimerIndex < NAS_NAS_ERABM_TIMER_NAME_BUTT; ucTimerIndex++)
    {
        NAS_ERABM_TimerStop(ucTimerIndex);
    }
    /* 如果存在激活承载，则通知CDS释放缓存的数据包，加上此判断是为了避免重复
       通知CDS释放缓存数据包 */
    if (0 != NAS_ERABM_GetActiveEpsBearerNum())
    {
        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

        /* 只有不存在EHRPD承载时，才通知CDS释放缓存的数据包，如果存在EHRPD承载时，不能清除 */
        if(0 == NAS_ERABM_GetActiveEhrpdBearerNum())
        #endif
        {
            /* 通知CDS释放缓存的数据包 */
            NAS_ERABM_SndErabmCdsFreeBuffDataInd();
        }
    }

    ucLModeStatus = NAS_ERABM_GetLModeStatus();

    /*初始化RABM实体*/
    NAS_ERABM_MEM_SET_S((VOS_VOID*)NAS_ERABM_Entity(),sizeof(NAS_ERABM_ENTITY_STRU), NAS_ERABM_NULL, sizeof(NAS_ERABM_ENTITY_STRU));

    NAS_ERABM_SetLModeStatus(ucLModeStatus);

    /* 初始化RABM统计信息 */
    NAS_ERABM_DebugInit();

    /*设置SERVICE流程没有启动状态*/
    NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_TERMIN);

    /*设置RABM没有等待EPS承载激活消息*/
    NAS_ERABM_SetWaitEpsBActSign(NAS_ERABM_NOT_WAIT_EPSB_ACT_MSG);

    /*设置RRC请求建立RB的个数为0*/
    NAS_ERABM_SetRbNumInfo(0);

    /*设置唯一激活且没有TFT的承载号为NAS_ERABM_ILL_EPSB_ID*/
    NAS_ERABM_GetOnlyActiveAndNoUlTftEpsbId() = NAS_ERABM_ILL_EPSB_ID;

    /*设置不存在上行数据阻塞*/
    NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);

    /*初始化EPS承载列表*/
    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId <= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        pstPdnAddr = NAS_ERABM_GetEpsbPdnAddr(ulEpsbId);
        NAS_ERABM_SetEpsbIdInfo(ulEpsbId, ulEpsbId);
        NAS_ERABM_SetEpsbRbIdInfo(ulEpsbId, NAS_ERABM_ILL_RB_ID);
        NAS_ERABM_SetRbStateInfo(ulEpsbId, NAS_ERABM_RB_DISCONNECTED);
        NAS_ERABM_MEM_SET_S(pstPdnAddr,sizeof(APP_ESM_IP_ADDR_STRU), NAS_ERABM_NULL, sizeof(APP_ESM_IP_ADDR_STRU));
        NAS_ERABM_ClearEpsbResource(ulEpsbId);
    }

    /*初始化RB建立临时表信息*/
    for (ulLoop = 0; ulLoop < NAS_ERABM_MAX_EPSB_NUM; ulLoop++)
    {
        NAS_ERABM_SetRbSetupEpsbIdInfo(ulLoop, NAS_ERABM_ILL_EPSB_ID);
        NAS_ERABM_SetRbSetupRbIdInfo(ulLoop, NAS_ERABM_ILL_RB_ID);
    }

    /*初始化RABM灌包相关信息*/
    NAS_ERABM_StAppDataBitIpv4(NAS_ERABM_OP_FALSE);
    NAS_ERABM_StAppDataBitIpv6(NAS_ERABM_OP_FALSE);
    NAS_ERABM_SetAppDataRmtPortIpv4(NAS_ERABM_NULL);
    NAS_ERABM_SetAppDataRmtPortIpv6(NAS_ERABM_NULL);
    NAS_ERABM_SetAppDataOperateType(APP_ERABM_DATA_TRANS_OPERATE_BUTT);
    NAS_ERABM_MEM_SET_S(NAS_ERABM_GetAppDataRemoteIpv4Addr(),
                        sizeof(NAS_ERABM_GetAppDataRemoteIpv4Addr())/sizeof(VOS_UINT8),
                        NAS_ERABM_NULL,
                        sizeof(NAS_ERABM_GetAppDataRemoteIpv4Addr())/sizeof(VOS_UINT8));
    NAS_ERABM_MEM_SET_S(NAS_ERABM_GetAppDataRemoteIpv6Addr(),
                        sizeof(NAS_ERABM_GetAppDataRemoteIpv6Addr())/sizeof(VOS_UINT8),
                        NAS_ERABM_NULL,
                        sizeof(NAS_ERABM_GetAppDataRemoteIpv6Addr())/sizeof(VOS_UINT8));

    NAS_ERABM_MEM_SET_S(NAS_ERABM_GET_IP_HEADER_BUFFER(),
                        NAS_ERABM_IP_HEADER_BUFFER_LEN,
                        NAS_ERABM_NULL,
                        NAS_ERABM_IP_HEADER_BUFFER_LEN);

    NAS_ERABM_MEM_SET_S(  NAS_ERABM_GetIpv4SegBuffAddr(),
                        sizeof(NAS_ERABM_IPV4_SEGMENT_BUFF_STRU),
                        NAS_ERABM_NULL,
                        sizeof(NAS_ERABM_IPV4_SEGMENT_BUFF_STRU));

    /* 清空下行FILTER配置 */
    NAS_ERABM_MEM_SET_S(   NAS_ERABM_IPF_GET_DL_FILTER_PTR(0),
                        (NAS_ERABM_IPF_MAX_DL_FILTER * sizeof(IPF_FILTER_CONFIG_S)),
                        NAS_ERABM_NULL,
                        (NAS_ERABM_IPF_MAX_DL_FILTER * sizeof(IPF_FILTER_CONFIG_S)));
    NAS_ERABM_IPF_SET_DL_FILTER_NUM(0);

    /* 初始化上行NDIS Filter有效 */
    NAS_ERABM_SetUlNdisFilterValidFlag(NAS_ERABM_UL_NDIS_FILTER_INVALID);
}


VOS_INT32  NAS_ERABM_PrintRabmRrcStatusInd
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT32                          ulLoop      = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    LRRC_LRABM_STATUS_IND_STRU           *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;


    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :LRRC_LRABM_STATUS_IND_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " enStatus = %d \r\n",
                       pstRcvMsg->enStatus,
                       &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulRabCnt = %d \r\n",
                       pstRcvMsg->ulRabCnt,
                       &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    for (ulLoop = 0; ulLoop < pstRcvMsg->ulRabCnt; ulLoop++)
    {
        NAS_COMM_nsprintf_2(pcBuff,
                           usTotalLen,
                           " aulRabId[%d] = %d \r\n",
                           ulLoop,
                           pstRcvMsg->aulRabId[ulLoop],
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }

    /* 打印消息的结束标题*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :LRRC_LRABM_STATUS_IND_STRU****************",
                    &ilOutPutLen);

   usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}



VOS_INT32  NAS_ERABM_PrintRabmRrcRabInd
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT32                          ulLoop      = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    LRRC_LRABM_RAB_IND_STRU              *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;


    /* 打印消息结构标题 */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :LRRC_LRABM_RAB_IND_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印消息的每个数据*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulRabCnt = %d \r\n",
                       pstRcvMsg->ulRabCnt,
                       &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    for (ulLoop = 0; ulLoop < pstRcvMsg->ulRabCnt; ulLoop++)
    {
        NAS_COMM_nsprintf_2(pcBuff,
                           usTotalLen,
                           " astRabInfo[%d].enRabChangeType = %d \r\n",
                           ulLoop,
                           pstRcvMsg->astRabInfo[ulLoop].enRabChangeType,
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_2(pcBuff,
                           usTotalLen,
                           " astRabInfo[%d].ulRabId = %d \r\n",
                           ulLoop,
                           pstRcvMsg->astRabInfo[ulLoop].ulRabId,
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_2(pcBuff,
                           usTotalLen,
                           " astRabInfo[%d].ulRbId = %d \r\n",
                           ulLoop,
                           pstRcvMsg->astRabInfo[ulLoop].ulRbId,
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }

    /* 打印消息的结束标题*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :LRRC_LRABM_RAB_IND_STRU****************",
                    &ilOutPutLen);

   usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}



VOS_INT32  NAS_ERABM_PrintRabmRrcMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRabmRrcMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* 获得消息表的长度 */
    ulRabmRrcMsgNum = sizeof(g_astERabmRrcMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    /* 查找对应的消息 */
    for (ulLoop = 0; ulLoop< ulRabmRrcMsgNum ; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astERabmRrcMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* 打印对应的消息 */
    if ( ulLoop < ulRabmRrcMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usOffset,
                         (VOS_CHAR *)(g_astERabmRrcMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astERabmRrcMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astERabmRrcMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                     usTotalLen,
                                                                     pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_ERABM_LOG1("NAS_ERABM_PrintRabmRrcMsg, Invalid enMsgId: ",pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_INFO1(NAS_ERABM_PrintRabmRrcMsg_ENUM, LNAS_PARAM_INVALID, pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);

}

VOS_INT32  NAS_ERABM_PrintRabmAppMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    EMM_ERABM_MSG_TYPE_ENUM_UINT32        enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRabmAppMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* 获得消息表的长度 */
    ulRabmAppMsgNum = sizeof(g_astERabmAppMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    /* 查找对应的消息 */
    for (ulLoop = 0; ulLoop< ulRabmAppMsgNum ; ulLoop++)
    {
        if (enMsgId == g_astERabmAppMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* 打印对应的消息 */
    if ( ulLoop < ulRabmAppMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astERabmAppMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_ERABM_LOG1("NAS_ERABM_PrintRabmAppMsg, Invalid enMsgId: ",enMsgId);
        TLPS_PRINT2LAYER_INFO1(NAS_ERABM_PrintRabmAppMsg_ENUM, LNAS_PARAM_INVALID, enMsgId);
    }

    return (usTotalLen - usOffset);

}





VOS_INT32  NAS_ERABM_PrintRabmTimer
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    VOS_UINT32                           ulTimerType
)

{
    VOS_UINT32                          ulRabmTimerNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* 获得消息表的长度 */
    ulRabmTimerNum = sizeof(g_astERabmStateTimerArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    /* 打印对应的消息 */
    if ( ulTimerType < ulRabmTimerNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astERabmStateTimerArray[ulTimerType].aucPrintString),
                         &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_ERABM_LOG1("NAS_ERABM_PrintRabmTimer, Invalid enMsgId: ",ulTimerType);
        TLPS_PRINT2LAYER_INFO1(NAS_ERABM_PrintRabmTimer_ENUM, LNAS_PARAM_INVALID, ulTimerType);
    }

    return (usTotalLen - usOffset);

}


VOS_INT32  NAS_ERABM_PrintRabmCdsMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    CDS_ERABM_MSG_ID_ENUM_UINT32         enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRabmAppMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* 获得消息表的长度 */
    ulRabmAppMsgNum = sizeof(g_astERabmCdsMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    /* 查找对应的消息 */
    for (ulLoop = 0; ulLoop< ulRabmAppMsgNum ; ulLoop++)
    {
        if (enMsgId == g_astERabmCdsMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* 打印对应的消息 */
    if ( ulLoop < ulRabmAppMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astERabmCdsMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_ERABM_LOG1("NAS_ERABM_PrintRabmCdsMsg, Invalid enMsgId: ",enMsgId);
        TLPS_PRINT2LAYER_INFO1(NAS_ERABM_PrintRabmCdsMsg_ENUM, LNAS_PARAM_INVALID, enMsgId);
    }

    return (usTotalLen - usOffset);

}


VOS_VOID NAS_ERABM_PrintRabmRevMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
)
{
    VOS_INT32                           ilOutPutLenHead     = 0;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen          = 0;

    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "NAS RABM Receive Message:",
                     &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_PrintRabmRevMsg, Print receive msg header exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_PrintRabmRevMsg_ENUM, LNAS_ReceiveMsgHeaderException);
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印各个PID的消息 */
    switch ( pstMsg->ulSenderPid )
    {
        case PS_PID_ESM:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "ESM-->RABM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintEsmRabmMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg);

            break;

        case PS_PID_MM:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "MM-->RABM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintMmRabmMsg(pcBuff,
                                             usTotalLen,
                                             pstMsg->ulMsgName);

            break;

        case PS_PID_ERRC:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "RRC-->RABM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ERABM_PrintRabmRrcMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg);

            break;

        case PS_PID_OM  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "APP(OM)-->RABM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ERABM_PrintRabmAppMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg->ulMsgName);
            break;

        case PS_PID_TC  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "TC-->RABM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintRabmTcMsg(pcBuff,
                                             usTotalLen,
                                             pstMsg->ulMsgName);
            break;


        case VOS_PID_TIMER  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "TIMER-->RABM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ERABM_PrintRabmTimer(pcBuff,
                                            usTotalLen,
                                           ((REL_TIMER_MSG *)(VOS_VOID *) pstMsg)->ulPara);
            break;

        case UEPS_PID_CDS  :
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "CDS-->RABM\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ERABM_PrintRabmCdsMsg(    pcBuff,
                                                        usTotalLen,
                                                        pstMsg->ulMsgName);
            break;
        default:
            NAS_ERABM_LOG2("NAS_ERABM_PrintRabmRevMsg,Invalid Pid, MsgId: ",
                          pstMsg->ulSenderPid,
                          pstMsg->ulMsgName);
            TLPS_PRINT2LAYER_INFO2(NAS_ERABM_PrintRabmRevMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulSenderPid, pstMsg->ulMsgName);

            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        NAS_ERABM_LOG2("NAS_ERABM_PrintRabmRevMsg, print return zero length.SenderPid, MsgId: ",
                      pstMsg->ulSenderPid,
                      pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_INFO2(NAS_ERABM_PrintRabmRevMsg_ENUM, LNAS_FUNCTION_LABEL2, pstMsg->ulSenderPid, pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff, usTotalLen);

    return ;

}


VOS_VOID NAS_ERABM_PrintRabmSendMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
)

{
    VOS_INT32                           ilOutPutLenHead     = 0;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen          = 0;

    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "NAS RABM Send Message:",
                     &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_PrintRabmSendMsg, Print send msg header exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_PrintRabmSendMsg_ENUM, LNAS_SendMsgHeaderException);
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;


    /* 打印各个PID的消息 */
    switch ( pstMsg->ulReceiverPid )
    {
        case PS_PID_ESM :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "RABM-->ESM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintEsmRabmMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg);
            break;

        case PS_PID_MM :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "RABM-->MM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintMmRabmMsg(
                                             pcBuff,
                                             usTotalLen,
                                             pstMsg->ulMsgName);
            break;

        case PS_PID_ERRC :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "RABM-->RRC\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ERABM_PrintRabmRrcMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg);
            break;

        case PS_PID_OM  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "RABM-->APP(OM)\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ERABM_PrintRabmAppMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg->ulMsgName);
            break;

        case PS_PID_TC  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "RABM-->TC\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintRabmTcMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg->ulMsgName);
            break;
        case UEPS_PID_CDS  :
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "RABM-->CDS\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ERABM_PrintRabmCdsMsg(    pcBuff,
                                                        usTotalLen,
                                                        pstMsg->ulMsgName);
            break;
        default:
            NAS_ERABM_LOG2("NAS_ERABM_PrintRabmSendMsg,Invalid Pid, MsgId: ",
                          pstMsg->ulReceiverPid,
                          pstMsg->ulMsgName);
            TLPS_PRINT2LAYER_INFO2(NAS_ERABM_PrintRabmSendMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulReceiverPid, pstMsg->ulMsgName);
            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        NAS_ERABM_LOG2("NAS_ERABM_PrintRabmSendMsg, print return zero length. ReceiverPid, MsgId: ",
                      pstMsg->ulReceiverPid,
                      pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_INFO2(NAS_ERABM_PrintRabmSendMsg_ENUM, LNAS_FUNCTION_LABEL2, pstMsg->ulReceiverPid, pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff,usTotalLen);

    return ;

}

/*****************************************************************************
 Function Name   : NAS_ERABM_GetActiveEpsBearerNum
 Description     : 获取激活EPS承载数
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

  History        :
  1.lihong00150010      2011-12-05      Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ERABM_GetActiveEpsBearerNum( VOS_VOID )
{
    VOS_UINT32                 ulEpsbId     = NAS_ERABM_MIN_EPSB_ID;
    VOS_UINT32                 ulActiveNum  = NAS_ERABM_NULL;

    for ( ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId <= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++ )
    {
        if ( NAS_ERABM_EPSB_INACTIVE == NAS_ERABM_GetEpsbStateInfo(ulEpsbId))
        {
            continue;
        }
        else
        {
            ulActiveNum++;
        }
    }

    return ulActiveNum;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_SndOmErabmTimerStatus
 功能描述  : 发送消息给OM模块，ERABM定时器运行完成
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年12月6日
   作    者   : niuxiufan 00181501
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_ERABM_SndOmErabmTimerStatus(
    NAS_ERABM_TIMER_RUN_STA_ENUM_UINT32        enTimerStatus,
    NAS_ERABM_TIMER_NAME_ENUM_UINT8           enTimerId,
    VOS_UINT32                              ulTimerRemainLen
)
{
    NAS_ERABM_TIMER_INFO_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_ERABM_TIMER_INFO_STRU*)NAS_ERABM_MEM_ALLOC(sizeof(NAS_ERABM_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndOmErabmTimerStatus: mem alloc fail!.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_RABM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_RABM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_ERABM_TIMER_INFO_STRU) - 20;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId + PS_MSG_ID_ERABM_TO_ERABM_OM_BASE;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->enTimerId                   = enTimerId;

    pstMsg->ulTimerRemainLen            = ulTimerRemainLen;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_ERABM_MEM_FREE(pstMsg);

}
/*****************************************************************************
 函 数 名  : NAS_REABM_RcvRabmRrmStatusInd
 功能描述  : 收到RRM有RF资源通知处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月09日
   作    者   : leixiantiao 00258641
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_REABM_RcvRabmRrmStatusInd()
{
    /* 在NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER运行期间尝试RB重建 */
    if(NAS_ERABM_TIMER_STATE_RUNNING == NAS_ERABM_IsTimerRunning(NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER))
    {
        /* NAS_ERABM_WAIT_RB_REEST_TIMER定时器未运行 */
        if (NAS_ERABM_TIMER_STATE_STOPED == NAS_ERABM_IsTimerRunning(NAS_ERABM_WAIT_RB_REEST_TIMER))
        {
            NAS_ERABM_TimerStart(   NAS_ERABM_WAIT_RB_REEST_LENGTH,
                                    NAS_ERABM_WAIT_RB_REEST_TIMER,
                                    VOS_FALSE);
            NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_INIT);
            NAS_ERABM_SndRabmEmmReestReq(VOS_FALSE);
        }
    }
    return;
}
/*****************************************************************************
 函 数 名  : NAS_ERABM_RrmMsgDistr
 功能描述  : RRM消息处理入口
 输入参数  : 消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月09日
   作    者   : leixiantiao 00258641
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_ERABM_RrmMsgDistr(VOS_VOID *pRcvMsg)
{
    PS_MSG_HEADER_STRU            *pRrcMsg;

    pRrcMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;
    switch(pRrcMsg->ulMsgName)
    {
        /* ID_RRM_PS_STATUS_IND消息处理 */
        case ID_RRM_PS_STATUS_IND:
            NAS_REABM_RcvRabmRrmStatusInd();
            break;
        default:
            break;
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_SecuMemCpy
 Description     : 安全memcpy
 Input           : VOS_VOID* pDst, VOS_UINT32 ulMaxBuffer, const VOS_VOID* pSrc,
                   VOS_UINT32  ulLength, VOS_UINT32 ulLineNO, VOS_UINT32 ulFileID
 Output          : None
 Return          : VOS_INT32

 History         :
    1.z00297373    2015-12-28  Draft Enact
*****************************************************************************/
VOS_INT32 NAS_ERABM_SecuMemCpy
(
    VOS_VOID            * pDst,
    VOS_UINT32          ulMaxBuffer,
    const VOS_VOID      * pSrc,
    VOS_UINT32          ulLength,
    VOS_UINT32          ulLineNO,
    VOS_UINT32          ulFileID
)
{
    /*如果源地址和目的地址重叠，需改用TLPS_MEM_MOVE_S，否则安全拷贝失败 */
    if(((pSrc > pDst) && ((VOS_UINT8 *)pSrc <= ((VOS_UINT8 *)pDst + ulMaxBuffer)))
        ||((pDst> pSrc) && ((VOS_UINT8 *)pDst <= ((VOS_UINT8 *)pSrc + ulLength)))
        || (pSrc == pDst))
    {
        return TLPS_MEM_MOVE_S((pDst), (ulMaxBuffer), (pSrc), (ulLength), (ulLineNO), (ulFileID));
    }
    else
    {
        return TLPS_MEM_CPY_S((pDst), (ulMaxBuffer), (pSrc), (ulLength), (ulLineNO), (ulFileID));
    }
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 Function Name   : NAS_ERABM_InitEhrpdIdInfo
 Description     : 初始化RABM的EHRPD承载管理实体中指定承载ID的上下文信息
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History        :
    1.sunjitan 00193151      2016-01-14  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ERABM_InitEhrpdIdInfo(VOS_UINT32    ulEhrpdBearerId)
{
    NAS_ERABM_INFO_STRU                *pstEhrpdBearerInfo;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_InitEhrpdIdInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_InitEhrpdIdInfo_ENUM, LNAS_ENTRY);

    /* 防止数组越界，承载ID非法时不做初始化，不处理 */
    if ((NAS_ERABM_MAX_EPSB_ID < ulEhrpdBearerId)
      ||(NAS_ERABM_MIN_EPSB_ID > ulEhrpdBearerId))
    {
        return;
    }

    pstEhrpdBearerInfo = NAS_ERABM_GetEhrpdBearerIdInfoAddr(ulEhrpdBearerId);

    NAS_ERABM_MEM_SET_S(pstEhrpdBearerInfo, sizeof(NAS_ERABM_INFO_STRU), 0, sizeof(NAS_ERABM_INFO_STRU));

    pstEhrpdBearerInfo->ulEpsbId          = ulEhrpdBearerId;
    pstEhrpdBearerInfo->ulRbId            = NAS_ERABM_ILL_RB_ID;
    pstEhrpdBearerInfo->enContextState    = NAS_ERABM_EPSB_INACTIVE;
    pstEhrpdBearerInfo->enRbState         = NAS_ERABM_RB_DISCONNECTED;
    pstEhrpdBearerInfo->enBearerCntxtType = ESM_ERABM_BEARER_TYPE_DEFAULT;

    /* 初始化缓存数据包个数为0 */
    NAS_ERABM_GetEhrpdBearerStorePktNum(ulEhrpdBearerId) = 0;

    return;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_InitEhrpdEntity
 Description     : 初始化RABM的EHRPD承载管理实体
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History        :
    1.sunjitan 00193151      2015-12-30  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ERABM_InitEhrpdEntity(VOS_VOID)
{
    VOS_UINT32                          ulEhrpdBearerId;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_InitEhrpdEntity is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_InitEhrpdEntity_ENUM, LNAS_ENTRY);

    NAS_ERABM_MEM_SET_S(&g_stNasERabmEhrpdEntity,
                         sizeof(NAS_ERABM_EHRPD_ENTITY_STRU),
                         0,
                         sizeof(NAS_ERABM_EHRPD_ENTITY_STRU));

    /* 初始化EHRPD实体信息 */
    for (ulEhrpdBearerId = NAS_ERABM_MIN_EPSB_ID; ulEhrpdBearerId <= NAS_ERABM_MAX_EPSB_ID; ulEhrpdBearerId++)
    {
        NAS_ERABM_InitEhrpdIdInfo(ulEhrpdBearerId);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_GetActiveEhrpdBearerNum
 Description     : 获取激活的EHRPD承载数
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History        :
    1.sunjitan 00193151      2015-12-30  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ERABM_GetActiveEhrpdBearerNum(VOS_VOID)
{
    VOS_UINT32                 ulEpsbId     = NAS_ERABM_MIN_EPSB_ID;
    VOS_UINT32                 ulActiveNum  = NAS_ERABM_NULL;

    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId <= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        if (NAS_ERABM_EPSB_INACTIVE == NAS_ERABM_GetEhrpdBearerStateInfo(ulEpsbId))
        {
            continue;
        }
        else
        {
            ulActiveNum++;
        }
    }

    /* 打印激活的承载数 */
    NAS_ERABM_LOG1("NAS_ERABM_GetActiveEhrpdBearerNum is:", ulActiveNum);
    TLPS_PRINT2LAYER_INFO1(NAS_ERABM_GetActiveEhrpdBearerNum_ENUM, LNAS_ERABM_EhrpdBearerIdStateActiveNum, ulActiveNum);

    return ulActiveNum;
}

#endif


/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


