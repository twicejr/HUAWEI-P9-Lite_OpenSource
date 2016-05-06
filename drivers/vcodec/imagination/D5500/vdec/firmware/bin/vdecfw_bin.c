/*!
 *****************************************************************************
 *
 * @File       vdecfw_bin.c
 * @Description    Set of tables (containing firmware in binary form) and offsets
 *  allowing for loading firmware into MTX RAM for execution.
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

#include "dbgopt_api_km.h"
#include "vdecfw_bin.h"
#include "report_api.h"

#ifdef VDEC_USE_PVDEC
#include "firmware.h"
#else
#ifdef HAS_AVS
#ifdef INCLUDE_SINGLE_STANDARD_FW
#include "base_non_oold_single_avs_bin.h"
#include "base_non_oold_single_avs_bin.c"
#endif
#include "parser_non_oold_multi_avs_bin.h"
#include "parser_non_oold_multi_avs_bin.c"
#endif
#ifdef HAS_H264
#ifdef INCLUDE_SINGLE_STANDARD_FW
#include "base_non_oold_single_h264_bin.h"
#include "base_non_oold_single_h264_bin.c"
#endif
#include "parser_non_oold_multi_h264_bin.h"
#include "parser_non_oold_multi_h264_bin.c"
#endif
#ifdef HAS_MPEG4
#ifdef INCLUDE_SINGLE_STANDARD_FW
#include "base_non_oold_single_mpeg4_bin.h"
#include "base_non_oold_single_mpeg4_bin.c"
#endif
#include "parser_non_oold_multi_mpeg4_bin.h"
#include "parser_non_oold_multi_mpeg4_bin.c"
#endif
#ifdef HAS_VP6
#ifdef INCLUDE_SINGLE_STANDARD_FW
#include "base_non_oold_single_vp6_bin.h"
#include "base_non_oold_single_vp6_bin.c"
#endif
#include "parser_non_oold_multi_vp6_bin.h"
#include "parser_non_oold_multi_vp6_bin.c"
#endif
#ifdef HAS_VP8
#ifdef INCLUDE_SINGLE_STANDARD_FW
#include "base_non_oold_single_vp8_bin.h"
#include "base_non_oold_single_vp8_bin.c"
#endif
#include "parser_non_oold_multi_vp8_bin.h"
#include "parser_non_oold_multi_vp8_bin.c"
#endif
#ifdef HAS_JPEG
#ifdef INCLUDE_SINGLE_STANDARD_FW
#include "base_non_oold_single_jpeg_bin.h"
#include "base_non_oold_single_jpeg_bin.c"
#endif
#include "parser_non_oold_multi_jpeg_bin.h"
#include "parser_non_oold_multi_jpeg_bin.c"
#endif
#ifdef HAS_MPEG2
#ifdef INCLUDE_SINGLE_STANDARD_FW
#include "base_non_oold_single_mpeg2_bin.h"
#include "base_non_oold_single_mpeg2_bin.c"
#endif
#include "parser_non_oold_multi_mpeg2_bin.h"
#include "parser_non_oold_multi_mpeg2_bin.c"
#endif
#ifdef HAS_REAL
#ifdef INCLUDE_SINGLE_STANDARD_FW
#include "base_non_oold_single_real_bin.h"
#include "base_non_oold_single_real_bin.c"
#endif
#include "parser_non_oold_multi_real_bin.h"
#include "parser_non_oold_multi_real_bin.c"
#endif
#ifdef HAS_VC1
#ifdef INCLUDE_SINGLE_STANDARD_FW
#include "base_non_oold_single_vc1_bin.h"
#include "base_non_oold_single_vc1_bin.c"
#endif
#include "parser_non_oold_multi_vc1_bin.h"
#include "parser_non_oold_multi_vc1_bin.c"
#endif
#include "base_non_oold_multi_bin.h"
#include "base_non_oold_multi_bin.c"
#endif /* VDEC_USE_PVDEC */

#ifdef VDEC_USE_PVDEC
#include "pvdec_full_bin.c"
#endif /* VDEC_USE_PVDEC */


#define __SET_BASE_FIRMWARE_INFO(info, mode, std) \
    do { \
        info->aui32Text              = aui32MTXBase##mode##std##Text; \
        info->aui32Data              = aui32MTXBase##mode##std##Data; \
        info->ui32TextBufSize        = ui32MTXBase##mode##std##TextSize; \
        info->ui32TextDmaSize        = ui32MTXBase##mode##std##TextSize; \
        info->ui32DataSize           = ui32MTXBase##mode##std##DataSize; \
        info->ui32TextOrigin         = ui32MTXBase##mode##std##TextOrigin; \
        info->ui32DataOrigin         = ui32MTXBase##mode##std##DataOrigin; \
    } while(0)

#define SET_BASE_FIRMWARE_INFO_SINGLE(info, mode, std) \
    __SET_BASE_FIRMWARE_INFO(info, _##mode##_single_, std##_)

#define SET_BASE_FIRMWARE_INFO_MULTI(info, mode) \
    __SET_BASE_FIRMWARE_INFO(info, _##mode##_multi, _)


#ifdef USE_FW_CTX_TRIMMING
#define __SET_MOD_FIRMWARE_CTX_TRIMMING_INFO(info, mode, std) \
    do { \
        info->ui32PsrCtxSize = ui32MTXParser##mode##std##CtxSize; \
    } while(0)
#endif /* USE_FW_CTX_TRIMMING */
#ifdef USE_FW_RELOC_INFO_PACKING
#define __SET_MOD_FIRMWARE_RELOC_PACKING_INFO(info, mode, std) \
    do { \
        info->ui32PackedRelocInfoSize = ui32MTXParser##mode##std##PackedRelocInfoSize; \
    } while(0)
#else /* not USE_FW_RELOC_INFO_PACKING */
#define __SET_MOD_FIRMWARE_RELOC_INFO(info, mode, std) \
    do { \
        info->aui32TextReloc          = aui32MTXParser##mode##std##TextReloc; \
        info->ui32TextRelocSize       = ui32MTXParser##mode##std##TextRelocSize; \
        info->aui8TextRelocType       = aui8MTXParser##mode##std##TextRelocType; \
        info->aui32TextRelocFullAddr  = aui32MTXParser##mode##std##TextRelocFullAddr; \
        info->aui32DataReloc          = aui32MTXParser##mode##std##DataReloc; \
        info->ui32DataRelocSize       = ui32MTXParser##mode##std##DataRelocSize; \
    } while(0)
#endif /* not USE_FW_RELOC_INFO_PACKING */
#define __SET_MOD_FIRMWARE_INFO(info, mode, std) \
    do { \
        info->aui32Text               = aui32MTXParser##mode##std##Text; \
        info->aui32Data               = aui32MTXParser##mode##std##Data; \
        info->ui32TextBufSize         = ui32MTXParser##mode##std##TextSize; \
        info->ui32TextDmaSize         = ui32MTXParser##mode##std##TextSize; \
        info->ui32DataSize            = ui32MTXParser##mode##std##DataSize; \
        info->ui32TextOrigin          = ui32MTXParser##mode##std##TextOrigin; \
        info->ui32DataOrigin          = ui32MTXParser##mode##std##DataOrigin; \
    } while(0)

#if defined(USE_FW_CTX_TRIMMING) && defined(USE_FW_RELOC_INFO_PACKING)
#define SET_MOD_FIRMWARE_INFO(info, mode, std) \
    do { \
        __SET_MOD_FIRMWARE_INFO(info, _##mode##_multi_, std##_); \
        __SET_MOD_FIRMWARE_CTX_TRIMMING_INFO(info, _##mode##_multi_, std##_); \
        __SET_MOD_FIRMWARE_RELOC_PACKING_INFO(info, _##mode##_multi_, std##_); \
    } while(0)
#elif defined(USE_FW_CTX_TRIMMING)
#define SET_MOD_FIRMWARE_INFO(info, mode, std) \
    do { \
        __SET_MOD_FIRMWARE_INFO(info, _##mode##_multi_, std##_); \
        __SET_MOD_FIRMWARE_CTX_TRIMMING_INFO(info, _##mode##_multi_, std##_); \
        __SET_MOD_FIRMWARE_RELOC_INFO(info, _##mode##_multi_, std##_); \
    } while(0)
#elif defined(USE_FW_RELOC_INFO_PACKING)
#define SET_MOD_FIRMWARE_INFO(info, mode, std) \
    do { \
        __SET_MOD_FIRMWARE_INFO(info, _##mode##_multi_, std##_); \
        __SET_MOD_FIRMWARE_RELOC_PACKING_INFO(info, _##mode##_multi_, std##_); \
    } while(0)
#else
#define SET_MOD_FIRMWARE_INFO(info, mode, std) \
    __SET_MOD_FIRMWARE_INFO(info, _##mode##_multi_, std##_); \
    __SET_MOD_FIRMWARE_RELOC_INFO(info, _##mode##_multi_, std##_);
#endif

IMG_RESULT VDECFW_GetBaseFirmware(
    VDECFW_sFirmwareBinInfo *  psFirmwareBinInfo,
    IMG_BOOL                   bSingleStream,
    IMG_BOOL                   bOold,
    VDEC_eVidStd               eVidStd
)
{
    IMG_RESULT ui32Result = IMG_ERROR_NOT_SUPPORTED;

#ifdef VDEC_USE_PVDEC

    const FIRMWARE * psFirmware = IMG_NULL;

    if (bSingleStream)
    {
        REPORT(REPORT_MODULE_HWCTRL, REPORT_CRIT, "Single standard firmware not supported for PVDEC");
        ui32Result = IMG_ERROR_NOT_SUPPORTED;
    }

    psFirmware = &sFwPvdec_full;
    IMG_MEMSET(psFirmwareBinInfo, 0, sizeof(*psFirmwareBinInfo));
    psFirmwareBinInfo->aui32Text = (IMG_UINT32 *)psFirmware->pui8Blob;
    psFirmwareBinInfo->ui32TextBufSize = psFirmware->uiBlobSize/sizeof(IMG_UINT32);
    psFirmwareBinInfo->ui32TextDmaSize = psFirmware->uiCoreSize/sizeof(IMG_UINT32);
    psFirmwareBinInfo->ui32TextOrigin = 0x80900000;

    psFirmwareBinInfo->aui32Data = (IMG_UINT32 *)IMG_NULL;
    psFirmwareBinInfo->ui32DataSize = 0;
    psFirmwareBinInfo->ui32DataOrigin = 0;

    REPORT(REPORT_MODULE_HWCTRL, REPORT_INFO, "Using PVDEC firmware from %s built at %s, core: %d, blob: %d",
           psFirmware->psVersion, psFirmware->psBuildDate, psFirmware->uiCoreSize, psFirmware->uiBlobSize);

    ui32Result = IMG_SUCCESS;

#else /* ndef VDEC_USE_PVDEC */

    if (bSingleStream)
    {
#ifdef INCLUDE_SINGLE_STANDARD_FW
        switch (eVidStd)
        {
#ifdef HAS_AVS
            case VDEC_STD_AVS:
                SET_BASE_FIRMWARE_INFO_SINGLE(psFirmwareBinInfo, non_oold, avs);
                ui32Result = IMG_SUCCESS;
                break;
#endif
#ifdef HAS_H264
            case VDEC_STD_H264:
                SET_BASE_FIRMWARE_INFO_SINGLE(psFirmwareBinInfo, non_oold, h264);
                ui32Result = IMG_SUCCESS;
                break;
#endif
#ifdef HAS_MPEG4
            case VDEC_STD_MPEG4:
            case VDEC_STD_H263:
            case VDEC_STD_SORENSON:
                SET_BASE_FIRMWARE_INFO_SINGLE(psFirmwareBinInfo, non_oold, mpeg4);
                ui32Result = IMG_SUCCESS;
                break;
#endif
#ifdef HAS_VP6
            case VDEC_STD_VP6:
                SET_BASE_FIRMWARE_INFO_SINGLE(psFirmwareBinInfo, non_oold, vp6);
                ui32Result = IMG_SUCCESS;
                break;
#endif
#ifdef HAS_VP8
            case VDEC_STD_VP8:
                SET_BASE_FIRMWARE_INFO_SINGLE(psFirmwareBinInfo, non_oold, vp8);
                ui32Result = IMG_SUCCESS;
                break;
#endif
#ifdef HAS_JPEG
            case VDEC_STD_JPEG:
                SET_BASE_FIRMWARE_INFO_SINGLE(psFirmwareBinInfo, non_oold, jpeg);
                ui32Result = IMG_SUCCESS;
                break;
#endif
#ifdef HAS_MPEG2
            case VDEC_STD_MPEG2:
                SET_BASE_FIRMWARE_INFO_SINGLE(psFirmwareBinInfo, non_oold, mpeg2);
                ui32Result = IMG_SUCCESS;
                break;
#endif
#ifdef HAS_REAL
            case VDEC_STD_REAL:
                SET_BASE_FIRMWARE_INFO_SINGLE(psFirmwareBinInfo, non_oold, real);
                ui32Result = IMG_SUCCESS;
                break;
#endif
#ifdef HAS_VC1
            case VDEC_STD_VC1:
                SET_BASE_FIRMWARE_INFO_SINGLE(psFirmwareBinInfo, non_oold, vc1);
                ui32Result = IMG_SUCCESS;
                break;
#endif
            default:
                break;
        }
#else /* not INCLUDE_SINGLE_STANDARD_FW */
        ui32Result = IMG_ERROR_NOT_SUPPORTED;
#endif /* not INCLUDE_SINGLE_STANDARD_FW */
    }
    else
    {
        SET_BASE_FIRMWARE_INFO_MULTI(psFirmwareBinInfo, non_oold);
        ui32Result = IMG_SUCCESS;
    }

#endif /* ndef VDEC_USE_PVDEC */

    return ui32Result;
}


IMG_RESULT VDECFW_GetStdFirmware(
    VDECFW_sFirmwareBinInfo *  psFirmwareBinInfo,
    VDEC_eVidStd               eStd,
    IMG_BOOL                   bOold)
{
    IMG_RESULT ui32Result = IMG_ERROR_NOT_SUPPORTED;

    switch (eStd)
    {
#ifndef  VDEC_USE_PVDEC
#ifdef HAS_AVS
        case VDEC_STD_AVS:
            SET_MOD_FIRMWARE_INFO(psFirmwareBinInfo, non_oold, avs);
            ui32Result = IMG_SUCCESS;
            break;
#endif
#ifdef HAS_H264
        case VDEC_STD_H264:
            SET_MOD_FIRMWARE_INFO(psFirmwareBinInfo, non_oold, h264);
            ui32Result = IMG_SUCCESS;
            break;
#endif
#ifdef HAS_MPEG4
        case VDEC_STD_MPEG4:
        case VDEC_STD_H263:
        case VDEC_STD_SORENSON:
            SET_MOD_FIRMWARE_INFO(psFirmwareBinInfo, non_oold, mpeg4);
            ui32Result = IMG_SUCCESS;
            break;
#endif
#ifdef HAS_VP6
        case VDEC_STD_VP6:
            SET_MOD_FIRMWARE_INFO(psFirmwareBinInfo, non_oold, vp6);
            ui32Result = IMG_SUCCESS;
            break;
#endif
#ifdef HAS_VP8
        case VDEC_STD_VP8:
            SET_MOD_FIRMWARE_INFO(psFirmwareBinInfo, non_oold, vp8);
            ui32Result = IMG_SUCCESS;
            break;
#endif
#ifdef HAS_JPEG
        case VDEC_STD_JPEG:
            SET_MOD_FIRMWARE_INFO(psFirmwareBinInfo, non_oold, jpeg);
            ui32Result = IMG_SUCCESS;
            break;
#endif
#ifdef HAS_MPEG2
        case VDEC_STD_MPEG2:
            SET_MOD_FIRMWARE_INFO(psFirmwareBinInfo, non_oold, mpeg2);
            ui32Result = IMG_SUCCESS;
            break;
#endif
#ifdef HAS_REAL
        case VDEC_STD_REAL:
            SET_MOD_FIRMWARE_INFO(psFirmwareBinInfo, non_oold, real);
            ui32Result = IMG_SUCCESS;
            break;
#endif
#ifdef HAS_VC1
        case VDEC_STD_VC1:
            SET_MOD_FIRMWARE_INFO(psFirmwareBinInfo, non_oold, vc1);
            ui32Result = IMG_SUCCESS;
            break;
#endif /* HAS_VC1 */
#endif /* VDEC_USE_PVDEC */
#ifdef HAS_HEVC
        case VDEC_STD_HEVC:
            /* HEVC firmware is only available for PVDEC and it's included
             * in PVDEC firmware blob, which contains all modules. No need to
             * return HEVC module info in this function */
            memset(psFirmwareBinInfo, 0, sizeof(*psFirmwareBinInfo));
            ui32Result = IMG_SUCCESS;
            break;
#endif
        default:
            break;
    }

    return ui32Result;
}


/* EOF */
