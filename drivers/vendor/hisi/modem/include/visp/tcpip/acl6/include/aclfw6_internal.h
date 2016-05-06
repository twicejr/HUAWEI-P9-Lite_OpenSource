/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              aclfw6_internal.h
*
*  Project Code: VISP V3R2C20
*   Module Name: ACL6 Firewall
*  Date Created: 12-08-2014
*        Author: s72256
*   Description: ACL6 Firewall related structures,API & Macro.
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  12-08-2014   s72256                  ACL6 Firewall related API
*
*******************************************************************************/
#ifndef _ACLFW6_INTERNAL_H_
#define _ACLFW6_INTERNAL_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#include "tcpip/acl6/include/acl6_cbb_api.h"



/*Internal structure to store the security policy configuration node values.*/
typedef struct tagACLFW6_CFGEX
{
    ULONG   ulNoFlag;                               /* 0-ACLFW6_CFG_ADD 1-ACLFW6_CFG_DEL */
    CHAR    stIfName[ACLFW6_MAX_INT_NAME_LEN+1];    /* Interface name. Length: 1 to 47 characters*/
    ULONG   ulIfIndex;                              /* Interface index, this is readonly property for user.*/
    ULONG   ulACLGroup;                             /* ACL group */
    ULONG   ulDirection;                            /* Filter direction,0-ACLFW6_FITLERTYPE_IN,1-ACLFW6_FITLERTYPE_OUT*/   
    ULONG   ulDefaultAction;                        /* ACL6_DENY or ACL6_PERMIT*/
} ACLFW6_CFGEX_S;


/*The macro for based interface hash algorithm*/
#define ACLFW6_HASH_DIV_CONST           128     /* Divide ifindex by this number */

/* Hash algorithm for converting Ifindex to hash length. */
#define ACLFW6_HASH_FUNCTION(ulIfIndex, ulMaxItemNum)  (((ulIfIndex / ACLFW6_HASH_DIV_CONST) + (ulIfIndex % ACLFW6_HASH_DIV_CONST)) % ulMaxItemNum)


/*ACLFW6 Hash node structure*/
typedef struct tagACLFW6HashInnerItem
{
    ULONG  ulValidFlag;                                /* Flag to check if the values are filled or not.*/
    ULONG  ulKey;                                      /* Hash Key mostly it is ifindex. */
    struct tagACLFW6HashInnerItem* pstNextCollisionNode; /* Contains list of collison hash node*/

} ACLFW6_HASH_INNER_ITEM_S;


/*ACLFW6 Hash table structure*/
typedef struct tagACLFW6HashTable
{
    ACLFW6_HASH_INNER_ITEM_S*  pstHashTable;           /*hash table*/
    ULONG                      ulMaxItemNum;           /*Maximum item number of this hash table*/
    ULONG                      ulApplictionItemSize;  /*Hash data i.e. the size of application item*/
    ULONG                      ulInnerItemSize;       /*Hash header i.e. size of ACLFW6_HASH_INNER_ITEM_S*/
    ULONG                      ulItemSize;            /*ulItemSize=ulApplictionItemSize+ulInnerItemSize*/
    ULONG                      ulCurrentItemNum;      /*the number of current item*/
} ACLFW6_HASH_TABLE_S;

/*ACL6 firewall filter structure with waitlist.*/
typedef struct tagACLFW6_WaitListSHOWFILTER_S
{
    CHAR    stIfName[ACLFW6_MAX_INT_NAME_LEN + 1];       /* Interface name */
    ULONG   ulHandle;                                    /* Waitlist handle */
}ACLFW6_WAITLIST_SHOWFILTER_S;

/*ACLFW6 Hash table waitlist structure*/
typedef struct tagACLFW6WaitlistTable
{
    ULONG ulFalg;                                     /* Contains the status to check if it reches end of hashtable.*/
    ACLFW6_HASH_INNER_ITEM_S  *pstNode;               /* Contains the current hash node content.*/

} ACLFW6_WAITLIST_S;

extern ACLFW6_HASH_TABLE_S *g_pstACLFW6CFGHash_share;


/*This enum stores the type of ACLFW6 PPI operation type.*/
typedef enum tagPPIACLFW6_OperationType  
{
    PPI_ACLFW6_ADD,    /* A new group is bound with an interface. */
    PPI_ACLFW6_DEL,    /* A group is unbound with an interface. */
    PPI_ACLFW6_GET,    /* To get hardware statistics. */
    PPI_ACLFW6_CLR,    /* To clear the statistics. */
    PPI_ACLFW6_MAX     /* MAX option. */
}E_ACLFW6_PPI_OPR;


/*Internal structure to hold the configuration & statistic for an interface.*/
typedef struct tagACLFW6_CfgNStatStructure
{
    ACLFW6_SHOWCFG_S    stIfCfg;  /*Contains the security policy configuration for an interface.*/
    ACLFW6_STAT_S       stIfStat; /*Contains the security policy statistic of an interface.*/
}ACLFW6_IF_CFG_STAT_S;

/*******************************************************************************
*    Func Name: ACLFW6_InboundFilter
* Date Created: 2014-08-12
*       Author: s72256
*  Description: Process inbound mbuf packet
*        Input: pstMBuf - MBuf
*       Output: 
*       Return: PP_PROCESS_BY_INTER_FUNCTION_QOSINPUT/PP_RET_ERROR/PP_PROCESS_BY_INTER_FUNCTION
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-12   s72256                  Create
*
*******************************************************************************/
ULONG ACLFW6_InboundFilter(MBUF_S *pMBuf);


/*******************************************************************************
*    Func Name: ACLFW6_OutboundFilter
* Date Created: 2014-08-12
*       Author: s72256
*  Description: Process outbound mbuf packet
*        Input: pstMBuf - MBuf
*       Output: 
*       Return: PP_PROCESS_BY_INTER_FUNCTION_QOSINPUT/PP_RET_ERROR/PP_PROCESS_BY_INTER_FUNCTION
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-12   s72256                  Create
*
*******************************************************************************/
ULONG ACLFW6_OutboundFilter(MBUF_S *pMBuf);


/*************************************************************************
    Function    :ACLFW6_Core_Init
    Description :Initialize the global variables
    Return      :ULONG - 
    		    This function will initialize the binding hash table.
    Parameters  :VOID
*------------------------------------------------------------------------*
*  Modification History
*  DATE        NAME        DESCRIPTION
*------------------------------------------------------------------------*
*  2014-08-19  Syed(s72256)       Create
*************************************************************************/
ULONG ACLFW6_Core_Init();


/*===========================================================================*\
    Function    :ACLFW6_CFG_AddNode
    Description :Add the configuration node
    Return      :ULONG - 
    Parameters  : ACLFW6_CFGEX_S * pstFWCfg 
*------------------------------------------------------------------------*
*  Modification History
*  DATE        NAME        DESCRIPTION
*------------------------------------------------------------------------*
*  2014-08-19  Syed(s72256)       Create
*************************************************************************/
ULONG ACLFW6_CFG_AddNode(ACLFW6_CFGEX_S * pstFW6Cfg);

/*===========================================================================*\
    Function    :ACLFW6_CFG_DeleteNode
    Description :Delete the node by name
    Return      :ULONG - 
    Parameters  :  ACLFW6_CFGEX_S * pstFWCfg - 
        
    Note
------------------------------------------------------------------------*
  Modification History
  DATE        NAME        DESCRIPTION
------------------------------------------------------------------------*
  22-08-2014  s72256(syed)  Created
\*===========================================================================*/
ULONG ACLFW6_CFG_DeleteNode(ACLFW6_CFGEX_S * pstFWCfg);


/*******************************************************************************
*    Func Name: ACLFW6_NotifyIfDelete
* Date Created: 2014-08-12
*       Author: s72256
*  Description: Callback function which is called when there is delete interface.
*        Input: ulIfIndex - Interface index
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-12   s72256                  Create
*
*******************************************************************************/
VOID ACLFW6_NotifyIfDelete(ULONG ulIfIndex);

/*******************************************************************************
 *   @Function Name:  ACLFW6_HashTableInit
 *   @brief		      This functions is used to initialize hash table
 *   @param[in]:      ULONG ulMaxItemNum
 *   @param[in]:      ULONG ulApplictionItemSize
 *   @param[in]:      ACLFW6_HASH_TABLE_S** pstHashTable
 *   @return code:    Help_ACLFW6_HASH_TABLE_OK in case of success.
 ******************************************************************************/
ULONG ACLFW6_HashTableInit(ULONG ulMaxItemNum, ULONG ulApplictionItemSize, 
    ACLFW6_HASH_TABLE_S** pstHashTable);



/*******************************************************************************
 *   @Function Name:  ACLFW6_HashTableInsertItem 
 *   @brief:		  This functions is used insert one application item according
 *                    to key, if item already existing, it will replace old one or
 *                    return item existing info according to ulInsertTypeit also 
 *                    return the location information (pointer) of inserting item 
 *                    in hash table by ppNewHashApplictionItem.
 *   @param[in]:      ACLFW6_HASH_TABLE_S* pApplicationHashTable,
 *   @param[in]:      ULONG ulKey
 *   @param[in]:      VOID* pHashApplicationItem
 *   @return code:    Help_ACLFW6_HASH_TABLE_OK in case of success.
 ******************************************************************************/
ULONG ACLFW6_HashTableInsertItem(ACLFW6_HASH_TABLE_S* pApplicationHashTable, ULONG ulKey,
                                    VOID* pHashApplicationItem);




/*******************************************************************************
 *   @Function Name:  ACLFW6_HashTableSearchItem
 *   @brief:		  This functions is used to search application item according
 *                    to key.
 *   @param[in]:      ACLFW6_HASH_TABLE_S* pApplicationHashTable,
 *   @param[in]:      UINT32 ulKey
 *   @param[out]:     VOID** pHashApplicationItem     appliction item
 *   @return code:    Help_ACLFW6_HASH_ITEM_NOT_EXIST/Help_ACLFW6_HASH_TABLE_OK
 ******************************************************************************/
ULONG ACLFW6_HashTableSearchItem(const ACLFW6_HASH_TABLE_S* pApplicationHashTable,
                                    ULONG ulKey,VOID** pHashApplicationItem);



/*******************************************************************************
 *   @Function Name: ACLFW6_HashTableDeleteItem
 *   @brief:		 This functions is used to delete one item according to key
 *                   the item space don't free, juse invalid this item
 *   @param[in]:     ACLFW6_HASH_TABLE_S* pApplicationHashTable,
 *   @param[in]:     ULONG ulKey    the hash table key value
 *   @return code:   Help_ACLFW6_HASH_TABLE_OK in case of success
 *   @error code:    
 ******************************************************************************/
ULONG ACLFW6_HashTableDeleteItem(ACLFW6_HASH_TABLE_S* pApplicationHashTable,ULONG ulKey);

/*******************************************************************************
*   @Function Name:  ACLFW6_HashTableFree                                   
*   @brief		      This functions is used to free hash table.this function only
*                    be called when appliction initialization fail.
*   @param[in]:     ACLFW6_HASH_TABLE_S* pApplicationHashTable
*   @return code:   Help_ACLFW6_HASH_TABLE_OK
******************************************************************************/
ULONG ACLFW6_HashTableFree(ACLFW6_HASH_TABLE_S* pApplicationHashTable);

/******************************************************************************
*    Func Name: ACLFW6_HashTableGetFirstFromIndex
*    Description: Get the first item from hash table at the index
*     Input: pApplicationHashTable - the pointer of the hash table
*            u32Index - the item index
*            pInnerItem - the current item. It must point to NULL to get the first item.
*
*     OutPut:
*             pInnerItem - The new current item after getting the nex item.*
*     Return:  ULONG : Help_ACLFW6_HASH_TABLE_OK - If more item is there
*					   Help_ACLFW6_HASH_ITEM_NOT_EXIST - no more item
******************************************************************************/
UINT32 ACLFW6_HashTableGetFirstFromIndex(ACLFW6_HASH_TABLE_S* pApplicationHashTable, UINT32 u32Index,
                                           ACLFW6_HASH_INNER_ITEM_S **pInnerItem);
/******************************************************************************
*    Func Name: ACLFW6_HashTableGetNext
*    Description: Get the next item in the hash table
*     Input: pApplicationHashTable - the pointer of the hash table
*     OutPut:
*             pInnerItem - the new current item after getting the nex item.*
*     Return:  ULONG : Help_ACLFW6_HASH_TABLE_OK - If more item is there
*					   Help_ACLFW6_HASH_ITEM_NOT_EXIST - no more item
*                       else                               - corresponding error code
******************************************************************************/
UINT32 ACLFW6_HashTableGetNext(ACLFW6_HASH_TABLE_S* pApplicationHashTable,
                                 ACLFW6_HASH_INNER_ITEM_S **pInnerItem);

/*******************************************************************************
*   @Function Name: ACLFW6_PPI_UPDATE_NODES
*   @brief		    Call back function prototype for PPI 
*   @param[in]:     ulOprType
*                   ulMsgType
*                   pData
*   @return code:   
******************************************************************************/
typedef ULONG (*ACLFW6_PPI_UPDATE_NODES) (ULONG ulOprType, ULONG ulMsgType, VOID *pData);

/* Global variable to store ACLFW6 PPI CALLBACK */
extern ACLFW6_PPI_UPDATE_NODES g_pstACLFW6PPIUpdate;

/* Global variable to check whether stat is enabled or not.*/
extern ULONG  g_pu32ACLFW6_FlowStatSwitch;

/*Macro to check if statistic recording is enabled or not*/
#define ACLFW6_FLOW_STAT_ENABLED (ACLFW6_FLOWSTAT_ON == g_pu32ACLFW6_FlowStatSwitch)




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

