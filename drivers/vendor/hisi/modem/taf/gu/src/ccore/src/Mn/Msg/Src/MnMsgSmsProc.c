

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "MnMsgInclude.h"
#include "siapppb.h"
#include "NVIM_Interface.h"
#include "MnMsgCtx.h"
#include "MnMsgProcNvim.h"

#include "NasGmmInterface.h"

#include "NasUsimmApi.h"

#include "MmCmInterface.h"

#include "TafSdcCtx.h"
#include "MnMsgSendSpm.h"
#include "TafStdlib.h"

#include "MnMsgSmCommProc.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "LmmSmsInterface.h"
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 常量定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_SMSPROC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/
#define MN_MSG_ACTIVE_MESSAGE_ENDSTR_NUM                    (3)
#define MN_MSG_ACTIVE_MESSAGE_ENDSTR_MAX_LEN                (3)
/*****************************************************************************
  3 变量定义
*****************************************************************************/
LOCAL MN_MSG_TS_DATA_INFO_STRU         f_stMsgTsData;
VOS_UINT8                              g_ucMnMsgAutoReply = 0;
LOCAL VOS_UINT32                       f_ulMsgMoNum = 0;
LOCAL VOS_UINT32                       f_ulMsgMtNum = 0;
#if ( VOS_WIN32 == VOS_OS_VER )
VOS_UINT8                               g_ucSetEfSmssClear = 0;
#endif

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/


LOCAL VOS_VOID  MN_MSG_GetCurrentLineLen(
    VOS_UINT8                           *pucOrgAddr,
    VOS_UINT32                          ulOrgLen,
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding,
    VOS_UINT32                          *pulCurrentLineLen,
    VOS_UINT32                          *pulLineLenWithOutEndFlag
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucLineEndStr[MN_MSG_ACTIVE_MESSAGE_ENDSTR_NUM][MN_MSG_ACTIVE_MESSAGE_ENDSTR_MAX_LEN]
                                            = {"\r\n", "\r", "\n"};
    VOS_UINT32                          ulLineLen;
    VOS_UINT8                           *pucEndFlagStr;
    VOS_BOOL                            bEqualFlag;
    VOS_INT8                            cRet;
    VOS_UINT32                          ulLineEndStrLen;

    /*输出参数初始化: 包含结束符或不包含结束符长度均赋值为输入字符串的总长度*/
    *pulCurrentLineLen          = ulOrgLen;
    *pulLineLenWithOutEndFlag   = ulOrgLen;

    /*循环变量初始化: 结束符首地址指向输入字符串首地址；行长度赋值为输入字符串的总长度*/
    pucEndFlagStr = pucOrgAddr;
    ulLineLen     = ulOrgLen;

    if (MN_MSG_MSG_CODING_UCS2 == enMsgCoding)
    {
        while (0 != ulLineLen)
        {
            /*UCS2编码: 检查是否存在行结束符<CR><LF>, <CR>, <LF>*/
            for (ulLoop = 0; ulLoop < MN_MSG_ACTIVE_MESSAGE_ENDSTR_NUM; ulLoop++)
            {
                MN_CmpAsciiStrAndUcs2StrCaseInsensitive(pucEndFlagStr,
                                                        ulLineLen,
                                                        aucLineEndStr[ulLoop],
                                                        &bEqualFlag);
                if (VOS_TRUE == bEqualFlag)
                {
                    *pulLineLenWithOutEndFlag = (VOS_UINT32)(pucEndFlagStr - pucOrgAddr);
                    *pulCurrentLineLen        = (VOS_UINT32)(*pulLineLenWithOutEndFlag
                                       + (VOS_UINT32)(VOS_StrLen((VOS_CHAR *)aucLineEndStr[ulLoop]) * 2));
                    return;
                }
            }

            pucEndFlagStr += MN_WORD_UCS2_ENCODE_LEN;
            ulLineLen     -= MN_WORD_UCS2_ENCODE_LEN;
        }

    }
    else
    {
        while (0 != ulLineLen)
        {
            /*ASCII编码: 检查是否存在行结束符<CR><LF>, <CR>, <LF>*/
            for (ulLoop = 0; ulLoop < MN_MSG_ACTIVE_MESSAGE_ENDSTR_NUM; ulLoop++)
            {
                ulLineEndStrLen = VOS_StrLen((VOS_CHAR *)aucLineEndStr[ulLoop]);
                if (ulLineLen < ulLineEndStrLen)
                {
                    continue;
                }

                cRet = VOS_StrNiCmp((VOS_CHAR *)pucEndFlagStr,
                                    (VOS_CHAR *)aucLineEndStr[ulLoop],
                                    ulLineEndStrLen);
                if (0 == cRet)
                {
                    *pulLineLenWithOutEndFlag = (VOS_UINT32)(pucEndFlagStr - pucOrgAddr);
                    *pulCurrentLineLen        = (VOS_UINT32)(*pulLineLenWithOutEndFlag
                                           + VOS_StrLen((VOS_CHAR *)aucLineEndStr[ulLoop]));
                    return;
                }
            }

            pucEndFlagStr++;
            ulLineLen--;
        }


    }

    return;
}


LOCAL VOS_VOID MN_MSG_IdentfyActiveMessage(
    const MN_MSG_DELIVER_STRU           *pstDeliver,
    VOS_BOOL                            *pbActiveMessage
)
{
    /*短信的CLASS类型不是CLASS1则输出短信不是激活短信*/
    /*短信的TP-PID类型不是TYPE0则输出短信不是激活短信*/
    if ((MN_MSG_TP_PID_SM_TYPE_0 == pstDeliver->enPid)
     && (MN_MSG_MSG_CLASS_1 == pstDeliver->stDcs.enMsgClass))
    {
        *pbActiveMessage = VOS_TRUE;
    }
    else
    {
        *pbActiveMessage = VOS_FALSE;
    }

    return;
}


LOCAL VOS_UINT32 MN_MSG_IdentifyActiveStatus(
    VOS_UINT8                                                   *pucOrgData,
    VOS_UINT32                                                  ulLineLen,
    MN_MSG_MSG_CODING_ENUM_U8                                   enMsgCoding,
    MN_MSG_ACTIVE_MESSAGE_STATUS_ENUM_UINT8                     *penActiveStatus
)
{
    VOS_BOOL                            pbEqualFlag;
    VOS_INT8                            cRet;

    /*UCS2编码情况下获取激活状态*/
    if (MN_MSG_MSG_CODING_UCS2 == enMsgCoding)
    {
        MN_CmpAsciiStrAndUcs2StrCaseInsensitive(pucOrgData,
                                                ulLineLen,
                                                (VOS_UINT8 *)"rs:on",
                                                &pbEqualFlag);
        if (VOS_TRUE == pbEqualFlag)
        {
            *penActiveStatus = MN_MSG_ACTIVE_MESSAGE_STATUS_ACTIVE;
            return VOS_OK;
        }

        MN_CmpAsciiStrAndUcs2StrCaseInsensitive(pucOrgData,
                                                ulLineLen,
                                                (VOS_UINT8 *)"rs:off",
                                                &pbEqualFlag);
        if (VOS_TRUE == pbEqualFlag)
        {
            *penActiveStatus = MN_MSG_ACTIVE_MESSAGE_STATUS_DEACTIVE;
            return VOS_OK;
        }

    }
    /*GSM7BIT 8BIT编码情况下获取激活状态*/
    else
    {
        cRet = VOS_StrNiCmp((VOS_CHAR *)pucOrgData, "rs:on", VOS_StrLen("rs:on"));
        if (0 == cRet)
        {
            *penActiveStatus = MN_MSG_ACTIVE_MESSAGE_STATUS_ACTIVE;
            return VOS_OK;
        }

        cRet = VOS_StrNiCmp((VOS_CHAR *)pucOrgData, "rs:off", VOS_StrLen("rs:off"));
        if (0 == cRet)
        {
            *penActiveStatus = MN_MSG_ACTIVE_MESSAGE_STATUS_DEACTIVE;
            return VOS_OK;
        }

    }

    return VOS_ERR;
}


LOCAL VOS_UINT32 MN_MSG_GetActiveStatus(
    const VOS_UINT8                                             *pucMsgData,
    VOS_UINT32                                                  ulMsgLen,
    MN_MSG_MSG_CODING_ENUM_U8                                   enMsgCoding,
    MN_MSG_ACTIVE_MESSAGE_STATUS_ENUM_UINT8                     *penActiveStatus
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           *pucOrgData;                            /*sms content,not 7bit,all 8bit */
    VOS_UINT32                          ulLineLen;
    VOS_UINT32                          ulCurrentLineLen;
    VOS_UINT32                          ulLineLenWithOutEndFlag;
    VOS_UINT8                           *pucStatusStr;


    ulLineLen = 0;


    pucOrgData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_TAF, ulMsgLen);
    if (VOS_NULL_PTR == pucOrgData)
    {
        MN_WARN_LOG("MN_MSG_GetActiveStatus:fail to alloc memory. ");
        return MN_ERR_NOMEM;
    }

    /*对短信内容进行7BIT到ASCII码的转换*/
    if (MN_MSG_MSG_CODING_7_BIT == enMsgCoding)
    {
        TAF_STD_ConvertDefAlphaToAscii(pucMsgData, ulMsgLen, pucOrgData, &ulLineLen);
    }
    else
    {
        PS_MEM_CPY(pucOrgData, pucMsgData, ulMsgLen);
        ulLineLen = ulMsgLen;
    }

    /*获取激活短信状态字段: 判断当前字符串是否"rs:on"或"rs:off"，不区分大小写
      若包含"rs:on"或"rs:off", 则获取操作成;
      否则,获取操作失败;
    */
    pucStatusStr = pucOrgData;
    while (0 != ulLineLen)
    {
        /*确认当前字段是否激活短信状态字段*/
        ulRet = MN_MSG_IdentifyActiveStatus(pucStatusStr,
                                            ulLineLen,
                                            enMsgCoding,
                                            penActiveStatus);
        if (VOS_OK == ulRet)
        {
            PS_MEM_FREE(WUEPS_PID_TAF, pucOrgData);
            return MN_ERR_NO_ERROR;
        }

        /*获取下一个信息行的行首并返回剩余字段长度;*/
        MN_MSG_GetCurrentLineLen(pucStatusStr,
                               ulLineLen,
                               enMsgCoding,
                               &ulCurrentLineLen,
                               &ulLineLenWithOutEndFlag);

        pucStatusStr    += ulCurrentLineLen;
        ulLineLen       -= ulCurrentLineLen;
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pucOrgData);
    return MN_ERR_UNSPECIFIED;
}


LOCAL VOS_UINT32 MN_MSG_GetActiveUrl(
    const VOS_UINT8                     *pucMsgData,
    VOS_UINT32                          ulMsgLen,
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding,
    MN_MSG_ACTIVE_MESSAGE_URL_STRU      *pstUrl
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulStrLen;
    VOS_UINT8                           *pucUrlStr;
    VOS_UINT8                           *pucOrgData;                            /*sms content,not 7bit,all 8bit */
    VOS_UINT32                          ulLineLen;
    VOS_UINT32                          ulCurrentLineLen;
    VOS_UINT32                          ulLineLenWithOutEndFlag;
    VOS_BOOL                            bEqualFlag;
    VOS_INT8                            cRet;


    ulLineLen = 0;


    pucOrgData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_TAF, ulMsgLen);
    if (VOS_NULL_PTR == pucOrgData)
    {
        return MN_ERR_NOMEM;
    }

    /*对短信内容进行7BIT到ASCII码的转换*/
    if (MN_MSG_MSG_CODING_7_BIT == enMsgCoding)
    {
        TAF_STD_ConvertDefAlphaToAscii(pucMsgData, ulMsgLen, pucOrgData, &ulLineLen);
    }
    else
    {
        PS_MEM_CPY(pucOrgData, pucMsgData, ulMsgLen);
        ulLineLen = ulMsgLen;
    }

    /*获取激活短信状态字段: 判断当前字符串是否"url:"，不区分大小写
      若包含"url:", 则获取操作成;      否则,获取操作失败;    */
    bEqualFlag  = VOS_FALSE;
    ulStrLen    = VOS_StrLen("url:");
    pucUrlStr   = pucOrgData;
    while (0 != ulLineLen)
    {
        /*确认当前字段是否激活短信状态字段*/
        if (MN_MSG_MSG_CODING_UCS2 == enMsgCoding)
        {
            MN_CmpAsciiStrAndUcs2StrCaseInsensitive(pucUrlStr,
                                                    ulLineLen,
                                                    (VOS_UINT8 *)"url:",
                                                    &bEqualFlag);
            if (VOS_TRUE == bEqualFlag)
            {
                pucUrlStr += (2 * ulStrLen);
                ulLineLen -= (2 * ulStrLen);
                break;
            }

        }
        else
        {
            cRet = VOS_StrNiCmp((VOS_CHAR *)pucUrlStr, "url:", ulStrLen);
            if (0 == cRet)
            {
                bEqualFlag = VOS_TRUE;
                pucUrlStr += ulStrLen;
                ulLineLen -= ulStrLen;
                break;
            }

        }

        /*获取下一个信息行的行首并返回剩余字段长度;*/
        MN_MSG_GetCurrentLineLen(pucUrlStr,
                                 ulLineLen,
                                 enMsgCoding,
                                 &ulCurrentLineLen,
                                 &ulLineLenWithOutEndFlag);

        ulLineLen -= ulCurrentLineLen;
        pucUrlStr += ulCurrentLineLen;
    }

    if (VOS_TRUE == bEqualFlag)
    {
        /*获取URL可能的最大长度*/
        MN_MSG_GetCurrentLineLen(pucUrlStr,
                                 ulLineLen,
                                 enMsgCoding,
                                 &ulCurrentLineLen,
                                 &pstUrl->ulLen);

        /*填写URL到输出参数*/
        PS_MEM_CPY(pstUrl->aucUrl, pucUrlStr, pstUrl->ulLen);
        ulRet = MN_ERR_NO_ERROR;
    }
    else
    {
        ulRet = MN_ERR_UNSPECIFIED;
    }


    PS_MEM_FREE(WUEPS_PID_TAF, pucOrgData);
    return ulRet;
}


VOS_UINT32 MN_MSG_WriteActiveMessage(
    MN_MSG_ACTIVE_MESSAGE_STRU          *pstOrgActiveMessageInfo,
    MN_MSG_ACTIVE_MESSAGE_STRU          *pstActiveMessageInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_INT32                           lRet;
    VOS_UINT8                           *pucActiveMessageInfo;
    VOS_UINT8                           *pucEvaluate;

    /*1.判断待写入的激活短信参数与NVIM中的参数是否一致；一致则不用写NVIM直接退出*/
    if (pstOrgActiveMessageInfo->enActiveStatus == pstActiveMessageInfo->enActiveStatus)
    {
        if (pstOrgActiveMessageInfo->stUrl.ulLen == pstActiveMessageInfo->stUrl.ulLen)
        {
            if (pstOrgActiveMessageInfo->enMsgCoding == pstActiveMessageInfo->enMsgCoding)
            {
                lRet = VOS_MemCmp(pstOrgActiveMessageInfo->stUrl.aucUrl,
                                   pstActiveMessageInfo->stUrl.aucUrl,
                                   pstActiveMessageInfo->stUrl.ulLen);
                if (0 == lRet)
                {
                    return MN_ERR_NO_ERROR;
                }
            }
        }
    }

    /*2.写激活短信参数到NVIM中*/
    /*2.1 为NVIM存储的数据流申请内存*/
    pucActiveMessageInfo = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                     MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    if (VOS_NULL_PTR == pucActiveMessageInfo)
    {
        return MN_ERR_NOMEM;
    }

    /*2.2 将激活短信参数数据结构转换成NVIM存储的数据流*/
    pucEvaluate = pucActiveMessageInfo;
    *pucEvaluate = pstActiveMessageInfo->enActiveStatus;
    pucEvaluate++;

    *pucEvaluate = pstActiveMessageInfo->enMsgCoding;
    pucEvaluate++;

    *pucEvaluate = (VOS_UINT8)(pstActiveMessageInfo->stUrl.ulLen & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 8) & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 16) & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 24) & 0xff);
    pucEvaluate++;

    PS_MEM_CPY(pucEvaluate,
               pstActiveMessageInfo->stUrl.aucUrl,
               pstActiveMessageInfo->stUrl.ulLen);

    /*2.3 写激活短信信息到NVIM*/
    ulRet = NV_Write(en_NV_Item_SMS_ActiveMessage_Para,
                     pucActiveMessageInfo,
                     MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    if (NV_OK != ulRet)
    {
        ulRet = MN_ERR_CLASS_SMS_NVIM;
    }
    else
    {
        ulRet = MN_ERR_NO_ERROR;
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pucActiveMessageInfo);
    return ulRet;
}


VOS_UINT32 MN_MSG_ReadActiveMessage(
    MN_MSG_ACTIVE_MESSAGE_STRU          *pstActiveMessage
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           *pucActiveMessageInfo;
    VOS_UINT8                           *pucEvaluate;

    pucActiveMessageInfo = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                     MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    if (VOS_NULL_PTR == pucActiveMessageInfo)
    {
        MN_WARN_LOG("MN_MSG_ReadActiveMessage : fail to alloc memory . ");
        return MN_ERR_NOMEM;
    }

    ulRet = NV_Read(en_NV_Item_SMS_ActiveMessage_Para,
                    pucActiveMessageInfo,
                    MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    if (NV_OK != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ReadActiveMessage : fail to read NVIM . ");
        PS_MEM_FREE(WUEPS_PID_TAF, pucActiveMessageInfo);
        return MN_ERR_CLASS_SMS_NVIM;
    }

    pucEvaluate = pucActiveMessageInfo;

    pstActiveMessage->enActiveStatus = *pucEvaluate;
    pucEvaluate++;

    pstActiveMessage->enMsgCoding   = *pucEvaluate;
    pucEvaluate++;

    /*lint -e701*/
    pstActiveMessage->stUrl.ulLen   = *pucEvaluate;
    pucEvaluate++;
    pstActiveMessage->stUrl.ulLen  |= *pucEvaluate << 8;
    pucEvaluate++;
    pstActiveMessage->stUrl.ulLen  |= *pucEvaluate << 16;
    pucEvaluate++;
    pstActiveMessage->stUrl.ulLen  |= *pucEvaluate << 24;
    pucEvaluate++;
    /*lint +e701*/

    if (pstActiveMessage->stUrl.ulLen > MN_MSG_ACTIVE_MESSAGE_MAX_URL_LEN)
    {
        MN_WARN_LOG("MN_MSG_ReadActiveMessage : fail to read NVIM . ");
        pstActiveMessage->stUrl.ulLen = MN_MSG_ACTIVE_MESSAGE_MAX_URL_LEN;
    }

    PS_MEM_CPY(pstActiveMessage->stUrl.aucUrl,
               pucEvaluate,
               pstActiveMessage->stUrl.ulLen);

    PS_MEM_FREE(WUEPS_PID_TAF, pucActiveMessageInfo);
    return MN_ERR_NO_ERROR;
}


LOCAL VOS_VOID MN_MSG_GetAndSaveActiveMessageInfo(
    const MN_MSG_DELIVER_STRU           *pstDeliver
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulRemainder;
    VOS_BOOL                            bActiveMessage;
    MN_MSG_ACTIVE_MESSAGE_STRU          stActiveMessageInfo;
    MN_MSG_ACTIVE_MESSAGE_STRU          stOrgActiveMessageInfo;

    /*If (MN_MSG_IdentfyActiveMessage为假)        Return; */
    MN_MSG_IdentfyActiveMessage(pstDeliver, &bActiveMessage);
    if (VOS_TRUE != bActiveMessage)
    {
        MN_INFO_LOG("MN_MSG_GetAndSaveActiveMessageInfo :not a active message. ");
        return;
    }

    /*记录短信的内容的编码格式: 此处已完成了GSM7bit到8BIT的转换*/
    if (MN_MSG_MSG_CODING_UCS2 == pstDeliver->stDcs.enMsgCoding)
    {
        ulRemainder = pstDeliver->stUserData.ulLen % MN_WORD_UCS2_ENCODE_LEN;
        if (0 != ulRemainder)
        {
            return;
        }

        stActiveMessageInfo.enMsgCoding = MN_MSG_MSG_CODING_UCS2;
    }
    else
    {
        stActiveMessageInfo.enMsgCoding = MN_MSG_MSG_CODING_8_BIT;
    }

    /*MN_MSG_GetActiveStatus获取激活状态信息失败        Return; */
    ulRet = MN_MSG_GetActiveStatus(pstDeliver->stUserData.aucOrgData,
                                   pstDeliver->stUserData.ulLen,
                                   pstDeliver->stDcs.enMsgCoding,
                                   &stActiveMessageInfo.enActiveStatus);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_INFO_LOG("MN_MSG_GetAndSaveActiveMessageInfo :no active status. ");
        return;
    }

    ulRet = MN_MSG_ReadActiveMessage(&stOrgActiveMessageInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return;
    }

    /*MN_MSG_GetActiveUrl获取激活短信URL信息*/
    ulRet = MN_MSG_GetActiveUrl(pstDeliver->stUserData.aucOrgData,
                                pstDeliver->stUserData.ulLen,
                                pstDeliver->stDcs.enMsgCoding,
                                &stActiveMessageInfo.stUrl);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        /*获取NVIM中记录的激活短信参数*/
        PS_MEM_CPY(&stActiveMessageInfo.stUrl,
                   &stOrgActiveMessageInfo.stUrl,
                   sizeof(stActiveMessageInfo.stUrl));
        stActiveMessageInfo.enMsgCoding = stOrgActiveMessageInfo.enMsgCoding;
    }

    /*记录短信的内容的编码格式: 此处已完成了GSM7bit到8BIT的转换*/
    /*MN_MSG_WriteActiveMessage写激活短信的激活状态和URL信息到NVIM；*/
    ulRet = MN_MSG_WriteActiveMessage(&stOrgActiveMessageInfo, &stActiveMessageInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_GetAndSaveActiveMessageInfo:Fail to Write NVIM.");
    }

    return;

}


LOCAL VOS_VOID MSG_DecodeRpData(
    const VOS_UINT8                     *pucRpduContent,
    MN_MSG_RP_DATA_STRU                 *pstRpData
)
{
    VOS_UINT32                          ucIdx = 0;

    /*lint -e961*/
    pstRpData->ucRpMsgType = pucRpduContent[ucIdx++];
    pstRpData->ucRpMr = pucRpduContent[ucIdx++];
    if (pucRpduContent[ucIdx] > 0)
    {
        pstRpData->stOrgAddr.ucBcdLen = pucRpduContent[ucIdx++] - 1;
        pstRpData->stOrgAddr.addrType = pucRpduContent[ucIdx++];
        PS_MEM_CPY(pstRpData->stOrgAddr.aucBcdNum,pucRpduContent+ucIdx,pstRpData->stOrgAddr.ucBcdLen);
        ucIdx += pstRpData->stOrgAddr.ucBcdLen;
    }
    else
    {
        pstRpData->stOrgAddr.ucBcdLen = 0;
        ucIdx++;
    }
    /*lint +e961*/

    if (pucRpduContent[ucIdx] > 0)
    {
        /*lint -e961*/
        pstRpData->stDestAddr.ucBcdLen = pucRpduContent[ucIdx++] - 1;
        pstRpData->stDestAddr.addrType = pucRpduContent[ucIdx++];
        /*lint +e961*/
        PS_MEM_CPY(pstRpData->stDestAddr.aucBcdNum,pucRpduContent+ucIdx,pstRpData->stDestAddr.ucBcdLen);
        ucIdx += pstRpData->stDestAddr.ucBcdLen;
    }
    else
    {
        pstRpData->stDestAddr.ucBcdLen = 0;
        ucIdx++;
    }
    /*lint -e961*/
    pstRpData->ucRpUserDataLen = pucRpduContent[ucIdx++];
    /*lint +e961*/
    PS_MEM_CPY(pstRpData->aucRpUserData,pucRpduContent + ucIdx,pstRpData->ucRpUserDataLen);
}



LOCAL VOS_VOID MSG_DecodeRpAck(
    const VOS_UINT8                     *pucRpduContent,
    VOS_UINT8                           ucRpduvLen,
    MN_MSG_RP_ACK_STRU                  *pstRpAck
)
{
    VOS_UINT32                          ucIdx = 0;
    /*lint -e961*/
    pstRpAck->ucRpMsgType = pucRpduContent[ucIdx++];
    pstRpAck->ucRpMr = pucRpduContent[ucIdx++];
    if ((ucRpduvLen > 3)
     && (MN_MSG_RP_USER_DATA_IEI == pucRpduContent[ucIdx]))
    {
        pstRpAck->bRpUserDataExist = VOS_TRUE;
        pstRpAck->ucRpUserDataIei = MN_MSG_RP_USER_DATA_IEI;
        ucIdx++;
        pstRpAck->ucRpUserDataLen = pucRpduContent[ucIdx++];
        PS_MEM_CPY(pstRpAck->aucRpUserData,pucRpduContent + ucIdx,pstRpAck->ucRpUserDataLen);
    }
    else
    {
        pstRpAck->bRpUserDataExist = VOS_FALSE;
    }
    /*lint +e961*/
}


LOCAL VOS_VOID MSG_DecodeRpErr(
    const VOS_UINT8                     *pucRpduContent,
    VOS_UINT8                           ucRpduvLen,
    MN_MSG_RP_ERR_STRU                  *pstRpErr
)
{
    VOS_UINT32                          ucIdx = 0;
    /*lint -e961*/
    pstRpErr->ucRpMsgType = pucRpduContent[ucIdx++];
    pstRpErr->ucRpMr = pucRpduContent[ucIdx++];
    pstRpErr->ucRpCauseLen = pucRpduContent[ucIdx++];
    pstRpErr->stRpCause.enRpCause = pucRpduContent[ucIdx++];
    if (1 == pstRpErr->ucRpCauseLen)
    {
        pstRpErr->stRpCause.bDiagnosticsExist = VOS_FALSE;
    }
    else
    {
        pstRpErr->stRpCause.bDiagnosticsExist = VOS_TRUE;
        pstRpErr->stRpCause.ucDiagnostics = pucRpduContent[ucIdx++];
    }
    if ((ucRpduvLen > (ucIdx + 1))
     && (MN_MSG_RP_USER_DATA_IEI == pucRpduContent[ucIdx]))
    {
        pstRpErr->bRpUserDataExist = VOS_TRUE;
        pstRpErr->ucRpUserDataIei = MN_MSG_RP_USER_DATA_IEI;
        ucIdx++;
        pstRpErr->ucRpUserDataLen= pucRpduContent[ucIdx++];
        PS_MEM_CPY(pstRpErr->aucRpUserData,pucRpduContent + ucIdx,pstRpErr->ucRpUserDataLen);
    }
    else
    {
        pstRpErr->bRpUserDataExist = VOS_FALSE;
    }
    /*lint +e961*/
}


LOCAL MN_MSG_RETRY_FLAG_U8 MSG_JudgeRetryFlg(VOS_VOID)
{
    MN_MSG_RETRY_INFO_STRU              stRetryInfo;
    VOS_UINT32                          ulRemainTimeTick;

    PS_MEM_SET(&stRetryInfo, 0, sizeof(stRetryInfo));

    MN_MSG_GetRetryInfo(&stRetryInfo);

    /* 当前没有设置重发 */
    if ((0 == stRetryInfo.ulRetryPeriod) || (0 == stRetryInfo.ulRetryInterval))
    {
        return MN_MSG_RETRY_OFF;
    }

    ulRemainTimeTick = MN_MSG_GetTimerRemainTime(MN_MSG_ID_WAIT_RETRY_PERIOD);
    if (ulRemainTimeTick == 0)
    {
        return MN_MSG_RETRY_END;
    }

    if (((VOS_INT32)(ulRemainTimeTick - stRetryInfo.ulRetryInterval)) <= 0)
    {
        return MN_MSG_RETRY_END;
    }

    return MN_MSG_RETRY_BEGIN;
}


PS_BOOL_ENUM_UINT8 MSG_CheckSmsTpErrorRetry(
    VOS_UINT32                          ulFailCause
)
{
    VOS_UINT32                          ulCause;
    PS_BOOL_ENUM_UINT8                  enRet;

    enRet = PS_TRUE;

    /* 判断是否是TP ERROR */
    if (TAF_MSG_ERROR_TP_ERROR_BEGIN  != (ulFailCause & TAF_MSG_ERROR_TP_ERROR_BEGIN))
    {
        return PS_TRUE;
    }

    ulCause = ulFailCause & (~TAF_MSG_ERROR_TP_ERROR_BEGIN);

    switch(ulCause)
    {
        /* 拒绝原因为 SM Rejected-Duplicate SM 则不需要重发 */
        case MN_MSG_TP_CAUSE_REJECTED_DUPLICATE_SM:
            enRet = PS_FALSE;
            break;

        default:
            enRet = PS_TRUE;
            break;
    }

    return enRet;
}



LOCAL VOS_BOOL MSG_IsProcessRetry(
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    SMR_SMT_ERROR_ENUM_UINT32           enErrCause,
    VOS_UINT32                          ulMoFailCause
)
{
    MN_MSG_RETRY_FLAG_U8                enRetryFlg = MN_MSG_RETRY_OFF;
    VOS_UINT32                          ulRet;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enOldSendDomain;

    /* 判断TP 错误原因值是否需要重试 */
    if ( PS_FALSE == MSG_CheckSmsTpErrorRetry(ulMoFailCause))
    {
        return VOS_FALSE;
    }

    enRetryFlg = MSG_JudgeRetryFlg();


    /* 当前NV未开启重发，判断是否需要通过另一个域进行发送 */
    if (MN_MSG_RETRY_OFF == enRetryFlg)
    {
        /* 重发存在两种情况,一个域发送失败通过另外一个域发送,
        但当CS域发送失败后,PS域发送成功,此时会先通过PS域发送
        PS域发送失败了,仍然需要通过CS域发送*/
        /* 重发功能关闭,判断是否需要重另外一个域发送 */
        if ( ((MN_MSG_SEND_DOMAIN_PS_PREFERRED == pstMoEntity->enHopeSendDomain)
            && (MN_MSG_SEND_DOMAIN_PS == pstMoEntity->enSendDomain))
          ||((MN_MSG_SEND_DOMAIN_CS_PREFERRED == pstMoEntity->enHopeSendDomain)
            && (MN_MSG_SEND_DOMAIN_CS == pstMoEntity->enSendDomain)))
        {
            enOldSendDomain = pstMoEntity->enSendDomain;
            MN_MSG_GetCurSendDomain(pstMoEntity->enHopeSendDomain,&(pstMoEntity->enSendDomain));
            /* 获取新的发送域和老的不一致才需要进行重发 */
            if (MN_MSG_SEND_DOMAIN_NO != pstMoEntity->enSendDomain)
            {
                if (pstMoEntity->enSendDomain != enOldSendDomain)
                {
                    /* TAF层重发的SUBMIT短信TP-RD应该修改为1，指示短信中心拒绝接收重复短信 */
                    MN_MSG_SetTpRd(pstMoEntity);

                    /*将一条完整的RP-Data发送给NAS层的SMS模块*/
                    ulRet = MN_MSG_SendSmsRpDataReq(pstMoEntity->enSendDomain,
                                                    pstMoEntity->aucRpDataInfo,
                                                    pstMoEntity->ucRpDataLen,
                                                    pstMoEntity->enMsgSignallingType);

                    if (VOS_OK == ulRet)
                    {
                        /* 更新MO变量 */
                        MN_MSG_CreateMoInfo(pstMoEntity);
                        return VOS_TRUE;
                    }
                }
            }
        }

        return VOS_FALSE;
    }

    if ( (VOS_TRUE          == MN_MSG_IsGuNeedSmsRetry(enErrCause))
      && (MN_MSG_RETRY_BEGIN == enRetryFlg) )
    {
        /* 需要进行重发,启动重发间隔定时器,定时器超时后再进行重发 */
        MN_MSG_StartTimer(MN_MSG_ID_WAIT_RETRY_INTERVAL, 0);

        return VOS_TRUE;
    }

    /* 重发过程结束,不需要进行任何操作,停止定时器 */
    MN_MSG_StopTimer(MN_MSG_ID_WAIT_RETRY_PERIOD);

    MN_MSG_StopTimer(MN_MSG_ID_WAIT_RETRY_INTERVAL);

    return VOS_FALSE;


}



LOCAL VOS_VOID MSG_CreateEFSmsrContent(
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucContent
)
{
    *pucContent = ucIndex;
    if (pstRawData->ulLen > (MN_MSG_EFSMSR_LEN - 1))
    {
        PS_MEM_CPY(pucContent + 1,pstRawData->aucData,MN_MSG_EFSMSR_LEN - 1);
    }
    else
    {
        PS_MEM_CPY(pucContent + 1,pstRawData->aucData,pstRawData->ulLen);
    }
}


LOCAL VOS_UINT32 MSG_FindReplaceSms(
    const MN_MSG_ASCII_ADDR_STRU       *pstOrigAddr,
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRecCount;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT8                           ucScaLen;                               /* Sca的长度 */
    VOS_UINT8                           *pucTpdu;                               /* 指向Tpdu的指针 */
    MN_MSG_RAW_TS_DATA_STRU             stRawData;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo;

    ucStatus = EF_SMS_STATUS_FREE_SPACE;
    pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                             sizeof(MN_MSG_TS_DATA_INFO_STRU));
    if (VOS_NULL_PTR == pstTsDataInfo)
    {
        return VOS_ERR;
    }

    ulRecCount = MN_MSG_GetSmCapacity(enMemStore);
    for (i = 0; i < ulRecCount; i++)
    {
        PS_MEM_SET(&stRawData,0X00,sizeof(stRawData));
        PS_MEM_SET(pstTsDataInfo,0X00,sizeof(MN_MSG_TS_DATA_INFO_STRU));
        ulRet = MN_MSG_GetStatus(enMemStore,i,&ucStatus);
        if ((MN_ERR_NO_ERROR == ulRet)
         && (((ucStatus & 0x03) == EF_SMS_STATUS_MT_READ)
          || ((ucStatus & 0x03) == EF_SMS_STATUS_MT_TO_BE_READ)))
        {

            PS_MEM_SET(aucSmContent, 0x00, sizeof(aucSmContent));

            ulRet = MN_MSG_ReadSmsInfo(enMemStore,i,aucSmContent);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                continue;
            }

            ucScaLen = aucSmContent[1];
            pucTpdu = aucSmContent + 1 + 1 + ucScaLen;
            if ( MN_MSG_TP_MTI_DELIVER != ( *pucTpdu & 0x03 ))
            {
                continue;
            }
            stRawData.enTpduType = MN_MSG_TP_MTI_DELIVER;
            stRawData.ulLen = (MN_MSG_EFSMS_LEN - ucScaLen) - 1;


            if ( stRawData.ulLen > sizeof(stRawData.aucData) )
            {
                stRawData.ulLen = sizeof(stRawData.aucData);
            }

            PS_MEM_CPY(stRawData.aucData,pucTpdu,stRawData.ulLen);
            ulRet = MN_MSG_Decode(&stRawData,pstTsDataInfo);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                continue;
            }
            ulRet = (VOS_UINT32)VOS_MemCmp(pstOrigAddr, &(pstTsDataInfo->u.stDeliver.stOrigAddr),sizeof(MN_MSG_ASCII_ADDR_STRU));
            if ((enPid == pstTsDataInfo->u.stDeliver.enPid)
             && (0 == ulRet))
            {
                *pulIndex = i;
                PS_MEM_FREE(WUEPS_PID_TAF, pstTsDataInfo);
                return VOS_OK;
            }
        }
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstTsDataInfo);

    return VOS_ERR;
}


LOCAL VOS_UINT32 MSG_SearchReplacedSms(
    const MN_MSG_ASCII_ADDR_STRU       *pstOrigAddr,
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid,
    MN_MSG_MEM_STORE_ENUM_U8           *penMemStore,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucActFlg;

    MN_MSG_GetReplaceFeature(&ucActFlg);
    if (MN_MSG_NVIM_ITEM_ACTIVE != ucActFlg)
    {
        return VOS_ERR;
    }

    ulRet = MSG_FindReplaceSms(pstOrigAddr, enPid, MN_MSG_MEM_STORE_SIM, pulIndex);
    if (VOS_OK == ulRet)
    {
        *penMemStore = MN_MSG_MEM_STORE_SIM;
        return VOS_OK;
    }

    ulRet = MSG_FindReplaceSms(pstOrigAddr, enPid, MN_MSG_MEM_STORE_NV, pulIndex);
    if (VOS_OK == ulRet)
    {
        *penMemStore = MN_MSG_MEM_STORE_NV;
        return VOS_OK;
    }

    return VOS_ERR;
}


VOS_UINT32 MSG_ProcReplaceSm(
    const MN_MSG_CONFIG_PARM_STRU       *pstCfgParm,
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSaveIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MN_OPERATION_ID_T                   bcopId;
#endif
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#else
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
#endif
    MN_MSG_DELIVER_EVT_INFO_STRU        stDeliverEvt;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    /* 短信不是Replace类型的，返回VOS_FALSE   不是替换属性短信，或没有可替换的短信 */
    if (((MN_MSG_TP_PID_REPLACE_SM_1 <= (VOS_UINT8)pstTsData->u.stDeliver.enPid )
       && (MN_MSG_TP_PID_REPLACE_SM_7 >= (VOS_UINT8)pstTsData->u.stDeliver.enPid))
      || (MN_MSG_TP_PID_RETURN_CALL == (VOS_UINT8)pstTsData->u.stDeliver.enPid))
    {
        ;
    }
    else
    {
        return VOS_FALSE;
    }

    /* 没有可替换的短信，返回VOS_FALSE   不是替换属性短信，或没有可替换的短信 */
    /* 此处需要对比标杆确认是否遍历所有MODEM的存储介质 */
    ulRet = MSG_SearchReplacedSms(&(pstTsData->u.stDeliver.stOrigAddr),
                                  pstTsData->u.stDeliver.enPid,
                                  &enMemStore,
                                  &ulSaveIndex);
    if (VOS_OK != ulRet)
    {
        return VOS_FALSE;
    }

    MN_MSG_CreateEFSmContent(pstScAddr,
                             pstRawData,
                             EF_SMS_STATUS_MT_TO_BE_READ,
                             aucSmContent);

    /* 用新收到的短信替换已经存储短信 */
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
|| (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
    PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
    stSmaUsimInfo.clientId = MN_CLIENT_ALL;
    stSmaUsimInfo.opId = 0;
    stSmaUsimInfo.usEfId = ulFileId;
    stSmaUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
    stSmaUsimInfo.ucRecIndex = (VOS_UINT8)ulSaveIndex;
    stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVNEWMSG;
    ulRet = MN_MSG_WriteSmsFile(enMemStore,VOS_TRUE,&stSmaUsimInfo,aucSmContent);
#else
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
        stWriteUsimInfo.stUsimInfo.clientId = MN_CLIENT_ALL;
        stWriteUsimInfo.stUsimInfo.opId = 0;
        stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
        stWriteUsimInfo.stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)ulSaveIndex;
        stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVNEWMSG;
        stWriteUsimInfo.bCreateNode = VOS_TRUE;
        ulRet = MN_MSG_WriteSmsFile(enMemStore, VOS_NULL_PTR, &stWriteUsimInfo, aucSmContent);

    }
    else
    {
        ulRet = MN_MSG_WriteSmsFile(enMemStore, &ulSaveIndex, VOS_NULL_PTR, aucSmContent);
    }
#endif

    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_MSG_Internal_SendRpt(VOS_FALSE,
                                MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                MN_MSG_TP_CAUSE_ERR_IN_MS);
        MN_WARN_LOG("MSG_ProcStoreSm:MN_MSG_WriteSmsFile Return Error");
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == pstCfgParm->enSmMemStore)
    {
        MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
        /*广播上报来一条短信*/
        bcopId = MN_MSG_GetBCopId();
        stDeliverEvt.ulInex = ulSaveIndex;
        MN_MSG_ReportRcvMsgEvent(bcopId,&stDeliverEvt);
        /*广播上报NVIM中短信已发生了改变*/
        MN_MSG_ReportSmChanged(MN_CLIENT_ALL,bcopId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
    }
#endif
    else
    {
    }

    return VOS_TRUE;
}


LOCAL VOS_VOID MSG_ProcClass2Msg(
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData
)
{
    VOS_UINT32                          ulSaveIndex;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#else
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
#endif
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    MN_INFO_LOG("MSG_ProcClass2Msg: step into function. ");
    PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);

    ulSaveIndex = MN_MSG_GetAvailSmRecIndex(MN_MSG_MEM_STORE_SIM);

    /*当前USIM卡已满 (此处参考协议23038)*/
    MN_NORM_LOG1("MSG_ProcClass2Msg: ucSaveIndex is ", (VOS_INT32)ulSaveIndex);
    if (MN_MSG_NO_AVAILABLE_SMS_REC != ulSaveIndex)
    {
        MN_MSG_CreateEFSmContent(pstScAddr,
                                 pstRawData,
                                 EF_SMS_STATUS_MT_TO_BE_READ,
                                 aucSmContent);

#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
  || (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
        PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
        stSmaUsimInfo.clientId = MN_CLIENT_ALL;
        stSmaUsimInfo.opId = 0;
        stSmaUsimInfo.usEfId = ulFileId;
        stSmaUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stSmaUsimInfo.ucRecIndex = ulSaveIndex;
        stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVNEWMSG;
        ulRet = MN_MSG_WriteSmsFile(MN_MSG_MEM_STORE_SIM,VOS_TRUE,&stSmaUsimInfo,aucSmContent);
#else
        PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
        stWriteUsimInfo.stUsimInfo.clientId = MN_CLIENT_ALL;
        stWriteUsimInfo.stUsimInfo.opId = 0;
        stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
        stWriteUsimInfo.stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)ulSaveIndex;
        stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVNEWMSG;
        stWriteUsimInfo.bCreateNode = VOS_TRUE;
        ulRet = MN_MSG_WriteSmsFile(MN_MSG_MEM_STORE_SIM,VOS_NULL_PTR,&stWriteUsimInfo,aucSmContent);

#endif

        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_MSG_Internal_SendRpt(VOS_FALSE,
                                    MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                    MN_MSG_TP_CAUSE_ERR_IN_MS);
            MN_WARN_LOG("MSG_ProcClass2Msg:Save Class 2 in Usim Error");
        }
        return;
    }

    MN_MSG_FailToWriteEfsms(MN_MSG_MEM_STORE_SIM, MN_MSG_WRITE_EFSMS_CAUSE_MEM_FULL);
}


LOCAL VOS_VOID MSG_ProcStoreSm(
    const MN_MSG_CONFIG_PARM_STRU       *pstCfgParm,
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData
)
{
    VOS_UINT32                          ulRet = VOS_ERR;
    VOS_UINT32                          ulSaveIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MN_OPERATION_ID_T                   bcopId;
#endif
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#else
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
#endif
    MN_MSG_DELIVER_EVT_INFO_STRU        stDeliverEvt;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
    PS_MEM_SET(&stSmssInfo,0X00,sizeof(stSmssInfo));
    MSG_BuildDeliverEvtParm(pstCfgParm,pstScAddr,pstRawData,&stDeliverEvt);

    ulSaveIndex = MN_MSG_GetAvailSmRecIndex(pstCfgParm->enSmMemStore);

    /*当前存储器已满,没有合法的ucSaveIndex*/
    if (MN_MSG_NO_AVAILABLE_SMS_REC == ulSaveIndex)
    {
        MN_MSG_FailToWriteEfsms(pstCfgParm->enSmMemStore,
                                MN_MSG_WRITE_EFSMS_CAUSE_MEM_FULL);
    }
    else
    {
        MN_MSG_CreateEFSmContent(pstScAddr,
                                 pstRawData,
                                 EF_SMS_STATUS_MT_TO_BE_READ,
                                 aucSmContent);

#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
  || (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
        PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
        stSmaUsimInfo.clientId = MN_CLIENT_ALL;
        stSmaUsimInfo.opId = 0;
        stSmaUsimInfo.usEfId = ulFileId;
        stSmaUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stSmaUsimInfo.ucRecIndex = (VOS_UINT8)ulSaveIndex;
        stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVNEWMSG;
        ulRet = MN_MSG_WriteSmsFile(pstCfgParm->enSmMemStore,VOS_TRUE,&stSmaUsimInfo,aucSmContent);
#else
        if (MN_MSG_MEM_STORE_SIM == pstCfgParm->enSmMemStore)
        {
            PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
            stWriteUsimInfo.stUsimInfo.clientId = MN_CLIENT_ALL;
            stWriteUsimInfo.stUsimInfo.opId = 0;
            stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
            stWriteUsimInfo.stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
            stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)ulSaveIndex;
            stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVNEWMSG;
            stWriteUsimInfo.bCreateNode = VOS_TRUE;
            ulRet = MN_MSG_WriteSmsFile(pstCfgParm->enSmMemStore,VOS_NULL_PTR,&stWriteUsimInfo,aucSmContent);

        }
        else
        {
            ulRet = MN_MSG_WriteSmsFile(pstCfgParm->enSmMemStore,&ulSaveIndex,VOS_NULL_PTR,aucSmContent);
        }
#endif

        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_MSG_Internal_SendRpt(VOS_FALSE,
                                    MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                    MN_MSG_TP_CAUSE_ERR_IN_MS);
            MN_WARN_LOG("MSG_ProcStoreSm:MN_MSG_WriteSmsFile Return Error");
        }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
        else if (MN_MSG_MEM_STORE_NV == pstCfgParm->enSmMemStore)
        {
            MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
            /*广播上报来一条短信*/
            bcopId = MN_MSG_GetBCopId();
            stDeliverEvt.ulInex = ulSaveIndex;
            MN_MSG_ReportRcvMsgEvent(bcopId,&stDeliverEvt);
            /*广播上报NVIM中短信已发生了改变*/
            MN_MSG_ReportSmChanged(MN_CLIENT_ALL,bcopId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
        }
#endif
        else
        {
        }
    }
}


LOCAL VOS_VOID MSG_ProcNoClassSm(
    const MN_MSG_CONFIG_PARM_STRU       *pstCfgParm,
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData
)
{
    MN_MSG_MEM_FLAG_ENUM_U8             enAppMemStatus;
    MN_OPERATION_ID_T                   bcopId;
    MN_MSG_DELIVER_EVT_INFO_STRU        stDeliverEvt;

    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvSmAct;                             /*action of received msg*/

    MN_INFO_LOG("MSG_ProcNoClassSm: Step into function.");
    MSG_BuildDeliverEvtParm(pstCfgParm,pstScAddr,pstRawData,&stDeliverEvt);
    bcopId = MN_MSG_GetBCopId();
    MN_NORM_LOG1("MSG_ProcNoClassSm: pstCfgParm->enRcvSmAct is ", pstCfgParm->enRcvSmAct);



    /* 默认取配置中的SmAct,在<MT>=3,收到的是CLASS3短信时候，需要修改按照+CMT方式上报 */
    enRcvSmAct = pstCfgParm->enRcvSmAct;


    /* CLASS3类型短信按照+CMT方式上报 */
    if ( ( (MN_MSG_RCVMSG_ACT_STORE    == pstCfgParm->enRcvSmAct)
        && (MN_MSG_CNMI_MT_CLASS3_TYPE  == pstCfgParm->enMtType))
      && (MN_MSG_MSG_CLASS_3            == pstTsData->u.stDeliver.stDcs.enMsgClass) )
    {
        enRcvSmAct = MN_MSG_RCVMSG_ACT_TRANSFER_AND_ACK;

        if ( MN_MSG_CSMS_MSG_VERSION_PHASE2_PLUS == pstCfgParm->enSmsServVersion )
        {
            enRcvSmAct = MN_MSG_RCVMSG_ACT_TRANSFER_ONLY;
        }
    }

    if (MN_MSG_RCVMSG_ACT_DISCARD == enRcvSmAct)
    {
        MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
        MN_INFO_LOG("MSG_ProcNoClassSm:Rcv Sm but enRcvSmAct is MN_MSG_RCVMSG_ACT_DISCARD");
    }
    else if (MN_MSG_RCVMSG_ACT_STORE == enRcvSmAct)
    {
        MSG_ProcStoreSm(pstCfgParm,pstScAddr,pstRawData,pstTsData);
    }
    else if (MN_MSG_RCVMSG_ACT_TRANSFER_ONLY == enRcvSmAct)
    {
        stDeliverEvt.enMemStore = MN_MSG_MEM_STORE_NONE;
        stDeliverEvt.ulInex     = 0;

        /*广播上报来一条短信*/
        MN_MSG_ReportRcvMsgEvent(bcopId,&stDeliverEvt);
        /*创建收短信相关信息*/
        MN_MSG_CreateMtInfo();

    }
    else
    {
        MN_MSG_GetCurAppMemStatus(&enAppMemStatus);
        MN_NORM_LOG1("MSG_ProcNoClassSm: enAppMemStatus is ", enAppMemStatus);
        if (MN_MSG_MEM_FULL_SET == enAppMemStatus)
        {
            MN_MSG_Internal_SendRpt(VOS_FALSE,
                                    MN_MSG_RP_CAUSE_MEMORY_EXCEEDED,
                                    MN_MSG_TP_CAUSE_MEMORY_FULL);

            MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FULL_SET);

            MN_WARN_LOG("MSG_ProcNoClassSm:Rcv New Msg but App Mem Full");
        }
        else
        {
            MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);


            /* 通知AT进行+CMT方式存储 */
            stDeliverEvt.enMemStore = MN_MSG_MEM_STORE_NONE;
            stDeliverEvt.ulInex     = 0;

            MN_MSG_ReportRcvMsgEvent(bcopId,&stDeliverEvt);
        }
    }
}


LOCAL VOS_VOID MN_MSG_RcvAndStoreClass0Msg(
    const MN_MSG_CONFIG_PARM_STRU       *pstCfgParm,
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData
)
{
    MN_MSG_CLASS0_TAILOR_U8             enClass0Tailor;
    MN_MSG_DELIVER_EVT_INFO_STRU        stDeliverEvt;
    MN_OPERATION_ID_T                   bcopId;

    /* 获取Class0短信定制 */
    MSG_BuildDeliverEvtParm(pstCfgParm,pstScAddr,pstRawData,&stDeliverEvt);

    enClass0Tailor = MN_MSG_GetClass0Tailor();
    if (MN_MSG_CLASS0_VODAFONE == enClass0Tailor)
    {
        /* Vodafone Class0 短信定制,存储方式与class 2短信类似,
        亦即当有新class 0短信到来的时候，直接将短信存储到SIM卡中，
        不受CNMI以及CPMS设置的影响，同时采用＋CMTI上报短信存储位置。*/
        MSG_ProcClass2Msg(pstScAddr,pstRawData);
        return;
    }

    /*1: Italy TIM Class0 短信定制（即H3G Class0 短信定制）
        H3G与意大利TIM Class 0短信需求相同，不对短信进行存储，
        要求将CLASS 0 短信直接采用+CMT进行主动上报。不受CNMI
        以及CPMS设置的影响，如果后台已经打开，则后台对CLASS 0短信进行显示。
      2：27005协议CNMI指定处理方式
      <MT>为0存储到（U）SIM卡但不在AT端口上报；
      <MT>为1存储到（U）SIM卡并且在AT端口上报存储位置（即CMTI方式上报）；
      <MT>为2不存储到（U）SIM卡但会在AT端口上报短信内容（即CMT方式上报）；
      <MT>为3存储到（U）SIM卡并且在AT端口上报存储位置（即CMTI方式上报）；
      这两种情况只是在AT上的显示不一样,所以此处不需要进行任何处理
    */
    else if (MN_MSG_CLASS0_TIM == enClass0Tailor)
    {
        if (MN_MSG_RCVMSG_ACT_TRANSFER_ONLY != pstCfgParm->enRcvSmAct)
        {
            /* TIM和VIVO定制的差异:在<MT>=1/3时,即使CSMS=1，也不需要+CNMA ACK */
            MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
        }
        else
        {
            /*如果是有应用回复Rp-Report,创建收短信相关信息*/
            MN_MSG_CreateMtInfo();
        }
        bcopId                  = MN_MSG_GetBCopId();
        stDeliverEvt.enMemStore = MN_MSG_MEM_STORE_NONE;
        stDeliverEvt.ulInex     = 0;
        MN_MSG_ReportRcvMsgEvent(bcopId, &stDeliverEvt);
    }
    else if (MN_MSG_CLASS0_VIVO == enClass0Tailor)
    {
        if (MN_MSG_CSMS_MSG_VERSION_PHASE2 == pstCfgParm->enSmsServVersion)
        {
            MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
        }
        else
        {
            /*如果是有应用回复Rp-Report,创建收短信相关信息*/
            MN_MSG_CreateMtInfo();
        }
        bcopId                  = MN_MSG_GetBCopId();
        stDeliverEvt.enMemStore = MN_MSG_MEM_STORE_NONE;
        stDeliverEvt.ulInex     = 0;
        MN_MSG_ReportRcvMsgEvent(bcopId, &stDeliverEvt);
    }
    else
    {
        MSG_ProcNoClassSm(pstCfgParm, pstScAddr,pstRawData, pstTsData);
    }

    return;
}


LOCAL VOS_UINT32 MSG_IsRequireDownloadMsg(
    const MN_MSG_TS_DATA_INFO_STRU     *pstTsData
)
{
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr = VOS_NULL_PTR;
    MN_MSG_USIM_EFUST_INFO_STRU         stEfUstInfo;

    PS_MEM_SET(&stEfUstInfo,0X00,sizeof(stEfUstInfo));
    MN_MSG_ReadUstInfo(&stEfUstInfo);

    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();

    MN_NORM_LOG1("MSG_IsRequireDownloadMsg: pstCustomCfgAddr->ucSmsPpDownlodSupportFlg ", (VOS_INT32)pstCustomCfgAddr->ucSmsPpDownlodSupportFlg);
    MN_NORM_LOG1("MSG_IsRequireDownloadMsg: stEfUstInfo.bSmsPpDataFlag is ", (VOS_INT32)stEfUstInfo.bSmsPpDataFlag);
    MN_NORM_LOG1("MSG_IsRequireDownloadMsg: enPid is ", pstTsData->u.stDeliver.enPid);
    MN_NORM_LOG1("MSG_IsRequireDownloadMsg: enMsgClass is ", pstTsData->u.stDeliver.stDcs.enMsgClass);

    /* 此处需要钩包输出ucSmsPpDownlodSupportFlg，bSmsPpDataFlag，enMsgClass和enPid数据 */

    /* NV项配置为MODEM不支持PP-DOWNLOAD功能，忽略DOWNLOAD属性 */
    if (MN_MSG_NV_ITEM_ACTIVE != pstCustomCfgAddr->ucSmsPpDownlodSupportFlg)
    {
        return VOS_FALSE;
    }

    /* (U)SIM配置不支持PP-DOWNLOAD功能，忽略DOWNLOAD属性 */
    if (VOS_TRUE != stEfUstInfo.bSmsPpDataFlag)
    {
        return VOS_FALSE;
    }

    /* 是OTA短信，要求DOWNLOAD */
    if ((MN_MSG_MSG_CLASS_2 == pstTsData->u.stDeliver.stDcs.enMsgClass)
     && ((MN_MSG_TP_PID_SIM_DATA_DOWNLOAD == pstTsData->u.stDeliver.enPid)
      || (MN_MSG_TP_PID_ANSI136_R_DATA == pstTsData->u.stDeliver.enPid)))
    {
        return VOS_TRUE;
    }

    /* 非OTA短信，不要求DOWNLOAD */
    return VOS_FALSE;
}


LOCAL VOS_UINT32 MSG_IsVsimCtrlDiscardMsg(
    const MN_MSG_TS_DATA_INFO_STRU     *pstTsData
)
{
    VOS_UINT32                          ulRet;

    /* 未启用VSIM控制流程 */
    ulRet = NAS_VSIM_IsRequireVsimCtrl();
    if (VOS_TRUE != ulRet)
    {
        return VOS_FALSE;
    }

    /* 要求DOWNLOAD的短信不受VSIM特性控制 */
    ulRet = MSG_IsRequireDownloadMsg(pstTsData);
    if (VOS_TRUE == ulRet)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


LOCAL VOS_VOID MSG_ProcSmsDeliver(
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData,
    VOS_UINT8                            ucRcvDomain
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_CONFIG_PARM_STRU             stCfgParm;
    VOS_BOOL                            bSupportFlag;
    MN_MSG_TP_CAUSE_ENUM_U8             enTpCause;

    VOS_UINT8                           ucCloseSmsFlg;

    PS_MEM_SET(&stCfgParm, 0, sizeof(stCfgParm));

    /*获取当前的短信的配置参数*/
    MN_MSG_GetCurCfgParm(&stCfgParm);

    MN_NORM_LOG1("MSG_ProcSmsDeliver: stCfgParm.enRcvSmAct is ", stCfgParm.enRcvSmAct);
    MN_NORM_LOG1("MSG_ProcSmsDeliver: enPid is ", pstTsData->u.stDeliver.enPid);
    MN_NORM_LOG1("MSG_ProcSmsDeliver: enMsgClass is ", pstTsData->u.stDeliver.stDcs.enMsgClass);

    f_ulMsgMtNum++;

    /* VSIM特性要求丢弃的短信，退出短信接收流程 */
    /* 启用VSIM控制流程时，非DOWNLOAD的短信，直接丢弃 */
    ulRet = MSG_IsVsimCtrlDiscardMsg(pstTsData);
    if (VOS_TRUE == ulRet)
    {
        MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
        MN_NORM_LOG("MSG_DiscardVsimCtrlMsg: VSIM feature discard deliver message.");

        return;
    }

    MN_MSG_GetAndSaveActiveMessageInfo(&pstTsData->u.stDeliver);

    /* 当前短信功能是否支持 */
    MN_MSG_GetCloseSMSFeature(&ucCloseSmsFlg);

    /*pid是"Short Message Type 0" (根据协议23040，该条短消息不进行保存，也不向应用层上报)*/
    if ((MN_MSG_TP_PID_SM_TYPE_0 == pstTsData->u.stDeliver.enPid)
     || (MN_MSG_NVIM_ITEM_ACTIVE == ucCloseSmsFlg))
    {
        MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
        MN_NORM_LOG("MSG_ProcSmsDeliver:Pid = MN_MSG_TP_PID_SM_TYPE_0,Discard it");
        return;
    }

    MN_MSG_DeliverMsgNotSupport(pstTsData, &bSupportFlag, &enTpCause);
    if (VOS_FALSE == bSupportFlag)
    {
        MN_MSG_Internal_SendRpt(VOS_FALSE, MN_MSG_RP_CAUSE_IE_NON_EXISTENT, enTpCause);
        MN_NORM_LOG1("MSG_ProcSmsDeliver: deliver message is not supported. enTpCause is ", enTpCause);
        return;
    }

    /* 更新MT时的接收域，只有在状态不为MN_MSG_MT_STATE_NULL时才有效 */
    TAF_MSG_UpdateMtRcvDomain(ucRcvDomain);

    /*TP-PID为Replace Short Message Type 1-Replace Short Message Type 7或Return Call Message
    用新接收到的短信替换之前存储的短信*/
    if (VOS_TRUE == MSG_ProcReplaceSm(&stCfgParm,pstScAddr,pstRawData,pstTsData))
    {
        return;
    }

    /*(pid是(U)SIM Data download || pid是MN_MSG_TP_PID_ANSI136_R_DATA) && 该条短信是
    Class 2类型的 &&支持Data download via SMS-PP(不支持,则按照Class 2短信保留在USIM中)*/
    ulRet = MSG_IsRequireDownloadMsg(pstTsData);
    if (VOS_TRUE == ulRet)
    {
        MN_MSG_SetMtTpPidAndDcs(pstTsData->u.stDeliver.enPid, pstTsData->u.stDeliver.stDcs);
        ulRet = MN_MSG_SmsPPEnvelopeReq(pstScAddr,pstRawData->aucData, pstRawData->ulLen);
        if (VOS_ERR == ulRet)
        {
            MN_MSG_Internal_SendRpt(VOS_FALSE,
                                    MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                    MN_MSG_TP_CAUSE_ERR_IN_MS);
        }
        return;
    }

    /*Class 2类型的短信只能存储在USIM中*/
    if (MN_MSG_MSG_CLASS_2 == pstTsData->u.stDeliver.stDcs.enMsgClass)
    {
        MSG_ProcClass2Msg(pstScAddr,pstRawData);
    }

    /*Class 0类型的短信的接收和存储*/
    else if (MN_MSG_MSG_CLASS_0 == pstTsData->u.stDeliver.stDcs.enMsgClass)
    {
        MN_MSG_RcvAndStoreClass0Msg(&stCfgParm,pstScAddr,pstRawData,pstTsData);
    }

    /*无Class类型的短信的接收和存储*/
    else
    {
        MSG_ProcNoClassSm(&stCfgParm,pstScAddr,pstRawData,pstTsData);
    }

    return;
}


VOS_VOID MN_MSG_GetStatusReportStorageInfo(
    MN_MSG_STORAGE_INFO_STRU            *pstStorageInfo
)
{
    VOS_UINT32                          ulSmsrIndex;
    VOS_UINT32                          ulSmsrCapacity;
    MN_MSG_CONFIG_PARM_STRU             stCfgParm;
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;
    VOS_UINT32                          ulFileId[2];

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId[0]    = USIMM_USIM_EFSMS_ID;
        ulFileId[1]    = USIMM_USIM_EFSMSR_ID;
    }
    else
    {
        ulFileId[0]    = USIMM_TELE_EFSMS_ID;
        ulFileId[1]    = USIMM_TELE_EFSMSR_ID;
    }

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();

    PS_MEM_SET(&stCfgParm, 0, sizeof(stCfgParm));

    MN_MSG_GetCurCfgParm(&stCfgParm);
    pstStorageInfo->enRcvSmAct = stCfgParm.enRcvStaRptAct;

    if (MN_MSG_RCVMSG_ACT_STORE != pstStorageInfo->enRcvSmAct)
    {
        return;
    }

    if (MN_MSG_NV_ITEM_DEACTIVE == pstCustomCfgAddr->ucSmsStatusInEfsmsSupportFlg)
    {
        pstStorageInfo->usFileIndex = (VOS_UINT16)ulFileId[1];
        pstStorageInfo->enMemStore  = stCfgParm.enStaRptMemStore;
        pstStorageInfo->ulIndex     = MN_MSG_NO_AVAILABLE_SMS_REC;

        ulSmsrCapacity = MN_MSG_GetSmsrCapacity(stCfgParm.enStaRptMemStore);
        if (0 != ulSmsrCapacity)
        {
            ulSmsrIndex = MN_MSG_GetAvailSmsrRecIndex(stCfgParm.enStaRptMemStore);
            if (MN_MSG_NO_AVAILABLE_SMS_REC == ulSmsrIndex)
            {
                MN_INFO_LOG("MN_MSG_GetStatusReportStorageInfo: Rcv StatusReport No Free smsr record.");
                /*若无空闲位置,则直接找到替换的一条短信状态报告的索引*/
                ulSmsrIndex = MN_MSG_GetReplaceSmsrRecIndex(stCfgParm.enStaRptMemStore);
            }

            pstStorageInfo->ulIndex = ulSmsrIndex;

        }

        if (MN_MSG_NO_AVAILABLE_SMS_REC == pstStorageInfo->ulIndex)
        {
            if (MN_MSG_CSMS_MSG_VERSION_PHASE2 == stCfgParm.enSmsServVersion)
            {
                pstStorageInfo->enRcvSmAct = MN_MSG_RCVMSG_ACT_TRANSFER_AND_ACK;
            }
            else
            {
                pstStorageInfo->enRcvSmAct = MN_MSG_RCVMSG_ACT_TRANSFER_ONLY;
            }

        }

    }
    else
    {
        pstStorageInfo->enMemStore  = stCfgParm.enSmMemStore;
        pstStorageInfo->usFileIndex = (VOS_UINT16)ulFileId[0];
        pstStorageInfo->ulIndex     = MN_MSG_GetAvailSmRecIndex(stCfgParm.enSmMemStore);
    }

    return;
}


VOS_UINT32 MN_MSG_StoreStatusReport(
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    const MN_MSG_STORAGE_INFO_STRU      *pstStorageInfo
)
{
    VOS_UINT8                           aucSmsrContent[MN_MSG_EFSMSR_LEN];
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT32                          ulRet;
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#endif
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;
    VOS_UINT32                          ulFileId[2];

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId[0]    = USIMM_USIM_EFSMS_ID;
        ulFileId[1]    = USIMM_USIM_EFSMSR_ID;
    }
    else
    {
        ulFileId[0]    = USIMM_TELE_EFSMS_ID;
        ulFileId[1]    = USIMM_TELE_EFSMSR_ID;
    }

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();


    /* 创建短信状态报告记录 */
    PS_MEM_SET(&stSmaUsimInfo, 0X00, sizeof(stSmaUsimInfo));
    stSmaUsimInfo.clientId          = MN_CLIENT_ALL;
    stSmaUsimInfo.opId              = 0;
    stSmaUsimInfo.usEfId            = pstStorageInfo->usFileIndex;
    stSmaUsimInfo.enDeleteType      = MN_MSG_DELETE_MAX;
    stSmaUsimInfo.ucRecIndex        = (VOS_UINT8)pstStorageInfo->ulIndex;
    stSmaUsimInfo.enSmaUsimAction   = MN_MSG_USIM_RCVSTARPT;

    if (MN_MSG_NV_ITEM_DEACTIVE == pstCustomCfgAddr->ucSmsStatusInEfsmsSupportFlg)
    {
        MN_MSG_CreateEFSmContent(pstScAddr,
                                 pstRawData,
                                 EF_SMS_STATUS_MT_TO_BE_READ,
                                 aucSmContent);

#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
  || (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
        ulRet = MN_MSG_WriteSmsFile(pstStorageInfo->enMemStore,VOS_TRUE,&stSmaUsimInfo,aucSmContent);
#else
        if (MN_MSG_MEM_STORE_SIM == pstStorageInfo->enMemStore)
        {
            PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
            stWriteUsimInfo.stUsimInfo.clientId = MN_CLIENT_ALL;
            stWriteUsimInfo.stUsimInfo.opId = 0;
            stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId[0];
            stWriteUsimInfo.stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
            stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)pstStorageInfo->ulIndex;
            stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVNEWMSG;
            stWriteUsimInfo.bCreateNode = VOS_TRUE;
            ulRet = MN_MSG_WriteSmsFile(pstStorageInfo->enMemStore,
                                        VOS_NULL_PTR,
                                        &stWriteUsimInfo,
                                        aucSmContent);

        }
        else
        {
            ulRet = MN_MSG_WriteSmsFile(pstStorageInfo->enMemStore,
                                        &pstStorageInfo->ulIndex,
                                        VOS_NULL_PTR,
                                        aucSmContent);
        }
#endif

    }
    else
    {
        /* 写短信状态报告记录到文件 */
        if ((MN_MSG_MEM_STORE_SIM == pstStorageInfo->enMemStore)
         && (ulFileId[1]       == pstStorageInfo->usFileIndex))
        {
            /* 协议栈不支持SMS记录与SMSR的关联，SMSR记录的第一个字节"关联的SMS记录索引"填0 */
            MSG_CreateEFSmsrContent(pstRawData, 0, aucSmsrContent);
            ulRet = MN_MSG_WriteSmsrFile(pstStorageInfo->enMemStore,
                                         &stSmaUsimInfo,
                                         aucSmsrContent);

        }
        else
        {
            MN_MSG_CreateEFSmContent(pstScAddr,
                                     pstRawData,
                                     EF_SMS_STATUS_MT_TO_BE_READ,
                                     aucSmContent);

#if ( (NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
   || (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
            ulRet = MN_MSG_WriteSmsFile(pstStorageInfo->enMemStore,VOS_TRUE,&stSmaUsimInfo,aucSmContent);
#else
            if (MN_MSG_MEM_STORE_SIM == pstStorageInfo->enMemStore)
            {
                PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
                stWriteUsimInfo.stUsimInfo.clientId = MN_CLIENT_ALL;
                stWriteUsimInfo.stUsimInfo.opId = 0;
                stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId[0];
                stWriteUsimInfo.stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
                stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)pstStorageInfo->ulIndex;
                stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVNEWMSG;
                stWriteUsimInfo.bCreateNode = VOS_TRUE;
                ulRet = MN_MSG_WriteSmsFile(pstStorageInfo->enMemStore,
                                            VOS_NULL_PTR,
                                            &stWriteUsimInfo,
                                            aucSmContent);

            }
            else
            {
                ulRet = MN_MSG_WriteSmsFile(pstStorageInfo->enMemStore,
                                            &pstStorageInfo->ulIndex,
                                            VOS_NULL_PTR,
                                            aucSmContent);
            }
#endif
        }

    }

    return ulRet;
}


LOCAL VOS_VOID MSG_ProcSmsStaRpt(
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData,
    VOS_UINT8                            ucRcvDomain
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_MEM_FLAG_ENUM_U8             enAppMemStatus;
    MN_OPERATION_ID_T                   bcopId;
    MN_MSG_DELIVER_EVT_INFO_STRU        stDeliverEvt;
    MN_MSG_STORAGE_INFO_STRU            stStorageInfo;

    /* 获取短信状态报告可用存储参数 */
    PS_MEM_SET(&stStorageInfo, 0x00, sizeof(stStorageInfo));
    MN_MSG_GetStatusReportStorageInfo(&stStorageInfo);

    /* 短信状态报告不存储: 给网络回复RP-ACK,并丢弃短信状态报告 */
    if (MN_MSG_RCVMSG_ACT_DISCARD == stStorageInfo.enRcvSmAct)
    {
        MN_INFO_LOG("MSG_ProcSmsStaRpt: enRcvSmAct is MN_MSG_RCVMSG_ACT_DISCARD");
        MN_MSG_Internal_SendRpt(VOS_TRUE, 0, 0);
        return;
    }

    /* 更新MT时的接收域，只有在状态不为MN_MSG_MT_STATE_NULL时才有效 */
    TAF_MSG_UpdateMtRcvDomain(ucRcvDomain);

    /* 短信状态报告上报事件数据填充: 短信中心号码，短信状态报告PDU，广播OPID */
    PS_MEM_SET(&stDeliverEvt, 0X00, sizeof(stDeliverEvt));
    PS_MEM_CPY(&stDeliverEvt.stRcvMsgInfo.stScAddr,
               pstScAddr,
               sizeof(stDeliverEvt.stRcvMsgInfo.stScAddr));
    PS_MEM_CPY(&stDeliverEvt.stRcvMsgInfo.stTsRawData,
               pstRawData,
               sizeof(stDeliverEvt.stRcvMsgInfo.stTsRawData));
    bcopId = MN_MSG_GetBCopId();

    /* 存储短信状态报告处理流程 */
    if (MN_MSG_RCVMSG_ACT_STORE == stStorageInfo.enRcvSmAct)
    {

        /* 获取空闲存储记录失败: 给网络回复RP-ERROR，同时上报^SMMEMFULL: <mem> */
        if (MN_MSG_NO_AVAILABLE_SMS_REC == stStorageInfo.ulIndex)
        {
            MN_NORM_LOG("MSG_ProcSmsStaRpt: There is no record available.");
            MN_MSG_FailToWriteEfsms(stStorageInfo.enMemStore,
                                    MN_MSG_WRITE_EFSMS_CAUSE_MEM_FULL);
            return;
        }

        /* 存储短信状态报告到文件 */
        ulRet = MN_MSG_StoreStatusReport(pstScAddr, pstRawData, &stStorageInfo);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG("MSG_ProcSmsStaRpt: MN_MSG_WriteSmsFile Return Error");
            MN_MSG_Internal_SendRpt(VOS_FALSE,
                                    MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                    MN_MSG_TP_CAUSE_ERR_IN_MS);
            return;
        }

        /* 存储短信状态报告到文件 */
        if (MN_MSG_MEM_STORE_NV == stStorageInfo.enMemStore)
        {
            MN_MSG_Internal_SendRpt(VOS_TRUE, 0, 0);

            /*广播上报来一条短信*/
            stDeliverEvt.enRcvSmAct = MN_MSG_RCVMSG_ACT_STORE;
            stDeliverEvt.enMemStore = stStorageInfo.enMemStore;
            stDeliverEvt.ulInex     = stStorageInfo.ulIndex;
            MN_MSG_ReportRcvMsgEvent(bcopId, &stDeliverEvt);

            /*广播上报NVIM中短信已发生了改变*/
            MN_MSG_ReportSmChanged(MN_CLIENT_ALL, bcopId, VOS_TRUE, MN_MSG_MEM_STORE_NV);
        }

    }
    else if (MN_MSG_RCVMSG_ACT_TRANSFER_ONLY == stStorageInfo.enRcvSmAct)
    {
        MN_MSG_ReportRcvMsgEvent(bcopId,&stDeliverEvt);
        /*创建收短信相关信息*/
        MN_MSG_CreateMtInfo();
    }
    else
    {
        MN_MSG_GetCurAppMemStatus(&enAppMemStatus);
        if (MN_MSG_MEM_FULL_SET == enAppMemStatus)
        {
            MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FULL_SET);

            MN_WARN_LOG("MSG_ProcSmsStaRpt:Rcv New Status Report but App Mem Full");
        }

        MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
        MN_MSG_ReportRcvMsgEvent(bcopId,&stDeliverEvt);
    }
}


LOCAL VOS_UINT32 MSG_UpdateEfSmsInfo
(
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity,
    MN_MSG_MEM_STORE_ENUM_U8            *penMemStore
)
{

    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT32                          ulRet;
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#else
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
#endif
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }


    PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);

    ulRet = MN_MSG_ReadSmsInfo(pstMoEntity->enSaveArea,
                               pstMoEntity->ulSaveIndex,
                               aucSmContent);

    if (MN_ERR_NO_ERROR == ulRet)
    {
        aucSmContent[0] = EF_SMS_STATUS_MO_SEND_TO_NT;

#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
          || (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
        PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
        stSmaUsimInfo.clientId = pstMoEntity->clientId;
        stSmaUsimInfo.opId = pstMoEntity->opId;
        stSmaUsimInfo.usEfId = ulFileId;
        stSmaUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stSmaUsimInfo.ucRecIndex = (VOS_UINT8)pstMoEntity->ulSaveIndex;
        stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVMORPT;
        ulRet = MN_MSG_WriteSmsFile(pstMoEntity->enSaveArea,VOS_FALSE,&stSmaUsimInfo,aucSmContent);
#else
        if (MN_MSG_MEM_STORE_SIM == pstMoEntity->enSaveArea)
        {
            PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
            stWriteUsimInfo.stUsimInfo.clientId = pstMoEntity->clientId;
            stWriteUsimInfo.stUsimInfo.opId = pstMoEntity->opId;
            stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
            stWriteUsimInfo.stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
            stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)pstMoEntity->ulSaveIndex;
            stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_RCVMORPT;
            stWriteUsimInfo.bCreateNode = VOS_FALSE;
            ulRet = MN_MSG_WriteSmsFile(pstMoEntity->enSaveArea,VOS_NULL_PTR,&stWriteUsimInfo,aucSmContent);

        }
        else
        {
            ulRet = MN_MSG_WriteSmsFile(pstMoEntity->enSaveArea,&pstMoEntity->ulSaveIndex,VOS_NULL_PTR,aucSmContent);
        }
#endif

        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG("MSG_UpdateEfSmsInfo:Update Sms in Usim or Nvim Error");
            return VOS_ERR;
        }
        return VOS_OK;
    }
    else
    {
        *penMemStore = MN_MSG_MEM_STORE_NONE;
        MN_WARN_LOG("MSG_ProcSmsRpMoRpRpt:Read Sms Failed");
        return VOS_ERR;
    }
}


VOS_UINT32 MSG_GetMoFailCause(
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    const SMR_SMT_ERROR_ENUM_UINT32      enErrorCode
)
{
    VOS_UINT32                          ulRet;

    if ((SMR_SMT_ERROR_RP_ERROR_BEGIN == (enErrorCode & SMR_SMT_ERROR_RP_ERROR_BEGIN))
     && (pstRawData->ulLen > 0))
    {
        ulRet = MN_MSG_Decode(pstRawData, &f_stMsgTsData);
        if (MN_ERR_NO_ERROR == ulRet)
        {
            return (f_stMsgTsData.u.stSubmitRptErr.enFailCause | TAF_MSG_ERROR_TP_ERROR_BEGIN);
        }

        MN_WARN_LOG("MSG_GetMoFailCause: MN_MSG_Decode Error");
    }

    return enErrorCode;
}


LOCAL VOS_VOID MSG_ProcSmsRpMoRpRpt(
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData ,
    const SMR_SMT_ERROR_ENUM_UINT32      enErrorCode
)
{
    VOS_UINT32                          ulRet = VOS_FALSE;
    MN_MSG_MEM_STORE_ENUM_U8            enCurMemStore;
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU     stSubmitRptEvt;
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MN_OPERATION_ID_T                   bcOpId;
#endif

    PS_MEM_SET(&stSubmitRptEvt,0X00,sizeof(stSubmitRptEvt));
    stSubmitRptEvt.ucMr = pstMoEntity->ucMr;

    /* 此处需要适配新的TAF-AT接口，发送成功，则上报STCS信息，否则获取错误原因值 */

    if (MN_MSG_TPDU_SUBMIT_RPT_ACK == pstRawData->enTpduType)
    {
        f_ulMsgMoNum++;

        stSubmitRptEvt.enErrorCode = TAF_MSG_ERROR_NO_ERROR;
        stSubmitRptEvt.enSaveArea  = pstMoEntity->enSaveArea;

        enCurMemStore = pstMoEntity->enSaveArea;
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
        if ((MN_MSG_MEM_STORE_SIM == pstMoEntity->enSaveArea)
         || (MN_MSG_MEM_STORE_NV == pstMoEntity->enSaveArea))
#else
        if (MN_MSG_MEM_STORE_SIM == pstMoEntity->enSaveArea)
#endif
        {
            ulRet = MSG_UpdateEfSmsInfo(pstMoEntity,&enCurMemStore);
            MN_INFO_LOG1("MSG_ProcSmsRpMoRpRpt: result of MSG_UpdateEfSmsInfo is ",
                         (VOS_INT32)ulRet);
            stSubmitRptEvt.enSaveArea = enCurMemStore;
            stSubmitRptEvt.ulSaveIndex = pstMoEntity->ulSaveIndex;
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
            if ((MN_MSG_MEM_STORE_NV == enCurMemStore)
             && (VOS_OK == ulRet))
            {
                bcOpId = MN_MSG_GetBCopId();
                MN_MSG_ReportSmChanged(pstMoEntity->clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
            }
#endif
        }
        MN_MSG_ReportSubmitRptEvent(pstMoEntity->clientId,
                                    pstMoEntity->opId,
                                    (MN_MSG_SUBMIT_RPT_EVT_INFO_STRU *)&stSubmitRptEvt,
                                    MN_MSG_EVT_SUBMIT_RPT);
        MN_INFO_LOG("MSG_ProcSmsRpMoRpRpt:Rcv Rp-Ack");
    }
    else if (MN_MSG_TPDU_SUBMIT_RPT_ERR == pstRawData->enTpduType)
    {
        stSubmitRptEvt.enErrorCode = MSG_GetMoFailCause(pstRawData, enErrorCode);
        /* 此处需要适配新的TAF-AT接口，发送成功，则上报STCS信息，否则获取错误原因值 */
        stSubmitRptEvt.enSaveArea = pstMoEntity->enSaveArea;
        stSubmitRptEvt.ulSaveIndex = pstMoEntity->ulSaveIndex;
        MN_MSG_ReportSubmitRptEvent(pstMoEntity->clientId,
                                    pstMoEntity->opId,
                                    (MN_MSG_SUBMIT_RPT_EVT_INFO_STRU *)&stSubmitRptEvt,
                                    MN_MSG_EVT_SUBMIT_RPT);
        MN_INFO_LOG("MSG_ProcSmsRpMoRpRpt:Rcv Rp-Error");
    }
    else
    {
    }
}


LOCAL VOS_VOID MSG_ProcSmsRpSmmaRpRpt(
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData ,
    const SMR_SMT_ERROR_ENUM_UINT32      enErrorCode
)
{
    MN_MSG_MEMSTATUS_EVT_INFO_STRU      stMemStatusEvt;
    MN_OPERATION_ID_T                   bcopId;

    PS_MEM_SET(&stMemStatusEvt,0X00,sizeof(stMemStatusEvt));

    if (MN_MSG_TPDU_SUBMIT_RPT_ACK == pstRawData->enTpduType)
    {
        if (VOS_TRUE == pstMoEntity->bReportFlag)
        {
            (VOS_VOID)MN_MSG_UpdateAppMemStatus(MN_MSG_MEM_FULL_UNSET);
            stMemStatusEvt.bSuccess = VOS_TRUE;
            stMemStatusEvt.ulFailCause = MN_ERR_NO_ERROR;
            stMemStatusEvt.enMemFlag = MN_MSG_MEM_FULL_UNSET;
            MN_MSG_ReportMemStatustEvent(pstMoEntity->clientId,
                                         pstMoEntity->opId,
                                         VOS_FALSE,
                                         &stMemStatusEvt,
                                         MN_MSG_EVT_SET_MEMSTATUS);
            bcopId = MN_MSG_GetBCopId();
            MN_MSG_ReportMemStatustEvent(pstMoEntity->clientId,
                                         bcopId,
                                         VOS_TRUE,
                                         &stMemStatusEvt,
                                         MN_MSG_EVT_MEMSTATUS_CHANGED);
        }

        MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FULL_UNSET);

        MN_INFO_LOG("MSG_ProcSmsRpSmmaRpRpt:Rcv Rp-Ack");
    }
    else if (MN_MSG_TPDU_SUBMIT_RPT_ERR == pstRawData->enTpduType)
    {
        if (VOS_TRUE == pstMoEntity->bReportFlag)
        {
            stMemStatusEvt.bSuccess = VOS_FALSE;
            stMemStatusEvt.ulFailCause = MSG_GetMoFailCause(pstRawData, enErrorCode);
            stMemStatusEvt.enMemFlag = MN_MSG_MEM_FULL_SET;
            MN_MSG_ReportMemStatustEvent(pstMoEntity->clientId,
                                         pstMoEntity->opId,
                                         VOS_FALSE,
                                         &stMemStatusEvt,
                                         MN_MSG_EVT_SET_MEMSTATUS);
        }
        MN_INFO_LOG("MSG_ProcSmsRpSmmaRpRpt:Rcv Rp-Error");
    }
    else
    {
    }
}


LOCAL VOS_VOID MSG_RcvSmsRpData(
    SMR_SMT_EST_IND_STRU                *pstEstInd
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_BCD_ADDR_STRU                stScAddr;
    MN_MSG_RAW_TS_DATA_STRU             stTsRawData;
    MN_MSG_RP_DATA_STRU                 stRpData;

    const VOS_UINT8                    *pucRcvMsg = VOS_NULL_PTR;

    pucRcvMsg   = pstEstInd->aucData;

    MN_INFO_LOG("MSG_RcvSmsRpData: step into function.");
    ulRet = MN_MSG_CheckUsimStatus();
    if (MN_ERR_NO_ERROR != ulRet)
    {
#if (FEATURE_IMS == FEATURE_ON)
        if (PS_PID_IMSA == pstEstInd->ulSenderPid)
        {
            MN_MSG_SetMtRouteStackType(TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP);
        }
        else
        {
            MN_MSG_SetMtRouteStackType(TAF_MSG_SIGNALLING_TYPE_NAS_SIGNALLING);
        }
#endif

        MN_MSG_Internal_SendRpt(VOS_FALSE,
                                MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                MN_MSG_TP_CAUSE_ERR_IN_MS);
        MN_WARN_LOG("MSG_RcvSmsRpData:Usim is not Ready");
        return;
    }

    PS_MEM_SET(&stScAddr,0X00,sizeof(stScAddr));
    PS_MEM_SET(&stTsRawData,0X00,sizeof(stTsRawData));
    PS_MEM_SET(&f_stMsgTsData,0X00,sizeof(f_stMsgTsData));
    PS_MEM_SET(&stRpData,0X00,sizeof(stRpData));

    /*3GPP 24011 RP DATA (Network to Mobile Station)*/
    MSG_DecodeRpData(pucRcvMsg,&stRpData);
    MN_INFO_LOG1("MSG_RcvSmsRpData: message RP-MR is ", stRpData.ucRpMr);
    PS_MEM_CPY(&stScAddr,&stRpData.stOrgAddr,sizeof(stScAddr));

    stTsRawData.ulLen = stRpData.ucRpUserDataLen;
    PS_MEM_CPY(stTsRawData.aucData,stRpData.aucRpUserData,stTsRawData.ulLen);

    MN_NORM_LOG1("MSG_RcvSmsRpData: message TP-MTI is ", ((stTsRawData.aucData[0]) & (0x03)));
    switch ((stTsRawData.aucData[0]) & (0x03))
    {
        case MN_MSG_TP_MTI_DELIVER:
            stTsRawData.enTpduType = MN_MSG_TPDU_DELIVER;
            break;
        case MN_MSG_TP_MTI_STATUS_REPORT:
            stTsRawData.enTpduType = MN_MSG_TPDU_STARPT;
            break;
        default:
            MN_MSG_Internal_SendRpt(VOS_FALSE,
                                    MN_MSG_RP_CAUSE_MSG_TYPE_NON_EXISTENT,
                                    MN_MSG_TP_CAUSE_ERR_IN_MS);
            MN_WARN_LOG("MSG_RcvSmsRpData:Invalid TPDU Type");
            return;
    }

    ulRet = MN_MSG_Decode(&stTsRawData,&f_stMsgTsData);

#if (FEATURE_IMS == FEATURE_ON)
    if (PS_PID_IMSA == pstEstInd->ulSenderPid)
    {
        MN_MSG_SetMtRouteStackType(TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP);
    }
    else
    {
        MN_MSG_SetMtRouteStackType(TAF_MSG_SIGNALLING_TYPE_NAS_SIGNALLING);
    }
#endif

    /*此处的错误原因应为MN_MSG_RP_CAUSE_INVALID_MSG_UNSPECIFIED
    参考24011 if the message was not an RP ERROR message, the MS shall ignore
    the message and return an RP ERROR message with cause value #95 "
    semantically incorrect message", if an appropriate connection exists*/
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_MSG_Internal_SendRpt(VOS_FALSE,
                                MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                MN_MSG_TP_CAUSE_TPDU_NOT_SUPPORTED);
        MN_WARN_LOG("MSG_RcvSmsRpData: Fail to decode TPDU.");
        return;
    }

    MN_NORM_LOG1("MSG_RcvSmsRpData: TPDU type: ",stTsRawData.enTpduType);
    if (MN_MSG_TPDU_DELIVER == stTsRawData.enTpduType)
    {
        NAS_EventReport(WUEPS_PID_SMS, NAS_OM_EVENT_SMS_RECEIVE,
                        &stRpData.ucRpMr, NAS_OM_EVENT_SMS_RECEIVE_LEN);
        /* 参数改变:增加接收域 */
        MSG_ProcSmsDeliver(&stScAddr,&stTsRawData,&f_stMsgTsData, pstEstInd->ucRcvDomain);
    }
    else
    {
        NAS_EventReport(WUEPS_PID_SMS, NAS_OM_EVENT_SMS_MT_NOTIFY,
                        &stRpData.ucRpMr, NAS_OM_EVENT_SMS_MT_NOTIFY_LEN);
        /* 参数改变:增加接收域 */
        MSG_ProcSmsStaRpt(&stScAddr,&stTsRawData,&f_stMsgTsData, pstEstInd->ucRcvDomain);
    }

}


LOCAL VOS_VOID  MSG_RcvSmsAttachInd(
    VOS_UINT8                           ucDomain,
    VOS_BOOL                            bAttachFlag
)
{
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain;
    MN_MSG_MO_STATE_ENUM_U8             enMoState;

    MN_MSG_UpdateRegState(ucDomain,bAttachFlag);

    /*如果当前已ATTACH上,则查看是否需要发送缓存消息*/
    if(VOS_TRUE == bAttachFlag)
    {
        enMoState = MN_MSG_GetMoState();
        if (MN_MSG_MO_STATE_WAIT_REPORT_IND != enMoState)
        {
            (VOS_VOID)MN_MSG_StartMo(&enSendDomain);
        }
        MN_MSG_StartMemNotification();
    }
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32  MN_MSG_IsLteNeedSmsRetry(
    LMM_SMS_ERR_CAUSE_ENUM_UINT32       enErrCause
)
{
    MN_MSG_RETRY_FLAG_U8                enRetryFlg;

    switch ( enErrCause )
    {
        case LMM_SMS_ERR_CAUSE_RRC_CONN_NOT_EXIST:
        case LMM_SMS_ERR_CAUSE_OTHERS:
            /* 需要尝试重发 */
            enRetryFlg = MSG_JudgeRetryFlg();

            if (MN_MSG_RETRY_BEGIN == enRetryFlg)
            {
                return VOS_TRUE;
            }

            return VOS_FALSE;

        case LMM_SMS_ERR_CAUSE_UE_MODE_PS_ONLY:
        case LMM_SMS_ERR_CAUSE_ACCESS_BARRED:
        case LMM_SMS_ERR_CAUSE_USIM_CS_INVALID:
        case LMM_SMS_ERR_CAUSE_USIM_PS_INVALID:
        case LMM_SMS_ERR_CAUSE_CS_SER_NOT_AVAILABLE:
        case LMM_SMS_ERR_CAUSE_CS_ATTACH_NOT_ALLOWED:
        case LMM_SMS_ERR_CAUSE_PS_ATTACH_NOT_ALLOWED:
        case LMM_SMS_ERR_CAUSE_T3402_RUNNING:
            return VOS_FALSE;

        default:
            MN_WARN_LOG("MN_MSG_IsLteNeedSmsRetry:error cause invalid");
            return VOS_FALSE;
    }


}

#endif


VOS_UINT32 TAF_MSG_IsSmsRetryCause_CmSrvRej(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enCause
)
{

    VOS_UINT8                           ucIndex;
    MN_MSG_RETRY_INFO_STRU              stRetryInfo;

    PS_MEM_SET(&stRetryInfo, 0, sizeof(stRetryInfo));

    MN_MSG_GetRetryInfo(&stRetryInfo);

    for (ucIndex = 0; ucIndex < stRetryInfo.ucSmsRetryCmSrvRejNum; ucIndex++)
    {
        if (enCause == stRetryInfo.aucSmsRetryCmSrvRejCause[ucIndex] + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 TAF_MSG_IsSmsRetryCause_MmInterErr(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enCause
)
{
    /* NAS_CC_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL是GU报resume_ind时ucCsResumeResult为fail, GU接入层异常，没必要再重拨
       NAS_CC_CAUSE_MM_INTER_ERR_BACK_TO_LTE是CSFB异系统失败重回LTE, MMC会去GU下搜网，需要重拨
       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL是消息发送异常，不需要重拨
       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL是GAS回复的失败，需要重拨
       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ECALL_INACTIVE 不需要重拨
       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE 短信业务时不需要重拨 */

    switch (enCause)
    {
        /* cs LAU rej #12现在有NV定制有业务时会触发搜网，可以允许重拨 */
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ECALL_INACTIVE:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_REL_REQ:
        case NAS_MMCM_REL_CAUSE_MM_INTER_ERR_LTE_LIMITED_SERVICE:

            return VOS_FALSE;

        default:
            return VOS_TRUE;
    }
}



VOS_UINT32 TAF_MSG_IsSmsRetryCause_RrConnFail(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enCause
)
{
    if ((NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT          == enCause)
     || (NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_ACCESS_BAR                       == enCause)
     || (NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_T3122_RUNING                     == enCause)
     || (NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_CURRENT_PROTOCOL_NOT_SUPPORT     == enCause)
     || (NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_INVALID_UE_STATE                 == enCause)
     || (NAS_MMCM_REL_CAUSE_RR_CONN_FAIL_CELL_BARRED                      == enCause))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}


VOS_UINT32 TAF_MSG_IsSmsRetryCause_RrRel(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enCause
)
{
    if ( (NAS_MMCM_REL_CAUSE_RR_REL_AUTH_REJ    == enCause)
      || (NAS_MMCM_REL_CAUSE_RR_REL_NAS_REL_REQ == enCause) )
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}


VOS_UINT32  MN_MSG_IsGuNeedSmsRetry(
    SMR_SMT_ERROR_ENUM_UINT32           enErrCause
)
{
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCmErrCause;
    MN_MSG_RP_CAUSE_ENUM_U8             enMsgRpCause;
    VOS_UINT32                          ulRslt;

    ulRslt  = VOS_TRUE;

    /* 是CS失败原因值，则判断CAUSE值 */
    if ( SMR_SMT_ERROR_CS_ERROR_BEGIN == (enErrCause & SMR_SMT_ERROR_CS_ERROR_BEGIN) )
    {

        enMmCmErrCause = (NAS_MMCM_REL_CAUSE_ENUM_UINT32)(enErrCause - SMR_SMT_ERROR_CS_ERROR_BEGIN);

        /* cm service reject */
        if ((enMmCmErrCause >= NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN)
         && (enMmCmErrCause <= NAS_MMCM_REL_CAUSE_CM_SRV_REJ_END))
        {
            ulRslt = TAF_MSG_IsSmsRetryCause_CmSrvRej(enMmCmErrCause);
        }
        /* est_cnf失败，与NAS_MM_IsAbleRecover_EstCnfFailResult的处理逻辑保持一致 */
        else if ((enMmCmErrCause >= NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN)
              && (enMmCmErrCause <= NAS_CC_CAUSE_RR_CONN_FAIL_END))
        {
            ulRslt = TAF_MSG_IsSmsRetryCause_RrConnFail(enMmCmErrCause);

        }

        /* rel_ind, 除了鉴权被拒，其他原因值与NAS_MM_IsNeedCmServiceRetry_RelIndResult的处理逻辑保持一致 */
        else if ((enMmCmErrCause >= NAS_CC_CAUSE_RR_REL_BEGIN)
              && (enMmCmErrCause <= NAS_CC_CAUSE_RR_REL_END))
        {
            ulRslt = TAF_MSG_IsSmsRetryCause_RrRel(enMmCmErrCause);
        }

        /* MM INTER ERR */
        else if ((enMmCmErrCause >= NAS_CC_CAUSE_MM_INTER_ERR_BEGIN)
              && (enMmCmErrCause <= NAS_CC_CAUSE_MM_INTER_ERR_END))
        {
            ulRslt = TAF_MSG_IsSmsRetryCause_MmInterErr(enMmCmErrCause);
        }

        else
        {
            /* CSFB Service reject，CSFB LMM fail，在短信过程中不可能出现，不需要重拨 */
            ulRslt  = VOS_FALSE;
        }

    }

    if ( SMR_SMT_ERROR_RP_ERROR_BEGIN == (enErrCause & SMR_SMT_ERROR_RP_ERROR_BEGIN) )
    {
        enMsgRpCause = (MN_MSG_RP_CAUSE_ENUM_U8)(enErrCause - SMR_SMT_ERROR_RP_ERROR_BEGIN);

        if (MN_MSG_RP_CAUSE_NETWORK_OUT_OF_ORDER == enMsgRpCause)
        {
            /* 如果是38原因值，网络乱序，一般是短信中心号码设置错误，不需要重发 */
            ulRslt  = VOS_FALSE;
        }
    }

    /* 非CS域失败，需要进行重发 */
    return ulRslt;

}



VOS_UINT8 MN_MSG_StartLinkCtrl(VOS_VOID)
{
    VOS_UINT8                           ucInCallFlg;
    VOS_UINT8                           ucRat;

    /* 2G接入技术且在呼叫中不启动短信连发功能 */
    ucInCallFlg = TAF_SDC_GetCsCallExistFlg();
    ucRat       = TAF_SDC_GetSysMode();
    if ((VOS_TRUE == ucInCallFlg)
     && (TAF_SDC_SYS_MODE_GSM == ucRat))
    {
        return MN_MSG_LINK_CTRL_DISABLE;
    }

    return MN_MSG_GetLinkCtrlParam();
}

/*lint -e438 -e830*/


VOS_VOID  MN_MSG_RcvSmsRpRpt(SMR_SMT_MO_REPORT_STRU *pstMsg)
{

    VOS_UINT32                          ulRet;
    MN_MSG_RAW_TS_DATA_STRU             stRawData;
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    MN_MSG_RP_CAUSE_STRU                stRpCause;
    MN_MSG_RP_ACK_STRU                  stRpAck;
    MN_MSG_RP_ERR_STRU                  stRpErr;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain;
    MN_MSG_LINK_CTRL_U8                 enLinkCtrl;
    MN_MSG_SEND_FAIL_FLAG_U8            enSendFailFlag;
    VOS_BOOL                            bIsTimerStart;
    VOS_BOOL                            bRetryProcess = VOS_FALSE;
    NAS_OM_SMS_MO_REPORT_STRU           stSmsMoReportPara;

    VOS_UINT32                          ulMoFailCause;


#if (FEATURE_ON == FEATURE_LTE)
    LMM_SMS_ERR_CAUSE_ENUM_UINT32       enErrorCause;
#endif

    PS_MEM_SET(&stRawData,0X00,sizeof(stRawData));
    PS_MEM_SET(&f_stMsgTsData,0X00,sizeof(f_stMsgTsData));
    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));
    PS_MEM_SET(&stRpCause,0X00,sizeof(stRpCause));
    PS_MEM_SET(&stRpAck,0X00,sizeof(stRpAck));
    PS_MEM_SET(&stRpErr,0X00,sizeof(stRpErr));

    MN_MSG_GetMoEntity(&stMoEntity);
    if (MN_MSG_MO_STATE_WAIT_REPORT_IND != stMoEntity.enSmaMoState)
    {
        MN_WARN_LOG("MSG_RcvSmsRpRpt:Mo State is NULL");
        return;
    }

    if (SMR_SMT_ERROR_NO_ERROR == pstMsg->enErrorCode)
    {
        MSG_DecodeRpAck(pstMsg->stRpduData.aucData, (VOS_UINT8)pstMsg->stRpduData.ulDataLen, &stRpAck);
        if (VOS_TRUE == stRpAck.bRpUserDataExist)
        {
            stRawData.ulLen = stRpAck.ucRpUserDataLen;
            PS_MEM_CPY(stRawData.aucData,stRpAck.aucRpUserData,stRawData.ulLen);
        }
        stRawData.enTpduType = MN_MSG_TPDU_SUBMIT_RPT_ACK;
        /* 判断当前短信重发周期定时器是否已启动,如果已经启动,则停止定时器 */
        bIsTimerStart = MN_MSG_IsTimerStarting(MN_MSG_ID_WAIT_RETRY_PERIOD);
        if (VOS_TRUE == bIsTimerStart)
        {
            MN_MSG_StopTimer(MN_MSG_ID_WAIT_RETRY_PERIOD);
        }
        /* 更新当前发送域发送成功 */
        enSendFailFlag = MN_MSG_GetSendFailFlag();
        if ( (MN_MSG_SEND_DOMAIN_PS == stMoEntity.enSendDomain)
          && (MN_MSG_SEND_FAIL_PS_DOMAIN == (enSendFailFlag & MN_MSG_SEND_FAIL_PS_DOMAIN)))
        {
            enSendFailFlag ^= MN_MSG_SEND_FAIL_PS_DOMAIN;
            MN_MSG_UpdateSendFailFlag(enSendFailFlag);
        }
        if ( (MN_MSG_SEND_DOMAIN_CS == stMoEntity.enSendDomain)
          && (MN_MSG_SEND_FAIL_CS_DOMAIN == (enSendFailFlag & MN_MSG_SEND_FAIL_CS_DOMAIN)))
        {
            enSendFailFlag ^= MN_MSG_SEND_FAIL_CS_DOMAIN;
            MN_MSG_UpdateSendFailFlag(enSendFailFlag);
        }
    }
    else
    {
        /* 更新当前发送域发送失败*/
        enSendFailFlag = MN_MSG_GetSendFailFlag();
        if ( (MN_MSG_SEND_DOMAIN_PS == stMoEntity.enSendDomain)
          && (MN_MSG_SEND_FAIL_PS_DOMAIN != (enSendFailFlag & MN_MSG_SEND_FAIL_PS_DOMAIN)))
        {
            enSendFailFlag |= MN_MSG_SEND_FAIL_PS_DOMAIN;
            MN_MSG_UpdateSendFailFlag(enSendFailFlag);
        }
        if ( (MN_MSG_SEND_DOMAIN_CS == stMoEntity.enSendDomain)
          && (MN_MSG_SEND_FAIL_CS_DOMAIN != (enSendFailFlag & MN_MSG_SEND_FAIL_CS_DOMAIN)))
        {
            enSendFailFlag |= MN_MSG_SEND_FAIL_CS_DOMAIN;
            MN_MSG_UpdateSendFailFlag(enSendFailFlag);
        }

#if (FEATURE_ON == FEATURE_LTE)


        if ((NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
         && (SMR_SMT_ERROR_EPS_ERROR_BEGIN == (pstMsg->enErrorCode & SMR_SMT_ERROR_EPS_ERROR_BEGIN)))
        {
            enErrorCause = (LMM_SMS_ERR_CAUSE_ENUM_UINT32)(pstMsg->enErrorCode - SMR_SMT_ERROR_EPS_ERROR_BEGIN);
            if (VOS_TRUE == MN_MSG_IsLteNeedSmsRetry(enErrorCause))
            {
                /* 需要进行重发,启动重发间隔定时器,定时器超时后再进行重发 */
                MN_MSG_StartTimer(MN_MSG_ID_WAIT_RETRY_INTERVAL, 0);
                MN_MSG_SaveRpErrInfo(pstMsg);
                return;
            }

            /* 重发过程结束,不需要进行任何操作,停止定时器 */
            MN_MSG_StopTimer(MN_MSG_ID_WAIT_RETRY_PERIOD);
            stRawData.enTpduType = MN_MSG_TPDU_SUBMIT_RPT_ERR;
            stRawData.ulLen      = 0;
            MN_MNTN_RecordSmsMoFailure(MSG_GetMoFailCause(&stRawData, pstMsg->enErrorCode));
#if (FEATURE_ON == FEATURE_PTM)
            /* 记录短信发送异常log */
            MN_MSG_FailErrRecord(pstMsg->enErrorCode);
#endif

            /* SMS MO FAIL事件上报 */
            stSmsMoReportPara.ulCause = pstMsg->enErrorCode;
            stSmsMoReportPara.ucSmsMr = stMoEntity.ucMr;

            NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_SMS_MO_FAIL,
                            &stSmsMoReportPara, sizeof(stSmsMoReportPara));

        }
        else
#endif

        {
            MSG_DecodeRpErr(pstMsg->stRpduData.aucData, (VOS_UINT8)pstMsg->stRpduData.ulDataLen, &stRpErr);
            PS_MEM_CPY(&stRpCause,&stRpErr.stRpCause,sizeof(stRpCause));
            if (VOS_TRUE == stRpErr.bRpUserDataExist)
            {
                stRawData.ulLen = stRpErr.ucRpUserDataLen;
                PS_MEM_CPY(stRawData.aucData,stRpErr.aucRpUserData,stRawData.ulLen);
            }
            stRawData.enTpduType = MN_MSG_TPDU_SUBMIT_RPT_ERR;

            ulMoFailCause = MSG_GetMoFailCause(&stRawData, pstMsg->enErrorCode);

            /* 判断当前是否需要进行重发 */
            bRetryProcess = MSG_IsProcessRetry(&stMoEntity, pstMsg->enErrorCode, ulMoFailCause);
            if (VOS_TRUE == bRetryProcess)
            {
                MN_MSG_SaveRpErrInfo(pstMsg);
                return;
            }

            MN_MNTN_RecordSmsMoFailure(ulMoFailCause);

#if (FEATURE_ON == FEATURE_PTM)
            /* 记录短信发送异常log */
            MN_MSG_FailErrRecord(pstMsg->enErrorCode);
#endif

            /* SMS MO FAIL事件上报 */
            stSmsMoReportPara.ulCause = pstMsg->enErrorCode;
            stSmsMoReportPara.ucSmsMr = stMoEntity.ucMr;

            NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_SMS_MO_FAIL,
                            &stSmsMoReportPara, sizeof(stSmsMoReportPara));

        }

    }

    if ((MN_MSG_MO_TYPE_MO == stMoEntity.enSmsMoType)
     || (MN_MSG_MO_TYPE_BUFFER_STK == stMoEntity.enSmsMoType))
    {
        MSG_ProcSmsRpMoRpRpt(&stMoEntity, &stRawData, pstMsg->enErrorCode);
    }
    else
    {
        MSG_ProcSmsRpSmmaRpRpt(&stMoEntity,&stRawData, pstMsg->enErrorCode);
    }

    MN_MSG_DestroyMoInfo();

    MN_MSG_StopTimer(MN_MSG_TID_LINK_CTRL);
    enLinkCtrl = MN_MSG_StartLinkCtrl();
    if (MN_MSG_LINK_CTRL_DISABLE == enLinkCtrl)
    {
        MN_MSG_SendSmsCpAckReq();
        /*查看是否有缓存消息,继续发送,没有缓存消息则发送一个空消息过去,有缓存消息则发送一条新的短信*/
        ulRet = MN_MSG_StartMo(&enSendDomain);
    }
    else
    {
        /*查看是否有缓存消息,继续发送,没有缓存消息则发送一个空消息过去,有缓存消息则发送一条新的短信*/
        ulRet = MN_MSG_StartMo(&enSendDomain);
        if ((VOS_OK != ulRet) /*当前没有消息需要发送，等待用户发送指示*/
         || (MN_MSG_SEND_DOMAIN_CS == enSendDomain))/*当前消息有消息要发送，且发送域为CS域*/
        {
            MN_MSG_StartTimer(MN_MSG_TID_LINK_CTRL, 0);
        }
    }


    return;
}
/*lint +e438 +e830*/


LOCAL VOS_VOID MSG_RcvSmsMtErrInd(SMR_SMT_MT_ERR_STRU *pstMtErr)
{
    MN_MSG_CUSTOM_CFG_INFO_STRU                   *pstMsCfgInfo = VOS_NULL_PTR;

    pstMsCfgInfo = MN_MSG_GetCustomCfgInfo();

    MN_MSG_DestroyMtInfo();

    if ((VOS_TRUE == pstMsCfgInfo->ucLocalStoreFlg)
     && (TAF_MSG_ERROR_TR2M_TIMEOUT == pstMtErr->enErrorCode))
    {
        MN_MSG_InitRcvPath();
    }

    MN_MSG_ReportDeliverErr((TAF_MSG_ERROR_ENUM_UINT32)pstMtErr->enErrorCode);
}


VOS_VOID MN_MSG_ProcSmsMsg(
    VOS_VOID                            *pMsg
)
{
    SMT_SMR_DATA_STRU                  *pstData = (SMT_SMR_DATA_STRU*)pMsg;
    SMR_SMT_ATTACH_STRU                *pstAttachData;

    switch (pstData->ulMsgName)
    {
        case SMR_SMT_ATTACH_IND:
            pstAttachData = (SMR_SMT_ATTACH_STRU *)pstData->aucData;
            MSG_RcvSmsAttachInd(pstAttachData->ucDomain, pstAttachData->bAttachFlag);
            break;
        case SMR_SMT_DATA_IND:
            MSG_RcvSmsRpData((SMR_SMT_EST_IND_STRU *)pMsg);
            break;
        case SMR_SMT_REPORT_IND:
            MN_MSG_RcvSmsRpRpt((SMR_SMT_MO_REPORT_STRU *)pstData);
            break;
        case SMR_SMT_MT_ERR_IND:
            MSG_RcvSmsMtErrInd((SMR_SMT_MT_ERR_STRU *)pstData);
#if (FEATURE_ON == FEATURE_PTM)
            /* 记录短信发送异常log */
            MN_MSG_FailErrRecord(((SMR_SMT_MT_ERR_STRU *)pstData)->enErrorCode);
#endif

            NAS_EventReport(WUEPS_PID_SMS, NAS_OM_EVENT_SMS_MT_FAIL,
                            &(((SMR_SMT_MT_ERR_STRU *)pstData)->enErrorCode), sizeof(TAF_MSG_ERROR_ENUM_UINT32));

            break;
        case SMR_SMT_LINK_CLOSE_IND:
            MN_MSG_StopTimer(MN_MSG_TID_LINK_CTRL);
            break;

        default:
            MN_WARN_LOG("MN_MSG_ProcSmsMsg:Error MsgName");
            break;
    }

}


VOS_VOID MN_MSG_PrintMoNum(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintMoNum: f_ulMsgMoNum is ", (VOS_INT32)f_ulMsgMoNum);
    return;
}


VOS_VOID MN_MSG_PrintMtNum(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintMtNum: f_ulMsgMtNum is ", (VOS_INT32)f_ulMsgMtNum);
    return;
}


VOS_UINT32 MN_MSG_AppStorageUnavailable(
    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvSmAct,
    MN_MSG_MEM_FLAG_ENUM_U8             enAppMemStatus,
    VOS_BOOL                           *pbUnavailableFlag
)
{

    if ((MN_MSG_RCVMSG_ACT_TRANSFER_AND_ACK != enRcvSmAct)
     && (MN_MSG_RCVMSG_ACT_TRANSFER_ONLY != enRcvSmAct)
     && (MN_MSG_RCVMSG_ACT_DISCARD != enRcvSmAct))
    {
        MN_WARN_LOG("MN_MSG_AppStorageUnavailable: invalid input parameter.");
        return MN_ERR_INVALIDPARM;
    }

    if (MN_MSG_RCVMSG_ACT_DISCARD == enRcvSmAct)
    {
        *pbUnavailableFlag = VOS_FALSE;
        return MN_ERR_NO_ERROR;
    }

    if (MN_MSG_MEM_FULL_SET == enAppMemStatus)
    {
        *pbUnavailableFlag = VOS_TRUE;
        return MN_ERR_NO_ERROR;
    }

    *pbUnavailableFlag = VOS_FALSE;
    return MN_ERR_NO_ERROR;
}


VOS_UINT32 MN_MSG_UeStorageUnavailable(
    MN_MSG_MEM_STORE_ENUM_U8            enSmMemStore,
    VOS_BOOL                           *pbUnavailableFlag
)
{
    VOS_UINT32                           ulRecInex;

    if ((MN_MSG_MEM_STORE_SIM != enSmMemStore)
     && (MN_MSG_MEM_STORE_NV != enSmMemStore))
    {
        MN_WARN_LOG("MN_MSG_UeStorageUnavailable: invalid input parameter.");
        return MN_ERR_INVALIDPARM;
    }

    ulRecInex = MN_MSG_GetAvailSmRecIndex(enSmMemStore);
    if (MN_MSG_NO_AVAILABLE_SMS_REC == ulRecInex)
    {
        *pbUnavailableFlag = VOS_TRUE;
        return MN_ERR_NO_ERROR;
    }

   *pbUnavailableFlag = VOS_FALSE;
   return MN_ERR_NO_ERROR;
}


VOS_UINT32 MN_MSG_ProcMoCtrl(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    const VOS_UINT8                     aucRpDataInfo[]
)
{
    MN_MSG_RP_DATA_STRU                 stRpData;
    MN_MSG_BCD_ADDR_STRU                stDestAddr;
    MN_MSG_RAW_TS_DATA_STRU             stTsRawData;
    VOS_UINT32                          ulRet;
    VOS_BOOL                            bBufferEntity;
    VOS_UINT32                          ulIndex;
    MN_MSG_MO_ENTITY_STRU               stMoEntity;

    ulRet = MN_MSG_GetSpecificStatusMoEntity(MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP,
                                             &bBufferEntity,
                                             &ulIndex,
                                             &stMoEntity);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        MN_WARN_LOG("MN_MSG_ProcMoCtrl:Usim is now Enveloping");
        return MN_ERR_CLASS_SMS_USIM_ENVELOPEPENDING;
    }

    /* 获取SUBMIT消息参数: 短信中心号码，短信目的号码 */
    PS_MEM_SET(&stRpData, 0x00, sizeof(stRpData));
    MSG_DecodeRpData(aucRpDataInfo, &stRpData);

    PS_MEM_SET(&stTsRawData, 0x00, sizeof(stTsRawData));
    stTsRawData.ulLen       = stRpData.ucRpUserDataLen;
    stTsRawData.enTpduType  = MN_MSG_TPDU_SUBMIT;
    PS_MEM_CPY(stTsRawData.aucData,stRpData.aucRpUserData, stRpData.ucRpUserDataLen);
    ulRet = MN_MSG_Decode(&stTsRawData, &f_stMsgTsData);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ProcMoCtrl: MN_MSG_Decode fail.");
        return ulRet;
    }

    /* 转换短信目的号码类型为ENVELOPE所需的BCD码类型 */
    PS_MEM_SET(&stDestAddr, 0x00, sizeof(stDestAddr));
    ulRet = TAF_STD_ConvertAsciiAddrToBcd(&f_stMsgTsData.u.stSubmit.stDestAddr,
                                  &stDestAddr);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ProcMoCtrl: get TP-DA fail.");
        return ulRet;
    }

    /* 补充LAI信息，组装并发送ENVELPE消息到USIM */
    ulRet = MN_MSG_MoSmsControlEnvelopeReq(ClientId, &stRpData.stDestAddr, &stDestAddr);

    return ulRet;
}


VOS_UINT32 MN_MSG_SendFdnCheckInfo(MN_MSG_MO_ENTITY_STRU *pstMoEntity)
{
    SI_PB_FDN_NUM_STRU                  stFdnInfo;
    MN_MSG_RP_DATA_STRU                 stRpData;
    MN_MSG_BCD_ADDR_STRU                stDestAddr;
    MN_MSG_RAW_TS_DATA_STRU             stTsRawData;
    VOS_UINT32                          ulRet;

    /* 获取SUBMIT消息参数: 短信中心号码，短信目的号码 */
    PS_MEM_SET(&stRpData, 0x00, sizeof(stRpData));
    MSG_DecodeRpData(pstMoEntity->aucRpDataInfo, &stRpData);

    PS_MEM_SET(&stTsRawData,0X00,sizeof(stTsRawData));
    stTsRawData.ulLen       = stRpData.ucRpUserDataLen;
    stTsRawData.enTpduType  = MN_MSG_TPDU_SUBMIT;
    PS_MEM_CPY(stTsRawData.aucData,stRpData.aucRpUserData, stRpData.ucRpUserDataLen);

    ulRet = MN_MSG_Decode(&stTsRawData, &f_stMsgTsData);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ProcMoCtrl: MN_MSG_Decode fail.");
        return ulRet;
    }

    /* 转换短信目的号码类型为FDN检查所需的BCD码类型 */
    PS_MEM_SET(&stDestAddr, 0x00, sizeof(stDestAddr));

    ulRet = TAF_STD_ConvertAsciiAddrToBcd(&f_stMsgTsData.u.stSubmit.stDestAddr,
                                  &stDestAddr);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ProcMoCtrl: get TP-DA fail.");
        return ulRet;
    }

    PS_MEM_SET(&stFdnInfo, 0x00, sizeof(stFdnInfo));

    stFdnInfo.ulNum1Len = stRpData.stDestAddr.ucBcdLen;
    PS_MEM_CPY(stFdnInfo.aucNum1,
               stRpData.stDestAddr.aucBcdNum,
               stFdnInfo.ulNum1Len);

    stFdnInfo.ulNum2Len = stDestAddr.ucBcdLen;
    PS_MEM_CPY(stFdnInfo.aucNum2,
               stDestAddr.aucBcdNum,
               stFdnInfo.ulNum2Len);

    ulRet = NAS_PBAPI_FdnNumCheck(WUEPS_PID_TAF, 0, pstMoEntity->clientId, &stFdnInfo);

    if (VOS_OK != ulRet)
    {
        return ulRet;
    }

    return MN_ERR_NO_ERROR;
}



#if ( VOS_WIN32 == VOS_OS_VER )

VOS_VOID MN_MSG_StubClearEfsmssFlag(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulStoreIndex;
    MN_MSG_STORE_MSG_STRU               stStoreMsg;

    MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FULL_UNSET);

    /* 释放缓存的SMMA消息 */
    ulStoreIndex = MN_MSG_GetStoreMsg(&stStoreMsg);
    if ((MN_MSG_NO_AVAILABLE_SMS_REC != ulStoreIndex)
     && (MN_MSG_MO_TYPE_SMMA == stStoreMsg.stMoInfo.enSmsMoType))
    {
        MN_MSG_FreeStoreMsg(ulStoreIndex);
    }

    MN_INFO_LOG("MN_MSG_StubClearEfsmssFlag: SMSS clear stub.");

    return;
}
#endif


VOS_UINT32 MN_MSG_CheckMemAvailable(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    VOS_BOOL                            bUnavailableFlag;
    MN_MSG_CONFIG_PARM_STRU             stCfgParm;
    MN_MSG_MT_CUSTOMIZE_ENUM_UINT8      enMtCustomize;
    VOS_BOOL                            bSmUnavailableFlag;

    MN_INFO_LOG("MN_MSG_CheckMemAvailable: step into function.");

    PS_MEM_SET(&stCfgParm, 0, sizeof(stCfgParm));

    #if ( VOS_WIN32 == VOS_OS_VER )
    if (0 != g_ucSetEfSmssClear)
    {
        MN_MSG_StubClearEfsmssFlag();
        return VOS_ERR;
    }
    #endif

    bUnavailableFlag    = VOS_TRUE;
    bSmUnavailableFlag  = VOS_TRUE;
    enMtCustomize       = MN_MSG_MT_CUSTOMIZE_NONE;
    MN_MSG_GetMtCustomizeInfo(&enMtCustomize);

    /* 获取用户的短信接收存储配置 */
    MN_MSG_GetCurCfgParm(&stCfgParm);

    /* 若用户配置的短信存储方式为非数据卡存储，则检查APP短信接收功能是否可用 */
    if (MN_MSG_RCVMSG_ACT_STORE != stCfgParm.enRcvSmAct)
    {
        ulRet = MN_MSG_AppStorageUnavailable(stCfgParm.enRcvSmAct,
                                            stCfgParm.enAppMemStatus,
                                            &bUnavailableFlag);
    }
    /* 若用户配置的短信存储方式为数据卡存储，
       否则根据用户设置的存储介质检查数据卡存储区短信接收功能是否可用 */
    else
    {
        ulRet = MN_MSG_UeStorageUnavailable(stCfgParm.enSmMemStore, &bUnavailableFlag);
    }

    if (MN_ERR_NO_ERROR != ulRet)
    {
        return VOS_ERR;
    }

    /*
    DCM定制要求: (U)SIM和用户指定的存储介质均为空闲状态，标示UE的短信存储介质空闲；
    主线版本要求: (U)SIM或用户指定的存储介质空闲，标示UE的短信存储介质空闲；
    */
    ulRet = MN_MSG_UeStorageUnavailable(MN_MSG_MEM_STORE_SIM, &bSmUnavailableFlag);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return VOS_ERR;
    }

    if (MN_MSG_MT_CUSTOMIZE_DCM == enMtCustomize)
    {
        if ((VOS_TRUE != bSmUnavailableFlag)
         && (VOS_TRUE != bUnavailableFlag))
        {
            return VOS_OK;
        }

    }
    else
    {
        if ((VOS_TRUE != bSmUnavailableFlag)
         || (VOS_TRUE != bUnavailableFlag))
        {
            return VOS_OK;
        }
    }

    return VOS_ERR;

}


VOS_UINT32 MN_MSG_MoCtrlAllowedWithModification(
    SI_STK_MOSMSCTRL_RSP_STRU          *pstMoCtrlRsp,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity
)
{
    MN_MSG_BCD_ADDR_STRU                stTpBcdAddr;
    MN_MSG_RP_DATA_STRU                 stRpData;
    MN_MSG_RAW_TS_DATA_STRU             stTsRawData;
     VOS_UINT32                         ulRet;

    PS_MEM_SET(&stTpBcdAddr, 0, sizeof(MN_MSG_BCD_ADDR_STRU));
    PS_MEM_SET(&stRpData, 0, sizeof(MN_MSG_RP_DATA_STRU));
    PS_MEM_SET(&stTsRawData, 0, sizeof(MN_MSG_RAW_TS_DATA_STRU));

    MSG_DecodeRpData(pstMoEntity->aucRpDataInfo, &stRpData);

    if (0 != pstMoCtrlRsp->OP_Addr1)
    {
        if ((pstMoCtrlRsp->Addr1.ucLen > MN_MSG_MAX_BCD_NUM_LEN)
         || (0 == pstMoCtrlRsp->Addr1.ucLen))
        {
            return MN_ERR_CLASS_SMS_MO_CTRL_USIM_PARA_ERROR;
        }

        stRpData.stDestAddr.ucBcdLen = pstMoCtrlRsp->Addr1.ucLen;
        stRpData.stDestAddr.addrType = pstMoCtrlRsp->Addr1.ucNumType;
        PS_MEM_CPY(stRpData.stDestAddr.aucBcdNum,
                   pstMoCtrlRsp->Addr1.pucAddr,
                   pstMoCtrlRsp->Addr1.ucLen);
    }

    /* 响应消息中存在TP-DA更新短信目的号码 */
    if (0 != pstMoCtrlRsp->OP_Addr2)
    {
        if ((pstMoCtrlRsp->Addr2.ucLen > MN_MSG_MAX_BCD_NUM_LEN)
         || (0 == pstMoCtrlRsp->Addr2.ucLen))
        {
            return MN_ERR_CLASS_SMS_MO_CTRL_USIM_PARA_ERROR;
        }

        stTpBcdAddr.ucBcdLen = pstMoCtrlRsp->Addr2.ucLen;
        stTpBcdAddr.addrType = pstMoCtrlRsp->Addr2.ucNumType;
        PS_MEM_CPY(stTpBcdAddr.aucBcdNum,
                   pstMoCtrlRsp->Addr2.pucAddr,
                   pstMoCtrlRsp->Addr2.ucLen);

        PS_MEM_SET(&stTsRawData,0X00,sizeof(stTsRawData));
        stTsRawData.ulLen = stRpData.ucRpUserDataLen;
        stTsRawData.enTpduType = MN_MSG_TPDU_SUBMIT;
        PS_MEM_CPY(stTsRawData.aucData,stRpData.aucRpUserData, stRpData.ucRpUserDataLen);

        ulRet = MN_MSG_Decode(&stTsRawData, &f_stMsgTsData);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        ulRet = MN_MSG_BcdAddrToAscii(&stTpBcdAddr, &f_stMsgTsData.u.stSubmit.stDestAddr);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        ulRet = MN_MSG_Encode(&f_stMsgTsData, &stTsRawData);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        /*根据24011填写参数内容,7.3.1.2 RP DATA (Mobile Station to Network)*/
        stRpData.ucRpUserDataLen = (VOS_UINT8)stTsRawData.ulLen;
        PS_MEM_CPY(stRpData.aucRpUserData, stTsRawData.aucData, stTsRawData.ulLen);
    }

    MN_MSG_EncodeRpData(&stRpData,
                        pstMoEntity->aucRpDataInfo,
                        &pstMoEntity->ucRpDataLen);

    return MN_ERR_NO_ERROR;
}


VOS_VOID MN_MSG_RcvUsimEnvelopeCnf(
        VOS_VOID                            *pMsg
)
{
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope;

    pstEnvelope = (SI_STK_ENVELOPEDWON_CNF_STRU *) pMsg;

    /* ucDataType STK用于透传EnvelopeType信息给业务发起模块 */
    if (SI_STK_ENVELOPE_PPDOWN == pstEnvelope->enEnvelopeType)
    {
        MN_MSG_RcvUsimEnvelopRsp(pstEnvelope);
        return;
    }

    if (SI_STK_ENVELOPE_SMSCRTL == pstEnvelope->enEnvelopeType)
    {
        MN_MSG_RcvUsimMoControlRsp(pstEnvelope);
        return;
    }


    return;
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID TAF_MSG_ProcEfsmsFile(
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU    *pstSubmitRptEvt
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_MEM_STORE_ENUM_U8            enCurMemStore;
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MN_OPERATION_ID_T                   bcOpId;
#endif
    enCurMemStore = MN_MSG_MEM_STORE_NONE;

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MEM_STORE_SIM == pstMoEntity->enSaveArea)
     || (MN_MSG_MEM_STORE_NV == pstMoEntity->enSaveArea))
#else
    if (MN_MSG_MEM_STORE_SIM == pstMoEntity->enSaveArea)
#endif
    {
        ulRet = VOS_FALSE;

        ulRet = MSG_UpdateEfSmsInfo(pstMoEntity,&enCurMemStore);
        MN_INFO_LOG1("TAF_MSG_UpdateEfsmsInfo: result of TAF_MSG_UpdateEfsmsInfo is ",
                     (VOS_INT32)ulRet);

        pstSubmitRptEvt->enSaveArea   = enCurMemStore;
        pstSubmitRptEvt->ulSaveIndex = pstMoEntity->ulSaveIndex;

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
        if ((MN_MSG_MEM_STORE_NV == enCurMemStore)
         && (VOS_OK == ulRet))
        {
            bcOpId = MN_MSG_GetBCopId();
            MN_MSG_ReportSmChanged(pstMoEntity->clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
        }
#endif
    }
}


VOS_VOID TAF_MSG_RcvImsaRpRpt(
    SMR_SMT_MO_REPORT_STRU *pstMsg
)
{
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    MN_MSG_RP_CAUSE_STRU                stRpCause;
    MN_MSG_RP_ERR_STRU                  stRpErr;
    MN_MSG_RP_ACK_STRU                  stRpAck;
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU     stSubmitRptEvt;
    NAS_OM_SMS_MO_REPORT_STRU           stSmsMoReportPara;

    PS_MEM_SET(&f_stMsgTsData,0X00,sizeof(f_stMsgTsData));
    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));
    PS_MEM_SET(&stRpCause,0X00,sizeof(stRpCause));
    PS_MEM_SET(&stRpErr,0X00,sizeof(stRpErr));
    PS_MEM_SET(&stRpAck,0X00,sizeof(stRpAck));
    PS_MEM_SET(&stSubmitRptEvt,0X00,sizeof(stSubmitRptEvt));

    MN_MSG_GetMoEntity(&stMoEntity);
    if (MN_MSG_MO_STATE_WAIT_REPORT_IND != stMoEntity.enSmaMoState)
    {
        MN_WARN_LOG("MSG_RcvSmsRpRpt:Mo State is NULL");
        return;
    }

    if (SMR_SMT_ERROR_NO_ERROR == pstMsg->enErrorCode)
    {
        MSG_DecodeRpAck(pstMsg->stRpduData.aucData, (VOS_UINT8)pstMsg->stRpduData.ulDataLen, &stRpAck);
        if (VOS_TRUE == stRpAck.bRpUserDataExist)
        {
            stSubmitRptEvt.stRawData.ulLen = stRpAck.ucRpUserDataLen;
            PS_MEM_CPY(&(stSubmitRptEvt.stRawData.aucData[0]),
                       stRpAck.aucRpUserData,
                       stRpAck.ucRpUserDataLen);
        }
        stSubmitRptEvt.stRawData.enTpduType = MN_MSG_TPDU_SUBMIT_RPT_ACK;

        if ((MN_MSG_MO_TYPE_MO == stMoEntity.enSmsMoType)
         || (MN_MSG_MO_TYPE_BUFFER_STK == stMoEntity.enSmsMoType))
        {
            TAF_MSG_ProcEfsmsFile(&stMoEntity, &stSubmitRptEvt);
        }
        else
        {
            if (VOS_TRUE == stMoEntity.bReportFlag)
            {
                (VOS_VOID)MN_MSG_UpdateAppMemStatus(MN_MSG_MEM_FULL_UNSET);
            }

            MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FULL_UNSET);
        }

        /* SMS MO SUCC事件上报 */
        stSmsMoReportPara.ulCause = MN_ERR_NO_ERROR;
        stSmsMoReportPara.ucSmsMr = stMoEntity.ucMr;

        NAS_EventReport(WUEPS_PID_SMS, NAS_OM_EVENT_SMS_MO_SUCC,
                        &stSmsMoReportPara, sizeof(stSmsMoReportPara));
    }
    else
    {
        MSG_DecodeRpErr(pstMsg->stRpduData.aucData, (VOS_UINT8)pstMsg->stRpduData.ulDataLen, &stRpErr);
        PS_MEM_CPY(&stRpCause,&stRpErr.stRpCause,sizeof(stRpCause));
        if (VOS_TRUE == stRpErr.bRpUserDataExist)
        {
            stSubmitRptEvt.stRawData.ulLen = stRpErr.ucRpUserDataLen;
            PS_MEM_CPY(&(stSubmitRptEvt.stRawData.aucData[0]),
                       stRpErr.aucRpUserData,
                       stSubmitRptEvt.stRawData.ulLen);
        }
        stSubmitRptEvt.stRawData.enTpduType = MN_MSG_TPDU_SUBMIT_RPT_ERR;

        MN_MNTN_RecordSmsMoFailure(MSG_GetMoFailCause(&(stSubmitRptEvt.stRawData), pstMsg->enErrorCode));

        /* SMS MO FAIL事件上报 */
        stSmsMoReportPara.ucSmsMr = stMoEntity.ucMr;
        stSmsMoReportPara.ulCause = MSG_GetMoFailCause(&(stSubmitRptEvt.stRawData), pstMsg->enErrorCode);

        NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_SMS_MO_FAIL,
                        &stSmsMoReportPara, sizeof(stSmsMoReportPara));
    }

    stSubmitRptEvt.ucMr        = stMoEntity.ucMr;
    stSubmitRptEvt.ulSaveIndex = stMoEntity.ulSaveIndex;
    stSubmitRptEvt.enSaveArea  = stMoEntity.enSaveArea;
    stSubmitRptEvt.enErrorCode = MSG_GetMoFailCause(&(stSubmitRptEvt.stRawData), pstMsg->enErrorCode);

    /* 通知SPM短信发送结果 */
    TAF_MSG_SpmMsgReportInd(&stSubmitRptEvt, &stMoEntity, TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP);

    /* destory MO entity*/
    MN_MSG_DestroyMoInfo();

    return;
}


VOS_VOID TAF_MSG_ProcImsaMsg(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                   *pstSmsMsg = VOS_NULL_PTR;

    pstSmsMsg = (MSG_HEADER_STRU *)pMsg;

    switch (pstSmsMsg->ulMsgName)
    {
        case ID_IMSA_MSG_DATA_IND:
            MSG_RcvSmsRpData((SMR_SMT_EST_IND_STRU *)pMsg);
            break;

        case ID_IMSA_MSG_REPORT_IND:
            TAF_MSG_RcvImsaRpRpt((SMR_SMT_MO_REPORT_STRU *)pMsg);
            break;

        case ID_IMSA_MSG_MT_ERR_IND:
            MSG_RcvSmsMtErrInd((SMR_SMT_MT_ERR_STRU*)pMsg);
            break;

        default:
            MN_WARN_LOG("TAF_MSG_ProcImsaMsg:Error MsgName");
            break;
    }
}
#endif


/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

