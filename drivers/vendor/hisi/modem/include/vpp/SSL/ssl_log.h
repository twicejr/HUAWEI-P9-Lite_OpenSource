
/*
                                                                            
                Copyright 2006, Huawei Technologies Co. Ltd.                
                            ALL RIGHTS RESERVED                             
                                                                            
----------------------------------------------------------------------------
                                                                            
                              ssl_log.h                                     
                                                                            
  Project Code: SeCert                                                      
   Module Name: SSL   		                                                
  Date Created: 2006-01-21                                                  
        Author: Jimmy Bahuleyan		                                        
   Description: Contains logging interface functions                          
----------------------------------------------------------------------------
  Modification History                                                        
  DATE        NAME             DESCRIPTION                                    
----------------------------------------------------------------------------  
  YYYY-MM-DD                                                                  
                                                                              
*/

#include "ipsi_ssl_build_conf.h"

#ifndef	__SEC_LOG_H
#define	__SEC_LOG_H

#include "ipsi_types.h"
#include "sec_sys.h"
#include "sec_log.h"
#include "ssl.h"

#ifdef  __cplusplus
extern "C" {
#endif

/*
  One of the INFO, DEBUG, ERR, FATAL macros _must_ be used to pass
  the format string to SEC_log, depending on the desired log level.
 */
#define	INFO(msg)	SEC_LOG_INFO, __FILE__, __LINE__, msg
#define	DEBUG(msg)	SEC_LOG_DEBUG, __FILE__, __LINE__, msg
#define	ERR(msg)	SEC_LOG_ERR, __FILE__, __LINE__, msg
#define	FATAL(msg)	SEC_LOG_FATAL, __FILE__, __LINE__, msg


#ifdef TLS_DEBUG
#define LOG_DBGBUF_SIZE  0x8000
#endif

#ifndef TLS_NO_STRONG_LOG


/**
* @defgroup ssl_log
* This section contains the ssl_log Functions
*/


/**
* @defgroup ssl_logFunctions
* @ingroup ssl_log
* This section contains the ssl_log Functions
*/


/*
    Func Name: SSL_getstSessionLog
*/
/**
* @defgroup SSL_getstSessionLog
* @ingroup ssl_logFunctions
* @par Prototype
* @code
* SEC_VOID SSL_getstSessionLog(const SSL_SESSION_S * session);
* @endcode
*
* @par Purpose
* This is used to record the session information in logging file.
*
* @par Description
* SSL_getstSessionLog function records the session information in logging file.
*
* @param[in] session Pointer to SSL_SESSION_S [N/A]
* 
* @retval SEC_VOID This function does not return any value [N/A|N/A]
* 
* @par Required Header File
* ssl_log.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_sessionPrint,\n
* SSL_getstSSLLog,\n
* SSL_getstSSLCtxLog.
*/
SSLLINKDLL SEC_VOID SSL_getstSessionLog(const SSL_SESSION_S * session);


/*
    Func Name: SSL_getstSSLLog()
*/
/**
* @defgroup SSL_getstSSLLog
* @ingroup ssl_logFunctions
* @par Prototype
* @code
* SEC_VOID SSL_getstSSLLog(SSL_S *ssl);
* @endcode
*
* @par Purpose
* This is used to record the variable information of SSL_S.
*
* @par Description
* SSL_getstSSLLog function records the variable infomation of SSL_S information in logging file.
* User can get some state and cert information.
*
* @param[in] ssl Pointer to SSL_S [N/A]
* 
* @retval SEC_VOID This function does not return any value [N/A|N/A]
* 
* @par Required Header File
* ssl_log.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getstSSLCtxLog,\n
* SSL_getstSessionLog.
*/
SSLLINKDLL SEC_VOID SSL_getstSSLLog(SSL_S *ssl);


/*
    Func Name: SSL_getstSSLCtxLog()
*/
/**
* @defgroup SSL_getstSSLCtxLog
* @ingroup ssl_logFunctions
* @par Prototype
* @code
* SEC_VOID SSL_getstSSLCtxLog(SSL_CTX_S *ctx);
* @endcode
*
* @par Purpose
* This is used to record the variable information of SSL_CTX_S.
*
* @par Description
* SSL_getstSSLCtxLog function records the variable information of SSL_CTX_S information in logging file.
* User can get some state and cert information.
*
* @param[in] ctx Pointer to SSL_CTX_S [N/A]
* 
* @retval SEC_VOID This function does not return any value [N/A|N/A]
* 
* @par Required Header File
* ssl_log.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getstSessionLog.
*/
SSLLINKDLL SEC_VOID SSL_getstSSLCtxLog(SSL_CTX_S *ctx);
#endif

#ifdef  __cplusplus
}
#endif

#endif	/* __SEC_LOG_H */

