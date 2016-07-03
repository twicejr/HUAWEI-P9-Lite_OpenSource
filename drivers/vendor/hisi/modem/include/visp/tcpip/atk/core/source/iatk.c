

#ifdef  __cplusplus
extern  "C"{
#endif

#include "tcpip/atk/include/atk_ext.h"

ULONG ATK_QueryInterface(IUnknown *This, COMP_IID iid, LPVOID *ppvObj);
ULONG ATK_InitCom();
ULONG ATK_SetModuleInfo(ATK_MOD_INFO_S *pstMInfo);

/*Component Factory for component */
extern IComponentFactory m_AtkFactory;

ATK_MOD_INFO_S             g_stAtkModInfo;

/*ATK 组件信息 */
ComponentInfo m_CompAtkInfo = 
{
    CID_COMP_ATK,
    "ATK Stat",
    "atk stat",
    { 1, 0, 0, 0 },
    &m_AtkFactory
};


/* functional interface of IP attack component  */
ComponentInfo *g_pCompAtkInfo = &m_CompAtkInfo;

struct IIF_COMP_ATK_ComIntFUNVtbl m_ATKFUNVtbl = 
{
    ATK_QueryInterface,
    ATK_AddAtkStat_PT,
    ATK_AddIcmpJumbogramStat_PT,
    ATK_IfDelete_Notify_PT,
    ATK_IsSwitchOpen
};

/* Component interface of function */
IIF_COMP_ATK_ComIntFUN  g_IComInt_Atk_FUN = 
{
    &m_ATKFUNVtbl
};

struct IIF_COMP_ATK_ComIntCFGVtbl m_ATKCFGVtbl = 
{
    ATK_QueryInterface,
    ATK_InitCom,
    ATK_SetModuleInfo,
    ATK_SetWarningSwitch,
    ATK_SetLargeIcmpLen,
    ATK_GetCfgInfo,
    ATK_GetStats,
    ATK_GetStatsByIf,
    ATK_ClrStatsByIf,
    ATK_ClrStats
};

/* Component interface of configration */
IIF_COMP_ATK_ComIntCFG g_IComInt_Atk_CFG = 
{
    &m_ATKCFGVtbl
};

/* Component interface of function */
ATK_INT_OBJ_S g_stIP_ATK_INT_OBJ = 
{
    &g_IComInt_Atk_FUN,
    &g_IComInt_Atk_CFG,
};


ULONG ATK_QueryInterface(IUnknown *This, COMP_IID iid, LPVOID *ppvObj)
{
    /* SYSTRACE (MID_IP_PP4, IP_PP4_COM, 0, 0, 0, 0); */\

    VOS_DBGASSERT(NULL != ppvObj);  

    if (NULL == ppvObj)
    {
        return VOS_ERR;
    }

    if ((This != (VOID*)&g_IComInt_Atk_FUN) 
        && (This != (VOID*)&g_IComInt_Atk_CFG) 
        )
        
    {
        *ppvObj = NULL;
        return VOS_ERR;
    }

    switch(iid)
    {
        case IID_COMP_ATK_INTF_FUN :
        {
            *ppvObj = (VOID*)&g_IComInt_Atk_FUN;
            break;
        }
        case IID_COMP_ATK_INTF_CFG :
        {
            *ppvObj = (VOID*)&g_IComInt_Atk_CFG;
            break;
        }
        default:
            *ppvObj = NULL;
            return VOS_ERR;
    }

    return VOS_OK;

}


ULONG ATK_InitCom()
{ 

    /* Get Vtable to ifnet module */
    if( VOS_OK != COMP_GetVTable(CID_COMP_IFNET, IID_COMP_IFNET_INTF_FUN, (LPVOID *)(&g_pstAtkIfFunVtbl)))
    {
        return VOS_ERR;
    }
    VOS_DBGASSERT(g_pstAtkIfFunVtbl != NULL);


    return VOS_OK;
}



ULONG ATK_SetModuleInfo(ATK_MOD_INFO_S *pstMInfo)
{
    if( NULL == pstMInfo )
    {
        return VOS_ERR;
    }
    (VOID)TCPIP_Mem_Copy( &g_stAtkModInfo, sizeof(ATK_MOD_INFO_S), pstMInfo, sizeof(ATK_MOD_INFO_S) );
    return VOS_OK;
}

#ifdef  __cplusplus
}
#endif

