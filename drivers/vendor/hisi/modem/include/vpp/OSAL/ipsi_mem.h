/**
Copyright(C) 2007, Huawei Tech. India Pvt. Ltd.
            ALL RIGHTS RESERVED
FileName   : ipsi_mem.h
Version    : 1
Author     : Jayaraghavendran K
Created on : 2006-12-29
Description: This file contains all the Memory Management related functions.
History:<author>   <date>          <desc>
*/

#ifndef __IPSI_MEM_H_
#define __IPSI_MEM_H_

#include "ipsi_types.h"

#ifdef  __cplusplus
extern "C" {
#endif

/**
    @brief          This function allocates memory of size bytes long 
                    and places it in *ptr

    @param[out]     *ptr            Pointer to the allocated memory , 
                                    which is suitably aligned
                                    for any variable, or NULL 
                                    if the request fails.
    @param[in]      size            Size of the memory block to be allocated.
    @retval         IPSI_SUCCESS   On Success
                    IPSI_FAILURE   On Failure
*/
IPSILINKDLL int ipsi_malloc(void **ptr, size_t size);


/**
    @brief          ipsi_free frees the memory space pointed to by ptr,
                    which must have been returned by a previous call to 
                    ipsi_malloc, otherwise,if ipsi_free(ptr) has already 
                    been called before, undefined behavior occurs. 
                    If ptr is NULL no operation is performed.

    @param[in]      *ptr    Pointer to the allocated memory 
                            which is to be freed.
    @retval         void    returns no value.
*/
IPSILINKDLL void ipsi_free(void *ptr);

/**
    @brief          This function used to set PID value for VPP security components
                       to track memory allocated and freed. Default value if not set using this
                       function is 1. This functions works only in DOPRA,DOPRAV2 and VISPDOPRAv2 OSAL.

    @param[in]      iPid - PID value to be set.
    @retval         IPSI_SUCCESS on success. IPSI_FAILURE if PID value is less than or equal to zero.
*/

IPSILINKDLL int SEC_setMemPid(SEC_INT32 iPid);


/**
    @brief          This function allocates memory of size bytes long 
                    and places it in *ptr and memsets the allocated buffer to 0

    @param[out]     *ptr            Pointer to the allocated memory , 
                                    which is suitably aligned
                                    for any variable, or NULL 
                                    if the request fails.
    @param[in]      size            Size of the memory block to be allocated.
    @retval         IPSI_SUCCESS   On Success
                    IPSI_FAILURE   On Failure
*/

IPSILINKDLL int ipsi_initialized_malloc(void **ptr, size_t size);


#ifdef  __cplusplus
}
#endif
#endif

