/*!
 *****************************************************************************
 *
 * @File       pixel_api.h
 * @Description    This file contains the header information for the generic pixel manipulation library.
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

#if !defined (__PIXEL_API_H__)
#define __PIXEL_API_H__

#include <img_types.h>
#include <img_defs.h>
#include <img_errors.h>
#include <img_pixfmts.h>
#include "img_structs.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DOXYGEN_CREATE_MODULES
/**
 * @defgroup IMGLIB_PIXEL Pixel API: pixel abstraction knowledge and access
 * @{
 */
/*-------------------------------------------------------------------------
 * Following elements are in the IMGLIB_PIXEL documentation module
 *------------------------------------------------------------------------*/
#endif

#define PIXEL_MAX_YUV_COMPONENTS	(32)					/**< @brief Max YUV components packet in one BOPs    */
/** @brief Return code to indicate end of image has been reached, when using Get/Set First/Next pixel functions.
 */
#define	PIXEL_END_OF_IMAGE_REACHED	(IMG_SUCCESS + 1)
#define	PIXEL_MAX_NAME_LENGTH 		30

typedef IMG_VOID * (*pixel_pfnMemoryTwiddlerFunction)(IMG_VOID *);

#define PIXEL_MULTICHROME   IMG_TRUE
#define PIXEL_MONOCHROME    IMG_FALSE
#define PIXEL_INVALID_BDC   8
#define IMG_MAX_NUM_PLANES		4
typedef struct
{
	IMG_BOOL abPlanes[IMG_MAX_NUM_PLANES];			/*! Booleans indicating which planes are in use. */
	IMG_UINT32 ui32BOPDenom;						/*! Common denominator for bytes per pixel calculation. */
	IMG_UINT32 aui32BOPNumer[IMG_MAX_NUM_PLANES];	/*! Per plane numerators for bytes per pixel calculation. */
	IMG_UINT32 ui32HDenom;							/*! Common denominator for horizontal pixel sub-sampling calculation. */
	IMG_UINT32 ui32VDenom;							/*! Common denominator for vertical pixel sub-sampling calculation. */
	IMG_UINT32 aui32HNumer[IMG_MAX_NUM_PLANES];		/*! Per plane numerators for horizontal pixel sub-sampling calculation. */
	IMG_UINT32 aui32VNumer[IMG_MAX_NUM_PLANES];		/*! Per plane numerators for vertical pixel sub-sampling calculation. */
} IMG_sPixelFormatDesc;

/*!
******************************************************************************

 @brief This type defines memory chroma interleaved order

******************************************************************************/
typedef enum
{
    PIXEL_INVALID_CI  = 0,
	PIXEL_UV_ORDER    = 1,
    PIXEL_VU_ORDER    = 2,
	PIXEL_YAYB_ORDER  = 4,
	PIXEL_AYBY_ORDER  = 8
} PIXEL_eChromaInterleaved;
/*!
******************************************************************************

 @brief This macro translates PIXEL_eChromaInterleaved values into value that can be used to write HW registers directly.

******************************************************************************/
#define PIXEL_GET_HW_CHROMA_INTERLEAVED(value)  ((value)&PIXEL_VU_ORDER ? IMG_TRUE : IMG_FALSE)

/*!
******************************************************************************

 @brief This type defines memory packing types

******************************************************************************/
typedef enum
{
    PIXEL_BIT8_MP		= 0, /**< @brief 8 bits format: no packing, whole byte is used */
	PIXEL_BIT10_MSB_MP  = 1, /**< @brief 10 bits format using most siginficant bits of a word (16b) */
    PIXEL_BIT10_LSB_MP  = 2, /**< @brief 10 bits format using least significant bits of a word (16b) */
	/**
	 * @brief 10 bits packed format using the 3 least significant 10 bits of a double word (32b)
	 *
	 * The double word is composed of 0b00CCCCCCCCCBBBBBBBBBBAAAAAAAAAA where A, B and C are the bits used to store the pixels' information.
	 */
    PIXEL_BIT10_MP		= 3
} PIXEL_eMemoryPacking;

/*!
******************************************************************************

 @brief This macro translates PIXEL_eMemoryPacking values into value that can be
 used to write HW registers directly.

******************************************************************************/
#define PIXEL_GET_HW_MEMORY_PACKING(value)   (   \
(value == PIXEL_BIT8_MP) 	   ? IMG_FALSE :     \
(value == PIXEL_BIT10_MSB_MP)  ? IMG_FALSE :     \
(value == PIXEL_BIT10_LSB_MP)  ? IMG_FALSE :     \
(value == PIXEL_BIT10_MP)      ? IMG_TRUE  :     \
IMG_FALSE)

/*!
******************************************************************************

 @brief This type defines chroma formats

******************************************************************************/
typedef enum
{
    PIXEL_FORMAT_MONO = 0,
	PIXEL_FORMAT_411  = 1,
    PIXEL_FORMAT_420  = 2,
    PIXEL_FORMAT_422  = 3,
    PIXEL_FORMAT_444  = 4,
    PIXEL_FORMAT_INVALID = 0xFF
} PIXEL_FormatIdc;

/*!
******************************************************************************

 @brief This macro translates PIXEL_FormatIdc values into value that can be
 used to write HW registers directly.

******************************************************************************/
#define PIXEL_GET_HW_CHROMA_FORMAT_IDC(value)   (   \
(value == PIXEL_FORMAT_MONO) ? 0 :                  \
(value == PIXEL_FORMAT_420)  ? 1 :                  \
(value == PIXEL_FORMAT_422)  ? 2 :                  \
(value == PIXEL_FORMAT_444)  ? 3 :                  \
PIXEL_FORMAT_INVALID )

/*!
******************************************************************************

 @brief This structure contains information about the pixel formats

******************************************************************************/
typedef struct
{
    IMG_ePixelFormat			ePixelFormat;
    PIXEL_eChromaInterleaved	eChromaInterleaved;
    IMG_BOOL					bChromaFormat;
    PIXEL_eMemoryPacking		eMemoryPacking;
    PIXEL_FormatIdc				eChromaFormatIdc;
    IMG_UINT32					ui32BitDepthY;
    IMG_UINT32					ui32BitDepthC;
    IMG_UINT32					ui32NoPlanes;
} PIXEL_sPixelInfo;

/*!
******************************************************************************

 @brief This macro can be used to fill a PIXEL control block automatically, from an
 IMG_sImageBufCB control block.

******************************************************************************/
#define	PIXEL_FILL_CONTROL_BLOCK_FROM_IMAGEBUFCB(PointerToPixelControlBlock,PointerToImageBufCB)		\
{																										\
	IMG_ASSERT ( PointerToPixelControlBlock != IMG_NULL );												\
	IMG_ASSERT ( PointerToImageBufCB != IMG_NULL );														\
																										\
	(PointerToPixelControlBlock)->ePixelColourFormat	= (PointerToImageBufCB)->ePixelFormat;			\
	(PointerToPixelControlBlock)->pvYBufBaseAddr		= (PointerToImageBufCB)->pvYBufAddr;			\
	(PointerToPixelControlBlock)->pvUVBufBaseAddr		= (PointerToImageBufCB)->pvUVBufAddr;			\
	(PointerToPixelControlBlock)->pvVBufBaseAddr		= (PointerToImageBufCB)->pvVBufAddr;			\
	(PointerToPixelControlBlock)->pvAlphaBufBaseAddr	= (PointerToImageBufCB)->pvAlphaBufAddr;		\
	(PointerToPixelControlBlock)->ui32ImageWidth		= (PointerToImageBufCB)->ui32ImageWidth;		\
	(PointerToPixelControlBlock)->ui32ImageHeight		= (PointerToImageBufCB)->ui32ImageHeight;		\
	(PointerToPixelControlBlock)->ui32YImageStride		= (PointerToImageBufCB)->ui32ImageStride;		\
}

/*!
******************************************************************************

 @brief This type defines the access mode

******************************************************************************/
typedef enum
{
    /** @brief The image in the buffer is treated as a progressive image and data
        from all lines is accessible.										*/
    PIXEL_MODE_PROGRESSIVE,
    /** @brief The image in the buffer is treated as two interlaced fields
        (field 0 and field 1), starting with the first line of
        field 0.  Only the field 0 lines are accessible. Heights should be
		specified in terms of a single field (i.e.: 'line 3' will access
		the third field 0 line, skipping all field 1 lines)					*/
    PIXEL_MODE_FIELD_0,
    /** @brief The image in the buffer is treated as two interlaced fields.
        Only the field 1 lines are accessible.	Heights should be
		specified in terms of a single field (i.e.: 'line 3' will access
		the third field 1 line, skipping all field 0 lines)					*/
    PIXEL_MODE_FIELD_1

} PIXEL_eMode;

/*!
******************************************************************************

 @brief This type defines the image in memory

******************************************************************************/
typedef struct
{
	/* Text representation of pixel type */
	#if defined PIXEL_LIB_INCLUDE_PIXEL_NAME_IN_INFO_STRUCT
	    char	acPixelFormatName [PIXEL_MAX_NAME_LENGTH];
	#endif

	/** @brief The number of pixels comprising a 'Block of pixels' (BOP), the smallest discrete element of data in this pixel colour format. */
	IMG_UINT32	ui32PixelsInBOP;
	/* All BOPs have the same number of pixels, but varying byte counts per component: */
	/** @brief The number of luma or RGB bytes in a BOP */
	IMG_UINT32	ui32YBytesInBOP;
	/** @brief Number of chrome/U bytes in a BOP (see details)
	 *
	 * The number of chroma bytes in a BOP - Only applies to pixel colour formats with a separate planar chroma component.
	 *
     * --- OR ---
	 *
     * The number of U bytes in a BOP - Only applies to pixel colour formats with a separate Y, U, V components.
	 */
	IMG_UINT32	ui32UVBytesInBOP;
	/** @brief The number of V bytes in a BOP -	Only applies to pixel colour formats with a separate Y, U, V components. */
    IMG_UINT32	ui32VBytesInBOP;
	/** @brief The number of alpha bytes in a BOP -	Only applies to pixel colour formats with a separate planar alpha component. */
	IMG_UINT32	ui32AlphaBytesInBOP;

	/*-------------------------------------------------------------------------*/

	/** @brief Set to IMG_TRUE if this buffer has a planar chroma component or has separate Y, U, V components. */
	IMG_BOOL	bIsPlanar;
	/** @brief Set to IMG_TRUE if the height (in lines) of the planar chroma component of this buffer is half the height of the planar luma component.
	 *
	 * This should only ever be non zero if 'bIsPlanar' is set to IMG_TRUE.
	 */
	IMG_BOOL	bUVHeightHalved;
	/** @brief Describes the UV stride in comparison to Y stride, multiplied by 4.
	 *
	 * Example, if UV stride is half the Y stride, then: ui32UVStrideRatioTimes4 = 0.5 * 4 = 2
	 */
    IMG_UINT32  ui32UVStrideRatioTimes4;
	/** @brief Set to IMG_TRUE if this buffer has a planar alpha component. */
	IMG_BOOL	bHasAlpha;

} PIXEL_sInfo;

/*!
******************************************************************************

 @brief This structure describes an image contained in memory.

 Sections (A) and (B) should be completed by the user before calls to PIXEL_ functions.
 In some cases, a control block should not be modified at all between PIXEL_ function calls - see individual function descriptions for details.

******************************************************************************/
typedef struct
{
	/* A.) To be set up by caller to BUF functions */
	IMG_ePixelFormat	ePixelColourFormat;		/* The pixel colour format of	*/
												/* the image in memory.			*/
	IMG_UINT32			ui32ImageWidth;			/* Image width in pixels.		*/
	IMG_UINT32          ui32ImageHeight;		/* Image height in pixels.		*/
	IMG_UINT8 *         pvYBufBaseAddr;			/* The byte address of the		*/
												/* luma / RGB data of the first */
												/* active pixel in the image.	*/
	IMG_UINT32			ui32YBufSize;			/* Size of above buffer			*/
    IMG_UINT8 *         pvUVBufBaseAddr;		/* The byte address of the		*/
												/* chroma data of the first		*/
												/* active pixel in the image.	*/
												/* This should be set to zero	*/
												/* for non planar images.		*/
	IMG_UINT32			ui32UVBufSize;			/* Size of above buffer			*/
    IMG_UINT8 *         pvVBufBaseAddr;		   /* The byte address of the V		*/
												/* chroma data of the first		*/
												/* active pixel in the image.	*/
												/* This should be set to zero	*/
												/* for non planar images.		*/
	IMG_UINT32			ui32VBufSize;			/* Size of above buffer			*/
    IMG_UINT8 *         pvAlphaBufBaseAddr;		/* The byte address of the		*/
												/* alpha data of the first		*/
												/* active pixel in the image.	*/
												/* This should be set to zero	*/
												/* for images which do not 		*/
												/* contain planar alpha.		*/
	IMG_UINT32			ui32AlphaBufSize;			/* Size of above buffer			*/
    IMG_UINT32          ui32YImageStride;		/* The stride, in bytes, of the	*/
												/* luma / RGB data of the		*/
												/* image. For planar images,	*/
												/* the chroma / alpha strides	*/
												/* are calculated automatically.*/
	PIXEL_eMode			eMode;					/* Controls how the buffer is	*/
												/* accessed by some PIXEL_		*/
												/* functions. See definition of	*/
												/* PIXEL_eMode for more details.*/

	/* B.) Twiddler function - if addresses need to be modified according to 	*/
	/* some algorithm before they are used to access memory, then this function	*/
	/* pointer should be pointed at the function which performs this operation.	*/
	/* The function must be of the form :										*/
	/*		IMG_VOID * MyFunction ( IMG_VOID * );								*/
	/*																			*/
	/* This pointer should be set to 'IMG_NULL' if no memory twiddling is		*/
	/* required.																*/
	pixel_pfnMemoryTwiddlerFunction	pfnTwiddlerFunction;

	/***************************************************************/
	/* Used internally by BUF lib - should NOT be modified by user */

	/* Copies of user values, that can be modified internally */
	IMG_UINT8 *			pvYBufAddr;
	IMG_UINT8 *			pvUVBufAddr;
	IMG_UINT8 *			pvVBufAddr;
	IMG_UINT8 *			pvAlphaBufAddr;
	IMG_UINT32          ui32InternalImageHeight;
	IMG_UINT32			ui32InternalYImageStride;

	IMG_UINT32          ui32PixelIndex;
    IMG_UINT8 *         pvLineYBufAddr;
    IMG_UINT8 *         pvLineUVBufAddr;
    IMG_UINT8 *         pvLineVBufAddr;
    IMG_UINT8 *         pvLineAlphaBufAddr;
    IMG_UINT32          ui32BufPixelNo;
    IMG_UINT32          ui32BufLineNo;
	IMG_BOOL			bEndOfImageHit;
	IMG_BOOL			bInsufficientData;

	/* Data I/O - should be filled with input data for an input function 	*/
	/* OR will contain data AFTER call to an output function.				*/
    IMG_UINT32          ui32Y[PIXEL_MAX_YUV_COMPONENTS];
    IMG_UINT32          ui32U[PIXEL_MAX_YUV_COMPONENTS];
    IMG_UINT32          ui32V[PIXEL_MAX_YUV_COMPONENTS];
    IMG_UINT32          ui32Alpha[PIXEL_MAX_YUV_COMPONENTS];
	/***************************************************************/

} PIXEL_sGetSetCB;


extern IMG_CHAR acPixelFormatIdcNames[6][16];
extern IMG_CHAR acPixelMemoryPackingNames[4][64];
extern IMG_CHAR acPixelChromaInterleavedNames[5][16];


#ifdef DOXYGEN_CREATE_MODULES
/**
 * @name Pixel knowledge functions
 * @{
 */
/*-------------------------------------------------------------------------
 * Following elements are in the pixel knowledge group
 *------------------------------------------------------------------------*/
#endif

/*!
******************************************************************************

 @brief Returns a pointer to a 'PIXEL_sInfo' structure, which lists characteristics
  of a buffer which can be derived from its pixel colour format.

******************************************************************************/
extern PIXEL_sInfo* PIXEL_GetBufferInfoFromPixelColourFormat(IMG_ePixelFormat ePixelColourFormat);

/*!
******************************************************************************

 @brief This function provides the Viddec software version and build number.
 @note Does not return NULL

 @Input ePixelFormat Pixel format of the stream.

 @return Pointer to the element of aPIXEL_sPixelInfo array which contains pixel format related info.
 @return If not found return a pointer to the default pixel format (IMG_PIXFMT_UNDEFINED)

******************************************************************************/
extern PIXEL_sPixelInfo* PIXEL_GetPixelInfo(const IMG_ePixelFormat ePixelFormat);


/*
******************************************************************************

 @brief Returns the correct pixel format based on the enum IMG_ePixelFormat

 @Input	eChromaFormatIdc
 @Input eChromaInterleaved
 @Input eMemoryPacking
 @Input ui32BitDepthY
 @Input ui32BitDepthC

 @Return member of the IMG_ePixelFormat enum

******************************************************************************/
extern IMG_ePixelFormat PIXEL_GetPixelFormat(
    PIXEL_FormatIdc eChromaFormatIdc,
    PIXEL_eChromaInterleaved eChromaInterleaved,
    PIXEL_eMemoryPacking eMemoryPacking,
    IMG_UINT32 ui32BitDepthY,
    IMG_UINT32 ui32BitDepthC,
    IMG_UINT32 ui32NoPlanes
);



/*!
******************************************************************************

 @Function              PIXEL_YUVGetDescriptor

 @Description

 Obtains the pixel format descriptor.

 @Input     psPixelInfo : Pointer to pixel information.

 @Output    psDesc : Pointer to pixel format descriptor.

 @Return	IMG_RESULT  : This function returns either IMG_SUCCESS or an
						  error code.

******************************************************************************/
extern IMG_RESULT PIXEL_YUVGetDescriptor(
    PIXEL_sPixelInfo        * psPixelInfo,
    IMG_sPixelFormatDesc  * psDesc
);


/*!
******************************************************************************

 @brief Fills an IMG_ePixelFormatDesc structure with a description of the given pixel format code.

 @Input ePixelFormat Pixel format code.
 @Input psFormatDesc Pointer to an IMG_ePixelFormatDesc structure to fill out.

 @return IMG_SUCCESS

******************************************************************************/
IMG_RESULT PIXEL_GetFormatDesc(IMG_ePixelFormat ePixelFormat, IMG_sPixelFormatDesc* psFormatDesc);

/*!
******************************************************************************

 @Description

 Generates pixel format code specified by factors from IMG_ePixelFormatDesc
 structure. Created pixel format is from range [IMG_PIXFMT_ARBPLANAR8,
 IMG_PIXFMT_ARBPLANAR8_LAST], suitable for description of JPEG.
 This function is opposite to PIXEL_GetFormatDesc().

 @brief Generates pixel format code specified by factors.

 @Output pePixelFormat Generated pixel format code.

 @Input psFormatDesc Pointer to an IMG_ePixelFormatDesc structure.

 @return IMG_SUCCESS

******************************************************************************/
IMG_RESULT PIXEL_GenPixFormat(IMG_ePixelFormat *pePixelFormat, IMG_sPixelFormatDesc* psFormatDesc);

#ifdef DOXYGEN_CREATE_MODULES
/**
 * @}
 */
/*-------------------------------------------------------------------------
 * end of the pixel knowledge group
 *------------------------------------------------------------------------*/

/**
 * @name Pixel access
 * @{
 */
/*-------------------------------------------------------------------------
 * Following elements are in the pixel access group
 *------------------------------------------------------------------------*/
#endif

/*!
******************************************************************************

 @brief This function is used to set a pixel in an image buffer to a particular value.

 The caller must set up a 'PIXEL_sGetSetCB' structure to point at the start of
 the buffer, and to describe the buffer format.

 @note The fields of the structure can be changed by calls to this function.

 @note The 'eMode' member of the 'PIXEL_sGetSetCB' is ignored by this function.
 The data will always be treated as progressive, and the values of ui32X and ui32Y should be set accordingly.

 @Input psGetSetCB A pointer to a control block describing the image to be accessed.
 @Input ui32X The x co-ordinate of the pixel to be accessed.
 @Input ui32Y The y co-ordinate of the pixel to be accessed.
 @Input ui32YorR Pixel's Y, R component or colour index, as a 10-bit value.
 @Input ui32UorG Pixel's U or G component, as a 10-bit value.
 @Input ui32VorB Pixel's V or B component, as a 10-bit value.
 @Input ui32Alpha Pixel's Alpha component, as a 10-bit value.

 @return This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT PIXEL_SetPixel(
	PIXEL_sGetSetCB* psGetSetCB,
	IMG_UINT32 ui32X,
	IMG_UINT32 ui32Y,
	IMG_UINT32 ui32YorR,
	IMG_UINT32 ui32UorG,
	IMG_UINT32 ui32VorB,
	IMG_UINT32 ui32Alpha
);

/*!
******************************************************************************

 @brief This function is used to set a group pixel in an image buffer to a particular value.

 The caller must set up a 'PIXEL_sGetSetCB' structure to point at the start of
 the buffer, and to describe the buffer format.

 @note The fields of the structure can be changed by calls to this function.

 @note The 'eMode' member of the 'PIXEL_sGetSetCB' is ignored by this function.
		The data will always be treated as progressive, and the values of
		ui32X and ui32Y should be set accordingly.

 @note This function will not span lines or allow the "group" to run on the end of
        a line

 @Input psGetSetCB A pointer to a control block describing the image to be accessed.
 @Input ui32X The x co-ordinate of the start of the group of pixels to be accessed.
 @Input ui32Y The y co-ordinate of the pixel to be accessed.
 @Output pui32YorR A pointer to an array used to specify the pixel's Y, R component or colour index values, as a 10-bit value.
 @Output pui32UorG A pointer to an array used to specify the pixel's U or G component values, as a 10-bit value.
 @Output pui32VorB A pointer to an array used to specify the pixel's V or B component values, as a 10-bit value.
 @Output pui32Alpha A pointer to an array used to specify the pixel's Alpha component values, as a 10-bit value.
 @Input ui32MaxPixels Max number of pixels to be set.

 @return The number of pixels set (<= to ui32MaxPixels).

******************************************************************************/
IMG_UINT32 PIXEL_SetPixelGroup(
	PIXEL_sGetSetCB *	psGetSetCB,
	IMG_UINT32 ui32X,
	IMG_UINT32 ui32Y,
	IMG_UINT32 *pui32YorR,
	IMG_UINT32 *pui32UorG,
	IMG_UINT32 *pui32VorB,
	IMG_UINT32 *pui32Alpha,
	IMG_UINT32 ui32MaxPixels
);

/*!
******************************************************************************

 @brief This function is used to set the first pixel in an image buffer.

 The caller must complete the relevant sections of a 'PIXEL_sGetSetCB' structure,
 which is passed to the function.

 @note The fields of the structure can be changed by calls to this function.

 @Input psGetSetCB A pointer to a control block describing the image to be accessed.
 @Input ui32Y Pixel's Y component, as a 10-bit value.
 @Input ui32U Pixel's U component, as a 10-bit value.
 @Input ui32V Pixel's V component, as a 10-bit value.
 @Input ui32Alpha Pixel's Alpha component, as a 10-bit value.

 @return This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT PIXEL_SetFirstPixel(
	PIXEL_sGetSetCB *psGetSetCB,
	IMG_UINT32 ui32Y,
	IMG_UINT32 ui32U,
	IMG_UINT32 ui32V,
	IMG_UINT32 ui32Alpha
);

/*!
******************************************************************************

 @brief This function is used to set the next pixel in an image buffer.
 @warning Calls to this function MUST follow an initial call to 'PIXEL_SetFirstPixel'.

 @warning The caller should pass the address of the 'PIXEL_sGetSetCB' structure
 which was previously passed to 'PIXEL_SetFirstPixel'.
 The structure should not be modified by the user after the first call to 'SetFirstPixel'.

 @note The fields of the structure can be changed by calls to this function.

 @Input psGetSetCB A pointer to a control block describing the image to be accessed.
 @Input ui32Y Pixel's Y component, as a 10-bit value.
 @Input ui32U Pixel's U component, as a 10-bit value.
 @Input ui32V Pixel's V component, as a 10-bit value.
 @Input ui32Alpha Pixel's Alpha component, as a 10-bit value.

 @return This function returns IMG_SUCCESS until the first call which exceeds the end of the
 image, at which point 'PIXEL_END_OF_IMAGE_REACHED' is returned.
 No data will be set as a result of a call to this function which subsequently returns 'end
 of image reached'.
 Successive calls to this function AFTER a call which has returned 'end of image reached'
 (and before a subsequent call to 'SetFirstPixel' will cause an assert).

******************************************************************************/
extern IMG_RESULT PIXEL_SetNextPixel(
	PIXEL_sGetSetCB *psGetSetCB,
	IMG_UINT32 ui32Y,
	IMG_UINT32 ui32U,
	IMG_UINT32 ui32V,
	IMG_UINT32 ui32Alpha
);

/*!
******************************************************************************

 @brief This function is used to terminate a sequence of pixel setting, using the
  sequence BFM_SetFirstPixel, followed by n x BFM_SetNextPixel.

 This function must be called after the last call to 'BFM_SetNextPixel'.

 @return This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
IMG_RESULT PIXEL_SetEnd(PIXEL_sGetSetCB *psGetSetCB);

/*!
******************************************************************************

 @brief This function is used to get the value of a pixel from an image buffer.

 The caller must set up a 'PIXEL_sGetSetCB' structure to point at the start of
 the buffer, and to describe the buffer format.

 @note The fields of the structure can be changed by calls to this function.

 @note The 'eMode' member of the 'PIXEL_sGetSetCB' is ignored by this function.
		The data will always be treated as progressive, and the values of
		ui32X and ui32Y should be set accordingly.

 @Input psGetSetCB A pointer to a control block describing the image to be accessed.
 @Input ui32X The x co-ordinate of the pixel to be accessed.
 @Input ui32Y The y co-ordinate of the pixel to be accessed.
 @Output pui32YorR A pointer used to return the pixel's Y, R component or colour index, returned as a 10-bit value.
 @Output pui32UorG A pointer used to return the pixel's U or G component, returned as a 10-bit value.
 @Output pui32VorB A pointer used to return the pixel's V or B component, returned as a 10-bit value.
 @Output pui32Alpha A pointer used to return the pixel's Alpha component, returned as a 10-bit value.

 @return This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT PIXEL_GetPixel(
	PIXEL_sGetSetCB *psGetSetCB,
	IMG_UINT32 ui32X,
	IMG_UINT32 ui32Y,
	IMG_UINT32 *pui32YorR,
	IMG_UINT32 *pui32UorG,
	IMG_UINT32 *pui32VorB,
	IMG_UINT32 *pui32Alpha
);

/*!
******************************************************************************

 @brief This function is used to get the value of pixel in a group from an image buffer.

 The caller must set up a 'PIXEL_sGetSetCB' structure to point at the start of
 the buffer, and to describe the buffer format.

 @note The fields of the structure can be changed by calls to this function.

 @note The 'eMode' member of the 'PIXEL_sGetSetCB' is ignored by this function.
		The data will always be treated as progressive, and the values of
		ui32X and ui32Y should be set accordingly.

 @note This function will not span lines or allow the "group" to run on the end of
        a line

 @Input psGetSetCB A pointer to a control block describing the image to be accessed.
 @Input ui32X The x co-ordinate of the start of the group of pixel to be accessed.
 @Input ui32Y The y co-ordinate of the pixel to be accessed.
 @Output pui32YorR A pointer an array used to return the pixel's Y, R component or colour index values, returned as a 10-bit value.
 @Output pui32UorG A pointer an array used to return the pixel's U or G component values, returned as a 10-bit value.
 @Output pui32VorB A pointer an array used to return the pixel's V or B component values, returned as a 10-bit value.
 @Output pui32Alpha A pointer an array used to return the pixel's Alpha component values, returned as a 10-bit value.
 @Input ui32MaxPixels : The max number of pixels to "get".

 @return The number of pixels "got" (<= to ui32MaxPixels).

******************************************************************************/
IMG_UINT32 PIXEL_GetPixelGroup(
	PIXEL_sGetSetCB *psGetSetCB,
	IMG_UINT32 ui32X,
	IMG_UINT32 ui32Y,
	IMG_UINT32 *pui32YorR,
	IMG_UINT32 *pui32UorG,
	IMG_UINT32 *pui32VorB,
	IMG_UINT32 *pui32Alpha,
    IMG_UINT32 ui32MaxPixels
);

/*!
******************************************************************************

 @brief This function is used to get the first pixel from an image buffer.

 The caller must complete the relevant sections of a 'PIXEL_sGetSetCB' structure,
 which is passed to the function.

 @note The fields of the structure can be changed by calls to this function.

 @Input psGetSetCB A pointer to a control block describing the image to be accessed.
 @Output pui32Y A pointer used to return the pixel's Y component, returned as a 10-bit value.
 @Output pui32U A pointer used to return the pixel's U component, returned as a 10-bit value.
 @Output pui32V A pointer used to return the pixel's V component, returned as a 10-bit value.
 @Output pui32Alpha A pointer used to return the pixel's Alpha component, returned as a 10-bit value.

 @return This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT PIXEL_GetFirstPixel(
	PIXEL_sGetSetCB *psGetSetCB,
	IMG_UINT32 *pui32Y,
	IMG_UINT32 *pui32U,
	IMG_UINT32 *pui32V,
	IMG_UINT32 *pui32Alpha
);

/*!
******************************************************************************

 @brief This function is used to get the next pixel from an image buffer.
 @warning Calls to this function MUST follow an initial call to 'BFM_GetFirstPixel'.

 @warning The caller should pass the address of the 'PIXEL_sGetSetCB' structure
 which was previously passed to 'PIXEL_GetFirstPixel'. The structure should
 not be modified by the user after the first call to 'GetFirstPixel'.

 @note The fields of the structure can be changed by calls to this function.

 @Input psGetSetCB A pointer to a control block describing the image to be accessed.
 @Output pui32Y A pointer used to return the pixel's Y component, returned as a 10-bit value.
 @Output pui32U A pointer used to return the pixel's U component, returned as a 10-bit value.
 @Output pui32V A pointer used to return the pixel's V component, returned as a 10-bit value.
 @Output pui32Alpha A pointer used to return the pixel's Alpha component, returned as a 10-bit value.

 @return This function returns IMG_SUCCESS until the first call which exceeds the end of the image, at which
 point 'PIXEL_END_OF_IMAGE_REACHED' is returned.
 No data will be read as a result of a call to this function which subsequently returns 'end of image reached'.
 Successive calls to this function AFTER a call which has returned 'end of image reached' (and before
 a subsequent call to 'GetFirstPixel' will cause an assert).

******************************************************************************/
extern IMG_RESULT PIXEL_GetNextPixel(
	PIXEL_sGetSetCB	*psGetSetCB,
	IMG_UINT32 *pui32Y,
	IMG_UINT32 *pui32U,
	IMG_UINT32 *pui32V,
	IMG_UINT32 *pui32Alpha
);

/******************************************************************************

 @brief This function is provided for reasons of symmetry, although it is purely a stub.

 When SETTING pixels in a buffer, using 'SetFirstPixel' followed by numerous calls to
 'SetNextPixel', the process must be completed with a call to 'SetEnd'. Although the
 'GetEnd' call is not actually needed, as memory has not been modified, the function
 is provided so that the 'GetFirstPixel', 'GetNextPixel', 'GetEnd' sequence reflects
 that used for setting pixels.

 @note It is not necessary to call this function - see above.

 @Input psGetSetCB A pointer to a control block describing the image to be accessed.

******************************************************************************/
IMG_RESULT PIXEL_GetEnd(PIXEL_sGetSetCB	*psGetSetCB);

#ifdef DOXYGEN_CREATE_MODULES
/**
 * @}
 */
/*-------------------------------------------------------------------------
 * end of the pixel access group
 *------------------------------------------------------------------------*/

/**
 * @}
 */
/*-------------------------------------------------------------------------
 * end of IMGLIB_PIXEL documentation module
 *------------------------------------------------------------------------*/
#endif

#ifdef __cplusplus
}
#endif

#endif	/* __PIXEL_API_H__ */
