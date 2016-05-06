/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallProcEccSrv.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2015年10月21日
  功能描述   : TAF X CALL处理ECC业务功能
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月21日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXCallProcEccSrv.h"
#include "cprocstime.h"
#include "TafStdlib.h"
#include "TafLog.h"
#include "TafXCallMntn.h"
#include "TafXCallSndApp.h"
#include "TafXCallSndXsms.h"
#include "TafXCallEccCipher.h"
#include "TafXCallEncKmcMsg.h"
#include "TafXCallSndCttf.h"
#include "taf_xcall_xsms_pif.h"
#include "TafXCallProcNvim.h"
#include "TafXCallSndXcc.h"
#include "TafSdcCtx.h"
#include "TafXCallEccCipher.h"
#include "TafSdcCtx.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_PROC_ECC_SRV_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/***************************************************************************************************
 * 密话事件处理表
 * 注: 事件处理表中，事件处理是按照枚举定义的顺序查找处理，如果新增事件，必须按照枚举类型的大小放到
 *     表中对应位置!!!
 **************************************************************************************************/
TAF_XCALL_ECC_EVENT_PROC_STRU  g_astTafXcallVoiceEncEventProcTab[TAF_XCALL_VOICE_ENC_MSG_EVENT_MAX] =
{
    /* APP消息事件类型 */
    {TAF_XCALL_APP_MSG_EVENT_ENC_VOICE_REQ,                     TAF_XCALL_ProcVoiceEncEventAppEncVoiceReq        },
    {TAF_XCALL_APP_MSG_EVENT_ORIG_REQ,                          TAF_XCALL_ProcVoiceEncEventAppOrigReq            },
    {TAF_XCALL_APP_MSG_EVENT_HANG_UP_REQ,                       TAF_XCALL_ProcVoiceEncEventAppHangUpReq          },

    /* KMC消息事件 */
    {TAF_XCALL_KMC_MSG_EVENT_MO_KEY_RSP,                        TAF_XCALL_ProcVoiceEncEventKmcMoKeyRsp           },
    {TAF_XCALL_KMC_MSG_EVENT_MT_ENCRYPT_IND,                    TAF_XCALL_ProcVoiceEncEventKmcMtEncryptInd       },
    {TAF_XCALL_KMC_MSG_EVENT_MT_KEY_RSP,                        TAF_XCALL_ProcVoiceEncEventKmcMtKeyRsp           },
    {TAF_XCALL_KMC_MSG_EVENT_ERR_IND,                           TAF_XCALL_ProcVoiceEncEventKmcErrInd             },

    /* XCC消息事件类型 */
    {TAF_XCALL_XCC_MSG_EVENT_INCOMING_CALL_IND,                 TAF_XCALL_ProcVoiceEncEventIncomingCallInd       },
    {TAF_XCALL_XCC_MSG_EVENT_DISC_IND,                          TAF_XCALL_ProcVoiceEncEventXccDiscInd            },
    {TAF_XCALL_XCC_MSG_EVENT_TCH_ASSIGN_CMPL_IND,               TAF_XCALL_ProcVoiceEncEventXccTchAssignCmplInd   },
    {TAF_XCALL_XCC_MSG_EVENT_ECC_SERVICE_CNF,                   TAF_XCALL_ProcVoiceEncEventXccEccServiceCnf      },
    {TAF_XCALL_XCC_MSG_EVENT_ANSWER_CALL_CNF,                   TAF_XCALL_ProcVoiceEncEventXccAnswerCnf          },

    /* XSMS消息事件 */
    {TAF_XCALL_XSMS_MSG_EVENT_ENC_VOICE_XSMS_SEND_CNF,           TAF_XCALL_ProcVoiceEncEventXsmsSendCnf          },

    /* 定时器事件 */
    {TAF_XCALL_TIMER_MSG_EVENT_WAIT_ORIG_REQ,                   TAF_XCALL_ProcVoiceEncEventTimerWaitOrigReq      },
    {TAF_XCALL_TIMER_MSG_EVENT_DELAY_SEND_ENCRYPT_REQ,          TAF_XCALL_ProcVoiceEncEventTimerDelaySendEncReq  },
    {TAF_XCALL_TIMER_MSG_EVENT_TX01,                            TAF_XCALL_ProcVoiceEncEventTimerTx01             },
    {TAF_XCALL_TIMER_MSG_EVENT_TX02,                            TAF_XCALL_ProcVoiceEncEventTimerTx02             },

    /* 内部触发事件 */
    {TAF_XCALL_XCC_MSG_EVENT_INT_CALL_REL_IND,                  TAF_XCALL_ProcVoiceEncEventIntCallRelInd         }
};

/***************************************************************************************************
 * 公钥更新事件处理处理表
 * 注: 事件处理表中，事件处理是按照枚举定义的顺序查找处理，如果新增事件，必须按照枚举类型的大小放到
 *     表中对应位置!!!
 **************************************************************************************************/
TAF_XCALL_ECC_EVENT_PROC_STRU  g_astTafXcallPubKeyEventProcTab[TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_MAX] =
{
    /* KMC消息事件 */
    {TAF_XCALL_KMC_MSG_EVENT_PUB_KEY_UPDATE_IND,                TAF_XCALL_ProcPubKeyEventKmcUpdateInd              },
    {TAF_XCALL_KMC_MSG_EVENT_PUB_KEY_UPDATE_ACK,                TAF_XCALL_ProcPubKeyEventKmcUpdateAck              },

    /* XSMS消息事件 */
    {TAF_XCALL_XCC_MSG_EVENT_PUB_KEY_UPDATE_XSMS_SEND_CNF,      TAF_XCALL_ProcPubKeyEventXsmsSendCnf               },

    /* 定时器事件 */
    {TAF_XCALL_TIMER_MSG_EVENT_PUB_KEY_UPDATE_WAIT_ACK,         TAF_XCALL_ProcPubKeyEventTimerWaitAck              }
};

/***************************************************************************************************
 * 远程控制操作事件处理表
 * 注: 事件处理表中，事件处理是按照枚举定义的顺序查找处理，如果新增事件，必须按照枚举类型的大小放到
 *     表中对应位置!!!
 **************************************************************************************************/
TAF_XCALL_ECC_EVENT_PROC_STRU  g_astTafXcallRemoteCtrlEventProcTab[TAF_XCALL_REMOTE_CTRL_MSG_EVENT_MAX] =
{
    /* APP消息事件类型 */
    {TAF_XCALL_APP_MSG_EVENT_REMOTE_CTRL_ANSWER_REQ,            TAF_XCALL_ProcRemoteCtrlEventAppRemoteCtrlAnswerReq  },

    /* KMC消息事件类型 */
    {TAF_XCALL_KMC_MSG_EVENT_ROMOTE_CTRL_CMD_IND,               TAF_XCALL_ProcRemoteCtrlEventKmcRemoteCtrlCmdInd     },

    /* XSMS消息事件 */
    {TAF_XCALL_XCC_MSG_EVENT_ROMOTE_CTRL_XSMS_SEND_CNF,         TAF_XCALL_ProcRemoteCtrlEventXsmsSendCnf},

    {TAF_XCALL_TIMER_MSG_EVENT_REMOTE_CTRL_WAIT_AP_ANSWER,      TAF_XCALL_ProcRemoteCtrlEventTimerWaitApAnswer}

};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_XCALL_FillAdditionalInfo
 功能描述  : 填充KMC额外信息
 输入参数  : pstKmcMsg -- KMC消息结构地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_FillAdditionalInfo(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
)
{
    VOS_INT32                           lSid;
    VOS_INT32                           lNid;
    VOS_UINT16                          usBaseId;

    lSid            = TAF_SDC_Get1xSid();
    lNid            = TAF_SDC_Get1xNid();
    usBaseId        = TAF_SDC_Get1xBaseId();

    /* 根据是否漫游填充附加信息  */

    /*电信协议中有如下描述

    "辅助信息字段包括了终端当前漫游地网络的SID、NID和BSID三个参数。
    这几个参数的顺序为： SID 高8bits+SID 低8bis+NID 高8bits+NID 低8bits+BSID 高8bits+BSID低8bits"

    所以只有在漫游地时才填充辅助信息字段*/
    if (TAF_SDC_SYS_ROAMING_STATUS_OFF == TAF_SDC_Get1xRoamingFlag())
    {
        pstKmcMsg->u.stKeyReq.stAdditionalInfo.usBsid               = 0;
        pstKmcMsg->u.stKeyReq.stAdditionalInfo.usNid                = 0;
        pstKmcMsg->u.stKeyReq.stAdditionalInfo.usSid                = 0;
    }
    else
    {
        pstKmcMsg->u.stKeyReq.stAdditionalInfo.usBsid               = usBaseId;
        pstKmcMsg->u.stKeyReq.stAdditionalInfo.usNid                = (lNid & 0x0000FFFF);
        pstKmcMsg->u.stKeyReq.stAdditionalInfo.usSid                = (lSid & 0x0000FFFF);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_FillKmcReqMsgTempPubKey
 功能描述  : 填充KMC REQ临时公钥信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_FillKmcReqMsgTempPubKey(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg,
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx
)
{
    /* 填充临时公钥信息 */
    pstKmcMsg->u.stKeyReq.stTmpPubKey.ucKeyLen = TAF_XCALL_MIN(pstKsNegoCtx->stTmpPubKey.ucKeyLen,
                                                               TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN);

    PS_MEM_CPY(&(pstKmcMsg->u.stKeyReq.stTmpPubKey.aucKey[0]),
               &(pstKsNegoCtx->stTmpPubKey.aucKey[0]),
               pstKsNegoCtx->stTmpPubKey.ucKeyLen);

    /* 填充公钥版本号 */
    pstKmcMsg->u.stKeyReq.ucKeyVersion = TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber()->ucVerNum;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ConvertRemoteNumFromStdBcdToKmcBcd
 功能描述  : 将远程号码存储的Bcd格式转成语音加密要求的BCD格式的编码
 输入参数  : VOS_UINT8                          *pucStdBcdContent
             VOS_UINT8                           ucStdBcdLen
             VOS_UINT8                          *pucEncVoiceMsgContent
             VOS_UINT8                           ucEncVoiceMsgLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_TRUE: 成功
             VOS_FALSE:失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月28日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_ConvertRemoteNumFromStdBcdToKmcBcd(
    VOS_UINT8                          *pucStdBcdContent,
    VOS_UINT8                           ucStdBcdLen,
    VOS_UINT8                          *pucEncVoiceMsgContent,
    VOS_UINT8                           ucEncVoiceMsgLen
)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucCurByteAddr  = VOS_NULL_PTR;
    VOS_UINT8                           ucTempByte;
    VOS_UINT8                           ucIsOddNum;

    ucTempByte                          = 0x00;
    i                                   = 0;
    ucIsOddNum                          = VOS_FALSE;

    /* 长度检查 */
    if ((ucEncVoiceMsgLen < ucStdBcdLen)
     || (0 == ucStdBcdLen))
    {
        return VOS_FALSE;
    }

    pucCurByteAddr  = pucStdBcdContent + ucStdBcdLen - 1;

    /* 末位字节为全F，返回失败 */
    if ((0xFF == *pucCurByteAddr)
     || (0x0F == (*pucCurByteAddr & 0x0F)))
    {
        return VOS_FALSE;
    }

    /* 若高位为F,说明是奇数个号码，置临时标记 */
    if (0xF0 == (*pucCurByteAddr & 0xF0))
    {
        ucIsOddNum                      = VOS_TRUE;
    }

    PS_MEM_SET(pucEncVoiceMsgContent, 0x00, sizeof(VOS_UINT8) * ucEncVoiceMsgLen);

    if (VOS_TRUE == ucIsOddNum)
    {
        for (i = ucStdBcdLen; i >= 1; i--)
        {
            ucTempByte      = 0x00;

            pucCurByteAddr  = pucStdBcdContent + i - 1;

            ucTempByte      = ucTempByte | (*pucCurByteAddr & 0x0F);

            if (i > 1)
            {
                ucTempByte  = ucTempByte | (*(pucCurByteAddr - 1) & 0xF0);
            }

            /* 从末尾开始往前赋值 */
            *(pucEncVoiceMsgContent + ucEncVoiceMsgLen - 1 - ucStdBcdLen + i)   = ucTempByte;
        }

        return VOS_TRUE;
    }

    for (i = ucStdBcdLen; i >= 1; i--)
    {
        ucTempByte      = 0x00;

        pucCurByteAddr  = pucStdBcdContent + i - 1;

        /* 将高低4位的位置互换 */
        ucTempByte      = ucTempByte | ((*pucCurByteAddr << 4) & 0xF0);
        ucTempByte      = ucTempByte | ((*pucCurByteAddr >> 4) & 0x0F);

        /* 从末尾开始往前赋值 */
        *(pucEncVoiceMsgContent + ucEncVoiceMsgLen - 1 - ucStdBcdLen + i)   = ucTempByte;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ConvertImsiFromStdBcdToKmcBcd
 功能描述  : 将Imsi中转换成语音加密要求的编码格式
             EG: 15位 IMSI = 230 040 680000079
             From StdBcd: 0x08 0x29 0x03 0x40 0x60 0x08 0x00 0x00 0x97 (首位低4位为保留位0x09)
             To   KmcBcd: 0x08 0x02 0x30 0x04 0x06 0x80 0x00 0x00 0x79
 输入参数  : VOS_UINT8                          *pucStdImsiContent,
             VOS_UINT8                          *pucEncVoiceImsiContent,
             VOS_UINT8                           ucEncVoiceImsiLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_TRUE: 成功
             VOS_FALSE:失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月28日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_ConvertImsiFromStdBcdToKmcBcd(
    VOS_UINT8                          *pucImsiContent,
    VOS_UINT8                          *pucEncVoiceImsiContent,
    VOS_UINT8                           ucEncVoiceImsiLen
)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucCurByteAddr  = VOS_NULL_PTR;
    VOS_UINT8                           ucTempByte;
    VOS_UINT8                           ucStdImsiLen;

    ucTempByte                          = 0x00;
    i                                   = 0;
    /* IMSI首字节存储IMSI的长度，第二个字节起存储IMSI内容 */
    ucStdImsiLen                        = *pucImsiContent;

    /* 长度检查 */
    if (ucEncVoiceImsiLen < ucStdImsiLen)
    {
        return VOS_FALSE;
    }

    /* Imsi首字节为长度，从第二个字节开始获取内容 */
    pucCurByteAddr  = pucImsiContent + 1;

    /* 初始化出参 */
    PS_MEM_SET(pucEncVoiceImsiContent, 0x00, sizeof(VOS_UINT8) * ucEncVoiceImsiLen);

    for (i = 0; i < ucStdImsiLen; i++)
    {
        /* 将高低4位的位置互换 */
        ucTempByte  = ucTempByte | ((*(pucCurByteAddr + i) << 4) & 0xF0);
        ucTempByte  = ucTempByte | ((*(pucCurByteAddr + i) >> 4) & 0x0F);

        /* 从末尾开始往前赋值 */
        *(pucEncVoiceImsiContent + ucEncVoiceImsiLen - ucStdImsiLen + i)   = ucTempByte;

        ucTempByte  = 0x00;
    }

    /* 若首字节低4位为9(Imsi保留位), 则将转换后的高4位置0 */
    if (0x09 == (*pucCurByteAddr & 0x09))
    {
        *(pucEncVoiceImsiContent + ucEncVoiceImsiLen - ucStdImsiLen)   &= 0x0F;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_FillKmcReqMsgCipherText
 功能描述  : 填充KMC REQ密文信息
 输入参数  : pstKmcMsg     -- KMC消息
             pstKsNegoCtx  -- 密话协商上下文
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_TRUE: 成功
             VOS_FALSE:失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月28日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_FillKmcReqMsgCipherText(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg,
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx
)
{
    TAF_XCALL_PLAIN_TEXT_INFO_STRU                          stPlainTextInfo;
    TAF_XCALL_HARDWARE_ID_INFO_STRU                         stHardWareIdInfo;
    TAF_ECC_CALL_BCD_NUM_STRU                               stCalledNumInfo;
    TAF_XCALL_CIPHER_ENCRYPTION_STRU                        stEncryption;
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity = VOS_NULL_PTR;

    PS_MEM_SET(&stPlainTextInfo, 0x00, sizeof(TAF_XCALL_PLAIN_TEXT_INFO_STRU));
    PS_MEM_SET(&stHardWareIdInfo, 0x00, sizeof(TAF_XCALL_HARDWARE_ID_INFO_STRU));
    PS_MEM_SET(&stCalledNumInfo, 0x00, sizeof(TAF_ECC_CALL_BCD_NUM_STRU));
    PS_MEM_SET(&stEncryption, 0x00, sizeof(TAF_XCALL_CIPHER_ENCRYPTION_STRU));

    if (VOS_FALSE == TAF_XCALL_GetHardWareInfo(&stHardWareIdInfo))
    {
        return VOS_FALSE;
    }

    /***********************************************************************************************
     * 被叫时：如果在呼叫接续中获取不到主叫号码（Alert with info 消息中主叫号码字段的PI 位为"00"且
     * num_of_char 为"0"，或PI 位为其他非零值），分两种模式分别处理：
     * - 自动模式（由被叫加密通知短信触发）：被叫密钥请求消息中的主叫号码填写从被叫加密通知消息中获
     *   取的主叫号码；不判断"被叫加密通知"消息中的"主叫号码"与当前通话主叫方的匹配问题；
     * - 手动模式（由用户按键触发）：在被叫密钥请求消息中不送主叫号码，"主叫号码"字段填全零("主叫号
     *   码"长度不变，填11 个"0")；
     * 主叫时：如果用户输入的被叫号码包括了前缀（即长度超过了11 位），直接读取用户输入号码的最后11
     * 位被叫号码
     * - 用户使用"临时预约主叫号码识别限制"时，或者在其它场景下可能在被叫号码前加拨前缀
     **********************************************************************************************/
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstKsNegoCtx->ucCallId);

    if ((VOS_FALSE                                      == TAF_XCALL_IsCallingNumExist(pstCallEntity))
     && (TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_MUNAUL_MODE == pstKsNegoCtx->enEccVoiceType))
    {
        stCalledNumInfo.ucNumLen = TAF_ECC_CALL_MAX_BCD_NUM_LEN;

        PS_MEM_SET(&(stCalledNumInfo.aucBcdNum[0]), 0, sizeof(stCalledNumInfo.aucBcdNum));
    }
    else
    {
        stCalledNumInfo.ucNumLen = pstKsNegoCtx->stCallNum.ucNumLen;

        PS_MEM_CPY(stCalledNumInfo.aucBcdNum,
                   pstKsNegoCtx->stCallNum.aucBcdNum,
                   sizeof(stCalledNumInfo.aucBcdNum));
    }


    if (VOS_FALSE == TAF_XCALL_GenerateEncVoicePlainText(TAF_SDC_GetCsimImsi(),
                                                        &stHardWareIdInfo,
                                                        &stCalledNumInfo,
                                                        &stPlainTextInfo))
    {
        return VOS_FALSE;
    }

    TAF_XCALL_MNTN_LogCipherText(&stPlainTextInfo, &stCalledNumInfo);

    stEncryption.ucPubKeyLen            = TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN;
    PS_MEM_CPY(&(stEncryption.aucPubKey[0]),
               &(TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber()->aucPubKey[0]),
               stEncryption.ucPubKeyLen);

    stEncryption.ucPlainDataLen         = stPlainTextInfo.ucNumLen;
    PS_MEM_CPY(&(stEncryption.aucPlainData[0]),
               &(stPlainTextInfo.aucContent[0]),
               stPlainTextInfo.ucNumLen);

    stEncryption.ucCipherDataLen        = TAF_XCALL_KMC_MSG_MAX_CIPHER_LEN;
    stEncryption.pucCipherData          = &(pstKmcMsg->u.stKeyReq.stCipher.aucCipher[0]);

    if (VOS_FALSE == TAF_XCALL_CipherEncrypt(&stEncryption))
    {
        return VOS_FALSE;
    }

    pstKmcMsg->u.stKeyReq.stCipher.usCipherLen   = (VOS_UINT16)stEncryption.ucEncrptionLen;

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_FillKmcKeyReqMsgTypeAndMode
 功能描述  : 填充KMC KEY请求的消息类型以及模式
 输入参数  : pstKmcMsg    -- KMC消息
             pstKsNegoCtx -- 密话协商消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_FillKmcKeyReqMsgTypeAndMode(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg,
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx
)
{
    switch (pstKsNegoCtx->enEccVoiceType)
    {
        case TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_MUNAUL_MODE:
            {
                pstKmcMsg->enSmsType                  = TAF_XCALL_KMC_MSG_TYPE_MO_KEY_REQ;
                pstKmcMsg->u.stKeyReq.enTriggerMode   = TAF_XCALL_KMC_MSG_TRIGGER_MODE_MANUAL;
            }
            break;

        case TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_AUTO_MODE:
            {
                pstKmcMsg->enSmsType                  = TAF_XCALL_KMC_MSG_TYPE_MO_KEY_REQ;
                pstKmcMsg->u.stKeyReq.enTriggerMode   = TAF_XCALL_KMC_MSG_TRIGGER_MODE_AUTO;
            }
            break;

        case TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_MUNAUL_MODE:
            {
                pstKmcMsg->enSmsType                  = TAF_XCALL_KMC_MSG_TYPE_MT_KEY_REQ;
                pstKmcMsg->u.stKeyReq.enTriggerMode   = TAF_XCALL_KMC_MSG_TRIGGER_MODE_MANUAL;
            }
            break;

        case TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_AUTO_MODE:
            {
                pstKmcMsg->enSmsType                  = TAF_XCALL_KMC_MSG_TYPE_MT_KEY_REQ;
                pstKmcMsg->u.stKeyReq.enTriggerMode   = TAF_XCALL_KMC_MSG_TRIGGER_MODE_AUTO;
            }
            break;

        default:
            /* 在调用函数之前，已经类型做了检查，这里不再做特殊处理 */
            break;
    }
}
/*****************************************************************************
 函 数 名  : TAF_XCALL_FillKmcUpdateRspMsg
 功能描述  : 填充KMC Update Rsp Msg
 输入参数  : VOS_VOID
 输出参数  :  TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
 返 回 值  : VOS_FALSE: 失败；
             VOS_TRUE : 成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月27日
    作    者   : l00359089
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XCALL_FillKmcUpdateRspMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
)
{
    pstKmcMsg->enSmsType = TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_RSP;

    if(VOS_TRUE != TAF_XCALL_CipherGetRandom(TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN, pstKmcMsg->u.stPubKeyUpdateRsp.aucRandomData))
    {
        /*随机数获取失败*/
        return VOS_FALSE;
    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetSendXsmsReqOpId
 功能描述  : 获取分配发送XSMS请求opId
 输入参数  : 无
 输出参数  : 无

 返 回 值  : usOpIdSeqNum -- 返回opId发送序列号
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16 TAF_XCALL_GetSendXsmsReqOpId(VOS_VOID)
{
    TAF_XCALL_XSMS_SEND_REQ_OPID_MGMT_CTX                  *pstOpIdMgmt = VOS_NULL_PTR;

    pstOpIdMgmt = TAF_XCALL_GetOpIdMgmtCtxAddr();

    pstOpIdMgmt->usOpIdSeqNum++;

    if (0 == pstOpIdMgmt->usOpIdSeqNum)
    {
        pstOpIdMgmt->usOpIdSeqNum++;
    }

    return (pstOpIdMgmt->usOpIdSeqNum);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_IsCallingNumExist
 功能描述  : 密话被叫时，判断主叫方号码是否存在
 输入参数  : pstCallEntity -- 呼叫实体地址
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月28日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_XCALL_IsCallingNumExist(
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity
)
{
    /****************************************************************************
        被叫时：如果在呼叫接续中获取不到主叫号码（Alert with info 消息中主叫号码字
        段的PI 位为"00"且num_of_char 为"0"，或PI 位为其他非零值），分两种模式分别
        处理：
        - 自动模式（由被叫加密通知短信触发）：被叫密钥请求消息中的主叫号码填写
        从被叫加密通知消息中获取的主叫号码；不判断"被叫加密通知"消息中的"主叫
        号码"与当前通话主叫方的匹配问题；
        - 手动模式（由用户按键触发）：在被叫密钥请求消息中不送主叫号码，"主叫号
        码"字段填全零("主叫号码"长度不变，填11 个"0")；
     ****************************************************************************/
    if (((0 == pstCallEntity->ucPi)
      && (0 == pstCallEntity->stCallNumber.ucNumLen))
     || (0 != pstCallEntity->ucPi))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_IsEncVoiceNumberSameAsCallNumber
 功能描述  : 检查密话号码是否与呼叫号码一致
 输入参数  : ucCallNumLen    -- 呼叫号码长度
             pucCallNum      -- pucCallNum呼叫号码信息
             pstEccRemoteNum -- ECC远端号码长度
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 号码一致； VOS_FALSE: 号码不一致
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XCALL_IsEncVoiceNumberSameAsCallNumber(
    VOS_UINT8                                               ucCallNumLen,
    VOS_UINT8                                              *pucCallNum,
    TAF_ECC_CALL_BCD_NUM_STRU                              *pstEccRemoteNum
)
{
    VOS_INT8                            aucCallNumAsciiNum[TAF_XCALL_MAX_ASCII_NUM_LEN + 1];
    VOS_INT8                            aucEccRemoteAsciiNum[TAF_XCALL_MAX_ENCRYPT_VOICE_NUM + 1];
    VOS_UINT8                           ucCallNumAsciiNumLen;
    VOS_UINT8                           ucEccRemoteAsciiNumLen;

    /* 转换密话请求或密话指示的号码到ascii格式 */
    ucEccRemoteAsciiNumLen = 0;
    PS_MEM_SET(&aucEccRemoteAsciiNum[0], 0, sizeof(aucEccRemoteAsciiNum));
    if (MN_ERR_NO_ERROR != TAF_STD_ConvertBcdNumberToAscii(pstEccRemoteNum->aucBcdNum,
                                                           pstEccRemoteNum->ucNumLen,
                                                           (VOS_CHAR*)aucEccRemoteAsciiNum))
    {
        return VOS_FALSE;
    }

    /* 获取ECC呼叫号码长度 */
    ucEccRemoteAsciiNumLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)aucEccRemoteAsciiNum);

    /* 转换呼叫实体中的号码到ascii格式 */
    ucCallNumAsciiNumLen = 0;
    PS_MEM_SET(&aucCallNumAsciiNum[0], 0, sizeof(aucCallNumAsciiNum));
    if (MN_ERR_NO_ERROR != TAF_STD_ConvertBcdNumberToAscii(pucCallNum,
                                                           ucCallNumLen,
                                                           (VOS_CHAR*)aucCallNumAsciiNum))
    {
        return VOS_FALSE;
    }

    /* 获取呼叫实体中的号码长度 */
    ucCallNumAsciiNumLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)aucCallNumAsciiNum);

    /* 取要比较的号码长度 */
    if (ucEccRemoteAsciiNumLen <= ucCallNumAsciiNumLen )
    {
        /* 对两个号码进行比较 */
        if (0 != PS_MEM_CMP(&aucCallNumAsciiNum[ucCallNumAsciiNumLen - ucEccRemoteAsciiNumLen],
                            &aucEccRemoteAsciiNum[0],
                            ucEccRemoteAsciiNumLen))
        {
            return VOS_FALSE;
        }
    }
    else
    {
        /* ECC号码已经去除了号码前缀这样的字符， 如果呼叫号码小于ECC号码，号码按不一致 */
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SendKmcKeyReqMsg
 功能描述  : 获取MT呼叫状态
 输入参数  : pstKsNegoCtx -- 密话协商上下文
 输出参数  : 无
 返 回 值  : TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32 -- 返回发送结果原因值

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32 TAF_XCALL_SendKmcKeyReqMsg(
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx
)
{
    TAF_XCALL_KMC_MSG_STRU             stKmcMsg;
    VOS_UINT8                          aucMsgData[TAF_XCALL_KMC_MSG_WMS_CDMA_USER_DATA_MAX];
    VOS_UINT16                         usMsgDataLen;

    PS_MEM_SET(&stKmcMsg, 0, sizeof(TAF_XCALL_KMC_MSG_STRU));

    /***********************************************************************************
     * 填充密话请求消息类型以及请求模式
     **********************************************************************************/
    TAF_XCALL_FillKmcKeyReqMsgTypeAndMode(&stKmcMsg, pstKsNegoCtx);

    /***********************************************************************************
     * 生成临时公私钥对，如果生成失败，返回未知错误
     **********************************************************************************/
    PS_MEM_SET(&pstKsNegoCtx->stTmpPubKey,  0, sizeof(TAF_XCALL_KMC_PUB_KEY_STRU));

    PS_MEM_SET(&pstKsNegoCtx->stTmpPrivKey, 0, sizeof(TAF_XCALL_KMC_PRIV_KEY_STRU));

    if (VOS_FALSE == TAF_XCALL_CipherGenTmpKey(&pstKsNegoCtx->stTmpPubKey, &pstKsNegoCtx->stTmpPrivKey))
    {
        return TAF_CALL_APP_ENCRYPT_VOICE_GET_TEMP_PUB_PIVA_KEY_FAILURE;
    }

    /* 填充KMC KEY请求临时公钥信息 */
    TAF_XCALL_FillKmcReqMsgTempPubKey(&stKmcMsg, pstKsNegoCtx);

    /***********************************************************************************
     * 填充密文信息
     **********************************************************************************/
    if (VOS_FALSE == TAF_XCALL_FillKmcReqMsgCipherText(&stKmcMsg, pstKsNegoCtx))
    {
        return TAF_CALL_APP_ENCRYPT_VOICE_FILL_CIPHER_TEXT_FAILURE;
    }

    /***********************************************************************************
     * 填充辅助信息
     **********************************************************************************/
    TAF_XCALL_FillAdditionalInfo(&stKmcMsg);

    /***********************************************************************************
     * KMC KEY请求编码，如果编码失败，返回内部错误
     **********************************************************************************/
    if (TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS != TAF_XCALL_EncodeKmcMsg(&stKmcMsg, &aucMsgData[0], &usMsgDataLen))
    {
        return TAF_CALL_APP_ENCRYPT_VOICE_MSG_ENCODE_FAILUE;
    }

    /***********************************************************************************
     * 申请XSMS发送请求对应opId，如果分配失败，返回内部错误
     **********************************************************************************/
    pstKsNegoCtx->usWaitXsmsCnfOpId = TAF_XCALL_GetSendXsmsReqOpId();

    /***********************************************************************************
     * 发送KMC密话请求消息给XSMS
     **********************************************************************************/
    TAF_XCALL_SendXsmsKmcMsgSendReq(pstKsNegoCtx->usWaitXsmsCnfOpId, (VOS_UINT8)usMsgDataLen, &aucMsgData[0]);

    return TAF_CALL_APP_ENCRYPT_VOICE_SUCC;
}
/*****************************************************************************
 函 数 名  : TAF_XCALL_SendKmcUpdateRspMsg
 功能描述  : 发送公钥更新响应消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE :失败
             VOS_TRUE : 成功

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月27日
    作    者   : l00359089
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XCALL_SendKmcUpdateRspMsg(
    VOS_UINT16                          usOpId,
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
)
{
    VOS_UINT8                          aucMsgData[TAF_XCALL_KMC_MSG_WMS_CDMA_USER_DATA_MAX];
    VOS_UINT16                         usMsgDataLen;

    if (VOS_TRUE != TAF_XCALL_FillKmcUpdateRspMsg(pstKmcMsg))
    {
        return VOS_FALSE;
    }

    /***********************************************************************************
    * KMC 公钥更新响应消息请求编码，如果编码失败，返回内部错误
    **********************************************************************************/
    usMsgDataLen = 0;

    PS_MEM_SET(aucMsgData, 0, sizeof(aucMsgData));

    if (TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS != TAF_XCALL_EncodeKmcMsg(pstKmcMsg, aucMsgData, &usMsgDataLen))
    {
       return VOS_FALSE;
    }

    /***********************************************************************************
    * 发送KMC公钥更新响应消息请求消息给XSMS
    **********************************************************************************/
    TAF_XCALL_SendXsmsKmcMsgSendReq(usOpId, usMsgDataLen, aucMsgData);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcEccEvent
 功能描述  : 处理ECC内部事件
 输入参数  : ulEventType     -- 内部事件
             VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcEccEvent(
    VOS_UINT32                                              ulEventType,
    TAF_XCALL_ECC_SRV_STATE_MACHINE_ID_ENUM_UINT32          enStateMachine,
    VOS_VOID                                               *pMsg,
    VOS_VOID                                               *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegotiateCtx   = VOS_NULL_PTR;
    TAF_XCALL_PUBLIC_KEY_UPDATE_CTX                        *pstPubkeyUPdateCtx  = VOS_NULL_PTR;
    TAF_XCALL_REMOTE_CTRL_CTX                              *pstRemoteCtrlCtx    = VOS_NULL_PTR;

    switch (enStateMachine)
    {
        case TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC:
            {
                pstKsNegotiateCtx                           = TAF_XCALL_GetKsNegotiateCtxAddr();

                TAF_XCALL_MNTN_LogVoiceEncryptState((TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType,
                                                     pstKsNegotiateCtx->enVoiceEncState);

                TAF_XCALL_ProcKmcKsNegotiateProcedure((TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType, pMsg, pKmcDecMsg);

                TAF_XCALL_MNTN_LogVoiceEncryptState((TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType,
                                                     pstKsNegotiateCtx->enVoiceEncState);
                break;
            }
        case TAF_XCALL_ECC_SRV_STATE_MACHINE_PUB_KEY_UPDATE:
            {
                pstPubkeyUPdateCtx                          = TAF_XCALL_GetPubKeyUpdateCtxAddr();

                TAF_XCALL_MNTN_LogEncVoiceKeyUpdateState((TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType,
                                                          pstPubkeyUPdateCtx->enK0UpdateState);

                TAF_XCALL_ProcKmcPublicKeyUpdateProcedure((TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType, pMsg, pKmcDecMsg);

                TAF_XCALL_MNTN_LogEncVoiceKeyUpdateState((TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType,
                                                          pstPubkeyUPdateCtx->enK0UpdateState);
                break;
            }
        case TAF_XCALL_ECC_SRV_STATE_MACHINE_REMOTE_CTRL:
            {
                pstRemoteCtrlCtx                            = TAF_XCALL_GetRemoteCtrlCtxAddr();

                TAF_XCALL_MNTN_LogEncVoiceRemoteCtrlState((TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType,
                                                           pstRemoteCtrlCtx->enRemoteCtrlState);

                TAF_XCALL_ProcKmcRemoteControlProcedure((TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType, pMsg, pKmcDecMsg);

                TAF_XCALL_MNTN_LogEncVoiceRemoteCtrlState((TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType,
                                                           pstRemoteCtrlCtx->enRemoteCtrlState);
                break;
            }
        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcKmcKsNegotiateProcedure
 功能描述  : 处理KMC的Ks协商流程
 输入参数  : enEventType     -- 内部事件
             VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcKmcKsNegotiateProcedure(
    TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32          enEventType,
    VOS_VOID                                               *pMsg,
    VOS_VOID                                               *pKmcDecMsg
)
{
    /* 检查当前的事件类型是否超出范围或与tab中的事件类型是否一致 */
    if ((enEventType >= TAF_XCALL_VOICE_ENC_MSG_EVENT_MAX)
     || (enEventType != g_astTafXcallVoiceEncEventProcTab[enEventType].ulEventType))
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF, "TAF_XCALL_ProcKmcKsNegotiateProcedure: enEventType = ", enEventType);

        return;
    }

    g_astTafXcallVoiceEncEventProcTab[enEventType].pfEventProcFun(pMsg, pKmcDecMsg);


    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcKmcPublicKeyUpdateProcedure
 功能描述  : 处理KMC公钥更新流程
 输入参数  : enEventType     -- 内部事件
             VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcKmcPublicKeyUpdateProcedure(
    TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32     enEventType,
    VOS_VOID                                               *pMsg,
    VOS_VOID                                               *pKmcDecMsg
)
{
    /* 检查当前的事件类型是否超出范围或与tab中的事件类型是否一致 */
    if ((enEventType >= TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_MAX)
     || (enEventType != g_astTafXcallPubKeyEventProcTab[enEventType].ulEventType))
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF, "TAF_XCALL_ProcKmcPublicKeyUpdateProcedure: enEventType = ", enEventType);

        return;
    }

    g_astTafXcallPubKeyEventProcTab[enEventType].pfEventProcFun(pMsg, pKmcDecMsg);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcKmcRemoteControlProcedure
 功能描述  : 处理远程控制流程
 输入参数  : enEventType     -- 内部事件
             VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcKmcRemoteControlProcedure(
    TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM_UINT32        enEventType,
    VOS_VOID                                               *pMsg,
    VOS_VOID                                               *pKmcDecMsg
)
{
    /* 检查当前的事件类型是否超出范围或与tab中的事件类型是否一致 */
    if ((enEventType >= TAF_XCALL_REMOTE_CTRL_MSG_EVENT_MAX)
     || (enEventType != g_astTafXcallRemoteCtrlEventProcTab[enEventType].ulEventType))
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF, "TAF_XCALL_ProcKmcRemoteControlProcedure: enEventType = ", enEventType);

        return;
    }

    g_astTafXcallRemoteCtrlEventProcTab[enEventType].pfEventProcFun(pMsg, pKmcDecMsg);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ExitVoiceEncriptProcedure
 功能描述  : 退出语音加密流程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月3日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ExitVoiceEncriptProcedure(VOS_VOID)
{
    /* 停止可能相关的密话定时器 */
    TAF_XCALL_StopTimer(TI_TAF_XCALL_VOICE_ENCRYPT_WAIT_ORIG_REQ_TIMER, 0);
    TAF_XCALL_StopTimer(TI_TAF_XCALL_DELAY_SEND_ENCRYPT_REQ, 0);
    TAF_XCALL_StopTimer(TI_TAF_XCALL_TX01_TIMER, 0);
    TAF_XCALL_StopTimer(TI_TAF_XCALL_TX02_TIMER, 0);

    /* 清除之前保存的KEY协商的上下文信息 */
    TAF_XCALL_InitEncVoiceKeyNegotiateCtx();
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ExitPubKeyUpdateProcedure
 功能描述  : 退出公钥更新流程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月3日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ExitPubKeyUpdateProcedure(VOS_VOID)
{
    TAF_XCALL_StopTimer(TI_TAF_XCALL_PUB_KEY_UPDATE_WAIT_ACK_TIMER, 0);

    /* 初始化公钥更新上下文信息 */
    TAF_XCALL_InitEncVoiceKmcUpdateCtx();
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ExitRemoteCtrlOpertionProcedure
 功能描述  : 退出远程控制操作流程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月3日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ExitRemoteCtrlOpertionProcedure(VOS_VOID)
{
    TAF_XCALL_StopTimer(TI_TAF_XCALL_REMOTE_CTRL_WAIT_AP_ANSWER_TIMER, 0);

    /* 初始化公钥更新上下文信息 */
    TAF_XCALL_InitEncVoiceRemoteCtrlCtx();
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncKmcKeyRsp
 功能描述  : 处理KMC下发的MT密钥响应事件
 输入参数  : *pMsg        -- 事件对应的消息内容
             pKmcDecMsg   -- KMC解码消息
             pstKsNegoCtx -- 密话上下文信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XCALL_VerifySignature(
    VOS_UINT8                           ucPubKeyLen,
    VOS_UINT8                          *pucPubKey,
    VOS_UINT8                           ucSignInfoLen,
    VOS_UINT8                          *pucSignInfo,
    VOS_UINT8                           ucSignDataLen,
    VOS_UINT8                          *pucSignData
)
{
    TAF_XCALL_CIPHER_VERIFY_STRU                            stCipherVerify;

    PS_MEM_SET(&stCipherVerify, 0, sizeof(stCipherVerify));

    stCipherVerify.ucPubKeyLen = (VOS_UINT8)TAF_XCALL_MIN(ucPubKeyLen, TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN);
    PS_MEM_CPY(&stCipherVerify.aucPubKey[0], pucPubKey, stCipherVerify.ucPubKeyLen);

    stCipherVerify.ucSigntureInfoLen = (VOS_UINT8)TAF_XCALL_MIN(ucSignInfoLen, TAF_XCALL_KMC_MSG_MAX_SIGN_INFO_LEN);
    PS_MEM_CPY(&stCipherVerify.auSigntureInfo[0], pucSignInfo, stCipherVerify.ucSigntureInfoLen);


    stCipherVerify.ucSigntureDataLen = TAF_XCALL_MIN(ucSignDataLen, TAF_XCALL_KMC_MSG_MAX_SIGN_DATA_LEN);
    PS_MEM_CPY(&stCipherVerify.auSigntureData[0], pucSignData, stCipherVerify.ucSigntureDataLen);

    return TAF_XCALL_CipherVerify(&stCipherVerify);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcMoAutoModeVoiceEncReq
 功能描述  : 处理用户下发的MO自动模式的密话请求
 输入参数  : pstKsNegoCtx      -- 密话协商上下文信息
             pstAppEncVoiceReq -- 密话请求消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcMoAutoModeVoiceEncReq(
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx,
    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                    *pstAppEncVoiceReq
)
{
    VOS_UINT32                                              ulCallIdNum;
    VOS_UINT8                                               aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity = VOS_NULL_PTR;

    /***********************************************************************************
     * 密话状态不匹配
     **********************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_STATE_MISMATCH);

        return;
    }

    PS_MEM_SET(&aucCallIds[0], 0, sizeof(aucCallIds));

    ulCallIdNum = TAF_XCALL_GetAllUsedCallId(&aucCallIds[0]);

    /***********************************************************************************
     * 如果存在两路呼叫，拒绝密话
     **********************************************************************************/
    if (TAF_XCALL_CALL_ENTITY_MAX_NUM == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAT_CALL_APP_ENCRYPT_VOICE_TWO_CALL_ENTITY_EXIST);

        return;
    }

    /***********************************************************************************
     * 如果无呼叫存在，则保存密话号码，等待呼叫请求
     **********************************************************************************/
    if (0 == ulCallIdNum)
    {
        pstKsNegoCtx->enEccVoiceType = pstAppEncVoiceReq->enEccVoiceType;

        PS_MEM_CPY(&pstKsNegoCtx->stCallNum,
                   &pstAppEncVoiceReq->stDialNumber,
                   sizeof(TAF_ECC_CALL_BCD_NUM_STRU));

        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_SUCC);

        TAF_XCALL_StartTimer(TI_TAF_XCALL_VOICE_ENCRYPT_WAIT_ORIG_REQ_TIMER, TI_TAF_XCALL_VOICE_ENCRYPT_WAIT_ORIG_REQ_LEN, 0);

        pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ORIG_REQ;

        return;
    }

    /***********************************************************************************
     * 检查呼叫方向，如果当前呼叫为MT呼叫，则密话操作失败
     **********************************************************************************/
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(aucCallIds[0]);

    if (MN_CALL_DIR_MO != pstCallEntity->enCallDir)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_NO_MO_CALL);

        return;
    }

    /***********************************************************************************
     * 如果MO呼叫不在DIALING状态或ACTIVE状态，则返回密话操作失败
     **********************************************************************************/
    if ((MN_CALL_S_ACTIVE   != pstCallEntity->enCallState)
     && (MN_CALL_S_DIALING  != pstCallEntity->enCallState)
     && (MN_CALL_S_ALERTING != pstCallEntity->enCallState))
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_CALL_STATE_NOT_ALLOWED);

        return;
    }

    /***********************************************************************************
     * 检查密话号码与呼叫实体号码是否一致
     **********************************************************************************/
    if (VOS_FALSE == TAF_XCALL_IsEncVoiceNumberSameAsCallNumber(pstCallEntity->stCalledNumber.ucNumLen,
                                                                &pstCallEntity->stCalledNumber.aucBcdNum[0],
                                                                &(pstAppEncVoiceReq->stDialNumber)))
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_CALL_NUM_MISMATCH);

        return;
    }

    /***********************************************************************************
     * 保存密话请求类型以及对端号码, 通知用户密话请求成功
     **********************************************************************************/
    pstKsNegoCtx->ucCallId       = aucCallIds[0];
    pstKsNegoCtx->enEccVoiceType = pstAppEncVoiceReq->enEccVoiceType;

    PS_MEM_CPY(&pstKsNegoCtx->stCallNum,
               &pstAppEncVoiceReq->stDialNumber,
               sizeof(TAF_ECC_CALL_BCD_NUM_STRU));

    TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_SUCC);

    /***********************************************************************************
     * 如果呼叫为active状态，检查TCH状态，如果TCH已指派，则迁移到启动2s延时定时器，等待密
     * 话请求发送，否则等待TCH指派指示状态
     **********************************************************************************/
    if (VOS_TRUE == pstCallEntity->ucTchAssignInd)
    {
        TAF_XCALL_StartTimer(TI_TAF_XCALL_DELAY_SEND_ENCRYPT_REQ,
                             TAF_XCALL_GetVoiceEncryptReqDelaySendTimerLen() * 1000,
                             0);

        pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_DELAY_SEND_ENCRYPT_REQ;
    }
    else
    {
        pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_TCH_ASSIGN_CMPL;
    }
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcMtAutoModeVoiceEncReq
 功能描述  : 处理用户下发的Mt自动模式的密话请求
 输入参数  : pstKsNegoCtx      -- 密话协商上下文信息
             pstAppEncVoiceReq -- 密话请求消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcMtAutoModeVoiceEncReq(
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx,
    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                    *pstAppEncVoiceReq
)
{
    VOS_UINT32                                              ulCallIdNum;
    VOS_UINT8                                               aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity = VOS_NULL_PTR;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEncVoiceSendRslt;

    /***********************************************************************************
     * 如果当前密话状态不在等待密话请求状态，拒绝密话请求
     **********************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_AP_ENCRYPT_REQ != pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_STATE_MISMATCH);

        return;
    }

    PS_MEM_SET(&aucCallIds[0], 0, sizeof(aucCallIds));

    ulCallIdNum = TAF_XCALL_GetAllUsedCallId(&aucCallIds[0]);

    /***********************************************************************************
     * 如果存在两路呼叫或无呼叫存在，拒绝密话请求(应该不存在该场景，这里做一下保护，避免callId为非法值)
     **********************************************************************************/
    if (TAF_XCALL_CALL_ENTITY_MAX_NUM == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAT_CALL_APP_ENCRYPT_VOICE_TWO_CALL_ENTITY_EXIST);

        return;
    }

    /***********************************************************************************
     * 如果无呼叫存在，拒绝密话请求(应该不存在该场景，这里做一下保护，避免callId为非法值)
     **********************************************************************************/
    if (0 == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_NO_CALL_EXIST);

        return;
    }

    /***********************************************************************************
     * 检查呼叫方向，如果当前呼叫不是MT呼叫，则密话操作失败
     **********************************************************************************/
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(aucCallIds[0]);

    if (MN_CALL_DIR_MT != pstCallEntity->enCallDir)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_NO_MT_CALL);

        return;
    }

    /***********************************************************************************************
     * 检查密话号码与呼叫实体号码是否一致, 对于MT自动，号码已经在密话指示时，进行了比较，这里只要比
     * 密话保存的号码即可
     **********************************************************************************************/
    if (VOS_FALSE == TAF_XCALL_IsEncVoiceNumberSameAsCallNumber(pstKsNegoCtx->stCallNum.ucNumLen,
                                                                &(pstKsNegoCtx->stCallNum.aucBcdNum[0]),
                                                                &(pstAppEncVoiceReq->stDialNumber)))
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_CALL_NUM_MISMATCH);

        return;
    }

    /***********************************************************************************************
     * 保存密话请求类型(注: 这里号码不需要保存了，收到密话指示时，已经保存了)
     **********************************************************************************************/
    pstKsNegoCtx->ucCallId       = aucCallIds[0];
    pstKsNegoCtx->enEccVoiceType = pstAppEncVoiceReq->enEccVoiceType;

    /***********************************************************************************
     * 如果呼叫为active状态，发送密话请求；否则，在incoming状态，等待用户接听请求
     **********************************************************************************/
    if (MN_CALL_S_ACTIVE == pstCallEntity->enCallState)
    {
        enEncVoiceSendRslt = TAF_XCALL_SendKmcKeyReqMsg(pstKsNegoCtx);

        if (TAF_CALL_APP_ENCRYPT_VOICE_SUCC != enEncVoiceSendRslt)
        {
            TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl,
                                            enEncVoiceSendRslt);

            /* 清除之前保存的KEY协商的上下文信息 */
            TAF_XCALL_ExitVoiceEncriptProcedure();

            return;
        }

        TAF_XCALL_StartTimer(TI_TAF_XCALL_TX01_TIMER, TI_TAF_XCALL_TX01_LEN, 0);

        pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP;

    }
    else
    {
        pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WATIING_CALL_ACCEPT_REQ;
    }

    TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_SUCC);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcMoManualModeVoiceEncReq
 功能描述  : 处理用户下发的MO自动模式的密话请求
 输入参数  : pstKsNegoCtx      -- 密话协商上下文信息
             pstAppEncVoiceReq -- 密话请求消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcMoManualModeVoiceEncReq(
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx,
    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                    *pstAppEncVoiceReq
)
{
    VOS_UINT32                                              ulCallIdNum;
    VOS_UINT8                                               aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity = VOS_NULL_PTR;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEncVoiceSendRslt;

    /***********************************************************************************
     * 密话状态不匹配
     **********************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_STATE_MISMATCH);

        return;
    }

    PS_MEM_SET(&aucCallIds[0], 0, sizeof(aucCallIds));

    ulCallIdNum = TAF_XCALL_GetAllUsedCallId(&aucCallIds[0]);

    /***********************************************************************************
     * 如果存在两路呼叫或无呼叫存在，拒绝密话请求
     **********************************************************************************/
    if (TAF_XCALL_CALL_ENTITY_MAX_NUM == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAT_CALL_APP_ENCRYPT_VOICE_TWO_CALL_ENTITY_EXIST);

        return;
    }

    /***********************************************************************************
     * 如果无呼叫存在，拒绝密话请求
     **********************************************************************************/
    if (0 == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_NO_CALL_EXIST);

        return;
    }

    /***********************************************************************************
     * 检查呼叫方向，如果当前呼叫不是MO呼叫，则密话操作失败
     **********************************************************************************/
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(aucCallIds[0]);

    if (MN_CALL_DIR_MO   != pstCallEntity->enCallDir)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_NO_MO_CALL);

        return;
    }

    /***********************************************************************************
     * 检查呼叫呼叫状态，如果当前呼叫不在激活态，则密话操作失败
     **********************************************************************************/
    if (MN_CALL_S_ACTIVE != pstCallEntity->enCallState)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_CALL_STATE_NOT_ALLOWED);

        return;
    }

    /***********************************************************************************
     * 检查密话号码与呼叫实体号码是否一致
     **********************************************************************************/
    if (VOS_FALSE == TAF_XCALL_IsEncVoiceNumberSameAsCallNumber(pstCallEntity->stCalledNumber.ucNumLen,
                                                                &pstCallEntity->stCalledNumber.aucBcdNum[0],
                                                                &(pstAppEncVoiceReq->stDialNumber)))
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_CALL_NUM_MISMATCH);

        return;
    }

    /***********************************************************************************
     * 保存密话请求类型以及对端号码, 发送密话请求。如果发送密话请求失败，通知用户密话失败
     **********************************************************************************/
    pstKsNegoCtx->ucCallId       = aucCallIds[0];
    pstKsNegoCtx->enEccVoiceType = pstAppEncVoiceReq->enEccVoiceType;

    PS_MEM_CPY(&pstKsNegoCtx->stCallNum,
               &pstAppEncVoiceReq->stDialNumber,
               sizeof(TAF_ECC_CALL_BCD_NUM_STRU));

    enEncVoiceSendRslt = TAF_XCALL_SendKmcKeyReqMsg(pstKsNegoCtx);

    if (TAF_CALL_APP_ENCRYPT_VOICE_SUCC != enEncVoiceSendRslt)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl,
                                        enEncVoiceSendRslt);

        /* 清除之前保存的KEY协商的上下文信息 */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /***********************************************************************************
     * 通知用户密话请求成功，状态迁移到等待KMC密话回复
     **********************************************************************************/
    TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_SUCC);


    TAF_XCALL_StartTimer(TI_TAF_XCALL_TX01_TIMER, TI_TAF_XCALL_TX01_LEN, 0);

    pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP;

}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcMtManualModeVoiceEncReq
 功能描述  : 处理用户下发的MT自动模式的密话请求
 输入参数  : pstKsNegoCtx      -- 密话协商上下文信息
             pstAppEncVoiceReq -- 密话请求消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcMtManualModeVoiceEncReq(
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx,
    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                    *pstAppEncVoiceReq
)
{
    VOS_UINT32                                              ulCallIdNum;
    VOS_UINT8                                               aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity = VOS_NULL_PTR;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEncVoiceSendRslt;

    /***********************************************************************************
     * 密话状态不匹配
     **********************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_STATE_MISMATCH);

        return;
    }

    PS_MEM_SET(&aucCallIds[0], 0, sizeof(aucCallIds));

    ulCallIdNum = TAF_XCALL_GetAllUsedCallId(&aucCallIds[0]);

    /***********************************************************************************
     * 如果存在两路呼叫或无呼叫存在，拒绝密话请求
     **********************************************************************************/
    if (TAF_XCALL_CALL_ENTITY_MAX_NUM == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAT_CALL_APP_ENCRYPT_VOICE_TWO_CALL_ENTITY_EXIST);

        return;
    }

    /***********************************************************************************
     * 如果无呼叫存在，拒绝密话请求
     **********************************************************************************/
    if (0 == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_NO_CALL_EXIST);

        return;
    }

    /***********************************************************************************
     * 检查呼叫方向，如果当前呼叫不是MT呼叫，则密话操作失败
     **********************************************************************************/
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(aucCallIds[0]);

    if (MN_CALL_DIR_MT != pstCallEntity->enCallDir)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_NO_MT_CALL);

        return;
    }

    /***********************************************************************************
     * 检查呼叫呼叫状态，如果当前呼叫不在激活态，则密话操作失败
     **********************************************************************************/
    if (MN_CALL_S_ACTIVE != pstCallEntity->enCallState)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_CALL_STATE_NOT_ALLOWED);

        return;
    }

    /***********************************************************************************
     * 检查密话号码与呼叫实体号码是否一致
     **********************************************************************************/
    /* 如果主叫号码(即对端号码)存在时，才进行号码比较 */
    if (VOS_TRUE == TAF_XCALL_IsCallingNumExist(pstCallEntity))
    {
        if (VOS_FALSE == TAF_XCALL_IsEncVoiceNumberSameAsCallNumber(pstCallEntity->stCallNumber.ucNumLen,
                                                                    &pstCallEntity->stCallNumber.aucBcdNum[0],
                                                                    &(pstAppEncVoiceReq->stDialNumber)))
        {
            TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_CALL_NUM_MISMATCH);

            return;
        }
    }

    /***********************************************************************************
     * 保存密话模式以及号码，发送密话请求。如果发送失败，通知用户密话失败
     **********************************************************************************/
    pstKsNegoCtx->ucCallId       = aucCallIds[0];
    pstKsNegoCtx->enEccVoiceType = pstAppEncVoiceReq->enEccVoiceType;

    PS_MEM_CPY(&pstKsNegoCtx->stCallNum,
               &pstAppEncVoiceReq->stDialNumber,
               sizeof(TAF_ECC_CALL_BCD_NUM_STRU));

    enEncVoiceSendRslt = TAF_XCALL_SendKmcKeyReqMsg(pstKsNegoCtx);

    if (TAF_CALL_APP_ENCRYPT_VOICE_SUCC != enEncVoiceSendRslt)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl,
                                        enEncVoiceSendRslt);

        /* 清除之前保存的KEY协商的上下文信息 */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /***********************************************************************************
     * 保存密话请求类型以及对端号码, 通知用户密话请求成功，状态迁移到等待KMC密话回复
     **********************************************************************************/
    TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_SUCC);

    TAF_XCALL_StartTimer(TI_TAF_XCALL_TX01_TIMER, TI_TAF_XCALL_TX01_LEN, 0);

    pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncKmcKeyRsp
 功能描述  : 处理KMC下发的MT密钥响应事件
 输入参数  : *pMsg        -- 事件对应的消息内容
             pKmcDecMsg   -- KMC解码消息
             pstKsNegoCtx -- 密话上下文信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncKmcKeyRsp(
    XSMS_XCALL_KMC_MSG_RCV_IND_STRU    *pstXsmsRcvInd,
    TAF_XCALL_KMC_MSG_STRU             *pKmcDecMsg,
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx
)
{
    TAF_XCALL_CIPHER_DECRYPTION_STRU    stDecryption;

    /***********************************************************************************************
     * 如果当前不是在等待KMC的密话响应时，不处理该消息
     **********************************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP != pstKsNegoCtx->enVoiceEncState)
    {
        return;
    }

    /* 停止可能相关的密话定时器 */
    TAF_XCALL_StopTimer(TI_TAF_XCALL_TX01_TIMER, 0);

    /***********************************************************************************************
     * 若收到的短信错误，则启动密话建立失败提示
     **********************************************************************************************/

    if (TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS != pKmcDecMsg->enRslt)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_MSG_DECODE_FAILUE,
                                       VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /***********************************************************************************************
     * 对密话RSP信息进行签名验证，验证失败，通知用户密话失败
     **********************************************************************************************/
    if (VOS_FALSE == TAF_XCALL_VerifySignature(TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN,
                                               &(TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber()->aucPubKey[0]),
                                               pKmcDecMsg->u.stKeyRsp.stSignInfo.ucSignInfoLen,
                                               &(pKmcDecMsg->u.stKeyRsp.stSignInfo.aucSignInfo[0]),
                                               (TAF_XCALL_KMC_MSG_HEADER_LEN + (VOS_UINT8)(pKmcDecMsg->u.stKeyRsp.stCipher.usCipherLen) + 1),
                                               &(pstXsmsRcvInd->aucData[0])))
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_SIGNTURE_VERIFY_FAILURE,
                                       VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /***********************************************************************************************
     * 获取密话KS信息
     **********************************************************************************************/
    PS_MEM_SET(&stDecryption, 0, sizeof(TAF_XCALL_CIPHER_DECRYPTION_STRU));

    stDecryption.ucCipherKeyLen  = pstKsNegoCtx->stTmpPrivKey.ucKeyLen;
    PS_MEM_CPY(&stDecryption.aucCipherKey[0],
               &pstKsNegoCtx->stTmpPrivKey.aucKey[0],
               sizeof(VOS_UINT8) * TAF_XCALL_KMC_MSG_MAX_KMC_PRIV_KEY_LEN);

    stDecryption.ucCipherDataLen = (VOS_UINT8)pKmcDecMsg->u.stKeyRsp.stCipher.usCipherLen;
    PS_MEM_CPY(&stDecryption.aucCipherData[0],
               &pKmcDecMsg->u.stKeyRsp.stCipher.aucCipher[0],
               sizeof(VOS_UINT8) * TAF_XCALL_KMC_MSG_MAX_CIPHER_LEN);

    stDecryption.ucPlainDataLen  = TAF_XCALL_ECC_KS_DATA_MAX_LEN;
    stDecryption.pucPlainData    = &pstKsNegoCtx->stKsInfo.aucKs[0];

    if (VOS_FALSE == TAF_XCALL_CipherDecrypt(&stDecryption))
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_DECRYPT_KS_FAILURE,
                                       VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }
    /* 成功后，更新密钥长度 */
    pstKsNegoCtx->stKsInfo.ucKsLen = stDecryption.ucEncrptionLen;

    PS_MEM_SET(&pstKsNegoCtx->stTmpPrivKey, 0, sizeof(TAF_XCALL_KMC_PRIV_KEY_STRU));
    PS_MEM_SET(&pstKsNegoCtx->stTmpPubKey,  0, sizeof(TAF_XCALL_KMC_PUB_KEY_STRU));

    /***********************************************************************************************
     * 进行密话SO协商，状态迁移到等待SO协商确认
     **********************************************************************************************/
    TAF_XCALL_SendEccServiceReq();

    /* 启动可能相关的密话定时器 */
    TAF_XCALL_StartTimer(TI_TAF_XCALL_TX02_TIMER, TI_TAF_XCALL_TX02_LEN, 0);

    pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ECC_SERVICE_CNF;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventAppEncVoiceReq
 功能描述  : 处理用户下发的密话请求
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventAppEncVoiceReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                    *pstAppEncVoiceReq = VOS_NULL_PTR;
    TAF_XCALL_ECC_SRV_CAP_INFO_STRU                        *pstEccSrvCap      = VOS_NULL_PTR;
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx      = VOS_NULL_PTR;

    pstAppEncVoiceReq = (TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU *)pMsg;

    /***********************************************************************************************
     * 检查当前语音加密业务能力，如果能力参数不支持或语音业务关闭，则拒绝语音呼叫
     **********************************************************************************************/
    pstEccSrvCap = TAF_XCALL_GetVoiceEncryptCapCfgPara();

    if ((VOS_FALSE == pstEccSrvCap->ucEccSrvCap)
     || (VOS_FALSE == pstEccSrvCap->ucEccSrvStatus))
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_ECC_CAP_NOT_SUPPORTED);

        return;
    }

    /***********************************************************************************************
     * 如果当前密话状态不在inactive状态，则有密话操作正在进行，拒绝当前的密话请求
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    switch (pstAppEncVoiceReq->enEccVoiceType)
    {
        case TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_AUTO_MODE:
            TAF_XCALL_ProcMtAutoModeVoiceEncReq(pstKsNegoCtx, pstAppEncVoiceReq);
            break;

        case TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_AUTO_MODE:
            TAF_XCALL_ProcMoAutoModeVoiceEncReq(pstKsNegoCtx, pstAppEncVoiceReq);
            break;

        case TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_MUNAUL_MODE:
            TAF_XCALL_ProcMoManualModeVoiceEncReq(pstKsNegoCtx, pstAppEncVoiceReq);
            break;

        case TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_MUNAUL_MODE:
            TAF_XCALL_ProcMtManualModeVoiceEncReq(pstKsNegoCtx, pstAppEncVoiceReq);
            break;

        default:
            TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_MODE_UNKNOWN);
            break;
    }
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventAppOrigReq
 功能描述  : 处理用户下发的呼叫请求事件
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : l00359089
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventAppOrigReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx      = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU                             *pstXcallEntity    = VOS_NULL_PTR;
    VOS_UINT32                                              ulCallIdNum;
    VOS_UINT8                                               aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    /* 如果当前状态不是WAITING_ORIG_REQ，不需要处理 */
    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ORIG_REQ != pstKsNegoCtx->enVoiceEncState)
    {
        return;
    }

    /* 停止定时器 */
    TAF_XCALL_StopTimer(TI_TAF_XCALL_VOICE_ENCRYPT_WAIT_ORIG_REQ_TIMER, 0);

    ulCallIdNum = TAF_XCALL_GetAllUsedCallId(&aucCallIds[0]);

    /***********************************************************************************
     * 如果存在两路呼叫或无呼叫存在，拒绝密话请求
     **********************************************************************************/
    if (TAF_XCALL_CALL_ENTITY_MAX_NUM == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                        TAT_CALL_APP_ENCRYPT_VOICE_TWO_CALL_ENTITY_EXIST,
                                        VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /***********************************************************************************
     * 如果无呼叫存在，拒绝密话请求
     **********************************************************************************/
    if (0 == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                        TAF_CALL_APP_ENCRYPT_VOICE_NO_CALL_EXIST,
                                        VOS_NULL_PTR);
        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    pstXcallEntity = TAF_XCALL_GetCallEntityAddr(aucCallIds[0]);

    if (VOS_TRUE == TAF_XCALL_IsEncVoiceNumberSameAsCallNumber(pstXcallEntity->stCalledNumber.ucNumLen,
                                                               &(pstXcallEntity->stCalledNumber.aucBcdNum[0]),
                                                               &pstKsNegoCtx->stCallNum))
    {
        /* 保存呼叫的callId标识 */
        pstKsNegoCtx->ucCallId        = aucCallIds[0];

        /*号码一致，状态迁移*/
        pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_TCH_ASSIGN_CMPL;
    }
    else
    {
        /*号码不一致，上报密话请求失败*/
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                        TAF_CALL_APP_ENCRYPT_VOICE_CALL_NUM_MISMATCH,
                                        VOS_NULL_PTR);
        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();
    }
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventAppHangUpReq
 功能描述  : 处理用户下发的挂机事件
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventAppHangUpReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx      = VOS_NULL_PTR;

    /***********************************************************************************************
     * 如果当前存在密话请求处理，包括网络的密话指示，则通知用户密话失败，原因是呼叫释放
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_CALL_RELEASED,
                                       VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();
    }
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventKmcMoKeyRsp
 功能描述  : 处理KMC下发的MO密钥响应事件
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventKmcMoKeyRsp(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx   = VOS_NULL_PTR;

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    /***********************************************************************************************
     * 如果收到的密话消息类型当前密话类型不一致，提示密话失败
     **********************************************************************************************/
    if ((TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_MUNAUL_MODE != pstKsNegoCtx->enEccVoiceType)
     && (TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_AUTO_MODE   != pstKsNegoCtx->enEccVoiceType))
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_MODE_MIMATCH,
                                       VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    TAF_XCALL_ProcVoiceEncKmcKeyRsp((XSMS_XCALL_KMC_MSG_RCV_IND_STRU *)pMsg,
                                    (TAF_XCALL_KMC_MSG_STRU *)pKmcDecMsg,
                                    pstKsNegoCtx);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventKmcMtKeyRsp
 功能描述  : 处理KMC下发的MT密钥响应事件
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventKmcMtKeyRsp(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx   = VOS_NULL_PTR;

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    /***********************************************************************************************
     * 如果收到的密话消息类型当前密话类型不一致，提示密话失败
     **********************************************************************************************/
    if ((TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_MUNAUL_MODE != pstKsNegoCtx->enEccVoiceType)
     && (TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_AUTO_MODE   != pstKsNegoCtx->enEccVoiceType))
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_MODE_MIMATCH,
                                       VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    TAF_XCALL_ProcVoiceEncKmcKeyRsp((XSMS_XCALL_KMC_MSG_RCV_IND_STRU *)pMsg,
                                    (TAF_XCALL_KMC_MSG_STRU *)pKmcDecMsg,
                                    pstKsNegoCtx);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventKmcMtEncryptInd
 功能描述  : 处理KMC下发的MT密钥指示事件
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventKmcMtEncryptInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_ECC_SRV_CAP_INFO_STRU    *pstEccSrvCap  = VOS_NULL_PTR;
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg     = VOS_NULL_PTR;
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx  = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    VOS_UINT32                          ulCallIdNum;

    /***********************************************************************************************
     * 如果当前UE不支持密话能力或密话关闭，忽略密话指示
     **********************************************************************************************/
    pstEccSrvCap = TAF_XCALL_GetVoiceEncryptCapCfgPara();

    if (VOS_FALSE == pstEccSrvCap->ucEccSrvStatus)
    {
        return;
    }

    /***********************************************************************************************
     * 消息解码失败，忽略密话指示
     **********************************************************************************************/
    pstKmcMsg = (TAF_XCALL_KMC_MSG_STRU *)pKmcDecMsg;

    if (TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS != pstKmcMsg->enRslt)
    {
        return;
    }

    /***********************************************************************************************
     * 如果当前已经存在密话请求，则忽略该密话指示
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != pstKsNegoCtx->enVoiceEncState)
    {
        return;
    }

    /***********************************************************************************
     * 如果存在两路呼叫或无呼叫存在，忽略密话指示
     **********************************************************************************/
    PS_MEM_SET(&aucCallIds[0], 0, sizeof(aucCallIds));

    ulCallIdNum = TAF_XCALL_GetAllUsedCallId(&aucCallIds[0]);

    if ((0                             == ulCallIdNum)
     || (TAF_XCALL_CALL_ENTITY_MAX_NUM == ulCallIdNum))
    {
        return;
    }

    /***********************************************************************************************
     * 如果当前不存在MT被叫，则忽略密话指示
     **********************************************************************************************/
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(aucCallIds[0]);

    if (MN_CALL_DIR_MT != pstCallEntity->enCallDir)
    {
        return;
    }

    /***********************************************************************************************
     * 如果被叫状态不在incoming或active状态，则忽略密话指示
     **********************************************************************************************/
    if ((MN_CALL_S_INCOMING != pstCallEntity->enCallState)
     && (MN_CALL_S_ACTIVE   != pstCallEntity->enCallState))
    {
        return;
    }

    /***********************************************************************************************
     * 转换密话指示中的号码，按本地BCD码格式保存
     **********************************************************************************************/
    pstKsNegoCtx->stCallNum.ucNumLen = TAF_XCALL_ConvertRemoteNumFromKmcBcdToStdBcd(pstKmcMsg->u.stMtEncryptInd.aucRemoteNumber,
                                                                                    pstKmcMsg->u.stMtEncryptInd.ucRemoteNumberLen,
                                                                                    pstKsNegoCtx->stCallNum.aucBcdNum,
                                                                                    TAF_ECC_CALL_MAX_BCD_NUM_LEN);

    /***********************************************************************************************
     * 检查密话号码与呼叫实体号码是否一致
     **********************************************************************************************/
    /* 如果主叫号码(即对端号码)存在时，才进行号码比较 */
    if (VOS_TRUE == TAF_XCALL_IsCallingNumExist(pstCallEntity))
    {
        if (VOS_FALSE == TAF_XCALL_IsEncVoiceNumberSameAsCallNumber(pstCallEntity->stCallNumber.ucNumLen,
                                                                    &pstCallEntity->stCallNumber.aucBcdNum[0],
                                                                    &(pstKsNegoCtx->stCallNum)))
        {
            /* 密话指示中的号码与主叫方号码不一致，忽略该密话指示 */
            TAF_XCALL_ExitVoiceEncriptProcedure();

            return;
        }
    }


    /***********************************************************************************************
     * 通知用户，有个被叫密话
     **********************************************************************************************/
    TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                   TAF_CALL_APP_ENCRYPT_VOICE_MT_CALL_NOTIFICATION,
                                   &pstKsNegoCtx->stCallNum);

    pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_AP_ENCRYPT_REQ;
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventKmcErrInd
 功能描述  : 处理KMC下发的MT密钥响应事件
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventKmcErrInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx = VOS_NULL_PTR;
    TAF_XCALL_KMC_MSG_STRU                                 *pstKmcMsg    = VOS_NULL_PTR;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEncVoiceErrCause;


    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    /***********************************************************************************************
     * 如果当前不是在等待KMC的密话响应时，直接返回
     **********************************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP != pstKsNegoCtx->enVoiceEncState)
    {
        return;
    }

    /***********************************************************************************************
     * 转换失败原因值，通知用户密话失败，停止相关定时器
     **********************************************************************************************/
    pstKmcMsg = (TAF_XCALL_KMC_MSG_STRU *)pKmcDecMsg;

    switch (pstKmcMsg->u.stErrInd.enErrCause)
    {
        case TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_LOCAL_NO_PERMISSION:
            enEncVoiceErrCause = TAF_CALL_APP_ENCRYPT_VOICE_LOCAL_TERMINAL_NO_AUTHORITY;
            break;

        case TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_REMOTE_NO_PERMISSION:
            enEncVoiceErrCause = TAF_CALL_APP_ENCRYPT_VOICE_REMOTE_TERMINAL_NO_AUTHORITY;
            break;

        case TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_LOCAL_ILLEGAL:
            enEncVoiceErrCause = TAF_CALL_APP_ENCRYPT_VOICE_LOCAL_TERMINAL_ILLEGAL;
            break;

        case TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_REMOTE_ILLEGAL:
            enEncVoiceErrCause = TAF_CALL_APP_ENCRYPT_VOICE_REMOTE_TERMINAL_ILLEGAL;
            break;

        case TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_ESTABLISH_TIME_OUT:
            enEncVoiceErrCause = TAF_CALL_APP_ENCRYPT_VOICE_TIMEOUT;
            break;

        default:
            enEncVoiceErrCause = TAF_CALL_APP_ENCRYPT_VOICE_UNKNOWN_ERROR;
            break;
    }

    TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                   enEncVoiceErrCause,
                                   VOS_NULL_PTR);

    /* 退出密话流程 */
    TAF_XCALL_ExitVoiceEncriptProcedure();
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventIncomingCallInd
 功能描述  : 处理XCC的被叫指示
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventIncomingCallInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx = VOS_NULL_PTR;

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    /***********************************************************************************************
     * 解决冲突场景: 密话命令已经收到，但还未收到用户的主叫请求命令，此时如果收到被叫，拒绝当前密话，
     * 接通被叫
     **********************************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_FAILURE_CAUSED_BY_INCOMING_CALL,
                                       VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();
    }
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventXccDiscInd
 功能描述  : 处理收到XCC电话断开指示
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventXccDiscInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx      = VOS_NULL_PTR;

    /***********************************************************************************************
     * 如果当前存在密话请求处理，包括网络的密话指示，则通知用户密话失败，原因是呼叫释放
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_CALL_RELEASED,
                                       VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();
    }
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventXccTchAssignCmplInd
 功能描述  : 处理收到XCC TCH指派完成指示
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventXccTchAssignCmplInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx = VOS_NULL_PTR;

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    /***********************************************************************************************
     * 如果当前密话请求状态不在等待TCH指派指示状态，直接返回；
     **********************************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_TCH_ASSIGN_CMPL != pstKsNegoCtx->enVoiceEncState)
    {
        return;
    }

    /***********************************************************************************************
     * 当前状态为等待TCH指派指示状态，则启动密话请求延时发送定时器，状态迁移到延时等待密话请求发送状
     * 态
     **********************************************************************************************/
    TAF_XCALL_StartTimer(TI_TAF_XCALL_DELAY_SEND_ENCRYPT_REQ,
                         TAF_XCALL_GetVoiceEncryptReqDelaySendTimerLen() * 1000,
                         0);

    /* 迁移状态到TAF_XCALL_VOICE_ENCRYPT_STA_DELAY_SEND_ENCRYPT_REQ */
    pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_DELAY_SEND_ENCRYPT_REQ;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventXccEccServiceCnf
 功能描述  : 处理收到XCC ECC SO确认消息
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventXccEccServiceCnf(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    XCC_XCALL_ECC_SERVICE_CNF_STRU     *pstEccSrvCnf = VOS_NULL_PTR;
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulCallDir;

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    pstEccSrvCnf = (XCC_XCALL_ECC_SERVICE_CNF_STRU *)pMsg;

    /***********************************************************************************************
     * 如果当前密话请求状态不在等待ECC_SERVICE_CNF，直接返回
     **********************************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ECC_SERVICE_CNF != pstKsNegoCtx->enVoiceEncState)
    {
        return;
    }

    /***********************************************************************************************
     * 如果业务协商不成功，则通知用户呼叫失败
     **********************************************************************************************/
    /* 停止TX02定时器 */
    TAF_XCALL_StopTimer(TI_TAF_XCALL_TX02_TIMER, 0);

    if (XCC_XCALL_ECC_SERVICE_RESULT_SUCC != pstEccSrvCnf->enRslt)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_SO_NEGO_FAILURE,
                                       VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /***********************************************************************************************
     * 调用加解密之前，必须先调用voice初始化函数。
     * outgoingcall，表示本次密话中终端是否是主叫，1 为主叫，0 为被叫。
     **********************************************************************************************/
    if ((TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_MUNAUL_MODE == pstKsNegoCtx->enEccVoiceType)
     || (TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_AUTO_MODE   == pstKsNegoCtx->enEccVoiceType))
    {
        ulCallDir = VOS_TRUE;
    }
    else
    {
        ulCallDir = VOS_FALSE;
    }

    if (VOS_FALSE == TAF_XCALL_CipherInitVoice(&pstKsNegoCtx->stKsInfo.aucKs[0], ulCallDir))
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_INIT_VOICE_FUNC_FAILURE,
                                       VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /***********************************************************************************************
     * 终端收到的会话密钥 Ks、产生的临时公私钥对在使用结束后，应立即删除且内容不可
    *  恢复（如置0）。
     **********************************************************************************************/
    PS_MEM_SET(&pstKsNegoCtx->stKsInfo, 0, sizeof(TAF_XCALL_KS_INFO_STRU));

    TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                   TAF_CALL_APP_ENCRYPT_VOICE_SUCC,
                                   VOS_NULL_PTR);

    TAF_XCALL_SendCttf1xMacEncryptVoiceNtf(MACITF_1X_ECC_VOICE_ENCRYPT_TYPE);

    /* 迁移状态到TAF_XCALL_VOICE_ENCRYPT_STA_ENCRYPT_ACTIVE */
    pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_ENCRYPT_ACTIVE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventXccAnswerCnf
 功能描述  : 处理收到XCC被叫接听应答消息
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventXccAnswerCnf(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    XCC_XCALL_ANSWER_CALL_CNF_STRU                         *pstAnswerCallCnf = VOS_NULL_PTR;
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx     = VOS_NULL_PTR;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enSendRslt;

    pstAnswerCallCnf = (XCC_XCALL_ANSWER_CALL_CNF_STRU *)pMsg;

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    /***********************************************************************************************
     * 如果当前密话请求状态不在等待密话接受请求状态，直接退出
     **********************************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_WATIING_CALL_ACCEPT_REQ != pstKsNegoCtx->enVoiceEncState)
    {
        return;
    }

    /***********************************************************************************************
     * 如果接听失败，则通知用户密话失败，原因值为呼叫接听失败
     **********************************************************************************************/
    if (TAF_XCC_CAUSE_SUCCESS != pstAnswerCallCnf->enCause)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_CALL_ANSWER_REQ_FAILURE,
                                       VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /***********************************************************************************************
     * 发送KMC密话请求，如果发送失败，通知用户，密话请求失败，否则启动TX01定时器，并迁移状态
     **********************************************************************************************/
    /* 保存call ID信息 */
    pstKsNegoCtx->ucCallId = pstAnswerCallCnf->ucCallId;

    enSendRslt = TAF_XCALL_SendKmcKeyReqMsg(pstKsNegoCtx);

    if (TAF_CALL_APP_ENCRYPT_VOICE_SUCC != enSendRslt)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       enSendRslt,
                                       VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /* 启动TX01定时器 */
    TAF_XCALL_StartTimer(TI_TAF_XCALL_TX01_TIMER, TI_TAF_XCALL_TX01_LEN, 0);

    /* 迁移状态到TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP */
    pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP;

}


/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventXsmsSendCnf
 功能描述  : 处理收到XSMS密话请求发送确认消息
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventXsmsSendCnf(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx   = VOS_NULL_PTR;
    XSMS_XCALL_KMC_MSG_SEND_CNF_STRU                       *pstXsmsSendCnf = VOS_NULL_PTR;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEncVoiceStatus;

    pstXsmsSendCnf = (XSMS_XCALL_KMC_MSG_SEND_CNF_STRU *)pMsg;

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    /***********************************************************************************************
     * 如果当前密话请求状态不在等待密话reponse状态，直接退出
     **********************************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP != pstKsNegoCtx->enVoiceEncState)
    {
        return;
    }

    /***********************************************************************************************
     * 如果当前密话请求消息发送成功，则不作任何操作，继续等待KMC的响应
     **********************************************************************************************/
    if (XSMS_XCALL_SEND_RESULT_SUCC == pstXsmsSendCnf->enRslt)
    {
        return;
    }

    /***********************************************************************************************
     * 如果当前密话请求消息发送失败，根据XSMS上报的原因值，通知用户密话失败
     **********************************************************************************************/
    switch (pstXsmsSendCnf->enRslt)
    {
        case XSMS_XCALL_SEND_RESULT_FAIL:
            enEncVoiceStatus = TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_FAIL;
            break;

        case XSMS_XCALL_SEND_RESULT_POOL_FULL:
            enEncVoiceStatus = TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_POOL_FULL;
            break;

        case XSMS_XCALL_SEND_RESULT_LINK_ERR:
            enEncVoiceStatus = TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_LINK_ERR;
            break;

        case XSMS_XCALL_SEND_RESULT_NO_TL_ACK:
            enEncVoiceStatus = TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_NO_TL_ACK;
            break;

        case XSMS_XCALL_SEND_RESULT_ENCODE_ERR:
            enEncVoiceStatus = TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_ENCODE_ERR;
            break;

        default:
            enEncVoiceStatus = TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_UNKNOWN;
            break;
    }

    TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                   enEncVoiceStatus,
                                   VOS_NULL_PTR);

    /* 退出密话流程 */
    TAF_XCALL_ExitVoiceEncriptProcedure();
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventTimerWaitOrigReq
 功能描述  : 处理等待ORIG请求时，定时器超时
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventTimerWaitOrigReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx      = VOS_NULL_PTR;

    /***********************************************************************************************
     * 如果当前正在等待呼叫请求时，等待orig req超时，则通知应用密话请求超时
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ORIG_REQ == pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_TIMEOUT,
                                       VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();
    }
}


/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventTimerDelaySendEncReq
 功能描述  : 处理延时密话请求发送时，定时器超时
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventTimerDelaySendEncReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx = VOS_NULL_PTR;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enSendRslt;

    /***********************************************************************************************
     * 如果当前状态是密话请求延时发送状态，则发送密话请求，发送成功，启动TX01定时器，状态迁移到
     * 等待密话请求响应状态
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    if (TAF_XCALL_VOICE_ENCRYPT_STA_DELAY_SEND_ENCRYPT_REQ == pstKsNegoCtx->enVoiceEncState)
    {
        enSendRslt = TAF_XCALL_SendKmcKeyReqMsg(pstKsNegoCtx);

        if (TAF_CALL_APP_ENCRYPT_VOICE_SUCC != enSendRslt)
        {
            TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                           enSendRslt,
                                           VOS_NULL_PTR);

            /* 退出密话流程 */
            TAF_XCALL_ExitVoiceEncriptProcedure();

            return;
        }

        /* 启动TX01定时器 */
        TAF_XCALL_StartTimer(TI_TAF_XCALL_TX01_TIMER, TI_TAF_XCALL_T301_LEN, 0);

        /* 迁移状态到TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP */
        pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP;
    }
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventTimerTx01
 功能描述  : 处理TX01定时器超时事件
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventTimerTx01(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx      = VOS_NULL_PTR;

    /***********************************************************************************************
     * 如果当前正在等待密话响应状态，收到TX01定时器时，通知应用密话超时，释放密话上下文信息
     * 其他状态不处理
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP == pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_TX01_TIMEOUT,
                                       VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();
    }
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventTimerTx02
 功能描述  : 处理TX02定时器超时事件
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventTimerTx02(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx      = VOS_NULL_PTR;

    /***********************************************************************************************
     * 如果当前正在等待ECC SERVICE CNF状态，收到TX02定时器时，通知应用密话超时，释放密话上下文信息
     * 其他状态不处理
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ECC_SERVICE_CNF == pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_TX02_TIMEOUT,
                                       VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();
    }
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcVoiceEncEventIntCallRelInd
 功能描述  : 处理内部造成的呼叫释放
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventIntCallRelInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx      = VOS_NULL_PTR;

    /***********************************************************************************************
     * 如果当前存在密话请求处理，包括网络的密话指示，则通知用户密话失败，原因是呼叫释放
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_CALL_RELEASED,
                                       VOS_NULL_PTR);

        /* 退出密话流程 */
        TAF_XCALL_ExitVoiceEncriptProcedure();
    }
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcPubKeyEventKmcUpdateInd
 功能描述  : 处理KMC的公钥更新请求消息
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : l00359089
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcPubKeyEventKmcUpdateInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KMC_MSG_STRU                                  stKmcSndMsg;
    TAF_XCALL_KMC_MSG_STRU                                 *pstKmcMsg          = VOS_NULL_PTR;
    TAF_XCALL_ECC_PUB_KEY_INFO_STRU                        *pstEccPubKeyInfo   = VOS_NULL_PTR;
    TAF_XCALL_PUBLIC_KEY_UPDATE_CTX                        *pstPubKeyUpdateCtx = VOS_NULL_PTR;
    XSMS_XCALL_KMC_MSG_RCV_IND_STRU                        *pstXsmsRcvInd      = VOS_NULL_PTR;
    VOS_UINT8                                               ucWaitSignLen;

    pstXsmsRcvInd   = (XSMS_XCALL_KMC_MSG_RCV_IND_STRU *)pMsg;

    /***********************************************************************************************
     * 消息解码失败，忽略该消息
     **********************************************************************************************/
    pstKmcMsg       = (TAF_XCALL_KMC_MSG_STRU *)pKmcDecMsg;

    if (TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS != pstKmcMsg->enRslt)
    {
        return;
    }

    pstPubKeyUpdateCtx = TAF_XCALL_GetPubKeyUpdateCtxAddr();
    /***********************************************************************************************
     * 若当前状态不是未激活状态，说明此时正有更新流程在执行，则丢弃新的消息
     **********************************************************************************************/
    if (TAF_XCALL_K0_UPATE_STA_INACTIVE != pstPubKeyUpdateCtx->enK0UpdateState)
    {
        return;
    }

    /***********************************************************************************************
     * 若当前状态是未激活状态，此时需要判断消息中的版本号和终端当前的版本号是否一致，一致的话不处理
     **********************************************************************************************/
    /* 获取本地存储的公钥 */
    pstEccPubKeyInfo = TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber();

    if ((pstEccPubKeyInfo->ucVerNum == pstKmcMsg->u.stPubKeyUpdateInd.ucKeyVersion))
    {
        return;
    }

    /* 签名验证 */
    ucWaitSignLen = pstKmcMsg->u.stPubKeyUpdateInd.stPubKey.ucKeyLen + TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_REQ_HEADER_LEN;

    if (VOS_FALSE == TAF_XCALL_VerifySignature(TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN,
                                               &pstEccPubKeyInfo->aucPubKey[0],
                                               pstKmcMsg->u.stPubKeyUpdateInd.stSignInfo.ucSignInfoLen,
                                               &(pstKmcMsg->u.stPubKeyUpdateInd.stSignInfo.aucSignInfo[0]),
                                               ucWaitSignLen,
                                               &(pstXsmsRcvInd->aucData[0])))
    {
        /*签名验证失败*/
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_XCALL_ProcPubKeyEventKmcUpdateInd: signature verify is failure!");

        return;
    }

    /***********************************************************************************
    * 获取消息发送opId, 签名验证成功，发送更新响应消息
    **********************************************************************************/
    pstPubKeyUpdateCtx->usWaitXsmsCnfOpId = TAF_XCALL_GetSendXsmsReqOpId();

    PS_MEM_SET(&stKmcSndMsg, 0, sizeof(TAF_XCALL_KMC_MSG_STRU));

    if (VOS_TRUE != TAF_XCALL_SendKmcUpdateRspMsg(pstPubKeyUpdateCtx->usWaitXsmsCnfOpId, &stKmcSndMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_XCALL_ProcPubKeyEventKmcUpdateInd: send KMC UPDATE RSP failure!");

        return;
    }

    /***********************************************************************************
    * 状态迁移到 等待KMC公钥更新确认
    **********************************************************************************/
    pstPubKeyUpdateCtx->enK0UpdateState = TAF_XCALL_K0_UPATE_STA_WAIT_KMC_RSP;

    /*将KMC公钥,版本号,随机数保存*/
    pstPubKeyUpdateCtx->ucPubKeyVerNum = pstKmcMsg->u.stPubKeyUpdateInd.ucKeyVersion;
    PS_MEM_CPY(pstPubKeyUpdateCtx->aucPubKey,
               pstKmcMsg->u.stPubKeyUpdateInd.stPubKey.aucKey,
               TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN);

    PS_MEM_CPY(pstPubKeyUpdateCtx->aucRandomData,
                stKmcSndMsg.u.stPubKeyUpdateRsp.aucRandomData,
                TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN);

    /* 启动等待公钥更新确认消息定时器 */
    TAF_XCALL_StartTimer(TI_TAF_XCALL_PUB_KEY_UPDATE_WAIT_ACK_TIMER, TI_TAF_XCALL_PUB_KEY_UPDATE_WAIT_ACK_LEN, 0);
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcPubKeyEventKmcUpdateAck
 功能描述  : 处理KMC的公钥更新确认消息
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : l00359089
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcPubKeyEventKmcUpdateAck(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KMC_MSG_STRU                                 *pstKmcMsg       = VOS_NULL_PTR;
    TAF_XCALL_PUBLIC_KEY_UPDATE_CTX                        *pstPubKeyUpdateCtx = VOS_NULL_PTR;
    TAF_XCALL_ECC_PUB_KEY_INFO_STRU                        *pstEccPubKeyInfo   = VOS_NULL_PTR;

    pstKmcMsg          = (TAF_XCALL_KMC_MSG_STRU *)pKmcDecMsg;
    pstPubKeyUpdateCtx = TAF_XCALL_GetPubKeyUpdateCtxAddr();

    /***********************************************************************************
    * 状态不是 等待KMC公钥更新确认，说明此时没有等待更新确认，不予处理
    **********************************************************************************/
    if (TAF_XCALL_K0_UPATE_STA_WAIT_KMC_RSP !=pstPubKeyUpdateCtx->enK0UpdateState )
    {
        return;
    }

    /***********************************************************************************************
     * 如果消息解码失败，退出流程
     **********************************************************************************************/
    if (TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS != pstKmcMsg->enRslt)
    {
        TAF_XCALL_ExitPubKeyUpdateProcedure();
        return;
    }

    /***********************************************************************************
    * 收到消息中的随机数与本地存储的随机数不相等，退出流程
    **********************************************************************************/
    if (0 != PS_MEM_CMP(pstPubKeyUpdateCtx->aucRandomData, pstKmcMsg->u.stPubKeyUpdateAck.aucRandomData, TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN))
    {
        TAF_XCALL_ExitPubKeyUpdateProcedure();
        return;
    }

    /***********************************************************************************
    * 更新NV　和　密话相关的数据上下文中的公钥版本号和公钥
    **********************************************************************************/
    TAF_XCALL_WriteVoiceEncryptPublicKeyAndVersionNumber(pstPubKeyUpdateCtx->aucPubKey, pstPubKeyUpdateCtx->ucPubKeyVerNum);

    pstEccPubKeyInfo = TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber();
    PS_MEM_SET(pstEccPubKeyInfo, 0, sizeof(TAF_XCALL_ECC_PUB_KEY_INFO_STRU));
    pstEccPubKeyInfo->ucVerNum = pstPubKeyUpdateCtx->ucPubKeyVerNum;
    PS_MEM_CPY(pstEccPubKeyInfo->aucPubKey, pstPubKeyUpdateCtx->aucPubKey, sizeof(pstEccPubKeyInfo->aucPubKey));

    /***********************************************************************************
    * 清除之前保存的公钥更新流程中的上下文信息
    **********************************************************************************/
    TAF_XCALL_ExitPubKeyUpdateProcedure();
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcPubKeyEventXsmsSendCnf
 功能描述  : 处理公钥更新的确认消息发送确认结果消息
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : l00359089
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcPubKeyEventXsmsSendCnf(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    XSMS_XCALL_KMC_MSG_SEND_CNF_STRU   *pstXsmsSendCnf = VOS_NULL_PTR;

    pstXsmsSendCnf  = (XSMS_XCALL_KMC_MSG_SEND_CNF_STRU *)pMsg;

    /*OpId的比较已经在外部进行过了，此处不需要再比较*/

    /***********************************************************************************
    * 发送确认结果如果失败， 清除之前保存的KMC公钥更新的上下文信息；成功，什么也不做
    **********************************************************************************/
    if(XSMS_XCALL_SEND_RESULT_SUCC != pstXsmsSendCnf->enRslt)
    {
        TAF_XCALL_ExitPubKeyUpdateProcedure();
    }
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcRemoteCtrlEventAppRemoteCtrlAnswerReq
 功能描述  : 处理用户下发的远程控制应答请求消息
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcRemoteCtrlEventAppRemoteCtrlAnswerReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU               *pstAppRemoteAnswerReq = VOS_NULL_PTR;
    TAF_XCALL_REMOTE_CTRL_CTX                              *pstRemoteCtrlCtx      = VOS_NULL_PTR;
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_ENUM_UINT8       enRemoteCtrlRslt;
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM_UINT8       enRemoteCtrlType;

    pstAppRemoteAnswerReq = (TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU *)pMsg;

    pstRemoteCtrlCtx      = TAF_XCALL_GetRemoteCtrlCtxAddr();
    enRemoteCtrlRslt      = TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_BUTT;
    enRemoteCtrlType      = TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_BUTT;

    /* 停止远程控制AP应答定时器 */
    TAF_XCALL_StopTimer(TI_TAF_XCALL_REMOTE_CTRL_WAIT_AP_ANSWER_TIMER, 0);

    /* 异常处理 */
    switch (pstRemoteCtrlCtx->enRemoteCtrlState)
    {
        case TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_INFO_ERASE_RSP:
            {
                if (TAF_CALL_REMOTE_CTRL_SEC_INFO_ERASE != pstAppRemoteAnswerReq->enRemoteCtrlEvtType)
                {
                    TAF_XCALL_SndAppRemoteCtrlAnswerCnf(&pstAppRemoteAnswerReq->stCtrl, TAF_CALL_SEND_RESULT_OPER_TYPE_ERROR);

                    (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_SECURE_INFO_ERASE,
                                                                     TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_OTHER_FAILURE,
                                                                     pstRemoteCtrlCtx);

                    /* 异常，退出远程控制流程*/
                    TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

                    return;
                }

                enRemoteCtrlType    = TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_SECURE_INFO_ERASE;

                break;
            }
        case TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_PASSWORD_RESET_RSP:
            {
                if (TAF_CALL_REMOTE_CTRL_PASSWORD_RESET != pstAppRemoteAnswerReq->enRemoteCtrlEvtType)
                {
                    TAF_XCALL_SndAppRemoteCtrlAnswerCnf(&pstAppRemoteAnswerReq->stCtrl, TAF_CALL_SEND_RESULT_OPER_TYPE_ERROR);

                    (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_PWD_RESET,
                                                                     TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_OTHER_FAILURE,
                                                                     pstRemoteCtrlCtx);

                    /* 异常，退出远程控制流程*/
                    TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

                    return;
                }

                enRemoteCtrlType    = TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_PWD_RESET;

                break;
            }
        default:
            {
                TAF_XCALL_SndAppRemoteCtrlAnswerCnf(&pstAppRemoteAnswerReq->stCtrl, TAF_CALL_SEND_RESULT_OPER_NOT_ALLOWED);

                /* 异常，退出远程控制流程*/
                TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

                return;
            }
    }

    if (TAF_CALL_REMOTE_CTRL_APP_SUCC == pstAppRemoteAnswerReq->enResult)
    {
        enRemoteCtrlRslt    = TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_SUCCESS;

        /* SUCC设置对应命令类型，用于收到SMS确认时，刷新NV */
        pstRemoteCtrlCtx->enRemoteCtrlCmdType   = enRemoteCtrlType;
    }
    else
    {
        enRemoteCtrlRslt    = TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_OTHER_FAILURE;
    }

    if (VOS_FALSE == TAF_XCALL_SendRemoteCtrlEventRsltToKmc(enRemoteCtrlType,
                                                            enRemoteCtrlRslt,
                                                            pstRemoteCtrlCtx))
    {
        TAF_XCALL_SndAppRemoteCtrlAnswerCnf(&pstAppRemoteAnswerReq->stCtrl, TAF_CALL_SEND_RESULT_INT_ERRROR);

        /* 异常，退出远程控制流程*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    /* 复制Ctrl头，回复的时候使用 */
    PS_MEM_CPY(&(pstRemoteCtrlCtx->stCcaCtrl), &(pstAppRemoteAnswerReq->stCtrl), sizeof(TAF_CCA_CTRL_STRU));

    /* 设置状态 */
    pstRemoteCtrlCtx->enRemoteCtrlState = TAF_XCALL_REMOTE_CTRL_STA_WAITING_RSP_SENT_RSLT;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcRemoteCtrlEventKmcRemoteCtrlCmdInd
 功能描述  : 处理KMC下发的远程控制命令请求消息
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcRemoteCtrlEventKmcRemoteCtrlCmdInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KMC_MSG_STRU                                 *pstKmcMsg           = VOS_NULL_PTR;
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU             *pstRemoteCtrlInd    = VOS_NULL_PTR;
    TAF_XCALL_REMOTE_CTRL_CTX                              *pstRemoteCtrlCtx    = VOS_NULL_PTR;
    TAF_XCALL_ECC_PUB_KEY_INFO_STRU                        *pstPubKeyAndVer     = VOS_NULL_PTR;
    XSMS_XCALL_KMC_MSG_RCV_IND_STRU                        *pstXsmsRcvInd       = VOS_NULL_PTR;
    TAF_STD_TIME_ZONE_TYPE_STRU                            *pstLastSysTimeZone  = VOS_NULL_PTR;
    VOS_UINT8                                               aucSignData[TAF_XCALL_SIGN_DATA_INFO_MAX_LEN];
    TAF_XCALL_HARDWARE_ID_INFO_STRU                         stHardWareInfo;

    pstKmcMsg                           = (TAF_XCALL_KMC_MSG_STRU *)pKmcDecMsg;
    pstRemoteCtrlInd                    = (TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU *)(&(pstKmcMsg->u.stRemoteCtrlInd));
    pstXsmsRcvInd                       = (XSMS_XCALL_KMC_MSG_RCV_IND_STRU *)pMsg;
    pstRemoteCtrlCtx                    = TAF_XCALL_GetRemoteCtrlCtxAddr();
    pstPubKeyAndVer                     = TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber();

    PS_MEM_SET(aucSignData, 0x00, sizeof(aucSignData));
    PS_MEM_SET(&stHardWareInfo, 0x00, sizeof(TAF_XCALL_HARDWARE_ID_INFO_STRU));

    /* 状态检查 */
    if (TAF_XCALL_REMOTE_CTRL_STA_INACTIVE != pstRemoteCtrlCtx->enRemoteCtrlState)
    {
        /* 处于其他状态，说明正在处理其他流程，丢弃消息 */

        return;
    }

    /* 消息解码错误，不处理该消息 */
    if (TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS != pstKmcMsg->enRslt)
    {
        (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(pstRemoteCtrlInd->enRomoteCtrlCmdType,
                                                         TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_OTHER_FAILURE,
                                                         pstRemoteCtrlCtx);

        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    /* 公钥版本匹配 */
    if (pstPubKeyAndVer->ucVerNum != pstRemoteCtrlInd->ucKeyVersion)
    {
        /* 公钥版本不匹配 */
        (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(pstRemoteCtrlInd->enRomoteCtrlCmdType,
                                                         TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_KEY_VERSION_MISMATCH_FAILURE,
                                                         pstRemoteCtrlCtx);

        /* 异常，退出远程控制流程*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    /* 数据长度检查 */
    if (pstXsmsRcvInd->usDataLen < TAF_XCALL_SIGN_DATA_INFO_LEN)
    {
        /* 消息长度不匹配 */
        (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(pstRemoteCtrlInd->enRomoteCtrlCmdType,
                                                         TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_SIGN_VERIFY_FAILURE,
                                                         pstRemoteCtrlCtx);

        /* 异常，退出远程控制流程*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    PS_MEM_CPY(aucSignData,
               pstXsmsRcvInd + (sizeof(XSMS_XCALL_KMC_MSG_RCV_IND_STRU) - sizeof(pstXsmsRcvInd->aucData)),
               sizeof(VOS_UINT8) * TAF_XCALL_SIGN_DATA_INFO_LEN);

    if (VOS_FALSE == TAF_XCALL_GetHardWareInfo(&stHardWareInfo))
    {
        /* HardWare信息获取失败 */
        (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(pstRemoteCtrlInd->enRomoteCtrlCmdType,
                                                         TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_SIGN_VERIFY_FAILURE,
                                                         pstRemoteCtrlCtx);

        /* 异常，退出远程控制流程*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    aucSignData[TAF_XCALL_SIGN_DATA_INFO_LEN]       = TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN + 1;
    aucSignData[TAF_XCALL_SIGN_DATA_INFO_LEN + 1]   = (VOS_UINT8)stHardWareInfo.enHardWareType;

    PS_MEM_CPY(&(aucSignData[TAF_XCALL_SIGN_DATA_INFO_LEN + 2]),
                 stHardWareInfo.aucHardWareIdInfo,
                 sizeof(VOS_UINT8) * TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN);

    if (VOS_FALSE == TAF_XCALL_VerifySignature(TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN,
                                               &(pstPubKeyAndVer->aucPubKey[0]),
                                               pstRemoteCtrlInd->stSignInfo.ucSignInfoLen,
                                               &(pstRemoteCtrlInd->stSignInfo.aucSignInfo[0]),
                                               TAF_XCALL_SIGN_DATA_INFO_MAX_LEN,
                                               &(aucSignData[0])))
    {
        /* 签名验证失败 */
        (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(pstRemoteCtrlInd->enRomoteCtrlCmdType,
                                                         TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_SIGN_VERIFY_FAILURE,
                                                         pstRemoteCtrlCtx);

        /* 签名验证失败，退出远程控制流程*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    /* 获取记录的上一次操作的时间 */
    if (TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_SECURE_INFO_ERASE == pstRemoteCtrlInd->enRomoteCtrlCmdType)
    {
        pstLastSysTimeZone               = TAF_XCALL_GetVoiceEncryptSecInfoEraseSysTime();
    }
    else
    {
        pstLastSysTimeZone               = TAF_XCALL_GetVoiceEncryptPassWordResetSysTime();
    }

    /* 时间戳检查 */
    if (VOS_FALSE == TAF_XCALL_IsTimeStampValid(&(pstRemoteCtrlInd->stTimeStamp),
                                                  pstLastSysTimeZone))
    {
        /* 时间戳检查失败 */
        (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(pstRemoteCtrlInd->enRomoteCtrlCmdType,
                                                         TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_OTHER_FAILURE,
                                                         pstRemoteCtrlCtx);

        /* 条件不满足，退出远程控制流程*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    /* 保存时间戳 */
    pstRemoteCtrlCtx->stTimeStamp       = pstRemoteCtrlInd->stTimeStamp;

    /* INFO ERASE */
    if (TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_SECURE_INFO_ERASE == pstRemoteCtrlInd->enRomoteCtrlCmdType)
    {
        TAF_XCALL_SndAppRemoteCtrlInd(&(pstRemoteCtrlCtx->stCcaCtrl), TAF_CALL_REMOTE_CTRL_SEC_INFO_ERASE);

        pstRemoteCtrlCtx->enRemoteCtrlState     = TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_INFO_ERASE_RSP;
    }
    else
    {
        /* PASSWD RESET */
        TAF_XCALL_SndAppRemoteCtrlInd(&(pstRemoteCtrlCtx->stCcaCtrl), TAF_CALL_REMOTE_CTRL_PASSWORD_RESET);

        pstRemoteCtrlCtx->enRemoteCtrlState     = TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_PASSWORD_RESET_RSP;
    }

    /* 启动等待AP远程控制应答定时器 */
    TAF_XCALL_StartTimer(TI_TAF_XCALL_REMOTE_CTRL_WAIT_AP_ANSWER_TIMER,
                         TAF_XCALL_GetRemoteCtrlWaitApAnswerTimerLen() * 1000,
                         0);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcRemoteCtrlEventXsmsSendCnf
 功能描述  : 处理发送远程控制响应消息发送结果事件
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcRemoteCtrlEventXsmsSendCnf(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    XSMS_XCALL_KMC_MSG_SEND_CNF_STRU                       *pstKmcMsgCnf            = VOS_NULL_PTR;
    TAF_XCALL_REMOTE_CTRL_CTX                              *pstRemoteCtrlCtx        = VOS_NULL_PTR;
    TAF_STD_TIME_ZONE_TYPE_STRU                            *pstLastRecTime          = VOS_NULL_PTR;

    pstKmcMsgCnf                        = (XSMS_XCALL_KMC_MSG_SEND_CNF_STRU *)pMsg;
    pstRemoteCtrlCtx                    = TAF_XCALL_GetRemoteCtrlCtxAddr();

    /* 检查当前状态是否为WAITING RSP RSLT */
    if (TAF_XCALL_REMOTE_CTRL_STA_WAITING_RSP_SENT_RSLT != pstRemoteCtrlCtx->enRemoteCtrlState)
    {
        /* 当前处于其他状态，丢弃消息 */

        return;
    }

    /* 根据结果回复AT消息 */
    if (XSMS_XCALL_SEND_RESULT_SUCC != pstKmcMsgCnf->enRslt)
    {
        TAF_XCALL_SndAppRemoteCtrlAnswerCnf(&(pstRemoteCtrlCtx->stCcaCtrl),
                                           TAF_CALL_SEND_RESULT_FAIL);

        /* 完成远程控制流程，退出远程控制流程*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    TAF_XCALL_SndAppRemoteCtrlAnswerCnf(&(pstRemoteCtrlCtx->stCcaCtrl),
                                           TAF_CALL_SEND_RESULT_SUCC);

    /* Answer Req的Rslt为Fail,不刷新NV */
    if (TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_BUTT == pstRemoteCtrlCtx->enRemoteCtrlCmdType)
    {
        /* 完成远程控制流程，退出远程控制流程*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    /* 根据命令类型刷新NV和对应全局变量 */
    if (TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_SECURE_INFO_ERASE == pstRemoteCtrlCtx->enRemoteCtrlCmdType)
    {
        pstLastRecTime                  = TAF_XCALL_GetVoiceEncryptSecInfoEraseSysTime();

        /* 赋值全局变量 */
        pstLastRecTime->usYear          = pstRemoteCtrlCtx->stTimeStamp.usYear;
        pstLastRecTime->usMonth         = pstRemoteCtrlCtx->stTimeStamp.usMonth;
        pstLastRecTime->usDay           = pstRemoteCtrlCtx->stTimeStamp.usDay;
        pstLastRecTime->usHour          = pstRemoteCtrlCtx->stTimeStamp.usHour;
        pstLastRecTime->usMinute        = pstRemoteCtrlCtx->stTimeStamp.usMinute;
        pstLastRecTime->usSecond        = pstRemoteCtrlCtx->stTimeStamp.usSecond;

        /* 写入NV */
        TAF_XCALL_WriteVoiceEncryptSecInfoEraseSysTime(&(pstRemoteCtrlCtx->stTimeStamp));

        /* 完成远程控制流程，退出远程控制流程*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    pstLastRecTime                      = TAF_XCALL_GetVoiceEncryptPassWordResetSysTime();

    /* 赋值全局变量 */
    pstLastRecTime->usYear              = pstRemoteCtrlCtx->stTimeStamp.usYear;
    pstLastRecTime->usMonth             = pstRemoteCtrlCtx->stTimeStamp.usMonth;
    pstLastRecTime->usDay               = pstRemoteCtrlCtx->stTimeStamp.usDay;
    pstLastRecTime->usHour              = pstRemoteCtrlCtx->stTimeStamp.usHour;
    pstLastRecTime->usMinute            = pstRemoteCtrlCtx->stTimeStamp.usMinute;
    pstLastRecTime->usSecond            = pstRemoteCtrlCtx->stTimeStamp.usSecond;

    TAF_XCALL_WriteVoiceEncryptPassWordResetSysTime(&(pstRemoteCtrlCtx->stTimeStamp));

    /* 完成远程控制流程，退出远程控制流程*/
    TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcRemoteCtrlEventTimerWaitApAnswer
 功能描述  : 处理发送远程控制响应消息发送结果事件
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcRemoteCtrlEventTimerWaitApAnswer(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_REMOTE_CTRL_CTX          *pstRemoteCtrlCtx        = VOS_NULL_PTR;

    pstRemoteCtrlCtx = TAF_XCALL_GetRemoteCtrlCtxAddr();

    if ((TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_INFO_ERASE_RSP     != pstRemoteCtrlCtx->enRemoteCtrlState)
     && (TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_PASSWORD_RESET_RSP != pstRemoteCtrlCtx->enRemoteCtrlState))
    {
        return;
    }

    if (TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_INFO_ERASE_RSP == pstRemoteCtrlCtx->enRemoteCtrlState)
    {
        (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_SECURE_INFO_ERASE,
                                                         TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_OTHER_FAILURE,
                                                         pstRemoteCtrlCtx);
    }
    else
    {
        (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_PWD_RESET,
                                                         TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_OTHER_FAILURE,
                                                         pstRemoteCtrlCtx);
    }

    TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

    return;

}

/*****************************************************************************
 函 数 名  : TAF_XCALL_IsMkTimeParaValid
 功能描述  : 检查TimeZone结构体个成员数值是否符合MkTime函数的要求
 输入参数  : TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeZone 时间
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_TRUE:  有效
             VOS_FALSE: 无效
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_IsMkTimeParaValid(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeZone
)
{
    VOS_UINT8                           aucDaysOfMonth[TAF_XCALL_TIME_MONTHS_OF_ONE_YEAR] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    /* 年份[1900,3000] */
    if ((pstTimeZone->usYear < 1900)
     || (pstTimeZone->usYear > 3000))
    {
        return VOS_FALSE;
    }

    /* 月份[1,12] */
    if ((pstTimeZone->usMonth < 1)
     || (pstTimeZone->usMonth > 12))
    {
        return VOS_FALSE;
    }

    /* 如果是2月份，判断闰年后2月加一天 */
    if (2 == pstTimeZone->usMonth)
    {
        if (((0 == (pstTimeZone->usYear % 4))
          && (0 != (pstTimeZone->usYear % 100)))
          || (0 == (pstTimeZone->usYear % 400)))
        {
            aucDaysOfMonth[pstTimeZone->usMonth - 1]++;
        }
    }

    /* 日[1,31] */
    if ((pstTimeZone->usDay < 1)
     || (pstTimeZone->usDay > aucDaysOfMonth[pstTimeZone->usMonth - 1]))
    {
        return VOS_FALSE;
    }

    /* 小时[0,23] */
    if (pstTimeZone->usHour > 23)
    {
        return VOS_FALSE;
    }

    /* 分钟[0,59] */
    if (pstTimeZone->usMinute > 59)
    {
        return VOS_FALSE;
    }

    /* 分钟[0,59] */
    if (pstTimeZone->usSecond > 59)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetTimeIntervalSince1970
 功能描述  : 获取当前时区原点与输入时间之间的秒数
 输入参数  : TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeZone 时间
 输出参数  : VOS_UINT64                         *pullTimeInterval
 返 回 值  : VOS_UINT32
             VOS_TRUE:  成功
             VOS_FALSE: 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_GetTimeIntervalSince1970(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeZone,
    VOS_UINT64                         *pullTimeInterval
)
{
    TAF_XCALL_STD_TIME_ZONE_STRU        stTMTimeZone;
    VOS_UINT64                          ullRslt;

    ullRslt                             = VOS_FALSE;
    PS_MEM_SET(&stTMTimeZone, 0x00, sizeof(TAF_XCALL_STD_TIME_ZONE_STRU));

    if (VOS_FALSE == TAF_XCALL_IsMkTimeParaValid(pstTimeZone))
    {
        *pullTimeInterval               = 0;

        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_GetTimeIntervalSince1970():WARNING: Invalid Time Zone!");

        return VOS_FALSE;
    }

    stTMTimeZone.ulYear                 = (VOS_UINT32)(pstTimeZone->usYear - TAF_XCALL_TIME_STAMP_ORIG_YEAR);
    stTMTimeZone.ulMonth                = (VOS_UINT32)(pstTimeZone->usMonth - TAF_XCALL_MKTIME_MONTH_OFFSET);
    stTMTimeZone.ulDay                  = (VOS_UINT32)pstTimeZone->usDay;
    stTMTimeZone.ulHour                 = (VOS_UINT32)pstTimeZone->usHour;
    stTMTimeZone.ulMinute               = (VOS_UINT32)pstTimeZone->usMinute;
    stTMTimeZone.ulSecond               = (VOS_UINT32)pstTimeZone->usSecond;

    /* 转换成从1970年1月1日0时0分0秒起的秒数 */

    /*lint -e571*/
    ullRslt                             = (VOS_UINT64)mktime((TAF_XCALL_MKTIME_TM_STRU *)&stTMTimeZone);
    /*lint +e571*/

    if (TAF_XCALL_STIME_INVALID_VALUE == ullRslt)
    {
        *pullTimeInterval               = 0;

        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_GetTimeIntervalSince1970():WARNING: mktime failed!");

        return VOS_FALSE;
    }

    *pullTimeInterval                   = ullRslt;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ConvertCurSysTime80msToStdTimeIntervalSince1970
 功能描述  : 将系统时间转换成从当前时区原点起的秒数
 输入参数  : VOS_UINT64 : 从CDMA_Timing_GetSystemTime80ms获取的当前系统时间(80ms)
 输出参数  : VOS_UINT64 : *pullStdSysTime
 返 回 值  : VOS_UINT32
             VOS_TRUE:  成功
             VOS_FASLE: 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_ConvertCurSysTime80msToStdTimeIntervalSince1970(
    VOS_UINT64                          ullCurSysTime,
    VOS_UINT64                         *pullStdSysTime
)
{
    TAF_STD_TIME_ZONE_TYPE_STRU         stOrigTimeZone;
    VOS_UINT64                          ullTimeInterval;

    ullTimeInterval                     = 0;

    /* 1980年1月6日0时0分0秒 */
    PS_MEM_SET(&stOrigTimeZone, 0x00, sizeof(TAF_STD_TIME_ZONE_TYPE_STRU));
    stOrigTimeZone.usYear               = TAF_XCALL_SYSTIME_ORIGINAL_YEAR;
    stOrigTimeZone.usMonth              = TAF_XCALL_SYSTIME_ORIGINAL_MONTH;
    stOrigTimeZone.usDay                = TAF_XCALL_SYSTIME_ORIGINAL_DAY;

    /* 最大时间间隔保护，防止翻转 */
    if (ullCurSysTime > TAF_XCALL_STIME_MAX_INTERVAL_VALUE)
    {
        return VOS_FALSE;
    }

    /* 获取1980年1月6日0时0分0秒距离1970年1月1日0时0分0秒的秒数 */
    if (VOS_FALSE == TAF_XCALL_GetTimeIntervalSince1970(&stOrigTimeZone, &ullTimeInterval))
    {
        return VOS_FALSE;
    }

    /* 将当前80ms个数换算成1秒的个数，并加上1980年1月6日到1970年1月1日的时间间隔 */
    *pullStdSysTime = ullTimeInterval + (VOS_UINT64)TAF_XCALL_STIME_CONVERT_80MS_TO_1S(ullCurSysTime);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_IsTimeZoneEmpty
 功能描述  : 判断时间结构是否为空
 输入参数  : TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeZone
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_TRUE:  为空
             VOS_FASLE: 不为空
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_IsTimeZoneEmpty(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeZone
)
{
    TAF_STD_TIME_ZONE_TYPE_STRU         stNullTimeZone;

    PS_MEM_SET(&stNullTimeZone, 0x00, sizeof(TAF_STD_TIME_ZONE_TYPE_STRU));

    if (0 == PS_MEM_CMP(pstTimeZone, &stNullTimeZone, sizeof(TAF_STD_TIME_ZONE_TYPE_STRU)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_IsTimeStampValid
 功能描述  : 判断网络时间戳是否符合要求
 输入参数  : pucTimeStamp: 时间戳
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_TRUE:  时间戳符合要求
             VOS_FALSE: 时间戳不符合要求
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_IsTimeStampValid(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeStamp,
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstLastSysTimeZone
)
{
    VOS_UINT64                          ullSysTimeInterval80ms;
    VOS_UINT64                          ullStdSysTimeInterval;
    VOS_UINT64                          ullStdMsgTimeInterval;
    VOS_UINT64                          ullStdLastTimeInterval;

    ullSysTimeInterval80ms              = 0;
    ullStdSysTimeInterval               = 0;
    ullStdMsgTimeInterval               = 0;
    ullStdLastTimeInterval              = 0;

    /* 检查原则:
       1.输入时间，本地时间，最近一次的时间
       查询终端最近一次的安全信息擦除操作记录（如果没有记录，则直接进入后续
       流程），若时间戳早于记录中的操作时间，或晚于记录操作时间五分钟内，则
       退出指令处理，否则进入后续流程

       2.把时间戳与当前本地时间相比，若时间戳早于本地时间24小时之内，则进入
       后续流程，否则退出指令处理  */

    /* 获取从1980年1月6日至今的系统时间 */
    ullSysTimeInterval80ms              = CDMA_Timing_GetSystemTime80ms(CDMA_TIMING_RTT_1X);

    if (TAF_XCALL_STIME_INVALID_VALUE == ullSysTimeInterval80ms)
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_IsTimeStampValid():WARNING: ullCurSysTime Invalid!");

        return VOS_FALSE;
    }

    /* 将系统时间转换成1970年1月1日的秒数 */
    if (VOS_FALSE == TAF_XCALL_ConvertCurSysTime80msToStdTimeIntervalSince1970(ullSysTimeInterval80ms, &ullStdSysTimeInterval))
    {
        /* 系统时间转换失败 */
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_IsTimeStampValid():WARNING: Convert Systime Failed!");

        return VOS_FALSE;
    }

    /* 将从网络获取到的时间转换成秒数 */
    if (VOS_FALSE == TAF_XCALL_GetTimeIntervalSince1970(pstTimeStamp, &ullStdMsgTimeInterval))
    {
        /* 网络时间转换失败 */
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_IsTimeStampValid():WARNING: Get Msg Time Interval Failed!");

        return VOS_FALSE;
    }

    /* 若系统记录的上一次的时间为空，则不检查此次消息与上次操作的时间间隔是否间隔5分钟以上 */
    if (VOS_FALSE == TAF_XCALL_IsTimeZoneEmpty(pstLastSysTimeZone))
    {
        /* 将年月日，时分秒转换成与1970年1月1日0时0分0秒起的间隔秒数 */
        if (VOS_FALSE == TAF_XCALL_GetTimeIntervalSince1970(pstLastSysTimeZone, &ullStdLastTimeInterval))
        {
            /* 秒数转换失败 */
            TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_IsTimeStampValid():WARNING: Get Last Time Interval Failed!");

            return VOS_FALSE;
        }

        /* 若间隔在5分钟以内或早于上一次记录的时间戳，则认为时间戳不符合要求 */
        if (ullStdMsgTimeInterval < (ullStdLastTimeInterval + TAF_XCALL_TIME_INTERVAL_5MINUTS))
        {
            TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_IsTimeStampValid():WARNING: Not Over 5 Minutes!");

            return VOS_FALSE;
        }
    }

    /* 若获取的系统时间间隔秒数小于1天，则认为获取异常，返回失败 */
    if (ullStdSysTimeInterval < TAF_XCALL_TIME_INTERVAL_ONEDAY)
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_IsTimeStampValid():WARNING: Sys Time Interval Less Than 1 Day!");

        return VOS_FALSE;
    }

    /* 若消息的时间早于当前系统时间24小时及以上, 或者晚于当前系统的时间，则认为时间戳无效 */
    if ((ullStdMsgTimeInterval <= (ullStdSysTimeInterval - TAF_XCALL_TIME_INTERVAL_ONEDAY))
     || (ullStdMsgTimeInterval > ullStdSysTimeInterval))
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_IsTimeStampValid():WARNING: Not In 24 Hours!");

        return VOS_FALSE;
    }

    /* 打印 */
    TAF_XCALL_MNTN_LogTimeStampValidation(pstTimeStamp,
                                          pstLastSysTimeZone,
                                          ullStdSysTimeInterval,
                                          ullStdLastTimeInterval,
                                          ullStdMsgTimeInterval);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GenerateEncVoicePlainText
 功能描述  : 将IMSI, HardWare Id, 被叫号码进行BCD编码合并到一个数组中,生成明文信息
 输入参数  : VOS_UINT8                                              *pucImsiInfo,
             TAF_XCALL_HARDWARE_ID_INFO_STRU                        *pstHardWareId,
             TAF_ECC_CALL_BCD_NUM_STRU                              *pstCalledNum,
 输出参数  : TAF_XCALL_PLAIN_TEXT_INFO_STRU                         *pstPlainTextInfo
 返 回 值  : VOS_UINT32
             VOS_TRUE:  合并成功
             VOS_FALSE: 合并失败
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_GenerateEncVoicePlainText(
    VOS_UINT8                                              *pucImsiInfo,
    TAF_XCALL_HARDWARE_ID_INFO_STRU                        *pstHardWareId,
    TAF_ECC_CALL_BCD_NUM_STRU                              *pstCalledNum,
    TAF_XCALL_PLAIN_TEXT_INFO_STRU                         *pstPlainTextInfo
)
{
    VOS_UINT8                          *pucPlainTextContent   = VOS_NULL_PTR;
    VOS_UINT8                           ucPlainTextInfoLen;
    VOS_UINT8                           aucStdCalledNum[TAF_XCALL_CALLEDNUM_INFO_MAX_LEN];
    VOS_UINT8                           aucStdImsi[TAF_XCALL_IMSI_INFO_LEN];

    pucPlainTextContent                 = pstPlainTextInfo->aucContent;
    PS_MEM_SET(aucStdCalledNum, 0x00, sizeof(aucStdCalledNum));
    PS_MEM_SET(aucStdImsi, 0x00, sizeof(aucStdImsi));
    ucPlainTextInfoLen                  = 0;

    /* 拼接Imsi */
    *pucPlainTextContent                = TAF_XCALL_IMSI_INFO_LEN;
    pucPlainTextContent++;
    ucPlainTextInfoLen++;

    /* Imsi编码转换 */
    if (VOS_FALSE == TAF_XCALL_ConvertImsiFromStdBcdToKmcBcd(pucImsiInfo,
                                                             aucStdImsi,
                                                             TAF_XCALL_IMSI_INFO_LEN))
    {
        PS_MEM_SET(pstPlainTextInfo, 0x00, sizeof(TAF_XCALL_PLAIN_TEXT_INFO_STRU));

        return VOS_FALSE;
    }

    PS_MEM_CPY(pucPlainTextContent, aucStdImsi, sizeof(VOS_UINT8) * TAF_XCALL_IMSI_INFO_LEN);
    pucPlainTextContent += TAF_XCALL_IMSI_INFO_LEN;
    ucPlainTextInfoLen  += TAF_XCALL_IMSI_INFO_LEN;

    /* 拼接HardWareInfo */
    *pucPlainTextContent                = TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN + 1;
    pucPlainTextContent++;
    ucPlainTextInfoLen++;

    *pucPlainTextContent                = (VOS_UINT8)pstHardWareId->enHardWareType;
    pucPlainTextContent++;
    ucPlainTextInfoLen++;

    /* MEID小端存储，直接复制 */
    PS_MEM_CPY(pucPlainTextContent, pstHardWareId->aucHardWareIdInfo, sizeof(VOS_UINT8) * TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN);
    pucPlainTextContent += TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN;
    ucPlainTextInfoLen  += TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN;

    /* 拼接CalledNum */
    *pucPlainTextContent                = TAF_XCALL_CALLEDNUM_INFO_MAX_LEN;
    pucPlainTextContent++;
    ucPlainTextInfoLen++;

    /* 被叫号码格式转换 */
    if (VOS_FALSE == TAF_XCALL_ConvertRemoteNumFromStdBcdToKmcBcd(pstCalledNum->aucBcdNum,
                                                                  pstCalledNum->ucNumLen,
                                                                  aucStdCalledNum,
                                                                  TAF_XCALL_CALLEDNUM_INFO_MAX_LEN))
    {
        PS_MEM_SET(pstPlainTextInfo, 0x00, sizeof(TAF_XCALL_PLAIN_TEXT_INFO_STRU));

        return VOS_FALSE;
    }

    PS_MEM_CPY(pucPlainTextContent, aucStdCalledNum, sizeof(VOS_UINT8) * TAF_XCALL_CALLEDNUM_INFO_MAX_LEN);
    ucPlainTextInfoLen  += TAF_XCALL_CALLEDNUM_INFO_MAX_LEN;

    pstPlainTextInfo->ucNumLen            = ucPlainTextInfoLen;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_SendRemoteCtrlEventRsltToKmc
 功能描述  : Remote Ctrl Ind消息失败的处理
 输入参数  : TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM_UINT8       enRemoteCtrlCmdType,  命令类型
             TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_ENUM_UINT8       enRemoteCtrlRsltType  远程控制信息回复结果
             TAF_XCALL_REMOTE_CTRL_CTX                              *pstRemoteCtrlCtx      远程控制信息上下文
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_TRUE   :发送成功
             VOS_FALSE  :发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_SendRemoteCtrlEventRsltToKmc(
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM_UINT8       enRemoteCtrlCmdType,
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_ENUM_UINT8       enRemoteCtrlRsltType,
    TAF_XCALL_REMOTE_CTRL_CTX                              *pstRemoteCtrlCtx
)
{
    TAF_XCALL_KMC_MSG_STRU                                  stKmcMsg;
    VOS_UINT16                                              usKmMsgLen;
    VOS_UINT8                                               aucKmcMsg[TAF_XCALL_KMC_MSG_WMS_CDMA_USER_DATA_MAX];

    PS_MEM_SET(&stKmcMsg, 0x00, sizeof(TAF_XCALL_KMC_MSG_STRU));
    PS_MEM_SET(aucKmcMsg, 0x00, sizeof(aucKmcMsg));
    usKmMsgLen                                              = 0;

    /* 构造回复的消息 */
    stKmcMsg.enSmsType                                      = TAF_XCALL_KMC_MSG_TYPE_ROMOTE_CTRL_CMD_RSP;
    stKmcMsg.u.stRemoteCtrlRsp.enRomoteCtrlCmdType          = enRemoteCtrlCmdType;
    stKmcMsg.u.stRemoteCtrlRsp.enExecuteRslt                = enRemoteCtrlRsltType;
    stKmcMsg.u.stRemoteCtrlRsp.ucKeyVersion                 = TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber()->ucVerNum;

    if (TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS == TAF_XCALL_EncodeKmcMsg(&stKmcMsg, &aucKmcMsg[0], &usKmMsgLen))
    {
        pstRemoteCtrlCtx->usWaitXsmsCnfOpId = TAF_XCALL_GetSendXsmsReqOpId();

        /* 发送KMC消息给XSMS */
        TAF_XCALL_SendXsmsKmcMsgSendReq(pstRemoteCtrlCtx->usWaitXsmsCnfOpId, usKmMsgLen, aucKmcMsg);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_GetHardWareInfo
 功能描述  : 获取硬件信息
 输入参数  :
 输出参数  : TAF_XCALL_HARDWARE_ID_INFO_STRU                         stHardWareIdInfo
 返 回 值  : VOS_UINT32
             VOS_TRUE:  获取成功
             VOS_FALSE: 获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_GetHardWareInfo(
    TAF_XCALL_HARDWARE_ID_INFO_STRU                        *pstHardWareIdInfo
)
{
    VOS_UINT8                                              *pucHardWareInfo = VOS_NULL_PTR;
    VOS_UINT8                                               aucInvalidHardWareId[TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN];

    PS_MEM_SET(aucInvalidHardWareId, TAF_XCALL_INVALID_HARDWARE_ID, sizeof(VOS_UINT8) * TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN);

    pstHardWareIdInfo->enHardWareType   = TAF_XCALL_HARDWARE_ID_TYPE_MEID;
    pstHardWareIdInfo->ucHardWareIdLen  = TAF_XCALL_HARDWARE_TYPE_MEID_LEN;
    pucHardWareInfo                     = TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.aucMeId;

    if (0 == PS_MEM_CMP(aucInvalidHardWareId, TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.aucMeId, sizeof(VOS_UINT8) * TAF_XCALL_HARDWARE_TYPE_MEID_LEN))
    {
        /* 若Meid无效，检查ESN是否可用 */
        if (0 == PS_MEM_CMP(aucInvalidHardWareId, &(TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.ulEsn), sizeof(VOS_UINT32)))
        {
            PS_MEM_SET(pstHardWareIdInfo, 0x00, sizeof(TAF_XCALL_HARDWARE_ID_INFO_STRU));

            /* HardWareId无效 */
            return VOS_FALSE;
        }

        pstHardWareIdInfo->enHardWareType       = TAF_XCALL_HARDWARE_ID_TYPE_ESN;
        pstHardWareIdInfo->ucHardWareIdLen      = TAF_XCALL_HARDWARE_TYPE_ESN_LEN;
        pucHardWareInfo                         = (VOS_UINT8 *)(&(TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.ulEsn));
    }

    PS_MEM_CPY((VOS_UINT8 *)&(pstHardWareIdInfo->aucHardWareIdInfo[TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN - 1]) - pstHardWareIdInfo->ucHardWareIdLen + 1,
               pucHardWareInfo,
               sizeof(VOS_UINT8) * pstHardWareIdInfo->ucHardWareIdLen);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ConvertRemoteNumFromKmcBcdToStdBcd
 功能描述  : 将KMC发过来的BCD 格式的号码转成标准BCD 格式的号码
             eg. 000000012345  --->  2143F5FFFFFF
                 000000123456  --->  214365FFFFFF
 输入参数  : VOS_UINT8  *pucKmcBcdNum  KMC发过来的BCD 格式的号码
             VOS_UINT8  ucKmcBcdNumLen  KMC发过来的BCD 格式的号码所占字节数
             VOS_UINT8  ucStdBcdNumLen 为标准BCD 格式的号码分配的字节数
 输出参数  : VOS_UINT8  *pucStdBcdNum, 转换后的号码

 返 回 值  : VOS_UINT32 转换成标准BCD 格式的有效号码长度(即除去填充OXFF的长度)
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月29日
    作    者   : l00359089
    修改内容   : Iteration 19
*****************************************************************************/
VOS_UINT8 TAF_XCALL_ConvertRemoteNumFromKmcBcdToStdBcd(
    VOS_UINT8                          *pucKmcBcdNum,
    VOS_UINT8                           ucKmcBcdNumLen,
    VOS_UINT8                          *pucStdBcdNum,
    VOS_UINT8                           ucStdBcdNumLen
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    VOS_UINT8                           ucIsOddNum;

    ucIsOddNum                          = VOS_FALSE;

    /*判断号码长度是否为奇数,如果第一个不为0的数的高字节是0,即为奇数*/
    for (i = 0; i < ucKmcBcdNumLen; i++)
    {
        if ( 0 != pucKmcBcdNum[i])
        {
            ucIsOddNum = (pucKmcBcdNum[i] & 0xF0) ? VOS_FALSE : VOS_TRUE;
            break;
        }
    }

    /*1 当i等于ucKmcBcdNumLen时,说明 KMC发过来的号码全为0,是无效的号码,则无法转换
      2 若标准BCD 格式的号码分配的空间,小于 KMC发过来的号码的有效长度,则无法转换*/
    if ((ucKmcBcdNumLen == i)
     || (ucStdBcdNumLen < (ucKmcBcdNumLen - i)))
    {
        PS_MEM_SET(&pucStdBcdNum[0], 0xFF, ucStdBcdNumLen);
        return 0;
    }

    if (VOS_FALSE == ucIsOddNum)
    {
        /* 将高低4位的位置互换 */
        for (j = 0; i < ucKmcBcdNumLen; j++, i++)
        {
            pucStdBcdNum[j]  = (VOS_UINT8)((pucKmcBcdNum[i] & 0x0F) << 4);
            pucStdBcdNum[j] |= (VOS_UINT8)((pucKmcBcdNum[i] & 0xF0) >> 4);
        }
    }
    else
    {
        for (j = 0; i < ucKmcBcdNumLen; j++, i++)
        {
            pucStdBcdNum[j] = (pucKmcBcdNum[i] & 0x0F);
            if ((i + 1) < ucKmcBcdNumLen )
            {
                pucStdBcdNum[j] |= (pucKmcBcdNum[i+1] & 0xF0) ;
            }
            else
            {
                pucStdBcdNum[j] |= 0xF0;
            }
        }
    }

    /*将剩余空间填充为OxFF*/
    if (j < ucStdBcdNumLen)
    {
        PS_MEM_SET(&pucStdBcdNum[j], 0xFF, (ucStdBcdNumLen - j));
    }

    return j ;
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ProcPubKeyEventTimerWaitAck
 功能描述  : 处理等待公钥更新确认消息定时器超时事件
 输入参数  : VOS_VOID *pMsg  -- 事件对应的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-10
    作    者   : l00359089
    修改内容   : 新生成函数 for iteration 19
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcPubKeyEventTimerWaitAck(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_PUBLIC_KEY_UPDATE_CTX    *pstPubKeyUpdateCtx = VOS_NULL_PTR;

    pstPubKeyUpdateCtx = TAF_XCALL_GetPubKeyUpdateCtxAddr();

    /***********************************************************************************
    * 状态处于等待KMC公钥更新确认，退出更新流程
    **********************************************************************************/
    if (TAF_XCALL_K0_UPATE_STA_WAIT_KMC_RSP == pstPubKeyUpdateCtx->enK0UpdateState )
    {
        TAF_XCALL_ExitPubKeyUpdateProcedure();
    }
}

#endif

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
