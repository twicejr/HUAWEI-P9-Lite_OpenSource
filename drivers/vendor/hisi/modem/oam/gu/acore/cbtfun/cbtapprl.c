

/******************************************************************************

                  版权所有 (C), 2015-2025, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Cbtapprl.c
  版 本 号   : 初稿
  作    者   :
  生成日期   :
  最近修改   :
  功能描述   : 进行CBT通道的数据包分包和组包
  函数列表   :
  修改历史   :
  1.日    期   : 2015年2月27日
    作    者   : x00263027
    修改内容   :

***************************************************************************** */

/*****************************************************************************
  1 头文件包含
**************************************************************************** */

#include "OmHdlcInterface.h"
#include "cbtapprl.h"
#include "omprivate.h"
#include "CbtPpm.h"
#include "msp_errno.h"
#include "diag_api.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define    THIS_FILE_ID        PS_FILE_ID_APP_CBT_RL_C
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#ifdef OAM_UT_DEBUG
VOS_UINT32                              g_ulCbtAcpuDbgFlag = VOS_NULL_DWORD;
#else
VOS_UINT32                              g_ulCbtAcpuDbgFlag = VOS_FALSE;
#endif


#define COMPONENT_MODE_COMBINE(CompMode, MsgId)  (((CompMode)<<16) | (MsgId))

/* CBT通道控制信息全局变量 */
CBT_RCV_CHAN_CTRL_INFO_STRU             g_stAcpuCbtCtrlInfo;
CBT_HDLC_ENCODE_MEM_CTRL                g_stCbtHdlcEncodeBuf;

VOS_SEM                                 g_ulTxCbtSem;
VOS_UINT32                              g_ulExpRcvTransId;
VOS_UINT32                              g_ulCbtMsgSN;


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : CBT_AcpuUsbFrameInit
 功能描述  : 当为虚拟串口时，需要初始化缓冲区
 输入参数  : VOS_VOID
 输出参数  : VOS_VOID
 返 回 值  : VOS_UINT32
 修改历史  :
   1.日    期  : 2009年3月28日
     作    者  : g47350
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 CBT_AcpuUsbFrameInit(VOS_VOID)
{
    VOS_UINT_PTR                        ulRealAddr;

    /* 申请CBT通道HDLC编码使用的uncached memory */
    VOS_MemSet(&g_stCbtHdlcEncodeBuf, 0, sizeof(g_stCbtHdlcEncodeBuf));

    g_stCbtHdlcEncodeBuf.pucBuf = (VOS_UINT8 *)VOS_UnCacheMemAlloc(2 * CBT_HDLC_BUF_MAX_LEN, &ulRealAddr);

    if (VOS_NULL_PTR == g_stCbtHdlcEncodeBuf.pucBuf)
    {
        LogPrint("CBT_AcpuUsbFrameInit: VOS_UnCacheMemAlloc failed \n");
        return VOS_ERR;
    }

    /* 保存buf实地址 */
    g_stCbtHdlcEncodeBuf.pucRealBuf = (VOS_UINT8 *)ulRealAddr;
    g_stCbtHdlcEncodeBuf.ulBufSize  = 2 * CBT_HDLC_BUF_MAX_LEN;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名     : CBT_AcpuInit
 功能描述  : OMRL模块的初始化函数
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2015年3月2日
     作    者  : x00263027
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 CBT_AcpuInit(VOS_VOID)
{
    g_ulCbtMsgSN       = 0;
    VOS_MemSet(&g_stAcpuCbtCtrlInfo, 0, sizeof(CBT_RCV_CHAN_CTRL_INFO_STRU));
    /* 首包序号为0 */
    g_stAcpuCbtCtrlInfo.stMsgCombineInfo.ucExpectedSegSn = 0;
    g_stAcpuCbtCtrlInfo.stMsgCombineInfo.usTimeStampH    = 0;
    g_stAcpuCbtCtrlInfo.ulCbtSwitchOnOff = CBT_STATE_IDLE;

    if (VOS_OK != CBT_AcpuUsbFrameInit())
    {
        LogPrint("CBT_AcpuInit:CBT_AcpuUsbFrameInit Fail.\n");
        return VOS_ERR;
    }

    /* 创建发送信号量 */
    if (VOS_OK != VOS_SmMCreate("TXCBT", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &g_ulTxCbtSem))
    {
        LogPrint("OM_AcpuInit: Error, VOS_SmMCreate Fail\n");
        return VOS_ERR;
    }

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_AcpuCpuIdToPid
 功能描述  : 根据SSID ID找到对应模块的PID
 输入参数  : ucSsId:   ssid ID
 输出参数  : pulPid -- 指向模块PID
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2015年2月27日
     作    者  : x00263027
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 CBT_AcpuSsIdToPid(VOS_UINT8 ucSsId, VOS_UINT32 *pulPid)
{
      switch(ucSsId)
      {
        case CBT_SSID_MODEM_CPU:
        case CBT_SSID_LTE_DSP:
        case CBT_SSID_GU_DSP:
        case CBT_SSID_TDS_DSP:
        case CBT_SSID_X_DSP:
            *pulPid = CCPU_PID_CBT;/* ccpu cbt pid */
            break;
        case CBT_SSID_APP_CPU:
            *pulPid = ACPU_PID_CBT; /* acpu cbt pid */
            break;
        default:
            return VOS_ERR;
      }

      return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CBT_AcpuMsgDispatch
 功能描述  : 将数据包分发出去
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2015年2月27日
     作    者  : x00263027
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 CBT_AcpuMsgDispatch(CBT_RCV_CHAN_CTRL_INFO_STRU * pstCtrlInfo)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulTransId;
    CBT_MSG_COMBINE_INFO_STRU          *pstCombineInfo;
    CBT_UNIFORM_MSG_STRU               *pstCbtMsg;

    pstCombineInfo = &(pstCtrlInfo->stMsgCombineInfo);
    pstCbtMsg      = (CBT_UNIFORM_MSG_STRU *)pstCombineInfo->pstWholeMsg->aucValue;
    ulTransId      = pstCbtMsg->stMsgHeader.ulTransId;

    if ((CBT_STATE_IDLE == g_stAcpuCbtCtrlInfo.ulCbtSwitchOnOff)
     && (APP_OM_ESTABLISH_REQ != pstCbtMsg->usMsgId))
    {
        return VOS_ERR;
    }

    /*消息是建链请求*/
    if (APP_OM_ESTABLISH_REQ == pstCbtMsg->usMsgId)
    {
        g_ulExpRcvTransId  = ulTransId;
    }

    if (g_ulExpRcvTransId != ulTransId)
    {
        /*记录TransId错误的统计信息*/
        pstCtrlInfo->stPcToUeErrRecord.usTransIdErr++;
    }

    g_ulExpRcvTransId = ulTransId + 1;

    /*lint -e40 -e534*/
    CBT_ACPU_DEBUG_TRACE((pstCombineInfo->pstWholeMsg)->aucValue, (pstCombineInfo->pstWholeMsg)->ulLength, CBT_ACPU_DISPATCH_MSG);
    /*lint +e40 +e534*/

    /* 通过OSA 消息发送给CBT */
    if (CCPU_PID_CBT == (pstCombineInfo->pstWholeMsg)->ulReceiverPid)/* 发送到C核 */
    {
        pstCtrlInfo->stPcToUeSucRecord.stCcpuData.ulDataLen += (pstCombineInfo->pstWholeMsg)->ulLength;
        pstCtrlInfo->stPcToUeSucRecord.stCcpuData.ulNum++;
    }
    else /* 发送到A核 */
    {
        pstCtrlInfo->stPcToUeSucRecord.stAcpuData.ulDataLen += (pstCombineInfo->pstWholeMsg)->ulLength;
        pstCtrlInfo->stPcToUeSucRecord.stAcpuData.ulNum++;
    }

    ulRslt = VOS_SendMsg(PC_PID_TOOL, (pstCombineInfo->pstWholeMsg));
    pstCombineInfo->pstWholeMsg = VOS_NULL_PTR;

    if (VOS_OK != ulRslt )
    {
        return VOS_ERR;
    }
    return VOS_OK;

}
/*****************************************************************************
 函 数 名  : CBT_AcpuMsgCombine
 功能描述  : 对消息 组包并发送给对应CPU OM消息处理模块处理
 输入参数  : pucData:   需要处理的数据内容
             ulDataLen: 数据长度

 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月26日
    作    者   : x00263027
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CBT_AcpuMsgCombine(CBT_RCV_CHAN_CTRL_INFO_STRU *pstCtrlInfo, VOS_UINT8 *pucData, VOS_UINT32 usLen)
{
    VOS_UINT32                          ulRslt = VOS_OK;
    VOS_UINT32                          ulTransId;
    VOS_UINT32                          ulTimeStampL;
    VOS_UINT16                          usTimeStampH;

    VOS_UINT8                           ucCurrentSegSn;
    VOS_UINT8                           ucFragFlag;
    VOS_UINT8                           ucEof;

    CBT_MSG_HEAD_STRU                  *pstMsgHeader;
    CBT_UNIFORM_MSG_STRU               *pstAppCbtMsg;
    CBT_MSG_COMBINE_INFO_STRU          *pstCombineInfo;

    pstCombineInfo = &(pstCtrlInfo->stMsgCombineInfo);

    /*Check the input parameter's validity.Make sure empty segment can't pass*/
    if ((VOS_NULL_PTR == pucData)
     || (usLen <= CBT_MSG_HEADER_LENGTH))
    {
        /*lint -e534*/
        LogPrint("CBT_AcpuMsgCombine: The input is wrong.");
        /*lint +e534*/

        pstCtrlInfo->stPcToUeErrRecord.usLenTooShortErr++;

        return VOS_ERR;
    }

    pstMsgHeader = (CBT_MSG_HEAD_STRU *)pucData;
    /*第一个字节固定为0x07(新CBT码流格式的第一个字节). 老的建链消息以5555aaaa开始，将被拦截*/
    if (CBT_MSG_FIRST_BYTE != pstMsgHeader->ucSid)
    {
        pstCtrlInfo->stPcToUeErrRecord.usDatatypeErr++;

        return VOS_ERR;
    }

    ucFragFlag     = pstMsgHeader->stMsgSegment.ucFragFlag;
    ucCurrentSegSn = pstMsgHeader->stMsgSegment.ucFragIndex;
    ucEof          = pstMsgHeader->stMsgSegment.ucEof;

    ulTransId      = pstMsgHeader->ulTransId;
    ulTimeStampL   = pstMsgHeader->stTimeStamp.ulTimestampL;
    usTimeStampH   = pstMsgHeader->stTimeStamp.usTimestampH;

    /*不分段*/
    if (0 == ucFragFlag)
    {
        ucCurrentSegSn = 0;
        ucEof          = CBT_END_FRAME;
    }

    /*When the MSG packet is new, we need initialize the static variable.*/
    if (0 == ucCurrentSegSn)
    {
        if (VOS_NULL_PTR != pstCombineInfo->pstWholeMsg)
        {
            if (VOS_OK != VOS_FreeMsg(PC_PID_TOOL, pstCombineInfo->pstWholeMsg))
            {
            }
            pstCombineInfo->pstWholeMsg = VOS_NULL_PTR;

            pstCtrlInfo->stPcToUeErrRecord.usPacketLostErr++;
        }

        /*The new MSG packet is coming.*/
        pstCombineInfo->ucExpectedSegSn = 0;
        pstCombineInfo->ulMoveLen       = 0;

        pstCombineInfo->ulTransId    = ulTransId;
        pstCombineInfo->ulTimeStampL = ulTimeStampL;
        pstCombineInfo->usTimeStampH = usTimeStampH;

        if (usLen < (CBT_MSG_HEADER_LENGTH + CBT_MSG_IDLEN_LENGTH))
        {
            /*lint -e534*/
            LogPrint("CBT_AcpuMsgCombine: The input parameter is wrong.");
            /*lint +e534*/

            pstCtrlInfo->stPcToUeErrRecord.usMsgLenErr++;

            return VOS_ERR;
        }
        pstAppCbtMsg = (CBT_UNIFORM_MSG_STRU *)pucData;
        pstCombineInfo->ulTotalMsgLen = pstAppCbtMsg->ulMsgLength + CBT_MSG_HEADER_LENGTH + CBT_MSG_IDLEN_LENGTH;

        /* 组包完成后判断是否大于阈值*/
        if (CBT_TOTAL_MSG_MAX_LEN < pstCombineInfo->ulTotalMsgLen)
        {
            pstCtrlInfo->stPcToUeErrRecord.usMsgTooLongErr++;

            /*lint -e534*/
            LogPrint1("CBT_AcpuMsgUCombine: receive first msg pack is too long %d;\r\n",
                        (VOS_INT32)pstCombineInfo->ulTotalMsgLen);
            /*lint +e534*/

            /* 底软最大支持保存1024字节的内容，底软没有提供宏，这里直接使用数字 */
            VOS_ProtectionReboot(OAM_PC_LENGTH_TOO_BIG, (VOS_INT)pstCombineInfo->ulTotalMsgLen, 0, (VOS_CHAR *)pucData, 1024);

            return VOS_ERR;
        }

        /*Allocate the memory space.*/
        pstCombineInfo->pstWholeMsg = VOS_AllocMsg(PC_PID_TOOL, pstCombineInfo->ulTotalMsgLen);
        if (VOS_NULL_PTR == pstCombineInfo->pstWholeMsg)
        {
            /*lint -e534*/
            LogPrint("CBT_AcpuMsgCombine: VOS_AllocMsg fail.");
            /*lint +e534*/

            pstCtrlInfo->stPcToUeErrRecord.usAllocMsg++;

            return VOS_ERR;
        }

        /* 根据SSID查找到相应的PID */
        ulRslt = CBT_AcpuSsIdToPid(pstAppCbtMsg->stMsgHeader.stModemSsid.ucSsid, &(pstCombineInfo->pstWholeMsg)->ulReceiverPid);
        if (VOS_OK != ulRslt)
        {
            /* 释放消息空间 */
            if (VOS_OK != VOS_FreeMsg(PC_PID_TOOL, pstCombineInfo->pstWholeMsg))
            {
            }

            pstCombineInfo->pstWholeMsg = VOS_NULL_PTR;

            pstCtrlInfo->stPcToUeErrRecord.usCpuIdErr++;

            return VOS_ERR;
        }

        if (VOS_OK != VOS_MemCpy((VOS_UINT8*)((pstCombineInfo->pstWholeMsg)->aucValue) + pstCombineInfo->ulMoveLen,
                        pucData, CBT_MSG_HEADER_LENGTH))
        {
        }

        pstCombineInfo->ulMoveLen += CBT_MSG_HEADER_LENGTH;
    }

    /*The expected TransId and Time Stamp is match*/
    if (pstCombineInfo->ulTransId != ulTransId)
    {
        /*Print the error info.*/
        /*lint -e534*/
        LogPrint2("CBT_AcpuMsgCombine: expected TransId is %d, current SN is %d.", pstCombineInfo->ulTransId, ulTransId);
        /*lint +e534*/

        /* 释放消息空间 */
        if (VOS_OK != VOS_FreeMsg(PC_PID_TOOL, pstCombineInfo->pstWholeMsg))
        {
        }

        pstCombineInfo->pstWholeMsg     = VOS_NULL_PTR;
        pstCombineInfo->ucExpectedSegSn = 0;

        pstCtrlInfo->stPcToUeErrRecord.usMsgSnErr++;

        return VOS_ERR;
    }

    if ( (pstCombineInfo->ulTimeStampL != ulTimeStampL) || (pstCombineInfo->usTimeStampH != usTimeStampH) )
    {
        /*Print the error info.*/
        /*lint -e534*/
        LogPrint("CBT_AcpuMsgCombine: expected TimeStamp is inCorrect.");
        /*lint +e534*/

        /* 释放消息空间 */
        if (VOS_OK != VOS_FreeMsg(PC_PID_TOOL, pstCombineInfo->pstWholeMsg))
        {
        }

        pstCombineInfo->pstWholeMsg     = VOS_NULL_PTR;
        pstCombineInfo->ucExpectedSegSn = 0;

        pstCtrlInfo->stPcToUeErrRecord.usTimeStampErr++;

        return VOS_ERR;
    }
    /*The expected MSG pakcet is lost.*/
    if (pstCombineInfo->ucExpectedSegSn != ucCurrentSegSn)
    {
        /*Print the error info.*/
        /*lint -e534*/
        LogPrint2("CBT_AcpuMsgCombine: expected SN is %d, current SN is %d.", pstCombineInfo->ucExpectedSegSn, ucCurrentSegSn);
        /*lint +e534*/

        /* 释放消息空间 */
        if (VOS_OK != VOS_FreeMsg(PC_PID_TOOL, pstCombineInfo->pstWholeMsg))
        {
        }

        pstCombineInfo->pstWholeMsg     = VOS_NULL_PTR;
        pstCombineInfo->ucExpectedSegSn = 0;

        pstCtrlInfo->stPcToUeErrRecord.usMsgSnErr++;

        return VOS_ERR;
    }

    /*We make sure that the memory can't be violated.*/
    if (pstCombineInfo->ulTotalMsgLen < (pstCombineInfo->ulMoveLen + (usLen - CBT_MSG_HEADER_LENGTH)))
    {
        /*lint -e534*/
        LogPrint("CBT_AcpuMsgCombine: The length of the packet is biger than the size of allocated memory.\n");
        /*lint +e534*/

        /* 释放消息空间 */
        if (VOS_OK != VOS_FreeMsg(PC_PID_TOOL, pstCombineInfo->pstWholeMsg))
        {
        }

        pstCombineInfo->pstWholeMsg     = VOS_NULL_PTR;
        pstCombineInfo->ucExpectedSegSn = 0;

        pstCtrlInfo->stPcToUeErrRecord.usNoMemErr++;

        return VOS_ERR;
    }

    if (VOS_OK != VOS_MemCpy((VOS_UINT8*)((pstCombineInfo->pstWholeMsg)->aucValue) + pstCombineInfo->ulMoveLen,
               pucData + CBT_MSG_HEADER_LENGTH, usLen - CBT_MSG_HEADER_LENGTH))
    {
    }

    pstCombineInfo->ulMoveLen += usLen - CBT_MSG_HEADER_LENGTH;
    pstCombineInfo->ucExpectedSegSn ++;

    /*If the current MSG packet is an complete packet.*/
    if (CBT_END_FRAME == ucEof)
    {
        /*It will send the MSG to CBT module.*/
        ulRslt = CBT_AcpuMsgDispatch(pstCtrlInfo);

        pstCombineInfo->ucExpectedSegSn = 0;

        return ulRslt;
    }

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : CBT_AcpuRcvData
 功能描述  : ACPU接收CBT通道上的数据
 输入参数  : pucData:   需要发送的数据内容
             ulSize: 数据长度
             pucRBData:回卷数据内容
             ulRBSize:回卷数据大小
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 修改历史  :
   1.日    期  : 2015年3月2日
     作    者  : x00263027
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 CBT_AcpuRcvData(VOS_UINT8 *pucData, VOS_UINT32 ulSize)
{
    return CBT_AcpuMsgCombine(&g_stAcpuCbtCtrlInfo, pucData, ulSize);
}

/*****************************************************************************
 函 数 名  : CBT_AcpuSendSegData
 功能描述  : 将CBT相关消息经HDLC封装后调接口发走
 输入参数  : pucSrc:指向待发送校准数据
             usSrcLen:数据长度
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 修改历史  :
   1.日    期   : 2015年3月2日
     作    者   : x00263027
     修改内容   : creat
*****************************************************************************/
VOS_UINT32 CBT_AcpuSendSegData(VOS_UINT8 * pucSrc, VOS_UINT16 usSrcLen)
{
    VOS_UINT16                         usHdlcEncLen;
    VOS_UINT32                         ulResult;

    /*进行互斥操作*/
    if ( VOS_OK != VOS_SmP(g_ulTxCbtSem, OM_PV_TIMEOUT) )
    {
        /*lint -e534*/
        LogPrint("CBT_AcpuSendSegData, Error, TxBuffSem VOS_SmP Failed.\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    /* 做HDLC编码 */
    if ( VOS_OK != Om_HdlcEncap(pucSrc,
                                usSrcLen,
                                g_stCbtHdlcEncodeBuf.pucBuf,
                                (VOS_UINT16)g_stCbtHdlcEncodeBuf.ulBufSize,
                                &usHdlcEncLen) )
    {
        if (VOS_OK != VOS_SmV(g_ulTxCbtSem))
        {
        }

        return VOS_ERR;
    }

    ulResult = CBTPPM_OamCbtPortDataSnd(g_stCbtHdlcEncodeBuf.pucBuf, g_stCbtHdlcEncodeBuf.pucRealBuf, usHdlcEncLen);

    if (VOS_OK != VOS_SmV(g_ulTxCbtSem))
    {
    }

    return ulResult;
}

/*****************************************************************************
 Prototype      : CBT_AcpuSendData
 Description    : CBT sends the data to tool side.
 Input          : pstMsg      - 待发送数据.
                  usMsgLen    - 数据长度.
 Output         : void
 Return Value   : VOS_OK - Success.

 History        : ---
    Date        : 2015-02-25
    Author      : x00263027
    Modification: Created function
 *****************************************************************************/
VOS_UINT32 CBT_AcpuSendData(CBT_UNIFORM_MSG_STRU * pstMsg, VOS_UINT16 usMsgLen)
{
    VOS_UINT8                           ucCurSegNum = 0; /*当前段序号*/
    VOS_UINT_PTR                        ulTempAddress;
    VOS_UINT8                           ucMsgCnt    = 1; /*分段的数量*/

    VOS_UINT8                          *pucBuf = VOS_NULL_PTR;
    VOS_UINT8                          *pucTmpBuf;

    /*如果没有建链 并且不是 建链消息的CNF 则直接返回*/
    if ((CBT_STATE_IDLE == g_stAcpuCbtCtrlInfo.ulCbtSwitchOnOff)
     && (OM_APP_ESTABLISH_CNF != pstMsg->usMsgId))
    {
        return VOS_OK;
    }

    /************************ 拆包然后hdlc编码后发送 ***********************/
    /* 计算分包个数 */
    ucMsgCnt = (VOS_UINT8)((usMsgLen - CBT_MSG_HEADER_LENGTH + (CBT_MSG_CONTEXT_MAX_LENGTH - 1))/(CBT_MSG_CONTEXT_MAX_LENGTH));

    /*分配分包结构的内存空间*/
    pucTmpBuf = (VOS_UINT8*)VOS_MemAlloc(PC_PID_TOOL,
                DYNAMIC_MEM_PT, CBT_MSG_SEGMENT_LEN + CBT_RL_DATATYPE_LEN);

    if (VOS_NULL_PTR == pucTmpBuf)
    {
        /*lint -e534*/
        LogPrint("OM_UsbFrameInit:VOS_MemAlloc g_pstSegMsgEx Failed!\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    /*TransId 和 时间戳*/
    pstMsg->stMsgHeader.ulTransId                = g_ulCbtMsgSN++;
    pstMsg->stMsgHeader.stTimeStamp.ulTimestampL = VOS_GetSlice();
    pstMsg->stMsgHeader.stTimeStamp.usTimestampH = 0;
    pstMsg->stMsgHeader.stMsgSegment.ucFragFlag  = 0;

    /* 每包需要添加一字节datatype*/
    pucTmpBuf[0] = 0x01;
    pucBuf = pucTmpBuf + CBT_RL_DATATYPE_LEN;

    ulTempAddress = (VOS_UINT_PTR)pstMsg + CBT_MSG_HEADER_LENGTH;
    usMsgLen -= CBT_MSG_HEADER_LENGTH;

    /* 大于最大分包大小的数据，按照最大分包大小进行数据发送的处理 */
    for (ucCurSegNum = 0; ucCurSegNum < ucMsgCnt-1; ucCurSegNum++)
    {
        pstMsg->stMsgHeader.stMsgSegment.ucFragIndex = ucCurSegNum;
        pstMsg->stMsgHeader.stMsgSegment.ucEof = 0;
        pstMsg->stMsgHeader.stMsgSegment.ucFragFlag = 1;

        /*lint -e534*/
        VOS_MemCpy(pucBuf, (VOS_UINT8*)pstMsg, CBT_MSG_HEADER_LENGTH);
        VOS_MemCpy(pucBuf + CBT_MSG_HEADER_LENGTH, (VOS_UINT8*)ulTempAddress, CBT_MSG_SEGMENT_LEN - CBT_MSG_HEADER_LENGTH);
        /*lint +e534*/
        ulTempAddress += CBT_MSG_SEGMENT_LEN - CBT_MSG_HEADER_LENGTH;

        /* 消息头前加上长度并调用USB接口发送出去 */
        if (VOS_OK != CBT_AcpuSendSegData(pucTmpBuf, CBT_RL_DATATYPE_LEN + CBT_MSG_SEGMENT_LEN))
        {
            /*lint -e534*/
            VOS_MemFree(PC_PID_TOOL, pucTmpBuf);
            /*lint +e534*/

            return VOS_ERR;
        }

        pucBuf = pucTmpBuf + CBT_RL_DATATYPE_LEN;

        /* 计算剩余数据包大小 */
        usMsgLen -= (CBT_MSG_SEGMENT_LEN - CBT_MSG_HEADER_LENGTH);
    }

    pstMsg->stMsgHeader.stMsgSegment.ucFragIndex = ucMsgCnt - 1;
    pstMsg->stMsgHeader.stMsgSegment.ucEof = CBT_END_FRAME;

    /*lint -e534*/
    VOS_MemCpy(pucBuf, (VOS_UINT8*)pstMsg, CBT_MSG_HEADER_LENGTH);
    VOS_MemCpy(pucBuf + CBT_MSG_HEADER_LENGTH, (VOS_UINT8*)ulTempAddress, usMsgLen);
    /*lint +e534*/

    /* 消息头前加上长度并调用USB接口发送出去 */
    if ( VOS_OK != CBT_AcpuSendSegData(pucTmpBuf, CBT_RL_DATATYPE_LEN + usMsgLen + CBT_MSG_HEADER_LENGTH))
    {
        /*lint -e534*/
        VOS_MemFree(PC_PID_TOOL, pucTmpBuf);
        /*lint +e534*/
        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemFree(PC_PID_TOOL, pucTmpBuf);
    /*lint +e534*/
    return VOS_OK;
}


VOS_VOID CBT_AcpuResetMsgHead(CBT_UNIFORM_MSG_STRU * pstCbtMsg)
{
    pstCbtMsg->stMsgHeader.ucSid = 0x07;
    pstCbtMsg->stMsgHeader.ucSessionID = 0x01;

    /*分段信息*/
    pstCbtMsg->stMsgHeader.stMsgSegment.ucMsgType = CBT_MT_CNF;
    pstCbtMsg->stMsgHeader.stMsgSegment.ucFragIndex = 0;
    pstCbtMsg->stMsgHeader.stMsgSegment.ucEof = 1;
    pstCbtMsg->stMsgHeader.stMsgSegment.ucFragFlag = 0;
}

VOS_VOID CBT_AcpuSendResultChannel(CBT_MODEM_SSID_STRU stModemSsid, CBT_COMPONENT_MODE_STRU stCompMode,
                            VOS_UINT16 usReturnPrimId, VOS_UINT32 ulResult)
{
    CBT_UNIFORM_MSG_STRU                stCbtToPcMsg;

    /*lint -e534*/
    VOS_MemSet(&stCbtToPcMsg, 0, sizeof(CBT_UNIFORM_MSG_STRU));
    /*lint +e534*/

    CBT_AcpuResetMsgHead(&stCbtToPcMsg);

    stCbtToPcMsg.stMsgHeader.stModemSsid = stModemSsid;
    stCbtToPcMsg.usMsgId     = usReturnPrimId;
    stCbtToPcMsg.stCompMode  = stCompMode;
    stCbtToPcMsg.ulMsgLength = 4;

    *((VOS_UINT32*)(stCbtToPcMsg.aucPara)) = ulResult;

    /*lint -e534*/
    CBT_AcpuSendData(&stCbtToPcMsg, (VOS_UINT16)sizeof(CBT_UNIFORM_MSG_STRU));
    /*lint +e534*/

    return;
}


VOS_VOID CBT_AcpuSendContentChannel(CBT_MODEM_SSID_STRU stModemSsid, CBT_COMPONENT_MODE_STRU stCompMode,
                             VOS_UINT16 usReturnPrimId, CBT_UNIFORM_MSG_STRU * pstCbtToPcMsg)
{
    CBT_UNIFORM_MSG_STRU               *pstTmpMsg;

    pstTmpMsg = (CBT_UNIFORM_MSG_STRU *)pstCbtToPcMsg;

    CBT_AcpuResetMsgHead(pstTmpMsg);
    pstTmpMsg->stMsgHeader.stModemSsid = stModemSsid;
    pstTmpMsg->usMsgId     = usReturnPrimId;
    pstTmpMsg->stCompMode  = stCompMode;

    /*lint -e534*/
    CBT_AcpuSendData(pstCbtToPcMsg, (VOS_UINT16)(pstCbtToPcMsg->ulMsgLength + CBT_MSG_HEAD_EX_LENGTH));
    /*lint +e534*/
    return;
}


/*****************************************************************************
 函 数 名  : CBT_AcpuRcvSucShow
 功能描述  : 打印数据从PC侧发往UE侧时正常处理的数据
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2015年3月16日
     作    者  : x00263027
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID CBT_AcpuRcvSucShow(VOS_VOID)
{
    CBT_ACPU_PC_UE_SUC_STRU              *pstPcToUeSucRecord = &(g_stAcpuCbtCtrlInfo.stPcToUeSucRecord);

    /*lint -e534*/
    vos_printf("\r\n *****CBT receive channel success info show *******\r\n");

    vos_printf("Total Data Recv From PC: num:%6u, len:%6u\n",
                pstPcToUeSucRecord->stTotalData.ulNum, pstPcToUeSucRecord->stTotalData.ulDataLen);

    vos_printf("Data after Hdlc decap:   num:%6u, len:%6u\n",
                pstPcToUeSucRecord->stHdlcDecapData.ulNum, pstPcToUeSucRecord->stHdlcDecapData.ulDataLen);

    vos_printf("Link Data Recv From PC: num:%6u, len:%6u\n",
                pstPcToUeSucRecord->stLinkData.ulNum, pstPcToUeSucRecord->stLinkData.ulDataLen);

    vos_printf("CCPU Data Recv From PC: num:%6u, len:%6u\n",
                pstPcToUeSucRecord->stCcpuData.ulNum, pstPcToUeSucRecord->stCcpuData.ulDataLen);

    vos_printf("ACPU Data Recv From PC: num:%6u, len:%6u\n",
                pstPcToUeSucRecord->stAcpuData.ulNum, pstPcToUeSucRecord->stAcpuData.ulDataLen);

    vos_printf("Data Send by ICC: num:%6u, len:%6u, slice:%6u\n",
                pstPcToUeSucRecord->stICCSendSUCInfo.ulICCOmSendMsgNum,
                pstPcToUeSucRecord->stICCSendSUCInfo.ulICCOmSendLen,
                pstPcToUeSucRecord->stICCSendSUCInfo.ulICCOmSendSlice);

    vos_printf("Rls Data Recv From PC: num:%6u, slice:%6u\n",
                pstPcToUeSucRecord->stRlsData.ulNum, pstPcToUeSucRecord->stRlsData.ulDataLen);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : CBT_AcpuRcvErrShow
 功能描述  : 打印数据从PC侧发往UE侧时异常数据
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2015年3月016日
     作    者  : x00263027
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID CBT_AcpuRcvErrShow(VOS_VOID)
{
    CBT_ACPU_PC_UE_FAIL_STRU             *pstPcToUeErrRecord = &(g_stAcpuCbtCtrlInfo.stPcToUeErrRecord);

    /*lint -e534*/
    vos_printf("\r\n *****CBT receive channel error info show *******\r\n");

    vos_printf("Total Lost Data Recv From PC: num:%6u, len:%6u\n",
            pstPcToUeErrRecord->stLostData.ulNum, pstPcToUeErrRecord->stLostData.ulDataLen);

    vos_printf("Number of Frame Decap Err: num:%6u\n", pstPcToUeErrRecord->ulFrameDecapErr);

    vos_printf("Number of Packet Len Err: num:%6u\n", pstPcToUeErrRecord->usPacketLenErr);

    vos_printf("Number of Too Short Err: num:%6u\n", pstPcToUeErrRecord->usLenTooShortErr);

    vos_printf("Number of Seg Len Err: num:%6u\n", pstPcToUeErrRecord->usSegLenErr);

    vos_printf("Number of Seg Num Err: num:%6u\n", pstPcToUeErrRecord->usSegNumErr);

    vos_printf("Number of DataType Err: num:%6u\n", pstPcToUeErrRecord->usDatatypeErr);

    vos_printf("Number of Too Long Err: num:%6u\n", pstPcToUeErrRecord->usMsgTooLongErr);

    vos_printf("Number of Cpu Id Err: num:%6u\n", pstPcToUeErrRecord->usCpuIdErr);

    vos_printf("Number of No Mem Err: num:%6u\n", pstPcToUeErrRecord->usNoMemErr);

    vos_printf("Number of Data Head Err: num:%6u\n", pstPcToUeErrRecord->usDataHeadErr);

    vos_printf("Number of Msg Len Err: num:%6u\n", pstPcToUeErrRecord->usMsgLenErr);

    vos_printf("Number of Msg Sn Err: num:%6u\n", pstPcToUeErrRecord->usMsgSnErr);

    vos_printf("Number of Msg TransId Err: num:%6u\n", pstPcToUeErrRecord->usTransIdErr);

    vos_printf("Number of Packet Lost Err: num:%6u\n", pstPcToUeErrRecord->usPacketLostErr);

    vos_printf("Number of TimeStamp Err: num:%6u\n", pstPcToUeErrRecord->usTimeStampErr);

    vos_printf("Number of Link Data Len Err: num:%6u\n", pstPcToUeErrRecord->usLinkDataLenErr);

    vos_printf("Number of Alloc msg Mem: num: %6u\n",pstPcToUeErrRecord->usAllocMsg);

    vos_printf("Number of Lost Msg Because Switch Is IDLE: num: %6u\n",pstPcToUeErrRecord->usLinkStatusErr);

    vos_printf("Data Send err by ICC: num:%6u, len:%6u, slice:%6u\n",
            pstPcToUeErrRecord->stICCSendFailInfo.ulICCOmSendErrNum,
            pstPcToUeErrRecord->stICCSendFailInfo.ulICCOmSendErrLen,
            pstPcToUeErrRecord->stICCSendFailInfo.ulICCOmSendErrSlice);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : CBT_OpenLog
 功能描述  : 打印当前OM通道的状态
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2015年11月18日
     作    者  : j00334311
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID CBT_AcpuOpenLog(VOS_UINT32 ulFlag)
{
    g_ulCbtAcpuDbgFlag = ulFlag;

    return;
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif
