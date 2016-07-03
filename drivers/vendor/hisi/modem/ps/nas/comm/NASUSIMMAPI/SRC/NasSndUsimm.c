

/*****************************************************************************
  头文件包含
*****************************************************************************/
#include "NasMntn.h"
#include "NasUsimmApiMntn.h"
#include "NasSndUsimm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID PS_FILE_ID_NAS_SNDUSIMM_C

/*****************************************************************************
  函数声明
*****************************************************************************/


/*****************************************************************************
  变量定义
*****************************************************************************/
NAS_USIMM_SVLTE_TYPE_ENUM_UINT8         g_enSvlteSupportFlg = NAS_USIMM_SVLTE_TYPE_BUTT;

/*****************************************************************************
  函数定义
*****************************************************************************/

VOS_VOID NAS_SNDUSIMM_SetSvlteSupportFlag(
    NAS_USIMM_SVLTE_TYPE_ENUM_UINT8     enSvlteSupportFlag
)
{
    g_enSvlteSupportFlg = enSvlteSupportFlag;

    return;
}


VOS_VOID NAS_SNDUSIMM_ReadSvlteSupportFlagNvim(
    VOS_VOID
)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    SVLTE_SUPPORT_FLAG_STRU             stSvlteSupportFlag;

    PS_MEM_SET(&stSvlteSupportFlag, 0x00, sizeof(stSvlteSupportFlag));

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_SVLTE_FLAG,
                         &stSvlteSupportFlag,
                         sizeof(SVLTE_SUPPORT_FLAG_STRU)))
    {
        return;
    }

    if (VOS_TRUE == stSvlteSupportFlag.ucSvlteSupportFlag)
    {
        NAS_SNDUSIMM_SetSvlteSupportFlag(NAS_USIMM_SVLTE_TYPE_SUPPORT);

        return;
    }

    NAS_SNDUSIMM_SetSvlteSupportFlag(NAS_USIMM_SVLTE_TYPE_NOT_SUPPORT);
#endif

    NAS_INFO_LOG(WUEPS_PID_MMA, "NAS_SNDUSIMM_ReadSvlteSupportFlagNvim is Called.");

    return;
}


NAS_USIMM_SVLTE_TYPE_ENUM_UINT8 NAS_SNDUSIMM_GetSvlteSupportFlag(
    VOS_VOID
)
{
    return g_enSvlteSupportFlg;
}


VOS_UINT32 NAS_SNDUSIMM_IsSvlteSupported(
    VOS_VOID
)
{
    if (NAS_USIMM_SVLTE_TYPE_BUTT == NAS_SNDUSIMM_GetSvlteSupportFlag())
    {
        NAS_SNDUSIMM_ReadSvlteSupportFlagNvim();
    }

    if (NAS_USIMM_SVLTE_TYPE_SUPPORT == NAS_SNDUSIMM_GetSvlteSupportFlag())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 NAS_SNDUSIMM_IsCdmaPid(
    VOS_UINT32                          ulSenderPid
)
{
    if (UEPS_PID_XSD == ulSenderPid)
    {
        return VOS_TRUE;
    }

    if (UEPS_PID_XREG == ulSenderPid)
    {
        return VOS_TRUE;
    }

    if (UEPS_PID_XCC == ulSenderPid)
    {
        return VOS_TRUE;
    }

    if (UEPS_PID_HSD == ulSenderPid)
    {
        return VOS_TRUE;
    }

    if (UEPS_PID_HSM == ulSenderPid)
    {
        return VOS_TRUE;
    }

    if (UEPS_PID_EHSM == ulSenderPid)
    {
        return VOS_TRUE;
    }

    if (UEPS_PID_HLU == ulSenderPid)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_SNDUSIMM_IsModem0SupportC(VOS_VOID)
{
    PLATAFORM_RAT_CAPABILITY_STRU       stModem0PlatRat;
    VOS_UINT16                          i;

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Platform_RAT_CAP, &stModem0PlatRat,
                              sizeof(PLATAFORM_RAT_CAPABILITY_STRU)))
    {
        NAS_TRACE_HIGH("NAS_SNDUSIMM_IsModem0SupportC read NV en_NV_Item_Platform_RAT_CAP failed!\r\n");
        return VOS_FALSE;
    }

    for (i = 0; i < stModem0PlatRat.usRatNum; i++)
    {
        if (PLATFORM_RAT_1X == stModem0PlatRat.aenRatList[i])
        {
            return VOS_TRUE;
        }

        if (PLATFORM_RAT_HRPD == stModem0PlatRat.aenRatList[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif


VOS_UINT32 NAS_SNDUSIMM_GetReceiverPid(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulModem0ReceiverID,
    VOS_UINT32                          ulModem1ReceiverID,
    VOS_UINT32                          ulModem2ReceiverID
)
{
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = 0;

    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        /* 如果支持Svlte，返回Modem0对应的ReceiverPid */
        return ulModem0ReceiverID;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == NAS_SNDUSIMM_IsCdmaPid(ulSenderPid))
    {
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
        if (VOS_TRUE == NAS_SNDUSIMM_IsModem0SupportC())
        {
            return ulModem0ReceiverID;
        }
        else
        {
            return ulModem1ReceiverID;
        }
#else
        return ulModem0ReceiverID;
#endif
    }
#endif

    /* 如果不支持，根据SenderPid获取ModemId */
    enModemId = VOS_GetModemIDFromPid(ulSenderPid);

    if (MODEM_ID_0 == enModemId)
    {
        return ulModem0ReceiverID;
    }

    if (MODEM_ID_1 == enModemId)
    {
        return ulModem1ReceiverID;
    }

    if (MODEM_ID_2 == enModemId)
    {
        return ulModem2ReceiverID;
    }

    return RECEIVERID_NOT_FOUND;
}


VOS_UINT32 NAS_SndUsimmUpdateFileReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    NAS_USIMM_UPDATEFILE_DATA_STRU     *pstSetFileInfo
)
{
    USIMM_UPDATEFILE_REQ_STRU          *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_CHAR                           *pucFilePathStr  = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;
    VOS_UINT32                          ulPathLength;

    /* 初始化 */
    ulReceiverPid   = 0;
    ulMsgLength     = 0;
    ulPathLength    = 0;

    /* 参数检查 */
    if (VOS_NULL_PTR == pstSetFileInfo)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmUpdateFileReq: pstSetFileInfo Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    if ((pstSetFileInfo->ulEfLen > MAX_FILE_LENGTH)
        || (pstSetFileInfo->ulEfLen < MIN_FILE_LENGTH))
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmUpdateFileReq: File Length Not In [1,65535].");

        return USIMM_API_WRONG_PARA;
    }

    /* 获取ReceiverPid */
    ulReceiverPid = NAS_SNDUSIMM_GetReceiverPid(ulSenderPid,
                                                I0_WUEPS_PID_USIM,
                                                I1_WUEPS_PID_USIM,
                                                I2_WUEPS_PID_USIM);
    if (RECEIVERID_NOT_FOUND == ulReceiverPid)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmUpdateFileReq: Get ReceiverPid Failed.");

        return USIMM_API_WRONG_PARA;
    }

    /* 文件Id转文件路径 */
    if (VOS_OK != USIMM_ChangeDefFileToPath(pstSetFileInfo->usEfId, &pucFilePathStr))
    {
        return USIMM_API_WRONG_PARA;
    }

    /* 文件路径长度保护 */
    ulPathLength = VOS_StrLen(pucFilePathStr);
    if (0 == ulPathLength)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmUpdateFileReq: File Path Str Error.");

        return USIMM_API_WRONG_PARA;
    }


    /* 分配消息内存并初始化 */
    ulMsgLength = (sizeof(USIMM_UPDATEFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH)
                + (pstSetFileInfo->ulEfLen - NAS_USIMM_UPDATEFILE_STRU_ARRAY_LENGTH * sizeof(VOS_UINT8));
    pstMsg = (USIMM_UPDATEFILE_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmUpdateFileReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* 填写消息头 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulSenderPid;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = ulReceiverPid;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;
    pstMsg->stMsgHeader.enMsgName       = USIMM_UPDATEFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = pstSetFileInfo->enAppType;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;

    /* 填写消息体 */
    pstMsg->stFilePath.ulPathLen        = ulPathLength;
    PS_MEM_CPY(pstMsg->stFilePath.acPath, pucFilePathStr, pstMsg->stFilePath.ulPathLen + 1);
    pstMsg->usDataLen                   = (VOS_UINT16)pstSetFileInfo->ulEfLen;
    pstMsg->ucRecordNum                 = pstSetFileInfo->ucRecordNum;
    PS_MEM_CPY(pstMsg->aucContent, pstSetFileInfo->pucEfContent, pstSetFileInfo->ulEfLen);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}


VOS_UINT32 NAS_SndUsimmReadFileReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    NAS_USIMM_GETFILE_DATA_STRU        *pstGetFileInfo
)
{
    USIMM_READFILE_REQ_STRU            *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_CHAR                           *pucFilePathStr  = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;
    VOS_UINT32                          ulPathLength;

    /* 初始化 */
    ulReceiverPid   = 0;
    ulMsgLength     = 0;
    ulPathLength    = 0;

    /* 参数检查 */
    if (VOS_NULL_PTR == pstGetFileInfo)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmGetAppFileReq: pstGetFileInfo Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* 获取ReceiverPid */
    ulReceiverPid = NAS_SNDUSIMM_GetReceiverPid(ulSenderPid,
                                                I0_WUEPS_PID_USIM,
                                                I1_WUEPS_PID_USIM,
                                                I2_WUEPS_PID_USIM);
    if (RECEIVERID_NOT_FOUND == ulReceiverPid)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmGetAppFileReq: Get ReceiverPid Failed.");

        return USIMM_API_WRONG_PARA;
    }

    /* 文件Id转文件路径 */
    if (VOS_OK != USIMM_ChangeDefFileToPath(pstGetFileInfo->usEfId, &pucFilePathStr))
    {
        return USIMM_API_WRONG_PARA;
    }

    /* 文件路径长度保护 */
    ulPathLength = VOS_StrLen(pucFilePathStr);
    if (0 == ulPathLength)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmUpdateFileReq: File Path Str Error.");

        return USIMM_API_WRONG_PARA;
    }

    /* 分配消息内存并初始化 */
    ulMsgLength = sizeof(USIMM_READFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (USIMM_READFILE_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmGetAppFileReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* 填写消息头 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulSenderPid;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = ulReceiverPid;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;
    pstMsg->stMsgHeader.enMsgName       = USIMM_READFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = pstGetFileInfo->enAppType;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;

    /* 填写消息体 */
    pstMsg->stFilePath.ulPathLen        = ulPathLength;
    pstMsg->bNeedReadCache              = VOS_TRUE;
    pstMsg->ucRecordNum                 = pstGetFileInfo->ucRecordNum;
    PS_MEM_CPY(pstMsg->stFilePath.acPath, pucFilePathStr, pstMsg->stFilePath.ulPathLen + 1);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}


VOS_UINT32 NAS_SndUsimmAuthReq(
    VOS_UINT32                          ulSenderPid,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    NAS_USIMM_AUTH_DATA_STRU           *pstAuth,
    VOS_UINT8                           ucOpId
)
{
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulMsgLength;

    /* 初始化 */
    ulReceiverPid   = 0;
    ulMsgLength     = 0;

    /* 参数检查 */
    if (VOS_NULL_PTR == pstAuth)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmAuthReq: pstAuth Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* 获取ReceiverPid */
    ulReceiverPid = NAS_SNDUSIMM_GetReceiverPid(ulSenderPid,
                                                I0_WUEPS_PID_USIM,
                                                I1_WUEPS_PID_USIM,
                                                I2_WUEPS_PID_USIM);
    if (RECEIVERID_NOT_FOUND == ulReceiverPid)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmAuthReq: Get ReceiverPid Failed.");

        return USIMM_API_WRONG_PARA;
    }

    /* 分配消息内存并初始化 */
    ulMsgLength = sizeof(USIMM_AUTHENTICATION_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (USIMM_AUTHENTICATION_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmAuthReq: Allocate Msg Failed");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* 填写消息头 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulSenderPid;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = ulReceiverPid;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;

    pstMsg->stMsgHeader.enMsgName       = USIMM_AUTHENTICATION_REQ;
    pstMsg->stMsgHeader.ulSendPara      = ucOpId;
    pstMsg->stMsgHeader.enAppType       = enAppType;

    /* 填写消息体 */

    pstMsg->enAuthType                  = pstAuth->enAuthType;
    PS_MEM_CPY(&(pstMsg->uAuth), &(pstAuth->unAuthPara), sizeof(pstAuth->unAuthPara));

    /* 调用VOS发送原语 */
    PS_SEND_URGENT_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}


VOS_UINT32 NAS_SndUsimmPinReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT8                           ucCmdType,
    VOS_UINT8                           ucPINType,
    VOS_UINT8                          *pucOldPIN,
    VOS_UINT8                          *pucNewPIN
)
{
    USIMM_PINHANDLE_REQ_STRU           *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT32                          ulMsgLength;

    /* 初始化 */
    ulReceiverPid   = 0;
    enAppType       = USIMM_GUTL_APP;
    ulMsgLength     = 0;

    /* 参数检查 */
    if (VOS_NULL_PTR == pucOldPIN)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmPinReq: pucOldPIN Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* 获取ReceiverPid */
    ulReceiverPid = NAS_SNDUSIMM_GetReceiverPid(ulSenderPid,
                                                I0_WUEPS_PID_USIM,
                                                I1_WUEPS_PID_USIM,
                                                I2_WUEPS_PID_USIM);
    if (RECEIVERID_NOT_FOUND == ulReceiverPid)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmPinReq: Get ReceiverPid Failed.");

        return USIMM_API_WRONG_PARA;
    }

    /* 分配消息内存并初始化 */
    ulMsgLength = sizeof(USIMM_PINHANDLE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (USIMM_PINHANDLE_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmPinReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* 填写消息头 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulSenderPid;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = ulReceiverPid;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;

    pstMsg->stMsgHeader.enMsgName       = USIMM_PINHANDLE_REQ;
    pstMsg->stMsgHeader.enAppType       = enAppType;
    pstMsg->stMsgHeader.ulSendPara      = 0;            /* 预留参数 */

    /* 填写消息体 */
    pstMsg->enCmdType                   = ucCmdType;
    pstMsg->enPINType                   = ucPINType;
    PS_MEM_CPY(pstMsg->aucOldPIN, pucOldPIN, USIMM_PINNUMBER_LEN);

    if (VOS_NULL_PTR != pucNewPIN)
    {
        PS_MEM_CPY(pstMsg->aucNewPIN, pucNewPIN, USIMM_PINNUMBER_LEN);
    }

    /* 调用VOS发送原语 */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}


VOS_UINT32 NAS_SndUsimmFdnNumCheckReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulContextIndex,
    VOS_UINT32                          ulSendPara,
    SI_PB_FDN_NUM_STRU                 *pstFdnInfo
)
{
    SI_PB_FDN_CHECK_REQ_STRU           *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulMsgLength;

    /* 初始化 */
    ulReceiverPid   = 0;
    ulMsgLength     = 0;

    /* 参数检查 */
    if (VOS_NULL_PTR == pstFdnInfo)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmFdnNumCheckReq: pstFdnInfo Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* 获取ReceiverPid */
    ulReceiverPid = NAS_SNDUSIMM_GetReceiverPid(ulSenderPid,
                                                I0_MAPS_PB_PID,
                                                I1_MAPS_PB_PID,
                                                I2_MAPS_PB_PID);
    if (RECEIVERID_NOT_FOUND == ulReceiverPid)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmFdnNumCheckReq: Get ReceiverPid Failed.");

        return USIMM_API_WRONG_PARA;
    }

    /* 分配消息内存并初始化 */
    ulMsgLength = sizeof(SI_PB_FDN_CHECK_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (SI_PB_FDN_CHECK_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmFdnNumCheckReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* 填写消息头 */
    pstMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulLength            = ulMsgLength;

    /* 填写消息体 */
    pstMsg->ulMsgName           = SI_PB_FDN_CHECK_REQ;
    pstMsg->enAppType           = USIMM_GUTL_APP;
    pstMsg->ulSendPara          = ulSendPara;
    pstMsg->ulContextIndex      = ulContextIndex;
    PS_MEM_CPY(&(pstMsg->stFDNNum), pstFdnInfo, sizeof(SI_PB_FDN_NUM_STRU));

    /* 调用VOS发送原语 */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}


VOS_UINT32 NAS_SndUsimmQueryFileReq(
    VOS_UINT32                          ulSenderPid,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usEFid
)
{
    USIMM_QUERYFILE_REQ_STRU           *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_CHAR                           *pucFilePathStr  = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;
    VOS_UINT32                          ulPathLength;

    /* 初始化 */
    ulReceiverPid   = 0;
    ulMsgLength     = 0;
    ulPathLength    = 0;

    /* 获取ReceiverPid */
    ulReceiverPid = NAS_SNDUSIMM_GetReceiverPid(ulSenderPid,
                                                I0_WUEPS_PID_USIM,
                                                I1_WUEPS_PID_USIM,
                                                I2_WUEPS_PID_USIM);
    if (RECEIVERID_NOT_FOUND == ulReceiverPid)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmQueryFileReq: Get ReceiverPid Failed.");

        return USIMM_API_WRONG_PARA;
    }

    /* 文件Id转文件路径 */
    if (VOS_OK != USIMM_ChangeDefFileToPath(usEFid, &pucFilePathStr))
    {
        return USIMM_API_WRONG_PARA;
    }

    /* 文件路径长度保护 */
    ulPathLength = VOS_StrLen(pucFilePathStr);
    if (0 == ulPathLength)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmUpdateFileReq: File Path Str Error.");

        return USIMM_API_WRONG_PARA;
    }

    /* 分配消息内存并初始化 */
    ulMsgLength = sizeof(USIMM_QUERYFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (USIMM_QUERYFILE_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmQueryFileReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* 填写消息头 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulSenderPid;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = ulReceiverPid;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;

    pstMsg->stMsgHeader.enMsgName       = USIMM_QUERYFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = enAppType;
    pstMsg->stMsgHeader.ulSendPara      = 0;                /* 预留参数 */

    /* 填写消息体 */
    pstMsg->stFilePath.ulPathLen        = ulPathLength;
    PS_MEM_CPY(pstMsg->stFilePath.acPath, pucFilePathStr, pstMsg->stFilePath.ulPathLen + 1);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}


VOS_UINT32 NAS_SndUsimmDeactiveCardReq(
    VOS_UINT32                          ulSenderPid
)
{
    USIMM_DEACTIVECARD_REQ_STRU        *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    /* 初始化 */
    ulMsgLength     = 0;

    /* 分配消息内存并初始化 */
    ulMsgLength = sizeof(USIMM_DEACTIVECARD_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (USIMM_DEACTIVECARD_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmDeactiveCardReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* 填写消息头 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulSenderPid;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;

    pstMsg->stMsgHeader.enMsgName       = USIMM_DEACTIVECARD_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulSendPara      = 0;                /* 预留参数 */

    /* 调用VOS发送原语 */
    PS_SEND_URGENT_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}


VOS_UINT32 NAS_SndUsimmEcallNumberQry(
    VOS_UINT32                          ulSenderPid,
    SI_PB_STORAGE_ENUM_UINT32           enStorage,
    VOS_UINT8                           ucListLen,
    VOS_UINT8                          *pucList
)
{
    SI_PB_ECALLQRY_REQ_STRU            *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    /* 初始化 */
    ulMsgLength     = 0;

    /* 参数检查 */
    if (VOS_NULL_PTR == pucList)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmEcallNumberQry: pucList Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* 分配消息内存并初始化 */
    ulMsgLength = (sizeof(SI_PB_ECALLQRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH)
                    + (ucListLen - NAS_SI_PB_ECALLQRY_REQ_STRU_ARRAY_LENGTH * sizeof(VOS_UINT8));
    pstMsg = (SI_PB_ECALLQRY_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmEcallNumberQry: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* 填写消息头 */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = ulSenderPid;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = MAPS_PB_PID;
    pstMsg->ulLength        = ulMsgLength;

    /* 填写消息体 */
    pstMsg->ulMsgName       = SI_PB_ECALL_QRY_REQ;
    pstMsg->enAppType       = USIMM_GUTL_APP;
    pstMsg->enStorage       = enStorage;
    pstMsg->ucListLen       = ucListLen;
    PS_MEM_CPY(pstMsg->aucList, pucList, ucListLen);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}


VOS_UINT32 NAS_SndUsimmEnvelopeDownloadReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    SI_STK_ENVELOPE_STRU               *pstENStru
)
{
    SI_STK_ENVELOPEDOWN_REQ_STRU       *pstMsg          = VOS_NULL_PTR;
    VOS_UINT8                           aucEvent[MAX_VALUE_OF_ONE_BYTE + 1];
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulMsgLength;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulOffSet;
    VOS_UINT32                          ulRslt;


    /* 初始化 */
    ulReceiverPid   = 0;
    ulMsgLength     = 0;
    ulDataLen       = 0;
    ulOffSet        = 0;
    ulRslt          = 0;
    PS_MEM_SET(aucEvent, 0x00, sizeof(aucEvent));

    /* 参数检查 */
    if (VOS_NULL_PTR == pstENStru)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmEnvelopeDownloadReq: pstENStru Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* 获取ReceiverPid */
    ulReceiverPid = NAS_SNDUSIMM_GetReceiverPid(ulSenderPid,
                                                I0_MAPS_STK_PID,
                                                I1_MAPS_STK_PID,
                                                I2_MAPS_STK_PID);
    if (RECEIVERID_NOT_FOUND == ulReceiverPid)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmEnvelopeDownloadReq: Get ReceiverPid Failed.");

        return USIMM_API_WRONG_PARA;
    }

    /* Envelope 类型检查 */
    if ((SI_STK_ENVELOPE_MENUSEL == pstENStru->enEnvelopeType)
        || (SI_STK_PROCMD == pstENStru->enEnvelopeType))
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmEnvelopeDownloadReq: The Input EnvelopeType Is Error");

        return USIMM_API_FAILED;
    }

    /* 数据重新编码存放到数组中 */
    ulRslt = SI_STK_EnvelopeData_Code(pstENStru, &ulDataLen, aucEvent, &ulOffSet);

    if (VOS_ERR == ulRslt)
    {
        NAS_LogStkApiEnvelopReqCode(ulRslt, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, aucEvent, ulDataLen, ulOffSet);

        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmEnvelopeDownloadReq: The SI_STK_EnvelopeData_Code Is Error");

        return USIMM_API_FAILED;
    }

    NAS_LogStkApiEnvelopReqCode(ulRslt, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, aucEvent, ulDataLen, ulOffSet);

    /* 保护外部API输出 */
    if (ulDataLen > SI_STK_DATA_MAX_LEN)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmEnvelopeDownloadReq: The SI_STK_EnvelopeData_Code ulDataLen > 256");

        return USIMM_API_FAILED;
    }

    /* 分配消息内存并初始化 */
    ulMsgLength = sizeof(SI_STK_ENVELOPEDOWN_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (SI_STK_ENVELOPEDOWN_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmEnvelopeDownloadReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* 填写消息头 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulReceiverPid;            /* USIMM 要求此消息SenderPid = ReceiverPid*/
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = ulReceiverPid;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;

    pstMsg->stMsgHeader.enMsgName       = SI_STK_ENVELOPEDWON_REQ;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;
    pstMsg->stMsgHeader.ucOpID          = VOS_NULL;
    pstMsg->stMsgHeader.usATClient      = VOS_NULL;

    /* 填写消息体 */
    pstMsg->bTransFlag                  = NAS_SI_STK_ENVELOPEDOWN_ENCODE;
    pstMsg->enEnvelopeType              = pstENStru->enEnvelopeType;
    pstMsg->stEnvelopeData.ulDataLen    = ulDataLen;
    PS_MEM_CPY(pstMsg->stEnvelopeData.aucData, &aucEvent[ulOffSet], ulDataLen);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}


VOS_UINT32 NAS_SndUsimmRestrictedAccessReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    USIMM_RACCESS_REQ_STRU             *pstData
)
{
    USIMM_RACCESS_REQ_STRU             *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    /* 初始化 */
    ulMsgLength     = 0;

    /* 参数检查 */
    if (VOS_NULL_PTR == pstData)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmRestrictedAccessReq: pstENStru Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* 分配消息内存并初始化 */
    ulMsgLength = sizeof(USIMM_RACCESS_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (USIMM_RACCESS_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmRestrictedAccessReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* 填写消息头 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulSenderPid;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;

    pstMsg->stMsgHeader.enMsgName       = USIMM_RACCESS_REQ;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;

    /* 填写消息体 */
    pstMsg->enCmdType                   = pstData->enCmdType;
    pstMsg->ucP1                        = pstData->ucP1;
    pstMsg->ucP2                        = pstData->ucP2;
    pstMsg->ucP3                        = pstData->ucP3;
    pstMsg->usEfId                      = pstData->usEfId;

    /* 拷贝文件路径 */
    pstMsg->usPathLen                   = ((pstData->usPathLen > USIMM_MAX_PATH_LEN)?\
                                          USIMM_MAX_PATH_LEN:pstData->usPathLen);

    /* 文件路径长度是U16为单位的，路径拷贝的长度要乘2 */
    PS_MEM_CPY(pstMsg->ausPath, pstData->ausPath, (pstMsg->usPathLen) * sizeof(VOS_UINT16));

    /* 根据P3参数拷贝<DATA>字段 */
    PS_MEM_CPY(pstMsg->aucContent, pstData->aucContent, pstData->ucP3);

    /* 调用VOS发送原语 */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}


VOS_UINT32 NAS_SndUsimmRefreshReq(
    VOS_UINT32                          ulSenderPid,
    USIMM_STK_COMMAND_DETAILS_STRU     *pstCMDDetail,
    USIMM_RESET_INFO_STRU              *pstRstInfo
)
{
    USIMM_STKREFRESH_REQ_STRU          *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    /* 初始化 */
    ulMsgLength     = 0;

    /* 参数检查 */
    if (VOS_NULL_PTR == pstCMDDetail)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmRefreshReq: pstCMDDetail Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    if (VOS_NULL_PTR == pstRstInfo)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmRefreshReq: pstRstInfo Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* 分配消息内存并初始化 */
    ulMsgLength = sizeof(USIMM_STKREFRESH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (USIMM_STKREFRESH_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmRefreshReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* 填写消息头 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulSenderPid;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;

    pstMsg->stMsgHeader.enMsgName       = USIMM_STKREFRESH_REQ;
    pstMsg->stMsgHeader.ulSendPara      = 0;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;

    /* 填写消息体 */
    pstMsg->ulCommandNum                = pstCMDDetail->ucCommandNum;
    pstMsg->ulCommandType               = pstCMDDetail->ucCommandType;
    pstMsg->enRefreshType               = pstCMDDetail->ucCommandQua;

    if (USIMM_AID_LEN_MAX < pstRstInfo->usAidLen)
    {
        pstMsg->ulAidLen = USIMM_AID_LEN_MAX;
    }
    else
    {
        pstMsg->ulAidLen = pstRstInfo->usAidLen;
    }

    if (VOS_NULL != pstMsg->ulAidLen)
    {
        (VOS_VOID)VOS_MemCpy(pstMsg->aucAid, pstRstInfo->aucAid, pstMsg->ulAidLen);
    }

    pstMsg->usLen = pstRstInfo->usFileListLen;

    if (VOS_NULL != pstRstInfo->usFileListLen)
    {
        PS_MEM_CPY(pstMsg->aucFileList, pstRstInfo->aucFileList, pstRstInfo->usFileListLen);
    }

    /* 调用VOS发送原语 */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

