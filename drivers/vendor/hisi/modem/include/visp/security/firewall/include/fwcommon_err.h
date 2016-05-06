/*************************************************************************
 *
 *              Copyright 2009, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 *
 *-----------------------------------------------------------------------*
 *
 *                              fwcommon_err.h
 *
 *       Version: DOPRA VISP V1R8C02 Firewall
 *   Module Name: fwcommon
 *  Date Created: 2009-08-10
 *        Author: kurt 57669
 *   Description: the main header file for firewall to include other header
 *                 file
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2006-12-01      kurt 57669    Create

 ************************************************************************/
#ifndef _FWCOMMON_ERR_H_
#define _FWCOMMON_ERR_H_

#ifdef  __cplusplus
extern "C" {
#endif

/*define the firewall init module error code*/
/*enumeration for firewall initialization errors */
/**
* @defgroup enumFWInitErrCode
* @ingroup 
* @par Prototype
* @code
* typedef enum enumFWCommonInitErrCode
* {
*     FW_INIT_OK = 0,
*     FW_INIT_ERROR = FWIPSAFE_FW_BEGIN_RET_CODE + 100 + 1 ,
*     FW_INIT_ERR_MALLOC_FW_MODULE_ENABLE_S,
*     FW_INIT_ERR_ADD_NAME_DB_FW_MODULE_ENABLE_S,
*     FW_CFG_NULL_SFE_ENABLE_FW_MODULE_BY_TYPE,
*     FW_INVALID_INPUT_SFE_ENABLE_FW_MODULE_BY_TYPE,
*     FW_INIT_ERR_CREATE_SYS_SPIN_LOCK,
*     FW_NULL_INPUT_PASSED_GET_VERSION
* }FW_INIT_ERR_CODE_E;
* @endcode 
* 
* @datastruct FW_INIT_OK = 0 Indicates firewall initialization success.
* @datastruct FW_INIT_ERROR Indicates firewall initialization fails.
* @datastruct FW_INIT_ERR_MALLOC_FW_MODULE_ENABLE_S Indicates malloc fails for variable which 
* stores status of all firewall modules.
* @datastruct FW_INIT_ERR_ADD_NAME_DB_FW_MODULE_ENABLE_S Indicates registering name in DB for 
* variable which stores status of all firewall modules.
* @datastruct FW_CFG_NULL_SFE_ENABLE_FW_MODULE_BY_TYPE Indicates firewall is not initialized.
* @datastruct FW_INVALID_INPUT_SFE_ENABLE_FW_MODULE_BY_TYPE Indicates invalid value to enable/disable
* firewall module.
* @datastruct FW_INIT_ERR_CREATE_SYS_SPIN_LOCK Indicates spin lock creation fails.
* @datastruct FW_NULL_INPUT_PASSED_GET_VERSION Indicated NULL pointer passed for getting the version

*/
typedef enum enumFWCommonInitErrCode
{
    FW_INIT_OK = 0,
    FW_INIT_ERROR = FWIPSAFE_FW_BEGIN_RET_CODE + 100 + 1 ,
    FW_INIT_ERR_MALLOC_FW_MODULE_ENABLE_S,
    FW_INIT_ERR_ADD_NAME_DB_FW_MODULE_ENABLE_S,
    FW_CFG_NULL_SFE_ENABLE_FW_MODULE_BY_TYPE,
    FW_INVALID_INPUT_SFE_ENABLE_FW_MODULE_BY_TYPE,
    FW_INIT_ERR_CREATE_SYS_SPIN_LOCK,
    FW_NULL_INPUT_PASSED_GET_VERSION
}FW_INIT_ERR_CODE_E;

/**
* @defgroup enumFWCommonDebugErrCode
* @ingroup 
* @par Prototype
* @code
* typedef enum enumFWCommonDebugErrCode
* {
*     FWCOMMON_DEBUG_OK = 0,
*     FWCOMMON_STAT_ERR_WLS_INIT_SWITCH_MALLOC = FWIPSAFE_FW_BEGIN_RET_CODE + 200 + 1 ,
*     FWCOMMON_STAT_ERR_WLS_INIT_SWITCH_ADDNAMEDB,
*     FWCOMMON_STAT_ERR_BLS_INIT_SWITCH_MALLOC,
*     FWCOMMON_STAT_ERR_BLS_INIT_SWITCH_ADDNAMEDB,
*     FWCOMMON_STAT_ERR_AD_INIT_SWITCH_MALLOC,
*     FWCOMMON_STAT_ERR_AD_INIT_SWITCH_ADDNAMEDB,
*     FWCOMMON_DEBUG_SFE_GETFLOWSTATISTICSWITCH_NULLPTR,
*     FWCOMMON_DEBUG_SFE_SETFLOWSTATISTICSWITCH_INVALID_SWITCH,
*     FWCOMMON_STAT_ERR_FWFLOWSTATINIT_SWITCH_MALLOC,
*     FWCOMMON_STAT_ERR_FWFLOWSTATINIT_SWITCH_ADDNAMEDB,
*     FWCOMMON_STAT_ERR_FWFLOWSTATINIT_MALLOC,
*     FWCOMMON_STAT_ERR_FWFLOWSTATINIT_ADDNAMEDB,
*     FWCOMMON_DEBUG_SFE_SETFLOWSTATISTICSWITCH_NULL_SWITCH,
*     FWCOMMON_DEBUG_SFE_GETFLOWSTATISTICSWITCH_NULL_SWITCH,
*     FWCOMMON_DEBUG_SFE_CLEARALLFLOWSTATISTIC_NULL_SHARE,
*
*     FWCOMMON_STAT_ERR_FWSTATINIT_SWITCH_MALLOC,    
*     FWCOMMON_STAT_ERR_FWSTATINIT_SWITCH_ADDNAMEDB,
*     FWCOMMON_DEBUG_SFE_SETFWSTATISTICSWITCH_INVALID_SWITCH,
*     FWCOMMON_DEBUG_SFE_SETFWSTATISTICSWITCH_NULL_SWITCH,
*     FWCOMMON_DEBUG_SFE_GETFWSTATISTICSWITCH_NULLPTR,
*     FWCOMMON_DEBUG_SFE_GETFWSTATISTICSWITCH_NULL_SWITCH
* }FWCOMMON_DEBUG_ERR_CODE_E;
* @endcode 
*
* @datastruct FW_INIT_OK = 0 Indicates firewall initialization success.
* @datastruct FWCOMMON_STAT_ERR_WLS_INIT_SWITCH_MALLOC Indicates malloc fail for whitelist statistics variable.
* @datastruct FWCOMMON_STAT_ERR_WLS_INIT_SWITCH_ADDNAMEDB Indicates registering name fails for whitelist statistics variable.
* @datastruct FWCOMMON_STAT_ERR_BLS_INIT_SWITCH_MALLOC Indicates malloc fail for blacklist statistics variable.
* @datastruct FWCOMMON_STAT_ERR_BLS_INIT_SWITCH_ADDNAMEDB Indicates registering name fails for blacklist statistics variable.
* @datastruct FWCOMMON_STAT_ERR_AD_INIT_SWITCH_MALLOC Indicates registering name fails for attack statistics variable.
* @datastruct FWCOMMON_STAT_ERR_AD_INIT_SWITCH_ADDNAMEDB Indicates registering name fails for attack statistics variable.
* @datastruct FWCOMMON_DEBUG_SFE_GETFLOWSTATISTICSWITCH_NULLPTR Indicates received null pointer to get flow statistics switch.
* @datastruct FWCOMMON_DEBUG_SFE_SETFLOWSTATISTICSWITCH_INVALID_SWITCH Indicates received invalid value to set flow statistic switch.
* @datastruct FWCOMMON_STAT_ERR_FWFLOWSTATINIT_SWITCH_MALLOC Indicates malloc fail for flow statistics switch variable. 
* @datastruct FWCOMMON_STAT_ERR_FWFLOWSTATINIT_SWITCH_ADDNAMEDB Indicates registering name fail for flow statistics switch variable. 
* @datastruct FWCOMMON_STAT_ERR_FWFLOWSTATINIT_MALLOC Indicates malloc fail for flow statistics. 
* @datastruct FWCOMMON_STAT_ERR_FWFLOWSTATINIT_ADDNAMEDB Indicates registering name fail for flow statistics.
* @datastruct FWCOMMON_DEBUG_SFE_SETFLOWSTATISTICSWITCH_NULL_SWITCH Indicates flow statistics switch variable is not initialized.
* @datastruct FWCOMMON_DEBUG_SFE_GETFLOWSTATISTICSWITCH_NULL_SWITCH Indicates flow statistics switch variable is not initialized.
* @datastruct FWCOMMON_DEBUG_SFE_CLEARALLFLOWSTATISTIC_NULL_SHARE Indicates flow statistics switch variable is not initialized.
* @datastruct FWCOMMON_STAT_ERR_FWSTATINIT_SWITCH_MALLOC Indicates malloc fail for VCPU statistics switch variable. 
* @datastruct FWCOMMON_STAT_ERR_FWSTATINIT_SWITCH_ADDNAMEDB Indicates registering name fail for VCPU statistics switch variable. 
* @datastruct FWCOMMON_DEBUG_SFE_SETFWSTATISTICSWITCH_INVALID_SWITCH Indicates received invalid value to set VCPU statistic switch.
* @datastruct FWCOMMON_DEBUG_SFE_SETFWSTATISTICSWITCH_NULL_SWITCH Indicates VCPU statistics switch variable is not initialized.
* @datastruct FWCOMMON_DEBUG_SFE_GETFWSTATISTICSWITCH_NULLPTR Indicates VCPU statistics switch variable is not initialized.
* @datastruct FWCOMMON_DEBUG_SFE_GETFWSTATISTICSWITCH_NULL_SWITCH Indicates VCPU statistics switch variable is not initialized.
*/
typedef enum enumFWCommonDebugErrCode
{
    FWCOMMON_DEBUG_OK = 0,
    FWCOMMON_STAT_ERR_WLS_INIT_SWITCH_MALLOC = FWIPSAFE_FW_BEGIN_RET_CODE + 200 + 1 ,
    FWCOMMON_STAT_ERR_WLS_INIT_SWITCH_ADDNAMEDB,
    FWCOMMON_STAT_ERR_BLS_INIT_SWITCH_MALLOC,
    FWCOMMON_STAT_ERR_BLS_INIT_SWITCH_ADDNAMEDB,
    FWCOMMON_STAT_ERR_AD_INIT_SWITCH_MALLOC,
    FWCOMMON_STAT_ERR_AD_INIT_SWITCH_ADDNAMEDB,
    FWCOMMON_DEBUG_SFE_GETFLOWSTATISTICSWITCH_NULLPTR,
    FWCOMMON_DEBUG_SFE_SETFLOWSTATISTICSWITCH_INVALID_SWITCH,
    FWCOMMON_STAT_ERR_FWFLOWSTATINIT_SWITCH_MALLOC,
    FWCOMMON_STAT_ERR_FWFLOWSTATINIT_SWITCH_ADDNAMEDB,
    FWCOMMON_STAT_ERR_FWFLOWSTATINIT_MALLOC,
    FWCOMMON_STAT_ERR_FWFLOWSTATINIT_ADDNAMEDB,
    FWCOMMON_DEBUG_SFE_SETFLOWSTATISTICSWITCH_NULL_SWITCH,
    FWCOMMON_DEBUG_SFE_GETFLOWSTATISTICSWITCH_NULL_SWITCH,
    FWCOMMON_DEBUG_SFE_CLEARALLFLOWSTATISTIC_NULL_SHARE,

    FWCOMMON_STAT_ERR_FWSTATINIT_SWITCH_MALLOC,    /* performance optimization */
    FWCOMMON_STAT_ERR_FWSTATINIT_SWITCH_ADDNAMEDB,
    FWCOMMON_DEBUG_SFE_SETFWSTATISTICSWITCH_INVALID_SWITCH,
    FWCOMMON_DEBUG_SFE_SETFWSTATISTICSWITCH_NULL_SWITCH,
    FWCOMMON_DEBUG_SFE_GETFWSTATISTICSWITCH_NULLPTR,
    FWCOMMON_DEBUG_SFE_GETFWSTATISTICSWITCH_NULL_SWITCH
}FWCOMMON_DEBUG_ERR_CODE_E;

/*define the hook function error codes*/
/**
* @defgroup enumFWCommonHookErrCode
* @ingroup 
* @par Prototype
* @code
* typedef enum enumFWCommonHookErrCode
* {
*     FWCOMMON_HOOK_OK = 0,
*     FW_ERR_MAC_INBOUND_REGISTER_FAILED = FWIPSAFE_FW_BEGIN_RET_CODE + 500 + 1 ,
*     FW_ERR_MAC_OUTBOUND_REGISTER_FAILED,
*     FW_ERR_IP_INBOUND_ALREADY_REGISTERED,
*     FW_ERR_IP_INBOUND_REGISTER_FAILED,
*     FW_ERR_IP_OUTBOUND_ALREADY_REGISTERED,
*     FW_ERR_IP_OUTBOUND_REGISTER_FAILED
* }FWCOMMON_HOOK_ERR_CODE_E;
* @endcode 
* 
* @datastruct FW_INIT_OK = 0 Indicates firewall initialization success.
* @datastruct FW_ERR_MAC_INBOUND_REGISTER_FAILED Indicates inboundFilter register failed for MAC layer.
* @datastruct FW_ERR_MAC_OUTBOUND_REGISTER_FAILED Indicates outboundFilter register failed for MAC layer.
* @datastruct FW_ERR_IP_INBOUND_ALREADY_REGISTERED Indicates inboundFilter already registered in IP layer.
* @datastruct FW_ERR_IP_INBOUND_REGISTER_FAILED Indicates inboundFilter register failed for IP layer.
* @datastruct FW_ERR_IP_OUTBOUND_ALREADY_REGISTERED Indicates outboundFilter already registered in IP layer.
* @datastruct FW_ERR_IP_OUTBOUND_REGISTER_FAILED Indicates outboundFilter register failed for IP layer.
*/
typedef enum enumFWCommonHookErrCode
{
    FWCOMMON_HOOK_OK = 0,
    FW_ERR_MAC_INBOUND_REGISTER_FAILED = FWIPSAFE_FW_BEGIN_RET_CODE + 500 + 1, /*InboundFilter register failed for MAC layer*/
    FW_ERR_MAC_OUTBOUND_REGISTER_FAILED,                             /*OutboundFilter register failed for MAC layer*/
    FW_ERR_IP_INBOUND_ALREADY_REGISTERED,                            /*InboundFilter already registered in IP layer*/
    FW_ERR_IP_INBOUND_REGISTER_FAILED,                               /*InboundFilter register failed for IP layer*/
    FW_ERR_IP_OUTBOUND_ALREADY_REGISTERED,                           /*OutboundFilter already registered in IP layer*/
    FW_ERR_IP_OUTBOUND_REGISTER_FAILED,                             /*OutboundFilter register failed for IP layer*/
} FWCOMMON_HOOK_ERR_CODE_E;

#ifdef  __cplusplus
}
#endif

#endif

