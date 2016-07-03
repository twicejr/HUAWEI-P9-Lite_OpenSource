

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafCbaProcUsim.h"
#include  "TafCbaMntn.h"
#include  "TafCbaComFunc.h"
#include  "TafCbaProcNvim.h"

#include  "UsimPsInterface.h"
#include  "MnMsgSmCommProc.h"
#include  "MnComm.h"
#include  "MnMsgTimerProc.h"
#include  "TafCbsInterface.h"
#include  "TafLog.h"

#include "NasUsimmApi.h"

#include "TafSdcCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_USIM_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/


/* Deleted TAF_CBA_ProcUsimGetFileRsp */
/* Deleted TAF_CBA_SndUsimGetFileReq */
/* Deleted TAF_CBA_RcvUsimGetEfCbmiRsp TAF_CBA_RcvUsimGetEfCbmirRsp TAF_CBA_RcvUsimGetEfCbmidRsp */


VOS_VOID TAF_CBA_ParseUsimFileEfCbmiData(
    VOS_UINT8                           ucEfCbmiExistFlg,
    VOS_UINT8                          *pucEf,
    VOS_UINT16                          usEfLen
)
{
    TAF_CBA_USIM_EFCBMI_FILE_INFO_STRU *pstEfCbmiFileInfo;
    VOS_UINT32                          ulLoop;
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmRangeids;
    VOS_UINT8                           ucMsgIdHigh;
    VOS_UINT8                           ucMsgIdLow;
    VOS_UINT16                          usMsgId;
    VOS_UINT8                          *pucCbmiOct;

    pstEfCbmiFileInfo = TAF_CBA_GetEfCbmiInfo();

    pstEfCbmiFileInfo->ucEfCbmiExistFlg = ucEfCbmiExistFlg;

    /* 文件不存在，仅更新全局变量的存在标志 */
    if (VOS_FALSE == ucEfCbmiExistFlg)
    {
        return;
    }

    /* 文件存在，更新文件内容 */
    pstEfCbmiFileInfo->usEfCbmiFileLen  = usEfLen;

    /* 将USIM中CBMI文件记录的ID集合填写内存中 */
    pstCbmRangeids = (TAF_CBA_CBMI_RANGE_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU));
    if (VOS_NULL_PTR == pstCbmRangeids)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ParseUsimFileEfCbmiData: Fail to Alloc memory.");
        return;
    }

    PS_MEM_SET(pstCbmRangeids, 0x00, sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU));

    /* 计算USIM EFCBMI中CBMI的个数 */
    pucCbmiOct                  = pucEf;
    pstCbmRangeids->usCbmirNum  = TAF_CBA_CountCbmiNum((VOS_UINT16 *)pucEf, usEfLen);

    /* 数据个数检查 */
    if ( pstCbmRangeids->usCbmirNum >= TAF_CBA_MAX_CBMID_RANGE_NUM )
    {
        pstCbmRangeids->usCbmirNum = TAF_CBA_MAX_CBMID_RANGE_NUM;
    }

    for (ulLoop = 0; ulLoop < pstCbmRangeids->usCbmirNum; ulLoop++)
    {
        ucMsgIdHigh = *(pucCbmiOct);
        pucCbmiOct++;

        ucMsgIdLow  = *(pucCbmiOct);
        pucCbmiOct++;

        usMsgId     = (VOS_UINT16)( (ucMsgIdHigh << 8) | (ucMsgIdLow));

        pstCbmRangeids->astCbmiRangeInfo[ulLoop].usMsgIdFrom = usMsgId;
        pstCbmRangeids->astCbmiRangeInfo[ulLoop].usMsgIdTo   = usMsgId;
        pstCbmRangeids->astCbmiRangeInfo[ulLoop].enRcvMode   = TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT;
    }

    /* 更新内存列表 */
    (VOS_VOID)TAF_CBA_AddCbMiRangeListToActiveList(pstCbmRangeids);

    PS_MEM_FREE(WUEPS_PID_TAF, pstCbmRangeids);

}


VOS_VOID TAF_CBA_ParseUsimFileEfCbmirData(
    VOS_UINT8                           ucEfCbmirExistFlg,
    VOS_UINT8                          *pucEf,
    VOS_UINT16                          usEfLen
)
{
    TAF_CBA_USIM_EFCBMIR_FILE_INFO_STRU                    *pstEfCbmirFileInfo;
    VOS_UINT32                                              ulLoop;
    TAF_CBA_CBMI_RANGE_LIST_STRU                           *pstCbmirList;
    VOS_UINT8                                               ucMsgIdHigh;
    VOS_UINT8                                               ucMsgIdLow;
    VOS_UINT16                                              usMsgId;
    VOS_UINT8                                              *pucCbmirOct;

    pstEfCbmirFileInfo = TAF_CBA_GetEfCbmiRangeInfo();

    pstEfCbmirFileInfo->ucEfCbmirExistFlg = ucEfCbmirExistFlg;

    if (VOS_FALSE == ucEfCbmirExistFlg)
    {
        return;
    }

    pstEfCbmirFileInfo->usEfCbmirFileLen  = usEfLen;

    /* 将USIM中CBMIR文件记录的ID集合填写临时内存中 */
    pstCbmirList = (TAF_CBA_CBMI_RANGE_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU));
    if (VOS_NULL_PTR == pstCbmirList)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_ParseUsimFileEfCbmirData: Fail to Alloc memory.");
        return;
    }

    /* 计算USIM EFCBMIR中CBMIR的个数 */
    pstCbmirList->usCbmirNum = TAF_CBA_CountCbmirNum((VOS_UINT16 *)pucEf, usEfLen);

    pucCbmirOct = pucEf;

    /* 数据个数检查 */
    if ( pstCbmirList->usCbmirNum >= TAF_CBA_MAX_CBMID_RANGE_NUM )
    {
        pstCbmirList->usCbmirNum = TAF_CBA_MAX_CBMID_RANGE_NUM;
    }

    for (ulLoop = 0; ulLoop < pstCbmirList->usCbmirNum; ulLoop++)
    {
        ucMsgIdHigh = *(pucCbmirOct);
        pucCbmirOct++;

        ucMsgIdLow  = *(pucCbmirOct);
        pucCbmirOct++;

        usMsgId     = (VOS_UINT16)( (ucMsgIdHigh << 8) | (ucMsgIdLow));
        pstCbmirList->astCbmiRangeInfo[ulLoop].usMsgIdFrom = usMsgId;

        ucMsgIdHigh = *(pucCbmirOct);
        pucCbmirOct++;

        ucMsgIdLow  = *(pucCbmirOct);
        pucCbmirOct++;

        usMsgId     = (VOS_UINT16)( (ucMsgIdHigh << 8) | (ucMsgIdLow));
        pstCbmirList->astCbmiRangeInfo[ulLoop].usMsgIdTo = usMsgId;

        pstCbmirList->astCbmiRangeInfo[ulLoop].enRcvMode = TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT;
    }

    /* 先对range list排序 */
    TAF_CBA_SortCbmiRangeList(pstCbmirList);

    /* 更新内存中CBMIR的范围 */
    (VOS_VOID)TAF_CBA_AddCbMiRangeListToActiveList(pstCbmirList);

    PS_MEM_FREE(WUEPS_PID_TAF, pstCbmirList);
}


VOS_VOID TAF_CBA_ApplyUsimInfo(VOS_VOID)
{
    VOS_UINT32                          ulIsActiveListEmpty;

    /* CBS激活列表是否为空 */
    ulIsActiveListEmpty = TAF_CBA_IsCbsActiveListEmpty();

    /* CBS激活列表不为空并且需要向AS发送CBS请求时向AS发送CBS请求 */
    if ((VOS_TRUE  == TAF_CBA_IsNeedActAsCbs())
     && (VOS_FALSE == ulIsActiveListEmpty))
    {
        TAF_CBA_SndAsActiveCbsReq(TAF_CBS_CFG_ACTIVE);
    }

    /* 更新NV和USIM卡文件, 使USIM卡中和UE的NV中的CBMI信息保存一致 */
    if ( TAF_CBA_GetCbmiRangNum() > 0)
    {
        /* 更新NV项中的MSGID 列表 */
        TAF_CBA_WriteCbmiRangeListNvim();

        /* 更新USIM中的MSGID 文件 */
        TAF_CBA_UpdateUsimFile();
    }

    /* 可维可测信息 */
    TAF_CBA_SndOmCbmiDownloadListInfo();

    /* 可维可测信息 */
    TAF_CBA_SndOmCbmiRangeList();

    return;

}


VOS_VOID TAF_CBA_ParseSpecUsimFileData (
    VOS_UINT16                          usFileId,
    VOS_UINT8                           ucFileExistFlg,
    VOS_UINT8                          *pucEf,
    VOS_UINT16                          ulEfLen
)
{
    switch (usFileId)
    {
        case USIMM_USIM_EFCBMI_ID:
            TAF_CBA_ParseUsimFileEfCbmiData(ucFileExistFlg, pucEf, ulEfLen);
            break;

        case USIMM_USIM_EFCBMIR_ID:
             TAF_CBA_ParseUsimFileEfCbmirData(ucFileExistFlg, pucEf, ulEfLen);
             break;

        case USIMM_USIM_EFCBMID_ID:
             TAF_CBA_ParseUsimFileEfCbmidData(ucFileExistFlg, pucEf, ulEfLen);
             break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_ParseSpecUsimFileData: The input is invalid.");
            break;
    }
}


VOS_VOID TAF_CBA_ReadSpecificFileListRefreshFile(
    VOS_UINT32                          ulFileId,
    NAS_USIMM_SERVICES_TYPE_ENUM_UINT32 ulUsimmService,
    USIMM_STKREFRESH_IND_STRU          *pstRefreshInd
)
{
    VOS_UINT32                          ulEfLen;
    VOS_UINT32                          ulResult;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;      /*APP类型*/
    VOS_UINT8                           ucFileExistFlg;
    VOS_UINT8                          *pucEf   = VOS_NULL_PTR;

    ulEfLen = 0;

    if (PS_USIM_SERVICE_NOT_AVAILIABLE != NAS_USIMMAPI_IsServiceAvailable(ulUsimmService))
    {
        if (VOS_TRUE == TAF_GetSpecificFileListRefreshFileInfo((VOS_UINT16)ulFileId, pstRefreshInd, &enAppType))
        {
            /* 读取 TAF_CBA_EF_CBMI_ID USIM文件 */
            ucFileExistFlg = VOS_TRUE;
            ulResult = NAS_USIMMAPI_GetCachedFile(ulFileId, &ulEfLen, &pucEf, enAppType);
            if (USIMM_API_SUCCESS != ulResult)
            {
                ucFileExistFlg = VOS_FALSE;
            }
            TAF_CBA_ParseSpecUsimFileData((VOS_UINT16)ulFileId, ucFileExistFlg, pucEf, (VOS_UINT16)ulEfLen);
        }
    }

    return;
}


VOS_VOID TAF_CBA_ReadUsimFile(
    VOS_UINT32                          ulFileId,
    NAS_USIMM_SERVICES_TYPE_ENUM_UINT32 ulUsimmService
)
{
    VOS_UINT32                          ulEfLen;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucFileExistFlg;
    VOS_UINT8                          *pucEf   = VOS_NULL_PTR;

    if (PS_USIM_SERVICE_NOT_AVAILIABLE != NAS_USIMMAPI_IsServiceAvailable(ulUsimmService))
    {
        ucFileExistFlg = VOS_TRUE;
        ulResult = NAS_USIMMAPI_GetCachedFile(ulFileId, &ulEfLen, &pucEf, USIMM_GUTL_APP);
        if (USIMM_API_SUCCESS != ulResult)
        {
            ucFileExistFlg = VOS_FALSE;
        }

        TAF_CBA_ParseSpecUsimFileData((VOS_UINT16)ulFileId, ucFileExistFlg, pucEf, (VOS_UINT16)ulEfLen);

    }

    return;
}


VOS_VOID TAF_CBA_ProcRefreshInd(USIMM_STKREFRESH_IND_STRU *pstRefreshInd)
{
    if ((USIMM_REFRESH_FILE_LIST != pstRefreshInd->enRefreshType)
     && (USIMM_REFRESH_3G_SESSION_RESET != pstRefreshInd->enRefreshType)
     && (USIMM_REFRESH_ALL_FILE != pstRefreshInd->enRefreshType))
    {
        return;
    }

    if (USIMM_REFRESH_FILE_LIST == pstRefreshInd->enRefreshType)
    {
        TAF_CBA_ReadSpecificFileListRefreshFile(USIMM_USIM_EFCBMI_ID, NAS_USIM_SVR_CBMI, pstRefreshInd);

        TAF_CBA_ReadSpecificFileListRefreshFile(USIMM_USIM_EFCBMIR_ID, NAS_USIM_SVR_CBMIR, pstRefreshInd);

        TAF_CBA_ReadSpecificFileListRefreshFile(USIMM_USIM_EFCBMID_ID, NAS_USIM_SVR_DATA_DL_SMSCB, pstRefreshInd);
    }
    else
    {
        TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMI_ID, NAS_USIM_SVR_CBMI);

        TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMIR_ID, NAS_USIM_SVR_CBMIR);

        TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMID_ID, NAS_USIM_SVR_DATA_DL_SMSCB);

    }


    /* 应用USIM文件信息到本地和通知底层配置更新 */
    TAF_CBA_ApplyUsimInfo();

    return;
}




VOS_VOID TAF_CBA_ParseUsimFileEfCbmidData(
    VOS_UINT8                           ucEfCbmidExistFlg,
    VOS_UINT8                          *pucEf,
    VOS_UINT16                          usEfLen
)
{
    TAF_CBA_USIM_EFCBMID_FILE_INFO_STRU                    *pstEfCbmidFileInfo;
    TAF_CBA_CBMI_DOWNLOAD_LIST_STRU                        *pstCfgData;
    VOS_UINT32                                              ulLoop;
    VOS_UINT8                                               ucMsgIdHigh;
    VOS_UINT8                                               ucMsgIdLow;
    VOS_UINT16                                              usMsgId;
    VOS_UINT8                                              *pucCbmiOct;

    pstEfCbmidFileInfo  = TAF_CBA_GetEfCbmidInfo();
    pstEfCbmidFileInfo->ucEfCbmidExistFlg = ucEfCbmidExistFlg;
    if (VOS_FALSE == ucEfCbmidExistFlg)
    {
        return;
    }

    pstCfgData          = TAF_CBA_GetCbmiDownloadList();

    pstEfCbmidFileInfo->usEfCbmidFileLen  = usEfLen;

    /* 计算USIM EFCBMID中CBMI的个数 */
    pucCbmiOct              = pucEf;
    pstCfgData->usCbmidNum  = TAF_CBA_CountCbmiNum((VOS_UINT16 *)pucEf, usEfLen);

    /* 数据个数检查 */
    if ( pstCfgData->usCbmidNum >= TAF_CBA_MAX_CBMID_NUM )
    {
        pstCfgData->usCbmidNum = TAF_CBA_MAX_CBMID_NUM;
    }

    for (ulLoop = 0; ulLoop < pstCfgData->usCbmidNum; ulLoop++)
    {
        ucMsgIdHigh = *(pucCbmiOct);
        pucCbmiOct++;

        ucMsgIdLow  = *(pucCbmiOct);
        pucCbmiOct++;

        usMsgId     = (VOS_UINT16)( (ucMsgIdHigh << 8) | (ucMsgIdLow));
        pstCfgData->ausMsgId[ulLoop] = usMsgId;
    }
}


VOS_UINT16 TAF_CBA_CountCbmiNum(
    VOS_UINT16                         *pusCbmi,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT8                           ucCounter;
    VOS_UINT32                          ulRealLen;
    VOS_UINT8                           ucOffset;

    /* 将其计算出实际的长度  TAF_CBA_CBMI_UNIT_LEN * N */
    ulRealLen = ulLength;
    ucOffset  = ulLength%TAF_CBA_CBMI_UNIT_LEN;
    if (0 != ucOffset)
    {
        ulRealLen -= ucOffset;
    }

    /* 参见 3GPP 31.102 4.2.14, 4.2.20 节的描述 , Unused entries shall be set to 'FF FF'. */
    ucCounter = (VOS_UINT8)(ulRealLen/TAF_CBA_CBMI_UNIT_LEN);
    while (ucCounter >= 1)
    {
        if (TAF_CBA_EF_MSGID_PADDING != pusCbmi[ucCounter - 1])
        {
            break;
        }
        ucCounter--;
    }
    return ucCounter;
}


VOS_UINT16 TAF_CBA_CountCbmirNum(
    VOS_UINT16                         *pusCbmir,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT8                           ucCounter;
    VOS_UINT16                          usTemp1;
    VOS_UINT16                          usTemp2;
    VOS_UINT32                          ulRealLen;
    VOS_UINT8                           ucOffset;

    /* 将其计算出实际的长度  TAF_CBA_CBMIR_UNIT_LEN*N */
    ulRealLen = ulLength;
    ucOffset  = ulLength%TAF_CBA_CBMIR_UNIT_LEN;
    if ( 0 != ucOffset  )
    {
        ulRealLen -= ucOffset;
    }

    /* 参见 3GPP 31.102 4.2.22节的描述 , Unused entries shall be set to 'FF FF FF FF'. */
    ucCounter = (VOS_UINT8)(ulRealLen/TAF_CBA_CBMI_UNIT_LEN);
    while (2 <= ucCounter)
    {
        usTemp1 = pusCbmir[ucCounter - 1];
        usTemp2 = pusCbmir[ucCounter - 2];
        if ((TAF_CBA_EF_MSGID_PADDING != usTemp1)
         || (TAF_CBA_EF_MSGID_PADDING != usTemp2))
        {
            break;
        }
        ucCounter -= 2;
    }

    ucCounter /=2;

    return ucCounter;
}


VOS_VOID TAF_CBA_BuildUsimEfCbmiContent(
    VOS_UINT16                         *pusMsgId
)
{
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmidRangeList;
    TAF_CBA_CBMI_RANGE_STRU            *pstCbmidRange;
    TAF_CBA_USIM_EFCBMI_FILE_INFO_STRU *pstEfCbmiFileInfo;
    VOS_UINT32                          ulEfCbmiLen;
    VOS_UINT8                           ucMsgIdHigh;
    VOS_UINT8                           ucMsgIdLow;
    VOS_UINT32                          ulCbmirRangeIdx;
    VOS_UINT16                          usCbmiNum;

    ulEfCbmiLen       = 0;
    pstCbmidRangeList = TAF_CBA_GetCbMiRangeList();
    usCbmiNum         = TAF_CBA_GetCbmiRangNum();

    if(usCbmiNum > TAF_CBA_MAX_CBMID_RANGE_NUM)
    {
        usCbmiNum = TAF_CBA_MAX_CBMID_RANGE_NUM;
    }

    pstEfCbmiFileInfo = TAF_CBA_GetEfCbmiInfo();

    for ( ulCbmirRangeIdx = 0; ulCbmirRangeIdx < usCbmiNum; ulCbmirRangeIdx++ )
    {
        pstCbmidRange = &(pstCbmidRangeList->astCbmiRangeInfo[ulCbmirRangeIdx]);

        if ( (TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT == pstCbmidRange->enRcvMode)
          && (pstCbmidRange->usMsgIdFrom == pstCbmidRange->usMsgIdTo)
          && (ulEfCbmiLen < (pstEfCbmiFileInfo->usEfCbmiFileLen/TAF_CBA_CBMI_UNIT_LEN)) )
        {
            ucMsgIdHigh = (pstCbmidRange->usMsgIdFrom)>>8;
            ucMsgIdLow  = (pstCbmidRange->usMsgIdFrom) & 0xFF;
            pusMsgId[ulEfCbmiLen] = ((ucMsgIdLow << 8) | ucMsgIdHigh);
            ulEfCbmiLen++;
        }

        if ( ulEfCbmiLen >= TAF_CBA_MAX_CBMID_RANGE_NUM )
        {
            break;
        }
    }

}


VOS_VOID TAF_CBA_BuildUsimEfCbmirContent(
    TAF_CBA_USIM_CBMIR_STRU                                *pstMsgRange
)
{
    TAF_CBA_CBMI_RANGE_LIST_STRU                           *pstCbmidRangeList;
    TAF_CBA_CBMI_RANGE_STRU                                *pstCbmidRange;
    TAF_CBA_USIM_EFCBMIR_FILE_INFO_STRU                    *pstEfCbmirFileInfo;
    VOS_UINT32                                              ulEfCbmirlLen;
    VOS_UINT8                                               ucMsgIdHigh;
    VOS_UINT8                                               ucMsgIdLow;
    VOS_UINT32                                              ulCbmidRangeIdx;
    VOS_UINT16                                              usCbmiNum;


    ulEfCbmirlLen      = 0;
    pstCbmidRangeList  = TAF_CBA_GetCbMiRangeList();
    usCbmiNum          = TAF_CBA_GetCbmiRangNum();

    if (usCbmiNum > TAF_CBA_MAX_CBMID_RANGE_NUM)
    {
        usCbmiNum = TAF_CBA_MAX_CBMID_RANGE_NUM;
    }

    pstEfCbmirFileInfo = TAF_CBA_GetEfCbmiRangeInfo();

    for ( ulCbmidRangeIdx = 0; ulCbmidRangeIdx < usCbmiNum; ulCbmidRangeIdx++ )
    {
        pstCbmidRange = &(pstCbmidRangeList->astCbmiRangeInfo[ulCbmidRangeIdx]);

        if ( (TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT == pstCbmidRange->enRcvMode)
          && (pstCbmidRange->usMsgIdFrom != pstCbmidRange->usMsgIdTo)
          && (ulEfCbmirlLen < (pstEfCbmirFileInfo->usEfCbmirFileLen/TAF_CBA_CBMIR_UNIT_LEN)) )
        {
            ucMsgIdHigh = (pstCbmidRange->usMsgIdFrom)>>8;
            ucMsgIdLow  = (pstCbmidRange->usMsgIdFrom) & 0xFF;
            pstMsgRange[ulEfCbmirlLen].usMsgIdFrom = ((ucMsgIdLow << 8) | ucMsgIdHigh);

            ucMsgIdHigh = (pstCbmidRange->usMsgIdTo)>>8;
            ucMsgIdLow  = (pstCbmidRange->usMsgIdTo) & 0xFF;
            pstMsgRange[ulEfCbmirlLen].usMsgIdTo = ((ucMsgIdLow << 8) | ucMsgIdHigh);
            ulEfCbmirlLen++;
        }

        if ( ulEfCbmirlLen >= TAF_CBA_MAX_CBMID_RANGE_NUM )
        {
            break;
        }
    }

}


VOS_VOID TAF_CBA_UpdateUsimFileEfCbmiReq(VOS_VOID)
{
    TAF_CBA_USIM_EFCBMI_FILE_INFO_STRU *pstEfCbmiFileInfo;
    VOS_UINT32                          ulSndCbmiFileLen;
    VOS_UINT16                          ausMsgId[TAF_CBA_MAX_CBMID_RANGE_NUM];
    VOS_UINT32                          ulRet;
    NAS_USIMM_UPDATEFILE_INFO_STRU      stSetFileInfo;
    VOS_UINT16                          usFileId;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;

    usFileId = USIMM_DEF_FILEID_BUTT;
    enSimType = TAF_SDC_GetSimType();
    PS_MEM_SET(&stSetFileInfo, 0x00, sizeof(stSetFileInfo));

    /* CBMI文件不存在则返回 */
    pstEfCbmiFileInfo = TAF_CBA_GetEfCbmiInfo();
    if ( VOS_TRUE != pstEfCbmiFileInfo->ucEfCbmiExistFlg )
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_CBA_UpdateUsimFileEfCbmiReq: File not exist in sim!");
        return;
    }

    PS_MEM_SET(ausMsgId, (VOS_CHAR)0xFF, sizeof(ausMsgId));

    /* 根据全局变量中的MSG ID构造EF文件数据 */
    TAF_CBA_BuildUsimEfCbmiContent(ausMsgId);

    /* 发送给USIM的文件长度需以短的为主, */
    ulSndCbmiFileLen = pstEfCbmiFileInfo->usEfCbmiFileLen;
    if ( ulSndCbmiFileLen > sizeof(ausMsgId) )
    {
        ulSndCbmiFileLen = sizeof(ausMsgId);
    }

    if (TAF_SDC_SIM_TYPE_SIM == enSimType)
    {
        usFileId = USIMM_GSM_EFCBMI_ID;
    }
    else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        usFileId = USIMM_USIM_EFCBMI_ID;
    }
    else
    {
        return;
    }

    /* 发送给USIM */
    TAF_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0,
                                    (VOS_UINT8)ulSndCbmiFileLen,
                                    (VOS_UINT8 *)ausMsgId);

    ulRet = NAS_USIMMAPI_SetFileReq(WUEPS_PID_TAF, 0, &stSetFileInfo);

    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_UpdateUsimFileEfCbmiReq: Write USIM failed!");
    }
}


VOS_VOID TAF_CBA_UpdateUsimFileEfCbmirReq(VOS_VOID)
{
    TAF_CBA_USIM_EFCBMIR_FILE_INFO_STRU                    *pstEfCbmirFileInfo;
    VOS_UINT32                                              ulSndCbmirFileLen;
    TAF_CBA_USIM_CBMIR_STRU                                 astMsgRange[TAF_CBA_MAX_CBMID_RANGE_NUM];
    VOS_UINT32                                              ulRet;
    NAS_USIMM_UPDATEFILE_INFO_STRU      stSetFileInfo;
    VOS_UINT16                          usFileId;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;

    enSimType = TAF_SDC_GetSimType();
    usFileId = USIMM_DEF_FILEID_BUTT;
    PS_MEM_SET(&stSetFileInfo, 0x00, sizeof(stSetFileInfo));

    /* CBMIR文件不存在则返回 */
    pstEfCbmirFileInfo = TAF_CBA_GetEfCbmiRangeInfo();
    if ( VOS_TRUE != pstEfCbmirFileInfo->ucEfCbmirExistFlg )
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_CBA_UpdateUsimFileEfCbmirReq: File not exist in sim!");
        return;
    }

    PS_MEM_SET(astMsgRange, (VOS_CHAR)0xFF, sizeof(astMsgRange));

    /* 根据全局变量中的MSG ID构造EF文件数据 */
    TAF_CBA_BuildUsimEfCbmirContent(astMsgRange);

    /* 发送给USIM的文件长度需以短的为主, */
    ulSndCbmirFileLen = pstEfCbmirFileInfo->usEfCbmirFileLen;
    if ( ulSndCbmirFileLen > sizeof(astMsgRange) )
    {
        ulSndCbmirFileLen = sizeof(astMsgRange);
    }

    if (TAF_SDC_SIM_TYPE_SIM == enSimType)
    {
        usFileId = USIMM_GSM_EFCBMIR_ID;
    }
    else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        usFileId = USIMM_USIM_EFCBMIR_ID;
    }
    else
    {
        return;
    }

    /* 发送给USIM */
    TAF_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0,
                                    (VOS_UINT8)ulSndCbmirFileLen,
                                    (VOS_UINT8 *)astMsgRange);

    ulRet = NAS_USIMMAPI_SetFileReq(WUEPS_PID_TAF, 0, &stSetFileInfo);

    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_UpdateUsimFileEfCbmirReq: Write USIM failed!");
    }
}


VOS_VOID  TAF_CBA_UpdateUsimFile(VOS_VOID)
{
    /* 还在获取USIM文件的过程中,不能写文件 */

    /* 更新 CBMI 文件 */
    TAF_CBA_UpdateUsimFileEfCbmiReq();

    /* 更新 CBMIR 文件 */
    TAF_CBA_UpdateUsimFileEfCbmirReq();
}


VOS_UINT32  TAF_CBA_ProcUsimSetFileRsp(
    USIMM_UPDATEFILE_CNF_STRU           *pstSetFileRsp
)
{

    VOS_UINT32                          ulEfId;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, pstSetFileRsp->stFilePath.ulPathLen, pstSetFileRsp->stFilePath.acPath, &ulEfId))
    {
        return VOS_ERR;
    }

    if (((USIMM_GSM_EFCBMI_ID != ulEfId) && (USIMM_USIM_EFCBMI_ID != ulEfId))
     && ((USIMM_GSM_EFCBMIR_ID != ulEfId) && (USIMM_USIM_EFCBMIR_ID != ulEfId))
     && ((USIMM_GSM_EFCBMID_ID != ulEfId) && (USIMM_USIM_EFCBMID_ID != ulEfId)))
    {
        return VOS_ERR;
    }

    if (VOS_OK != (pstSetFileRsp->stCmdResult.ulResult))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_CBA_ProcUsimSetFileRsp:Write Files Error",
                        ulEfId);
    }

    return VOS_OK;
}


VOS_VOID TAF_CBA_SndUsimCbMsg(
    VOS_UINT32                          ulSendPID,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_CBRAW_TS_DATA_STRU          *pstCbMsg
)
{
    VOS_UINT32                          ulRet;
    SI_STK_ENVELOPE_STRU                stDataDownLoad;

    PS_MEM_SET(&stDataDownLoad, 0, sizeof(stDataDownLoad));

    /* 填写发送给USIM的固定字段 */
    stDataDownLoad.enEnvelopeType  = SI_STK_ENVELOPE_CBDOWN;
    stDataDownLoad.DeviceId.ucSDId = SI_DEVICE_NETWORK;
    stDataDownLoad.DeviceId.ucDDId = SI_DEVICE_UICC;

    stDataDownLoad.uEnvelope.CBDown.OP_CBPage        = 1;

    /* 越界保护 */
    if (pstCbMsg->ulLen > SI_STK_DATA_MAX_LEN)
    {
        pstCbMsg->ulLen = SI_STK_DATA_MAX_LEN;
    }

    stDataDownLoad.uEnvelope.CBDown.CBPage.ulLen     = (VOS_UINT8)pstCbMsg->ulLen;

    PS_MEM_CPY(stDataDownLoad.aucData, pstCbMsg->aucData, pstCbMsg->ulLen);

    stDataDownLoad.uEnvelope.CBDown.CBPage.pucCBPage = stDataDownLoad.aucData;

    /* 通知USIM发送Envelope */

    ulRet = NAS_STKAPI_EnvelopeDownload(ulSendPID, MN_CLIENT_ID_BROADCAST,&stDataDownLoad);


    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "MN_MSG_EnvelopeCbm: Fail to envelope download Cbm in USIM!");
    }

    return;
}

/* Deleted TAF_CBA_IsUsimFileReadFinished */
/*lint -restore */

#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
