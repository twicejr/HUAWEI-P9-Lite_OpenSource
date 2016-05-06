/*!
 *****************************************************************************
 *
 * @File       dec_resources.c
 * @Title      VDECDD Decoder Resources Component
 * @Description    This file contains the VDECDD decoder resources component.
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

#include "dec_resources.h"

#include "hwctrl_api.h"
#include "vdecdd_mmu.h"
#include "report_api.h"
#include "pool_api.h"
#include "msvdx_msg.h"

#ifndef SYSBRG_BRIDGING
    #include "talmmu_api.h"
#else
    #include "sysmem_utils.h"
#endif

#include "vdecfw_bin.h"
#include "vdecfw.h"
#ifdef HAS_AVS
#include "avsfw_data.h"
#endif /* HAS_AVS */
#ifdef HAS_H264
#include "h264fw_data.h"
#endif /* HAS_H264 */
#ifdef HAS_MPEG4
#include "mpeg4fw_data.h"
#endif /* HAS_MPEG4 */
#ifdef HAS_VP6
#include "vp6fw_data.h"
#endif /* HAS_VP6 */
#ifdef HAS_VP8
#include "vp8fw_data.h"
#endif /* HAS_VP8 */
#ifdef HAS_MPEG2
#include "mpeg2fw_data.h"
#endif /* HAS_MPEG2 */
#ifdef HAS_REAL
#include "realfw_data.h"
#endif /* HAS_REAL */
#ifdef HAS_VC1
#include "vc1fw_data.h"
#endif /* HAS_VC1 */

#ifdef HAS_H264
extern IMG_UINT16        gaui16h264VlcTableData[544];
extern const IMG_UINT16  gui16h264VlcTableSize;
extern IMG_UINT16        gaui16h264VlcIndexData[38][3];
extern const IMG_UINT8   gui8h264VlcIndexSize;
#endif /* HAS_H264 */

#ifdef HAS_MPEG4
extern IMG_UINT16        gaui16mpeg4VlcTableData[966];
extern const IMG_UINT16  gui16mpeg4VlcTableSize;
extern IMG_UINT16        gaui16mpeg4VlcIndexData[17][3];
extern const IMG_UINT8   gui8mpeg4VlcIndexSize;
#endif /* HAS_MPEG4 */

#ifdef HAS_VP6
extern IMG_UINT16        gaui16vp6VlcTableData[1];
extern const IMG_UINT16  gui16vp6VlcTableSize;
extern IMG_UINT16        gaui16vp6VlcIndexData[38][3];
extern const IMG_UINT8   gui8vp6VlcIndexSize;
#endif /* HAS_VP6 */

#ifdef HAS_VP8
extern IMG_UINT16        gaui16vp8VlcTableData[1];
extern const IMG_UINT16  gui16vp8VlcTableSize;
extern IMG_UINT16        gaui16vp8VlcIndexData[1][3];
extern const IMG_UINT8   gui8vp8VlcIndexSize;
#endif /* HAS_VP8 */

#ifdef HAS_MPEG2
extern IMG_UINT16        gaui16mpeg2VlcTableData[382];
extern const IMG_UINT16  gui16mpeg2VlcTableSize;
extern IMG_UINT16        gaui16mpeg2VlcIndexData[7][3];
extern const IMG_UINT8   gui8mpeg2VlcIndexSize;
#endif /* HAS_MPEG2 */

#ifdef HAS_REAL
IMG_UINT16        gaui16realVlcTableData[1] = { 0 };
const IMG_UINT16  gui16realVlcTableSize = 1;
IMG_UINT16        gaui16realVlcIndexData[1][3] = {{ 0,0,0 }};
const IMG_UINT8   gui8realVlcIndexSize = 1;
#endif /* HAS_REAL */

#ifdef HAS_VC1
extern IMG_UINT16        gaui16vc1VlcTableData[7045];
extern const IMG_UINT16  gui16vc1VlcTableSize;
extern IMG_UINT16        gaui16vc1VlcIndexData[83][3];
extern const IMG_UINT8   gui8vc1VlcIndexSize;
#endif /* HAS_VC1 */

/*
******************************************************************************

 @Function              decres_PackVlcTables

******************************************************************************/
static IMG_VOID
decres_PackVlcTables(
    IMG_UINT16 * paui16Packed,
    IMG_UINT16 * paui16Unpacked,
    IMG_UINT16 ui16Size
)
{
    IMG_UINT16 i, j;

    for (i = 0; i < ui16Size; i++)
    {
        j = i * 3;
        /* opcode 14:12 *//* width 11:9 *//* symbol 8:0 */
        paui16Packed[i] = 0
                          | ((paui16Unpacked[j]) << 12)
                          | ((paui16Unpacked[j + 1]) << 9)
                          | (paui16Unpacked[j + 2]);
    }
}


typedef struct
{
    IMG_VOID      * pvData;
    IMG_UINT32      ui32NumEntries;

    IMG_VOID      * pvIndexTable;
    IMG_UINT32      ui32NumTables;

} DECODER_sVlcTable;


/*****************************************************************************
  Union with sizes of firmware parser header structure sizes. Dec_resources
  uses the largest to allocate the header buffer.
******************************************************************************/
typedef union
{
#ifdef HAS_AVS
    AVSFW_sHeaderData  sAVSHeader;
#endif /* HAS_AVS */
#ifdef HAS_H264
    H264FW_sHeaderData  sH264Header;
#endif /* HAS_H264 */
#ifdef HAS_MPEG4
    MPEG4FW_sHeaderData sMPEG4Header;
#endif /* HAS_MPEG4 */
#ifdef HAS_VP6
    VP6FW_sHeaderData sVP6Header;
#endif /* HAS_VP6 */
#ifdef HAS_VP8
    VP8FW_sHeaderData sVP8Header;
#endif /* HAS_VP8 */
#ifdef HAS_JPEG
    JPEGFW_sHeaderData sJPEGHeader;
#endif /* HAS_JPEG */
#ifdef HAS_MPEG2
    MPEG2FW_sHeaderData sMPEG2Header;
#endif /* HAS_MPEG2 */
#ifdef HAS_REAL
    REALFW_sHeaderData sREALHeader;
#endif /* HAS_REAL */
#ifdef HAS_VC1
    VC1FW_sHeaderData sVC1Header;
#endif /* HAS_VC1 */
} decres_uFwHeaders;


/*!
******************************************************************************
 This array contains the size of each resource allocation.
 @brief  Resource Allocation Sizes

 NOTE: This should be kept in step with #DECODER_eResType.
 ******************************************************************************/
static const IMG_UINT32 aui32ResourceSize[DECODER_RESTYPE_MAX] =
{
    sizeof(VDECFW_sTransaction),
    sizeof(decres_uFwHeaders),
    BATCH_MSG_BUFFER_SIZE,
#ifdef HAS_HEVC
    MEM_TO_REG_BUF_SIZE + SLICE_PARAMS_BUF_SIZE + ABOVE_PARAMS_BUF_SIZE
#endif /* HAS_HEVC */
};


#define DECODER_END_BYTES_SIZE  40

static const IMG_UINT8 aui8StartCode[] =
{
    0x00, 0x00, 0x01, 0x00,
};

static const IMG_UINT8 aui8EndBytes[VDEC_STD_MAX][DECODER_END_BYTES_SIZE] =
{
    /* Undefined. */
    {
        0x00
    },
    /* MPEG2. */
    {
        0x00, 0x00, 0x01, 0xB7,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    },
    /* MPEG4. */
    {
        0x00, 0x00, 0x01, 0xB1,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    },
    /* H263. */
    {
        0x00, 0x00, 0x01, 0xB1,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    },
    /* H.264. */
    {
        0x00, 0x00, 0x00, 0x24,
        0x0B, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x0B,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    },
    /* VC-1. */
    {
        0x00, 0x00, 0x01, 0x0A,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    },
    /* AVS. */
    {
        0x00, 0x00, 0x01, 0xB1,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    },
    /* REAL. */
    {
        0x00
    },
    /* JPEG. */
    {
        0xFF, 0xD9, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    },
    /* VP6. */
    {
        0x00
    },
    /* VP8. */
    {
        //VP8 uses byte count
        //Sending only to consume in the FW
        //and set the VDECFW_PSRFLAGS_END flag
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    },
    /* SORENSON. */
    {
        0x00, 0x00, 0x01, 0xB1,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    },
};



/*!
******************************************************************************

 @Function              decres_GetVlcData

******************************************************************************/
static IMG_RESULT decres_GetVlcData(
    DECODER_sVlcTable  * psVlcTable,
    VDEC_eVidStd         eVidStd
)
{
    switch (eVidStd)
    {
#ifdef HAS_AVS
    case VDEC_STD_AVS:
        psVlcTable->pvData         = IMG_NULL;
        psVlcTable->ui32NumEntries = 0;
        psVlcTable->pvIndexTable   = IMG_NULL;
        psVlcTable->ui32NumTables  = 0;
        break;
#endif /* HAS_AVS */
#ifdef HAS_H264
    case VDEC_STD_H264:
        psVlcTable->pvData         = gaui16h264VlcTableData;
        psVlcTable->ui32NumEntries = gui16h264VlcTableSize;
        psVlcTable->pvIndexTable   = gaui16h264VlcIndexData;
        psVlcTable->ui32NumTables  = gui8h264VlcIndexSize;
        break;
#endif /* HAS_H264 */
#ifdef HAS_MPEG4
    case VDEC_STD_MPEG4:
    case VDEC_STD_H263:
    case VDEC_STD_SORENSON:
        psVlcTable->pvData         = gaui16mpeg4VlcTableData;
        psVlcTable->ui32NumEntries = gui16mpeg4VlcTableSize;
        psVlcTable->pvIndexTable   = gaui16mpeg4VlcIndexData;
        psVlcTable->ui32NumTables  = gui8mpeg4VlcIndexSize;
        break;
#endif /* HAS_MPEG4 */
#ifdef HAS_VP6
    case VDEC_STD_VP6:
        psVlcTable->pvData         = gaui16vp6VlcTableData;
        psVlcTable->ui32NumEntries = gui16vp6VlcTableSize;
        psVlcTable->pvIndexTable   = gaui16vp6VlcIndexData;
        psVlcTable->ui32NumTables  = gui8vp6VlcIndexSize;
        break;
#endif /* HAS_VP6 */
#ifdef HAS_VP8
    case VDEC_STD_VP8:
        //VP8 does not need VLC tables, review
        psVlcTable->pvData         = gaui16vp8VlcTableData;
        psVlcTable->ui32NumEntries = gui16vp8VlcTableSize;
        psVlcTable->pvIndexTable   = gaui16vp8VlcIndexData;
        psVlcTable->ui32NumTables  = gui8vp8VlcIndexSize;
        break;
#endif /* HAS_VP8 */
#ifdef HAS_JPEG
    case VDEC_STD_JPEG:
        psVlcTable->pvData         = IMG_NULL;
        psVlcTable->ui32NumEntries = 0;
        psVlcTable->pvIndexTable   = IMG_NULL;
        psVlcTable->ui32NumTables  = 0;
        break;
#endif /* HAS_JPEG */
#ifdef HAS_MPEG2
    case VDEC_STD_MPEG2:
        psVlcTable->pvData         = gaui16mpeg2VlcTableData;
        psVlcTable->ui32NumEntries = gui16mpeg2VlcTableSize;
        psVlcTable->pvIndexTable   = gaui16mpeg2VlcIndexData;
        psVlcTable->ui32NumTables  = gui8mpeg2VlcIndexSize;
        break;
#endif /* HAS_MPEG2 */
#ifdef HAS_REAL
    case VDEC_STD_REAL:
        psVlcTable->pvData         = gaui16realVlcTableData;
        psVlcTable->ui32NumEntries = gui16realVlcTableSize;
        psVlcTable->pvIndexTable   = gaui16realVlcIndexData;
        psVlcTable->ui32NumTables  = gui8realVlcIndexSize;
        break;
#endif /* HAS_REAL */
#ifdef HAS_VC1
    case VDEC_STD_VC1:
        psVlcTable->pvData         = gaui16vc1VlcTableData;
        psVlcTable->ui32NumEntries = gui16vc1VlcTableSize;
        psVlcTable->pvIndexTable   = gaui16vc1VlcIndexData;
        psVlcTable->ui32NumTables  = gui8vc1VlcIndexSize;
        break;
#endif /* HAS_VC1 */
    default:
        VDEC_BZERO(psVlcTable);
        break;
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              decoder_fnBufInfoDestructor

******************************************************************************/
static IMG_VOID dec_resources_fnBufInfoDestructor (
    IMG_VOID *  pvParam
)
{
    VXDIO_sDdBufInfo *  psDdBufInfo = pvParam;
    IMG_RESULT      ui32Result;

    IMG_ASSERT(psDdBufInfo != IMG_NULL);

    ui32Result = MMU_FreeMem(psDdBufInfo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);

    IMG_FREE(psDdBufInfo);
    psDdBufInfo = IMG_NULL;
}



/*!
******************************************************************************

 @Function              RESOURCE_PictureDetach

******************************************************************************/
IMG_RESULT RESOURCE_PictureDetach(
    IMG_HANDLE                * phsResCtx,
    DECODER_sDecPict          * psDecPict
)
{
    DECODER_sResCtx * psResCtx = (DECODER_sResCtx *) *phsResCtx;

    // return transaction buffer.
    LST_add(&psResCtx->asPoolDataList[DECODER_RESTYPE_TRANSACTION], psDecPict->psTransactionInfo);
    POOL_ResFree(psDecPict->psTransactionInfo->hResource);

    // return picture header information buffer.
    LST_add(&psResCtx->asPoolDataList[DECODER_RESTYPE_HDR], psDecPict->psHdrInfo);
    POOL_ResFree(psDecPict->psHdrInfo->hResource);

    //return batch message buffer.
    LST_add(&psResCtx->asPoolDataList[DECODER_RESTYPE_BATCH_MSG], psDecPict->psBatchMsgInfo);
    POOL_ResFree(psDecPict->psBatchMsgInfo->hResource);

    // return HEVC buffer
#ifdef HAS_HEVC
    if (psDecPict->psHevcInfo)
    {
        LST_add(&psResCtx->asPoolDataList[DECODER_RESTYPE_HEVC_BUF], psDecPict->psHevcInfo);
        POOL_ResFree(psDecPict->psHevcInfo->hResource);
    }
#endif /* HAS_HEVC */

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              decres_GetResource

******************************************************************************/
static IMG_RESULT
decres_GetResource(
    DECODER_sResCtx * psResCtx,
    DECODER_eResType eResType,
    RES_sResInfo     ** ppsResInfo
    )
{
    RES_sResInfo * psResInfo = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_SUCCESS;

    psResInfo = LST_removeHead(&psResCtx->asPoolDataList[eResType]);
    IMG_ASSERT(psResInfo);
    if (psResInfo)
    {
        IMG_ASSERT(psResInfo->psDdBufInfo);
        if (psResInfo->psDdBufInfo)
        {
            ui32Result = POOL_ResAlloc(psResCtx->ahResPool[eResType], psResInfo->hResource);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                ui32Result = IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE;
                goto error;
            }

            IMG_MEMSET(psResInfo->psDdBufInfo->pvCpuVirt, 0, psResInfo->psDdBufInfo->ui32BufSize);
            *ppsResInfo = psResInfo;
        }
        else
        {
            ui32Result = IMG_ERROR_FATAL;
            goto error;
        }
    }
    else
    {
        ui32Result = IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE;
        goto error;
    }

error:
    return ui32Result;
}



/*!
******************************************************************************

 @Function              RESOURCE_PictureAttach

******************************************************************************/
IMG_RESULT RESOURCE_PictureAttach(
    IMG_HANDLE                * phsResCtx,
    VDEC_eVidStd                eVidStd,
    DECODER_sDecPict          * psDecPict
)
{
    DECODER_sResCtx * psResCtx = (DECODER_sResCtx *) *phsResCtx;
    IMG_RESULT ui32Result;

    // Obtain transaction buffer.
    ui32Result = decres_GetResource(psResCtx,
        DECODER_RESTYPE_TRANSACTION,
        &psDecPict->psTransactionInfo);

    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    // Obtain picture header information buffer.
    ui32Result = decres_GetResource(psResCtx,
        DECODER_RESTYPE_HDR,
        &psDecPict->psHdrInfo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

#ifdef HAS_HEVC
    // Obtain HEVC buffer
    if (eVidStd == VDEC_STD_HEVC)
    {
        ui32Result = decres_GetResource(psResCtx,
                                        DECODER_RESTYPE_HEVC_BUF,
                                        &psDecPict->psHevcInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }
#endif /* HAS_HEVC */

    // Obtain picture batch message buffer.
    ui32Result = decres_GetResource(psResCtx,
        DECODER_RESTYPE_BATCH_MSG,
        &psDecPict->psBatchMsgInfo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    psDecPict->psIntraBufInfo = &psResCtx->sIntraBufInfo;
    psDecPict->psAuxLineBufInfo = &psResCtx->sAuxLineBufInfo;
    psDecPict->psEndBytesBufInfo = &psResCtx->asEndBytesBufInfo[eVidStd];
    psDecPict->psVlcTablesBufInfo = &psResCtx->asVlcTablesBufInfo[eVidStd];
    psDecPict->psVlcIdxTableBufInfo = &psResCtx->asVlcIdxTableBufInfo[eVidStd];
    psDecPict->psStartCodeBufInfo = &psResCtx->sStartCodeBufInfo;

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              RESOURCE_Create

******************************************************************************/
IMG_RESULT RESOURCE_Create(
    IMG_HANDLE                  hMmuDevHandle,
    VXD_sCoreProps            * psCoreProps,
    HWCTRL_sRendec            * psMsvdxRendecProps,
    IMG_UINT32                  ui32NumDecodeSlots,
    VXDIO_sMemPool              sSecurePool,
    VXDIO_sMemPool              sInsecurePool,
    VXDIO_sDdBufInfo            asRendecBufInfo[],
    IMG_HANDLE                * phResources
)
{
    DECODER_sResCtx   * psResCtx;
    IMG_RESULT          ui32Result;
    IMG_UINT32          ui32I = 0;
    DECODER_sVlcTable   sVlcTable;

    VDEC_MALLOC(psResCtx);
    IMG_ASSERT(psResCtx);
    if (psResCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "Failed to allocate memory for resource context");
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psResCtx);

    /* Allocate Intra buffer. */
    ui32Result = MMU_DeviceMalloc(hMmuDevHandle,
                                  MMU_HEAP_DEVICE_BUFFERS,
                                  sSecurePool,          //Secure if Secure allocation is possible
                                  psCoreProps->ui32NumPixelPipes *
#ifdef HAS_H264
                                  INTRA_BUF_SIZE * 3,   // separate colour planes
#else
                                  INTRA_BUF_SIZE,
#endif
                                  DEV_MMU_PAGE_ALIGNMENT,
                                  &psResCtx->sIntraBufInfo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    if (psCoreProps->bAuxLineBufSupported)
    {
        /* Allocate aux line buffer. */
        ui32Result = MMU_DeviceMalloc(hMmuDevHandle,
                                  MMU_HEAP_DEVICE_BUFFERS,
                                  sSecurePool,          //Secure if Secure allocation is possible
                                  AUX_LINE_BUFFER_SIZE * 3 * psCoreProps->ui32NumPixelPipes, // separate colour planes
                                  DEV_MMU_PAGE_ALIGNMENT,
                                  &psResCtx->sAuxLineBufInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }
    }

    if (psMsvdxRendecProps->aui32BufferSize[0] != 0 &&
        psMsvdxRendecProps->aui32BufferSize[1] != 0)
    {
        /* Allocate RenDec buffer 0. */
        ui32Result = MMU_DeviceMalloc(hMmuDevHandle,
                                      MMU_HEAP_DEVICE_BUFFERS,
                                      sSecurePool,             //Secure if Secure allocation is possible
                                      psMsvdxRendecProps->aui32BufferSize[0],
                                      DEV_MMU_PAGE_ALIGNMENT,
                                      &psResCtx->asRendecBufInfo[0]);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        /* Allocate RenDec buffer 1. */
        ui32Result = MMU_DeviceMalloc(hMmuDevHandle,
                                      MMU_HEAP_DEVICE_BUFFERS,
                                      sSecurePool,                 //Secure if Secure allocation is possible
                                      psMsvdxRendecProps->aui32BufferSize[1],
                                      DEV_MMU_PAGE_ALIGNMENT,
                                      &psResCtx->asRendecBufInfo[1]);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        asRendecBufInfo[0] = psResCtx->asRendecBufInfo[0];
        asRendecBufInfo[1] = psResCtx->asRendecBufInfo[1];
    }

    /* Allocate standard-specific buffers. */
    for (ui32I = VDEC_STD_UNDEFINED + 1; ui32I < VDEC_STD_MAX; ui32I++)
    {
        //IMG_UINT64  ui64Address;
        // End-bytes.
        ui32Result = MMU_DeviceMalloc(hMmuDevHandle,
                                      MMU_HEAP_DEVICE_BUFFERS,
                                      sInsecurePool, //End-bytes are always in insecure memory
                                      sizeof(aui8EndBytes[ui32I]),
                                      DEV_MMU_PAGE_ALIGNMENT,
                                      &psResCtx->asEndBytesBufInfo[ui32I]);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }
        // Add flushing to the flushing buffer
        IMG_MEMCPY(psResCtx->asEndBytesBufInfo[ui32I].pvCpuVirt,
                   aui8EndBytes[ui32I],
                   sizeof(aui8EndBytes[ui32I]));

        UPDATE_DEVICE((&psResCtx->asEndBytesBufInfo[ui32I]), IMG_TRUE);

        // VLC tables
        ui32Result = decres_GetVlcData(&sVlcTable, ui32I);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        if (sVlcTable.ui32NumTables > 0)
        {
            /* Size of VLC IDX table in bytes. Has to be aligned to 4, so transfer to MTX succeeds.
             * (VLC IDX is copied to local RAM of MTX)*/
            IMG_UINT32 ui32VlcIdxTableSize =  VDEC_ALIGN_SIZE((sizeof(IMG_UINT16) * sVlcTable.ui32NumTables * 3), 4);

            ui32Result = MMU_DeviceMalloc(hMmuDevHandle,
                                          MMU_HEAP_DEVICE_BUFFERS,
                                          sInsecurePool, //VLC Tables are always in insecure memory
                                          sizeof(IMG_UINT16) * sVlcTable.ui32NumEntries,
                                          DEV_MMU_PAGE_ALIGNMENT,
                                          &psResCtx->asVlcTablesBufInfo[ui32I]);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error;
            }

            if (sVlcTable.pvData != IMG_NULL)
            {
                decres_PackVlcTables(psResCtx->asVlcTablesBufInfo[ui32I].pvCpuVirt,
                        sVlcTable.pvData,
                        sVlcTable.ui32NumEntries);

                UPDATE_DEVICE((&psResCtx->asVlcTablesBufInfo[ui32I]), IMG_TRUE);
            }

            // VLC index table
            ui32Result = MMU_DeviceMalloc(hMmuDevHandle,
                                          MMU_HEAP_DEVICE_BUFFERS,
                                          sInsecurePool, //VLC Index Tables are always in insecure memory
                                          ui32VlcIdxTableSize,
                                          DEV_MMU_PAGE_ALIGNMENT,
                                         &psResCtx->asVlcIdxTableBufInfo[ui32I]);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error;
            }

            if (sVlcTable.pvIndexTable != IMG_NULL)
            {
                IMG_MEMCPY(psResCtx->asVlcIdxTableBufInfo[ui32I].pvCpuVirt,
                           sVlcTable.pvIndexTable,
                           psResCtx->asVlcIdxTableBufInfo[ui32I].ui32BufSize);
                UPDATE_DEVICE((&psResCtx->asVlcIdxTableBufInfo[ui32I]), IMG_TRUE);
            }
        }
    }

    // Start code.
    ui32Result = MMU_DeviceMalloc(hMmuDevHandle,
                                  MMU_HEAP_DEVICE_BUFFERS,
                                  sInsecurePool, //Additional StartCodes are always in insecure memory
                                  sizeof(aui8StartCode),
                                  DEV_MMU_PAGE_ALIGNMENT,
                                  &psResCtx->sStartCodeBufInfo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }
    IMG_MEMCPY(psResCtx->sStartCodeBufInfo.pvCpuVirt,
               aui8StartCode,
               sizeof(aui8StartCode));

    UPDATE_DEVICE((&psResCtx->sStartCodeBufInfo), IMG_TRUE);

    for (ui32I = 0; ui32I < DECODER_RESTYPE_MAX; ui32I++)
    {
        IMG_UINT32 ui32J;

        ui32Result = POOL_PoolCreate(&psResCtx->ahResPool[ui32I]);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        LST_init(&psResCtx->asPoolDataList[ui32I]);

        for (ui32J = 0; ui32J < ui32NumDecodeSlots; ui32J++)
        {
            RES_sResInfo * psResInfo;

            VDEC_MALLOC(psResInfo);
            IMG_ASSERT(psResInfo);
            if (psResInfo == IMG_NULL)
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                    "Failed to allocate memory for resource");
                ui32Result = IMG_ERROR_OUT_OF_MEMORY;
                goto error_local_res_info_alloc;
            }

            VDEC_MALLOC(psResInfo->psDdBufInfo);
            IMG_ASSERT(psResInfo->psDdBufInfo);
            if (psResInfo->psDdBufInfo == IMG_NULL)
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                    "Failed to allocate memory for resource buffer information structure");
                ui32Result = IMG_ERROR_OUT_OF_MEMORY;
                goto error_local_dd_buf_alloc;
            }

            ui32Result = MMU_DeviceMalloc(hMmuDevHandle,
                                          MMU_HEAP_DEVICE_BUFFERS,
                                          sInsecurePool,    //Transaction, FW Headers and Batch Messages are always in insecure memory
                                          aui32ResourceSize[ui32I],
                                          DEV_MMU_PAGE_ALIGNMENT,
                                          psResInfo->psDdBufInfo);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error_local_res_alloc;
            }

            /* Register with the buffer pool */
            ui32Result = POOL_ResRegister(psResCtx->ahResPool[ui32I],
                dec_resources_fnBufInfoDestructor,
                psResInfo->psDdBufInfo,
                sizeof(*psResInfo->psDdBufInfo),
                IMG_FALSE,
                IMG_NULL,
                &psResInfo->hResource);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error_local_res_register;
            }

            LST_add(&psResCtx->asPoolDataList[ui32I], psResInfo);
            continue;

            /* Roll back in case of local errors. */
error_local_res_register:
            MMU_FreeMem(psResInfo->psDdBufInfo);
error_local_res_alloc:
            IMG_FREE(psResInfo->psDdBufInfo);
error_local_dd_buf_alloc:
            IMG_FREE(psResInfo);
error_local_res_info_alloc:
            goto error;
        }
    }

    *phResources = (IMG_HANDLE)psResCtx;

    return IMG_SUCCESS;

    /* Roll back in case of errors. */
error:
    RESOURCES_Destroy((IMG_HANDLE)psResCtx);

    return ui32Result;
}


/*!
******************************************************************************

 @Function              RESOURCES_Destroy

******************************************************************************/
IMG_RESULT RESOURCES_Destroy(
    IMG_HANDLE  hsResCtx
)
{
    IMG_RESULT      ui32Result = IMG_SUCCESS;
    IMG_RESULT      ui32AuxResult = IMG_SUCCESS;
    IMG_UINT32      ui32I = 0;
    RES_sResInfo  * psResInfo;
    RES_sResInfo  * psNextResInfo;

    DECODER_sResCtx  * psResCtx = (DECODER_sResCtx *) hsResCtx;

    if (IMG_NULL == psResCtx)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    if (psResCtx->sIntraBufInfo.hMemory)
    {
        ui32AuxResult = MMU_FreeMem(&psResCtx->sIntraBufInfo);
        IMG_ASSERT(ui32AuxResult == IMG_SUCCESS);
        if (ui32AuxResult != IMG_SUCCESS)
        {
            ui32Result = ui32AuxResult;
        }
    }

    if (psResCtx->sAuxLineBufInfo.hMemory)
    {
        ui32AuxResult = MMU_FreeMem(&psResCtx->sAuxLineBufInfo);
        IMG_ASSERT(ui32AuxResult == IMG_SUCCESS);
        if (ui32AuxResult != IMG_SUCCESS)
        {
            ui32Result = ui32AuxResult;
        }
    }

    for (ui32I = 0; ui32I < 2; ui32I++)
    {
        if (psResCtx->asRendecBufInfo[ui32I].hMemory)
        {
            ui32AuxResult = MMU_FreeMem(&psResCtx->asRendecBufInfo[ui32I]);
            IMG_ASSERT(ui32AuxResult == IMG_SUCCESS);
            if (ui32AuxResult != IMG_SUCCESS)
            {
                ui32Result = ui32AuxResult;
            }
        }
    }

    for (ui32I = 0; ui32I < VDEC_STD_MAX; ui32I++)
    {
        if (psResCtx->asEndBytesBufInfo[ui32I].hMemory)
        {
            ui32AuxResult = MMU_FreeMem(&psResCtx->asEndBytesBufInfo[ui32I]);
            IMG_ASSERT(ui32AuxResult == IMG_SUCCESS);
            if (ui32AuxResult != IMG_SUCCESS)
            {
                ui32Result = ui32AuxResult;
            }
        }

        if (psResCtx->asVlcTablesBufInfo[ui32I].hMemory)
        {
            ui32AuxResult = MMU_FreeMem(&psResCtx->asVlcTablesBufInfo[ui32I]);
            IMG_ASSERT(ui32AuxResult == IMG_SUCCESS);
            if (ui32AuxResult != IMG_SUCCESS)
            {
                ui32Result = ui32AuxResult;
            }
        }

        if (psResCtx->asVlcIdxTableBufInfo[ui32I].hMemory)
        {
            ui32AuxResult = MMU_FreeMem(&psResCtx->asVlcIdxTableBufInfo[ui32I]);
            IMG_ASSERT(ui32AuxResult == IMG_SUCCESS);
            if (ui32AuxResult != IMG_SUCCESS)
            {
                ui32Result = ui32AuxResult;
            }
        }
    }

    if (psResCtx->sStartCodeBufInfo.hMemory)
    {
        ui32AuxResult = MMU_FreeMem(&psResCtx->sStartCodeBufInfo);
        IMG_ASSERT(ui32AuxResult == IMG_SUCCESS);
        if (ui32AuxResult != IMG_SUCCESS)
        {
            ui32Result = ui32AuxResult;
        }
    }

    for (ui32I = 0; ui32I < DECODER_RESTYPE_MAX; ui32I++)
    {
        if (psResCtx->ahResPool[ui32I])
        {
            psResInfo = LST_first(&psResCtx->asPoolDataList[ui32I]);
            while (psResInfo)
            {
                psNextResInfo = LST_next(psResInfo);
                LST_remove(&psResCtx->asPoolDataList[ui32I], psResInfo);
                ui32AuxResult = POOL_ResDestroy(psResInfo->hResource, IMG_TRUE);
                IMG_ASSERT(ui32AuxResult == IMG_SUCCESS);
                if (ui32AuxResult != IMG_SUCCESS)
                {
                    ui32Result = ui32AuxResult;
                }
                IMG_FREE(psResInfo);
                psResInfo = psNextResInfo;
            }
            POOL_PoolDestroy(psResCtx->ahResPool[ui32I]);
        }
    }

    IMG_FREE(psResCtx);

    return ui32Result;
}
