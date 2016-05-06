/*
Copyright(C) 2007, Huawei Tech. India Pvt. Ltd.
ALL RIGHTS RESERVED

Author     : liguangying
Created on : 2008-07-10
Description: This file contains all the log related functions.
*/



#ifndef __IPSI_LOG_H__
#define __IPSI_LOG_H__

#include "ipsi_types.h"
#include "sec_sys.h"


#ifdef  __cplusplus
extern "C" {
#endif

	/*the maximal size of ipis logging message, when user use ipsi_log function, he can't
	  transfer the logging message that size is big than IPSI_MESSAGE_MAX_SIZE. otherwise, it
	  will induce the crash.
	*/
    #define SEC_LOG_MESSAGE_MAX_SIZE  2048

    /*the level for logging module*/
    typedef enum 
    {
    	SEC_LOG_DISABLED = 0,
        SEC_LOG_FATAL = 1,
    	SEC_LOG_ERR = 2, 
    	SEC_LOG_WARNING = 3,
    	SEC_LOG_INFO = 4,
    	SEC_LOG_DEBUG = 5,
    	SEC_LOG_TRACE = 6,
    	SEC_LOG_ALL = 7
     } SEC_LOG_LEVEL;
   

	/*ipsi_LogSizecCb - type of the callback to be provided by application
      to handle log buffer size overflow event. It may close the current IO 
	  and open a new one for logging.*/
     typedef SEC_INT (*SEC_LOG_SZ_CB) (SEC_FILE_F *pLogIO);
    
	/*ipsi_LogCb - type of the callback to be provided by application
      to handle log event.*/
	 typedef SEC_INT (*SEC_LOG_CB) (int level, const char *file, int line, 
                                    const char *msg);


/** @defgroup sec_log
* This section contains the sec_log Functions.
*/


/** @defgroup sec_logFunctions
* @ingroup sec_log
* This section contains the sec_log Functions.
*/



/**
* @defgroup SEC_log
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_INT SEC_log (
* SEC_LOG_LEVEL level,
* const char *file,
* int line,
* const SEC_CHAR *fmt, ...);
* @endcode
*
* @par Purpose
* This is used to log an error message based on log level set. 
*
* @par Description
* SEC_log function logs an error message with priority 'level'. The arguments are printf like.
*
* @param[in] level The log level of the message [N/A]
* @param[in] fmt A format string as passed to printf [N/A]
* @param[in] file The file where event occured [N/A]
* @param[in] line The line in file where event occured [N/A]
* 
* @retval SEC_INT On success [SEC_SUCCESS|N/A]
* @retval SEC_INT On failure [SEC_ERROR|N/A]
*
* @par Required Header File
* sec_log.h
*
* @par Note
* \n
* The log function must be called with the appropriate log level macro. The format string is passed as an
* argument to the log macro. The macros are one of INFO, DEBUG, ERR, FATAL. It is upto these macros to set
* the appropriate log level (hence the programmer need not specify the log level explicitly).
* Eg: SEC_log (INFO ("%d seconds since last packet"), sess->time);
* The above logs an infomational message.\n
* \n
* The logging infomation size should not be big than SEC_LOG_MESSAGE_MAX_SIZE, otherwise, it will induce crash.
*\n
* If application set maximum size for logging & current log file exceeds maximum limit, it is expected that
* application should backup the existing file & create new file using SEC_setLogFile.
* Application should take care that API is success in the callback function. If the API is failed, log file would be NULL
* and new logs would not be logged.
*
* @par Related Topics
* SEC_getLogLevel,\n
* SEC_setLogLevel
*/
 
CRYPTOLINKDLL SEC_INT SEC_log (SEC_LOG_LEVEL level, const char *file, int line, const SEC_CHAR *fmt, ...);

/**
* @defgroup SEC_logBuf
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_INT SEC_logBuf(SEC_LOG_LEVEL level,
* const char *file,
* int line,
* const SEC_CHAR* buf,
* unsigned int len);
* @endcode
*
* @par Purpose
* This is used to log an error message based on log level set. 
*
* @par Description
* SEC_logBuf function logs an error message body with priority 'level'. 
*
* @param[in] level The log level of the message [N/A]
* @param[in] file The file where event occured [N/A]
* @param[in] line The line in file where event occured [N/A]
* @param[in] buf  The logging message [N/A]
* @param[in] len  Length of log message [N/A]
*
* @retval SEC_INT On success [SEC_SUCCESS|N/A]
* @retval SEC_INT On failure [SEC_ERROR|N/A]
*
* @par Required Header File
* sec_log.h
*
* @par Note
* \n
* SEC_logBuf function will be called when application will record huge string logging message such as certificate.
*\n
* If application set maximum size for logging & current log file exceeds maximum limit, it is expected that
* application should backup the existing file & create new file using SEC_setLogFile.
* Application should take care that API is success in the callback function. If the API is failed, log file would be NULL
* and new logs would not be logged.
*
* @par Related Topics
* SEC_logBuf
*/
CRYPTOLINKDLL SEC_INT SEC_logBuf(SEC_LOG_LEVEL level, const char *file, int line, const SEC_CHAR* buf,unsigned int len);


/**
* @defgroup SEC_getLogLevel
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_LOG_LEVEL SEC_getLogLevel (SEC_VOID);
* @endcode
*
* @par Purpose
* This is used to get the current log level set. 
*
* @par Description
* SEC_getLogLevel function returns the current log level set.
*
* @par Parameters
* N/A
* 
* @retval SEC_LOG_LEVEL The current log level [The log levels can be one of these:
* INFO, DEBUG, ERR, FATAL|N/A]
*
* @par Required Header File
* sec_log.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SEC_log,\n
* SEC_setLogLevel
*/

CRYPTOLINKDLL SEC_LOG_LEVEL SEC_getLogLevel (SEC_VOID);

/**
* @defgroup SEC_setLogLevel
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_VOID SEC_setLogLevel (SEC_LOG_LEVEL eLevel);
* @endcode
*
* @par Purpose
* This is used to set the current log level required.
*
* @par Description
* SEC_setLogLevel function sets the current log level. Only messages equal to or above the current log level will be
* logged.
*
* @param[in] eLevel The log level to be set [N/A]
* 
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl_log.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SEC_log,\n
* SEC_getLogLevel
*/ 

CRYPTOLINKDLL SEC_VOID SEC_setLogLevel (SEC_LOG_LEVEL eLevel);


/**
* @defgroup SEC_setLogFile
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_INT SEC_setLogFile (const SEC_CHAR *pLog);
* @endcode
*
* @par Purpose
* This is used to set the specified file as log file.
*
* @par Description
* SEC_setLogFile function sets the specified file as the current log file.
* It will close previous log file, if any.
*
* @param[in] pLog Path of new file [N/A]
* 
* @retval SEC_INT On success [SEC_SUCCESS|N/A]
* @retval SEC_INT In case of an error. Error happens in case of file open error [SEC_ERROR|N/A]
*
* @par Required Header File
* sec_log.h
* 
* @par Note
* \n
* Log files defined by SEC_setLogFile (const char *file) will be always appended.
* SEC_setLogFile function should be called only once. This function is
* not thread safe and can not be called from multiple threads. This function
* should be called only in main thread.
* 
*
* The file name passed to this API will be directly opened in append mode. No specific file access permissions
* are set for this file. 
*
* No canonicalization is performed for the path associated with the filename and no verification is done on the 
* name passed through the "file" argument. User should do the corresponding verifications before passing
* the input to this function.
* 
* If the user wishes specific file access permissions for the log file, then instead of using 
* this API, they can set the log callback using the SEC_setLogCallback API and save the logs to a file with
* required access permissions themselves.
* 
* @par Related Topics
* SEC_getLogFile,\n
* SEC_setLogMaxSize,\n
* SEC_setLogSizeHandler
*/
CRYPTOLINKDLL SEC_INT SEC_setLogFile (const SEC_CHAR *file);

/**
* @defgroup SEC_setLogFile_MTSafe
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_INT SEC_setLogFile_MTSafe(const char *file,
*                                        SEC_LOG_LEVEL eLevel);
* @endcode
*
* @par Purpose
* This is used to set the log file and log level to be logged.
*
* @par Description
* SEC_setLogFile_MTSafe function sets the specified file as the current
* log file and level passed as current log level.
* It will call close on previous file, if any. This function is thread safe
* function but it is recommended to call this API in main thread at start
* of an application.
*
* @param[in] file Path of new file [N/A]
* @param[in] eLevel Log level to be set. Log level can be one of them from
* following list:
*	- SEC_LOG_DISABLED
*	- SEC_LOG_FATAL
*	- SEC_LOG_ERR
*	- SEC_LOG_WARNING
*	- SEC_LOG_INFO
*	- SEC_LOG_DEBUG
*	- SEC_LOG_TRACE
*	- SEC_LOG_ALL
* 
* @retval SEC_INT On success [SEC_SUCCESS|N/A]
* @retval SEC_INT In case of an error.
*                 Error happens in case of file open failures. [SEC_ERROR|N/A]
* 
* @par Note
* \n
* Log files defined by SEC_setLogFile_MTSafe (const char *file)
* will be always appended.
* This function is multi-thread safe function.
*
* The file name passed to this API will be directly opened in append mode. No specific file access permissions
* are set for this file. 
*
* No canonicalization is performed for the path associated with the filename and no verification is done on the 
* name passed through the "file" argument. User should do the corresponding verifications before passing
* the input to this function.
* 
* If the user wishes specific file access permissions for the log file, then instead of using 
* this API, they can set the log callback using the SEC_setLogCallback API and save the logs to a file with
* required access permissions themselves.
* 
* @par Required Header File
* sec_log.h
* 
* @par Related Topics
* SEC_getLogFile,\n
* SEC_setLogMaxSize,\n
* SEC_setLogSizeHandler
*/
CRYPTOLINKDLL SEC_INT SEC_setLogFile_MTSafe(const char *file,
                                        SEC_LOG_LEVEL eLevel);

/**
* @defgroup SEC_closeLogFile_MTSafe
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_INT SEC_closeLogFile_MTSafe(SEC_VOID);
* @endcode
*
* @par Purpose
* This is used to close the log file.
*
* @par Description
* SEC_closeLogFile_MTSafe function closes the log file.
*
* @par Parameters
* N/A
* 
* @retval SEC_SUCCESS On closing the log file successfully.
* @retval SEC_ERROR on failure
*
* @par Required Header File
* sec_log.h
*
* @par Note
* \n
* This function is multi-thread safe function. It is recommended that
* it should be called at the end of an application.
*
* @par Related Topics
* SEC_getLogFile,\n
* SEC_setLogMaxSize,\n
* SEC_setLogSizeHandler
* 
*/
CRYPTOLINKDLL SEC_INT SEC_closeLogFile_MTSafe(SEC_VOID);

/**
* @defgroup SEC_closeLogFile
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_VOID SEC_closeLogFile(void);
* @endcode
*
* @par Purpose
* This is used to close the logging file.
*
* @par Description
* SEC_closeLogFile function closes the logging file.
*
* @par Parameters
* N/A
* 
* @retval SEC_VOID This does not return any value [N/A|N/A]
* 
* @par Note
* \n
* SEC_closeLogFile should be called only once when application exits.
* This function should be called only in main thread. This function
* is not thread safe and cannot be called from multiple threads.
* If not called in main thread and called in some other thread,
* it will lead to abnormal behavior.
*
* @par Required Header File
* sec_log.h
* 
* @par Related Topics
* SEC_getLogFile,\n
* SEC_setLogMaxSize,\n
* SEC_setLogSizeHandler
*/
CRYPTOLINKDLL SEC_VOID SEC_closeLogFile(void);


/**
* @defgroup SEC_getLogFile
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_FILE_F *SEC_getLogFile (SEC_VOID);
* @endcode
*
* @par Purpose
* This is used to get the current log file set.
*
* @par Description
* SEC_getLogFile function gets the current log file set.
*
* @par Parameters
* N/A
* 
* @retval SEC_FILE_F* Returns the log file set [Current file if any or NULL|N/A]
*
* @par Required Header File
* sec_log.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* SEC_setLogFile,\n
* SEC_setLogMaxSize,\n
* SEC_getLogMaxSize,\n
* SEC_setLogSizeHandler.
*/

CRYPTOLINKDLL SEC_FILE_F *SEC_getLogFile (SEC_VOID);


/**
* @defgroup SEC_setLogMaxSize
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_VOID SEC_setLogMaxSize (SEC_UINT uiSz);
* @endcode
*
* @par Purpose
* This is used to set the maximum bytes to be logged.
*
* @par Description
* SEC_setLogMaxSize function sets the maximum bytes to be logged to log device.
*
* @param[in] uiSz Maximum bytes to be logged [N/A]
* 
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* sec_log.h
*
* @par Note
* \n
* This API should not be called in any of the log callbacks.
* 
* @par Related Topics
* SEC_setLogFile \n
* SEC_getLogMaxSize
*/
CRYPTOLINKDLL SEC_VOID SEC_setLogMaxSize (SEC_UINT uiSz);


/**
* @defgroup SEC_getLogMaxSize
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_UINT SEC_getLogMaxSize (SEC_VOID);
* @endcode
*
* @par Purpose
* This is used to get the size limit for maximum bytes to be logged to the log device.
*
* @par Description
* SEC_getLogMaxSize function gets the size limit for log device.
*
* @par Parameters
* N/A
*
* @retval SEC_UINT Maximum log size limit [size|N/A]
*
* @par Required Header File
* sec_log.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SEC_setLogFile,\n
* SEC_setLogMaxSize,\n
* SEC_setLogSizeHandler.
*/

CRYPTOLINKDLL SEC_UINT SEC_getLogMaxSize (SEC_VOID);


/**
* @defgroup SEC_setLogSizeHandler
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_VOID SEC_setLogSizeHandler (SEC_LOG_SZ_CB pFunc);
* @endcode
*
* @par Purpose
* This is used to set the handler for log size overflow.
*
* @par Description
* SEC_setLogSizeHandler function sets the handler for log size overflow.
*
* @param[in] pFunc Callback function from application [N/A]
* 
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* sec_log.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SEC_setLogFile \n
* SEC_getLogMaxSize.
*/
CRYPTOLINKDLL SEC_VOID SEC_setLogSizeHandler (SEC_LOG_SZ_CB pFunc);

/**
* @defgroup SEC_setLogCallback
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_VOID SEC_setLogCallback (SEC_LOG_CB cb);
* @endcode
*
* @par Purpose
* This is used to set the handler for logging messages.
*
* @par Description
* SEC_setLogCallback function sets the handler for logging. It is used to override the default logging to file mechanism.
*
* @param[in] cb Callback function from application [N/A]
* 
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* sec_log.h
*
* @par Note
* \n
* This function should be called only once during the begining of the application
* 
* @par Related Topics
* SEC_log,\n
* SEC_getLogLevel,\n
* SEC_setLogLevel.
*/ 

CRYPTOLINKDLL SEC_VOID SEC_setLogCallback (SEC_LOG_CB cb);

/**
* @defgroup SEC_initLogLock
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_INT SEC_initLogLock(void);
* @endcode
*
* @par Purpose
* This is used to initialize lock for logging system.
*
* @par Description
* SEC_initLogLock function initializes the lock of logging system. In system logging, it uses the lock for
* threadsafe. when user uses the system in mutil-tread environment, they should call this API to initialize the logging
* lock.
*
* @par Parameters
* N/A
* 
* @retval SEC_INT On success [SEC_SUCCESS|N/A]
* @retval SEC_INT On failure [SEC_ERROR|N/A]
*
* @par Required Header File
* sec_log.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SEC_log,\n
* SEC_getLogLevel,\n
* SEC_setLogLevel.
*/ 

CRYPTOLINKDLL SEC_INT SEC_initLogLock(void);

/*
    @brief          The SEC_freeLogLock function will free the lock of  logging system;

    @retval         SEC_SUCCESS   On Successful Completion .
                    SEC_ERROR     On Failure.
*/
/**
* @defgroup SEC_freeLogLock
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_INT SEC_freeLogLock(void);
* @endcode
*
* @par Purpose
* This is used to free the global lock for logging messages.
*
* @par Description
* SEC_freeLogLock function frees the lock of logging system.
*
* @par Parameters
* N/A
* 
* @retval SEC_INT On success [SEC_SUCCESS|N/A]
* @retval SEC_INT On error [SEC_ERROR|N/A]
*
* @par Required Header File
* sec_log.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SEC_log,\n
* SEC_getLogLevel,\n
* SEC_setLogLevel.
*/
CRYPTOLINKDLL SEC_INT SEC_freeLogLock(void);

/**
* @defgroup SEC_initLogLevelLock
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_INT SEC_initLogLevelLock(void);
* @endcode
*
* @par Purpose
* This is used to initialize lock for loglevel.
*
* @par Description
* SEC_initLogLevelLock function initializes the lock global loglevel. In system logging, it uses the lock for
* threadsafe. when user uses the system in mutil-tread environment, they should call this API to initialize the loglevel
* lock.
*
* @par Parameters
* N/A
* 
* @retval SEC_INT On success [SEC_SUCCESS|N/A]
* @retval SEC_INT On failure [SEC_ERROR|N/A]
*
* @par Required Header File
* sec_log.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SEC_log,\n
* SEC_getLogLevel,\n
* SEC_setLogLevel.
*/ 
CRYPTOLINKDLL SEC_INT SEC_initLogLevelLock(void);


/*
    @brief          The SEC_freeLogLock function will free the lock of  logging system;

    @retval         SEC_SUCCESS   On Successful Completion .
                    SEC_ERROR     On Failure.
*/
/**
* @defgroup SEC_freeLogLevelLock
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_INT SEC_freeLogLevelLock(void);
* @endcode
*
* @par Purpose
* This is used to free the global lock for loglevel.
*
* @par Description
* SEC_freeLogLevelLock function frees the lock for loglevel.
*
* @par Parameters
* N/A
* 
* @retval SEC_INT On success [SEC_SUCCESS|N/A]
* @retval SEC_INT On error [SEC_ERROR|N/A]
*
* @par Required Header File
* sec_log.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SEC_log,\n
* SEC_getLogLevel,\n
* SEC_setLogLevel.
*/
CRYPTOLINKDLL SEC_INT SEC_freeLogLevelLock(void);

#ifdef  __cplusplus
}
#endif

#endif	/* __SEC_LOG_H */


