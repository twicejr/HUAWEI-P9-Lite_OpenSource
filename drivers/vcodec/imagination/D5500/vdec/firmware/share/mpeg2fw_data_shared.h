/*!
 *****************************************************************************
 *
 * @File       mpeg2fw_data_shared.h
 * @Title      Public data structures for the mpeg2 parser firmware module
 * @Description    Public data structures for the mpeg2 parser firmware module
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

#ifndef _MPEG2FW_DATA_H_
#define _MPEG2FW_DATA_H_

#include "vdecfw_share.h"

#include "img_types.h"
#include "vdecfw.h"

#define MPEG2FW_QUANT_MAT_SIZE      64   /* Size of quantiser matrices */

typedef enum
{
    MPEG2FW_I = 0,
    MPEG2FW_P,
    MPEG2FW_B,
    MPEG2FW_MAX

} MPEG2FW_eCodingType;

/*!
******************************************************************************

 This describes an MPEG2 picture. It is part of the Context data

******************************************************************************/
typedef struct
{
    VDECFW_sImageBuffer          sPrimary;             /*!< Primary decode buffer base addresses */

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TransactionId);     /*!< Unique ID for this frame or first field of this picture */

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8DisplayFlags);      /*!< Flags for this picture for the display process */

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, MPEG2FW_eCodingType, ePicCodingType);       /*!< Picture coding type (I, P, B) */

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bSentForDisplay);      /*!< Whether picture was already added to display list in
                                                            picture manager*/
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PicCount);         /*!< Picture order count */

} MPEG2FW_sPicture;


/*!
******************************************************************************

 This describes the MPEG2 Sequence level data required by the MPEG2
 firmware that should be supplied by the Host.

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Width);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Height);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bIsMpeg2);             /*!< Whether MPEG2 or MPEG1 */

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, aui8IntraQMatrix[64]);             /*!< 8X8 intra quantisation matrix in zigzag scanning order             */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, aui8NonIntraQMatrix[64]);          /*!< 8X8 non-intra quantisation matrix in zigzag scanning order         */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, aui8ChromaIntraQMatrix[64]);       /*!< 8X8 chroma intra quantisation matrix in zigzag scanning order      */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, aui8ChromaNonIntraQMatrix[64]);    /*!< 8X8 chroma non-intra quantisation matrix in zigzag scanning order  */

} MPEG2FW_sSequenceInfo;


/*!
******************************************************************************

 This describes the MPEG2 parser component "Header data", shown in the
 Firmware Memory Layout diagram. This data is required by the MPEG2 firmware
 and should be supplied by the Host.

******************************************************************************/
typedef struct
{
    VDECFW_sImageBuffer         sPrimary;               /*!< Primary decode buffer base addresses */
    VDECFW_sImageBuffer         sAlternate;             //!< buffer base addresses for alternate output

} MPEG2FW_sHeaderData;


/*!
******************************************************************************

 This describes the MPEG2 parser component "Context data", shown in the
 Firmware Memory Layout diagram. This data is the state preserved across
 pictures. It is loaded and saved by the Firmware, but requires the host to
 provide buffer(s) for this.

******************************************************************************/
typedef struct
{
    MPEG2FW_sPicture             sNewRefPic;           /*!< First reference picture (MPEG2 requires up to 2
                                                            reference pictures */
    MPEG2FW_sPicture             sOldRefPic;           /*!< Second reference picture */

    MPEG2FW_sPicture             sLastBField;          /* If last field was of B type we keep it here 
                                                          to be able to pair it with the next B field coming.
                                                          We do this for B fields specificaly because I an P fields
                                                          are kept in the Reference picture structure and if we copy
                                                          them here we risk displaying them or freeing them twice */

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bFirstField);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastLumaRecon);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastChromaRecon);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastChroma2Recon);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastLumaAlter);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastChromaAlter);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastChroma2Alter);

    VDECFW_sImageBuffer          sLastPrimary;
    VDECFW_sImageBuffer          sLastAlternative;

    MPEG2FW_sSequenceInfo        sSequenceInfo;        /*!< Sequence header information. */

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32SeqHdrId);         /*!< Current sequence header ID -- used to detect new sequence header */

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8SliceVertPos);      /*!< Slice vertical position */

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32ActualPicCount);   /*!< Picture order count */

} MPEG2FW_sContextData;


#endif /* _MPEG2FW_DATA_H_ */
