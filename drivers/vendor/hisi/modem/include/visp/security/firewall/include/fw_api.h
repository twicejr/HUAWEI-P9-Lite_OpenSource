
#ifndef _FW_API_H_
#define _FW_API_H_



typedef enum tagFWCOMMON_Modules
{
    ALL_FW_MODULES_DISABLED = 0x00,           /* No modules are enabled */
    FWCOMMON_WLS = 0x01,            /* White list */
    FWCOMMON_BLS = 0x02,            /* Black list */
    FWCOMMON_ADBASIC = 0x04,        /*Basic attack defense*/
    FWCOMMON_ADEXTENDED = 0x08,     /*Extended attack defense*/
    FWCOMMON_ALL = (FWCOMMON_WLS | FWCOMMON_BLS 
                    | FWCOMMON_ADBASIC | FWCOMMON_ADEXTENDED ), /*All modules*/
} FWCOMMON_MODULES_E;




/**
* @defgroup FW_Init FW_Init
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FW_Init();
* @endcode 
* 
* @par Description
* This function will call all other firewall modules to initialize.
* 
* @param[in]   []
* @param[out]   []
*
* @retval UINT32 Firewall initialization is success [FW_INIT_OK|] 
* @retval UINT32 Malloc fails in whitelist [WLS_ERR_MALLOC|] 
* @retval UINT32 Registering global variable name fails in whitelist [WLS_ERR_ADD_NAMEDB|] 
* @retval UINT32 Hash table initialization fails for whitelist [WLS_ERR_HASH_INIT|] 
* @retval UINT32 Malloc fails in blacklist [BLS_ERR_MALLOC|] 
* @retval UINT32 Registering global variable name fails in blacklist [BLS_ERR_ADD_NAMEDB|] 
* @retval UINT32 Hash table initialization fails for blacklist [BLS_ERR_HASH_INIT|] 
* @retval UINT32 Malloc fails in malformed attack module [AD_ERR_MALLOC_AD_MALFORM_CFG_S|]
* @retval UINT32 Registering global variable name fails in malformed attack module [AD_ERR_ADD_NAME_DB_MALFORM_CFG_S|]
* @retval UINT32 Malloc fails in malformed attack module [AD_ERR_MALLOC_AD_CFG_S|]
* @retval UINT32 Registering global variable name fails in attack module [AD_ERR_ADD_NAME_DB_AD_CFG_S|]
* @retval UINT32 Hash table initialization fails for attack module [AD_HASH_FAIL_INIT_IF_CFG|]
* @retval UINT32 Hash table initialization fails for flood attack module [AD_HASH_FAIL_INIT_FLOOD_CFG|]
*
* @par Dependency
* sfe_fwcommon_inc.h
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

UINT32 FW_Init(VOID);

/**
* @defgroup FW_InitEx FW_InitEx
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FW_InitEx();
* @endcode 
* 
* @par Description
* This function will call all other firewall modules to initialize.
* 
* @param[in]   []
* @param[out]   []
*
* @retval UINT32 Firewall initialization is success [FW_INIT_OK|] 
* @retval UINT32 Malloc fails in whitelist [WLS_ERR_MALLOC|] 
* @retval UINT32 Registering global variable name fails in whitelist [WLS_ERR_ADD_NAMEDB|] 
* @retval UINT32 Hash table initialization fails for whitelist [WLS_ERR_HASH_INIT|] 
* @retval UINT32 Malloc fails in blacklist [BLS_ERR_MALLOC|] 
* @retval UINT32 Registering global variable name fails in blacklist [BLS_ERR_ADD_NAMEDB|] 
* @retval UINT32 Hash table initialization fails for blacklist [BLS_ERR_HASH_INIT|] 
* @retval UINT32 Malloc fails in malformed attack module [AD_ERR_MALLOC_AD_MALFORM_CFG_S|]
* @retval UINT32 Registering global variable name fails in malformed attack module [AD_ERR_ADD_NAME_DB_MALFORM_CFG_S|]
* @retval UINT32 Malloc fails in malformed attack module [AD_ERR_MALLOC_AD_CFG_S|]
* @retval UINT32 Registering global variable name fails in attack module [AD_ERR_ADD_NAME_DB_AD_CFG_S|]
* @retval UINT32 Hash table initialization fails for attack module [AD_HASH_FAIL_INIT_IF_CFG|]
* @retval UINT32 Hash table initialization fails for flood attack module [AD_HASH_FAIL_INIT_FLOOD_CFG|]
*
* @par Dependency
* sfe_fwcommon_inc.h
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

UINT32 FW_InitEx(VOID);

/**
* @defgroup FW_EnableFWModuleByType FW_EnableFWModuleByType
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FW_EnableFWModuleByType(UINT32 u32Enable,UINT32 u32ModuleType);
* @endcode 
* 
* @par Description
* This function enables the firewall module by type.
* 
* @param[in] u32Enable Value to enable or disable [0/1]
* @param[in] u32ModuleType Module type []
* @param[out]   []
*
* @retval UINT32 Enable/Disable success [FW_OK|] 
* @retval UINT32 Global configuration for firewall not initialized [FW_CFG_NULL_SFE_ENABLE_FW_MODULE_BY_TYPE|] 
* @retval UINT32 Invalid input parameter to the function [FW_INVALID_INPUT_SFE_ENABLE_FW_MODULE_BY_TYPE|] 
*
* @par Dependency
* sfe_fwcommon_inc.h
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
UINT32 FW_EnableFWModuleByType(UINT32 u32Enable,UINT32 u32ModuleType);


/**
* @defgroup FW_IsEnableFWModuleByType FW_IsEnableFWModuleByType
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FW_IsEnableFWModuleByType(UINT32 u32ModuleType);
* @endcode 
* 
* @par Description
* This function checks whether firewall module is enabled by type or not.
* 
* @param[in] u32ModuleType Module type []
* @param[out]   []
*
* @retval UINT32 Disabled [0|] 
* @retval UINT32 Enabled [1|] 
*
* @par Dependency
* sfe_fwcommon_inc.h
* 
* 
* @par Note
* \n
* 
*	- The caller should not pass a invalid u32ModuleType to the function.
*	- The value of u32ModuleType should between FWCOMMON_WLS and
* FWCOMMON_ALL (excluding FWCOMMON_ALL). This function will not check the
* validation of u32ModuleType.
*	- The configuration of firewall module should be initialized before 
* calling this function.
* 
* 
* @par Related Topics
* None
*/ 
UINT32 FW_IsEnableFWModuleByType(UINT32 u32ModuleType);


/**
* @defgroup FW_ShowFirewallModuleStatus FW_ShowFirewallModuleStatus
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* VOID FW_ShowFirewallModuleStatus();
* @endcode 
* 
* @par Description
* This function displays status of all the firewall modules
* 
* @param[in]   []
* @param[out]   []
*
* @retval  [|] 
*
* @par Dependency
* sfe_fwcommon_inc.h
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
VOID FW_ShowFirewallModuleStatus(VOID);


/**
* @defgroup FW_RcvWithLayer FW_RcvWithLayer
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FW_RcvWithLayer(VOID *pstMBuf, FWCOMMON_LAYER_TYPE_E enLayer);
* @endcode 
* 
* @par Description
* This function is used to process the inbound message for Firewall,
* include black list, white list, attack defense, and packet filter.
* 
* @param[in] pstMBuf Pointer to MBUF_S structure []
* @param[in] u32Layer Layer to which the receive function is hooked []
* @param[out]   []
*
* @retval UINT32 The message should be process by protocol stack [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 The message has been process by firewall. PP do not need to process the packet any more.
* [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
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
* FW_Send
*/ 

extern UINT32 FW_RcvWithLayer(VOID *pstMBuf, UINT32 enLayer);

/**
* @defgroup FW_RcvMacLayer FW_RcvMacLayer
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FW_RcvMacLayer(VOID *pstMBuf);
* @endcode 
* 
* @par Description
* This function is used to process the inbound message for Firewall,
* include black list, white list, attack defense, and packet filter.
* 
* @param[in] pstMBuf Pointer to MBUF_S structure []
* @param[out]   []
*
* @retval UINT32 The message should be process by protocol stack [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 The message has been process by firewall. PP do not need to process the packet any more.
* [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
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
* FW_Send
*/ 

extern UINT32 FW_RcvMacLayer(VOID *pstMBuf);


/**
* @defgroup FW_RcvIPLayer FW_RcvIPLayer
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FW_RcvIPLayer(VOID *pstMBuf);
* @endcode 
* 
* @par Description
* This function is used to process the inbound message for Firewall,
* include black list, white list, attack defense, and packet filter.
* 
* @param[in] pstMBuf Pointer to MBUF_S structure []
* @param[out]   []
*
* @retval UINT32 The message should be process by protocol stack [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 The message has been process by firewall. PP do not need to process the packet any more.
* [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
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

extern UINT32 FW_RcvIPLayer(VOID *pstMBuf);


/**
* @defgroup FW_SendWithLayer FW_SendWithLayer
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FW_SendWithLayer(VOID *pstMBuf);
* @endcode 
* 
* @par Description
* Process the outbound message for Firewall, include black list,
* white list, attack defense, and packet filter.
* 
* @param[in] pstMBuf Pointer to MBUF_S structure []
* @param[in] u32Layer Layer to which the receive function is hooked []
* @param[out]   []
*
* @retval UINT32 The message should be processed by protocol stack [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 The message has been processed by firewall. PP do not need to process the packet any more.
* [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
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

extern UINT32 FW_SendWithLayer(VOID *pstMBuf, UINT32 enLayer);


/**
* @defgroup FW_SendMacLayer FW_SendMacLayer
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FW_SendMacLayer(VOID *pstMBuf);
* @endcode 
* 
* @par Description
* Process the outbound message for Firewall, include black list,
* white list, attack defense, and packet filter.
* 
* @param[in] pstMBuf Pointer to MBUF_S structure []
* @param[out]   []
*
* @retval UINT32 The message should be processed by protocol stack [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 The message has been processed by firewall. PP do not need to process the packet any more.
* [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
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

extern UINT32 FW_SendMacLayer(VOID *pstMBuf);


/**
* @defgroup FW_SendIPLayer FW_SendIPLayer
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FW_SendIPLayer(VOID *pstMBuf);
* @endcode 
* 
* @par Description
* Process the outbound message for Firewall, include black list,
* white list, attack defense, and packet filter.
* 
* @param[in] pstMBuf Pointer to MBUF_S structure []
* @param[out]   []
*
* @retval UINT32 The message should be processed by protocol stack [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 The message has been processed by firewall. PP do not need to process the packet any more.
* [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
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

extern UINT32 FW_SendIPLayer(VOID *pstMBuf);

/**
* @defgroup FW_Rcv FW_Rcv
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FW_Rcv(SFE_MBUF_S *pstMBuf);
* @endcode 
* 
* @par Description
* This function is used to process the inbound message for Firewall,
* include black list, white list, attack defense, and packet filter.
* 
* @param[in] pstMBuf Pointer to SFE_MBUF_S structure []
* @param[out]   []
*
* @retval UINT32 The message should be process by protocol stack [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 The message should be drop by protocol stack [IP_PP4_INTER_PROCESS_ERROR|] 
* @retval UINT32 The message has been process by firewall. PP do not need to process the packet any more.
* [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
* 
* @par Dependency
*    - sfe_fwcommon_inc.h
*    - fw_config.h
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* FW_Send
*/ 

UINT32 FW_Rcv(VOID *pstMBuf);

/**
* @defgroup FW_Send
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FW_Send(SFE_MBUF_S *pstMBuf);
* @endcode 
* 
* @par Description
* Process the outbound message for Firewall, include black list,
* white list, attack defense, and packet filter.
* 
* @param[in] pstMBuf Pointer to SFE_MBUF_S structure []
* @param[out]   []
*
* @retval UINT32 The message should be processed by protocol stack [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 The message should be dropped by protocol stack [IP_PP4_INTER_PROCESS_ERROR|] 
* @retval UINT32 The message has been processed by firewall. PP do not need to process the packet any more.
* [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
* 
* @par Dependency
*    - sfe_fwcommon_inc.h
*    - fw_config.h
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* FW_Rcv
*/

UINT32 FW_Send(VOID *pstMBuf);

/**
* @defgroup FW_Rcv_HardCode FW_Rcv_HardCode
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FW_Rcv_HardCode(SFE_MBUF_S *pstMBuf);
* @endcode 
* 
* @par Description
* This function is used to process the inbound message for Firewall,
* include black list, white list, attack defense, and packet filter.
* It is a hard code version of FW_Rcv(). And the performance is more better than FW_Rcv(). 
* However, the firewall module process flow can not be modified with the definition of g_arrInboundFWTable[],  
* g_arrInboundBasicADTable[] and g_arrInboundExtendedADTable[] in the shell.
* 
* @param[in] pstMBuf Pointer to SFE_MBUF_S structure []
* @param[out]   []
*
* @retval UINT32 The message should be process by protocol stack [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 The message should be drop by protocol stack [IP_PP4_INTER_PROCESS_ERROR|] 
* @retval UINT32 The message has been process by firewall. PP do not need to process the packet any more.
* [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
* 
* @par Dependency
*    - sfe_fwcommon_inc.h
*    - fw_config.h
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* FW_Rcv_HardCode
*/ 
UINT32 FW_Rcv_HardCode(VOID *pstMBuf);

/**
* @defgroup FW_GetVersion FW_GetVersion
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FW_GetVersion(CHAR *pcVerInfo);
* @endcode 
* 
* @par Description
* This function is used to get the version of Firewall CBB
* 
* @param[in]   []
* @param[out] pi8VerInfo Pointer for storing the verion info []
*
* @retval UINT32 Get Version successful [FW_OK|]
* @retval UINT32 NULL pointer passed for getting the version [FW_NULL_INPUT_PASSED_GET_VERSION|] 
* 
* @par Dependency
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*/
UINT32 FW_GetVersion(CHAR *pcVerInfo);

/**
* @defgroup FW_ShowVersion FW_ShowVersion
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* VOID FW_ShowVersion(VOID);
* @endcode 
* 
* @par Description
* This function is used to show the version of Firewall CBB
* 
* @param[in]   []
* @param[out]   []
*
* @retval  [|]
* 
* @par Dependency
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*/
VOID FW_ShowVersion(VOID);

#endif /*_FW_API_H_*/

