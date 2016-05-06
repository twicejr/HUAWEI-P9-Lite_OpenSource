/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : CssProcAtMsg.c
  Description     : 该C文件给出了CSS接收到AT消息的实现
  History         :
     1.chengmin 00285307    2015-10-12  Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include            "CssAtInterface.h"
#include            "CssProcAtMsg.h"
#include            "CssCloudStrategyPublic.h"
#include            "CssProcCommMsg.h"
#include            "MnClient.h"


#define    THIS_FILE_ID        PS_FILE_ID_CSSPROCATMSG_C


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name  : CSS_UpdateStateAccordingToAtMccSetMsg
 Description    : 根据下发的消息来更新状态表
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2016-01-29  Draft Enact
*****************************************************************************/
VOS_VOID CSS_UpdateStateAccordingToAtMccSetMsg
(
    const AT_CSS_MCC_INFO_SET_REQ_STRU           *pRcvMsg,
    VOS_UINT8                                     aucMcc[2],
    VOS_UINT32                                    ulRslt
)
{
    VOS_UINT32                          ulLoop;
    CSS_CLOUD_PUB_CONTROL_STRU         *pstCssCloudContrl;
    VOS_UINT32                          ulUpdateRslt;

    pstCssCloudContrl = CSS_GetCloudContrlAddr();

    TLPS_PRINT2LAYER_INFO(CSS_UpdateStateAccordingToAtMccSetMsg_ENUM, LNAS_ENTRY);

    /* 如果是AP正在更新过程中 */
    if (CSS_TRUE == CSS_IsApUpdating())
    {
        TLPS_PRINT2LAYER_INFO(CSS_UpdateStateAccordingToAtMccSetMsg_ENUM, LNAS_FUNCTION_LABEL1);

        /* 更新流程中的状态表 */
        (VOS_VOID)CSS_UpdateOneMcc(&(pstCssCloudContrl->stApMccUpdate), aucMcc);

        /* 如果全部更新完了，则终止该流程 */
        if ((CSS_TRUE == CSS_IsAllMccUpdated(&(pstCssCloudContrl->stApMccUpdate))
             && CSS_END_OF_AT_SEQ == pRcvMsg->ucSeq)
            || (CSS_CAUSE_NULL_PTR == ulRslt))
        {
            TLPS_PRINT2LAYER_INFO(CSS_UpdateStateAccordingToAtMccSetMsg_ENUM, LNAS_FUNCTION_LABEL2);

            /* 终止AP更新流程 */
            CSS_EndApUpdateProcedure();
        }
    }

    /* 查找MMC或AS是否正在更新中 */
    for (ulLoop = 0; ulLoop < CSS_MAX_PID_NUM; ++ulLoop)
    {
        /* 不属于正在更新的流程则continue */
        if (CSS_TRUE != pstCssCloudContrl->astMccUpdate[ulLoop].ucIsUpdating)
        {
            continue;
        }

        /* 内存已不够存储，直接中断流程 */
        if (CSS_CAUSE_NULL_PTR == ulRslt)
        {
            /* 回复GEO_RSP */
            CSS_SndCurrGeoRsp(pstCssCloudContrl->astMccUpdate[ulLoop].ulPid, CSS_RESULT_FAIL);

            /* 终止流程 */
            CSS_EndMmcOrAsUpdateProcedure(&(pstCssCloudContrl->astMccUpdate[ulLoop]));

            continue;
        }

        /* 状态表更新 */
        ulUpdateRslt = CSS_UpdateOneMcc(&(pstCssCloudContrl->astMccUpdate[ulLoop]), aucMcc);

        /* 如果全部更新完了，则终止该流程 */
        if (CSS_TRUE == CSS_IsAllMccUpdated(&(pstCssCloudContrl->astMccUpdate[ulLoop]))
            && CSS_END_OF_AT_SEQ == pRcvMsg->ucSeq)
        {
            /* 回复GEO_RSP */
            if (CSS_SUCC == ulRslt)
            {
                CSS_SndCurrGeoRsp(pstCssCloudContrl->astMccUpdate[ulLoop].ulPid, CSS_RESULT_SUCC);
            }
            else
            {
                CSS_SndCurrGeoRsp(pstCssCloudContrl->astMccUpdate[ulLoop].ulPid, CSS_RESULT_FAIL);
            }

            /* 终止流程 */
            CSS_EndMmcOrAsUpdateProcedure(&(pstCssCloudContrl->astMccUpdate[ulLoop]));
        }
        else
        {
            if (CSS_TRUE == ulUpdateRslt && CSS_SUCC != ulRslt)
            {
                /* 回复GEO_RSP失败 */
                CSS_SndCurrGeoRsp(pstCssCloudContrl->astMccUpdate[ulLoop].ulPid, CSS_RESULT_FAIL);

                /* 终止流程 */
                CSS_EndMmcOrAsUpdateProcedure(&(pstCssCloudContrl->astMccUpdate[ulLoop]));
            }
        }
    }
}

/*****************************************************************************
 Function Name  : CSS_SendAtMccSetCnf
 Description    : 向AT回复MCC_INFO_SET_CNF消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_SendAtMccSetCnf(const AT_CSS_MCC_INFO_SET_REQ_STRU  *pRcvMsg, VOS_UINT32 ulResult)
{
    CSS_AT_MCC_INFO_SET_CNF_STRU       *pstMccSetCnf;

    TLPS_PRINT2LAYER_INFO1(CSS_SendAtMccSetCnf_ENUM, LNAS_ENTRY, ulResult);

    if (VOS_NULL_PTR == pRcvMsg)
    {
        /*打印异常信息*/
        return ;
    }

    /*分配消息空间*/
    pstMccSetCnf = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_AT_MCC_INFO_SET_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstMccSetCnf)
    {
        /*打印异常信息*/
        return ;
    }

    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstMccSetCnf),
                    CSS_GET_MSG_LENGTH(pstMccSetCnf),
                    0,
                    CSS_GET_MSG_LENGTH(pstMccSetCnf));

    CSS_WRITE_AT_MSG_HEAD(pstMccSetCnf,ID_CSS_AT_MCC_INFO_SET_CNF);

    pstMccSetCnf->ucSeq                 = pRcvMsg->ucSeq;
    pstMccSetCnf->ulResult              = ulResult;
    pstMccSetCnf->usClientId            = pRcvMsg->usClientId;

    /*调用消息发送函数 */
    CSS_SND_MSG(pstMccSetCnf);
}



VOS_VOID CSS_SendAtQueryMccNotifyByMccList(CSS_MCC_ID_STRU astMccID[CSS_MAX_PLMN_ID_NUM], VOS_UINT32 ulMccNum, VOS_UINT16 usClientId)
{
    CSS_AT_QUERY_MCC_INFO_NOTIFY_STRU  *pMsg;
    VOS_UINT32                          ulLoop;

    TLPS_PRINT2LAYER_INFO2(CSS_SendAtQueryMccNotifyByMccList_ENUM, LNAS_ENTRY, ulMccNum, usClientId);

    /*分配消息空间*/
    pMsg = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_AT_QUERY_MCC_INFO_NOTIFY_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pMsg)
    {
        /*打印异常信息*/
        return ;
    }

    CSS_MEM_SET_S( CSS_GET_MSG_ENTITY(pMsg), CSS_GET_MSG_LENGTH(pMsg), 0, CSS_GET_MSG_LENGTH(pMsg));

    CSS_WRITE_AT_MSG_HEAD(pMsg,ID_CSS_AT_QUERY_MCC_INFO_NOTIFY);

    /* 赋值MCC ID */
    for (ulLoop = 0; ulLoop < ulMccNum; ++ulLoop)
    {
        pMsg->astMccId[ulLoop].aucMcc[0] = astMccID[ulLoop].aucMccId[0];
        pMsg->astMccId[ulLoop].aucMcc[1] = astMccID[ulLoop].aucMccId[1];
    }

    pMsg->ulMccNum   = ulMccNum;
    pMsg->usClientId = usClientId;

    /* 拷贝版本号 */
    CSS_MEM_CPY_S(  pMsg->aucVersionId,
                    sizeof(VOS_UINT8)*MCC_INFO_VERSION_LEN,
                    CSS_GetCloudContrlAddr()->aucVersion,
                    sizeof(VOS_UINT8)*MCC_INFO_VERSION_LEN);


    /*调用消息发送函数 */
    CSS_SND_MSG(pMsg);
}



/*****************************************************************************
 Function Name  : CSS_ProcAtMsgDeleteOneMccReq
 Description    : ID_AT_CSS_MCC_INFO_SET_REQ消息的删除处理
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcAtMsgDeleteOneMccReq
(
    const AT_CSS_MCC_INFO_SET_REQ_STRU  *pRcvMsg
)
{
    VOS_UINT8                           aucMccId[2] = {0};
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM];
    VOS_UINT32                          ulMccNum;

    CSS_MEM_SET_S(  astMccID,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM,
                    0,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);

    /* 转换MCC ID */
    if (CSS_FAIL == CSS_ConvertStrToHex(aucMccId, pRcvMsg->aucMccInfoBuff, 4))
    {
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_FAIL);
        return;
    }

    TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgDeleteOneMccReq_ENUM, LNAS_ENTRY);

    /* 如果MMC或者AS没有在更新过程中，则向AT发送MCC请求 */
    if (CSS_FALSE == CSS_IsMmcOrAsUpdating())
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgDeleteOneMccReq_ENUM, LNAS_FUNCTION_LABEL1);

        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_SUCC);

        /* 如果指定删除的这个MCC在本地存在，则启动更新流程 */
        if (CSS_TRUE == CSS_IsMccExistInLocal(aucMccId))
        {
            TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgDeleteOneMccReq_ENUM, LNAS_FUNCTION_LABEL2);

            /* 向AP上报该MCC */
            ulMccNum = 1;
            astMccID[0].aucMccId[0] = aucMccId[0];
            astMccID[0].aucMccId[1] = aucMccId[1];

            /* 启动AP更新流程 */
            CSS_StartApMccUpdateProcedure(astMccID, ulMccNum, pRcvMsg->usClientId);

            /* 删除该MCC预置频点信息 */
            CSS_DeleteOneMcc(aucMccId);
        }
    }
    /* 如果MMC或者AS正在更新过程中，则必然是流程对冲情况，此时AP还未下发MCC，
       只需将本地MCC删除，等待AP下发SET_REQ */
    else
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgDeleteOneMccReq_ENUM, LNAS_FUNCTION_LABEL3);

        /* 删除本地的MCC预置频点信息 */
        CSS_DeleteOneMcc(aucMccId);

        /* 回复SET_CNF */
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_SUCC);
    }
}


/*****************************************************************************
 Function Name  : CSS_ProcAtMsgDeleteAllMccReq
 Description    : ID_AT_CSS_MCC_INFO_SET_REQ消息的删除处理
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcAtMsgDeleteAllMccReq
(
    const AT_CSS_MCC_INFO_SET_REQ_STRU  *pRcvMsg
)
{
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM];
    VOS_UINT32                          ulMccNum;

    CSS_MEM_SET_S(  astMccID,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM,
                    0,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);

    TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgDeleteAllMccReq_ENUM, LNAS_ENTRY);

    /* 如果MMC或者AS没有在更新过程中，则向AT发送MCC请求 */
    if (CSS_FALSE == CSS_IsMmcOrAsUpdating())
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgDeleteAllMccReq_ENUM, LNAS_FUNCTION_LABEL1);

        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_SUCC);

        /* 获取内存中的所有MCC ID */
        CSS_GetMccListFromLocal(astMccID, &ulMccNum);

        /* 如果MCC ID个数不为0，则启动更新流程 */
        if (0 != ulMccNum)
        {
            /* 启动AP更新流程 */
            CSS_StartApMccUpdateProcedure(astMccID, ulMccNum, pRcvMsg->usClientId);

            /* 删除本地的MCC预置频点信息 */
            CSS_DeleteAllMcc();
        }
    }
    /* 如果MMC或者AS正在更新过程中，则必然是流程对冲情况，此时AP还未下发MCC，AP处理AT命令是串行处理，一条AT命令没有处理完前，不能处理其他AT命令
       只需将本地MCC删除，等待AP下发SET_REQ */
    else
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgDeleteAllMccReq_ENUM, LNAS_FUNCTION_LABEL2);

        /* 删除本地的MCC预置频点信息 */
        CSS_DeleteAllMcc();

        /* 回复SET_CNF */
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_SUCC);
    }

}


/*****************************************************************************
 Function Name  : CSS_ProcAtMsgAddMccReq
 Description    : ID_AT_CSS_MCC_INFO_SET_REQ消息的添加处理
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcAtMsgAddMccReq
(
    const AT_CSS_MCC_INFO_SET_REQ_STRU  *pRcvMsg
)
{
    VOS_UINT8                           aucMcc[2] = {0};
    VOS_UINT8                          *pucBuff;
    VOS_UINT32                          ulBuffLen;
    VOS_UINT32                          ulResult;


    /* 转换MCC ID */
    if (CSS_FAIL == CSS_ConvertStrToHex(aucMcc, pRcvMsg->aucMccInfoBuff, 4))
    {
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_FAIL);
        return;
    }

    TLPS_PRINT2LAYER_INFO2(CSS_ProcAtMsgAddMccReq_ENUM, LNAS_ENTRY, aucMcc[0], aucMcc[1]);

    /* 将字符串转成16进制 */
    if (0 != (pRcvMsg->ulMccInfoBuffLen % 2))
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgAddMccReq_ENUM, LNAS_FUNCTION_LABEL1);

        /* 向AT回复SET_CNF */
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_FAIL);

        /* 更新状态表 */
        CSS_UpdateStateAccordingToAtMccSetMsg(pRcvMsg, aucMcc, CSS_FAIL);
        return;
    }

    ulBuffLen = pRcvMsg->ulMccInfoBuffLen / 2;
    pucBuff = CSS_MEM_ALLOC(sizeof(VOS_UINT8)*ulBuffLen);
    if (CSS_NULL_PTR == pucBuff)
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgAddMccReq_ENUM, LNAS_FUNCTION_LABEL2);

        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_FAIL);

        /* 更新状态表 */
        CSS_UpdateStateAccordingToAtMccSetMsg(pRcvMsg, aucMcc, CSS_FAIL);
        return;
    }

    if (CSS_FAIL == CSS_ConvertStrToHex(pucBuff, pRcvMsg->aucMccInfoBuff, pRcvMsg->ulMccInfoBuffLen))
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgAddMccReq_ENUM, LNAS_FUNCTION_LABEL3);

        CSS_MEM_FREE(pucBuff);
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_FAIL);

        /* 更新状态表 */
        CSS_UpdateStateAccordingToAtMccSetMsg(pRcvMsg, aucMcc, CSS_FAIL);
        return;
    }

    /* 先锁任务，防止解码过程中，接入层调用API接口 */
    (VOS_VOID)VOS_TaskLock();

    /* 读取消息中的MCC预置频点 */
    ulResult = CSS_ReadMccFromAtMsg(pucBuff, ulBuffLen);

    /* 解锁任务 */
    (VOS_VOID)VOS_TaskUnlock();

    if (CSS_SUCC == ulResult)
    {
        /* 向AT回复成功 */
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_SUCC);
    }
    else
    {
        /* 向AT回复失败 */
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_FAIL);
    }

    /* 更新状态表 */
    CSS_UpdateStateAccordingToAtMccSetMsg(pRcvMsg, aucMcc, ulResult);

    CSS_MEM_FREE(pucBuff);
}



/*****************************************************************************
 Function Name  : CSS_ProcAtMsgMccSetReq
 Description    : ID_AT_CSS_MCC_INFO_SET_REQ消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcAtMsgMccSetReq
(
    const AT_CSS_MCC_INFO_SET_REQ_STRU  *pRcvMsg
)
{
    TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgMccSetReq_ENUM, LNAS_ENTRY);

    /* 如果云通信特性不使用，直接返回 */
    if (CSS_FALSE == CSS_IsCloudStrategyEnable())
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgMccSetReq_ENUM, LNAS_FUNCTION_LABEL1);
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_SUCC);
        return;
    }

    /* 如果不从云端获取，也直接返回 */
    if (CSS_FALSE == CSS_IsPrefFreqEnable())
    {
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_SUCC);
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgMccSetReq_ENUM, LNAS_FUNCTION_LABEL2);
        return;
    }

    /* 如果本地版本号还为初始状态，则将本地所有MCC都删除，然后版本会更新 */
    if (CSS_FALSE == CSS_HasGetMccVersionFromAp())
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgMccSetReq_ENUM, LNAS_FUNCTION_LABEL3);
        CSS_DeleteAllMcc();
    }

    /* 读取云端版本号，保存在本地 */
    CSS_MEM_CPY_S(  CSS_GetCloudContrlAddr()->aucVersion,
                    sizeof(VOS_UINT8)*MCC_INFO_VERSION_LEN,
                    pRcvMsg->aucVersionId,
                    sizeof(VOS_UINT8)*MCC_INFO_VERSION_LEN);

    /* 根据操作类型处理 */
    if (AT_CSS_SET_MCC_TYPE_DELETE_ALL_MCC == pRcvMsg->ucOperateType)
    {
        CSS_ProcAtMsgDeleteAllMccReq(pRcvMsg);
    }
    else if (AT_CSS_SET_MCC_TYPE_DELETE_ONE_MCC == pRcvMsg->ucOperateType)
    {
        CSS_ProcAtMsgDeleteOneMccReq(pRcvMsg);
    }
    else if (AT_CSS_SET_MCC_TYPE_ADD_MCC == pRcvMsg->ucOperateType)
    {
        CSS_ProcAtMsgAddMccReq(pRcvMsg);
    }
    else
    {
        CSS_SendAtMccSetCnf(pRcvMsg, CSS_RESULT_FAIL);
    }

    /* 打印本地存储的预置频点信息 */
    CSS_PrintLocalPrefFreqInfo();

    /* 勾出本地全局变量 */
    CSS_SndOmPubCloudCtrlInd();
}

/*****************************************************************************
 Function Name  : CSS_ProcAtMsgMccVersionReq
 Description    : ID_AT_CSS_MCC_VERSION_INFO_REQ消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcAtMsgMccVersionReq
(
    const AT_CSS_MCC_VERSION_INFO_REQ_STRU  *pRcvMsg
)
{
    CSS_AT_MCC_VERSION_INFO_CNF_STRU   *pCnf;

    TLPS_PRINT2LAYER_INFO(CSS_ProcAtMsgMccVersionReq_ENUM, LNAS_ENTRY);

    if (VOS_NULL_PTR == pRcvMsg)
    {
        /*打印异常信息*/
        return ;
    }

    /*分配消息空间*/
    pCnf = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_AT_MCC_VERSION_INFO_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pCnf)
    {
        /*打印异常信息*/
        return ;
    }

    CSS_MEM_SET_S( CSS_GET_MSG_ENTITY(pCnf), CSS_GET_MSG_LENGTH(pCnf), 0, CSS_GET_MSG_LENGTH(pCnf));
    CSS_WRITE_AT_MSG_HEAD(pCnf,ID_CSS_AT_MCC_VERSION_INFO_CNF);

    pCnf->usClientId    = pRcvMsg->usClientId;

    CSS_MEM_CPY_S(  pCnf->aucVersionId,
                    sizeof(VOS_UINT8)*MCC_INFO_VERSION_LEN,
                    CSS_GetCloudContrlAddr()->aucVersion,
                    sizeof(VOS_UINT8)*MCC_INFO_VERSION_LEN);

    /*调用消息发送函数 */
    CSS_SND_MSG(pCnf);
}


/*****************************************************************************
 Function Name  : CSS_ProcAtMsg
 Description    : AT消息处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcAtMsg(const VOS_VOID *pRcvMsg)
{

    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_AT_CSS_MCC_INFO_SET_REQ:
            CSS_ProcAtMsgMccSetReq((const AT_CSS_MCC_INFO_SET_REQ_STRU*)pRcvMsg);
            break;

        case ID_AT_CSS_MCC_VERSION_INFO_REQ:
            CSS_ProcAtMsgMccVersionReq((const AT_CSS_MCC_VERSION_INFO_REQ_STRU *)pRcvMsg);
            break;

        default:
            break;
    }

    return;
}


#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of CssProcAtMsg.c */



