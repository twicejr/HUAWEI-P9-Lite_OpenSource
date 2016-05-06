/*!
 *****************************************************************************
 *
 * @File       dec_resources.h
 * @Title      VDECDD Decoder Resources Component
 * @Description    This file contains the structure and function prototypes
 *  for the VDECDD decoder resources component.
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

#ifndef _DEC_RESOURCES_H_
#define _DEC_RESOURCES_H_

#include "img_defs.h"
#include "vxd_buf.h"
#include "vxd.h"
#include "hwctrl_int.h"
#include "decoder_int.h"

/*!
******************************************************************************
 This structure contains the core resources.
 @brief  Decoder Core Resources
******************************************************************************/
typedef struct
{
    VXDIO_sDdBufInfo       sIntraBufInfo;                             /*!< Intra buffer info.           */
    VXDIO_sDdBufInfo       sAuxLineBufInfo;                           /*!< Auxiliary line buffer info.  */
    VXDIO_sDdBufInfo       asRendecBufInfo[VDEC_NUM_RENDEC_BUFFERS];  /*!< Rendec buffer info.          */
    VXDIO_sDdBufInfo       sStartCodeBufInfo;                         /*!< Start code buffer info.      */
    VXDIO_sDdBufInfo       asEndBytesBufInfo[VDEC_STD_MAX];           /*!< End Bytes buffer info.       */
    VXDIO_sDdBufInfo       asVlcTablesBufInfo[VDEC_STD_MAX];          /*!< VLC tables buffer info.      */
    VXDIO_sDdBufInfo       asVlcIdxTableBufInfo[VDEC_STD_MAX];        /*!< VLC index table buffer info. */
    IMG_HANDLE             ahResPool[DECODER_RESTYPE_MAX];            /*!< Resource pool handles.       */
    LST_T                  asPoolDataList[DECODER_RESTYPE_MAX];       /*!< Resource pool data.          */

} DECODER_sResCtx;



/*!
******************************************************************************

 @Function              DECRES_ReturnResource

******************************************************************************/
extern IMG_RESULT RESOURCE_PictureDetach(
    IMG_HANDLE                * phsResCtx,
    DECODER_sDecPict          * psDecPict
);


/*!
******************************************************************************

 @Function              DECRES_GetResource

******************************************************************************/
extern IMG_RESULT RESOURCE_PictureAttach(
    IMG_HANDLE                * phsResCtx,
    VDEC_eVidStd                eVidStd,
    DECODER_sDecPict          * psDecPict
);


/*!
******************************************************************************

 @Function              RESOURCE_Create

 @Description

 This function creates device resources.

 @Input     hMmuDevHandle        : The MMU device handle.

 @Input     psCoreProps          : Pointer to core properties.

 @Input     psMsvdxIoRendecProps : Pointer to rendec properties.

 @Input     ui32NumDecodeSlots   : Number of decode slots on core.

 @Input     eSecurePool          : Secure memory pool

 @Input     eInsecurePool        : Insecure memory pool

 @Output    asRendecBufInfo      : Array of rendec buffer information.

 @Output    phResources          : Pointer to resources handle.

 @Return	IMG_RESULT : This function returns either IMG_SUCCESS or an
						 error code.

******************************************************************************/
extern IMG_RESULT 
RESOURCE_Create(
    IMG_HANDLE                      hMmuDevHandle,
    VXD_sCoreProps                * psCoreProps,
    HWCTRL_sRendec                * psMsvdxIoRendecProps,
    IMG_UINT32                      ui32NumDecodeSlots,
    VXDIO_sMemPool                  sSecurePool,
    VXDIO_sMemPool                  sInsecurePool,
    VXDIO_sDdBufInfo                asRendecBufInfo[],
    IMG_HANDLE                    * phResources
);


/*!
******************************************************************************

 @Function              RESOURCES_Destroy

 @Description

 This function removes device resources. 

 @Input		psDecRes        : Pointer to decoder resources.

 @Return	IMG_RESULT : This function returns either IMG_SUCCESS or an
						 error code.

******************************************************************************/
extern IMG_RESULT RESOURCES_Destroy(
    IMG_HANDLE                hsResCtx
);




#endif /* _DEC_RESOURCES_H_ */
