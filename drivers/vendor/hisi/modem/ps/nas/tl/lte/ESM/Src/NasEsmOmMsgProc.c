/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEsmOmMsgProc.c
  Description     :
  History         :
     1.sunbing       2008-12-30   Draft Enact
     2.杨茜惠 00135146    2009-03-06  Modify  BA8D01127

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasEsmInclude.h"
#include  "msp_diag.h"

#include  "SysNvId.h"
#include  "omnvinterface.h"

#include "TlPsDrv.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMOMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMOMMSGPROC_C
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

VOS_UINT32                  g_NasEsmOmInfoIndFlag = 0;

ESM_FTM_INFO_MANAGE_STRU             g_astEsmFtmInfoManage;
ESM_DATABASE_INFO_STRU               g_astEsmInfo;

VOS_UINT32               g_ulRptPdpStatus = APP_ESM_DT_REPORT_STATUS_CLOSE;
VOS_UINT32               g_ulNasEsmOmMsgHookFlag = 0;
APP_ESM_DT_STRU          g_stEsmDtInfo;

/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_ESM_TransparentMsgProc
 Description     : 透明传输命令处理函数
 Input           : VOS_VOID* pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2008-12-30  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_TransparentMsgProc( VOS_VOID* pRcvMsg )
{
    NAS_ESM_TRANSPARENT_CMD_REQ_STRU  *pAppMsg = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_TransparentMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_TransparentMsgProc_ENUM, LNAS_ENTRY);

    pAppMsg = (NAS_ESM_TRANSPARENT_CMD_REQ_STRU*)pRcvMsg;

    switch(pAppMsg->enEsmTpCmdType)
    {
        case NAS_ESM_TP_CMD_TYPE_TEST:

            break;

        default:
            NAS_ESM_WARN_LOG("NAS_ESM_TransparentMsgProc:NORM: Transparent Cmd not support!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_TransparentMsgProc_ENUM, 1);
            break;
    }

}


/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmOmTpCmdCnfMsg
 Description     : 透明命令回复
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2008-12-30  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_ESM_SndEsmOmTpCmdCnfMsg(const VOS_UINT8 *pucData,
                                                        VOS_UINT32 ulLength)
{
    PS_OM_TRANSPARENT_CMD_CNF_STRU     *pPsOmTpCmdCnf       = VOS_NULL_PTR;
    VOS_UINT16                          usOriginalId        = 0;
    VOS_UINT16                          usTerminalId        = 0;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmOmTpCmdCnfMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmOmTpCmdCnfMsg_ENUM, LNAS_ENTRY);

    /*根据空口消息的长度分配空间，处于消息头外*/
    if(ulLength > ESM_MIN_SND_MSG_LEN)
    {
        pPsOmTpCmdCnf = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(PS_OM_TRANSPARENT_CMD_CNF_STRU) + (ulLength - ESM_MIN_SND_MSG_LEN));
    }
    else/*如果长度小于ESM_MIN_SND_MSG_LEN，分配的空间等于ESM_MIN_SND_MSG_LEN*/
    {
        pPsOmTpCmdCnf = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(PS_OM_TRANSPARENT_CMD_CNF_STRU));
    }

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pPsOmTpCmdCnf)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmOmTpCmdCnfMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmOmTpCmdCnfMsg_ENUM, 1);
        return ;
    }


    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pPsOmTpCmdCnf),
                        NAS_ESM_GET_MSG_LENGTH(pPsOmTpCmdCnf),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pPsOmTpCmdCnf));

    /*将空口消息存放到EMM_ESM_DATA_REQ_STRU结构中*/
    /*lint -e669*/
    NAS_ESM_MEM_CPY_S(pPsOmTpCmdCnf->aucTransCmdCnf, ulLength, pucData, ulLength);
    /*lint +e669*/

    /*分配本次过程APP_MSG_HEADER*/
    NAS_ESM_AssignMidHeader(&usOriginalId,&usTerminalId);

    /*填写消息头*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pPsOmTpCmdCnf,OM_PS_TRANSPARENT_CMD_CNF,\
                              usOriginalId,usTerminalId,0);

    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pPsOmTpCmdCnf);

}


/*****************************************************************************
 Function Name   : NAS_ESM_SndAirMsgReportInd
 Description     : 发送空口消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2008-12-30  Draft Enact
    2.  z00138739        2009-5-22  Modify, BJ9D00871

*****************************************************************************/
VOS_VOID NAS_ESM_SndAirMsgReportInd
(
    const VOS_UINT8                    *pucData,
    VOS_UINT32                          ulLength,
    NAS_ESM_AIR_MSG_DIR_ENUM_UINT8      enMsgDir,
    OM_PS_AIR_MSG_ENUM_UINT8            enMsgId
)
{
#ifndef PS_ITT_PC_TEST
    /*z00282933, 多模OM融合添加 - BEGIN*/
    DIAG_AIR_IND_STRU       stAirMsg;
    /*z00282933, 多模OM融合添加 - END*/
    VOS_UINT8                  *pucTmpData = VOS_NULL_PTR;

    /*分配空口消息空间*/
    pucTmpData = (VOS_UINT8*)
                        NAS_ESM_MEM_ALLOC(ulLength);

    if(VOS_NULL_PTR== pucTmpData)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_SndAirMsgReportInd: MEM_ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndAirMsgReportInd_ENUM, LNAS_EMM_ALLOC_FAIL);
        return;
    }


    NAS_ESM_MEM_CPY_S(pucTmpData, ulLength, pucData, ulLength);

    /*z00282933, 多模OM融合添加 - BEGIN*/
    /*设置空口消息方向*/
    if(NAS_ESM_AIR_MSG_DIR_ENUM_UP == enMsgDir)
    {
        stAirMsg.ulModule = LPS_OM_ID(PS_PID_ESM, OS_MSG_UL);
        stAirMsg.ulPid = PS_PID_ESM;
        stAirMsg.ulDirection = DIAG_SIDE_NET;
    }
    else
    {
        stAirMsg.ulModule = LPS_OM_ID(PS_PID_ESM, OS_MSG_DL);
        stAirMsg.ulPid = PS_PID_ESM;
        stAirMsg.ulDirection = DIAG_SIDE_UE;
    }
    stAirMsg.ulMsgId = (VOS_UINT32)(enMsgId+ PS_MSG_ID_AIR_BASE);
    stAirMsg.ulLength = ulLength;
    stAirMsg.pData = (void*)pucTmpData;

    /*上报空口消息*/
    if(ERR_MSP_SUCCESS != LDRV_DIAG_AIRMSGREPORT(&stAirMsg))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SndAirMsgReportInd: Send Msg Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_SndAirMsgReportInd_ENUM, LNAS_FAIL);
    }
    /*z00282933, 多模OM融合添加 - END*/

    /*释放空口消息空间*/
    NAS_ESM_MEM_FREE(pucTmpData);


#endif

    NAS_ESM_NORM_LOG("ESM->OMT: PS_OMT_AIR_MSG_REPORT_IND\r");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndAirMsgReportInd_ENUM, 1);

}

/*****************************************************************************
 Function Name  : NAS_ESM_SndKeyEventReportInd()
 Description    : 作成和发送OM_PS_KEY_EVENT_REPORT_IND消息
 Input          : VOS_UINT8 ucKeyEvent 关键事件
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
    1.sunbing49683      2008-12-30  Draft Enact
    2.  z00138739        2009-5-22  Modify, BJ9D00871

*****************************************************************************/
VOS_VOID NAS_ESM_SndKeyEventReportInd(OM_PS_KEY_EVENT_ENUM_UINT8 enKeyEvent)
{
    /*z00282933, 多模OM融合添加 - BEGIN*/
#if (VOS_WIN32 != VOS_OS_VER)
    DIAG_EVENT_IND_STRU stDiagEventInd;

#ifndef PS_ITT_PC_TEST

    NAS_ESM_MEM_SET_S(  &stDiagEventInd,
                        sizeof(DIAG_EVENT_IND_STRU),
                        0,
                        sizeof(DIAG_EVENT_IND_STRU));

    stDiagEventInd.ulModule = LPS_OM_ID(UE_MODULE_ESM_ID, DIAG_LOG_TYPE_INFO);
    stDiagEventInd.ulPid = UE_MODULE_ESM_ID;
    stDiagEventInd.ulEventId = (VOS_UINT32)(enKeyEvent+OM_PS_KEY_EVENT_BASE_ID);

    /*lint -e778*/
    /*lint -e648*/
    if(ERR_MSP_SUCCESS != LDRV_DIAG_EVENTREPORT(&stDiagEventInd))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SndKeyEventReportInd: Send Msg Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_SndKeyEventReportInd_ENUM, LNAS_FAIL);
    }
    /*lint +e648*/
    /*lint +e778*/
#endif

#endif
    /*z00282933, 多模OM融合添加 - END*/

    NAS_ESM_NORM_LOG("ESM->OMT: PS_OMT_KEY_EVT_REPORT_IND\r");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndKeyEventReportInd_ENUM, 1);
}
/*****************************************************************************
 Function Name  : NAS_ESM_OmMsgDistr
 Description    : ESM模块OM消息分发函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2013-08-06  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_OmMsgDistr
(
    VOS_VOID                           *pRcvMsg
)
{
    PS_MSG_HEADER_STRU         *pOmMsg = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_SmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_OmMsgDistr_ENUM, LNAS_ENTRY);

    pOmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息名，调用相应的消息处理函数*/
    switch(pOmMsg->ulMsgName)
    {
        /*如果收到的是ID_SM_ESM_PDP_CONTEXT_INFO_IND消息*/
        case ID_OM_ESM_INFO_REPORT_REQ:
            (VOS_VOID)LTE_MsgHook((VOS_VOID*)pRcvMsg);
            NAS_ESM_OmInfoIndMsgProc(pRcvMsg );
            break;

        case ID_APP_ESM_DT_INQ_PDP_INFO_REQ:
            NAS_ESM_AppQueryActPdpInfoMsgProc(pRcvMsg);
            break;

        #if (FEATURE_PTM == FEATURE_ON)
        case ID_OM_FTM_CTRL_IND:
            (VOS_VOID)NAS_ESM_RevOmFtmCtrlMsg((MsgBlock *)pRcvMsg);
            break;
        #endif

        default:
            /*打印异常信息*/
            NAS_ESM_WARN_LOG("NAS_ESM_OmMsgDistr:WARNING:OM->ESM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_OmMsgDistr_ENUM, 1);
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_OmInfoIndMsgProc
 Description     : 上报ESM信息的控制消息处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181     2013-06-21  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_OmInfoIndMsgProc(VOS_VOID *pRcvMsg)
{
    OM_ESM_INFO_REPORT_REQ_STRU        *pEsmOmInfoReqMsg;
    OM_ESM_INFO_REPORT_CNF_STRU        *pEsmOmInfoCnfMsg;

    NAS_ESM_NORM_LOG("NAS_ESM_OMInfoIndMsgProc: enter !!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_OmInfoIndMsgProc_ENUM, LNAS_ENTRY);

    pEsmOmInfoReqMsg = (OM_ESM_INFO_REPORT_REQ_STRU *)pRcvMsg;

    if (OM_ESM_INFO_REPORT_OPEN == pEsmOmInfoReqMsg->enRptCtrl)
    {
        g_NasEsmOmInfoIndFlag = OM_ESM_REPORT_INFO_OPEN;
    }
    else
    {
        g_NasEsmOmInfoIndFlag = OM_ESM_REPORT_INFO_CLOSE;

    }
    /* 将保存上报信息的全局变量清除 */
    NAS_ESM_MEM_SET_S(  g_stEsmOmInfo,
                        sizeof(OM_ESM_STATE_INFO_STRU)*APP_ESM_MAX_EPSB_NUM,
                        NAS_ESM_NULL,
                        sizeof(OM_ESM_STATE_INFO_STRU)*APP_ESM_MAX_EPSB_NUM);

    /* 为消息分配地址 */
    pEsmOmInfoCnfMsg = (VOS_VOID *)NAS_ESM_ALLOC_MSG(sizeof(OM_ESM_INFO_REPORT_CNF_STRU));
    if(VOS_NULL_PTR  == pEsmOmInfoCnfMsg)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppInfoIndMsgProc: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_OmInfoIndMsgProc_ENUM, LNAS_EMM_ALLOC_FAIL);
        return;
    }


    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pEsmOmInfoCnfMsg),
                        NAS_ESM_GET_MSG_LENGTH(pEsmOmInfoCnfMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pEsmOmInfoCnfMsg));


    /* 打包消息头 */
    pEsmOmInfoCnfMsg->ulMsgId       = ID_OM_ESM_INFO_REPORT_CNF;
    pEsmOmInfoCnfMsg->ulSenderCpuId = pEsmOmInfoReqMsg->ulReceiverCpuId;
    pEsmOmInfoCnfMsg->ulSenderPid     = pEsmOmInfoReqMsg->ulReceiverPid;
    pEsmOmInfoCnfMsg->ulReceiverPid   = pEsmOmInfoReqMsg->ulSenderPid;
    pEsmOmInfoCnfMsg->ulReceiverCpuId  = pEsmOmInfoReqMsg->ulSenderCpuId;
    /* OM融合，所有透传消息CNF和REQ中的usOriginalId和usTerminalId必须对应，不能颠倒 */
    pEsmOmInfoCnfMsg->usOriginalId    = pEsmOmInfoReqMsg->usOriginalId;
    pEsmOmInfoCnfMsg->usTerminalId    = pEsmOmInfoReqMsg->usTerminalId;
    pEsmOmInfoCnfMsg->ulSN            = pEsmOmInfoReqMsg->ulSN;

    /*设置OPID*/
    pEsmOmInfoCnfMsg->ulOpId      = pEsmOmInfoReqMsg->ulOpId;


    pEsmOmInfoCnfMsg->ulRslt      = APP_SUCCESS;

    /* 发送消息 */
    NAS_ESM_SND_MSG(pEsmOmInfoCnfMsg);
    return;
}
/*lint +e961*/
/*lint +e960*/


VOS_VOID NAS_ESM_OmInfoIndProc(VOS_VOID)
{
    VOS_UINT32 ulFtmRst = NAS_ESM_FAILURE;

    if(NAS_ESM_FTM_ACTION_FLAG_OPEN == NAS_ESM_GetFtmInfoActionFlag())
    {
        ulFtmRst = NAS_ESM_CompareEsmDatabaseInfo();
    }

    NAS_ESM_UpdateEsmDatabaseInfo();

    if(NAS_ESM_SUCCESS == ulFtmRst)
    {
        NAS_ESM_SendOmFtmMsg();
    }
}


VOS_VOID NAS_ESM_FtmInfoInit(VOS_VOID)
{
    NAS_ESM_INFO_LOG("NAS_ESM_FtmInfoInit.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_FtmInfoInit_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(  NAS_ESM_GetFtmInfoManageAddr(),
                        sizeof(ESM_FTM_INFO_MANAGE_STRU),
                        0,
                        sizeof(ESM_FTM_INFO_MANAGE_STRU));

    NAS_ESM_MEM_SET_S(  NAS_ESM_GetEsmInfoAddr(),
                        sizeof(ESM_DATABASE_INFO_STRU),
                        0,
                        sizeof(ESM_DATABASE_INFO_STRU));

    NAS_ESM_GetFtmInfoActionFlag() = NAS_ESM_FTM_ACTION_FLAG_CLOSE;

    return;
}

 /*****************************************************************************
  Function Name   : NAS_ESM_RevOmFtmCtrlMsg
  Description     : 收到OM工程模式控制消息
  Input           : 1.MsgBlock   *pMsgStru
  Output          : None
  Return          : VOS_UINT32

  History         :
     1. lifuxin 00253982 2013-11-01 新建

 *****************************************************************************/
VOS_UINT32   NAS_ESM_RevOmFtmCtrlMsg(MsgBlock   *pMsgStru)
{
    OM_FTM_CTRL_IND_STRU  *pstOmFtmCtrlInfo;
    NAS_ESM_INFO_LOG("NAS_ESM_RevOmFtmCtrlMsg.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RevOmFtmCtrlMsg_ENUM, LNAS_ENTRY);

    if (VOS_NULL_PTR == pMsgStru)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RevOmFtmCtrlMsg, input point is null!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RevOmFtmCtrlMsg_ENUM, LNAS_NULL_PTR);

        return NAS_ESM_MSG_DISCARD;
    }

    pstOmFtmCtrlInfo = (OM_FTM_CTRL_IND_STRU *)(VOS_VOID *)pMsgStru;

    NAS_ESM_INFO_LOG1("ESM_OM_ProcOmFtmCtrlInfo, ucActionFlag = ", pstOmFtmCtrlInfo->ucActionFlag);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_RevOmFtmCtrlMsg_ENUM, 1, pstOmFtmCtrlInfo->ucActionFlag);

    if(1 == pstOmFtmCtrlInfo->ucActionFlag)
    {
        /*设置工程模式上报功能打开*/
        NAS_ESM_SetFtmOmManageFtmActionFlag(NAS_ESM_FTM_ACTION_FLAG_OPEN);

        /*上报当前信息 */
        NAS_ESM_SendOmFtmMsg();
    }
    else
    {
        /*关闭工程模式上报，*/
        NAS_ESM_SetFtmOmManageFtmActionFlag(NAS_ESM_FTM_ACTION_FLAG_CLOSE);
    }

    return NAS_ESM_MSG_HANDLED;
}


VOS_UINT32 NAS_ESM_CompareEsmDatabaseInfo(VOS_VOID)
{
    NAS_ESM_INFO_LOG("NAS_ESM_CompareEsmDatabaseInfo.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_CompareEsmDatabaseInfo_ENUM, LNAS_ENTRY);

    if(NAS_ESM_GetFtmInfoEsmCause() != NAS_ESM_GetEsmInfoAddr()->ucEsmCause)
    {
        return NAS_ESM_SUCCESS;
    }

    return NAS_ESM_FAILURE;
}


VOS_VOID NAS_ESM_UpdateEsmDatabaseInfo(VOS_VOID)
{
    NAS_ESM_INFO_LOG("NAS_ESM_UpdateEsmDatabaseInfo.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_UpdateEsmDatabaseInfo_ENUM, LNAS_ENTRY);

    NAS_ESM_GetEsmInfoAddr()->ucEsmCause = NAS_ESM_GetFtmInfoEsmCause();
}

 /*****************************************************************************
  Function Name   : NAS_ESM_RevOmFtmCtrlMsg
  Description     : 发送状态变化消息给OM
  Input           : None
  Output          : None
  Return          : None

  History         :
     1. lifuxin 00253982 2013-11-01 新建

 *****************************************************************************/
VOS_VOID     NAS_ESM_SendOmFtmMsg(VOS_VOID)
{
    LNAS_OM_FTM_REPROT_IND_STRU *pFtmMsg;

    NAS_ESM_INFO_LOG("NAS_ESM_SendOmFtmMsg.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SendOmFtmMsg_ENUM, LNAS_ENTRY);

    /* 若工程模式关闭，则不发送 */
    if(NAS_ESM_FTM_ACTION_FLAG_OPEN != NAS_ESM_GetFtmInfoActionFlag())
    {
        NAS_ESM_INFO_LOG1("NAS_ESM_SendOmFtmMsg: ActionFlag = ", NAS_ESM_GetFtmInfoActionFlag());
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_SendOmFtmMsg_ENUM, 1, NAS_ESM_GetFtmInfoActionFlag());
        return;
    }

    /*分配空间并检验分配是否成功*/
    pFtmMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(LNAS_OM_FTM_REPROT_IND_STRU));
    if ( VOS_NULL_PTR == pFtmMsg )
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SendOmFtmMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SendOmFtmMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return ;
    }

    /*构造ID_EMM_ESM_PDN_CON_IND消息*/
    /*填充消息头*/
    NAS_ESM_COMP_OM_MSG_HEADER(         pFtmMsg,
                                        (sizeof(LNAS_OM_FTM_REPROT_IND_STRU)-
                                        NAS_ESM_LEN_VOS_MSG_HEADER));

    /*填充消息ID*/
    pFtmMsg->ulMsgName                  = ID_OM_FTM_REPROT_IND;

    /*填充消息内容*/
    pFtmMsg->ulMsgType                  = OM_ERR_LOG_MSG_FTM_REPORT;
    pFtmMsg->ulMsgSN                    = (NAS_ESM_GetFtmInfoMsgSN());
    NAS_ESM_GetFtmInfoMsgSN()++;
    pFtmMsg->ulRptlen                   = sizeof(LNAS_OM_FTM_REPROT_CONTENT_STRU);

    pFtmMsg->stLnasFtmContent.ulMsgModuleID  = OM_ERR_LOG_MOUDLE_ID_ESM;
    pFtmMsg->stLnasFtmContent.usModemId      = 0;
    pFtmMsg->stLnasFtmContent.usProjectID    = 0;
    pFtmMsg->stLnasFtmContent.ulLength       = sizeof(LNAS_ESM_FTM_INFO_STRU);
    pFtmMsg->stLnasFtmContent.u.stEsmFtmInfo.ucEsmCause = g_astEsmInfo.ucEsmCause;

    /*向OM发送消息*/
    NAS_ESM_SND_MSG( pFtmMsg);


    return;

}


/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_ESM_ReportActPdpInfo
 Description     : 主动上报动态PDP信息的消息
 Input           : VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.niuxiufan 00181501      2012-09-07  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_ReportActPdpInfo( VOS_VOID)
{
    APP_ESM_INQ_PDP_INFO_IND_STRU    *pAppIndMsg;
    NAS_OM_ACT_PDP_INFO_STRU          *pstActPdpInfo = (VOS_VOID*)NAS_ESM_MEM_ALLOC(sizeof(NAS_OM_ACT_PDP_INFO_STRU));

    if (VOS_NULL_PTR == pstActPdpInfo)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_ReportActPdpInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ReportActPdpInfo_ENUM, LNAS_EMM_ALLOC_FAIL);
        return;
    }

    if (APP_ESM_DT_REPORT_STATUS_CLOSE == g_ulRptPdpStatus)
    {
        NAS_ESM_MEM_FREE(pstActPdpInfo);
        return;
    }

    /*分配空间并检验分配是否成功*/
    pAppIndMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_PDP_INFO_IND_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pAppIndMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppReportActPdpInfo:ERROR:ESM->APP ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ReportActPdpInfo_ENUM, 1);
        NAS_ESM_MEM_FREE(pstActPdpInfo);
        return;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  pstActPdpInfo,
                        sizeof(NAS_OM_ACT_PDP_INFO_STRU),
                        0,
                        sizeof(NAS_OM_ACT_PDP_INFO_STRU));


    /*填写消息头*/
    NAS_ESM_WRITE_APP_DT_IND_MSG_HEAD(pAppIndMsg,ID_APP_ESM_DT_INQ_PDP_INFO_IND,\
                              NAS_ESM_NULL,\
                              NAS_ESM_NULL,\
                              NAS_ESM_NULL);

    pAppIndMsg->ulOpId = DIAG_CMD_EMM_APP_PDP_INFO_IND;

    /*获取激活承载的信息 */
    NAS_ESM_GetActPdpInfo(pstActPdpInfo);

    NAS_ESM_MEM_CPY_S(  &pAppIndMsg->stActPdpInfo,
                        sizeof(NAS_OM_ACT_PDP_INFO_STRU),
                        pstActPdpInfo,
                        sizeof(NAS_OM_ACT_PDP_INFO_STRU));

    NAS_ESM_MEM_CPY_S(  &g_stEsmDtInfo.stActPdpInfo,
                        sizeof(NAS_OM_ACT_PDP_INFO_STRU),
                        pstActPdpInfo,
                        sizeof(NAS_OM_ACT_PDP_INFO_STRU));

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEsmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID *)pAppIndMsg);
    }
#endif
    /*调用消息发送函数 */
    NAS_ESM_SND_MSG(pAppIndMsg);
    NAS_ESM_MEM_FREE(pstActPdpInfo);

}

/*****************************************************************************
 Function Name   : NAS_ESM_SndOmRegCidInfo
 Description     : 可维可测，向OM发送注册时选择的CID
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei 00307272    2015-08-18   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndOmRegCidInfo(VOS_UINT32  ulRegCid)
{
    NAS_ESM_OM_LOG_REG_CID_INFO_STRU             *pstRegCidInfo      = VOS_NULL_PTR;

    /* 分配空间并检验分配是否成功 */
    pstRegCidInfo  = (NAS_ESM_OM_LOG_REG_CID_INFO_STRU*)NAS_ESM_MEM_ALLOC( \
                                                  sizeof(NAS_ESM_OM_LOG_REG_CID_INFO_STRU));
    if (VOS_NULL_PTR == pstRegCidInfo)
    {
        return;
    }

    NAS_ESM_MEM_SET_S(  pstRegCidInfo,
                        sizeof(NAS_ESM_OM_LOG_REG_CID_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_OM_LOG_REG_CID_INFO_STRU));

    pstRegCidInfo->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstRegCidInfo->stMsgHeader.ulSenderPid         = PS_PID_ESM;
    pstRegCidInfo->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstRegCidInfo->stMsgHeader.ulReceiverPid       = PS_PID_ESM;
    pstRegCidInfo->stMsgHeader.ulLength            = sizeof(NAS_ESM_OM_LOG_REG_CID_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstRegCidInfo->stMsgHeader.ulMsgName           = NAS_ESM_OM_LOG_REG_CID_INFO;
    pstRegCidInfo->ulRegCid                        = ulRegCid;

    /* 消息上报HIDS */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstRegCidInfo);
    NAS_ESM_MEM_FREE(pstRegCidInfo);

    return;
}





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

