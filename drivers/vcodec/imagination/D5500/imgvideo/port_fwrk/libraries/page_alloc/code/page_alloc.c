/*!
 *****************************************************************************
 *
 * @File       page_alloc.c
 * @Description    This file contains the Page Allocator.
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called "GPLHEADER" included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#include "img_defs.h"
#include "img_types.h"
#include "img_errors.h"
#include "page_alloc.h"
#include "page_alloc_km.h"
#include "dman_api_km.h"
#include "rman_api.h"
#include "sysmem_utils.h"
#include "sysdev_utils.h"
#include "sysos_api_km.h"
#include "report_api.h"
#include "sysbrg_utils.h"

#define PALLOC_RES_TYPE_1    (0x09090001)    /*!< Resource type */

/*!
******************************************************************************
 This structure contains attachment information.
******************************************************************************/
typedef struct
{
    IMG_HANDLE  hDevHandle;     /*<! Device handle          */
    IMG_HANDLE  hResBHandle;    /*<! Resource bucket handle */
    SYSDEVU_sInfo*  hSysDevHandle;  /*<! SYSDEVKN device handle */
} PALLOC_sAttachContext;

/*!
******************************************************************************
 This structure contains allocation information.
******************************************************************************/
typedef struct
{
    IMG_HANDLE           hDevHandle;    /*!< DMAN device handle             */
    SYSMEMU_sPages       *hPagesHandle;  /*!< SYSMEM handle                  */
    PALLOCKM_sAllocInfo  sAllocInfo;    /*!< Allocation information         */
    IMG_HANDLE           hBufHandle;    /*!< Handle to specific buffer data */
    PALLOC_eImportBufType      eBufType;      /*!< Buffer type                    */
} PALLOC_sKmAlloc;

struct PALLOCKM_Heap;

typedef SYS_eMemPool (*PALLOCKM_InitHeap)(struct PALLOCKM_Heap *heap);

struct PALLOCKM_Heap {
	SYS_eMemPool heap_id;
	PALLOCKM_InitHeap init;
};

#if defined(PORTFWRK_SYSMEM_ION)
static SYS_eMemPool initAndroidION(struct PALLOCKM_Heap *heap) {
	IMG_RESULT result;
	SYS_eMemPool memHeap;
	result = SYSMEMKM_AddIONMemory(IMG_NULL, &memHeap);
	IMG_ASSERT(result == IMG_SUCCESS);
	if (result != IMG_SUCCESS)
		return SYS_eMemPoolInvalid;

	return memHeap;
}
#endif

#if defined(PORTFWRK_SYSMEM_ASHMEM)
static SYS_eMemPool initAndroidAshMem(struct PALLOCKM_Heap *heap) {
	IMG_RESULT result;
	SYS_eMemPool memHeap;
	result = SYSMEMKM_AddAshMemory(IMG_NULL, &memHeap);
	IMG_ASSERT(result == IMG_SUCCESS);
	if (result != IMG_SUCCESS)
		return SYS_eMemPoolInvalid;

	return memHeap;
}
#endif

#if defined(PORTFWRK_SYSMEM_DMABUF)
static SYS_eMemPool initDMABuf(struct PALLOCKM_Heap *heap) {
	IMG_RESULT result;
	SYS_eMemPool memHeap;
	result = SYSMEMKM_AddDMABufMemory(IMG_NULL, &memHeap);
	IMG_ASSERT(result == IMG_SUCCESS);
	if (result != IMG_SUCCESS)
		return SYS_eMemPoolInvalid;

	return memHeap;
}
#endif

#if defined(PORTFWRK_SYSMEM_DMABUF)
static SYS_eMemPool initGEMBuf(struct PALLOCKM_Heap *heap) {
	IMG_RESULT result;
	SYS_eMemPool memHeap;
	result = SYSMEMKM_AddDMABufMemory(IMG_NULL, &memHeap);
	IMG_ASSERT(result == IMG_SUCCESS);
	if (result != IMG_SUCCESS)
		return SYS_eMemPoolInvalid;

	return memHeap;
}
#endif

#if defined(PORTFWRK_SYSMEM_ION)
static struct PALLOCKM_Heap androidion = { SYS_eMemPoolInvalid, initAndroidION }; /* PALLOC_BUFTYPE_ANDROIDNATIVE */
#endif

#if defined(PORTFWRK_SYSMEM_ASHMEM)
static struct PALLOCKM_Heap ashmem = { SYS_eMemPoolInvalid, initAndroidAshMem }; /* PALLOC_BUFTYPE_ANDROIDASHMEM */
#endif

#if defined(PORTFWRK_SYSMEM_DMABUF)
static struct PALLOCKM_Heap dmaheap = { SYS_eMemPoolInvalid, initDMABuf }; /* PALLOC_BUFTYPE_DMABUF */
static struct PALLOCKM_Heap gemheap = { SYS_eMemPoolInvalid, initGEMBuf }; /* PALLOC_BUFTYPE_GEMBUF */
#endif

struct PALLOCKM_Heap *pallockm_heaps[PALLOC_BUFTYPE_MAX] = {
		IMG_NULL,  /* PALLOC_BUFTYPE_DEFAULT */
		IMG_NULL, /* PALLOC_BUFTYPE_USERALLOC */
#if defined(PORTFWRK_SYSMEM_ION)
		&androidion,
#else
		IMG_NULL,
#endif
#if defined(PORTFWRK_SYSMEM_ASHMEM)
		&ashmem,
#else
		IMG_NULL,
#endif
#if defined(PORTFWRK_SYSMEM_DMABUF)
		&dmaheap,
#else
		IMG_NULL,
#endif
#if defined(PORTFWRK_SYSMEM_DMABUF)
		&gemheap,
#else
		IMG_NULL,
#endif
};

#define PALLOCKM(index) (pallockm_heaps[(index)])

static IMG_BOOL initialized = IMG_FALSE;
/*!
******************************************************************************

 @Function                PALLOCKM_Initialise

******************************************************************************/
IMG_RESULT PALLOCKM_Initialise(IMG_VOID)
{
	int i;

	if (initialized)
		return IMG_SUCCESS;

	for (i = 0; i < PALLOC_BUFTYPE_MAX; i++) {
		if (PALLOCKM(i))
			PALLOCKM(i)->heap_id = PALLOCKM(i)->init(PALLOCKM(i));
	}

	initialized = IMG_TRUE;
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                PALLOCKM_Deinitialise

******************************************************************************/
IMG_VOID PALLOCKM_Deinitialise(IMG_VOID)
{
	int i;
	for (i = 0; i < PALLOC_BUFTYPE_MAX; i++) {
		if (PALLOCKM(i) && SYS_eMemPoolIsValid(PALLOCKM(i)->heap_id))
			SYSMEMU_RemoveMemoryHeap(PALLOCKM(i)->heap_id);
	}

	initialized = IMG_FALSE;
}


/*!
******************************************************************************

 @Function              palloc_fnCompConnect

******************************************************************************/
static IMG_RESULT palloc_fnCompConnect (
    IMG_HANDLE   hAttachHandle,
    IMG_VOID **  ppvCompAttachmentData
)
{
    PALLOC_sAttachContext *  psAttachContext;
    IMG_UINT32               ui32Result;
    IMG_CHAR *               pszDeviceName;

    /* Allocate attachment context structure...*/
    psAttachContext = IMG_MALLOC(sizeof(*psAttachContext));
    IMG_ASSERT(psAttachContext != IMG_NULL);
    if (psAttachContext == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    IMG_MEMSET(psAttachContext, 0, sizeof(*psAttachContext));

    /* Ensure the resource manager is initialised...*/
    ui32Result = RMAN_Initialise();
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_rman_init;
    }

    /* Create a bucket for the resources...*/
    ui32Result = RMAN_CreateBucket(&psAttachContext->hResBHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_rman_bucket;
    }

    /* Get device information...*/
    psAttachContext->hDevHandle = DMANKM_GetDevHandleFromAttach(hAttachHandle);
    pszDeviceName = DMANKM_GetDeviceName(psAttachContext->hDevHandle);
    ui32Result = SYSDEVU_OpenDevice(pszDeviceName, &psAttachContext->hSysDevHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_sysdev_open;
    }

    /* Return attachment context...*/
    *ppvCompAttachmentData = psAttachContext;

    /* Return success...*/
    return IMG_SUCCESS;

    /* Error handling. */
error_sysdev_open:
    RMAN_DestroyBucket(psAttachContext->hResBHandle);
error_rman_bucket:
error_rman_init:
    IMG_FREE(psAttachContext);

    return ui32Result;
}

/*!
******************************************************************************

 @Function              palloc_fnCompDisconnect

******************************************************************************/
static IMG_RESULT palloc_fnCompDisconnect (
    IMG_HANDLE  hAttachHandle,
    IMG_VOID *  pvCompAttachmentData
)
{
    PALLOC_sAttachContext *  psAttachContext = pvCompAttachmentData;

    /* Destroy the bucket and it's resources...*/
    RMAN_DestroyBucket(psAttachContext->hResBHandle);

    /* If we opened a device...*/
    if (psAttachContext->hSysDevHandle != IMG_NULL)
    {
        SYSDEVU_CloseDevice(psAttachContext->hSysDevHandle);
    }

    /* Free attachment context...*/
    IMG_FREE(psAttachContext);

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              palloc_fnCompAttach

******************************************************************************/
static IMG_RESULT palloc_fnCompAttach(
    IMG_HANDLE            hConnHandle,
    DMANKM_sCompAttach *  psCompAttach
)
{
    psCompAttach->pfnCompConnect    = palloc_fnCompConnect;
    psCompAttach->pfnCompDisconnect = palloc_fnCompDisconnect;

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                PALLOC_AttachToConnection

******************************************************************************/
IMG_RESULT PALLOC_AttachToConnection(
    IMG_UINT32           ui32ConnId,
    SYSBRG_POINTER_ARG(IMG_UINT32) pui32AttachId
)
{
    IMG_HANDLE  hDevHandle;
    IMG_UINT32  ui32Result;
    IMG_HANDLE  hConnHandle;
    IMG_UINT32  ui32AttachId;

    /* Get the connection handle from it's ID...*/
    ui32Result = DMANKM_GetConnHandleFromId(ui32ConnId, &hConnHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Get the device handle from the connection...*/
    hDevHandle = DMANKM_GetDevHandleFromConn(hConnHandle);
    IMG_ASSERT(IMG_NULL != hDevHandle);
    if (IMG_NULL == hDevHandle)
    {
        return IMG_ERROR_FATAL;
    }

    /* Lock the device...*/
    DMANKM_LockDeviceContext(hDevHandle);

    /* Call on to the kernel function...*/
    ui32Result = DMANKM_AttachComponent(hConnHandle, "PALLOCBRG", palloc_fnCompAttach, IMG_NULL, &ui32AttachId);

    /* Unlock the device...*/
    DMANKM_UnlockDeviceContext(hDevHandle);

    /* Check the DMANKM_AttachComponent() call's result. */
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    ui32Result = SYSOSKM_CopyToUser(pui32AttachId, &ui32AttachId, sizeof(ui32AttachId));
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Return ui32Result...*/
    return ui32Result;
}

/*!
******************************************************************************

 @Function             palloc_fnFree

******************************************************************************/
static IMG_VOID palloc_fnFree(
    IMG_VOID *  pvParam
)
{
    PALLOC_sKmAlloc *psKmAlloc = (PALLOC_sKmAlloc *) pvParam;
    IMG_UINT numPages;

    numPages = (psKmAlloc->sAllocInfo.ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;
    SYSMEMU_FreePages(psKmAlloc->hPagesHandle);
    IMG_BIGORSMALL_FREE(numPages * sizeof(IMG_PHYSADDR), psKmAlloc->sAllocInfo.ppaPAddr);

    /* Free this structure */
    IMG_FREE(psKmAlloc);
}


/*!
******************************************************************************

 @Function                PALLOC_Alloc1

******************************************************************************/
IMG_RESULT PALLOC_Alloc1(
    IMG_UINT32                ui32AttachId,
    SYS_eMemAttrib            eMemAttrib,
    SYSBRG_POINTER_ARG(PALLOC_sUmAlloc) psUmAlloc
)
{
    IMG_HANDLE               hDevHandle;
    IMG_UINT32               ui32Result;
    PALLOC_sKmAlloc *        psKmAlloc;
    IMG_HANDLE               hAttachHandle;
    PALLOC_sAttachContext *  psAttachContext;
    IMG_UINT32               ui32PageNo;
    PALLOC_sUmAlloc          sUmAllocCp;
    IMG_UINT32               ui32PageIdx;
    IMG_PHYSADDR *           pPhys;
    SYSMEMU_sPages *         psSysMem;
    SYS_eMemPool             eMemPool;
    SYSDEVU_sInfo *          psSysDev;
    /* the following code assumes that IMG_PHYSADDR and IMG_UINT64 are the same size */

#ifndef SYSBRG_BRIDGING
    IMG_VOID *               pvKmAddr;
#endif

    ui32Result = SYSOSKM_CopyFromUser(&sUmAllocCp, psUmAlloc, sizeof(sUmAllocCp));
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    IMG_ASSERT(!sUmAllocCp.bMappingOnly);

    /* Get the attachment handle from its ID...*/
    ui32Result = DMANKM_GetAttachHandleFromId(ui32AttachId, &hAttachHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Get access to the attachment specific data...*/
    psAttachContext = DMANKM_GetCompAttachmentData(hAttachHandle);
    IMG_ASSERT(IMG_NULL != psAttachContext);
    if (IMG_NULL == psAttachContext)
    {
        return IMG_ERROR_FATAL;
    }

    /* Get access to the device handle...*/
    hDevHandle = DMANKM_GetDevHandleFromAttach(hAttachHandle);
    IMG_ASSERT(IMG_NULL != hDevHandle);
    if (IMG_NULL == hDevHandle)
    {
        return IMG_ERROR_FATAL;
    }

    /* Lock the device...*/
    DMANKM_LockDeviceContext(hDevHandle);

    psSysDev = psAttachContext->hSysDevHandle;
    IMG_ASSERT(psSysDev != IMG_NULL);
    if (psSysDev == IMG_NULL)
    {
        ui32Result = IMG_ERROR_DEVICE_NOT_FOUND;
        goto error_sys_dev_handle;
    }

    eMemPool = (eMemAttrib & SYS_MEMATTRIB_SECURE) ? psSysDev->secureMemPool : psSysDev->sMemPool;

    /* Allocate allocation info...*/
    psKmAlloc = IMG_MALLOC(sizeof(*psKmAlloc));
    IMG_ASSERT(psKmAlloc != IMG_NULL);
    if (psKmAlloc == IMG_NULL)
    {
        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto error_alloc_info;
    }
    IMG_MEMSET(psKmAlloc, 0, sizeof(*psKmAlloc));

    /* Save device handle etc...*/
    psKmAlloc->hDevHandle          = hDevHandle;
    psKmAlloc->sAllocInfo.ui32Size = sUmAllocCp.ui32Size;
    psKmAlloc->hBufHandle          = NULL;

    /* Allocate pages...*/
    ui32Result = SYSMEMU_AllocatePages(sUmAllocCp.ui32Size, eMemAttrib, eMemPool,
                                       (IMG_HANDLE)&psKmAlloc->hPagesHandle, &pPhys);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_alloc_pages;
    }

#ifndef SYSBRG_BRIDGING
    SYSMEMU_GetCpuKmAddr(&pvKmAddr, psKmAlloc->hPagesHandle);
    IMG_ASSERT(pvKmAddr != IMG_NULL);
    if(pvKmAddr == IMG_NULL)
    {
        ui32Result = IMG_ERROR_FATAL;
        goto error_cpu_km_addr;
    }
#endif

    /* Return addresses...*/
    psSysMem = psKmAlloc->hPagesHandle;

    /* Check if contiguous...*/
    psKmAlloc->sAllocInfo.bIsContiguous = SYSMEMKM_IsContiguous(psKmAlloc->hPagesHandle);

    /* Get the device id...*/
    ui32Result = DMANKM_GetDeviceId(hDevHandle, &sUmAllocCp.ui32DeviceId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_get_dev_id;
    }

    sUmAllocCp.ui64Offset = 0;
    if (psSysMem->hRegHandle)
    {
        // Determine the offset to memory if it has been made mappable in UM.
        sUmAllocCp.ui64Offset = pPhys[0];
    }

    /* Calculate the size of the allocation in pages...*/
    ui32PageNo = (sUmAllocCp.ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;
    psKmAlloc->sAllocInfo.ppaPAddr = IMG_BIGORSMALL_ALLOC(sizeof(IMG_PHYSADDR) * ui32PageNo);
    IMG_ASSERT(psKmAlloc->sAllocInfo.ppaPAddr);
    if (IMG_NULL == psKmAlloc->sAllocInfo.ppaPAddr)
    {
        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto error_page_array;
    }
    IMG_MEMSET(psKmAlloc->sAllocInfo.ppaPAddr, 0, sizeof(IMG_PHYSADDR) * ui32PageNo);

    for (ui32PageIdx = 0; ui32PageIdx < ui32PageNo; ++ui32PageIdx)
    {
        psKmAlloc->sAllocInfo.ppaPAddr[ui32PageIdx] = pPhys[ui32PageIdx];
    }

    /* Register this with the resource manager...*/
    ui32Result = RMAN_RegisterResource(psAttachContext->hResBHandle, PALLOC_RES_TYPE_1,
                                       palloc_fnFree, psKmAlloc, IMG_NULL, &sUmAllocCp.ui32AllocId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_resource_register;
    }

    /* Unlock the device...*/
    DMANKM_UnlockDeviceContext(hDevHandle);

    /* Copy to user changed PALLOC_sUmAlloc, including physical device addresses */
    ui32Result = SYSOSKM_CopyToUser(psUmAlloc, &sUmAllocCp, sizeof(sUmAllocCp));
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_copy_to_user;
    }
    ui32Result = SYSOSKM_CopyToUser(sUmAllocCp.ppaDevPAddr, psKmAlloc->sAllocInfo.ppaPAddr,
                                    sizeof(*psKmAlloc->sAllocInfo.ppaPAddr) * ui32PageNo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_copy_to_user;
    }

    /* Return. */
    return IMG_SUCCESS;

    /* Error handling. */
error_copy_to_user:
    /* Free everything. */
    PALLOC_Free1(sUmAllocCp.ui32AllocId);
    goto error_return;

error_resource_register:
    IMG_BIGORSMALL_FREE(sizeof(IMG_PHYSADDR) * ui32PageNo,
                        psKmAlloc->sAllocInfo.ppaPAddr);
error_page_array:
error_get_dev_id:
#ifndef SYSBRG_BRIDGING
error_cpu_km_addr:
#endif /* SYSBRG_BRIDGING */
    SYSMEMU_FreePages(psKmAlloc->hPagesHandle);
error_alloc_pages:
    IMG_FREE(psKmAlloc);
error_alloc_info:
error_sys_dev_handle:
    /* Unlock the device. */
    DMANKM_UnlockDeviceContext(hDevHandle);

error_return:
    return ui32Result;
}


/*!
******************************************************************************

 @Function              PALLOC_Import1

******************************************************************************/
IMG_RESULT PALLOC_Import1(
    IMG_UINT32                ui32AttachId,
    PALLOC_eImportBufType	  bufType,
    SYS_eMemAttrib            eMemAttrib,
    IMG_INT32                 buff_fd,
    SYSBRG_POINTER_ARG(PALLOC_sUmAlloc) psUmAlloc
)
{
    IMG_HANDLE               hDevHandle;
    IMG_UINT32               ui32Result;
    PALLOC_sKmAlloc *        psKmAlloc;
    IMG_HANDLE               hAttachHandle;
    PALLOC_sAttachContext *  psAttachContext;
    IMG_UINT32               ui32PageNo;
    IMG_UINT32               ui32PageIdx;
    PALLOC_sUmAlloc          sUmAllocCp;
    IMG_PHYSADDR *           ppaDevAddrs;
    SYSDEVU_sInfo *          psSysDev;
    SYS_eMemPool             eMemPool;

    DEBUG_REPORT(REPORT_MODULE_PALLOC, "PALLOC_Import1 fd %d", buff_fd);

    IMG_ASSERT(bufType < PALLOC_BUFTYPE_MAX);
    if (bufType >= PALLOC_BUFTYPE_MAX)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    ui32Result = SYSOSKM_CopyFromUser(&sUmAllocCp, psUmAlloc, sizeof sUmAllocCp);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    IMG_ASSERT(sUmAllocCp.bMappingOnly);

    /* Get the attachment handle from its ID... */
    ui32Result = DMANKM_GetAttachHandleFromId(ui32AttachId, &hAttachHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Get access to the attachment specific data...*/
    psAttachContext = DMANKM_GetCompAttachmentData(hAttachHandle);
    IMG_ASSERT(IMG_NULL != psAttachContext);
    if (IMG_NULL == psAttachContext)
    {
        return IMG_ERROR_FATAL;
    }

    /* Get access to the device handle...*/
    hDevHandle = DMANKM_GetDevHandleFromAttach(hAttachHandle);
    IMG_ASSERT(IMG_NULL != hDevHandle);
    if (IMG_NULL == hDevHandle)
    {
        return IMG_ERROR_FATAL;
    }

    /* Lock the device...*/
    DMANKM_LockDeviceContext(hDevHandle);

    psSysDev = psAttachContext->hSysDevHandle;
    IMG_ASSERT(psSysDev != IMG_NULL); // I
    if (psSysDev == IMG_NULL)
    {
        ui32Result = IMG_ERROR_DEVICE_NOT_FOUND;
        goto error_sys_dev_handle;
    }

    eMemPool = (eMemAttrib & SYS_MEMATTRIB_SECURE) ? psSysDev->secureMemPool : psSysDev->sMemPool;

    /* Allocate allocation info...*/
    psKmAlloc = IMG_MALLOC(sizeof *psKmAlloc);
    IMG_ASSERT(psKmAlloc != IMG_NULL);
    if (psKmAlloc == IMG_NULL)
    {
        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto error_alloc_info;
    }
    IMG_MEMSET(psKmAlloc, 0, sizeof *psKmAlloc);

    /* Save device handle etc... */
    psKmAlloc->hDevHandle = hDevHandle;
    psKmAlloc->sAllocInfo.ui32Size = sUmAllocCp.ui32Size;
    psKmAlloc->sAllocInfo.bIsContiguous = IMG_FALSE;

    /* Get the device id...*/
    ui32Result = DMANKM_GetDeviceId(hDevHandle, &sUmAllocCp.ui32DeviceId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_get_dev_id;
    }

    psKmAlloc->sAllocInfo.bMappingOnly = IMG_TRUE;

    /* Calculate the size of the allocation in pages */
    ui32PageNo = (sUmAllocCp.ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;

    psKmAlloc->sAllocInfo.ppaPAddr = IMG_BIGORSMALL_ALLOC(sizeof(IMG_PHYSADDR) * ui32PageNo);
    IMG_ASSERT(psKmAlloc->sAllocInfo.ppaPAddr);
    if (IMG_NULL == psKmAlloc->sAllocInfo.ppaPAddr)
    {
        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto error_page_array;
    }
    ppaDevAddrs = IMG_BIGORSMALL_ALLOC((sizeof *ppaDevAddrs) * ui32PageNo);
    IMG_ASSERT(ppaDevAddrs);
    if (IMG_NULL == ppaDevAddrs)
    {
        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto error_addr_array;
    }

    /* Import pages */
	sUmAllocCp.eBufType = psKmAlloc->eBufType = bufType;

	IMG_ASSERT(PALLOCKM(bufType));
	if (!PALLOCKM(bufType))
	{
		DEBUG_REPORT(REPORT_MODULE_PALLOC, "Importing bufType (%i) isn't supported by this build.", bufType);
		ui32Result = IMG_ERROR_GENERIC_FAILURE;
		goto error_import_pages;
	}

    psKmAlloc->hPagesHandle = SYSMEMU_ImportPages(PALLOCKM(bufType)->heap_id, psSysDev, sUmAllocCp.ui32Size, eMemAttrib,
                                                  buff_fd, psKmAlloc->sAllocInfo.ppaPAddr,
                                                  SYSBRG_POINTER_FROM_USER(sUmAllocCp.pvCpuUmAddr), IMG_FALSE);
    IMG_ASSERT(psKmAlloc->hPagesHandle != IMG_NULL);
    if (psKmAlloc->hPagesHandle == IMG_NULL)
    {
    	ui32Result = IMG_ERROR_GENERIC_FAILURE;
        goto error_import_pages;
    }

    // Access from user space is not needed for the moment. Can be changed.
    sUmAllocCp.ui64Offset = 0;

    for (ui32PageIdx = 0; ui32PageIdx < ui32PageNo; ++ui32PageIdx)
    {
        IMG_PHYSADDR paCpuPAddr = psKmAlloc->sAllocInfo.ppaPAddr[ui32PageIdx];
        ppaDevAddrs[ui32PageIdx] =
        		SYSDEVU_CpuPAddrToDevPAddr(psAttachContext->hSysDevHandle, paCpuPAddr);
    }

    /* Register this with the resource manager */
    ui32Result = RMAN_RegisterResource(psAttachContext->hResBHandle, PALLOC_RES_TYPE_1,
                                       palloc_fnFree, psKmAlloc, IMG_NULL, &sUmAllocCp.ui32AllocId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_resource_register;
    }

    /* Unlock the device...*/
    DMANKM_UnlockDeviceContext(hDevHandle);

    /* Copy to user changed PALLOC_sUmAlloc, including physical device addresses */
    ui32Result = SYSOSKM_CopyToUser(psUmAlloc, &sUmAllocCp, sizeof sUmAllocCp);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_copy_to_user;
    }
    ui32Result = SYSOSKM_CopyToUser(sUmAllocCp.ppaDevPAddr, ppaDevAddrs,
                                    (sizeof *ppaDevAddrs) * ui32PageNo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_copy_to_user;
    }
    /* Free the address array */
    IMG_BIGORSMALL_FREE((sizeof *ppaDevAddrs) * ui32PageNo, ppaDevAddrs);

    /* Return. */
    return IMG_SUCCESS;

    /* Error handling. */
error_copy_to_user:
    /* Free everything. */
    PALLOC_Free1(sUmAllocCp.ui32AllocId);
    goto error_return;

error_resource_register:
    SYSMEMU_FreePages(psKmAlloc->hPagesHandle);
error_import_pages:
    IMG_BIGORSMALL_FREE((sizeof *ppaDevAddrs) * ui32PageNo, ppaDevAddrs);
error_addr_array:
    IMG_BIGORSMALL_FREE(sizeof(IMG_PHYSADDR) * ui32PageNo, psKmAlloc->sAllocInfo.ppaPAddr);
error_page_array:
error_get_dev_id:
    IMG_FREE(psKmAlloc);
error_alloc_info:
error_sys_dev_handle:
    /* Unlock the device. */
    DMANKM_UnlockDeviceContext(hDevHandle);

error_return:
    return ui32Result;
}


/*!
******************************************************************************

 @Function                PALLOC_Free1

******************************************************************************/
IMG_RESULT PALLOC_Free1(
    IMG_UINT32  ui32AllocId
)
{
    IMG_UINT32         ui32Result;
    PALLOC_sKmAlloc *  psKmAlloc;
    IMG_HANDLE         hResHandle;
    IMG_HANDLE         hDevHandle;

    /* Get the resource info from the id...*/
    ui32Result = RMAN_GetResource(ui32AllocId, PALLOC_RES_TYPE_1, (IMG_VOID **)&psKmAlloc, &hResHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    hDevHandle = psKmAlloc->hDevHandle;
    IMG_ASSERT(IMG_NULL != hDevHandle);
    if (IMG_NULL == hDevHandle)
    {
        return IMG_ERROR_FATAL;
    }

    /* Lock the device...*/
    DMANKM_LockDeviceContext(hDevHandle);

    /* Free through the resource manager...*/
    RMAN_FreeResource(hResHandle);

    /* Unlock the device...*/
    DMANKM_UnlockDeviceContext(hDevHandle);

    /* Return IMG_SUCCESS...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                PALLOCKM_GetAllocInfo

******************************************************************************/
IMG_RESULT PALLOCKM_GetAllocInfo(
    IMG_UINT32             ui32AllocId,
    PALLOCKM_sAllocInfo *  psAllocInfo
)
{
    IMG_UINT32         ui32Result;
    PALLOC_sKmAlloc *  psKmAlloc;
    IMG_HANDLE         hResHandle;

    /* Get the resource info from the id...*/
    ui32Result = RMAN_GetResource(ui32AllocId, PALLOC_RES_TYPE_1, (IMG_VOID **)&psKmAlloc, &hResHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Return the allocation info...*/
    *psAllocInfo = psKmAlloc->sAllocInfo;

    /* Return IMG_SUCCESS...*/
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                PALLOCKM_GetPagesHandle

******************************************************************************/
IMG_RESULT PALLOCKM_GetPagesHandle(
    IMG_UINT32   ui32AllocId,
    IMG_HANDLE * pPagesHandle
)
{
    IMG_UINT32         ui32Result;
    PALLOC_sKmAlloc *  psKmAlloc;

    /* Get the resource info from the id...*/
    ui32Result = RMAN_GetResource(ui32AllocId, PALLOC_RES_TYPE_1, (IMG_VOID **)&psKmAlloc, IMG_NULL);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Return the pages handle */
    *pPagesHandle = psKmAlloc->hPagesHandle;

    /* Return IMG_SUCCESS...*/
    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(PALLOCKM_GetPagesHandle)

/*!
******************************************************************************

 @Function                PALLOCKM_CloneAlloc

******************************************************************************/
IMG_RESULT PALLOCKM_CloneAlloc(
    IMG_UINT32    ui32AllocId,
    IMG_HANDLE    hResBHandle,
    IMG_HANDLE *  phResHandle,
    IMG_UINT32 *  pui32AllocId
)
{
    IMG_UINT32  ui32Result;
    IMG_HANDLE  hResHandle;

    /* Get the resource info from the id...*/
    ui32Result = RMAN_GetResource(ui32AllocId, PALLOC_RES_TYPE_1, IMG_NULL, &hResHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Create a cloned reference...*/
    ui32Result = RMAN_CloneResourceHandle(hResHandle, hResBHandle, phResHandle, pui32AllocId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Return IMG_SUCCESS...*/
    return IMG_SUCCESS;
}
