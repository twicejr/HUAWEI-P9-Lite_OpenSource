/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasTcPdcpMsgProc.c
  Description     : TC模块处理PDCP消息
  History         :
     1.李洪 00150010       2009-10-13   Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasETcPdcpMsgProc.h"
#include  "NasETcNwMsgEncode.h"
#include  "NasETcEmmMsgProc.h"
#include  "NasETcERabmMsgProc.h"
#include  "NasETcOmMsgProc.h"
#include  "NasERabmAppMsgProc.h"
#include  "NasETcMain.h"
#include  "CdsEtcInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASTCPDCPMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASTCPDCPMSGPROC_C
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

/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_ETC_PdcpUlMsgDistr
 Description     : PDCP UL的消息处理函数
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-14  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ETC_PdcpUlMsgDistr
(
    VOS_VOID                           *pRcvMsg
)
{
    PS_MSG_HEADER_STRU         *pPdcpUlMsg  = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ETC_INFO_LOG("NAS_ETC_PdcpUlMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_PdcpUlMsgDistr_ENUM, LNAS_ENTRY);

    /* 在ETC收到EMM消息处，已经做了判断，如果当前L是挂起状态，正常情况下不会收到除去
    ID_LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF以外的几条消息；L模挂起，环回状态激活，收到关机消息时，
    会给PDCP发送ID_LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF，用于通知PDCP去激活环回状态*/


    pPdcpUlMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息名，调用相应的消息处理函数*/
    switch (pPdcpUlMsg->ulMsgName)
    {
        /*如果收到的是ID_TC_PDCP_ACTIVATE_TEST_MODE_CNF消息*/
        case ID_LTC_LPDCP_ACTIVATE_TEST_MODE_CNF:

            NAS_ETC_RcvTcPdcpUlActTestModeCnf( (LTC_LPDCP_ACTIVATE_TEST_MODE_CNF_STRU *) pRcvMsg );
            break;

        /*如果收到的是ID_TC_PDCP_START_TEST_LOOP_CNF消息*/
        case ID_LTC_LPDCP_START_TEST_LOOP_CNF:

            NAS_ETC_RcvTcPdcpUlStartTestLoopCnf( (LTC_LPDCP_START_TEST_LOOP_CNF_STRU *) pRcvMsg );
            break;

        /*如果收到的是ID_TC_PDCP_STOP_TEST_LOOP_CNF消息*/
        case ID_LTC_LPDCP_STOP_TEST_LOOP_CNF:

            NAS_ETC_RcvTcPdcpUlStopTestLoopCnf( (LTC_LPDCP_STOP_TEST_LOOP_CNF_STRU *) pRcvMsg );
            break;

        /*如果收到的是ID_TC_PDCP_DEACTIVATE_TEST_MODE_CNF消息*/
        case ID_LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF:

            NAS_ETC_RcvTcPdcpUlDeactTestModeCnf( (LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF_STRU *) pRcvMsg );
            break;

        default:
            NAS_ETC_WARN_LOG("NAS_ETC_PdcpUlMsgDistr:WARNING:PDCP->TC Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ETC_PdcpUlMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ETC_RcvTcPdcpUlActTestModeCnf
 Description     : PDCP UL模块发来的ACTIVATE TEST MODE CNF消息处理函数
 Input           : pRcvMsg-----------收到的ACTIVATE TEST MODE CNF消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_RcvTcPdcpUlActTestModeCnf
(
    const LTC_LPDCP_ACTIVATE_TEST_MODE_CNF_STRU *pRcvMsg
)
{
    VOS_UINT32                          ulMsgLength;
    VOS_UINT8                           aucMsgBuff[NAS_ETC_UL_AIR_MSG_BUFFER_LEN];

    /* 若结果为失败，则直接返回 */
    if (NAS_ETC_RESULT_TYPE_SUCCESS != pRcvMsg->ulResult)
    {
        NAS_ETC_WARN_LOG("NAS_ETC_RcvTcPdcpUlActTestModeCnf:WARNING:Act test mode failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_RcvTcPdcpUlActTestModeCnf_ENUM, LNAS_TC_StartTestLoopFailed);
        return;
    }

    /* 编码形成ACTIVATE TEST MODE COMPLETE消息 */
    NAS_ETC_EncodeActTestModeComplete(aucMsgBuff, &ulMsgLength);

    /* 将ACTIVATE TEST MODE COMPLETE消息发送给EMM */
    NAS_ETC_SndTcEmmDataReqMsg(aucMsgBuff, ulMsgLength);

    /* 将模式设置为环回模式 */
    NAS_ETC_SetModeType(NAS_ETC_MODE_TYPE_LB);

    /* 通知RABM进入环回模式 */
    NAS_ETC_SndTcRabmActTestModeMsg();

    /* 通知CDS进入环回模式 */
    NAS_ETC_SndTcCdsActTestModeMsg();

    /* 空口消息上报 */
    NAS_ETC_SndAirMsgReportInd(  aucMsgBuff,ulMsgLength,
                                NAS_ETC_AIR_MSG_DIR_ENUM_UP,
                                TC_ACT_TEST_MODE_CMP);

}

/*****************************************************************************
 Function Name   : NAS_ETC_RcvTcPdcpUlStartTestLoopCnf
 Description     : PDCP UL模块发来的START TEST LOOP CNF消息处理函数
 Input           : pRcvMsg-----------收到的START TEST LOOP CNF消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_RcvTcPdcpUlStartTestLoopCnf
(
    const LTC_LPDCP_START_TEST_LOOP_CNF_STRU *pRcvMsg
)
{
    VOS_UINT32                          ulMsgLength;
    VOS_UINT8                           aucMsgBuff[NAS_ETC_UL_AIR_MSG_BUFFER_LEN];

    /* 若结果为失败，则直接返回 */
    if (NAS_ETC_RESULT_TYPE_SUCCESS != pRcvMsg->ulResult)
    {
        NAS_ETC_WARN_LOG("NAS_ETC_RcvTcPdcpUlStartTestLoopCnf:WARNING:Start test loop failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_RcvTcPdcpUlStartTestLoopCnf_ENUM, LNAS_TC_StartTestLoopFailed);
        return;
    }

    /* 编码形成CLOSE UE TEST LOOP COMPLETE消息 */
    NAS_ETC_EncodeCloseUeTestLoopComplete(aucMsgBuff, &ulMsgLength);

    /* 将CLOSE UE TEST LOOP COMPLETE消息发送给EMM */
    NAS_ETC_SndTcEmmDataReqMsg(aucMsgBuff, ulMsgLength);

    /* 空口消息上报 */
    NAS_ETC_SndAirMsgReportInd(  aucMsgBuff,ulMsgLength,
                                NAS_ETC_AIR_MSG_DIR_ENUM_UP,
                                TC_CLOSE_UE_TEST_LOOP_CMP);
}

/*****************************************************************************
 Function Name   : NAS_ETC_RcvTcPdcpUlStopTestLoopCnf
 Description     : PDCP UL模块发来的STOP TEST LOOP CNF消息处理函数
 Input           : pRcvMsg-----------收到的STOP TEST LOOP CNF消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_RcvTcPdcpUlStopTestLoopCnf
(
    const LTC_LPDCP_STOP_TEST_LOOP_CNF_STRU *pRcvMsg
)
{
    VOS_UINT32                          ulMsgLength;
    VOS_UINT8                           aucMsgBuff[NAS_ETC_UL_AIR_MSG_BUFFER_LEN];

    /* 若结果为失败，则直接返回 */
    if (NAS_ETC_RESULT_TYPE_SUCCESS != pRcvMsg->ulResult)
    {
        NAS_ETC_WARN_LOG("NAS_ETC_RcvTcPdcpUlStopTestLoopCnf:WARNING:Stop test loop failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_RcvTcPdcpUlStopTestLoopCnf_ENUM, LNAS_TC_StopTestLoopFailed);
        return;
    }

    /* 编码形成OPEN UE TEST LOOP COMPLETE消息 */
    NAS_ETC_EncodeOpenUeTestLoopComplete(aucMsgBuff, &ulMsgLength);

    /* 将OPEN UE TEST LOOP COMPLETE消息发送给EMM */
    NAS_ETC_SndTcEmmDataReqMsg(aucMsgBuff, ulMsgLength);

    /* 空口消息上报 */
    NAS_ETC_SndAirMsgReportInd(  aucMsgBuff,ulMsgLength,
                                NAS_ETC_AIR_MSG_DIR_ENUM_UP,
                                TC_OPEN_UE_TEST_LOOP_CMP);
}

/*****************************************************************************
 Function Name   : NAS_ETC_RcvTcPdcpUlDeactTestModeCnf
 Description     : PDCP UL模块发来的DEACTIVATE TEST MODE CNF消息处理函数
 Input           : pRcvMsg-----------收到的DEACTIVATE TEST MODE CNF消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_RcvTcPdcpUlDeactTestModeCnf
(
    const LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF_STRU *pRcvMsg
)
{
    VOS_UINT32                          ulMsgLength;
    VOS_UINT8                           aucMsgBuff[NAS_ETC_UL_AIR_MSG_BUFFER_LEN];

    /* 若结果为失败，则直接返回 */
    if (NAS_ETC_RESULT_TYPE_SUCCESS != pRcvMsg->ulResult)
    {
        NAS_ETC_WARN_LOG("NAS_ETC_RcvTcPdcpUlDeactTestModeCnf:WARNING:Deact test mode failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_RcvTcPdcpUlDeactTestModeCnf_ENUM, LNAS_TC_StopTestLoopFailed);
        return;
    }

    /* 将模式设置为正常模式 */
    NAS_ETC_SetModeType(NAS_ETC_MODE_TYPE_NORMAL);

    /* 通知CDS退出环回模式 */
    NAS_ETC_SndTcCdsDeactTestModeMsg();

    /* L模挂起的情况下，不需要给EMM发送COMPLETR消息，不需要上报空口消息 */
    if (NAS_ETC_L_MODE_STATUS_NORMAL == NAS_ETC_GetLModeStatus())
    {
        /* L模挂起状态，ERABM收到ETC发送的去激活环回模式消息，直接丢弃；收到关机消息后，
        ESM会给ERABM发送ID_ESM_ERABM_REL_IND消息，通知ERABM清除资源，所以在挂起状态下不需要再
        给ERABM发送去激活环回状态消息 */
        /* 通知RABM进入正常模式 */
        NAS_ETC_SndTcRabmDeactTestModeMsg();

        /* 编码形成DEACTIVATE TEST MODE COMPLETE消息 */
        NAS_ETC_EncodeDeactTestModeComplete(aucMsgBuff, &ulMsgLength);

        /* 将DEACTIVATE TEST MODE COMPLETE消息发送给EMM */
        NAS_ETC_SndTcEmmDataReqMsg(aucMsgBuff, ulMsgLength);

        /* 空口消息上报 */
        NAS_ETC_SndAirMsgReportInd(  aucMsgBuff,ulMsgLength,
                                    NAS_ETC_AIR_MSG_DIR_ENUM_UP,
                                    TC_DEACT_TEST_MODE_CMP);
    }

}


/*****************************************************************************
 Function Name   : NAS_ETC_SndTcPdcpActTestModeMsg
 Description     : TC模块向PDCP模块发送ACTIVATE TEST MODE消息
 Input           : pstTcNwMsgIE--------译码后的空口消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcPdcpActTestModeMsg
(
    const NAS_ETC_NW_MSG_STRU           *pstTcNwMsgIE
)
{
    LTC_LPDCP_ACTIVATE_TEST_MODE_STRU     *pstTcPdcpActTestMode = VOS_NULL_PTR;

    /* 分配空间并检验分配是否成功 */
    pstTcPdcpActTestMode = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(LTC_LPDCP_ACTIVATE_TEST_MODE_STRU));

    /* 检测是否分配成功 */
    if (VOS_NULL_PTR == pstTcPdcpActTestMode)
    {
        /* 打印异常信息 */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcPdcpActTestModeMsg:ERROR:TC->PDCP,Memory Alloc FAIL!");
        return ;
    }

    /* 清空 */
    NAS_ETC_MEM_SET_S( NAS_ETC_GET_TC_PDCP_MSG_ENTITY(pstTcPdcpActTestMode), NAS_ETC_GET_MSG_LENGTH(pstTcPdcpActTestMode),0,
                            NAS_ETC_GET_MSG_LENGTH(pstTcPdcpActTestMode));

    /* 填写消息头 */
    NAS_ETC_WRITE_PDCP_MSG_HEAD(pstTcPdcpActTestMode,ID_LTC_LPDCP_ACTIVATE_TEST_MODE);

    /* 填写环回模式 */
    pstTcPdcpActTestMode->enLoopBackMode = pstTcNwMsgIE->enLoopBackMode;

    /* 调用消息发送函数 */
    NAS_ETC_SND_MSG(pstTcPdcpActTestMode);

    /* 打印发送消息 */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcPdcpActTestModeMsg:NORM:Send ID_LTC_LPDCP_ACTIVATE_TEST_MODE!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcPdcpActTestModeMsg_ENUM, LNAS_TC_SndMsg);
}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcPdcpDeactTestModeMsg
 Description     : TC模块向PDCP模块发送DEACTIVATE TEST MODE消息
 Input           : pstTcNwMsgIE--------译码后的空口消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcPdcpDeactTestModeMsg( VOS_VOID )
{
    LTC_LPDCP_DEACTIVATE_TEST_MODE_STRU     *pstTcPdcpDeActTestMode = VOS_NULL_PTR;

    /* 分配空间并检验分配是否成功 */
    pstTcPdcpDeActTestMode = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(LTC_LPDCP_DEACTIVATE_TEST_MODE_STRU));

    /* 检测是否分配成功 */
    if (VOS_NULL_PTR == pstTcPdcpDeActTestMode)
    {
        /* 打印异常信息 */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcPdcpDeactTestModeMsg:ERROR:TC->PDCP,Memory Alloc FAIL!");
        return ;
    }

    /* 清空 */
    NAS_ETC_MEM_SET_S( NAS_ETC_GET_TC_PDCP_MSG_ENTITY(pstTcPdcpDeActTestMode),
                        NAS_ETC_GET_MSG_LENGTH(pstTcPdcpDeActTestMode), 
                        0,
                        NAS_ETC_GET_MSG_LENGTH(pstTcPdcpDeActTestMode));

    /* 填写消息头 */
    NAS_ETC_WRITE_PDCP_MSG_HEAD(pstTcPdcpDeActTestMode,ID_LTC_LPDCP_DEACTIVATE_TEST_MODE);

    /* 调用消息发送函数 */
    NAS_ETC_SND_MSG(pstTcPdcpDeActTestMode);

    /* 打印发送消息 */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcPdcpDeactTestModeMsg:NORM:Send ID_LTC_LPDCP_DEACTIVATE_TEST_MODE!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcPdcpDeactTestModeMsg_ENUM, LNAS_TC_SndMsg);
}
/*****************************************************************************
 Function Name   : NAS_ETC_SndTcPdcpStartTestLoopMsg
 Description     : TC模块向PDCP模块发送START TEST LOOP消息
 Input           : pstTcNwMsgIE--------译码后的空口消息
 Output          : None
 Return          : VOS_VOID


 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcPdcpStartTestLoopMsg
(
    const NAS_ETC_NW_MSG_STRU           *pstTcNwMsgIE
)
{
    LTC_LPDCP_START_TEST_LOOP_STRU       *pstTcPdcpStartTestLoop = VOS_NULL_PTR;

    /* 分配空间并检验分配是否成功 */
    pstTcPdcpStartTestLoop = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(LTC_LPDCP_START_TEST_LOOP_STRU));

    /* 检测是否分配成功 */
    if (VOS_NULL_PTR == pstTcPdcpStartTestLoop)
    {
        /* 打印异常信息 */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcPdcpStartTestLoopMsg:ERROR:TC->PDCP,Memory Alloc FAIL!");
        return ;
    }

    /* 清空 */
    NAS_ETC_MEM_SET_S( NAS_ETC_GET_TC_PDCP_MSG_ENTITY(pstTcPdcpStartTestLoop),NAS_ETC_GET_MSG_LENGTH(pstTcPdcpStartTestLoop), 0,
                            NAS_ETC_GET_MSG_LENGTH(pstTcPdcpStartTestLoop));

    /* 填写消息头 */
    NAS_ETC_WRITE_PDCP_MSG_HEAD(pstTcPdcpStartTestLoop,ID_LTC_LPDCP_START_TEST_LOOP);

    /* 填写环回模式 */
    pstTcPdcpStartTestLoop->enLoopBackMode = pstTcNwMsgIE->enLoopBackMode;

    /* 填写环回模式具体内容 */
    if (pstTcPdcpStartTestLoop->enLoopBackMode == LLOOP_BACK_MODE_A)
    {
        NAS_ETC_MEM_CPY_S( &pstTcPdcpStartTestLoop->u.stLBModeA,
                        sizeof(LLOOP_BACK_MODE_A_STRU),
                        &pstTcNwMsgIE->stLBModeA,
                        sizeof(LLOOP_BACK_MODE_A_STRU));

    }
    else
    {
        NAS_ETC_MEM_CPY_S( &pstTcPdcpStartTestLoop->u.stLBModeB,
                        sizeof(LLOOP_BACK_MODE_B_STRU),
                        &pstTcNwMsgIE->stLBModeB,
                        sizeof(LLOOP_BACK_MODE_B_STRU));
    }

    /* 调用消息发送函数 */
    NAS_ETC_SND_MSG(pstTcPdcpStartTestLoop);

    /* 打印发送消息 */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcPdcpStartTestLoopMsg:NORM:Send ID_LTC_LPDCP_START_TEST_LOOP!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcPdcpStartTestLoopMsg_ENUM, LNAS_TC_SndMsg);
}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcPdcpStopTestLoopMsg
 Description     : TC模块向PDCP模块发送STOP TEST LOOP消息
 Input           : pstTcNwMsgIE--------译码后的空口消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcPdcpStopTestLoopMsg
(
    const NAS_ETC_NW_MSG_STRU           *pstTcNwMsgIE
)
{
    LTC_LPDCP_STOP_TEST_LOOP_STRU        *pstTcPdcpStopTestLoop = VOS_NULL_PTR;

    (VOS_VOID)pstTcNwMsgIE;

    /* 分配空间并检验分配是否成功 */
    pstTcPdcpStopTestLoop = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(LTC_LPDCP_STOP_TEST_LOOP_STRU));

    /* 检测是否分配成功 */
    if (VOS_NULL_PTR == pstTcPdcpStopTestLoop)
    {
        /* 打印异常信息 */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcPdcpStopTestLoopMsg:ERROR:TC->PDCP,Memory Alloc FAIL!");
        return ;
    }

    /* 清空 */
    NAS_ETC_MEM_SET_S( NAS_ETC_GET_TC_PDCP_MSG_ENTITY(pstTcPdcpStopTestLoop),
                        NAS_ETC_GET_MSG_LENGTH(pstTcPdcpStopTestLoop),
                        0,
                        NAS_ETC_GET_MSG_LENGTH(pstTcPdcpStopTestLoop));

    /* 填写消息头 */
    NAS_ETC_WRITE_PDCP_MSG_HEAD(pstTcPdcpStopTestLoop,ID_LTC_LPDCP_STOP_TEST_LOOP);

    /* 调用消息发送函数 */
    NAS_ETC_SND_MSG(pstTcPdcpStopTestLoop);

    /* 打印发送消息 */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcPdcpStopTestLoopMsg:NORM:Send ID_LTC_LPDCP_STOP_TEST_LOOP!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcPdcpStopTestLoopMsg_ENUM, LNAS_TC_SndMsg);
}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcCdsActTestModeMsg
 Description     : 通知CDS进入环回模式
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.niuxiufan 00181501      2012-02-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcCdsActTestModeMsg(VOS_VOID)
{
    CDS_ETC_ACT_TEST_MODE_NOTIFY_STRU        *pstTcCdsActTestLoop = VOS_NULL_PTR;


    /* 分配空间并检验分配是否成功 */
    pstTcCdsActTestLoop = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(CDS_ETC_ACT_TEST_MODE_NOTIFY_STRU));

    /* 检测是否分配成功 */
    if (VOS_NULL_PTR == pstTcCdsActTestLoop)
    {
        /* 打印异常信息 */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcCdsActTestModeMsg:ERROR:TC->CDS,Memory Alloc FAIL!");
        return ;
    }

    /* 填写消息头 */
    NAS_ETC_WRITE_CDS_MSG_HEAD(pstTcCdsActTestLoop,ID_ETC_CDS_ACT_TEST_MODE_NOTIFY);

    /* 调用消息发送函数 */
    NAS_ETC_SND_MSG(pstTcCdsActTestLoop);

    /* 打印发送消息 */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcCdsActTestModeMsg:NORM:Send ID_ETC_CDS_ACT_TEST_MODE_NOTIFY!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcCdsActTestModeMsg_ENUM, LNAS_TC_SndMsg);

}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcCdsDeactTestModeMsg
 Description     : 通知CDS退出环回模式
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.niuxiufan 00181501      2012-02-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcCdsDeactTestModeMsg(VOS_VOID)
{
    ETC_CDS_DEACT_TEST_MODE_NOTIFY_STRU        *pstTcCdsDeactTestLoop = VOS_NULL_PTR;


    /* 分配空间并检验分配是否成功 */
    pstTcCdsDeactTestLoop = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(ETC_CDS_DEACT_TEST_MODE_NOTIFY_STRU));

    /* 检测是否分配成功 */
    if (VOS_NULL_PTR == pstTcCdsDeactTestLoop)
    {
        /* 打印异常信息 */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcCdsDeactTestModeMsg:ERROR:TC->CDS,Memory Alloc FAIL!");
        return ;
    }

    /* 填写消息头 */
    NAS_ETC_WRITE_CDS_MSG_HEAD(pstTcCdsDeactTestLoop,ID_ETC_CDS_DEACT_TEST_MODE_NOTIFY);

    /* 调用消息发送函数 */
    NAS_ETC_SND_MSG(pstTcCdsDeactTestLoop);

    /* 打印发送消息 */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcCdsDeactTestModeMsg:NORM:Send ID_ETC_CDS_DEACT_TEST_MODE_NOTIFY!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcCdsDeactTestModeMsg_ENUM, LNAS_TC_SndMsg);

}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcCdsStartTestLoopMsg
 Description     : TC模块向CDS模块发送START TEST LOOP消息
 Input           : pstTcNwMsgIE--------译码后的空口消息
 Output          : None
 Return          : VOS_VOID


 History         :
    1.y00151394      2012-09-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcCdsStartTestLoopMsg
(
    const NAS_ETC_NW_MSG_STRU           *pstTcNwMsgIE
)
{
    ETC_CDS_START_TEST_LOOP_NOTIFY_STRU *pstStartNfyMsg;

    /* 分配空间并检验分配是否成功 */
    pstStartNfyMsg = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(ETC_CDS_START_TEST_LOOP_NOTIFY_STRU));

    /* 检测是否分配成功 */
    if (VOS_NULL_PTR == pstStartNfyMsg)
    {
        /* 打印异常信息 */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcCdsStartTestLoopMsg:ERROR:TC->CDS,Memory Alloc FAIL!");
        return ;
    }

    /* 填写消息头 */
    NAS_ETC_WRITE_CDS_MSG_HEAD(pstStartNfyMsg,ID_ETC_CDS_START_TEST_LOOP_NOTIFY);

    /* 填写环回模式 */
    if (LLOOP_BACK_MODE_B == pstTcNwMsgIE->enLoopBackMode)
    {
        pstStartNfyMsg->ulLBMode = CDS_ETC_LB_MODE_B;
        pstStartNfyMsg->ulLBModeBTmrLen = pstTcNwMsgIE->stLBModeB.ulDelayTime;
    }
    else
    {
        pstStartNfyMsg->ulLBMode = LLOOP_BACK_MODE_A;
        pstStartNfyMsg->ulLBModeBTmrLen = 0;
    }

    /* 调用消息发送函数 */
    NAS_ETC_SND_MSG(pstStartNfyMsg);

    /* 打印发送消息 */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcCdsStartTestLoopMsg:NORM:Send ID_ETC_CDS_START_TEST_LOOP_NOTIFY!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcCdsStartTestLoopMsg_ENUM, LNAS_TC_SndMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcCdsStopTestLoopMsg
 Description     : TC模块向CDS模块发送STOP TEST LOOP消息
 Input           : pstTcNwMsgIE--------译码后的空口消息
 Output          : None
 Return          : VOS_VOID


 History         :
    1.y00151394      2012-09-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcCdsStopTestLoopMsg(VOS_VOID)
{
    ETC_CDS_STOP_TEST_LOOP_NOTIFY_STRU *pstStopNfyMsg;

    /* 分配空间并检验分配是否成功 */
    pstStopNfyMsg = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(ETC_CDS_STOP_TEST_LOOP_NOTIFY_STRU));

    /* 检测是否分配成功 */
    if (VOS_NULL_PTR == pstStopNfyMsg)
    {
        /* 打印异常信息 */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcCdsStopTestLoopMsg:ERROR:TC->CDS,Memory Alloc FAIL!");
        return ;
    }

    /* 填写消息头 */
    NAS_ETC_WRITE_CDS_MSG_HEAD(pstStopNfyMsg,ID_ETC_CDS_STOP_TEST_LOOP_NOTIFY);

    /* 调用消息发送函数 */
    NAS_ETC_SND_MSG(pstStopNfyMsg);

    /* 打印发送消息 */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcCdsStopTestLoopMsg:NORM:Send ID_ETC_CDS_STOP_TEST_LOOP_NOTIFY!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcCdsStopTestLoopMsg_ENUM, LNAS_TC_SndMsg);

    return;
}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasTcPdcpMsgProc.c */

