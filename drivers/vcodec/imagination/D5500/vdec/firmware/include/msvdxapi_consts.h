/*!
 *****************************************************************************
 *
 * @File       msvdxapi_consts.h
 * @Title      MSVDX API Header
 * @Description    Exported MSVDX API details
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

#ifndef __MSVDXAPI_CONSTS_H__
#define __MSVDXAPI_CONSTS_H__

#if defined (__cplusplus)
extern "C" {
#endif



/******************************************************************************
 Some defines...
******************************************************************************/

/* MSVDX Heap IDs, note: not all heaps are available to clients */
#define MSVDX_SHARED_HEAP_ID			0
#define MSVDX_BITSTREAM_HEAP_ID			1
#define MSVDX_DATA_HEAP_ID				2
#define MSVDX_FRAMES_HEAP_ID			3
#define MSVDX_TILED_FRAMES_2K_HEAP_ID	4
#define MSVDX_TILED_FRAMES_4K_HEAP_ID	5
#define MSVDX_TILED_FRAMES_8K_HEAP_ID	6

#define MSVDX_MAX_HEAP_ID				6
#define MSVDX_UNDEFINED_HEAP_ID			(~0UL)

/******************************************************************************
 * Capability Flags 
 *****************************************************************************/

/* FW capabilities shalt be defined in top byte of INT32 */
#define CAPABILITY_FW_FS					(IMG_UINT32)(1<<31)
#define CAPABILITY_FW_1KSEGMENT				(IMG_UINT32)(1<<30)
#define CAPABILITY_FW_VC1_HEADER_PARSING	(IMG_UINT32)(1<<29)
#define CAPABILITY_FW_H264_INTRA_DEBLOCK	(IMG_UINT32)(1<<28)
#define CAPABILITY_FW_BE_OPPS_SUPPORTED		(IMG_UINT32)(1<<27)
#define	CAPABILITY_FW_NALU_EXTRACTION		(IMG_UINT32)(1<<26)
#define	CAPABILITY_FW_PVDEC					(IMG_UINT32)(1<<25)


/* The firmware can explicity say that it does not support a standard */
#define	DISABLE_VC1							(IMG_UINT32)(1<<8)

/* 
	HW capabilities related to HW video format support should be defined in
	bytes 2 and 3 of a 4-byte word
*/
#define CAPABILITY_HEVC		(1<<21)
#define CAPABILITY_VP8		(1<<20)
#define CAPABILITY_SORENSON	(1<<19)
#define CAPABILITY_AVS		(1<<18)
#define CAPABILITY_RV		(1<<17)
#define CAPABILITY_VP6	    (1<<16)
#define CAPABILITY_MPEG2	(1<<15)
#define CAPABILITY_MPEG4	(1<<14)
#define CAPABILITY_MPEG4_DP	(1<<13)
#define CAPABILITY_H264		(1<<12)
#define CAPABILITY_WMV9		(1<<11)
#define CAPABILITY_JPEG		(1<<10)
#define CAPABILITY_VC1_BP	(1<<9)
#define CAPABILITY_VC1		(1<<8)

/* 
	HW capabilities not related to video format support
	should be defined in lower byte
*/
#define CAPABILITY_LOSSLESS_H264	(1<<5)
#define CAPABILITY_EXTENDED_STRIDE	(1<<4)
#define CAPABILITY_IDCT_RESIDUAL	(1<<3)
#define CAPABILITY_ROTATION			(1<<2)
#define CAPABILITY_SCALING			(1<<1)
#define CAPABILITY_HD				(1<<0)


#if defined (__cplusplus)
}
#endif

#endif /* __MSVDXAPI_CONSTS_H__ */
