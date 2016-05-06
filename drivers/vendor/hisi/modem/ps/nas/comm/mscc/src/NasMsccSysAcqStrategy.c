

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasMsccCtx.h"
#include "PsCommonDef.h"
#include "NasMsccMntn.h"
#include "NasMsccMlplMsplApi.h"
#include "NasMsccComFunc.h"
#include "NasMsccSysAcqStrategy.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_SYS_ACQ_STRATEGY_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* according to different acquire scene,here provide the sys acq list build table */
NAS_MSCC_SYS_ACQ_LIST_BUILD_TBL_STRU    g_astNasMsccSysAcqListBuildTbl[] =
{
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SWITCH_ON,                      NAS_MSCC_BuildSysAcqList_SwitchOn},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SWITCH_ON_INIT_ACQ_SUCC,        NAS_MSCC_BuildSysAcqList_InitAcqSuccInSwitchOn},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SWITCH_ON_INIT_ACQ_FAIL,        NAS_MSCC_BuildSysAcqList_InitAcqFailInSwitchOn},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_AVAILABLE_TIMER_EXPIRED,        NAS_MSCC_BuildSysAcqList_AvailableTimerExpired},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_HRPD_LOST,                      NAS_MSCC_BuildSysAcqList_HrpdLost},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_LTE_LOST,                       NAS_MSCC_BuildSysAcqList_LteLost},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SLEEP_TIMER_EXPIRED,            NAS_MSCC_BuildSysAcqList_SleepTimerExpired},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_LTE_RF_AVAILABLE,               NAS_MSCC_BuildSysAcqList_LteRfAvailable},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_HRPD_RF_AVAILABLE,              NAS_MSCC_BuildSysAcqList_HrpdRfAvailable},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SYS_CFG_SET,                    NAS_MSCC_BuildSysAcqList_SysCfgSet},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_MO_TRIGGER,                          NAS_MSCC_BuildSysAcqList_MoTrigger},

    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_LTE_NOT_AVAILABLE,                                NAS_MSCC_BuildSysAcqList_LteNotAvailable},
};


/*****************************************************************************
  3 函数定义
*****************************************************************************/


VOS_VOID NAS_MSCC_BuildSysAcqList(
    NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_UINT32           enSysAcqScene,
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    VOS_UINT32                          i;
    pNasMsccSysAcqListBuildFunc         pfunSysAcqListBuild = VOS_NULL_PTR;

    for (i = 0; i < (sizeof(g_astNasMsccSysAcqListBuildTbl)/sizeof(NAS_MSCC_SYS_ACQ_LIST_BUILD_TBL_STRU)); i++)
    {
        if (enSysAcqScene == g_astNasMsccSysAcqListBuildTbl[i].enSysAcqScene)
        {
            pfunSysAcqListBuild = g_astNasMsccSysAcqListBuildTbl[i].pfunSysAcqListBuild;
            break;
        }
    }

    if (VOS_NULL_PTR != pfunSysAcqListBuild)
    {
        pfunSysAcqListBuild(pst1xLocInfo, pstLteLocInfo, pstSysAcqListInfo);
    }

    return;
}



VOS_VOID NAS_MSCC_BuildSysAcqList_SwitchOn(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    NAS_MSCC_PRIOR_SYS_ENUM_UINT8       enPriSys = NAS_MSCC_PRIOR_SYS_BUTT;
    NAS_MSCC_MMSS_LOCATION_INFO_STRU   *pstMmsLocInfo;
    VOS_UINT8                           ucIndex;

    ucIndex  = 0;

    pstMmsLocInfo = NAS_MSCC_GetMmssLastLocationInfoAddr();

    /* 根据无卡初搜位置信息，查找lte或hrpd的优先级。如果返回NAS_MSCC_PRIOR_SYS_BUTT，
        还是维持原有逻辑，需要使用last loc info查找lte或hrpd优先级 */
    enPriSys = NAS_MSCC_GetPrefRatWithNoCardInitSearchLocInfo();

    if (NAS_MSCC_PRIOR_SYS_BUTT == enPriSys)
    {
        /* if the MMSS location info values are not valid or GUL mode, should do initial sytem acquire */
        if ((VOS_FALSE                    == pstMmsLocInfo->ucIsLocInfoUsedInSwitchOn)
         || (NAS_MSCC_LC_RAT_COMBINED_GUL == pstMmsLocInfo->enSysAcqMode))
        {
            pstSysAcqListInfo->astInitialAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
            pstSysAcqListInfo->astInitialAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
            ucIndex++;

            if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
            {
                pstSysAcqListInfo->astInitialAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_1X;
                pstSysAcqListInfo->astInitialAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
                ucIndex++;
            }

            pstSysAcqListInfo->ucInitialAcqSysNum = ucIndex;

            return;
        }

        /* using last locaiton info to determine the prefered rat */
        enPriSys = NAS_MSCC_GetPrefRatWithLastLocInfo();
    }

    if (NAS_MSCC_LTE_PRIOR == enPriSys)
    {
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;
    }
    else if (NAS_MSCC_HRPD_PRIOR == enPriSys)
    {
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;
    }
    else
    {
        /* the prior is butt indicate we could not judge the perfered rat,we have to do the initial system acqquire */
        pstSysAcqListInfo->astInitialAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
        pstSysAcqListInfo->astInitialAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->astInitialAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_1X;
        pstSysAcqListInfo->astInitialAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->ucInitialAcqSysNum = ucIndex;
    }

    return;
}




VOS_VOID NAS_MSCC_BuildSysAcqList_InitAcqSuccInSwitchOn(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    NAS_MSCC_PRIOR_SYS_ENUM_UINT8       enPriSys;
    VOS_UINT8                           ucIndex;

    ucIndex  = 0;
    enPriSys = NAS_MSCC_PRIOR_SYS_BUTT;

    /* use lte location to determine the preferred rat */
    if (VOS_NULL_PTR != pstLteLocInfo)
    {
        enPriSys = NAS_MSCC_GetPrefRatWithLteLocInfo(pstLteLocInfo);
    }

    /* use 1x location to determine the preferred rat */
    if (VOS_NULL_PTR != pst1xLocInfo)
    {
        enPriSys = NAS_MSCC_GetPrefRatWith1xLocInfo(pst1xLocInfo);
    }

    if (NAS_MSCC_HRPD_PRIOR == enPriSys)
    {
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;
    }
    else if (NAS_MSCC_LTE_PRIOR == enPriSys)
    {
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;
    }
    else
    {
        /* use initial system acquire result could not determine which prefer,should continue
           uset the less prefered rat to do the initial system acquire */

        pstSysAcqListInfo->ucNormalAcqSysNum = 0;

        return;
    }

    pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;

    return;
}




VOS_VOID NAS_MSCC_BuildSysAcqList_InitAcqFailInSwitchOn(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    /* while initial acquire failed,we directly acquire hrpd, so
       use the same logic in lte lost scene */
    NAS_MSCC_BuildSysAcqList_LteLost(pst1xLocInfo, pstLteLocInfo, pstSysAcqListInfo);

    return;
}



VOS_VOID NAS_MSCC_BuildSysAcqList_AvailableTimerExpired(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    NAS_MSCC_PRIOR_SYS_ENUM_UINT8       enPriSys;
    VOS_UINT8                           ucIndex;

    ucIndex  = 0;

    /* using last locaiton info to determine the prefered rat */
    enPriSys = NAS_MSCC_GetPrefRatWithLastLocInfo();

    if (NAS_MSCC_HRPD_PRIOR == enPriSys)
    {
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;
    }
    else
    {
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;
    }

    return;
}




VOS_VOID NAS_MSCC_BuildSysAcqList_HrpdLost(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    VOS_UINT8                           ucIndex;

    ucIndex  = 0;

    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
    ucIndex++;

    pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;

    return;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_BuildSysAcqList_LteLost
Description     :   The function is used to build system acquire list while lte lost
Input parameters:   pst1xLocInfo ---- 1x location info
                    pstLteLocInfo-----lte location info
Output parameters:  pstSysAcqListInfo---system acqurie list info
Return Value    :   VOS_VOID
Modify History:
    1)  Date    :   2015-04-16
        Author  :   w00176964
        Modify content :Create
    2)  Date    :   2015-12-21
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/

VOS_VOID NAS_MSCC_BuildSysAcqList_LteLost(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    VOS_UINT8                           ucIndex;

    ucIndex  = 0;

    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
    ucIndex++;

    /* LTE掉网场景,先尝试DO,DO尝试失败后再尝试搜下LTE */
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
    ucIndex++;

    pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;

    return;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_BuildSysAcqList_LteNotAvailable
Description     :   LTE不可用(临时或永久)时构造捕获列表
Input parameters:   pst1xLocInfo ---- 1x location info
                    pstLteLocInfo-----lte location info
Output parameters:  pstSysAcqListInfo---system acqurie list info
Return Value    :   VOS_VOID
Modify History:
    1)  Date    :   2015-12-21
        Author  :   w00176964
        Modify content :Create
*****************************************************************************/

VOS_VOID NAS_MSCC_BuildSysAcqList_LteNotAvailable(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    VOS_UINT8                           ucIndex;

    ucIndex  = 0;

    /* Lte不可用(NO RF或PS卡无效等)时,只搜DO,下轮搜网,L变为可用再尝试搜L */
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
    ucIndex++;

    pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;

    return;
}




VOS_VOID NAS_MSCC_BuildSysAcqList_SleepTimerExpired(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    NAS_MSCC_BuildSysAcqList_AvailableTimerExpired(pst1xLocInfo, pstLteLocInfo, pstSysAcqListInfo);

    return;
}




VOS_VOID NAS_MSCC_BuildSysAcqList_MoTrigger(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    NAS_MSCC_BuildSysAcqList_AvailableTimerExpired(pst1xLocInfo, pstLteLocInfo, pstSysAcqListInfo);

    return;
}



VOS_VOID NAS_MSCC_BuildSysAcqList_LteRfAvailable(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    VOS_UINT8                           ucIndex;

    ucIndex  = 0;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
    ucIndex++;

    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
    ucIndex++;

    pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;

    return;
}


VOS_VOID NAS_MSCC_BuildSysAcqList_HrpdRfAvailable(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    VOS_UINT8                           ucIndex;

    ucIndex  = 0;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
    ucIndex++;

    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
    ucIndex++;

    pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;

    return;
}



VOS_VOID NAS_MSCC_BuildSysAcqList_SysCfgSet(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    NAS_MSCC_BuildSysAcqList_SwitchOn(pst1xLocInfo, pstLteLocInfo, pstSysAcqListInfo);

    return;
}




VOS_UINT32 NAS_MSCC_GetNextNormalAcquireSysInAcqSysList(
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstAcqSysListInfo,
    NAS_MSCC_SYS_ACQ_SYS_INFO_STRU                         *pstNextAcqSysInfo
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < pstAcqSysListInfo->ucNormalAcqSysNum; ucIndex++)
    {
        if (NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED == pstAcqSysListInfo->astNormalAcqSysList[ucIndex].enAcqStatus)
        {
            pstNextAcqSysInfo->enAcqStatus = pstAcqSysListInfo->astNormalAcqSysList[ucIndex].enAcqStatus;
            pstNextAcqSysInfo->ulRatMode   = pstAcqSysListInfo->astNormalAcqSysList[ucIndex].ulRatMode;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MSCC_GetNextInitialAcquireSysInAcqSysList(
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstAcqSysListInfo,
    NAS_MSCC_SYS_ACQ_SYS_INFO_STRU                         *pstNextAcqSysInfo
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < pstAcqSysListInfo->ucInitialAcqSysNum; ucIndex++)
    {
        if (NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED == pstAcqSysListInfo->astInitialAcqSysList[ucIndex].enAcqStatus)
        {
            pstNextAcqSysInfo->enAcqStatus = pstAcqSysListInfo->astInitialAcqSysList[ucIndex].enAcqStatus;
            pstNextAcqSysInfo->ulRatMode   = pstAcqSysListInfo->astInitialAcqSysList[ucIndex].ulRatMode;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_VOID NAS_MSCC_UpdateAcqRatStatusInNormalAcqSysList(
    VOS_RATMODE_ENUM_UINT32                                 ulRatMode,
    NAS_MSCC_SYS_ACQ_STATUS_ENUM_UINT8                      enSysAcqStatus,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstAcqSysListInfo
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < pstAcqSysListInfo->ucNormalAcqSysNum; ucIndex++)
    {
        if (ulRatMode == pstAcqSysListInfo->astNormalAcqSysList[ucIndex].ulRatMode)
        {
            pstAcqSysListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = enSysAcqStatus;
        }
    }

    return;
}



VOS_VOID NAS_MSCC_ResetAcqRatStatusInNormalAcqSysList(
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstAcqSysListInfo
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < pstAcqSysListInfo->ucNormalAcqSysNum; ucIndex++)
    {
        pstAcqSysListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
    }

    return;
}





NAS_MSCC_PRIOR_SYS_ENUM_UINT8  NAS_MSCC_GetPrefRatWithLastLocInfo(VOS_VOID)
{
    NAS_MSCC_MMSS_LOCATION_INFO_STRU                       *pstMmssLocationInfo = VOS_NULL_PTR;
    NAS_MSCC_MMSS_SYSACQ_CFG_STRU                          *pstMmssSysAcqCfgInfo = VOS_NULL_PTR;
    NAS_MSCC_PRIOR_SYS_ENUM_UINT8                           enPreferredRat;

    pstMmssLocationInfo = NAS_MSCC_GetMmssLastLocationInfoAddr();

    /* Get the MMSS Cfg Info Address */
    pstMmssSysAcqCfgInfo = NAS_MSCC_GetMmssSysAcqCfgInfoAddr();

    /* Default value is invalid RAT */
    enPreferredRat = NAS_MSCC_PRIOR_SYS_BUTT;

    /* Check if CDMA 1x Location Info is preferred. If TRUE, use the MCC, SID and NID values to find the preferred RAT in MSPL */
    if ((VOS_TRUE == pstMmssSysAcqCfgInfo->ucIs1xLocInfoPrefThanLte)
     && (VOS_TRUE == pstMmssLocationInfo->ucCdma1xActiveFlag))
    {
        enPreferredRat = NAS_MSCC_GetPrefRatWith1xLocInfo(&(pstMmssLocationInfo->st1xLocationInfo));
    }
    else if (VOS_TRUE == pstMmssLocationInfo->ucLteActiveFlag)
    {
        enPreferredRat = NAS_MSCC_GetPrefRatWithLteLocInfo(&pstMmssLocationInfo->stLteLocationInfo);
    }
    else if (VOS_TRUE == pstMmssLocationInfo->ucCdma1xActiveFlag)
    {
        enPreferredRat = NAS_MSCC_GetPrefRatWith1xLocInfo(&(pstMmssLocationInfo->st1xLocationInfo));
    }
    else /* When HRPD and LTE System priority is not found */
    {
        enPreferredRat = NAS_MSCC_PRIOR_SYS_BUTT;
    }

    return enPreferredRat;
}



NAS_MSCC_PRIOR_SYS_ENUM_UINT8  NAS_MSCC_GetPrefRatWith1xLocInfo(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocationInfo
)
{
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                  st1xSysInfo;
    NAS_MSCC_PRIOR_SYS_ENUM_UINT8                           enPreferredRat;
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstMsplList = VOS_NULL_PTR;

    pstMsplList = (NAS_MSCC_MSPL_SYS_LIST_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                                                   sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    if (VOS_NULL_PTR == pstMsplList)
    {
        return NAS_MSCC_PRIOR_SYS_BUTT;
    }

    /* Clear the Structure variables */
    PS_MEM_SET(&st1xSysInfo, 0x00 , sizeof(NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU));
    PS_MEM_SET(pstMsplList, 0x00, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    st1xSysInfo.ulMcc                  = pst1xLocationInfo->ulMcc;
    st1xSysInfo.ulMnc                  = pst1xLocationInfo->ulMnc;
    st1xSysInfo.ucIsMccValid           = VOS_TRUE;
    st1xSysInfo.ucIsMncValid           = VOS_TRUE;
    st1xSysInfo.usSid                  = pst1xLocationInfo->usSid;
    st1xSysInfo.usNid                  = pst1xLocationInfo->usNid;

    st1xSysInfo.enPriClassCdma20001x   = pst1xLocationInfo->en1xPrioClass;
    st1xSysInfo.enPriClassCdma2000Ai   = pst1xLocationInfo->enAIPrioClass;

    enPreferredRat = NAS_MSCC_PRIOR_SYS_BUTT;

    if (VOS_TRUE == NAS_MSCC_GetMsplSysListBy1xLoc(&st1xSysInfo, pstMsplList))
    {
        if (VOS_TRUE == NAS_MSCC_IsLteMorePreferredThanHrpdInMspl(pstMsplList))
        {
            enPreferredRat = NAS_MSCC_LTE_PRIOR;
        }

        /* If 3GPP or LTE is not the more preferred RAT, return HRPD priority */
        else
        {
            enPreferredRat = NAS_MSCC_HRPD_PRIOR;
        }
    }

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsplList);

    return enPreferredRat;
}




NAS_MSCC_PRIOR_SYS_ENUM_UINT8  NAS_MSCC_GetPrefRatWithLteLocInfo(
    NAS_MSCC_LTE_LOC_INFO_STRU         *pstLteLocInfo
)
{
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU                stLteLocationInfo;
    NAS_MSCC_PRIOR_SYS_ENUM_UINT8                           enPreferredRat;
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstMsplList         = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;

    pstMsplList = (NAS_MSCC_MSPL_SYS_LIST_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                                                   sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    if (VOS_NULL_PTR == pstMsplList)
    {
        return NAS_MSCC_PRIOR_SYS_BUTT;
    }

    /* Clear the Structure variables */
    PS_MEM_SET(&stLteLocationInfo, 0x00 , sizeof(NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU));
    PS_MEM_SET(pstMsplList, 0x00, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    /* Initialize the input structure */
    stLteLocationInfo.stPlmnId.ulMcc = pstLteLocInfo->ulMcc;
    stLteLocationInfo.stPlmnId.ulMnc = pstLteLocInfo->ulMnc;
    stLteLocationInfo.enPriClass     = pstLteLocInfo->enPrioClass;
    stLteLocationInfo.enSysRat       = VOS_RATMODE_LTE;

    enPreferredRat = NAS_MSCC_PRIOR_SYS_BUTT;

    pstMatchedMsplTable = NAS_MSCC_GetMatchedMsplTableBy3gppInfo(&stLteLocationInfo);

    if (VOS_NULL_PTR != pstMatchedMsplTable)
    {
        NAS_MSCC_GetSysListFromMsplTable(pstMatchedMsplTable, pstMsplList);

        if (VOS_TRUE == NAS_MSCC_IsLteMorePreferredThanHrpdInMspl(pstMsplList))
        {
            enPreferredRat = NAS_MSCC_LTE_PRIOR;
        }

        /* If 3GPP or LTE is not the more preferred RAT, return HRPD priority */
        else
        {
            enPreferredRat = NAS_MSCC_HRPD_PRIOR;
        }
    }

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsplList);

    return enPreferredRat;

}



VOS_UINT8  NAS_MSCC_IsLteMorePreferredThanHrpdInMspl(
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU   *pstMsplSysList
)
{
    VOS_UINT8                           i;

    /* 消除 PCLINT429 告警 */
    pstMsplSysList = pstMsplSysList;

    /* Loop through the MSPL Info list. If LTE or 3GPP AI occurs first in the List, then return LTE is preferred */
    for (i = 0; i < pstMsplSysList->ucSysCount; i++)
    {
        if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI == pstMsplSysList->astSysList[i].enSysType)
         || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD == pstMsplSysList->astSysList[i].enSysType))
        {
            /* If the system type is HRPD or CDMA2000Ai, then return VOS_FALSE */
            return VOS_FALSE;
        }

        if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI == pstMsplSysList->astSysList[i].enSysType)
         || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE == pstMsplSysList->astSysList[i].enSysType))
        {
            /* If the system type is LTE or 3GPPAi, then return VOS_TRUE */
            return VOS_TRUE;
        }

    }

    /* here in mlpl sys list hrpd and lte both not exist,we consider lte more prefered */
    return VOS_TRUE;
}


NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8 NAS_MSCC_GetDestBsrSysTypeInSysList(
    VOS_RATMODE_ENUM_UINT32                                 enCurSysRat,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
)
{
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enSysType;
    VOS_UINT8                                               ucLoop;

    enSysType = NAS_MSCC_MLPL_MSPL_SYS_TYPE_BUTT;

    for (ucLoop = 0; ucLoop < pstOutSysList->ucSysCount; ucLoop++)
    {
        if ((VOS_RATMODE_LTE                            == enCurSysRat)
         && ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI   == pstOutSysList->astSysList[ucLoop].enSysType)
          || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD == pstOutSysList->astSysList[ucLoop].enSysType)))
        {
            enSysType =  pstOutSysList->astSysList[ucLoop].enSysType;
            break;
        }

        if ((VOS_RATMODE_HRPD                    == enCurSysRat)
        && ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI == pstOutSysList->astSysList[ucLoop].enSysType)
         || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE     == pstOutSysList->astSysList[ucLoop].enSysType)))
        {
            enSysType =  pstOutSysList->astSysList[ucLoop].enSysType;
            break;
        }
    }

    return enSysType;
}


NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8 NAS_MSCC_GetDestBsrSysPriClassInSysList(
    VOS_RATMODE_ENUM_UINT32                                 enCurSysRat,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
)
{
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enPriClass;
    VOS_UINT8                                               ucLoop;

    enPriClass = NAS_MSCC_MSPL_SYS_PRI_CLASS_BUTT;

    for (ucLoop = 0; ucLoop < pstOutSysList->ucSysCount; ucLoop++)
    {
        if ((VOS_RATMODE_LTE                            == enCurSysRat)
         && ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI   == pstOutSysList->astSysList[ucLoop].enSysType)
          || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD == pstOutSysList->astSysList[ucLoop].enSysType)))
        {
            enPriClass =  pstOutSysList->astSysList[ucLoop].enPriClass;
            break;
        }

        if ((VOS_RATMODE_HRPD                    == enCurSysRat)
        && ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI == pstOutSysList->astSysList[ucLoop].enSysType)
         || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE     == pstOutSysList->astSysList[ucLoop].enSysType)))
        {
            enPriClass =  pstOutSysList->astSysList[ucLoop].enPriClass;
            break;
        }
    }

    return enPriClass;
}



VOS_UINT8  NAS_MSCC_IsLteSysTypeExistInSysList(
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU   *pstSysList
)
{
    VOS_UINT8                           i;

    for (i = 0; i < pstSysList->ucSysCount; i++)
    {
        if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI == pstSysList->astSysList[i].enSysType)
          ||(NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE     == pstSysList->astSysList[i].enSysType))
        {
            return VOS_TRUE;
        }

    }

    return VOS_FALSE;
}


VOS_UINT8  NAS_MSCC_IsHrpdSysTypeExistInSysList(
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU   *pstSysList
)
{
    VOS_UINT8                           i;

    for (i = 0; i < pstSysList->ucSysCount; i++)
    {
        if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI   == pstSysList->astSysList[i].enSysType)
          ||(NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD == pstSysList->astSysList[i].enSysType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_VOID  NAS_MSCC_ConvertSysAcqSceneToBuildSysAcqListScene(
    NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene,
    NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_UINT32          *penBuildSysAcqListScene
)
{
    switch (enSysAcqScene)
    {
        case NAS_MSCC_SYS_ACQ_SCENE_SWITCH_ON:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SWITCH_ON;
            break;

        case NAS_MSCC_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_AVAILABLE_TIMER_EXPIRED;
            break;

        case NAS_MSCC_SYS_ACQ_SCENE_HRPD_LOST:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_HRPD_LOST;
            break;

        case NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_LTE_LOST;
            break;

        case NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SLEEP_TIMER_EXPIRED;
            break;

        case NAS_MSCC_SYS_ACQ_SCENE_SYS_CFG_SET:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SYS_CFG_SET;
            break;


        case NAS_MSCC_SYS_ACQ_SCENE_LTE_RF_AVAILABLE:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_LTE_RF_AVAILABLE;
            break;

        case NAS_MSCC_SYS_ACQ_SCENE_HRPD_RF_AVAILABLE:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_HRPD_RF_AVAILABLE;
            break;

        case NAS_MSCC_SYS_ACQ_SCENE_MO_TRIGGER:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_MO_TRIGGER;
            break;

        case NAS_MSCC_SYS_ACQ_SCENE_LTE_NOT_AVAILABLE:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_LTE_NOT_AVAILABLE;
            break;

        default:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_BUTT;
            break;
    }

}


/*****************************************************************************
 函 数 名  : NAS_MSCC_GetAllowedSrchLtePriClassWith1xLocInfo
 功能描述  : 用1x位置信息取得ltepriclass及是否允许搜lte的标志位

 输入参数  : pst1xSysSrvInfoInd 1x系统服务信息
 输出参数  : penLtePriClass   lte的priclass
 返 回 值  : VOS_FALSE:不允许搜lte
             VOS_TRUE: 允许搜lte
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年09月18日
   作    者   : y00346957
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetAllowedSrchLtePriClassWith1xLocInfo(
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU               *pst1xSysSrvInfoInd,
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8            *penLtePriClass
)
{
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                  st1xInputInfo;
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                        stMsplList;
    VOS_UINT8                                               uc1xIndex;
    NAS_MSCC_MSPL_ID_STRU                                  *pstInMsplTable;

    PS_MEM_SET(&st1xInputInfo, 0x00, sizeof(NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU));
    PS_MEM_SET(&stMsplList, 0x00, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    st1xInputInfo.ulMcc         = pst1xSysSrvInfoInd->stSysSrvInfo.stServiceInfo.ulMcc;
    st1xInputInfo.ulMnc         = pst1xSysSrvInfoInd->stSysSrvInfo.stServiceInfo.usMnc;
    st1xInputInfo.ucIsMccValid  = VOS_TRUE;
    st1xInputInfo.ucIsMncValid  = VOS_TRUE;
    st1xInputInfo.usSid         = pst1xSysSrvInfoInd->stSysSrvInfo.usSid;
    st1xInputInfo.usNid         = pst1xSysSrvInfoInd->stSysSrvInfo.usNid;
    st1xInputInfo.enPriClassCdma20001x  = pst1xSysSrvInfoInd->stSysSrvInfo.en1xPriClass;
    st1xInputInfo.enPriClassCdma2000Ai  = pst1xSysSrvInfoInd->stSysSrvInfo.enAIPriClass;

    /* 1x无服务则认为LTE允许搜索any网络 */
    if (NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE == pst1xSysSrvInfoInd->stSysSrvInfo.enServiceStatus)
    {
        *penLtePriClass  = NAS_MSCC_PIF_PLMN_PRIORITY_ANY;

        return VOS_TRUE;
    }

    pstInMsplTable= NAS_MSCC_GetMatchedMsplTableBy1xLocInfo(&st1xInputInfo, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR);

    if (VOS_NULL_PTR == pstInMsplTable)
    {
        *penLtePriClass = NAS_MSCC_PIF_PLMN_PRIORITY_ANY;

        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MSCC_GetMsplSysListBy1xLoc(&st1xInputInfo, &stMsplList))
    {
        /* 获取mspl表失败，lte的priclass为any */
        *penLtePriClass = NAS_MSCC_PIF_PLMN_PRIORITY_ANY;

        return VOS_TRUE;
    }

    /* 如果mspl表中找不到1x的index,则lte没有priclass没有限定 */
    if (VOS_FALSE == NAS_MSCC_Get1xMatchedMsplRecIndex(&st1xInputInfo, pstInMsplTable, &uc1xIndex))
    {
        *penLtePriClass = NAS_MSCC_PIF_PLMN_PRIORITY_ANY;

        return VOS_TRUE;
    }

    /* mspl表中，没有lte记录或者lte的优先级低于1x */
    if (VOS_FALSE == NAS_MSCC_GetLtePriClassInMsplListWith1xIndex(&stMsplList, penLtePriClass, uc1xIndex))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetLtePriClassInMsplListWith1xIndex
 功能描述  : 基于1xIndex取得lte的priclass
 输入参数  : pstMsplList: MSPL列表
             uc1xIndex:   1x系统的下标
 输出参数  : penLtePriClass: 匹配Lte且优先级大于等于1x的prioClass
 返 回 值  : vos_ture:存在lte网络优先级不小于1x
             vos_false:不存在在lte网络优先级不小于1x

 修改历史      :
  1.日    期   : 2015年9月18日
    作    者   : y00346957
    修改内容   : 新生成函数
  2.日    期   : 2015年12月10日
    作    者   : y00346957
    修改内容   : DTS2015120901925 修改，在MSPL表中lte优先级大于1x且对lte限定最低的priclass
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetLtePriClassInMsplListWith1xIndex(
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstMsplList,
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8            *penLtePriClass,
    VOS_UINT8                                               uc1xIndex
)
{
    NAS_MSCC_MSPL_SYS_INFO_STRU                            *pstMsplSysInfo;
    VOS_UINT8                                               ucIndex;
    VOS_UINT8                                               ucRetBefore1x;
    VOS_UINT8                                               ucRetBehind1x;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enLtePriClass;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enTempLtePriClass;
    VOS_UINT8                                               ucIsExistLteInMspl;

    ucIsExistLteInMspl  = VOS_FALSE;
    ucRetBefore1x       = VOS_FALSE;
    ucRetBehind1x       = VOS_FALSE;
    enLtePriClass       = NAS_MSCC_PIF_PLMN_PRIORITY_HOME;
    enTempLtePriClass   = NAS_MSCC_PIF_PLMN_PRIORITY_BUTT;

    /* 遍历mspl表，看是否有lte的记录 */
    for (ucIndex = 0; ucIndex < pstMsplList->ucSysCount; ucIndex++)
    {
        pstMsplSysInfo = &(pstMsplList->astSysList[ucIndex]);

        if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI == pstMsplSysInfo->enSysType)
         || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE == pstMsplSysInfo->enSysType))
        {
            ucIsExistLteInMspl = VOS_TRUE;
            break;
        }
    }

    /* mspl中没有lte，则不搜lte */
    if (VOS_FALSE == ucIsExistLteInMspl)
    {
        return VOS_FALSE;
    }

    /* 遍历下标小于 1xIndex的记录,寻找大于或等于1x优先级的lte的priclass */
    for (ucIndex = 0; ucIndex < uc1xIndex; ucIndex++)
    {
        pstMsplSysInfo = &(pstMsplList->astSysList[ucIndex]);

        if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI == pstMsplSysInfo->enSysType)
         || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE     == pstMsplSysInfo->enSysType))
        {
            enTempLtePriClass = NAS_MSCC_ConvertMsplPriClassToPIfFormat(pstMsplSysInfo->enPriClass);

            /* 寻找限定最低的lte的priclass，eg:如果存在priclass分别为home和any的lte的记录，则lte的priclass为any */
            if ((enTempLtePriClass >= enLtePriClass) && (NAS_MSCC_PIF_PLMN_PRIORITY_BUTT != enTempLtePriClass))
            {
                enLtePriClass = enTempLtePriClass;
                ucRetBefore1x = VOS_TRUE;
            }
        }
    }

    /* 基于1xIndex取得1x记录后面的lte的priclass */
    ucRetBehind1x = NAS_MSCC_GetLtePriClassInMsplListBehind1xIndex(pstMsplList, &enLtePriClass, uc1xIndex);

    if ((VOS_TRUE == ucRetBefore1x) || (VOS_TRUE == ucRetBehind1x))
    {
        *penLtePriClass = enLtePriClass;

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetLtePriClassAfter1xIndex
 功能描述  : 基于1xIndex取得1x记录后面的lte的priclass
 输入参数  : pstMsplList: MSPL列表
             uc1xIndex:   1x系统的下标
 输出参数  : penLtePriClass:lte priclass
 返 回 值  : vos_ture:存在1x记录后面的lte网络优先级不小于1x
             vos_false:不存在1x记录后面的lte网络优先级不小于1x

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : y00346957
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetLtePriClassInMsplListBehind1xIndex(
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstMsplList,
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8            *penLtePriClass,
    VOS_UINT8                                               uc1xIndex
)
{
    VOS_UINT8                                               ucIndex;
    NAS_MSCC_MSPL_SYS_INFO_STRU                            *pstMsplSysInfo;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enLtePriClass;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enTempLtePriClass;
    VOS_UINT8                                               ucRet;

    enLtePriClass       = *penLtePriClass;
    enTempLtePriClass   = NAS_MSCC_PIF_PLMN_PRIORITY_BUTT;
    ucRet               = VOS_FALSE;

     /* 遍历下标大于等于1x下标，找到lte系统，判断1x下标到lte下标之间有没有syspri为more的 */
    for (ucIndex = uc1xIndex; ucIndex < pstMsplList->ucSysCount; ucIndex++)
    {
        pstMsplSysInfo = &(pstMsplList->astSysList[ucIndex]);

        if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI == pstMsplSysInfo->enSysType)
         || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE     == pstMsplSysInfo->enSysType))
        {
             enTempLtePriClass = NAS_MSCC_ConvertMsplPriClassToPIfFormat(pstMsplSysInfo->enPriClass);

            /* 寻找限定最低的lte的priclass，eg:如果存在priclass分别为home和any的lte的记录，则lte的priclass为any */
            if ((enTempLtePriClass >= enLtePriClass) && (NAS_MSCC_PIF_PLMN_PRIORITY_BUTT != enTempLtePriClass))
            {
                enLtePriClass = enTempLtePriClass;
                ucRet         = VOS_TRUE;
            }
        }

        /* 在lte网络前存在sys pri为more的系统 */
        if (NAS_MSCC_MSPL_SYS_PRI_MORE == pstMsplSysInfo->enSysPri)
        {
            break;
        }
    }

    *penLtePriClass = enLtePriClass;

    return ucRet;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_GetPrefRatWithNoCardInitSearchLocInfo
 功能描述  : 根据无卡初搜位置信息，查找lte或hrpd的优先级。如果返回NAS_MSCC_PRIOR_SYS_BUTT，需要使用last loc info查找lte或hrpd优先级
 输入参数  : VOS_VOID
 输出参数  : VOS_VOID
 返 回 值  : NAS_MSCC_PRIOR_SYS_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月10日
    作    者   : j00354216
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MSCC_PRIOR_SYS_ENUM_UINT8 NAS_MSCC_GetPrefRatWithNoCardInitSearchLocInfo(VOS_VOID)
{
    NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU                  *pstNoCardInitSearchLocInfo = VOS_NULL_PTR;
    NAS_MSCC_MMSS_SYSACQ_CFG_STRU                          *pstMmssSysAcqCfgInfo       = VOS_NULL_PTR;
    NAS_MSCC_PRIOR_SYS_ENUM_UINT8                           enPriSys                   = NAS_MSCC_PRIOR_SYS_BUTT;
    NAS_MSCC_1X_LOC_INFO_STRU                               st1xLocationInfo;
    NAS_MSCC_LTE_LOC_INFO_STRU                              stLteLocationInfo;

    pstNoCardInitSearchLocInfo = NAS_MSCC_GetNoCardInitSearchLocInfoAddr();
    pstMmssSysAcqCfgInfo       = NAS_MSCC_GetMmssSysAcqCfgInfoAddr();

    /* 无卡初搜位置信息只在上电开机时使用，软开机不使用， 上电开机使用后，标志位ucIsLocInfoUsed置为已使用TRUE,
        后续的软开机时，判断标志位，如果为TRUE，就不再使用初搜的位置信息
    */
    if (VOS_TRUE == pstNoCardInitSearchLocInfo->ucIsLocInfoUsed)
    {
        return NAS_MSCC_PRIOR_SYS_BUTT;
    }

    if (VOS_TRUE == pstMmssSysAcqCfgInfo->ucIs1xLocInfoPrefThanLte)
    {
        if (NAS_MSCC_INVALID_SID != pstNoCardInitSearchLocInfo->stInitSearchCdmaLoc.lSid)
        {
            /* 1x无卡初搜位置信息有效，使用1x位置信息查表确定hrpd和lte优先级 */
            PS_MEM_SET(&st1xLocationInfo, 0x00 , sizeof(NAS_MSCC_1X_LOC_INFO_STRU));

            st1xLocationInfo.ulMcc = pstNoCardInitSearchLocInfo->stInitSearchCdmaLoc.ulMcc;
            st1xLocationInfo.ulMnc = NAS_MSCC_INVALID_MNC;
            st1xLocationInfo.usSid = (VOS_UINT16)pstNoCardInitSearchLocInfo->stInitSearchCdmaLoc.lSid;
            st1xLocationInfo.usNid = (VOS_UINT16)pstNoCardInitSearchLocInfo->stInitSearchCdmaLoc.lNid;

            enPriSys = NAS_MSCC_GetPrefRatWith1xLocInfo(&st1xLocationInfo);
        }
        else
        {
            /* 使用last location info确定优先驻留系统 */
            enPriSys = NAS_MSCC_PRIOR_SYS_BUTT;
        }
    }
    else
    {
        if (NAS_MSCC_INVALID_MCC != pstNoCardInitSearchLocInfo->stInitSearchGulLoc.ulMcc)
        {
            /* LTE无卡初搜位置信息有效，使用lte位置信息查表确定lte和hrpd优先级 */
            PS_MEM_SET(&stLteLocationInfo, 0x00 , sizeof(NAS_MSCC_LTE_LOC_INFO_STRU));

            stLteLocationInfo.ulMcc       = pstNoCardInitSearchLocInfo->stInitSearchGulLoc.ulMcc;
            stLteLocationInfo.ulMnc       = pstNoCardInitSearchLocInfo->stInitSearchGulLoc.ulMnc;

            enPriSys = NAS_MSCC_GetPrefRatWithLteLocInfo(&stLteLocationInfo);
        }
        else
        {
            /* 使用last location info确定优先驻留系统 */
            enPriSys = NAS_MSCC_PRIOR_SYS_BUTT;
        }
    }

    return enPriSys;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




