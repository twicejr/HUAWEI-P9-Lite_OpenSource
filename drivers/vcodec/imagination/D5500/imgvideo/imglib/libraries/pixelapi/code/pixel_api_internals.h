/*!
 *****************************************************************************
 *
 * @File       pixel_api_internals.h
 * @Description    This file contains the header information for the internal functions used by
 *  the generic pixel manipulation library.
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

#if !defined (__PIXEL_API_INTERNALS_H__)
#define __PIXEL_API_INTERNALS_H__

#ifdef DOXYGEN_CREATE_MODULES
/**
 * @defgroup IMGLIB_PIXEL Pixel API: pixel abstraction knowledge and access
 * @{
 */
/*-------------------------------------------------------------------------
 * Following elements are in the IMGLIB_PIXEL documentation module
 *------------------------------------------------------------------------*/

/**
 * @name Internal functions
 * @{
 */
/*-------------------------------------------------------------------------
 * Following elements are in the itnernals
 *------------------------------------------------------------------------*/
#endif

/* Defines */

/* Macros */
//#define	PIXEL_GET_UV_STRIDE(ControlBlock)((psBufInfo->bUVStrideHalved==IMG_TRUE)?(ControlBlock->ui32InternalYImageStride/2):(ControlBlock->ui32InternalYImageStride))
#define	PIXEL_GET_UV_STRIDE(ControlBlock)((psBufInfo->ui32UVStrideRatioTimes4 * ControlBlock->ui32InternalYImageStride) / 4)

#define	PIXEL_GET_UV_HEIGHT(ControlBlock)((psBufInfo->bUVHeightHalved==IMG_TRUE)?(ControlBlock->ui32InternalImageHeight/2):(ControlBlock->ui32InternalImageHeight))


#define	PIXEL_GET_PIXEL_INFO(PixelColourFormat,TablePointer)							\
{																						\
	IMG_ASSERT ( TablePointer == IMG_NULL );											\
	TablePointer = PIXEL_GetBufferInfoFromPixelColourFormat( PixelColourFormat );		\
	IMG_ASSERT ( TablePointer != IMG_NULL );											\
}

#define	PIXEL_TWIDDLE_ADDRESS(ControlBlock,Address)((ControlBlock->pfnTwiddlerFunction==IMG_NULL)?Address:((ControlBlock->pfnTwiddlerFunction)(Address)))

/* Typedefs */
typedef struct pixel_tag_sPixelInfoTable
{
	IMG_ePixelFormat				ePixelColourFormat;
	PIXEL_sInfo						sInfo;
	
}	pixel_sPixelInfoTable;

/* Externs */
extern	pixel_sPixelInfoTable		PIXEL_asPixelInfo			[];

/* Function prototypes */
pixel_sPixelInfoTable *	pixel_GetPixelInfoFromPixelColourFormat	(	IMG_ePixelFormat		ePixelColourFormat	);
IMG_VOID				pixel_BlockNextBOPs						(	PIXEL_sGetSetCB *		psGetSetCB			);
IMG_VOID				pixel_DeblockNextBOPs					(	PIXEL_sGetSetCB *		psGetSetCB			);

/*!
******************************************************************************

 @brief Returns a pointer to a 'PIXEL_sInfo' structure, which lists characteristics
  of a buffer which can be derived from its pixel colour format.

******************************************************************************/
extern PIXEL_sInfo* PIXEL_GetBufferInfoFromPixelColourFormat(IMG_ePixelFormat ePixelColourFormat);

#ifdef DOXYGEN_CREATE_MODULES
/**
 * @}
 */
/*-------------------------------------------------------------------------
 * end of the Internals
 *------------------------------------------------------------------------*/

/**
 * @}
 */
/*-------------------------------------------------------------------------
 * Following elements are in the IMGLIB_PIXEL documentation module
 *------------------------------------------------------------------------*/
#endif

#endif /* __PIXEL_API_INTERNALS_H__ */

