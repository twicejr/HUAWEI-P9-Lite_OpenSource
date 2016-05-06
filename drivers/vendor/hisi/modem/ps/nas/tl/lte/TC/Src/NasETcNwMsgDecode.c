/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasTcNwMsgDecode.c
    Description : EMM发给TC的网侧消息的公共处理
    History     :
     1.李洪00150010      2009-10-13  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include   "NasETcNwMsgDecode.h"
#include   "NasETcOmMsgProc.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASTCNWMSGDECODE_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASTCNWMSGDECODE_C
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
  Function Name  : NAS_ETC_DecodeNwMsg()
  Description    : TC模块解析空口消息函数
  Input          : VOS_UINT8             *pucMsg,
                      VOS_UINT32         *ulMsgLen,
                      NAS_ETC_NW_MSG_STRU *pstMsgIE
  Output         : VOS_VOID
  Return Value   : VOS_VOID

  History        :
      1.lihong00150010  2009-10-14  Draft Enact

*****************************************************************************/
NAS_ETC_CAUSE_ENUM_UINT8 NAS_ETC_DecodeNwMsg
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                         *pulMsgLen,
    NAS_ETC_NW_MSG_STRU                 *pstMsgIE
)
{
    VOS_UINT32                          ulSum               = NAS_ETC_NULL;
    NAS_ETC_CAUSE_ENUM_UINT8             enTcCause           = NAS_ETC_CAUSE_SUCCESS;
    VOS_UINT32                          ulMsgLen            = *pulMsgLen;
    VOS_UINT32                          ulMsgLenTmp         = NAS_ETC_NULL;
    VOS_UINT8                          *pucTmpMsg           = pucMsg;
    NAS_ETC_NW_MSG_STRU                 *pstTmpMsgIE         = pstMsgIE;

    /*打印进入该函数*/
    NAS_ETC_INFO_LOG("NAS_ETC_DecodeNwMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_DecodeNwMsg_ENUM, LNAS_ENTRY);

    /*入口参数检查(pucMsg)*/
    if ((VOS_NULL_PTR == pucTmpMsg) || (ulMsgLen < NAS_ETC_MSG_MIN_LEN))
    {
        NAS_ETC_WARN_LOG("NAS_ETC_DecodeNwMsg:WARNING:TC MSG is null!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_DecodeNwMsg_ENUM, LNAS_TC_TcMsgLenthError);
        return NAS_ETC_CAUSE_ERROR;
    }

    /*判断Protocol discriminator*/
    if (NAS_ETC_MSG_PD != (pucTmpMsg[ulSum] & NAS_ETC_MSG_LOW_BIT))
    {
        NAS_ETC_WARN_LOG("NAS_ETC_DecodeNwMsg:WARNING:Protocol discriminator wrong!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_DecodeNwMsg_ENUM, LNAS_EMM_PROTOCOL_ERROR);
        return NAS_ETC_CAUSE_ERROR;
    }

    /*跳过Protocol discriminator和Skip indicator*/
    ulSum++;

    /*记录Message type*/
    pstMsgIE->enTcCnMsgType = pucTmpMsg[ulSum++];

    /* 记录已译码的消息长度 */
    *pulMsgLen = ulSum;

    /* 计算剩余未译码的消息长度 */
    ulMsgLenTmp = ulMsgLen - NAS_ETC_SUM_LEN_OF_PD_MSGTYPE;

    /* 根据不同的消息进行相应的译码 */
    switch (pstMsgIE->enTcCnMsgType)
    {
        case NAS_ETC_CNMSG_TYPE_ACT_TEST_MODE:
            enTcCause = NAS_ETC_DecodeNwActTestModeMsg(  pucMsg + ulSum,
                                                        &ulMsgLenTmp,
                                                        pstTmpMsgIE);

            /* 记录已译码的消息长度 */
            *pulMsgLen = *pulMsgLen + ulMsgLenTmp;

            NAS_ETC_SndAirMsgReportInd(  pucMsg,*pulMsgLen,
                                        NAS_ETC_AIR_MSG_DIR_ENUM_DOWN,
                                        TC_ACT_TEST_MODE);
            break;

        case NAS_ETC_CNMSG_TYPE_CLOSE_UE_TEST_LOOP:
            enTcCause = NAS_ETC_DecodeNwCloseUeTestLoopMsg(  pucMsg + ulSum,
                                                            &ulMsgLenTmp,
                                                            pstTmpMsgIE);

            /* 记录已译码的消息长度 */
            *pulMsgLen = *pulMsgLen + ulMsgLenTmp;

            NAS_ETC_SndAirMsgReportInd(  pucMsg,*pulMsgLen,
                                        NAS_ETC_AIR_MSG_DIR_ENUM_DOWN,
                                        TC_CLOSE_UE_TEST_LOOP);
            break;

        case NAS_ETC_CNMSG_TYPE_OPEN_UE_TEST_LOOP:
            NAS_ETC_SndAirMsgReportInd(  pucMsg,*pulMsgLen,
                                        NAS_ETC_AIR_MSG_DIR_ENUM_DOWN,
                                        TC_OPEN_UE_TEST_LOOP);
            break;
        case NAS_ETC_CNMSG_TYPE_DEACT_TEST_MODE:
            NAS_ETC_SndAirMsgReportInd(  pucMsg,*pulMsgLen,
                                        NAS_ETC_AIR_MSG_DIR_ENUM_DOWN,
                                        TC_DEACT_TEST_MODE);
            break;

        #if ( FEATURE_LPP == FEATURE_ON )
        case NAS_ETC_CNMSG_TYPE_RESET_UE_POSITION_INFO:

            /*解出UE Positioning Technology*/
            pstMsgIE->ucUePositionTech = pucTmpMsg[ulSum];

            /* 记录已译码的消息长度 */
            *pulMsgLen = *pulMsgLen + 1;

            NAS_ETC_SndAirMsgReportInd(  pucMsg,*pulMsgLen,
                                        NAS_ETC_AIR_MSG_DIR_ENUM_DOWN,
                                        TC_RESET_POSITION_INFO);
            break;
        #endif


        default:
            NAS_ETC_WARN_LOG("NAS_ETC_DecodeNwMsg:WARNING:TC MSG Type not assigned ");
            TLPS_PRINT2LAYER_WARNING(NAS_ETC_DecodeNwMsg_ENUM, LNAS_TC_TCMSGTypeNotAssigned);
            return NAS_ETC_CAUSE_ERROR;
    }

    /* 判断已译码的消息长度与输入的消息总长度是否一致 */
    if (*pulMsgLen != ulMsgLen)
    {
        NAS_ETC_WARN_LOG("NAS_ETC_DecodeNwMsg:WARNING:Decoded Msg Len is not equal to input Msg Len ");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_DecodeNwMsg_ENUM, LNAS_TC_TcMsgLenthError);
    }

    return enTcCause;
}

/*****************************************************************************
 Function Name   : NAS_ETC_DecodeNwActTestModeMsg
 Description     : 译码ACTIVATE TEST MODE空口消息
 Input           : None
 Output          : None
 Return          : NAS_ETC_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
NAS_ETC_CAUSE_ENUM_UINT8  NAS_ETC_DecodeNwActTestModeMsg
(
    const VOS_UINT8                    *pucMsg,
    VOS_UINT32                         *pulTcMsgLen,
    NAS_ETC_NW_MSG_STRU                 *pstMsgIE
)
{
    VOS_UINT32                          ulSum               =  NAS_ETC_NULL;
    VOS_UINT32                          ulUnDecodeMsgLen    = *pulTcMsgLen;
    NAS_ETC_NW_MSG_STRU                 *pstTmpMsgIE         =  pstMsgIE;

    /*打印进入该函数*/
    NAS_ETC_INFO_LOG("NAS_ETC_DecodeNwActTestModeMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_DecodeNwActTestModeMsg_ENUM, LNAS_ENTRY);

    /* 判断剩余未译码长度是否合法 */
    if (ulUnDecodeMsgLen != (NAS_ETC_MIN_ACT_TEST_MODE_MSG_LEN - NAS_ETC_SUM_LEN_OF_PD_MSGTYPE))
    {
        NAS_ETC_WARN_LOG("NAS_ETC_DecodeNwActTestModeMsg:WARN: Input parameter error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_DecodeNwActTestModeMsg_ENUM, LNAS_PARAM_INVALID);
        return NAS_ETC_CAUSE_ERROR;
    }

    /* 保存环回模式 */
    pstTmpMsgIE->bitOpLBMode = NAS_ETC_OP_TRUE;
    pstTmpMsgIE->enLoopBackMode = pucMsg[ulSum++];

    /*保存此函数译出的消息长度*/
    *pulTcMsgLen = ulSum ;

    if ((pstTmpMsgIE->enLoopBackMode != LLOOP_BACK_MODE_A)
         && (pstTmpMsgIE->enLoopBackMode != LLOOP_BACK_MODE_B))
    {
        NAS_ETC_WARN_LOG("NAS_ETC_DecodeNwActTestModeMsg:WARN: Legal Loop Back Mode Type!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_DecodeNwActTestModeMsg_ENUM, LNAS_TC_LegalLoopBackModeType);
        return NAS_ETC_CAUSE_ERROR;
    }

    /*返回SM_SUCCESS*/
    return NAS_ETC_CAUSE_SUCCESS;
}

/*lint -e662*/
/*****************************************************************************
 Function Name   : NAS_ETC_DecodeNwCloseUeTestLoopModeA
 Description     : 译码CLOSE UE TEST LOOP空口消息模式A
 Input           : None
 Output          : None
 Return          : NAS_ETC_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-06-23  Draft Enact

*****************************************************************************/
NAS_ETC_CAUSE_ENUM_UINT8  NAS_ETC_DecodeNwCloseUeTestLoopModeA
(
    const VOS_UINT8                    *pucMsg,
    VOS_UINT32                         *pulTcMsgLen,
    NAS_ETC_NW_MSG_STRU                 *pstMsgIE
)
{
    VOS_UINT32                          ulSum               = NAS_ETC_NULL;
    VOS_UINT32                          ulLbSetListLen      = NAS_ETC_NULL;
    VOS_UINT16                          usSduSize           = NAS_ETC_NULL;
    VOS_UINT32                          ulLoop              = NAS_ETC_NULL;
    VOS_UINT32                          ulUnDecodeMsgLen    = *pulTcMsgLen;
    NAS_ETC_NW_MSG_STRU                 *pstTmpMsgIE         = pstMsgIE;

    pstTmpMsgIE->bitOpLBModeA = NAS_ETC_OP_TRUE;

    /* 记录LB set list长度 */
    ulLbSetListLen = pucMsg[ulSum++];

    /* 剩余未译码长度减1 */
    ulUnDecodeMsgLen--;

    /* LB set list长度必须为3的倍数，且要小于或等于剩余未译码长度 */
    if (((ulLbSetListLen % NAS_ETC_LB_SETUP_DRB_IE_LEN) != NAS_ETC_NULL)
         || (ulLbSetListLen > ulUnDecodeMsgLen))
    {
        NAS_ETC_WARN_LOG("NAS_ETC_DecodeNwCloseUeTestLoopMsg:WARN:LB Setup List Len Error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_DecodeNwCloseUeTestLoopModeA_ENUM, LNAS_FUNCTION_LABEL1);
        return NAS_ETC_CAUSE_ERROR;
    }

    /* 保存LB setup DRB个数 */
    pstTmpMsgIE->stLBModeA.ulDrbNum = ulLbSetListLen / NAS_ETC_LB_SETUP_DRB_IE_LEN;
    if (pstTmpMsgIE->stLBModeA.ulDrbNum > NAS_ETC_MAX_DRB_NUM)
    {
        NAS_ETC_WARN_LOG("NAS_ETC_DecodeNwCloseUeTestLoopMsg:WARN:DRB num is more than 8!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_DecodeNwCloseUeTestLoopModeA_ENUM, LNAS_FUNCTION_LABEL2);
        return NAS_ETC_CAUSE_ERROR;
    }

    /* 逐一保存LB setup DRB信息 */
    for (ulLoop = NAS_ETC_NULL; ulLoop < pstTmpMsgIE->stLBModeA.ulDrbNum; ulLoop++)
    {
        /* 保存SDU size信息 */
        usSduSize = (VOS_UINT16)pucMsg[ulSum++];
        usSduSize = (VOS_UINT16)(usSduSize << NAS_ETC_MOVEMENT_8_BITS)
                                    | (VOS_UINT16)pucMsg[ulSum++];

        /* 空口消息中SDU SIZE的单位为bit，而TC与PDCP接口中SDU SIZE的单位为
           byte，因此需要除8 */
        usSduSize /= 8;
        if (usSduSize > NAS_ETC_MAX_SDU_SIZE)
        {
            NAS_ETC_WARN_LOG("NAS_ETC_DecodeNwCloseUeTestLoopMsg:WARN:SDU SIZE is more than 1520!");
            TLPS_PRINT2LAYER_WARNING(NAS_ETC_DecodeNwCloseUeTestLoopModeA_ENUM, LNAS_FUNCTION_LABEL3);
            return NAS_ETC_CAUSE_ERROR;
        }
        pstTmpMsgIE->stLBModeA.astDrbSetup[ulLoop].ulSduSize = (VOS_UINT32)usSduSize;

        /* 保存DRB ID信息 */
        pstTmpMsgIE->stLBModeA.astDrbSetup[ulLoop].ulDrbId
                    = (VOS_UINT32)(pucMsg[ulSum++] & NAS_ETC_MSG_LOW_5_BIT);
    }

    *pulTcMsgLen = ulSum;
    return NAS_ETC_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ETC_DecodeNwCloseUeTestLoopMsg
 Description     : 译码CLOSE UE TEST LOOP空口消息
 Input           : None
 Output          : None
 Return          : NAS_ETC_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
NAS_ETC_CAUSE_ENUM_UINT8  NAS_ETC_DecodeNwCloseUeTestLoopMsg
(
    const VOS_UINT8                    *pucMsg,
    VOS_UINT32                         *pulTcMsgLen,
    NAS_ETC_NW_MSG_STRU                 *pstMsgIE
)
{
    VOS_UINT32                          ulSum               = NAS_ETC_NULL;
    NAS_ETC_CAUSE_ENUM_UINT8             enTcCause           = NAS_ETC_CAUSE_SUCCESS;
    VOS_UINT32                          ulUnDecodeMsgLen    = *pulTcMsgLen;
    VOS_UINT32                          ulMsgLenTmp         = NAS_ETC_NULL;
    NAS_ETC_NW_MSG_STRU                 *pstTmpMsgIE         = pstMsgIE;

    /*打印进入该函数*/
    NAS_ETC_INFO_LOG("NAS_ETC_DecodeNwCloseUeTestLoopMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_DecodeNwCloseUeTestLoopMsg_ENUM, LNAS_ENTRY);

    /* 判断剩余未译码长度是否合法 */
    if (ulUnDecodeMsgLen < (NAS_ETC_MIN_CLOSE_UE_TEST_LOOP_MSG_LEN - NAS_ETC_SUM_LEN_OF_PD_MSGTYPE))
    {
        NAS_ETC_WARN_LOG("NAS_ETC_DecodeNwCloseUeTestLoopMsg:WARN: Input parameter error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_DecodeNwCloseUeTestLoopMsg_ENUM, LNAS_PARAM_INVALID);
        return NAS_ETC_CAUSE_ERROR;
    }

    /* 保存环回模式 */
    pstTmpMsgIE->bitOpLBMode = NAS_ETC_OP_TRUE;
    pstTmpMsgIE->enLoopBackMode = pucMsg[ulSum++];

    /* 剩余未译码长度减1 */
    ulUnDecodeMsgLen--;

    /* 保存环回模式具体信息 */
    if (pstTmpMsgIE->enLoopBackMode == LLOOP_BACK_MODE_A)
    {
        ulMsgLenTmp = ulUnDecodeMsgLen;

        /* 译码模式A */
        enTcCause = NAS_ETC_DecodeNwCloseUeTestLoopModeA(   &pucMsg[ulSum],
                                                            &ulMsgLenTmp,
                                                            pstTmpMsgIE);

        if (NAS_ETC_CAUSE_SUCCESS != enTcCause)
        {
            return enTcCause;
        }

        ulSum += ulMsgLenTmp;
    }
    else if (pstTmpMsgIE->enLoopBackMode == LLOOP_BACK_MODE_B)
    {
        pstTmpMsgIE->bitOpLBModeB = NAS_ETC_OP_TRUE;

        /* 保存PDU delay 信息 */
        pstTmpMsgIE->stLBModeB.ulDelayTime = pucMsg[ulSum++];
    }
    else
    {
        NAS_ETC_WARN_LOG("NAS_ETC_DecodeNwCloseUeTestLoopMsg:WARN: Legal Loop Back Mode Type!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_DecodeNwCloseUeTestLoopMsg_ENUM, LNAS_TC_LegalLoopBackModeType);
        return NAS_ETC_CAUSE_ERROR;
    }

    /*保存此函数译出的消息长度*/
    *pulTcMsgLen = ulSum ;

    /*返回SM_SUCCESS*/
    return NAS_ETC_CAUSE_SUCCESS;
}
/*lint +e662*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasTcNwMsgDecode.c */
