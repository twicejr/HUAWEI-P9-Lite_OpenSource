/**
Copyright(C) 2007, Huawei Tech. India Pvt. Ltd.
            ALL RIGHTS RESERVED

Filenmae   : ipsi_thread.h
Version    : 1
Author     : Jayaraghavendran K
Created on : 2007-01-04
Description: This file contains all the thread related functions.
History:<author>   <date>          <desc>
*/

#ifndef __IPSI_THREAD_H_
#define __IPSI_THREAD_H_

#include "ipsi_types.h"
#include "ipsi_misc.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* Pointer to read write lock */
typedef void* ipsi_rwlock_t;

/* Pointer to thread id */
typedef void* ipsi_thread_id_t;

typedef void* ipsi_cond_var_t;
typedef void* ipsi_mutex_t;
typedef void* ipsi_thread_handle_t;


/**
    @brief        The ipsi_rwlock_create function creates the read/write lock
                  and initializes it.

    @param[out]   lock           An initialised read/write lock pointer.
    @retval       IPSI_SUCCESS  On Success
                  IPSI_FAILURE  On Failure
*/
IPSILINKDLL int ipsi_rwlock_create(ipsi_rwlock_t *lock);


/**
    @brief        The ipsi_rwlock_destroy function destroys the read/write lock.

    @param[in]    lock           lock variable which has been created using
                                 ipsi_rwlock_create function.
    @retval       IPSI_SUCCESS  On Success
                  IPSI_FAILURE  On Failure
*/
IPSILINKDLL int ipsi_rwlock_destroy(ipsi_rwlock_t lock);


/**
    @brief        The ipsi_rwlock_rdlock functions locks a read/write lock 
                  for reading,blocks until the lock can be acquired.

    @param[in]    lock           lock variable which has been created using
                                 ipsi_rwlock_create function.
    @retval       IPSI_SUCCESS  On Success
                  IPSI_FAILURE  On Failure
*/
IPSILINKDLL int ipsi_rwlock_rdlock(ipsi_rwlock_t lock);


/**
    @brief        The ipsi_rwlock_tryrdlock function attempts to lock a 
                  read/write lock for reading without blocking if the lock 
                  is unavailable.

    @param[in]    lock           lock variable which has been created using
                                 ipsi_rwlock_create function.
    @retval       IPSI_SUCCESS  On Success
                  IPSI_FAILURE  On Failure
*/
IPSILINKDLL int ipsi_rwlock_tryrdlock(ipsi_rwlock_t lock);


/**
    @brief        The ipsi_rwlock_wrlock function locks a read/write lock 
                  for writing,blocks until the lock can be acquired.

    @param[in]    lock           lock variable which has been created using
                                 ipsi_rwlock_create function.
    @retval       IPSI_SUCCESS  On Success
                  IPSI_FAILURE  On Failure
*/
IPSILINKDLL int ipsi_rwlock_wrlock(ipsi_rwlock_t lock);


/**
    @brief        The ipsi_rwlock_trywrlock function attempts to lock a 
                  read/write lock for writing without blocking if the lock 
                  is unavailable.

    @param[in]    lock           lock variable which has been created using
                                 ipsi_rwlock_create function.
    @retval       IPSI_SUCCESS  On Success
                  IPSI_FAILURE  On Failure
*/
IPSILINKDLL int ipsi_rwlock_trywrlock(ipsi_rwlock_t lock);


/**
    @brief        The ipsi_rwlock_unlock unlocks the read/write lock.

    @param[in]    lock           lock variable which has been created using
                                 ipsi_rwlock_create function.
    @retval       IPSI_SUCCESS  On Success
                  IPSI_FAILURE  On Failure
*/
IPSILINKDLL int ipsi_rwlock_unlock(ipsi_rwlock_t lock);


/**
    @brief    The ipsi_get_thread_id function will return the Thread ID of the
              current thread.

    @retval   Thread ID of the current Thread.
*/
IPSILINKDLL ipsi_thread_id_t ipsi_get_thread_id(void);


/**
    @brief    The ipsi_thread_create function will create the thread.

    @param[in]    dpvThread Thread to be spawned.
                  pFnstartRoutine Rotine to be executed by the thread
                  pvArg Thread input argument.
                  dpvThreadHandle Thread handle.

    @retval       IPSI_SUCCESS  On Success
                  IPSI_FAILURE  On Failure
*/
IPSILINKDLL SEC_INT ipsi_thread_create(
          ipsi_thread_id_t *pvThread,
          SEC_VOID* (*pFnstartRoutine)(SEC_VOID *arg), SEC_VOID *pvArg,
          ipsi_thread_handle_t *pThreadHandle);


/**
    @brief    The ipsi_thread_close function will close the thread.

    @param[in]    pvThread Pointer to thread.
                  pstThreadHandle Pointer to handle.

    @retval       IPSI_SUCCESS  On Success
                  IPSI_FAILURE  On Failure
*/

IPSILINKDLL SEC_VOID ipsi_thread_close(ipsi_thread_id_t Thread,
                            ipsi_thread_handle_t ThreadHandle);


/**
    @brief    The ipsi_createCondVar function cretes conditional variable.

    @param[in]     picondvar Pointer to conditional var

    @retval       IPSI_SUCCESS  On Success
                  IPSI_FAILURE  On Failure
*/
IPSILINKDLL SEC_INT ipsi_createCondVar(ipsi_cond_var_t *pcondvar);


/**
    @brief    The ipsi_condTimedwait waits until the timeout or it gets signal

    @param[in]    condmutex Pointer to mutex.
                  picondvar Pointer to conditional var


    @retval       IPSI_SUCCESS  On Success
                  IPSI_FAILURE  On Failure
*/
IPSILINKDLL SEC_INT ipsi_condTimedwait(SEC_INT timeout,
         ipsi_cond_var_t condvar,ipsi_mutex_t condmutex);

/**
    @brief    The ipsi_condSignal waits until the timeout or it gets signal

    @param[in]    condvar Pointer to conditional var
				  condmutex Pointer to mutex



    @retval       IPSI_SUCCESS  On Success
                  IPSI_FAILURE  On Failure
*/
IPSILINKDLL SEC_INT ipsi_condSignal(ipsi_cond_var_t condvar);


/**
    @brief    The ipsi_deleteCondVar waits until the timeout or it gets signal

    @param[in]  picondvar Pointer to conditional var



    @retval       IPSI_SUCCESS  On Success
                  IPSI_FAILURE  On Failure
*/
IPSILINKDLL SEC_INT ipsi_deleteCondVar(ipsi_cond_var_t condvar);

IPSILINKDLL SEC_INT ipsi_thread_create_ex(SEC_VOID* (*pFnstartRoutine)(SEC_VOID *arg),
                           SEC_VOID *pvArg,ipsi_thread_id_t *pThread);

IPSILINKDLL SEC_VOID ipsi_thread_close_ex(ipsi_thread_id_t Thread);



/**
    @brief          ipsi_opensemaphore:creates/opens the named semaphore object

    @param          pcString   The name of the semaphore
					pSemHandlem  The semaphore handle
					pError  The open semaphore error
					pCloseStatus The close semaphore status

    @retval         This function returns IPSI_SUCCESS if it succeeds
					otherwise return IPSI_FAILURE
*/
IPSILINKDLL int ipsi_opensemaphore(char *pcString,
                                   ipsi_sem_handle_t *pSemHandlem,
                                   int * piError,int * piCloseStatus);


/**
    @brief          ipsi_closesemaphore:Closes the semaphore object

    @param          pcString   The name of the semaphore
					pSemHandlem  The semaphore handle

    @retval         This function returns IPSI_SUCCESS if it succeeds
					otherwise return IPSI_FAILURE
*/
IPSILINKDLL int ipsi_closesemaphore(char *pcString,
                                    ipsi_sem_handle_t pSemHandlem);


IPSILINKDLL int ipsi_create_atomic_glbInitLock(void);

IPSILINKDLL int ipsi_acquire_glbInitLock(void);

IPSILINKDLL int ipsi_release_glbInitLock(void);


#ifdef  __cplusplus
}
#endif
#endif

