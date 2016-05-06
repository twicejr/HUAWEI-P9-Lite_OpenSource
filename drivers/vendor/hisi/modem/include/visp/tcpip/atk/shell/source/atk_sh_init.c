

#ifdef  __cplusplus
extern "C"{
#endif

#include "tcpip/atk/include/atk_ext.h"

extern struct ComponentInfo m_CompAtkInfo; 

/* Component interface of function */
struct IIF_COMP_ATK_ComIntFUNVtbl          *g_pstShAtkFunVtbl = NULL;
/* Component interface of configration */
struct IIF_COMP_ATK_ComIntCFGVtbl          *g_pstShAtkCfgVtbl = NULL;

ULONG Atk_Init(VOID);

/*structure to hold information for the ATK Application*/
APP_INIT_INFO_S g_stATKAppInfo = 
{
    MID_COMP_ATK,                   /* ulMID */

    "ATK",                          /* szAppName[APP_NAME_MAX_LEN + 1] */
    &m_CompAtkInfo,                 /* pstComponentInfo */

    NULL,                           /* pfTaskEntry */
    "",                             /* szTaskName[APP_TASK_NAME_LEN + 1] */
    0,                              /* ulTaskPriority */
    0,                              /* ulTaskMode */
    0,                              /* ulTaskStackSize */
    {0,0,0,0},                      /* ulTaskArg[APP_TASK_PARA_NUM] */

    (APP_INIT_FUNC)Atk_Init,        /* pfAppInit */
    NULL,                           /* pfMibReg */ 
    NULL,                           /* pfIfnetHotNotifyCB */
    NULL,                           /* pfCfaCB */
    NULL,                           /* ppcExecInfor_EN */
    NULL,                           /* ppcExecInfor_CN */    
    NULL,                           /* ppcExecInfor_EXTD*/
    0,                              /* ulAppIndex */
    0,                              /* ulTaskId */
    0                               /* ulExecInforIndex */
};


ULONG ATK_RegApp ()
{ 
    return SYS_RegAppInfo(&g_stATKAppInfo);
}


ULONG Atk_Init(VOID)
{
    ATK_MOD_INFO_S pstMInfo = {MID_COMP_ATK, 0};
 
    if( VOS_OK != COMP_GetVTable( CID_COMP_ATK, IID_COMP_ATK_INTF_FUN, (LPVOID *)(&g_pstShAtkFunVtbl)))
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }
   
    if( VOS_OK != COMP_GetVTable( CID_COMP_ATK, IID_COMP_ATK_INTF_CFG, (LPVOID *)(&g_pstShAtkCfgVtbl)))
    {    
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    if (VOS_OK != g_pstShAtkCfgVtbl->pfATK_InitCom())
    {       
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    if (VOS_OK != g_pstShAtkCfgVtbl->pfATK_SetModuleInfo(&pstMInfo))
    {       
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }  

    /* Initialize hash table as all NULL. */
    g_pstAttackStatsList = NULL;

    /* Initialize attack configurations. */
    (VOID)TCPIP_Mem_Set((CHAR *)&g_stAttackWarningStatus, 0, sizeof(ATTACK_WARNING_S)); 

    (VOID)TCPIP_Mem_Set((CHAR *)&g_stGlobalAttackStats, 0, sizeof(TCPIP_ATTACKSTAT_S)); 

    /* Create 60 second timer to track malformed packet warning. */
    g_ulATK_Timer = 0;

    /* Initialize attack configurations. */
    g_stAttackCfg.ulAtkSwitch           = ATTACK_SWITCH_RESET;
    g_stAttackCfg.ulAtkWarnMaxThreshold = ATTACK_WARNING_MAX_THRESHOLD;
    g_stAttackCfg.ulAtkWarnMinThreshold = ATTACK_WARNING_MIN_THRESHOLD;
    g_stAttackCfg.ulLargeIcmpMaxSize    = ATTACK_LARGE_ICMP_MAX_LEN;

    return VOS_OK;   
}


#ifdef  __cplusplus
}
#endif

