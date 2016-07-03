

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXCallDecKmcMsg.h"
#include "TafLog.h"
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_DEC_KMC_MSG_C
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)

VOS_UINT32 TAF_XCALL_ConvertBcdToDecimal(
    VOS_UINT8                                              *pucSrcData,
    VOS_UINT16                                             *pusDestData
)
{
    VOS_UINT8                           ucHigh;
    VOS_UINT8                           ucLow;

    ucHigh                              =0x00;
    ucLow                               =0x00;

    ucHigh = (VOS_UINT8)(((*pucSrcData) & 0xF0) >> 4);
    ucLow  = (*pucSrcData) & 0x0F;

    /*如果BCD格式中的数字不是0-9,则返回失败*/
    if ((0x09 < ucHigh)
     || (0x09 < ucLow))
    {
        return VOS_FALSE;
    }

    *pusDestData = ucHigh * 10 + ucLow;

    return VOS_TRUE;
}

VOS_UINT32 TAF_XCALL_ConvertBcdTimeStampToDecimalTimeStamp(
    VOS_UINT8                                              *pucSrcData,
    TAF_STD_TIME_ZONE_TYPE_STRU                            *pstTimeStamp
)
{
    VOS_UINT16                          usYearTmp;

    usYearTmp = 0;

    if (VOS_FALSE == TAF_XCALL_ConvertBcdToDecimal(pucSrcData, &usYearTmp))
    {
        return VOS_FALSE;
    }

    pstTimeStamp->usYear   = (VOS_UINT16)(usYearTmp * 100);
    pucSrcData++;
    usYearTmp = 0;

    if (VOS_FALSE == TAF_XCALL_ConvertBcdToDecimal(pucSrcData, &usYearTmp))
    {
        return VOS_FALSE;
    }

    pstTimeStamp->usYear   +=usYearTmp;
    pucSrcData++;

    if (VOS_FALSE == TAF_XCALL_ConvertBcdToDecimal(pucSrcData,
                                                   &pstTimeStamp->usMonth))
    {
        return VOS_FALSE;
    }

    pucSrcData++;

    if (VOS_FALSE == TAF_XCALL_ConvertBcdToDecimal(pucSrcData,
                                                   &pstTimeStamp->usDay))
    {
        return VOS_FALSE;
    }

    pucSrcData++;

    if (VOS_FALSE == TAF_XCALL_ConvertBcdToDecimal(pucSrcData,
                                                   &pstTimeStamp->usHour))
    {
        return VOS_FALSE;
    }

    pucSrcData++;

    if (VOS_FALSE == TAF_XCALL_ConvertBcdToDecimal(pucSrcData,
                                                   &pstTimeStamp->usMinute))
    {
        return VOS_FALSE;
    }

    pucSrcData++;

    if (VOS_FALSE == TAF_XCALL_ConvertBcdToDecimal(pucSrcData,
                                                   &pstTimeStamp->usSecond))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

VOS_VOID TAF_XCALL_DecKeyRspMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
)
{
    TAF_XCALL_KMC_MSG_KEY_RSP_STRU     *pstKeyRsp = VOS_NULL_PTR;

    pstKeyRsp = &pstDecodedData->u.stKeyRsp;

    /*密文长度*/
    pstKeyRsp->stCipher.usCipherLen = ((VOS_UINT16)(*pucdata_ptr++)) & 0x00FF;

    /* 密文长度等于0，大于门限值 或者 地址超出 User Data 的范围
    这里没有加入保留字段长度的判断,是因为担心消息内容中如果没有填充保留字段,而判断保留字段长度,就会导致解码失败.
    另外,再后续的处理中,保留字段目前没有用到*/
    if ((0 == pstKeyRsp->stCipher.usCipherLen)
     || ((pucdata_ptr + pstKeyRsp->stCipher.usCipherLen) >= (pucMsgData + usMsgDataLen)))
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_CIPHER_LEN_ERR;
        return ;
    }

    /*密文*/
    PS_MEM_CPY(pstKeyRsp->stCipher.aucCipher, pucdata_ptr, pstKeyRsp->stCipher.usCipherLen);
    pucdata_ptr = pucdata_ptr + pstKeyRsp->stCipher.usCipherLen;

    /*KMC签名信息长度*/
    pstKeyRsp->stSignInfo.ucSignInfoLen = *pucdata_ptr++;

    /* 签名信息长度大于门限值 或者 地址超出 User Data 的范围 */
    if ((0 == pstKeyRsp->stSignInfo.ucSignInfoLen)
     || ((pucdata_ptr + pstKeyRsp->stSignInfo.ucSignInfoLen) > (pucMsgData + usMsgDataLen)))
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SIGN_INFO_LEN_ERR;
        return ;
    }

    /* 签名信息*/
    PS_MEM_CPY(pstKeyRsp->stSignInfo.aucSignInfo, pucdata_ptr, pstKeyRsp->stSignInfo.ucSignInfoLen);
    pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}

VOS_VOID TAF_XCALL_DecMtEncryptIndMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
)
{
    /*主叫号码长度*/
    pstDecodedData->u.stMtEncryptInd.ucRemoteNumberLen = *pucdata_ptr++;

    /* 主叫号码长度等于0，大于门限值 或者 地址超出 User Data 的范围 */
    if ((0 == pstDecodedData->u.stMtEncryptInd.ucRemoteNumberLen)
     || (TAF_XCALL_KMC_MSG_MAX_REMOTE_NUMBER_LEN < pstDecodedData->u.stMtEncryptInd.ucRemoteNumberLen)
     || ((pucdata_ptr + pstDecodedData->u.stMtEncryptInd.ucRemoteNumberLen) > (pucMsgData + usMsgDataLen)))
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_REMOTE_NUMBER_LEN_ERR;
        return ;
    }

    /*为了考虑兼容性，如果长度不满足6个字节，打印一个告警信息，在长度许可范围内，可继续解析号码*/
    if (TAF_XCALL_KMC_MSG_MAX_REMOTE_NUMBER_LEN > pstDecodedData->u.stMtEncryptInd.ucRemoteNumberLen)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_XCALL_DecMtEncryptIndMsg():RemoteNumberLen < Max len (6)!");
    }

    PS_MEM_CPY(pstDecodedData->u.stMtEncryptInd.aucRemoteNumber, pucdata_ptr, pstDecodedData->u.stMtEncryptInd.ucRemoteNumberLen);

    pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}

VOS_VOID TAF_XCALL_DecErrIndMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
)
{
    /*错误原因值 */
    pstDecodedData->u.stErrInd.enErrCause = *pucdata_ptr;

    if (TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_BUTT <= pstDecodedData->u.stErrInd.enErrCause)
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_ERR_IND_CAUSE_ERR;
        return ;
    }

    pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}

VOS_VOID TAF_XCALL_DecPubKeyUpdateMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
)
{
    if (TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_REQ_HEADER_LEN >= usMsgDataLen)
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_MSG_NOT_ENOUGH;
        return ;
    }

    /*KMC公钥版本*/
    pstDecodedData->u.stPubKeyUpdateInd.ucKeyVersion        = *pucdata_ptr++;

    /*KMC公钥长度*/
    pstDecodedData->u.stPubKeyUpdateInd.stPubKey.ucKeyLen            = *pucdata_ptr++;

    /* 公钥长度大于门限值 或者 地址超出 User Data 的范围 */
    if ((0 == pstDecodedData->u.stPubKeyUpdateInd.stPubKey.ucKeyLen)
     || (TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN < pstDecodedData->u.stPubKeyUpdateInd.stPubKey.ucKeyLen)
     || ((pucdata_ptr + pstDecodedData->u.stPubKeyUpdateInd.stPubKey.ucKeyLen) >= (pucMsgData + usMsgDataLen)))
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_PUB_KEY_LEN_ERR;
        return ;
    }

    PS_MEM_CPY(pstDecodedData->u.stPubKeyUpdateInd.stPubKey.aucKey,
               pucdata_ptr,
               pstDecodedData->u.stPubKeyUpdateInd.stPubKey.ucKeyLen);
    pucdata_ptr = pucdata_ptr + pstDecodedData->u.stPubKeyUpdateInd.stPubKey.ucKeyLen;

    /*KMC签名信息长度*/
    pstDecodedData->u.stPubKeyUpdateInd.stSignInfo.ucSignInfoLen       = *pucdata_ptr++;

    /* 签名信息长度等于0，大于门限值 或者 地址超出 User Data 的范围 */
    if ((0 == pstDecodedData->u.stPubKeyUpdateInd.stSignInfo.ucSignInfoLen )
     || ((pucdata_ptr + pstDecodedData->u.stPubKeyUpdateInd.stSignInfo.ucSignInfoLen) > (pucMsgData + usMsgDataLen)))
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SIGN_INFO_LEN_ERR;
        return ;
    }

    PS_MEM_CPY(pstDecodedData->u.stPubKeyUpdateInd.stSignInfo.aucSignInfo,
               pucdata_ptr,
               pstDecodedData->u.stPubKeyUpdateInd.stSignInfo.ucSignInfoLen);
    pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}

VOS_VOID TAF_XCALL_DecPubKeyUpdateAckMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
)
{
    if ((TAF_XCALL_KMC_MSG_HEADER_LEN + TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN) > usMsgDataLen)
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_MSG_NOT_ENOUGH;
        return ;
    }

    /*随机数*/
    PS_MEM_CPY(pstDecodedData->u.stPubKeyUpdateAck.aucRandomData, pucdata_ptr, TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN);
    pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}

VOS_VOID TAF_XCALL_DecRemoteCtrlCmdMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
)
{

    if (TAF_XCALL_KMC_MSG_REMOTE_CTRL_HEADER_LEN > usMsgDataLen)
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_MSG_NOT_ENOUGH;
        return ;
    }

    /*KMC公钥版本*/
    pstDecodedData->u.stRemoteCtrlInd.ucKeyVersion = *pucdata_ptr++;

    /*时间戳*/
    if ( VOS_FALSE == TAF_XCALL_ConvertBcdTimeStampToDecimalTimeStamp(pucdata_ptr,
                                                                      &pstDecodedData->u.stRemoteCtrlInd.stTimeStamp))
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_TIME_STAMP_ERR;
        return ;
    }

    pucdata_ptr += TAF_XCALL_KMC_MSG_TIME_STAMP_LEN;

    /*远程控制指令类型*/
    pstDecodedData->u.stRemoteCtrlInd.enRomoteCtrlCmdType   = *pucdata_ptr++;

    if (TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_BUTT <= pstDecodedData->u.stRemoteCtrlInd.enRomoteCtrlCmdType)
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_ROMOTE_CTRL_CMD_TYPE_ERR;
        return ;
    }

     /*KMC签名信息长度*/
    pstDecodedData->u.stRemoteCtrlInd.stSignInfo.ucSignInfoLen = *pucdata_ptr++;


    /* 签名信息长度等于0，大于门限值 或者 地址超出 User Data 的范围 */
    if ((0 == pstDecodedData->u.stRemoteCtrlInd.stSignInfo.ucSignInfoLen)
     || ((pucdata_ptr + pstDecodedData->u.stRemoteCtrlInd.stSignInfo.ucSignInfoLen) > (pucMsgData + usMsgDataLen)))
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SIGN_INFO_LEN_ERR;
        return ;
    }

    PS_MEM_CPY(pstDecodedData->u.stRemoteCtrlInd.stSignInfo.aucSignInfo,
               pucdata_ptr,
               pstDecodedData->u.stRemoteCtrlInd.stSignInfo.ucSignInfoLen);
    pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}



VOS_VOID TAF_XCALL_DecodeKmcMsg(
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                          usMsgDataLen,
    TAF_XCALL_KMC_MSG_STRU             *pstDecodedData
)
{
    VOS_UINT8                          *pucdata_ptr = VOS_NULL_PTR;

    if (TAF_XCALL_KMC_MSG_HEADER_LEN > usMsgDataLen)
    {
        pstDecodedData->enRslt    = TAF_XCALL_KMC_MSG_PROCESS_RSLT_MSG_NOT_ENOUGH;
        pstDecodedData->enSmsType = TAF_XCALL_KMC_MSG_TYPE_UNKNOWN;
        return;
    }

    pucdata_ptr = pucMsgData ;

    /* specific msg identifier*/
    pstDecodedData->ucSpecSmsID = *pucdata_ptr++;

    /* extended control field*/
    PS_MEM_CPY(pstDecodedData->aucExtCtrlField, pucdata_ptr, TAF_XCALL_KMC_MSG_EXT_CTRL_BYTES);
    pucdata_ptr = pucdata_ptr+ TAF_XCALL_KMC_MSG_EXT_CTRL_BYTES;

    /*消息类型*/
    pstDecodedData->enSmsType = *pucdata_ptr++;

    switch(pstDecodedData->enSmsType)
    {
        case TAF_XCALL_KMC_MSG_TYPE_MO_KEY_RSP:
        case TAF_XCALL_KMC_MSG_TYPE_MT_KEY_RSP:
        {
            TAF_XCALL_DecKeyRspMsg(pucMsgData, usMsgDataLen, pucdata_ptr, pstDecodedData);
            break;
        }
        case TAF_XCALL_KMC_MSG_TYPE_MT_ENCRYPT_IND:
        {
            TAF_XCALL_DecMtEncryptIndMsg(pucMsgData, usMsgDataLen, pucdata_ptr, pstDecodedData);
            break;
        }
        case TAF_XCALL_KMC_MSG_TYPE_ERR_IND:
        {
            TAF_XCALL_DecErrIndMsg(pucMsgData, usMsgDataLen, pucdata_ptr, pstDecodedData);
            break;
        }
        case TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_IND:
        {
            TAF_XCALL_DecPubKeyUpdateMsg(pucMsgData, usMsgDataLen, pucdata_ptr, pstDecodedData);
            break;
        }
        case TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_ACK:
        {
            TAF_XCALL_DecPubKeyUpdateAckMsg(pucMsgData, usMsgDataLen, pucdata_ptr, pstDecodedData);
            break;
        }
        case TAF_XCALL_KMC_MSG_TYPE_ROMOTE_CTRL_CMD_IND:
        {
            TAF_XCALL_DecRemoteCtrlCmdMsg(pucMsgData, usMsgDataLen, pucdata_ptr, pstDecodedData);
            break;
        }
        default:
        {
            pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_MSG_TYPE_UNKNOWN;
            break;
        }
    }

}

#endif

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */














































