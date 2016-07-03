

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasCcb.h"
#include  "CnasXregCtx.h"
#include  "CnasXregMain.h"
#include  "CnasXregFsmMainTbl.h"
#include  "CnasTimerMgmt.h"
#include  "CnasMntn.h"
#include  "CnasXregProcess.h"
#include  "CnasXregTimer.h"
#include  "CnasXregListProc.h"
#include  "csn1clib.h"
#include  "CnasXregSndCas.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include  "UserDefinedDataTypes_cs0005.h"
#endif
#include  "NVIM_Interface.h"

#include "NasNvInterface.h"

#include "CnasXregMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_PROCESS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
CNAS_XREG_REGSTATE_STRU                 g_stCnasXregStateInfo;

CNAS_XREG_SYS_MSG_CONTENT_STRU          g_stCnasXregSysMsgCont;

CNAS_XREG_HOME_INFO_STRU                g_stCnasXregHomeInfo;

NAS_OM_REPORT_ACTION_ENUM_UINT8         g_enCnasXregRptAction = NAS_OM_REPORT_STOP;

/* 57 = 85-29+1 */
VOS_UINT32  g_aulCnasXregCountMax[] =
{
    152, 181, 215, 256, 304, 362, 430, 512,
    608, 724, 861, 1024, 1217, 1448, 1722, 2048,
    2435, 2896, 3444, 4096, 4870, 5792, 6888, 8192,
    9741, 11585, 13777, 16384, 19483, 23170, 27554, 32768,
    38967, 46340, 55108, 65536, 77935, 92681, 110217, 131072,
    155871, 185363, 220435, 262144, 311743, 370727, 440871, 524288,
    623487, 741455, 881743, 1048576, 1246974, 1482910, 1763487, 2097152,
    2493948
};

CNAS_XREG_DBG_STAT_STRU                 g_stCnasXregDbgStat = {0};

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/


CNAS_XREG_REGSTATE_STRU* CNAS_XREG_GetRegStateAddr(VOS_VOID)
{
    return &g_stCnasXregStateInfo;
}


CNAS_XREG_SYS_MSG_CONTENT_STRU* CNAS_XREG_GetSysMsgAddr(VOS_VOID)
{
    return &g_stCnasXregSysMsgCont;
}



VOS_UINT32 CNAS_XREG_SquareRoot(VOS_UINT32 ulNumber)
{
    VOS_UINT32      i;
    float           x;
    float           y;
    float           f;
    VOS_UINT32      ulResult;

    f   = 1.5F;

    x   = ulNumber * 0.5F;

    y   = ulNumber;

    i   = * ( VOS_UINT32 * ) &y;

    i   = 0x5f375a86 - ( i >> 1 );         /*魔术数*/

    y   = * ( float * ) &i;

    y   = y * ( f - ( x * y * y ) );        /*迭代1    1/sqrt(number)  */

    y   = y * ( f - ( x * y * y ) );        /*迭代2    1/sqrt(number)  */

    y   = y * ( f - ( x * y * y ) );        /*迭代3    1/sqrt(number)  */

    ulResult = (VOS_UINT32)(ulNumber * y);

    return ulResult;
}



VOS_UINT32 CNAS_XREG_CalcDistance(
    VOS_INT32                           lOldLat,
    VOS_INT32                           lOldLong,
    VOS_INT32                           lNewLat,
    VOS_INT32                           lNewLong
)
{
    VOS_UINT32                          ulDeltaLat;
    VOS_UINT32                          ulDist;
    VOS_UINT32                          ulDeltaLong;
    VOS_DOUBLE                          dDeltaLong;

    if (lNewLat > lOldLat)
    {
        ulDeltaLat = (VOS_UINT32)(lNewLat - lOldLat);
    }
    else
    {
        ulDeltaLat = (VOS_UINT32)(lOldLat - lNewLat);
    }

    if ( ulDeltaLat > CNAS_XREG_DELTAVALUE_MAX )    /*判断最大值，超过范围无意义*/
    {
        return CNAS_XREG_DELTADIST_MAX;
    }

    if (lNewLong > lOldLong)
    {
        ulDeltaLong = (VOS_UINT32)(lNewLong - lOldLong);
    }
    else
    {
        ulDeltaLong = (VOS_UINT32)(lOldLong - lNewLong);
    }

    if (( ulDeltaLong > CNAS_XREG_180DEGREE )&&( ulDeltaLong < CNAS_XREG_360DEGREE ))
    {
        ulDeltaLong = CNAS_XREG_360DEGREE - ulDeltaLong;
    }
    else if (ulDeltaLong > CNAS_XREG_360DEGREE)
    {
        ulDeltaLong = ulDeltaLong - CNAS_XREG_360DEGREE;
    }
    else
    {
        ulDeltaLong = ulDeltaLong;
    }

    dDeltaLong = (VOS_DOUBLE)ulDeltaLong * cos((VOS_DOUBLE)(((3.14F)/180*lOldLat)/14400));

    ulDeltaLong = (VOS_UINT32)dDeltaLong;

    if ( ulDeltaLong > CNAS_XREG_DELTAVALUE_MAX )    /*判断最大值，超过范围无意义*/
    {
        return CNAS_XREG_DELTADIST_MAX;
    }

    ulDist =  CNAS_XREG_SquareRoot(( ulDeltaLat * ulDeltaLat ) + ( ulDeltaLong * ulDeltaLong ));

    ulDist = ulDist >> 4;

    return ulDist;
}


VOS_VOID CNAS_XREG_StartTime(VOS_UINT32 ulTimerId, VOS_UINT32 ulTimerLen)
{
    CNAS_TIMER_INFO_STRU                stTimerInfo;

    stTimerInfo.ulParam             = VOS_NULL;
    stTimerInfo.ulTimerId           = ulTimerId;
    stTimerInfo.ulTimerLen          = ulTimerLen;
    stTimerInfo.ulTimerPrecision    = VOS_TIMER_PRECISION_0;

    CNAS_RestartTimer(UEPS_PID_XREG, &stTimerInfo);

    return;
}


VOS_VOID CNAS_XREG_SetRegEnabled(VOS_UINT16 usSid,
                                              VOS_UINT16 usNid,
                                              VOS_UINT8  ucHomeReg,
                                              VOS_UINT8  ucSidRoamReg,
                                              VOS_UINT8  ucNidRoamReg)
{
    CNAS_XREG_ROAMING_STATE_UINT8       enRoamingState;
    VOS_UINT32                          ulIndex;
    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU *pstHomeSidNids;

    g_stCnasXregStateInfo.enRegEnabledFlag = CNAS_XREG_VAR_NO;

    enRoamingState = CNAS_XREG_SID_ROAMING;

    pstHomeSidNids = CNAS_CCB_GetHomeSidNidList();

    for (ulIndex = 0; ulIndex < pstHomeSidNids->ucSysNum; ulIndex++)
    {
        /* 找到相同的SID值 */
        if (usSid == pstHomeSidNids->astHomeSidNid[ulIndex].usSid)
        {
            enRoamingState = CNAS_XREG_NID_ROAMING;

            /* 找到相同的NID值 */
            if ((usNid == pstHomeSidNids->astHomeSidNid[ulIndex].usNid)
                || (CNAS_XREG_HOME_NID == pstHomeSidNids->astHomeSidNid[ulIndex].usNid))
            {
                enRoamingState = CNAS_XREG_NO_ROAMING;

                break;
            }
        }
    }

    /* The mobile station is not roaming, and both HOME_REGs and MOB_TERM_HOMEp are equal to '1'*/
    if (CNAS_XREG_NO_ROAMING == enRoamingState)
    {
        CNAS_CCB_SetMtCallInRoamingAccFlg(g_stCnasXregHomeInfo.ucMobTermHome);

        if ((VOS_TRUE == ucHomeReg)&&(VOS_TRUE == g_stCnasXregHomeInfo.ucMobTermHome))
        {
            g_stCnasXregStateInfo.enRegEnabledFlag = CNAS_XREG_VAR_YES;
        }

        return;
    }

    /* The mobile station is a foreign SID roamer and both FOR_SID_REGs and
       MOB_TERM_FOR_SIDp are equal to '1'; otherwise the mobile station shall set REG_ENABLEDs to NO. */
    if (CNAS_XREG_SID_ROAMING == enRoamingState)
    {
        CNAS_CCB_SetMtCallInRoamingAccFlg(g_stCnasXregHomeInfo.ucMobTermForSid);

        if ((VOS_TRUE == ucSidRoamReg)&&(VOS_TRUE == g_stCnasXregHomeInfo.ucMobTermForSid))
        {
            g_stCnasXregStateInfo.enRegEnabledFlag = CNAS_XREG_VAR_YES;
        }

        return;
    }

    /* The mobile station is a foreign NID roamer and both FOR_NID_REGs and MOB_TERM_FOR_NIDp are equal to '1' */
    if (CNAS_XREG_NID_ROAMING == enRoamingState)
    {
        CNAS_CCB_SetMtCallInRoamingAccFlg(g_stCnasXregHomeInfo.ucMobTermForNid);

        if ((VOS_TRUE == ucNidRoamReg)&&(VOS_TRUE == g_stCnasXregHomeInfo.ucMobTermForNid))
        {
            g_stCnasXregStateInfo.enRegEnabledFlag = CNAS_XREG_VAR_YES;
        }
    }

    return;
}


VOS_VOID CNAS_XREG_RegSuccProc(VOS_VOID)
{


    VOS_UINT32                          ulTimerLen;
    XSD_XREG_SYS_INFO_STRU             *pstSysInfo;

    /* 假如开机定时器正在启动，则停止 */
    if (CNAS_XREG_TIMER_RUNNING == g_stCnasXregStateInfo.enT57MState)
    {
        CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_T57M, 0);

        g_stCnasXregStateInfo.enT57MState = CNAS_XREG_TIMER_EXPIRED;    /*按照超时处理，这样关机会发起注册*/
    }

    /* 将初始COUNT值清0 */
    g_stCnasXregStateInfo.ulRegInitCount = 0;

    ulTimerLen = (g_stCnasXregStateInfo.ulRegCountMax - g_stCnasXregStateInfo.ulRegInitCount)
                            *CNAS_XREG_MS_PER_COUNT;

    if ((VOS_NULL != ulTimerLen) && (CNAS_XREG_TIMER_NULL != g_stCnasXregStateInfo.enRegTimerState))
    {
        if (CNAS_XREG_TIMER_MAX_LEN < ulTimerLen)
        {
            g_stCnasXregStateInfo.ulRemainderTimerLen = ulTimerLen - CNAS_XREG_TIMER_MAX_LEN;

            /* 重启周期注册定时器 */
            CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_PERIOD_REG, CNAS_XREG_TIMER_MAX_LEN);
        }
        else
        {
            g_stCnasXregStateInfo.ulRemainderTimerLen = 0;

            /* 重启周期注册定时器 */
            CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_PERIOD_REG, ulTimerLen);
        }

        g_stCnasXregStateInfo.enRegTimerState = CNAS_XREG_TIMER_RUNNING;
    }

    /* 指示已经成功注册上 */
    g_stCnasXregStateInfo.enRegisterFlag = CNAS_XREG_VAR_YES;

    if (CNAS_XREG_SYSMSG_NOT_CURRENT == g_stCnasXregSysMsgCont.enAvailable)
    {
        CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_RegSuccProc: SysMsg is not current.");
    }

    /* 获取当前保存的系统消息 */
    pstSysInfo = &(g_stCnasXregSysMsgCont.stSysInfo);

    /* 删除超时节点 */
    CNAS_XREG_RefreshLists();

    /* 删除LIST中BandClass or BlockSystem不同的节点 */
    CNAS_XREG_DelNodesByBandBlkSys(pstSysInfo);

    /* 更新ZONE_LIST列表和SID_NID_LIST列表 */
    CNAS_XREG_UpdateZoneList(pstSysInfo, pstSysInfo->usSid, pstSysInfo->usNid, pstSysInfo->stRegInfo.usRegZone, pstSysInfo->stRegInfo.ucZoneTimer);
    CNAS_XREG_UpdateSidNidList(pstSysInfo, pstSysInfo->usSid, pstSysInfo->usNid, pstSysInfo->stRegInfo.ucZoneTimer);

    /* 根据系统消息中的ucRegZoneNum，将ZONE_LIST中的多余项删除 */
    CNAS_XREG_TotalZones(pstSysInfo->stRegInfo.ucRegZoneNum);

    /* 假如ucMultiSidFlg为0 */
    if (0 == pstSysInfo->stRegInfo.ucMultiSidFlg)
    {
        CNAS_XREG_DelMultSids();
    }

    /* 假如ucMultiNidFlg为0 */
    if (0 == pstSysInfo->stRegInfo.ucMultiNidFlg)
    {
        CNAS_XREG_DelMultNids();
    }

    /* 保存位置参数 */
    g_stCnasXregStateInfo.stDistInfo.lBaseLast = pstSysInfo->stBaseStationInfo.lBaseLatitude;
    g_stCnasXregStateInfo.stDistInfo.lBaseLong = pstSysInfo->stBaseStationInfo.lBaseLongitude;
    g_stCnasXregStateInfo.stDistInfo.ulDistThrd = pstSysInfo->stRegInfo.usRegDistance;
    g_stCnasXregStateInfo.enDistRegFlag = CNAS_XREG_VAR_NO;

    /* 保存BandClass和BlockOrSys */
    g_stCnasXregStateInfo.enBlkSys    = CNAS_XREG_BandFreqToBlkSys(pstSysInfo->usBandClass, pstSysInfo->usFreq);
    g_stCnasXregStateInfo.usBandClass = pstSysInfo->usBandClass;

    /* 注册成功后将版本变化标记清空 */
    g_stCnasXregStateInfo.enIsVerChange  = CNAS_XREG_VAR_NO;

    /* 注册成功后将TCH态切换标记清空 */
    g_stCnasXregStateInfo.enIsTchHandoff = CNAS_XREG_VAR_NO;

    /* 注册成功则更新保存的UE参数 */
    (VOS_VOID)CNAS_XREG_SciParaCheck();
    (VOS_VOID)CNAS_XREG_TermParaCheck();

    /* 将当前的SIDNIDLIST和ZONELIST可维可测输出 */
    CNAS_XREG_ZoneListMntn();
    CNAS_XREG_SidNidListMntn();
    CNAS_XREG_SndOmRegListReportInd();

    return;
}


VOS_VOID CNAS_XREG_RegFailProc(VOS_VOID)
{
    

    XSD_XREG_SYS_INFO_STRU             *pstSysInfo;

    if (CNAS_XREG_SYSMSG_NOT_CURRENT == g_stCnasXregSysMsgCont.enAvailable)
    {
        CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_RegFailProc: SysMsg is not current.");
    }

    /* 获取当前保存的系统消息 */
    pstSysInfo = &(g_stCnasXregSysMsgCont.stSysInfo);

    CNAS_XREG_RefreshLists();

    /* 删除LIST中BandClass or BlockSystem不同的节点 */
    CNAS_XREG_DelNodesByBandBlkSys(pstSysInfo);

    /* 将当前ZONE节点放入ZONE_LIST中 */
    CNAS_XREG_AddCurrZoneNode(pstSysInfo->usSid, pstSysInfo->usNid,
                                pstSysInfo->stRegInfo.usRegZone, pstSysInfo->stRegInfo.ucZoneTimer);

    /* 将当前SIDNID节点放入SIDNID_LIST中 */
    CNAS_XREG_AddCurrSidNidNode(pstSysInfo->usSid, pstSysInfo->usNid, pstSysInfo->stRegInfo.ucZoneTimer);

    /* 将当前的SIDNIDLIST和ZONELIST可维可测输出 */
    CNAS_XREG_ZoneListMntn();
    CNAS_XREG_SidNidListMntn();
    CNAS_XREG_SndOmRegListReportInd();

    return;
}


VOS_VOID CNAS_XREG_MobTermSet(VOS_UINT16 usSid, VOS_UINT16 usNid)
{
    CNAS_XREG_ROAMING_STATE_UINT8       enRoamingState;
    VOS_UINT32                          ulIndex;
    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU *pstHomeSidNids;

    enRoamingState = CNAS_XREG_SID_ROAMING;

    pstHomeSidNids = CNAS_CCB_GetHomeSidNidList();

    for (ulIndex = 0; ulIndex < pstHomeSidNids->ucSysNum; ulIndex++)
    {
        if (usSid == pstHomeSidNids->astHomeSidNid[ulIndex].usSid)
        {
            enRoamingState = CNAS_XREG_NID_ROAMING;

            if ((usNid == pstHomeSidNids->astHomeSidNid[ulIndex].usNid)
                || (CNAS_XREG_HOME_NID == pstHomeSidNids->astHomeSidNid[ulIndex].usNid))
            {
                enRoamingState = CNAS_XREG_NO_ROAMING;

                break;
            }
        }
    }

    if (CNAS_XREG_NO_ROAMING == enRoamingState)
    {
        CNAS_CCB_SetMtCallInRoamingAccFlg(g_stCnasXregHomeInfo.ucMobTermHome);

        return;
    }

    if (CNAS_XREG_SID_ROAMING == enRoamingState)
    {
        CNAS_CCB_SetMtCallInRoamingAccFlg(g_stCnasXregHomeInfo.ucMobTermForSid);

        return;
    }

    if (CNAS_XREG_NID_ROAMING == enRoamingState)
    {
        CNAS_CCB_SetMtCallInRoamingAccFlg(g_stCnasXregHomeInfo.ucMobTermForNid);
    }

    return;
}



VOS_VOID CNAS_XREG_MSRMProc(CNAS_XREG_MSRM_STRU *pstMsrm)
{

    XSD_XREG_SYS_INFO_STRU             *pstSysInfo;

    /* 记录注册结果 */
    CNAS_XREG_RecordRegRslt(CAS_CNAS_1X_REGISTRATION_TYPE_BUTT, VOS_OK);

    /* 刷新ZONE&SIDNID列表 */
    CNAS_XREG_RefreshLists();

    if (CNAS_XREG_SYSMSG_NOT_CURRENT == g_stCnasXregSysMsgCont.enAvailable)
    {
        CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_RegSuccProc: SysMsg is not current.");
    }

    /* 获取当前保存的系统消息 */
    pstSysInfo = &(g_stCnasXregSysMsgCont.stSysInfo);

    /* 更新ZONE_LIST列表和SID_NID_LIST列表 */
    CNAS_XREG_UpdateZoneList(pstSysInfo, pstMsrm->usSid, pstMsrm->usNid, pstMsrm->usRegZone, pstMsrm->ucZoneTimer);
    CNAS_XREG_UpdateSidNidList(pstSysInfo, pstMsrm->usSid, pstMsrm->usNid, pstMsrm->ucZoneTimer);

    /* 设置ZONE列表的最大个数 */
    CNAS_XREG_TotalZones(pstMsrm->ucTotalZones);

    /* 假如ucMultSids为0 */
    if (0 == pstMsrm->ucMultSids)
    {
        CNAS_XREG_DelMultSids();
    }

    /* 假如ucMultNids为0 */
    if (0 == pstMsrm->ucMultNids)
    {
        CNAS_XREG_DelMultNids();
    }

    /* 保存位置参数 */
    g_stCnasXregStateInfo.stDistInfo.lBaseLast  = pstMsrm->lBaseLat;
    g_stCnasXregStateInfo.stDistInfo.lBaseLong  = pstMsrm->lBaseLong;
    g_stCnasXregStateInfo.stDistInfo.ulDistThrd = pstMsrm->usRegDist;
    g_stCnasXregStateInfo.enDistRegFlag = CNAS_XREG_VAR_NO;

    /* 保存BandClass和BlockOrSys */
    g_stCnasXregStateInfo.enBlkSys    = CNAS_XREG_BandFreqToBlkSys(pstSysInfo->usBandClass, pstSysInfo->usFreq);
    g_stCnasXregStateInfo.usBandClass = pstSysInfo->usBandClass;

    /* 设置MOB_TERMs */
    CNAS_XREG_MobTermSet(pstMsrm->usSid, pstMsrm->usNid);

    /* 注册成功后将版本变化标记清空 */
    g_stCnasXregStateInfo.enIsVerChange  = CNAS_XREG_VAR_NO;

    /* 注册成功后将TCH态切换标记清空 */
    g_stCnasXregStateInfo.enIsTchHandoff = CNAS_XREG_VAR_NO;

    /* 保存和上报可维可测注册类型 */
    CNAS_XREG_GetRegStateAddr()->enRegTypeMntn = NAS_OM_CDMA_TRAFFIC_CHANNEL_REGISTRATION;
    CNAS_XREG_SndOmRegTypeReportInd(NAS_OM_CDMA_TRAFFIC_CHANNEL_REGISTRATION);

    /* 将当前的SIDNIDLIST和ZONELIST可维可测输出 */
    CNAS_XREG_ZoneListMntn();
    CNAS_XREG_SidNidListMntn();
    CNAS_XREG_SndOmRegListReportInd();

    return;
}


VOS_UINT32 CNAS_XREG_ORDMCheck(CNAS_XREG_ORDM_STRU *pstOrdm)
{
    /* Registration Request Order */
    if ((CNAS_XREG_REG_ORD == pstOrdm->ucOrder) && (CNAS_XREG_REG_REQ == pstOrdm->ucOrdq))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}


VOS_UINT32 CNAS_XREG_GetCountMax(VOS_UINT8 ucRegPeriod)
{
    if ((CNAS_XREG_MIN_REG_PRD <= ucRegPeriod) && (CNAS_XREG_MAX_REG_PRD >= ucRegPeriod))
    {
        return g_aulCnasXregCountMax[ucRegPeriod - CNAS_XREG_MIN_REG_PRD];
    }

    return 0;
}



VOS_VOID CNAS_XREG_RegTimerStart(XSD_XREG_SYS_INFO_STRU *pstSysInfo,
                                             CNAS_XREG_REGSTATE_STRU  *pstSysState)
{
    VOS_UINT32                          ulCountMax;
    VOS_UINT32                          ulTimerLen;

    /* 定时器已经启动则退出 */
    if ((CNAS_XREG_TIMER_NULL != pstSysState->enRegTimerState)
        || (CNAS_XREG_VAR_NO == pstSysState->enRegEnabledFlag))
    {
        return;
    }

    ulCountMax = CNAS_XREG_GetCountMax(pstSysInfo->stRegInfo.ucRegPeriod);

    /* 参数不正确 */
    if (0 == ulCountMax)
    {
        return;
    }

    pstSysState->ulRegCountMax = ulCountMax;

    /* 取随机值 */
    pstSysState->ulRegInitCount = VOS_Rand(ulCountMax - 1);

    ulTimerLen = (pstSysState->ulRegCountMax - pstSysState->ulRegInitCount)*CNAS_XREG_MS_PER_COUNT;

    if (CNAS_XREG_TIMER_MAX_LEN < ulTimerLen)
    {
        pstSysState->ulRemainderTimerLen = ulTimerLen - CNAS_XREG_TIMER_MAX_LEN;

        /* 启动注册定时器 */
        CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_PERIOD_REG, CNAS_XREG_TIMER_MAX_LEN);
    }
    else
    {
        pstSysState->ulRemainderTimerLen = 0;

        /* 启动注册定时器 */
        CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_PERIOD_REG, ulTimerLen);
    }

    pstSysState->enRegTimerState = CNAS_XREG_TIMER_RUNNING;

    return;
}


VOS_VOID CNAS_XREG_RegTimerStop(VOS_VOID)
{
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_PERIOD_REG, 0);

    g_stCnasXregStateInfo.enRegTimerState = CNAS_XREG_TIMER_NULL;

    return;
}


VOS_VOID CNAS_XREG_RegTimerRefresh(VOS_UINT8 ucRegPeriod)
{
    VOS_UINT32                          ulCountMax;
    VOS_UINT32                          ulRemainLen;
    VOS_INT32                           lTimerLen;

    /* 假如值为0则关闭注册定时器 */
    if (0 == ucRegPeriod)
    {
        CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_PERIOD_REG, 0);

        g_stCnasXregStateInfo.enRegTimerState = CNAS_XREG_TIMER_NULL;

        return;
    }

    /* 更新MAX值 */
    ulCountMax = CNAS_XREG_GetCountMax(ucRegPeriod);

    if ((0 != ulCountMax) && (ulCountMax != g_stCnasXregStateInfo.ulRegCountMax))
    {
        /* 判断定时器注册功能是否启动 */
        if (CNAS_XREG_TIMER_NULL == g_stCnasXregStateInfo.enRegTimerState)
        {
            g_stCnasXregStateInfo.ulRegCountMax = ulCountMax;

            return;
        }

        /* 获得定时器剩余长度 */
        ulRemainLen = CNAS_GetSpecifiedTimerRemainLen(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_PERIOD_REG, 0);

        ulRemainLen += g_stCnasXregStateInfo.ulRemainderTimerLen;

        if (0 != ulRemainLen)
        {
            lTimerLen = (VOS_INT32)(ulRemainLen + (ulCountMax - g_stCnasXregStateInfo.ulRegCountMax)*CNAS_XREG_MS_PER_COUNT);

            if (0 < lTimerLen)
            {
                if (CNAS_XREG_TIMER_MAX_LEN < lTimerLen)
                {
                    g_stCnasXregStateInfo.ulRemainderTimerLen = (VOS_UINT32)(lTimerLen - CNAS_XREG_TIMER_MAX_LEN);

                    /* 启动注册定时器 */
                    CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_PERIOD_REG, CNAS_XREG_TIMER_MAX_LEN);
                }
                else
                {
                    g_stCnasXregStateInfo.ulRemainderTimerLen = 0;

                    /* 启动注册定时器 */
                    CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_PERIOD_REG, (VOS_UINT32)lTimerLen);
                }

                g_stCnasXregStateInfo.enRegTimerState = CNAS_XREG_TIMER_RUNNING;
            }
            else
            {
                CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_PERIOD_REG, 0);

                /* 定时器已经超时 */
                g_stCnasXregStateInfo.enRegTimerState = CNAS_XREG_TIMER_EXPIRED;
            }
        }

        g_stCnasXregStateInfo.ulRegCountMax = ulCountMax;
    }

    return;
}


VOS_BOOL CNAS_XREG_PowerUpCheck(CNAS_XREG_SYS_MSG_CONTENT_STRU   *pstSysInfoSave,
                                                CNAS_XREG_REGSTATE_STRU         *pstSysState)
{
    /* POWER_UP_REG  is equal to 1; and
       REGISTERED  is equal to NO, and
       REG_ENABLED  is equal to YES. */
    if ((VOS_TRUE               == pstSysInfoSave->stSysInfo.stRegInfo.ucPowerUpReg)
        &&(CNAS_XREG_VAR_NO     == pstSysState->enRegisterFlag)
        &&(CNAS_XREG_VAR_YES    == pstSysState->enRegEnabledFlag))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_BOOL CNAS_XREG_PowerUpParaCheck(CNAS_XREG_SYS_MSG_CONTENT_STRU   *pstSysInfoSave,
                                                    CNAS_XREG_REGSTATE_STRU          *pstSysState)
{
    CNAS_XREG_BLKSYS_ENUM_UINT8         enBlkSys;

    enBlkSys = CNAS_XREG_BandFreqToBlkSys(pstSysInfoSave->stSysInfo.usBandClass, pstSysInfoSave->stSysInfo.usFreq);

    if ((VOS_TRUE                    == pstSysInfoSave->stSysInfo.stRegInfo.ucPowerUpReg)
        &&(CNAS_XREG_VAR_YES         == pstSysState->enRegEnabledFlag)
        &&(CNAS_XREG_VAR_YES         == pstSysState->enRegisterFlag)
        &&((pstSysState->usBandClass != pstSysInfoSave->stSysInfo.usBandClass)
            || (enBlkSys != pstSysState->enBlkSys)))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_BOOL CNAS_XREG_TimerBaseCheck(CNAS_XREG_REGSTATE_STRU  *pstSysState)
{
    /*PARAMETER_REG  is equal to 1; and
       There is no entry of SID_NID_LIST  whose SID and NID fields match the stored SID and NID . */
    if ((CNAS_XREG_VAR_YES            == pstSysState->enRegEnabledFlag)
        &&(CNAS_XREG_TIMER_EXPIRED      == pstSysState->enRegTimerState))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_BOOL CNAS_XREG_PowerDownCheck(VOS_VOID)
{

    /*REG_ENABLED  equals YES; and

    POWER_DOWN_REG  equals 1; and

    There is an entry of SID_NID_LIST  for which the SID and NID fields are equal to SID  and NID ; and

    The power-up/initialization timer (see 2.6.5.1.1) is disabled or has expired. */
    if ((VOS_NULL_PTR != CNAS_XREG_FindSidNidNode(g_stCnasXregSysMsgCont.stSysInfo.usSid, g_stCnasXregSysMsgCont.stSysInfo.usNid))
        &&(VOS_TRUE == g_stCnasXregSysMsgCont.stSysInfo.stRegInfo.ucPowerDownReg)
        &&(CAS_CNAS_1X_CAS_IDLE_STATE == g_stCnasXregStateInfo.enCasState)
        &&(CNAS_XREG_VAR_YES        == g_stCnasXregStateInfo.enRegEnabledFlag)
        &&(CNAS_XREG_TIMER_EXPIRED  == g_stCnasXregStateInfo.enT57MState))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_BOOL CNAS_XREG_DistanceCheck(CNAS_XREG_SYS_MSG_CONTENT_STRU   *pstSysInfoSave,
                                            CNAS_XREG_REGSTATE_STRU         *pstSysState)
{
    /*REG_DIST  is not equal to zero; and
      REG_ENABLED  is equal to YES; and
      The current base station distance from the base station in which the mobile
      station last registered (see 2.6.5.1.4) is greater than or equal to REG_DIST_REGs-p*/

    if ((0 != pstSysInfoSave->stSysInfo.stRegInfo.usRegDistance)
        &&(CNAS_XREG_VAR_YES == pstSysState->enRegEnabledFlag)
        &&(CNAS_XREG_VAR_YES == pstSysState->enDistRegFlag))
    {
        pstSysState->enDistRegFlag = CNAS_XREG_VAR_NO;

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_BOOL CNAS_XREG_ZoneCheck(CNAS_XREG_SYS_MSG_CONTENT_STRU   *pstSysInfoSave,
                                        CNAS_XREG_REGSTATE_STRU         *pstSysState)
{
    /*TOTAL_ZONES  is not equal to zero; and
      REG_ENABLED  is equal to YES; and
      There is no entry of ZONE_LIST  whose SID, NID and REG_ZONE fields match the stored SID , NID  and REG_ZONE .*/

    if ((CNAS_XREG_VAR_YES == pstSysState->enRegEnabledFlag)
        && (0 != pstSysInfoSave->stSysInfo.stRegInfo.ucRegZoneNum))
    {
        if (VOS_NULL_PTR == CNAS_XREG_FindZoneNode(pstSysInfoSave->stSysInfo.usSid,
                                                   pstSysInfoSave->stSysInfo.usNid,
                                                   pstSysInfoSave->stSysInfo.stRegInfo.usRegZone))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_BOOL CNAS_XREG_SciParaCheck(VOS_VOID)
{
    VOS_UINT8                               ucCardSci;

    ucCardSci = CNAS_XREG_GetCardSciValue();

    if (ucCardSci != CNAS_XREG_GetLastSciValue())
    {
        CNAS_XREG_SetLastSciValue(ucCardSci);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_BOOL CNAS_XREG_TermParaCheck(VOS_VOID)
{
    CNAS_NVIM_1X_MOB_TERM_STRU          stTermNv;

    /* 将NV项中读到的值和卡中的相比较，如果不同则发起注册操作 */
    if (NV_OK != NV_Read(en_NV_Item_1X_MOB_TERM, &stTermNv, sizeof(stTermNv)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XREG, "CNAS_XREG_TermParaCheck:NV_Read Failed");

        return VOS_FALSE;
    }

    if ((g_stCnasXregHomeInfo.ucMobTermForNid != stTermNv.ucMobTermForNid)
     || (g_stCnasXregHomeInfo.ucMobTermForSid != stTermNv.ucMobTermForSid)
     || (g_stCnasXregHomeInfo.ucMobTermHome   != stTermNv.ucMobTermHome))
    {
        stTermNv.ucMobTermForNid = g_stCnasXregHomeInfo.ucMobTermForNid;
        stTermNv.ucMobTermForSid = g_stCnasXregHomeInfo.ucMobTermForSid;
        stTermNv.ucMobTermHome   = g_stCnasXregHomeInfo.ucMobTermHome;

        (VOS_VOID)NV_Write(en_NV_Item_1X_MOB_TERM, &stTermNv, sizeof(stTermNv));

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_BOOL CNAS_XREG_ParaCheck(CNAS_XREG_SYS_MSG_CONTENT_STRU   *pstSysInfoSave,
                                        CNAS_XREG_REGSTATE_STRU          *pstSysState)
{
    /*PARAMETER_REG  is equal to 1!ˉ; and
      There is no entry of SID_NID_LIST  whose SID and NID fields match the stored SID  and NID.*/

    if (VOS_FALSE == pstSysInfoSave->stSysInfo.stRegInfo.ucParameterReg)
    {
        return VOS_FALSE;
    }

    if (VOS_NULL_PTR == CNAS_XREG_FindSidNidNode(pstSysInfoSave->stSysInfo.usSid, pstSysInfoSave->stSysInfo.usNid))
    {
        return VOS_TRUE;
    }

    /* 判断卡中的SCI值是否有变化 */
    if (VOS_TRUE == CNAS_XREG_SciParaCheck())
    {
        return VOS_TRUE;
    }


    if (VOS_TRUE == CNAS_XREG_TermParaCheck())
    {
        return VOS_TRUE;
    }

    /* 协议版本发生变化 */
    if (CNAS_XREG_VAR_YES == g_stCnasXregStateInfo.enIsVerChange)
    {
        return VOS_TRUE;
    }

    /* TCH下最后切换到没有注册过的小区 */
    if (CNAS_XREG_VAR_YES == g_stCnasXregStateInfo.enIsTchHandoff)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_BOOL CNAS_XREG_UserZoneCheck(CNAS_XREG_REGSTATE_STRU  *pstSysState)
{
    return VOS_FALSE;   /*本地迭代不实现*/
}


VOS_BOOL CNAS_XREG_EncryptCheck(CNAS_XREG_REGSTATE_STRU  *pstSysState)
{
    return VOS_FALSE;   /*本地迭代不实现*/
}


CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8 CNAS_XREG_IdleRegCheck(VOS_VOID)
{
    VOS_UINT32      ulResult;

    if ((CNAS_XREG_SYSMSG_CURRENT != g_stCnasXregSysMsgCont.enAvailable)
        ||(CNAS_XREG_TIMER_EXPIRED  != g_stCnasXregStateInfo.enT57MState)
        ||(CAS_CNAS_1X_CAS_IDLE_STATE  != g_stCnasXregStateInfo.enCasState))
    {
        return CAS_CNAS_1X_REGISTRATION_TYPE_BUTT;
    }

    /* 启动周期性注册定时器 */
    CNAS_XREG_RegTimerStart(&g_stCnasXregSysMsgCont.stSysInfo, &g_stCnasXregStateInfo);

    /* 刷新超时链表节点 */
    CNAS_XREG_RefreshLists();

    ulResult = CNAS_XREG_PowerUpCheck(&g_stCnasXregSysMsgCont, &g_stCnasXregStateInfo);

    if (VOS_TRUE == ulResult)
    {
        return CAS_CNAS_1X_POWER_UP_REGISTRATION;
    }

    ulResult = CNAS_XREG_PowerUpParaCheck(&g_stCnasXregSysMsgCont, &g_stCnasXregStateInfo);

    if (VOS_TRUE == ulResult)
    {
        return CAS_CNAS_1X_POWER_UP_REGISTRATION;
    }

    ulResult = CNAS_XREG_ParaCheck(&g_stCnasXregSysMsgCont, &g_stCnasXregStateInfo);

    if (VOS_TRUE == ulResult)
    {
        return CAS_CNAS_1X_PARAMETER_CHANGED_REGISTRATION;
    }

    ulResult = CNAS_XREG_TimerBaseCheck(&g_stCnasXregStateInfo);

    if (VOS_TRUE == ulResult)
    {
        return CAS_CNAS_1X_TIMER_BASED_REGISTRATION;
    }

    ulResult = CNAS_XREG_DistanceCheck(&g_stCnasXregSysMsgCont, &g_stCnasXregStateInfo);

    if (VOS_TRUE == ulResult)
    {
        return CAS_CNAS_1X_DISTANCE_BASED_REGISTRATION;
    }

    ulResult = CNAS_XREG_ZoneCheck(&g_stCnasXregSysMsgCont, &g_stCnasXregStateInfo);

    if (VOS_TRUE == ulResult)
    {
        return CAS_CNAS_1X_ZONE_BASED_REGISTRATION;
    }

    return CAS_CNAS_1X_REGISTRATION_TYPE_BUTT;
}


VOS_VOID CAS_XREG_GetTrueCodeByComplementCode(
    VOS_INT32                          *plTrueCode,
    VOS_UINT32                          ulCompCode,
    VOS_UINT8                           ucCompLen
)
{
    VOS_UINT32                           ulTemp;
    VOS_UINT32                           ulLoop;

    if ((ucCompLen > 32)
     || (ucCompLen < 2))
    {
        CNAS_ERROR_LOG(UEPS_PID_XREG, "CAS_XREG_GetTrueCodeByComplementCode: ucCompLen invalid");

        return ;
    }

    /* 判断传入的补码是否为正数，false表示正数，true表示负数 */
    if (0 == (((VOS_UINT32)1 << (ucCompLen - 1)) & ulCompCode))
    {
        *plTrueCode                     = (VOS_INT32)ulCompCode;
    }
    else
    {
        ulTemp                          = ulCompCode;
        for (ulLoop = ucCompLen;ulLoop < 32;ulLoop++)
        {
            ulTemp                      |= (VOS_UINT32)1 << ulLoop;
        }

        *plTrueCode                     = (VOS_INT32)ulTemp;
    }

    return ;
}


VOS_UINT32 CNAS_XREG_DSCHDataTrans(CAS_CNAS_1X_DSCH_DATA_IND_STRU *pstDschData)
{
    CS0005E_Details                     stCS0005Detail;
    c_f_dsch                            stDecodeData;
    VOS_INT                             lDecodeRslt;
    CNAS_XREG_MSRM_STRU                 stMsrm;

    CNAS_XREG_SetCS0005EDetailPara(&stCS0005Detail, pstDschData->enDschMsgType, CNAS_CCB_GetPRevInUse(), 0);

    /* 初始化内存 */
    PS_MEM_SET(&stDecodeData, 0, sizeof(stDecodeData));

    /* 解码 SYNC 消息 */
    lDecodeRslt = DECODE_c_f_dsch((char *)(pstDschData->aucMsgData),
                                              0,
                                              &stDecodeData,
                                              pstDschData->usMsgDataLen, /* 按bit长度输入 */
                                              &stCS0005Detail);

    /* 解码失败, 释放内存, 返回 */
    if ((lDecodeRslt < 0)
     || (U_c_f_dsch_MSRM != stDecodeData.Present))
    {
        if (VOS_NULL_PTR != stDecodeData.u.MSRM)
        {
            FREE_c_f_dsch(&stDecodeData);
        }

        return VOS_ERR;
    }

    CAS_XREG_GetTrueCodeByComplementCode(&(stMsrm.lBaseLat), stDecodeData.u.MSRM->BASE_LAT, 22);
    CAS_XREG_GetTrueCodeByComplementCode(&(stMsrm.lBaseLong), stDecodeData.u.MSRM->BASE_LONG, 23);

    stMsrm.usNid        = (VOS_UINT16)stDecodeData.u.MSRM->NID;
    stMsrm.usRegDist    = (VOS_UINT16)stDecodeData.u.MSRM->REG_DIST;
    stMsrm.usRegZone    = (VOS_UINT16)stDecodeData.u.MSRM->REG_ZONE;
    stMsrm.usSid        = (VOS_UINT16)stDecodeData.u.MSRM->SID;
    stMsrm.ucMultNids   = stDecodeData.u.MSRM->MULT_NIDS;
    stMsrm.ucMultSids   = stDecodeData.u.MSRM->MULT_SIDS;
    stMsrm.ucTotalZones = stDecodeData.u.MSRM->TOTAL_ZONES;
    stMsrm.ucZoneTimer  = stDecodeData.u.MSRM->ZONE_TIMER;

    CNAS_XREG_MSRMProc(&stMsrm);

    FREE_c_f_dsch(&stDecodeData);

    return VOS_OK;
}


VOS_UINT32 CNAS_XREG_CSCHDataTrans(CAS_CNAS_1X_CSCH_DATA_IND_STRU *pstCschData)
{
    CS0005E_Details                     stCS0005Detail;
    c_f_csch_mini6                      stDecodeData;
    VOS_INT                             lDecodeRslt;
    CNAS_XREG_ORDM_STRU                 stOrdm;

    CNAS_XREG_SetCS0005EDetailPara(&stCS0005Detail, pstCschData->enCschMsgType, CNAS_CCB_GetPRevInUse(), 0);

    /* 初始化内存 */
    PS_MEM_SET(&stDecodeData, 0, sizeof(stDecodeData));

    /* 解码 SYNC 消息 */
    lDecodeRslt = DECODE_c_f_csch_mini6((char *)(pstCschData->aucMsgData),
                                              0,
                                              &stDecodeData,
                                              pstCschData->usMsgDataLen, /* 按bit长度输入 */
                                              &stCS0005Detail);

    /* 解码失败, 释放内存, 返回 */
    if ((lDecodeRslt < 0)
     || (U_c_f_csch_mini6_ORDM != stDecodeData.Present)
     || (VOS_NULL_PTR == stDecodeData.u.ORDM->order.parameters.u.p_R_Generic_Order))
    {
        if (VOS_NULL_PTR != stDecodeData.u.ORDM)
        {
            FREE_c_f_csch_mini6(&stDecodeData);
        }

        return VOS_ERR;
    }

    stOrdm.ucOrder = stDecodeData.u.ORDM->order.ORDER;
    stOrdm.ucOrdq  = stDecodeData.u.ORDM->order.parameters.u.p_R_Generic_Order->ORDQ;

    /* 判断当前Order消息是否为Registation Requset Order */
    if (VOS_OK != CNAS_XREG_ORDMCheck(&stOrdm))
    {
        FREE_c_f_csch_mini6(&stDecodeData);

        return VOS_ERR;
    }

    FREE_c_f_csch_mini6(&stDecodeData);

    return VOS_OK;
}


VOS_VOID CNAS_XREG_ClearGlobal(VOS_VOID)
{
    VOS_MemSet(&g_stCnasXregStateInfo, 0, sizeof(g_stCnasXregStateInfo));

    g_stCnasXregStateInfo.enRegTypeMntn = NAS_OM_CDMA_REG_MODE_BUTT;

    VOS_MemSet(&g_stCnasXregSysMsgCont, 0, sizeof(g_stCnasXregSysMsgCont));

    g_stCnasXregSysMsgCont.enAvailable = CNAS_XREG_SYSMSG_STATE_BUTT;

    VOS_MemSet(&g_stCnasXregHomeInfo, 0, sizeof(g_stCnasXregHomeInfo));

    /* 默认值 */
    CNAS_XREG_SetCardSciValue(CNAS_XREG_SCI_DEF_VALUE);

    (VOS_VOID)CNAS_XREG_IsSetMobTerm(VOS_TRUE, VOS_TRUE, VOS_TRUE);

    CNAS_XREG_RestoreList();

    return;
}


VOS_VOID CNAS_XREG_GlobalMntn(VOS_UINT32 ulMsgID,VOS_UINT32 ulEvent)
{
    CNAS_XREG_MNTN_MSG_STRU     *pstMsg;

    pstMsg = (CNAS_XREG_MNTN_MSG_STRU*)VOS_AllocMsg(UEPS_PID_XREG, sizeof(CNAS_XREG_MNTN_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverPid   = UEPS_PID_XREG;
    pstMsg->enMsgId         = ulMsgID;
    pstMsg->ulEventID       = ulEvent;
    pstMsg->enCurState      = CNAS_XREG_GetCurrFsmId();

    VOS_MemCpy(&(pstMsg->stCnasXregStateInfo),  &g_stCnasXregStateInfo,  sizeof(g_stCnasXregStateInfo));
    VOS_MemCpy(&(pstMsg->stCnasXregSysMsgCont), &g_stCnasXregSysMsgCont, sizeof(g_stCnasXregSysMsgCont));
    VOS_MemCpy(&(pstMsg->stCnasXregHomeInfo),   &g_stCnasXregHomeInfo,   sizeof(g_stCnasXregHomeInfo));

    DIAG_TraceReport((VOS_VOID *)(pstMsg));

    VOS_FreeMsg(UEPS_PID_XREG, pstMsg);

    return;
}


CNAS_XREG_BLKSYS_ENUM_UINT8 CNAS_XREG_BandFreqToBlkSys(VOS_UINT16 usBandClass, VOS_UINT16 usFreq)
{
    if (0 == usBandClass)
    {
        if (CNAS_XREG_NUM_RANGE(1, 333, usFreq)
            || CNAS_XREG_NUM_RANGE(667, 716, usFreq)
            || CNAS_XREG_NUM_RANGE(991, 1023, usFreq))
        {
            return CNAS_XREG_BLKSYS_CELL_A;
        }

        if (CNAS_XREG_NUM_RANGE(334, 666, usFreq)
            || CNAS_XREG_NUM_RANGE(717, 799, usFreq))
        {
            return CNAS_XREG_BLKSYS_CELL_B;
        }
    }

    if (1 == usBandClass)
    {
        if (299 >= usFreq)
        {
            return CNAS_XREG_BLKSYS_PCS_A;
        }

        if (CNAS_XREG_NUM_RANGE(300, 399, usFreq))
        {
            return CNAS_XREG_BLKSYS_PCS_D;
        }

        if (CNAS_XREG_NUM_RANGE(400, 699, usFreq))
        {
            return CNAS_XREG_BLKSYS_PCS_B;
        }

        if (CNAS_XREG_NUM_RANGE(700, 799, usFreq))
        {
            return CNAS_XREG_BLKSYS_PCS_E;
        }

        if (CNAS_XREG_NUM_RANGE(800, 899, usFreq))
        {
            return CNAS_XREG_BLKSYS_PCS_F;
        }

        if (CNAS_XREG_NUM_RANGE(900, 1199, usFreq))
        {
            return CNAS_XREG_BLKSYS_PCS_C;
        }
    }

    return CNAS_XREG_BLKSYS_BUTT;
}


VOS_VOID CNAS_XREG_RecordRegRslt(CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8 enRegType,
                                            CAS_CNAS_1X_EST_RSLT_ENUM_UINT8 enEstRslt)
{
    g_stCnasXregDbgStat.stRecordItem[g_stCnasXregDbgStat.ulIndex].enRegType = enRegType;
    g_stCnasXregDbgStat.stRecordItem[g_stCnasXregDbgStat.ulIndex].enEstRslt = enEstRslt;
    g_stCnasXregDbgStat.stRecordItem[g_stCnasXregDbgStat.ulIndex].ulSlice   = VOS_GetSlice();

    g_stCnasXregDbgStat.ulIndex++;

    if (CNAS_XREG_MAX_ITEM_NUM == g_stCnasXregDbgStat.ulIndex)
    {
        g_stCnasXregDbgStat.ulIndex = 0;
    }

    return;
}


VOS_VOID CNAS_XREG_RecordShow(VOS_VOID)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = g_stCnasXregDbgStat.ulIndex; ulIndex < CNAS_XREG_MAX_ITEM_NUM; ulIndex++)
    {
        if (0 != g_stCnasXregDbgStat.stRecordItem[ulIndex].ulSlice)
        {
            vos_printf("enRegType: %d, enEstRslt: %d, ulSlice: 0x%x.\r\n ",
                        g_stCnasXregDbgStat.stRecordItem[ulIndex].enRegType,
                        g_stCnasXregDbgStat.stRecordItem[ulIndex].enEstRslt,
                        g_stCnasXregDbgStat.stRecordItem[ulIndex].ulSlice);
        }
    }

    for (ulIndex = 0; ulIndex < g_stCnasXregDbgStat.ulIndex; ulIndex++)
    {
        vos_printf("enRegType: %d, enEstRslt: %d, ulSlice: 0x%x.\r\n ",
                    g_stCnasXregDbgStat.stRecordItem[ulIndex].enRegType,
                    g_stCnasXregDbgStat.stRecordItem[ulIndex].enEstRslt,
                    g_stCnasXregDbgStat.stRecordItem[ulIndex].ulSlice);
    }
}


VOS_VOID CNAS_XREG_SetPowerOffDeregFlg(
    VOS_UINT8                           ucPowerOffDeregFlg
)
{
    g_stCnasXregStateInfo.ucPowerOffDeregFlg = ucPowerOffDeregFlg;
}


VOS_UINT8 CNAS_XREG_GetPowerOffDeregFlg(VOS_VOID)
{
    return g_stCnasXregStateInfo.ucPowerOffDeregFlg;
}



VOS_BOOL CNAS_XREG_IsSetMobTerm(
    VOS_UINT8                           ucMobTermForNid,
    VOS_UINT8                           ucMobTermForSid,
    VOS_UINT8                           ucMobTermHome
)
{
    VOS_BOOL                            bIsValueChange = VOS_FALSE;

    if (ucMobTermForNid != g_stCnasXregHomeInfo.ucMobTermForNid)
    {
        g_stCnasXregHomeInfo.ucMobTermForNid = ucMobTermForNid;

        bIsValueChange = VOS_TRUE;
    }

    if (ucMobTermForSid != g_stCnasXregHomeInfo.ucMobTermForSid)
    {
        g_stCnasXregHomeInfo.ucMobTermForSid = ucMobTermForSid;

        bIsValueChange = VOS_TRUE;
    }

    if (ucMobTermHome != g_stCnasXregHomeInfo.ucMobTermHome)
    {
        g_stCnasXregHomeInfo.ucMobTermHome = ucMobTermHome;

        bIsValueChange = VOS_TRUE;
    }

    return bIsValueChange;
}


VOS_VOID CNAS_XREG_SetCardSciValue(
    VOS_UINT8                           ucSciValue
)
{
    g_stCnasXregHomeInfo.ucCardSci = ucSciValue;

    return;
}


VOS_UINT8 CNAS_XREG_GetCardSciValue(VOS_VOID)
{
    return g_stCnasXregHomeInfo.ucCardSci;
}


VOS_VOID CNAS_XREG_SetLastSciValue(
    VOS_UINT8                           ucSciValue
)
{
    g_stCnasXregHomeInfo.ucLastSci = ucSciValue;

    return;
}


VOS_UINT8 CNAS_XREG_GetLastSciValue(VOS_VOID)
{
    return g_stCnasXregHomeInfo.ucLastSci;
}


VOS_VOID CNAS_XREG_CalcSciValue(VOS_VOID)
{
    VOS_UINT8                           ucSciValue;
    VOS_UINT8                           ucCardSci;

    /* 判断当前系统消息是否为最新 */
    if (CNAS_XREG_SYSMSG_NOT_CURRENT == g_stCnasXregSysMsgCont.enAvailable)
    {
        CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_CalcSciValue: SysMsg is not current.");

        return;
    }

    ucCardSci  = CNAS_XREG_GetCardSciValue();

    /* 当前网络没有注册过 */
    if (VOS_NULL_PTR == CNAS_XREG_FindSidNidNode(g_stCnasXregSysMsgCont.stSysInfo.usSid,
                                                 g_stCnasXregSysMsgCont.stSysInfo.usNid))
    {
        ucSciValue = CNAS_MIN(1, g_stCnasXregSysMsgCont.stSysInfo.ucMaxSlotCycleIndex);

        /* 规避前一次异常关机后开机，网侧还是用原来的SCI下发寻呼的问题 */
        ucSciValue = CNAS_MIN(ucCardSci, ucSciValue);
    }
    else /* 当前网络已注册过 */
    {
        ucSciValue = CNAS_MIN(ucCardSci, g_stCnasXregSysMsgCont.stSysInfo.ucMaxSlotCycleIndex);
    }

    g_stCnasXregHomeInfo.ucCurrSci = ucSciValue;

    CNAS_XREG_SndCASSciReq(ucSciValue);

    return;
}



VOS_VOID CNAS_XREG_BlkSysChange(
    XSD_XREG_SYS_INFO_STRU             *pstNewSysInfo,
    XSD_XREG_SYS_INFO_STRU             *pstOldSysInfo
)
{
    CNAS_XREG_BLKSYS_ENUM_UINT8         enNewBlkSys;
    CNAS_XREG_BLKSYS_ENUM_UINT8         enOldBlkSys;

    enNewBlkSys = CNAS_XREG_BandFreqToBlkSys(pstNewSysInfo->usBandClass, pstNewSysInfo->usFreq);
    enOldBlkSys = CNAS_XREG_BandFreqToBlkSys(pstOldSysInfo->usBandClass, pstOldSysInfo->usFreq);

    if (enNewBlkSys != enOldBlkSys)
    {
        /* Set timer-based registation enable status (COUNTER_ENABLEDs) to NO. */
        CNAS_XREG_RegTimerStop();

        /* Set autonomous registation enable status (REG_ENABLEDs) to NO.. */
        g_stCnasXregStateInfo.enRegEnabledFlag = CNAS_XREG_VAR_NO;

        /* Set the registerd flag (REGISTEREDs) to NO.*/
        g_stCnasXregStateInfo.enRegisterFlag = CNAS_XREG_VAR_NO;
        /* Set the returnCasue (RETURN_CAUSEs) to 0x00 (NORMAL_ACCESS).*/
        CNAS_CCB_Set1xReturnCause(CNAS_CCB_1X_RETURN_CAUSE_NORMAL_ACCESS);
    }

    /* 判断协议版本是否变化 */
    if (pstNewSysInfo->ucPRevInUse != pstOldSysInfo->ucPRevInUse)
    {
        g_stCnasXregStateInfo.enIsVerChange = CNAS_XREG_VAR_YES;
    }

    return;
}


VOS_VOID CNAS_XREG_EnableNoCardMode(VOS_VOID)
{
    g_stCnasXregHomeInfo.ucNoCardMode = VOS_TRUE;

    return;
}


VOS_UINT8 CNAS_XREG_GetNoCardMode(VOS_VOID)
{
    return g_stCnasXregHomeInfo.ucNoCardMode;
}


VOS_VOID  CNAS_XREG_SetOmRegReportFlag(
    NAS_OM_REPORT_ACTION_ENUM_UINT8     enRptAction
)
{
    g_enCnasXregRptAction = enRptAction;

    return;
}


NAS_OM_REPORT_ACTION_ENUM_UINT8  CNAS_XREG_GetOmRegReportFlag(VOS_VOID)
{
    return g_enCnasXregRptAction;
}


VOS_VOID CNAS_XREG_ProcCardReadFileCnf_EF_TERM(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile;
    VOS_UINT8                           ucMobTermForNid;
    VOS_UINT8                           ucMobTermForSid;
    VOS_UINT8                           ucMobTermHome;
    CNAS_NVIM_1X_MOB_TERM_STRU          stTermNv;

    ucMobTermForNid = VOS_FALSE;
    ucMobTermForSid = VOS_FALSE;
    ucMobTermHome   = VOS_FALSE;

    pstFile = (USIMM_READFILE_CNF_STRU*)pstMsg;

    /* 参数判断 */
    if ((VOS_OK != pstFile->stCmdResult.ulResult) || (0 == pstFile->usEfLen))
    {
        CNAS_WARNING_LOG2(UEPS_PID_XREG, "CNAS_XREG_ProcCardReadFileCnf_EF_TERM:ERROR: Read Error:",
                          pstFile->stCmdResult.ulResult, pstFile->usEfLen);

        return;
    }

    /* NID */
    if (0 != (pstFile->aucEf[0] & CNAS_XREG_MOB_TERM_NID_MASK))
    {
        ucMobTermForNid = VOS_TRUE;
    }

    /* SID */
    if (0 != (pstFile->aucEf[0] & CNAS_XREG_MOB_TERM_SID_MASK))
    {
        ucMobTermForSid = VOS_TRUE;
    }

    /* HOME */
    if (0 != (pstFile->aucEf[0] & CNAS_XREG_MOB_TERM_HOME_MASK))
    {
        ucMobTermHome   = VOS_TRUE;
    }

    /* 保存到全局变量中 */
    if (VOS_TRUE == CNAS_XREG_IsSetMobTerm(ucMobTermForNid, ucMobTermForSid, ucMobTermHome))
    {
        CNAS_XREG_SetCardFilesChangeFlg(CNAS_XREG_REFRESH_CARD_FILE_TERM_FLG);
    }

    /* 假如NV项未激活则将卡中的值写入NV中 */
    stTermNv.ucMobTermForNid = ucMobTermForNid;
    stTermNv.ucMobTermForSid = ucMobTermForSid;
    stTermNv.ucMobTermHome   = ucMobTermHome;
    stTermNv.ucRsv           = 0;

    (VOS_VOID)NV_Write(en_NV_Item_1X_MOB_TERM, &stTermNv, sizeof(stTermNv));

    return;
}


VOS_VOID CNAS_XREG_ProcCardReadFileCnf_EF_SSCI(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile;
    VOS_UINT8                           ucSci;

    pstFile = (USIMM_READFILE_CNF_STRU*)pstMsg;

    if ((VOS_OK != pstFile->stCmdResult.ulResult) || (0 == pstFile->usEfLen))
    {
        CNAS_WARNING_LOG2(UEPS_PID_XREG, "CNAS_XREG_ProcCardReadFileCnf_EF_SSCI:ERROR: Read Error:",
                          pstFile->stCmdResult.ulResult, pstFile->usEfLen);

        return;
    }

    ucSci = pstFile->aucEf[0] & CNAS_XREG_SSCI_VALUE_MASK;

    /* 如果文件变更则刷新缓存 */
    if (ucSci != CNAS_XREG_GetCardSciValue())
    {
        /* 保存到全局变量中 */
        CNAS_XREG_SetCardSciValue(ucSci);

        CNAS_XREG_SetCardFilesChangeFlg(CNAS_XREG_REFRESH_CARD_FILE_SSCI_FLG);
    }

    return ;
}


VOS_VOID CNAS_XREG_ProcCardReadFileCnf(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile;
    USIMM_DEF_FILEID_ENUM_UINT32        enEfId;

    pstFile = (USIMM_READFILE_CNF_STRU*)pstMsg;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstFile->stFilePath.ulPathLen, pstFile->stFilePath.acPath, &enEfId))
    {
        return;
    }

    switch (enEfId)
    {
        case USIMM_CDMA_EFTERM_ID:
        case USIMM_CSIM_EFTERM_ID:
            CNAS_XREG_ProcCardReadFileCnf_EF_TERM(pstMsg);
            break;

        case USIMM_CDMA_EFSSCI_ID:
        case USIMM_CSIM_EFSSCI_ID:
            CNAS_XREG_ProcCardReadFileCnf_EF_SSCI(pstMsg);
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_ProcCardReadFileCnf:WARNING: File Id Abnormal");
            break;
    }

    return;
}


VOS_VOID CNAS_XREG_TchHandoffProc(
    XSD_XREG_SYS_INFO_IND_STRU         *pstSysInfoMsg
)
{
    /* 在TCH态假如切换到没有注册过的小区，退出TCH态后需要进行注册操作 */
    if (CNAS_CCB_1X_CAS_TCH_STATE == CNAS_CCB_GetCasState())
    {
        if (VOS_NULL_PTR == CNAS_XREG_FindSidNidNode(pstSysInfoMsg->stSysInfo.usSid,
                                                     pstSysInfoMsg->stSysInfo.usNid))
        {
            /* 需要注册 */
            g_stCnasXregStateInfo.enIsTchHandoff = CNAS_XREG_VAR_YES;
        }
        else
        {
            /* 不需要注册 */
            g_stCnasXregStateInfo.enIsTchHandoff = CNAS_XREG_VAR_NO;
        }
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




