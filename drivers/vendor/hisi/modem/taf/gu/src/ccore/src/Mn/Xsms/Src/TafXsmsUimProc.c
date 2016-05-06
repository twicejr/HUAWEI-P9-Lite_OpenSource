/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsUimProc.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年10月31日
  功能描述   : 1X SMS(Short Message Service)任务处理USIMM发来的消息函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXsmsUimProc.h"
#include "TafXsmsCtx.h"
#include "TafXsmsTimer.h"
#include "TafXsmsSndAt.h"
#include "TafXsmsMtFsmMain.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_UIM_PROC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
TAF_XSMS_INIT_CTRL_INFO_STRU   g_stTafXsmsInitCtrlInfo;

TAF_XSMS_CTRL_INFO_STRU        g_stTafXsmsReqCtrlInfo;

TAF_XSMS_FILETABLE_STRU         g_stTafXsmsFileTable[] =
{
    {TAF_XSMS_EFSMS_FILEID,     USIMM_CDMA_EFSMS_ID,    USIMM_CSIM_EFSMS_ID},
    {TAF_XSMS_EFSMSS_FILEID,    USIMM_CDMA_EFSMSS_ID,   USIMM_CSIM_EFSMSS_ID},
    {TAF_XSMS_EFIMSIT_FILEID,   USIMM_CDMA_EFIMSIM_ID,  USIMM_CSIM_EFIMSIM_ID}
};

/*****************************************************************************
  3 函数定义
*****************************************************************************/

/*****************************************************************************
函 数 名  :TAF_XSMS_ChangeFileID
功能描述  :转换字符串格式
输入参数  :

输出参数  :无
返 回 值  :VOS_OK    :失败
           VOS_ERR   :成功

修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_VOID TAF_XSMS_ChangeFileID(TAF_XSMS_FILEID_ENUM_ENUM_UINT32   enFileID,
                                            USIMM_DEF_FILEID_ENUM_UINT32       *penDefID)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    if (USIMM_CARD_UIM == pstInitCtrlInfoAddr->enCardType)
    {
        *penDefID = g_stTafXsmsFileTable[enFileID].enUIMID;
    }
    else
    {
        *penDefID = g_stTafXsmsFileTable[enFileID].enCSIMID;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_GetCdmaFileReq
功能描述  :读取CDMA文件操作　
输入参数  :ulSenderPid:调用者ID
           usEfId:文件ID
           ucRecordNum:读取记录号
           enAppType:读取应用的标识号
输出参数  :无
返 回 值  :
调用函数  :VOS_AllocMsg
           VOS_SendMsg
被调函数  :
修订记录  :
1. 日    期   : 2014年7月4日
   作    者   : g00256031
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 TAF_XSMS_GetFileReq(USIMM_DEF_FILEID_ENUM_UINT32   enFileID,
                                        VOS_UINT32                    ulSendPara,
                                        VOS_UINT8                      ucIndex)
{
    USIMM_READFILE_REQ_STRU     *pstMsg;
    VOS_CHAR                    *pcFilePath;

    if (VOS_ERR == USIMM_ChangeDefFileToPath(enFileID, &pcFilePath))
    {
        return VOS_ERR; /*返回函数错误信息*/
    }

    pstMsg = (USIMM_READFILE_REQ_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                sizeof(USIMM_READFILE_REQ_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR; /*返回函数错误信息*/
    }

    /*填充消息内容*/
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;
    pstMsg->stMsgHeader.enMsgName       = USIMM_READFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_CDMA_APP;
    pstMsg->ucRecordNum                 = ucIndex;

    pstMsg->stFilePath.ulPathLen    = VOS_StrLen(pcFilePath);

    PS_MEM_CPY(pstMsg->stFilePath.acPath, pcFilePath, pstMsg->stFilePath.ulPathLen);

    return VOS_SendMsg(UEPS_PID_XSMS, pstMsg);
}

/*****************************************************************************
函 数 名  :USIMM_GetCdmaFileReq
功能描述  :读取CDMA文件操作　
输入参数  :ulSenderPid:调用者ID
           usEfId:文件ID
           ucRecordNum:读取记录号
           enAppType:读取应用的标识号
输出参数  :无
返 回 值  :
调用函数  :VOS_AllocMsg
           VOS_SendMsg
被调函数  :
修订记录  :
1. 日    期   : 2014年7月4日
   作    者   : g00256031
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 TAF_XSMS_SetFileReq(TAF_XSMS_FILEID_ENUM_ENUM_UINT32 enXSMSID,
                                        VOS_UINT32                      ulSendPara,
                                        TAF_XSMS_SETFILE_INFO_STRU      *pstFileInfo)
{
    USIMM_UPDATEFILE_REQ_STRU       *pstMsg;
    VOS_CHAR                        *pcFilePath;
    USIMM_DEF_FILEID_ENUM_UINT32    enFileID;

    TAF_XSMS_ChangeFileID(enXSMSID, &enFileID);

    if (VOS_ERR == USIMM_ChangeDefFileToPath(enFileID, &pcFilePath))
    {
        return VOS_ERR; /*返回函数错误信息*/
    }

    pstMsg = (USIMM_UPDATEFILE_REQ_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                sizeof(USIMM_UPDATEFILE_REQ_STRU)-VOS_MSG_HEAD_LENGTH+pstFileInfo->usEfLen);

    if(VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR; /*返回函数错误信息*/
    }

    /*填充消息内容*/
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;
    pstMsg->stMsgHeader.enMsgName       = USIMM_UPDATEFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_CDMA_APP;
    pstMsg->ucRecordNum                 = pstFileInfo->ucRecordNum;
    pstMsg->usDataLen                   = pstFileInfo->usEfLen;

    PS_MEM_CPY(pstMsg->aucContent, pstFileInfo->pucEfContent, pstFileInfo->usEfLen);

    pstMsg->stFilePath.ulPathLen        = VOS_StrLen(pcFilePath);

    PS_MEM_CPY(pstMsg->stFilePath.acPath, pcFilePath, pstMsg->stFilePath.ulPathLen);

    return VOS_SendMsg(UEPS_PID_XSMS, pstMsg);
}

/*****************************************************************************
 函 数 名  :SI_PB_QueryFileReq
 功能描述  :找到EFSMS空闲条目
 输入参数  :无
 输出参数  :pucIndex:找到的空闲记录
 返 回 值  : VOS_OK:找到空闲记录
             VOS_ERR:未找到空闲记录
 调用函数  :无

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32 TAF_XSMS_QueryFileReq(TAF_XSMS_FILEID_ENUM_ENUM_UINT32 enXSMSID)
{
    USIMM_QUERYFILE_REQ_STRU        *pstMsg;
    VOS_CHAR                        *pcFilePath;
    USIMM_DEF_FILEID_ENUM_UINT32    enFileID;

    TAF_XSMS_ChangeFileID(enXSMSID, &enFileID);

    if (VOS_ERR == USIMM_ChangeDefFileToPath(enFileID, &pcFilePath))
    {
        return VOS_ERR; /*返回函数错误信息*/
    }

    pstMsg = (USIMM_QUERYFILE_REQ_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                    sizeof(USIMM_QUERYFILE_REQ_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR; /*返回函数错误信息*/
    }

    /*填充消息内容*/
    pstMsg->stMsgHeader.enAppType       = USIMM_CDMA_APP;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_QUERYFILE_REQ;
    pstMsg->stMsgHeader.ulSendPara      = 0;

    pstMsg->stFilePath.ulPathLen        = VOS_StrLen(pcFilePath);

    PS_MEM_CPY(pstMsg->stFilePath.acPath, pcFilePath, pstMsg->stFilePath.ulPathLen);

    return VOS_SendMsg(MAPS_PB_PID, pstMsg);
}

/*****************************************************************************
 函 数 名  :TAF_XSMS_FindFreeIndex
 功能描述  :找到EFSMS空闲条目
 输入参数  :无
 输出参数  :pucIndex:找到的空闲记录
 返 回 值  : VOS_OK:找到空闲记录
             VOS_ERR:未找到空闲记录
 调用函数  :无

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_FindFreeIndex(VOS_UINT8 *pucIndex)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    VOS_UINT8                           i;

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    /* 根据当前的总索引查询空记录 */
    for (i = 1; i <= pstInitCtrlInfoAddr->ucMaxRecord; i++)
    {
        if (TAF_XSMS_EFSMS_STATUS_FREE == TAF_XSMS_GetBitFromBuf(pstInitCtrlInfoAddr->aucFreeIndex, i))
        {
            break;
        }
    }

    /* 内容全满 */
    if (i > pstInitCtrlInfoAddr->ucMaxRecord)
    {
        return VOS_ERR;
    }

    *pucIndex = i;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  :TAF_XSMS_GetBitFromBuf
 功能描述  :在数据中设定Bit位的值
 输入参数  :ucDataBuf:   数据内容
            ulBitNo:     Bit号,从1开始
            ulValue:     需要设置的值,0或1
 输出参数  :无
 返 回 值  : 1:有效、0:无效
 调用函数  :无

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_SetBitToBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo,VOS_UINT32 ulValue)
{
    VOS_UINT32                          ulOffset;
    VOS_UINT8                           ucBit;

    ulOffset = (ulBitNo - 1)/ 8;

    ucBit    = (VOS_UINT8)((ulBitNo - 1)%8);

    if (VOS_NULL != ulValue)
    {
        /*lint -e701 */
        pucDataBuf[ulOffset] |= (VOS_UINT8)(0x1<<ucBit);
        /*lint +e701 */
    }
    else
    {
        /*lint -e701 */
        pucDataBuf[ulOffset] &= (~(VOS_UINT8)(0x1<<ucBit));
        /*lint +e701 */
    }

    return;
}

/*****************************************************************************
 函 数 名  :TAF_XSMS_GetBitFromBuf
 功能描述  :从数据中获取指定Bit位的值　
 输入参数  :ucDataBuf:   数据内容
           ulBitNo:     Bit号，从1开始
 输出参数  :无
 返 回 值  : 1:有效、0:无效
 调用函数  :无

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_GetBitFromBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo)
{
    VOS_UINT32                          ulOffset;
    VOS_UINT8                           ucBit;

    ulOffset = (ulBitNo - 1)/ 8;

    ucBit    = (VOS_UINT8)((ulBitNo - 1)%8);

    return (pucDataBuf[ulOffset]>>ucBit)&0x1;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_AtSmsDeleteReq
 功能描述  : AT命令的删除请求
 输入参数  : ucLen:记录长度
             ucIndex:记录索引，从1开始
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_AtSmsDeleteReq(VOS_UINT8 ucIndex)
{
    TAF_XSMS_SETFILE_INFO_STRU          stSetFileReq;
    VOS_UINT8                           aucData[TAF_XSMS_RECORD_LEN_MAX];
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    /* 删除操作，第一个字节为FREE状态，第二个字节表示长度，其它全为FF */
    VOS_MemSet(aucData, (VOS_CHAR)0xFF, sizeof(aucData));

    aucData[0] = TAF_XSMS_UIM_MSG_STATUS_FREE;
    aucData[1] = VOS_NULL;

    /* 填充写文件请求结构 */
    stSetFileReq.ucRecordNum  = ucIndex;
    stSetFileReq.usEfLen      = pstInitCtrlInfoAddr->ucRecordLen;
    stSetFileReq.pucEfContent = aucData;

    /* 透传参数指示是从AT来的请求 */
    return TAF_XSMS_SetFileReq(TAF_XSMS_EFSMS_FILEID, TAF_XSMS_UIM_REQ_TYPE_AT, &stSetFileReq);
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MsgIdUpdataReq
 功能描述  : MO过程中更新MESSAGE ID的处理
 输入参数  : pucMsgId:要写入的MESSAGE ID的内容
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgIdUpdataReq(VOS_UINT8 *pucMsgId)
{
    TAF_XSMS_SETFILE_INFO_STRU          stSetFileReq;

    /* 填充写文件请求结构 */
    stSetFileReq.ucRecordNum  = 0;
    stSetFileReq.usEfLen      = 2;
    stSetFileReq.pucEfContent = pucMsgId;

    /* 透传参数指示是从MO来的请求 */
    return TAF_XSMS_SetFileReq(TAF_XSMS_EFSMSS_FILEID, TAF_XSMS_UIM_REQ_TYPE_MO, &stSetFileReq);
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_AtSmsWriteReq
 功能描述  : AT命令的写入请求
 输入参数  : ucLen:记录长度
             pucData:要写入的内容
             ucIndex:记录索引，从1开始
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_AtSmsWriteReq(VOS_UINT8 ucLen, VOS_UINT8 *pucData, VOS_UINT8 ucIndex)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    TAF_XSMS_SETFILE_INFO_STRU         stSetFileReq;
    VOS_UINT8                           aucData[TAF_XSMS_RECORD_LEN_MAX];

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    /* 未使用的 */
    VOS_MemSet(aucData, (VOS_CHAR)0xFF, sizeof(aucData));

    PS_MEM_CPY(aucData, pucData, ucLen);

    /* 填充写文件请求结构 */
    stSetFileReq.ucRecordNum  = ucIndex;
    stSetFileReq.usEfLen      = pstInitCtrlInfoAddr->ucRecordLen;
    stSetFileReq.pucEfContent = aucData;

    /* 透传参数指示是从AT来的请求 */
    return TAF_XSMS_SetFileReq(TAF_XSMS_EFSMS_FILEID, TAF_XSMS_UIM_REQ_TYPE_AT, &stSetFileReq);
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_PrlWriteReq
 功能描述  : MT过程中PRL文件更新请求
 输入参数  : ucLen:记录长度
             pucPrl:PRL文件内容
             ucIndex:记录索引，从1开始
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_PrlWriteReq(VOS_UINT8 ucLen, VOS_UINT8 *pucPrl, VOS_UINT8 ucIndex)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    TAF_XSMS_SETFILE_INFO_STRU          stSetFileReq;
    VOS_UINT8                           aucData[TAF_XSMS_RECORD_LEN_MAX];

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    VOS_MemSet(aucData, 0, sizeof(aucData));

    PS_MEM_CPY(aucData, pucPrl, ucLen);

    /* 填充写文件请求结构 */
    stSetFileReq.ucRecordNum  = ucIndex;
    stSetFileReq.usEfLen      = pstInitCtrlInfoAddr->ucRecordLen;
    stSetFileReq.pucEfContent = aucData;

    /* 透传参数指示是从MT过程来的请求 */
    return TAF_XSMS_SetFileReq(TAF_XSMS_EFSMS_FILEID, TAF_XSMS_UIM_REQ_TYPE_MT, &stSetFileReq);
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_CommonFileWriteReq
 功能描述  : MT过程中文件更新请求
 输入参数  : ucLen:记录长度
             pucData:PRL文件内容
             ucIndex:记录索引，从1开始
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_CommonFileWriteReq(VOS_UINT8 ucLen, VOS_UINT8 *pucData, VOS_UINT8 ucIndex)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    TAF_XSMS_SETFILE_INFO_STRU          stSetFileReq;
    VOS_UINT8                           aucData[TAF_XSMS_RECORD_LEN_MAX];

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    VOS_MemSet(aucData, (VOS_CHAR)0xFF, sizeof(aucData));

    aucData[0] = TAF_XSMS_STATUS_REC_UNREAD;
    aucData[1] = ucLen;

    PS_MEM_CPY(aucData + 2, pucData, ucLen);

    /* 填充写文件请求结构 */
    stSetFileReq.ucRecordNum  = ucIndex;
    stSetFileReq.usEfLen      = pstInitCtrlInfoAddr->ucRecordLen;
    stSetFileReq.pucEfContent = aucData;

    /* 透传参数指示是从MT过程来的请求 */
    return TAF_XSMS_SetFileReq(TAF_XSMS_EFSMS_FILEID, TAF_XSMS_UIM_REQ_TYPE_MT, &stSetFileReq);
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_PrlReadReq
 功能描述  : MT过程中PRL文件读取请求
 输入参数  : ucIndex:记录索引，从1开始
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_PrlReadReq(VOS_UINT8 ucIndex)
{
    USIMM_DEF_FILEID_ENUM_UINT32    enDefID;

    TAF_XSMS_ChangeFileID(TAF_XSMS_EFSMS_FILEID, &enDefID);

    /* 透传参数指示是从MT过程来的请求 */
    return TAF_XSMS_GetFileReq(enDefID, TAF_XSMS_UIM_REQ_TYPE_MT, ucIndex);
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_InitFileReadReq
 功能描述  : 初始化过程中文件读取请求
 输入参数  : ucIndex:记录索引，记录文件从1开始，透明文件从0开始
             usFileId:文件ID
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_InitFileReadReq(VOS_UINT8 ucIndex, VOS_UINT32 enFileId)
{
    USIMM_DEF_FILEID_ENUM_UINT32    enDefID;

    TAF_XSMS_ChangeFileID(enFileId, &enDefID);

    /* 透传参数指示是从初始化过程来的请求 */
    return TAF_XSMS_GetFileReq(enDefID, TAF_XSMS_UIM_REQ_TYPE_INIT, ucIndex);
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_PihStatusIndProc
 功能描述  : 卡状态变更消息
 输入参数  : pstMsg:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_PihStatusIndProc(USIMM_CARDSTATUS_IND_STRU *pstMsg)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    /* 收到无卡状态，停止初始化 */
    if (USIMM_CARD_SERVIC_ABSENT == pstMsg->stCsimUimInfo.enCardService)
    {
        TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT);
        /*VOS_MemSet(pstInitCtrlInfoAddr, 0, sizeof(TAF_XSMS_INIT_CTRL_INFO_STRU));*/
        TAF_XSMS_MsgInitInd(pstInitCtrlInfoAddr->ucMaxRecord);

        return;
    }

    /* 初始化未完成情况下收到卡服务可用时开始初始化，其它状态时清空初始化状态 */
    if (TAF_XSMS_INIT_STATUS_NOT_INIT == pstInitCtrlInfoAddr->enSmsInitState)
    {
        /* 不是UIM卡也不是CSIM卡时不需要初始化 */
        if ((USIMM_CARD_UIM != pstMsg->stCsimUimInfo.enCardType)
            && (USIMM_CARD_CSIM != pstMsg->stCsimUimInfo.enCardType))
        {
            return;
        }

        /* 保存卡类型 */
        pstInitCtrlInfoAddr->enCardType = pstMsg->stCsimUimInfo.enCardType;

        if (USIMM_CARD_SERVIC_AVAILABLE == pstMsg->stCsimUimInfo.enCardService)
        {
            /* 启动定时器 */
            TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT, TI_TAF_XSMS_TIMER_USIMM_INIT_LEN);

            pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile  = TAF_XSMS_EFIMSIT_FILEID;

            (VOS_VOID)TAF_XSMS_InitFileReadReq(0, TAF_XSMS_EFIMSIT_FILEID);
        }
        else
        {
            VOS_MemSet(pstInitCtrlInfoAddr, 0, sizeof(TAF_XSMS_INIT_CTRL_INFO_STRU));
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_PihMsgProc
 功能描述  : PIH消息处理函数
 输入参数  : pstMsg:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_PihMsgProc(TAF_XSMS_UIM_MSG_STRU *pstMsg)
{
    switch (pstMsg->ulMsgName)
    {
        /* 卡状态变更消息 */
        case USIMM_CARDSTATUS_IND:
            TAF_XSMS_PihStatusIndProc((USIMM_CARDSTATUS_IND_STRU *)pstMsg);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_InitUsimmMaxRecordRspMsgProc
 功能描述  : 初始化过程获取6F3C文件最大记录数请求回复的处理函数
 输入参数  : pstMsg:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_InitUsimmMaxRecordRspMsgProc(USIMM_QUERYFILE_CNF_STRU *pstMsg)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;

    /* 获取文件最大记录数出错不再尝试 */
    if (VOS_OK != pstMsg->stCmdResult.ulResult)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_InitUsimmMaxRecordRspMsgProc:Get Max Record Err");

        return;
    }

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    /* 记录EFSMS的记录数和记录长度 */
    pstInitCtrlInfoAddr->ucMaxRecord = pstMsg->ucRecordNum;
    pstInitCtrlInfoAddr->ucRecordLen = pstMsg->ucRecordLen;

    /* 记录当前EFSMS读取的记录数和文件ID */
    pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile  = TAF_XSMS_EFSMS_FILEID;
    pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex = 1;

    /* 读取EFSMS记录并启动定时器 */
    TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT, TI_TAF_XSMS_TIMER_USIMM_INIT_LEN);
    (VOS_VOID)TAF_XSMS_InitFileReadReq(pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex, TAF_XSMS_EFSMS_FILEID);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_InitEfsmsFileMsgProc
 功能描述  : 初始化过程读取6F3C文件请求回复处理函数
 输入参数  : pstMsg:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_InitEfsmsFileMsgProc(USIMM_READFILE_CNF_STRU *pstMsg)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;

    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT);

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    /* 读取成功时根据第一个字节的状态将索引分别设置为已使用和未使用 */
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        if (TAF_XSMS_UIM_MSG_STATUS_FREE == pstMsg->aucEf[0])
        {
            TAF_XSMS_SetBitToBuf(pstInitCtrlInfoAddr->aucFreeIndex,
                                 pstMsg->ucRecordNum,
                                 TAF_XSMS_EFSMS_STATUS_FREE);
        }
        else
        {
            TAF_XSMS_SetBitToBuf(pstInitCtrlInfoAddr->aucFreeIndex,
                                 pstMsg->ucRecordNum,
                                 TAF_XSMS_EFSMS_STATUS_USED);
        }
    }
    /* 读取失败时设置为已使用，记录号不能使用USIMM返回的INDEX，要用XSMS全局变量保存的INDEX */
    else
    {
        TAF_XSMS_SetBitToBuf(pstInitCtrlInfoAddr->aucFreeIndex,
                             pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex,
                             TAF_XSMS_EFSMS_STATUS_USED);
    }

    /* 记录当前EFSMS读取的记录数和文件ID */
    pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile  = TAF_XSMS_EFSMS_FILEID;
    pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex++;

    /* 如果索引值大于最大记录数，初始化已完成，上报AT */
    if (pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex > pstInitCtrlInfoAddr->ucMaxRecord)
    {
        TAF_XSMS_MsgInitInd(pstInitCtrlInfoAddr->ucMaxRecord);
        pstInitCtrlInfoAddr->enSmsInitState = TAF_XSMS_INIT_STATUS_FINISH;
    }
    else
    {
        /* 读取EFSMS记录并启动定时器 */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT, TI_TAF_XSMS_TIMER_USIMM_INIT_LEN);
        (VOS_VOID)TAF_XSMS_InitFileReadReq(pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex, TAF_XSMS_EFSMS_FILEID);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_InitTimeOutMsgProc
 功能描述  : 初始化过程读取文件请求超时处理函数
 输入参数  : pstMsg:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_InitTimeOutMsgProc(VOS_VOID)
{
    VOS_UINT32                          ulRslt = VOS_ERR;
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    if (TAF_XSMS_EFSMS_FILEID == pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_InitTimeOutMsgProc:Read EFSMS Time Out");

        /* 读取超时将此记录设置为已使用 */
        TAF_XSMS_SetBitToBuf(pstInitCtrlInfoAddr->aucFreeIndex,
                             pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex,
                             TAF_XSMS_EFSMS_STATUS_USED);

        pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex++;

        /* 继续读取下一条记录，如果索引值大于最大记录数，初始化已完成，上报AT */
        if (pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex > pstInitCtrlInfoAddr->ucMaxRecord)
        {
            TAF_XSMS_MsgInitInd(pstInitCtrlInfoAddr->ucMaxRecord);
            pstInitCtrlInfoAddr->enSmsInitState = TAF_XSMS_INIT_STATUS_FINISH;

            return;
        }
        else
        {
            /* 读取EFSMS记录 */
            ulRslt = TAF_XSMS_InitFileReadReq(pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex, TAF_XSMS_EFSMS_FILEID);
        }
    }
    /* 读取IMSI超时，读取下一个文件EFSMSS */
    else if (TAF_XSMS_EFIMSIT_FILEID == pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_InitTimeOutMsgProc:Read EFIMSI Time Out");

        pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile  = TAF_XSMS_EFSMSS_FILEID;
        pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex = VOS_NULL;

        /* 读取EFSMSS记录 */
        ulRslt = TAF_XSMS_InitFileReadReq(pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex, TAF_XSMS_EFSMSS_FILEID);
    }
    /* 读取EFSMSS超时，MESSAGE ID设置为0，读取下一个文件EFSMS */
    else if (TAF_XSMS_EFSMSS_FILEID == pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_InitTimeOutMsgProc:Read EFSMSS Time Out");

        pstInitCtrlInfoAddr->usMessageId                = VOS_NULL;
        pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile  = TAF_XSMS_EFSMS_FILEID;
        pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex = VOS_NULL;

        /* 获取EFSMS记录的最大记录数，不启动定时器 */
        TAF_XSMS_QueryFileReq(TAF_XSMS_EFSMS_FILEID);
    }
    else
    {
        /* do nothing make pclint happy */
        return;
    }

    /* 启动定时器 */
    if (VOS_OK == ulRslt)
    {
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT, TI_TAF_XSMS_TIMER_USIMM_INIT_LEN);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_InitUsimmGetFileRspMsgProc
 功能描述  : 初始化过程读取文件请求回复处理函数
 输入参数  : pstMsg:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_InitUsimmGetFileRspMsgProc(USIMM_READFILE_CNF_STRU *pstMsg)
{
    VOS_UINT32                          ulRslt = VOS_ERR;
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    VOS_UINT16                          usMessageId;
    VOS_UINT8                          *pucTmp;
    VOS_UINT32                          ulEFID;

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    (VOS_VOID)USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstMsg->stFilePath.ulPathLen, pstMsg->stFilePath.acPath, &ulEFID);

    switch (ulEFID)
    {
        /* 读取IMSI成功后读取EFSMSS文件 */
        case USIMM_CDMA_EFIMSIM_ID:
        case USIMM_CSIM_EFIMSIM_ID:
            TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT);

            pucTmp = pstMsg->aucEf;

            if (VOS_OK == pstMsg->stCmdResult.ulResult)
            {
                PS_MEM_CPY(pstInitCtrlInfoAddr->aucImsi, (VOS_UINT8*)(VOS_UINT32)pucTmp, TAF_XSMS_IMSI_LEN_MAX);
            }

            /* 记录当前读取的文件ID为EFSMSS */
            pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile  = TAF_XSMS_EFSMSS_FILEID;

            ulRslt = TAF_XSMS_InitFileReadReq(0, TAF_XSMS_EFSMSS_FILEID);

            break;

        /* 读取SMSS成功后获取EFSMS文件的最大记录数 */
        case USIMM_CDMA_EFSMSS_ID:
        case USIMM_CSIM_EFSMSS_ID:
            TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT);

            if (VOS_OK == pstMsg->stCmdResult.ulResult)
            {
                /* 网络字节序到主机字节序转换 */
                usMessageId = pstMsg->aucEf[0] << 8;
                usMessageId += pstMsg->aucEf[1];
                pstInitCtrlInfoAddr->usMessageId = usMessageId;

                /* 记录当前读取的文件ID为EFSMS */
                pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile  = TAF_XSMS_EFSMS_FILEID;
                pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex = VOS_NULL;
            }

            /* 获取最大记录数不启动保护定时器 */
            TAF_XSMS_QueryFileReq(TAF_XSMS_EFSMS_FILEID);

            break;

        case USIMM_CSIM_EFSMS_ID:
        case USIMM_CDMA_EFSMS_ID:
            /* 在函数里面启动保护定时器 */
            TAF_XSMS_InitEfsmsFileMsgProc(pstMsg);
            break;

        default:
            break;
    }

    if (VOS_OK == ulRslt)
    {
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT, TI_TAF_XSMS_TIMER_USIMM_INIT_LEN);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MtGetFileRspMsgProc
 功能描述  : MT过程读取文件请求回复处理函数
 输入参数  : pstMsg:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_MtGetFileRspMsgProc(USIMM_READFILE_CNF_STRU *pstMsg)
{
    VOS_UINT32              ulEFID;

    (VOS_VOID)USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstMsg->stFilePath.ulPathLen, pstMsg->stFilePath.acPath, &ulEFID);

    /* MT过程中只处理6F3C */
    if ((USIMM_CDMA_EFSMS_ID == ulEFID)||(USIMM_CSIM_EFSMS_ID == ulEFID))
    {
        TAF_XSMS_MtFsmMainProc((MsgBlock *)pstMsg);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_UsimmGetFileRspMsgProc
 功能描述  : XSMS模块读取文件请求回复处理函数
 输入参数  : pstMsg:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_UsimmGetFileRspMsgProc(USIMM_READFILE_CNF_STRU *pstMsg)
{
    /* 只有在初始化和MT过程中才有读取文件的操作 */
    switch (pstMsg->stCmdResult.ulSendPara)
    {
        case TAF_XSMS_UIM_REQ_TYPE_INIT:
            TAF_XSMS_InitUsimmGetFileRspMsgProc(pstMsg);
            break;

        case TAF_XSMS_UIM_REQ_TYPE_MT:
            TAF_XSMS_MtGetFileRspMsgProc(pstMsg);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_AtSetFileRspMsgProc
 功能描述  : AT命令下发写文件请求回复处理函数
 输入参数  : pstMsg:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_AtSetFileRspMsgProc(USIMM_UPDATEFILE_CNF_STRU *pstMsg)
{
    TAF_XSMS_CTRL_INFO_STRU            *pstCtrlInfoAddr;
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulEFDefID;

    (VOS_VOID)USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstMsg->stFilePath.ulPathLen, pstMsg->stFilePath.acPath, &ulEFDefID);

    /* AT命令的写文件操作只有6F3C */
    if ((USIMM_CDMA_EFSMS_ID != ulEFDefID)&&(USIMM_CSIM_EFSMS_ID != ulEFDefID))
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_AtSetFileRspMsgProc:Rcv Msg EF not 6F3C");

        return;
    }

    pstCtrlInfoAddr     = TAF_XSMS_GetReqCtrlInfoAddr();
    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    if (TAF_XSMS_APP_MSG_TYPE_WRITE_REQ == pstCtrlInfoAddr->enAppMsgType)
    {
        /* 上报AT写入记录结果，并且索引表中对应的BIT设置为已使用 */
        if (VOS_OK == pstMsg->stCmdResult.ulResult)
        {
            ucIndex = pstMsg->ucRecordNum;

            TAF_XSMS_SetBitToBuf(pstInitCtrlInfoAddr->aucFreeIndex, ucIndex, TAF_XSMS_EFSMS_STATUS_USED);

            /* AT上报索引值，从1开始，AT的处理函数会减1 */
            TAF_XSMS_MsgWriteCnf(pstCtrlInfoAddr->usClient, pstCtrlInfoAddr->ucOpID, VOS_OK, ucIndex);
        }
        else
        {
            TAF_XSMS_WARNING_LOG("TAF_XSMS_AtSetFileRspMsgProc: Write SMS Fail");

            TAF_XSMS_MsgWriteCnf(pstCtrlInfoAddr->usClient, pstCtrlInfoAddr->ucOpID, VOS_ERR, 0);
        }
    }
    else if (TAF_XSMS_APP_MSG_TYPE_DELETE_REQ == pstCtrlInfoAddr->enAppMsgType)
    {
        /* 上报AT删除记录结果，并且索引表中对应的BIT清除 */
        if (VOS_OK == pstMsg->stCmdResult.ulResult)
        {
            ucIndex = pstMsg->ucRecordNum;
            TAF_XSMS_SetBitToBuf(pstInitCtrlInfoAddr->aucFreeIndex, ucIndex, TAF_XSMS_EFSMS_STATUS_FREE);
            TAF_XSMS_MsgDeleteCnf(pstCtrlInfoAddr->usClient, pstCtrlInfoAddr->ucOpID, VOS_OK);
        }
        else
        {
            TAF_XSMS_WARNING_LOG("TAF_XSMS_AtSetFileRspMsgProc: Delete SMS Fail");

            TAF_XSMS_MsgDeleteCnf(pstCtrlInfoAddr->usClient, pstCtrlInfoAddr->ucOpID, VOS_ERR);
        }
    }
    else
    {
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_MtSetFileRspMsgProc
 功能描述  : MT过程写文件请求回复处理函数
 输入参数  : pstMsg:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_MtSetFileRspMsgProc(USIMM_UPDATEFILE_CNF_STRU *pstMsg)
{
    VOS_UINT32                          ulEFDefID;

    (VOS_VOID)USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstMsg->stFilePath.ulPathLen, pstMsg->stFilePath.acPath, &ulEFDefID);

    /* MT过程中只有PRL文件更新 */
    if ((USIMM_CDMA_EFSMS_ID == ulEFDefID)||(USIMM_CSIM_EFSMS_ID == ulEFDefID))
    {
        TAF_XSMS_MtFsmMainProc((MsgBlock *)pstMsg);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_UsimmSetFileRspMsgProc
 功能描述  : USIMM写文件请求回复消息处理函数
 输入参数  : pstMsg:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_UsimmSetFileRspMsgProc(USIMM_UPDATEFILE_CNF_STRU *pstMsg)
{
    /* 只有AT命令和MO/MT过程中才有更新文件的操作 */
    switch (pstMsg->stCmdResult.ulSendPara)
    {
        case TAF_XSMS_UIM_REQ_TYPE_AT:
            TAF_XSMS_AtSetFileRspMsgProc(pstMsg);
            break;

        /* MO过程目前只写MessageID，不论是否成功都不用管 */
        case TAF_XSMS_UIM_REQ_TYPE_MO:
            /* do nothing, make pclint happy */
            break;

        case TAF_XSMS_UIM_REQ_TYPE_MT:
            TAF_XSMS_MtSetFileRspMsgProc(pstMsg);
            break;

        default:

            break;
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_UsimmMsgProc
 功能描述  : USIMM消息处理函数
 输入参数  : pstMsg:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_UsimmMsgProc(TAF_XSMS_UIM_MSG_STRU *pstMsg)
{
    switch (pstMsg->ulMsgName)
    {
        /* 读取文件请求CNF */
        case USIMM_READFILE_CNF:
            TAF_XSMS_UsimmGetFileRspMsgProc((USIMM_READFILE_CNF_STRU *)pstMsg);
            break;
        /* 更新文件请求CNF */
        case USIMM_UPDATEFILE_CNF:
            TAF_XSMS_UsimmSetFileRspMsgProc((USIMM_UPDATEFILE_CNF_STRU *)pstMsg);
            break;
        /* 获取文件最大记录数请求CNF */
        case USIMM_QUERYFILE_CNF:
            TAF_XSMS_InitUsimmMaxRecordRspMsgProc((USIMM_QUERYFILE_CNF_STRU *)pstMsg);
            break;

        default:
            break;
    }

    return;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

