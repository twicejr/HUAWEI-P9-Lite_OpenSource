

#ifndef __IPSAFE_DEBUG_API_H__
#define __IPSAFE_DEBUG_API_H__

#ifdef __cplusplus
    extern "C"{
#endif /* __cplusplus */

#include "security/apiinclude/ipsafe_basetype.h"

#define IPSAFE_DEBUG_ENABLE 1       /*This constant indicates 
                                    warning log type, configuration log type and run time log type is enabled. */
#define IPSAFE_DEBUG_DISABLE 0      /*This constant indicates 
                                    warning log type, configuration log type and run time log type is disabled. */

#define IPSAFE_DEBUG_TYPE_ERROR        0x0001    /* This constant is used to set the debug type as error. 
                                                   Debug callback function will be called when any 
                                                                                        debug information with this type is there.TBD:*/
#define IPSAFE_DEBUG_TYPE_INOUT        0x0002    /* This constant is used to set the debug type as input/output. 
                                                                                         Debug callback function will be called when any debug information 
                                                                                         for inbound/outbound module is there.TBD:*/
#define IPSAFE_DEBUG_TYPE_PROC         0x0004        /* This constant is used to set the debug type as process. 
                                                                                        Debug callback function will be called when any
                                                                                        debug information for runtime is there.TBD:*/
#define IPSAFE_DEBUG_TYPE_VERBOSE     0x0008      /*This constant is used for providing extra log information like packet configuration details.*/

/*Use this macro to enable all the types of debugs*/
#define IPSAFE_DEBUG_TYPE_ALL \
    (IPSAFE_DEBUG_TYPE_ERROR | IPSAFE_DEBUG_TYPE_INOUT | IPSAFE_DEBUG_TYPE_PROC | IPSAFE_DEBUG_TYPE_VERBOSE)


/* These macros are used to enable debug type switch for particular modules */
/* To enable debugs for more than one module, use the OR operator between the macros for the modules to be enabled 
   and pass that to the API*/
#define IPSAFE_DEBUG_MODULE_NAT        0x00000001    /*Enables debug type switch for NAT*/
#define IPSAFE_DEBUG_MODULE_ALG        0x00000002    /*Enables debug type switch for ALG*/
#define IPSAFE_DEBUG_MODULE_FC         0x00000004    /*Enables debug type switch for FC*/
#define IPSAFE_DEBUG_MODULE_BLK        0x00000008    /*Enables debug type switch for BLK*/
#define IPSAFE_DEBUG_MODULE_ALGFTP     0x00000010    /*Enables debug type switch for ALG F*P*/
#define IPSAFE_DEBUG_MODULE_ALGICMP    0x00000020    /*Enables debug type switch for ALG ICMP*/
#define IPSAFE_DEBUG_MODULE_ALGVRF     0x00000040    /*Enables debug type switch for ALG VRF*/
#define IPSAFE_DEBUG_MODULE_ALGSMTP    0x00000080    /*Enables debug type switch for ALG SMTP*/
#define IPSAFE_DEBUG_MODULE_ALGRTSP    0x00000100    /*Enables debug type switch for ALG RTSP*/
#define IPSAFE_DEBUG_MODULE_STAT       0x00000200    /*Enables debug type switch for statistics to 
                                                     display packet content when auto statistics drop a packet*/
#define IPSAFE_DEBUG_MODULE_ALGNBT     0x00000400    /*Enables debug type switch for ALG NBT*/
#define IPSAFE_DEBUG_MODULE_ALGMMS     0x00000800    /*Enables debug type switch for ALG MMS*/
#define IPSAFE_DEBUG_MODULE_ALGSIP     0x00001000    /*Enables debug type switch for ALG SIP*/
#define IPSAFE_DEBUG_MODULE_ALGMSN     0x00002000    /*Enables debug type switch for ALG MMS*/
#define IPSAFE_DEBUG_MODULE_H323       0x00004000   /*Enables debug type switch for ALG H323*/
#define IPSAFE_DEBUG_MODULE_ALGILS     0x00008000    /*Enables debug type switch for ALG ILS*/
#define IPSAFE_DEBUG_MODULE_SDP        0x00010000    /*Enables debug type switch for ALG SDP*/
#define IPSAFE_DEBUG_MODULE_MGCP       0x00020000   /*Enables debug type switch for ALG MGCP*/


/*To enable debugs for all modules use this macro*/
#define IPSAFE_DEBUG_MODULE_ALL \
    (IPSAFE_DEBUG_MODULE_NAT | IPSAFE_DEBUG_MODULE_ALG | IPSAFE_DEBUG_MODULE_FC \
    | IPSAFE_DEBUG_MODULE_BLK | IPSAFE_DEBUG_MODULE_ALGFTP | IPSAFE_DEBUG_MODULE_ALGICMP \
    | IPSAFE_DEBUG_MODULE_ALGVRF | IPSAFE_DEBUG_MODULE_ALGSMTP | IPSAFE_DEBUG_MODULE_ALGRTSP \
    | IPSAFE_DEBUG_MODULE_STAT | IPSAFE_DEBUG_MODULE_ALGMMS | IPSAFE_DEBUG_MODULE_ALGNBT | IPSAFE_DEBUG_MODULE_H323\
    | IPSAFE_DEBUG_MODULE_ALGSIP|IPSAFE_DEBUG_MODULE_ALGILS | IPSAFE_DEBUG_MODULE_SDP | IPSAFE_DEBUG_MODULE_MGCP)
    

/*ERRORCODE< Error Codes of all Debug API's >*/
typedef enum enumIpsafeDebugErrCode
{
    IPSAFE_DEBUG_SUCCESS,
    IPSAFE_DEBUG_ERR_RET_CODE_BEGIN = IPSAFE_DEBUG_BEGIN_RET_CODE,    /*<3000> Beginning of debug module error and 
                                                                        return code.*/
    IPSAFE_DEBUG_INIT_ERR_ALLOC_DEBUG_TYPE_SWITCH,                    /*<3001> Failed to allocate memory for debug type 
                                                                        switch in Debug Initialization */
    IPSAFE_DEBUG_INIT_ERR_ALLOC_DEBUG_VCPU_SWITCH,                    /*<3002> Failed to allocate memory for debug VCPU 
                                                                        switch in Debug Initialization */
    IPSAFE_DEBUG_INIT_ERR_ALLOC_DEBUG_MODULE_SWITCH,                  /*<3003> Failed to allocate memory for debug module 
                                                                        switch in Debug Initialization */
    IPSAFE_DEBUG_INIT_ERR_ALLOC_OUTPUT_TO_COM,                        /*<3004> Failed to allocate memory for Out to Com 
                                                                        variable in Debug Initialization */
    IPSAFE_DEBUG_REGDBG_OUTPUT_HOOK_FUN_ERR_VCPU_ALREADY_INIT,        /*<3005> Failed to register debug output hook 
                                                                        function as VCPU is already initialized */
    IPSAFE_DEBUG_REGDBG_OUTPUT_HOOK_FUN_ERR_NULL_PTR,                 /*<3006> Failed to register output hook function due 
                                                                        to Null pointer */
    IPSAFE_DEBUG_REGINFOHOOK_ERR_NULLPTR,                             /*<3007> Failed to register Info hook function due to 
                                                                        Null pointer */
    IPSAFE_DEBUG_REGINFOHOOK_ERR_VCPU_ALREADY_INIT,                   /*<3008> Failed to register Info hook function as 
                                                                        VCPU is already initialized */
    IPSAFE_DEBUG_SETDEBUGTYPE_ERR_DEBUG_TYPE_SWITCH_NULL_PTR,         /*<3009> Failed to set debug type switch due to null 
                                                                        pointer */
    IPSAFE_DEBUG_SETDEBUGTYPE_ERR_INVALID_TYPE,                       /*<3010> Failed to set debug type due to invalid 
                                                                        input type */
    IPSAFE_DEBUG_SETDEBUGVCPU_ERR_DBG_VCPUSWITCH_NULL_POINTER,        /*<3011> Failed to set debug VCPU switch due to 
                                                                        Null Pointer*/
    IPSAFE_DEBUG_SETDBGMODULE_ERR_DBG_MOD_NULL_PTR,                   /*<3012> Failed to set debug module due to null 
                                                                        pointer */
    IPSAFE_DEBUG_GETDEBUG_ERR_DBG_TYPE_NULL_POINTER,                  /*<3013> Failed to get debug type due to debug type 
                                                                        Null Pointer */
    IPSAFE_DEBUG_GETDEBUG_ERR_DBG_VCPU_NULL_POINTER,                  /*<3014> Failed to get debug switch due to vcpu type 
                                                                        null pointer */
    IPSAFE_DEBUG_GETDEBUG_ERR_DBG_MOD_NULL_POINTER,                   /*<3015> Failed to get debug switch due to module 
                                                                        null pointer */
    IPSAFE_DEBUG_GETDEBUGSWITCH_ERR_INPUT_NULL_POINTER                /*<3016> Failed to get debug switch due to input null 
                                                                        pointer */

}IPSAFE_DEBUG_ERR_CODE_E;

/*ERRORCODE< Error Codes of all Log API's >*/
typedef enum enumIpsafeLogErrCode
{ 
    IPSAFE_LOG_SUCCESS,
    IPSAFE_LOG_ERR_RET_CODE_BEGIN = IPSAFE_LOG_BEGIN_RET_CODE,        /*<4000> Beginning of log module error and 
                                                                        return code.*/
    IPSAFE_LOG_INIT_ERR_ALLOC_LOG_LEVEL,                              /*<4001> Failed to allocate memory for log level in 
                                                                        log initialization */
    IPSAFE_LOG_INIT_ERR_ALLOC_LOG_TYPE,                               /*<4002> Failed to allocate memory for log type in 
                                                                        log initialization */
    IPSAFE_LOG_REGLOG_ERR_VCPU_ALREADY_INIT,                          /*<4003> Failed to register log because VCPU is 
                                                                        already initialized */
    IPSAFE_LOG_REGLOG_ERR_NULL_FUNC_POINTER,                          /*<4004> Failed to register log due to NULL 
                                                                        function pointer*/
    IPSAFE_LOG_REGLOG_ERR_INPUT_NULL_POINTER,                         /*<4005> Failed to register log due to NULL input */
    IPSAFE_LOG_SETLOGLEVEL_ERR_LOG_LEVEL_NULL_POINTER,                /*<4006> Failed to set log level due to NULL 
                                                                        Pointer */
    IPSAFE_LOG_SETLOGLEVEL_ERR_INPUT_LEVEL_INVALID,                   /*<4007> Failed to set log level due to invalid 
                                                                        inputs */
    IPSAFE_LOG_GETLOGLEVEL_ERR_LOG_LEVEL_NULL_POINTER,                /*<4008> Failed to get log level due to NULL 
                                                                        pointer */
    IPSAFE_LOG_GETLOGLEVEL_ERR_INPUT_NULL_POINTER,                    /*<4009> Failed to get log level due to input null 
                                                                        pointer */
    IPSAFE_LOG_SETLOGTYPE_ERR_LOGTYPE_NULL_POINTER,                   /*<4010> Failed to set log type due to NULL log 
                                                                        type */
    IPSAFE_LOG_SETLOGTYPE_ERR_INPUT_INVALID,                          /*<4011> Failed to set log type due to invalid 
                                                                        input */
    IPSAFE_LOG_GETLOGTYPE_ERR_LOGTYPE_NULL_POINTER,                   /*<4012> Failed to get Log type due to NULL Log type*/
    IPSAFE_LOG_GETLOGTYPE_ERR_INPUT_NULL_POINTER,                      /*<4013> Failed to get Log type due to NULL inputs */

    IPSAFE_LOG_INIT_ERR_NAMEDBADD_LOG_TYPE,                           /*<4014> failed to add name db for log type */
    IPSAFE_LOG_INIT_ERR_NAMEDBADD_LOG_LEVEL                           /*<4015> Failed to add name db for log level */

}IPSAFE_LOG_ERR_CODE_E;

/*STRUCT< This enum is for NAT log level. You can set any one of the log level in the NAT debug module. 
          Based on the log level set by you, log callback functions are called. Highest priority log level will 
          automatically be enabled.>*/
typedef enum IPSAFE_LOG_LEVEL_Etag
{
    IPSAFE_LOG_LEVEL_CRITICAL = 0, /*Critical log level*/
    IPSAFE_LOG_LEVEL_ERROR,        /*Error log level*/
    IPSAFE_LOG_LEVEL_WARNING,      /*Warning log level*/
    IPSAFE_LOG_LEVEL_INFO,         /*Information log level*/
    IPSAFE_LOG_LEVEL_DEBUG,        /*Debug log level*/
    IPSAFE_LOG_LEVEL_END
}IPSAFE_LOG_LEVEL_E;



#define IPSAFE_LOG_TYPE_WARNING    0x0001      /*This constant indicates that log callback function is called 
                                                for the warning log type.*/
#define IPSAFE_LOG_TYPE_CFG        0x0010      /*This constant indicates that log callback function is called 
                                                for the configuration log type.*/
#define IPSAFE_LOG_TYPE_RUN        0x0100      /*This constant indicates that log callback function is called 
                                                 for the run time log.*/



typedef VOID (*IPSAFE_LOG_FIXLEN_CALLBACK_FUNC)(UINT32 u32LogCode, UINT32 u32LogLevel,
                                                 UINT32 u32LogType, VOID* pFormat,
                                                 UINT32 u32Para1, UINT32 u32Para2,
                                                 UINT32 u32Para3, UINT32 u32Para4);



typedef VOID (*IPSAFE_LOG_VARLEN_CALLBACK_FUNC)(UINT32 u32LogCode, 
                                                 UINT32 u32LogLevel,
                                                 UINT32 u32LogType, 
                                                 VOID* pFormat, 
                                                 VOID* pData);


typedef VOID (*IPSAFE_DEBUG_OUTPUT_CALLBACK_FUNC)(CHAR *pcDebugOutput);



typedef VOID (*IPSAFE_INFO_OUTPUT_CALLBACK_FUNC)(CHAR *pcInfoOutput);


/*STRUCT< This structure hooks the callback for the log function. 
                    This structure is used to set the log callback function in the 
                    debug module of Security Sub system.>*/
typedef struct tagIPSAFE_LOG_HOOK_FUNC
{
    IPSAFE_LOG_FIXLEN_CALLBACK_FUNC pfLogFixLenFuncPtr;   /*Fixed length log function pointer*/
    IPSAFE_LOG_VARLEN_CALLBACK_FUNC pfLogVarLenFuncPtr;   /*Variable length log function pointer*/
}IPSAFE_LOG_HOOK_FUNC_S;




extern UINT32 IPSAFE_RegLogHookFunc(IPSAFE_LOG_HOOK_FUNC_S* pstHookFunc);




extern UINT32 IPSAFE_SetLogLevel(UINT32 u32LogLevel);



extern UINT32 IPSAFE_GetLogLevel(UINT32* pu32LogLevel);




extern UINT32 IPSAFE_SetLogType(UINT32 u32WarningLogEnable, 
            UINT32 u32CfgLogEnable, 
            UINT32 u32RunLogEnable);



extern UINT32 IPSAFE_GetLogType(UINT32* pu32WarningLogEnable, 
            UINT32* pu32CfgLogEnable, 
            UINT32* pu32RunLogEnable);





extern VOID IPSAFE_ShowLogSwitch(VOID);





extern UINT32 IPSAFE_RegDebugOutputHookFunc(IPSAFE_DEBUG_OUTPUT_CALLBACK_FUNC 
                                      pfDebugOutput);





extern UINT32 IPSAFE_SetDebugTypeSwitch (UINT32 u32DebugTypeSwitch);




extern UINT32 IPSAFE_SetDebugVcpuSwitch (UINT32 u32DebugVcpuSwitch);




extern UINT32 IPSAFE_SetDebugModuleSwitch (UINT32 u32DebugModuleSwitch);




extern UINT32 IPSAFE_GetDebugSwitch(UINT32* pu32DebugTypeSwitch, 
            UINT32* pu32DebugVcpuSwitch,
            UINT32* pu32DebugModuleSwitch);




extern VOID IPSAFE_ShowDebugSwitch(VOID);



extern UINT32 IPSAFE_RegInfoOutputHookFunc(IPSAFE_INFO_OUTPUT_CALLBACK_FUNC 
                                         pfInfoOutput);



extern VOID IPSAFE_SetOutputToCOMSwitch(UINT32 u32Switch);



#ifdef __cplusplus 
}
#endif /* __cplusplus */

#endif /* __IPSAFE_DEBUG_H__ */

