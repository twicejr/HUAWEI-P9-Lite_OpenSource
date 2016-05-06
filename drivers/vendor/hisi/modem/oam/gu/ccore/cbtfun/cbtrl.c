/******************************************************************************

                  版权所有 (C), 2015-2025, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Cbtrl.c
  版 本 号   : 初稿
  作    者   :
  生成日期   :
  最近修改   :
  功能描述   : 进行CBT通道的数据包分包和组包
  函数列表   :
  修改历史   :
  1.日    期   : 2015年2月28日
    作    者   : x00263027
    修改内容   :

***************************************************************************** */

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

/*****************************************************************************
 函 数 名  : CBT_GreenChannel
 功能描述  : 绿色通道，OM提供给外部的发送接口
 输入参数  : ucFuncType  - 功能ID
             usPrimId    - 原语值
             pucData     - 指向发送数据的指针
             usLen       - 发送数据的长度
 输出参数  : 无
 返 回 值  : VOS_OK  - 成功
             VOS_ERR - 失败

 修改历史      :
  1.日    期   : 2015年2月28日
    作    者   : x00263027
    修改内容   : 新生成函数
*****************************************************************************/
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
