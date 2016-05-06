/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              fib4c_type.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB4
* Date Created: 2003-07-08
*       Author: Zhang Hongyan
*  Description: Contains the structure definitions of messages and data
*               used in FIB table
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-07-08   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00646
*  2006-04-21   Jiangtao                Adjust for D00859 
*  2006-11-10   zhoutong(43740)         规范性整改
*
*******************************************************************************/
 
#ifdef  __cplusplus
extern  "C"{
#endif
 
#ifndef _FIB4C_TYPE_H
#define _FIB4C_TYPE_H

/* Return values while Fectching FIB data */
#define FIB4_RT_START  VOS_ERR + 1
#define FIB4_RT_END    VOS_ERR + 2
#define FIB4_ERR_SCAN  VOS_ERR + 3
#define FIB4_ERR_SCAN_2  VOS_ERR + 4
#define FIB4_ERR_SCAN_3  VOS_ERR + 5
#define FIB4_ERR_SCAN_4  VOS_ERR + 6


/*注意:
如果修改错误码，请同步修改sfib_sh_main.c文件中的
CHAR *Inf_IP_Fib4C_En[]描述信息*/
/* Enumerations which index into the Debug and information message table */
typedef enum FIB4C_DEBUG_INFO_Etag
{
    FIB4_INFO_CORE_CALLBACK = 1,     /*1 */
    FIB4_INFO_ROUTE_ADD,             /*2 */
    FIB4_INFO_ROUTE_DELETE,          /*3 */
    FIB4_INFO_ROUTE_REFRESH,         /*4 */
    FIB4_INFO_ROUTE_CLEAR_ZONE,      /*5 */
    FIB4_INFO_UPDATE_FIB_CACHE,      /*6 */
    FIB4_INFO_REG_CACHE,             /*7 */
    FIB4_INFO_UPDATE_CACHE,          /*8 */
    FIB4_INFO_CONTR_INIT,            /*9 */
    FIB4_INFO_MODULE_INIT,           /*10*/
    FIB4_INFO_REG_SH,                /*11*/
    FIB4_INFO_ROUTE_INIT,            /*12*/
    FIB4_INFO_DLL_FIRST,             /*13*/
    FIB4_INFO_DLL_LAST,              /*14*/
    FIB4_INFO_BAL_ROUTE_REFRESHED,   /*15*/
    FIB4_INFO_BAL_ROUTE_ADDED,       /*16*/
    FIB4_INFO_EXT_NODE_ADDED,        /*17*/
    FIB4_INFO_EXT_NODE_EXIST,        /*18*/
    FIB4_INFO_FST_DLL_ELMNT_RMVD,    /*19*/
    FIB4_INFO_LST_DLL_ELMNT_RMVD,    /*20*/
    FIB4_INFO_DLL_ELMNT_RMVD,        /*21*/
    FIB4_INFO_BAL_RT_ELMNT_RMVD,     /*22*/
    FIB4_INFO_NON_BAL_RT_RMVD,       /*23*/
    FIB4_INFO_BAL_RT_RMVD,           /*24*/
    FIB4_INFO_WTLST_REG,             /*25*/
    FIB4_INFO_WTLST_UNREG,           /*26*/
    FIB4_INFO_WTLST_END,             /*27*/
    FIB4_INFO_RTLIST_CREATE,         /*28*/

    FIB4_INFO_DBG_ENBL,              /*29*/
    FIB4_INFO_DBG_DSBL,              /*30*/
    FIB4_INFO_OPEN_RT,               /*31*/
    FIB4_INFO_GET_BULK_DATA,         /*32*/

    FIB4_INFO_DIS_DBG_REG,           /*33*/
    FIB4_INFO_DBG_CLI_RCVD,          /*34*/
    FIB4_INFO_DSP_CLI_RCVD,          /*35*/
    FIB4_INFO_DST_ADDR_CAT,          /*36*/
    FIB4_INFO_NXTHOP_ADDR_CAT,       /*37*/
    FIB4_INFO_FLAG_CAT,              /*38*/
    FIB4_INFO_TIME_CAT,              /*39*/
    FIB4_INFO_INF_INFO_CAT,          /*40*/
    FIB4_INFO_SND_DBG_TO_IO,         /*41*/
    FIB4_INFO_BEST_SEARCH,           /*42*/
    FIB4_INFO_DSP_IO_BRD,            /*43*/
    FIB4_INFO_DSP_MAIN_BRD,          /*44*/

    FIB4_ERR_INVALID_INPUT,          /*45*/
    FIB4_ERR_CORE_CALLBACK,          /*46*/
    FIB4_ERR_ROUTE_ADD,              /*47*/
    FIB4_ERR_ROUTE_DELETE,           /*48*/
    FIB4_ERR_ROUTE_REFRESH,          /*49*/

    FIB4_ERR_ROUTE_CLEAR_ZONE,       /*50*/
    FIB4_ERR_MESSAGE_TYPE,           /*51*/
    FIB4_ERR_ROUTE_BALANCE,          /*52*/
    FIB4_ERR_GET_BULK_FIB,           /*53*/

    FIB4_ERR_ALLOC_FAIL,             /*54*/
    FIB4_ERR_NODE_FAIL,              /*55*/
    FIB4_ERR_NO_BAL_ENTRY,           /*56*/
    FIB4_ERR_SEARCH_FAIL,            /*57*/
    FIB4_ERR_SCAN_FAIL,              /*58*/
    FIB4_ERR_WTLST_REG,              /*59*/
    FIB4_ERR_WTLST_UNREG,            /*60*/
    FIB4_ERR_WTLST_GET,              /*61*/
    FIB4_ERR_MOD_INFO,               /*62*/
    FIB4_ERR_COM_ACT,                /*63*/
    FIB4_ERR_SND_DBG_FAIL            /*64*/

}FIB4C_DEBUG_INFO_E;



/*  Serves as main data store for maintaining IPv4 FIB entries. This data structure has to be 
    initialized by attaching the appropriate implementation functions during initialization.  
    This is maintained by FIB4Container.    For Radix implementation using VOS APIs for 
    IPv4 Radix tree, The  route entries are defined using the data structure of type 
    VOS_RDX4_EXTNODE and tree is built using  data structure of type 
    VOS_RDX4_INTNODE.  (to as described in above section, i.e VOID is replaced with 
    these radix data structure definitions) */
typedef struct tagIP4_FIBTable
{
    VOID* pvHandleToCurTable;   /* Handle to table, can be a radix internal node or some other */
    ULONG ulNoOf_routesInTable; /* number of routes in IPv4-FIB Table */
    ULONG ulFutureUse1;
    ULONG ulFutureUse2;   
}IP4_FIBTable;

typedef struct tagIP4_FIBTable_AccessFuns
{
    /* The following are Function pointers which needs to be linked to appropriate 
    implementation functions, during Module Initialization */
    ULONG (*pfInitRoute) ();
    ULONG (*pfAddRoute) ( RTMSG4_S * pstRouteEntry );
    ULONG (*pfDeleteRoute) (RTMSG4_S * pstRouteEntry);
    ULONG (*pfSearchBest) (ROUTE4_S * pstRoute4,BOOL_T bEnableRoutBal);

    ULONG (*pfClearZone) ();
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG (*pfClearSpecZone) (USHORT usZoneID);
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

    /* End of modification */
    ULONG (*pfGetBulkFIBData) (ULONG  ulWaitlistIndex,
                               ULONG ulNumOfEntryWanted,
                               ULONG *pulNumOfEntryReturn,
                               RT4_ENTRY_S **pastFIBData );
    ULONG (*pfIsBalancedRoute) ( RTMSG4_S * pstRtMsg, 
                                 ULONG * pulBalCount, 
                                 SLL_S *pstBalRoutList );
    ULONG (*pfRefreshRouteByIntfPrio) (USHORT usZoneID,
                                       ULONG ulIfIndex);
    /* The below ones are right now not used, left here for future ref, to use if any */
    ULONG  (*pfGetFirst) (VOID *pvRoot, VOID *pvRouteEntryGot);
    ULONG  (*pfGetNext) (VOID *pvCurEntry, VOID *pvRouteEntryGot);
    ULONG  (*pfGetNextExt) (ULONG* pulWaitlistIndex,
                            ULONG ulRtSetCnt,               
                            SLL_S *pstRtList);
    ULONG (*pfDeleteAll) (VOID* pvInfo1);
}IP4_FIBTable_AccessFuns_S;

/*  This is a structure of callback function details. This is used during registering the callback
    functions of shell for writing into Message Queue, Reading from Message Queue by Core, 
    also writing timer  */
typedef struct tagIP4_FIBContainer_SHELL_EV_CALLBACUP_SET
{
    /* Printing/Sending debug info */
    VOID (*pfFIB4C_ShellDebugOut) (FIB4C_DEBUG_INFO_E eState, char *pBuf, ULONG ulLen);     
}IP4_FIBContainer_SHELL_EV_CALLBACUP_SET_S;

/*  This is a structure of callback function details. This is used during registering the callback 
    function for downloading FIB to FE, by FE   */
typedef struct tagFIB4_CACHE_UPDATE_FUNC_SET_S
{
    /* modified by Guru, for Cache implementation, 28-11-2003 */
    ULONG (*pfUpdate) ( RTMSG4_S *pstRTMsg, ULONG ulBaseCacheIndex, ULONG ulCurrCacheIndex );
    ULONG (*pfAllocValid) ( ROUTE4_S *pstRoute4 );
    ULONG (*pfGetAvailCacheIndex) (USHORT usZoneID);
    /* modificatin ends */
}FIB4_CACHE_UPDATE_FUNC_SET_S;

/*  For shell to initilize module specific information of core, such as IPC 
       queue ID, for sending and receiving IPC messages, this info is set in core, when apprpriate
       function is invoked by FIB4 Init (shell part) during initilization during nit call by VRP root */
typedef struct tagIP4_FIBContainer_MOD_INFO
{
    ULONG ulModID;
    ULONG ulSubModID;
    ULONG ulLocalIPC_TID;
    ULONG ulPeerIPC_TID;
}IP4_FIBContainer_MOD_INFO_S;



#endif

#ifdef  __cplusplus
}
#endif

