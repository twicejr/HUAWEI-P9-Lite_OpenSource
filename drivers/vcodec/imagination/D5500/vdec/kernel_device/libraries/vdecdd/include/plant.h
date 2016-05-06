/*!
 *****************************************************************************
 *
 * @File       plant.h
 * @Title      VDECDD Plant Component
 * @Description    This file contains the structure and function prototypes
 *  for the VDEC DD plant component.
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

#ifndef __VDECDD_PLANT_H__
#define __VDECDD_PLANT_H__

#include <img_defs.h>
#include <vdecdd.h>
#include <vdecdd_int.h>

#ifdef __cplusplus
extern "C" {
#endif


/*!
******************************************************************************
 This enumeration describes the plant callback types.
 @brief  Plant Callback Types
******************************************************************************/
typedef enum
{
    PLANT_CB_PICTURE_RESOURCE_ADD = VDECDD_CBGRP_PLANT,     /*!< New picture resource bundle (pvData: VDECDD_sPictResInt *)
                                                              allocated in response to #PLANT_StreamResourceCreate.       */
    PLANT_CB_PICTURE_RESOURCE_REMOVE,                       /*!< Picture resource should no longer be referenced.         */
    PLANT_CB_MAX,

} PLANT_eCBType;


/*!
******************************************************************************

 @Function              PLANT_Initialise

 @Description

 This function prepares the global state of the plant. There is a single
 instance of the plant within the device driver. A single callback is
 registered for the plant since it may not refer to a stream or core see
 #PLANT_eCBType. pvStrParam: pvStrUserData supplied by user in
 PLANT_StreamCreate() and pvCoreParam: IMG_NULL.

 Usage: during driver initialisation in vdeckm_fnDevInit().

 @Input    pvInitUserData : Pointer to component-wide user data.

 @Input    pfnCallback    : Pointer to component callback function.

 @Input    sDdDevInfo     : Device information.

 @Input    ui32NumCores   : Number of cores on device.

 @Input    ui32NumPipes   : Number of pixel pipes on core.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
PLANT_Initialise(
    IMG_VOID *              pvInitUserData,
    VDECDD_pfnCompCallback  pfnCallback,
    VDECDD_sDdDevConfig     sDdDevConfig,
    IMG_UINT32              ui32NumCores,
    IMG_UINT32              ui32NumPipes
);


/*!
******************************************************************************

 @Function              PLANT_Deinitialise

 @Description

 This function shuts-down the plant.

 Usage: during driver deinitialisation in vdeckm_fnDevDeinit().

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
PLANT_Deinitialise(
    IMG_VOID
);


/*!
******************************************************************************

 @Function              PLANT_StreamCreate

 @Description

 This function creates a plant stream context. All stream-specific configuration
 should be provided here in #VDEC_sStrConfigData.

 @Input    psStrConfig   : Pointer to VDEC stream configuration.

 @Input    hMmuStrHandle : VDECDD MMU stream context handle.

 @Input    pvStrUserData : Pointer to stream-specific user data.

 @Output   phPltStrCtx   : Pointer to plant stream context handle

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
PLANT_StreamCreate(
    VDEC_sStrConfigData *  psStrConfig,
    IMG_HANDLE             hMmuStrHandle,
    IMG_VOID *             pvStrUserData,
    IMG_HANDLE *           phPltStrCtx
);


/*!
******************************************************************************

 @Function              PLANT_StreamDestroy

 @Description

 This function destroys a plant stream context.

 @Input    hPltStrCtx : Plant stream context handle.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
PLANT_StreamDestroy(
    IMG_HANDLE  hPltStrCtx
);


/*!
******************************************************************************

 @Function              PLANT_StreamResourceCreate

 @Description

 This function is used to allocate internal picture-based resources associated with
 a stream. Resources will be pushed-out through callback #PLANT_CB_PICTURE_RESOURCE_ADD,
 one for each picture. All resources previously allocated by the plant (for this stream)
 will be re-used if they are suitable for the requirements.

 @Input     hPltStrCtx              : Plant stream context handle.

 @Input     bClosedGOP              : Resources should be created for a closed GOP where
                                      references are no longer used.

 @Input     eMemPool                : Memory pool to use.

 @Input     psComSeqHdrInfo         : Pointer to standard agnostic sequence header
                                      information.

 @Input     psOutputConfig          : Pointer to output configuration information.

 @Input     psDispPictBuf           : Pointer to display picture buffer.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT PLANT_StreamResourceCreate(
    IMG_HANDLE                    hPltStrCtx,
    IMG_BOOL                      bClosedGOP,
    VXDIO_sMemPool                sMemPool,
    const VDEC_sComSequHdrInfo  * psComSeqHdrInfo,
    const VDEC_sStrOutputConfig * psOutputConfig,
    const VDECDD_sDdPictBuf     * psDispPictBuf
);


/*!
******************************************************************************

 @Function              PLANT_StreamResourceDestroy

 @Description

 This function is used to destroy all picture resources allocated by the plant
 and associated with the stream.

 @Input    hPltStrCtx : Plant stream context handle.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
PLANT_StreamResourceDestroy(
    IMG_HANDLE  hPltStrCtx
);


/*!
******************************************************************************

 @Function              PLANT_IsStreamResourceSuitable

 @Description

 This function is used to check whether current picture resources are
 suitable for the specified sequence header and output configuration.

 @Input    hPltStrCtx               : Plant stream context handle.

 @Input    psComSeqHdrInfo          : Pointer to standard agnostic sequence header
                                      information.

 @Input    psOutputConfig           : Pointer to output configuration information.

 @Input     psDispPictBuf           : Pointer to display picture buffer.

 @Return   IMG_BOOL : See function description.

******************************************************************************/
extern IMG_BOOL 
PLANT_IsStreamResourceSuitable(
    IMG_HANDLE                      hPltStrCtx,
    const VDEC_sComSequHdrInfo    * psComSeqHdrInfo,
    const VDEC_sStrOutputConfig   * psOutputConfig,
    const VDECDD_sDdPictBuf       * psDispPictBuf
);



#if defined(__cplusplus)
}
#endif

#endif /* __VDECDD_PLANT_H__    */
