/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMsccProcNvim.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2015年01月26日
  功能描述   : MSCC module读NVIM处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年01月26日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsCommonDef.h"
#include "NasMsccProcNvim.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "ImsaNvInterface.h"
#include "LPsNvInterface.h"
#include "LNvCommon.h"
#endif
#include "NVIM_Interface.h"
#include "NasNvInterface.h"

#include "NasMntn.h"
#include "NasMsccTimerMgmt.h"
#include "NasMsccComFunc.h"

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
#include "NasDynLoad.h"
#endif

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_PROC_NVIM_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
Function Name   :   NAS_MSCC_ReadNvim_SwitchOn
Description     :   This function is used to read NVIM info while switch on.
Input parameters:   None.
Output parameters:  None.
Return Value    :   VOS_VOID.
Modify History:
    1)  Date    :   2014-02-02
        Author  :   a00295761
        Modify content :    Create
    2)  Date    :   2015-04-11
        Author  :   a00295761
        Modify content :CDMA 1X Iteration Modified
    3.  日    期   : 2016年1月6日
        作    者   : w00242748
        修改内容   : DTS2015072705348:进入紧急呼回呼模式后，挂起HRPD和LTE；退出紧急呼
                     回呼模式后，再进行搜网，紧急呼回呼模式下，不进行其他任何形式搜网；
*****************************************************************************/

VOS_VOID NAS_MSCC_ReadNvim(VOS_VOID)
{
    /* INit the Platform RAT cap structure */
    NAS_MSCC_ReadPlatformRatCapNvim();

    /* Init the IMS Config Parameter Structure */
    NAS_MSCC_ReadImsCfgInfoNvim();

    /* Read the NV System Acquire Info */
    NAS_MSCC_ReadMmssNvimInfo();

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    NAS_DYNLOAD_ReadDynloadCtrlNvim();

    NAS_DYNLOAD_ReadDynloadExceptionCtrlNvim();
#endif

    NAS_MSCC_ReadEmcCallBackCfgNvim();

    NAS_MSCC_Read1xServiceClSysAcqStrategyCfgNvim();
}


VOS_VOID NAS_MSCC_ReadImsCfgInfoNvim(VOS_VOID)
{
    /* Read NVIM to update the IMS RAT support */
    NAS_MSCC_ReadImsRatSupportNvim();

    /* Init the Voice domain */
    NAS_MSCC_ReadVoiceDomainNvim();

    /* Init the Ims Voice Cap Timer Len */
    NAS_MSCC_ReadWaitImsVoiceCapTimerLenNvim();
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_ReadImsRatSupportNvim
 功能描述  : 初始化IMS支持信息
 输入参数  : pstImsCfgInfo -- 本地保存IMS NV配置信息地址

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月27日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年04月13日
   作    者   : w00176964
   修改内容   : CDMA 1x Iteration 10 Modified

*****************************************************************************/
VOS_VOID NAS_MSCC_ReadImsRatSupportNvim(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                          ulLength;
    IMSA_NV_IMS_RAT_SUPPORT_STRU        stImsSupport;
#endif

    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();

    /* IMS宏关闭时，默认初始化为不支持IMS */
    PS_MEM_SET(&(pstImsCfgInfo->stImsRatSupport), 0, sizeof(NAS_MSCC_IMS_RAT_SUPPORT_STRU));

    pstImsCfgInfo->stImsRatSupport.ucGsmImsSupportFlag   = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucUtranImsSupportFlag = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucLteImsSupportFlag   = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucGsmEmsSupportFlag   = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucUtranEmsSupportFlag = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucLteEmsSupportFlag   = VOS_FALSE;

    /* IMS能力只有在FEATURE_IMS打开时，才有可能设置为开启 */
#if (FEATURE_ON == FEATURE_IMS)
    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(EN_NV_ID_IMS_RAT_SUPPORT, &ulLength);

    if (ulLength > sizeof(IMSA_NV_IMS_RAT_SUPPORT_STRU))
    {
        NAS_TRACE_HIGH("NAS_MSCC_ReadImsRatSupportNvim(): EN_NV_ID_IMS_RAT_SUPPORT length Error");

        return;
    }

    /* 读NV项EN_NV_ID_IMS_RAT_SUPPORT，失败，直接返回 */
    if (NV_OK != NV_Read(EN_NV_ID_IMS_RAT_SUPPORT, &stImsSupport, ulLength))
    {

        NAS_TRACE_HIGH("NAS_MSCC_ReadImsRatSupportNvim(): read EN_NV_ID_IMS_RAT_SUPPORT Error");

        return;
    }

    /* 赋值到全局变量中 */
    pstImsCfgInfo->stImsRatSupport.ucGsmImsSupportFlag   = stImsSupport.ucGsmEmsSupportFlag;
    pstImsCfgInfo->stImsRatSupport.ucUtranImsSupportFlag = stImsSupport.ucUtranImsSupportFlag;
    pstImsCfgInfo->stImsRatSupport.ucLteImsSupportFlag   = stImsSupport.ucLteImsSupportFlag;
    pstImsCfgInfo->stImsRatSupport.ucGsmEmsSupportFlag   = stImsSupport.ucGsmEmsSupportFlag;
    pstImsCfgInfo->stImsRatSupport.ucUtranEmsSupportFlag = stImsSupport.ucUtranEmsSupportFlag;
    pstImsCfgInfo->stImsRatSupport.ucLteEmsSupportFlag   = stImsSupport.ucLteEmsSupportFlag;
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_ReadVoiceDomainNvim
 功能描述  : 初始化语音优选域
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月29日
   作    者   : y00245242
   修改内容   : 新生成函数

 2.日    期   : 2015年04月13日
   作    者   : w00176964
   修改内容   : CDMA 1x Iteration 10 Modified
*****************************************************************************/
VOS_VOID NAS_MSCC_ReadVoiceDomainNvim(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                          ulLength;
    LNAS_LMM_NV_VOICE_DOMAIN_STRU       stVoiceDomain;
#endif

    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();

    /* NV关闭时，默认初始化为CS ONLY */
    pstImsCfgInfo->enVoiceDomain = NAS_MSCC_VOICE_DOMAIN_CS_ONLY;

#if (FEATURE_ON == FEATURE_IMS)
    pstImsCfgInfo->enVoiceDomain = NAS_MSCC_VOICE_DOMAIN_IMS_PS_PREFERRED;

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(EN_NV_ID_UE_VOICE_DOMAIN, &ulLength);

    if (ulLength > sizeof(LNAS_LMM_NV_VOICE_DOMAIN_STRU))
    {
        NAS_TRACE_HIGH("NAS_MSCC_ReadVoiceDomainNvim(): EN_NV_ID_UE_VOICE_DOMAIN length Error");

        return;
    }

    /* 读NV项EN_NV_ID_UE_VOICE_DOMAIN，失败，直接返回 */
    if (NV_OK != NV_Read(EN_NV_ID_UE_VOICE_DOMAIN,
                         &stVoiceDomain, ulLength))
    {

        NAS_TRACE_HIGH("NAS_MSCC_ReadVoiceDomainNvim(): read EN_NV_ID_UE_VOICE_DOMAIN Error");

        return;
    }

    /* NV项激活，并且取值合法时，赋值到全局变量中 */
    if ( (VOS_TRUE                              == stVoiceDomain.bitOpVoicDomain)
      && (NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED >= stVoiceDomain.enVoicDomain) )
    {
        pstImsCfgInfo->enVoiceDomain = stVoiceDomain.enVoicDomain;
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_ReadWaitImsVoiceCapTimerLenNvim
 功能描述  : 从NV中获取等待IMS VOICE CAP的定时器时长
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年01月29日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年4月13日
   作    者   : w00176964
   修改内容   : CDMA 1x Iteration Modified

*****************************************************************************/
VOS_VOID NAS_MSCC_ReadWaitImsVoiceCapTimerLenNvim(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_IMS)
    NAS_NVIM_WAIT_IMS_VOICE_AVAIL_TIMER_LEN_STRU            stImsVoiceAvailTimerLen;
    VOS_UINT32                                              ulLength;
#endif
    NAS_MSCC_IMS_CONFIG_PARA_STRU                          *pstImsCfgInfo;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();

    pstImsCfgInfo->ulWaitImsVoiceAvailTimerLen = TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_AVAIL_IND_LEN;

#if (FEATURE_ON == FEATURE_IMS)
    ulLength = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_WAIT_IMS_VOICE_AVAIL_Timer_Len, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_WAIT_IMS_VOICE_AVAIL_TIMER_LEN_STRU))
    {
        NAS_TRACE_HIGH("NAS_MSCC_ReadWaitImsVoiceCapTimerLenNvim(): en_NV_Item_WAIT_IMS_VOICE_AVAIL_Timer_Len length Error");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_WAIT_IMS_VOICE_AVAIL_Timer_Len,
                         &stImsVoiceAvailTimerLen,
                         ulLength))
    {
        NAS_TRACE_HIGH("NAS_MSCC_ReadWaitImsVoiceCapTimerLenNvim(): en_NV_Item_WAIT_IMS_VOICE_AVAIL_Timer_Len error");
        return;
    }

    if (VOS_TRUE == stImsVoiceAvailTimerLen.ucNvimActiveFlag)
    {
        /* NV的长度为0使用默认时长,NV的单位为S,需要转换为毫秒 */
        if (0 == stImsVoiceAvailTimerLen.ucWaitImsVoiceAvailTimerLen)
        {
            pstImsCfgInfo->ulWaitImsVoiceAvailTimerLen = TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_AVAIL_IND_LEN;
        }
        else
        {
            pstImsCfgInfo->ulWaitImsVoiceAvailTimerLen = stImsVoiceAvailTimerLen.ucWaitImsVoiceAvailTimerLen * NAS_MSCC_THOUSAND_MILLISECOND_UNIT;
        }
    }
#endif

    return;
}




VOS_VOID NAS_MSCC_ReadPlatformRatCapNvim(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    PLATAFORM_RAT_CAPABILITY_STRU       stNvPlatformRatCap;
    VOS_RATMODE_ENUM_UINT32             enNasMsccPlatformRat;
    NAS_MSCC_PLATFORM_RAT_CAP_STRU     *pstPlatformRatCap;

    pstPlatformRatCap = NAS_MSCC_GetPlatformRatCap();

    /* Initialize the Platform RAT cap structure to contain only GSM */
    pstPlatformRatCap->ucRatNum      = 1;
    pstPlatformRatCap->aenRatList[0] = VOS_RATMODE_GSM;
    for (i = 1; i < VOS_RATMODE_BUTT; i++)
    {
        pstPlatformRatCap->aenRatList[i] = VOS_RATMODE_BUTT;
    }

    /* MemSet the stNvPlatformRatCap local structure to zero. Read NV 9203 to get the platform RAT capability supported*/
    PS_MEM_SET(&stNvPlatformRatCap, 0x0, sizeof(stNvPlatformRatCap));
    if (NV_OK != NV_Read(en_NV_Item_Platform_RAT_CAP,
                         &stNvPlatformRatCap,
                         sizeof(PLATAFORM_RAT_CAPABILITY_STRU)))
    {
        NAS_TRACE_HIGH("NAS_MSCC_ReadPlatformRatCapNvim():ERROR: read en_NV_Item_PLATFORM_RAT_CAP Error");

        return;
    }

    /* If the Number of RAT read from NVIM is greater than maximum, set the Number of Rat to the max value */
    if (stNvPlatformRatCap.usRatNum >= PLATFORM_MAX_RAT_NUM)
    {
        NAS_TRACE_HIGH("NAS_MSCC_ReadPlatformRatCapNvim():ERROR: en_NV_Item_PLATFORM_RAT_CAP Invalid: Number of Platforms greater than MAX");

        return;
    }

    /* Check if the NVIM data is valid */
    if (VOS_FALSE == NAS_MSCC_IsPlatformRatCapNvimValid(&stNvPlatformRatCap))
    {
        NAS_TRACE_HIGH("NAS_MSCC_ReadPlatformRatCapNvim():ERROR: en_NV_Item_PLATFORM_RAT_CAP Invalid");

        return;
    }

    j = 0;

    /* Read the NVIM data and convert the NVIM format to MSCC Enum format. Skip the BUTT plarform types */
    for (i = 0; i < stNvPlatformRatCap.usRatNum; i++)
    {
        enNasMsccPlatformRat = NAS_MSCC_ConvertNvPlatformRatToMsccType(stNvPlatformRatCap.aenRatList[i]);
        if (VOS_RATMODE_BUTT != enNasMsccPlatformRat)
        {
            pstPlatformRatCap->aenRatList[j] = enNasMsccPlatformRat;
            j ++;
        }
    }

    /* If atleast one entry is copied into the pstPlatformRatCap, update the number of RATs to the number read. */
    if (j > 0)
    {
        pstPlatformRatCap->ucRatNum      = (VOS_UINT8)j;
    }

    return;
}




VOS_VOID NAS_MSCC_ReadMmssNvimInfo(VOS_VOID)
{
    /* Read the MSCC Location Info From NVIM */
    NAS_MSCC_ReadLastLocationInfoNvim();

    /* Read the CL System Acquire Cfg NVIM */
    NAS_MSCC_ReadMmssSystemAcquireCfgNvim();
}



VOS_VOID NAS_MSCC_ReadMmssSystemAcquireCfgNvim(VOS_VOID)
{
    NAS_NVIM_MMSS_SYSTEM_ACQUIRE_CFG_STRU                   stNvimMmssSystemAcquireCfg;
    NAS_MSCC_MMSS_SYSACQ_CFG_STRU                          *pstMmssSysAcqCfgInfo = VOS_NULL_PTR;

    PS_MEM_SET(&stNvimMmssSystemAcquireCfg, 0x0, sizeof(NAS_NVIM_MMSS_SYSTEM_ACQUIRE_CFG_STRU));

    /* Get the MMSS Sys acq Cfg Info global variable address */
    pstMmssSysAcqCfgInfo = NAS_MSCC_GetMmssSysAcqCfgInfoAddr();

    if (NV_OK != NV_Read(en_Nv_Item_Mmss_System_Acquire_Cfg,
                     &stNvimMmssSystemAcquireCfg,
                     sizeof(NAS_NVIM_MMSS_SYSTEM_ACQUIRE_CFG_STRU)))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ReadCLSystemAcquireCfgNvim: NV Read Failed!");

        return;
    }

    NAS_MSCC_LogReadNVInfo(en_Nv_Item_Mmss_System_Acquire_Cfg,
                           sizeof(NAS_NVIM_MMSS_SYSTEM_ACQUIRE_CFG_STRU),
                           UEPS_PID_MSCC,
                           (VOS_UINT8 *)&stNvimMmssSystemAcquireCfg);

    /* Log the MMSS System acquire Cfg */
    NAS_MSCC_MNTN_LogNvimMmssCfgInfo(&stNvimMmssSystemAcquireCfg);

    /* Read the Search LTE on HSD Sync Ind Control Flag from NVIM */
    /* Read the NV Value if the NV value is true or False */
    if ((stNvimMmssSystemAcquireCfg.ucReAcqLteOnHrpdSyncIndFlag == VOS_TRUE)
      ||(stNvimMmssSystemAcquireCfg.ucReAcqLteOnHrpdSyncIndFlag == VOS_FALSE))
    {
        pstMmssSysAcqCfgInfo->ucReAcqLteOnHrpdSyncIndFlag = stNvimMmssSystemAcquireCfg.ucReAcqLteOnHrpdSyncIndFlag;

    }
    /* If the NV Value is neither true nor false, then use the default value of true */
    else
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ReadMsccSearchLteOnHrpdSyncIndSwitch: Invalid Value!");

        /* Initialize to FALSE */
        pstMmssSysAcqCfgInfo->ucReAcqLteOnHrpdSyncIndFlag = VOS_FALSE;
    }

    /* Read the CDMA 1x Preferred flag from NVIM */
    /* Read the NV Value if the NV value is true or False */
    if ((stNvimMmssSystemAcquireCfg.ucIs1xLocInfoPrefThanLte == VOS_TRUE)
      ||(stNvimMmssSystemAcquireCfg.ucIs1xLocInfoPrefThanLte == VOS_FALSE))
    {
        pstMmssSysAcqCfgInfo->ucIs1xLocInfoPrefThanLte = stNvimMmssSystemAcquireCfg.ucIs1xLocInfoPrefThanLte;

    }
    /* If the NV Value is neither true nor false, then use the default value of true */
    else
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ReadCdma1xLocationInfoPreferredFlag: Invalid Value!");

        /* Initialize the flag to contain CDMA 1x preferred */
        pstMmssSysAcqCfgInfo->ucIs1xLocInfoPrefThanLte = VOS_TRUE;

    }

    /* Save the Sys Acq timer Cfg from NVIM */
    NAS_MSCC_SaveSysAcqTimerCfg(&(stNvimMmssSystemAcquireCfg.stMmssSysAcqTimerCfg),
                                &(pstMmssSysAcqCfgInfo->stSysAcqTimerCfg));

    return;
}




VOS_VOID NAS_MSCC_ReadLastLocationInfoNvim(VOS_VOID)
{
    NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU                   stNvimMmssLocationInfo;
    NAS_MSCC_MMSS_LOCATION_INFO_STRU                       *pstMmssLocationInfo = VOS_NULL_PTR;

    PS_MEM_SET(&stNvimMmssLocationInfo, 0x0, sizeof(NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU));

    /* Get the MMSS Location Info Global variable address */
    pstMmssLocationInfo = NAS_MSCC_GetMmssLastLocationInfoAddr();

    /* Read the NV Item */
    if (NV_OK != NV_Read(en_Nv_Item_MmssLastLocationInfo,
                         &stNvimMmssLocationInfo,
                         sizeof(NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU)))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ReadLastLocationInfoNvim: Read NV Failed!");

        return;
    }

    NAS_MSCC_LogReadNVInfo(en_Nv_Item_MmssLastLocationInfo,
                           sizeof(NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU),
                           UEPS_PID_MSCC,
                           (VOS_UINT8 *)&stNvimMmssLocationInfo);

    /* Log the MMSS Last Location Info */
    NAS_MSCC_MNTN_LogNvimMmssLastLocInfo(&stNvimMmssLocationInfo);

    /* If the MMSS Location Info valid flag is not TRUE, use the default values written in the previous step */
    if (VOS_TRUE != stNvimMmssLocationInfo.ucIsLocInfoUsedInSwitchOn)

    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ReadLastLocationInfoNvim: Location Info NVIM Flag is not active!");

        return;
    }
    /* Read the NVIM Values if the Valid flag is TRUE */
    else
    {

        if (NAS_NVIM_LC_RAT_COMBINED_GUL == stNvimMmssLocationInfo.enSysAcqMode)
        {
            /* Set the System Acquire Mode as GUL in System Acquire Ctrl global variable and return*/
            pstMmssLocationInfo->enSysAcqMode = NAS_MSCC_LC_RAT_COMBINED_GUL;

            /* Set the location info as valid */
            pstMmssLocationInfo->ucIsLocInfoUsedInSwitchOn = VOS_TRUE;
        }
        /* Update the global values to the NV values if Sys Acq Mode is CL */
        else if (NAS_NVIM_LC_RAT_COMBINED_CL == stNvimMmssLocationInfo.enSysAcqMode)
        {
            /* Set the System Acquire Mode as CL */
            pstMmssLocationInfo->enSysAcqMode = NAS_MSCC_LC_RAT_COMBINED_CL;

            /* Update the global values to the NV values */
            pstMmssLocationInfo->ucCdma1xActiveFlag         = stNvimMmssLocationInfo.ucIs1xLocInfoValid;
            pstMmssLocationInfo->ucLteActiveFlag            = stNvimMmssLocationInfo.ucIsLteLocInfoValid;

            /* Update the 1x location info */
            pstMmssLocationInfo->st1xLocationInfo.ulMcc = stNvimMmssLocationInfo.st1xLocInfo.ulMcc;
            pstMmssLocationInfo->st1xLocationInfo.ulMnc = stNvimMmssLocationInfo.st1xLocInfo.ulMnc;
            pstMmssLocationInfo->st1xLocationInfo.usSid = stNvimMmssLocationInfo.st1xLocInfo.usSid;
            pstMmssLocationInfo->st1xLocationInfo.usNid = stNvimMmssLocationInfo.st1xLocInfo.usNid;

            pstMmssLocationInfo->st1xLocationInfo.en1xPrioClass = stNvimMmssLocationInfo.st1xLocInfo.en1xPrioClass;
            pstMmssLocationInfo->st1xLocationInfo.enAIPrioClass = stNvimMmssLocationInfo.st1xLocInfo.enAIPrioClass;

            /* Update the LTE location info */
            pstMmssLocationInfo->stLteLocationInfo.ulMcc = stNvimMmssLocationInfo.st3gppLocInfo.ulMcc;
            pstMmssLocationInfo->stLteLocationInfo.ulMnc = stNvimMmssLocationInfo.st3gppLocInfo.ulMnc;

            pstMmssLocationInfo->stLteLocationInfo.enPrioClass = stNvimMmssLocationInfo.st3gppLocInfo.enPrioClass;

            /* Set the location info as valid */
            pstMmssLocationInfo->ucIsLocInfoUsedInSwitchOn = VOS_TRUE;

        }
        /* Make error log if System Acquire mode is invalid */
        else
        {
            NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ReadLastLocationInfoNvim: System acquire mode is invalid!");
        }
    }

    return;
}




VOS_VOID NAS_MSCC_WriteMmssLocationInfoNvim(
    NAS_MSCC_MMSS_LOCATION_INFO_STRU                       *pstMmssLocationInfo
)
{
    NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU    stNvimMmssLocationInfo;

    PS_MEM_SET(&stNvimMmssLocationInfo, 0x0, sizeof(NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU));

    /* Construct the NVIM MMSS Location info */
    if (NAS_MSCC_LC_RAT_COMBINED_CL == pstMmssLocationInfo->enSysAcqMode)
    {
        stNvimMmssLocationInfo.enSysAcqMode = NAS_NVIM_LC_RAT_COMBINED_CL;
    }
    else
    {
        stNvimMmssLocationInfo.enSysAcqMode = NAS_NVIM_LC_RAT_COMBINED_GUL;
    }

    stNvimMmssLocationInfo.ucIs1xLocInfoValid  = pstMmssLocationInfo->ucCdma1xActiveFlag;
    stNvimMmssLocationInfo.ucIsLteLocInfoValid = pstMmssLocationInfo->ucLteActiveFlag;

    /* Update the 1x Location Info */
    stNvimMmssLocationInfo.st1xLocInfo.ulMcc   = pstMmssLocationInfo->st1xLocationInfo.ulMcc;
    stNvimMmssLocationInfo.st1xLocInfo.ulMnc   = pstMmssLocationInfo->st1xLocationInfo.ulMnc;
    stNvimMmssLocationInfo.st1xLocInfo.usSid   = pstMmssLocationInfo->st1xLocationInfo.usSid;
    stNvimMmssLocationInfo.st1xLocInfo.usNid   = pstMmssLocationInfo->st1xLocationInfo.usNid;
    stNvimMmssLocationInfo.st1xLocInfo.en1xPrioClass = pstMmssLocationInfo->st1xLocationInfo.en1xPrioClass;
    stNvimMmssLocationInfo.st1xLocInfo.enAIPrioClass = pstMmssLocationInfo->st1xLocationInfo.enAIPrioClass;

    /* Update the LTE Location Info */
    stNvimMmssLocationInfo.st3gppLocInfo.ulMcc  = pstMmssLocationInfo->stLteLocationInfo.ulMcc;
    stNvimMmssLocationInfo.st3gppLocInfo.ulMnc  = pstMmssLocationInfo->stLteLocationInfo.ulMnc;
    stNvimMmssLocationInfo.st3gppLocInfo.enPrioClass = pstMmssLocationInfo->stLteLocationInfo.enPrioClass;

    /* Set the NVIM location info as valid */
    stNvimMmssLocationInfo.ucIsLocInfoUsedInSwitchOn = VOS_TRUE;

    if (NV_OK != NV_Write(en_Nv_Item_MmssLastLocationInfo,
                         &stNvimMmssLocationInfo, sizeof(NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU)))
    {
        /* Make Error log is NV Write Fails */
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_WriteMmssLocationInfoNvim:Write Nvim Failed");

        return;
    }

    return;
}



VOS_UINT8 NAS_MSCC_ReadMlplMsplNvim(
    NAS_MSCC_NVIM_MLPL_MSPL_STRU                            *pstNvimMlplMspl
)
{
    if (NV_OK != NV_Read(en_NV_Item_MLPL_MSPL_FILE, pstNvimMlplMspl,
                                            sizeof(NAS_MSCC_NVIM_MLPL_MSPL_STRU)))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ReadAndParseMlplMsplNvim:ERROR: Read Nvim Failed");

        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_ReadEmcCallBackCfgNvim
 功能描述  : 从NVIM中获取紧急呼回呼配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_ReadEmcCallBackCfgNvim(VOS_VOID)
{
    CNAS_NVIM_1X_CALLBACK_CFG_STRU      stNvCallBackCfg;

    PS_MEM_SET(&stNvCallBackCfg, 0x00, sizeof(CNAS_NVIM_1X_CALLBACK_CFG_STRU));

    if (NV_OK != NV_Read(en_Nv_Item_EMC_CALLBACK_CFG,
                         &stNvCallBackCfg, sizeof(CNAS_NVIM_1X_CALLBACK_CFG_STRU)))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ReadCallBackCfgNvim:Read Nvim Failed");

        /* 读取失败 默认关闭CallBack */
        NAS_MSCC_SetEmcCallBackEnableFlag(VOS_FALSE);

        return;
    }

    NAS_MSCC_SetEmcCallBackEnableFlag(stNvCallBackCfg.ulCallBackEnableFlg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_Read1xServiceClSysAcqStrategyCfgNvim
 功能描述  : 从NVIM中获取1x有服务时CL系统捕获策略配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MSCC_Read1xServiceClSysAcqStrategyCfgNvim(VOS_VOID)
{
    NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_CFG_STRU stNvim1xSrvClSysAcqStrategyCfg;
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU *pst1xSrvClSysAcqPatternCfgPhaseOne;
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU *pst1xSrvClSysAcqPatternCfgPhaseTwo;
    VOS_UINT32                                              ulLength;

    PS_MEM_SET(&stNvim1xSrvClSysAcqStrategyCfg, 0x0, sizeof(NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_CFG_STRU));

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_CFG, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_CFG_STRU))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_Read1xServiceClSysAcqStrategyCfgNvim(): en_NV_Item_Oos_Plmn_Search_Strategy_Cfg length Error");

        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_CFG,
                         &stNvim1xSrvClSysAcqStrategyCfg,
                         sizeof(NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_CFG_STRU)))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_Read1xServiceClSysAcqStrategyCfgNvim: Read NV Failed!");

        return;
    }

    NAS_MSCC_LogReadNVInfo(en_NV_Item_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_CFG,
                           sizeof(NAS_NVIM_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_CFG_STRU),
                           UEPS_PID_MSCC,
                           (VOS_UINT8 *)&stNvim1xSrvClSysAcqStrategyCfg);

    pst1xSrvClSysAcqPatternCfgPhaseOne = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr();
    pst1xSrvClSysAcqPatternCfgPhaseTwo = NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr();

    /* 每个阶段的历史搜和全频搜次数不能同时配置为0 */
    if ((0 == stNvim1xSrvClSysAcqStrategyCfg.stPhaseOnePatternCfg.ucLteFullBandSrchNum)
     && (0 == stNvim1xSrvClSysAcqStrategyCfg.stPhaseOnePatternCfg.ucLteHistorySrchNum))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_Read1xServiceClSysAcqStrategyCfgNvim: invalid phase one pattern setttings for srch num!");

        return;
    }

    if ((0 == stNvim1xSrvClSysAcqStrategyCfg.stPhaseTwoPatternCfg.ucLteFullBandSrchNum)
     && (0 == stNvim1xSrvClSysAcqStrategyCfg.stPhaseTwoPatternCfg.ucLteHistorySrchNum))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_Read1xServiceClSysAcqStrategyCfgNvim: invalid phase two pattern setttings for srch num!");

        return;
    }

    /* sleep timer长度为0则取默认值 */
    if (0 == stNvim1xSrvClSysAcqStrategyCfg.stPhaseOnePatternCfg.usSleepTimeLen)
    {
        pst1xSrvClSysAcqPatternCfgPhaseOne->usSleepTimeLen = TI_NAS_MSCC_DEFAULT_1X_SERVICE_AVAILABLE_TIMER_PHASE_ONE_SLEEP_TIMER_LEN;
    }
    else
    {
        pst1xSrvClSysAcqPatternCfgPhaseOne->usSleepTimeLen = stNvim1xSrvClSysAcqStrategyCfg.stPhaseOnePatternCfg.usSleepTimeLen;
    }

    pst1xSrvClSysAcqPatternCfgPhaseOne->ucLteFullBandSrchNum = stNvim1xSrvClSysAcqStrategyCfg.stPhaseOnePatternCfg.ucLteFullBandSrchNum;
    pst1xSrvClSysAcqPatternCfgPhaseOne->ucLteHistorySrchNum  = stNvim1xSrvClSysAcqStrategyCfg.stPhaseOnePatternCfg.ucLteHistorySrchNum;
    pst1xSrvClSysAcqPatternCfgPhaseOne->usTotalTimeLen    = stNvim1xSrvClSysAcqStrategyCfg.stPhaseOnePatternCfg.usTotalTimeLen;

    /* 2阶段信息 */
    if (0 == stNvim1xSrvClSysAcqStrategyCfg.stPhaseTwoPatternCfg.usSleepTimeLen)
    {
        pst1xSrvClSysAcqPatternCfgPhaseTwo->usSleepTimeLen = TI_NAS_MSCC_DEFAULT_1X_SERVICE_AVAILABLE_TIMER_PHASE_TWO_SLEEP_TIMER_LEN;
    }
    else
    {
        pst1xSrvClSysAcqPatternCfgPhaseTwo->usSleepTimeLen = stNvim1xSrvClSysAcqStrategyCfg.stPhaseTwoPatternCfg.usSleepTimeLen;
    }

    pst1xSrvClSysAcqPatternCfgPhaseTwo->ucLteFullBandSrchNum = stNvim1xSrvClSysAcqStrategyCfg.stPhaseTwoPatternCfg.ucLteFullBandSrchNum;
    pst1xSrvClSysAcqPatternCfgPhaseTwo->ucLteHistorySrchNum  = stNvim1xSrvClSysAcqStrategyCfg.stPhaseTwoPatternCfg.ucLteHistorySrchNum;
    pst1xSrvClSysAcqPatternCfgPhaseTwo->usTotalTimeLen    = stNvim1xSrvClSysAcqStrategyCfg.stPhaseTwoPatternCfg.usTotalTimeLen;

    /* reserve:目前只读取第一和第二阶段的信息,后续的扩展使用 */

    NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo();

    return;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



