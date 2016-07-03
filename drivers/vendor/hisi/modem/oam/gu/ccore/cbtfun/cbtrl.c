

/*****************************************************************************
  1 头文件包含
**************************************************************************** */

#include "cbtrl.h"
#include "pamom.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_CBT_RL_C

extern VOS_UINT32                   g_ulCbtSwitchOnOff;




VOS_VOID CBT_ResetMsgHead(CBT_UNIFORM_MSG_STRU * pstCbtToPcMsg)
{
    pstCbtToPcMsg->stMsgHeader.ucSid = 0x07;
    pstCbtToPcMsg->stMsgHeader.ucSessionID = 0x01;

    /*分段信息*/
    pstCbtToPcMsg->stMsgHeader.stMsgSegment.ucMsgType = CBT_MT_CNF;
    pstCbtToPcMsg->stMsgHeader.stMsgSegment.ucFragIndex = 0;
    pstCbtToPcMsg->stMsgHeader.stMsgSegment.ucEof = 1;
    pstCbtToPcMsg->stMsgHeader.stMsgSegment.ucFragFlag = 0;
}

VOS_UINT32 CBT_SendData(CBT_UNIFORM_MSG_STRU * pucMsg, VOS_UINT16 usMsgLen)
{
    CBT_CTOA_MSG_STRU                  *pstCbtMsg;

    /* 链路未建立 */
    if (CBT_STATE_IDLE == g_ulCbtSwitchOnOff)
    {
        /* 记录可维可测信息 */
        return VOS_ERR;
    }

    /* 将消息发到A核OM处理 */
    pstCbtMsg = (CBT_CTOA_MSG_STRU *)VOS_AllocMsg(CCPU_PID_CBT, usMsgLen + 2*sizeof(VOS_UINT16));

    if (VOS_NULL_PTR == pstCbtMsg)
    {
        return VOS_ERR;
    }

    pstCbtMsg->ulReceiverPid      = ACPU_PID_CBT;
    pstCbtMsg->usPrimId           = CBT_CCPU_TO_ACPU_SEND_DATA_REQ;
    pstCbtMsg->usLen              = usMsgLen;

    /*lint -e534*/
    VOS_MemCpy(pstCbtMsg->aucData, pucMsg, usMsgLen);
    /*lint +e534*/

    return VOS_SendMsg(CCPU_PID_CBT, pstCbtMsg);
}


VOS_VOID CBT_SendResultChannel(CBT_MODEM_SSID_STRU stModemSsid, CBT_COMPONENT_MODE_STRU stCompMOde,
                                VOS_UINT16 usReturnPrimId, VOS_UINT32 ulResult)
{
    CBT_UNIFORM_MSG_STRU                stCbtToPcMsg;

    /*lint -e534*/
    VOS_MemSet(&stCbtToPcMsg, 0, sizeof(CBT_UNIFORM_MSG_STRU));
    /*lint +e534*/
    CBT_ResetMsgHead(&stCbtToPcMsg);

    stCbtToPcMsg.stMsgHeader.stModemSsid    = stModemSsid;
    stCbtToPcMsg.usMsgId                    = usReturnPrimId;
    stCbtToPcMsg.stCompMode                 = stCompMOde;
    stCbtToPcMsg.ulMsgLength                = 4;

    *((VOS_UINT32*)(stCbtToPcMsg.aucPara)) = ulResult;

    /*lint -e534*/
    CBT_SendData(&stCbtToPcMsg, (VOS_UINT16)sizeof(CBT_UNIFORM_MSG_STRU));
    /*lint +e534*/
    return;
}


VOS_VOID CBT_SendContentChannel(CBT_MODEM_SSID_STRU stModemSsid, CBT_COMPONENT_MODE_STRU stCompMode,
                                       VOS_UINT16 usReturnPrimId, CBT_UNIFORM_MSG_STRU * pstCbtToPcMsg)
{
    CBT_UNIFORM_MSG_STRU               *pstTmpMsg;

    pstTmpMsg = (CBT_UNIFORM_MSG_STRU *)pstCbtToPcMsg;

    CBT_ResetMsgHead(pstTmpMsg);
    pstTmpMsg->stMsgHeader.stModemSsid              = stModemSsid;
    pstTmpMsg->stMsgHeader.stMsgSegment.ucMsgType   = CBT_MT_CNF;
    pstTmpMsg->usMsgId                              = usReturnPrimId;
    pstTmpMsg->stCompMode                           = stCompMode;

    /*lint -e534*/
    CBT_SendData(pstCbtToPcMsg, (VOS_UINT16)(pstCbtToPcMsg->ulMsgLength + CBT_MSG_HEAD_EX_LENGTH));
    /*lint +e534*/
    return;
}


VOS_UINT32 CBT_GreenChannel(CBT_MODEM_SSID_STRU stModemSsid, CBT_COMPONENT_MODE_STRU stCompMode, VOS_UINT16 usPrimId,
                            VOS_UINT8 *pucData, VOS_UINT16 usLen)
{
    CBT_UNIFORM_MSG_STRU *           pstAppMsg;
    VOS_UINT32                       ulResult;

    pstAppMsg = (CBT_UNIFORM_MSG_STRU *)VOS_MemAlloc(PC_PID_TOOL,
                                         DYNAMIC_MEM_PT, usLen + CBT_MSG_HEAD_EX_LENGTH);
    if (NULL == pstAppMsg)
    {
        PS_LOG(CCPU_PID_CBT, 0, PS_PRINT_ERROR, "CBT_GreenChannel:VOS_MemAlloc.\n");
        return VOS_ERR;
    }

    CBT_ResetMsgHead(pstAppMsg);

    pstAppMsg->stMsgHeader.stModemSsid = stModemSsid;
    pstAppMsg->usMsgId                 = usPrimId;
    pstAppMsg->stCompMode              = stCompMode;
    pstAppMsg->ulMsgLength             = usLen;

    /*假如内容长度为0，表示没有发送内容*/
    if ((0 != usLen) && (VOS_NULL_PTR != pucData))
    {
        /*lint -e534*/
        VOS_MemCpy(pstAppMsg->aucPara, pucData, usLen);
        /*lint +e534*/
    }

    ulResult = CBT_SendData((CBT_UNIFORM_MSG_STRU *)pstAppMsg, usLen + CBT_MSG_HEAD_EX_LENGTH);
    /*lint -e534*/
    VOS_MemFree(CCPU_PID_CBT, pstAppMsg);
    /*lint +e534*/

    return ulResult;
}


#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif
