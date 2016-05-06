/*************************************************************************
*    
*                  Copyright 2009, Huawei Technologies Co. Ltd.
*                              ALL RIGHTS RESERVED
*    
*    -----------------------------------------------------------------------*
*    
*                                 ipsi_bin_log.h
*    
*      Project Code: 
*      Module Name:Binary Log
*      Version    : 1
*      Date Created: 5.8.2011
*      Author:Pallavi Meher
*      Description: Header file contains the  function declaration for the
*                for the binary log module.
*    -----------------------------------------------------------------------*
*      Modification History
*      DATE                NAME                            DESCRIPTION
*                               
 *************************************************************************/
#ifndef __IPSI_BIN_LOG_H__
#define __IPSI_BIN_LOG_H__

#include "ipsi_crypto_buildconf.h"

#ifndef __IPSI_NO_BIN_LOG__



#include "ipsi_types.h"
#include "ipsi_string.h"
#include "sec_sys.h"

#ifdef	 __cplusplus
extern	"C"{
#endif

/*This constant indicates 
warning log type, configuration log type
and run time log type is enabled. */

/**
* @defgroup Binary_Log_Functions Binary Log Functions
* This section contains the binary log functionalities
*/

/**
* @defgroup Binary_Log_DataStructures Binary Log DataStructures
* @ingroup Binary_Log_Functions
* This section contains the binary log data structures.
*/

/**
* @defgroup Binary_Log_Enum Binary Log Enum
* @ingroup Binary_Log_Functions
* This section contains the binary log enumerations.
*/

/**
* @defgroup BinaryMacroDefinitions Binary Macro Definitions
* @ingroup Binary_Log_Functions
* @code
* // Indicates warning log type, configuration log type, and run time
* // log type is enabled
* #define IPSI_BIN_LOG_TYPE_ENABLE 1
*
* // Indicates warning log type, configuration log type and
* // run time log type is disabled.
* #define IPSI_BIN_LOG_TYPE_DISABLE 0
* 
* // Indicates that log callback function is called for the
* // warning log type.
* #define IPSI_BIN_LOG_TYPE_WARNING  0x0001
* 
* // This constant indicates that log callback function is called  
* // for the configuration log type
* #define IPSI_BIN_LOG_TYPE_CFG      0x0010 
* 
* // Indicates that log callback function is called for the
* // run time log.
* #define IPSI_BIN_LOG_TYPE_RUN      0x0100  
* 
* @endcode
*/


#define IPSI_BIN_LOG_TYPE_ENABLE 1  

/*This constant indicates 
 warning log type, configuration log type and
 run time log type is disabled. */

#define IPSI_BIN_LOG_TYPE_DISABLE 0      

/*This constant indicates that log  
callback function is called  for 
the warning log type.*/                   


#define IPSI_BIN_LOG_TYPE_WARNING  0x0001

/*This constant indicates that log
  callback function is called  for
 the configuration log type.*/

#define IPSI_BIN_LOG_TYPE_CFG      0x0010 

/*This constant indicates that log
 callback function is called 
  for the run time log.*/


#define IPSI_BIN_LOG_TYPE_RUN      0x0100  

/* You can set any one of the log level . 
    Based on the log level set by you, log callback functions are called.
    Highest priority log level will automatically be enabled.*/
  
/**
* @defgroup IPSI_BIN_LOG_LEVEL_E
* @ingroup Binary_Log_Enum
* @par Prototype
* @code
* typedef enum IPSI_BIN_LOG_LEVEL
* {
*    IPSI_BIN_LOG_LEVEL_CRITICAL = 0, 
*    IPSI_BIN_LOG_LEVEL_ERROR,        
*    IPSI_BIN_LOG_LEVEL_WARNING,      
*    IPSI_BIN_LOG_LEVEL_INFO,         
*    IPSI_BIN_LOG_LEVEL_DEBUG,    
*    IPSI_BIN_LOG_LEVEL_END
* } IPSI_BIN_LOG_LEVEL_E;
* @endcode
*
* @dataEnum IPSI_BIN_LOG_LEVEL_CRITICAL   Log Level is CRITICAL.
* @dataEnum IPSI_BIN_LOG_LEVEL_ERROR      Log Level is ERROR.
* @dataEnum IPSI_BIN_LOG_LEVEL_WARNING    Log Level is WARNING.
* @dataEnum IPSI_BIN_LOG_LEVEL_INFO       Log Level is INFO.
* @dataEnum IPSI_BIN_LOG_LEVEL_DEBUG      Log Level is DEBUG.
* @dataEnum IPSI_BIN_LOG_LEVEL_END        Log Level is END.
*/

typedef enum IPSI_BIN_LOG_LEVEL
{
    IPSI_BIN_LOG_LEVEL_CRITICAL = 0, /*CRITICAL LOG LEVEL*/
    IPSI_BIN_LOG_LEVEL_ERROR,        /*ERROR LOG LEVEL*/
    IPSI_BIN_LOG_LEVEL_WARNING,      /*WARNING LOG LEVEL */
    IPSI_BIN_LOG_LEVEL_INFO,         /*INFO LOG LEVEL*/
    IPSI_BIN_LOG_LEVEL_DEBUG,     /*DEBUG LOG LEVEL*/
    IPSI_BIN_LOG_LEVEL_END
} IPSI_BIN_LOG_LEVEL_E;


/**
* @defgroup IPSI_BIN_LOG_FIXLEN_CALLBACK_FUNC
* @ingroup Binary_Log_Functions
* @par Prototype
* @code
* typedef void (*IPSI_BIN_LOG_FIXLEN_CALLBACK_FUNC)(SEC_UINT uiLogCode,
*                                                  SEC_UINT uiLogLevel,
*                                                 SEC_UINT uiLogType,
*                                                 void * pFormat,
*                                                 void* ulPara1,
*                                                 void* ulPara2,
*                                                 void* ulPara3,
*                                                 void* ulPara4);
* @endcode
*
* @par Purpose
* This function is a callback function pointer for the fixed length log.
* This callback function will return back to a maximum of 4 unsigned 
* parameters which has been passed to logging function
*
* @par Description
* This is a callback function pointer for fixed length log.From the input 
* arguments, user can identify the unique log code, log level, and log type.
* Using this function, user can get maximum of 4 different unsigned values.
*
* @param[in] uiLogCode Indicates unique log code [NA/NA]
* @param[in] uiLogLevel Indicates unique log level [IPSI_BIN_LOG_LEVEL_E]
* @param[in] uiLogType Indicates unique log type. 
* [IPSI_BIN_LOG_TYPE_WARNING/IPSI_BIN_LOG_TYPE_CFG/IPSI_BIN_LOG_TYPE_RUN]
* @param[in]  pFormat Indicates log message. Contains "%d", if any variable
* argument is passed [NA/NA]
* @param[in] ulPara1  First unsigned parameter [NA/NA]
* @param[in] ulPara2  Second unsigned parameter [NA/NA]
* @param[in] ulPara3  Third unsigned parameter [NA/NA]
* @param[in] ulPara4  Fourth unsigned parameter [NA/NA]
* 
* @par Return values
* None
* @par Dependency
* ipsi_bin_log.h
*
* @attribute No No
*
* @par Note
* \n
* - If this callback is used in multi-threaded scenario, application need to 
*   take care of synchronization of the logs.
* - ulPara1, ulPara2, ulPara3, and ulPara4 are unsigned parameters and 
*   while using these parameters application need to typecast to appropriate 
*   data type.
*
* @par Example
* None
*
* @par Related Topics
* None
*/

typedef void (*IPSI_BIN_LOG_FIXLEN_CALLBACK_FUNC)(SEC_UINT uiLogCode,
                                                  SEC_UINT uiLogLevel,
                                                 SEC_UINT uiLogType,
                                                 void * pFormat,
                                                 void* ulPara1,
                                                 void* ulPara2,
                                                 void* ulPara3,
                                                 void* ulPara4);


/**
* @defgroup IPSI_BIN_LOG_VARLEN_CALLBACK_FUNC
* @ingroup Binary_Log_Functions
* @par Prototype
* @code
* typedef void (*IPSI_BIN_LOG_VARLEN_CALLBACK_FUNC)(SEC_UINT uiLogCode, 
*                                                  SEC_UINT uiLogLevel,
*                                                  SEC_UINT uiLogType, 
*                                                  void* pFormat, 
*                                                  void* pData);
* @endcode
*
* @par Purpose
* The function is a callback function pointer for the variable length log. 
* \n
* This callback function will return back the string which has been passed
* to the logging function.
* 
* @par Description
* This is a callback function pointer for variable length log.From the input 
* arguments, user can identify the unique log code, log level, and log type.
* Using this function, user can get the string that is passed.
* @param[in] uiLogCode Indicates unique log code. [NA/NA]
* @param[in] uiLogLevel Indicates unique log level. [IPSI_BIN_LOG_LEVEL_E]
* @param[in] uiLogType Indicates unique log type.
* [IPSI_BIN_LOG_TYPE_WARNING/IPSI_BIN_LOG_TYPE_CFG/IPSI_BIN_LOG_TYPE_RUN]
* @param[in] pFormat Log Message. Contains "%s" in the message. [NA/NA]
* @param[in] pData NULL Terminated string. [NA/NA]
* 
* @par Return values
* None
* @par Dependency
* ipsi_bin_log.h
*
* @attribute No No
*
* @par Note
* \n
* If this callback is used in multi-threaded scenario, application need to 
* take care of synchronization of the logs.
*
* @par Example
* None
*
* @par Related Topics
* None
*/

typedef void (*IPSI_BIN_LOG_VARLEN_CALLBACK_FUNC)(SEC_UINT uiLogCode, 
                                                 SEC_UINT uiLogLevel,
                                                 SEC_UINT uiLogType, 
                                                 void* pFormat, 
                                                 void* pData);



/* This structure is used to set the log callback function in IPSI Log.*/ 

/**
* @defgroup IPSI_REG_BIN_LOG_FUNC_S
* @ingroup Binary_Log_DataStructures
* @par Prototype
* @code
* typedef struct stIpsiRegBinLogFunc
* {
*    IPSI_BIN_LOG_FIXLEN_CALLBACK_FUNC pfLogFixLenFuncPtr;
*    IPSI_BIN_LOG_VARLEN_CALLBACK_FUNC pfLogVarLenFuncPtr;   
* }IPSI_REG_BIN_LOG_FUNC_S;
* @endcode
* @datastruct pfLogFixLenFuncPtr Specifies Fixed length log function pointer
* @datastruct pfLogVarLenFuncPtr Specifies Variable length
*  log function pointer   
*/

typedef struct stIpsiRegBinLogFunc
{
       /*Fixed length log function pointer*/
    IPSI_BIN_LOG_FIXLEN_CALLBACK_FUNC pfLogFixLenFuncPtr;

     /*Variable length log function pointer*/   
    IPSI_BIN_LOG_VARLEN_CALLBACK_FUNC pfLogVarLenFuncPtr;   
}IPSI_REG_BIN_LOG_FUNC_S;




/**
* @defgroup IPSI_BinLog_regLogFunc
* @ingroup Binary_Log_Functions
* @par Prototype
* @code
* SEC_INT IPSI_BinLog_regLogFunc(IPSI_REG_BIN_LOG_FUNC_S 
*                                * pstBinLogFunc);
*
* @endcode
*
* @par Purpose
* This API is used to set the callback function for the log.
*
* @par Description
* This function sets the two callback functions, that is,
* IPSI_BIN_LOG_VARLEN_CALLBACK_FUNC and IPSI_BIN_LOG_FIXLEN_CALLBACK_FUNC.
* @param[in] pstBinLogFunc Indicates NULL pointer. [NA/NA]
*
* @retval SEC_SUCCESS Indicates success [0|NA]
* @retval SEC_ERROR Indicates failure [-1|NA]
*
* @par Dependency
* ipsi_bin_log.h
*
* @attribute No No
*
* @par Note
* \n
* This API should be called only in main thread at the beginning
* of the application.
*
* @par Example
* None
*
* @par Related Topics
* None
*/
 CRYPTOLINKDLL SEC_INT IPSI_BinLog_regLogFunc(IPSI_REG_BIN_LOG_FUNC_S 
                                                              * pstBinLogFunc);

 

/**
* @defgroup IPSI_BinLog_setLogLevel
* @ingroup Binary_Log_Functions
* @par Prototype
* @code
* SEC_INT IPSI_BinLog_setLogLevel(IPSI_BIN_LOG_LEVEL_E eLevel);
* @endcode
*
* @par Purpose
* This API is used to set the current log level required.
*
* @par Description
* This function sets the current log level.
* Only messages equal to or above the current log level will be logged.
* If Log level is set to IPSI_BIN_LOG_LEVEL_END, no log messages are logged.
* @param[in] eLevel Specifies the log level to be set, IPSI_BIN_LOG_LEVEL_E.
* [IPSI_BIN_LOG_LEVEL_E]
* 
* @retval SEC_SUCCESS Indicates success [0|NA]
* @retval SEC_ERROR Indicates failure [-1|NA]
*
* @par Dependency
* ipsi_bin_log.h
*
* @attribute No No
*
* @par Note
*
* None
*
* @par Example
* None
*
* @par Related Topics
* None
*/


 CRYPTOLINKDLL SEC_INT IPSI_BinLog_setLogLevel(IPSI_BIN_LOG_LEVEL_E eLevel);


/**
* @defgroup IPSI_BinLog_getLogLevel
* @ingroup Binary_Log_Functions
* @par Prototype
* @code
* IPSI_BIN_LOG_LEVEL_E  IPSI_BinLog_getLogLevel(SEC_VOID);
* @endcode
*
* @par Purpose
* This function is used to get the current log level set. 
*
* @par Description
* This API function returns the current log level set.
*
* @par Parameters
* None
* 
* @retval SEC_LOG_LEVEL_E The current log level.
* The log levels can be one of these: \n
* IPSI_BIN_LOG_LEVEL_CRITICAL, IPSI_BIN_LOG_LEVEL_ERROR, 
* IPSI_BIN_LOG_LEVEL_WARNING, IPSI_BIN_LOG_LEVEL_INFO, 
* IPSI_BIN_LOG_LEVEL_DEBUG, and IPSI_BIN_LOG_LEVEL_END. 
* [NA|NA]
*
* @par Dependency
* ipsi_bin_log.h
*
* @attribute No No
*
* @par Note
*
* None
*
* @par Example
* None
*
* @par Related Topics
* None
*/

 CRYPTOLINKDLL IPSI_BIN_LOG_LEVEL_E  IPSI_BinLog_getLogLevel(SEC_VOID);

/**
* @defgroup IPSI_BinLog_setLogType
* @ingroup Binary_Log_Functions
* @par Prototype
* @code
* SEC_INT IPSI_BinLog_setLogType(SEC_UINT uiWarningLogEnable, 
*             SEC_UINT uiCfgLogEnable, 
*             SEC_UINT uiRunLogEnable);
* @endcode
*
* @par Purpose
* This function is used for setting the log level. 
*
* @par Description
* This function sets the warning, configuration, and run-time log type status.
* If none of the log types are set, no log messages are logged.
* @par Parameters
* @param[in] uiWarningLogEnable Indicates whether to enable or disable
*  warning log. IPSI_BIN_LOG_TYPE_ENABLE - Enable,
*  IPSI_BIN_LOG_TYPE_DISABLE - Disable. 
*  [IPSI_BIN_LOG_TYPE_ENABLE]
* @param[in] uiCfgLogEnable: Indicates whether to enable or disable the
*   configuration log. IPSI_BIN_LOG_TYPE_ENABLE - Enable,
*  IPSI_BIN_LOG_TYPE_DISABLE -Disable.
*  [IPSI_BIN_LOG_TYPE_ENABLE]
* @param[in] uiRunLogEnable: Indicates whether to enable or disable the
*  runtime log. IPSI_BIN_LOG_TYPE_ENABLE - Enable,
* IPSI_BIN_LOG_TYPE_DISABLE - Disable.
* [IPSI_BIN_LOG_TYPE_ENABLE]
* 
* @retval SEC_SUCCESS Indicates success [0|NA]
* @retval SEC_ERROR Indicates failure [-1|NA]
*
* @par Dependency
* ipsi_bin_log.h
*
* @attribute No No
*
* @par Note
*
* None
*
* @par Example
* None
*
* @par Related Topics
* None
*/
 
 CRYPTOLINKDLL SEC_INT IPSI_BinLog_setLogType(SEC_UINT uiWarningLogEnable, 
            SEC_UINT uiCfgLogEnable, 
            SEC_UINT uiRunLogEnable);


/**
* @defgroup IPSI_BinLog_getLogType
* @ingroup Binary_Log_Functions
* @par Prototype
* @code
* SEC_INT IPSI_BinLog_getLogType(SEC_UINT* puiWarningLogEnable, 
*             SEC_UINT* puiCfgLogEnable, 
*             SEC_UINT* puiRunLogEnable);
* 
* @endcode
*
* @par Purpose
* This function is used to get the log type.
*
* @par Description
* This function gets the warning, configuration, and runtime log level status.
* 
* @param[in] puiWarningLogEnable Indicates the warning log type status. 
* IPSI_BIN_LOG_TYPE_ENABLE - Enable, IPSI_BIN_LOG_TYPE_DISABLE - Disable.
* [NA]
* @param[in] puiCfgLogEnable Indicates the configuration log type status
* IPSI_BIN_LOG_TYPE_ENABLE - Enable,  IPSI_BIN_LOG_TYPE_DISABLE - Disable.
* [NA]
* @param[in] puiRunLogEnable Indicates the runtime log level status.
* IPSI_BIN_LOG_TYPE_ENABLE - Enable, IPSI_BIN_LOG_TYPE_DISABLE - Disable. 
* [NA]
* 
* @retval SEC_SUCCESS Indicates success [0|NA]
* @retval SEC_ERROR Indicates failure [-1|NA]
*
* @par Dependency
* ipsi_bin_log.h
*
* @attribute No No
*
* @par Note
*
* None
*
* @par Example
* None
*
* @par Related Topics
* None
*/

 CRYPTOLINKDLL SEC_INT IPSI_BinLog_getLogType(SEC_UINT* puiWarningLogEnable, 
            SEC_UINT* puiCfgLogEnable, 
            SEC_UINT* puiRunLogEnable);


#ifdef	__cplusplus
}
#endif /* end of __cplusplus */

#endif
#endif









