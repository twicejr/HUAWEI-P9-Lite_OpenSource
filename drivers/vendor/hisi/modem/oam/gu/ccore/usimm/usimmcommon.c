/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : UsimmBase.c
  Author       : zhuli 00100318
  Version      : v00R002
  Date         : 2008-5-15
  Description  : 该C文件给出了---Common模块实现
  Function List:
  History      :
 ************************************************************************/

#include "usimmbase.h"
#include "mdrv.h"
#include "usimmapdu.h"
#include "usimmdl.h"
#include "msp_diag_comm.h"
#include "usimmt1dl.h"
#include "usimmglobal.h"
#include "usimminit.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_COMMON_C
/*lint +e767*/

#ifdef USIMM_DEBUG_PEINT
/*****************************************************************************
函 数 名  :USIMM_PRINT
功能描述  :打印
输入参数  :
输出参数  :
返 回 值  :
调用函数  :
 修订记录 :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_PRINT(
    VOS_UINT32                          ulPrintLev,
    VOS_INT8                            *pucString)
{
    switch(ulPrintLev)
    {
        case USIMM_NORMAL:
            /*lint -e534*/
            vos_printf("\r\nNORMAL:%s\r\n",pucString);
            /*lint +e534*/
            break;

        case USIMM_INFO:
            /*lint -e534*/
            vos_printf("\r\nINFO:%s\r\n",pucString);
            /*lint +e534*/
            break;

        case USIMM_WARNING:
            /*lint -e534*/
            vos_printf("\r\nWARNING:%s\r\n",pucString);
            /*lint +e534*/
            break;

        default:
            /*lint -e534*/
            vos_printf("\r\nERROR:%s\r\n",pucString);
            /*lint +e534*/
            break;
    }

    return;
}
#endif

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)

/*****************************************************************************
函 数 名  :USIMM_GetTFFile
功能描述  :读取固定长度的二进制文件内容
输入参数  :
输出参数  :无
返 回 值  :
调用函数  :
修订记录  :
1. 日    期   : 2009年11月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32  USIMM_GetDefTFMem(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileId,
    VOS_UINT16                         *pusReadLen,
    VOS_UINT8                          **pucData)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           ucChannelID;
    VOS_UINT8                           *pucContent;
    USIMM_EFFCP_ST                      *pstCurEFInfo;

    if ((VOS_NULL_PTR == pusReadLen) ||(VOS_NULL_PTR == pucData))
    {
        USIMM_ERROR_LOG("USIMM_GetDefTFMem: Para Error");

        return VOS_ERR;
    }

    ulResult = USIMM_SelectFileByDefFileId(enAppType, USIMM_NEED_FCP, enDefFileId);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GetDefTFMem: USIMM_SelectFileByDefFileId Error");

        return VOS_ERR;
    }

    pstCurEFInfo = USIMM_CCB_GetCurEFInfo(enAppType);

    if (VOS_NULL_PTR == pstCurEFInfo)
    {
        USIMM_ERROR_LOG("USIMM_GetDefTFMem: USIMM_CCB_GetCurEFInfo Error");

        return VOS_ERR;
    }

    if(pstCurEFInfo->enFileType != USIMM_EFSTRUCTURE_TRANSPARENT)
    {
        USIMM_ERROR_LOG("USIMM_GetDefTFMem:File Type error");

        return VOS_ERR;
    }

    ucChannelID = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelID)
    {
        USIMM_ERROR_LOG("USIMM_GetDefTFMem:USIMM_CCB_GetAppChNO error");

        return VOS_ERR;
    }

    if (pstCurEFInfo->usFileLen > USIMM_MAX_FILE_SIZE)
    {
        usDataLen = USIMM_MAX_FILE_SIZE;
    }
    else
    {
        usDataLen = pstCurEFInfo->usFileLen;
    }

    pucContent= (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, STATIC_MEM_PT, usDataLen);

    if (VOS_NULL_PTR == pucContent)
    {
        USIMM_ERROR_LOG("USIMM_GetDefTFMem:VOS_MemAlloc error");

        return VOS_ERR;
    }

    ulResult = USIMM_SendReadBinaryApdu(ucChannelID, VOS_NULL, usDataLen, pucContent);

    if (USIMM_SW_OK != ulResult)
    {
        VOS_MemFree(WUEPS_PID_USIM, pucContent);
    }
    else
    {
        *pucData    = pucContent;
        *pusReadLen = usDataLen;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_GetTFFile
功能描述  :读取固定长度的二进制文件内容
输入参数  :
输出参数  :无
返 回 值  :
调用函数  :
修订记录  :
1. 日    期   : 2009年11月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32  USIMM_GetTFByDefFID(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileId,
    VOS_UINT16                          usReadLen,
    VOS_UINT8                          *pucData)
{
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           ucChannelID;

    if (VOS_OK != USIMM_SelectFileByDefFileId(enAppType, USIMM_NEED_FCP, enDefFileId))
    {
        USIMM_ERROR_LOG("USIMM_GetTFByDefFID: USIMM_SelectFileByDefFileId Error");

        return VOS_ERR;
    }

    if (USIMM_CCB_GetCurEFInfo(enAppType)->enFileType != USIMM_EFSTRUCTURE_TRANSPARENT)
    {
        USIMM_ERROR_LOG("USIMM_GetTFFile:File Type error");

        return VOS_ERR;
    }

    if (USIMM_READ_ALL_FILE_CONTENT == usReadLen)
    {
        usDataLen = USIMM_CCB_GetCurEFInfo(enAppType)->usFileLen;
    }
    else
    {
        usDataLen = usReadLen;
    }

    /* 获取CHANNEL ID，不判断是否为空，在前面USIMM_CCB_GetCurEFInfo函数里已经判断过 */
    ucChannelID = USIMM_CCB_GetAppChNO(enAppType);

    return USIMM_SendReadBinaryApdu(ucChannelID, VOS_NULL, usDataLen, pucData);
}

/*****************************************************************************
函 数 名  :USIMM_WriteTFFile
功能描述  :读取固定长度的二进制文件内容
输入参数  :
输出参数  :无
返 回 值  :
调用函数  :
修订记录  :
1. 日    期   : 2009年11月12日
   作    者   : H59254
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32  USIMM_WriteTFFileByDefID(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileId,
    VOS_UINT16                          usDataLen,
    VOS_UINT8                          *pucData)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucChannelID;

    ulResult = USIMM_SelectFileByDefFileId(enAppType, USIMM_NEED_FCP, enDefFileId);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_WriteTFFileByDefID:USIMM_SelectFileByDefFileId error");
        return VOS_ERR;
    }

    if (USIMM_CCB_GetCurEFInfo(enAppType)->enFileType != USIMM_EFSTRUCTURE_TRANSPARENT)
    {
        USIMM_ERROR_LOG("USIMM_WriteTFFileByDefID:USIMM_CCB_GetCurEFInfo error");
        return VOS_ERR;
    }

    /* 获取CHANNEL ID，不判断是否为空，在前面USIMM_CCB_GetCurEFInfo函数里已经判断过 */
    ucChannelID = USIMM_CCB_GetAppChNO(enAppType);

    return USIMM_SendUpdateBinaryApdu(ucChannelID, usDataLen, pucData);
}

/*****************************************************************************
函 数 名  :USIMM_STATUSCmd
功能描述  :发送STATUS命令并解析返回内容
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_ReadBinary_APDU
           USIMM_CheckSW
修订记录  :
1. 日    期   : 2007年7月11日
    作    者   : z00100318
    修改内容   : Creat
2. 日    期  : 2011年8月30日
   作    者  : j00168360
   修改内容  : [DTS2011083000162]，USIM模块正向清理保护性复位及卡路径选择
*****************************************************************************/

VOS_UINT32 USIMM_STATUSProc(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT16                          usCurDfID;
    VOS_UINT16                          usCurFcpLen;
    VOS_UINT16                          usCurDfIDTemp;
    USIMM_UICC_ADF_INFO_STRU*           pstUiccAdfInfo = VOS_NULL_PTR;

    ulResult = USIMM_SendStatusPollingApdu(&stRspData);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_StatusHandle: Command SW is Error");

        return ulResult;
    }

    USIMM_INFO_LOG("USIMM_StatusHandle: The Status Command is OK");

    /* 根据当前主应用类型得到当前的DF和DF的FCP */
    usCurDfID   = USIMM_CCB_GetCurFileInfo(USIMM_UNLIMIT_AUTO)->usCurDFID;
    usCurFcpLen = USIMM_CCB_GetCurFileInfo(USIMM_UNLIMIT_AUTO)->usCurDFFcpLen;

    ulResult = USIMM_DecodeDFFcp(USIMM_CCB_GetCardType(), &stRspData, USIMM_CCB_GetCurFileInfo(USIMM_UNLIMIT_AUTO));

    if (ulResult != VOS_OK)
    {
        /* 出错需要还原之前的值，避免下次发送错误 */
        USIMM_CCB_GetCurFileInfo(USIMM_UNLIMIT_AUTO)->usCurDFFcpLen  = usCurFcpLen;

        USIMM_CCB_GetCurFileInfo(USIMM_UNLIMIT_AUTO)->usCurDFID      = usCurDfID;

        USIMM_WARNING_LOG("USIMM_STATUSProc: USIMM_DecodeDFFcp Fail");

        /* 只要status apdu下去卡有响应就认为卡在位 */
        return USIMM_SW_OK;
    }

    if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())  /* 当前为SIM */
    {
        USIMM_COMM_SaveDFPinInfo(USIMM_UNLIMIT_AUTO);

        USIMM_CCB_GetCurFileInfo(USIMM_UNLIMIT_AUTO)->usCurDFID = USIMM_CCB_GetCurDFInfo(USIMM_UNLIMIT_AUTO)->usDFID;
    }
    else
    {
        pstUiccAdfInfo =  USIMM_CCB_GetAdfInfoByCH(USIMM_APDU_BASECHANNEL);

        if (VOS_NULL_PTR == pstUiccAdfInfo)
        {
            /* 只要status apdu下去卡有响应就认为卡在位 */
            USIMM_WARNING_LOG("USIMM_STATUSProc: USIMM_CCB_GetAdfInfoByCH Fail");

            return USIMM_SW_OK;
        }

        /*lint -e534*/
        if (VOS_OK == VOS_MemCmp(pstUiccAdfInfo->aucAID,
                                  USIMM_CCB_GetCurDFInfo(USIMM_UNLIMIT_AUTO)->aucName,
                                  pstUiccAdfInfo->ulAIDLen))
        {
            USIMM_CCB_GetCurFileInfo(USIMM_UNLIMIT_AUTO)->usCurDFID = ADF;
        /*lint +e534*/
        }
        else
        {
            USIMM_CCB_GetCurFileInfo(USIMM_UNLIMIT_AUTO)->usCurDFID = USIMM_CCB_GetCurDFInfo(USIMM_UNLIMIT_AUTO)->usDFID;
        }
    }

    usCurDfIDTemp   = USIMM_CCB_GetCurFileInfo(USIMM_UNLIMIT_AUTO)->usCurDFID;

    if ((USIMM_NULL_ID != usCurDfID) && (usCurDfID != usCurDfIDTemp))
    {
        USIMM_ERROR_LOG("USIMM_StatusHandle:The Status Command is not Same,The Card Should be Changed");

        return USIMM_SW_DFPATH_ERROR;
    }

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_UpdatePukState
功能描述  :更新PUK码状态
输入参数  :USIMM_APP_PIN_INFO_STRU            *pstPinInfo

输出参数  :无
返 回 值  :无
调用函数  :
修订记录  :
1. 日    期   : 2015年4月14日
    作    者   : g00256031
    修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_UpdatePukState(
    USIMM_APP_PIN_INFO_STRU            *pstPinInfo
)
{

    if (0 == pstPinInfo->ucPinRemainTime)
    {
        USIMM_NORMAL_LOG("USIMM_UpdatePukState: Set USIMM_PUK_NEED");

        pstPinInfo->enPinVerified = USIMM_PUK_NEED;
    }

    if (0 == pstPinInfo->ucPukRemainTime)
    {
        USIMM_NORMAL_LOG("USIMM_UpdatePukState: Set USIMM_PUK_BLOCK");

        pstPinInfo->enPinVerified = USIMM_PUK_BLOCK;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_ReCountPINRemainTime
功能描述  :重新初始化当前的PIN剩余次数
输入参数  :enPINType:PIN类型
           ulResult :命令操作结果
输出参数  :无
返 回 值  :无
调用函数  :
修订记录  :
1. 日    期   : 2007年8月11日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_ReCountPINRemainTime(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulCmdType,
    USIMM_PIN_TYPE_ENUM_UINT32          enPINType
)
{
    USIMM_APP_PIN_INFO_STRU            *pstPinInfo;

    if ((USIMM_SW_SECURITY_ERROR == ulResult)
     || (USIMM_SW_CMD_REMAINTIME == ulResult)
     || (USIMM_SW_PIN_BLOCK == ulResult))
    {
        if(USIMM_PINCMD_UNBLOCK == ulCmdType)
        {
            USIMM_WARNING_LOG("USIMM_ReCountPINRemainTime: The PUK is Wrong, Verify is failed");

            if (USIMM_PIN == enPINType)
            {
                return USIMM_INCORRECT_PASSWORD;
            }

            if (USIMM_PIN2 == enPINType)
            {
                return USIMM_INCORRECT_PASSWORD;
            }
        }
        else
        {
            USIMM_WARNING_LOG("USIMM_ReCountPINRemainTime: The PIN is Wrong, Verify is failed");

            if(USIMM_PIN == enPINType)
            {
                pstPinInfo = USIMM_CCB_GetPIN1InfoByApp(enAppType);
                return ((pstPinInfo->ucPinRemainTime == 0)?USIMM_SIM_PUK_REQUIRED:USIMM_INCORRECT_PASSWORD);/* [false alarm]: 屏蔽Fortify 错误 */
            }

            if(USIMM_PIN2 == enPINType)
            {
                pstPinInfo = USIMM_CCB_GetPIN2InfoByApp(enAppType);
                return ((pstPinInfo->ucPinRemainTime == 0)?USIMM_SIM_PUK2_REQUIRED:USIMM_INCORRECT_PASSWORD);/* [false alarm]: 屏蔽Fortify 错误 */
            }
        }
    }

    USIMM_WARNING_LOG("USIMM_ReCountPINRemainTime: The PIN or PUK Status is Wrong, Reamin Time should not Changed");

    return USIMM_SIM_FAILURE;
}

/*****************************************************************************
函 数 名  :USIMM_ChangePIN
功能描述  :更改PIN操作，并重新初始化当前的PIN剩余次数
输入参数  :enPINType:PIN类型
           pucOldPIN:原PIN
           pucNewPIN:新PIN
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_ChangePIN_APDU
          USIMM_CheckSW
          USIMM_GetPINRemainTime
          USIMM_AdjudgeCardState
修订记录  :
1. 日    期   : 2007年7月11日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_ChangePIN(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PIN_TYPE_ENUM_UINT32          enPINType,
    VOS_UINT8                          *pucOldPIN,
    VOS_UINT8                          *pucNewPIN
)
{
    VOS_UINT32                          ulResult;
    USIMM_APP_PIN_INFO_STRU            *pstPinInfo;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT8                           ucChannelID;

    ucChannelID = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelID)
    {
        USIMM_ERROR_LOG("USIMM_ChangePIN:USIMM_CCB_GetAppChNO error");

        return VOS_ERR;
    }

    if (USIMM_PIN == enPINType)
    {
        pstPinInfo = USIMM_CCB_GetPIN1InfoByApp(enAppType);
    }
    else            /*暂时不需要支持其它类型PIN*/
    {
        pstPinInfo = USIMM_CCB_GetPIN2InfoByApp(enAppType);
    }

    if (VOS_NULL_PTR == pstPinInfo)
    {
        USIMM_ERROR_LOG("USIMM_ChangePIN: pstPinInfo is Null Ptr");
        return VOS_ERR;
    }

    ulResult = USIMM_SendChangePinApdu(ucChannelID, pstPinInfo->ucPINRefNum, pucOldPIN, pucNewPIN, &stRspData);

    if(USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
    {
        (VOS_VOID)USIMM_UICC_InitPINRemainTime(ucChannelID, pstPinInfo->ucPINRefNum, &(pstPinInfo->ucPinRemainTime));
    }
    else
    {
        (VOS_VOID)USIMM_STATUSProc();
    }

    if(USIMM_SW_OK != ulResult)
    {
        ulResult = USIMM_ReCountPINRemainTime(ucChannelID, ulResult, USIMM_PINCMD_CHANGE, enPINType);
    }

    USIMM_UpdatePukState(pstPinInfo);

    return ulResult;        /*更改不成功则返回VOS_ERR*/
}

/*****************************************************************************
函 数 名  :USIMM_UnblockPIN
功能描述  :实现解锁PIN操作，并初始化PIN/PUK剩余次数　
输入参数  :enPINType:   解锁PIN类型
          pucPUK:       PUK内容
          pucNewPIN:  新PIN内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_UnblockPIN_APDU
          USIMM_CheckSW
          USIMM_GetPINRemainTime
          USIMM_GetPUKRemainTime
          USIMM_AdjudgeCardState
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_UnblockPIN(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PIN_TYPE_ENUM_UINT32          enPINType,
    VOS_UINT8                          *pucPUK,
    VOS_UINT8                          *pucNewPIN
)
{
    VOS_UINT32                          ulResult;
    USIMM_APP_PIN_INFO_STRU            *pstPinInfo;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT8                           ucPINType;
    VOS_UINT8                           ucChannelID;

    if ((VOS_NULL_PTR == pucNewPIN)||(VOS_NULL_PTR == pucPUK)
      || ((USIMM_PIN != enPINType)&&(USIMM_PIN2 != enPINType))) /*参数检查*/
    {
        USIMM_ERROR_LOG("USIMM_UnblockPIN: Input Parameter Error");

        return VOS_ERR;
    }

    ucChannelID = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelID)
    {
        USIMM_ERROR_LOG("USIMM_UnblockPIN:USIMM_CCB_GetAppChNO error");

        return VOS_ERR;
    }

    if (USIMM_PIN == enPINType)
    {
        pstPinInfo = USIMM_CCB_GetPIN1InfoByApp(enAppType);

        if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
        {
            ucPINType = pstPinInfo->ucPINRefNum;
        }
        else
        {
            ucPINType = 0x00;
        }
    }
    else
    {
        pstPinInfo = USIMM_CCB_GetPIN2InfoByApp(enAppType);

        ucPINType = pstPinInfo->ucPINRefNum;
    }

    ulResult = USIMM_SendUnblockPinApdu(ucChannelID, ucPINType, pucPUK, pucNewPIN, &stRspData);

    if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
    {
        (VOS_VOID)USIMM_UICC_InitPINRemainTime(ucChannelID, ucPINType, &(pstPinInfo->ucPinRemainTime));

        if (VOS_OK != USIMM_UICC_InitPUKRemainTime(ucChannelID, ucPINType, &(pstPinInfo->ucPukRemainTime)))
        {
            USIMM_INFO_LOG("USIMM_UnblockPIN: Get PUK Remain Time fail");
        }
    }
    else
    {
        (VOS_VOID)USIMM_STATUSProc();
    }

    /*根据结果更改当前的PIN次数*/
    if(USIMM_SW_OK == ulResult)
    {
        if(USIMM_PIN == enPINType)
        {
            pstPinInfo->enPinVerified = USIMM_PIN_NONEED;

            pstPinInfo->enPinEnable   = USIMM_PIN_ENABLED;
        }
        else
        {
            pstPinInfo->enPinVerified = USIMM_PIN_NEED;
        }
    }
    else        /*判断剩余次数更改PIN状态*/
    {
        ulResult = USIMM_ReCountPINRemainTime(enAppType, ulResult, USIMM_PINCMD_UNBLOCK, enPINType);
    }

    USIMM_UpdatePukState(pstPinInfo);

    return ulResult;        /*更改不成功则返回VOS_ERR*/
}

/*****************************************************************************
函 数 名  :USIMM_PINVerify
功能描述  :实现当前PIN码的验证、激活、去激活功能
输入参数  :enPINType:当前操作的PIN类型
           enPINCmd:当前操作类型
           pucPIN:     PIN码内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DisablePIN_APDU
          USIMM_EnablePIN_APDU
          USIMM_VerifyPIN_APDU
          USIMM_GetPINRemainTime
          USIMM_AdjudgeCardState
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_PINVerify(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PIN_TYPE_ENUM_UINT32          enPINType,
    VOS_UINT8                           ucPINCmd,
    VOS_UINT8                          *pucPIN
)
{
    VOS_UINT32                          ulResult;
    USIMM_APP_PIN_INFO_STRU            *pstPinInfo;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT8                           ucChannelID;

    ucChannelID = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelID)
    {
        USIMM_ERROR_LOG("USIMM_PINVerify:USIMM_CCB_GetAppChNO error");

        return VOS_ERR;
    }

    if (USIMM_PIN == enPINType)
    {
        pstPinInfo = USIMM_CCB_GetPIN1InfoByApp(enAppType);
    }
    else            /*暂时不需要支持其它类型PIN*/
    {
        pstPinInfo = USIMM_CCB_GetPIN2InfoByApp(enAppType);
    }

    if (VOS_NULL_PTR == pstPinInfo)
    {
        return VOS_ERR;
    }

    ulResult = USIMM_SendVerifyPinApdu(ucChannelID, ucPINCmd, pstPinInfo->ucPINRefNum, pucPIN, &stRspData);

    if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())  /*重新初始化当前的PIN剩余次数*/
    {
        (VOS_VOID)USIMM_UICC_InitPINRemainTime(ucChannelID, pstPinInfo->ucPINRefNum, &(pstPinInfo->ucPinRemainTime));
    }
    else
    {
        (VOS_VOID)USIMM_STATUSProc();
    }

    if (USIMM_SW_OK == ulResult) /*当前操作成功*/
    {
        if (USIMM_PIN2 == enPINType)     /*对于PIN2不需要修改状态*/
        {
            USIMM_UpdatePukState(pstPinInfo);

            return VOS_OK;
        }

        if (USIMM_PINCMD_ENABLE == ucPINCmd)    /*根据当前的操作类型修改PIN1状态*/
        {
            pstPinInfo->enPinEnable    = USIMM_PIN_ENABLED;
        }
        else if(USIMM_PINCMD_DISABLE == ucPINCmd)
        {
            pstPinInfo->enPinEnable    = USIMM_PIN_DISABLED;

            pstPinInfo->enPinVerified  = USIMM_PIN_NONEED;
        }
        else
        {
            pstPinInfo->enPinVerified  = USIMM_PIN_NONEED;
        }
    }
    else        /*判断剩余次数*/
    {
        ulResult = USIMM_ReCountPINRemainTime(enAppType, ulResult, ucPINCmd, enPINType);
    }

    USIMM_UpdatePukState(pstPinInfo);

    return ulResult;        /*更改不成功则返回VOS_ERR*/
}

/*****************************************************************************
函 数 名  :USIMM_InitUsimFDNBDNStatus
功能描述  :初始化USIM卡当前的FDN/BDN状态　
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2011年6月20日
    作    者   : j00168360
    修改内容   : Creat[DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_InitUsimFDNBDNStatus(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT8                   ucData;
    USIMM_FDNSTATUS_ENUM_UINT32 enFDNStatus;
    USIMM_BDNSTATUS_ENUM_UINT32 enBDNStatus;

    ulResult = USIMM_GetTFByDefFID(USIMM_GUTL_APP, USIMM_USIM_EFEST_ID, sizeof(ucData), &ucData);

    if(VOS_OK == ulResult) /*该文件的存在不是必须的*/
    {
        /*判断内容初始化对应的全局变量*/
        if (PS_USIM_SERVICE_AVAILIABLE == USIMM_IsServiceAvailable(USIM_SVR_FDN))
        {
            enFDNStatus = (ucData&0x01)?USIMM_FDNSTATUS_ON:USIMM_FDNSTATUS_OFF;
        }
        else
        {
            enFDNStatus = USIMM_FDNSTATUS_OFF;
        }

        USIMM_CCB_SetAppFDN(USIMM_GUTL_APP,enFDNStatus);

        if (PS_USIM_SERVICE_AVAILIABLE == USIMM_IsServiceAvailable(USIM_SVR_BDN))
        {
            enBDNStatus = (ucData&0x02)?USIMM_BDNSTATUS_ON:USIMM_BDNSTATUS_OFF;
        }
        else
        {
            enBDNStatus = USIMM_BDNSTATUS_OFF;
        }

        USIMM_CCB_SetAppBDN(USIMM_GUTL_APP,enBDNStatus);

    }
    else
    {
        USIMM_ERROR_LOG("USIMM_InitUsimFDNBDNStatus: USIMM_InitUsimFDNBDNStatus Error");
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_SimFDNBDNProcess
功能描述  :完成SIM卡的FDN功能开启后的初始化中相关文件有效的过程　
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat
2. 日    期   : 2011年6月20日
    作    者   : j00168360
    修改内容   : 修改函数名[DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_SimFDNBDNProcess(VOS_VOID)
{
    VOS_UINT32                          ulResult;

    ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_GSM_EFIMSI_ID);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_SimFDNBDNProcess: USIMM_SelectFile(EFIMSI) Error");

        return VOS_ERR;
    }

    if (USIMM_EFSTATUS_DEACTIVE == USIMM_CCB_GetCurEFInfo(USIMM_GUTL_APP)->enFileStatus)
    {
        (VOS_VOID)USIMM_SendActivateApdu(USIMM_APDU_BASECHANNEL);
    }

    ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_GSM_EFLOCI_ID);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_SimFDNBDNProcess: USIMM_SelectFile(EFLOCI) Error");

        return VOS_ERR;
    }

    if(USIMM_EFSTATUS_DEACTIVE == USIMM_CCB_GetCurEFInfo(USIMM_GUTL_APP)->enFileStatus)
    {
        (VOS_VOID)USIMM_SendActivateApdu(USIMM_APDU_BASECHANNEL);
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_FdnCapabilityRequest
功能描述  :初始化SIM卡FDN能力请求　
输入参数  :无
输出参数  :USIMM_FDNSTATUS_ENUM_UINT32 *pulFdnStatus
返 回 值  :无
修订记录  :
1. 日    期   : 2013年5月7日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_FdnCapabilityRequest(
    USIMM_FDNSTATUS_ENUM_UINT32         *pulFdnStatus)
{
    VOS_UINT32                          ulResult;

    /* 若FDN状态在SST文件中未allocated and activated,FDN未激活 */
    if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(SIM_SVR_FDN))
    {
        *pulFdnStatus = USIMM_FDNSTATUS_OFF;

        return;
    }

    /* 若ADN状态在SST文件中未allocated and activated,FDN激活 */
    if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(SIM_SVR_ADN))
    {
        *pulFdnStatus = USIMM_FDNSTATUS_ON;

        return;
    }

    /* ADN文件不存在,FDN激活 */
    ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_TELE_EFADN_ID);

    if (VOS_OK != ulResult)
    {
        *pulFdnStatus = USIMM_FDNSTATUS_ON;
    }
    else
    {
        /* ADN文件无效,FDN激活 */
        if (USIMM_EFSTATUS_DEACTIVE == USIMM_CCB_GetCurEFInfo(USIMM_GUTL_APP)->enFileStatus)
        {
            *pulFdnStatus = USIMM_FDNSTATUS_ON;
        }
        /* ADN文件有效,FDN未激活 */
        else
        {
            *pulFdnStatus = USIMM_FDNSTATUS_OFF;
        }
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_BdnCapabilityRequest
功能描述  :初始化SIM卡BDN能力请求　
输入参数  :无
输出参数  :USIMM_BDNSTATUS_ENUM_UINT32 *pulBdnStatus
返 回 值  :无
修订记录  :
1. 日    期   : 2013年5月7日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_BdnCapabilityRequest(
    USIMM_BDNSTATUS_ENUM_UINT32         *pulBdnStatus)
{
    VOS_UINT32                          ulResult;

    /* 如果不支持Call Control功能，BDN未激活 */
    if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(SIM_SVR_CALL_CONTROL))
    {
        *pulBdnStatus = USIMM_BDNSTATUS_OFF;

        return;
    }

    /* BDN在SST中不存在或BDN状态在SST文件中未allocated and activated,BDN未激活 */
    if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(SIM_SVR_BDN))
    {
        *pulBdnStatus = USIMM_BDNSTATUS_OFF;

        return;
    }

    /* BDN文件不存在,BDN未激活 */
    ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_TELE_EFBDN_ID);
    if (VOS_OK != ulResult)
    {
        *pulBdnStatus = USIMM_BDNSTATUS_OFF;
    }
    else
    {
        /* BDN文件有效,BDN激活 */
        if (USIMM_EFSTATUS_ACTIVE == USIMM_CCB_GetCurEFInfo(USIMM_GUTL_APP)->enFileStatus)
        {
            *pulBdnStatus = USIMM_BDNSTATUS_ON;
        }
        /* BDN文件无效,BDN未激活 */
        else
        {
            *pulBdnStatus = USIMM_BDNSTATUS_OFF;
        }
    }

    return;
}

/*****************************************************************************
函 数 名  : USIMM_UICCFDNEnable
功能描述  : UICC FDN激活操作，目前仅支持CDMA和GUTL
输入参数  : enAppType 应用类型
输出参数  : 无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/

VOS_UINT32 USIMM_UICCFDNEnable(
    USIMM_CARDAPP_ENUM_UINT32           enAppType)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucData;
    VOS_UINT16                          usEFESTID;
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileId;

    if (USIMM_GUTL_APP == enAppType)
    {
        usEFESTID   = EFEST;
        enDefFileId = USIMM_USIM_EFEST_ID;
    }
    else if (USIMM_CDMA_APP == enAppType)
    {
        usEFESTID   = EF_CSIM_EST;
        enDefFileId = USIMM_CSIM_EFEST_ID;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICCFDNEnable: AppType Error");

        return VOS_ERR;
    }

    ulResult = USIMM_PoolReadOneFile(usEFESTID, sizeof(VOS_UINT8), &ucData, enAppType);

    if(VOS_ERR == ulResult)
    {
        USIMM_ERROR_LOG("USIMM_3GppFDNEnable: EFEST Read Error");

        return VOS_ERR;
    }

    ucData = ucData|0x01;

    ulResult = USIMM_WriteTFFileByDefID(enAppType, enDefFileId, sizeof(VOS_UINT8), &ucData);

    if(USIMM_SW_OK != ulResult)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_3GppFDNEnable: USIMM_WriteTFFile Error");

        return VOS_ERR;
    }

    (VOS_VOID)USIMM_PoolUpdateOneFile(enAppType, usEFESTID, sizeof(VOS_UINT8), &ucData);

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : USIMM_ICCFDNEnable
功能描述  : ICC FDN激活操作，目前仅支持CDMA和GUTL
输入参数  : enAppType 应用类型
输出参数  : 无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/

VOS_UINT32 USIMM_ICCFDNEnable(
    USIMM_CARDAPP_ENUM_UINT32           enAppType)
{
    VOS_UINT32                          ulResult;
    USIMM_FILEPATH_INFO_STRU            stFilePath;
    VOS_UINT8                           ucChannelID;

    ucChannelID = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelID)
    {
        USIMM_ERROR_LOG("USIMM_ICCFDNEnable: USIMM_CCB_GetAppChNO Wrong");

        return USIMM_SW_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(stFilePath.acPath, USIMM_TELE_EFADN_STR, VOS_StrLen(USIMM_TELE_EFADN_STR) + 1);
    /*lint +e534*/

    stFilePath.ulPathLen =  VOS_StrLen(USIMM_TELE_EFADN_STR);

    ulResult = USIMM_SelectFile(enAppType, USIMM_NEED_FCP, &stFilePath);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_FDNEnable: USIMM_SelectFile(EFADN) Error");

        return VOS_ERR;
    }

    ulResult = USIMM_SendDeactivateApdu(ucChannelID);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_FDNEnable: USIMM_DeactivateFile_APDU Error");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : USIMM_UICCFDNDisable
功能描述  : UICC FDN去激活操作，目前仅支持CDMA和GUTL
输入参数  : enAppType 应用类型
输出参数  : 无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/

VOS_UINT32 USIMM_UICCFDNDisable(
    USIMM_CARDAPP_ENUM_UINT32           enAppType)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucData;
    VOS_UINT16                          usEFESTID;
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileId;

    if (USIMM_GUTL_APP == enAppType)
    {
        usEFESTID   = EFEST;
        enDefFileId = USIMM_USIM_EFEST_ID;
    }
    else if (USIMM_CDMA_APP == enAppType)
    {
        usEFESTID   = EF_CSIM_EST;
        enDefFileId = USIMM_CSIM_EFEST_ID;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICCFDNEnable: AppType Error");

        return VOS_ERR;
    }

    ulResult = USIMM_PoolReadOneFile(usEFESTID, sizeof(VOS_UINT8), &ucData, enAppType);

    if(VOS_ERR == ulResult)
    {
        USIMM_ERROR_LOG("USIMM_FDNDisable: USIMM_PoolReadOneFile Failed");

        return VOS_ERR;
    }

    ucData = ucData&0xFE;

    ulResult = USIMM_WriteTFFileByDefID(enAppType, enDefFileId, sizeof(VOS_UINT8), &ucData);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_FDNDisable: USIMM_UpdateTFFile Failed");

        return VOS_ERR;
    }

    (VOS_VOID)USIMM_PoolUpdateOneFile(enAppType, usEFESTID,sizeof(VOS_UINT8), &ucData);

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : USIMM_ICCFDNDisable
功能描述  : ICC FDN去激活操作，目前仅支持CDMA和GUTL
输入参数  : enAppType 应用类型
输出参数  : 无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :
修订记录  :
1. 日    期   : 2007年7月10日
   作    者   : z00100318
   修改内容   : Creat

*****************************************************************************/

VOS_UINT32 USIMM_ICCFDNDisable(
    USIMM_CARDAPP_ENUM_UINT32           enAppType)
{
    VOS_UINT32                          ulResult;
    USIMM_FILEPATH_INFO_STRU            stFilePath;

    /* 激活ADN电话本*/
    /*lint -e534*/
    VOS_MemCpy(stFilePath.acPath, USIMM_TELE_EFADN_STR, VOS_StrLen(USIMM_TELE_EFADN_STR) + 1);
    /*lint +e534*/

    stFilePath.ulPathLen          =  VOS_StrLen(USIMM_TELE_EFADN_STR);

    ulResult = USIMM_SelectFile(enAppType, USIMM_NEED_FCP, &stFilePath);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_FDNDisable: USIMM_SelectFile(EFADN) Failed");

        return VOS_ERR;
    }

    ulResult = USIMM_SendActivateApdu(USIMM_APDU_BASECHANNEL);

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_FDNEstChgInd
功能描述  :FDN激活触发REFRESH上报
输入参数  :无
输出参数  :无
返 回 值  :无
修订记录  :
1.  日    期   : 2014年04月25日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_FDNEstChgInd(VOS_VOID)
{
    USIMM_STKREFRESH_REQ_STRU           stMsg;
    VOS_UINT8                           aucEfest[]={0x3F, 0x00, 0x7F, 0xFF, 0x6F, 0x56};

    /*lint -e534 */
    VOS_MemSet(&stMsg, 0, sizeof(USIMM_STKREFRESH_REQ_STRU));
    /*lint +e534 */

    stMsg.usLen = sizeof(aucEfest);
    /*lint -e534 */
    VOS_MemCpy(stMsg.aucFileList, aucEfest, stMsg.usLen);
    /*lint +e534 */

    USIMM_RefreshFileIndHandle(&stMsg, USIMM_GUTL_APP);

    return;
}

/*****************************************************************************
函 数 名  :USIMM_FindTagInSMPTLV
功能描述  :在SimpleTLV数据结构中查询当前的Tag，返回实际数据长度的偏移
输入参数  :ucDataBuf:   数据内容
           ucTag:       查询的Tag
           ulDataLen:   数据总长度
输出参数  :无
返 回 值  :USIMM_TAGNOTFOUND
           长度字节的偏移
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_FindTagInSMPTLV(
    VOS_UINT8                           *pucDataBuf, 
    VOS_UINT8                           ucTag, 
    VOS_UINT32                          ulDataLen)
{
    VOS_UINT32 i;

    for(i=0; i<ulDataLen;)
    {
        if((pucDataBuf[i]&0x7F) == (ucTag&0x7F))
        {
            if(pucDataBuf[i+1] == 0x81)
            {
                return (i+2);   /*返回长度字节的偏移*/
            }
            else
            {
                return (i+1);
            }
        }
        else
        {
            if(pucDataBuf[i+1] == 0x81)      /*跳到下一个Tag*/
            {
                i += pucDataBuf[i+2] + 3;
            }
            else
            {
                i += pucDataBuf[i+1] + 2;
            }
        }
    }

    return USIMM_TAGNOTFOUND;
}

/*****************************************************************************
函 数 名  :USIMM_FindTagInBERTLV
功能描述  :在BERTLV数据结构中查询Tag并返回长度字节所在偏移　
输入参数  :ucDataBuf:   数据内容
           ucTag:       查询的Tag
           ulDataLen:   数据总长度
输出参数  :无
返 回 值  :USIMM_TAGNOTFOUND
           长度字节的偏移
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_FindTagInBERTLV(
    VOS_UINT8                           *pucDataBuf, 
    VOS_UINT8                           ucTag, 
    VOS_UINT32                          ulDataLen)
{
    VOS_UINT32 i;

    for(i=0; i<ulDataLen;)
    {
        if((pucDataBuf[i]&0x7F) == (ucTag&0x7F))   /*返回长度字节偏移*/
        {
            return (i+1);
        }
        else
        {
            i += pucDataBuf[i+1] + 2; /*跳到下一个Tag*/
        }
    }

    return USIMM_TAGNOTFOUND;
}

/*****************************************************************************
函 数 名  :USIMM_FindTagInCTLV
功能描述  :在压缩TLV 数据结构中查询Tag并返回Tag数据的偏移　
输入参数  :ucDataBuf:   数据内容
           ucTag:       查询的Tag
           ulDataLen:   数据总长度
输出参数  :无
返 回 值  :USIMM_TAGNOTFOUND
           长度字节的偏移
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_FindTagInCTLV(
    VOS_UINT8                           *pucDataBuf, 
    VOS_UINT8                           ucTag, 
    VOS_UINT32                          ulDataLen)
{
    VOS_UINT32 i;

    for(i=0; i<ulDataLen;)
    {
        if((pucDataBuf[i]&0xF0) == (ucTag&0xF0))    /*返回当前内容第一个字节偏移*/
        {
            return (i+1);
        }
        else
        {
            i += (pucDataBuf[i]&0x0F) + 1 ;   /*跳到下一个Tag*/
        }
    }

    return USIMM_TAGNOTFOUND;
}

/*****************************************************************************
函 数 名  :USIMM_GetBitFromBuf
功能描述  :从数据中获取指定Bit位的值　
输入参数  :ucDataBuf:   数据内容
           ulBitNo:     Bit号
           ulBufLen:    数据总长度
输出参数  :无
返 回 值  :USIMM_BITNOFOUNE
           Bit值
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_GetBitFromBuf(
    VOS_UINT8                           *pucDataBuf, 
    VOS_UINT32                          ulBitNo,
    VOS_UINT32                          ulBufLen)
{
    VOS_UINT32  ulOffset;
    VOS_UINT8   ucBit;

    ulOffset = (ulBitNo - 1)/ 8;

    ucBit     = (VOS_UINT8)((ulBitNo - 1)%8);

    if ( ulOffset >=  ulBufLen )
    {
        return USIMM_BITNOFOUNE;
    }

    return ((pucDataBuf[ulOffset]>>ucBit)&0x00000001);
}


/*****************************************************************************
函 数 名  :USIMM_DecideTMode
功能描述  :确定DL层是使用T=0还是T=1模式　
输入参数  :pstSCIATRInfo:底软返回的ATR参数
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2013年10月25日
    作    者   : j00168360
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_DecideTMode(
    SCI_ATRINFO_S                       *pstSCIATRInfo)
{
    NV_USIMM_T1_CTRL_PARA_STRU                              stT1CtrlPara;
    USIMM_T1_BLOCK_EPILOGUE_FIELD_ENUM_UINT32               enEDM;
    VOS_UINT32                                              ulResult;
    VOS_UINT32                                              ulResult2         = VOS_ERR;
    VOS_INT32                                               lVoltageSwitchRst = USIMM_SCI_NONEED_CHANGEVCC;

    /*lint -e534*/
    VOS_MemSet(&stT1CtrlPara, 0, sizeof(stT1CtrlPara));
    /*lint +e534*/

    /* 读NV项 */
    if (VOS_OK != NV_Read(en_NV_Item_Usimm_T1_Ctrl_PARA, &stT1CtrlPara, sizeof(stT1CtrlPara)))
    {
        /* 打印错误 */
        USIMM_ERROR_LOG("USIMM_DecideTMode:USIM Read T1 PARA NV error");

        /* NV读取失败，显式赋值为T0 */
        stT1CtrlPara.enTMode = USIMM_DL_T_MODE_T0;

    }

    /* 如果NV指示支持T=1,且底软API返回支持T=1 */
    if ((USIMM_DL_T_MODE_T1 == stT1CtrlPara.enTMode)
        && (T1_PROTOCOL_MODE == pstSCIATRInfo->Tbyte))
    {
        /* 设置T=1模式 */
        g_enUSIMMTMode = USIMM_DL_T_MODE_T1;

        /* TS_102221规范中EDC只使用LRC，而ISO_IEC 7816-3 2006中，则规定按ATR中的指示来决定EDC使用LRC或CRC。
            为协议兼容考虑，代码支持这两种规范，由NV项en_NV_Item_Usimm_T1_Ctrl_PARA决定具体遵循哪一种规范 */
        if(USIMM_T1_ERR_DETECT_MODE_TS102221 == stT1CtrlPara.enEDM)
        {
            enEDM = USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC;
        }
        else
        {
            enEDM = pstSCIATRInfo->errDetectMode;
        }

        /* 备份ATR中的相关T=1信息，用于卡复位后恢复T=1上下文使用 */
        g_stUSIMMT1Para.enErrDetectMode = enEDM;
        g_stUSIMMT1Para.ulIFSC          = pstSCIATRInfo->valIFSC;
        g_stUSIMMT1Para.ulIFSD          = pstSCIATRInfo->valIFSD;

        /* 更新T=1参数 */
        ulResult = USIMM_T1DLUpdateParaByATR(enEDM, pstSCIATRInfo->valIFSC, pstSCIATRInfo->valIFSD);

        if (VOS_OK == ulResult)
        {
            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, 
                                WUEPS_PID_USIM, 
                                WUEPS_PID_USIM, 
                                USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_2);

            if(VOS_OK != mdrv_sci_switch_protocol((PROTOCOL_MODE_E)g_enUSIMMTMode))
            {
                USIMM_WARNING_LOG("USIMM_DecodeATR:SET T MODE FAILED");

                /* 可维可测信息统计 */
                g_stT1StatisticInfo.ulProtocolSwitchFailCnt++;
            }

            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

            /* 发送IFS命令,确认是否确实支持T=1 */
            ulResult2 = USIMM_T1SendIFSD_APDU((VOS_UINT8)stT1CtrlPara.ulDefaultIFSD);
        }

        /* 更新参数失败或者发送IFS失败都要切到T=0 */
        if ((VOS_OK != ulResult) || (VOS_OK != ulResult2))
        {
            if(USIMM_DL_T1_GCF_ENABLE == stT1CtrlPara.enGcfFlag)
            {
                USIMM_ERROR_LOG("USIMM_DecideTMode: it is GCF test");

                return VOS_ERR;
            }

            g_enUSIMMTMode = USIMM_DL_T_MODE_T0;

            /* 发送IFS失败切换到T=0 */
            ulResult = USIMM_DLResetCard(USIMM_RESET_CARD, &lVoltageSwitchRst);

            if(VOS_OK != ulResult)
            {
                USIMM_ERROR_LOG("USIMM_DecideTMode: Reset Card is Failed");

                return VOS_ERR;
            }

            /* 通知底软当前支持T模式,失败只做打印 */
            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_2);
            if(VOS_OK != mdrv_sci_switch_protocol((PROTOCOL_MODE_E)g_enUSIMMTMode))
            {
                USIMM_WARNING_LOG("USIMM_DecodeATR:SET T MODE FAILED");

                /* 可维可测信息统计 */
                g_stT1StatisticInfo.ulProtocolSwitchFailCnt++;
            }
            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);
        }
    }
    else
    {
        g_enUSIMMTMode = USIMM_DL_T_MODE_T0;

        /* 通知底软当前支持T模式,失败只做打印 */
        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_2);
        if(VOS_OK != mdrv_sci_switch_protocol((PROTOCOL_MODE_E)g_enUSIMMTMode))
        {
            USIMM_WARNING_LOG("USIMM_DecodeATR:SET T MODE FAILED");

            /* 可维可测信息统计 */
            g_stT1StatisticInfo.ulProtocolSwitchFailCnt++;
        }
        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeDFPSDO
功能描述  :解析USIM卡的DF FCP中的PSDO数据内容
输入参数  :pPSDO:       PSDO的数据内容
           ulDataLen:  PSDO数据长度
输出参数  :pstDfInfo:当前DF的PIN信息
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_DecodeDFPSDO(
    VOS_UINT8                           *pucPSDO, 
    VOS_UINT32                          ulDataLen,
    USIMM_DFFCP_ST                      *pstDfInfo)
{
    VOS_UINT32  ulOffset = 0;
    VOS_UINT8   ucPINMapOffset = 2;
    VOS_UINT32  i ;
    VOS_UINT8   ucPinMapMask=0x80;
    VOS_UINT32  ulPinStatus;

    i = pucPSDO[ulOffset+1]*8;       /*总共可能的密码个数用于后面位图计算*/

    ulOffset = pucPSDO[ulOffset+1] + 2;

    while(((i > 0) && (ulOffset < ulDataLen)))
    {
        if(pucPSDO[ulOffset] != USIMM_FCP_PINRER_TAG)
        {
            ulOffset += 3;

            continue;
        }

        ulPinStatus = (pucPSDO[ucPINMapOffset]&ucPinMapMask)?1:0; /*如果Bit不为0*/

        if((pucPSDO[ulOffset+2] <= 0x88) && (pucPSDO[ulOffset+2] >= 0x81))
        {
            pstDfInfo->ucPIN2RefNum                 = pucPSDO[ulOffset+2];

            pstDfInfo->stPINInfo.enPin2Enable = USIMM_PIN_ENABLED&ulPinStatus;
        }
        else if((pucPSDO[ulOffset+2] <= 0x08) && (pucPSDO[ulOffset+2] >= 0x01))
        {
            pstDfInfo->ucPIN1RefNum                 = pucPSDO[ulOffset+2];

            pstDfInfo->stPINInfo.enPin1Enable = USIMM_PIN_ENABLED&ulPinStatus;
        }
        else if(pucPSDO[ulOffset+2] == 0x11)
        {
            gstUSIMMBaseInfo.enUniversalPINStatus = USIMM_PIN_ENABLED&ulPinStatus;
        }
        else
        {
            USIMM_NORMAL_LOG("USIMM_DecodeDFPSDO: The PSDO Could Not Support");
        }

        i--;

        ulOffset += 3;

        if( 0 == (i % 8) )/*如果bitmap走完一个字节，取下字节的bitmap*/
        {
            ucPINMapOffset++;

            ucPinMapMask = 0x80;
        }
        else
        {
            ucPinMapMask = ucPinMapMask>>1;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeCharacter
功能描述  :解析File characteristics,获得Clock的停止状态及LEVEL信息
输入参数  :ucFileChara
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2008年8月4日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_DecodeCharacter(
    VOS_UINT8                           ucFileChara)
{
    if(0x00 == (ucFileChara&0x0D))
    {
        gstUSIMMDrvInfo.enCLKStop = USIMM_CLKSTOP_NOALLOW;

        return;
    }

    if(0x00 == (ucFileChara&0x0C))/*解析Level ，取值HIGH,LOW,NONE*/
    {
         gstUSIMMDrvInfo.enCLKLevel = USIMM_CLKLEVEL_LOW;/*如果当前电平不确定，默认按照低电平进行*/
    }
    else if(0x04 == (ucFileChara&0x0C))
    {
        gstUSIMMDrvInfo.enCLKLevel = USIMM_CLKLEVEL_HIGH;/*高电平进入时钟停止*/
    }
    else if(0x08 == (ucFileChara&0x0C))
    {
        gstUSIMMDrvInfo.enCLKLevel = USIMM_CLKLEVEL_LOW;/*低电平进入时钟停止*/
    }
    else
    {
        USIMM_WARNING_LOG("USIMM_DecodeCharacter:Input Error");

        gstUSIMMDrvInfo.enCLKLevel = USIMM_CLKLEVEL_NONE;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeUsimDFFcp
功能描述  :解析USIM卡的DF FCP内容
输入参数  :ucLen:       FCP数据长度
           pucData:   FCP数据内容
输出参数  :pstDfInfo: Df信息
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_FindTagInSMPTLV
           USIMM_FindTagInBERTLV
           USIMM_DecodeDFPSDO
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_DecodeUsimDFFcp(
    VOS_UINT32                          ulLen, 
    VOS_UINT8                           *pucData, 
    USIMM_DFFCP_ST                      *pstDfInfo)
{
    VOS_UINT32 ulResult = VOS_OK;
    VOS_UINT32 ulStart;
    VOS_UINT32 ulOffset;
    VOS_UINT32 ulSubOffset;
    VOS_UINT32 ulDataLen;

    ulStart = USIMM_FindTagInSMPTLV(pucData, USIMM_FCP_TAG, ulLen);/*查询起始Tag*/

    if(USIMM_TAGNOTFOUND == ulStart)
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimDFFcp:FCP Tag not found");

        return VOS_ERR;
    }

    ulDataLen = pucData[ulStart];   /*有效数据长度*/

    ulStart++;                      /*指向需要解析的数据头*/

    /*解析文件描述字段*/
    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_FILE_DES_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND == ulOffset)   /*该字段必须存在*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimDFFcp:File Describer Tag not found");

        return VOS_ERR;
    }

    ulOffset +=ulStart + 1;

    if((pucData[ulOffset]&0x38) == 0) /*文件类型错误*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimDFFcp:File Type Error");

        return VOS_ERR;
    }

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_FID_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        ulOffset += ulStart + 1;

        pstDfInfo->usDFID = (VOS_UINT16)((pucData[ulOffset]<<0x08)&0xFF00)+pucData[ulOffset+1];
    }

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_NAME_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        ulOffset += ulStart;

        if(pucData[ulOffset] > 16)
        {
            USIMM_ERROR_LOG("USIMM_DecodeUsimDFFcp:File Name Error");

            return VOS_ERR;
        }

        /*lint -e534*/
        VOS_MemCpy(pstDfInfo->aucName, &pucData[ulOffset+1], pucData[ulOffset]);
        /*lint +e534*/

        pstDfInfo->ucNameLen = pucData[ulOffset];
    }

    /*解析File Characteristic 获得有关CLock停止状态及Level信息*/
    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_PRIVITE_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
       ulSubOffset = USIMM_FindTagInBERTLV(&pucData[ulOffset+ulStart+1], USIMM_FCP_CHARA_TAG, pucData[ulOffset+ulStart]);

       if ( USIMM_TAGNOTFOUND != ulSubOffset )
       {
            USIMM_DecodeCharacter(pucData[ulOffset+ulStart+ulSubOffset+2]);/*跳过长度信息指向要解析的数据*/

            pstDfInfo->ucCharaByte = pucData[ulOffset+ulStart+ulSubOffset+2];
       }

       ulSubOffset = USIMM_FindTagInBERTLV(&pucData[ulOffset+ulStart+1], USIMM_FCP_SUPSYSCMD_TAG, pucData[ulOffset+ulStart]);

       if ( USIMM_TAGNOTFOUND != ulSubOffset )
       {
           pstDfInfo->ucSupCmd = pucData[ulOffset+ulStart+ulSubOffset+2];
       }
    }

    /*确定DF安全标识方法*/
    pstDfInfo->enSCMode  = USIMM_SC_ATTRIB_NO;

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_SA_CF_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        pstDfInfo->enSCMode = USIMM_SC_ATTRIB_COMPACT;
    }

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_SA_REF_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        pstDfInfo->enSCMode = USIMM_SC_ATTRIB_REFERENCE;
    }

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_SA_EF_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        pstDfInfo->enSCMode = USIMM_SC_ATTRIB_EXPANDED;
    }

    /*解析PIN状态数据对象描述字段*/
    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_PIN_TO_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND == ulOffset)
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimDFFcp:FCP Pin Tag not found");
        return VOS_ERR;
    }

    ulResult = USIMM_DecodeDFPSDO(&pucData[ulOffset+ulStart+1], pucData[ulOffset+ulStart],pstDfInfo);

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeSimDFFcp
功能描述  :解析USIM卡的DF FCP内容　
输入参数  :ucLen:       FCP数据长度
           pucData:   FCP数据内容
输出参数  :pstDfInfo: Df信息
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_DecodeSimDFFcp(
    VOS_UINT32                          ulLen, 
    VOS_UINT8                           *pucData, 
    USIMM_DFFCP_ST                      *pstDfInfo)
{
    USIMM_SIMDF_FCP_ST            stSimDFFcp;

    if(ulLen < sizeof(USIMM_SIMDF_FCP_ST))
    {
        USIMM_ERROR_LOG("USIMM_DecodeSimDFFcp:Input Length Error");

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy((VOS_UINT8 *)&stSimDFFcp, pucData, sizeof(USIMM_SIMDF_FCP_ST));
    /*lint +e534*/

    stSimDFFcp.usFileID = ((stSimDFFcp.usFileID<<8)&0xff00)|((stSimDFFcp.usFileID>>8)&0x00ff);

    pstDfInfo->usDFID = stSimDFFcp.usFileID;

    /*文件类型错误*/
    if ((USIMM_SIM_FILE_TYPE_MF != stSimDFFcp.ucFileType)
     && (USIMM_SIM_FILE_TYPE_DF != stSimDFFcp.ucFileType))
    {
        USIMM_ERROR_LOG("USIMM_DecodeSimDFFcp:File Type Error");

        return VOS_ERR;
    }

    pstDfInfo->ucCharaByte = stSimDFFcp.ucFileChara;

    /*解析File Characteristic 获得有关CLock停止状态及Level信息*/
    USIMM_DecodeCharacter(stSimDFFcp.ucFileChara);

    if(0x00 == (stSimDFFcp.ucFileChara&0x80))    /*获取当前的PIN状态*/
    {
        pstDfInfo->stPINInfo.enPin1Enable = USIMM_PIN_ENABLED;
    }
    else
    {
        pstDfInfo->stPINInfo.enPin1Enable = USIMM_PIN_DISABLED;
    }

    pstDfInfo->stPINInfo.enPin2Enable = USIMM_PIN_ENABLED;

    /*初始化PIN剩余次数*/
    pstDfInfo->stPINInfo.ucPin1RemainTime = stSimDFFcp.ucPIN1RemainTime&0x0F;

    pstDfInfo->stPINInfo.ucPuk1RemainTime = stSimDFFcp.ucPUK1RemainTime&0x0F;

    pstDfInfo->stPINInfo.ucPin2RemainTime = stSimDFFcp.ucPIN2RemainTime&0x0F;

    pstDfInfo->stPINInfo.ucPuk2RemainTime = stSimDFFcp.ucPUK2RemainTime&0x0F;

    /*初始化默认内容*/
    pstDfInfo->ucPIN1RefNum = 0x01;

    pstDfInfo->ucPIN2RefNum = 0x02;

    pstDfInfo->ucNameLen    = 0;

    pstDfInfo->enSCMode     = USIMM_SC_ATTRIB_NO;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeUsimEFFcp
功能描述  :解析USIM卡的EF FCP内容　
输入参数  :ucLen:     FCP数据长度
           pucData:   FCP数据内容
输出参数  :pstDfInfo: EF信息
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_FindTagInSMPTLV
           USIMM_FindTagInBERTLV
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat
2.日    期  : 2011年7月5日
  作    者  : j00168360
  修改内容  : [DTS2011070102597]，SIM卡FDN功能开启，ADN文件可读可更新时电话本无法操作
*****************************************************************************/
VOS_UINT32 USIMM_DecodeUsimEFFcp(
    VOS_UINT32                          ulLen, 
    VOS_UINT8                           *pucData,
    USIMM_EFFCP_ST                      *pstEFInfo)
{
    VOS_UINT32 ulStart;
    VOS_UINT32 ulOffset;
    VOS_UINT32 ulDataLen;
    VOS_UINT8  ucTemp;

    ulStart = USIMM_FindTagInSMPTLV(pucData, USIMM_FCP_TAG, ulLen);/*查询起始Tag*/

    if(USIMM_TAGNOTFOUND == ulStart)
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimEFFcp:Data Length Error");

        return VOS_ERR;
    }

    ulDataLen = pucData[ulStart];   /*有效数据长度*/

    ulStart++;                     /*指向需要解析的数据头*/

    /*解析文件描述字段*/
    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_FILE_DES_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND == ulOffset)   /*该字段必须存在*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimEFFcp:File Describer not found");

        return VOS_ERR;
    }

    ulOffset += ulStart;

    ucTemp = pucData[ulOffset+1]&0x07;

    if(0x01 == ucTemp) /*文件类型TRANSPARENT*/
    {
        pstEFInfo->enFileType = USIMM_EFSTRUCTURE_TRANSPARENT;
    }
    else if(0x02 == ucTemp)/*文件为FIXED*/
    {
        pstEFInfo->enFileType       = USIMM_EFSTRUCTURE_FIXED;

        pstEFInfo->ucRecordLen    = pucData[ulOffset+4];

        pstEFInfo->ucRecordNum   = pucData[ulOffset+5];
    }
    else if(0x06 == ucTemp)/*文件为CYCLE*/
    {
        pstEFInfo->enFileType = USIMM_EFSTRUCTURE_CYCLE;

        pstEFInfo->ucRecordLen    = pucData[ulOffset+4];

        pstEFInfo->ucRecordNum   = pucData[ulOffset+5];
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimEFFcp:File Type Error");

        return VOS_ERR;
    }

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_FID_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        ulOffset += ulStart + 1;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimEFFcp:File ID Tag not Found");

        return VOS_ERR;
    }

    /*解析文件大小*/
    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_FILESIZE_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND == ulOffset)   /*字段必须存在*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimEFFcp:File Size Tag not Found");

        return VOS_ERR;
    }

    ulOffset += ulStart;

    pstEFInfo->usFileLen = (VOS_UINT16)(((pucData[ulOffset+1]<<0x08)&0xFF00) + pucData[ulOffset+2]);

    /*解析文件状态字段*/
    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_LCSI_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND == ulOffset)
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimEFFcp:Life Cycle Tag not Found");

        return VOS_ERR;
    }

    /* 仅当b1为0，b3为1时，文件才是DEACTIVE的 */
    if  ((0x0 == (pucData[ulOffset+ulStart+1]&0x01))
        && (0x4 == (pucData[ulOffset+ulStart+1]&0x04)))
    {
        pstEFInfo->enFileStatus = USIMM_EFSTATUS_DEACTIVE;
    }
    else
    {
        pstEFInfo->enFileStatus = USIMM_EFSTATUS_ACTIVE;
    }

    pstEFInfo->enFileReadUpdateFlag = USIMM_EF_RW_NOT;

    /*解析文件短名*/
    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_SFI_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        pstEFInfo->ucSFI = pucData[ulOffset+ulStart+1];
    }

    /*确定EF安全标识方法*/
    pstEFInfo->enSCMode  = USIMM_SC_ATTRIB_NO;

    pstEFInfo->usEFArrID = 0;

    pstEFInfo->ucArrNo   = 0;

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_SA_CF_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        pstEFInfo->enSCMode = USIMM_SC_ATTRIB_COMPACT;
    }

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_SA_REF_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        ulOffset += ulStart;

        pstEFInfo->enSCMode = USIMM_SC_ATTRIB_REFERENCE;

        pstEFInfo->usEFArrID = (VOS_UINT16)((pucData[ulOffset+1]<<0x08)&0xFF00)+pucData[ulOffset+2];

        pstEFInfo->ucArrNo    = pucData[ulOffset+3];
    }

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_SA_EF_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        pstEFInfo->enSCMode = USIMM_SC_ATTRIB_EXPANDED;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeSimEFFcp
功能描述  :解析SIM卡的EF FCP内容　
输入参数  :ucLen:     FCP数据长度
           pucData:   FCP数据内容
输出参数  :pstDfInfo: EF信息
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat
2.日    期  : 2011年7月5日
  作    者  : j00168360
  修改内容  : [DTS2011070102597]，SIM卡FDN功能开启，ADN文件可读可更新时电话本无法操作
*****************************************************************************/
VOS_UINT32 USIMM_DecodeSimEFFcp(
    VOS_UINT32                          ulLen, 
    VOS_UINT8                           *pucData,
    USIMM_EFFCP_ST                      *pstEFInfo)
{
    USIMM_SIMEF_FCP_ST          stSimEFFcp;

    if(ulLen < (sizeof(USIMM_SIMEF_FCP_ST) - 1))/*FCP的第15位对于透明文件不是mandatory 的*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeSimEFFcp:Input Length Error");

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy((VOS_UINT8 *)&stSimEFFcp, pucData, sizeof(USIMM_SIMEF_FCP_ST));
    /*lint +e534*/

    stSimEFFcp.usFileID = ((stSimEFFcp.usFileID>>8)&0x00ff)|((stSimEFFcp.usFileID<<8)&0xff00);

    stSimEFFcp.usFileLen = ((stSimEFFcp.usFileLen>>8)&0x00ff)|((stSimEFFcp.usFileLen<<8)&0xff00);

    pstEFInfo->usFileLen = stSimEFFcp.usFileLen;/*获取文件大小*/

    if(0x04 != stSimEFFcp.ucFileType)/*文件类型错误*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeSimEFFcp:File Type Error");

        return VOS_ERR;
    }

    pstEFInfo->enFileStatus         = (stSimEFFcp.ucFileStatus&0x01);/*获取文件状态*/

    pstEFInfo->enFileReadUpdateFlag = (stSimEFFcp.ucFileStatus&0x04);/*获取文件读取和更新标志*/

    if(0x00 == stSimEFFcp.ucEFStruct)   /*文件为TRANSPARENT*/
    {
        pstEFInfo->enFileType  = USIMM_EFSTRUCTURE_TRANSPARENT;
    }
    else if(0x01 == stSimEFFcp.ucEFStruct)  /*文件类型为FIXED*/
    {
        pstEFInfo->enFileType  = USIMM_EFSTRUCTURE_FIXED;

        pstEFInfo->ucRecordLen = stSimEFFcp.ucRecordLen;

        pstEFInfo->ucRecordNum = (VOS_UINT8)(pstEFInfo->usFileLen/pstEFInfo->ucRecordLen);
    }
    else if(0x03 == stSimEFFcp.ucEFStruct)  /*文件类型为CYCLE*/
    {
        pstEFInfo->enFileType  = USIMM_EFSTRUCTURE_CYCLE;

        pstEFInfo->ucRecordLen = stSimEFFcp.ucRecordLen;

        pstEFInfo->ucRecordNum = (VOS_UINT8)(pstEFInfo->usFileLen/pstEFInfo->ucRecordLen);
    }
    else    /*文件类型错误*/
    {
        USIMM_WARNING_LOG("USIMM_DecodeSimEFFcp: EF Struct Error");

        return VOS_ERR;
    }

    /*初始化其它内容*/
    pstEFInfo->enSCMode  = USIMM_SC_ATTRIB_NO;

    pstEFInfo->usEFArrID = 0;

    pstEFInfo->ucArrNo   = 0;

    pstEFInfo->ucSFI     = 0;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeEFFcp
功能描述  : 解析FCP内容，
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DecodeUsimEFFcp
           USIMM_DecodeSimEFFcp

修订记录  :
1. 日    期   : 2010年8月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_DecodeEFFcp(
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCurCardType,
    USIMM_APDU_RSP_STRU                *pstApduRspData,
    USIMM_CURFILEINFO_ST               *pstCurFileInfo)
{
    VOS_UINT32 ulResult;

    USIMM_ClearCurEFInfo(pstCurFileInfo);

    if (USIMM_PHYCARD_TYPE_UICC == enCurCardType)  /*当前为USIM/CSIM/ISIM*/
    {
        ulResult = USIMM_DecodeUsimEFFcp(pstApduRspData->usRspLen, pstApduRspData->aucRsp, &pstCurFileInfo->stEFInfo);
    }
    else
    {
        ulResult = USIMM_DecodeSimEFFcp(pstApduRspData->usRspLen, pstApduRspData->aucRsp, &pstCurFileInfo->stEFInfo);
    }

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_DecodeEFFcp:Decode FCP error");

        /*lint -e534 */
        VOS_MemSet(&pstCurFileInfo->stEFInfo, 0, sizeof(USIMM_EFFCP_ST));
        /*lint +e534 */

        return USIMM_SW_ERR;
    }

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeDFFcp
功能描述  : 解析FCP内容，
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DecodeUsimDFFcp
           USIMM_DecodeSimDFFcp

修订记录  :
1. 日    期   : 2010年8月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_DecodeDFFcp(
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCurCardType,
    USIMM_APDU_RSP_STRU                *pstApduRspData,
    USIMM_CURFILEINFO_ST               *pstCurFileInfo)
{
    VOS_UINT32 ulResult;

    USIMM_ClearCurDFInfo(pstCurFileInfo);

    if (USIMM_PHYCARD_TYPE_UICC == enCurCardType)  /*当前为USIM/CSIM/ISIM*/
    {
        ulResult = USIMM_DecodeUsimDFFcp(pstApduRspData->usRspLen, pstApduRspData->aucRsp, &pstCurFileInfo->stDFInfo);
    }
    else
    {
        ulResult = USIMM_DecodeSimDFFcp(pstApduRspData->usRspLen, pstApduRspData->aucRsp, &pstCurFileInfo->stDFInfo);
    }

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_DecodeDFFcp:Decode Fcp error");

        return USIMM_SW_ERR;
    }

    pstCurFileInfo->usCurDFFcpLen = pstApduRspData->usRspLen;

    return USIMM_SW_OK;
}

/*****************************************************************************
 函 数 名  : USIMM_DecodeFileFcp
 功能描述  : 解析USIM卡的文件 FCP内容
 输入参数  : usFileId;
 输出参数  : 无
 返 回 值  : 无
 修改历史  : m00128685
             2010-03-19
*****************************************************************************/
VOS_UINT32 USIMM_DecodeFileFcp(
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType,
    USIMM_U16_LVDATA_STRU               *pstFilePath,
    USIMM_APDU_RSP_STRU                 *pstApduRspData,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo)
{
    VOS_UINT32              ulResult = VOS_ERR;
    VOS_UINT16              usFileId;

    if(pstFilePath->ulDataLen < 1)
    {
        USIMM_ERROR_LOG("USIMM_DecodeFileFcp: file path len is 0");

        return VOS_ERR;
    }

    usFileId = pstFilePath->pusData[pstFilePath->ulDataLen-1];

    if (USIMM_IS_EF_FILE(usFileId))/* 更新EF文件FCP */
    {
        ulResult = USIMM_DecodeEFFcp(enCardType, pstApduRspData, pstCurFileInfo);
    }
    else/* 更新DF文件FCP */
    {
        ulResult = USIMM_DecodeDFFcp(enCardType, pstApduRspData, pstCurFileInfo);
    }

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_DecodeFileFcp: Fail to Decode FCP");
    }

    return ulResult;
}

/*****************************************************************************
 函 数 名  : USIMM_ReportEvent
 功能描述  : 通过调用OM提供的接口上报状态事件
 输入参数  : usEventId: 事件ID
 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史  : m00128685
             2009-11-10
*****************************************************************************/
VOS_VOID USIMM_ReportEvent(VOS_UINT16 usEventId)
{
    DIAG_EVENT_IND_STRU                 stEventInd;
    VOS_UINT8                           usModemId;

/* 标识主卡副卡 */
#if defined (INSTANCE_1)
    usModemId = DIAG_MODEM_1;
#elif defined (INSTANCE_2)
    usModemId = DIAG_MODEM_2;
#else
    usModemId = DIAG_MODEM_0;
#endif

    stEventInd.ulModule = DIAG_GEN_MODULE(usModemId, DIAG_MODE_COMM);
    stEventInd.ulPid    = WUEPS_PID_USIM;
    stEventInd.ulEventId= usEventId;
    stEventInd.ulLength = VOS_NULL;
    stEventInd.pData    = VOS_NULL_PTR;

    /*lint -e534*/
    (VOS_VOID)DIAG_EventReport(&stEventInd);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : USIMM_CardFilePathCMP
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 修改历史  : zhuli
             2010-03-19
*****************************************************************************/
VOS_UINT32 USIMM_CardFilePathCMP(
    VOS_UINT32                          ulPath1Len, 
    VOS_UINT16                          *pusPath1,
    VOS_UINT32                          ulPath2Len, 
    VOS_UINT16                          *pusPath2)
{
    if(ulPath2Len != ulPath1Len)
    {
        return VOS_ERR;
    }

    /*lint -e534*/
    if(VOS_OK != VOS_MemCmp(pusPath1, pusPath2, ulPath1Len*sizeof(VOS_UINT16)))
    {
        return VOS_ERR;
    /*lint +e534*/
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_UsimFIDToIsimFID
功能描述  :将USIM的文件ID转换成ISIM的文件ID
输入参数  :usFileID--待转换文件ID
输出参数  :无
返 回 值  :转换后文件ID
           空
修订记录  :
1. 日    期   : 2013年7月22日
   作    者   : zhuli
   修改内容   : Creat

*****************************************************************************/
USIMM_DEF_FILEID_ENUM_UINT32 USIMM_UsimEFIDToIsimEFID(
    USIMM_DEF_FILEID_ENUM_UINT32        enUsimID)
{
    VOS_UINT32                           i;

    if ((USIMM_USIM_ID > enUsimID)||(USIMM_USIM_EFPWS_ID < enUsimID))
    {
        USIMM_WARNING_LOG("USIMM_UsimEFIDToIsimEFID: usUsimID Error");

        return VOS_NULL_WORD;
    }

    /* 根据USIM文件ID查找对应的ISIM文件ID */
    for (i = 0; i < USIMM_ISIMEFTOUSIMEF_TBL_SIZE; i++)
    {
        if (g_astUSIMMIsimUsimEFTBL[i].ulUsimEFID == enUsimID)
        {
            return g_astUSIMMIsimUsimEFTBL[i].ulIsimEFID;
        }
    }

    /* 找不到则返回空 */
    return VOS_NULL_WORD;
}

/*****************************************************************************
函 数 名  :USIMM_IsimFIDToUsimFID
功能描述  :将ISIM的文件ID转换成USIM的文件ID
输入参数  :usFileID--待转换文件ID
输出参数  :无
返 回 值  :转换后文件ID
           空
修订记录  :
1. 日    期   : 2013年7月22日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
USIMM_DEF_FILEID_ENUM_UINT32 USIMM_IsimEFIDToUsimEFID(
    USIMM_DEF_FILEID_ENUM_UINT32        enIsimID)
{
    VOS_UINT32                           i;

    if ((USIMM_ISIM_ID > enIsimID)||(USIMM_ISIM_EFSMSP_ID < enIsimID))
    {
        USIMM_WARNING_LOG("USIMM_IsimEFIDToUsimEFID: usIsimID Error");

        return VOS_NULL_WORD;
    }

    /* 根据ISIM文件ID查找对应的USIM文件ID */
    for (i=0; i<USIMM_ISIMEFTOUSIMEF_TBL_SIZE; i++)
    {
        if (g_astUSIMMIsimUsimEFTBL[i].ulIsimEFID == enIsimID)
        {
            return g_astUSIMMIsimUsimEFTBL[i].ulUsimEFID;
        }
    }

    /* 找不到则返回空 */
    return VOS_NULL_WORD;
}

/*****************************************************************************
函 数 名  :SI_PIH_GetMncLen
功能描述  :获取MNC的长度
输入参数  :pucAdContent  -- AD文件内容
           ulFileSize    -- 文件内容
输出参数  :无
返 回 值  :MNC的长度
调用函数  :
修订记录  :
1. 日    期   : 2013年03月26日
   作    者   : g47350
   修改内容   : Creat
*****************************************************************************/
VOS_UINT8 USIMM_GetMncLen(
    VOS_UINT8                           *pucAdContent, 
    VOS_UINT32                          ulFileSize)
{
    VOS_UINT8                           ucHplmnMncLen;

    ucHplmnMncLen = USIMM_MNC_TWO_BYTES_LEN;

    /* 文件大小过小，则默认MNC为2字节长度 */
    if(USIMM_EF_AD_MIN_LEN >= ulFileSize)
    {
        return ucHplmnMncLen;
    }

    /* 判断MNC长度,MNC可能为2位或3位 */
    if ((USIMM_MNC_TWO_BYTES_LEN == (pucAdContent[USIMM_AD_MNC_LEN_POS] & 0x0F))
        || (USIMM_MNC_THREE_BYTES_LEN == (pucAdContent[USIMM_AD_MNC_LEN_POS] & 0x0F)))
    {
        ucHplmnMncLen = pucAdContent[USIMM_AD_MNC_LEN_POS] & 0x0F;
    }

    return ucHplmnMncLen;
}

/*****************************************************************************
 函 数 名  : USIMM_BcdNumToAsciiNum
 功能描述  : BCD码转位ASCII码，代码来自NAS
 输入参数  : VOS_UINT8 *pucAsciiNum
             VOS_UINT8 *pucBcdNum
             VOS_UINT8 ucBcdNumLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月24日
    作    者   : j00168360
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID USIMM_BcdNumToAsciiNum(
    VOS_UINT8                           *pucAsciiNum, 
    VOS_UINT8                           *pucBcdNum, 
    VOS_UINT8                           ucBcdNumLen)
{
    VOS_UINT8       ucTmp;
    VOS_UINT8       ucFirstNumber;
    VOS_UINT8       ucSecondNumber;

    for (ucTmp = 0; ucTmp < ucBcdNumLen; ucTmp++)
    {
        ucFirstNumber = (VOS_UINT8)((*(pucBcdNum + ucTmp)) & 0x0f);             /*low four bits*/
        ucSecondNumber = (VOS_UINT8)(((*(pucBcdNum + ucTmp)) >> 4) & 0x0f);   /*high four bits*/
        if(ucFirstNumber <= 9)
        {
            *pucAsciiNum = ucFirstNumber + 0x30;
            pucAsciiNum++;
        }
        else if(0xa == ucFirstNumber)            /* the key is '*' */
        {
            *pucAsciiNum = 0x2a;
            pucAsciiNum++;
        }
        else if(0xb == ucFirstNumber)            /* the key is '#' */
        {
            *pucAsciiNum = 0x23;
            pucAsciiNum++;
        }
        else                                     /* the key is 'a','b'or 'c' */
        {
            *pucAsciiNum = ucFirstNumber + 0x57;
            pucAsciiNum++;
        }

        /* the following proceed the second number */
        if(0xf == ucSecondNumber)
        {
            break;
        }
        if(ucSecondNumber <= 9)
        {
            *pucAsciiNum = ucSecondNumber + 0x30;
            pucAsciiNum++;
        }
        else if(0xa == ucSecondNumber)            /* the key is '*' */
        {
            *pucAsciiNum = 0x2a;
            pucAsciiNum++;
        }
        else if(0xb == ucSecondNumber)            /* the key is '#' */
        {
            *pucAsciiNum = 0x23;
            pucAsciiNum++;
        }
        else                                     /* the key is 'a','b'or 'c' */
        {
            *pucAsciiNum = ucSecondNumber + 0x57;
            pucAsciiNum++;
        }

    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_ImsiBcd2Ascii
功能描述  :解析IMSI
输入参数  :无
输出参数  :pucAsciiStr--解析结果
           pucAsciiLen -- Ascii长度

返 回 值  :无
调用函数  :
修订记录  :
1. 日    期   : 2013年07月26日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ImsiBcd2Ascii(
    VOS_UINT8                           *pucAsciiStr)
{
    VOS_UINT32                          ulI = 0;
    VOS_UINT8                           ucTmp;
    VOS_UINT8                           aucImsi[USIMM_EF_IMSI_LEN];

    if (USIMM_API_SUCCESS != USIMM_GetCardIMSI(aucImsi))
    {
        USIMM_ERROR_LOG("USIMM_DecodeImsi: USIMM_GetCardIMSI fail.");
        return USIMM_SW_ERR;
    }

    /* 判断IMSI长度是否合法 */
    if (USIMM_IMSI_MAX_LEN < aucImsi[0])
    {
        USIMM_ERROR_LOG("USIMM_DecodeImsi: IMSI length is error.");
        return USIMM_SW_ERR;
    }

    /*国际移动用户识别码*/
    /*清空存放字符串的缓冲区*/
    for ( ulI = 0; ulI < (VOS_UINT32)(aucImsi[0]*2); ulI++ )
    {
        pucAsciiStr[ulI] = 0;
    }
    ucTmp = (aucImsi[1] >> 4) & 0x0f;

    /* 取出第一位BCD码进行转换 */
    USIMM_BcdNumToAsciiNum(pucAsciiStr, &ucTmp, 1);

    /* 将其余Bcd转换为Ascii码 */
    USIMM_BcdNumToAsciiNum(pucAsciiStr + 1, aucImsi + 2, (VOS_UINT8)((aucImsi[0]*2) - 1)/2);

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_GetAsciiMCCAndMNC
功能描述  :根据ascii形式的IMSI获取ascii形式的MCC和MNC
输入参数  :pucAsciiImsi  -- ascii形式的IMSI
输出参数  :pucAsciiMCC -- ascii形式的MCC
           pucAsciiMNC -- ascii形式的MNC
返 回 值  :无
调用函数  :
修订记录  :
1. 日    期   : 2013年07月26日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_GetAsciiMCCAndMNC(
    VOS_UINT8                           *pucAsciiImsi, 
    VOS_UINT8                           *pucAsciiMCC, 
    VOS_UINT8                           *pucAsciiMNC)
{
    VOS_UINT8                           ucMncLen;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           *pucData = VOS_NULL_PTR;

    /* 从AD文件中，获取HPLMN MNC长度 */
    if (USIMM_API_SUCCESS != USIMM_GetCachedFile(USIMM_USIM_EFAD_STR, &ulDataLen, &pucData, USIMM_GUTL_APP))
    {
       USIMM_ERROR_LOG("USIMM_DecodeImsi: USIMM_GetCachedFile fail.");
       return;
    }

    /* 获取MNC长度 */
    ucMncLen = USIMM_GetMncLen(pucData, ulDataLen);

    /* 获取MCC */
    pucAsciiMCC[0] = pucAsciiImsi[0];
    pucAsciiMCC[1] = pucAsciiImsi[1];
    pucAsciiMCC[2] = pucAsciiImsi[2];

    /* 获取MNC */
    if (USIMM_MNC_TWO_BYTES_LEN == ucMncLen)
    {
        pucAsciiMNC[0] = '0';
        pucAsciiMNC[1] = pucAsciiImsi[3];
        pucAsciiMNC[2] = pucAsciiImsi[4];
    }
    else
    {
        pucAsciiMNC[0] = pucAsciiImsi[3];
        pucAsciiMNC[1] = pucAsciiImsi[4];
        pucAsciiMNC[2] = pucAsciiImsi[5];
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_IsSIMServiceAvailable
功能描述  :获取SIM卡服务状态　
输入参数  :enService:服务ID
输出参数  :无
返 回 值  :PS_USIM_SERVICE_NOT_AVAILIABLE
           PS_USIM_SERVICE_NOT_AVAILIABLE
被调函数  :
修订记录  :
1. 日    期   : 2013年7月26日
   作    者   : g47350
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_IsSIMServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32      enService)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulFileNum;
    VOS_UINT8                           ucBitNo;

    if (USIMM_CARD_SERVIC_AVAILABLE != USIMM_CCB_GetAppService(USIMM_GUTL_APP))
    {
        USIMM_WARNING_LOG("USIMM_IsSIMServiceAvailable: The Card Type is Wrong");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    /* 查询当前的文件缓冲 */
    ulResult = USIMM_PoolFindFile(EFSST, &ulFileNum, USIMM_GUTL_APP);

    if (ulResult != USIMM_API_SUCCESS)
    {
        USIMM_WARNING_LOG("USIMM_IsServiceAvailable: Read File is Failed");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    ucBitNo = (VOS_UINT8)((enService * 2) - 1);

    /* 获取缓冲的Bit信息 */
    ulResult = USIMM_GetBitFromBuf(USIMM_CCB_GetPoolFileByIndex(ulFileNum)->pucContent,
                                    ucBitNo,
                                    USIMM_CCB_GetPoolFileByIndex(ulFileNum)->usLen);

    /* SIM卡还判断ACTIVE位 */
    if (PS_USIM_SERVICE_AVAILIABLE == ulResult)
    {
        ulResult = USIMM_GetBitFromBuf(USIMM_CCB_GetPoolFileByIndex(ulFileNum)->pucContent,
                                        (ucBitNo+1),
                                        USIMM_CCB_GetPoolFileByIndex(ulFileNum)->usLen);
    }

    if (USIMM_BITNOFOUNE == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_IsServiceAvailable: The Service is Out of File");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_IsUSIMServiceAvailable
功能描述  :获取USIM卡服务状态　
输入参数  :enService:服务ID
输出参数  :无
返 回 值  :PS_USIM_SERVICE_NOT_AVAILIABLE
           PS_USIM_SERVICE_NOT_AVAILIABLE
被调函数  :
修订记录  :
1. 日    期   : 2013年7月26日
   作    者   : g47350
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_IsUSIMServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32      enService)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulFileNum;
    VOS_UINT8                           ucBitNo;
    USIMM_TEST_PHYCARD_TYPE_ENUM_UINT32 enCardType;
    USIMM_CARD_SERVIC_ENUM_UINT32       enAppService;

    enCardType   = USIMM_CCB_GetTestCardType();
    enAppService = USIMM_CCB_GetAppService(USIMM_GUTL_APP);

    if ((USIMM_TEST_TYPE_ROM_SIM == enCardType)
        || (USIMM_CARD_SERVIC_AVAILABLE != enAppService))
    {
        USIMM_WARNING_LOG("USIMM_IsUSIMServiceAvailable: The Card Type is Wrong");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    /* 查询当前的文件缓冲 */
    ulResult = USIMM_PoolFindFile(EFUST, &ulFileNum, USIMM_GUTL_APP);

    if(ulResult != USIMM_API_SUCCESS)
    {
        USIMM_WARNING_LOG("USIMM_IsUSIMServiceAvailable: Read File is Failed");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    ucBitNo = (VOS_UINT8)((enService - SIM_SVR_BUTT) + 1);

    /* 获取缓冲的Bit信息 */
    ulResult = USIMM_GetBitFromBuf(USIMM_CCB_GetPoolFileByIndex(ulFileNum)->pucContent,
                                    ucBitNo,
                                    USIMM_CCB_GetPoolFileByIndex(ulFileNum)->usLen);

    if(USIMM_BITNOFOUNE == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_IsUSIMServiceAvailable: The Service is Out of File");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    return ulResult;

}

/*****************************************************************************
函 数 名  :USIMM_IsSimuISIMServiceAvailable
功能描述  :获取模拟ISIM卡服务状态　
输入参数  :enService:服务ID
输出参数  :无
返 回 值  :PS_USIM_SERVICE_NOT_AVAILIABLE
           PS_USIM_SERVICE_NOT_AVAILIABLE
被调函数  :
修订记录  :
1. 日    期   : 2013年7月26日
   作    者   : g47350
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_IsSimuISIMServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32      enService)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucBitNo;

    /* SM-over-IP 对应了USIM上的两个服务项 */
    if (ISIM_SVR_SOI == enService)
    {
        ulResult = USIMM_IsUSIMServiceAvailable(USIM_SVR_DATA_DL_SMSPP);

        if (PS_USIM_SERVICE_NOT_AVAILIABLE == ulResult)
        {
            return PS_USIM_SERVICE_NOT_AVAILIABLE;
        }

        ulResult = USIMM_IsUSIMServiceAvailable(USIM_SVR_SM_VOER_IP);
    }
    else
    {
        /* 查找USIM上对应ISIM服务位位置 */
        ucBitNo = g_aucServIsimToUsim[enService - USIM_SVR_BUTT];

        /* 没有对应服务位则返回不支持 */
        if (0 == ucBitNo)
        {
            return PS_USIM_SERVICE_NOT_AVAILIABLE;
        }

        ulResult = USIMM_IsUSIMServiceAvailable(ucBitNo);
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_IsISIMServiceAvailable
功能描述  :获取ISIM卡服务状态　
输入参数  :enService:服务ID
输出参数  :无
返 回 值  :PS_USIM_SERVICE_NOT_AVAILIABLE
           PS_USIM_SERVICE_NOT_AVAILIABLE
被调函数  :
修订记录  :
1. 日    期   : 2013年7月26日
   作    者   : g47350
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_IsISIMServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32      enService)
{
    VOS_UINT32                          ulFileNum;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucBitNo;

    /* 由于没有真实的ISIM卡需要读取USIM卡中的UST来实现 */
    if (USIMM_CARD_SERVIC_AVAILABLE != USIMM_CCB_GetAppService(USIMM_IMS_APP))
    {
        USIMM_WARNING_LOG("USIMM_IsISIMServiceAvailable: The Card Type is Wrong");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    /* 判断是否为模拟ISIM */
    if (VOS_TRUE == USIMM_CCB_GetUsimSimulateIsimStatus())
    {
        return USIMM_IsSimuISIMServiceAvailable(enService);
    }

     /* 查询当前的文件缓冲 */
    ulResult = USIMM_PoolFindFile(EFISIMIST, &ulFileNum, USIMM_IMS_APP);

     if (ulResult != USIMM_API_SUCCESS)
     {
         USIMM_WARNING_LOG("USIMM_IsISIMServiceAvailable: Read File is Failed");

         return PS_USIM_SERVICE_NOT_AVAILIABLE;
     }

     ucBitNo = (VOS_UINT8)((enService - USIM_SVR_BUTT) + 1);

     /* 获取缓冲的Bit信息 */
     ulResult = USIMM_GetBitFromBuf(USIMM_CCB_GetPoolFileByIndex(ulFileNum)->pucContent,
                                     ucBitNo,
                                     USIMM_CCB_GetPoolFileByIndex(ulFileNum)->usLen);

     if (USIMM_BITNOFOUNE == ulResult)
     {
         USIMM_WARNING_LOG("USIMM_IsISIMServiceAvailable: The Service is Out of File");

         return PS_USIM_SERVICE_NOT_AVAILIABLE;
     }

     return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_IsUIMServiceAvailable
功能描述  :获取ISIM卡服务状态　
输入参数  :enService:服务ID
输出参数  :无
返 回 值  :PS_USIM_SERVICE_NOT_AVAILIABLE
           PS_USIM_SERVICE_NOT_AVAILIABLE
被调函数  :
修订记录  :
1. 日    期   : 2013年7月26日
   作    者   : g47350
   修改内容   : Creat
2. 日    期   : 2015年04月17日
   作    者   : c00299064
   修改内容   : 多应用迭代开发
*****************************************************************************/
VOS_UINT32 USIMM_IsUIMServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32      enService
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulFileNum;
    VOS_UINT8                           ucBitNo;

    if (USIMM_CARD_SERVIC_AVAILABLE != USIMM_CCB_GetAppService(USIMM_CDMA_APP))
    {
        USIMM_WARNING_LOG("USIMM_IsUIMServiceAvailable: The Card Type is Wrong");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    /* 查询当前的文件缓冲 */
    ulResult = USIMM_PoolFindFile(EFCST, &ulFileNum, USIMM_CDMA_APP);

    if(ulResult != USIMM_API_SUCCESS)
    {
        USIMM_WARNING_LOG("USIMM_IsUIMServiceAvailable: Read File is Failed");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    /* 根据协议应当有两位来判断服务在不在，但是由于此文件不可写，只判断卡支持不支持 */
    ucBitNo = (VOS_UINT8)((enService - ISIM_SVR_BUTT) * 2 + 1);

    /* 获取缓冲的Bit信息 */
    ulResult = USIMM_GetBitFromBuf(USIMM_CCB_GetPoolFileByIndex(ulFileNum)->pucContent,
                                    ucBitNo,
                                    USIMM_CCB_GetPoolFileByIndex(ulFileNum)->usLen);

    /* UIM卡还判断ACTIVE位 */
    if (PS_USIM_SERVICE_AVAILIABLE == ulResult)
    {
        ulResult = USIMM_GetBitFromBuf(USIMM_CCB_GetPoolFileByIndex(ulFileNum)->pucContent,
                                        (ucBitNo+1),
                                        USIMM_CCB_GetPoolFileByIndex(ulFileNum)->usLen);
    }

    if(USIMM_BITNOFOUNE == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_IsUIMServiceAvailable: The Service is Out of File");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_IsUIMServiceAvailable
功能描述  :获取ISIM卡服务状态　
输入参数  :enService:服务ID
输出参数  :无
返 回 值  :PS_USIM_SERVICE_NOT_AVAILIABLE
           PS_USIM_SERVICE_NOT_AVAILIABLE
被调函数  :
修订记录  :
1. 日    期   : 2013年7月26日
   作    者   : g47350
   修改内容   : Creat
2. 日    期   : 2015年04月17日
   作    者   : c00299064
   修改内容   : 多应用迭代开发
*****************************************************************************/
VOS_UINT32 USIMM_IsCSIMServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32      enService
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulFileNum;
    VOS_UINT8                           ucBitNo;

    if (USIMM_CARD_SERVIC_AVAILABLE != USIMM_CCB_GetAppService(USIMM_CDMA_APP))
    {
        USIMM_WARNING_LOG("USIMM_IsUIMServiceAvailable: The Card Type is Wrong");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    /* 查询当前的文件缓冲 */
    ulResult = USIMM_PoolFindFile(EFCSIMST, &ulFileNum, USIMM_CDMA_APP);

    if(ulResult != USIMM_API_SUCCESS)
    {
        USIMM_WARNING_LOG("USIMM_IsUIMServiceAvailable: Read File is Failed");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    ucBitNo = (VOS_UINT8)((enService - UIM_SVR_BUTT) + 1);

    /* 获取缓冲的Bit信息 */
    ulResult = USIMM_GetBitFromBuf(USIMM_CCB_GetPoolFileByIndex(ulFileNum)->pucContent,
                                    ucBitNo,
                                    USIMM_CCB_GetPoolFileByIndex(ulFileNum)->usLen);

    if(USIMM_BITNOFOUNE == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_IsUIMServiceAvailable: The Service is Out of File");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    return ulResult;
}
/*****************************************************************************
函 数 名  :USIMM_ReadFile
功能描述  :实现文件读取操作
输入参数  :enEFFileType -- 文件类型
           ucRecordNum -- 记录数
           usDataLen -- 更新数据长度
           pucData -- 更新数据
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2013年07月23日
   作    者   : j00168360
   修改内容   : Creat

2. 日    期   : 2015年3月31日
   作    者   : d00212987
   修改内容   : 卡多应用迭代II开发
*****************************************************************************/
VOS_UINT32 USIMM_ReadFile(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_EFFCP_ST                     *pstCurEFFcp,
    USIMM_GETCNF_INFO_STRU             *pstCnfInfo)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucChannelID;

    ucChannelID = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelID)
    {
        USIMM_ERROR_LOG("USIMM_ReadFile: USIMM_CCB_GetAppChNO Fail");
        return USIMM_SW_ERR;
    }

    switch(pstCurEFFcp->enFileType)
    {
        case USIMM_EFSTRUCTURE_TRANSPARENT:       /*读取二进制文件*/
            ulResult = USIMM_SendReadBinaryApdu(ucChannelID,
                                        VOS_NULL,
                                        pstCnfInfo->usDataLen,
                                        pstCnfInfo->pucEf);
            break;

        case USIMM_EFSTRUCTURE_FIXED:             /*读取记录文件*/
        case USIMM_EFSTRUCTURE_CYCLE:
            ulResult = USIMM_SendReadRecordApdu(ucChannelID,
                                                pstCurEFFcp->ucRecordNum,
                                                pstCurEFFcp->ucRecordLen,
                                                pstCnfInfo->ucRecordNum,
                                                pstCnfInfo->pucEf);
            break;

        default:
            USIMM_WARNING_LOG("USIMM_GetFileHandle: The File Type is Not Support");
            ulResult = USIMM_SW_OTHER_ERROR;
            break;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_GetReadFilePara
功能描述  :获取读文件的参数
输入参数  :ucRecordNum -- 文件记录数
           pstMsg--指向读取文件消息结构
输出参数  :pstCnfInfo -- 指向回复消息结构
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2013年7月22日
   作    者   : j00168360
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_GetReadFilePara(
    VOS_UINT8                           ucRecordNum,
    USIMM_EFFCP_ST                     *pstEFInfo,
    USIMM_GETCNF_INFO_STRU             *pstCnfInfo
)
{
    VOS_UINT32                          ulResult = USIMM_SW_OK;

    if (VOS_NULL_PTR == pstEFInfo)
    {
        USIMM_ERROR_LOG("USIMM_GetReadFilePara: EFInfo is NUll!");

        return USIMM_SW_OUTOF_RANGE;
    }

    switch(pstEFInfo->enFileType)
    {
        case USIMM_EFSTRUCTURE_TRANSPARENT:       /*读取二进制文件*/
            pstCnfInfo->usDataLen   = (pstEFInfo->usFileLen > USIMM_MAX_FILE_SIZE) ? USIMM_MAX_FILE_SIZE : pstEFInfo->usFileLen;

            pstCnfInfo->usEfLen     = pstCnfInfo->usDataLen;                                /*读取长度和文件长度一致*/

            break;

        case USIMM_EFSTRUCTURE_FIXED:                   /*读取记录文件*/
        case USIMM_EFSTRUCTURE_CYCLE:
            if(ucRecordNum > pstEFInfo->ucRecordNum)    /*检查读取的记录号是否越界*/
            {
                USIMM_ERROR_LOG("USIMM_GetReadFilePara: The Record Index is Out of the File Range");

                ulResult = USIMM_SW_OUTOF_RANGE;

                break;
            }

            pstCnfInfo->usEfLen = pstEFInfo->ucRecordLen;     /*即使读取全部记录也添为记录长度*/

            pstCnfInfo->ucRecordNum = ucRecordNum;

            if(USIMM_READ_ALLRECORD == ucRecordNum)
            {
                pstCnfInfo->ucTotalNum = pstEFInfo->ucRecordNum;

                pstCnfInfo->usDataLen  = pstEFInfo->usFileLen;
            }
            else
            {
                pstCnfInfo->ucTotalNum = 1;

                pstCnfInfo->usDataLen  = pstEFInfo->ucRecordLen;
            }

            break;

        default:
            USIMM_WARNING_LOG("USIMM_GetReadFilePara: The File Type is Not Support");

            ulResult = USIMM_SW_OTHER_ERROR;

            break;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_CardStatusRegCbFuncProc
功能描述  :SIM卡热插拨注册回调处理
输入参数  :无
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2013年9月25日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_CardStatusRegCbFuncProc(VOS_VOID)
{
    NVIM_USIM_CARD_STATUS_CB_TYPE_STRU  stType;

    if (NV_OK != NV_Read(en_NV_Item_Card_Status_Cb_Type, &stType, sizeof(NVIM_USIM_CARD_STATUS_CB_TYPE_STRU)))
    {
        stType.enType = USIMM_CARD_STATUS_REG_TYPE_M2M;
    }

    if (USIMM_CARD_STATUS_REG_TYPE_M2M == stType.enType)
    {
        mdrv_sci_register_callback(USIMM_SciCardStatusIndCbFunc);
    }
    else if (USIMM_CARD_STATUS_REG_TYPE_E5 == stType.enType)
    {
        mdrv_sci_register_callback(USIMM_SCICardOutNotify);
    }
    else
    {
        return;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_IsCLEnable
功能描述  :获取C+L功能设置标记状态
输入参数  :无
输出参数  :无
返 回 值  :VOS_FALSE/VOS_TRUE
修订记录  :
1. 日    期   : 2014年1月22日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_BOOL USIMM_IsCLEnable(VOS_VOID)
{
    TAF_NV_LC_CTRL_PARA_STRU            stNVData;

    if (NV_OK != NV_Read(en_NV_Item_LC_Ctrl_PARA, &stNVData, sizeof(TAF_NV_LC_CTRL_PARA_STRU)))
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == stNVData.ucLCEnableFlg)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
函 数 名  :USIMM_GetRATMode
功能描述  :获取C+L 接入模式功能设置标记状态
输入参数  :无
输出参数  :无
返 回 值  :RAT_COMBINE_GUL/RAT_COMBINE_CL
修订记录  :
1. 日    期   : 2013年7月22日
   作    者   : j00168360
   修改内容   : Creat

*****************************************************************************/
TAF_NVIM_LC_RAT_COMBINED_ENUM_UINT8 USIMM_GetRATMode(VOS_VOID)
{
    TAF_NV_LC_CTRL_PARA_STRU    stNVData;

    if (NV_OK != NV_Read(en_NV_Item_LC_Ctrl_PARA, &stNVData, sizeof(TAF_NV_LC_CTRL_PARA_STRU)))
    {
        return TAF_NVIM_LC_RAT_COMBINED_GUL;
    }

    if (TAF_NVIM_LC_RAT_COMBINED_CL == stNVData.enRatCombined)
    {
        return TAF_NVIM_LC_RAT_COMBINED_CL;
    }
    else
    {
        return TAF_NVIM_LC_RAT_COMBINED_GUL;
    }
}

/*****************************************************************************
函 数 名  :USIMM_GetPreferApp
功能描述  :获取优先APP
输入参数  :无
输出参数  :无
返 回 值  :USIMM_NV_GUTL_APP/USIMM_NV_CDMA_APP
修订记录  :
1. 日    期   : 2015年6月12日
   作    者   : h00300778
   修改内容   : Creat
*****************************************************************************/
USIMM_NV_CARDAPP_ENUM_UINT32 USIMM_GetPreferApp(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulCdmaHit;
    VOS_UINT32                          ulGutlHit;
    USIMM_APP_PRIORITY_CONFIG_STRU      stAppInfo;

    /* NV项读取失败，默认按GUTL类型返回 */
    if (NV_OK != NV_Read(en_NV_Item_Usim_App_Priority_Cfg, &stAppInfo, sizeof(USIMM_APP_PRIORITY_CONFIG_STRU)))
    {
        return USIMM_NV_GUTL_APP;
    }

    ulCdmaHit = VOS_FALSE;
    ulGutlHit = VOS_FALSE;

    /* 查找CDMA和GUTL应用在NV项中的位置 */
    for (i = 0; i < stAppInfo.ucAppNum; i++)
    {
        if (USIMM_NV_GUTL_APP == stAppInfo.aenAppList[i])
        {
            ulGutlHit = VOS_TRUE;

            break;
        }

        if (USIMM_NV_CDMA_APP == stAppInfo.aenAppList[i])
        {
            ulCdmaHit = VOS_TRUE;

            break;
        }
    }

    if (VOS_TRUE == ulGutlHit)
    {
        return USIMM_NV_GUTL_APP;
    }
    else if (VOS_TRUE == ulCdmaHit)
    {
        return USIMM_NV_CDMA_APP;
    }
    else
    {
        return USIMM_NV_GUTL_APP;
    }
}

/*****************************************************************************
 函 数 名  : USIMM_SetAccFileAccess
 功能描述  : 规避0x6F78 Acc文件接入权限为零的问题
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月30日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  USIMM_SetAccFileAccess(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulRecordNum;
    VOS_UINT16                         *pusData;
    VOS_UINT32                          ulRandomNum;
    VOS_UINT8                           ucByteOffset;
    VOS_UINT8                           ucBitOffset;
    VOS_UINT8                           aucData[2] = {0,0};

    ulResult    =   USIMM_PoolFindFile(0x6F78, &ulRecordNum, USIMM_GUTL_APP);

    if (VOS_ERR == ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SetRandomAccess: File Could not Found");/*打印错误*/

        return;
    }

    if (VOS_NULL_PTR == USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->pucContent)
    {
        USIMM_ERROR_LOG("USIMM_SetRandomAccess: File Content is Empty");/*打印错误*/

        return;
    }

    pusData = (VOS_UINT16 *)USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->pucContent;

    if (VOS_NULL == *pusData)
    {
        ulRandomNum = (VOS_UINT32)VOS_Rand(10);

        ulRandomNum = ulRandomNum % 10;

        ucByteOffset    = (ulRandomNum < 8)?1:0;
        ucBitOffset     = ulRandomNum % 8;

        /*lint -e701*/
        aucData[ucByteOffset] |= (VOS_UINT8)(1<<ucBitOffset);
        /*lint +e701*/

        /*lint -e534*/
        VOS_MemCpy(pusData, aucData, sizeof(VOS_UINT16));
        /*lint +e534*/
    }

    return;
}

/*****************************************************************************
 函 数 名  : USIMM_SetImsiFile
 功能描述  : USIMM模块规避IMSI文件第一个字节为全FF的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月11日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID USIMM_SetImsiFile(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulRecordNum;
    VOS_UINT8                          *pucData;
    VOS_UINT8                           aucFirstByte;

    ulResult = USIMM_PoolFindFile(EFIMSI, &ulRecordNum, USIMM_GUTL_APP);

    if (VOS_ERR == ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SetImsiFile: File Could not Found");/*打印错误*/

        return;
    }

    if (VOS_NULL_PTR == USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->pucContent)
    {
        USIMM_ERROR_LOG("USIMM_SetImsiFile: File Content is Empty");/*打印错误*/

        return;
    }

    pucData = USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->pucContent;

    aucFirstByte = pucData[0];

    if (VOS_NULL_BYTE == aucFirstByte)
    {
        pucData[0] = 0x08;
    }

    return;
}

/*****************************************************************************
函 数 名  : USIMM_UICC_DecodeEFDIR
功能描述  : 解析EFDIR内容，并且选中其中的3GPP应用
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_SelectEFByID
           USIMM_ReadLFFile
           USIMM_SelectFile_APDU
修订记录  :
1. 日    期   : 2015年3月3日
    作    者   : g00256031
    修改内容   : Creat

*****************************************************************************/
USIMM_CARD_TYPE_ENUM_UINT32 USIMM_COMM_CardAppToType(
    USIMM_CARDAPP_ENUM_UINT32       enAppType
)
{
    if (USIMM_TEST_TYPE_ROM_SIM == USIMM_CCB_GetTestCardType())
    {
        return USIMM_CARD_ROM_SIM;
    }

    if (USIMM_CARD_SERVIC_ABSENT == USIMM_CCB_GetAppService(enAppType))
    {
        return USIMM_CARD_NOCARD;
    }

    if (USIMM_GUTL_APP == enAppType)
    {
        if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
        {
            return USIMM_CARD_SIM;
        }

        if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
        {
            return USIMM_CARD_USIM;
        }
    }

    if (USIMM_IMS_APP == enAppType)
    {
        return USIMM_CARD_ISIM;
    }

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    if (USIMM_CDMA_APP == enAppType)
    {
        if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
        {
            return USIMM_CARD_UIM;
        }

        if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
        {
            return USIMM_CARD_CSIM;
        }
    }
#endif

    return USIMM_CARD_NOCARD;
}

/*****************************************************************************
函 数 名  : USIMM_SelectAID
功能描述  : 选中其中的3GPP应用
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2015年3月18日
    作    者   : zhuli
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_SelectAIDFile(
    VOS_UINT8                           ucChannelNo,
    USIMM_SELECT_P2_PARA_ENUM_UINT8     enMode,
    USIMM_AID_INFO_STRU                *pstAIDInfo,
    USIMM_APDU_RSP_STRU                *pstApduRsp
)
{
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;
    VOS_UINT32                          ulResult;
    USIMM_COMM_CARD_APP_INFO_STRU       *pstAppInfo;

    pstAppInfo = USIMM_CCB_GetAppInfoByCH(ucChannelNo);

    if (VOS_NULL_PTR == pstAppInfo)
    {
        USIMM_ERROR_LOG("USIMM_SelectAID: Input ucChannel Error");

        return USIMM_SW_ERR;
    }

    stApduHead.ucChannel    = ucChannelNo;
    stApduHead.ucINS        = CMD_INS_SELECT;
    stApduHead.ucP1         = USIMM_SELECT_BY_DF_NAME;
    stApduHead.ucP2         = enMode;
    stApduHead.ucP3         = (VOS_UINT8)pstAIDInfo->ulAIDLen;

    stApduData.ulDataLen    = pstAIDInfo->ulAIDLen;
    stApduData.pucData      = pstAIDInfo->aucAID;

    /*保存FCP返回的数据长度和内容，如果失败，会自动清空为0*/
    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stApduData,
                                    pstApduRsp);

    pstAppInfo->stAdfInfo.usFcpLen = pstApduRsp->usRspLen;

    if (USIMM_SW_OK == ulResult)
    {
        pstAppInfo->stAdfInfo.ulAIDLen = pstAIDInfo->ulAIDLen;

        /*lint -e534 */
        VOS_MemCpy(pstAppInfo->stAdfInfo.aucAID, pstAIDInfo->aucAID, pstAIDInfo->ulAIDLen);
        /*lint +e534 */

        USIMM_CCB_SetAIDFcp(ucChannelNo, pstApduRsp->usRspLen,pstApduRsp->aucRsp);

        return USIMM_SW_OK;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_CloseChannel
功能描述  :关闭逻辑通道
输入参数  :ucChannelID: 逻辑通道号的地址
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2013年5月15日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_CloseChannel(
    VOS_UINT8                           ucChannelNo)
{
    VOS_UINT32                          ulResult;
    USIMM_COMM_CARD_APP_INFO_STRU       *pstAppInfo;

    if (USIMM_APDU_BASECHANNEL == ucChannelNo)
    {
        USIMM_WARNING_LOG("USIMM_CloseChannel: ucChannelNo Error");

        return USIMM_SW_ERR;
    }

    pstAppInfo = USIMM_CCB_GetAppInfoByCH(ucChannelNo);

    if (VOS_NULL_PTR != pstAppInfo)
    {
        pstAppInfo->stAdfInfo.ulAIDLen  = VOS_NULL;

        pstAppInfo->enAppType           = USIMM_UNLIMIT_APP_BUTT;
    }

    USIMM_CCB_ClearAIDFcp(ucChannelNo);

    USIMM_CCB_ClearResponse(ucChannelNo);

    ulResult = USIMM_SendCloseChannelApdu(ucChannelNo);

    /*判断检查结果*/
    if (USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_CloseChannel: USIMM_CheckSW Error");

        return ulResult;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_OpenChannel
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
VOS_UINT32 USIMM_OpenChannel(
    VOS_UINT8                           *pucChannelNo)
{
    VOS_UINT32                          ulResult;
    USIMM_CARDAPP_ENUM_UINT32           i;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT8                           ucChannelNo;

    ulResult = USIMM_SendOpenChannelApdu(&ucChannelNo);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_OpenChannel: USIMM_OpenChannelApdu err.");

        return ulResult;
    }

    enAppType =  USIMM_CCB_GetAppTypeByCH(ucChannelNo);

    if (USIMM_UNLIMIT_APP_BUTT != enAppType)
    {
        USIMM_ERROR_LOG("USIMM_OpenChannel: App is using.");

        return USIMM_SW_ERR;
    }

    for(i=USIMM_UNLIMIT_APP1; i<USIMM_UNLIMIT_AUTO; i++)
    {
        if (VOS_NULL_BYTE == USIMM_CCB_GetAppChNO(i))
        {
            USIMM_CCB_SetAppChNO(ucChannelNo, i);

            *pucChannelNo = ucChannelNo;

            return USIMM_SW_OK;
        }
    }

    USIMM_ERROR_LOG("USIMM_OpenChannel: USIMM_CCB_GetAppChNO err.");

    (VOS_VOID)USIMM_CloseChannel(ucChannelNo);

    return USIMM_SW_ERR;
}

/*****************************************************************************
函 数 名  :USIMM_SearchAllAID
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
VOS_BOOL USIMM_SearchAllAID(
    VOS_UINT32                          ulAIDLen,
    VOS_UINT8                          *pucAID,
    VOS_UINT8                          *pucChannelNo
)
{
    VOS_UINT8                           i;
    VOS_BOOL                            bResult;
    VOS_UINT32                          ulDataLen;
    USIMM_UICC_ADF_INFO_STRU           *pstADF;

    if (VOS_NULL == ulAIDLen)
    {
        return VOS_FALSE;
    }

    bResult = VOS_FALSE;

    for(i=0; i<USIMM_CHANNEL_NUMBER_MAX; i++)
    {
        pstADF = USIMM_CCB_GetAdfInfoByCH(i);

        if (VOS_NULL_PTR == pstADF)
        {
            break;
        }

        ulDataLen = (pstADF->ulAIDLen>ulAIDLen) ? pstADF->ulAIDLen : ulAIDLen;

        if (VOS_OK == VOS_MemCmp(pstADF->aucAID, pucAID, ulDataLen))
        {
            bResult = VOS_TRUE;

            *pucChannelNo = i;

            break;
        }
    }

    return bResult;
}

/*****************************************************************************
函 数 名  : USIMM_SelectFileByDefFileId
功能描述  : 通过DEF FILEID 选择文件
输入参数  : enAppType
            enEfFcpFlag
            enDefFileId
输出参数  :无
返 回 值  : VOS_OK/VOS_ERR

修订记录  :
1. 日    期   : 2015年4月08日
   作    者   : C00299064
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SelectFileByDefFileId(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_FILE_NEED_FCP_ENUM_UINT32     enEfFcpFlag,
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileId
)
{
    USIMM_FILEPATH_INFO_STRU           stFilePath;
    VOS_CHAR                          *pcPath        = VOS_NULL_PTR;

    /*lint -e534*/
    VOS_MemSet(&stFilePath, 0, sizeof(USIMM_FILEPATH_INFO_STRU));
    /*lint +e534*/

    if (VOS_ERR == USIMM_ChangeDefFileToPath(enDefFileId, &pcPath))
    {
        USIMM_ERROR_LOG("USIMM_SelectFileByFileId:USIMM_ChangeDefFileToPath err");
        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(stFilePath.acPath, pcPath, VOS_StrLen(pcPath) + 1);
    /*lint +e534*/
    stFilePath.ulPathLen    = VOS_StrLen(pcPath);

    return USIMM_SelectFile(enAppType, enEfFcpFlag, &stFilePath);
}

/*****************************************************************************
函 数 名  :USIMM_IS_EF_FILE
功能描述  :USIMM判断当前是否是DF
输入参数  :usFileId:文件ID
输出参数  :无
返 回 值  :VOS_TRUE/VOS_FALSE
修订记录  :
1. 日    期   : 2015年5月12日
   作    者   : H00300778
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_IS_EF_FILE(
    VOS_UINT16                          usFileId)
{
    if (USIMM_EF_FILE == ((usFileId>>0x0C)&0x01))
    {
        return VOS_TRUE;
    }
    else if ((VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulPKCS15)
          && ((0x5031 == usFileId)
           || (0x5027 == usFileId)
           || (0x5006 == usFileId)
           || (0x5003 == usFileId)
           || (0x2003 == usFileId)
           || (0x5032 == usFileId)
           || (0x5207 == usFileId)))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
函 数 名  :USIMM_MakeCHAPCmdData
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2015年6月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_MakeCHAPCmdData(
    USIMM_COMPUTEIP_CHAP_STRU           *pstChapData,
    USIMM_U8_DATA_STRU                  *pstCmdData)
{
    pstCmdData->aucData[0]  = pstChapData->ucChapID;

    pstCmdData->ucDataLen   = 1;

    pstCmdData->aucData[1]  = pstChapData->ucNAI_Enter_Index;

    pstCmdData->ucDataLen++;

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[2],
                            pstChapData->stChapChallenge.aucData,
                            pstChapData->stChapChallenge.ucDataLen);

    pstCmdData->ucDataLen += pstChapData->stChapChallenge.ucDataLen;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_MakeMNHACmdData
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2015年6月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_MakeMNHACmdData(
    USIMM_COMPUTEIP_MNHA_STRU           *pstMNHAData,
    USIMM_U8_DATA_STRU                  *pstCmdData)
{
    pstCmdData->ucDataLen = VOS_NULL;

    if (USIMM_SPECAUTH_BLOCK_BUTT <= pstMNHAData->enBlockType)
    {
        USIMM_ERROR_LOG("USIMM_MakeMNHACmdData: enBlockType Error");

        return USIMM_SW_CMD_ERROR;
    }

    if (  (USIMM_SPECAUTH_BLOCK_FIRST == pstMNHAData->enBlockType)
        ||(USIMM_SPECAUTH_BLOCK_SINGLE== pstMNHAData->enBlockType))
    {
        pstCmdData->ucDataLen   = 1;

        pstCmdData->aucData[0]  = pstMNHAData->ucNAI_Enter_Index;
    }
    else
    {
        pstCmdData->ucDataLen   = 0;
    }

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[pstCmdData->ucDataLen], 
                            pstMNHAData->stChapChallenge.aucData,
                            pstMNHAData->stChapChallenge.ucDataLen);

    pstCmdData->ucDataLen += pstMNHAData->stChapChallenge.ucDataLen;

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_MakeMIPCmdData
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2015年6月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_MakeMIPCmdData(
    USIMM_COMPUTEIP_MIPRRQHASH_STRU     *pstMIPData,
    USIMM_U8_DATA_STRU                  *pstCmdData)
{
    pstCmdData->ucDataLen = VOS_NULL;

    if (USIMM_SPECAUTH_BLOCK_BUTT <= pstMIPData->enBlockType)
    {
        USIMM_ERROR_LOG("USIMM_MakeMIPCmdData: enBlockType Error");

        return USIMM_SW_CMD_ERROR;
    }

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[0],
                            pstMIPData->stMIPRRQData.aucData,
                            pstMIPData->stMIPRRQData.ucDataLen);

    pstCmdData->ucDataLen = pstMIPData->stMIPRRQData.ucDataLen;

    if ( (USIMM_SPECAUTH_BLOCK_SINGLE == pstMIPData->enBlockType)
        ||(USIMM_SPECAUTH_BLOCK_LAST  == pstMIPData->enBlockType))
    {
        (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[pstCmdData->ucDataLen], 
                                pstMIPData->stMNAAAExHeader.aucData,
                                pstMIPData->stMNAAAExHeader.ucDataLen);

        pstCmdData->ucDataLen += pstMIPData->stMNAAAExHeader.ucDataLen;
    }

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_MakeMNAAACmdData
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2015年6月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_MakeMNAAACmdData(
    USIMM_COMPUTEIP_MNAAA_STRU          *pstMNAAAData,
    USIMM_U8_DATA_STRU                  *pstCmdData)
{
    pstCmdData->aucData[0]  = pstMNAAAData->ucNAI_Enter_Index;

    pstCmdData->ucDataLen   = 1;

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[1],
                            pstMNAAAData->stChallenge.aucData,
                            pstMNAAAData->stChallenge.ucDataLen);

    pstCmdData->ucDataLen += pstMNAAAData->stChallenge.ucDataLen;

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_MakeHRPDCmdData
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2015年6月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_MakeHRPDCmdData(
    USIMM_COMPUTEIP_HRPD_STRU           *pstHRPDData,
    USIMM_U8_DATA_STRU                  *pstCmdData)
{
    pstCmdData->aucData[0]  = pstHRPDData->ucCHAPID;

    pstCmdData->ucDataLen   = 1;

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[1],
                            pstHRPDData->stChapChallenge.aucData,
                            pstHRPDData->stChapChallenge.ucDataLen);

    pstCmdData->ucDataLen += pstHRPDData->stChapChallenge.ucDataLen;

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_CDMASpecAuthComputeIP
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2015年6月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_CdmaSpecAuthComputeIP(
    VOS_UINT8                           ucChannelID,
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader,
    USIMM_COMPUTEIP_AUTH_STRU           *pstComputeIP)
{
    VOS_UINT32                  ulResult;
    USIMM_U8_DATA_STRU          stCmdData;
    USIMM_APDU_RSP_STRU         stRspData;
    VOS_UINT8                   ucP2;
    USIMM_COMPUTEIP_CNF_STRU    stComputeIPCnf;

    ucP2 = VOS_NULL;

    switch(pstComputeIP->enComputeIPType)
    {
        case USIMM_COMPUTEIP_CHAP:
            ulResult = USIMM_MakeCHAPCmdData(&pstComputeIP->uComputeIPData.stChapData,
                                            &stCmdData);
            break;

        case USIMM_COMPUTEIP_MNHA:
            ucP2 = pstComputeIP->uComputeIPData.stMNHAData.enBlockType;
            ulResult = USIMM_MakeMNHACmdData(&pstComputeIP->uComputeIPData.stMNHAData,
                                            &stCmdData);
            break;

        case USIMM_COMPUTEIP_MIP:
            ucP2 = pstComputeIP->uComputeIPData.stMIPData.enBlockType;
            ulResult = USIMM_MakeMIPCmdData(&pstComputeIP->uComputeIPData.stMIPData,
                                            &stCmdData);
            break;

        case USIMM_COMPUTEIP_MNAAA:
            ucP2 = VOS_NULL;
            ulResult = USIMM_MakeMNAAACmdData(&pstComputeIP->uComputeIPData.stMNAAAData,
                                            &stCmdData);
            break;

        case USIMM_COMPUTEIP_HRPD:
            ucP2 = VOS_NULL;
            ulResult = USIMM_MakeHRPDCmdData(&pstComputeIP->uComputeIPData.stHRPDData,
                                            &stCmdData);
            break;

        default:
            USIMM_ERROR_LOG("USIMM_CdmaSpecAuthComputeIP: enComputeIPType Error");
            ulResult = USIMM_SW_CMD_ERROR;
            break;
    }

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_CdmaSpecAuthComputeIP: Make CMD Error");

        return ulResult;
    }

    ulResult = USIMM_SendComputeIPApdu(ucChannelID, 
                                    pstComputeIP->enComputeIPType,
                                    ucP2,
                                    &stCmdData,
                                    &stRspData);

    if (USIMM_SW_OK == ulResult)
    {
        stComputeIPCnf.enComputeIPType  = pstComputeIP->enComputeIPType;
        stComputeIPCnf.ulDataLen        = stRspData.usRspLen;

        if (VOS_NULL != stRspData.usRspLen)
        {
            (VOS_VOID)VOS_MemCpy(stComputeIPCnf.aucRspData,
                                stRspData.aucRsp,
                                stRspData.usRspLen);
        }

        USIMM_CdmaSepcAuthCnf(pstMsgHeader,
                                ulResult,
                                USIMM_CDMASPEC_COMPUTEIP,
                                (USIMM_CDMASPECAUTH_DATA_UNION*)&stComputeIPCnf);
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_MakeRetrieveSKData
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2015年6月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_MakeRetrieveSKData(
    USIMM_BCMCS_RETRIEVESK_STRU         *pstRetrieveSK,
    USIMM_U8_DATA_STRU                  *pstCmdData)
{
    VOS_UINT32                  ulOffset;

    pstCmdData->aucData[0] = 0x01;

    pstCmdData->ucDataLen = 1;

    ulOffset = 1;

    if (USIMM_APDU_DATA_MAXLEN < (ulOffset
                                + (pstRetrieveSK->stBCMCSFlowID.ucLen+2)
                                + (pstRetrieveSK->stBAKID.ucLen+2)
                                + (pstRetrieveSK->stSKRand.ucLen+2)))
    {
        return USIMM_SW_CMD_ERROR;
    }

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstRetrieveSK->stBCMCSFlowID,
                        pstRetrieveSK->stBCMCSFlowID.ucLen+2);

    ulOffset += pstRetrieveSK->stBCMCSFlowID.ucLen+2;

    pstCmdData->ucDataLen += pstRetrieveSK->stBCMCSFlowID.ucLen+2;

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstRetrieveSK->stBAKID,
                        pstRetrieveSK->stBAKID.ucLen+2);

    pstCmdData->ucDataLen += pstRetrieveSK->stBAKID.ucLen+2;

    ulOffset += pstRetrieveSK->stBAKID.ucLen+2;

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstRetrieveSK->stSKRand,
                        pstRetrieveSK->stSKRand.ucLen+2);

    pstCmdData->ucDataLen += pstRetrieveSK->stSKRand.ucLen+2;

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_MakeUpdateBAKData
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2015年6月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_MakeUpdateBAKData(
    USIMM_BCMCS_UPDATABAK_STRU          *pstUpdateBAK,
    USIMM_U8_DATA_STRU                  *pstCmdData)
{
    VOS_UINT32                  ulOffset;

    pstCmdData->aucData[0] = 0x01;

    pstCmdData->ucDataLen = 1;

    ulOffset = 1;

    if (USIMM_APDU_DATA_MAXLEN < (ulOffset
                                + (pstUpdateBAK->stBCMCSFlowID.ucLen+2)
                                + (pstUpdateBAK->stBAKID.ucLen+2)
                                + (pstUpdateBAK->stBAKExprie.ucLen+2)
                                + (pstUpdateBAK->stTKRand.ucLen+2)
                                + (pstUpdateBAK->stEncryptedBAK.ucDataLen)))
    {
        return USIMM_SW_CMD_ERROR;
    }

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstUpdateBAK->stBCMCSFlowID,
                        pstUpdateBAK->stBCMCSFlowID.ucLen+2);

    ulOffset += pstUpdateBAK->stBCMCSFlowID.ucLen+2;

    pstCmdData->ucDataLen += pstUpdateBAK->stBCMCSFlowID.ucLen+2;

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstUpdateBAK->stBAKID,
                        pstUpdateBAK->stBAKID.ucLen+2);

    pstCmdData->ucDataLen += pstUpdateBAK->stBAKID.ucLen+2;

    ulOffset += pstUpdateBAK->stBAKID.ucLen+2;

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstUpdateBAK->stBAKExprie,
                        pstUpdateBAK->stBAKExprie.ucLen+2);

    ulOffset += pstUpdateBAK->stBAKExprie.ucLen+2;

    pstCmdData->ucDataLen += pstUpdateBAK->stBAKExprie.ucLen+2;

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstUpdateBAK->stTKRand,
                        pstUpdateBAK->stTKRand.ucLen+2);

    ulOffset += pstUpdateBAK->stTKRand.ucLen+2;

    pstCmdData->ucDataLen += pstUpdateBAK->stTKRand.ucLen+2;

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        pstUpdateBAK->stEncryptedBAK.aucData,
                        pstUpdateBAK->stEncryptedBAK.ucDataLen);

    pstCmdData->ucDataLen += pstUpdateBAK->stEncryptedBAK.ucDataLen;

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_MakeDeleteBAKData
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2015年6月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_MakeDeleteBAKData(
    USIMM_BCMCS_DELETEBAK_STRU          *pstDeleteBAK,
    USIMM_U8_DATA_STRU                  *pstCmdData)
{
    VOS_UINT32                  ulOffset;

    pstCmdData->aucData[0] = 0x01;

    pstCmdData->ucDataLen = 1;

    ulOffset = 1;

    if (USIMM_APDU_DATA_MAXLEN < (ulOffset
                                + (pstDeleteBAK->stBAKID.ucLen+2)
                                + (pstDeleteBAK->stBCMCSFlowID.ucLen+2)))
    {
        return USIMM_SW_CMD_ERROR;
    }

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstDeleteBAK->stBCMCSFlowID,
                        pstDeleteBAK->stBCMCSFlowID.ucLen+2);

    ulOffset += pstDeleteBAK->stBCMCSFlowID.ucLen+2;

    pstCmdData->ucDataLen += pstDeleteBAK->stBCMCSFlowID.ucLen+2;

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstDeleteBAK->stBAKID,
                        pstDeleteBAK->stBAKID.ucLen+2);

    pstCmdData->ucDataLen += pstDeleteBAK->stBAKID.ucLen+2;

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_MakeReSRTPData
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2015年6月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_MakeReSRTPData(
    USIMM_BCMCS_RETRIEVE_SRTPSK_STRU    *pstReSRTPSK,
    USIMM_U8_DATA_STRU                  *pstCmdData)
{
    VOS_UINT32                  ulOffset;

    pstCmdData->aucData[0] = 0x01;

    pstCmdData->ucDataLen = 1;

    ulOffset = 1;

    if (USIMM_APDU_DATA_MAXLEN < (ulOffset
                                + (pstReSRTPSK->stBCMCSFlowID.ucLen+2)
                                + (pstReSRTPSK->stBAKID.ucLen+2)
                                + (pstReSRTPSK->stSKRand.ucLen+2)
                                + (pstReSRTPSK->stPacketIndex.ucLen+2)))
    {
        return USIMM_SW_CMD_ERROR;
    }

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstReSRTPSK->stBCMCSFlowID,
                        pstReSRTPSK->stBCMCSFlowID.ucLen+2);

    ulOffset += pstReSRTPSK->stBCMCSFlowID.ucLen+2;

    pstCmdData->ucDataLen += pstReSRTPSK->stBCMCSFlowID.ucLen+2;

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstReSRTPSK->stBAKID,
                        pstReSRTPSK->stBAKID.ucLen+2);

    pstCmdData->ucDataLen += pstReSRTPSK->stBAKID.ucLen+2;

    ulOffset += pstReSRTPSK->stBAKID.ucLen+2;

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstReSRTPSK->stSKRand,
                        pstReSRTPSK->stSKRand.ucLen+2);

    ulOffset += pstReSRTPSK->stSKRand.ucLen+2;

    pstCmdData->ucDataLen += pstReSRTPSK->stSKRand.ucLen+2;

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstReSRTPSK->stPacketIndex,
                        pstReSRTPSK->stPacketIndex.ucLen+2);

    pstCmdData->ucDataLen += pstReSRTPSK->stPacketIndex.ucLen+2;

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_MakeGenAuthData
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2015年6月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_MakeGenAuthData(
    USIMM_BCMCS_GENAUTH_SIGN_STRU       *pstGenAuthSign,
    USIMM_U8_DATA_STRU                  *pstCmdData)
{
    VOS_UINT32                  ulOffset;

    pstCmdData->aucData[0] = 0x01;

    pstCmdData->ucDataLen = 1;

    ulOffset = 1;

    if (USIMM_APDU_DATA_MAXLEN < (ulOffset
                                + (pstGenAuthSign->stBCMCSFlowID.ucLen+2)
                                + (pstGenAuthSign->stBAKID.ucLen+2)
                                + (pstGenAuthSign->stTimestamp.ucLen+2)))
    {
        return USIMM_SW_CMD_ERROR;
    }

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstGenAuthSign->stBCMCSFlowID,
                        pstGenAuthSign->stBCMCSFlowID.ucLen+2);

    ulOffset += pstGenAuthSign->stBCMCSFlowID.ucLen+2;

    pstCmdData->ucDataLen += pstGenAuthSign->stBCMCSFlowID.ucLen+2;

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstGenAuthSign->stBAKID,
                        pstGenAuthSign->stBAKID.ucLen+2);

    pstCmdData->ucDataLen += pstGenAuthSign->stBAKID.ucLen+2;

    ulOffset += pstGenAuthSign->stBAKID.ucLen+2;

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstGenAuthSign->stTimestamp,
                        pstGenAuthSign->stTimestamp.ucLen+2);

    pstCmdData->ucDataLen += pstGenAuthSign->stTimestamp.ucLen+2;

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_MakeBCMCSAuthData
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2015年6月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_MakeBCMCSAuthData(
    USIMM_BCMCS_AUTHENTICATION_STRU     *pstAuthentication,
    USIMM_U8_DATA_STRU                  *pstCmdData)
{
    VOS_UINT32                  ulOffset;

    pstCmdData->aucData[0] = 0x01;

    pstCmdData->ucDataLen = 1;

    ulOffset = 1;

    if (USIMM_APDU_DATA_MAXLEN < (ulOffset
                                + (pstAuthentication->stRand.ucLen+2)
                                + (pstAuthentication->stChallenge.ucLen+2)))
    {
        return USIMM_SW_CMD_ERROR;
    }

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstAuthentication->stChallenge,
                        pstAuthentication->stChallenge.ucLen+2);

    ulOffset += pstAuthentication->stChallenge.ucLen+2;

    pstCmdData->ucDataLen += pstAuthentication->stChallenge.ucLen+2;

    (VOS_VOID)VOS_MemCpy(&pstCmdData->aucData[ulOffset],
                        (VOS_UINT8*)&pstAuthentication->stRand,
                        pstAuthentication->stRand.ucLen+2);

    pstCmdData->ucDataLen += pstAuthentication->stRand.ucLen+2;

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_CDMASpecAuthBSMCS
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2015年6月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_CdmaSpecAuthBCMCS(
    VOS_UINT8                           ucChannelID,
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader,
    USIMM_BCMCS_DATA_STRU               *pstBCMCS)
{
    VOS_UINT32                  ulResult;
    USIMM_U8_DATA_STRU          stCmdData;
    USIMM_APDU_RSP_STRU         stRspData;
    USIMM_BCMCS_CNF_STRU        stBCMCSCnf;

    switch(pstBCMCS->enBCMCSType)
    {
        case USIMM_BCMCS_RETRIEVESK:
            ulResult = USIMM_MakeRetrieveSKData(&pstBCMCS->uBCMCSData.stRetrieveSK,
                                                &stCmdData);
            break;

        case USIMM_BCMCS_UPDATABAK:
            ulResult = USIMM_MakeUpdateBAKData(&pstBCMCS->uBCMCSData.stUpdateBAK,
                                                &stCmdData);
            break;

        case USIMM_BCMCS_DELETEBAK:
            ulResult = USIMM_MakeDeleteBAKData(&pstBCMCS->uBCMCSData.stDeleteBAK,
                                                &stCmdData);
            break;

        case USIMM_BCMCS_RETRIEVE_SRTPSK:
            ulResult = USIMM_MakeReSRTPData(&pstBCMCS->uBCMCSData.stReSRTPSK,
                                                &stCmdData);
            break;

        case USIMM_BCMCS_GENAUTH_SIGN:
            ulResult = USIMM_MakeGenAuthData(&pstBCMCS->uBCMCSData.stGenAuthSign,
                                                &stCmdData);
            break;

        case USIMM_BCMCS_AUTHENTICATION:
            ulResult = USIMM_MakeBCMCSAuthData(&pstBCMCS->uBCMCSData.stAuthentication,
                                                &stCmdData);
            break;

        default:
            ulResult = USIMM_SW_CMD_ERROR;
            break;
    }

    if (USIMM_SW_OK != ulResult)
    {
        return ulResult;
    }

    ulResult = USIMM_SendBCMCSApdu(ucChannelID, pstBCMCS->enBCMCSType, &stCmdData, &stRspData);

    if (USIMM_SW_OK == ulResult)
    {
        stBCMCSCnf.enBCMCSType = pstBCMCS->enBCMCSType;

        if (VOS_NULL != stRspData.usRspLen)
        {
            stBCMCSCnf.ucBCMCSRspTag = stRspData.aucRsp[0];

            stBCMCSCnf.ucBCMCSRspLen = stRspData.aucRsp[1];

            (VOS_VOID)VOS_MemCpy(stBCMCSCnf.aucBCMCSRsp,
                                &stRspData.aucRsp[2],
                                stRspData.aucRsp[1]);
        }
        else
        {
            stBCMCSCnf.ucBCMCSRspTag = VOS_NULL;

            stBCMCSCnf.ucBCMCSRspLen = VOS_NULL;
        }

        USIMM_CdmaSepcAuthCnf(pstMsgHeader, 
                            USIMM_SW_OK, 
                            USIMM_CDMASPEC_BCMCS, 
                            (USIMM_CDMASPECAUTH_DATA_UNION*)&stBCMCSCnf);
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_CdmaSpecAuthApp
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :VOS_OK/VOS_ERR
修订记录  :
1. 日    期   : 2015年6月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/

VOS_UINT32 USIMM_CdmaSpecAuthApp(
    VOS_UINT8                           ucChannelID,
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader,
    USIMM_CDMAAPP_AUTH_STRU             *pstAppAuth)
{
    VOS_UINT32                  ulResult;
    VOS_UINT32                  ulOffset;
    VOS_UINT32                  ulTotalLen;
    USIMM_U8_DATA_STRU          stCmdData;
    USIMM_APDU_RSP_STRU         stRspData;
    USIMM_CDMAAPP_AUTH_CNF_STRU stAppAuthCnf;

    ulTotalLen = (pstAppAuth->stRealm.ucDataLen
                + pstAppAuth->stServiceNonce.ucDataLen
                + pstAppAuth->stClientNonce.ucDataLen
                + 8);

    if (USIMM_APDU_DATA_MAXLEN < ulTotalLen)
    {
        USIMM_WARNING_LOG("USIMM_CdmaSpecAuthApp: Msg Data Len Error");

        return USIMM_SW_CMD_ERROR;
    }

    stCmdData.ucDataLen = 1;

    stCmdData.aucData[0]= (VOS_UINT8)pstAppAuth->enAuthMech;

    stCmdData.ucDataLen++;

    stCmdData.aucData[1]= (VOS_UINT8)pstAppAuth->ulAppID;

    stCmdData.aucData[2]= 0x00;

    stCmdData.aucData[3]= pstAppAuth->stRealm.ucDataLen;

    (VOS_VOID)VOS_MemCpy(&stCmdData.aucData[4],
                            pstAppAuth->stRealm.aucData,
                            pstAppAuth->stRealm.ucDataLen);

    stCmdData.ucDataLen += pstAppAuth->stRealm.ucDataLen + 2;

    stCmdData.aucData[stCmdData.ucDataLen] = 0x00;

    stCmdData.ucDataLen++;

    stCmdData.aucData[stCmdData.ucDataLen] = pstAppAuth->stServiceNonce.ucDataLen;

    stCmdData.ucDataLen++;

    (VOS_VOID)VOS_MemCpy(&stCmdData.aucData[stCmdData.ucDataLen],
                            pstAppAuth->stServiceNonce.aucData,
                            pstAppAuth->stServiceNonce.ucDataLen);

    stCmdData.ucDataLen += pstAppAuth->stServiceNonce.ucDataLen;

    stCmdData.aucData[stCmdData.ucDataLen] = 0x00;

    stCmdData.ucDataLen++;

    stCmdData.aucData[stCmdData.ucDataLen] = pstAppAuth->stClientNonce.ucDataLen;

    stCmdData.ucDataLen++;

    (VOS_VOID)VOS_MemCpy(&stCmdData.aucData[stCmdData.ucDataLen],
                            pstAppAuth->stClientNonce.aucData,
                            pstAppAuth->stClientNonce.ucDataLen);

    stCmdData.ucDataLen += pstAppAuth->stClientNonce.ucDataLen;

    ulResult = USIMM_SendAppAuthApdu(ucChannelID, &stCmdData, &stRspData);

    if (USIMM_SW_OK == ulResult)
    {
        stAppAuthCnf.enAppAuthType = pstAppAuth->enAuthMech;

        if (stRspData.usRspLen != VOS_NULL)
        {
            stAppAuthCnf.stResponse.ucDataLen = stRspData.aucRsp[0];

            (VOS_VOID)VOS_MemCpy(stAppAuthCnf.stResponse.aucData,
                                &stRspData.aucRsp[1],
                                stAppAuthCnf.stResponse.ucDataLen);

            ulOffset = stAppAuthCnf.stResponse.ucDataLen + 1;

            stAppAuthCnf.stSessionKey1.ucDataLen = stRspData.aucRsp[ulOffset+1];

            ulOffset += 2;

            (VOS_VOID)VOS_MemCpy(stAppAuthCnf.stSessionKey1.aucData,
                                &stRspData.aucRsp[ulOffset],
                                stAppAuthCnf.stSessionKey1.ucDataLen);

            ulOffset += stAppAuthCnf.stSessionKey1.ucDataLen;

            stAppAuthCnf.stSessionKey2.ucDataLen = stRspData.aucRsp[ulOffset+1];

            ulOffset += 2;

            (VOS_VOID)VOS_MemCpy(stAppAuthCnf.stSessionKey2.aucData,
                                &stRspData.aucRsp[ulOffset],
                                stAppAuthCnf.stSessionKey2.ucDataLen);
        }
        else
        {
            stAppAuthCnf.stResponse.ucDataLen       = 0;
            stAppAuthCnf.stSessionKey1.ucDataLen    = 0;
            stAppAuthCnf.stSessionKey2.ucDataLen    = 0;
        }

        USIMM_CdmaSepcAuthCnf(pstMsgHeader,
                            USIMM_SW_OK,
                            USIMM_CDMASPEC_APPAUTH,
                            (USIMM_CDMASPECAUTH_DATA_UNION*)&stAppAuthCnf);
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_CheckTimeOutError
功能描述  :
输入参数  :
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2015年6月12日
   作    者   : zhuli
   修改内容   : Creat
*****************************************************************************/

VOS_VOID USIMM_CheckTimeOutError(VOS_VOID)
{
    USIMMDL_ERROR_ENUM_UINT32           enDLError;

    enDLError = USIMM_GetT0DLErrorInfo();

    if ((USIMMDL_SCISENDLC_ERROR < enDLError)&&(enDLError < USIMMDL_STATE_ERROR))
    {
        USIMM_SetTimeOutFlag(VOS_TRUE);
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_CheckSupportAP
功能描述  :判断当前是否支持AP
输入参数  :无
输出参数  :无
返 回 值  :VOS_TRUE/VOS_FALSE
调用函数  : GetProductType
被调函数  : 外部接口
History     :
1.日    期  : 2014年10月09日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_BOOL USIMM_CheckSupportAP(VOS_VOID)
{
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU stAPPConfig;

    if(NV_OK != NV_Read(en_NV_Item_System_APP_Config, &stAPPConfig, sizeof(VOS_UINT16)))
    {
        USIMM_ERROR_LOG("SI_STK_CheckSupportAP: Read en_NV_Item_System_APP_Config Failed");

        return VOS_FALSE;
    }

    if(SYSTEM_APP_ANDROID == stAPPConfig.usSysAppConfigType)
    {
        USIMM_NORMAL_LOG("SI_STK_CheckSupportAP: System App is Android");

        return VOS_TRUE;
    }

    USIMM_NORMAL_LOG("SI_STK_CheckSupportAP: System App is other");

    return VOS_FALSE;
}


#else

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
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat


*****************************************************************************/
VOS_UINT32 USIMM_UpdateLFFile(VOS_UINT8 ucRecordNum, VOS_UINT8 *pucData, VOS_UINT8 ucLen)
{
    VOS_UINT32 ulResult;
    VOS_UINT8  ucP2 = 0x04;    /*统一按照绝对方式更新*/

    ulResult = USIMM_UpdateRecord_APDU(ucRecordNum, ucP2, ucLen, pucData);

    if(VOS_OK != ulResult)/*判断发送结果*/
    {
        USIMM_ERROR_LOG("USIMM_UpdateLFFile:USIMM_UpdateRecord_APDU error");

        return USIMM_SW_SENDCMD_ERROR;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    if(USIMM_SW_OK != ulResult)/*判断更新结果*/
    {
        USIMM_WARNING_LOG("USIMM_UpdateLFFile:USIMM_CheckSW error");
    }

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
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat


*****************************************************************************/
VOS_UINT32 USIMM_UpdateTFFile(VOS_UINT16 usLen, VOS_UINT8 *pucData)
{
    VOS_UINT32 ulResult = VOS_ERR;
    VOS_UINT16 usUpdateLen;
    VOS_UINT8  ucP3 = 0;

    for(usUpdateLen=0; usUpdateLen<usLen;usUpdateLen+=ucP3)
    {
        if(usLen > (0xFF+usUpdateLen))   /*判断当前的剩余数据长度*/
        {
            ucP3 = 0xFF;                            /*剩余数据大于255*/
        }
        else
        {
            ucP3 = (VOS_UINT8)(usLen-usUpdateLen);   /*剩余数据可以一次更新完毕*/
        }

        ulResult = USIMM_UpdateBinary_APDU(usUpdateLen, ucP3, pucData+usUpdateLen);

        if(VOS_OK != ulResult)         /*判断发送结果*/
        {
            USIMM_ERROR_LOG("USIMM_UpdateTFFile:USIMM_UpdateBinary_APDU error");

            return USIMM_SW_SENDCMD_ERROR;
        }

        ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

        if(USIMM_SW_OK!= ulResult)  /*判断检查结果*/
        {
            USIMM_WARNING_LOG("USIMM_UpdateTFFile:USIMM_CheckSW error");
        }
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_UpdateCLFFile
功能描述  :更新循环记录文件　
输入参数  :pucData:数据内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_UpdateRecord_APDU
           USIMM_CheckSW
修订记录  :
1. 日    期   : 2007年7月11日
    作    者   : z00100318
    修改内容   : Creat


*****************************************************************************/
VOS_UINT32 USIMM_UpdateCLFFile(VOS_UINT8 *pucData, VOS_UINT8 ucDataLen)
{
    VOS_UINT32 ulResult;

    ulResult = USIMM_UpdateRecord_APDU(0x00, 0x03, ucDataLen,  pucData);

    if(VOS_OK != ulResult)/*判断发送结果*/
    {
        USIMM_ERROR_LOG("USIMM_UpdateCLFFile:USIMM_UpdateRecord_APDU error");

        return USIMM_SW_SENDCMD_ERROR;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    if(USIMM_SW_OK != ulResult)/*判断检查结果*/
    {
        USIMM_WARNING_LOG("USIMM_UpdateCLFFile:USIMM_CheckSW error");
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
1. 日    期   : 2007年7月11日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_ReadLFFile(USIMM_EFFCP_ST *pstCurEFFcp, VOS_UINT8 ucRecordNum, VOS_UINT8 *pucContent)
{
    VOS_UINT32                          i    = 1;
    VOS_UINT32                          ulTotalNum;
    VOS_UINT32                          ulResult;

    if(USIMM_READ_ALLRECORD == ucRecordNum)
    {
        ulTotalNum = pstCurEFFcp->ucRecordNum;
    }
    else
    {
        i = ucRecordNum;

        ulTotalNum = i;
    }

    for(; i<=ulTotalNum; i++)
    {
        if(VOS_OK != USIMM_ReadRecord_APDU((VOS_UINT8)i, 0x04, pstCurEFFcp->ucRecordLen))/*判断发送结果*/
        {
            USIMM_ERROR_LOG("USIMM_ReadLFFile: USIMM_ReadRecord_APDU Error");

            if (VOS_OK != USIMM_ReadRecord_APDU((VOS_UINT8)i, 0x04, pstCurEFFcp->ucRecordLen))
            {
                USIMM_ERROR_LOG("USIMM_ReadLFFile:Resend USIMM_ReadRecord_APDU Error");

                return USIMM_SW_SENDCMD_ERROR;
            }
        }

        ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

        if(USIMM_SW_OK != ulResult)/*判断检查结果*/
        {
            USIMM_WARNING_LOG("USIMM_ReadLFFile: USIMM_CheckSW Error");

            return ulResult;
        }

        /*lint -e534*/
        VOS_MemCpy(pucContent, gstUSIMMAPDU.aucRecvBuf, pstCurEFFcp->ucRecordLen);
        /*lint +e534*/

        pucContent += pstCurEFFcp->ucRecordLen;
    }

    return USIMM_SW_OK;
}

/*****************************************************************************
函 数 名  :USIMM_ReadTFFile
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
VOS_UINT32 USIMM_ReadTFFile(VOS_UINT16 usLen, VOS_UINT8 *pucContent)
{
    VOS_UINT32 ulResult;
    VOS_UINT16 usReadedLen;
    VOS_UINT8  ucP3 = 0;

    for(usReadedLen=0; usReadedLen<usLen; usReadedLen+=ucP3)
    {
        if((usLen-usReadedLen) > 0xFF)      /*最大更新长度*/
        {
            ucP3 = 0xFF;
        }
        else
        {
            ucP3 = (VOS_UINT8)(usLen-usReadedLen);  /*剩余更新长度*/
        }

        ulResult = USIMM_ReadBinary_APDU(usReadedLen, ucP3);

        if(VOS_OK != ulResult)/*判断更新发送结果*/
        {
            USIMM_ERROR_LOG("USIMM_ReadTFFile: USIMM_ReadBinary_APDU Error");

            if (VOS_OK != USIMM_ReadBinary_APDU(usReadedLen, ucP3))
            {
                USIMM_ERROR_LOG("USIMM_ReadTFFile:Resend USIMM_ReadBinary_APDU Error");

                return USIMM_SW_SENDCMD_ERROR;
            }
        }

        ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

        if(USIMM_SW_OK != ulResult)/*判断检查结果*/
        {
            USIMM_WARNING_LOG("USIMM_ReadTFFile: USIMM_CheckSW Error");

            return ulResult;
        }

        /*lint -e534*/
        VOS_MemCpy(pucContent+usReadedLen, gstUSIMMAPDU.aucRecvBuf, ucP3);
        /*lint +e534*/
    }

    return USIMM_SW_OK;
}


/*****************************************************************************
函 数 名  :USIMM_GetTFFile
功能描述  :读取固定长度的二进制文件内容
输入参数  :
输出参数  :无
返 回 值  :
调用函数  :
修订记录  :
1. 日    期   : 2009年11月12日
   作    者   : H59254
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32  USIMM_GetTFFile(USIMM_APP_TYPE_ENUM_UINT32 enAppType, VOS_UINT16 usFileId, VOS_UINT16 usReadLen,VOS_UINT8 *pucData)
{
    VOS_UINT32  ulResult;
    VOS_UINT16  usDataLen;

    ulResult = USIMM_SelectFile(enAppType, USIMM_NEED_FCP, 1, &usFileId);

    if(VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    if(gstUSIMMCurFileInfo.stEFInfo.enFileType != USIMM_EFSTRUCTURE_TRANSPARENT)
    {
        return VOS_ERR;
    }

    if(USIMM_READ_ALL_FILE_CONTENT == usReadLen)
    {
        usDataLen = gstUSIMMCurFileInfo.stEFInfo.usFileLen;
    }
    else
    {
        usDataLen = usReadLen;
    }

    ulResult = USIMM_ReadTFFile(usDataLen, pucData);

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_WriteTFFile
功能描述  :读取固定长度的二进制文件内容
输入参数  :
输出参数  :无
返 回 值  :
调用函数  :
修订记录  :
1. 日    期   : 2009年11月12日
   作    者   : H59254
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32  USIMM_WriteTFFile(USIMM_APP_TYPE_ENUM_UINT32 enFileApp, VOS_UINT16 usFileId, VOS_UINT16 usDataLen,VOS_UINT8 *pucData)
{
    VOS_UINT32  ulResult;

    ulResult = USIMM_SelectFile(enFileApp, USIMM_NEED_FCP, 1, &usFileId);

    if(VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    if(gstUSIMMCurFileInfo.stEFInfo.enFileType != USIMM_EFSTRUCTURE_TRANSPARENT)
    {
        return VOS_ERR;
    }

    return USIMM_UpdateTFFile(usDataLen, pucData);
}

/*****************************************************************************
函 数 名  :USIMM_STATUSCmd
功能描述  :发送STATUS命令并解析返回内容
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_ReadBinary_APDU
           USIMM_CheckSW
修订记录  :
1. 日    期   : 2007年7月11日
    作    者   : z00100318
    修改内容   : Creat
2. 日    期  : 2011年8月30日
   作    者  : j00168360
   修改内容  : [DTS2011083000162]，USIM模块正向清理保护性复位及卡路径选择
*****************************************************************************/
VOS_UINT32 USIMM_STATUSProc(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usCurDfID   = gstUSIMMCurFileInfo.usCurDFID;
    VOS_UINT16                          usCurFcpLen = gstUSIMMCurFileInfo.usCurDFFcpLen;

    ulResult = USIMM_Status_APDU(USIMM_STATUS_NO_INDICATION, USIMM_STATUS_FCP_RETURNED, (VOS_UINT8)gstUSIMMCurFileInfo.usCurDFFcpLen);

    if(VOS_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_StatusHandle: USIMM_Status_APDU is Error");

        return USIMM_SW_SENDCMD_ERROR;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    if(USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_StatusHandle: Command SW is Error");

        /* 只要status apdu下去卡有响应就认为卡在位 */
        return USIMM_SW_OK;
    }

    USIMM_INFO_LOG("USIMM_StatusHandle: The Status Command is OK");

    ulResult = USIMM_DecodeDFFcp(gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType, &gstUSIMMAPDU, &gstUSIMMCurFileInfo);

    if(ulResult != VOS_OK)
    {
        /* 出错需要还原之前的值，避免下次发送错误 */
        gstUSIMMCurFileInfo.usCurDFFcpLen   = usCurFcpLen;

        gstUSIMMCurFileInfo.usCurDFID       = usCurDfID;

        /* 只要status apdu下去卡有响应就认为卡在位 */
        return USIMM_SW_OK;
    }

    if (USIMM_CARD_SIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)  /*当前为SIM*/
    {
        USIMM_SaveDFPinInfo();

        gstUSIMMCurFileInfo.usCurDFID = gstUSIMMCurFileInfo.stDFInfo.usDFID;
    }
    else
    {
        if(VOS_OK == VOS_MemCmp(gstUSIMMADFInfo.aucAID, gstUSIMMCurFileInfo.stDFInfo.aucName, gstUSIMMADFInfo.ulAIDLen))
        {
            gstUSIMMCurFileInfo.usCurDFID = ADF;
        }
        else
        {
            gstUSIMMCurFileInfo.usCurDFID = gstUSIMMCurFileInfo.stDFInfo.usDFID;
        }
    }

    if((USIMM_NULL_ID != usCurDfID)&&(usCurDfID != gstUSIMMCurFileInfo.usCurDFID))
    {
        USIMM_ERROR_LOG("USIMM_StatusHandle:The Status Command is not Same,The Card Should be Changed");

        return USIMM_SW_DFPATH_ERROR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_GetPINRemainTime
功能描述  :获取当前的PIN剩余次数
输入参数  :ucPINNo:当前PIN的索引号
输出参数  :全局变量中的PIN剩余次数
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_VerifyPIN_APDU
修订记录  :
1. 日    期   : 2007年7月11日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_GetPINRemainTime(VOS_UINT8 ucPINNo)
{
    VOS_UINT32  ulResult;
    VOS_UINT8   ucRemain;

    ulResult = USIMM_PINVerify_APDU(CMD_INS_VERIFY,ucPINNo, VOS_NULL_PTR);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_GetPINRemainTime: USIMM_PINVerify_APDU Error");

        return VOS_ERR;
    }

    if(0x63 == gstUSIMMAPDU.ucSW1)
    {
        ucRemain = gstUSIMMAPDU.ucSW2&0x0F;
    }
    else
    {
        ucRemain = 0;
    }

    if(gstUSIMMADFInfo.ucPIN1RefNum == ucPINNo)
    {
        gstUSIMMADFInfo.stPINInfo.ucPin1RemainTime = ucRemain;
    }
    else if(gstUSIMMADFInfo.ucPIN2RefNum == ucPINNo)
    {
        gstUSIMMADFInfo.stPINInfo.ucPin2RemainTime = ucRemain;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_GetPUKRemainTime
功能描述  :获取当前的PUK的剩余次数
输入参数  :PUK对应的PIN的索引号
输出参数  :全局变量中PUK剩余次数
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_UnblockPIN_APDU
修订记录  :
1. 日    期   : 2007年7月11日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_GetPUKRemainTime(VOS_UINT8 ucPINNo)
{
    VOS_UINT32 ulResult;
    VOS_UINT8  ucRemain;

    ulResult = USIMM_UnblockPIN_APDU(ucPINNo, VOS_NULL_PTR,VOS_NULL_PTR);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_GetPUKRemainTime: USIMM_UnblockPIN_APDU Error");

        return VOS_ERR;
    }

    if(0x63 == gstUSIMMAPDU.ucSW1)
    {
        ucRemain = gstUSIMMAPDU.ucSW2&0x0F;
    }
    else
    {
        ucRemain = 0;
    }

    if(gstUSIMMADFInfo.ucPIN1RefNum == ucPINNo)
    {
        gstUSIMMADFInfo.stPINInfo.ucPuk1RemainTime = ucRemain;
    }
    else if(gstUSIMMADFInfo.ucPIN2RefNum == ucPINNo)
    {
        gstUSIMMADFInfo.stPINInfo.ucPuk2RemainTime = ucRemain;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_AdjudgeCardState
功能描述  :根据当前的PIN状态转换当前的卡状态并上报
输入参数  :无
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月11日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_AdjudgeCardState(VOS_VOID)
{
    USIMM_CARD_SERVIC_ENUM_UINT32 enProCardService;

    enProCardService = gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService;    /*保存当前的卡状态*/

    /*判断密码状态*/
    if(0 == gstUSIMMADFInfo.stPINInfo.ucPin1RemainTime)    /*PIN1剩余0次*/
    {
        USIMM_NORMAL_LOG("USIMM_AdjudgeCardState: The PIN of the Card is Block");

        gstUSIMMADFInfo.enPin1Verified  = USIMM_PUK_NEED;
    }

    if(0 == gstUSIMMADFInfo.stPINInfo.ucPin2RemainTime)    /*PIN2剩余0次*/
    {
        USIMM_NORMAL_LOG("USIMM_AdjudgeCardState: The PIN2 of the Card is Block");

        gstUSIMMADFInfo.enPin2Verified  = USIMM_PUK_NEED;
    }

    if(0 == gstUSIMMADFInfo.stPINInfo.ucPuk1RemainTime)    /*PUK1剩余0次*/
    {
        USIMM_WARNING_LOG("USIMM_AdjudgeCardState: The Card PUK is Block, Card Could Not Used");

        gstUSIMMADFInfo.enPin1Verified  = USIMM_PUK_BLOCK;
    }

    /*根据密码状态判断卡状态*/
    if(USIMM_PUK_BLOCK == gstUSIMMADFInfo.enPin1Verified)/*判断PUK BLOCK状态*/
    {
        USIMM_NORMAL_LOG("USIMM_AdjudgeCardState: PUK is Block");

        gstUSIMMBaseInfo.enCurPINType   = USIMM_PUK;

        gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService   = USIMM_CARD_SERVIC_UNAVAILABLE;
    }
    else if(USIMM_PUK_NEED == gstUSIMMADFInfo.enPin1Verified)/*判断PUK状态*/
    {
        USIMM_NORMAL_LOG("USIMM_AdjudgeCardState: The Card Need the PUK Password");

        if (USIMM_POOL_AVAILABLE == gstUSIMMPOOL.enPoolStatus)
        {
            gstUSIMMPOOL.enPoolStatus = USIMM_POOL_NEED_PASSWORD;
        }

        gstUSIMMBaseInfo.enCurPINType = USIMM_PUK;

        gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService = USIMM_CARD_SERVIC_SIM_PUK;
    }
    else if(USIMM_PIN_NEED == gstUSIMMADFInfo.enPin1Verified) /*再判断当前PIN1状态*/
    {
        USIMM_NORMAL_LOG("USIMM_AdjudgeCardState: The Card Need the PIN Password");

        if (USIMM_POOL_AVAILABLE == gstUSIMMPOOL.enPoolStatus)
        {
            gstUSIMMPOOL.enPoolStatus = USIMM_POOL_NEED_PASSWORD;
        }

        gstUSIMMBaseInfo.enCurPINType = USIMM_PIN;

        gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService = USIMM_CARD_SERVIC_SIM_PIN;

    }
    else if(USIMM_PUK_NEED == gstUSIMMADFInfo.enPin2Verified)   /*再判断PUK2状态*/
    {
        USIMM_NORMAL_LOG("USIMM_AdjudgeCardState: The Card Need the PUK2 Password");

        gstUSIMMBaseInfo.enCurPINType = USIMM_PUK2;

        gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService = USIMM_CARD_SERVIC_AVAILABLE;
    }
    else  /*再判断PIN2状态*/                                                                                  /*最后默认需要PIN2*/
    {
        USIMM_NORMAL_LOG("USIMM_AdjudgeCardState: The Card Need the PIN2 Password");

        gstUSIMMBaseInfo.enCurPINType = USIMM_PIN2;

        gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService = USIMM_CARD_SERVIC_AVAILABLE;
    }

    if(enProCardService != gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService )
    {
        USIMM_NORMAL_LOG("USIMM_AdjudgeCardState: The Card State is Changed, Need Report the Card State");

        gastUSIMMCardAppInfo[USIMM_UICC_USIM].enStateChange = USIMM_CARD_STATE_CHANGED;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_ReCountPINRemainTime
功能描述  :重新初始化当前的PIN剩余次数
输入参数  :enPINType:PIN类型
           ulResult :命令操作结果
输出参数  :无
返 回 值  :无
调用函数  :
修订记录  :
1. 日    期   : 2007年8月11日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_ReCountPINRemainTime(VOS_UINT32 ulResult,
                                      VOS_UINT32  ulCmdType,
                                      USIMM_PIN_TYPE_ENUM_UINT32 enPINType)
{
    if((USIMM_SW_SECURITY_ERROR == ulResult)||(USIMM_SW_CMD_REMAINTIME == ulResult)
       ||(USIMM_SW_PIN_BLOCK == ulResult))
    {
        if(USIMM_PINCMD_UNBLOCK == ulCmdType)
        {
            USIMM_WARNING_LOG("USIMM_ReCountPINRemainTime: The PUK is Wrong, Verify is failed");

            if(USIMM_PIN == enPINType)
            {
                return USIMM_INCORRECT_PASSWORD;
            }

            if(USIMM_PIN2 == enPINType)
            {
                return USIMM_INCORRECT_PASSWORD;
            }
        }
        else
        {
            USIMM_WARNING_LOG("USIMM_ReCountPINRemainTime: The PIN is Wrong, Verify is failed");

            if(USIMM_PIN == enPINType)
            {
                return ((gstUSIMMADFInfo.stPINInfo.ucPin1RemainTime == 0)?USIMM_SIM_PUK_REQUIRED:USIMM_INCORRECT_PASSWORD);/* [false alarm]: 屏蔽Fortify 错误 */
            }

            if(USIMM_PIN2 == enPINType)
            {
                return ((gstUSIMMADFInfo.stPINInfo.ucPin2RemainTime == 0)?USIMM_SIM_PUK2_REQUIRED:USIMM_INCORRECT_PASSWORD);/* [false alarm]: 屏蔽Fortify 错误 */
            }
        }
    }

    USIMM_WARNING_LOG("USIMM_ReCountPINRemainTime: The PIN or PUK Status is Wrong, Reamin Time should not Changed");

    return USIMM_SIM_FAILURE;
}

/*****************************************************************************
函 数 名  :USIMM_ChangePIN
功能描述  :更改PIN操作，并重新初始化当前的PIN剩余次数
输入参数  :enPINType:PIN类型
           pucOldPIN:原PIN
           pucNewPIN:新PIN
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_ChangePIN_APDU
          USIMM_CheckSW
          USIMM_GetPINRemainTime
          USIMM_AdjudgeCardState
修订记录  :
1. 日    期   : 2007年7月11日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_ChangePIN(USIMM_PIN_TYPE_ENUM_UINT32 enPINType, VOS_UINT8 *pucOldPIN, VOS_UINT8 *pucNewPIN)
{
    VOS_UINT32  ulResult;
    VOS_UINT8   ucPINType;

    if(USIMM_PIN == enPINType)
    {
        ucPINType = gstUSIMMADFInfo.ucPIN1RefNum;
    }
    else /*暂时不需要支持其它PIN*/
    {
        ucPINType = gstUSIMMADFInfo.ucPIN2RefNum;
    }

    ulResult = USIMM_ChangePIN_APDU(ucPINType, pucOldPIN, pucNewPIN);

    if(VOS_OK != ulResult)/*检查结果*/
    {
        USIMM_ERROR_LOG("USIMM_ChangePIN: USIMM_ChangePIN_APDU Error");

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        /*lint -e534*/
        USIMM_GetPINRemainTime(ucPINType);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        USIMM_STATUSProc();
        /*lint +e534*/
    }


    if(USIMM_SW_OK != ulResult)
    {
        ulResult = USIMM_ReCountPINRemainTime(ulResult, USIMM_PINCMD_CHANGE, enPINType);
    }

    return ulResult;        /*更改不成功则返回VOS_ERR*/
}

/*****************************************************************************
函 数 名  :USIMM_UnblockPIN
功能描述  :实现解锁PIN操作，并初始化PIN/PUK剩余次数　
输入参数  :enPINType:   解锁PIN类型
          pucPUK:       PUK内容
          pucNewPIN:  新PIN内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_UnblockPIN_APDU
          USIMM_CheckSW
          USIMM_GetPINRemainTime
          USIMM_GetPUKRemainTime
          USIMM_AdjudgeCardState
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_UnblockPIN(USIMM_PIN_TYPE_ENUM_UINT32 enPINType, VOS_UINT8 *pucPUK, VOS_UINT8 *pucNewPIN)
{
    VOS_UINT32 ulResult;
    VOS_UINT8  ucPINType;

    if((VOS_NULL_PTR == pucNewPIN)||(VOS_NULL_PTR == pucPUK)
        ||((USIMM_PIN != enPINType)&&(USIMM_PIN2 != enPINType)))/*参数检查*/
    {
        USIMM_ERROR_LOG("USIMM_UnblockPIN: Input Parameter Error");

        return VOS_ERR;
    }

    if(USIMM_PIN == enPINType)
    {
        if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
        {
            ucPINType = gstUSIMMADFInfo.ucPIN1RefNum;
        }
        else
        {
            ucPINType = 0x00;
        }
    }
    else
    {
        ucPINType = gstUSIMMADFInfo.ucPIN2RefNum;
    }

    ulResult = USIMM_UnblockPIN_APDU(ucPINType, pucPUK, pucNewPIN);

    if(VOS_OK != ulResult)/*检查结果*/
    {
        USIMM_ERROR_LOG("USIMM_UnblockPIN: USIMM_UnblockPIN_APDU Error");

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        /*lint -e534*/
        USIMM_GetPINRemainTime(ucPINType);
        /*lint +e534*/

        if (VOS_OK != USIMM_GetPUKRemainTime(ucPINType))
        {
            USIMM_INFO_LOG("USIMM_UnblockPIN: Get PUK Remain Time fail");
        }
    }
    else
    {
        /*lint -e534*/
        USIMM_STATUSProc();
        /*lint +e534*/
    }

    /*根据结果更改当前的PIN次数*/
    if(USIMM_SW_OK == ulResult)
    {
        if(USIMM_PIN == enPINType)
        {
            gstUSIMMADFInfo.enPin1Verified = USIMM_NONEED;

            gstUSIMMADFInfo.stPINInfo.enPin1Enable = USIMM_PIN_ENABLED;
        }
        else
        {
            gstUSIMMADFInfo.enPin2Verified = USIMM_PIN_NEED;
        }
    }
    else        /*判断剩余次数更改PIN状态*/
    {
        ulResult = USIMM_ReCountPINRemainTime(ulResult, USIMM_PINCMD_UNBLOCK, enPINType);
    }

    return ulResult;        /*更改不成功则返回VOS_ERR*/
}

/*****************************************************************************
函 数 名  :USIMM_PINVerify
功能描述  :实现当前PIN码的验证、激活、去激活功能
输入参数  :enPINType:当前操作的PIN类型
           enPINCmd:当前操作类型
           pucPIN:     PIN码内容
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DisablePIN_APDU
          USIMM_EnablePIN_APDU
          USIMM_VerifyPIN_APDU
          USIMM_GetPINRemainTime
          USIMM_AdjudgeCardState
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_PINVerify(USIMM_PIN_TYPE_ENUM_UINT32 enPINType,VOS_UINT8 ucPINCmd,VOS_UINT8 *pucPIN)
{
    VOS_UINT32 ulResult;
    VOS_UINT8  ucPINType;

    if(USIMM_PIN == enPINType)
    {
        ucPINType = gstUSIMMADFInfo.ucPIN1RefNum;
    }
    else            /*暂时不需要支持其它类型PIN*/
    {
        ucPINType = gstUSIMMADFInfo.ucPIN2RefNum;
    }

    ulResult = USIMM_PINVerify_APDU(ucPINCmd,ucPINType, pucPIN);

    if(VOS_OK != ulResult)/*检查结果*/
    {
        USIMM_ERROR_LOG("USIMM_PINVerify: USIMM_PINVerify_APDU Error");

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)  /*重新初始化当前的PIN剩余次数*/
    {
        /*lint -e534*/
        USIMM_GetPINRemainTime(ucPINType);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        USIMM_STATUSProc();
        /*lint +e534*/
    }

    if(USIMM_SW_OK == ulResult) /*当前操作成功*/
    {
        if(USIMM_PIN2 == enPINType)     /*对于PIN2不需要修改状态*/
        {
            return VOS_OK;
        }

        if(USIMM_PINCMD_ENABLE == ucPINCmd)    /*根据当前的操作类型修改PIN1状态*/
        {
            gstUSIMMADFInfo.stPINInfo.enPin1Enable  = USIMM_PIN_ENABLED;
        }
        else if(USIMM_PINCMD_DISABLE== ucPINCmd)
        {
            gstUSIMMADFInfo.stPINInfo.enPin1Enable  = USIMM_PIN_DISABLED;

            gstUSIMMADFInfo.enPin1Verified          = USIMM_NONEED;
        }
        else
        {
            gstUSIMMADFInfo.enPin1Verified          = USIMM_NONEED;
        }
    }
    else        /*判断剩余次数*/
    {
        ulResult = USIMM_ReCountPINRemainTime(ulResult, ucPINCmd, enPINType);
    }

    return ulResult;        /*更改不成功则返回VOS_ERR*/
}

/*****************************************************************************
函 数 名  :USIMM_InitUsimFDNBDNStatus
功能描述  :初始化USIM卡当前的FDN/BDN状态　
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2011年6月20日
    作    者   : j00168360
    修改内容   : Creat[DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_InitUsimFDNBDNStatus(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT8                   ucData;

    ulResult = USIMM_GetTFFile(USIMM_UMTS_APP, EFEST, sizeof(ucData), &ucData);

    if(VOS_OK == ulResult) /*该文件的存在不是必须的*/
    {
        /*判断内容初始化对应的全局变量*/
        if (PS_USIM_SERVICE_AVAILIABLE == USIMM_IsServiceAvailable(USIM_SVR_FDN))
        {
            gstUSIMMBaseInfo.enFDNStatus = (ucData&0x01)?USIMM_FDNSTATUS_ON:USIMM_FDNSTATUS_OFF;
        }
        else
        {
            gstUSIMMBaseInfo.enFDNStatus = USIMM_FDNSTATUS_OFF;
        }

        if (PS_USIM_SERVICE_AVAILIABLE == USIMM_IsServiceAvailable(USIM_SVR_BDN))
        {
            gstUSIMMBaseInfo.enBDNStatus = (ucData&0x02)?USIMM_BDNSTATUS_ON:USIMM_BDNSTATUS_OFF;
        }
        else
        {
            gstUSIMMBaseInfo.enBDNStatus = USIMM_BDNSTATUS_OFF;
        }
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_InitUsimFDNBDNStatus: USIMM_InitUsimFDNBDNStatus Error");
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_SimFDNBDNProcess
功能描述  :完成SIM卡的FDN功能开启后的初始化中相关文件有效的过程　
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat
2. 日    期   : 2011年6月20日
    作    者   : j00168360
    修改内容   : 修改函数名[DTS2011042900838]卡初始化流程优化

*****************************************************************************/
VOS_UINT32 USIMM_SimFDNBDNProcess(VOS_VOID)
{
    VOS_UINT32 ulResult;
    VOS_UINT16 ausPath[3] = {MF, DFGSM, EFIMSI};

    ulResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_SimFDNBDNProcess: USIMM_SelectFileWithPath(EFIMSI) Error");

        return VOS_ERR;
    }

    if(USIMM_EFSTATUS_DEACTIVE == gstUSIMMCurFileInfo.stEFInfo.enFileStatus)
    {
        /*lint -e534*/
        USIMM_ActivateFile_APDU();
        /*lint +e534*/
    }

    ausPath[2] = EFLOCI;

    ulResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

    if(VOS_OK != ulResult)/*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_SimFDNBDNProcess: USIMM_SelectFileWithPath(EFLOCI) Error");

        return VOS_ERR;
    }

    if(USIMM_EFSTATUS_DEACTIVE == gstUSIMMCurFileInfo.stEFInfo.enFileStatus)
    {
        /*lint -e534*/
        USIMM_ActivateFile_APDU();
        /*lint +e534*/
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_InitSimFDNBDNStatus
功能描述  :初始化SIM卡当前的FDN/BDN状态　
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_SelectEFByPath
          USIMM_ReadTFFile
修订记录  :
1. 日    期   : 2011年6月20日
    作    者   : j00168360
    修改内容   : Creat[DTS2011042900838]卡初始化流程优化
2. 日    期  : 2011年8月30日
   作    者  : j00168360
   修改内容  : [DTS2011083000162]，USIM模块正向清理保护性复位及卡路径选择
*****************************************************************************/
VOS_UINT32 USIMM_InitSimFDNBDNStatus(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT16                  ausPath[] = {MF,DFGSM,EFIMSI};
    USIMM_EFSTATUS_ENUM_UINT8   imsiState = USIMM_EFSTATUS_ACTIVE;
    USIMM_EFSTATUS_ENUM_UINT8   lociState = USIMM_EFSTATUS_ACTIVE;

    /* PHASE1的SIM卡不需要处理BDN FDN过程，只有 PHASE2 PHASE2+的卡才需要 */
    if(gstUSIMMBaseInfo.ulSimPhase < USIMM_SIM_PHASE_TWO)
    {
        USIMM_WARNING_LOG("USIMM_SimProfileDownload: SIM Not Support SAT");

        return VOS_OK;
    }

    ulResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

    if(VOS_OK != ulResult)/*判断结果和文件状态*/
    {
        USIMM_ERROR_LOG("USIMM_InitSimFDNBDNStatus: USIMM_SelectFileWithPath(EFIMSI) Error");

        return VOS_ERR;
    }

    imsiState = gstUSIMMCurFileInfo.stEFInfo.enFileStatus;

    ausPath[2] = EFLOCI;

    ulResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

    if(VOS_OK != ulResult)/*判断结果和文件状态*/
    {
        USIMM_ERROR_LOG("USIMM_InitSimFDNBDNStatus: USIMM_SelectFileWithPath(EFLOCI) Error");

        return VOS_ERR;
    }

    lociState = gstUSIMMCurFileInfo.stEFInfo.enFileStatus;

    /* IMSI和LOCI不同时无效时，单板执行不受约束操作 */
    if((USIMM_EFSTATUS_DEACTIVE != imsiState)||(USIMM_EFSTATUS_DEACTIVE != lociState))
    {
        USIMM_WARNING_LOG("USIMM_InitSimFDNBDNStatus: EFLOCI or EFIMSI File Statue Error");
    }

    /* BDN能力请求 */
    USIMM_BdnCapabilityRequest(&gstUSIMMBaseInfo.enBDNStatus);

    /* FDN能力请求 */
    USIMM_FdnCapabilityRequest(&gstUSIMMBaseInfo.enFDNStatus);

    return USIMM_SimFDNBDNProcess();
}

/*****************************************************************************
函 数 名  :USIMM_FdnCapabilityRequest
功能描述  :初始化SIM卡FDN能力请求　
输入参数  :无
输出参数  :USIMM_FDNSTATUS_ENUM_UINT32 *pulFdnStatus
返 回 值  :无
修订记录  :
1. 日    期   : 2013年5月7日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_FdnCapabilityRequest(USIMM_FDNSTATUS_ENUM_UINT32 *pulFdnStatus)
{
    VOS_UINT16                          ausPath[] = {MF, DFTELCOM, EFADN};
    VOS_UINT32                          ulResult;

    /* 若FDN状态在SST文件中未allocated and activated,FDN未激活 */
    if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(SIM_SVR_FDN))
    {
        *pulFdnStatus = USIMM_FDNSTATUS_OFF;

        return;
    }

    /* 若ADN状态在SST文件中未allocated and activated,FDN激活 */
    if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(SIM_SVR_ADN))
    {
        *pulFdnStatus = USIMM_FDNSTATUS_ON;

        return;
    }

    /* ADN文件不存在,FDN激活 */
    ulResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);
    if (VOS_OK != ulResult)
    {
        *pulFdnStatus = USIMM_FDNSTATUS_ON;
    }
    else
    {
        /* ADN文件无效,FDN激活 */
        if (USIMM_EFSTATUS_DEACTIVE == gstUSIMMCurFileInfo.stEFInfo.enFileStatus)
        {
            *pulFdnStatus = USIMM_FDNSTATUS_ON;
        }
        /* ADN文件有效,FDN未激活 */
        else
        {
            *pulFdnStatus = USIMM_FDNSTATUS_OFF;
        }
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_BdnCapabilityRequest
功能描述  :初始化SIM卡BDN能力请求　
输入参数  :无
输出参数  :USIMM_BDNSTATUS_ENUM_UINT32 *pulBdnStatus
返 回 值  :无
修订记录  :
1. 日    期   : 2013年5月7日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_BdnCapabilityRequest(USIMM_BDNSTATUS_ENUM_UINT32 *pulBdnStatus)
{
    VOS_UINT16                          ausPath[] = {MF, DFTELCOM, EFBDN};
    VOS_UINT32                          ulResult;

    /* 如果不支持Call Control功能，BDN未激活 */
    if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(SIM_SVR_CALL_CONTROL))
    {
        *pulBdnStatus = USIMM_BDNSTATUS_OFF;

        return;
    }

    /* BDN在SST中不存在或BDN状态在SST文件中未allocated and activated,BDN未激活 */
    if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(SIM_SVR_BDN))
    {
        *pulBdnStatus = USIMM_BDNSTATUS_OFF;

        return;
    }

    /* BDN文件不存在,BDN未激活 */
    ulResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);
    if (VOS_OK != ulResult)
    {
        *pulBdnStatus = USIMM_BDNSTATUS_OFF;
    }
    else
    {
        /* BDN文件有效,BDN激活 */
        if (USIMM_EFSTATUS_ACTIVE == gstUSIMMCurFileInfo.stEFInfo.enFileStatus)
        {
            *pulBdnStatus = USIMM_BDNSTATUS_ON;
        }
        /* BDN文件无效,BDN未激活 */
        else
        {
            *pulBdnStatus = USIMM_BDNSTATUS_OFF;
        }
    }

    return;
}



/*****************************************************************************
函 数 名  :USIMM_FDNEnable
功能描述  :实现FDN功能的开启　
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_SelectEFByPath
          USIMM_PoolFindFile
          USIMM_ReadTFFile
          USIMM_UpdateTFFile
          USIMM_DeactivateFile_APDU
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_FDNEnable(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          ausPath[]={MF,DFTELCOM,EFADN};
    VOS_UINT8                           ucData;


    if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        ulResult = USIMM_PoolReadOneFile(EFEST, sizeof(VOS_UINT8), &ucData, USIMM_UMTS_APP);

        if(VOS_ERR == ulResult)/*如果缓存中没有则需要从卡中读取*/
        {
            return VOS_ERR;
        }

        ucData = ucData|0x01;

        ulResult = USIMM_WriteTFFile(USIMM_UMTS_APP, EFEST, sizeof(ucData), &ucData);

        if(USIMM_SW_OK != ulResult)/*判断结果*/
        {
            USIMM_ERROR_LOG("USIMM_FDNEnable: USIMM_UpdateTFFile Error");

            return VOS_ERR;
        }

        /*lint -e534*/
        USIMM_PoolUpdateOneFile(EFEST, USIMM_UMTS_APP, sizeof(ucData), &ucData);
        /*lint +e534*/
    }
    else
    {
        ulResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

        if(VOS_OK != ulResult)/*判断结果*/
        {
            USIMM_ERROR_LOG("USIMM_FDNEnable: USIMM_SelectFileWithPath(EFADN) Error");

            return VOS_ERR;
        }

        ulResult = USIMM_DeactivateFile_APDU();

        if(VOS_OK != ulResult)/*判断结果*/
        {
            USIMM_ERROR_LOG("USIMM_FDNEnable: USIMM_DeactivateFile_APDU Error");

            return VOS_ERR;
        }

        ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

        if(USIMM_SW_OK != ulResult)/*判断结果*/
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}
/*****************************************************************************
函 数 名  :USIMM_FDNDisable
功能描述  :实现FDN功能的关闭
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_SelectEFByPath
          USIMM_PoolFindFile
          USIMM_ReadTFFile
          USIMM_ActivateFile_APDU
          USIMM_CheckSW
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_FDNDisable(VOS_VOID)
{
    VOS_UINT32  ulResult;
    VOS_UINT8   ucData;
    VOS_UINT16  ausPath[] = {MF, DFTELCOM,EFADN};

    if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)/*USIM卡*/
    {
        ulResult = USIMM_PoolReadOneFile(EFEST, sizeof(VOS_UINT8), &ucData, USIMM_UMTS_APP);

        if(VOS_ERR == ulResult)/*如果缓存中没有则需要从卡中读取*/
        {
            USIMM_ERROR_LOG("USIMM_FDNDisable: USIMM_PoolReadOneFile Failed");

            return VOS_ERR;
        }

        ucData = ucData&0xFE;

        ulResult = USIMM_WriteTFFile(USIMM_UMTS_APP, EFEST, sizeof(VOS_UINT8),&ucData);

        if(VOS_OK != ulResult)/*判断结果*/
        {
            USIMM_ERROR_LOG("USIMM_FDNDisable: USIMM_UpdateTFFile Failed");

            return VOS_ERR;
        }

        /*lint -e534*/
        USIMM_PoolUpdateOneFile(EFEST, USIMM_UMTS_APP, sizeof(ucData), &ucData);
        /*lint +e534*/
    }
    else
    {
        /* 激活ADN电话本*/
        ulResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

        if(VOS_OK != ulResult)/*判断结果*/
        {
            USIMM_ERROR_LOG("USIMM_FDNDisable: USIMM_SelectFileWithPath(EFADN) Failed");

            return VOS_ERR;
        }

        ulResult = USIMM_ActivateFile_APDU();

        if(VOS_OK != ulResult)/*判断结果*/
        {
            USIMM_ERROR_LOG("USIMM_FDNDisable: USIMM_ActivateFile_APDU Failed");

            return VOS_ERR;
        }

        ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

        if(USIMM_SW_OK != ulResult)/*判断结果*/
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_FDNEstChgInd
功能描述  :FDN激活触发REFRESH上报
输入参数  :无
输出参数  :无
返 回 值  :无
修订记录  :
1.  日    期   : 2014年04月25日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_FDNEstChgInd(VOS_VOID)
{
    USIMM_STKREFRESH_REQ_STRU              stMsg;
    VOS_UINT8                           aucEfest[]={0x3F, 0x00, 0x7F, 0xFF, 0x6F, 0x56};

    /*lint -e534*/
    VOS_MemSet(&stMsg, 0, sizeof(USIMM_STKREFRESH_REQ_STRU));
    /*lint +e534*/

    stMsg.usLen = sizeof(aucEfest);
    /*lint -e534*/
    VOS_MemCpy(stMsg.aucFileList, aucEfest, stMsg.usLen);
    /*lint +e534*/

    USIMM_RefreshFileIndHandle(&stMsg);

    return;
}

/*****************************************************************************
函 数 名  :USIMM_FindTagInSMPTLV
功能描述  :在SimpleTLV数据结构中查询当前的Tag，返回实际数据长度的偏移
输入参数  :ucDataBuf:   数据内容
           ucTag:       查询的Tag
           ulDataLen:   数据总长度
输出参数  :无
返 回 值  :USIMM_TAGNOTFOUND
           长度字节的偏移
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_FindTagInSMPTLV(VOS_UINT8 *pucDataBuf, VOS_UINT8 ucTag, VOS_UINT32 ulDataLen)
{
    VOS_UINT32 i;

    for(i=0; i<ulDataLen;)
    {
        if((pucDataBuf[i]&0x7F) == (ucTag&0x7F))
        {
            if(pucDataBuf[i+1] == 0x81)
            {
                return (i+2);   /*返回长度字节的偏移*/
            }
            else
            {
                return (i+1);
            }
        }
        else
        {
            if(pucDataBuf[i+1] == 0x81)      /*跳到下一个Tag*/
            {
                i += pucDataBuf[i+2] + 3;
            }
            else
            {
                i += pucDataBuf[i+1] + 2;
            }
        }
    }

    return USIMM_TAGNOTFOUND;
}


/*****************************************************************************
函 数 名  :USIMM_FindTagInBERTLV
功能描述  :在BERTLV数据结构中查询Tag并返回长度字节所在偏移　
输入参数  :ucDataBuf:   数据内容
           ucTag:       查询的Tag
           ulDataLen:   数据总长度
输出参数  :无
返 回 值  :USIMM_TAGNOTFOUND
           长度字节的偏移
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_FindTagInBERTLV(VOS_UINT8 *pucDataBuf, VOS_UINT8 ucTag, VOS_UINT32 ulDataLen)
{
    VOS_UINT32 i;

    for(i=0; i<ulDataLen;)
    {
        if((pucDataBuf[i]&0x7F) == (ucTag&0x7F))   /*返回长度字节偏移*/
        {
            return (i+1);
        }
        else
        {
            i += pucDataBuf[i+1] + 2; /*跳到下一个Tag*/
        }
    }

    return USIMM_TAGNOTFOUND;
}

/*****************************************************************************
函 数 名  :USIMM_FindTagInCTLV
功能描述  :在压缩TLV 数据结构中查询Tag并返回Tag数据的偏移　
输入参数  :ucDataBuf:   数据内容
           ucTag:       查询的Tag
           ulDataLen:   数据总长度
输出参数  :无
返 回 值  :USIMM_TAGNOTFOUND
           长度字节的偏移
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_FindTagInCTLV(VOS_UINT8 *pucDataBuf, VOS_UINT8 ucTag, VOS_UINT32 ulDataLen)
{
    VOS_UINT32 i;

    for(i=0; i<ulDataLen;)
    {
        if((pucDataBuf[i]&0xF0) == (ucTag&0xF0))    /*返回当前内容第一个字节偏移*/
        {
            return (i+1);
        }
        else
        {
            i += (pucDataBuf[i]&0x0F) + 1 ;   /*跳到下一个Tag*/
        }
    }

    return USIMM_TAGNOTFOUND;
}

/*****************************************************************************
函 数 名  :USIMM_GetBitFromBuf
功能描述  :从数据中获取指定Bit位的值　
输入参数  :ucDataBuf:   数据内容
           ulBitNo:     Bit号
           ulBufLen:    数据总长度
输出参数  :无
返 回 值  :USIMM_BITNOFOUNE
           Bit值
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_GetBitFromBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo,VOS_UINT32 ulBufLen)
{
    VOS_UINT32  ulOffset;
    VOS_UINT8   ucBit;

    ulOffset = (ulBitNo - 1)/ 8;

    ucBit     = (VOS_UINT8)((ulBitNo - 1)%8);

    if ( ulOffset >=  ulBufLen )
    {
        return USIMM_BITNOFOUNE;
    }

    return ((pucDataBuf[ulOffset]>>ucBit)&0x00000001);
}


/*****************************************************************************
函 数 名  :USIMM_DecideTMode
功能描述  :确定DL层是使用T=0还是T=1模式　
输入参数  :pstSCIATRInfo:底软返回的ATR参数
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2013年10月25日
    作    者   : j00168360
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_DecideTMode(SCI_ATRINFO_S *pstSCIATRInfo)
{
    NV_USIMM_T1_CTRL_PARA_STRU                              stT1CtrlPara;
    USIMM_T1_BLOCK_EPILOGUE_FIELD_ENUM_UINT32               enEDM;
    VOS_UINT32                                              ulResult;
    VOS_UINT32                                              ulResult2 = VOS_ERR;
    VOS_INT32                                               lVoltageSwitchRst;

    /*lint -e534*/
    VOS_MemSet(&stT1CtrlPara, 0, sizeof(stT1CtrlPara));
    /*lint +e534*/

    /* 读NV项 */
    if(VOS_OK != NV_Read(en_NV_Item_Usimm_T1_Ctrl_PARA, &stT1CtrlPara, sizeof(stT1CtrlPara)))
    {
        /* 打印错误 */
        USIMM_ERROR_LOG("USIMM_DecideTMode:USIM Read T1 PARA NV error");

        /* NV读取失败，显式赋值为T0 */
        stT1CtrlPara.enTMode = USIMM_DL_T_MODE_T0;

    }

    /* 如果NV指示支持T=1,且底软API返回支持T=1 */
    if((USIMM_DL_T_MODE_T1 == stT1CtrlPara.enTMode)
        && (T1_PROTOCOL_MODE == pstSCIATRInfo->Tbyte))
    {
        /* 设置T=1模式 */
        g_enUSIMMTMode = USIMM_DL_T_MODE_T1;

        /* TS_102221规范中EDC只使用LRC，而ISO_IEC 7816-3 2006中，则规定按ATR中的指示来决定EDC使用LRC或CRC。
            为协议兼容考虑，代码支持这两种规范，由NV项en_NV_Item_Usimm_T1_Ctrl_PARA决定具体遵循哪一种规范 */
        if(USIMM_T1_ERR_DETECT_MODE_TS102221 == stT1CtrlPara.enEDM)
        {
            enEDM = USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC;
        }
        else
        {
            enEDM = pstSCIATRInfo->errDetectMode;
        }

        /* 备份ATR中的相关T=1信息，用于卡复位后恢复T=1上下文使用 */
        g_stUSIMMT1Para.enErrDetectMode = enEDM;
        g_stUSIMMT1Para.ulIFSC          = pstSCIATRInfo->valIFSC;
        g_stUSIMMT1Para.ulIFSD          = pstSCIATRInfo->valIFSD;

        /* 更新T=1参数 */
        ulResult = USIMM_T1DLUpdateParaByATR(enEDM, pstSCIATRInfo->valIFSC, pstSCIATRInfo->valIFSD);

        if(VOS_OK == ulResult)
        {
            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_2);
            if(VOS_OK != mdrv_sci_switch_protocol((PROTOCOL_MODE_E)g_enUSIMMTMode))
            {
                USIMM_WARNING_LOG("USIMM_DecodeATR:SET T MODE FAILED");

                /* 可维可测信息统计 */
                g_stT1StatisticInfo.ulProtocolSwitchFailCnt++;
            }
            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

            /* 发送IFS命令,确认是否确实支持T=1 */
            ulResult2 = USIMM_T1SendIFSD_APDU((VOS_UINT8)stT1CtrlPara.ulDefaultIFSD);
        }

        /* 更新参数失败或者发送IFS失败都要切到T=0 */
        if((VOS_OK != ulResult) || (VOS_OK != ulResult2))
        {
            if(USIMM_DL_T1_GCF_ENABLE == stT1CtrlPara.enGcfFlag)
            {
                USIMM_ERROR_LOG("USIMM_DecideTMode: it is GCF test");

                return VOS_ERR;
            }

            g_enUSIMMTMode = USIMM_DL_T_MODE_T0;

            /* 发送IFS失败切换到T=0 */
            ulResult = USIMM_DLResetCard(USIMM_RESET_CARD, &lVoltageSwitchRst);

            if(VOS_OK != ulResult)
            {
                USIMM_ERROR_LOG("USIMM_DecideTMode: Reset Card is Failed");

                return VOS_ERR;
            }

            /* 通知底软当前支持T模式,失败只做打印 */
            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_2);
            if(VOS_OK != mdrv_sci_switch_protocol((PROTOCOL_MODE_E)g_enUSIMMTMode))
            {
                USIMM_WARNING_LOG("USIMM_DecodeATR:SET T MODE FAILED");

                /* 可维可测信息统计 */
                g_stT1StatisticInfo.ulProtocolSwitchFailCnt++;
            }
            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

        }
    }
    else
    {
        g_enUSIMMTMode = USIMM_DL_T_MODE_T0;

        /* 通知底软当前支持T模式,失败只做打印 */
        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_2);
        if(VOS_OK != mdrv_sci_switch_protocol((PROTOCOL_MODE_E)g_enUSIMMTMode))
        {
            USIMM_WARNING_LOG("USIMM_DecodeATR:SET T MODE FAILED");

            /* 可维可测信息统计 */
            g_stT1StatisticInfo.ulProtocolSwitchFailCnt++;
        }
        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeATR
功能描述  :实现ATR 历史字节的判断　
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_DecodeATR(VOS_VOID)
{
    VOS_INT32                           lSCIResult;
    VOS_UINT32                          ulATRLen     = 0;
    VOS_UINT8                           aucATR[USIMM_ATR_MAX_LEN] = {0};
    VOS_UINT32                          ulHistoryLen;
    VOS_UINT8                           aucAtrStub[2] = {0x3B, 0x00};
    OM_SIM_ATR_FLAG_STRU                stFlag;
    SCI_ATRINFO_S                       stSCIATRInfo;

    stFlag.ulSimAtrFlag = VOS_FALSE;

    lSCIResult = mdrv_sci_get_atr((VOS_ULONG*)&ulATRLen, aucATR, &stSCIATRInfo);

    if((USIMM_SCI_SUCCESS != lSCIResult)||(ulATRLen > sizeof(aucATR)))
    {
        USIMM_ERROR_LOG("USIMM_DecodeATR:USIMMSCIGetATR get ATR Error");

        return VOS_ERR;
    }

    if(VOS_OK != USIMM_DecideTMode(&stSCIATRInfo))
    {
        USIMM_ERROR_LOG("USIMM_DecodeATR:USIMM_DecideTMode Error");

        return VOS_ERR;
    }

    USIMM_SciDataHook(ulATRLen, aucATR);

    ulHistoryLen = aucATR[USIMM_ATR_T0_OFFSET]&0x0F;  /*获取ATR历史字节长度*/

    if(ulATRLen < (ulHistoryLen+1))
    {
        USIMM_ERROR_LOG("USIMM_DecodeATR:USIM ATR Length Error");

        return VOS_ERR;
    }

    gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType = USIMM_CARD_USIM;

    /* 以下代码是GCF测试桩，仅NV项打开时并且ATR为3B 00时才需要，认为当前是SIM卡 */
    if (VOS_OK != NV_Read(en_NV_Item_Sim_ATR_Flag, &stFlag, sizeof(stFlag)))
    {
        return VOS_OK;
    }

    if (VOS_FALSE == stFlag.ulSimAtrFlag)
    {
        return VOS_OK;
    }

    if (ulATRLen != sizeof(aucAtrStub))
    {
        return VOS_OK;
    }

    if (VOS_OK == VOS_MemCmp(aucATR, aucAtrStub, sizeof(aucAtrStub)))
    {
        gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType = USIMM_CARD_SIM;

        /* 默认从7F20开始选择文件 */
        gstUSIMMCurFileInfo.usCurDFID      = MF;
        gstUSIMMCurFileInfo.usCurEFID      = USIMM_NULL_ID;
        gstUSIMMCurFileInfo.usCurDFFcpLen  = VOS_NULL;
        gstUSIMMCurFileInfo.usFilePathLen  = 1;
        gstUSIMMCurFileInfo.ausFilePath[0] = MF;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeATRSecondSteup
功能描述  :ATR解析第二步　
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_FindTagInCTLV
           USIMM_GetBitFromBuf
修订记录  :
1. 日    期   : 2012年7月28日
    作    者   : h59254
    修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_DecodeATRSecondStep(VOS_VOID)
{
    VOS_UINT32                          ulATRLen     = 0;
    VOS_UINT8                           aucATR[USIMM_ATR_MAX_LEN]   = {0};
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulDataOffset;
    VOS_UINT32                          ulHistoryLen;
    VOS_INT32                           lSCIResult;
    VOS_UINT32                          ulResult;
    SCI_ATRINFO_S                       stSCIATRInfo;

    lSCIResult = mdrv_sci_get_atr((VOS_ULONG*)&ulATRLen, aucATR, &stSCIATRInfo);

    if ((USIMM_SCI_SUCCESS != lSCIResult)
        ||(ulATRLen > sizeof(aucATR)))
    {
        USIMM_ERROR_LOG("USIMM_DecodeATRSecondStep:USIMMSCIGetATR get ATR Error");

        return;
    }

    USIMM_SciDataHook(ulATRLen, aucATR);

    /* 获取ATR历史字节长度 */
    ulHistoryLen    = aucATR[USIMM_ATR_T0_OFFSET]&0x0F;

    /* 获取ATR历史字节的起始位置 */
    if ((ulATRLen < ulHistoryLen) || (VOS_NULL == ulHistoryLen))
    {
        return;
    }

    ulOffset        = ulATRLen - ulHistoryLen;

    /* 3G卡的历史字节 */
    if(CTLV_IND_TAG == aucATR[ulOffset])
    {
        ulOffset++;                             /* 指向后面的的一个Tag */

        if (ulOffset >= sizeof(aucATR))
        {
            return;
        }

        ulHistoryLen--;

        /*解析卡能力字节*/
        ulResult = USIMM_FindTagInCTLV(&aucATR[ulOffset], CARD_CPB_TAG, ulHistoryLen);

        if(USIMM_TAGNOTFOUND != ulResult)
        {
            if (ulResult > ulHistoryLen)
            {
                return;
            }

            ulDataOffset = ulResult + ulOffset;

            if (ulDataOffset >= sizeof(aucATR))
            {
                return;
            }

            gstUSIMMBaseInfo.enSupportPath = USIMM_GetBitFromBuf(&aucATR[ulDataOffset], 6, sizeof(VOS_UINT8));

            gstUSIMMBaseInfo.enSupportSFI  = USIMM_GetBitFromBuf(&aucATR[ulDataOffset], 3, sizeof(VOS_UINT8));

            if(CARD_CPB3_TAG == aucATR[ulDataOffset-1])
            {
                if ((ulDataOffset + 1) >= sizeof(aucATR))
                {
                    return;
                }

                gstUSIMMBaseInfo.enSupportChannel = (((aucATR[ulDataOffset+1]&0x10) != 0)?USIMM_SUPPORT_CHANNEL:USIMM_NOTSUPPORT_CHANNEL);
            }
        }
    }

    return;
}


/*****************************************************************************
函 数 名  :USIMM_DecodeDFPSDO
功能描述  :解析USIM卡的DF FCP中的PSDO数据内容
输入参数  :pPSDO:       PSDO的数据内容
           ulDataLen:  PSDO数据长度
输出参数  :pstDfInfo:当前DF的PIN信息
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_DecodeDFPSDO(VOS_UINT8 *pucPSDO, VOS_UINT32 ulDataLen,USIMM_DFFCP_ST *pstDfInfo)
{
    VOS_UINT32  ulOffset = 0;
    VOS_UINT8   ucPINMapOffset = 2;
    VOS_UINT32  i ;
    VOS_UINT8   ucPinMapMask=0x80;
    VOS_UINT32  ulPinStatus;

    i = pucPSDO[ulOffset+1]*8;       /*总共可能的密码个数用于后面位图计算*/

    ulOffset = pucPSDO[ulOffset+1] + 2;

    while(((i > 0) && (ulOffset < ulDataLen)))
    {
        if(pucPSDO[ulOffset] != USIMM_FCP_PINRER_TAG)
        {
            ulOffset += 3;

            continue;
        }

        ulPinStatus = (pucPSDO[ucPINMapOffset]&ucPinMapMask)?1:0; /*如果Bit不为0*/

        if((pucPSDO[ulOffset+2] <= 0x88) && (pucPSDO[ulOffset+2] >= 0x81))
        {
            pstDfInfo->ucPIN2RefNum                 = pucPSDO[ulOffset+2];

            pstDfInfo->stPINInfo.enPin2Enable = USIMM_PIN_ENABLED&ulPinStatus;
        }
        else if((pucPSDO[ulOffset+2] <= 0x08) && (pucPSDO[ulOffset+2] >= 0x01))
        {
            pstDfInfo->ucPIN1RefNum                 = pucPSDO[ulOffset+2];

            pstDfInfo->stPINInfo.enPin1Enable = USIMM_PIN_ENABLED&ulPinStatus;
        }
        else if(pucPSDO[ulOffset+2] == 0x11)
        {
            gstUSIMMBaseInfo.enUniversalPINStatus = USIMM_PIN_ENABLED&ulPinStatus;
        }
        else
        {
            USIMM_NORMAL_LOG("USIMM_DecodeDFPSDO: The PSDO Could Not Support");
        }

        i--;

        ulOffset += 3;

        if( 0 == (i % 8) )/*如果bitmap走完一个字节，取下字节的bitmap*/
        {
            ucPINMapOffset++;

            ucPinMapMask = 0x80;
        }
        else
        {
            ucPinMapMask = ucPinMapMask>>1;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeCharacter
功能描述  :解析File characteristics,获得Clock的停止状态及LEVEL信息
输入参数  :ucFileChara
输出参数  :无
返 回 值  :无
调用函数  :无
修订记录  :
1. 日    期   : 2008年8月4日
    作    者   : m00128685
    修改内容   : Creat

*****************************************************************************/
VOS_VOID USIMM_DecodeCharacter(VOS_UINT8 ucFileChara)
{
    if(0x00 == (ucFileChara&0x0D))
    {
        gstUSIMMDrvInfo.enCLKStop = USIMM_CLKSTOP_NOALLOW;

        return;
    }

    if(0x00 == (ucFileChara&0x0C))/*解析Level ，取值HIGH,LOW,NONE*/
    {
         gstUSIMMDrvInfo.enCLKLevel = USIMM_CLKLEVEL_LOW;/*如果当前电平不确定，默认按照低电平进行*/
    }
    else if(0x04 == (ucFileChara&0x0C))
    {
        gstUSIMMDrvInfo.enCLKLevel = USIMM_CLKLEVEL_HIGH;/*高电平进入时钟停止*/
    }
    else if(0x08 == (ucFileChara&0x0C))
    {
        gstUSIMMDrvInfo.enCLKLevel = USIMM_CLKLEVEL_LOW;/*低电平进入时钟停止*/
    }
    else
    {
        USIMM_WARNING_LOG("USIMM_DecodeCharacter:Input Error");

        gstUSIMMDrvInfo.enCLKLevel = USIMM_CLKLEVEL_NONE;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeUsimDFFcp
功能描述  :解析USIM卡的DF FCP内容
输入参数  :ucLen:       FCP数据长度
           pucData:   FCP数据内容
输出参数  :pstDfInfo: Df信息
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_FindTagInSMPTLV
           USIMM_FindTagInBERTLV
           USIMM_DecodeDFPSDO
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_DecodeUsimDFFcp(VOS_UINT32 ulLen, VOS_UINT8 *pucData, USIMM_DFFCP_ST *pstDfInfo)
{
    VOS_UINT32 ulResult = VOS_OK;
    VOS_UINT32 ulStart;
    VOS_UINT32 ulOffset;
    VOS_UINT32 ulSubOffset;
    VOS_UINT32 ulDataLen;

    ulStart = USIMM_FindTagInSMPTLV(pucData, USIMM_FCP_TAG, ulLen);/*查询起始Tag*/

    if(USIMM_TAGNOTFOUND == ulStart)
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimDFFcp:FCP Tag not found");

        return VOS_ERR;
    }

    ulDataLen = pucData[ulStart];   /*有效数据长度*/

    ulStart++;                      /*指向需要解析的数据头*/

    /*解析文件描述字段*/
    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_FILE_DES_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND == ulOffset)   /*该字段必须存在*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimDFFcp:File Describer Tag not found");

        return VOS_ERR;
    }

    ulOffset +=ulStart + 1;

    if((pucData[ulOffset]&0x38) == 0) /*文件类型错误*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimDFFcp:File Type Error");

        return VOS_ERR;
    }

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_FID_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        ulOffset += ulStart + 1;

        pstDfInfo->usDFID = (VOS_UINT16)((pucData[ulOffset]<<0x08)&0xFF00)+pucData[ulOffset+1];
    }

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_NAME_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        ulOffset += ulStart;

        if(pucData[ulOffset] > 16)
        {
            USIMM_ERROR_LOG("USIMM_DecodeUsimDFFcp:File Name Error");

            return VOS_ERR;
        }

        /*lint -e534*/
        VOS_MemCpy(pstDfInfo->aucName, &pucData[ulOffset+1], pucData[ulOffset]);
        /*lint +e534*/

        pstDfInfo->ucNameLen = pucData[ulOffset];
    }

    /*解析File Characteristic 获得有关CLock停止状态及Level信息*/
    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_PRIVITE_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
       ulSubOffset = USIMM_FindTagInBERTLV(&pucData[ulOffset+ulStart+1], USIMM_FCP_CHARA_TAG, pucData[ulOffset+ulStart]);

       if ( USIMM_TAGNOTFOUND != ulSubOffset )
       {
            USIMM_DecodeCharacter(pucData[ulOffset+ulStart+ulSubOffset+2]);/*跳过长度信息指向要解析的数据*/

            pstDfInfo->ucCharaByte = pucData[ulOffset+ulStart+ulSubOffset+2];
       }

       ulSubOffset = USIMM_FindTagInBERTLV(&pucData[ulOffset+ulStart+1], USIMM_FCP_SUPSYSCMD_TAG, pucData[ulOffset+ulStart]);

       if ( USIMM_TAGNOTFOUND != ulSubOffset )
       {
           pstDfInfo->ucSupCmd = pucData[ulOffset+ulStart+ulSubOffset+2];
       }
    }

    /*确定DF安全标识方法*/
    pstDfInfo->enSCMode  = USIMM_SC_ATTRIB_NO;

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_SA_CF_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        pstDfInfo->enSCMode = USIMM_SC_ATTRIB_COMPACT;
    }

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_SA_REF_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        pstDfInfo->enSCMode = USIMM_SC_ATTRIB_REFERENCE;
    }

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_SA_EF_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        pstDfInfo->enSCMode = USIMM_SC_ATTRIB_EXPANDED;
    }

    /*解析PIN状态数据对象描述字段*/
    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_PIN_TO_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND == ulOffset)
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimDFFcp:FCP Pin Tag not found");
        return VOS_ERR;
    }

    ulResult = USIMM_DecodeDFPSDO(&pucData[ulOffset+ulStart+1], pucData[ulOffset+ulStart],pstDfInfo);

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeSimDFFcp
功能描述  :解析USIM卡的DF FCP内容　
输入参数  :ucLen:       FCP数据长度
           pucData:   FCP数据内容
输出参数  :pstDfInfo: Df信息
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_DecodeSimDFFcp(VOS_UINT32 ulLen, VOS_UINT8 *pucData, USIMM_DFFCP_ST *pstDfInfo)
{
    USIMM_SIMDF_FCP_ST            stSimDFFcp;

    if(ulLen < sizeof(USIMM_SIMDF_FCP_ST))
    {
        USIMM_ERROR_LOG("USIMM_DecodeSimDFFcp:Input Length Error");

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy((VOS_UINT8 *)&stSimDFFcp, pucData, sizeof(USIMM_SIMDF_FCP_ST));
    /*lint +e534*/

    stSimDFFcp.usFileID = ((stSimDFFcp.usFileID<<8)&0xff00)|((stSimDFFcp.usFileID>>8)&0x00ff);

    pstDfInfo->usDFID = stSimDFFcp.usFileID;

    /*文件类型错误*/
    if ((USIMM_SIM_FILE_TYPE_MF != stSimDFFcp.ucFileType)
     && (USIMM_SIM_FILE_TYPE_DF != stSimDFFcp.ucFileType))
    {
        USIMM_ERROR_LOG("USIMM_DecodeSimDFFcp:File Type Error");

        return VOS_ERR;
    }

    pstDfInfo->ucCharaByte = stSimDFFcp.ucFileChara;

    /*解析File Characteristic 获得有关CLock停止状态及Level信息*/
    USIMM_DecodeCharacter(stSimDFFcp.ucFileChara);

    if(0x00 == (stSimDFFcp.ucFileChara&0x80))    /*获取当前的PIN状态*/
    {
        pstDfInfo->stPINInfo.enPin1Enable = USIMM_PIN_ENABLED;
    }
    else
    {
        pstDfInfo->stPINInfo.enPin1Enable = USIMM_PIN_DISABLED;
    }

    pstDfInfo->stPINInfo.enPin2Enable = USIMM_PIN_ENABLED;

    /*初始化PIN剩余次数*/
    pstDfInfo->stPINInfo.ucPin1RemainTime = stSimDFFcp.ucPIN1RemainTime&0x0F;

    pstDfInfo->stPINInfo.ucPuk1RemainTime = stSimDFFcp.ucPUK1RemainTime&0x0F;

    pstDfInfo->stPINInfo.ucPin2RemainTime = stSimDFFcp.ucPIN2RemainTime&0x0F;

    pstDfInfo->stPINInfo.ucPuk2RemainTime = stSimDFFcp.ucPUK2RemainTime&0x0F;

    /*初始化默认内容*/
    pstDfInfo->ucPIN1RefNum = 0x01;

    pstDfInfo->ucPIN2RefNum = 0x02;

    pstDfInfo->ucNameLen    = 0;

    pstDfInfo->enSCMode     = USIMM_SC_ATTRIB_NO;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeUsimEFFcp
功能描述  :解析USIM卡的EF FCP内容　
输入参数  :ucLen:     FCP数据长度
           pucData:   FCP数据内容
输出参数  :pstDfInfo: EF信息
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_FindTagInSMPTLV
           USIMM_FindTagInBERTLV
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat
2.日    期  : 2011年7月5日
  作    者  : j00168360
  修改内容  : [DTS2011070102597]，SIM卡FDN功能开启，ADN文件可读可更新时电话本无法操作
*****************************************************************************/
VOS_UINT32 USIMM_DecodeUsimEFFcp(VOS_UINT32 ulLen, VOS_UINT8 *pucData,USIMM_EFFCP_ST *pstEFInfo)
{
    VOS_UINT32 ulStart;
    VOS_UINT32 ulOffset;
    VOS_UINT32 ulDataLen;
    VOS_UINT8  ucTemp;

    ulStart = USIMM_FindTagInSMPTLV(pucData, USIMM_FCP_TAG, ulLen);/*查询起始Tag*/

    if(USIMM_TAGNOTFOUND == ulStart)
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimEFFcp:Data Length Error");

        return VOS_ERR;
    }

    ulDataLen = pucData[ulStart];   /*有效数据长度*/

    ulStart++;                     /*指向需要解析的数据头*/

    /*解析文件描述字段*/
    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_FILE_DES_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND == ulOffset)   /*该字段必须存在*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimEFFcp:File Describer not found");

        return VOS_ERR;
    }

    ulOffset += ulStart;

    ucTemp = pucData[ulOffset+1]&0x07;

    if(0x01 == ucTemp) /*文件类型TRANSPARENT*/
    {
        pstEFInfo->enFileType = USIMM_EFSTRUCTURE_TRANSPARENT;
    }
    else if(0x02 == ucTemp)/*文件为FIXED*/
    {
        pstEFInfo->enFileType       = USIMM_EFSTRUCTURE_FIXED;

        pstEFInfo->ucRecordLen    = pucData[ulOffset+4];

        pstEFInfo->ucRecordNum   = pucData[ulOffset+5];
    }
    else if(0x06 == ucTemp)/*文件为CYCLE*/
    {
        pstEFInfo->enFileType = USIMM_EFSTRUCTURE_CYCLE;

        pstEFInfo->ucRecordLen    = pucData[ulOffset+4];

        pstEFInfo->ucRecordNum   = pucData[ulOffset+5];
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimEFFcp:File Type Error");

        return VOS_ERR;
    }

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_FID_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        ulOffset += ulStart + 1;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimEFFcp:File ID Tag not Found");

        return VOS_ERR;
    }

    /*解析文件大小*/
    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_FILESIZE_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND == ulOffset)   /*字段必须存在*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimEFFcp:File Size Tag not Found");

        return VOS_ERR;
    }

    ulOffset += ulStart;

    pstEFInfo->usFileLen = (VOS_UINT16)(((pucData[ulOffset+1]<<0x08)&0xFF00) + pucData[ulOffset+2]);

    /*解析文件状态字段*/
    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_LCSI_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND == ulOffset)
    {
        USIMM_ERROR_LOG("USIMM_DecodeUsimEFFcp:Life Cycle Tag not Found");

        return VOS_ERR;
    }

    /* 仅当b1为0，b3为1时，文件才是DEACTIVE的 */
    if  ((0x0 == (pucData[ulOffset+ulStart+1]&0x01))
        && (0x4 == (pucData[ulOffset+ulStart+1]&0x04)))
    {
        pstEFInfo->enFileStatus = USIMM_EFSTATUS_DEACTIVE;
    }
    else
    {
        pstEFInfo->enFileStatus = USIMM_EFSTATUS_ACTIVE;
    }

    pstEFInfo->enFileReadUpdateFlag = USIMM_EF_RW_NOT;

    /*解析文件短名*/
    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_SFI_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        pstEFInfo->ucSFI = pucData[ulOffset+ulStart+1];
    }

    /*确定EF安全标识方法*/
    pstEFInfo->enSCMode  = USIMM_SC_ATTRIB_NO;

    pstEFInfo->usEFArrID = 0;

    pstEFInfo->ucArrNo   = 0;

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_SA_CF_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        pstEFInfo->enSCMode = USIMM_SC_ATTRIB_COMPACT;
    }

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_SA_REF_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        ulOffset += ulStart;

        pstEFInfo->enSCMode = USIMM_SC_ATTRIB_REFERENCE;

        pstEFInfo->usEFArrID = (VOS_UINT16)((pucData[ulOffset+1]<<0x08)&0xFF00)+pucData[ulOffset+2];

        pstEFInfo->ucArrNo    = pucData[ulOffset+3];
    }

    ulOffset = USIMM_FindTagInBERTLV(&pucData[ulStart], USIMM_FCP_SA_EF_TAG, ulDataLen);

    if(USIMM_TAGNOTFOUND != ulOffset)
    {
        pstEFInfo->enSCMode = USIMM_SC_ATTRIB_EXPANDED;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeSimEFFcp
功能描述  :解析SIM卡的EF FCP内容　
输入参数  :ucLen:     FCP数据长度
           pucData:   FCP数据内容
输出参数  :pstDfInfo: EF信息
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :无
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat
2.日    期  : 2011年7月5日
  作    者  : j00168360
  修改内容  : [DTS2011070102597]，SIM卡FDN功能开启，ADN文件可读可更新时电话本无法操作
*****************************************************************************/
VOS_UINT32 USIMM_DecodeSimEFFcp(VOS_UINT32 ulLen, VOS_UINT8 *pucData,USIMM_EFFCP_ST *pstEFInfo)
{
    USIMM_SIMEF_FCP_ST          stSimEFFcp;

    if(ulLen < (sizeof(USIMM_SIMEF_FCP_ST) - 1))/*FCP的第15位对于透明文件不是mandatory 的*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeSimEFFcp:Input Length Error");

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy((VOS_UINT8 *)&stSimEFFcp, pucData, sizeof(USIMM_SIMEF_FCP_ST));
    /*lint +e534*/

    stSimEFFcp.usFileID = ((stSimEFFcp.usFileID>>8)&0x00ff)|((stSimEFFcp.usFileID<<8)&0xff00);

    stSimEFFcp.usFileLen = ((stSimEFFcp.usFileLen>>8)&0x00ff)|((stSimEFFcp.usFileLen<<8)&0xff00);

    pstEFInfo->usFileLen = stSimEFFcp.usFileLen;/*获取文件大小*/

    if(0x04 != stSimEFFcp.ucFileType)/*文件类型错误*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeSimEFFcp:File Type Error");

        return VOS_ERR;
    }

    pstEFInfo->enFileStatus         = (stSimEFFcp.ucFileStatus&0x01);/*获取文件状态*/

    pstEFInfo->enFileReadUpdateFlag = (stSimEFFcp.ucFileStatus&0x04);/*获取文件读取和更新标志*/

    if(0x00 == stSimEFFcp.ucEFStruct)   /*文件为TRANSPARENT*/
    {
        pstEFInfo->enFileType  = USIMM_EFSTRUCTURE_TRANSPARENT;
    }
    else if(0x01 == stSimEFFcp.ucEFStruct)  /*文件类型为FIXED*/
    {
        pstEFInfo->enFileType  = USIMM_EFSTRUCTURE_FIXED;

        pstEFInfo->ucRecordLen = stSimEFFcp.ucRecordLen;

        pstEFInfo->ucRecordNum = (VOS_UINT8)(pstEFInfo->usFileLen/pstEFInfo->ucRecordLen);
    }
    else if(0x03 == stSimEFFcp.ucEFStruct)  /*文件类型为CYCLE*/
    {
        pstEFInfo->enFileType  = USIMM_EFSTRUCTURE_CYCLE;

        pstEFInfo->ucRecordLen = stSimEFFcp.ucRecordLen;

        pstEFInfo->ucRecordNum = (VOS_UINT8)(pstEFInfo->usFileLen/pstEFInfo->ucRecordLen);
    }
    else    /*文件类型错误*/
    {
        USIMM_WARNING_LOG("USIMM_DecodeSimEFFcp: EF Struct Error");

        return VOS_ERR;
    }

    /*初始化其它内容*/
    pstEFInfo->enSCMode  = USIMM_SC_ATTRIB_NO;

    pstEFInfo->usEFArrID = 0;

    pstEFInfo->ucArrNo   = 0;

    pstEFInfo->ucSFI     = 0;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeEFFcp
功能描述  : 解析FCP内容，
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DecodeUsimEFFcp
           USIMM_DecodeSimEFFcp

修订记录  :
1. 日    期   : 2010年8月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_DecodeEFFcp(
    USIMM_CARD_TYPE_ENUM_UINT32         enCurCardType,
    USIMM_APDU_ST                      *pstApduData,
    USIMM_CURFILEINFO_ST               *pstCurFileInfo)
{
    VOS_UINT32 ulResult;

    USIMM_ClearCurEFInfo(pstCurFileInfo);

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    if ((USIMM_CARD_USIM == enCurCardType) || (USIMM_CARD_CSIM == enCurCardType))  /*当前为USIM CSIM*/
#else
    if (USIMM_CARD_USIM == enCurCardType)  /*当前为USIM*/
#endif  /*(FEATURE_UE_MODE_CDMA == FEATURE_ON)*/
    {
        ulResult = USIMM_DecodeUsimEFFcp((VOS_UINT8)pstApduData->ulRecDataLen, pstApduData->aucRecvBuf, &pstCurFileInfo->stEFInfo);
    }
    else
    {
        ulResult = USIMM_DecodeSimEFFcp((VOS_UINT8)pstApduData->ulRecDataLen, pstApduData->aucRecvBuf, &pstCurFileInfo->stEFInfo);
    }

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_DecodeEFFcp:Decode FCP error");

        /*lint -e534*/
        VOS_MemSet(&pstCurFileInfo->stEFInfo, 0, sizeof(USIMM_EFFCP_ST));
        /*lint +e534*/

        return USIMM_SW_ERR;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeDFFcp
功能描述  : 解析FCP内容，
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_DecodeUsimDFFcp
           USIMM_DecodeSimDFFcp

修订记录  :
1. 日    期   : 2010年8月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_DecodeDFFcp(
    USIMM_CARD_TYPE_ENUM_UINT32         enCurCardType,
    USIMM_APDU_ST                      *pstApduData,
    USIMM_CURFILEINFO_ST               *pstCurFileInfo)
{
    VOS_UINT32 ulResult;

    USIMM_ClearCurDFInfo(pstCurFileInfo);

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    if ((USIMM_CARD_USIM == enCurCardType) || (USIMM_CARD_CSIM == enCurCardType))  /*当前为USIM CSIM*/
#else
    if (USIMM_CARD_USIM == enCurCardType)  /*当前为USIM*/
#endif  /*(FEATURE_UE_MODE_CDMA == FEATURE_ON)*/
    {
        ulResult = USIMM_DecodeUsimDFFcp(pstApduData->ulRecDataLen, pstApduData->aucRecvBuf, &pstCurFileInfo->stDFInfo);
    }
    else
    {
        ulResult = USIMM_DecodeSimDFFcp(pstApduData->ulRecDataLen, pstApduData->aucRecvBuf, &pstCurFileInfo->stDFInfo);
    }

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_DecodeDFFcp:Decode Fcp error");

        return USIMM_SW_ERR;
    }

    pstCurFileInfo->usCurDFFcpLen = (VOS_UINT16)pstApduData->ulRecDataLen;

    return ulResult;
}

/*****************************************************************************
 函 数 名  : USIMM_DecodeFileFcp
 功能描述  : 解析USIM卡的文件 FCP内容
 输入参数  : usFileId;
 输出参数  : 无
 返 回 值  : 无
 修改历史  : m00128685
             2010-03-19
*****************************************************************************/
VOS_UINT32 USIMM_DecodeFileFcp(USIMM_CARD_TYPE_ENUM_UINT32     enCardType,
                                        USIMM_U16_LVDATA_STRU          *pstFilePath,
                                        USIMM_APDU_ST                  *pstApduData,
                                        USIMM_CURFILEINFO_ST           *pstCurFileInfo)
{
    VOS_UINT32              ulResult = VOS_ERR;
    VOS_UINT16              usFileId;

    if(pstFilePath->ulDataLen < 1)
    {
        USIMM_ERROR_LOG("USIMM_DecodeFileFcp: file path len is 0");

        return VOS_ERR;
    }

    usFileId = pstFilePath->pusData[pstFilePath->ulDataLen-1];

    if (USIMM_IS_EF_FILE(usFileId))/* 更新EF文件FCP */
    {
        ulResult = USIMM_DecodeEFFcp(enCardType, pstApduData, pstCurFileInfo);
    }
    else/* 更新DF文件FCP */
    {
        ulResult = USIMM_DecodeDFFcp(enCardType, pstApduData, pstCurFileInfo);
    }

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_DecodeFileFcp: Fail to Decode FCP");
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_DecodeEFDIR
功能描述  : 解析EFDIR内容，并且选中其中的3GPP应用
输入参数  :无
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :USIMM_SelectEFByID
           USIMM_ReadLFFile
           USIMM_SelectFile_APDU
修订记录  :
1. 日    期   : 2007年7月10日
    作    者   : z00100318
    修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_DecodeEFDIR(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulAidLen;
    VOS_UINT32                          i;
    VOS_UINT8                          *pucdata;
    VOS_UINT8                           aucUsimRidAppCode[USIMM_RID_LEN + USIMM_APP_CODE_LEN] = {0xA0,0x00,0x00,0x00,0x87,0x10,0x02};
    VOS_UINT8                           aucIsimRidAppCode[USIMM_RID_LEN + USIMM_APP_CODE_LEN] = {0xA0,0x00,0x00,0x00,0x87,0x10,0x04};
    VOS_UINT8                           aucCsimRidAppCode[USIMM_RID_LEN + USIMM_APP_CODE_LEN] = {0xA0,0x00,0x00,0x03,0x43,0x10,0x02};
    VOS_UINT16                          ausPath[] = {MF, EFDIR};
    VOS_BOOL                            ulUsimAidHit = VOS_FALSE;

    ulResult = USIMM_SelectFile(USIMM_UMTS_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

    if(VOS_OK != ulResult)/*选择文件*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeEFDIR: EFDIR could not Found");/*打印错误*/

        return VOS_ERR;
    }

    pucdata = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM,DYNAMIC_MEM_PT,gstUSIMMCurFileInfo.stEFInfo.usFileLen);

    if(VOS_NULL_PTR == pucdata)   /*判断结果*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeEFDIR: VOS_MemAlloc Error");/*打印错误*/

        return VOS_ERR;
    }

    if(USIMM_EFSTRUCTURE_FIXED == gstUSIMMCurFileInfo.stEFInfo.enFileType)
    {
        if (USIMM_SW_OK != USIMM_ReadLFFile(&gstUSIMMCurFileInfo.stEFInfo, USIMM_READ_ALLRECORD, pucdata))      /*读取记录内容*/
        {
            USIMM_INFO_LOG("USIMM_DecodeEFDIR: USIMM_ReadLFFile Error");
        }
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_DecodeEFDIR: EFDIR File Type Error");/*打印错误*/

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pucdata);
        /*lint +e534*/

        return VOS_ERR;                                              /*按照102.221 13.1 节不支持二进制格式文件*/
    }

    ulResult = VOS_ERR;

    for(i=0; i<gstUSIMMCurFileInfo.stEFInfo.usFileLen; i+=gstUSIMMCurFileInfo.stEFInfo.ucRecordLen)
    {
        if ( (APP_TMP_TAG != pucdata[i + APP_TMP_TAG_OFFSET])
          || (APP_IND_TAG != pucdata[i + APP_IND_TAG_OFFSET]))    /*判断内容合法性*/
        {
            USIMM_WARNING_LOG("USIMM_DecodeEFDIR: EFDIR Content not Right");/*打印错误*/

            continue;
        }

        ulAidLen = (pucdata[i + APP_AID_LEN_OFFSET] > USIMM_AID_LEN_MAX)?USIMM_AID_LEN_MAX:pucdata[i + APP_AID_LEN_OFFSET];

        /* 只要匹配到A0000000871002就认为找到了USIM的AID */
        if ((VOS_OK == VOS_MemCmp(pucdata + i + APP_AID_VALUE_OFFSET, aucUsimRidAppCode, sizeof(aucUsimRidAppCode)))
            && (VOS_FALSE == ulUsimAidHit))
        {

            /*lint -e534*/
            VOS_MemCpy(gstUSIMMADFInfo.aucAID, pucdata + i + APP_AID_VALUE_OFFSET, ulAidLen);    /*保存相关信息*/
            /*lint +e534*/

            gstUSIMMADFInfo.ulAIDLen = ulAidLen;

            ulResult = VOS_OK;

            g_astAidInfo[USIMM_AID_TYPE_USIM].ulAIDLen = ulAidLen;
            /*lint -e534*/
            VOS_MemCpy(g_astAidInfo[USIMM_AID_TYPE_USIM].aucAID, pucdata + i + APP_AID_VALUE_OFFSET, ulAidLen);    /*保存相关信息*/
            /*lint +e534*/

            ulUsimAidHit = VOS_TRUE;
        }

        /* 只要匹配到A0000000871004就认为找到了ISIM的AID */
        if (VOS_OK == VOS_MemCmp(pucdata + i + APP_AID_VALUE_OFFSET, aucIsimRidAppCode, sizeof(aucIsimRidAppCode)))
        {
            g_astAidInfo[USIMM_AID_TYPE_ISIM].ulAIDLen = ulAidLen;
            /*lint -e534*/
            VOS_MemCpy(g_astAidInfo[USIMM_AID_TYPE_ISIM].aucAID, pucdata + i + APP_AID_VALUE_OFFSET, ulAidLen);    /*保存相关信息*/
            /*lint +e534*/
        }

        /* 只要匹配到A0000003431002就认为找到了CSIM的AID */
        if (VOS_OK == VOS_MemCmp(pucdata + i + APP_AID_VALUE_OFFSET, aucCsimRidAppCode, sizeof(aucCsimRidAppCode)))
        {
            g_astAidInfo[USIMM_AID_TYPE_CSIM].ulAIDLen = ulAidLen;
            /*lint -e534*/
            VOS_MemCpy(g_astAidInfo[USIMM_AID_TYPE_CSIM].aucAID, pucdata + i + APP_AID_VALUE_OFFSET, ulAidLen);    /*保存相关信息*/
            /*lint +e534*/
        }
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pucdata);
    /*lint +e534*/

    g_stUSIMMCardVersionType.enCardMode     = USIMM_CARD_UICC_TYPE;
    g_stUSIMMCardVersionType.ucHasCModule   = (VOS_NULL != g_astAidInfo[USIMM_AID_TYPE_CSIM].ulAIDLen);
    g_stUSIMMCardVersionType.ucHasWGModule  = (VOS_NULL != g_astAidInfo[USIMM_AID_TYPE_USIM].ulAIDLen);

    /* USIM和CSIM同时不存在，EFDIR文件记录无效，切到SIM卡继续初始化 */
    if ((VOS_NULL == g_astAidInfo[USIMM_AID_TYPE_USIM].ulAIDLen)
     && (VOS_NULL == g_astAidInfo[USIMM_AID_TYPE_CSIM].ulAIDLen))
    {
        return VOS_ERR;
    }

    /* 电信要求必须能够支持CDMA应用 */
    if (VOS_TRUE == USIMM_IsCLEnable())
    {
        /* 如果是电信版本，CSIM+USIM时按有卡初始化，单USIM上报无卡，单CSIM时上报无卡由CSIMA来初始化CDMA的应用 */
        if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulCUIMCheck)
        {
            if ((VOS_NULL == g_astAidInfo[USIMM_AID_TYPE_USIM].ulAIDLen)
             || (VOS_NULL == g_astAidInfo[USIMM_AID_TYPE_CSIM].ulAIDLen))
            {
                gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType = USIMM_CARD_NOCARD;
                return USIMM_INIT_FATAL_EXIT;
            }
        }
        /* 如果是全网通版本，CSIM+USIM时按有卡初始化，单USIM上报有卡按GUTL版本使用，单CSIM时上报无卡由CSIMA来初始化CDMA的应用 */
        else
        {
            if ((VOS_NULL == g_astAidInfo[USIMM_AID_TYPE_USIM].ulAIDLen)
             && (VOS_NULL != g_astAidInfo[USIMM_AID_TYPE_CSIM].ulAIDLen))
            {
                /*单CSIM卡*/
                gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType = USIMM_CARD_NOCARD;
                return USIMM_INIT_FATAL_EXIT;
            }
        }
    }

    return ulResult;
}

/*****************************************************************************
 函 数 名  : USIMM_ReportEvent
 功能描述  : 通过调用OM提供的接口上报状态事件
 输入参数  : usEventId: 事件ID
 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史  : m00128685
             2009-11-10
*****************************************************************************/
VOS_VOID USIMM_ReportEvent(VOS_UINT16 usEventId)
{
    DIAG_EVENT_IND_STRU                 stEventInd;
    VOS_UINT8                           usModemId;

/* 标识主卡副卡 */
#if defined (INSTANCE_1)
    usModemId = DIAG_MODEM_1;
#elif defined (INSTANCE_2)
    usModemId = DIAG_MODEM_2;
#else
    usModemId = DIAG_MODEM_0;
#endif

    stEventInd.ulModule = DIAG_GEN_MODULE(usModemId, DIAG_MODE_COMM);
    stEventInd.ulPid    = WUEPS_PID_USIM;
    stEventInd.ulEventId= usEventId;
    stEventInd.ulLength = VOS_NULL;
    stEventInd.pData    = VOS_NULL_PTR;

    /*lint -e534*/
    (VOS_VOID)DIAG_EventReport(&stEventInd);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : USIMM_RefrehFilePath
 功能描述  : 更新选文件的路径信息
 输入参数  : pucDstPath: 待更新的路径信息
             *pusDstLen:  待更新路径长度
             pucSrcPath: 新产生的路径信息
             usSrcLen:   新产生的路径长度
 输出参数  : pucDstPath: 更新后的路径信息
             *pusDstLen: 更新后的路径长度
 返 回 值  : VOS_ERR:更新路径信息失败
             VOS_OK: 更新路径信息成功
 修改历史  : m00128685
             2010-03-19
*****************************************************************************/
VOS_UINT32 USIMM_RefrehFilePath(VOS_UINT8 *pucDstPath,
                                       VOS_UINT16 *pusDstLen,
                                       VOS_UINT8 *pucSrcPath,
                                       VOS_UINT16 usSrcLen)
{
    VOS_UINT16 usLen = 0;
    VOS_UINT8  ucPreDfFlag = VOS_FALSE;
    VOS_UINT8  ucPreDfType = MFTAG;

    switch (pucSrcPath[0])
    {
        case EFUNDERGRANDADF:
            ucPreDfType = DFUNDERDF;
            break;
        case EFUNDERMF:
        case DFUNDERMF:
            ucPreDfType = MFTAG;
            break;
        case DFUNDERDF:
        case EFUNDERDF:
            ucPreDfType = DFUNDERMF;
            break;
        case MFTAG:
            usLen = *pusDstLen;
            break;
        default:
            USIMM_ERROR_LOG("USIMM_RefrehFilePath: Unknown File Type");
            return VOS_ERR;
    }

    while (usLen < *pusDstLen)
    {
        if (ucPreDfType == pucDstPath[usLen])
        {
            usLen += sizeof(VOS_UINT16);
            ucPreDfFlag = VOS_TRUE;
            break;
        }

        usLen += sizeof(VOS_UINT16);
    }

    if (VOS_FALSE == ucPreDfFlag)
    {
        /*lint -e534*/
        VOS_MemCpy(pucDstPath, pucSrcPath, usSrcLen);
        /*lint +e534*/
        *pusDstLen = usSrcLen;
    }
    else
    {
        if ((usSrcLen + usLen) > USIMM_MAX_PATH_LEN*2)
        {
            return VOS_ERR;
        }

        /*lint -e534*/
        VOS_MemCpy(pucDstPath+usLen, pucSrcPath, usSrcLen);
        /*lint +e534*/

        *pusDstLen = usSrcLen + usLen;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : USIMM_CardFilePathCMP
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 修改历史  : zhuli
             2010-03-19
*****************************************************************************/
VOS_UINT32 USIMM_CardFilePathCMP(VOS_UINT32 ulPath1Len, VOS_UINT16 *pusPath1,VOS_UINT32 ulPath2Len, VOS_UINT16 *pusPath2)
{
    if(ulPath2Len != ulPath1Len)
    {
        return VOS_ERR;
    }

    if(VOS_OK != VOS_MemCmp(pusPath1, pusPath2, ulPath1Len*sizeof(VOS_UINT16)))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_UsimFIDToIsimFID
功能描述  :将USIM的文件ID转换成ISIM的文件ID
输入参数  :usFileID--待转换文件ID
输出参数  :无
返 回 值  :转换后文件ID
           空
修订记录  :
1. 日    期   : 2013年7月22日
   作    者   : j00168360
   修改内容   : Creat

*****************************************************************************/
VOS_UINT16 USIMM_UsimEFIDToIsimEFID(VOS_UINT16 usFileID)
{
    VOS_UINT32                           i;

    /* 根据USIM文件ID查找对应的ISIM文件ID */
    for (i = 0; i < (sizeof(gastIsimUsimEFConTBL)/sizeof(USIMM_ISIM_USIM_CONVERSION_ST)); i++)
    {
        if (gastIsimUsimEFConTBL[i].usUsimEFID == usFileID)
        {
            return gastIsimUsimEFConTBL[i].usIsimEFID;
        }
    }

    /* 找不到则返回空 */
    return VOS_NULL_WORD;
}

/*****************************************************************************
函 数 名  :USIMM_IsimFIDToUsimFID
功能描述  :将ISIM的文件ID转换成USIM的文件ID
输入参数  :usFileID--待转换文件ID
输出参数  :无
返 回 值  :转换后文件ID
           空
修订记录  :
1. 日    期   : 2013年7月22日
   作    者   : j00168360
   修改内容   : Creat

*****************************************************************************/
VOS_UINT16 USIMM_IsimEFIDToUsimEFID(VOS_UINT16 usFileID)
{
    VOS_UINT32                           i;

    /* 根据ISIM文件ID查找对应的USIM文件ID */
    for (i = 0; i < sizeof(gastIsimToUsimEFTBL)/sizeof(USIMM_ISIM_USIM_CONVERSION_ST); i++)
    {
        if (gastIsimToUsimEFTBL[i].usIsimEFID == usFileID)
        {
            return gastIsimToUsimEFTBL[i].usUsimEFID;
        }
    }

    /* 找不到则返回空 */
    return VOS_NULL_WORD;
}

/*****************************************************************************
函 数 名  :SI_PIH_GetMncLen
功能描述  :获取MNC的长度
输入参数  :pucAdContent  -- AD文件内容
           ulFileSize    -- 文件内容
输出参数  :无
返 回 值  :MNC的长度
调用函数  :
修订记录  :
1. 日    期   : 2013年03月26日
   作    者   : g47350
   修改内容   : Creat
*****************************************************************************/
VOS_UINT8 USIMM_GetMncLen(VOS_UINT8 *pucAdContent, VOS_UINT32 ulFileSize)
{
    VOS_UINT8                           ucHplmnMncLen;

    ucHplmnMncLen = USIMM_MNC_TWO_BYTES_LEN;

    /* 文件大小过小，则默认MNC为2字节长度 */
    if(USIMM_EF_AD_MIN_LEN >= ulFileSize)
    {
        return ucHplmnMncLen;
    }

    /* 判断MNC长度,MNC可能为2位或3位 */
    if ((USIMM_MNC_TWO_BYTES_LEN == (pucAdContent[USIMM_AD_MNC_LEN_POS] & 0x0F))
        || (USIMM_MNC_THREE_BYTES_LEN == (pucAdContent[USIMM_AD_MNC_LEN_POS] & 0x0F)))
    {
        ucHplmnMncLen = pucAdContent[USIMM_AD_MNC_LEN_POS] & 0x0F;
    }

    return ucHplmnMncLen;
}

/*****************************************************************************
 函 数 名  : USIMM_BcdNumToAsciiNum
 功能描述  : BCD码转位ASCII码，代码来自NAS
 输入参数  : VOS_UINT8 *pucAsciiNum
             VOS_UINT8 *pucBcdNum
             VOS_UINT8 ucBcdNumLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月24日
    作    者   : j00168360
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID USIMM_BcdNumToAsciiNum(VOS_UINT8 *pucAsciiNum, VOS_UINT8 *pucBcdNum, VOS_UINT8 ucBcdNumLen)
{
    VOS_UINT8       ucTmp;
    VOS_UINT8       ucFirstNumber;
    VOS_UINT8       ucSecondNumber;

    for (ucTmp = 0; ucTmp < ucBcdNumLen; ucTmp++)
    {
        ucFirstNumber = (VOS_UINT8)((*(pucBcdNum + ucTmp)) & 0x0f);             /*low four bits*/
        ucSecondNumber = (VOS_UINT8)(((*(pucBcdNum + ucTmp)) >> 4) & 0x0f);   /*high four bits*/
        if(ucFirstNumber <= 9)
        {
            *pucAsciiNum = ucFirstNumber + 0x30;
            pucAsciiNum++;
        }
        else if(0xa == ucFirstNumber)            /* the key is '*' */
        {
            *pucAsciiNum = 0x2a;
            pucAsciiNum++;
        }
        else if(0xb == ucFirstNumber)            /* the key is '#' */
        {
            *pucAsciiNum = 0x23;
            pucAsciiNum++;
        }
        else                                     /* the key is 'a','b'or 'c' */
        {
            *pucAsciiNum = ucFirstNumber + 0x57;
            pucAsciiNum++;
        }

        /* the following proceed the second number */
        if(0xf == ucSecondNumber)
        {
            break;
        }
        if(ucSecondNumber <= 9)
        {
            *pucAsciiNum = ucSecondNumber + 0x30;
            pucAsciiNum++;
        }
        else if(0xa == ucSecondNumber)            /* the key is '*' */
        {
            *pucAsciiNum = 0x2a;
            pucAsciiNum++;
        }
        else if(0xb == ucSecondNumber)            /* the key is '#' */
        {
            *pucAsciiNum = 0x23;
            pucAsciiNum++;
        }
        else                                     /* the key is 'a','b'or 'c' */
        {
            *pucAsciiNum = ucSecondNumber + 0x57;
            pucAsciiNum++;
        }

    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_ImsiBcd2Ascii
功能描述  :解析IMSI
输入参数  :无
输出参数  :pucAsciiStr--解析结果
           pucAsciiLen -- Ascii长度

返 回 值  :无
调用函数  :
修订记录  :
1. 日    期   : 2013年07月26日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ImsiBcd2Ascii(VOS_UINT8 *pucAsciiStr)
{
    VOS_UINT32                          ulI = 0;
    VOS_UINT8                           ucTmp;
    VOS_UINT8                           aucImsi[USIMM_EF_IMSI_LEN];

    if (USIMM_API_SUCCESS != USIMM_GetCardIMSI(aucImsi))
    {
        USIMM_ERROR_LOG("USIMM_DecodeImsi: USIMM_GetCardIMSI fail.");
        return USIMM_SW_ERR;
    }

    /* 判断IMSI长度是否合法 */
    if (USIMM_IMSI_MAX_LEN < aucImsi[0])
    {
        USIMM_ERROR_LOG("USIMM_DecodeImsi: IMSI length is error.");
        return USIMM_SW_ERR;
    }

    /*国际移动用户识别码*/
    /*清空存放字符串的缓冲区*/
    for ( ulI = 0; ulI < (VOS_UINT32)(aucImsi[0]*2); ulI++ )
    {
        pucAsciiStr[ulI] = 0;
    }
    ucTmp = (aucImsi[1] >> 4) & 0x0f;

    /* 取出第一位BCD码进行转换 */
    USIMM_BcdNumToAsciiNum(pucAsciiStr, &ucTmp, 1);

    /* 将其余Bcd转换为Ascii码 */
    USIMM_BcdNumToAsciiNum(pucAsciiStr + 1, aucImsi + 2, (VOS_UINT8)((aucImsi[0]*2) - 1)/2);

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :USIMM_GetAsciiMCCAndMNC
功能描述  :根据ascii形式的IMSI获取ascii形式的MCC和MNC
输入参数  :pucAsciiImsi  -- ascii形式的IMSI
输出参数  :pucAsciiMCC -- ascii形式的MCC
           pucAsciiMNC -- ascii形式的MNC
返 回 值  :无
调用函数  :
修订记录  :
1. 日    期   : 2013年07月26日
   作    者   : j00168360
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_GetAsciiMCCAndMNC(VOS_UINT8 *pucAsciiImsi, VOS_UINT8 *pucAsciiMCC, VOS_UINT8 *pucAsciiMNC)
{
    VOS_UINT8                           ucMncLen;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           *pucData = VOS_NULL_PTR;

    /* 从AD文件中，获取HPLMN MNC长度 */
    if (USIMM_API_SUCCESS != USIMM_GetCachedFile(USIMM_USIM_EFAD_STR, &ulDataLen, &pucData, USIMM_GUTL_APP))
    {
       USIMM_ERROR_LOG("USIMM_DecodeImsi: USIMM_GetCachedFile fail.");
       return;
    }

    /* 获取MNC长度 */
    ucMncLen = USIMM_GetMncLen(pucData, ulDataLen);

    /* 获取MCC */
    pucAsciiMCC[0] = pucAsciiImsi[0];
    pucAsciiMCC[1] = pucAsciiImsi[1];
    pucAsciiMCC[2] = pucAsciiImsi[2];

    /* 获取MNC */
    if (USIMM_MNC_TWO_BYTES_LEN == ucMncLen)
    {
        pucAsciiMNC[0] = '0';
        pucAsciiMNC[1] = pucAsciiImsi[3];
        pucAsciiMNC[2] = pucAsciiImsi[4];
    }
    else
    {
        pucAsciiMNC[0] = pucAsciiImsi[3];
        pucAsciiMNC[1] = pucAsciiImsi[4];
        pucAsciiMNC[2] = pucAsciiImsi[5];
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_IsSIMServiceAvailable
功能描述  :获取SIM卡服务状态　
输入参数  :enService:服务ID
输出参数  :无
返 回 值  :PS_USIM_SERVICE_NOT_AVAILIABLE
           PS_USIM_SERVICE_NOT_AVAILIABLE
被调函数  :
修订记录  :
1. 日    期   : 2013年7月26日
   作    者   : g47350
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_IsSIMServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulFileNum;
    VOS_UINT8                           ucBitNo;

    if ((USIMM_CARD_SIM != gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
        || (USIMM_CARD_SERVIC_AVAILABLE != gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService))
    {
        USIMM_WARNING_LOG("USIMM_IsSIMServiceAvailable: The Card Type is Wrong");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    /* 查询当前的文件缓冲 */
    ulResult = USIMM_PoolFindFile(EFSST, &ulFileNum, USIMM_UNLIMIT_APP);

    if(ulResult != USIMM_API_SUCCESS)
    {
        USIMM_WARNING_LOG("USIMM_IsServiceAvailable: Read File is Failed");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    ucBitNo = (VOS_UINT8)((enService * 2) - 1);

    /* 获取缓冲的Bit信息 */
    ulResult = USIMM_GetBitFromBuf(gstUSIMMPOOL.astpoolRecord[ulFileNum].pucContent,
                                    ucBitNo,
                                    gstUSIMMPOOL.astpoolRecord[ulFileNum].usLen);

    /* SIM卡还判断ACTIVE位 */
    if (PS_USIM_SERVICE_AVAILIABLE == ulResult)
    {
        ulResult = USIMM_GetBitFromBuf(gstUSIMMPOOL.astpoolRecord[ulFileNum].pucContent,
                                        (ucBitNo+1),
                                        gstUSIMMPOOL.astpoolRecord[ulFileNum].usLen);
    }

    if(USIMM_BITNOFOUNE == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_IsServiceAvailable: The Service is Out of File");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_IsUSIMServiceAvailable
功能描述  :获取USIM卡服务状态　
输入参数  :enService:服务ID
输出参数  :无
返 回 值  :PS_USIM_SERVICE_NOT_AVAILIABLE
           PS_USIM_SERVICE_NOT_AVAILIABLE
被调函数  :
修订记录  :
1. 日    期   : 2013年7月26日
   作    者   : g47350
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_IsUSIMServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulFileNum;
    VOS_UINT8                           ucBitNo;

    if (((USIMM_CARD_USIM != gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
        && (USIMM_CARD_ROM_SIM != gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType))
        || (USIMM_CARD_SERVIC_AVAILABLE != gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService))
    {
        USIMM_WARNING_LOG("USIMM_IsUSIMServiceAvailable: The Card Type is Wrong");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    /* 查询当前的文件缓冲 */
    ulResult = USIMM_PoolFindFile(EFUST, &ulFileNum, USIMM_UNLIMIT_APP);

    if(ulResult != USIMM_API_SUCCESS)
    {
        USIMM_WARNING_LOG("USIMM_IsUSIMServiceAvailable: Read File is Failed");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    ucBitNo = (VOS_UINT8)((enService - SIM_SVR_BUTT) + 1);

    /* 获取缓冲的Bit信息 */
    ulResult = USIMM_GetBitFromBuf(gstUSIMMPOOL.astpoolRecord[ulFileNum].pucContent,
                                    ucBitNo,
                                    gstUSIMMPOOL.astpoolRecord[ulFileNum].usLen);

    if(USIMM_BITNOFOUNE == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_IsUSIMServiceAvailable: The Service is Out of File");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    return ulResult;

}

/*****************************************************************************
函 数 名  :USIMM_IsISIMServiceAvailable
功能描述  :获取ISIM卡服务状态　
输入参数  :enService:服务ID
输出参数  :无
返 回 值  :PS_USIM_SERVICE_NOT_AVAILIABLE
           PS_USIM_SERVICE_NOT_AVAILIABLE
被调函数  :
修订记录  :
1. 日    期   : 2013年7月26日
   作    者   : g47350
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_IsISIMServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucBitNo;

    /* 由于没有真实的ISIM卡需要读取USIM卡中的UST来实现 */
    if ((USIMM_CARD_ISIM != gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardType)
        || ((USIMM_CARD_SERVIC_AVAILABLE != gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardService)))
    {
        USIMM_WARNING_LOG("USIMM_IsISIMServiceAvailable: The Card Type is Wrong");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    /* SM-over-IP 对应了USIM上的两个服务项 */
    if (ISIM_SVR_SOI == enService)
    {
        ulResult = USIMM_IsUSIMServiceAvailable(USIM_SVR_DATA_DL_SMSPP);

        if (PS_USIM_SERVICE_NOT_AVAILIABLE == ulResult)
        {
            return PS_USIM_SERVICE_NOT_AVAILIABLE;
        }

        ulResult = USIMM_IsUSIMServiceAvailable(USIM_SVR_SM_VOER_IP);
    }
    else
    {
        /* 查找USIM上对应ISIM服务位位置 */
        ucBitNo = g_aucServIsimToUsim[enService - USIM_SVR_BUTT];

        /* 没有对应服务位则返回不支持 */
        if (0 == ucBitNo)
        {
            return PS_USIM_SERVICE_NOT_AVAILIABLE;
        }

        ulResult = USIMM_IsUSIMServiceAvailable(ucBitNo);
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_ReadFile
功能描述  :实现文件读取操作
输入参数  :enEFFileType -- 文件类型
           ucRecordNum -- 记录数
           usDataLen -- 更新数据长度
           pucData -- 更新数据
输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2013年07月23日
   作    者   : j00168360
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_ReadFile(USIMM_EFFCP_ST               *pstCurEFFcp,
                                 VOS_UINT8                   ucRecordNum,
                                 VOS_UINT16                  usDataLen,
                                 VOS_UINT8                   *pucData)
{
    VOS_UINT32                          ulResult;

    switch(pstCurEFFcp->enFileType)
    {
        case USIMM_EFSTRUCTURE_TRANSPARENT:       /*读取二进制文件*/
            ulResult = USIMM_ReadTFFile(usDataLen, pucData);
            break;

        case USIMM_EFSTRUCTURE_FIXED:                   /*读取记录文件*/
        case USIMM_EFSTRUCTURE_CYCLE:
            ulResult = USIMM_ReadLFFile(pstCurEFFcp, ucRecordNum, pucData);
            break;

        default:
            USIMM_WARNING_LOG("USIMM_GetFileHandle: The File Type is Not Support");
            ulResult = USIMM_SW_OTHER_ERROR;
            break;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_GetReadFilePara
功能描述  :获取读文件的参数
输入参数  :ucRecordNum -- 文件记录数
           pstMsg--指向读取文件消息结构
输出参数  :pstCnfInfo -- 指向回复消息结构
返 回 值  :VOS_ERR
           VOS_OK
修订记录  :
1. 日    期   : 2013年7月22日
   作    者   : j00168360
   修改内容   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_GetReadFilePara(VOS_UINT8 ucRecordNum, USIMM_EFFCP_ST *pstEFInfo, USIMM_GETCNF_INFO_STRU *pstCnfInfo)
{
    VOS_UINT32                          ulResult = USIMM_SW_OK;

    switch(pstEFInfo->enFileType)
    {
        case USIMM_EFSTRUCTURE_TRANSPARENT:       /*读取二进制文件*/
            pstCnfInfo->usDataLen   = (pstEFInfo->usFileLen > USIMM_MAX_FILE_SIZE) ? USIMM_MAX_FILE_SIZE : pstEFInfo->usFileLen;

            pstCnfInfo->usEfLen     = pstCnfInfo->usDataLen;                                /*读取长度和文件长度一致*/

            break;

        case USIMM_EFSTRUCTURE_FIXED:                   /*读取记录文件*/
        case USIMM_EFSTRUCTURE_CYCLE:
            if(ucRecordNum > pstEFInfo->ucRecordNum)/*检查读取的记录号是否越界*/
            {
                USIMM_ERROR_LOG("USIMM_GetReadFilePara: The Record Index is Out of the File Range");

                ulResult = USIMM_SW_OUTOF_RANGE;

                break;
            }

            pstCnfInfo->usEfLen = pstEFInfo->ucRecordLen;     /*即使读取全部记录也添为记录长度*/

            pstCnfInfo->ucRecordNum = ucRecordNum;

            if(USIMM_READ_ALLRECORD == ucRecordNum)
            {
                pstCnfInfo->ucTotalNum = pstEFInfo->ucRecordNum;

                pstCnfInfo->usDataLen  = pstEFInfo->usFileLen;
            }
            else
            {
                pstCnfInfo->ucTotalNum = 1;

                pstCnfInfo->usDataLen  = pstEFInfo->ucRecordLen;
            }

            break;

        default:
            USIMM_WARNING_LOG("USIMM_GetReadFilePara: The File Type is Not Support");

            ulResult = USIMM_SW_OTHER_ERROR;

            break;
    }

    return ulResult;
}

/*****************************************************************************
函 数 名  :USIMM_CardStatusRegCbFuncProc
功能描述  :SIM卡热插拨注册回调处理
输入参数  :无
输出参数  :无
返 回 值  :无
修订记录  :
1. 日    期   : 2013年9月25日
   作    者   : h59254
   修改内容   : Creat
*****************************************************************************/
VOS_VOID USIMM_CardStatusRegCbFuncProc(VOS_VOID)
{
    NVIM_USIM_CARD_STATUS_CB_TYPE_STRU  stType;

    if (NV_OK != NV_Read(en_NV_Item_Card_Status_Cb_Type, &stType, sizeof(NVIM_USIM_CARD_STATUS_CB_TYPE_STRU)))
    {
        stType.enType = USIMM_CARD_STATUS_REG_TYPE_M2M;
    }

    if (USIMM_CARD_STATUS_REG_TYPE_M2M == stType.enType)
    {
        mdrv_sci_register_callback(USIMM_SciCardStatusIndCbFunc);
    }
    else if (USIMM_CARD_STATUS_REG_TYPE_E5 == stType.enType)
    {
        mdrv_sci_register_callback(USIMM_SCICardOutNotify);
    }
    else
    {
        return;
    }

    return;
}

/*****************************************************************************
函 数 名  :USIMM_IsCLEnable
功能描述  :获取C+L功能设置标记状态
输入参数  :无
输出参数  :无
返 回 值  :VOS_FALSE/VOS_TRUE
修订记录  :
1. 日    期   : 2014年1月22日
   作    者   : z00100318
   修改内容   : Creat
*****************************************************************************/
VOS_BOOL USIMM_IsCLEnable(VOS_VOID)
{
    TAF_NV_LC_CTRL_PARA_STRU            stNVData;

    if (NV_OK != NV_Read(en_NV_Item_LC_Ctrl_PARA, &stNVData, sizeof(TAF_NV_LC_CTRL_PARA_STRU)))
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == stNVData.ucLCEnableFlg)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
函 数 名  :USIMM_GetRATMode
功能描述  :获取C+L 接入模式功能设置标记状态
输入参数  :无
输出参数  :无
返 回 值  :RAT_COMBINE_GUL/RAT_COMBINE_CL
修订记录  :
1. 日    期   : 2013年7月22日
   作    者   : j00168360
   修改内容   : Creat

*****************************************************************************/
TAF_NVIM_LC_RAT_COMBINED_ENUM_UINT8 USIMM_GetRATMode(VOS_VOID)
{

    TAF_NV_LC_CTRL_PARA_STRU    stNVData;

    if (NV_OK != NV_Read(en_NV_Item_LC_Ctrl_PARA, &stNVData, sizeof(TAF_NV_LC_CTRL_PARA_STRU)))
    {
        return TAF_NVIM_LC_RAT_COMBINED_GUL;
    }

    if ((TAF_NVIM_LC_RAT_COMBINED_CL == stNVData.enRatCombined)&&(VOS_TRUE == stNVData.ucLCEnableFlg))
    {
        return TAF_NVIM_LC_RAT_COMBINED_CL;
    }
    else
    {
        return TAF_NVIM_LC_RAT_COMBINED_GUL;
    }

}

/*****************************************************************************
 函 数 名  : USIMM_SetAccFileAccess
 功能描述  : 规避0x6F78 Acc文件接入权限为零的问题
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月30日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  USIMM_SetAccFileAccess( VOS_VOID )
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulRecordNum;
    VOS_UINT16                         *pusData;
    VOS_UINT32                          ulRandomNum;
    VOS_UINT8                           ucByteOffset;
    VOS_UINT8                           ucBitOffset;
    VOS_UINT8                           aucData[2] = {0,0};

    ulResult    =   USIMM_PoolFindFile(0x6F78, &ulRecordNum, USIMM_UNLIMIT_APP);

    if(VOS_ERR == ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SetRandomAccess: File Could not Found");/*打印错误*/

        return;
    }

    if(VOS_NULL_PTR == gstUSIMMPOOL.astpoolRecord[ulRecordNum].pucContent)
    {
        USIMM_ERROR_LOG("USIMM_SetRandomAccess: File Content is Empty");/*打印错误*/

        return;
    }

    pusData = (VOS_UINT16 *)gstUSIMMPOOL.astpoolRecord[ulRecordNum].pucContent;

    if (VOS_NULL == *pusData)
    {
        ulRandomNum = (VOS_UINT32)VOS_Rand(10);

        ulRandomNum = ulRandomNum % 10;

        ucByteOffset    = (ulRandomNum < 8)?1:0;
        ucBitOffset     = ulRandomNum % 8;

        /*lint -e701*/
        aucData[ucByteOffset] |= (VOS_UINT8)(1<<ucBitOffset);
        /*lint +e701*/

        /*lint -e534*/
        VOS_MemCpy(pusData, aucData, sizeof(VOS_UINT16));
        /*lint +e534*/
    }

    return;
}

/*****************************************************************************
 函 数 名  : USIMM_SetImsiFile
 功能描述  : USIMM模块规避IMSI文件第一个字节为全FF的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月11日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID USIMM_SetImsiFile(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulRecordNum;
    VOS_UINT8                          *pucData;
    VOS_UINT8                           aucFirstByte;

    ulResult    =   USIMM_PoolFindFile(0x6F07, &ulRecordNum, USIMM_UNLIMIT_APP);

    if (VOS_ERR == ulResult)
    {
        USIMM_ERROR_LOG("USIMM_FileImsiAccessFix: File Could not Found");/*打印错误*/

#if(FEATURE_ON == FEATURE_PTM)
        USIMM_RecordCardErrorLog(USIMM_MNTN_MODULE_INIT,
                                USIMM_MNTN_INIT_IMSIFAIL,
                                VOS_NULL,
                                VOS_NULL,
                                USIMM_MNTN_ERROR_LEVEL_CRITICAL);
#endif

        return;
    }

    if(VOS_NULL_PTR == gstUSIMMPOOL.astpoolRecord[ulRecordNum].pucContent)
    {
        USIMM_ERROR_LOG("USIMM_SetRandomAccess: File Content is Empty");/*打印错误*/

        return;
    }

    pucData = gstUSIMMPOOL.astpoolRecord[ulRecordNum].pucContent;

    aucFirstByte = pucData[0];

    if (VOS_NULL_BYTE == aucFirstByte)
    {
        pucData[0] = 0x08;
    }

    return;
}

/*****************************************************************************
 函 数 名  : USIMM_FileAccessFix
 功能描述  : USIMM模块内文件处理规避入口
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月2日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID USIMM_FileAccessFix( VOS_VOID )
{
    USIMM_SetAccFileAccess();

    USIMM_SetImsiFile();

    return;
}

/*****************************************************************************
函 数 名  :USIMM_IS_EF_FILE
功能描述  :USIMM判断当前是否是DF
输入参数  :usFileId:文件ID
输出参数  :无
返 回 值  :VOS_TRUE/VOS_FALSE
修订记录  :
1. 日    期   : 2015年5月12日
   作    者   : H00300778
   修改内容   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_IS_EF_FILE(VOS_UINT16 usFileId)
{
    if (USIMM_EF_FILE == ((usFileId>>0x0C)&0x01))
    {
        return VOS_TRUE;
    }
    else if ((VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulPKCS15)
          && ((0x5031 == usFileId)
           || (0x5027 == usFileId)
           || (0x5006 == usFileId)
           || (0x5003 == usFileId)
           || (0x2003 == usFileId)
           || (0x5032 == usFileId)
           || (0x5207 == usFileId)))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
函 数 名  :USIMM_CheckSupportAP
功能描述  :判断当前是否支持AP
输入参数  :无
输出参数  :无
返 回 值  :VOS_TRUE/VOS_FALSE
调用函数  : GetProductType
被调函数  : 外部接口
History     :
1.日    期  : 2014年10月09日
  作    者  : z00100318
  修改内容  : Create
*****************************************************************************/
VOS_BOOL USIMM_CheckSupportAP(VOS_VOID)
{
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU stAPPConfig;

    if(NV_OK != NV_Read(en_NV_Item_System_APP_Config, &stAPPConfig, sizeof(VOS_UINT16)))
    {
        USIMM_ERROR_LOG("SI_STK_CheckSupportAP: Read en_NV_Item_System_APP_Config Failed");

        return VOS_FALSE;
    }

    if(SYSTEM_APP_ANDROID == stAPPConfig.usSysAppConfigType)
    {
        USIMM_NORMAL_LOG("SI_STK_CheckSupportAP: System App is Android");

        return VOS_TRUE;
    }

    USIMM_NORMAL_LOG("SI_STK_CheckSupportAP: System App is other");

    return VOS_FALSE;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

