/*!
 *****************************************************************************
 *
 * @File       vxe_common.h
 * @Title      VXE common definitions
 * @Description    VXE common definitions
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

#ifndef _VXECOMMON_H_
#define _VXECOMMON_H_

#include "topazscfwif.h"

/*!
*****************************************************************************

 @details    Enum describing error codes

 @brief          Error code

****************************************************************************/
typedef enum
{
	IMG_ERR_OK					= 0,	//!< OK
	IMG_ERR_SURFACE_LOCKED		= 1,	//!< The requested surface was locked
	IMG_ERR_MEMORY				= 2,	//!< A memory error occured
	IMG_ERR_FILE				= 3,	//!< A file error occured
	IMG_ERR_NOBUFFERAVAILABLE	= 4,	//!< No buffer was available
	IMG_ERR_COMPLETE			= 5,	//!< Command is complete
	IMG_ERR_INVALID_CONTEXT		= 6,	//!< An invalid context was given
	IMG_ERR_INVALID_SIZE		= 7,	//!< An invalid size was given
	IMG_ERR_TIMEOUT				= 8,	//!< Timeout
	IMG_ERR_RETRY				= 9,
	IMG_ERR_UNEXPECTED_STATE	= 10,	//!<Unexpected state
	IMG_ERR_UNDEFINED			= -1
} IMG_ERRORCODE;



/*!
*****************************************************************************

 @details    Enum describing buffer lock status

 @brief          Buffer lock status

****************************************************************************/
typedef enum
{
	BUFFER_FREE	= 1,  //!< Buffer is not locked
	HW_LOCK,          //!< Buffer is locked by hardware
	SW_LOCK,          //!< Buffer is locked by software
	NOTDEVICEMEMORY,  //!< Buffer is not a device memory buffer
} LOCK_STATUS;

/*!
*****************************************************************************

 @details    Struct describing a coded data buffer

 @brief          Coded data buffer

****************************************************************************/
typedef struct
{
	struct MEMORY_INFO_TAG *	pMemInfo;				//!< Pointer to the memory handle for the buffer
	LOCK_STATUS					sLock;                  //!< Lock status for the buffer
	IMG_UINT32					ui32Size;               //!< Size in bytes of the buffer
	IMG_UINT32					ui32BytesWritten;       //!< Number of bytes written into buffer
} IMG_BUFFER, IMG_CODED_BUFFER;

typedef struct
{
	IMG_BUFFER *psCodePackageFWBuffer;
	CODED_PACKAGE_DMA_INFO * psCodedPackageFW;
} CODED_INFO;

#if defined(HW_4_0)
typedef struct
{
	IMG_UINT32	ui32LinkedListMem;
	IMG_UINT32	ui32LinkedListNext;
} LINKED_LIST_NODE;
#endif

// This structure is used by the Drivers
typedef struct
{
	CODED_INFO sMTXInfo;
	IMG_CODED_BUFFER *paCodedBuffer[MAX_CODED_BUFFERS_PER_PACKAGE]; // Array of pointers to buffers
	IMG_BUFFER *psHeaderBuffer;
#if defined(HW_4_0)
	IMG_BUFFER *psLinkedList;
#endif
	IMG_UINT8 ui8NumCodedBuffers;
	IMG_UINT8 ui8Busy;
} CODED_PACKAGE_HOST;

/*!
*****************************************************************************

 @details    Struct describing surface component info

 @brief          Surface component info

****************************************************************************/
typedef struct
{
	IMG_UINT32	ui32Step;
	IMG_UINT32	ui32Width;
	IMG_UINT32	ui32Height;
	IMG_UINT32	ui32PhysWidth;
	IMG_UINT32	ui32PhysHeight;
} IMG_SURF_COMPONENT_INFO;

/*!
*****************************************************************************

 @details    Struct describing a frame

 @brief          Frame information

****************************************************************************/
typedef struct
{
	IMG_BUFFER *			psYPlaneBuffer;						//!< pointer to the image buffer
	IMG_BUFFER *			psUPlaneBuffer;						//!< pointer to the image buffer
	IMG_BUFFER *			psVPlaneBuffer;						//!< pointer to the image buffer
	IMG_UINT32				ui32WidthBytes;							//!< stride of pBuffer
	IMG_UINT32				ui32Height;							//!< height of picture in pBuffer

	IMG_UINT32				ui32ComponentCount;					//!< number of colour components used
	IMG_FORMAT				eFormat;

	IMG_UINT32				aui32ComponentOffset[3];
	IMG_UINT32				aui32BottomComponentOffset[3];
	IMG_SURF_COMPONENT_INFO	aui32ComponentInfo[3];

	IMG_INT32				i32YComponentOffset;
	IMG_INT32				i32UComponentOffset;
	IMG_INT32				i32VComponentOffset;

	IMG_INT32				i32Field0YOffset, i32Field1YOffset;
	IMG_INT32				i32Field0UOffset, i32Field1UOffset;
	IMG_INT32				i32Field0VOffset, i32Field1VOffset;

	IMG_UINT16				ui16SrcYStrideBytes, ui16SrcUVStrideBytes;
	IMG_BOOL	bImported;
} IMG_FRAME, JPEG_SOURCE_SURFACE;


/*!
*****************************************************************************

 @details    Struct describing an array of frames

 @brief          Frame array

****************************************************************************/
typedef struct
{
	IMG_UINT32 ui32ArraySize;   //!< Number of frames in array
	IMG_FRAME *aFrame;          //!< Pointer to start of frame array
} IMG_FRAME_ARRAY;


/*!
*****************************************************************************

 @details    Struct describing list items

 @brief          List item structure

****************************************************************************/
typedef struct _LIST_ITEM_
{
	struct _LIST_ITEM_ *psNext;		//!< Next item in the list
	IMG_VOID *pvData;				//!< pointer to list item data
} LIST_ITEM;


/*!
*****************************************************************************

 @details    Struct describing rate control params

 @brief          Rate control parameters

****************************************************************************/
typedef struct
{
	IMG_UINT32	ui32BitsPerSecond;			//!< Bit rate
	IMG_UINT32	ui32TransferBitsPerSecond;	//!< Transfer rate of encoded data from encoder to the output
	IMG_UINT32	ui32InitialQpI;				//!< Initial QP I frames (only field used by JPEG)
	IMG_UINT32	ui32InitialQpP;				//!< Initial QP P frames (only field used by JPEG)
	IMG_UINT32	ui32InitialQpB;				//!< Initial QP B frames (only field used by JPEG)
	IMG_UINT32	ui32BUSize;					//!< Basic unit size
	IMG_UINT32	ui32FrameRate;
	IMG_UINT32	ui32BufferSize;
	IMG_UINT32	ui32IntraFreq;
	IMG_INT16	iMinQP;
	IMG_INT16	iMaxQP;
	IMG_BOOL	bRCEnable;
	IMG_INT32	i32InitialLevel;
	IMG_INT32	i32InitialDelay;	
	IMG_UINT16	ui16BFrames;
	IMG_BOOL16	b16Hierarchical;

	IMG_BOOL  	bEnableSliceBob;	//!< Enable movement of slice boundary when Qp is high
	IMG_UINT8  ui8MaxSliceBob;     //!< Maximum number of rows the slice boundary can be moved
	IMG_UINT8  ui8SliceBobQp;		//!< Minimum Qp at which slice bobbing should take place

	IMG_INT8	i8QCPOffset;
	IMG_BOOL	bScDetectDisable;
	IMG_UINT32	ui32SliceByteLimit;
	IMG_UINT32	ui32SliceMBLimit;
	IMG_RCMODE	eRCMode;
	IMG_RC_VCM_MODE	eRCVcmMode;
	IMG_UINT32	uRCCfsMaxMarginPerc;
	IMG_BOOL	bDisableFrameSkipping;
#if defined(HW_4_0)	
#if defined(VP8_RC)
	IMG_BOOL	bDisableVp8Segmentation;
	IMG_UINT8	ui8Vp8NumTemporalLayers;
	IMG_UINT32	ui32Vp8Layer0Bitrate;
	IMG_UINT32	ui32Vp8Layer1Bitrate;
	IMG_UINT32	ui32Vp8Layer2Bitrate;
#endif
#endif
	IMG_BOOL16	bDisableVcmHardware; 
} IMG_RC_PARAMS;


/*!
*****************************************************************************
*
* @details    
*
* @brief      Bit fields for ui32MmuFlags
*
****************************************************************************/
#define MMU_USE_MMU_FLAG		0x00000001
#define MMU_TILED_FLAG			0x00000002
#define MMU_EXTENDED_ADDR_FLAG	0x00000004
#define MMU_SECURE_FW_UPLOAD	0x00000008
#define MMU_TILED_INTERLEAVED	0x00000010



#endif
