/*************************************************************************
Copyright (C), 2004, Huawei Tech. Co., Ltd.
FileName: fw_process.h
Version: 1
Author:  Ramalingeswara Reddy 72335
Creation Date: 2009-08-17
Description: This file header file for firewall inbound/outbound process file

History:<author>                        <date>          <desc>
         Ramalingeswara Reddy 72335     2009-08-07      Create
*************************************************************************/
#ifndef _FW_API_SH_H_
#define _FW_API_SH_H_

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef ETHARP_INPUT
#define ETHARP_INPUT 0
#endif

#ifndef ETHARP_OUTPUT
#define ETHARP_OUTPUT 1
#endif

/*Declare hook register function*/
typedef ULONG (*HOOK_FUNC)(VOID *pstMBuf);




/**
* @defgroup FW_Hook FW_Hook
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FW_Hook(UINT32 u32Priority);
* @endcode 
* 
* @par Description
* This function will hook firewall functions to the layers
* 
* @param[in] u32Priority Priority []
* @param[out]   []
*
* @retval UINT32 Hooking success [FWCOMMON_HOOK_OK|]
* @retval UINT32 InboundFilter register failed for MAC layer [FW_ERR_MAC_INBOUND_REGISTER_FAILED|]
* @retval UINT32 InboundFilter register failed for MAC layer [FW_ERR_MAC_OUTBOUND_REGISTER_FAILED|]
* @retval UINT32 InboundFilter already registered in IP layer [FW_ERR_IP_INBOUND_ALREADY_REGISTERED|]
* @retval UINT32 InboundFilter register failed for IP layer [FW_ERR_IP_INBOUND_REGISTER_FAILED|]
* @retval UINT32 OutboundFilter already registered in IP layer [FW_ERR_IP_OUTBOUND_ALREADY_REGISTERED|]
* @retval UINT32 OutboundFilter register failed for IP layer [FW_ERR_IP_OUTBOUND_REGISTER_FAILED|]
* 
* @par Dependency
*    - sfe_fwcommon_inc.h
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

extern UINT32 FW_Hook(UINT32 u32Priority);


/**
* @defgroup FWCOMMON_Hook FWCOMMON_Hook
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FWCOMMON_Hook(VOID);
* @endcode 
* 
* @par Description
* This is empty implementation of the hook, the function FW_Hook should be called for hooking
* 
* @param[in] u32Priority Priority []
* @param[out]   []
*
* @retval UINT32 Hooking success [FWCOMMON_HOOK_OK|]
*
* @par Dependency
*    - sfe_fwcommon_inc.h
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

UINT32 FWCOMMON_Hook(VOID);

#ifdef  __cplusplus
}
#endif

#endif/*_FW_PROCESS_H_*/

