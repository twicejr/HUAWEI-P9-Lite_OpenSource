
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "tcpip/atk/include/atk_ext.h"

extern struct IIF_COMP_ATK_ComIntFUNVtbl *g_pstShAtkFunVtbl;
extern struct IIF_COMP_ATK_ComIntCFGVtbl *g_pstShAtkCfgVtbl;


ULONG TCPIP_SetAtkWarningSwitch(ULONG ulSwitch, ULONG ulMaxThreshold, ULONG ulMinThreshold)
{
    ULONG ulReturn = VOS_OK;

    if(NULL == g_pstShAtkCfgVtbl)
    {
        ulReturn = ATK_RET_MODULE_NOT_INIT;

        goto EXIT_LABEL;
    }

    if ((ATTACK_SWITCH_RESET != ulSwitch) && (ATTACK_SWITCH_SET != ulSwitch))
    {        
        ulReturn = ATK_RET_INVALID_SWITCH;

        goto EXIT_LABEL;
    }

    /* Validate threshold values only if switch is set and threshold values are
        non zero. */
    if ((ATTACK_SWITCH_SET == ulSwitch)
        && ((0 != ulMaxThreshold) || (0 != ulMinThreshold)))
    {
        if (ulMinThreshold > ulMaxThreshold)
        {      
            ulReturn = ATK_RET_INVALID_THRESHOLD;

            goto EXIT_LABEL;
        }

        /* Minimum threshold must be greater than zero. */
        if (0 == ulMinThreshold)
        {      
            ulReturn = ATK_RET_INVALID_THRESHOLD;

            goto EXIT_LABEL;
        }
    }

    TCPIP_BEGIN_PT(g_ulSemForTightMods);

    ulReturn = g_pstShAtkCfgVtbl->pfATK_SetWarningSwitch(ulSwitch, ulMaxThreshold, ulMinThreshold);

    TCPIP_END_PT(g_ulSemForTightMods);

EXIT_LABEL:

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_344A, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG, 
        "TCPIP ATK LOG: TCPIP_SetAtkWarningSwitch (%u, %u, %u), return : %d \n",
        ulSwitch, ulMaxThreshold, ulMinThreshold, ulReturn);

    return ulReturn;
}


ULONG TCPIP_SetAtkLargeIcmpLen(ULONG ulMaxSize)
{

    ULONG ulReturn = VOS_OK;

    if (NULL == g_pstShAtkCfgVtbl)
    {
        ulReturn = ATK_RET_MODULE_NOT_INIT;

        goto EXIT_LABEL;
    }

    /* Validate maxlen value. */
    if ((ulMaxSize < ATTACK_LARGE_ICMP_MIN_LEN)
        || (ulMaxSize > ATTACK_LARGE_ICMP_MAX_LEN))
    {      
        ulReturn = ATK_RET_ICMP_MAX_LEN;

        goto EXIT_LABEL;
    }

    TCPIP_BEGIN_PT(g_ulSemForTightMods);

    ulReturn = g_pstShAtkCfgVtbl->pfATK_SetLargeIcmpLen(ulMaxSize);

    TCPIP_END_PT(g_ulSemForTightMods);

EXIT_LABEL:

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_344B, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG, 
        "TCPIP ATK LOG: TCPIP_SetAtkLargeIcmpLen(%u), return : %d \n",
        ulMaxSize, ulReturn, 0, 0);

    return ulReturn;

}


ULONG TCPIP_GetAtkCfgInfo(ATTACK_CFG_INFO_S *pstAtkCfgInfo)
{

    ULONG ulReturn = VOS_OK;

    if (NULL == g_pstShAtkCfgVtbl)
    {
        return ATK_RET_MODULE_NOT_INIT;
    }

    if (NULL == pstAtkCfgInfo)
    {
        return ATK_RET_INPUT_NULL;
    }

    TCPIP_BEGIN_PT(g_ulSemForTightMods);

    ulReturn = g_pstShAtkCfgVtbl->pfATK_GetCfgInfo(pstAtkCfgInfo);

    TCPIP_END_PT(g_ulSemForTightMods);

    return ulReturn;
}


ULONG TCPIP_GetAtkStats(TCPIP_ATTACKSTAT_S *pstAtkStat)
{

    ULONG ulReturn = VOS_OK;

    if (NULL == g_pstShAtkCfgVtbl)
    {
        return ATK_RET_MODULE_NOT_INIT;
    }

    if (NULL == pstAtkStat)
    {
        return ATK_RET_INPUT_NULL;
    }

    TCPIP_BEGIN_PT(g_ulSemForTightMods);

    ulReturn = g_pstShAtkCfgVtbl->pfATK_GetStats(pstAtkStat);

    TCPIP_END_PT(g_ulSemForTightMods);

    return ulReturn;
}



ULONG TCPIP_GetAtkStatsByIf(ULONG ulIfIndex, TCPIP_ATTACKSTAT_S *pstAtkStat)
{

    ULONG ulReturn = VOS_OK;

    if(NULL == g_pstShAtkCfgVtbl)
    {
        return ATK_RET_MODULE_NOT_INIT;
    }

    if (NULL == pstAtkStat)
    {
        return ATK_RET_INPUT_NULL;
    }

    TCPIP_BEGIN_PT(g_ulSemForTightMods);

    if (NULL == IF_GetIfByIndex(ulIfIndex))
    {
        TCPIP_END_PT(g_ulSemForTightMods);
        return ATK_RET_INVALID_IF;
    }

    ulReturn = g_pstShAtkCfgVtbl->pfATK_GetStatsByIf(ulIfIndex, pstAtkStat);

    TCPIP_END_PT(g_ulSemForTightMods);

    return ulReturn;
}


ULONG TCPIP_ClrAtkStatsByIf(ULONG ulIfIndex)
{

    ULONG ulReturn = VOS_OK;

    if(NULL == g_pstShAtkCfgVtbl)
    {
        ulReturn = ATK_RET_MODULE_NOT_INIT;

        goto EXIT_LABEL;
    }

    TCPIP_BEGIN_PT(g_ulSemForTightMods);

    if (NULL == IF_GetIfByIndex(ulIfIndex))
    {
        TCPIP_END_PT(g_ulSemForTightMods);
        return ATK_RET_INVALID_IF;
    }

    ulReturn = g_pstShAtkCfgVtbl->pfATK_ClrStatsByIf(ulIfIndex, ATTACK_STAT_CLEAR);

    TCPIP_END_PT(g_ulSemForTightMods);

EXIT_LABEL:

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_344C, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG, 
            "TCPIP ATK LOG: TCPIP_ClrAtkStatsByIf(%u), return :%d \n",
            ulIfIndex, ulReturn, 0, 0);

    return ulReturn;
}


ULONG TCPIP_ClrAtkStats()
{

    ULONG ulReturn = VOS_OK;

    if(NULL == g_pstShAtkCfgVtbl)
    {
        ulReturn = ATK_RET_MODULE_NOT_INIT;

        goto EXIT_LABEL;
    }

    TCPIP_BEGIN_PT(g_ulSemForTightMods);

    ulReturn = g_pstShAtkCfgVtbl->pfATK_ClrStats();

    TCPIP_END_PT(g_ulSemForTightMods);

EXIT_LABEL:

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_344D, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG, 
            "TCPIP ATK LOG: TCPIP_ClrAtkStats(), return : %d \n",
            ulReturn, 0, 0, 0);

    return ulReturn;
}


ULONG TCPIP_ShowAtkInfo()
{
    ULONG ulReturn = 0;
    TCPIP_ATTACKSTAT_S stAtkStat = {0};

    if(NULL == g_pstShAtkCfgVtbl)
    {
        return ATK_RET_MODULE_NOT_INIT;
    }

    TCPIP_BEGIN_PT(g_ulSemForTightMods);

    ulReturn = g_pstShAtkCfgVtbl->pfATK_GetStats(&stAtkStat);

    TCPIP_END_PT(g_ulSemForTightMods);

    ATK_ShowStats(&stAtkStat);

    return ulReturn;
}


ULONG TCPIP_ShowAtkStatsByIntfName(CHAR *szIfName)
{
    ULONG ulReturn = VOS_OK;
    ULONG ulIfIndex = 0;
    TCPIP_ATTACKSTAT_S stAtkStat = {0};

    if((NULL == g_pstAtkIfFunVtbl) || (NULL == g_pstShAtkCfgVtbl))
    {
        return ATK_RET_MODULE_NOT_INIT;
    }

    if (NULL == szIfName)
    {        
        return ATK_RET_INPUT_NULL;
    }

    if (VOS_OK != g_pstAtkIfFunVtbl->pfIF_GetIfIndexByFullName(szIfName, &ulIfIndex))
    {
        return ATK_RET_INVALID_IF;
    }

    TCPIP_BEGIN_PT(g_ulSemForTightMods);

    ulReturn = g_pstShAtkCfgVtbl->pfATK_GetStatsByIf(ulIfIndex, &stAtkStat);

    TCPIP_END_PT(g_ulSemForTightMods);

    ATK_ShowStats(&stAtkStat);

    return ulReturn;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

