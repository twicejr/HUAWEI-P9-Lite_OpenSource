/* crypto/crypto.h */
/* ====================================================================
  Copyright (c) 1998-2003 The OpenSSL Project.  All rights reserved.
 
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
 
  1. Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer. 
 
  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
 
  3. All advertising materials mentioning features or use of this
     software must display the following acknowledgment:
     "This product includes software developed by the OpenSSL Project
     for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 
  4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
     endorse or promote products derived from this software without
     prior written permission. For written permission, please contact
     openssl-core@openssl.org.
 
  5. Products derived from this software may not be called "OpenSSL"
     nor may "OpenSSL" appear in their names without prior written
     permission of the OpenSSL Project.
 
  6. Redistributions of any form whatsoever must retain the following
     acknowledgment:
     "This product includes software developed by the OpenSSL Project
     for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 
  THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
  EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
  ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
  OF THE POSSIBILITY OF SUCH DAMAGE.
  ====================================================================
 
  This product includes cryptographic software written by Eric Young
  (eay@cryptsoft.com).  This product includes software written by Tim
  Hudson (tjh@cryptsoft.com).
 
 */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
  All rights reserved.
 
  This package is an SSL implementation written
  by Eric Young (eay@cryptsoft.com).
  The implementation was written so as to conform with Netscapes SSL.
  
  This library is free for commercial and non-commercial use as SEC_INT32 as
  the following conditions are aheared to.  The following conditions
  apply to all code found in this distribution, be it the RC4, RSA,
  lhash, DES, etc., code; not just the SSL code.  The SSL documentation
  included with this distribution is covered by the same copyright terms
  except that the holder is Tim Hudson (tjh@cryptsoft.com).
  
  Copyright remains Eric Young's, and as such any Copyright notices in
  the code are not to be removed.
  If this package is used in a product, Eric Young should be given attribution
  as the author of the parts of the library used.
  This can be in the form of a textual message at program startup or
  in documentation (online or textual) provided with the package.
  
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
  1. Redistributions of source code must retain the copyright
     notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
  3. All advertising materials mentioning features or use of this software
     must display the following acknowledgement:
     "This product includes cryptographic software written by
      Eric Young (eay@cryptsoft.com)"
     The word 'cryptographic' can be left out if the rouines from the library
     being used are not cryptographic related :-).
  4. If you include any Windows specific code (or a derivative thereof) from 
     the apps directory (application code) you must include an acknowledgement:
     "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
  
  THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
  SUCH DAMAGE.
  
  The licence and distribution terms for any publically available version or
  derivative of this code cannot be changed.  i.e. this code cannot simply be
  copied and put under another distribution licence
  [including the GNU Public Licence.]
 */
/* ====================================================================
  Copyright 2002 Sun Microsystems, Inc. ALL RIGHTS RESERVED.
  ECDH support in OpenSSL originally developed by 
  SUN MICROSYSTEMS, INC., and contributed to the OpenSSL project.
 */

#include "ipsi_ssl_build_conf.h"

#ifndef __IPSI_SSL_LOCK_H__
#define __IPSI_SSL_LOCK_H__

#include "ipsi_types.h"
#include "sec_sys.h"
#include "sec_def.h"


#ifdef  __cplusplus
extern "C" {
#endif

/* These are the different types of locks used _internally_ */
#define	SSL_LOCK_ERR			1
#define	SSL_LOCK_X509			2
#define	SSL_LOCK_X509_PKEY		3
#define SSL_LOCK_X509_CRL		4
#define SSL_LOCK_RSA			5
#define SSL_LOCK_EVP_PKEY		6
#define SSL_LOCK_X509_STORE		7
#define SSL_LOCK_SSL_CTX		8
#define SSL_LOCK_SSL_CERT		9
#define SSL_LOCK_SSL_SESSION	10
#define SSL_LOCK_SSL_SESS_CERT	11
#define SSL_LOCK_SSL			12
#define SSL_LOCK_COMP			13
#define SSL_LOCK_LOG 			14
#define SSL_LOCK_HANDSHAKE      15
#define SSL_LOCK_TLS_EXTN       16
#define SSL_LOCK_RANDOM			17
#define SSL_NUM_LOCKS			18	/* Application callback must handle these many number of locks */

/* These are the kinds of operations performed with SSL_lock */
#define SSL_LOCK		1	/* locking */
#define SSL_UNLOCK		2	/* unlocking */
#define SSL_READ		4	/* read lock */
#define SSL_WRITE		8	/* write lock */

#ifndef SSL_NO_LOCK
#	ifndef SSL_W_LOCK
#		define SSL_W_LOCK(type)	\
			SSL_lock(SSL_LOCK|SSL_WRITE,type,__FILE__,__LINE__)	/* A write lock operation */
#		define SSL_W_UNLOCK(type)	\
			SSL_lock(SSL_UNLOCK|SSL_WRITE,type,__FILE__,__LINE__) /* unlock a write lock */
#		define SSL_R_LOCK(type)	\
			SSL_lock(SSL_LOCK|SSL_READ,type,__FILE__,__LINE__)	/* A read lock operation */
#		define SSL_R_UNLOCK(type)	\
			SSL_lock(SSL_UNLOCK|SSL_READ,type,__FILE__,__LINE__) /* unlock a read lock */
#		define SSL_ADD(addr,amount,type)	\
			SSL_addLock(addr,amount,type,__FILE__,__LINE__)		/* do a thread-safe counter add */
#	endif
#else
#	define SSL_W_LOCK(a)
#	define SSL_W_UNLOCK(a)
#	define SSL_R_LOCK(a)
#	define SSL_R_UNLOCK(a)
#	define SSL_ADD(a,b,c)	((*(a))+=(b))
#endif

/**
* @defgroup ssl_lock
* This section contains ssl_lock Functions.
*/

/**
* @defgroup ssl_lockFunctions
* @ingroup ssl_lock
* This section contains the ssl_sock Functions.
*/


/*
    Func Name:  SSL_getNewLockid
*/
/**
* @defgroup SSL_getNewLockid
* @ingroup ssl_lockFunctions
* @par Prototype
* @code
* SEC_INT SSL_getNewLockid(SEC_CHAR *name);
* @endcode
*
* @par Purpose
* This is used to add a new lock to the list of application defined locks.
*
* @par Description
* SSL_getNewLockid function adds a new lock to the list of application defined locks. The name of the lock is
* given as input and the ID is returned.
*
* @param[in] name The name of the lock [N/A]
*
* @retval SEC_INT New id will be returned [New id|N/A]
* @retval SEC_INT On error [SEC_NULL|N/A]
*
* @par Required Header File
* ssl_lock.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* SSL_numLocks,\n
* SSL_lock,\n
* SSL_setIdCallback,\n
* SSL_getIdCallback,\n
* SSL_threadId,\n
* SSL_getLockName.
*/

SSLLINKDLL SEC_INT SSL_getNewLockid(SEC_CHAR *name);

/*
    Func Name:  SSL_numLocks
*/
/**
* @defgroup SSL_numLocks
* @ingroup ssl_lockFunctions
* @par Prototype
* @code
* SEC_INT SSL_numLocks(SEC_VOID);
* @endcode
*
* @par Purpose
* This is used to get the number of predefined locks.
*
* @par Description
* SSL_numLocks function returns the number of pre-defined locks.
*
* @par Parameters
* N/A
*
* @retval SEC_INT Number of predefined locks [Number of locks|N/A]
*
* @par Required Header File
* ssl_lock.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* SSL_getNewLockid,\n
* SSL_lock,\n
* SSL_setIdCallback,\n
* SSL_getIdCallback,\n
* SSL_threadId,\n
* SSL_getLockName.
*/

SSLLINKDLL SEC_INT SSL_numLocks(SEC_VOID);

/*
    Func Name:  SSL_lock
*/
/**
* @defgroup SSL_lock
* @ingroup ssl_lockFunctions
* @par Prototype
* @code
* SEC_VOID SSL_lock(SEC_INT mode, SEC_INT type,const SEC_CHAR *file,SEC_INT line);
* @endcode
*
* @par Purpose
* This is used to lock or unlock a particular lock.
*
* @par Description
* SSL_lock function locks/unlocks a lock identified by id. Do not call directly
* instead use the SSL_*_LOCK/SSL_*_UNLOCK macros.
*
* @param[in] mode determines the locking or unlocking operation [N/A]
* @param[in] type Type of lock which is to be locked or unlocked [N/A]
* @param[in] file File name from where this is called [N/A]
* @param[in] line Line number [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl_lock.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* SSL_getNewLockid,\n
* SSL_numLocks,\n
* SSL_setIdCallback,\n
* SSL_getIdCallback,\n
* SSL_threadId,\n
* SSL_getLockName.
*/

SSLLINKDLL SEC_VOID SSL_lock(SEC_INT mode, SEC_INT type,const SEC_CHAR *file,SEC_INT line);

/*
    Func Name:  SSL_setLockingCallback
*/
/**
* @defgroup SSL_setLockingCallback
* @ingroup ssl_lockFunctions
* @par Prototype
* @code
* SEC_VOID SSL_setLockingCallback(SEC_VOID (*func)(SEC_INT mode,SEC_INT type,
* const SEC_CHAR *file,SEC_INT line));
* @endcode
*
* @par Purpose
* This is used to set the locking callback.
*
* @par Description
* SSL_setLockingCallback function sets the locking callback which will actually perform the lock/unlock operation.
* 
* @param[in] func The pointer of the callback [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl_lock.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* SSL_getLockingCallback.
*/

SSLLINKDLL SEC_VOID SSL_setLockingCallback(SEC_VOID (*func)(SEC_INT mode,SEC_INT type,
					      const SEC_CHAR *file,SEC_INT line));

/*
    Func Name:  SSL_getLockingCallback
*/
/**
* @defgroup SSL_getLockingCallback
* @ingroup ssl_lockFunctions
* @par Prototype
* @code
* SEC_VOID (*SSL_getLockingCallback(SEC_VOID))(SEC_INT mode,SEC_INT type,const SEC_CHAR *file, SEC_INT line);
* @endcode
*
* @par Purpose
* This is used to get locking callback
*
* @par Description
* SSL_getLockingCallback function returns the callback which will actually
* perform the lock/unlock operation.
*
* @par Parameters
* N/A
*
* @retval cb The callback function ((SEC_VOID) (*)(SEC_INT mode,SEC_INT type,const SEC_CHAR *file, SEC_INT line)) or
* SEC_NULL if pointer to the callback function is not set [Pointer to the callback function or SEC_NULL|N/A]
*
* @par Required Header File
* ssl_lock.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* SSL_setLockingCallback,\n
* SSL_addLock.
*/

SSLLINKDLL SEC_VOID (*SSL_getLockingCallback(SEC_VOID))(SEC_INT mode,SEC_INT type,const SEC_CHAR *file,
		SEC_INT line);

/*
    Func Name:  SSL_setAddLockCallback
*/
/**
* @defgroup SSL_setAddLockCallback
* @ingroup ssl_lockFunctions
* @par Prototype
* @code
* SEC_VOID SSL_setAddLockCallback(SEC_INT (*func)(SEC_INT *num,SEC_INT mount,SEC_INT type,
* const SEC_CHAR *file,SEC_INT line));
* @endcode
*
* @par Purpose
* This is used to set the callback which actually performs the thread safe counter add operations.
*
* @par Description
* SSL_setAddLockCallback function sets the callback which will actually perform the thread safe counter add operation.
*
* @param[in] func The pointer of the callback [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl_lock.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* SSL_getAddLockCallback,\n
* SSL_addLock.
*/

SSLLINKDLL SEC_VOID SSL_setAddLockCallback(SEC_INT (*func)(SEC_INT *num,SEC_INT mount,SEC_INT type,
					      const SEC_CHAR *file, SEC_INT line));

/*
    Func Name:  SSL_getAddLockCallback
*/
/**
* @defgroup SSL_getAddLockCallback
* @ingroup ssl_lockFunctions
* @par Prototype
* @code
* SEC_INT (*SSL_getAddLockCallback(SEC_VOID))(SEC_INT *num,SEC_INT mount,SEC_INT type,
* const SEC_CHAR *file,SEC_INT line);
* @endcode
*
* @par Purpose
* This is used to get the callback which actually performs the thread safe add operation.
*
* @par Description 
* SSL_getAddLockCallback function returns the callback which will actually perform the thread safe add operation.
*
* @par Parameters
* N/A
*
* @retval cb The callback function ((SEC_INT) (*)(SEC_INT *num,SEC_INT mount,SEC_INT type,
* const SEC_CHAR *file,SEC_INT line)) or SEC_NULL if pointer to the callback function is not set
* [Pointer to the callback function or SEC_NULL|N/A]
*
* @par Required Header File
* ssl_lock.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* N/A
*/

SSLLINKDLL SEC_INT (*SSL_getAddLockCallback(SEC_VOID))(SEC_INT *num,SEC_INT mount,SEC_INT type,
					  const SEC_CHAR *file,SEC_INT line);

/*
    Func Name:  SSL_setIdCallback
*/
/**
* @defgroup SSL_setIdCallback
* @ingroup ssl_lockFunctions
* @par Prototype
* @code
* SEC_VOID SSL_setIdCallback(SEC_UINT32 (*func)(SEC_VOID));
* @endcode
*
* @par Purpose
* This is used to set the callback which will return the ID of current thread.
*
* @par Description 
* SSL_setIdCallback function sets the callback which will return the ID of current thread.
*
* @param[in] func The pointer of the callback [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl_lock.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* SSL_getNewLockid,\n
* SSL_numLocks,\n
* SSL_lock,\n
* SSL_getIdCallback,\n
* SSL_threadId,\n
* SSL_getLockName.
*/

SSLLINKDLL SEC_VOID SSL_setIdCallback(SEC_UINT32 (*func)(SEC_VOID));

/*
    Func Name:  SSL_getIdCallback
*/
/**
* @defgroup SSL_getIdCallback
* @ingroup ssl_lockFunctions
* @par Prototype
* @code
* SEC_UINT32 (*SSL_getIdCallback(SEC_VOID))(SEC_VOID);
* @endcode
*
* @par Purpose
* This is used to get the callback function which returns the ID of the current thread.
* 
* @par Description
* SSL_getIdCallback function gets the callback which will return the ID of the current thread.
*
* @par Parameters
* N/A
*
* @retval cb The callback function ((SEC_UINT32) (*)(SEC_VOID)) or SEC_NULL if pointer to the callback function is not
* set [Pointer to the callback function or SEC_NULL|N/A]
*
* @par Required Header File
* ssl_lock.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* SSL_getNewLockid,\n
* SSL_numLocks,\n
* SSL_lock,\n
* SSL_setIdCallback,\n
* SSL_threadId,\n
* SSL_getLockName.
*/

SSLLINKDLL SEC_UINT32 (*SSL_getIdCallback(SEC_VOID))(SEC_VOID);

/*
    Func Name:  SSL_threadId
*/
/**
* @defgroup SSL_threadId
* @ingroup ssl_lockFunctions
* @par Prototype
* @code
* SEC_UINT32 SSL_threadId(SEC_VOID);
* @endcode
*
* @par Purpose
* This is used to get the id of current thread.
*
* @par Description
* SSL_threadId function returns the id of current thread.
*
* @par Parameters
* N/A
*
* @retval SEC_UINT32 id of the thread [Thread id|N/A]
*
* @par Required Header File
* ssl_lock.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* SSL_getNewLockid,\n
* SSL_numLocks,\n
* SSL_lock,\n
* SSL_setIdCallback,\n
* SSL_getIdCallback,\n
* SSL_getLockName.
*/

SSLLINKDLL SEC_UINT32 SSL_threadId(SEC_VOID);

/*
    Func Name:  SSL_getLockName
*/
/**
* @defgroup SSL_getLockName
* @ingroup ssl_lockFunctions
* @par Prototype
* @code
* const SEC_CHAR *SSL_getLockName(SEC_INT type);
* @endcode
*
* @par Purpose
* This is used to get the name of lockid.
*
* @par Description
* SSL_getLockName function returns the name of lock of id 'type'.
*
* @param[in] type The lock id [N/A]
*
* @retval SEC_CHAR* Name of the lock [Lock name|NA]
*
* @par Required Header File
* ssl_lock.h
*
* @par Note
* \n
* If the lock of id 'type' does not exist, the API will return "ERROR".
*
* @par Related Topics
* SSL_getNewLockid,\n
* SSL_numLocks,\n
* SSL_lock,\n
* SSL_setIdCallback,\n
* SSL_getIdCallback,\n
* SSL_threadId.
*/

SSLLINKDLL const SEC_CHAR *SSL_getLockName(SEC_INT type);

/*
    Func Name:  SSL_addLock
*/
 
/**
* @defgroup SSL_addLock
* @ingroup ssl_lockFunctions
* @par Prototype
* @code
* SEC_INT SSL_addLock(SEC_INT *pointer,
* SEC_INT amount,
* SEC_INT type,
* const SEC_CHAR *file, SEC_INT line);
* @endcode
*
* @par Purpose
* This is used to perform the thread safe counter add operation.
*
* @par Description
* SSL_addLock function performs the thread safe counter add operation with after taking lock identified by 'type'.
* Do not call directly instead use the SSL_ADD macro.
*
* @param[in] pointer Pointer to counter [N/A]
* @param[in] amount Amount to add [N/A]
* @param[in] type ID of the lock [N/A]
* @param[in] file File name from where this is called [N/A]
* @param[in] line Line number [N/A]
*
* @retval SEC_INT  returns the updated value of the counter [New value|N/A]
* @retval SEC_INT On error [SEC_NULL|N/A]
*
* @par Required Header File
* ssl_lock.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* SSL_setAddLockCallback,\n
* SSL_getAddLockCallback.
*/

SSLLINKDLL SEC_INT SSL_addLock(SEC_INT *pointer,SEC_INT amount,SEC_INT type, const SEC_CHAR *file,
		    SEC_INT line);


/*
    Func Name:  SSL_enableMultiThread
*/
 
/**
* @defgroup SSL_enableMultiThread
* @ingroup ssl_lockFunctions
* @par Prototype
* @code
* SEC_VOID SSL_enableMultiThread(SEC_VOID);
* @endcode
*
* @par Purpose
* This is used to set the library for thread safe running.
*
* @par Description
* SSL_enableMultiThread function sets the library for thread safe running. It's based on the osal thread locking
* function. If this function is called, we should not call SSL_setIdCallback and SSL_setLockingCallback functions. We
* should call SSL_freeMultiThread function to free the resource allocate by this API.
*
* @par Parameters
* N/A
*
* @retval SEC_VOID  Does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl_lock.h
*
* @par Note
* \n
* This function should be called only in main thread at the beginning
* of the application.
*
* @par Related Topics
* SSL_freeMultiThread.
*/

SSLLINKDLL SEC_VOID SSL_enableMultiThread(SEC_VOID);

/*
    Func Name:  SSL_freeMultiThread
*/
 
/**
* @defgroup SSL_freeMultiThread
* @ingroup ssl_lockFunctions
* @par Prototype
* @code
* SEC_VOID SSL_freeMultiThread(SEC_VOID);
* @endcode
*
* @par Purpose
* This is used to free the thread related resources.
*
* @par Description
* SSL_freeMultiThread function frees the resources allocated by SSL_enableMultiThread.
*
* @par Parameters
* N/A
*
* @retval SEC_VOID  Does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl_lock.h
*
* @par Note
* \n
* This function should be called only in main thread at the end
* of the application.
*
* @par Related Topics
* SSL_enableMultiThread,\n
* SSL_threadCleanup,\n
* SSL_libraryFini.
*/

SSLLINKDLL SEC_VOID SSL_freeMultiThread(SEC_VOID);

#ifdef  __cplusplus
}
#endif
#endif

