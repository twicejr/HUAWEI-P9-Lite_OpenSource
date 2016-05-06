/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              aclfw6_api.h
*
*  Project Code: VISP V3R2C20
*   Module Name: ACL6 Firewall
*  Date Created: 12-08-2014
*        Author: s72256
*   Description: ACL6 Firewall related API
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  12-08-2014   s72256                  ACL6 Firewall related API
*
*******************************************************************************/
#ifndef _ACLFW6_API_H_
#define _ACLFW6_API_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#include "tcpip/acl6/include/acl6_cbb_api.h"

/*Max interface name length*/
#define ACLFW6_MAX_INT_NAME_LEN 47
#define ACLFW6_MIN_INT_NAME_LEN 1

/*Maximum number of interface configurable for acl6 firewall.*/
#define ACLFW6_MAXNODE 255

/*ACL6 firewall inbound & outbound packet type.*/
#define ACLFW6_FITLERTYPE_IN  0 
#define ACLFW6_FITLERTYPE_OUT 1

/* ACL6 firewall configuration add & delete type*/
#define ACLFW6_CFG_ADD 0 
#define ACLFW6_CFG_DEL 1

#define ACLFW6_HASH_ITEM_FILLED 1
#define ACLFW6_HASH_ITEM_EMPTY  0

#define ACLFW6_HASH_NO_KEY  0



/*ACL6 firewall cofiguration structure.*/
typedef struct tagACLFW6_CFG
{
    ULONG   ulNoFlag;                               /* 0-ACLFW6_CFG_ADD 1-ACLFW6_CFG_DEL */
    CHAR    stIfName[ACLFW6_MAX_INT_NAME_LEN+1];    /* Interface name. Length: 1 to 47 characters*/
    ULONG   ulACLGroup;                             /* ACL group */
    ULONG   ulDirection;                            /* Filter direction,0-ACLFW6_FITLERTYPE_IN,1-ACLFW6_FITLERTYPE_OUT*/   
    ULONG   ulDefaultAction;                        /* ACL6_DENY or ACL6_PERMIT*/
} ACLFW6_CFG_S;




/*ACL6 firewall cofiguration show structure.*/
typedef struct tagACLFW6_SHOWCFG
 {
    CHAR    stIfName[ACLFW6_MAX_INT_NAME_LEN+1];    /* Interface name*/
    ULONG   ulIfIndex;                              /* Interface index*/
    ULONG   ulInboundACL;                           /* Indicates inbound packet ACL group.*/
    ULONG   ulOutboundACL;                          /* Indicates outbound packet ACL group.*/
    ULONG   ulInBoundACLDefaultAction;              /* Indicates default action to be taken when there is no rule 
                                                       that exists in attached group for inbound packets */
    ULONG   ulOutBoundACLDefaultAction;             /* Indicates default action to be taken when there is no rule 
                                                       that exists in attached group for outbound packets */
}ACLFW6_SHOWCFG_S;


/*ACL6 firewall filter structure.*/
typedef struct tagACLFW6_SHOWFILTER_S
{
    CHAR    stIfName[ACLFW6_MAX_INT_NAME_LEN + 1]; /* Interface Name*/
}ACLFW6_SHOWFILTER_S;


/*ACL6 firewall statistic structure.*/
typedef struct tagACLFW6_STAT
 {
     ULONG ulInDropPackets;             /* Indicates the number of dropped interface inbound packets*/
     ULONG ulInPassPackets;             /* Indicates the number of passed interface inbound packets*/
     ULONG ulInErrPackets;              /* Indicates the number of interface inbound packets with error*/
     ULONG ulOutDropPackets;            /* Indicates the number of dropped interface outbound packets*/
     ULONG ulOutPassPackets;            /* Indicates the number of passed interface outbound packets*/
     ULONG ulOutErrPackets;             /* Indicates the number of interface outbound packets with error*/
} ACLFW6_STAT_S;


/*ACL6 firewall PPI statistic structire*/
typedef struct tagACLFW6_PPI_COUNT_S
{
    ULONG ulACLFW6TotalUpdate;     /*Total number of update notifications to PPI from ACLFW6 */
    ULONG ulACLFW6FailureUpdate;   /*Total number of failure notifications to PPI from ACLFW6 */
    ULONG ulPPIIn6UpdateCount;     /*Total number of update notifications to PPI from ACLFW6 for inbound IP packet*/
    ULONG ulPPIIn6DeleteCount;     /*Total number of delete notifications to PPI from ACLFW6 for inbound IP packet*/
    ULONG ulPPIOut6UpdateCount;    /*Total number of update notifications to PPI from ACLFW6 for outbound IP packet*/
    ULONG ulPPIOut6DeleteCount;    /*Total number of delete notifications to PPI from ACLFW6 for outbound IP packet*/
} ACLFW6_PPI_COUNT_S;



/* ACL-FW6 configuration PPI data structures */
typedef struct tagPPI_ACLFW6CFG
{
    CHAR    stIfName[ACLFW6_MAX_INT_NAME_LEN+1]; /* Interface Name*/
    ULONG   ulGroupID;                           /* ACL6 Group ID */ 
    ULONG   ulDirection;                         /* Filter Direction 0:Inbound 1:Outbound */ 
    ULONG   ulDefaultAction;                     /* Default action to be taken when there is no rule, ACL6_DENY/ACL6_PERMIT */
}PPI_ACLFW6_CFG_S;


/* ACL-FW6 message type */
typedef enum tagPPIACLFW6MSGType  
{
    PPI_ACLFW6_BIND,        /* Packet filtering bind to an interface */
    PPI_ACLFW6_STAT         /* Get statistical information */
}E_ACLFW6_PPI_MSG;


#define ACLFW6_FLOWSTAT_OFF     0
#define ACLFW6_FLOWSTAT_ON      1


/*******************************************************************************
*    Func Name: ACLFW6_Init
* Date Created: 2014-08-12
*       Author: s72256
*  Description: ACL-FW6 initialization
*        Input: 
*       Output: 
*       Return:  Help_ACL6_OK :
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-12   s72256                  Create
*
*******************************************************************************/
ULONG ACLFW6_Init(ULONG ulRegPri);


/*******************************************************************************
*    Func Name: ACLFW6_CFG_SecurityPolicy
* Date Created: 2014-08-12
*       Author: s72256
*  Description: ACL-FW6 initialization
*        Input: pstACLFW6Cfg
*       Output: 
*       Return:  Help_ACL6_OK :
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-12   s72256                  Create
*
*******************************************************************************/
ULONG ACLFW6_CFG_SecurityPolicy(ACLFW6_CFG_S * pstACLFW6Cfg);

/*******************************************************************************
*    Func Name: ACLFW6_ShowCfgByIf
* Date Created: 2014-08-12
*       Author: s72256
*  Description: show ACL-FW6 configuration information
*        Input: pucIfName, Interface name
*       Output: 
*       Return:  Help_ACL6_OK :
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-12   s72256                  Create
*
*******************************************************************************/
VOID ACLFW6_ShowCfgByIf(CHAR *pucIfName);


/*******************************************************************************
*    Func Name: ACLFW6_GetCfgByIf
* Date Created: 2014-08-12
*       Author: s72256
*  Description: Get ACL-FW6 configuration information
*        Input: pucIfName - Interface name
*       Output: pstShowCfg - Cofiguration Info
*       Return:  Help_ACL6_OK :
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-12   s72256                  Create
*
*******************************************************************************/
ULONG ACLFW6_GetCfgByIf(CHAR *pucIfName, ACLFW6_SHOWCFG_S *pstShowCfg);

/*******************************************************************************
*    Func Name: ACLFW6_SecPolicy_Open
* Date Created: 2014-08-12
*       Author: s72256
*  Description: Open ACL-FW6 configuration table
*        Input: pstFilter - Interface details
*       Output: pulHandle - waitlist handle Info
*       Return: Help_ACL6_OK :
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-12   s72256                  Create
*
*******************************************************************************/
ULONG ACLFW6_SecPolicy_Open(ULONG *pulHandle, ACLFW6_SHOWFILTER_S *pstFilter);

/*******************************************************************************
*    Func Name: ACLFW6_SecPolicy_GetNext
* Date Created: 2014-08-12
*       Author: s72256
*  Description: Get next entry from ACL-FW6 configuration table
*        Input: ulHandle - waitlist handle
*       Output: pstShowObj - Configuration Info
*       Return: Help_ACL6_OK :
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-12   s72256                  Create
*
*******************************************************************************/
ULONG ACLFW6_SecPolicy_GetNext(ULONG ulHandle, ACLFW6_SHOWCFG_S *pstShowObj);

/*******************************************************************************
*    Func Name: ACLFW6_SecPolicy_Close
* Date Created: 2014-08-12
*       Author: s72256
*  Description: Close ACL-FW6 configuration table
*        Input: ulHandle - waitlist handle
*       Output: 
*       Return: Help_ACL6_OK :
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-12   s72256                  Create
*
*******************************************************************************/
ULONG ACLFW6_SecPolicy_Close(ULONG ulHandle);

/*******************************************************************************
*    Func Name: ACLFW6_ShowInterfaceStat
* Date Created: 2014-09-12
*       Author: s72256
*  Description: Show ACL-FW6 Packet statistics for an interface
*        Input: pcIfName - Interface name
*       Output: 
*       Return: Help_ACL6_OK :
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-12   s72256                  Create
*
*******************************************************************************/
VOID ACLFW6_ShowInterfaceStat(CHAR *pcIfName);

/*******************************************************************************
*    Func Name: ACLFW6_GetInterfaceStat
* Date Created: 2014-08-12
*       Author: s72256
*  Description: Get ACL-FW6 Packet statistics for an interface
*        Input: pcIfName - Interface Name
*       Output: pstStat - Stat entry for an interface
*       Return: Help_ACL6_OK :
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-12   s72256                  Create
*
*******************************************************************************/
ULONG ACLFW6_GetInterfaceStat(CHAR *pcIfName, ACLFW6_STAT_S* pstStat);

/*******************************************************************************
*    Func Name: ACLFW6_ClearInterfaceStat
* Date Created: 2014-09-12
*       Author: s72256
*  Description: Clears ACL-FW6 Packet statistics for given interface
*        Input: pcIfName , Interface Name
*       Output: 
*       Return: Help_ACL6_OK :
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-12   s72256                  Create
*
*******************************************************************************/
ULONG ACLFW6_ClearInterfaceStat(CHAR *pcIfName);

/*******************************************************************************
*    Func Name: ACLFW6_SetFlowStatisticSwitch
* Date Created: 2014-09-12
*       Author: s72256
*  Description: To set the flowstatistics switch
*        Input: 
*             UINT32 u32FlowStatSwitch ( Valid values - ACLFW6_FLOWSTAT_OFF/ACLFW6_FLOWSTAT_ON)
*               ACLFW6_FLOWSTAT_OFF = 0 - To disable flow statistics
*               ACLFW6_FLOWSTAT_ON  = 1 - To enable flow statistics
*       Output: 
*       Return: Help_ACL6_OK :
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-12   s72256                  Create
*
*******************************************************************************/
UINT32 ACLFW6_SetFlowStatisticSwitch (UINT32 u32FlowStatSwitch);

/*******************************************************************************
*    Func Name: ACLFW6_Stat_OpenList
* Date Created: 2014-09-15
*       Author: s72256(syed)
*  Description: ACLFW6 Function to open the statistic table
*        Input: 
*       Output: pulHandle
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-15   s72256(Syed)             Create
*******************************************************************************/
ULONG ACLFW6_Stat_OpenList(ULONG *pulHandle);

/*******************************************************************************
*    Func Name: ACLFW6_Stat_GetNext
* Date Created: 2014-09-15
*       Author: s72256(syed)
*  Description: ACLFW6 Function to get entry from the statistic table.
*        Input: pulHandle - waitlist handle
*       Output: pstStat - statistic output
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-15   s72256(Syed)             Create
*******************************************************************************/
ULONG ACLFW6_Stat_GetNext(ULONG pulHandle, ACLFW6_STAT_S* pstStat);


/*******************************************************************************
*    Func Name: ACLFW6_Stat_CloseList
* Date Created: 2014-09-15
*       Author: s72256(syed)
*  Description: ACLFW6 Function to close the statistic table.
*        Input: ulHandle - waitlist handle
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-15   s72256(Syed)             Create
*******************************************************************************/
ULONG ACLFW6_Stat_CloseList(ULONG ulHandle);


/*******************************************************************************
*    Func Name: ACLFW6_ShowAllStat
* Date Created: 2014-09-12
*       Author: s72256
*  Description: This function is used to show all policy statistic.
*        Input: 
*       Output: 
*       Return: Help_ACL6_OK :
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-19   s72256                  Create
*
*******************************************************************************/
ULONG ACLFW6_ShowAllStat();

/*******************************************************************************
*    Func Name: ACLFW6_ClearAllStat
* Date Created: 2014-09-19
*       Author: s72256
*  Description: This function is used to clear all statistic.
*        Input: 
*       Output: 
*       Return: Help_ACL6_OK :
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-19   s72256                  Create
*
*******************************************************************************/
ULONG ACLFW6_ClearAllStat();


/*******************************************************************************
*    Func Name: ACLFW6_PPI_HOOK_FUNC
* Date Created: 2014-09-08
*       Author: s72256
*  Description: Prototype of callback function for ACLFW6 PPI registration.
*        Input: 
*       Output: 
*       Return:  :
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-08   s72256                  Create
*
*******************************************************************************/
typedef ULONG (*ACLFW6_PPI_HOOK_FUNC)(ULONG ulOprType, ULONG ulMsgType, VOID* pData);


/*******************************************************************************
*    Func Name: ACLFW6_PPI_HookRegister
* Date Created: 2014-09-08
*       Author: s72256(syed)
*  Description: Function to register the ACLFW6 ppi callback
*        Input: ACLFW6_PPI_HOOK_FUNC pfACLFWPPIHook:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-08   s72256(Syed)             Create
*
*******************************************************************************/
ULONG ACLFW6_PPI_HookRegister(ACLFW6_PPI_HOOK_FUNC pfACLFW6PPIHook);

/*******************************************************************************
*    Func Name: ACLFW6_PPI_Update
* Date Created: 2014-09-08
*       Author: s72256(syed)
*  Description: 
*        Input: 
*       Output: pstCount
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-08   s72256(Syed)             Create
*******************************************************************************/
ULONG ACLFW6_PPI_GetCount(ACLFW6_PPI_COUNT_S *pstCount);

/*******************************************************************************
*    Func Name: ACLFW6_PPI_ResetCount
* Date Created: 2014-09-08
*       Author: s72256(syed)
*  Description: ACLFW6 Function to reset the PPI statistic
*        Input: 
*       Output: pstCount
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-08   s72256(Syed)             Create
*******************************************************************************/
ULONG ACLFW6_PPI_ResetCount(VOID);

/*******************************************************************************
*    Func Name: ACLFW6_PPI_ShowCount
* Date Created: 2014-09-08
*       Author: s72256(syed)
*  Description: ACLFW6 Function to show the PPI statistic
*        Input: 
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-08   s72256(Syed)             Create
*******************************************************************************/
VOID ACLFW6_PPI_ShowCount(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

