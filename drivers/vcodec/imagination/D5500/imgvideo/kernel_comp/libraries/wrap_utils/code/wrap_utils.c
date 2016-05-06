/*!
 *****************************************************************************
 *
 * @File       wrap_utils.c
 * @Description    This file contains the bridged part TAL Wrapper Utilities - a kernel component
 *  used within the Portablity Framework.
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

#include "wrap_utils.h"
#include "wrap_utils_km.h"
#include "dman_api_km.h"
#include "rman_api.h"
#include "sysos_api_km.h"
#include "sysdev_utils.h"
#include "sysbrg_api_km.h"
#include "target.h"


/*!
******************************************************************************
 This structure contains attachment information.
******************************************************************************/
typedef struct
{
    IMG_HANDLE  hDevHandle;     //<! Device handle
    IMG_HANDLE  hResBHandle;    //<! Resource bucket handle
    SYSDEVU_sInfo *hSysDevHandle;  //<! SYSDEVKN device handle

} WRAPU_sAttachContext;

/*!
******************************************************************************

 @Function                WRAPU_Initialise

******************************************************************************/
IMG_RESULT WRAPU_Initialise(IMG_VOID)
{
    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                WRAPU_Deinitialise

******************************************************************************/
IMG_VOID WRAPU_Deinitialise(IMG_VOID)
{
}


/*!
******************************************************************************

 @Function              wrapu_fnCompConnect

******************************************************************************/
static IMG_RESULT wrapu_fnCompConnect (
    IMG_HANDLE   hAttachHandle,
    IMG_VOID **  ppvCompAttachmentData
)
{
    WRAPU_sAttachContext *  psAttachContext;
    IMG_UINT32              ui32Result;
    IMG_CHAR *              pszDeviceName;

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
        goto error_create_bucket;
    }

    /* Get device information...*/
    psAttachContext->hDevHandle = DMANKM_GetDevHandleFromAttach(hAttachHandle);
    pszDeviceName = DMANKM_GetDeviceName(psAttachContext->hDevHandle);
    ui32Result = SYSDEVU_OpenDevice(pszDeviceName, &psAttachContext->hSysDevHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_open_device;
    }

    /* Return attachment context...*/
    *ppvCompAttachmentData = psAttachContext;

    /* Return success...*/
    return IMG_SUCCESS;

    /* Error handling. */
error_open_device:
    RMAN_DestroyBucket(psAttachContext->hResBHandle);
error_create_bucket:
error_rman_init:
    IMG_FREE(psAttachContext);

    return ui32Result;
}

/*!
******************************************************************************

 @Function              wrapu_fnCompDisconnect

******************************************************************************/
static IMG_RESULT wrapu_fnCompDisconnect (
    IMG_HANDLE  hAttachHandle,
    IMG_VOID *  pvCompAttachmentData
)
{
    WRAPU_sAttachContext *  psAttachContext = pvCompAttachmentData;

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

 @Function              wrapu_fnCompAttach

******************************************************************************/
static IMG_RESULT wrapu_fnCompAttach (
    IMG_HANDLE            hConnHandle,
    DMANKM_sCompAttach *  psCompAttach
)
{
    psCompAttach->pfnCompConnect    = wrapu_fnCompConnect;
    psCompAttach->pfnCompDisconnect = wrapu_fnCompDisconnect;

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                WRAPU_AttachToConnection

******************************************************************************/
IMG_RESULT WRAPU_AttachToConnection(
    IMG_UINT32          ui32ConnId,
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

    /* Lock the device...*/
    DMANKM_LockDeviceContext(hDevHandle);

    /* Call on to the kernel function...*/
    ui32Result = DMANKM_AttachComponent(hConnHandle, "WRAPU", wrapu_fnCompAttach, IMG_NULL, &ui32AttachId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);

    /* Unlock the device...*/
    DMANKM_UnlockDeviceContext(hDevHandle);

    SYSOSKM_CopyToUser(pui32AttachId, &ui32AttachId, sizeof(ui32AttachId));

    /* Return ui32Result...*/
    return ui32Result;
}


/*!
******************************************************************************

 @Function                WRAPU_GetUmMappableAddr

******************************************************************************/
IMG_RESULT WRAPU_GetUmMappableAddr(
    IMG_UINT32           ui32AttachId,
    WRAPU_eRegionId      eRegionId,
    SYSBRG_POINTER_ARG(IMG_UINT64) pui64CpuKmAddr,
    SYSBRG_POINTER_ARG(IMG_UINT32) pui32RegionSize
)
{
    IMG_PHYSADDR paCpuPhysAddr;
    WRAPU_sAttachContext *  psAttachContext;
    IMG_HANDLE              hAttachHandle;
    IMG_UINT32              ui32Result;
    IMG_VOID*               pvCpuKmAddr;
    IMG_UINT32              ui32RegionSize;

    /* Set size of region to 0...*/
    ui32RegionSize = 0;

    /* Get the attachment handle from it's ID...*/
    ui32Result = DMANKM_GetAttachHandleFromId(ui32AttachId, &hAttachHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Get access to the attachment specific data...*/
    psAttachContext = DMANKM_GetCompAttachmentData(hAttachHandle);

    switch (eRegionId)
    {
    case WRAPU_REGID_REGISTERS:
        /* Map the device....*/
        ui32Result = SYSDEVU_GetCpuKmAddr(psAttachContext->hSysDevHandle, (SYSDEVU_eRegionId)eRegionId, &pvCpuKmAddr, &ui32RegionSize);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        ui32Result = SYSDEVU_GetCpuAddrs(
        		psAttachContext->hSysDevHandle,
                (SYSDEVU_eRegionId)eRegionId,
                IMG_NULL, /* km addr */
                &paCpuPhysAddr, /* phys addr */
                IMG_NULL /* size */
        );
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        SYSOSKM_CopyToUser(pui64CpuKmAddr, &paCpuPhysAddr, sizeof(paCpuPhysAddr));
        break;

    case WRAPU_REGID_SLAVE_PORT:
    default:
        IMG_ASSERT(IMG_FALSE);
        return IMG_ERROR_GENERIC_FAILURE;
    }

    SYSOSKM_CopyToUser(pui32RegionSize, &ui32RegionSize, sizeof(ui32RegionSize));

    /* Return success...*/
    return IMG_SUCCESS;
}

