

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "v_typdef.h"
#include "TafTypeDef.h"
#include "TafAppSsa.h"
#include "MnMsgTs.h"
#include "Taf_MmiStrParse.h"
#include "TafMmiEncode.h"
#include "TafStdlib.h"
#include "NasStkInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
  2 常量定义
*****************************************************************************/
#define THIS_FILE_ID                PS_FILE_ID_TAF_MMIENCODE_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

TAF_MMI_ENCODE_PROC_FUNC_STRU           g_astTafMmiEncodeSsProcFunc[] = {
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_REGISTERSS_MSG),         TAF_MmiEncodeRegisterMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_ERASESS_MSG),            TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_ACTIVATESS_MSG),         TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_DEACTIVATESS_MSG),       TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_INTERROGATESS_MSG),      TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_REGPWD_MSG),             TAF_MmiEncodeRegisterPwdMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_ERASECCENTRY_MSG),       TAF_MmiEncodeEraseCcEntryMmiString},

    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_REGISTERSS_REQ),          TAF_MmiEncodeRegisterMmiString},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_ERASESS_REQ),             TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_ACTIVATESS_REQ),          TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_DEACTIVATESS_REQ),        TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_INTERROGATESS_REQ),       TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_REGPWD_REQ),              TAF_MmiEncodeRegisterPwdMmiString},
};

TAF_MMI_OPERATION_TABLE_STRU            g_astTafMmiEventOperationTypeTbl[] = {
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_REGISTERSS_MSG),         TAF_MMI_REGISTER_SS,    {0, 0, 0}},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_ERASESS_MSG),            TAF_MMI_ERASE_SS,       {0, 0, 0}},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_ACTIVATESS_MSG),         TAF_MMI_ACTIVATE_SS,    {0, 0, 0}},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_DEACTIVATESS_MSG),       TAF_MMI_DEACTIVATE_SS,  {0, 0, 0}},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_INTERROGATESS_MSG),      TAF_MMI_INTERROGATE_SS, {0, 0, 0}},

    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_REGISTERSS_REQ),          TAF_MMI_REGISTER_SS,    {0, 0, 0}},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_ERASESS_REQ),             TAF_MMI_ERASE_SS,       {0, 0, 0}},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_ACTIVATESS_REQ),          TAF_MMI_ACTIVATE_SS,    {0, 0, 0}},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_DEACTIVATESS_REQ),        TAF_MMI_DEACTIVATE_SS,  {0, 0, 0}},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_INTERROGATESS_REQ),       TAF_MMI_INTERROGATE_SS, {0, 0, 0}},
};

/* ASCII to 非压缩GSM 7bit转换表(第8bit设置为0)，UE发起的USSD Request，先转换后压缩*/
LOCAL VOS_UINT8 g_aucTafMmiDefAsciiToAlphaTbl[] =
{
0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x0A,0x2E,0x2E,0x0D,0x2E,0x2E,
0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
0x20,0x21,0x22,0x23,0x02,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
0x00,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x28,0x2F,0x29,0x2E,0x2D,
0x2F,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x21,0x2F,0x29,0x2D,0x2E
};

/*lint -save -e958 */

/*****************************************************************************
  5 函数实现
*****************************************************************************/



VOS_UINT32 TAF_MmiGetEventOperationTypeTblSize(VOS_VOID)
{
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(g_astTafMmiEventOperationTypeTbl) / sizeof(g_astTafMmiEventOperationTypeTbl[0]);

    return ulTblSize;
}


TAF_MMI_OPERATION_TABLE_STRU *TAF_MmiGetEventOperationTypeTblAddr(VOS_VOID)
{
    return g_astTafMmiEventOperationTypeTbl;
}


VOS_UINT8*   TAF_MmiGetCurrAsciiToAlphaTableAddr(VOS_VOID)
{
    return g_aucTafMmiDefAsciiToAlphaTbl;
}


VOS_UINT32 TAF_MmiGetOperationType(
    VOS_UINT32                          ulEventType,
    MN_MMI_OPERATION_TYPE_ENUM_U8      *penSsOpType
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTableSize;
    TAF_MMI_OPERATION_TABLE_STRU       *pstEventOperationType = VOS_NULL_PTR;

    /* 获取事件对应的操作类型 */
    ulTableSize           = TAF_MmiGetEventOperationTypeTblSize();
    pstEventOperationType = TAF_MmiGetEventOperationTypeTblAddr();

    for (ulLoop = 0; ulLoop < ulTableSize; ulLoop++)
    {
        if (ulEventType == pstEventOperationType->ulEventType)
        {
            *penSsOpType = pstEventOperationType->enSsOpType;
            return VOS_TRUE;
        }

        pstEventOperationType++;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_MmiEncodeOperationTypeString(
    VOS_UINT32                          ulEventType,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTableSize;
    MN_MMI_OPERATION_TYPE_ENUM_U8       enSsOpType;
    MN_MMI_SS_OP_Tbl_STRU              *pstOperationType      = VOS_NULL_PTR;

    /* 获取事件对应的操作类型 */
    ulRet = TAF_MmiGetOperationType(ulEventType, &enSsOpType);

    /* 获取业务操作类型失败，返回编码失败 */
    if (VOS_FALSE == ulRet)
    {

        return VOS_FALSE;
    }


    /* 获取补充业务操作类型字符串 */
    ulTableSize       = MMI_GetOporationTypeTblSize();
    pstOperationType  = MMI_GetOporationTypeTblAddr();
    for (ulLoop = 0; ulLoop < ulTableSize; ulLoop++)
    {
        if (enSsOpType == pstOperationType->enSsOpType)
        {
            *pulLength = VOS_StrLen((VOS_CHAR *)pstOperationType->pcSsOpStr);
            (VOS_VOID)VOS_StrNCpy((VOS_CHAR *)pcOutMmiStr,
                        (VOS_CHAR *)pstOperationType->pcSsOpStr,
                        *pulLength);
            return VOS_TRUE;
        }

        pstOperationType++;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_MmiEncodeBS(
    TAF_SS_BASIC_SERVICE_STRU          *pstBsService,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulBSLength
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTableSize;
    MN_MMI_BS_TABLE_STRU               *pstBsType = VOS_NULL_PTR;

    /* 获取BS字符串 */
    ulTableSize = MMI_GetBSTblSize();
    pstBsType   = MMI_GetBSTblAddr();

    for (ulLoop = 0; ulLoop < ulTableSize; ulLoop++)
    {
        if ((pstBsType->ucNetBsCode == pstBsService->BsServiceCode)
         && (pstBsType->ucNetBsType == pstBsService->BsType))
        {
            *pulBSLength = VOS_StrLen((VOS_CHAR *)pstBsType->pcMmiBs);
            (VOS_VOID)VOS_StrNCpy(pcOutMmiStr, pstBsType->pcMmiBs, *pulBSLength);
            return VOS_TRUE;
        }

        pstBsType++;
    }

    /* 如果在BS表中没有找到对应的项，仍然返回成功做call control检查 */
    *pulBSLength    = 0;
    *pcOutMmiStr    = VOS_NULL_PTR;

    return VOS_TRUE;
}


VOS_UINT32 TAF_MmiEncodeSC(
    TAF_SS_CODE                         ucSsCode,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulScLength
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTableSize;
    MN_MMI_SC_TABLE_STRU               *pstSCType;

    /* 获取SC字符串 */
    ulTableSize = MMI_GetSCTblSize();
    pstSCType   = MMI_GetSCTblAddr();

    for (ulLoop = 0; ulLoop < ulTableSize; ulLoop++)
    {
        if (pstSCType->ucNetSc == ucSsCode)
        {
            *pulScLength = VOS_StrLen((VOS_CHAR *)pstSCType->pcMmiSc);
            (VOS_VOID)VOS_StrNCpy(pcOutMmiStr, pstSCType->pcMmiSc, *pulScLength);
            return VOS_TRUE;
        }

        pstSCType++;
    }

    return VOS_FALSE;
}


VOS_VOID TAF_MmiEncodeDN(
    TAF_SS_REGISTERSS_REQ_STRU         *pstRegisterInfo,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulDNLength
)
{
    VOS_UINT32                          ulNumberLength;

    ulNumberLength = VOS_StrLen((VOS_CHAR *)pstRegisterInfo->aucFwdToNum);
    if (ulNumberLength > TAF_SS_MAX_FORWARDED_TO_NUM_LEN)
    {
        ulNumberLength = TAF_SS_MAX_FORWARDED_TO_NUM_LEN;
    }

    (VOS_VOID)VOS_StrNCpy(pcOutMmiStr, (VOS_CHAR *)pstRegisterInfo->aucFwdToNum, ulNumberLength);

    /* 根据目的号码和子号码字符串输出*DN和长度 */
    *pulDNLength = ulNumberLength;

    return;
}


VOS_VOID TAF_MmiEncodePW(
    VOS_UINT8                          *pucPassword,
    VOS_UINT32                          ulPasswordLength,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulPWLength
)
{

    /* 构造密码字符串 */
    PS_MEM_CPY(pcOutMmiStr, pucPassword, ulPasswordLength);

    *pulPWLength = ulPasswordLength;

    return;
}


VOS_UINT32 TAF_MmiEncodeCfnrTimerLen(
    VOS_UINT8                           ucTime,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulLength
)
{
    return TAF_STD_Itoa(ucTime, pcOutMmiStr, pulLength);
}


VOS_UINT32 TAF_MmiEncodeCcbsIndex(
    VOS_UINT8                           ucCallIndex,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulLength
)
{
    return TAF_STD_Itoa(ucCallIndex, pcOutMmiStr, pulLength);

}


VOS_UINT32 TAF_MmiEncodeRegisterMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pPara,
    VOS_CHAR                           *pcOutMmiStr
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulStrLength;
    TAF_SS_REGISTERSS_REQ_STRU         *pstRegisterInfo = VOS_NULL_PTR;

    /*
    只有呼叫转移需要注册操作，涉及命令^CMMI,+CCFC
        Supplementary   Service     Service Code    SIA     SIB SIC
    22.082
            CFU                     21              DN      BS   -
            CF Busy                 67              DN      BS   -
            CF No Reply             61              DN      BS   T
            CF Not Reachable        62              DN      BS   -

            all CF                  002             DN      BS   T
            all conditional CF      004             DN      BS   T

    */
    ulPos           = 0;
    pstRegisterInfo = (TAF_SS_REGISTERSS_REQ_STRU *)pPara;

    /* 输出通用注册操作前缀: ** */
    ulRet = TAF_MmiEncodeOperationTypeString(ulEventType, pcOutMmiStr, &ulPos);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeRegisterMmiString: invalid usMsgType.");
        return ulRet;
    }

    /* 追加SC字符串: */
    ulRet = TAF_MmiEncodeSC(pstRegisterInfo->SsCode,
                            (pcOutMmiStr + ulPos),
                            &ulStrLength);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeRegisterMmiString: invalid SsCode.");
        return ulRet;
    }
    ulPos += ulStrLength;

    /* 追加DN字符串: *呼叫转移主号码和子号码    */
    /* 构造基本业务字符串间隔符* */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    if ((VOS_TRUE == pstRegisterInfo->OP_NumType)
     && (VOS_TRUE == pstRegisterInfo->OP_FwdToNum))
    {
        TAF_MmiEncodeDN(pstRegisterInfo, (pcOutMmiStr + ulPos), &ulStrLength);
        ulPos += ulStrLength;
    }
    else
    {
        return VOS_FALSE;
    }

    /* 构造子号码字符串，解码函数没有子地址，协议也没有明确的子地址格式，
    不提供 */

    /* 无条件转移或遇忙转移没有BS参数时直接追加#结束，否则，没有BS也要填充* */
    if ((VOS_FALSE == pstRegisterInfo->OP_BsService)
     && (VOS_FALSE == pstRegisterInfo->OP_NoRepCondTime))
    {
        /* 追加#  */
        *(pcOutMmiStr + ulPos) = '#';

        return VOS_TRUE;
    }

    /* 追加BS字符串: *BS     */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    if (VOS_TRUE == pstRegisterInfo->OP_BsService)
    {
        ulRet = TAF_MmiEncodeBS(&(pstRegisterInfo->BsService),
                                (pcOutMmiStr + ulPos),
                                &ulStrLength);
        if (VOS_TRUE != ulRet)
        {
            MN_WARN_LOG("TAF_MmiEncodeRegisterMmiString: invalid BS parameter.");
            return ulRet;
        }
        ulPos += ulStrLength;
    }

    /*
    呼叫转移，呼叫条件转移以及无应答转移需要有定时器触发用户无应答转移
    追加T字符串: *T */
    if ((TAF_ALL_FORWARDING_SS_CODE == pstRegisterInfo->SsCode)
     || (TAF_ALL_COND_FORWARDING_SS_CODE == pstRegisterInfo->SsCode)
     || (TAF_CFNRY_SS_CODE == pstRegisterInfo->SsCode))
    {
        if (VOS_TRUE != pstRegisterInfo->OP_NoRepCondTime)
        {
            return VOS_FALSE;
        }

        TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

        ulRet = TAF_MmiEncodeCfnrTimerLen(pstRegisterInfo->NoRepCondTime,
                                          (pcOutMmiStr + ulPos),
                                          &ulStrLength);
        if (VOS_TRUE != ulRet)
        {
            MN_WARN_LOG("TAF_MmiEncodeRegisterMmiString: invalid T parameter.");
            return ulRet;
        }

        ulPos += ulStrLength;
    }

    /* 追加#  */
    *(pcOutMmiStr + ulPos) = '#';

    return VOS_TRUE;
}

/*lint -e438 -e830*/


VOS_UINT32 TAF_MmiEncodeActiveMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pMsg,
    VOS_CHAR                           *pcOutMmiStr
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulStrLength;
    MN_MMI_OPERATION_TYPE_ENUM_U8       enSsOpType;
    TAF_SS_ACTIVATESS_REQ_STRU         *pstActiveInfo = VOS_NULL_PTR;

    /*
    涉及命令^CMMI,+CCFC,+CCWA,
    +CLIR,+CLIP,+COLP
    1)呼叫转移激活，去激活和查询和删除操作操作不需要DN和T参数
      如果存在BS参数，需要为DN参数保留*，否则，不填写*
    2)话机闭锁业务激活和去激活格式如下，查询操作不需要密码
    22.088
        Supplementary   Service     Service Code    SIA     SIB SIC
            BAOC                    33              PW      BS  -
            BAOIC                   331             PW      BS  -
            BAOIC exc home          332             PW      BS  -
            BAIC                    35              PW      BS  -
            BAIC roaming            351             PW      BS  -

            all Barring Serv.       330             PW      BS  -
            Outg. Barr. Serv.       333             PW      BS
            Inc. Barr. Serv.        353             PW      BS
    3)CCBS查询操作不需要n参数
    22.093
            CCBS                    37              n   See Section 4.5.5               where n=1-5
    4)呼叫等待的激活，去激活和查询
    22.083
            WAIT                    43              BS      -   -
    */
    /* 输出通用激活(*)，去激活(#)，查询操作前缀(*#)，删除操作前缀(##):  */
    ulPos = 0;
    ulRet = TAF_MmiEncodeOperationTypeString(ulEventType, pcOutMmiStr, &ulPos);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeActiveMmiString: invalid usMsgType.");
        return ulRet;
    }

    pstActiveInfo = (TAF_SS_ACTIVATESS_REQ_STRU *)pMsg;

    /* 追加SC字符串: SC */
    ulRet = TAF_MmiEncodeSC(pstActiveInfo->SsCode,
                            (pcOutMmiStr + ulPos),
                            &ulStrLength);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeActiveMmiString: invalid SC parameter.");
        return ulRet;
    }
    ulPos += ulStrLength;

    if ((VOS_FALSE == pstActiveInfo->OP_Password)
     && (VOS_FALSE == pstActiveInfo->OP_BsService))
    {
        /* 追加#  */
        *(pcOutMmiStr + ulPos) = '#';
        ulPos                  += sizeof('#');

        return ulRet;
    }

    ulRet = TAF_MmiGetOperationType(ulEventType, &enSsOpType);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeActiveMmiString: operation type.");
        return ulRet;
    }

    /* 追加PW字符串: *PW */
    if ((TAF_ALL_BARRING_SS_CODE == (TAF_SS_CODE_MASK & (pstActiveInfo->SsCode)))
      && ((TAF_MMI_ACTIVATE_SS == enSsOpType)
       || (TAF_MMI_DEACTIVATE_SS == enSsOpType)))
    {
        TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

        if (VOS_TRUE == pstActiveInfo->OP_Password)
        {
            TAF_MmiEncodePW(pstActiveInfo->aucPassword,
                            TAF_SS_MAX_PASSWORD_LEN,
                            (pcOutMmiStr + ulPos),
                            &ulStrLength);

            ulPos += ulStrLength;
        }
    }

    /* 呼叫转移存在BS参数时，需要为DN参数保留* */
    if (TAF_ALL_FORWARDING_SS_CODE == (TAF_SS_CODE_MASK & (pstActiveInfo->SsCode)))
    {
        TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);
    }

    /* 追加BS字符串: *BS     */
    /*  3GPP 22030 6.5.2 Structure of the MMI:
        Where SI is not applicable according to the definition of the supplementary service, then *SI is omitted.
        Where its use is optional, but not selected for a particular call set-up, it may be omitted or entered as an extra *
        if this is necessary to avoid ambiguity of interpretation.
    */
    if (VOS_TRUE == pstActiveInfo->OP_BsService)
    {
        TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

        ulRet = TAF_MmiEncodeBS(&(pstActiveInfo->BsService),
                                (pcOutMmiStr + ulPos),
                                &ulStrLength);

        if (VOS_TRUE != ulRet)
        {
            MN_WARN_LOG("TAF_MmiEncodeActiveMmiString: invalid BS parameter!");

            return ulRet;
        }

        ulPos += ulStrLength;
    }

    /* 追加#  */
    *(pcOutMmiStr + ulPos) = '#';

    return ulRet;
}
/*lint +e438 +e830*/


VOS_UINT32 TAF_MmiEncodeRegisterPwdMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pMsg,
    VOS_CHAR                           *pcOutMmiStr
)
{
    VOS_UINT32                          ulRet;
    TAF_SS_REGPWD_REQ_STRU             *pstRegisterPwdInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulSCLength;

    /*
       涉及命令^CMMI,+CPWD
       输出注册新密码操作前缀: **03，此处的SsCode标示闭锁类型，
       不能用于输出新密码注册信息，所以直接赋值**03

    22030 6.5.4 Registration of new password
        * 03 * ZZ * OLD_PASSWORD * NEW_PASSWORD * NEW_PASSWORD #
        The UE shall also support the alternative procedure:
        ** 03 * ZZ * OLD_PASSWORD * NEW_PASSWORD * NEW_PASSWORD #
        where, for Barring Services, ZZ = 330;
        for a common password for all appropriate services, delete the ZZ, entering:
        * 03 ** OLD_PASSWORD * NEW_PASSWORD * NEW_PASSWORD #
        The UE shall also support the alternative procedure:
        ** 03 ** OLD_PASSWORD * NEW_PASSWORD * NEW_PASSWORD #
    */
    (VOS_VOID)VOS_StrCpy(pcOutMmiStr, TAF_MMI_REGISTER_PASSWORD);
    ulPos              = VOS_StrLen(TAF_MMI_REGISTER_PASSWORD);

    pstRegisterPwdInfo = (TAF_SS_REGPWD_REQ_STRU *)pMsg;

    /* 追加SC字符串: *SC */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    ulRet = TAF_MmiEncodeSC(pstRegisterPwdInfo->SsCode,
                            (pcOutMmiStr + ulPos),
                            &ulSCLength);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeRegisterPwdMmiString: invalid SC parameter.");
        return ulRet;
    }
    ulPos += ulSCLength;


    /* 追加旧PW字符串: *OLDPASSWORD    */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    (VOS_VOID)VOS_StrNCpy((VOS_CHAR *)(pcOutMmiStr + ulPos), (VOS_CHAR *)pstRegisterPwdInfo->aucOldPwdStr, TAF_SS_MAX_PASSWORD_LEN);
    ulPos += TAF_SS_MAX_PASSWORD_LEN;

    /* 追加新PW字符串: *NEWPASSWORD     */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    (VOS_VOID)VOS_StrNCpy((VOS_CHAR *)(pcOutMmiStr + ulPos), (VOS_CHAR *)pstRegisterPwdInfo->aucNewPwdStr, TAF_SS_MAX_PASSWORD_LEN);
    ulPos += TAF_SS_MAX_PASSWORD_LEN;

    /* 追加新PW确认字符串: *NEWPASSWORD     */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    (VOS_VOID)VOS_StrNCpy((VOS_CHAR *)(pcOutMmiStr + ulPos), (VOS_CHAR *)pstRegisterPwdInfo->aucNewPwdStrCnf, TAF_SS_MAX_PASSWORD_LEN);
    ulPos += TAF_SS_MAX_PASSWORD_LEN;

    /* 追加#  */
    *(pcOutMmiStr + ulPos) = '#';

    return ulRet;
}


VOS_UINT32 TAF_MmiEncodeEraseCcEntryMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pPara,
    VOS_CHAR                           *pcOutMmiStr
)
{
    TAF_SS_ERASECC_ENTRY_REQ_STRU      *pstEraseCcEntryInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSCLength;
    VOS_UINT32                          ulIndexLength;

    /*
       涉及命令^CMMI
    CCBS去激活指定INDEX的CCBS操作格式#37*n#
    CCBS去激活CCBS操作格式#37#
        Supplementary   Service     Service Code    SIA     SIB SIC
    22.093
            CCBS                    37              n   See Section 4.5.5               where n=1-5
            因为不在通用的注册，删除，激活和去激活消息中，所以不调用通用接口获取操作码
    */
    (VOS_VOID)VOS_StrCpy(pcOutMmiStr, "#");
    ulPos               = VOS_StrLen("#");

    pstEraseCcEntryInfo = (TAF_SS_ERASECC_ENTRY_REQ_STRU *)pPara;

    /* 追加SC字符串: */
    ulRet = TAF_MmiEncodeSC(pstEraseCcEntryInfo->SsCode,
                            (pcOutMmiStr + ulPos),
                            &ulSCLength);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeEraseCcEntryMmiString: invalid SC parameter.");
        return ulRet;
    }
    ulPos += ulSCLength;

    /* 根据OP_CcbsIndex和CcbsIndex生成*n    */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);
    if (VOS_TRUE == pstEraseCcEntryInfo->OP_CcbsIndex)
    {

        /* 转换数字类型的INDEX为字符类型 */
        ulRet = TAF_MmiEncodeCcbsIndex(pstEraseCcEntryInfo->CcbsIndex,
                               (pcOutMmiStr + ulPos),
                               &ulIndexLength);
        if (VOS_TRUE != ulRet)
        {
            MN_WARN_LOG("TAF_MmiEncodeEraseCcEntryMmiString: invalid CcbsIndex.");
            return ulRet;
        }
        ulPos += ulIndexLength;

    }

    /* 追加#  */
    *(pcOutMmiStr + ulPos) = '#';

    return VOS_TRUE;
}


TAF_MMI_ENCODE_PROC_FUNC_STRU *TAF_MmiEncodeSsProcFuncTblAddr(VOS_VOID)
{
    return g_astTafMmiEncodeSsProcFunc;
}


VOS_UINT32 TAF_MmiEncodeSsProcFuncTblSize(VOS_VOID)
{
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(g_astTafMmiEncodeSsProcFunc) / sizeof(g_astTafMmiEncodeSsProcFunc[0]);

    return ulTblSize;
}


VOS_UINT32 TAF_MmiEncodeMmiString(
    VOS_VOID                           *pPara,
    VOS_CHAR                           *pcOutMmiStr
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTableSize;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulEventType;
    TAF_MMI_ENCODE_PROC_FUNC            pMsgProcFunc = VOS_NULL_PTR;
    TAF_MMI_ENCODE_PROC_FUNC_STRU      *pstMapTbl    = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppReq    = VOS_NULL_PTR;

    /* 获取指定消息的消息处理函数 */
    pstAppReq   = (MN_APP_REQ_MSG_STRU *)pPara;
    ulEventType = TAF_MMI_BuildEventType(pstAppReq->ulSenderPid, pstAppReq->usMsgName);

    /* 获取处理函数，获取到LOOP值后判断函数指针是否为空 */
    ulTableSize = TAF_MmiEncodeSsProcFuncTblSize();
    pstMapTbl   = TAF_MmiEncodeSsProcFuncTblAddr();

    for (ulLoop = 0; ulLoop < ulTableSize; ulLoop++)
    {
        if (pstMapTbl->ulEventType == ulEventType)
        {
            pMsgProcFunc = pstMapTbl->pMsgProcFunc;
            break;
        }

        pstMapTbl++;
    }

    if (VOS_NULL_PTR == pMsgProcFunc)
    {
        return VOS_FALSE;
    }

    ulRet = pMsgProcFunc(ulEventType, pstAppReq->aucContent, pcOutMmiStr);

    return ulRet;

}



VOS_UINT32 TAF_MmiEncodeUssdMessage (
    TAF_SS_USSD_STRING_STRU            *pstPara
)
{
    VOS_UINT8                           aucTmp[TAF_SS_MAX_UNPARSE_PARA_LEN];
    VOS_UINT32                          ulEncodeLen;
    VOS_UINT8                           aucTemp_buffer[TAF_SS_MAX_UNPARSE_PARA_LEN];
    VOS_UINT32                          i;
    VOS_UINT8                          *pucCurTransTbl = VOS_NULL_PTR;

    PS_MEM_SET(aucTmp, 0 , TAF_SS_MAX_UNPARSE_PARA_LEN);
    PS_MEM_SET(aucTemp_buffer, 0 , TAF_SS_MAX_UNPARSE_PARA_LEN);
    ulEncodeLen = 0;

    /* 判断输入的字符串是否超长,7bit编码时最长182个字符 */
    if (pstPara->usCnt > TAF_SS_MAX_USSDSTRING_LEN)
    {
        MN_WARN_LOG("TAF_MmiEncodeUssdMessage: string is too long");
        return VOS_FALSE;
    }

    /* convert from ascii coding into GSM default-alphabet
       coding with 1 char per byte  */
    pucCurTransTbl      = TAF_MmiGetCurrAsciiToAlphaTableAddr();
    for (i = 0; i < pstPara->usCnt; i++)
    {
        aucTemp_buffer[i]   = pucCurTransTbl[pstPara->aucUssdStr[i]];
    }

    /* 循环结构,转换成7bit编码方式 */
    if (VOS_OK != TAF_STD_Pack7Bit(aucTemp_buffer, pstPara->usCnt, 0, aucTmp, &ulEncodeLen))
    {
        MN_WARN_LOG("TAF_MmiEncodeUssdMessage: TAF_STD_Pack7Bit Error");
    }

    /* 判断是否有7个位的空余,如果有多余的7个位则填充'0001101' */
    if (TAF_MMI_BITS_PER_SEPTET == (pstPara->usCnt % TAF_MMI_BITS_PER_OCTET))
    {
       aucTmp[ulEncodeLen - 1] = aucTmp[ulEncodeLen - 1] | TAF_MMI_USSD_7BIT_PAD;
    }

    pstPara->usCnt = (VOS_UINT16)ulEncodeLen;
    PS_MEM_CPY(pstPara->aucUssdStr, aucTmp, pstPara->usCnt);

    return VOS_TRUE;
}
/*lint -restore */

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

