/*!
 *****************************************************************************
 *
 * @File       talmmu_api.c
 * @Description    TAL MMU Extensions.
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

#include "talmmu_api.h"

#if !defined (__TALMMU_NO_TAL__)
    #include "tal.h"
    #include "tal_setup.h"
#endif

#include "system.h"
#include <lst.h>
#include "addr_alloc1.h"
#include "sysmem_utils.h"

#if defined (IMG_KERNEL_MODULE)
#include <linux/module.h>
#endif

#if defined (__TALMMU_USE_PALLOC__)
#include "page_alloc.h"
#endif

#if defined (__TALMMU_USE_SYSAPIS__)
    #include "sysmem_utils.h"
#endif
#if defined (__TALMMU_USE_SYSAPIS__)
    #include "sysdev_utils.h"
#endif

#include "system.h"

#if !defined (__TALMMU_NO_OS__)
    #if defined (__TALMMU_USE_SYSAPIS__) || defined (__TALMMU_USE_PALLOC__)
        #include "sysos_api_km.h"
        #define TALMMU_sIntMask                IMG_UINT32
        #define talmmu_DisableInt()            0; SYSOSKM_DisableInt()
        #define talmmu_EnableInt(sOldIntMask)  talmmu_EnableInt1(sOldIntMask)
static IMG_VOID talmmu_EnableInt1(IMG_UINT32 sOldIntMask)
{
    SYSOSKM_EnableInt();
}
    #else
        #include <krn.h>
        #define TALMMU_sIntMask                KRN_IPL_T
        #define talmmu_DisableInt()            KRN_raiseIPL()
        #define talmmu_EnableInt(sOldIntMask)  talmmu_EnableInt(sOldIntMask)
static IMG_VOID talmmu_EnableInt1(IMG_UINT32 sOldIntMask)
{
    KRN_restoreIPL(sOldIntMask);
}
    #endif
#else
        #define TALMMU_sIntMask                IMG_UINT32
        #define talmmu_DisableInt()            0;
        #define talmmu_EnableInt(sOldIntMask)
#endif

#define TALMMU_FREE(a) if (a != IMG_NULL) IMG_FREE(a)        //<! Macro to free if pointer not IMG_NULL

#define     TALMMU_MAX_DEVICE_HEAPS     (32)    /*!< Max. number of heaps for a device         */
#define     TALMMU_MAX_TEMPLATES        (32)    /*!< Max. number of templates in existence at once    */

#define IS_SET(a,b) ((b & a) != 0)              //!< Used to check if a bit is set.

typedef struct TALMMU_tag_sDevMemHeap TALMMU_sDevMemHeap;

/*!
******************************************************************************
  This structure contains the device memory template information.
******************************************************************************/
typedef struct
{
    LST_T                   sList;                       /*!< List item                                                 */

    TALMMU_sDevMemInfo      sDevMemInfo;                 /*!< Copy of the device info structure                         */
    IMG_HANDLE              hPTDirMemSpace;              /*!< Memory space ID for page table directory allocations      */
    IMG_HANDLE              hPTEntryMemSpace;            /*!< Memory space ID for page table allocations                */
#if defined (__TALMMU_USE_SYSAPIS__)
    SYSDEVU_sInfo *         hSysDevHandle;               /*!< Handle for SYSDEV device                                  */
#endif
    IMG_UINT32              ui32NoHeaps;                 /*!< Number of heaps                                           */
    TALMMU_sDevMemHeap *    pasDevMemHeap[TALMMU_MAX_DEVICE_HEAPS]; /*!< Array of heap pointers                         */
    IMG_UINT32              ui32NoContexts;              /*!< Number of active contexts                                 */
    LST_T                   sDevMemContextList;          /*!< List of device memory context created from this template  */
    IMG_UINT32              ui32PageNoShift;             /*!< Bits to shift right to obtain page number                 */
    IMG_UINT32              ui32ByteInPageMask;          /*!< Mask to extract byte-within-page                          */
    IMG_UINT32              ui32HeapAlignment;           /*!< Heap alignment                                            */
    IMG_UINT32              ui32PageTableEntriesPerPage; /*!< Page table entries/page                                   */
    IMG_UINT32              ui32PageTableNoShift;        /*!< Bits to shift right for page table number                 */
    IMG_UINT32              ui32IndexInPageTableMask;    /*!< Mask to extract index-within-page-table                   */
    IMG_UINT32              ui32PageDirNoShift;          /*!< Bits to shift right to page table directory entry number  */
    IMG_UINT32              ui32TileWidth;               /*!< Tile width (in bytes)                                     */
    IMG_UINT32              ui32TileRowShift;            /*!< Bits to shift to remove tile row offset                   */
    IMG_UINT32              ui32YRowWithinTileShift;     /*!< Bits to shift to Y row within tile                        */
    TALMMU_pfnEventCallback pfnEventCallback;            /*!< Pointer to event callback function                        */
    IMG_VOID *              pCallbackParameter;          /*!< PClient callback data                                     */

} TALMMU_sDevMemTemplate;

/*!
******************************************************************************
  This structure contains the device memory context information.
******************************************************************************/
typedef struct
{
    LST_T                    sList;               //!< List item

    TALMMU_sDevMemTemplate * psDevMemTemplate;    //!< Pointer to device template
    IMG_UINT32               ui32NoHeaps;         //!< Number of heaps
    TALMMU_sDevMemHeap *     pasDevMemHeap[TALMMU_MAX_DEVICE_HEAPS]; //!< Array of heap pointers
    IMG_UINT32               ui32MmuContextId;    //!< The MMU context id used with TAL_MmuSetContext()
    IMG_UINT32 *             pui32PageDir;        //!< Pointer to memory that represents the page table directory

#if !defined (__TALMMU_NO_TAL__)
    IMG_HANDLE               hPageDirTalHandle;   //!< TAL handles for page table directory
#endif

#if defined (__TALMMU_USE_PALLOC__)
    IMG_UINT32               ui32PageDirAllocId;  //!< PALLOC allocation Id
#endif

#if defined (__TALMMU_USE_SYSAPIS__)
    IMG_HANDLE               hSysMemHandlePageDir;//!< SYSMEM handle
#endif

} TALMMU_sDevMemContext;

/*!
******************************************************************************
  This structure contains the page table information.
******************************************************************************/
typedef struct
{
    IMG_UINT32    ui32PageTableRefCount;                 /*!< Page table reference count for page table.            */
    IMG_UINT32 *  pui32PageTable;                        /*!< Pointer to memory that represents the page table.     */
#if !defined (__TALMMU_NO_TAL__)
    IMG_HANDLE    hPageTableTalHandle;                   /*!< TAL handles for page table.                           */
#endif
#if defined (__TALMMU_USE_SYSAPIS__)
    IMG_HANDLE    hPageTableSysMemHandle;                /*!< Handles for memory that represents the page table.    */
#endif
 #if defined (__TALMMU_USE_PALLOC__)
    IMG_UINT32    ui32PageTableAllocId;                  /*!< PALLOC Ids to memory that represents the page table.  */
#endif

#if !defined (__TALMMU_NO_TAL__)
    IMG_HANDLE    ahMemTalHandles[DEV_MMU_PAGE_SIZE/4];  /*!< Array of TAL handles for mapped pages.                */
#endif

} TALMMU_sPageTable;

/*!
******************************************************************************
  This structure contains the device memory heap information.
******************************************************************************/
struct TALMMU_tag_sDevMemHeap
{
    LST_T                    sList;               /*!< List item                                                             */

    TALMMU_sHeapInfo         sHeapInfo;           /*!< Copy of the heap info structure                                       */
    TALMMU_sDevMemTemplate * psDevMemTemplate;    /*!< Pointer to device memory template                                     */
    IMG_BOOL                 bExtDevVirAddr;      /*!< IMG_TRUE if Device virtual offset allocated externally (by the user)  */
    LST_T                    sMemoryList;         /*!< List of memory allocations                                            */
    IMG_HANDLE               hMemSpace;           /*!< Memory space ID for memory allocations                                */
    IMG_HANDLE               hPTMemSpace;         /*!< Memory space ID for Page Table allocations                            */
    ADDR_sContext            sContext;            /*!< Address context structure                                             */
    ADDR_sRegion             sRegions;            /*!< Region structure                                                      */

    IMG_BOOL                 bPageChanges;        /*!< Indicates whether the MMU must be flushed                             */

    IMG_UINT32               ui32NoOfPages;       /*!< No. of pages in this heap                                             */
    IMG_UINT32               ui32NoOfPageTables;  /*!< No. of page tables for this heap                                      */
    TALMMU_sPageTable **     pasPageTable;        /*!< Pointer to an array of page table structures.                         */

    IMG_UINT32               ui32GuardBand;       /*!< Size of heap guard band                                               */
    IMG_UINT32               ui32TiledAlignment;  /*!< Alignment required for Tiled Regions                                  */


#if defined(__TALMMU_USE_PALLOC__) || defined(__TALMMU_USE_SYSAPIS__)
    SYS_eMemAttrib           eMemAttrib;          /*!< Memory attribute                                                      */
    SYS_eMemPool             eMemPool;            /*!< Memory pool                                                           */
#endif

};

/*!
******************************************************************************
  This structure contains the memory allocation information.
******************************************************************************/
typedef struct
{
    LST_T                   sList;                /*!< List item                                                             */

    TALMMU_sDevMemHeap *    psDevMemHeap;         /*!< Heap from which it was allocated                                      */
    TALMMU_sDevMemContext * psDevMemContext;      /*!< Context through which memory was mapped                               */
    IMG_UINT32              ui32Size;             /*!< Size                                                                  */
    IMG_UINT32              ui32Alignment;        /*!< Alignment                                                             */
    IMG_UINT32              ui32DevVirtOffset;    /*!< Device virtual offset of allocation                                   */
    IMG_VOID *              pvCpuNonAlignedAddr;  /*!< CPU non-aligned linear address                                        */
    IMG_VOID *              pvCpuLinearAddr;      /*!< CPU linear address                                                    */
    IMG_BOOL                bMapped;              /*!< IMG_TRUE if memory is mapped                                          */
    IMG_BOOL                bExtDevVirAddr;       /*!< IMG_TRUE if Device virtual offset allocated externally (by the user)  */
    IMG_VOID *              pvDetileBuffer;       /*! Alternate buffer for de-tiling                                         */
    IMG_HANDLE              hExtImportHandle;     /*!< The buffer "external import" handle.                                  */

#if defined (__TALMMU_USE_PALLOC__)
    IMG_UINT32              ui32AllocId;          /*!< PALLOC allocation Id                                                  */
#endif

#if defined (__TALMMU_USE_SYSAPIS__)
    IMG_HANDLE              hSysMemHandle;        /*!< Handle to the block of memory                                         */
#endif

} TALMMU_sMemory;

static  IMG_BOOL gInitialised = IMG_FALSE;

static  LST_T   gsDevMemTemplateList;       /*!< List of device memory templates...*/

#if !defined (__TALMMU_NO_TAL__)
static IMG_RESULT talmmu_ProcessCopy (
    TALMMU_sDevMemHeap *  psDevMemHeap,
    TALMMU_sMemory *      psMemory,
    IMG_UINT32            ui32PageNo,
    IMG_CHAR *            pvPageMemory,
    IMG_CHAR *            pvCpuLinearAddr,
    IMG_UINT32            ui32ByteInPage,
    IMG_UINT32            ui32BytesToProcess,
    IMG_UINT32            ui32BytesProcessed,
    IMG_UINT32            ui32Param,
    IMG_VOID *            pvParam
);
#endif


/*!
******************************************************************************

 @Function                talmmu_NextHighestPowerOfTwo

******************************************************************************/
static IMG_UINT32 talmmu_NextHighestPowerOfTwo (IMG_UINT32 k)
{
    IMG_UINT32    i;

    k--;
    for (i=1; i<sizeof(IMG_UINT32)*8; i=i*2)
    {
        k = k | k >> i;
    }

    return k+1;
}


/*!
******************************************************************************

 @Function                talmmu_WhatPowerOfTwoIsThis

******************************************************************************/
static IMG_UINT32 talmmu_WhatPowerOfTwoIsThis (IMG_UINT32 k)
{
    IMG_UINT32    i=0;

    /* Check that this is a power of two */
    IMG_ASSERT ( (k&(k-1)) == 0 );

    while ( k > 0 )
    {
        i++;
        k = k>>1;
    }

    IMG_ASSERT (i>0);
    return (i-1);
}


/*!
******************************************************************************

 @Function                talmmu_MakePageDirEntryValid

******************************************************************************/
static IMG_UINT32 talmmu_MakePageDirEntryValid(
    TALMMU_sDevMemContext *  psDevMemContext,
    TALMMU_sDevMemHeap *     psDevMemHeap,
    const IMG_UINT32         ui32PageTableNo
)
{
    IMG_UINT32               ui32Result = IMG_SUCCESS;
    IMG_UINT32               ui32PageDirNo;
    TALMMU_sDevMemTemplate * psDevMemTemplate = psDevMemHeap->psDevMemTemplate;
    IMG_UINT32               ui32Bits = 0x00000001;  /* Initially set valid bit...*/
#if defined (__TALMMU_NO_TAL__)
    IMG_PHYSADDR             paAddr;
#endif

    IMG_ASSERT(psDevMemHeap->pasPageTable != IMG_NULL);
    if(psDevMemHeap->pasPageTable == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo] != IMG_NULL);

    ui32PageDirNo = (psDevMemHeap->sHeapInfo.ui32BaseDevVirtAddr>>psDevMemTemplate->ui32PageDirNoShift) + ui32PageTableNo;

    /* Switch on MMU type...*/
    switch (psDevMemTemplate->sDevMemInfo.eMMUType)
    {
    case TALMMU_MMUTYPE_4K_PAGES_32BIT_ADDR:  //!< Support for 4kb pages and 32-bit address range
    case TALMMU_MMUTYPE_4K_PAGES_36BIT_ADDR:  //!< Support for 4kb pages and 36-bit address range
    case TALMMU_MMUTYPE_4K_PAGES_40BIT_ADDR:
#if !defined (__TALMMU_NO_TAL__)
        ui32Result = TALINTVAR_WriteMemRef(psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableTalHandle, 0, psDevMemHeap->hPTMemSpace, 1);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
#else

    #if defined (__TALMMU_USE_SYSAPIS__)
        paAddr = SYSMEMU_CpuKmAddrToCpuPAddr(psDevMemHeap->eMemPool,
                                             psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable);
        paAddr = SYSDEVU_CpuPAddrToDevPAddr(psDevMemHeap->psDevMemTemplate->hSysDevHandle, paAddr);
    #else
        #error Not Supported __TALMMU_NO_TAL__ must be used with __TALMMU_USE_SYSAPIS__
    #endif

#endif

        /* if 36 bit MMU...*/
        if (psDevMemTemplate->sDevMemInfo.eMMUType == TALMMU_MMUTYPE_4K_PAGES_36BIT_ADDR)
        {
            /* Need to shift the address by 4 to fit in 32 bits...*/
#if !defined (__TALMMU_NO_TAL__)
            ui32Result = TALINTVAR_RunCommand(TAL_PDUMPL_INTREG_SHR,
                                              psDevMemHeap->hPTMemSpace,
                                              1,
                                              psDevMemHeap->hPTMemSpace,
                                              1,
                                              psDevMemHeap->hPTMemSpace,
                                              4,
                                              IMG_FALSE);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
#else
            paAddr >>= 4;
#endif
       }

        /* if 40 bit MMU...*/
        if (psDevMemTemplate->sDevMemInfo.eMMUType == TALMMU_MMUTYPE_4K_PAGES_40BIT_ADDR)
        {
            /* Need to shift the address by 8 to fit in 32 bits...*/
#if !defined (__TALMMU_NO_TAL__)
            ui32Result = TALINTVAR_RunCommand(TAL_PDUMPL_INTREG_SHR,
                                              psDevMemHeap->hPTMemSpace,
                                              1,
                                              psDevMemHeap->hPTMemSpace,
                                              1,
                                              psDevMemHeap->hPTMemSpace,
                                              8,
                                              IMG_FALSE);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
#else
            paAddr >>= 8;
#endif
        }

        /* Set valid and any other bits...*/
#if !defined (__TALMMU_NO_TAL__)
        ui32Result = TALINTVAR_RunCommand(TAL_PDUMPL_INTREG_OR,
                                          psDevMemHeap->hPTMemSpace,
                                          1,
                                          psDevMemHeap->hPTMemSpace,
                                          1,
                                          psDevMemHeap->hPTMemSpace,
                                          ui32Bits,
                                          IMG_FALSE);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
#else
        paAddr |= ui32Bits;
#endif

#if !defined (__TALMMU_NO_TAL__)
         ui32Result = TALINTVAR_WriteToMem32(psDevMemContext->hPageDirTalHandle, ui32PageDirNo<<2, psDevMemHeap->hPTMemSpace, 1);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
#else
        IMG_ASSERT((paAddr & 0xFFFFFFFF00000000ull) == 0);
        psDevMemContext->pui32PageDir[ui32PageDirNo] = (IMG_UINT32)paAddr;
#endif
#ifdef __TALMMU_USE_SYSAPIS__
	SYSMEMU_UpdateMemoryRegion(psDevMemContext->hSysMemHandlePageDir, CPU_TO_DEV, ui32PageDirNo * sizeof(psDevMemContext->pui32PageDir[0]), sizeof(psDevMemContext->pui32PageDir[0]));
#endif
        break;

    case TALMMU_MMUTYPE_VAR_PAGES_32BIT_ADDR: //!< Support for variable size pages and 32-bit address range (not yet supported by TALLMMU)
    case TALMMU_MMUTYPE_VP_40BIT:
    default:
        IMG_ASSERT(IMG_FALSE);                 /* Not supported */
        break;
    }

    //Indicate MMU cache must be flushed
    psDevMemHeap->bPageChanges = IMG_TRUE;

    return ui32Result;
}

/*!
******************************************************************************

 @Function                talmmu_MakePageDirEntryInvalid

******************************************************************************/
static IMG_VOID talmmu_MakePageDirEntryInvalid(
    TALMMU_sDevMemContext *  psDevMemContext,
    TALMMU_sDevMemHeap *     psDevMemHeap,
    IMG_UINT32               ui32PageTableNo
)
{
 #if !defined (__TALMMU_NO_TAL__)
    IMG_UINT32                ui32Result;
#endif
    IMG_UINT32                ui32PageDirNo;
    TALMMU_sDevMemTemplate *  psDevMemTemplate = psDevMemHeap->psDevMemTemplate;

    ui32PageDirNo = (psDevMemHeap->sHeapInfo.ui32BaseDevVirtAddr>>psDevMemTemplate->ui32PageDirNoShift) + ui32PageTableNo;
    psDevMemContext->pui32PageDir[ui32PageDirNo] = 0;
#ifdef __TALMMU_USE_SYSAPIS__
    SYSMEMU_UpdateMemoryRegion(psDevMemContext->hSysMemHandlePageDir, CPU_TO_DEV, ui32PageDirNo * sizeof(psDevMemContext->pui32PageDir[0]), sizeof(psDevMemContext->pui32PageDir[0]));
#endif

#if !defined (__TALMMU_NO_TAL__)
    IMG_ASSERT(psDevMemContext->hPageDirTalHandle != IMG_NULL);
    ui32Result = TALMEM_WriteWordDefineContext32(psDevMemContext->hPageDirTalHandle,ui32PageDirNo<<2, 0, psDevMemHeap->hPTMemSpace);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return;
    }
#endif

    //Indicate MMU cache must be flushed
    psDevMemHeap->bPageChanges = IMG_TRUE;
}

/*!
******************************************************************************

 @Function                talmmu_MakePageTableEntryValid

******************************************************************************/
static IMG_RESULT talmmu_MakePageTableEntryValid(
    TALMMU_sDevMemHeap *  psDevMemHeap,
    const IMG_UINT32      ui32PageNo,
    TALMMU_eMapAttrib     eMapAttrib,
    IMG_PHYSADDR          paCpuPhysAddr
)
{
    TALMMU_sDevMemTemplate *  psDevMemTemplate = psDevMemHeap->psDevMemTemplate;
    IMG_UINT32                ui32PageTableNo;
    IMG_UINT32                ui32IndexInPageTable;
    IMG_UINT32                ui32Result = IMG_SUCCESS;
    IMG_UINT32                ui32Bits = 0x00000001;  /* Initially set valid bit...*/
    TALMMU_sIntMask           sOldIntMask;
#if defined (__TALMMU_NO_TAL__)
    IMG_PHYSADDR              paAddr;
#endif

    /* If write only...*/
    if (IS_SET(TALMMU_MAPATTRIB_SET_WRITE_ONLY, eMapAttrib))
    {
        /* Add read only...*/
        ui32Bits |= 0x00000002;
    }

    /* If read only...*/
    if (IS_SET(TALMMU_MAPATTRIB_SET_READ_ONLY, eMapAttrib))
    {
        /* Add read only...*/
        ui32Bits |= 0x00000004;
    }

     /* If cache consistency bit to be set...*/
    if (
            (IS_SET(TALMMU_MAPATTRIB_SET_CACHE_CONSISTENCY, eMapAttrib)) ||
            (IS_SET(TALMMU_HEAPFLAGS_SET_CACHE_CONSISTENCY, psDevMemHeap->sHeapInfo.eHeapFlags))
            )
    {
        /* Add cache consistency...*/
        ui32Bits |= 0x00000008;
    }

    ui32PageTableNo      = ui32PageNo >> psDevMemTemplate->ui32PageTableNoShift;
    ui32IndexInPageTable = ui32PageNo & psDevMemTemplate->ui32IndexInPageTableMask;
    IMG_ASSERT(ui32PageTableNo < psDevMemHeap->ui32NoOfPageTables);
    IMG_ASSERT(ui32IndexInPageTable < psDevMemTemplate->ui32PageTableEntriesPerPage);

    IMG_ASSERT(psDevMemHeap->pasPageTable != IMG_NULL);
    if(psDevMemHeap->pasPageTable == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo] != IMG_NULL);

    /* Disable interrupts */
    sOldIntMask = talmmu_DisableInt();

    /* Switch on MMU type...*/
    switch (psDevMemTemplate->sDevMemInfo.eMMUType)
    {
    case TALMMU_MMUTYPE_4K_PAGES_32BIT_ADDR:  //!< Support for 4kb pages and 32-bit address range
    case TALMMU_MMUTYPE_4K_PAGES_36BIT_ADDR:  //!< Support for 4kb pages and 36-bit address range
    case TALMMU_MMUTYPE_4K_PAGES_40BIT_ADDR:
#if !defined (__TALMMU_NO_TAL__)
        IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable] != IMG_NULL);
        ui32Result = TALINTVAR_WriteMemRef(psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable],
                                           0,
                                           psDevMemHeap->hMemSpace,
                                           2);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto ErrorExit;
        }
#else

    #if defined (__TALMMU_USE_SYSAPIS__)
        paAddr = SYSDEVU_CpuPAddrToDevPAddr(psDevMemHeap->psDevMemTemplate->hSysDevHandle, paCpuPhysAddr);
    #else
        #error Not Supported __TALMMU_NO_TAL__ must be used with __TALMMU_USE_SYSAPIS__
    #endif

#endif

        /* if 36 bit MMU...*/
        if (psDevMemTemplate->sDevMemInfo.eMMUType == TALMMU_MMUTYPE_4K_PAGES_36BIT_ADDR)
        {
            /* Need to shift the address by 4 to fit in 32 bits...*/
#if !defined (__TALMMU_NO_TAL__)
            ui32Result = TALINTVAR_RunCommand(TAL_PDUMPL_INTREG_SHR,
                                              psDevMemHeap->hPTMemSpace,
                                              2,
                                              psDevMemHeap->hPTMemSpace,
                                              2,
                                              psDevMemHeap->hPTMemSpace,
                                              4,
                                              IMG_FALSE);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto ErrorExit;
            }
#else
            paAddr >>= 4;
#endif

        }


        /* if 40 bit MMU...*/
        if (psDevMemTemplate->sDevMemInfo.eMMUType == TALMMU_MMUTYPE_4K_PAGES_40BIT_ADDR)
        {
            /* Need to shift the address by 8 to fit in 32 bits...*/
#if !defined (__TALMMU_NO_TAL__)
            ui32Result = TALINTVAR_RunCommand(TAL_PDUMPL_INTREG_SHR,
                                              psDevMemHeap->hPTMemSpace,
                                              2,
                                              psDevMemHeap->hPTMemSpace,
                                              2,
                                              psDevMemHeap->hPTMemSpace,
                                              8,
                                              IMG_FALSE);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto ErrorExit;
            }
#else
            paAddr >>= 8;
#endif

        }

        /* Set valid and any other bits...*/
#if !defined (__TALMMU_NO_TAL__)
        ui32Result = TALINTVAR_RunCommand(TAL_PDUMPL_INTREG_OR,
                                          psDevMemHeap->hPTMemSpace,
                                          2,
                                          psDevMemHeap->hPTMemSpace,
                                          2,
                                          psDevMemHeap->hPTMemSpace,
                                          ui32Bits,
                                          IMG_FALSE);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto ErrorExit;
        }
#else
        paAddr |= ui32Bits;
#endif

#if !defined (__TALMMU_NO_TAL__)
        ui32Result = TALINTVAR_WriteToMem32(psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableTalHandle,
                                            ui32IndexInPageTable<<2,
                                            psDevMemHeap->hMemSpace,
                                            2);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto ErrorExit;
        }
#else
        IMG_ASSERT((paAddr & 0xFFFFFFFF00000000ull) == 0);
        psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable[ui32IndexInPageTable] = (IMG_UINT32)paAddr;
#endif
#ifdef __TALMMU_USE_SYSAPIS__
        SYSMEMU_UpdateMemoryRegion(psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableSysMemHandle, CPU_TO_DEV,
        		ui32IndexInPageTable * sizeof(psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable), sizeof(psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable[0]));
#endif
        break;

    case TALMMU_MMUTYPE_VAR_PAGES_32BIT_ADDR: //!< Support for variable size pages and 32-bit address range (not yet supported by TALLMMU)
    case TALMMU_MMUTYPE_VP_40BIT:
    default:
        IMG_ASSERT(IMG_FALSE);                 /* Not supported */
        break;
    }

    /* Re-enable interrupts */
#if !defined (__TALMMU_NO_TAL__)
ErrorExit:
#endif
    talmmu_EnableInt(sOldIntMask);

    // Indicate MMU cache must be flushed
    psDevMemHeap->bPageChanges = IMG_TRUE;

    return ui32Result;
}

/*!
******************************************************************************

 @Function                talmmu_MakePageTableEntryInvalid

******************************************************************************/
static IMG_RESULT talmmu_MakePageTableEntryInvalid(
    TALMMU_sDevMemHeap *  psDevMemHeap,
    IMG_UINT32            ui32PageNo
)
{
    TALMMU_sDevMemTemplate *  psDevMemTemplate = psDevMemHeap->psDevMemTemplate;
    IMG_UINT32                ui32PageTableNo;
    IMG_UINT32                ui32IndexInPageTable;
    IMG_UINT32                ui32Result = IMG_SUCCESS;
//#if !defined (__TALMMU_NO_TAL__)
//    IMG_UINT32                ui32Result = IMG_SUCCESS;
//#endif

    ui32PageTableNo      = ui32PageNo >> psDevMemTemplate->ui32PageTableNoShift;
    ui32IndexInPageTable = ui32PageNo & psDevMemTemplate->ui32IndexInPageTableMask;
    IMG_ASSERT(ui32PageTableNo < psDevMemHeap->ui32NoOfPageTables);
    IMG_ASSERT(ui32IndexInPageTable < psDevMemTemplate->ui32PageTableEntriesPerPage);

    IMG_ASSERT(psDevMemHeap->pasPageTable != IMG_NULL);
    if(psDevMemHeap->pasPageTable == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo] != IMG_NULL);

    psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable[ui32IndexInPageTable] = 0;
#ifdef __TALMMU_USE_SYSAPIS__
    SYSMEMU_UpdateMemoryRegion(psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableSysMemHandle, CPU_TO_DEV,
            		ui32IndexInPageTable * sizeof(psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable), sizeof(psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable[0]));
#endif

#if !defined (__TALMMU_NO_TAL__)
    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableTalHandle != IMG_NULL);
    ui32Result = TALMEM_WriteWordDefineContext32(psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableTalHandle,
                                                 ui32IndexInPageTable<<2,
                                                 0,
                                                 psDevMemHeap->hMemSpace);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }
#endif

    //Indicate MMU cache must be flushed
    psDevMemHeap->bPageChanges = IMG_TRUE;

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                talmmu_pfnProcessFunc

******************************************************************************/
typedef IMG_RESULT ( * talmmu_pfnProcessFunc) (
    TALMMU_sDevMemHeap *  psDevMemHeap,
    TALMMU_sMemory *      psMemory,
    IMG_UINT32            ui32PageNo,
    IMG_CHAR *            pvPageMemory,
    IMG_CHAR *            pvCpuLinearAddr,
    IMG_UINT32            ui32ByteInPage,
    IMG_UINT32            ui32BytesToProcess,
    IMG_UINT32            ui32BytesProcessed,
    IMG_UINT32            ui32Param,
    IMG_VOID *            pvParam
);


/*!
******************************************************************************

 @Function                talmmu_ProcessMemoryRegion

******************************************************************************/
static IMG_RESULT talmmu_ProcessMemoryRegion(
    TALMMU_sMemory *       psMemory,
    IMG_UINT32             ui32Offset,
    IMG_UINT32             ui32Size,
    IMG_BOOL               bUseTiling,
    talmmu_pfnProcessFunc  pfnProcessFunc,
    IMG_UINT32             ui32Param,
    IMG_VOID *             pvParam
)
{
    TALMMU_sDevMemHeap *      psDevMemHeap;
    TALMMU_sDevMemTemplate *  psDevMemTemplate;
    IMG_UINT32                ui32PageNo;
    IMG_UINT32                ui32ByteInPage;
    IMG_UINT32                ui32BytesToProcess;
    IMG_CHAR *                pvPageMemory;
    IMG_CHAR *                pvCpuLinearAddr;
    IMG_UINT32                ui32CurOffset;
    IMG_UINT32                ui32DevVirtAddr;
    IMG_UINT32                ui32TileInX;
    IMG_UINT32                ui32YRowWithinTile;
    IMG_UINT32                ui32TopBits;
    IMG_UINT32                ui32BottomBits;
    IMG_UINT32                ui32ProcessStride;
    IMG_BOOL                  bTile;
    IMG_UINT32                ui32Result = IMG_SUCCESS;
    IMG_UINT32                ui32PageTableNo;
//    IMG_UINT32                ui32IndexInPageTable;

    IMG_UINT32                ui32TopBitsMask = 0;
    IMG_UINT32                ui32BottomBitsMask = 0;
    IMG_UINT32                ui32TileInXMask = 0;
    IMG_UINT32                ui32TileInXShift = 0;
    IMG_UINT32                ui32YRowWithinTileMask = 0;
    IMG_ASSERT(gInitialised);
    IMG_ASSERT((ui32Offset+ui32Size) <= psMemory->ui32Size);

    psDevMemHeap     = psMemory->psDevMemHeap;
    psDevMemTemplate = psDevMemHeap->psDevMemTemplate;

    psDevMemHeap->bPageChanges = IMG_FALSE;
    bTile = bUseTiling && psDevMemHeap->sHeapInfo.bTiled;
    /* Loop over the memory region...*/
    ui32CurOffset = ui32Offset;
    /* If tiled...*/
    if (bTile)
    {
        ui32TopBitsMask        = (0xFFFFFFFF << (((psDevMemHeap->sHeapInfo.ui32XTileStride+1)
                                                   + psDevMemTemplate->ui32YRowWithinTileShift)
                                                       + psDevMemTemplate->ui32TileRowShift));
        ui32BottomBitsMask     = (0xFFFFFFFF >> (32 - psDevMemTemplate->ui32TileRowShift));
        ui32TileInXMask        = (0xFFFFFFFF >> (32 - (psDevMemHeap->sHeapInfo.ui32XTileStride+1)));
        ui32TileInXShift       = (psDevMemTemplate->ui32TileRowShift+(psDevMemHeap->sHeapInfo.ui32XTileStride+1));
        ui32YRowWithinTileMask = (0xFFFFFFFF >> (32 - psDevMemTemplate->ui32YRowWithinTileShift));
        ui32ProcessStride      = psDevMemTemplate->ui32TileWidth;
        if (psDevMemHeap->sHeapInfo.eHeapFlags & TALMMU_HEAPFLAGS_128BYTE_INTERLEAVE)
        {
            ui32ProcessStride = 128;
        }
        else if (psDevMemHeap->sHeapInfo.eHeapFlags & TALMMU_HEAPFLAGS_256BYTE_INTERLEAVE)
        {
            ui32ProcessStride = 256;
        }
    }
    else
    {
        ui32ProcessStride = psDevMemTemplate->sDevMemInfo.ui32PageSize;
    }
    while (ui32Size > 0)
    {
        /* Calculate current device virtual address...*/
        ui32DevVirtAddr = psMemory->ui32DevVirtOffset + ui32CurOffset;

        /* If tiled...*/
        if (bTile)
        {
            /* Calculate the tiled virtual address...*/
            ui32TileInX = ui32DevVirtAddr >> psDevMemTemplate->ui32TileRowShift;
            ui32TileInX &= ui32TileInXMask;

            ui32YRowWithinTile = ui32DevVirtAddr >> ui32TileInXShift;
            ui32YRowWithinTile &= ui32YRowWithinTileMask;

            ui32TopBits = ui32DevVirtAddr & ui32TopBitsMask;

            ui32BottomBits = ui32DevVirtAddr & ui32BottomBitsMask;

            ui32DevVirtAddr = ui32TopBits |
                              (ui32TileInX << (psDevMemTemplate->ui32TileRowShift+psDevMemTemplate->ui32YRowWithinTileShift)) |
                              (ui32YRowWithinTile << psDevMemTemplate->ui32TileRowShift) |
                              ui32BottomBits;

            // Check that the tiling hasn't taken the address out of the range for this memory
            IMG_ASSERT(ui32DevVirtAddr >= psMemory->ui32DevVirtOffset);
            IMG_ASSERT(ui32DevVirtAddr < psMemory->ui32DevVirtOffset + psMemory->ui32Size);
            if (psDevMemHeap->sHeapInfo.eHeapFlags & TALMMU_HEAPFLAGS_128BYTE_INTERLEAVE)
            {
                if (ui32DevVirtAddr & 0x100)
                    ui32DevVirtAddr ^= 0x80;
            }
            else if (psDevMemHeap->sHeapInfo.eHeapFlags & TALMMU_HEAPFLAGS_256BYTE_INTERLEAVE)
            {
                ui32DevVirtAddr ^= ((ui32DevVirtAddr & (0x3 << 12)) >> 4); // Mask just 13:12 and XOR with 9:8
            }
        }

        /* From the device virtual address (or tiled virtual address), calculate...*/
        ui32PageNo           = ui32DevVirtAddr >> psDevMemTemplate->ui32PageNoShift;
        ui32PageTableNo      = ui32PageNo >> psDevMemTemplate->ui32PageTableNoShift;
//        ui32IndexInPageTable = ui32PageNo & psDevMemTemplate->ui32IndexInPageTableMask;
        ui32ByteInPage       = ui32DevVirtAddr & psDevMemTemplate->ui32ByteInPageMask;

        IMG_ASSERT(psDevMemHeap->pasPageTable != IMG_NULL);
        if(psDevMemHeap->pasPageTable == IMG_NULL)
        {
            ui32Result = IMG_ERROR_INVALID_PARAMETERS;
            return ui32Result;
        }

        /* If we don't have a page table structure covering this part of the region then create one. */
        if (psDevMemHeap->pasPageTable[ui32PageTableNo] == IMG_NULL)
        {
            psDevMemHeap->pasPageTable[ui32PageTableNo] = IMG_MALLOC(sizeof(*psDevMemHeap->pasPageTable[ui32PageTableNo]));
            IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo] != IMG_NULL);
            if (psDevMemHeap->pasPageTable[ui32PageTableNo] == IMG_NULL)
            {
                return IMG_ERROR_OUT_OF_MEMORY;
            }

            IMG_MEMSET(psDevMemHeap->pasPageTable[ui32PageTableNo], 0, sizeof(*psDevMemHeap->pasPageTable[ui32PageTableNo]));
        }

#ifdef __TALMMU_USE_TILE_TEST__
#ifdef SYSBRG_BRIDGING
        if( (pfnProcessFunc == talmmu_ProcessCopy) && (ui32Param == IMG_FALSE) )
        {
            pvCpuLinearAddr = &((IMG_CHAR *)psMemory->pvDetileBuffer)[ui32CurOffset];
        }
        else
        {
            pvCpuLinearAddr = &((IMG_CHAR *)psMemory->pvCpuLinearAddr)[ui32DevVirtAddr - psMemory->ui32DevVirtOffset];
        }
#else /* not SYSBRG_BRIDGING */
        pvCpuLinearAddr = &((IMG_CHAR *)psMemory->pvCpuLinearAddr)[ui32CurOffset];
#endif /* not SYSBRG_BRIDGING */
#else /* not __TALMMU_USE_TILE_TEST__ */
        pvCpuLinearAddr = &((IMG_CHAR *)psMemory->pvCpuLinearAddr)[ui32DevVirtAddr - psMemory->ui32DevVirtOffset];
#endif /* not __TALMMU_USE_TILE_TEST__ */

        /* Set pointer to the memory representing the page...*/
        pvPageMemory = &((IMG_CHAR*)psMemory->pvCpuLinearAddr)[ui32ByteInPage];

        /* If tiled...*/
        if (bTile)
        {
            /* Calculate size to end of stride...*/
            ui32BytesToProcess = ((ui32ByteInPage & ~(ui32ProcessStride-1)) + ui32ProcessStride) - ui32ByteInPage;
        }
        else
        {
            /* Calculate size to end of page...*/
            ui32BytesToProcess = psDevMemTemplate->sDevMemInfo.ui32PageSize - ui32ByteInPage;
        }

        /* If size remaiing is less than the size to end of page...*/
        if (ui32Size < ui32BytesToProcess)
        {
            /* The size is what is left to process...*/
            ui32BytesToProcess = ui32Size;
        }

        /* Call process function...*/
        ui32Result = pfnProcessFunc(psDevMemHeap, psMemory, ui32PageNo, pvPageMemory,
                                    pvCpuLinearAddr, ui32ByteInPage, ui32BytesToProcess,
                                    ui32CurOffset - ui32Offset, ui32Param, pvParam);

        if (ui32Result == IMG_SUCCESS)
        {
            /* Update loop variables...*/
            ui32Size      -= ui32BytesToProcess;
            ui32CurOffset += ui32BytesToProcess;
        }
        else
        {
            break;
        }
    }

    /* If page changed...*/
    if (psDevMemHeap->bPageChanges)
    {
        /* Flush the MMU cache */
        if (psDevMemTemplate->pfnEventCallback != IMG_NULL)
        {
            psDevMemTemplate->pfnEventCallback(TALMMU_EVENT_FLUSH_CACHE, psDevMemTemplate->pCallbackParameter, 0, psDevMemHeap->hMemSpace);
        }
    }
    return ui32Result;
}

/*!
******************************************************************************

 @Function                talmmu_ProcessMemMap

******************************************************************************/
static IMG_RESULT talmmu_ProcessMemMap (
    TALMMU_sDevMemHeap *  psDevMemHeap,
    TALMMU_sMemory *      psMemory,
    const IMG_UINT32      ui32PageNo,
    IMG_CHAR *            pvPageMemory,
    IMG_CHAR *            pvCpuLinearAddr,
    IMG_UINT32            ui32ByteInPage,
    IMG_UINT32            ui32BytesToProcess,
    IMG_UINT32            ui32BytesProcessed,
    IMG_UINT32            ui32Param,
    IMG_VOID *            pvParam
)
{
    TALMMU_sMemory *          psMem = pvParam;
    TALMMU_sDevMemContext *   psDevMemContext = psMem->psDevMemContext;
    TALMMU_sDevMemTemplate *  psDevMemTemplate;
    IMG_UINT32                ui32PageTableNo;
#if !defined (__TALMMU_NO_TAL__)
    IMG_UINT32                ui32IndexInPageTable;
#endif
    IMG_UINT32                ui32Result = IMG_SUCCESS;
    IMG_VOID *                pvPageCpuLinearAddr;
#if defined (__TALMMU_USE_SYSAPIS__)
    SYSMEMU_sPages *          psSysMem = psMem->hSysMemHandle;
#endif

    psDevMemTemplate = psDevMemHeap->psDevMemTemplate;

    /* Determine the page table entry for this page...*/
    ui32PageTableNo      = ui32PageNo >> psDevMemTemplate->ui32PageTableNoShift;
#if !defined (__TALMMU_NO_TAL__)
    ui32IndexInPageTable = ui32PageNo & psDevMemTemplate->ui32IndexInPageTableMask;
#endif
    IMG_ASSERT(ui32PageTableNo < psDevMemHeap->ui32NoOfPageTables);

    IMG_ASSERT(psDevMemHeap->pasPageTable != IMG_NULL);
    if (psDevMemHeap->pasPageTable == IMG_NULL)
        return IMG_ERROR_INVALID_PARAMETERS;
    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo] != IMG_NULL);

     pvPageCpuLinearAddr = (IMG_VOID*)((IMG_UINTPTR)pvCpuLinearAddr & (~((IMG_UINTPTR)psDevMemTemplate->sDevMemInfo.ui32PageSize -1)));

#if !defined (__TALMMU_NO_TAL__)
    /* Malloc device memory...*/
    if(psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable] == IMG_NULL)
    {
        /* Guard this to make sure we are not trying to allocate memory again and again, which was happening when tiling.
           talmmu_ProcessMemMap is called multiple times from talmmu_ProcessMemoryRegion for the same page which has
           already being allocated memory. */
        ui32Result = TALMEM_Malloc(psDevMemHeap->hMemSpace,
                                   pvPageCpuLinearAddr,
                                   psDevMemTemplate->sDevMemInfo.ui32PageSize,
                                   psDevMemTemplate->sDevMemInfo.ui32PageSize,
                                   &psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable],
                                   IMG_FALSE,
                                   IMG_NULL);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }
#endif

    /* If the page table reference count is not 0...*/
    if (psDevMemHeap->pasPageTable[ui32PageTableNo]->ui32PageTableRefCount != 0)
    {
        /* Has reference, should have memory...*/
        IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable != IMG_NULL);
    }
    else
    {
#if defined (__TALMMU_USE_PALLOC__)
        /* Allocate memory to represent the page table...*/
        IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->ui32PageTableAllocId == IMG_NULL);
        ui32Result = PALLOC_Alloc(psDevMemTemplate->sDevMemInfo.ui32AttachId,
                                  psDevMemTemplate->sDevMemInfo.ui32PageSize,
                                  psDevMemTemplate->sDevMemInfo.eMemAttrib,
                                  psDevMemTemplate->sDevMemInfo.eMemPool,
                                  (IMG_VOID **)&psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable,
                                  &psDevMemHeap->pasPageTable[ui32PageTableNo]->ui32PageTableAllocId);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
#elif defined (__TALMMU_USE_SYSAPIS__)
        {
            ui32Result = SYSMEMU_AllocatePages(psDevMemTemplate->sDevMemInfo.ui32PageSize,
            									psDevMemTemplate->sDevMemInfo.eMemAttrib,
                                               psDevMemTemplate->sDevMemInfo.eMemPool,
                                               &psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableSysMemHandle,
                                               IMG_NULL);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            SYSMEMU_GetCpuKmAddr((IMG_VOID **)&psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable ,
                psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableSysMemHandle);

            IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable != IMG_NULL);
            if (psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable == IMG_NULL)
            {
                return IMG_ERROR_FATAL;
            }

        }
#elif defined (__TALMMU_USE_MALLOC__)
        psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable = IMG_MALLOC(psDevMemTemplate->sDevMemInfo.ui32PageSize);
        IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable != IMG_NULL);
        if (psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable == IMG_NULL)
        {
            return IMG_ERROR_OUT_OF_MEMORY;
        }
#else
    #error "No/wrong TALMMU alloc option defined!"
#endif

        IMG_MEMSET(psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable, 0, psDevMemTemplate->sDevMemInfo.ui32PageSize);

#if !defined (__TALMMU_NO_TAL__)
        /* Should not have a TAL handle...*/
        IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableTalHandle == IMG_NULL);

        /* Malloc device memory... pte*/
        ui32Result = TALMEM_Malloc(psDevMemHeap->hPTMemSpace,
                                   (IMG_CHAR *)psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable,
                                   psDevMemTemplate->sDevMemInfo.ui32PageSize,
                                   psDevMemTemplate->sDevMemInfo.ui32PageSize,
                                   &psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableTalHandle,
                                   IMG_TRUE,
                                   IMG_NULL);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
#endif
        /* Make the page table directory entry valid for this page table...*/
        ui32Result = talmmu_MakePageDirEntryValid(psDevMemContext, psDevMemHeap, ui32PageTableNo);
        IMG_ASSERT( ui32Result==IMG_SUCCESS );
        if (ui32Result != IMG_SUCCESS )
        {
            return ui32Result;
        }
    }

    /* Make the page table entry valid for this page...*/
#if defined (__TALMMU_USE_SYSAPIS__)
    if (psSysMem->ppaPhysAddr) {
        //paPhysAddr contains addresses of host pages, so first get physical adress of it
        //device pages may be smaller than host ones, if so we need to compute offset
        //which is multiple of device page size and index of device page in currennt host page
        IMG_SIZE addrIdx = ui32BytesProcessed / HOST_MMU_PAGE_SIZE;
        IMG_UINT32 ui32DevPageInHostPage = ((ui32BytesProcessed % HOST_MMU_PAGE_SIZE )/ DEV_MMU_PAGE_SIZE);//get bytes processed in current host page, than get index of device page
        talmmu_MakePageTableEntryValid(psDevMemHeap, ui32PageNo, 0,
                                       psSysMem->ppaPhysAddr[addrIdx] + DEV_MMU_PAGE_SIZE * ui32DevPageInHostPage);

    } else
#endif
    {
        talmmu_MakePageTableEntryValid(psDevMemHeap, ui32PageNo, 0,
                                       SYSMEMU_CpuKmAddrToCpuPAddr(psSysMem->memHeap->memId, pvPageCpuLinearAddr));
    }

    /* Update the page table reference count...*/
    psDevMemHeap->pasPageTable[ui32PageTableNo]->ui32PageTableRefCount++;

    return ui32Result;
}

/*!
******************************************************************************

 @Function                talmmu_ProcessMemUnmap

******************************************************************************/
static IMG_RESULT talmmu_ProcessMemUnmap (
    TALMMU_sDevMemHeap *  psDevMemHeap,
    TALMMU_sMemory *      psMemory,
    IMG_UINT32            ui32PageNo,
    IMG_CHAR *            pvPageMemory,
    IMG_CHAR *            pvCpuLinearAddr,
    IMG_UINT32            ui32ByteInPage,
    IMG_UINT32            ui32BytesToProcess,
    IMG_UINT32            ui32BytesProcessed,
    IMG_UINT32            ui32Param,
    IMG_VOID *            pvParam
)
{
    TALMMU_sDevMemContext *   psDevMemContext = pvParam;
    TALMMU_sDevMemTemplate *  psDevMemTemplate;
    IMG_UINT32                ui32PageTableNo;
#if !defined (__TALMMU_NO_TAL__)
    IMG_UINT32                ui32IndexInPageTable;
#endif
    IMG_UINT32                ui32Result;

    psDevMemTemplate = psDevMemHeap->psDevMemTemplate;

    /* Determine the page table entry for this page...*/
    ui32PageTableNo      = ui32PageNo >> psDevMemTemplate->ui32PageTableNoShift;
#if !defined (__TALMMU_NO_TAL__)
    ui32IndexInPageTable = ui32PageNo & psDevMemTemplate->ui32IndexInPageTableMask;
#endif
    IMG_ASSERT(ui32PageTableNo < psDevMemHeap->ui32NoOfPageTables);

    IMG_ASSERT(psDevMemHeap->pasPageTable != IMG_NULL);
    if(psDevMemHeap->pasPageTable == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo] != IMG_NULL);

    /* Should have memory for this page...*/
#if defined (__TALMMU_USE_PALLOC__)
    if(psMemory->ui32AllocId)
#elif defined (__TALMMU_USE_SYSAPIS__)
    if(psMemory->hSysMemHandle)
#else
    if(psMemory->pvCpuLinearAddr != IMG_NULL)
#endif
    {

#if !defined (__TALMMU_NO_TAL__)
        if (psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable] != IMG_NULL)
        {
            /* Free device memory...*/
            IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable] != IMG_NULL);
            ui32Result = TALMEM_Free(&psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable]);
            IMG_ASSERT( ui32Result==IMG_SUCCESS );
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
            IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable] == IMG_NULL);
        }
#endif

        /* Update page table reference count...*/
        psDevMemHeap->pasPageTable[ui32PageTableNo]->ui32PageTableRefCount--;

        /* If the page table reference count is 0...*/
        if (psDevMemHeap->pasPageTable[ui32PageTableNo]->ui32PageTableRefCount == 0)
        {
#if !defined (__TALMMU_NO_TAL__)
            /* Free device memory...*/
            ui32Result = TALMEM_Free(&psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableTalHandle);
            IMG_ASSERT( ui32Result==IMG_SUCCESS );
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
            IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableTalHandle == IMG_NULL);
#endif

            /* Free the memory that represents the page table...*/
            IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable != IMG_NULL);
#if defined (__TALMMU_USE_PALLOC__)
            IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->ui32PageTableAllocId != IMG_NULL);
            PALLOC_Free(psDevMemHeap->pasPageTable[ui32PageTableNo]->ui32PageTableAllocId);
            psDevMemHeap->pasPageTable[ui32PageTableNo]->ui3PageTable2AllocId = IMG_NULL;
#elif defined (__TALMMU_USE_SYSAPIS__)
            IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableSysMemHandle != IMG_NULL);
        SYSMEMU_FreePages(psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableSysMemHandle);
            psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableSysMemHandle = IMG_NULL;
#elif defined (__TALMMU_USE_MALLOC__)
            TALMMU_FREE(psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable);
#else
    #error "No/wrong TALMMU alloc option defined!"
#endif
            psDevMemHeap->pasPageTable[ui32PageTableNo]->pui32PageTable = IMG_NULL;

            /* Invalidate the page table directory entry for the page table...*/
            if (psDevMemContext != IMG_NULL)
            {
                /* Invalidate the page table directory entry for the page table...*/
                talmmu_MakePageDirEntryInvalid(psDevMemContext, psDevMemHeap, ui32PageTableNo);
            }

            /* Free the page table structure for this area. */
            TALMMU_FREE(psDevMemHeap->pasPageTable[ui32PageTableNo]);
            psDevMemHeap->pasPageTable[ui32PageTableNo] = IMG_NULL;
        }
        else
        {
            /* Invalidate the page table entry for the page...*/
            ui32Result = talmmu_MakePageTableEntryInvalid(psDevMemHeap, ui32PageNo);
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

 @Function                talmmu_ProcessMapAttrib

******************************************************************************/
static IMG_RESULT talmmu_ProcessMapAttrib (
    TALMMU_sDevMemHeap *  psDevMemHeap,
    TALMMU_sMemory *      psMemory,
    IMG_UINT32            ui32PageNo,
    IMG_CHAR *            pvPageMemory,
    IMG_CHAR *            pvCpuLinearAddr,
    IMG_UINT32            ui32ByteInPage,
    IMG_UINT32            ui32BytesToProcess,
    IMG_UINT32            ui32BytesProcessed,
    IMG_UINT32            ui32Param,
    IMG_VOID *            pvParam
)
{
    IMG_UINT32                ui32PageTableNo;
#if !defined (__TALMMU_NO_TAL__)
    IMG_UINT32                ui32IndexInPageTable;
#endif
    TALMMU_sDevMemTemplate *  psDevMemTemplate;
#if defined (__TALMMU_USE_SYSAPIS__)
    TALMMU_sMemory *          psMem = pvParam;
    SYSMEMU_sPages *          psSysMem = psMem->hSysMemHandle;
#endif
    IMG_UINT32                ui32Result;

    psDevMemTemplate = psDevMemHeap->psDevMemTemplate;

    /* Determine the page table entry for this page...*/
    ui32PageTableNo      = ui32PageNo >> psDevMemTemplate->ui32PageTableNoShift;
#if !defined (__TALMMU_NO_TAL__)
    ui32IndexInPageTable = ui32PageNo & psDevMemTemplate->ui32IndexInPageTableMask;
#endif
    IMG_ASSERT(ui32PageTableNo < psDevMemHeap->ui32NoOfPageTables);

    IMG_ASSERT(psDevMemHeap->pasPageTable != IMG_NULL);
    if(psDevMemHeap->pasPageTable == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo] != IMG_NULL);

#if !defined (__TALMMU_NO_TAL__)
    /* Should have TAL handles for this page...*/
    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable]  != IMG_NULL);
#endif

    /* Make the page table entry valid and read only for this page...*/
#if defined (__TALMMU_USE_SYSAPIS__)
    if (psSysMem->ppaPhysAddr) {
        IMG_SIZE addrIdx = ui32BytesProcessed / HOST_MMU_PAGE_SIZE;
        IMG_UINT32 ui32DevPageInHostPage = ((ui32BytesProcessed % HOST_MMU_PAGE_SIZE )/ DEV_MMU_PAGE_SIZE);
        talmmu_MakePageTableEntryValid(psDevMemHeap, ui32PageNo, ui32Param,
                                       psSysMem->ppaPhysAddr[addrIdx] + DEV_MMU_PAGE_SIZE * ui32DevPageInHostPage);

    } else
#endif
    {
        talmmu_MakePageTableEntryValid(psDevMemHeap, ui32PageNo, ui32Param,
                                       SYSMEMU_CpuKmAddrToCpuPAddr(psSysMem->memHeap->memId, pvCpuLinearAddr));
    }

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                talmmu_DevMemFree

******************************************************************************/
static IMG_RESULT talmmu_DevMemFree(
    IMG_HANDLE  hDevMemContext,
    IMG_HANDLE  hMemory
)
{
    TALMMU_sMemory *      psMemory = hMemory;
    TALMMU_sDevMemHeap *  psDevMemHeap;
    IMG_UINT32            ui32Result;
    TALMMU_sIntMask       sOldIntMask;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(hMemory != IMG_NULL);
    if(hMemory == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    psDevMemHeap = psMemory->psDevMemHeap;

    /* If mapped then unmap..*/
    if (psMemory->bMapped)
    {
        /* Call function to process region...*/
        ui32Result = talmmu_ProcessMemoryRegion(psMemory, 0, psMemory->ui32Size, IMG_FALSE, talmmu_ProcessMemUnmap, 0, hDevMemContext);
          IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
   }

    /* If the device virtual memory address is not allocated externally...*/
    if (!psMemory->bExtDevVirAddr)
    {
        /* Free device virtual address...*/
        ADDR_CxFree(&psDevMemHeap->sContext, "", psMemory->ui32DevVirtOffset);
    }
    sOldIntMask = talmmu_DisableInt();

    /* Remove the memory allocation from the list...*/
    LST_remove(&psDevMemHeap->sMemoryList, psMemory);

    /* Re-enable interrupts */
    talmmu_EnableInt(sOldIntMask);

    /* Free the memory (if required) and structure...*/
    if (psMemory->pvCpuNonAlignedAddr != IMG_NULL)
    {
#if defined (__TALMMU_USE_PALLOC__)
        IMG_ASSERT(psMemory->ui32AllocId != IMG_NULL);
        if (psMemory->ui32AllocId != IMG_NULL)
            PALLOC_Free(psMemory->ui32AllocId);
#elif defined (__TALMMU_USE_SYSAPIS__)
        IMG_ASSERT(psMemory->hSysMemHandle != IMG_NULL);
        if (psMemory->hSysMemHandle != IMG_NULL)
            SYSMEMU_FreePages(psMemory->hSysMemHandle);
#elif defined (__TALMMU_USE_MALLOC__)
#if defined  (__TALMMU_USE_TILE_TEST__)
        if ( (psMemory->psDevMemHeap->sHeapInfo.bTiled == IMG_TRUE) && (psMemory->pvDetileBuffer != psMemory->pvCpuLinearAddr) )
        {
            if (psMemory->pvDetileBuffer != IMG_NULL)
                TALMMU_FREE(psMemory->pvDetileBuffer);
        }
#endif /* defined  (__TALMMU_USE_TILE_TEST__) */
        TALMMU_FREE(psMemory->pvCpuNonAlignedAddr);
#else
    #error "No/wrong TALMMU alloc option defined!"
#endif
    }
    else
    {
#if defined (__TALMMU_USE_SYSAPIS__)
        IMG_ASSERT(psMemory->hSysMemHandle != IMG_NULL);
        if (psMemory->hSysMemHandle != IMG_NULL)
            SYSMEMU_FreePages(psMemory->hSysMemHandle);
#endif
    }
    TALMMU_FREE(psMemory);

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                TALMMU_DevMemHeapEmpty

******************************************************************************/
IMG_RESULT TALMMU_DevMemHeapEmpty(
    IMG_HANDLE  hDevMemContext,
    IMG_HANDLE  hDevMemHeap
)
{
    TALMMU_sDevMemContext *  psDevMemContext = hDevMemContext;
    TALMMU_sDevMemHeap *     psDevMemHeap    = hDevMemHeap;
    IMG_UINT32                ui32Result;
    //TALMMU_sIntMask          sOldIntMask;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(hDevMemHeap != IMG_NULL);

    if(psDevMemHeap == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    /* Free all memory allocations...*/
    while (!LST_empty(&psDevMemHeap->sMemoryList))
    {
        talmmu_DevMemFree(psDevMemContext, LST_first(&psDevMemHeap->sMemoryList));
    }

    /* Disable interrupts */
    //sOldIntMask = talmmu_DisableInt();

    /* Deinitialise the memory context...*/
    ADDR_CxDeinitialise(&psDevMemHeap->sContext);

    /* Re-enable interupts */
    //talmmu_EnableInt(sOldIntMask);

    /* Free the page table array. */
    TALMMU_FREE(psDevMemHeap->pasPageTable);

    /* Return success. */
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                talmmu_DevMemHeapDestroy

******************************************************************************/
static IMG_VOID talmmu_DevMemHeapDestroy(
    IMG_HANDLE  hDevMemContext,
    IMG_HANDLE  hDevMemHeap
)
{
    TALMMU_sDevMemHeap *  psDevMemHeap = hDevMemHeap;

    TALMMU_DevMemHeapEmpty(hDevMemContext, hDevMemHeap);
    TALMMU_FREE(psDevMemHeap);
}

/*!
******************************************************************************

 @Function                TALMMU_Initialise

******************************************************************************/
IMG_RESULT TALMMU_Initialise(IMG_VOID)
{
#if !defined (__TALMMU_NO_TAL__)
    IMG_UINT32  ui32Result;
#endif

    /* If not initialised....*/
    if (!gInitialised)
    {
        /* Initialise list items...*/
        LST_init(&gsDevMemTemplateList);

#if !defined (__TALMMU_NO_TAL__)

#if !defined (IMG_KERNEL_MODULE)
        ui32Result = TALSETUP_Initialise();

        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
#endif
#endif
        /* Now initialised...*/
        gInitialised = IMG_TRUE;
    }

    /* Return success. */
    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(TALMMU_Initialise)

/*!
******************************************************************************

 @Function                TALMMU_Deinitialise

******************************************************************************/
IMG_RESULT TALMMU_Deinitialise(IMG_VOID)
{
    TALMMU_sDevMemTemplate *  psDevMemTemplate;
    /* If initialised...*/
    if (gInitialised)
    {
        /* Destroy the device memory templates...*/
        while (!LST_empty(&gsDevMemTemplateList))
        {
            psDevMemTemplate = (TALMMU_sDevMemTemplate*)LST_first(&gsDevMemTemplateList);
            TALMMU_DevMemTemplateDestroy((IMG_HANDLE)psDevMemTemplate);
        }

        /* No longer initialised...*/
        gInitialised = IMG_FALSE;
    }

    /* Return success. */
    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(TALMMU_Deinitialise)


/*!
******************************************************************************

 @Function                TALMMU_DevMemTemplateCreate

******************************************************************************/
IMG_RESULT TALMMU_DevMemTemplateCreate(
    TALMMU_sDevMemInfo *  psDevMemInfo,
    IMG_HANDLE *          phDevMemTemplate
)
{
    TALMMU_sDevMemTemplate *  psDevMemTemplate;
    TALMMU_sDevMemTemplate *  psTmpDevMemTemplate;
    TALMMU_sIntMask           sOldIntMask;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psDevMemInfo != IMG_NULL);
    if (psDevMemInfo == IMG_NULL)
        return IMG_ERROR_INVALID_PARAMETERS;

    /* Allocate new device memory Template - for template...*/
    psDevMemTemplate = IMG_MALLOC(sizeof(TALMMU_sDevMemTemplate));
     IMG_ASSERT(psDevMemTemplate != IMG_NULL);
    if (psDevMemTemplate == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    IMG_MEMSET(psDevMemTemplate, 0, sizeof(TALMMU_sDevMemTemplate));
    psDevMemTemplate->sDevMemInfo = *psDevMemInfo;
#if defined __TALMMU_USE_SYSAPIS__
    {
        IMG_UINT32  ui32Result;

        /* Open the device. */
        ui32Result = SYSDEVU_OpenDevice(psDevMemInfo->pszDeviceName, &psDevMemTemplate->hSysDevHandle);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            IMG_FREE(psDevMemTemplate);
            return ui32Result;
        }
    }
#endif

    LST_init(&psDevMemTemplate->sDevMemContextList);

#if !defined (__TALMMU_NO_TAL__)
    psDevMemTemplate->hPTDirMemSpace = TAL_GetMemSpaceHandle (psDevMemInfo->pszPageDirMemSpaceName);
    IMG_ASSERT(psDevMemTemplate->hPTDirMemSpace != IMG_NULL);
    if (psDevMemInfo->pszPageTableMemSpaceName == IMG_NULL)
    {
        psDevMemTemplate->hPTEntryMemSpace = TAL_MEMSPACE_ID_NONE;
    }
    else
    {
        psDevMemTemplate->hPTEntryMemSpace = TAL_GetMemSpaceHandle (psDevMemInfo->pszPageTableMemSpaceName);
        IMG_ASSERT(psDevMemTemplate->hPTEntryMemSpace != IMG_NULL);
    }
#endif

    /* Disable interrupts */
    sOldIntMask = talmmu_DisableInt();

    /* Check this template exist...*/
    psTmpDevMemTemplate = LST_first(&gsDevMemTemplateList);
    while (psTmpDevMemTemplate != IMG_NULL)
    {
        IMG_ASSERT(psDevMemTemplate->sDevMemInfo.ui32DeviceId != psTmpDevMemTemplate->sDevMemInfo.ui32DeviceId);
        psTmpDevMemTemplate = LST_next(psTmpDevMemTemplate);
    }
    if (psTmpDevMemTemplate != IMG_NULL)
    {
        IMG_ASSERT(psDevMemTemplate->sDevMemInfo.ui32DeviceId != psTmpDevMemTemplate->sDevMemInfo.ui32DeviceId);
    }

    /* Setup the page no. shift and byte in page mask...*/
    IMG_ASSERT(psDevMemTemplate->sDevMemInfo.ui32PageSize == (4*1024));
    psDevMemTemplate->ui32PageNoShift             = 12; /* For the page within a full 32-bit address   */
    psDevMemTemplate->ui32ByteInPageMask          = 0xFFF;
    psDevMemTemplate->ui32HeapAlignment           = 0x400000;
    psDevMemTemplate->ui32PageTableEntriesPerPage = (psDevMemTemplate->sDevMemInfo.ui32PageSize / sizeof(IMG_UINT32));
    psDevMemTemplate->ui32PageTableNoShift        = 10;   /* For the page table within the heap       */
    psDevMemTemplate->ui32IndexInPageTableMask    = 0x3FF;
    psDevMemTemplate->ui32PageDirNoShift          = 22;   /* For full 32-bit device virtual address   */
    switch (psDevMemTemplate->sDevMemInfo.eTilingScheme)
    {
    case 1:
        psDevMemTemplate->ui32TileWidth           = 512;  /* Tile width (in bytes)                    */
        psDevMemTemplate->ui32TileRowShift        = 9;    /* Bits to shift to remove tile row offset  */
        psDevMemTemplate->ui32YRowWithinTileShift = 3;    /* Bits to shift to remove Y row within tile */
        break;
    case 0:
        psDevMemTemplate->ui32TileWidth           = 256;  /* Tile width (in bytes)                    */
        psDevMemTemplate->ui32TileRowShift        = 8;    /* Bits to shift to remove tile row offset  */
        psDevMemTemplate->ui32YRowWithinTileShift = 4;    /* Bits to shift to remove Y row within tile */
        break;
    default:
        IMG_ASSERT(IMG_FALSE);
        break;
    }

    /* Add to list...*/
    LST_add(&gsDevMemTemplateList, psDevMemTemplate);

    /* Re-enable interrupts */
    talmmu_EnableInt(sOldIntMask);

    /* Return the device memory Template as a handle...*/
    *phDevMemTemplate = psDevMemTemplate;

    /* Return success. */
    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(TALMMU_DevMemTemplateCreate)


/*!
******************************************************************************

 @Function                TALMMU_DevMemTemplateDestroy

******************************************************************************/
IMG_RESULT TALMMU_DevMemTemplateDestroy(
    IMG_HANDLE  hDevMemTemplate
)
{
    TALMMU_sDevMemTemplate *  psDevMemTemplate = hDevMemTemplate;
    IMG_UINT32                i;
    TALMMU_sIntMask           sOldIntMask;
    IMG_UINT32                ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(hDevMemTemplate != IMG_NULL);
    if(hDevMemTemplate == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    /* Destroy the device memory contexts...*/
    while (!LST_empty(&psDevMemTemplate->sDevMemContextList))
    {
        TALMMU_DevMemContextDestroy(LST_first(&psDevMemTemplate->sDevMemContextList));
    }

    IMG_ASSERT(psDevMemTemplate->ui32NoContexts == 0);

    /* Destroy the device memory heaps...*/
    for (i=0; i<psDevMemTemplate->ui32NoHeaps; i++)
    {
        talmmu_DevMemHeapDestroy(IMG_NULL, psDevMemTemplate->pasDevMemHeap[i]);
    }

    /* Disable interrupts */
    sOldIntMask = talmmu_DisableInt();

    /* Remove the device memory Template from the list...*/
    LST_remove(&gsDevMemTemplateList, psDevMemTemplate);

    /* Re-enable interrupts */
    talmmu_EnableInt(sOldIntMask);

#if defined __TALMMU_USE_SYSAPIS__
    /* Close the device. */
    SYSDEVU_CloseDevice(psDevMemTemplate->hSysDevHandle);
#endif

    /* Free the name and structure...*/
    TALMMU_FREE(psDevMemTemplate);

    /* Return success. */
    return IMG_SUCCESS;

}

IMGVIDEO_EXPORT_SYMBOL(TALMMU_DevMemTemplateDestroy)
/*!
******************************************************************************

 @Function                talmmu_CreateHeap

******************************************************************************/
static IMG_RESULT talmmu_CreateHeap(
    IMG_HANDLE             hDevMemTemplate,
    TALMMU_sHeapInfo *     psHeapInfo,
    IMG_BOOL               bFull,
    TALMMU_sDevMemHeap **  ppsDevMemHeap
)
{
    TALMMU_sDevMemTemplate *  psDevMemTemplate = hDevMemTemplate;
    TALMMU_sDevMemHeap *      psDevMemHeap;

    /* Allocate new device heap info structure...*/
    psDevMemHeap = IMG_MALLOC(sizeof(TALMMU_sDevMemHeap));
    IMG_ASSERT(psDevMemHeap != IMG_NULL);
    if (psDevMemHeap == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    IMG_MEMSET(psDevMemHeap, 0, sizeof(TALMMU_sDevMemHeap));
    psDevMemHeap->psDevMemTemplate = psDevMemTemplate;
    psDevMemHeap->sHeapInfo        = *psHeapInfo;
    LST_init(&psDevMemHeap->sMemoryList);
#if defined (__TALMMU_USE_PALLOC__) || defined (__TALMMU_USE_SYSAPIS__)
    psDevMemHeap->eMemAttrib = psDevMemTemplate->sDevMemInfo.eMemAttrib;
    psDevMemHeap->eMemPool   = psDevMemTemplate->sDevMemInfo.eMemPool;
#endif
#if !defined (__TALMMU_NO_TAL__)
    psDevMemHeap->hMemSpace = TAL_GetMemSpaceHandle (psHeapInfo->pszMemSpaceName);
    IMG_ASSERT(psDevMemHeap->hMemSpace != IMG_NULL);
    if (psDevMemTemplate->hPTEntryMemSpace == TAL_MEMSPACE_ID_NONE)
    {
        psDevMemHeap->hPTMemSpace = psDevMemHeap->hMemSpace;
    }
    else
    {
        psDevMemHeap->hPTMemSpace = psDevMemTemplate->hPTEntryMemSpace;
    }
#endif

    /* Check size is > 0...*/
    IMG_ASSERT(psHeapInfo->ui32Size > 0);

    /* If tiled...*/
    if (psHeapInfo->bTiled)
    {
        /* Check alignment and size...*/
        IMG_ASSERT((psHeapInfo->ui32BaseDevVirtAddr & (~0xFFF00000)) == 0);
        IMG_ASSERT((psHeapInfo->ui32Size & (~0xFFF00000)) == 0);
        psDevMemHeap->ui32TiledAlignment = 1 << (psDevMemTemplate->ui32TileRowShift +
                                                 psDevMemTemplate->ui32YRowWithinTileShift +
                                                 psHeapInfo->ui32XTileStride + 1);
    }

    /* If full structure required...*/
    if (bFull)
    {
        //TALMMU_sIntMask                   sOldIntMask;

        /* Disable interrupts */
        //sOldIntMask = talmmu_DisableInt();

        /* Setup the address allocation functions for device virtual addresses...*/
        ADDR_CxInitialise(&psDevMemHeap->sContext);
        psDevMemHeap->sRegions.ui64BaseAddr = 0;
        psDevMemHeap->sRegions.ui64Size     = psDevMemHeap->sHeapInfo.ui32Size;
        ADDR_CxDefineMemoryRegion(&psDevMemHeap->sContext, &psDevMemHeap->sRegions);

        /* Re-enable interupts */
        //talmmu_EnableInt(sOldIntMask);

        /* Calculate no. of pages in this heap...*/
        psDevMemHeap->ui32NoOfPages = psDevMemHeap->sHeapInfo.ui32Size >> psDevMemTemplate->ui32PageNoShift;
        IMG_ASSERT(psDevMemHeap->ui32NoOfPages != 0);

        /* Calculate no. of page tables in this heap...*/
        psDevMemHeap->ui32NoOfPageTables = (psDevMemHeap->ui32NoOfPages + psDevMemTemplate->ui32PageTableEntriesPerPage - 1) >>
                                                psDevMemTemplate->ui32PageTableNoShift;
        IMG_ASSERT(psDevMemHeap->ui32NoOfPageTables != 0);

        /* Allocate memory for the page table structures...*/
        psDevMemHeap->pasPageTable = IMG_MALLOC(sizeof(*psDevMemHeap->pasPageTable)*psDevMemHeap->ui32NoOfPageTables);
        IMG_ASSERT(psDevMemHeap->pasPageTable != IMG_NULL);
        if (psDevMemHeap->pasPageTable == IMG_NULL)
        {
            IMG_FREE(psDevMemHeap);
            return IMG_ERROR_OUT_OF_MEMORY;
        }
        IMG_MEMSET(psDevMemHeap->pasPageTable, 0, (sizeof(*psDevMemHeap->pasPageTable)*psDevMemHeap->ui32NoOfPageTables));
    }

    /* Return pointer to heap...*/
    *ppsDevMemHeap = psDevMemHeap;

    /* Return success. */
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                TALMMU_DevMemHeapAdd

******************************************************************************/
IMG_RESULT TALMMU_DevMemHeapAdd(
    IMG_HANDLE          hDevMemTemplate,
    TALMMU_sHeapInfo *  psHeapInfo
)
{
    TALMMU_sDevMemTemplate *  psDevMemTemplate = hDevMemTemplate;
    TALMMU_sDevMemHeap *      psDevMemHeap;
    TALMMU_sDevMemHeap *      psTmpDevMemHeap;
    IMG_UINT32                i;
    IMG_UINT32                ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(hDevMemTemplate != IMG_NULL);
    if(hDevMemTemplate == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    IMG_ASSERT(psHeapInfo != IMG_NULL);
    if(psHeapInfo == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    IMG_ASSERT(psHeapInfo->pszMemSpaceName != IMG_NULL);
    IMG_ASSERT((psHeapInfo->ui32BaseDevVirtAddr & (psDevMemTemplate->ui32HeapAlignment-1)) == 0);
    IMG_ASSERT((psHeapInfo->ui32Size & psDevMemTemplate->ui32ByteInPageMask) == 0);

    /* Check this heap doesn't exist...*/
    for (i=0; i<psDevMemTemplate->ui32NoHeaps; i++)
    {
        psTmpDevMemHeap = psDevMemTemplate->pasDevMemHeap[i];
        /* Check for overlapping heaps...*/
        if (psHeapInfo->ui32BaseDevVirtAddr <= psTmpDevMemHeap->sHeapInfo.ui32BaseDevVirtAddr)
        {
            IMG_ASSERT((psHeapInfo->ui32BaseDevVirtAddr + psHeapInfo->ui32Size) <= psTmpDevMemHeap->sHeapInfo.ui32BaseDevVirtAddr);
        }
        else
        {
            IMG_ASSERT((psTmpDevMemHeap->sHeapInfo.ui32BaseDevVirtAddr + psTmpDevMemHeap->sHeapInfo.ui32Size) <= psHeapInfo->ui32BaseDevVirtAddr);
        }
        /* Check for heap with the same id...*/
        IMG_ASSERT(psHeapInfo->ui32HeapId != psTmpDevMemHeap->sHeapInfo.ui32HeapId);
    }

    /* Branch on heap type...*/
    switch (psHeapInfo->eHeapType)
    {
    case TALMMU_HEAP_SHARED_EXPORTED:        /*!< Shared and exported            */
        ui32Result = talmmu_CreateHeap(hDevMemTemplate, psHeapInfo, IMG_TRUE, &psDevMemHeap);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
        break;

    case TALMMU_HEAP_PERCONTEXT:             /*!< Per context heap               */
        ui32Result = talmmu_CreateHeap(hDevMemTemplate, psHeapInfo, IMG_TRUE, &psDevMemHeap);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
        break;

    default:
        IMG_ASSERT(IMG_FALSE);
        break;
    }

    /* Add to list...*/
    psDevMemTemplate->pasDevMemHeap[psDevMemTemplate->ui32NoHeaps] = psDevMemHeap;
    psDevMemTemplate->ui32NoHeaps++;

    /* Return success. */
    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(TALMMU_DevMemHeapAdd)


/*!
******************************************************************************

 @Function                TALMMU_DevMemContextCreate

******************************************************************************/
IMG_RESULT TALMMU_DevMemContextCreate(
    IMG_HANDLE    hDevMemTemplate,
    IMG_UINT32    ui32MmuContextId,
    IMG_HANDLE *  phDevMemContext
)
{
    TALMMU_sDevMemTemplate *  psDevMemTemplate = hDevMemTemplate;
    TALMMU_sDevMemContext *   psDevMemContext;
    TALMMU_sDevMemHeap *      psDevMemHeap;
    IMG_UINT32                i;
    IMG_UINT32                ui32PageTableNo;
//    IMG_UINT32                ui32TiledRegionNo;
    IMG_UINT32                ui32Result;
    TALMMU_sIntMask           sOldIntMask;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(hDevMemTemplate != IMG_NULL);
    if (hDevMemTemplate == IMG_NULL)
        return IMG_ERROR_INVALID_PARAMETERS;

    /* Allocate new device memory context...*/
    psDevMemContext = IMG_MALLOC(sizeof(TALMMU_sDevMemContext));
    IMG_ASSERT(psDevMemContext != IMG_NULL);
    if (psDevMemContext == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    IMG_MEMSET(psDevMemContext, 0, sizeof(TALMMU_sDevMemContext));
    psDevMemContext->psDevMemTemplate = psDevMemTemplate;
    psDevMemContext->ui32MmuContextId = ui32MmuContextId;

    /* Allocate memory to represent the page table directory...*/
#if defined (__TALMMU_USE_PALLOC__)
    ui32Result = PALLOC_Alloc(psDevMemTemplate->sDevMemInfo.ui32AttachId,
                              psDevMemTemplate->sDevMemInfo.ui32PageSize,
                              psDevMemTemplate->sDevMemInfo.eMemAttrib,
                              psDevMemTemplate->sDevMemInfo.eMemPool,
                              (IMG_VOID **)&psDevMemContext->pui32PageDir,
                              &psDevMemContext->ui32PageDirAllocId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_page_table_dir_alloc;
    }
#elif defined (__TALMMU_USE_SYSAPIS__)
    {
        ui32Result = SYSMEMU_AllocatePages(psDevMemTemplate->sDevMemInfo.ui32PageSize,
        									psDevMemTemplate->sDevMemInfo.eMemAttrib,
                                           psDevMemTemplate->sDevMemInfo.eMemPool,
                                           &psDevMemContext->hSysMemHandlePageDir,
                                           IMG_NULL);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error_page_table_dir_alloc;
        }

        SYSMEMU_GetCpuKmAddr((IMG_VOID **)&psDevMemContext->pui32PageDir, psDevMemContext->hSysMemHandlePageDir);

        IMG_ASSERT(psDevMemContext->pui32PageDir != IMG_NULL);
        if (psDevMemContext->pui32PageDir == IMG_NULL)
        {
            ui32Result = IMG_ERROR_FATAL;
            goto error_cpu_km_map;
        }
    }
#elif defined (__TALMMU_USE_MALLOC__)
    psDevMemContext->pui32PageDir = IMG_MALLOC(psDevMemTemplate->sDevMemInfo.ui32PageSize);
    IMG_ASSERT(psDevMemContext->pui32PageDir != IMG_NULL);
    if (psDevMemContext->pui32PageDir == IMG_NULL)
    {
        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto error_page_table_dir_alloc;
    }
#else
    #error "No/wrong TALMMU alloc option defined!"
#endif

    IMG_ASSERT(psDevMemContext->pui32PageDir);
    IMG_MEMSET(psDevMemContext->pui32PageDir, 0, psDevMemTemplate->sDevMemInfo.ui32PageSize);

    /* Check for PTD Alignment */
    if ( psDevMemTemplate->sDevMemInfo.ui32PageTableDirAlignment != 0 )
    {
        /* Alignment requirement specified by user is larger than page size    */
        /* Make sure alignment is a multiple of page size.                    */
        IMG_ASSERT ( (psDevMemTemplate->sDevMemInfo.ui32PageTableDirAlignment % psDevMemTemplate->sDevMemInfo.ui32PageSize) == 0 );
    }
    else
    {
        /* Set up PTD alignment to Page Size */
        psDevMemTemplate->sDevMemInfo.ui32PageTableDirAlignment  = psDevMemTemplate->sDevMemInfo.ui32PageSize;
    }

#if !defined (__TALMMU_NO_TAL__)
    /* Malloc device memory for Page Directory */
    ui32Result = TALMEM_Malloc(psDevMemTemplate->hPTDirMemSpace,
                               (IMG_CHAR *)psDevMemContext->pui32PageDir,
                               psDevMemTemplate->sDevMemInfo.ui32PageSize,
                               psDevMemTemplate->sDevMemInfo.ui32PageTableDirAlignment,
                               &psDevMemContext->hPageDirTalHandle,
                               IMG_TRUE,
                               IMG_NULL);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_page_dir_alloc;
    }
#endif

    /* Reference or create heaps for this context...*/
//    ui32TiledRegionNo = 0;
    for (i=0; i<psDevMemTemplate->ui32NoHeaps; i++)
    {
        psDevMemHeap = psDevMemTemplate->pasDevMemHeap[i];
        IMG_ASSERT(psDevMemHeap != IMG_NULL);
        if (psDevMemHeap == IMG_NULL)
            goto error_heap_create;

        /* Branch on heap type...*/
        switch (psDevMemHeap->sHeapInfo.eHeapType)
        {
        case TALMMU_HEAP_SHARED_EXPORTED:        /*!< Shared and exported            */
            IMG_ASSERT(psDevMemHeap->pasPageTable != IMG_NULL);
            if (psDevMemHeap->pasPageTable == IMG_NULL)
                goto error_heap_create;

            psDevMemContext->pasDevMemHeap[i] = psDevMemHeap;

            /* Loop over the currently allocated page tables for this heap...*/
            for (ui32PageTableNo=0; ui32PageTableNo<psDevMemHeap->ui32NoOfPageTables; ui32PageTableNo++)
            {
                /* If this page table has a reference...*/
                if ( (psDevMemHeap->pasPageTable[ui32PageTableNo] != IMG_NULL) && (psDevMemHeap->pasPageTable[ui32PageTableNo]->ui32PageTableRefCount != 0) )
                {
#if !defined (__TALMMU_NO_TAL__)
                    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableTalHandle != IMG_NULL);
#endif
                    /* Make the page table directory entry valid for this page table...*/
                    talmmu_MakePageDirEntryValid(psDevMemContext, psDevMemHeap, ui32PageTableNo);
                }
            }
            break;

        case TALMMU_HEAP_PERCONTEXT:             /*!< Per context heap               */
            ui32Result = talmmu_CreateHeap(psDevMemTemplate, &psDevMemHeap->sHeapInfo , IMG_TRUE, &psDevMemContext->pasDevMemHeap[i]);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error_heap_create;
            }
            break;

        default:
            IMG_ASSERT(IMG_FALSE);
            break;
        }

        psDevMemContext->ui32NoHeaps++;
    }

    /* Disable interrupts */
    sOldIntMask = talmmu_DisableInt();

    /* Add to list...*/
    LST_add(&psDevMemTemplate->sDevMemContextList, psDevMemContext);

    /* Update no. of contexts active...*/
    psDevMemTemplate->ui32NoContexts++;

    /* Re-enable interrupts */
    talmmu_EnableInt(sOldIntMask);

    /* Return the device memory context as a handle...*/
    *phDevMemContext = psDevMemContext;

    /* Return success. */
    return IMG_SUCCESS;

    /* Error handling. */
error_heap_create:
    for(i--; i >= 0; i--)
    {
        psDevMemHeap = psDevMemContext->pasDevMemHeap[i];
        if (TALMMU_HEAP_PERCONTEXT == psDevMemHeap->sHeapInfo.eHeapType)
        {
            talmmu_DevMemHeapDestroy(psDevMemContext, psDevMemHeap);
        }
        psDevMemContext->ui32NoHeaps--;
    }
#if !defined (__TALMMU_NO_TAL__)
    TALMEM_Free(&psDevMemContext->hPageDirTalHandle);
#endif
#if !defined (__TALMMU_NO_TAL__)
error_page_dir_alloc:
#endif
#if defined (__TALMMU_USE_SYSAPIS__)
error_cpu_km_map:
    SYSMEMU_FreePages(psDevMemContext->hSysMemHandlePageDir);
    psDevMemContext->hSysMemHandlePageDir = IMG_NULL;
#endif
error_page_table_dir_alloc:
    IMG_FREE(psDevMemContext);

    return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(TALMMU_DevMemContextCreate)

/*!
******************************************************************************

 @Function                TALMMU_DevMemContextDestroy

******************************************************************************/
IMG_RESULT TALMMU_DevMemContextDestroy(
    IMG_HANDLE  hDevMemContext
)
{
    TALMMU_sDevMemContext *   psDevMemContext = hDevMemContext;
    TALMMU_sDevMemTemplate *  psDevMemTemplate;
    TALMMU_sDevMemHeap *      psDevMemHeap;
    IMG_UINT32                i;
    IMG_UINT32                ui32PageTableNo;
    TALMMU_sIntMask           sOldIntMask;
    IMG_UINT32                ui32Result;
//#if !defined (__TALMMU_NO_TAL__)
//    IMG_UINT32                ui32Result;
//#endif

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(hDevMemContext != IMG_NULL);
    if(hDevMemContext == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }


    psDevMemTemplate = psDevMemContext->psDevMemTemplate;

#if !defined (__TALMMU_NO_TAL__)
    /* Clear MMU context...*/
    ui32Result = TALVMEM_ClearContext(psDevMemContext->psDevMemTemplate->hPTDirMemSpace, psDevMemContext->ui32MmuContextId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }
#endif

    /* Reference or create heaps for this context...*/
    for (i=0; i<psDevMemContext->ui32NoHeaps; i++)
    {
        psDevMemHeap = psDevMemContext->pasDevMemHeap[i];
        IMG_ASSERT(psDevMemHeap != IMG_NULL);
        if(psDevMemHeap == IMG_NULL)
        {
            ui32Result = IMG_ERROR_INVALID_PARAMETERS;
            return ui32Result;
        }

        /* Branch on heap type...*/
        switch (psDevMemHeap->sHeapInfo.eHeapType)
        {
        case TALMMU_HEAP_SHARED_EXPORTED:        /*!< Shared and exported            */
            IMG_ASSERT(psDevMemHeap->pasPageTable != IMG_NULL);
            if (psDevMemHeap->pasPageTable == IMG_NULL)
                return IMG_ERROR_GENERIC_FAILURE;

            /* Loop over the currently allocated page tables for this heap...*/
            for (ui32PageTableNo=0; ui32PageTableNo<psDevMemHeap->ui32NoOfPageTables; ui32PageTableNo++)
            {
                /* If this page table has a reference...*/
                if ( (psDevMemHeap->pasPageTable[ui32PageTableNo] != IMG_NULL) &&
                     (psDevMemHeap->pasPageTable[ui32PageTableNo]->ui32PageTableRefCount != 0) )
                {
 #if !defined (__TALMMU_NO_TAL__)
                    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->hPageTableTalHandle != IMG_NULL);
#endif
                    /* Invalidate the page table directory entry for the page table...*/
                    talmmu_MakePageDirEntryInvalid(psDevMemContext, psDevMemHeap, ui32PageTableNo);
                }
            }
            break;

        case TALMMU_HEAP_PERCONTEXT:             /*!< Per context heap               */
            talmmu_DevMemHeapDestroy(psDevMemContext, psDevMemHeap);
            break;

        default:
            IMG_ASSERT(IMG_FALSE);
            break;
        }
    }

#if !defined (__TALMMU_NO_TAL__)
    /* Free device memory for page table directory...*/
    ui32Result = TALMEM_Free(&psDevMemContext->hPageDirTalHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }
    IMG_ASSERT(psDevMemContext->hPageDirTalHandle == IMG_NULL);
#endif

    /* Free the memory that represents the page table directory....*/
    IMG_ASSERT(psDevMemContext->pui32PageDir != IMG_NULL);
#if defined (__TALMMU_USE_PALLOC__)
    IMG_ASSERT(psDevMemContext->ui32PageDirAllocId != IMG_NULL);
    PALLOC_Free(psDevMemContext->ui32PageDirAllocId);
    psDevMemContext->ui32PageDirAllocId = IMG_NULL;
#elif defined (__TALMMU_USE_SYSAPIS__)
    IMG_ASSERT(psDevMemContext->hSysMemHandlePageDir != IMG_NULL);
    if(psDevMemContext->hSysMemHandlePageDir == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    SYSMEMU_FreePages(psDevMemContext->hSysMemHandlePageDir);
    psDevMemContext->hSysMemHandlePageDir = IMG_NULL;
#elif defined (__TALMMU_USE_MALLOC__)
    TALMMU_FREE(psDevMemContext->pui32PageDir);
#else
    #error "No/wrong TALMMU alloc option defined!"
#endif
    psDevMemContext->pui32PageDir = IMG_NULL;

    /* Disable interrupts */
    sOldIntMask = talmmu_DisableInt();

    /* Remove the device memory context from the list...*/
    LST_remove(&psDevMemTemplate->sDevMemContextList, psDevMemContext);

    /* Update no. of contexts active...*/
    psDevMemContext->psDevMemTemplate->ui32NoContexts--;

    /* Re-enable interrupts */
    talmmu_EnableInt(sOldIntMask);

    /* Free the name and structure...*/
    TALMMU_FREE(psDevMemContext);

    /* Return success. */
    return IMG_SUCCESS;
}

IMGVIDEO_EXPORT_SYMBOL(TALMMU_DevMemContextDestroy)

#if !defined (__TALMMU_NO_TAL__)
/*!
******************************************************************************

 @Function                TALMMU_DevMemContextGetPtd

 ******************************************************************************/
IMG_RESULT TALMMU_DevMemContextGetPtd(
    IMG_HANDLE    hDevMemContext,
    IMG_HANDLE *  phTalHandle
)
{

    TALMMU_sDevMemContext *  psDevMemContext = hDevMemContext;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(hDevMemContext != IMG_NULL);

    *phTalHandle = psDevMemContext->hPageDirTalHandle;

    /* Return success. */
    return IMG_SUCCESS;
}
#endif


/*!
******************************************************************************

 @Function                TALMMU_DevMemContextSetMMUPtd

******************************************************************************/
IMG_RESULT TALMMU_DevMemContextSetMMUPtd(
    IMG_HANDLE  hDevMemContext,
    IMG_VOID *  pvAltCbParam
)
{
    TALMMU_sDevMemContext *   psDevMemContext = hDevMemContext;
    TALMMU_sDevMemTemplate *  psDevMemTemplate;
    IMG_UINT32                ui32Result = IMG_SUCCESS;
    TALMMU_sIntMask           sOldIntMask;

#if !defined (__TALMMU_NO_TAL__)
    IMG_UINT32            ui32TiledRegionNo;
    TALMMU_sDevMemHeap *  psDevMemHeap;
    IMG_UINT32            i;
#else
    IMG_PHYSADDR paAddr;
#endif

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(hDevMemContext != IMG_NULL);
    if(hDevMemContext == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    /* Disable interrupts */
    sOldIntMask = talmmu_DisableInt();

    /* Get access to the device template...*/
    psDevMemTemplate = psDevMemContext->psDevMemTemplate;

#if !defined (__TALMMU_NO_TAL__)
    /* Register page table with system */
    ui32Result = TALINTVAR_WriteMemRef(psDevMemContext->hPageDirTalHandle,
                                       0,
                                       psDevMemTemplate->hPTDirMemSpace,
                                       1);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto ErrorExit;
    }
#else
    #if defined (__TALMMU_USE_SYSAPIS__)
            paAddr = SYSMEMU_CpuKmAddrToCpuPAddr(psDevMemTemplate->sDevMemInfo.eMemPool,
                                                 psDevMemContext->pui32PageDir);
            paAddr = SYSDEVU_CpuPAddrToDevPAddr(psDevMemTemplate->hSysDevHandle, paAddr);
    #else
            #error Not Supported __TALMMU_NO_TAL__ must be used with __TALMMU_USE_SYSAPIS__
    #endif
#endif

    /* if 36 bit MMU...*/
    if (psDevMemTemplate->sDevMemInfo.eMMUType == TALMMU_MMUTYPE_4K_PAGES_36BIT_ADDR)
    {
        /* Need to shift the address by 4 to fit in 32 bits...*/
#if !defined (__TALMMU_NO_TAL__)
        ui32Result = TALINTVAR_RunCommand(TAL_PDUMPL_INTREG_SHR,
                                          psDevMemTemplate->hPTDirMemSpace,
                                          1,
                                          psDevMemTemplate->hPTDirMemSpace,
                                          1,
                                          0,
                                          4,
                                          IMG_FALSE);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto ErrorExit;
        }
#else
        paAddr >>= 4;
#endif
    }

    if (psDevMemTemplate->sDevMemInfo.eMMUType == TALMMU_MMUTYPE_4K_PAGES_40BIT_ADDR)
    {
        /* Need to shift the address by 4 to fit in 32 bits...*/
#if !defined (__TALMMU_NO_TAL__)
            ui32Result = TALINTVAR_RunCommand(TAL_PDUMPL_INTREG_SHR,
                                              psDevMemTemplate->hPTDirMemSpace,
                                              1,
                                              psDevMemTemplate->hPTDirMemSpace,
                                              1,
                                              0,
                                              8,
                                              IMG_FALSE);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto ErrorExit;
            }
#else
        paAddr >>= 8;
#endif
    }

    /* If callback defined...*/
    if (psDevMemTemplate->pfnEventCallback != IMG_NULL)
    {
#if !defined (__TALMMU_NO_TAL__)
        psDevMemTemplate->pfnEventCallback(TALMMU_EVENT_WRITE_PAGE_DIRECTORY_REF,
                                           pvAltCbParam ? pvAltCbParam : psDevMemTemplate->pCallbackParameter,
                                           1,
                                           (IMG_VOID*)psDevMemTemplate->hPTDirMemSpace);
#else
        IMG_ASSERT((paAddr & 0xFFFFFFFF00000000ULL) == 0);
        psDevMemTemplate->pfnEventCallback(TALMMU_EVENT_WRITE_PAGE_DIRECTORY_REF,
                                            pvAltCbParam ? pvAltCbParam : psDevMemTemplate->pCallbackParameter,
                                           (IMG_UINT32)paAddr,
                                           IMG_NULL);
#endif
    }
    else
    {
        IMG_ASSERT(IMG_FALSE);            /* This function really requires the callback to be defined...*/
    }

#if !defined (__TALMMU_NO_TAL__)
    /* Set page table directory TAL MMUContext */
    ui32Result = TALVMEM_SetContext(psDevMemTemplate->hPTDirMemSpace,
                                    psDevMemContext->ui32MmuContextId,
                                    psDevMemTemplate->sDevMemInfo.eMMUType,
                                    psDevMemContext->hPageDirTalHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto ErrorExit;
    }

    /* Check to see if any of the heaps are tiled...*/
    ui32TiledRegionNo = 0;
    for (i=0; i<psDevMemContext->ui32NoHeaps; i++)
    {
        psDevMemHeap = psDevMemTemplate->pasDevMemHeap[i];
        IMG_ASSERT(psDevMemHeap != IMG_NULL);

        /* If tiled...*/
        if (psDevMemHeap->sHeapInfo.bTiled)
        {
            if (psDevMemHeap->hMemSpace != psDevMemTemplate->hPTDirMemSpace
                && TALPDUMP_GetNoContexts() != 0)
            {
                IMG_UINT32 ui32SemaId = TALPDUMP_GetSemaphoreId(psDevMemHeap->hMemSpace, psDevMemTemplate->hPTDirMemSpace);
                TALPDUMP_Unlock(psDevMemTemplate->hPTDirMemSpace, ui32SemaId);
                TALPDUMP_Lock(psDevMemHeap->hMemSpace, ui32SemaId);
            }
            /* Define tilled region with TAL...*/
            ui32Result = TALVMEM_SetTiledRegion(psDevMemHeap->hMemSpace,
                                                psDevMemContext->ui32MmuContextId,
                                                ui32TiledRegionNo++,
                                                psDevMemHeap->sHeapInfo.ui32BaseDevVirtAddr,
                                                psDevMemHeap->sHeapInfo.ui32Size,
                                                psDevMemHeap->sHeapInfo.ui32XTileStride);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto ErrorExit;
            }
        }
    }

    /* Re-enable interrupts */
ErrorExit:
#endif
    talmmu_EnableInt(sOldIntMask);

    /* Return success. */
    return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(TALMMU_DevMemContextSetMMUPtd)


/*!
******************************************************************************

 @Function                TALMMU_GetHeapHandle

******************************************************************************/
IMG_RESULT TALMMU_GetHeapHandle(
    IMG_UINT32    ui32HeapId,
    IMG_HANDLE    hDevMemContext,
    IMG_HANDLE *  phDevMemHeap
)
{
    TALMMU_sDevMemContext *  psDevMemContext = hDevMemContext;
    IMG_UINT32               i;
    IMG_UINT32               ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(hDevMemContext != IMG_NULL);
    if(hDevMemContext == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }


    for (i=0; i<psDevMemContext->ui32NoHeaps; i++)
    {
        if (psDevMemContext->pasDevMemHeap[i]->sHeapInfo.ui32HeapId == ui32HeapId)
        {
            *phDevMemHeap = psDevMemContext->pasDevMemHeap[i];

            return IMG_SUCCESS;
        }
    }
    IMG_ASSERT(IMG_FALSE);
    return IMG_ERROR_GENERIC_FAILURE;
}
IMGVIDEO_EXPORT_SYMBOL(TALMMU_GetHeapHandle)


/*!
******************************************************************************

 @Function                TALMMU_GetHeapInfo

******************************************************************************/
IMG_RESULT TALMMU_GetHeapInfo(
    IMG_HANDLE          hDevMemHeap,
    TALMMU_sHeapInfo *  psHeapInfo
)
{    
    TALMMU_sDevMemHeap    * psDevMemHeap = hDevMemHeap;
    IMG_RESULT              ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psDevMemHeap != IMG_NULL);

    if(psDevMemHeap == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    *psHeapInfo = psDevMemHeap->sHeapInfo;

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                TALMMU_DevMemHeapOptions

******************************************************************************/
IMG_RESULT TALMMU_DevMemHeapOptions(
    IMG_HANDLE            hDevMemHeap,
    TALMMU_eHeapOptionId  eHeapOptionId,
    TALMMU_uHeapOptions   uHeapOptions
)
{
    TALMMU_sDevMemHeap *psDevMemHeap = hDevMemHeap;
    switch (eHeapOptionId)
    {
    case TALMMU_HEAP_OPT_ADD_GUARD_BAND:
        psDevMemHeap->ui32GuardBand = uHeapOptions.sGuardBandOpt.ui32GuardBand;
        break;

#if defined (__TALMMU_USE_PALLOC__) || defined (__TALMMU_USE_SYSAPIS__)
    case TALMMU_HEAP_OPT_SET_MEM_ATTRIB:
        psDevMemHeap->eMemAttrib = uHeapOptions.eMemAttrib;
        break;

    case TALMMU_HEAP_OPT_SET_MEM_POOL:
        psDevMemHeap->eMemPool = uHeapOptions.eMemPool;
        break;
#endif

    default:
        IMG_ASSERT(IMG_FALSE);
        break;
    }

    /* Return success. */
    return IMG_SUCCESS;
}

IMGVIDEO_EXPORT_SYMBOL(TALMMU_DevMemHeapOptions)
/*!
******************************************************************************

 @Function                TALMMU_GetContextHandle

******************************************************************************/
IMG_RESULT TALMMU_GetContextHandle (
    IMG_HANDLE    hDevMemObject,
    IMG_HANDLE *  phDevMemContext
)
{

    TALMMU_sMemory *  psDevMem = hDevMemObject;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psDevMem != IMG_NULL);
    if (psDevMem == IMG_NULL)
        return IMG_ERROR_INVALID_PARAMETERS;

    *phDevMemContext = ((IMG_HANDLE) psDevMem->psDevMemContext);

    /* Return success. */
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                TALMMU_GetContextId

******************************************************************************/
 IMG_RESULT TALMMU_GetContextId(
    IMG_HANDLE    hDevMemContext,
    IMG_UINT32 *  pui32MmuContextId
)
{
    TALMMU_sDevMemContext *  psDevMemContext = hDevMemContext;
    IMG_RESULT              ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psDevMemContext != IMG_NULL);
    if(psDevMemContext == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    *pui32MmuContextId = ((IMG_UINT32) (psDevMemContext->ui32MmuContextId));

    /* Return success. */
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                talmmu_DevMemMallocNonMap

******************************************************************************/
static IMG_RESULT talmmu_DevMemMallocNonMap(
    IMG_HANDLE    hDevMemContext,
    IMG_HANDLE    hDevMemHeap,
    IMG_UINT32    ui32Size,
    IMG_UINT32    ui32Alignment,
    IMG_VOID *    pvCpuLinearAddr,
    IMG_UINT32    ui32DevVirtOffset,
    IMG_BOOL      bExtDevVirAddr,
    IMG_HANDLE    hExtImportHandle,
    IMG_HANDLE *  phMemory
)
{
    TALMMU_sDevMemContext *   psDevMemContext = hDevMemContext;
    TALMMU_sDevMemTemplate *  psDevMemTemplate;
    TALMMU_sDevMemHeap *      psDevMemHeap    = hDevMemHeap;
    TALMMU_sMemory *          psMemory;
    IMG_UINT64                ui64DevOffset = 0;
    IMG_RESULT                ui32Result = IMG_SUCCESS;
    TALMMU_sIntMask           sOldIntMask;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psDevMemContext != IMG_NULL);
    if(psDevMemContext == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    IMG_ASSERT(hDevMemHeap != IMG_NULL);
    if (hDevMemHeap == IMG_NULL)
        return IMG_ERROR_INVALID_PARAMETERS;

    psDevMemTemplate = psDevMemContext->psDevMemTemplate;

    /* Allocate new memory info structure...*/
    psMemory = IMG_MALLOC(sizeof(TALMMU_sMemory));
    IMG_ASSERT(psMemory != IMG_NULL);
    if (psMemory == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    IMG_MEMSET(psMemory, 0, sizeof(TALMMU_sMemory));
    psMemory->psDevMemHeap     = psDevMemHeap;
    psMemory->psDevMemContext  = psDevMemContext;
    psMemory->bExtDevVirAddr   = bExtDevVirAddr;
    psMemory->hExtImportHandle = hExtImportHandle;

    /* We always for to be at least page aligned. */
    if ( ui32Alignment >= psDevMemTemplate->sDevMemInfo.ui32PageSize )
    {
        /* Alignment requirement specified by user is larger than page size - make sure alignment    */
        /* is a multiple of page size.                                                                */
        IMG_ASSERT ( (ui32Alignment % psDevMemTemplate->sDevMemInfo.ui32PageSize) == 0 );

        psMemory->ui32Alignment = ui32Alignment;
    }
    else
    {
        /* Alignment requirement specified by user is smaller than page size - make sure page size    */
        /* is a multiple of alignment.                                                                */
        if ( ui32Alignment != 0 )
        {
            IMG_ASSERT ( (psDevMemTemplate->sDevMemInfo.ui32PageSize % ui32Alignment) == 0 );
        }

        /* Now round up alignment to one page */
        psMemory->ui32Alignment  = psDevMemTemplate->sDevMemInfo.ui32PageSize;
    }

    /* Round size up to next multiple of physical pages */
    if (( ui32Size % psDevMemTemplate->sDevMemInfo.ui32PageSize ) != 0)
    {
        psMemory->ui32Size = ((ui32Size / psDevMemTemplate->sDevMemInfo.ui32PageSize) + 1) * psDevMemTemplate->sDevMemInfo.ui32PageSize;
    }
    else
    {
        psMemory->ui32Size = ui32Size;
    }

    /* If the device virtual address was externally defined...*/
    if (psMemory->bExtDevVirAddr)
    {
        /* Check alignment of the host and virtual address...*/
        IMG_ASSERT((((IMG_UINTPTR)pvCpuLinearAddr) & (psMemory->ui32Alignment-1)) == 0);
        IMG_ASSERT(((ui32DevVirtOffset) & (psMemory->ui32Alignment-1)) == 0);

        /* Check virtual address is within the heap...*/
        IMG_ASSERT(ui32DevVirtOffset >= psDevMemHeap->sHeapInfo.ui32BaseDevVirtAddr);
        IMG_ASSERT(ui32DevVirtOffset < (psDevMemHeap->sHeapInfo.ui32BaseDevVirtAddr + psDevMemHeap->sHeapInfo.ui32Size));

        /* Set the device virtual address...*/
        ui64DevOffset = ui32DevVirtOffset -  psDevMemHeap->sHeapInfo.ui32BaseDevVirtAddr;
    }
    else
    {
        /* Disable interrupts */
        //sOldIntMask = talmmu_DisableInt();

        ui32Result = ADDR_CxMalloc1Res(&psDevMemHeap->sContext, "", (psMemory->ui32Size + psDevMemHeap->ui32GuardBand), psMemory->ui32Alignment, &ui64DevOffset);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);

        /* Re-enable interupts */
        //talmmu_EnableInt(sOldIntMask);
    }

    psMemory->ui32DevVirtOffset = IMG_UINT64_TO_UINT32(ui64DevOffset);
    if (ui32Result != IMG_SUCCESS)
    {
        /* If heap space is unavaliable return NULL, the caller must handle this condition */
        //printf("Virtual Memory Heap (#%d) exhausted\n", psDevMemHeap->sHeapInfo.ui32HeapId);
        TALMMU_FREE( psMemory );
        return ui32Result;
    }

    /* If no user supplied memory...*/
    if (pvCpuLinearAddr == IMG_NULL)
    {
        /* Allocate CPU memory...*/
#if defined (__TALMMU_USE_PALLOC__)
        ui32Result = PALLOC_Alloc(psDevMemTemplate->sDevMemInfo.ui32AttachId,
                                  psMemory->ui32Size,
                                  psDevMemHeap->eMemAttrib,
                                  psDevMemHeap->eMemPool,
                                  &psMemory->pvCpuNonAlignedAddr,
                                  &psMemory->ui32AllocId);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto free_virt;
        }
        psMemory->pvCpuLinearAddr = psMemory->pvCpuNonAlignedAddr;

#elif defined (__TALMMU_USE_SYSAPIS__)
        {
            ui32Result = SYSMEMU_AllocatePages(psMemory->ui32Size,
                                               psDevMemHeap->eMemAttrib,
                                               psDevMemHeap->eMemPool,
                                               &psMemory->hSysMemHandle,
                                               IMG_NULL);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto free_virt;
            }

            SYSMEMU_GetCpuKmAddr((IMG_VOID **)&psMemory->pvCpuNonAlignedAddr, psMemory->hSysMemHandle);

            IMG_ASSERT(psMemory->pvCpuNonAlignedAddr != IMG_NULL);
            if (psMemory->pvCpuNonAlignedAddr == IMG_NULL)
            {
                ui32Result = IMG_ERROR_FATAL;
                goto free_sysmem;
            }

            psMemory->pvCpuLinearAddr = psMemory->pvCpuNonAlignedAddr;
        }
#elif defined (__TALMMU_USE_MALLOC__)
        psMemory->pvCpuNonAlignedAddr = IMG_MALLOC(psMemory->ui32Size + psMemory->ui32Alignment - 1);
        IMG_ASSERT(psMemory->pvCpuNonAlignedAddr != IMG_NULL);
        if (psMemory->pvCpuNonAlignedAddr == IMG_NULL)
        {
            ui32Result = IMG_ERROR_OUT_OF_MEMORY;
            goto free_virt;
        }
        psMemory->pvCpuLinearAddr = psMemory->pvCpuNonAlignedAddr;
        if (
                (psMemory->ui32Alignment > 1) &&
                (((IMG_UINTPTR)psMemory->pvCpuNonAlignedAddr % psMemory->ui32Alignment) != 0)
            )
        {
            psMemory->pvCpuLinearAddr = &(((IMG_CHAR*)psMemory->pvCpuNonAlignedAddr)[psMemory->ui32Alignment -(((IMG_UINTPTR)psMemory->pvCpuNonAlignedAddr) % psMemory->ui32Alignment)]);
        }
#else
    #error "No/wrong TALMMU alloc option defined!"
#endif
    }
    else
    {
#if defined (__TALMMU_USE_SYSAPIS__)
        /* Import the pages from external source. */
        ui32Result = SYSMEMU_DuplicateHandle(psMemory->ui32Size,
                                         hExtImportHandle,
                                         &psMemory->hSysMemHandle,
                                         (IMG_VOID **)&psMemory->pvCpuNonAlignedAddr);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto free_virt;
        }
        psMemory->pvCpuLinearAddr = psMemory->pvCpuNonAlignedAddr;
#else
        IMG_ASSERT(0);
#endif
    }

    /* Disable interrupts */
    sOldIntMask = talmmu_DisableInt();

    /* Add memory allocation to the list for this heap...*/
    /* If the heap is empty...*/
    if (LST_empty(&psDevMemHeap->sMemoryList))
    {
        /* Save flag to indicate whether the device virtual address is allocated internally or externally...*/
        psDevMemHeap->bExtDevVirAddr = psMemory->bExtDevVirAddr;
    }
    /* Once we have started allocating in one way ensure that we continue to do this...*/
    LST_add(&psDevMemHeap->sMemoryList, psMemory);

    /* Re-enable interupts */
    talmmu_EnableInt(sOldIntMask);

    /* If we are using tile mode in the framework a piece of host memory must be allocated
        to allow the video memory to be un-tiled */
    psMemory->pvDetileBuffer = psMemory->pvCpuLinearAddr;

#if defined  (__TALMMU_USE_TILE_TEST__) && !defined (__TALMMU_USE_MALLOC__)
    if ( psMemory->psDevMemHeap->sHeapInfo.bTiled == IMG_TRUE )
    {
        psMemory->pvDetileBuffer = IMG_MALLOC(psMemory->ui32Size + psMemory->ui32Alignment - 1);
    }
#endif /* (__TALMMU_USE_TILE_TEST__) && !defined (__TALMMU_USE_MALLOC__) */
    /* Return the memory structure as a handle...*/
    *phMemory = psMemory;

    /* Return success. */
    return IMG_SUCCESS;

free_sysmem:
    SYSMEMU_FreePages(psMemory->hSysMemHandle);
free_virt:
    ADDR_CxFree(&psDevMemHeap->sContext, "", psMemory->ui32DevVirtOffset);
    TALMMU_FREE(psMemory);
    return ui32Result;
}

/*!
******************************************************************************

 @Function                talmmu_DevMemMalloc

******************************************************************************/
static IMG_RESULT talmmu_DevMemMalloc(
    IMG_HANDLE    hDevMemContext,
    IMG_HANDLE    hDevMemHeap,
    IMG_UINT32    ui32Size,
    IMG_UINT32    ui32Alignment,
    IMG_VOID *    pvCpuLinearAddr,
    IMG_UINT32    ui32DevVirtOffset,
    IMG_BOOL      bExtDevVirAddr,
    IMG_HANDLE    hExtImportHandle,
    IMG_HANDLE *  phMemory
)
{
    IMG_UINT32            ui32Result;
    TALMMU_sDevMemHeap *  psDevMemHeap = hDevMemHeap;
    IMG_HANDLE            psMemory;
    if (psDevMemHeap->sHeapInfo.bTiled)
    {
       // Do we need to round up alignment and size if it is tiled?
       if ( ui32Alignment == 0 || psDevMemHeap->ui32TiledAlignment % ui32Alignment == 0)
       {
           ui32Alignment = psDevMemHeap->ui32TiledAlignment;
           ui32Size = (ui32Size + ui32Alignment - 1) & ~(ui32Alignment - 1);
       }
       else
       {
 //           printf("Alignment of 0x%08X is not compatible with required tile alignment of 0x%08x\n", ui32Alignment, psDevMemHeap->ui32TiledAlignment);
            IMG_ASSERT(psDevMemHeap->ui32TiledAlignment % ui32Alignment != 0);
       }

    }
    ui32Result = talmmu_DevMemMallocNonMap(hDevMemContext,
                                           hDevMemHeap,
                                           ui32Size,
                                           ui32Alignment,
                                           pvCpuLinearAddr,
                                           ui32DevVirtOffset,
                                           bExtDevVirAddr,
                                           hExtImportHandle,
                                           &psMemory);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Map the memory...*/
    ui32Result = TALMMU_DevMemMap(psMemory);
    if( ui32Result != IMG_SUCCESS)
    {
        TALMMU_DevMemFree1(psMemory);
        psMemory = IMG_NULL;
    }

    /* Return the memory structure as a handle...*/
    *phMemory = psMemory;

    /* Return success. */
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                TALMMU_DevMemMalloc

******************************************************************************/
IMG_RESULT TALMMU_DevMemMalloc(
    IMG_HANDLE    hDevMemContext,
    IMG_HANDLE    hDevMemHeap,
    IMG_UINT32    ui32Size,
    IMG_UINT32    ui32Alignment,
    IMG_HANDLE *  phMemory
)
{
    IMG_UINT32  ui32Result;

    ui32Result = talmmu_DevMemMalloc(hDevMemContext, hDevMemHeap, ui32Size, ui32Alignment, IMG_NULL, 0, IMG_FALSE, IMG_NULL, phMemory);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    return ui32Result;
}

/*!
******************************************************************************

 @Function                TALMMU_DevMemMalloc1

******************************************************************************/
IMG_RESULT TALMMU_DevMemMalloc1(
    IMG_HANDLE    hDevMemContext,
    IMG_UINT32    ui32HeapId,
    IMG_UINT32    ui32Size,
    IMG_UINT32    ui32Alignment,
    IMG_HANDLE *  phMemory
)
{
    IMG_UINT32  ui32Result;
    IMG_HANDLE  hDevMemHeap;

    ui32Result = TALMMU_GetHeapHandle(ui32HeapId, hDevMemContext, &hDevMemHeap);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    ui32Result = talmmu_DevMemMalloc(hDevMemContext, hDevMemHeap, ui32Size, ui32Alignment, IMG_NULL, 0, IMG_FALSE, IMG_NULL, phMemory);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(TALMMU_DevMemMalloc1)


/*!
******************************************************************************

 @Function                TALMMU_DevMemMalloc1NonMap

******************************************************************************/
IMG_RESULT TALMMU_DevMemMalloc1NonMap(
    IMG_HANDLE    hDevMemContext,
    IMG_UINT32    ui32HeapId,
    IMG_UINT32    ui32Size,
    IMG_UINT32    ui32Alignment,
    IMG_HANDLE *  phMemory
)
{
    IMG_UINT32  ui32Result;
    IMG_HANDLE  hDevMemHeap;

    ui32Result = TALMMU_GetHeapHandle(ui32HeapId, hDevMemContext, &hDevMemHeap);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    ui32Result = talmmu_DevMemMallocNonMap(hDevMemContext, hDevMemHeap, ui32Size, ui32Alignment, IMG_NULL, 0, IMG_FALSE, IMG_NULL, phMemory);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    return ui32Result;
}

/*!
******************************************************************************

 @Function                TALMMU_DevMemMapExtMem

******************************************************************************/
IMG_RESULT TALMMU_DevMemMapExtMem(
    IMG_HANDLE    hDevMemContext,
    IMG_HANDLE    hDevMemHeap,
    IMG_UINT32    ui32Size,
    IMG_UINT32    ui32Alignment,
    IMG_VOID *    pvCpuLinearAddr,
    IMG_HANDLE    hExtImportHandle,
    IMG_HANDLE *  phMemory
)
{
    IMG_UINT32  ui32Result;

    ui32Result = talmmu_DevMemMalloc(hDevMemContext,
                                     hDevMemHeap,
                                     ui32Size,
                                     ui32Alignment,
                                     pvCpuLinearAddr,
                                     0,
                                     IMG_FALSE,
                                     hExtImportHandle,
                                     phMemory);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(TALMMU_DevMemMapExtMem)


/*!
******************************************************************************

 @Function                TALMMU_DevMemMapExtMem1

******************************************************************************/
IMG_RESULT TALMMU_DevMemMapExtMem1(
    IMG_HANDLE    hDevMemContext,
    IMG_UINT32    ui32HeapId,
    IMG_UINT32    ui32Size,
    IMG_UINT32    ui32Alignment,
    IMG_VOID *    pvCpuLinearAddr,
    IMG_HANDLE    hExtImportHandle,
    IMG_HANDLE *  phMemory
)
{
    IMG_UINT32  ui32Result;
    IMG_HANDLE  hDevMemHeap;

    ui32Result = TALMMU_GetHeapHandle(ui32HeapId, hDevMemContext, &hDevMemHeap);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    ui32Result = talmmu_DevMemMalloc(hDevMemContext,
                                     hDevMemHeap,
                                     ui32Size,
                                     ui32Alignment,
                                     pvCpuLinearAddr,
                                     0,
                                     IMG_FALSE,
                                     hExtImportHandle,
                                     phMemory);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(TALMMU_DevMemMapExtMem1)

/*!
******************************************************************************

 @Function                TALMMU_DevMemMapExt1

******************************************************************************/
IMG_RESULT TALMMU_DevMemMapExt1(
    IMG_HANDLE    hDevMemContext,
    IMG_UINT32    ui32HeapId,
    IMG_VOID *    pvCpuLinearAddr,
    IMG_UINT32    ui32DevVirtOffset,
    IMG_UINT32    ui32Size,
    IMG_UINT32    ui32Alignment,
    IMG_HANDLE    hExtImportHandle,
    IMG_HANDLE *  phMemory
)
{
    IMG_UINT32  ui32Result;
    IMG_HANDLE  hDevMemHeap;

    ui32Result = TALMMU_GetHeapHandle(ui32HeapId, hDevMemContext, &hDevMemHeap);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    ui32Result = talmmu_DevMemMalloc(hDevMemContext,
                                     hDevMemHeap,
                                     ui32Size,
                                     ui32Alignment,
                                     pvCpuLinearAddr,
                                     ui32DevVirtOffset,
                                     IMG_TRUE,
                                     hExtImportHandle,
                                     phMemory);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    return ui32Result;
}

/*!
******************************************************************************

 @Function                TALMMU_DevMemFree

******************************************************************************/
IMG_RESULT TALMMU_DevMemFree(
    IMG_HANDLE  hDevMemContext,
    IMG_HANDLE  hMemory
)
{
     IMG_UINT32              ui32Result;
    TALMMU_sDevMemContext *  psDevMemContext = hDevMemContext;
    TALMMU_sMemory *         psMemory        = hMemory;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(hMemory != IMG_NULL);
    if (hMemory == IMG_NULL)
        return IMG_ERROR_GENERIC_FAILURE;
    IMG_ASSERT(psMemory->psDevMemContext = psDevMemContext);

    ui32Result = talmmu_DevMemFree(hDevMemContext, hMemory);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(TALMMU_DevMemFree)


/*!
******************************************************************************

 @Function                TALMMU_DevMemFree1

******************************************************************************/
IMG_RESULT TALMMU_DevMemFree1(
    IMG_HANDLE  hMemory
)
{
     IMG_UINT32       ui32Result;
    TALMMU_sMemory *  psMemory = hMemory;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(hMemory != IMG_NULL);
    if(hMemory == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    ui32Result = talmmu_DevMemFree(psMemory->psDevMemContext, hMemory);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    return ui32Result;
}

IMGVIDEO_EXPORT_SYMBOL(TALMMU_DevMemFree1)
/*!
******************************************************************************

 @Function                TALMMU_CpuMemMap

******************************************************************************/
IMG_RESULT TALMMU_CpuMemMap(
    IMG_HANDLE   hMemory,
    IMG_VOID **  pvMemory
)
{
    TALMMU_sMemory *  psMemory = hMemory;
    IMG_UINT32                ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(hMemory != IMG_NULL);
    if(hMemory == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    if (psMemory->pvDetileBuffer != IMG_NULL)
    {
        *pvMemory = psMemory->pvDetileBuffer;
    }
    else
    {
        *pvMemory = psMemory->pvCpuLinearAddr;
    }

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(TALMMU_CpuMemMap)


/*!
******************************************************************************

 @Function                TALMMU_GetAllocId

******************************************************************************/
IMG_RESULT TALMMU_GetAllocId(
    IMG_HANDLE  hMemory,
    IMG_UINT32  pui32AllocId
)
{
#if defined (__TALMMU_USE_PALLOC__)
   TALMMU_sMemory *  psMemory = hMemory;
#endif

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(hMemory != IMG_NULL);
#if defined (__TALMMU_USE_PALLOC__)
    *pui32AllocId = psMemory->ui32AllocId;
#else
    IMG_ASSERT(IMG_FALSE);
#endif

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                TALMMU_CpuMemUnmap

******************************************************************************/
IMG_RESULT TALMMU_CpuMemUnmap(
    IMG_HANDLE  hMemory
)
{
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                TALMMU_DevMemMap

******************************************************************************/
IMG_RESULT TALMMU_DevMemMap(
    IMG_HANDLE  hMemory
)
{
    IMG_UINT32                  ui32Result;
    TALMMU_sMemory *            psMemory = hMemory;
#if !defined (__TALMMU_NO_TAL__)
    TALMMU_sDevMemHeap *        psDevMemHeap;
#endif
//    TALMMU_sDevMemTemplate *    psDevMemTemplate;
    IMG_HANDLE                  hDevMemContext;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(!psMemory->bMapped);

#if !defined (__TALMMU_NO_TAL__)
   psDevMemHeap = psMemory->psDevMemHeap;
#endif
//    psDevMemTemplate = psDevMemHeap->psDevMemTemplate;
    hDevMemContext   = psMemory->psDevMemContext;

    /* Call function to process region...*/
    ui32Result = talmmu_ProcessMemoryRegion(psMemory, 0, psMemory->ui32Size, IMG_FALSE, talmmu_ProcessMemMap, 0, psMemory);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);

    if (ui32Result == IMG_SUCCESS)
    {
        psMemory->bMapped = IMG_TRUE;
#if !defined (__TALMMU_NO_TAL__)
        TALPDUMP_Comment( psDevMemHeap->hMemSpace, "TALMMU_DevMemMap: Page tables updated");
#endif
    }
    else
    {
        /* Memory no mapped...*/
        ui32Result = talmmu_ProcessMemoryRegion(psMemory, 0, psMemory->ui32Size, IMG_FALSE, talmmu_ProcessMemUnmap, 0, hDevMemContext);
    }
    return ui32Result;
}

/*!
******************************************************************************

 @Function                TALMMU_DevMemUnmap

******************************************************************************/
 IMG_RESULT TALMMU_DevMemUnmap(
    IMG_HANDLE  hMemory
)
{
    TALMMU_sMemory *          psMemory = hMemory;
//    TALMMU_sDevMemHeap *      psDevMemHeap;
//    TALMMU_sDevMemTemplate *  psDevMemTemplate;
    IMG_HANDLE                hDevMemContext;
    IMG_UINT32                ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psMemory->bMapped);

//    psDevMemHeap     = psMemory->psDevMemHeap;
//    psDevMemTemplate = psDevMemHeap->psDevMemTemplate;
    hDevMemContext   = psMemory->psDevMemContext;

    /* Call function to process region...*/
    ui32Result = talmmu_ProcessMemoryRegion(psMemory, 0, psMemory->ui32Size, IMG_FALSE, talmmu_ProcessMemUnmap, 0, hDevMemContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Memory no unmapped...*/
    psMemory->bMapped = IMG_FALSE;

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(TALMMU_DevMemUnmap)

/*!
******************************************************************************

 @Function                TALMMU_DevMemSetMapAttrib

******************************************************************************/
IMG_RESULT TALMMU_DevMemSetMapAttrib(
    IMG_HANDLE         hMemory,
    TALMMU_eMapAttrib  eMapAttrib
)
{
    TALMMU_sMemory *  psMemory = hMemory;
    IMG_UINT32        ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psMemory->bMapped);

    /* Call function to process region...*/
    ui32Result = talmmu_ProcessMemoryRegion(psMemory, 0, psMemory->ui32Size, IMG_TRUE,
                                            talmmu_ProcessMapAttrib, eMapAttrib, psMemory);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    return ui32Result;
}

/*!
******************************************************************************

 @Function                talmmu_ProcessExtBuffer

******************************************************************************/
static IMG_RESULT talmmu_ProcessExtBuffer (
    TALMMU_sDevMemHeap *  psDevMemHeap,
    TALMMU_sMemory *      psMemory,
    IMG_UINT32            ui32PageNo,
    IMG_CHAR *            pvPageMemory,
    IMG_CHAR *            pvCpuLinearAddr,
    IMG_UINT32            ui32ByteInPage,
    IMG_UINT32            ui32BytesToProcess,
    IMG_UINT32            ui32BytesProcessed,
    IMG_UINT32            ui32Param,
    IMG_VOID *            pvParam
)
{
    IMG_BOOL    bToMemory = ui32Param;
    IMG_CHAR *  pcBuffer = pvParam;

    /* If Buffer to Memory ...*/
    if (bToMemory)
    {
        // Copy from buffer to memory
        IMG_MEMCPY(pvCpuLinearAddr, pcBuffer + ui32BytesProcessed, ui32BytesToProcess);
    }
    else
    {
        // Copy from memory to buffer
        IMG_MEMCPY(pcBuffer + ui32BytesProcessed, pvCpuLinearAddr, ui32BytesToProcess);
    }
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                TALMMU_CopyTileBuffer

******************************************************************************/
IMG_RESULT TALMMU_CopyTileBuffer(
    IMG_HANDLE  hMemory,
    IMG_UINT32  ui32Offset,
    IMG_UINT32  ui32Size,
    IMG_CHAR *  pcBuffer,
    IMG_BOOL    bToMemory
)
{
    TALMMU_sMemory *  psMemory = hMemory;
    IMG_UINT32        ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psMemory->bMapped);
    IMG_ASSERT((ui32Offset+ui32Size) <= psMemory->ui32Size);

    /* Call function to process region...*/
    ui32Result = talmmu_ProcessMemoryRegion(psMemory, ui32Offset, ui32Size, IMG_TRUE, talmmu_ProcessExtBuffer, bToMemory, pcBuffer);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(TALMMU_CopyTileBuffer)


#if !defined (__TALMMU_NO_TAL__)
/*!
******************************************************************************

 @Function                TALMMU_WriteDevMemRef

******************************************************************************/
IMG_RESULT TALMMU_WriteDevMemRef(
    IMG_HANDLE  hMemSpace,
    IMG_UINT32  ui32Offset,
    IMG_HANDLE  hRefMemory,
    IMG_UINT32  ui32RefOffset
)
{
    return TALMMU_WriteDevMemRefWithBitPattern(hMemSpace, ui32Offset, hRefMemory, ui32RefOffset, 0);
}

/*!
******************************************************************************

 @Function                TALMMU_WriteDevMemRefWithBitPattern

******************************************************************************/
IMG_RESULT TALMMU_WriteDevMemRefWithBitPattern(
    IMG_HANDLE  hMemSpace,
    IMG_UINT32  ui32Offset,
    IMG_HANDLE  hRefMemory,
    IMG_UINT32  ui32RefOffset,
    IMG_UINT32  ui32BitPattern
)
{
    TALMMU_sMemory *          psRefMemory = hRefMemory;
//    TALMMU_sDevMemTemplate *  psDevMemTemplate;
    TALMMU_sDevMemHeap *      psDevMemHeap;
    IMG_UINT32                ui32Value;
    IMG_UINT32                ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psRefMemory->bMapped);
    IMG_ASSERT(ui32RefOffset < psRefMemory->ui32Size);

    psDevMemHeap     = psRefMemory->psDevMemHeap;
//    psDevMemTemplate = psDevMemHeap->psDevMemTemplate;

    ui32Value = psDevMemHeap->sHeapInfo.ui32BaseDevVirtAddr + psRefMemory->ui32DevVirtOffset + ui32RefOffset;
    ui32Value |= ui32BitPattern;

    ui32Result = TALREG_WriteWord32(hMemSpace, ui32Offset, ui32Value);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);

    return ui32Result;
}

/*!
******************************************************************************

 @Function                TALMMU_CirBufPollDevMem

******************************************************************************/
IMG_RESULT TALMMU_CirBufPollDevMem(
    IMG_HANDLE  hDeviceMem,
    IMG_UINT32  ui32Offset,
    IMG_UINT32  ui32WriteOffsetVal,
    IMG_UINT32  ui32PacketSize,
    IMG_UINT32  ui32BufferSize
)
{
    TALMMU_sMemory *          psMemory = hDeviceMem;
    TALMMU_sDevMemHeap *      psDevMemHeap;
    TALMMU_sDevMemTemplate *  psDevMemTemplate;
    IMG_UINT32                ui32PageNo;
    IMG_UINT32                ui32PageTableNo;
    IMG_UINT32                ui32IndexInPageTable;
    IMG_UINT32                ui32ByteInPage;
    IMG_UINT32                ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psMemory->bMapped);
    IMG_ASSERT(ui32Offset < psMemory->ui32Size);

    psDevMemHeap     = psMemory->psDevMemHeap;
    psDevMemTemplate = psDevMemHeap->psDevMemTemplate;

    ui32PageNo           = (psMemory->ui32DevVirtOffset + ui32Offset) >> psDevMemTemplate->ui32PageNoShift;
    ui32PageTableNo      = ui32PageNo >> psDevMemTemplate->ui32PageTableNoShift;
    ui32IndexInPageTable = ui32PageNo & psDevMemTemplate->ui32IndexInPageTableMask;
    ui32ByteInPage       = (psMemory->ui32DevVirtOffset + ui32Offset) & psDevMemTemplate->ui32ByteInPageMask;

    IMG_ASSERT(psDevMemHeap->pasPageTable != IMG_NULL);
    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo] != IMG_NULL);

    /* Should have TAL handles for this page and reference count...*/
    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable]  != IMG_NULL);

    ui32Result = TALMEM_CircBufPoll32(psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable],
                                      ui32ByteInPage,
                                      ui32WriteOffsetVal,
                                      ui32PacketSize,
                                      ui32BufferSize,
                                      0,
                                      0);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    return ui32Result;
}

/*!
******************************************************************************

 @Function                TALMMU_PollDevMem

******************************************************************************/
IMG_RESULT TALMMU_PollDevMem(
    IMG_HANDLE  hMemory,
    IMG_UINT32  ui32Offset,
    IMG_UINT32  ui32CheckFuncIdExt,
    IMG_UINT32  ui32RequValue,
    IMG_UINT32  ui32Enable,
    IMG_UINT32  ui32PollCount,
    IMG_UINT32  ui32TimeOut
)
{
    TALMMU_sMemory *          psMemory = hMemory;
    TALMMU_sDevMemHeap *      psDevMemHeap;
    TALMMU_sDevMemTemplate *  psDevMemTemplate;
    IMG_UINT32                ui32PageNo;
    IMG_UINT32                ui32PageTableNo;
    IMG_UINT32                ui32IndexInPageTable;
    IMG_UINT32                ui32ByteInPage;
    IMG_UINT32                ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psMemory->bMapped);
    IMG_ASSERT(ui32Offset < psMemory->ui32Size);

    psDevMemHeap     = psMemory->psDevMemHeap;
    psDevMemTemplate = psDevMemHeap->psDevMemTemplate;

    ui32PageNo           = (psMemory->ui32DevVirtOffset + ui32Offset) >> psDevMemTemplate->ui32PageNoShift;
    ui32PageTableNo      = ui32PageNo >> psDevMemTemplate->ui32PageTableNoShift;
    ui32IndexInPageTable = ui32PageNo & psDevMemTemplate->ui32IndexInPageTableMask;
    ui32ByteInPage       = (psMemory->ui32DevVirtOffset + ui32Offset) & psDevMemTemplate->ui32ByteInPageMask;

    IMG_ASSERT(psDevMemHeap->pasPageTable != IMG_NULL);
    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo] != IMG_NULL);

    /* Should have TAL handles for this page and reference count...*/
    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable]  != IMG_NULL);

    ui32Result = TALMEM_Poll32(psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable],
                               ui32ByteInPage,
                               ui32CheckFuncIdExt,
                               ui32RequValue,
                               ui32Enable,
                               ui32PollCount,
                               ui32TimeOut);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);

    return ui32Result;
}

/*!
******************************************************************************

 @Function                talmmu_ProcessCopy

******************************************************************************/
static IMG_RESULT talmmu_ProcessCopy (
    TALMMU_sDevMemHeap *  psDevMemHeap,
    TALMMU_sMemory *      psMemory,
    IMG_UINT32            ui32PageNo,
    IMG_CHAR *            pvPageMemory,
    IMG_CHAR *            pvCpuLinearAddr,
    IMG_UINT32            ui32ByteInPage,
    IMG_UINT32            ui32BytesToProcess,
    IMG_UINT32            ui32BytesProcessed,
    IMG_UINT32            ui32Param,
    IMG_VOID *            pvParam
)
{
    IMG_BOOL    bHostToDeviceMem = ui32Param;
    IMG_UINT32  ui32PageTableNo;
    IMG_UINT32  ui32IndexInPageTable;
    IMG_UINT32  ui32Result;

    ui32PageTableNo      = ui32PageNo >>psDevMemHeap->psDevMemTemplate->ui32PageTableNoShift;
    ui32IndexInPageTable = ui32PageNo & psDevMemHeap->psDevMemTemplate->ui32IndexInPageTableMask;

    IMG_ASSERT(psDevMemHeap->pasPageTable != IMG_NULL);
    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo] != IMG_NULL);

    /* Should have TAL handles for this page and reference count...*/
    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable]  != IMG_NULL);

    /* If host to device...*/
    if (bHostToDeviceMem)
    {
#if defined (__TALMMU_USE_MALLOC__)
        IMG_MEMCPY(pvPageMemory, pvCpuLinearAddr, ui32BytesToProcess);
#endif
        ui32Result = TALMEM_UpdateDeviceRegion(psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable],
                                               ui32ByteInPage,
                                               ui32BytesToProcess);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }
    else
    {
        /* Device to host...*/
        ui32Result = TALMEM_UpdateHostRegion(psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable],
                                             ui32ByteInPage,
                                             ui32BytesToProcess);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
#if defined (__TALMMU_USE_MALLOC__) || defined (__TALMMU_USE_TILE_TEST__)
        IMG_MEMCPY(pvCpuLinearAddr, pvPageMemory, ui32BytesToProcess);
#endif
    }
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                talmmu_CopyMemRegion

******************************************************************************/
static IMG_RESULT talmmu_CopyMemRegion(
    IMG_HANDLE  hMemory,
    IMG_UINT32  ui32Offset,
    IMG_UINT32  ui32Size,
    IMG_BOOL    bHostToDeviceMem
)
{
    TALMMU_sMemory *          psMemory = hMemory;
//    TALMMU_sDevMemHeap *      psDevMemHeap;
//    TALMMU_sDevMemTemplate *  psDevMemTemplate;
    IMG_UINT32                ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psMemory->bMapped);
    IMG_ASSERT((ui32Offset+ui32Size) <= psMemory->ui32Size);

//    psDevMemHeap     = psMemory->psDevMemHeap;
//    psDevMemTemplate = psDevMemHeap->psDevMemTemplate;

    /* Call function to process region...*/
    ui32Result = talmmu_ProcessMemoryRegion(psMemory, ui32Offset, ui32Size, IMG_TRUE, talmmu_ProcessCopy, bHostToDeviceMem, IMG_NULL);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    return ui32Result;
}


/*!
******************************************************************************

 @Function                TALMMU_CopyHostToDevMem

******************************************************************************/
IMG_RESULT TALMMU_CopyHostToDevMem(
    IMG_HANDLE  hMemory
)
{
    TALMMU_sMemory *  psMemory = hMemory;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psMemory->bMapped);

    TALMMU_CopyHostToDevMemRegion(psMemory, 0, psMemory->ui32Size);

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                TALMMU_CopyHostToDevMemRegion

******************************************************************************/
IMG_RESULT TALMMU_CopyHostToDevMemRegion(
    IMG_HANDLE  hMemory,
    IMG_UINT32  ui32Offset,
    IMG_UINT32  ui32Size
)
{
    return talmmu_CopyMemRegion(hMemory, ui32Offset, ui32Size, IMG_TRUE);
}

/*!
******************************************************************************

 @Function                TALMMU_CopyDevMemToHost

******************************************************************************/
IMG_RESULT TALMMU_CopyDevMemToHost(
    IMG_HANDLE  hMemory
)
{
    TALMMU_sMemory *  psMemory = hMemory;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psMemory->bMapped);

    TALMMU_CopyDevMemToHostRegion(hMemory, 0, psMemory->ui32Size);

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                TALMMU_CopyDevMemToHostRegion

******************************************************************************/
IMG_RESULT TALMMU_CopyDevMemToHostRegion(
    IMG_HANDLE  hMemory,
    IMG_UINT32  ui32Offset,
    IMG_UINT32  ui32Size
)
{
    return talmmu_CopyMemRegion(hMemory, ui32Offset, ui32Size, IMG_FALSE);
}
#endif

/*!
******************************************************************************

 @Function              TALMMU_GetDevVirtAddress

******************************************************************************/
IMG_RESULT TALMMU_GetDevVirtAddress(
    IMG_HANDLE    hMemory,
    IMG_UINT32 *  pui32DevVirt
)
{
    TALMMU_sMemory *      psMemory = hMemory;
    TALMMU_sDevMemHeap *  psDevMemHeap;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(hMemory);
    if(hMemory == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    psDevMemHeap = psMemory->psDevMemHeap;

    *pui32DevVirt = (psDevMemHeap->sHeapInfo.ui32BaseDevVirtAddr + psMemory->ui32DevVirtOffset);

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(TALMMU_GetDevVirtAddress)


/*!
******************************************************************************

 @Function              TALMMU_GetDevHeapId

******************************************************************************/
IMG_RESULT TALMMU_GetDevHeapId(
    IMG_HANDLE    hMemory,
    IMG_UINT32 *  pui32HeapId
)
{
    TALMMU_sMemory *      psMemory = hMemory;
    TALMMU_sDevMemHeap *  psDevMemHeap;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psMemory->bMapped);

    psDevMemHeap = psMemory->psDevMemHeap;

    *pui32HeapId = (psDevMemHeap->sHeapInfo.ui32HeapId);

    /* Return success. */
    return IMG_SUCCESS;
}


#if !defined (__TALMMU_NO_TAL__)
/*!
******************************************************************************

 @Function                TALMMU_DevMemWriteDevMemRef

******************************************************************************/
IMG_RESULT TALMMU_DevMemWriteDevMemRef(
    IMG_HANDLE  hMemory,
    IMG_UINT32  ui32Offset,
    IMG_HANDLE  hRefMemory,
    IMG_UINT32  ui32RefOffset
)
{
    return TALMMU_DevMemWriteDevMemRefWithBitPattern(hMemory, ui32Offset, hRefMemory, ui32RefOffset, 0);
}

/*!
******************************************************************************

 @Function                TALMMU_DevMemWriteDevMemRefWithBitPattern

******************************************************************************/
IMG_RESULT TALMMU_DevMemWriteDevMemRefWithBitPattern(
    IMG_HANDLE  hMemory,
    IMG_UINT32  ui32Offset,
    IMG_HANDLE  hRefMemory,
    IMG_UINT32  ui32RefOffset,
    IMG_UINT32  ui32BitPattern
)
{
    TALMMU_sMemory *          psMemory    = hMemory;
//    TALMMU_sDevMemHeap *      psDevMemHeap;
//    TALMMU_sDevMemTemplate *  psDevMemTemplate;
    TALMMU_sMemory *          psRefMemory = hRefMemory;
    TALMMU_sDevMemHeap *      psRefDevMemHeap;
//    TALMMU_sDevMemTemplate *  psRefDevMemContext;
    IMG_UINT32                ui32Value;
    IMG_UINT32 *              pui32CpuLinearMem;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psMemory->bMapped);
    IMG_ASSERT(ui32Offset < psMemory->ui32Size);
    IMG_ASSERT(psRefMemory->bMapped);
    IMG_ASSERT(psMemory->pvCpuLinearAddr != 0);
    IMG_ASSERT(ui32RefOffset < psRefMemory->ui32Size);

//    psDevMemHeap     = psMemory->psDevMemHeap;
//    psDevMemTemplate = psDevMemHeap->psDevMemTemplate;

    psRefDevMemHeap    = psRefMemory->psDevMemHeap;
//    psRefDevMemContext = psRefDevMemHeap->psDevMemTemplate;

    ui32Value = psRefDevMemHeap->sHeapInfo.ui32BaseDevVirtAddr + psRefMemory->ui32DevVirtOffset + ui32RefOffset;
    ui32Value |= ui32BitPattern;

    /* Put reference into CPU linear region...*/
    pui32CpuLinearMem = (IMG_UINT32 *) &(((IMG_CHAR *)psMemory->pvCpuLinearAddr)[ui32Offset]);
    IMG_ASSERT(((IMG_UINTPTR)pui32CpuLinearMem & 0x3) == 0);
    *pui32CpuLinearMem = ui32Value;

    /* Update the region...*/
    return talmmu_CopyMemRegion(hMemory, ui32Offset, 4, IMG_TRUE);
}
#endif

/*!
******************************************************************************

 @Function                TALMMU_GetTilingSetup

******************************************************************************/
IMG_RESULT TALMMU_GetTilingSetup(
    IMG_HANDLE                  hDevMemTemplate,
    IMG_UINT32                  ui32BufferStride,
    IMG_UINT32                  ui32BufferHeight,
    TALMMU_sTilingParameters *  psTilingParameters )
{
    IMG_UINT32                ui32LineStride_NextHighestPowerOfTwo;
    IMG_UINT32                ui32TileHeight;
    IMG_UINT32                ui32TileWidth;
    IMG_UINT32                ui32BitsInTilingFieldRange;
    IMG_UINT32                ui32CorrectedLineStrideInTiles;
    IMG_UINT32                ui32TileRangeAsAPowerOfTwo;
    TALMMU_sDevMemTemplate *  psDevMemTemplate;
    IMG_UINT32                ui32Result;

    IMG_ASSERT ( hDevMemTemplate != IMG_NULL );
    if(hDevMemTemplate == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    IMG_ASSERT ( psTilingParameters != IMG_NULL );
    if(psTilingParameters == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    IMG_ASSERT ( ui32BufferStride > 0 );
    IMG_ASSERT ( ui32BufferHeight > 0 );

    /* Get access to descriptor for physical memory */
    psDevMemTemplate = (TALMMU_sDevMemTemplate *) hDevMemTemplate;

    /* Establish tile width and height */
    IMG_ASSERT ( psDevMemTemplate->ui32YRowWithinTileShift > 0 );
    ui32TileHeight = (1 << psDevMemTemplate->ui32YRowWithinTileShift);
    IMG_ASSERT ( psDevMemTemplate->ui32TileRowShift > 0 );
    ui32TileWidth = (1 << psDevMemTemplate->ui32TileRowShift);
    IMG_ASSERT ( psDevMemTemplate->ui32TileWidth == ui32TileWidth );

    /* Correct procedure for selecting tile & image strides    is    */
    /* as follows:                                                */
    /* 1) Establish image width in bytes (e.g:1500 bytes)        */
    /* 2) What is next highest power of two which is also a        */
    /*      multiple of the tile width? (e.g.: 2^11 = 2048).        */
    if ( ui32BufferStride <= ui32TileWidth )
    {
        /* If buffer width is less than one tile wide, then just round up to a single tile */
        ui32LineStride_NextHighestPowerOfTwo = ui32TileWidth;
    }
    else
    {
        ui32LineStride_NextHighestPowerOfTwo = talmmu_NextHighestPowerOfTwo ( ui32BufferStride );
    }
    IMG_ASSERT ( (ui32LineStride_NextHighestPowerOfTwo % ui32TileWidth) == 0 );
    ui32CorrectedLineStrideInTiles = ui32LineStride_NextHighestPowerOfTwo / ui32TileWidth;

    /* 3) Tile stride (X field width) must be set to            */
    /*      ((power of two used in step 2) - 1)                    */
    /*      (e.g.: 2 in this case, as we established that 2^3        */
    /*      tiles gave us the next highest boundary, so the power */
    /*    of two used was 3, hence we use a tile stride of 2    */
    /*    (as this equates to an X field width of 3 bits).        */
    ui32TileRangeAsAPowerOfTwo = talmmu_WhatPowerOfTwoIsThis ( ui32CorrectedLineStrideInTiles );
    if ( ui32TileRangeAsAPowerOfTwo == 0 )
    {
        /* The minimum number of bits we can assign to the number of tiles per line is 1 */
        ui32TileRangeAsAPowerOfTwo = 1;
    }
    psTilingParameters->ui32TileStride = (ui32TileRangeAsAPowerOfTwo-1);
    psTilingParameters->ui32RoundedLineStride = ui32CorrectedLineStrideInTiles * ui32TileWidth;

    /* 4) Base address alignment must be set such that no bits    */
    /*      are set within the tiling field ranges (X and Y        */
    /*      fields - see below).                                    */
    ui32BitsInTilingFieldRange = psDevMemTemplate->ui32TileRowShift +
                                 ui32TileRangeAsAPowerOfTwo +
                                 psDevMemTemplate->ui32YRowWithinTileShift;
    psTilingParameters->ui32BaseAddressAlignment = (1<<ui32BitsInTilingFieldRange);

    /* 5) Buffer height must be a multiple of the tile height    */
    if (( ui32BufferHeight % ui32TileHeight ) != 0 )
    {
        psTilingParameters->ui32RoundedBufferHeight = ((ui32BufferHeight / ui32TileHeight) + 1) * ui32TileHeight;
    }
    else
    {
        psTilingParameters->ui32RoundedBufferHeight = ui32BufferHeight;
    }

    /* Return success. */
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                TALMMU_ConvertTileStride

******************************************************************************/
IMG_RESULT    TALMMU_ConvertTileStride(
    IMG_HANDLE    hDevMemContext,
    IMG_UINT32    ui32XTileStride,
    IMG_UINT32 *  pui32TileStride
)
{
     // This should perhaps be moved to the MMU API and called from there
    TALMMU_sDevMemContext *   psDevMemContext = hDevMemContext;
    TALMMU_sDevMemTemplate *  psDevMemTemplate = psDevMemContext->psDevMemTemplate;
    switch (psDevMemTemplate->sDevMemInfo.eTilingScheme)
    {
    case 1:
        *pui32TileStride = 512 << ( ui32XTileStride + 1 );
        break;
    case 0:
        *pui32TileStride = 256 << ( ui32XTileStride + 1 );
        break;
    default:
        IMG_ASSERT(IMG_FALSE);
        *pui32TileStride = 0;
    }

    /* Return success. */
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                TALMMU_AddCallback

******************************************************************************/
IMG_RESULT TALMMU_AddCallback(
    IMG_HANDLE               hDevMemTemplate,
    TALMMU_pfnEventCallback  pfnEventCallback,
    IMG_VOID *               pCallbackParameter
)
{
    TALMMU_sDevMemTemplate *  psDevMemTemplate = hDevMemTemplate;
    IMG_UINT32                ui32Result;

    IMG_ASSERT(hDevMemTemplate != IMG_NULL);
    if(hDevMemTemplate == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    IMG_ASSERT(psDevMemTemplate->pfnEventCallback == IMG_NULL);
    psDevMemTemplate->pfnEventCallback   = pfnEventCallback;
    psDevMemTemplate->pCallbackParameter = pCallbackParameter;

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(TALMMU_AddCallback)

/*!
******************************************************************************

 @Function                TALMMU_RemoveCallback

******************************************************************************/
IMG_RESULT TALMMU_RemoveCallback(
    IMG_HANDLE  hDevMemTemplate
)
{
    TALMMU_sDevMemTemplate *  psDevMemTemplate = hDevMemTemplate;
    IMG_UINT32                ui32Result;

    IMG_ASSERT(hDevMemTemplate != IMG_NULL);
    if(hDevMemTemplate == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        return ui32Result;
    }

    IMG_ASSERT(psDevMemTemplate->pfnEventCallback != IMG_NULL);
    psDevMemTemplate->pfnEventCallback = IMG_NULL;

    return IMG_SUCCESS;
}


#if !defined (__TALMMU_NO_TAL__)
/*!
******************************************************************************

 @Function                talmmu_ProcessGetDevPhysAdd

******************************************************************************/
IMG_RESULT talmmu_ProcessGetDevPhysAddr (
    TALMMU_sDevMemHeap *  psDevMemHeap,
    TALMMU_sMemory *      psMemory,
    IMG_UINT32            ui32PageNo,
    IMG_CHAR *            pvPageMemory,
    IMG_CHAR *            pvCpuLinearAddr,
    IMG_UINT32            ui32ByteInPage,
    IMG_UINT32            ui32BytesToProcess,
    IMG_UINT32            ui32BytesProcessed,
    IMG_UINT32            ui32Param,
    IMG_VOID *            pvParam
)
{
    IMG_UINT32    ui32PageTableNo;
    IMG_UINT32    ui32IndexInPageTable;
    IMG_UINT64 *  pui64DevPhysAddr = pvParam;
    IMG_UINT64    ui64DevPhysAddr;

    ui32PageTableNo      = ui32PageNo >> psDevMemHeap->psDevMemTemplate->ui32PageTableNoShift;
    ui32IndexInPageTable = ui32PageNo & psDevMemHeap->psDevMemTemplate->ui32IndexInPageTableMask;

    IMG_ASSERT(psDevMemHeap->pasPageTable != IMG_NULL);
    IMG_ASSERT(psDevMemHeap->pasPageTable[ui32PageTableNo] != IMG_NULL);

    ui64DevPhysAddr = TALDEBUG_GetDevMemAddress(psDevMemHeap->pasPageTable[ui32PageTableNo]->ahMemTalHandles[ui32IndexInPageTable]);

    *pui64DevPhysAddr = ui64DevPhysAddr;

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                TALMMU_GetDevPhysAdd

******************************************************************************/
IMG_RESULT TALMMU_GetDevPhysAddr(
    IMG_HANDLE    hMemory,
    IMG_UINT64 *  pui64DevPhysAddr
)
{
    TALMMU_sMemory *  psMemory = hMemory;
    IMG_UINT32        ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(hMemory);

    ui32Result = talmmu_ProcessMemoryRegion(psMemory, 0, 4, IMG_TRUE, talmmu_ProcessGetDevPhysAddr, 0, pui64DevPhysAddr);
     IMG_ASSERT(ui32Result == IMG_SUCCESS);
    return ui32Result;
}
#endif
