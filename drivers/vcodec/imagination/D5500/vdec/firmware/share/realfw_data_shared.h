/*!
 *****************************************************************************
 *
 * @File       realfw_data_shared.h
 * @Title      Public data structures for the mpeg4 parser firmware module
 * @Description    Public data structures for the mpeg4 parser firmware module
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

#ifdef USE_SHARING
#endif

#ifndef _REALFW_DATA_H_
#define _REALFW_DATA_H_

#include "vdecfw_share.h"

#include "img_types.h"
#include "vdecfw.h"

#define REALFW_MAX_RPR_IMAGES           8
#define REALFW_MAX_FRAGMENTS            (0x100)
#define REALFW_NUM_START_BYTES_COPIED   12

/*!
******************************************************************************
 This type defines the codec mode parameter
******************************************************************************/
typedef enum
{
    REAL_CODEC_RV30     = 0,
    REAL_CODEC_RV30_RAW = 1,
    REAL_CODEC_RV40     = 2,
    REAL_CODEC_RV40_RAW = 3

} REALFW_eCodecMode;

/*
******************************************************************************
 This type defines the picture type parameter
******************************************************************************/
typedef enum
{
    REAL_INTRAPIC        = 0x0,
    REAL_FORCED_INTRAPIC = 0x1,
    REAL_INTERPIC        = 0x2,
    REAL_TRUEBPIC        = 0x3

} REALFW_ePicType;

typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, ui16ImageWidth);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, ui16ImageHeight);

} REALFW_RPR_Images;

/*!
******************************************************************************

 This describes the sequence header data required by the Real Video firmware that should
 be supplied by the Host.

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, REALFW_eCodecMode, eCodecMode);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32SeqFlags);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, REALFW_RPR_Images, asRPRImages[REALFW_MAX_RPR_IMAGES]);

} REALFW_sSequenceHeader;



/*!
******************************************************************************

 This describes the picture level info required by the Real Video firmware that should
 be supplied by the Host.

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32FragmentSize[REALFW_MAX_FRAGMENTS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32NumFragments);

} REALFW_sPictureHeader;


/*!
******************************************************************************

 This describes an RealVideo picture. It is part of the Context data

******************************************************************************/
typedef struct
{

    VDECFW_sImageBuffer  sPrimary;                 //!< Primary decode buffer base addresses
    VDECFW_sImageBuffer  sAlternate;               //!< buffer base addresses for alternate output

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32MbParamsBaseAddress);  //!< Macroblock parameters base address for the picture
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TransactionId);        //!< Unique ID for this picture
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8DisplayFlags);          //!< Flags for this picture for the display process
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bSentForDisplay);          //!< If this picture has been sent for display
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, REALFW_ePicType, eCodingType);              //!< Frame type
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, ui16TemporalRef);          //!< Temporal reference
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Width);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Height);

} REALFW_sPicture;


/*!
******************************************************************************

 This describes the Real Video parser component "Header data", shown in the
 Firmware Memory Layout diagram. This data is required by the Real Video firmware
 and should be supplied by the Host.

******************************************************************************/
typedef struct
{
    REALFW_sPictureHeader  sPicHdrInfo;              //!< Picture level info

    VDECFW_sImageBuffer    sPrimary;                 //!< Primary decode buffer base addresses
    VDECFW_sImageBuffer    sAlternate;               //!< buffer base addresses for alternate output

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32MbParamsBaseAddress);  //!< Macroblock parameters base address for the picture

} REALFW_sHeaderData;


/*!
******************************************************************************
 This struct contains REAL RPR parameters
******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_INT32, i32AxInitial);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_INT32, i32AxIncrement);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_INT32, i32AyInitial);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_INT32, i32AyIncrement);

} REALFW_sRprParams;


/*!
******************************************************************************

 This describes the Real Video parser component "Context data", shown in the
 Firmware Memory Layout diagram. This data is the state preserved across
 pictures. It is loaded and saved by the Firmware, but requires the host to
 provide buffer(s) for this.

******************************************************************************/
typedef struct
{
    REALFW_sPicture         sOldRefPic;
    REALFW_sPicture         sNewRefPic;
    REALFW_sSequenceHeader  sSeqHdrInfo;                 //!< Sequence level info
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, ui16lastSlicePictureWidth);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, ui16lastSlicePictureHeight);

} REALFW_sContextData;
#endif /* _REALFW_DATA_H_*/
