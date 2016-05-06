/*************************************************************************
Copyright (C), 2004, Huawei Tech. Co., Ltd.
FileName: wls_api.h
Version: 1
Author:  Ramalingeswara Reddy 72335
Creation Date: 2009-08-07
Description: This is header file for wls_process.c

History:<author>                     <date>          <desc>     
        Ramalingeswara Reddy 72335   2009-08-07      Create
**************************************************************************/
#ifndef _WLS_API_H_
#define _WLS_API_H_


#ifdef  __cplusplus
extern "C" {
#endif

/**
* @defgroup enumWLSReturnCode WLS_RETURN_CODE
* @ingroup WLE White List Enums
* @par Prototype
* @code
* typedef enum enumWLSReturnCode
* {
*     WLS_MAXRULEREACHED=1,
*     WLS_ENTRY_NOT_EXISTS,
* }WLS_RETURN_CODE;
* @endcode 
* 
*
* @par Description
* This enum consists of Whitelist API return values.
* 
* @datastruct WLS_MAXRULEREACHED=1 Indicates maximum limit reached while inserting an entry into Whitelist.
* @datastruct WLS_ENTRY_NOT_EXISTS Indicates entry does not exists in Whitelist.
*/

typedef enum enumWLSReturnCode
{
    WLS_MAXRULEREACHED = 1,
    WLS_ENTRY_NOT_EXISTS,
}WLS_RETURN_CODE;


/**
* @defgroup tagWLS_INFO WLS_INFO_S/PWLS_INFO_S
* @ingroup WLS White List Structures
* @par Prototype
* @code
* typedef struct tagWLS_INFO
* {
*     UINT32  u32Ip;
* } WLS_INFO_S,*PWLS_INFO_S;
* @endcode 
* 
* @par Description
* This structure is used to configure / retrieve / delete entries in the Whitelist.
* 
* @datastruct u32Ip IP in Whitelist which is configured / retrieved / deleted.
*/
typedef struct tagWLS_INFO
{
    UINT32  u32Ip;    
} WLS_INFO_S,*PWLS_INFO_S;

/**
* @defgroup enumWLSErrCode WLS_ERR_CODE_E
* @ingroup FEC Firewall Error Codes
* @par Prototype
* @code
* typedef enum enumWLSErrCode
* {
*     WLS_OK=0,
*     WLS_ERR_ADD_INTERNAL_HASH_FAIL=FWIPSAFE_FW_WLS_BEGIN_RET_CODE + 1,
*     WLS_ERR_ADD_NAMEDB,
*     WLS_ERR_MALLOC,
*     WLS_ERR_HASH_INIT,
*     WLS_ERR_INIT_ENABLE,
*     WLS_ERR_INIT_DISABLE,
*     WLS_ERR_INIT_ADDENTRY,
*     WLS_ERR_INIT_DELENTRY,
*     SFE_WLS_ERR_ADD_NULLPTR_INPUT,
*     SFE_WLS_ERR_DELETE_NULLPTR_INPUT
*     WLS_ERR_OPEN_FAIL_OPENLIST,
*     WLS_ERR_GET_FAIL_GETNEXT,
*     WLS_ERR_CLOSE_FAIL_CLOSELIST,
*     SFE_WLS_ERR_NULLPTR_OPENLIST,
*     SFE_WLS_ERR_HANDLE_NULLPTR_GETNEXT,
*     SFE_WLS_ERR_HANDLE_NULLPTR_CLOSELIST,
*     WLS_ERR_INIT_OPENLIST,
*     WLS_ERR_INIT_GETNEXT,
*     WLS_ERR_INIT_CLOSELIST,
*     SFE_WLS_ERR_STRUCT_NULLPTR_GETNEXT,
*     SFE_WLS_ERR_STRUCT_NULLPTR_GETSTAT,
*     WLS_ERR_INIT_GETSTAT,
*     SFE_WLS_ERR_STRUCT_NULLPTR_GETVCPUSTAT,
*     WLS_ERR_INIT_GETVCPUSTAT,
*     SFE_WLS_ERR_INVALID_VCPUNUM_GETVCPUSTAT,
*     WLS_ERR_STAT_INIT,
*     WLS_ERR_GET_PRECONFIG_FAIL
* }WLS_ERR_CODE_E;
* @endcode 
* 
* @par Description
* This enum consists of the Whitelist API error codes.
* 
* @datastruct WLS_OK=0 Indicates Whitelist operation success.
* @datastruct WLS_ERR_ADD_INTERNAL_HASH_FAIL=FWIPSAFE_FW_WLS_BEGIN_RET_CODE+1 Indicates error occurred while inserting an 
* entry into Whitelist.
* @datastruct WLS_ERR_ADD_NAMEDB Indicates error in registering the global variable name.
* @datastruct WLS_ERR_MALLOC Indicates error in allocating memory.
* @datastruct WLS_ERR_HASH_INIT Indicates error in initializing hash for Whitelist.
* @datastruct WLS_ERR_INIT_ENABLE Indicates failed to enable Whitelist as Firewall initialization is not done.
* @datastruct WLS_ERR_INIT_DISABLE Indicates failed to disable Whitelist as Firewall initialization is not done.
* @datastruct WLS_ERR_INIT_ADDENTRY Indicates error while inserting an entry into Whitelist as
* Firewall initialization is not done.
* @datastruct WLS_ERR_INIT_DELENTRY Indicates error while removing an entry from Whitelist as
* Firewall initialization is not done.
* @datastruct SFE_WLS_ERR_ADD_NULLPTR_INPUT Indicates received NULL pointer as input argument to add an entry.
* @datastruct SFE_WLS_ERR_DELETE_NULLPTR_INPUT Indicates received NULL pointer as input argument to delete an entry.
* @datastruct WLS_ERR_OPEN_FAIL_OPENLIST Indicates failed to open the Whitelist.
* @datastruct WLS_ERR_GET_FAIL_GETNEXT Indicates failed to get next entry from Whitelist.
* @datastruct WLS_ERR_CLOSE_FAIL_CLOSELIST Indicates failed to close the Whitelist
* @datastruct SFE_WLS_ERR_NULLPTR_OPENLIST Indicates received NULL pointer as input argument to open the Whitelist.
* @datastruct SFE_WLS_ERR_HANDLE_NULLPTR_GETNEXT Indicates received NULL pointer as handle to get next entry from Whitelist.
* @datastruct SFE_WLS_ERR_HANDLE_NULLPTR_CLOSELIST Indicates received NULL pointer as handle to close the Whitelist.
* @datastruct WLS_ERR_INIT_OPENLIST Indicates failed to open the Whitelist as Firewall initialization is not done.
* @datastruct WLS_ERR_INIT_GETNEXT Indicates failed to get next entry from Whitelist as Firewall initialization 
* is not done.
* @datastruct WLS_ERR_INIT_CLOSELIST Indicates failed to close the Whitelist as Firewall initialization is not 
* done.
* @datastruct SFE_WLS_ERR_STRUCT_NULLPTR_GETNEXT Indicates received NULL pointer as Whitelist structure to get next 
* entry from Whitelist.
* @datastruct SFE_WLS_ERR_STRUCT_NULLPTR_GETSTAT Indicates received NULL pointer as Whitelist statistics structure.
* @datastruct WLS_ERR_INIT_GETSTAT Indicates failed to get all statistics of Whitelist as Whitelist is not
* initialized.
* @datastruct SFE_WLS_ERR_STRUCT_NULLPTR_GETVCPUSTAT Indicates received NULL pointer as Whitelist statistics structure.
* @datastruct WLS_ERR_INIT_GETVCPUSTAT Indicates failed to get statistics of given VCPU as Whitelist is not
* initialized.
* @datastruct SFE_WLS_ERR_INVALID_VCPUNUM_GETVCPUSTAT Indicates invalid VCPU number while getting statistics in.
* @datastruct WLS_ERR_STAT_INIT Indicates failed to initialize statistics for Whitelist.
* @datastruct WLS_ERR_GET_PRECONFIG_FAIL Indicates failed to get the pre configuration data for Whitelist.
*/

typedef enum enumWLSErrCode
{
    WLS_OK = 0,     
    WLS_ERR_ADD_INTERNAL_HASH_FAIL = FWIPSAFE_FW_WLS_BEGIN_RET_CODE + 1, 
    WLS_ERR_ADD_NAMEDB,      
    WLS_ERR_MALLOC,          
    WLS_ERR_HASH_INIT,       
    WLS_ERR_INIT_ENABLE,
    WLS_ERR_INIT_DISABLE,
    WLS_ERR_INIT_ADDENTRY,
    WLS_ERR_INIT_DELENTRY,
    SFE_WLS_ERR_ADD_NULLPTR_INPUT,
    SFE_WLS_ERR_DELETE_NULLPTR_INPUT,
    WLS_ERR_OPEN_FAIL_OPENLIST,
    WLS_ERR_GET_FAIL_GETNEXT,
    WLS_ERR_CLOSE_FAIL_CLOSELIST,
    SFE_WLS_ERR_NULLPTR_OPENLIST,
    SFE_WLS_ERR_HANDLE_NULLPTR_GETNEXT,
    SFE_WLS_ERR_HANDLE_NULLPTR_CLOSELIST,
    WLS_ERR_INIT_OPENLIST,
    WLS_ERR_INIT_GETNEXT,
    WLS_ERR_INIT_CLOSELIST,
    SFE_WLS_ERR_STRUCT_NULLPTR_GETNEXT,
    SFE_WLS_ERR_STRUCT_NULLPTR_GETSTAT,
    WLS_ERR_INIT_GETSTAT,
    SFE_WLS_ERR_STRUCT_NULLPTR_GETVCPUSTAT,
    WLS_ERR_INIT_GETVCPUSTAT,
    SFE_WLS_ERR_INVALID_VCPUNUM_GETVCPUSTAT,
    WLS_ERR_STAT_INIT,
    WLS_ERR_GET_PRECONFIG_FAIL
}WLS_ERR_CODE_E;

/**
* @defgroup WLS_Enable WLS_Enable
* @ingroup WLF White List Functions
* @par Prototype
* @code
* UINT32 WLS_Enable(VOID);
* @endcode 
* 
* @par Description
* This function is used to enable Whitelist. This function is used only when Whitelist must be enabled in the 
* complete Firewall functionality. The user who uses Whitelist separately need not call this function. 
* 
* @param[in]   []
* @param[out]   []
* 
* @retval UINT32 Enabling Whitelist is success [WLS_OK|]
* @retval UINT32 Enabling Whitelist has failed as Firewall is not initialized [WLS_ERR_INIT_ENABLE|]
* 
* @par Dependency
* None
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* WLS_Disable
*/ 
extern UINT32 WLS_Enable(VOID);

/**
* @defgroup WLS_Disable WLS_Disable
* @ingroup WLF White List Functions
* @par Prototype
* @code
* UINT32 WLS_Disable(VOID);
* @endcode 
* 
* @par Description
* This function is used to disable Whitelist. This function is used only when Whitelist must be disabled in the 
* complete Firewall functionality. The user who uses Whitelist separately need not call this function.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval UINT32 Disabling Whitelist is success. [WLS_OK|]
* @retval UINT32 Disabling Whitelist has failed as Firewall is not initialized [WLS_ERR_INIT_DISABLE|]
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
* WLS_Enable
*/ 
extern UINT32 WLS_Disable(VOID);

/**
* @defgroup WLS_AddEntry WLS_AddEntry
* @ingroup WLF White List Functions
* @par Prototype
* @code
* UINT32 WLS_AddEntry( WLS_INFO_S *pstWLSInfo);
* @endcode 
* 
* @par Description
* This function is used to insert an entry into Whitelist. 
* It accepts a structure in which you can configure the IP. This IP will then be
* inserted into the Whitelist by this function.
* 
* @param[in] pstWLSInfo Pointer to WLS_INFO_S structure. []
* @param[out]   []
* 
* @retval UINT32 Adding entry to Whitelist is success. [WLS_OK|]
* @retval UINT32 Received NULL pointer as input argument. [SFE_WLS_ERR_ADD_NULLPTR_INPUT|]
* @retval UINT32 Failed to insert entry in Whitelist as Firewall is not initialized [WLS_ERR_INIT_ADDENTRY|]
* @retval UINT32 Failed to insert entry in Whitelist as hash operation failed. [WLS_ERR_ADD_INTERNAL_HASH_FAIL|]
* @retval UINT32 Maximum number of rules reached for Whitelist. [WLS_MAXRULEREACHED|]
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
* WLS_DelEntry
*/ 
extern UINT32 WLS_AddEntry(WLS_INFO_S *pstWLSInfo);

/**
* @defgroup WLS_DelEntry WLS_DelEntry
* @ingroup WLF White List Functions
* @par Prototype
* @code
* UINT32 WLS_DelEntry(const WLS_INFO_S *pstWLSInfo);
* @endcode 
* 
* @par Description
* This function is used to delete an entry from Whitelist. 
* It accepts a structure in which you can configure the IP. This IP will then be 
* deleted from the Whitelist by this function.
* 
* @param[in] pstWLSInfo Pointer to WLS_INFO_S structure. []
* @param[out]   []
* 
* @retval UINT32 Deleting entry from Whitelist is success. [WLS_OK|]
* @retval UINT32 Received NULL pointer as input argument. [SFE_WLS_ERR_DELETE_NULLPTR_INPUT|]
* @retval UINT32 Failed to delete entry from Whitelist as Firewall is not initialized. [WLS_ERR_INIT_DELENTRY|]
* @retval UINT32 The entry does not exists in Whitelist. [WLS_ENTRY_NOT_EXISTS|]
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
* WLS_AddEntry
*/ 
extern UINT32 WLS_DelEntry(const WLS_INFO_S *pstWLSInfo);

/**
* @defgroup WLS_Init WLS_Init
* @ingroup WLF White List Functions
* @par Prototype
* @code
* UINT32 WLS_Init(VOID);
* @endcode 
* 
* @par Description
* This function is used to initialize Whitelist. This is called internally from Firewall Init function.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval UINT32 Initializing Whitelist is success. [WLS_OK|]
* @retval UINT32 Error in getting preconfiguration data for Whitelist. [WLS_ERR_GET_PRECONFIG_FAIL|]
* @retval UINT32 Failed to allocate memory for Whitelist. [WLS_ERR_MALLOC|]
* @retval UINT32 Registering global variable name failed in Whitelist. [WLS_ERR_ADD_NAMEDB|]
* @retval UINT32 Hash table initialization failed for Whitelist. [WLS_ERR_HASH_INIT|]
* @retval UINT32 Statistics initialization failed for Whitelist. [WLS_ERR_STAT_INIT|]
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
UINT32 WLS_Init(VOID);


/**
* @defgroup WLS_OpenList WLS_OpenList
* @ingroup WLF White List Functions
* @par Prototype
* @code
* UINT32 WLS_OpenList(VOID **ppHandle);
* @endcode 
* 
* @par Description
* This function is used to open Whitelist.
* 
* @param[in,out] ppHandle Pointer to a pointer to the Whitelist handle[]
* 
* @retval UINT32 Opening Whitelist is success. [FWCOMMON_ITERATOR_ITEM_EXIST|]
* @retval UINT32 Received NULL pointer as input argument to open Whitelist. 
* [SFE_WLS_ERR_NULLPTR_OPENLIST|]
* @retval UINT32 Failed to open Whitelist as Whitelist is not initialized. [WLS_ERR_INIT_OPENLIST|]
* @retval UINT32 Failed to open Whitelist as iterator operation failed. [WLS_ERR_OPEN_FAIL_OPENLIST|]
* @retval UINT32 No item exists in Whitelist. [FWCOMMON_ITERATOR_ITEM_NOT_EXIST|]
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
* WLS_CloseList
*/ 

extern UINT32 WLS_OpenList(VOID **ppHandle);

/**
* @defgroup WLS_GetNext WLS_GetNext
* @ingroup WLF White List Functions
* @par Prototype
* @code
* UINT32 WLS_GetNext(VOID *pHandle, WLS_INFO_S * pstWLSInfo);
* @endcode 
* 
* @par Description
* This function is used to get next entry from Whitelist. On calling this API in a loop, we can get the entries of 
* the Whitelist. On reaching the end of the list, this API will return failure once, after which it will again continue
* to give the entries of the list. The order of getting the entries may not be same as the order in which the entries were added.
*
* @param[in] pHandle Handle to Whitelist []
* @param[out] pstWLSInfo Structure to get the Whitelist entries[]
* 
* @retval UINT32 Getting next item from Whitelist is success. [FWCOMMON_ITERATOR_ITEM_EXIST|]
* @retval UINT32 NULL pointer is passed for handle to Whitelist. [SFE_WLS_ERR_HANDLE_NULLPTR_GETNEXT|]
* @retval UINT32 NULL pointer is passed for pointer to Whitelist structure. [SFE_WLS_ERR_STRUCT_NULLPTR_GETNEXT|]
* @retval UINT32 Failed to get next entry from Whitelist as Whitelist is not initialized. [WLS_ERR_INIT_GETNEXT|]
* @retval UINT32 Failed to get next entry from Whitelist as iterator operation failed. [WLS_ERR_GET_FAIL_GETNEXT|]
* @retval UINT32 No item exists in Whitelist. [FWCOMMON_ITERATOR_ITEM_NOT_EXIST|]
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
*	- WLS_CloseList
*	- WLS_OpenList
*/ 

extern UINT32 WLS_GetNext(VOID *pHandle, WLS_INFO_S* pstWLSInfo);

/**
* @defgroup WLS_CloseList WLS_CloseList
* @ingroup WLF White List Functions
* @par Prototype
* @code
* UINT32 WLS_CloseList(VOID *pHandle);
* @endcode 
* 
* @par Description
* This function is used to close Whitelist.
* 
* @param[in] pHandle Handle to Whitelist []
* @param[out]   []
* 
* @retval UINT32 Closing Whitelist is success. [WLS_OK|]
* @retval UINT32 Received NULL pointer to close Whitelist. [SFE_WLS_ERR_HANDLE_NULLPTR_CLOSELIST|]
* @retval UINT32 Failed to close Whitelist as Whitelist is not initialized. [WLS_ERR_INIT_CLOSELIST|]
* @retval UINT32 Failed to close Whitelist as iterator operation failed. [WLS_ERR_CLOSE_FAIL_CLOSELIST|]
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
* WLS_OpenList
*/

extern UINT32 WLS_CloseList(VOID *pHandle);

/**
* @defgroup WLS_ShowList WLS_ShowList
* @ingroup WLF White List Functions
* @par Prototype
* @code
* VOID WLS_ShowList(VOID);
* @endcode 
* 
* @par Description
* This function is used to show configured IP in Whitelist. The order of showing the entries 
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

extern VOID WLS_ShowList(VOID);

/**
* @defgroup WLS_ClearStat WLS_ClearStat
* @ingroup WLF White List Functions
* @par Prototype
* @code
* VOID WLS_ClearStat(VOID);
* @endcode 
* 
* @par Description
* This function will reset all the VCPU statistics of Whitelist.
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

extern VOID WLS_ClearStat(VOID);

/**
* @defgroup WLS_GetStat WLS_GetStat
* @ingroup WLF White List Functions
* @par Prototype
* @code
* UINT32 WLS_GetStat( WLS_STAT_S * pstWLSStat);
* @endcode 
* 
* @par Description
* This function will give the sum of all the VCPU statistics.
* 
* @param[in]   []
* @param[out] pstWLSStat Whitelist statistics structure []
* 
* @retval UINT32 Getting Whitelist statistics is success. [WLS_OK|]
* @retval UINT32 Received NULL pointer as Whitelist statistics structure. [SFE_WLS_ERR_STRUCT_NULLPTR_GETSTAT|]
* @retval UINT32 Failed to get Whitelist statistics as Whitelist is not initialized. [WLS_ERR_INIT_GETSTAT|]
* 
* @par Dependency
*	- fwcommon_statistic_api.h
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* WLS_ShowStat
*/

extern UINT32 WLS_GetStat(WLS_STAT_S* pstWLSStat);

/**
* @defgroup WLS_GetVCPUStat WLS_GetVCPUStat
* @ingroup WLF White List Functions
* @par Prototype
* @code
* UINT32 WLS_GetVCPUStat(UINT32 u32VCPUNum, WLS_STAT_S * pstWLSStat);
* @endcode 
* 
* @par Description
* This function will give statistics of the given VCPU.
* 
* @param[in] u32VCPUNum VCPU number for which statistics are required []
* @param[out] pstWLSStat Whitelist statistics structure []
* 
* @retval UINT32 Getting Whitelist statistics of given VCPU is success. [WLS_OK|]
* @retval UINT32 Received NULL pointer as Whitelist statistics structure. [SFE_WLS_ERR_STRUCT_NULLPTR_GETVCPUSTAT|]
* @retval UINT32 Received invalid VCPU number. [SFE_WLS_ERR_INVALID_VCPUNUM_GETVCPUSTAT|]
* @retval UINT32 Failed to get Whitelist statistics of given VCPU 
* because Whitelist is not initialized. [WLS_ERR_INIT_GETVCPUSTAT|]
* 
* @par Dependency
*	- fwcommon_statistic_api.h
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* WLS_ShowVCPUStat
*/

extern UINT32 WLS_GetVCPUStat(UINT32 u32VCPUNum, WLS_STAT_S* pstWLSStat);

/**
* @defgroup WLS_ShowStat WLS_ShowStat
* @ingroup WLF White List Functions
* @par Prototype
* @code
* VOID WLS_ShowStat(VOID);
* @endcode 
* 
* @par Description
* This function will show the sum of all VCPU Whitelist statistics, that is, how many packet's source IP matched with 
* Whitelist entries, how many packet's source IP did not match with Whitelist entries, and how many error
* packets were received by Whitelist.
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
* WLS_GetStat
*/

extern VOID WLS_ShowStat(VOID);

/**
* @defgroup WLS_ShowVCPUStat WLS_ShowVCPUStat
* @ingroup WLF White List Functions
* @par Prototype
* @code
* VOID WLS_ShowVCPUStat(UINT32 u32VCPUNum);
* @endcode 
* 
* @par Description
* This function will show Whitelist statistics of given VCPU, that is, how many packet's source IP matched with 
* Whitelist entries, how many packet's source IP did not match with Whitelist entries, and how many error
* packets were received by Whitelist.
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
* WLS_GetVCPUStat
*/
extern VOID WLS_ShowVCPUStat(UINT32 u32VCPUNum);

#ifdef  __cplusplus
}
#endif

#endif

