/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasTcEmmMsgProc.c
    Description : 处理EMM发给TC的消息
    History     :
     1.李洪 00150010       2009-10-13  Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasETcEmmMsgProc.h"
#include    "NasETcPdcpMsgProc.h"
#include    "NasETcNwMsgDecode.h"
#include    "NasETcMain.h"

#include    "NasETcMtcMsgProc.h"

#if ( FEATURE_LPP == FEATURE_ON )
#include    "EtcLppInterface.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASTCEMMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASTCEMMMSGPROC_C
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
 Function Name  : NAS_ETC_EmmMsgDistr()
 Description    : TC模块EMM消息处理函数
 Input          : pRcvMsg-----------收到的消息
 Output         : None
 Return Value   : VOS_VOID

 History        :
      1.李洪00150010         2009-10-13  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_ETC_EmmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg  = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ETC_INFO_LOG("NAS_ETC_EmmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_EmmMsgDistr_ENUM, LNAS_ENTRY);

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息名，调用相应的消息处理函数*/
    switch (pEmmMsg->ulMsgName)
    {
        /*如果收到的是ID_EMM_ETC_DATA_IND消息*/
        case ID_EMM_ETC_DATA_IND:
            if (NAS_ETC_L_MODE_STATUS_NORMAL != NAS_ETC_GetLModeStatus())
            {
                NAS_ETC_WARN_LOG("NAS_ETC_EmmMsgDistr:Tc is already suspended!");
                TLPS_PRINT2LAYER_WARNING(NAS_ETC_EmmMsgDistr_ENUM, LNAS_TC_Tcsuspended);
                return ;
            }

            /*调用TC_RcvTcEmmDataInd函数*/
            NAS_ETC_RcvTcEmmDataInd( (EMM_ETC_DATA_IND_STRU *) pRcvMsg );
            break;

        /*如果收到的是ID_EMM_ETC_REL_IND消息*/
        case ID_EMM_ETC_REL_IND:
            if (NAS_ETC_MODE_TYPE_LB == NAS_ETC_GetModeType())
            {
                /* 通知PDCP退出环回模式 */
                NAS_ETC_SndTcPdcpDeactTestModeMsg();

                /* 收到PDCP的去激活回复之后，会自动给CDS发送去激活请求，不需要在此处发送 */
            }
            break;

        default:
            NAS_ETC_WARN_LOG("NAS_ETC_EmmMsgDistr:WARNING:EMM->TC Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ETC_EmmMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }
}

#if ( FEATURE_LPP == FEATURE_ON )
/*****************************************************************************
 Function Name   : NAS_ETC_SndTcResetUePositionInfoMsg
 Description     : TC模块向LPP模块发送RESET POSITION
 Input           : pstTcNwMsgIE--------译码后的空口消息
 Output          : None
 Return          : VOS_VOID


 History         :
    1.lifuxin 00253982      2015-9-1  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcResetUePositionInfoMsg
(
    const NAS_ETC_NW_MSG_STRU           *pstTcNwMsgIE
)
{
    ETC_LPP_RESET_POSTION_INFO_STRU       *pstTcLppRestPostion = VOS_NULL_PTR;
    TLPS_PRINT2LAYER_WARNING(NAS_ETC_SndTcResetUePositionInfoMsg_ENUM, LNAS_LPP_Func_Enter);

    /* 分配空间并检验分配是否成功 */
    pstTcLppRestPostion = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(ETC_LPP_RESET_POSTION_INFO_STRU));

    /* 检测是否分配成功 */
    if (VOS_NULL_PTR == pstTcLppRestPostion)
    {
        /* 打印异常信息 */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcResetUePositionInfoMsg:ERROR:TC->LPP,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_SndTcResetUePositionInfoMsg_ENUM, LNAS_LPP_MallocMemFail);
        return ;
    }

    /* 填写消息头 */
    NAS_ETC_WRITE_LPP_MSG_HEAD(pstTcLppRestPostion,ID_ETC_LPP_RESET_POSTION_INFO_IND);

    /*填写消息内容*/
    pstTcLppRestPostion->enRestType = pstTcNwMsgIE->ucUePositionTech;

    /* 调用消息发送函数 */
    NAS_ETC_SND_MSG(pstTcLppRestPostion);
}
#endif

/*****************************************************************************
 Function Name   : NAS_ETC_NwMsgProcess
 Description     : 处理空口消息
 Input           : pstTcNwMsgIE-------译码后的空口消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_NwMsgProcess
(
    const NAS_ETC_NW_MSG_STRU           *pstTcNwMsgIE
)
{
    switch(pstTcNwMsgIE->enTcCnMsgType)
    {
        case NAS_ETC_CNMSG_TYPE_ACT_TEST_MODE:
            NAS_ETC_NORM_LOG("NAS_ETC_NwMsgProcess:Receive Msg Type is NAS_ETC_CNMSG_TYPE_ACT_TEST_MODE!");
            TLPS_PRINT2LAYER_INFO(NAS_ETC_NwMsgProcess_ENUM, LNAS_FUNCTION_LABEL1);
            NAS_ETC_SndTcPdcpActTestModeMsg(pstTcNwMsgIE);

            NAS_ETC_SndTcMtcStatusInfoMsg(MTC_NAS_TC_START);
            break;

        case NAS_ETC_CNMSG_TYPE_DEACT_TEST_MODE:
            NAS_ETC_NORM_LOG("NAS_ETC_NwMsgProcess:Receive Msg Type is NAS_ETC_CNMSG_TYPE_DEACT_TEST_MODE!");
            TLPS_PRINT2LAYER_INFO(NAS_ETC_NwMsgProcess_ENUM, LNAS_FUNCTION_LABEL2);
            NAS_ETC_SndTcPdcpDeactTestModeMsg();

            NAS_ETC_SndTcMtcStatusInfoMsg(MTC_NAS_TC_STOP);
            break;

        case NAS_ETC_CNMSG_TYPE_CLOSE_UE_TEST_LOOP:
            NAS_ETC_NORM_LOG("NAS_ETC_NwMsgProcess:Receive Msg Type is NAS_ETC_CNMSG_TYPE_CLOSE_UE_TEST_LOOP!");
            TLPS_PRINT2LAYER_INFO(NAS_ETC_NwMsgProcess_ENUM, LNAS_FUNCTION_LABEL3);
            NAS_ETC_SndTcPdcpStartTestLoopMsg(pstTcNwMsgIE);
            NAS_ETC_SndTcCdsStartTestLoopMsg(pstTcNwMsgIE);
            break;

        case NAS_ETC_CNMSG_TYPE_OPEN_UE_TEST_LOOP:
            NAS_ETC_NORM_LOG("NAS_ETC_NwMsgProcess:Receive Msg Type is NAS_ETC_CNMSG_TYPE_OPEN_UE_TEST_LOOP!");
            TLPS_PRINT2LAYER_INFO(NAS_ETC_NwMsgProcess_ENUM, LNAS_FUNCTION_LABEL4);
            NAS_ETC_SndTcPdcpStopTestLoopMsg(pstTcNwMsgIE);
            NAS_ETC_SndTcCdsStopTestLoopMsg();
            break;

        #if ( FEATURE_LPP == FEATURE_ON )
        case NAS_ETC_CNMSG_TYPE_RESET_UE_POSITION_INFO:
            NAS_ETC_NORM_LOG("NAS_ETC_NwMsgProcess:Receive Msg Type is NAS_ETC_CNMSG_TYPE_RESET_UE_POSITION_INFO!");
            NAS_ETC_SndTcResetUePositionInfoMsg(pstTcNwMsgIE);
            break;
        #endif

        default:
            NAS_ETC_WARN_LOG("NAS_ETC_NwMsgProcess:WARNNING: Illegal Msg Type!");
            TLPS_PRINT2LAYER_WARNING(NAS_ETC_NwMsgProcess_ENUM, LNAS_MSG_INVALID);
            break;
    }
}


/*****************************************************************************
 Function Name  : NAS_ETC_RcvTcEmmDataInd()
 Description    : TC模块收到ID_EMM_ETC_DATA_IND处理函数
 Input          : EMM_ETC_DATA_IND_STRU *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2008-10-13  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ETC_RcvTcEmmDataInd( EMM_ETC_DATA_IND_STRU *pRcvMsg )
{
    NAS_ETC_CAUSE_ENUM_UINT8             enTcCause           = NAS_ETC_CAUSE_SUCCESS;
    VOS_UINT32                          ulRcvNwMsgLen       = NAS_ETC_NULL;
    NAS_ETC_NW_MSG_STRU                  stTcNwMsgIE;
    VOS_UINT8                          *pucTmpTcMsg         = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ETC_INFO_LOG("NAS_ETC_RcvTcEmmDataInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_RcvTcEmmDataInd_ENUM, LNAS_ENTRY);

    /*取出此消息中所包含SM消息的长度*/
    ulRcvNwMsgLen = pRcvMsg->stTcMsg.ulTcMsgSize;

    /*取得SM消息首地址*/
    pucTmpTcMsg = pRcvMsg->stTcMsg.aucTcMsg;

    /*清空NAS_ESM_NW_MSG_STRU*/
    NAS_ETC_MEM_SET_S((VOS_VOID*)&stTcNwMsgIE,sizeof(NAS_ETC_NW_MSG_STRU), 0, sizeof(NAS_ETC_NW_MSG_STRU));

    /*调用空口消息解析函数, 如果解析失败直接返回*/
    enTcCause = NAS_ETC_DecodeNwMsg( pucTmpTcMsg,
                                   &ulRcvNwMsgLen,
                                   &stTcNwMsgIE );

    /*如果解析错误，打印译码错误*/
    if (NAS_ETC_CAUSE_SUCCESS != enTcCause)
    {
        /*打印异常信息*/
        NAS_ETC_WARN_LOG("NAS_ETC_RcvTcEmmDataInd:WARNING: Decode Nw Msg Error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_RcvTcEmmDataInd_ENUM, LNAS_TC_NwMsgError);
    }
    else
    {
        /*处理此条空口消息*/
        NAS_ETC_NwMsgProcess(&stTcNwMsgIE);
    }
}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcEmmDataReqMsg
 Description     : 向EMM模块发送DATA REQ消息
 Input           : None
 Output          : pSendMsg-----------发送消息存储区
                   pulLength----------发送消息长度
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcEmmDataReqMsg
(
    const VOS_UINT8                    *pucSendMsg,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulTmpLength         = NAS_ETC_NULL;
    EMM_ETC_DATA_REQ_STRU               *pTcEmmDataReq       = VOS_NULL_PTR;

    /*根据空口消息的长度分配空间*/
    if (NAS_ETC_NULL == ulLength)
    {
        NAS_ETC_WARN_LOG("NAS_ETC_SndTcEmmDataReqMsg: WARNING: Msg Length is zero");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_SndTcEmmDataReqMsg_ENUM, LNAS_EMM_MSG_LENGTH_ERROR);
        return ;
    }
    else if (ulLength > TC_MIN_SND_MSG_LEN)
    {
        ulTmpLength = ulLength - TC_MIN_SND_MSG_LEN ;
        pTcEmmDataReq = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(EMM_ETC_DATA_REQ_STRU) + ulTmpLength);
    }
    else
    {
        pTcEmmDataReq = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(EMM_ETC_DATA_REQ_STRU));
    }

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pTcEmmDataReq)
    {
        /*打印异常信息*/
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcEmmDataReqMsg:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    NAS_ETC_MEM_SET_S( NAS_ETC_GET_MSG_ENTITY(pTcEmmDataReq),NAS_ETC_GET_MSG_LENGTH(pTcEmmDataReq), 0, NAS_ETC_GET_MSG_LENGTH(pTcEmmDataReq));

    /*填写空口消息头长度*/
    pTcEmmDataReq->stTcMsg.ulTcMsgSize = ulLength;

    /*将空口消息存放到EMM_ESM_DATA_REQ_STRU结构中*/
    /*lint -e669*/
    NAS_ETC_MEM_CPY_S(pTcEmmDataReq->stTcMsg.aucTcMsg, ulLength, pucSendMsg, ulLength);
    /*lint +e669*/

    /*填写消息头*/
    NAS_ETC_WRITE_EMM_MSG_HEAD(pTcEmmDataReq,ID_EMM_ETC_DATA_REQ);

    /*调用消息发送函数 */
    NAS_ETC_SND_MSG(pTcEmmDataReq);

    NAS_ETC_NORM_LOG("NAS_ETC_SndTcEmmDataReqMsg:NORM:Send ID_EMM_ETC_DATA_REQ!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcEmmDataReqMsg_ENUM, LNAS_FUNCTION_LABEL1);
}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasTcEmmMsgProc.c */
