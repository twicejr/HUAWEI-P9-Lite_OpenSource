/*!
 *****************************************************************************
 *
 * @File       tal.c
 * @Description    This file contains a subset of the TAL functions for secure media.
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

#ifdef __linux__

#include "img_types.h"
#include "img_defs.h"
#include "img_errors.h"
#include "system.h"
#include "target.h"
#include "lst.h"
#include "tal.h"

/*!
******************************************************************************
 This structure contains registered device information.
******************************************************************************/
typedef struct
{
    LST_LINK;   /*!< List link (allows the structure to be part of a MeOS list).*/

    IMG_CHAR *  pszDeviceName;      //<! Device name
    IMG_UINT32  ui32DevFlags;       //<! Device flags
    IMG_VOID *  pvRegCpuKmAddr;     //<! Register block address
    IMG_UINT32  ui32RegSize;        //<! Size of register block
    LST_T       sMemSpaceList;      //<! List of memory spaces
    IMG_HANDLE  hSysDevHandle;      //<! SYSDEV handle
    IMG_UINT32  ui32ConnId;         //<! Connection id
    IMG_UINT32  ui32DeviceId;       //<! Device id
    IMG_UINT32  ui32WrapUAttachId;  //<! Attachment id>of sif

} TAL_sDeviceInfo;

/*!
******************************************************************************
 This structure contains registered memory space information.
******************************************************************************/
typedef struct
{
    LST_LINK;            /*!< List link (allows the structure to be part of a MeOS list).*/

    TAL_sDeviceInfo       * psTalDevInfo;           //<! Pointer to the device
    IMG_CHAR              * pszMemSpaceName;        //<! Memory space name flags
    TARGET_eMemSpaceType    eMemSpaceType;          //<! Type of memory space
    IMG_UINT64              ui64BaseOffset;         //<! Base offset
    IMG_UINT64              ui64Size;               //<! Size (in bytes)
    IMG_UINT32            * pui32RegisterSpace;     //<! Pointer to register base

} TAL_sMemSpaceInfo;


static LST_T  gsTalDevList;  //<! List of devices.


#ifdef IMG_KERNEL_MODULE
#include <linux/delay.h>
#include <asm/io.h>
#endif


/*!
******************************************************************************

 @Function              tal_Sleep

******************************************************************************/
static IMG_VOID tal_Sleep(IMG_UINT32 ui32uSec)
{
#ifdef IMG_KERNEL_MODULE
    usleep_range(ui32uSec, ui32uSec);
#else
    //Sleep function
#endif
}


/*!
******************************************************************************

 @Function              tal_fnFree

******************************************************************************/
static IS_NOT_USED IMG_VOID
tal_fnFree(
    IMG_VOID *  pvParam
)
{
    TAL_sDeviceInfo   * psTalDeviceInfo = IMG_NULL;
    TAL_sMemSpaceInfo * psTalMemSpaceInfo = IMG_NULL;

    // Free all registered devices and their associated memory spaces.
    psTalDeviceInfo = LST_removeHead(&gsTalDevList);
    while (psTalDeviceInfo)
    {
        psTalMemSpaceInfo = LST_removeHead(&psTalDeviceInfo->sMemSpaceList);
        while (psTalMemSpaceInfo)
        {
            IMG_FREE(psTalMemSpaceInfo->pszMemSpaceName);
            IMG_FREE(psTalMemSpaceInfo);

            psTalMemSpaceInfo = LST_removeHead(&psTalDeviceInfo->sMemSpaceList);
        }

        IMG_FREE(psTalDeviceInfo->pszDeviceName);
        IMG_FREE(psTalDeviceInfo);

        psTalDeviceInfo = LST_removeHead(&gsTalDevList);
    }
}

/*!
******************************************************************************

 @Function                TAL_MemSpaceRegister

******************************************************************************/
IMG_RESULT
TAL_MemSpaceRegister(
    const TARGET_sMemorySpace      * pTargetMemSpaceInfo
)
{
    TAL_sDeviceInfo   * psTalDeviceInfo = IMG_NULL;
    TAL_sMemSpaceInfo * psTalMemSpaceInfo = IMG_NULL;
    IMG_UINT32          ui32Result;

    // Only register spaces are supported in this version of the TAL.
    // Ignoring all other types.
#if 0
    if (pTargetMemSpaceInfo->eMemorySpaceType != TARGET_MEMSPACE_REGISTER)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }
#endif

    // Ensure that this memory space name has not been registered before.
    // Memory space names must be unique across all devices.
    psTalDeviceInfo = LST_first(&gsTalDevList);
    while (psTalDeviceInfo)
    {
        psTalMemSpaceInfo = LST_first(&psTalDeviceInfo->sMemSpaceList);
        while (psTalMemSpaceInfo)
        {
            if (IMG_STRCMP(psTalMemSpaceInfo->pszMemSpaceName, pTargetMemSpaceInfo->pszMemorySpaceName) == 0)
            {
                psTalMemSpaceInfo = IMG_NULL;
                ui32Result = IMG_ERROR_ALREADY_INITIALISED;
                goto error;
            }

            psTalMemSpaceInfo = LST_next(psTalMemSpaceInfo);
        }

        psTalDeviceInfo = LST_next(psTalDeviceInfo);
    }

    // Find the device associated with the memory space.
    psTalDeviceInfo = LST_first(&gsTalDevList);
    while (psTalDeviceInfo)
    {
        if (IMG_STRCMP(psTalDeviceInfo->pszDeviceName, pTargetMemSpaceInfo->psDevice->pszDeviceName) == 0)
        {
            break;
        }
        psTalDeviceInfo = LST_next(psTalDeviceInfo);
    }

    if (psTalDeviceInfo == IMG_NULL)
    {
        ui32Result = IMG_ERROR_DEVICE_NOT_FOUND;
        goto error;
    }

    // Allocate a memory space structure.
    psTalMemSpaceInfo = IMG_MALLOC(sizeof(*psTalMemSpaceInfo));
    IMG_ASSERT(psTalMemSpaceInfo != IMG_NULL);
    if (psTalMemSpaceInfo == IMG_NULL)
    {
        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto error;
    }
    IMG_MEMSET(psTalMemSpaceInfo, 0, sizeof(*psTalMemSpaceInfo));

    psTalMemSpaceInfo->psTalDevInfo = psTalDeviceInfo;
    psTalMemSpaceInfo->eMemSpaceType = pTargetMemSpaceInfo->eMemorySpaceType;
    psTalMemSpaceInfo->pszMemSpaceName = IMG_STRDUP(pTargetMemSpaceInfo->pszMemorySpaceName);
    IMG_ASSERT(psTalMemSpaceInfo->pszMemSpaceName);
    if (psTalMemSpaceInfo->pszMemSpaceName == IMG_NULL)
    {
        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto error;
    }
    psTalMemSpaceInfo->ui64BaseOffset = pTargetMemSpaceInfo->sRegister.ui64RegBaseAddr;
    psTalMemSpaceInfo->ui64Size = pTargetMemSpaceInfo->sRegister.ui32RegSize;

    psTalMemSpaceInfo->pui32RegisterSpace = (IMG_UINT32 *) ((IMG_CHAR*)psTalDeviceInfo->pvRegCpuKmAddr + psTalMemSpaceInfo->ui64BaseOffset);

    LST_add(&psTalDeviceInfo->sMemSpaceList, psTalMemSpaceInfo);

    return IMG_SUCCESS;

error:
    if (psTalMemSpaceInfo)
    {
        if (psTalMemSpaceInfo->pszMemSpaceName)
        {
            IMG_FREE(psTalMemSpaceInfo->pszMemSpaceName);
            psTalMemSpaceInfo->pszMemSpaceName = IMG_NULL;
        }

        IMG_FREE(psTalMemSpaceInfo);
        psTalMemSpaceInfo = IMG_NULL;
    }

    return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(TAL_MemSpaceRegister);

/*!
******************************************************************************

 @Function                tal_MemSpaceUnRegister

******************************************************************************/
static IMG_RESULT
tal_MemSpaceUnRegister(
    TAL_sMemSpaceInfo * psTalMemSpaceInfo
)
{
    if (psTalMemSpaceInfo->pszMemSpaceName)
    {
        IMG_FREE(psTalMemSpaceInfo->pszMemSpaceName);
        psTalMemSpaceInfo->pszMemSpaceName = IMG_NULL;
    }

    IMG_FREE(psTalMemSpaceInfo);

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                TAL_DeviceRegister

******************************************************************************/
IMG_RESULT
TAL_DeviceRegister(
    const TARGET_sDevice  * psTargetDeviceInfo
)
{
    TAL_sDeviceInfo   * psTalDeviceInfo = IMG_NULL;
    IMG_UINT32          ui32Result;

    // Ensure that this device name has not been registered before.
    psTalDeviceInfo = LST_first(&gsTalDevList);
    while (psTalDeviceInfo)
    {
        if (IMG_STRCMP(psTalDeviceInfo->pszDeviceName, psTargetDeviceInfo->pszDeviceName) == 0)
        {
            return IMG_ERROR_ALREADY_INITIALISED;
        }
        psTalDeviceInfo = LST_next(psTalDeviceInfo);
    }



    // Allocate a device structure.
    psTalDeviceInfo = IMG_MALLOC(sizeof(*psTalDeviceInfo));
    IMG_ASSERT(psTalDeviceInfo != IMG_NULL);
    if (psTalDeviceInfo == IMG_NULL)
    {
        ui32Result = IMG_ERROR_MALLOC_FAILED;
        goto tal_dev_error;
    }
    IMG_MEMSET(psTalDeviceInfo, 0, sizeof(*psTalDeviceInfo));

    psTalDeviceInfo->pszDeviceName = IMG_STRDUP(psTargetDeviceInfo->pszDeviceName);
    IMG_ASSERT(psTalDeviceInfo->pszDeviceName);
    if (psTalDeviceInfo->pszDeviceName == IMG_NULL)
    {
        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto tal_dev_name_error;
    }
    psTalDeviceInfo->ui32DevFlags   = psTargetDeviceInfo->ui32DevFlags;
    psTalDeviceInfo->pvRegCpuKmAddr = psTargetDeviceInfo->pvKmRegBase;
    psTalDeviceInfo->ui32RegSize    = psTargetDeviceInfo->ui32RegSize;

    LST_init(&psTalDeviceInfo->sMemSpaceList);

    LST_add(&gsTalDevList, psTalDeviceInfo);


    return IMG_SUCCESS;

    /* Error handling. */
tal_dev_name_error:
    IMG_FREE(psTalDeviceInfo);
tal_dev_error:
    return ui32Result;
}

IMGVIDEO_EXPORT_SYMBOL(TAL_DeviceRegister)
/*!
******************************************************************************

 @Function                TAL_DeviceUnRegister

******************************************************************************/
IMG_RESULT
TAL_DeviceUnRegister(
    const char * pszDeviceName
)
{
    TAL_sDeviceInfo   * psTalDeviceInfo = IMG_NULL;
    IMG_UINT32          ui32Result;

    // Ensure that this device name has not been registered before.
    psTalDeviceInfo = LST_first(&gsTalDevList);
    while (psTalDeviceInfo)
    {
        if (IMG_STRCMP(psTalDeviceInfo->pszDeviceName, pszDeviceName) == 0)
        {
            TAL_sMemSpaceInfo * psTalMemSpaceInfo;

            LST_remove(&gsTalDevList, psTalDeviceInfo);

            // Free device resource allocations.
            IMG_FREE(psTalDeviceInfo->pszDeviceName);
            psTalDeviceInfo->pszDeviceName = IMG_NULL;

            psTalMemSpaceInfo = LST_removeHead(&psTalDeviceInfo->sMemSpaceList);
            while (psTalMemSpaceInfo)
            {
                ui32Result = tal_MemSpaceUnRegister(psTalMemSpaceInfo);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    goto error;
                }

                psTalMemSpaceInfo = LST_removeHead(&psTalDeviceInfo->sMemSpaceList);
            }

            IMG_FREE(psTalDeviceInfo);
            psTalDeviceInfo = IMG_NULL;
            break;
        }
        psTalDeviceInfo = LST_next(psTalDeviceInfo);
    }



    return IMG_SUCCESS;

error:
    return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(TAL_DeviceUnRegister)

/*!
******************************************************************************

 @Function                TAL_GetMemSpaceHandle

******************************************************************************/
IMG_HANDLE
TAL_GetMemSpaceHandle (
    const IMG_CHAR *  psMemSpaceName
)
{
    TAL_sDeviceInfo   * psTalDeviceInfo = IMG_NULL;
    TAL_sMemSpaceInfo * psTalMemSpaceInfo = IMG_NULL;

    if (psMemSpaceName == IMG_NULL)
    {
        goto error;
    }

    // Find the memory space associated with the name.
    // The registration function ensures unique memory space names
    // across all registered devices.
    psTalDeviceInfo = LST_first(&gsTalDevList);
    while (psTalDeviceInfo)
    {
        psTalMemSpaceInfo = LST_first(&psTalDeviceInfo->sMemSpaceList);
        while (psTalMemSpaceInfo)
        {
            if (IMG_STRCMP(psTalMemSpaceInfo->pszMemSpaceName, psMemSpaceName) == 0)
            {
                goto out;
            }

            psTalMemSpaceInfo = LST_next(psTalMemSpaceInfo);
        }

        psTalDeviceInfo = LST_next(psTalDeviceInfo);
    }

out:
    return (IMG_HANDLE)psTalMemSpaceInfo;
error:
    return IMG_NULL;

}
IMGVIDEO_EXPORT_SYMBOL(TAL_GetMemSpaceHandle)

/*!
******************************************************************************

 @Function              TALREG_WriteWord32

******************************************************************************/
IMG_RESULT
TALREG_WriteWord32(
    IMG_HANDLE  hMemSpace,
    IMG_UINT32  ui32Offset,
    IMG_UINT32  ui32Value
)
{
    TAL_sMemSpaceInfo * psTalMemSpaceInfo = hMemSpace;

    IMG_ASSERT((ui32Offset & 0x3) == 0);

    /* Check memory space ID is valid...*/
    IMG_ASSERT(hMemSpace);
    if (hMemSpace == IMG_NULL)
    {
        return IMG_ERROR_INVALID_ID;
    }

    IMG_ASSERT(psTalMemSpaceInfo->eMemSpaceType == TARGET_MEMSPACE_REGISTER);
    IMG_ASSERT(psTalMemSpaceInfo->pui32RegisterSpace != IMG_NULL);
    if (psTalMemSpaceInfo->pui32RegisterSpace == IMG_NULL)
        return IMG_ERROR_GENERIC_FAILURE;

    // Write register.
#ifdef IMG_KERNEL_MODULE
    iowrite32(ui32Value, (void __iomem *) &psTalMemSpaceInfo->pui32RegisterSpace[ui32Offset>>2]);
#else
    *(volatile IMG_UINT32 *) &psTalMemSpaceInfo->pui32RegisterSpace[ui32Offset>>2] = ui32Value;
#endif

    /* Return success...*/
    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(TALREG_WriteWord32)

/*!
******************************************************************************

 @Function              TALREG_ReadWord32

******************************************************************************/
IMG_RESULT
TALREG_ReadWord32(
    IMG_HANDLE    hMemSpace,
    IMG_UINT32    ui32Offset,
    IMG_UINT32 *  pui32Value
)
{
    TAL_sMemSpaceInfo * psTalMemSpaceInfo = hMemSpace;

    IMG_ASSERT((ui32Offset & 0x3) == 0);

    // Check memory space is valid...
    IMG_ASSERT(hMemSpace);
    if (hMemSpace == IMG_NULL)
    {
        return IMG_ERROR_INVALID_ID;
    }

    IMG_ASSERT(psTalMemSpaceInfo->eMemSpaceType == TARGET_MEMSPACE_REGISTER);
    IMG_ASSERT(psTalMemSpaceInfo->pui32RegisterSpace != IMG_NULL);
    if (psTalMemSpaceInfo->pui32RegisterSpace == IMG_NULL)
        return IMG_ERROR_GENERIC_FAILURE;

    // Read register.
#ifdef IMG_KERNEL_MODULE
    *pui32Value = ioread32((void __iomem *) &psTalMemSpaceInfo->pui32RegisterSpace[ui32Offset>>2]);
#else
    *pui32Value = *(volatile IMG_UINT32 *) &psTalMemSpaceInfo->pui32RegisterSpace[ui32Offset>>2];
#endif

    /* Return success...*/
    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(TALREG_ReadWord32)

typedef IMG_BOOL ( * TAL_pfnCheckFunc) (
    IMG_UINT64                        ui64ReadValue,                //!< The value read from memory / register
    IMG_UINT64                        ui64TestVal_WrOff,            //!< Either the test value or the write offset
    IMG_UINT64                        ui64Enable_PackSize,        //!< Either the enable mask or the packet size
    IMG_UINT64                        ui64BufSize                    //!< The buffer size (not required for comparison operations)
);

#define TAL_CHECKFUNC_MASK        (0x0000FFFF)

/*!
******************************************************************************

 @Function                TALREG_Poll32

******************************************************************************/
IMG_RESULT
TALREG_Poll32(
    IMG_HANDLE  hMemSpace,
    IMG_UINT32  ui32Offset,
    IMG_UINT32  ui32CheckFuncIdExt,
    IMG_UINT32  ui32RequValue,
    IMG_UINT32  ui32Enable,
    IMG_UINT32  ui32PollCount,
    IMG_UINT32  ui32TimeOut
)
{
    IMG_UINT32  ui32Count, ui32ReadVal;
    IMG_UINT32  ui32Result = IMG_SUCCESS;

    if (ui32CheckFuncIdExt != TAL_CHECKFUNC_ISEQUAL && ui32CheckFuncIdExt != TAL_CHECKFUNC_GREATEREQ)
    {
        IMG_ASSERT(0);
        return IMG_ERROR_GENERIC_FAILURE;
    }

    // Add high-frequency poll loops.
    ui32PollCount += 10;

    // High-frequency loop (designed for shorter hardware latency such as reset).
    for (ui32Count = 0; ui32Count < ui32PollCount; ui32Count++)
    {
        /* Read from the device */
        ui32Result = TALREG_ReadWord32(hMemSpace, ui32Offset, &ui32ReadVal);
        if (IMG_SUCCESS != ui32Result)
        {
            break;
        }

        ui32ReadVal = (ui32ReadVal & ui32Enable);

        if (ui32CheckFuncIdExt == TAL_CHECKFUNC_ISEQUAL)
        {
        	if(ui32ReadVal == ui32RequValue)
        	{
        		ui32Result = IMG_SUCCESS;
				break;
        	}
        } 
        else 
        {
        	if(ui32ReadVal >= ui32RequValue)
        	{
        		ui32Result = IMG_SUCCESS;
				break;
        	}
        }

        // Sleep to wait for hardware.
        // Period is selected to allow for high-frequency polling (5us, e.g. reset)
        // over the first 10 iterations, then reverting to 
        // a lower-frequency (100us, e.g. DMA) for the remainder.
        if (ui32Count < 10)
        {
            tal_Sleep(5);
        }
        else
        {
            tal_Sleep(100);
        }
    }

    if ((IMG_SUCCESS != ui32Result) || (ui32Count >= ui32PollCount))
    {
        ui32Result = IMG_ERROR_TIMEOUT;
    }

    return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(TALREG_Poll32)


IMG_RESULT TAL_Wait(
   IMG_HANDLE						hMemSpace,
	IMG_UINT32						ui32Time
)
{
	// Time in mellisecond
#if defined (IMG_KERNEL_MODULE)
	// This may need a general implementation
	mdelay(ui32Time);
	return IMG_SUCCESS;
#else
	IMG_ASSERT(0);
	return IMG_ERROR_FATAL;
#endif
}
IMGVIDEO_EXPORT_SYMBOL(TAL_Wait)

/*!
******************************************************************************

 @Function              TAL_GetMemSpaceOffset

******************************************************************************/
IMG_RESULT TAL_GetMemSpaceOffset(
    IMG_HANDLE   hMemSpace,
    IMG_UINT64 * pui64MemSpaceOffset
)
{
    TAL_sMemSpaceInfo * psTalMemSpaceInfo = hMemSpace;

	if (psTalMemSpaceInfo == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    *pui64MemSpaceOffset = psTalMemSpaceInfo->ui64BaseOffset;

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(TAL_GetMemSpaceOffset)

#endif

