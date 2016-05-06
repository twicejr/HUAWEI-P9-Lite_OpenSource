/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : UsimmApi.c
  Author       : zhuli
  Version      : V100R002
  Date         : 2008-5-15
  Description  : 该C文件给出了---完成初始化和消息处理模块实现
  Function List:
  History      :
 ************************************************************************/
#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

#include "si_pb.h"
#include "UsimmApi.h"
#include "TafOamInterface.h"


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_PB_BASE_C
/*lint +e767*/

VOS_UINT32  g_ulPbrRecordNum = 0;

/*****************************************************************************
函 数 名  :SI_PB_CheckSupportAP
功能描述  :判断当前是否支持AP
输入参数  :无
输出参数  :无
返 回 值  :VOS_TRUE/VOS_FALSE
调用函数  :
被调函数  : 外部接口
History     :
1.日    期  : 2013年11月19日
  作    者  : H59254
  修改内容  : Create
*****************************************************************************/
VOS_BOOL SI_PB_CheckSupportAP(VOS_VOID)
{
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU     stAPPConfig;

    if (NV_OK != NV_Read(en_NV_Item_System_APP_Config, &stAPPConfig, sizeof(VOS_UINT16)))
    {
        PB_NORMAL_LOG("SI_PB_CheckSupportAP: Read en_NV_Item_System_APP_Config Failed");

        return VOS_FALSE;
    }

    if (SYSTEM_APP_ANDROID == stAPPConfig.usSysAppConfigType)
    {
        PB_NORMAL_LOG("SI_PB_CheckSupportAP: System App is Android");

        return VOS_TRUE;
    }

    PB_NORMAL_LOG("SI_PB_CheckSupportAP: System App is other");

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  :SI_PB_HexToAsciiCode
功能描述  :转换字符串格式
输入参数  :

输出参数  :无
返 回 值  :VOS_OK    :失败
           VOS_ERR   :成功

修订记录  :
1. 日    期   : 2015年2月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 SI_PB_HexToAsciiCode(VOS_UINT8 ucSrc,VOS_CHAR *pcDst)
{
    if(ucSrc <= 0x09)
    {
        *pcDst = (VOS_CHAR)(ucSrc-0x00) + '0';
    }
    else if ((0xa <= ucSrc)&&(ucSrc <= 0xf))
    {
        *pcDst = (VOS_CHAR)(ucSrc-0x0a) + 'A';
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :SI_PB_AsciiToHexCode
功能描述  :转换字符串格式
输入参数  :

输出参数  :无
返 回 值  :VOS_OK    :失败
           VOS_ERR   :成功

修订记录  :
1. 日    期   : 2015年2月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 SI_PB_AsciiToHexCode(VOS_CHAR cSrc, VOS_UINT8 *pucDst)
{
    if (( cSrc >= '0') && (cSrc <= '9')) /* the number is 0-9 */
    {
        *pucDst = (VOS_UINT8)(cSrc - '0');
    }
    else if ( (cSrc >= 'a') && (cSrc <= 'f') ) /* the number is a-f */
    {
        *pucDst = (VOS_UINT8)(cSrc - 'a') + 0x0a;
    }
    else if ( (cSrc >= 'A') && (cSrc <= 'F') ) /* the number is A-F */
    {
        *pucDst = (VOS_UINT8)(cSrc - 'A') + 0x0a;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :SI_PB_GetEFIDFromPath
功能描述  :从文件路径中获取EF的ID
输入参数  :

输出参数  :无
返 回 值  :VOS_OK    :失败
           VOS_ERR   :成功

修订记录  :
1. 日    期   : 2015年2月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/

VOS_VOID SI_PB_GetEFIDFromPath(USIMM_FILEPATH_INFO_STRU *pstFilePath,VOS_UINT16 *pusEFID)
{
    VOS_UINT8   ucTemp;
    VOS_UINT32  i;

    *pusEFID = VOS_NULL;

    for(i=1; i<=4; i++)
    {
        if( VOS_ERR == SI_PB_AsciiToHexCode(pstFilePath->acPath[pstFilePath->ulPathLen-i], &ucTemp))
        {
            return;
        }

        /*lint -e701*/
        *pusEFID += (VOS_UINT16)((VOS_UINT16)ucTemp<<((i-1)*4));
        /*lint +e701*/
    }

    return ;
}

/*****************************************************************************
函 数 名  :SI_PB_ChageFileToPathStr
功能描述  :转换文件ID到文件路径
输入参数  :

输出参数  :无
返 回 值  :

修订记录  :
1. 日    期   : 2015年2月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/

VOS_VOID SI_PB_ChangeFileToPathStr(VOS_UINT16 usEFID, USIMM_FILEPATH_INFO_STRU *pstFilePath)
{
    VOS_UINT16                  usDFID;

    if ((usEFID&0xFF00) == 0x6F00)
    {
        if (USIMM_CARD_SIM == gstPBInitState.enCardType)
        {
            pstFilePath->ulPathLen    = VOS_StrLen(USIMM_TELE_STR);

            /*lint -e534*/
            VOS_MemCpy(pstFilePath->acPath, USIMM_TELE_STR, pstFilePath->ulPathLen);
            /*lint +e534*/
        }
        else
        {
            pstFilePath->ulPathLen    = VOS_StrLen(USIMM_USIM_STR);

            /*lint -e534*/
            VOS_MemCpy(pstFilePath->acPath, USIMM_USIM_STR, pstFilePath->ulPathLen);
            /*lint +e534*/
        }
    }
    else
    {
        usDFID = USIMM_GetPbDfPath();

        if (ADF == usDFID)
        {
            pstFilePath->ulPathLen    = VOS_StrLen(USIMM_USIM_DFPHONEBOOK_STR);

            /*lint -e534*/
            VOS_MemCpy(pstFilePath->acPath, USIMM_USIM_DFPHONEBOOK_STR, pstFilePath->ulPathLen);
            /*lint +e534*/
        }
        else
        {
            pstFilePath->ulPathLen    = VOS_StrLen(USIMM_TELE_DFPB_STR);

            /*lint -e534*/
            VOS_MemCpy(pstFilePath->acPath, USIMM_TELE_DFPB_STR, pstFilePath->ulPathLen);
            /*lint +e534*/
        }
    }

    /*lint -e534*/
    SI_PB_HexToAsciiCode((VOS_UINT8)((usEFID>>12)&0x0F) ,&pstFilePath->acPath[pstFilePath->ulPathLen]);
    SI_PB_HexToAsciiCode((VOS_UINT8)((usEFID>>8)&0x0F) ,&pstFilePath->acPath[pstFilePath->ulPathLen+1]);
    SI_PB_HexToAsciiCode((VOS_UINT8)((usEFID>>4)&0x0F) ,&pstFilePath->acPath[pstFilePath->ulPathLen+2]);
    SI_PB_HexToAsciiCode((VOS_UINT8)(usEFID&0x0F) ,&pstFilePath->acPath[pstFilePath->ulPathLen+3]);
    /*lint +e534*/

    pstFilePath->ulPathLen += 4;

    return;
}

/*****************************************************************************
函 数 名  :SI_PB_CheckFileID
功能描述  :读取文件操作　
输入参数  :
输出参数  :无
返 回 值  :
修订记录  :
1. 日    期   : 2015年2月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 SI_PB_CheckFileID(VOS_UINT16 usFileID)
{
    VOS_UINT8                           ucFileType;

    ucFileType = (VOS_UINT8)((usFileID>>0x08)&0xFF);

    if ((0x4F == ucFileType)||(0x6F == ucFileType))
    {
        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}

/*****************************************************************************
函 数 名  :SI_PB_GetFileReq
功能描述  :读取文件操作　
输入参数  :
输出参数  :无
返 回 值  :
修订记录  :
1. 日    期   : 2015年2月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_GetFileReq(SI_PB_GETFILE_INFO_STRU    *pstGetFileInfo)
{
    USIMM_READFILE_REQ_STRU     *pstMsg;

    if (VOS_ERR == SI_PB_CheckFileID(pstGetFileInfo->usEfId))
    {
        PB_ERROR_LOG("SI_PB_GetFileReq: The SI_PB_CheckFileID is Wrong");

        return VOS_ERR; /*返回函数错误信息*/
    }

    pstMsg = (USIMM_READFILE_REQ_STRU *)VOS_AllocMsg(MAPS_PB_PID,
                                                     sizeof(USIMM_READFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PB_ERROR_LOG("SI_PB_GetFileReq: The VOS_AllocMsg is Wrong");

        return VOS_ERR; /*返回函数错误信息*/
    }

    /*填充消息内容*/
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulSendPara      = 0;
    pstMsg->stMsgHeader.enMsgName       = USIMM_READFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->ucRecordNum                 = pstGetFileInfo->ucRecordNum;

    SI_PB_ChangeFileToPathStr(pstGetFileInfo->usEfId, &pstMsg->stFilePath);

    return VOS_SendMsg(MAPS_PB_PID , pstMsg);
}

/*****************************************************************************
函 数 名  :SI_PB_GetFileReq
功能描述  :更新文件操作　
输入参数  :
输出参数  :无
返 回 值  :
修订记录  :
1. 日    期   : 2015年2月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_SetFileReq(SI_PB_SETFILE_INFO_STRU    *pstSetFileInfo)
{
    USIMM_UPDATEFILE_REQ_STRU          *pstMsg;

    if (VOS_ERR == SI_PB_CheckFileID(pstSetFileInfo->usEfId))
    {
        PB_ERROR_LOG("SI_PB_SetFileReq: The SI_PB_CheckFileID is Wrong");

        return VOS_ERR; /*返回函数错误信息*/
    }

    if ((pstSetFileInfo->ucRecordNum == VOS_NULL)||(pstSetFileInfo->ulEfLen > 0xFF))
    {
        PB_ERROR_LOG("SI_PB_SetFileReq: The pstSetFileInfo is Wrong");

        return VOS_ERR; /*返回函数错误信息*/
    }

    pstMsg = (USIMM_UPDATEFILE_REQ_STRU *)VOS_AllocMsg(MAPS_PB_PID,
                                                sizeof(USIMM_UPDATEFILE_REQ_STRU)-VOS_MSG_HEAD_LENGTH+pstSetFileInfo->ulEfLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        PB_ERROR_LOG("SI_PB_SetFileReq: The VOS_AllocMsg is Wrong");

        return VOS_ERR; /*返回函数错误信息*/
    }

    /*填充消息内容*/
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulSendPara      = 0;
    pstMsg->stMsgHeader.enMsgName       = USIMM_UPDATEFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->ucRecordNum                 = pstSetFileInfo->ucRecordNum;
    pstMsg->usDataLen                   = (VOS_UINT16)pstSetFileInfo->ulEfLen;

    /*lint -e534*/
    VOS_MemCpy(pstMsg->aucContent, pstSetFileInfo->pucEfContent, pstSetFileInfo->ulEfLen);
    /*lint +e534*/

    SI_PB_ChangeFileToPathStr(pstSetFileInfo->usEfId, &pstMsg->stFilePath);

    return VOS_SendMsg(MAPS_PB_PID , pstMsg);
}

/*****************************************************************************
函 数 名  :SI_PB_QueryFileReq
功能描述  :获取文件信息　
输入参数  :usEfId:文件ID
输出参数  :无
返 回 值  :
修订记录  :
1. 日    期   : 2015年2月12日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_QueryFileReq(VOS_UINT16 usEFID)
{
    USIMM_QUERYFILE_REQ_STRU    *pstMsg;

    if (VOS_ERR == SI_PB_CheckFileID(usEFID))
    {
        PB_ERROR_LOG("SI_PB_QueryFileReq: The usEFID is Wrong");

        return VOS_ERR; /*返回函数错误信息*/
    }

    pstMsg = (USIMM_QUERYFILE_REQ_STRU *)VOS_AllocMsg(MAPS_PB_PID,
                                                    sizeof(USIMM_QUERYFILE_REQ_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        PB_ERROR_LOG("SI_PB_QueryFileReq: The VOS_AllocMsg is Wrong");

        return VOS_ERR; /*返回函数错误信息*/
    }

    /*填充消息内容*/
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_QUERYFILE_REQ;
    pstMsg->stMsgHeader.ulSendPara      = 0;

    SI_PB_ChangeFileToPathStr(usEFID, &pstMsg->stFilePath);

    return VOS_SendMsg(MAPS_PB_PID, pstMsg);
}

/*****************************************************************************
函 数 名  :SI_PB_SearchReq
功能描述  :查询文件请求
输入参数  :
输出参数  :无
返 回 值  :VOS_OK
           VOS_ERR
修订记录  :
1. 日    期   : 2015年2月12日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_SearchFileReq(USIMM_U8_LVDATA_STRU    *pstData,
                                VOS_UINT16               usFileId)
{
    USIMM_SEARCHFILE_REQ_STRU          *pstMsg;

    if (VOS_ERR == SI_PB_CheckFileID(usFileId))
    {
        PB_ERROR_LOG("SI_PB_SearchFileReq: The usFileId is Wrong");

        return VOS_ERR; /*返回函数错误信息*/
    }

    pstMsg = (USIMM_SEARCHFILE_REQ_STRU *)VOS_AllocMsg(MAPS_PB_PID,
                                                (sizeof(USIMM_SEARCHFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH) + pstData->ulDataLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        PB_ERROR_LOG("SI_PB_SearchReq: The VOS_AllocMsg is Wrong");

        return VOS_ERR; /* 返回函数错误信息 */
    }

    /* 填充消息内容 */
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_SEARCHFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->ulDataLen                   = pstData->ulDataLen;

    /*lint -e534*/
    VOS_MemCpy(pstMsg->aucData, pstData->pucData, pstData->ulDataLen);
    /*lint +e534*/

    SI_PB_ChangeFileToPathStr(usFileId, &pstMsg->stFilePath);

    return VOS_SendMsg(MAPS_PB_PID, pstMsg);
}

/*****************************************************************************
函 数 名  : SI_PB_SetSPBFileReq
功能描述  : 复合电话本更新请求
输入参数  : pstSPBReq  文件搜索参数
输出参数  : 无
返 回 值  : VOS_UINT32 函数执行结果
调用函数  : 无
被调函数  : 外部接口
History     :
1. 日    期  : 2015年2月12日
   作    者  : z00100318
   修改内容  : Create

2. 日    期   : 2015年3月31日
   作    者   : d00212987
   修改内容   : 卡多应用迭代II开发
*****************************************************************************/
VOS_UINT32 SI_PB_SetSPBFileReq(SI_PB_SPBDATA_STRU *pstSPBReq)
{
    VOS_UINT32                      i;
    USIMM_SETMUTILFILE_REQ_STRU     *pstMsg;

    if(VOS_NULL_PTR == pstSPBReq)
    {
        PB_ERROR_LOG("SI_PB_SetSPBFileReq: The Parameter is Wrong");

        return VOS_ERR;
    }

    if(0 == pstSPBReq->usFileNum)/*没有需要更新的电话本文件*/
    {
        PB_ERROR_LOG("SI_PB_SetSPBFileReq: No file to update");

        return VOS_ERR;
    }

    pstMsg = (USIMM_SETMUTILFILE_REQ_STRU *)VOS_AllocMsg(MAPS_PB_PID,
                                            sizeof(USIMM_SETMUTILFILE_REQ_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        PB_ERROR_LOG("SI_PB_SetSPBFileReq: VOS_AllocMsg is Failed");

        return VOS_ERR;
    }

    for(i=0; i<pstSPBReq->usFileNum; i++)
    {
#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
        SI_PB_ChangeFileToPathStr(pstSPBReq->usFileID[i], &(pstMsg->stFileData[i].stFilePath));
#else
        pstMsg->stFileData[i].usFileID    = pstSPBReq->usFileID[i];
#endif

        pstMsg->stFileData[i].ucRecordNum = pstSPBReq->ucRecordNum[i];
        pstMsg->stFileData[i].usDataLen   = pstSPBReq->usDataLen[i];

        if(VOS_NULL_PTR == pstSPBReq->pContent[i])
        {
            PB_WARNING_LOG("SI_PB_SetSPBFileReq: Req Content Empty");

            /*lint -e534*/
            VOS_FreeMsg(MAPS_PB_PID, pstMsg);
            /*lint +e534*/

            return VOS_ERR;
        }

        /*lint -e534*/
        VOS_MemCpy(pstMsg->stFileData[i].aucContent, pstSPBReq->pContent[i], pstSPBReq->usDataLen[i]);
        /*lint +e534*/
    }

    pstMsg->stMsgHeader.ulReceiverPid       = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName           = USIMM_SETMUTILFILE_REQ;
    pstMsg->stMsgHeader.enAppType           = USIMM_GUTL_APP;
    pstMsg->ulFileCount                     = pstSPBReq->usFileNum;

    return VOS_SendMsg(MAPS_PB_PID, pstMsg);
}


/*****************************************************************************
函 数 名  : SI_PB_ClearPBContent
功能描述  : 释放缓冲电话本的内容
输入参数  : ulClearType:决定是清除所有电话本还是除ECC之外的电话本
输出参数  : 无
返 回 值  : 无
调用函数  : VOS_MemFree
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_ClearPBContent(VOS_UINT32 ulClearType)
{
    VOS_UINT32 i;

    /*有可能ADN和MSISDN指向同一块内存，避免重复释放*/
    if(gastEXTContent[PB_ADN_CONTENT].pExtContent ==
                gastEXTContent[PB_MSISDN_CONTENT].pExtContent)
    {
        gastEXTContent[PB_MSISDN_CONTENT].pExtContent = VOS_NULL_PTR;
    }

    for (i=0; i<SI_PB_MAX_NUMBER; i++)
    {

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if((SI_CLEARXDN == ulClearType)
        && ((PB_ECC == gastPBContent[i].enPBType)
         || (PB_XECC == gastPBContent[i].enPBType))) /*只清除部分电话本不含ECC*/
        {
           continue;
        }
#else
        if((SI_CLEARXDN == ulClearType)
        && (PB_ECC == gastPBContent[i].enPBType)) /*只清除部分电话本不含ECC*/
        {
           continue;
        }
#endif

        if(VOS_NULL_PTR != gastPBContent[i].pContent)
        {
            /*lint -e534*/
            PB_FREE(gastPBContent[i].pContent);
            /*lint +e534*/

            gastPBContent[i].pContent = VOS_NULL_PTR;
        }

        if (VOS_NULL_PTR != gastPBContent[i].pIndex)
        {
            /*lint -e534*/
            PB_FREE(gastPBContent[i].pIndex);
            /*lint +e534*/

            gastPBContent[i].pIndex = VOS_NULL_PTR;
        }

        if(VOS_NULL_PTR != gastEXTContent[i].pExtContent)
        {
            /*lint -e534*/
            PB_FREE(gastEXTContent[i].pExtContent);
            /*lint +e534*/

            gastEXTContent[i].pExtContent = VOS_NULL_PTR;
        }

        gastPBContent[i].enInitialState = PB_NOT_INITIALISED;
    }

    PB_WARNING_LOG("SI_PB_ClearPBContent: Clear The PB Content");

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_ClearSPBContent
功能描述  : 释放缓冲复合电话本的内容
输入参数  : ulClearType:决定是清除所有电话本还是除ECC之外的电话本
输出参数  : 无
返 回 值  : 无
调用函数  : VOS_MemFree
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_ClearSPBContent(VOS_UINT32 ulClearType)
{
    VOS_UINT32 i;

    for (i=0; i<SI_PB_ANRMAX; i++)
    {
        if(VOS_NULL_PTR != gastANRContent[i].pContent)
        {
            /*lint -e534*/
            PB_FREE(gastANRContent[i].pContent);
            /*lint +e534*/

            gastANRContent[i].pContent = VOS_NULL_PTR;
        }
    }

    if(VOS_NULL_PTR != gstEMLContent.pContent)
    {
        /*lint -e534*/
        PB_FREE(gstEMLContent.pContent);
        /*lint +e534*/

        gstEMLContent.pContent = VOS_NULL_PTR;
    }

    if(VOS_NULL_PTR != gstIAPContent.pIAPContent)
    {
        /*lint -e534*/
        PB_FREE(gstIAPContent.pIAPContent);
        /*lint +e534*/

        gstIAPContent.pIAPContent = VOS_NULL_PTR;
    }

    PB_WARNING_LOG("SI_PB_ClearSPBContent: Clear The SPB Content");

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_ExtExceptionProc
功能描述  : EXT文件出现异常状态的处理函数
输入参数  : ulClearType:要处理的EXT文件类型
输出参数  : 无
返 回 值  : 无
调用函数  : VOS_MemFree
被调函数  :
修订记录  :
1.  日    期   : 2009年5月16日
    作    者   : h59254
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_ExtExceptionProc(VOS_UINT16 usExtFileId)
{
    VOS_UINT8   i;
    VOS_UINT32  ulType;

    PB_WARNING_LOG("SI_PB_ExtExceptionProc: Into the PB Ext File Exc Handle");

    for( i = 0 ; i < PB_MSISDN_CONTENT; i++)
    {
        if(usExtFileId == gastEXTContent[i+1].usExtFileId)
        {
            break;
        }
    }

    if(i >= PB_MSISDN_CONTENT)
    {
        return;
    }

    ulType = i + 1;

    if(VOS_NULL_PTR != gastEXTContent[ulType].pExtContent)
    {
        /*lint -e534*/
        PB_FREE(gastEXTContent[ulType].pExtContent);
        /*lint +e534*/
        gastEXTContent[ulType].pExtContent = VOS_NULL_PTR;
    }

    gastEXTContent[ulType].usExtFlag        = SI_PB_FILE_NOT_EXIST;
    gastEXTContent[ulType].usExtFileId      = 0xFFFF;
    gastEXTContent[ulType].usExtTotalNum    = 0;
    gastEXTContent[ulType].usExtUsedNum     = 0;

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_CheckXDNFileID
功能描述  : 检查是否是XDN电话本文件
输入参数  : usFileID:文件ID
输出参数  : 无
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : 无
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_CheckXDNFileID(VOS_UINT16 usFileID)
{
    switch(usFileID)
    {
        case EFFDN:
        case EFBDN:
        case EFMSISDN:
        case EFPSC:
        case EFCC:
        case EFPUID:
            return VOS_OK;
        default:
            return VOS_ERR;
    }
}

/*****************************************************************************
函 数 名  : SI_PB_CheckSYNCHFileID
功能描述  : 检查是否是3G重同步文件
输入参数  : usFileID:文件ID
输出参数  : 无
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : 无
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_CheckSYNCHFileID(VOS_UINT16 usFileID)
{
    switch(usFileID)
    {
        case EFPSC:
        case EFCC:
        case EFPUID:
            return VOS_OK;
        default:
            if ( usFileID == gstPBCtrlInfo.astUIDInfo[0].usFileID )
            {
                return VOS_OK;
            }
            else if ( usFileID == gstPBCtrlInfo.astPBCInfo[0].usFileID )
            {
                return VOS_OK;
            }
            else
            {
                return VOS_ERR;
            }
    }
}

/*****************************************************************************
函 数 名  : SI_PB_CheckExtFileID
功能描述  : 检查是否是EXT文件
输入参数  : usFileID:文件ID
输出参数  : 无
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : 无
被调函数  :
修订记录  :
1.  日    期   : 2009年5月7日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_CheckExtFileID(VOS_UINT16 usFileID)
{
    switch(usFileID)
    {
        case EFEXT1:
        case EFEXT2:
        case EFEXT3:
        /*case EFEXT5: */
        case EFEXT6:
        case EFEXT7:
        case EFEXT4_USIM:
        case EFEXT4_SIM:
            return VOS_OK;
        default:
            break;
    }

    /* 与USIM卡ADN文件的EXT1文件ID相同 */
    if(usFileID == gastEXTContent[PB_ADN_CONTENT].usExtFileId)
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
函 数 名  : SI_PB_JumpToNextPB
功能描述  : 进入下一个电话本
输入参数  : ulPBType:当前正在初始化的电话本
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_JumpToNextPB(VOS_UINT32 ulPBType)
{
    if ( PB_ADN_CONTENT == ulPBType )
    {
        gulPBFileCnt = gstPBCtrlInfo.ulADNFileNum;/*跳过ADN电话本*/
    }
    else
    {
        gulPBFileCnt++;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitSYNCHGetProc
功能描述  : 处理3G重同步文件内容
输入参数  : pstMsg
输出参数  : gstPBCtrlInfo
            gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_InitSYNCHGetProc(PBMsgBlock *pstMsg)
{
    USIMM_READFILE_CNF_STRU    *pstPBMsg;
    VOS_UINT16                  usEFID;

    pstPBMsg = (USIMM_READFILE_CNF_STRU *)pstMsg;

    SI_PB_GetEFIDFromPath(&pstPBMsg->stFilePath, &usEFID);

    if ( VOS_OK != pstPBMsg->stCmdResult.ulResult )/*如果USIMM模块回复错误，则重同步失败*/
    {
        PB_ERROR_LOG("SI_PB_InitSYNCHProc:USIMM Confirm ERROR");

        gstPBInitState.enPBInitState = SI_PB_INIT_USIMPBCNF_ERR;

        if( (EFPUID == usEFID)
            || (gstPBCtrlInfo.astPBCInfo[0].usFileID == usEFID) )
        {
            gulPBRecordCnt = 1;/*下面开始初始化EFPBC和EFUID,逐条读取记录，从第一条开始*/
        }

        return;
    }

    gstPBInitState.enPBInitState = SI_PB_INIT_STATUS_OK;


    if( EFCC == usEFID )/*处理EFCC文件的读请求回复*/
    {
        gstPBCtrlInfo.usCCValue += pstPBMsg->aucEf[0]<<8;

        gstPBCtrlInfo.usCCValue += pstPBMsg->aucEf[1];

        return;
    }

    if( EFPSC == usEFID )/*处理EFPSC文件的读请求回复*/
    {
        /*lint -e701 */
        gstPBCtrlInfo.ulPSCValue += pstPBMsg->aucEf[0]<<24;

        gstPBCtrlInfo.ulPSCValue += pstPBMsg->aucEf[1]<<16;

        gstPBCtrlInfo.ulPSCValue += pstPBMsg->aucEf[2]<<8;
        /*lint +e701 */

        gstPBCtrlInfo.ulPSCValue += pstPBMsg->aucEf[3];

        return;
    }


    if( EFPUID == usEFID )/*处理EFPUIS文件的读请求回复*/
    {
        gstPBCtrlInfo.usPUIDValue += pstPBMsg->aucEf[0]<<8;

        gstPBCtrlInfo.usPUIDValue += pstPBMsg->aucEf[1];

        gulPBRecordCnt = 1;/*下面开始初始化EFPBC和EFUID,逐条读取记录，从第一条开始*/

        return;
    }

    if( gstPBCtrlInfo.astPBCInfo[0].usFileID == usEFID )/*处理EFPBC文件的读请求回复*/
    {
        SI_PB_DecodeEFPBCRecord(pstPBMsg->aucEf, pstPBMsg->ucRecordNum);

        if ( ++gulPBRecordCnt > gstPBCtrlInfo.astADNInfo[0].ucRecordNum)/*PBC的记录数和ADN的一样多*/
        {
            gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_EXCEED;/*所有记录都读取完成*/
        }
        else
        {
            gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_REMAIN;
        }

        return;
    }

    if( gstPBCtrlInfo.astUIDInfo[0].usFileID == usEFID )/*处理EFUID文件的读请求回复*/
    {
        SI_PB_DecodeEFUIDRecord(pstPBMsg->aucEf);

        if ( ++gulPBRecordCnt > gstPBCtrlInfo.astADNInfo[0].ucRecordNum)/*PBC的记录数和ADN的一样多*/
        {
            gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_EXCEED;/*所有记录都读取完成*/
        }
        else
        {
            gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_REMAIN;
        }
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitSYNCHSetProc
功能描述  : 处理3G重同步文件内容
输入参数  : pstMsg
输出参数  : gstPBCtrlInfo
            gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_InitSYNCHSetProc(PBMsgBlock *pstMsg)
{
    USIMM_UPDATEFILE_CNF_STRU       *pstPBMsg;
    VOS_UINT16                      usEFId;

    pstPBMsg = (USIMM_UPDATEFILE_CNF_STRU *)pstMsg;

    SI_PB_GetEFIDFromPath(&pstPBMsg->stFilePath, &usEFId);

    /*AT2D15855*/
    /*如果是PSC文件更新回复，则表明对有变化条目的记录已经完成，
    把相关全局变量置零，准备进入初始化下一步*/
    if ( EFCC == usEFId)
    {
        gstPBInitState.stPBCUpdate.ucEntryChangeNum = 0;

        PB_INFO_LOG("SI_PB_InitSYNCHSetProc:PB Init Finished!");
    }

    if ( VOS_OK != pstPBMsg->stCmdResult.ulResult )
    {
        PB_ERROR_LOG("SI_PB_InitSYNCHProc:USIMM Confirm ERROR");

        return;
    }

    /*处理USIMM更新PBC的请求回复*/
    if( gstPBCtrlInfo.astPBCInfo[0].usFileID == usEFId)
    {
        ++gulPBRecordCnt;

        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_REMAIN;

        return;
    }

    return;
}
/*****************************************************************************
函 数 名  : SI_PB_InitPBStateProc
功能描述  : 根据对USIMM模块回复的处理情况，确定下一个初始化步骤
输入参数  : enPBInitState:初始化状态
输出参数  : gulPBFileCnt
            gulPBRecordCnt
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2008年10月31日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_InitPBStateProc(SI_PB_INIT_STATUS_ENUM_UNIT32 enPBInitState)
{
    VOS_UINT32  ulPBType = 0xFF;

    switch( enPBInitState )
    {
        /* 查找命令USIMM模块回返错误 */
        case SI_PB_INIT_SEARCH_ERR:
            if (PB_INIT_IAP_SEARCH == gstPBInitState.enPBInitStep)
            {
                gstPBInitState.enPBInitStep = PB_INIT_IAP_CONTENT;
            }
            else if (PB_INIT_EML_SEARCH == gstPBInitState.enPBInitStep)
            {
                gstPBInitState.enPBInitStep = PB_INIT_EML_CONTENT;
            }
            else if (PB_INIT_ANR_SEARCH == gstPBInitState.enPBInitStep)
            {
                gstPBInitState.enPBInitStep = PB_INIT_ANR_CONTENT;
            }
            else if (PB_INIT_XDN_SEARCH == gstPBInitState.enPBInitStep)
            {
                gstPBInitState.enPBInitStep = PB_INIT_XDN_CONTENT;
            }
            else if (PB_INIT_PBC_SEARCH == gstPBInitState.enPBInitStep)
            {
                gstPBInitState.enPBInitStep = PB_INIT_PBC_CONTENT;
            }
            else
            {
                /*do nothing
 */
            }

            gulPBRecordCnt  = 1;    /* 从第一条记录开始初始化电话本内容 */

            break;

        case SI_PB_INIT_STATUS_OK:/*当前文件正确处理，准备进入下一个文件处理请求*/
        case SI_PB_INIT_EXT_ERR:/*初始化EXT文件空间时出错，跳入下一个EXT文件*/
            gulPBFileCnt++;

            break;

        case SI_PB_INIT_RECORD_REMAIN:/*当前文件仍有未读记录，继续处理剩余记录*/
        case SI_PB_INIT_EXT_RECORD:     /* 需要去初始化EXT文件的内容 */
        case SI_PB_INIT_SEARCH_OK:      /* SEARCH处理成功 */
            break;

        case SI_PB_INIT_PBTYPE_UNKOWN:/*当前初始化的电话本类型非法，跳入下一个文件*/
            gulPBFileCnt++;
            gulPBRecordCnt = 1;
            break;

        case SI_PB_INIT_RECORD_EXCEED:/*当前文件所有记录处理完毕，进入下一个文件处理*/

            /* 对于以读取方式初始化的文件完成初始化之后，下
            一个文件还是要以SEARCH方式来初始化 */
            if (PB_INIT_IAP_CONTENT2 == gstPBInitState.enPBInitStep)
            {
                gstPBInitState.enPBInitStep = PB_INIT_IAP_SEARCH;
            }
            else if (PB_INIT_EML_CONTENT2 == gstPBInitState.enPBInitStep)
            {
                gstPBInitState.enPBInitStep = PB_INIT_EML_SEARCH;
            }
            else if (PB_INIT_ANR_CONTENT2 == gstPBInitState.enPBInitStep)
            {
                gstPBInitState.enPBInitStep = PB_INIT_ANR_SEARCH;
            }
            else if (PB_INIT_XDN_CONTENT2 == gstPBInitState.enPBInitStep)
            {
                gstPBInitState.enPBInitStep = PB_INIT_XDN_SEARCH;
            }
            else
            {

            }

            gulPBFileCnt++;
            gulPBRecordCnt = 1;

            break;

        case SI_PB_INIT_USIMPBCNF_ERR:/*USIMM回复错误*/
        case SI_PB_INIT_FILE_DECATIVE:/*正在初始化的文件未激活*/
        case SI_PB_INIT_PBMALLOC_FAIL:/*分配内存失败*/

            /*获得当前初始化文件对应的电话本*/
            /*lint -e534*/
            SI_PB_GetXDNPBType(&ulPBType, gstPBInitState.ausFileId[gulPBFileCnt]);
            /*lint +e534*/

            if(0xFF == ulPBType)
            {
                /*No PB Found*/
            }
            else
            {
                if (VOS_NULL_PTR != gastPBContent[ulPBType].pContent)
                {
                    /*lint -e534*/
                    PB_FREE( gastPBContent[ulPBType].pContent);
                    /*lint +e534*/

                    gastPBContent[ulPBType].pContent = VOS_NULL_PTR;
                }

                if (VOS_NULL_PTR != gastPBContent[ulPBType].pIndex)
                {
                    /*lint -e534*/
                    PB_FREE( gastPBContent[ulPBType].pIndex);
                    /*lint +e534*/

                    gastPBContent[ulPBType].pIndex = VOS_NULL_PTR;
                }
            }

            /*跳至下一个电话本*/
            SI_PB_JumpToNextPB(ulPBType);

            break;

        case SI_PB_INIT_USIMSPBCNF_ERR:/*复合电话本初始化USIMM回复错误*/
        case SI_PB_INIT_SPBMALLOC_FAIL:/*复合电话本分配内存失败*/

            /*如果是扩展号码处理，则继续跳至下一个文件处理*/
            if((PB_INIT_ANR_CONTENT == gstPBInitState.enPBInitStep)
               ||(PB_INIT_EML_CONTENT == gstPBInitState.enPBInitStep))
            {
                gulPBFileCnt++;

                gulPBRecordCnt = 1;

                break;
            }

            gulPBFileCnt = 0;

            gstPBInitState.enPBInitStep++;/*跳至下一步*/

            if(PB_INIT_SYNCH == gstPBInitState.enPBInitStep)
            {
                /*填写3G重同步需要的文件信息*/
                gstPBInitState.ausFileId[0] = EFPSC;
                gstPBInitState.ausFileId[1] = EFCC;
                gstPBInitState.ausFileId[2] = EFPUID;
                /*gstPBInitState.ausFileId[3] = gstPBCtrlInfo.astPBCInfo[0].usFileID;
 */
                gstPBInitState.ausFileId[3] = gstPBCtrlInfo.astUIDInfo[0].usFileID;

                PB_WARNING_LOG("SI_PB_InitPBStateProc: Go to PB_INIT_XDN_CONTENT Step");

                gulPBRecordCnt = 0;
            }
            else
            {
                gulPBRecordCnt = 1;
            }

            break;

        case SI_PB_INIT_MSGTYPE_ERR:

            gstPBInitState.enReqStatus = PB_REQ_SEND;

            break;

        default:

            break;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitPBStatusJudge
功能描述  : 根据当前的卡类型和服务状态，确定下一个初始化步骤
输入参数  : 无
输出参数  : gstPBInitState
            gulPBInitFileNum
返 回 值  : VOS_Ok
            VOS_ERR
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2008年10月31日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_InitPBStatusJudge(VOS_VOID)
{

    /*如果为SIM卡，填写需要初始化的文件和初始化信息*/
    if ( USIMM_CARD_SIM == gstPBInitState.enCardType )
    {
        PB_INFO_LOG("SI_PB_InitPBStatusJudge:Go to PB_INIT_XDN_SPACE Step");

        /* 如果与AP对接时不需要初始化ADN文件 */
        if (VOS_TRUE == SI_PB_CheckSupportAP())
        {
            gstPBCtrlInfo.ulADNFileNum           = 0;

            gstPBInitState.ausFileId[0]          = EFFDN;
            gstPBInitState.ausFileId[1]          = EFBDN;
            gstPBInitState.ausFileId[2]          = EFMSISDN;
            gstPBInitState.ausFileId[3]          = EFSDN;

            gulPBInitFileNum                     = 4;
        }
        else
        {
            gstPBCtrlInfo.ulADNFileNum           = 1;

            gstPBCtrlInfo.astADNInfo[0].usFileID = SIM_EFADN;

            gstPBInitState.ausFileId[0]          = SIM_EFADN;
            gstPBInitState.ausFileId[1]          = EFFDN;
            gstPBInitState.ausFileId[2]          = EFBDN;
            gstPBInitState.ausFileId[3]          = EFMSISDN;
            gstPBInitState.ausFileId[4]          = EFSDN;

            gulPBInitFileNum                     = 5;
        }

        gastEXTContent[PB_ADN_CONTENT].usExtFileId      = EFEXT1;
        gastEXTContent[PB_FDN_CONTENT].usExtFileId      = EFEXT2;
        gastEXTContent[PB_BDN_CONTENT].usExtFileId      = EFEXT4_SIM;
        gastEXTContent[PB_MSISDN_CONTENT].usExtFileId   = EFEXT1;
        gastEXTContent[PB_SDN_CONTENT].usExtFileId      = EFEXT3;

        /*需要初始化的XDN文件个数为5，EXT文件的个数和4，
        原因是SIM卡中ADN与MSISDN共用一个EXT文件*/
        gastPBContent[PB_ADN_CONTENT].ulExtInfoNum      = PB_ADN_CONTENT;
        gastPBContent[PB_FDN_CONTENT].ulExtInfoNum      = PB_FDN_CONTENT;
        gastPBContent[PB_BDN_CONTENT].ulExtInfoNum      = PB_BDN_CONTENT;
        gastPBContent[PB_MSISDN_CONTENT].ulExtInfoNum   = PB_ADN_CONTENT;
        gastPBContent[PB_SDN_CONTENT].ulExtInfoNum      = PB_SDN_CONTENT;

        /* 对于SIM卡不采用SEARCH方式处理，设置要查找偏移量为0并且不支持SEARCH方式 */
        gstPBSearchCtrlInfo.usReadOffset                = 0;
        gstPBInitState.enPBSearchState                  = PB_SEARCH_DISABLE;

        gulPBInitExtFileNum                             = 3;

        /*设置下一个初始化步骤为初始化XDN电话本空间信息*/
        gstPBInitState.enPBInitStep          = PB_INIT_XDN_SPACE;
    }
    /*USIM卡则进入初始化EFPBR*/
    else
    {
        PB_INFO_LOG("SI_PB_InitPBStatusJudge:Go to PB_INIT_EFPBR Step");

        gstPBInitState.enPBInitStep = PB_INIT_EFPBR;
    }

    gulPBFileCnt = 0;/*已初始化文件数置零*/

    return VOS_OK;
}
/*****************************************************************************
函 数 名  : SI_PB_InitEFpbrReq
功能描述  : 向USIMM模块发送获取EFPBR内容的请求，并确定下一步初始化步骤
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK:成功
            VOS_ERR:失败
调用函数  : USIMM_GetFileReq
被调函数  :
修订记录  :
1.  日    期   : 2008年10月31日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_InitEFpbrReq(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT32                  ulFileCnt;
    SI_PB_GETFILE_INFO_STRU     stGetFileInfo;
    VOS_UINT32                  ulUsimSvr;

    /*gulPBFileCnt不为0,则已初始化过EFPBR，则进入初始化XDN电话本空间的步骤*/
    if (0 < gulPBFileCnt)
    {
        /* 如果与AP对接时不需要初始化ADN文件 */
        if (VOS_TRUE == SI_PB_CheckSupportAP())
        {
            gstPBCtrlInfo.ulADNFileNum = 0;
        }

        /*记录初始化过程中需要初始化的电话本文件*/
        for(ulFileCnt=0; ulFileCnt<gstPBCtrlInfo.ulADNFileNum; ulFileCnt++)
        {
            gstPBInitState.ausFileId[ulFileCnt] = gstPBCtrlInfo.astADNInfo[ulFileCnt].usFileID;
        }

        gstPBInitState.ausFileId[ulFileCnt++]   = EFFDN;
        gstPBInitState.ausFileId[ulFileCnt++]   = EFBDN;

        gstPBInitState.ausFileId[ulFileCnt]   = EFSDN;
        ulFileCnt++;

        ulUsimSvr = USIMM_IsServiceAvailable(USIM_SVR_MSISDN);

        if (PS_USIM_SERVICE_AVAILIABLE == ulUsimSvr)
        {
            gstPBInitState.ausFileId[ulFileCnt++]   = EFMSISDN;
        }

        /* 记录XDN文件对应的EXT控制信息的偏移量 */
        gastPBContent[PB_ADN_CONTENT].ulExtInfoNum      = PB_ADN_CONTENT;
        gastPBContent[PB_FDN_CONTENT].ulExtInfoNum      = PB_FDN_CONTENT;
        gastPBContent[PB_BDN_CONTENT].ulExtInfoNum      = PB_BDN_CONTENT;
        gastPBContent[PB_MSISDN_CONTENT].ulExtInfoNum   = PB_MSISDN_CONTENT;
        gastPBContent[PB_SDN_CONTENT].ulExtInfoNum      = PB_SDN_CONTENT;

        gastEXTContent[PB_ADN_CONTENT].usExtFileId      = gstPBCtrlInfo.usEXT1FileID;
        gastEXTContent[PB_FDN_CONTENT].usExtFileId      = EFEXT2;
        gastEXTContent[PB_BDN_CONTENT].usExtFileId      = EFEXT4_USIM;
        gastEXTContent[PB_SDN_CONTENT].usExtFileId      = EFEXT3;

        if (PS_USIM_SERVICE_AVAILIABLE != USIMM_IsServiceAvailable(USIM_SVR_EXT5))
        {
            gastEXTContent[PB_MSISDN_CONTENT].usExtFlag = SI_PB_FILE_NOT_EXIST;
            gastEXTContent[PB_MSISDN_CONTENT].usExtFileId = 0xFFFF;

            gulPBInitExtFileNum = 4;
        }
        else
        {
            gastEXTContent[PB_MSISDN_CONTENT].usExtFileId = EFEXT5;

            gulPBInitExtFileNum = 5;
        }

        gstPBInitState.enPBInitStep = PB_INIT_XDN_SPACE;

        /*如果不支持复合电话本，则所有信息清0*/
        if(0 == gstPBConfigInfo.ucSPBFlag)
        {
            gstPBCtrlInfo.ulANRFileNum = 0;
            gstPBCtrlInfo.ulEMLFileNum = 0;
            gstPBCtrlInfo.ulIAPFileNum = 0;
        }

        /*不存在Type2类型电话本,同一卡只支持一种类型电话本，所以Anr及Email下标均取0*/
        if((PB_FILE_TYPE2 != gstPBCtrlInfo.astANRInfo[0][0].enANRType)
            &&(PB_FILE_TYPE2 != gstPBCtrlInfo.astEMLInfo[0].enEMLType))
        {
            gstPBCtrlInfo.ulIAPFileNum = 0;
        }

        /*总共需初始化的文件数*/
        gulPBInitFileNum    = ulFileCnt;

        gulPBFileCnt = 0;

        PB_INFO_LOG("SI_PB_InitEFpbrReq: Go to PB_INIT_ADN_SPACE Step");

        return VOS_OK;
    }

    stGetFileInfo.ucRecordNum   = 0;
    stGetFileInfo.usEfId        = EFPBR;

    ulResult = SI_PB_GetFileReq(&stGetFileInfo);    /*向USIMM模块发送获取EFPBR文件内容的请求*/

    /*发送请求失败，则退出初始化*/
    if ( VOS_OK != ulResult )
    {
        PB_ERROR_LOG("SI_PB_InitEFpbrReq:Get EFPBR Content Failed");

        gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

        return VOS_ERR;
    }

    /*设置初始化请求状态为请求已发送*/
    gstPBInitState.enReqStatus = PB_REQ_SEND;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitXDNSpaceReq
功能描述  : 向USIMM模块发送初始化XDN电话本的请求，并设定下一步初始化步骤
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : SI_PB_QueryFileReq
被调函数  :
修订记录  :
1.  日    期   : 2008年10月31日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_InitXDNSpaceReq(VOS_VOID)
{
    VOS_UINT32 ulResult = VOS_OK;

    if(gulPBFileCnt < gulPBInitFileNum)/*如果还有空间未初始化的电话本，向USIMM发送获取该电话本记录数的请求*/
    {
        ulResult = SI_PB_QueryFileReq(gstPBInitState.ausFileId[gulPBFileCnt]);

        /*发送请求失败，则退出初始化步骤*/
        if ( VOS_OK != ulResult )
        {
            PB_ERROR_LOG("SI_PB_InitXDNSpaceReq: SI_PB_QueryFileReq Failed");

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            /*从1开始，ECC号码空间不释放*/
            SI_PB_ClearPBContent(SI_CLEARXDN);

            SI_PB_InitStatusInd(USIMM_PB_IDLE);

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    /*所有电话本空间初始化完毕，进入初始化电话本内容的步骤*/
    gulPBFileCnt = 0;/*文件计数清零*/

    gulPBRecordCnt = 1;/*从第一条记录开始初始化电话本内容*/

    gstPBInitState.enPBInitStep = PB_INIT_ANR_SPACE;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitANRSpaceReq
功能描述  : 向USIMM模块发送初始化ANR空间的请求，并设定下一步初始化步骤
输入参数  : 无
输出参数  :
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : SI_PB_QueryFileReq
被调函数  :
修订记录  :
1.  日    期   : 2009年5月8日
    作    者   : m00128685
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitANRSpaceReq(VOS_VOID)
{
    VOS_UINT16  usANRFileId;

    /*如果还有ANR空间未初始化的电话本，向USIMM发送获取该EXT文件记录数的请求*/
    if(gulPBFileCnt < gstPBCtrlInfo.ulANRFileNum)
    {
        if (VOS_OK != SI_PB_GetANRFid((gulPBFileCnt+1),&usANRFileId))
        {
            PB_ERROR_LOG("SI_PB_InitANRSpaceReq:SI_PB_GetANRFid Failed");

            /* 对应关系混乱，则没有继续初始化的必要 */
            SI_PB_ClearSPBContent(SI_CLEARSPB);

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            return VOS_ERR;
        }

        if(VOS_OK != SI_PB_QueryFileReq(usANRFileId) )
        {
            PB_ERROR_LOG("SI_PB_InitANRSpaceReq: SI_PB_QueryFileReq Failed");

            /* 发送请求失败，则没有继续初始化的必要 */
            SI_PB_ClearSPBContent(SI_CLEARSPB);

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    PB_INFO_LOG("SI_PB_InitIAPSpaceReq: Go to PB_INIT_EML_SPACE Step");

    gulPBFileCnt = 0;/*文件计数清零*/

    /*所有ANR空间初始化完毕，进入Email初始化的步骤*/
    gstPBInitState.enPBInitStep = PB_INIT_EML_SPACE;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitEMLSpaceReq
功能描述  : 向USIMM模块发送初始化ANR空间的请求，并设定下一步初始化步骤
输入参数  : 无
输出参数  :
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : SI_PB_QueryFileReq
被调函数  :
修订记录  :
1.  日    期   : 2009年6月15日
    作    者   : m00128685
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitEMLSpaceReq(VOS_VOID)
{
    VOS_UINT16  usEMLFileId;

    /*如果还有Email空间未初始化的电话本，向USIMM发送获取该EML文件记录数的请求*/
    if(gulPBFileCnt < gstPBCtrlInfo.ulEMLFileNum)
    {
        usEMLFileId = gstPBCtrlInfo.astEMLInfo[gulPBFileCnt].usEMLFileID;

        if(VOS_OK != SI_PB_QueryFileReq(usEMLFileId) )
        {
            PB_ERROR_LOG("SI_PB_InitEMLSpaceReq: SI_PB_QueryFileReq Failed");

            /* 发送请求失败，则没有继续初始化的必要 */
            SI_PB_ClearSPBContent(SI_CLEARSPB);

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    /*所有Email空间初始化完毕，进入IAP初始化的步骤*/

    PB_INFO_LOG("SI_PB_InitEMLSpaceReq: Go to PB_INIT_IAP_SPACE Step");

    gulPBFileCnt = 0;/*文件计数清零*/

    gstPBInitState.enPBInitStep = PB_INIT_IAP_SPACE;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitIAPSpaceReq
功能描述  : 向USIMM模块发送初始化IAP空间的请求，并设定下一步初始化步骤
输入参数  : 无
输出参数  :
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : SI_PB_QueryFileReq
被调函数  :
修订记录  :
1.  日    期   : 2009年6月15日
    作    者   : m00128685
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitIAPSpaceReq(VOS_VOID)
{
    VOS_UINT16  usIAPFileId;

    /*如果还有IAP空间未初始化的电话本，向USIMM发送获取该IAP文件记录数的请求*/
    if(gulPBFileCnt < gstPBCtrlInfo.ulIAPFileNum)
    {
        usIAPFileId = gstPBCtrlInfo.astIAPInfo[gulPBFileCnt].usIAPFileID;

        if(VOS_OK != SI_PB_QueryFileReq(usIAPFileId) )
        {
            PB_ERROR_LOG("SI_PB_InitEMLSpaceReq: SI_PB_QueryFileReq Failed");

            /* 发送请求失败，则没有继续初始化的必要 */
            SI_PB_ClearSPBContent(SI_CLEARSPB);

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    /*所有IAP空间初始化完毕，进入EXT初始化的步骤*/

    PB_INFO_LOG("SI_PB_InitIAPSpaceReq: Go to PB_INIT_EXT_SPACE Step");

    gulPBFileCnt = 0;/*文件计数清零*/

    gstPBInitState.enPBInitStep = PB_INIT_EXT_SPACE;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitEXTSpaceReq
功能描述  : 向USIMM模块发送初始化EXT空间的请求，并设定下一步初始化步骤
输入参数  : 无
输出参数  :
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : SI_PB_QueryFileReq
被调函数  :
修订记录  :
1.  日    期   : 2009年6月3日
    作    者   : m00128685
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitEXTSpaceReq(VOS_VOID)
{
    VOS_UINT16  usExtFileId;

    /*如果还有EXT空间未初始化的电话本，向USIMM发送获取该EXT文件记录数的请求*/
    if(gulPBFileCnt < gulPBInitExtFileNum)
    {
        /*EXT文件的下标从1开始，0预留不使用*/
        usExtFileId = gastEXTContent[gulPBFileCnt+1].usExtFileId;

        if(0xFFFF == usExtFileId)
        {
            gulPBFileCnt++;

            return VOS_OK;
        }

        if(VOS_OK != SI_PB_QueryFileReq(usExtFileId) )
        {
            PB_ERROR_LOG("SI_PB_InitEXTSpaceReq: SI_PB_QueryFileReq Failed");

            /* 如果初始EXT文件空间失败，将对应文件设置为FF后继续初始化下一步 */
            gulPBFileCnt++;
            SI_PB_ExtExceptionProc(usExtFileId);

            return VOS_OK;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    /*所有EXT空间初始化完毕，进入所有电话本空间初始化的步骤*/


    gulPBFileCnt = 0;/*文件计数清零*/
    gulPBRecordCnt = 1;/*从第一条记录开始初始化电话本内容*/

    if (USIMM_CARD_SIM == gstPBInitState.enCardType)/*SIM卡*/
    {
        gstPBInitState.enPBInitStep = PB_INIT_XDN_CONTENT;

        return VOS_OK;
    }

    /* 优先进行SEARCH方式的初始化 */
    if((0 != gstPBCtrlInfo.ulIAPFileNum)/*Type2 类型电话本存在*/
       &&(1 == gstPBConfigInfo.ucSPBFlag))/*支持复合电话本*/
    {
        gstPBInitState.enPBInitStep = PB_INIT_IAP_SEARCH;

        PB_INFO_LOG("SI_PB_InitEXTSpaceReq: Go to PB_INIT_IAP_SEARCH Step");
    }
    else
    {
        gstPBInitState.enPBInitStep = PB_INIT_EML_SEARCH;

        PB_INFO_LOG("SI_PB_InitEXTSpaceReq: Go to PB_INIT_EML_SEARCH Step");
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitIAPContentReq
功能描述  : 向USIMM模块发送获取ADN电话本内容的请求，并设定下一步初始化步骤
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : USIMM_GetFileReq
被调函数  :
修订记录  :
1.  日    期   : 2008年10月31日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_InitIAPContentReq(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    SI_PB_GETFILE_INFO_STRU     stGetFileInfo;

    if( gulPBFileCnt < gstPBCtrlInfo.ulIAPFileNum)/*目前IAP电话本还有未读的内容*/
    {
        stGetFileInfo.ucRecordNum   = (VOS_UINT8)gulPBRecordCnt;
        stGetFileInfo.usEfId        = gstPBCtrlInfo.astIAPInfo[gulPBFileCnt].usIAPFileID;

        /*读下一条记录的请求*/
        ulResult = SI_PB_GetFileReq(&stGetFileInfo);

        /*发送读请求失败，则退出初始化*/
        if( VOS_OK != ulResult )
        {
            PB_ERROR_LOG("SI_PB_InitIAPContentReq: SI_PB_GetFileReq Failed");

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            if ( VOS_NULL_PTR != gstIAPContent.pIAPContent)
            {
                /*lint -e534*/
                PB_FREE( gstIAPContent.pIAPContent);
                /*lint +e534*/

                gstIAPContent.pIAPContent = VOS_NULL_PTR;
            }

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    gstPBInitState.enPBInitStep = PB_INIT_EML_SEARCH;
    gulPBFileCnt = 0;
    gulPBRecordCnt = 1;/*为零时读取所有记录*/

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitEXTContentReq
功能描述  : 向USIMM模块发送获取EXT内容的请求，并设定下一步初始化步骤
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : USIMM_GetFileReq
被调函数  :
修订记录  :
1.  日    期   : 2009年5月8日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitEXTContentReq(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usFileId;
    VOS_UINT32                  ulPBType;
    VOS_UINT32                  i;
    SI_PB_GETFILE_INFO_STRU     stGetFileInfo;

    usFileId = SI_PB_TransferFileCnt2ExtFileID(gulPBFileCnt, &ulPBType);

    stGetFileInfo.ucRecordNum   = (VOS_UINT8)gulExtRecord;
    stGetFileInfo.usEfId        = usFileId;

    /*读下一条记录的请求*/
    ulResult = SI_PB_GetFileReq(&stGetFileInfo);

    /*发送读请求失败，则退出初始化*/
    if( VOS_OK != ulResult )
    {
        PB_ERROR_LOG("SI_PB_InitXDNContentReq: SI_PB_GetFileReq Failed");

        SI_PB_ExtExceptionProc(usFileId);

        gastPBContent[ulPBType].ucNumberLen -= SI_PB_NUM_LEN;

        /*所有ANR文件不支持扩展号码*/
        if(PB_ADN_CONTENT  == ulPBType )
        {
            for(i = 0; i < SI_PB_ANRMAX; i++)
            {
                gastANRContent[i].ucNumberLen = SI_PB_NUM_LEN;
            }
        }

        gstPBInitState.enPBInitStep = PB_INIT_XDN_CONTENT;

        return VOS_OK;
    }

    gstPBInitState.enReqStatus = PB_REQ_SEND;

    return VOS_OK;

}

/*****************************************************************************
函 数 名  : SI_PB_InitIAPSearchReq
功能描述  : 向USIMM模块发送IAP文件的查找请求
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : SI_PB_SearchReq
被调函数  :
修订记录  :
1.  日    期   : 2010年01月19日
    作    者   : H59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitIAPSearchReq(VOS_VOID)
{
    VOS_UINT32              ulResult;
    VOS_UINT8               aucContent[255];
    USIMM_U8_LVDATA_STRU    stData;

    /*lint -e534*/
    VOS_MemSet(aucContent, (VOS_CHAR)0xFF, sizeof(aucContent));
    /*lint +e534*/

    /* 目前IAP文件还有未初始化的内容 */
    if (gulPBFileCnt < gstPBCtrlInfo.ulIAPFileNum)
    {
        stData.pucData      = aucContent;
        stData.ulDataLen    = gstPBCtrlInfo.astIAPInfo[gulPBFileCnt].ucRecordLen;

        /* 发送IAP查找的请求 */
        ulResult = SI_PB_SearchFileReq(&stData,
                                    gstPBCtrlInfo.astIAPInfo[gulPBFileCnt].usIAPFileID);

        /* 发送读请求失败，则退出初始化 */
        if( VOS_OK != ulResult )
        {
            PB_ERROR_LOG("SI_PB_InitIAPSearchReq: SI_PB_SearchReq Failed");

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            /* 发送请求失败，则没有继续初始化的必要 */
            SI_PB_ClearSPBContent(SI_CLEARSPB);

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    gulPBFileCnt                        = 0;                        /* 文件记数器清零 */
    gulPBRecordCnt                      = 1;                        /* 为零时读取所有记录 */
    gstPBInitState.enPBInitStep         = PB_INIT_EML_SEARCH;       /* 下一步以查找方式来初始化EMAIL文件 */
    gstPBSearchCtrlInfo.usReadOffset    = 0;                        /* 读取查找匹配列表的偏移量从0开始 */

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitEmailSearchReq
功能描述  : 向USIMM模块发送EMAIL文件的查找请求
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : SI_PB_SearchReq
被调函数  :
修订记录  :
1.  日    期   : 2010年01月19日
    作    者   : H59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitEmailSearchReq(VOS_VOID)
{
    VOS_UINT32              ulResult;
    VOS_UINT16              usEMLFileId;
    VOS_UINT8               aucContent[255];
    USIMM_U8_LVDATA_STRU    stData;

    /*lint -e534*/
    VOS_MemSet(aucContent, (VOS_CHAR)0xFF, sizeof(aucContent));
    /*lint +e534*/

    /* 目前EMAIL还有未查找的文件 */
    if (gulPBFileCnt < gstPBCtrlInfo.ulEMLFileNum)
    {
        usEMLFileId = gstPBCtrlInfo.astEMLInfo[gulPBFileCnt].usEMLFileID;

        stData.pucData      = aucContent;
        stData.ulDataLen    = gstPBCtrlInfo.astEMLInfo[gulPBFileCnt].ucRecordLen;

        /* 发送查找请求 */
        ulResult = SI_PB_SearchFileReq( &stData, usEMLFileId);

        /*发送读请求失败，则退出初始化*/
        if( VOS_OK != ulResult )
        {
            PB_ERROR_LOG("SI_PB_InitEmailSearchReq: SI_PB_SearchReq Failed");

            /* 对应关系混乱，则没有继续初始化的必要,调接口请缓存 */
            SI_PB_ClearSPBContent(SI_CLEARSPB);

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    gulPBFileCnt                        = 0;                        /* 文件记数器清零 */
    gulPBRecordCnt                      = 1;                        /* 为零时读取所有记录 */
    gstPBInitState.enPBInitStep         = PB_INIT_ANR_SEARCH;       /* 下一步以查找方式来初始化ANR文件 */
    gstPBSearchCtrlInfo.usReadOffset    = 0;                        /* 读取查找匹配列表的偏移量从0开始 */

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitANRSearchReq
功能描述  : 向USIMM模块发送ANR文件的查找请求
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : SI_PB_SearchReq
被调函数  :
修订记录  :
1.  日    期   : 2010年01月20日
    作    者   : H59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitANRSearchReq(VOS_VOID)
{
    VOS_UINT32              ulResult;
    VOS_UINT16              usANRFileId;
    VOS_UINT8               aucContent[255];
    VOS_UINT8               ucXSuffix;
    VOS_UINT8               ucYSuffix;
    USIMM_U8_LVDATA_STRU    stData;

    /*lint -e534*/
    VOS_MemSet(aucContent, (VOS_CHAR)0xFF, sizeof(aucContent));
    /*lint +e534*/

    /* 目前ANR电话本还有未查找的内容 */
    if (gulPBFileCnt < gstPBCtrlInfo.ulANRFileNum)
    {
        /* 如果当前初始化的文件已被去激活，则跳置下一个电话本继续初始化 */
        if (VOS_OK != SI_PB_GetANRFid((gulPBFileCnt+1),&usANRFileId))
        {
            /* 对应关系混乱，则没有继续初始化的必要 */
            SI_PB_ClearSPBContent(SI_CLEARSPB);

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            PB_ERROR_LOG("SI_PB_InitANRSearchReq: Get ANR Fid Failed");

            return VOS_ERR;
        }

        /* 获取当前初始化的文件的ID */
        if (VOS_OK != SI_PB_GetANRSuffix(&ucXSuffix, &ucYSuffix, usANRFileId))
        {
            gstPBInitState.enPBInitState = SI_PB_INIT_PBTYPE_UNKOWN;

            PB_ERROR_LOG("SI_PB_InitANRSearchReq:PB Tpye Error");

            return VOS_ERR;
        }

        stData.pucData      = aucContent;
        stData.ulDataLen    = gastANRContent[ucYSuffix].ucRecordLen;

        /* 发送查询请求 */
        ulResult = SI_PB_SearchFileReq(&stData, usANRFileId);

        /* 发送读请求失败，则退出初始化 */
        if( VOS_OK != ulResult )
        {
            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            /* 调接口清除复合电话本缓存 */
            SI_PB_ClearSPBContent(SI_CLEARSPB);

            PB_ERROR_LOG("SI_PB_InitANRSearchReq: SI_PB_SearchReq Failed");

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    gulPBFileCnt                        = 0;                        /* 文件记数器清零 */
    gulPBRecordCnt                      = 1;                        /* 为零时读取所有记录 */
    gstPBInitState.enPBInitStep         = PB_INIT_XDN_SEARCH;       /* 下一步以查找方式来初始化XDN文件 */
    gstPBSearchCtrlInfo.usReadOffset    = 0;                        /* 读取查找匹配列表的偏移量从0开始 */

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitXDNSearchReq
功能描述  : 向USIMM模块发送XDN文件的查找请求
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : SI_PB_SearchReq
被调函数  :
修订记录  :
1.  日    期   : 2010年01月21日
    作    者   : H59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitXDNSearchReq(VOS_VOID)
{
    VOS_UINT32              ulResult;
    VOS_UINT32              ulPBType;
    VOS_UINT8               aucContent[255];
    USIMM_U8_LVDATA_STRU    stData;

    /*lint -e534*/
    VOS_MemSet(aucContent, (VOS_CHAR)0xFF, sizeof(aucContent));
    /*lint +e534*/

    /* 目前XDN电话本还有未读的内容 */
    if (gulPBFileCnt < gulPBInitFileNum)
    {
        /*lint -e534*/
        SI_PB_GetXDNPBType(&ulPBType, gstPBInitState.ausFileId[gulPBFileCnt]);
        /*lint +e534*/

        /* 如果当前初始化的文件已被去激活，则跳置下一个电话本继续初始化 */
        if (USIMM_EFSTATUS_DEACTIVE == gastPBContent[ulPBType].enActiveStatus)
        {
            PB_NORMAL_LOG("SI_PB_InitXDNSearchReq:The File is Decative");

            SI_PB_JumpToNextPB(ulPBType);

            return VOS_OK;
        }

        stData.pucData      = aucContent;
        stData.ulDataLen    = gastPBContent[ulPBType].ucRecordLen;

        /* 发送查找请求 */
        ulResult = SI_PB_SearchFileReq(&stData,
                                    gstPBInitState.ausFileId[gulPBFileCnt]);

        /* 发送读请求失败，则退出初始化 */
        if (VOS_OK != ulResult)
        {
            PB_ERROR_LOG("SI_PB_InitXDNSearchReq:SI_PB_SearchReq Failed");

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            /* 调接口清除电话本缓存 */
            SI_PB_ClearPBContent(SI_CLEARXDN);
            SI_PB_ClearSPBContent(SI_CLEARSPB);

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    gulPBFileCnt    = 0;
    gulPBRecordCnt  = 1;

    if(VOS_FALSE == gucPBCStatus)
    {
        gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;
    }
    else
    {
        gstPBInitState.enPBInitStep = PB_INIT_PBC_SEARCH;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitPBCSearchReq
功能描述  : 向USIMM模块发送PBC文件的查找请求
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : SI_PB_SearchReq
被调函数  :
修订记录  :
1.  日    期   : 2010年02月02日
    作    者   : H59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitPBCSearchReq(VOS_VOID)
{
    VOS_UINT32              ulResult;
    VOS_UINT16              usPBCFileId;
    VOS_UINT8               aucContent[2];
    USIMM_U8_LVDATA_STRU    stData;

    usPBCFileId     = gstPBCtrlInfo.astPBCInfo[0].usFileID;
    aucContent[0]   = 0;
    aucContent[1]   = 0;

    /* 目前PBC电话本还有未查找的内容 */
    if (gulPBFileCnt < 1)
    {
        stData.pucData      = aucContent;
        stData.ulDataLen    = sizeof(aucContent);

        /* 发送查询请求 */
        ulResult = SI_PB_SearchFileReq(&stData, usPBCFileId);

        /* 发送读请求失败，则退出初始化 */
        if( VOS_OK != ulResult )
        {
            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            PB_ERROR_LOG("SI_PB_InitPBCSearchReq: SI_PB_SearchReq Failed");

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    /* PBC查找结束，进行重同步过程 */
    gstPBInitState.enPBInitStep = PB_INIT_SYNCH;
    gulPBFileCnt    = 0;
    gulPBRecordCnt  = 0;

    /* 填写3G重同步需要的文件信息 */
    gstPBInitState.ausFileId[0] = EFPSC;
    gstPBInitState.ausFileId[1] = EFCC;
    gstPBInitState.ausFileId[2] = EFPUID;
    /*gstPBInitState.ausFileId[3] = gstPBCtrlInfo.astPBCInfo[0].usFileID; */
    gstPBInitState.ausFileId[3] = gstPBCtrlInfo.astUIDInfo[0].usFileID;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitIAPContentReq2
功能描述  : 根据查找结果向USIMM模块发送IAP文件的读取请求
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : USIMM_GetFileReq
被调函数  :
修订记录  :
1.  日    期   : 2010年01月19日
    作    者   : H59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitIAPContentReq2(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usOffset;
    SI_PB_GETFILE_INFO_STRU     stGetFileInfo;

    /* 当前IAP文件还有未初始化的记录 */
    if (gstPBSearchCtrlInfo.usReadOffset < gstPBSearchCtrlInfo.usReadNum)
    {
        usOffset = gstPBSearchCtrlInfo.usReadOffset;

        stGetFileInfo.ucRecordNum   = gstPBSearchCtrlInfo.aucReadString[usOffset];
        stGetFileInfo.usEfId        = gstPBSearchCtrlInfo.usEfId;

        /* 读下一条记录的请求 */
        ulResult = SI_PB_GetFileReq(&stGetFileInfo);

        /* 发送读请求失败，则退出初始化 */
        if ( VOS_OK != ulResult )
        {
            PB_ERROR_LOG("SI_PB_InitIAPContentReq2: SI_PB_GetFileReq Failed");

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            SI_PB_ClearSPBContent(SI_CLEARSPB);

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    if (gulPBFileCnt < gstPBCtrlInfo.ulIAPFileNum)
    {
        /* 还有IAP文件要进行查找处理 */
        gstPBInitState.enPBInitStep     = PB_INIT_IAP_SEARCH;
    }
    else
    {
        /* 下一步以查找方式来初始化EMAIL文件 */
        gstPBInitState.enPBInitStep     = PB_INIT_EML_SEARCH;
        gulPBFileCnt                    = 0;    /* 文件记数器清零 */
    }

    gulPBRecordCnt                      = 1;    /* 为零时读取所有记录 */
    gstPBSearchCtrlInfo.usReadOffset    = 0;    /* 读取查找匹配列表的偏移量从0开始 */

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitEmailContentReq
功能描述  : 根据查找结果向USIMM模块发送EMAIL文件的读取请求
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年01月20日
    作    者   : H59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitEmailContentReq(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usOffset;
    SI_PB_GETFILE_INFO_STRU     stGetFileInfo;

    /* 当前EMAIL文件还有未初始化的记录 */
    if (gstPBSearchCtrlInfo.usReadOffset < gstPBSearchCtrlInfo.usReadNum)
    {
        usOffset = gstPBSearchCtrlInfo.usReadOffset;

        stGetFileInfo.ucRecordNum   = gstPBSearchCtrlInfo.aucReadString[usOffset];
        stGetFileInfo.usEfId        = gstPBSearchCtrlInfo.usEfId;

        /*读下一条记录的请求*/
        ulResult = SI_PB_GetFileReq(&stGetFileInfo);

        /*发送读请求失败，则退出初始化*/
        if (VOS_OK != ulResult)
        {
            PB_ERROR_LOG("SI_PB_InitEmailContentReq: SI_PB_GetFileReq Failed");

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            SI_PB_ClearSPBContent(SI_CLEARSPB);

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    if (gulPBFileCnt < gstPBCtrlInfo.ulEMLFileNum)
    {
        /* 还有EMAIL文件要进行查找处理 */
        gstPBInitState.enPBInitStep     = PB_INIT_EML_SEARCH;
    }
    else
    {
        /* 下一步以查找方式来初始化ANR文件 */
        gstPBInitState.enPBInitStep     = PB_INIT_ANR_SEARCH;
        gulPBFileCnt                    = 0;    /* 文件记数器清零 */
    }

    gulPBRecordCnt                      = 1;    /* 为零时读取所有记录 */
    gstPBSearchCtrlInfo.usReadOffset    = 0;    /* 读取查找匹配列表的偏移量从0开始 */

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitANRContentReq2
功能描述  : 根据查找结果向USIMM模块发送ANR文件的读取请求
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年01月20日
    作    者   : H59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitANRContentReq2(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usOffset;
    SI_PB_GETFILE_INFO_STRU     stGetFileInfo;

    /* 当前ANR文件还有未初始化的记录 */
    if (gstPBSearchCtrlInfo.usReadOffset < gstPBSearchCtrlInfo.usReadNum)
    {
        usOffset = gstPBSearchCtrlInfo.usReadOffset;

        stGetFileInfo.ucRecordNum   = gstPBSearchCtrlInfo.aucReadString[usOffset];
        stGetFileInfo.usEfId        = gstPBSearchCtrlInfo.usEfId;

        /* 读下一条记录的请求 */
        ulResult = SI_PB_GetFileReq(&stGetFileInfo);

        /*发送读请求失败，则退出初始化*/
        if (VOS_OK != ulResult)
        {
            PB_ERROR_LOG("SI_PB_InitANRContentReq2: SI_PB_GetFileReq Failed");

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            /*调接口清除复合电话本缓存*/
            SI_PB_ClearSPBContent(SI_CLEARSPB);

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    if (gulPBFileCnt < gstPBCtrlInfo.ulANRFileNum)
    {
        /* 还有ANR文件要进行查找处理 */
        gstPBInitState.enPBInitStep = PB_INIT_ANR_SEARCH;
    }
    else
    {
        /* 下一步以查找方式来初始化XDN文件 */
        gstPBInitState.enPBInitStep = PB_INIT_XDN_SEARCH;
        gulPBFileCnt                = 0;        /* 文件记数器清零 */
    }

    gulPBRecordCnt                      = 1;    /* 为零时读取所有记录 */
    gstPBSearchCtrlInfo.usReadOffset    = 0;    /* 读取查找匹配列表的偏移量从0开始 */

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitXDNContentReq2
功能描述  : 根据查找结果向USIMM模块发送XDN文件的读取请求
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年01月21日
    作    者   : H59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitXDNContentReq2(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usOffset;
    SI_PB_GETFILE_INFO_STRU     stGetFileInfo;

    /* 当前XDN文件还有未初始化的记录 */
    if (gstPBSearchCtrlInfo.usReadOffset < gstPBSearchCtrlInfo.usReadNum)
    {
        usOffset = gstPBSearchCtrlInfo.usReadOffset;

        stGetFileInfo.ucRecordNum   = gstPBSearchCtrlInfo.aucReadString[usOffset];
        stGetFileInfo.usEfId        = gstPBSearchCtrlInfo.usEfId;

        /* 读下一条记录的请求 */
        ulResult = SI_PB_GetFileReq(&stGetFileInfo);

        /* 发送读请求失败，则退出初始化 */
        if (VOS_OK != ulResult)
        {
            PB_ERROR_LOG("SI_PB_InitXDNContentReq2: SI_PB_GetFileReq Failed");

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            /* 调接口清除复合电话本缓存 */
            SI_PB_ClearSPBContent(SI_CLEARSPB);
            SI_PB_ClearPBContent(SI_CLEARXDN);

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    if (gulPBFileCnt < gulPBInitFileNum)
    {
        /* 还有XDN文件要进行查找处理 */
        gstPBInitState.enPBInitStep         = PB_INIT_XDN_SEARCH;
        gstPBSearchCtrlInfo.usReadOffset    = 0;    /* 读取查找匹配列表的偏移量从0开始 */
    }
    else
    {
        gulPBFileCnt    = 0;
        gulPBRecordCnt  = 1;

        if (USIMM_CARD_SIM == gstPBInitState.enCardType)/*SIM卡*/
        {
            /* SIM卡无重同步过程，通知APP初始化已完成 */
            PB_INFO_LOG("SI_PB_InitXDNContentReq2: Go to PB_INIT_INFO_APP Step");

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;
        }
        else
        {
            PB_INFO_LOG("SI_PB_InitXDNContentReq2: Go to PB_INIT_PBC_SEARCH Step");

            if(VOS_FALSE == gucPBCStatus)
            {
                gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;
            }
            else
            {
                gstPBInitState.enPBInitStep = PB_INIT_PBC_SEARCH;
            }
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitPBCContentReq2
功能描述  : 根据查找结果向USIMM模块发送PBC文件的读取请求
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年02月02日
    作    者   : H59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitPBCContentReq2(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usOffset;
    SI_PB_GETFILE_INFO_STRU     stGetFileInfo;

    /* 当前PBC文件还有未初始化的记录 */
    if (gstPBSearchCtrlInfo.usReadOffset < gstPBSearchCtrlInfo.usReadNum)
    {
        usOffset = gstPBSearchCtrlInfo.usReadOffset;

        stGetFileInfo.ucRecordNum   = gstPBSearchCtrlInfo.aucReadString[usOffset];
        stGetFileInfo.usEfId        = gstPBSearchCtrlInfo.usEfId;

        /* 读下一条记录的请求 */
        ulResult = SI_PB_GetFileReq(&stGetFileInfo);

        /* 发送读请求失败，则退出初始化 */
        if (VOS_OK != ulResult)
        {
            PB_ERROR_LOG("SI_PB_InitPBCContentReq2: SI_PB_GetFileReq Failed");

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }
    else
    {
        gulPBFileCnt    = 0;
        gulPBRecordCnt  = 0;

        /* 填写3G重同步需要的文件信息 */
        gstPBInitState.ausFileId[0] = EFPSC;
        gstPBInitState.ausFileId[1] = EFCC;
        gstPBInitState.ausFileId[2] = EFPUID;
        /*gstPBInitState.ausFileId[3] = gstPBCtrlInfo.astPBCInfo[0].usFileID; */
        gstPBInitState.ausFileId[3] = gstPBCtrlInfo.astUIDInfo[0].usFileID;
        gstPBInitState.enPBInitStep = PB_INIT_SYNCH;

        return VOS_OK;
    }
}

/*****************************************************************************
函 数 名  : SI_PB_InitPBCContentReq
功能描述  : 向USIMM模块发送PBC文件的读取请求
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年02月02日
    作    者   : H59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitPBCContentReq(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usPBCFileId;
    SI_PB_GETFILE_INFO_STRU     stGetFileInfo;

    usPBCFileId     = gstPBCtrlInfo.astPBCInfo[0].usFileID;

    /* 目前PBC电话本还有未读取的记录 */
    if (gulPBFileCnt < 1)
    {
        stGetFileInfo.ucRecordNum   = (VOS_UINT8)gulPBRecordCnt;
        stGetFileInfo.usEfId        = usPBCFileId;

        ulResult = SI_PB_GetFileReq(&stGetFileInfo);

        /*发送读请求失败，则退出初始化*/
        if( VOS_OK != ulResult )
        {
            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            PB_ERROR_LOG("SI_PB_InitPBCContentReq: SI_PB_GetFileReq Failed");

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }
    else
    {
        gulPBFileCnt    = 0;
        gulPBRecordCnt  = 0;

        /* 填写3G重同步需要的文件信息 */
        gstPBInitState.ausFileId[0] = EFPSC;
        gstPBInitState.ausFileId[1] = EFCC;
        gstPBInitState.ausFileId[2] = EFPUID;
        /*gstPBInitState.ausFileId[3] = gstPBCtrlInfo.astPBCInfo[0].usFileID; */
        gstPBInitState.ausFileId[3] = gstPBCtrlInfo.astUIDInfo[0].usFileID;
        gstPBInitState.enPBInitStep = PB_INIT_SYNCH;

        return VOS_OK;
    }
}

/*****************************************************************************
函 数 名  : SI_PB_InitXDNContentReq
功能描述  : 向USIMM模块发送获取XDN电话本内容的请求，并设定下一步初始化步骤
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : USIMM_GetFileReq
被调函数  :
修订记录  :
1.  日    期   : 2008年10月31日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_InitXDNContentReq(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT32                  ulPBType;
    SI_PB_GETFILE_INFO_STRU     stGetFileInfo;

    if( gulPBFileCnt < gulPBInitFileNum )/*目前XDN电话本还有未读的内容*/
    {
        /*lint -e534*/
        SI_PB_GetXDNPBType(&ulPBType, gstPBInitState.ausFileId[gulPBFileCnt]);
        /*lint +e534*/

        /*如果当前初始化的文件已被去激活，则跳置下一个电话本继续初始化*/
        if( USIMM_EFSTATUS_DEACTIVE == gastPBContent[ulPBType].enActiveStatus )
        {
            PB_NORMAL_LOG("SI_PB_InitXDNContentReq:The File is Decative");

            SI_PB_JumpToNextPB(ulPBType);

            return VOS_OK;
        }

        stGetFileInfo.ucRecordNum   = (VOS_UINT8)gulPBRecordCnt;
        stGetFileInfo.usEfId        = gstPBInitState.ausFileId[gulPBFileCnt];

        /*读下一条记录的请求*/
        ulResult = SI_PB_GetFileReq(&stGetFileInfo);

        /*发送读请求失败，则退出初始化*/
        if( VOS_OK != ulResult )
        {
            PB_ERROR_LOG("SI_PB_InitXDNContentReq: SI_PB_GetFileReq Failed");

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            if ( VOS_NULL_PTR != gastPBContent[ulPBType].pContent )
            {
                /*lint -e534*/
                PB_FREE( gastPBContent[ulPBType].pContent);
                /*lint +e534*/

                gastPBContent[ulPBType].pContent = VOS_NULL_PTR;
            }

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    if (USIMM_CARD_SIM == gstPBInitState.enCardType)/*SIM卡*/
    {
        PB_INFO_LOG("SI_PB_InitXDNContentReq: Go to PB_INIT_INFO_APP Step");

        gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;
    }
    else
    {
        PB_INFO_LOG("SI_PB_InitXDNContentReq: Go to PB_INIT_PBC_SEARCH Step");

        if(VOS_FALSE == gucPBCStatus)
        {
            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;
        }
        else
        {
            gstPBInitState.enPBInitStep = PB_INIT_PBC_SEARCH;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitANRContentReq
功能描述  : 向USIMM模块发送获取ADN电话本内容的请求，并设定下一步初始化步骤
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : USIMM_GetFileReq
被调函数  :
修订记录  :
1.  日    期   : 2008年10月31日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_InitANRContentReq(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usANRFileId;
    SI_PB_GETFILE_INFO_STRU     stGetFileInfo;

    if( gulPBFileCnt < gstPBCtrlInfo.ulANRFileNum)/*目前ANR电话本还有未读的内容*/
    {
        /*如果当前初始化的文件已被去激活，则跳置下一个电话本继续初始化*/
        if (VOS_OK != SI_PB_GetANRFid((gulPBFileCnt+1),&usANRFileId))
        {
            /* 对应关系混乱，则没有继续初始化的必要 */
            SI_PB_ClearSPBContent(SI_CLEARSPB);

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            PB_ERROR_LOG("SI_PB_InitANRContentReq: Get ANR Fid Failed");

            return VOS_ERR;
        }

        stGetFileInfo.ucRecordNum   = (VOS_UINT8)gulPBRecordCnt;
        stGetFileInfo.usEfId        = usANRFileId;

        /*读下一条记录的请求*/
        ulResult = SI_PB_GetFileReq(&stGetFileInfo);

        /*发送读请求失败，则退出初始化*/
        if( VOS_OK != ulResult )
        {
            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            /*调接口清除复合电话本缓存*/
            SI_PB_ClearSPBContent(SI_CLEARSPB);

            PB_ERROR_LOG("SI_PB_InitANRContentReq: SI_PB_GetFileReq Failed");

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    gulPBFileCnt = 0;
    gulPBRecordCnt = 1;
    gstPBInitState.enPBInitStep = PB_INIT_XDN_SEARCH;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitEMLContentReq
功能描述  : 向USIMM模块发送获取EXT内容的请求，并设定下一步初始化步骤
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : USIMM_GetFileReq
被调函数  :
修订记录  :
1.  日    期   : 2009年6月3日
    作    者   : m00128685
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitEXTRContentReq(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usEXTFileId;
    VOS_UINT32                  i;
    SI_PB_GETFILE_INFO_STRU     stGetFileInfo;

    usEXTFileId = gastEXTContent[PB_ADN_CONTENT].usExtFileId;

    stGetFileInfo.ucRecordNum   = (VOS_UINT8)gulExtRecord;
    stGetFileInfo.usEfId        = usEXTFileId;

    /*读下一条记录的请求*/
    ulResult = SI_PB_GetFileReq(&stGetFileInfo);

    /*发送读请求失败，则设置对应EXT为无效，继续初始化其余ANR内容*/
    if( VOS_OK != ulResult )
    {
        SI_PB_ExtExceptionProc(usEXTFileId);

        gastPBContent[PB_ADN_CONTENT].ucNumberLen = SI_PB_NUM_LEN;

        /*所有ANR文件不支持扩展号码*/
        for(i = 0; i < SI_PB_ANRMAX; i++)
        {
            gastANRContent[i].ucNumberLen = SI_PB_NUM_LEN;
        }

        /*AT2D15843*/
        gstPBInitState.enPBInitStep = PB_INIT_ANR_CONTENT;

        PB_ERROR_LOG("SI_PB_InitEXTRContentReq: SI_PB_GetFileReq Failed");

        return VOS_OK;
    }

    gstPBInitState.enReqStatus = PB_REQ_SEND;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitEXTRContentReq
功能描述  : 向USIMM模块发送获取EXT内容的请求，并设定下一步初始化步骤
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : USIMM_GetFileReq
被调函数  :
修订记录  :
1.  日    期   : 2009年6月3日
    作    者   : m00128685
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitEMLContentReq(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usEMLFileId;
    SI_PB_GETFILE_INFO_STRU     stGetFileInfo;

    if( gulPBFileCnt < gstPBCtrlInfo.ulEMLFileNum)/*目前ANR电话本还有未读的内容*/
    {
        usEMLFileId = gstPBCtrlInfo.astEMLInfo[gulPBFileCnt].usEMLFileID;

        stGetFileInfo.ucRecordNum   = (VOS_UINT8)gulPBRecordCnt;
        stGetFileInfo.usEfId        = usEMLFileId;

        /*读下一条记录的请求*/
        ulResult = SI_PB_GetFileReq(&stGetFileInfo);

        /*发送读请求失败，则退出初始化*/
        if( VOS_OK != ulResult )
        {
            PB_ERROR_LOG("SI_PB_InitXDNContentReq: SI_PB_GetFileReq Failed");

            /* 对应关系混乱，则没有继续初始化的必要 */
            SI_PB_ClearSPBContent(SI_CLEARSPB);

            PB_ERROR_LOG("SI_PB_InitANRContentReq: Get ANR Fid Failed");

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            /*调接口请缓存*/

            return VOS_ERR;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;

        return VOS_OK;
    }

    gulPBFileCnt = 0;
    gulPBRecordCnt = 1;
    gstPBInitState.enPBInitStep = PB_INIT_ANR_SEARCH;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitSYNCHReq
功能描述  : 向USIMM模块发送获取3G重同步所需文件的请求，并设定下一步初始化步骤
输入参数  : 无
输出参数  : VOS_OK
            VOS_ERR
返 回 值  :
调用函数  : USIMM_GetFileReq
被调函数  :
修订记录  :
1.  日    期   : 2008年10月31日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_InitSYNCHReq(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usZero = 0;
    VOS_UINT8                   ucRecordNum;
    SI_PB_SETFILE_INFO_STRU     stUpdateReq;
    SI_PB_GETFILE_INFO_STRU     stGetFileInfo;

    /* 总共有4个3G重同步文件,PBC文件在其它函数中进行初始化 */
    if( 4 > gulPBFileCnt )
    {
        stGetFileInfo.ucRecordNum   = (VOS_UINT8)gulPBRecordCnt;
        stGetFileInfo.usEfId        = gstPBInitState.ausFileId[gulPBFileCnt];

        /*文件的数据量不大，一次获取所有记录内容*/
        ulResult = SI_PB_GetFileReq(&stGetFileInfo);

        /* 发送读取文件请求失败，设置初始化状态为初始化已完成 */
        if ( VOS_OK != ulResult )
        {
            PB_ERROR_LOG("SI_PB_InitSYNCHReq: SI_PB_GetFileReq Failed");

            gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

            return VOS_OK;
        }

        gstPBInitState.enReqStatus = PB_REQ_SEND;
    }
    /*判断ADN电话本的内容是否发生变化*/
    else if ( 0 != gstPBInitState.stPBCUpdate.ucEntryChangeNum )
    {
        /*更新发生变化的PBC文件记录*/
        if ( gulPBRecordCnt <= gstPBInitState.stPBCUpdate.ucEntryChangeNum )
        {
            /*获取发生变化的PBC文件的记录号*/
            ucRecordNum = gstPBInitState.stPBCUpdate.aucRecord[gulPBRecordCnt];

            stUpdateReq.pucEfContent    = (VOS_UINT8 *)&usZero;
            stUpdateReq.ucRecordNum     = ucRecordNum;
            stUpdateReq.ulEfLen         = sizeof(usZero);
            stUpdateReq.usEfId          = gstPBCtrlInfo.astPBCInfo[0].usFileID;

            /*把对应的PBC记录置为0*/
            ulResult = SI_PB_SetFileReq(&stUpdateReq);

            /*发送写文件请求失败，则退出初始化*/
            if ( VOS_OK != ulResult )
            {
                PB_ERROR_LOG("SI_PB_InitSYNCHReq: SI_PB_SetFileReq Failed");

                gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;

                return VOS_ERR;
            }

            gstPBInitState.enReqStatus = PB_REQ_SEND;
        }
        /*判断是否需要更新CC、UID和PSC等重同步文件*/
        else if ( 1 != gstPBInitState.stPBCUpdate.ucCCUpdateFlag )
        {
            SI_PB_IncreaceCCValue(gstPBInitState.stPBCUpdate.ucEntryChangeNum,1);

            gstPBInitState.stPBCUpdate.ucCCUpdateFlag = 1;

            gstPBInitState.enReqStatus = PB_REQ_SEND;
        }
        /*等待重同步过程完成*/
        else
        {
            /*等待3G重同步过程*/
            gstPBInitState.enReqStatus = PB_REQ_SEND;
        }
    }
    /*重同步过程完成，进入回调上报过程*/
    else
    {
        PB_INFO_LOG("SI_PB_InitSYNCHReq:Go to PB_INIT_INFO_APP Step");

        gstPBInitState.enPBInitStep = PB_INIT_INFO_APP;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitInfoApp
功能描述  : 初始化最后一步，通过消息发送给Acpu同步全局变量
输入参数  : 无
输出参数  : gstPBInitState
返 回 值  : VOS_OK
            VOS_ERR
调用函数  : SI_PBSendGobalToAcpu
被调函数  :
修订记录  :
1.  日    期   : 2008年10月31日
    作    者   : m00128685
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitInfoApp(VOS_VOID)
{
    VOS_UINT32              ulBdnState;
    VOS_UINT32              ulFdnState;
    SI_PB_EVENT_INFO_STRU   stPBEvent;

    stPBEvent.ClientId    = MN_CLIENT_ALL;
    stPBEvent.ClientId    = MN_GetRealClientId(stPBEvent.ClientId, MAPS_PB_PID);
    stPBEvent.OpId        = 0;
    stPBEvent.PBError     = VOS_OK;
    stPBEvent.PBEventType = SI_PB_EVENT_INFO_IND;

    /*获取FDN、BDN状态*/
    USIMM_BdnQuery(&ulBdnState);
    USIMM_FdnQuery(&ulFdnState, VOS_NULL_PTR);

    /*填写需要回调上报的电话本信息*/
    stPBEvent.PBEvent.PBInfoInd.ADNRecordNum    = gastPBContent[PB_ADN_CONTENT].usTotalNum;
    stPBEvent.PBEvent.PBInfoInd.ADNTextLen      = (VOS_UINT16)gastPBContent[PB_ADN_CONTENT].ucNameLen;
    stPBEvent.PBEvent.PBInfoInd.ADNNumberLen    = gastPBContent[PB_ADN_CONTENT].ucNumberLen;
    stPBEvent.PBEvent.PBInfoInd.BDNRecordNum    = gastPBContent[PB_BDN_CONTENT].usTotalNum;
    stPBEvent.PBEvent.PBInfoInd.BdnState        = (VOS_UINT16)ulBdnState;
    stPBEvent.PBEvent.PBInfoInd.BDNTextLen      = (VOS_UINT16)gastPBContent[PB_BDN_CONTENT].ucNameLen;
    stPBEvent.PBEvent.PBInfoInd.BDNNumberLen    = gastPBContent[PB_BDN_CONTENT].ucNumberLen;
    stPBEvent.PBEvent.PBInfoInd.FDNRecordNum    = gastPBContent[PB_FDN_CONTENT].usTotalNum;
    stPBEvent.PBEvent.PBInfoInd.FdnState        = (VOS_UINT16)ulFdnState;
    stPBEvent.PBEvent.PBInfoInd.FDNTextLen      = (VOS_UINT16)gastPBContent[PB_FDN_CONTENT].ucNameLen;
    stPBEvent.PBEvent.PBInfoInd.FDNNumberLen    = gastPBContent[PB_FDN_CONTENT].ucNumberLen;
    stPBEvent.PBEvent.PBInfoInd.MSISDNTextLen   = (VOS_UINT16)gastPBContent[PB_MSISDN_CONTENT].ucNameLen;
    stPBEvent.PBEvent.PBInfoInd.MSISDNRecordNum = gastPBContent[PB_MSISDN_CONTENT].usTotalNum;
    stPBEvent.PBEvent.PBInfoInd.MSISDNNumberLen = gastPBContent[PB_MSISDN_CONTENT].ucNumberLen;
    stPBEvent.PBEvent.PBInfoInd.ANRNumberLen    = gastANRContent[0].ucNumberLen;
    stPBEvent.PBEvent.PBInfoInd.EMAILTextLen    = gstEMLContent.ucDataLen;
    stPBEvent.PBEvent.PBInfoInd.CardType        = (VOS_UINT16)gstPBInitState.enCardType;

    /*lint -e534*/
    SI_PBCallback(&stPBEvent);
    /*lint +e534*/

    /*设置初始化状态为已初始化*/
    gstPBInitState.enPBInitStep = PB_INIT_FINISHED;

    /*通知USIM模块可以进行时钟停止模式*/
    SI_PB_InitStatusInd(USIMM_PB_IDLE);

    SI_PBSendGlobalToAcpu();

    /* 通知NAS电话本初始化完成，用于ECALL处理 */
    SI_PB_EcallInitInd();

    gstPBInitState.enReqStatus = PB_REQ_SEND;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitEccProc
功能描述  : 处理USIMM模块上报的ECC号码
输入参数  : pstMsg:USIMM模块上报的消息
输出参数  : gastPBContent[PB_ECC_CONTENT].pContent:ECC号码内容
            gastPBContent[PB_ECC_CONTENT].usTotalNum:ECC号码数目
            gastPBContent[PB_ECC_CONTENT].enInitialState:ECC电话本初始化状态

返 回 值  :
调用函数  : VOS_MemAlloc
            VOS_MemCpy
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_InitEccProc(PBMsgBlock *pstMsg)
{
    USIMM_ECCNUMBER_IND_STRU           *pstPBMsg;
    VOS_UINT32                          ulOffset;
    VOS_UINT8                          *pucRecord;

    pstPBMsg = (USIMM_ECCNUMBER_IND_STRU *)(pstMsg);

    /* 参数检查，上报的ECC号码为空，则初始化步骤出错，返回错误 */
    if (VOS_NULL == pstPBMsg->usFileSize)
    {
        gastPBContent[PB_ECC_CONTENT].enInitialState = PB_FILE_NOT_EXIST;
        return VOS_ERR;
    }

    gastPBContent[PB_ECC_CONTENT].pContent\
        = (VOS_UINT8 *)PB_MALLOC(pstPBMsg->usFileSize);

    if ( VOS_NULL_PTR == gastPBContent[PB_ECC_CONTENT].pContent )
    {
        PB_ERROR_LOG("SI_PB_InitEccProc:MemAlloc Failed");

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(gastPBContent[PB_ECC_CONTENT].pContent, pstPBMsg->ucContent, pstPBMsg->usFileSize);
    /*lint +e534*/

    /*USIM卡ECC号码为记录文件，SIM卡ECC文件为透明文件*/
    if ( USIMM_CARD_USIM == pstPBMsg->ucEccType )
    {
        gastPBContent[PB_ECC_CONTENT].usTotalNum  = pstPBMsg->ucRecordNum;
        gastPBContent[PB_ECC_CONTENT].ucRecordLen = (VOS_UINT8)(pstPBMsg->usFileSize/pstPBMsg->ucRecordNum);
        gastPBContent[PB_ECC_CONTENT].ucNameLen   = gastPBContent[PB_ECC_CONTENT].ucRecordLen - SI_PB_ECC_EXCEPT_NAME;
        gastPBContent[PB_ECC_CONTENT].ucNumberLen = SI_PB_ECC_LEN;
    }
    else
    {
        gastPBContent[PB_ECC_CONTENT].usTotalNum  = (VOS_UINT16)(pstPBMsg->usFileSize/SI_PB_ECC_LEN);
        gastPBContent[PB_ECC_CONTENT].ucRecordLen = SI_PB_ECC_LEN;
        gastPBContent[PB_ECC_CONTENT].ucNameLen   = 0;
        gastPBContent[PB_ECC_CONTENT].ucNumberLen = SI_PB_ECC_LEN;
    }

    /*判断每条记录的有效性，得出已用记录数*/
    for (ulOffset = 0; ulOffset < gastPBContent[PB_ECC_CONTENT].usTotalNum; ulOffset++)
    {
       pucRecord = pstPBMsg->ucContent +(ulOffset*gastPBContent[PB_ECC_CONTENT].ucRecordLen);

       if ( VOS_OK == SI_PB_CheckEccValidity(pucRecord))
       {
            gastPBContent[PB_ECC_CONTENT].usUsedNum++;
       }
    }

    /*置ECC电话本初始化状态为已初始化*/
    gastPBContent[PB_ECC_CONTENT].enInitialState = PB_INITIALISED;

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
函 数 名  : SI_PB_InitXeccProc
功能描述  : 处理USIMM模块上报的XECC号码
输入参数  : pstMsg:USIMM模块上报的消息
输出参数  : 无
修订记录  :
1.  日    期   : 2015年06月11日
    作    者   : h00300778
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_InitXeccProc(PBMsgBlock *pstMsg)
{
    USIMM_XECCNUMBER_IND_STRU          *pstPBMsg;
    VOS_UINT32                          ulOffset;
    VOS_UINT8                          *pucRecord;

    pstPBMsg = (USIMM_XECCNUMBER_IND_STRU *)(pstMsg);

    /* 参数检查，上报的ECC号码为空，则初始化步骤出错，返回错误 */
    if (VOS_NULL == pstPBMsg->usFileSize)
    {
        gastPBContent[PB_XECC_CONTENT].enInitialState = PB_FILE_NOT_EXIST;
        return VOS_ERR;
    }

    gastPBContent[PB_XECC_CONTENT].pContent = (VOS_UINT8 *)PB_MALLOC(pstPBMsg->usFileSize);

    if ( VOS_NULL_PTR == gastPBContent[PB_XECC_CONTENT].pContent )
    {
        PB_ERROR_LOG("SI_PB_InitXeccProc:MemAlloc Failed");

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(gastPBContent[PB_XECC_CONTENT].pContent, pstPBMsg->ucContent, pstPBMsg->usFileSize);

    gastPBContent[PB_XECC_CONTENT].usTotalNum  = (VOS_UINT16)(pstPBMsg->usFileSize/SI_PB_ECC_LEN);
    gastPBContent[PB_XECC_CONTENT].ucRecordLen = SI_PB_ECC_LEN;
    gastPBContent[PB_XECC_CONTENT].ucNameLen   = 0;
    gastPBContent[PB_XECC_CONTENT].ucNumberLen = SI_PB_ECC_LEN;

    /*判断每条记录的有效性，得出已用记录数*/
    for (ulOffset = 0; ulOffset < gastPBContent[PB_XECC_CONTENT].usTotalNum; ulOffset++)
    {
       pucRecord = pstPBMsg->ucContent +(ulOffset*gastPBContent[PB_XECC_CONTENT].ucRecordLen);

       if ( VOS_OK == SI_PB_CheckEccValidity(pucRecord))
       {
            gastPBContent[PB_XECC_CONTENT].usUsedNum++;
       }
    }

    /*置ECC电话本初始化状态为已初始化*/
    gastPBContent[PB_XECC_CONTENT].enInitialState = PB_INITIALISED;

    return VOS_OK;
}
#endif

/*****************************************************************************
函 数 名  : SI_PB_InitStateProc
功能描述  : 处理USIMM模块上报的卡状态信息,判断电话本激活状态，并进入下一步初始化
输入参数  : pstMsg:USIMM模块上报的消息
输出参数  : gstPBInitState
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_InitPBStatusProc(PBMsgBlock *pstMsg)
{

    USIMM_CARDSTATUS_IND_STRU *pstPBMsg;

    pstPBMsg = (USIMM_CARDSTATUS_IND_STRU *)pstMsg;

    if (USIMM_CARDSTATUS_IND != pstPBMsg->ulMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)PB_WARNING_LOG("SI_PB_InitPBStatusProc:Wrong Msg!");
        /*lint +e534*/

        return;
    }

    if (VOS_TRUE == USIMM_VsimIsActive())    /*vSIM功能打开*/
    {
        PB_WARNING_LOG("SI_PB_InitPBStatusProc: The vSIM is Open");

        return;
    }

    SI_PB_ClearPBContent(SI_CLEARXDN);

    SI_PB_ClearSPBContent(SI_CLEARALL);

    /*卡服务不可用*/
    if (( USIMM_CARD_SERVIC_AVAILABLE != pstPBMsg->stUsimSimInfo.enCardService)
        &&( USIMM_CARD_SERVIC_AVAILABLE != pstPBMsg->stCsimUimInfo.enCardService))
    {
        PB_ERROR_LOG("SI_PB_InitPBStatusProc:Card Servic Unavaliable");

        SI_PB_InitStatusInd(USIMM_PB_IDLE);

        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;
    }
    else
    {
        PB_INFO_LOG("SI_PB_InitPBStatusProc:PB Init Begin");

        SI_PB_InitStatusInd(USIMM_PB_INITIALING);

        SI_PB_InitGlobeVariable();

        gstPBInitState.enReqStatus = PB_REQ_NOT_SEND;

        gstPBInitState.enPBInitState = SI_PB_INIT_STATUS_OK;
    }

    /* 保存卡状态 */
    gstPBInitState.enCardType = pstPBMsg->stUsimSimInfo.enCardType;

    return;
}
/*****************************************************************************
函 数 名  : SI_PB_InitEFpbrProc
功能描述  : 解析EFPBR文件，获取ADN、UID等文件的FID信息
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  : gstPBInitState
返 回 值  :
调用函数  : SI_PB_InitXDNSpace
            SI_PB_DecodeEFPBR
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_InitEFpbrProc(PBMsgBlock *pstMsg)
{
    USIMM_READFILE_CNF_STRU     *pstPBMsg;
    VOS_UINT32                  ulResult;
    VOS_UINT32                  ulPbrTotalNum;
    VOS_UINT16                  usEFID;

    pstPBMsg = (USIMM_READFILE_CNF_STRU *)(pstMsg);

    SI_PB_GetEFIDFromPath(&pstPBMsg->stFilePath, &usEFID);

    /*回复的内容非当前所期望，则初始化步骤出错*/
    if ((USIMM_READFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
        ||(EFPBR != usEFID)||(VOS_OK != pstPBMsg->stCmdResult.ulResult))
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_STATUS_OK;

        gstPBCtrlInfo.ulADNFileNum = 0;
        gstPBCtrlInfo.usEXT1FileID = 0xFFFF;
        gucPBCStatus = VOS_FALSE;

        /*lint -e534*/
        (VOS_VOID)LogPrint1("\r\nSI_PB_InitEFpbrProc:Response Error 0x%x\r\n", (VOS_INT)usEFID);
        /*lint +e534*/

        return;
    }

    ulPbrTotalNum =  pstPBMsg->ucTotalNum;

    if(0 != g_ulPbrRecordNum)
    {
       ulPbrTotalNum = g_ulPbrRecordNum;
       g_ulPbrRecordNum = 0;
    }

    /*解析EFPBR内容*/
    ulResult = SI_PB_DecodeEFPBR((VOS_UINT8)ulPbrTotalNum,
                                 (VOS_UINT8)pstPBMsg->usEfLen, pstPBMsg->aucEf);

    /*获取EFPBR文件内容失败，则跳过ADN初始化，进入FDN空间的初始化*/
    if ( VOS_OK != ulResult )
    {
        PB_ERROR_LOG("SI_PB_InitEFpbrProc:Decode EFPBR Content Failed");

        return;
    }

    /*当前正常处理USIMM回复*/
    gstPBInitState.enPBInitState = SI_PB_INIT_STATUS_OK;

    return;
}
/*****************************************************************************
函 数 名  : SI_PB_AllocPBSpace
功能描述  : 为电话本分配内存，并设置默认值
输入参数  :
输出参数  :

返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年9月5日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_AllocPBSpace(VOS_UINT8 **ppPBContent,VOS_UINT32 ulPBSize,VOS_CHAR cDefaultVal)
{
    *ppPBContent = (VOS_UINT8 *)PB_MALLOC(ulPBSize);

    if (VOS_NULL_PTR == *ppPBContent)
    {
        PB_ERROR_LOG("SI_PB_AllocPBSpace:MemAlloc Failed");

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(*ppPBContent, cDefaultVal, ulPBSize);
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_CheckXDNPara
功能描述  : 检查USIMM模块回复消息的参数
输入参数  : pstPBMsg:USIMM模块回复的消息
输出参数  : 无

返 回 值  : 无

修订记录  :
1.  日    期   : 2011年7月1日
    作    者   : j00168360
    修改内容   : Creat[DTS2011070102597]，SIM卡FDN功能开启，ADN文件可读可更新时电话本无法操作

*****************************************************************************/
VOS_UINT32 SI_PB_CheckXDNPara(USIMM_QUERYFILE_CNF_STRU *pstPBMsg)
{
    VOS_UINT16                          usEFID;

    SI_PB_GetEFIDFromPath(&pstPBMsg->stFilePath, &usEFID);

    if ((USIMM_QUERYFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    ||((gstPBInitState.ausFileId[gulPBFileCnt]!= usEFID)))
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint1("\r\nSI_PB_CheckXDNPara:Response Error 0x%x\r\n", (VOS_INT)usEFID);
        /*lint +e534*/

        return VOS_ERR;
    }

    if(VOS_OK != pstPBMsg->stCmdResult.ulResult)
    {
        /*设置处理状态为USIMM回复错误*/
        gstPBInitState.enPBInitState = SI_PB_INIT_USIMPBCNF_ERR;

        if (EFBDN == usEFID)
        {
            PB_NORMAL_LOG("SI_PB_CheckXDNPara:EFBDN Not Exist");
        }
        else
        {
            PB_ERROR_LOG("SI_PB_CheckXDNPara:Intial Step Error");
        }

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_CardStatusInd
功能描述  : 上报卡状态
输入参数  : null
输出参数  : null

返 回 值  :

修订记录  :
1.  日    期   : 2012年06月9日
    作    者   : j00168360
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_CardStatusInd(VOS_VOID)
{
    USIMM_CARDSTATUS_IND_STRU          *pUsimMsg;
    USIMM_CARD_SERVIC_ENUM_UINT32       enService = USIMM_CARD_SERVIC_BUTT;

    pUsimMsg = (USIMM_CARDSTATUS_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_CARDSTATUS_IND_STRU)-VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pUsimMsg )
    {
        /*lint -e534*/
        vos_printf("SI_PB_CardStatusInd: VOS_AllocMsg is Failed\r\n");
        /*lint +e534*/

        return;
    }

    /*lint -e534*/
    USIMM_GetCardType(gstPBInitState.enCardType, &enService);
    /*lint +e534*/

    pUsimMsg->ulMsgName                     = USIMM_CARDSTATUS_IND;    /* 设置消息名称 */
    pUsimMsg->stUsimSimInfo.enCardType      = gstPBInitState.enCardType;
    pUsimMsg->stUsimSimInfo.enCardService   = enService;
    pUsimMsg->stCsimUimInfo.enCardType      = USIMM_CARD_NOCARD;
    pUsimMsg->stCsimUimInfo.enCardService   = USIMM_CARD_SERVIC_ABSENT;
    pUsimMsg->stIsimInfo.enCardType         = USIMM_CARD_NOCARD;
    pUsimMsg->stIsimInfo.enCardService      = USIMM_CARD_SERVIC_ABSENT;
    pUsimMsg->ulReceiverPid                 = MAPS_PB_PID;

    (VOS_VOID)VOS_SendMsg(pUsimMsg->ulSenderPid, pUsimMsg);

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_XDNSpaceCheck
功能描述  : 检查XDN空间
输入参数  : ulPBType:电话本类型
            pstPBMsg:
输出参数  : null

返 回 值  :

修订记录  :
1.  日    期   : 2012年06月9日
    作    者   : j00168360
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_XDNSpaceCheck(VOS_UINT32 ulPBType, USIMM_QUERYFILE_CNF_STRU *pstPBMsg)
{
    if(PB_ADN_CONTENT == ulPBType)
    {
       gstPBCtrlInfo.astADNInfo[gulPBFileCnt].ucRecordNum = pstPBMsg->ucRecordNum;

       gstPBCtrlInfo.astADNInfo[gulPBFileCnt].ucRecordLen = pstPBMsg->ucRecordLen;

       if((gastPBContent[ulPBType].ucRecordLen*gastPBContent[ulPBType].usTotalNum < SI_PB_XDN_SPACE)
       &&(gastPBContent[ulPBType].usTotalNum <= SI_PB_XDN_SUPPORT_NUM))
       {
          g_ulPbrRecordNum++;
       }
       else
       {
          SI_PB_ReleaseAll();

          /* 发送重新初始化信息 */
          SI_PB_CardStatusInd();

          return VOS_ERR;
       }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : SI_PB_InitXDNSpaceMsgProc
功能描述  : 初始化ADN、FDN、BDN和MSISDN号码的空间
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  : gastPBContent
            gstPBInitState
            gstPBCtrlInfo

返 回 值  :
调用函数  : SI_PB_InitSYNCH //Huashan
            SI_PB_InitXDNContent //Balong
            SI_PB_InitXDNSpace
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_InitXDNSpaceMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_QUERYFILE_CNF_STRU  *pstPBMsg;
    VOS_UINT32                ulPBType = 0;
    VOS_UINT32                ulNextPBType = 0;
    VOS_UINT32                ulResult;

    pstPBMsg = (USIMM_QUERYFILE_CNF_STRU *)pstMsg;

    ulResult = SI_PB_CheckXDNPara(pstPBMsg);

    if( VOS_OK != ulResult )
    {
        PB_ERROR_LOG("SI_PB_InitXDNSpaceMsgProc:check XDN para error");

        return;
    }

    /*获取当前初始化文件对应的电话本类型*/
    ulResult = SI_PB_GetXDNPBType(&ulPBType, gstPBInitState.ausFileId[gulPBFileCnt]);

    if( VOS_OK != ulResult )
    {
        /*设置处理状态为电话本类型未知，则准备进入下一个文件继续初始化*/
        gstPBInitState.enPBInitState = SI_PB_INIT_PBTYPE_UNKOWN;

        PB_ERROR_LOG("SI_PB_InitXDNSpaceMsgProc:Unspecified PB Type");

        return;
    }

    if((USIMM_EFSTATUS_DEACTIVE == pstPBMsg->enFileStatus) && (USIMM_EF_RW_NOT == pstPBMsg->enFileRWFlag))
    {
        /*把对应电话本的激活状态设置为未激活*/
        gastPBContent[ulPBType].enActiveStatus = USIMM_EFSTATUS_DEACTIVE;

        /*设置处理状态为文件未激活，准备跳入下个电话本继续初始化*/
        gstPBInitState.enPBInitState = SI_PB_INIT_FILE_DECATIVE;

        PB_NORMAL_LOG("SI_PB_InitXDNSpaceMsgProc:The File is Decative");

        return;
    }

    /*根据USIMM回复消息，记录目前正在初始化的电话本的相关信息*/
    gastPBContent[ulPBType].ucRecordLen = pstPBMsg->ucRecordLen;

    gastPBContent[ulPBType].usTotalNum += pstPBMsg->ucRecordNum;

    gastPBContent[ulPBType].ucNameLen   = pstPBMsg->ucRecordLen - SI_PB_EXCEPT_NAME;

    /*如果是ADN电话本，需要记录每个ADN文件的记录数和记录长度*/
    if(VOS_OK != SI_PB_XDNSpaceCheck(ulPBType,pstPBMsg))
    {
       return;
    }

    /*获取下一个需要初始化的电话本*/
    /*lint -e534*/
    SI_PB_GetXDNPBType(&ulNextPBType, gstPBInitState.ausFileId[gulPBFileCnt+1]);
    /*lint +e534*/

    /*ADN文件空间已初始化完毕，剩下的电话本都是一个电话本对应一个文件*/
    if ( ((PB_ADN_CONTENT == ulPBType)&&(PB_ADN_CONTENT != ulNextPBType))
         || (PB_ADN_CONTENT != ulPBType) )
    {
        ulResult = gastPBContent[ulPBType].ucRecordLen*gastPBContent[ulPBType].usTotalNum;

        gastPBContent[ulPBType].ucNumberLen = SI_PB_NUM_LEN;

        /*巴龙产品为所有电话本分配缓存空间,ADN文件不能超过60K(1000条记录)*/
        if ( 0 < ulResult )
        {
            if( ulResult <= SI_PB_XDN_SPACE )
            {
                gastPBContent[ulPBType].pContent = (VOS_UINT8*)PB_MALLOC(ulResult);
            }
            else
            {
                PB_ERROR_LOG("SI_PB_InitADNSpaceMsgProc:PB XDN Memory is Too Big To Support");
                gastPBContent[ulPBType].pContent = VOS_NULL_PTR;
            }

            if ( VOS_NULL_PTR == gastPBContent[ulPBType].pContent )
            {
                /*设置处理状态为分配内存失败*/
                gstPBInitState.enPBInitState = SI_PB_INIT_PBMALLOC_FAIL;

                PB_ERROR_LOG("SI_PB_InitADNSpaceMsgProc:MemAlloc Failed");

                return;
            }
            /*lint -e534*/
            VOS_MemSet(gastPBContent[ulPBType].pContent, (VOS_CHAR)0xFF, ulResult);
            /*lint +e534*/
        }

        /*不管缓存是否存在都为索引表分配空间，标志每条记录的使用情况*/
        if (0 < ulResult)
        {
            if ( VOS_OK != SI_PB_AllocPBSpace(&gastPBContent[ulPBType].pIndex,
                (gastPBContent[ulPBType].usTotalNum+7)/8,0x00))
            {
                /*设置处理状态为分配内存失败*/
                gstPBInitState.enPBInitState = SI_PB_INIT_PBMALLOC_FAIL;

                PB_ERROR_LOG("SI_PB_InitADNSpaceMsgProc:Index MemAlloc Failed");

                return;
            }
        }
    }

    /*设置处理状态为成功处理*/
    gstPBInitState.enPBInitState = SI_PB_INIT_STATUS_OK;

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitANRSpaceMsgProc
功能描述  : 初始化ANR号码的空间
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  : gastPBContent
            gstPBInitState
            gstPBCtrlInfo

返 回 值  :
调用函数  : SI_PB_InitSYNCH //Huashan
            SI_PB_InitXDNContent //Balong
            SI_PB_InitXDNSpace
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_InitANRSpaceMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_QUERYFILE_CNF_STRU    *pstPBMsg;
    VOS_UINT8                   ucXSuffix = 0; /*当前ANR文件在缓存中的x下标*/
    VOS_UINT8                   ucYSuffix = 0; /*当前ANR文件在缓存中的y下标*/
    VOS_UINT32                  ulTotalLen;
    VOS_UINT16                  usEFID;

    pstPBMsg = (USIMM_QUERYFILE_CNF_STRU *)pstMsg;

    if (USIMM_QUERYFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitANRSpaceMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    SI_PB_GetEFIDFromPath(&pstPBMsg->stFilePath, &usEFID);

    if(VOS_OK != SI_PB_GetANRSuffix(&ucXSuffix,&ucYSuffix, usEFID))
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_PBTYPE_UNKOWN;

        PB_ERROR_LOG("SI_PB_InitANRSpaceMsgProc:PB Type Error");

        return;
    }

    /*如果错误，则初始化状态出错*/
    if(VOS_OK != pstPBMsg->stCmdResult.ulResult)
    {
        /*设置处理状态为USIMM回复错误*/
        gstPBInitState.enPBInitState = SI_PB_INIT_USIMSPBCNF_ERR;

        /*lint -e534*/
        VOS_MemSet(&gastANRContent[ucYSuffix], 0, sizeof(SI_ANR_CONTENT_STRU));
        /*lint +e534*/

        PB_ERROR_LOG("SI_PB_InitANRSpaceMsgProc:Intial Step Error");

        return;
    }

    /*根据USIMM回复消息，记录目前正在初始化的电话本的相关信息*/
    gastANRContent[ucYSuffix].ucRecordLen = pstPBMsg->ucRecordLen;

    gastANRContent[ucYSuffix].usTotalNum += pstPBMsg->ucRecordNum;

    gastANRContent[ucYSuffix].ucNumberLen = SI_PB_NUM_LEN;

    /*需要记录每个ANR文件的记录数和记录长度*/
    gstPBCtrlInfo.astANRInfo[ucXSuffix][ucYSuffix].ucRecordNum = pstPBMsg->ucRecordNum;

    gstPBCtrlInfo.astANRInfo[ucXSuffix][ucYSuffix].ucRecordLen = pstPBMsg->ucRecordLen;

    /*判断此组ANR是否已经初始化完毕*/
    if(VOS_OK == SI_PB_GheckANRLast(ucXSuffix,ucYSuffix))
    {
        ulTotalLen = gastANRContent[ucYSuffix].usTotalNum*gastANRContent[ucYSuffix].ucRecordLen;

        /*ANR按3组，每条记录17字节，1000条记录申请51K内存*/
        if(ulTotalLen <= 51000)
        {
            gastANRContent[ucYSuffix].pContent = (VOS_UINT8*)PB_MALLOC(ulTotalLen);
        }
        else
        {
            PB_ERROR_LOG("SI_PB_InitANRSpaceMsgProc:PB ANR Memery is Too Big To Support");
            gastANRContent[ucYSuffix].pContent = VOS_NULL_PTR;
        }

        if ( VOS_NULL_PTR == gastANRContent[ucYSuffix].pContent )
        {
            /*设置处理状态为分配内存失败*/
            gstPBInitState.enPBInitState = SI_PB_INIT_SPBMALLOC_FAIL;

            PB_ERROR_LOG("SI_PB_InitANRSpaceMsgProc:MemAlloc Failed");

            return;
        }

        /*lint -e534*/
        VOS_MemSet(gastANRContent[ucYSuffix].pContent, (VOS_CHAR)0xFF, ulTotalLen);
        /*lint +e534*/
    }

    /*设置处理状态为成功处理*/
    gstPBInitState.enPBInitState = SI_PB_INIT_STATUS_OK;

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitEMLSpaceMsgProc
功能描述  : 初始化Email的空间
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  : gastPBContent
            gstPBInitState
            gstPBCtrlInfo

返 回 值  :
调用函数  : SI_PB_InitSYNCH //Huashan
            SI_PB_InitXDNContent //Balong
            SI_PB_InitXDNSpace
被调函数  :
修订记录  :
1.  日    期   : 2009年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_InitEMLSpaceMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_QUERYFILE_CNF_STRU    *pstPBMsg;
    VOS_UINT32                  ulSuffix; /*当前ANR文件在缓存中的下标*/
    VOS_UINT32                  ulTotalLen;

    ulSuffix = gulPBFileCnt;/*ANR文件控制信息数组的X坐标对应ADN文件计数器*/

    pstPBMsg = (USIMM_QUERYFILE_CNF_STRU *)pstMsg;

    if (USIMM_QUERYFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitEMLSpaceMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    /*如果错误，则初始化状态出错*/
    if(VOS_OK != pstPBMsg->stCmdResult.ulResult)
    {
        /*设置处理状态为USIMM回复错误，可能是因为文件根本就不存在。这种情况不用按出错处理，跳到下一步去*/
        gstPBInitState.enPBInitState = SI_PB_INIT_STATUS_OK;

        gstPBCtrlInfo.ulEMLFileNum = 0;

        PB_ERROR_LOG("SI_PB_InitEMLSpaceMsgProc:Init EML Space Error");

        return;
    }

    /*根据USIMM回复消息，记录目前正在初始化的电话本的相关信息*/
    gstEMLContent.ucRecordLen = pstPBMsg->ucRecordLen;

    gstEMLContent.usTotalNum += pstPBMsg->ucRecordNum;

    gstEMLContent.ucDataLen = (PB_FILE_TYPE1 == gstPBCtrlInfo.astEMLInfo[ulSuffix].enEMLType)?
                               pstPBMsg->ucRecordLen:(pstPBMsg->ucRecordLen-2);

    /*需要记录每个ANR文件的记录数和记录长度*/
    gstPBCtrlInfo.astEMLInfo[ulSuffix].ucRecordNum = pstPBMsg->ucRecordNum;

    gstPBCtrlInfo.astEMLInfo[ulSuffix].ucRecordLen = pstPBMsg->ucRecordLen;

    /*判断是否所有Email空间已经初始化完毕*/
    if((ulSuffix+1) == gstPBCtrlInfo.ulEMLFileNum)
    {
        ulTotalLen = gstEMLContent.usTotalNum*gstEMLContent.ucRecordLen;

        /*EMAIL按1000条记录64字节分配内存*/
        if(ulTotalLen <= 64000)
        {
            gstEMLContent.pContent = (VOS_UINT8 *)PB_MALLOC(ulTotalLen);
        }
        else
        {
            PB_ERROR_LOG("SI_PB_InitEMLSpaceMsgProc:PB Email Memery is Too Big To Support");
            gstEMLContent.pContent = VOS_NULL_PTR;
        }

        if ( VOS_NULL_PTR == gstEMLContent.pContent )
        {
            /*设置处理状态为分配内存失败*/
            gstPBInitState.enPBInitState = SI_PB_INIT_SPBMALLOC_FAIL;

            PB_ERROR_LOG("SI_PB_InitEMLSpaceMsgProc:MemAlloc Failed");

            return;
        }

        /*lint -e534*/
        VOS_MemSet(gstEMLContent.pContent, (VOS_CHAR)0xFF, ulTotalLen);
        /*lint +e534*/
    }

    /*设置处理状态为成功处理*/
    gstPBInitState.enPBInitState = SI_PB_INIT_STATUS_OK;

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitIAPSpaceMsgProc
功能描述  : 初始化IAP的空间
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  : gastPBContent
            gstPBInitState
            gstPBCtrlInfo

返 回 值  :
调用函数  : SI_PB_InitSYNCH //Huashan
            SI_PB_InitXDNContent //Balong
            SI_PB_InitXDNSpace
被调函数  :
修订记录  :
1.  日    期   : 2009年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_InitIAPSpaceMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_QUERYFILE_CNF_STRU  *pstPBMsg;
    VOS_UINT32                ulSuffix; /*当前IAP文件在缓存中的下标*/
    VOS_UINT32                ulTotalLen;

    ulSuffix = gulPBFileCnt;/*IAP文件控制信息数组的X坐标对应ADN文件计数器*/

    pstPBMsg = (USIMM_QUERYFILE_CNF_STRU *)pstMsg;

    if (USIMM_QUERYFILE_CNF != pstPBMsg->stCmdResult.enMsgName  )
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitIAPSpaceMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    /*如果错误，则初始化状态出错*/
    if(VOS_OK != pstPBMsg->stCmdResult.ulResult)
    {
        /*设置处理状态为USIMM回复错误*/
        gstPBInitState.enPBInitState = SI_PB_INIT_USIMSPBCNF_ERR;

        PB_ERROR_LOG("SI_PB_InitEMLSpaceMsgProc:PB Type Error");

        return;
    }

    /*根据USIMM回复消息，记录目前正在初始化的电话本的相关信息*/
    gstIAPContent.ucRecordLen = pstPBMsg->ucRecordLen;

    gstIAPContent.usTotalNum += pstPBMsg->ucRecordNum;

    /*需要记录每个IAP文件的记录数和记录长度*/
    gstPBCtrlInfo.astIAPInfo[ulSuffix].ucRecordNum = pstPBMsg->ucRecordNum;

    gstPBCtrlInfo.astIAPInfo[ulSuffix].ucRecordLen = pstPBMsg->ucRecordLen;

    /*判断是否所有IAP空间已经初始化完毕*/
    if((ulSuffix+1) == gstPBCtrlInfo.ulIAPFileNum)
    {
        ulTotalLen = gstIAPContent.usTotalNum*gstIAPContent.ucRecordLen;

        gstIAPContent.pIAPContent = (VOS_UINT8 *)PB_MALLOC(ulTotalLen);

        if ( VOS_NULL_PTR == gstIAPContent.pIAPContent )
        {
            /*设置处理状态为分配内存失败*/
            gstPBInitState.enPBInitState = SI_PB_INIT_SPBMALLOC_FAIL;

            PB_ERROR_LOG("SI_PB_InitEMLSpaceMsgProc:MemAlloc Failed");

            return;
        }

        /*lint -e534*/
        VOS_MemSet(gstIAPContent.pIAPContent, (VOS_CHAR)0xFF, ulTotalLen);
        /*lint +e534*/
    }

    /*设置处理状态为成功处理*/
    gstPBInitState.enPBInitState = SI_PB_INIT_STATUS_OK;

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitEXTSpaceMsgProc
功能描述  : 初始化ADN、FDN、BDN和MSISDN号码的EXT空间
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  : gastPBContent
            gstPBInitState
            gstPBCtrlInfo

返 回 值  :
调用函数  : SI_PB_InitSYNCH //Huashan
            SI_PB_InitXDNContent //Balong
            SI_PB_InitXDNSpace
被调函数  :
修订记录  :
1.  日    期   : 2009年5月8日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_InitEXTSpaceMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_QUERYFILE_CNF_STRU    *pstPBMsg;
    VOS_UINT32                  ulFileSize;
    VOS_UINT32                  i;
    VOS_UINT16                  usEFID;

    pstPBMsg = (USIMM_QUERYFILE_CNF_STRU *)pstMsg;

    if (USIMM_QUERYFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitEXTSpaceMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    SI_PB_GetEFIDFromPath(&pstPBMsg->stFilePath, &usEFID);

    if(VOS_OK != pstPBMsg->stCmdResult.ulResult)
    {
        /*设置处理状态为电话本类型未知，则准备进入下一个文件继续初始化*/
        gstPBInitState.enPBInitState = SI_PB_INIT_PBTYPE_UNKOWN;
        gastEXTContent[gulPBFileCnt+1].pExtContent = VOS_NULL_PTR;

        PB_ERROR1_LOG("SI_PB_InitEXTSpaceMsgProc:EXT File Not Exist.", usEFID);

        return;
    }

    ulFileSize = (pstPBMsg->ucRecordNum) * (pstPBMsg->ucRecordLen);

    gastEXTContent[gulPBFileCnt+1].pExtContent = (VOS_UINT8 *)PB_MALLOC(ulFileSize);

    if ( VOS_NULL_PTR == gastEXTContent[gulPBFileCnt+1].pExtContent )
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_PBMALLOC_FAIL;
        gastEXTContent[gulPBFileCnt+1].usExtFlag   = SI_PB_FILE_NOT_EXIST;

        PB_ERROR_LOG("SI_PB_InitEXTSpaceMsgProc:MemAlloc Failed");

        return;
    }

    /* EXT文件的记录并不是所有都会初始化，所以要将EXT文件的缓存空间全部都设置为FF */
    /*lint -e534*/
    VOS_MemSet(gastEXTContent[gulPBFileCnt+1].pExtContent, (VOS_INT8)0xFF, ulFileSize);
    /*lint +e534*/

    gastEXTContent[gulPBFileCnt+1].usExtFlag     = SI_PB_FILE_EXIST;
    gastEXTContent[gulPBFileCnt+1].usExtTotalNum = pstPBMsg->ucRecordNum;

    gastPBContent[gulPBFileCnt+1].ucNumberLen    += SI_PB_EXT_NUM_LEN;

    /*所有ANR文件支持扩展号码*/
    if( usEFID == gstPBCtrlInfo.usEXT1FileID )
    {
        for(i = 0; i < SI_PB_ANRMAX; i++)
        {
            gastANRContent[i].ucNumberLen +=SI_PB_NUM_LEN;
        }
    }

    /* 对于SIM卡，ADN和MSISDN的EXT文件对应于同一文件*/
    if( EFEXT1 == usEFID )
    {
        gastEXTContent[PB_MSISDN_CONTENT].usExtFlag     = SI_PB_FILE_EXIST;
        gastEXTContent[PB_MSISDN_CONTENT].usExtTotalNum = pstPBMsg->ucRecordNum;
        gastEXTContent[PB_MSISDN_CONTENT].pExtContent   = gastEXTContent[PB_ADN_CONTENT].pExtContent;

        gastPBContent[PB_MSISDN_CONTENT].ucNumberLen    = SI_PB_EXT_NUM_LEN;
    }

    /*设置处理状态为成功处理*/
    gstPBInitState.enPBInitState = SI_PB_INIT_STATUS_OK;

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitIAPContentMsgProc
功能描述  : 根据IAP内容，初始化ADN和Type2类型Email记录号的对应关系
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  : gastPBContent
            gstPBInitState
            gstPBCtrlInfo
            gulPBRecordCnt
返 回 值  :
调用函数  : SI_PB_CountADNIndex
            VOS_MemCpy
            SI_PB_CheckContentValidity
            SI_PB_InitXDNContent
            VOS_MemFree
被调函数  :
修订记录  :
1.  日    期   : 2008年06月05日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_InitIAPContentMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_READFILE_CNF_STRU     *pstPBMsg;
    VOS_UINT32                   ulOffset;
    VOS_UINT16                   usRecordNum;
    VOS_UINT8                    ucTotalRecordNum;
    VOS_UINT8                    i;

    pstPBMsg = (USIMM_READFILE_CNF_STRU *)pstMsg;

    if (USIMM_READFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitIAPContentMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    /*如果回复的FID不是当前正在初始化的电话本的FID，则初始化步骤出错*/
    if ( VOS_OK != pstPBMsg->stCmdResult.ulResult )
    {
        PB_ERROR_LOG("SI_PB_InitIAPContentMsgProc:Get File Content Failed");

        if ( VOS_NULL_PTR != gstIAPContent.pIAPContent)
        {
            /*lint -e534*/
            PB_FREE( gstIAPContent.pIAPContent);
            /*lint +e534*/

            gstIAPContent.pIAPContent = VOS_NULL_PTR;
        }

        /*设置处理状态为USIMM回复错误*/
        gstPBInitState.enPBInitState = SI_PB_INIT_USIMSPBCNF_ERR;

        return;
    }

    if ( VOS_NULL_PTR == gstIAPContent.pIAPContent )
    {
        /*设置处理状态为分配内存失败*/
        gstPBInitState.enPBInitState = SI_PB_INIT_PBMALLOC_FAIL;

        PB_ERROR_LOG("SI_PB_InitIAPContentMsgProc:Memory is Null");

        return;
    }

    /* 每个IAP文件的记录数可能不一致，计算偏移量时要累加 */
    usRecordNum = pstPBMsg->ucRecordNum;

    for (i = 0; i < gulPBFileCnt; i++)
    {
        usRecordNum += gstPBCtrlInfo.astIAPInfo[i].ucRecordNum;
    }

    ulOffset = (usRecordNum - 1) * pstPBMsg->usEfLen;

    /*lint -e534*/
    VOS_MemCpy(gstIAPContent.pIAPContent + ulOffset,\
                                        pstPBMsg->aucEf, pstPBMsg->usEfLen);
    /*lint +e534*/

    ucTotalRecordNum = gstPBCtrlInfo.astIAPInfo[gulPBFileCnt].ucRecordNum;

    if (++gulPBRecordCnt > ucTotalRecordNum)/*当前初始化文件的记录已全部初始化完毕*/
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_EXCEED;
    }
    else
    {
        /*设置处理状态为还有未初始化的记录*/
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_REMAIN;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitXDNContentMsgProc
功能描述  : 初始化XDN电话本缓存，完成后进入初始化下一步
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  : gastPBContent
            gstPBInitState
            gstPBCtrlInfo
            gulPBRecordCnt
返 回 值  :
调用函数  : SI_PB_CountADNIndex
            VOS_MemCpy
            SI_PB_CheckContentValidity
            SI_PB_InitXDNContent
            VOS_MemFree
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_InitXDNContentMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_READFILE_CNF_STRU            *pstPBMsg;
    VOS_UINT32                          ulPBType     = 0;
    VOS_UINT32                          ulNextPBType = 0;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulExtInfoNum;
    VOS_UINT16                          usExtRecIdOffset;
    VOS_UINT16                          usIndex;/*记录ADN电话本记录号对应的缓存索引号*/
    VOS_UINT8                           ucRecordNum;
    VOS_UINT16                          usEFID;

    pstPBMsg = (USIMM_READFILE_CNF_STRU *)pstMsg;

    if (USIMM_READFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitXDNContentMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    SI_PB_GetEFIDFromPath(&pstPBMsg->stFilePath, &usEFID);

    /*获取当前初始化的文件对应的电话本*/
    ulResult = SI_PB_GetXDNPBType(&ulPBType, gstPBInitState.ausFileId[gulPBFileCnt]);

    if ( VOS_OK != ulResult )
    {
        /*设置处理状态为电话本类型未知*/
        gstPBInitState.enPBInitState = SI_PB_INIT_PBTYPE_UNKOWN;

        PB_ERROR_LOG("SI_PB_InitXDNSpaceMsgProc:Unspecified PB Type");

        return;
    }

    /* SIM卡回复出错，跳转到下个电话本处理 */
    if  (VOS_OK != pstPBMsg->stCmdResult.ulResult)
    {
        PB_WARNING_LOG("SI_PB_InitXDNContentMsgProc:Intial File Error");

        /*设置处理状态为USIMM回复错误*/
        gstPBInitState.enPBInitState = SI_PB_INIT_USIMPBCNF_ERR;

        return;
    }

    /*获取回复的记录内容在缓存中的位置，ADN和其他电话本分别处理*/
    if ( PB_ADN_CONTENT == ulPBType )
    {
        /*获取当前的文件和记录号对应的缓存索引号*/
        if (VOS_OK != SI_PB_CountADNIndex(usEFID, pstPBMsg->ucRecordNum, &usIndex))
        {
            /*设置处理状态为当前文件所有记录处理完毕*/
            gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_EXCEED;

            PB_ERROR_LOG("SI_PB_InitXDNContentMsgProc:Get Record Index Failed");

            return;
        }

        ucRecordNum = gstPBCtrlInfo.astADNInfo[gulPBFileCnt].ucRecordNum;
    }
    else
    {
        usIndex = (VOS_UINT16)gulPBRecordCnt;

        ucRecordNum = (VOS_UINT8)gastPBContent[ulPBType].usTotalNum;
    }

    ulOffset = (usIndex - 1)*gastPBContent[ulPBType].ucRecordLen;

    if ( VOS_NULL_PTR == gastPBContent[ulPBType].pContent )
    {
        /* 设置处理状态为分配内存失败，下一步继续使用SEARCH的方式进行初始化 */
        gstPBInitState.enPBInitState = SI_PB_INIT_PBMALLOC_FAIL;
        gstPBInitState.enPBInitStep  = PB_INIT_XDN_SEARCH;

        return;
    }

    /*复制XDN电话本的记录到缓存*/
    /*lint -e534*/
    VOS_MemCpy(gastPBContent[ulPBType].pContent + ulOffset,
               pstPBMsg->aucEf, gastPBContent[ulPBType].ucRecordLen);
    /*lint +e534*/

    /*检查此记录是否为有效记录*/
    if ( VOS_OK == SI_PB_CheckContentValidity(&gastPBContent[ulPBType], pstPBMsg->aucEf))
    {
        gastPBContent[ulPBType].usUsedNum++;

        if (SI_PB_CONTENT_INVALID == SI_PB_GetBitFromBuf(gastPBContent[ulPBType].pIndex,
                                                        usIndex))
        {
            /*如果之前姓名和号码字段为空，但当前解析出ADN不为空，则该条复合记录置为非空*/
            if(PB_ADN_CONTENT == ulPBType)
            {
                gstPBCtrlInfo.ulTotalUsed++;
            }

            SI_PB_SetBitToBuf(gastPBContent[ulPBType].pIndex,usIndex,SI_PB_CONTENT_VALID);
        }
    }

    usExtRecIdOffset = ((EFBDN == usEFID)?\
                        (pstPBMsg->usEfLen - 2):(pstPBMsg->usEfLen - 1));

    ulExtInfoNum = gastPBContent[ulPBType].ulExtInfoNum;

    /* 检查是否有EXT文件要读取，XDN文件中扩展记录的记录号不能为0或0xFF */
    if( ( 0xFF != pstPBMsg->aucEf[usExtRecIdOffset] )
        && (0 != pstPBMsg->aucEf[usExtRecIdOffset])
        && (SI_PB_FILE_NOT_EXIST != gastEXTContent[ulExtInfoNum].usExtFlag) )
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_EXT_RECORD;
        gstPBInitState.enPBInitStep  = PB_INIT_EXT_CONTENT;
        gulExtRecord                 = pstPBMsg->aucEf[usExtRecIdOffset];
        return;
    }

    if ( ++gulPBRecordCnt > ucRecordNum )/*当前初始化文件的记录已全部初始化完毕*/
    {
        /*获取下一个需要缓存内容的电话本*/
        /*lint -e534*/
        SI_PB_GetXDNPBType(&ulNextPBType, gstPBInitState.ausFileId[gulPBFileCnt+1]);
        /*lint +e534*/

        /*lint -e774 修改人:祝锂; 检视人:徐铖 51137;原因:保护用户错误输入 */
        /*如果是最后一个ADN文件，或非ADN电话本<一个文件对应一个电话本>*/
        if ( (PB_ADN_CONTENT != ulPBType) ||
             ((PB_ADN_CONTENT == ulPBType)&&(PB_ADN_CONTENT != ulNextPBType)))
        {
            /*设置当前电话本初始化状态为已初始化*/
            gastPBContent[ulPBType].enInitialState = PB_INITIALISED;
        }
        /*lint +e774 修改人:祝锂;检视人:徐铖 51137; */

        /*设置处理状态为当前文件的所有记录已初始化完毕*/
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_EXCEED;
    }
    else
    {
        /*设置处理状态为还有未初始化的记录*/
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_REMAIN;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitExtContentMsgProc
功能描述  : 初始化EXT内容，完成后进入初始化下一步
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年5月6日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_InitEXTContentMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_READFILE_CNF_STRU      *pstPBMsg;
    VOS_UINT32                   ulOffset;
    VOS_UINT32                   ulPBType;
    VOS_UINT32                   ulNextPBType;
    VOS_UINT32                   ulResult1;
    VOS_UINT32                   ulResult2;
    VOS_UINT8                    ucRecordNum;
    VOS_UINT32                   ulExtInfoNum;

    pstPBMsg = (USIMM_READFILE_CNF_STRU *)pstMsg;

    if (USIMM_READFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitEXTContentMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    /*获取当前初始化的文件对应的电话本文件类型*/
    if ( VOS_OK != SI_PB_GetXDNPBType(&ulPBType, gstPBInitState.ausFileId[gulPBFileCnt]) )
    {
        /*设置处理状态为电话本类型未知*/
        gstPBInitState.enPBInitState = SI_PB_INIT_PBTYPE_UNKOWN;

         /*AT2D15844*/
        gstPBInitState.enPBInitStep = PB_INIT_XDN_CONTENT;

        PB_ERROR_LOG("SI_PB_InitXDNSpaceMsgProc:Unspecified PB Type");

        return;
    }

    /*获取回复的记录内容在缓存中的位置，ADN和其他电话本的EXT文件分别处理*/
    if ( PB_ADN_CONTENT == ulPBType )
    {
        ucRecordNum = gstPBCtrlInfo.astADNInfo[gulPBFileCnt].ucRecordNum;
    }
    else
    {
        ucRecordNum = (VOS_UINT8)gastPBContent[ulPBType].usTotalNum;
    }

    ulResult1 = (gstPBSearchCtrlInfo.usReadOffset >= gstPBSearchCtrlInfo.usReadNum);    /* 当前SEARCH记录已全部初始化完成 */
    ulResult2 = (++gulPBRecordCnt > ucRecordNum);                                       /* 当前初始化文件的记录已全部初始化完毕 */

    /* 如果当前读取记录已经超过当前文件记录数需要切换到下一个文件 */
    if (ulResult1 || ulResult2)
    {
        /*获取下一个需要缓存内容的电话本*/
        /*lint -e534*/
        SI_PB_GetXDNPBType(&ulNextPBType, gstPBInitState.ausFileId[gulPBFileCnt+1]);
        /*lint +e534*/

        /*lint -e774 修改人:祝锂; 检视人:徐铖 51137;原因:保护用户错误输入 */

        /*如果是最后一个ADN文件，或非ADN电话本<一个文件对应一个电话本>*/
        if ( (PB_ADN_CONTENT != ulPBType) ||
             ((PB_ADN_CONTENT == ulPBType)&&(PB_ADN_CONTENT != ulNextPBType)))
        {
            /*设置当前电话本初始化状态为已初始化*/
            gastPBContent[ulPBType].enInitialState = PB_INITIALISED;
        }
        /*lint +e774 修改人:祝锂;检视人:徐铖 51137; */

        /*设置处理状态为当前文件的所有记录已初始化完毕*/
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_EXCEED;
    }
    else
    {
        /*设置处理状态为还有未初始化的记录*/
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_REMAIN;
    }

    /*下一步初始化文件为XDN文件*/
    /*gstPBInitState.enPBInitStep = PB_INIT_XDN_CONTENT;
 */

    /* 下一步初始化文件为XDN文件，根据查找状态来判断
    是使用逐条读取的方式还是用查找的方式来初始化 */
    if (PB_SEARCH_ENABLE  == gstPBInitState.enPBSearchState)
    {
        gstPBInitState.enPBInitStep = PB_INIT_XDN_CONTENT2;
    }
    else
    {
        gstPBInitState.enPBInitStep = PB_INIT_XDN_CONTENT;
    }

    if ( VOS_OK != pstPBMsg->stCmdResult.ulResult )
    {
        /* 如果在初始化EXT文件的过程中出错，如读取失败，不处理，继续XDN的初始化 */
        PB_WARNING_LOG("SI_PB_InitEXTContentMsgProc:Read File Content is Failed");

        return;
    }
    else
    {
        ulOffset = (gulExtRecord - 1)*SI_PB_EXT_LEN;

        /*复制EXT内容到缓存，如果记录为有效记录，已使用记录才加1*/
        ulExtInfoNum = gastPBContent[ulPBType].ulExtInfoNum;

        /*lint -e420 -e534 修改人: j00174725; 检视人: xucheng*/
        VOS_MemCpy(gastEXTContent[ulExtInfoNum].pExtContent + ulOffset, pstPBMsg->aucEf, SI_PB_EXT_LEN);
        /*lint +e420 +e534 修改人: j00174725; 检视人: xucheng*/

        if( 0 != *(pstPBMsg->aucEf+1))
        {
            gastEXTContent[ulExtInfoNum].usExtUsedNum++;
        }

        return;
    }
}

/*****************************************************************************
函 数 名  : SI_PB_InitIAPSearchMsgProc
功能描述  : 根据IAP查找结果处理函数
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年01月18日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_InitIAPSearchMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_SEARCHFILE_CNF_STRU       *pstPBMsg;
    VOS_UINT16                      usEFID;

    pstPBMsg = (USIMM_SEARCHFILE_CNF_STRU *)pstMsg;

    if (USIMM_SEARCHFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitIAPSearchMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    SI_PB_GetEFIDFromPath(&pstPBMsg->stFilePath, &usEFID);

    /* 查找的结果可以是OK也可以是NORECORD FOUND(无匹配记录)，其它回复结果都是错误的 */
    if ((USIMM_SW_NORECORD_FOUND == pstPBMsg->stCmdResult.ulResult)
        || (VOS_OK == pstPBMsg->stCmdResult.ulResult))
    {
        gstPBSearchCtrlInfo.usReadNum       = gstPBCtrlInfo.astIAPInfo[gulPBFileCnt].ucRecordNum - pstPBMsg->usDataLen;
        gstPBSearchCtrlInfo.usReadOffset    = 0;                        /* 读取查找匹配列表的偏移量从0开始 */
        gstPBSearchCtrlInfo.usEfId          = usEFID;
        gstPBInitState.enPBInitState        = SI_PB_INIT_SEARCH_OK;
        gstPBInitState.enPBInitStep         = PB_INIT_IAP_CONTENT2;

        SI_PB_SearchResultProc(gstPBSearchCtrlInfo.aucReadString,
                                pstPBMsg->aucData,
                                pstPBMsg->usDataLen,
                                gstPBCtrlInfo.astIAPInfo[gulPBFileCnt].ucRecordNum);

        /* 如果没有匹配的记录，将文件计数器加1，准备处理下一个文件 */
        if (0 == gstPBSearchCtrlInfo.usReadNum)
        {
            gulPBFileCnt++;
        }
    }
    /* 查找的文件不存在，设置匹配的记录数为零，继续下一文件的查找过程 */
    else if (USIMM_SW_NOFILE_FOUND == pstPBMsg->stCmdResult.ulResult)
    {
        gulPBFileCnt++;                                                 /* 文件计数器加1，准备处理下一个文件 */
        gstPBSearchCtrlInfo.usReadNum       = 0;
        gstPBSearchCtrlInfo.usReadOffset    = 0;                        /* 读取查找匹配列表的偏移量从0开始 */
        gstPBInitState.enPBInitState        = SI_PB_INIT_SEARCH_OK;
        gstPBInitState.enPBInitStep         = PB_INIT_IAP_CONTENT2;
        gstPBInitState.enPBSearchState      = PB_SEARCH_ENABLE;
    }
    else
    {
        /* 设置处理状态为USIMM SEARCH回复错误 */
        gstPBInitState.enPBInitState = SI_PB_INIT_SEARCH_ERR;

        PB_ERROR_LOG("SI_PB_InitIAPSearchMsgProc:Search Result Error.");
    }

    return;
}


/*****************************************************************************
函 数 名  : SI_PB_InitEmailSearchMsgProc
功能描述  : EMAIL查找结果处理函数
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年01月19日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_InitEmailSearchMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_SEARCHFILE_CNF_STRU   *pstPBMsg;
    VOS_UINT8                   ucSuffix;
    VOS_UINT16                  usEFID;

    pstPBMsg = (USIMM_SEARCHFILE_CNF_STRU *)pstMsg;

    if (USIMM_SEARCHFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitEmailSearchMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    ucSuffix = (VOS_UINT8)gulPBFileCnt;

    SI_PB_GetEFIDFromPath(&pstPBMsg->stFilePath, &usEFID);

    /* 查找的结果可以是OK也可以是NORECORD FOUND(无匹配记录)，其它回复结果都是错误的 */
    if ((USIMM_SW_NORECORD_FOUND == pstPBMsg->stCmdResult.ulResult)
        || (VOS_OK == pstPBMsg->stCmdResult.ulResult))
    {
        gstPBSearchCtrlInfo.usReadNum       = gstPBCtrlInfo.astEMLInfo[gulPBFileCnt].ucRecordNum - pstPBMsg->usDataLen;
        gstPBSearchCtrlInfo.usEfId          = usEFID;
        gstPBSearchCtrlInfo.usReadOffset    = 0;                        /* 读取查找匹配列表的偏移量从0开始 */
        gstPBInitState.enPBInitState        = SI_PB_INIT_SEARCH_OK;     /* 状态处理函数将文件计数器加1，准备处理下一个文件 */
        gstPBInitState.enPBInitStep         = PB_INIT_EML_CONTENT2;

        SI_PB_SearchResultProc(gstPBSearchCtrlInfo.aucReadString,
                                pstPBMsg->aucData,
                                pstPBMsg->usDataLen,
                                gstPBCtrlInfo.astEMLInfo[gulPBFileCnt].ucRecordNum);

        /* 如果SEARCH的结果是没有要读取的记录，需要判断当前文件是否是EMAIL文件的最后文件，
           如果是需要将对应的存储器类型设置为初始化已完成. 如果没有匹配的记录，将文件计数
           器加1，准备处理下一个文件*/
        if (0 == gstPBSearchCtrlInfo.usReadNum)
        {
            gulPBFileCnt++;

            if ((ucSuffix+1) == (VOS_UINT8)gstPBCtrlInfo.ulEMLFileNum)
            {
                gstEMLContent.enInitialState = PB_INITIALISED;
            }
        }
    }
    /* 查找的文件不存在，设置匹配的记录数为零，继续下一文件的查找过程 */
    else if (USIMM_SW_NOFILE_FOUND == pstPBMsg->stCmdResult.ulResult)
    {
        gulPBFileCnt++;                                                 /* 文件计数器加1，准备处理下一个文件 */
        gstPBSearchCtrlInfo.usReadNum       = 0;
        gstPBSearchCtrlInfo.usReadOffset    = 0;                        /* 读取查找匹配列表的偏移量从0开始 */
        gstPBInitState.enPBInitState        = SI_PB_INIT_SEARCH_OK;
        gstPBInitState.enPBInitStep         = PB_INIT_EML_CONTENT2;
        gstPBInitState.enPBSearchState      = PB_SEARCH_ENABLE;
    }
    else
    {
        /* 设置处理状态为USIMM回复SEARCH错误,按一般初始化步骤处理 */
        gstPBInitState.enPBInitState = SI_PB_INIT_SEARCH_ERR;

        PB_ERROR_LOG("SI_PB_InitEmailSearchMsgProc:Search Result Error.");
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitANRSearchMsgProc
功能描述  : ANR查找结果处理函数
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年01月20日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_InitANRSearchMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_SEARCHFILE_CNF_STRU       *pstPBMsg;
    VOS_UINT8                       ucXSuffix;
    VOS_UINT8                       ucYSuffix;
    VOS_UINT16                      usEFID;

    pstPBMsg = (USIMM_SEARCHFILE_CNF_STRU *)pstMsg;

    if (USIMM_SEARCHFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitANRSearchMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    SI_PB_GetEFIDFromPath(&pstPBMsg->stFilePath, &usEFID);

    /* 获取当前初始化的文件对应的电话本 */
    if (VOS_OK != SI_PB_GetANRSuffix(&ucXSuffix, &ucYSuffix, usEFID))
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_PBTYPE_UNKOWN;

        PB_ERROR_LOG("SI_PB_InitANRSearchMsgProc:PB Tpye Error");

        return;
    }

    /* 查找的结果可以是OK也可以是NORECORD FOUND(无匹配记录)，其它回复结果都是错误的 */
    if ((USIMM_SW_NORECORD_FOUND == pstPBMsg->stCmdResult.ulResult)
        || (VOS_OK == pstPBMsg->stCmdResult.ulResult))
    {
        gstPBSearchCtrlInfo.usReadNum       = gstPBCtrlInfo.astANRInfo[ucXSuffix][ucYSuffix].ucRecordNum - pstPBMsg->usDataLen;
        gstPBSearchCtrlInfo.usEfId          = usEFID;
        gstPBSearchCtrlInfo.usReadOffset    = 0;                        /* 读取查找匹配列表的偏移量从0开始 */
        gstPBInitState.enPBInitState        = SI_PB_INIT_SEARCH_OK;     /* 状态处理函数将文件计数器加1，准备处理下一个文件 */
        gstPBInitState.enPBInitStep         = PB_INIT_ANR_CONTENT2;
        gstPBInitState.enPBSearchState      = PB_SEARCH_ENABLE;

        SI_PB_SearchResultProc(gstPBSearchCtrlInfo.aucReadString,
                                pstPBMsg->aucData,
                                pstPBMsg->usDataLen,
                                gstPBCtrlInfo.astANRInfo[ucXSuffix][ucYSuffix].ucRecordNum);

        /* 如果SEARCH的结果是没有要读取的记录，需要判断当前文件是否是EMAIL文件的最后文件，
           如果是需要将对应的存储器类型设置为初始化已完成. 如果没有匹配的记录，将文件计数
           器加1，准备处理下一个文件*/
        if (0 == gstPBSearchCtrlInfo.usReadNum)
        {
            gulPBFileCnt++;

            if (VOS_OK == SI_PB_GheckANRLast(ucXSuffix, ucYSuffix))
            {
                gstEMLContent.enInitialState = PB_INITIALISED;
                gstPBCtrlInfo.ulANRStorageNum++;
            }
        }
    }
    /* 查找的文件不存在，设置匹配的记录数为零，继续下一文件的查找过程 */
    else if (USIMM_SW_NOFILE_FOUND == pstPBMsg->stCmdResult.ulResult)
    {
        gulPBFileCnt++;                                                 /* 文件计数器加1，准备处理下一个文件 */
        gstPBSearchCtrlInfo.usReadNum       = 0;
        gstPBSearchCtrlInfo.usReadOffset    = 0;                        /* 读取查找匹配列表的偏移量从0开始 */
        gstPBInitState.enPBInitState        = SI_PB_INIT_SEARCH_OK;
        gstPBInitState.enPBInitStep         = PB_INIT_ANR_CONTENT2;
        gstPBInitState.enPBSearchState      = PB_SEARCH_ENABLE;
    }
    else
    {
        /* 设置处理状态为USIMM回复错误,查找失败，则采用逐条读取的方式来完成ANR文件的初始化 */
        gstPBInitState.enPBInitState    = SI_PB_INIT_SEARCH_ERR;
        gstPBInitState.enPBSearchState  = PB_SEARCH_DISABLE;

        PB_ERROR_LOG("SI_PB_InitANRSearchMsgProc:Search Result Error.");
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitXDNSearchMsgProc
功能描述  : XDN查找结果处理函数
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年01月21日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_InitXDNSearchMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_SEARCHFILE_CNF_STRU       *pstPBMsg;
    VOS_UINT32                      ulPBType;
    VOS_UINT32                      ulNextPBType = PB_CONTENT_BUTT;
    VOS_UINT8                       ucRecordNum;
    VOS_UINT16                      usEFID;

    pstPBMsg = (USIMM_SEARCHFILE_CNF_STRU *)pstMsg;

    if (USIMM_SEARCHFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitXDNSearchMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    SI_PB_GetEFIDFromPath(&pstPBMsg->stFilePath, &usEFID);

    /* 获取当前初始化的文件对应的电话本 */
    if ( VOS_OK != SI_PB_GetXDNPBType(&ulPBType, usEFID) )
    {
        /* 设置处理状态为电话本类型未知 */
        gstPBInitState.enPBInitState = SI_PB_INIT_PBTYPE_UNKOWN;

        PB_ERROR_LOG("SI_PB_InitXDNSearchMsgProc:Unspecified PB Type");

        return;
    }

    /* 查找的结果可以是OK也可以是NORECORD FOUND(无匹配记录)，其它回复结果都是错误的 */
    if ((USIMM_SW_NORECORD_FOUND == pstPBMsg->stCmdResult.ulResult)
        || (VOS_OK == pstPBMsg->stCmdResult.ulResult))
    {
        if (PB_ADN_CONTENT == ulPBType)
        {
            ucRecordNum = gstPBCtrlInfo.astADNInfo[gulPBFileCnt].ucRecordNum;
        }
        else
        {
            ucRecordNum = (VOS_UINT8)gastPBContent[ulPBType].usTotalNum;
        }

        gstPBSearchCtrlInfo.usReadNum       = ucRecordNum - pstPBMsg->usDataLen;
        gstPBSearchCtrlInfo.usEfId          = usEFID;
        gstPBSearchCtrlInfo.usReadOffset    = 0;                        /* 读取查找匹配列表的偏移量从0开始 */
        gstPBInitState.enPBInitState        = SI_PB_INIT_SEARCH_OK;     /* 状态处理函数将文件计数器加1，准备处理下一个文件 */
        gstPBInitState.enPBInitStep         = PB_INIT_XDN_CONTENT2;
        gstPBInitState.enPBSearchState      = PB_SEARCH_ENABLE;

        SI_PB_SearchResultProc(gstPBSearchCtrlInfo.aucReadString,
                                pstPBMsg->aucData,
                                pstPBMsg->usDataLen,
                                ucRecordNum);

        /* 如果SEARCH的结果是没有要读取的记录，需要判断当前文件是否是XDN文件的最后文件，
           如果是需要将对应的存储器类型设置为初始化已完成 */
        if (0 == gstPBSearchCtrlInfo.usReadNum)
        {
            gulPBFileCnt++;

            /* 获取下一个需要缓存内容的电话本 */
            /*lint -e534*/
            SI_PB_GetXDNPBType(&ulNextPBType, gstPBInitState.ausFileId[gulPBFileCnt]);
            /*lint +e534*/

            /********** 如果是最后一个ADN文件，或非ADN电话本<一个文件对应一个电话本 *************/
            if (PB_ADN_CONTENT != ulPBType)
            {
                /* 设置当前电话本初始化状态为已初始化 */
                gastPBContent[ulPBType].enInitialState = PB_INITIALISED;
            }
            else if(PB_ADN_CONTENT != ulNextPBType)
            {
                /* 设置当前电话本初始化状态为已初始化 */
                gastPBContent[ulPBType].enInitialState = PB_INITIALISED;
            }
            else
            {
                ;
            }
        }
    }
    /* 查找的文件不存在，设置匹配的记录数为零，继续下一文件的查找过程 */
    else if (USIMM_SW_NOFILE_FOUND == pstPBMsg->stCmdResult.ulResult)
    {
        gulPBFileCnt++;                                                 /* 文件计数器加1，准备处理下一个文件 */
        gstPBSearchCtrlInfo.usReadNum       = 0;
        gstPBSearchCtrlInfo.usReadOffset    = 0;                        /* 读取查找匹配列表的偏移量从0开始 */
        gstPBInitState.enPBInitState        = SI_PB_INIT_SEARCH_OK;
        gstPBInitState.enPBInitStep         = PB_INIT_XDN_CONTENT2;
        gstPBInitState.enPBSearchState      = PB_SEARCH_ENABLE;

    }
    else
    {
        /* 设置处理状态为USIMM回复错误,查找失败，则采用逐条读取的方式来完成XDN文件的初始化 */
        gstPBInitState.enPBInitState    = SI_PB_INIT_SEARCH_ERR;
        gstPBInitState.enPBSearchState  = PB_SEARCH_DISABLE;

        PB_ERROR_LOG("SI_PB_InitXDNSearchMsgProc:Search Result Error.");
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitPBCSearchMsgProc2
功能描述  : PBC查找结果处理函数
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年02月02日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_InitPBCSearchMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_SEARCHFILE_CNF_STRU       *pstPBMsg;
    VOS_UINT16                      usEFID;

    pstPBMsg = (USIMM_SEARCHFILE_CNF_STRU *)pstMsg;

    if (USIMM_SEARCHFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitPBCSearchMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    SI_PB_GetEFIDFromPath(&pstPBMsg->stFilePath, &usEFID);

    /* 查找的结果可以是OK也可以是NORECORD FOUND(无匹配记录)，其它回复结果都是错误的 */
    if ((USIMM_SW_NORECORD_FOUND == pstPBMsg->stCmdResult.ulResult)
        || (VOS_OK == pstPBMsg->stCmdResult.ulResult))
    {
        /* 只有在SEARCH的处理函数中根据CNF消息中带回的PBC记录数来处理，
           在非SEARCH的处理函数中还是用ADN的记录数来判断 */
        gstPBCtrlInfo.usPBCRecordNum        = pstPBMsg->usTotalRecNum;
        gstPBSearchCtrlInfo.usReadNum       = gstPBCtrlInfo.usPBCRecordNum - pstPBMsg->usDataLen;
        gstPBSearchCtrlInfo.usEfId          = usEFID;
        gstPBSearchCtrlInfo.usReadOffset    = 0;                        /* 读取查找匹配列表的偏移量从0开始 */
        gstPBInitState.enPBInitState        = SI_PB_INIT_SEARCH_OK;     /* 状态处理函数将文件计数器加1，准备处理下一个文件 */
        gstPBInitState.enPBInitStep         = PB_INIT_PBC_CONTENT2;
        gstPBInitState.enPBSearchState      = PB_SEARCH_ENABLE;

        SI_PB_SearchResultProc(gstPBSearchCtrlInfo.aucReadString,
                                pstPBMsg->aucData,
                                pstPBMsg->usDataLen,
                                (VOS_UINT8)gstPBCtrlInfo.usPBCRecordNum);
    }
    /* 查找的文件不存在，设置匹配的记录数为零，继续下一文件的查找过程 */
    else if (USIMM_SW_NOFILE_FOUND == pstPBMsg->stCmdResult.ulResult)
    {
        gulPBFileCnt++;                                                 /* 文件计数器加1，准备处理下一个文件 */
        gstPBInitState.enPBInitState        = SI_PB_INIT_SEARCH_OK;
        gstPBInitState.enPBInitStep         = PB_INIT_PBC_SEARCH;       /* 从PB_INIT_PBC_SEARCH自然转到3G重同步过程 */
        gstPBInitState.enPBSearchState      = PB_SEARCH_ENABLE;
        gstPBSearchCtrlInfo.usReadOffset    = 0;
        gstPBSearchCtrlInfo.usReadNum       = 0;
    }
    else
    {
        /* 设置处理状态为USIMM回复错误,查找失败，则采用逐条读取的方式来完成PBC文件的初始化 */
        gstPBInitState.enPBInitState    = SI_PB_INIT_SEARCH_ERR;
        gstPBInitState.enPBSearchState  = PB_SEARCH_DISABLE;

        PB_ERROR_LOG("SI_PB_InitPBCSearchMsgProc:Search Result Error.");
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitIAPContentMsgProc2
功能描述  : 根据IAP查找结果初始化IAP的内容
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年01月18日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_InitIAPContentMsgProc2(PBMsgBlock *pstMsg)
{
    USIMM_READFILE_CNF_STRU      *pstPBMsg;
    VOS_UINT32                   ulOffset;
    VOS_UINT16                   usRecordNum;
    VOS_UINT8                    i;

    pstPBMsg = (USIMM_READFILE_CNF_STRU *)pstMsg;

    if (USIMM_READFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitIAPContentMsgProc2:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    if ( VOS_NULL_PTR == gstIAPContent.pIAPContent )
    {
        /* 设置处理状态为分配内存失败 */
        gstPBInitState.enPBInitState = SI_PB_INIT_PBMALLOC_FAIL;

        return;
    }

    if (VOS_OK == pstPBMsg->stCmdResult.ulResult)
    {
        /* 每个IAP文件的记录数可能不一致，计算偏移量时要累加 */
        usRecordNum = pstPBMsg->ucRecordNum;/*gstPBCtrlInfo.astIAPInfo[gulPBFileCnt].ucRecordNum; */

        for (i = 0; i < gulPBFileCnt; i++)
        {
            usRecordNum += gstPBCtrlInfo.astIAPInfo[i].ucRecordNum;
        }

        ulOffset = (usRecordNum - 1) * gstPBCtrlInfo.astIAPInfo[gulPBFileCnt].ucRecordLen;

        /*lint -e534*/
        VOS_MemCpy(gstIAPContent.pIAPContent + ulOffset, pstPBMsg->aucEf,
                            gstPBCtrlInfo.astIAPInfo[gulPBFileCnt].ucRecordLen);
        /*lint +e534*/
    }
    else
    {
        /* 如果读取记录失败，则不处理，继续后面记录的初始化 */
    }

    if (++gstPBSearchCtrlInfo.usReadOffset >= gstPBSearchCtrlInfo.usReadNum)
    {
        /* 当前初始化文件的记录已全部初始化完毕 */
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_EXCEED;
    }
    else
    {
        /* 设置处理状态为还有未初始化的记录 */
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_REMAIN;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitEmailContentMsgProc
功能描述  : 根据EMAIL查找结果初始化MEAIL的内容
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年01月20日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_InitEmailContentMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_READFILE_CNF_STRU      *pstPBMsg;
    VOS_UINT32                   ulOffset;
    VOS_UINT16                   usIndex;       /* 记录ADN电话本记录号对应的缓存索引号 */
    VOS_UINT16                   usRecordNum;   /* 当前读取的记录在所有记录中的编号，从1开始 */
    VOS_UINT8                    ucSuffix;
    VOS_UINT32                   i;

    ucSuffix = (VOS_UINT8)gulPBFileCnt;

    pstPBMsg = (USIMM_READFILE_CNF_STRU *)pstMsg;

    if (USIMM_READFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitEmailContentMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    if ( VOS_NULL_PTR == gstEMLContent.pContent )
    {
        /*设置处理状态为分配内存失败*/
        gstPBInitState.enPBInitState = SI_PB_INIT_SPBMALLOC_FAIL;

        return;
    }

    if (VOS_OK == pstPBMsg->stCmdResult.ulResult)
    {
        /* EMAIL文件中每组记录数可能不一致，计算偏移量时需要从头开始累加 */
        usRecordNum = pstPBMsg->ucRecordNum;

        for (i = 0; i < ucSuffix; i++)
        {
            usRecordNum += gstPBCtrlInfo.astEMLInfo[i].ucRecordNum;
        }

        usIndex     = usRecordNum -1;
        ulOffset    = usIndex * pstPBMsg->usEfLen;

        if (VOS_OK == SI_PB_EMLContentProc(pstPBMsg, ucSuffix, usRecordNum))
        {
            /* 复制Email电话本的记录到缓存 */
            /*lint -e534*/
            VOS_MemCpy(gstEMLContent.pContent + ulOffset, pstPBMsg->aucEf, pstPBMsg->usEfLen);
            /*lint +e534*/
        }
    }
    else
    {
        /* 如果读取记录失败，则不处理，继续后面记录的初始化 */
    }

    if (++gstPBSearchCtrlInfo.usReadOffset >= gstPBSearchCtrlInfo.usReadNum)
    {

        if((ucSuffix+1) == (VOS_UINT8)gstPBCtrlInfo.ulEMLFileNum)
        {
            gstEMLContent.enInitialState = PB_INITIALISED;
        }

        /* 当前初始化文件的记录已全部初始化完毕 */
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_EXCEED;
    }
    else
    {
        /* 设置处理状态为还有未初始化的记录 */
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_REMAIN;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitANRContentMsgProc2
功能描述  : 根据ANR查找结果初始化ANR的内容
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年01月20日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_InitANRContentMsgProc2(PBMsgBlock *pstMsg)
{
    USIMM_READFILE_CNF_STRU            *pstPBMsg;
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulExtInfoNum;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usIndex;    /*记录ADN电话本记录号对应的缓存索引号*/
    VOS_UINT16                          usExtRecIdOffset;
    VOS_UINT16                          usAnrRecordLen;
    VOS_UINT8                           ucXSuffix;
    VOS_UINT8                           ucYSuffix;
    VOS_UINT8                          *pucANRContent;
    VOS_UINT16                          usEFID;
    VOS_UINT8                           i;

    pstPBMsg = (USIMM_READFILE_CNF_STRU *)pstMsg;

    if (USIMM_READFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitANRContentMsgProc2:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    SI_PB_GetEFIDFromPath(&pstPBMsg->stFilePath, &usEFID);

    /* 获取当前初始化的文件的ID */
    if (VOS_OK != SI_PB_GetANRSuffix(&ucXSuffix, &ucYSuffix, usEFID))
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_PBTYPE_UNKOWN;

        PB_ERROR_LOG("SI_PB_InitANRContentMsgProc2:PB Tpye Error");

        return;
    }

    if ( VOS_NULL_PTR == gastANRContent[ucYSuffix].pContent )
    {
        /* 设置处理状态为分配内存失败 */
        gstPBInitState.enPBInitState = SI_PB_INIT_SPBMALLOC_FAIL;

        return;
    }

    if(VOS_OK == pstPBMsg->stCmdResult.ulResult)
    {
        /* 每组ADN文件对应的ANR记录数可能不一致，需要从头开始累加 */
        usIndex = pstPBMsg->ucRecordNum;

        for (i = 0; i < ucXSuffix; i++)
        {
            usIndex += gstPBCtrlInfo.astANRInfo[i][ucYSuffix].ucRecordNum;
        }

        ulOffset = (usIndex-1)*gstPBCtrlInfo.astANRInfo[ucXSuffix][ucYSuffix].ucRecordLen;

        pucANRContent   = gastANRContent[ucYSuffix].pContent + ulOffset;
        usAnrRecordLen  = gastANRContent[ucYSuffix].ucRecordLen;

        /* 复制ANR电话本的记录到缓存 */
        /*lint -e534*/
        VOS_MemCpy(pucANRContent, pstPBMsg->aucEf, usAnrRecordLen);
        /*lint +e534*/

        if (PB_FILE_TYPE2 == gstPBCtrlInfo.astANRInfo[ucXSuffix][ucYSuffix].enANRType)
        {
            usExtRecIdOffset = pstPBMsg->usEfLen - 3;
        }
        else
        {
            usExtRecIdOffset = pstPBMsg->usEfLen - 1;
        }

        ulExtInfoNum = gastPBContent[PB_ADN_CONTENT].ulExtInfoNum;

        /* 检查此记录是否为有效记录，如果是有效记录还要检查 */
        if (VOS_OK == SI_PB_CheckANRValidity(pucANRContent))
        {
            ulResult = SI_PB_InitANRType2ValidJudge(ucXSuffix,ucYSuffix,pstPBMsg->ucRecordNum,&usIndex);
        }
        else
        {
            ulResult = VOS_ERR;
        }

        /*该记录有效*/
        if (VOS_OK == ulResult)
        {
            gastANRContent[ucYSuffix].usUsedNum++;

            /* 如果之前姓名和号码字段为空，但当前解析出second number不为空，则该条复合记录置为非空 */
            if (SI_PB_CONTENT_INVALID == SI_PB_GetBitFromBuf(gastPBContent[PB_ADN_CONTENT].pIndex, usIndex))
            {
                gstPBCtrlInfo.ulTotalUsed++;

                SI_PB_SetBitToBuf(gastPBContent[PB_ADN_CONTENT].pIndex,usIndex,SI_PB_CONTENT_VALID);
            }
        }
        else
        {
            /* 如果该记录无效，则设置该EXT信息为无效 */
            pstPBMsg->aucEf[usExtRecIdOffset] = 0xFF;

            /* 同时设置ANR内存内容为无效 */
            /*pucANRContent[0] = 0xFF; */
            /*lint -e534*/
            VOS_MemSet(pucANRContent, (VOS_CHAR)0xFF, usAnrRecordLen);
            /*lint +e534*/
        }

        /* 检查是否有EXT文件要读取，XDN文件中扩展记录的记录号不能为0或0xFF */
        if ((0xFF != pstPBMsg->aucEf[usExtRecIdOffset])
            && (0 != pstPBMsg->aucEf[usExtRecIdOffset])
            && (SI_PB_FILE_NOT_EXIST != gastEXTContent[ulExtInfoNum].usExtFlag))
        {
            gstPBInitState.enPBInitState = SI_PB_INIT_EXT_RECORD;
            gstPBInitState.enPBInitStep  = PB_INIT_EXTR_CONTENT;
            gulExtRecord                 = pstPBMsg->aucEf[usExtRecIdOffset];
            gulPBRecordCnt               = 0;   /* 无意义，防止在EXT函数处理时出错 */
            ++gstPBSearchCtrlInfo.usReadOffset; /* 查找结果偏移量加1，在EXT记录处理完时不必加1 */
            return;
        }
    }
    else
    {
        /* 如果读取记录失败，则不处理，继续后面记录的初始化 */
    }

    /* 当前需要查找的记录已全部初始化完毕 */
    if ( ++gstPBSearchCtrlInfo.usReadOffset >= gstPBSearchCtrlInfo.usReadNum )
    {
        if (VOS_OK == SI_PB_GheckANRLast(ucXSuffix,ucYSuffix))
        {
            gastANRContent[ucYSuffix].enInitialState = PB_INITIALISED;

            gstPBCtrlInfo.ulANRStorageNum++;
        }

        /* 设置处理状态为当前文件的所有记录已初始化完毕 */
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_EXCEED;
    }
    else
    {
        /* 设置处理状态为还有未初始化的记录 */
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_REMAIN;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitANRContentMsgProc2
功能描述  : 根据XDN查找结果初始化XDN的内容
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年01月21日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_InitXDNContentMsgProc2(PBMsgBlock *pstMsg)
{
    USIMM_READFILE_CNF_STRU         *pstPBMsg;
    VOS_UINT32                      ulPBType;
    VOS_UINT32                      ulOffset;
    VOS_UINT32                      ulExtInfoNum;
    VOS_UINT32                      ulNextPBType = PB_CONTENT_BUTT;
    VOS_UINT16                      usIndex;       /*记录ADN电话本记录号对应的缓存索引号*/
    VOS_UINT16                      usExtRecIdOffset;
    VOS_UINT16                      usEFID;

    pstPBMsg = (USIMM_READFILE_CNF_STRU *)pstMsg;

    if (USIMM_READFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitXDNContentMsgProc2:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    SI_PB_GetEFIDFromPath(&pstPBMsg->stFilePath, &usEFID);

    /* 获取当前初始化的文件对应的电话本文件类型 */
    if (VOS_OK != SI_PB_GetXDNPBType(&ulPBType, usEFID))
    {
        PB_ERROR_LOG("SI_PB_InitXDNContentMsgProc2:Unspecified PB Type");

        /*设置处理状态为电话本类型未知*/
        gstPBInitState.enPBInitState = SI_PB_INIT_PBTYPE_UNKOWN;
        gstPBInitState.enPBInitStep  = PB_INIT_XDN_CONTENT2;

        return;
    }

    if (VOS_NULL_PTR == gastPBContent[ulPBType].pContent)
    {
        PB_ERROR_LOG("SI_PB_InitXDNContentMsgProc2:Null Ptr");

        /* 设置处理状态为分配内存失败 */
        gstPBInitState.enPBInitState = SI_PB_INIT_PBMALLOC_FAIL;

        return;
    }

    if (VOS_OK == pstPBMsg->stCmdResult.ulResult)
    {
        /* 获取回复的记录内容在缓存中的位置，ADN和其他电话本分别处理 */
        if ( PB_ADN_CONTENT == ulPBType )
        {
            /* 获取当前的文件和记录号对应的缓存索引号 */
            if (VOS_OK != SI_PB_CountADNIndex(usEFID, pstPBMsg->ucRecordNum, &usIndex))
            {
                /* 设置处理状态为当前文件所有记录处理完毕 */
                gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_EXCEED;

                PB_ERROR_LOG("SI_PB_InitXDNContentMsgProc2:Get Record Index Failed");

                return;
            }
        }
        else
        {
            usIndex     = pstPBMsg->ucRecordNum;
        }

        ulOffset = (usIndex - 1) * gastPBContent[ulPBType].ucRecordLen;

        /* 复制XDN电话本的记录到缓存 */
        /*lint -e534*/
        VOS_MemCpy(gastPBContent[ulPBType].pContent + ulOffset,
                   pstPBMsg->aucEf, gastPBContent[ulPBType].ucRecordLen);
        /*lint +e534*/

        /* 检查此记录是否为有效记录 */
        if (VOS_OK == SI_PB_CheckContentValidity(&gastPBContent[ulPBType], pstPBMsg->aucEf))
        {
            gastPBContent[ulPBType].usUsedNum++;

            if (SI_PB_CONTENT_INVALID ==
                        SI_PB_GetBitFromBuf(gastPBContent[ulPBType].pIndex, usIndex))
            {
                /* 如果之前姓名和号码字段为空，但当前解析出ADN不为空，则该条复合记录置为非空 */
                if(PB_ADN_CONTENT == ulPBType)
                {
                    gstPBCtrlInfo.ulTotalUsed++;
                }

                SI_PB_SetBitToBuf(gastPBContent[ulPBType].pIndex,usIndex,SI_PB_CONTENT_VALID);
            }
        }

        usExtRecIdOffset = ((EFBDN == usEFID)?\
                            (pstPBMsg->usEfLen - 2):(pstPBMsg->usEfLen - 1));

        ulExtInfoNum = gastPBContent[ulPBType].ulExtInfoNum;

        /* 检查是否有EXT文件要读取，XDN文件中扩展记录的记录号不能为0或0xFF */
        if( ( 0xFF != pstPBMsg->aucEf[usExtRecIdOffset] )
            && (0 != pstPBMsg->aucEf[usExtRecIdOffset])
            && (SI_PB_FILE_NOT_EXIST != gastEXTContent[ulExtInfoNum].usExtFlag) )
        {
            gstPBInitState.enPBInitState = SI_PB_INIT_EXT_RECORD;
            gstPBInitState.enPBInitStep  = PB_INIT_EXT_CONTENT;
            gulExtRecord                 = pstPBMsg->aucEf[usExtRecIdOffset];
            gulPBRecordCnt               = 0;   /* 无意义，防止在EXT函数处理时出错 */
            ++gstPBSearchCtrlInfo.usReadOffset; /* 查找结果偏移量加1，在EXT记录处理完时不必加1 */
            return;
        }
    }
    else
    {
        /* 如果读取记录失败，则不处理，继续后面记录的初始化 */
    }

    /* 当前需要查找的记录已全部初始化完毕 */
    if ( ++gstPBSearchCtrlInfo.usReadOffset >= gstPBSearchCtrlInfo.usReadNum )
    {
        /* 获取下一个需要缓存内容的电话本 */
        /*lint -e534*/
        SI_PB_GetXDNPBType(&ulNextPBType, gstPBInitState.ausFileId[gulPBFileCnt+1]);
        /*lint +e534*/

        /********** 如果是最后一个ADN文件，或非ADN电话本<一个文件对应一个电话本 *************/
        if (PB_ADN_CONTENT != ulPBType)
        {
            /* 设置当前电话本初始化状态为已初始化 */
            gastPBContent[ulPBType].enInitialState = PB_INITIALISED;
        }
        else if(PB_ADN_CONTENT != ulNextPBType)
        {
            /* 设置当前电话本初始化状态为已初始化 */
            gastPBContent[ulPBType].enInitialState = PB_INITIALISED;
        }
        else
        {
            ;
        }

        /* 设置处理状态为当前文件的所有记录已初始化完毕 */
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_EXCEED;
    }
    else
    {
        /* 设置处理状态为还有未初始化的记录 */
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_REMAIN;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitPBCContentMsgProc2
功能描述  : 根据PBC查找结果初始化PBC的内容
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年02月02日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_InitPBCContentMsgProc2(PBMsgBlock *pstMsg)
{
    USIMM_READFILE_CNF_STRU      *pstPBMsg;
    VOS_UINT8                    aucEF[2];

    pstPBMsg = (USIMM_READFILE_CNF_STRU *)pstMsg;

    if (USIMM_READFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitPBCContentMsgProc2:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    if (VOS_OK != pstPBMsg->stCmdResult.ulResult)
    {
        /*lint -e534*/
        VOS_MemSet(aucEF, 0x00, sizeof(aucEF));
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(aucEF, pstPBMsg->aucEf, sizeof(aucEF));
        /*lint +e534*/
    }

    SI_PB_DecodeEFPBCRecord(aucEF, pstPBMsg->ucRecordNum);

    /* 当前需要查找的记录已全部初始化完毕 */
    if (++gstPBSearchCtrlInfo.usReadOffset >= gstPBSearchCtrlInfo.usReadNum)
    {
        /* 所有记录都读取完成 */
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_EXCEED;
    }
    else
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_REMAIN;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitPBCContentMsgProc
功能描述  : 根据PBC查找结果初始化PBC的内容
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年02月02日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_InitPBCContentMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_READFILE_CNF_STRU     *pstPBMsg;
    VOS_UINT8                    aucEF[2];

    pstPBMsg = (USIMM_READFILE_CNF_STRU *)pstMsg;

    if (USIMM_READFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitPBCContentMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    if (VOS_OK != pstPBMsg->stCmdResult.ulResult)
    {
        /*lint -e534*/
        VOS_MemSet(aucEF, 0x00, sizeof(aucEF));
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(aucEF, pstPBMsg->aucEf, sizeof(aucEF));
        /*lint +e534*/
    }

    SI_PB_DecodeEFPBCRecord(aucEF, pstPBMsg->ucRecordNum);

    /* 当前需要读取的记录已全部初始化完毕 */
    if (++gulPBRecordCnt > gstPBCtrlInfo.astADNInfo[0].ucRecordNum)
    {
        /* 所有记录都读取完成 */
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_EXCEED;
    }
    else
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_REMAIN;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitANRType2ValidJudge
功能描述  : 对于Type2类型有效ANR记录,确认IAP对应关系是否正确，如果不正确则不计为有效记录
输入参数  :
输出参数  :
返 回 值  : VOS_OK  有效
            VOS_ERR 无效
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年09月14日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_InitANRType2ValidJudge(VOS_UINT8 ucXSuffix, VOS_UINT8 ucYSuffix,
                                                    VOS_UINT8 ucRecordNum,VOS_UINT16 *pusRealIndex)
{
    VOS_UINT32 i;

    if(PB_FILE_TYPE2 == gstPBCtrlInfo.astANRInfo[ucXSuffix][ucYSuffix].enANRType)
    {
        for(i = 0; i < gstPBCtrlInfo.astIAPInfo[ucXSuffix].ucRecordNum; i++)
        {
            /*IAP中能找到该记录对应关系*/
            if(gstIAPContent.pIAPContent[(ucXSuffix*(gstPBCtrlInfo.astIAPInfo[0].ucRecordLen*gstPBCtrlInfo.astIAPInfo[0].ucRecordNum))
                    +(i*gstPBCtrlInfo.astIAPInfo[0].ucRecordLen)+(gstPBCtrlInfo.astANRInfo[ucXSuffix][ucYSuffix].ulANRTagNum-1)] == ucRecordNum)
            {
                *pusRealIndex = (VOS_UINT16)((ucXSuffix*gstPBCtrlInfo.astIAPInfo[0].ucRecordNum) + (i+1));

                return VOS_OK;
            }
        }

        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
    }
}
/*****************************************************************************
函 数 名  : SI_PB_InitANRContentMsgProc
功能描述  : 初始化XDN电话本缓存，完成后进入初始化下一步
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  : gastPBContent
            gstPBInitState
            gstPBCtrlInfo
            gulPBRecordCnt
返 回 值  :
调用函数  : SI_PB_CountADNIndex
            VOS_MemCpy
            SI_PB_CheckContentValidity
            SI_PB_InitXDNContent
            VOS_MemFree
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_InitANRContentMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_READFILE_CNF_STRU     *pstPBMsg;
    VOS_UINT32                  ulOffset;
    VOS_UINT32                  ulExtInfoNum;
    VOS_UINT32                  ulResult = VOS_OK;
    VOS_UINT16                  usExtRecIdOffset;
    VOS_UINT16                  usAnrRecordLen;
    VOS_UINT16                  usIndex;/*记录ADN电话本记录号对应的缓存索引号*/
    VOS_UINT8                   ucRecordNum;
    VOS_UINT8                   ucXSuffix;
    VOS_UINT8                   ucYSuffix;
    VOS_UINT8                   *pucANRContent;
    VOS_UINT8                   i;
    VOS_UINT16                  usEFID;

    pstPBMsg = (USIMM_READFILE_CNF_STRU *)pstMsg;

    if (USIMM_READFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitANRContentMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    SI_PB_GetEFIDFromPath(&pstPBMsg->stFilePath, &usEFID);

    /*获取当前初始化的文件对应的电话本*/
    if(VOS_OK != SI_PB_GetANRSuffix(&ucXSuffix, &ucYSuffix, usEFID))
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_PBTYPE_UNKOWN;

        PB_ERROR_LOG("SI_PB_InitANRContentMsgProc:PB Tpye Error");

        return;
    }

    /*如果错误，则初始化状态出错*/
    if(VOS_OK != pstPBMsg->stCmdResult.ulResult)
    {
        /*设置处理状态为USIMM回复错误*/
        gstPBInitState.enPBInitState = SI_PB_INIT_USIMSPBCNF_ERR;

        PB_ERROR_LOG("SI_PB_InitANRContentMsgProc:Intial Step Error");

        return;
    }

    if ( VOS_NULL_PTR == gastANRContent[ucYSuffix].pContent )
    {
        /*设置处理状态为分配内存失败*/
        gstPBInitState.enPBInitState = SI_PB_INIT_SPBMALLOC_FAIL;

        return;
    }

    /* 每组ADN文件对应的ANR记录数可能不一致，需要从头开始累加 */
    usIndex = pstPBMsg->ucRecordNum;

    for (i = 0; i < ucXSuffix; i++)
    {
        usIndex += gstPBCtrlInfo.astANRInfo[i][ucYSuffix].ucRecordNum;
    }

    ulOffset = (usIndex-1)*gstPBCtrlInfo.astANRInfo[ucXSuffix][ucYSuffix].ucRecordLen;

    pucANRContent = gastANRContent[ucYSuffix].pContent + ulOffset;
    usAnrRecordLen  = gastANRContent[ucYSuffix].ucRecordLen;

    /*复制ANR电话本的记录到缓存*/
    /*lint -e534*/
    VOS_MemCpy(pucANRContent, pstPBMsg->aucEf, usAnrRecordLen);
    /*lint +e534*/

    if(PB_FILE_TYPE2 == gstPBCtrlInfo.astANRInfo[ucXSuffix][ucYSuffix].enANRType)
    {
        usExtRecIdOffset = pstPBMsg->usEfLen - 3;
    }
    else
    {
        usExtRecIdOffset = pstPBMsg->usEfLen - 1;
    }

    ulExtInfoNum = gastPBContent[PB_ADN_CONTENT].ulExtInfoNum;

    /*检查此记录是否为有效记录*/
    if(VOS_OK == SI_PB_CheckANRValidity(pucANRContent))
    {
        ulResult = SI_PB_InitANRType2ValidJudge(ucXSuffix, ucYSuffix, pstPBMsg->ucRecordNum, &usIndex);
    }
    else
    {
        ulResult = VOS_ERR;
    }

    /*该记录有效*/
    if(VOS_OK == ulResult)
    {
        gastANRContent[ucYSuffix].usUsedNum++;

        /*如果之前姓名和号码字段为空，但当前解析出second number不为空，则该条复合记录置为非空*/
        if (SI_PB_CONTENT_INVALID == SI_PB_GetBitFromBuf(gastPBContent[PB_ADN_CONTENT].pIndex, usIndex))
        {
            gstPBCtrlInfo.ulTotalUsed++;

            SI_PB_SetBitToBuf(gastPBContent[PB_ADN_CONTENT].pIndex,usIndex,SI_PB_CONTENT_VALID);
        }
    }
    else
    {
        /*如果该记录无效，则设置该EXT信息为无效*/
        pstPBMsg->aucEf[usExtRecIdOffset] = 0xFF;

        /*同时设置ANR内存内容为无效*/
        pucANRContent[0] = 0xFF;
    }

    /* 检查是否有EXT文件要读取，XDN文件中扩展记录的记录号不能为0或0xFF */
    if( ( 0xFF != pstPBMsg->aucEf[usExtRecIdOffset] )
        && (0 != pstPBMsg->aucEf[usExtRecIdOffset])
        && (SI_PB_FILE_NOT_EXIST != gastEXTContent[ulExtInfoNum].usExtFlag) )
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_EXT_RECORD;
        gstPBInitState.enPBInitStep  = PB_INIT_EXTR_CONTENT;
        gulExtRecord                 = pstPBMsg->aucEf[usExtRecIdOffset];
        return;
    }

    ucRecordNum = gstPBCtrlInfo.astANRInfo[ucXSuffix][ucYSuffix].ucRecordNum;

    if ( ++gulPBRecordCnt > ucRecordNum )/*当前初始化文件的记录已全部初始化完毕*/
    {
        if(VOS_OK == SI_PB_GheckANRLast(ucXSuffix,ucYSuffix))
        {
            gastANRContent[ucYSuffix].enInitialState = PB_INITIALISED;

            gstPBCtrlInfo.ulANRStorageNum++;
        }

        /*设置处理状态为当前文件的所有记录已初始化完毕*/
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_EXCEED;
    }
    else
    {
        /*设置处理状态为还有未初始化的记录*/
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_REMAIN;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitEXTRContentMsgProc
功能描述  : 初始化ANR EXT内容，完成后进入初始化下一步
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年6月3日
    作    者   : m00128685
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_InitEXTRContentMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_READFILE_CNF_STRU     *pstPBMsg;
    VOS_UINT32                   ulOffset;
    VOS_UINT32                   ulResult1;
    VOS_UINT32                   ulResult2;
    VOS_UINT8                    ucRecordNum;
    VOS_UINT16                   usANRFileId;
    VOS_UINT32                   ulExtInfoNum;
    VOS_UINT8                    ucXSuffix;
    VOS_UINT8                    ucYSuffix;

    pstPBMsg = (USIMM_READFILE_CNF_STRU *)pstMsg;

    if (USIMM_READFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitEXTRContentMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    if (VOS_OK != SI_PB_GetANRFid((gulPBFileCnt+1),&usANRFileId))
    {
        /*设置处理状态为电话本类型未知*/
        gstPBInitState.enPBInitState = SI_PB_INIT_PBTYPE_UNKOWN;

        /*AT2D15844*/
        gstPBInitState.enPBInitStep = PB_INIT_ANR_CONTENT;

        PB_ERROR_LOG("SI_PB_InitEXTRContentMsgProc:Unspecified PB Type");

        return;
    }

    if(VOS_OK != SI_PB_GetANRSuffix(&ucXSuffix, &ucYSuffix, usANRFileId))
    {
        /*设置处理状态为电话本类型未知*/
        gstPBInitState.enPBInitState = SI_PB_INIT_PBTYPE_UNKOWN;

        /*AT2D15844*/
        gstPBInitState.enPBInitStep = PB_INIT_ANR_CONTENT;

        PB_ERROR_LOG("SI_PB_InitEXTRContentMsgProc:Suffix Error");

        return;
    }

    ucRecordNum = gstPBCtrlInfo.astANRInfo[ucXSuffix][ucYSuffix].ucRecordNum;

    ulResult1 = (gstPBSearchCtrlInfo.usReadOffset >= gstPBSearchCtrlInfo.usReadNum);    /* 当前SEARCH记录已全部初始化完成 */
    ulResult2 = (++gulPBRecordCnt > ucRecordNum);                                       /* 当前初始化文件的记录已全部初始化完毕 */

    /* 如果当前读取记录已经超过当前文件记录数需要切换到下一个文件 */
    if (ulResult1 || ulResult2)
    {
        if(VOS_OK == SI_PB_GheckANRLast(ucXSuffix,ucYSuffix))
        {
            gastANRContent[ucYSuffix].enInitialState = PB_INITIALISED;
            gstPBCtrlInfo.ulANRStorageNum++;
        }

        /*设置处理状态为当前文件的所有记录已初始化完毕*/
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_EXCEED;
    }
    else
    {
        /*设置处理状态为还有未初始化的记录*/
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_REMAIN;
    }

    /* 下一步初始化文件为ANR文件，根据查找状态来判断
    是使用逐条读取的方式还是用查找的方式来初始化 */
    if (PB_SEARCH_ENABLE  == gstPBInitState.enPBSearchState)
    {
        gstPBInitState.enPBInitStep = PB_INIT_ANR_CONTENT2;
    }
    else
    {
        gstPBInitState.enPBInitStep = PB_INIT_ANR_CONTENT;
    }

    if ( VOS_OK != pstPBMsg->stCmdResult.ulResult )
    {
        /* 如果在初始化EXT文件的过程中出错，如读取失败，不处理，继续ANR的初始化 */
        PB_ERROR_LOG("SI_PB_InitEXTRContentMsgProc:Intial Msg Return Error");
        return;
    }
    else
    {
        ulOffset = (gulExtRecord - 1)*SI_PB_EXT_LEN;

        /*复制EXT内容到缓存，如果记录为有效记录，已使用记录才加1*/
        ulExtInfoNum = gastPBContent[PB_ADN_CONTENT].ulExtInfoNum;

        /*lint -e420 -e534 修改人: j00174725; 检视人: xucheng*/
        VOS_MemCpy(gastEXTContent[ulExtInfoNum].pExtContent + ulOffset, pstPBMsg->aucEf, SI_PB_EXT_LEN);
        /*lint +e420 +e534 修改人: j00174725; 检视人: xucheng*/

        if( 0 != *(pstPBMsg->aucEf+1))
        {
            gastEXTContent[ulExtInfoNum].usExtUsedNum++;
        }

        return;
    }
}

/*****************************************************************************
函 数 名  : SI_PB_InitEXTRContentMsgProc
功能描述  : 初始化Email内容，完成后进入初始化下一步
输入参数  : pstMsg:USIMM模块回复的消息
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年5月6日
    作    者   : m00128685
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_InitEMLContentMsgProc(PBMsgBlock *pstMsg)
{
    USIMM_READFILE_CNF_STRU      *pstPBMsg;
    VOS_UINT32                   ulOffset;
    VOS_UINT16                   usIndex;/*记录ADN电话本记录号对应的缓存索引号*/
    VOS_UINT8                    ucRecordNum;
    VOS_UINT8                    ucSuffix;
    VOS_UINT8                    i;

    ucSuffix = (VOS_UINT8)gulPBFileCnt;

    pstPBMsg = (USIMM_READFILE_CNF_STRU *)pstMsg;

    if (USIMM_READFILE_CNF != pstPBMsg->stCmdResult.enMsgName)
    {
        gstPBInitState.enPBInitState = SI_PB_INIT_MSGTYPE_ERR;

        /*lint -e534*/
        (VOS_VOID)LogPrint("\r\nSI_PB_InitEMLContentMsgProc:Wrong Msg\r\n");
        /*lint +e534*/

        return;
    }

    /*如果错误，则初始化状态出错*/
    if(VOS_OK != pstPBMsg->stCmdResult.ulResult)
    {
        /*设置处理状态为USIMM回复错误*/
        gstPBInitState.enPBInitState = SI_PB_INIT_USIMSPBCNF_ERR;

        PB_ERROR_LOG("SI_PB_InitEMLContentMsgProc:Intial Step Error");

        return;
    }

    if ( VOS_NULL_PTR == gstEMLContent.pContent )
    {
        /*设置处理状态为分配内存失败*/
        gstPBInitState.enPBInitState = SI_PB_INIT_SPBMALLOC_FAIL;

        PB_ERROR_LOG("SI_PB_InitEMLContentMsgProc:The Memory is Null");

        return;
    }

    usIndex     = pstPBMsg->ucRecordNum;

    for (i = 0; i < ucSuffix; i++)
    {
        usIndex += gstPBCtrlInfo.astEMLInfo[i].ucRecordNum;
    }

    ucRecordNum = gstPBCtrlInfo.astEMLInfo[ucSuffix].ucRecordNum;
    ulOffset    = (usIndex - 1) * gstPBCtrlInfo.astEMLInfo[ucSuffix].ucRecordLen;

    if (VOS_OK == SI_PB_EMLContentProc(pstPBMsg, ucSuffix, usIndex))
    {
        /*复制Email电话本的记录到缓存*/
        /*lint -e534*/
        VOS_MemCpy(gstEMLContent.pContent + ulOffset, pstPBMsg->aucEf, pstPBMsg->usEfLen);
        /*lint +e534*/
    }

    if ( ++gulPBRecordCnt > ucRecordNum )/*当前初始化文件的记录已全部初始化完毕*/
    {
        if((ucSuffix+1) == (VOS_UINT8)gstPBCtrlInfo.ulEMLFileNum)
        {
            gstEMLContent.enInitialState = PB_INITIALISED;
        }

        /*设置处理状态为当前文件的所有记录已初始化完毕*/
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_EXCEED;
    }
    else
    {
        /*设置处理状态为还有未初始化的记录*/
        gstPBInitState.enPBInitState = SI_PB_INIT_RECORD_REMAIN;
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitSYNCHProc
功能描述  : 处理3G重同步文件内容
输入参数  : pstMsg
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2008年10月15日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_InitSYNCHProc(PBMsgBlock *pstMsg)
{
    if(USIMM_READFILE_CNF == pstMsg->ulMsgName)
    {
        /*处理3G重同步时的读文件请求回复*/
        SI_PB_InitSYNCHGetProc(pstMsg);

        return;
    }

    if(USIMM_UPDATEFILE_CNF == pstMsg->ulMsgName)
    {
        /*处理3G重同步时的写文件请求回复*/
        SI_PB_InitSYNCHSetProc(pstMsg);
    }

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_InitInfoAppDebug
功能描述  : INFO APP过程的DEBUG函数
输入参数  : pstMsg
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2015年3月12日
    作    者   : H00300778
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_InitInfoAppDebug(PBMsgBlock *pstMsg)
{
    /*设置初始化状态为已初始化*/
    gstPBInitState.enPBInitStep = PB_INIT_FINISHED;

    /*lint -e534*/
    vos_printf("\r\nSI_PB_InitInfoAppDebug:");
    vos_printf("\r\nSend Pid: %d",pstMsg->ulSenderPid);
    vos_printf("\r\nRcv Pid: %d", pstMsg->ulReceiverPid);
    vos_printf("\r\nMsg Name: %d", pstMsg->ulMsgName);
    /*lint +e534*/

    return;
}

/*****************************************************************************
函 数 名  : SI_PB_TransferFileCnt2ExtFileID
功能描述  : 从当前初始化的XDN文件的计数转换到EXT文件的ID
输入参数  : PBFileCnt
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2009年5月8日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT16  SI_PB_TransferFileCnt2ExtFileID(VOS_UINT32 PBFileCnt,
                                                    VOS_UINT32 *pulPBType)
{
    VOS_UINT32      ulPBType;

    /*lint -e534*/
    SI_PB_GetXDNPBType(&ulPBType, gstPBInitState.ausFileId[PBFileCnt]);
    /*lint +e534*/

    *pulPBType = ulPBType;

    /*如果为SIM卡，填写需要初始化的文件和初始化信息*/
    if ( USIMM_CARD_SIM == gstPBInitState.enCardType )
    {
        if(PB_ADN_CONTENT == ulPBType)/*ADN*/
        {
            return gastEXTContent[PB_ADN_CONTENT].usExtFileId;
        }
        else if(PB_FDN_CONTENT == ulPBType)/*FDN*/
        {
            return gastEXTContent[PB_FDN_CONTENT].usExtFileId;
        }
        else if(PB_BDN_CONTENT == ulPBType)/*BDN*/
        {
            return gastEXTContent[PB_BDN_CONTENT].usExtFileId;
        }
        else/*MSISDN*/
        {
            return gastEXTContent[PB_ADN_CONTENT].usExtFileId;
        }
    }
    else
    {
        if(PB_ADN_CONTENT ==ulPBType)/*ADN*/
        {
            return gastEXTContent[PB_ADN_CONTENT].usExtFileId;
        }
        else if(PB_FDN_CONTENT == ulPBType )/*FDN*/
        {
            return gastEXTContent[PB_FDN_CONTENT].usExtFileId;
        }
        else if(PB_BDN_CONTENT == ulPBType)/*BDN*/
        {
            return gastEXTContent[PB_BDN_CONTENT].usExtFileId;
        }
        else/*MSISDN*/
        {
            return gastEXTContent[PB_MSISDN_CONTENT].usExtFileId;
        }
    }
}

/*****************************************************************************
函 数 名  : SI_PB_SearchResultProc
功能描述  : 查找结果处理函数，通过输入的匹配记录号得到需要读取的记录号
输入参数  : PBFileCnt
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年01月18日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID SI_PB_SearchResultProc(VOS_UINT8           *pucReadString,
                                            VOS_UINT8         *pucSearchResult,
                                            VOS_UINT16        usMatchNum,
                                            VOS_UINT8         ucTotalNum)
{
    VOS_UINT32  ulOffset;
    VOS_UINT8   ucBit;
    VOS_UINT8   i;
    VOS_UINT8   usBitNo;
    VOS_UINT8   aucBitMap[32];

    /*lint -e534*/
    VOS_MemSet(pucReadString, (VOS_CHAR)0xFF, 256);
    /*lint +e534*/

    /* 如果一个匹配的记录都没有，则需要从头读到尾 */
    if (0 == usMatchNum)
    {
        for (i = 0; i < 254; i++)
        {
            *pucReadString++ = (i+1);
        }
        return;
    }

    /*lint -e534*/
    VOS_MemSet(aucBitMap, (VOS_CHAR)0xFF, sizeof(aucBitMap));
    /*lint +e534*/

    /* 把匹配结果对应的位都设置为零 */
    for (i = 0; i < usMatchNum; i++)
    {
        usBitNo     = pucSearchResult[i];
        ulOffset    = (usBitNo - 1) / 8;
        ucBit       = (VOS_UINT8)((usBitNo - 1) % 8);

        /*lint -e701 */
        aucBitMap[ulOffset] &= (~(VOS_UINT8)(0x1 << ucBit));
        /*lint +e701 */
    }

    /* 把不为零的位都取出来做为下一步读取的记录号 */
    for(i = 0; i < ucTotalNum; i++)
    {
        usBitNo     = i;
        ulOffset    = usBitNo / 8;
        ucBit       = (VOS_UINT8)(usBitNo % 8);

        /*lint -e701 */
        if ((aucBitMap[ulOffset] >> ucBit) & 0x1)
        /*lint +e701 */
        {
            *pucReadString++ = (i + 1);
        }
    }
}


/*****************************************************************************
函 数 名  : SI_PB_EMLContentProc
功能描述  : Email文件内容的处理函数，需要判断是否为TYPE2类型的文件。
            如果EMAIL文件的使用情况与IAP不一致，需要将内容中的EMAIL设置为
            未使用，并清空内容
输入参数  :
输出参数  :
返 回 值  :
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2010年01月20日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_EMLContentProc(USIMM_READFILE_CNF_STRU *pstPBMsg,
                                            VOS_UINT8               ucSuffix,
                                            VOS_UINT16              usEmailIndex)
{
    VOS_UINT32          ulResult = VOS_ERR;
    VOS_UINT32          ulIAPOffset;
    VOS_UINT32          ulEmlTag;
    VOS_UINT32          i;
    VOS_UINT16          usIAPRecordNum;
    VOS_UINT16          usIndex;

    /* 如果EMAIL文件是TYPE1类型的文件，直接使用usEmailIndex而不需要从IAP文件中去计算 */
    usIndex     = usEmailIndex;

    if (0xFF != pstPBMsg->aucEf[0])
    {
        if (PB_FILE_TYPE2 == gstPBCtrlInfo.astEMLInfo[ucSuffix].enEMLType)
        {
            /* 每组IAP文件的记录数可能不一致，需要从头开始累加 */
            usIAPRecordNum = 0;

            for (i = 0; i < ucSuffix; i++)
            {
                usIAPRecordNum += gstPBCtrlInfo.astIAPInfo[i].ucRecordNum;
            }

            ulEmlTag = gstPBCtrlInfo.astEMLInfo[ucSuffix].ulEMLTagNum;

            /* 如果没有IAP对应到该记录，则认为该记录无效 */
            for (i = 0; i < gstPBCtrlInfo.astIAPInfo[ucSuffix].ucRecordNum; i++)
            {
                ulIAPOffset = (usIAPRecordNum + i) * gstIAPContent.ucRecordLen;

                if (gstIAPContent.pIAPContent[ulIAPOffset +(ulEmlTag - 1)] == pstPBMsg->ucRecordNum)
                {
                    PB_INFO_LOG("Check IAP & EMAIL OK, Valid Record.");

                    gstEMLContent.usUsedNum++;

                    /* 获取该条Email记录对应的索引号 */
                    usIndex = (VOS_UINT16)(usIAPRecordNum + i + 1);

                    ulResult = VOS_OK;

                    break;
                }
            }
        }
        else
        {
            ulResult    = VOS_OK;
            gstEMLContent.usUsedNum++;
        }

        if (VOS_OK == ulResult)
        {
            if (SI_PB_CONTENT_INVALID == SI_PB_GetBitFromBuf(gastPBContent[PB_ADN_CONTENT].pIndex, usIndex))
            {
                gstPBCtrlInfo.ulTotalUsed++;

                SI_PB_SetBitToBuf(gastPBContent[PB_ADN_CONTENT].pIndex, usIndex, SI_PB_CONTENT_VALID);
            }
        }

        return ulResult;
    }
    else
    {
        return ulResult;
    }
}

/*****************************************************************************
函 数 名  :SI_PB_RefreshUIDFile_Stub
功能描述  :刷新UID文件内容的桩函数，用于在GCF测试的时候调用
输入参数  :无
输出参数  :无
返 回 值  :VOS_OK 解析成功
           VOS_ERR 解析失败
修订记录  :
1. 日    期   : 2007年10月15日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_RefreshUIDFile_Stub(VOS_UINT8 ucAdnIndex)
{
    VOS_UINT8                   aucIndex[2];
    VOS_UINT8                   i;
    VOS_UINT32                  ulResult;
    VOS_UINT16                  usIndex = 1;
    SI_PB_SETFILE_INFO_STRU     stUpdateReq;

    if(0xFFFF != gstPBCtrlInfo.usPUIDValue)
    {
        return;
    }

    aucIndex[0] = 0;

    aucIndex[1] = 1;

    for(i=1; i<=10; i++)
    {
        ulResult = SI_PB_GetBitFromBuf(gastPBContent[PB_ADN_CONTENT].pIndex, usIndex);

        if((ulResult == SI_PB_CONTENT_VALID)&&(i != ucAdnIndex))
        {
            stUpdateReq.pucEfContent    = aucIndex;
            stUpdateReq.ucRecordNum     = i;
            stUpdateReq.ulEfLen         = sizeof(aucIndex);
            stUpdateReq.usEfId          = gstPBCtrlInfo.astUIDInfo[0].usFileID;

            ulResult = SI_PB_SetFileReq(&stUpdateReq);

            if(VOS_OK != ulResult)
            {
                PB_ERROR_LOG("SI_PB_RefreshUIDFile_Stub: Update the UID File Failed");

                return;
            }

            aucIndex[1]++;
        }

        usIndex++;
    }

    gstPBCtrlInfo.usPUIDValue = gstPBCtrlInfo.usUIDMaxValue;

    aucIndex[1] = (VOS_UINT8)(gstPBCtrlInfo.usUIDMaxValue&0xFF);

    stUpdateReq.pucEfContent    = aucIndex;
    stUpdateReq.ucRecordNum     = 2;
    stUpdateReq.ulEfLen         = sizeof(aucIndex);
    stUpdateReq.usEfId          = EFPUID;

    ulResult = SI_PB_SetFileReq(&stUpdateReq);

    if(VOS_OK != ulResult)
    {
        PB_ERROR_LOG("SI_PB_RefreshUIDFile_Stub: Update the PUID File Failed");

        return;
    }

    stUpdateReq.pucEfContent    = aucIndex;
    stUpdateReq.ucRecordNum     = ucAdnIndex;
    stUpdateReq.ulEfLen         = sizeof(aucIndex);
    stUpdateReq.usEfId          = gstPBCtrlInfo.astUIDInfo[0].usFileID;

    ulResult = SI_PB_SetFileReq(&stUpdateReq);

    if(VOS_OK != ulResult)
    {
        PB_ERROR_LOG("SI_PB_RefreshUIDFile_Stub: Update the UID File Last Record Failed");

        return;
    }

    return;
}

/*****************************************************************************
函 数 名  :SI_PB_UpdateCCFile

功能描述  :更新电话本CC计数器和PSC计数器的内容

输入参数  :usIncValue:输入增加的计数器

输出参数  :无

返 回 值  :VOS_OK 解析成功
           VOS_ERR 解析失败

调用函数  :无

被调函数  :无

修订记录  :
1. 日    期   : 2007年10月15日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_VOID SI_PB_IncreaceCCValue(VOS_UINT16 usIncValue,VOS_UINT8 ucAdnIndex)
{
    VOS_UINT16                  usCCTemp;
    VOS_UINT8                   aucContent[4];
    SI_PB_SETFILE_INFO_STRU     stUpdateReq;

    /*USIM卡进入3G重同步*/
    if(USIMM_CARD_USIM != gstPBInitState.enCardType)
    {
        return;
    }

    usCCTemp  = usIncValue + gstPBCtrlInfo.usCCValue;

    if(usCCTemp < gstPBCtrlInfo.usCCValue)  /*由于发生的溢出造成了增加后的值小于原有值*/
    {
        gstPBCtrlInfo.usCCValue = 1;/*对于CC文件内容重新计算，每次从1而不是0开始计数，所以需要再增加1*/

        usCCTemp = 1;

        /*更新PSC的内容*/
        gstPBCtrlInfo.ulPSCValue++;
        gstPBCtrlInfo.ulPSCValue = ((0 == gstPBCtrlInfo.ulPSCValue) ? 1 : (gstPBCtrlInfo.ulPSCValue));

        aucContent[0] = (VOS_UINT8)((gstPBCtrlInfo.ulPSCValue>>24)&0x000000FF);
        aucContent[1] = (VOS_UINT8)((gstPBCtrlInfo.ulPSCValue>>16)&0x000000FF);
        aucContent[2] = (VOS_UINT8)((gstPBCtrlInfo.ulPSCValue>>8)&0x000000FF);
        aucContent[3] = (VOS_UINT8)(gstPBCtrlInfo.ulPSCValue&0x000000FF);

        stUpdateReq.pucEfContent    = aucContent;
        stUpdateReq.ucRecordNum     = 0;
        stUpdateReq.ulEfLen         = sizeof(aucContent);
        stUpdateReq.usEfId          = EFPSC;

        if(VOS_OK != SI_PB_SetFileReq(&stUpdateReq))
        {
            PB_ERROR_LOG("SI_PB_IncreaceCCValue: Update the EFPSC File is Error");
            return;
        }

        SI_PB_RefreshUIDFile_Stub(ucAdnIndex);    /*刷新UID的内容*/
    }

    aucContent[0] = (VOS_UINT8)((usCCTemp>>8)&0x00FF);
    aucContent[1] = (VOS_UINT8)(usCCTemp&0x00FF);

    stUpdateReq.pucEfContent    = aucContent;
    stUpdateReq.ucRecordNum     = 0;
    stUpdateReq.ulEfLen         = 2;
    stUpdateReq.usEfId          = EFCC;

    if(VOS_OK != SI_PB_SetFileReq(&stUpdateReq))
    {
        PB_ERROR_LOG("SI_PB_IncreaceCCValue: Update the EFCC File is Error");

        return;
    }

    return;
}

#ifdef __cplusplus
  #if __cplusplus
  }
  #endif
#endif



