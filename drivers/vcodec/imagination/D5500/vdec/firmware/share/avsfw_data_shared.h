/*!
 *****************************************************************************
 *
 * @File       avsfw_data_shared.h
 * @Title      Public data structures for the avs parser firmware module
 * @Description    Public data structures for the avs parser firmware module
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

#ifndef _AVSFW_DATA_H_
#define _AVSFW_DATA_H_

#include "vdecfw_share.h"

#include "img_types.h"
#include "vdecfw.h"

/*!
******************************************************************************

 This describes an AVS picture coding type.

******************************************************************************/
typedef enum
{
    AVSFW_CODING_TYPE_I = 0,
    AVSFW_CODING_TYPE_P,
    AVSFW_CODING_TYPE_B,
    AVSFW_CODING_TYPE_MAX

} AVSFW_eCodingType;

/*!
******************************************************************************

 This describes the AVS picture FIFO, required for setting picture distance
 references.

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, AVSFW_eCodingType, ePicCodingType);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8PictureDistance);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bPictureStructure);

} AVSFW_sRefPicFIFOEntry;


/*!
******************************************************************************

 This describes an AVS picture. It is part of the Context data

******************************************************************************/
typedef struct
{
    VDECFW_sImageBuffer sPrimary;                   /*!< Primary decode buffer base addresses */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, AVSFW_eCodingType, ePicCodingType);             /*!< Picture coding type (I, P, B) */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TransId);           /*!< Unique ID for this frame or first field of this picture */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8DisplayFlags);            /*!< Flags for this picture for the display process */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bSentForDisplay);            /*!< Whether picture was already added to display list in picture manager*/
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32MbParamsBaseAddress);    /*!< Macroblock parameters base address for the picture */

} AVSFW_sPicture;

/*!
******************************************************************************

 This describes the AVS parser component "Header data", shown in the
 Firmware Memory Layout diagram. This data is required by the AVS firmware
 and should be supplied by the Host.

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8ProfileId);               /*!< AVS profile information.                              */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8LevelId);                 /*!< AVS level information.                                */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bProgressiveSequence);       /*!< if set, sequence does not contain interlaced frames.  */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8ChromaFormat);            /*!< chroma format (4:2:0 or 4:2:2).                       */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8SamplePrecision);         /*!< precision of luma and chroma samples.                 */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8AspectRatio);             /*!< Aspect ratio code                                     */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bLowDelay);                  /*!< if set, sequence does not contain B-pictures.         */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32BbvBufferSize);          /*!< BBV buffer size                                       */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, ui16HorizontalSize);         /*!< Horizontal size                                       */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, ui16VerticalSize);           /*!< Vertical size                                         */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32BitRate);                /*!< Stream bit rate                                       */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32MbParamsBaseAddress);    /*!< Macroblock parameters base address for the picture    */
    VDECFW_sImageBuffer sPrimary;                   /*!< Primary decode buffer base addresses                  */
    VDECFW_sImageBuffer sAlternate;                 /*!< buffer base addresses for alternate output            */

} AVSFW_sHeaderData;


#define REF_PIC_FIFO_SIZE 8
/*!
******************************************************************************

 This describes the AVS parser component "Context data", shown in the
 Firmware Memory Layout diagram. This data is the state preserved across
 pictures. It is loaded and saved by the Firmware, but requires the host to
 provide buffer(s) for this.

******************************************************************************/
typedef struct
{
    AVSFW_sRefPicFIFOEntry  asRefPicFIFO[REF_PIC_FIFO_SIZE];   /*!< AVS reference picture FIFO                                       */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32CurrPicID);                     /*!< Current picture ID                                               */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PrevPicID);                     /*!< Previous picture ID                                              */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastLumaRecon);                 /*!< Last Luma picture base address                                   */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastChromaRecon);               /*!< Last Chroma picture base address                                 */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastLumaAlter);                 /*!< Last Luma picture alternative address                            */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastChromaAlter);               /*!< Last Chroma picture alternative address                          */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32LastMbParamsBaseAddress);       /*!< Last Macroblock parameters base address for the picture          */
    VDECFW_sImageBuffer     sLastPrimary;                      /*!< Last primary decode buffer base addresses                        */
    VDECFW_sImageBuffer     sLastAlternative;                  /*!< Last alternative decode buffer base addresses                    */
    AVSFW_sPicture          sNewRefPic;                        /*!< First reference picture (AVS requires up to 2 reference pictures */
    AVSFW_sPicture          sOldRefPic;                        /*!< Second reference picture                                         */

} AVSFW_sContextData;

#endif /* _AVSFW_DATA_H_ */
