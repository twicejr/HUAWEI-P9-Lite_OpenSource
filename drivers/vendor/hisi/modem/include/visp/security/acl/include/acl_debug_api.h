/*************************************************************************
 *
 *              Copyright 2009, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 *
 *-----------------------------------------------------------------------*
 *
 *                              fwcommon_debug.h
 *
 *  Project Code: DOPRA VISP V1R8C02 Firewall
 *   Module Name: Firewall Debug Module 
 *   Version    : 1
 *  Date Created: 2009-08-13
 *        Author: Mayur 71325
 *   Description: Header file contains the wrapper function declaration for the
 *                for the firewall log module for control plane and data plane. This functions are 
 *                wrapper function of the TCPIP Log Module for control plane and SFE Log Module for 
 *                data plane. This settings are not local to only firewall module but the applicable
 *                to whole control plane and data plane VISP module.
 *                
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2009-08-13      Mayur 71325	    Create
 ************************************************************************/

#ifndef __ACL_DEBUG_H__
#define __ACL_DEBUG_H__

#ifdef __cplusplus
    extern "C"{
#endif /* __cplusplus */


/**
* @defgroup aa Debugging API Reference
* This section contains all the descriptions for functions, enums, error codes,
* structures, and callback functions.
*/

/**
* @defgroup d Debugging Functions
* @ingroup aa Debugging API Reference
* This section contains debugging functions.
*/

/**
* @defgroup ACLCOMMON_RegLogHookFunc ACLCOMMON_RegLogHookFunc
* @ingroup d Debugging Functions
* @par Prototype
* @code
* UINT32 ACLCOMMON_RegLogHookFunc(FWIPSAFE_LOG_HOOK_FUNC_S* pstHookFunc);
* @endcode 
* 
* @par Description
* This function is used to set the callback function for the firewall log in control plane only. Firewall calls the 
* registered function for any log. These callback functions will be called based on
* firewall settings.
* 
* @param[in] pstHookFunc Pointer to the ACLCOMMON_LOG_HOOK_FUNC_S.  []
* @param[out]   []
* 
* @retval UINT32 On Success [FW_OK|]
* @retval UINT32 pstHookFunc is NULL pointer [FWIPSAFE_LOG_REGLOG_ERR_INPUT_NULL_POINTER|]
* @retval UINT32 Please refer the return value of TCPIP_RegFuncLogOutputHook of VISP control plane [|]
* 
* @par Dependency
* tcpip/public/tcpip_pub_api.h
* 
* 
* 
* @par Note
* \n
* 
* Refer SFE_FWCOMMON_RegLogHookFunc to set the log callback in data plane.
* Same can be set by TCPIP_RegFuncLogOutputHook function also.
* 
* 
* @par Related Topics
* ACLCOMMON_LOG_HOOK_FUNC_S
*/ 
UINT32 ACLCOMMON_RegLogHookFunc(FWIPSAFE_LOG_HOOK_FUNC_S* pstHookFunc);

/**
* @defgroup ACLCOMMON_SetLogLevel ACLCOMMON_SetLogLevel
* @ingroup d Debugging Functions
* @par Prototype
* @code
* UINT32 ACLCOMMON_SetLogLevel(UINT32 u32LogLevel);
* @endcode 
* 
* @par Description
* This function sets the firewall log level in control plane and data plane. 
* Log level can be of any value of FWCOMMON_LOG_LEVEL_E. Log level having higher priority than 
* u32LogLevel will be enabled. Based on this setting, firewall calls the log callback functions.
* 
* @param[in] u32LogLevel Indicates firewall log level. Default value for control plane 
*            is FWCOMMON_LOG_LEVEL_DEBUG and for data plane it is FWCOMMON_LOG_LEVEL_INFO [FWCOMMON_LOG_LEVEL_E]
* @param[out]   []
* 
* @retval UINT32 On Success [FW_OK|]
* @retval UINT32 Refer the return value of TCPIP_SetLogLevel of VISP control plane [|]
* @retval UINT32 Refer the return value of SFE_SetLogLevel of VISP data plane [|]
* 
* 
* @par Dependency
* tcpip/public/tcpip_debug.h
* ipsfe/public/debug/include/sfe_log.h
* 
* 
* @par Note
* \n
* 
* Control plane and data plane log level can also be set by TCPIP_GetLogLevel and SFE_GetLogLevel respectively.
* 
* 
* @par Related Topics
* FWCOMMON_LOG_LEVEL_E
*/ 
UINT32 ACLCOMMON_SetLogLevel(UINT32 u32LogLevel);

/**
* @defgroup ACLCOMMON_GetLogLevel ACLCOMMON_GetLogLevel
* @ingroup d Debugging Functions
* @par Prototype
* @code
* UINT32 ACLCOMMON_GetLogLevel(UINT32* pu32LogLevel);
* @endcode 
* 
* @par Description
* This function gets the firewall log level. If control plane and data plane have different
* log levels, then output parameter contains the log level of data plane.
*
* @param[in]   []
* @param[out] pu32LogLevel Firewall log level [FWCOMMON_LOG_LEVEL_DEBUG|FWCOMMON_LOG_LEVEL_E]
* 
* @retval UINT32 On Success [FW_OK|]
* @retval UINT32 pu32LogLevel is NULL pointer [FWCOMMON_DEBUG_REGGETLOGLEVEL_NULLPT|]
* @retval UINT32 Please refer the return value of TCPIP_GetLogLevel of VISP control plane [|]
* @retval UINT32 Please refer the return value of SFE_GetLogLevel of VISP data plane [|]
* 
* @par Dependency
* tcpip/public/tcpip_debug.h
* ipsfe/public/debug/include/sfe_log.h
* 
* 
* @par Note
* \n
* 
* Control plane and data plane log level can be get by TCPIP_GetLogLevel and SFE_GetLogLevel respectively.
* 
* 
* @par Related Topics
* FWCOMMON_LOG_LEVEL_E
*/ 
UINT32 ACLCOMMON_GetLogLevel(UINT32* pu32LogLevel);

/**
* @defgroup ACLCOMMON_SetLogType ACLCOMMON_SetLogType
* @ingroup d Debugging Functions
* @par Prototype
* @code
* UINT32 ACLCOMMON_SetLogType(UINT32 ul32WarningLogEnable, 
*             UINT32 u32CfgLogEnable, 
*             UINT32 u32RunLogEnable);
* @endcode 
* 
* @par Description
* This function sets the firewall warning, configuration and run time log type status for
* control plane and data plane. Based on this setting, firewall calls the log callback functions.
* 
* @param[in] ul32WarningLogEnable Warning log can be enabled or disabled. 
*            [FWCOMMON_DEBUG_ENABLE-FWCOMMON_DEBUG_DISABLE/FWCOMMON_DEBUG_ENABLE]
* @param[in] u32CfgLogEnable Configuration log can be enabled or disabled. 
*            [FWCOMMON_DEBUG_ENABLE-FWCOMMON_DEBUG_DISABLE/FWCOMMON_DEBUG_ENABLE]
* @param[in] u32RunLogEnable Runtime log can be enabled or disabled. 
*            [FWCOMMON_DEBUG_ENABLE-FWCOMMON_DEBUG_DISABLE/FWCOMMON_DEBUG_ENABLE]
* @param[out]   []
* 
* @retval UINT32 On Success [FW_OK|]
* @retval UINT32 Please refer the return value of TCPIP_SetLogType of VISP control plane [|]
* @retval UINT32 Please refer the return value of SFE_SetLogType of VISP data plane [|]
* 
* @par Dependency
* tcpip/public/tcpip_debug.h
* ipsfe/public/debug/include/sfe_log.h
* 
* @par Note
* \n
* 
* Control plane and data plane log type can also be set by TCPIP_SetLogType and SFE_SetLogType respectively.
* 
* @par Related Topics
* None
*/ 
UINT32 ACLCOMMON_SetLogType(UINT32 ul32WarningLogEnable, 
            UINT32 u32CfgLogEnable, 
            UINT32 u32RunLogEnable);

/**
* @defgroup ACLCOMMON_GetLogType ACLCOMMON_GetLogType
* @ingroup d Debugging Functions
* @par Prototype
* @code
* UINT32 ACLCOMMON_GetLogType(UINT32* pu32WarningLogEnable, 
*             UINT32* pul32CfgLogEnable, 
*             UINT32* pu32RunLogEnable);
* @endcode 
* 
* @par Description
* This function gets the firewall warning, configuration and run type log level status.
* If control plane and data plane have different log type settings, 
* then output parameter contains log type settings of data plane.
* 
* 
* @param[in]   []
* @param[out] pu32WarningLogEnable Firewall Warning log type status 
*             [FWCOMMON_DEBUG_ENABLE-FWCOMMON_DEBUG_DISABLE/FWCOMMON_DEBUG_ENABLE]
* @param[out] pul32CfgLogEnable Firewall Configuration log type status 
*             [FWCOMMON_DEBUG_ENABLE-FWCOMMON_DEBUG_DISABLE/FWCOMMON_DEBUG_ENABLE]
* @param[out] pu32RunLogEnable Firewall Runtime log type status 
*             [FWCOMMON_DEBUG_ENABLE-FWCOMMON_DEBUG_DISABLE/FWCOMMON_DEBUG_ENABLE]
* 
* @retval UINT32 On Success [FW_OK|]
* @retval UINT32 Input pointer is NULL. [FWCOMMON_DEBUG_GETLOGTYPE_NULLPTR|]
* @retval UINT32 Please refer the return value of TCPIP_GetLogType of VISP control plane [|]
* @retval UINT32 Please refer the return value of SFE_GetLogType of VISP data plane [|]
* 
* @par Dependency
* tcpip/public/tcpip_debug.h
* ipsfe/public/debug/include/sfe_log.h
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
UINT32 ACLCOMMON_GetLogType(UINT32* pu32WarningLogEnable, 
            UINT32* pul32CfgLogEnable, 
            UINT32* pu32RunLogEnable);

/**
* @defgroup ACLCOMMON_ShowLogSwitch ACLCOMMON_ShowLogSwitch
* @ingroup d Debugging Functions
* @par Prototype
* @code
* VOID ACLCOMMON_ShowLogSwitch(VOID);
* @endcode 
* 
* @par Description
* This function displays the data plane log level and log type status on the console.
*
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value [|]
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
* None
*/ 
VOID ACLCOMMON_ShowLogSwitch(VOID);

/**
* @defgroup ACLCOMMON_RegDebugOutputHookFunc ACLCOMMON_RegDebugOutputHookFunc
* @ingroup d Debugging Functions
* @par Prototype
* @code
* UINT32 ACLCOMMON_RegDebugOutputHookFunc(FWIPSAFE_DEBUG_OUTPUT_CALLBACK_FUNC 
*                                      pfDebugOutput);
* @endcode 
* 
* @par Description
* This function is used to set the callback function for the firewall debug in control plane only. Firewall calls the
* registered function for any debug. This callback function is called based on firewall settings.
* 
* @param[in] pfDebugOutput Function pointer of type FWCOMMON_DEBUG_OUTPUT_CALLBACK_FUNC []
* @param[out]   []
* 
* @retval UINT32 On Success [FW_OK|]
* @retval UINT32 pfDebugOutput is NULL pointer [FWCOMMON_DEBUG_REGDEBUGHOOK_NULLPTR|]
* @retval UINT32 Please refer the return value of TCPIP_RegFuncDebugOutputHook of VISP control plane [|]
* 
* 
* @par Dependency
* tcpip/public/tcpip_pub_api.h
* 
* 
* @par Note
* \n
* Refer SFE_FWCOMMON_RegDebugOutputHookFunc to set the debug callback in data plane.
* Same can be set by TCPIP_RegFuncDebugOutputHook function also.
* 
* 
* @par Related Topics
* None
*/ 
UINT32 ACLCOMMON_RegDebugOutputHookFunc(FWIPSAFE_DEBUG_OUTPUT_CALLBACK_FUNC 
                                      pfDebugOutput);

/**
* @defgroup ACLCOMMON_SetDebugTypeSwitch ACLCOMMON_SetDebugTypeSwitch
* @ingroup d Debugging Functions
* @par Prototype
* @code
* UINT32 ACLCOMMON_SetDebugTypeSwitch (UINT32 u32DebugTypeSwitch);
* @endcode 
* 
* @par Description
* This function sets the firewall debug type switch. 
* 
* @param[in] u32DebugTypeSwitch Firewall debug type switch. TBD: Default value.
* [FWCOMMON_DEBUG_TYPE_ERROR-FWCOMMON_DEBUG_TYPE_VERBOSE]
* @param[out]   []
* 
* @retval UINT32 On Success [FW_OK|]
* @retval UINT32 Please refer the return value of SFE_SetDebugTypeSwitch of VISP data plane [|]
* 
* @par Dependency
* tcpip/public/tcpip_pub_api.h
* 
* 
* @par Note
* \n
* None
*  
* @par Example
* You can set more than one debug type using | operator.
* 
* @par Related Topics
* None
*/ 
UINT32 ACLCOMMON_SetDebugTypeSwitch (UINT32 u32DebugTypeSwitch);

/**
* @defgroup ACLCOMMON_SetDebugVcpuSwitch ACLCOMMON_SetDebugVcpuSwitch
* @ingroup d Debugging Functions
* @par Prototype
* @code
* UINT32 ACLCOMMON_SetDebugVcpuSwitch (UINT32 u32DebugVcpuSwitch);
* @endcode 
* 
* @par Description
* This function sets the VCPU switch number in the data plane. A maximum of 32 VCPU switches
* are supported. Each bit of the UINT32 input argument represents one VCPU switch number.
* Bit number of the UINT32 represents the VCPU switch number. 
*  
* @param[in] u32DebugVcpuSwitch VCPU switch number []
* @param[out]   []
* 
* @retval UINT32 On Success [FW_OK|]
* @retval UINT32 Please refer the return value of SFE_SetDebugVcpuSwitch of VISP data plane [|]
* 
* 
* @par Dependency
* ipsfe/public/debug/include/sfe_debug.h
* 
* 
* @par Note
* \n
* Data plane VCPU switch can be set by SFE_SetDebugVcpuSwitch.
*
* 
* @par Example
* If u32DebugVcpuSwitch = 5, the corresponding binary representation is 101.
* This means first and third VCPU switch debug info is set.
* 
* @par Related Topics
* None
*/ 
UINT32 ACLCOMMON_SetDebugVcpuSwitch (UINT32 u32DebugVcpuSwitch);

/**
* @defgroup ACLCOMMON_SetDebugModuleSwitch ACLCOMMON_SetDebugModuleSwitch
* @ingroup d Debugging Functions
* @par Prototype
* @code
* UINT32 ACLCOMMON_SetDebugModuleSwitch (UINT32 u32DebugModuleSwitch);
* @endcode 
* 
* @par Description
* This function sets the module type for the debug information. 
* Set the debug module switch using left switch. 0x01 << <ModuleType>
* 
* @param[in] u32DebugModuleSwitch Module information 
* [FWCOMMON_DEBUG_MOD_WLS-FWCOMMON_DEBUG_MOD_STAT]
* @param[out]   []
* 
* @retval UINT32 On Success [FW_OK|]	SFE_GetLogLevel
* @retval UINT32 Please refer the return value of SFE_SetDebugModuleSwitch of VISP data plane [|]
* 
* @par Dependency
* None
* 
* 
* @par Note
* \n
* Data plane module type can be set using SFE_SetDebugModuleSwitch
* 
* @par Example
* You can set more than one module type using '|' operator.
*  
* @par Related Topics
* None
*/ 
UINT32 ACLCOMMON_SetDebugModuleSwitch (UINT32 u32DebugModuleSwitch);

/**
* @defgroup ACLCOMMON_GetDebugSwitch ACLCOMMON_GetDebugSwitch
* @ingroup d Debugging Functions
* @par Prototype
* @code
* UINT32 ACLCOMMON_GetDebugSwitch(UINT32* pu32DebugTypeSwitch, 
*            UINT32* pu32DebugVcpuSwitch,
*            UINT32* pu32DebugModuleSwitch);
* @endcode 
* 
* @par Description
* This function gets the firewall debug information from data plane. It gets the debug type, 
* VCPU switch number, and module information.
* 
* @param[in]   []
* @param[out] pu32DebugTypeSwitch Debug type information []
* @param[out] pu32DebugVcpuSwitch Debug VCPU switch number []
* @param[out] pu32DebugModuleSwitch Debug module information []
* 
* @retval UINT32 On Success [FW_OK|]
* @retval UINT32 Input pointer is NULL [FWCOMMON_DEBUG_GETDEBUGSWITCH_NULLPTR|]
* @retval UINT32 Please refer the return value of SFE_SetDebugModuleSwitch of VISP data plane [|]
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
* None
*/ 
UINT32 ACLCOMMON_GetDebugSwitch(UINT32* pu32DebugTypeSwitch, 
            UINT32* pu32DebugVcpuSwitch,
            UINT32* pu32DebugModuleSwitch);

/**
* @defgroup ACLCOMMON_ShowDebugSwitch ACLCOMMON_ShowDebugSwitch
* @ingroup d Debugging Functions
* @par Prototype
* @code
* VOID ACLCOMMON_ShowDebugSwitch(VOID);
* 
* @endcode 
* 
* @par Description
* This function displays the data plane debug information on the console.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
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
* None
*/ 
VOID ACLCOMMON_ShowDebugSwitch(VOID);


/**
* @defgroup ACLCOMMON_RegInfoOutputHookFunc ACLCOMMON_RegInfoOutputHookFunc
* @ingroup d Debugging Functions
* @par Prototype
* @code
* UINT32 ACLCOMMON_RegInfoOutputHookFunc(FWIPSAFE_INFO_OUTPUT_CALLBACK_FUNC 
*                                         pfInfoOutput);
* @endcode 
* 
* @par Description
* This function is used to set the callback function for the firewall information in control plane only. 
* Firewall calls the registered function for any information output.
* 
* @param[in] pfInfoOutput Function pointer of type FWCOMMON_INFO_OUTPUT_CALLBACK_FUNC []
* @param[out]   []
* 
* @retval UINT32 On Success [FW_OK|]
* @retval UINT32 pfInfoOutput is NULL Pointer [FWCOMMON_DEBUG_REGINFOHOOK_NULLPTR|]
* @retval UINT32 Please refer the return value of TCPIP_RegFuncInfoOutputHook of VISP control plane [|]
* 
* @par Dependency
* tcpip/public/tcpip_pub_api.h
* 
* 
* @par Note
* \n
* Refer SFE_FWCOMMON_RegInfoOutputHookFunc to set the log callback in data plane.
*  
* @par Related Topics
* None
*/ 
UINT32 ACLCOMMON_RegInfoOutputHookFunc(FWIPSAFE_INFO_OUTPUT_CALLBACK_FUNC 
                                         pfInfoOutput);

/**
* @defgroup ACLCOMMON_SetOutputToCOMSwitch ACLCOMMON_SetOutputToCOMSwitch
* @ingroup d Debugging Functions
* @par Prototype
* @code
* VOID ACLCOMMON_SetOutputToCOMSwitch(UINT32 u32Switch);
* @endcode 
* 
* @par Description
* This function sets the COM switch to the firewall. Based on this switch, firewall displays the 
* log or debug or information on the console. You can provide more than one switch using | operator.
* 
* @param[in] u32Switch COM switch 
* [FWCOMMON_OUTPUT_FIX_LOG-FWCOMMON_OUTPUT_INFO]
* @param[out]   []
* 
* @retval VOID This function does not return any value [|]
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
* None
*/ 
VOID ACLCOMMON_SetOutputToCOMSwitch(UINT32 u32Switch);



#ifdef __cplusplus 
}
#endif /* __cplusplus */

#endif /* __FWCOMMON_DEBUG_H__ */
