

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "product_config.h"
#include "vos.h"
#include "Taf_Tafm_Remote.h"
#include "MnComm.h"
#include "MnErrorCode.h"
#include "TafClientApi.h"

#include "mdrv.h"
#include "NasComm.h"
#include "NasStkInterface.h"
#include "NasUsimmApi.h"

#include "TafAppMma.h"
#include "TafApsApi.h"
#include "MnCall.h"

#include "MmaAppLocal.h"
#include "TafSdcCtx.h"
#include "TafAppMma.h"

#include "TafMtaPhy.h"
#include "MtaPhyInterface.h"
#include "MnCallApi.h"
#include "Taf_MmiStrParse.h"

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
#include "TafMtcInterface.h"
#endif

#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
  1 类型定义
*****************************************************************************/


/*****************************************************************************
   2 变量定义
*****************************************************************************/

/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID PS_FILE_ID_MN_COMM_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

LOCAL VOS_BOOL f_bMnUsimPresent = VOS_FALSE;

NAS_MNTN_MSG_INFO_STRU                  g_stMnMntnErrorLogMsg = {0};

LOCAL MN_QRYMSGPARA_ATTR                f_astMnQryMsgParaAttr[] = {


    {TAF_PH_IMSI_ID_PARA,           {0,0,0},sizeof(TAF_PH_IMSI_STRU)},
    {TAF_PH_MS_CLASS_PARA,          {0,0,0},sizeof(TAF_PH_MS_CLASS_TYPE)},
    {TAF_PH_CUR_FREQ,               {0,0,0},sizeof(TAF_PH_FRQ_STRU)},




    {TAF_PH_ICC_ID,                 {0,0,0},sizeof(TAF_PH_ICC_ID_STRU)},
    {TAF_PH_PNN_PARA,               {0,0,0},sizeof(TAF_PH_USIM_PNN_CNF_STRU)},
    {TAF_PH_CPNN_PARA,              {0,0,0},sizeof(TAF_PH_USIM_PNN_CNF_STRU)},
    {TAF_PH_OPL_PARA,               {0,0,0},sizeof(TAF_PH_USIM_OPL_CNF_STRU)},

    {TAF_PH_PNN_RANGE_PARA,         {0,0,0},sizeof(TAF_PH_QRY_USIM_RANGE_INFO_STRU)},
    {TAF_PH_OPL_RANGE_PARA,         {0,0,0},sizeof(TAF_PH_QRY_USIM_RANGE_INFO_STRU)},


};


TAF_CS_ERR_CODE_MAP_STRU g_astMnCallErrCodeMapTbl[] =
{
    {TAF_CS_CAUSE_CC_NW_PROTOCOL_ERROR_UNSPECIFIED                  ,   MN_CALL_INVALID_CAUSE                                   },
    {TAF_CS_CAUSE_CC_NW_UNASSIGNED_CAUSE                            ,   MN_CALL_UNASSIGNED_CAUSE                                },
    {TAF_CS_CAUSE_CC_NW_NO_ROUTE_TO_DEST                            ,   MN_CALL_NO_ROUTE_TO_DEST                                },
    {TAF_CS_CAUSE_CC_NW_CHANNEL_UNACCEPTABLE                        ,   MN_CALL_CHANNEL_UNACCEPTABLE                            },
    {TAF_CS_CAUSE_CC_NW_OPERATOR_DETERMINED_BARRING                 ,   MN_CALL_OPERATOR_DETERMINED_BARRING                     },
    {TAF_CS_CAUSE_CC_NW_NORMAL_CALL_CLEARING                        ,   MN_CALL_NORMAL_CALL_CLEARING                            },
    {TAF_CS_CAUSE_CC_NW_USER_BUSY                                   ,   MN_CALL_USER_BUSY                                       },
    {TAF_CS_CAUSE_CC_NW_NO_USER_RESPONDING                          ,   MN_CALL_NO_USER_RESPONDING                              },
    {TAF_CS_CAUSE_CC_NW_USER_ALERTING_NO_ANSWER                     ,   MN_CALL_USER_ALERTING_NO_ANSWER                         },
    {TAF_CS_CAUSE_CC_NW_CALL_REJECTED                               ,   MN_CALL_CALL_REJECTED                                   },
    {TAF_CS_CAUSE_CC_NW_NUMBER_CHANGED                              ,   MN_CALL_NUMBER_CHANGED                                  },
    {TAF_CS_CAUSE_CC_NW_PRE_EMPTION                                 ,   MN_CALL_PRE_EMPTION                                     },
    {TAF_CS_CAUSE_CC_NW_NON_SELECTED_USER_CLEARING                  ,   MN_CALL_NON_SELECTED_USER_CLEARING                      },
    {TAF_CS_CAUSE_CC_NW_DESTINATION_OUT_OF_ORDER                    ,   MN_CALL_DESTINATION_OUT_OF_ORDER                        },
    {TAF_CS_CAUSE_CC_NW_INVALID_NUMBER_FORMAT                       ,   MN_CALL_INVALID_NUMBER_FORMAT                           },
    {TAF_CS_CAUSE_CC_NW_FACILITY_REJECTED                           ,   MN_CALL_FACILITY_REJECTED                               },
    {TAF_CS_CAUSE_CC_NW_RESPONSE_TO_STATUS_ENQUIRY                  ,   MN_CALL_RESPONSE_TO_STATUS_ENQUIRY                      },
    {TAF_CS_CAUSE_CC_NW_NORMAL_UNSPECIFIED                          ,   MN_CALL_NORMAL_UNSPECIFIED                              },
    {TAF_CS_CAUSE_CC_NW_NO_CIRCUIT_CHANNEL_AVAILABLE                ,   MN_CALL_NO_CIRCUIT_CHANNEL_AVAILABLE                    },
    {TAF_CS_CAUSE_CC_NW_NETWORK_OUT_OF_ORDER                        ,   MN_CALL_NETWORK_OUT_OF_ORDER                            },
    {TAF_CS_CAUSE_CC_NW_TEMPORARY_FAILURE                           ,   MN_CALL_TEMPORARY_FAILURE                               },
    {TAF_CS_CAUSE_CC_NW_SWITCHING_EQUIPMENT_CONGESTION              ,   MN_CALL_SWITCHING_EQUIPMENT_CONGESTION                  },
    {TAF_CS_CAUSE_CC_NW_ACCESS_INFORMATION_DISCARDED                ,   MN_CALL_ACCESS_INFORMATION_DISCARDED                    },
    {TAF_CS_CAUSE_CC_NW_REQUESTED_CIRCUIT_CHANNEL_NOT_AVAILABLE     ,   MN_CALL_REQUESTED_CIRCUIT_CHANNEL_NOT_AVAILABLE         },
    {TAF_CS_CAUSE_CC_NW_RESOURCES_UNAVAILABLE_UNSPECIFIED           ,   MN_CALL_RESOURCES_UNAVAILABLE_UNSPECIFIED               },
    {TAF_CS_CAUSE_CC_NW_QUALITY_OF_SERVICE_UNAVAILABLE              ,   MN_CALL_QUALITY_OF_SERVICE_UNAVAILABLE                  },
    {TAF_CS_CAUSE_CC_NW_REQUESTED_FACILITY_NOT_SUBSCRIBED           ,   MN_CALL_REQUESTED_FACILITY_NOT_SUBSCRIBED               },
    {TAF_CS_CAUSE_CC_NW_INCOMING_CALL_BARRED_WITHIN_CUG             ,   MN_CALL_INCOMING_CALL_BARRED_WITHIN_CUG                 },
    {TAF_CS_CAUSE_CC_NW_BEARER_CAPABILITY_NOT_AUTHORISED            ,   MN_CALL_BEARER_CAPABILITY_NOT_AUTHORISED                },
    {TAF_CS_CAUSE_CC_NW_BEARER_CAPABILITY_NOT_PRESENTLY_AVAILABLE   ,   MN_CALL_BEARER_CAPABILITY_NOT_PRESENTLY_AVAILABLE       },
    {TAF_CS_CAUSE_CC_NW_SERVICE_OR_OPTION_NOT_AVAILABLE             ,   MN_CALL_SERVICE_OR_OPTION_NOT_AVAILABLE                 },
    {TAF_CS_CAUSE_CC_NW_BEARER_SERVICE_NOT_IMPLEMENTED              ,   MN_CALL_BEARER_SERVICE_NOT_IMPLEMENTED                  },
    {TAF_CS_CAUSE_CC_NW_ACM_GEQ_ACMMAX                              ,   MN_CALL_ACM_GEQ_ACMMAX                                  },
    {TAF_CS_CAUSE_CC_NW_REQUESTED_FACILITY_NOT_IMPLEMENTED          ,   MN_CALL_REQUESTED_FACILITY_NOT_IMPLEMENTED              },
    {TAF_CS_CAUSE_CC_NW_ONLY_RESTRICTED_DIGITAL_INFO_BC_AVAILABLE   ,   MN_CALL_ONLY_RESTRICTED_DIGITAL_INFO_BC_AVAILABLE       },
    {TAF_CS_CAUSE_CC_NW_SERVICE_OR_OPTION_NOT_IMPLEMENTED           ,   MN_CALL_SERVICE_OR_OPTION_NOT_IMPLEMENTED               },
    {TAF_CS_CAUSE_CC_NW_INVALID_TRANSACTION_ID_VALUE                ,   MN_CALL_INVALID_TRANSACTION_ID_VALUE                    },
    {TAF_CS_CAUSE_CC_NW_USER_NOT_MEMBER_OF_CUG                      ,   MN_CALL_USER_NOT_MEMBER_OF_CUG                          },
    {TAF_CS_CAUSE_CC_NW_INCOMPATIBLE_DESTINATION                    ,   MN_CALL_INCOMPATIBLE_DESTINATION                        },
    {TAF_CS_CAUSE_CC_NW_INVALID_TRANSIT_NETWORK_SELECTION           ,   MN_CALL_INVALID_TRANSIT_NETWORK_SELECTION               },
    {TAF_CS_CAUSE_CC_NW_SEMANTICALLY_INCORRECT_MESSAGE              ,   MN_CALL_SEMANTICALLY_INCORRECT_MESSAGE                  },
    {TAF_CS_CAUSE_CC_NW_INVALID_MANDATORY_INFORMATION               ,   MN_CALL_INVALID_MANDATORY_INFORMATION                   },
    {TAF_CS_CAUSE_CC_NW_MESSAGE_TYPE_NON_EXISTENT                   ,   MN_CALL_MESSAGE_TYPE_NON_EXISTENT                       },
    {TAF_CS_CAUSE_CC_NW_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROT_STATE ,   MN_CALL_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROT_STATE     },
    {TAF_CS_CAUSE_CC_NW_IE_NON_EXISTENT_OR_NOT_IMPLEMENTED          ,   MN_CALL_IE_NON_EXISTENT_OR_NOT_IMPLEMENTED              },
    {TAF_CS_CAUSE_CC_NW_CONDITIONAL_IE_ERROR                        ,   MN_CALL_CONDITIONAL_IE_ERROR                            },
    {TAF_CS_CAUSE_CC_NW_MESSAGE_NOT_COMPATIBLE_WITH_PROTOCOL_STATE  ,   MN_CALL_MESSAGE_NOT_COMPATIBLE_WITH_PROTOCOL_STATE      },
    {TAF_CS_CAUSE_CC_NW_RECOVERY_ON_TIMER_EXPIRY                    ,   MN_CALL_RECOVERY_ON_TIMER_EXPIRY                        },
    {TAF_CS_CAUSE_CC_NW_PROTOCOL_ERROR_UNSPECIFIED                  ,   MN_CALL_PROTOCOL_ERROR_UNSPECIFIED                      },
    {TAF_CS_CAUSE_CC_NW_INTERWORKING_UNSPECIFIED                    ,   MN_CALL_INTERWORKING_UNSPECIFIED                        },
    {TAF_CS_CAUSE_CC_NW_PROTOCOL_ERROR_UNSPECIFIED                  ,   MN_CALL_CC_CAUSE_BUTT                                   }

};


VOS_UINT16 f_ausMnAsciiSfxDefAlpha[MN_MAX_GSM7BITDEFALPHA_NUM] =
{
/* 0x00 */  '@',    0x00a3, '$',    0x00a5, 0x00e8, 0x00e9, 0x00f9, 0x00ec,
/* 0x08 */  0x00f2, 0x00c7, 0x000a, 0x00d8, 0x00f8, 0x000d, 0x00c5, 0x00e5,
/* 0x10 */  0x0394, '_',    0x03a6, 0x0393, 0x039b, 0x03a9, 0x03a0, 0x03a8,
/* 0x18 */  0x03a3, 0x0398, 0x039e, 0x00a0,   0x00c6, 0x00e6, 0x00df, 0x00c9,
/* 0x20 */  ' ',    '!',    0x0022, '#',    0x00a4, '%',    '&',    0x0027,
/* 0x28 */  '(',    ')',    '*',    '+',    ',',    '-',    '.',    '/',
/* 0x30 */  '0',    '1',    '2',    '3',    '4',    '5',    '6',    '7',
/* 0x38 */  '8',    '9',    ':',    ';',    '<',    '=',    '>',    '?',
/* 0x40 */  0x00a1, 'A',    'B',    'C',    'D',    'E',    'F',    'G',
/* 0x48 */  'H',    'I',    'J',    'K',    'L',    'M',    'N',    'O',
/* 0x50 */  'P',    'Q',    'R',    'S',    'T',    'U',    'V',    'W',
/* 0x58 */  'X',    'Y',    'Z',    0x00c4, 0x00d6, 0x00d1, 0x00dc, 0x00a7,
/* 0x60 */  0x00bf, 'a',    'b',    'c',    'd',    'e',    'f',    'g',
/* 0x68 */  'h',    'i',    'j',    'k',    'l',    'm',    'n',    'o',
/* 0x70 */  'p',    'q',    'r',    's',    't',    'u',    'v',    'w',
/* 0x78 */  'x',    'y',    'z',    0x00e4, 0x00f6, 0x00f1, 0x00fc, 0x00e0
};

/*lint -save -e958 */

/*****************************************************************************
   3 函数实现
*****************************************************************************/

MN_CLIENT_ID_T MN_GetRealClientId(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulPid
)
{
    MODEM_ID_ENUM_UINT16                enModemId;

    /* 根据Pid的值获取ModemId */
    enModemId = VOS_GetModemIDFromPid(ulPid);

    if (enModemId >= MODEM_ID_BUTT)
    {
        return usClientId;
    }

    /* 根据ModemId获取ClientId */
    if (MODEM_ID_0 == enModemId)
    {
        return (usClientId & AT_BROADCAST_CLIENT_ID_MODEM_0);
    }
    else if (MODEM_ID_1 == enModemId)
    {
        return (usClientId & AT_BROADCAST_CLIENT_ID_MODEM_1);
    }
    else
    {
        return (usClientId & AT_BROADCAST_CLIENT_ID_MODEM_2);
    }
}


VOS_BOOL  MN_IsUsimPresent(VOS_VOID)
{
    return f_bMnUsimPresent;
}


VOS_VOID  MN_SetUsimPresent(VOS_BOOL bPresent)
{
    f_bMnUsimPresent = bPresent;
}


VOS_VOID  MN_SendClientResponse(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulErrorCode
)
{
    MN_INFO_LOG1("MN_SendClientResponse, ErrorCode", (VOS_INT32)ulErrorCode);

    /* 调用本地操作上报函数 */
    MN_CMDCNF_SendMsg(clientId, opId, ulErrorCode);

}


VOS_VOID  MN_SendClientEvent(
    MN_CLIENT_ID_T                      usClientId,
    MN_CALLBACK_TYPE_T                  ucCallbackType,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pEventContent
)
{

    switch (ucCallbackType)
    {
        case MN_CALLBACK_MSG:
            /*短信业务事件上报处理*/
            MN_MSG_SendMsg(usClientId, ulEventType, (MN_MSG_EVENT_INFO_STRU *)pEventContent);
            break;

        case MN_CALLBACK_CS_CALL:
            /*CS业务事件上报处理*/
            MN_CS_SendMsg(usClientId, ulEventType, (MN_CALL_INFO_STRU *)pEventContent);
            break;

        case MN_CALLBACK_SS:
            /*SS业务事件上报处理*/
            MN_SS_SendMsg(usClientId, ulEventType, (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)pEventContent);
            break;

        case MN_CALLBACK_VOICE_CONTROL:

            /*voice control事件上报处理*/
            MN_VC_SendMsg(usClientId, ulEventType, (APP_VC_EVENT_INFO_STRU *)pEventContent);
            break;

        default:
            break;

    }

}


VOS_VOID MN_SetBitMap(
    VOS_UINT32                          *pulBitMap,
    VOS_UINT32                          ulIndex,
    VOS_BOOL                            bReset
)
{
    VOS_UINT8                            ucX;
    VOS_UINT32                           ulY;

    ulY = ulIndex/32;
    ucX = (VOS_UINT8)(ulIndex%32);
    if (VOS_FALSE == bReset)
    {
        pulBitMap[ulY] |= ((VOS_UINT32)1 << ucX);
    }
    else
    {
        pulBitMap[ulY] ^= ((VOS_UINT32)1 << ucX);
    }
    return;
}


VOS_UINT32 MN_GetBitMap(
    VOS_UINT32                          *pulBitMap,
    VOS_UINT32                          ulIndex
)
{
    VOS_UINT8                           ucX;
    VOS_UINT32                          ulY;
    VOS_UINT32                          ulMask;

    ulY = ulIndex/32;
    ucX = (VOS_UINT8)ulIndex%32;
    ulMask = ((VOS_UINT32)1 << ucX);
    if (0 != (pulBitMap[ulY] & ulMask))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}



VOS_VOID MN_CmpAsciiStrAndUcs2StrCaseInsensitive(
    VOS_UINT8                           *pucUcs2Str,
    VOS_UINT32                          ulUcs2Strlen,
    VOS_UINT8                           *pucAsciiStr,
    VOS_BOOL                            *pbEqualFlag
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulAsciiStrLen;
    VOS_UINT32                          ulPos;

    *pbEqualFlag    = VOS_FALSE;
    ulAsciiStrLen   = VOS_StrLen((VOS_CHAR *)pucAsciiStr);

    /*必须大于或等于ASCII码字符串长度的2倍才可能是同一字符串的两种编码格式;*/
    if (ulUcs2Strlen < (ulAsciiStrLen * 2))
    {
        return;
    }

    for (ulLoop = 0; ulLoop < ulAsciiStrLen; ulLoop++)
    {
        /*获取UCS2字符的高位数值与0比较: 不为0则不可能与ASCII编码字符相等*/
        ulPos = (2 * ulLoop);
        if (0 != pucUcs2Str[ulPos])
        {
            return;
        }

        /*获取UCS2字符的低位数值与ASCII字符串比较对应字符比较*/
        ulPos += 1;
        if (VOS_CharToLower((VOS_CHAR)pucAsciiStr[ulLoop])
         != VOS_CharToLower((VOS_CHAR)pucUcs2Str[ulPos]))
        {
            return;
        }
    }

    *pbEqualFlag = VOS_TRUE;

    return;

}


VOS_UINT32 MN_DeciDigit2Ascii(
    VOS_UINT8                           aucDeciDigit[],
    VOS_UINT32                          ulLength,
    VOS_UINT8                           aucAscii[]
)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < ulLength; ulLoop++)
    {
        if (aucDeciDigit[ulLoop] > 9)
        {
            return VOS_ERR;
        }

        aucAscii[ulLoop] = aucDeciDigit[ulLoop] + '0';
    }

    return VOS_OK;
}


VOS_VOID MN_MNTN_RecordSmsMoFailure(TAF_MSG_ERROR_ENUM_UINT32 enErrorCode)
{
    VOS_UINT32                          ulRet;
    NAS_MNTN_SMS_MO_FAIL_EVENT_STRU     stSmsMoFailEvent;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enAvailableSendDomain;

    if (g_stMnMntnErrorLogMsg.ucMoFailureCounter >= NAS_MNTN_ERRORLOG_SMS_MO_FAILURE_MAX)
    {
        MN_NORM_LOG("MN_MNTN_RecordSmsMoFailure: counter reach NAS_MNTN_ERRORLOG_SMS_MO_FAILURE_MAX.");
        return;
    }

    /* 填写短信发送失败事件信息 */
    PS_MEM_SET(&stSmsMoFailEvent, 0x00, sizeof(stSmsMoFailEvent));

    NAS_MMA_OutputUsimInfo(&stSmsMoFailEvent.stUsimInfo);

    NAS_MNTN_OutputPositionInfo(&stSmsMoFailEvent.stPositionInfo);

    MN_MSG_OutputSmsMoFailureInfo(enErrorCode, &stSmsMoFailEvent.stMoFail);

    MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_PS, &enAvailableSendDomain);
    if (MN_MSG_SEND_DOMAIN_PS == enAvailableSendDomain)
    {
        stSmsMoFailEvent.enPsStatus = NAS_MNTN_SEND_DOMAIN_STATUS_AVAILABLE;
    }
    else
    {
        stSmsMoFailEvent.enPsStatus = NAS_MNTN_SEND_DOMAIN_STATUS_UNAVAILABLE;
    }

    MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_CS, &enAvailableSendDomain);
    if (MN_MSG_SEND_DOMAIN_CS == enAvailableSendDomain)
    {
        stSmsMoFailEvent.enCsStatus = NAS_MNTN_SEND_DOMAIN_STATUS_AVAILABLE;
    }
    else
    {
        stSmsMoFailEvent.enCsStatus = NAS_MNTN_SEND_DOMAIN_STATUS_UNAVAILABLE;
    }

    /* 输出短信发送失败事件信息 */
    ulRet = MNTN_RecordErrorLog(NAS_EVT_TYPE_DEF(WUEPS_PID_TAF,MNTN_NAS_ERRORLOG_SMS_MO_FAILURE),
                        &stSmsMoFailEvent,
                        sizeof(stSmsMoFailEvent));
    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_MNTN_RecordSmsMoFailure: MNTN_RecordErrorLog fail.");
        return;
    }

    /* 事件计数器累加 */
    g_stMnMntnErrorLogMsg.ucMoFailureCounter++;

    return;
}

VOS_UINT32 MN_GetFileSize(
    FILE                                *fp,
    VOS_UINT32                          *pulFileSize
)
{
    /*定位到文件尾部*/
    if((-1) == mdrv_file_seek(fp, 0, SEEK_END))
    {
        MN_WARN_LOG("MN_MSG_GetFileSize:LSEEK error\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_SEEK_FILE;
    }

    /*读取文件大小*/
    *pulFileSize = (VOS_UINT32)mdrv_file_tell(fp);
    if((-1) == ((VOS_INT32)*pulFileSize ))
    {
        MN_WARN_LOG("MN_MSG_GetFileSize:ftell error\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_TELL_FILE;
    }

    return MN_ERR_NO_ERROR;
}


VOS_VOID MN_MNTN_RecordSmsMeError (
    MNTN_ME_OPERATION_ENUM_UINT32       enOperation,
    VOS_UINT32                          ulErrorNo
)
{
    NAS_MNTN_SMS_ME_ERROR_EVENT_STRU    stMeError;
    VOS_UINT32                          ulRet;
/*
    If ME文件操作失败事件记录次数达上限NAS_MNTN_ERRORLOG_ME_FILE_ERROR_MAX
       打印告警并返回；
    调用函数MNTN_RecordErrorLog记录MNTN_NAS_ERRORLOG_ME_FILE_ERROR事件
    If 函数返回失败
        打印告警并返回；
    事件计数器累加
*/
    if (g_stMnMntnErrorLogMsg.ucMeFileErrorCounter >= NAS_MNTN_ERRORLOG_ME_FILE_ERROR_MAX)
    {
        MN_NORM_LOG("MN_MNTN_RecordSmsMeError: counter reach NAS_MNTN_ERRORLOG_ME_FILE_ERROR_MAX.");
        return;
    }

    stMeError.enOperation = enOperation;
    stMeError.ulErrorNo   = ulErrorNo;

    /* 输出短信发送失败事件信息 */
    ulRet = MNTN_RecordErrorLog(NAS_EVT_TYPE_DEF(WUEPS_PID_TAF,MNTN_NAS_ERRORLOG_SMS_ME_ERROR),
                                &stMeError,
                                sizeof(stMeError));
    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_MNTN_RecordSmsMeError: MNTN_RecordErrorLog fail.");
        return;
    }

    /* 事件计数器累加 */
    g_stMnMntnErrorLogMsg.ucMeFileErrorCounter++;

    return;

}


VOS_VOID  MN_SendReportMsg(TAF_UINT8 ucType,TAF_UINT8* pData,TAF_UINT16 usLen)
{
    MN_AT_IND_EVT_STRU                  *pstEvent;
    TAF_UINT32                          ulTmpAddr;

    /* 增加自定义的ITEM，共4个字节 */
    pstEvent = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, (usLen + MN_AT_INTERFACE_MSG_HEADER_LEN));
    if (TAF_NULL_PTR == pstEvent)
    {
        MN_ERR_LOG("MN_SendReportMsg:ERROR:Alloc Msg");
        return;
    }

    pstEvent->ulReceiverPid     = WUEPS_PID_AT;
    pstEvent->usMsgName         = ucType;
    pstEvent->usLen             = usLen;

    ulTmpAddr = (TAF_UINT32)pstEvent->aucContent;
    PS_MEM_CPY((TAF_VOID *)ulTmpAddr, pData, usLen);

    /*发送消息到AT_PID;*/
    if ( 0 != PS_SEND_MSG( WUEPS_PID_TAF, pstEvent ) )
    {
        MN_ERR_LOG("MN_SendReportMsg:ERROR");
        return;
    }

    return;
}



MN_CLIENT_ID_TYPE_UINT16 MN_GetClientIdType(MN_CLIENT_ID_T usClientId)
{
    /*AT的CLIENT*/
    if (usClientId < AT_CLIENT_ID_BUTT)
    {
        return MN_CLIENT_ID_TYPE_AT;
    }

    /*OAM的CLIENT*/

    if ((usClientId >= OAM_CLIENT_ID_OM)
      &&(usClientId < OMA_CLIENT_ID_BUTT))
    {
        return MN_CLIENT_ID_TYPE_OAM;
    }

    return MN_CLIENT_ID_TYPE_BUTT;
}


VOS_UINT32 MN_GetPidFromClientId(MN_CLIENT_ID_T usClientId)
{
    VOS_UINT32                          ulRcvPid;

    switch(usClientId)
    {


        case OAM_CLIENT_ID_SPY:
            ulRcvPid = WUEPS_PID_SPY;
            break;



        case OAM_CLIENT_ID_STK:
            ulRcvPid = MAPS_STK_PID;
            break;

        case OAM_CLIENT_ID_PIH:
            ulRcvPid = MAPS_PIH_PID;
            break;

        case OAM_CLIENT_ID_PB:
            ulRcvPid = MAPS_PB_PID;
            break;

        case OAM_CLIENT_ID_CBT:
            ulRcvPid = CCPU_PID_CBT;
            break;

        default:
            ulRcvPid = VOS_PID_BUTT;
            break;
    }

    return ulRcvPid;
}


VOS_VOID MN_CS_SendMsgToAt(
    MN_CLIENT_ID_T                      clientId,
    MN_CALL_EVENT_ENUM_U32              enEventType,
    MN_CALL_INFO_STRU                  *pstEvent
)
{
    MN_AT_IND_EVT_STRU                 *pMsg;
    TAF_UINT16                          usLength;
    TAF_UINT32                          ulEventTypeLen;
    TAF_UINT32                          ulTmpAddr;

    pMsg     = TAF_NULL_PTR;
    usLength = 0;

    if(TAF_NULL_PTR == pstEvent)
    {
        MN_WARN_LOG("MN_CS_SendMsgToAt pEvent NULL");
        return;
    }

   ulEventTypeLen  = sizeof(enEventType);
   usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_CALL_INFO_STRU)) + ulEventTypeLen);

    /* 从第二个字节开始 */
    pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,usLength);
    if (TAF_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CS_SendMsgToAt:ERROR:Alloc Msg");
        return;
    }

    /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = WUEPS_PID_TAF;
    pMsg->ulReceiverPid   = WUEPS_PID_AT;

    pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_CS_CALL;
    pMsg->usLen     = (VOS_UINT16)(sizeof(MN_CALL_INFO_STRU) + ulEventTypeLen);     /* 类型 */
    pMsg->clientId  = MN_GetRealClientId(clientId, WUEPS_PID_TAF);

    pstEvent->clientId = MN_GetRealClientId(pstEvent->clientId, WUEPS_PID_TAF);

    /* 填写新消息内容 */
    ulEventTypeLen  = sizeof(enEventType);
    ulTmpAddr = (TAF_UINT32)pMsg->aucContent;
    PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
    PS_MEM_CPY((VOS_VOID*)(ulTmpAddr + ulEventTypeLen),
               pstEvent,
               sizeof(MN_CALL_INFO_STRU));

    /*发送消息到AT_PID;*/
    if ( 0 != PS_SEND_MSG( WUEPS_PID_TAF, pMsg ) )
    {
        MN_ERR_LOG("MN_CS_SendMsgToAt:ERROR");
        return;
    }
}


VOS_VOID MN_CS_SendMsgToOam(
    MN_CLIENT_ID_T                      clientId,
    MN_CALL_EVENT_ENUM_U32              enEventType,
    VOS_UINT32                          ulOamRcvPid,
    MN_CALL_INFO_STRU                  *pstEvent
)
{
    MN_APP_CS_CALLINFO_MSG_STRU        *pstMsg;
    VOS_UINT32                          ulLength;

    if(VOS_NULL_PTR == pstEvent)
    {
        MN_WARN_LOG("MN_CS_SendMsgToOam: pEvent NULL");
        return;
    }

    /* 为回复OAM的消息TAF_STK_CS_CALLINFO_EVENT_IND申请内存 */
    ulLength = sizeof(MN_APP_CS_CALLINFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (MN_APP_CS_CALLINFO_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("MN_CS_SendMsgToOam: Alloc Msg");
        return;
    }

    /* 填写新消息内容 */
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;

    pstMsg->ulReceiverPid   = NAS_GetOamReceivePid(ulOamRcvPid);

    pstMsg->ulMsgId         = TAF_STK_CS_CALLINFO_EVENT_IND;
    pstMsg->enEventType     = enEventType;

    PS_MEM_CPY(&(pstMsg->stCsCallInfo), pstEvent, sizeof(MN_CALL_INFO_STRU));

    /* 发送消息到OAM; */
    if (0 != PS_SEND_MSG( WUEPS_PID_TAF, pstMsg))
    {
        MN_ERR_LOG("MN_CS_SendMsgToOam: PS_SEND_MSG ERROR");
        return;
    }
}


VOS_VOID MN_CS_SendMsg(
    MN_CLIENT_ID_T                      usClientId,
    MN_CALL_EVENT_ENUM_U32              enEventType,
    MN_CALL_INFO_STRU                  *pstEvent
)
{
    MN_CLIENT_ID_TYPE_UINT16            enClientIdType;
    VOS_UINT32                          ulOamRcvPid;

    enClientIdType  = MN_GetClientIdType(usClientId);

    /*广播CLIENT ID的处理*/
    if (MN_CLIENT_ID_BROADCAST ==  usClientId)
    {
        /*发给STK*/
        MN_CS_SendMsgToOam(usClientId, enEventType, MAPS_STK_PID, pstEvent);


        /* 需要主动上报时发给AT */
        /*if (VOS_TRUE == TAF_CALL_IsEventNeedRpt(enEventType))*/
        MN_CS_SendMsgToAt(usClientId, enEventType, pstEvent);



        MN_CS_ProcEmergencyCallEvent(enEventType, pstEvent);
        return;
    }

    /*AT CLIENT*/
    if (MN_CLIENT_ID_TYPE_AT == enClientIdType)
    {
        MN_CS_SendMsgToAt(usClientId, enEventType, pstEvent);
    }
    else
    {
        /*通过client id获取对应的pid*/
        ulOamRcvPid = MN_GetPidFromClientId(usClientId);

        if (VOS_PID_BUTT == ulOamRcvPid)
        {
            MN_ERR_LOG("MN_CS_SendMsg: no pid!");
            return;
        }
        /*调用对应的消息发送函数*/
        MN_CS_SendMsgToOam(usClientId, enEventType, ulOamRcvPid, pstEvent);
    }

    return;
}



VOS_VOID MN_MSG_SendMsgToOam(
    MN_CLIENT_ID_T                      clientId,
    MN_MSG_EVENT_ENUM_U32               enEventType,
    VOS_UINT32                          ulOamRcvPid,
    MN_MSG_EVENT_INFO_STRU             *pstEvent
)
{
    MN_APP_MSG_EVENT_IND_STRU          *pstMsg;
    VOS_UINT32                          ulLength;

    if(VOS_NULL_PTR == pstEvent)
    {
        MN_WARN_LOG("MN_MSG_SendMsgToOam: pstEvent NULL");
        return;
    }

    ulLength = sizeof(MN_APP_MSG_EVENT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (MN_APP_MSG_EVENT_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("MN_MSG_SendMsgToOam: Alloc Msg");
        return;
    }

    /* 填写新消息内容 */
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;

    pstMsg->ulReceiverPid   = NAS_GetOamReceivePid(ulOamRcvPid);

    pstMsg->ulMsgId         = TAF_STK_MSG_EVENT_IND;
    pstMsg->enEventType     = enEventType;

    PS_MEM_CPY(&(pstMsg->stEvent), pstEvent, sizeof(pstMsg->stEvent));

    /*发送消息到OAM的指定PID ;*/
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstMsg ) )
    {
        MN_ERR_LOG("MN_MSG_SendMsgToOam: PS_SEND_MSG fail.");
        return;
    }
}


VOS_VOID MN_MSG_SendMsgToAt(
    MN_CLIENT_ID_T                      clientId,
    MN_MSG_EVENT_ENUM_U32               enEventType,
    MN_MSG_EVENT_INFO_STRU             *pstEvent
)
{
    MN_AT_IND_EVT_STRU                  *pMsg               = TAF_NULL_PTR;
    TAF_UINT16                          usLength            = 0;
    TAF_UINT32                          ulEventTypeLen;

    if(TAF_NULL_PTR == pstEvent)
    {
        MN_WARN_LOG("MN_MSG_SendMsgToAt: pEvent NULL");
        return;
    }

    ulEventTypeLen  = sizeof(enEventType);
    usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_MSG_EVENT_INFO_STRU)) + ulEventTypeLen);

    /* 从第二个字节开始 */
    pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, usLength);
    if (TAF_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_MSG_SendMsgToAt:ERROR:Alloc Msg");
        return;
    }

    /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = WUEPS_PID_TAF;
    pMsg->ulReceiverPid   = WUEPS_PID_AT;

    pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_MSG;
    pMsg->aucReserved1[0] = 0;
    pMsg->aucReserved1[1] = 0;
    pMsg->clientId  = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    pMsg->usLen     = (VOS_UINT16)(sizeof(MN_MSG_EVENT_INFO_STRU) + ulEventTypeLen);     /* 类型 */

    pstEvent->clientId = MN_GetRealClientId(pstEvent->clientId, WUEPS_PID_TAF);

    /* 填写新消息内容 */
    PS_MEM_CPY(pMsg->aucContent, &enEventType, ulEventTypeLen);
    PS_MEM_CPY((MN_MSG_EVENT_INFO_STRU *)&(pMsg->aucContent[ulEventTypeLen]),
               pstEvent,
               sizeof(MN_MSG_EVENT_INFO_STRU));

    /*发送消息到AT_PID;*/
    if ( 0 != PS_SEND_MSG( WUEPS_PID_TAF, pMsg ) )
    {
        MN_ERR_LOG("MN_MSG_SendMsgToAt:ERROR");
        return;
    }
}


VOS_VOID MN_MSG_SendMsg(
    MN_CLIENT_ID_T                      usClientId,
    MN_MSG_EVENT_ENUM_U32               enEventType,
    MN_MSG_EVENT_INFO_STRU             *pstEvent
)
{
    MN_CLIENT_ID_TYPE_UINT16            enClientIdType;
    VOS_UINT32                          ulOamRcvPid;

    enClientIdType = MN_GetClientIdType(usClientId);

    /*广播CLIENT ID的处理*/
    if (MN_CLIENT_ID_BROADCAST ==  usClientId)
    {
        /*只需要发给AT*/
        if (VOS_TRUE == TAF_MSG_IsEventNeedRpt(enEventType))
        {
            MN_MSG_SendMsgToAt(usClientId, enEventType, pstEvent);
        }

        return;
    }

    /*AT CLIENT*/
    if (MN_CLIENT_ID_TYPE_AT == enClientIdType)
    {

        /*只需要发给AT*/
        if (VOS_TRUE == TAF_MSG_IsEventNeedRpt(enEventType))
        {
            MN_MSG_SendMsgToAt(usClientId, enEventType, pstEvent);
        }
    }
    else
    {
        /*通过client id获取对应的pid*/
        ulOamRcvPid = MN_GetPidFromClientId(usClientId);

        if (VOS_PID_BUTT == ulOamRcvPid)
        {
            MN_ERR_LOG("MN_MSG_SendMsg: no pid!");
            return;
        }

        /*调用对应的消息发送函数*/
        MN_MSG_SendMsgToOam(usClientId, enEventType, ulOamRcvPid, pstEvent);
    }

    return;
}


VOS_VOID MN_SS_SendMsgToOam(
    MN_CLIENT_ID_T                      clientId,
    VOS_UINT32                          ulEventType,
    VOS_UINT32                          ulOamRcvPid,
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent
)
{
    MN_APP_SS_EVENT_IND_STRU           *pstMsg;
    VOS_UINT32                          ulLength;

    if(VOS_NULL_PTR == pstEvent)
    {
        MN_WARN_LOG("MN_SS_SendMsgToOam: pstEvent NULL");
        return;
    }

    ulLength = sizeof(MN_APP_SS_EVENT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (MN_APP_SS_EVENT_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("MN_SS_SendMsgToOam: Alloc Msg");
        return;
    }

    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;

    pstMsg->ulReceiverPid   = NAS_GetOamReceivePid(ulOamRcvPid);

    pstMsg->ulMsgId         = TAF_STK_SS_EVENT_IND;
    pstMsg->ulEventType     = ulEventType;

    /* 填写新消息内容 */
    PS_MEM_CPY(&(pstMsg->stSsEvent), pstEvent, sizeof(pstMsg->stSsEvent));

    /*发送消息到OAM的指定PID ;*/
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstMsg ) )
    {
        MN_ERR_LOG("MN_SS_SendMsgToOam: PS_SEND_MSG fail.");
        return;
    }

    return;
}


VOS_VOID MN_SS_SendMsgToAt(
    MN_CLIENT_ID_T                      clientId,
    VOS_UINT32                          ulEventType,
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent
)
{
    if(TAF_NULL_PTR == pstEvent)
    {
        MN_WARN_LOG("MN_MSG_SendMsgToAt pEvent NULL");
        return;
    }

    pstEvent->ClientId = MN_GetRealClientId(pstEvent->ClientId, WUEPS_PID_TAF);

    MN_SendReportMsg(MN_CALLBACK_SS,(TAF_UINT8*)pstEvent,sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
}


VOS_VOID MN_SS_SendMsg(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulEventType,
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstEvent
)
{
    MN_CLIENT_ID_TYPE_UINT16            enClientIdType;
    VOS_UINT32                          ulOamRcvPid;

    enClientIdType = MN_GetClientIdType(usClientId);

    /*广播CLIENT ID的处理*/
    if (MN_CLIENT_ID_BROADCAST ==  usClientId)
    {
        /*发给STK*/
        MN_SS_SendMsgToOam(usClientId, ulEventType, MAPS_STK_PID, pstEvent);

        /*只需要发给AT*/
        if (VOS_TRUE == TAF_SS_IsEventNeedRpt((TAF_SS_EVENT)ulEventType))
        {
            MN_SS_SendMsgToAt(usClientId, ulEventType, pstEvent);
        }

        return;
    }

    /*AT CLIENT*/
    if (MN_CLIENT_ID_TYPE_AT == enClientIdType)
    {
        if (VOS_TRUE == TAF_SS_IsEventNeedRpt((TAF_SS_EVENT)ulEventType))
        {
            MN_SS_SendMsgToAt(usClientId, ulEventType, pstEvent);
        }
    }
    else
    {
        /*通过client id获取对应的pid*/
        ulOamRcvPid = MN_GetPidFromClientId(usClientId);

        if (VOS_PID_BUTT == ulOamRcvPid)
        {
            MN_ERR_LOG("MN_SS_SendMsg: no pid!");
            return;
        }

        /*调用对应的消息发送函数*/
        MN_SS_SendMsgToOam(usClientId, ulEventType, ulOamRcvPid, pstEvent);

    }

    return;
}


VOS_VOID MN_CMDCNF_SendMsgToOam(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulOamRcvPid,
    VOS_UINT32                          ulErrorCode
)
{
    MN_APP_CMD_CNF_STRU                *pstMsg;
    VOS_UINT32                          ulLength;

    ulLength = sizeof(MN_APP_CMD_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (MN_APP_CMD_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("MN_CMDCNF_SendMsgToOam: Alloc Msg");
        return;
    }

    /* 填写新消息内容 */
    pstMsg->ulSenderPid               = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId           = VOS_LOCAL_CPUID;

    pstMsg->ulReceiverPid             = NAS_GetOamReceivePid(ulOamRcvPid);

    pstMsg->ulMsgId                   = TAF_STK_CMD_CNF;
    pstMsg->stCmdCnfEvent.clientId    = clientId;
    pstMsg->stCmdCnfEvent.opId        = opId;
    pstMsg->stCmdCnfEvent.ucRsv       = 0;
    pstMsg->stCmdCnfEvent.ulErrorCode = ulErrorCode;

    /*发送消息到OAM的指定PID ;*/
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstMsg ) )
    {
        MN_ERR_LOG("MN_CMDCNF_SendMsgToOam: PS_SEND_MSG fail.");
        return;
    }

    return;
}


VOS_VOID MN_CMDCNF_SendMsgToAt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_UINT32                          ulErrorCode
)
{
    AT_CMD_CNF_EVENT        CmdCnfEvent;

    CmdCnfEvent.clientId    = MN_GetRealClientId(clientId, WUEPS_PID_TAF);;
    CmdCnfEvent.opId        = opId;
    CmdCnfEvent.ulErrorCode = ulErrorCode;

    MN_SendReportMsg(MN_CALLBACK_CMD_CNF, (TAF_UINT8*)&CmdCnfEvent, sizeof(AT_CMD_CNF_EVENT));

    return;
}


VOS_VOID MN_CMDCNF_SendMsg(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_UINT32                          ulErrorCode
)
{
    MN_CLIENT_ID_TYPE_UINT16            enClientIdType;
    VOS_UINT32                          ulOamRcvPid;

    enClientIdType = MN_GetClientIdType(usClientId);

    /*广播CLIENT ID的处理*/
    if (MN_CLIENT_ID_BROADCAST ==  usClientId)
    {
        /*只需要发给AT*/
        MN_CMDCNF_SendMsgToAt(usClientId, ucOpId, ulErrorCode);

        return;
    }

    /*AT CLIENT*/
    if (MN_CLIENT_ID_TYPE_AT == enClientIdType)
    {
        MN_CMDCNF_SendMsgToAt(usClientId, ucOpId, ulErrorCode);
    }
    else
    {
        /*通过client id获取对应的pid*/
        ulOamRcvPid = MN_GetPidFromClientId(usClientId);

        if (VOS_PID_BUTT == ulOamRcvPid)
        {
            MN_ERR_LOG("MN_CMDCNF_SendMsg: no pid!");
            return;
        }

        /*调用对应的消息发送函数*/
        MN_CMDCNF_SendMsgToOam(usClientId, ucOpId, ulOamRcvPid, ulErrorCode);
    }

    return;
}


VOS_VOID MN_PH_SendMsgToOam(
    VOS_UINT32                          ulOamRcvPid,
    TAF_PHONE_EVENT_INFO_STRU          *pstEvent
)
{
    MN_APP_PHONE_EVENT_INFO_STRU       *pstMsg;
    VOS_UINT32                          ulLength;

    if(VOS_NULL_PTR == pstEvent)
    {
        MN_WARN_LOG("MN_PH_SendMsgToOam: pstEvent NULL");
        return;
    }

    /* 为回复OAM的消息TAF_STK_CS_CALLINFO_EVENT_IND申请内存 */
    ulLength = sizeof(MN_APP_PHONE_EVENT_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (MN_APP_PHONE_EVENT_INFO_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("MN_CS_SendMsgToOam: Alloc Msg");
        return;
    }

    /* 填写新消息内容 */
    pstMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulOamRcvPid;

    pstMsg->ulMsgId         = TAF_OAM_PHONE_EVENT_IND;
    PS_MEM_CPY(&(pstMsg->stPhoneEvent), pstEvent, sizeof(pstMsg->stPhoneEvent));

    /* 发送消息到OAM; */
    if (0 != PS_SEND_MSG( WUEPS_PID_MMA, pstMsg))
    {
        MN_ERR_LOG("MN_PH_SendMsgToOam: PS_SEND_MSG ERROR");
        return;
    }
}


VOS_VOID MN_PH_SendMsgToAt(VOS_UINT8  *pEvent,VOS_UINT32 ulLen)
{
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU*)pEvent;

    if(TAF_NULL_PTR == pEvent)
    {
        MN_WARN_LOG("MN_PH_SendMsgToAt pEvent NULL");
        return;
    }

    pstPhoneEvent->ClientId = MN_GetRealClientId(pstPhoneEvent->ClientId, WUEPS_PID_TAF);

    MN_SendReportMsg(MN_CALLBACK_PHONE,(TAF_UINT8*)pEvent,(VOS_UINT16)ulLen);
}


VOS_VOID MN_PH_SendMsg(MN_CLIENT_ID_T usClientId,VOS_UINT8 *pEvent,VOS_UINT32 ulLen)
{
    MN_CLIENT_ID_TYPE_UINT16            enClientIdType;
    VOS_UINT32                          ulOamRcvPid;
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU*)pEvent;
    enClientIdType = MN_GetClientIdType(usClientId);

    /*广播CLIENT ID的处理*/
    if (MN_CLIENT_ID_BROADCAST ==  usClientId)
    {
        /*只需要发给AT*/
        if (VOS_TRUE == TAF_MMA_IsEventNeedRpt(pstPhoneEvent))
        {
            MN_PH_SendMsgToAt(pEvent,ulLen);
        }

        return;
    }

    /*AT CLIENT*/
    if (MN_CLIENT_ID_TYPE_AT == enClientIdType)
    {
        MN_PH_SendMsgToAt(pEvent,ulLen);
    }
    else
    {
        /*通过client id获取对应的pid*/
        ulOamRcvPid = MN_GetPidFromClientId(usClientId);

        if (VOS_PID_BUTT == ulOamRcvPid)
        {
            MN_ERR_LOG("MN_PH_SendMsg: no pid!");
            return;
        }

        /*调用对应的消息发送函数*/
        /*只对电话事件消息需要发送给OAM，列表搜结果不需要发送给列表搜.*/
        if ( ulLen == sizeof(TAF_PHONE_EVENT_INFO_STRU))
        {
            MN_PH_SendMsgToOam(ulOamRcvPid, pstPhoneEvent);
        }

    }

    return;
}

/*lint -e438 -e830*/


VOS_VOID MN_DATASTATUS_SendMsgToAt(
    TAF_UINT16                          ClientId,
    TAF_UINT8                           ucDomain,
    TAF_UINT8                           ucRabId,
    TAF_UINT8                           ucStatus,
    TAF_UINT8                           ucCause
)
{
    TAF_UINT16 usAddr = 0;
    TAF_UINT16 usLength = 0;
    TAF_UINT8 ucType = MN_CALLBACK_DATA_STATUS;
    TAF_UINT8  aucTmp[255];
    MN_CLIENT_ID_T                      ulRealClientId;

    ulRealClientId = MN_GetRealClientId(ClientId, WUEPS_PID_TAF);

    usLength = sizeof(ulRealClientId)+sizeof(ucDomain)+sizeof(ucRabId)+sizeof(ucStatus)+sizeof(ucCause);

    PS_MEM_CPY(aucTmp+usAddr,&ulRealClientId,sizeof(ulRealClientId));
    usAddr += sizeof(ulRealClientId);

    PS_MEM_CPY(aucTmp+usAddr,&ucDomain,sizeof(ucDomain));
    usAddr += sizeof(ucDomain);

    PS_MEM_CPY(aucTmp+usAddr,&ucRabId,sizeof(ucRabId));
    usAddr += sizeof(ucRabId);

    PS_MEM_CPY(aucTmp+usAddr,&ucStatus,sizeof(ucStatus));
    usAddr += sizeof(ucStatus);

    PS_MEM_CPY(aucTmp+usAddr,&ucCause,sizeof(ucCause));
    usAddr += sizeof(ucCause);

    MN_SendReportMsg(ucType,aucTmp,usLength);

}
/*lint +e438 +e830*/


VOS_VOID MN_DATASTATUS_SendMsg(
    TAF_UINT16                          usClientId,
    TAF_UINT8                           ucDomain,
    TAF_UINT8                           ucRabId,
    TAF_UINT8                           ucStatus,
    TAF_UINT8                           ucCause
)
{
    MN_CLIENT_ID_TYPE_UINT16            enClientIdType;
    VOS_UINT32                          ulOamRcvPid;

    enClientIdType = MN_GetClientIdType(usClientId);

    /*广播CLIENT ID的处理*/
    if (MN_CLIENT_ID_BROADCAST ==  usClientId)
    {
        /*只需要发给AT*/
        MN_DATASTATUS_SendMsgToAt(usClientId, ucDomain, ucRabId, ucStatus, ucCause);

        return;
    }

    /*AT CLIENT*/
    if (MN_CLIENT_ID_TYPE_AT == enClientIdType)
    {
        MN_DATASTATUS_SendMsgToAt(usClientId, ucDomain, ucRabId, ucStatus, ucCause);
    }
    else
    {
        /*通过client id获取对应的pid*/
        ulOamRcvPid = MN_GetPidFromClientId(usClientId);

        if (VOS_PID_BUTT == ulOamRcvPid)
        {
            MN_ERR_LOG("MN_DATASTATUS_SendMsg: no pid!");
            return;
        }

        /*调用对应的消息发送函数: 目前没有OAM的接口消息，不处理 */

    }

    return;
}


VOS_VOID MN_SETPARA_SendMsgToOam(
    TAF_UINT16                          ClientId,
    TAF_UINT8                           OpId,
    VOS_UINT32                          ulOamRcvPid,
    TAF_PARA_SET_RESULT                 Result,
    TAF_PARA_TYPE                       ucParaType
)
{
    MN_APP_PHONE_SET_CNF_STRU          *pstMsg;
    VOS_UINT32                          ulLength;

    /* 为回复OAM的消息TAF_STK_CS_CALLINFO_EVENT_IND申请内存 */
    ulLength = sizeof(MN_APP_PHONE_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (MN_APP_PHONE_SET_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("MN_SETPARA_SendMsgToOam: Alloc Msg");
        return;
    }

    /* 填写新消息内容 */
    pstMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulOamRcvPid;

    pstMsg->ulMsgId         = TAF_OAM_PHONE_SET_CNF;
    pstMsg->ucParaType      = ucParaType;
    pstMsg->ucResult        = Result;
    PS_MEM_SET(pstMsg->aucReserved, 0x00, sizeof(pstMsg->aucReserved));

    /* 发送消息到OAM; */
    if (0 != PS_SEND_MSG( WUEPS_PID_TAF, pstMsg))
    {
        MN_ERR_LOG("MN_SETPARA_SendMsgToOam: PS_SEND_MSG ERROR");
        return;
    }
}

/*lint -e438 -e830*/


VOS_VOID MN_SETPARA_SendMsgToAt(
    TAF_UINT16                          ClientId,
    TAF_UINT8                           OpId,
    TAF_PARA_SET_RESULT                 Result,
    TAF_PARA_TYPE                       ParaType,
    TAF_VOID                           *pPara
)
{
    TAF_UINT16 usAddr = 0;
    TAF_UINT16 usLength = 0;
    TAF_UINT8 ucType = MN_CALLBACK_SET;
    TAF_UINT8 *pParaBuf = TAF_NULL_PTR;
    MN_CLIENT_ID_T                      ulRealClientId;

    ulRealClientId = MN_GetRealClientId(ClientId, WUEPS_PID_TAF);

    /* 注意: 需要增加置放长度的两个字节 */
    usLength = sizeof(ulRealClientId) + sizeof(OpId) + sizeof(Result) + sizeof(ParaType);

    pParaBuf = (TAF_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_TAF,usLength);
    if (TAF_NULL_PTR == pParaBuf)
    {
        MN_WARN_LOG("MN_SETPARA_SendMsgToAt Malloc mem fail");
        return;
    }

    PS_MEM_CPY(pParaBuf+usAddr,&ulRealClientId,sizeof(ulRealClientId));
    usAddr += sizeof(ulRealClientId);

    PS_MEM_CPY(pParaBuf+usAddr,&OpId,sizeof(OpId));
    usAddr += sizeof(OpId);

    PS_MEM_CPY(pParaBuf+usAddr,&Result,sizeof(Result));
    usAddr += sizeof(Result);

    PS_MEM_CPY(pParaBuf+usAddr,&ParaType,sizeof(ParaType));
    usAddr += sizeof(ParaType);

    MN_SendReportMsg(ucType,pParaBuf,usLength);

    PS_MEM_FREE(WUEPS_PID_TAF,pParaBuf);
}
/*lint +e438 +e830*/


VOS_VOID MN_SETPARA_SendMsg(
    TAF_UINT16                          usClientId,
    TAF_UINT8                           ucOpId,
    TAF_PARA_SET_RESULT                 ucResult,
    TAF_PARA_TYPE                       ucParaType,
    TAF_VOID                           *pPara
)
{
    MN_CLIENT_ID_TYPE_UINT16            enClientIdType;
    VOS_UINT32                          ulOamRcvPid;

    enClientIdType = MN_GetClientIdType(usClientId);

    /*广播CLIENT ID的处理*/
    if (MN_CLIENT_ID_BROADCAST ==  usClientId)
    {
        /*只需要发给AT*/
        MN_SETPARA_SendMsgToAt(usClientId, ucOpId, ucResult, ucParaType, pPara);

        return;
    }

    /*AT CLIENT*/
    if (MN_CLIENT_ID_TYPE_AT == enClientIdType)
    {
        MN_SETPARA_SendMsgToAt(usClientId, ucOpId, ucResult, ucParaType, pPara);
    }
    else
    {
        /*通过client id获取对应的pid*/
        ulOamRcvPid = MN_GetPidFromClientId(usClientId);

        if (VOS_PID_BUTT == ulOamRcvPid)
        {
            MN_ERR_LOG("MN_SETPARA_SendMsg: no pid!");
            return;
        }

        /*调用对应的消息发送函数*/
        MN_SETPARA_SendMsgToOam(usClientId, ucOpId, ulOamRcvPid, ucResult, ucParaType);

    }

    return;
}


LOCAL VOS_UINT32 MN_GetQryMsgParaLen(
    TAF_PARA_TYPE                       QueryType,
    TAF_VOID                           *pPara,
    TAF_UINT16                         *pusParaLen
)
{
    TAF_UINT32                          ulLoop;
    TAF_UINT32                          ulQryMsgParaAttrNum;
    TAF_PH_USIM_PNN_CNF_STRU            stPnnPara;
    TAF_PH_USIM_OPL_CNF_STRU            stOplPara;
    MN_QRYMSGPARA_ATTR                  *pstParaAttr = TAF_NULL_PTR;

    PS_MEM_SET(&stPnnPara, 0, sizeof(TAF_PH_USIM_PNN_CNF_STRU));
    PS_MEM_SET(&stOplPara, 0, sizeof(TAF_PH_USIM_OPL_CNF_STRU));
    if (TAF_NULL_PTR == pPara)
    {
        *pusParaLen = 0;
        return VOS_OK;
    }

    ulQryMsgParaAttrNum = sizeof(f_astMnQryMsgParaAttr)/sizeof(f_astMnQryMsgParaAttr[0]);

    /*获取参数固定结构长度*/
    for (ulLoop = 0; ulLoop < ulQryMsgParaAttrNum; ulLoop++)
    {
        if (f_astMnQryMsgParaAttr[ulLoop].QueryType == QueryType)
        {
            pstParaAttr = &f_astMnQryMsgParaAttr[ulLoop];
            break;
        }
    }

    if (TAF_NULL_PTR == pstParaAttr)
    {
        return VOS_ERR;
    }
    *pusParaLen = (TAF_UINT16)pstParaAttr->ulFixedPartLen;

    if (TAF_PH_CPNN_PARA == QueryType)
    {
        return VOS_OK;
    }

    /*获取参数可变结构长度*/
    if (TAF_PH_PNN_PARA == QueryType)
    {
        PS_MEM_CPY(&stPnnPara, pPara, sizeof(TAF_PH_USIM_PNN_CNF_STRU));
        *pusParaLen += (TAF_UINT16)(stPnnPara.TotalRecordNum * sizeof(TAF_PH_USIM_PNN_RECORD));
        return VOS_OK;
    }

    if (TAF_PH_OPL_PARA == QueryType)
    {
        PS_MEM_CPY(&stOplPara,pPara,sizeof(TAF_PH_USIM_OPL_CNF_STRU));
        *pusParaLen += (TAF_UINT16)(stOplPara.TotalRecordNum * sizeof(TAF_PH_USIM_OPL_CNF_STRU));
        return VOS_OK;
    }

    return VOS_OK;
}


VOS_VOID MN_QRYPARA_SendMsgToAt  (
    TAF_UINT16                          usClientId,
    TAF_UINT8                           OpId,
    TAF_PARA_TYPE                       QueryType,
    TAF_UINT16                          usErrorCode,
    TAF_VOID                           *pPara
)
{
    TAF_UINT16 usAddr = 0;
    TAF_UINT16 usLength = 0;
    TAF_UINT16 usParaLen = 0;
    TAF_UINT8 ucType = MN_CALLBACK_QRY;
    TAF_UINT8 *pParaBuf = TAF_NULL_PTR;
    MN_CLIENT_ID_T                      ulRealClientId;

    if (VOS_OK != MN_GetQryMsgParaLen(QueryType, pPara, &usParaLen))
    {
        MN_WARN_LOG("At_QryParaCallBackFunc QueryType FAILURE");
        return;
    }

    ulRealClientId = MN_GetRealClientId(usClientId, WUEPS_PID_TAF);

    /* 注意: 需要增加置放长度的两个字节 */
    usLength = usParaLen + sizeof(ulRealClientId) + sizeof(OpId)
               + sizeof(QueryType) + sizeof(usErrorCode) + sizeof(usParaLen);
    pParaBuf = (TAF_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_TAF,usLength);
    if(TAF_NULL_PTR == pParaBuf)
    {
        MN_WARN_LOG("MN_QRYPARA_SendMsgToAt Mem alloc fail");
        return;
    }

    PS_MEM_CPY(pParaBuf+usAddr,&ulRealClientId,sizeof(ulRealClientId));
    usAddr += sizeof(ulRealClientId);

    PS_MEM_CPY(pParaBuf+usAddr,&OpId,sizeof(OpId));
    usAddr += sizeof(OpId);

    PS_MEM_CPY(pParaBuf+usAddr,&QueryType,sizeof(QueryType));
    usAddr += sizeof(QueryType);

    PS_MEM_CPY(pParaBuf+usAddr,&usErrorCode,sizeof(usErrorCode));
    usAddr += sizeof(usErrorCode);

    /* 注意: 是二级指针 usParaLen--pPara[ucCidNum.ptr[内容地址]]--[内容] */
    PS_MEM_CPY(pParaBuf+usAddr,&usParaLen,sizeof(usParaLen));
    /* usParaLen */
    usAddr += sizeof(usParaLen);
    /* pPara */
    if(TAF_NULL_PTR != pPara)
    {
        PS_MEM_CPY(pParaBuf+usAddr,pPara,usParaLen);
    }
    MN_SendReportMsg(ucType,pParaBuf,usLength);

    PS_MEM_FREE(WUEPS_PID_TAF,pParaBuf);
}


VOS_VOID MN_QRYPARA_SendMsg(
    TAF_UINT16                          usClientId,
    TAF_UINT8                           ucOpId,
    TAF_PARA_TYPE                       ucQueryType,
    TAF_UINT16                          usErrorCode,
    TAF_VOID                           *pPara
)
{
    MN_CLIENT_ID_TYPE_UINT16            enClientIdType;
    VOS_UINT32                          ulOamRcvPid;

    enClientIdType = MN_GetClientIdType(usClientId);

    /*广播CLIENT ID的处理*/
    if (MN_CLIENT_ID_BROADCAST ==  usClientId)
    {
        /*只需要发给AT*/
        MN_QRYPARA_SendMsgToAt(usClientId, ucOpId, ucQueryType, usErrorCode, pPara);

        return;
    }

    /*AT CLIENT*/
    if (MN_CLIENT_ID_TYPE_AT == enClientIdType)
    {
        MN_QRYPARA_SendMsgToAt(usClientId, ucOpId, ucQueryType, usErrorCode, pPara);
    }
    else
    {
        /*通过client id获取对应的pid*/
        ulOamRcvPid = MN_GetPidFromClientId(usClientId);

        if (VOS_PID_BUTT == ulOamRcvPid)
        {
            MN_ERR_LOG("MN_QRYPARA_SendMsg: no pid!");
            return;
        }

        /*调用对应的消息发送函数: 目前没有OAM的接口消息，不处理 */
    }

    return;
}


VOS_VOID MN_VC_SendMsgToAt(
    MN_CLIENT_ID_T                      clientId,
    VOS_UINT32                          ulEventType,
    APP_VC_EVENT_INFO_STRU             *pstEvent
)
{
    MN_AT_IND_EVT_STRU                  *pMsg               = TAF_NULL_PTR;
    TAF_UINT16                          usLength            = 0;
    TAF_UINT32                          ulEventTypeLen;

    if(TAF_NULL_PTR == pstEvent)
    {
        MN_WARN_LOG("MN_VC_SendMsgToAt: pEvent NULL");
        return;
    }

    ulEventTypeLen  = sizeof(ulEventType);
    usLength = (TAF_UINT16)((MN_AT_INTERFACE_MSG_HEADER_LEN + sizeof(MN_MSG_EVENT_INFO_STRU)) + ulEventTypeLen);

    /* 从第二个字节开始 */
    pMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, usLength);
    if (TAF_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_VC_SendMsgToAt:ERROR:Alloc Msg");
        return;
    }

    /* 拷贝本地缓存和实体索引到pMsg->aucValue;*/
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = WUEPS_PID_TAF;
    pMsg->ulReceiverPid   = WUEPS_PID_AT;

    pMsg->usMsgName = (TAF_UINT16)MN_CALLBACK_VOICE_CONTROL;
    pMsg->aucReserved1[0] = 0;
    pMsg->aucReserved1[1] = 0;
    pMsg->clientId  = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    pMsg->usLen     = (VOS_UINT16)(sizeof(MN_MSG_EVENT_INFO_STRU) + ulEventTypeLen);     /* 类型 */

    pstEvent->clientId = MN_GetRealClientId(pstEvent->clientId, WUEPS_PID_TAF);

    /* 填写新消息内容 */
    PS_MEM_CPY(pMsg->aucContent, &ulEventType, ulEventTypeLen);
    PS_MEM_CPY((APP_VC_EVENT_INFO_STRU *)&(pMsg->aucContent[ulEventTypeLen]),
               pstEvent,
               sizeof(APP_VC_EVENT_INFO_STRU));

    /*发送消息到AT_PID;*/
    if ( 0 != PS_SEND_MSG( WUEPS_PID_TAF, pMsg ) )
    {
        MN_ERR_LOG("MN_VC_SendMsgToAt:ERROR");
        return;
    }
}


VOS_VOID MN_VC_SendMsg(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulEventType,
    APP_VC_EVENT_INFO_STRU             *pstEvent
)
{
    MN_CLIENT_ID_TYPE_UINT16            enClientIdType;
    VOS_UINT32                          ulOamRcvPid;

    enClientIdType = MN_GetClientIdType(usClientId);

    /*广播CLIENT ID的处理*/
    if (MN_CLIENT_ID_BROADCAST ==  usClientId)
    {
        /*只需要发给AT*/
        MN_VC_SendMsgToAt(usClientId, ulEventType, pstEvent);

        return;
    }

    /*AT CLIENT*/
    if (MN_CLIENT_ID_TYPE_AT == enClientIdType)
    {
        MN_VC_SendMsgToAt(usClientId, ulEventType, pstEvent);
    }
    else
    {
        /*通过client id获取对应的pid*/
        ulOamRcvPid = MN_GetPidFromClientId(usClientId);

        if (VOS_PID_BUTT == ulOamRcvPid)
        {
            MN_ERR_LOG("MN_VC_SendMsg: no pid!");
            return;
        }

        /*调用对应的消息发送函数: 目前没有OAM的接口消息，不处理 */
    }

    return;
}



TAF_CS_CAUSE_ENUM_UINT32 TAF_CALL_MapCcCauseToCsCause(
    MN_CALL_CC_CAUSE_ENUM_U8            enCcCause
)
{
    TAF_CS_ERR_CODE_MAP_STRU           *pstCsErrMapTblPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulCsErrMapTblSize;
    VOS_UINT32                          ulCnt;

    pstCsErrMapTblPtr = TAF_CS_GET_CC_ERR_CODE_MAP_TBL_PTR();
    ulCsErrMapTblSize = TAF_CS_GET_CC_ERR_CODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulCsErrMapTblSize; ulCnt++)
    {
        if (pstCsErrMapTblPtr[ulCnt].enCcCause == enCcCause)
        {
            return pstCsErrMapTblPtr[ulCnt].enCsCause;
        }
    }

    return TAF_CS_CAUSE_UNKNOWN;
}


/* Delete MN_GetLaiForMoCtrl */


VOS_UINT32 TAF_CALL_IsEventNeedRpt(
    MN_CALL_EVENT_ENUM_U32              enEventType
)
{
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU   *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
    VOS_UINT32                           ulChkCssiFlg;
    VOS_UINT32                           ulChkCssuFlg;
    VOS_UINT32                           ulChkCuus1IFlg;
    VOS_UINT32                           ulChkCuus1UFlg;
    VOS_UINT32                           ulRslt;

    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();
    ulRslt                  = VOS_TRUE;

    ulChkCssiFlg    = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                                TAF_SDC_RPT_CMD_CSSI);

    ulChkCssuFlg    = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                                TAF_SDC_RPT_CMD_CSSU);

    ulChkCuus1IFlg  = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                                TAF_SDC_RPT_CMD_CUUS1I);

    ulChkCuus1UFlg  = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                                TAF_SDC_RPT_CMD_CUUS1U);

    switch (enEventType)
    {
        /* ORIG主动上报 */
        case MN_CALL_EVT_ORIG:

            ulRslt = TAF_CALL_IsOrigNeedRpt();
            break;

        /* CONF主动上报 */
        case MN_CALL_EVT_CALL_PROC:

            ulRslt = TAF_CALL_IsConfNeedRpt();
            break;

        /* CONN主动上报 */
        case MN_CALL_EVT_CONNECT:

            ulRslt = TAF_CALL_IsConnNeedRpt();
            break;

        /* CEND主动上报 */
        case MN_CALL_EVT_RELEASED:

            ulRslt = TAF_CALL_IsCendNeedRpt();
            break;

        /* CSSN主动上报关闭 */
        case MN_CALL_EVT_SS_NOTIFY:
            if ( (VOS_FALSE == ulChkCssuFlg)
              && (VOS_FALSE == ulChkCssiFlg) )
            {
                ulRslt = VOS_FALSE;
            }
            break;

        /* CUUS1主动上报关闭 */
        case MN_CALL_EVT_UUS1_INFO:
            if ( (VOS_FALSE == ulChkCuus1UFlg)
              && (VOS_FALSE == ulChkCuus1IFlg) )
            {
                ulRslt = VOS_FALSE;
            }
            break;

        default:
            ulRslt = VOS_TRUE;
            break;

    }

    return ulRslt;
}


VOS_UINT32 TAF_MSG_IsEventNeedRpt(
    MN_MSG_EVENT_ENUM_U32              enEventType
)
{
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();
    ulRslt          = VOS_TRUE;

    switch (enEventType)
    {
        /* SMMEMFULL主动上报 */
        case MN_MSG_EVT_STORAGE_EXCEED:
            if (VOS_FALSE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                    TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                    TAF_SDC_RPT_CMD_SMMEMFULL))
            {
                ulRslt = VOS_FALSE;
            }
            break;

        default:
            ulRslt = VOS_TRUE;
            break;

    }

    return ulRslt;
}


VOS_UINT32 TAF_SS_IsEventNeedRpt (
    TAF_SS_EVENT  ulEvent
)
{
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    VOS_UINT32                          ulChkCusdFlg;
    VOS_UINT32                          ulResult;

    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();
    ulChkCusdFlg            = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                                        TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                                        TAF_SDC_RPT_CMD_CUSD);
    ulResult                = VOS_TRUE;

    switch(ulEvent)
    {
        /* CUSD是否需要上报 */
        case TAF_SS_EVT_USS_REQ_IND:
        case TAF_SS_EVT_USS_NOTIFY_IND:
        case TAF_SS_EVT_USS_RELEASE_COMPLETE_IND:
        case TAF_SS_EVT_PROCESS_USS_REQ_CNF:

            if (VOS_FALSE == ulChkCusdFlg)
            {
                ulResult = VOS_FALSE;
            }
            else
            {
                ulResult = VOS_TRUE;
            }

            break;

        default:
            ulResult = VOS_TRUE;
            break;
    }

    return ulResult;

}


VOS_VOID MN_CS_ProcEmergencyCallEvent(
    MN_CALL_EVENT_ENUM_U32              enEventType,
    MN_CALL_INFO_STRU                  *pstEvent
)
{
    VOS_UINT32                              ulResult;
    TAF_TEMP_PROTECT_CONFIG_STRU            stTempProtectPara;

    if (MN_CALL_TYPE_EMERGENCY == pstEvent->enCallType)
    {
        /* 读取温度保护与紧急呼叫交互NV项 */
        ulResult = NV_ReadEx(MODEM_ID_0,
                             en_NV_Item_TEMP_PROTECT_CONFIG,
                             &stTempProtectPara,
                             sizeof(TAF_TEMP_PROTECT_CONFIG_STRU));

        if (NV_OK != ulResult)
        {
            MN_ERR_LOG("MN_CS_ProcEmergencyCallEvent: Read NV fail");
            return;
        }

        if (TAF_EMERGENCY_NOTIFY_ENABLE == stTempProtectPara.ucECallNotifySupport)
        {
            if (MN_CALL_EVT_ORIG == enEventType)
            {
                MN_SendEmergencyCallStatusToOam(TAF_OAM_EMERGENCY_CALL_START);
                TAF_MTA_SndPhyEmergencyCallStatus(MTA_PHY_EMERGENCY_CALL_START);
                return;
            }

            if (MN_CALL_EVT_RELEASED == enEventType)
            {
                MN_SendEmergencyCallStatusToOam(TAF_OAM_EMERGENCY_CALL_END);
                TAF_MTA_SndPhyEmergencyCallStatus(MTA_PHY_EMERGENCY_CALL_END);
                return;
            }
        }
    }

    return;
}


VOS_VOID MN_SendEmergencyCallStatusToOam(
    TAF_OAM_EMERGENCY_CALL_STATUS_ENUM_UINT8                enEventType
)
{
    TAF_OAM_EMERGENCY_CALL_STATUS_STRU                     *pstMsg;
    VOS_UINT32                                              ulLength;

    ulLength = sizeof(TAF_OAM_EMERGENCY_CALL_STATUS_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (TAF_OAM_EMERGENCY_CALL_STATUS_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("MN_SendEmergencyCallStatusToOam: Alloc Msg");
        return;
    }

    /* 填写新消息内容 */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid           = WUEPS_PID_SPY;
    pstMsg->ulLength                = ulLength;
    pstMsg->ulMsgId                 = TAF_OAM_EMERGENCY_CALL_STATUS_NOTIFY;
    pstMsg->enEmergencyCallStatus   = enEventType;
    PS_MEM_SET(pstMsg->aucReserved1, 0x00, sizeof(pstMsg->aucReserved1));

    /*发送消息到OAM的指定PID ;*/
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstMsg))
    {
        MN_ERR_LOG("MN_SendEmergencyCallStatusToOam: PS_SEND_MSG fail.");
        return;
    }
}


VOS_VOID TAF_CALL_SendMsgToStk(
    MN_CALL_EVENT_ENUM_U32              enEventType,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    NAS_CALL_STK_EVT_STRU              *pstMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    /* 为回复OAM的消息TAF_STK_CS_CALLINFO_EVENT_IND申请内存 */
    if (ulLength < 4)
    {
        ulMsgLen = sizeof(NAS_CALL_STK_EVT_STRU) - VOS_MSG_HEAD_LENGTH;
    }
    else
    {
        /*lint -e961*/
        ulMsgLen = sizeof(NAS_CALL_STK_EVT_STRU) - VOS_MSG_HEAD_LENGTH - 4 + ulLength;
        /*lint +e961*/
    }

    pstMsg   = (NAS_CALL_STK_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, ulMsgLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("TAF_CALL_SendMsgToStk: Alloc Msg Failed!");
        return;
    }
    PS_MEM_SET((((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH), 0, ulMsgLen);

    /* 填写新消息内容 */
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = NAS_GetOamReceivePid(MAPS_STK_PID);
    pstMsg->ulMsgId         = TAF_STK_CS_CALLINFO_EVENT_IND;
    pstMsg->enEventType     = enEventType;

    if (VOS_NULL_PTR != pData)
    {
       PS_MEM_CPY(pstMsg->aucEvent, pData, ulLength);
    }

    /* 发送消息到OAM */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstMsg))
    {
        MN_ERR_LOG("TAF_CALL_SendMsgToStk: PS_SEND_MSG ERROR!");
    }

    return;
}


VOS_VOID TAF_CALL_SendMsgToAt(
    MN_CLIENT_ID_T                      usClientId,
    MN_CALL_EVENT_ENUM_U32              enEventType,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    MN_AT_IND_EVT_STRU                 *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulEvtTypeLen;

    ulEvtTypeLen    = sizeof(MN_CALL_EVENT_ENUM_U32);
    ulMsgLen        = MN_AT_INTERFACE_MSG_HEADER_LEN + ulEvtTypeLen + ulLength;

    /* 申请内存 */
    pstMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, ulMsgLen);
    if (TAF_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("TAF_CALL_SendMsgToAt: Alloc Msg Failed!");
        return;
    }
    PS_MEM_SET((((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH), 0, ulMsgLen);

    /* 填写消息公共内容 */
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->usMsgName       = MN_CALLBACK_CS_CALL;
    pstMsg->clientId        = MN_GetRealClientId(usClientId, WUEPS_PID_TAF);
    pstMsg->usLen           = (VOS_UINT16)(ulEvtTypeLen + ulLength);

    /* 填写事件内容 */
    PS_MEM_CPY(pstMsg->aucContent, &enEventType, ulEvtTypeLen);
    if (VOS_NULL_PTR != pData)
    {
        PS_MEM_CPY((pstMsg->aucContent + ulEvtTypeLen), pData, ulLength);
    }

    /* 发送消息到AT */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstMsg))
    {
        MN_ERR_LOG("TAF_CALL_SendMsgToAt: PS_SEND_MSG ERROR!");
    }

    return;
}


VOS_VOID TAF_CALL_SendMsg(
    MN_CLIENT_ID_T                      usClientId,
    MN_CALL_EVENT_ENUM_U32              enEventType,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    MN_CLIENT_ID_TYPE_UINT16            enClientIdType;
    VOS_UINT32                          ulOamRcvPid;

    enClientIdType  = MN_GetClientIdType(usClientId);

    /* 广播CLIENT ID的处理 */
    /* 此处仅关注外层的ClientId，内层结构如果是CALL_INFO结构体
       需要有调用者保证ClientId为真正的ClientId，而不是MN_CLIENT_ALL */
    if (MN_CLIENT_ID_BROADCAST ==  usClientId)
    {
        /*发给STK*/
        TAF_CALL_SendMsgToStk(enEventType, pData, ulLength);

        /* 需要主动上报时发给AT */
        TAF_CALL_SendMsgToAt(usClientId, enEventType, pData, ulLength);

        return;
    }

    /* AT CLIENT */
    if (MN_CLIENT_ID_TYPE_AT == enClientIdType)
    {
        TAF_CALL_SendMsgToAt(usClientId, enEventType, pData, ulLength);
    }
    else
    {
        /*通过client id获取对应的pid*/
        ulOamRcvPid = MN_GetPidFromClientId(usClientId);

        if (MAPS_STK_PID != ulOamRcvPid)
        {
            MN_ERR_LOG("TAF_CALL_SendMsg: ERROR PID!");
            return;
        }

        /*调用对应的消息发送函数*/
        TAF_CALL_SendMsgToStk(enEventType, pData, ulLength);
    }

    return;
}


VOS_UINT32 TAF_GetSpecificFileListRefreshFileInfo(
    VOS_UINT16                          usFileId,
    USIMM_STKREFRESH_IND_STRU          *pstRefreshInd,
    USIMM_CARDAPP_ENUM_UINT32          *penAppType
)
{
    VOS_UINT32                          ulLoop;

    if (USIMM_REFRESH_FILE_LIST != pstRefreshInd->enRefreshType)
    {
        return VOS_FALSE;
    }

    for (ulLoop = 0; ulLoop < pstRefreshInd->usEfNum; ulLoop++)
    {
        if (pstRefreshInd->astEfId[ulLoop].usFileId == usFileId)
        {
            *penAppType = pstRefreshInd->astEfId[ulLoop].enAppType;
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

#if (FEATURE_MULTI_MODEM == FEATURE_ON)

VOS_VOID TAF_SendMtcCsSrvInfoInd(VOS_VOID)
{
    TAF_MTC_CS_SERVICE_INFO_IND_STRU   *pstCsSrvInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;


    pstCsSrvInfo = (TAF_MTC_CS_SERVICE_INFO_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                         WUEPS_PID_TAF,
                                                         sizeof(TAF_MTC_CS_SERVICE_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstCsSrvInfo)
    {
        MN_ERR_LOG("TAF_SendMtcCsSrvInfoInd: Alloc Msg Failed!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCsSrvInfo + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MTC_CS_SERVICE_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstCsSrvInfo->stMsgHeader.ulReceiverPid   = UEPS_PID_MTC;
    pstCsSrvInfo->stMsgHeader.ulMsgName       = ID_MTC_CS_SERVICE_INFO_IND;

    pstCsSrvInfo->ucCallSrvExistFlg = TAF_SDC_GetCsCallExistFlg();
    pstCsSrvInfo->ucSmsSrvExistFlg  = TAF_SDC_GetCsSmsSrvExistFlg();
    pstCsSrvInfo->ucSsSrvExistFlg   = TAF_SDC_GetCsSsSrvExistFlg();

    ulResult = PS_SEND_MSG(WUEPS_PID_TAF, pstCsSrvInfo);
    if( VOS_OK != ulResult )
    {
        MN_ERR_LOG("TAF_SendMtcCsSrvInfoInd: Send Msg Failed!");
    }

    return;
}
#endif



VOS_VOID MN_CALL_GetDataCfgInfoFromBc(
    const NAS_CC_IE_BC_STRU             *pstBc,
    MN_CALL_CS_DATA_CFG_INFO_STRU       *pstDataCfgInfo
)
{
    VOS_UINT32                          ulOffsetAddr;

    ulOffsetAddr = (VOS_UINT32)pstBc + pstBc->LastOctOffset + 2;

    /* 如果CE存在，那么刷新CE */
    if ( ulOffsetAddr > (VOS_UINT32)&pstBc->Octet6c)
    {
        pstDataCfgInfo->enConnElem = pstBc->Octet6c.ConnElement;
    }

    /* 刷新业务名称 */
    if ( ulOffsetAddr > (VOS_UINT32)&pstBc->Octet6)
    {
        if (NAS_CC_ITC_OTHER == pstBc->Octet3.InfoTransCap)
        {
            if (NAS_CC_SYNC == pstBc->Octet6.SyncAsync)
            {
                pstDataCfgInfo->enName =  MN_CALL_CSD_NAME_SYNC_RDI;
            }
            else
            {
                pstDataCfgInfo->enName =  MN_CALL_CSD_NAME_ASYNC_RDI;
            }
        }
        else
        {
            if (NAS_CC_SYNC == pstBc->Octet6.SyncAsync)
            {
                pstDataCfgInfo->enName = MN_CALL_CSD_NAME_SYNC_UDI;
            }
            else
            {
                pstDataCfgInfo->enName = MN_CALL_CSD_NAME_ASYNC_UDI;
            }
        }

    }

    /* 获取speed的值 */
    if ( ulOffsetAddr > (VOS_UINT32)&pstBc->Octet6d )
    {
        switch (pstBc->Octet6d.FNUR)
        {
        case NAS_CC_FNUR_NONE:
            switch (pstBc->Octet6a.UserRate)
            {
            case NAS_CC_USER_RATE_300:
                pstDataCfgInfo->enSpeed = MN_CALL_CSD_SPD_300;
                break;

            case NAS_CC_USER_RATE_1200:
                pstDataCfgInfo->enSpeed = MN_CALL_CSD_SPD_1K2;
                break;

            case NAS_CC_USER_RATE_2400:
                pstDataCfgInfo->enSpeed = MN_CALL_CSD_SPD_2K4;
                break;

            case NAS_CC_USER_RATE_4800:
                pstDataCfgInfo->enSpeed = MN_CALL_CSD_SPD_4K8;
                break;

            case NAS_CC_USER_RATE_9600:
                pstDataCfgInfo->enSpeed = MN_CALL_CSD_SPD_9K6;
                break;

            case NAS_CC_USER_RATE_12K:
                pstDataCfgInfo->enSpeed = MN_CALL_CSD_SPD_12K;
                break;

            default:
                break;
            }
            break;

        case NAS_CC_FNUR_9600:
            pstDataCfgInfo->enSpeed = MN_CALL_CSD_SPD_9K6;
            break;

        case NAS_CC_FNUR_14400:
            pstDataCfgInfo->enSpeed = MN_CALL_CSD_SPD_14K4;
            break;

        case NAS_CC_FNUR_19200:
            pstDataCfgInfo->enSpeed = MN_CALL_CSD_SPD_19K2;
            break;

        case NAS_CC_FNUR_22800:
            pstDataCfgInfo->enSpeed = NAS_CC_FNUR_22800;
            break;

        case NAS_CC_FNUR_38400:
            pstDataCfgInfo->enSpeed = MN_CALL_CSD_SPD_38K4;
            break;

        case NAS_CC_FNUR_48000:
            pstDataCfgInfo->enSpeed = MN_CALL_CSD_SPD_48K;
            break;

        case NAS_CC_FNUR_56000:
            pstDataCfgInfo->enSpeed = MN_CALL_CSD_SPD_56K;
            break;

        case NAS_CC_FNUR_64000:
            pstDataCfgInfo->enSpeed = MN_CALL_CSD_SPD_64K;
            break;

        case NAS_CC_FNUR_33600:
            pstDataCfgInfo->enSpeed = MN_CALL_CSD_SPD_33K6;
            break;
        case NAS_CC_FNUR_32000:
            pstDataCfgInfo->enSpeed = MN_CALL_CSD_SPD_32K;
            break;

        case NAS_CC_FNUR_31200:
            pstDataCfgInfo->enSpeed = MN_CALL_CSD_SPD_31K2;
            break;

        default:
            break;
        }
    }
}




VOS_UINT32  MN_CALL_JudgeMtCallType(
    const NAS_CC_IE_BC_OCTET3_STRU      *pstOctet3,
    const NAS_CC_IE_BC_OCTET5A_STRU     *pstOctet5a,
    MN_CALL_TYPE_ENUM_U8                *penCallType
)
{
    switch (pstOctet3->InfoTransCap)
    {
    case NAS_CC_ITC_SPEECH:
    case NAS_CC_ITC_AUXILIARY_SPEECH:
        *penCallType = MN_CALL_TYPE_VOICE;
        break;

    case NAS_CC_ITC_UDI:
        *penCallType = MN_CALL_TYPE_VIDEO;
        break;

    case NAS_CC_ITC_3D1K:
        *penCallType = MN_CALL_TYPE_CS_DATA;
        break;

    case NAS_CC_ITC_FAX:
        *penCallType = MN_CALL_TYPE_FAX;
        break;

    case NAS_CC_ITC_OTHER:
        if (NAS_CC_OTHER_RA_H223_H245 == pstOctet5a->OtherRA)
        {
            *penCallType = MN_CALL_TYPE_VIDEO;
        }
        else
        {
            return VOS_ERR;
        }
        break;

    default:
        return VOS_ERR;
    }

    return VOS_OK;
}


#if (FEATURE_ON == FEATURE_PTM)

VOS_VOID TAF_SndAcpuOmFaultErrLogInd(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulDataLen,
    NAS_ERR_LOG_ALM_ID_ENUM_U16         usAlmId
)
{
    OM_FAULT_ERR_LOG_IND_STRU                              *pstFaultRptInd = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLen;
    VOS_UINT32                                              ulContentAddr;
    NAS_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_U16                 enReportType;

    /* 申请消息结构内存 */
    /*lint -e961*/
    ulMsgLen     = sizeof(OM_FAULT_ERR_LOG_IND_STRU) - VOS_MSG_HEAD_LENGTH - 4 + ulDataLen;
    /*lint +e961*/
    pstFaultRptInd = (OM_FAULT_ERR_LOG_IND_STRU*)PS_ALLOC_MSG(WUEPS_PID_TAF, ulMsgLen);
    if (VOS_NULL_PTR == pstFaultRptInd)
    {
        TAF_LOG(WUEPS_PID_TAF, VOS_NULL, PS_LOG_LEVEL_ERROR, "TAF_SndAcpuOmFaultErrLogInd:ERROR: Alloc msg fail.");
        return;
    }

    /* 构造消息结构体 */
    pstFaultRptInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstFaultRptInd->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstFaultRptInd->ulReceiverPid     = MSP_PID_DIAG_APP_AGENT;
    pstFaultRptInd->ulSenderPid       = WUEPS_PID_TAF;
    pstFaultRptInd->ulMsgName         = ID_OM_FAULT_ERR_LOG_IND;

    enReportType = NAS_GetErrLogUnsoliReportType(usAlmId);

    if (NAS_ERR_LOG_FAULT_REPORT == enReportType)
    {
        pstFaultRptInd->ulMsgType     = OM_ERR_LOG_MSG_FAULT_REPORT;
    }
    else if (NAS_ERR_LOG_ALARM_REPORT == enReportType)
    {
        pstFaultRptInd->ulMsgType     = OM_ERR_LOG_MSG_ALARM_REPORT;
    }
    else
    {
        pstFaultRptInd->ulMsgType     = OM_ERR_LOG_MSG_TYPE_BUTT;
    }

    pstFaultRptInd->ulMsgSN           = 0;
    pstFaultRptInd->ulRptlen          = ulDataLen;

    ulContentAddr                     = (VOS_UINT32)pstFaultRptInd->aucContent;
    PS_MEM_CPY((VOS_UINT8 *)ulContentAddr, pData, ulDataLen);

    /* 发送消息到ACPU OM模块 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstFaultRptInd))
    {
        TAF_LOG(WUEPS_PID_TAF, VOS_NULL, PS_LOG_LEVEL_ERROR, "TAF_SndAcpuOmFaultErrLogInd:ERROR: SEND MSG FIAL.");
    }

    return;
}
#endif

#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID TAF_SndMmaImsSrvInfoNotify(
    VOS_UINT8                           ucImsCallFlg
)
{
    TAF_MMA_IMS_SRV_INFO_NOTIFY_STRU              *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_MMA_IMS_SRV_INFO_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,sizeof(TAF_MMA_IMS_SRV_INFO_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        MN_WARN_LOG("TAF_SPM_SendMsgSmmaRsp:ERROR: VOS_AllocMsg fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(TAF_MMA_IMS_SRV_INFO_NOTIFY_STRU));

    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid           = WUEPS_PID_MMA;
    pstMsg->ulLength                = sizeof(TAF_MMA_IMS_SRV_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgName               = ID_TAF_MMA_IMS_SRV_INFO_NOTIFY;
    pstMsg->ucImsCallFlg            = ucImsCallFlg;

    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstMsg ) )
    {
        MN_WARN_LOG( "TAF_SndMmaImsSrvInfoNotify:WARNING:SEND ID_TAF_MMA_IMS_SRV_INFO_NOTIFY msg FAIL!" );
    }

    return;
}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID TAF_SndMmaCdmaMoCallStartNtf(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType
)
{
    TAF_MMA_CDMA_MO_CALL_START_NTF_STRU *pstCallStartNtf = VOS_NULL_PTR;

    /* 分配消息 */
    pstCallStartNtf = (TAF_MMA_CDMA_MO_CALL_START_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulModuleId,
                      sizeof(TAF_MMA_CDMA_MO_CALL_START_NTF_STRU));
    if (VOS_NULL_PTR == pstCallStartNtf)
    {
        return;
    }

    /* 填充消息 */
    pstCallStartNtf->ulReceiverPid       = WUEPS_PID_MMA;
    pstCallStartNtf->ulLength            = sizeof(TAF_MMA_CDMA_MO_CALL_START_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET((VOS_UINT8 *)pstCallStartNtf + VOS_MSG_HEAD_LENGTH,
               0x0,
               (VOS_SIZE_T)(sizeof(TAF_MMA_CDMA_MO_CALL_START_NTF_STRU) - VOS_MSG_HEAD_LENGTH));

    pstCallStartNtf->enMsgId            = ID_TAF_MMA_CDMA_MO_CALL_START_NTF;
    pstCallStartNtf->enCallType         = enCallType;

    /* 发送消息 */
    PS_SEND_MSG(ulModuleId, pstCallStartNtf);

    return;
}


VOS_VOID TAF_SndMmaCdmaMoCallEndNtf(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType
)
{
    TAF_MMA_CDMA_MO_CALL_END_NTF_STRU  *pstCallEndNtf = VOS_NULL_PTR;

    /* 分配消息 */
    pstCallEndNtf = (TAF_MMA_CDMA_MO_CALL_END_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulModuleId,
                      sizeof(TAF_MMA_CDMA_MO_CALL_END_NTF_STRU));
    if (VOS_NULL_PTR == pstCallEndNtf)
    {
        return;
    }

    /* 填充消息 */
    pstCallEndNtf->ulReceiverPid        = WUEPS_PID_MMA;
    pstCallEndNtf->ulLength             = sizeof(TAF_MMA_CDMA_MO_CALL_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET((VOS_UINT8 *)pstCallEndNtf + VOS_MSG_HEAD_LENGTH,
               0x0,
               (VOS_SIZE_T)(sizeof(TAF_MMA_CDMA_MO_CALL_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH));

    pstCallEndNtf->enMsgId              = ID_TAF_MMA_CDMA_MO_CALL_END_NTF;
    pstCallEndNtf->enCallType           = enCallType;

    /* 发送消息 */
    PS_SEND_MSG(ulModuleId, pstCallEndNtf);

    return;
}



VOS_VOID TAF_SndMmaCdmaMoCallSuccessNtf(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType
)
{
    TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF_STRU   *pstCallSuccNtf = VOS_NULL_PTR;

    /* 分配消息 */
    pstCallSuccNtf = (TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulModuleId,
                      sizeof(TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF_STRU));
    if (VOS_NULL_PTR == pstCallSuccNtf)
    {
        return;
    }

    /* 填充消息 */
    pstCallSuccNtf->ulReceiverPid       = WUEPS_PID_MMA;
    pstCallSuccNtf->ulLength            = sizeof(TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET((VOS_UINT8 *)pstCallSuccNtf + VOS_MSG_HEAD_LENGTH,
                0x0,
                (VOS_SIZE_T)(sizeof(TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF_STRU) - VOS_MSG_HEAD_LENGTH));

    pstCallSuccNtf->enMsgId             = ID_TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF;
    pstCallSuccNtf->enCallType          = enCallType;

    /* 发送消息 */
    PS_SEND_MSG(ulModuleId, pstCallSuccNtf);

    return;
}



VOS_VOID TAF_SndMmaCdmaCallRedialSystemAcquireNtf(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType,
    VOS_UINT32                          ulCause
)
{
    TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU       *pstCallRedialNtf = VOS_NULL_PTR;

    /* 分配消息 */
    pstCallRedialNtf = (TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ulModuleId,
                       sizeof(TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU));
    if (VOS_NULL_PTR == pstCallRedialNtf)
    {
        return;
    }

    /* 填充消息 */
    pstCallRedialNtf->ulReceiverPid     = WUEPS_PID_MMA;
    pstCallRedialNtf->ulLength          = sizeof(TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET((VOS_UINT8 *)pstCallRedialNtf + VOS_MSG_HEAD_LENGTH,
                0x0,
                (VOS_SIZE_T)(sizeof(TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU) - VOS_MSG_HEAD_LENGTH));

    pstCallRedialNtf->enMsgId           = ID_TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF;
    pstCallRedialNtf->enCallType        = enCallType;
    pstCallRedialNtf->ulCause           = ulCause;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_TAF, pstCallRedialNtf);

    return;
}


VOS_VOID TAF_SndMmaPsRatTypeNotify(
    TAF_MMA_PS_RAT_TYPE_ENUM_UINT32     enRatType
)
{
    TAF_MMA_PS_RAT_TYPE_NTF_STRU       *pstRatTypeChgNtf = VOS_NULL_PTR;

    /* 分配消息 */
    pstRatTypeChgNtf = (TAF_MMA_PS_RAT_TYPE_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                        sizeof(TAF_MMA_PS_RAT_TYPE_NTF_STRU));
    if (VOS_NULL_PTR == pstRatTypeChgNtf)
    {
        return;
    }

    /* 填充消息 */
    pstRatTypeChgNtf->ulReceiverPid     = WUEPS_PID_MMA;
    pstRatTypeChgNtf->ulLength          = sizeof(TAF_MMA_PS_RAT_TYPE_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET((VOS_UINT8 *)pstRatTypeChgNtf + VOS_MSG_HEAD_LENGTH,
               0x0,
               (VOS_SIZE_T)(sizeof(TAF_MMA_PS_RAT_TYPE_NTF_STRU) - VOS_MSG_HEAD_LENGTH));

    pstRatTypeChgNtf->ulMsgName         = ID_TAF_MMA_PS_RAT_TYPE_NTF;
    pstRatTypeChgNtf->enRatType         = enRatType;

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_TAF, pstRatTypeChgNtf);

    return;
}

#endif

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

