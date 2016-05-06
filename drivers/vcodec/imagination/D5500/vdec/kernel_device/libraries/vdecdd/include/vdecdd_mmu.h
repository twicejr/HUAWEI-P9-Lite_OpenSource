/*!
 *****************************************************************************
 *
 * @File       vdecdd_mmu.h
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

#include <img_errors.h>
#include <img_defs.h>
#include "msvdx_ext.h"
#include "vxd_ext.h"
#include <vdecdd_int.h>
#include <vdecdd_mmu_defs.h>

#ifndef _VDECDD_MMU_H_
#define _VDECDD_MMU_H_


#ifdef __cplusplus
extern "C" {
#endif


/*!
******************************************************************************
 This type defines the VDECDD MMU device event callbacks
******************************************************************************/
typedef enum
{
	/*! Function to flush the cache.		*/
	VDECDDMMU_EVENT_FLUSH_CACHE,

	/* Placeholder*/
	VDECDDMMU_MAX_NUM_EVENTS

} VDECDDMMU_eEvent;


/*!
******************************************************************************
 This type defines MMU variant.
******************************************************************************/



/*!
******************************************************************************
 This type defines the MMU heaps.
******************************************************************************/




/*!
******************************************************************************
 This structure describes tiling of heap.
******************************************************************************/



typedef IMG_RESULT (*VDECDDMMU_pfnDeviceCallback) (
    VDECDDMMU_eEvent            eEvent,
    IMG_VOID *                  pCallbackParameter
);



/*!
******************************************************************************

 @Function				MMU_StreamGetPtdHandle

 @Description

 This function is used to obtain the stream PTD (Page Table Directory) handle.
 
 @Input		hMmuStrHandle   : MMU stream handle.

 @Output    phStrPtd        : Pointer to stream PTD handle.
 
 @Return	IMG_RESULT	    : This function returns either IMG_SUCCESS or an
							  error code.

******************************************************************************/
extern IMG_RESULT MMU_StreamGetPtdHandle(
    IMG_HANDLE 				hMmuStrHandle,
    IMG_HANDLE            * phStrPtd
);


/*!
******************************************************************************

 @Function				MMU_GetTiledHeaps

 @Description

 This function is used to obtain tiling information for tiled heaps.

 @Input     eTileScheme     : Tiling scheme.

 @Output    pui32NumHeaps   : Pointer to number of heaps with tiling.

 @Output    pasTilingInfo   : Pointer to an array into which tiling information
                              should be added. NOTE: This must be large enough 
                              for all tiled heaps.
 
 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT MMU_GetTiledHeaps(
    VDEC_eTileScheme        eTileScheme,
    IMG_UINT32            * pui32NumHeaps,
    MMU_sHeapTilingInfo   * pasTilingInfo

);


/*!
******************************************************************************

 @Function				MMU_GetHeap

 @Description

 This function is used to obtain the heap ID for an image buffer.

 @Input     eTileScheme     : Tiling scheme.

 @Input     ui32ImageStride : Image stride (in bytes).

 @Output    peHeapId        : A pointer used to return the MMU heap ID.
 
 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT MMU_GetHeap(
    VDEC_eTileScheme        eTileScheme,
    IMG_UINT32              ui32ImageStride,
    MMU_eHeapId           * peHeapId

);


/*!
******************************************************************************

 @Function              MMU_DeviceCreate

 @Description

 This function is used to create and initialise the MMU device context.

 @Input     eMmuType            : MMU type.

 @Input     eTileScheme         : VDEC_eTileScheme

 @Input     pfnDeviceCallback   : Pointer to MMU device callback handler function.

 @Input     eMemPool            : Memory pool

 @Input     pvCallbackParameter : Pointer to MMU device callback parameter.

 @Input     ui32PtdAlignment    : Alignment of Page Table directory.

 @Output    phMmuDevHandle      : A pointer used to return the MMU device handle.

 @Return    IMG_RESULT          : This function returns either IMG_SUCCESS or an
                                  error code.

******************************************************************************/
extern IMG_RESULT MMU_DeviceCreate(
    MMU_eMmuType                    eMmuType,
    VDEC_eTileScheme                eTileScheme,
    VDECDDMMU_pfnDeviceCallback     pfnDeviceCallback,
    VXDIO_sMemPool                  sMemPool,
    IMG_VOID                      * pvCallbackParameter,
    IMG_UINT32                      ui32PtdAlignment,
    IMG_HANDLE                    * phMmuDevHandle
);


/*!
******************************************************************************

 @Function              MMU_DeviceDestroy

 @Description

 This function is used to create and initialise the MMU device context.

 NOTE: Destroy device automatically destroys any streams and frees and
 memory allocated using MMU_DeviceMalloc() and MMU_StreamMalloc().

 @Input		hMmuDevHandle    : The MMU device handle.
 
 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT  MMU_DeviceDestroy(
	IMG_HANDLE 				hMmuDevHandle
);


/*!
******************************************************************************

 @Function              MMU_DeviceMalloc

 @Description

 This function is used to allocate device memory.

 @Input		hMmuDevHandle    : The MMU device handle.

 @Input     eHeapId		: The heap Id.

 @Input     eMemPool        : The memory pool we are using 

 @Input		ui32Size	    : The size, in bytes, to be allocated.

 @Input		ui32Alignment   : The required byte alignment (1, 2, 4, 8, 16 etc).

 @Output	psDdBufInfo		: A pointer to a #VXDIO_sDdBufInfo structure 
								used to return the buffer info.
 
 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT  MMU_DeviceMalloc(
	IMG_HANDLE 				hMmuDevHandle,
    MMU_eHeapId             eHeapId,
    VXDIO_sMemPool          sMemPool,
	IMG_UINT32              ui32Size,
	IMG_UINT32              ui32Alignment,
	VXDIO_sDdBufInfo      * psDdBufInfo
);


/*!
******************************************************************************

 @Function MMU_DeviceWritePtdToMem
 
 @Description

 This function is used to write the Device Page Table Directory to memory.

 @Input     hMmuDevHandle   : The MMU stream handle.

 @Input     psPtdBufInfo    : Pointer to Ptd buffer information.

 @Input     psPtdInfo       : Pointer to structure containing Address of PTD
                              related information.

 @Return    IMG_RESULT      : This function returns either IMG_SUCCESS or an
                              error code.

******************************************************************************/
extern IMG_RESULT MMU_DeviceWritePtdToMem(
    IMG_HANDLE              hMmuDevHandle,
    VXDIO_sDdBufInfo      * psPtdBufInfo,
    VXDIO_sPtdInfo        * psPtdInfo
);


/*!
******************************************************************************

 @Function              MMU_StreamCreate

 @Description

 This function is used to create and initialise the MMU stream context.

 @Input		hMmuDevHandle    : The MMU device handle.

 @Output    phMmuStrHandle    : A pointer used to return the MMU stream handle.
 
 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT  MMU_StreamCreate(
	IMG_HANDLE 				hMmuDevHandle,
	IMG_HANDLE *			phMmuStrHandle
);


/*!
******************************************************************************

 @Function              MMU_StreamDestroy

 @Description

 This function is used to create and initialise the MMU stream context.
 
 NOTE: Destroy  automatically frees and memory allocated using MMU_StreamMalloc().

 @Input		hMmuStrHandle    : The MMU stream handle.
 
 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT  MMU_StreamDestroy(
	IMG_HANDLE 				hMmuStrHandle
);


/*!
******************************************************************************

 @Function              MMU_StreamMalloc

 @Description

 This function is used to allocate stream memory.

 @Input		hMmuStrHandle    : The MMU stream handle.

 @Input     eHeapId		: The heap Id.

 @Input     eMemPool        : Memory pool to use.

 @Input		ui32Size	    : The size, in bytes, to be allocated.

 @Input		ui32Alignment   : The required byte alignment (1, 2, 4, 8, 16 etc).

 @Output	psDdBufInfo		: A pointer to a #VXDIO_sDdBufInfo structure 
								used to return the buffer info.
 
 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT  MMU_StreamMalloc(
	IMG_HANDLE 				hMmuStrHandle,
    MMU_eHeapId             eHeapId,
    VXDIO_sMemPool          sMemPool,
	IMG_UINT32              ui32Size,
	IMG_UINT32              ui32Alignment,
	VXDIO_sDdBufInfo      * psDdBufInfo
);


/*!
******************************************************************************

 @Function				MMU_StreamMapExt

 @Description

 This function is used to malloc device memory (virtual memory), but mapping 
 this to memory that has already been allocated (externally).
 
 NOTE: Memory can be freed using MMU_Free().  However, this does not
 free the memory provided by the caller via pvCpuLinearAddr.

 @Input		hMmuStrHandle    : The MMU stream handle.

 @Input     eHeapId		: The heap Id.
							  
 @Input		ui32Size	    : The size, in bytes, to be allocated.

 @Input		ui32Alignment   : The required byte alignment (1, 2, 4, 8, 16 etc).
 							  
 @Input     pvCpuLinearAddr : CPU linear address of the memory to be allocated
                              for the device.

 @Input     hExtImportHandle	: The buffer "external import" handle.

 @Output	psDdBufInfo		: A pointer to a #VXDIO_sDdBufInfo structure 
								used to return the buffer info.

 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT	MMU_StreamMapExt(
	IMG_HANDLE 				hMmuStrHandle,
    MMU_eHeapId             eHeapId,
	IMG_UINT32              ui32Size,
	IMG_UINT32              ui32Alignment,
    IMG_VOID *              pvCpuLinearAddr,
	IMG_HANDLE				hExtImportHandle,
	VXDIO_sDdBufInfo      * psDdBufInfo
);


/*!
******************************************************************************

 @Function				MMU_StreamWritePtdToMem
 
 @Description

 This function is used to write the Page Table Directory to memory.

 @Input		hMmuStrHandle   : The MMU stream handle.

 @Input     psPtdBufInfo    : Pointer to Ptd buffer information.

 @Return	IMG_RESULT	    :	This function returns either IMG_SUCCESS or an
							    error code.

******************************************************************************/
extern IMG_RESULT MMU_StreamWritePtdToMem(
    IMG_HANDLE 				hMmuStrHandle,
    VXDIO_sDdBufInfo      * psPtdBufInfo
);


/*!
******************************************************************************

 @Function              MMU_FreeMem

 @Description

 This function is used to free device memory.

 @Input		psDdBufInfo		: A pointer to a #VXDIO_sDdBufInfo structure.
 
 @Return	IMG_RESULT	:	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT  MMU_FreeMem(
	VXDIO_sDdBufInfo  * psDdBufInfo
);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _VDECDD_MMU_H_ */
