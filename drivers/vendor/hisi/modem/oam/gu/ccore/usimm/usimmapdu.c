/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : UsimmBase.c
  Author       : zhuli 00100318
  Version      : V100R002
  Date         : 2008-5-15
  Description  : 该C文件给出了---APDU模块实现
  Function List:
  History      :
 ************************************************************************/
#include "product_config.h"

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)

#include "usimmapdu.h"
#include "usimmdl.h"
#include "usimmt1dl.h"
#include "usimmglobal.h"
#include "UsimPsInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_APDUMODULE_C
/*lint +e767*/
/*****************************************************************************
函 数 名  :USIMM_UiccPinOperationResultProc
功能描述  :对DL层返回的结果和状态字还要针对PIN码操作再做判断
输入参数  :ulResult:DL层返回的结果
           pstRspData:返回的内容和状态字
输出参数  :无
返 回 值  :USIMM_SWCHECK_ENUM_UINT32
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_UiccPinOperationResultProc(
    VOS_UINT8                           ucINS,
    VOS_UINT32                          ulResult)
{
    /* ICC卡PIN操作不对SW状态字再做处理，下面DL层已经处理过 */
    if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
    {
        return ulResult;
    }

    if (  (CMD_INS_VERIFY       == ucINS)
        ||(CMD_INS_DISABLE_PIN  == ucINS)
        ||(CMD_INS_CHANGE_PIN   == ucINS)
        ||(CMD_INS_ENABLE_PIN   == ucINS)
        ||(CMD_INS_UNBLOCK_PIN  == ucINS))
    {
        return USIMM_SW_CMD_REMAINTIME;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_CheckSW
功能描述  :检查命令发送的结构
输入参数  :pstUSIMMAPDU

输出参数  :无
返 回 值  :USIMM_SWCHECK_ENUM_UINT16
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_CheckSW(
    VOS_UINT8                           ucINS,
    VOS_UINT8                           ucSW1,
    VOS_UINT8                           ucSW2)
{
    USIMM_SWCHECK_ST                   *pstSWCheck;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          i;
    USIMM_SWCHECK_ENUM_UINT16           enResult = USIMM_SW_OTHER_ERROR;

    if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())  /*根据卡类型判断*/
    {
        pstSWCheck = gausSimSWCheck;

        ulLen      = USIMM_SIMSW_MAXNUMBER;
    }
    else
    {
        pstSWCheck = gausUsimSWCheck;

        ulLen      = USIMM_USIMSW_MAXNUMBER;
    }

    for(i=0; i<ulLen; i++)
    {
        if(pstSWCheck[i].ucSW1 != ucSW1)        /*先判断SW1匹配*/
        {
            continue;
        }

        if((0xC0 == (ucSW2&0xF0))&&(0x63 == pstSWCheck[i].ucSW1))
        {
            /* 对DL层返回的结果和状态字还要针对PIN码操作再做判断 */
            enResult = (USIMM_SWCHECK_ENUM_UINT16)USIMM_UiccPinOperationResultProc(ucINS, 
                                                                            pstSWCheck[i].enResult);

            break;
        }

        if((0xFF == pstSWCheck[i].ucSW2)||(ucSW2 == pstSWCheck[i].ucSW2))/*不需要判断SW2或者SW2匹配*/
        {
            enResult = pstSWCheck[i].enResult;

            break;
        }
    }

    if (USIMM_SW_OK_WITH_SAT == enResult)    /*SAT需要特殊处理*/
    {
        USIMM_INFO_LOG("USIMM_CheckSW: There is SAT Data Need Fetch");

        gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NEEDFETCH;

        if (0x00 == ucSW2)           /*代表当前获取主动命令长度256*/
        {
            gstUSIMMBaseInfo.usSATLen = 0x100;
        }
        else
        {
            gstUSIMMBaseInfo.usSATLen = ucSW2;
        }

        enResult = USIMM_SW_OK;
    }

    return (VOS_UINT32)enResult;
}

/*****************************************************************************
函 数 名  :USIMM_MakeApduCLA
功能描述  :检查命令发送的结构
输入参数  :pstUSIMMAPDU

输出参数  :无
返 回 值  :USIMM_SWCHECK_ENUM_UINT16
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT8 USIMM_MakeApduCLA(
    VOS_UINT8                           ucChannel,
    VOS_UINT8                           ucINS,
    VOS_UINT8                           ucCLABit,
    USIMM_APDUCMD_ATTRIBUTE_ENUM_UINT8  enAttribute)
{
    VOS_UINT8           ucCLA;
    VOS_UINT8           ucTempChannel;

    if ((CMD_INS_TERMINAL_PROFILE   == ucINS)
        ||(CMD_INS_ENVELOPE         == ucINS)
        ||(CMD_INS_FETCH            == ucINS)
        ||(CMD_INS_TERMINAL_RESPONSE== ucINS))
    {
        return (gstUSIMMBaseInfo.ucCLA | ucCLABit);
    }

    if ( ucChannel <= USIMM_APDU_CHANNEL_4 )
    {
        ucTempChannel = (ucChannel&0x03);
    }
    else
    {
        ucTempChannel = ((ucChannel-4)&0x0F);

        gstUSIMMBaseInfo.ucCLA |= 0x40;
    }

    if ((USIMM_APDUCMD_CSIM == enAttribute)
        &&(CMD_INS_COMPUTE_IP_AUTH == ucINS))
    {
        ucCLA = ucTempChannel|USIMM_APDU_3GPP_CLA;
    }
    else
    {
        ucCLA = ucTempChannel|gstUSIMMBaseInfo.ucCLA;
    }

    if (VOS_NULL != ucCLABit)
    {
        ucCLA = ucCLA|ucCLABit;
    }

    return ucCLA;
}

/*****************************************************************************
函 数 名  :USIMM_MakeTpduCLA
功能描述  :检查命令发送的结构
输入参数  :pstUSIMMAPDU

输出参数  :无
返 回 值  :USIMM_SWCHECK_ENUM_UINT16
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT8 USIMM_MakeTpduCLA(
    VOS_UINT8                           ucChannel,
    VOS_UINT8                           ucCLA,
    VOS_UINT8                           ucINS)
{
    VOS_UINT8           ucResultCLA;
    VOS_UINT8           ucTempChannel;

    if ((CMD_INS_TERMINAL_PROFILE   == ucINS)
        ||(CMD_INS_ENVELOPE         == ucINS)
        ||(CMD_INS_FETCH            == ucINS)
        ||(CMD_INS_TERMINAL_RESPONSE== ucINS))
    {
        return ucCLA;
    }

    if ( ucChannel <= USIMM_APDU_CHANNEL_4 )
    {
        ucTempChannel = (ucChannel&0x03);
    }
    else
    {
        ucTempChannel = ((ucChannel-4)&0x0F);

        ucCLA = ucCLA | 0x40;
    }

    ucResultCLA = ucTempChannel|ucCLA;

    return ucResultCLA;
}

/*****************************************************************************
函 数 名  :USIMM_SelectFile_APDU
功能描述  :发送选择文件的命令
输入参数  :pstApduInfo:      命令参数
           ulRetryCnt:       命令执行次数
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_SelectFile_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt
)
{
    VOS_UINT32                          ulResult;

    if(USIMM_SELECT_RETURN_FCP_TEMPLATE == pstApduInfo->aucAPDU[P2])
    {
        /* 此种场景下为case4 */
        pstApduInfo->ulLeValue      = USIMM_LE_MAX_LEN;
    }
    else
    {
        /* case3 */
        pstApduInfo->ulLeValue      = VOS_NULL;
    }

    ulResult = USIMM_DLHandle(pstApduInfo);/*调用链路层处理函数*/

    if (USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SelectFile_APDU:USIMM_DLHandle error");

        return USIMM_SENDAPDU_FAIL;
    }

    ulResult = USIMM_CheckSW(pstApduInfo->aucAPDU[INS], pstApduInfo->ucSW1, pstApduInfo->ucSW2);

    /* 状态字为Warning或Technical Problem则再次进行选文件操作 */
    if ((USIMM_SW_WARNING == ulResult) || (USIMM_SW_TECH_ERROR == ulResult))
    {
        if (1 == ulSendCnt) /*第一次发送*/
        {
            /*TMO测试需求，增加不同参数的重试机制*/
            if (USIMM_SELECT_RETURN_FCP_TEMPLATE == pstApduInfo->aucAPDU[P2])
            {
                pstApduInfo->aucAPDU[P2] = USIMM_SELECT_ACTIVATE_AID;
            }
            else if (USIMM_SELECT_NO_DATA_RETURNED == pstApduInfo->aucAPDU[P2])
            {
                pstApduInfo->aucAPDU[P2] = USIMM_SELECT_RETURN_FCP_TEMPLATE;
            }
            else
            {
                return USIMM_SENDAPDU_FAIL;
            }

            return USIMM_SENDAPDU_RETRY;
        }
        else
        {
            return USIMM_SENDAPDU_FAIL;
        }
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
函 数 名  :USIMM_Status_APDU
功能描述  :通过指定的通道号Status命令发送
输入参数  :pstApduInfo:      命令参数
           ulRetryCnt:       命令执行次数
输出参数  :无
返 回 值  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_Status_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt)
{
    VOS_UINT32              ulResult;

    if ((VOS_NULL == pstApduInfo->aucAPDU[P3])
     && (USIMM_STATUS_NO_DATA_RETURNED != pstApduInfo->aucAPDU[P2]))
    {
        pstApduInfo->ulLeValue = 0x100;
    }
    else
    {
        pstApduInfo->ulLeValue = pstApduInfo->aucAPDU[P3];
    }

    ulResult = USIMM_DLHandle(pstApduInfo);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_STATUS_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
函 数 名  :USIMM_Manage_Channel_APDU
功能描述  :通道管理命令发送
输入参数  :pstApduInfo:      命令参数
           ulRetryCnt:       命令执行次数
输出参数  :无
返 回 值  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_ManageChannel_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt)
{
    VOS_UINT32              ulResult;

    if (USIMM_MANAGECH_CLOSECH == pstApduInfo->aucAPDU[P1])
    {
        if (USIMM_MANAGECH_ASSIGNED_CARD == pstApduInfo->aucAPDU[P2])
        {
            USIMM_ERROR_LOG("USIMM_Manage_Channel_APDU: pstApduInfo->aucAPDU[P2] is Failed");/*打印错误*/

            return USIMM_SENDAPDU_FAIL;
        }
        else
        {
            /* 在对应的逻辑通道上发 在打开逻辑通道时:p2为0，关闭逻辑通道时:p2为对应逻辑通道号 */
            pstApduInfo->aucAPDU[CLA] = pstApduInfo->aucAPDU[CLA] | pstApduInfo->aucAPDU[P2];
        }
    }

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Manage_Channel_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
函 数 名  :USIMM_Terminal_Capability_APDU
功能描述  :terminal capability命令发送
输入参数  :pstApduInfo:      命令参数
           ulRetryCnt:       命令执行次数
输出参数  :无
返 回 值  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_TerminalCapability_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt)
{
    VOS_UINT32 ulResult;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Terminal_Capability_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
函 数 名  :USIMM_StoreESNMEID_APDU
功能描述  :发送Store ESN MEID命令
输入参数  :pstApduInfo:      命令参数
           ulRetryCnt:       命令执行次数
输出参数  :无
返 回 值  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_StoreESNMEID_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt
)
{
    VOS_UINT32              ulResult;

    pstApduInfo->ulLcValue      = USIMM_STORE_ESNMEID_MAX;   /*填充命令其它内容*/

    pstApduInfo->ulLeValue      = 0x01;                      /*固定值*/

    ulResult = USIMM_DLHandle(pstApduInfo);   /*调用链路层处理函数*/

    if (USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_StoreESNMEID_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
函 数 名  :USIMM_ManageSsdAPDU
功能描述  :发送MANAGE SSD命令
输入参数  :pstApduInfo:      命令参数
           ulRetryCnt:       命令执行次数
输出参数  :无
返 回 值  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_ManageSsd_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt)
{
    VOS_UINT32      ulResult;

    ulResult = USIMM_DLHandle(pstApduInfo);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ManageSsdAPDU: USIMM_DLHandle is Failed");/*打印错误*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
函 数 名  :USIMM_GenerateKeyVpmAPDU
功能描述  :发送Generate Key/VPM命令
输入参数  :pstApduInfo:      命令参数
           ulRetryCnt:       命令执行次数
输出参数  :无
返 回 值  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_GenerateKeyVpm_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt)
{
    VOS_UINT32      ulResult;

    ulResult = USIMM_DLHandle(pstApduInfo);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GenerateKeyVpmAPDU: USIMM_DLHandle is Failed");/*打印错误*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
函 数 名  :USIMM_BSChallengeAPDU
功能描述  :发送Store ESN MEID命令
输入参数  :pstApduInfo:      命令参数
           ulRetryCnt:       命令执行次数
输出参数  :无
返 回 值  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_BSChallenge_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt)
{
    VOS_UINT32      ulResult;

    pstApduInfo->ulLeValue    = USIMM_BS_RANDSEED_MAX;

    ulResult = USIMM_DLHandle(pstApduInfo);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_BSChallengeAPDU: USIMM_DLHandle is Failed");/*打印错误*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
函 数 名  :USIMM_SendCase4_APDU
功能描述  :Search Increace Authentication 命令发送
输入参数  :pstApduInfo:      命令参数
           ulRetryCnt:       命令执行次数
输出参数  :无
返 回 值  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_SendCase4_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulRetryCnt)
{
    VOS_UINT32                      ulResult;

    /* 此种场景下为case4 */
    pstApduInfo->ulLeValue = USIMM_LE_MAX_LEN;

    ulResult = USIMM_DLHandle(pstApduInfo);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Search_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
函 数 名  :USIMM_SendAndRetry_APDU
功能描述  :ReadBinary UPDATEBINARY READRECORD UPDATERECORD 命令发送
输入参数  :pstApduInfo:      命令参数
           ulRetryCnt:       命令执行次数
输出参数  :无
返 回 值  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_SendAndRetry_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt)
{
    VOS_UINT32                          ulResult;

    ulResult = USIMM_DLHandle(pstApduInfo);   /*调用链路层处理函数*/

    if (USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendAndRetry_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        if (1 == ulSendCnt)
        {
            return USIMM_SENDAPDU_RETRY;
        }
        else
        {
            return USIMM_SENDAPDU_FAIL;
        }
    }

    ulResult = USIMM_CheckSW(pstApduInfo->aucAPDU[INS], pstApduInfo->ucSW1, pstApduInfo->ucSW2);

    if ((USIMM_SW_OK != ulResult)&&(1 == ulSendCnt))
    {
        USIMM_ERROR_LOG("USIMM_SendAndRetry_APDU: USIMM_CheckSW is Failed");/*打印错误*/

        return USIMM_SENDAPDU_RETRY;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
函 数 名  :USIMM_SendOneTime_APDU
功能描述  :VerifyPIN ChangePIN UnblockPIN DeactivateFile ActivateFile 命令发送
输入参数  :pstApduInfo:      命令参数
           ulRetryCnt:       命令执行次数
输出参数  :无
返 回 值  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_SendOneTime_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt)
{
    VOS_UINT32                          ulResult;

    ulResult = USIMM_DLHandle(pstApduInfo);   /*调用链路层处理函数*/

    if (USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendOneTime_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

USIMM_APDU_FUNC_LIST    g_aUSIMMApduFuncTbl[]=
{
    {CMD_INS_SELECT                ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SelectFile_APDU},
    {CMD_INS_STATUS                ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_Status_APDU},
    {CMD_INS_READ_BINARY           ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendAndRetry_APDU},
    {CMD_INS_UPDATE_BINARY         ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendAndRetry_APDU},
    {CMD_INS_READ_RECORD           ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendAndRetry_APDU},
    {CMD_INS_UPDATE_RECORD         ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendAndRetry_APDU},
    {CMD_INS_SEARCH_RECORD         ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendCase4_APDU},
    {CMD_INS_INCREASE              ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_SendCase4_APDU},
    {CMD_INS_RETRIEVE_DATA         ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_SET_DATA              ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_VERIFY                ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_CHANGE_PIN            ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_DISABLE_PIN           ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_ENABLE_PIN            ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_UNBLOCK_PIN           ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_DEACTIVATE_FILE       ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_ACTIVATE_FILE         ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_AUTHENTICATE          ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendCase4_APDU},
    {CMD_INS_GET_CHALLENGE         ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_TERMINAL_PROFILE      ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_ENVELOPE              ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_SendCase4_APDU},
    {CMD_INS_FETCH                 ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_TERMINAL_RESPONSE     ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_MANAGE_CHANNEL        ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_ManageChannel_APDU},
    {CMD_INS_TERMINAL_CAPABILITY   ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_TerminalCapability_APDU},
    {CMD_INS_MANAGE_SECURE_CHANNEL ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_TRANSACT_DATA         ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_SLEEP                 ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_BASE_STATION_CHALLENGE,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_BSChallenge_APDU},
    {CMD_INS_UPDATE_SSD            ,    0,                      USIMM_APDUCMD_UIM,      0,  USIMM_SendOneTime_APDU},
    {CMD_INS_CONFIRM_SSD           ,    0,                      USIMM_APDUCMD_UIM,      0,  USIMM_SendOneTime_APDU},
    {CMD_INS_MANAGE_SSD            ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_CSIM,     0,  USIMM_ManageSsd_APDU},
    {CMD_INS_GENERATE_KEY          ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_GenerateKeyVpm_APDU},
    {CMD_INS_STORE_ESNMEID         ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_StoreESNMEID_APDU},
    {CMD_INS_LCS_SSAVE_VERIFY      ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_MMS_CFG         ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_LCS_TLS_GMASTER       ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_LCS_TLS_GVERIFY       ,    0,                      USIMM_APDUCMD_CSIM,     0,  VOS_NULL_PTR},
    {CMD_INS_VANDG_KEYBLOCK        ,    0,                      USIMM_APDUCMD_CSIM,     0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_MMS_DOWNLOAD    ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_3GPD_DOWNLOAD   ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_SUCURE_MODE     ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_FRESH           ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_SKEY_GENERATION ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_GENERIC_KEY     ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_KEY_GENERATION  ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_GENERIC_CFG     ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_DOWNLOAD        ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_BCMCS                 ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_APP_AUTH              ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_UMAC_GENERATION       ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_CONFIRM_KEYS          ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_COMPUTE_IP_AUTH       ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_CSIM,     0,  USIMM_SendOneTime_APDU},
    {CMD_INS_OTASP_MMD_CFG         ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_MMD_DOWNLOAD    ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_SYSTAG_CFG      ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_COMMIT          ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_VALIDATE        ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_SSPR_CFG        ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_SSPR_DOWNLOAD   ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_SYSTAG_DOWNLOAD ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_OTAPA_REQUEST   ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_PUZL_CFG        ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_PUZL_DOWNLOAD   ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_3GPD_CFG        ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR}
};

/*****************************************************************************
函 数 名  : USIMM_MakeAPDUCmdData
功能描述  : 填充APDU的命令函数
输入参数  : pstApduHead: APDU命令的头
            pstApduData: APDU命令数据内容，可以为空
输出参数  : pstRspData : APDU命令的返回内容
返 回 值  : 无

修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_MakeAPDUCmdData(
    USIMM_APDU_HEAD_STRU                *pstApduHead,
    USIMM_U8_LVDATA_STRU                *pstApduData,
    USIMM_APDU_RSP_STRU                 *pstRspData)
{
    /*lint -e534*/
    VOS_MemSet(&gstUSIMMAPDU, 0, sizeof(gstUSIMMAPDU));

    if (VOS_NULL_PTR != pstRspData)
    {
        VOS_MemSet(pstRspData, 0, sizeof(USIMM_APDU_RSP_STRU));
    }
    /*lint +e534*/

    /*填充APDU命令头*/
    gstUSIMMAPDU.aucAPDU[INS]   = pstApduHead->ucINS;

    gstUSIMMAPDU.aucAPDU[P1]    = pstApduHead->ucP1;

    gstUSIMMAPDU.aucAPDU[P2]    = pstApduHead->ucP2;

    /*填充命令其它内容*/
    if (VOS_NULL_PTR != pstApduData)
    {
        gstUSIMMAPDU.aucAPDU[P3]    = (VOS_UINT8)pstApduData->ulDataLen;

        gstUSIMMAPDU.ulLcValue      = pstApduData->ulDataLen;

        /*lint -e534*/
        VOS_MemCpy(gstUSIMMAPDU.aucSendBuf,
                    pstApduData->pucData,
                    gstUSIMMAPDU.aucAPDU[P3]);
        /*lint +e534*/
    }
    else
    {
        gstUSIMMAPDU.aucAPDU[P3]    = pstApduHead->ucP3;

        gstUSIMMAPDU.ulLcValue      = VOS_NULL;

        gstUSIMMAPDU.ulLeValue      = pstApduHead->ucP3;
    }

    return;
}

/*****************************************************************************
函 数 名  : USIMM_AttApduSWCheck
功能描述  : ATT定制功能，需要检查返回的命令状态字
输入参数  : 无
返 回 值  : 无

修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_AttApduSWCheck(VOS_VOID)
{
    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAtt_flg)
    {
        if ((0x6F == gstUSIMMAPDU.ucSW1)&&(0x00 == gstUSIMMAPDU.ucSW2))
        {
            g_ulATTSpecErrSWCnt++;
        }
        else
        {
            g_ulATTSpecErrSWCnt = 0;
        }

        if (g_ulATTSpecErrSWCnt >= 3)                                 /*连续超过3次上报无卡*/
        {
            USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_NOCARD);        /*当前状态为无卡*/
        }
    }

    return;
}

/*****************************************************************************
函 数 名  : USIMM_SendAPDUHandle
功能描述  : 发送APDU的命令主控函数
输入参数  : enAttribute: 命令属性用于区分相同INS的不同处理
            pstApduHead: APDU命令的头
            pstApduData: APDU命令数据内容，可以为空
输出参数  : pstRspData : APDU命令的返回内容
返 回 值  : USIMM_SWCHECK_ENUM_UINT32

修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
USIMM_SWCHECK_ENUM_UINT32 USIMM_SendAPDUHandle(
    USIMM_APDUCMD_ATTRIBUTE_ENUM_UINT8  enAttribute,
    USIMM_APDU_HEAD_STRU                *pstApduHead,
    USIMM_U8_LVDATA_STRU                *pstApduData,
    USIMM_APDU_RSP_STRU                 *pstRspData)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulSendCnt;
    USIMM_SENDAPDU_RESULT_ENUM_UINT32   enResult = USIMM_SENDAPDU_FAIL;

    if (VOS_NULL_PTR == pstApduHead)
    {
        USIMM_ERROR_LOG("USIMM_SendAPDUHandle: pstApduHead NULL");/*打印错误*/

        return USIMM_SW_ERR;
    }

    USIMM_MakeAPDUCmdData(pstApduHead, pstApduData, pstRspData);

    if (VOS_NULL_PTR != pstRspData)
    {
        (VOS_VOID)VOS_MemSet(pstRspData, 0, sizeof(USIMM_APDU_RSP_STRU));
    }
    /*lint +e534*/

    ulSendCnt = 0;

    for (i=0; i<ARRAYSIZE(g_aUSIMMApduFuncTbl);)
    {
        if ((g_aUSIMMApduFuncTbl[i].ucINS       == pstApduHead->ucINS)
            &&(g_aUSIMMApduFuncTbl[i].pProcFun  != VOS_NULL_PTR)
            &&(g_aUSIMMApduFuncTbl[i].enAttribute == enAttribute))
        {
            ulSendCnt++;

            gstUSIMMAPDU.aucAPDU[CLA] = USIMM_MakeApduCLA(pstApduHead->ucChannel,
                                                            pstApduHead->ucINS,
                                                            g_aUSIMMApduFuncTbl[i].ucCLABit,
                                                            g_aUSIMMApduFuncTbl[i].enAttribute);

            enResult = g_aUSIMMApduFuncTbl[i].pProcFun(&gstUSIMMAPDU, ulSendCnt);

            if (USIMM_SENDAPDU_RETRY == enResult)
            {
                USIMM_ERROR_LOG("USIMM_SendAPDUHandle: APDU Need Retry");/*打印错误*/

                continue;
            }
            else
            {
                break;
            }
        }

        i++;
    }

    if (USIMM_SENDAPDU_FAIL == enResult)
    {
        USIMM_ERROR_LOG("USIMM_SendAPDUHandle: APDU Send Fail");/*打印错误*/

        return USIMM_SW_SENDCMD_ERROR;
    }

    if (VOS_NULL_PTR != pstRspData)
    {
        pstRspData->usRspLen    = (VOS_UINT16)gstUSIMMAPDU.ulRecDataLen;

        pstRspData->ucSW1       = gstUSIMMAPDU.ucSW1;

        pstRspData->ucSW2       = gstUSIMMAPDU.ucSW2;

        pstRspData->ucApduSW1   = gstUSIMMAPDU.ucApduSW1;

        pstRspData->ucApduSW2   = gstUSIMMAPDU.ucApduSW2;

        if (VOS_NULL != gstUSIMMAPDU.ulRecDataLen)
        {
            /*lint -e534*/
            VOS_MemCpy(pstRspData->aucRsp,
                        gstUSIMMAPDU.aucRecvBuf,
                        gstUSIMMAPDU.ulRecDataLen);
            /*lint +e534*/
        }
    }

    USIMM_AttApduSWCheck();

    return USIMM_CheckSW(pstApduHead->ucINS,
                        gstUSIMMAPDU.ucSW1,
                        gstUSIMMAPDU.ucSW2);   /*返回的是最后的结果，不是第一次发送结果*/
}

/*****************************************************************************
函 数 名  :USIMM_T1SendIFSD_APDU
功能描述  :T=1协议发送IFSD命令
输入参数  :ucData:UE可接收块的信息域大小
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2013年10月18日
   作    者   : j00168360
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_T1SendIFSD_APDU(
    VOS_UINT8                           ucData)
{
    VOS_UINT32      ulResult;

    /*lint -e534*/
    VOS_MemSet(gstUSIMMAPDU.aucAPDU, 0, USIMM_APDU_HEADLEN);

    VOS_MemSet(gstUSIMMAPDU.aucSendBuf, 0, USIMM_APDU_MAXLEN);
    /*lint +e534*/

    /* 需要发送一个字节的IFS大小 */
    gstUSIMMAPDU.ulLcValue = 0x01;

    gstUSIMMAPDU.ulLeValue = 0x00;

    gstUSIMMAPDU.aucSendBuf[0] = ucData;

    /* 标记当前要发送IFS REQ */
    g_bSendIFSReqFlag = VOS_TRUE;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    g_bSendIFSReqFlag = VOS_FALSE;

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_T1SendIFSD_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : USIMM_SendTPDUHandle
功能描述  : 发送APDU的命令主控函数
输入参数  : pstApduHead: APDU命令的头
            pstApduData: APDU命令数据内容，可以为空
输出参数  : pstRspData : APDU命令的返回内容
返 回 值  : USIMM_SWCHECK_ENUM_UINT32

修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
USIMM_SWCHECK_ENUM_UINT32 USIMM_SendTPDUHandle(
    USIMM_TPDU_HEAD_STRU                *pstTpduHead,
    USIMM_U8_LVDATA_STRU                *pstTpduData,
    USIMM_APDU_RSP_STRU                 *pstRspData
)
{
    VOS_UINT32                          ulResult;

    if ((VOS_NULL_PTR == pstTpduHead)||(VOS_NULL_PTR == pstRspData))
    {
        USIMM_ERROR_LOG("USIMM_SendAPDUHandle: pstTpduHead or pstRspData NULL");/*打印错误*/

        return USIMM_SW_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(&gstUSIMMAPDU, 0, sizeof(gstUSIMMAPDU));

    VOS_MemSet(pstRspData, 0, sizeof(USIMM_APDU_RSP_STRU));
    /*lint +e534*/

    /*填充APDU命令头*/
    gstUSIMMAPDU.aucAPDU[CLA]   = USIMM_MakeTpduCLA(pstTpduHead->ucChannel,
                                                    pstTpduHead->ucCLA,
                                                    pstTpduHead->ucINS);    /*仅处理通道问题*/

    gstUSIMMAPDU.aucAPDU[INS]   = pstTpduHead->ucINS;

    gstUSIMMAPDU.aucAPDU[P1]    = pstTpduHead->ucP1;

    gstUSIMMAPDU.aucAPDU[P2]    = pstTpduHead->ucP2;

    /*填充命令其它内容*/
    if (VOS_NULL != pstTpduData->ulDataLen)    /*case3, case4*/
    {
        if ((pstTpduData->ulDataLen < pstTpduHead->ucP3)
            ||(pstTpduData->ulDataLen > (pstTpduHead->ucP3 + 1)))
        {
            USIMM_ERROR_LOG("USIMM_SendTPDUHandle: the data len is more");/*打印错误*/

            return USIMM_SW_ERR;
        }

        gstUSIMMAPDU.aucAPDU[P3]    = pstTpduHead->ucP3;

        gstUSIMMAPDU.ulLcValue      = pstTpduHead->ucP3;

        /*lint -e534*/
        VOS_MemCpy(gstUSIMMAPDU.aucSendBuf, pstTpduData->pucData, gstUSIMMAPDU.aucAPDU[P3]);
        /*lint +e534*/

        /* case4场景，有一字节的LE字段 */
        if (pstTpduData->ulDataLen == (pstTpduHead->ucP3 + 1))
        {
            gstUSIMMAPDU.ulLeValue = pstTpduData->pucData[pstTpduData->ulDataLen - 1];
        }
    }
    else                            /*case1 case2*/
    {
        gstUSIMMAPDU.aucAPDU[P3]    = pstTpduHead->ucP3;

        gstUSIMMAPDU.ulLcValue      = VOS_NULL;

        gstUSIMMAPDU.ulLeValue      = pstTpduHead->ucP3;
    }

    if (0 == pstTpduHead->ucChannel)
    {
        ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/
    }
    else
    {
        ulResult = USIMM_CglaDLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/
    }

    if (USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendTPDUHandle: USIMM_DLHandle Fail");/*打印错误*/

        return USIMM_SW_OTHER_ERROR;
    }

    pstRspData->usRspLen = (VOS_UINT16)gstUSIMMAPDU.ulLeValue;

    pstRspData->ucSW1       = gstUSIMMAPDU.ucSW1;

    pstRspData->ucSW2       = gstUSIMMAPDU.ucSW2;

    pstRspData->ucApduSW1   = gstUSIMMAPDU.ucApduSW1;

    pstRspData->ucApduSW2   = gstUSIMMAPDU.ucApduSW2;

    if (VOS_NULL != gstUSIMMAPDU.ulLeValue)
    {
        /*lint -e534*/
        VOS_MemCpy(pstRspData->aucRsp, gstUSIMMAPDU.aucRecvBuf, gstUSIMMAPDU.ulLeValue);
        /*lint +e534*/
    }

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  : USIMM_DLResetCard
功能描述  : 返回卡复位状态
输入参数  : ulResetType:复位卡类型
            plVoltageSwitchRst:电压切换结果
输出参数  : 无
返 回 值  : VOS_INT32，0表示复位成功，其余不成功
调用函数  : 无
被调函数  :
修订记录  :
1. 日    期   : 2008年8月4日
   作    者   : m00128685
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_DLResetCard(VOS_UINT32 ulResetType, VOS_INT32 *plVoltageSwitchRst)
{
    VOS_INT32                           lSCIResult = VOS_ERR;
    VOS_UINT32                          i;
    NV_USIMM_T1_CTRL_PARA_STRU          stT1CtrlPara;

    if (USIMM_RESET_CARD == ulResetType)
    {
        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                            WUEPS_PID_USIM,
                            WUEPS_PID_USIM,
                            USIMMDL_DRV_USIMMSCI_RST);

        (VOS_VOID)mdrv_sci_reset(COLD_RESET);

        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

        if(USIMM_DL_T_MODE_T1 == g_enUSIMMTMode)
        {
            /* 更新变量 */
            if(VOS_OK != USIMM_T1DLUpdateParaByATR(g_stUSIMMT1Para.enErrDetectMode,
                                                    g_stUSIMMT1Para.ulIFSC,
                                                    g_stUSIMMT1Para.ulIFSD))
            {
                USIMM_ERROR_LOG("USIMM_DLResetCard: USIMM_T1DLUpdateParaByATR fail!");
                return VOS_ERR;
            }

            /*lint -e534*/
            VOS_MemSet(&stT1CtrlPara, 0, sizeof(stT1CtrlPara));
            /*lint +e534*/

            /* 读NV项 */
            if(VOS_OK != NV_Read(en_NV_Item_Usimm_T1_Ctrl_PARA,
                                &stT1CtrlPara,
                                sizeof(stT1CtrlPara)))
            {
                /* 打印错误 */
                USIMM_ERROR_LOG("USIMM_DecideTMode:USIM Read T1 PARA NV error");

                /* NV读取失败，显式赋值为T0 */
                stT1CtrlPara.enTMode = USIMM_DL_T_MODE_T0;
            }

            /* 发送IFS命令,告诉卡UE接收能力 */
            if(VOS_OK != USIMM_T1SendIFSD_APDU((VOS_UINT8)stT1CtrlPara.ulDefaultIFSD))
            {
                USIMM_ERROR_LOG("USIMM_DLResetCard: USIMM_T1SendIFSD_APDU fail!");
                return VOS_ERR;
            }

            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                                WUEPS_PID_USIM,
                                WUEPS_PID_USIM,
                                USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_1);

            if(VOS_OK != mdrv_sci_switch_protocol((PROTOCOL_MODE_E)g_enUSIMMTMode))
            {
                /* 可维可测信息统计 */
                g_stT1StatisticInfo.ulProtocolSwitchFailCnt++;

                USIMM_WARNING_LOG("USIMM_DLResetCard:SET T MODE FAILED");
            }

            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);
        }
    }
    else
    {
        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                            WUEPS_PID_USIM,
                            WUEPS_PID_USIM,
                            USIMMDL_DRV_USIMMSCI_CLASS_SWITCH);

        lSCIResult = mdrv_sci_switch_class();

        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

        *plVoltageSwitchRst = lSCIResult;

        if (USIMM_SCI_SUCCESS == lSCIResult)      /*电压切换成功后需要延迟*/
        {
            USIMM_NORMAL_LOG("USIMM_DLResetCard: SIM Card Change the Voltage Successful");
        }
        else if (USIMM_SCI_NONEED_CHANGEVCC == lSCIResult)
        {
            USIMM_NORMAL_LOG("USIMM_DLResetCard: Card needn't Change the Voltage");
        }
        else                     /*电压切换失败按照无卡处理*/
        {
            USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_NOCARD);

            return VOS_ERR;
        }
    }

    for (i = 0; i < USIMM_GET_SCISTATUS_MAX; i++)        /*循环判断当前的卡复位情况*/
    {
        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                            WUEPS_PID_USIM,
                            WUEPS_PID_USIM,
                            USIMMDL_DRV_USIMMSCI_GET_CARD_STAU);

        lSCIResult = mdrv_sci_get_cardstatus(); /*如果复位成功则返回成功*/

        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

        if (SCI_CARD_STATE_BUSY != lSCIResult)
        {
            break;
        }
#if (VOS_OS_VER != VOS_WIN32)       /* PC Stub */
        HPA_USIMLowPowerLock(WUEPS_PID_USIM);
#endif

        (VOS_VOID)VOS_TaskDelay(20);     /*等待底软接收完成ATR和PPS过程*/

#if (VOS_OS_VER != VOS_WIN32)       /* PC Stub */
        HPA_USIMLowPowerUnLock(WUEPS_PID_USIM);
#endif
    }

    if (SCI_CARD_STATE_NOCARD == lSCIResult)
    {
        USIMM_ERROR_LOG("USIMM_DLResetCard: USIMM Could Not Find Any SIM Card!");

        USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_NOCARD);

        if (USIMM_RESET_CARD == ulResetType)
        {   
            mdrv_sci_save_recorddata(SCI_LOG_RESET_FAIL);
        }
        else
        {
            mdrv_sci_save_recorddata(SCI_LOG_VOL_SWITCH_FAIL);
        }

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : USIMM_TerminateADF
功能描述  : 选中其中的3GPP应用
输入参数  : 无
输出参数  : 无
返 回 值  : NA
修订记录  :
1. 日    期   : 2015年3月18日
    作    者   : zhuli
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_SendStatusApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucP1,
    VOS_UINT8                           ucP2,
    VOS_UINT8                           ucP3)
{
    USIMM_APDU_HEAD_STRU                stApduHead;

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_STATUS;
    stApduHead.ucP1         = ucP1;

    if (USIMM_STATUS_NO_DATA_RETURNED == ucP2)
    {
        stApduHead.ucP2         = USIMM_STATUS_NO_DATA_RETURNED;
        stApduHead.ucP3         = VOS_NULL;
    }
    else
    {
        stApduHead.ucP2         = ucP2;
        stApduHead.ucP3         = ucP3;
    }

    return USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                &stApduHead,
                                VOS_NULL_PTR,
                                VOS_NULL_PTR);
}

/*****************************************************************************
函 数 名  :USIMM_StatusPollingNeedFcp
功能描述  :发送STATUS命令要求返回FCP
输入参数  :无
输出参数  :pstRspData:STATUS命令返回的FCP内容
返 回 值  :VOS_OK/VOS_ERR

修订记录  :
1. 日    期   : 2015年3月7日
    作    者   : h00300778
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendStatusPollingApdu(
    USIMM_APDU_RSP_STRU                 *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;

    enAppType   = USIMM_CCB_GetMainAppType();

    stApduHead.ucChannel    = 0;
    stApduHead.ucINS        = CMD_INS_STATUS;

    stApduHead.ucP1         = USIMM_STATUS_NO_INDICATION;
    stApduHead.ucP2         = USIMM_STATUS_FCP_RETURNED;
    stApduHead.ucP3         = (VOS_UINT8)USIMM_CCB_GetCurFileInfo(enAppType)->usCurDFFcpLen;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    VOS_NULL_PTR,
                                    pstRspData);

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_SendOpenSpecificChannelCmd
功能描述  :发送打开指定CHANNEL ID的MANAGE CHANNEL命令的APDU
输入参数  :ucP2:P2参数
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR

修订记录  :
1. 日    期   : 2015年4月9日
    作    者   : h00300778
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendCloseChannelApdu(
    VOS_UINT8                           ucP2)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_APDU_RSP_STRU                 stRspData;

    stApduHead.ucChannel    = 0;
    stApduHead.ucINS        = CMD_INS_MANAGE_CHANNEL;
    stApduHead.ucP1         = USIMM_CLOSE_CHANNEL;
    stApduHead.ucP2         = ucP2;
    stApduHead.ucP3         = 0;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    VOS_NULL_PTR,
                                    &stRspData);

    /* 判断发送结果 */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendCloseChannelApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}


/*****************************************************************************
函 数 名  :USIMM_OpenChannelApdu
功能描述  :打开逻辑通道
输入参数  :无
输出参数  :pucChannelID: 返回逻辑通道号
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年3月18日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendOpenChannelApdu(
    VOS_UINT8                          *pucChannelID
)
{
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT8                           ucChannelID;
    VOS_UINT32                          ulResult;

    /* 下发manage打开逻辑通道,打开通道的时候在基本逻辑通道上，因此P2参数为0,P3参数填1，期望带回一个字节的channelID */
    stApduHead.ucChannel        = USIMM_APDU_BASECHANNEL;
    stApduHead.ucINS            = CMD_INS_MANAGE_CHANNEL;
    stApduHead.ucP1             = USIMM_OPEN_CHANNEL;
    stApduHead.ucP2             = USIMM_MANAGECH_ASSIGNED_CARD;
    stApduHead.ucP3             = 0x01;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    VOS_NULL_PTR,
                                    &stRspData);

    /*判断检查结果*/
    if (USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_SendOpenChannelApdu: USIMM_SendAPDUHandle Error");

        return ulResult;
    }

    ucChannelID = stRspData.aucRsp[0];

    /* 通道ID超出合法范围 */
    if (USIMM_CHANNEL_NUMBER_MAX <= ucChannelID)
    {
        USIMM_ERROR_LOG("USIMM_SendOpenChannelApdu: Channel ID is not valid.");

        (VOS_VOID)USIMM_SendCloseChannelApdu(ucChannelID);

        return USIMM_SW_ERR;
    }

    *pucChannelID = ucChannelID;

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_UpdateLFFile
功能描述  :更新记录文件的一条记录内容　
输入参数  :ucRecordNum: 记录号
           pucData:数据内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_UpdateRecord_APDU
           USIMM_CheckSW
修订记录  :
1. 日    期   : 2007年3月18日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_SendUpdateRecordApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucMode,
    VOS_UINT8                           ucRecordNum,
    VOS_UINT8                          *pucData,
    VOS_UINT8                           ucLen)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_UPDATE_RECORD;

    stApduHead.ucP1         = ucRecordNum;
    stApduHead.ucP2         = ucMode;
    stApduHead.ucP3         = ucLen;

    stApduData.ulDataLen    = ucLen;
    stApduData.pucData      = pucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stApduData,
                                    VOS_NULL_PTR);

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_UpdateTFFile
功能描述  :更新二进制文件内容　
输入参数  :usLen:   更新数据长度
           pucData:更新数据内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_UpdateBinary_APDU
           USIMM_CheckSW
修订记录  :
1. 日    期   : 2007年3月18日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_SendUpdateBinaryApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT16                          usLen,
    VOS_UINT8                          *pucData
)
{
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;
    VOS_UINT32                          ulResult = USIMM_SW_OK;
    VOS_UINT16                          usUpdateLen;
    VOS_UINT8                           ucP3 = 0;

    stApduHead.ucChannel    = ucChannelID;

    stApduHead.ucINS        = CMD_INS_UPDATE_BINARY;

    for (usUpdateLen=0; usUpdateLen<usLen; usUpdateLen += ucP3)
    {
        if(usLen > (0xFF + usUpdateLen))   /*判断当前的剩余数据长度*/
        {
            ucP3 = 0xFF;                            /*剩余数据大于255*/
        }
        else
        {
            ucP3 = (VOS_UINT8)(usLen - usUpdateLen);   /*剩余数据可以一次更新完毕*/
        }

        stApduHead.ucP1         = (VOS_UINT8)((usUpdateLen >> 8) & 0xFF);
        stApduHead.ucP2         = (VOS_UINT8)(usUpdateLen & 0xFF);
        stApduHead.ucP3         = ucP3;

        stApduData.ulDataLen    = ucP3;
        stApduData.pucData      = (pucData + usUpdateLen);

        ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                        &stApduHead,
                                        &stApduData,
                                        VOS_NULL_PTR);

        if (VOS_OK != ulResult)         /*判断发送结果*/
        {
            USIMM_ERROR_LOG("USIMM_UpdateTFFile:USIMM_UpdateBinary_APDU error");

            return ulResult;
        }
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_ReadLFFile
功能描述  :读取当前记录文件的指定记录内容
输入参数  :ucRecordNum:记录号
输出参数  :pucContent:读取的记录内容
返 回 值  : VOS_ERR
            VOS_OK
调用函数  :USIMM_ReadRecord_APDU
           USIMM_CheckSW
修订记录  :
1. 日    期   : 2007年3月18日
    作    者   : z00100318
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendReadRecordApdu(
    VOS_UINT8                           ucChannel,
    VOS_UINT8                           ucTotalNum,
    VOS_UINT8                           ucRecordLen,
    VOS_UINT8                           ucRecordIndex,
    VOS_UINT8                          *pucContent)
{
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT32                          i    = 1;
    VOS_UINT32                          ulTotalNum;

    if (ucTotalNum < ucRecordIndex)
    {
        USIMM_ERROR_LOG("USIMM_SendReadRecordApdu:ucRecordIndex Error");

        return USIMM_SW_ERR;
    }

    stApduHead.ucChannel    = ucChannel;
    stApduHead.ucINS        = CMD_INS_READ_RECORD;
    stApduHead.ucP2         = USIMM_RECORD_ABSOLTE;
    stApduHead.ucP3         = ucRecordLen;

    if(USIMM_READ_ALLRECORD == ucRecordIndex)
    {
        ulTotalNum = ucTotalNum;
    }
    else
    {
        i           = ucRecordIndex;

        ulTotalNum  = ucRecordIndex;
    }

    for(; i<=ulTotalNum; i++)
    {
        stApduHead.ucP1         = (VOS_UINT8)i;

        if(VOS_OK != USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                            &stApduHead,
                                            VOS_NULL_PTR,
                                            &stRspData))/*判断发送结果*/
        {
            USIMM_ERROR_LOG("USIMM_ReadLFFile: USIMM_ReadRecord_APDU Error");

            return USIMM_SW_SENDCMD_ERROR;
        }

        /*lint -e534 */
        VOS_MemCpy(pucContent, stRspData.aucRsp, ucRecordLen);
        /*lint +e534 */

        pucContent += ucRecordLen;
    }

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_SendReadBinaryApdu
功能描述  :读取二进制文件的指定长度的内容　
输入参数  :usLen:读取数据的长度
输出参数  :pucContent:读取数据内容
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_ReadBinary_APDU
           USIMM_CheckSW
修订记录  :
1. 日    期   : 2007年7月11日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_SendReadBinaryApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT16                          usOffset,
    VOS_UINT16                          usNeedLen,
    VOS_UINT8                           *pucContent)
{
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usReadedLen;
    VOS_UINT8                           ucP3 = 0;

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_READ_BINARY;

    for (usReadedLen=0; usReadedLen<usNeedLen; usReadedLen+=ucP3)
    {
        if ((usNeedLen - usReadedLen) > 0xFF)      /*最大更新长度*/
        {
            ucP3 = 0xFF;
        }
        else
        {
            ucP3 = (VOS_UINT8)(usNeedLen - usReadedLen);  /*剩余更新长度*/
        }

        stApduHead.ucP1         = (VOS_UINT8)(((usReadedLen+usOffset) >> 8) & 0xFF);
        stApduHead.ucP2         = (VOS_UINT8)((usReadedLen+usOffset) & 0xFF);
        stApduHead.ucP3         = ucP3;

        ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                        &stApduHead,
                                        VOS_NULL_PTR,
                                        &stRspData);

        if(VOS_OK != ulResult)/*判断更新发送结果*/
        {
            USIMM_ERROR_LOG("USIMM_SendReadBinaryApdu: USIMM_ReadBinary_APDU Error");

            return ulResult;
        }

        /*lint -e534*/
        VOS_MemCpy(pucContent + usReadedLen, stRspData.aucRsp, ucP3);
        /*lint +e534*/
    }

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_SendUnblockPinApdu
功能描述  :发送UNBLOCK PIN命令的APDU
输入参数  :enAppType:应用类型
           ucPinType:PIN码类型
           pucPukData:PUK码内容
           pucPinData:新PIN码内容
输出参数  :pstRspData:UNBLOCK PIN命令返回的内容
返 回 值  :VOS_OK/VOS_ERR

修订记录  :
1. 日    期   : 2015年4月7日
   作    者   : h00300778
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendUnblockPinApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucPinType,
    VOS_UINT8                          *pucPukData,
    VOS_UINT8                          *pucPinData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stPukData;
    USIMM_U8_LVDATA_STRU               *pstPinData = VOS_NULL_PTR;
    VOS_UINT8                           aucPukData[USIMM_PINNUMBER_LEN * 2];
    VOS_UINT8                           ucP3;

    if (VOS_NULL_PTR == pucPukData)
    {
        ucP3        = 0;
        pstPinData  = VOS_NULL_PTR;
    }
    else
    {
        ucP3        = USIMM_PINNUMBER_LEN * 2;
        pstPinData  = &stPukData;

        /*lint -e534 */
        /*填充APDU命令内容*/
        VOS_MemCpy(aucPukData, pucPukData, USIMM_PINNUMBER_LEN);
        VOS_MemCpy(aucPukData + USIMM_PINNUMBER_LEN, pucPinData, USIMM_PINNUMBER_LEN);
        /*lint +e534 */

        stPukData.ulDataLen = ucP3;
        stPukData.pucData   = aucPukData;
    }

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_UNBLOCK_PIN;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = ucPinType;
    stApduHead.ucP3         = ucP3;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    pstPinData,
                                    pstRspData);

    /* 判断发送结果 */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendUnblockPinApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_SendChangePinApdu
功能描述  :发送CHANGE PIN命令的APDU
输入参数  :enAppType:应用类型
           ucPinType:PIN码类型
           pucData:旧PIN码内容
           pucNewPinData:新PIN码内容
输出参数  :pstRspData:CHANGE PIN命令返回的内容
返 回 值  :VOS_OK/VOS_ERR

修订记录  :
1. 日    期   : 2015年4月7日
   作    者   : h00300778
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendChangePinApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucPinType,
    VOS_UINT8                          *pucPinData,
    VOS_UINT8                          *pucNewPinData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stPinData;
    VOS_UINT8                           aucPinData[USIMM_PINNUMBER_LEN * 2];

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_CHANGE_PIN;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = ucPinType;
    stApduHead.ucP3         = USIMM_PINNUMBER_LEN * 2;

    /*lint -e534 */
    /*填充APDU命令内容*/
    VOS_MemCpy(aucPinData, pucPinData, USIMM_PINNUMBER_LEN);

    VOS_MemCpy(aucPinData + USIMM_PINNUMBER_LEN, pucNewPinData, USIMM_PINNUMBER_LEN);
    /*lint +e534 */

    stPinData.ulDataLen = USIMM_PINNUMBER_LEN * 2;
    stPinData.pucData   = aucPinData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stPinData,
                                    pstRspData);

    /* 判断发送结果 */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendChangePinApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_SendVerifyPinApdu
功能描述  :发送VERIFY PIN命令的APDU
输入参数  :enAppType:应用类型
           ucCmdType:命令类型参数
           ucPinType:PIN码类型
           pucData:PIN码内容，可以为空
输出参数  :pstRspData:VERIFY PIN命令返回的内容
返 回 值  :VOS_OK/VOS_ERR

修订记录  :
1. 日    期   : 2015年4月7日
   作    者   : h00300778
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendVerifyPinApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucCmdType,
    VOS_UINT8                           ucPinType,
    VOS_UINT8                          *pucPinData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stPinData;
    USIMM_U8_LVDATA_STRU               *pstPinData;
    VOS_UINT8                           aucPinData[USIMM_PINNUMBER_LEN];
    VOS_UINT8                           ucP3;

    if (VOS_NULL_PTR == pucPinData)
    {
        ucP3 = VOS_NULL;

        pstPinData = VOS_NULL;
    }
    else
    {
        ucP3 = USIMM_PINNUMBER_LEN;

        /*lint -e534*/
        VOS_MemCpy(aucPinData, pucPinData, USIMM_PINNUMBER_LEN);
        /*lint +e534*/

        stPinData.ulDataLen = USIMM_PINNUMBER_LEN;
        stPinData.pucData   = aucPinData;

        pstPinData          = &stPinData;
    }

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = ucCmdType;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = ucPinType;
    stApduHead.ucP3         = ucP3;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    pstPinData,
                                    pstRspData);

    /* 判断发送结果 */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendVerifyPinApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_SendBSChallengeApdu
功能描述  :发送BASE STATION CHALLENGE命令的APDU
输入参数  :enAppType:应用类型
           ucP3:P3参数
           pucData:返回的数据
输出参数  :pstRspData:BASE STATION CHALLENGE命令返回的内容
返 回 值  :VOS_OK/VOS_ERR

修订记录  :
1. 日    期   : 2015年4月7日
   作    者   : h00300778
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendBSChallengeApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stBSChallengeData;

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_BASE_STATION_CHALLENGE;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = 0;
    stApduHead.ucP3         = ucP3;

    stBSChallengeData.ulDataLen    = ucP3;
    stBSChallengeData.pucData      = pucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stBSChallengeData,
                                    pstRspData);

    /* 判断发送结果 */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendBSChallengeApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  : USIMM_SendTerminalCapabilityApdu
功能描述  : 发送Terminal_Capability apdu
输入参数  : API层下发消息内容
输出参数  : 无
返 回 值  : VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年04月10日
   作    者   : c00299064
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendTerminalCapabilityApdu(
    VOS_UINT8                           ucP1,
    VOS_UINT8                           ucP2,
    USIMM_TERMINAL_CAPABILITY_STRU     *pstTerminalCapability)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;
    USIMM_APDU_RSP_STRU                 stRspData;

    /*lint -e534*/
    VOS_MemSet(&stApduHead, 0, sizeof(USIMM_APDU_HEAD_STRU));
    VOS_MemSet(&stApduData, 0, sizeof(stApduData));
    VOS_MemSet(&stRspData,  0, sizeof(stRspData));
    /*lint +e534*/

    /* 使用主通道 */
    stApduHead.ucChannel    = USIMM_BASE_CHANNEL_NUM;
    stApduHead.ucP1         = ucP1;
    stApduHead.ucP2         = ucP1;
    stApduHead.ucP3         = (VOS_UINT8)pstTerminalCapability->ulLen;
    stApduHead.ucINS        = CMD_INS_TERMINAL_CAPABILITY;

    stApduData.ulDataLen    = pstTerminalCapability->ulLen;

    stApduData.pucData      = pstTerminalCapability->aucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stApduData,
                                    &stRspData);

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_SendGenerateKeyVpmApdu
功能描述  :发送GENERATE KEY VPM 命令的APDU
输入参数  :enAppType:应用类型
           ucP3:P3参数
           pucData:返回的数据
输出参数  :pstRspData:GENERATE KEY VPM命令返回的内容
返 回 值  :VOS_OK/VOS_ERR

修订记录  :
1. 日    期   : 2015年4月9日
   作    者   : h00300778
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendGenerateKeyVpmApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stGenerateKeyVpmData;

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_GENERATE_KEY;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = 0;
    stApduHead.ucP3         = ucP3;

    stGenerateKeyVpmData.ulDataLen    = ucP3;
    stGenerateKeyVpmData.pucData      = pucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stGenerateKeyVpmData,
                                    pstRspData);

    /* 判断发送结果 */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendGenerateKeyVpmApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_SendUpdateSsdApdu
功能描述  :发送UPDATE SSD命令的APDU
输入参数  :enAppType:应用类型
           ucP3:P3参数
           pucData:返回的数据
输出参数  :pstRspData:UPDATE SSD命令返回的内容
返 回 值  :VOS_OK/VOS_ERR

修订记录  :
1. 日    期   : 2015年4月9日
   作    者   : h00300778
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendUpdateSsdApdu(
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stUpdateSsdData;

    stApduHead.ucChannel    = USIMM_APDU_BASECHANNEL;
    stApduHead.ucINS        = CMD_INS_UPDATE_SSD;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = 0;
    stApduHead.ucP3         = ucP3;

    stUpdateSsdData.ulDataLen    = ucP3;
    stUpdateSsdData.pucData      = pucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_UIM,
                                    &stApduHead,
                                    &stUpdateSsdData,
                                    VOS_NULL_PTR);

    /* 判断发送结果 */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendUpdateSsdApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_SendConfirmSsdApdu
功能描述  :发送CONFIRM SSD命令的APDU
输入参数  :enAppType:应用类型
           ucP3:P3参数
           pucData:返回的数据
输出参数  :pstRspData:UPDATE SSD命令返回的内容
返 回 值  :VOS_OK/VOS_ERR

修订记录  :
1. 日    期   : 2015年4月9日
   作    者   : h00300778
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendConfirmSsdApdu(
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stConfirmData;

    stApduHead.ucChannel    = USIMM_APDU_BASECHANNEL;
    stApduHead.ucINS        = CMD_INS_CONFIRM_SSD;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = 0;
    stApduHead.ucP3         = ucP3;

    stConfirmData.ulDataLen = ucP3;
    stConfirmData.pucData   = pucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_UIM,
                                    &stApduHead,
                                    &stConfirmData,
                                    VOS_NULL_PTR);

    /* 判断发送结果 */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendUpdateSsdApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_SendManageSsdApdu
功能描述  :发送MANAGE SSD命令的APDU
输入参数  :enAppType:应用类型
           ucP2:P2参数
           ucP3:P3参数
           pucData:返回的数据
输出参数  :pstRspData:UPDATE SSD命令返回的内容
返 回 值  :VOS_OK/VOS_ERR

修订记录  :
1. 日    期   : 2015年4月9日
   作    者   : h00300778
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendManageSsdApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucP2,
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stConfirmData;

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_MANAGE_SSD;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = ucP2;
    stApduHead.ucP3         = ucP3;

    stConfirmData.ulDataLen = ucP3;
    stConfirmData.pucData   = pucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_CSIM,
                                    &stApduHead,
                                    &stConfirmData,
                                    VOS_NULL_PTR);

    /* 判断发送结果 */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendManageSsdApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_SendAuthenticationApdu
功能描述  :发送AUTHENTICAION命令的APDU
输入参数  :enAppType:应用类型
           ucP1:P1参数
           ucP2:P2参数
           ucP3:P3参数
           pucData:返回的数据
输出参数  :pstRspData:STATUS命令返回的FCP内容
返 回 值  :VOS_OK/VOS_ERR

修订记录  :
1. 日    期   : 2015年3月7日
    作    者   : h00300778
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendAuthenticationApdu(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT8                           ucP1,
    VOS_UINT8                           ucP2,
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stAuthData;
    VOS_UINT32                          ulChannelNo;

    ulChannelNo = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ulChannelNo)
    {
        return VOS_ERR;
    }

    stApduHead.ucChannel    = (VOS_UINT8)ulChannelNo;
    stApduHead.ucINS        = CMD_INS_AUTHENTICATE;
    stApduHead.ucP1         = ucP1;
    stApduHead.ucP2         = ucP2;
    stApduHead.ucP3         = ucP3;

    stAuthData.ulDataLen    = ucP3;
    stAuthData.pucData      = pucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stAuthData,
                                    pstRspData);

    /* 判断发送结果 */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendAuthenticationApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}


/*****************************************************************************
函 数 名  :USIMM_DeactivateFile
功能描述  :DeactivateFile命令发送
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_SendDeactivateApdu(
    VOS_UINT8                           ucChannelID)
{
    USIMM_APDU_HEAD_STRU                stApduHead;

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_DEACTIVATE_FILE;
    stApduHead.ucP1         = 0x00;
    stApduHead.ucP2         = 0x00;
    stApduHead.ucP3         = 0x00;

    return USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                &stApduHead,
                                VOS_NULL_PTR,
                                VOS_NULL_PTR);   /*调用链路层处理函数*/
}

/*****************************************************************************
函 数 名  :USIMM_ActivateFile
功能描述  :ActivateFile命令发送
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_SendActivateApdu(
    VOS_UINT8                           ucChannelID)
{
    USIMM_APDU_HEAD_STRU                stApduHead;

    stApduHead.ucChannel    = ucChannelID;

    stApduHead.ucINS        = CMD_INS_ACTIVATE_FILE;
    stApduHead.ucP1         = 0x00;
    stApduHead.ucP2         = 0x00;
    stApduHead.ucP3         = 0x00;

    return USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                &stApduHead,
                                VOS_NULL_PTR,
                                VOS_NULL_PTR);   /*调用链路层处理函数*/
}

/*****************************************************************************
函 数 名  : USIMM_INIT_GetTermimalProfile
功能描述  : 初始化中获得终端参数
输入参数  : ucLen
            pucData
输出参数  : 无
返 回 值  : VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年04月10日
   作    者   : c00299064
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendTermimalProfileDownloadApdu(
    VOS_UINT8                           ucLen,
    VOS_UINT8                          *pucData
)
{
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;

    /*lint -e534*/
    VOS_MemSet(&stApduHead, 0, sizeof(USIMM_APDU_HEAD_STRU));
    VOS_MemSet(&stApduData, 0, sizeof(stApduData));
    /*lint +e534*/

    /* 使用主通道 */
    stApduHead.ucChannel    = USIMM_BASE_CHANNEL_NUM;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = 0;
    stApduHead.ucP3         = ucLen;
    stApduHead.ucINS        = CMD_INS_TERMINAL_PROFILE;

    stApduData.ulDataLen    = ucLen;

    stApduData.pucData      = pucData;

    return USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                &stApduHead,
                                &stApduData,
                                VOS_NULL_PTR);
}

/*****************************************************************************
函 数 名  : USIMM_INIT_SendStoreESNMEIDApdu
功能描述  : 初始化中保存ESNMEID
输入参数  : ucLen
            pucData
输出参数  : 无
返 回 值  : VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年04月10日
   作    者   : c00299064
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendStoreESNMEIDApdu(
    UICC_STORE_ESN_MEID_P1_UINT8        enDataType,
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                          *pucData,
    USIMM_APDU_RSP_STRU                *pstRspData
)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;

    /*lint -e534*/
    VOS_MemSet(&stApduHead, 0, sizeof(USIMM_APDU_HEAD_STRU));
    VOS_MemSet(&stApduData, 0, sizeof(stApduData));
    /*lint +e534*/

    /* 使用主通道 */
    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucP1         = enDataType;
    stApduHead.ucP2         = 0;
    stApduHead.ucP3         = USIMM_STORE_ESNMEID_MAX;
    stApduHead.ucINS        = CMD_INS_STORE_ESNMEID;

    stApduData.ulDataLen    = USIMM_STORE_ESNMEID_MAX;

    stApduData.pucData      = pucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stApduData,
                                    pstRspData);

    return ulResult;

}

/*****************************************************************************
函 数 名  : USIMM_SendComputIPApdu
功能描述  : 下发ComputeIP命令
输入参数  : ucLen
            pucData
输出参数  : 无
返 回 值  : VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年06月10日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendComputeIPApdu(
    VOS_UINT8                           ucChannelID,
    USIMM_COMPUTEIP_AUTH_ENUM_UINT32	enP1,
    VOS_UINT8                           ucP2,
    USIMM_U8_DATA_STRU                 *pstCmdData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;

    /*lint -e534*/
    VOS_MemSet(&stApduHead, 0, sizeof(USIMM_APDU_HEAD_STRU));
    VOS_MemSet(&stApduData, 0, sizeof(stApduData));
    /*lint +e534*/

    /* 使用主通道 */
    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucP1         = (VOS_UINT8)enP1;
    stApduHead.ucP2         = ucP2;
    stApduHead.ucP3         = pstCmdData->ucDataLen;
    stApduHead.ucINS        = CMD_INS_COMPUTE_IP_AUTH;

    stApduData.ulDataLen    = pstCmdData->ucDataLen;

    stApduData.pucData      = pstCmdData->aucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_CSIM,
                                    &stApduHead,
                                    &stApduData,
                                    pstRspData);

    return ulResult;
}

/*****************************************************************************
函 数 名  : USIMM_SendBCMCSApdu
功能描述  : 下发BCMCS命令
输入参数  : ucLen
            pucData
输出参数  : 无
返 回 值  : VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年06月10日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendBCMCSApdu(
    VOS_UINT8                           ucChannelID,
    USIMM_BCMCS_AUTH_ENUM_UINT32	    enP1,
    USIMM_U8_DATA_STRU                 *pstCmdData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;

    /*lint -e534*/
    VOS_MemSet(&stApduHead, 0, sizeof(USIMM_APDU_HEAD_STRU));
    VOS_MemSet(&stApduData, 0, sizeof(stApduData));
    /*lint +e534*/

    /* 使用主通道 */
    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucP1         = (VOS_UINT8)enP1;
    stApduHead.ucP2         = VOS_NULL;
    stApduHead.ucP3         = pstCmdData->ucDataLen;
    stApduHead.ucINS        = CMD_INS_BCMCS;

    stApduData.ulDataLen    = pstCmdData->ucDataLen;

    stApduData.pucData      = pstCmdData->aucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stApduData,
                                    pstRspData);

    /*SW需要特殊判断*/
    if (USIMM_BCMCS_DELETEBAK == enP1)
    {
        if ((0x94 == pstRspData->ucSW1)
           &&(0x02 == pstRspData->ucSW2))
        {
            ulResult = USIMM_SW_INVALID_BAKID;
        }

        if ((0x94 == pstRspData->ucSW1)
           &&(0x04 == pstRspData->ucSW2))
        {
            ulResult = USIMM_SW_INVALID_BCMCSFID;
        }
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  : USIMM_SendAppAuthApdu
功能描述  : 下发CDMA APP Auth命令
输入参数  : ucLen
            pucData
输出参数  : 无
返 回 值  : VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年06月10日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendAppAuthApdu(
    VOS_UINT8                           ucChannelID,
    USIMM_U8_DATA_STRU                 *pstCmdData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;

    /*lint -e534*/
    VOS_MemSet(&stApduHead, 0, sizeof(USIMM_APDU_HEAD_STRU));
    VOS_MemSet(&stApduData, 0, sizeof(stApduData));
    /*lint +e534*/

    /* 使用主通道 */
    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucP1         = VOS_NULL;
    stApduHead.ucP2         = VOS_NULL;
    stApduHead.ucP3         = pstCmdData->ucDataLen;
    stApduHead.ucINS        = CMD_INS_APP_AUTH;

    stApduData.ulDataLen    = pstCmdData->ucDataLen;

    stApduData.pucData      = pstCmdData->aucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stApduData,
                                    pstRspData);

    return ulResult;
}

#else

#include "usimmapdu.h"
#include "usimmdl.h"
#include "usimmt1dl.h"
#include "usimmglobal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_APDUMODULE_C
/*lint +e767*/

/*****************************************************************************
函 数 名  :USIMM_CheckSW
功能描述  :检查命令发送的结构
输入参数  :pstUSIMMAPDU

输出参数  :无
返 回 值  :USIMM_SWCHECK_ENUM_UINT16
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_CheckSW(USIMM_APDU_ST *pstUSIMMAPDU)
{
    USIMM_SWCHECK_ST                   *pstSWCheck;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          i;
    VOS_UINT8                           ucSW1;
    VOS_UINT8                           ucSW2;
    USIMM_SWCHECK_ENUM_UINT16           enResult = USIMM_SW_OTHER_ERROR;

    ucSW1 = pstUSIMMAPDU->ucSW1;
    ucSW2 = pstUSIMMAPDU->ucSW2;

    if (USIMM_SIM_CLA == pstUSIMMAPDU->aucAPDU[CLA])  /*根据卡类型判断*/
    {
        pstSWCheck = gausSimSWCheck;

        ulLen      = USIMM_SIMSW_MAXNUMBER;
    }
    else
    {
        pstSWCheck = gausUsimSWCheck;

        ulLen      = USIMM_USIMSW_MAXNUMBER;
    }

    for(i=0; i<ulLen; i++)
    {
        if(pstSWCheck[i].ucSW1 != ucSW1)        /*先判断SW1匹配*/
        {
            continue;
        }

        if((0xC0 == (ucSW2&0xF0))&&(0x63 == pstSWCheck[i].ucSW1))
        {
            if ((CMD_INS_VERIFY         == pstUSIMMAPDU->aucAPDU[INS])
                ||(CMD_INS_CHANGE_PIN   == pstUSIMMAPDU->aucAPDU[INS])
                ||(CMD_INS_UNBLOCK_PIN  == pstUSIMMAPDU->aucAPDU[INS])
                ||(CMD_INS_DISABLE_PIN  == pstUSIMMAPDU->aucAPDU[INS])
                ||(CMD_INS_ENABLE_PIN   == pstUSIMMAPDU->aucAPDU[INS]))
            {
                enResult = pstSWCheck[i].enResult;
            }
            else
            {
                enResult = USIMM_SW_WARNING;
            }

            break;
        }

        if((0xFF == pstSWCheck[i].ucSW2)||(ucSW2 == pstSWCheck[i].ucSW2))/*不需要判断SW2或者SW2匹配*/
        {
            enResult = pstSWCheck[i].enResult;

            break;
        }
    }

    if (USIMM_SW_OK_WITH_SAT == enResult)    /*SAT需要特殊处理*/
    {
        USIMM_INFO_LOG("USIMM_CheckSW: There is SAT Data Need Fetch");

        gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NEEDFETCH;

        if (0x00 == ucSW2)           /*代表当前获取主动命令长度256*/
        {
            gstUSIMMBaseInfo.usSATLen = 0x100;
        }
        else
        {
            gstUSIMMBaseInfo.usSATLen = ucSW2;
        }

        enResult = USIMM_SW_OK;
    }

    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAtt_flg)
    {
        if ((0x6F == ucSW1)&&(0x00 == ucSW2))
        {
            g_ulATTSpecErrSWCnt++;
        }
        else
        {
            g_ulATTSpecErrSWCnt = 0;
        }

        if (g_ulATTSpecErrSWCnt >= 3)                                 /*连续超过3次上报无卡*/
        {
            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType        = USIMM_CARD_NOCARD;        /*当前状态为无卡*/
            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService     = USIMM_CARD_SERVIC_ABSENT; /*当前状态为无卡*/

            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enStateChange     = USIMM_CARD_STATE_CHANGED;
        }
    }

    return (VOS_UINT32)enResult;
}

/*****************************************************************************
函 数 名  :USIMM_SelectFileByChannelID_APDU
功能描述  :通过指定的通道号发送选择文件的命令
输入参数  :ucChannelID:通道ID号
           ucP1:     命令参数1
           ucP2:     命令参数2
           ucP3:     命令参数3
           pucData:  命令数据
输出参数  :无
返 回 值  : VOS_ERR
            VOS_OK
调用函数  :USIMM_DLHandle

修订记录  :
1. 日    期   : 2013年5月15日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SelectFileByChannelID_APDU(VOS_UINT8 ucChannelID, USIMM_APDU_ST *pstApduInfo)
{
    VOS_UINT32                          ulResult;

    pstApduInfo->aucAPDU[CLA]   = pstApduInfo->aucAPDU[CLA]|ucChannelID; /*填充APDU命令头*/

    pstApduInfo->aucAPDU[INS]   = CMD_INS_SELECT;

    pstApduInfo->ulLcValue      = pstApduInfo->aucAPDU[P3];                  /*填充命令其它内容*/

    if(USIMM_SELECT_RETURN_FCP_TEMPLATE == pstApduInfo->aucAPDU[P2])
    {
        /* 此种场景下为case4 */
        pstApduInfo->ulLeValue      = USIMM_LE_MAX_LEN;
    }
    else
    {
        /* case3 */
        pstApduInfo->ulLeValue      = VOS_NULL;
    }

    ulResult = USIMM_DLHandle(pstApduInfo);/*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SelectFile_APDU:USIMM_DLHandle error");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_SelectFile_APDU
功能描述  :发送选择文件的命令
输入参数  :ucP1:     命令参数1
           ucP2:     命令参数2
           ucP3:     命令参数3
           pucData:  命令数据
输出参数  :无
返 回 值  : VOS_ERR
            VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_SelectFile_APDU(USIMM_APDU_ST   *pstApduInfo)
{
    return USIMM_SelectFileByChannelID_APDU(0, pstApduInfo);
}

/*****************************************************************************
函 数 名  :USIMM_ReselectFileAPDU
功能描述  :尝试多次进行选文件操作
输入参数  :pstApduInfo:Select File的APDU
输出参数  :无
返 回 值  :VOS_ERR/VOS_OK
修订记录  :
1. 日    期   : 2013年6月17日
   作    者   : g47350
   修改内容   : 新增加函数
*****************************************************************************/
VOS_UINT32 USIMM_ReselectFileAPDU(USIMM_APDU_ST   *pstApduInfo)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulResult;

    for (ulIndex = 0; ulIndex < USIMM_SELECT_MAX_TIME; ulIndex++)
    {
        /* 不带FCP情况下连续出错则采用带FCP的方式尝试 */
        if ((USIMM_SELECT_NO_DATA_RETURNED == pstApduInfo->aucAPDU[P2])
            && ((USIMM_SELECT_MAX_TIME - 1) == ulIndex))
        {
            pstApduInfo->aucAPDU[P2] = USIMM_SELECT_RETURN_FCP_TEMPLATE;
        }

        ulResult = USIMM_SelectFile_APDU(pstApduInfo);

        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_ReselectFileAPDU: USIMM_SelectFile_APDU fail.");

            return USIMM_SW_SENDCMD_ERROR;
        }

        ulResult = USIMM_CheckSW(pstApduInfo);

        /* 状态字为Warning或Technical Problem则再次进行选文件操作 */
        if ((USIMM_SW_WARNING == ulResult) || (USIMM_SW_TECH_ERROR == ulResult))
        {
            continue;
        }

        break;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_StatusByID_APDU
功能描述  :通过指定的通道号Status命令发送
输入参数  :ucP1:       命令参数1
           ucP2:       命令参数2
           ucP3:       命令参数3
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle

修订记录  :
1. 日    期   : 2013年5月15日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_StatusByChannelID_APDU(VOS_UINT8 ucChannelID, VOS_UINT8 ucP1,VOS_UINT8 ucP2,VOS_UINT8 ucP3)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|ucChannelID|0x80; /*填充APDU命令头*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_STATUS;

    gstUSIMMAPDU.aucAPDU[P1]  = ucP1;

    gstUSIMMAPDU.aucAPDU[P2]  = ucP2;

    gstUSIMMAPDU.aucAPDU[P3]  = ucP3;

    gstUSIMMAPDU.ulLcValue = 0x00;                              /*填充命令其它内容*/

    if((ucP3 == 0x00)&&(ucP2 != 0x0C))
    {
        gstUSIMMAPDU.ulLeValue = 0x100;
    }
    else
    {
        gstUSIMMAPDU.ulLeValue = ucP3;
    }


    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_STATUS_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_Status_APDU
功能描述  :Status命令发送
输入参数  :ucP1:       命令参数1
           ucP2:       命令参数2
           ucP3:       命令参数3
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_Status_APDU(VOS_UINT8 ucP1,VOS_UINT8 ucP2,VOS_UINT8 ucP3)
{
    return USIMM_StatusByChannelID_APDU(0, ucP1, ucP2, ucP3);
}

/*****************************************************************************
函 数 名  :USIMM_ReadBinary_APDU
功能描述  :ReadBinary命令发送
输入参数  :usOffset:读取内容偏移
           ucP3:     读取内容长度
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_ReadBinary_APDU(VOS_UINT16 usOffset, VOS_UINT8 ucP3)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;

    (VOS_VOID)VOS_MemSet(&gstUSIMMAPDU, 0, sizeof(gstUSIMMAPDU));

    for (i = 0; i < 2; i++)
    {
        gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*填充APDU命令头*/

        gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_READ_BINARY;

        gstUSIMMAPDU.aucAPDU[P1]  = (VOS_UINT8)((usOffset>>8)&0xFF);

        gstUSIMMAPDU.aucAPDU[P2]  = (VOS_UINT8)(usOffset&0xFF);

        gstUSIMMAPDU.aucAPDU[P3]  = ucP3;

        gstUSIMMAPDU.ulLcValue    = 0x00;           /*填充命令其它内容*/

        gstUSIMMAPDU.ulLeValue    = ucP3;

        ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

        if (USIMM_DL_SUCESS != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_Status_APDU: USIMM_DLHandle is Failed");/*打印错误*/

            continue;
        }

        ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

        if (USIMM_SW_OK != ulResult)
        {
            continue;
        }
        else
        {
            break;
        }
    }


    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_UpdateBinary_APDU
功能描述  :UpdateBinary命令发送
输入参数  :usOffset:更新内容偏移
           ucP3:   更新内容长度
           pucData:更新数据内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_UpdateBinary_APDU(VOS_UINT16 usOffset, VOS_UINT8 ucP3, VOS_UINT8* pucData)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;

    for (i = 0; i < 2; i++)
    {
        /*填充APDU命令头*/
        gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA;

        gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_UPDATE_BINARY;

        gstUSIMMAPDU.aucAPDU[P1]  = (VOS_UINT8)((usOffset>>0x08)&0xFF);

        gstUSIMMAPDU.aucAPDU[P2]  = (VOS_UINT8)(usOffset&0xFF);

        gstUSIMMAPDU.aucAPDU[P3]  = ucP3;

        /*lint -e534*/
        VOS_MemCpy(gstUSIMMAPDU.aucSendBuf, pucData, ucP3);/*填充APDU命令内容*/
        /*lint +e534*/

        gstUSIMMAPDU.ulLcValue   = ucP3;                  /*填充命令其它内容*/

        gstUSIMMAPDU.ulLeValue   = 0x00;

        ulResult = USIMM_DLHandle(&gstUSIMMAPDU);/*调用链路层处理函数*/

        if(USIMM_DL_SUCESS != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_UpdateBinary_APDU: USIMM_DLHandle is Failed");/*打印错误*/

            continue;
        }

        ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

        if (USIMM_SW_OK != ulResult)
        {
            continue;
        }
        else
        {
            break;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_ReadRecord_APDU
功能描述  :ReadRecord命令发送
输入参数  :ucRecordNum:读取记录号
           ucMode:        读取方式
           ucLen:          读取数据长度
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_ReadRecord_APDU(VOS_UINT8 ucRecordNum, VOS_UINT8 ucMode, VOS_UINT8 ucLen)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;

    (VOS_VOID)VOS_MemSet(&gstUSIMMAPDU, 0, sizeof(gstUSIMMAPDU));

    for (i = 0; i < 2; i++)
    {
        gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*填充APDU命令头*/

        gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_READ_RECORD;

        gstUSIMMAPDU.aucAPDU[P1]  = ucRecordNum;

        gstUSIMMAPDU.aucAPDU[P2]  = ucMode;

        gstUSIMMAPDU.aucAPDU[P3]  = ucLen;

        gstUSIMMAPDU.ulLcValue    = 0x00;           /*填充命令其它内容*/

        gstUSIMMAPDU.ulLeValue    = ucLen;

        ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

        if (USIMM_DL_SUCESS != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_ReadRecord_APDU: USIMM_DLHandle is Failed");/*打印错误*/

            continue;
        }

        ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

        if (USIMM_SW_OK != ulResult)
        {
            continue;
        }
        else
        {
            break;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_UpdateRecord_APDU
功能描述  :UpdateRecord命令发送
输入参数  :ucRecordNum:更新记录号
           ucMode:        更新方式
           ucLen:          更新数据长度
           pucData:      更新数据内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_UpdateRecord_APDU(VOS_UINT8 ucRecordNum, VOS_UINT8 ucMode, VOS_UINT8 ucLen, VOS_UINT8* pucData)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;


    for (i = 0; i < 2; i++)
    {
        gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*填充APDU命令头*/

        gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_UPDATE_RECORD;

        gstUSIMMAPDU.aucAPDU[P1]  = ucRecordNum;

        gstUSIMMAPDU.aucAPDU[P2]  = ucMode;

        gstUSIMMAPDU.aucAPDU[P3]  = ucLen;

        /*lint -e534*/
        VOS_MemCpy(gstUSIMMAPDU.aucSendBuf, pucData, ucLen);/*填充APDU命令内容*/
        /*lint +e534*/

        gstUSIMMAPDU.ulLcValue = ucLen;                              /*填充命令其它内容*/

        gstUSIMMAPDU.ulLeValue = 0x00;

        ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

        if(USIMM_DL_SUCESS != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_UpdateRecord_APDU: USIMM_DLHandle is Failed");/*打印错误*/

            continue;
        }

        ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

        if (USIMM_SW_OK != ulResult)
        {
            continue;
        }
        else
        {
            break;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_Search_APDU
功能描述  :Search命令发送
输入参数  :ucP1:     命令参数1
           ucP2:     命令参数2
           ucP3:     命令参数3
           pucData:  命令数据
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_Search_APDU(VOS_UINT8 ucP1, VOS_UINT8 ucP2, VOS_UINT8 ucP3, VOS_UINT8* pucData)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*填充APDU命令头*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_SEARCH_RECORD;

    gstUSIMMAPDU.aucAPDU[P1]  = ucP1;

    gstUSIMMAPDU.aucAPDU[P2]  = ucP2;

    gstUSIMMAPDU.aucAPDU[P3]  = ucP3;

    /*lint -e534*/
    VOS_MemCpy(gstUSIMMAPDU.aucSendBuf, pucData, ucP3);/*填充APDU命令内容*/
    /*lint +e534*/

    gstUSIMMAPDU.ulLcValue = ucP3;                              /*填充命令其它内容*/

    gstUSIMMAPDU.ulLeValue = 0x00;

    /* 此种场景下为case4 */
    gstUSIMMAPDU.ulLeValue = USIMM_LE_MAX_LEN;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Search_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_Increace_APDU
功能描述  :Increace命令发送
输入参数  :ucLen:       数据长度
           pucData:   数据内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_Increase_APDU(VOS_UINT8 ucLen, VOS_UINT8* pucData)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*填充APDU命令头*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_INCREASE;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P3]  = ucLen;

    /*lint -e534*/
    VOS_MemCpy(gstUSIMMAPDU.aucSendBuf, pucData, ucLen);/*填充APDU命令内容*/
    /*lint +e534*/

    gstUSIMMAPDU.ulLcValue = ucLen;                              /*填充命令其它内容*/

    /* 此种场景下为case4 */
    gstUSIMMAPDU.ulLeValue = USIMM_LE_MAX_LEN;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Increase_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_VerifyPIN_APDU
功能描述  :VerifyPIN命令发送
输入参数  :ucPINType:  PIN类型
           pucPINData: PIN 数据
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_PINVerify_APDU(VOS_UINT8 ucCmdType,VOS_UINT8 ucPINType, VOS_UINT8* pucPINData)
{
    VOS_UINT32 ulResult;
    VOS_UINT8  ucLen;

    if(VOS_NULL_PTR == pucPINData)  /*获取当前的PIN剩余次数*/
    {
        ucLen = 0x00;
    }
    else                                                /*校验PIN*/
    {
        ucLen = 0x08;
    }

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*填充APDU命令头*/

    gstUSIMMAPDU.aucAPDU[INS] = ucCmdType;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = ucPINType;

    gstUSIMMAPDU.aucAPDU[P3]  = ucLen;

    if(8 == ucLen)
    {
        /*lint -e668 -e534 修改人: j00174725; 检视人: xucheng */
        VOS_MemCpy(gstUSIMMAPDU.aucSendBuf, pucPINData, 0x08);/*填充APDU命令内容*/
        /*lint +e668 +e534 修改人: j00174725; 检视人: xucheng */
    }

    gstUSIMMAPDU.ulLcValue = ucLen;                              /*填充命令其它内容*/

    gstUSIMMAPDU.ulLeValue = 0x00;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_PINVerify_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_ChangePIN_APDU
功能描述  :ChangePIN命令发送
输入参数  :ucPINType: PIN类型
           pucOldPIN: 旧PIN
           pucNewPIN:新PIN
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_ChangePIN_APDU(VOS_UINT8 ucPINType, VOS_UINT8* pucOldPIN, VOS_UINT8* pucNewPIN)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*填充APDU命令头*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_CHANGE_PIN;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = ucPINType;

    gstUSIMMAPDU.aucAPDU[P3]  = 0x10;

    /*lint -e534*/
    VOS_MemCpy(&gstUSIMMAPDU.aucSendBuf[0], pucOldPIN, 0x08);/*填充APDU命令内容*/

    VOS_MemCpy(&gstUSIMMAPDU.aucSendBuf[8], pucNewPIN, 0x08);
    /*lint +e534*/

    gstUSIMMAPDU.ulLcValue = 0x10;                              /*填充命令其它内容*/

    gstUSIMMAPDU.ulLeValue = 0x00;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ChangePIN_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_UnblockPIN_APDU
功能描述  :UnblockPIN命令发送
输入参数  :ucPINType:  PIN类型
           pucPUKData: PUK 数据
           pucPINData: PIN 数据
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_UnblockPIN_APDU(VOS_UINT8 ucPINType, VOS_UINT8* pucPUKData, VOS_UINT8* pucPINData)
{
    VOS_UINT32 ulResult;
    VOS_UINT8  ucP3;

    if(VOS_NULL_PTR == pucPUKData)
    {
        ucP3 = 0x00;
    }
    else
    {
        ucP3 = 0x10;
    }

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*填充APDU命令头*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_UNBLOCK_PIN;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = ucPINType;

    gstUSIMMAPDU.aucAPDU[P3]  = ucP3;

    if(0x00  != ucP3)
    {
        /*lint -e668 -e534 修改人: j00174725; 检视人: xucheng */
        VOS_MemCpy(&gstUSIMMAPDU.aucSendBuf[0], pucPUKData, 0x08);/*填充APDU命令内容*/
        /*lint +e668 修改人: j00174725; 检视人: xucheng */

        VOS_MemCpy(&gstUSIMMAPDU.aucSendBuf[8], pucPINData, 0x08);
        /*lint +e534*/
    }

    gstUSIMMAPDU.ulLcValue = ucP3;                              /*填充命令其它内容*/

    gstUSIMMAPDU.ulLeValue = 0;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_UnblockPIN_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_DeactivateFile_APDU
功能描述  :DeactivateFile命令发送
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_DeactivateFile_APDU(VOS_VOID)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*填充APDU命令头*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_DEACTIVATE_FILE;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P3]  = 0x00;

    gstUSIMMAPDU.ulLcValue    = 0x00;                /*填充命令其它内容*/

    gstUSIMMAPDU.ulLeValue    = 0x00;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_DeactivateFile_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_ActivateFile_APDU
功能描述  :ActivateFile命令发送
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_ActivateFile_APDU(VOS_VOID)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*填充APDU命令头*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_ACTIVATE_FILE;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P3]  = 0x00;

    gstUSIMMAPDU.ulLcValue    = 0x00;           /*填充命令其它内容*/

    gstUSIMMAPDU.ulLeValue    = 0x00;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ActivateFile_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_Authentication_APDU
功能描述  :Authentication命令发送
输入参数  :ucMode: 鉴权类型
           pucRand:随机数
           pucAuth:鉴权数据
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_Authentication_APDU(VOS_UINT8 ucP1, VOS_UINT8 ucMode, VOS_UINT8 *pucData, VOS_UINT32 ulDataLen)
{
    VOS_UINT32                          ulResult;

    /* 参数检测 */
    if (USIMM_APDU_MAXLEN <= ulDataLen)
    {
        USIMM_ERROR_LOG("USIMM_Authentication_APDU: ulDataLen is too big.");

        return VOS_ERR;
    }

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*填充APDU命令头*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_AUTHENTICATE;

    gstUSIMMAPDU.aucAPDU[P1]  = ucP1;

    gstUSIMMAPDU.aucAPDU[P2]  = ucMode;

    gstUSIMMAPDU.aucAPDU[P3]  = (VOS_UINT8)ulDataLen;

    /*lint -e534*/
    VOS_MemCpy(&gstUSIMMAPDU.aucSendBuf[0], pucData, ulDataLen);/*填充随机数内容*/
    /*lint +e534*/

    gstUSIMMAPDU.ulLcValue = gstUSIMMAPDU.aucAPDU[P3];      /*填充命令其它内容*/

    /* 此种场景下为case4 */
    gstUSIMMAPDU.ulLeValue = USIMM_LE_MAX_LEN;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Authentication_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_TermimalProfile_APDU
功能描述  :TermimalProfile命令发送
输入参数  :ucLen:       数据长度
           pucData:   数据内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_TermimalProfile_APDU(VOS_UINT8 ucLen, VOS_UINT8* pucData)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*填充APDU命令头*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_TERMINAL_PROFILE;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P3]  = ucLen;

    /*lint -e534*/
    VOS_MemCpy(&gstUSIMMAPDU.aucSendBuf[0], pucData, ucLen);/*填充APDU命令内容*/
    /*lint +e534*/

    gstUSIMMAPDU.ulLcValue = ucLen;                              /*填充命令其它内容*/

    gstUSIMMAPDU.ulLeValue = 0x00;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_TermimalProfile_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_Envelope_APDU
功能描述  :Envelope命令发送
输入参数  :ucLen:       数据长度
           pucData:   数据内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK

调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_Envelope_APDU(VOS_UINT8 ucLen, VOS_UINT8* pucData)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*填充APDU命令头*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_ENVELOPE;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P3]  = ucLen;

    /*lint -e534*/
    VOS_MemCpy(&gstUSIMMAPDU.aucSendBuf[0], pucData, ucLen);/*填充APDU命令内容*/
    /*lint +e534*/

    gstUSIMMAPDU.ulLcValue = ucLen;                              /*填充命令其它内容*/

    /* 此种场景下为case4 */
    gstUSIMMAPDU.ulLeValue = USIMM_LE_MAX_LEN;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Envelope_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_Fetch_APDU
功能描述  :Fetch命令发送
输入参数  :ucLen:       数据长度
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_Fetch_APDU(VOS_UINT8 ucLen)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*填充APDU命令头*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_FETCH;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P3]  = ucLen;

    gstUSIMMAPDU.ulLcValue = 0x00;                              /*填充命令其它内容*/

    if(ucLen == 0x00)
    {
        gstUSIMMAPDU.ulLeValue = 0x100;
    }
    else
    {
        gstUSIMMAPDU.ulLeValue = ucLen;
    }

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Fetch_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
函 数 名  :USIMM_TerminalResponse_APDU
功能描述  :TerminalResponse命令发送
输入参数  :ucLen:       数据长度
           pucData:   数据内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_TerminalResponse_APDU(VOS_UINT8 ucLen, VOS_UINT8* pucData)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*填充APDU命令头*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_TERMINAL_RESPONSE;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P3]  = ucLen;

    /*lint -e534*/
    VOS_MemCpy(&gstUSIMMAPDU.aucSendBuf[0], pucData, ucLen);/*填充APDU命令内容*/
    /*lint +e534*/

    gstUSIMMAPDU.ulLcValue = ucLen;                              /*填充命令其它内容*/

    gstUSIMMAPDU.ulLeValue = 0x00;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_TerminalResponse_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_FormatCsimApdu
功能描述  :构造CSIM命令的APDU数据
输入参数  :pstMsg:      输入数据结构
           pstUsimmApdu:输出APDU结构
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :VOS_MemCpy

 修订记录  :
1. 日    期   : 2010年03月19日
   作    者   : m00128685
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_FormatCsimApdu(USIMM_GACCESS_REQ_STRU *pstMsg,
                                            USIMM_APDU_ST          *pstUsimmApdu)
{
    /* 如果数据长度小于四字节，则是出错的场景 */
    if(pstMsg->usDataLen < T1_CASE1_APDU_LEN)
    {
        /* 打印错误 */
        USIMM_ERROR_LOG("USIMM_FormatCsimApdu: data len is less than 4 bytes");

        return VOS_ERR;
    }

    /* CASE1和CASE2的情况 */
    if ( (T1_CASE1_APDU_LEN == pstMsg->usDataLen)
        || (pstMsg->usDataLen == sizeof(pstUsimmApdu->aucAPDU)))/*无Lc字段*/
    {
        USIMM_INFO_LOG("USIMM_FormatCsimApdu: The Command have any Lc Data");

        /* copy apdu */
        /*lint -e534*/
        VOS_MemCpy(pstUsimmApdu->aucAPDU, pstMsg->aucContent, pstMsg->usDataLen);
        /*lint +e534*/

        pstUsimmApdu->ulLcValue = 0;

        pstUsimmApdu->ulLeValue = pstUsimmApdu->aucAPDU[P3];  /*Le的数据可能为0*/

        return VOS_OK;
    }

    /* 数据填入对应的结构体 */
    /*lint -e534*/
    VOS_MemCpy(pstUsimmApdu->aucAPDU, pstMsg->aucContent, sizeof(pstUsimmApdu->aucAPDU));
    /*lint +e534*/

    /* 判断P3字节指示是否正确 */
    if(pstMsg->usDataLen < (pstUsimmApdu->aucAPDU[P3] + USIMM_APDU_HEADLEN))
    {
        USIMM_ERROR_LOG("USIMM_FormatCsimApdu: LC is wrong");/*打印错误*/

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(pstUsimmApdu->aucSendBuf, (pstMsg->aucContent + USIMM_APDU_HEADLEN), pstUsimmApdu->aucAPDU[P3]);
    /*lint +e534*/

    pstUsimmApdu->ulLcValue = pstUsimmApdu->aucAPDU[P3];

    /* 数据过长 */
    if(pstMsg->usDataLen > (USIMM_APDU_HEADLEN + pstUsimmApdu->aucAPDU[P3] + 1))
    {
        USIMM_ERROR_LOG("USIMM_FormatCsimApdu: the data len is more");/*打印错误*/

        return VOS_ERR;
    }

    /* case4场景，有一字节的LE字段 */
    if(pstMsg->usDataLen == (USIMM_APDU_HEADLEN + pstUsimmApdu->aucAPDU[P3] + 1))
    {
        pstUsimmApdu->ulLeValue = pstMsg->aucContent[pstMsg->usDataLen - 1];
    }
    else
    {
        /* case3场景 */
        pstUsimmApdu->ulLeValue = 0;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_FormatIsdbApdu
功能描述  :构造ISDB命令的APDU数据
输入参数  :pstMsg:      输入数据结构
           pstUsimmApdu:输出APDU结构
输出参数  :USIMM_APDU_ST          *pstUsimmApdu
返 回 值  :VOS_ERR/VOS_OK
修订记录  :
1. 日    期   : 2012年08月29日
   作    者   : H59254
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_FormatIsdbApdu(
    USIMM_ISDB_ACCESS_REQ_STRU         *pstMsg,
    USIMM_APDU_ST                      *pstUsimmApdu)
{
    /* 如果数据长度小于四字节，则是出错的场景 */
    if(pstMsg->usDataLen < T1_CASE1_APDU_LEN)
    {
        /* 打印错误 */
        USIMM_ERROR_LOG("USIMM_FormatIsdbApdu: data len is less than 4 bytes");

        return VOS_ERR;
    }

    /* CASE1和CASE2的情况 */
    if ( (T1_CASE1_APDU_LEN == pstMsg->usDataLen)
        || (pstMsg->usDataLen == sizeof(pstUsimmApdu->aucAPDU)))/*无Lc字段*/
    {
        USIMM_INFO_LOG("USIMM_FormatIsdbApdu: The Command have any Lc Data");

        /* copy apdu */
        /*lint -e534*/
        VOS_MemCpy(pstUsimmApdu->aucAPDU, pstMsg->aucContent, pstMsg->usDataLen);
        /*lint +e534*/

        pstUsimmApdu->ulLcValue = 0;

        pstUsimmApdu->ulLeValue = pstUsimmApdu->aucAPDU[P3];  /*Le的数据可能为0*/

        return VOS_OK;
    }

    /* 数据填入对应的结构体 */
    /*lint -e420 -e534 */
    VOS_MemCpy(pstUsimmApdu->aucAPDU, pstMsg->aucContent, sizeof(pstUsimmApdu->aucAPDU));
    /*lint +e420 +e534 */

    /* 判断P3字节指示是否正确 */
    if(pstMsg->usDataLen < (pstUsimmApdu->aucAPDU[P3] + USIMM_APDU_HEADLEN))
    {
        USIMM_ERROR_LOG("USIMM_FormatIsdbApdu: LC is wrong");/*打印错误*/

        return VOS_ERR;
    }

    /*lint -e416 -e534 */
    VOS_MemCpy(pstUsimmApdu->aucSendBuf, (pstMsg->aucContent + USIMM_APDU_HEADLEN), pstUsimmApdu->aucAPDU[P3]);
    /*lint +e416 +e534 */

    pstUsimmApdu->ulLcValue = pstUsimmApdu->aucAPDU[P3];

    /* 数据过长 */
    if(pstMsg->usDataLen > (USIMM_APDU_HEADLEN + pstUsimmApdu->aucAPDU[P3] + 1))
    {
        USIMM_ERROR_LOG("USIMM_FormatIsdbApdu: the data len is more");/*打印错误*/

        return VOS_ERR;
    }

    /* case4场景，有一字节的LE字段 */
    if(pstMsg->usDataLen == (USIMM_APDU_HEADLEN + pstUsimmApdu->aucAPDU[P3] + 1))
    {
        pstUsimmApdu->ulLeValue = pstMsg->aucContent[pstMsg->usDataLen - 1];
    }
    else
    {
        /* case3场景 */
        pstUsimmApdu->ulLeValue = 0;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_FormatStandardApdu
功能描述  :将传进来的数据构造成标准的APDU数据
输入参数  :pucData:     数据内容
           usLen:       数据长度
           pstUsimmApdu:输出APDU结构
输出参数  :USIMM_APDU_ST          *pstUsimmApdu
返 回 值  :VOS_ERR/VOS_OK
修订记录  :
1. 日    期   : 2013年05月15日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_FormatStandardApdu(VOS_UINT8 *pucData, VOS_UINT16 usLen, USIMM_APDU_ST *pstUsimmApdu)
{
    /* 无Lc字段 */
    if (usLen <= sizeof(pstUsimmApdu->aucAPDU))
    {
        USIMM_INFO_LOG("USIMM_FormatStandardApdu: The Command have any Lc Data");

        /* 当APDU为case1时，Le字段为0 */
        pstUsimmApdu->aucAPDU[P3] = 0;

        /*lint -e534*/
        VOS_MemCpy(pstUsimmApdu->aucAPDU, pucData, usLen);
        /*lint +e534*/

        pstUsimmApdu->ulLcValue = 0;

        /* Le的数据可能为0 */
        pstUsimmApdu->ulLeValue = pstUsimmApdu->aucAPDU[P3];
    }
    /* 有Lc字段 */
    else if ((usLen > sizeof(pstUsimmApdu->aucAPDU))
             &&(usLen <= (sizeof(pstUsimmApdu->aucAPDU)+USIMM_APDU_MAXLEN)))
    {
        USIMM_INFO_LOG("USIMM_FormatStandardApdu: The Command have Lc Data");

        /* 判断Lc字段是否正确 */
        if ((sizeof(pstUsimmApdu->aucAPDU) + pucData[P3]) > usLen)
        {
            USIMM_ERROR_LOG("USIMM_FormatStandardApdu: Lc is Error");

            return VOS_ERR;
        }

        /*lint -e534*/
        VOS_MemCpy(pstUsimmApdu->aucAPDU, pucData, sizeof(pstUsimmApdu->aucAPDU));

        /*lint -e416*/
        VOS_MemCpy(pstUsimmApdu->aucSendBuf,
                   pucData+sizeof(pstUsimmApdu->aucAPDU),
                   pstUsimmApdu->aucAPDU[P3]);
        /*lint +e534*/
        /*lint +e416*/
        pstUsimmApdu->ulLcValue = pstUsimmApdu->aucAPDU[P3];

        /* 数据过长 */
        if(usLen > (USIMM_APDU_HEADLEN + pstUsimmApdu->aucAPDU[P3] + 1))
        {
            USIMM_ERROR_LOG("USIMM_FormatCsimApdu: the data len is more");/*打印错误*/

            return VOS_ERR;
        }

        if(usLen == (USIMM_APDU_HEADLEN + pstUsimmApdu->aucAPDU[P3] + 1))
        {
            /* case4 */
            pstUsimmApdu->ulLeValue = pucData[usLen - 1];
        }
        else
        {
            /* case3 */
            pstUsimmApdu->ulLeValue = 0;
        }
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_FormatStandardApdu: The Command Type is Error");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_Manage_Channel_APDU
功能描述  :通道管理命令发送
输入参数  :ucP1:       命令参数1
           ucP2:       命令参数2
           ucP3:       命令参数3
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2013年5月14日
   作    者   : j00168360
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_Manage_Channel_APDU(VOS_UINT8 ucP1, VOS_UINT8 ucP2, VOS_UINT8 ucP3)
{
    VOS_UINT32 ulResult;

    /* 在对应的逻辑通道上发 在打开逻辑通道时:p2为0，关闭逻辑通道时:p2为对应逻辑通道号 */
    gstUSIMMAPDU.aucAPDU[CLA] = USIMM_USIM_CLA | ucP2;

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_MANAGE_CHANNEL;

    gstUSIMMAPDU.aucAPDU[P1]  = ucP1;

    gstUSIMMAPDU.aucAPDU[P2]  = ucP2;

    gstUSIMMAPDU.aucAPDU[P3]  = ucP3;

    gstUSIMMAPDU.ulLcValue = 0x00;

    gstUSIMMAPDU.ulLeValue = ucP3;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Manage_Channel_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
函 数 名  :USIMM_Terminal_Capability_APDU
功能描述  :terminal capability命令发送
输入参数  :ucP1:       命令参数1
           ucP2:       命令参数2
           USIMM_TERMINAL_CAPABILITY_STRU:     命令内容数据单元
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DLHandle
修订记录  :
1. 日    期   : 2013年5月14日
   作    者   : j00168360
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_Terminal_Capability_APDU(VOS_UINT8 ucP1, VOS_UINT8 ucP2, USIMM_TERMINAL_CAPABILITY_STRU *pstTerminalCapability)
{
    VOS_UINT32 ulResult;
    VOS_UINT32 ulLen = 0;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*填充APDU命令头*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_TERMINAL_CAPABILITY;

    gstUSIMMAPDU.aucAPDU[P1]  = ucP1;

    gstUSIMMAPDU.aucAPDU[P2]  = ucP2;

    /*lint -e534*/
    VOS_MemCpy(gstUSIMMAPDU.aucSendBuf, (VOS_UINT8 *)pstTerminalCapability->aucData,
                           pstTerminalCapability->ulLen);/*填充APDU命令内容*/
    /*lint +e534*/

    ulLen = pstTerminalCapability->ulLen;

    gstUSIMMAPDU.aucAPDU[P3]  = (VOS_UINT8)ulLen;

    gstUSIMMAPDU.ulLcValue = ulLen;                  /*填充命令其它内容*/

    gstUSIMMAPDU.ulLeValue = 0x00;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_STATUS_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_T1SendIFSD_APDU
功能描述  :T=1协议发送IFSD命令
输入参数  :ucData:UE可接收块的信息域大小
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2013年10月18日
   作    者   : j00168360
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_T1SendIFSD_APDU(VOS_UINT8 ucData)
{
    VOS_UINT32      ulResult;

    /*lint -e534*/
    VOS_MemSet(gstUSIMMAPDU.aucAPDU, 0, USIMM_APDU_HEADLEN);

    VOS_MemSet(gstUSIMMAPDU.aucSendBuf, 0, USIMM_APDU_MAXLEN);
    /*lint +e534*/

    /* 需要发送一个字节的IFS大小 */
    gstUSIMMAPDU.ulLcValue = 0x01;

    gstUSIMMAPDU.ulLeValue = 0x00;

    gstUSIMMAPDU.aucSendBuf[0] = ucData;

    /* 标记当前要发送IFS REQ */
    g_bSendIFSReqFlag = VOS_TRUE;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*调用链路层处理函数*/

    g_bSendIFSReqFlag = VOS_FALSE;

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_T1SendIFSD_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}


#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
/*****************************************************************************
函 数 名  :USIMM_StoreESNMEID_APDU
功能描述  :发送Store ESN MEID命令
输入参数  :ucData:UE可接收块的信息域大小
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2013年10月18日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_StoreESNMEID_APDU(UICC_STORE_ESN_MEID_P1_UINT8     enDataType,
                                                    VOS_UINT8                   *pucData,
                                                    USIMM_APDU_ST               *pstUSIMMAPDU)
{
    VOS_UINT32      ulResult;

    pstUSIMMAPDU->aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*填充APDU命令头*/

    pstUSIMMAPDU->aucAPDU[INS] = CMD_INS_STORE_ESNMEID;

    pstUSIMMAPDU->aucAPDU[P1]  = enDataType;

    pstUSIMMAPDU->aucAPDU[P2]  = 0x00;

    /*lint -e534*/
    VOS_MemCpy(pstUSIMMAPDU->aucSendBuf, pucData, USIMM_STORE_ESNMEID_MAX);/*填充APDU命令内容*/
    /*lint +e534*/

    pstUSIMMAPDU->aucAPDU[P3]  = USIMM_STORE_ESNMEID_MAX;

    pstUSIMMAPDU->ulLcValue = USIMM_STORE_ESNMEID_MAX;   /*填充命令其它内容*/

    pstUSIMMAPDU->ulLeValue = 0x01;                      /*固定值*/

    ulResult = USIMM_DLHandle(pstUSIMMAPDU);   /*调用链路层处理函数*/

    if (USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_StoreESNMEID_APDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_UpdateSsdAPDU
功能描述  :发送UPDATE SSD命令
输入参数  :ucLen:SSD长度
           pucData:SSD内容
           pstUSIMMAPDU:APDU发判断数据结构
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2014年07月10日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_UpdateSsdAPDU(VOS_UINT8                    ucLen,
                                            VOS_UINT8                   *pucData,
                                            USIMM_APDU_ST               *pstUSIMMAPDU)
{
    VOS_UINT32      ulResult;

    pstUSIMMAPDU->aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*填充APDU命令头*/

    pstUSIMMAPDU->aucAPDU[INS] = CMD_INS_UPDATE_SSD;

    pstUSIMMAPDU->aucAPDU[P1]  = 0;

    pstUSIMMAPDU->aucAPDU[P2]  = 0;

    pstUSIMMAPDU->aucAPDU[P3]  = ucLen;

    pstUSIMMAPDU->ulLcValue    = ucLen;           /*填充命令其它内容*/

    pstUSIMMAPDU->ulLeValue    = 0;

    /*lint -e534*/
    VOS_MemCpy(pstUSIMMAPDU->aucSendBuf, pucData, ucLen);/*填充APDU命令内容*/
    /*lint +e534*/

    ulResult = USIMM_DLHandle(pstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_UpdateSsdAPDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_ConfirmSsdAPDU
功能描述  :发送Store ESN MEID命令
输入参数  :ucLen:AUTHBS长度
           pucData:AUTHBS内容
           pstUSIMMAPDU:APDU下发数据结构
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2014年07月10日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ConfirmSsdAPDU(VOS_UINT8                   ucLen,
                                            VOS_UINT8                   *pucData,
                                            USIMM_APDU_ST               *pstUSIMMAPDU)
{
    VOS_UINT32      ulResult;

    pstUSIMMAPDU->aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*填充APDU命令头*/

    pstUSIMMAPDU->aucAPDU[INS] = CMD_INS_CONFIRM_SSD;

    pstUSIMMAPDU->aucAPDU[P1]  = 0;

    pstUSIMMAPDU->aucAPDU[P2]  = 0;

    pstUSIMMAPDU->aucAPDU[P3]  = ucLen;

    pstUSIMMAPDU->ulLcValue    = ucLen;           /*填充命令其它内容*/

    pstUSIMMAPDU->ulLeValue    = 0;

    /*lint -e534*/
    VOS_MemCpy(pstUSIMMAPDU->aucSendBuf, pucData, ucLen);/*填充APDU命令内容*/
    /*lint +e534*/

    ulResult = USIMM_DLHandle(pstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ConfirmSsdAPDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_ManageSsdAPDU
功能描述  :发送MANAGE SSD命令
输入参数  :ucCmd:命令类型，区分是update ssd还是confirm ssd
           ucLen:AUTHBS长度
           pucData:AUTHBS内容
           pstUSIMMAPDU:APDU下发数据结构
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2014年07月10日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ManageSsdAPDU(VOS_UINT8                   ucCmd,
                                            VOS_UINT8                   ucLen,
                                            VOS_UINT8                   *pucData,
                                            USIMM_APDU_ST               *pstUSIMMAPDU)
{
    VOS_UINT32      ulResult;

    pstUSIMMAPDU->aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*填充APDU命令头*/

    pstUSIMMAPDU->aucAPDU[INS] = CMD_INS_MANAGE_SSD;

    pstUSIMMAPDU->aucAPDU[P1]  = 0;

    pstUSIMMAPDU->aucAPDU[P2]  = ucCmd;

    pstUSIMMAPDU->aucAPDU[P3]  = ucLen;

    pstUSIMMAPDU->ulLcValue    = ucLen;           /*填充命令其它内容*/

    pstUSIMMAPDU->ulLeValue    = 0;

    /*lint -e534*/
    VOS_MemCpy(pstUSIMMAPDU->aucSendBuf, pucData, ucLen);/*填充APDU命令内容*/
    /*lint +e534*/

    ulResult = USIMM_DLHandle(pstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ManageSsdAPDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_GenerateKeyVpmAPDU
功能描述  :发送Generate Key/VPM命令
输入参数  :ucLen:下发数据的长度
           pucData:下发数据的内容
           pstUSIMMAPDU:APDU下发数据结构
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
1. 日    期   : 2014年07月10日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GenerateKeyVpmAPDU(VOS_UINT8                   ucLen,
                                                    VOS_UINT8                   *pucData,
                                                    USIMM_APDU_ST               *pstUSIMMAPDU)
{
    VOS_UINT32      ulResult;

    pstUSIMMAPDU->aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*填充APDU命令头*/

    pstUSIMMAPDU->aucAPDU[INS] = CMD_INS_GENERATE_KEY;

    pstUSIMMAPDU->aucAPDU[P1]  = 0;

    pstUSIMMAPDU->aucAPDU[P2]  = 0;

    pstUSIMMAPDU->aucAPDU[P3]  = ucLen;

    pstUSIMMAPDU->ulLcValue    = ucLen;           /*填充命令其它内容*/

    pstUSIMMAPDU->ulLeValue    = 0;

    /*lint -e534*/
    VOS_MemCpy(pstUSIMMAPDU->aucSendBuf, pucData, ucLen);/*填充APDU命令内容*/
    /*lint +e534*/

    ulResult = USIMM_DLHandle(pstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GenerateKeyVpmAPDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_BSChallengeAPDU
功能描述  :发送Store ESN MEID命令
输入参数  :pucRandSeed:Rand SSD的内容
           pstUSIMMAPDU:APDU下发数据结构
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2014年07月10日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_BSChallengeAPDU(VOS_UINT8                  *pucRandSeed,
                                             USIMM_APDU_ST               *pstUSIMMAPDU)
{
    VOS_UINT32      ulResult;

    pstUSIMMAPDU->aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*填充APDU命令头*/

    pstUSIMMAPDU->aucAPDU[INS] = CMD_INS_BASE_STATION_CHALLENGE;

    pstUSIMMAPDU->aucAPDU[P1]  = 0;

    pstUSIMMAPDU->aucAPDU[P2]  = 0;

    pstUSIMMAPDU->aucAPDU[P3]  = USIMM_BS_RANDSEED_MAX;

    pstUSIMMAPDU->ulLcValue    = USIMM_BS_RANDSEED_MAX;           /*填充命令其它内容*/

    pstUSIMMAPDU->ulLeValue    = USIMM_BS_RANDSEED_MAX;

    /*lint -e534*/
    VOS_MemCpy( pstUSIMMAPDU->aucSendBuf, (VOS_UINT8 *)pucRandSeed,  pstUSIMMAPDU->aucAPDU[P3]);/*填充APDU命令内容*/
    /*lint +e534*/

    ulResult = USIMM_DLHandle(pstUSIMMAPDU);   /*调用链路层处理函数*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_BSChallengeAPDU: USIMM_DLHandle is Failed");/*打印错误*/

        return VOS_ERR;
    }

    return VOS_OK;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

