/*!
 *****************************************************************************
 *
 * @File       vxd_int.h
 * @Description    Common low level VXD core interface component
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

#if !defined (__VXD_INT_H__)
#define __VXD_INT_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "img_defs.h"
#include "vdecdd_int.h"
#include "vxd.h"
#include "scaler_setup.h"


#define INTRA_BUF_SIZE                  (1024 * 32)
#define AUX_LINE_BUFFER_SIZE            (512 * 1024)

#define MAX_PICTURE_WIDTH               (4096)
#define MAX_PICTURE_HEIGHT              (4096)
#define MAX_MB_WIDTH                    (VDEC_ALIGN_SIZE(MAX_PICTURE_WIDTH, VDEC_MB_DIMENSION) / VDEC_MB_DIMENSION)
#define MAX_MB_HEIGHT                   (VDEC_ALIGN_SIZE(MAX_PICTURE_HEIGHT,VDEC_MB_DIMENSION) / VDEC_MB_DIMENSION)
#define MAX_MB_SIZE                     ((MAX_MB_WIDTH+4)*MAX_MB_HEIGHT)

#ifdef HAS_H264
#define H264_FE_BUFFER_SIZE             (0)
#define H264_BE_BUFFER_SIZE             (0)
#else
#define H264_FE_BUFFER_SIZE             (0)
#define H264_BE_BUFFER_SIZE             (0)
#endif /* HAS_H264 */

#ifdef HAS_MPEG4
#define MPEG4_FE_BUFFER_SIZE            (0)
#define MPEG4_BE_BUFFER_SIZE            (0)
#else
#define MPEG4_FE_BUFFER_SIZE            (0)
#define MPEG4_BE_BUFFER_SIZE            (0)
#endif /* HAS_MPEG4 */

#ifdef HAS_AVS
#define AVS_FE_BUFFER_SIZE              (0)
#define AVS_BE_BUFFER_SIZE              (0)
#else
#define AVS_FE_BUFFER_SIZE              (0)
#define AVS_BE_BUFFER_SIZE              (0)
#endif /* HAS_AVS */

#ifdef HAS_VP8
//Define the buffer size for the max image size possible
#define MB_FLAGS_BUFFER_SIZE            (VDEC_MB_DIMENSION*1024)
#define FIRST_PARTITION_BUFFER_SIZE     (MAX_MB_SIZE*64)
#define CURRENT_PICTURE_BUFFER_SIZE     (MAX_MB_SIZE*64)
#define SEGMENTID_BUFFER_SIZE           (MAX_MB_SIZE/4)

#define MB_FLAGS_BUFFER_OFFSET          (0)
#define FIRST_PARTITION_BUFFER_OFFSET   (((MB_FLAGS_BUFFER_OFFSET+MB_FLAGS_BUFFER_SIZE) + 3) & 0xFFFFFFFC)
#define CURRENT_PICTURE_BUFFER_OFFSET   (((FIRST_PARTITION_BUFFER_OFFSET+FIRST_PARTITION_BUFFER_SIZE) + 3) & 0xFFFFFFFC)
#define SEGMENTID_BUFFER_OFFSET         (((CURRENT_PICTURE_BUFFER_OFFSET+CURRENT_PICTURE_BUFFER_SIZE) + 3) & 0xFFFFFFFC)

#define VP8_FE_BUFFER_SIZE              (0)
#define VP8_BE_BUFFER_SIZE              (((SEGMENTID_BUFFER_OFFSET+SEGMENTID_BUFFER_SIZE) + 3) & 0xFFFFFFFC)
#else
#define VP8_FE_BUFFER_SIZE              (0)
#define VP8_BE_BUFFER_SIZE              (0)
#endif /* HAS_VP8 */

#ifdef HAS_VP6
//Define the buffer size for the max image size possible
#define VP6_PIC_BUFFER_SIZE             (MAX_MB_SIZE*64)
#define VP6_PIC_BUFFER_OFFSET           (0)

#define VP6_FE_BUFFER_SIZE              (0)
#define VP6_BE_BUFFER_SIZE              (((VP6_PIC_BUFFER_SIZE) + 3) & 0xFFFFFFFC)
#else
#define VP6_FE_BUFFER_SIZE              (0)
#define VP6_BE_BUFFER_SIZE              (0)
#endif /* HAS_VP6 */

#ifdef HAS_VC1
#define VC1_MSB_BUFFER_SIZE             (MAX_MB_SIZE/4)
#define VC1_MSB_BUFFER_OFFSET           (0)
#define VC1_BE_BUFFER_SIZE              (((VC1_MSB_BUFFER_SIZE) + 3) & 0xFFFFFFFC)

#define VC1_BITPLANE_BUFFER_SIZE        (((MAX_MB_WIDTH+16)* MAX_MB_HEIGHT))
#define VC1_BITPLANE0_BUFFER_OFFSET     (0)
#define VC1_BITPLANE1_BUFFER_OFFSET     (((VC1_BITPLANE0_BUFFER_OFFSET+VC1_BITPLANE_BUFFER_SIZE) + 3) & 0xFFFFFFFC)
#define VC1_BITPLANE2_BUFFER_OFFSET     (((VC1_BITPLANE1_BUFFER_OFFSET+VC1_BITPLANE_BUFFER_SIZE) + 3) & 0xFFFFFFFC)
#define VC1_FE_BUFFER_SIZE              (((VC1_BITPLANE2_BUFFER_OFFSET+VC1_BITPLANE_BUFFER_SIZE) + 3) & 0xFFFFFFFC)
#else
#define VC1_FE_BUFFER_SIZE              (0)
#define VC1_BE_BUFFER_SIZE              (0)
#endif /* HAS_VC1 */


/*!
******************************************************************************
 This macro returns the host address of device buffer.
******************************************************************************/
#define GET_HOST_ADDR(buf, device)                                     \
(                                                                      \
    (device) ? ((buf)->ui32DevVirt) : (IMG_UINTPTR)((buf)->pvCpuVirt)  \
)

#define GET_HOST_ADDR_OFFSET(buf, device, offset)                      \
(                                                                      \
    (device) ?                                                         \
        (((buf)->ui32DevVirt)+(offset)) :                              \
        (((IMG_UINTPTR)((buf)->pvCpuVirt))+(offset))                   \
)

#ifdef SYSBRG_BRIDGING
// Ensure memory is synchronised between host cpu and device
#define UPDATE_DEVICE(buf, device) SYSMEMU_UpdateMemory(((buf)->hMemoryAlloc), CPU_TO_DEV)
#define UPDATE_HOST(buf, device)   SYSMEMU_UpdateMemory(((buf)->hMemoryAlloc), DEV_TO_CPU)
#else
#include "talmmu_api.h"
// Update the device/host memory.
#define UPDATE_DEVICE(buf, device) { if ((device)) { TALMMU_CopyHostToDevMem(((buf)->hMemory)); } }
#define UPDATE_HOST(buf, device)   { if ((device)) { TALMMU_CopyDevMemToHost(((buf)->hMemory)); } }
#endif


typedef struct
{
    VDECDD_sDdPictBuf  * psReconPict;
    VDECDD_sDdPictBuf  * psAltPict;

    VXDIO_sDdBufInfo   * psIntraBufInfo;
    VXDIO_sDdBufInfo   * psAuxLineBufInfo;

    IMG_UINT32           ui32IntraBufPipeOffset;
    IMG_UINT32           ui32AuxLineBufPipeOffset;

    VXDIO_sDdBufInfo   * psMSBBufInfo;

    IMG_BOOL             bTwoPass;

} VXD_sBuffers;


/*!
******************************************************************************

 @Function              VXD_SetAltPictCmds

 @Description

 This has all that it needs to translate a Stream Unit for a picture
 into a transaction.

 @Input  psStrUnit       : Pointer to stream unit.

 @Input  psStrConfigData : Pointer to stream configuration.

 @Input  psOutputConfig  : Pointer to output configuration.

 @Input  psCoreProps     : Pointer to decoder core properties.

 @Input  psDecPict       : Pointer to decoder picture.

 @Return IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
VXD_SetAltPictCmds(
    const VDECDD_sStrUnit        * psStrUnit,
    const VDEC_sStrConfigData    * psStrConfigData,
    const VDEC_sStrOutputConfig  * psOutputConfig,
    const VXD_sCoreProps         * psCoreProps,
    const VXD_sBuffers           * psBuffers,
    IMG_UINT32                   * pui32PictCmds
);


/*!
******************************************************************************

 @Function              VXD_SetReconPictCmds

 @Description

 This has all that it needs to translate a Stream Unit for a picture into a transaction.

 @Input  psStrUnit       : Pointer to stream unit.

 @Input  psStrConfigData : Pointer to stream configuration.

 @Input  psOutputConfig  : Pointer to output configuration.

 @Input  psCoreProps     : Pointer to decoder core properties.

 @Input  psDecPict       : Pointer to decoder picture.

 @Return IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
VXD_SetReconPictCmds(
    const VDECDD_sStrUnit        * psStrUnit,
    const VDEC_sStrConfigData    * psStrConfigData,
    const VDEC_sStrOutputConfig  * psOutputConfig,
    const VXD_sCoreProps         * psCoreProps,
    const VXD_sBuffers           * psBuffers,
    IMG_UINT32                   * pui32PictCmds
);


/*
******************************************************************************

 @Function              VXD_GetScalerCoeffCmds

******************************************************************************/
extern IMG_RESULT
VXD_GetScalerCoeffCmds(
    const SCALER_sCoeffs  * psScalerCoeffs,
    IMG_UINT32            * pui32PictCmds
);


/*
******************************************************************************

 @Function              VXD_GetScalerCmds

******************************************************************************/
extern IMG_RESULT
VXD_GetScalerCmds(
    const SCALER_sConfig    * psScalerConfig,
    const SCALER_sPitch     * psPitch,
    const SCALER_sFilter    * psFilter,
    const PIXEL_sPixelInfo  * psOutLoopPixelInfo,
    SCALER_sParams          * psParams,
    IMG_UINT32              * pui32PictCmds
);


/*!
******************************************************************************

 @Function              VXD_GetCodedPicSize

 This creates value of MSVDX_CMDS_CODED_PICTURE_SIZE register.

 @Input  ui16WidthMin1  : Width minus 1.

 @Input  ui16HeightMin1 : Height minus 1.

 @return IMG_UINT32     : Value of register.

******************************************************************************/
extern IMG_UINT32
VXD_GetCodedPicSize(
    IMG_UINT16  ui16WidthMin1,
    IMG_UINT16  ui16HeightMin1
);

#if defined(__cplusplus)
}
#endif

#endif /* __VXD_INT_H__ */



