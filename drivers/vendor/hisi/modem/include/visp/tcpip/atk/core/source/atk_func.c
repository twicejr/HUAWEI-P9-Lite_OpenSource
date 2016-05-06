

#ifdef  __cplusplus
extern "C"{
#endif

#include "tcpip/atk/include/atk_ext.h"


VOID ATK_Sock_TimeCallBack(VOID *pArg)
{
    /* Local variable that is passed to TCPIP_WarningOut. */
    ATTACK_WARNING_S stAttackWarning = {0};

    TCPIP_BEGIN_PT(g_ulSemForTightMods);

    /* Compare the malformed packet counter with the max and min threshold and
        raise or cancel warning */
    if (g_stAttackWarningStatus.ulAtkCounts >= g_stAttackCfg.ulAtkWarnMaxThreshold)
    {
        /* Raise the warning if it not is already present */
        if (ATTACK_WARNING_END == g_stAttackWarningStatus.ulWarningType)
        {
            /* Fill warning information. */
            g_stAttackWarningStatus.ulWarningType = ATTACK_WARNING_BEGIN;

            (VOID)TCPIP_Mem_Copy((VOID *)&stAttackWarning, sizeof(ATTACK_WARNING_S),
                                 (VOID *)&g_stAttackWarningStatus, sizeof(ATTACK_WARNING_S));

            /* Raise warning*/
            TCPIP_WarningOut(WARNING_ATTACK, (VOID *)&stAttackWarning);
        }
    }
    else if (g_stAttackWarningStatus.ulAtkCounts < g_stAttackCfg.ulAtkWarnMinThreshold)
    {
        /* Clear the warning if it is already present */
        if (ATTACK_WARNING_BEGIN == g_stAttackWarningStatus.ulWarningType)
        {
            /* Fill warning information. */
            g_stAttackWarningStatus.ulWarningType = ATTACK_WARNING_END;

            stAttackWarning.ulWarningType = ATTACK_WARNING_END;
            stAttackWarning.ulAtkCounts = g_stAttackWarningStatus.ulAtkCounts;

            /* Close the warning*/
            TCPIP_WarningOut(WARNING_ATTACK, (VOID *)&stAttackWarning);
        }
    }

    /* Reset attack warning status. */
    g_stAttackWarningStatus.ulAtkCounts = 0;   
    g_stAttackWarningStatus.ulWarnAtkType = 0; 
    g_stAttackWarningStatus.ulWarnIfIndex = 0;;
    (VOID)TCPIP_Mem_Set((CHAR *)&g_stAttackWarningStatus.stWarnIpHead, 0, sizeof(IP_S));

    TCPIP_END_PT(g_ulSemForTightMods);

    return;
}

/*******************************************************************************
*    Func Name: ATK_AddAtkStat
* Date Created: 2014-08-06
*       Author: a00900892
*  Description: Increment count of an attack type in attack statistics for an
*               interface.
*        Input: ulIfIndex: If index of the incoming interface.
*               ulAttackType: Type of IP attack, one of ENUM_ATKSTATTYPE.
*               pstIp£ºPointer to the IP header of the incoming packet.
*       Output: 
*       Return: VRP_YES: If module not initialized, else VRP_NO.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-06   a00900892               Create
*  2014-08-18   a00900892               Modify (change return type, DTS2014081805831)
*  2014-08-26   a00900892               Modify (for DTS2014082605389)
*
*******************************************************************************/
ULONG ATK_AddAtkStat(ULONG ulIfIndex, ULONG ulAttackType, IP_S *pstIp)
{
    ULONG ulHashIndex = 0;
    ATTACKSTAT_BY_IF_S *pstAttackStatByIf = NULL;

    /* Do not add stats if ulAtkSwitch is not set. */
    if (ATTACK_SWITCH_SET != g_stAttackCfg.ulAtkSwitch)
    {
        return VRP_YES;
    }

    /* Pointer to IP header cannot be NULL. */
    if (NULL == pstIp)
    {
        return VRP_NO;
    }

    /* Get hash index using the interface index;*/
    ulHashIndex = HASH_FUN(ulIfIndex);

    /* Access the attack stat by interface structure from the hash table. */
    pstAttackStatByIf = g_pstAttackStatsList[ulHashIndex];

    /* Search in hash list for the entry with same IfIndex. */
    while (NULL != pstAttackStatByIf)
    {
        /* If IfIndex match, break the loop. */
        if (ulIfIndex == pstAttackStatByIf->ulIfIndex)
        {
            break;
        }

        pstAttackStatByIf = pstAttackStatByIf->pst_NextStat;
    }

    /* If entry is not present in list, then create and add infront of hash list. */
    if (NULL == pstAttackStatByIf)
    {
        /* Allocate and initialize memory for new entry. */
        pstAttackStatByIf = (ATTACKSTAT_BY_IF_S *)TCPIP_Malloc(
                                        MID_COMP_ATK | SID_COMP_ATK_LIST_ENTRY_S,
                                        sizeof(ATTACKSTAT_BY_IF_S));
        if (NULL == pstAttackStatByIf)
        {
            TCPIP_LOG_FIXLEN(RUN_LOG_VISP_344F, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN, 
                "TCPIP ATK LOG: ATK_AddAtkStat (%u, %d), malloc fail \n",
                ulIfIndex, ulAttackType, 0, 0);

            return VRP_NO;
        }

        (VOID)TCPIP_Mem_Set((CHAR *)pstAttackStatByIf, 0, sizeof(ATTACKSTAT_BY_IF_S));

        pstAttackStatByIf->ulIfIndex    = ulIfIndex;
        pstAttackStatByIf->pst_NextStat = g_pstAttackStatsList[ulHashIndex];

        g_pstAttackStatsList[ulHashIndex] = pstAttackStatByIf;
    }

    /* Increment IP attact statistics for the specified attack type. */
    switch (ulAttackType)
    {
        case ATK_STAT_TYPE_HEAD_ERR:
            pstAttackStatByIf->stAttackStats.ulHeadErrorStat++;
            g_stGlobalAttackStats.ulHeadErrorStat++;
            break;

        case ATK_STAT_TYPE_INVALID_IPOPT:
            pstAttackStatByIf->stAttackStats.ulIpOptErrStat++;
            g_stGlobalAttackStats.ulIpOptErrStat++;
            break;

        case ATK_STAT_TYPE_UNKOWNPRRO:
            pstAttackStatByIf->stAttackStats.ulunkownProStat++;
            g_stGlobalAttackStats.ulunkownProStat++;
            break;

        case ATK_STAT_TYPE_SPOOF:
            pstAttackStatByIf->stAttackStats.ulIpSpoofStat++;
            g_stGlobalAttackStats.ulIpSpoofStat++;
            break;

        case ATK_STAT_TYPE_REASS_TIMEOUT:
            pstAttackStatByIf->stAttackStats.ulIpReassTimeOutStat++;
            g_stGlobalAttackStats.ulIpReassTimeOutStat++;
            break;

        case ATK_STAT_TYPE_REASS_ERR:
            pstAttackStatByIf->stAttackStats.ulIpReassErrStat++;
            g_stGlobalAttackStats.ulIpReassErrStat++;
            break;

        case ATK_STAT_TYPE_INVALID_TCP:
            pstAttackStatByIf->stAttackStats.ulTcpErrorStat++;
            g_stGlobalAttackStats.ulTcpErrorStat++;
            break;

        case ATK_STAT_TYPE_LAND:
            pstAttackStatByIf->stAttackStats.ulLandAtkStat++;
            g_stGlobalAttackStats.ulLandAtkStat++;
            break;

        case ATK_STAT_TYPE_WINNUKE:
            pstAttackStatByIf->stAttackStats.ulWinnukeStat++;
            g_stGlobalAttackStats.ulWinnukeStat++;
            break;

        case ATK_STAT_TYPE_ICMP_LARGE:
            pstAttackStatByIf->stAttackStats.ulIcmpLargeStat++;
            g_stGlobalAttackStats.ulIcmpLargeStat++;
            break;

        default:

            /* Wrong attack type, return.*/
            return VRP_NO;
    }

    /* Update warning status structure. */
    g_stAttackWarningStatus.ulAtkCounts++;

    if ((g_stAttackWarningStatus.ulAtkCounts >= g_stAttackCfg.ulAtkWarnMaxThreshold)
        && (ATTACK_WARNING_END == g_stAttackWarningStatus.ulWarningType))
    {
        g_stAttackWarningStatus.ulWarnAtkType = ulAttackType;
        g_stAttackWarningStatus.ulWarnIfIndex = ulIfIndex;

        (VOID)TCPIP_Mem_Copy(&g_stAttackWarningStatus.stWarnIpHead, sizeof(IP_S),
                                pstIp, sizeof(IP_S));
    }

    return VRP_NO;
}


ULONG ATK_AddIcmpJumbogramStat(ULONG ulIfIndex, ULONG ulLen, IP_S *pstIp)
{

    /* Do not add stats if ulAtkSwitch is not set. */
    if (ATTACK_SWITCH_SET != g_stAttackCfg.ulAtkSwitch)
    {
        return VOS_OK;
    }

    /* Pointer to IP header cannot be NULL. */
    if (NULL == pstIp)
    {
        return VOS_OK;
    }

    /* No need to drop the packet or increase attack count. */
    if (ulLen <= g_stAttackCfg.ulLargeIcmpMaxSize)
    {
        return VOS_OK;
    }

    /* Add statistics of type ATK_STAT_TYPE_ICMP_LARGE */
    (VOID)ATK_AddAtkStat(ulIfIndex, ATK_STAT_TYPE_ICMP_LARGE, pstIp);

    return VOS_ERR;
}


ULONG ATK_DelAllStats()
{

    ULONG ulHashIndex = 0;
    ATTACKSTAT_BY_IF_S *pstAttackStatByIf = NULL;

    /* Free all entries from hash table. */
    for (; ulHashIndex < ATTACK_HASH_LEN; ulHashIndex++)
    {
        /* Traverse hash list and free all entries. */
        while (NULL != g_pstAttackStatsList[ulHashIndex])
        {
            pstAttackStatByIf = g_pstAttackStatsList[ulHashIndex];

            g_pstAttackStatsList[ulHashIndex] = pstAttackStatByIf->pst_NextStat;

            (VOID)TCPIP_Free((VOID *)pstAttackStatByIf);
        }

        g_pstAttackStatsList[ulHashIndex] = NULL;
    }

    return VOS_OK;
}


VOID ATK_IfDelete_Notify(ULONG ulIfIndex)
{

    (VOID)ATK_ClrStatsByIf(ulIfIndex, ATTACK_STAT_FREE);

    return;
}


ULONG ATK_AddAtkStat_PT(ULONG ulIfIndex, ULONG ulAttackType, IP_S *pstIp)
{

    ULONG ulReturn = VOS_OK;

    TCPIP_BEGIN_PT(g_ulSemForTightMods);

    ulReturn = ATK_AddAtkStat(ulIfIndex, ulAttackType, pstIp);

    TCPIP_END_PT(g_ulSemForTightMods);

    return ulReturn;
}


ULONG ATK_AddIcmpJumbogramStat_PT(ULONG ulIfIndex, ULONG ulLen, IP_S *pstIp)
{

    ULONG ulReturn = VOS_OK;

    TCPIP_BEGIN_PT(g_ulSemForTightMods);

    ulReturn = ATK_AddIcmpJumbogramStat(ulIfIndex, ulLen, pstIp);

    TCPIP_END_PT(g_ulSemForTightMods);

    return ulReturn;
}


VOID ATK_IfDelete_Notify_PT(ULONG ulIfIndex)
{

    TCPIP_BEGIN_PT(g_ulSemForTightMods);

    ATK_IfDelete_Notify(ulIfIndex);

    TCPIP_END_PT(g_ulSemForTightMods);

    return;
}


ULONG ATK_IsSwitchOpen()
{

    if (ATTACK_SWITCH_SET == g_stAttackCfg.ulAtkSwitch)
    {
        return VRP_YES;
    }

    return VRP_NO;
}

#ifdef  __cplusplus
}
#endif

