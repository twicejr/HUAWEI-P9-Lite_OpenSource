/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcProcNvim.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2010年5月10日
  最近修改   :
  功能描述   : MMC处理NV项的读写文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年05月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasMmlCtx.h"
#include "NasMmcCtx.h"
#include "NasMmcProcNvim.h"
#include "NasComm.h"

#include "NasMmlLib.h"
#include "NasMmcProcUsim.h"
#include "pscfg.h"
#include "NasMmcSndOm.h"
#include "NasUsimmApi.h"
#if (FEATURE_LTE == FEATURE_ON)
#include "msp_nvim.h"
#include "LNvCommon.h"
#include "LNasNvInterface.h"
#include "LPsNvInterface.h"
#include "ImsaNvInterface.h"

#include "NasMmcSndLmm.h"
#endif

#include "ScInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/


/* DSDS使能NV从TTF读取 */
#include "TtfNvInterface.h"
#include "WasNvInterface.h"

#include "NasMmcComFunc.h"

/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, begin */
#include "SysNvId.h"
/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, end */
#include "NasMmcPlmnSelectionStrategy.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_PROC_NIVM_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadCsOnlyDataServiceSupportNvim
 功能描述  : 读取用户定制NV项，控制PS注册被禁止时是否允许数据业务触发PS域注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年02月12日
    作    者   : f62575
    修改内容   : DTS2014012902032: en_NV_Item_CS_ONLY_DATA_SERVICE_SUPPORT_FLG
数据修改为从内存中获取
*****************************************************************************/
VOS_VOID NAS_MMC_ReadCsOnlyDataServiceSupportNvim( VOS_VOID )
{
    NAS_MML_CS_ONLY_DATA_SERVICE_SUPPORT_FLG_STRU           stCsOnlyDataServiceSupportFlg;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    PS_MEM_SET(&stCsOnlyDataServiceSupportFlg, 0, sizeof(stCsOnlyDataServiceSupportFlg));
    if (NV_OK != NV_Read(en_NV_Item_CS_ONLY_DATA_SERVICE_SUPPORT_FLG,
                         &stCsOnlyDataServiceSupportFlg,
                         sizeof(stCsOnlyDataServiceSupportFlg)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadCsOnlyDataServiceSupportNvim():WARNING: en_NV_Item_CS_ONLY_DATA_SERVICE_SUPPORT_FLG Error");

        return;
    }


    if (NAS_MMC_NV_ITEM_ACTIVE != stCsOnlyDataServiceSupportFlg.ucActiveFlg)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadCsOnlyDataServiceSupportNvim(): NV deactive.");
        return;
    }

    if (0 != stCsOnlyDataServiceSupportFlg.ucCsOnlyDataServiceSupportFlg)
    {
        stCsOnlyDataServiceSupportFlg.ucCsOnlyDataServiceSupportFlg = VOS_TRUE;
    }

    pstMiscellaneousCfgInfo->ucCsOnlyDataServiceSupportFlg
             = stCsOnlyDataServiceSupportFlg.ucCsOnlyDataServiceSupportFlg;

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadLteDisabledUseLteInfoFlagNvim
 功能描述  : 读取l disabled场景，是否从l获取安全上下文和guti映射信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年02月25日
    作    者   : z00161729
    修改内容   : DTS2014022206794:GCF 9.2.1.2.1b/9.2.3.2.3/9.2.1.2.1失败disable
                 lte时rau需要从L获取安全上下文

*****************************************************************************/
VOS_VOID NAS_MMC_ReadLteDisabledUseLteInfoFlagNvim(VOS_VOID)
{
    NAS_MMC_LTE_DISABLED_USE_LTE_INFO_FLAG_STRU             stLDisabledUseLInfoFlag;
    VOS_UINT32                                              ulLength;

    ulLength                = 0;
    PS_MEM_SET(&stLDisabledUseLInfoFlag, 0, sizeof(stLDisabledUseLInfoFlag));

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_LTE_DISABLED_USE_LTE_INFO_FLAG, &ulLength);

    if (ulLength > sizeof(NAS_MMC_LTE_DISABLED_USE_LTE_INFO_FLAG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteDisabledUseLteInfoFlagNvim(): nv length Error");
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_LTE_DISABLED_USE_LTE_INFO_FLAG,
                         &stLDisabledUseLInfoFlag, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadLteDisabledUseLteInfoFlagNvim():WARNING: NV read Error");

        return;
    }

    /* 测试卡nv项默认开启*/
    if ((VOS_TRUE == NAS_USIMMAPI_IsTestCard())
     || (VOS_TRUE == stLDisabledUseLInfoFlag.ucLDisabledRauUseLInfoFlag))
    {
        NAS_MML_SetLteDisabledRauUseLteInfoFlag(VOS_TRUE);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadWgRfMainBandNvim
 功能描述  : 从NV中获取手机支持的GU接入技术的主集通路
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年02月10日
    作    者   : f62575
    修改内容   : DTS2014012600456: en_NV_Item_WG_RF_MAIN_BAND
数据修改为从内存中获取
*****************************************************************************/
VOS_VOID NAS_MMC_ReadWgRfMainBandNvim( VOS_VOID )
{
    NAS_NVIM_WG_RF_MAIN_BAND_STRU       stRfMainBand;
    VOS_UINT32                          ulDataLen;

    ulDataLen = 0;

    PS_MEM_SET(&stRfMainBand, 0x00, sizeof(stRfMainBand));

    (VOS_VOID)NV_GetLength(en_NV_Item_WG_RF_MAIN_BAND, &ulDataLen);

    if (NV_OK != NV_Read(en_NV_Item_WG_RF_MAIN_BAND, &stRfMainBand, ulDataLen))
    {
        /*打印未成功初始化值，原值保留*/
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadWgRfMainBandNvim():Read en_NV_Item_WG_RF_MAIN_BAND Failed!");
        return;
    }

    NAS_MML_SetGsmBandCapability(stRfMainBand.ulGband);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadLauRejTrigPlmnSearchNvim
 功能描述  : 读取NV项
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月21日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ReadLauRejTrigPlmnSearchNvim( VOS_VOID )
{
    NAS_NVIM_LAU_REJ_TRIG_PLMN_SEARCH_CFG_STRU              stLauRejCfg;
    VOS_UINT32                                              ulLength;
    NAS_MML_LAU_REJ_TRIG_PLMN_SEARCH_STRU                  *pstLauRejCfg    = VOS_NULL_PTR;

    ulLength        = 0;
    pstLauRejCfg    = NAS_MML_GetLauRejTrigPlmnSearchCfg();

    PS_MEM_SET(&stLauRejCfg, 0, sizeof(NAS_NVIM_LAU_REJ_TRIG_PLMN_SEARCH_CFG_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_LAU_REJ_TRIG_PLMN_SEARCH, &ulLength);
    if (ulLength > sizeof(NAS_NVIM_LAU_REJ_TRIG_PLMN_SEARCH_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadLauRejTrigPlmnSearchNvim():en_NV_Item_LAU_REJ_TRIG_PLMN_SEARCH Length Error");
        return;
    }


    if (NV_OK != NV_Read(en_NV_Item_LAU_REJ_TRIG_PLMN_SEARCH,
                         &stLauRejCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadLauRejTrigPlmnSearchNvim():en_NV_Item_LAU_REJ_TRIG_PLMN_SEARCH Error");

        return;
    }


    /* NV赋值到全局变量中 */
    if (stLauRejCfg.ucCmSrvTrigPlmnSearchCauseNum   > NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM)
    {
        stLauRejCfg.ucCmSrvTrigPlmnSearchCauseNum   = NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM;
    }

    pstLauRejCfg->ucCmSrvExistTrigPlmnSearch        = stLauRejCfg.ucCmSrvExistTrigPlmnSearch;
    pstLauRejCfg->ucCmSrvTrigPlmnSearchCauseNum     = stLauRejCfg.ucCmSrvTrigPlmnSearchCauseNum;
    PS_MEM_CPY(pstLauRejCfg->aucCmSrvTrigPlmnSearchCause, stLauRejCfg.aucCmSrvTrigPlmnSearchCause, stLauRejCfg.ucCmSrvTrigPlmnSearchCauseNum);

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadLauRejNeedRetryWhenCmSrvExist
 功能描述  : 读取NV项
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月21日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ReadLauRejNeedNoRetryWhenCmSrvExistNvim( VOS_VOID )
{
    NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU     *pstLauRejCfg = VOS_NULL_PTR;
    NAS_NVIM_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU     stLauRejCfg;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              i;

    ulLength        = 0;
    i               = 0;

    PS_MEM_SET(&stLauRejCfg, 0, sizeof(NAS_NVIM_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST, &ulLength);
    if (ulLength > sizeof(NAS_NVIM_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU))
    {
        return;
    }

    pstLauRejCfg = NAS_MML_GetLauRejNoRetryWhenCmSrvExistCfgInfo();

    if (NV_OK != NV_Read(en_NV_Item_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST,
                         &stLauRejCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadLauRejNeedRetryWhenCmSrvExist():en_NV_Item_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST Error");

        return;
    }

    pstLauRejCfg->ucLauRejCauseNum  = stLauRejCfg.ucLauRejCauseNum;
    pstLauRejCfg->ucLauRejTimes     = stLauRejCfg.ucLauRejTimes;

    if (pstLauRejCfg->ucLauRejCauseNum > NAS_NVIM_MAX_REJECT_NO_RETRY_CAUSE_NUM)
    {
        pstLauRejCfg->ucLauRejCauseNum = NAS_NVIM_MAX_REJECT_NO_RETRY_CAUSE_NUM;
    }

    for (i = 0; i < pstLauRejCfg->ucLauRejCauseNum; i++)
    {
        pstLauRejCfg->aucLauRejCause[i] = stLauRejCfg.aucLauRejCause[i];
    }

    return;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadRoamingRejectNoRetryFlgNvim
 功能描述  : 从NV中获取是否支持收到reject 17时不再重试的定制
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月29日
   作    者   : l00208543
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ReadRoamingRejectNoRetryFlgNvim( VOS_VOID )
{
    NAS_MML_ROAMINGREJECT_NORETYR_CFG_STRU                 *pstNoRetryCfg = VOS_NULL_PTR;
    NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU                 stRoamingRejectNoRetryCfg;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              i;

    ulLength        = 0;
    i               = 0;

    PS_MEM_SET(&stRoamingRejectNoRetryCfg, 0, sizeof(NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_ROAMING_REJECT_NORETRY_CFG, &ulLength);
    if (ulLength > sizeof(NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU))
    {
        return;
    }

    pstNoRetryCfg = NAS_MML_GetRoamingRejectNoRetryCfg();

    if (NV_OK != NV_Read(en_NV_Item_ROAMING_REJECT_NORETRY_CFG,
                         &stRoamingRejectNoRetryCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadRoamingRejectNoRetryFlgNvim():en_NV_Item_ROAMING_REJECT_NORETRY_CFG Error");

        return;
    }

    pstNoRetryCfg->ucNoRetryRejectCauseNum = stRoamingRejectNoRetryCfg.ucNoRetryRejectCauseNum;

    if (pstNoRetryCfg->ucNoRetryRejectCauseNum > NAS_MML_MAX_ROAMING_REJECT_NO_RETRY_CAUSE_NUM)
    {
        pstNoRetryCfg->ucNoRetryRejectCauseNum = NAS_MML_MAX_ROAMING_REJECT_NO_RETRY_CAUSE_NUM;
    }

    for (i = 0; i < pstNoRetryCfg->ucNoRetryRejectCauseNum; i++)
    {
        pstNoRetryCfg->aucNoRetryRejectCause[i] = stRoamingRejectNoRetryCfg.aucNoRetryRejectCause[i];
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadImeisvNvim
 功能描述  : 从NV中获取IMEISV的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月13日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2012年12月13日
   作    者   : L00171473
   修改内容   : DTS2012121802573, TQE清理
 3.日    期   : 2013年05月21日
   作    者   : Y00213812
   修改内容   : 调用SC端口读取IMEI号码的NV项
*****************************************************************************/
VOS_VOID NAS_MMC_ReadImeisvNvim( VOS_VOID )
{
    VOS_UINT8                           aucImeisv[NV_ITEM_IMEI_SIZE];
    VOS_UINT8                           i;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    VOS_UINT8                           aucImeiSvn[4];

    MODEM_ID_ENUM_UINT16                enModemId;


    PS_MEM_SET(aucImeisv, 0x00, sizeof(aucImeisv));

    pstMsCapability = NAS_MML_GetMsCapability();

    /* 由PID获取MODEMID */
    enModemId = VOS_GetModemIDFromPid(WUEPS_PID_MMC);

    NAS_TRACE_HIGH("SC_PERS_VerifyNvReadImei begin");

    /* 调用SC接口读取IMEI号码 */
    (VOS_VOID)SC_PERS_VerifyNvReadImei(enModemId, en_NV_Item_IMEI, aucImeisv, NV_ITEM_IMEI_SIZE);

    NAS_TRACE_HIGH("SC_PERS_VerifyNvReadImei end");

    for (i = 0; i < NV_ITEM_IMEI_SIZE; i++)
    {
        pstMsCapability->aucImeisv[i] = aucImeisv[i];
    }

    /* 需要将最后两个字节置为0 */
    pstMsCapability->aucImeisv[NV_ITEM_IMEI_SIZE-2] = 0;
    pstMsCapability->aucImeisv[NV_ITEM_IMEI_SIZE-1] = 0;



    PS_MEM_SET(aucImeiSvn, 0x00, sizeof(aucImeiSvn));

    /* 后获取IMEISV的内容 */
    if (NV_OK != NV_Read(en_NV_Item_Imei_Svn,
                    aucImeiSvn, sizeof(aucImeiSvn)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadImeisvNvim:Read Nvim Failed");
        return;

    }

    /* NV项有效,则更新 */
    if (VOS_TRUE == aucImeiSvn[0])
    {
         pstMsCapability->aucImeisv[NV_ITEM_IMEI_SIZE-2] = aucImeiSvn[1];
         pstMsCapability->aucImeisv[NV_ITEM_IMEI_SIZE-1] = aucImeiSvn[2];
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadSupported3GppReleaseNvim
 功能描述  : 从NV中读取协议版本,包括获取G和W 3GPP协议版本,
             获取MS支持SGSN的版本，主要用于终端上报的SGSN版本,
             获取MS支持MSC的版本，主要用于终端上报的MSC版本
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月14日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : s46746
    修改内容   : 对于R7、R8新增信息单元,使用协议版本控制
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  4.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadSupported3GppReleaseNvim(VOS_VOID)
{
    NAS_MML_MS_3GPP_REL_STRU           *pstMs3GppRel = VOS_NULL_PTR;
    NAS_MMC_NVIM_MSCR_VERSION_STRU      stMscrVersion;
    NAS_MMC_NVIM_SGSNR_VERSION_STRU     stSgsnrVersion;
    VOS_UINT32                          ulLength;

    NAS_MMC_NVIM_SUPPORT_3GPP_RELEASE_STRU  stSupported3GppRelease;

    ulLength                                          = 0;


    stSupported3GppRelease.aucSupported3GppRelease[0] = NAS_MML_3GPP_REL_R4 + 1;
    stSupported3GppRelease.aucSupported3GppRelease[1] = NAS_MML_3GPP_REL_R6 + 1;

    stMscrVersion.ucStatus          = NAS_MMC_NV_ITEM_DEACTIVE;
    stMscrVersion.ucUeMscrVersion   = 0;

    stSgsnrVersion.ucStatus         = NAS_MMC_NV_ITEM_DEACTIVE;
    stSgsnrVersion.ucUeSgsnrVersion = 0;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();

    /* 读取支持的协议栈版本 */
    if(NV_OK != NV_Read (en_NV_Item_NAS_Supported_3GPP_Release,
                         &stSupported3GppRelease, NAS_MMC_NVIM_SUPPORTED_3GPP_RELEASE_SIZE))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSupported3GppReleaseNvim(): en_NV_Item_Supported_3GPP_Release Error");
        return;
    }

    /* NV手册中描述NV中记录值含义:
    1：R4版本；
    2：R5版本；
    3：R6版本（默认值）；
    4：R7版本。
    */

    pstMs3GppRel->enMsGsmRel   = stSupported3GppRelease.aucSupported3GppRelease[0] - 1;
    pstMs3GppRel->enMsWcdmaRel = stSupported3GppRelease.aucSupported3GppRelease[1] - 1;
    (VOS_VOID)NV_GetLength(en_NV_Item_UE_MSCR_VERSION, &ulLength);
    /* 读取MSC的版本 */
    if (NV_OK != NV_Read (en_NV_Item_UE_MSCR_VERSION, &stMscrVersion, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSupported3GppReleaseNvim():WARNING: NV_Read en_NV_Item_UE_MSCR_VERSION Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stMscrVersion.ucStatus)
    {
        pstMs3GppRel->enMsMscRel = stMscrVersion.ucUeMscrVersion;
    }


    /* 读取SGSN的版本 */
    if (NV_OK != NV_Read (en_NV_Item_UE_SGSNR_VERSION, &stSgsnrVersion, sizeof(stSgsnrVersion)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSupported3GppReleaseNvim():WARNING: NV_Read en_NV_Item_UE_SGSNR_VERSION Error");
        return;
    }

    if(NAS_MMC_NV_ITEM_ACTIVE == stSgsnrVersion.ucStatus)
    {
        pstMs3GppRel->enMsSgsnRel = stSgsnrVersion.ucUeSgsnrVersion;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadClassMark1Nvim
 功能描述  : 从NV中获取ClassMark1信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月14日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadClassMark1Nvim(VOS_VOID)
{
    VOS_UINT8                           ucClassmark1;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;


    ucClassmark1 = NAS_MML_DEFAULT_CLASSMARK1_VALUE;

    pstMsCapability = NAS_MML_GetMsCapability();

    if (NV_OK != NV_Read (en_NV_Item_Gsm_Classmark1,
                          &ucClassmark1, sizeof(VOS_UINT8)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,  "NAS_MMC_ReadClassMark1Nvim(): NV_Read Classmark1 Error");
        return;
    }

    pstMsCapability->ucClassmark1 = ucClassmark1;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadClassMark2Nvim
 功能描述  : 从NV中获取ClassMark2信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月14日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadClassMark2Nvim(VOS_VOID)
{
    VOS_UINT8                           aucClassmark2[NAS_MML_CLASSMARK2_LEN];
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;


    PS_MEM_SET(aucClassmark2, 0x00, NAS_MML_CLASSMARK2_LEN);

    pstMsCapability = NAS_MML_GetMsCapability();

    if (NV_OK != NV_Read (en_NV_Item_Gsm_Classmark2,
                          aucClassmark2, NAS_MML_CLASSMARK2_LEN))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadClassMark2Nvim():NV_Read Classmark2 Error");
        return;
    }

    PS_MEM_CPY(pstMsCapability->aucClassmark2, aucClassmark2, NAS_MML_CLASSMARK2_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateNetworkCapabilityGeaValue
 功能描述  : 获取NV项en_NV_Item_GEA_SUPPORT_CTRL，更新network capability的GEA1,GEA2值。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月15日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateNetworkCapabilityGeaValue(VOS_VOID)
{
    NAS_MMC_NVIM_GPRS_GEA_ALG_CTRL_STRU stGeaSupportCtrl;
    VOS_UINT8                           ucGeaSupportCtrl;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    stGeaSupportCtrl.ucStatus         = NAS_MMC_NV_ITEM_DEACTIVE;
    stGeaSupportCtrl.ucGeaSupportCtrl = 0;

    pstMsCapability = NAS_MML_GetMsCapability();

    (VOS_VOID)NV_GetLength(en_NV_Item_GEA_SUPPORT_CTRL, &ulLength);
    if (ulLength > sizeof(stGeaSupportCtrl))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_GEA_SUPPORT_CTRL, &stGeaSupportCtrl, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_UpdateNetworkCapabilityGeaValue():NV_Read en_NV_Item_GEA_SUPPORT_CTRL Error");

        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stGeaSupportCtrl.ucStatus)
    {
        ucGeaSupportCtrl = stGeaSupportCtrl.ucGeaSupportCtrl;

        /* 初始化为GEA1-GEA7都不支持 */
        pstMsCapability->stMsNetworkCapability.aucNetworkCapability[0] &= ~NAS_MMC_GPRS_GEA1_VALUE;
        pstMsCapability->stMsNetworkCapability.aucNetworkCapability[1] &= ~( NAS_MMC_GPRS_GEA2_VALUE
                                                                          | NAS_MMC_GPRS_GEA3_VALUE
                                                                          | NAS_MMC_GPRS_GEA4_VALUE
                                                                          | NAS_MMC_GPRS_GEA5_VALUE
                                                                          | NAS_MMC_GPRS_GEA6_VALUE
                                                                          | NAS_MMC_GPRS_GEA7_VALUE);

        /*  GEA1: 第一个字节的最高位 */
        if (NAS_MMC_GPRS_GEA1_SUPPORT == (ucGeaSupportCtrl & NAS_MMC_GPRS_GEA1_SUPPORT))
        {
            pstMsCapability->stMsNetworkCapability.aucNetworkCapability[0] |= NAS_MMC_GPRS_GEA1_VALUE;
        }

        /*  GEA2: 第二个字节的左起第二个bit */
        if (NAS_MMC_GPRS_GEA2_SUPPORT == (ucGeaSupportCtrl & NAS_MMC_GPRS_GEA2_SUPPORT))
        {
            pstMsCapability->stMsNetworkCapability.aucNetworkCapability[1] |= NAS_MMC_GPRS_GEA2_VALUE;
        }

        /* GEA3: 第二个字节的左起第三个bit */
        if (NAS_MMC_GPRS_GEA3_SUPPORT == (ucGeaSupportCtrl & NAS_MMC_GPRS_GEA3_SUPPORT))
        {
            pstMsCapability->stMsNetworkCapability.aucNetworkCapability[1] |= NAS_MMC_GPRS_GEA3_VALUE;
        }

        /* GEA4: 第二个字节的左起第四个bit */
        if (NAS_MMC_GPRS_GEA4_SUPPORT == (ucGeaSupportCtrl & NAS_MMC_GPRS_GEA4_SUPPORT))
        {
            pstMsCapability->stMsNetworkCapability.aucNetworkCapability[1] |= NAS_MMC_GPRS_GEA4_VALUE;
        }

        /* GEA5: 第二个字节的左起第五个bit */
        if (NAS_MMC_GPRS_GEA5_SUPPORT == (ucGeaSupportCtrl & NAS_MMC_GPRS_GEA5_SUPPORT))
        {
            pstMsCapability->stMsNetworkCapability.aucNetworkCapability[1] |= NAS_MMC_GPRS_GEA5_VALUE;
        }

        /* GEA6: 第二个字节的左起第六个bit */
        if (NAS_MMC_GPRS_GEA6_SUPPORT == (ucGeaSupportCtrl & NAS_MMC_GPRS_GEA6_SUPPORT))
        {
            pstMsCapability->stMsNetworkCapability.aucNetworkCapability[1] |= NAS_MMC_GPRS_GEA6_VALUE;
        }

        /* GEA7: 第二个字节的左起第七个bit */
        if (NAS_MMC_GPRS_GEA7_SUPPORT == (ucGeaSupportCtrl & NAS_MMC_GPRS_GEA7_SUPPORT))
        {
            pstMsCapability->stMsNetworkCapability.aucNetworkCapability[1] |= NAS_MMC_GPRS_GEA7_VALUE;
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadNetworkCapabilityNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_NetworkCapability
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011年7月14日
   作    者   : z00161729
   修改内容   : 新生成函数

 2.日    期   : 2011年8月19日
   作    者   : w00167002
   修改内容   : V7R1 PHASEII 重构: 内存分配赋值越界，导致崩溃
 3.日    期   : 2012年8月10日
   作    者   : L00171473
   修改内容   : DTS2012082204471, TQE清理
 4.日    期   : 2013年05月20日
   作    者   : m00217266
   修改内容   : nv项拆分
*****************************************************************************/
VOS_VOID NAS_MMC_ReadNetworkCapabilityNvim(VOS_VOID)
{
    NAS_MMC_NVIM_NETWORK_CAPABILITY_STRU                    stNetworkCap;/*network capability*/

    VOS_UINT32                          ulLen;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;


    ulLen = 0;
    PS_MEM_SET(&stNetworkCap, 0x00, sizeof(NAS_MMC_NVIM_NETWORK_CAPABILITY_STRU));

    pstMsCapability = NAS_MML_GetMsCapability();
    (VOS_VOID)NV_GetLength(en_NV_Item_NetworkCapability, &ulLen);

    if (ulLen > (NAS_MML_MAX_NETWORK_CAPABILITY_LEN + 1))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadNetworkCapabilityNvim():WARNING: en_NV_Item_NetworkCapability length Error");
        return;
    }
    else
    {
        if(NV_OK != NV_Read (en_NV_Item_NetworkCapability, &stNetworkCap, ulLen))
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadNetworkCapabilityNvim():en_NV_Item_NetworkCapability Error");
            return;
        }
    }

    /* nv中aucNetworkCapability[0]存的长度为networkCapbility长度 + networkCapbility值*/
    pstMsCapability->stMsNetworkCapability.ucNetworkCapabilityLen = stNetworkCap.aucNetworkCapability[0];

    if (pstMsCapability->stMsNetworkCapability.ucNetworkCapabilityLen > NAS_MML_MAX_NETWORK_CAPABILITY_LEN)
    {
        pstMsCapability->stMsNetworkCapability.ucNetworkCapabilityLen = NAS_MML_MAX_NETWORK_CAPABILITY_LEN;
    }

    /* 存贮网络能力 */
    PS_MEM_CPY(&pstMsCapability->stMsNetworkCapability.aucNetworkCapability[0],
               &(stNetworkCap.aucNetworkCapability[1]),
               pstMsCapability->stMsNetworkCapability.ucNetworkCapabilityLen);

    /* 根据en_NV_Item_GEA_SUPPORT_CTRL更新network capability的GEA的值 */
    NAS_MMC_UpdateNetworkCapabilityGeaValue();
    return;
}

/* Added by w00176964 for 短信支持能力和UC2能力NV优化, 2013-3-11, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUcs2CustomizationNvim
 功能描述  : 从NV中获取NV项: NV_Item_UCS2_Customization
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年3月11日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年5月17日
   作    者   : l00167671
   修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUcs2CustomizationNvim(VOS_VOID)
{
    NAS_MML_MS_CAPACILITY_INFO_STRU                        *pstMsCapability = VOS_NULL_PTR;
    VOS_UINT32                                              ulDataLen;
    VOS_UINT32                                              ulResult;
    NAS_MMC_NVIM_UCS2_CUSTOMIZATION_STRU                    stUcs2Customization;

    ulDataLen       = 0;
    pstMsCapability = NAS_MML_GetMsCapability();

    stUcs2Customization.usUcs2Customization = NAS_MMC_UCS2_NO_PREFER;

    (VOS_VOID)NV_GetLength(en_NV_Item_UCS2_Customization, &ulDataLen);
    if (ulDataLen > sizeof(stUcs2Customization))
    {
        return;
    }

    ulResult = NV_Read(en_NV_Item_UCS2_Customization, &stUcs2Customization, ulDataLen);

    /* 读取失败，默认 the ME has no preference between the use of the default alphabet and the use of UCS2 */
    if ( NV_OK != ulResult )
    {
        stUcs2Customization.usUcs2Customization = NAS_MMC_UCS2_NO_PREFER;
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadUcs2CustomizationNvim():en_NV_Item_UCS2_Customization Error");
    }

    /* 更新classmark2中的UCS2能力,更新ms network capability中的UCS2的能力 */
    if (NAS_MMC_UCS2_NO_PREFER == stUcs2Customization.usUcs2Customization)
    {
        pstMsCapability->aucClassmark2[3] |= 0x10;
        pstMsCapability->stMsNetworkCapability.aucNetworkCapability[0] |= 0x10;
    }
    else
    {
        pstMsCapability->aucClassmark2[3] &= 0xef;
        pstMsCapability->stMsNetworkCapability.aucNetworkCapability[0] &= 0xef;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadCloseSmsCapabilityConfigNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_Close_SMS_Capability_Config
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年3月11日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年5月17日
   作    者   : l00167671
   修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadCloseSmsCapabilityConfigNvim(VOS_VOID)
{
    NAS_MML_MS_CAPACILITY_INFO_STRU                        *pstMsCapability = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;
    NAS_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU                  stCloseSmsCapabilityCfg;
    VOS_UINT32                                              ulRet;

    ulLength        = 0;

    pstMsCapability = NAS_MML_GetMsCapability();

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_Close_SMS_Capability_Config, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCloseSmsCapabilityConfigNvim():en_NV_Item_Close_SMS_Capability_Config length Error");
        return;
    }

    ulRet = NV_Read(en_NV_Item_Close_SMS_Capability_Config,
                   &stCloseSmsCapabilityCfg,
                    ulLength);

    /* 读取关闭短信定制NV失败,默认不关闭短信功能 */
    if (NV_OK != ulRet)
    {
        stCloseSmsCapabilityCfg.ucActFlg = VOS_FALSE;

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCloseSmsCapabilityConfigNvim():en_NV_Item_CLOSE_SMS_Capability_Config Failed");
    }

    /* 更新ms network capability中的CS/PS的短信支持能力,更新class mark2中的PS短信能力 */
    if (VOS_TRUE == stCloseSmsCapabilityCfg.ucActFlg)
    {
        pstMsCapability->stMsNetworkCapability.aucNetworkCapability[0] &= 0x9f;
        pstMsCapability->aucClassmark2[2] &= 0xf7;
    }
    else
    {
        pstMsCapability->stMsNetworkCapability.aucNetworkCapability[0] |= 0x60;
        pstMsCapability->aucClassmark2[2] |= 0x08;
    }

    return;
}
/* Added by w00176964 for 短信支持能力和UC2能力NV优化, 2013-3-11, end */


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadLteRoamConfigNvim
 功能描述  : 从NV中获取LTE国际漫游配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月6日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : DTS2012042403564:读取NV先读取长度
  3.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadLteRoamConfigNvim(VOS_VOID)
{
    NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU            stLteRoamNvCfg;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              aulRoamEnabledMccList[5];


    ulLength = 0;

    PS_MEM_SET(&stLteRoamNvCfg,       0x00, sizeof(NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU));
    PS_MEM_SET(aulRoamEnabledMccList, 0x00, sizeof(aulRoamEnabledMccList));

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_Lte_Internation_Roam_Config, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteRoamConfigNvim():WARNING: en_NV_Item_Lte_Internation_Roam_Config length Error");
        return;
    }

    if ( NV_OK != NV_Read(en_NV_Item_Lte_Internation_Roam_Config,
                          &stLteRoamNvCfg,
                           ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteRoamConfigNvim(): en_NV_Item_Lte_Internation_Roam_Config Error");
        return;
    }

    PS_MEM_CPY(aulRoamEnabledMccList, stLteRoamNvCfg.aucRoamEnabledMccList, sizeof(aulRoamEnabledMccList));

    /* 设置当前LTE国际漫游是否允许 */
    NAS_MML_SetLteRoamAllowedFlg(stLteRoamNvCfg.ucLteRoamAllowedFlg);

    /* 设置允许LTE漫游的国家码 */
    NAS_MML_SetRoamEnabledMccList(aulRoamEnabledMccList);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadLNasReleaseNvim
 功能描述  : 从NV中读取L协议版本
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年12月24日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2015年4月18日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_ReadLNasReleaseNvim(VOS_VOID)
{
    LNAS_LMM_NV_NAS_RELEASE_STRU        stNvNasRelease;
    VOS_UINT32                          ulLength;
    NAS_MML_MS_3GPP_REL_STRU           *pstMs3GppRel = VOS_NULL_PTR;

    ulLength     = 0;
    pstMs3GppRel = NAS_MML_GetMs3GppRel();

    pstMs3GppRel->enLteNasRelease = NAS_MML_3GPP_REL_R9;

    /* 获取NV EN_NV_ID_NAS_RELEASE 长度 */
    (VOS_VOID)NV_GetLength(EN_NV_ID_NAS_RELEASE, &ulLength);

    if (ulLength > sizeof(LNAS_LMM_NV_NAS_RELEASE_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLNasReleaseNvim():WARNING: EN_NV_ID_NAS_RELEASE length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(EN_NV_ID_NAS_RELEASE,
                         &stNvNasRelease, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadLNasReleaseNvim(): EN_NV_ID_NAS_RELEASE Error");
        return;
    }

    if (VOS_TRUE == stNvNasRelease.bitOpReleaseName)
    {
        if (0x00000b00 <= stNvNasRelease.ulReleaseName)
        {
            pstMs3GppRel->enLteNasRelease = NAS_MML_3GPP_REL_R11;
            return;
        }

        if (0x00000a00 <= stNvNasRelease.ulReleaseName)
        {
            pstMs3GppRel->enLteNasRelease = NAS_MML_3GPP_REL_R10;
            return;
        }
    }


    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadRPLMNConfigNvim
 功能描述  : 从NV中获取LTE国际漫游配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月24日
    作    者   : t00173447
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadRPLMNConfigNvim(VOS_VOID)
{
    NAS_MMC_NVIM_ROAM_SEARCH_RPLMN_CFG_STRU            stRoamPlmnSearchNvCfg;
    VOS_UINT32                                         ulLength = 0;

    PS_MEM_SET(&stRoamPlmnSearchNvCfg, 0x00, sizeof(NAS_MMC_NVIM_ROAM_SEARCH_RPLMN_CFG_STRU));

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_Roam_Search_Rplmn_Config, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_ROAM_SEARCH_RPLMN_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteRoamConfigNvim():WARNING: en_NV_Item_Roam_Search_Rplmn_Config length Error");
        return;
    }

    if ( NV_OK != NV_Read(en_NV_Item_Roam_Search_Rplmn_Config,
                          &stRoamPlmnSearchNvCfg,
                           ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteRoamConfigNvim(): en_NV_Item_Roam_Search_Rplmn_Config Error");
        return;
    }

    /*保存漫游先搜RPLMN标识*/
    NAS_MML_SetRoamRplmnSearchFlg(stRoamPlmnSearchNvCfg.ucRoamRplmnflg);
    /*保存国内Mcc列表*/
    NAS_MML_SetNationalMCCList(stRoamPlmnSearchNvCfg.aucRoamEnabledMccList);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadDisableLTEOnBandConfigNvim
 功能描述  : 从NV中获取LTE国际漫游配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月24日
    作    者   : t00173447
    修改内容   : 新生成函数
  2.日    期   : 2014年11月27日
    作    者   : s00217060
    修改内容   : 9251 NV项废弃，新增3001 NV，配合接入层修改
*****************************************************************************/
VOS_VOID NAS_MMC_ReadSBMCustomDualIMSIConfigNvim(VOS_VOID)
{
    /* en_NV_Item_SBM_CUSTOM_DUAL_IMSI-->en_NV_Item_SBM_CUSTOM_DUAL_IMSI_NEW
       NVIM_SBM_CUSTOM_DUAL_IMSI_STRU -->NVIM_SBM_CUSTOM_DUAL_IMSI_STRU_NEW */
    NVIM_SBM_CUSTOM_DUAL_IMSI_STRU_NEW                      stSBMDualimsiNvCfg;
    VOS_UINT32                                              ulLength;
    ulLength = 0;

    PS_MEM_SET(&stSBMDualimsiNvCfg, 0x00, sizeof(NVIM_SBM_CUSTOM_DUAL_IMSI_STRU_NEW));

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_SBM_CUSTOM_DUAL_IMSI_NEW, &ulLength);

    if (ulLength > sizeof(NVIM_SBM_CUSTOM_DUAL_IMSI_STRU_NEW))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSBMCustomDualIMSIConfigNvim():WARNING: en_NV_Item_SBM_CUSTOM_DUAL_IMSI_NEW length Error");
        return;
    }

    if ( NV_OK != NV_Read(en_NV_Item_SBM_CUSTOM_DUAL_IMSI_NEW,
                          &stSBMDualimsiNvCfg,
                           ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSBMCustomDualIMSIConfigNvim(): en_NV_Item_SBM_CUSTOM_DUAL_IMSI_NEW Error");
        return;
    }

    /*保存软银定制开关*/
    NAS_MML_SetDisableLTEOnBandFlg(stSBMDualimsiNvCfg.ucSbmCustomDualImsiFlg);

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ReadDailRejectConfigNvim
 功能描述  : 从NV中获取拨号被拒配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月6日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年4月25日
    作    者   : w00176964
    修改内容   : DTS2012042403564:读取NV先读取长度
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  4.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadDailRejectConfigNvim(VOS_VOID)
{
    NAS_MMC_NVIM_DAIL_REJECT_CFG_STRU   stDellRejectCfg;
    VOS_UINT32                          ulLength;


    stDellRejectCfg.ucEnableFlg = VOS_FALSE;


    ulLength = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_Dail_Reject_Config, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_DAIL_REJECT_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadDailRejectConfigNvim():WARNING: en_NV_Item_Dail_Reject_Config length Error");
        return;
    }

    if ( NV_OK != NV_Read(en_NV_Item_Dail_Reject_Config,
                          &stDellRejectCfg,
                          ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadDellRejectConfigNvim(): en_NV_Item_Dell_Reject_Config Error");
        return;
    }

    /* 设置当前拨号被拒是否可用 */
    NAS_MML_SetDailRejectCfg(stDellRejectCfg.ucEnableFlg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadMsModeNvim
 功能描述  : 从NVIM中获取手机模式信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月18日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年4月23日
    作    者   : w00166186
    修改内容   : DTS2012033104746,关机状态设置服务域为ANY不生效
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  4.日    期   : 2013年05月20日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
VOS_VOID  NAS_MMC_ReadMsModeNvim( VOS_VOID )
{
    NAS_NVIM_MS_CLASS_STRU              stMsClass;
    VOS_UINT32                          ulLength;

    ulLength        = 0;

    PS_MEM_SET(&stMsClass, 0x00, sizeof(NAS_NVIM_MS_CLASS_STRU));
    stMsClass.ucMsClass = NAS_MML_MS_MODE_BUTT;

    (VOS_VOID)NV_GetLength(en_NV_Item_MMA_MsClass, &ulLength);
    if (ulLength > sizeof(NAS_NVIM_MS_CLASS_STRU))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_MMA_MsClass, &stMsClass, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadMsModeNvim():en_NV_Item_MMA_MsClass NV Read Fail!");
        return;
    }

    /* NV中的取值定义( 0：只支持CS域手机；1：NV_MS_CLASS_CG，只支持PS域手机；
       2：NV_MS_CLASS_A，支持CS/PS域手机（默认值）)与MML中的不一致，需要转换*/

    if ((NV_MS_MODE_CS_ONLY == stMsClass.ucMsClass)
    ||  (NV_MS_MODE_ANY == stMsClass.ucMsClass))
    {
        NAS_MML_SetMsMode(NAS_MML_MS_MODE_CS_ONLY);
    }

    else if (NV_MS_MODE_PS_ONLY == stMsClass.ucMsClass)
    {
        NAS_MML_SetMsMode(NAS_MML_MS_MODE_PS_ONLY);
    }
    else if (NV_MS_MODE_CS_PS == stMsClass.ucMsClass)
    {
        NAS_MML_SetMsMode(NAS_MML_MS_MODE_PS_CS);
    }
    else
    {
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUserSetBandNvim
 功能描述  : 从NV中获取当前用户设置的G/W/L频段
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月19日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUserSetBandNvim(VOS_VOID)
{
    NVIM_UE_SUPPORT_FREQ_BAND_STRU                          stUserSetFreqBand;
    NAS_MML_MS_BAND_INFO_STRU                              *pstUserSetBand = VOS_NULL_PTR;
    LTE_BAND_STRU                                           stLteBand;


    PS_MEM_SET(&stUserSetFreqBand, 0x00, sizeof(stUserSetFreqBand));
    PS_MEM_SET(&stLteBand,         0x00, sizeof(stLteBand));

    pstUserSetBand = NAS_MML_GetMsSupportBand();

    /* 读用户设置的GU频段 NV项 */
    if (NV_OK != NV_Read(en_NV_Item_Support_Freqbands,
                         &stUserSetFreqBand, sizeof(NVIM_UE_SUPPORT_FREQ_BAND_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadUserSetBandNvim():en_NV_Item_Support_Freqbands Error");
        return;
    }

    pstUserSetBand->unGsmBand.ulBand   = stUserSetFreqBand.ulGsmBand;
    pstUserSetBand->unWcdmaBand.ulBand = stUserSetFreqBand.ulWcdmaBand;

    /* 读用户设置的LTE频段 NV项 */
    if (NV_OK != NV_Read(en_NV_Item_USER_SET_LTEBANDS,
                         &stLteBand, sizeof(LTE_BAND_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadUserSetBandNvim():en_NV_Item_USER_SET_LTEBANDS Error");
        return;
    }

    pstUserSetBand->stLteBand = stLteBand;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUseSingleRplmnFlagNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_Use_Single_Rplmn_When_Area_Lost.
             FT Orange TA问题新增,丢网时到另一模式搜索同一个Rplmn
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2010年7月19日
    作    者   : z00161729
    修改内容   : 新增函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年05月20日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUseSingleRplmnFlagNvim(VOS_VOID)
{
    NAS_MMC_NVIM_USE_SINGLE_RPLMN_STRU  stUseSingleRplmnFlag;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength        = 0;


    stUseSingleRplmnFlag.usUseSingleRplmnFlag = NAS_MMC_NV_ITEM_ACTIVE;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    (VOS_VOID)NV_GetLength(en_NV_Item_Use_Single_Rplmn_When_Area_Lost, &ulLength);
    if (ulLength > sizeof(stUseSingleRplmnFlag))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_Use_Single_Rplmn_When_Area_Lost,
                         &stUseSingleRplmnFlag, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadUseSingleRplmnFlagNvim():en_NV_Item_Use_Single_Rplmn_When_Area_Lost Error");

        return;
    }

    if ((stUseSingleRplmnFlag.usUseSingleRplmnFlag != NAS_MMC_NV_ITEM_DEACTIVE)
     && (stUseSingleRplmnFlag.usUseSingleRplmnFlag != NAS_MMC_NV_ITEM_ACTIVE))
    {
        return;
    }

    /* usUseSingleRplmnFlag为0表WCDMA和GSM存储各自注册的RPLMN */
    if (NAS_MMC_NV_ITEM_DEACTIVE == stUseSingleRplmnFlag.usUseSingleRplmnFlag)
    {
        /* 支持双RPLMN */
        pstRplmnCfgInfo->ucMultiRATRplmnFlg = VOS_TRUE;
    }
    else
    {
        pstRplmnCfgInfo->ucMultiRATRplmnFlg = VOS_FALSE;
    }


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadRplmnWithRatNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_RPlmnWithRat
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月19日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年1月28日
    作    者   : w00176964
    修改内容   : DTS2013012802243:单板首次升级自动注册到TDS网络
  4.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadRplmnWithRatNvim(VOS_VOID)
{
    NAS_NVIM_RPLMN_WITH_RAT_STRU        stRplmn;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList = VOS_NULL_PTR;

    pstRatPrioList           = NAS_MML_GetMsPrioRatList();


    stRplmn.stGRplmn.ulMcc          = NAS_MML_INVALID_MCC;
    stRplmn.stGRplmn.ulMnc          = NAS_MML_INVALID_MNC;
    stRplmn.stWRplmn.ulMcc          = NAS_MML_INVALID_MCC;
    stRplmn.stWRplmn.ulMnc          = NAS_MML_INVALID_MNC;
    stRplmn.ucLastRplmnRat          = NAS_MML_NET_RAT_TYPE_BUTT;
    stRplmn.ucLastRplmnRatEnableFlg = VOS_FALSE;

    pstRplmnCfgInfo   = NAS_MML_GetRplmnCfg();

    if(NV_OK != NV_Read (en_NV_Item_RPlmnWithRat, &stRplmn, sizeof(NAS_NVIM_RPLMN_WITH_RAT_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRplmnWithRatNvim(): en_NV_Item_RPlmnWithRat Error");
        return;
    }

    if ((stRplmn.ucLastRplmnRatEnableFlg != NAS_MMC_NV_ITEM_DEACTIVE)
     && (stRplmn.ucLastRplmnRatEnableFlg != NAS_MMC_NV_ITEM_ACTIVE))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRplmnWithRatNvim(): NV parameter Error");
        return;
    }

    pstRplmnCfgInfo->ucLastRplmnRatFlg = stRplmn.ucLastRplmnRatEnableFlg;

    /* 单板首次升级此值为默认的0XFF,此时需要按照默认的SYSCFGEX的接入优先级取
       最高优先级 */
    if ((NAS_MML_NET_RAT_TYPE_INVALID == stRplmn.ucLastRplmnRat)
     || (NAS_MML_NET_RAT_TYPE_BUTT    == stRplmn.ucLastRplmnRat))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRplmnWithRatNvim(): RplmnRat invalid change to RatPrio");
    
        pstRplmnCfgInfo->enLastRplmnRat = pstRatPrioList->aucRatPrio[0];
    }
    else
    {
        pstRplmnCfgInfo->enLastRplmnRat    = stRplmn.ucLastRplmnRat;
    }

    PS_MEM_CPY(&pstRplmnCfgInfo->stGRplmnInNV, &stRplmn.stGRplmn, sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_CPY(&pstRplmnCfgInfo->stWRplmnInNV, &stRplmn.stWRplmn, sizeof(NAS_MML_PLMN_ID_STRU));


    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadNvimLastRplmnRat
 功能描述  : 从NV中获取NV项LastRplmnRat: en_NV_Item_RPlmnWithRat
 输入参数  : 无
 输出参数  : penNvimLastRplmnRat
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年10月8日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadNvimLastRplmnRat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penNvimLastRplmnRat
)
{
    NAS_NVIM_RPLMN_WITH_RAT_STRU        stRplmn;

    stRplmn.stGRplmn.ulMcc          = NAS_MML_INVALID_MCC;
    stRplmn.stGRplmn.ulMnc          = NAS_MML_INVALID_MNC;
    stRplmn.stWRplmn.ulMcc          = NAS_MML_INVALID_MCC;
    stRplmn.stWRplmn.ulMnc          = NAS_MML_INVALID_MNC;
    stRplmn.ucLastRplmnRat          = NAS_MML_NET_RAT_TYPE_BUTT;
    stRplmn.ucLastRplmnRatEnableFlg = VOS_FALSE;

    if(NV_OK != NV_Read (en_NV_Item_RPlmnWithRat, &stRplmn, sizeof(NAS_NVIM_RPLMN_WITH_RAT_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadNvimLastRplmnRat(): en_NV_Item_RPlmnWithRat Error");
        return;
    }

    if ((stRplmn.ucLastRplmnRatEnableFlg != NAS_MMC_NV_ITEM_DEACTIVE)
     && (stRplmn.ucLastRplmnRatEnableFlg != NAS_MMC_NV_ITEM_ACTIVE))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadNvimLastRplmnRat(): NV parameter Error");
        return;
    }

    *penNvimLastRplmnRat = stRplmn.ucLastRplmnRat;

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_WriteRplmnWithRatNvim
 功能描述  : 写NV: en_NV_Item_RPlmnWithRat
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年8月6日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_WriteRplmnWithRatNvim(VOS_VOID)
{
    NAS_NVIM_RPLMN_WITH_RAT_STRU        stRplmn;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    stRplmn.ucLastRplmnRat          = pstRplmnCfgInfo->enLastRplmnRat;
    stRplmn.stGRplmn.ulMcc          = pstRplmnCfgInfo->stGRplmnInNV.ulMcc;
    stRplmn.stGRplmn.ulMnc          = pstRplmnCfgInfo->stGRplmnInNV.ulMnc;
    stRplmn.stWRplmn.ulMcc          = pstRplmnCfgInfo->stWRplmnInNV.ulMcc;
    stRplmn.stWRplmn.ulMnc          = pstRplmnCfgInfo->stWRplmnInNV.ulMnc;
    stRplmn.ucLastRplmnRatEnableFlg = pstRplmnCfgInfo->ucLastRplmnRatFlg;

    if(NV_OK != NV_Write(en_NV_Item_RPlmnWithRat, &stRplmn, sizeof(NAS_NVIM_RPLMN_WITH_RAT_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_WriteRplmnWithRatNvim(): en_NV_Item_RPlmnWithRat Error");
    }

    return;
}


#if   (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadTinInfoNvim
 功能描述  : 从NVIM中获取TIN信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月28日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2011年7月18日
    作    者   : z00161729
    修改内容   : V7R1 phase II调整全局变量修改

  3.日    期   : 2011年11月18日
    作    者   : zhoujun /40661
    修改内容   : DTS2011111402309,last imsi保存有问题需要修改
  4.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  5.日    期   : 2013年01月28日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，增加平台不支持LTE时异常保护
  6.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadTinInfoNvim( VOS_VOID )
{
    /* Modified by l00167671 for NV拆分项目 , 2013-05-17, begin */
    NAS_NVIM_TIN_INFO_STRU          stTinInfo;
    /* Modified by l00167671 for NV拆分项目 , 2013-05-17, end */

    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;


    PS_MEM_SET(&stTinInfo, 0x00, sizeof(stTinInfo));

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* Modified by l00167671 for NV拆分项目 , 2013-05-17, begin */
    if ( NV_OK != NV_Read(en_NV_Item_TIN_INFO,
                          &stTinInfo,
                          sizeof(stTinInfo) ))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadTinInfoNvim(): en_NV_Item_TIN_INFO Error");

        return;
    }
    /* Modified by l00167671 for NV拆分项目 , 2013-05-17, end */

    PS_MEM_CPY(pstRplmnCfgInfo->aucLastImsi, stTinInfo.aucImsi, sizeof(pstRplmnCfgInfo->aucLastImsi));
    pstRplmnCfgInfo->enTinType = (NAS_MML_TIN_TYPE_ENUM_UINT8)stTinInfo.ucTinType;

    /* 如果平台不支持LTE，需要对Tin type进行异常保护 */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        if ((NAS_MML_TIN_TYPE_GUTI == pstRplmnCfgInfo->enTinType)
         || (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == pstRplmnCfgInfo->enTinType))
        {
            pstRplmnCfgInfo->enTinType = NAS_MML_TIN_TYPE_INVALID;
        }
    }

    return;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_WriteTinInfoNvim
 功能描述  : 更新TIN INFO的内容到NVIM
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月18日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数
 2.日    期   : 2013年5月17日
   作    者   : l00167671
   修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID  NAS_MMC_WriteTinInfoNvim(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType,
    VOS_UINT8                          *pucImsi
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    /* Modified by l00167671 for NV拆分项目 , 2013-05-17, begin */
    NAS_NVIM_TIN_INFO_STRU              stTinInfo;
    /* Modified by l00167671 for NV拆分项目 , 2013-05-17, end */

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /*
        The following EMM parameter shall be stored in a non-volatile memory in the
        ME together with the IMSI from the USIM:
        -   TIN.
        This EMM parameter can only be used if the IMSI from the USIM matches the
        IMSI stored in the non-volatile memory of the ME; else the UE shall delete
        the EMM parameter.
    */

    /* 先更新MML的参数 */
    pstRplmnCfgInfo->enTinType  = enTinType;
    PS_MEM_CPY(pstRplmnCfgInfo->aucLastImsi, pucImsi, sizeof(pstRplmnCfgInfo->aucLastImsi));

    /* 再更新NVIM中的参数 */
    stTinInfo.ucTinType        = pstRplmnCfgInfo->enTinType;
    PS_MEM_CPY(stTinInfo.aucImsi, pstRplmnCfgInfo->aucLastImsi, sizeof(stTinInfo.aucImsi));
    PS_MEM_SET(stTinInfo.aucReserve, 0, sizeof(stTinInfo.aucReserve));

    /* 保存在NVIM中 */
    if (NV_OK != NV_Write (en_NV_Item_TIN_INFO,
                           &stTinInfo,
                           sizeof(stTinInfo)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_WriteTinInfoNvim:Write NV Failed");
    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadLteCsServiceConfigNvim
 功能描述  : 从NV中获取L支持的cs业务配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月28日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年3月3日
    作    者   : w00167002
    修改内容   : V7R1C50 CSFB调整:周君检视意见，MML不需要存储NVIM激活标志，
                 减少内存的使用(更改结构体为枚举NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8)
  3.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  4.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadLteCsServiceConfigNvim(VOS_VOID)
{
    NAS_NVIM_LTE_CS_SERVICE_CFG_STRU                        stLteCsServiceCfg;
    VOS_UINT32                                              ulLength;

    ulLength        = 0;


    PS_MEM_SET(&stLteCsServiceCfg, 0x00, sizeof(NAS_NVIM_LTE_CS_SERVICE_CFG_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_Lte_Cs_Service_Config, &ulLength);
    if (ulLength > sizeof(stLteCsServiceCfg))
    {
        return;
    }
    if ( NV_OK != NV_Read(en_NV_Item_Lte_Cs_Service_Config,
                          &stLteCsServiceCfg,
                          ulLength ))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteCsServiceConfigNvim(): en_NV_Item_Lte_Cs_Service_Config Error");
        return;
    }

    /* 如果NV项激活并且值有效，则更新MML中的全局变量 */
    if ((NAS_MMC_NV_ITEM_ACTIVE == stLteCsServiceCfg.ucNvimActiveFlg)
     && (stLteCsServiceCfg.ucLteCsServiceCfg < NAS_MML_LTE_SUPPORT_BUTT))
    {
        /* 设置当前LTE的CS业务配置能力的NV项激活 */
        NAS_MML_SetLteCsServiceCfg(stLteCsServiceCfg.ucLteCsServiceCfg);

#if (VOS_WIN32 == VOS_OS_VER)
        NAS_MML_SetLteCsServiceCfg(NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS);
#endif

        return;
    }

    /* NV无效时设置为  */
    NAS_MML_SetLteCsServiceCfg(NAS_MML_LTE_SUPPORT_BUTT);

#if (VOS_WIN32 == VOS_OS_VER)
        NAS_MML_SetLteCsServiceCfg(NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS);
#endif


    return;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_ReadHoWaitSysinfoTimeLenNvim
 功能描述  : 从NV中获取CSFB HO流程等系统消息时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月14日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadHoWaitSysinfoTimeLenNvim(VOS_VOID)
{
    NAS_MMC_NVIM_HO_WAIT_SYSINFO_TIMER_CFG_STRU             stHoTimerCfg;


    PS_MEM_SET(&stHoTimerCfg, 0x00, sizeof(stHoTimerCfg));

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_Ho_Wait_Sysinfo_Timer_Config,
                         &stHoTimerCfg, sizeof(NAS_MMC_NVIM_HO_WAIT_SYSINFO_TIMER_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadHoWaitSysinfoTimeLenNvim(): en_NV_Item_HO_WAIT_SYSINFO_TIMER_Config Error");
        return;
    }

    /* en_NV_Item_HO_WAIT_SYSINFO_TIMER_Config未使能，则设置等系统消息时间为默认值1s */
    if ( NAS_MMC_NV_ITEM_DEACTIVE == stHoTimerCfg.ucNvimActiveFlg )
    {
        NAS_MML_SetHoWaitSysinfoTimerLen(NAS_MML_HO_WAIT_SYS_INFO_DEFAULT_LEN_VALUE);
        return;
    }

    /* en_NV_Item_HO_WAIT_SYSINFO_TIMER_Config设置等系统消息时间为0，则更新为默认值1s */
    if ( 0 == stHoTimerCfg.ucWaitSysinfoTimeLen )
    {
        NAS_MML_SetHoWaitSysinfoTimerLen(NAS_MML_HO_WAIT_SYS_INFO_DEFAULT_LEN_VALUE);
        return;
    }

    /* 更新MML全局变量中的HO等系统消息的值 */
    NAS_MML_SetHoWaitSysinfoTimerLen(stHoTimerCfg.ucWaitSysinfoTimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND);

    return;
}
#endif
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadCsfbEmgCallLaiChgLauFirstNvim
 功能描述  : 从NV中获取csfb紧急呼叫到GU，MM收到系统消息lai改变先做lau还是
             先进行呼叫等呼叫结束后再做lau标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月14日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadCsfbEmgCallLaiChgLauFirstNvim(VOS_VOID)
{
    NAS_MMC_NVIM_CSFB_EMG_CALL_LAI_CHG_LAU_FIRST_CFG_STRU   stCsfbEmgCallLauFirstCfg;
    VOS_UINT32                                              ulLength;


    PS_MEM_SET(&stCsfbEmgCallLauFirstCfg, 0x00, sizeof(NAS_MMC_NVIM_CSFB_EMG_CALL_LAI_CHG_LAU_FIRST_CFG_STRU));

    ulLength = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_Csfb_Emg_Call_LaiChg_Lau_First_CFG, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_CSFB_EMG_CALL_LAI_CHG_LAU_FIRST_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCsfbEmgCallLaiChgLauFirstNvim():WARNING: en_NV_Item_Csfb_Emergency_Call_LaiChg_Lau_First_CFG length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_Csfb_Emg_Call_LaiChg_Lau_First_CFG,
                         &stCsfbEmgCallLauFirstCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadCsfbEmgCallLaiChgLauFirstNvim(): en_NV_Item_Csfb_Emergency_Call_LaiChg_Lau_First_CFG Error");
        return;
    }

    if (VOS_TRUE == stCsfbEmgCallLauFirstCfg.ucCsfbEmgCallLaiChgLauFirstFlg)
    {
        NAS_MML_SetCsfbEmgCallLaiChgLauFirstFlg(stCsfbEmgCallLauFirstCfg.ucCsfbEmgCallLaiChgLauFirstFlg);
    }

    return;
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */



/*****************************************************************************
 函 数 名  : NAS_MMC_ReadEHPlmnSupportNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_Standard_EHplmn_Support_Flg
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月20日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadEHPlmnSupportNvim(VOS_VOID)
{
    NAS_MMC_NVIM_EHPLMN_SUPPORT_FLG_STRU                    stEHPlmnSupportFlg;
    NAS_MML_HPLMN_CFG_INFO_STRU                            *pstHplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength        = 0;

    stEHPlmnSupportFlg.usEHPlmnSupportFlg = VOS_FALSE;

    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();

    (VOS_VOID)NV_GetLength(en_NV_Item_Standard_EHplmn_Support_Flg, &ulLength);
    if (ulLength > sizeof(stEHPlmnSupportFlg))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_Standard_EHplmn_Support_Flg,
                         &stEHPlmnSupportFlg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadEHPlmnSupportNvim(): en_NV_Item_Standard_EHplmn_Support_Flg Error");
        return;
    }

    if ((NAS_MMC_NV_ITEM_ACTIVE != stEHPlmnSupportFlg.usEHPlmnSupportFlg)
     && (NAS_MMC_NV_ITEM_DEACTIVE != stEHPlmnSupportFlg.usEHPlmnSupportFlg))
    {
        return;
    }

    pstHplmnCfgInfo->ucEhplmnSupportFlg = (VOS_UINT8)stEHPlmnSupportFlg.usEHPlmnSupportFlg;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadActingHPlmnSupportNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_ACTING_PLMN_SUPPORT_FLAG
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012年6月11日
    作    者   : w00166186
    修改内容   : AT&T&DCM项目新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadActingHPlmnSupportNvim(VOS_VOID)
{
    NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU                     stActingHPlmnSupport;
    VOS_UINT32                                              ulLength;


    PS_MEM_SET(&stActingHPlmnSupport, 0x00, sizeof(NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU));
    ulLength = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_ACTING_PLMN_SUPPORT_FLAG, &ulLength);

    if (ulLength > sizeof(NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadActingHPlmnSupportNvim():WARNING: en_NV_Item_ACTING_PLMN_SUPPORT_FLAG length Error");
        return;
    }

    /* 读取ACTING-HPLMN控制NV */
    if (NV_OK != NV_Read(en_NV_Item_ACTING_PLMN_SUPPORT_FLAG,
                         &stActingHPlmnSupport, sizeof(NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadActingHPlmnSupportNvim(): en_NV_Item_ACTING_PLMN_SUPPORT_FLAG Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stActingHPlmnSupport.ucNvimActiveFlg)
    {
        /* 赋值ACTING-HPLMN控制标志 */
        NAS_MML_SetActingHplmnSupportFlg(VOS_TRUE);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadSearchHPlmnFlgAutoModeNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_SrchHplmnFlg_StartOrAreaLostInAutoMode
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2010年7月20日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
  4.日    期   : 2014年3月19日
    作    者   : w00242748
    修改内容   : DTS2014031200137:当NV特性打开时，自动开机或者搜网时，如果首次搜索RPLMN的话，
                 需要将HPLMN/EHPLMN带给接入层。
*****************************************************************************/
VOS_VOID NAS_MMC_ReadSearchHPlmnFlgAutoModeNvim(VOS_VOID)
{
    NAS_MMC_NVIM_AUTO_SEARCH_HPLMN_FLG_STRU                 stHplmnSearchFlg;
    NAS_MML_HPLMN_CFG_INFO_STRU                            *pstHplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength        = 0;

    stHplmnSearchFlg.usAutoSearchHplmnFlg  = 0;

    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();

    (VOS_VOID)NV_GetLength(en_NV_Item_SrchHplmnFlg_StartOrAreaLostInAutoMode, &ulLength);
    if (ulLength > sizeof(stHplmnSearchFlg))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_SrchHplmnFlg_StartOrAreaLostInAutoMode,
                         &stHplmnSearchFlg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadSearchHPlmnFlgAutoModeNvim():en_NV_Item_SrchHplmnFlg_StartOrAreaLostInAutoMode Error");
        return;
    }

    if (stHplmnSearchFlg.usAutoSearchHplmnFlg >= NAS_MML_SEARCH_HPLMN_FLG_TYPE_BUTT )
    {
        return;
    }

    pstHplmnCfgInfo->enAutoSearchHplmnFlg = (VOS_UINT8)stHplmnSearchFlg.usAutoSearchHplmnFlg;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadAddEhplmnWhenSrchHplmnFlgNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_SrchHplmnFlg_StartOrAreaLostInAutoMode
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :

  1.日    期   : 2015年9月30日
    作    者   : c00318887
    修改内容   : 新建函数
*****************************************************************************/

VOS_VOID NAS_MMC_ReadAddEhplmnWhenSrchHplmnNvim(VOS_VOID)
{
    NAS_NVIM_ADD_EHPLMN_WHEN_SRCH_HPLMN_CFG_STRU            stAddEhplmnWhenSrchHplmnFlag;
    NAS_MML_HPLMN_CFG_INFO_STRU                            *pstHplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength                                                = 0;

    stAddEhplmnWhenSrchHplmnFlag.ucActiveFlag               = VOS_FALSE;

    pstHplmnCfgInfo                                         = NAS_MML_GetHplmnCfg();

    (VOS_VOID)NV_GetLength(en_NV_Item_Add_EHPLMN_WHEN_SRCH_HPLMN_CFG, &ulLength);
    if (ulLength > sizeof(stAddEhplmnWhenSrchHplmnFlag))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_Add_EHPLMN_WHEN_SRCH_HPLMN_CFG,
                         &stAddEhplmnWhenSrchHplmnFlag, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadAddEhplmnWhenSrchHplmnNvim():en_NV_Item_Add_EHPLMN_WHEN_SRCH_HPLMN_CFG Error");
        return;
    }

    if ((NAS_MMC_NV_ITEM_ACTIVE   != stAddEhplmnWhenSrchHplmnFlag.ucActiveFlag)
     && (NAS_MMC_NV_ITEM_DEACTIVE != stAddEhplmnWhenSrchHplmnFlag.ucActiveFlag))
    {
        return;
    }

    pstHplmnCfgInfo->ucAddEhplmnWhenSrchHplmnFlg            = stAddEhplmnWhenSrchHplmnFlag.ucActiveFlag;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadSearchHPlmnFlgManualModeNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_SrchHplmnFlg_StartInManualMode
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2010年7月20日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadSearchHPlmnFlgManualModeNvim(VOS_VOID)
{
    NAS_MMC_NVIM_MANUAL_SEARCH_HPLMN_FLG_STRU               stManualSearchHplmnFlg;
    NAS_MML_HPLMN_CFG_INFO_STRU                            *pstHplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength        = 0;


    stManualSearchHplmnFlg.usManualSearchHplmnFlg = VOS_TRUE;

    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();

    (VOS_VOID)NV_GetLength(en_NV_Item_SrchHplmnFlg_StartInManualMode, &ulLength);
    if (ulLength > sizeof(stManualSearchHplmnFlg))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_SrchHplmnFlg_StartInManualMode,
                         &(stManualSearchHplmnFlg), ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSearchHPlmnFlgManualModeNvim():en_NV_Item_SrchHplmnFlg_StartInManualMode Error");
        return;
    }

    if ((NAS_MMC_NV_ITEM_ACTIVE != stManualSearchHplmnFlg.usManualSearchHplmnFlg)
     && (NAS_MMC_NV_ITEM_DEACTIVE != stManualSearchHplmnFlg.usManualSearchHplmnFlg))
    {
        return;
    }

    pstHplmnCfgInfo->ucManualSearchHplmnFlg = (VOS_UINT8)stManualSearchHplmnFlg.usManualSearchHplmnFlg;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadSearchHplmnFlgPowerOnNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_SearchHplmnAtPowerOn
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月20日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadSearchHplmnFlgPowerOnNvim(VOS_VOID)
{
    NAS_MMC_NVIM_HPLMN_SEARCH_POWERON_STRU                  stHplmnSearchPowerOn;
    NAS_MML_HPLMN_CFG_INFO_STRU                            *pstHplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength        = 0;


    stHplmnSearchPowerOn.ucHplmnSearchPowerOn = VOS_FALSE;

    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();

    (VOS_VOID)NV_GetLength(en_NV_Item_SearchHplmnAtPowerOn, &ulLength);
    if (ulLength > sizeof(stHplmnSearchPowerOn))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_SearchHplmnAtPowerOn, &stHplmnSearchPowerOn, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSearchHplmnFlgPowerOnNvim():en_NV_Item_SearchHplmnAtPowerOn Error");
        return;
    }

    if ((NAS_MMC_NV_ITEM_ACTIVE != stHplmnSearchPowerOn.ucHplmnSearchPowerOn)
     && (NAS_MMC_NV_ITEM_DEACTIVE != stHplmnSearchPowerOn.ucHplmnSearchPowerOn))
    {
        return;
    }

    pstHplmnCfgInfo->ucHplmnSearchPowerOn = stHplmnSearchPowerOn.ucHplmnSearchPowerOn;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadEnhancedHPlmnSearchFlagNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_Enhanced_Hplmn_Srch_Flg
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月20日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
****************************************************************************/
VOS_VOID NAS_MMC_ReadEnhancedHPlmnSearchFlagNvim(VOS_VOID)
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU                        *pstBgSearchCfg = VOS_NULL_PTR;
    NAS_MMC_NVIM_ENHANCED_HPLMN_SRCH_FLG_STRU               stEnhancedHplmnSrchFlg;
    VOS_UINT32                                              ulLength;

    ulLength        = 0;


    stEnhancedHplmnSrchFlg.usEnhancedHplmnSrchFlg = VOS_FALSE;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();
    (VOS_VOID)NV_GetLength(en_NV_Item_Enhanced_Hplmn_Srch_Flg, &ulLength);
    if (ulLength > sizeof(stEnhancedHplmnSrchFlg))
    {
        return;
    }
    if (NV_OK != NV_Read(en_NV_Item_Enhanced_Hplmn_Srch_Flg, &stEnhancedHplmnSrchFlg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_ReadEnhancedHPlmnSearchFlagNvim(): en_NV_Item_Enhanced_Hplmn_Srch_Flg Error");
        return;
    }

    if ((NAS_MMC_NV_ITEM_ACTIVE != stEnhancedHplmnSrchFlg.usEnhancedHplmnSrchFlg)
     && (NAS_MMC_NV_ITEM_DEACTIVE != stEnhancedHplmnSrchFlg.usEnhancedHplmnSrchFlg))
    {
        return;
    }

    pstBgSearchCfg->ucEnhancedHplmnSrchFlg = (VOS_UINT8)stEnhancedHplmnSrchFlg.usEnhancedHplmnSrchFlg;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadSpecialRoamFlgNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_Special_Roam_Flag
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月20日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadSpecialRoamFlgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_SPECIAL_ROAM_STRU      stSpecialRoam;
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength        = 0;


    stSpecialRoam.ucStatus         = NAS_MMC_NV_ITEM_DEACTIVE;
    stSpecialRoam.ucSpecialRoamFlg = VOS_FALSE;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();
    (VOS_VOID)NV_GetLength(en_NV_Item_Special_Roam_Flag, &ulLength);
    if (ulLength > sizeof(stSpecialRoam))
    {
        return;
    }
    if (NV_OK != NV_Read (en_NV_Item_Special_Roam_Flag, &stSpecialRoam, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSpecialRoamFlgNvim():en_NV_Item_Special_Roam_Flag Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stSpecialRoam.ucStatus)
    {
        pstBgSearchCfg->ucSpecialRoamFlg = stSpecialRoam.ucSpecialRoamFlg;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadNetworkNameNvim
 功能描述  : 从NV项en_NV_Item_Network_Name_From_MM_Info中读取保存的网络通过MM INFO下发的长短网络名
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2010年7月26日
   作    者   : zhoujun \40661
   修改内容   : 新生成函数
 2.日    期   : 2013年5月17日
   作    者   : l00167671
   修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadNetworkNameNvim( VOS_VOID )
{
    NAS_MMC_NVIM_OPERATOR_NAME_INFO_STRU                    stNvimOperatorName;
    NAS_MML_OPERATOR_NAME_INFO_STRU                        *pstOperatorName;

    pstOperatorName = NAS_MML_GetOperatorNameInfo();

    if(NV_OK != NV_Read (en_NV_Item_Network_Name_From_MM_Info, &stNvimOperatorName, sizeof(stNvimOperatorName)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadNetworkNameNvim:WARNING: Read NV Item Fail.");
        return;
    }

    pstOperatorName->stOperatorPlmnId.ulMcc = stNvimOperatorName.stOperatorPlmnId.ulMcc;
    pstOperatorName->stOperatorPlmnId.ulMnc = stNvimOperatorName.stOperatorPlmnId.ulMnc;
    PS_MEM_CPY(pstOperatorName->aucOperatorNameLong, stNvimOperatorName.aucOperatorNameLong, NAS_NVIM_MAX_OPER_LONG_NAME_LEN);
    PS_MEM_CPY(pstOperatorName->aucOperatorNameShort, stNvimOperatorName.aucOperatorNameShort, NAS_NVIM_MAX_OPER_SHORT_NAME_LEN);

}

/*****************************************************************************
 函 数 名  : NAS_MML_IsInNvEplmnList
 功能描述  : 判断PLMN ID是否在NV中的EPLMN LIST列表中
 输入参数  : pstPlmnId:需要判断的PLMN ID
             ucPlmnNum:PLMN ID个数
             pstPlmnIdList:PLMN ID列表
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID在禁止列表中
             VOS_FALSE : PLMN ID不在禁止列表中
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年02月15日
   作    者   : w00176964
   修改内容   : 新生成函数

  2.日    期   : 2012年2月15日
    作    者   : z40661
    修改内容   : 该函数以前在MML中,将其放入MMC中，MML不需要包含nviminterfac-
                 e.h
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsInNvEplmnList(
    NVIM_PLMN_VALUE_STRU               *pstPlmnId,
    VOS_UINT8                           ucPlmnNum,
    NVIM_PLMN_VALUE_STRU               *pstPlmnIdList
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < ucPlmnNum ; i++ )
    {
        if ( (pstPlmnId->ucMcc[0] == pstPlmnIdList[i].ucMcc[0])
          && (pstPlmnId->ucMcc[1] == pstPlmnIdList[i].ucMcc[1])
          && (pstPlmnId->ucMcc[2] == pstPlmnIdList[i].ucMcc[2])
          && (pstPlmnId->ucMnc[0] == pstPlmnIdList[i].ucMnc[0])
          && (pstPlmnId->ucMnc[1] == pstPlmnIdList[i].ucMnc[1])
          && (pstPlmnId->ucMnc[2] == pstPlmnIdList[i].ucMnc[2]) )
        {
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertMmlPlmnIdToNvimEquPlmn
 功能描述  : 将MML格式的PlmnID转换为Nvim的Eplmn
              23002f(MML的格式 Mcc:0x000302,Mnc:0x0f0200)-->2,3,0,0,2,f
 输入参数  : pstPlmnId: MML的PLMN ID
 输出参数  : pstNvimPlmnId: NvimEPlmn格式
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年03月15日
   作    者   : l00130025
   修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
*****************************************************************************/
VOS_VOID NAS_MMC_ConvertMmlPlmnIdToNvimEquPlmn(
    NAS_MML_PLMN_ID_STRU               *pstMmlPlmnId,
    NVIM_PLMN_VALUE_STRU               *pstNvimPlmnId
)
{
    /* 转化MCC */
    pstNvimPlmnId->ucMcc[0] = (VOS_UINT8)(pstMmlPlmnId->ulMcc & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMcc[1] = (VOS_UINT8)((pstMmlPlmnId->ulMcc >> 8) & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMcc[2] = (VOS_UINT8)((pstMmlPlmnId->ulMcc >> 16) & NAS_MML_OCTET_LOW_FOUR_BITS);

    /* 转化MNC */
    pstNvimPlmnId->ucMnc[0] = (VOS_UINT8)(pstMmlPlmnId->ulMnc & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMnc[1] = (VOS_UINT8)((pstMmlPlmnId->ulMnc >> 8) & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMnc[2] = (VOS_UINT8)((pstMmlPlmnId->ulMnc >> 16) & NAS_MML_OCTET_LOW_FOUR_BITS);

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertMmlEquListToNvimEquPlmnList
 功能描述  : 将MML格式的Eplmn列表转换为Nvim的Eplmn列表
 输入参数  : pstMmlEPlmnList: MML的EplmnList
 输出参数  : pstNvimEPlmnList:Nvim格式的EPlmnList
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年03月15日
   作    者   : l00130025
   修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
*****************************************************************************/
VOS_VOID NAS_MMC_ConvertMmlEquListToNvimEquPlmnList(
    NAS_MML_EQUPLMN_INFO_STRU          *pstMmlEPlmnList,
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList
)
{
    VOS_UINT8                           i;

    pstNvimEPlmnList->ucCount = pstMmlEPlmnList->ucEquPlmnNum;

    if (pstNvimEPlmnList->ucCount > NVIM_MAX_EPLMN_NUM)
    {
        pstNvimEPlmnList->ucCount = NVIM_MAX_EPLMN_NUM;
    }

    for (i = 0; i < pstNvimEPlmnList->ucCount; i++)
    {
        NAS_MMC_ConvertMmlPlmnIdToNvimEquPlmn(&(pstMmlEPlmnList->astEquPlmnAddr[i]),
                                              &(pstNvimEPlmnList->struPlmnList[i]));

    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNvimEPlmnListEqual
 功能描述  : 判断2个NVIM_EQUIVALENT_PLMN_LIST_STRU是否相同
 输入参数  : pstNvimEPlmnList1,pstNvimEPlmnList2待比较的2个NvimPlmnList
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 2个EplmnList相同
              VOS_FALSE : 2个EplmnList不同
 调用函数  :
 被调函数  :
 修改历史      :
    1.日    期   : 2012年03月15日
      作    者   : l00130025
      修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNvimEPlmnListEqual(
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList1,
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList2
)
{
    VOS_UINT32                          i;

    if (pstNvimEPlmnList1->ucCount != pstNvimEPlmnList2->ucCount)
    {
        return VOS_FALSE;
    }

    /* Eplmn个数大于0,但Rplmn不同时，EplmnList不相同 */
    if (pstNvimEPlmnList1->ucCount > 0)
    {
        if (VOS_FALSE == NAS_MMC_IsInNvEplmnList(&(pstNvimEPlmnList1->struPlmnList[0]),
											     1,
                                                 pstNvimEPlmnList2->struPlmnList))
        {
            return VOS_FALSE;
        }
    }
    else
    {
        return VOS_TRUE;
    }

    /* 其它Eplmn没有进行排序且有重复数据，需要对比2个列表才能确定相同 */
    for ( i = 1 ; i < pstNvimEPlmnList1->ucCount ; i++ )
    {
        if (VOS_FALSE == NAS_MMC_IsInNvEplmnList(&(pstNvimEPlmnList1->struPlmnList[i]),
											     pstNvimEPlmnList2->ucCount,
                                                 pstNvimEPlmnList2->struPlmnList))
        {
            return VOS_FALSE;
        }
    }

    for ( i = 1 ; i < pstNvimEPlmnList2->ucCount ; i++ )
    {
        if (VOS_FALSE == NAS_MMC_IsInNvEplmnList(&(pstNvimEPlmnList2->struPlmnList[i]),
                                                 pstNvimEPlmnList1->ucCount,
                                                 pstNvimEPlmnList1->struPlmnList))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_DeleteEPlmnList
 功能描述  : 删除当前的Eplmn列表，在Eps注册被拒时调用
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年03月15日
   作    者   : l00130025
   修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环

*****************************************************************************/
VOS_VOID NAS_MMC_DeleteEPlmnList( VOS_VOID )
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEPlmnList    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmnId = VOS_NULL_PTR;

    pstEPlmnList   = NAS_MML_GetEquPlmnList();

    /* 删除Eplmn */
    NAS_MML_InitEquPlmnInfo(pstEPlmnList);

    /* 更新NV的Eplmn */
    NAS_MMC_WriteEplmnNvim();

    /*将当前网络添加Eplmn列表*/
    pstCurrPlmnId = NAS_MML_GetCurrCampPlmnId();

    pstEPlmnList->astEquPlmnAddr[0].ulMcc = pstCurrPlmnId->ulMcc;
    pstEPlmnList->astEquPlmnAddr[0].ulMnc = pstCurrPlmnId->ulMnc;

    pstEPlmnList->ucEquPlmnNum = 1;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_WriteEplmnNvim
 功能描述  : 将Eplmn更新到NV中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月14日
    作    者   : likelai
    修改内容   : 新生成函数
  2.日    期   : 2011年7月26日
    作    者   : w00176964
    修改内容   : V7R1 Phase II,全局变量调整
  3.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
*****************************************************************************/
VOS_VOID NAS_MMC_WriteEplmnNvim(VOS_VOID)
{
    VOS_UINT32                          ulUpdateNvFlag;
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNewNvEquPlmnList = VOS_NULL_PTR;
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstOldNvEquPlmnList = VOS_NULL_PTR;


    ulUpdateNvFlag  = VOS_FALSE;

    pstNewNvEquPlmnList = (NVIM_EQUIVALENT_PLMN_LIST_STRU*)PS_MEM_ALLOC(
                                                      WUEPS_PID_MMC,
                                                      sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstNewNvEquPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_WriteEplmnNvim:ERROR: Memory Alloc Error");
        return;
    }

    pstOldNvEquPlmnList = (NVIM_EQUIVALENT_PLMN_LIST_STRU*)PS_MEM_ALLOC(
                                                        WUEPS_PID_MMC,
                                                        sizeof (NVIM_EQUIVALENT_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstOldNvEquPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_WriteEplmnNvim:ERROR: Memory Alloc Error");
        PS_MEM_FREE(WUEPS_PID_MMC, pstNewNvEquPlmnList);
        return;
    }

    PS_MEM_SET(pstNewNvEquPlmnList, 0, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));
    PS_MEM_SET(pstOldNvEquPlmnList, 0, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));

    NAS_MMC_ConvertMmlEquListToNvimEquPlmnList(NAS_MML_GetEquPlmnList(),
                                               pstNewNvEquPlmnList);

    /* 读取NV中EPLMN信息 */
    if ( NV_OK == NV_Read(en_NV_Item_EquivalentPlmn,
                         pstOldNvEquPlmnList, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU)) )
    {
        if (VOS_FALSE == NAS_MMC_IsNvimEPlmnListEqual(pstNewNvEquPlmnList,
                                                      pstOldNvEquPlmnList))
        {
            ulUpdateNvFlag = VOS_TRUE;
        }
    }
    else
    {
        /* 读取 NV 失败，需要更新 EPLMN */
        ulUpdateNvFlag = VOS_TRUE;
    }

    if ( VOS_TRUE == ulUpdateNvFlag )
    {
        if (NV_OK != NV_Write(en_NV_Item_EquivalentPlmn,
                              pstNewNvEquPlmnList,
                              sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU)))
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_WriteEplmnNvim:WARNING: en_NV_Item_EquivalentPlmn Error");
        }
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstNewNvEquPlmnList);
    PS_MEM_FREE(WUEPS_PID_MMC, pstOldNvEquPlmnList);


}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadHplmnFirstSearchPeriodNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_HPlmnFirstTimer
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2013年05月20日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
VOS_VOID NAS_MMC_ReadHplmnFirstSearchPeriodNvim(VOS_VOID)
{
    NAS_NVIM_HPLMN_FIRST_TIMER_STRU stFirstHplmnTime;
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg = VOS_NULL_PTR;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();

    /* 初始默认为2分钟 */
    stFirstHplmnTime.ucHplmnTimerLen = 2;
    if (NV_OK != NV_Read (en_NV_Item_HPlmnFirstTimer, &(stFirstHplmnTime.ucHplmnTimerLen), sizeof(VOS_UINT8)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadHplmnFirstSearchPeriodNvim():WARNING: en_NV_Item_HPlmnFirstTimer Error");
        return;
    }

    /* NV项中是以分钟来保存的,实际上启动定时器时需要以ms来启动 */
    pstBgSearchCfg->ulFirstStartHplmnTimerLen = (stFirstHplmnTime.ucHplmnTimerLen) * NAS_MML_SIXTY_SECOND * NAS_MML_ONE_THOUSAND_MILLISECOND;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadDefaultHplmnSrchPeriodNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_Default_Hplmn_Srch_Peri
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadDefaultHplmnSrchPeriodNvim(VOS_VOID)
{
    NAS_MMC_NVIM_DEFAULT_MAX_HPLMN_PERIOD_STRU   stDefaultHplmnSrchPeri;
    NAS_MML_BG_SEARCH_CFG_INFO_STRU             *pstBgSearchCfg = VOS_NULL_PTR;


    stDefaultHplmnSrchPeri.ucDefaultMaxHplmnPeriFlg = NAS_MMC_NV_ITEM_DEACTIVE;
    stDefaultHplmnSrchPeri.ucDefaultMaxHplmnTim     = 0;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();

    if (NV_OK != NV_Read(en_NV_Item_Default_Max_Hplmn_Srch_Peri,
                         &stDefaultHplmnSrchPeri,
                         sizeof(NAS_MMC_NVIM_DEFAULT_MAX_HPLMN_PERIOD_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadDefaultHplmnSrchPeriodNvim(): en_NV_Item_Default_Hplmn_Srch_Peri Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stDefaultHplmnSrchPeri.ucDefaultMaxHplmnPeriFlg)
    {
        pstBgSearchCfg->stDefaultMaxHplmnTimerPeriod.ucNvimActiveFlg      = stDefaultHplmnSrchPeri.ucDefaultMaxHplmnPeriFlg;

        /* NVIM中是以分钟来保存的,启动定时器需要以ms来启动 */
        pstBgSearchCfg->stDefaultMaxHplmnTimerPeriod.ulDefaultMaxHplmnLen = stDefaultHplmnSrchPeri.ucDefaultMaxHplmnTim * NAS_MML_SIXTY_SECOND * NAS_MML_ONE_THOUSAND_MILLISECOND;
    }

    return;
}

/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadHighPrioPlmnRefreshTriggerBGSearchFlagNvim
 功能描述  : 读取en_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG nv项内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月28日
    作    者   : c00318887
    修改内容   : for file refresh 新增
*****************************************************************************/
VOS_VOID NAS_MMC_ReadHighPrioPlmnRefreshTriggerBGSearchFlagNvim(VOS_VOID)
{
    NAS_MMC_NVIM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_STRU  stHighPrioPlmnRefreshTriggerBGSearchCfg;
    VOS_UINT32                                                  ulLength;

    ulLength = 0;
    PS_MEM_SET(&stHighPrioPlmnRefreshTriggerBGSearchCfg, 0x0, sizeof(NAS_MMC_NVIM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_STRU));

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadHighPrioPlmnRefreshTriggerBGSearchFlagNvim(): en_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG length Error");
        return;
    }


    if (NV_OK != NV_Read (en_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG, &stHighPrioPlmnRefreshTriggerBGSearchCfg, sizeof(NAS_MMC_NVIM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadHighPrioPlmnRefreshTriggerBGSearchFlagNvim():WARNING: en_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stHighPrioPlmnRefreshTriggerBGSearchCfg.ucTriggerBGSearchFlag)
    {
        NAS_MML_SetHighPrioPlmnRefreshTriggerBGSearchFlag(stHighPrioPlmnRefreshTriggerBGSearchCfg.ucTriggerBGSearchFlag);

        /* NVIM中是以秒来保存的,启动定时器需要以ms来启动 */
        if (0 == stHighPrioPlmnRefreshTriggerBGSearchCfg.usSearchDelayLen)
        {
            stHighPrioPlmnRefreshTriggerBGSearchCfg.usSearchDelayLen = NV_ITEM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_DEFAULT_DELAY_LEN;
        }

        NAS_MML_SetHighPrioPlmnRefreshTriggerBGSearchDelayLen(stHighPrioPlmnRefreshTriggerBGSearchCfg.usSearchDelayLen * 1000);
    }

    return;
}

/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadSrchHplmnTtimerValueNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_SearchHplmnTtimerValue
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadSrchHplmnTtimerValueNvim(VOS_VOID)
{
    NAS_MMC_NVIM_SEARCH_HPLMN_TIMER_STRU stSrchHplmnTimer;
    NAS_MML_BG_SEARCH_CFG_INFO_STRU     *pstBgSearchCfg = VOS_NULL_PTR;


    stSrchHplmnTimer.ucStatus              = NAS_MMC_NV_ITEM_DEACTIVE;
    stSrchHplmnTimer.usSrchHplmnTimerValue = 0;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();

    if (NV_OK != NV_Read (en_NV_Item_SearchHplmnTtimerValue, &stSrchHplmnTimer, sizeof(NAS_MMC_NVIM_SEARCH_HPLMN_TIMER_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadSrchHplmnTtimerValueNvim():WARNING: en_NV_Item_SearchHplmnTtimerValue Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stSrchHplmnTimer.ucStatus)
    {
        pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ucNvimActiveFlg         = stSrchHplmnTimer.ucStatus;
        pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ulNonFirstHplmnTimerLen = stSrchHplmnTimer.usSrchHplmnTimerValue * NAS_MML_SIXTY_SECOND * NAS_MML_ONE_THOUSAND_MILLISECOND;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadWhiteOpeLockPlmnInfoNvim
 功能描述  : 锁网功能开启时从内存和NV中获取到锁网运营商PLMN(白名单)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadWhiteOpeLockPlmnInfoNvim( VOS_VOID )
{
    NAS_MMC_NVIM_OPER_LOCK_WHITEPLMN_STRU stOperLockPlmnList;
    NAS_MML_PLMN_LOCK_CFG_INFO_STRU      *pstPlmnLockCfgInfo = VOS_NULL_PTR;


    stOperLockPlmnList.ulWhitePlmnLockNum = 0;

    pstPlmnLockCfgInfo = NAS_MML_GetPlmnLockCfg();

    if (NV_OK != NV_Read (en_NV_Item_OPERLOCK_PLMN_INFO_WHITE, &stOperLockPlmnList, sizeof(NAS_MMC_NVIM_OPER_LOCK_WHITEPLMN_STRU)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadWhiteOpeLockPlmnInfoNvim:Read NV Failed");
        return;
    }

    if (0 != stOperLockPlmnList.ulWhitePlmnLockNum)
    {
        /* 白名单生效 */
        pstPlmnLockCfgInfo->ucWhitePlmnLockNum = (VOS_UINT8)stOperLockPlmnList.ulWhitePlmnLockNum;

        if (stOperLockPlmnList.ulWhitePlmnLockNum > NAS_MML_MAX_WHITE_LOCK_PLMN_NUM)
        {
            pstPlmnLockCfgInfo->ucWhitePlmnLockNum = NAS_MML_MAX_WHITE_LOCK_PLMN_NUM;
        }

        PS_MEM_CPY(pstPlmnLockCfgInfo->astWhitePlmnId,
                   stOperLockPlmnList.astWhitePlmnId,
                   (sizeof(NAS_MML_PLMN_ID_STRU) * NAS_MML_MAX_WHITE_LOCK_PLMN_NUM));
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadBlackOperLockPlmnInfoNvim
 功能描述  : 锁网功能开启时从内存和NV中获取到锁网运营商PLMN(黑名单)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月26日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadBlackOperLockPlmnInfoNvim( VOS_VOID )
{
    NAS_MMC_NVIM_OPER_LOCK_BLACKPLMN_STRU stOperLockPlmnList;
    NAS_MML_PLMN_LOCK_CFG_INFO_STRU      *pstPlmnLockCfgInfo = VOS_NULL_PTR;


    stOperLockPlmnList.ulBlackPlmnLockNum = 0;


    PS_MEM_SET(&stOperLockPlmnList, 0x00, sizeof(stOperLockPlmnList));

    pstPlmnLockCfgInfo = NAS_MML_GetPlmnLockCfg();

    if (NV_OK != NV_Read (en_NV_Item_OperLock_Plmn_Info, &stOperLockPlmnList, sizeof(NAS_MMC_NVIM_OPER_LOCK_BLACKPLMN_STRU)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadBlackOperLockPlmnInfoNvim:Read NV Failed");
        return;
    }

    pstPlmnLockCfgInfo->ucBlackPlmnLockNum = (VOS_UINT8)stOperLockPlmnList.ulBlackPlmnLockNum;

    if ( stOperLockPlmnList.ulBlackPlmnLockNum > NAS_MML_MAX_BLACK_LOCK_PLMN_NUM )
    {
        pstPlmnLockCfgInfo->ucBlackPlmnLockNum = NAS_MML_MAX_BLACK_LOCK_PLMN_NUM;
    }

    PS_MEM_CPY(pstPlmnLockCfgInfo->astBlackPlmnId,
               stOperLockPlmnList.astBlackPlmnId,
               (sizeof(NAS_MML_PLMN_ID_STRU) * NAS_MML_MAX_BLACK_LOCK_PLMN_NUM));

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsRatForbiddenListNvimParaRangeValid
 功能描述  : 检查rat forbidden list参数范围是否合法。
 输入参数  : pstParaValue:NVIM的参数范围
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月12日
    作    者   : z00234330
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsRatForbiddenListNvimParaRangeValid(
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU *pstParaValue
)
{
    if (NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_BUTT <= pstParaValue->enSwitchFlag)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsRatForbiddenListNvimValid:The para enSwitchFlag is invalid");
        return VOS_FALSE;
    }

    /* 参数检查，如果NV配置的SIM卡数目大于NVIM_MAX_IMSI_FORBIDDEN_LIST_NUM，则认为配置的NV参数非法，直接返回；*/
    if ( NAS_NVIM_MAX_IMSI_FORBIDDEN_LIST_NUM < pstParaValue->ucImsiListNum )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsRatForbiddenListNvimValid:The para ucImsiListNum is invalid");
        return VOS_FALSE;
    }

    /* 参数检查，如果NV配置的禁止RAT数目大于2，则认为配置的NV参数非法，直接返回 */
    if ( NAS_NVIM_MAX_SUPPORTED_FORBIDDEN_RAT_NUM < pstParaValue->ucForbidRatNum )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsRatForbiddenListNvimValid:The para ucForbidRatNum is invalid");
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsRatForbiddenListNvimValid
 功能描述  : 对en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config统一做参数检查
 目前只支持禁止LTE或同时禁止LTE+3G，
 因此需要检查NV中配置的禁止RAT数目和禁止的接入技术是否符合该要求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 只允许以下两种禁止网络制式的组合:

 1. NUM = 1; RAT = LTE;
 2. NUM = 2; RAT = LTE + 3G;

 修改历史      :
  1.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 新生成函数，目前仅支持NV中配置禁止LTE或者禁止LTE+UTRAN，
                 NV中配置其他禁止网络制式的组合认为是非法参数
 2.日    期   : 2013年12月11日
   作    者   : z00234330
   修改内容   : dts2013121106833,降圈复杂度
*****************************************************************************/
VOS_UINT8 NAS_MMC_IsRatForbiddenListNvimValid(
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU *pstParaValue
)
{
    VOS_UINT32                          i;

    i = 0;

    if ( VOS_FALSE == NAS_MMC_IsRatForbiddenListNvimParaRangeValid(pstParaValue) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsRatForbiddenListNvimValid:The para is invalid");
        return VOS_FALSE;
    }

    /* 如果禁止网络制式列表中包含GSM，则返回VOS_FALSE */
    for (i = 0; i < pstParaValue->ucForbidRatNum; i++)
    {
        if (NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_GERAN == pstParaValue->aenForbidRatList[i])
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsRatForbiddenListNvimValid:The para aenForbidRatList is invalid");
            return VOS_FALSE;
        }
    }

    /* 如果禁止接入技术的数目为0，也认为参数是正确的 */
    if (NAS_NVIM_FORBIDDEN_RAT_NUM_0 == pstParaValue->ucForbidRatNum)
    {
        return VOS_TRUE;
    }

    /* 只允许两种组合，仅LTE或LTE+UTRAN */
    if ((NAS_NVIM_FORBIDDEN_RAT_NUM_1             == pstParaValue->ucForbidRatNum)
     && (NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN == pstParaValue->aenForbidRatList[0]))
    {
        return VOS_TRUE;
    }

    if ((NAS_NVIM_FORBIDDEN_RAT_NUM_2 == pstParaValue->ucForbidRatNum))
    {
        if ((NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_UTRAN  == pstParaValue->aenForbidRatList[0])
         && (NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN == pstParaValue->aenForbidRatList[1]))
        {
            return VOS_TRUE;
        }

        if ((NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN == pstParaValue->aenForbidRatList[0])
         && (NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_UTRAN  == pstParaValue->aenForbidRatList[1]))
        {
            return VOS_TRUE;
        }

        if ((NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN == pstParaValue->aenForbidRatList[0])
         && (NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN == pstParaValue->aenForbidRatList[1]))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertNvimRatToMmlType
 功能描述  : 将Nvim的接入技术转换成Mml的类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 新生成函数，目前仅支持NV中配置禁止LTE或者禁止LTE+UTRAN，
                 NV中配置其他禁止网络制式的组合认为是非法参数
*****************************************************************************/
VOS_UINT32 NAS_MMC_ConvertNvimRatToMmlType(
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM_UINT8            enNvRatType,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        *penMmlRatType
)
{
    switch(enNvRatType)
    {
        case NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_GERAN:
            *penMmlRatType = NAS_MML_NET_RAT_TYPE_GSM;
            break;

        case NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_UTRAN:
            *penMmlRatType = NAS_MML_NET_RAT_TYPE_WCDMA;
            break;

        case NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN:
            *penMmlRatType = NAS_MML_NET_RAT_TYPE_LTE;
            break;

        default:
            *penMmlRatType = NAS_MML_NET_RAT_TYPE_BUTT;
            return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadRatForbiddenListConfigNvim
 功能描述  : 读取根据卡类型禁止某些网络制式的NV配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 新生成函数，目前仅支持NV中配置禁止LTE或者禁止LTE+UTRAN，
                 NV中配置其他禁止网络制式的组合认为是非法参数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadRatForbiddenListConfigNvim( VOS_VOID )
{
    VOS_UINT32                                              i;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stSimPlmn;
    NAS_MML_PLMN_ID_STRU                                    stPlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enMmlRatType;

    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU                    stRatForbiddenListCfgNvim;
    NAS_MML_RAT_FORBIDDEN_LIST_STRU                        *pstRatForbiddenList = VOS_NULL_PTR;

    PS_MEM_SET(&stRatForbiddenListCfgNvim, 0x00, sizeof(stRatForbiddenListCfgNvim));
    PS_MEM_SET(&stSimPlmn, 0x00, sizeof(stSimPlmn));
    PS_MEM_SET(&stPlmn, 0x00, sizeof(stPlmn));

    enMmlRatType = NAS_MML_NET_RAT_TYPE_BUTT;

    pstRatForbiddenList = NAS_MML_GetRatForbiddenListCfg();

    if (NV_OK != NV_Read(en_NV_Item_Rat_Forbidden_List_Config, &stRatForbiddenListCfgNvim, sizeof(NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRatForbiddenListAccordImsiConfigNvim:Read NV Failed");
        return;
    }

    /* 统一做参数检查 */
    if (VOS_FALSE == NAS_MMC_IsRatForbiddenListNvimValid(&stRatForbiddenListCfgNvim))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRatForbiddenListAccordImsiConfigNvim:The paras of nvim is invalid");
        return;

    }
    /* 将NV中的参数保存到MML */
    pstRatForbiddenList->enSwitchFlag   = stRatForbiddenListCfgNvim.enSwitchFlag;

    /* 保存禁止RAT信息 */
    pstRatForbiddenList->ucForbidRatNum = 0;
    for (i = 0; i < stRatForbiddenListCfgNvim.ucForbidRatNum; i++)
    {
        if (VOS_TRUE == NAS_MMC_ConvertNvimRatToMmlType(stRatForbiddenListCfgNvim.aenForbidRatList[i], &enMmlRatType))
        {
            pstRatForbiddenList->aenForbidRatList[pstRatForbiddenList->ucForbidRatNum] = enMmlRatType;
            pstRatForbiddenList->ucForbidRatNum++;
        }
    }

    pstRatForbiddenList->ucImsiListNum  = 0;

    /* 将USIM中保存的PLMN信息转换为内存中的信息 */
    for ( i = 0; i < stRatForbiddenListCfgNvim.ucImsiListNum; i++ )
    {
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, stRatForbiddenListCfgNvim.astImsiList[i].aucSimPlmn, NAS_MML_SIM_PLMN_ID_LEN);
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stPlmn))
        {
            pstRatForbiddenList->astImsiList[pstRatForbiddenList->ucImsiListNum].ulMcc = stPlmn.ulMcc;
            pstRatForbiddenList->astImsiList[pstRatForbiddenList->ucImsiListNum].ulMnc = stPlmn.ulMnc;
            pstRatForbiddenList->ucImsiListNum++;
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadDisabledRatPlmnInfoNvim
 功能描述  : 读取禁止接入技术的PLMN信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月15日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2015年1月14日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改

  4.日    期   : 2015年4月18日
    作    者   : w00167002
    修改内容   : DTS2015032709270:NV中最大禁止网络的个数为8个。
*****************************************************************************/
VOS_VOID NAS_MMC_ReadDisabledRatPlmnInfoNvim( VOS_VOID )
{
    NAS_MMC_NVIM_DISABLED_RAT_PLMN_INFO_STRU                stDisabledRatPlmnList;

    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledRatPlmnCfgInfo;
    VOS_UINT32                                              i;


    PS_MEM_SET(&stDisabledRatPlmnList, 0x00, sizeof(stDisabledRatPlmnList));

    pstDisabledRatPlmnCfgInfo = NAS_MML_GetDisabledRatPlmnInfo();

    if (NV_OK != NV_Read (en_NV_Item_Disabled_Rat_Plmn_Info, &stDisabledRatPlmnList, sizeof(NAS_MMC_NVIM_DISABLED_RAT_PLMN_INFO_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadDisabledRatPlmnInfoNvim:Read NV Failed");
        return;
    }

    pstDisabledRatPlmnCfgInfo->ulDisabledRatPlmnNum = (VOS_UINT8)stDisabledRatPlmnList.ulDisabledRatPlmnNum;

    if (stDisabledRatPlmnList.ulDisabledRatPlmnNum > NAS_MML_NVIM_MAX_DISABLED_RAT_PLMN_NUM)
    {
        pstDisabledRatPlmnCfgInfo->ulDisabledRatPlmnNum = NAS_MML_NVIM_MAX_DISABLED_RAT_PLMN_NUM;
    }

    for (i = 0; i < pstDisabledRatPlmnCfgInfo->ulDisabledRatPlmnNum; i++)
    {
        pstDisabledRatPlmnCfgInfo->astDisabledRatPlmnId[i].stPlmnWithRat.stPlmnId.ulMcc = stDisabledRatPlmnList.astDisabledRatPlmnId[i].ulMcc;
        pstDisabledRatPlmnCfgInfo->astDisabledRatPlmnId[i].stPlmnWithRat.stPlmnId.ulMnc = stDisabledRatPlmnList.astDisabledRatPlmnId[i].ulMnc;
        pstDisabledRatPlmnCfgInfo->astDisabledRatPlmnId[i].stPlmnWithRat.enRat          = stDisabledRatPlmnList.astDisabledRatPlmnId[i].enRat;

        pstDisabledRatPlmnCfgInfo->astDisabledRatPlmnId[i].ulPlmnDisabledForbiddenSlice   = NAS_MML_MAX_TIME_SLICE;

        pstDisabledRatPlmnCfgInfo->astDisabledRatPlmnId[i].ulPlmnDisabledBeginSlice     = 0;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUserCfgEhplmnInfoNvim
 功能描述  : NV en_NV_Item_User_Cfg_Ehplmn_Info中获取到用户配置的EHplmn信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月6日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2012年12月22日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2014年12月22日
    作    者   : wx270776
    修改内容   : 增加扩展的Ehplmn组

*****************************************************************************/
VOS_VOID NAS_MMC_ReadUserCfgExtEhplmnInfoNvim( VOS_VOID )
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              ulNvimEhplmnNum;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stSimPlmn;
    NAS_MML_PLMN_ID_STRU                                    stPlmn;
    NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU              stNvimCfgExtEhplmnInfo;
    NAS_MML_USER_CFG_EXT_EHPLMN_INFO_STRU                  *pstUserCfgExtEhplmnInfo;

    PS_MEM_SET(&stNvimCfgExtEhplmnInfo, 0x00, sizeof(stNvimCfgExtEhplmnInfo));

    pstUserCfgExtEhplmnInfo = NAS_MML_GetUserCfgExtEhplmnInfo();
    /*循环变量初始化*/
    ulNvimEhplmnNum = 0;

    if ( NV_OK != NV_Read( en_NV_Item_User_Cfg_Ext_Ehplmn_Info,
                            &stNvimCfgExtEhplmnInfo, sizeof(NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU)) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadUserCfgEhplmnInfoNvim:Read NV Failed");
        return;
    }

    ulNvimEhplmnNum = stNvimCfgExtEhplmnInfo.ulNvimEhplmnNum;
    pstUserCfgExtEhplmnInfo->ulUserCfgEhplmnNum = ulNvimEhplmnNum;
    if ( ulNvimEhplmnNum > NAS_MML_MAX_USER_CFG_EXT_EHPLMN_NUM )
    {
        ulNvimEhplmnNum = NAS_MML_MAX_USER_CFG_EXT_EHPLMN_NUM;
    }

    /* 将NV中的PLMN LIST信息保存到MML的全局变量中去 */

    for (j = 0; j < ulNvimEhplmnNum; j++)
    {
        /* 初始化内存中存放PLMN网络列表个数 */
        pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[j].ucImsiPlmnListNum = 0;

        /* 防止数组越界 */
        if (stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucImsiPlmnListNum > NAS_MMC_MAX_USER_CFG_IMSI_PLMN_NUM)
        {
            stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucImsiPlmnListNum = NAS_MMC_MAX_USER_CFG_IMSI_PLMN_NUM;
        }

        for ( i = 0; i < stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucImsiPlmnListNum; i++ )
        {
            PS_MEM_CPY(stSimPlmn.aucSimPlmn, stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].astImsiPlmnList[i].aucSimPlmn, NAS_MML_SIM_PLMN_ID_LEN);
            NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

            if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stPlmn))
            {
                pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[j].astImsiPlmnList[pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[j].ucImsiPlmnListNum] = stPlmn;
                pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[j].ucImsiPlmnListNum++;
            }
        }

        /* 将NV中的EHplmn信息保存到MML的全局变量中去 */

        /* 初始化内存中存放PLMN网络列表个数 */
        pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[j].ucEhplmnListNum = 0;

        /* 防止数组越界 */
        if ( stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucEhplmnListNum > NAS_MMC_MAX_USER_CFG_EHPLMN_NUM )
        {
            stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucEhplmnListNum = NAS_MMC_MAX_USER_CFG_EHPLMN_NUM;
        }

        for ( i = 0; i < stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucEhplmnListNum; i++ )
        {
            PS_MEM_CPY(stSimPlmn.aucSimPlmn, stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].astEhPlmnList[i].aucSimPlmn, NAS_MML_SIM_PLMN_ID_LEN);
            NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

            if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stPlmn))
            {
                pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[j].astEhPlmnList[pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[j].ucEhplmnListNum] = stPlmn;
                pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[j].ucEhplmnListNum++;
            }
        }
    }

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadStandardSTKSteeringOfRoamingFlgNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_SrchHplmnFlg_StartOrAreaLostInAutoMode
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月26日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadStandardSTKSteeringOfRoamingFlgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_STK_STEERING_OF_ROAMING_SUPPORT_FLG_STRU   stStkSteeringOfRoamingSupportFlg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_Standard_STK_SteeringOfRoaming_Support_Flg, &ulLength);
    stStkSteeringOfRoamingSupportFlg.usStkSteeringOfRoamingSupportFlg = VOS_TRUE;

    if (NV_OK != NV_Read(en_NV_Item_Standard_STK_SteeringOfRoaming_Support_Flg,
                         &stStkSteeringOfRoamingSupportFlg,
                         ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadStandardSTKSteeringOfRoamingFlgNvim():WARNING: en_NV_Item_Standard_STK_SteeringOfRoaming_Support_Flg Error");
        return;
    }

    if ((NAS_MMC_NV_ITEM_ACTIVE !=  stStkSteeringOfRoamingSupportFlg.usStkSteeringOfRoamingSupportFlg)
     && (NAS_MMC_NV_ITEM_DEACTIVE !=  stStkSteeringOfRoamingSupportFlg.usStkSteeringOfRoamingSupportFlg))
    {
        return;
    }

    NAS_MML_SetStkSteeringOfRoamingSupportFlg((VOS_UINT8) stStkSteeringOfRoamingSupportFlg.usStkSteeringOfRoamingSupportFlg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadCsRejSearchSupportFlagNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_SteeringofRoaming_SUPPORT_CTRL,
             vodafone的搜网定制需求,CS域失败四次后下发搜网请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadCsRejSearchSupportFlagNvim(VOS_VOID)
{
    NAS_MMC_NVIM_CS_REJ_SEARCH_SUPPORT_STRU  stCsRejSearchSupportFlg;
    VOS_UINT32                               ulLength;

    ulLength        = 0;


    stCsRejSearchSupportFlg.ucStatus                = NAS_MMC_NV_ITEM_DEACTIVE;
    stCsRejSearchSupportFlg.ucCsRejSearchSupportFlg = VOS_FALSE;

    (VOS_VOID)NV_GetLength(en_NV_Item_SteeringofRoaming_SUPPORT_CTRL, &ulLength);
    if (ulLength > sizeof(stCsRejSearchSupportFlg))
    {
        return;
    }

    if (NV_OK != NV_Read (en_NV_Item_SteeringofRoaming_SUPPORT_CTRL,
                          &stCsRejSearchSupportFlg, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCsRejSearchSupportFlagNvim():WARNING: NV_Read en_NV_Item_SteeringofRoaming_SUPPORT_CTRL Error");
        return;
    }

    if(NAS_MMC_NV_ITEM_ACTIVE == stCsRejSearchSupportFlg.ucStatus)
    {
        NAS_MML_SetCsRejSearchSupportFlg(stCsRejSearchSupportFlg.ucCsRejSearchSupportFlg);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadAutoAttachNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_Autoattach
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月26日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年05月17日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
VOS_VOID NAS_MMC_ReadAutoAttachNvim(VOS_VOID)
{
    NAS_NVIM_AUTOATTACH_STRU            stAutoattachFlag;
    VOS_UINT32                          ulLength;

    ulLength        = 0;


    stAutoattachFlag.usAutoattachFlag= VOS_TRUE;

    (VOS_VOID)NV_GetLength(en_NV_Item_Autoattach, &ulLength);
    if (ulLength > sizeof(stAutoattachFlag))
    {
        return;
    }

    if(NV_OK != NV_Read (en_NV_Item_Autoattach, &stAutoattachFlag, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadAutoAttachNvim():WARNING: en_NV_Item_Autoattach Error");
        return;
    }

    NAS_MML_SetPsAutoAttachFlg((VOS_UINT8)stAutoattachFlag.usAutoattachFlag);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadPlmnSelectionModeNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_SelPlmn_Mode
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月26日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年05月20日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
VOS_VOID NAS_MMC_ReadPlmnSelectionModeNvim(VOS_VOID)
{
    NAS_NVIM_SELPLMN_MODE_STRU                          stPlmnSelMode;


    stPlmnSelMode.usSelPlmnMode = NAS_MMC_PLMN_SELECTION_MODE_BUTT;

    if (NV_OK != NV_Read (en_NV_Item_SelPlmn_Mode, &stPlmnSelMode.usSelPlmnMode, sizeof(stPlmnSelMode.usSelPlmnMode)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPlmnSelectionModeNvim():WARNING: en_NV_Item_SelPlmn_Mode Error");
        return;
    }

    if ((stPlmnSelMode.usSelPlmnMode != NAS_MMC_PLMN_SELECTION_MODE_AUTO)
     && (stPlmnSelMode.usSelPlmnMode != NAS_MMC_PLMN_SELECTION_MODE_MANUAL))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPlmnSelectionModeNvim():NV parameter invalid");
        return;
    }

    NAS_MMC_SetPlmnSelectionMode((NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8)(stPlmnSelMode.usSelPlmnMode));

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_WritePlmnSelectionModeNvim
 功能描述  : 写NV项: en_NV_Item_SelPlmn_Mode
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月29日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年05月20日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
VOS_VOID NAS_MMC_WritePlmnSelectionModeNvim(VOS_VOID)
{
    NAS_NVIM_SELPLMN_MODE_STRU          stPlmnSelMode;
    VOS_UINT32                          ulNvLength;

    ulNvLength = 0;
    stPlmnSelMode.usSelPlmnMode = NAS_MMC_GetPlmnSelectionMode();

    (VOS_VOID)NV_GetLength(en_NV_Item_SelPlmn_Mode, &ulNvLength);
    if (NV_OK != NV_Write(en_NV_Item_SelPlmn_Mode,
                      &stPlmnSelMode,
                      ulNvLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_WritePlmnSelectionModeNvim():en_NV_Item_SelPlmn_Mode Error");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadEquivalentPlmnNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_EquivalentPlmn
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月26日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，避免手动搜网重选被拒触发死循环
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadEquivalentPlmnNvim(VOS_VOID)
{

    NVIM_EQUIVALENT_PLMN_LIST_STRU      stEquivPlmn;
    VOS_UINT32                          i;
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulEquPlmnNum;


    PS_MEM_SET(&stEquivPlmn, 0x00, sizeof(stEquivPlmn));

    pstNetWorkInfo = NAS_MML_GetNetworkInfo();

    if (NV_OK != NV_Read (en_NV_Item_EquivalentPlmn, &stEquivPlmn, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadEquivalentPlmnNvim():WARNING: en_NV_Item_EquivalentPlmn Error");
        return;
    }

    if ( NVIM_MAX_EPLMN_NUM < stEquivPlmn.ucCount)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadEquivalentPlmnNvim():ERROR: EquivalentPlmn Num ERROR.");
        stEquivPlmn.ucCount = NVIM_MAX_EPLMN_NUM;
    }

    ulEquPlmnNum = stEquivPlmn.ucCount;

    if (ulEquPlmnNum > NAS_MML_MAX_EQUPLMN_NUM)
    {
        ulEquPlmnNum = NAS_MML_MAX_EQUPLMN_NUM;
    }

    for (i = 0; i < ulEquPlmnNum; i++)
    {
        pstNetWorkInfo->stEquPlmnInfo.astEquPlmnAddr[i].ulMcc =
                            (stEquivPlmn.struPlmnList[i].ucMcc[0]
                            | ((VOS_UINT32)stEquivPlmn.struPlmnList[i].ucMcc[1] << 8)
                            | ((VOS_UINT32)stEquivPlmn.struPlmnList[i].ucMcc[2] << 16));

        pstNetWorkInfo->stEquPlmnInfo.astEquPlmnAddr[i].ulMnc =
                           (stEquivPlmn.struPlmnList[i].ucMnc[0]
                           | ((VOS_UINT32)stEquivPlmn.struPlmnList[i].ucMnc[1] << 8)
                           | ((VOS_UINT32)stEquivPlmn.struPlmnList[i].ucMnc[2] << 16));
    }

    /* 从EPLMN列表中删除无效的网络 */
    ulEquPlmnNum = NAS_MML_DelInvalidPlmnFromList(ulEquPlmnNum, pstNetWorkInfo->stEquPlmnInfo.astEquPlmnAddr);
    pstNetWorkInfo->stEquPlmnInfo.ucEquPlmnNum = (VOS_UINT8)ulEquPlmnNum;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadMaxForbRoamLaNvim
 功能描述  : 从NV中获取NV项: en_NV_Item_Max_Forb_Roam_La
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年7月26日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadMaxForbRoamLaNvim(VOS_VOID)
{
    NAS_MMC_NVIM_MAX_FORB_ROAM_LA_STRU   stMaxForbRoamLa;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU *pstMiscellaneousCfgInfo = VOS_NULL_PTR;


    stMaxForbRoamLa.ucMaxForbRoamLaFlg = NAS_MMC_NV_ITEM_DEACTIVE;
    stMaxForbRoamLa.ucMaxForbRoamLaNum = 0;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    if (NV_OK != NV_Read(en_NV_Item_Max_Forb_Roam_La,
                         &stMaxForbRoamLa, sizeof(NAS_MMC_NVIM_MAX_FORB_ROAM_LA_STRU)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
                        "NAS_MMC_ReadMaxForbRoamLaNvim():WARNING: en_NV_Item_Max_Forb_Roam_La Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stMaxForbRoamLa.ucMaxForbRoamLaFlg)
    {
        pstMiscellaneousCfgInfo->ucMaxForbRoamLaFlg = stMaxForbRoamLa.ucMaxForbRoamLaFlg;
        pstMiscellaneousCfgInfo->ucMaxForbRoamLaNum = stMaxForbRoamLa.ucMaxForbRoamLaNum;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadGsmForbidAccessInfoNvim
 功能描述  : 从en_NV_Item_EFust_Service_Cfg NV中获取GSM是否禁止接入信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月26日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理

*****************************************************************************/
VOS_VOID NAS_MMC_ReadGsmForbidAccessInfoNvim(VOS_VOID)
{
    NAS_MMC_NVIM_EFUST_SERVICE_CFG_STRU  stEfustServiceCfg;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU *pstMiscellaneousCfgInfo = VOS_NULL_PTR;


    PS_MEM_SET(&stEfustServiceCfg, 0x00, sizeof(NAS_MMC_NVIM_EFUST_SERVICE_CFG_STRU));

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    if (NV_OK != NV_Read(en_NV_Item_EFust_Service_Cfg,
                         &stEfustServiceCfg, sizeof(NAS_MMC_NVIM_EFUST_SERVICE_CFG_STRU)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
                        "NAS_MMC_ReadGsmForbidAccessInfoNvim:WARNING: en_NV_Item_EFust_Service_Cfg Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stEfustServiceCfg.ucStatus)
    {
        pstMiscellaneousCfgInfo->ucNvGsmForbidFlg = stEfustServiceCfg.ucForbidReg2GNetWork;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadRoamBrokerRegisterFailCntNvim
 功能描述  : 从NV中获取注册失败次数信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月27日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年1月17日
    作    者   : w00167002
    修改内容   : DTS2011122006209:增加保存RoamBroker是否激活内容
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理

*****************************************************************************/
VOS_VOID NAS_MMC_ReadRoamBrokerRegisterFailCntNvim(VOS_VOID)
{
    NAS_MMC_NVIM_REG_FAIL_CNT_STRU       stRegisterFailCnt;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU *pstMiscellaneousCfgInfo = VOS_NULL_PTR;


    stRegisterFailCnt.ucNvActiveFlag = VOS_FALSE;
    stRegisterFailCnt.ucRegFailCnt   = 0;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    if (NV_OK != NV_Read(en_NV_Item_Register_Fail_Cnt,
                         &stRegisterFailCnt, sizeof(NAS_MMC_NVIM_REG_FAIL_CNT_STRU)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRoamBrokerRegisterFailCntNvim():WARNING: en_Nv_Item_Register_Fail_Cnt Error");
        return;
    }

    pstMiscellaneousCfgInfo->ucRoamBrokerRegisterFailCnt = NAS_MML_MAX_CS_REG_FAIL_CNT;

    if ((VOS_TRUE == stRegisterFailCnt.ucNvActiveFlag)
     && (stRegisterFailCnt.ucRegFailCnt < NAS_MML_MAX_CS_REG_FAIL_CNT))
    {
        pstMiscellaneousCfgInfo->ucRoamBrokerRegisterFailCnt = stRegisterFailCnt.ucRegFailCnt;

        pstMiscellaneousCfgInfo->ucRoamBrokerActiveFlag      = VOS_TRUE;
    }


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadPsLociNvim
 功能描述  : 从NV中获取PS Loci文件
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月29日
    作    者   : s46746
    修改内容   : 新生成函数

  2.日    期   : 2011年12月12日
    作    者   : zhoujun /40661
    修改内容   : DTS2011101103567
  3.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  4.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadPsLociNvim(VOS_VOID)
{
    NAS_NVIM_PS_LOCI_SIM_FILES_STRU stPsLocInfo;


    PS_MEM_SET(&stPsLocInfo, 0x00, sizeof(stPsLocInfo));

    if (NV_OK != NV_Read(en_NV_Item_Ps_Loci,
                         &stPsLocInfo, NAS_NVIM_PS_LOCI_SIM_FILE_LEN))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPsLociNvim():WARNING: en_NV_Item_Ps_Loci Error");

        return;
    }

    /* 更新PTMSI的内容 */
    NAS_MMC_UpdatePtmsiFormPsLociFile(stPsLocInfo.aucPsLocInfo);

    /* 更新PTMSI SIGNATURE的内容 */
    NAS_MMC_UpdatePtmsiSignatureFormPsLociFile(stPsLocInfo.aucPsLocInfo);

    /* 更新RAI的内容 */
    NAS_MMC_UpdateRaiFormPsLociFile(stPsLocInfo.aucPsLocInfo);

    NAS_MML_UpdateSimPsLociFileContent(stPsLocInfo.aucPsLocInfo);

    /* 更新GPRS的状态 */
    if (stPsLocInfo.aucPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN - 1] > NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED )
    {
        stPsLocInfo.aucPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN - 1] = NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED;
    }
    NAS_MML_SetPsUpdateStatus(stPsLocInfo.aucPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN - 1]);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_WritePsLociNvim
 功能描述  : 写PS Loci文件
 输入参数  : pstPsLocInfo PS loc信息
             ulSize       PS loc信息的大小
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月11日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_WritePsLociNvim(
    VOS_UINT8                          *pstPsLocInfo,
    VOS_UINT32                          ulSize
)
{
    VOS_UINT32                          i;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity = VOS_NULL_PTR;

    pstMsIdentity       = NAS_MML_GetSimMsIdentity();

    /* 非法PS LOC信息或长度 */
    if ((VOS_NULL_PTR == pstPsLocInfo)
     || (0 ==ulSize)
     || (ulSize > NAS_MML_PS_LOCI_SIM_FILE_LEN))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_WritePsLociNvim:ERROR: Invalid PS loc info!");

        return;
    }

    if (NV_OK != NV_Write(en_NV_Item_Ps_Loci, pstPsLocInfo, ulSize))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_WritePsLociNvim:ERROR: (VOS_VOID)NV_Write Error");

        return;
    }

    /* 设置PTMSI的内容无效 */
    for (i = 0; i < NAS_MML_MAX_PTMSI_LEN; i++)
    {
        pstMsIdentity->aucPtmsi[i]  = pstPsLocInfo[i];
    }

    /* 设置PTMSI SIGNATURE的内容无效 */
    for (i = 0; i < NAS_MML_MAX_PTMSI_SIGNATURE_LEN; i++)
    {
        pstMsIdentity->aucPtmsiSignature[i] = pstPsLocInfo[i + NAS_MML_PTMSI_SIGNATRUE_POS_EFPSLOCI_FILE];
    }

    /* 更新RAI的内容 */
    NAS_MMC_UpdateRaiFormPsLociFile(pstPsLocInfo);

    /* 更新GPRS的状态 */
    NAS_MML_SetPsUpdateStatus(pstPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN - 1]);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadRoamCfgInfoNvim
 功能描述  : 从en_NV_Item_Roam_Capa NV中获取漫游特性
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月18日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadRoamCfgInfoNvim(VOS_VOID)
{
    NAS_NVIM_ROAM_CFG_INFO_STRU         stRoamFeature;
    NAS_MML_ROAM_CFG_INFO_STRU         *pstRoamCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulNvLenght;


    stRoamFeature.ucRoamFeatureFlg = NAS_MMC_NV_ITEM_DEACTIVE;
    stRoamFeature.ucRoamCapability = NAS_MML_ROAM_BUTT;
    ulNvLenght                     = 0;

    pstRoamCfgInfo = NAS_MML_GetRoamCfg();

    (VOS_VOID)NV_GetLength(en_NV_Item_Roam_Capa, &ulNvLenght);
    if (NV_OK != NV_Read(en_NV_Item_Roam_Capa,
                         &stRoamFeature, ulNvLenght))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadRoamFeatureNvim():WARNING: en_NV_Item_Roam_Capa Error");

        return;
    }

    if ((NAS_MMC_NV_ITEM_ACTIVE == stRoamFeature.ucRoamFeatureFlg)
     && (stRoamFeature.ucRoamCapability < NAS_MML_ROAM_BUTT))
    {
        pstRoamCfgInfo->ucRoamFeatureFlg = stRoamFeature.ucRoamFeatureFlg;
        pstRoamCfgInfo->enRoamCapability = stRoamFeature.ucRoamCapability;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadDtSingleDomainPlmnSearchNvim
 功能描述  : 从NV中获取DT单域注册失败达到最大次数搜网定制
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月29日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadDtSingleDomainPlmnSearchNvim(VOS_VOID)
{
    NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_CNT_STRU                stSingleDomainFailCnt;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength = 0;


    stSingleDomainFailCnt.ucSingleDomainFailPlmnSrchFlag = NAS_MMC_NV_ITEM_DEACTIVE;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    (VOS_VOID)NV_GetLength(en_NV_Item_SINGLE_DOMAIN_FAIL_SRCH_PLMN_CNT, &ulLength);
    if (NV_OK != NV_Read(en_NV_Item_SINGLE_DOMAIN_FAIL_SRCH_PLMN_CNT,
                         &stSingleDomainFailCnt.ucSingleDomainFailPlmnSrchFlag, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadDtSingleDomainPlmnSearchNvim():WARNING: en_NV_Item_SINGLE_DOMAIN_FAIL_SRCH_PLMN_CNT Error");

        return;
    }


    if ((NAS_MMC_NV_ITEM_ACTIVE != stSingleDomainFailCnt.ucSingleDomainFailPlmnSrchFlag)
     && (NAS_MMC_NV_ITEM_DEACTIVE != stSingleDomainFailCnt.ucSingleDomainFailPlmnSrchFlag))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadDtSingleDomainPlmnSearchNvim():WARNING: NV parameter Error");
        return;
    }

    pstMiscellaneousCfgInfo->ucSingleDomainFailPlmnSrchFlag
             = stSingleDomainFailCnt.ucSingleDomainFailPlmnSrchFlag;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadLastImsiFromNvim
 功能描述  : V3R2获取保存在NVIM中的last imsi的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月17日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

  2.日    期   : 2012年3月2日
    作    者   : z40661
    修改内容   : DTS2012021703361，读取last imsi出错
  3.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  4.日    期   : 2013年05月20日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
VOS_VOID  NAS_MMC_ReadLastImsiNvim( VOS_VOID )
{

    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfg;
    NAS_MMC_NVIM_LAST_IMSI_STRU         stLastImsi;
    VOS_UINT32                          ulLength;

    ulLength = 0;


    PS_MEM_SET(&stLastImsi, 0x00, sizeof(NAS_MMC_NVIM_LAST_IMSI_STRU));

    pstRplmnCfg = NAS_MML_GetRplmnCfg();

    (VOS_VOID)NV_GetLength(en_NV_Item_Last_Imsi, &ulLength);

    /* 保存在NVIM中,NVIM中保持的第一位是有效位，第二位以后才是IMSI内容 */
    if (NV_OK != NV_Read(en_NV_Item_Last_Imsi,
                    &stLastImsi, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
            "NAS_MMC_ReadLastImsiNvim(): WARNING: en_NV_Item_Last_Imsi Error");

        return;
    }

    PS_MEM_CPY(pstRplmnCfg->aucLastImsi,stLastImsi.aucImsi,NAS_MML_MAX_IMSI_LEN);


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateLastImsi
 功能描述  : V3R2更新保存在NVIM中的last imsi的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月17日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

  2.日    期   : 2012年3月2日
    作    者   : z40661
    修改内容   : DTS2012021703361，读取last imsi出错

  3.日    期   : 2013年05月20日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/

VOS_VOID NAS_MMC_UpdateLastImsi( VOS_VOID )
{

    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT8                           aucLastImsi[NAS_MML_MAX_IMSI_LEN];
    NAS_MMC_NVIM_LAST_IMSI_STRU         stLastImsi;
    VOS_UINT32                          ulLength;

    ulLength = 0;
    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    PS_MEM_SET(aucLastImsi, 0x00, NAS_MML_MAX_IMSI_LEN);
    PS_MEM_SET(&stLastImsi, 0x00, sizeof(NAS_MMC_NVIM_LAST_IMSI_STRU));

    if ( USIMM_API_SUCCESS != USIMM_GetCardIMSI(aucLastImsi) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateLastImsi:Get Imsi Failed");
        return;
    }

    PS_MEM_CPY(pstRplmnCfgInfo->aucLastImsi, aucLastImsi, sizeof(aucLastImsi));
    PS_MEM_CPY(stLastImsi.aucImsi, aucLastImsi, sizeof(aucLastImsi));

    (VOS_VOID)NV_GetLength(en_NV_Item_Last_Imsi, &ulLength);

    /* 保存在NVIM中,NVIM中保持的第一位是有效位，第二位以后才是IMSI内容 */
    if (NV_OK != NV_Write (en_NV_Item_Last_Imsi,
                           &stLastImsi,
                           ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateLastImsi:Write NV Failed");
    }

}

/* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_ReaducWcdmaPriorityGsmFlgNvim
 功能描述  : 从NV中获取H3G需求,W网络优先于GSM网络定制
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
  4.日    期   : 2013年12月13日
    作    者   : z00161729
    修改内容   : DTS2013121206933:非高优先级可用高低质量的网络按syscfg设置接入技术优先级排序，9055 nv项控制
*****************************************************************************/
VOS_VOID NAS_MMC_ReaducWcdmaPriorityGsmNvim(VOS_VOID)
{
    NAS_MMC_NVIM_WCDMA_PRIORITY_GSM_FLG_STRU                stWcdmaPriorityGsm;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength = 0;

    stWcdmaPriorityGsm.ucWcdmaPriorityGsmFlg = NAS_MMC_NV_ITEM_DEACTIVE;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    /* 默认设置为不激活 */
    pstMiscellaneousCfgInfo->ucWcdmaPriorityGsmFlg             = NAS_MMC_NV_ITEM_DEACTIVE;
    pstMiscellaneousCfgInfo->ucSortAvailalePlmnListRatPrioFlg  = NAS_MMC_NV_ITEM_DEACTIVE;

    (VOS_VOID)NV_GetLength(en_NV_Item_NVIM_WCDMA_PRIORITY_GSM_SUPPORT_FLG, &ulLength);
    if (NV_OK != NV_Read(en_NV_Item_NVIM_WCDMA_PRIORITY_GSM_SUPPORT_FLG,
                         &stWcdmaPriorityGsm, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadDtSingleDomainPlmnSearchNvim():WARNING: en_NV_Item_NVIM_WCDMA_PRIORITY_GSM_SUPPORT_FLG Error");

        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stWcdmaPriorityGsm.ucWcdmaPriorityGsmFlg)
    {
        pstMiscellaneousCfgInfo->ucWcdmaPriorityGsmFlg = stWcdmaPriorityGsm.ucWcdmaPriorityGsmFlg;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stWcdmaPriorityGsm.ucSortAvailalePlmnListRatPrioFlg)
    {
        pstMiscellaneousCfgInfo->ucSortAvailalePlmnListRatPrioFlg = stWcdmaPriorityGsm.ucSortAvailalePlmnListRatPrioFlg;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadPsOnlyCsServiceSupportNvim
 功能描述  : 从NV中获取服务域设置为PS ONLY时，是否支持CS域短信和呼叫业务(紧急呼叫除外)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadPsOnlyCsServiceSupportNvim(VOS_VOID)
{
    NAS_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG_STRU            stPsOnlyCsServiceSupportFlg;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength = 0;


    stPsOnlyCsServiceSupportFlg.ucPsOnlyCsServiceSupportFlg = NAS_MMC_NV_ITEM_DEACTIVE;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    (VOS_VOID)NV_GetLength(en_NV_Item_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG, &ulLength);
    if (ulLength > sizeof(stPsOnlyCsServiceSupportFlg))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG,
                         &stPsOnlyCsServiceSupportFlg, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadDtSingleDomainPlmnSearchNvim():WARNING: en_NV_Item_SINGLE_DOMAIN_FAIL_SRCH_PLMN_CNT Error");

        return;
    }


    if ((NAS_MMC_NV_ITEM_ACTIVE != stPsOnlyCsServiceSupportFlg.ucPsOnlyCsServiceSupportFlg)
     && (NAS_MMC_NV_ITEM_DEACTIVE != stPsOnlyCsServiceSupportFlg.ucPsOnlyCsServiceSupportFlg))
    {
        pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg = NAS_MMC_NV_ITEM_DEACTIVE;
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReaducWcdmaPriorityGsmNvim():WARNING: NV parameter Error");
        return;
    }

    pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg
             = stPsOnlyCsServiceSupportFlg.ucPsOnlyCsServiceSupportFlg;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadAPPConfigSupportNvim
 功能描述  : 从NV中获取服务域设置为PS ONLY时，是否支持CS域短信和呼叫业务(紧急呼叫除外)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年05月17日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
VOS_VOID NAS_MMC_ReadAPPConfigSupportNvim(VOS_VOID)
{
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU                     stSysAppConfig;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    stSysAppConfig.usSysAppConfigType = SYSTEM_APP_BUTT;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    (VOS_VOID)NV_GetLength(en_NV_Item_System_APP_Config, &ulLength);
    if (ulLength > sizeof(stSysAppConfig))
    {
        return;
    }
    if (NV_OK != NV_Read(en_NV_Item_System_APP_Config,
                         &stSysAppConfig, ulLength))
    {
        pstMiscellaneousCfgInfo->usAppConfigSupportFlg  = SYSTEM_APP_MP;
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadAPPConfigSupportNvim():WARNING: read en_NV_Item_System_APP_Config Error");

        return;
    }


    if ( SYSTEM_APP_ANDROID < stSysAppConfig.usSysAppConfigType )
    {
        pstMiscellaneousCfgInfo->usAppConfigSupportFlg  = SYSTEM_APP_MP;
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadAPPConfigSupportNvim():WARNING: en_NV_Item_System_APP_Config error");

    }
    else
    {
        pstMiscellaneousCfgInfo->usAppConfigSupportFlg = stSysAppConfig.usSysAppConfigType ;
    }
    return;
}

/* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

/* Modified by z40661 for 泰国AIS特性 2012-05-17, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadAisRoamingNvim
 功能描述  : 读取NVIM中的泰国AIS特性开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月17日
    作    者   : zhoujun \ 40661
    修改内容   : 新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadAisRoamingNvim( VOS_VOID  )
{
    NAS_MMC_NVIM_AIS_ROAMING_CFG_STRU   stNvimAisRoamingCfg;
    NAS_MML_AIS_ROAMING_CFG_STRU       *pstAisRoamingCfg;


    PS_MEM_SET(&stNvimAisRoamingCfg, 0x00, sizeof(stNvimAisRoamingCfg));

    pstAisRoamingCfg = NAS_MML_GetAisRoamingCfg();

    if (NV_OK != NV_Read(en_NV_Item_NVIM_AIS_ROAMING_CFG,
                         &stNvimAisRoamingCfg, sizeof(stNvimAisRoamingCfg)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadAisRoamingNvim():WARNING: read en_NV_Item_NVIM_AIS_ROAMING_CFG Error");

        return;
    }

    pstAisRoamingCfg->ucEnableFlg            = stNvimAisRoamingCfg.ucEnableFlg;
    pstAisRoamingCfg->enHighPrioRatType      = stNvimAisRoamingCfg.ucHighPrioRatType;
    pstAisRoamingCfg->stHighPrioPlmnId.ulMcc = stNvimAisRoamingCfg.stHighPrioPlmnId.ulMcc;
    pstAisRoamingCfg->stHighPrioPlmnId.ulMnc = stNvimAisRoamingCfg.stHighPrioPlmnId.ulMnc;
    pstAisRoamingCfg->stSimHPlmnId.ulMcc     = stNvimAisRoamingCfg.stSimHPlmnId.ulMcc;
    pstAisRoamingCfg->stSimHPlmnId.ulMnc     = stNvimAisRoamingCfg.stSimHPlmnId.ulMnc;
}

/* Modified by z40661 for 泰国AIS特性 2012-05-17, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUserAutoReselCfgNvim
 功能描述  : 从NV中获取en_NV_Item_User_Auto_Resel_Switch NV项内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年5月15日
   作    者   : l00130025
   修改内容   : DTS2012012903053:Ts23.122 ch4.4.3.2.1 Auto user reselecton功能支持
 2.日    期   : 2012年12月13日
   作    者   : L00171473
   修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUserAutoReselCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_USER_AUTO_RESEL_CFG_STRU    stUserAutoReselCfg;
    VOS_UINT32                               ulLength;

    ulLength = 0;


    PS_MEM_SET(&stUserAutoReselCfg, 0x00, sizeof(NAS_MMC_NVIM_USER_AUTO_RESEL_CFG_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_User_Auto_Resel_Switch, &ulLength);


    if (NV_OK != NV_Read(en_NV_Item_User_Auto_Resel_Switch,
                         &stUserAutoReselCfg, ulLength))
    {
        stUserAutoReselCfg.ucAutoReselActiveFlg  = VOS_FALSE;
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadUserAutoReselCfgNvim():WARNING: read en_NV_Item_User_Auto_Resel_Switch Error");

    }

    if (stUserAutoReselCfg.ucAutoReselActiveFlg == VOS_TRUE)
    {
        NAS_MML_SetUserAutoReselActiveFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetUserAutoReselActiveFlg(VOS_FALSE);
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadScanCtrlNvim
 功能描述  : 从NV项en_NV_Item_Scan_Ctrl_Para中读取是否支持搜索控制
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月11日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadScanCtrlNvim(VOS_VOID)
{
    NVIM_SCAN_CTRL_STRU                 stNvScanCtrl;
    VOS_UINT32                          ulLength;

    ulLength = 0;


    (VOS_VOID)NV_GetLength(en_NV_Item_Scan_Ctrl_Para, &ulLength);
    if (ulLength > sizeof(stNvScanCtrl))
    {
        return;
    }

    PS_MEM_SET(&stNvScanCtrl, 0x00, sizeof(NVIM_SCAN_CTRL_STRU));

    /* 读NV项en_NV_Item_Scan_Ctrl_Para，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_Scan_Ctrl_Para,
                         &stNvScanCtrl, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadScanCtrlNvim():WARNING: read en_NV_Item_Scan_Ctrl_Para Error");

        return;
    }

    /* 未激活，直接返回 */
    if (NAS_MMC_NV_ITEM_ACTIVE != stNvScanCtrl.ucNvimActiveFlg)
    {
        return;
    }

    /* 搜索控制已激活，更新搜索控制标识为VOS_TRUE */
    NAS_MML_SetScanCtrlEnableFlg(VOS_TRUE);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadHPlmnSearchRegardLessMccNvim
 功能描述  : 从NV中获取en_NV_Item_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月11日
    作    者   : w00166186
    修改内容   : AT&T&DCM新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadHPlmnSearchRegardLessMccNvim(VOS_VOID)
{
    NAS_MMC_NVIM_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT_STRU   stHplmnSearchRegardlessMcc;


    PS_MEM_SET(&stHplmnSearchRegardlessMcc, 0x00, sizeof(stHplmnSearchRegardlessMcc));

    /* 读取NV */
    if (NV_OK != NV_Read(en_NV_Item_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT,
                         &stHplmnSearchRegardlessMcc, sizeof(NAS_MMC_NVIM_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadHPlmnSearchRegardLessMccNvim(): en_NV_Item_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT Error");
        return;
    }

    /*  有效性检查 */
    if (NAS_MMC_NV_ITEM_ACTIVE != stHplmnSearchRegardlessMcc.ucNvimActiveFlg)
    {
        return;
    }

    if (stHplmnSearchRegardlessMcc.ucCustomMccNum > NAS_MML_BG_SEARCH_REGARDLESS_MCC_NUMBER)
    {
        return;
    }

    /* 赋值到全局变量 */
    NAS_MML_SetBgSearchRegardlessMccList(stHplmnSearchRegardlessMcc.aulCustommMccList, stHplmnSearchRegardlessMcc.ucCustomMccNum);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertNivmActionToMmlType
 功能描述  : 将从NV中读取的动作类型转化为MMC类型
 输入参数  : enNvAction:NV中定义的操作
 输出参数  : penMmlAction
 返 回 值  : VOS_TRUE 转化成功
             VOS_FALSE 转化失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月11日
    作    者   : w00166186
    修改内容   : AT&T&DCM新生成函数
  2.日    期   : 2014年8月19日
    作    者   : w00167002
    修改内容   : DTS2014081905808:在配置PS注册拒绝14时候，若当前在HOME PLMN上，则可能
               触发循环乒乓，修改为增加ACTION动作:在漫游网络上触发选网，在HOME网络上
               不生效，按现有流程进行处理
*****************************************************************************/
VOS_UINT32 NAS_MMC_ConvertNivmActionToMmlType(
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8   enNvAction,
    NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8       *penMmlAction
)
{
    switch(enNvAction)
    {
        case NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_PLMN_SELECTION:
            *penMmlAction = NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_PLMN_SELECTION;
            break;

        case NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_NORMAL_CAMP_ON:
            *penMmlAction = NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_NORMAL_CAMP_ON;
            break;

        case NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_OPTIONAL_PLMN_SELECTION:
            *penMmlAction = NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_OPTIONAL_PLMN_SELECTION;
            break;

        case NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_LIMITED_CAMP_ON:
            *penMmlAction = NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_LIMITED_CAMP_ON;
            break;

        case NAS_MMC_NVIM_SINGLE_DOMAIN_ROAMING_REG_FAIL_ACTION_PLMN_SELECTION:
            *penMmlAction = NAS_MML_SINGLE_DOMAIN_ROAMING_REG_FAIL_ACTION_PLMN_SELECTION;
            break;

        default:
            *penMmlAction = NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_BUTT;
            return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadPrioHplmnActCfgNvim
 功能描述  : 从NV中获取定制的接入技术NV
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年6月9日
   作    者   : l00130025
   修改内容   : DTS2012060400029:添加对HPLMNAct优先接入技术的定制；目前USim卡中HPLMNACT很多不支持L
 2.日    期   : 2012年12月13日
   作    者   : L00171473
   修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadPrioHplmnActCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_PRIO_HPLMNACT_CFG_STRU    stHplmnActCfg;
    NAS_MML_PRIO_HPLMNACT_CFG_STRU        *pstPrioHplmnActCfg = VOS_NULL_PTR;


    PS_MEM_SET(&stHplmnActCfg, 0x00, sizeof(stHplmnActCfg));

    pstPrioHplmnActCfg = NAS_MML_GetPrioHplmnActCfg();

    if (NV_OK != NV_Read(en_NV_Item_PRIO_HPLMNACT_CFG,
                        &stHplmnActCfg, sizeof(NAS_MMC_NVIM_PRIO_HPLMNACT_CFG_STRU)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadPrioHplmnActCfgNvim(): read en_NV_Item_PRIO_HPLMNACT_CFG fail");

        return;
    }

    /* 获取该定制是否激活 */
    if (NAS_MMC_NV_ITEM_ACTIVE == stHplmnActCfg.ucStatus)
    {
        pstPrioHplmnActCfg->ucActiveFlg = VOS_TRUE;
    }
    else
    {
        pstPrioHplmnActCfg->ucActiveFlg = VOS_FALSE;
    }

    /* 获取定制的优先的HPLMNAct,只考虑产品支持的接入技术 */
#if (FEATURE_ON == FEATURE_LTE)

    pstPrioHplmnActCfg->usPrioHplmnAct = (stHplmnActCfg.usPrioHplmnAct & NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE);

#else
    pstPrioHplmnActCfg->usPrioHplmnAct = (stHplmnActCfg.usPrioHplmnAct & NAS_MML_SIM_UE_SUPPORT_RAT);

#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertNivmRegCauseToMmlType
 功能描述  : 将从NV中读取的动作类型转化为MML类型
 输入参数  : enNvCause :nv中定制原因值
 输出参数  : penMmcCause: MML的定义的原因值
 返 回 值  : VOS_TRUE 转化成功
             VOS_FALSE 转化失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月11日
    作    者   : w00166186
    修改内容   : AT&T&DCM新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ConvertNivmRegCauseToMmlType(
    NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM_UINT16                 enNvCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                     *penMmlCause
)
{
    switch (enNvCause)
    {
        case NAS_MMC_NVIM_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            *penMmlCause = NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN;
            break;

        case NAS_MMC_NVIM_REG_FAIL_CAUSE_TIMER_TIMEOUT:
            *penMmlCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;
            break;

        default:
            *penMmlCause = NAS_MML_REG_FAIL_CAUSE_BUTT;
            return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadSingleDomainFailActionListNvim
 功能描述  : 从NV中获取en_NV_Item_SINGLE_DOMAIN_FAIL_ACTION_LIST
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月11日
    作    者   : w00166186
    修改内容   : AT&T&DCM新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadSingleDomainFailActionListNvim(VOS_VOID)
{
    NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU    stSingleDomainFailAction;
    NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_LIST_CTX_STRU    *pstSingleDomainFailActionCtx = VOS_NULL_PTR;
    VOS_UINT32                                          i;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                  enRegCause;
    NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8    enAction;


    PS_MEM_SET(&stSingleDomainFailAction, 0x00, sizeof(stSingleDomainFailAction));

    /* 读取NV */
    if (NV_OK != NV_Read(en_NV_Item_SINGLE_DOMAIN_FAIL_ACTION_LIST,
                         &stSingleDomainFailAction, sizeof(NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSingleDomainFailActionListNvim(): en_NV_Item_SINGLE_DOMAIN_FAIL_ACTION_LIST Error");
        return;
    }

    /* 有效性检查 */
    if (NAS_MMC_NV_ITEM_ACTIVE != stSingleDomainFailAction.ucActiveFlag)
    {
        return;
    }

    /* 个数非法 */
    if (stSingleDomainFailAction.ucCount > NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_MAX_LIST)
    {
        return;
    }

    pstSingleDomainFailActionCtx = NAS_MML_GetSingleDomainFailActionCtx();

    pstSingleDomainFailActionCtx->ucActiveFlag = VOS_TRUE;

    /* 将NV项的值保存到全局变量，需要将NV中定制的ACTION值转换为MMC定义的ACTION值 */
    for (i = 0; i < stSingleDomainFailAction.ucCount; i++)
    {
        if (NAS_MMC_NVIM_REG_DOMAIN_CS == stSingleDomainFailAction.astSingleDomainFailActionList[i].enDomain)
        {
            pstSingleDomainFailActionCtx->astSingleDomainFailActionList[pstSingleDomainFailActionCtx->ucCount].enDomain
                = NAS_MML_REG_DOMAIN_CS;
        }
        else if (NAS_MMC_NVIM_REG_DOMAIN_PS == stSingleDomainFailAction.astSingleDomainFailActionList[i].enDomain)
        {
            pstSingleDomainFailActionCtx->astSingleDomainFailActionList[pstSingleDomainFailActionCtx->ucCount].enDomain
                = NAS_MML_REG_DOMAIN_PS;
        }
        else
        {
            continue;
        }

        if (VOS_FALSE == NAS_MMC_ConvertNivmRegCauseToMmlType(stSingleDomainFailAction.astSingleDomainFailActionList[i].enRegCause, &enRegCause))
        {
            continue;
        }

        if (VOS_FALSE == NAS_MMC_ConvertNivmActionToMmlType(stSingleDomainFailAction.astSingleDomainFailActionList[i].enAction, &enAction))
        {
            continue;
        }


        pstSingleDomainFailActionCtx->astSingleDomainFailActionList[pstSingleDomainFailActionCtx->ucCount].enRegCause
            = enRegCause;

        pstSingleDomainFailActionCtx->astSingleDomainFailActionList[pstSingleDomainFailActionCtx->ucCount].enAction
            = enAction;

        pstSingleDomainFailActionCtx->ucCount++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadRegFailNetWorkFailureCustomFlagNvim
 功能描述  : 从NV中获取en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月11日
    作    者   : w00166186
    修改内容   : AT&T&DCM新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadRegFailNetWorkFailureCustomFlagNvim(VOS_VOID)
{
    NAS_MMC_NVIM_REG_FAIL_NETWORK_FAILURE_CUSTOM_FLG_STRU   stCsRegFailNetFailureCustom;
    VOS_UINT32                                              ulLength;


    PS_MEM_SET(&stCsRegFailNetFailureCustom, 0x00, sizeof(NAS_MMC_NVIM_REG_FAIL_NETWORK_FAILURE_CUSTOM_FLG_STRU));

    ulLength = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_REG_FAIL_NETWORK_FAILURE_CUSTOM_FLG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRegFailNetWorkFailureCustomFlagNvim():WARNING: en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG length Error");
        return;
    }

    /* 读取NV */
    if (NV_OK != NV_Read(en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG,
                         &stCsRegFailNetFailureCustom, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRegFailNetWorkFailureCustomFlagNvim(): en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG Error");
        return;
    }

    /* NV有效性检查 */
    if (NAS_MMC_NV_ITEM_ACTIVE != stCsRegFailNetFailureCustom.ucNvimActiveFlg)
    {
        return;
    }

    /* 赋值到全局变量 */
    NAS_MML_SetRegFailNetWorkFailureCustomFlag(VOS_TRUE);

    return;
}

/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-13, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadPlmnExactlyCompareNvim
 功能描述  : 从NV中获取en_NV_Item_PLMN_EXACTLY_COMPARE_FLG
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月15日
    作    者   : t00212959
    修改内容   : DCM定制需求和遗留问题新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadPlmnExactlyCompareNvim(VOS_VOID)
{
    NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU             stPlmnExactlyCompara;
    VOS_UINT32                                              ulLength;


    PS_MEM_SET(&stPlmnExactlyCompara, 0x00, sizeof(NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU));

    ulLength = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_PLMN_EXACTLY_COMPARE_FLG, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPlmnExactlyCompareNvim():WARNING: en_NV_Item_PLMN_EXACTLY_COMPARE_FLG length Error");
        return;
    }

    /* 读取NV */
    if (NV_OK != NV_Read (en_NV_Item_PLMN_EXACTLY_COMPARE_FLG, &stPlmnExactlyCompara, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPlmnExactlyCompareNvim(): en_NV_Item_PLMN_EXACTLY_COMPARE_FLG Error");
        return;
    }

    /* NV有效性检查 */
    if (VOS_TRUE == stPlmnExactlyCompara.ucPlmnExactlyCompareFlag)
    {
        /* 赋值到全局变量 */
        NAS_MML_SetPlmnExactlyComparaFlg(stPlmnExactlyCompara.ucPlmnExactlyCompareFlag);
    }

    return;
}
/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-13, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadCustomizeServiceNvim
 功能描述  : 从en_NV_Item_CustomizeService中获取是否支持cs语音业务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月8日
    作    者   : z00161729
    修改内容   : DTS2012083007796:无卡支持语音业务时开机应优先选择gu下anycell驻留
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述

  4.日    期   : 2014年3月28日
    作    者   : z00234330
    修改内容   : dts2014032608235,nv8271,设置为0,0,表示不支持语音业务,mmc错误的判断了,认为支持语音业务。
*****************************************************************************/
VOS_VOID NAS_MMC_ReadCustomizeServiceNvim(VOS_VOID)
{
    NAS_NVIM_CUSTOMIZE_SERVICE_STRU                         stCustomServ;
    VOS_UINT32                                              ulLength;


    ulLength = 0;

    PS_MEM_SET(&stCustomServ, (VOS_CHAR)0x0, sizeof(NAS_NVIM_CUSTOMIZE_SERVICE_STRU));

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_CustomizeService, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_CUSTOMIZE_SERVICE_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCustomizeServiceNvim():WARNING: en_NV_Item_CustomizeService length Error");
        return;
    }

    /* 读取en_NV_Item_CustomizeService NV */
    if (NV_OK != NV_Read (en_NV_Item_CustomizeService, &stCustomServ, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCustomizeServiceNvim(): en_NV_Item_CustomizeService Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_DEACTIVE == stCustomServ.ulStatus)
    {
        NAS_MML_SetSupportCsServiceFLg(VOS_FALSE);
    }

    if ((NAS_MMC_NV_ITEM_ACTIVE == stCustomServ.ulStatus)
     && (VOS_FALSE == stCustomServ.ulCustomizeService))
    {
        NAS_MML_SetSupportCsServiceFLg(VOS_FALSE);
    }

    return;

}



/*****************************************************************************
 函 数 名  : NAS_MMC_ReadHplmnRegisterCtrlNvim
 功能描述  : 从NV中获取en_NV_Item_HPLMN_REGISTER_CTRL_FLG
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月29日
    作    者   : w00176964
    修改内容   : U9700_BVT测试:增加NV控制HPLMN注册被拒后是否继续发起注册
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID NAS_MMC_ReadHplmnRegisterCtrlNvim(VOS_VOID)
{
    NAS_MMC_NVIM_HPLMN_REGISTER_CTRL_FLAG_STRU              stHplmnRegisterCtrlFlg;
    VOS_UINT32                                              ulLength;


    PS_MEM_SET(&stHplmnRegisterCtrlFlg, 0x00, sizeof(NAS_MMC_NVIM_HPLMN_REGISTER_CTRL_FLAG_STRU));

    ulLength = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_Hplmn_Register_Ctrl_Flg, &ulLength);

    if (ulLength > sizeof(stHplmnRegisterCtrlFlg))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadHplmnRegisterCtrlNvim():WARNING: en_NV_Item_Hplmn_Register_Ctrl_Flg length Error");
        return;
    }

    /* 读取NV */
    if (NV_OK != NV_Read (en_NV_Item_Hplmn_Register_Ctrl_Flg, &stHplmnRegisterCtrlFlg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadHplmnRegisterCtrlNvim(): en_NV_Item_Hplmn_Register_Ctrl_Flg Error");
        return;
    }

    /* NV有效性检查 */
    if (VOS_TRUE == stHplmnRegisterCtrlFlg.ucHplmnRegisterCtrlFlg)
    {
        /* 赋值到全局变量 */
        NAS_MML_SetHplmnRegisterCtrlFlg(stHplmnRegisterCtrlFlg.ucHplmnRegisterCtrlFlg);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadH3gCtrlNvim
 功能描述  : 从NV中获取en_NV_Item_H3G_CTRL_FLG
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月10日
    作    者   : w00176964
    修改内容   : 增加NV控制H3g漫游的一些特性
*****************************************************************************/
VOS_VOID NAS_MMC_ReadH3gCtrlNvim(VOS_VOID)
{
    NAS_MMC_NVIM_H3G_CTRL_FLAG_STRU     stH3gCtrlFlg;
    VOS_UINT32                          ulLength;

    PS_MEM_SET(&stH3gCtrlFlg, 0x00, sizeof(NAS_MMC_NVIM_H3G_CTRL_FLAG_STRU));

    ulLength = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_H3g_Customization, &ulLength);

    if (ulLength > sizeof(stH3gCtrlFlg))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadH3gCtrlNvim():WARNING: en_NV_Item_H3g_Customization length Error");
        return;
    }

    /* 读取NV */
    if (NV_OK != NV_Read (en_NV_Item_H3g_Customization, &stH3gCtrlFlg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadH3gCtrlNvim(): en_NV_Item_H3g_Customization Error");
        return;
    }

    /* 赋值到全局变量 */
    NAS_MML_SetH3gCtrlFlg(stH3gCtrlFlg.ucH3gCtrlFlg);

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadCellSignReportCfgNvim
 功能描述  : 从NV中读取信号质量上报相关配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月21日
    作    者   : z00161729
    修改内容   : 支持cerssi新增函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年1月9日
    作    者   : t00212959
    修改内容   : DTS2013010809978,增加时间间隔
  4.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_ReadCellSignReportCfgNvim( VOS_VOID )
{

    NAS_MMC_MAINTAIN_CTX_STRU                              *pstMaintainInfo = VOS_NULL_PTR;
    NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU                      stCellSignReportCfg;
    VOS_UINT32                                              ulLength;

    pstMaintainInfo = NAS_MMC_GetMaintainInfo();
    PS_MEM_SET(&stCellSignReportCfg, (VOS_CHAR)0x0, sizeof(stCellSignReportCfg));


    ulLength = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_CELL_SIGN_REPORT_CFG, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCellSignReportCfgNvim():WARNING: en_NV_Item_CELL_SIGN_REPORT_CFG length Error");
        return;
    }

    if(NV_OK != NV_Read(en_NV_Item_CELL_SIGN_REPORT_CFG,
                        &stCellSignReportCfg,
                        ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCellSignReportCfgNvim:read en_NV_Item_CELL_SIGN_REPORT_CFG failed");
        return;
    }

    /* 获取nv项中信号改变门限配置，开机时需通知接入层 */
    pstMaintainInfo->ucSignThreshold = stCellSignReportCfg.ucSignThreshold;

    if (stCellSignReportCfg.ucSignThreshold > NAS_MMC_MAX_SIGN_THRESHOLD)
    {
        pstMaintainInfo->ucSignThreshold = 0;
    }

    /* 获取nv项中信号改变间隔时间，开机时需通知接入层 */
    pstMaintainInfo->ucMinRptTimerInterval = stCellSignReportCfg.ucMinRptTimerInterval;

    if (stCellSignReportCfg.ucMinRptTimerInterval > NAS_MMC_MAX_SIGN_TIMERINTERVAL)
    {
        pstMaintainInfo->ucMinRptTimerInterval = 0;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_WriteCellSignReportCfgNvim
 功能描述  : 写NV项: en_NV_Item_CELL_SIGN_REPORT_CFG
 输入参数  : ucSignThreshold - ^cerssi设置的信号质量门限
             ucMinRptTimerInterval - ^cerssi设置的间隔时间
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011年11月26日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2013年1月9日
    作    者   : t00212959
    修改内容   : DTS2013010809978,增加时间间隔
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_MMC_WriteCellSignReportCfgNvim(VOS_UINT8 ucSignThreshold,VOS_UINT8 ucMinRptTimerInterval)
{
    NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU  stCellSignReportCfg;
    VOS_UINT32                          ulLength;

    PS_MEM_SET(&stCellSignReportCfg, 0x0, sizeof(stCellSignReportCfg));
    ulLength = 0;

    stCellSignReportCfg.ucSignThreshold       = ucSignThreshold;
    stCellSignReportCfg.ucMinRptTimerInterval = ucMinRptTimerInterval;

    (VOS_VOID)NV_GetLength(en_NV_Item_CELL_SIGN_REPORT_CFG, &ulLength);
    if (NV_OK != NV_Write(en_NV_Item_CELL_SIGN_REPORT_CFG,
                          &stCellSignReportCfg,
                          ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_WriteCellSignReportCfgNvim():en_NV_Item_CELL_SIGN_REPORT_CFG Error");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadPlatformRatCapNvim
 功能描述  : 从NV中读取平台接入技术能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : s00217060
    修改内容   : 新增函数
  2.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
  3.日    期   : 2014年12月8日
    作    者   : s00217060
    修改内容   : 在kmsg中增加平台能力的可维可测
  4.日    期   : 2015年3月11日
    作    者   : wx270776
    修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/
VOS_VOID NAS_MMC_ReadPlatformRatCapNvim( VOS_VOID )
{
    NAS_MML_PLATFORM_RAT_CAP_STRU              *pstPlatformRatCap = VOS_NULL_PTR;
    PLATAFORM_RAT_CAPABILITY_STRU               stNvPlatformRatCap;
    NAS_MML_PLATFORM_RAT_TYPE_ENUM_UINT8        enNasPlatformRatCap;
    VOS_UINT32                                  ulLength;
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  i;

    ulLength = 0;
    pstPlatformRatCap = NAS_MML_GetPlatformRatCap();
    PS_MEM_SET(&stNvPlatformRatCap, (VOS_CHAR)0x0, sizeof(stNvPlatformRatCap));

    /* 初始化为GSM ONLY */
    pstPlatformRatCap->ucRatNum      = NAS_MML_MIN_PLATFORM_RAT_NUM;
    pstPlatformRatCap->aenRatPrio[0] = NAS_MML_PLATFORM_RAT_TYPE_GSM;

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_Platform_RAT_CAP, &ulLength);

    if (ulLength > sizeof(PLATAFORM_RAT_CAPABILITY_STRU))
    {
        NAS_MMC_SndOmPlatformRatCap();

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPlatformRatCapNvim():WARNING: en_NV_Item_PLATFORM_RAT_CAP length Error");

        NAS_TRACE_HIGH("en_NV_Item_PLATFORM_RAT_CAP length Error, ulLength = %d", ulLength);
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_READ_PLATFORM_RAT_CAP_NVIM_FAILURE);

        return;
    }

    /* 读NV项en_NV_Item_PLATFORM_RAT_CAP，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_Platform_RAT_CAP,
                         &stNvPlatformRatCap, sizeof(PLATAFORM_RAT_CAPABILITY_STRU)))
    {
        NAS_MMC_SndOmPlatformRatCap();

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPlatformRatCapNvim():WARNING: read en_NV_Item_PLATFORM_RAT_CAP Error");

        NAS_TRACE_HIGH("read en_NV_Item_PLATFORM_RAT_CAP Error");
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_READ_PLATFORM_RAT_CAP_NVIM_FAILURE);

        return;
    }

    /* 有效性检查：无效，直接返回 */
    if (VOS_FALSE == NAS_MMC_IsPlatformRatCapNvimValid(&stNvPlatformRatCap))
    {
        NAS_MMC_SndOmPlatformRatCap();

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPlatformRatCapNvim():WARNING: en_NV_Item_PLATFORM_RAT_CAP Invalid");

        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_READ_PLATFORM_RAT_CAP_NVIM_FAILURE);

        return;
    }

    /* 赋值到全局变量 */
    ucIndex = 0;
    for (i = 0; i < stNvPlatformRatCap.usRatNum; i++)
    {
        if (VOS_TRUE == NAS_MMC_ConvertNvimTypePlatformRatCapToNasType((stNvPlatformRatCap.aenRatList[i]),
                                                                        &enNasPlatformRatCap))
        {
            pstPlatformRatCap->aenRatPrio[ucIndex] = enNasPlatformRatCap;
            ucIndex++;
        }
    }

    if (ucIndex > 0)
    {
        pstPlatformRatCap->ucRatNum = ucIndex;
    }

    /* 可维可测，打印LOG */
    NAS_MMC_SndOmPlatformRatCap();

    NAS_TRACE_HIGH("read en_NV_Item_PLATFORM_RAT_CAP correct, RatNum = %d, aenRatList[0]= %d, aenRatList[1]= %d, aenRatList[2]= %d, aenRatList[3]= %d, aenRatList[4]= %d,aenRatList[5]= %d, aenRatList[6]= %d",
                    stNvPlatformRatCap.usRatNum, stNvPlatformRatCap.aenRatList[0], stNvPlatformRatCap.aenRatList[1], stNvPlatformRatCap.aenRatList[2], stNvPlatformRatCap.aenRatList[3], stNvPlatformRatCap.aenRatList[4], stNvPlatformRatCap.aenRatList[5], stNvPlatformRatCap.aenRatList[6]);

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlatformRatCapNvimValid
 功能描述  : 从NV中读取平台接入技术能力
 输入参数  : pstNvPlatformRatCap 平台接入技术能力的NV项结构体指针
 输出参数  : 无
 返 回 值  : VOS_TRUE:平台接入技术能力NV项有效
             VOS_FALSE:平台接入技术能力NV项无效
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : s00217060
    修改内容   : 新增函数
  2.日    期   : 2013年8月29日
    作    者   : w00242748
    修改内容   : KLOC告警清理
  3.日    期   : 2014年6月17日
    作    者   : z00234330
    修改内容   : PCINT清理
  4.日    期   : 2014年12月8日
    作    者   : s00217060
    修改内容   : kmsg中增加平台能力的可维可测
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlatformRatCapNvimValid(
    PLATAFORM_RAT_CAPABILITY_STRU              *pstNvPlatformRatCap
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /* 如果平台支持的接入技术个数为0，返回无效 */
    /* Modified by z00234330 for PCLINT清理, 2014-06-24, begin */
    if ((0 == pstNvPlatformRatCap->usRatNum)
      ||( pstNvPlatformRatCap->usRatNum > PLATFORM_MAX_RAT_NUM))
    /* Modified by z00234330 for PCLINT清理, 2014-06-24, end */
    {
        NAS_TRACE_HIGH("en_NV_Item_PLATFORM_RAT_CAP RatNum Invalid, RatNum = %d", pstNvPlatformRatCap->usRatNum);

        return VOS_FALSE;
    }

    for (i = 0; i < pstNvPlatformRatCap->usRatNum; i++)
    {
        /* 如果平台支持的接入技术有重复，返回无效  */
        for (j = i + 1 ; j < pstNvPlatformRatCap->usRatNum; j++ )
        {
            if (pstNvPlatformRatCap->aenRatList[i] == pstNvPlatformRatCap->aenRatList[j])
            {
                NAS_TRACE_HIGH("en_NV_Item_PLATFORM_RAT_CAP Rat duplicate, RatNum = %d, aenRatList[%d] = aenRatList[%d] = %d", pstNvPlatformRatCap->usRatNum, i, j, pstNvPlatformRatCap->aenRatList[i]);

                return VOS_FALSE;
            }
        }

        /* 如果平台支持的接入技术无效，返回无效 */
        if (PLATFORM_RAT_BUTT <= pstNvPlatformRatCap->aenRatList[i])
        {
            NAS_TRACE_HIGH("en_NV_Item_PLATFORM_RAT_CAP Rat invalid, aenRatList[%d] = %d", i, pstNvPlatformRatCap->aenRatList[i]);

            return VOS_FALSE;
        }
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertNvimTypePlatformRatCapToNasType
 功能描述  : 把NV类型的平台接入技术能力转换成NAS类型的
 输入参数  : enNvPlatformRatCap:NV类型的平台接入技术能力
 输出参数  : *penNasPlatformRatCap:NAS类型的平台接入技术能力
 返 回 值  :  VOS_TRUE:转换成功
              VOS_FALSE:转换失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : s00217060
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_ConvertNvimTypePlatformRatCapToNasType(
    PLATFORM_RAT_TYPE_ENUM_UINT16                       enNvPlatformRatCap,
    NAS_MML_PLATFORM_RAT_TYPE_ENUM_UINT8               *penNasPlatformRatCap
)
{
    VOS_UINT32                          ulRslt;
    ulRslt  = VOS_FALSE;

    switch (enNvPlatformRatCap)
    {
        case PLATFORM_RAT_GSM:
            *penNasPlatformRatCap = NAS_MML_PLATFORM_RAT_TYPE_GSM;
            ulRslt                = VOS_TRUE;
            break;

        case PLATFORM_RAT_WCDMA:
            *penNasPlatformRatCap = NAS_MML_PLATFORM_RAT_TYPE_WCDMA;
            ulRslt                = VOS_TRUE;
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        case PLATFORM_RAT_TDS:
            *penNasPlatformRatCap = NAS_MML_PLATFORM_RAT_TYPE_TD_SCDMA;
            ulRslt                = VOS_TRUE;
            break;
#endif

#if   (FEATURE_ON == FEATURE_LTE)
        case PLATFORM_RAT_LTE:
            *penNasPlatformRatCap = NAS_MML_PLATFORM_RAT_TYPE_LTE;
            ulRslt                = VOS_TRUE;
            break;
#endif
        default:
            ulRslt                = VOS_FALSE;
            break;
    }
    return ulRslt;

}


#if  (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadEnableLteTimerLenNvim
 功能描述  : 从NV中获取enable lte定时器时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2015年4月24日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_MMC_ReadEnableLteTimerLenNvim(VOS_VOID)
{
    NAS_MMC_NVIM_ENABLE_LTE_TIMER_LEN_STRU                  stEnableLteTimerLen;
    VOS_UINT32                                              ulLength;

    PS_MEM_SET(&stEnableLteTimerLen, 0x00, sizeof(stEnableLteTimerLen));
    ulLength = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_Enable_Lte_Timer_Len, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_ENABLE_LTE_TIMER_LEN_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadEnableLteTimerLenNvim(): en_NV_Item_Enable_Lte_Timer_Len length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_Enable_Lte_Timer_Len,
                         &stEnableLteTimerLen, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadEnableLteTimerLenNvim(): en_NV_Item_Enable_Lte_Timer_Len error");
        return;
    }

    /* nv项激活且设置enable lte定时器时长为0，则更新为默认值5分钟 */
    if (VOS_TRUE == stEnableLteTimerLen.ucNvimActiveFlag)
    {
        if (0 == stEnableLteTimerLen.ucCsfbEmgCallEnableLteTimerLen)
        {
            NAS_MML_SetCsfbEmgCallEnableLteTimerLen(NAS_MML_ENABLE_LTE_TIMER_DEFAULT_LEN);
        }
        else
        {
            /* 更新MML全局变量中的enable lte定时器时长,nv项单位是分钟，启定时器单位是毫秒 */
            NAS_MML_SetCsfbEmgCallEnableLteTimerLen(stEnableLteTimerLen.ucCsfbEmgCallEnableLteTimerLen * NAS_MML_SIXTY_SECOND
                                         * NAS_MML_ONE_THOUSAND_MILLISECOND);
        }

        if (0 == stEnableLteTimerLen.ucCsPsMode1EnableLteTimerLen)
        {
            NAS_MML_SetCsPsMode13GPPEnableLteTimerLen(NAS_MML_ENABLE_LTE_TIMER_DEFAULT_LEN);
        }
        else
        {
            NAS_MML_SetCsPsMode13GPPEnableLteTimerLen(stEnableLteTimerLen.ucCsPsMode1EnableLteTimerLen * NAS_MML_SIXTY_SECOND
                                         * NAS_MML_ONE_THOUSAND_MILLISECOND);
        }

        if (NAS_MML_VOICE_NOT_PREFER_DISABLED_PLMN_MAX_INVALID_PERIOD == stEnableLteTimerLen.ucLteVoiceNotAvailPlmnForbiddenPeriod)
        {
            NAS_MML_SetVoiceNotAvailPlmnForbiddenPeriod(NAS_MML_MAX_TIME_SLICE);
        }
        else
        {
            NAS_MML_SetVoiceNotAvailPlmnForbiddenPeriod(stEnableLteTimerLen.ucLteVoiceNotAvailPlmnForbiddenPeriod * NAS_MML_SIXTY_SECOND * NAS_MML_ONE_THOUSAND_MILLISECOND);
        }
    }

    return;
}

/* Added by c00318887 for 移植T3402 , 2015-6-17, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadDisableLteStartT3402EnableLteCfgNvim
 功能描述  : 读取en_NV_Item_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG nv项内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月28日
    作    者   : c00318887
    修改内容   : for file refresh 新增
*****************************************************************************/
VOS_VOID NAS_MMC_ReadDisableLteStartT3402EnableLteCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG_STRU        stDisableLteStartT3402EnableLteCfg;
    VOS_UINT32                                                      ulLength;

    ulLength = 0;
    PS_MEM_SET(&stDisableLteStartT3402EnableLteCfg, 0x0, sizeof(NAS_MMC_NVIM_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG_STRU));

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadDisableLteStartT3402EnableLteCfgNvim(): en_NV_Item_Enable_Lte_Timer_Len_Using_T3402_CFG length Error");
        return;
    }


    if (NV_OK != NV_Read (en_NV_Item_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG, &stDisableLteStartT3402EnableLteCfg, sizeof(NAS_MMC_NVIM_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadDisableLteStartT3402EnableLteCfgNvim():WARNING: en_NV_Item_Enable_Lte_Timer_Len_Using_T3402_CFG Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stDisableLteStartT3402EnableLteCfg.ucT3402Flag)
    {
        NAS_MML_SetDisableLteStartT3402EnableLteFlag(stDisableLteStartT3402EnableLteCfg.ucT3402Flag);
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stDisableLteStartT3402EnableLteCfg.ucHighPrioRatTimerNotEnableLteFlag)
    {
        NAS_MML_SetHighPrioRatBgEnableLteFlag(NAS_MML_HIGH_PRIO_RAT_BG_SEARCH_PROC_LTE_NOT_ENABLE_LTE);
    }

    return;
}

/* Added by c00318887 for 移植T3402 , 2015-6-17, end */


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadCsfbRauFollowOnFlgNvim
 功能描述  : 读取NV项中，Csfb mt/mo过程中，RAU是否需要带follow on标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月25日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2013年7月25日
    作    者   : w00242748
    修改内容   : DTS2014053105098:CSFB mo是否需要带follow on增加NV控制
*****************************************************************************/
VOS_VOID NAS_MMC_ReadCsfbRauFollowOnFlgNvim(VOS_VOID)
{
    NAS_MMC_CSFB_RAU_FOLLOW_ON_FLAG_STRU                    stCsfbRauFollowOnFlg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    PS_MEM_SET(&stCsfbRauFollowOnFlg, 0x00, sizeof(stCsfbRauFollowOnFlg));

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_CSFB_RAU_FOLLOW_ON_FLAG, &ulLength);

    if (ulLength > sizeof(NAS_MMC_CSFB_RAU_FOLLOW_ON_FLAG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCsfbRauFollowOnFlgNvim(): en_NV_Item_CSFB_RAU_FOLLOW_ON_FLAG length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_CSFB_RAU_FOLLOW_ON_FLAG,
                         &stCsfbRauFollowOnFlg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCsfbRauFollowOnFlgNvim(): en_NV_Item_CSFB_RAU_FOLLOW_ON_FLAG error");
        return;
    }

    if (VOS_TRUE == stCsfbRauFollowOnFlg.ucIsRauNeedFollowOnCsfbMtFlg)
    {
         NAS_MML_SetIsRauNeedFollowOnCsfbMtFlg(VOS_TRUE);
    }

    if (VOS_TRUE == stCsfbRauFollowOnFlg.ucIsRauNeedFollowOnCsfbMoFlg)
    {
         NAS_MML_SetIsRauNeedFollowOnCsfbMoFlg(VOS_TRUE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadLteCustomMccInfoNvim
 功能描述  : 读取NV 0xD22A，获取是否删除FDD的总控开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月27日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadLteCustomMccInfoNvim(VOS_VOID)
{
    LTE_CUSTOM_MCC_INFO_STRU            stLteCustomMccInfo;
    VOS_UINT32                          ulLength;

    ulLength = 0;
    PS_MEM_SET(&stLteCustomMccInfo, 0x00, sizeof(stLteCustomMccInfo));

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(EN_NV_ID_LTE_CUSTOM_MCC_INFO, &ulLength);

    if (ulLength > sizeof(LTE_CUSTOM_MCC_INFO_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteCustomMccInfoNvim(): EN_NV_ID_LTE_CUSTOM_MCC_INFO length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(EN_NV_ID_LTE_CUSTOM_MCC_INFO,
                         &stLteCustomMccInfo, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteCustomMccInfoNvim(): EN_NV_ID_LTE_CUSTOM_MCC_INFO error");
        return;
    }

    if (VOS_TRUE == stLteCustomMccInfo.ucSwitchFlag)
    {
         NAS_MML_SetIsDelFddBandSwitchOnFlg(VOS_TRUE);
    }

    return;
}


#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadCsgCfgNvim
 功能描述  : 读CSG配置nv项
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月14日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID NAS_MMC_ReadCsgCfgNvim(VOS_VOID)
{
    NAS_NVIM_CSG_CTRL_CFG_STRU         stCsgCtrlCfgNvim;
    VOS_UINT32                         ulLength;

    PS_MEM_SET(&stCsgCtrlCfgNvim, 0x00, sizeof(stCsgCtrlCfgNvim));
    ulLength = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_CSG_CTRL_CFG, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_CSG_CTRL_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCsgCfgNvim():en_NV_Item_CSG_CTRL_CFG length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_CSG_CTRL_CFG,
                         &stCsgCtrlCfgNvim, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadCsgCfgNvim(): en_NV_Item_CSG_CTRL_CFG error");
        return;
    }

    if (VOS_TRUE == stCsgCtrlCfgNvim.ucIsSupportCsgFlag)
    {
        NAS_MML_SetCsgSupportFlag(VOS_TRUE);
    }

    if (VOS_TRUE == stCsgCtrlCfgNvim.ucCsgListOnlyReportOperatorCsgListFlag)
    {
        NAS_MML_SetOnlyReportOperatorCsgListFlag(VOS_TRUE);
    }

    return;
}

#endif

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadSvlteSupportFlagNvim
 功能描述  : 读取svlte是否支持nv
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月3日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadSvlteSupportFlagNvim(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    SVLTE_SUPPORT_FLAG_STRU             stSvlteSupportFlag;
    VOS_UINT32                          ulLength;

    ulLength = 0;
    PS_MEM_SET(&stSvlteSupportFlag, 0x00, sizeof(stSvlteSupportFlag));

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_SVLTE_FLAG, &ulLength);

    if (ulLength > sizeof(SVLTE_SUPPORT_FLAG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSvlteSupportFlagNvim(): en_NV_Item_SVLTE_FLAG length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_SVLTE_FLAG,
                         &stSvlteSupportFlag, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSvlteSupportFlagNvim(): en_NV_Item_SVLTE_FLAG error");
        return;
    }

    if (VOS_TRUE == stSvlteSupportFlag.ucSvlteSupportFlag)
    {
         NAS_MML_SetSvlteSupportFlag(VOS_TRUE);
    }
#endif

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ReadPsTransferCfgNvim
 功能描述  : 初始化PS域迁移NV
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年05月28日
    作    者   : x00203213
    修改内容   : V9R1C53 读取PS TRANSFER的NV
*****************************************************************************/
VOS_VOID NAS_MMC_ReadPsTransferCfgNvim(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

    MTC_NV_PS_TRANSFER_CFG_STRU         stPsTransferCfg;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    PS_MEM_SET(&stPsTransferCfg, 0x00, sizeof(stPsTransferCfg));

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_PS_TRANSFER_CFG, &ulLength);

    if (ulLength > sizeof(MTC_NV_PS_TRANSFER_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPsTransferCfgNvim(): en_NV_Item_PS_TRANSFER_CFG length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_PS_TRANSFER_CFG,
                         &stPsTransferCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPsTransferCfgNvim(): en_NV_Item_PS_TRANSFER_CFG error");
        return;
    }

    if (MTC_PS_TRANSFER_OFF_AREA == stPsTransferCfg.enSolutionCfg)
    {
         NAS_MML_SetPsTransferOffAreaModeFlag(VOS_TRUE);
    }

#endif

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ReadDsdaPlmnSearchEnhancedCfgNvim
 功能描述  : 控制通过两个Modem的信息交互的增强型的搜索策略；当前支持的策略为：
             通过另一Modem的PLMN信息,控制FDD搜网是否跳过的策略。
             比如GUTL+G的版本，当副卡已经驻留在国内G网的时候，主卡搜网可以跳过FDD的搜索（中移动国内只需要支持TDD模式）
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月23日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
  3.日    期   : 2014年1月26日
    作    者   : z00161729
    修改内容   : DTS2014012305088:支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，
                 通过历史频点支持NCELL搜索。如果Modem1传递过来的邻区信息存在，以邻区信息NCELL搜索
*****************************************************************************/
VOS_VOID NAS_MMC_ReadDsdaPlmnSearchEnhancedCfgNvim(VOS_VOID)
{
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU                   stDsdaPlmnSearchEnhancedCfg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    PS_MEM_SET(&stDsdaPlmnSearchEnhancedCfg, 0x00, sizeof(stDsdaPlmnSearchEnhancedCfg));

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG, &ulLength);

    if (ulLength > sizeof(NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadDsdaPlmnSearchEnhancedCfgNvim(): en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG,
                         &stDsdaPlmnSearchEnhancedCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadDsdaPlmnSearchEnhancedCfgNvim(): en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG error");
        return;
    }

    if (NAS_MMC_UTRAN_SKIP_W_PLMNSEARCH_MASK == (stDsdaPlmnSearchEnhancedCfg.usSolutionMask & NAS_MMC_UTRAN_SKIP_W_PLMNSEARCH_MASK))
    {
         NAS_MMC_SetUtranSkipWPlmnSearchFlag(VOS_TRUE);
    }

    if (NAS_MMC_SUPPORT_NCELL_SEARCH_MASK == (stDsdaPlmnSearchEnhancedCfg.usSolutionMask & NAS_MMC_SUPPORT_NCELL_SEARCH_MASK))
    {
        NAS_MMC_SetNcellSearchFlag(VOS_TRUE);
        NAS_MMC_SetNcellSearchFirstTimerLen(stDsdaPlmnSearchEnhancedCfg.ucSolution2NcellQuickSearchTimer);
        NAS_MMC_SetNcellSearchSecondTimerLen(stDsdaPlmnSearchEnhancedCfg.ucSolution2NcellQuickSearchTimer2);
    }

#endif

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadRoamPlmnSelectionSortCfgNvim
 功能描述  : 读取漫游搜网排序配置
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月23日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2015年10月28日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0

*****************************************************************************/
VOS_VOID NAS_MMC_ReadRoamPlmnSelectionSortCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_ROAM_PLMN_SELECTION_SORT_CFG_STRU          stNvRoamSortCfg;
    VOS_UINT32                                              ulLength;


    PS_MEM_SET(&stNvRoamSortCfg, 0, sizeof(NAS_MMC_NVIM_ROAM_PLMN_SELECTION_SORT_CFG_STRU));
    ulLength    = 0;

    /* 如果是虚拟sim卡，则不需要支持漫游优化，否则可能搜网更慢 */
    if (VOS_TRUE == USIMM_VsimIsActive())
    {
        NAS_MMC_SetRoamPlmnSelectionSortActiveFlg(VOS_FALSE);

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRoamPlmnSelectionSortCfgNvim: Is virtual sim!");
        return;
    }

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_Roam_Plmn_Selection_Sort_Cfg, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_ROAM_PLMN_SELECTION_SORT_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRoamPlmnSelectionSortCfgNvim(): en_NV_Item_Roam_Plmn_Selection_Sort_Cfg length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_Roam_Plmn_Selection_Sort_Cfg,
                         &stNvRoamSortCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRoamPlmnSelectionSortCfgNvim(): en_NV_Item_Roam_Plmn_Selection_Sort_Cfg error");
        return;
    }

    NAS_MMC_SetRoamPlmnSelectionSortActiveFlg(VOS_FALSE);
    NAS_MMC_SetSrchUOplmnPriorToDplmnFlg(VOS_FALSE);

    if (VOS_TRUE == stNvRoamSortCfg.ucRoamPlmnSelectionSortFlg)
    {
        NAS_MMC_SetRoamPlmnSelectionSortActiveFlg(VOS_TRUE);
    }

    if (VOS_TRUE == stNvRoamSortCfg.ucSrchUOplmnPriorToDplmnFlg)
    {
        NAS_MMC_SetSrchUOplmnPriorToDplmnFlg(VOS_TRUE);
    }

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ReadNonOosPlmnSearchFeatureSupportCfgNvim
 功能描述  : 读取history搜定时器时长
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月23日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年10月28日
    作    者   : h00281185
    修改内容   : 將原有History NV改為 en_NV_Item_Non_Oos_Plmn_Search_Feature_Support_Cfg

*****************************************************************************/
VOS_VOID NAS_MMC_ReadNonOosPlmnSearchFeatureSupportCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU                   stNonOosPlmnSearchFeatureSupportCfg;
    VOS_UINT32                                                                  ulLength;
    NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU                       *pstNonOosPLMNSearchFeatureSupportCfg  = VOS_NULL_PTR;

    pstNonOosPLMNSearchFeatureSupportCfg  = NAS_MMC_GetNonOosPlmnSearchFeatureSupportCfg();
    ulLength        = 0;
    PS_MEM_SET(&stNonOosPlmnSearchFeatureSupportCfg, 0x00, sizeof(stNonOosPlmnSearchFeatureSupportCfg));

    /* 如果是测试卡，不读取NV，采用默认值 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        pstNonOosPLMNSearchFeatureSupportCfg->ucHistoryActiveFlg  = VOS_FALSE;
        pstNonOosPLMNSearchFeatureSupportCfg->ucPrefBandActiveFlg = VOS_FALSE;
        pstNonOosPLMNSearchFeatureSupportCfg->enSearchTypeAfterHistoryInAreaLostScene = NAS_MMC_PLMN_SEARCH_TYPE_AFTER_HISTORY_SPEC;
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadNonOosPlmnSearchFeatureSupportCfgNvim(): Test Card.");
        return;
    }

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_Non_Oos_Plmn_Search_Feature_Support_Cfg, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadNonOosPlmnSearchFeatureSupportCfgNvim(): en_NV_Item_History_Timer_Len_Cfg length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_Non_Oos_Plmn_Search_Feature_Support_Cfg,
                         &stNonOosPlmnSearchFeatureSupportCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadNonOosPlmnSearchFeatureSupportCfgNvim(): en_NV_Item_History_Timer_Len_Cfg error");
        return;
    }

    if (VOS_TRUE == stNonOosPlmnSearchFeatureSupportCfg.ucHistoryActiveFlg)
    {
        pstNonOosPLMNSearchFeatureSupportCfg->ucHistoryActiveFlg  = stNonOosPlmnSearchFeatureSupportCfg.ucHistoryActiveFlg;
    }

    if (VOS_TRUE == stNonOosPlmnSearchFeatureSupportCfg.ucPrefBandActiveFlg)
    {
        pstNonOosPLMNSearchFeatureSupportCfg->ucPrefBandActiveFlg = stNonOosPlmnSearchFeatureSupportCfg.ucPrefBandActiveFlg;
    }

    pstNonOosPLMNSearchFeatureSupportCfg->enSearchTypeAfterHistoryInAreaLostScene = stNonOosPlmnSearchFeatureSupportCfg.ucSearchTypeAfterHistoryInAreaLostScene;

    if (NAS_MMC_PLMN_SEARCH_TYPE_AFTER_HISTORY_BUTT <= stNonOosPlmnSearchFeatureSupportCfg.ucSearchTypeAfterHistoryInAreaLostScene)
    {
        pstNonOosPLMNSearchFeatureSupportCfg->enSearchTypeAfterHistoryInAreaLostScene = NAS_MMC_PLMN_SEARCH_TYPE_AFTER_HISTORY_NONE;
    }

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadOosPlmnSearchStrategyCfgNvim
 功能描述  : 读取搜网定时器次数和时长
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : h00281185
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ReadOosPlmnSearchStrategyCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_OOS_PLMN_SEARCH_STRATEGY_CFG_STRU          stOosPlmnSearchStrategyCfg;
    VOS_UINT32                                              ulLength;
    NAS_MMC_OOS_PLMN_SEARCH_STRATEGY_INFO_STRU             *pstOosPlmnSearchStrategyInfo  = VOS_NULL_PTR;

    pstOosPlmnSearchStrategyInfo                      = NAS_MMC_GetOosPlmnSearchStrategyInfo();
    ulLength                                      = 0;

    PS_MEM_SET(&stOosPlmnSearchStrategyCfg, 0x00, sizeof(stOosPlmnSearchStrategyCfg));

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_Oos_Plmn_Search_Strategy_Cfg, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_OOS_PLMN_SEARCH_STRATEGY_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadOosPlmnSearchStrategyCfgNvim(): en_NV_Item_Oos_Plmn_Search_Strategy_Cfg length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_Oos_Plmn_Search_Strategy_Cfg,
                         &stOosPlmnSearchStrategyCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadOosPlmnSearchStrategyCfgNvim(): en_NV_Item_Oos_Plmn_Search_Strategy_Cfg error");
        return;
    }

    /* 第一阶段定时器参数更新到全局变量  */
    if (0 == stOosPlmnSearchStrategyCfg.stPhaseOnePatternCfg.usSleepTimerLen)
    {
        pstOosPlmnSearchStrategyInfo->stPhaseOnePatternCfg.usSleepTimerLen   = NAS_MCC_NVIM_PHASE_ONE_DEFUALT_SLEEP_TIME_LEN;
    }
    else
    {
        pstOosPlmnSearchStrategyInfo->stPhaseOnePatternCfg.usSleepTimerLen   = stOosPlmnSearchStrategyCfg.stPhaseOnePatternCfg.usSleepTimerLen;
    }
    pstOosPlmnSearchStrategyInfo->stPhaseOnePatternCfg.ucHistoryNum          = stOosPlmnSearchStrategyCfg.stPhaseOnePatternCfg.ucHistoryNum;
    pstOosPlmnSearchStrategyInfo->stPhaseOnePatternCfg.ucPrefBandNum         = stOosPlmnSearchStrategyCfg.stPhaseOnePatternCfg.ucPrefBandNum;
    pstOosPlmnSearchStrategyInfo->stPhaseOnePatternCfg.ucFullBandNum         = stOosPlmnSearchStrategyCfg.stPhaseOnePatternCfg.ucFullBandNum;
    pstOosPlmnSearchStrategyInfo->stPhaseOnePatternCfg.usTotalTimerLen       = stOosPlmnSearchStrategyCfg.stPhaseOnePatternCfg.usTotalTimerLen;

    /* 若所有Timer皆关闭, default设定FullBandNum为1次 */
    if((0 == pstOosPlmnSearchStrategyInfo->stPhaseOnePatternCfg.ucHistoryNum)
     &&(0 == pstOosPlmnSearchStrategyInfo->stPhaseOnePatternCfg.ucPrefBandNum)
     &&(0 == pstOosPlmnSearchStrategyInfo->stPhaseOnePatternCfg.ucFullBandNum))
    {
        pstOosPlmnSearchStrategyInfo->stPhaseOnePatternCfg.ucFullBandNum = NAS_MCC_NVIM_PHASE_ONE_DEFAULT_FULL_BAND_NUM;
    }

    /* 第二阶段定时器参数更新到全局变量  */
    if (0 == stOosPlmnSearchStrategyCfg.stPhaseTwoPatternCfg.usSleepTimerLen)
    {
        pstOosPlmnSearchStrategyInfo->stPhaseTwoPatternCfg.usSleepTimerLen   = NAS_MCC_NVIM_PHASE_TWO_DEFAULT_SLEEP_TIME_LEN;
    }
    else
    {
        pstOosPlmnSearchStrategyInfo->stPhaseTwoPatternCfg.usSleepTimerLen   = stOosPlmnSearchStrategyCfg.stPhaseTwoPatternCfg.usSleepTimerLen;
    }
    pstOosPlmnSearchStrategyInfo->stPhaseTwoPatternCfg.ucHistoryNum          = stOosPlmnSearchStrategyCfg.stPhaseTwoPatternCfg.ucHistoryNum;
    pstOosPlmnSearchStrategyInfo->stPhaseTwoPatternCfg.ucPrefBandNum         = stOosPlmnSearchStrategyCfg.stPhaseTwoPatternCfg.ucPrefBandNum;
    pstOosPlmnSearchStrategyInfo->stPhaseTwoPatternCfg.usTotalTimerLen       = stOosPlmnSearchStrategyCfg.stPhaseTwoPatternCfg.usTotalTimerLen;
    /* 由於目前没有实现第三阶段与第四阶段的搜网, 所以第二阶段的FullBandNum不从NV取. 此处先给定值*/
    pstOosPlmnSearchStrategyInfo->stPhaseTwoPatternCfg.ucFullBandNum         = NAS_MCC_NVIM_PHASE_TWO_DEFAULT_FULL_BAND_NUM;

    /* 第三和第四阶段的NV结构保留,变数不处理 */
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadGetGeoCfgInfoNvim
 功能描述  : 读取获取国家码的配置信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ReadGetGeoCfgInfoNvim(VOS_VOID)
{
    NAS_NVIM_GET_GEO_CFG_INFO_STRU                          stGetGeoCfgInfo;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              i;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstGetGeoRatList  = VOS_NULL_PTR;

    pstGetGeoRatList  = NAS_MML_GetGeoPrioRatList();

    ulLength = 0;
    PS_MEM_SET(&stGetGeoCfgInfo, 0x00, sizeof(NAS_NVIM_GET_GEO_CFG_INFO_STRU));

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_Get_Geo_Cfg_Info, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_GET_GEO_CFG_INFO_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadGetGeoCfgInfoNvim(): en_NV_Item_Get_Geo_Cfg_Info length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_Get_Geo_Cfg_Info, &stGetGeoCfgInfo, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadGetGeoCfgInfoNvim(): en_NV_Item_Get_Geo_Cfg_Info error");
        return;
    }

    /* NV项未打开时，接入技术无效 */
    if (VOS_FALSE == stGetGeoCfgInfo.ucActiveFlag)
    {
        return;
    }

    /* 超过最大个数按最大个数处理 */
    if (NAS_MML_MAX_RAT_NUM < stGetGeoCfgInfo.stGetGeoPrioRatList.ucRatOrderNum)
    {
        stGetGeoCfgInfo.stGetGeoPrioRatList.ucRatOrderNum   = NAS_MML_MAX_RAT_NUM;
    }

    for (i = 0; i < stGetGeoCfgInfo.stGetGeoPrioRatList.ucRatOrderNum; i++)
    {
        pstGetGeoRatList->aucRatPrio[i]  = stGetGeoCfgInfo.stGetGeoPrioRatList.aucRatOrder[i];
    }

    pstGetGeoRatList->ucRatNum  = stGetGeoCfgInfo.stGetGeoPrioRatList.ucRatOrderNum;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadIsrSupportNvim
 功能描述  : 读取ISR是否激活的NVIM项
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月23日
    作    者   : z00234330
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_ReadIsrSupportNvim( VOS_VOID )
{
    VOS_UINT32                          ulLen;
    NAS_NVIM_ISR_CFG_STRU               stIsrCfg;

    ulLen = 0;

    PS_MEM_SET(&stIsrCfg, 0x00, sizeof(stIsrCfg));
    (VOS_VOID)NV_GetLength(en_NV_Item_NasIsrSupport, &ulLen);

    /* 读NV项en_NV_Item_NasIsrSupport，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_NasIsrSupport,
                         &stIsrCfg, ulLen))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadIsrSupportNvim():WARNING: read en_NV_Item_NasIsrSupport Error");

        return;
    }

    if ( VOS_TRUE == stIsrCfg.ucIsrSupport)
    {
        NAS_MML_SetIsrSupportFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetIsrSupportFlg(VOS_FALSE);
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadRefreshRplmnWhenEplmnInvalidCfgNvim
 功能描述  : 读取EPLMN无效时候是否删除RPLMN配置
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ReadRefreshRplmnWhenEplmnInvalidCfgNvim(VOS_VOID)
{
    NAS_NVIM_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG_STRU      stRefreshRplmnCfg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    PS_MEM_SET(&stRefreshRplmnCfg, 0x00, sizeof(stRefreshRplmnCfg));

    /* USIM卡时候不删除，按默认值处理 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return ;
    }

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRefreshRplmnWhenEplmnInvalidCfgNvim(): en_NV_Item_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG,
                         &stRefreshRplmnCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRefreshRplmnWhenEplmnInvalidCfgNvim(): en_NV_Item_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG error");
        return;
    }

    /* 不需要删除RPLMN的配置，其他默认需要删除RPLMN */
    if (VOS_FALSE == stRefreshRplmnCfg.ucDeleteRplmnFlg)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "DeleteRplmnWhenEplmnInvalidFlg IS FALSE");
        NAS_MML_SetDeleteRplmnWhenEplmnInvalidFlg(VOS_FALSE);

        return;
    }

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "DeleteRplmnWhenEplmnInvalidFlg IS TRUE");

    NAS_MML_SetDeleteRplmnWhenEplmnInvalidFlg(VOS_TRUE);

    return;
}


#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadErrlogCtrlInfoNvim
 功能描述  : 根据NV:en_NV_Item_ErrLogCtrlInfo初始化ErrlogInfo
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadErrlogCtrlInfoNvim(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;
    NV_ID_ERR_LOG_CTRL_INFO_STRU        stErrorLogCtrlInfo;

    ulLength = 0;
    PS_MEM_SET(&stErrorLogCtrlInfo, 0x00, sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_ErrLogCtrlInfo, &ulLength);

    ulResult = NV_Read(en_NV_Item_ErrLogCtrlInfo,
                       &stErrorLogCtrlInfo,
                       ulLength);

    if (ulResult == NV_OK)
    {
        NAS_MML_SetErrlogCtrlFlag(stErrorLogCtrlInfo.ucAlmStatus);
        NAS_MML_SetErrlogAlmLevel(stErrorLogCtrlInfo.ucAlmLevel);
    }
    else
    {
        NAS_MML_SetErrlogCtrlFlag(VOS_FALSE);
        NAS_MML_SetErrlogAlmLevel(NAS_ERR_LOG_CTRL_LEVEL_CRITICAL);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadErrlogNwSrchRecordcfgNvim
 功能描述  : 根据NV:en_NV_Item_Nw_Search_Chr_Record_Cfg初始化ErrlogInfo
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : f00179208
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadErrlogNwSrchRecordcfgNvim(VOS_VOID)
{
    VOS_UINT32                              ulResult;
    VOS_UINT32                              ulLength;
    NAS_NVIM_NW_SEARCH_CHR_RECORD_CFG_STRU  stRecordCfg;

    ulLength = 0;
    PS_MEM_SET(&stRecordCfg, 0x00, sizeof(NAS_NVIM_NW_SEARCH_CHR_RECORD_CFG_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_Nw_Search_Chr_Record_Cfg, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_NW_SEARCH_CHR_RECORD_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadErrlogNwSrchRecordcfgNvim():WARNING: en_NV_Item_Nw_Search_Chr_Record_Cfg length Error");

        return;
    }

    ulResult = NV_Read(en_NV_Item_Nw_Search_Chr_Record_Cfg,
                       &stRecordCfg,
                       ulLength);

    if (ulResult != NV_OK)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadErrlogNwSrchRecordcfgNvim():WARNING: read en_NV_Item_Nw_Search_Chr_Record_Cfg Error");

        NAS_MML_SetErrLogNwSrchCfgActiveFlag(VOS_FALSE);
        NAS_MML_SetErrLogNwSrchCfgRecordNum(0);

        return;
    }

    NAS_MML_SetErrLogNwSrchCfgActiveFlag(stRecordCfg.ucActiveFlag);
    NAS_MML_SetErrLogNwSrchCfgRecordNum(stRecordCfg.ulRecordNum);

    /* 测试卡，则不开启该功能 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        NAS_MML_SetErrLogNwSrchCfgActiveFlag(VOS_FALSE);
    }

    return;
}


#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadAccBarPlmnSearchNvim
 功能描述  : 读取非HPLMN/RPLMN网络下接入禁止后是否发起plmn搜网的NVIM项
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : s00190137
*****************************************************************************/
VOS_VOID NAS_MMC_ReadAccBarPlmnSearchNvim(VOS_VOID)
{
    VOS_UINT32                                              ulLen;
    NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU               stAccBarPlmnSearchFlg;

    ulLen = 0;

    PS_MEM_SET(&stAccBarPlmnSearchFlg, 0x00, sizeof(NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_ACC_BAR_PLMN_SEARCH_FLG, &ulLen);

    /* 读NV项en_NV_Item_ACC_BAR_PLMN_SEARCH_FLG，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_ACC_BAR_PLMN_SEARCH_FLG,
                         &stAccBarPlmnSearchFlg, ulLen))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadAccBarPlmnSearchNvim():WARNING: read en_NV_Item_ACC_BAR_PLMN_SEARCH_FLG Error");

        return;
    }

    /* 赋值到全局变量 */
    if ( VOS_TRUE == stAccBarPlmnSearchFlg.ucAccBarPlmnSearchFlg)
    {
        NAS_MML_SetSupportAccBarPlmnSearchFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetSupportAccBarPlmnSearchFlg(VOS_FALSE);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUserCfgOPlmnInfoNvim
 功能描述  : 根据NV:en_NV_Item_USER_CFG_OPLMN_LIST初始化stUserCfgPlmnInfo
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : s00190137
  2.日    期    : 2013年11月26日
    作    者    : s00190137
    修改内容    : 将最大支持设置的OPLMN扩展到256个
  3.日    期   : 2015年10月08日
    作    者   : zwx247453
    修改内容   : 清除Coverity告警
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUserCfgOPlmnInfoNvim(VOS_VOID)
{
    VOS_UINT32                                              ulLen;
    VOS_UINT32                                              ulStep;
    VOS_UINT32                                              ulNvOplmnAvail;
    NAS_MML_PLMN_ID_STRU                                    stPlmn;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stSimPlmn;
    NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU                *pstNvimCfgOPlmnInfo = VOS_NULL_PTR;
    NAS_MML_USER_CFG_OPLMN_INFO_STRU                       *pstUserCfgOPlmnInfo = VOS_NULL_PTR;

    ulLen = 0;
    PS_MEM_SET(&stPlmn, 0x00, sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_SET(&stSimPlmn, 0x00, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

    pstNvimCfgOPlmnInfo = (NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU*)PS_MEM_ALLOC(
                                                      WUEPS_PID_MMC,
                                                      sizeof(NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU));
    if (VOS_NULL_PTR == pstNvimCfgOPlmnInfo)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadUserCfgOPlmnInfoNvim():ERROR: Memory Alloc Error");
        return;
    }

    PS_MEM_SET(pstNvimCfgOPlmnInfo, 0x00, sizeof(NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST, &ulLen);

    pstUserCfgOPlmnInfo = NAS_MML_GetUserCfgOPlmnInfo();

    /* 读NV项en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST,
                         pstNvimCfgOPlmnInfo, ulLen))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadUserCfgOPlmnInfoNvim():WARNING: read en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST Error");
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgOPlmnInfo);
        return;
    }

    /* 确保ucActiveFlg值有效，为VOS_TRUE或VOS_FALSE */
    if (VOS_TRUE != pstNvimCfgOPlmnInfo->ucActiveFlg)
    {
         pstNvimCfgOPlmnInfo->ucActiveFlg = VOS_FALSE;
    }

    /* 确保ucImsiCheckFlg值有效，为VOS_TRUE或VOS_FALSE */
    if (VOS_FALSE != pstNvimCfgOPlmnInfo->ucImsiCheckFlg)
    {
         pstNvimCfgOPlmnInfo->ucImsiCheckFlg = VOS_TRUE;
    }

    /* 将NV中的PLMN LIST信息保存到MML的全局变量中去 */
    pstUserCfgOPlmnInfo->ucActiveFlg       = pstNvimCfgOPlmnInfo->ucActiveFlg;
    pstUserCfgOPlmnInfo->ucImsiCheckFlg    = pstNvimCfgOPlmnInfo->ucImsiCheckFlg;
    PS_MEM_CPY(pstUserCfgOPlmnInfo->aucVersion, pstNvimCfgOPlmnInfo->aucVersion, sizeof(pstUserCfgOPlmnInfo->aucVersion));

    /* 将NV中的OPLMN保存到内存中,需要防止数组越界 */
    if ( pstNvimCfgOPlmnInfo->usOplmnListNum > NAS_MML_MAX_USER_CFG_OPLMN_NUM )
    {
        pstNvimCfgOPlmnInfo->usOplmnListNum = NAS_MML_MAX_USER_CFG_OPLMN_NUM;
    }
    pstUserCfgOPlmnInfo->usOplmnListNum = pstNvimCfgOPlmnInfo->usOplmnListNum;

    /* 将NV中保存的IMSI信息转换为内存中的信息,需要防止数组越界 */
    if ( pstNvimCfgOPlmnInfo->ucImsiPlmnListNum > NAS_MML_MAX_USER_OPLMN_IMSI_NUM )
    {
        pstNvimCfgOPlmnInfo->ucImsiPlmnListNum = NAS_MML_MAX_USER_OPLMN_IMSI_NUM;
    }

    pstUserCfgOPlmnInfo->ucImsiPlmnListNum = 0;
    for ( ulStep = 0; ulStep < pstNvimCfgOPlmnInfo->ucImsiPlmnListNum; ulStep++ )
    {
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstNvimCfgOPlmnInfo->astImsiPlmnList[ulStep].aucSimPlmn, NAS_MML_SIM_PLMN_ID_LEN);
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stPlmn))
        {
            pstUserCfgOPlmnInfo->astImsiPlmnList[pstUserCfgOPlmnInfo->ucImsiPlmnListNum] = stPlmn;
            pstUserCfgOPlmnInfo->ucImsiPlmnListNum++;
        }
    }

    /* 如果用户设置的OPLMN有效，需要将NV中的OPLMN列表保存到MML全局变量中 */
    ulNvOplmnAvail = NAS_MML_IsNvimOplmnAvail();

    if (VOS_TRUE == ulNvOplmnAvail)
    {
        /* 使用NV中的OPLMN文件覆盖MML中保存卡文件OPLMN信息的全局变量 */
        NAS_MMC_UpdateOPlmnInfoFromNvim(pstNvimCfgOPlmnInfo->aucOPlmnList, pstNvimCfgOPlmnInfo->usOplmnListNum);
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgOPlmnInfo);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadDplmnNplmnInfoNvim
 功能描述  : 根据NV:en_NV_Item_Cfg_Dplmn_Nplmn初始化DPLMN NPLMN
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月14日
    作    者   : c00188733
    修改内容   : 新生成函数
  2.日    期   : 2014年11月3日
    作    者   : z00161729
    修改内容   : 开机漫游搜网项目修改
  3.日    期   : 2015年10月08日
    作    者   : zwx247453
    修改内容   : 清除Coverity告警

  3.日    期   : 2015年10月21日
    作    者   : l00289540
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 修改
  4.日    期   : 2015年12月12日
    作    者   : s00217060
    修改内容   : DTS2015120901555:读完NV加打印
*****************************************************************************/
 VOS_VOID  NAS_MMC_ReadDplmnNplmnInfoNvim(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU                                    stHplmnId;
    VOS_UINT8                                              *pucImsi              = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;

    /* 取得手机卡中IMSI的信息 */
    pucImsi     = NAS_MML_GetSimImsi();

    /* 从当前的IMSI中取出home plmn */
    stHplmnId  = NAS_MML_GetImsiHomePlmn(pucImsi);

    pstDPlmnNPlmnCfgInfo = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    /* Sim/Usim卡存在时，获取的Imsi才是有效值  */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        return;
    }

    /* 读en_NV_Item_Dplmn_Nplmn_Cfg */
    NAS_MMC_ReadDplmnNplmnCfgNvim(pstDPlmnNPlmnCfgInfo);

    /* 如果当前HPLMN不在NV配置的EHPLMN列表中，可能已经换卡，原来的DPLMN/NPLMN信息无效 */
    if (VOS_FALSE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&stHplmnId,
                                                           pstDPlmnNPlmnCfgInfo->ucEHplmnNum,
                                                           pstDPlmnNPlmnCfgInfo->astEHplmnList))
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "Hplmn Derived From Imsi isn\'t in saved NV Ehplmn list");
        return;
    }

    /* 读en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg */
    NAS_MMC_ReadFirstPresetDplmnNplmnCfgNvim();

    /* 读en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg */
    NAS_MMC_ReadSecondPresetDplmnNplmnCfgNvim();

    /* 读en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg */
    NAS_MMC_ReadSelfLearnDplmnNplmnCfgNvim(pstDPlmnNPlmnCfgInfo);

    NAS_MMC_LogDplmnNplmnList();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_WriteApPresetAndSelfLearnDplmnNplmnToNvim
 功能描述  : 将全局变量中AP预置的以及自学习的DPLMN NPLMN写入到NV中
 输入参数  :VOS_VOID
 输出参数  : 无
 返 回 值  :VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : l00289540
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 修改
*****************************************************************************/
VOS_VOID NAS_MMC_WriteApPresetAndSelfLearnDplmnNplmnToNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
)
{
    /* 更新en_NV_Item_Dplmn_Nplmn_Cfg */
    NAS_MMC_UpdateDplmnNplmnCfgNvim(pstDPlmnNPlmnCfgInfo);

    /* 更新en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg */
    NAS_MMC_UpdateApPresetDplmnToFirstPresetDplmnNplmnCfgNvim(pstDPlmnNPlmnCfgInfo);

    /* 更新en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg */
    NAS_MMC_UpdateApPresetDplmnToSecondPresetDplmnNplmnCfgNvim(pstDPlmnNPlmnCfgInfo);

    /* 更新en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg */
    NAS_MMC_UpdateSelfLearnDplmnNplmnToSelfLearnDplmnNplmnCfgNvim(pstDPlmnNPlmnCfgInfo);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateDplmnNplmnCfgNvim
 功能描述  : 更新DPLMN/NPLMN Cfg 到对应的NVIM
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : l00289540
    修改内容   : 新生成函数
  2.日    期   : 2015年12月2日
    作    者   : s00217060
    修改内容   : DTS2015070103821:coverity

*****************************************************************************/
VOS_VOID NAS_MMC_ReadDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
)
{
    NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU                       stNvimDPlmnNPlmnCfg;
    VOS_UINT32                                              ulLen;

    /* 读en_NV_Item_Dplmn_Nplmn_Cfg */
    PS_MEM_SET(&stNvimDPlmnNPlmnCfg, 0x00, sizeof(NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU));
    ulLen       = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_Dplmn_Nplmn_Cfg, &ulLen);

    if (ulLen > sizeof(NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:NAS_MMC_ReadDplmnNplmnInfoNvim : wrong len of en_NV_Item_Dplmn_Nplmn_Cfg");
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_Dplmn_Nplmn_Cfg, &stNvimDPlmnNPlmnCfg, ulLen))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:NAS_MMC_ReadDplmnNplmnInfoNvim : read en_NV_Item_Dplmn_Nplmn_Cfg Failed");
        return;
    }

    NAS_MMC_UpdateDPlmnNPlmnCfgInfo(&stNvimDPlmnNPlmnCfg, pstDPlmnNPlmnCfgInfo);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateDplmnNplmnCfgNvim
 功能描述  : 更新DPLMN/NPLMN Cfg 到对应的NVIM
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
)
{
    NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU                       stNvimDplmnNplmnCfg;
    NAS_MML_PLMN_ID_STRU                                    stUserPlmn;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stNvimPlmn;
    VOS_UINT32                                              ulLen;
    VOS_UINT32                                              i;
    VOS_UINT8                                               ucMaxEhplmnNum;

    ulLen                    = 0;
    ucMaxEhplmnNum           = NAS_MML_MIN(pstDPlmnNPlmnCfgInfo->ucEHplmnNum, NAS_MMC_MAX_CFG_HPLMN_NUM);

    /* 初始化 */
    PS_MEM_SET(&stNvimDplmnNplmnCfg, 0x00, sizeof(NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU));

    /* 更新版本信息 */
    PS_MEM_CPY(stNvimDplmnNplmnCfg.aucVersionId,
               pstDPlmnNPlmnCfgInfo->aucVersionId,
               NAS_MCC_INFO_VERSION_LEN * sizeof(VOS_UINT8));

    /* 更新EHPLMN */
    stNvimDplmnNplmnCfg.ucEHplmnNum     = ucMaxEhplmnNum;

    for (i = 0; i < ucMaxEhplmnNum; i++)
    {
       PS_MEM_SET(&stNvimPlmn, 0x00, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

       stUserPlmn.ulMcc = pstDPlmnNPlmnCfgInfo->astEHplmnList[i].ulMcc;
       stUserPlmn.ulMnc = pstDPlmnNPlmnCfgInfo->astEHplmnList[i].ulMnc;

       NAS_MMC_ConvertNasPlmnToSimFormat(&stUserPlmn, &stNvimPlmn);

       stNvimDplmnNplmnCfg.aucEHplmnList[(i * NAS_MML_SIM_FORMAT_PLMN_LEN)]     = stNvimPlmn.aucSimPlmn[0];
       stNvimDplmnNplmnCfg.aucEHplmnList[(i * NAS_MML_SIM_FORMAT_PLMN_LEN) + 1] = stNvimPlmn.aucSimPlmn[1];
       stNvimDplmnNplmnCfg.aucEHplmnList[(i * NAS_MML_SIM_FORMAT_PLMN_LEN) + 2] = stNvimPlmn.aucSimPlmn[2];
    }

    (VOS_VOID)NV_GetLength(en_NV_Item_Dplmn_Nplmn_Cfg, &ulLen);

    (VOS_VOID)NV_Write(en_NV_Item_Dplmn_Nplmn_Cfg, &stNvimDplmnNplmnCfg, ulLen);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadFirstPresetDplmnNplmnCfgNvim
 功能描述  : 读取NV en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg，并更新到全局变量中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : l00289540
    修改内容   : 新生成函数
  2.日    期   : 2015年12月2日
    作    者   : s00217060
    修改内容   : DTS2015070103821修改:coverity

*****************************************************************************/
VOS_VOID NAS_MMC_ReadFirstPresetDplmnNplmnCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 *pstNvimCfgDPlmnNPlmnInfo = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;

    pstNvimCfgDPlmnNPlmnInfo = (NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU*)PS_MEM_ALLOC(
                                                      WUEPS_PID_MMC,
                                                      sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));
    if (VOS_NULL_PTR == pstNvimCfgDPlmnNPlmnInfo)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:NAS_MMC_ReadDplmnNplmnInfoNvim Mem Alloc Failed");

        return;
    }

    /* 读en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg */
    PS_MEM_SET(pstNvimCfgDPlmnNPlmnInfo, 0x00, sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));
    ulLen       = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg, &ulLen);

    if (ulLen > sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
        return;
    }

    /* 读NV项en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg,
                         pstNvimCfgDPlmnNPlmnInfo, ulLen))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
        return;
    }

    pstDPlmnNPlmnCfgInfo = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    /* 将读取的DPLMN & NPLMN 更新到到全局变量中 */
    NAS_MMC_UpdateDplmnNplmnInfo(pstNvimCfgDPlmnNPlmnInfo, pstDPlmnNPlmnCfgInfo);

    /* 更新全局变量中记录的AP预置的DPLMN个数 */
    pstDPlmnNPlmnCfgInfo->usPresetDplmnNum = pstDPlmnNPlmnCfgInfo->usDplmnListNum;

    PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateApPresetDplmnToFirstPresetDplmnNplmnCfgNvim
 功能描述  : 更新 DPLMN List 到对应的NV en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateApPresetDplmnToFirstPresetDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
)
{
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 *pstNvimCfgDPlmnNPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stNvimPlmn;
    NAS_MML_PLMN_ID_STRU                                    stUserPlmn;
    VOS_UINT32                                              ulLen;
    VOS_UINT32                                              i;

    PS_MEM_SET(&stNvimPlmn, 0, sizeof(stNvimPlmn));
    PS_MEM_SET(&stUserPlmn, 0, sizeof(stUserPlmn));
    ulLen       = 0;

    if (0 == pstDPlmnNPlmnCfgInfo->usPresetDplmnNum)
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "ERROR:NAS_MMC_UpdateApPresetDplmnToFirstPresetDplmnNplmnCfgNvim usPresetDplmnNum = 0");

        return;
    }

    pstNvimCfgDPlmnNPlmnInfo = (NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU*)PS_MEM_ALLOC(
                                   WUEPS_PID_MMC,
                                   sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));

    if (VOS_NULL_PTR == pstNvimCfgDPlmnNPlmnInfo)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:NAS_MMC_UpdateApPresetDplmnToFirstPresetDplmnNplmnCfgNvim Mem Alloc Failed");

        return;
    }

    PS_MEM_SET( pstNvimCfgDPlmnNPlmnInfo, 0x00, sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));

    /* 构造NV DPLMN List */
    pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum = NAS_MML_MIN(pstDPlmnNPlmnCfgInfo->usPresetDplmnNum, NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM);

    for (i = 0; i < pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum; i++)
    {
        PS_MEM_SET(&stNvimPlmn, 0x00, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

        stUserPlmn.ulMcc = pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMcc;
        stUserPlmn.ulMnc = pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMnc;

        NAS_MMC_ConvertNasPlmnToSimFormat(&stUserPlmn, &stNvimPlmn);

        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN)]     = stNvimPlmn.aucSimPlmn[0];
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 1] = stNvimPlmn.aucSimPlmn[1];
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 2] = stNvimPlmn.aucSimPlmn[2];
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 3] = (VOS_UINT8)((pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.usSimRat) >> NAS_MML_OCTET_MOVE_EIGHT_BITS);
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 4] = (VOS_UINT8)((pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.usSimRat) & (0x00FF));

        /* 更新注册域信息 */
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 5] = pstDPlmnNPlmnCfgInfo->astDPlmnList[i].enRegDomain;

        /* 更新类型信息 */
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 6] = pstDPlmnNPlmnCfgInfo->astDPlmnList[i].enType;
    }

    /* 写NV项en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg */
    (VOS_VOID)NV_GetLength(en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg, &ulLen);
    (VOS_VOID)NV_Write(en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg, pstNvimCfgDPlmnNPlmnInfo, ulLen);

    PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadSecondPresetDplmnNplmnCfgNvim
 功能描述  : 读取NV en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg，并更新到全局变量中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : l00289540
    修改内容   : 新生成函数
  2.日    期   : 2015年12月2日
    作    者   : s00217060
    修改内容   : DTS2015070103821:coverity

*****************************************************************************/
VOS_VOID NAS_MMC_ReadSecondPresetDplmnNplmnCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 *pstNvimCfgDPlmnNPlmnInfo = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo     = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;

    pstDPlmnNPlmnCfgInfo = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    /* Ap预置的DPLMN个数小于NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM，全部存储在 NV en_NV_Item_First_Preset_Dplmn_Nplmn_Cfg */
    if (pstDPlmnNPlmnCfgInfo->usPresetDplmnNum < NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM)
    {
        return;
    }

    pstNvimCfgDPlmnNPlmnInfo = (NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU*)PS_MEM_ALLOC(
                                                      WUEPS_PID_MMC,
                                                      sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));

    if (VOS_NULL_PTR == pstNvimCfgDPlmnNPlmnInfo)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:NAS_MMC_ReadDplmnNplmnInfoNvim Mem Alloc Failed");

        return;
    }

    /* 读en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg */
    PS_MEM_SET(pstNvimCfgDPlmnNPlmnInfo, 0x00, sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));
    ulLen       = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg, &ulLen);

    if (ulLen > sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
        return;
    }

    /* 读NV项en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg,
                         pstNvimCfgDPlmnNPlmnInfo, ulLen))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
        return;
    }

    /* 将读取的DPLMN & NPLMN 更新到到全局变量中 */
    NAS_MMC_UpdateDplmnNplmnInfo(pstNvimCfgDPlmnNPlmnInfo, pstDPlmnNPlmnCfgInfo);

    /* 更新全局变量中记录的AP预置的DPLMN个数 */
    pstDPlmnNPlmnCfgInfo->usPresetDplmnNum = pstDPlmnNPlmnCfgInfo->usDplmnListNum;

    PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateApPresetDplmnToSecondPresetDplmnNplmnCfgNvim
 功能描述  : 更新DPLMN List 到对应的NV en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg
             全局变量NAS_MMC_GetDPlmnNPlmnCfgInfo()的第256 至 512 个DPLMN更新到此NV中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : l00289540
    修改内容   : 新生成函数
  2.日    期   : 2015年12月12日
    作    者   : s00217060
    修改内容   : DTS2015120901555修改：NAS_MML_MIN参数不能用表达式

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateApPresetDplmnToSecondPresetDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
)
{
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 *pstNvimCfgDPlmnNPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stNvimPlmn;
    NAS_MML_PLMN_ID_STRU                                    stUserPlmn;
    VOS_UINT16                                              usLeftDPlmnNum;
    VOS_UINT32                                              ulLen;
    VOS_UINT32                                              i;

    PS_MEM_SET(&stNvimPlmn, 0, sizeof(stNvimPlmn));
    PS_MEM_SET(&stUserPlmn, 0, sizeof(stUserPlmn));
    ulLen       = 0;

    pstNvimCfgDPlmnNPlmnInfo = (NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU*)PS_MEM_ALLOC(
                                   WUEPS_PID_MMC,
                                   sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));

    if (VOS_NULL_PTR == pstNvimCfgDPlmnNPlmnInfo)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:NAS_MMC_UpdateApPresetDplmnToSecondPresetDplmnNplmnCfgNvim Mem Alloc Failed");

        return;
    }

    PS_MEM_SET( pstNvimCfgDPlmnNPlmnInfo, 0x00, sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));

    /* 全局变量 pstDPlmnNPlmnCfgInfo 中AP预置的第256至512的DPLMN才需要更新到此NV中 */
    if (pstDPlmnNPlmnCfgInfo->usPresetDplmnNum <= NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM)
    {
        /* 为了防止原来的NV项中有值，把原来的NV项清0 */
        (VOS_VOID)NV_GetLength(en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg, &ulLen);
        (VOS_VOID)NV_Write(en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg, pstNvimCfgDPlmnNPlmnInfo, ulLen);

        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
        return;
    }


    /* 构造NV DPLMN List */
    usLeftDPlmnNum  = pstDPlmnNPlmnCfgInfo->usPresetDplmnNum - NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM;
    pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum = NAS_MML_MIN(usLeftDPlmnNum, NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM);

    for (i = 0; i < pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum; i++)
    {
        PS_MEM_SET(&stNvimPlmn, 0x00, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

        stUserPlmn.ulMcc = pstDPlmnNPlmnCfgInfo->astDPlmnList[i+NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM].stSimPlmnWithRat.stPlmnId.ulMcc;
        stUserPlmn.ulMnc = pstDPlmnNPlmnCfgInfo->astDPlmnList[i+NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM].stSimPlmnWithRat.stPlmnId.ulMnc;

        NAS_MMC_ConvertNasPlmnToSimFormat(&stUserPlmn, &stNvimPlmn);

        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN)]     = stNvimPlmn.aucSimPlmn[0];
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 1] = stNvimPlmn.aucSimPlmn[1];
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 2] = stNvimPlmn.aucSimPlmn[2];
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 3] = (VOS_UINT8)((pstDPlmnNPlmnCfgInfo->astDPlmnList[i+NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM].stSimPlmnWithRat.usSimRat) >> NAS_MML_OCTET_MOVE_EIGHT_BITS);
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 4] = (VOS_UINT8)((pstDPlmnNPlmnCfgInfo->astDPlmnList[i+NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM].stSimPlmnWithRat.usSimRat) & (0x00FF));

        /* 更新注册域信息 */
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 5] = pstDPlmnNPlmnCfgInfo->astDPlmnList[i+NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM].enRegDomain;

        /* 更新类型信息 */
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 6] = pstDPlmnNPlmnCfgInfo->astDPlmnList[i+NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM].enType;
    }

    /* 写NV项en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg */
    (VOS_VOID)NV_GetLength(en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg, &ulLen);
    (VOS_VOID)NV_Write(en_NV_Item_Second_Preset_Dplmn_Nplmn_Cfg, pstNvimCfgDPlmnNPlmnInfo, ulLen);

    PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadSelfLearnDplmnNplmnCfgNvim
 功能描述  : NV en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg中保存的是UE自学习得到的DPLMN，
             读取此NV并保存到相应的全局变量中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : l00289540
    修改内容   : 新生成函数
  2.日    期   : 2015年12月2日
    作    者   : s00217060
    修改内容   : DTS2015070103821:coverity

*****************************************************************************/
VOS_VOID NAS_MMC_ReadSelfLearnDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                     *pstDPlmnNPlmnCfgInfo
)
{
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 *pstNvimCfgDPlmnNPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;

    pstNvimCfgDPlmnNPlmnInfo = (NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU*)PS_MEM_ALLOC(
                                                      WUEPS_PID_MMC,
                                                      sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));

    if (VOS_NULL_PTR == pstNvimCfgDPlmnNPlmnInfo)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:NAS_MMC_ReadDplmnNplmnInfoNvim Mem Alloc Failed");

        return;
    }

    /* 读en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg */
    PS_MEM_SET(pstNvimCfgDPlmnNPlmnInfo, 0x00, sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));
    ulLen       = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg, &ulLen);

    if (ulLen > sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
        return;
    }

    /* 读NV项en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg,
                         pstNvimCfgDPlmnNPlmnInfo, ulLen))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
        return;
    }

    /* 更新到全局变量中 */
    NAS_MMC_UpdateDplmnNplmnInfo(pstNvimCfgDPlmnNPlmnInfo, pstDPlmnNPlmnCfgInfo);

    PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateSelfLearnDplmnNplmnToSelfLearnDplmnNplmnCfgNvim
 功能描述  : 更新电信 CT DPLMN/NPLMN Cfg 到对应的NV en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg
             全局变量NAS_MMC_GetDPlmnNPlmnCfgInfo()的AP预置DPLMN之后的自学习类型的DPLMN更新到此NV中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : l00289540
    修改内容   : 新生成函数
  2.日    期   : 2015年12月12日
    作    者   : s00217060
    修改内容   : DTS2015120901555修改：NAS_MML_MIN参数不能用表达式

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateSelfLearnDplmnNplmnToSelfLearnDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
)
{
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 *pstNvimCfgDPlmnNPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stNvimPlmn;
    NAS_MML_PLMN_ID_STRU                                    stUserPlmn;
    VOS_UINT16                                              usDplmnListNum;
    VOS_UINT16                                              usPresetDplmnNum;
    VOS_UINT16                                              usSelfLearnDplmnNum;
    VOS_UINT32                                              ulLen;
    VOS_UINT32                                              i;


    usDplmnListNum           = pstDPlmnNPlmnCfgInfo->usDplmnListNum;
    usPresetDplmnNum         = pstDPlmnNPlmnCfgInfo->usPresetDplmnNum;
    ulLen                    = 0;

    PS_MEM_SET(&stNvimPlmn, 0x00, sizeof(stNvimPlmn));
    PS_MEM_SET(&stUserPlmn, 0x00, sizeof(stUserPlmn));

    /* 全局变量 pstDPlmnNPlmnCfgInfo 中AP预置的第usPresetDplmnNum至usDplmnListNum的DPLMN才需要更新到此NV中 */
    pstNvimCfgDPlmnNPlmnInfo = (NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU*)PS_MEM_ALLOC(
                                   WUEPS_PID_MMC,
                                   sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));

    if (VOS_NULL_PTR == pstNvimCfgDPlmnNPlmnInfo)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:NAS_MMC_UpdateApPresetDplmnToSecondPresetDplmnNplmnCfgNvim Mem Alloc Failed");

        return;
    }

    PS_MEM_SET(pstNvimCfgDPlmnNPlmnInfo, 0x00, sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));
    usSelfLearnDplmnNum = usDplmnListNum - usPresetDplmnNum;

    pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum = NAS_MML_MIN(usSelfLearnDplmnNum, NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM);

    /* 保存自学习的 DPLMN */
    for (i = 0; i < pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum; i++)
    {
        PS_MEM_SET(&stNvimPlmn, 0x00, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

        stUserPlmn.ulMcc = pstDPlmnNPlmnCfgInfo->astDPlmnList[i+usPresetDplmnNum].stSimPlmnWithRat.stPlmnId.ulMcc;
        stUserPlmn.ulMnc = pstDPlmnNPlmnCfgInfo->astDPlmnList[i+usPresetDplmnNum].stSimPlmnWithRat.stPlmnId.ulMnc;

        NAS_MMC_ConvertNasPlmnToSimFormat(&stUserPlmn, &stNvimPlmn);

        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN)]     = stNvimPlmn.aucSimPlmn[0];
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 1] = stNvimPlmn.aucSimPlmn[1];
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 2] = stNvimPlmn.aucSimPlmn[2];
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 3] =
              (VOS_UINT8)((pstDPlmnNPlmnCfgInfo->astDPlmnList[i+usPresetDplmnNum].stSimPlmnWithRat.usSimRat) >> NAS_MML_OCTET_MOVE_EIGHT_BITS);

        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 4] =
              (VOS_UINT8)((pstDPlmnNPlmnCfgInfo->astDPlmnList[i+usPresetDplmnNum].stSimPlmnWithRat.usSimRat) & (0x00FF));

        /* 更新注册域信息 */
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 5] = pstDPlmnNPlmnCfgInfo->astDPlmnList[i+usPresetDplmnNum].enRegDomain;

        /* 更新类型信息 */
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 6] = pstDPlmnNPlmnCfgInfo->astDPlmnList[i+usPresetDplmnNum].enType;
    }

    /* 保存自学习的 NPLMN */
    pstNvimCfgDPlmnNPlmnInfo->usNplmnListNum = pstDPlmnNPlmnCfgInfo->usNplmnListNum;

    for (i = 0; i < pstDPlmnNPlmnCfgInfo->usNplmnListNum; i++)
    {
        PS_MEM_SET(&stNvimPlmn, 0x00, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

        stUserPlmn.ulMcc = pstDPlmnNPlmnCfgInfo->astNPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMcc;
        stUserPlmn.ulMnc = pstDPlmnNPlmnCfgInfo->astNPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMnc;

        NAS_MMC_ConvertNasPlmnToSimFormat(&stUserPlmn, &stNvimPlmn);

        pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN)]     = stNvimPlmn.aucSimPlmn[0];
        pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 1] = stNvimPlmn.aucSimPlmn[1];
        pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 2] = stNvimPlmn.aucSimPlmn[2];
        pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 3] =
              (VOS_UINT8)((pstDPlmnNPlmnCfgInfo->astNPlmnList[i].stSimPlmnWithRat.usSimRat) >> NAS_MML_OCTET_MOVE_EIGHT_BITS);

        pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 4] =
              (VOS_UINT8)((pstDPlmnNPlmnCfgInfo->astNPlmnList[i].stSimPlmnWithRat.usSimRat) & (0x00FF));

        /* 更新注册域信息 */
        pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 5] = pstDPlmnNPlmnCfgInfo->astNPlmnList[i].enRegDomain;

        /* 更新类型信息 */
        pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(i * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 6] = pstDPlmnNPlmnCfgInfo->astNPlmnList[i].enType;
    }

    /* 写NV项en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg */
    (VOS_VOID)NV_GetLength(en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg, &ulLen);
    (VOS_VOID)NV_Write(en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg, pstNvimCfgDPlmnNPlmnInfo, ulLen);

    PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_WriteSelfLearnDplmnNplmnToNvim
 功能描述  : 将全局变量中的DPLMN NPLMN写入到NV中
 输入参数  :VOS_VOID
 输出参数  : 无
 返 回 值  :VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月14日
   作    者   : c00188733
   修改内容   : 新生成函数
 2.日    期   : 2014年11月3日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改
 3.日    期   : 2015年10月21日
   作    者   : l00289540
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 修改
*****************************************************************************/
VOS_VOID NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
)
{
    /* 更新en_NV_Item_Dplmn_Nplmn_Cfg */
    NAS_MMC_UpdateDplmnNplmnCfgNvim(pstDPlmnNPlmnCfgInfo);

    /* 更新en_NV_Item_Self_Learn_Dplmn_Nplmn_Cfg */
    NAS_MMC_UpdateSelfLearnDplmnNplmnToSelfLearnDplmnNplmnCfgNvim(pstDPlmnNPlmnCfgInfo);

    return;
}

/* NAS_MMC_JudegeHplmnType 删除 */

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadModemRfShareCfgNvim
 功能描述  : 根据NV:NV_MODEM_RF_SHARE_EX_CFG初始化是否支持DSDS
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2015年9月9日
    作    者   : lwx277467
    修改内容   : DTS2015072005238
*****************************************************************************/
VOS_VOID NAS_MMC_ReadModemRfShareCfgNvim(VOS_VOID)
{
    NV_MODEM_RF_SHARE_CFG_EX_STRU          stNvimRfShareCfgExInfo;
    VOS_UINT32                             ProfileId;

    PS_MEM_SET(&stNvimRfShareCfgExInfo, 0x00, sizeof(NV_MODEM_RF_SHARE_CFG_EX_STRU));

    /* 读NV项en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_MODEM_RF_SHARE_EX_CFG,
                         &stNvimRfShareCfgExInfo, sizeof(NV_MODEM_RF_SHARE_CFG_EX_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadModemRfShareCfgNvim():WARNING: read en_NV_MODEM_RF_SHARE_EX_CFG Error");

        return;
    }

    ProfileId = stNvimRfShareCfgExInfo.ulProfileTypeId;
    if(ProfileId > 7)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadModemRfShareCfgNvim():WARNING: get ProfileId Error");
        return;
    }

    if ( (VOS_TRUE  != stNvimRfShareCfgExInfo.astNvModemRfShareCfg[ProfileId].usSupportFlag)
      && (VOS_FALSE != stNvimRfShareCfgExInfo.astNvModemRfShareCfg[ProfileId].usSupportFlag) )
    {
        /* NV内容异常保护 */
        stNvimRfShareCfgExInfo.astNvModemRfShareCfg[ProfileId].usSupportFlag = VOS_FALSE;
    }

    NAS_MML_SetDsdsRfShareFlg(stNvimRfShareCfgExInfo.astNvModemRfShareCfg[ProfileId].usSupportFlag);

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadDsdsEndSessionDelayNvim
 功能描述  : 读取NV:en_NV_Item_DSDS_END_SESSION_DELAY并设置延迟时间
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月17日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadDsdsEndSessionDelayNvim(VOS_VOID)
{
    NAS_MMC_NVIM_DSDS_END_SESSION_DELAY_STRU                stNvimDsdsEndSessionDelay;
    NAS_MML_DSDS_END_SESSION_DELAY_STRU                     stDsdsEndSesssionDelay;

    PS_MEM_SET(&stNvimDsdsEndSessionDelay, 0x00, sizeof(NAS_MMC_NVIM_DSDS_END_SESSION_DELAY_STRU));
    PS_MEM_SET(&stDsdsEndSesssionDelay, 0x00, sizeof(NAS_MML_DSDS_END_SESSION_DELAY_STRU));

    /* 读NV项en_NV_Item_DSDS_END_SESSION_DELAY，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_DSDS_END_SESSION_DELAY,
                         &stNvimDsdsEndSessionDelay, sizeof(NAS_MMC_NVIM_DSDS_END_SESSION_DELAY_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
            "NAS_MMC_ReadDsdsEndSessionDelayNvim():WARNING: read en_NV_Item_DSDS_END_SESSION_DELAY Error");

        return;
    }

    if (stNvimDsdsEndSessionDelay.ulCsRegEndSessionDelayTime > NAS_MML_CS_REG_END_SESSION_MAX_DELAY_TIME)
    {
        stDsdsEndSesssionDelay.ulCsRegEndSessionDelayTime = NAS_MML_CS_REG_END_SESSION_MAX_DELAY_TIME;
    }
    else
    {
        stDsdsEndSesssionDelay.ulCsRegEndSessionDelayTime = stNvimDsdsEndSessionDelay.ulCsRegEndSessionDelayTime;
    }

    if (stNvimDsdsEndSessionDelay.ulPsRegEndSessionDelayTime > NAS_MML_PS_REG_END_SESSION_MAX_DELAY_TIME)
    {
        stDsdsEndSesssionDelay.ulPsRegEndSessionDelayTime = NAS_MML_PS_REG_END_SESSION_MAX_DELAY_TIME;
    }
    else
    {
        stDsdsEndSesssionDelay.ulPsRegEndSessionDelayTime = stNvimDsdsEndSessionDelay.ulPsRegEndSessionDelayTime;
    }

    NAS_MML_SetDsdsEndSessionDelay(&stDsdsEndSesssionDelay);

    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUmtsCodecTypeNvim
 功能描述  : 读取NV:en_NV_Item_UMTS_CODEC_TYPE
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月8日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MMC_ReadUmtsCodecTypeNvim(VOS_VOID)
{
    MN_CALL_UMTS_CODEC_TYPE_STRU        stNvimCodecType;
    NAS_MML_CALL_UMTS_CODEC_TYPE_STRU   stCodecType;

    PS_MEM_SET(&stNvimCodecType, 0x00, sizeof(stNvimCodecType));
    PS_MEM_SET(&stCodecType, 0x00, sizeof(stCodecType));

    if ( NV_OK != NV_Read(en_NV_Item_UMTS_CODEC_TYPE,
                          &stNvimCodecType,
                          sizeof(stNvimCodecType)))
    {
        return;
    }

    stCodecType.ucCnt = stNvimCodecType.ucCnt;
    PS_MEM_CPY(stCodecType.aucUmtsCodec, stNvimCodecType.aucUmtsCodec, sizeof(stCodecType.aucUmtsCodec));

    NAS_MML_CALL_SetCallUmtsCodecType(&stCodecType);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadItemMdeCodecNvim
 功能描述  : 读取NV:en_NV_Item_UMTS_CODEC_TYPE
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月8日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MMC_ReadMedCodecTypeNvim(VOS_VOID)
{
    MN_CALL_NIMV_ITEM_CODEC_TYPE_STRU   stNvimCodecType;
    NAS_MML_CALL_GSM_CODEC_TYPE_STRU    stCodecType;

    PS_MEM_SET(&stNvimCodecType, 0x00, sizeof(stNvimCodecType));
    PS_MEM_SET(&stCodecType, 0x00, sizeof(stCodecType));

    if ( NV_OK != NV_Read(en_NV_Item_MED_CODEC_TYPE,
                          &stNvimCodecType,
                          sizeof(stNvimCodecType)))
    {
        return;
    }

    stCodecType.ucCodecTypeNum = stNvimCodecType.ucCodecTypeNum;
    PS_MEM_CPY(stCodecType.aucCodecType, stNvimCodecType.aucCodecType, sizeof(stNvimCodecType.aucCodecType));

    NAS_MML_CALL_SetCallGsmCodecType(&stCodecType);
}

/* Added by f00261443 for VoLTE_PhaseIII项目, 2013-12-24, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadImsVoiceMMEnableNvim
 功能描述  : 读取Ims Voice 移动性管理相关NV 写入MML中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月25日
    作    者   : f00261443
*****************************************************************************/
VOS_VOID NAS_MMC_ReadImsVoiceMMEnableNvim(VOS_VOID)
{
    NAS_MMC_IMS_VOICE_MOBILE_MANAGEMENT stImsVoiceMM;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_IMS_VOICE_MOBILE_MANAGEMENT, &ulLength);
    if (ulLength > sizeof(stImsVoiceMM))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadImsVoiceMMEnableNvim():WARNING: NvGetLength too long");
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_IMS_VOICE_MOBILE_MANAGEMENT,
                         &stImsVoiceMM, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadImsVoiceMMEnableNvim():WARNING: read en_NV_Item_IMS_VOICE_MOBILE_MANAGEMENT Error");
        return;
    }

    if (VOS_TRUE  == stImsVoiceMM.ucImsVoiceInterSysLauEnable)
    {
        NAS_MML_SetImsVoiceInterSysLauEnableFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetImsVoiceInterSysLauEnableFlg(VOS_FALSE);
    }

    if (VOS_TRUE  == stImsVoiceMM.ucImsVoiceMMEnable)
    {
        NAS_MML_SetImsVoiceMMEnableFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetImsVoiceMMEnableFlg(VOS_FALSE);
    }

    return;
}
/* Added by f00261443 for VoLTE_PhaseIII项目, 2013-12-24, End */

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadLcCtrlParaNvim
 功能描述  : 读取LC特性配置nv
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
VOS_VOID NAS_MMC_ReadLcCtrlParaNvim(VOS_VOID)
{
    TAF_NV_LC_CTRL_PARA_STRU            stLcCtrlPara;

    PS_MEM_SET(&stLcCtrlPara, 0, sizeof(stLcCtrlPara));

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_LC_Ctrl_PARA,
                         &stLcCtrlPara,
                         sizeof(stLcCtrlPara)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLcCtrlParaNvim(): en_NV_Item_LC_Ctrl_PARA error");
        return;
    }

    if (VOS_TRUE == stLcCtrlPara.ucLCEnableFlg)
    {
        NAS_MML_SetLcEnableFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetLcEnableFlg(VOS_FALSE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadIgnoreAuthRejFlgNvim
 功能描述  : 读取是否移除鉴权拒绝的NVIM项
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年02月18日
    作    者   : l00215384
	修改内容    : 新增
  2.日    期   : 2015年10月08日
    作    者   : zwx247453
    修改内容   : 清除Coverity告警
*****************************************************************************/
VOS_VOID NAS_MMC_ReadIgnoreAuthRejFlgNvim(VOS_VOID)
{
    VOS_UINT32                                              ulLen;
    NAS_MMC_NVIM_IGNORE_AUTH_REJ_CFG_STRU                   stIgnoreAuthRejInfo;

    ulLen = 0;
    PS_MEM_SET(&stIgnoreAuthRejInfo, 0x00, sizeof(NAS_MMC_NVIM_IGNORE_AUTH_REJ_CFG_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_Ignore_Auth_Rej_CFG, &ulLen);

    stIgnoreAuthRejInfo.ucIgnoreAuthRejFlg = VOS_FALSE;
    stIgnoreAuthRejInfo.ucMaxAuthRejNo = 0;
    /* 读NV项en_NV_Item_Remove_Auth_Rej_CFG，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_Ignore_Auth_Rej_CFG,
                         &stIgnoreAuthRejInfo, ulLen))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadIgnoreAuthRejFlgNvim():WARNING: read en_NV_Item_Remove_Auth_Rej_CFG Error");

        return;
    }

    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        NAS_MML_SetIgnoreAuthRejFlg(VOS_FALSE);
        return;
    }

    /* 赋值到全局变量 */
    if ( VOS_TRUE == stIgnoreAuthRejInfo.ucIgnoreAuthRejFlg)
    {
        NAS_MML_SetIgnoreAuthRejFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetIgnoreAuthRejFlg(VOS_FALSE);
    }

    NAS_MML_SetMaxAuthRejNo((stIgnoreAuthRejInfo.ucMaxAuthRejNo));

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadHighPrioRatHplmnTimerCfgNvim
 功能描述  : 从NVIM中获取的High Prio Rat Hplmn Timer定时器的时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年10月25日
    作    者   : b00269685
    修改内容   : 增加TD下定时器次数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadHighPrioRatHplmnTimerCfgNvim( VOS_VOID  )
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU       *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;
    NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU   stHighRatHplmnTimerCfg;

    PS_MEM_SET(&stHighRatHplmnTimerCfg, 0x00, sizeof(stHighRatHplmnTimerCfg));

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();

    if (NV_OK != NV_Read (en_NV_Item_HIGH_PRIO_RAT_HPLMN_TIMER_CFG, &stHighRatHplmnTimerCfg, sizeof(stHighRatHplmnTimerCfg)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadHighPrioRatHplmnTimerCfgNvim:Read NV Failed");
        return;
    }

    pstHighRatHplmnTimerCfg->ucActiveFLg = VOS_FALSE;

    if (VOS_TRUE == stHighRatHplmnTimerCfg.ucActiveFLg)
    {
        pstHighRatHplmnTimerCfg->ucActiveFLg                = VOS_TRUE;
        pstHighRatHplmnTimerCfg->ucTdThreshold              = stHighRatHplmnTimerCfg.ucTdThreshold;
        pstHighRatHplmnTimerCfg->ulFirstSearchTimeLen       = stHighRatHplmnTimerCfg.ulFirstSearchTimeLen;
        pstHighRatHplmnTimerCfg->ulNonFirstSearchTimeLen    = stHighRatHplmnTimerCfg.ulNonFirstSearchTimeLen;
        pstHighRatHplmnTimerCfg->ulFirstSearchTimeCount     = stHighRatHplmnTimerCfg.ulFirstSearchTimeCount;
        pstHighRatHplmnTimerCfg->ulRetrySearchTimeLen       = stHighRatHplmnTimerCfg.ulRetrySearchTimeLen;
    }

    return;
}

#if  (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUltraFlashCsfbSupportFlgNvim
 功能描述  : 读取是否支持ultra flash csfb的NVIM项
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年05月30日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUltraFlashCsfbSupportFlgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_ULTRA_FLASH_CSFB_SUPPORT_FLG_STRU          stUltraFlashCsfbSupport;

    PS_MEM_SET(&stUltraFlashCsfbSupport, 0x00, sizeof(NAS_MMC_NVIM_ULTRA_FLASH_CSFB_SUPPORT_FLG_STRU));

    /* 读NV项en_NV_Item_Ultra_Flash_Csfb_Support_Flg，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_Ultra_Flash_Csfb_Support_Flg,
                         &stUltraFlashCsfbSupport,
                         sizeof(NAS_MMC_NVIM_ULTRA_FLASH_CSFB_SUPPORT_FLG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadIgnoreAuthRejFlgNvim():WARNING: read en_NV_Item_Remove_Auth_Rej_CFG Error");

        return;
    }

    /* 赋值到全局变量 */
    if ( VOS_TRUE == stUltraFlashCsfbSupport.ucUltraFlashCsfbSupportFLg)
    {
        NAS_MML_SetUltraFlashCsfbSupportFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetUltraFlashCsfbSupportFlg(VOS_FALSE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadSrvccSupportFlgNvim
 功能描述  : 读取是否支持ultra flash csfb的NVIM项
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年05月30日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2014年10月8日
    作    者   : b00269685
    修改内容   : 增加是否支持srvcc标志
*****************************************************************************/
VOS_VOID NAS_MMC_ReadSrvccSupportFlgNvim(VOS_VOID)
{
    IMS_NV_IMS_CAP_STRU                 stImsCap;
    VOS_UINT8                           ucSrvccFlg;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;

    pstMsCapability = NAS_MML_GetMsCapability();

    PS_MEM_SET(&stImsCap, 0x00, sizeof(IMS_NV_IMS_CAP_STRU));

    /* 读NV项EN_NV_ID_IMS_CAPABILITY，失败，直接返回 */
    if (NV_OK != NV_Read(EN_NV_ID_IMS_CAPABILITY,
                         &stImsCap,
                         sizeof(IMS_NV_IMS_CAP_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSrvccSupportFlgNvim():WARNING: read EN_NV_ID_IMS_CAPABILITY Error");

        return;
    }

    /* active/hold/alerting/pre alterting任一个状态支持SRVCC，就给网络报支持SRVCC */
    ucSrvccFlg  = (stImsCap.ucSrvccOnImsSupportFlag || stImsCap.ucSrvccMidCallOnImsSupportFlag
                || stImsCap.ucSrvccAlertingOnImsSupportFlag || stImsCap.ucSrvccPreAlertingOnImsSupportFlag);

    /* 赋值到全局变量，aucNetworkCapability中srvcc的bit位所在的位置参考3GPP 24008 */
    if ( VOS_TRUE == ucSrvccFlg)
    {
        NAS_MML_SetSupportSrvccFlg(VOS_TRUE);
        pstMsCapability->stMsNetworkCapability.aucNetworkCapability[2] |= 0x08;
    }
    else
    {
        NAS_MML_SetSupportSrvccFlg(VOS_FALSE);
        pstMsCapability->stMsNetworkCapability.aucNetworkCapability[2] &= 0xf7;
    }

    return;
}


#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_Read3GPP2UplmnNotPrefFlgNvim
 功能描述  : 读取是否支持3gpp2 UPLMN不是优选网络
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月13日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_Read3GPP2UplmnNotPrefFlgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_3GPP2_UPLMN_NOT_PREF_STRU                  st3GPP2UplmnNotPref;

    PS_MEM_SET(&st3GPP2UplmnNotPref, 0x00, sizeof(NAS_MMC_NVIM_3GPP2_UPLMN_NOT_PREF_STRU));

    /* 读NV项en_NV_Item_3GPP2_Uplmn_Not_Pref_Flg，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_3GPP2_Uplmn_Not_Pref_Flg,
                         &st3GPP2UplmnNotPref,
                         sizeof(NAS_MMC_NVIM_3GPP2_UPLMN_NOT_PREF_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_Read3GPP2UplmnNotPrefFlgNvim():WARNING: read en_NV_Item_3GPP2_Uplmn_Not_Pref_Flg Error");

        return;
    }

    /* 赋值到全局变量 */
    if (VOS_TRUE == st3GPP2UplmnNotPref.uc3GPP2UplmnNotPrefFlg)
    {
        NAS_MML_Set3GPP2UplmnNotPrefFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_Set3GPP2UplmnNotPrefFlg(VOS_FALSE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadDamCfgNvim
 功能描述  : 读取支持DAM特性相关的配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_VOID NAS_MMC_ReadDamCfgNvim(VOS_VOID)
{
    PS_NV_DAM_CONFIG_PARA_STRU                  stDamCfgInfo;
    VOS_UINT32                                  ulLength;
    VOS_UINT8                                   i;
    NAS_MML_DAM_PLMN_INFO_CONFIG_STRU          *pstDamPlmnInfoCfg = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                        stGUNasPlmn;
    MMC_LMM_PLMN_ID_STRU                        stLMMPlmn;

    PS_MEM_SET(&stDamCfgInfo, 0x00, sizeof(stDamCfgInfo));
    PS_MEM_SET(&stGUNasPlmn, 0x00, sizeof(stGUNasPlmn));
    PS_MEM_SET(&stLMMPlmn, 0x00, sizeof(stLMMPlmn));
    ulLength              = 0;
    pstDamPlmnInfoCfg     = NAS_MML_GetDamPlmnInfoCfg();

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(EN_NV_ID_DAM_CONFIG_PARA, &ulLength);

    if (ulLength > sizeof(PS_NV_DAM_CONFIG_PARA_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadDamCfgNvim(): nv length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(EN_NV_ID_DAM_CONFIG_PARA,
                         &stDamCfgInfo, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadDamCfgNvim(): read nv error");
        return;
    }

    /* 获取enable lte是否需要搜网设置 */
    if (VOS_TRUE == stDamCfgInfo.ucEnableLteTrigPlmnSearchFlag)
    {
        NAS_MML_SetEnableLteTrigPlmnSearchFlag(stDamCfgInfo.ucEnableLteTrigPlmnSearchFlag);
    }

    if (stDamCfgInfo.stDamConfigPlmnPara.stDamPlmnList.ulPlmnNum > NAS_MML_SUPPORT_DAM_MAX_PLMN_NUM)
    {
        stDamCfgInfo.stDamConfigPlmnPara.stDamPlmnList.ulPlmnNum = NAS_MML_SUPPORT_DAM_MAX_PLMN_NUM;
    }

    if (stDamCfgInfo.stDamConfigPlmnPara.stImsiPlmnList.ulPlmnNum  > NAS_MML_SUPPORT_DAM_MAX_PLMN_NUM)
    {
        stDamCfgInfo.stDamConfigPlmnPara.stImsiPlmnList.ulPlmnNum = NAS_MML_SUPPORT_DAM_MAX_PLMN_NUM;
    }

    pstDamPlmnInfoCfg->stDamPlmnList.ucPlmnNum = (VOS_UINT8)stDamCfgInfo.stDamConfigPlmnPara.stDamPlmnList.ulPlmnNum;

    for (i = 0; i < stDamCfgInfo.stDamConfigPlmnPara.stDamPlmnList.ulPlmnNum; i++)
    {
        stLMMPlmn.aucPlmnId[0] = stDamCfgInfo.stDamConfigPlmnPara.stDamPlmnList.astPlmnId[i].aucPlmnId[0];
        stLMMPlmn.aucPlmnId[1] = stDamCfgInfo.stDamConfigPlmnPara.stDamPlmnList.astPlmnId[i].aucPlmnId[1];
        stLMMPlmn.aucPlmnId[2] = stDamCfgInfo.stDamConfigPlmnPara.stDamPlmnList.astPlmnId[i].aucPlmnId[2];

        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLMMPlmn, &stGUNasPlmn);

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stGUNasPlmn))
        {
            pstDamPlmnInfoCfg->stDamPlmnList.astPlmnId[i].ulMcc = stGUNasPlmn.ulMcc;
            pstDamPlmnInfoCfg->stDamPlmnList.astPlmnId[i].ulMnc = stGUNasPlmn.ulMnc;
        }
    }

    pstDamPlmnInfoCfg->stImsiPlmnList.ucPlmnNum = (VOS_UINT8)stDamCfgInfo.stDamConfigPlmnPara.stImsiPlmnList.ulPlmnNum;

    for (i = 0; i < stDamCfgInfo.stDamConfigPlmnPara.stImsiPlmnList.ulPlmnNum; i++)
    {
        stLMMPlmn.aucPlmnId[0] = stDamCfgInfo.stDamConfigPlmnPara.stImsiPlmnList.astPlmnId[i].aucPlmnId[0];
        stLMMPlmn.aucPlmnId[1] = stDamCfgInfo.stDamConfigPlmnPara.stImsiPlmnList.astPlmnId[i].aucPlmnId[1];
        stLMMPlmn.aucPlmnId[2] = stDamCfgInfo.stDamConfigPlmnPara.stImsiPlmnList.astPlmnId[i].aucPlmnId[2];

        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLMMPlmn, &stGUNasPlmn);

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stGUNasPlmn))
        {
            pstDamPlmnInfoCfg->stImsiPlmnList.astPlmnId[i].ulMcc = stGUNasPlmn.ulMcc;
            pstDamPlmnInfoCfg->stImsiPlmnList.astPlmnId[i].ulMnc = stGUNasPlmn.ulMnc;
        }
    }

    /* 获取在DAM网络disable lte后是否需要将DAM网络加入禁止接入技术网络列表中 */
    if (VOS_TRUE == stDamCfgInfo.ucAddDamPlmnInDisablePlmnWithRatListFlag)
    {
        NAS_MML_SetAddDamPlmnInDisablePlmnWithRatListFlag(VOS_TRUE);
    }

    return;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_ReadSyscfgTriPlmnSrchCfgNvim
 功能描述  : 读取SYSCFG触发搜网的配置
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月14日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadSyscfgTriPlmnSrchCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_SYSCFG_TRIGGER_PLMN_SEARCH_CFG_STRU        stSyscfgTriPlmnSrchCfg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    PS_MEM_SET(&stSyscfgTriPlmnSrchCfg, 0x00, sizeof(NAS_MMC_NVIM_SYSCFG_TRIGGER_PLMN_SEARCH_CFG_STRU));

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_Syscfg_Trigger_Plmn_Search_Cfg, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_SYSCFG_TRIGGER_PLMN_SEARCH_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSyscfgTriPlmnSrchCfgNvim(): en_NV_Item_Syscfg_Trigger_Plmn_Search_Cfg length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_Syscfg_Trigger_Plmn_Search_Cfg,
                         &stSyscfgTriPlmnSrchCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSyscfgTriPlmnSrchCfgNvim(): en_NV_Item_Syscfg_Trigger_Plmn_Search_Cfg error");
        return;
    }

    if (VOS_TRUE == stSyscfgTriPlmnSrchCfg.ucHighPrioRatPlmnSrchFlg)
    {
        NAS_MML_SetSyscfgTriHighRatSrchFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetSyscfgTriHighRatSrchFlg(VOS_FALSE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadChangeNwCauseCfgNvim
 功能描述  : 从NV项读取用户配置的网侧拒绝原因信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月20日
   作    者   : h00285180
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MMC_ReadChangeNwCauseCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU                   stNvConfigCause;
    VOS_UINT32                                              ulRslt;

    PS_MEM_SET(&stNvConfigCause, 0x00, sizeof(NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU));

    ulRslt = NV_Read(en_NV_Item_ChangeNWCause_CFG,
                     (VOS_VOID *)&stNvConfigCause,
                     sizeof(NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU));

    if (NV_OK == ulRslt)
    {
        if (NAS_MMC_NVIM_MAX_CAUSE_NUM < stNvConfigCause.ucCsRegCauseNum)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadChangeNwCauseCfgNvim(): config NV para ucCsRegCauseNum err.");
            return;
        }

        if (NAS_MMC_NVIM_MAX_CAUSE_NUM < stNvConfigCause.ucPsRegCauseNum)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadChangeNwCauseCfgNvim(): config NV para ucPsRegCauseNum err.");
            return;
        }

        if (NAS_MMC_NVIM_MAX_CAUSE_NUM < stNvConfigCause.ucDetachCauseNum)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadChangeNwCauseCfgNvim(): config NV para ucDetachCauseNum err.");
            return;
        }

        if (NAS_MMC_NVIM_MAX_CAUSE_NUM < stNvConfigCause.ucPsSerRejCauseNum)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadChangeNwCauseCfgNvim(): config NV para ucPsSerRejCauseNum err.");
            return;
        }

        if (NAS_MMC_NVIM_MAX_CAUSE_NUM < stNvConfigCause.ucMmAbortCauseNum)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadChangeNwCauseCfgNvim(): config NV para ucMmAbortCauseNum err.");
            return;
        }

        if (NAS_MMC_NVIM_MAX_CAUSE_NUM < stNvConfigCause.ucCmSerRejCauseNum)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadChangeNwCauseCfgNvim(): config NV para ucCmSerRejCauseNum err.");
            return;
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadChangeNwCauseCfgNvim(): config NV err.");

        PS_MEM_SET(&stNvConfigCause, 0x00, sizeof(NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU));
    }

    /* 保存NV配置信息 */
    NAS_MML_SetChangeNWCauseCfg(&stNvConfigCause);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadRelPsSignalConCfgNvim
 功能描述  : 从NVIM中获取配置的t3340和T3440 定时器的时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月04日
    作    者   : h00285180
    修改内容   : 新生成函数
  2.日    期   : 2015年7月17日
    作    者   : z00161729
    修改内容   : DTS2015071505434:rau或attach请求不带follow on，网络回复attach accept或rau accept中携带follow on proceed标识，gmm需要
                增加判断如果ps rab存在或存在rabm重建或sm业务请求或cds存在缓存数据则不启动T3340，否则启动t3340开启网络防呆功能
*****************************************************************************/
VOS_VOID NAS_MMC_ReadRelPsSignalConCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_REL_PS_SIGNAL_CON_CFG_STRU                 stRelPsSigConCfg;

    PS_MEM_SET(&stRelPsSigConCfg, 0x00, sizeof(NAS_MMC_NVIM_REL_PS_SIGNAL_CON_CFG_STRU));

    if(NV_OK != NV_Read(en_NV_Item_REL_PS_SIGNAL_CON_CFG,
                        (VOS_VOID *)&stRelPsSigConCfg,
                        sizeof(NAS_MMC_NVIM_REL_PS_SIGNAL_CON_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadRelPsSignalConCfgNvim():en_NV_Item_REL_PS_SIGNAL_CON_CFG Error");
        return;
    }

    if(VOS_TRUE == stRelPsSigConCfg.ucRelPsSignalConFlg)
    {
        NAS_MML_SetRelPsSigConFlg(VOS_TRUE);
        NAS_MML_SetRelPsSigConCfg_T3340TimerLen(stRelPsSigConCfg.ulT3340Len);;
    }

    if (VOS_FALSE == stRelPsSigConCfg.ucPdpExistNotStartT3340Flag)
    {
        NAS_MML_SetPdpExistNotStartT3340Flag(stRelPsSigConCfg.ucPdpExistNotStartT3340Flag);
    }


}

#if  (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadLteRejCause14CfgNvim
 功能描述  : 从NV中获取LTE #14拒绝优化配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

  1.日    期   : 2015年1月5日
    作    者   : h00285180
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadLteRejCause14CfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_LTE_REJ_CAUSE_14_CFG_STRU    stLteRejCause14Cfg;

    PS_MEM_SET(&stLteRejCause14Cfg, 0x00, sizeof(NAS_MMC_NVIM_LTE_REJ_CAUSE_14_CFG_STRU));

    if (NV_OK != NV_Read(en_NV_Item_LTE_REJ_CAUSE_14_CFG,
                         (VOS_VOID *)&stLteRejCause14Cfg,
                         sizeof(NAS_MMC_NVIM_LTE_REJ_CAUSE_14_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadLteRejCause14CfgNvim():en_NV_Item_LTE_REJ_CAUSE_14_CFG Error");
        return;
    }

    /* 一致性测试卡，或功能未开启 */
    if (   (VOS_TRUE  == NAS_USIMMAPI_IsTestCard())
        || (VOS_FALSE == stLteRejCause14Cfg.ucLteRejCause14Flg))
    {
        NAS_MML_SetLteRejCause14Flg(VOS_FALSE);
        return;
    }

    NAS_MML_SetLteRejCause14Flg(VOS_TRUE);
    NAS_MML_SetLteRejCause14EnableLteTimerLen(stLteRejCause14Cfg.usLteRejCause14EnableLteTimerLen * NAS_MML_SIXTY_SECOND
                                 * NAS_MML_ONE_THOUSAND_MILLISECOND);
}
#endif

#if  (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadImsRatSupportNvim
 功能描述  : 从NV中IMS是否支持
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月11日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadImsRatSupportNvim(VOS_VOID)
{
    VOS_UINT32                                  ulLength;
    IMSA_NV_IMS_RAT_SUPPORT_STRU                stImsSupport;

    /* IMS能力只有在FEATURE_IMS打开时，才有可能设置为开启 */
    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(EN_NV_ID_IMS_RAT_SUPPORT, &ulLength);

    if (ulLength > sizeof(IMSA_NV_IMS_RAT_SUPPORT_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadImsRatSupportNvim():WARNING: EN_NV_ID_IMS_RAT_SUPPORT length Error");

        return;
    }

    /* 读NV项EN_NV_ID_IMS_RAT_SUPPORT，失败，直接返回 */
    if (NV_OK != NV_Read(EN_NV_ID_IMS_RAT_SUPPORT,
                         &stImsSupport, ulLength))
    {

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadImsRatSupportNvim():WARNING: read EN_NV_ID_IMS_RAT_SUPPORT Error");

        return;
    }

    /* 赋值到全局变量中 */
    NAS_MML_SetLteImsSupportFlg(stImsSupport.ucLteImsSupportFlag);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadImsCapNvim
 功能描述  : 从NV中IMS是否支持
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月11日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadImsCapNvim(VOS_VOID)
{
    VOS_UINT32                                  ulLength;
    IMS_NV_IMS_CAP_STRU                         stImsCapa;

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(EN_NV_ID_IMS_CAPABILITY, &ulLength);

    if (ulLength > sizeof(IMS_NV_IMS_CAP_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadImsCapNvim():WARNING: EN_NV_ID_IMS_CAPABILITY length Error");

        return;
    }

    /* 读NV项EN_NV_ID_IMS_CAPABILITY，失败，直接返回 */
    if (NV_OK != NV_Read(EN_NV_ID_IMS_CAPABILITY,
                         &stImsCapa, ulLength))
    {

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadImsCapNvim():WARNING: read EN_NV_ID_IMS_CAPABILITY Error");

        return;
    }

    /* 赋值到全局变量中 */
    NAS_MML_SetVoiceCallOnImsSupportFlag(stImsCapa.ucVoiceCallOnImsSupportFlag);
    NAS_MML_SetVideoCallOnImsSupportFlag(stImsCapa.ucVideoCallOnImsSupportFlag);
    NAS_MML_SetSmsOnImsSupportFlag(stImsCapa.ucSmsOnImsSupportFlag);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadUssdOnImsNvim
 功能描述  : 从NV中IMS是否支持
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月11日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUssdOnImsNvim(VOS_VOID)
{
    VOS_UINT32                                  ulLength;
    TAF_NV_IMS_USSD_SUPPORT_STRU                stUssdFlg;

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_IMS_USSD_SUPPORT_FLG, &ulLength);

    if (ulLength > sizeof(TAF_NV_IMS_USSD_SUPPORT_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadUssdOnImsNvim():WARNING: en_NV_Item_IMS_USSD_SUPPORT_FLG length Error");

        return;
    }

    /* 读NV项en_NV_Item_IMS_USSD_SUPPORT_FLG，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_IMS_USSD_SUPPORT_FLG,
                         &stUssdFlg, ulLength))
    {

        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadUssdOnImsNvim():WARNING: read en_NV_Item_IMS_USSD_SUPPORT_FLG Error");

        return;
    }

    /* NV项激活，更新USSD支持配置信息 */
    NAS_MML_SetUssdOnImsSupportFlag(stUssdFlg.ucUssdOnImsSupportFlag);

    return;
}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadDsdsActiveModemModeNvim
 功能描述  : 从NVIM中获取当前DSDS下是否双卡
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月11日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadDsdsActiveModemModeNvim(VOS_VOID)
{
    TAF_NV_DSDS_ACTIVE_MODEM_MODE_STRU  stMode;

    PS_MEM_SET(&stMode, 0x00, sizeof(TAF_NV_DSDS_ACTIVE_MODEM_MODE_STRU));

    if (NV_OK != NV_Read(en_NV_Item_DSDS_Active_Modem_Mode,
                        (VOS_VOID *)&stMode,
                        sizeof(TAF_NV_DSDS_ACTIVE_MODEM_MODE_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadDsdsActiveModemModeNvim():en_NV_Item_DSDS_Active_Modem_Mode Error");
        return;
    }

    if (TAF_NV_ACTIVE_MULTI_MODEM == stMode.enActiveModem)
    {
        NAS_MML_SetDsdsMultiModemModeFlg(VOS_TRUE);

        return;
    }

    NAS_MML_SetDsdsMultiModemModeFlg(VOS_FALSE);

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ReadCsmoSupportedCfgNvim
 功能描述  : 从NVIM中获取当前是否配置支持CSMO
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月11日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadCsmoSupportedCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_CSMO_SUPPORTED_CFG_STRU  stNvimCfgCsmoInfo;

    PS_MEM_SET(&stNvimCfgCsmoInfo, 0x00, sizeof(stNvimCfgCsmoInfo));

    if (NV_OK != NV_Read(en_NV_Item_Csmo_Supported_Cfg_Info,
                        (VOS_VOID *)&stNvimCfgCsmoInfo,
                        sizeof(NAS_MMC_NVIM_CSMO_SUPPORTED_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadCsmoSupportedCfgNvim():en_NV_Item_Csmo_Supported_Cfg_Info Error");
        return;
    }

    if (VOS_TRUE == stNvimCfgCsmoInfo.ucCsmoSupportedFlg)
    {
        NAS_MML_SetCsmoSupportedFlg(VOS_TRUE);

        return;
    }

    NAS_MML_SetCsmoSupportedFlg(VOS_FALSE);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadCsmoSupportedCfgNvim
 功能描述  : 从NVIM中获取当前是否配置支持CSMO
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月11日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadT3212TimerCfgNvim(VOS_VOID)
{
    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU                   *pstT3212Info        = VOS_NULL_PTR;
    NAS_MMC_NVIM_T3212_TIMER_CFG_STRU                       stNvimCfgT3212Info;

    pstT3212Info = NAS_MML_GetT3212TimerInfo();
    PS_MEM_SET(&stNvimCfgT3212Info, 0x00, sizeof(stNvimCfgT3212Info));

    if (NV_OK != NV_Read(en_NV_Item_T3212_Timer_Cfg_Info,
                        (VOS_VOID *)&stNvimCfgT3212Info,
                        sizeof(NAS_MMC_NVIM_T3212_TIMER_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadT3212TimerCfgNvim():en_NV_Item_Csmo_Supported_Cfg_Info Error");
        return;
    }

    pstT3212Info->ulT3212NvActiveFlg = VOS_FALSE;

    /* 对NV配置的异常值进行兼容处理, 配置T3212时长为0，则修改为默认6分钟 */
    if (0 == stNvimCfgT3212Info.ulT3212Phase1TimeLen)
    {
        stNvimCfgT3212Info.ulT3212Phase1TimeLen = NAS_MML_T3212_DEFAULT_UNIT_LEN;
    }

    /* 对NV配置的异常值进行兼容处理, 配置T3212时长为0，则修改为默认6分钟 */
    if (0 == stNvimCfgT3212Info.ulT3212Phase2TimeLen)
    {
        stNvimCfgT3212Info.ulT3212Phase2TimeLen = NAS_MML_T3212_DEFAULT_UNIT_LEN;
    }

    /* NV配置的T3212最大定时器不超过18小时 */
    if (stNvimCfgT3212Info.ulT3212Phase1TimeLen >= NAS_MML_T3212_CFG_MAX_VALUE)
    {
        stNvimCfgT3212Info.ulT3212Phase1TimeLen = NAS_MML_T3212_CFG_MAX_VALUE;
    }

    /* NV配置的T3212最大定时器不超过18小时 */
    if (stNvimCfgT3212Info.ulT3212Phase2TimeLen >= NAS_MML_T3212_CFG_MAX_VALUE)
    {
        stNvimCfgT3212Info.ulT3212Phase2TimeLen = NAS_MML_T3212_CFG_MAX_VALUE;
    }

    if (VOS_TRUE == stNvimCfgT3212Info.ulNvActiveFlg)
    {
        pstT3212Info->ulT3212NvActiveFlg = VOS_TRUE;
    }

    pstT3212Info->ulT3212StartSceneCtrlBitMask  = stNvimCfgT3212Info.ulT3212StartSceneCtrlBitMask;
    pstT3212Info->ulT3212Phase1TimeLen          = stNvimCfgT3212Info.ulT3212Phase1TimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND;
    pstT3212Info->ulT3212Phase1Count            = stNvimCfgT3212Info.ulT3212Phase1Count;
    pstT3212Info->ulT3212Phase2TimeLen          = stNvimCfgT3212Info.ulT3212Phase2TimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND;
    pstT3212Info->ulT3212Phase2Count            = stNvimCfgT3212Info.ulT3212Phase2Count;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadRoamDisplayCfgNvim
 功能描述  : 从NVIM中获取当前判断是否漫游时是否要考虑EPLMN
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月20日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadRoamDisplayCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_ROAM_DISPLAY_CFG_STRU          stNvimRoamDisplayCfg;;

    PS_MEM_SET(&stNvimRoamDisplayCfg, 0x00, sizeof(stNvimRoamDisplayCfg));

    if (NV_OK != NV_Read(en_NV_Item_Roam_Display_Cfg,
                        (VOS_VOID *)&stNvimRoamDisplayCfg,
                        sizeof(NAS_MMC_NVIM_ROAM_DISPLAY_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadRoamDisplayCfgNvim():en_NV_Item_Roam_Display_Cfg Error");
        return;
    }

    if (VOS_TRUE == stNvimRoamDisplayCfg.ucHplmnInEplmnDisplayHomeFlg)
    {
        NAS_MML_SetHplmnInEplmnDisplayHomeFlg(VOS_TRUE);

        return;
    }

    NAS_MML_SetHplmnInEplmnDisplayHomeFlg(VOS_FALSE);

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadLteOos2GPrefPlmnSelCfgNvim
 功能描述  : 读取Lte OOS选网优化NV配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月03日
    作    者   : h00285180
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadLteOos2GPrefPlmnSelCfgNvim(VOS_VOID)
{
    VOS_UINT32                                              i;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stSimPlmn;
    NAS_MML_PLMN_ID_STRU                                    stPlmn;
    NAS_MMC_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU          stLteOosPlmnSelCfgNvim;
    NAS_MML_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU              *pstLteOosPlmnSelCfg = VOS_NULL_PTR;

    PS_MEM_SET(&stLteOosPlmnSelCfgNvim, 0x00, sizeof(NAS_MMC_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU));
    PS_MEM_SET(&stSimPlmn, 0x00, sizeof(stSimPlmn));
    PS_MEM_SET(&stPlmn, 0x00, sizeof(stPlmn));

    pstLteOosPlmnSelCfg = NAS_MML_GetLteOos2GPrefPlmnSelCfg();
    pstLteOosPlmnSelCfg->ucImsiListNum  = 0;

    if (NV_OK != NV_Read(en_NV_Item_LTE_OOS_2G_PREF_PLMN_SEL_CFG, &stLteOosPlmnSelCfgNvim, sizeof(NAS_MMC_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteOos2GPrefPlmnSelCfgNvim:Read NV Failed");
        return;
    }

    /* 参数保护,超过最大值按照最大值计算 */
    if (NAS_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_MAX_IMSI_LIST_NUM < stLteOosPlmnSelCfgNvim.ucImsiListNum)
    {
        stLteOosPlmnSelCfgNvim.ucImsiListNum = NAS_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_MAX_IMSI_LIST_NUM;
    }

    /* 将USIM中保存的PLMN信息转换为内存中的信息 */
    for ( i = 0; i < stLteOosPlmnSelCfgNvim.ucImsiListNum; i++ )
    {
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, stLteOosPlmnSelCfgNvim.astImsiList[i].aucSimPlmn, NAS_MML_SIM_PLMN_ID_LEN);
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stPlmn))
        {
            pstLteOosPlmnSelCfg->astImsiList[pstLteOosPlmnSelCfg->ucImsiListNum].ulMcc = stPlmn.ulMcc;
            pstLteOosPlmnSelCfg->astImsiList[pstLteOosPlmnSelCfg->ucImsiListNum].ulMnc = stPlmn.ulMnc;
            pstLteOosPlmnSelCfg->ucImsiListNum++;
        }
    }
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadPsRegFailMaxTimesTrigLauOnceFlgNvim
 功能描述  : 从NVIM中获取联合Attach/Rau建链失败达到最大次数是否只触发一次LAU的NV配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : l00289540
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadPsRegFailMaxTimesTrigLauOnceFlgNvim(VOS_VOID)
{
    NAS_NVIM_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG_STRU stPsRegFailMaxTimesTrigLauOnce;
    VOS_UINT32                                            ulLength;

    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPsRegFailMaxTimesTrigLauOnceFlgNvim():WARNING: en_NV_Item_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG length Error");

        return;
    }

    PS_MEM_SET(&stPsRegFailMaxTimesTrigLauOnce, 0x00, sizeof(NAS_NVIM_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG_STRU));

    if (NV_OK != NV_Read(en_NV_Item_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG,
                        (VOS_VOID *)&stPsRegFailMaxTimesTrigLauOnce,
                        sizeof(NAS_NVIM_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                  "NAS_MMC_ReadPsRegFailMaxTimesTrigLauOnceFlgNvim():en_NV_Item_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG Error");
    }

    if (VOS_TRUE == stPsRegFailMaxTimesTrigLauOnce.ucPsRegFailMaxTimesTrigLauOnceFlg)
    {
        NAS_MML_SetPsRegFailMaxTimesTrigLauOnceFlg(VOS_TRUE);

        return;
    }

    NAS_MML_SetPsRegFailMaxTimesTrigLauOnceFlg(VOS_FALSE);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadKeepSrchHplmnEvenRejByCause13Nvim
 功能描述  : 从NVIM中获取HPLMN注册被#13拒绝之后是否再搜该HPLMN with rat的NV配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : l00289540
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadKeepSrchHplmnEvenRejByCause13Nvim(VOS_VOID)
{
    NAS_NVIM_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG_STRU  stKeepSrchHplmnEvenRejByCause13;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadKeepSrchHplmnEvenRejByCause13Nvim():WARNING: en_NV_Item_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG length Error");

        return;
    }

    PS_MEM_SET(&stKeepSrchHplmnEvenRejByCause13, 0x00, sizeof(stKeepSrchHplmnEvenRejByCause13));

    if (NV_OK != NV_Read(en_NV_Item_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG,
                        (VOS_VOID *)&stKeepSrchHplmnEvenRejByCause13,
                        sizeof(NAS_NVIM_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                  "NAS_MMC_ReadKeepSrchHplmnEvenRejByCause13Nvim():en_NV_Item_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG Error");
    }

    if (VOS_TRUE == stKeepSrchHplmnEvenRejByCause13.ucKeepSrchHplmnEvenRejByCause13Flg)
    {
        NAS_MML_SetKeepSrchHplmnEvenRejByCause13Flg(VOS_TRUE);

        return;
    }

    NAS_MML_SetKeepSrchHplmnEvenRejByCause13Flg(VOS_FALSE);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadEpsRejByCause14InVplmnAllowPsRegFlgNvim
 功能描述  : 从NVIM中获取VPLMN注册被#14拒绝之后是否允许在2/3G PS域注册的NV配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : l00289540
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadEpsRejByCause14InVplmnAllowPsRegFlgNvim(VOS_VOID)
{
    NAS_NVIM_EPS_REJ_BY_CAUSE_14_IN_VPLMN_ALLOW_PS_REG_CFG_STRU stEpsRejByCause14InVplmnAllowPsRegCfg;
    VOS_UINT32                                                  ulLength;

    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_EPS_REJ_BY_CAUSE_14_IN_VPLMN_Allow_PS_REG_CFG, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_EPS_REJ_BY_CAUSE_14_IN_VPLMN_ALLOW_PS_REG_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadEpsRejByCause14InVplmnAllowPsRegFlgNvim():WARNING: en_NV_Item_EPS_REJ_BY_CAUSE_14_IN_VPLMN_Allow_PS_REG_CFG length Error");

        return;
    }

    PS_MEM_SET(&stEpsRejByCause14InVplmnAllowPsRegCfg,
                0x00,
                sizeof(NAS_NVIM_EPS_REJ_BY_CAUSE_14_IN_VPLMN_ALLOW_PS_REG_CFG_STRU));

    if (NV_OK != NV_Read(en_NV_Item_EPS_REJ_BY_CAUSE_14_IN_VPLMN_Allow_PS_REG_CFG,
                        (VOS_VOID *)&stEpsRejByCause14InVplmnAllowPsRegCfg,
                        sizeof(NAS_NVIM_EPS_REJ_BY_CAUSE_14_IN_VPLMN_ALLOW_PS_REG_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                  "NAS_MMC_ReadEpsRejByCause14InVplmnAllowPsRegFlgNvim():en_NV_Item_EPS_REJ_BY_CAUSE_14_IN_VPLMN_Allow_PS_REG_CFG Error");
        return;
    }

    if (VOS_TRUE == stEpsRejByCause14InVplmnAllowPsRegCfg.ucEpsRejByCause14InVplmnAllowPsRegFlg)
    {
        NAS_MML_SetEpsRejByCause14InVplmnAllowPsRegFlg(VOS_TRUE);

        return;
    }

    NAS_MML_SetEpsRejByCause14InVplmnAllowPsRegFlg(VOS_FALSE);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadCarryEplmnWhenSrchRplmnCfgNvim
 功能描述  : 从NVIM中读取搜索RPLMN是否需要携带EPLMN的NV配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : l00289540
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadCarryEplmnWhenSrchRplmnCfgNvim(VOS_VOID)
{
    NAS_NVIM_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU           stCarryEplmnWhenSrchRplmnCfg;
    NAS_MML_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU           *pstCarryEplmnWhenSrchRplmnCfg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCarryEplmnWhenSrchRplmnCfgNvim():WARNING: en_NV_Item_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG length Error");

        return;
    }

    PS_MEM_SET(&stCarryEplmnWhenSrchRplmnCfg,
                0x00,
                sizeof(NAS_NVIM_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU));

    pstCarryEplmnWhenSrchRplmnCfg = NAS_MML_GetCarryEplmnWhenSrchRplmnCfg();

    if (NV_OK != NV_Read(en_NV_Item_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG,
                        (VOS_VOID *)&stCarryEplmnWhenSrchRplmnCfg,
                        sizeof(NAS_NVIM_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                  "NAS_MMC_ReadCarryEplmnWhenSrchRplmnCfgNvim():en_NV_Item_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG Error");
    }

    if (NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_BUTT > stCarryEplmnWhenSrchRplmnCfg.enSwitchFlag)
    {
        pstCarryEplmnWhenSrchRplmnCfg->enSwitchFlag = stCarryEplmnWhenSrchRplmnCfg.enSwitchFlag;
    }
    else
    {
        pstCarryEplmnWhenSrchRplmnCfg->enSwitchFlag = NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_OFF;
    }

    if (VOS_TRUE == stCarryEplmnWhenSrchRplmnCfg.ucCarryEplmnSceneSwitchOn)
    {
        pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneSwitchOn = VOS_TRUE;
    }

    if (VOS_TRUE == stCarryEplmnWhenSrchRplmnCfg.ucCarryEplmnSceneAreaLost)
    {
        pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneAreaLost = VOS_TRUE;
    }

    if (VOS_TRUE == stCarryEplmnWhenSrchRplmnCfg.ucCarryEplmnSceneAvailableTimerExpired)
    {
        pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneAvailableTimerExpired = VOS_TRUE;
    }

    if (VOS_TRUE == stCarryEplmnWhenSrchRplmnCfg.ucCarryEplmnSceneCSFBServiceRej)
    {
        pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneCSFBServiceRej = VOS_TRUE;
    }

    if (VOS_TRUE == stCarryEplmnWhenSrchRplmnCfg.ucCarryEplmnSceneDisableLte)
    {
        pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneDisableLte = VOS_TRUE;
    }

    if (VOS_TRUE == stCarryEplmnWhenSrchRplmnCfg.ucCarryEplmnSceneEnableLte)
    {
        pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneEnableLte = VOS_TRUE;
    }

    if (VOS_TRUE == stCarryEplmnWhenSrchRplmnCfg.ucCarryEplmnSceneSysCfgSet)
    {
        pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneSysCfgSet = VOS_TRUE;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadProtectMtCsfbPagingProcedureLenNvim
 功能描述  : 从NVIM中获取mt csfb paging procedure timer的长度
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月4日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadProtectMtCsfbPagingProcedureLenNvim(VOS_VOID)
{
    NAS_MMC_NVIM_PROTECT_MT_CSFB_PAGING_PROCEDURE_LEN_STRU  stNvimProtectMtCsfbPagingProcedureLen;;

    PS_MEM_SET(&stNvimProtectMtCsfbPagingProcedureLen, 0x00, sizeof(stNvimProtectMtCsfbPagingProcedureLen));

    if (NV_OK != NV_Read(en_NV_Item_Protect_Mt_Csfb_Paging_Procedure_Len,
                        (VOS_VOID *)&stNvimProtectMtCsfbPagingProcedureLen,
                        sizeof(NAS_MMC_NVIM_PROTECT_MT_CSFB_PAGING_PROCEDURE_LEN_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadProtectMtCsfbPagingProcedureLenNvim():en_NV_Item_Protect_Mt_Csfb_Paging_Procedure_Len Error");
        return;
    }

    if (stNvimProtectMtCsfbPagingProcedureLen.usMtCsfbPagingProcedureLen < NAS_MML_PROTECT_MT_CSFB_PAGING_PROCEDURE_MIN_LEN)
    {
        NAS_MML_SetProtectMtCsfbPagingProcedureLen(NAS_MML_PROTECT_MT_CSFB_PAGING_PROCEDURE_MIN_LEN);

        return;
    }

    if (stNvimProtectMtCsfbPagingProcedureLen.usMtCsfbPagingProcedureLen > NAS_MML_PROTECT_MT_CSFB_PAGING_PROCEDURE_MAX_LEN)
    {
        NAS_MML_SetProtectMtCsfbPagingProcedureLen(NAS_MML_PROTECT_MT_CSFB_PAGING_PROCEDURE_MAX_LEN);

        return;
    }

    NAS_MML_SetProtectMtCsfbPagingProcedureLen(stNvimProtectMtCsfbPagingProcedureLen.usMtCsfbPagingProcedureLen);

    return;
}

/* added by y00176023 for DTS2015091602371 澳电低优先级ANYCELL搜LTE定制, 2015-9-17, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_ReadLowPrioAnycellsearchLteCfgNvim
 功能描述  : 从NVIM中获取当前值判断anyCell 搜是否优先搜索3G/2G
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月19日
    作    者   : y00176023
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ReadLowPrioAnycellsearchLteCfgNvim(VOS_VOID)
{
    NAS_NVIM_LOW_PRIO_ANYCELL_SEARCH_LTE_FLG_STRU           stNvimLowPrioAnycellsearchLteCfg;

    PS_MEM_SET(&stNvimLowPrioAnycellsearchLteCfg, 0x00, sizeof(NAS_NVIM_LOW_PRIO_ANYCELL_SEARCH_LTE_FLG_STRU));

    if (NV_OK != NV_Read(en_NV_Item_Low_Prio_Anycell_Search_Lte_Cfg,
                        (VOS_VOID *)&stNvimLowPrioAnycellsearchLteCfg,
                        sizeof(NAS_NVIM_LOW_PRIO_ANYCELL_SEARCH_LTE_FLG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadLowPrioAnycellsearchLteCfgNvim():en_NV_Item_Low_Prio_Anycell_Search_Lte_Cfg Error");
        return;
    }

    if (VOS_TRUE == stNvimLowPrioAnycellsearchLteCfg.ucLowPrioAnycellSearchLteFlg)
    {
        NAS_MML_SetLowPrioAnycellSearchLteFlg(VOS_TRUE);

        return;
    }

    NAS_MML_SetLowPrioAnycellSearchLteFlg(VOS_FALSE);

    return;
}
/* added by y00176023 for DTS2015091602371 澳电低优先级ANYCELL搜LTE定制, 2015-9-17, end */


/*****************************************************************************
 函 数 名  : NAS_MMC_ReadCsRegFailForbLaTimeCfgNvim
 功能描述  : 读取en_NV_Item_CS_REG_FAIL_CAUSE_FORB_LA_TIME_CFG 配置
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : z00359541
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_MMC_ReadCsRegFailForbLaTimeCfgNvim(VOS_VOID)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    NAS_MMC_NVIM_CUSTOMIZED_FORB_LA_CFG_STRU         stCustomizedForbLaCfg;

    PS_MEM_SET(&stCustomizedForbLaCfg, 0x00, sizeof(stCustomizedForbLaCfg));

    pstForbLaWithValidPeriodCfg = NAS_MML_GetForbLaWithValidPeriodCfg();

    /* 测试卡不生效 */
    if (VOS_TRUE  == NAS_USIMMAPI_IsTestCard())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCsRegFailForbLaTimeCfgNvim():Test SIM, Forb La List Invalid");
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_CS_REG_FAIL_FORB_LA_TIME_CFG, &stCustomizedForbLaCfg,
                          sizeof(NAS_MMC_NVIM_CUSTOMIZED_FORB_LA_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCsRegFailForbLaTimeCfgNvim():Read NV Failed");
        return;
    }

    if (stCustomizedForbLaCfg.usRegFailCauseNum > NAS_MML_NVIM_MAX_REG_FAIL_CAUSE_NUM)
    {
        NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_ReadCsRegFailForbLaTimeCfgNvim(): Forb La Num read from NV exceeds max", stCustomizedForbLaCfg.usRegFailCauseNum);
        stCustomizedForbLaCfg.usRegFailCauseNum = NAS_MML_NVIM_MAX_REG_FAIL_CAUSE_NUM;
    }

    pstForbLaWithValidPeriodCfg->ulSupportForbLaWithValidPeriodNum = stCustomizedForbLaCfg.usRegFailCauseNum;

    for (i = 0; i < pstForbLaWithValidPeriodCfg->ulSupportForbLaWithValidPeriodNum; i++)
    {
        pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usRegFailCause              = stCustomizedForbLaCfg.ausRegFailCauseList[i];
        pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usForbLaValidPeriodLen      = stCustomizedForbLaCfg.usForbLaTimeLen;
        pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usPunishTimeLen               = stCustomizedForbLaCfg.usPunishTimeLen;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadKeepCsForbInfoWhenPsRegSuccCfgNvim
 功能描述  : 读取en_NV_Item_KEEP_CS_FORB_INFO_WHEN_PS_REG_SUCC_CFG 配置
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月11日
    作    者   : z00359541
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_MMC_ReadKeepCsForbInfoWhenPsRegSuccCfgNvim(VOS_VOID)
{
    NAS_NVIM_KEEP_CS_FORB_INFO_WHEN_PS_REG_SUCC_STRU           stKeepCsForbInfoCfg;

    PS_MEM_SET(&stKeepCsForbInfoCfg, 0x00, sizeof(stKeepCsForbInfoCfg));

    /* 测试卡不生效 */
    if (VOS_TRUE  == NAS_USIMMAPI_IsTestCard())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadKeepCsForbInfoWhenPsRegSuccCfgNvim():Test SIM, Do not keep CS Forb Info when PS Reg Succ");
        NAS_MML_SetKeepCsForbInfoCfg(VOS_FALSE);
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_KEEP_CS_FORB_INFO_WHEN_PS_REG_SUCC_CFG, &stKeepCsForbInfoCfg,
                          sizeof(NAS_NVIM_KEEP_CS_FORB_INFO_WHEN_PS_REG_SUCC_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadKeepCsForbInfoWhenPsRegSuccCfgNvim():Read NV Failed");
        NAS_MML_SetKeepCsForbInfoCfg(VOS_FALSE);
        return;
    }

    if (VOS_TRUE == stKeepCsForbInfoCfg.ucKeepCsForbInfoFlg)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadKeepCsForbInfoWhenPsRegSuccCfgNvim(): Set to TRUE");
        NAS_MML_SetKeepCsForbInfoCfg(VOS_TRUE);
        return;
    }

    NAS_MML_SetKeepCsForbInfoCfg(VOS_FALSE);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ReadClearCksnCfgNvim
 功能描述  : 读取en_NV_Item_CLEAR_CKSN_CFG 配置
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : z00359541
    修改内容   : 新建
  2.日    期   : 2016年1月19日
    作    者   : c00318887
    修改内容   : 扩充NV
*****************************************************************************/
VOS_VOID NAS_MMC_ReadClearCksnCfgNvim(VOS_VOID)
{
    NAS_NVIM_CLEAR_CKSN_STRU            stClearCksnCfg;

    PS_MEM_SET(&stClearCksnCfg, 0x00, sizeof(stClearCksnCfg));
    
    NAS_MML_SetNwIgnoreAuthFailCfg(VOS_FALSE);
    NAS_MML_SetUsimGsmAuthNvCfg(VOS_FALSE);

    /* 测试卡不生效 */
    if (VOS_TRUE  == NAS_USIMMAPI_IsTestCard())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadClearCksnCfgNvim():Test Card, Do not Clear CKSN");
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_CLEAR_CKSN_CFG, &stClearCksnCfg,
                          sizeof(NAS_NVIM_CLEAR_CKSN_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadClearCksnCfgNvim():Read NV Failed");
        return;
    }

    if (VOS_TRUE == stClearCksnCfg.ucNwIgnoreAuthFailFlg)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadClearCksnCfgNvim(): Set NwIgnoreAuthFailFlg to TRUE");
        NAS_MML_SetNwIgnoreAuthFailCfg(VOS_TRUE);
    }

    if (VOS_TRUE == stClearCksnCfg.ucUsimGsmAuthCfg)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadClearCksnCfgNvim(): Set UsimGsmAuthFlg to TRUE");
        NAS_MML_SetUsimGsmAuthNvCfg(VOS_TRUE);
    }


    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


