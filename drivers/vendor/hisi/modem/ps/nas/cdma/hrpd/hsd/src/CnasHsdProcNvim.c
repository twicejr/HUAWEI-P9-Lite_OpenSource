/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdProcNvim.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年07月08日
  功能描述   : HSD处理NV的读取
  函数列表   :
  修改历史   :

  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasHsdProcNvim.h"
#include  "CnasHsdCtx.h"
#include  "NVIM_Interface.h"
#include  "CnasMntn.h"
#include  "CnasHsdMntn.h"
#include  "NasNvInterface.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_PROC_NVIM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_ReadMruNvim
 功能描述  : 从NV中获取MRU的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月12日
   作    者   : h00300778
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_ReadMruNvim(VOS_VOID)
{
    CNAS_HSD_HRPD_MRU_LIST_STRU        *pstMruList;
    CNAS_NVIM_HRPD_MRU_LIST_STRU        stNvMruList;
    VOS_UINT16                          i;

    pstMruList      = CNAS_HSD_GetMruList();

    PS_MEM_SET(&stNvMruList, 0x0, sizeof(CNAS_NVIM_HRPD_MRU_LIST_STRU));

    if (NV_OK != NV_Read(en_NV_Item_HRPD_MRU_LIST, &stNvMruList, sizeof(CNAS_NVIM_HRPD_MRU_LIST_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_ReadMruNvim:Read Nvim Failed");

        return;
    }

    CNAS_MNTN_LogReadNVInfo(en_NV_Item_HRPD_MRU_LIST,
                            sizeof(CNAS_NVIM_HRPD_MRU_LIST_STRU),
                            UEPS_PID_HSD,
                            (VOS_UINT8 *)&stNvMruList);

    pstMruList->ucCurrMruNum = stNvMruList.ucSysNum;

    for (i = 0; i < stNvMruList.ucSysNum; i++)
    {
        pstMruList->astHrpdSys[i].stFreq.enBandClass = stNvMruList.astSystem[i].usBandClass;
        pstMruList->astHrpdSys[i].stFreq.usChannel   = stNvMruList.astSystem[i].usChannel;

        PS_MEM_CPY(pstMruList->astHrpdSys[i].aucSubnet, stNvMruList.astSystem[i].aucSubnet, sizeof(VOS_UINT8) * CNAS_NVIM_HRPD_SUBNET_LEN);
    }

    CNAS_HSD_LogMruList(pstMruList, ID_CNAS_HSD_MNTN_MRU_LOG_TYPE_READ_NV);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_WriteMruNvim
 功能描述  : 将MRU的内容写入NV中
 输入参数  : pstMruList - 写入MRU的列表
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月12日
   作    者   : h00300778
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_WriteMruNvim(CNAS_HSD_HRPD_MRU_LIST_STRU *pstMruList)
{
    CNAS_NVIM_HRPD_MRU_LIST_STRU        stNvMruList;
    VOS_UINT16                          i;

    PS_MEM_SET(&stNvMruList, 0x0, sizeof(CNAS_NVIM_HRPD_MRU_LIST_STRU));

    stNvMruList.ucSysNum = pstMruList->ucCurrMruNum;

    for (i = 0; i < pstMruList->ucCurrMruNum; i++)
    {
        stNvMruList.astSystem[i].usBandClass        = pstMruList->astHrpdSys[i].stFreq.enBandClass;
        stNvMruList.astSystem[i].usChannel          = pstMruList->astHrpdSys[i].stFreq.usChannel;

        PS_MEM_CPY(stNvMruList.astSystem[i].aucSubnet, pstMruList->astHrpdSys[i].aucSubnet, sizeof(VOS_UINT8) * CNAS_NVIM_HRPD_SUBNET_LEN);
    }

    if (NV_OK != NV_Write(en_NV_Item_HRPD_MRU_LIST, &stNvMruList,  sizeof(CNAS_NVIM_HRPD_MRU_LIST_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_WriteMruNvim:Write Nvim Failed");

    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ReadSearchIntervalNvim
 功能描述  : 从NV中获取扫描间隔相关的内容

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月13日
   作    者   : Z00316370
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_ReadSearchIntervalNvim(VOS_VOID)
{
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU                   *pstOocScheduleInfo = VOS_NULL_PTR;
    CNAS_NVIM_HRPD_OOC_TIMER_SCHEDULE_INFO_STRU        stNvTimerScheduleInfo;
    VOS_UINT16                                         i;

    pstOocScheduleInfo       = CNAS_HSD_GetOocScheduleInfo();

    PS_MEM_SET(&stNvTimerScheduleInfo,
              0,
              sizeof(CNAS_NVIM_HRPD_OOC_TIMER_SCHEDULE_INFO_STRU));

    /* need to confirm en_NV_Item_HRPD_OOC_TIMER_SCHEDULE_INFO */
    if (NV_OK != NV_Read(en_NV_Item_HRPD_OOC_TIMER_SCHEDULE_INFO,
                        &stNvTimerScheduleInfo, sizeof(CNAS_NVIM_HRPD_OOC_TIMER_SCHEDULE_INFO_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_ReadSearchIntervalNvim:Read Nvim Failed");
        pstOocScheduleInfo->stConfigInfo.ucPhaseNum                      = 1;
        pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[0].usTimerLen   = 5;
        pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[0].usTimes      = 5;

        /* 读卡失败时默认mru0搜索长度为0 */
        pstOocScheduleInfo->stConfigInfo.ucMru0SearchTimerLen            = 0;

        return;
    }

    CNAS_MNTN_LogReadNVInfo(en_NV_Item_HRPD_OOC_TIMER_SCHEDULE_INFO,
                            sizeof(CNAS_NVIM_HRPD_OOC_TIMER_SCHEDULE_INFO_STRU),
                            UEPS_PID_HSD,
                            (VOS_UINT8 *)&stNvTimerScheduleInfo);

    stNvTimerScheduleInfo.ucPhaseNum                      = (VOS_UINT8)CNAS_MIN(CNAS_HSD_MAX_OOC_SCHEDULE_PHASE_NUM, stNvTimerScheduleInfo.ucPhaseNum);
    pstOocScheduleInfo->stConfigInfo.ucPhaseNum           = stNvTimerScheduleInfo.ucPhaseNum;
    pstOocScheduleInfo->stConfigInfo.ucMru0SearchTimerLen = stNvTimerScheduleInfo.ucMru0SearchTimerLen;

    for(i = 0; i < pstOocScheduleInfo->stConfigInfo.ucPhaseNum; i++)
    {
        pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[i].usTimes    = stNvTimerScheduleInfo.astOocTimerInfo[i].usTimes;
        pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[i].usTimerLen = stNvTimerScheduleInfo.astOocTimerInfo[i].usTimerLen;
    }

    CNAS_HSD_InitOocCtxInfo();

    CNAS_HSD_LogOocScheduleInfo(&stNvTimerScheduleInfo);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ReadOperLockWhiteSidInfoNvim
 功能描述  : 读取白名单中SID信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年8月1日
   作    者   : x00306642
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_ReadOperLockSysWhiteListInfoNvim(VOS_VOID)
{
    CNAS_NVIM_OPER_LOCK_SYS_WHITE_LIST_STRU                 stOperLockSysWhiteList;
    CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU                 *pstOperLockSysWhiteList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstOperLockSysWhiteList = CNAS_CCB_GetOperLockSysWhiteList();

    PS_MEM_SET(&stOperLockSysWhiteList, 0x0, sizeof(stOperLockSysWhiteList));
    PS_MEM_SET(pstOperLockSysWhiteList, 0x0, sizeof(CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU));

    if (NV_OK != NV_Read(en_NV_Item_OPER_LOCK_SYS_WHITE_LIST_INFO,
                         &stOperLockSysWhiteList, sizeof(stOperLockSysWhiteList)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_ReadOperLockSysWhiteListInfoNvim:Read Nvim Failed");
        return;
    }

    pstOperLockSysWhiteList->ucEnable      = stOperLockSysWhiteList.ucEnable;
    pstOperLockSysWhiteList->usWhiteSysNum = CNAS_MIN(stOperLockSysWhiteList.usWhiteSysNum, CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM);

    for (i = 0; i < pstOperLockSysWhiteList->usWhiteSysNum;i++ )
    {
        pstOperLockSysWhiteList->astSysInfo[i].usStartSid = stOperLockSysWhiteList.astSysInfo[i].usStartSid;
        pstOperLockSysWhiteList->astSysInfo[i].usEndSid   = stOperLockSysWhiteList.astSysInfo[i].usEndSid;
        pstOperLockSysWhiteList->astSysInfo[i].ulMcc      = stOperLockSysWhiteList.astSysInfo[i].ulMcc;
    }

    CNAS_HSD_LogOperLockSysWhiteList(pstOperLockSysWhiteList);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ReadCTCCCustomizeFreqNvim
 功能描述  : 读取中国电信自定义频点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年8月1日
   作    者   : x00306642
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_ReadCTCCCustomizeFreqNvim(VOS_VOID)
{
    CNAS_NVIM_CTCC_CUSTOMIZE_FREQ_LIST_STRU                 stCustFreqList;
    CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU                 *pstCustFreqList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstCustFreqList = CNAS_CCB_GetCTCCCustomizeFreqList();

    PS_MEM_SET(&stCustFreqList, 0x0, sizeof(stCustFreqList));
    PS_MEM_SET(pstCustFreqList, 0x0, sizeof(CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU));

    if (NV_OK != NV_Read(en_NV_Item_CTCC_CUSTOMIZE_FREQ_INFO,
                         &stCustFreqList, sizeof(stCustFreqList)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_ReadCTCCCustomizeFreqNvim:Read Nvim Failed");
        return;
    }

    pstCustFreqList->ucEnableFlg = stCustFreqList.ucEnableFlg;
    pstCustFreqList->usFreqNum   = CNAS_MIN(stCustFreqList.usFreqNum, CNAS_CCB_MAX_FREQ_NUM);

    for (i = 0; i < pstCustFreqList->usFreqNum;i++ )
    {
        pstCustFreqList->astFreqList[i].usChannel   = stCustFreqList.astFreqList[i].usChannel;
    }

    CNAS_HSD_LogCTCCCustomizeFreqList(pstCustFreqList);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ReadPrlNvim
 功能描述  : 从NV中获取PRL的内容, 并解析PRL内容

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年08月18日
   作    者   : x00306642
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_ReadPrlNvim(VOS_VOID)
{
    CNAS_NVIM_1X_EVDO_PRL_LIST_STRU                        *pPrlData = VOS_NULL_PTR;
    VOS_UINT32                                              ulRslt;

    /* 读取PRL前，为PRL码流分配临时内存空间 */
    pPrlData = (CNAS_NVIM_1X_EVDO_PRL_LIST_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD, sizeof(CNAS_NVIM_1X_EVDO_PRL_LIST_STRU));

    if (VOS_NULL_PTR != pPrlData)
    {
        PS_MEM_SET(pPrlData, 0, sizeof(CNAS_NVIM_1X_EVDO_PRL_LIST_STRU));

        if (NV_OK != NV_Read(en_NV_Item_PRL_LIST, pPrlData, sizeof(CNAS_NVIM_1X_EVDO_PRL_LIST_STRU)))
        {
            CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_ReadPrlNvim: Read Nvim Failed");

            /* 释放内存 */
            PS_MEM_FREE(UEPS_PID_HSD, pPrlData);

            return;
        }

        /* 默认尝试用EPRL方式解析PRL码流 */
        ulRslt = CNAS_PRL_ProcPrlInfo(&(pPrlData->ucPrlData[0]), sizeof(CNAS_NVIM_1X_EVDO_PRL_LIST_STRU), CNAS_PRL_SSPR_P_REV_3);

        if (VOS_TRUE == ulRslt)
        {
            CNAS_HSD_LogPrlSourceType(CNAS_HSD_PRL_TYPE_NVRAM);
        }
        else
        {
            CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_ReadPrlNvim: parse Nvim PRL Failed");
        }

        /* 释放内存 */
        PS_MEM_FREE(UEPS_PID_HSD, pPrlData);
    }
    else
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_ReadPrlNvim: Malloc Mem Failed");
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_ReadHrpdSupportBandClassMaskNvim
 功能描述  : 从NV中获取do支持的Band Class
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年8月14日
   作    者   : x00306642
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_ReadHrpdSupportBandClassMaskNvim(VOS_VOID)
 {
    VOS_UINT32                                            *pulHrpdSupportBandClassMask = VOS_NULL_PTR;
    CNAS_NVIM_HRPD_SUPPORT_BANDCLASS_MASK_STRU             stHrpdSupportBandClassMask;

    pulHrpdSupportBandClassMask = &(CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ulUeSupportedBand);

    PS_MEM_SET(&stHrpdSupportBandClassMask, 0x0, sizeof(stHrpdSupportBandClassMask));

    if (NV_OK != NV_Read(en_NV_Item_CDMA_SUPPORT_BANDCLASS_MASK,
                         &stHrpdSupportBandClassMask, sizeof(stHrpdSupportBandClassMask)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_ReadHprdSupportBandClassMaskNvim:Read Nvim Failed");

        return;
    }

    *pulHrpdSupportBandClassMask = stHrpdSupportBandClassMask.ulSupportBandclassMask;

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_ReadTestConfigNvim
 功能描述  : 从NV中获取TestConfig的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月20日
   作    者   : z00316370
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_ReadTestConfigNvim(VOS_VOID)
{
    CNAS_HSD_TEST_CONFIG_STRU          *pstTestConfig = VOS_NULL_PTR;
    CNAS_NVIM_TEST_CONFIG_STRU          stTestConfig;
    CNAS_NVIM_NO_CARD_MODE_CFG_STRU     stNoCardModeCfg;


    pstTestConfig      = CNAS_HSD_GetTestConfig();

    PS_MEM_SET(&stTestConfig, 0x0, sizeof(stTestConfig));

    if (NV_OK != NV_Read(en_NV_Item_TEST_CONFIG,
                         &stTestConfig, sizeof(stTestConfig)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_ReadTestConfigNvim:Read Nvim Failed");

        pstTestConfig->ucReadNvPrlDirectly  = VOS_FALSE;
        pstTestConfig->ucReadDefaultPrl     = VOS_FALSE;
    }
    else
    {

        CNAS_MNTN_LogReadNVInfo(en_NV_Item_TEST_CONFIG,
                                sizeof(CNAS_NVIM_TEST_CONFIG_STRU),
                                UEPS_PID_HSD,
                                (VOS_UINT8 *)&stTestConfig);

        pstTestConfig->ucReadNvPrlDirectly  = stTestConfig.ucReadNvPrlDirectly;
        pstTestConfig->ucReadDefaultPrl     = stTestConfig.ucReadDefaultPrl;
    }

    /* 读取无卡模式控制NV项 */
    PS_MEM_SET(&stNoCardModeCfg, 0x0, sizeof(stNoCardModeCfg));

    if (NV_OK != NV_Read(en_NV_Item_NO_CARD_MODE_CFG,
                         &stNoCardModeCfg, sizeof(stNoCardModeCfg)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_ReadNoCardModeCfgNvim: Read Nvim Failed");

        pstTestConfig->ucNoCardModeCfgFlg = VOS_FALSE;
    }
    else
    {
        CNAS_MNTN_LogReadNVInfo(en_NV_Item_NO_CARD_MODE_CFG,
                                sizeof(CNAS_NVIM_NO_CARD_MODE_CFG_STRU),
                                UEPS_PID_HSD,
                                (VOS_UINT8 *)&stNoCardModeCfg);

        pstTestConfig->ucNoCardModeCfgFlg = (VOS_UINT8)stNoCardModeCfg.ulEnableFlag;
    }

    return;
}

/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




