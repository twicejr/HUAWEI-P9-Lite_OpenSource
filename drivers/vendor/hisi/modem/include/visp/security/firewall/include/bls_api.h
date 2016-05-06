/*************************************************************************
Copyright (C), 2004, Huawei Tech. Co., Ltd.
FileName: bls_api.h
Version: 1
Author:  Ramalingeswara Reddy 72335
Creation Date: 2009-08-25
Description: This is header file for bls_process.c

History:<author>                     <date>          <desc>     
        Ramalingeswara Reddy 72335   2009-08-25      Create
**************************************************************************/
#ifndef _BLS_API_H_
#define _BLS_API_H_


#define BLS_MAX_TIMEOUT 1000  /* Maximum timeout value for Black List entry */


/**
* @defgroup enumBLSReturnCode BLS_RETURN_CODE
* @ingroup BLE Black List Enums
* @par Prototype
* @code
* typedef enum enumBLSReturnCode
* {
*     BLS_MAXRULEREACHED=1,
*     BLS_ENTRY_NOT_EXISTS,
* }BLS_RETURN_CODE;
* @endcode 
* 
* @par Description
* This enum consists of blacklist return values.
*
* @datastruct BLS_MAXRULEREACHED=1 Indicates maximum rules reached for blacklist.
* @datastruct BLS_ENTRY_NOT_EXISTS Indicates entry does not exist in blacklist.
*/

typedef enum enumBLSReturnCode
{
    BLS_MAXRULEREACHED = 1,
    BLS_ENTRY_NOT_EXISTS,
}BLS_RETURN_CODE;

/**
* @defgroup tagBLS_INFO BLS_INFO_S/PBLS_INFO_S
* @ingroup BLS Black List Structures
* @par Prototype
* @code
* typedef struct tagBLS_INFO
* {
*     UINT32  u32Ip;
*     UINT64  u64TimeOut;
*     UINT32  u32EnableLog;
* } BLS_INFO_S,*PBLS_INFO_S;
* @endcode 
* 
* @par Description
* This structure stores the details of the blacklist entry configuration.
*
* @datastruct u32Ip IP which user wants to add to blacklist.
* @datastruct u64TimeOut Timeout value for blacklist. Range is 1-1000. If we give timeout value other
* than zero, IP will be deleted from blacklist after that much time. If we give zero as timeout 
* that entry will not be deleted untill user deletes it manually
* @datastruct u32EnableLog Log flag for blacklist entry. This log flag will decide whether to log or not in debug log,
* when the packet is dropped from blacklist. If it is set to 1, it will log source IP when packet dropped
* from blacklist and when an entry added to blacklist with timeout value as zero.
*/
typedef struct tagBLS_INFO
{
    UINT32  u32Ip;
    UINT64  u64TimeOut;
    UINT32  u32EnableLog;
} BLS_INFO_S,*PBLS_INFO_S;

/**
* @defgroup enumBLSErrCode BLS_ERR_CODE_E
* @ingroup FEC Firewall Error Codes
* @par Prototype
* @code
* typedef enum enumBLSErrCode BLS_ERR_CODE_E
* {
*     BLS_OK=FW_OK,
*     BLS_ERR_ADD_INTERNAL_HASH_FAIL=FWCOMMON_BLSMODID + 1,
*     BLS_ERR_ADD_NAMEDB,
*     BLS_ERR_MALLOC,
*     BLS_ERR_HASH_INIT,
*     BLS_ERR_INIT_ENABLE,
*     BLS_ERR_INIT_DISABLE,
*     BLS_ERR_INIT_ADDENTRY,
*     BLS_ERR_INIT_DELENTRY,
*     SFE_BLS_ERR_ADD_NULLPTR_INPUT,
*     SFE_BLS_ERR_TIMEOUT_OUTOF_RANGE,
*     SFE_BLS_ERR_DELETE_NULLPTR_INPUT,
*     BLS_ERR_NULLPTR_OPENLIST,
*     BLS_ERR_OPEN_FAIL_OPENLIST,
*     BLS_ERR_GET_FAIL_GETNEXT,
*     BLS_ERR_CLOSE_FAIL_CLOSELIST,
*     SFE_BLS_ERR_NULLPTR_OPENLIST,
*     SFE_BLS_ERR_HANDLE_NULLPTR_GETNEXT,
*     SFE_BLS_ERR_HANDLE_NULLPTR_CLOSELIST,
*     BLS_ERR_INIT_OPENLIST,
*     BLS_ERR_INIT_GETNEXT,
*     BLS_ERR_INIT_CLOSELIST,
*     SFE_BLS_ERR_STRUCT_NULLPTR_GETNEXT,
*     SFE_BLS_ERR_STRUCT_NULLPTR_GETSTAT,
*     BLS_ERR_INIT_GETSTAT,
*     SFE_BLS_ERR_STRUCT_NULLPTR_GETVCPUSTAT,
*     BLS_ERR_INIT_GETVCPUSTAT,
*     SFE_BLS_ERR_INVALID_VCPUNUM_GETVCPUSTAT,
*     BLS_ERR_STAT_INIT,
*     SFE_BLS_ERR_INVLID_ACL_GROUP_NUMBER,
*     BLS_ERR_INIT_SETBINDACLGROUP,
*     SFE_BLS_ERR_NULLPTR_GET_BINDACLGROUP,
*     BLS_ERR_INIT_GETBINDACLGROUP,
*     SFE_BLS_ERR_INVALID_LOG_SWITCH,
*     BLS_ERR_MALLOC_TIMER,
*     BLS_ERR_ADD_NAME_DB_TIMER,
*     BLS_ERR_TIMER_CREATE_MULTIPLANE
* }BLS_ERR_CODE_E;
* @endcode 
* 
* @par Description
* This enum consists of blacklist errors.
*
* @datastruct BLS_OK=FW_OK Indicates blacklist operation success.
* @datastruct BLS_ERR_ADD_INTERNAL_HASH_FAIL=FWCOMMON_BLSMODID+1 Indicates error occurred while inserting an 
* entry into blacklist.
* @datastruct BLS_ERR_ADD_NAMEDB Indicates error in registering the global variable name.
* @datastruct BLS_ERR_MALLOC Indicates error in allocating memory.
* @datastruct BLS_ERR_HASH_INIT Indicates error in initializing hash for blacklist.
* @datastruct BLS_ERR_INIT_ENABLE Indicates failed to enable blacklist, as firewall initialization is not done.
* @datastruct BLS_ERR_INIT_DISABLE Indicates failed to disable blacklist, as firewall initialization is not done.
* @datastruct BLS_ERR_INIT_ADDENTRY Indicates error while inserting an entry into blacklist, 
* as firewall initialization is not done.
* @datastruct BLS_ERR_INIT_DELENTRY Indicates error while removing an entry from blacklist, 
* as firewall initialization is not done.
* @datastruct SFE_BLS_ERR_ADD_NULLPTR_INPUT Indicates received null pointer as input argument to add an entry.
* @datastruct SFE_BLS_ERR_TIMEOUT_OUTOF_RANGE Indicates timeout of the entry is out of range.
* @datastruct SFE_BLS_ERR_DELETE_NULLPTR_INPUT Indicates received null pointer as input argument to delete an entry.
* @datastruct BLS_ERR_OPEN_FAIL_OPENLIST Indicates failed to open the blacklist.
* @datastruct BLS_ERR_GET_FAIL_GETNEXT Indicates failed to get next entry from blacklist.
* @datastruct BLS_ERR_CLOSE_FAIL_CLOSELIST Indicates failed to close the blacklist
* @datastruct SFE_BLS_ERR_NULLPTR_OPENLIST Indicates received null pointer as input argument to open the blacklist.
* @datastruct SFE_BLS_ERR_HANDLE_NULLPTR_GETNEXT Indicates received null pointer as handle to get next 
* entry from blacklist.
* @datastruct SFE_BLS_ERR_HANDLE_NULLPTR_CLOSELIST Indicates received null pointer as handle to close the blacklist.
* @datastruct BLS_ERR_INIT_OPENLIST Indicates failed to open the blacklist, as firewall initialization is not done.
* @datastruct SFE_BLS_ERR_NULLPTR_GETNEXT Indicates failed to get next entry from blacklist in dataplane, 
* as firewall initialization is not done.
* @datastruct SFE_BLS_ERR_NULLPTR_CLOSELIST Indicates failed to close the blacklist, as
* firewall initialization is not done.
* @datastruct SFE_BLS_ERR_STRUCT_NULLPTR_GETNEXT Indicates received null pointer as blacklist structure to get next 
* entry from blacklist.
* @datastruct SFE_BLS_ERR_STRUCT_NULLPTR_GETSTAT Indicates recieved null pointer as blacklist statistics structure.
* @datastruct BLS_ERR_INIT_GETSTAT Indicates failed to get all statistics of blacklist, as blacklist is not
* initialized.
* @datastruct SFE_BLS_ERR_STRUCT_NULLPTR_GETVCPUSTAT Indicates recieved null pointer as blacklist statistics structure.
* @datastruct BLS_ERR_INIT_GETVCPUSTAT Indicates failed to get statistics of given VCPU, as blacklist is not
* initialized.
* @datastruct SFE_BLS_ERR_INVALID_VCPUNUM_GETVCPUSTAT Indicates invalid VCPU number while getting statistics.
* @datastruct BLS_ERR_STAT_INIT Indicates failed to initialize statistics for blacklist.
* @datastruct SFE_BLS_ERR_INVLID_ACL_GROUP_NUMBER Indicates recieved invalid ACL group number to bind with blacklist. 
* only basic and advanced ACL groups can be binded
* @datastruct BLS_ERR_INIT_SETBINDACLGROUP Indicates failed to bind acl group with blacklist, as blacklist is not
* initialized.
* @datastruct SFE_BLS_ERR_NULLPTR_GET_BINDACLGROUP Indicates recieved null pointer to get binded acl group with blacklist.
* @datastruct BLS_ERR_INIT_GETBINDACLGROUP Indicates failed to get binded acl group with blacklist, as blacklist is not
* initialized.
* @datastruct SFE_BLS_ERR_INVALID_LOG_SWITCH Indicates invalid Enablelog flag while adding an entry to blacklist.
* @datastruct BLS_ERR_MALLOC_TIMER Indicates failed to allocate memory for blacklist timer.
* @datastruct BLS_ERR_ADD_NAME_DB_TIMER Indicates failed to register timer name.
* @datastruct BLS_ERR_TIMER_CREATE_MULTIPLANE Indicates failed to create timer for blacklist.
* @datastruct BLS_ERR_GET_PRECONFIG_FAIL Indicates failed to get the pre configuration data for Blacklist.
*/

typedef enum enumBLSErrCode
{
    BLS_OK = 0,
    BLS_ERR_ADD_INTERNAL_HASH_FAIL = FWIPSAFE_FW_BLS_BEGIN_RET_CODE + 1,
    BLS_ERR_ADD_NAMEDB,
    BLS_ERR_MALLOC,
    BLS_ERR_HASH_INIT,
    BLS_ERR_INIT_ENABLE,
    BLS_ERR_INIT_DISABLE,
    BLS_ERR_INIT_ADDENTRY,
    BLS_ERR_INIT_DELENTRY,
    SFE_BLS_ERR_ADD_NULLPTR_INPUT,
    SFE_BLS_ERR_TIMEOUT_OUTOF_RANGE,
    SFE_BLS_ERR_DELETE_NULLPTR_INPUT,
    BLS_ERR_OPEN_FAIL_OPENLIST,
    BLS_ERR_GET_FAIL_GETNEXT,
    BLS_ERR_CLOSE_FAIL_CLOSELIST,
    SFE_BLS_ERR_NULLPTR_OPENLIST,
    SFE_BLS_ERR_HANDLE_NULLPTR_GETNEXT,
    SFE_BLS_ERR_HANDLE_NULLPTR_CLOSELIST,
    BLS_ERR_INIT_OPENLIST,
    BLS_ERR_INIT_GETNEXT,
    BLS_ERR_INIT_CLOSELIST,
    SFE_BLS_ERR_STRUCT_NULLPTR_GETNEXT,
    SFE_BLS_ERR_STRUCT_NULLPTR_GETSTAT,
    BLS_ERR_INIT_GETSTAT,
    SFE_BLS_ERR_STRUCT_NULLPTR_GETVCPUSTAT,
    BLS_ERR_INIT_GETVCPUSTAT,
    SFE_BLS_ERR_INVALID_VCPUNUM_GETVCPUSTAT,
    BLS_ERR_STAT_INIT,
    SFE_BLS_ERR_INVLID_ACL_GROUP_NUMBER,
    BLS_ERR_INIT_SETBINDACLGROUP,
    SFE_BLS_ERR_NULLPTR_GET_BINDACLGROUP,
    BLS_ERR_INIT_GETBINDACLGROUP,
    SFE_BLS_ERR_INVALID_LOG_SWITCH,
    BLS_ERR_MALLOC_TIMER,
    BLS_ERR_ADD_NAME_DB_TIMER,
    BLS_ERR_TIMER_CREATE_MULTIPLANE,
    BLS_ERR_GET_PRECONFIG_FAIL
}BLS_ERR_CODE_E;


/**
* @defgroup BLS_Enable BLS_Enable
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* UINT32 BLS_Enable(VOID);
* @endcode 
* 
* @par Description
* This function is used to enable the blacklist. This function is used only when blacklist must be enabled in the 
* complete firewall functionality. The user who uses blacklist seperately need not call this function. 
* 
* @param[in]   []
* @param[out]   []
* 
* @retval UINT32 Enabling blacklist is success. [BLS_OK|]
* @retval UINT32 Enabling blacklist has failed as firewall is not initialized. [BLS_ERR_INIT_ENABLE|]
* 
* @par Dependency
* None
*
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* BLS_Disable
*/
extern UINT32 BLS_Enable(VOID);

/**
* @defgroup BLS_Disable BLS_Disable
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* UINT32 BLS_Disable(VOID);
* @endcode 
* 
* @par Description
* This function is used to disable blacklist. This function is used only when blacklist must be disabled in the 
* complete firewall functionality. The user who uses blacklist seperately need not call this function. 
* 
* @param[in]   []
* @param[out]   []
* 
* @retval UINT32 Disabling blacklist is success. [BLS_OK|]
* @retval UINT32 Disabling blacklist has failed as firewall is not initialized. [BLS_ERR_INIT_DISABLE|]
*
* @par Dependency
* None
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* BLS_Enable
*/ 
extern UINT32 BLS_Disable(VOID);

/**
* @defgroup BLS_AddEntry BLS_AddEntry
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* UINT32 BLS_AddEntry( BLS_INFO_S *pstBLSInfo);
* @endcode 
* 
* @par Description
* This function is used to insert an entry into blacklist. 
* It accepts a structure in which you can configure the IP, timeout value and value of enable log. The mentioned
* IP will be inserted into the blacklist.
* 
* @param[in] pstBLSInfo Pointer to BLS_INFO_S structure []
* @param[out]   []
* 
* @retval UINT32 Adding entry to blacklist is success. [BLS_OK|]
* @retval UINT32 Received null pointer as input argument. [SFE_BLS_ERR_ADD_NULLPTR_INPUT|]
* @retval UINT32 Timeout value of IP is out of range. [SFE_BLS_ERR_TIMEOUT_OUTOF_RANGE|]
* @retval UINT32 Invalid value provided for Enablelog flag. [SFE_BLS_ERR_INVALID_LOG_SWITCH|]
* @retval UINT32 Failed to insert entry in blacklist as firewall is not initialized. [BLS_ERR_INIT_ADDENTRY|]
* @retval UINT32 Maximum number of rules reached for blacklist. [BLS_MAXRULEREACHED|]
* @retval UINT32 Failed to insert entry in blacklist as hash operation failed. [BLS_ERR_ADD_INTERNAL_HASH_FAIL|]
* 
* @par Dependency
* None
* 
* @par Note
* \n
* 
* This function will not log any information when dynamic entries are added.
* 
* 
* @par Related Topics
* BLS_DelEntry
*/ 
extern UINT32 BLS_AddEntry(BLS_INFO_S *pstBLSInfo);

/**
* @defgroup BLS_DelEntry BLS_DelEntry
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* UINT32 BLS_DelEntry(const BLS_INFO_S *pstBLSInfo);
* @endcode 
* 
* @par Description
* This function is used to delete an entry from blacklist. 
* It accepts a structure in which user can configure the IP. This IP will be 
* deleted from the blacklist.
* 
* @param[in] pstBLSInfo Pointer to BLS_INFO_S structure. []
* @param[out]   []
* 
* @retval UINT32 Deleting entry from blacklist success. [BLS_OK|]
* @retval UINT32 Received null pointer as input argument. [SFE_BLS_ERR_DELETE_NULLPTR_INPUT|]
* @retval UINT32 Failed to delete entry from blacklist as firewall is not initialized. [BLS_ERR_INIT_DELENTRY|]
* @retval UINT32 The entry does not exists in blacklist. [BLS_ENTRY_NOT_EXISTS|]
* 
* @par Dependency
*	- bls_common.h
*	- sfe_fwcommon_inc.h
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* BLS_AddEntry
*/ 
extern UINT32 BLS_DelEntry(const BLS_INFO_S *pstBLSInfo);

/**
* @defgroup BLS_Init BLS_Init
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* UINT32 BLS_Init(VOID);
* @endcode 
* 
* @par Description
* This function is used to initialize blacklist.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval UINT32 Initializing blacklist is success. [BLS_OK|]
* @retval UINT32 Failed to get pre-configuration of maximum entries that can be configured
* in blacklist. [BLS_ERR_GET_PRECONFIG_FAIL|]
* @retval UINT32 Failed to allocate memory for blacklist. [BLS_ERR_MALLOC|]
* @retval UINT32 Registering global variable name failed in blacklist. [BLS_ERR_ADD_NAMEDB|]
* @retval UINT32 Hash table initialization failed for blacklist. [BLS_ERR_HASH_INIT|]
* @retval UINT32 Indicates failed to allocate memory for blacklist timer. [BLS_ERR_MALLOC_TIMER|]
* @retval UINT32 Indicates failed to register timer name. [BLS_ERR_ADD_NAME_DB_TIMER|]
* @retval UINT32 Indicates failed to create timer for blacklist. [BLS_ERR_TIMER_CREATE_MULTIPLANE|]
* @retval UINT32 Statiatics initialization failed for blacklist. [BLS_ERR_STAT_INIT|]
* 
* @par Dependency
* None
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/ 
UINT32 BLS_Init(VOID);

/* Prototypes for blacklist packet filter function*/
/**
* @defgroup BLS_PacketFilter BLS_PacketFilter
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* UINT32 BLS_PacketFilter(VOID* pstMBuf);
* @endcode 
* 
* @par Description
* It will accept packet structure and it will return a value, which gives the status of packet in blacklist.
* If blacklist is binded with any ACL group, ACL module also has to be initialized to use this API 
* 
* @param[in] pstMBuf Pointer to MBUF_S structure []
* @param[out]   []
*
* @retval UINT32 Indicates message should be processed by protocol stack [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 Indicates message has been processed by firewall. PP need not process the packet any more.
* [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
* 
* @par Dependency
* ACL-Adaptor
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/ 
UINT32 BLS_PacketFilter(VOID *pstMBuf);

/**
* @defgroup BLS_OpenList BLS_OpenList
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* UINT32 BLS_OpenList(VOID **ppHandle);
* @endcode 
* 
* @par Description
* This function is used to open blacklist.
* 
* @param[in]   []
* @param[out] ppHandle Pointer to void pointer which stores blacklist handle []
* 
* @retval UINT32 Opening blacklist is success. [FWCOMMON_ITERATOR_ITEM_EXIST|]
* @retval UINT32 Recieved null pointer as input argument to open blacklist. [SFE_BLS_ERR_NULLPTR_OPENLIST|]
* @retval UINT32 Failed to open blacklist as blacklist is not initialized. [BLS_ERR_INIT_OPENLIST|]
* @retval UINT32 Failed to open blacklist as iterator operation failed. [BLS_ERR_OPEN_FAIL_OPENLIST|]
* @retval UINT32 No item exists in blacklist. [FWCOMMON_ITERATOR_ITEM_NOT_EXIST|]
* 
* @par Dependency
*
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* BLS_CloseList
*/ 

extern UINT32 BLS_OpenList(VOID **ppHandle);

/**
* @defgroup BLS_GetNext BLS_GetNext
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* UINT32 BLS_GetNext(VOID *pHandle, BLS_INFO_S * pstBLSInfo);
* @endcode 
* 
* @par Description
* This function is used to get next entry from blacklist. On calling this API in a loop, you can get the entries of 
* the list. On reaching the end of the list, this API will return failure once, 
* after which it will again continue to give the entries of the list. The order of getting the entries may not be same 
* as the order in which the entries were added.
* 
* @param[in] pHandle Handle to blacklist []
* @param[out] pstBLSInfo Blacklist structure []
* 
* @retval UINT32 Getting next item from blacklist is success. [FWCOMMON_ITERATOR_ITEM_EXIST|]
* @retval UINT32 Recieved null pointer as handle to get next entry from blacklist. [SFE_BLS_ERR_HANDLE_NULLPTR_GETNEXT|]
* @retval UINT32 Recieved null pointer to get next entry from blacklist. [SFE_BLS_ERR_STRUCT_NULLPTR_GETNEXT|]
* @retval UINT32 Failed to get next entry from blacklist as blacklist is not initialized. [BLS_ERR_INIT_GETNEXT|]
* @retval UINT32 Failed to get next entry from blacklist as iterator operation failed. [BLS_ERR_GET_FAIL_GETNEXT|]
* @retval UINT32 No item exists in blacklist. [FWCOMMON_ITERATOR_ITEM_NOT_EXIST|]
* 
* @par Dependency
* None
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/ 

extern UINT32 BLS_GetNext(VOID *pHandle, BLS_INFO_S* pstBLSInfo);

/**
* @defgroup BLS_CloseList BLS_CloseList
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* UINT32 BLS_CloseList(VOID *pHandle);
* @endcode 
* 
* @par Description
* This function is used to close blacklist.
* 
* @param[in] pHandle Handle to blacklist []
* @param[out]   []
* 
* @retval UINT32 Closing blacklist is success. [BLS_OK|]
* @retval UINT32 Recieved null handle to close blacklist.. [SFE_BLS_ERR_NULLPTR_CLOSELIST|]
* @retval UINT32 Failed to close blacklist as blacklist is not initialized. [BLS_ERR_INIT_CLOSELIST|]
* @retval UINT32 Failed to close blacklist as iterator operation failed. [BLS_ERR_CLOSE_FAIL_CLOSELIST|]
* 
* @par Dependency
*	- bls_common.h
*	- sfe_fwcommon_inc.h
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* BLS_OpenList
*/

extern UINT32 BLS_CloseList(VOID *pHandle);

/**
* @defgroup BLS_ShowList BLS_ShowList
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* VOID BLS_ShowList(VOID);
* @endcode 
* 
* @par Description
* This function is used to show configured IP in blacklist. The order of showing the entries 
* may not be same as the order in which the entries were added.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* None
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/

extern VOID BLS_ShowList(VOID);

/**
* @defgroup BLS_ClearStat BLS_ClearStat
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* VOID BLS_ClearStat(VOID);
* @endcode 
* 
* @par Description
* This function will reset all blacklist statistics.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* None
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/

extern VOID BLS_ClearStat();

/**
* @defgroup BLS_GetStat BLS_GetStat
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* UINT32 BLS_GetStat( BLS_STAT_S * pstBLSStat);
* @endcode 
* 
* @par Description
* This function will give the sum of all the VCPUs blacklist statistics.
* 
* @param[in]   []
* @param[out] pstBLSStat Blacklist statistics structure []
* 
* @retval UINT32 Getting blacklist statistics success. [BLS_OK|]
* @retval UINT32 Recieved null pointer as blacklist statistics structure. [SFE_BLS_ERR_STRUCT_NULLPTR_GETSTAT|]
* @retval UINT32 Failed to get blacklist statistics as blacklist is not initialized. [BLS_ERR_INIT_GETSTAT|]
* 
* @par Dependency
* fwcommon_statistic_api.h
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* BLS_ShowStat
*/

extern UINT32 BLS_GetStat(BLS_STAT_S* pstBLSStat);

/**
* @defgroup BLS_GetVCPUStat BLS_GetVCPUStat
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* UINT32 BLS_GetVCPUStat(UINT32 u32VCPUNum, BLS_STAT_S * pstBLSStat);
* @endcode 
* 
* @par Description
* This function will give statistics of given VCPU. This statistics will be stored 
* in the structure BLS_STAT_S
* 
* @param[in] u32VCPUNum VCPU number for which statistics are required []
* @param[out] pstBLSStat Blacklist statistics structure []
* 
* @retval UINT32 Getting blacklist statistics of given VCPU is success. [BLS_OK|]
* @retval UINT32 Recieved invalid VCPU number. [SFE_BLS_ERR_INVALID_VCPUNUM_GETVCPUSTAT|]
* @retval UINT32 Recieved null pointer as blacklist statistics structure. [SFE_BLS_ERR_STRUCT_NULLPTR_GETVCPUSTAT|]
* @retval UINT32 Failed to get blacklist statistics of given VCPU 
* as blacklist is not initialized. [BLS_ERR_INIT_GETVCPUSTAT|]
* 
* @par Dependency
* fwcommon_statistic_api.h
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* BLS_ShowVCPUStat
*/

extern UINT32 BLS_GetVCPUStat(UINT32 u32VCPUNum, BLS_STAT_S* pstBLSStat);

/**
* @defgroup BLS_ShowStat BLS_ShowStat
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* VOID BLS_ShowStat(VOID);
* @endcode 
* 
* @par Description
* This function will show the total blacklist statstics, that is,  how many packets were passed from blacklist, how
* many packets were dropped from blacklist, how many error packets were recieved by blacklist, and how many dynamic 
* entries were added to blacklist.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* None
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* BLS_GetStat
*/

extern VOID BLS_ShowStat(VOID);

/**
* @defgroup BLS_ShowVCPUStat BLS_ShowVCPUStat
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* VOID BLS_ShowVCPUStat(UINT32 u32VCPUNum);
* @endcode 
* 
* @par Description
* This function will show blacklist statstics of given VCPU, that is, how many packets were passed from blacklist, how
* many packets were dropped from blacklist, how many error packets were recieved by blacklist, and how many dynamic 
* entries were added to blacklist.
* 
* @param[in] u32VCPUNum VCPU number for which statistics is required []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* None
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* BLS_GetVCPUStat
*/

extern VOID BLS_ShowVCPUStat(UINT32 u32VCPUNum);


/**
* @defgroup BLS_SetBindACLGroup BLS_SetBindACLGroup
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* UINT32 BLS_SetBindACLGroup(UINT32 u32GroupNumber);
* @endcode 
* 
* @par Description
* This function will bind ACL group with blacklist. Only basic and advanced ACL groups can be binded with blacklist.
* If zero is passed to this API, it will remove binding of blacklist with ACL. At a time only one ACL group can be 
* binded with blacklist. Calling this API will overwrite the previous binded group.
* 
* @param[in] u32GroupNumber ACL group number which is to be binded with blacklist []
* @param[out]   []
* 
* @retval UINT32 Binding ACL group to blacklist is success. [BLS_OK|]
* @retval UINT32 Indicates received invalid ACL group number. only basic and advanced groups can 
* be binded with blacklist [SFE_BLS_ERR_INVLID_ACL_GROUP_NUMBER|]
* @retval UINT32 Binding ACL group to blacklist is failed, as blacklist is not initialized 
* [BLS_ERR_INIT_SETBINDACLGROUP|]
* 
* @par Dependency
* None
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* BLS_GetBindACLGroup
*/

extern UINT32 BLS_SetBindACLGroup(UINT32 u32GroupNumber);

/**
* @defgroup BLS_GetBindACLGroup BLS_GetBindACLGroup
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* UINT32 BLS_GetBindACLGroup(UINT32 *pu32GroupNumber);
* @endcode 
* 
* @par Description
* This function will get binded ACL group with blacklist. If this API gives binded ACL group as zero, it means
* no ACL group is binded with blacklist.
* 
* @param[in]   []
* @param[out] pu32GroupNumber The pointer in which binded acl group will be stored. []
* 
* @retval UINT32 Getting ACL group binded with blacklist is success. [BLS_OK|]
* @retval UINT32 Indicates received null pointer as input to get ACL group number 
* binded with blacklist [SFE_BLS_ERR_NULLPTR_GET_BINDACLGROUP|]
* @retval UINT32 Getting ACL group binded with blacklist is failed, as blacklist is not initialized 
* [BLS_ERR_INIT_GETBINDACLGROUP|]
* 
* @par Dependency
* None
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* BLS_SetBindACLGroup
*/

extern UINT32 BLS_GetBindACLGroup(UINT32 *pu32GroupNumber);


/**
* @defgroup BLS_ShowBindACLGroup BLS_ShowBindACLGroup
* @ingroup BLF Black List Functions
* @par Prototype
* @code
* VOID BLS_ShowBindACLGroup(VOID);
* @endcode 
* 
* @par Description
* This function will show binded ACL group with blacklist.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* None
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/

extern VOID BLS_ShowBindACLGroup(VOID);

#endif

