/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLppEmmMsgProc.c
    Description : 处理EMM发给LPP的消息
    History     :
    lifuxin 00253982 2015-7-7  新开发
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "vos.h"
#include    "PsLogdef.h"
#include    "PsTypeDef.h"
#include    "NasLppEmmMsgProc.h"
#include    "EmmLppInterface.h"
#include    "NasLppPublic.h"
#include    "NasLppUpPublic.h"
#include    "NasLppSendMsg.h"
#include    "NasLppEncode.h"
#include    "NasLppOm.h"
#include    "NasLppIntraMsgProc.h"
#include    "NasLppDecode.h"
#include    "NasLppSendMsg.h"
#include    "LppMtaInterface.h"
#include    "OmCommon.h"
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



#define    THIS_FILE_ID            PS_FILE_ID_NASLPPEMMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPEMMMSGPROC_C

#if (FEATURE_LPP == FEATURE_ON)

static  VOS_UINT32              g_ulEmmLppOpId = 0;


/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e701*/
/*****************************************************************************
 Function Name  : NAS_LPP_SndAllUplinkMsg
 Description    : 取出buffer中的直传消息依次发送给LMM
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-30  新开发
*****************************************************************************/
VOS_VOID  NAS_LPP_SndAllUplinkMsg(VOS_VOID)
{
    NAS_LPP_UP_MSG_BUFF_POOL_STRU   *pstUpMsgBuffPool   = NAS_LPP_NULL_PTR;
    LPP_LMM_DATA_REQ_STRU           *pstLppDataReq      = NAS_LPP_NULL_PTR;
    LPP_LMM_DATA_REQ_STRU           *pstLppBuffDataReq  = NAS_LPP_NULL_PTR;
    VOS_UINT32                       ulLoop             = 0;
    VOS_BOOL                         bSendFlag          = PS_FALSE;
    VOS_UINT32                       ulLength           = 0;
    VOS_UINT32                       ulUplinkIndx       = 0;
    VOS_UINT8                        ucSessionIndx      = 0;
    VOS_UINT32                       ulSessionId        = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_SndAllUplinkMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndAllUplinkMsg_ENUM, LNAS_LPP_SndAllUplinkMsgEnter);

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();

    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        /*如果上行index的使用标记为true，说明对应的索引处存储了上行消息*/
        if(PS_TRUE == pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUsedFlag)
        {
            /*上行缓存索引*/
            ulUplinkIndx = pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUpLinkBuffIndex;

            /*对应的索引的bit位置上了，则说明一定有上行直传消息，则传之*/
            if(0 != (pstUpMsgBuffPool->ulBitMap & (0x1 << ulUplinkIndx)))
            {
                bSendFlag = pstUpMsgBuffPool->astLppUpMsg[ulUplinkIndx].bSendBufFlag;
                pstLppBuffDataReq = &(pstUpMsgBuffPool->astLppUpMsg[ulUplinkIndx].u.stLppDataReq);
                ulLength = pstUpMsgBuffPool->astLppUpMsg[ulUplinkIndx].u.stLppDataReq.ulLength + VOS_MSG_HEAD_LENGTH;
                if(PS_FALSE == bSendFlag)
                {
                    NAS_LPP_INFO_LOG1("NAS_LPP_SndAllUplinkMsg: Send data req, pool index = !", ulUplinkIndx);
                    TLPS_PRINT2LAYER_INFO1(NAS_LPP_SndAllUplinkMsg_ENUM, LNAS_LPP_SndDataReqPoolIndex, ulUplinkIndx);
                    pstLppDataReq = (LPP_LMM_DATA_REQ_STRU*)NAS_LPP_ALLOC_MSG(ulLength);
                    if(NAS_LPP_NULL_PTR == pstLppDataReq)
                    {
                        return;
                    }
                    NAS_LPP_MEM_CPY_S(  pstLppDataReq,
                                        ulLength,
                                        pstLppBuffDataReq,
                                        ulLength);

                    /*获取成功，而且没有发送成功过，则调用发送函数发送dataReq给LMM*/
                    NAS_LPP_SND_MSG(pstLppDataReq);

                    ulSessionId = pstUpMsgBuffPool->astLppUpMsg[ulUplinkIndx].stLppMsgIdentity.ulSessionId;
                    ucSessionIndx = NAS_LPP_SearchSessionIndx(ulSessionId);
                    if(PS_NULL_UINT8 != ucSessionIndx)
                    {
                        /*先停*/
                        NAS_LPP_TimerStop(ucSessionIndx,
                                           NAS_LPP_TIMER_INVAILD_PARA,
                                           TI_NAS_LPP_SEQUENCE_NUMBER_INVALID);
                        /*再起*/
                        NAS_LPP_TimerStart(ucSessionIndx,
                                           NAS_LPP_TIMER_INVAILD_PARA,
                                           TI_NAS_LPP_SEQUENCE_NUMBER_INVALID);
                    }

                }
            }
        }
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_ConnFailHandle
 Description    : 连接FAIL之后的处理
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_VOID  NAS_LPP_ConnFailHandle(VOS_VOID)
{
    NAS_LPP_INFO_LOG("NAS_LPP_ConnFailHandle enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_ConnFailHandle_ENUM, LNAS_LPP_ConnFailHandleEnter);

    NAS_LPP_SndIntraLppMsg(0, NAS_LPP_NULL_PTR, NAS_LPP_CONN_MANAGE_FAIL);
    NAS_LPP_ClearLppTransCnt();
    NAS_LPP_SetLppConnStatus(NAS_LPP_CONN_STATUS_IDLE);

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_RcvLppEmmEstCnf
 Description    : LPP模块收到建链回复消息
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_VOID  NAS_LPP_RcvLppEmmEstCnf(const LMM_LPP_EST_CNF_STRU *stEstCnf)
{
    NAS_LPP_INFO_LOG("NAS_LPP_RcvLppEmmEstCnf is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEmmEstCnf_ENUM, LNAS_LPP_RcvLppEmmEstCnfEnter);

    /*停止建链定时器*/
    NAS_LPP_TimerStop(NAS_LPP_TIMER_INVAILD_PARA,
                      NAS_LPP_TIMER_INVAILD_PARA,
                      TI_NAS_LPP_WAIT_EST_CNF);

    switch (stEstCnf->ulEstRst)
    {
        case LMM_LPP_EST_RESULT_SUCC:
            NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmEstCnf: EST SUCC, Start Send Uplink Buffer Msg!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEmmEstCnf_ENUM, LNAS_LPP_RcvLppEmmEstCnfEstSucc);

            /*建链成功，将当前的连接状态置成CONNECT*/
            NAS_LPP_SetLppConnStatus(NAS_LPP_CONN_STATUS_CONNECT);

            /*依次去取上行缓存buffer中的直传消息，发送给LMM*/
            NAS_LPP_SndAllUplinkMsg();

            /*清空传输次数为0*/
            NAS_LPP_ClearLppTransCnt();
            break;

        case LMM_LPP_EST_RESULT_FAIL_3411_RUNNING:
            /*3411正在运行中，等10s之后再次尝试发起建链*/
            /*疑问，如果根据一个定时器去取不同的超时时间*/
            NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmEstCnf: 3411 running!");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvLppEmmEstCnf_ENUM, LNAS_LPP_RcvLppEmmEstCnf3411Running);
            NAS_LPP_ModifyTimerLen(TI_NAS_LPP_WAIT_RE_EST,PS_NULL_UINT8,PS_NULL_UINT8,10000);
            NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                               NAS_LPP_TIMER_INVAILD_PARA,
                               TI_NAS_LPP_WAIT_RE_EST);
            break;

        case LMM_LPP_EST_RESULT_FAIL_SERVICE_FAIL:
            NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmEstCnf: sevice fail!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLppEmmEstCnf_ENUM, LNAS_LPP_RcvLppEmmEstCnfServiceFail);
            /*SERVICER FAIL场景，等2s后再尝试发起建链*/
            /*建链失败的场景，考虑重建链*/
            NAS_LPP_ModifyTimerLen(TI_NAS_LPP_WAIT_RE_EST,PS_NULL_UINT8,PS_NULL_UINT8, 2000);
            NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                               NAS_LPP_TIMER_INVAILD_PARA,
                               TI_NAS_LPP_WAIT_RE_EST);
            break;

        default:
            /*除开上面之外的状态，不再发起建链，直接通知终止当前流程*/
            NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmEstCnf: No 3411 and sevice fail!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLppEmmEstCnf_ENUM, LNAS_LPP_RcvLppEmmEstCnfBeside3411AndServiveFail);
            NAS_LPP_ConnFailHandle();
            break;
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppMsgIndentityByOpId
 Description    : 通过OPID找到LppMsgIndentity
 Input          : LMM_LPP_DATA_CNF_STRU *pstDataCnf
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-30  新开发
*****************************************************************************/
NAS_LPP_MSG_IDENTITY_STRU*  NAS_LPP_GetLppMsgIndentityByOpId
(
    VOS_UINT32              ulLmmLppOpId
)
{
    NAS_LPP_UP_MSG_BUFF_POOL_STRU   *pstUpMsgBuffPool = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_IDENTITY_STRU       *pstLppMsgIndentity = NAS_LPP_NULL_PTR;
    VOS_UINT32                       ulLoop           = 0;
    VOS_UINT32                       ulOpId           = 0;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();
    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        if(0 != (pstUpMsgBuffPool->ulBitMap & (0x1 << ulLoop)))
        {
            ulOpId = pstUpMsgBuffPool->astLppUpMsg[ulLoop].u.stLppDataReq.ulOpId;
            NAS_LPP_INFO_LOG2("NAS_LPP_GetLppMsgIndentityByOpId: SOpid, DOpid!,", ulOpId, ulLmmLppOpId);
            TLPS_PRINT2LAYER_INFO1(NAS_LPP_GetLppMsgIndentityByOpId_ENUM, LNAS_LPP_GetLppMsgIndentityByOpIdSourceOpId, ulOpId);
            TLPS_PRINT2LAYER_INFO1(NAS_LPP_GetLppMsgIndentityByOpId_ENUM, LNAS_LPP_GetLppMsgIndentityByOpIdDestinationOpId, ulLmmLppOpId);
            if(ulOpId == ulLmmLppOpId)
            {
                pstLppMsgIndentity = &(pstUpMsgBuffPool->astLppUpMsg[ulLoop].stLppMsgIdentity);
                break;
            }
        }

    }

    return pstLppMsgIndentity;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppMsgUpBuffByOpId
 Description    : 通过OPID找到上行缓存buffer
 Input          : LMM_LPP_DATA_CNF_STRU *pstDataCnf
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-30  新开发
*****************************************************************************/
LPP_UPLINK_MSG_BUF_STRU*  NAS_LPP_GetLppMsgUpBuffByOpId
(
    VOS_UINT32              ulLmmLppOpId
)
{
    NAS_LPP_UP_MSG_BUFF_POOL_STRU   *pstUpMsgBuffPool = NAS_LPP_NULL_PTR;
    VOS_UINT32                       ulLoop           = 0;
    VOS_UINT32                       ulOpId           = 0;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();
    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        if(0 != (pstUpMsgBuffPool->ulBitMap & (0x1 << ulLoop)))
        {
            ulOpId = pstUpMsgBuffPool->astLppUpMsg[ulLoop].u.stLppDataReq.ulOpId;
            if(ulOpId == ulLmmLppOpId)
            {
                return  &(pstUpMsgBuffPool->astLppUpMsg[ulLoop]);
            }
        }

    }

    return NAS_LPP_NULL_PTR;
}


/*****************************************************************************
 Function Name  : NAS_LPP_GetLppMsgSendFlagByOpId
 Description    : 通过OPID找到SendFlag
 Input          : LMM_LPP_DATA_CNF_STRU *pstDataCnf
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-30  新开发
*****************************************************************************/
VOS_BOOL  NAS_LPP_GetLppMsgSendFlagByOpId
(
    VOS_UINT32              ulLmmLppOpId
)
{
    NAS_LPP_UP_MSG_BUFF_POOL_STRU   *pstUpMsgBuffPool = NAS_LPP_NULL_PTR;
    VOS_UINT32                       ulLoop           = 0;
    VOS_UINT32                       ulOpId           = 0;
    VOS_BOOL                         bSendFlag        = PS_FALSE;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();
    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        if(0 != (pstUpMsgBuffPool->ulBitMap & (0x1 << ulLoop)))
        {
            ulOpId = pstUpMsgBuffPool->astLppUpMsg[ulLoop].u.stLppDataReq.ulOpId;
            if(ulOpId == ulLmmLppOpId)
            {
                bSendFlag = pstUpMsgBuffPool->astLppUpMsg[ulLoop].bSendBufFlag;
            }
        }

    }

    return bSendFlag;
}

/*****************************************************************************
 Function Name  : NAS_LPP_GetLppMsgSendFlagByOpId
 Description    : 通过OPID找到SendFlag
 Input          : LMM_LPP_DATA_CNF_STRU *pstDataCnf
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-30  新开发
*****************************************************************************/
VOS_VOID  NAS_LPP_SetLppMsgSendFlagByOpId
(
    VOS_UINT32                  ulLmmLppOpId,
    VOS_BOOL                    bLppSendFlag
)
{
    NAS_LPP_UP_MSG_BUFF_POOL_STRU   *pstUpMsgBuffPool = NAS_LPP_NULL_PTR;
    VOS_UINT32                       ulLoop           = 0;
    VOS_UINT32                       ulOpId           = 0;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();
    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        if(0 != (pstUpMsgBuffPool->ulBitMap & (0x1 << ulLoop)))
        {
            ulOpId = pstUpMsgBuffPool->astLppUpMsg[ulLoop].u.stLppDataReq.ulOpId;
            if(ulOpId == ulLmmLppOpId)
            {
                pstUpMsgBuffPool->astLppUpMsg[ulLoop].bSendBufFlag = bLppSendFlag;

                return;
            }
        }

    }

    return;
}


/*****************************************************************************
 Function Name  : NAS_LPP_IsAckDataCnf
 Description    : 判断发送的消息是否就是ack消息
 Input          : pstLppMsgIdentity
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_BOOL  NAS_LPP_IsAckDataCnf
(
    NAS_LPP_MSG_IDENTITY_STRU           *pstLppMsgIdentity
)
{
    if(NAS_LPP_UPLINK_MSG_TYPE_ACK == pstLppMsgIdentity->enUplinkMsgType)
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
 Function Name  : NAS_LPP_AckDataCnfSuccHandle
 Description    : LPP收到ACK消息的data cnf之后的处理
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_VOID  NAS_LPP_AckDataCnfSuccHandle
(
    VOS_UINT32          ulOpId
)
{
    LPP_UPLINK_MSG_BUF_STRU  *pstUplinkMsgBuff = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_AckDataCnfSuccHandle is entered!");

    pstUplinkMsgBuff = NAS_LPP_GetLppMsgUpBuffByOpId(ulOpId);
    if(NAS_LPP_NULL_PTR == pstUplinkMsgBuff)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_AckDataCnfSuccHandle: No buffer!");
        return;
    }

    NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuff);

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_RcvLppEmDataCnf
 Description    : LPP模块收到直传回复的消息处理
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_VOID  NAS_LPP_RcvLppEmDataCnf(const LMM_LPP_DATA_CNF_STRU *pstDataCnf)
{
    NAS_LPP_MSG_IDENTITY_STRU           *pstLppMsgIdentity  = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmDataCnf is entered!");
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_RcvLppEmDataCnf_ENUM, LNAS_LPP_RcvLppEmDataCnfResult, pstDataCnf->enDataCnfRst);

    switch (pstDataCnf->enDataCnfRst)
    {
        case LMM_LPP_SEND_RSLT_SUCCESS:
            /*
            直传成功，发送内部消息给相应的transaction，启动重传定时器，同时将对应
            buffer指针设置为NULL,表示当前没有不再使用该buffer
            */
            NAS_LPP_ClearLppTransCnt();
            /*直传成功,发送内部消息通知transaction，并且将sendFlag设置成TRUE*/
            pstLppMsgIdentity = NAS_LPP_GetLppMsgIndentityByOpId(pstDataCnf->ulOpId);
            if(NAS_LPP_NULL_PTR == pstLppMsgIdentity)
            {
                NAS_LPP_ERR_LOG("NAS_LPP_RcvLppEmDataCnf: don't find the LppMsgIndentity!");
                TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLppEmDataCnf_ENUM, LNAS_LPP_RcvLppEmDataCnfDontFindUpBuff);

                return;
            }

            /*如果当前消息就是ACK消息的回复，那么删除对应的上行buffer的缓存消息*/
           /* if(PS_TRUE == NAS_LPP_IsAckDataCnf(pstLppMsgIdentity))
            {
                NAS_LPP_AckDataCnfSuccHandle(pstDataCnf->ulOpId);
                break;
            }*/

            NAS_LPP_SndIntraLppMsg( pstDataCnf->ulOpId, pstLppMsgIdentity, NAS_LPP_SUCCESS);

            /*将直传buffer的SendFlag置成TRUE*/
            NAS_LPP_SetLppMsgSendFlagByOpId(pstDataCnf->ulOpId, PS_TRUE);

            break;

        case LMM_LPP_SEND_RSLT_FAIL_RRC_CONN_NOT_EXIST:
            if(NAS_LPP_GetTransLppMsgCnt() < NAS_LPP_GetLppTransAttepCnt())
            {
                /*建链次数没有达到最大，发起建链*/
                NAS_LPP_LppLmmEstReq();

                /*启动建链定时器*/
                NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                                  NAS_LPP_TIMER_INVAILD_PARA,
                                  TI_NAS_LPP_WAIT_EST_CNF);

                /*传输次数加1*/
                NAS_LPP_TransLppMsgAddCnt();
            }
            else
            {
                /*建链次数达到最大次数，通知Session释放所有的资源*/
                NAS_LPP_ConnFailHandle();
            }
            break;

        case LMM_LPP_SEND_RSLT_LOW_LAYER_FAIL:
            /*底层错误，等待2s之后发起建链*/
            NAS_LPP_ModifyTimerLen(TI_NAS_LPP_WAIT_RE_EST,PS_NULL_UINT8,PS_NULL_UINT8, NAS_LPP_LOW_LAYER_FAIL_RE_REST_TIME_LEN);
            NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                               NAS_LPP_TIMER_INVAILD_PARA,
                               TI_NAS_LPP_WAIT_RE_EST);
            break;

        case LMM_LPP_SEND_RSLT_FAIL_3411_RUNNING:
            /*等十秒钟再发起建链*/
            NAS_LPP_ModifyTimerLen(TI_NAS_LPP_WAIT_RE_EST,PS_NULL_UINT8,PS_NULL_UINT8, NAS_LPP_3411_FAIL_RE_REST_TIME_LEN);
            NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                               NAS_LPP_TIMER_INVAILD_PARA,
                               TI_NAS_LPP_WAIT_RE_EST);
            break;

        default:
            /*除开上面之外的状态，不再发起建链，直接通知终止当前流程*/
            NAS_LPP_ConnFailHandle();
            break;
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_CheckEcidDownLinkMsg
 Description    : 校验ECID下行空口消息
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-22  新开发
*****************************************************************************/
VOS_UINT32  NAS_LPP_CheckEcidDownLinkMsg(LPP_REQ_LOCATION_INFO_R9_IES_STRU *pstReqLocInfoR9Ies)
{
    NAS_LPP_NORM_LOG("NAS_LPP_CheckEcidDownLinkMsg is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_CheckEcidDownLinkMsg_ENUM, LNAS_LPP_CheckEcidDownLinkMsgEnter);

    /*ECID The field is optionally present, need ON, if ECID is requested. Otherwise it is not present.*/
    /*如果是条件触发上报，那么一定是ECID的定位技术，如果出现其他的定位技术，则认为是错误*/
    if((NAS_LPP_SLCT == pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.bitOpTriggeredReportCriteria)
       && ((NAS_LPP_SLCT == pstReqLocInfoR9Ies->bitOpOtdoaReqLocationInfo)
       || (NAS_LPP_SLCT == pstReqLocInfoR9Ies->bitOpAGNSSReqLocationInfo)))
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckEcidDownLinkMsg,LPP msg body: Tigger report NOT for OTDOA&GNSS!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckEcidDownLinkMsg_ENUM,
                               LNAS_LPP_CheckEcidDownLinkMsgTiggerReportNotForOtdoaAndGnss);

        return NAS_LPP_MSG_VERIFY_COMMOM_BODY_REPORT_TYPE_ERROR;
    }

    return NAS_LPP_MSG_VERIFY_SUCC;
}


/*****************************************************************************
 Function Name  : NAS_LPP_CheckEcidDownLinkMsg
 Description    : 校验公共的下行空口消息
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID
 History        :
      lifuxin 00253982 2015-7-22  新开发
*****************************************************************************/
VOS_UINT32  NAS_LPP_CheckCommomDownLinkMsg(LPP_MESSAGE_STRU *pstLppMsg)
{
    LPP_REQ_LOCATION_INFO_R9_IES_STRU  *pstReqLocInfoR9Ies = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_CheckCommomDownLinkMsg is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_CheckCommomDownLinkMsg_ENUM, LNAS_LPP_CheckCommomDownLinkMsgEnter);

    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckCommomDownLinkMsg_ENUM, pstLppMsg->bitOpLppMessageBody,LNAS_LPP_TransIndex);

    /*消息头的检查*/
    /*如果当前带有消息体，则transactionID和sequenceNumber一定存在*/
    if((NAS_LPP_SLCT == pstLppMsg->bitOpLppMessageBody)
       && ((NAS_LPP_NO_SLCT == pstLppMsg->bitOpLppTransactionId)))
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckCommomDownLinkMsg,LPP msg body: No transId or sequence Number!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckCommomDownLinkMsg_ENUM, LNAS_LPP_CheckCommomDownLinkMsgLppMsgBodyNoTransIdOrSequenceNumber);

        return NAS_LPP_MSG_VERIFY_HEAD_FAIL;
    }

    /*如果当前不带有消息体，基于目前的协议版本来说，那么该消息一定是ACK消息*/
    if((NAS_LPP_NO_SLCT == pstLppMsg->bitOpLppMessageBody)
      && ((NAS_LPP_NO_SLCT == pstLppMsg->bitOpAcknowledgement)
      || ((NAS_LPP_SLCT == pstLppMsg->bitOpAcknowledgement)
      && (NAS_LPP_NO_SLCT == pstLppMsg->stAcknowledgement.bitOpAckIndicator))))
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckCommomDownLinkMsg,Ack Msg: No Ack or Have Ack but no AckIndicatior!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckCommomDownLinkMsg_ENUM, LNAS_LPP_CheckCommomDownLinkMsgAckMsgNoAckOrHaveAckButNoAckindicatior);

        return NAS_LPP_MSG_VERIFY_HEAD_FAIL;
    }

    if ( (NAS_LPP_SLCT == pstLppMsg->bitOpLppMessageBody)
       &&(LPP_C1_MESSAGE_BODY_CHOSEN == pstLppMsg->stLppMessageBody.ulChoice)
       &&(LPP_SUPPORT_MESSAGE_BODY_REQUEST_LOCATION_INFO_CHOSEN == pstLppMsg->stLppMessageBody.u.stC1.ulChoice) )
    {
        /*三种上报方式的检查*/
        pstReqLocInfoR9Ies = NAS_LPP_GetDownLinkLocationReqIEAddr(pstLppMsg);
        if(NAS_LPP_SLCT == pstReqLocInfoR9Ies->bitOpCommonIEsReqLocationInfo)
        {

            /*如果要求是周期性的上报，则要求清除上报一次以及触发上报的信息*/
            if(NAS_LPP_SLCT == pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.bitOpPeriodicalReportCriteria)
            {
                pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.bitOpTriggeredReportCriteria =
                                                                                    NAS_LPP_NO_SLCT;
                NAS_LPP_MEM_SET_S(&(pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.stTriggerReportCriteria),
                                sizeof(LPP_MTA_COMMON_TRIGGER_REPORT_CRITERIA_STRU),
                                0,
                                sizeof(LPP_MTA_COMMON_TRIGGER_REPORT_CRITERIA_STRU));

                /*清除上报一次场景的信息*/
                pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.stQos.bitOpResponseTime = NAS_LPP_NO_SLCT;
                NAS_LPP_MEM_SET_S(&(pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.stQos.stResponseTime),
                                sizeof(LPP_MTA_COMMON_RESPONSE_TIME_STRU),
                                0,
                                sizeof(LPP_MTA_COMMON_RESPONSE_TIME_STRU));
            }

            /*如果是上报一次的场景，则要求清除触发上报的场景*/
            if((NAS_LPP_SLCT == pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.bitOpQos)
                    && (NAS_LPP_SLCT == pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.stQos.bitOpResponseTime))
            {
                pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.bitOpTriggeredReportCriteria =
                                                                                    NAS_LPP_NO_SLCT;
                NAS_LPP_MEM_SET_S(&(pstReqLocInfoR9Ies->stCommonIEsReqLocationInfo.stTriggerReportCriteria),
                                sizeof(LPP_MTA_COMMON_TRIGGER_REPORT_CRITERIA_STRU),
                                0,
                                sizeof(LPP_MTA_COMMON_TRIGGER_REPORT_CRITERIA_STRU));
            }

            /*既不是周期性上报，又不是上报一次的场景，则一定是触发上报的场景*/
        }
    }

    return NAS_LPP_MSG_VERIFY_SUCC;
}

/*****************************************************************************
 Function Name  : NAS_LPP_CheckOtdoaDownLinkMsg
 Description    : 校验OTDOA下行空口消息
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-22  新开发
*****************************************************************************/
VOS_UINT32  NAS_LPP_CheckOtdoaDownLinkMsg(LPP_REQ_LOCATION_INFO_R9_IES_STRU *pstReqLocInfoR9Ies)
{

    return NAS_LPP_MSG_VERIFY_SUCC;
}

/*****************************************************************************
 Function Name  : NAS_LPP_CheckGnssDownLinkMsg
 Description    : 校验GNSS下行空口消息
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-22  新开发
*****************************************************************************/
VOS_UINT32  NAS_LPP_CheckGnssDownLinkMsg(LPP_REQ_LOCATION_INFO_R9_IES_STRU *pstReqLocInfoR9Ies)
{
    if(NAS_LPP_NO_SLCT == pstReqLocInfoR9Ies->bitOpAGNSSReqLocationInfo)
    {
        return  NAS_LPP_MSG_VERIFY_SUCC;
    }
    /*
    gnssMethods
    This field indicates the satellite systems allowed by the location server. This is represented by a bit
    string in GNSS-ID-Bitmap, with a one value at the bit position means the particular GNSS is allowed; a
    zero value means not allowed.The target device shall not request assistance data or report or obtain
    measurements for systems that are not indicated in this bit map. At least one of the bits in this bit
    map shall be set to value one.
    */
    /*检查GnssMethods，至少要有一个BIT被置成了1，否则被认为是错误*/
    if((0 == pstReqLocInfoR9Ies->stAGNSSReqLocationInfo.stGNSSPositonINsturction.stGNSSMethods.usGnssIdsCnt)
       && (0 == pstReqLocInfoR9Ies->stAGNSSReqLocationInfo.stGNSSPositonINsturction.stGNSSMethods.usGNSSIDs))
    {
        return NAS_LPP_FAILURE;
    }

    return NAS_LPP_MSG_VERIFY_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_CheckOtdoaNeighbourCell
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-6  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_CheckOtdoaNeighbourCell
(
    LPP_OTDOA_NEIGHOUR_CELL_INFO_STRU   *pstOtdoaNeighbourCellInfo,
    VOS_UINT32                           ulRefArfcn)
{
    VOS_UINT32 ulLoop,ulLoop1,ulEarfcn; /* referrencr earfcn这里不需要知道明确的大小，只是作为一个比较的基准值而已*/

    if (pstOtdoaNeighbourCellInfo->ulOtdoaNeighbourCellInfoListCnt > LPP_MAX_FREQ_LAYERS_LEN)
    {
        NAS_LPP_ERR_LOG1("otdoa neighbor cell freq cnt overflow", pstOtdoaNeighbourCellInfo->ulOtdoaNeighbourCellInfoListCnt);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighborCellFreqCntOverflow);

        return NAS_LPP_MSG_VERIFY_FAIL;
    }

    /* 前置条件:neighbour list不支持additional neighbor list*/
    /*neighbour list每个频率层里的小区的频率要一致*/
    for ( ulLoop = 0 ; ulLoop < pstOtdoaNeighbourCellInfo->ulOtdoaNeighbourCellInfoListCnt; ulLoop++ )
    {
        if (pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt > LPP_MAX_OTDOA_NEIGHBOUR_CELL_INFO_ELMENT_LEN)
        {
            NAS_LPP_ERR_LOG2("otdoa neighbor cell cell cnt overflow",
                             ulLoop,
                             pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt);
            TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellCntOverflowLoop, ulLoop);
            TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellCntOverflowLoopCnt,
                                                pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt);

            return NAS_LPP_MSG_VERIFY_FAIL;
        }

        /*每个频点的第一个小区频率*/
        if (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].bitOpEarfcn)
        {
            ulEarfcn = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].stEarfcn.ulArfcnValueEUTRA;
        }
        else if (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].bitOpEarfcnV9a0)
        {
            ulEarfcn = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].stEarfcnv9a0.ulArfcnValueEUTRAv9a0;
        }
        else
        {
            ulEarfcn = ulRefArfcn;
        }


        for ( ulLoop1 = 1 ;
              ulLoop1 < pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt;
              ulLoop1++ )
        {
            /*后续每个小区的频率要保持一致:比较第n个和第(n-1)个*/
            if (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[ulLoop1].bitOpEarfcn)
            {
                if ( ulEarfcn != pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[ulLoop1].stEarfcn.ulArfcnValueEUTRA )
                {
                    NAS_LPP_ERR_LOG2("otdoa neighbor cell arfcn not same ",ulLoop,ulLoop1);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellArfcnNotSameLoop, ulLoop);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellArfcnNotSameLoop1, ulLoop1);

                    return NAS_LPP_MSG_VERIFY_FAIL;
                }
            }
            else if (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[ulLoop1].bitOpEarfcnV9a0)
            {
                if ( ulEarfcn != pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[ulLoop1].stEarfcnv9a0.ulArfcnValueEUTRAv9a0 )
                {
                    NAS_LPP_ERR_LOG2("otdoa neighbor v9a0 cell arfcn not same ",ulLoop,ulLoop1);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellArfcnVa90NotSameLoop, ulLoop);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellArfcnVa90NotSameLoop1, ulLoop1);

                    return NAS_LPP_MSG_VERIFY_FAIL;
                }
            }
            else
            {
                /*每个小区的频点都不用明确说明*/
                if ( ulEarfcn != ulRefArfcn )
                {
                    NAS_LPP_ERR_LOG2("otdoa neighbor ref cell arfcn not same ",ulLoop,ulLoop1);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellRefCellNotSameLoop, ulLoop);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CheckOtdoaNeighbourCell_ENUM, LNAS_LPP_CheckOtdoaParameterOtdoaNeighberCellRefCellNotSameLoop1, ulLoop1);

                    return NAS_LPP_MSG_VERIFY_FAIL;
                }
                else
                {
                }
            }

        }
    }


    return NAS_LPP_MSG_VERIFY_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetRefEarfcnFromOtdoaAssis
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-12  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_GetRefEarfcnFromOtdoaAssis( LPP_OTDOA_REF_CELL_INFO_STRU  *pstOtdoaRefCellInfo )
{
    VOS_UINT32 ulEarfcn;

    /*36.355  earfcnRef         ARFCN-ValueEUTRA        OPTIONAL,       -- Cond NotSameAsServ0
      This field is absent if earfcnRef-v9a0 is present. Otherwise, the field is mandatory present if the EARFCN of
      the OTDOA assistance data reference cell is not the same as the EARFCN of the target devices's current primary cell.*/
    if (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpEarFcnRef)
    {
         ulEarfcn = pstOtdoaRefCellInfo->stEarfcnRef.ulArfcnValueEUTRA;
    }
    /*earfcnRef-v9a0        ARFCN-ValueEUTRA-v9a0   OPTIONAL    -- Cond NotSameAsServ2
      The field is absent if earfcnRef is present. Otherwise, the field is mandatory present if the EARFCN of the OTDOA
      assistance data reference cell is not the same as the EARFCN of the target devices's current primary cell.*/
    else if ( (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpEarfcnRefV9a0)
            &&(NAS_LPP_SLCT == pstOtdoaRefCellInfo->stEarfcnRefV9a0.bitOpARFCNValueEutraV9A0) )
    {
        ulEarfcn = pstOtdoaRefCellInfo->stEarfcnRefV9a0.ulArfcnValueEUTRAv9a0;
    }
    /* 如果bitOpEarFcnRef和bitOpEarfcnRefV9a0都不在,使用serving cell的*/
    else
    {
        ulEarfcn = NAS_LPP_GetServingCell()->ulEarfcn;
    }

    return ulEarfcn;

}
/*****************************************************************************
 Function Name   : NAS_LPP_CheckAssisData
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-12  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_CheckAssisData( LPP_MESSAGE_PROVIDE_ASSIST_DATA_STRU *pstProvideAssistanceData )
{
    LPP_PROVIDE_ASSIST_DATA_R9_IES_STRU *pstProvideAssitDataR9;
    NAS_LPP_OTDOA_ASSIST_CFG_STRU       *pstOtdoaAssisCfg;
    VOS_UINT32 ulRslt;

    pstProvideAssitDataR9 = &(pstProvideAssistanceData->u.stC1.u.stProvideAssitDataR9);

    pstOtdoaAssisCfg = NAS_LPP_GetOtdoaAssisCfg();

    /* 由于neighbour cell list不支持 addtional neighbour list，所以，所有的相同频点的小区都排在一个frequency cell 层里。*/
    if ( (NAS_LPP_SLCT == pstProvideAssistanceData->u.stC1.u.stProvideAssitDataR9.bitOpOTDOAProvideAssistData)
       &&(NAS_LPP_SLCT == pstProvideAssitDataR9->stOTDOAProvideAssistanceData.bitOpOtdoaNeighbourCellInfo) )
    {
        if ( LPP_LRRC_INFO_FLAG_VALID == pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag )
        {
            ulRslt = NAS_LPP_CheckOtdoaNeighbourCell(&pstProvideAssitDataR9->stOTDOAProvideAssistanceData.stOtdoaNeighbourCellInfo,
                                                     pstOtdoaAssisCfg->stOtdoaReferenceCellInfo.ulEarfcn);
            if (NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
            {
                NAS_LPP_ERR_LOG("NAS_LPP_CheckAssisData fail");
                TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckAssisData_ENUM, LNAS_LPP_CheckOtdoaNeighbourCellFail);
                return ulRslt;
            }
        }
        else if ( NAS_LPP_SLCT ==pstProvideAssitDataR9->stOTDOAProvideAssistanceData.bitOpOtdoaReferenceCellInfo )
        {
            ulRslt = NAS_LPP_CheckOtdoaNeighbourCell(&pstProvideAssitDataR9->stOTDOAProvideAssistanceData.stOtdoaNeighbourCellInfo,
                                                     NAS_LPP_GetRefEarfcnFromOtdoaAssis(&pstProvideAssitDataR9->stOTDOAProvideAssistanceData.stOtdoaRefCellInfo) );
            if (NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
            {
                NAS_LPP_ERR_LOG("NAS_LPP_CheckAssisData fail1");
                TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckAssisData_ENUM, LNAS_LPP_CheckOtdoaNeighbourCellFail1);
                return ulRslt;
            }
        }
        else
        {
        }
    }

    return NAS_LPP_MSG_VERIFY_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_CheckAssisDataAfterSave
 Description     :  在存储完之后检查辅助数据
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-2  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_CheckOtdoaAssisDataAfterSave( VOS_VOID )
{
    NAS_LPP_OTDOA_ASSIST_CFG_STRU           *pstOtdoaAssisCfg;
    NAS_LPP_SERVING_CELL_STRU               *pstServingCell;
    LPP_LRRC_OTDOA_NEIGHBOUR_FREQ_INFO_STRU *pstNeighborFreqInfo;
    VOS_UINT32 ulLoop = 0,ulLoop1 = 0;
    VOS_UINT32                               ulAssistDataCellNum = 0;

    pstOtdoaAssisCfg = NAS_LPP_GetOtdoaAssisCfg();
    pstServingCell   = NAS_LPP_GetServingCell();

    NAS_LPP_ERR_LOG("NAS_LPP_CheckOtdoaAssisDataAfterSave enter");
    TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckOtdoaAssisDataAfterSave_ENUM, LNAS_LPP_CheckOtdoaAssisDataAfterSaveEnter);

    /*1、至少要2个小区:ref 小区和neighbor小区都要存在，
       2、ref + neighbor里要包含primary cell
       3、neighbor cell的频点个数不要超过3个*/
    /*36.355 6.5.11
    The location server should include at least one cell for which the SFN can be obtained by the target device,
    e.g. the serving cell, in the assistance data, either as the assistance data reference cell or in the neighbour cell list.
    Otherwise the target device will be unable to perform the OTDOA measurement and the positioning operation will fail.*/
    if ( (LPP_LRRC_INFO_FLAG_VALID != pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag)
       ||(LPP_LRRC_INFO_FLAG_VALID != pstOtdoaAssisCfg->ucOtdoaNeighbourCellInfoFlag) )
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckOtdoaAssisDataAfterSave: ucOtdoaReferenceCellInfoFlag or ucOtdoaNeighbourCellInfoFlag inValid");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckOtdoaAssisDataAfterSave_ENUM, LNAS_LPP_RefCellOrNeighbourCellInValid);
        return NAS_LPP_MSG_VERIFY_FAIL;
    }

    /* 辅助数据中的小区个数统计，此处是参考小区个数 */
    ulAssistDataCellNum += 1;
    if ( (pstServingCell->usPhyCellId == pstOtdoaAssisCfg->stOtdoaReferenceCellInfo.usPhyCellId)
       &&(pstServingCell->ulEarfcn == pstOtdoaAssisCfg->stOtdoaReferenceCellInfo.ulEarfcn) )
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckOtdoaAssisDataAfterSave: Servie Cell Not in Reference Cell");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckOtdoaAssisDataAfterSave_ENUM, LNAS_LPP_ServiceCellNotRefCell);
        return NAS_LPP_MSG_VERIFY_SUCC;
    }

    for ( ulLoop = 0 ; ulLoop < pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.ulFreqInfoNum; ulLoop++ )
    {
        pstNeighborFreqInfo = &pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop];
        for ( ulLoop1 = 0 ; ulLoop1 < pstNeighborFreqInfo->ulCellNum; ulLoop1++ )
        {
            if ( (pstServingCell->usPhyCellId == pstNeighborFreqInfo->stOtdoaNeighbourCellInfoList[ulLoop1].usPhyCellId)
               &&(pstServingCell->ulEarfcn == pstNeighborFreqInfo->ulEarfcn) )
            {
                break;
            }
        }

        /* 如果这个频点中找到*/
        if (ulLoop1 < pstNeighborFreqInfo->ulCellNum)
        {
            break;
        }
    }

    /* 如果没找到*/
    if (ulLoop >= pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.ulFreqInfoNum)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckOtdoaAssisDataAfterSave: Servie Cell Not in Reference Cell1");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckOtdoaAssisDataAfterSave_ENUM, LNAS_LPP_ServiceCellNotRefCell1);
        return NAS_LPP_MSG_VERIFY_FAIL;
    }
    /* 统计辅助数据小区个数 */
    for ( ulLoop = 0 ; ulLoop < pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.ulFreqInfoNum; ulLoop++ )
    {
        pstNeighborFreqInfo  = &pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop];
        ulAssistDataCellNum += pstNeighborFreqInfo->ulCellNum;
    }
    if (ulAssistDataCellNum < NAS_LPP_OTDOA_CELL_MIN_NUM)
    {
        return NAS_LPP_MSG_VERIFY_FAIL;
    }

    return NAS_LPP_MSG_VERIFY_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_CheckReqLocationInfo
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-12  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_CheckReqLocationInfo( LPP_MESSAGE_REQUEST_LOCATION_INFO_STRU *pstRequestLocationInformation )
{
    LPP_REQ_LOCATION_INFO_R9_IES_STRU *pstReqLocationInfoR9;
    VOS_UINT32 ulRslt = NAS_LPP_MSG_VERIFY_SUCC;

    pstReqLocationInfoR9 = &pstRequestLocationInformation->u.stC1.u.stReqLocationInfoR9;
    NAS_LPP_INFO_LOG("NAS_LPP_CheckReqLocationInfo");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_CheckReqLocationInfo_ENUM, LNAS_LPP_CheckReqLocationInfoEnter);

    /*校验ECID下行asn相关是否正确*/
    ulRslt = NAS_LPP_CheckEcidDownLinkMsg(pstReqLocationInfoR9);
    if(NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckReqLocationInfo: ECID CHECK ERROR");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckReqLocationInfo_ENUM, LNAS_LPP_CheckReqLocationInfoEcidCheckError);
        return ulRslt;
    }

    /*校验otdoa下行asn相关是否正确*/
    ulRslt = NAS_LPP_CheckOtdoaDownLinkMsg(pstReqLocationInfoR9);
    if(NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckReqLocationInfo: otdoa CHECK ERROR");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckReqLocationInfo_ENUM, LNAS_LPP_CheckReqLocationInfoOtdoaCheckError);
        return ulRslt;
    }

    /*校验gnss下行asn相关是否正确*/
    ulRslt = NAS_LPP_CheckGnssDownLinkMsg(pstReqLocationInfoR9);
    if(NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
    {
        return ulRslt;
    }
    return NAS_LPP_MSG_VERIFY_SUCC;
}

/*****************************************************************************
 Function Name  : NAS_LPP_CheckDownLinkMsg
 Description    : 校验下行空口消息
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-22  新开发
*****************************************************************************/
VOS_UINT32  NAS_LPP_CheckDownLinkMsg(LPP_MESSAGE_STRU *pstLppMsg)
{
    VOS_UINT32              ulRslt = NAS_LPP_MSG_VERIFY_SUCC;
    VOS_UINT32              ulMsgType;

    /*消息头的检查*/
    /*三种上报方式的检查*/
    /*如果是条件触发上报，那么一定是ECID的定位技术，如果出现其他的定位计数，则认为是错误*/
    NAS_LPP_NORM_LOG("NAS_LPP_CheckDownLinkMsg is entered!");
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_CheckDownLinkMsg_ENUM, LNAS_LPP_CheckDownLinkMsgEnterType, pstLppMsg->stLppMessageBody.u.stC1.ulChoice);

    /*校验公共的下行asn是否正确*/
    ulRslt = NAS_LPP_CheckCommomDownLinkMsg(pstLppMsg);
    if(NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_CheckDownLinkMsg: COMMON CHECK FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckDownLinkMsg_ENUM, LNAS_LPP_CheckDownLinkMsgCommonCheckFail);
        return ulRslt;
    }

    /* 如果后面没有msg body，直接退出 */
    if ( NAS_LPP_SLCT != pstLppMsg->bitOpLppMessageBody)
    {
        return ulRslt;
    }

    /*后面分别检查request capability/request location information/assistant data/down abort/down error*/
    ulMsgType = pstLppMsg->stLppMessageBody.u.stC1.ulChoice;
    switch ( ulMsgType )
    {
        case LPP_SUPPORT_MESSAGE_BODY_REQUEST_CAPABILITIES_CHOSEN :
            /*无需检查*/
            break;
        case LPP_SUPPORT_MESSAGE_BODY_PROVIDE_ASSISTANCE_DATA_CHOSEN :
            ulRslt = NAS_LPP_CheckAssisData(&pstLppMsg->stLppMessageBody.u.stC1.u.stProvideAssistanceData);
            /*otdoa的assist data在transaction结束时检查*/
            break;
        case LPP_SUPPORT_MESSAGE_BODY_REQUEST_LOCATION_INFO_CHOSEN :
            ulRslt = NAS_LPP_CheckReqLocationInfo(&pstLppMsg->stLppMessageBody.u.stC1.u.stRequestLocationInformation);
            break;
        case LPP_SUPPORT_MESSAGE_BODY_ABORT_CHOSEN :
            /*无需检查*/
            break;
        case LPP_SUPPORT_MESSAGE_BODY_ERROR_CHOSEN :
            /*无需检查*/
            break;
        default:
            break;
    }

    return ulRslt;
}

/*****************************************************************************
 Function Name  : NAS_LPP_RcvAckTransNotEndHandle
 Description    : 收到ack的消息，但是对应transaction还没有结束处理,需要根据
                  当前transaction的主状态子状态去确定一下步动作
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_RcvAckTransInLocationProvideProcess
(
    NAS_LPP_REPORT_LOCATION_TYPE_ENUM_UINT8 enLocationReportType,
    VOS_UINT8                               ucTransIndx,
    VOS_UINT8                               ucSessionIndex,
    VOS_UINT8                               ucSessionTransIndx
)
{
    /*这里多个分支可以合并，暂时保留现有逻辑，因为针对没有上报方式还有不同的处理*/
    NAS_LPP_INFO_LOG("NAS_LPP_RcvAckTransInLocationProvideProcess enter!");
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_RcvAckTransInLocationProvideProcess_ENUM, LNAS_LPP_enLocationReportType, enLocationReportType);

    switch(enLocationReportType)
    {
        case NAS_LPP_REPORT_LOCATION_TYPE_ONCE:
            /*如果是只上报一次的场景，那么进入到这个分支一定是异常，
              因为provideLocationInformation已经将endtransactionFlag置成true了
            */
            NAS_LPP_ERR_LOG("NAS_LPP_RcvAckTransInLocationProvideProcess: Report ONCE abnormal!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvAckTransInLocationProvideProcess_ENUM, LNAS_LPP_RcvAckTransInLocationProvideProcessReportOnceAbnormal);
            break;

        case NAS_LPP_REPORT_LOCATION_TYPE_PERIOD:
            /*
            周期性触发，如果进入了这个分支，则说明当前上报次数一定没有达到上限, 这里的
            处理只需要将该transaction的状态转成等测量IND即可(同时停止重传定时器)，周期性定时器
            超时时候自然会组包provideLocation发给网侧，同时启动周期性定时器，直到次数达到上限
            */
            NAS_LPP_ChangeTransFsmState(ucSessionIndex, ucSessionTransIndx, LPP_MS_LOCATION, LPP_SS_WAIT_MEAS_IND);
            break;

        case NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER:
           /*
            条件触发，如果进入了这个分支，则说明当前duration上报定时器没有超时，处理跟上面类似，
            将该transaction的状态转成IDLE即可，duration定时器超时，自然会组包provide发给网侧，
            直到duration到期
           */
           NAS_LPP_ChangeTransFsmState(ucSessionIndex, ucSessionTransIndx, LPP_MS_LOCATION, LPP_SS_WAIT_MEAS_IND);
           break;

        default:
            NAS_LPP_ERR_LOG("NAS_LPP_RcvAckTransInLocationProvideProcess: Report Type Error!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvAckTransInLocationProvideProcess_ENUM, LNAS_LPP_ReportTypeError);
            break;
    }
}

/*****************************************************************************
 Function Name  : NAS_LPP_RcvAckTransNotEndHandle
 Description    : 收到ack的消息，但是对应transaction还没有结束处理,需要根据
                  当前transaction的主状态子状态去确定一下步动作
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_RcvAckTransNotEndHandle
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucTransIndx,
    VOS_UINT8                           ucSessionTransIndx
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransEntity          = NAS_LPP_NULL_PTR;
    NAS_LPP_REPORT_LOCATION_TYPE_ENUM_UINT8     enReportLocationType    = 0;



    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvAckTransNotEndHandle: Don't find Transaction!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvAckTransNotEndHandle_ENUM, LNAS_LPP_DontFindTransaction);

        return;
    }

    TLPS_PRINT2LAYER_INFO1(NAS_LPP_RcvAckTransNotEndHandle_ENUM, LNAS_LPP_enLastUpMsgId, pstTransEntity->enLastUpMsgId);

    switch(pstTransEntity->enLastUpMsgId)
    {
        case    NAS_LPP_AIR_MSG_PROVIDE_CAP:
                /*
                  如果上一动作是提供能力消息给网侧，按理此时transaction应该结束，
                  但是如果还是进入了这个分支，说明transaction实体中没有将transaction
                  标记没有结束，出现异常，记录一下，作为异常处理
                */
                NAS_LPP_ERR_LOG("NAS_LPP_RcvAckTransNotEndHandle: CapProvdie Process abnormal!");
                break;

        case    NAS_LPP_AIR_MSG_REQUEST_ASSIST_DATA:
                /*下一迭代添加，收到辅助信息请求的ACK，停重传定时器，转到等网络侧辅助数据等操作*/
                NAS_LPP_ChangeTransFsmState(ucSessionIndx, ucSessionTransIndx, LPP_MS_ASSISTDATA, LPP_SS_ASSISTDATA_WAIT_CN_CNF);
                break;

        case    NAS_LPP_AIR_MSG_PROVIDE_LOCATION_INFO:
                /*如果上一动作是提供位置信息给网侧，那么需要根据当前上报方式是周期性还是条件触发，还是
                仅仅上报一次*/
                /*获取上报位置信息类型*/
                enReportLocationType = NAS_LPP_GetSessionEntityReportType(ucSessionIndx,ucSessionTransIndx);
                NAS_LPP_RcvAckTransInLocationProvideProcess(enReportLocationType,
                                                            ucTransIndx,
                                                            ucSessionIndx,
                                                            ucTransIndx);
                break;

        case    NAS_LPP_AIR_MSG_UP_ERR:
                /*现阶段不做ERR消息的ACK机制，暂时预留*/
                break;

        case    NAS_LPP_AIR_MSG_UP_ABORT:
                /*Abort*/
                NAS_LPP_ERR_LOG("NAS_LPP_RcvAckTransNotEndHandle: Abort Process abnormal!");
                break;

        default:
            break;
    }
}

/*****************************************************************************
 Function Name  : NAS_LPP_NwMsgProcess
 Description    : NAS_LPP_NwMsgProcess
 Input          : pstLppMsg     下行LPP消息
                  ulSessionId   下行LPP流程所在session的ID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_NwMsgWithAckIeHandle
(
    NAS_LPP_MSG_HEAD_STRU              *pstMsgHead,
    VOS_UINT32                          ulSessionId
)
{
    LPP_UPLINK_MSG_BUF_STRU                    *pstUplinkMsgBuf         = NAS_LPP_NULL_PTR;
    VOS_UINT8                                   ucSessionTransIndx      = 0;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransEntity          = NAS_LPP_NULL_PTR;
    VOS_UINT8                                   ucSessionIndx           = 0;
    VOS_UINT8                                   ucTransIndx             = 0;

    NAS_LPP_NORM_LOG("NAS_LPP_NwMsgWithAckIeHandle enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_NwMsgWithAckIeHandle_ENUM, LNAS_LPP_Func_Enter);

    /*查找上行缓存buffer*/
    pstUplinkMsgBuf = NAS_LPP_FindUpLinkBuffer(
                                    pstMsgHead->stAcknowledgement.stAckIndicator.ucSequenceNumber,
                                    ulSessionId);
    if(NAS_LPP_NULL_PTR == pstUplinkMsgBuf)
    {
        /*加保护如果等于空，则上行缓存中没有找到对应消息缓存*/
        NAS_LPP_ERR_LOG("NAS_LPP_NwMsgWithAckIeHandle: Don't find UpLink buffer Msg!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_NwMsgWithAckIeHandle_ENUM, LNAS_LPP_DontFindUplinkBufferMsg);

        return;
    }

    /*通过buffer句柄中的identity找到对应transaction实体*/
    ucSessionIndx = NAS_LPP_SearchSessionIndx(pstUplinkMsgBuf->stLppMsgIdentity.ulSessionId);
    NAS_LPP_SearchTransEntityIndx(ucSessionIndx,
                                  &(pstUplinkMsgBuf->stLppMsgIdentity.stTransId),
                                  &ucTransIndx,
                                  &ucSessionTransIndx);

    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_NwMsgWithAckIeHandle: Don't find Transaction!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_NwMsgWithAckIeHandle_ENUM, LNAS_LPP_DontFindTransaction);
        return;
    }

    /*
      找到了transaction实体，如果标记了该transaction结束，
      则释放transaction的资源，并且clear相关的操作
    */
    if(NAS_LPP_TRANS_END == pstTransEntity->ucTransEndFlag)
    {
        /*当对应的transaction是位置提供，而且是最后一条消息，而且当前session没有其他的transaction正在running location， 则需要清session*/
        if( PS_FALSE == NAS_LPP_IsThereOtherTransactionRunningInSession(ucSessionIndx,&(pstUplinkMsgBuf->stLppMsgIdentity.stTransId)) )
        {
            NAS_LPP_WARN_LOG("NAS_LPP_NwMsgWithAckIeHandle:No running transaction, Release this session!");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_NwMsgWithAckIeHandle_ENUM, LNAS_LPP_NoRunningTransReleaseSession);
            NAS_LPP_ReleaseSessionEntityByIndex(ucSessionIndx);
        }
        else
        {
            NAS_LPP_WARN_LOG("NAS_LPP_NwMsgWithAckIeHandle: Have other transaction, Just release this Transaction!");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_NwMsgWithAckIeHandle_ENUM, LNAS_LPP_HaveOtherTransJustReleaseThisTrans);
            NAS_LPP_ReleaseTransEntity(ucSessionIndx, ucSessionTransIndx);
        }
    }
    else
    {
        /*transaction还没有结束*/
        /* 如果重传多次上行消息后收到ACK，则需要清除重传计数，在这里对所有上行消息的ACK清除重传计数 */
        pstTransEntity->ucRetranNum = 0;
        NAS_LPP_WARN_LOG("NAS_LPP_NwMsgWithAckIeHandle: Transaction don't end!");
        TLPS_PRINT2LAYER_WARNING(NAS_LPP_NwMsgWithAckIeHandle_ENUM, LNAS_LPP_TransDontEnd);
        NAS_LPP_RcvAckTransNotEndHandle(ucSessionIndx, ucTransIndx, ucSessionTransIndx);
        NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuf);
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_EncodeAckMsg
 Description    : 编码上行ack消息
 Input          : pstLppMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_UINT8 NAS_LPP_EncodeAckMsgWithMsgIndentiy
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppHead,
    VOS_UINT32                         *pulLppMsgLen,
    VOS_UINT8                          *pucEncodeOutMsg,
    NAS_LPP_MSG_IDENTITY_STRU          *pstLppMsgIdentity,
    VOS_UINT32                          ulSessionId
)
{
    NAS_LPP_MSG_HEAD_STRU  *pstUplinkAckMsg = NAS_LPP_NULL_PTR;
    VOS_UINT16              usRslt          = 0;
    VOS_UINT16              usBitPos        = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_EncodeAckMsgWithMsgIndentiy enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_EncodeAckMsgWithMsgIndentiy_ENUM, LNAS_LPP_Func_Enter);


    pstUplinkAckMsg = NAS_LPP_MEM_ALLOC(sizeof(NAS_LPP_MSG_HEAD_STRU));
    if(NAS_LPP_NULL_PTR == pstUplinkAckMsg)
    {
        return NAS_LPP_FAILURE;
    }
    NAS_LPP_MEM_SET_S(pstUplinkAckMsg,sizeof(NAS_LPP_MSG_HEAD_STRU), 0, sizeof(NAS_LPP_MSG_HEAD_STRU));

    /*参数准备*/
    pstUplinkAckMsg->bitOpAcknowledgement = NAS_LPP_SLCT;
    pstUplinkAckMsg->stAcknowledgement.bAckRequested = PS_FALSE;
    pstUplinkAckMsg->stAcknowledgement.bitOpAckIndicator = NAS_LPP_SLCT;
    pstUplinkAckMsg->stAcknowledgement.stAckIndicator.ucSequenceNumber =
                                    pstLppHead->stSequenceNumber.ucSequenceNumber;
    pstUplinkAckMsg->bEndTransaction = PS_FALSE;
    /*
    尽管transactionId在ACK消息中按照协议要求不需要带，但是参考了罗德的trace，
    也将transaction带给网侧了，所以目前实现也是将其带给网侧
    */
    pstUplinkAckMsg->bitOpLppTransactionId = NAS_LPP_SLCT;
    pstUplinkAckMsg->stTransactionId.enInitiator =
                                    pstLppHead->stTransactionId.enInitiator;
    pstUplinkAckMsg->stTransactionId.ucTransactionNumber =
                                    pstLppHead->stTransactionId.ucTransactionNumber;

    /*开始编码*/
    usRslt = NAS_LPP_EncodeMessage((LPP_MESSAGE_STRU*)pstUplinkAckMsg,
                                   &usBitPos,
                                    pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_EncodeAckMsgWithMsgIndentiy: Encode Ack msg Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeAckMsgWithMsgIndentiy_ENUM, LNAS_LPP_ENCODE_LPP_MSG_FAIL);
        NAS_LPP_MEM_FREE(pstUplinkAckMsg);
        return NAS_LPP_FAILURE;
    }
    *pulLppMsgLen = usBitPos/8;

    /*填充上行消息身份识别信息*/
    pstLppMsgIdentity->ulSessionId                      = ulSessionId;
    pstLppMsgIdentity->stTransId.enInitiator            =
                                pstUplinkAckMsg->stTransactionId.enInitiator;
    pstLppMsgIdentity->stTransId.ucTransactionNumber    =
                                pstUplinkAckMsg->stTransactionId.ucTransactionNumber;
    pstLppMsgIdentity->enUplinkMsgType                  =
                                NAS_LPP_UPLINK_MSG_TYPE_ACK;

    /*释放动态分配的内存*/
    NAS_LPP_MEM_FREE(pstUplinkAckMsg);

    /*编码成功*/
    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
 Function Name  : NAS_LPP_SaveUpMsgBufferIndex
 Description    : 存储缓存buffer的索引值
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-9-2  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_SaveUpMsgBufferIndex(VOS_UINT8 ucUplinkBuffIndx)
{
    NAS_LPP_UP_MSG_BUFF_POOL_STRU  *pstUpMsgBuffPool    = NAS_LPP_NULL_PTR;
    VOS_UINT32                      ulLoop              = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_SaveUpMsgBufferIndex Enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveUpMsgBufferIndex_ENUM, LNAS_LPP_Func_Enter);

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();
    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        /*如果当前index没有被占用，则将index的值存储到该位置*/
        if(PS_FALSE == pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUsedFlag)
        {
            pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUsedFlag        = PS_TRUE;
            pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUpLinkBuffIndex = ucUplinkBuffIndx;
            break;
        }
    }

    NAS_LPP_OmUpMsgBuffMallocSuccInd(ucUplinkBuffIndx, pstUpMsgBuffPool->astUpmsgSeq,pstUpMsgBuffPool->ulBitMap);
}

/*lint -e661*/
/*lint -e662*/
/*****************************************************************************
 Function Name  : NAS_LPP_PushUplinkMsgToBuff
 Description    : 将上行空口消息放到上行缓存buffer
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_UINT16 NAS_LPP_PushUplinkMsgToBuff
(
    VOS_UINT32                          ulDataReqSize,
    LPP_LMM_DATA_REQ_STRU              *pstLppDataReq,
    NAS_LPP_MSG_IDENTITY_STRU          *pstLppMsgIdentity
)
{
    LPP_UPLINK_MSG_BUF_STRU            *pstUplinkMsgBuf     = NAS_LPP_NULL_PTR;
    VOS_UINT8                           ucUpLinkBuffIndx    = PS_NULL_UINT8;
    VOS_UINT8                           ucLoop              = 0;
    VOS_BOOL                            bHaveSameProLocFlag = 0;
    NAS_LPP_UP_MSG_BUFF_POOL_STRU      *pstUpMsgBufPool = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_PushUplinkMsgToBuff enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_PushUplinkMsgToBuff_ENUM, LNAS_LPP_Func_Enter);

    /*
      在上行buffer缓存的消息发送完成前，如果又有新的provideLocation消息发送给网络侧，则用新的覆盖旧的，
      注意:注意不要新增
    */
    pstUpMsgBufPool = NAS_LPP_GetLppUpMsgBuffPool();

    if(PS_TRUE == pstLppMsgIdentity->bIsProvideLocFalg)
    {
        for(ucLoop = 0; ucLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ucLoop++)
        {
            /*如果已经保存的上行的消息，如果Session，transaction相同，而且是ProvideLocation消息，而且还没有发送成功，则认为上行缓存已经有了
              一条provideLocation消息待发送，此时，需要用新的覆盖旧的消息
            */
            if((pstUpMsgBufPool->astLppUpMsg[ucLoop].stLppMsgIdentity.ulSessionId == pstLppMsgIdentity->ulSessionId)
               && (pstUpMsgBufPool->astLppUpMsg[ucLoop].stLppMsgIdentity.stTransId.ucTransactionNumber == pstLppMsgIdentity->stTransId.ucTransactionNumber)
               && (pstUpMsgBufPool->astLppUpMsg[ucLoop].stLppMsgIdentity.stTransId.enInitiator == pstLppMsgIdentity->stTransId.enInitiator)
               && (PS_TRUE == pstUpMsgBufPool->astLppUpMsg[ucLoop].stLppMsgIdentity.bIsProvideLocFalg)
               && (NAS_LPP_UPLINK_MSG_TYPE_PROCESS == pstUpMsgBufPool->astLppUpMsg[ucLoop].stLppMsgIdentity.enUplinkMsgType)
               && (PS_FALSE == pstUpMsgBufPool->astLppUpMsg[ucLoop].bSendBufFlag))
            {
                NAS_LPP_WARN_LOG("NAS_LPP_PushUplinkMsgToBuff: Use New ProvideLocation Msg!");
                TLPS_PRINT2LAYER_WARNING(NAS_LPP_PushUplinkMsgToBuff_ENUM, LNAS_LPP_UseNewProvideLocationMsg);

                bHaveSameProLocFlag = PS_TRUE;
                ucUpLinkBuffIndx    = ucLoop;
                break;
            }
        }
    }

    if(PS_FALSE == bHaveSameProLocFlag)
    {
        /*没有相同的缓存的消息，申请新的缓存buffer*/
        pstUplinkMsgBuf = NAS_LPP_MallocUpMsgBuffer(&ucUpLinkBuffIndx);
        if(NAS_LPP_NULL_PTR == pstUplinkMsgBuf)
        {
            NAS_LPP_ERR_LOG("NAS_LPP_PushUplinkMsgToBuff: Can't alloc UpMsg buffer!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_PushUplinkMsgToBuff_ENUM, LNAS_LPP_CanntAllocUpMsgBuffer);
            return  NAS_LPP_FAILURE;
        }
    }
    else
    {
        /*有相同的缓存消息，直接覆盖之*/
        pstUplinkMsgBuf = &(pstUpMsgBufPool->astLppUpMsg[ucUpLinkBuffIndx]);
    }

    /*保存上行缓存的索引信息*/
    NAS_LPP_SaveUpMsgBufferIndex(ucUpLinkBuffIndx);

    NAS_LPP_MEM_CPY_S(&(pstUplinkMsgBuf->stLppMsgIdentity),
                    sizeof(NAS_LPP_MSG_IDENTITY_STRU),
                    pstLppMsgIdentity,
                    sizeof(NAS_LPP_MSG_IDENTITY_STRU));
    pstUplinkMsgBuf->bSendBufFlag = PS_FALSE;
    NAS_LPP_MEM_CPY_S(&(pstUplinkMsgBuf->u.stLppDataReq),
                    NAS_LPP_MAX_BUFF_MSG_LEN,
                    pstLppDataReq,
                    ulDataReqSize);

    return      NAS_LPP_SUCCESS;
}
/*lint +e662*/
/*lint +e661*/


VOS_UINT32  NAS_LPP_AllocEmmLppOpId( VOS_VOID )
{
    g_ulEmmLppOpId++;
    if(g_ulEmmLppOpId  == NAS_LMM_LPP_OPID_NOT_VAILID)
    {
        g_ulEmmLppOpId = 0;
    }
    return  (g_ulEmmLppOpId);
}

/*****************************************************************************
 Function Name  : NAS_LPP_FillWithLppDataReqMsg
 Description    : 填充发送给LMM的DATA REQ消息
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_FillWithLppDataReqMsg
(
    VOS_UINT32                          ulLppMsgLen,
    VOS_UINT8                          *pucEncodeOutMsg,
    LPP_LMM_DATA_REQ_STRU              *pstLppDataReq,
    VOS_UINT32                          ulSessionId
)
{
    NAS_LPP_WARN_LOG("NAS_LPP_FillWithLppDataReqMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_FillWithLppDataReqMsg_ENUM, LNAS_LPP_Func_Enter);

    /*填写空口消息头长度*/
    pstLppDataReq->ulSessionId              = ulSessionId;
    pstLppDataReq->ulOpId                   = NAS_LPP_AllocEmmLppOpId();

    pstLppDataReq->stLppMsg.ulLppMsgSize    = ulLppMsgLen;
    NAS_LPP_MEM_CPY_S(pstLppDataReq->stLppMsg.aucLppMsg,
                    ulLppMsgLen,
                    pucEncodeOutMsg,
                    ulLppMsgLen);

    /*填写消息头*/
    NAS_LPP_WRITE_EMM_MSG_HEAD(pstLppDataReq, ID_LPP_LMM_DATA_REQ);

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_LppLmmEstReq
 Description    : LPP给LMM发起建链请求消息
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_LppLmmEstReq( VOS_VOID )
{
    LPP_LMM_EST_REQ_STRU               *pstEstReqMsg;

    NAS_LPP_NORM_LOG("NAS_LPP_LppLmmEstReq enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_LppLmmEstReq_ENUM, LNAS_LPP_Func_Enter);

    /* 申请内存  */
    pstEstReqMsg = (VOS_VOID*)NAS_LPP_ALLOC_MSG(sizeof(LPP_LMM_EST_REQ_STRU));
    if( NAS_LPP_NULL_PTR == pstEstReqMsg )
    {
        return;
    }

    NAS_LPP_MEM_SET_MSG(pstEstReqMsg, sizeof(LPP_LMM_EST_REQ_STRU), 0, sizeof(LPP_LMM_EST_REQ_STRU));

    /*填写消息头*/
    NAS_LPP_WRITE_EMM_MSG_HEAD(pstEstReqMsg, ID_LPP_LMM_EST_REQ);

    /*调用消息发送函数 */
    NAS_LPP_SND_MSG(pstEstReqMsg);

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_LppLmmDataReq
 Description    : LPP给LMM发送直传消息
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_LppLmmDataReq
(
    VOS_UINT32                          ulSessionId,
    VOS_UINT32                          ulLppMsgLen,
    VOS_UINT8                          *pucEncodeOutMsg,
    VOS_UINT32                          ulOpId
)
{
    VOS_UINT32                          ulTmpLength     = 0;
    LPP_LMM_DATA_REQ_STRU              *pstLppDataReq   = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_LppLmmDataReq enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_Func_Enter);


    /*根据空口消息的长度分配空间*/
    if( 0 == ulLppMsgLen)
    {
        NAS_LPP_WARN_LOG("NAS_LPP_LppLmmDataReq: WARNING: Msg Length is zero");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_MallocMemFail);
        return ;
    }
    else if(ulLppMsgLen > NAS_LPP_MIN_SND_MSG_LEN)
    {
        ulTmpLength = ulLppMsgLen - NAS_LPP_MIN_SND_MSG_LEN ;
        pstLppDataReq = (VOS_VOID*)NAS_LPP_ALLOC_MSG(sizeof(LPP_LMM_DATA_REQ_STRU) + ulTmpLength);
    }
    else/*如果长度小于NAS_LPP_MIN_SND_MSG_LEN，分配的空间等于NAS_LPP_MIN_SND_MSG_LEN*/
    {
        pstLppDataReq = (VOS_VOID*)NAS_LPP_ALLOC_MSG(sizeof(LPP_LMM_DATA_REQ_STRU));
    }

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstLppDataReq)
    {
        /*打印异常信息*/
        NAS_LPP_ERR_LOG("NAS_LPP_LppLmmDataReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_MallocMemFail);
        return ;
    }

    /*填写空口消息头长度*/
    pstLppDataReq->stLppMsg.ulLppMsgSize = ulLppMsgLen;

    /*将空口消息存放到ID_LPP_LMM_DATA_REQ结构中*/
    /*lint -e669*/
    NAS_LPP_MEM_CPY_S(pstLppDataReq->stLppMsg.aucLppMsg,ulLppMsgLen, pucEncodeOutMsg, ulLppMsgLen);
    /*lint +e669*/

    /*填写SessionId*/
    pstLppDataReq->ulSessionId = ulSessionId;

    /*填写OpId*/
    pstLppDataReq->ulOpId = ulOpId;

    /*填写消息头*/
    NAS_LPP_WRITE_EMM_MSG_HEAD(pstLppDataReq, ID_LPP_LMM_DATA_REQ);

    /*调用消息发送函数 */
    NAS_LPP_SND_MSG(pstLppDataReq);

}

/*****************************************************************************
 Function Name  : NAS_LPP_SendUplinkMsg
 Description    : 发送上行的空口消息
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_SendUplinkMsg
(
    VOS_UINT32                          ulSessionId,
    VOS_UINT32                          ulLppMsgLen,
    VOS_UINT8                          *pucEncodeOutMsg,
    NAS_LPP_MSG_IDENTITY_STRU          *pstLppMsgIdentity
)
{
    LPP_LMM_DATA_REQ_STRU              *pstLppDataReq   = NAS_LPP_NULL_PTR;
    VOS_UINT32                          ulDataReqSize   = 0;
    VOS_UINT16                          usRslt          = 0;

    NAS_LPP_NORM_LOG("NAS_LPP_SendUplinkMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SendUplinkMsg_ENUM, LNAS_LPP_Func_Enter);

    ulDataReqSize = sizeof(LPP_LMM_DATA_REQ_STRU) + ulLppMsgLen - 4;
    pstLppDataReq = (LPP_LMM_DATA_REQ_STRU *)NAS_LPP_MEM_ALLOC(ulDataReqSize);
    if (VOS_NULL_PTR == pstLppDataReq)
    {
          return ;
    }

    NAS_LPP_MEM_SET_S(pstLppDataReq, ulDataReqSize,0, ulDataReqSize);
    pstLppDataReq->ulLength = ulDataReqSize - VOS_MSG_HEAD_LENGTH;

    /*组装给LMM发送的DATA REQ*/
    NAS_LPP_FillWithLppDataReqMsg(ulLppMsgLen, pucEncodeOutMsg, pstLppDataReq, ulSessionId);

    /*在发送上行消息之前无论当前连接状态是什么，首先将上行消息缓存*/
    usRslt = NAS_LPP_PushUplinkMsgToBuff(ulDataReqSize, pstLppDataReq, pstLppMsgIdentity);
    if (NAS_LPP_SUCCESS != usRslt)
    {
        NAS_LPP_MEM_FREE(pstLppDataReq);
        return ;
    }

    /*根据当前的链路状态，决定是发建链还是发直传*/
    switch(NAS_LPP_GetLppConnStatus())
    {
        case NAS_LPP_CONN_STATUS_IDLE:
            NAS_LPP_NORM_LOG("NAS_LPP_SendUplinkMsg: IDLE, Start Est!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_ConnStatusIdle);

            /*Idle态，发起建链*/
            NAS_LPP_LppLmmEstReq();

            /*传输计数加1*/
            NAS_LPP_TransLppMsgAddCnt();

            /*发起建链之后，将链路置成ESTING*/
            NAS_LPP_SetLppConnStatus(NAS_LPP_CONN_STATUS_ESTING);

            /*启动建链定时器*/
            NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                               NAS_LPP_TIMER_INVAILD_PARA,
                               TI_NAS_LPP_WAIT_EST_CNF);
            break;

        case NAS_LPP_CONN_STATUS_ESTING:
            /*建链过程中，仅仅将上行消息保存到buffer中*/
            NAS_LPP_NORM_LOG("NAS_LPP_SendUplinkMsg: ESTING!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_ConnStatusEsting);
            break;

        case NAS_LPP_CONN_STATUS_CONNECT:
            NAS_LPP_NORM_LOG("NAS_LPP_SendUplinkMsg: CONNECT, DataReq!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_ConnStatusConnect);

            /*传输计数加1*/
            NAS_LPP_TransLppMsgAddCnt();

            /*连接态，直接发送直传消息*/
            NAS_LPP_LppLmmDataReq(ulSessionId,
                                  ulLppMsgLen,
                                  pucEncodeOutMsg,
                                  pstLppDataReq->ulOpId);
            break;

        default:
            break;
    }

    NAS_LPP_MEM_FREE(pstLppDataReq);

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_ResendUplinkMsg
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ResendUplinkMsg
(
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_ID_STRU               *pstTransId )
{
    LPP_LMM_DATA_REQ_STRU              *pstLppDataReq = NAS_LPP_NULL_PTR;
    VOS_UINT32                          ulDataReqSize = 0;
    LPP_UPLINK_MSG_BUF_STRU            *pstUpMsgBuf = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_ResendUplinkMsg");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_ResendUplinkMsg_ENUM, LNAS_LPP_Func_Enter);

    /*寻找上行消息缓存*/
    pstUpMsgBuf = NAS_LPP_SearchUpMsgBuff(ulSessionId, pstTransId);
    if (NAS_LPP_NULL_PTR == pstUpMsgBuf)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_ResendUplinkMsg: Can't find pstUpMsgBuf");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_ResendUplinkMsg_ENUM, LNAS_LPP_DontFindUplinkBufferMsg);
        return;
    }

    /*重传时需要将SendBuffFlag置成False，原因是如果走到重传，那么上次一定是发送成功了，
    此时sendflag已经置成了true，在重传的时候需要将此flag置成false，等收到data cnf成功
    之后再置成ture，否则，会存在发送不出去的情况*/
    pstUpMsgBuf->bSendBufFlag = PS_FALSE;
    ulDataReqSize = pstUpMsgBuf->u.stLppDataReq.ulLength + VOS_MSG_HEAD_LENGTH;
    pstLppDataReq = (LPP_LMM_DATA_REQ_STRU*)NAS_LPP_ALLOC_MSG(ulDataReqSize);
    if ( NAS_LPP_NULL_PTR == pstLppDataReq )
    {
        NAS_LPP_ERR_LOG("resend up msg alloc fail");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_ResendUplinkMsg_ENUM, LNAS_LPP_MallocMemFail);
        return;
    }

    NAS_LPP_MEM_CPY_S(pstLppDataReq,ulDataReqSize, &pstUpMsgBuf->u.stLppDataReq, ulDataReqSize);

    /*根据当前的链路状态，决定是发建链还是发直传*/
    switch(NAS_LPP_GetLppConnStatus())
    {
        case NAS_LPP_CONN_STATUS_IDLE:
            TLPS_PRINT2LAYER_INFO(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_ConnStatusIdle);
            /*Idle态，发起建链*/
            NAS_LPP_LppLmmEstReq();

            /*建链次数加1*/
            NAS_LPP_TransLppMsgAddCnt();

            /*发起建链之后，将链路置成ESTING*/
            NAS_LPP_SetLppConnStatus(NAS_LPP_CONN_STATUS_ESTING);
            NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                               NAS_LPP_TIMER_INVAILD_PARA,
                               TI_NAS_LPP_WAIT_EST_CNF);
            break;
        case NAS_LPP_CONN_STATUS_ESTING:
            /*建链过程中，仅仅将上行消息保存到buffer中*/
            TLPS_PRINT2LAYER_INFO(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_ConnStatusEsting);
            break;

        case NAS_LPP_CONN_STATUS_CONNECT:
            /*连接态，直接发送直传消息*/
            NAS_LPP_SND_MSG(pstLppDataReq);
            TLPS_PRINT2LAYER_INFO(NAS_LPP_LppLmmDataReq_ENUM, LNAS_LPP_ConnStatusConnect);
            break;

        default:
            break;
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_GNSSCapReq
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.wangensheng      2015-10-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_GNSSCapReq( VOS_VOID )
{
    LPP_MTA_GNSS_CAPABITY_REQ_STRU     *pstLppSendMtaCapReq = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_GNSSCapReq enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_NGSSCapReq_ENUM, LNAS_LPP_Func_Enter);

    /* malloc the msg memory */
    pstLppSendMtaCapReq = (LPP_MTA_GNSS_CAPABITY_REQ_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_MTA_GNSS_CAPABITY_REQ_STRU));
    if (NAS_LPP_NULL_PTR == pstLppSendMtaCapReq )
    {
        return;
    }

    NAS_LPP_MEM_SET_MSG(pstLppSendMtaCapReq, sizeof(LPP_MTA_GNSS_CAPABITY_REQ_STRU), 0, sizeof(LPP_MTA_GNSS_CAPABITY_REQ_STRU));

    /* set the msg data */
    NAS_LPP_WRITE_MTA_MSG_HEAD(pstLppSendMtaCapReq,ID_LPP_MTA_GNSS_CAP_REQ);

    pstLppSendMtaCapReq->stGnssCapReq.bAssistanceDataSupportListReq = PS_TRUE;
    pstLppSendMtaCapReq->stGnssCapReq.bGnssSupportListReq           = PS_TRUE;
    pstLppSendMtaCapReq->stGnssCapReq.blocationVelocityTypesReq     = PS_TRUE;

    /* send msg data */
    NAS_LPP_SND_MSG(pstLppSendMtaCapReq);
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeOtodaCapability
 Description     : 组织otodoa的能力
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-20  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_EncodeOtodaCapability
(
    LPP_PROVIDE_CAPABILITIES_R9_IES_STRU    *pstProvideCapR9Ies,
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElement,
    LRRC_SUPPORT_CAPABILITY_STRU            *pstLrrcCap
)
{
    VOS_UINT32                              ulLoop,ulBandNum = 0,ulExtBandNum = 0;
    VOS_UINT32                              ulTmpIndex ,ulTmpShit, ulTmp;

    NAS_LPP_INFO_LOG("NAS_LPP_ResendUplinkMsg");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_EncodeOtodaCapability_ENUM, LNAS_LPP_Func_Enter);

    if( (NAS_LPP_SLCT == pstTransElement->stCapReq.bitOpOtdoaCapReq)
      &&(VOS_TRUE == pstLrrcCap->bRrcCapbilityFlag)
      &&(LPP_LRRC_INFO_FLAG_VALID == pstLrrcCap->stRrcCapbility.ucOtdoaUeAssistFlag))/*ucOtdoaUeAssistFlag是36.331里ue能力的支持*/
    {
        pstProvideCapR9Ies->bitOpOTDOAProvideCapabilities = NAS_LPP_SLCT;
        pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpOtdoaProvideCapExt = NAS_LPP_SLCT;

        pstProvideCapR9Ies->stOTDOAProvideCapabilities.stOtdoaMode.ucOTDOAMode = 0x01;  /*第0 bit为1，表示支持OTDOA*/
        pstProvideCapR9Ies->stOTDOAProvideCapabilities.stOtdoaMode.ucOTDOAModeLen = 1;

        /*additionalNeighbourCellInfoList
        This field, if present, indicates that the target device supports up to 3×24 OTDOA-NeighbourCellInfoElement in OTDOA NeighbourCellInfoList
        in OTDOA-ProvideAssistanceData without any restriction for the earfcn in each OTDOA-NeighbourCellInfoElement as specified in subclause 6.5.1.2. */
        /*pstProvideCapR9Ies->stOTDOAProvideCapabilities.enAdditionalNeighbourCellInfoListR10 = ;为了处理3*24层的标准小区结构，这个IE可以设置成不存在*/
        if (LPP_LRRC_INFO_FLAG_VALID == pstLrrcCap->stRrcCapbility.ucAddOtdoaNeighbourCellInfoListFlag)
        {
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpAdditionalNeighbourCellInfoListR10 = NAS_LPP_SLCT;
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.enAdditionalNeighbourCellInfoListR10 = LPP_INTER_FREQ_RSTD_MEASUREMENT_R10_SUPPORT;
        }
        else
        {
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpAdditionalNeighbourCellInfoListR10 = NAS_LPP_NO_SLCT;
        }

        for ( ulLoop = 0 ; ulLoop < LPP_MAX_SUPPORTED_BAND_EUTRA_NUM; ulLoop++ )
        {
            ulTmpIndex = ulLoop/32;
            ulTmpShit  = ulLoop%32;
            ulTmp = pstLrrcCap->stRrcCapbility.aulBandInd[ulTmpIndex];
            if ( 0 != (ulTmp & (0x01 << ulTmpShit) ) )
            {
                pstProvideCapR9Ies->stOTDOAProvideCapabilities.stSupportedBandListEutra.astSupportedBandArray[ulBandNum].ulBandEutra = ulLoop+1;
                ulBandNum++;
            }
        }

        for ( ulLoop = LPP_MAX_SUPPORTED_BAND_EUTRA_NUM ; ulLoop < LRRC_LPP_MAX_BAND_IND_NUM; ulLoop++ )
        {
            ulTmpIndex = ulLoop/32;
            ulTmpShit  = ulLoop%32;
            ulTmp = pstLrrcCap->stRrcCapbility.aulBandInd[ulTmpIndex];
            if ( 0 != (ulTmp & (0x01 << ulTmpShit) ) )
            {
                if ( ulExtBandNum >= LPP_MAX_SUPPORTED_BAND_EUTRA_NUM )
                {
                    NAS_LPP_ERR_LOG1("encode capability ,ext band overflow,ulLoop", ulLoop);
                    TLPS_PRINT2LAYER_INFO1(NAS_LPP_EncodeOtodaCapability_ENUM, LNAS_LPP_ExtBandOverflowLoop, ulLoop);
                    return NAS_LPP_FAILURE;
                }
                pstProvideCapR9Ies->stOTDOAProvideCapabilities.stSupportedBandListEutraV9A0.astSupportedBandArray[ulExtBandNum].bitOpBandEutraV9A0 = NAS_LPP_SLCT;
                pstProvideCapR9Ies->stOTDOAProvideCapabilities.stSupportedBandListEutraV9A0.astSupportedBandArray[ulExtBandNum].ulBandEutraV9A0 = ulLoop+1;
                ulExtBandNum++;
            }
        }

        pstProvideCapR9Ies->stOTDOAProvideCapabilities.stSupportedBandListEutra.ulSupportBandNum = ulBandNum;
        if ( 0 != ulBandNum )
        {
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpSupportedBandListEutra = NAS_LPP_SLCT;
        }
        else
        {
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpSupportedBandListEutra = NAS_LPP_NO_SLCT;
        }

        pstProvideCapR9Ies->stOTDOAProvideCapabilities.stSupportedBandListEutraV9A0.ulSupportBandNum = ulExtBandNum;
        if ( 0 != ulExtBandNum )
        {
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpSupportedBandListEutraV9A0  = NAS_LPP_SLCT;
        }
        else
        {
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpSupportedBandListEutraV9A0  = NAS_LPP_NO_SLCT;
        }

        if ( LPP_LRRC_INFO_FLAG_VALID == pstLrrcCap->stRrcCapbility.ucInterFreqRSTDMeasFlag )
        {
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpInterFreqRSTDmeasurementR10 = NAS_LPP_SLCT;
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.enInterFreqRSTDmeasurementR10 = LPP_INTER_FREQ_RSTD_MEASUREMENT_R10_SUPPORT;
        }
        else
        {
            pstProvideCapR9Ies->stOTDOAProvideCapabilities.bitOpInterFreqRSTDmeasurementR10 = NAS_LPP_NO_SLCT;
        }
    }
    else
    {
        pstProvideCapR9Ies->bitOpOTDOAProvideCapabilities = NAS_LPP_NO_SLCT;
        return NAS_LPP_FAILURE;
    }

    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LPP_SetGnssCapData
 Description     : 组织GNSS的能力
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangensheng      2015-10-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SetGnssCapData
(
    LPP_AGNSS_PROVIDE_CAP_STRU         *pstAGNSSProvideCapabilities,
    NAS_LPP_CAP_REQ_STRU               *pstCapReq,
    MTA_LPP_AGNSS_PROVIDE_CAP_STRU     *pstMtaLppGnssCap
)
{

    /* 赋值GNSS能力结构 - assistancedatasupportlist */
    if ((PS_TRUE  == pstCapReq->stGnssReqCap.bAssistanceDataSupportListReq)
        &&(NAS_LPP_SLCT == pstMtaLppGnssCap->bitOpAssistanceDataSupportList))
    {
        pstAGNSSProvideCapabilities->bitOpAssistanceDataSupportList = NAS_LPP_SLCT;
        pstAGNSSProvideCapabilities->stAssistanceDataSupportList =
                                    pstMtaLppGnssCap->stAssistanceDataSupportList;
    }

    /* 赋值GNSS能力结构 - gnsssupportlist */
    if ((PS_TRUE  == pstCapReq->stGnssReqCap.bGnssSupportListReq)
        &&(NAS_LPP_SLCT == pstMtaLppGnssCap->bitOpGnssSupportList))
    {
        pstAGNSSProvideCapabilities->bitOpGnssSupportList = NAS_LPP_SLCT;
        pstAGNSSProvideCapabilities->stGnssSupportList =
                                    pstMtaLppGnssCap->stGnssSupportList;
    }

    /* 赋值GNSS能力结构 - location velocity types */
    if (PS_TRUE  == pstCapReq->stGnssReqCap.blocationVelocityTypesReq)
    {
        if (NAS_LPP_SLCT == pstMtaLppGnssCap->bitOpLocationCoordinateTypes)
        {
            pstAGNSSProvideCapabilities->bitOpLocationCoordinateTypes = NAS_LPP_SLCT;
            pstAGNSSProvideCapabilities->stLocationCoordinateTypes =
                                    pstMtaLppGnssCap->stLocationCoordinateTypes;
        }

        if ( NAS_LPP_SLCT == pstMtaLppGnssCap->bitOpVelocityTypes )
        {
            pstAGNSSProvideCapabilities->bitOpVelocityTypes = NAS_LPP_SLCT;
            pstAGNSSProvideCapabilities->stVelocityTypes =
                                    pstMtaLppGnssCap->stVelocityTypes;
        }
    }
}

/*****************************************************************************
 Function Name  : NAS_LPP_EncodeCapabilityProvideMsg
 Description    : 编码能力提供消息
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-7-24  新开发
*****************************************************************************/
VOS_UINT8 NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppMsg,
    VOS_UINT32                         *pulLppMsgLen,
    VOS_UINT8                          *pucEncodeOutMsg,
    NAS_LPP_MSG_IDENTITY_STRU          *pstLppMsgIdentity,
    VOS_UINT32                          ulSessionId,
    VOS_UINT8                           ucTransIndx
)
{
    LPP_MESSAGE_STRU                       *pstUplinkProvideCap = NAS_LPP_NULL_PTR;
    LPP_PROVIDE_CAPABILITIES_R9_IES_STRU   *pstProvideCapR9Ies  = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElement    = NAS_LPP_NULL_PTR;
    LRRC_SUPPORT_CAPABILITY_STRU           *pstLrrcCap          = NAS_LPP_NULL_PTR;
    VOS_UINT16                              usRslt              = 0;
    VOS_UINT16                              usBitPos            = 0;
    NAS_LPP_GNSS_DATA_STRU                 *pstGnssData         = NAS_LPP_NULL_PTR;

    NAS_LPP_ERR_LOG("NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_Func_Enter);

    /*清空LPP MSG BUFF*/
    NAS_LPP_ClearLppMsgBuff();

    /*获取LPP MSG BUFF*/
    pstUplinkProvideCap = NAS_LPP_GetLppMsgBuff();
    pstLrrcCap = NAS_LPP_GetLrrcCap();

    /* 获取 LPP GNSS 能力的结构体 */
    pstGnssData = NAS_LPP_GetGnssData();

    pstTransElement = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if ( NAS_LPP_NULL_PTR == pstTransElement)
    {
        NAS_LPP_ERR_LOG1("encode capability with wrong index", ucTransIndx);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_TransDontEnd);
        return NAS_LPP_FAILURE;
    }

    /*得到上行提供能力的地址*/
    pstProvideCapR9Ies  = NAS_LPP_GetUpLinkProvideCapIEAddr(pstUplinkProvideCap);

    /*能力提供公共信元*/
    pstUplinkProvideCap->bitOpLppTransactionId    = NAS_LPP_SLCT;
    pstUplinkProvideCap->bitOpSequenceNumber      = NAS_LPP_SLCT;
    pstUplinkProvideCap->bitOpAcknowledgement     = NAS_LPP_SLCT;
    pstUplinkProvideCap->bitOpLppMessageBody      = NAS_LPP_SLCT;
    /*本transaction结束*/
    pstUplinkProvideCap->bEndTransaction          = PS_TRUE;
    pstUplinkProvideCap->stTransactionId.enInitiator =
        pstLppMsg->stTransactionId.enInitiator;
    pstUplinkProvideCap->stTransactionId.ucTransactionNumber  =
        pstLppMsg->stTransactionId.ucTransactionNumber;
    pstUplinkProvideCap->stSequenceNumber.ucSequenceNumber = NAS_LPP_GetUpMsgSequenceNum();
    pstUplinkProvideCap->stAcknowledgement.bitOpAckIndicator = NAS_LPP_NO_SLCT;
    /*需要网络侧回复ACK*/
    pstUplinkProvideCap->stAcknowledgement.bAckRequested  = PS_TRUE;
    pstUplinkProvideCap->stLppMessageBody.ulChoice        =
        LPP_C1_MESSAGE_BODY_CHOSEN;
    pstUplinkProvideCap->stLppMessageBody.u.stC1.ulChoice =
        LPP_SUPPORT_MESSAGE_BODY_PROVIDE_CAPABILITIES_CHOSEN;
    pstUplinkProvideCap->stLppMessageBody.u.stC1.u.stProvideCapabilities.ulChoice =
        LPP_C1_CRITI_EXT_PROVIDE_CAPABILITIES_CHOSEN;
    pstUplinkProvideCap->stLppMessageBody.u.stC1.u.stProvideCapabilities.u.stC1.ulChoice =
        LPP_PROVIDE_CAPABILITIES_R9_CHOSEN;

    /*如果请求了ECID的能力，则填充ECID的提供能力信息*/
    if(NAS_LPP_SLCT == pstTransElement->stCapReq.bitOpEcidCapReq)
    {
        NAS_LPP_INFO_LOG("NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo: Ecid Capa Req!");
        TLPS_PRINT2LAYER_INFO(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_EcidCpaReq);

        pstProvideCapR9Ies->bitOpECIDProvideCapabilities = NAS_LPP_SLCT;
        pstProvideCapR9Ies->stECIDProvideCapabilities.stEcidMeasSupported.ucEcidMeasSupCnt = 3;

        /*填充ECID支持的能力*/
        if(LPP_LRRC_INFO_FLAG_VALID == NAS_LPP_GetLrrcRxTxTimeDiffMeasFlag())
        {
            /*111代表RSRP, RSRQ， RXTXTimeDiff都支持*/
            pstProvideCapR9Ies->stECIDProvideCapabilities.stEcidMeasSupported.ucEcidMeasSup = 0x07; /*111*/
        }
        else
        {
            /*110代表RSRP, RSRQ支持， 但是RXTXTimeDiff不支持*/
            pstProvideCapR9Ies->stECIDProvideCapabilities.stEcidMeasSupported.ucEcidMeasSup = 0x06; /*110*/
        }
    }

    if(NAS_LPP_SLCT == pstTransElement->stCapReq.bitOpOtdoaCapReq)
    {
        NAS_LPP_INFO_LOG("NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo: Otdoa Capa Req!");
        TLPS_PRINT2LAYER_INFO(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_OtdoaCpaReq);

        if (NAS_LPP_SUCCESS != NAS_LPP_EncodeOtodaCapability(pstProvideCapR9Ies,pstTransElement,pstLrrcCap) )
        {
            NAS_LPP_ERR_LOG("Encode otdoa capability fail");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_EncodeOtdoaCapabilityFail);
            pstProvideCapR9Ies->bitOpOTDOAProvideCapabilities = NAS_LPP_NO_SLCT;
        }
    }

    if(NAS_LPP_SLCT == pstTransElement->stCapReq.bitOpAgnssCapReq)
    {
        /*如果开机的请求能力成功的回复了，则直接组织上报*/
        if ( PS_TRUE == pstGnssData->bGnssCapbilityFlag )
        {
            pstProvideCapR9Ies->bitOpAGNSSProvideCapabilities = NAS_LPP_SLCT;
            NAS_LPP_SetGnssCapData(&pstProvideCapR9Ies->stAGNSSProvideCapabilities,
                                   &pstTransElement->stCapReq ,
                                   &pstGnssData->stMtaLppGnssCap);
        }
        else
        {
            pstProvideCapR9Ies->bitOpAGNSSProvideCapabilities = NAS_LPP_NO_SLCT;
        }
    }

    /*开始编码*/
    usRslt = NAS_LPP_EncodeMessage(pstUplinkProvideCap,
                                   &usBitPos,
                                   pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo: Encode ProvideCap msg Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo_ENUM, LNAS_LPP_ENCODE_LPP_MSG_FAIL);
        return NAS_LPP_FAILURE;
    }

    *pulLppMsgLen = usBitPos/8;

    /* 填充上行消息身份识别信息 */
    pstLppMsgIdentity->ulSessionId                   =
                                                    ulSessionId;
    pstLppMsgIdentity->stTransId.enInitiator            =
                                                    pstUplinkProvideCap->stTransactionId.enInitiator;
    pstLppMsgIdentity->stTransId.ucTransactionNumber    =
                                                    pstUplinkProvideCap->stTransactionId.ucTransactionNumber;
    pstLppMsgIdentity->usSequnceNum                     =
                                                    pstUplinkProvideCap->stSequenceNumber.ucSequenceNumber;
    pstLppMsgIdentity->enUplinkMsgType                  =
                                                    NAS_LPP_UPLINK_MSG_TYPE_PROCESS;

    /* 编码成功 */
    return NAS_LPP_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_LPP_CreatNewTransAndReqAssistData
 Description     :  生成新的transaction，然后申请辅助数据
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-11  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_CreatNewTransAndReqAssistData
(
    VOS_UINT8                               ucSessionIndx,
    VOS_BOOL                                enOtdoaAssist,
    VOS_BOOL                                enGnssAssist,
    MTA_LPP_GNSS_ASSIST_DATA_REQ_STRU      *pstMtaLppGnssAssistDataReq
)
{
    VOS_UINT8                                   ucTmpTransIndx = 0;
    VOS_UINT8                                   ucTmpSessionTransIndex = 0;
    VOS_UINT8                                   ucRslt = 0;
    NAS_LPP_TRANS_ID_STRU                       stTransId = {0};

    NAS_LPP_INFO_LOG("NAS_LPP_CreatNewTransAndReqAssistData_ENUM ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_CreatNewTransAndReqAssistData_ENUM, LNAS_LPP_Func_Enter);

    /*创建一个新的Transaction，申请辅助数据*/
    NAS_LPP_CreatNewTrans(ucSessionIndx,&ucTmpSessionTransIndex,&ucTmpTransIndx);

    /*在新的trans里申请辅助数据*/
    if ( PS_NULL_UINT8 != ucTmpTransIndx )
    {
        ucRslt = NAS_LPP_SndUplinkReqAssistDataMsg(ucSessionIndx,ucTmpSessionTransIndex,ucTmpTransIndx,enOtdoaAssist,enGnssAssist, pstMtaLppGnssAssistDataReq);
        if(NAS_LPP_SUCCESS != ucRslt)
        {
            stTransId.enInitiator =
                NAS_LPP_GetLppEntityCtx()->stTransEntityPool.astTransElementEntity[ucTmpTransIndx].stTransId.enInitiator;
            stTransId.ucTransactionNumber =
                NAS_LPP_GetLppEntityCtx()->stTransEntityPool.astTransElementEntity[ucTmpTransIndx].stTransId.ucTransactionNumber;
            NAS_LPP_ReleaseTransactionOrSession(ucSessionIndx,
                                                ucTmpSessionTransIndex,
                                               &stTransId);
            return;
        }
        NAS_LPP_ChangeTransFsmState(ucSessionIndx, ucTmpSessionTransIndex, LPP_MS_ASSISTDATA, LPP_SS_WAIT_INTRA_DATA_CNF);
    }
}

/*lint -e774*/
/*****************************************************************************
 Function Name   : NAS_LPP_AgainReqAssistData
 Description     :  接收完当前的辅助数据 流程后，再次补充申请辅助数据
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-9-11  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_AgainReqAssistData( VOS_VOID )
{
    NAS_LPP_CONFIG_PARA_STRU                *pstCfgpara;
    NAS_LPP_LOC_TECH_MAP_STRU               *pstTechmap;
    VOS_UINT8 ucSessionIdx = PS_NULL_UINT8,ucOtdoaSessionIdx = PS_NULL_UINT8;
    VOS_BOOL enReqOtdoaAssis = VOS_FALSE;

    NAS_LPP_ERR_LOG("NAS_LPP_AgainReqAssistData ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_AgainReqAssistData_ENUM, LNAS_LPP_Func_Enter);

    pstCfgpara = NAS_LPP_GetCfgPara();

    pstTechmap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);

    /*如果location req要求了otdoa的测量，但是，当前otoda的辅助数据没有*/
    if ( (NAS_LPP_NULL_PTR != pstTechmap)
       &&(LPP_LRRC_INFO_FLAG_INVALID == pstCfgpara->stOtdoaAssisCfg.ucOtdoaReferenceCellInfoFlag) )
    {
        enReqOtdoaAssis = VOS_TRUE;
        ucOtdoaSessionIdx = pstTechmap->ucSessionIndx;
    }

    /*先建立一个transaction，申请辅助信息*/
    if (VOS_TRUE == enReqOtdoaAssis)
    {
        if (PS_NULL_UINT8 != ucOtdoaSessionIdx )
        {
            ucSessionIdx = ucOtdoaSessionIdx;
        }


        NAS_LPP_CreatNewTransAndReqAssistData( ucSessionIdx, enReqOtdoaAssis, VOS_FALSE, NAS_LPP_NULL_PTR);
    }

}
/*lint +e774*/

/*****************************************************************************
 Function Name   : NAS_LPP_StopTechLocForLackOfAssistData
 Description     : 缺少辅助数据，需要停止的测量:只有OTDOA有此情况。如果OTDOA没有辅助数据，并且，OTDOA的transaction
                   里没有其他的定位，要删除此transaction。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_StopTechLocForLackOfAssistData( VOS_VOID )
{
    NAS_LPP_CONFIG_PARA_STRU                *pstCfgpara;
    NAS_LPP_LOC_TECH_MAP_STRU               *pstTechmap;
    NAS_LPP_LOC_TECH_RUNING_STRU             stPosSearchRslt = {0};
    NAS_LPP_SUB_STATE_ENUM_UINT32            enSubState;
    VOS_UINT8                                ucRslt = 0;
    NAS_LPP_TRANS_ID_STRU                    stTransId = {0};

    NAS_LPP_INFO_LOG("NAS_LPP_StopTechLocForLackOfAssistData ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_StopTechLocForLackOfAssistData_ENUM, LNAS_LPP_Func_Enter);

    pstCfgpara = NAS_LPP_GetCfgPara();

    pstTechmap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);

    /*如果location req要求了otdoa的测量，但是，当前otoda的辅助数据没有*/
    if ( NAS_LPP_NULL_PTR != pstTechmap )
    {
        if (LPP_LRRC_INFO_FLAG_INVALID == pstCfgpara->stOtdoaAssisCfg.ucOtdoaReferenceCellInfoFlag)
        {
            /*看此transaction里是否还有其他的定位技术*/
            NAS_LPP_SearchRunningPosTechByTransIndx(pstTechmap->ucTransIndx,&stPosSearchRslt);
            if (1 == stPosSearchRslt.ucNum)
            {
                /*发送一个上行ABORT,结束transaction*/
                ucRslt = NAS_LPP_SndUpLppAbortMsg(pstTechmap->ucSessionIndx,
                                                  pstTechmap->ucSessionTranIndx,
                                                  pstTechmap->ucTransIndx,
                                                  LPP_COMMON_IES_ABORT_TARGET_DEVCIE_ABORT,
                                                  VOS_TRUE,
                                                  VOS_TRUE);
                if(NAS_LPP_SUCCESS != ucRslt)
                {
                    stTransId.enInitiator =
                        NAS_LPP_GetLppEntityCtx()->stTransEntityPool.astTransElementEntity[pstTechmap->ucTransIndx].stTransId.enInitiator;

                    stTransId.ucTransactionNumber =
                        NAS_LPP_GetLppEntityCtx()->stTransEntityPool.astTransElementEntity[pstTechmap->ucTransIndx].stTransId.ucTransactionNumber;

                    NAS_LPP_ReleaseTransactionOrSession(pstTechmap->ucSessionIndx,
                                                        pstTechmap->ucSessionTranIndx,
                                                       &stTransId);
                    return;
                }

                NAS_LPP_SetEndTransFlg(pstTechmap->ucSessionIndx,
                                       pstTechmap->ucSessionTranIndx,
                                       VOS_TRUE);

                NAS_LPP_ChangeTransFsmState(pstTechmap->ucSessionIndx,
                                            pstTechmap->ucSessionTranIndx,
                                            NAS_LPP_GetLppMainState(pstTechmap->ucSessionIndx,pstTechmap->ucSessionTranIndx),
                                            LPP_SS_WAIT_INTRA_DATA_CNF);
            }
            else/*transaction还有其他的定位技术*/
            {
                enSubState = NAS_LPP_GetLppSubState(pstTechmap->ucSessionIndx,pstTechmap->ucSessionTranIndx);
                if ((LPP_SS_WAIT_ASSISTDATA_RCV_CMP == enSubState)||(LPP_SS_WAIT_ASSISTDATA_REQ_PROCESS_CMP == enSubState))
                {
                    NAS_LPP_ChangeTransFsmState(pstTechmap->ucSessionIndx,
                                                pstTechmap->ucSessionTranIndx,
                                                NAS_LPP_GetLppMainState(pstTechmap->ucSessionIndx,pstTechmap->ucSessionTranIndx),
                                                LPP_SS_WAIT_MEAS_IND);
                }
            }
        }
    }
}

/*****************************************************************************
Function Name  : NAS_LPP_VerifyOrCreateTransaction
Description    : 创建transaction
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-7-24  新开发
*****************************************************************************/
NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU* NAS_LPP_VerifyOrCreateTransaction
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppMsgHead,
    VOS_UINT32                          ulSessionId,
    VOS_UINT8                          *pucTransIndx,
    VOS_UINT8                          *pucSessionTransIndx
)
{
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU        *pstSessionEntity    = NAS_LPP_NULL_PTR;
    VOS_UINT8                                   ucTransIndex        = 0;
    VOS_UINT32                                  ulRslt              = 0;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransEntity      = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANS_ID_STRU                       stTransId;
    VOS_UINT8                                   ucSessionIndx       = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_VerifyOrCreateTransaction ENTER!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_VerifyOrCreateTransaction_ENUM, LNAS_LPP_Func_Enter);

    ucSessionIndx = NAS_LPP_SearchSessionIndx(ulSessionId);
    if(PS_NULL_UINT8 == ucSessionIndx)
    {
        /*没找到，创建session实体*/
        NAS_LPP_WARN_LOG("NAS_LPP_VerifyOrCreateTransaction: can't find Session!");
        TLPS_PRINT2LAYER_WARNING(NAS_LPP_VerifyOrCreateTransaction_ENUM, LNAS_LPP_CanntFindSession);

        pstSessionEntity = NAS_LPP_MallocSessionEntity(ulSessionId); /*创建session实体*/
        if(NAS_LPP_NULL_PTR == pstSessionEntity)
        {
            NAS_LPP_ERR_LOG("NAS_LPP_VerifyOrCreateTransaction: can't Alloc Session Entity!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_VerifyOrCreateTransaction_ENUM, LNAS_LPP_CanntAllocSessionEntity);
            return NAS_LPP_NULL_PTR;
        }

        ucTransIndex = NAS_LPP_MallocTransEntityIndx(&(pstLppMsgHead->stTransactionId)); /*创建transaction实体*/
        pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndex);
        if(NAS_LPP_NULL_PTR == pstTransEntity)
        {
            NAS_LPP_ERR_LOG("NAS_LPP_VerifyOrCreateTransaction: can't Alloc Transcation Entity!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_VerifyOrCreateTransaction_ENUM, LNAS_LPP_CanntAllocTransEntity);
            NAS_LPP_ReleaseSessionEntityByIndex(ucSessionIndx);
            return NAS_LPP_NULL_PTR;
        }

        ulRslt = NAS_LPP_AddTransEntityToSession(pstSessionEntity, ucTransIndex, pucSessionTransIndx); /*将session和transaction关联起来*/
        if(NAS_LPP_SUCCESS != ulRslt)
        {
            NAS_LPP_ERR_LOG("NAS_LPP_VerifyOrCreateTransaction: Transcation entity is full!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_VerifyOrCreateTransaction_ENUM, LNAS_LPP_TransEntityIsFull);
            return NAS_LPP_NULL_PTR;
        }
    }
    else
    {
        /*找到了session，获取实体指针*/
        pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
        if(NAS_LPP_NULL_PTR == pstSessionEntity)
        {
            NAS_LPP_ERR_LOG("NAS_LPP_VerifyOrCreateTransaction: can't Get Session Entity!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_VerifyOrCreateTransaction_ENUM, LNAS_LPP_CanntGetSessionEntity);
            return NAS_LPP_NULL_PTR;
        }

        stTransId.enInitiator           = pstLppMsgHead->stTransactionId.enInitiator;
        stTransId.ucTransactionNumber   = pstLppMsgHead->stTransactionId.ucTransactionNumber;
        /*能找到session实体，则查找session中transaction实体*/
        NAS_LPP_SearchTransEntityIndx(ucSessionIndx,
                                      &stTransId,
                                      &ucTransIndex,
                                      pucSessionTransIndx);
        pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndex);
        if(NAS_LPP_NULL_PTR == pstTransEntity)
        {
            /*没有找到，则创建transaction实体*/
            NAS_LPP_WARN_LOG("NAS_LPP_VerifyOrCreateTransaction: can't find transation!");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_VerifyOrCreateTransaction_ENUM, LNAS_LPP_DontFindTransaction);
            ucTransIndex = NAS_LPP_MallocTransEntityIndx(&(pstLppMsgHead->stTransactionId));
            pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndex);
            if(NAS_LPP_NULL_PTR == pstTransEntity)
            {
                NAS_LPP_ERR_LOG("NAS_LPP_VerifyOrCreateTransaction: can't Alloc Transcation Entity!");
                TLPS_PRINT2LAYER_ERROR(NAS_LPP_VerifyOrCreateTransaction_ENUM, LNAS_LPP_CanntAllocTransEntity);
                return NAS_LPP_NULL_PTR;
            }

            ulRslt = NAS_LPP_AddTransEntityToSession(pstSessionEntity, ucTransIndex, pucSessionTransIndx); /*将session和transaction关联起来*/
            if(NAS_LPP_SUCCESS != ulRslt)
            {
                NAS_LPP_ERR_LOG("NAS_LPP_VerifyOrCreateTransaction: Transcation entity is full!");
                TLPS_PRINT2LAYER_ERROR(NAS_LPP_VerifyOrCreateTransaction_ENUM, LNAS_LPP_TransEntityIsFull);
                NAS_LPP_ReturnTransEntityToPool(ucTransIndex);

                return NAS_LPP_NULL_PTR;
            }
        }
    }

    *pucTransIndx = ucTransIndex;

    return pstTransEntity;
}

/*****************************************************************************
Function Name  : NAS_LPP_SndUplinkProvideCapbilityMsg
Description    : 发送上行的能力提供消息
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-7-24  新开发
*****************************************************************************/
VOS_UINT8 NAS_LPP_SndUplinkProvideCapbilityMsg
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppMsgHead,
    VOS_UINT32                          ulSessionId,
    VOS_UINT8                           ucTransIndx
)
{
    VOS_UINT32                          ulLppMsgLen     = 0;
    VOS_UINT8                          *pucEncodeOutMsg = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_IDENTITY_STRU           stLppMsgIdentity = {0};
    VOS_UINT8                           ucRslt          = 0;

    NAS_LPP_NORM_LOG("NAS_LPP_SndUplinkProvideCapbilityMsg!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndUplinkProvideCapbilityMsg_ENUM, LNAS_LPP_Func_Enter);

    /*分配编码之后码流的存储空间*/
    pucEncodeOutMsg = NAS_LPP_MEM_ALLOC(sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);
    if(NAS_LPP_NULL_PTR == pucEncodeOutMsg)
    {
        return NAS_LPP_FAILURE;
    }

    /*清空*/
    NAS_LPP_MEM_SET_S(pucEncodeOutMsg,sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN, 0, sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);

    /*组装提供能力消息,并且获取身份识别信息*/
    ucRslt = NAS_LPP_EncodeCapabilityProvideMsgWithIndentityInfo(pstLppMsgHead,
                                                                 &ulLppMsgLen,
                                                                 pucEncodeOutMsg,
                                                                 &stLppMsgIdentity,
                                                                 ulSessionId,
                                                                 ucTransIndx);
    if(NAS_LPP_SUCCESS != ucRslt)
    {
        NAS_LPP_MEM_FREE(pucEncodeOutMsg);
        return ucRslt;
    }

    /*HIDS air msg */
    NAS_LPP_SendOmtAirMsg(NAS_LPP_OMT_AIR_MSG_UP,
                          LNAS_LPP_PROV_CAP,
                          ulLppMsgLen,
                          pucEncodeOutMsg);

    /*发送编码好的数据给网侧*/
    NAS_LPP_SendUplinkMsg(ulSessionId,
                          ulLppMsgLen,
                          pucEncodeOutMsg,
                          &stLppMsgIdentity);

    /*释放动态内存*/
    NAS_LPP_MEM_FREE(pucEncodeOutMsg);

    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvCapabitlityRequestHandle
Description    : 处理网络侧下发的能力请求消息
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-7-24  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_RcvCapabitlityRequestHandle
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppMsgHead,
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_INDEX_STRU           *pstLppTransIndex
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransEntity      = NAS_LPP_NULL_PTR;
    VOS_UINT8                                   ucSessionTransIndx  = 0;
    VOS_UINT8                                   ucSessionIndx       = 0;
    VOS_UINT8                                   ucTransIndx         = 0;
    NAS_LPP_GNSS_DATA_STRU                     *pstGnssData         = NAS_LPP_NULL_PTR;
    VOS_UINT8                                   ucRslt              = 0;
    NAS_LPP_TRANS_ID_STRU                       stTransId          = {0};

    NAS_LPP_NORM_LOG("NAS_LPP_RcvCapabitlityRequestHandle!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvCapabitlityRequestHandle_ENUM, LNAS_LPP_Func_Enter);

    /*得到transaction的相关联的参数*/
    pstTransEntity      = pstLppTransIndex->pstTransEntity;
    ucTransIndx         = pstLppTransIndex->ucTransIndx;
    ucSessionTransIndx  = pstLppTransIndex->ucSessionTransIndx;

    pstGnssData = NAS_LPP_GetGnssData();

    /*获得session的index*/
    ucSessionIndx = NAS_LPP_SearchSessionIndx(ulSessionId);

    /*保存下行sequenceNumber*/
    NAS_LPP_SetDownLinkMsgSequenceNum(ucSessionIndx,
                                      pstLppMsgHead->stSequenceNumber.ucSequenceNumber);

    if((NAS_LPP_SLCT == pstTransEntity->stCapReq.bitOpAgnssCapReq)
       &&(PS_FALSE == pstGnssData->bGnssCapbilityFlag))
    {
        /*如果开机请求的能力不成功，则需要请求MTA GNSS的能力信息，
          如果同时也请求了ECID, OTDOA的能力，则等待GNSS的能力回复之后
          才上报
        */
        NAS_LPP_GNSSCapReq();

        /* 转状态到等能力cnf，启动等GNSS CAP CNF 定时器 */
        NAS_LPP_ChangeTransFsmState(ucSessionIndx,
                                    ucSessionTransIndx,
                                    LPP_MS_CAPABILITY,
                                    LPP_SS_CAP_REQ_WAIT_CNF);
        return;
    }

    /*回复ProvideCapbility消息*/
    ucRslt = NAS_LPP_SndUplinkProvideCapbilityMsg(pstLppMsgHead, ulSessionId,ucTransIndx);
    if(NAS_LPP_SUCCESS != ucRslt)
    {
        stTransId.enInitiator = pstLppMsgHead->stTransactionId.enInitiator;
        stTransId.ucTransactionNumber = pstLppMsgHead->stTransactionId.ucTransactionNumber;
        NAS_LPP_ReleaseTransactionOrSession(ucSessionIndx,
                                            ucSessionTransIndx,
                                            &stTransId);
        return;
    }

    /*表示当前transaction如果收到网络侧的ACK之后，就可以结束了*/
    pstTransEntity->ucTransEndFlag   = PS_TRUE;

    /*记录当前发送的空口消息，用于收到网络侧的消息之后决定转到什么状态*/
    pstTransEntity->enLastUpMsgId    = NAS_LPP_AIR_MSG_PROVIDE_CAP;

    /*转状态,转到能力交互，子状态等内部的data cnf，也就是确认把空口消息发送到了基站*/
    NAS_LPP_ChangeTransFsmState(ucSessionIndx,
                                ucSessionTransIndx,
                                LPP_MS_CAPABILITY,
                                LPP_SS_WAIT_INTRA_DATA_CNF);

    return;
}

/*****************************************************************************
Function Name   : NAS_LPP_CfgLrrcOtdoaMeas
Description     : 配置LRRC的otoda测量
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-8-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_CfgLrrcOtdoaMeasInLocationTrans
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT8                           ucTransIndx,
    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8    ucLcsMeasCmd

)
{
    NAS_LPP_NORM_LOG("NAS_LPP_CfgLrrcOtdoaMeasInLocationTrans!");
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_CfgLrrcOtdoaMeasInLocationTrans_ENUM, LNAS_LPP_LcsMeasCmd, ucLcsMeasCmd);

    NAS_LPP_SndOtdoaMeasReq(ucSessionIndx,ucSessionTransIndx,ucLcsMeasCmd);

    if (LPP_LRRC_LCS_MEAS_CMD_SETUP == ucLcsMeasCmd)
    {
        NAS_LPP_ChangeTransFsmState(ucSessionIndx,ucSessionTransIndx,LPP_MS_LOCATION,LPP_SS_WAIT_LRRC_MEAS_CNF);
    }
    else
    {
        NAS_LPP_ChangeTransFsmState(ucSessionIndx,ucSessionTransIndx,LPP_MS_LOCATION,LPP_SS_WAIT_RELEASE_LRRC_MEAS_CNF);
    }
}

/*****************************************************************************
Function Name   : NAS_LPP_RcvOtdoaAssistDataHandle
Description     : otdoa的辅助数据处理
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-9-2  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_RcvOtdoaAssistDataHandle
(
    VOS_UINT8                           ucSessionIndx,
    NAS_LPP_TRANS_INDEX_STRU           *pstLppTransIndex
)
{
    NAS_LPP_LOC_TECH_MAP_STRU              *pstLocTechmap    = NAS_LPP_NULL_PTR;
    NAS_LPP_CONFIG_PARA_STRU               *pstCfgPara;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU    *pstSessionEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8                               ucRslt           = 0;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity  = NAS_LPP_NULL_PTR;
    VOS_UINT32 ulRslt;
    NAS_LPP_TRANS_ID_STRU                   stTransId      = {0};

    pstCfgPara = NAS_LPP_GetCfgPara();

    if ( (NAS_LPP_SLCT != pstCfgPara->bitOtdoaAssisChng))
    {
        return;
    }

    pstCfgPara->bitOtdoaAssisChng = NAS_LPP_NO_SLCT;

    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if(NAS_LPP_NULL_PTR  == pstSessionEntity)
    {
        return;
    }

    pstTransEntity = NAS_LPP_GetTransElementByIndex(pstLppTransIndex->ucTransIndx);
    if (NAS_LPP_NULL_PTR == pstTransEntity)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvOtdoaAssistDataHandle_ENUM, LNAS_LPP_TransDontEnd);
        return;
    }
    /*在本session的其他transaction里查找:有没有otdoa的location info req的transaction
     只有OTDOA的request location transaction里有等待辅助数据的情况。GNSS不一定要求辅助数据.*/

    /*等assist data transaction结束是，检查OTDOA的数据是否齐全和正确*/
    ulRslt = NAS_LPP_CheckOtdoaAssisDataAfterSave();
    if (NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvOtdoaAssistDataHandle_ENUM, LNAS_LPP_NAS_LPP_CheckOtdoaAssisDataAfterSaveFail);
        /* 返回lpp error */
        ucRslt = NAS_LPP_SndUpLppErrorMsg(pstSessionEntity->ulSessionId,
                                         &pstTransEntity->stTransId,
                                          LPP_COMMON_IES_ERROR_LPP_MESSAGE_BODY_ERROR,
                                          VOS_TRUE,
                                          VOS_TRUE);
        if(NAS_LPP_SUCCESS != ucRslt)
        {
            pstLocTechmap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);
            if(NAS_LPP_NULL_PTR != pstLocTechmap)
            {
                stTransId.enInitiator =
                    NAS_LPP_GetLppEntityCtx()->stTransEntityPool.astTransElementEntity[pstLocTechmap->ucTransIndx].stTransId.enInitiator;
                stTransId.ucTransactionNumber =
                    NAS_LPP_GetLppEntityCtx()->stTransEntityPool.astTransElementEntity[pstLocTechmap->ucTransIndx].stTransId.ucTransactionNumber;
                NAS_LPP_ReleaseTransactionOrSession(pstLocTechmap->ucSessionIndx,
                                                    pstLocTechmap->ucSessionTranIndx,
                                                    &stTransId);

            }
            return;
        }

        NAS_LPP_SetEndTransFlg(ucSessionIndx,
                               pstLppTransIndex->ucSessionTransIndx,
                               VOS_TRUE);

        /*  释放对应的todoa参数 */
        pstTransEntity->enLastUpMsgId = NAS_LPP_AIR_MSG_UP_ERR;
        NAS_LPP_MEM_SET_S(&pstCfgPara->stOtdoaAssisCfg,sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU), 0, sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU) );
    }

    pstLocTechmap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);
    if (NAS_LPP_NULL_PTR != pstLocTechmap)
    {
        TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvOtdoaAssistDataHandle_ENUM, LNAS_LPP_GetOtdoaRunningSucc);
        /*如果有查找到OTDOA的location info req， 在那个transaction下面继续走流程，配置LRRC/GNSS*/
        if (pstLocTechmap->ucSessionIndx == ucSessionIndx)
        {
            if (NAS_LPP_MSG_VERIFY_SUCC == ulRslt)
            {
                /*loc infor req transaction里配置LRRC*/
                NAS_LPP_CfgLrrcOtdoaMeasInLocationTrans(pstLocTechmap->ucSessionIndx,
                                                        pstLocTechmap->ucSessionTranIndx,
                                                        pstLocTechmap->ucTransIndx,
                                                        LPP_LRRC_LCS_MEAS_CMD_SETUP);
            }
            else
            {
                /*loc infor req transaction里 释放LRRC*/
                NAS_LPP_CfgLrrcOtdoaMeasInLocationTrans(pstLocTechmap->ucSessionIndx,
                                                        pstLocTechmap->ucSessionTranIndx,
                                                        pstLocTechmap->ucTransIndx,
                                                        LPP_LRRC_LCS_MEAS_CMD_REL);
            }
        }
        else /* 如果没找到，不配置LRRC,等otdoa的loc infor req再配置LRRC*/
        {
        }
    }

}

/*****************************************************************************
Function Name   : NAS_LPP_RcvGnssAssistDataHandle
Description     :
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-9-2  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvGnssAssistDataHandle( VOS_UINT8 ucSessionIndx )
{
    /*  透传给 MTA，无需处理*/
}
/***************z**************************************************************
Function Name  : NAS_LPP_RcvAssistDataProvideHandle
Description    : 处理网络侧下发的辅助信息提供消息
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-7-24  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_RcvAssistDataProvideHandle
(
    NAS_LPP_MSG_HEAD_STRU              *pstMsgHead,
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_INDEX_STRU           *pstLppTransIndex
)
{
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity  = NAS_LPP_NULL_PTR;
    VOS_UINT8                                ucTransIndx            = 0;
    VOS_UINT8                                ucSessionIndx          = 0;
    NAS_LPP_CONFIG_PARA_STRU                *pstCfgPara             = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvAssistDataProvideHandle!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvAssistDataProvideHandle_ENUM, LNAS_LPP_Func_Enter);

    /*1、如果是先收到location info req、再补充收集assist data的情况，收完assist data，结束本TRANSACTION后，
         在那个location info req的transaction里根据assist data配置LRRC或gps。
      2、如果是切换小区后的assist data 更新，直接根据assist data配置LRRC或gps*/

    /*获得session的index*/
    ucSessionIndx = NAS_LPP_SearchSessionIndx(ulSessionId);
    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if ( NAS_LPP_NULL_PTR == pstSessionEntity  )
    {
        NAS_LPP_ERR_LOG1("assist data not found session", ulSessionId);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvAssistDataProvideHandle_ENUM, LNAS_LPP_CanntGetSessionEntity);
        return;
    }

    /*在辅助数据接收完成前，先不配置LRRC和gnss*/
    if (VOS_TRUE != pstMsgHead->bEndTransaction)
    {
        return;
    }
    /*接收完辅助数据，将GNSS辅助数据改变的标识清除*/
    pstCfgPara = NAS_LPP_GetCfgPara();
    pstCfgPara->bitGnssAssisChng = NAS_LPP_NO_SLCT;

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndx,pstLppTransIndex->ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if (NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("NAS_LPP_RcvAssistDataProvideHandle:wrong session index,session trans index ",
                          ucSessionIndx,
                          pstLppTransIndex->ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvOtdoaAssistDataHandle_ENUM, LNAS_LPP_DontFindTransaction);
        return;
    }

    NAS_LPP_SetEndTransFlg( ucSessionIndx, pstLppTransIndex->ucSessionTransIndx,VOS_TRUE);

    NAS_LPP_RcvOtdoaAssistDataHandle(ucSessionIndx,pstLppTransIndex);
    NAS_LPP_RcvGnssAssistDataHandle(ucSessionIndx);


    /*判断是否需要补充申请其它辅助信息的:如果辅助数据的transaction 是UE自己创建的、并且UE在此也主动申请了OTDOA的辅助数据，就无需再申请了*/
    if ( LPP_INITIATOR_TYPE_LOCATION_SERVER == pstTransElementEntity->stTransId.enInitiator )
    {
        NAS_LPP_AgainReqAssistData();
    }
    else
    {
        if ( (NAS_LPP_SLCT != pstTransElementEntity->bitOpOtdoaAssistReq) )
        {
            /*虽然此辅助数据流程是UE发起的，但是没有专门申请过OTDOA的辅助数据，如果需要otdoa的辅助数据，也要尝试申请otdoa的*/
            NAS_LPP_AgainReqAssistData();
        }
        else
        {
            /*判断由于没有辅助数据，需要停止的定位测量:只有OTDOA*/
            NAS_LPP_StopTechLocForLackOfAssistData();
        }
    }

    if ((NAS_LPP_SLCT == pstMsgHead->bitOpAcknowledgement)
        && (VOS_TRUE == pstMsgHead->stAcknowledgement.bAckRequested))
    {
        /*如果是辅助数据的最后一条消息，而且请求了ACK，则将当前的子状态转成LPP_SS_WAIT_INTRA_DATA_CNF
          等待上行ack的dataCnf,收到ack的dataCnf之后，LPP会清空辅助数据transaction相关的信息
        */
        NAS_LPP_ChangeTransFsmState( ucSessionIndx, pstLppTransIndex->ucSessionTransIndx, LPP_MS_ASSISTDATA, LPP_SS_WAIT_INTRA_DATA_CNF);
    }
    else
    {
        /*辅助数据没有请求ack，清空当前session或者transaction*/
        NAS_LPP_ReleaseTransactionOrSession(ucSessionIndx,
                                            pstLppTransIndex->ucSessionTransIndx,
                                            &(pstLppTransIndex->pstTransEntity->stTransId));
    }

    return;
}
/*****************************************************************************
Function Name   : NAS_LPP_ProvideAssistDataConflictProcess
Description     :  辅助数据的对冲处理
               辅助数据流程的对冲处理:如果这条assist data是一个新的transaction的( 也就是找不到一个transaction)，
               需要判断是否有其他一个辅助数据流程在进行中.
                   如果有，就扔掉此消息,  但是，还要返回lpp ack.
                   如果没有，继续后面的处理
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-9-10  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_ProvideAssistDataConflictProcess
(
    VOS_BOOL                            enFirstAssistData,
    VOS_UINT32                          ulSessionId
)
{
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT8 ucLoop,ucLoop1;
    VOS_UINT8 ucSessionIdx;

    NAS_LPP_NORM_LOG("NAS_LPP_ProvideAssistDataConflictProcess!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_ProvideAssistDataConflictProcess_ENUM, LNAS_LPP_Func_Enter);

    /* 不是第一条*/
    if ( VOS_TRUE != enFirstAssistData )
    {
        return  NAS_LPP_SUCCESS;
    }

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    /*查找是否有其他的assist data transaction存在*/
    for ( ucLoop1 = 0 ; ucLoop1 < NAS_LPP_MAX_SESSION_COUNT; ucLoop1++ )
    {
        if ( 0 == (pstSessionEntityPool->ulSessionActiveBitmap & (0x1<<ucLoop1)) )
        {
            continue;
        }

        ucSessionIdx = ucLoop1;
        pstSessionEntity = &(pstSessionEntityPool->astLppSessionEntity[ucSessionIdx]);

        for ( ucLoop = 0 ; ucLoop < pstSessionEntity->stLppTrans.ucTransIdCount; ucLoop++ )
        {
            if (LPP_MS_ASSISTDATA == NAS_LPP_GetLppMainState(ucSessionIdx,ucLoop) )
            {
                return NAS_LPP_ASSIST_DATA_CONFLICT;
            }
        }
    }

    if (ucLoop1 >= NAS_LPP_MAX_SESSION_COUNT)
    {
        /*没找到，表示不冲突*/
        return NAS_LPP_SUCCESS;
    }

    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
Function Name  : NAS_LPP_SndLppMtaGnssMeasReq
Description    : 给MTA发送GNSS的测量请求
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-10-19 新开发
*****************************************************************************/
VOS_VOID NAS_LPP_SndLppMtaGnssMeasReq
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx
)
{
    LPP_MTA_GNSS_LOCATION_INFO_REQ_STRU    *pstGnssMeasReq  = NAS_LPP_NULL_PTR;
    VOS_UINT32                              ulSessionId     = 0;
    LPP_MESSAGE_STRU                       *pstMsgBuff      = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_SndLppMtaGnssMeasReq enter");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndLppMtaGnssMeasReq_ENUM, LNAS_LPP_Func_Enter);

    ulSessionId = NAS_LPP_GetLppSessionEntityPool()->astLppSessionEntity[ucSessionIndx].ulSessionId;
    pstMsgBuff  = NAS_LPP_GetLppMsgBuff();

    pstGnssMeasReq = (LPP_MTA_GNSS_LOCATION_INFO_REQ_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_MTA_GNSS_LOCATION_INFO_REQ_STRU));
    if (NAS_LPP_NULL_PTR == pstGnssMeasReq)
    {
        return;
    }

    NAS_LPP_MEM_SET_MSG(pstGnssMeasReq, sizeof(LPP_MTA_GNSS_LOCATION_INFO_REQ_STRU), 0, sizeof(LPP_MTA_GNSS_LOCATION_INFO_REQ_STRU));

    /*消息头*/
    NAS_LPP_WRITE_MTA_MSG_HEAD(pstGnssMeasReq, ID_LPP_MTA_GNSS_LOC_INFO_REQ);

    /*填充GNSS Meas Req消息实体*/
    pstGnssMeasReq->ulSessionId = ulSessionId;
    NAS_LPP_MEM_CPY_S(&(pstGnssMeasReq->stCommonIESReqLocInfo),
                    sizeof(LPP_MTA_COMMON_IES_REQ_LOCATION_INFO_STRU),
                    &(pstMsgBuff->stLppMessageBody.u.stC1.u.stRequestLocationInformation.u.stC1.u.stReqLocationInfoR9.stCommonIEsReqLocationInfo),
                    sizeof(LPP_MTA_COMMON_IES_REQ_LOCATION_INFO_STRU));

    NAS_LPP_MEM_CPY_S(&(pstGnssMeasReq->stGnssReqLocationInfo),
                    sizeof(LPP_MTA_AGNSS_REQ_LOCATION_INFO_STRU),
                    &(pstMsgBuff->stLppMessageBody.u.stC1.u.stRequestLocationInformation.u.stC1.u.stReqLocationInfoR9.stAGNSSReqLocationInfo),
                    sizeof(LPP_MTA_AGNSS_REQ_LOCATION_INFO_STRU));

    NAS_LPP_SND_MSG(pstGnssMeasReq);

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_RcvLocationReqForOtdoaHandle
 Description    : 收到OTDOA位置信息请求的处理
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      lifuxin 00253982 2015-11-06  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_RcvLocationReqForOtdoaHandle
(
    VOS_UINT32                      ulSessionId,
    VOS_UINT8                       ucSessionIndx,
    VOS_UINT8                       ucSessionTransIndx
)
{
    NAS_LPP_OTDOA_ASSIST_CFG_STRU              *pstOtdoaAssisCfg = NAS_LPP_NULL_PTR;
    NAS_LPP_CONFIG_PARA_STRU                   *pstCfgPara       = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvLocationReqForOtdoaHandle!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLocationReqForOtdoaHandle_ENUM, LNAS_LPP_Func_Enter);

    pstOtdoaAssisCfg = NAS_LPP_GetOtdoaAssisCfg();
    pstCfgPara = NAS_LPP_GetCfgPara();

    /*迭代三再做， 实现的步骤如下:
    1. 检测当前是否辅助数据(两个点: 本session是否有过OTDOA的辅助信息交换过程，以及locReq中时候带有OTDOA的辅助信息是否无效)
    2. 如果辅助信息无效，则新起transaction去请求OTDOA的辅助数据,如果是多种定位计数，此时子状态暂时不转成等请求辅助信息完成
    3. 当ECID测量cnf收到之后，检测本session请求了OTDOA的位置信息，而且当前有transaction正在进行辅助信息的交互过程，则将状态
       转成等待请求辅助数据完成， 辅助信息接收完成之后，在给LRRC发送OTDOA的测量请求，状态转成等待OTODA的测量cnf
    4. 如果辅助信息有效，直接给LRRC发送OTDOA测量请求
    5. 将当前定位计数加1
    */
    /*判断OTDOA辅助数据是否有效*/
    TLPS_PRINT2LAYER_WARNING2(NAS_LPP_RcvLocationReqForOtdoaHandle_ENUM, LNAS_LPP_RefCellFlagAndAssistChangeFlag, pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag, pstCfgPara->bitOtdoaAssisChng);

    if ( (LPP_LRRC_INFO_FLAG_VALID == pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag)
       &&(NAS_LPP_SLCT != pstCfgPara->bitOtdoaAssisChng) )
    {
        /*直接配置LRRC*/
        NAS_LPP_SndOtdoaMeasReq(ucSessionIndx, ucSessionTransIndx,LPP_LRRC_LCS_MEAS_CMD_SETUP);

        if ( LPP_SS_WAIT_LRRC_MEAS_CNF != NAS_LPP_GetLppSubState(ucSessionIndx, ucSessionTransIndx) )
        {
            /*转状态到等待LRRC测量CNF*/
            NAS_LPP_ChangeTransFsmState(ucSessionIndx, ucSessionTransIndx, LPP_MS_LOCATION, LPP_SS_WAIT_LRRC_MEAS_CNF);
        }
    }
    else
    {
        /* 判断是否有已经在进行的辅助数据流程:
              如果有，等那个辅助数据流程结束了，再判断是否otdoa的辅助数据有效、是否需要起辅助数据的请求流程;
              如果没有，立即申请辅助数据*/
        if (NAS_LPP_ASSIST_DATA_CONFLICT == NAS_LPP_ProvideAssistDataConflictProcess(VOS_TRUE,ulSessionId) )
        {
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvLocationReqForOtdoaHandle_ENUM, LNAS_LPP_AssistDataRcvIsRunning);
            /* 转状态到等待辅助数据完成 */
            NAS_LPP_ChangeTransFsmState(ucSessionIndx, ucSessionTransIndx, LPP_MS_LOCATION, LPP_SS_WAIT_ASSISTDATA_RCV_CMP);
        }
        else
        {
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvLocationReqForOtdoaHandle_ENUM, LNAS_LPP_NoAssistDataReqAssistData);
            /* 立即申请 */

            /* 转状态到等待LRRC测量CNF */
            NAS_LPP_ChangeTransFsmState(ucSessionIndx, ucSessionTransIndx, LPP_MS_LOCATION, LPP_SS_WAIT_ASSISTDATA_REQ_PROCESS_CMP);

            NAS_LPP_CreatNewTransAndReqAssistData(ucSessionIndx,VOS_TRUE,VOS_FALSE, NAS_LPP_NULL_PTR);
        }
    }

    pstCfgPara->bitOtdoaReq = NAS_LPP_NO_SLCT;

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvLocationRequestHandle
Description    : 处理网络侧下发的位置信息请求消息
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-7-24  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_RcvLocationRequestHandle
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppMsgHead,
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_INDEX_STRU           *pstLppTransIndex
)
{
    VOS_UINT8                                   ucSessionTransIndx  = 0;
    VOS_UINT8                                   ucSessionIndx       = 0;
    NAS_LPP_CONFIG_PARA_STRU                   *pstCfgPara          = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvLocationRequestHandle!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLocationRequestHandle_ENUM, LNAS_LPP_Func_Enter);

    pstCfgPara = NAS_LPP_GetCfgPara();

    /*
     协议约定，多个session或者一个session内部不能同时存在同一种定位技术的
     transaction正在runing，简言之，每当来了一个locationReq，遍历一遍所有
     session有没有正在running统一类型的定位计数，但是有一种场景，如果当前
     网络侧请求了两种定位技术，比如 OTDOA， ECID， 但是ECID 在另外一个session
     已经请求了， 那么本次请求就只做OTDOA的测量，如果OTDOA的测量现在也正在做
     那么直接回复网络侧abort即可
    */

    /*得到transaction的相关联的参数*/
    ucSessionTransIndx  = pstLppTransIndex->ucSessionTransIndx;

    /*获取sessionIndx*/
    ucSessionIndx = NAS_LPP_SearchSessionIndx(ulSessionId);
    if(PS_NULL_UINT8 == ucSessionIndx)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvLocationRequestHandle: Search session Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLocationRequestHandle_ENUM, LNAS_LPP_CanntGetSessionEntity);
        return;
    }

    /*保存下行sequenceNumber*/
    NAS_LPP_SetDownLinkMsgSequenceNum(ucSessionIndx,
                                      pstLppMsgHead->stSequenceNumber.ucSequenceNumber);

    /*配置ECID测量请求*/
    if(NAS_LPP_SLCT == pstCfgPara->bitEcidReq)
    {
        NAS_LPP_NORM_LOG("NAS_LPP_RcvLocationRequestHandle: Req Ecid Meas Info");
        TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLocationRequestHandle_ENUM, LNAS_LPP_ReqEcidMeasInfo);

        /*如果请求的ECID的位置测量信息，给LRRC发测量请求*/
        NAS_LPP_SndLppLrrcEcidMeasReq( ucSessionIndx, ucSessionTransIndx,LPP_LRRC_LCS_MEAS_CMD_SETUP);

        /*转状态到等待LRRC测量CNF*/
        NAS_LPP_ChangeTransFsmState(ucSessionIndx, ucSessionTransIndx, LPP_MS_LOCATION, LPP_SS_WAIT_LRRC_MEAS_CNF);

        pstCfgPara->bitEcidReq = NAS_LPP_NO_SLCT;
    }

    /*配置OTDOA测量请求*/
    if(NAS_LPP_SLCT == pstCfgPara->bitOtdoaReq)
    {
        NAS_LPP_RcvLocationReqForOtdoaHandle(ulSessionId, ucSessionIndx, ucSessionTransIndx);
    }

    /*配置GNSS测量请求*/
    if(NAS_LPP_SLCT == pstCfgPara->bitGnssReq)
    {
        /*迭代四再做，实现步骤如下:
        1. 发送GNSS测量请求给MTA
        2. 将当前的定位计数加1
        3. GNSS模块如果存在辅助数据，则会LPP发送meas IND，
        4. GNSS模块如果不存在辅助数据，则会给LPP发送辅助信息请求， LPP创建新的transaction去请求GNSS的辅助数据，
           此时对应的LOCATION的transaction不需要转成等待辅助信息完成，对于LPP来说，只要跟MTA发送完位置信息请求
           之后，直接等meas IND即可，无需关心中间的辅助信息过程
        */
        /*透传位置测量请求给MTA即可*/
        NAS_LPP_OmMtaLocInfoReq(ID_LPP_MTA_GNSS_LOC_INFO_REQ);
        NAS_LPP_SndLppMtaGnssMeasReq(ucSessionIndx, ucSessionTransIndx);

        /*转状态到等待MTA GNSS测量IND*/
        if((LPP_SS_WAIT_LRRC_MEAS_CNF != NAS_LPP_GetLppSubState(ucSessionIndx, ucSessionTransIndx))
           && (LPP_SS_WAIT_ASSISTDATA_REQ_PROCESS_CMP != NAS_LPP_GetLppSubState(ucSessionIndx, ucSessionTransIndx))
           && (LPP_SS_WAIT_ASSISTDATA_RCV_CMP != NAS_LPP_GetLppSubState(ucSessionIndx, ucSessionTransIndx)))
        {
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvLocationRequestHandle_ENUM, LNAS_LPP_AllPosTechStartMeas);
            NAS_LPP_ChangeTransFsmState(ucSessionIndx, ucSessionTransIndx, LPP_MS_LOCATION, LPP_SS_WAIT_MEAS_IND);
        }

        pstCfgPara->bitGnssReq = NAS_LPP_NO_SLCT;
    }

    TLPS_PRINT2LAYER_INFO1(NAS_LPP_RcvLocationRequestHandle_ENUM, LNAS_LPP_ReportType, NAS_LPP_GetSessionEntityReportType(ucSessionIndx,ucSessionTransIndx));

    /*根据不通的上报方式启动不同的定时器*/
    switch(NAS_LPP_GetSessionEntityReportType(ucSessionIndx,ucSessionTransIndx))
    {
        case NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER:

            /*如果持续时间是0，说明是不限定次数的上报*/
            if(0 == NAS_LPP_GetTimerLen(TI_NAS_LPP_REPORT_DURATION,ucSessionIndx,ucSessionTransIndx, NAS_LPP_UP_POS_REQ_TECH_TYPE_BUTT))
            {
                TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvLocationRequestHandle_ENUM, LNAS_LPP_ReportTypeTriggerNoLimitCnt);
                break;
            }

            /*否则需要启动启动duration定时器*/
            NAS_LPP_TimerStart(ucSessionIndx,
                               ucSessionTransIndx,
                               TI_NAS_LPP_REPORT_DURATION);
            break;

        case NAS_LPP_REPORT_LOCATION_TYPE_PERIOD:
            /*
            NAS_LPP_TimerStart(ucSessionIndx,
                               NAS_LPP_TIMER_INVAILD_PARA,
                               TI_NAS_LPP_PERIODICAL_REPORT);*/
            /*
            对于周期性定时器的启动，此时不启动，再存两种可能，
            1. 当前没有辅助数据，请求辅助
            2. 有辅助数据，等测量cnf
            对于上述两种情况统一在收到LRRC的测量回复的时候，启动
            周期性定时器
            */
            break;

        case NAS_LPP_REPORT_LOCATION_TYPE_ONCE:
            NAS_LPP_TimerStart(ucSessionIndx,
                               ucSessionTransIndx,
                               TI_NAS_LPP_RESPONSE_TIMER);
            break;

        default:
            NAS_LPP_ERR_LOG("NAS_LPP_RcvLocationRequestHandle: Error Report Type!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLocationRequestHandle_ENUM, LNAS_LPP_ReportTypeError);
            break;
    }

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvAortHandle
Description    : 处理网络侧下发的Abort的消息
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-7-24  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_RcvAortHandle
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppMsgHead,
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_INDEX_STRU           *pstLppTransIndex
)
{
    NAS_LPP_TRANS_ID_STRU stTransId;
    VOS_UINT8 ucSessionIndex;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvAortHandle!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvAortHandle_ENUM, LNAS_LPP_Func_Enter);

    ucSessionIndex = NAS_LPP_SearchSessionIndx(ulSessionId);
    if (PS_NULL_UINT8 == ucSessionIndex)
    {
        NAS_LPP_ERR_LOG1("rev abort with wrong session id", ulSessionId);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvAortHandle_ENUM, LNAS_LPP_CanntGetSessionEntity);
        return;
    }

    stTransId.enInitiator = pstLppMsgHead->stTransactionId.enInitiator;
    stTransId.ucTransactionNumber = pstLppMsgHead->stTransactionId.ucTransactionNumber;

    /*如果有上行LPP ACK发送 */
    if ( (NAS_LPP_SLCT == pstLppMsgHead->bitOpAcknowledgement)
       &&(PS_TRUE == pstLppMsgHead->stAcknowledgement.bAckRequested) )
    {
        NAS_LPP_ChangeTransFsmState(ucSessionIndex,
                                    pstLppTransIndex->ucSessionTransIndx,
                                    NAS_LPP_GetLppMainState(ucSessionIndex, pstLppTransIndex->ucSessionTransIndx),
                                    LPP_SS_WAIT_INTRA_DATA_CNF_OF_UP_LPP_ACK);
    }
    else
    {
        NAS_LPP_AbortAndErrorProcess(ucSessionIndex,
                                     pstLppTransIndex->ucSessionTransIndx,
                                     &stTransId);
    }

    return;
}


VOS_VOID  NAS_LPP_SndMtaResetGnssMeasAbortInd(VOS_VOID)
{
    LPP_MTA_GNSS_MEAS_ABORT_IND_STRU    *pstGnssMeasAbortInd  = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_SndMtaResetGnssMeasAbortInd!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndMtaResetGnssMeasAbortInd_ENUM, LNAS_LPP_Func_Enter);

    pstGnssMeasAbortInd = (LPP_MTA_GNSS_MEAS_ABORT_IND_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_MTA_GNSS_MEAS_ABORT_IND_STRU));
    if (NAS_LPP_NULL_PTR == pstGnssMeasAbortInd)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndMtaResetGnssMeasAbortInd_ENUM, LNAS_LPP_MallocMemFail);
        return;
    }

    NAS_LPP_MEM_SET_MSG(pstGnssMeasAbortInd, sizeof(LPP_MTA_GNSS_MEAS_ABORT_IND_STRU), 0, sizeof(LPP_MTA_GNSS_MEAS_ABORT_IND_STRU));

    /*消息头*/
    NAS_LPP_WRITE_MTA_MSG_HEAD(pstGnssMeasAbortInd, ID_LPP_MTA_GNSS_MEAS_ABORT_IND);

    NAS_LPP_SND_MSG(pstGnssMeasAbortInd);

    return;
}

/*****************************************************************************
Function Name   : NAS_LPP_GnssRcvAbortHandle
Description     : 收到GNSS abort的处理
Input           : None
Output          : None
Return          : VOS_VOID

History         :
1.lifuxin 00253982      2015-10-21  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_GnssRcvAbortHandle
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndx
)
{
    NAS_LPP_LOC_TECH_MAP_STRU          *pstLocTechMap   = NAS_LPP_NULL_PTR;
    NAS_LPP_NORM_LOG("NAS_LPP_GnssRcvAbortHandle!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_GnssRcvAbortHandle_ENUM, LNAS_LPP_Func_Enter);

    pstLocTechMap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_GNSS);
    if(NAS_LPP_NULL_PTR == pstLocTechMap)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_GnssRcvAbortHandle: Can't find the running table of GNSS");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_GnssRcvAbortHandle_ENUM, LNAS_LPP_CannotFindGnssRunningTable);

        return;
    }

    /*如果找到GNSS的对应的transaction，则说明网络侧想终止当前GNSS测量，发送abort给MTA*/
    if((pstLocTechMap->ucSessionIndx == ucSessionIndex)
       &&(pstLocTechMap->ucSessionTranIndx == ucSessionTransIndx))
    {
        NAS_LPP_SndMtaResetGnssMeasAbortInd();
    }

}

/*****************************************************************************
Function Name   : NAS_LPP_AbortAndErrorProcess
Description     :
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-9-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_AbortAndErrorProcess
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndx,
    NAS_LPP_TRANS_ID_STRU              *pstTransId
)
{
    NAS_LPP_INFO_LOG("NAS_LPP_AbortAndErrorProcess!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_AbortAndErrorProcess_ENUM, LNAS_LPP_Func_Enter);

    NAS_LPP_GnssRcvAbortHandle(ucSessionIndex, ucSessionTransIndx);

    if (PS_FALSE == NAS_LPP_IsThereOtherTransactionRunningInSession(ucSessionIndex, pstTransId) )
    {
        /*释放对应的 session*/
        NAS_LPP_ReleaseSessionEntityByIndex(ucSessionIndex);
    }
    else
    {
        /*只释放transaction*/
        NAS_LPP_ReleaseTransEntity(ucSessionIndex,ucSessionTransIndx);
    }
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvErrorHandle
Description    : 处理网络侧下发的Error消息的处理
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-7-24  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_RcvErrorHandle
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppMsgHead,
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_INDEX_STRU           *pstLppTransIndex
)
{
    NAS_LPP_TRANS_ID_STRU stTransId;
    VOS_UINT8 ucSessionIndex;

    NAS_LPP_WARN_LOG("NAS_LPP_RcvErrorHandle!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvErrorHandle_ENUM, LNAS_LPP_Func_Enter);

    ucSessionIndex = NAS_LPP_SearchSessionIndx(ulSessionId);

    stTransId.enInitiator = pstLppMsgHead->stTransactionId.enInitiator;
    stTransId.ucTransactionNumber = pstLppMsgHead->stTransactionId.ucTransactionNumber;

    /*如果有上行LPP ACK发送 */
    if ( (NAS_LPP_SLCT == pstLppMsgHead->bitOpAcknowledgement)
       &&(PS_TRUE == pstLppMsgHead->stAcknowledgement.bAckRequested) )
    {
        NAS_LPP_ChangeTransFsmState(ucSessionIndex,
                                    pstLppTransIndex->ucSessionTransIndx,
                                    NAS_LPP_GetLppMainState(ucSessionIndex, pstLppTransIndex->ucSessionTransIndx),
                                    LPP_SS_WAIT_INTRA_DATA_CNF_OF_UP_LPP_ACK);
    }
    else
    {
        NAS_LPP_AbortAndErrorProcess(ucSessionIndex,
                                     pstLppTransIndex->ucSessionTransIndx,
                                     &stTransId);
    }

return;
}

/*****************************************************************************
Function Name  : NAS_LPP_PassCheckLppDownLinkMsgHandle
Description    : 处理经过了各种检测之后的LPP空口消息
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_PassCheckLppDownLinkMsgHandle
(
    NAS_LPP_MSG_HEAD_STRU              *pstMsgHead,
    VOS_UINT32                          ulSessionId,
    VOS_UINT32                          ulMsgType,
    NAS_LPP_TRANS_INDEX_STRU           *pstLppTransIndex
)
{
    NAS_LPP_INFO_LOG1("NAS_LPP_PassCheckLppDownLinkMsgHandle: LppMsgType =!", ulMsgType);
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_PassCheckLppDownLinkMsgHandle_ENUM, LNAS_LPP_Func_Enter, ulMsgType);

    switch(ulMsgType)
    {
        case LPP_SUPPORT_MESSAGE_BODY_REQUEST_CAPABILITIES_CHOSEN:
            /*网络侧请求LPP能力信息处理*/
            NAS_LPP_RcvCapabitlityRequestHandle(pstMsgHead, ulSessionId, pstLppTransIndex);
            break;

        case LPP_SUPPORT_MESSAGE_BODY_PROVIDE_ASSISTANCE_DATA_CHOSEN:
            /*网络侧提供辅助信息的处理*/
            NAS_LPP_RcvAssistDataProvideHandle(pstMsgHead, ulSessionId, pstLppTransIndex);
            break;

        case LPP_SUPPORT_MESSAGE_BODY_REQUEST_LOCATION_INFO_CHOSEN:
            /*网络侧请求LPP位置信息处理*/
            NAS_LPP_RcvLocationRequestHandle(pstMsgHead, ulSessionId, pstLppTransIndex);
            break;

        case LPP_SUPPORT_MESSAGE_BODY_ABORT_CHOSEN:
            /*网络侧下发ABORT消息的处理*/
            NAS_LPP_RcvAortHandle(pstMsgHead, ulSessionId, pstLppTransIndex);
            break;

        case LPP_SUPPORT_MESSAGE_BODY_ERROR_CHOSEN:
            /*网络侧下发ERROR消息的处理*/
            NAS_LPP_RcvErrorHandle(pstMsgHead, ulSessionId, pstLppTransIndex);
            break;

        default:
            NAS_LPP_ERR_LOG("NAS_LPP_PassCheckLppDownLinkMsgHandle: Error DownLink Msg Type!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_PassCheckLppDownLinkMsgHandle_ENUM, LNAS_LPP_ErrorDownlinMsgType);
            break;
    }

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_NwMsgProcess
Description    : NAS_LPP_NwMsgProcess
Input          : pstLppMsg     下行LPP消息
              ulSessionId   下行LPP流程所在session的ID
Output         : VOS_VOID
Return Value   : VOS_VOID
History        :
  lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_UINT8 NAS_LPP_SndUplinkAckMsg
(
    NAS_LPP_MSG_HEAD_STRU              *pstMsgHead,
    VOS_UINT32                          ulSessionId
)
{
    VOS_UINT32                          ulLppMsgLen     = 0;
    VOS_UINT8                          *pucEncodeOutMsg = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_IDENTITY_STRU           stLppMsgIdentity = {0};
    VOS_UINT8                           ucRslt          = 0;

    NAS_LPP_WARN_LOG("NAS_LPP_SndUplinkAckMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndUplinkAckMsg_ENUM, LNAS_LPP_Func_Enter);

    /*分配编码之后码流的存储空间*/
    pucEncodeOutMsg = NAS_LPP_MEM_ALLOC(sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);
    if(NAS_LPP_NULL_PTR == pucEncodeOutMsg)
    {
        return NAS_LPP_FAILURE;
    }

    /*清空*/
    NAS_LPP_MEM_SET_S(pucEncodeOutMsg,sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN, 0, sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);

    ucRslt = NAS_LPP_EncodeAckMsgWithMsgIndentiy(pstMsgHead,
                                        &ulLppMsgLen,
                                        pucEncodeOutMsg,
                                        &stLppMsgIdentity,
                                        ulSessionId);
    if(NAS_LPP_SUCCESS != ucRslt)
    {
        NAS_LPP_MEM_FREE(pucEncodeOutMsg);
        return NAS_LPP_FAILURE;
    }

    /*HIDS air msg */
    NAS_LPP_SendOmtAirMsg(NAS_LPP_OMT_AIR_MSG_UP,
                          LNAS_LPP_ACK_UP,
                          ulLppMsgLen,
                          pucEncodeOutMsg);
    /*发送编码好的数据给网侧*/
    NAS_LPP_SendUplinkMsg(ulSessionId,
                          ulLppMsgLen,
                          pucEncodeOutMsg,
                          &stLppMsgIdentity);

    /*释放动态内存*/
    NAS_LPP_MEM_FREE(pucEncodeOutMsg);

    return NAS_LPP_SUCCESS;
}


/*****************************************************************************
Function Name   : NAS_LPP_NwMsgPreProcess
Description     : LPP消息的前一部分消息的处理
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-8-11  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_NwMsgPreProcess
(
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity,
    NAS_LPP_MSG_HEAD_STRU                   *pstMsgHead,
    VOS_UINT32                               ulSessionId,
    VOS_UINT32                               ulMsgType
)
{
    VOS_UINT32                          ulRslt          = 0;
    VOS_UINT32                          ucRslt          = 0;

    NAS_LPP_NORM_LOG("NAS_LPP_NwMsgPreProcess is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_NwMsgPreProcess_ENUM, LNAS_LPP_Func_Enter);

    /*首先看该条LPP消息有没有带对上行消息的ACK回复，如果是，则处理*/
    if((NAS_LPP_SLCT == pstMsgHead->bitOpAcknowledgement)
       && (NAS_LPP_SLCT == pstMsgHead->stAcknowledgement.bitOpAckIndicator))
    {
        /*带有上行消息的确认*/
        TLPS_PRINT2LAYER_WARNING(NAS_LPP_NwMsgPreProcess_ENUM, LNAS_LPP_DownlinkAckMsg);
        NAS_LPP_NwMsgWithAckIeHandle(pstMsgHead,
                                     ulSessionId);
    }

    if(NAS_LPP_NO_SLCT == pstMsgHead->bitOpLppMessageBody)
    {
        /*消息体不存在，则说明该条空口消息仅仅是ACK消息*/
        TLPS_PRINT2LAYER_WARNING(NAS_LPP_NwMsgPreProcess_ENUM, LNAS_LPP_DownlinkMsgNoLppMsgBody);
        return NAS_LPP_MSG_PROCESS_CMPL;
    }

    /*带有LPP消息body*/
    if((NAS_LPP_SLCT == pstMsgHead->bitOpAcknowledgement)
       && (PS_TRUE == pstMsgHead->stAcknowledgement.bAckRequested))
    {
        /*需要回复ACK消息*/
        ucRslt = NAS_LPP_SndUplinkAckMsg(pstMsgHead, ulSessionId);
        if(NAS_LPP_SUCCESS != ucRslt)
        {
            return NAS_LPP_MSG_PROCESS_CMPL;
        }

        pstTransEntity->enLastUpMsgId = NAS_LPP_AIR_MSG_UP_LPP_ACK;
    }

    if (NAS_LPP_NO_SLCT == pstMsgHead->bitOpSequenceNumber)
    {
        return NAS_LPP_SUCCESS;
    }
    /*重复消息检测*/
    ulRslt = NAS_LPP_MsgDuplicateDetect(ulSessionId,
                                        pstMsgHead->stSequenceNumber.ucSequenceNumber);
    if(NAS_LPP_SUCCESS != ulRslt)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_NwMsgProcess: Duplicate Lpp Msg!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_NwMsgPreProcess_ENUM, LNAS_LPP_DuplicateDetect);
        return NAS_LPP_MSG_PROCESS_CMPL;
    }

    return NAS_LPP_SUCCESS;
}


/*****************************************************************************
Function Name  : NAS_LPP_NwMsgProcess
Description    : NAS_LPP_NwMsgProcess
Input          : pstLppMsg     下行LPP消息
              ulSessionId   下行LPP流程所在session的ID
Output         : VOS_VOID
Return Value   : VOS_VOID
History        :
  lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_NwMsgProcess
(
NAS_LPP_MSG_HEAD_STRU              *pstMsgHead,
VOS_UINT32                          ulSessionId,
VOS_UINT32                          ulMsgType,
NAS_LPP_TRANS_INDEX_STRU           *pstLppTransIndex
)
{
    VOS_UINT8                   ucSessionIndx = 0;

    /*通过重复消息检测处理消息*/
    NAS_LPP_PassCheckLppDownLinkMsgHandle(pstMsgHead,
                                          ulSessionId,
                                          ulMsgType,
                                          pstLppTransIndex);

    ucSessionIndx = NAS_LPP_SearchSessionIndx(ulSessionId);
    if(PS_NULL_UINT8 != ucSessionIndx)
    {
        /*先停*/
        NAS_LPP_TimerStop(ucSessionIndx,
                           NAS_LPP_TIMER_INVAILD_PARA,
                           TI_NAS_LPP_SEQUENCE_NUMBER_INVALID);
        /*再起*/
        NAS_LPP_TimerStart(ucSessionIndx,
                           NAS_LPP_TIMER_INVAILD_PARA,
                           TI_NAS_LPP_SEQUENCE_NUMBER_INVALID);
    }

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_SaveDownLinkCapReqMsg
Description    : LPP模块收到下行空口消息的保存
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_UINT32  NAS_LPP_SaveDownLinkCapReqMsg
(
    LPP_MESSAGE_STRU                       *pstLppMsg,
    VOS_UINT8                               ucSessionIndx,
    VOS_UINT8                               ucTransIndx
)
{
    LPP_REQUEST_CAPABILITIES_R9_IES_STRU       *pstReqCapInfo       = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransElement     = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_SaveDownLinkCapReqMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveDownLinkCapReqMsg_ENUM, LNAS_LPP_Func_Enter);

    pstTransElement = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if ( NAS_LPP_NULL_PTR == pstTransElement)
    {
        NAS_LPP_ERR_LOG1("save capability with wrong index", ucTransIndx);
        return  NAS_LPP_MSG_PROCESS_CMPL;
    }

    pstReqCapInfo   = NAS_LPP_GetDownLinkCapReqIEAddr(pstLppMsg);

    pstTransElement->stCapReq.bitOpEcidCapReq   = pstReqCapInfo->bitOpECIDRequestCapabilities;
    pstTransElement->stCapReq.bitOpOtdoaCapReq  = pstReqCapInfo->bitOpOTDOARequestCapabilities;
    pstTransElement->stCapReq.bitOpAgnssCapReq  = pstReqCapInfo->bitOpAGNSSRequestCapabilities;

    if (NAS_LPP_SLCT==pstTransElement->stCapReq.bitOpAgnssCapReq)
    {
        pstTransElement->stCapReq.stGnssReqCap.bAssistanceDataSupportListReq = pstReqCapInfo->stAGNSSRequestCapabilities.bAssistanceDataSupportListReq;
        pstTransElement->stCapReq.stGnssReqCap.bGnssSupportListReq = pstReqCapInfo->stAGNSSRequestCapabilities.bGnssSupportListReq;
        pstTransElement->stCapReq.stGnssReqCap.blocationVelocityTypesReq = pstReqCapInfo->stAGNSSRequestCapabilities.blocationVelocityTypesReq;
    }
    return  NAS_LPP_MSG_VERIFY_SUCC;
}


/*****************************************************************************
Function Name   : NAS_LPP_SaveOtdoaRefCell
Description     : 存储otdoa的ref cell
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-8-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SaveOtdoaRefCell
(
LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU *pstOtdoaAssist,
NAS_LPP_SERVING_CELL_STRU          *pstServingCell,
NAS_LPP_OTDOA_ASSIST_CFG_STRU      *pstOtdoaAssisCfg
)
{
    LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU     *pstOtdoaRefCellCfg;
    LPP_OTDOA_REF_CELL_INFO_STRU                *pstOtdoaRefCellInfo;

    LPP_LRRC_OTDOA_ANT_PORT_CFG_ENUM_UINT8 aucAntennaPortConfig[LPP_LRRC_OTDOA_ANT_PORT_BUTT] =
                                    {LPP_LRRC_OTDOA_ANT_PORT_1_OR_2, LPP_LRRC_OTDOA_ANT_PORT_4};

    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_ENUM_UINT8 aucPrsMutType[LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_BUTT] =
                                    {LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO2,
                                     LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO4,
                                     LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO8,
                                     LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO16};

    LPP_LRRC_OTDOA_NUMDL_FRAMES_ENUM_UINT8 aucNumFrams[LPP_LRRC_OTDOA_NUMDL_FRAMES_BUTT] =
                                    {LPP_LRRC_OTDOA_NUMDL_FRAMES_1,
                                     LPP_LRRC_OTDOA_NUMDL_FRAMES_2,
                                     LPP_LRRC_OTDOA_NUMDL_FRAMES_4,
                                     LPP_LRRC_OTDOA_NUMDL_FRAMES_6};

    LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM_UINT8 aucBandWidth[LPP_LRRC_OTDOA_PRS_BANDWIDTH_BUTT] =
                                    {LPP_LRRC_OTDOA_PRS_BANDWIDTH_N6,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N15,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N25,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N50,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N75,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N100};

    LPP_LRRC_OTDOA_CP_TYPE_ENUM_UINT8 aucCpType[LPP_LRRC_OTDOA_CP_TYPE_BUTT] =
                                    {LPP_LRRC_OTDOA_CP_TYPE_NORMAL,
                                     LPP_LRRC_OTDOA_CP_TYPE_EXTENDED};

    NAS_LPP_NORM_LOG("NAS_LPP_SaveOtdoaRefCell enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveOtdoaRefCell_ENUM, LNAS_LPP_Func_Enter);

    if (NAS_LPP_NO_SLCT == pstOtdoaAssist->bitOpOtdoaReferenceCellInfo)
    {
        pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
        return;
    }

    pstOtdoaRefCellCfg  = &(pstOtdoaAssisCfg->stOtdoaReferenceCellInfo);
    pstOtdoaRefCellInfo = &(pstOtdoaAssist->stOtdoaRefCellInfo);

    pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag = LPP_LRRC_INFO_FLAG_VALID;

    pstOtdoaRefCellCfg->usPhyCellId = pstOtdoaRefCellInfo->usPhyCellId;
    pstOtdoaRefCellCfg->ucCpLen     = aucCpType[pstOtdoaRefCellInfo->enCpLength];

    if (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpCellGlobalId)
    {
        pstOtdoaRefCellCfg->ucCellGlobalIdFlag = LPP_LRRC_INFO_FLAG_VALID;
        pstOtdoaRefCellCfg->stCellGlobalIdInfo.ulCellIdentity = pstOtdoaRefCellInfo->stCellGlobalId.ulCellIdentity;

        /*两个之间的转换*/
        NAS_LPP_LppPlmn2NasPlmn( &pstOtdoaRefCellInfo->stCellGlobalId.stPlmnIdentity, pstOtdoaRefCellCfg->stCellGlobalIdInfo.aucPlmnId);
    }
    else
    {
        pstOtdoaRefCellCfg->ucCellGlobalIdFlag = LPP_LRRC_INFO_FLAG_INVALID;
    }

    pstOtdoaRefCellCfg->ulEarfcn = NAS_LPP_GetRefEarfcnFromOtdoaAssis(&(pstOtdoaAssist->stOtdoaRefCellInfo));

    if (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpAntennaPortConfig)
    {
        pstOtdoaRefCellCfg->ucAntennaPortConfigFlag = LPP_LRRC_INFO_FLAG_VALID;
        pstOtdoaRefCellCfg->ucAntennaPortConfig = aucAntennaPortConfig[pstOtdoaRefCellInfo->enAntennaPortConfig];
    }
    else
    {
        pstOtdoaRefCellCfg->ucAntennaPortConfigFlag = LPP_LRRC_INFO_FLAG_INVALID;
    }

    if (NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpPrsInfo)
    {
        pstOtdoaRefCellCfg->ucPrsInfoFlag = LPP_LRRC_INFO_FLAG_VALID;

        if ( (NAS_LPP_SLCT == pstOtdoaRefCellInfo->stPrsInfo.bitOpPrsMutingInfoR9 )
           &&(NAS_LPP_SLCT == pstOtdoaRefCellInfo->stPrsInfo.bitOpPrsInfoExt) )
        {
            pstOtdoaRefCellCfg->stPrsInfo.ucPrsMutingInfoFlag = LPP_LRRC_INFO_FLAG_VALID;

            pstOtdoaRefCellCfg->stPrsInfo.ucPrsMutingInfoType
                = aucPrsMutType[pstOtdoaRefCellInfo->stPrsInfo.stPrsMutingInfoR9.ulChoice];

            /*prs-MutingInfo-r9       CHOICE {
                    po2-r9                  BIT STRING (SIZE(2)),
                    po4-r9                  BIT STRING (SIZE(4)),
                    po8-r9                  BIT STRING (SIZE(8)),
                    po16-r9                 BIT STRING (SIZE(16)),
                    ...
                } 最长16bit，2个字节*/

           /*usPo2R9,usPo4R9,usPo8R9,usPo16R9都是16bit*/
           pstOtdoaRefCellCfg->stPrsInfo.usPrsMutingInfo = pstOtdoaRefCellInfo->stPrsInfo.stPrsMutingInfoR9.u.usPo2R9;
        }
        else
        {
            pstOtdoaRefCellCfg->stPrsInfo.ucPrsMutingInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
        }

        pstOtdoaRefCellCfg->stPrsInfo.ucPrsBandWidth = aucBandWidth[pstOtdoaRefCellInfo->stPrsInfo.enPrsBandWith];
        pstOtdoaRefCellCfg->stPrsInfo.ucNumdlFrames  = aucNumFrams[pstOtdoaRefCellInfo->stPrsInfo.enNumDlFrames];
        pstOtdoaRefCellCfg->stPrsInfo.usPrsConfigurationIndex = (VOS_UINT16)pstOtdoaRefCellInfo->stPrsInfo.ulPrsConfigIndex;
    }
    else
    {
        pstOtdoaRefCellCfg->ucPrsInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
    }
}

/*****************************************************************************
 Function Name   : NAS_LPP_SaveCellGlobalId
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SaveCellGlobalId
(
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg,
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement
)
{
    if (NAS_LPP_SLCT == pstNgnbrCellElement->bitOpCellGlobalId)
    {
        pstOtdoaNghbrCellCfg->ucCellGlobalIdFlag = LPP_LRRC_INFO_FLAG_VALID;
        pstOtdoaNghbrCellCfg->stCellGlobalIdInfo.ulCellIdentity = pstNgnbrCellElement->stCellGlobalId.ulCellIdentity;

        NAS_LPP_LppPlmn2NasPlmn(&pstNgnbrCellElement->stCellGlobalId.stPlmnIdentity,pstOtdoaNghbrCellCfg->stCellGlobalIdInfo.aucPlmnId);
    }
    else
    {
        pstOtdoaNghbrCellCfg->ucCellGlobalIdFlag = LPP_LRRC_INFO_FLAG_INVALID;
    }
}
/*****************************************************************************
 Function Name   : NAS_LPP_SaveCpLength
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SaveCpLength
(
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg,
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement,
    LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU     *pstOtdoaRefCellCfg
)
{

    LPP_LRRC_OTDOA_CP_TYPE_ENUM_UINT8 aucCpType[LPP_LRRC_OTDOA_CP_TYPE_BUTT] =
                                        {LPP_LRRC_OTDOA_CP_TYPE_NORMAL,
                                         LPP_LRRC_OTDOA_CP_TYPE_EXTENDED};

    if (NAS_LPP_SLCT == pstNgnbrCellElement->bitOpCpLength)
    {
        pstOtdoaNghbrCellCfg->ucCpLen = aucCpType[pstNgnbrCellElement->enCpLength];
    }
    else
    {
        /*The field is mandatory present if the cyclic prefix length is not the same as for the assistance data reference cell;
              otherwise it is not present.*/
        pstOtdoaNghbrCellCfg->ucCpLen = pstOtdoaRefCellCfg->ucCpLen;
    }
}
/*****************************************************************************
 Function Name   : NAS_LPP_SavePrs
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SavePrs
(
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg,
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement
)
{
    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_ENUM_UINT8 aucPrsMutType[LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_BUTT] =
                                    {LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO2,
                                     LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO4,
                                     LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO8,
                                     LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO16};

    LPP_LRRC_OTDOA_NUMDL_FRAMES_ENUM_UINT8 aucNumFrams[LPP_LRRC_OTDOA_NUMDL_FRAMES_BUTT] =
                                    {LPP_LRRC_OTDOA_NUMDL_FRAMES_1,
                                     LPP_LRRC_OTDOA_NUMDL_FRAMES_2,
                                     LPP_LRRC_OTDOA_NUMDL_FRAMES_4,
                                     LPP_LRRC_OTDOA_NUMDL_FRAMES_6};

    LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM_UINT8 aucBandWidth[LPP_LRRC_OTDOA_PRS_BANDWIDTH_BUTT] =
                                    {LPP_LRRC_OTDOA_PRS_BANDWIDTH_N6,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N15,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N25,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N50,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N75,
                                     LPP_LRRC_OTDOA_PRS_BANDWIDTH_N100};

    if (NAS_LPP_SLCT == pstNgnbrCellElement->bitOpPrsInfo)
    {
        pstOtdoaNghbrCellCfg->ucPrsInfoFlag = LPP_LRRC_INFO_FLAG_VALID;

        /*
            PRS-Info ::= SEQUENCE {
                prs-Bandwidth           ENUMERATED { n6, n15, n25, n50, n75, n100, ... },
                prs-ConfigurationIndex  INTEGER (0..4095),
                numDL-Frames            ENUMERATED {sf-1, sf-2, sf-4, sf-6, ...},
                ...,
                prs-MutingInfo-r9       CHOICE {
                    po2-r9                  BIT STRING (SIZE(2)),
                    po4-r9                  BIT STRING (SIZE(4)),
                    po8-r9                  BIT STRING (SIZE(8)),
                    po16-r9                 BIT STRING (SIZE(16)),
                    ...
                }                                                       OPTIONAL                -- Need OP
            }

        pstNgnbrCellElement->stPrsInfo.bitOpPrsInfoExt作用表示 "..."之后的是否有效 */

        if ( (NAS_LPP_SLCT == pstNgnbrCellElement->stPrsInfo.bitOpPrsMutingInfoR9)
            &&(NAS_LPP_SLCT == pstNgnbrCellElement->stPrsInfo.bitOpPrsInfoExt))
        {
            pstOtdoaNghbrCellCfg->stPrsInfo.ucPrsMutingInfoFlag = LPP_LRRC_INFO_FLAG_VALID;

            pstOtdoaNghbrCellCfg->stPrsInfo.ucPrsMutingInfoType = aucPrsMutType[pstNgnbrCellElement->stPrsInfo.stPrsMutingInfoR9.ulChoice];

            pstOtdoaNghbrCellCfg->stPrsInfo.usPrsMutingInfo = pstNgnbrCellElement->stPrsInfo.stPrsMutingInfoR9.u.usPo2R9;
        }
        else
        {
            pstOtdoaNghbrCellCfg->stPrsInfo.ucPrsMutingInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
        }

        pstOtdoaNghbrCellCfg->stPrsInfo.ucPrsBandWidth      = aucBandWidth[pstOtdoaNghbrCellCfg->stPrsInfo.ucPrsBandWidth];
        pstOtdoaNghbrCellCfg->stPrsInfo.ucNumdlFrames       = aucNumFrams[pstOtdoaNghbrCellCfg->stPrsInfo.ucNumdlFrames];
        pstOtdoaNghbrCellCfg->stPrsInfo.usPrsConfigurationIndex = (VOS_UINT16)pstNgnbrCellElement->stPrsInfo.ulPrsConfigIndex;

    }
    else
    {
        pstOtdoaNghbrCellCfg->ucPrsInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
    }
}

/*****************************************************************************
 Function Name   : NAS_LPP_SaveAntennaPort
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SaveAntennaPort
(
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg,
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement
)
{
    LPP_LRRC_OTDOA_ANT_PORT_CFG_ENUM_UINT8 aucAntennaPortConfig[LPP_LRRC_OTDOA_ANT_PORT_BUTT] =
                                    {LPP_LRRC_OTDOA_ANT_PORT_1_OR_2, LPP_LRRC_OTDOA_ANT_PORT_4};

    if (NAS_LPP_SLCT == pstNgnbrCellElement->bitOpAntennaPortconfig)
    {
        pstOtdoaNghbrCellCfg->ucAntennaPortConfigFlag = LPP_LRRC_INFO_FLAG_VALID;
        pstOtdoaNghbrCellCfg->ucAntennaPortConfig = aucAntennaPortConfig[pstNgnbrCellElement->enAntennaPortConfig];
    }
    else
    {
        pstOtdoaNghbrCellCfg->ucAntennaPortConfigFlag = LPP_LRRC_INFO_FLAG_INVALID;
    }
}

/*****************************************************************************
 Function Name   : NAS_LPP_SaveSlotNumOffset
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SaveSlotNumOffset
(
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg,
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement
)
{
    if (NAS_LPP_SLCT == pstNgnbrCellElement->bitOpSlotNumberOffset)
    {
        pstOtdoaNghbrCellCfg->ucSlotNumberOffsetFlag = LPP_LRRC_INFO_FLAG_VALID;

        pstOtdoaNghbrCellCfg->ucSlotNumberOffset = (VOS_UINT8)pstNgnbrCellElement->usSlotNumberOffset;
    }
    else
    {
        pstOtdoaNghbrCellCfg->ucSlotNumberOffsetFlag = LPP_LRRC_INFO_FLAG_INVALID;
    }
}

/*****************************************************************************
 Function Name   : NAS_LPP_SavePrsSubFrameOffset
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SavePrsSubFrameOffset
(
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg,
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement
)
{
    if (NAS_LPP_SLCT == pstNgnbrCellElement->bitOpPrsSubFrameOffset)
    {
        pstOtdoaNghbrCellCfg->ucPrsSubFramOffsettFlag = LPP_LRRC_INFO_FLAG_VALID;

        pstOtdoaNghbrCellCfg->usPrsSubframeOffset = pstNgnbrCellElement->usPrsSubframeOffset;
    }
    else
    {
        pstOtdoaNghbrCellCfg->ucPrsSubFramOffsettFlag = LPP_LRRC_INFO_FLAG_INVALID;
    }
}


/*****************************************************************************
Function Name   :
Description     : 存储otodoa的临区信息
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-8-20  Draft Enact

*****************************************************************************/
VOS_VOID   NAS_LPP_SaveOtdoaNghbrCell
(
LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU      *pstOtdoaAssist,
NAS_LPP_OTDOA_ASSIST_CFG_STRU           *pstOtdoaAssisCfg
)
{
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg;
    LPP_OTDOA_NEIGHOUR_CELL_INFO_STRU           *pstOtdoaNeighbourCellInfo;
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement;
    LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU     *pstOtdoaRefCellCfg;
    VOS_UINT32 ulLoop,i,ulFreqNum,ulCellNum;

    NAS_LPP_NORM_LOG("NAS_LPP_SaveOtdoaNghbrCell enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveOtdoaNghbrCell_ENUM, LNAS_LPP_Func_Enter);

    if (NAS_LPP_NO_SLCT == pstOtdoaAssist->bitOpOtdoaNeighbourCellInfo)
    {
        pstOtdoaAssisCfg->ucOtdoaNeighbourCellInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
        return;
    }

    pstOtdoaRefCellCfg = &(pstOtdoaAssisCfg->stOtdoaReferenceCellInfo);

    pstOtdoaNeighbourCellInfo = &(pstOtdoaAssist->stOtdoaNeighbourCellInfo);

    pstOtdoaAssisCfg->ucOtdoaNeighbourCellInfoFlag = LPP_LRRC_INFO_FLAG_VALID;

    pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.ulFreqInfoNum = pstOtdoaNeighbourCellInfo->ulOtdoaNeighbourCellInfoListCnt;
    ulFreqNum = pstOtdoaNeighbourCellInfo->ulOtdoaNeighbourCellInfoListCnt;
    for ( ulLoop = 0 ; ulLoop < ulFreqNum; ulLoop++ )
    {
        /*取每个频点第一个作为freq layer的freq*/
        if (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].bitOpEarfcn)
        {
            pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop].ulEarfcn
                = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].stEarfcn.ulArfcnValueEUTRA;
        }
        else if ( (NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].bitOpEarfcnV9a0)
                &&(NAS_LPP_SLCT == pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].stEarfcnv9a0.bitOpARFCNValueEutraV9A0) )
        {
            pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop].ulEarfcn
                = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[0].stEarfcnv9a0.ulArfcnValueEUTRAv9a0;
        }
        else
        {
            pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop].ulEarfcn = pstOtdoaRefCellCfg->ulEarfcn;
        }

        pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop].ulCellNum
            = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt;

        ulCellNum = pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].ulOtdoaNeighbourFreqInfoCnt;

        for ( i = 0 ; i < ulCellNum; i++ )
        {
            pstOtdoaNghbrCellCfg = &pstOtdoaAssisCfg->stOtdoaNeighbourCellInfo.stOtdoaNeighbourFreqInfoList[ulLoop].stOtdoaNeighbourCellInfoList[i];
            pstNgnbrCellElement  = &pstOtdoaNeighbourCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop].astOtdoaNeighbourFreqInfoArray[i];

            NAS_LPP_SaveCellGlobalId(pstOtdoaNghbrCellCfg,pstNgnbrCellElement);

            NAS_LPP_SaveCpLength(pstOtdoaNghbrCellCfg,pstNgnbrCellElement,pstOtdoaRefCellCfg);

            NAS_LPP_SavePrs(pstOtdoaNghbrCellCfg,pstNgnbrCellElement);

            NAS_LPP_SaveAntennaPort(pstOtdoaNghbrCellCfg,pstNgnbrCellElement);

            NAS_LPP_SaveSlotNumOffset(pstOtdoaNghbrCellCfg,pstNgnbrCellElement);

            NAS_LPP_SavePrsSubFrameOffset(pstOtdoaNghbrCellCfg,pstNgnbrCellElement);

            pstOtdoaNghbrCellCfg->usPhyCellId    = (VOS_UINT16)pstNgnbrCellElement->ulPhysCellId;
            pstOtdoaNghbrCellCfg->usExpectedRSTD = pstNgnbrCellElement->usExpectedRSTD;
            pstOtdoaNghbrCellCfg->usExpectedRSTDUncertainty = pstNgnbrCellElement->usExpectedRSTDUncertainty;
        }
    }

}

/*****************************************************************************
Function Name   : NAS_LPP_SaveOtdoaAssistData
Description     : 存储otdoa的辅助数据
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-8-13  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_SaveOtdoaAssistData
(
LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU *pstOtdoaAssist
)
{
    NAS_LPP_SERVING_CELL_STRU     *pstServingCell;
    NAS_LPP_OTDOA_ASSIST_CFG_STRU *pstOtdoaAssisCfg;

    NAS_LPP_NORM_LOG("NAS_LPP_SaveOtdoaAssistData enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveOtdoaAssistData_ENUM, LNAS_LPP_Func_Enter);

    pstServingCell = NAS_LPP_GetServingCell();
    pstOtdoaAssisCfg = NAS_LPP_GetOtdoaAssisCfg();

    /*如果有error，就不用处理后面的了,直接结束当前的OTDOA的辅助数据处理*/
    if (NAS_LPP_SLCT == pstOtdoaAssist->bitOpOtdoaError)
    {
        NAS_LPP_ERR_LOG1("otdoa error cause", pstOtdoaAssist->stOtdoaError.u.stLocationServerErrorCauses.enOtdoaLocationServerErrorCause);
        pstOtdoaAssisCfg->ucOtdoaReferenceCellInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
        pstOtdoaAssisCfg->ucOtdoaNeighbourCellInfoFlag = LPP_LRRC_INFO_FLAG_INVALID;
        return NAS_LPP_FAILURE;
    }

    NAS_LPP_SaveOtdoaRefCell(pstOtdoaAssist,pstServingCell,pstOtdoaAssisCfg);

    NAS_LPP_SaveOtdoaNghbrCell(pstOtdoaAssist,pstOtdoaAssisCfg);

    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
Function Name   : NAS_LPP_SaveGnssAssistData
Description     : 存储GNSS的辅助数据:不存储，直接透传给MTA，最后到GNSS芯片
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-8-13  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_SaveGnssAssistData
(
    LPP_AGNSS_PROVIDE_ASSIST_DATA_STRU *pstAgnssAssist,
    VOS_UINT8                           ucTransIndx
)
{
    LPP_MTA_GNSS_PROVIDE_ASSIST_DATA_CNF_STRU       *pstGnssAssistDataCnf = NAS_LPP_NULL_PTR;
    LPP_MTA_GNSS_PROVIDE_ASSIST_DATA_IND_STRU       *pstGnssAssistDataInd = NAS_LPP_NULL_PTR;
    LPP_MTA_AGNSS_PROVIDE_ASSIST_DATA_ELEMENT_STRU  *pstGnssProvideAssistData = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU         *pstTransEntity = NAS_LPP_NULL_PTR;
    LPP_MTA_GNSS_GENERIC_ASSIST_DATA_ELEMENT_STRU   *pastGNSSGenericAssistDataArray[LPP_MAX_VALID_GNSS_POSITION_TECH]={0};
    LPP_MTA_GNSS_DATA_BITS_SAT_ELEMENT_STRU         *pastGNSSDataBitsSatListArray[LPP_MAX_VALID_GNSS_POSITION_TECH][LPP_MAX_GNSS_SAT_CNT] = {{0}};
    LPP_GNSS_GENERIC_ASSIST_DATA_ELEMENT_STRU       *pstAirGNSSGenericAssistData;
    VOS_UINT32                                       ulLoop = 0,i = 0;

    NAS_LPP_NORM_LOG("NAS_LPP_SaveGnssAssistData enter");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveGnssAssistData_ENUM, LNAS_LPP_Func_Enter);

    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if (NAS_LPP_NULL_PTR == pstTransEntity)
    {
        NAS_LPP_ERR_LOG1("save gnss assist Data with warong trans index", ucTransIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SaveGnssAssistData_ENUM, LNAS_LPP_DontFindTransaction, ucTransIndx);
        return NAS_LPP_FAILURE;
    }

    if (LPP_INITIATOR_TYPE_TARGET_DEVICE == pstTransEntity->stTransId.enInitiator)
    {
        pstGnssAssistDataCnf = (LPP_MTA_GNSS_PROVIDE_ASSIST_DATA_CNF_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_MTA_GNSS_PROVIDE_ASSIST_DATA_CNF_STRU));
        if (NAS_LPP_NULL_PTR == pstGnssAssistDataCnf)
        {
            return NAS_LPP_FAILURE;
    }
        NAS_LPP_OmMtaAssistData(ID_LPP_MTA_GNSS_ASSISTDATA_CNF );
        NAS_LPP_MEM_SET_MSG(pstGnssAssistDataCnf, sizeof(LPP_MTA_GNSS_MEAS_ABORT_IND_STRU), 0, sizeof(LPP_MTA_GNSS_PROVIDE_ASSIST_DATA_CNF_STRU));
        NAS_LPP_WRITE_MTA_MSG_HEAD(pstGnssAssistDataCnf,ID_LPP_MTA_GNSS_ASSISTDATA_CNF);
        pstGnssProvideAssistData = &pstGnssAssistDataCnf->stGnssProvideAssistData;
    }
    else
    {
        pstGnssAssistDataInd = (LPP_MTA_GNSS_PROVIDE_ASSIST_DATA_IND_STRU *)NAS_LPP_ALLOC_MSG(sizeof(LPP_MTA_GNSS_PROVIDE_ASSIST_DATA_IND_STRU));
        if (NAS_LPP_NULL_PTR == pstGnssAssistDataInd)
        {
            NAS_LPP_ERR_LOG("save gnss assist Data ,malloc msg fail");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_SaveGnssAssistData_ENUM, LNAS_LPP_MallocMsgFail2);
            return NAS_LPP_FAILURE;
        }
        NAS_LPP_OmMtaAssistData(ID_LPP_MTA_GNSS_ASSISTDATA_IND );
        NAS_LPP_MEM_SET_MSG(pstGnssAssistDataInd, sizeof(LPP_MTA_GNSS_PROVIDE_ASSIST_DATA_IND_STRU), 0, sizeof(LPP_MTA_GNSS_PROVIDE_ASSIST_DATA_IND_STRU));
        NAS_LPP_WRITE_MTA_MSG_HEAD(pstGnssAssistDataInd,ID_LPP_MTA_GNSS_ASSISTDATA_IND);
        pstGnssProvideAssistData = &pstGnssAssistDataInd->stGnssProvideAssistData;
    }

    pstGnssProvideAssistData->bitOpAGnssProvideAssistDataExt = pstAgnssAssist->bitOpAGnssProvideAssistDataExt;
    pstGnssProvideAssistData->bitOpGNSSCommonAssitData = pstAgnssAssist->bitOpGNSSCommonAssitData;
    pstGnssProvideAssistData->bitOpGNSSError = pstAgnssAssist->bitOpGNSSError;
    pstGnssProvideAssistData->bitOpGNSSGenericAssitData = pstAgnssAssist->bitOpGNSSGenericAssitData;

    pstGnssProvideAssistData->stGNSSCommonAssistData = pstAgnssAssist->stGNSSCommonAssistData;
    pstGnssProvideAssistData->stGNSSError = pstAgnssAssist->stGNSSError;

    pstGnssProvideAssistData->stGNSSGenericAssitData.ulGNSSGenericAssitDataCnt = pstAgnssAssist->stGNSSGenericAssitData.ulGNSSGenericAssitDataCnt;
    if (LPP_MAX_VALID_GNSS_POSITION_TECH < pstGnssProvideAssistData->stGNSSGenericAssitData.ulGNSSGenericAssitDataCnt)
    {
        pstGnssProvideAssistData->stGNSSGenericAssitData.ulGNSSGenericAssitDataCnt = LPP_MAX_VALID_GNSS_POSITION_TECH;
    }

    for ( ulLoop = 0 ; ulLoop < pstGnssProvideAssistData->stGNSSGenericAssitData.ulGNSSGenericAssitDataCnt; ulLoop++ )
    {
        pastGNSSGenericAssistDataArray[ulLoop] = (LPP_MTA_GNSS_GENERIC_ASSIST_DATA_ELEMENT_STRU *)NAS_LPP_MEM_ALLOC( sizeof(LPP_MTA_GNSS_GENERIC_ASSIST_DATA_ELEMENT_STRU) );
        if (NAS_LPP_NULL_PTR == pastGNSSGenericAssistDataArray[ulLoop])
        {
            break;
        }
        pstGnssProvideAssistData->stGNSSGenericAssitData.pastGNSSGenericAssistDataArray[ulLoop] = pastGNSSGenericAssistDataArray[ulLoop];
        pstAirGNSSGenericAssistData = &pstAgnssAssist->stGNSSGenericAssitData.astGNSSGenericAssistDataArray[ulLoop];

        pastGNSSGenericAssistDataArray[ulLoop]->bitOpGNSSAcqAssit = pstAirGNSSGenericAssistData->bitOpGNSSAcqAssit;
        pastGNSSGenericAssistDataArray[ulLoop]->bitOpGNSSAlmanac = pstAirGNSSGenericAssistData->bitOpGNSSAlmanac;
        pastGNSSGenericAssistDataArray[ulLoop]->bitOpGNSSAuxInfo = pstAirGNSSGenericAssistData->bitOpGNSSAuxInfo;
        pastGNSSGenericAssistDataArray[ulLoop]->bitOpGNSSDataBitAssit = pstAirGNSSGenericAssistData->bitOpGNSSDataBitAssit;
        pastGNSSGenericAssistDataArray[ulLoop]->bitOpGNSSDiffCorrection = pstAirGNSSGenericAssistData->bitOpGNSSDiffCorrection;
        pastGNSSGenericAssistDataArray[ulLoop]->bitOpGNSSGenericAssistDataElementExt = pstAirGNSSGenericAssistData->bitOpGNSSGenericAssistDataElementExt;
        pastGNSSGenericAssistDataArray[ulLoop]->bitOpGNSSNavigationModel = pstAirGNSSGenericAssistData->bitOpGNSSNavigationModel;
        pastGNSSGenericAssistDataArray[ulLoop]->bitOpGNSSRealTimeIntegrity = pstAirGNSSGenericAssistData->bitOpGNSSRealTimeIntegrity;
        pastGNSSGenericAssistDataArray[ulLoop]->bitOpGNSSTimeModelIs = pstAirGNSSGenericAssistData->bitOpGNSSTimeModelIs;
        pastGNSSGenericAssistDataArray[ulLoop]->bitOpGNSSUtcModel = pstAirGNSSGenericAssistData->bitOpGNSSUtcModel;
        pastGNSSGenericAssistDataArray[ulLoop]->bitOpSbasId = pstAirGNSSGenericAssistData->bitOpSbasId;

        pastGNSSGenericAssistDataArray[ulLoop]->stGNSSId = pstAirGNSSGenericAssistData->stGNSSId;
        pastGNSSGenericAssistDataArray[ulLoop]->stSbasId = pstAirGNSSGenericAssistData->stSbasId;
        pastGNSSGenericAssistDataArray[ulLoop]->stGNSSTimeModels = pstAirGNSSGenericAssistData->stGNSSTimeModels;
        pastGNSSGenericAssistDataArray[ulLoop]->stGNSSDiffCorrect = pstAirGNSSGenericAssistData->stGNSSDiffCorrect;
        pastGNSSGenericAssistDataArray[ulLoop]->stGNSSNavigationModel = pstAirGNSSGenericAssistData->stGNSSNavigationModel;
        pastGNSSGenericAssistDataArray[ulLoop]->stGNSSRealTimeIntergrity = pstAirGNSSGenericAssistData->stGNSSRealTimeIntergrity;

        pastGNSSGenericAssistDataArray[ulLoop]->stGNSSAcquisitAssit = pstAirGNSSGenericAssistData->stGNSSAcquisitAssit;
        pastGNSSGenericAssistDataArray[ulLoop]->stGNSSAlmanac = pstAirGNSSGenericAssistData->stGNSSAlmanac;
        pastGNSSGenericAssistDataArray[ulLoop]->stGNSSUtcModel = pstAirGNSSGenericAssistData->stGNSSUtcModel;
        pastGNSSGenericAssistDataArray[ulLoop]->stGNSSAuxInfo = pstAirGNSSGenericAssistData->stGNSSAuxInfo;


        pastGNSSGenericAssistDataArray[ulLoop]->stGNSSDataBitAssistance.bitOpGNSSDataBitAssistExt
                = pstAirGNSSGenericAssistData->stGNSSDataBitAssistance.bitOpGNSSDataBitAssistExt;

        pastGNSSGenericAssistDataArray[ulLoop]->stGNSSDataBitAssistance.bitOpGNSSTodFrac
                = pstAirGNSSGenericAssistData->stGNSSDataBitAssistance.bitOpGNSSTodFrac;

        pastGNSSGenericAssistDataArray[ulLoop]->stGNSSDataBitAssistance.usGNSSTod
                = pstAirGNSSGenericAssistData->stGNSSDataBitAssistance.usGNSSTod;

        pastGNSSGenericAssistDataArray[ulLoop]->stGNSSDataBitAssistance.usGNSSTodFrac
                = pstAirGNSSGenericAssistData->stGNSSDataBitAssistance.usGNSSTodFrac;

        for ( i = 0 ; i < pstAirGNSSGenericAssistData->stGNSSDataBitAssistance.stGNSSDataBitsSatlist.ulGNSSDataBitsSatListCnt; i++ )
        {
            pastGNSSDataBitsSatListArray[ulLoop][i] = (LPP_MTA_GNSS_DATA_BITS_SAT_ELEMENT_STRU *)NAS_LPP_MEM_ALLOC( sizeof(LPP_MTA_GNSS_DATA_BITS_SAT_ELEMENT_STRU) );
            if (NAS_LPP_NULL_PTR == pastGNSSDataBitsSatListArray[ulLoop][i])
            {
                break;
            }
            pastGNSSGenericAssistDataArray[ulLoop]->stGNSSDataBitAssistance.stGNSSDataBitsSatlist.pastGNSSDataBitsSatListArray[i]
                = pastGNSSDataBitsSatListArray[ulLoop][i];

            NAS_LPP_MEM_CPY_S(pastGNSSDataBitsSatListArray[ulLoop][i],
                            sizeof(LPP_MTA_GNSS_DATA_BITS_SAT_ELEMENT_STRU),
                            &pstAirGNSSGenericAssistData->stGNSSDataBitAssistance.stGNSSDataBitsSatlist.astGNSSDataBitsSatListArray[i],
                            sizeof(LPP_MTA_GNSS_DATA_BITS_SAT_ELEMENT_STRU));
        }

        if ( i < pstAirGNSSGenericAssistData->stGNSSDataBitAssistance.stGNSSDataBitsSatlist.ulGNSSDataBitsSatListCnt )
        {
            break;
        }

    }
    /*lint -e613*/
    if (LPP_INITIATOR_TYPE_TARGET_DEVICE == pstTransEntity->stTransId.enInitiator)
    {
        NAS_LPP_SND_MSG(pstGnssAssistDataCnf);/* [false alarm]:代码保证不会访问空指针 */
    }
    else
    {
        NAS_LPP_SND_MSG(pstGnssAssistDataInd);/* [false alarm]:代码保证不会访问空指针 */
    }
    /*lint +e613*/
    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
Function Name  : NAS_LPP_SaveDownLinkAssistDataProvideMsg
Description    : LPP模块收到下行空口消息的保存
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-7-13  新开发
  xiaojun 2015-8-14
*****************************************************************************/
VOS_UINT32  NAS_LPP_SaveDownLinkAssistDataProvideMsg
(
    LPP_MESSAGE_STRU                       *pstLppMsg,
    VOS_UINT8                               ucSessionIndx,
    VOS_UINT8                               ucSessionTransIndx,
    VOS_UINT8                               ucTransIndx
)
{
    LPP_PROVIDE_ASSIST_DATA_R9_IES_STRU        *pstProvideAssitDataR9;
    NAS_LPP_CONFIG_PARA_STRU                   *pstCfgPara;
    NAS_LPP_LOC_TECH_MAP_STRU                  *pstTechMap;
    VOS_UINT32 ulRslt;

    NAS_LPP_NORM_LOG("NAS_LPP_SaveDownLinkAssistDataProvideMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveDownLinkAssistDataProvideMsg_ENUM, LNAS_LPP_Func_Enter);

    pstProvideAssitDataR9 = &(pstLppMsg->stLppMessageBody.u.stC1.u.stProvideAssistanceData.u.stC1.u.stProvideAssitDataR9);

    pstCfgPara = NAS_LPP_GetCfgPara();

    if (NAS_LPP_SLCT == pstProvideAssitDataR9->bitOpOTDOAProvideAssistData)
    {
        /*如果是transaction里收到的第一条otdoa 的assist data，要把以前的otdoa的参数先删除  */
        if (NAS_LPP_NO_SLCT == pstCfgPara->bitOtdoaAssisChng)
        {
            NAS_LPP_MEM_SET_S(&pstCfgPara->stOtdoaAssisCfg,sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU), 0, sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU));
        }

        ulRslt = NAS_LPP_SaveOtdoaAssistData(&pstProvideAssitDataR9->stOTDOAProvideAssistanceData);
        if (NAS_LPP_SUCCESS == ulRslt)
        {
            pstCfgPara->bitOtdoaAssisChng = NAS_LPP_SLCT;
        }
        else
        {
            /*只有协议带otdoa error的情况才会返回save error,所以，不退出，继续处理gnss的*/
            pstCfgPara->bitOtdoaAssisChng = NAS_LPP_NO_SLCT;
            NAS_LPP_MEM_SET_S(&pstCfgPara->stOtdoaAssisCfg, sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU),0, sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU));

            NAS_LPP_ERR_LOG("save otdoa error");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_SaveDownLinkAssistDataProvideMsg_ENUM, LNAS_LPP_SaveOtdoaAssistFail);

            /*如果有otdoa的测量，释放otdoa的测量,不等cnf了*/
            pstTechMap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);
            if (NAS_LPP_NULL_PTR != pstTechMap)
            {
                NAS_LPP_ReleasePosTechMeas(pstTechMap->ucSessionIndx,pstTechMap->ucSessionTranIndx,NAS_LPP_POSITION_TECH_OTDOA);
            }
        }
    }

    if (NAS_LPP_SLCT == pstProvideAssitDataR9->bitOpAGNSSProvideAssistData)
    {
        ulRslt = NAS_LPP_SaveGnssAssistData(&pstProvideAssitDataR9->stAGNSSProvideAssistanceData,ucTransIndx);
        if (NAS_LPP_SUCCESS == ulRslt)
        {
            pstCfgPara->bitGnssAssisChng = NAS_LPP_SLCT;
        }
        else
        {
            NAS_LPP_ERR_LOG("save gnss assist error");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_SaveDownLinkAssistDataProvideMsg_ENUM, LNAS_LPP_SaveGnssAssistFail);
            return ulRslt;
        }
    }

    return NAS_LPP_MSG_VERIFY_SUCC;
}

/*****************************************************************************
Function Name   : NAS_LPP_SaveCommCfgInfo
Description     :
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-8-7  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SaveCommCfgInfo
(
    LPP_COMMON_IES_REQ_LOCATION_INFO_STRU   *pstCommonIEsReqLocationInfo,
    NAS_LPP_COMM_CONFIG_INFO_STRU           *pstLppCommCfgInfo
)
{
    VOS_UINT8 aucRptAmnt[LPP_REPORT_AMOUNT_BUTT] = {1,2,4,8,16,32,64,0};
    VOS_UINT32 aulRptIntvl[LPP_REPORT_INTERVAL_BUTT] = {0,1000,2000,4000,8000,10000,16000,20000,32000,64000};
    LPP_LRRC_OTDOA_RPRT_INTERVAL_ENUM_UINT16  aenRptIntvl[LPP_REPORT_INTERVAL_BUTT] =
    {   LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_1, /* 此对应LPP空口消息对应LPP_REPORT_INTERVAL_NO_PERIOD_REPORT的情形，仅做保护*/
        LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_1, LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_2,
        LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_4, LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_8,
        LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_10,LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_16,
        LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_20,LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_32,
        LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_64
    };

    NAS_LPP_NORM_LOG("NAS_LPP_SaveCommCfgInfo enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveCommCfgInfo_ENUM, LNAS_LPP_Func_Enter);

    /*存储qos*/
    if (NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->bitOpQos)
    {
        pstLppCommCfgInfo->bitOpQos = NAS_LPP_SLCT;
        NAS_LPP_MEM_CPY_S(&pstLppCommCfgInfo->stQos, sizeof(LPP_MTA_COMMON_QOS_STRU),&pstCommonIEsReqLocationInfo->stQos, sizeof(LPP_MTA_COMMON_QOS_STRU));
    }

    /*存储environment*/
    if ( NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->bitOpEnvironment )
    {
        pstLppCommCfgInfo->enEnvironment = pstCommonIEsReqLocationInfo->enEnvironment;
    }
    else
    {
        pstLppCommCfgInfo->enEnvironment = LPP_ENVIRONMENT_BUTT;
    }

    /*存储additional*/
    if ( NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->bitOPAddtionInfo )
    {
        pstLppCommCfgInfo->enAdditonInfo = pstCommonIEsReqLocationInfo->enAdditonInfo;
    }
    else
    {
        pstLppCommCfgInfo->enAdditonInfo = LPP_ADDITON_REPORT_ONLY_RETURN_INFO_REQ;
    }

    pstLppCommCfgInfo->enLocationInformationType = pstCommonIEsReqLocationInfo->enLocationInformationType;

    /*存储bitOpLocationCoordinateType*/
    pstLppCommCfgInfo->bitOpLocationCoordinateType = pstCommonIEsReqLocationInfo->bitOpLocationCoordinateType;
    if ( NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->bitOpLocationCoordinateType )
    {
        NAS_LPP_MEM_CPY_S(&pstLppCommCfgInfo->stLocationCoordinateType,
                        sizeof(LPP_MTA_COMMON_LOCATION_COORDINATE_TYPE_STRU),
                        &pstCommonIEsReqLocationInfo->stLocationCoordinateType,
                        sizeof(LPP_MTA_COMMON_LOCATION_COORDINATE_TYPE_STRU));
    }

    /*存储bitOPVelocityTypes*/
    pstLppCommCfgInfo->bitOPVelocityTypes = pstCommonIEsReqLocationInfo->bitOPVelocityTypes;
    if ( NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->bitOPVelocityTypes )
    {
        NAS_LPP_MEM_CPY_S(&pstLppCommCfgInfo->stVeloctytype,
                        sizeof(LPP_MTA_COMMON_VELOCITY_TYPE_STRU),
                        &pstCommonIEsReqLocationInfo->stVeloctytype,
                        sizeof(LPP_MTA_COMMON_VELOCITY_TYPE_STRU));
    }

    /*存储上报准则: 按照上报的优先级,period>response>triger*/
    if (NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->bitOpPeriodicalReportCriteria)
    {
        pstLppCommCfgInfo->stReportCriteria.enType = NAS_LPP_REPORT_LOCATION_TYPE_PERIOD;
        pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.stLppTimer.enTimerId = TI_NAS_LPP_PERIODICAL_REPORT;

        pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.ucReportAmount
            = aucRptAmnt[pstCommonIEsReqLocationInfo->stPeriodReport.enReportAmount];

        pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.ulReportIntraval
            = aulRptIntvl[pstCommonIEsReqLocationInfo->stPeriodReport.enReportInterval];

        pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.enOtdoaRprtInterval
            = aenRptIntvl[pstCommonIEsReqLocationInfo->stPeriodReport.enReportInterval];
    }
    else if ( (NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->bitOpQos)
            &&(NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->stQos.bitOpResponseTime))
    {
        pstLppCommCfgInfo->stReportCriteria.enType = NAS_LPP_REPORT_LOCATION_TYPE_ONCE;
        pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.stLppTimer.enTimerId = TI_NAS_LPP_RESPONSE_TIMER;

        pstLppCommCfgInfo->stReportCriteria.u.stReportOnce.ulResponseTime
            = (VOS_UINT32)(pstCommonIEsReqLocationInfo->stQos.stResponseTime.ucTime) *1000;/*s转成ms*/
    }
    else if (NAS_LPP_SLCT == pstCommonIEsReqLocationInfo->bitOpTriggeredReportCriteria)
    {
        pstLppCommCfgInfo->stReportCriteria.enType = NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER;
        pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.stLppTimer.enTimerId = TI_NAS_LPP_REPORT_DURATION;

        pstLppCommCfgInfo->stReportCriteria.u.stReportTrigger.ulReportDuration
            = (VOS_UINT32)(pstCommonIEsReqLocationInfo->stTriggerReportCriteria.ulReportDuration) *1000;/*s转成ms*/
    }
    else
    {
        NAS_LPP_ERR_LOG("no report criteria");
    }

}

/*****************************************************************************
Function Name  : NAS_LPP_CheckUPrunningEcidPosTech
Description    : LPP 用户面下ECID是否在执行，如果执行就清空
Input          : VOS_VOID
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  WANGENSHENG 00324863 2015-12-2  新开发
  lifuxin  2015-12-7              逻辑修改
*****************************************************************************/
VOS_VOID NAS_LPP_CheckUPrunningPosTech
(
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    LPP_REQ_LOCATION_INFO_R9_IES_STRU       *pstReqLocationInfo  = NAS_LPP_NULL_PTR;
    NAS_LPP_USER_PLANE_ENTITY_STRU          *pstLppUPEntity      = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_CheckOtdoaDownLinkMsg is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_CheckOtdoaDownLinkMsg_ENUM, LNAS_LPP_Func_Enter);

    pstLppUPEntity      = NAS_LPP_GetLppUpEntityCtx();
    pstReqLocationInfo  = NAS_LPP_GetDownLinkLocationReqIEAddr(pstLppMsg);

    if ((NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID != pstLppUPEntity->stEcidUpEntity.enReqPosTechType)
        && (NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA != pstLppUPEntity->stEcidUpEntity.enReqPosTechType)
        && (PS_TRUE != pstLppUPEntity->stMultiPosTechEntity.bReqEcidAndOtdoaFlag))
    {
        /*如果用户面没有流程正在running，无需检查，直接返回*/
        return;
    }

    /* 用户面同时请求两种定位技术时 */
    if (PS_TRUE == pstLppUPEntity->stMultiPosTechEntity.bReqEcidAndOtdoaFlag)
    {
        if ((NAS_LPP_SLCT == pstReqLocationInfo->bitOpEcidReqLocationInfo)
          ||(NAS_LPP_SLCT == pstReqLocationInfo->bitOpOtdoaReqLocationInfo))
        {
            NAS_LPP_SndUpLppMtaEcidAndOtodaMeasmentInd(LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_REQ_MEAS_NOT_AVAIL,
                                                       LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_UNABLE_TO_MEAS_ANY_NEIGHBOUR_CELL);
            NAS_LPP_UPClrEntity();
        }
    }

    /* 用户面ECID冲突时 */
    if (NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == pstLppUPEntity->stEcidUpEntity.enReqPosTechType)
    {
        if (NAS_LPP_SLCT == pstReqLocationInfo->bitOpEcidReqLocationInfo)
        {
            NAS_LPP_UPClrEcidCtx();
            NAS_LPP_SndUpLppMtaEcidMeasmentInd(LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_REQ_MEAS_NOT_AVAIL);
        }
    }

    /* 用户面OTDOA冲突时 */
    if (NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == pstLppUPEntity->stOtdoaUpEntity.enReqPosTechType)
    {
        if (NAS_LPP_SLCT == pstReqLocationInfo->bitOpEcidReqLocationInfo)
        {
            NAS_LPP_UPClrOtdoaCtx();
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_CheckOtdoaDownLinkMsg_ENUM, LNAS_LPP_CheckEcidDownLinkMsgCLROTDOA);
            NAS_LPP_SndUpLppMtaOtdoaMeasmentInd(LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_UNABLE_TO_MEAS_REF_CELL);
        }
    }

}

/*****************************************************************************
Function Name  : NAS_LPP_SaveDownLinkLoctionReqMsg
Description    : LPP模块收到下行空口消息的保存
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  wangensheng 00324863 2015-12-16  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_SaveRunTechInfo
(
    LPP_MESSAGE_STRU                           *pstLppMsg,
    VOS_UINT8                                   ucSessionIndx,
    VOS_UINT8                                   ucSessionTransIndx,
    VOS_UINT8                                   ucTransIndx
)
{
    LPP_REQ_LOCATION_INFO_R9_IES_STRU          *pstReqLocationInfo  = NAS_LPP_NULL_PTR;
    NAS_LPP_LOCATION_REQ_STRU                  *pstLocationReqBuff  = NAS_LPP_NULL_PTR;
    NAS_LPP_CONFIG_PARA_STRU                   *pstConfigPara       = NAS_LPP_NULL_PTR;

    /*保存NW请求位置相关信息，以备后用*/
    pstReqLocationInfo  = NAS_LPP_GetDownLinkLocationReqIEAddr(pstLppMsg);
    pstLocationReqBuff  = NAS_LPP_GetLocationReqBuff();
    pstConfigPara = NAS_LPP_GetCfgPara();

    if(NAS_LPP_SLCT == pstReqLocationInfo->bitOpEcidReqLocationInfo)
    {
        pstLocationReqBuff->bitOpEcidLocReq  = NAS_LPP_SLCT;
        NAS_LPP_MEM_CPY_S(  &(pstLocationReqBuff->stEcidReqLocationInfo),
                            sizeof(LPP_ECID_REQ_LOCATION_INFO_STRU),
                            &(pstReqLocationInfo->stEcidReqLocationInfo),
                            sizeof(LPP_ECID_REQ_LOCATION_INFO_STRU));
        pstConfigPara->bitEcidReq = NAS_LPP_SLCT;
    }

    if(NAS_LPP_SLCT == pstReqLocationInfo->bitOpOtdoaReqLocationInfo)
    {
        pstLocationReqBuff->bitOpOtdoaLocReq = NAS_LPP_SLCT;
        NAS_LPP_MEM_CPY_S(  &(pstLocationReqBuff->stOtdoaReqLocationInfo),
                            sizeof(LPP_OTDOA_REQ_LOCATION_INFO_STRU),
                            &(pstReqLocationInfo->stOtdoaReqLocationInfo),
                            sizeof(LPP_OTDOA_REQ_LOCATION_INFO_STRU));
        pstConfigPara->bitOtdoaReq = NAS_LPP_SLCT;
    }

    if(NAS_LPP_SLCT == pstReqLocationInfo->bitOpAGNSSReqLocationInfo)
    {
        pstLocationReqBuff->bitOpAgnssLocReq = NAS_LPP_SLCT;
        NAS_LPP_MEM_CPY_S(  &(pstLocationReqBuff->stAGNSSReqLocationInfo),
                            sizeof(LPP_AGNSS_REQ_LOCATION_INFO_STRU),
                            &(pstReqLocationInfo->stAGNSSReqLocationInfo),
                            sizeof(LPP_AGNSS_REQ_LOCATION_INFO_STRU));
        pstConfigPara->bitGnssReq = NAS_LPP_SLCT;
    }

    /*保存当前有效的定位技术*/
    if(NAS_LPP_SLCT == pstReqLocationInfo->bitOpEcidReqLocationInfo)
    {
        NAS_LPP_AddRunningPositionTech(NAS_LPP_POSITION_TECH_ECID,ucSessionIndx,ucSessionTransIndx,ucTransIndx);
    }

    if(NAS_LPP_SLCT == pstReqLocationInfo->bitOpOtdoaReqLocationInfo)
    {
        NAS_LPP_AddRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA,ucSessionIndx,ucSessionTransIndx,ucTransIndx);

    }

    if(NAS_LPP_SLCT == pstReqLocationInfo->bitOpAGNSSReqLocationInfo)
    {
        NAS_LPP_AddRunningPositionTech(NAS_LPP_POSITION_TECH_GNSS,ucSessionIndx,ucSessionTransIndx,ucTransIndx);
    }
}
/*****************************************************************************
Function Name  : NAS_LPP_SaveDownLinkLoctionReqMsg
Description    : LPP模块收到下行空口消息的保存
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_UINT32  NAS_LPP_SaveDownLinkLoctionReqMsg
(
    LPP_MESSAGE_STRU                       *pstLppMsg,
    VOS_UINT8                               ucSessionIndx,
    VOS_UINT8                               ucSessionTransIndx,
    VOS_UINT8                               ucTransIndx
)
{
    LPP_REQ_LOCATION_INFO_R9_IES_STRU          *pstReqLocationInfo  = NAS_LPP_NULL_PTR;
    NAS_LPP_LOCATION_REQ_STRU                  *pstLocationReqBuff  = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransElement     = NAS_LPP_NULL_PTR;
    NAS_LPP_COMM_CONFIG_INFO_STRU              *pstLppCommCfgInfo   = NAS_LPP_NULL_PTR;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU        *pstSessionEntity    = NAS_LPP_NULL_PTR;
    NAS_LPP_CONFIG_PARA_STRU                   *pstConfigPara       = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_HEAD_STRU                       stMsgHead;
    NAS_LPP_LOC_TECH_RUNING_STRU               *pstRunLocTech;
    VOS_UINT32 ulLoop;
    VOS_UINT8 ucIndex;

    NAS_LPP_NORM_LOG("NAS_LPP_SaveDownLinkLoctionReqMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveDownLinkLoctionReqMsg_ENUM, LNAS_LPP_Func_Enter);

    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if(NAS_LPP_NULL_PTR  == pstSessionEntity)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SaveDownLinkLoctionReqMsg_ENUM, LNAS_LPP_CanntGetSessionEntity);
        return NAS_LPP_MSG_VERIFY_FAIL;
    }

    pstTransElement = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if ( NAS_LPP_NULL_PTR == pstTransElement)
    {
        NAS_LPP_ERR_LOG1("save request with wrong index", ucTransIndx);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SaveDownLinkLoctionReqMsg_ENUM, LNAS_LPP_DontFindTransaction);
        return  NAS_LPP_MSG_VERIFY_FAIL;
    }

    /*保存NW请求位置相关信息，以备后用*/
    pstReqLocationInfo  = NAS_LPP_GetDownLinkLocationReqIEAddr(pstLppMsg);
    pstLocationReqBuff  = NAS_LPP_GetLocationReqBuff();
    pstRunLocTech = NAS_LPP_GetRuningLocTech();

    pstConfigPara = NAS_LPP_GetCfgPara();

    /*不支持同一个transaction里先后发2个request location information的情况。出现此情况，丢弃后面的消息*/
    if (pstTransElement->ucCommCfgIndex < NAS_LPP_MAX_POS_TECH)
    {
        NAS_LPP_ERR_LOG2("discard loc request, ucSessionIndx,ucTransIndx", ucSessionIndx,ucTransIndx);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SaveDownLinkLoctionReqMsg_ENUM, LNAS_LPP_SamePosTechError);
        NAS_LPP_SndUpLppErrorMsg(pstSessionEntity->ulSessionId,
                                &pstTransElement->stTransId,
                                 LPP_COMMON_IES_ERROR_LPP_MESSAGE_BODY_ERROR,
                                 VOS_TRUE,
                                 VOS_FALSE);
        return NAS_LPP_MSG_PROCESS_CMPL;
    }

    /*如果location request里要求的定位技术在之前已经有运行的，拒绝后面发送来的定位技术:
      1)如果location request里要求的定位技术有部分在之前是没有的，可以选择增加这部分新下发的定位技术；
      2)如果location request里要求的定位技术在之前都有运行，丢弃此消息，返回ABORT*/
    for ( ulLoop = 0 ; ulLoop < pstRunLocTech->ucNum; ulLoop++ )
    {
        if (NAS_LPP_POSITION_TECH_ECID == pstRunLocTech->astLocTechMap[ulLoop].enPositionTech)
        {
            pstReqLocationInfo->bitOpEcidReqLocationInfo = NAS_LPP_NO_SLCT;
        }
        else if (NAS_LPP_POSITION_TECH_OTDOA == pstRunLocTech->astLocTechMap[ulLoop].enPositionTech)
        {
            pstReqLocationInfo->bitOpOtdoaReqLocationInfo = NAS_LPP_NO_SLCT;
        }
        else//GNSS
        {
            pstReqLocationInfo->bitOpAGNSSReqLocationInfo = NAS_LPP_NO_SLCT;
        }
    }
    /*丢弃此消息,发LPP ACK*/
    if ( (NAS_LPP_NO_SLCT == pstReqLocationInfo->bitOpEcidReqLocationInfo)
       &&(NAS_LPP_NO_SLCT == pstReqLocationInfo->bitOpOtdoaReqLocationInfo)
       &&(NAS_LPP_NO_SLCT == pstReqLocationInfo->bitOpAGNSSReqLocationInfo) )
    {
        NAS_LPP_ERR_LOG("all loc tech are already run,discard this lpp msg");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SaveDownLinkLoctionReqMsg_ENUM, LNAS_LPP_SamePosTechError);
        NAS_LPP_SaveLppMsgHead(&stMsgHead,pstLppMsg);
        NAS_LPP_SndUpLppErrorMsg(pstSessionEntity->ulSessionId,
                                &pstTransElement->stTransId,
                                 LPP_COMMON_IES_ERROR_LPP_MESSAGE_BODY_ERROR,
                                 VOS_TRUE,
                                 VOS_TRUE);

        NAS_LPP_SetEndTransFlg(ucSessionIndx,
                               ucSessionTransIndx,
                               VOS_TRUE);
        return NAS_LPP_MSG_PROCESS_CMPL;
    }

    /* 确认用户面的定位技术 */
    NAS_LPP_CheckUPrunningPosTech(pstLppMsg);

    if(NAS_LPP_SLCT == pstReqLocationInfo->bitOpCommonIEsReqLocationInfo)
    {
        /*先申请comm信息的存储地址*/
        ucIndex = NAS_LPP_MallocCommCfgInfoElementIndex(ucTransIndx);
        pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(ucIndex);
        if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo)
        {
            NAS_LPP_ERR_LOG("save req fail malloc comm buffer");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_SaveDownLinkLoctionReqMsg_ENUM, LNAS_LPP_MallocCfgBufferFail);
            return  NAS_LPP_MSG_PROCESS_CMPL;
        }

        /*记录下comm 的地址*/
        pstTransElement->ucCommCfgIndex = ucIndex;

        NAS_LPP_SaveCommCfgInfo(&pstReqLocationInfo->stCommonIEsReqLocationInfo, pstLppCommCfgInfo);
    }

    if(NAS_LPP_SLCT == pstReqLocationInfo->bitOpEcidReqLocationInfo)
    {
        pstLocationReqBuff->bitOpEcidLocReq  = NAS_LPP_SLCT;
        NAS_LPP_MEM_CPY_S(&(pstLocationReqBuff->stEcidReqLocationInfo),
                        sizeof(LPP_ECID_REQ_LOCATION_INFO_STRU),
                        &(pstReqLocationInfo->stEcidReqLocationInfo),
                        sizeof(LPP_ECID_REQ_LOCATION_INFO_STRU));
        pstConfigPara->bitEcidReq = NAS_LPP_SLCT;
    }
    NAS_LPP_SaveRunTechInfo(pstLppMsg, ucSessionIndx, ucSessionTransIndx, ucTransIndx);

    return  NAS_LPP_MSG_VERIFY_SUCC;
}

/*****************************************************************************
Function Name  : NAS_LPP_SaveDownLinkMsg
Description    : LPP模块收到下行空口消息的保存
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_UINT32  NAS_LPP_SaveDownLinkMsg
(
    LPP_MESSAGE_STRU                       *pstLppMsg,
    VOS_UINT8                               ucSessionIndx,
    VOS_UINT8                               ucSessionTransIndx,
    VOS_UINT8                               ucTransIndx
)
{
    VOS_UINT32                          ulMsgType       = 0;
    VOS_UINT32                          ulReturnRslt    = NAS_LPP_MSG_PROCESS_CMPL;

    NAS_LPP_NORM_LOG("NAS_LPP_SaveDownLinkMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveDownLinkMsg_ENUM, LNAS_LPP_Func_Enter);

    ulMsgType = NAS_LPP_GetDownlinkMsgType(pstLppMsg);

    switch(ulMsgType)
    {
        case LPP_SUPPORT_MESSAGE_BODY_REQUEST_CAPABILITIES_CHOSEN:
            ulReturnRslt = NAS_LPP_SaveDownLinkCapReqMsg(pstLppMsg, ucSessionIndx,ucTransIndx);
            break;

        case LPP_SUPPORT_MESSAGE_BODY_PROVIDE_ASSISTANCE_DATA_CHOSEN:
            /*对于辅助数据消息的保存，目前设计OTDOA, GNSS，后续阶段在做*/
            ulReturnRslt = NAS_LPP_SaveDownLinkAssistDataProvideMsg(pstLppMsg, ucSessionIndx,ucSessionTransIndx,ucTransIndx);
            break;

        case LPP_SUPPORT_MESSAGE_BODY_REQUEST_LOCATION_INFO_CHOSEN:
            /*保存locationReq的信息*/
            ulReturnRslt = NAS_LPP_SaveDownLinkLoctionReqMsg(pstLppMsg, ucSessionIndx,ucSessionTransIndx,ucTransIndx);
            break;

        case LPP_SUPPORT_MESSAGE_BODY_ABORT_CHOSEN:
            ulReturnRslt = NAS_LPP_MSG_VERIFY_SUCC;
            break;

        case LPP_SUPPORT_MESSAGE_BODY_ERROR_CHOSEN:
            ulReturnRslt = NAS_LPP_MSG_VERIFY_SUCC;
            break;

        default:
            NAS_LPP_ERR_LOG("NAS_LPP_SaveDownLinkMsg: Error DownLink Msg Type!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveDownLinkMsg_ENUM, LNAS_LPP_ErrorDownLinkMsgType);
            break;
    }

    return ulReturnRslt;

}

/*****************************************************************************
Function Name  : NAS_LPP_SaveLppMsgHead
Description    : 得到LPP消息头
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_VOID  NAS_LPP_SaveLppMsgHead
(
    NAS_LPP_MSG_HEAD_STRU              *pstMsgHead,
    LPP_MESSAGE_STRU                   *pstLppMsgBuff
)
{
    NAS_LPP_NORM_LOG("NAS_LPP_SaveLppMsgHead is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SaveLppMsgHead_ENUM, LNAS_LPP_Func_Enter);

    pstMsgHead->bEndTransaction         = pstLppMsgBuff->bEndTransaction;
    pstMsgHead->bitOpAcknowledgement    = pstLppMsgBuff->bitOpAcknowledgement;
    pstMsgHead->bitOpLppMessageBody     = pstLppMsgBuff->bitOpLppMessageBody;
    pstMsgHead->bitOpLppTransactionId   = pstLppMsgBuff->bitOpLppTransactionId;
    pstMsgHead->bitOpSequenceNumber     = pstLppMsgBuff->bitOpSequenceNumber;

    NAS_LPP_MEM_CPY_S(&(pstMsgHead->stTransactionId),
                    sizeof(LPP_TRANSACTION_ID_STRU),
                    &(pstLppMsgBuff->stTransactionId),
                    sizeof(LPP_TRANSACTION_ID_STRU));

    NAS_LPP_MEM_CPY_S(&(pstMsgHead->stSequenceNumber),
                    sizeof(LPP_SEQUENCE_NUMBER_STRU),
                    &(pstLppMsgBuff->stSequenceNumber),
                    sizeof(LPP_SEQUENCE_NUMBER_STRU));

    NAS_LPP_MEM_CPY_S(&(pstMsgHead->stAcknowledgement),
                    sizeof(LPP_ACKNOWLEDGEMENT_STRU),
                    &(pstLppMsgBuff->stAcknowledgement),
                    sizeof(LPP_ACKNOWLEDGEMENT_STRU));

    return;
}

/*****************************************************************************
Function Name   : NAS_LPP_FirstAssistDataAndStartProtectTimer
Description     :  判断transaction的第一条是否是assist data
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-9-7  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_FirstLppMsgIsAssistData
(
    VOS_UINT32                          ulSessionId,
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity;
    NAS_LPP_TRANS_ID_STRU                   stTransId;
    VOS_UINT8                               ucSessionTransIndx;

    if (LPP_SUPPORT_MESSAGE_BODY_PROVIDE_ASSISTANCE_DATA_CHOSEN != pstLppMsg->stLppMessageBody.u.stC1.ulChoice)
    {
        return VOS_FALSE;
    }

    stTransId.enInitiator = pstLppMsg->stTransactionId.enInitiator;
    stTransId.ucTransactionNumber = pstLppMsg->stTransactionId.ucTransactionNumber;

    pstTransEntity = NAS_LPP_SearchTransEntity(ulSessionId,
                                               &(stTransId),
                                               &ucSessionTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        NAS_LPP_NORM_LOG("assist data is first lpp msg for transaction !");
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
Function Name   : NAS_LPP_DecodeFailProcess
Description     : 将解码失败的消息返回给网侧
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.wangensheng      2015-9-8  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_DecodeFailProcess
(
    VOS_UINT32                          ulSessionId,
    VOS_UINT32                          ulDecodeFailRslt,
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    VOS_UINT8                           ucErrorType = LPP_COMMON_IES_ERROR_UNDEFINED;
    NAS_LPP_TRANS_ID_STRU               stTransID;

    /* 将解码错误原因值映射为消息错误原因值 */
    switch ( ulDecodeFailRslt )
    {
        case NAS_LPP_DECODE_MSG_HEADER_ERROR_INCORRECT_VALUE:
        case NAS_LPP_DECODE_MSG_HEADER_ERROR_LOGIC_ABNORMAL:
        case NAS_LPP_DECODE_MSG_BODY_ERROR_TOO_SHORT:

            ucErrorType = LPP_COMMON_IES_ERROR_LPP_MESSAGE_HEADER_ERROR;
            break;
        case NAS_LPP_DECODE_MSG_BODY_ERROR_HAVE_EXT_IE_BUT_DONOT_TAKE:
        case NAS_LPP_DECODE_MSG_BODY_ERROR_TOTOAL_LEN_MISMATCH:
        case NAS_LPP_DECODE_MSG_BODY_ERROR_OPTION_IE_BECOME_COERCIVE_IE:
        case NAS_LPP_DECODE_MSG_BODY_ERROR_OPTION_IE_LV_VALUE_MISMATCH:
        case NAS_LPP_DECODE_MSG_BODY_ERROR_VALUE_ERROR_IN_CERTAIN_PROCESS:
        case NAS_LPP_DECODE_MSG_BODY_ERROR_TYPE_NON_EXIST:

            ucErrorType = LPP_COMMON_IES_ERROR_LPP_MESSAGE_BODY_ERROR;
            break;
        case NAS_LPP_DECODE_MSG_UNDEFINED_ERROR:
        case NAS_LPP_DECODE_FAIL:

            ucErrorType = LPP_COMMON_IES_ERROR_UNDEFINED;
            break;
        case NAS_LPP_DECODE_MSG_EPDU_ERROR_VALUE_ERROR:

            ucErrorType = LPP_COMMON_IES_ERROR_EPDU_ERROR;
            break;
        case NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR:
        case NAS_LPP_DECODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR:
        case NAS_LPP_DECODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR:
        case NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR:
        case NAS_LPP_DECODE_MSG_VALUE_ERROR_EXT_IE_LEN_ERROR:
        case NAS_LPP_DECODE_MSG_VALUE_ERROR_CHAR_LEN_ERROR:
        case NAS_LPP_DECODE_MSG_VALUE_ERROR_CHOICE_ERROR:

            ucErrorType = LPP_COMMON_IES_ERROR_INCORRECT_DATA_VALUE;
            break;
        default:

            ucErrorType = LPP_COMMON_IES_ERROR_UNDEFINED;
            break;

    }

    stTransID.enInitiator = pstLppMsg->stTransactionId.enInitiator;
    stTransID.ucTransactionNumber = pstLppMsg->stTransactionId.ucTransactionNumber;

    /*2015.12.14:这里解码失败，不需要网侧对上行error回ack，不需要清除transaction */
    NAS_LPP_SndUpLppErrorMsg(ulSessionId,&stTransID,ucErrorType,PS_FALSE,PS_FALSE);
}

/*****************************************************************************
Function Name   : NAS_LPP_DownLinkMsgFailProcess
Description     : 将解码失败的消息返回给网侧
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.wangensheng      2015-9-8  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_DownLinkMsgFailProcess
(
    VOS_UINT32                          ulSessionId,
    VOS_UINT32                          ulDecodeFailRslt,
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    VOS_UINT8                           ucErrorType = LPP_COMMON_IES_ERROR_UNDEFINED;
    NAS_LPP_TRANS_ID_STRU               stTransID;
    VOS_UINT8                           ucSessionIndx = PS_NULL_UINT8;
    VOS_UINT8                           ucTransIndx   = PS_NULL_UINT8;
    VOS_UINT8                           ucSessionTransIndx = PS_NULL_UINT8;

    /* 将解码错误原因值映射为消息错误原因值 */
    switch ( ulDecodeFailRslt )
    {
        case NAS_LPP_MSG_VERIFY_HEAD_FAIL:

            ucErrorType = LPP_COMMON_IES_ERROR_LPP_MESSAGE_HEADER_ERROR;
            break;
        case NAS_LPP_MSG_VERIFY_COMMOM_BODY_REPORT_TYPE_ERROR:
        case NAS_LPP_MSG_VERIFY_FAIL:

            ucErrorType = LPP_COMMON_IES_ERROR_LPP_MESSAGE_BODY_ERROR;
            break;

        default:

            ucErrorType = LPP_COMMON_IES_ERROR_UNDEFINED;
            break;

    }

    stTransID.enInitiator = pstLppMsg->stTransactionId.enInitiator;
    stTransID.ucTransactionNumber = pstLppMsg->stTransactionId.ucTransactionNumber;

    /*2015.12.14:*/
    ucSessionIndx = NAS_LPP_SearchSessionIndx(ulSessionId);
    NAS_LPP_SearchTransEntityIndx(ucSessionIndx, &stTransID, &ucTransIndx, &ucSessionTransIndx);
    if ((PS_NULL_UINT8 == ucTransIndx)||(PS_NULL_UINT8 == ucSessionIndx))
    {
         NAS_LPP_SndUpLppErrorMsg(ulSessionId,&stTransID,ucErrorType,PS_FALSE,PS_TRUE);
    }
    else
    {
         NAS_LPP_SndUpLppErrorMsg(ulSessionId,&stTransID,ucErrorType,PS_TRUE,PS_TRUE);
    }

    NAS_LPP_SetEndTransFlg(ucSessionIndx, ucSessionTransIndx, VOS_TRUE);
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvLppEmmDataInd
Description    : LPP模块收到LMM data ind的处理(下行空口的处理)
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-7-13  新开发
*****************************************************************************/
VOS_VOID  NAS_LPP_RcvLppEmmDataInd(LMM_LPP_DATA_IND_STRU *pRcvMsg )
{
    VOS_UINT32                              ulRslt          = 0;
    VOS_UINT32                              ulRcvNwMsgLen   = 0;
    LPP_MESSAGE_STRU                       *pstLppMsgBuff   = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_HEAD_STRU                   stMsgHead;
    VOS_UINT32                              ulMsgType       = 0;
    VOS_UINT8                               ucSessionIndx   = 0;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8                               ucTransIndx     = 0;
    VOS_UINT8                               ucSessionTransIndx = 0;
    VOS_UINT32                              ulReturnRslt    = 0;
    NAS_LPP_TRANS_INDEX_STRU                stLppTransIndex;
    VOS_BOOL                                bFirstLppMsgIsAssistData;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmDataInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEmmDataInd_ENUM, LNAS_LPP_Func_Enter);

    ulRcvNwMsgLen = pRcvMsg->stLppMsg.ulLppMsgSize;
    if( ulRcvNwMsgLen > LPP_MAX_MSG_CONTAINER_CNTNTS_LEN )
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvLppEmmDataInd:WARNING:EMM->LPP Message NW Msg over-long!");
        ulRcvNwMsgLen = LPP_MAX_MSG_CONTAINER_CNTNTS_LEN;
    }

    /*清空LPP MSG BUFF*/
    NAS_LPP_ClearLppMsgBuff();

    /*获取LPP MSG BUFF*/
    /*用户存储解码之后数据的buffer大小有优化空间，目前分两步走:
      1. 将GNSS定位数量16的改成6，将每种GNSS定位技术中的卫星个数从64改成35，这样下来可以省1.2M的空间
      2. 对于sequence of的场景使用指针数据代替，这样空间省可以到byte级别
      本阶段只做第一点， 对于第二点后续再优化
     */
    pstLppMsgBuff = NAS_LPP_GetLppMsgBuff();

    /*空口解码*/
    ulRslt = NAS_LPP_DecodeMessage(pRcvMsg->stLppMsg.aucLppMsg,
                                   ulRcvNwMsgLen,
                                   pstLppMsgBuff);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        /*解码不成功*/
        NAS_LPP_ERR_LOG("NAS_LPP_RcvLppEmmDataInd: Decode Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLppEmmDataInd_ENUM, LNAS_LPP_DecodeError);

        NAS_LPP_SendOmtAirMsg(NAS_LPP_OMT_AIR_MSG_DOWN,
                              LNAS_LPP_DN_MSG_PARA_ERR,
                              ulRcvNwMsgLen,
                              pRcvMsg->stLppMsg.aucLppMsg);

        /*根据不同的原因值，映射到空口可以识别的原因值，然后给网侧发送ERROR消息*/
        NAS_LPP_DecodeFailProcess( pRcvMsg->ulSessionId, ulRslt, pstLppMsgBuff);
        return;
    }

    /*HIDS air msg */
    NAS_LPP_SendOmtAirMsg(NAS_LPP_OMT_AIR_MSG_DOWN,
                          NAS_LPP_OmGetMsgType(NAS_LPP_OMT_AIR_MSG_DOWN),
                          ulRcvNwMsgLen,
                          pRcvMsg->stLppMsg.aucLppMsg);

    /*获取当前空口消息类型*/
    ulMsgType = NAS_LPP_GetDownlinkMsgType(pstLppMsgBuff);

    /*解码成功，下行消息asn的检测*/
    ulRslt = NAS_LPP_CheckDownLinkMsg(pstLppMsgBuff);
    if(NAS_LPP_MSG_VERIFY_SUCC != ulRslt)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvLppEmmDataInd: Verify Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLppEmmDataInd_ENUM, LNAS_LPP_VerifyFail);
        /*空口校验失败，给网络侧发送ERROR消息*/
        /*如果返回的是NAS_LPP_MSG_VERIFY_HEAD_FAIL，则给网侧回复ERROR头错误*/
        /*如果返回的是NAS_LPP_MSG_VERIFY_COMMOM_BODY_REPORT_TYPE_ERROR，也给网络
        回复ERROR，消息体错误*/
        NAS_LPP_DownLinkMsgFailProcess( pRcvMsg->ulSessionId, ulRslt, pstLppMsgBuff);
        return;
    }

    /*取出LPP消息头头*/
    NAS_LPP_SaveLppMsgHead(&stMsgHead, pstLppMsgBuff);

    /*判断是否启动接收assist data 的保护定时器:
        1、 如果provide assist data 是transaction的的第一个消息，就要启动保护定时器;
        2、 如果是ue发起申请的，等收到发送cnf后启动*/
    bFirstLppMsgIsAssistData = NAS_LPP_FirstLppMsgIsAssistData(pRcvMsg->ulSessionId,pstLppMsgBuff);

    /*辅助数据流程的对冲处理:*/
    if ( (NAS_LPP_SLCT == pstLppMsgBuff->bitOpLppMessageBody)
       &&(LPP_SUPPORT_MESSAGE_BODY_PROVIDE_ASSISTANCE_DATA_CHOSEN == pstLppMsgBuff->stLppMessageBody.u.stC1.ulChoice) )
    {
        if (NAS_LPP_ASSIST_DATA_CONFLICT == NAS_LPP_ProvideAssistDataConflictProcess(bFirstLppMsgIsAssistData,pRcvMsg->ulSessionId) )
        {
            /*带有LPP消息body*/
            if( (NAS_LPP_SLCT == stMsgHead.bitOpAcknowledgement)
              &&(PS_TRUE == stMsgHead.stAcknowledgement.bAckRequested) )
            {
                /*需要回复ACK消息*/
                NAS_LPP_SndUplinkAckMsg(&stMsgHead, pRcvMsg->ulSessionId);
            }
            return;
        }
    }

    /*获取transaction实体*/
    pstTransEntity = NAS_LPP_VerifyOrCreateTransaction(&stMsgHead,
                                                       pRcvMsg->ulSessionId,
                                                       &ucTransIndx,
                                                       &ucSessionTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvLocationRequestHandle: Transcation Alloc Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLppEmmDataInd_ENUM, LNAS_LPP_CanntAllocTransEntity);
        return;
    }

    /*消息的重复性检查，下行ack的处理，*/
    ulRslt = NAS_LPP_NwMsgPreProcess(pstTransEntity,&stMsgHead, pRcvMsg->ulSessionId, ulMsgType);

    /*如果处理完成，无需后续处理，退出*/
    if (NAS_LPP_MSG_PROCESS_CMPL == ulRslt)
    {
        return;
    }

    /*填充transaction实体的索引以及数组下标以及结构指针*/
    stLppTransIndex.pstTransEntity      = pstTransEntity;
    stLppTransIndex.ucTransIndx         = ucTransIndx;
    stLppTransIndex.ucSessionTransIndx  = ucSessionTransIndx;

    /*获取sessionIndx，此时一定存在Session实体*/
    ucSessionIndx = NAS_LPP_SearchSessionIndx(pRcvMsg->ulSessionId);

    /*启动接收assist data的保护定时器*/
    if ( (VOS_TRUE == bFirstLppMsgIsAssistData)&& ( VOS_FALSE == pstLppMsgBuff->bEndTransaction))
    {
        NAS_LPP_ChangeTransFsmState(ucSessionIndx,ucSessionTransIndx,LPP_MS_ASSISTDATA,LPP_SS_ASSISTDATA_WAIT_CN_CNF);
    }

    /*保存下行空口消息*/
    ulReturnRslt = NAS_LPP_SaveDownLinkMsg(pstLppMsgBuff, ucSessionIndx,ucSessionTransIndx,ucTransIndx);
    if(NAS_LPP_MSG_VERIFY_SUCC != ulReturnRslt)
    {
        return ;
    }

    /*校验成功, 处理消息*/
    NAS_LPP_NwMsgProcess(&stMsgHead,
                         pRcvMsg->ulSessionId,
                         ulMsgType,
                         &stLppTransIndex);

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvLppEmmStartInd
Description    : LPP模块EMM消息处理函数
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-8-4  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_RcvLppEmmStartInd( LMM_LPP_START_IND_STRU *pRcvMsg )
{
    NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmStartInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEmmStartInd_ENUM, LNAS_LPP_Func_Enter);



    /*读取nv*/
    NAS_LPP_ReadLppNvConfig();

    /* 清除除了能力之外的结构体数据 */
    NAS_LPP_LppInitExceptCap();

    /* 给MTA发消息获取能力，同时启动定时器加保护 */
    NAS_LPP_GNSSCapReq();

    /* 启动等GNSS CAP CNF 定时器 */
    NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                       NAS_LPP_TIMER_INVAILD_PARA,
                       TI_NAS_LPP_WAIT_GNSS_CAP_CNF);
    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvLppEmmStopInd
Description    : LPP模块EMM消息处理函数
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-8-4  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_RcvLppEmmStopInd( LMM_LPP_STOP_IND_STRU *pRcvMsg )
{
    NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmStopInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEmmStopInd_ENUM, LNAS_LPP_Func_Enter);

    NAS_LPP_ReleaseAllSession();

    /*用户面清实体*/
    NAS_LPP_UPClrEntity();

    NAS_LPP_MEM_SET_S(NAS_LPP_GetLppEntityCtx(),sizeof(NAS_LPP_ENTITY_STRU), 0, sizeof(NAS_LPP_ENTITY_STRU));
    g_ulEmmLppOpId = 0;

    /* 清除除了能力之外的结构体数据 */
    NAS_LPP_LppInitExceptCap();

    return;
}

/*****************************************************************************
Function Name   : NAS_LPP_RcvLppEmmCellChngInd
Description     :
Input           : None
Output          : None
Return          : VOS_UINT32

History         :
1.XiaoJun      2015-9-1  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvLppEmmCellChngInd( LMM_LPP_CELL_CHANGE_IND *pRcvMsg)
{
    NAS_LPP_SERVING_CELL_STRU   *pstServingCell;
    NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmCellChngInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEmmCellChngInd_ENUM, LNAS_LPP_Func_Enter);
    pstServingCell = NAS_LPP_GetServingCell();

    if(pRcvMsg->usPhyCellId != pstServingCell->usPhyCellId)
    {
        pstServingCell->bitCELLIDChng = NAS_LPP_SLCT;
    }
    pstServingCell->ulEarfcn    = pRcvMsg->ulEarfcn;
    pstServingCell->usPhyCellId = pRcvMsg->usPhyCellId;
    pstServingCell->ulCellIdentity = pRcvMsg->ulCellId;

    /*3是数组aucPlmnId的长度*/
    NAS_LPP_MEM_CPY_S(pstServingCell->aucPlmnId,3,pRcvMsg->aucPlmnId, 3);
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvLppEmmRelInd
Description    : LPP模块EMM消息处理函数
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-8-4  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_RcvLppEmmRelInd( LMM_LPP_START_IND_STRU *pRcvMsg )
{
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8        enEcidReqPosType = NAS_LPP_UP_POS_REQ_TECH_TYPE_BUTT;
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8        enOtdoaReqPosType = NAS_LPP_UP_POS_REQ_TECH_TYPE_BUTT;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEmmRelInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLppEmmRelInd_ENUM, LNAS_LPP_Func_Enter);

    enEcidReqPosType = NAS_LPP_GetEcidPosType();
    enOtdoaReqPosType = NAS_LPP_GetOtdoaPosType();

    if(PS_TRUE == NAS_LPP_GetEcidAndOtdoaMeasFlag())
    {
        NAS_LPP_UPClrEntity();
    }
    else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID == enEcidReqPosType)
    {
        NAS_LPP_UPClrEcidCtx();
    }
    else if(NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA == enOtdoaReqPosType)
    {
        NAS_LPP_UPClrOtdoaCtx();
    }
    else
    {
    }

    NAS_LPP_ReleaseAllSession();

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_EmmMsgDistr
Description    : LPP模块EMM消息处理函数
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lifuxin 00253982 2015-7-7  新开发
*****************************************************************************/
VOS_VOID NAS_LPP_EmmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg  = VOS_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_EmmMsgDistr is entered!");

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_EmmMsgDistr_ENUM, LNAS_LPP_Func_Enter, pEmmMsg->ulMsgName);

    /*根据消息名，调用相应的消息处理函数*/
    switch(pEmmMsg->ulMsgName)
    {
        case ID_LMM_LPP_DATA_IND:
            NAS_LPP_RcvLppEmmDataInd((LMM_LPP_DATA_IND_STRU *)pRcvMsg);
            break;

        case ID_LMM_LPP_EST_CNF:
            NAS_LPP_RcvLppEmmEstCnf((LMM_LPP_EST_CNF_STRU *)pRcvMsg);
            break;

        case ID_LMM_LPP_DATA_CNF:
            NAS_LPP_RcvLppEmDataCnf((LMM_LPP_DATA_CNF_STRU *)pRcvMsg);
            break;

        case ID_LMM_LPP_START_IND:
            NAS_LPP_RcvLppEmmStartInd((LMM_LPP_START_IND_STRU *)pRcvMsg);
            break;

        case ID_LMM_LPP_STOP_IND:
            NAS_LPP_RcvLppEmmStopInd((LMM_LPP_STOP_IND_STRU *)pRcvMsg);
            break;

        case ID_LMM_LPP_CELL_CHANGE_IND:
            NAS_LPP_RcvLppEmmCellChngInd((LMM_LPP_CELL_CHANGE_IND *)pRcvMsg);
            break;

        case ID_LMM_LPP_REL_IND:
            NAS_LPP_RcvLppEmmRelInd((LMM_LPP_START_IND_STRU *)pRcvMsg);
            break;

        default:
            NAS_LPP_WARN_LOG("NAS_LPP_EmmMsgDistr:NORM: Error SenderPid!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_EmmMsgDistr_ENUM, LNAS_LPP_ErrorSenderPid);
            break;
    }

    return;
}
/*lint +e701*/
#endif
#ifdef __cplusplus
#if __cplusplus
    }
    #endif
#endif
/* end of NasLppEmmMsgProc.c */
