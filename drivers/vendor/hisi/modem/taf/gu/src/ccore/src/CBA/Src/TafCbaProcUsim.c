/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCbaProcUsim.c
  版 本 号   : 初稿
  作    者   : l00171473
  生成日期   : 2012年3月19日
  最近修改   :
  功能描述   : CBA模块对USIM相关的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 创建文件

******************************************************************************/

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


/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* Deleted TAF_CBA_ProcUsimGetFileRsp */
/* Deleted TAF_CBA_SndUsimGetFileReq */
/* Deleted TAF_CBA_RcvUsimGetEfCbmiRsp TAF_CBA_RcvUsimGetEfCbmirRsp TAF_CBA_RcvUsimGetEfCbmidRsp */
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
 函 数 名  : TAF_CBA_ParseUsimFileEfCbmiData
 功能描述  : 解析USIM中的EFCBMI 文件内容, 更新到内存中
 输入参数  : pstUsimGetFileRsp: USIM中EFCBMI文件内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月15日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数

  2.日    期   : 2012年3月30日
    作    者   : l00171473
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  3.日    期   : 2012年12月26日
    作    者   : 张鹏 /z00214637
    修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
  4.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
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

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    pstEfCbmiFileInfo->ucEfCbmiExistFlg = ucEfCbmiExistFlg;

    /* 文件不存在，仅更新全局变量的存在标志 */
    if (VOS_FALSE == ucEfCbmiExistFlg)
    {
        return;
    }

    /* 文件存在，更新文件内容 */
    pstEfCbmiFileInfo->usEfCbmiFileLen  = usEfLen;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    /* 将USIM中CBMI文件记录的ID集合填写内存中 */
    pstCbmRangeids = (TAF_CBA_CBMI_RANGE_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU));
    if (VOS_NULL_PTR == pstCbmRangeids)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ParseUsimFileEfCbmiData: Fail to Alloc memory.");
        return;
    }

    PS_MEM_SET(pstCbmRangeids, 0x00, sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU));

    /* 计算USIM EFCBMI中CBMI的个数 */
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    pucCbmiOct                  = pucEf;
    pstCbmRangeids->usCbmirNum  = TAF_CBA_CountCbmiNum((VOS_UINT16 *)pucEf, usEfLen);
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

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

/*****************************************************************************
 函 数 名  : TAF_CBA_ParseUsimFileEfCbmirData
 功能描述  : 解析USIM中的EFCBMIR文件内容, 并更新到内存中
 输入参数  : pstUsimGetFileRsp: USIM中EFCBMIR文件内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月15日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年12月26日
    作    者   : 张鹏 /z00214637
    修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
  3.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
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

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    pstEfCbmirFileInfo->ucEfCbmirExistFlg = ucEfCbmirExistFlg;

    if (VOS_FALSE == ucEfCbmirExistFlg)
    {
        return;
    }

    pstEfCbmirFileInfo->usEfCbmirFileLen  = usEfLen;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    /* 将USIM中CBMIR文件记录的ID集合填写临时内存中 */
    pstCbmirList = (TAF_CBA_CBMI_RANGE_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU));
    if (VOS_NULL_PTR == pstCbmirList)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_ParseUsimFileEfCbmirData: Fail to Alloc memory.");
        return;
    }

    /* 计算USIM EFCBMIR中CBMIR的个数 */
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    pstCbmirList->usCbmirNum = TAF_CBA_CountCbmirNum((VOS_UINT16 *)pucEf, usEfLen);

    pucCbmirOct = pucEf;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

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

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
/*****************************************************************************
 函 数 名  : TAF_CBA_ApplyUsimInfo
 功能描述  : 更新USIM文件到NV项和底层模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CBA_ParseSpecUsimFileData
 功能描述  : 更新指定CBA文件的信息
 输入参数  :  VOS_UINT16                          usFileId,
    VOS_UINT8                           ucFileExistFlg,
    VOS_UINT8                          *pucEf,
    VOS_UINT32                          ulEfLen
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月27日
    作    者   : l00208543
    修改内容   : STK升级项目
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CBA_ReadSpecificFileListRefreshFile
 功能描述  : 指定文件列表的REFRESH事件触发的文件更新，更新指定文件信息
 输入参数  : usFileId           文件ID
             ulUsimmService     文件涉及的USIM服务，仅有服务存在情况下文件存在
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : STK升级项目
  2.日    期   : 2013年11月04日                                                    
    作    者   : s00217060                                                         
    修改内容   : VoLTE_PhaseII项目
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CBA_ReadUsimFile
 功能描述  : 更新指定USIM文件信息
 输入参数  : usFileId           文件ID
             ulUsimmService     文件涉及的USIM服务，仅有服务存在情况下文件存在
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : STK升级项目
  2.日    期   : 2013年11月04日                                                    
    作    者   : s00217060                                                         
    修改内容   : VoLTE_PhaseII项目
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CBA_ProcRefreshInd
 功能描述  : 处理来自USIM模块的文件数据消息
 输入参数  : pstMsg: 来自USIM模块的VOS消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
  2.日    期   : 2013年11月04日                                                    
    作    者   : s00217060                                                         
    修改内容   : VoLTE_PhaseII项目

*****************************************************************************/
VOS_VOID TAF_CBA_ProcRefreshInd(USIMM_STKREFRESH_IND_STRU *pstRefreshInd)
{
    if ((USIMM_REFRESH_FILE_LIST != pstRefreshInd->enRefreshType)
     && (USIMM_REFRESH_3G_SESSION_RESET != pstRefreshInd->enRefreshType)
     && (USIMM_REFRESH_ALL_FILE != pstRefreshInd->enRefreshType))
    {
        return;
    }

    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, begin */
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

    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-11-04, end */

    /* 应用USIM文件信息到本地和通知底层配置更新 */
    TAF_CBA_ApplyUsimInfo();

    return;
}


/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
 函 数 名  : TAF_CBA_ParseUsimFileEfCbmidData
 功能描述  : 解析USIM中的EFCBMID文件内容, 更新到内存中
 输入参数  : pstUsimGetFileRsp: USIM中EFCBMIR文件内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月15日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年12月26日
    作    者   : 张鹏 /z00214637
    修改内容   : PS_USIM_GET_FILE_RLT_SUCCESS替换为VOS_OK
  3.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级

*****************************************************************************/
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
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    pstEfCbmidFileInfo->ucEfCbmidExistFlg = ucEfCbmidExistFlg;
    if (VOS_FALSE == ucEfCbmidExistFlg)
    {
        return;
    }
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    pstCfgData          = TAF_CBA_GetCbmiDownloadList();

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    pstEfCbmidFileInfo->usEfCbmidFileLen  = usEfLen;

    /* 计算USIM EFCBMID中CBMI的个数 */
    pucCbmiOct              = pucEf;
    pstCfgData->usCbmidNum  = TAF_CBA_CountCbmiNum((VOS_UINT16 *)pucEf, usEfLen);
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

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

/*****************************************************************************
 函 数 名  : TAF_CBA_CountCbmiNum
 功能描述  : 计算USIM卡中存储的CBMI或CBMID 个数
 输入参数  : pusCbmi : 数据区的起始指针；
             ulLength: 数据区长度；
 输出参数  : 无
 返 回 值  : CB Message Identifier的个数; 或
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月20日
    作    者   : 傅映君 62575
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CBA_CountCbmirNum
 功能描述  : 计算CBMIR的个数；
 输入参数  : pusCbmir: 数据区的起始指针；
             ucLength: 数据区长度，数据区长度以字节为单位；
 输出参数  : 无
 返 回 值  : CB Message Identifier Range的个数；
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年12月20日
    作    者   : 傅映君 62575
    修改内容   : 新生成函数

  2.日    期   : 2010年5月20日
    作    者   : zhoujun /z40661
    修改内容   : 此处修改的目的是为了避免如下情况，用户设置0-65535
  3.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理Fortify
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CBA_BuildUsimEfCbmiContent
 功能描述  : 构造发送给USIM的EF CBMI文件内容
 输入参数  : 无
 输出参数  : pusMsgId: USIM的EF CBMI文件内容
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理Coverity

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CBA_BuildUsimEfCbmirContent
 功能描述  : 构造发送给USIM的EF CBMIR文件内容
 输入参数  : 无
 输出参数  : pstMsgRange: USIM的 EF CBMIR文件内容
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2013年07月22日
    作    者   : j00177245
    修改内容   : 清理Fortify

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CBA_UpdateUsimFileEfCbmiReq
 功能描述  : 根据全局变量中的MSG ID更新USIM中EFCBMI文件
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2012年12月26日
    作    者   : 张鹏 id:00214637
    修改内容   : USIM对外接口函数变更的处理 ，
                 Client ID 到 PID的转换处理 ，入参封装成结构体。
  3.日    期   : 2013年6月7日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
  4.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CBA_UpdateUsimFileEfCbmirReq
 功能描述  : 根据全局变量中的MSG ID更新USIM中EFCBMIR文件
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2012年12月26日
    作    者   : 张鹏 id:00214637
    修改内容   : USIM对外接口函数变更的处理 ，
                 Client ID 到 PID的转换处理 ，入参封装成结构体。
  3.日    期   : 2013年6月7日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
  4.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CBA_UpdateUsimFile
 功能描述  : 根据全局变量中的MSG ID更新USIM文件
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月20日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2012年3月28日
    作    者   : w00176964
    修改内容   : 读取USIM文件逻辑更改
  3.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
VOS_VOID  TAF_CBA_UpdateUsimFile(VOS_VOID)
{
    /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
    /* 还在获取USIM文件的过程中,不能写文件 */
    /* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

    /* 更新 CBMI 文件 */
    TAF_CBA_UpdateUsimFileEfCbmiReq();

    /* 更新 CBMIR 文件 */
    TAF_CBA_UpdateUsimFileEfCbmirReq();
}

/*****************************************************************************
 函 数 名  : TAF_CBA_ProcUsimSetFileRsp
 功能描述  : 处理接收到USIM发送过来的SetFileRsp的原语
 输入参数  : pMsg:USIM发送过来的设置文件的内容
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月20日
    作    者   : l00171473
    修改内容   : 新生成函数, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.日    期   : 2012年12月26日
    作    者   : 张鹏/z00214637
    修改内容   : PS_USIM_SET_FILE_RLT_SUCCESS转换为VOS_OK
  3.日    期   : 2015年02月06日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CBA_SndUsimCbMsg
 功能描述  : 存储EFCBMID中指定的CBS消息
 输入参数  : clientId           - 发起该请求的Client的ID
             opId               - Operation ID, 标识本次操作
             pstCbMsg           - 需要Envelope Download到USIM的CBS内容;
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月14日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年12月26日
    作    者   : 张鹏 id:00214637
    修改内容   : USIM对外接口函数变更的处理
  3.日    期   : 2013年5月16日
    作    者   : w00176964
    修改内容   : SS FDN&Call Control项目:SI_STK_EnvelopeDownload接口增加client ID
  4.日    期   : 2013年6月7日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口调整
*****************************************************************************/
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

/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* Deleted TAF_CBA_IsUsimFileReadFinished */
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */
/*lint -restore */

#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
