/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasTcNwMsgEncode.c
    Description : TC模块组装空口消息发给网侧
    History     :
     1.李洪   00150010     2009-10-13  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasETcNwMsgEncode.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASTCNWMSGENCODE_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASTCNWMSGENCODE_C
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

VOS_VOID  NAS_ETC_EncodeActTestModeComplete
(
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT32                          ulSum        = NAS_ETC_NULL;
    VOS_UINT8                          *pTmpSendMsg  = pSendMsg;

    NAS_ETC_INFO_LOG("NAS_ETC_EncodeActTestModeComplete is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_EncodeActTestModeComplete_ENUM, LNAS_ENTRY);

    /*存放Protocol discriminator和Skip indicator，记录消息长度*/
    pTmpSendMsg[ulSum++] = ((VOS_UINT8)(NAS_ETC_SKIP_INDICATOR<< NAS_ETC_MOVEMENT_4_BITS)\
                                        & NAS_ETC_MSG_HIGH_BIT) | NAS_ETC_MSG_PD;

    /*存放Message type: NAS_ETC_CNMSG_TYPE_ACT_TEST_MODE_COMPLETE，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ETC_CNMSG_TYPE_ACT_TEST_MODE_COMPLETE;

    *pulLength = ulSum;
}


VOS_VOID  NAS_ETC_EncodeCloseUeTestLoopComplete
(
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT32                          ulSum        = NAS_ETC_NULL;
    VOS_UINT8                          *pTmpSendMsg  = pSendMsg;

    NAS_ETC_INFO_LOG("NAS_ETC_EncodeCloseUeTestLoopComplete is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_EncodeCloseUeTestLoopComplete_ENUM, LNAS_ENTRY);

    /*存放Protocol discriminator和Skip indicator，记录消息长度*/
    pTmpSendMsg[ulSum++] = ((VOS_UINT8)(NAS_ETC_SKIP_INDICATOR<< NAS_ETC_MOVEMENT_4_BITS)\
                                        & NAS_ETC_MSG_HIGH_BIT) | NAS_ETC_MSG_PD;

    /*存放Message type: NAS_ETC_CNMSG_TYPE_CLOSE_UE_TEST_LOOP_COMPLETE，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ETC_CNMSG_TYPE_CLOSE_UE_TEST_LOOP_COMPLETE;

    *pulLength = ulSum;
}


VOS_VOID  NAS_ETC_EncodeOpenUeTestLoopComplete
(
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT32                          ulSum        = NAS_ETC_NULL;
    VOS_UINT8                          *pTmpSendMsg  = pSendMsg;

    NAS_ETC_INFO_LOG("NAS_ETC_EncodeOpenUeTestLoopComplete is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_EncodeOpenUeTestLoopComplete_ENUM, LNAS_ENTRY);

    /*存放Protocol discriminator和Skip indicator，记录消息长度*/
    pTmpSendMsg[ulSum++] = ((VOS_UINT8)(NAS_ETC_SKIP_INDICATOR<< NAS_ETC_MOVEMENT_4_BITS)\
                                        & NAS_ETC_MSG_HIGH_BIT) | NAS_ETC_MSG_PD;

    /*存放Message type: NAS_ETC_CNMSG_TYPE_OPEN_UE_TEST_LOOP_COMPLETE，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ETC_CNMSG_TYPE_OPEN_UE_TEST_LOOP_COMPLETE;

    *pulLength = ulSum;
}


VOS_VOID  NAS_ETC_EncodeDeactTestModeComplete
(
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT32                          ulSum        = NAS_ETC_NULL;
    VOS_UINT8                          *pTmpSendMsg  = pSendMsg;

    NAS_ETC_INFO_LOG("NAS_ETC_EncodeDeactTestModeComplete is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_EncodeDeactTestModeComplete_ENUM, LNAS_ENTRY);

    /*存放Protocol discriminator和Skip indicator，记录消息长度*/
    pTmpSendMsg[ulSum++] = ((VOS_UINT8)(NAS_ETC_SKIP_INDICATOR<< NAS_ETC_MOVEMENT_4_BITS)\
                                        & NAS_ETC_MSG_HIGH_BIT) | NAS_ETC_MSG_PD;

    /*存放Message type: NAS_ETC_CNMSG_TYPE_DEACT_TEST_MODE_COMPLETE，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ETC_CNMSG_TYPE_DEACT_TEST_MODE_COMPLETE;

    *pulLength = ulSum;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasTcNwMsgEncode.c */

