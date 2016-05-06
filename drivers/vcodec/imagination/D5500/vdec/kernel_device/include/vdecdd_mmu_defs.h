/*!
 *****************************************************************************
 *
 * @File       vdecdd_mmu_defs.h
 * @Title      VDECDD MMU Definitions
 * @Description    This file contains VDECDD MMU definitions. These definitions
 *  are used internally and are provided in this header
 *  only for debugging purposes.
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

#include <img_defs.h>

#ifndef _VDECDD_MMU_DEF_H_
#define _VDECDD_MMU_DEF_H_


#ifdef __cplusplus
extern "C" {
#endif


/*!
******************************************************************************
 This type defines MMU variant.
******************************************************************************/
typedef enum
{
    MMU_TYPE_NONE = 0,
    MMU_TYPE_32BIT,
    MMU_TYPE_36BIT,
    MMU_TYPE_40BIT,

} MMU_eMmuType;

/*!
******************************************************************************
  This type defines the MMU tiling scheme
******************************************************************************/
typedef enum
{
    MMU_MMUTILING_SCHEME_0 = 0,  
    MMU_MMUTILING_SCHEME_1 = 1,

    MMU_MMUTILING_SCHEME_MAX
} MMU_eMMUTilingScheme;


/*!
******************************************************************************
 This type defines the MMU heaps.
******************************************************************************/
typedef enum
{
    MMU_HEAP_IMAGE_BUFFERS_UNTILED = 0x00,  //!< Heap for untiled video buffers
    MMU_HEAP_IMAGE_BUFFERS_512,             //!< Heap for 512 tile stride video buffers
    MMU_HEAP_IMAGE_BUFFERS_1024,            //!< Heap for 1024 tile stride video buffers
    MMU_HEAP_IMAGE_BUFFERS_2048,            //!< Heap for 2048 tile stride video buffers
    MMU_HEAP_IMAGE_BUFFERS_4096,            //!< Heap for 4096 tile stride video buffers
    MMU_HEAP_DEVICE_BUFFERS,                //!< Heap for Device buffers
    MMU_HEAP_BITSTREAM_BUFFERS,             //!< Heap for bitstream buffers
    MMU_HEAP_STREAM_BUFFERS,                //!< Heap for Stream buffers

    MMU_HEAP_MAX,                           //!< Number of heaps

} MMU_eHeapId;


/*!
******************************************************************************
 This structure describes tiling of heap.
******************************************************************************/
typedef struct
{
    IMG_UINT32              ui32StartOffset;    //!< Start offset in VM to heap
    IMG_UINT32              ui32Size;           //!< Size of heap (in bytes)
    IMG_UINT32              ui32HwTileStride;   //!< Hardware tile stride value

    //MMU_eMMUTilingScheme    eMMUTilingScheme;   //!< Tiling Scheme

} MMU_sHeapTilingInfo;


extern IMG_CHAR acMmuTypeNames[][32];


#ifdef __cplusplus
}
#endif

#endif /* #ifndef _VDECDD_MMU_DEFS_H_ */
