/*!
 *****************************************************************************
 *
 * @File       talmmu_api.h
 * @Description    TAL MMU Extensions.
 *  The TALMMU extensions sit on top of the normal TAL functions and provide an
 *  abstraction that allows MMU memory mapping and setup to be generated.
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

#if !defined (__TALMMU_API_H__)
#define __TALMMU_API_H__

#include <img_errors.h>
#include <img_types.h>
#include <img_defs.h>
#include <img_mem.h>

#if !defined (__TALMMU_USE_MALLOC__)
#include <system.h>
#endif

#if defined (__cplusplus)
extern "C" {
#endif

    
/*!
******************************************************************************
  This type defines the MMU tiling scheme
******************************************************************************/
typedef enum
{
    TALMMU_MMUTILING_SCHEME_0 = 0,  
    TALMMU_MMUTILING_SCHEME_1 = 1
} TALMMU_eMMUTilingScheme;


/*!
******************************************************************************
  This type defines the MMU type
  Note: This should in sync with what is there in mmu.h MMU_Types
******************************************************************************/
typedef enum
{
    TALMMU_MMUTYPE_4K_PAGES_32BIT_ADDR  = 0x1,  //!< Support for 4kb pages and 32-bit address range
    TALMMU_MMUTYPE_VAR_PAGES_32BIT_ADDR,		//!< Support for variable size pages and 32-bit address range (not yet supported by TALLMMU)
    TALMMU_MMUTYPE_4K_PAGES_36BIT_ADDR,			//!< Support for 4kb pages and 36-bit address range
	TALMMU_MMUTYPE_4K_PAGES_40BIT_ADDR,			//!< Fixed 4K page size MMU with 40bit addresses
	TALMMU_MMUTYPE_VP_40BIT					    //!< Variable page size MMU with 40bit virtual and device addressing

} TALMMU_eMMUType;

/*!
******************************************************************************
  This type defines the device flags - bit flags that can be combined
******************************************************************************/
typedef enum
{
    TALMMU_DEVFLAGS_NONE = 0x0,  //!< None set

} TALMMU_eDevFlags;

/*!
******************************************************************************
  This structure contains the device memory information.
******************************************************************************/
typedef struct
{
    IMG_UINT32              ui32DeviceId;				//!< Device id.
    TALMMU_eMMUType         eMMUType;                   //!< MMU Type.
    TALMMU_eMMUTilingScheme eTilingScheme;              //!< Tiling Scheme to be used
    TALMMU_eDevFlags        eDevFlags;                  //!< Device flags - bit flags that can be combined
    IMG_CHAR *              pszPageDirMemSpaceName;		//!< Name of the memory space for page directory allocations
    IMG_CHAR *              pszPageTableMemSpaceName;	//!< Name of the memory space for page table allocations
	IMG_UINT32  			ui32PageSize;				//!< Page size (in bytes)
	IMG_UINT32				ui32PageTableDirAlignment;	//!< Page Table Directory Alignment (in bytes - must be multiple of Page size)

/*** Used when __TALMMU_USE_PALLOC__ and __TALMMU_USE_SYSMEM__ defined ***/
	SYS_eMemAttrib			eMemAttrib;					//!< Memory attribute
	SYS_eMemPool			eMemPool;					//!< Memory pool

/*** Used when __TALMMU_USE_SYSMEM__ defined ***/
    IMG_CHAR *              pszDeviceName;				//!< Pointer to device name
	
/*** Used when __TALMMU_USE_PALLOC__ defined ***/
	IMG_UINT32				ui32AttachId;				//!< PALLOC attachment Id	

} TALMMU_sDevMemInfo;

/*!
******************************************************************************
  This type defines the heap type
******************************************************************************/
typedef enum
{
    TALMMU_HEAP_SHARED_EXPORTED,        //!< Shared and exported
    TALMMU_HEAP_PERCONTEXT,             //!< Per context heap

} TALMMU_eHeapType;

/*!
******************************************************************************
  This type defines the heap flags - bit flags that can be combined
******************************************************************************/
typedef enum
{
    TALMMU_HEAPFLAGS_NONE = 0x0,                            //!< None set
    TALMMU_HEAPFLAGS_SET_CACHE_CONSISTENCY = 0x00000001,    //!< Set cache consistency
	TALMMU_HEAPFLAGS_128BYTE_INTERLEAVE = 0x00000002,		//!< 128byte interleaving
    TALMMU_HEAPFLAGS_256BYTE_INTERLEAVE = 0x00000004		//!< 256byte interleaving

} TALMMU_eHeapFlags;

/*!
******************************************************************************
  This structure contains the device memory heap information.

  NOTE: pvBaseCpuVirtAddr and ui32BaseDevVirtAddr should be page aligned.
  NOTE: ui32Size should be an integral number of pages.
******************************************************************************/
typedef struct
{
    IMG_UINT32              ui32HeapId;         //!< Heap id.
    TALMMU_eHeapType        eHeapType;          //!< Heap type
    TALMMU_eHeapFlags       eHeapFlags;         //!< Heap flags - bit flags that can be combined
    IMG_CHAR *              pszMemSpaceName;    //!< Name of the memory space for memory allocations
    IMG_UINT32              ui32BaseDevVirtAddr;//!< Base device virtual address
    IMG_UINT32              ui32Size;           //!< size (in bytes)
    IMG_BOOL                bTiled;             //!< IMG_TRUE if the heap is tiled
    IMG_UINT32              ui32XTileStride;     //!< Tile stride - only used if bTiled == IMG_TRUE
    IMG_UINT32              ui32TiledRegionNo;  //!< Tiled region number used with TAL_MmuSetTiledRegion()

} TALMMU_sHeapInfo;

/*!
******************************************************************************
  This type defines the map attribute flags - bit flags that can be combined
******************************************************************************/
typedef enum
{
    TALMMU_MAPATTRIB_NONE = 0x0,                             //!< None set
    TALMMU_MAPATTRIB_SET_CACHE_CONSISTENCY   = 0x00000001,   //!< Set cache consistency
    TALMMU_MAPATTRIB_SET_READ_ONLY           = 0x00000002,   //!< Set read only
    TALMMU_MAPATTRIB_SET_WRITE_ONLY          = 0x00000004,   //!< Set write only

} TALMMU_eMapAttrib;

/*!
******************************************************************************
  This structure describes the appropriate parameters for setting up a
  tiled region and buffers within that region, based on a desired line
  stride for those buffers.
******************************************************************************/
typedef struct
{
	IMG_UINT32	ui32RoundedLineStride;
	IMG_UINT32	ui32RoundedBufferHeight;
	IMG_UINT32	ui32BaseAddressAlignment;
	IMG_UINT32	ui32TileStride;

} TALMMU_sTilingParameters;
    
/*!
******************************************************************************
 This type defines the event types for the TALMMU callbacks
******************************************************************************/
typedef enum
{
	/*! Function to flush the cache.		*/
	TALMMU_EVENT_FLUSH_CACHE,
	/*! Function to write the page directory address to the device */
	TALMMU_EVENT_WRITE_PAGE_DIRECTORY_REF,

	/* Placeholder*/
	TALMMU_NO_OF_EVENTS

} TALMMU_eEvent;

/*!
******************************************************************************
 This type defines extra heap options which can be added using the options function
******************************************************************************/
typedef enum
{
	/*! Add guard band to all mallocs */
	TALMMU_HEAP_OPT_ADD_GUARD_BAND,
	TALMMU_HEAP_OPT_SET_MEM_ATTRIB,
	TALMMU_HEAP_OPT_SET_MEM_POOL,

	/* Placeholder*/
	TALMMU_NO_OF_OPTIONS

} TALMMU_eHeapOptionId;

typedef struct
{
	IMG_UINT32 ui32GuardBand;
}TALMMU_sGuardBandOptions, *psTALMMU_sGuardBandOptions;


typedef union
{
	TALMMU_sGuardBandOptions	sGuardBandOpt;				//!< Guardband parameters

/*** Used when __TALMMU_USE_PALLOC__ and __TALMMU_USE_SYSMEM__ defined ***/
	SYS_eMemAttrib				eMemAttrib;					//!< PALLOC memory attribute
	SYS_eMemPool				eMemPool;					//!< PALLOC memory pool
}TALMMU_uHeapOptions;

/**
 * @brief This is the prototype for event callback functions.
 *
 * @Input    pCallbackParameter   A pointer to the application specific data.
 *
 * @Input    eEvent               Indicates the event which has occued.
 *
 * @Input    ui32IntRegIdOrAddr   IntRegId or address.
 *
 * @Input    hMemSpac             Handler to memspace.
 *
 * @return   This function returns either IMG_SUCCESS or an error code.
 */
typedef IMG_RESULT (*TALMMU_pfnEventCallback) (
    TALMMU_eEvent               eEvent,
    IMG_VOID *                  pCallbackParameter,
    IMG_UINT32                  ui32IntRegIdOrAddr,
    IMG_HANDLE  			    hMemSpac
);

/*!
******************************************************************************

 @Function				TALMMU_Initialise

 @Description

 This function is used to initialise the TALMMU component.

 @Input		None.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_Initialise(IMG_VOID);

/*!
******************************************************************************

 @Function				TALMMU_Deinitialise

 @Description

 This function is used to de-initialise the TALMMU component.

 NOTE: This function frees all memory structure, host and device memory that
 has been allocated.

 @Input		None.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_Deinitialise(IMG_VOID);

/*!
******************************************************************************

 @Function				TALMMU_DevMemTemplateCreate

 @Description

 This function is used to create a device memory template.

 @Input     psDevMemInfo    : A pointer to a TALMMU_sDevMemInfo structure.

 @Output    phDevMemTemplate	: A pointer used to return the template handle.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemTemplateCreate(
    TALMMU_sDevMemInfo *    psDevMemInfo,
	IMG_HANDLE *			phDevMemTemplate
);

/*!
******************************************************************************

 @Function				TALMMU_DevMemTemplateDestroy

 @Description

 This function is used to destroy a device memory template previously created 
 using TALMMU_DevMemTemplateCreate().

 NOTE: Frees all of the memory structures associated with the device.

 @Input		hDevMemTemplate  : Handle for device memory template object.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemTemplateDestroy(
	IMG_HANDLE              hDevMemTemplate
);

/*!
******************************************************************************

 @Function				TALMMU_DevMemHeapAdd

 @Description

 This function is used to add a heap to a device template.

 @Input		hDevMemTemplate  : Handle for device memory template object.

 @Input     psHeapInfo      : A pointer to a TALMMU_sHeapInfo structure.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemHeapAdd(
	IMG_HANDLE              hDevMemTemplate,
    TALMMU_sHeapInfo *      psHeapInfo    
);

/*!
******************************************************************************

 @Function				TALMMU_DevMemHeapUpdateTileStride

 @Description

 This function is used to update a heap's tile stride.

 @Input		hDevMemContext  : Handle for device memory context object.

 @Input     ui32Heap        : The number of the heap to be updated.

 @Input     ui32TileStride  : The new tile stride for the heap.

 @Return	None.

******************************************************************************/
extern
IMG_VOID TALMMU_DevMemHeapUpdateTileStride(
	IMG_HANDLE              hDevMemContext,
	IMG_UINT32              ui32Heap,
	IMG_UINT32              ui32TileStride
);
/*!
******************************************************************************

 @Function				TALMMU_DevMemHeapEmpty

  @Description

 This function is used to empty a heap of data (release all the memory).

 @Input		hDevMemContext  : Handle for context of heap.

 @Input     hDevMemHeap     : Handle for heap to be destroyed.
 
 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemHeapEmpty(
	IMG_HANDLE              hDevMemContext,
	IMG_HANDLE              hDevMemHeap
);

/*!
******************************************************************************

 @Function				TALMMU_DevMemHeapOptions

 @Description

 This function is used to set additional heap options

 @Input     hDevMemHeap    : Handle for heap to be destroyed.

 @Input		eHeapOptionId  : Heap options ID.

 @Input		uHeapOptions   : Heap options.
 
 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemHeapOptions(
	IMG_HANDLE              hDevMemHeap,
	TALMMU_eHeapOptionId	eHeapOptionId,
	TALMMU_uHeapOptions		uHeapOptions
);

/*!
******************************************************************************

 @Function				TALMMU_DevMemContextCreate

 @Description

 This function is used to create a device memory context.

 @Input		hDevMemTemplate  : Handle for device memory template object.

 @Input     ui32MmuContextId : The MMU context ID used with the TAL.

 @Output	phDevMemContext : A pointer used to return the handle for 
								device memory context object.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemContextCreate(
	IMG_HANDLE              hDevMemTemplate,
    IMG_UINT32              ui32MmuContextId,
	IMG_HANDLE *            phDevMemContext
);

/*!
******************************************************************************

 @Function				TALMMU_DevMemContextDestroy

 @Description

 This function is used to destroy a device memory context previously created 
 using TALMMU_DevMemContextCreate().

 NOTE: Frees all of the memory structures associated with the device.

 @Input		hDevMemContext  : Handle for device memory context object.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemContextDestroy(
	IMG_HANDLE              hDevMemContext
);


#if !defined (__TALMMU_NO_TAL__)
/*!
******************************************************************************

 @Function				TALMMU_DevMemContextGetPtd

 @Description

 This function is used to obtain the page table directory for a device memory
 context.

 @Input		hDevMemContext  : Handle for device memory context object.

 @Output	phTalHandle      : A pointer used to return the TAL handle for 
								the memory containing the PDT.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemContextGetPtd(
	IMG_HANDLE              hDevMemContext,
	IMG_HANDLE *			phTalHandle
);
#endif


/*!
******************************************************************************

 @Function				TALMMU_DevMemContextSetMMUPtd

 @Description

 This function is used to set the page table directory from a device context.

 NOTE: This also sets up any additional TAL MMU context required (e.g. tiling
 region etc.)

 @Input		hDevMemContext  : Handle for device memory context object.

 @Input     pvAltCbParam      : Alternative callback parameter. If IMG_NULL
                              the parameter registered with TALMMU_AddCallback()
                              will be returned.
 
 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemContextSetMMUPtd(
	IMG_HANDLE              hDevMemContext,
    IMG_VOID              * pvAltCbParam
);


/*!
******************************************************************************

 @Function				TALMMU_GetHeapHandle

 @Description

 This function is used to obtain the heap handle for a heap in a device
 memory context.

 @Input     ui32HeapId      : Heap id specified in the #TALMMU_sHeapInfo 
                              structure.

 @Input		hDevMemContext  : Handle for device memory context object.

 @Output	phDevMemHeap      : A pointer used to return the handle to the heap object.
 
 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_GetHeapHandle(
    IMG_UINT32              ui32HeapId,
	IMG_HANDLE              hDevMemContext,
	IMG_HANDLE *			phDevMemHeap
);

/*!
******************************************************************************

 @Function              TALMMU_GetDevHeapId

 @Description

 This function is used to obtain the heap Id for a heap in a device memory
 context.

 @Input		hMemory		:	A handle to the heap object.

 @Output	pui32HeapId	:	A pointer used to return the heap Id
 
 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_GetDevHeapId(
	IMG_HANDLE              hMemory,
    IMG_UINT32 *            pui32HeapId
);

/*!
******************************************************************************

 @Function              TALMMU_GetHeapInfo

 @Description

 This function is used to obtain a pointer to the heap information used to
 create a heap, given the heap handle.

 @Input		hDevMemHeap		:	A handle to the heap object.

 @Output	psHeapInfo		:	A pointer to a #TALMMU_sHeapInfo structure used
								to return the heap information originally provided
								by the user when this heap was created.
 
 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_GetHeapInfo(
	IMG_HANDLE				hDevMemHeap,
	TALMMU_sHeapInfo *		psHeapInfo
);

/*!
******************************************************************************

 @Function				TALMMU_GetContextHandle

 @Description

 This function will return the handle of the MMU context through which the
 referenced memory object was mapped.

 @Input		hDevMemObject	: Handle of the device memory object for which the
							  context handle should be obtained.

 @Output	phDevMemContext	: A pointer used to return a handle to the 
							  MMU context through which the
							  referenced device memory object was mapped.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_GetContextHandle (
	IMG_HANDLE				hDevMemObject, 
	IMG_HANDLE *			phDevMemContext
);

/*!
******************************************************************************

 @Function				TALMMU_GetContextId

 @Description

 This function will return the Id of an MMU context, given its handle

 @Input		hDevMemContext	: Handle to the MMU context for which the Id
							  should be obtained.

 @Output	pui32MmuContextId	: A pointer used to retunr the Id of the referenced MMU context.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_GetContextId(
	IMG_HANDLE				hDevMemContext,
	IMG_UINT32 *			pui32MmuContextId
);

/*!
******************************************************************************

 @Function				TALMMU_DevMemMalloc

 @Description

 This function is used to malloc device memory. The device memory is mapped into
 the devices MMU.

 @Input		hDevMemContext  : Handle for device memory context object.

 @Input		hDevMemHeap     : Handle for heap object.

 @Input		ui32Size	    : The size, in bytes, to be allocated.

 @Input		ui32Alignment   : The required byte alignment (1, 2, 4, 8, 16 etc).


 @Output	phMemory         : A pointer used to return a handle for the memory object.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.


******************************************************************************/
extern IMG_RESULT TALMMU_DevMemMalloc(
	IMG_HANDLE              hDevMemContext,
	IMG_HANDLE              hDevMemHeap,
	IMG_UINT32              ui32Size,
	IMG_UINT32              ui32Alignment,
	IMG_HANDLE *			phMemory
);

/*!
******************************************************************************

 @Function				TALMMU_DevMemMalloc1

 @Description

 This function is used to malloc device memory. The device memory is mapped into
 the devices MMU.

 @Input		hDevMemContext  : Handle for device memory context object.

 @Input     ui32HeapId      : Heap id specified in the #TALMMU_sHeapInfo 
                              structure.

 @Input		ui32Size	    : The size, in bytes, to be allocated.

 @Input		ui32Alignment   : The required byte alignment (1, 2, 4, 8, 16 etc).

 @Output	phMemory         : A pointer used to return a handle for the memory object.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemMalloc1(
	IMG_HANDLE              hDevMemContext,
    IMG_UINT32              ui32HeapId,
	IMG_UINT32              ui32Size,
	IMG_UINT32              ui32Alignment,
	IMG_HANDLE *			phMemory
);

/*!
******************************************************************************

 @Function				TALMMU_DevMemMalloc1NonMap

 @Description

 This function is used to malloc device virtual memory without mapping the
 device memory in to the device's MMU. TALMMU_DevMemMap() is used to map the
 memory into the device's MMU.

 @Input		hDevMemContext  : Handle for device memory context object.

 @Input     ui32HeapId      : Heap id specified in the #TALMMU_sHeapInfo 
                              structure.

 @Input		ui32Size	    : The size, in bytes, to be allocated.

 @Input		ui32Alignment   : The required byte alignment (1, 2, 4, 8, 16 etc).

 @Output	phMemory         : A pointer used to return a handle for the memory object.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemMalloc1NonMap(
	IMG_HANDLE              hDevMemContext,
    IMG_UINT32              ui32HeapId,
	IMG_UINT32              ui32Size,
	IMG_UINT32              ui32Alignment,
	IMG_HANDLE *			phMemory
);


/*!
******************************************************************************

 @Function				TALMMU_DevMemMapExtMem

 @Description

 This function is used to malloc device memory (virtual memory), but mapping 
 this to memory that has already been allocated (externally).

 NOTE: Memory can be freed using TALMMU_DevMemFree().  However, this does not
 free the memory provided by the caller via pvCpuLinearAddr.

 @Input		hDevMemContext  : Handle for device memory context object.

 @Input		hDevMemHeap     : Handle for heap object.

 @Input		ui32Size	    : The size, in bytes, to be allocated.

 @Input		ui32Alignment   : The required byte alignment (1, 2, 4, 8, 16 etc).

 @Input     pvCpuLinearAddr : CPU linear address of the memory to be allocated
                              for the device.

 @Input     hExtImportHandle	: The buffer "external import" handle.

 @Output	phMemory         : A pointer used to return a handle for the memory object.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemMapExtMem(
	IMG_HANDLE              hDevMemContext,
	IMG_HANDLE              hDevMemHeap,
	IMG_UINT32              ui32Size,
	IMG_UINT32              ui32Alignment,
    IMG_VOID *              pvCpuLinearAddr,
	IMG_HANDLE				hExtImportHandle,
	IMG_HANDLE *			phMemory
);

/*!
******************************************************************************

							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemMapExtMem1(
	IMG_HANDLE              hDevMemContext,
    IMG_UINT32              ui32HeapId,
	IMG_UINT32              ui32Size,
	IMG_UINT32              ui32Alignment,
    IMG_VOID *              pvCpuLinearAddr,
	IMG_HANDLE				hExtImportHandle,
	IMG_HANDLE *			phMemory
);

/*!
******************************************************************************

 @Function				TALMMU_DevMemMapExt1

 @Description

 This function is used to setup mapping of external memory already mapped
 in the device virtual space

 @Input		hDevMemContext  : Handle for device memory context object.
 
 @Input     ui32HeapId      : Heap id specified in the #TALMMU_sHeapInfo 
                              structure.
							  
 @Input     pvCpuLinearAddr : CPU linear address of the memory to be allocated
                              for the device.

 @Input     ui32DevVirtOffset : Device Virtual address of the memory
							  
 @Input		ui32Size	    : The size, in bytes, to be allocated.

 @Input		ui32Alignment   : The required byte alignment (1, 2, 4, 8, 16 etc).

 @Input     hExtImportHandle	: The buffer "external import" handle.

 @Output	phMemory         : A pointer used to return a handle for the memory object.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemMapExt1(
	IMG_HANDLE              hDevMemContext,
    IMG_UINT32              ui32HeapId,
    IMG_VOID *              pvCpuLinearAddr,
    IMG_UINT32              ui32DevVirtOffset,
	IMG_UINT32              ui32Size,
	IMG_UINT32              ui32Alignment,
	IMG_HANDLE				hExtImportHandle,
	IMG_HANDLE *			phMemory
	);

/*!
******************************************************************************

 @Function				TALMMU_DevMemMapExt1

 @Description

 This function is used to malloc device memory.

 NOTE: Memory can be freed using TALMMU_DevMemFree().  However, this does not
 free the memory provided by the caller via pvCpuLinearAddr or the device
 virtual address space provided via ui32DevVirtOffset.

 @Input		hDevMemContext  : Handle for device memory context object.

 @Input     ui32HeapId      : Heap id specified in the #TALMMU_sHeapInfo 
                              structure.

 @Input     pvCpuLinearAddr : CPU linear address of the memory to be allocated
                              for the device.

 @Input     ui32DevVirtOffset   : Device virtual offset of the allocation

 @Input		ui32Size	    : The size, in bytes, to be allocated.

 @Input		ui32Alignment   : The required byte alignment (1, 2, 4, 8, 16 etc).

 @Input     hExtImportHandle	: The buffer "external import" handle.

 @Output	phMemory         : A pointer used to return a handle for the memory object.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemMapExt1(
	IMG_HANDLE              hDevMemContext,
    IMG_UINT32              ui32HeapId,
    IMG_VOID *              pvCpuLinearAddr,
    IMG_UINT32              ui32DevVirtOffset,
	IMG_UINT32              ui32Size,
	IMG_UINT32              ui32Alignment,
	IMG_HANDLE				hExtImportHandle,
	IMG_HANDLE *			phMemory
);

/*!
******************************************************************************

 @Function				TALMMU_DevMemFree

 @Description

 This function is used to free device memory allocated using
 TALMMU_DevMemMalloc().

 NOTE: This function should be depricated in favor of TALMMU_DevMemFree1().

 @Input		hDevMemContext  : Handle for device memory context object.

 @Input		hMemory         : Handle for the memory object.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemFree(
	IMG_HANDLE              hDevMemContext,
	IMG_HANDLE              hMemory
);

/*!
******************************************************************************

 @Function				TALMMU_DevMemFree1

 @Description

 This function is used to free device memory allocated using
 TALMMU_DevMemMalloc().

 @Input		hMemory         : Handle for the memory object.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemFree1(
	IMG_HANDLE              hMemory
);

/*!
******************************************************************************

 @Function				TALMMU_GetAllocId

 @Description

 This function is used to obtains the PALLOC allocation ID.

 @Input		hMemory         : Handle for the memory object.

 @Output	pui32AllocId      : A pointer used to return the PALLOC allocation ID.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_GetAllocId(
	IMG_HANDLE              hMemory,
	IMG_UINT32				pui32AllocId
);

/*!
******************************************************************************

 @Function				TALMMU_CpuMemMap

 @Description

 This function is used to map the memory allocated using TALMMU_DevMemMalloc()
 so that it can be accessed by the CPU.

 @Input		hMemory         : Handle for the memory object.

 @Output	pvMemory      : A pointer used to return to the mapped memory - CPU linear address.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_CpuMemMap(
	IMG_HANDLE              hMemory,
	IMG_VOID **				pvMemory
);

/*!
******************************************************************************

 @Function				TALMMU_CpuMemUnmap

 @Description

 This function is used to un-map the memory previously mapped using
 TALMMU_CpuMemMap().

 @Input		hMemory         : Handle for the memory object.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_CpuMemUnmap(
	IMG_HANDLE              hMemory
);

/*!
******************************************************************************

 @Function				TALMMU_DevMemSetMapAttrib

 @Description

 This function is used to set mapping attributes.

 NOTE: The memory must have been mapped into the MMU before the call is made.

 @Input		hMemory         : Handle for the memory object.

 @Input     eMapAttrib      : Attribute flags to be set.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemSetMapAttrib(
	IMG_HANDLE              hMemory,
    TALMMU_eMapAttrib       eMapAttrib
);

/*!
******************************************************************************

 @Function				TALMMU_DevMemMap

 @Description

 This function is used to map the memory allocated through then the TALMMU 
 component so that it can be accessed by a device.

 Maps the allocation so that the device can access the memory through it's MMU.

 @Input		hMemory         : Handle for the memory object.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemMap(
	IMG_HANDLE              hMemory
);

/*!
******************************************************************************

 @Function				TALMMU_DevMemUnmap

 @Description

 This function is used to un-map the memory previously mapped using
 TALMMU_DevMemMap().

 Un-maps this so that the device can no longer access the memory through
 it's MMU and flushes the MMU cache for this region.

 NOTE: The MMU cache may need to be flushed after um-mapping an allocation
 - to ensure that a stale version is not picked up from teh cache.

 @Input		hMemory         : Handle for the memory object.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemUnmap(
	IMG_HANDLE              hMemory
);


/*!
******************************************************************************

 @Function				TALMMU_WriteDevMemRef

 @Description

 This function is used to write a reference to a device memory address to
 a memory space.

 @Input		hMemSpace		: A Handle to the TAL memory space for the 
 								target register
 @Input		ui32Offset		: The offset, in bytes, of the from the base of
							  the memory space.
 @Input		hRefMemory      : Handle for the referenced memory object.

 @Input		ui32RefOffset	: The offset to be applied, in bytes from the
							  base address of the referenced device memory.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_WriteDevMemRef(
	IMG_HANDLE				hMemSpace,
	IMG_UINT32				ui32Offset,
	IMG_HANDLE              hRefMemory,
	IMG_UINT32				ui32RefOffset
);


/*!
******************************************************************************

 @Function				TALMMU_WriteDevMemRefWithBitPattern

 @Description

 This function is used to write a reference to a device memory address to
 a memory space.

 The address of the device memory base plus the offset is passed to the
 mangler function and the resultant address the value of ui32BitPattern is
 OR'd with this and written to the target memory.

 @Input		hMemSpace		: A Handle to the TAL memory space for the 
 								target register
 @Input		ui32Offset		: The offset, in bytes, of the from the base of
							  the memory space.
 @Input		hRefMemory      : Handle for the referenced memory object.

 @Input		ui32RefOffset	: The offset to be applied, in bytes from the
							  base address of the referenced device memory.

 @Input		ui32BitPattern	: A bit pattern to be applied (OR'd) to the mangled
							  address BEFORE writing the memory reference.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_WriteDevMemRefWithBitPattern(
	IMG_HANDLE				hMemSpace,
	IMG_UINT32				ui32Offset,
	IMG_HANDLE              hRefMemory,
	IMG_UINT32				ui32RefOffset,
	IMG_UINT32				ui32BitPattern
);


/*!
******************************************************************************

 @Function				TALMMU_CirBufPollDevMem

 @Description

 This function is used to poll and wait for a value to be read from a word in
 a circular buffer device memory block. 

 @Input		hDeviceMem   	: Device memory handle

 @Input		ui32Offset		: The offset, in bytes, of the from the base of
							  the memory space.

 @Input		ui32WriteOffsetVal : The write offset value.

 @Input		ui32PacketSize : Size of packet

 @Input		ui32BufferSize  : Size of circular buffer

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_CirBufPollDevMem(
	IMG_HANDLE						hDeviceMem,
	IMG_UINT32                      ui32Offset,
	IMG_UINT32						ui32WriteOffsetVal,
	IMG_UINT32						ui32PacketSize,
	IMG_UINT32						ui32BufferSize
);


/*!
******************************************************************************

 @Function				TALMMU_PollDevMem

 @Description

 This function is used to poll and wait for a value to be read from a word in
 a device memory block. This can be used to force synchronous operation within
 the host and is reflected in the PDUMP output.

 The check function is located in the wrapper and can perform any masking,
 logical or comparison operations that may be required.  The TAL contains a
 built in check functions whose to check for =, <, <=, >, and >=.  See
 #TAL_CHECKFUNC_ISEQUAL and associated defines.

 @Input		hRefMemory      : Handle for the referenced memory object.

 @Input		ui32Offset	    : The offset, in bytes, of the from the base of
						      the memory space.

 @Input		ui32CheckFuncIdExt	: The check function ID.

 @Input		ui32RequValue	: The required value.

 @Input		ui32Enable	    : A mask to be applied to the value read before
						      comparing with the required value.

 @Input		ui32PollCount   : Number of times to repeat the poll.

 @Input		ui32TimeOut	    : The time-out value, in clock cycles, between polls.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_PollDevMem(
	IMG_HANDLE              hRefMemory,
	IMG_UINT32              ui32Offset,
    IMG_UINT32              ui32CheckFuncIdExt,
    IMG_UINT32              ui32RequValue,
    IMG_UINT32              ui32Enable,
    IMG_UINT32              ui32PollCount,
    IMG_UINT32              ui32TimeOut
);


/*!
******************************************************************************

 @Function				TALMMU_CopyHostToDevMem

 @Description

 This function is used to update the device memory (the current
 contents of the host buffer are transferred to the device).

 @Input		hMemory         : Handle for the memory object.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_CopyHostToDevMem(
	IMG_HANDLE              hMemory
);



/*!
******************************************************************************

 @Function				TALMMU_CopyHostToDevMemRegion

 @Description

 This function is used to update a region of the device memory (the current
 contents of the region of the host buffer are transferred to the device).

 @Input		hMemory         : Handle for the memory object.

 @Input		ui32Offset	    : The offset of the reference to be update, in bytes
						      from the base address of the device memory.

 @Input		ui32Size	    : The size (in bytes) of the region to be updated.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_CopyHostToDevMemRegion(
	IMG_HANDLE              hMemory,
	IMG_UINT32			    ui32Offset,
	IMG_UINT32			    ui32Size
);


/*!
******************************************************************************

 @Function				TALMMU_CopyTileBuffer

 @Description

 This function is used to copy data between a tiled memory buffer and
 a supplied untiled buffer. Data will be tiled / untiled during the copy

 #NOTE! This function will copy to / from the host buffer only, it will
         not initiate a copy to / from the device

 @Input		hMemory         : Handle for the memory object.

 @Input		ui32Offset	    : The offset of the reference to be update, in bytes
						      from the base address of the device memory.

 @Input		ui32Size	    : The size (in bytes) of the region to be updated.

 @Input		pcBuffer		: A supplied buffer to copy to / from

 @Input		bToMemory		: If true, copy from pcBuffer to memory and tile
							  If false, copy from memory to pcBuffer and de-tile

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_CopyTileBuffer(
	IMG_HANDLE              hMemory,
	IMG_UINT32			    ui32Offset,
	IMG_UINT32			    ui32Size,
	IMG_CHAR*				pcBuffer,
	IMG_BOOL					bToMemory
);



/*!
******************************************************************************

 @Function				TALMMU_CopyDevMemToHost

 @Description

 This function is used to update the host buffer from the device memory
 (the current contents of the device memory are transferred to the
 host buffer).

 @Input		hMemory         : Handle for the memory object.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_CopyDevMemToHost(
	IMG_HANDLE              hMemory
);



/*!
******************************************************************************

 @Function				TALMMU_CopyDevMemToHostRegion

 @Description

 This function is used to update a region of the host buffer from the device
 memory on (the current contents of the device memory are transferred to the
 host buffer).

 @Input		hMemory         : Handle for the memory object.

 @Input		ui32Offset	    : The offset of the region to be update, in bytes
						      from the base address of the device memory.

 @Input		ui32Size	    : The size (in bytes) of the region to be updated.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_CopyDevMemToHostRegion( 
	IMG_HANDLE              hMemory,
	IMG_UINT32				ui32Offset,
	IMG_UINT32				ui32Size
);



/*!
******************************************************************************

 @Function              TALMMU_GetDevVirtAddress

 @Description

 This function is use to obtain the device (virtual) memory address which 
 may be required for as a device virtual address in some of the TAL image
 functions.

 @Input		hMemory         : Handle for the memory object.

 @Output    pui32DevVirt     : A piointer used to return the device virtual address.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_GetDevVirtAddress(
	IMG_HANDLE              hMemory,
	IMG_UINT32 *			pui32DevVirt
);

/*!
******************************************************************************

 @Function				TALMMU_DevMemWriteDevMemRef

 @Description

 Where device use linked memory structures, (e.g. DMAC descriptors)
 it is necessary, when these structures in the device memory,
 to fix-up the references in the memory so that they reference the
 appropriate device memory rather than the host memory.

 The address mangling is done the same as TAL_WriteDevMemRef().

 @Input		hMemory         : Handle for the memory object.

 @Input		ui32Offset	    : The offset of the reference to be update, in bytes
						      from the base address of the device memory.

 @Input		hRefMemory      : Handle for the referenced memory object.

 @Input		ui32RefOffset	: The offset to be applied, in bytes from the base
							  address of the referenced device memory.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemWriteDevMemRef(
	IMG_HANDLE						hMemory,
	IMG_UINT32						ui32Offset,
	IMG_HANDLE						hRefMemory,
	IMG_UINT32						ui32RefOffset
);



/*!
******************************************************************************

 @Function				TALMMU_DevMemWriteDevMemRefWithBitPattern

 @Description

 This function is similar to TALMMU_DevMemWriteDevMemRef(), but allows a
 bit pattern to be OR'd into the address written in the same way as
 TALMMU_WriteDevMemRefWithBitPattern().

 @Input		hMemory         : Handle for the memory object.

 @Input		ui32Offset	    : The offset of the reference to be update, in bytes
						      from the base address of the device memory.

 @Input		hRefMemory      : Handle for the referenced memory object.

 @Input		ui32RefOffset	: The offset to be applied, in bytes from the base
							  address of the referenced device memory.

 @Input		ui32BitPattern	: A bit pattern to be applied (OR'd) to the mangled
							  address BEFORE writing the memory reference.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemWriteDevMemRefWithBitPattern(
	IMG_HANDLE						hMemory,
	IMG_UINT32						ui32Offset,
	IMG_HANDLE						hRefMemory,
	IMG_UINT32						ui32RefOffset,
	IMG_UINT32						ui32BitPattern
);


/*!
******************************************************************************

 @Function				TALMMU_DevMemWriteDevMemRefWithBitPattern1

 @Description

 This function is similar to TALMMU_DevMemWriteDevMemRef(), but allows a
 bit pattern to be OR'd into the address written in the same way as
 TALMMU_WriteDevMemRefWithBitPattern(). This variant of the function allows
 a mangler Id to be specified (in order to perform operations to the virtual
 address before writing it to memory).

 @Input		hMemory         : Handle for the memory object.

 @Input		ui32Offset	    : The offset of the reference to be update, in bytes
						      from the base address of the device memory.

 @Input		hRefMemory      : Handle for the referenced memory object.

 @Input		ui32RefOffset	: The offset to be applied, in bytes from the base
							  address of the referenced device memory.

 @Input		ui32BitPattern	: A bit pattern to be applied (OR'd) to the mangled
							  address BEFORE writing the memory reference.

 @Input		ui32MemSpaceId	: The ID of the mem space containing the required
							  mangler function.

 @Input		ui32ManglerFunctionId : The ID of the mangler function to be used.
									Should be set to 'TAL_NULL_MANGLER_ID' if
									no mangler function is required.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_DevMemWriteDevMemRefWithBitPattern1(
	IMG_HANDLE						hMemory,
	IMG_UINT32						ui32Offset,
	IMG_HANDLE						hRefMemory,
	IMG_UINT32						ui32RefOffset,
	IMG_UINT32						ui32BitPattern,
	IMG_UINT32						ui32MemSpaceId,
	IMG_UINT32						ui32ManglerFunctionId
);


/*!
******************************************************************************

 @Function				TALMMU_GetTilingSetup

 @Description

 This function is used to establish the requirements for a tiled MMU region,
 and the buffers which are allocated from it. The user must specify the
 desired line stride and height of the buffers they intend to allocate from
 the region, and the function will complete a 'TALMMU_sTilingParameters'
 structure, containing the tile stride to use when creating the region and
 the new line stride, height and base address alignment requirements for the
 buffers allocated from the region.

 @Input		hDevMemTemplate :	A handle to a device memory template, obtained
								by calling 'TALMMU_DevMemTemplateCreate'.

 @Input		ui32BufferStride :	The (unmodified) stride of the buffers to be
								allocated from the tiled region.

 @Input		ui32BufferHeight :	The (unmodified) height of the buffers to be
								allocated from the tiled region.

 @Input		psTilingParameters : Pointer to a 'TALMMU_sTilingParameters'
								 structure which the function will complete.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT TALMMU_GetTilingSetup ( IMG_HANDLE					hDevMemTemplate,
									IMG_UINT32					ui32BufferStride,
									IMG_UINT32					ui32BufferHeight,
									TALMMU_sTilingParameters *	psTilingParameters );

/*!
******************************************************************************

 @Function				TALMMU_ConvertTileStride

 @Description

 This function is used to calculate the tile stride from the
 X tile stride value.

 @Input		hDevMemContext :	A handle to a device memory context.

 @Input		ui32XTileStride :	The X Tile Stride parameter.

 @Output	pui32TileStride :	A pointer used to return the tile stride.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.
 
******************************************************************************/
extern IMG_RESULT	TALMMU_ConvertTileStride ( 
	IMG_HANDLE					hDevMemContext,
	IMG_UINT32					ui32XTileStride,
	IMG_UINT32 *				pui32TileStride
);

/*!
******************************************************************************

 @Function				TALMMU_AddCallback

 @Description

 This function will add a callback to a context.

 @Input		hDevMemTemplate		: A handle to the template.

 @Input		pfnCallbackToAdd	: The Function that is to executed.

 @Input		pCallbackParameter  : Client callback datae.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern	IMG_RESULT TALMMU_AddCallback(	
	IMG_HANDLE              hDevMemTemplate,
	TALMMU_pfnEventCallback	pfnEventCallback,
	IMG_VOID *				pCallbackParameter
);

/*!
******************************************************************************

 @Function				TALMMU_RemoveCallback

 @Description

 This function will remove a callback to a context.

 @Input		hDevMemTemplate		: A handle to the template.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
IMG_RESULT TALMMU_RemoveCallback(	
	IMG_HANDLE              hDevMemTemplate
);

/*!
******************************************************************************

 @Function				TALMMU_GetDevPhysAddr

 @Description

 This function returns the device physical address of a memory region.

 @Input		hMemory :             Handle to the memory region

 @Output	pui64DevPhysAddr :	A pointer used to return the physical address of the memory region. 

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
IMG_RESULT TALMMU_GetDevPhysAddr(
	IMG_HANDLE			hMemory,
	IMG_UINT64 *			pui64DevPhysAddr
);

#if defined (__cplusplus)
}
#endif

#endif /* __TALMMU_API_H__	*/


