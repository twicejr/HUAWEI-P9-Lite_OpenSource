/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              fib6c_type.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB6
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
*  2006-03-30   Jiangtao                Adjust for D00645
*  2006-04-21   Jiangtao                Adjust for D00858 
*
*******************************************************************************/
 
#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _FIB6C_TYPE_H
#define _FIB6C_TYPE_H

#include "vos/vospubh/utlsll.h"

#define FIB6_RT_START           VOS_ERR + 1
#define FIB6_RT_END             VOS_ERR + 2
#define FIB6_ERR_SCAN           VOS_ERR + 3
#define RM_ERR_SCAN             VOS_ERR + 4

/* Enumerations which index into the Debug and information message table */
/*注意:
如果修改错误码，请同步修改Sfib6_sh_main.c文件中的
CHAR *Inf_IP_Fib6C_En[]描述信息*/
typedef enum FIB6C_DEBUG_INFO_Etag
{
    FIB6_INFO_CORE_CALLBACK = 1,    /*01*/   
    FIB6_INFO_ROUTE_ADD,            /*02*/
    FIB6_INFO_ROUTE_DELETE,         /*03*/
    FIB6_INFO_ROUTE_MODIFY,         /*04*/
    FIB6_INFO_ROUTE_CLEAR_ZONE,     /*05*/
    FIB6_INFO_UPDATE_FIB_CACHE,     /*06*/
    FIB6_INFO_REG_CACHE,            /*07*/
    FIB6_INFO_UPDATE_CACHE,         /*08*/
    FIB6_INFO_CONTR_INIT,           /*09*/
    FIB6_INFO_MODULE_INIT,          /*10*/
    FIB6_INFO_REG_SH,               /*11*/
    FIB6_INFO_ROUTE_INIT,           /*12*/
    FIB6_INFO_DLL_FIRST,            /*13*/
    FIB6_INFO_DLL_LAST,             /*14*/
    FIB6_INFO_BAL_ROUTE_MODIFIED,   /*15*/
    FIB6_INFO_BAL_ROUTE_ADDED,      /*16*/
    FIB6_INFO_EXT_NODE_ADDED,       /*17*/
    FIB6_INFO_EXT_NODE_EXIST,       /*18*/
    FIB6_INFO_FST_DLL_ELMNT_RMVD,   /*19*/
    FIB6_INFO_LST_DLL_ELMNT_RMVD,   /*20*/
    FIB6_INFO_DLL_ELMNT_RMVD,       /*21*/
    FIB6_INFO_BAL_RT_ELMNT_RMVD,    /*22*/
    FIB6_INFO_NON_BAL_RT_RMVD,      /*23*/
    FIB6_INFO_BAL_RT_RMVD,          /*24*/
    FIB6_INFO_WTLST_REG,            /*25*/
    FIB6_INFO_WTLST_UNREG,          /*26*/
    FIB6_INFO_WTLST_END,            /*27*/
    FIB6_INFO_RTLIST_CREATE,        /*28*/

    FIB6C_INFO_DBG_ENBL,            /*29*/
    FIB6_INFO_DBG_DSBL,             /*30*/
    FIB6_INFO_OPEN_RT,              /*31*/
    FIB6_INFO_GET_BULK_DATA,        /*32*/

    FIB6_INFO_DIS_DBG_REG,          /*33*/
    FIB6_INFO_DBG_CLI_RCVD,         /*34*/
    FIB6_INFO_DSP_CLI_RCVD,         /*35*/
    FIB6_INFO_DST_ADDR_CAT,         /*36*/
    FIB6_INFO_NXTHOP_ADDR_CAT,      /*37*/
    FIB6_INFO_FLAG_CAT,             /*38*/
    FIB6_INFO_TIME_CAT,             /*39*/
    FIB6_INFO_INF_INFO_CAT,         /*40*/
    FIB6_INFO_SND_DBG_TO_IO,        /*41*/
    FIB6_INFO_DSP_IO_BRD,           /*42*/
    FIB6_INFO_DSP_MAIN_BRD,         /*43*/

    FIB6_ERR_INVALID_INPUT,         /*44*/
    FIB6_ERR_CORE_CALLBACK,         /*45*/
    FIB6_ERR_ROUTE_ADD,             /*46*/
    FIB6_ERR_ROUTE_DELETE,          /*47*/
    FIB6_ERR_ROUTE_MODIFY,          /*48*/
    FIB6_ERR_ROUTE_CLEAR_ZONE,      /*49*/
    FIB6_ERR_MESSAGE_TYPE,          /*50*/
    FIB6_ERR_ROUTE_BALANCE,         /*51*/
    FIB6_ERR_BEST_SEARCH,           /*52*/
    FIB6_ERR_GET_BULK_FIB,          /*53*/
    FIB6_ERR_ALLOC_FAIL,            /*54*/
    FIB6_ERR_NODE_FAIL,             /*55*/
    FIB6_ERR_NO_BAL_ENTRY,          /*56*/
    FIB6_ERR_SEARCH_FAIL,           /*57*/
    FIB6_ERR_SCAN_FAIL,             /*58*/
    FIB6_ERR_WTLST_REG,             /*59*/
    FIB6_ERR_WTLST_UNREG,           /*60*/
    FIB6_ERR_WTLST_GET,             /*61*/
    FIB6_ERR_MOD_INFO,              /*62*/
    FIB6_ERR_COM_ACT,               /*63*/
    FIB6_ERR_SND_DBG_FAIL,          /*64*/

}FIB6C_DEBUG_INFO_E;

/*  Serves as main data store for maintaining IPv6 FIB entries. This data structure has to be 
    initialized by attaching the appropriate implementation functions during initialization.  
    This is maintained by FIB6Container.    For Radix implementation using VOS APIs for 
    IPv6 Radix tree, The  route entries are defined using the data structure of type 
    VOS_RDX6_EXTNODE and tree is built using  data structure of type 
    VOS_RDX6_INTNODE.  (to as described in above section, i.e VOID is replaced with 
    these radix data structure definitions) */
typedef struct tagIP6_FIBTable
{
     VOID*  pvHandleToCurTable;      /* Handle to table, can be a radix internal node or some other */
     ULONG  ulNoOf_routesInTable;    /* number of routes in IPv6-FIB Table */
     ULONG  ulFutureUse1;
     ULONG  ulFutureUse2;
}IP6_FIBTable;

typedef struct tagIP6_FIBTable_AccessFuns
{
    /* The following are Function pointers which needs to be linked to appropriate 
       implementation functions, during Module Initialization */
    ULONG (*pfInitRoute) ();
    ULONG (*pfAddRoute) ( RTMSG6_S * pstRouteEntry );

    ULONG (*pfDeleteRoute) (RTMSG6_S * pstRouteEntry);
    ULONG (*pfSearchBest) (ROUTE6_S * pstRoute6, BOOL_T bEnableRouteBal);
    ULONG (*pfModifyRoute) (RTMSG6_S * pstRouteEntry);

    ULONG (*pfClearZone) (USHORT    usZoneID);

    ULONG (*pfGetBulkFIBData) (USHORT usZoneID,
                               UINTPTR  ulWaitlistIndex,
                               ULONG ulNumOfEntryWanted,
                               ULONG *pulNumOfEntryReturn,
                               RT6_ENTRY_S **pastFIBData );
    ULONG (*pfIsBalancedRoute)(RTMSG6_S * pstRtMsg, ULONG * pulBalCount, SLL_S *pstBalRoutList);

    /* The below ones are right now not used, left here for future ref, to use if any */
    ULONG (*pfGetFirst) (VOID *pvRoot, VOID *pvRouteEntryGot);
    ULONG (*pfGetNext) (VOID *pvCurEntry, VOID *pvRouteEntryGot);
    ULONG (*pfGetNextExt) (UINTPTR* pulWaitlistIndex, ULONG ulRtSetCnt, SLL_S *pstRtList);
    ULONG (*pfDeleteAll) (VOID* pvInfo1);
}IP6_FIBTable_AccessFuns_S;

/* This is a structure of callback function details. This is used during registering
   the callback functions of shell for writing into Message Queue, Reading from 
   Message Queue by Core, also writing timer  */
typedef struct tagIP6_FIBContainer_SHELL_EV_CALLBACUP_SET
{
    /* Printing/Sending debug info */
    VOID (*pfFIB6C_ShellDebugOut) (FIB6C_DEBUG_INFO_E eState, char *pBuf, ULONG ulLen); 
                     
}IP6_FIBContainer_SHELL_EV_CALLBACUP_SET_S;

/* This is a structure of callback function details. This is used during registering
   the callback function for downloading FIB to FE, by FE */
typedef struct tagFIB6_CACHE_UPDATE_FUNC_SET_S
{
    ULONG (*pfUpdate) ( RTMSG6_S *pstRTMsg, ULONG ulBaseCacheIndex, ULONG ulCurrCacheIndex );
    ULONG (*pfAllocValid) ( ROUTE6_S *pstRoute6 );
    ULONG (*pfGetAvailCacheIndex) (USHORT usZoneID);
}FIB6_CACHE_UPDATE_FUNC_SET_S;

/* For shell to initilize module specific information of core, such as IPC 
   queue ID, for sending and receiving IPC messages, this info is set in core, 
   when apprpriate function is invoked by FIB6 Init (shell part) during 
   initilization during nit call by VRP root */
typedef struct tagIP6_FIBContainer_MOD_INFO
{
    ULONG ulModID;
    ULONG ulSubModID;
    ULONG ulLocalIPC_TID;
    ULONG ulPeerIPC_TID;
}IP6_FIBContainer_MOD_INFO_S;

#endif

#ifdef  __cplusplus
}
#endif

