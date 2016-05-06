/*!
 *****************************************************************************
 *
 * @File       vdecdd_mmu.c
 * @Title      VDECDD MMU Functions
 * @Description    This file contains VDECDD MMU functions
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

#include "vdecdd_mmu.h"
#include "talmmu_api.h"
#include "vdecdd_int.h"
#include "report_api.h"
#include "lst.h"

#include "sysmem_utils.h"

#ifndef SYSBRG_BRIDGING
    #include "tal.h"
#endif /* not SYSBRG_BRIDGING */

#define GUARD_BAND  0x1000


/*!
******************************************************************************
 This structure describes an MMU heap.
******************************************************************************/
typedef struct
{
    IMG_CHAR              * pszName;
    MMU_eHeapId             eHeapId;
    TALMMU_eHeapType        eHeapType;
    IMG_UINT32              ui32StartOffset;
    IMG_UINT32              ui32Size;
    IMG_UINT32              ui32TileStride;
    IMG_CHAR              * pszMemSpace;
    IMG_BOOL                bUseGuardBand;
    IMG_BOOL                bImageBuffers;

} MMU_sHeap;


/*!
******************************************************************************
 This array contains names for each MMU type and should be kept
 in step with the MMU types defined in MMU_eMmuType.
******************************************************************************/
IMG_CHAR acMmuTypeNames[][32] =
{
    "None",
    "32-bit MMU",
    "36-bit MMU",
    "40-bit MMU",
};


static const MMU_sHeap asMmuHeaps[MMU_HEAP_MAX] =
{
    { "Image untiled",  MMU_HEAP_IMAGE_BUFFERS_UNTILED, TALMMU_HEAP_PERCONTEXT,         0x10000000, 0x40000000, 0,      "MEMBE",        IMG_TRUE,   IMG_TRUE  },
    { "Image 512",      MMU_HEAP_IMAGE_BUFFERS_512,     TALMMU_HEAP_PERCONTEXT,         0x50000000, 0x10000000, 512,    "MEMBE",        IMG_TRUE,   IMG_TRUE  },
    { "Image 1024",     MMU_HEAP_IMAGE_BUFFERS_1024,    TALMMU_HEAP_PERCONTEXT,         0x60000000, 0x10000000, 1024,   "MEMBE",        IMG_TRUE,   IMG_TRUE  },
    { "Image 2048",     MMU_HEAP_IMAGE_BUFFERS_2048,    TALMMU_HEAP_PERCONTEXT,         0x70000000, 0x10000000, 2048,   "MEMBE",        IMG_TRUE,   IMG_TRUE  },
    { "Image 4096",     MMU_HEAP_IMAGE_BUFFERS_4096,    TALMMU_HEAP_PERCONTEXT,         0x80000000, 0x10000000, 4096,   "MEMBE",        IMG_TRUE,   IMG_TRUE  },
    { "Device",         MMU_HEAP_DEVICE_BUFFERS,        TALMMU_HEAP_SHARED_EXPORTED,    0x90000000, 0x02000000, 0,      "MEM",          IMG_TRUE,  IMG_FALSE },
    { "Bitstream",      MMU_HEAP_BITSTREAM_BUFFERS,     TALMMU_HEAP_PERCONTEXT,         0x92000000, 0x02000000, 0,      "MEMDMAC_02",   IMG_TRUE,  IMG_FALSE },
    { "Stream",         MMU_HEAP_STREAM_BUFFERS,        TALMMU_HEAP_PERCONTEXT,         0x94000000, 0x6C000000, 0,      "MEM",          IMG_TRUE,  IMG_FALSE },
};


static TALMMU_sHeapInfo sHeapInfo =
{
    MMU_HEAP_IMAGE_BUFFERS_UNTILED,  /* Heap ID                     */
    TALMMU_HEAP_PERCONTEXT,          /* Heap type                   */
    TALMMU_HEAPFLAGS_NONE,           /* Heap flags                  */
    "MEMBE",                         /* Memory space name           */
    0,                               /* Start address (virtual)     */
    0,                               /* Size of heap, in bytes      */
    IMG_FALSE,                       /* Is heap tiled? (1 for yes)  */
    0,                               /* Tile size                   */
    0                                /* Tiled region number         */
};


/*!
******************************************************************************
 This structure contains the device context.
 @brief  VDECDD MMU Device Context
 ******************************************************************************/
typedef struct
{
    IMG_HANDLE                      hDevMemTemplate;        /*!< Handle for MMU template.               */
    IMG_HANDLE                      hDevMemContext;         /*!< Handle for MMU context.                */
    LST_T                           sStrList;               /*!< List of streams.                       */

    VDECDDMMU_pfnDeviceCallback     pfnDeviceCallback;      /*!< Pointer to device callback function.   */
    IMG_VOID                      * pvCallbackParameter;    /*!< Pointer to device callback parameter.  */

    IMG_UINT32                      ui32ContextId;

    IMG_UINT32                      ui32NextContextId;

} MMU_sDevContext;

/*!
******************************************************************************
 This structure contains the stream context.
 @brief  VDECDD MMU Stream Context
 ******************************************************************************/
typedef struct
{
    LST_LINK;           /*!< List link (allows the structure to be part of a MeOS list).  */

    IMG_HANDLE          hDevMemContext;  /*!< Handle for MMU context.     */
    MMU_sDevContext *   psDevContext;    /*!< Pointer to device context.  */
    IMG_UINT32          ui32ContextId;   /*!< MMU context Id.             */

#ifdef SYSBRG_BRIDGING
    IMG_UINT32          ui32PtdPhysAddr;
#else /* not SYSBRG_BRIDGING */
    IMG_HANDLE          hPtdMemSpace;
    IMG_UINT32          ui32IntRegNum;
#endif /* not SYSBRG_BRIDGING */

} MMU_sStrContext;



/*!
******************************************************************************

 @Function              mmu_DevMemContextCreate

******************************************************************************/
static IMG_RESULT mmu_DevMemContextCreate(
    MMU_sDevContext *  psDevContext,
    IMG_HANDLE *       phMmuContext
)
{
    IMG_RESULT           ui32Result;
    IMG_HANDLE           hDevMemHeap;
    TALMMU_uHeapOptions  uHeapOpt1;
    IMG_UINT32           i;

    psDevContext->ui32NextContextId++;

    /* Create a context from the template */
    ui32Result = TALMMU_DevMemContextCreate(psDevContext->hDevMemTemplate, psDevContext->ui32NextContextId, phMmuContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    // Apply options to heaps.
    uHeapOpt1.sGuardBandOpt.ui32GuardBand = GUARD_BAND;

    for (i = 0; i < MMU_HEAP_MAX; i++)
    {
        ui32Result = TALMMU_GetHeapHandle(asMmuHeaps[i].eHeapId, *phMmuContext, &hDevMemHeap);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        if (asMmuHeaps[i].bUseGuardBand &&
            uHeapOpt1.sGuardBandOpt.ui32GuardBand > 0)
        {
            ui32Result = TALMMU_DevMemHeapOptions(hDevMemHeap, TALMMU_HEAP_OPT_ADD_GUARD_BAND, uHeapOpt1);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }

    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function                MMU_GetTiledHeaps

******************************************************************************/
IMG_RESULT MMU_GetTiledHeaps(
    VDEC_eTileScheme        eTileScheme,
    IMG_UINT32            * pui32NumHeaps,
    MMU_sHeapTilingInfo   * pasTilingInfo
)
{
    MMU_eHeapId         eHeapId;
    const IMG_UINT32  * pui32TileStrides;
    IMG_UINT32          ui32NumStrides;
    IMG_UINT32          ui32NumTiledHeaps = 0;

    switch (eTileScheme)
    {
    case VDEC_TS0_256x16:
        pui32TileStrides = aui32Tile256x16RowStride;
        ui32NumStrides = VDEC_ARRAY_SIZE(aui32Tile256x16RowStride);
        break;

    case VDEC_TS1_512x8:
        pui32TileStrides = aui32Tile512x8RowStride;
        ui32NumStrides = VDEC_ARRAY_SIZE(aui32Tile512x8RowStride);
        break;

    default:
        IMG_ASSERT(IMG_FALSE);
        return IMG_ERROR_INVALID_PARAMETERS;
        break;
    }

    // Obtain tiling information for each tiled heap
    for (eHeapId = 0; eHeapId < MMU_HEAP_MAX; eHeapId++)
    {
        if (asMmuHeaps[eHeapId].ui32TileStride)
        {
            IMG_UINT32 i;
            MMU_sHeapTilingInfo * psTilingInfo = &pasTilingInfo[ui32NumTiledHeaps];

            // Determine hardware coded stride value.
            for (i = 0; i < ui32NumStrides; i++)
            {
                if (asMmuHeaps[eHeapId].ui32TileStride == pui32TileStrides[i])
                {
                    break;
                }
            }

            psTilingInfo->ui32HwTileStride = i;
            psTilingInfo->ui32StartOffset = asMmuHeaps[eHeapId].ui32StartOffset;
            psTilingInfo->ui32Size = asMmuHeaps[eHeapId].ui32Size;

            ui32NumTiledHeaps++;
        }
    }

    *pui32NumHeaps = ui32NumTiledHeaps;

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function                MMU_GetHeap

******************************************************************************/
IMG_RESULT MMU_GetHeap(
    VDEC_eTileScheme        eTileScheme,
    IMG_UINT32              ui32ImageStride,
    MMU_eHeapId           * peHeapId

)
{
    IMG_UINT32           i;
    IMG_BOOL             bFound = IMG_FALSE;
    IMG_UINT32           ui32TileStride = ui32ImageStride;

    if (eTileScheme == VDEC_TS_NONE)
    {
        // Tile stride not used when untiling.
        ui32TileStride = 0;
    }

    for (i = 0; i < MMU_HEAP_MAX; i++)
    {
        if (asMmuHeaps[i].bImageBuffers &&
            asMmuHeaps[i].ui32TileStride >= ui32TileStride)
        {
            *peHeapId = asMmuHeaps[i].eHeapId;
            bFound = IMG_TRUE;
            break;
        }
    }

    IMG_ASSERT(bFound);
    if (!bFound)
    {
        REPORT(REPORT_MODULE_MMU, REPORT_ERR,
            "MMU heap not found for image stride [%d]",
            ui32ImageStride);
        return IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE;
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function                mmu_Callback

******************************************************************************/
static IMG_RESULT mmu_Callback(
    TALMMU_eEvent           eEvent,
    IMG_VOID *              pCallbackParameter,
    IMG_UINT32              ui32IntRegIdOrAddr,
    IMG_HANDLE              pvMemSpaceId
)
{
    IMG_RESULT ui32Result;

    switch (eEvent)
    {
        case TALMMU_EVENT_FLUSH_CACHE:
        {
            MMU_sDevContext   * psDevContext = pCallbackParameter;

            ui32Result = psDevContext->pfnDeviceCallback(VDECDDMMU_EVENT_FLUSH_CACHE,
                                                         psDevContext->pvCallbackParameter);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }
        break;

        case TALMMU_EVENT_WRITE_PAGE_DIRECTORY_REF:
        {
            MMU_sStrContext * psStrContext = (IMG_VOID *)pCallbackParameter;

#ifdef SYSBRG_BRIDGING
            // Store the PTD physical address.
            psStrContext->ui32PtdPhysAddr = ui32IntRegIdOrAddr;
#else /* not SYSBRG_BRIDGING */
            // Copy the internal register to another internal register.
            TALINTVAR_RunCommand(
                TAL_PDUMPL_INTREG_MOV,
                pvMemSpaceId,
                psStrContext->ui32IntRegNum,
                pvMemSpaceId,
                ui32IntRegIdOrAddr,
                pvMemSpaceId,
                (IMG_UINT64)ui32IntRegIdOrAddr,
                IMG_TRUE);
            psStrContext->hPtdMemSpace = pvMemSpaceId;
#endif /* not SYSBRG_BRIDGING */
        }
        break;

    default:
        IMG_ASSERT(IMG_FALSE);
        break;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              MMU_DeviceCreate

******************************************************************************/
IMG_RESULT  MMU_DeviceCreate(
    MMU_eMmuType                    eMmuType,
    VDEC_eTileScheme                eTileScheme,
    VDECDDMMU_pfnDeviceCallback     pfnDeviceCallback,
    VXDIO_sMemPool                  sMemPool,
    IMG_VOID                      * pvCallbackParameter,
    IMG_UINT32                      ui32PtdAlignment,
    IMG_HANDLE                    * phMmuDevHandle
)
{
    IMG_RESULT          ui32Result = IMG_SUCCESS;
    IMG_BOOL            bTiling = IMG_TRUE;
    TALMMU_eMMUType     eTalMmuType = TALMMU_MMUTYPE_4K_PAGES_32BIT_ADDR;
    IMG_UINT32          i;
    MMU_sDevContext *   psDevContext;
    TALMMU_sDevMemInfo  sDevMemInfo;

    // Set the TAL MMU type.
    switch (eMmuType)
    {
    case MMU_TYPE_32BIT:
        eTalMmuType = TALMMU_MMUTYPE_4K_PAGES_32BIT_ADDR;
        break;

    case MMU_TYPE_36BIT:
        eTalMmuType = TALMMU_MMUTYPE_4K_PAGES_36BIT_ADDR;
        break;

    case MMU_TYPE_40BIT:
        eTalMmuType = TALMMU_MMUTYPE_4K_PAGES_40BIT_ADDR;
        break;

    default:
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Allocate a device context structure...*/
    VDEC_MALLOC(psDevContext);
    IMG_ASSERT(psDevContext != IMG_NULL);
    if (psDevContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_MMU, REPORT_ERR,
            "Failed to allocate memory for MMU device context");
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psDevContext);

    /* Initialise stream list. */
    LST_init(&psDevContext->sStrList);

    psDevContext->pfnDeviceCallback = pfnDeviceCallback;
    psDevContext->pvCallbackParameter = pvCallbackParameter;

    /* Initialise TALMMU. */
    ui32Result = TALMMU_Initialise();
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_tal_init;
    }

    /* Create an MMU template */
    sDevMemInfo.pszDeviceName = "VDEC";
    sDevMemInfo.ui32DeviceId = 0;
    sDevMemInfo.eMMUType = eTalMmuType;
    sDevMemInfo.eDevFlags = TALMMU_DEVFLAGS_NONE;
    sDevMemInfo.pszPageDirMemSpaceName = "MEM";
    sDevMemInfo.pszPageTableMemSpaceName = IMG_NULL;
    sDevMemInfo.ui32PageSize = DEV_MMU_PAGE_SIZE;
    sDevMemInfo.ui32PageTableDirAlignment = ui32PtdAlignment;
    sDevMemInfo.eMemAttrib = (SYS_MEMATTRIB_UNCACHED | SYS_MEMATTRIB_WRITECOMBINE);
    sDevMemInfo.eMemPool = sMemPool.eMemPoolId;
    sDevMemInfo.eTilingScheme = (eTileScheme == VDEC_TS1_512x8) ? TALMMU_MMUTILING_SCHEME_1 : TALMMU_MMUTILING_SCHEME_0;

    ui32Result = TALMMU_DevMemTemplateCreate(&sDevMemInfo, &psDevContext->hDevMemTemplate);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_tal_template;
    }

    TALMMU_AddCallback(psDevContext->hDevMemTemplate,
                       mmu_Callback,
                       (IMG_PVOID)psDevContext);

    /* Add heaps to template */
    for (i = 0; i < MMU_HEAP_MAX; i++)
    {
        sHeapInfo.ui32HeapId = asMmuHeaps[i].eHeapId;
        sHeapInfo.eHeapType = asMmuHeaps[i].eHeapType;
        sHeapInfo.pszMemSpaceName = asMmuHeaps[i].pszMemSpace;
        sHeapInfo.bTiled = (bTiling && asMmuHeaps[i].ui32TileStride) ? IMG_TRUE : IMG_FALSE;
        sHeapInfo.ui32BaseDevVirtAddr = asMmuHeaps[i].ui32StartOffset;
        sHeapInfo.ui32Size = asMmuHeaps[i].ui32Size;
        sHeapInfo.ui32XTileStride = 0;

        if (asMmuHeaps[i].ui32TileStride)
        {
            IMG_UINT32  ui32HwTileStride;
            IMG_UINT32  ui32Log2HwTileStride = 0;

            ui32HwTileStride = asMmuHeaps[i].ui32TileStride;
            // Calculate HW tile stride. 
            // HW tile stride = log2((tile_stride / tile_width)/ 2)
            ui32HwTileStride >>= 1;
            switch (eTileScheme)
            {
            case VDEC_TS0_256x16:
                ui32HwTileStride >>= 8;
                break;
            case VDEC_TS1_512x8:
                ui32HwTileStride >>= 9;
                break;
            default:
                IMG_ASSERT(0);
                break;
            }

            ui32HwTileStride >>= 1;
            while (ui32HwTileStride)
            {
                ui32HwTileStride >>= 1;
                ui32Log2HwTileStride++;
            }
            // Calculated hardware coded stride value.
            ui32HwTileStride = ui32Log2HwTileStride;

            sHeapInfo.ui32XTileStride = ui32HwTileStride;
        }

        ui32Result = TALMMU_DevMemHeapAdd(psDevContext->hDevMemTemplate, &sHeapInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error_tal_heap;
        }
    }

    /* Create the device context. */
    ui32Result = mmu_DevMemContextCreate(psDevContext, &psDevContext->hDevMemContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_mmu_context;
    }

    psDevContext->ui32ContextId = psDevContext->ui32NextContextId;

    /* Return the device context. */
    *phMmuDevHandle = psDevContext;

    return IMG_SUCCESS;

    /* Roll back in case of errors. */
error_mmu_context:
error_tal_heap:
    TALMMU_DevMemTemplateDestroy(psDevContext->hDevMemTemplate);
error_tal_template:
error_tal_init:
    IMG_FREE(psDevContext);

    return ui32Result;
}



/*!
******************************************************************************

 @Function              MMU_DeviceDestroy

******************************************************************************/
IMG_RESULT  MMU_DeviceDestroy(
    IMG_HANDLE  hMmuDevHandle
)
{
    MMU_sDevContext *  psDevContext = hMmuDevHandle;
    IMG_UINT32         ui32Result;
    MMU_sStrContext *  psStrContext;

    /* Validate inputs. */
    if (hMmuDevHandle == IMG_NULL)
    {
        REPORT(REPORT_MODULE_MMU, REPORT_ERR,
            "Invalid arguments to function: %s",
            __FUNCTION__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Destroy all streams associated with the device. */
    psStrContext = LST_first(&psDevContext->sStrList);
    while (psStrContext != IMG_NULL)
    {
        ui32Result = MMU_StreamDestroy(psStrContext);
         IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        /* See if there are more streams. */
        psStrContext = LST_first(&psDevContext->sStrList);
    }

    /* Destroy the device context */
    ui32Result = TALMMU_DevMemContextDestroy(psDevContext->hDevMemContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Destroy the template. */
    ui32Result = TALMMU_DevMemTemplateDestroy (psDevContext->hDevMemTemplate);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Deinitialise TALMMU. */
    /*** NOTE: We don't deinitiliase TALMMU as this would destroy all contexts        */
    /*** Which could affect other device drivers within the kernel component that    */
    /*** may be using TALMMU.                                                        */
//    ui32Result = TALMMU_Deinitialise();
//    IMG_ASSERT(ui32Result == IMG_SUCCESS);
//    if (ui32Result != IMG_SUCCESS)
//    {
//        return ui32Result;
//    }

    IMG_FREE(psDevContext);

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              mmu_Malloc

******************************************************************************/
static IMG_RESULT mmu_Malloc(
    IMG_HANDLE              hDevMemContext,
    MMU_eHeapId             eHeapId,
    VXDIO_sMemPool          sMemPool,
    IMG_UINT32              ui32Size,
    IMG_UINT32              ui32Alignment,
    VXDIO_sDdBufInfo      * psDdBufInfo
)
{
    IMG_RESULT          ui32Result;
    IMG_HANDLE          hDevMemHeap;
    IMG_VOID          * pvCpuVirtAddr;

    IMG_ASSERT(hDevMemContext != IMG_NULL);
    if(hDevMemContext == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    psDdBufInfo->eMemAttrib = (SYS_eMemAttrib)(SYS_MEMATTRIB_UNCACHED | SYS_MEMATTRIB_WRITECOMBINE);
    psDdBufInfo->eMemPool = sMemPool.eMemPoolId;

    if(sMemPool.eMemPoolType == VXDIO_MEMPOOL_SECURE)
    {
        psDdBufInfo->eMemAttrib |= SYS_MEMATTRIB_SECURE;
    }


    /* Set buffer size. */
    psDdBufInfo->ui32BufSize = ui32Size;

    /* Allocate device memory. */
    /* We always for to be at least page aligned. */
    if ( ui32Alignment >= DEV_MMU_PAGE_SIZE )
    {
        /* Alignment requirement specified by user is larger than page size - make sure alignment	*/
        /* is a multiple of page size.																*/
        IMG_ASSERT ( (ui32Alignment % DEV_MMU_PAGE_SIZE) == 0 );
    }
    else
    {
        /* Alignment requirement specified by user is smaller than page size - make sure page size	*/
        /* is a multiple of alignment.																*/
        if ( ui32Alignment != 0 )
        {
            IMG_ASSERT ( (DEV_MMU_PAGE_SIZE % ui32Alignment) == 0 );
        }

        /* Now round up alignment to one page */
        ui32Alignment = DEV_MMU_PAGE_SIZE;
    }

    /* Round size up to next multiple of physical pages */
    if (( ui32Size % HOST_MMU_PAGE_SIZE ) != 0)
    {
        ui32Size = ((ui32Size / HOST_MMU_PAGE_SIZE) + 1) * HOST_MMU_PAGE_SIZE;
    }

    ui32Result = SYSMEMU_AllocatePages(psDdBufInfo->ui32BufSize,
                                 psDdBufInfo->eMemAttrib, 
                                 psDdBufInfo->eMemPool,
                                 &psDdBufInfo->hMemoryAlloc,
                                 &psDdBufInfo->ppaPhysAddr);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

#ifdef SECURE_MEDIA_SUPPORT
    if (psDdBufInfo->eMemAttrib & SYS_MEMATTRIB_SECURE)
    {
        //Secure Memory needs to be Allocated but not mapped

        // Provide a dummy address to TALMMU just so it doesn't repeat the allocation.
        pvCpuVirtAddr = (IMG_VOID *)DEV_MMU_PAGE_SIZE;

#ifdef __TALMMU_USE_TILE_TEST__
#error "Detile buffer not supported with Secure Device"
#endif
    }
    else
#endif
    {
        //Insecure Memory needs to be Allocated and mapped
        ui32Result = SYSMEMU_GetCpuKmAddr(&psDdBufInfo->pvCpuVirt, psDdBufInfo->hMemoryAlloc);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
		pvCpuVirtAddr = psDdBufInfo->pvCpuVirt;

    }
	IMG_ASSERT(psDdBufInfo->ppaPhysAddr);

    /* Get heap handle.*/
    ui32Result = TALMMU_GetHeapHandle(eHeapId, hDevMemContext, &hDevMemHeap);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Allocate device "virtual" memory. */
    ui32Result = TALMMU_DevMemMapExtMem(hDevMemContext, hDevMemHeap, ui32Size, ui32Alignment, pvCpuVirtAddr, psDdBufInfo->hMemoryAlloc, &psDdBufInfo->hMemory);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        if (ui32Result == IMG_ERROR_OUT_OF_MEMORY)
        {
            REPORT(REPORT_MODULE_MMU, REPORT_ERR,
                "Device Virtual memory allocation failed");
        }

        return ui32Result;
    }

    /* Get the device virtual address. */
    ui32Result = TALMMU_GetDevVirtAddress(psDdBufInfo->hMemory, &psDdBufInfo->ui32DevVirt);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    ///* Get the CPU linear address. */
    //ui32Result = TALMMU_CpuMemMap(psDdBufInfo->hMemory, &psDdBufInfo->pvCpuVirt);
    //IMG_ASSERT(ui32Result == IMG_SUCCESS);
    //if (ui32Result != IMG_SUCCESS)
    //{
    //    return ui32Result;
    //}
#ifndef IMG_KERNEL_MODULE
    {
        TALMMU_sHeapInfo sHeap;
        IMG_HANDLE hFEMemHandle;
        IMG_HANDLE hBEMemHandle;

        TALMMU_GetHeapInfo(hDevMemHeap, &sHeap);

        switch (sHeap.ui32HeapId)
        {
        case MMU_HEAP_IMAGE_BUFFERS_4096:
        case MMU_HEAP_IMAGE_BUFFERS_2048:
        case MMU_HEAP_IMAGE_BUFFERS_1024:
        case MMU_HEAP_IMAGE_BUFFERS_512:
        case MMU_HEAP_IMAGE_BUFFERS_UNTILED:
            {
                IMG_UINT32 i;
                IMG_MEMSET(psDdBufInfo->pvCpuVirt, 0, psDdBufInfo->ui32BufSize);
                TALMMU_CopyHostToDevMem(psDdBufInfo->hMemory);

                hBEMemHandle = TAL_GetMemSpaceHandle(sHeap.pszMemSpaceName);
                
                for(i = 0; i < MMU_HEAP_MAX; i++)
                {
                    if(!asMmuHeaps[i].bImageBuffers)
                    {
                        hFEMemHandle = TAL_GetMemSpaceHandle(asMmuHeaps[i].pszMemSpace);
                        break;
                    }
                }
                // Image buffers are captured in the backend context pdump.
                // Use this lock to make sure that buffers have been allocated
                // when FE will try to submit them.
                TALPDUMP_Unlock(hBEMemHandle, VDEC_BE_FE_PDUMP_SEM);
                TALPDUMP_Lock(hFEMemHandle,VDEC_BE_FE_PDUMP_SEM);
            }
        default:
            break;
        }
    }
#endif   
        
    DEBUG_REPORT(REPORT_MODULE_MMU,
        "MAP (Internal): CPU PYHS [%#llx] VM [0x%p] --> DEV VM [0x%08X - 0x%08X] (%d bytes)",
        psDdBufInfo->ppaPhysAddr[0],
        psDdBufInfo->pvCpuVirt,
        psDdBufInfo->ui32DevVirt,
        psDdBufInfo->ui32DevVirt + ui32Size,
        ui32Size);

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              MMU_DeviceMalloc

******************************************************************************/
IMG_RESULT  MMU_DeviceMalloc(
    IMG_HANDLE              hMmuDevHandle,
    MMU_eHeapId             eHeapId,
    VXDIO_sMemPool          sMemPool,
    IMG_UINT32              ui32Size,
    IMG_UINT32              ui32Alignment,
    VXDIO_sDdBufInfo      * psDdBufInfo
)
{
    MMU_sDevContext *  psDevContext = hMmuDevHandle;
    IMG_UINT32         ui32Result;

    /* Validate inputs. */
    if (hMmuDevHandle == IMG_NULL)
    {
        REPORT(REPORT_MODULE_MMU, REPORT_ERR,
            "Invalid arguments to function: %s",
            __FUNCTION__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Check if device level heap. */
    switch (eHeapId)
    {
    case MMU_HEAP_DEVICE_BUFFERS:
        break;

    case MMU_HEAP_IMAGE_BUFFERS_4096:
    case MMU_HEAP_IMAGE_BUFFERS_2048:
    case MMU_HEAP_IMAGE_BUFFERS_1024:
    case MMU_HEAP_IMAGE_BUFFERS_512:
    case MMU_HEAP_IMAGE_BUFFERS_UNTILED:
    case MMU_HEAP_BITSTREAM_BUFFERS:
	case MMU_HEAP_STREAM_BUFFERS:
    default:
        IMG_ASSERT(IMG_FALSE);
        break;
    }

    /* No streams must be active when we allocate device memory otherwise
        the memory will not be accessible to all streams. */
    IMG_ASSERT(LST_empty(&psDevContext->sStrList));

    /* Allocate device memory. */
    ui32Result = mmu_Malloc(psDevContext->hDevMemContext, eHeapId, sMemPool, ui32Size, ui32Alignment, psDdBufInfo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              MMU_StreamCreate

******************************************************************************/
IMG_RESULT  MMU_StreamCreate(
    IMG_HANDLE    hMmuDevHandle,
    IMG_HANDLE *  phMmuStrHandle
)
{
    MMU_sDevContext *  psDevContext = hMmuDevHandle;
    MMU_sStrContext *  psStrContext;
    IMG_RESULT         ui32Result;

    /* Validate inputs. */
    if (hMmuDevHandle == IMG_NULL)
    {
        REPORT(REPORT_MODULE_MMU, REPORT_ERR,
            "Invalid arguments to function: %s",
            __FUNCTION__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Allocate a stream context structure...*/
    VDEC_MALLOC(psStrContext);
    IMG_ASSERT(psStrContext != IMG_NULL);
    if (psStrContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_MMU, REPORT_ERR,
            "Failed to allocate memory for MMU stream context");
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psStrContext);

    psStrContext->psDevContext = psDevContext;
#ifndef SYSBRG_BRIDGING
    psStrContext->ui32IntRegNum = 32;
#endif /* not SYSBRG_BRIDGING */

    /* Create a stream context. */
    ui32Result = mmu_DevMemContextCreate(psDevContext, &psStrContext->hDevMemContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        IMG_FREE(psStrContext);
        return ui32Result;
    }

    psStrContext->ui32ContextId = psDevContext->ui32NextContextId;

    /* Add stream to list. */
    LST_add(&psDevContext->sStrList, psStrContext);

    *phMmuStrHandle = psStrContext;

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              MMU_StreamDestroy

******************************************************************************/
IMG_RESULT  MMU_StreamDestroy(
    IMG_HANDLE  hMmuStrHandle
)
{
    MMU_sStrContext *  psStrContext = hMmuStrHandle;
    IMG_RESULT         ui32Result;

    /* Validate inputs. */
    if (hMmuStrHandle == IMG_NULL)
    {
        REPORT(REPORT_MODULE_MMU, REPORT_ERR,
            "Invalid arguments to function: %s",
            __FUNCTION__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

#ifndef IMG_KERNEL_MODULE
    {
        IMG_HANDLE hFEMemHandle, hBEMemHandle;
        IMG_UINT32 i;

        for(i = 0; i < MMU_HEAP_MAX; i++)
        {
            if(asMmuHeaps[i].bImageBuffers)
            {
                hBEMemHandle = TAL_GetMemSpaceHandle(asMmuHeaps[i].pszMemSpace);
                break;
            }
        }

        for(i = 0; i < MMU_HEAP_MAX; i++)
        {
            if(!asMmuHeaps[i].bImageBuffers)
            {
                hFEMemHandle = TAL_GetMemSpaceHandle(asMmuHeaps[i].pszMemSpace);
                break;
            }
        }

        // Stream buffers are allocated in the FE pdump ctx
        // Use this lock to make sure that buffers will not be freed
        // before hardware finishes with them.
        TALPDUMP_Unlock(hBEMemHandle, VDEC_BE_FE_PDUMP_SEM);
        TALPDUMP_Lock(hFEMemHandle,VDEC_BE_FE_PDUMP_SEM);
    }
#endif

    /* remove stream to list. */
    LST_remove(&psStrContext->psDevContext->sStrList, psStrContext);

    /* Destroy the device context */
    ui32Result = TALMMU_DevMemContextDestroy(psStrContext->hDevMemContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    IMG_FREE(psStrContext);

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              MMU_StreamMalloc

******************************************************************************/
IMG_RESULT  MMU_StreamMalloc(
    IMG_HANDLE              hMmuStrHandle,
    MMU_eHeapId             eHeapId,
    VXDIO_sMemPool          sMemPool,
    IMG_UINT32              ui32Size,
    IMG_UINT32              ui32Alignment,
    VXDIO_sDdBufInfo      * psDdBufInfo
)
{
    MMU_sStrContext *  psStrContext = hMmuStrHandle;
    IMG_RESULT         ui32Result;

    /* Validate inputs. */
    if (hMmuStrHandle == IMG_NULL)
    {
        REPORT(REPORT_MODULE_MMU, REPORT_ERR,
            "Invalid arguments to function: %s",
            __FUNCTION__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Check if device level heap. */
    switch (eHeapId)
    {
    case MMU_HEAP_IMAGE_BUFFERS_4096:
    case MMU_HEAP_IMAGE_BUFFERS_2048:
    case MMU_HEAP_IMAGE_BUFFERS_1024:
    case MMU_HEAP_IMAGE_BUFFERS_512:
    case MMU_HEAP_IMAGE_BUFFERS_UNTILED:
    case MMU_HEAP_BITSTREAM_BUFFERS:
    case MMU_HEAP_STREAM_BUFFERS:
        break;

    case MMU_HEAP_DEVICE_BUFFERS:
    default:
        IMG_ASSERT(IMG_FALSE);
        break;
    }

    /* Allocate device memory. */
    ui32Result = mmu_Malloc(psStrContext->hDevMemContext, eHeapId, sMemPool, ui32Size, ui32Alignment, psDdBufInfo);
    IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                MMU_StreamMapExt

******************************************************************************/
IMG_RESULT  MMU_StreamMapExt(
    IMG_HANDLE              hMmuStrHandle,
    MMU_eHeapId             eHeapId,
    IMG_UINT32              ui32Size,
    IMG_UINT32              ui32Alignment,
    IMG_VOID              * pvCpuLinearAddr,
    IMG_HANDLE              hExtImportHandle,
    VXDIO_sDdBufInfo      * psDdBufInfo
)
{
    MMU_sStrContext *  psStrContext = hMmuStrHandle;
    IMG_RESULT         ui32Result;
    IMG_HANDLE         hDevMemHeap;
    IMG_VOID         * pvCpuVirtAddr = (IMG_VOID *)DEV_MMU_PAGE_SIZE;

    /* Validate inputs. */
    if (hMmuStrHandle == IMG_NULL)
    {
        REPORT(REPORT_MODULE_MMU, REPORT_ERR,
            "Invalid arguments to function: %s",
            __FUNCTION__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Check if device level heap. */
    switch (eHeapId)
    {
    case MMU_HEAP_IMAGE_BUFFERS_4096:
    case MMU_HEAP_IMAGE_BUFFERS_2048:
    case MMU_HEAP_IMAGE_BUFFERS_1024:
    case MMU_HEAP_IMAGE_BUFFERS_512:
    case MMU_HEAP_IMAGE_BUFFERS_UNTILED:
    case MMU_HEAP_BITSTREAM_BUFFERS:
    case MMU_HEAP_STREAM_BUFFERS:
        break;

    case MMU_HEAP_DEVICE_BUFFERS:
    default:
        IMG_ASSERT(IMG_FALSE);
        break;
    }

    /* Set buffer size. */
    psDdBufInfo->ui32BufSize = ui32Size;

    psDdBufInfo->ppaPhysAddr = ((SYSMEMU_sPages*)hExtImportHandle)->ppaPhysAddr;
	IMG_ASSERT(psDdBufInfo->ppaPhysAddr);

#ifndef SYSBRG_BRIDGING
    ui32Result = SYSMEMU_GetCpuKmAddr(&psDdBufInfo->pvCpuVirt, hExtImportHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    IMG_ASSERT(psDdBufInfo->pvCpuVirt == pvCpuLinearAddr);
    psDdBufInfo->pvCpuVirt = pvCpuLinearAddr;
#endif

    psDdBufInfo->eMemAttrib = ((SYSMEMU_sPages*)hExtImportHandle)->eMemAttrib;

    /* Get heap handle.*/
    ui32Result = TALMMU_GetHeapHandle(eHeapId, psStrContext->hDevMemContext, &hDevMemHeap);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Allocate device "virtual" memory. */
    ui32Result = TALMMU_DevMemMapExtMem(psStrContext->hDevMemContext, hDevMemHeap, ui32Size, ui32Alignment, pvCpuVirtAddr, hExtImportHandle, &psDdBufInfo->hMemory);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        if (ui32Result == IMG_ERROR_OUT_OF_MEMORY)
        {
            REPORT(REPORT_MODULE_MMU, REPORT_ERR,
                   "Device Virtual memory allocation failed");
        }

        return ui32Result;
    }

    /* Get the device virtual address. */
    ui32Result = TALMMU_GetDevVirtAddress(psDdBufInfo->hMemory, &psDdBufInfo->ui32DevVirt);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

#ifndef IMG_KERNEL_MODULE
    {
        TALMMU_sHeapInfo sHeap;
        IMG_HANDLE hFEMemHandle;
        IMG_HANDLE hBEMemHandle;

        TALMMU_GetHeapInfo(hDevMemHeap, &sHeap);

        switch (sHeap.ui32HeapId)
        {
        case MMU_HEAP_IMAGE_BUFFERS_4096:
        case MMU_HEAP_IMAGE_BUFFERS_2048:
        case MMU_HEAP_IMAGE_BUFFERS_1024:
        case MMU_HEAP_IMAGE_BUFFERS_512:
        case MMU_HEAP_IMAGE_BUFFERS_UNTILED:
            {
                IMG_UINT32 i;
                IMG_MEMSET(psDdBufInfo->pvCpuVirt, 0, psDdBufInfo->ui32BufSize);
                TALMMU_CopyHostToDevMem(psDdBufInfo->hMemory);

                hBEMemHandle = TAL_GetMemSpaceHandle(sHeap.pszMemSpaceName);
                
                for(i = 0; i < MMU_HEAP_MAX; i++)
                {
                    if(!asMmuHeaps[i].bImageBuffers)
                    {
                        hFEMemHandle = TAL_GetMemSpaceHandle(asMmuHeaps[i].pszMemSpace);
                        break;
                    }
                }
                // Image buffers are captured in the backend context pdump.
                // Use this lock to make sure that buffers have been allocated
                // when FE will try to submit them.
                TALPDUMP_Unlock(hBEMemHandle, VDEC_BE_FE_PDUMP_SEM);
                TALPDUMP_Lock(hFEMemHandle,VDEC_BE_FE_PDUMP_SEM);
            }
        default:
            break;
        }
    }
#endif 

    DEBUG_REPORT(REPORT_MODULE_MMU,
        "MAP (External): CPU PYHS [%#llx] VM [0x%p] --> DEV VM [0x%08X - 0x%08X] (%d bytes)",
        psDdBufInfo->ppaPhysAddr[0],
        psDdBufInfo->pvCpuVirt,
        psDdBufInfo->ui32DevVirt,
        psDdBufInfo->ui32DevVirt + ui32Size,
        ui32Size);

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                MMU_DeviceWritePtdToMem

******************************************************************************/
IMG_RESULT MMU_DeviceWritePtdToMem(
    IMG_HANDLE           hMmuDevHandle,
    VXDIO_sDdBufInfo   * psPtdBufInfo,
    VXDIO_sPtdInfo     * psPtdInfo
)
{
    MMU_sDevContext *  psDevContext = hMmuDevHandle;
    MMU_sStrContext    sStrContext;

    /* Validate inputs. */
    if (hMmuDevHandle == IMG_NULL)
    {
        REPORT(REPORT_MODULE_MMU, REPORT_ERR,
            "Invalid arguments to function: %s",
            __FUNCTION__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

#ifndef SYSBRG_BRIDGING
    sStrContext.ui32IntRegNum = 30;
#endif /* not SYSBRG_BRIDGING */

    // Set the MMU PTD which will generate event #TALMMU_EVENT_WRITE_PAGE_DIRECTORY_REF
    // and trigger a callback to mmu_Callback with stream context.
    TALMMU_DevMemContextSetMMUPtd(psDevContext->hDevMemContext, &sStrContext);

#ifdef SYSBRG_BRIDGING
    *((IMG_UINT32*)psPtdBufInfo->pvCpuVirt) = sStrContext.ui32PtdPhysAddr;
    psPtdInfo->ui32PtdPhysAddr = sStrContext.ui32PtdPhysAddr;
#else /* not SYSBRG_BRIDGING */
    IMG_ASSERT(psPtdBufInfo->hMemory);
    TALINTVAR_WriteToVirtMem32(psPtdBufInfo->hMemory,
                               (IMG_UINT64)psPtdBufInfo->ui32DevVirt,
                               psDevContext->ui32ContextId,
                               sStrContext.hPtdMemSpace,
                               sStrContext.ui32IntRegNum);
    psPtdInfo->hPtdMemSpace = sStrContext.hPtdMemSpace;
    psPtdInfo->ui32IntRegNum = sStrContext.ui32IntRegNum;
#endif /* not SYSBRG_BRIDGING */

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                MMU_StreamWritePtdToMem

******************************************************************************/
IMG_RESULT MMU_StreamWritePtdToMem(
    IMG_HANDLE              hMmuStrHandle,
    VXDIO_sDdBufInfo      * psBufInfo
)
{
    MMU_sStrContext *  psStrContext = hMmuStrHandle;

    /* Validate inputs. */
    if (hMmuStrHandle == IMG_NULL)
    {
        REPORT(REPORT_MODULE_MMU, REPORT_ERR,
            "Invalid arguments to function: %s",
            __FUNCTION__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    // Set the MMU PTD which will generate event #TALMMU_EVENT_WRITE_PAGE_DIRECTORY_REF
    // and trigger a callback to mmu_Callback with stream context.
    TALMMU_DevMemContextSetMMUPtd(psStrContext->hDevMemContext, psStrContext);

#ifdef SYSBRG_BRIDGING
    *((IMG_UINT32*)psBufInfo->pvCpuVirt) = psStrContext->ui32PtdPhysAddr;
#else /* not SYSBRG_BRIDGING */
    IMG_ASSERT(psBufInfo->hMemory);
    TALINTVAR_WriteToVirtMem32(psBufInfo->hMemory,
                               (IMG_UINT64)psBufInfo->ui32DevVirt,
                               psStrContext->ui32ContextId,
                               psStrContext->hPtdMemSpace,
                               psStrContext->ui32IntRegNum);
#endif /* not SYSBRG_BRIDGING */

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              MMU_FreeMem

******************************************************************************/
IMG_RESULT  MMU_FreeMem(
    VXDIO_sDdBufInfo *  psDdBufInfo
)
{
    IMG_RESULT  ui32Result;

    /* Validate inputs. */
    if (psDdBufInfo == IMG_NULL)
    {
        REPORT(REPORT_MODULE_MMU, REPORT_ERR,
            "Invalid arguments to function: %s",
            __FUNCTION__);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

 
#ifndef IMG_KERNEL_MODULE
    {
        TALMMU_sHeapInfo sHeap;
        IMG_HANDLE hFEMemHandle;
        IMG_HANDLE hBEMemHandle;
        IMG_HANDLE hDevMemCtx, hDevMemHeap;
        IMG_UINT32 ui32HeapId;
        
        TALMMU_GetContextHandle(psDdBufInfo->hMemory, &hDevMemCtx);

        TALMMU_GetDevHeapId(psDdBufInfo->hMemory, &ui32HeapId); 
        TALMMU_GetHeapHandle(ui32HeapId, hDevMemCtx, &hDevMemHeap);

        TALMMU_GetHeapInfo(hDevMemHeap, &sHeap);
        

        switch (sHeap.ui32HeapId)
        {
            case MMU_HEAP_STREAM_BUFFERS:
            case MMU_HEAP_BITSTREAM_BUFFERS:
            case MMU_HEAP_DEVICE_BUFFERS:
            {
                IMG_UINT32 i;

                hFEMemHandle = TAL_GetMemSpaceHandle(sHeap.pszMemSpaceName);

                for(i = 0; i < MMU_HEAP_MAX; i++)
                {
                    if(asMmuHeaps[i].bImageBuffers)
                    {
                        hBEMemHandle = TAL_GetMemSpaceHandle(asMmuHeaps[i].pszMemSpace);
                        break;
                    }
                }
                // Stream buffers are allocated in the FE pdump ctx
                // Use this lock to make sure that buffers will not be freed
                // before hardware finishes with them.
                TALPDUMP_Unlock(hBEMemHandle, VDEC_BE_FE_PDUMP_SEM);
                TALPDUMP_Lock(hFEMemHandle,VDEC_BE_FE_PDUMP_SEM);
            }
        default:
            break;
        }
    }
#endif   

    /* Free the memory. */
    ui32Result = TALMMU_DevMemFree1(psDdBufInfo->hMemory);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    if (psDdBufInfo->hMemoryAlloc != IMG_NULL)
    {
        SYSMEMU_FreePages(psDdBufInfo->hMemoryAlloc);
    }

    return IMG_SUCCESS;
}
