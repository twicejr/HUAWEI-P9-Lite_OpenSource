/*!
 *****************************************************************************
 *
 * @File       decoder.c
 * @Title      VDECDD Decoder Component
 * @Description    This file contains the VDECDD decoder component.
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

#include "decoder.h"

#include "msvdx_ext.h"
#include "decoder_int.h"
#include "vxd.h"
#include "hwctrl_api.h"
#include "idgen_api.h"
#include "dbgopt_api_km.h"
#include "pool_api.h"
#include "vdecdd_mmu.h"
#include "resource.h"
#include "translation_api.h"
#include "dec_resources.h"
#include "dman_api_km.h"

#ifndef SYSBRG_BRIDGING
    #include "talmmu_api.h"
#else
    #include "sysmem_utils.h"
#endif

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
#ifdef HAS_VC1
#include "vc1fw_data.h"
#endif /* HAS_VC1 */
#ifdef HAS_JPEG
#include "jpegfw_data.h"
#endif /* HAS_JPEG */
#ifdef HAS_MPEG2
#include "mpeg2fw_data.h"
#endif /* HAS_MPEG2 */
#ifdef HAS_REAL
#include "realfw_data.h"
#endif /* HAS_REAL */
#ifdef HAS_HEVC
#include "hevcfw_data.h"
#endif /* HAS_HEVC */

#include "pixel_api.h"

#include "sysos_api_km.h"

#include "lst.h"
#include "dq.h"

#include "xpltags.h"

#include "report_api.h"
#include "vdecfw_bin.h"

#ifdef FW_PERFORMANCE_LOGGING
#include "perflog_api.h"
#endif

#if defined(CONFIG_X86)
#include <asm/cacheflush.h>
#endif

/*! Default number of slots (pictures) in each core per pipe. */
#define CORE_NUM_DECODE_SLOTS 2

/*! Default device watch timer period (in ms). */
#define CORE_DEFAULT_DWR_PERIOD 100         // Around 3 frames period @30FPS. This is good enough for production driver. Needs to be increase for c-sim using debug options.

/*! Default retry count of device watch timer for JPEG */
#define CORE_DEFAULT_DWR_JPEG_RETRY 5       // JPEGs can take longer to decode and there's no way to determine if HW is locked up.

/*! Default core FE HW timeout. */
#define CORE_DEFAULT_FE_TIMEOUT 120000      // 300x 400clock avg mb time.

/*! Default core BE HW timeout. */
#define CORE_DEFAULT_BE_TIMEOUT 0x3FFFC0 //0x7FFF80    // Maximum value.

/*! Default core PSR HW timeout. */
#define CORE_DEFAULT_PSR_TIMEOUT 0x3FFFF //0x7FFF80    // Maximum value.

/*! Maximum number of unique picture ids within stream. */
#define DECODER_MAX_PICT_ID             GET_STREAM_PICTURE_ID(((1ULL << 32) - 1ULL))

/*! Maximum number of concurrent pictures within stream. */
#define DECODER_MAX_CONCURRENT_PICT     0x100

#define GET_NEXT_PICTURE_ID(current_picture_id) \
    ((current_picture_id == FWIF_BIT_MASK(FWIF_NUMBITS_STREAM_PICTURE_ID)) ? 1 : current_picture_id + 1)

#define GET_PREV_PICTURE_ID(current_picture_id) \
    ((current_picture_id == 1) ? FWIF_BIT_MASK(FWIF_NUMBITS_STREAM_PICTURE_ID) : current_picture_id - 1)

#define decoder_IsFakeMTX(ctx, core_num)    ((ctx->psDevConfig->bFakeMtx) ? IMG_TRUE : IMG_FALSE)

#ifdef HAS_H264
#define H264_SGM_BUFFER_BYTES_PER_MB  1
#define H264_SGM_MAX_MBS              3600
#endif /* HAS_H264 */
#ifdef HAS_MPEG4
#define MPEG4_FE_VRL_NOT_CODED  1088
#endif /* HAS_MPEG4 */
#ifdef HAS_VC1
#define VC1_MAX_HEIGHT_MBS  (256)   //4096/16 (MAX_WIDTH/MB_SIZE)
#define VC1_MAX_WIDTH_MBS   (256)   //4096/16 (MAX_WIDTH/MB_SIZE)
#endif /* HAS_VC1 */

#ifdef VDEC_USE_PVDEC
#define CONTEXT_BUFF_SIZE   (72)
#endif /* VDEC_USE_PVDEC */

#if ((MAX_CONCURRENT_STREAMS) > FWIF_BIT_MASK(FWIF_NUMBITS_STREAM_ID))
#error Maximum number of concurrent streams (MAX_CONCURRENT_STREAMS) should be less than or equal to FWIF_BIT_MASK(FWIF_NUMBITS_STREAM_ID)
#endif


/*!
******************************************************************************
 This macro reports a Decoder warning once only.
******************************************************************************/
#define IMG_WARN_ONCE(...)                                              \
{                                                                       \
    static IMG_BOOL bDone = IMG_FALSE;                                  \
    if (!bDone)                                                         \
    {                                                                   \
        REPORT(REPORT_MODULE_DECODER, REPORT_WARNING, __VA_ARGS__);     \
        bDone = IMG_TRUE;                                               \
    }                                                                   \
}


/*!
******************************************************************************
 This union contains firmware contexts. Used to allocate buffers for firmware
 context.
 @brief  Decoder Context
******************************************************************************/
typedef union
{
#ifdef HAS_AVS
    AVSFW_sContextData   sAVSContext;
#endif /* HAS_AVS */
#ifdef HAS_H264
    H264FW_sContextData   sH264Context;
#endif /* HAS_H264 */
#ifdef HAS_MPEG4
    MPEG4FW_sContextData  sMPEG4Context;
#endif /* HAS_MPEG4 */
#ifdef HAS_VP6
    VP6FW_sContextData  sVP6Context;
#endif /* HAS_VP6 */
#ifdef HAS_VP8
    VP8FW_sContextData  sVP8Context;
#endif /* HAS_VP8 */
#ifdef HAS_JPEG
    JPEGFW_sContextData  sJPEGContext;
#endif /* HAS_JPEG */
#ifdef HAS_REAL
    REALFW_sContextData  sREALContext;
#endif /* HAS_REAL */
#ifdef HAS_VC1
    VC1FW_sContextData   sVC1Context;
#endif
#ifdef HAS_MPEG2
    MPEG2FW_sContextData sMPEG2Context;
#endif /* HAS_MPEG2 */
#ifdef HAS_HEVC
    HEVCFW_sContextData  sHEVCContext;
#endif /* HAS_HEVC */
} DECODER_uFwContexts;

/*!
******************************************************************************
 This structure contains the Decoder Context.
 @brief  Decoder Context
******************************************************************************/
typedef struct
{
    // Configuration
    IMG_BOOL                    bInitialised;                       /*!< Indicates whether component is initialised.                */
    VDECDD_pfnCompCallback      pfnCompCallback;                    /*!< Callback from component to return output.                  */
    IMG_VOID *                  pvCompInitUserData;                 /*!< Callback user data from component.                         */

    const VDECDD_sDdDevConfig * psDevConfig;                        /*!< Device configuration.                                      */
    IMG_UINT32                  ui32NumCores;                       /*!< Number of cores on device.                                 */
    IMG_UINT32                  ui32NumPipes;                       /*!< Number of pipes per core.                                 */
    LST_T                       sCoreList;                          /*!< List of core context structures.                           */
    LST_T                       sStreamList;                        /*!< List of stream context structures.                         */

    // Handles
    IMG_HANDLE                  hMmuDevHandle;                      /*!< VDECDDMMU Device context.                                  */
    IMG_HANDLE                  hStrIdGen;                          /*!< Stream-based ID generator handle for use with firmware.    */
    IMG_HANDLE                  hDevHandle;                         /*!< Device handle.                                             */

    VXDIO_sDdBufInfo            sPtdBufInfo;                        /*!< Buffer to hold device Page Table directory address.        */
    VXDIO_sPtdInfo              sPtdInfo;                           /*!< Base address of PTD related informations.                   */

    IMG_BOOL                    abSupportedStandards[VDEC_STD_MAX]; /*!< Defines if particular standard is supported.               */
    MSVDXIO_sFw                 sFw;

    SYS_eMemPool                eSecurePool;
    SYS_eMemPool                eInsecurePool;

    // Concurrent streams
    IMG_UINT32                  ui32StrCnt;

} DECODER_sContext;



/*!
******************************************************************************
 This structure contains the stream context.
 @brief  Decoder Stream Context
******************************************************************************/
typedef struct
{
    LST_LINK;                                           /*!< List link (allows the structure to be part of a MeOS list).    */

    // Configuration.
    IMG_UINT32              ui32StrId;                  /*!< Stream Id used with firmware.                                  */
    IMG_UINT8               ui8Pipe;                    /*!< Pipe which stream will be decoded on, may change during playback */
    VDEC_sStrConfigData     sConfig;                    /*!< Global configuration.                                          */
    DECODER_sContext *      psDecCtx;                   /*!< Pointer to Decoder context.                                    */
    IMG_VOID *              pvUserData;                 /*!< Callback user data from component.                             */
    IMG_VOID *              pvUserIntData;              /*!< User data associated with interrupt handling.                  */

    // Handles
    IMG_HANDLE              hMmuStrHandle;              /*!< VDECDDMMU stream context.                                        */
    IMG_HANDLE              hPictIdGen;                 /*!< Picture-based ID generator handle for use with firmware.       */

    // Lists: in-flight data/resources
    LST_T                   sPendStrUnitList;           /*!< List of pictures that are pending decode complete (in-flight).                         */
    DQ_T                    sStrDecdPictList;           /*!< Doubly linked-list of decoded pictures, held by the firmware.                          */

    // Resources
    IMG_UINT32              ui32NumRefRes;              /*!< Maximum number of active pictures in stream.                                           */
    LST_T                   sRefResList;                /*!< List of buffer control structures.                                                     */
    IMG_UINT32              ui32NumDecRes;              /*!< Maximum number of simultaneously decoding pictures.                                    */
    LST_T                   sDecResList;                /*!< List of decode resources allocated per core/stream.                                    */

    // State (decoding)
    VDECDD_sDecStrStatus    sDecStrStatus;              /*!< Stream status.                                                                         */

#ifdef VDEC_USE_PVDEC
    VXDIO_sDdBufInfo        sPtdBufInfo;                /*!< Information for buffer which contains stream PTD phys address.                         */
    VXDIO_sDdBufInfo        sPvdecFwCtxBuf;             /*!< Additional PVDEC FW context buffer.                                                    */
#endif /* VDEC_USE_PVDEC */

    IMG_UINT32              ui32LastFeTransactionId;    /*!< Transaction ID of last picture on stream.                                              */
    IMG_UINT32              ui32NextDecPictId;          /*!< Serial number (incrementing) of next decoded picture (order) which needs processing .  */

    IMG_UINT32              ui32NextPictIdExpected;     /*!< Serial number of the next picture expected to come up (from fw) as decoded */

    DECODER_sPictDecRes *   psCurFePictDecRes;          /*!< Pointer to device resource of current front-end picture.                                */
    DECODER_sPictDecRes *   psPrevFePictDecRes;         /*!< Pointer to device resource of previous front-end picture.                               */
    DECODER_sPictDecRes *   psLastBePictDecRes;         /*!< Pointer to device resource of newest decoded back-end picture
                                                             (in decode order).                                                                      */

    DECODER_sDecPict *      psCurrentPicture;           /*!< Pointer to current front-end picture being processed.                                   */

} DECODER_sStrContext;

#ifndef IMG_KERNEL_MODULE
/*!
******************************************************************************
 This structure contains the resources that was used by the last picture sent
 for decode. It is used for pdumping. It enables the driver to add an extra lock
 between two pictures when they share a resource.
******************************************************************************/
typedef struct
{
    IMG_BOOL        bInit;
    IMG_HANDLE      hTransactionInfo;
    IMG_HANDLE      hHdrInfo;
    IMG_HANDLE      hReconPict;
    IMG_HANDLE      hAltPict;
    IMG_HANDLE      hBatchMsgInfo;
    IMG_HANDLE      hPictHdrInfo;
    IMG_HANDLE      hPictRefRes;
    IMG_HANDLE      hCurPictDecRes;
    IMG_HANDLE      hPrevPictDecRes;

} DECODER_sLastResSubmitted;

#endif
/*!
******************************************************************************
 This structure contains the core context.
 @brief  Decoder Core Context
******************************************************************************/
typedef struct
{
    LST_LINK;                                           /*!< List link (allows the structure to be part of a MeOS list).    */

    DECODER_sContext          * psDecCtx;                   /*!< Pointer to Decoder context.                                    */

    IMG_BOOL                    bEnumerated;                /*!< Indicates whether the core has been enumerated.              */
    IMG_BOOL                    bMaster;                    /*!< Core is master (controls clocks).                            */
    IMG_BOOL                    bConfigured;                /*!< Core is configured.                                          */
    IMG_UINT32                  ui32CoreNum;                /*!< Core identifier.                                             */

    IMG_UINT32                  ui32CoreFeatures;           /*!< Core feature flags - see #VDECDD_eCoreFeatureFlags.          */
    IMG_UINT32                  aui32PipeFeatures[VDEC_MAX_PIXEL_PIPES];  /*!< Core feature flags - see #VDECDD_eCoreFeatureFlags.          */
    VXD_sCoreProps              sCoreProps;

    IMG_HANDLE                  hResources;                 /*!< Core resources.                                              */
    IMG_HANDLE                  hHwCtx;                     /*!< Hardware control context.                                    */

    IMG_UINT32                  ui32CumulativePics;         /*!<                                                              */

    IMG_BOOL                    bAPM;                       /*!< Indicates whether Active Power Management is enabled
                                                               for the device. This turns off power to the core when
                                                               there is nothing to decode.                                    */
    IMG_BOOL                    bBusy;                      /*!< Core busy flag, TRUE when end bytes are expected             */

#ifndef IMG_KERNEL_MODULE
    DECODER_sLastResSubmitted   sLasRes;
#endif

} DECODER_sCoreContext;


/*!
******************************************************************************
 This structure defines the decode picture reference.
 @brief  Decoder Picture Reference
******************************************************************************/
typedef struct
{
    LST_LINK;                                   /*!< List link (allows the structure to be part of a MeOS list).    */

    // These are only required to remove pictures from
    // core when stream is destroyed
    DECODER_sDecPict        * psDecPict;        /*!< Pointer to decoding picture                                    */
    DECODER_sCoreContext    * psDecCoreCtx;     /*!< Pointer to core where stream unit is decoded.                  */

    VDECDD_sStrUnit         * psStrUnit;        /*!< Pointer to stream unit.                                        */

} DECODER_sDecStrUnit;


/*!
******************************************************************************
 This structure defines the decoded picture.
 @brief  Decoded Picture
******************************************************************************/
typedef struct
{
    DQ_LINK;                /*!< Context is DQ listable. Pictures can be decoded on multiple cores thus may arrive out of order.    */

    IMG_UINT32              ui32TransactionId;

    IMG_BOOL                bProcessed;         /*!< Flag to indicate whether decoded picture has been processed.                   */
    IMG_BOOL                bProcessFailed;     /*!< Defaul: IMG_FALSE, set to IMG_TRUE if we failed to complete the processing     */
    IMG_BOOL                bForceDisplay;      /*!< Force displaying the picture due to processing errors.                         */
    IMG_UINT32              ui32DisplayIdx;     /*!< Index within buffer control of next display picture.                           */
    IMG_UINT32              ui32ReleaseIdx;     /*!< Index within buffer control of next release picture.                           */

    VDECDD_sPicture       * psPicture;          /*!< Pointer to decoded picture.                                                    */
    DECODER_sFwMessage    * psFirstFieldFwMsg;  /*!< Pointer to firmware decoded information.                                       */
    DECODER_sFwMessage    * psSecondFieldFwMsg; /*!< Pointer to firmware decoded information.                                       */
    DECODER_sPictRefRes   * psPictRefRes;       /*!< Pointer to stream resource used for picture.                                   */

} DECODER_sDecodedPict;


/*!
******************************************************************************
 This array defines the names for each decode level.
 NOTE: these should be kept in sync with values in #VDECDD_eDecodeLevel.
******************************************************************************/
IMG_CHAR * apszDecodeLevels[] =
{
    "scheduler [parse only]",
    "decoder [fake hw]",
    "firmware",
    "front-end hardware",

    "all",
};


#ifdef FW_PERFORMANCE_LOGGING
static IMG_RESULT
decoder_WritePerfData(
    IMG_UINT8   uiUSID,
    IMG_UINT8   uiGroupID,
    IMG_UINT8   uiTagType,
    IMG_UINT16  uiTagSubject,
    IMG_UINT32  uiData
)
{
    IMG_UINT64 uiPerfDataElement = 0;

    IMG_ASSERT( uiTagType <= 0xf );
    IMG_ASSERT( uiTagSubject <= 0xfff );

    uiPerfDataElement |= ( (IMG_UINT64)uiUSID << 56 ); // bits 63-56: Context ID
    uiPerfDataElement |= ( (IMG_UINT64)uiGroupID << 48 ); // bits 55-48: Message ID
    uiPerfDataElement |= ( (IMG_UINT64)(uiTagType & 0xf) << 44 ); // bits 47-44: Tag Type
    uiPerfDataElement |= ( (IMG_UINT64)(uiTagSubject & 0xfff) << 32 ); // bits 43-32: Tag Subject
    uiPerfDataElement |= uiData; // bits 31-0: Data

    PERFLOG_WritePerfMsg(uiPerfDataElement);

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              decoder_SavePerfDataField

******************************************************************************/
static IMG_RESULT decoder_SavePerfDataField(
    IMG_UINT32 ui32StrId,
    IMG_UINT32 ui32PictureID,
    VDECFW_sPerformanceData * psPerformanceData
)
{
    IMG_RESULT ui32Result = IMG_ERROR_GENERIC_FAILURE;

    if(IMG_NULL != psPerformanceData)
    {
        // Timing point 1-2
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_BEGIN, FE_SETUP_1_2, psPerformanceData->ui32PictureStarted);
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_END, FE_SETUP_1_2, psPerformanceData->ui32FirmwareReady);

        // Timing point 2-5
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_BEGIN, PARSE_HEADER_SETUP_REG_2_5, psPerformanceData->ui32FirmwareReady);
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_END, PARSE_HEADER_SETUP_REG_2_5, psPerformanceData->ui32EntdecStarted);

        // Timing point 5-3
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_BEGIN, PICMAN_4_5, psPerformanceData->ui32EntdecStarted);
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_END, PICMAN_4_5, psPerformanceData->ui32PicmanComplete);

        // Timing point 3-4
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_BEGIN, FW_SAVED_3_4, psPerformanceData->ui32PicmanComplete);
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_END, FW_SAVED_3_4, psPerformanceData->ui32FirmwareSaved);

        // FE DECODE 1ST Slice: Timing point 5-6
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_BEGIN, FE_1STSLICE_5_6, psPerformanceData->ui32EntdecStarted);
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_END, FE_1STSLICE_5_6, psPerformanceData->ui32Fe1sliceDone);

        // FE DECODE: Timing point 2-7
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_BEGIN, FE_DECODE_2_7, psPerformanceData->ui32FirmwareReady);
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_END, FE_DECODE_2_7, psPerformanceData->ui32FePictureComplete);

        // BE DECODE 1ST Slice: Timing point 8-9
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_BEGIN, BE_1STSLICE_8_9, psPerformanceData->ui32BePictureStarted);
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_END, BE_1STSLICE_8_9, psPerformanceData->ui32Be1sliceDone);

        // BE DECODE: Timing point 8-10
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_BEGIN, BE_DECODE_8_10, psPerformanceData->ui32BePictureStarted);
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_END, BE_DECODE_8_10, psPerformanceData->ui32BePictureComplete);

        // Cumulative Time SLICE_HEADER
        decoder_WritePerfData(ui32StrId, ui32PictureID, DATA_ITEM, PARSE_SLICE_HEADER, psPerformanceData->ui32TotParseSliceHeader);

        // Cumulative Time SETUP_REGISTERS
        decoder_WritePerfData(ui32StrId, ui32PictureID, DATA_ITEM, SETUP_REGISTERS, psPerformanceData->ui32TotSetupRegisters);

        // Cumulative Time 2-5
        decoder_WritePerfData(ui32StrId, ui32PictureID, DATA_ITEM, PARSE_AND_SETUP_REG, psPerformanceData->ui32TotParseAndSetupReg);

        // SYNC TIME: Time SYNC_START-SYNCH_COMPLETE
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_BEGIN, SYNC_TIME, psPerformanceData->ui32SyncStart);
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_END, SYNC_TIME, psPerformanceData->ui32SyncComplete);

        // MTX LOAD: 1-2 + 4-5 + Cumulative Time 2-5
        decoder_WritePerfData(ui32StrId, ui32PictureID, DATA_ITEM, MTX_LOAD,
            (psPerformanceData->ui32FirmwareReady-psPerformanceData->ui32PictureStarted)+
            (psPerformanceData->ui32FirmwareSaved-psPerformanceData->ui32EntdecStarted)+
            psPerformanceData->ui32TotParseAndSetupReg);

        // 1st Slice Load Parser Context and serialize
        decoder_WritePerfData(ui32StrId, ui32PictureID, DATA_ITEM, PARSER_LOAD, psPerformanceData->ui32TotParserLoad);

        // 1st Slice DMA and setup VLC tables
        decoder_WritePerfData(ui32StrId, ui32PictureID, DATA_ITEM, TOTAL_SETUP_VLC, psPerformanceData->ui32TotVLC);

        // HW FE DECODE: Cumulative Time 5-6
        decoder_WritePerfData(ui32StrId, ui32PictureID, DATA_ITEM, TOTAL_HW_FE_SUM_5_6, psPerformanceData->ui32TotHwFEDecode);

        // HW BE DECODE: Cumulative Time 8-9
        decoder_WritePerfData(ui32StrId, ui32PictureID, DATA_ITEM, TOTAL_HW_FE_SUM_8_9, psPerformanceData->ui32TotHwBEDecode);

        // Total Time 1-10
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_BEGIN, TOTAL_1_10, psPerformanceData->ui32PictureStarted);
        decoder_WritePerfData(ui32StrId, ui32PictureID, RANGE_END, TOTAL_1_10, psPerformanceData->ui32BePictureComplete);

        ui32Result = IMG_SUCCESS;
    }

    return ui32Result;
}

/*!
******************************************************************************

 @Function              decoder_SavePerfData

******************************************************************************/
static IMG_RESULT decoder_SavePerfData(
    DECODER_sDecStrUnit * psDecStrUnit
)
{
    //DECODER_sContext *      psDecCtx = ((DECODER_sStrContext *)psDecStrUnit->psDecPict->psDecStrCtx)->psDecCtx;
    DECODER_sStrContext *   psStrCtx = (DECODER_sStrContext *)psDecStrUnit->psDecPict->psDecStrCtx;
    DECODER_sDecPict *      psDecPict= psDecStrUnit->psDecPict;
    DECODER_sCoreContext *  psDecCoreCtx = psDecStrUnit->psDecCoreCtx;
    IMG_UINT32 ui32PictureID = GET_STREAM_PICTURE_ID(psDecPict->ui32TransactionId);

    BSPP_sBitStrSeg   * psBitStrSeg = IMG_NULL;
    IMG_UINT32 ui32PictureBitStrSize = 0;

    psBitStrSeg = LST_first(&psDecStrUnit->psStrUnit->sBitStrSegList);
    while(psBitStrSeg != IMG_NULL)
    {
        ui32PictureBitStrSize += psBitStrSeg->ui32DataSize;
        psBitStrSeg = LST_next(psBitStrSeg);
    }

    if(psDecPict->psFirstFieldFwMsg->sPerformanceData.bFirstFieldReceived)
    {
        decoder_WritePerfData(psStrCtx->ui32StrId, ui32PictureID, DATA_ITEM, CORE_ID, psDecCoreCtx->ui32CoreNum);
        decoder_WritePerfData(psStrCtx->ui32StrId, ui32PictureID, DATA_ITEM, FRAME_ID, ui32PictureID);
        decoder_WritePerfData(psStrCtx->ui32StrId, ui32PictureID, DATA_ITEM, SLICE_NUM, psDecPict->psFirstFieldFwMsg->sPerformanceData.ui16NumSlices);
        //decoder_WritePerfData(psStrCtx->ui32StrId, ui32PictureID, DATA_ITEM, SLICE_TYPE, psDecPict->psPictHdrInfo->eCodingType);
        decoder_WritePerfData(psStrCtx->ui32StrId, ui32PictureID, DATA_ITEM, FRAME_BITSTREAM_BIT_SIZE, ui32PictureBitStrSize);
        decoder_WritePerfData(psStrCtx->ui32StrId, ui32PictureID, DATA_ITEM, FRAME_CODED_WIDTH, psDecPict->psPictHdrInfo->sCodedFrameSize.ui32Width);
        decoder_WritePerfData(psStrCtx->ui32StrId, ui32PictureID, DATA_ITEM, FRAME_CODED_HEIGHT, psDecPict->psPictHdrInfo->sCodedFrameSize.ui32Height);
        decoder_WritePerfData(psStrCtx->ui32StrId, ui32PictureID, DATA_ITEM, FRAME_CODED_SIZE,
            psDecPict->psPictHdrInfo->sCodedFrameSize.ui32Width*psDecPict->psPictHdrInfo->sCodedFrameSize.ui32Height);

        decoder_SavePerfDataField(psStrCtx->ui32StrId, ui32PictureID, &psDecPict->psFirstFieldFwMsg->sPerformanceData);
    }

    if(psDecPict->psSecondFieldFwMsg->sPerformanceData.bFirstFieldReceived)
    {
        decoder_WritePerfData(psStrCtx->ui32StrId, ui32PictureID, DATA_ITEM, CORE_ID, psDecCoreCtx->ui32CoreNum);
        decoder_WritePerfData(psStrCtx->ui32StrId, ui32PictureID, DATA_ITEM, FRAME_ID, ui32PictureID+1);
        decoder_WritePerfData(psStrCtx->ui32StrId, ui32PictureID, DATA_ITEM, SLICE_NUM, psDecPict->psSecondFieldFwMsg->sPerformanceData.ui16NumSlices);
        //decoder_WritePerfData(psStrCtx->ui32StrId, ui32PictureID, DATA_ITEM, SLICE_TYPE, psDecPict->psPictHdrInfo->eCodingType);
        decoder_WritePerfData(psStrCtx->ui32StrId, ui32PictureID, DATA_ITEM, FRAME_BITSTREAM_BIT_SIZE, ui32PictureBitStrSize);
        decoder_WritePerfData(psStrCtx->ui32StrId, ui32PictureID, DATA_ITEM, FRAME_CODED_WIDTH, psDecPict->psPictHdrInfo->sCodedFrameSize.ui32Width);
        decoder_WritePerfData(psStrCtx->ui32StrId, ui32PictureID, DATA_ITEM, FRAME_CODED_HEIGHT, psDecPict->psPictHdrInfo->sCodedFrameSize.ui32Height);
        decoder_WritePerfData(psStrCtx->ui32StrId, ui32PictureID, DATA_ITEM, FRAME_CODED_SIZE,
            psDecPict->psPictHdrInfo->sCodedFrameSize.ui32Width*psDecPict->psPictHdrInfo->sCodedFrameSize.ui32Height);

        decoder_SavePerfDataField(psStrCtx->ui32StrId, ui32PictureID, &psDecPict->psSecondFieldFwMsg->sPerformanceData);
    }

    return IMG_SUCCESS;
}
#endif

/*!
******************************************************************************

 @Function              decoder_SetFeatureFlags

 @Description

 This function sets the features flags from the core properties.

 @Input     p                     : Pointer to core properties.

 @Input     pui32CoreFeatureFlags : Pointer to core feature flags word.

******************************************************************************/
static IMG_VOID
decoder_SetFeatureFlags(
    VXD_sCoreProps      * psCoreProps,
    IMG_UINT32          * pui32CoreFeatureFlags,
    IMG_UINT32          * aui32PipeFeatureFlags
)
{
    IMG_UINT8 ui8PipeMinus1;

    for(ui8PipeMinus1 = 0; ui8PipeMinus1 < psCoreProps->ui32NumPixelPipes; ui8PipeMinus1++)
    {
        *pui32CoreFeatureFlags |= aui32PipeFeatureFlags[ui8PipeMinus1] |= (psCoreProps->abMpeg2[ui8PipeMinus1]) ? VDECDD_COREFEATURE_MPEG2 : 0;
        *pui32CoreFeatureFlags |= aui32PipeFeatureFlags[ui8PipeMinus1] |= (psCoreProps->abMpeg4[ui8PipeMinus1]) ? VDECDD_COREFEATURE_MPEG4 : 0;
        *pui32CoreFeatureFlags |= aui32PipeFeatureFlags[ui8PipeMinus1] |= (psCoreProps->abH264[ui8PipeMinus1])  ? VDECDD_COREFEATURE_H264  : 0;
        *pui32CoreFeatureFlags |= aui32PipeFeatureFlags[ui8PipeMinus1] |= (psCoreProps->abVc1[ui8PipeMinus1])   ? VDECDD_COREFEATURE_VC1   : 0;
        *pui32CoreFeatureFlags |= aui32PipeFeatureFlags[ui8PipeMinus1] |= (psCoreProps->abAvs[ui8PipeMinus1])   ? VDECDD_COREFEATURE_AVS   : 0;
        *pui32CoreFeatureFlags |= aui32PipeFeatureFlags[ui8PipeMinus1] |= (psCoreProps->abReal[ui8PipeMinus1])  ? VDECDD_COREFEATURE_REAL  : 0;
        *pui32CoreFeatureFlags |= aui32PipeFeatureFlags[ui8PipeMinus1] |= (psCoreProps->abJpeg[ui8PipeMinus1])  ? VDECDD_COREFEATURE_JPEG  : 0;
        *pui32CoreFeatureFlags |= aui32PipeFeatureFlags[ui8PipeMinus1] |= (psCoreProps->abVp6[ui8PipeMinus1])   ? VDECDD_COREFEATURE_VP6   : 0;
        *pui32CoreFeatureFlags |= aui32PipeFeatureFlags[ui8PipeMinus1] |= (psCoreProps->abVp8[ui8PipeMinus1])   ? VDECDD_COREFEATURE_VP8   : 0;
         //only first pipe can be master when decoding HEVC in multipipe mode (FW restriction)
        *pui32CoreFeatureFlags |= aui32PipeFeatureFlags[ui8PipeMinus1] |= (psCoreProps->abHEVC[ui8PipeMinus1]) && ui8PipeMinus1 == 0 ? VDECDD_COREFEATURE_HEVC  : 0;
        *pui32CoreFeatureFlags |= aui32PipeFeatureFlags[ui8PipeMinus1] |= (psCoreProps->bHdSupport)       ? VDECDD_COREFEATURE_HD_DECODE         : 0;
        *pui32CoreFeatureFlags |= aui32PipeFeatureFlags[ui8PipeMinus1] |= (psCoreProps->abRotationSupport[ui8PipeMinus1]) ? VDECDD_COREFEATURE_ROTATION          : 0;
        *pui32CoreFeatureFlags |= aui32PipeFeatureFlags[ui8PipeMinus1] |= (psCoreProps->abScalingSupport[ui8PipeMinus1])  ? VDECDD_COREFEATURE_SCALING           : 0;
        *pui32CoreFeatureFlags |= aui32PipeFeatureFlags[ui8PipeMinus1] |= (psCoreProps->bScalingWithOold) ? VDECDD_COREFEATURE_SCALING_WITH_OOLD : 0;
        *pui32CoreFeatureFlags |= aui32PipeFeatureFlags[ui8PipeMinus1] |= (psCoreProps->bExtendedStrides) ? VDECDD_COREFEATURE_EXTENDED_STRIDES  : 0;
}
}



/*!
******************************************************************************

 @Function              decoder_CoreGetContext

 @Description

 This function returns the core context structure for the given core number.

 @Input     psDecCtx : Pointer to Decoder context.

 @Input     ui32CoreNum : Core number.

 @Return    DECODER_sCoreContext : This function returns a pointer to the core
                                   context structure or IMG_NULL if not found.

******************************************************************************/
static DECODER_sCoreContext *
decoder_CoreGetContext(
    DECODER_sContext * psDecCtx,
    IMG_UINT32 ui32CoreNum
)
{
    DECODER_sCoreContext * psDecCoreCtx;
    IMG_BOOL bFound;
    IMG_UINT32 i = 0;

    // Ensure that the decoder component has been initialised.
    IMG_ASSERT(psDecCtx->bInitialised);

    bFound = IMG_FALSE;
    psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
    while (psDecCoreCtx)
    {
        i++;
        if (psDecCoreCtx->ui32CoreNum == ui32CoreNum)
        {
            bFound = IMG_TRUE;
            break;
        }

        psDecCoreCtx = LST_next(psDecCoreCtx);
    }

    return (bFound) ? psDecCoreCtx : IMG_NULL;
}


/*!
******************************************************************************

 @Function              decoder_GetCoreAndLoad

******************************************************************************/
static IMG_RESULT
decoder_GetCoreAndLoad(
    DECODER_sContext      * psDecCtx,
    IMG_UINT32              ui32StreamFeature,
    IMG_UINT32            * pui32AvailLoad,
    IMG_UINT32            * pui32MinLoad,
    DECODER_sCoreContext ** ppsDecCoreCtx,
    IMG_UINT8             * pui8MinLoadedPipe
)
{
    DECODER_sCoreContext * psDecCoreCtx;
    IMG_UINT32             ui32AvailLoad = -1;
    IMG_UINT32             ui32MinLoad = -1;
    IMG_RESULT             ui32Result;

    psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
    while (psDecCoreCtx)
    {
        // Determine the main/available load on suitable cores.
        if ((ui32StreamFeature & psDecCoreCtx->ui32CoreFeatures) == ui32StreamFeature && !psDecCoreCtx->bBusy)
        {
            IMG_UINT32 aui32NumFreeSlots[VDEC_MAX_PIXEL_PIPES];
            IMG_UINT32 aui32PipeLoad[VDEC_MAX_PIXEL_PIPES];
            IMG_UINT8  ui8PipeMinus1 = 0;

            ui32Result = HWCTRL_GetCoreStatus(psDecCoreCtx->hHwCtx,
                                              aui32NumFreeSlots,
                                              aui32PipeLoad,
                                              IMG_NULL);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            for(ui8PipeMinus1 = 0; ui8PipeMinus1 < VDEC_MAX_PIXEL_PIPES;ui8PipeMinus1++)
            {
                if((ui32StreamFeature & psDecCoreCtx->aui32PipeFeatures[ui8PipeMinus1]) == ui32StreamFeature )
                {
                    if (aui32PipeLoad[ui8PipeMinus1] < ui32MinLoad)
                    {
                        ui32MinLoad = aui32PipeLoad[ui8PipeMinus1];
            }

                    if (aui32NumFreeSlots[ui8PipeMinus1] &&
                        aui32PipeLoad[ui8PipeMinus1] < ui32AvailLoad)
            {
                        ui32AvailLoad = aui32PipeLoad[ui8PipeMinus1];

                        if(pui8MinLoadedPipe)
                        {
                            *pui8MinLoadedPipe = ui8PipeMinus1 + 1;
                        }

                if (ppsDecCoreCtx)
                {
                    *ppsDecCoreCtx = psDecCoreCtx;
                }
            }
        }
            }
        }

        psDecCoreCtx = LST_next(psDecCoreCtx);
    }

    if (pui32MinLoad)
    {
        *pui32MinLoad = ui32MinLoad;
    }
    if (pui32AvailLoad)
    {
        *pui32AvailLoad = ui32AvailLoad;
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              decoder_PictureDestroy

 @Description

 Free the picture container and optionally release image buffer back to client.
 Default is to decrement the reference count held by this picture.

******************************************************************************/
static IMG_RESULT
decoder_PictureDestroy(
    DECODER_sStrContext * psDecStrCtx,
    IMG_UINT32 ui32PictId,
    IMG_BOOL bReleaseImage
)
{
    VDECDD_sPicture * psPicture;
    IMG_RESULT ui32Result;

    ui32Result = IDGEN_GetHandle(psDecStrCtx->hPictIdGen, ui32PictId, (IMG_VOID **)&psPicture);
    if (ui32Result == IMG_SUCCESS)
    {
        ui32Result = IDGEN_FreeId(psDecStrCtx->hPictIdGen, ui32PictId);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        if (psPicture->psDecPictInfo)
        {
            // Destroy the picture
            IMG_FREE(psPicture->psDecPictInfo);
            psPicture->psDecPictInfo = IMG_NULL;
        }

        // Return unused picture and internal resources
        if (psPicture->sDisplayPictBuf.psPictBuf)
        {
            if (bReleaseImage)
            {
                RESOURCE_ItemRelease(&psPicture->sDisplayPictBuf.psPictBuf->sDdBufInfo.ui32RefCount);
            }
            else
            {
                RESOURCE_ItemReturn(&psPicture->sDisplayPictBuf.psPictBuf->sDdBufInfo.ui32RefCount);
            }
            VDEC_BZERO(&psPicture->sDisplayPictBuf);
        }

        if (psPicture->psPictResInt)
        {
            RESOURCE_ItemReturn(&psPicture->psPictResInt->ui32RefCount);
            psPicture->psPictResInt = IMG_NULL;
        }

        IMG_FREE(psPicture);
        psPicture = IMG_NULL;
    }
    else
    {
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        return ui32Result;
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              decoder_DecodedPictureDestroy

******************************************************************************/
static IMG_RESULT
decoder_DecodedPictureDestroy(
    DECODER_sStrContext  * psDecStrCtx,
    DECODER_sDecodedPict * psDecodedPict,
    IMG_BOOL               bReleaseImageToClient
)
{
    IMG_RESULT ui32Result;

    if (psDecodedPict->psPicture)
    {
        IMG_ASSERT(psDecodedPict->psPicture->ui32PictId == GET_STREAM_PICTURE_ID(psDecodedPict->ui32TransactionId));

        ui32Result = decoder_PictureDestroy(psDecStrCtx,
                                            psDecodedPict->psPicture->ui32PictId,
                                            bReleaseImageToClient);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        psDecodedPict->psPicture = IMG_NULL;
    }

    DQ_remove(psDecodedPict); // DQ List: psDecStrCtx->sStrDecdPictList
    psDecStrCtx->sDecStrStatus.ui32NumPictDecoded--;

    RESOURCE_ItemReturn(&psDecodedPict->psPictRefRes->ui32RefCount);

    DEBUG_REPORT(REPORT_MODULE_DECODER,
        "[USERSID=0x%08X] [TID=0x%08X] COMPLETE",
        GET_STREAM_ID(psDecodedPict->ui32TransactionId),
        psDecodedPict->ui32TransactionId);

    IMG_FREE(psDecodedPict->psFirstFieldFwMsg);
    psDecodedPict->psFirstFieldFwMsg = IMG_NULL;
    IMG_FREE(psDecodedPict->psSecondFieldFwMsg);
    psDecodedPict->psSecondFieldFwMsg = IMG_NULL;

    IMG_FREE(psDecodedPict);
    psDecodedPict = IMG_NULL;

    return IMG_SUCCESS;
}


#ifdef VDEC_MSVDX_HARDWARE

/*!
******************************************************************************

 @Function              decoder_GetDecodedPict

******************************************************************************/
static DECODER_sDecodedPict *
decoder_GetDecodedPict(
    IMG_UINT32      ui32TransactionId,
    DQ_T          * psDqList
)
{
    DECODER_sDecodedPict * psDecodedPict;
    IMG_VOID * pvItem = IMG_NULL;

    psDecodedPict = DQ_first(psDqList);
    while (psDecodedPict)
    {
        if (psDecodedPict->ui32TransactionId == ui32TransactionId)
        {
            pvItem = psDecodedPict;
            break;
        }

        if (psDecodedPict != DQ_last(psDqList))
        {
            psDecodedPict = DQ_next(psDecodedPict);
        }
        else
        {
            psDecodedPict = IMG_NULL;
        }
    }

    return pvItem;
}

/*!
******************************************************************************

 @Function              decoder_GetDecodedPictOfStream

******************************************************************************/
static DECODER_sDecodedPict *
decoder_GetDecodedPictOfStream(
    IMG_UINT32      ui32PictId,
    DQ_T          * psDqList
)
{
    DECODER_sDecodedPict * psDecodedPict;
    IMG_VOID * pvItem = IMG_NULL;

    psDecodedPict = DQ_first(psDqList);
    while (psDecodedPict)
    {
        if (GET_STREAM_PICTURE_ID(psDecodedPict->ui32TransactionId) == ui32PictId)
        {
            pvItem = psDecodedPict;
            break;
        }

        if (psDecodedPict != DQ_last(psDqList))
        {
            psDecodedPict = DQ_next(psDecodedPict);
        }
        else
        {
            psDecodedPict = IMG_NULL;
        }
    }

    return pvItem;
}

#endif


/*!
******************************************************************************

 @Function              decoder_PictureDisplay

******************************************************************************/
static IMG_RESULT
decoder_PictureDisplay(
    DECODER_sStrContext * psDecStrCtx,
    IMG_UINT32 ui32PictId,
    IMG_BOOL bLast
)
{
    VDECDD_sPicture * psPicture;
    IMG_RESULT        ui32Result;
    static IMG_UINT32 ui32DisplayNum = 0;

    ui32Result = IDGEN_GetHandle(psDecStrCtx->hPictIdGen, ui32PictId, (IMG_VOID **)&psPicture);
    if (ui32Result == IMG_SUCCESS)
    {
        // Indicate whether there are more pictures coming for display.
        psPicture->psDecPictInfo->bLastInSequence = bLast;

        // Set decode order id
        psPicture->psDecPictInfo->ui32DecodeId = ui32PictId;

        // this can happen when reference pictures span different configurations.

        // Return the picture to the client for display
        psDecStrCtx->sDecStrStatus.ui32TotalPictDisplayed++;
        RESOURCE_ItemUse(&psPicture->sDisplayPictBuf.psPictBuf->sDdBufInfo.ui32RefCount);

        ui32DisplayNum++;
        DEBUG_REPORT(REPORT_MODULE_DECODER,
            "[USERSID=0x%08X] DISPLAY(%d): PIC_ID[%d]",
            psDecStrCtx->sConfig.ui32UserStrId,
            ui32DisplayNum,
            ui32PictId);

#if defined(CONFIG_X86)
        if(psPicture->sDisplayPictBuf.psPictBuf->sDdBufInfo.pvCpuVirt)
        {
            clflush_cache_range(psPicture->sDisplayPictBuf.psPictBuf->sDdBufInfo.pvCpuVirt, psPicture->sDisplayPictBuf.psPictBuf->sDdBufInfo.ui32BufSize);
        }
#endif
#if 0
        {
            IMG_UINT32 i;
            IMG_UINT32 ui32CodedWidth;
            IMG_UINT32 ui32CodedHeight;
            static IMG_UINT32 ui32OutputNum = 0;
            static IMG_VOID * fpDump = IMG_NULL;
            static VDEC_sPictRendInfo sPictBufInfo;

            if (fpDump == IMG_NULL ||
                IMG_MEMCMP(&psPicture->sDisplayPictBuf.sPictBufInfo, &sPictBufInfo, sizeof(sPictBufInfo)))
            {
                IMG_CHAR acName[128];

                if (fpDump)
                {
                    fclose(fpDump);
                }
                else
                {
                    IMG_MEMSET(&sPictBufInfo, 0, sizeof(sPictBufInfo));
                }

                sprintf(acName,"dump_%d.res", ui32OutputNum++);

                fpDump = fopen(acName, "wb");
                IMG_ASSERT(fpDump);
            }

            if (psPicture->psDecPictInfo->sOutputConfig.eRotMode == VDEC_ROTATE_90 ||
                psPicture->psDecPictInfo->sOutputConfig.eRotMode == VDEC_ROTATE_270)
            {
                ui32CodedWidth = psPicture->sDisplayPictBuf.sPictBufInfo.sRendPictSize.ui32Height;
                ui32CodedHeight = psPicture->sDisplayPictBuf.sPictBufInfo.sRendPictSize.ui32Width;
            }
            else
            {
                ui32CodedWidth = psPicture->sDisplayPictBuf.sPictBufInfo.sRendPictSize.ui32Width;
                ui32CodedHeight = psPicture->sDisplayPictBuf.sPictBufInfo.sRendPictSize.ui32Height;
            }

            // Write luma.
            for (i = 0; i < ui32CodedHeight; i++)
            {
                fwrite((IMG_UINT8*)psPicture->sDisplayPictBuf.psPictBuf->sDdBufInfo.pvCpuVirt +
                       (i * psPicture->sDisplayPictBuf.sPictBufInfo.asPlaneInfo[0].ui32Stride),
                       1,
                       psPicture->sDisplayPictBuf.sPictBufInfo.asPlaneInfo[0].ui32Stride,
                       fpDump);
            }

            // Write chroma.
            for (i = 0; i < (ui32CodedHeight+1)/2; i++)
            {
                fwrite((IMG_UINT8 * )psPicture->sDisplayPictBuf.psPictBuf->sDdBufInfo.pvCpuVirt +
                            psPicture->sDisplayPictBuf.sPictBufInfo.asPlaneInfo[1].ui32Offset +
                       (i * psPicture->sDisplayPictBuf.sPictBufInfo.asPlaneInfo[1].ui32Stride),
                       1,
                       psPicture->sDisplayPictBuf.sPictBufInfo.asPlaneInfo[1].ui32Stride,
                       fpDump);
            }

            sPictBufInfo = psPicture->sDisplayPictBuf.sPictBufInfo;
        }
#endif

        ui32Result = psDecStrCtx->psDecCtx->pfnCompCallback(
            DECODER_CB_PICTURE_DISPLAY,
            psDecStrCtx->psDecCtx->pvCompInitUserData,
            IMG_NULL,
            psDecStrCtx->pvUserData,
            psPicture);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }
    else
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "[USERSID=0x%08X] ERROR: DISPLAY PICTURE HAS AN EXPIRED ID",
            psDecStrCtx->sConfig.ui32UserStrId);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              DECODER_GetNextDecPictContiguous

******************************************************************************/
static DECODER_sDecodedPict *
DECODER_GetNextDecPictContiguous(
    DECODER_sDecodedPict  * psDecodedPicture,
    IMG_UINT32              ui32NextDecPictId,
    DQ_T                  * psStrDecdPictList
)
{
    DECODER_sDecodedPict * psNextDecPict = IMG_NULL;
    DECODER_sDecodedPict * psResultDecPict = IMG_NULL;

    if (psDecodedPicture)
    {
        if (psDecodedPicture != DQ_last(psStrDecdPictList))
        {
            psNextDecPict = DQ_next(psDecodedPicture);

            if (IMG_NULL != psNextDecPict->psPicture)
            {
                // If we have no holes in the decoded list (i.e. next
                // decoded picture is next in bitstream decode order).
                if (HAS_X_REACHED_Y(ui32NextDecPictId, psNextDecPict->psPicture->ui32PictId, 1 << FWIF_NUMBITS_STREAM_PICTURE_ID))
                {
                    psResultDecPict = psNextDecPict;
                }
            }
        }
    }

    return psResultDecPict;
}


/*!
******************************************************************************

 @Function              decoder_NextPicture

 @Description

 Returns the next unprocessed picture or IMG_NULL if the next picture is not
 next in bitstream decode order or there are no more decoded pictures in the
 list.

 @Input     psCurrentDecodedPicture : Pointer to current decoded picture.

 @Input     ui32NextDecPictId       : Picture ID of next picture in decode order.

 @Input     psStrDecdPictList       : Pointer to decoded picture list.

 @Return    DECODER_sDecodedPict *  : Pointer to next decoded picture to process.

******************************************************************************/
static DECODER_sDecodedPict *
decoder_NextPicture(
    DECODER_sDecodedPict  * psCurrentDecodedPicture,
    IMG_UINT32              ui32NextDecPictId,
    DQ_T                  * psStrDecdPictList
)
{
    DECODER_sDecodedPict* psReturn = IMG_NULL;

    IMG_ASSERT(psStrDecdPictList != IMG_NULL);
    if(psStrDecdPictList == IMG_NULL)
    {
        return IMG_NULL;
    }

    if (psCurrentDecodedPicture == IMG_NULL)
    {
        psCurrentDecodedPicture = DQ_first(psStrDecdPictList);
    }

    if (psCurrentDecodedPicture != IMG_NULL && !psCurrentDecodedPicture->bProcessFailed)
    {
        // Search for picture ID greater than picture in list
        do
        {
            if (!psCurrentDecodedPicture->bProcessed)
            {
                //Return the current one because it has not been processed
                psReturn = psCurrentDecodedPicture;
                break;
            }

            // Obtain a pointer to the next picture in bitstream decode order.
            psCurrentDecodedPicture = DECODER_GetNextDecPictContiguous(psCurrentDecodedPicture, ui32NextDecPictId, psStrDecdPictList);
        }
        while (psCurrentDecodedPicture && !psCurrentDecodedPicture->bProcessFailed);
    }

    return psReturn;
}

/*!
******************************************************************************

 @Function              decoder_PictureDecoded

******************************************************************************/
static IMG_RESULT
decoder_PictureDecoded(
    DECODER_sStrContext   * psDecStrCtx,
    VDECDD_sPicture       * psPicture,
    DECODER_sFwMessage    * psFirstFieldFwMsg,
    DECODER_sFwMessage    * psSecondFieldFwMsg,
    DECODER_sPictRefRes   * psPictRefRes,
    IMG_UINT32              ui32TransactionId
)
{
    DECODER_sDecodedPict  * psDecodedPict;
    DECODER_sDecodedPict  * psNextDecodedPict;
#ifdef VDEC_MSVDX_HARDWARE
    DECODER_sDecodedPict  * psPrevDecodedPict;
    VDECFW_sBufferControl * psBufferControl;
#endif
    VDEC_sComSequHdrInfo  * psComSequHdrInfo = &psPicture->sDisplayPictBuf.psPictBuf->psDdStrContext->sComSequHdrInfo;
    IMG_RESULT ui32Result;

    // Create a container for decoded picture.
    VDEC_MALLOC(psDecodedPict);
    IMG_ASSERT(psDecodedPict);
    if (psDecodedPict == IMG_NULL)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "[USERSID=0x%08X] Failed to allocate memory for decoded picture",
            psDecStrCtx->sConfig.ui32UserStrId);
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psDecodedPict);

    psDecodedPict->psPicture = psPicture;
    psDecodedPict->psFirstFieldFwMsg = psFirstFieldFwMsg;
    psDecodedPict->psSecondFieldFwMsg = psSecondFieldFwMsg;
    psDecodedPict->psPictRefRes = psPictRefRes;
    psDecodedPict->ui32TransactionId = ui32TransactionId;

    //Updating the Buffer Control which contains information about pictures to display and release
    UPDATE_HOST((&psDecodedPict->psPictRefRes->sFwCtrlBuf), !decoder_IsFakeMTX(psDecStrCtx->psDecCtx, GET_CORE_ID(ui32TransactionId)));
    // Updating standard specific context.
    UPDATE_HOST((&psDecStrCtx->psCurFePictDecRes->sFwCtxBuf), !decoder_IsFakeMTX(psDecStrCtx->psDecCtx, GET_CORE_ID(ui32TransactionId)));

    // Populate the decoded picture information structure.
    psPicture->psDecPictInfo->ePictState = VDEC_PICT_STATE_DECODED;

    IMG_MEMCPY(&psPicture->psDecPictInfo->sFirstFieldTagContainer.sPictHwCrc, &psFirstFieldFwMsg->sPictHwCrc, sizeof(psPicture->psDecPictInfo->sFirstFieldTagContainer.sPictHwCrc));
    IMG_MEMCPY(&psPicture->psDecPictInfo->sSecondFieldTagContainer.sPictHwCrc, &psSecondFieldFwMsg->sPictHwCrc, sizeof(psPicture->psDecPictInfo->sSecondFieldTagContainer.sPictHwCrc));

#ifdef VDEC_MSVDX_HARDWARE
    psBufferControl = (VDECFW_sBufferControl*)psDecodedPict->psPictRefRes->sFwCtrlBuf.pvCpuVirt;
    if (psBufferControl->b2ndFieldOfPair)
    {
        // Search the first field anc fill the sSecondFieldTagContainer
        IMG_UINT32 ui32PrevDecPictId = (GET_PREV_PICTURE_ID(GET_STREAM_PICTURE_ID(psDecodedPict->ui32TransactionId)));
        psPrevDecodedPict = decoder_GetDecodedPictOfStream(ui32PrevDecPictId,&psDecStrCtx->sStrDecdPictList);
        if(psPrevDecodedPict != IMG_NULL)
        {
            IMG_MEMCPY(&psPicture->psDecPictInfo->sSecondFieldTagContainer.sPictHwCrc, &psPrevDecodedPict->psFirstFieldFwMsg->sPictHwCrc, sizeof(psPicture->psDecPictInfo->sSecondFieldTagContainer.sPictHwCrc));
        }
        else
        {
            REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "[USERSID=0x%08X] [TID 0x%08X] Failed to find decoded picture to attatch sSecondFieldTagContainer",
                psDecStrCtx->sConfig.ui32UserStrId, psDecodedPict->ui32TransactionId);
        }
        psPrevDecodedPict = IMG_NULL;
    }
#endif

    // Report any issues in decoding
    if (psDecodedPict->psPicture->psDecPictInfo->ui32ErrorFlags )
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
            "[USERSID=0x%08X] [PID=0x%08X] BSPP reported errors [flags: 0x%08X]",
            psDecStrCtx->sConfig.ui32UserStrId,
            psDecodedPict->psPicture->ui32PictId,
            psDecodedPict->psPicture->psDecPictInfo->ui32ErrorFlags);
    }

    if ((psDecodedPict->psFirstFieldFwMsg->sPictDecoded.ui32FEError & FLAG_MASK(VDECFW_MSGFLAG_DECODED_FEERROR_PSRWDT)) ||
        (psDecodedPict->psSecondFieldFwMsg->sPictDecoded.ui32FEError & FLAG_MASK(VDECFW_MSGFLAG_DECODED_FEERROR_PSRWDT)))
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
            "[USERSID=0x%08X] [TID 0x%08X] Firmware parsing timed-out.",
            psDecStrCtx->sConfig.ui32UserStrId, psDecodedPict->ui32TransactionId);
        psPicture->psDecPictInfo->ui32ErrorFlags |= VDEC_ERROR_PSR_TIMEOUT;
    }
    if ((psDecodedPict->psFirstFieldFwMsg->sPictDecoded.ui32FEError & FLAG_MASK(VDECFW_MSGFLAG_DECODED_FEERROR_ENTDECERROR)) ||
        (psDecodedPict->psSecondFieldFwMsg->sPictDecoded.ui32FEError & FLAG_MASK(VDECFW_MSGFLAG_DECODED_FEERROR_ENTDECERROR)))
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
            "[USERSID=0x%08X] [TID 0x%08X] Front-end HW processing terminated prematurely due to an error.",
            psDecStrCtx->sConfig.ui32UserStrId, psDecodedPict->ui32TransactionId);
        psPicture->psDecPictInfo->ui32ErrorFlags |= VDEC_ERROR_FEHW_DECODE;
    }
    if ((psDecodedPict->psFirstFieldFwMsg->sPictDecoded.ui32FEError & FLAG_MASK(VDECFW_MSGFLAG_DECODED_FEERROR_SRERROR)) ||
        (psDecodedPict->psSecondFieldFwMsg->sPictDecoded.ui32FEError & FLAG_MASK(VDECFW_MSGFLAG_DECODED_FEERROR_SRERROR)))
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
            "[USERSID=0x%08X] [TID 0x%08X] HW Shift Register access returned an error during FEWH parsing.",
            psDecStrCtx->sConfig.ui32UserStrId, psDecodedPict->ui32TransactionId);
        psPicture->psDecPictInfo->ui32ErrorFlags |= VDEC_ERROR_SR_ERROR;
    }
    if ((psDecodedPict->psFirstFieldFwMsg->sPictDecoded.ui32FEError & FLAG_MASK(VDECFW_MSGFLAG_DECODED_FEERROR_SRERROR_FW_PARSING)) ||
        (psDecodedPict->psSecondFieldFwMsg->sPictDecoded.ui32FEError & FLAG_MASK(VDECFW_MSGFLAG_DECODED_FEERROR_SRERROR_FW_PARSING)))
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
            "[USERSID=0x%08X] [TID 0x%08X] HW Shift Register access returned an error during firmware header parsing.",
            psDecStrCtx->sConfig.ui32UserStrId, psDecodedPict->ui32TransactionId);
        psPicture->psDecPictInfo->ui32ErrorFlags |= VDEC_ERROR_PSR_SR_ERROR;
    }
    if ((psDecodedPict->psFirstFieldFwMsg->sPictDecoded.ui32FEError & FLAG_MASK(VDECFW_MSGFLAG_DECODED_FEERROR_FW_PARSING_SEQ_ERROR)) ||
        (psDecodedPict->psSecondFieldFwMsg->sPictDecoded.ui32FEError & FLAG_MASK(VDECFW_MSGFLAG_DECODED_FEERROR_FW_PARSING_SEQ_ERROR)))
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
            "[USERSID=0x%08X] [TID 0x%08X] Firmware parser failed to  follow all the required processing steps.",
            psDecStrCtx->sConfig.ui32UserStrId, psDecodedPict->ui32TransactionId);
        psPicture->psDecPictInfo->ui32ErrorFlags |= VDEC_ERROR_PSR_PROCESS_NOT_NORMAL;
    }
    if ((psDecodedPict->psFirstFieldFwMsg->sPictDecoded.ui32FEError & (1 << VDECFW_MSGFLAG_DECODED_FEERROR_HWWDT_SHIFT)) ||
        (psDecodedPict->psSecondFieldFwMsg->sPictDecoded.ui32FEError & (1 << VDECFW_MSGFLAG_DECODED_FEERROR_HWWDT_SHIFT)))
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
            "[USERSID=0x%08X] [TID 0x%08X] Front-end HW processing timed-out.",
            psDecStrCtx->sConfig.ui32UserStrId, psDecodedPict->ui32TransactionId);
        psPicture->psDecPictInfo->ui32ErrorFlags |= VDEC_ERROR_FEHW_TIMEOUT;
    }

    if ((psDecodedPict->psFirstFieldFwMsg->sPictDecoded.ui32FEError & (1 << VDECFW_MSGFLAG_DECODED_MISSING_REFERENCES_SHIFT)) ||
        (psDecodedPict->psSecondFieldFwMsg->sPictDecoded.ui32FEError & (1 << VDECFW_MSGFLAG_DECODED_MISSING_REFERENCES_SHIFT)))
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
            "[USERSID=0x%08X] [TID 0x%08X] There are missing references for the current frame.May have corruption",
            psDecStrCtx->sConfig.ui32UserStrId, psDecodedPict->ui32TransactionId);

        // This is not a serious error, indicate host app to drop the frame as may have corruption.
        psPicture->psDecPictInfo->ui32ErrorFlags |= VDEC_ERROR_MISSING_REFERENCES;
    }

    if (psDecodedPict->psFirstFieldFwMsg->sPictDecoded.ui32NoBEDWT > 0)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
            "[USERSID=0x%08X] [TID 0x%08X] Back-end HW processing timed-out. Aborted slices %d",
            psDecStrCtx->sConfig.ui32UserStrId, psDecodedPict->ui32TransactionId,
            psDecodedPict->psFirstFieldFwMsg->sPictDecoded.ui32NoBEDWT);
        psPicture->psDecPictInfo->ui32ErrorFlags |= VDEC_ERROR_BEHW_TIMEOUT;
    }
    if (psDecodedPict->psSecondFieldFwMsg->sPictDecoded.ui32NoBEDWT > 0)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
            "[USERSID=0x%08X] [TID 0x%08X] Back-end HW processing timed-out. Aborted slices %d",
            psDecStrCtx->sConfig.ui32UserStrId, psDecodedPict->ui32TransactionId,
            psDecodedPict->psSecondFieldFwMsg->sPictDecoded.ui32NoBEDWT);
        psPicture->psDecPictInfo->ui32ErrorFlags |= VDEC_ERROR_BEHW_TIMEOUT;
    }

    if ((psDecodedPict->psFirstFieldFwMsg->sPictDecoded.bDWRFired) ||
        (psDecodedPict->psSecondFieldFwMsg->sPictDecoded.bDWRFired))
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
            "[USERSID=0x%08X] MSVDX Device Reset (DWR or MMU fault).",
            psDecStrCtx->sConfig.ui32UserStrId);
        psPicture->psDecPictInfo->ui32ErrorFlags |= VDEC_ERROR_SERVICE_TIMER_EXPIRY;
    }
#ifdef VDEC_MSVDX_HARDWARE
    if (!(((IMG_BUFFERTYPE_PAIR == psBufferControl->eDecPictType) &&
           VDECFW_PICMGMT_FIELD_CODED_PICTURE_EXECUTED(psBufferControl->ui8PictMgmtFlags))
          ||
          FLAG_IS_SET(psBufferControl->ui8PictMgmtFlags, VDECFW_PICMGMTFLAG_PICTURE_EXECUTED)))
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
            "[USERSID=0x%08X] [TID 0x%08X] Picture management was not executed for this picture; forcing display.",
            psDecStrCtx->sConfig.ui32UserStrId, psDecodedPict->ui32TransactionId);
        psDecodedPict->bForceDisplay = IMG_TRUE;
    }
#endif

    psDecStrCtx->sDecStrStatus.ui32TotalPictFinished++;

    //Use NextPictIdExpected to do this check. ui32NextPictId could be different
    //from what expected at this point because we failed to process a picture the last
    //time run this function (this is still an error (unless doing multi-core) but not
    //the error reported here.
    if (psDecStrCtx->psDecCtx->ui32NumCores == 1 &&
        psPicture->ui32PictId != psDecStrCtx->ui32NextPictIdExpected)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "[USERSID=0x%08X] ERROR: MISSING DECODED PICTURE (%d)",
            psDecStrCtx->sConfig.ui32UserStrId,
            psDecStrCtx->ui32NextDecPictId);
    }

    psDecStrCtx->ui32NextDecPictId = GET_NEXT_PICTURE_ID(GET_STREAM_PICTURE_ID(psDecodedPict->ui32TransactionId));
    psDecStrCtx->ui32NextPictIdExpected = psDecStrCtx->ui32NextDecPictId;

    // Add the picture itself to the decoded list
    psNextDecodedPict = DQ_first(&psDecStrCtx->sStrDecdPictList);
    while (psNextDecodedPict &&
           !HAS_X_REACHED_Y(GET_STREAM_PICTURE_ID(psNextDecodedPict->ui32TransactionId), psPicture->ui32PictId, 1 << FWIF_NUMBITS_STREAM_PICTURE_ID))
    {
        if (psNextDecodedPict != DQ_last(&psDecStrCtx->sStrDecdPictList))
        {
            psNextDecodedPict = DQ_next(psNextDecodedPict);
        }
        else
        {
            psNextDecodedPict = IMG_NULL;
        }
    }

    if (psNextDecodedPict)
    {
        DQ_addBefore(psNextDecodedPict, psDecodedPict);
    }
    else
    {
        DQ_addTail(&psDecStrCtx->sStrDecdPictList, psDecodedPict);
    }

    psDecStrCtx->sDecStrStatus.ui32NumPictDecoded++;

    // Process the decoded pictures in the encoded order.
    psDecodedPict = DQ_first(&psDecStrCtx->sStrDecdPictList);
    IMG_ASSERT(psDecodedPict);
    if (psDecodedPict == IMG_NULL)
    {
        ui32Result = IMG_ERROR_UNEXPECTED_STATE;
        goto error;
    }

    // Send picture decoded message for BSPP
    {
        IMG_UINT32  ui32Result;
        ui32Result = psDecStrCtx->psDecCtx->pfnCompCallback(
            DECODER_CB_PICTURE_DECODED,
            psDecStrCtx->psDecCtx->pvCompInitUserData,
            IMG_NULL,
            psDecStrCtx->pvUserData,
            psPicture);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }

    //Loop on the unprocessed pictures until we failed to process one or we have processed them all
    for(psNextDecodedPict = decoder_NextPicture(psDecodedPict, psDecStrCtx->ui32NextDecPictId, &psDecStrCtx->sStrDecdPictList);
        psNextDecodedPict != IMG_NULL;
        psNextDecodedPict = decoder_NextPicture(psDecodedPict, psDecStrCtx->ui32NextDecPictId, &psDecStrCtx->sStrDecdPictList))
    {
#ifdef VDEC_MSVDX_HARDWARE

        IMG_UINT32 i = 0;
        DECODER_sDecodedPict* psDisplayPict = IMG_NULL;
        DECODER_sDecodedPict* psReleasePict = IMG_NULL;
        IMG_BOOL bLastToDisplayForSeq = IMG_FALSE;
#endif
        //psNextDecodedPict is used to temporarily store psDecodedPict so that we can clear the bProcessFailed flag before returning
        psDecodedPict = psNextDecodedPict;

#ifdef VDEC_MSVDX_HARDWARE

        if ((psDecStrCtx->psDecCtx->psDevConfig->eDecodeLevel > VDECDD_DECODELEVEL_DECODER) && !psDecodedPict->bForceDisplay)
        {
            VDECFW_sBufferControl* psBufCtrl = IMG_NULL;

            //Updated above
            psBufCtrl = (VDECFW_sBufferControl*)psDecodedPict->psPictRefRes->sFwCtrlBuf.pvCpuVirt;

            if (psBufCtrl->ui32Width && psBufCtrl->ui32Height)
            {
                /* Firmware sets image size as it is in bitstream. */

                switch(psPicture->sOutputConfig.eRotMode)
                {
                case VDEC_ROTATE_90:
                    psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32Width = psBufCtrl->ui32Height;
                    psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32Height = psBufCtrl->ui32Width;
                    psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32TopOffset = 0;
                    psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32LeftOffset =
                        VDEC_ALIGN_SIZE(psBufCtrl->ui32Height, VDEC_MB_DIMENSION) - psBufCtrl->ui32Height;
                    break;
                case VDEC_ROTATE_180:
                    psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32Width = psBufCtrl->ui32Width;
                    psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32Height = psBufCtrl->ui32Height;
                    psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32TopOffset =
                        VDEC_ALIGN_SIZE(psBufCtrl->ui32Height, VDEC_MB_DIMENSION) - psBufCtrl->ui32Height;
                    psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32LeftOffset = VDEC_ALIGN_SIZE(psBufCtrl->ui32Width, VDEC_MB_DIMENSION) - psBufCtrl->ui32Width;
                    break;
                case VDEC_ROTATE_270:
                    psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32Width = psBufCtrl->ui32Height;
                    psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32Height = psBufCtrl->ui32Width;
                    psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32TopOffset = VDEC_ALIGN_SIZE(psBufCtrl->ui32Width, VDEC_MB_DIMENSION) - psBufCtrl->ui32Width;
                    psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32LeftOffset = 0;
                    break;
                case VDEC_ROTATE_0:
                default:
                    if ((psBufCtrl->ui32ScaleWidth!=0) && (psBufCtrl->ui32ScaleHeight!=0))
                    {
                        psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32Width = psBufCtrl->ui32ScaleWidth;
                        psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32Height = psBufCtrl->ui32ScaleHeight;
                    }
                    else
                    {
                        psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32Width = psBufCtrl->ui32Width;
                        psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32Height = psBufCtrl->ui32Height;
                    }
                    psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32TopOffset = 0;
                    psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32LeftOffset = 0;
                    break;
                }

                psPicture->psDecPictInfo->sRendInfo.sRendPictSize.ui32Width = psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32Width;
                psPicture->psDecPictInfo->sRendInfo.sRendPictSize.ui32Height = psPicture->psDecPictInfo->sDispInfo.sDispRegion.ui32Height;

                /* Update encoded size with values coded in bitstream, so golden image can be loaded correctly */
                psPicture->psDecPictInfo->sDispInfo.sEncDispRegion.ui32Width = psBufCtrl->ui32Width;
                psPicture->psDecPictInfo->sDispInfo.sEncDispRegion.ui32Height = psBufCtrl->ui32Height;
            }

            //if(psBufCtrl->eDecPictType == IMG_BUFFERTYPE_PAIR)
            //{
            //    psDecStrCtx->sDecStrStatus.ui32FieldsAsFrameDecodes++;
            //}
            psDecodedPict->psPicture->psDecPictInfo->ui32TimeStamp              =   psBufCtrl->ui32TimeStamp; // should be used in RV only
            psDecodedPict->psPicture->psDecPictInfo->sDispInfo.bTopFieldFirst = psBufCtrl->bTopFieldFirst;

            psDecodedPict->psPicture->psDecPictInfo->ui32IdForHWCrcCheck = GET_STREAM_PICTURE_ID(psDecodedPict->ui32TransactionId) - 1;
            psDecodedPict->psPicture->psDecPictInfo->ui32IdForHWCrcCheck += psDecStrCtx->sDecStrStatus.ui32FieldsAsFrameDecodes;

            if (IMG_BUFFERTYPE_PAIR == psBufCtrl->eDecPictType && !psBufCtrl->b2ndFieldOfPair)
            {
                psDecStrCtx->sDecStrStatus.ui32FieldsAsFrameDecodes++;
            }

            if (psBufCtrl->b2ndFieldOfPair)
            {
                // Second field of pair is always complementary type to the eFirstPictTagType of the previous picture
                IMG_UINT32 ui32PrevDecPictId = (GET_PREV_PICTURE_ID(GET_STREAM_PICTURE_ID(psDecodedPict->ui32TransactionId)));
                psPrevDecodedPict = decoder_GetDecodedPictOfStream(ui32PrevDecPictId,&psDecStrCtx->sStrDecdPictList);
                if(psPrevDecodedPict != IMG_NULL)
                {
                    psPrevDecodedPict->psPicture->psDecPictInfo->sSecondFieldTagContainer.pvPictTagParam = psDecodedPict->psPicture->psDecPictInfo->sFirstFieldTagContainer.pvPictTagParam;

                    //Copy the first field info in the proper place
                    IMG_MEMCPY(&psPrevDecodedPict->psPicture->psDecPictInfo->sSecondFieldTagContainer.sPictHwCrc,
                        &psFirstFieldFwMsg->sPictHwCrc,
                        sizeof(psPrevDecodedPict->psPicture->psDecPictInfo->sSecondFieldTagContainer.sPictHwCrc));

                    if (psDecStrCtx->sConfig.bUpdateYUV || psDecStrCtx->psDecCtx->psDevConfig->bPdumpAndRes)
                    {
                        /* Update the image buffer content for pdump */
                        UPDATE_HOST((&psPrevDecodedPict->psPicture->sDisplayPictBuf.psPictBuf->sDdBufInfo), IMG_TRUE);
                    }
                }
                else
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "[USERSID=0x%08X] [TID 0x%08X] Failed to find decoded picture to attatch tag",
                        psDecStrCtx->sConfig.ui32UserStrId, psDecodedPict->ui32TransactionId);
                }               
            }
            else
            {
                // Not Second-field-of-pair picture tag correlates its Tag to the its type by setting the eFirstPictTagType in the following way
                psDecodedPict->psPicture->psDecPictInfo->sFirstFieldTagContainer.ePicType = psBufCtrl->eDecPictType;
                IMG_MEMCPY(&psPicture->psDecPictInfo->sFirstFieldTagContainer.sPictHwCrc,
                        &psFirstFieldFwMsg->sPictHwCrc,
                        sizeof(psPicture->psDecPictInfo->sFirstFieldTagContainer.sPictHwCrc));

                if (psDecStrCtx->sConfig.bUpdateYUV || psDecStrCtx->psDecCtx->psDevConfig->bPdumpAndRes)
                {
                    if (psBufCtrl->eDecPictType != IMG_BUFFERTYPE_FIELD_TOP &&
                        psBufCtrl->eDecPictType != IMG_BUFFERTYPE_FIELD_BOTTOM)
                    {
                        /* Update the image buffer content for pdump */
                        UPDATE_HOST((&psDecodedPict->psPicture->sDisplayPictBuf.psPictBuf->sDdBufInfo), IMG_TRUE);
                    }
                }
             }

            //Update the id of the next picture to process. It has to be update always (even if we fail to process)
            //This has to be a global flag because it will be passed in both decoder_NextPicture (and then to DECODER_NextDecPictContiguous inside it)
            //and to the corner case check below
            psDecStrCtx->ui32NextDecPictId = GET_NEXT_PICTURE_ID(GET_STREAM_PICTURE_ID(psDecodedPict->ui32TransactionId));

            //Display all the picture in the list that have been decoded and signalled by the fw to be displayed
            for (i = psDecodedPict->ui32DisplayIdx;
                 i < psBufCtrl->ui32DisplayListLength && !psDecodedPict->bProcessFailed;
                 i++, psDecodedPict->ui32DisplayIdx++)
            {
                // Display picture if it has been decoded (i.e. in decoded list).
                psDisplayPict = decoder_GetDecodedPict(psBufCtrl->aui32DisplayList[i], &psDecStrCtx->sStrDecdPictList);
                if (psDisplayPict)
                {
                    if (FLAG_IS_SET((psBufCtrl->aui8DisplayFlags[i]), VDECFW_BUFFLAG_DISPLAY_FIELD_CODED))
                    {
                        if ( !FLAG_IS_SET((psBufCtrl->aui8DisplayFlags[i]), VDECFW_BUFFLAG_DISPLAY_SINGLE_FIELD) )
                        {
                            psDisplayPict->psPicture->psDecPictInfo->eBufferType = IMG_BUFFERTYPE_PAIR;
                        }
                        else
                        {
                            psDisplayPict->psPicture->psDecPictInfo->eBufferType =
                                FLAG_IS_SET((psBufCtrl->aui8DisplayFlags[i]), VDECFW_BUFFLAG_DISPLAY_BOTTOM_FIELD)
                                    ? IMG_BUFFERTYPE_FIELD_BOTTOM : IMG_BUFFERTYPE_FIELD_TOP;
                        }
                    }
                    else
                    {
                        psDisplayPict->psPicture->psDecPictInfo->eBufferType = IMG_BUFFERTYPE_FRAME;
                    }

                    psDisplayPict->psPicture->psDecPictInfo->ui16ViewID = psBufCtrl->aui8DisplayViewIds[i];

                    // When no reference pictures are left to display and this is the last display picture in response to the last decoded picture, signal.
                    if (/*LST_empty(&psDecStrCtx->sStrRefList) &&*/ psDecodedPict->psPicture->bLastPictInSeq && (i == (psBufCtrl->ui32DisplayListLength - 1)))
                    {
                        bLastToDisplayForSeq = IMG_TRUE;
                    }

                    DEBUG_REPORT(REPORT_MODULE_DECODER,
                        "[USERSID=0x%08X] [TID=0x%08X] DISPLAY",
                        psDecStrCtx->sConfig.ui32UserStrId,
                        psBufCtrl->aui32DisplayList[i]);
                    ui32Result = decoder_PictureDisplay(psDecStrCtx,
                                                        GET_STREAM_PICTURE_ID(psBufCtrl->aui32DisplayList[i]),
                                                        bLastToDisplayForSeq);

                    IMG_ASSERT(ui32Result == IMG_SUCCESS);
                    if (ui32Result != IMG_SUCCESS)
                    {
                        return ui32Result;
                    }
                }
                else
                {
                    //In single core senario should not come here.
                    if(psDecStrCtx->psDecCtx->ui32NumCores == 1)
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                           "[USERSID=0x%08X] Failed to find decoded picture [TID = 0x%08X] to send for display",
                           psDecStrCtx->sConfig.ui32UserStrId, psBufCtrl->aui32DisplayList[i]);
                    }
                    else
                    {
                        //Mark as process failed only if multicore to wait for the required
                        //picture to come up. In a single core scenario this is an error
                        //so there is nothing to wait for, just process the picture. It adds
                        //error resilience
                        psDecodedPict->bProcessFailed = IMG_TRUE;
                    }
                }
            }

            // Release all unused pictures (firmware request)
            for (i = psDecodedPict->ui32ReleaseIdx;
                 i < psBufCtrl->ui32ReleaseListLength && !psDecodedPict->bProcessFailed;
                 i++,  psDecodedPict->ui32ReleaseIdx++)
            {
                psReleasePict = decoder_GetDecodedPict(psBufCtrl->aui32ReleaseList[i], &psDecStrCtx->sStrDecdPictList);
                if (psReleasePict)
                {
                    if (psReleasePict->bProcessed)
                    {
                        // If the decoded picture has been processed, destroy now.
                        ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psReleasePict, IMG_FALSE);
                        IMG_ASSERT(ui32Result == IMG_SUCCESS);
                        if (ui32Result != IMG_SUCCESS)
                        {
                            return ui32Result;
                        }
                    }
                    else
                    {
                        // If the decoded picture is not processed just destroy the containing picture.
                        ui32Result = decoder_PictureDestroy(psDecStrCtx,
                                                            GET_STREAM_PICTURE_ID(psBufCtrl->aui32ReleaseList[i]),
                                                            IMG_FALSE);
                        IMG_ASSERT(ui32Result == IMG_SUCCESS);
                        if (ui32Result != IMG_SUCCESS)
                        {
                            return ui32Result;
                        }
                        psReleasePict->psPicture = IMG_NULL;
                    }
                }
                else
                {
                    //In single core senario should not come here.
                    if(psDecStrCtx->psDecCtx->ui32NumCores == 1)
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                           "[USERSID=0x%08X] Failed to find decoded picture [TID = 0x%08X] to release",
                           psDecStrCtx->sConfig.ui32UserStrId, psBufCtrl->aui32ReleaseList[i]);
                    }
                    else
                    {
                        //Mark as process failed only if multicore to wait for the required
                        //picture to come up. In a single core scenario this is an error
                        //so there is nothing to wait for, just process the picture. It adds
                        //error resilience
                        psDecodedPict->bProcessFailed = IMG_TRUE;
                    }
                }
            }
        }
        else
#endif
        {
            // Always display the picture if we have no hardware
            DEBUG_REPORT(REPORT_MODULE_DECODER,
                "[USERSID=0x%08X] [TID=0x%08X] DISPLAY",
                psDecStrCtx->sConfig.ui32UserStrId,
                psDecodedPict->ui32TransactionId);
            ui32Result = decoder_PictureDisplay( psDecStrCtx, psDecodedPict->psPicture->ui32PictId, psDecodedPict->psPicture->bLastPictInSeq);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            // Always release the picture if we have no hardware
            ui32Result = decoder_PictureDestroy(psDecStrCtx, psDecodedPict->psPicture->ui32PictId, IMG_FALSE);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
            psDecodedPict->psPicture = IMG_NULL;
        }

        //If we have processed the current picture
        if (!psDecodedPict->bProcessFailed)
        {
            psDecodedPict->bProcessed = IMG_TRUE;

            //If the current picture has been released then remove the container from the decoded list
            if (psDecodedPict->psPicture == IMG_NULL)
            {
                // Only destroy the decoded picture once it is processed and the fw has instructed to release the picture.
                ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_FALSE);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }
                psDecodedPict = IMG_NULL;
            } //end if(psDecodedPict->psPicture == IMG_NULL)
        } //end if(!psDecodedPict->bProcessFailed)
    }//end for

    // Always clear the bProcessFailed flag to ensure that this picture will be processed on the next function call
    if (psDecodedPict != IMG_NULL)
    {
        psDecodedPict->bProcessFailed = IMG_FALSE;
    }

    /* Go through the list of decoded pictures to check if there are any pictures left for displaying
     * and that are still not displayed due to picture management errors. */
    /* NOTE: Do not apply to HEVC streams due to DPB overflow issues. */
    if (VDEC_STD_HEVC != psDecStrCtx->sConfig.eVidStd)
    {
        IMG_UINT32 ui32PictBufNum;
        IMG_UINT32 ui32DecPictNum = 0;
        IMG_UINT32 ui32RequiredPictNum = 0;
        DECODER_sDecodedPict * psAuxDecodedPict;
        DECODER_sDecodedPict * psDisplayDecodedPict = IMG_NULL;

        /* Get the minimum required number of picture buffers. */
        VDECDDUTILS_RefPictGetMaxNum(&psDecStrCtx->sConfig, psComSequHdrInfo, &ui32RequiredPictNum);
        ui32RequiredPictNum += (psComSequHdrInfo->bInterlacedFrames ? 2 : 1); // This gives minimum required buffers

        /* Get the number of currently available picture buffers. */
        psDecStrCtx->psDecCtx->pfnCompCallback(
                    DECODER_CB_GET_PICT_BUF_NUMBER,
                    IMG_NULL,
                    IMG_NULL,
                    psDecStrCtx->pvUserData,
                    &ui32PictBufNum);

        /* Start the procedure only if there is enough picture buffers registered. */
        if (ui32PictBufNum >= ui32RequiredPictNum)
        {
            /* Allow for one picture buffer for display. */
            ui32PictBufNum--;

            /* Count the number of decoded pictures that were not displayed yet. */
            psAuxDecodedPict = DQ_first(&psDecStrCtx->sStrDecdPictList);
            while (psAuxDecodedPict)
            {
                if(IMG_NULL != psAuxDecodedPict->psPicture)
                {
                    ui32DecPictNum++;
                    if(IMG_NULL == psDisplayDecodedPict)
                    {
                        psDisplayDecodedPict = psAuxDecodedPict;
                    }
                }
                if (psAuxDecodedPict != DQ_last(&psDecStrCtx->sStrDecdPictList))
                {
                    psAuxDecodedPict = DQ_next(psAuxDecodedPict);
                }
                else
                {
                    psAuxDecodedPict = IMG_NULL;
                }
            }

            /* If there is at least one not displayed picture... */
            if (psDisplayDecodedPict)
            {
                /* While the number of not displayed decoded pictures exceeds
                 * the number of maximum allowed number of pictures being held by VDEC... */
                while(ui32DecPictNum > ui32PictBufNum)
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
                        "[USERSID=0x%08X] Number of outstanding decoded pictures exceeded number of available pictures buffers.",
                        psDecStrCtx->sConfig.ui32UserStrId);

                    /* Find the picture with the least picture id. */
                    psAuxDecodedPict = DQ_next(psDisplayDecodedPict);
                    while (psAuxDecodedPict)
                    {
                        if (psAuxDecodedPict != DQ_last(&psDecStrCtx->sStrDecdPictList))
                        {
                            if((IMG_NULL != psAuxDecodedPict->psPicture) &&
                               (psAuxDecodedPict->psPicture->ui32PictId < psDisplayDecodedPict->psPicture->ui32PictId))
                            {
                                psDisplayDecodedPict = psAuxDecodedPict;
                            }
                            psAuxDecodedPict = DQ_next(psAuxDecodedPict);
                        }
                        else
                        {
                            if((IMG_NULL != psAuxDecodedPict->psPicture) &&
                               (psAuxDecodedPict->psPicture->ui32PictId < psDisplayDecodedPict->psPicture->ui32PictId))
                            {
                                psDisplayDecodedPict = psAuxDecodedPict;
                            }
                            psAuxDecodedPict = IMG_NULL;
                        }
                    }

                    /* Display and release the picture with the least picture id. */
                    DEBUG_REPORT(REPORT_MODULE_DECODER,
                        "[USERSID=0x%08X] [TID=0x%08X] DISPLAY FORCED",
                        psDecStrCtx->sConfig.ui32UserStrId,
                        psDisplayDecodedPict->ui32TransactionId);
                    ui32Result = decoder_PictureDisplay( psDecStrCtx, psDisplayDecodedPict->psPicture->ui32PictId, psDisplayDecodedPict->psPicture->bLastPictInSeq);
                    IMG_ASSERT(ui32Result == IMG_SUCCESS);
                    if (ui32Result != IMG_SUCCESS)
                    {
                        return ui32Result;
                    }

                    ui32Result = decoder_PictureDestroy(psDecStrCtx, psDisplayDecodedPict->psPicture->ui32PictId, IMG_FALSE);
                    IMG_ASSERT(ui32Result == IMG_SUCCESS);
                    if (ui32Result != IMG_SUCCESS)
                    {
                        return ui32Result;
                    }
                    psDisplayDecodedPict->psPicture = IMG_NULL;
                    psDisplayDecodedPict->bProcessed = IMG_TRUE;

                    ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDisplayDecodedPict, IMG_FALSE);
                    IMG_ASSERT(ui32Result == IMG_SUCCESS);
                    if (ui32Result != IMG_SUCCESS)
                    {
                        return ui32Result;
                    }
                    psDisplayDecodedPict = IMG_NULL;

                    /* Decrease the number of not displayed decoded pictures. */
                    ui32DecPictNum--;
                }
            }
        }
    }

    return IMG_SUCCESS;

error:
    return ui32Result;
}


static IMG_RESULT decoder_WrapBitStrSegments(
    LST_T *              psBitStrSegList,//VDECDD_sBitStrSeg
    LST_T *              psDecPictSegList,//DECODER_sDecPictSeg
    IMG_UINT32           ui32UserStrId)
{
    // Required for attaching segments to the decode picture
    BSPP_sBitStrSeg   * psBitStrSeg;
    DECODER_sDecPictSeg * psDecPictSeg;

    // Add the segments to the Decode Picture
    psBitStrSeg = LST_first(psBitStrSegList);
    while(psBitStrSeg)
    {
        VDEC_MALLOC(psDecPictSeg);
        IMG_ASSERT(psDecPictSeg);
        if (psDecPictSeg == IMG_NULL)
        {
            REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                "[USERSID=0x%08X] Failed to allocate memory for current picture's bitstream segments",
                ui32UserStrId);
            return IMG_ERROR_OUT_OF_MEMORY;
        }
        VDEC_BZERO(psDecPictSeg);

        psDecPictSeg->psBitStrSeg = psBitStrSeg;
        LST_add(psDecPictSegList,psDecPictSeg);

        psBitStrSeg = LST_next(psBitStrSeg);
    }

    return IMG_SUCCESS;
}

static IMG_VOID decoder_CleanBitStrSegments(
    LST_T *              psDecPictSegList)//DECODER_sDecPictSeg
{
    DECODER_sDecPictSeg * psDecPictSeg;

    while(IMG_NULL != (psDecPictSeg = LST_removeHead(psDecPictSegList)))
    {
        IMG_FREE(psDecPictSeg);
    }
}

/*!
******************************************************************************

 @Function              decoder_PictureDecode

******************************************************************************/
static IMG_RESULT
decoder_PictureDecode(
    DECODER_sCoreContext *  psDecCoreCtx,
    DECODER_sStrContext *   psDecStrCtx,
    VDECDD_sStrUnit *       psStrUnit,
    DECODER_sDecPict **     ppsDecPict
)
{
    VDECDD_sPicture     * psPicture = psStrUnit->pvDdPictData;
    DECODER_sDecPict    * psDecPict;
    IMG_RESULT            ui32Result = IMG_SUCCESS;

    // Ensure this is a new picture.
    IMG_ASSERT(psDecStrCtx->psCurrentPicture == IMG_NULL);
    IMG_ASSERT(psStrUnit->eStrUnitType == VDECDD_STRUNIT_PICTURE_START);

    psDecCoreCtx->ui32CumulativePics++;

    // Allocate a unique id to the picture.
    ui32Result = IDGEN_AllocId(psDecStrCtx->hPictIdGen, psPicture, &psPicture->ui32PictId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Allocate the decoded picture information structure. */
    VDEC_MALLOC(psPicture->psDecPictInfo);
    IMG_ASSERT(psPicture->psDecPictInfo);
    if (psPicture->psDecPictInfo == IMG_NULL)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "[USERSID=0x%08X] Failed to allocate memory for decoded picture information",
            psDecStrCtx->sConfig.ui32UserStrId);
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psPicture->psDecPictInfo);

    // Extract decoded information from the stream unit.
    psPicture->psDecPictInfo->ui32ErrorFlags = psStrUnit->ui32ErrorFlags;
    psPicture->psDecPictInfo->sFirstFieldTagContainer.pvPictTagParam = psStrUnit->pvStrUnitTag;
    psPicture->psDecPictInfo->sOutputConfig  = psPicture->sOutputConfig;
    psPicture->psDecPictInfo->sRendInfo      = psPicture->sDisplayPictBuf.sRendInfo;
    psPicture->psDecPictInfo->sDispInfo      = psStrUnit->psPictHdrInfo->sDispInfo;

    // Extract aux picture information from the stream unit.
    psPicture->sDecPictAuxInfo.ui32SequenceHdrId = psStrUnit->psSequHdrInfo->ui32SequHdrId;
    psPicture->sDecPictAuxInfo.ui32PPSId         = psStrUnit->psPictHdrInfo->sPictAuxData.ui32Id;
    psPicture->sDecPictAuxInfo.ui32SecondPPSId   = psStrUnit->psPictHdrInfo->sSecondPictAuxData.ui32Id;

    // Create a new decoder picture container.
    VDEC_MALLOC(psDecPict);
    IMG_ASSERT(psDecPict);
    if (psDecPict == IMG_NULL)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "[USERSID=0x%08X] Failed to allocate memory for decode picture",
            psDecStrCtx->sConfig.ui32UserStrId);
        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto error_dec_pict;
    }
    VDEC_BZERO(psDecPict);

    // Attach decoder/picture context information.
    psDecPict->psDecStrCtx = psDecStrCtx;
    psDecPict->ui8Pipe = psDecStrCtx->ui8Pipe;

    // Construct the transaction Id.
    // This consists of stream and core number in addition to picture number in stream
    // and a 4-bit value representing the picture number in core.
    psDecPict->ui32TransactionId = CREATE_TRANSACTION_ID(psDecCoreCtx->ui32CoreNum,
                                                         psDecStrCtx->ui32StrId,
                                                         psDecCoreCtx->ui32CumulativePics,
                                                         psPicture->ui32PictId);

    // Add picture to core decode list
    psDecStrCtx->sDecStrStatus.ui32NumPictDecoding++;

    // Fake a FW message to process when decoded.
    VDEC_MALLOC(psDecPict->psFirstFieldFwMsg);
    IMG_ASSERT(psDecPict->psFirstFieldFwMsg);
    if (psDecPict->psFirstFieldFwMsg == IMG_NULL)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "[USERSID=0x%08X] Failed to allocate memory for firmware message for decoded picture",
            psDecStrCtx->sConfig.ui32UserStrId);
        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto error_fw_msg;
    }
    VDEC_BZERO(psDecPict->psFirstFieldFwMsg);

    VDEC_MALLOC(psDecPict->psSecondFieldFwMsg);
    IMG_ASSERT(psDecPict->psSecondFieldFwMsg);
    if (psDecPict->psSecondFieldFwMsg == IMG_NULL)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "[USERSID=0x%08X] Failed to allocate memory for firmware message for decoded picture",
            psDecStrCtx->sConfig.ui32UserStrId);
        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto error_fw_msg;
    }
    VDEC_BZERO(psDecPict->psSecondFieldFwMsg);

    // Add the segments to the Decode Picture
    ui32Result = decoder_WrapBitStrSegments(&psStrUnit->sBitStrSegList,
                               &psDecPict->sDecPictSegList,
                               psDecStrCtx->sConfig.ui32UserStrId);

    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_segments;
    }

    // Shuffle the current and previous
    // Hold a reference to the last context on the FE
    if (psDecStrCtx->psPrevFePictDecRes)
    {
        // Return previous last FW context.
        RESOURCE_ItemReturn(&psDecStrCtx->psPrevFePictDecRes->ui32RefCount);

#ifndef IMG_KERNEL_MODULE
        if(RESOURCE_ItemIsAvailable(&psDecStrCtx->psPrevFePictDecRes->ui32RefCount))
        {
            RESOURCE_ListRemove(&psDecStrCtx->sDecResList, psDecStrCtx->psPrevFePictDecRes);
            RESOURCE_ListAdd(&psDecStrCtx->sDecResList, psDecStrCtx->psPrevFePictDecRes, 0, &psDecStrCtx->psPrevFePictDecRes->ui32RefCount);
        }
#endif
    }

    psDecStrCtx->psPrevFePictDecRes = psDecStrCtx->psCurFePictDecRes;
    psDecPict->psPrevPictDecRes = psDecStrCtx->psPrevFePictDecRes;

    // Get a new stream decode resource bundle for current picture.
    psDecPict->psCurPictDecRes = RESOURCE_ListGetAvail(&psDecStrCtx->sDecResList);
    IMG_ASSERT(psDecPict->psCurPictDecRes);
    if (psDecPict->psCurPictDecRes == IMG_NULL)
    {
        ui32Result = IMG_ERROR_UNEXPECTED_STATE;
        goto error_dec_res;
    }

#ifdef HAS_H264
    if (VDEC_STD_H264 == psDecStrCtx->sConfig.eVidStd)
    {
        // Copy any SGM for current picture.
        if (psStrUnit->psPictHdrInfo->sPictSgmData.ui32Id != BSPP_INVALID)
        {
            IMG_ASSERT(psStrUnit->psPictHdrInfo->sPictSgmData.ui32Size <= psDecPict->psCurPictDecRes->sH264SgmBuf.ui32BufSize);
            //Updated in translation_api
            IMG_MEMCPY(psDecPict->psCurPictDecRes->sH264SgmBuf.pvCpuVirt,
                psStrUnit->psPictHdrInfo->sPictSgmData.pvData,
                psStrUnit->psPictHdrInfo->sPictSgmData.ui32Size);
        }
    }
#endif /* HAS_H264 */

    psDecPict->psCurPictDecRes->ui32TransactionId = psDecPict->ui32TransactionId;
    psDecStrCtx->psCurFePictDecRes = psDecPict->psCurPictDecRes;
    RESOURCE_ItemUse(&psDecStrCtx->psCurFePictDecRes->ui32RefCount);

    // Get a new control buffer.
    psDecPict->psPictRefRes = RESOURCE_ListGetAvail(&psDecStrCtx->sRefResList);
    IMG_ASSERT(psDecPict->psPictRefRes);
    if (psDecPict->psPictRefRes == IMG_NULL)
    {
        ui32Result = IMG_ERROR_UNEXPECTED_STATE;
        goto error_ref_res;
    }


#ifdef VDEC_USE_PVDEC
    psDecPict->psStrPtdBufInfo = &psDecStrCtx->sPtdBufInfo;
#else
    psDecPict->psStrPtdBufInfo = &psDecStrCtx->psDecCtx->sPtdBufInfo;
#endif

#ifdef VDEC_USE_PVDEC
    psDecPict->psStrPvdecFwCtxBuf = &psDecStrCtx->sPvdecFwCtxBuf;
#endif
    psDecPict->psPictHdrInfo = psStrUnit->psPictHdrInfo;

    // Provide ID of sync pictures when multiple cores are available.
    if (psDecStrCtx->psDecCtx->ui32NumCores > 1)
    {
        // Picture must always synchronise on front-end with previous from same stream.
        psDecPict->ui32FeSyncTransactionId = psDecStrCtx->ui32LastFeTransactionId;

        // Synchronisation on back-end is only required when used for reference.
        // Since this calculation is quite involved this initial implementation will
        // assume that every picture is dependent on the previous.
        psDecPict->ui32BeSyncTransactionId = psDecStrCtx->ui32LastFeTransactionId;
    }

    // Take the WDT period configured for the device.
    psDecPict->ui32FeWdtPeriod = psDecStrCtx->psDecCtx->psDevConfig->ui32FeWdtPeriod;
    psDecPict->ui32BeWdtPeriod = psDecStrCtx->psDecCtx->psDevConfig->ui32BeWdtPeriod;
    psDecPict->ui32PSRWdtPeriod = psDecStrCtx->psDecCtx->psDevConfig->ui32PSRWdtPeriod;

    // Obtain (core) resources for the picture.
    ui32Result = RESOURCE_PictureAttach(
        &psDecCoreCtx->hResources,
        psDecStrCtx->sConfig.eVidStd,
        psDecPict);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_res_attach;
    }

#ifndef IMG_KERNEL_MODULE
    if(psDecCoreCtx->sLasRes.bInit)
    {
           // If two consecutive pictures use the same output buffer and we want to dump the output at the pdump.
        if( (((psDecPict->psAltPict != IMG_NULL && psDecCoreCtx->sLasRes.hAltPict == psDecPict->psAltPict) ||
              (psDecPict->psReconPict != IMG_NULL && psDecCoreCtx->sLasRes.hReconPict == psDecPict->psReconPict))
              && psDecCoreCtx->psDecCtx->psDevConfig->bPdumpAndRes) ||
           (psDecPict->psHdrInfo != IMG_NULL && psDecCoreCtx->sLasRes.hHdrInfo == psDecPict->psHdrInfo) ||
           (psDecPict->psBatchMsgInfo != IMG_NULL && psDecCoreCtx->sLasRes.hBatchMsgInfo == psDecPict->psBatchMsgInfo) ||
           (psDecPict->psTransactionInfo != IMG_NULL && psDecCoreCtx->sLasRes.hTransactionInfo == psDecPict->psTransactionInfo) ||
           (psDecPict->psPictHdrInfo != IMG_NULL && psDecCoreCtx->sLasRes.hPictHdrInfo == psDecPict->psPictHdrInfo) ||
           (psDecPict->psPictRefRes != IMG_NULL && psDecCoreCtx->sLasRes.hPictRefRes == psDecPict->psPictRefRes) ||
           // If the context buffer which the previous picture will load from is the same as this one will save into
           (psDecPict->psCurPictDecRes != IMG_NULL && psDecCoreCtx->sLasRes.hPrevPictDecRes == psDecPict->psCurPictDecRes))
        {

            // Sync pdump contexts if two consecutive pictures share a resource. This is because if we don't the script
            // may try to schedule them together for decoding.
            HWCTRL_SyncPDumpContexts(psDecCoreCtx->hHwCtx);
        }
    }

    psDecCoreCtx->sLasRes.bInit = IMG_TRUE;
    psDecCoreCtx->sLasRes.hAltPict = psDecPict->psAltPict;
    psDecCoreCtx->sLasRes.hReconPict = psDecPict->psReconPict;
    psDecCoreCtx->sLasRes.hHdrInfo = psDecPict->psHdrInfo;
    psDecCoreCtx->sLasRes.hBatchMsgInfo = psDecPict->psBatchMsgInfo;
    psDecCoreCtx->sLasRes.hTransactionInfo = psDecPict->psTransactionInfo;
    psDecCoreCtx->sLasRes.hPictHdrInfo = psDecPict->psPictHdrInfo;
    psDecCoreCtx->sLasRes.hPictRefRes = psDecPict->psPictRefRes;
    psDecCoreCtx->sLasRes.hPrevPictDecRes = psDecPict->psPrevPictDecRes;
#endif
    // Clear fw context data for re-use.
    IMG_MEMSET(psDecPict->psCurPictDecRes->sFwCtxBuf.pvCpuVirt, 0, psDecPict->psCurPictDecRes->sFwCtxBuf.ui32BufSize);
    UPDATE_DEVICE((&psDecPict->psCurPictDecRes->sFwCtxBuf), !decoder_IsFakeMTX(psDecStrCtx->psDecCtx, psDecCoreCtx->ui32CoreNum));

    // Clear the control data in case the picture is discarded before being prepared by firmware.
    IMG_MEMSET(psDecPict->psPictRefRes->sFwCtrlBuf.pvCpuVirt, 0, psDecPict->psPictRefRes->sFwCtrlBuf.ui32BufSize);
    UPDATE_DEVICE(&psDecPict->psPictRefRes->sFwCtrlBuf, !decoder_IsFakeMTX(psDecStrCtx->psDecCtx, psDecCoreCtx->ui32CoreNum));

    // Translate all the host data into a native and optimal firmware representation.
#ifdef VDEC_USE_PVDEC
    {
        DECODER_sRegsOffsets sRegsOffsets = { 0 };

        ui32Result = HWCTRL_GetRegsOffsets(psDecCoreCtx->hHwCtx, &sRegsOffsets);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error_other;
        }

        ui32Result = TRANSLATION_CtrlAllocPrepare(
                        &psDecStrCtx->sConfig,
                        psStrUnit,
                        psDecPict,
                        &psDecCoreCtx->sCoreProps,
                        decoder_IsFakeMTX(psDecStrCtx->psDecCtx, psDecCoreCtx->ui32CoreNum),
                        &sRegsOffsets);
    }
#else /* ndef VDEC_USE_PVDEC */
    ui32Result = TRANSLATION_PicturePrepare(
                    psDecStrCtx->ui32StrId,
                    &psDecStrCtx->sConfig,
                    psStrUnit,
                    psDecPict,
                    &psDecCoreCtx->sCoreProps,
                    decoder_IsFakeMTX(psDecStrCtx->psDecCtx, psDecCoreCtx->ui32CoreNum));
#endif /* ndef VDEC_USE_PVDEC */

    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_other;
    }

    // This particular core might have gone into APM, so make sure we resume before proceeding.
    if(psDecCoreCtx->bAPM)
    {
        DMANKM_ResumeDevice(psDecCoreCtx->psDecCtx->hDevHandle, IMG_TRUE);
        psDecCoreCtx->bAPM = IMG_FALSE;
    }

    if(psDecStrCtx->sConfig.bLowLatencyMode)
    {
        // Submit picture for decoding.
        ui32Result = HWCTRL_PictureSubmit(
                        psDecCoreCtx->hHwCtx,
                        psDecPict);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error_other;
        }

        /* Submit the bitstream segments */
        ui32Result = HWCTRL_PictureSubmitFragment(
                        psDecCoreCtx->hHwCtx,
                        &psDecPict->sDecPictSegList);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error_other;
        }
    }
    else
    {
        ui32Result = HWCTRL_PictureSubmitBatch(
                        psDecCoreCtx->hHwCtx,
                        psDecPict,
                        psDecCoreCtx->hResources,
                        &psDecCoreCtx->psDecCtx->sPtdInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if(ui32Result != IMG_SUCCESS)
        {
            goto error_other;
        }
    }

    IMG_ASSERT(psDecCoreCtx->bBusy == IMG_FALSE);
    psDecCoreCtx->bBusy = IMG_TRUE;
    // Store this transaction ID in stream context.
    //if ()
    {
        psDecStrCtx->ui32LastFeTransactionId = psDecPict->ui32TransactionId;
        psDecStrCtx->psCurrentPicture = psDecPict;
    }

    psDecStrCtx->sDecStrStatus.ui32Features = psStrUnit->ui32Features;

    *ppsDecPict = psDecPict;

    return IMG_SUCCESS;

    /* Roll back in case of errors. */
error_other:
    RESOURCE_PictureDetach(&psDecCoreCtx->hResources, psDecPict);
error_res_attach:
error_ref_res:
error_dec_res:
error_segments:
    decoder_CleanBitStrSegments(&psDecPict->sDecPictSegList);
    IMG_FREE(psDecPict->psFirstFieldFwMsg);
    IMG_FREE(psDecPict->psSecondFieldFwMsg);
error_fw_msg:
    IMG_FREE(psDecPict);
error_dec_pict:
    IMG_FREE(psPicture->psDecPictInfo);

    return ui32Result;
}

/*!
******************************************************************************

 @Function              decoder_PictureSubmitMoreData

******************************************************************************/
static IMG_RESULT
decoder_PictureSubmitMoreData(
        DECODER_sStrContext *   psDecStrCtx,
        VDECDD_sStrUnit *       psStrUnit
)
{
    VDECDD_sPicture     * psPicture = IMG_NULL;
    IMG_RESULT            ui32Result;

    // Required for attaching segments to the decode picture
    DECODER_sDecPict    * psDecPict;
    DECODER_sCoreContext* psDecCoreCtx;

    IMG_ASSERT(psStrUnit->eStrUnitType == VDECDD_STRUNIT_PICTURE_FRAG);

    // Get pointer to appropriate VDECDD_sPicture via picture id
    {
        ui32Result = IDGEN_GetHandle(psDecStrCtx->hPictIdGen,
                                     GET_STREAM_PICTURE_ID(psDecStrCtx->ui32LastFeTransactionId),
                                     (IMG_VOID **) &psPicture);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        IMG_ASSERT(psPicture != IMG_NULL);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
        if (psPicture == IMG_NULL)
        {
            REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                "[USERSID=0x%08X] Unable to find current picture from transaction ID",
                psDecStrCtx->sConfig.ui32UserStrId);
            return IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE;
        }
    }

    // Update error flags
    psPicture->psDecPictInfo->ui32ErrorFlags |= psStrUnit->ui32ErrorFlags;

    // Get the core handle
    psDecCoreCtx = decoder_CoreGetContext(psDecStrCtx->psDecCtx,
                                          GET_CORE_ID(psDecStrCtx->ui32LastFeTransactionId));
    IMG_ASSERT(psDecCoreCtx != IMG_NULL);
    if (psDecCoreCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
               "[USERSID=0x%08X] Unable to obtain core context from last front-end transaction ID",
               psDecStrCtx->sConfig.ui32UserStrId);
        return IMG_ERROR_FATAL;
    }

    ui32Result = HWCTRL_GetPicPendPictList(psDecCoreCtx->hHwCtx,
                                           psDecStrCtx->ui32LastFeTransactionId,
                                           &psDecPict);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    // Add the segments to the Decode Picture
    ui32Result = decoder_WrapBitStrSegments(&psStrUnit->sBitStrSegList,
                                            &psDecPict->sDecPictSegList,
                                            psDecStrCtx->sConfig.ui32UserStrId);

    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_segments;
    }

    // Submit picture for decoding.
    ui32Result = HWCTRL_PictureSubmitFragment(psDecCoreCtx->hHwCtx, &psDecPict->sDecPictSegList);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    return IMG_SUCCESS;
error_segments:
    decoder_CleanBitStrSegments(&psDecPict->sDecPictSegList);
    return ui32Result;
}


/*!
******************************************************************************

 @Function              decoder_KickListService

******************************************************************************/
static IMG_RESULT
decoder_KickListService(
        DECODER_sStrContext *   psDecStrCtx,
        VDECDD_sStrUnit *       psStrUnit
)
{
    IMG_RESULT             ui32Result;
    DECODER_sCoreContext * psCoreCtx;

    psCoreCtx = decoder_CoreGetContext(psDecStrCtx->psDecCtx, GET_CORE_ID(psDecStrCtx->ui32LastFeTransactionId));
    IMG_ASSERT(psCoreCtx != IMG_NULL);
    if(psCoreCtx == IMG_NULL)
    {
        return IMG_ERROR_FATAL;
    }
    // Kick SW Interrupt
    ui32Result = HWCTRL_KickSwInterrupt(psCoreCtx->hHwCtx, (IMG_HANDLE)psDecStrCtx);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              decoder_PictureFinalize

******************************************************************************/
static IMG_RESULT
decoder_PictureFinalize(
        DECODER_sStrContext *   psDecStrCtx,
        VDECDD_sStrUnit *       psStrUnit
)
{
    VDECDD_sPicture      * psPicture = IMG_NULL;
    IMG_RESULT             ui32Result;
    DECODER_sDecPict     * psDecPict = psDecStrCtx->psCurrentPicture;
    DECODER_sCoreContext * psDecCoreCtx = IMG_NULL;

    IMG_ASSERT(psStrUnit->eStrUnitType == VDECDD_STRUNIT_PICTURE_END);
    IMG_ASSERT(psDecPict);
    if (IMG_NULL == psDecPict)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
               "[USERSID=0x%08X] Unable to get the current picture from Decoder context",
               psDecStrCtx->sConfig.ui32UserStrId);
        return IMG_ERROR_GENERIC_FAILURE;
    }

    // Get pointer to appropriate VDECDD_sPicture via picture id
    ui32Result = IDGEN_GetHandle(psDecStrCtx->hPictIdGen,
                                 GET_STREAM_PICTURE_ID(psDecStrCtx->ui32LastFeTransactionId),
                                 (IMG_VOID **) &psPicture);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    IMG_ASSERT(psPicture != IMG_NULL);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }
    if (psPicture == IMG_NULL)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "[USERSID=0x%08X] Unable to find current picture from transaction ID",
            psDecStrCtx->sConfig.ui32UserStrId);
        return IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE;
    }

    // Update error flags
    psPicture->psDecPictInfo->ui32ErrorFlags |= psStrUnit->ui32ErrorFlags;

    psDecCoreCtx = decoder_CoreGetContext(psDecStrCtx->psDecCtx, GET_CORE_ID(psDecStrCtx->ui32LastFeTransactionId));
    IMG_ASSERT(psDecCoreCtx != IMG_NULL);
    if (psDecCoreCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
               "[USERSID=0x%08X] Unable to obtain core context from last front-end transaction ID",
               psDecStrCtx->sConfig.ui32UserStrId);
        return IMG_ERROR_GENERIC_FAILURE;
    }

    // Submit end bytes
    ui32Result = HWCTRL_CoreSendEndBytes(
                    psDecCoreCtx->hHwCtx,
                    psDecPict->psEndBytesBufInfo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    IMG_ASSERT(psDecCoreCtx->bBusy == IMG_TRUE);
    psDecCoreCtx->bBusy = IMG_FALSE;

    // Picture data are now complete, nullify pointer
    psDecStrCtx->psCurrentPicture = IMG_NULL;

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              decoder_StreamGetContext

 @Description

 This function returns the stream context structure for the given stream handle.

 @Return    DECODER_sStrContext : This function returns a pointer to the stream
                                   context structure or IMG_NULL if not found.

******************************************************************************/
static DECODER_sStrContext *
decoder_StreamGetContext(
    IMG_HANDLE hDecStrCtx
)
{
    return (DECODER_sStrContext *)hDecStrCtx;
}



/*!
******************************************************************************

 @Function              decoder_StreamFlush

 @Description

 Flush all display images from reference picture list and release all
 references held (if requested). Firmware stream context destroyed?

******************************************************************************/
static IMG_RESULT
decoder_StreamFlush(
    DECODER_sStrContext *   psDecStrCtx,
    IMG_BOOL                bDiscardRefs
)
{
    DECODER_sDecStrUnit     * psDecStrUnit;
    DECODER_sDecodedPict    * psDecodedPict;
    IMG_RESULT                ui32Result;

    // Since the stream should be stopped before flushing
    // there should be no pictures in the stream list.
    psDecStrUnit = LST_first(&psDecStrCtx->sPendStrUnitList);
    while (psDecStrUnit)
    {
        IMG_ASSERT(psDecStrUnit->psStrUnit->eStrUnitType != VDECDD_STRUNIT_PICTURE_START);
        psDecStrUnit = LST_next(psDecStrUnit);
    }

    psDecodedPict = DQ_last(&psDecStrCtx->sStrDecdPictList);

#ifdef VDEC_MSVDX_HARDWARE
    if (psDecStrCtx->psDecCtx->psDevConfig->eDecodeLevel > VDECDD_DECODELEVEL_DECODER)
    {
        // Get oldest reference to display.
        psDecodedPict = DQ_last(&psDecStrCtx->sStrDecdPictList);

        if (psDecodedPict)
        {
            switch(psDecStrCtx->sConfig.eVidStd)
            {
#ifdef HAS_AVS
            case VDEC_STD_AVS:
            {
                AVSFW_sContextData   * psCtxData = (AVSFW_sContextData *)psDecStrCtx->psLastBePictDecRes->sFwCtxBuf.pvCpuVirt;
                DECODER_sDecodedPict * psDisplayPict;

                // Update the fw context for analysing the dpb in order to display or release any outstanding picture
                UPDATE_HOST((&psDecStrCtx->psLastBePictDecRes->sFwCtxBuf), !decoder_IsFakeMTX(psDecStrCtx->psDecCtx, 0));   //If core 0 is fake, all are fake

                if(psCtxData->sNewRefPic.ui32TransId && (!psCtxData->sNewRefPic.bSentForDisplay) )
                {
                    DEBUG_REPORT(REPORT_MODULE_DECODER,
                        "[TID=0x%08X] DISPLAY", psCtxData->sNewRefPic.ui32TransId);

                    psDisplayPict = decoder_GetDecodedPict(psCtxData->sNewRefPic.ui32TransId, &psDecStrCtx->sStrDecdPictList);
                    if (psDisplayPict && psDisplayPict->psPicture && psDisplayPict->psPicture->psDecPictInfo)
                    {
                        if (FLAG_IS_SET((psCtxData->sNewRefPic.ui8DisplayFlags), VDECFW_BUFFLAG_DISPLAY_FIELD_CODED))
                        {
                            if ( !FLAG_IS_SET((psCtxData->sNewRefPic.ui8DisplayFlags), VDECFW_BUFFLAG_DISPLAY_SINGLE_FIELD) )
                            {
                                psDisplayPict->psPicture->psDecPictInfo->eBufferType = IMG_BUFFERTYPE_PAIR;
                            }
                            else
                            {
                                psDisplayPict->psPicture->psDecPictInfo->eBufferType =
                                    FLAG_IS_SET((psCtxData->sNewRefPic.ui8DisplayFlags), VDECFW_BUFFLAG_DISPLAY_BOTTOM_FIELD)
                                        ? IMG_BUFFERTYPE_FIELD_BOTTOM : IMG_BUFFERTYPE_FIELD_TOP;
                            }
                        }
                        else
                        {
                            psDisplayPict->psPicture->psDecPictInfo->eBufferType = IMG_BUFFERTYPE_FRAME;
                        }
                    }
                    else
                    {
                        IMG_ASSERT(IMG_FALSE);
                    }

                    ui32Result = decoder_PictureDisplay(psDecStrCtx,
                                                        GET_STREAM_PICTURE_ID(psCtxData->sNewRefPic.ui32TransId),
                                                        IMG_TRUE);
                    IMG_ASSERT(ui32Result == IMG_SUCCESS);
                    if (ui32Result != IMG_SUCCESS)
                    {
                        return ui32Result;
                    }
                }
                if (bDiscardRefs)
                {
                    IMG_UINT32 ui32i;
                    IMG_UINT32 aui32PicIdsToDestroy[] = { psCtxData->sNewRefPic.ui32TransId,
                                                          psCtxData->sOldRefPic.ui32TransId, };

                    for (ui32i = 0; ui32i < sizeof(aui32PicIdsToDestroy)/sizeof(IMG_UINT32); ui32i++)
                    {
                        if(aui32PicIdsToDestroy[ui32i])
                        {
                            psDecodedPict = decoder_GetDecodedPict(aui32PicIdsToDestroy[ui32i],
                                    &psDecStrCtx->sStrDecdPictList);
                            if (psDecodedPict)
                            {
                                ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_FALSE);
                                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                                if (ui32Result != IMG_SUCCESS)
                                {
                                    return ui32Result;
                                }
                            }
                        }
                    }

                    psCtxData->sNewRefPic.ui32TransId  = 0;
                    psCtxData->sOldRefPic.ui32TransId  = 0;
                }
                break;
            }
#endif /* HAS_AVS */
#ifdef HAS_H264
                case VDEC_STD_H264:
                {
                    H264FW_sContextData * psCtxData = (H264FW_sContextData *)psDecStrCtx->psLastBePictDecRes->sFwCtxBuf.pvCpuVirt;
                    IMG_BOOL bFound = IMG_TRUE;
                    IMG_UINT32 i;
                    IMG_INT32  i32MinCount;
                    IMG_UINT32 ui32MinCountIdx;
                    IMG_UINT32 ui32NumDisplayPics = 0;
                    IMG_UINT32 ui32NumPicsDisplayed = 0;
                    DECODER_sDecodedPict* psDisplayPict = IMG_NULL;

                    // Update the fw context for analysing the dpb in order to display or release any outstanding picture
                    UPDATE_HOST((&psDecStrCtx->psLastBePictDecRes->sFwCtxBuf), !decoder_IsFakeMTX(psDecStrCtx->psDecCtx, 0));   //If core 0 is fake, all are fake

                    // Determine how many display pictures reside in the DPB.
                    if (psCtxData->ui32DpbSize > H264FW_MAX_DPB_SIZE)
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                            "[USERSID=0x%08X] Incorrect DPB size: %d",
                            psDecStrCtx->sConfig.ui32UserStrId, psCtxData->ui32DpbSize);
                        psCtxData->ui32DpbSize = H264FW_MAX_DPB_SIZE;
                    }

                    for (i = 0; i < psCtxData->ui32DpbSize; i++)
                    {
                        if (psCtxData->asDpb[i].ui32TransactionId)
                        {
                            if (psCtxData->asDpb[i].bNeededForOutput)
                            {
                                ui32NumDisplayPics++;
                            }
                        }
                    }

                    // Check for picture stuck outside the dpb
                    if (psCtxData->asLastDisplayedPicData[0].ui32TransactionId)
                    {
                        DEBUG_REPORT(REPORT_MODULE_DECODER,
                            "[USERSID=0x%08X] [TID=0x%08X] DISPLAY",
                            psDecStrCtx->sConfig.ui32UserStrId,
                            psCtxData->asLastDisplayedPicData[0].ui32TransactionId);
                        IMG_ASSERT(psCtxData->asLastDisplayedPicData[0].ui32TransactionId != 0xffffffff);

                        psDisplayPict = decoder_GetDecodedPict(psCtxData->asLastDisplayedPicData[0].ui32TransactionId,
                                                               &psDecStrCtx->sStrDecdPictList);

                        if (psDisplayPict && psDisplayPict->psPicture && psDisplayPict->psPicture->psDecPictInfo)
                        {
                            if (FLAG_IS_SET((psCtxData->ui8PrevDisplayFlags), VDECFW_BUFFLAG_DISPLAY_FIELD_CODED))
                            {
                                if ( !FLAG_IS_SET((psCtxData->ui8PrevDisplayFlags), VDECFW_BUFFLAG_DISPLAY_SINGLE_FIELD) )
                                {
                                    psDisplayPict->psPicture->psDecPictInfo->eBufferType = IMG_BUFFERTYPE_PAIR;
                                }
                                else
                                {
                                    psDisplayPict->psPicture->psDecPictInfo->eBufferType =
                                        FLAG_IS_SET((psCtxData->ui8PrevDisplayFlags), VDECFW_BUFFLAG_DISPLAY_BOTTOM_FIELD)
                                            ? IMG_BUFFERTYPE_FIELD_BOTTOM : IMG_BUFFERTYPE_FIELD_TOP;
                                }
                            }
                            else
                            {
                                psDisplayPict->psPicture->psDecPictInfo->eBufferType = IMG_BUFFERTYPE_FRAME;
                            }

                        }
                        else
                        {
                            IMG_ASSERT(psDisplayPict);
                            IMG_ASSERT(psDisplayPict && psDisplayPict->psPicture);
                            IMG_ASSERT(psDisplayPict && psDisplayPict->psPicture && psDisplayPict->psPicture->psDecPictInfo);
                        }

                        ui32Result = decoder_PictureDisplay(psDecStrCtx,GET_STREAM_PICTURE_ID(psCtxData->asLastDisplayedPicData[0].ui32TransactionId), IMG_TRUE);
                        IMG_ASSERT(ui32Result == IMG_SUCCESS);
                        if (ui32Result != IMG_SUCCESS)
                        {
                            return ui32Result;
                        }
                    }

                    while (bFound)
                    {
                        i32MinCount = ((IMG_UINT32)(1 << 31)) - 1;
                        ui32MinCountIdx = -1;
                        bFound = IMG_FALSE;

                        // Loop over the DPB to find the first in order
                        for (i = 0; i < psCtxData->ui32DpbSize; i++)
                        {
                            if (psCtxData->asDpb[i].ui32TransactionId)
                            {
                                if ( psCtxData->asDpb[i].bNeededForOutput || bDiscardRefs )
                                {
                                    if (psCtxData->asDpb[i].i32TopFieldOrderCount < i32MinCount)
                                    {
                                        i32MinCount = psCtxData->asDpb[i].i32TopFieldOrderCount;
                                        ui32MinCountIdx = i;
                                        bFound = IMG_TRUE;
                                    }
                                }
                            }
                        }

                        if (bFound)
                        {
                            if (psCtxData->asDpb[ui32MinCountIdx].bNeededForOutput)
                            {
                                DEBUG_REPORT(REPORT_MODULE_DECODER,
                                    "[USERSID=0x%08X] [TID=0x%08X] DISPLAY",
                                    psDecStrCtx->sConfig.ui32UserStrId,
                                    psCtxData->asDpb[ui32MinCountIdx].ui32TransactionId);
                                IMG_ASSERT(psCtxData->asDpb[ui32MinCountIdx].ui32TransactionId != 0xffffffff);

                                psDisplayPict = decoder_GetDecodedPict(psCtxData->asDpb[ui32MinCountIdx].ui32TransactionId,
                                                                       &psDecStrCtx->sStrDecdPictList);

                                if (psDisplayPict && psDisplayPict->psPicture && psDisplayPict->psPicture->psDecPictInfo)
                                {
                                    if (FLAG_IS_SET((psCtxData->asDpb[ui32MinCountIdx].ui8DisplayFlags), VDECFW_BUFFLAG_DISPLAY_FIELD_CODED))
                                    {
                                        if (!FLAG_IS_SET((psCtxData->asDpb[ui32MinCountIdx].ui8DisplayFlags), VDECFW_BUFFLAG_DISPLAY_SINGLE_FIELD))
                                        {
                                            psDisplayPict->psPicture->psDecPictInfo->eBufferType = IMG_BUFFERTYPE_PAIR;
                                        }
                                        else
                                        {
                                            psDisplayPict->psPicture->psDecPictInfo->eBufferType =
                                                FLAG_IS_SET((psCtxData->asDpb[ui32MinCountIdx].ui8DisplayFlags), VDECFW_BUFFLAG_DISPLAY_BOTTOM_FIELD)
                                                    ? IMG_BUFFERTYPE_FIELD_BOTTOM : IMG_BUFFERTYPE_FIELD_TOP;
                                        }
                                    }
                                    else
                                    {
                                        psDisplayPict->psPicture->psDecPictInfo->eBufferType = IMG_BUFFERTYPE_FRAME;
                                    }

                                    psDisplayPict->psPicture->psDecPictInfo->ui16ViewID = psCtxData->asDpb[ui32MinCountIdx].ui16ViewId;
                                }
                                else
                                {
                                    IMG_ASSERT(psDisplayPict);
                                    IMG_ASSERT(psDisplayPict && psDisplayPict->psPicture);
                                    IMG_ASSERT(psDisplayPict && psDisplayPict->psPicture && psDisplayPict->psPicture->psDecPictInfo);
                                }

                                ui32NumPicsDisplayed++;
                                ui32Result = decoder_PictureDisplay(psDecStrCtx,
                                                                    GET_STREAM_PICTURE_ID(psCtxData->asDpb[ui32MinCountIdx].ui32TransactionId),
                                                                    (ui32NumPicsDisplayed == ui32NumDisplayPics) ? IMG_TRUE : IMG_FALSE);
                                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                                if (ui32Result != IMG_SUCCESS)
                                {
                                    return ui32Result;
                                }
                                psCtxData->asDpb[ui32MinCountIdx].bNeededForOutput = IMG_FALSE;
                            }

                            if (bDiscardRefs)
                            {
                                psDecodedPict = decoder_GetDecodedPict(psCtxData->asDpb[ui32MinCountIdx].ui32TransactionId,
                                                                       &psDecStrCtx->sStrDecdPictList);
                                if (psDecodedPict)
                                {
                                    ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_FALSE);
                                    IMG_ASSERT(ui32Result == IMG_SUCCESS);
                                    if (ui32Result != IMG_SUCCESS)
                                    {
                                        return ui32Result;
                                    }
                                }

                                psCtxData->asDpb[ui32MinCountIdx].ui32TransactionId = 0;
                            }
                        }
                    }

                    IMG_ASSERT(ui32NumPicsDisplayed == ui32NumDisplayPics);
                    break;
                }
#endif /* HAS_H264 */

#ifdef HAS_MPEG4
                case VDEC_STD_MPEG4:
                case VDEC_STD_H263:
                case VDEC_STD_SORENSON:
                {
                    MPEG4FW_sContextData * psCtxData = (MPEG4FW_sContextData *)psDecStrCtx->psLastBePictDecRes->sFwCtxBuf.pvCpuVirt;

                    // Update the fw context for analysing the dpb in order to display or release any outstanding picture
                    UPDATE_HOST((&psDecStrCtx->psLastBePictDecRes->sFwCtxBuf), !decoder_IsFakeMTX(psDecStrCtx->psDecCtx, 0));   //If core 0 is fake, all are fake

                    if(psCtxData->sNewRefPic.ui32TransactionId && (!psCtxData->sNewRefPic.bSentForDisplay))
                    {
                        DEBUG_REPORT(REPORT_MODULE_DECODER,
                            "[TID=0x%08X] DISPLAY", psCtxData->sNewRefPic.ui32TransactionId);

                        ui32Result = decoder_PictureDisplay(psDecStrCtx,
                                                            GET_STREAM_PICTURE_ID(psCtxData->sNewRefPic.ui32TransactionId),
                                                            IMG_TRUE);
                        IMG_ASSERT(ui32Result == IMG_SUCCESS);
                        if (ui32Result != IMG_SUCCESS)
                        {
                            return ui32Result;
                        }

                    }
                    if (bDiscardRefs)
                    {
                        if(psCtxData->sNewRefPic.ui32TransactionId)
                        {
                            psDecodedPict = decoder_GetDecodedPict(psCtxData->sNewRefPic.ui32TransactionId,
                                                                   &psDecStrCtx->sStrDecdPictList);
                            if (psDecodedPict)
                            {
                                ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_FALSE);
                                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                                if (ui32Result != IMG_SUCCESS)
                                {

                                    return ui32Result;
                                }
                            }

                            psCtxData->sNewRefPic.ui32TransactionId = 0;
                        }
                        if(psCtxData->sOldRefPic.ui32TransactionId)
                        {
                            psDecodedPict = decoder_GetDecodedPict(psCtxData->sOldRefPic.ui32TransactionId,
                                                                   &psDecStrCtx->sStrDecdPictList);
                            if (psDecodedPict)
                            {
                                ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_FALSE);
                                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                                if (ui32Result != IMG_SUCCESS)
                                {
                                    return ui32Result;
                                }
                            }

                            psCtxData->sOldRefPic.ui32TransactionId = 0;
                        }
                    }
                    break;
                }
#endif /* HAS_MPEG4 */

#ifdef HAS_VP6
                case VDEC_STD_VP6:
                {
                    VP6FW_sContextData * psCtxData = (VP6FW_sContextData *)psDecStrCtx->psLastBePictDecRes->sFwCtxBuf.pvCpuVirt;

                    // Update the fw context for analysing the dpb in order to display or release any outstanding picture
                    UPDATE_HOST((&psDecStrCtx->psLastBePictDecRes->sFwCtxBuf), !decoder_IsFakeMTX(psDecStrCtx->psDecCtx, 0));   //If core 0 is fake, all are fake

                    if (bDiscardRefs)
                    {
                        IMG_ASSERT(psCtxData->sLastPic.ui32TransactionId);
                        {
                            psDecodedPict = decoder_GetDecodedPict(psCtxData->sLastPic.ui32TransactionId,
                                                                   &psDecStrCtx->sStrDecdPictList);
                            if (psDecodedPict)
                            {
                                ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_FALSE);
                                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                                if (ui32Result != IMG_SUCCESS)
                                {
                                    return ui32Result;
                                }
                            }
                        }
                        if(psCtxData->sGoldenPic.ui32TransactionId &&
                          (psCtxData->sGoldenPic.ui32TransactionId != psCtxData->sLastPic.ui32TransactionId)
                          )
                        {
                            psDecodedPict = decoder_GetDecodedPict(psCtxData->sGoldenPic.ui32TransactionId,
                                                                   &psDecStrCtx->sStrDecdPictList);
                            if (psDecodedPict)
                            {
                                ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_FALSE);
                                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                                if (ui32Result != IMG_SUCCESS)
                                {
                                    return ui32Result;
                                }
                            }
                            psCtxData->sGoldenPic.ui32TransactionId = 0;
                        }
                        psCtxData->sGoldenPic.ui32TransactionId = 0;
                        psCtxData->sLastPic.ui32TransactionId = 0;
                    }
                    break;
                }
#endif /* HAS_VP6 */
#ifdef HAS_VP8
                case VDEC_STD_VP8:
                    {
                        VP8FW_sContextData * psCtxData = (VP8FW_sContextData *)psDecStrCtx->psLastBePictDecRes->sFwCtxBuf.pvCpuVirt;

                        // Update the fw context for analysing the dpb in order to display or release any outstanding picture
                        UPDATE_HOST((&psDecStrCtx->psLastBePictDecRes->sFwCtxBuf), !decoder_IsFakeMTX(psDecStrCtx->psDecCtx, 0));   //If core 0 is fake, all are fake

                        if (bDiscardRefs)
                        {
                            psDecodedPict = decoder_GetDecodedPict(psCtxData->sLastPic.ui32TransactionId, &psDecStrCtx->sStrDecdPictList);
                            if (psDecodedPict)
                            {
                                ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_FALSE);
                                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                                if (ui32Result != IMG_SUCCESS)
                                {

                                    return ui32Result;
                                }
                            }
                            psCtxData->sLastPic.ui32TransactionId = 0;

                            psDecodedPict = decoder_GetDecodedPict(psCtxData->sGoldenPic.ui32TransactionId, &psDecStrCtx->sStrDecdPictList);
                            if (psDecodedPict)
                            {
                                ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_FALSE);
                                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                                if (ui32Result != IMG_SUCCESS)
                                {

                                    return ui32Result;
                                }
                            }
                            psCtxData->sGoldenPic.ui32TransactionId = 0;

                            psDecodedPict = decoder_GetDecodedPict(psCtxData->sAltPic.ui32TransactionId, &psDecStrCtx->sStrDecdPictList);
                            if (psDecodedPict)
                            {
                                ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_FALSE);
                                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                                if (ui32Result != IMG_SUCCESS)
                                {

                                    return ui32Result;
                                }
                            }
                            psCtxData->sAltPic.ui32TransactionId = 0;
                        }
                        break;
                    }
#endif /* HAS_VP8 */
#ifdef HAS_MPEG2
                case VDEC_STD_MPEG2:
                {
                    MPEG2FW_sContextData * psCtxData = (MPEG2FW_sContextData *)psDecStrCtx->psLastBePictDecRes->sFwCtxBuf.pvCpuVirt;
                    DECODER_sDecodedPict * psDisplayPict;

                    // Update the fw context for analysing the dpb in order to display or release any outstanding picture
                    UPDATE_HOST((&psDecStrCtx->psLastBePictDecRes->sFwCtxBuf), !decoder_IsFakeMTX(psDecStrCtx->psDecCtx, 0));   //If core 0 is fake, all are fake

                    if(psCtxData->sLastBField.ui32TransactionId)
                    {
                        // We have an unpaired B field we need to display first.
                        DEBUG_REPORT(REPORT_MODULE_DECODER,
                            "[TID=0x%08X] DISPLAY", psCtxData->sLastBField.ui32TransactionId);
                        ui32Result = decoder_PictureDisplay(psDecStrCtx,
                                                            GET_STREAM_PICTURE_ID(psCtxData->sLastBField.ui32TransactionId),
                                                            IMG_TRUE);
                        IMG_ASSERT(ui32Result == IMG_SUCCESS);
                        if (ui32Result != IMG_SUCCESS)
                        {
                            return ui32Result;
                        }

                        psDecodedPict = decoder_GetDecodedPict(psCtxData->sLastBField.ui32TransactionId,
                                &psDecStrCtx->sStrDecdPictList);
                        if (psDecodedPict)
                        {
                            ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_FALSE);
                            IMG_ASSERT(ui32Result == IMG_SUCCESS);
                            if (ui32Result != IMG_SUCCESS)
                            {
                                return ui32Result;
                            }
                        }
                        psCtxData->sLastBField.ui32TransactionId = 0;
                    }


                    if(psCtxData->sNewRefPic.ui32TransactionId && (!psCtxData->sNewRefPic.bSentForDisplay))
                    {
                        DEBUG_REPORT(REPORT_MODULE_DECODER,
                            "[TID=0x%08X] DISPLAY", psCtxData->sNewRefPic.ui32TransactionId);

                        psDisplayPict = decoder_GetDecodedPict(psCtxData->sNewRefPic.ui32TransactionId, &psDecStrCtx->sStrDecdPictList);
                        if (psDisplayPict && psDisplayPict->psPicture && psDisplayPict->psPicture->psDecPictInfo)
                        {
                            if (FLAG_IS_SET((psCtxData->sNewRefPic.ui8DisplayFlags), VDECFW_BUFFLAG_DISPLAY_FIELD_CODED))
                            {
                                if ( !FLAG_IS_SET((psCtxData->sNewRefPic.ui8DisplayFlags), VDECFW_BUFFLAG_DISPLAY_SINGLE_FIELD) )
                                {
                                    psDisplayPict->psPicture->psDecPictInfo->eBufferType = IMG_BUFFERTYPE_PAIR;
                                }
                                else
                                {
                                    psDisplayPict->psPicture->psDecPictInfo->eBufferType =
                                        FLAG_IS_SET((psCtxData->sNewRefPic.ui8DisplayFlags), VDECFW_BUFFLAG_DISPLAY_BOTTOM_FIELD)
                                            ? IMG_BUFFERTYPE_FIELD_BOTTOM : IMG_BUFFERTYPE_FIELD_TOP;
                                }
                            }
                            else
                            {
                                psDisplayPict->psPicture->psDecPictInfo->eBufferType = IMG_BUFFERTYPE_FRAME;
                            }
                        }
                        else
                        {
                            IMG_ASSERT(psDisplayPict);
                            IMG_ASSERT(psDisplayPict && psDisplayPict->psPicture);
                            IMG_ASSERT(psDisplayPict && psDisplayPict->psPicture && psDisplayPict->psPicture->psDecPictInfo);
                        }

                        ui32Result = decoder_PictureDisplay(psDecStrCtx,
                                                            GET_STREAM_PICTURE_ID(psCtxData->sNewRefPic.ui32TransactionId),
                                                            IMG_TRUE);
                        IMG_ASSERT(ui32Result == IMG_SUCCESS);
                        if (ui32Result != IMG_SUCCESS)
                        {
                            return ui32Result;
                        }
                    }
                    if (bDiscardRefs)
                    {
                        IMG_UINT32 ui32i;
                        IMG_UINT32 aui32PicIdsToDestroy[] = { psCtxData->sNewRefPic.ui32TransactionId,
                                                              psCtxData->sOldRefPic.ui32TransactionId };

                        for (ui32i = 0; ui32i < sizeof(aui32PicIdsToDestroy)/sizeof(IMG_UINT32); ui32i++)
                        {
                            if(aui32PicIdsToDestroy[ui32i])
                            {
                                psDecodedPict = decoder_GetDecodedPict(aui32PicIdsToDestroy[ui32i],
                                        &psDecStrCtx->sStrDecdPictList);
                                if (psDecodedPict)
                                {
                                    ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_FALSE);
                                    IMG_ASSERT(ui32Result == IMG_SUCCESS);
                                    if (ui32Result != IMG_SUCCESS)
                                    {
                                        return ui32Result;
                                    }
                                }
                            }
                        }

                        psCtxData->sNewRefPic.ui32TransactionId = 0;
                        psCtxData->sOldRefPic.ui32TransactionId = 0;
                    }
                    break;
                }
#endif /* HAS_MPEG2 */
#ifdef HAS_REAL
                case VDEC_STD_REAL:
                {
                    REALFW_sContextData * psCtxData = (REALFW_sContextData *)psDecStrCtx->psLastBePictDecRes->sFwCtxBuf.pvCpuVirt;

                    // Update the fw context for analysing the dpb in order to display or release any outstanding picture
                    UPDATE_HOST((&psDecStrCtx->psLastBePictDecRes->sFwCtxBuf), !decoder_IsFakeMTX(psDecStrCtx->psDecCtx, 0));   //If core 0 is fake, all are fake

                    if(psCtxData->sNewRefPic.ui32TransactionId && (!psCtxData->sNewRefPic.bSentForDisplay))
                    {
                        DEBUG_REPORT(REPORT_MODULE_DECODER,
                            "[TID=0x%08X] DISPLAY", psCtxData->sNewRefPic.ui32TransactionId);

                        ui32Result = decoder_PictureDisplay(psDecStrCtx,
                                                            GET_STREAM_PICTURE_ID(psCtxData->sNewRefPic.ui32TransactionId),
                                                            IMG_TRUE);
                        IMG_ASSERT(ui32Result == IMG_SUCCESS);
                        if (ui32Result != IMG_SUCCESS)
                        {
                            return ui32Result;
                        }

                    }
                    if (bDiscardRefs)
                    {
                        if(psCtxData->sNewRefPic.ui32TransactionId)
                        {
                            psDecodedPict = decoder_GetDecodedPict(psCtxData->sNewRefPic.ui32TransactionId,
                                                                   &psDecStrCtx->sStrDecdPictList);
                            if (psDecodedPict)
                            {
                                ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_FALSE);
                                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                                if (ui32Result != IMG_SUCCESS)
                                {

                                    return ui32Result;
                                }
                            }

                            psCtxData->sNewRefPic.ui32TransactionId = 0;
                        }
                        if(psCtxData->sOldRefPic.ui32TransactionId)
                        {
                            psDecodedPict = decoder_GetDecodedPict(psCtxData->sOldRefPic.ui32TransactionId,
                                                                   &psDecStrCtx->sStrDecdPictList);
                            if (psDecodedPict)
                            {
                                ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_FALSE);
                                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                                if (ui32Result != IMG_SUCCESS)
                                {
                                    return ui32Result;
                                }
                            }

                            psCtxData->sOldRefPic.ui32TransactionId = 0;
                        }
                    }
                    break;
                }
#endif /* HAS_REAL */
#ifdef HAS_VC1
                case VDEC_STD_VC1:
                {
                    VC1FW_sContextData * psCtxData = (VC1FW_sContextData *)psDecStrCtx->psLastBePictDecRes->sFwCtxBuf.pvCpuVirt;
                    IMG_BOOL bFound = IMG_TRUE;
                    IMG_UINT32 i;
                    //IMG_INT32  i32MinCount;
                    IMG_UINT32 ui32MinCountIdx;
                    IMG_UINT32 ui32NumDisplayPics = 0;
                    IMG_UINT32 ui32NumPicsDisplayed = 0;
                    DECODER_sDecodedPict* psDisplayPict = IMG_NULL;

                    // Update the fw context for analysing the references in order to display or release any outstanding picture
                    UPDATE_HOST((&psDecStrCtx->psLastBePictDecRes->sFwCtxBuf), !decoder_IsFakeMTX(psDecStrCtx->psDecCtx, 0));   //If core 0 is fake, all are fake

                    // Determine how many display pictures reside in the DPB.
                    for (i = 1; i < VC1FW_MAX_DPB_SIZE; i++)
                    {
                        if (psCtxData->asDpb[i].ui32TransactionId)
                        {
                            //Always needed for output in VC-1
                            ui32NumDisplayPics++;
                        }
                    }

                    //Destroy the picture from VC1FW_DPB_OLDREF_SLOT, it has been already displayed
                    if (bDiscardRefs && psCtxData->asDpb[0].ui32TransactionId)
                    {
                        psDecodedPict = decoder_GetDecodedPict(psCtxData->asDpb[0].ui32TransactionId, &psDecStrCtx->sStrDecdPictList);
                        if (psDecodedPict)
                        {
                            ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_FALSE);
                            IMG_ASSERT(ui32Result == IMG_SUCCESS);
                            if (ui32Result != IMG_SUCCESS)
                            {
                                return ui32Result;
                            }
                        }
                        psCtxData->asDpb[0].ui32TransactionId = 0;
                    }

                    while (bFound)
                    {
                        ui32MinCountIdx = -1;
                        bFound = IMG_FALSE;

                        // Loop over the DPB to find the first in order, starting from VC1FW_DPB_NEWREF_SLOT
                        for (i = 1; i < VC1FW_MAX_DPB_SIZE && !bFound; i++)
                        {
                            if (psCtxData->asDpb[i].ui32TransactionId)
                            {
                                if ( bDiscardRefs )
                                {
                                    ui32MinCountIdx = i;
                                    bFound = IMG_TRUE;
                                }
                            }
                        }

                        if (bFound)
                        {
                            DEBUG_REPORT(REPORT_MODULE_DECODER,
                                "[USERSID=0x%08X] [TID=0x%08X] DISPLAY",
                                psDecStrCtx->sConfig.ui32UserStrId,
                                psCtxData->asDpb[ui32MinCountIdx].ui32TransactionId);
                            IMG_ASSERT(psCtxData->asDpb[ui32MinCountIdx].ui32TransactionId != 0xffffffff);

                            psDisplayPict = decoder_GetDecodedPict(psCtxData->asDpb[ui32MinCountIdx].ui32TransactionId, &psDecStrCtx->sStrDecdPictList);

                            if (psDisplayPict && psDisplayPict->psPicture && psDisplayPict->psPicture->psDecPictInfo)
                            {
                                if (FLAG_IS_SET((psCtxData->asDpb[ui32MinCountIdx].ui8DisplayFlags), VDECFW_BUFFLAG_DISPLAY_FIELD_CODED))
                                {
                                    if (!FLAG_IS_SET((psCtxData->asDpb[ui32MinCountIdx].ui8DisplayFlags), VDECFW_BUFFLAG_DISPLAY_SINGLE_FIELD))
                                    {
                                        psDisplayPict->psPicture->psDecPictInfo->eBufferType = IMG_BUFFERTYPE_PAIR;
                                    }
                                    else
                                    {
                                        psDisplayPict->psPicture->psDecPictInfo->eBufferType =
                                            FLAG_IS_SET((psCtxData->asDpb[ui32MinCountIdx].ui8DisplayFlags), VDECFW_BUFFLAG_DISPLAY_BOTTOM_FIELD)
                                            ? IMG_BUFFERTYPE_FIELD_BOTTOM : IMG_BUFFERTYPE_FIELD_TOP;
                                    }
                                }
                                else
                                {
                                    psDisplayPict->psPicture->psDecPictInfo->eBufferType = IMG_BUFFERTYPE_FRAME;
                                }
                            }
                            else
                            {
                                IMG_ASSERT(psDisplayPict);
                                IMG_ASSERT(psDisplayPict && psDisplayPict->psPicture);
                                IMG_ASSERT(psDisplayPict && psDisplayPict->psPicture && psDisplayPict->psPicture->psDecPictInfo);
                            }

                            ui32NumPicsDisplayed++;
                            ui32Result = decoder_PictureDisplay(psDecStrCtx,
                                GET_STREAM_PICTURE_ID(psCtxData->asDpb[ui32MinCountIdx].ui32TransactionId),
                                (ui32NumPicsDisplayed == ui32NumDisplayPics) ? IMG_TRUE : IMG_FALSE);
                            IMG_ASSERT(ui32Result == IMG_SUCCESS);
                            if (ui32Result != IMG_SUCCESS)
                            {
                                return ui32Result;
                            }

                            if (bDiscardRefs)
                            {
                                psDecodedPict = decoder_GetDecodedPict(psCtxData->asDpb[ui32MinCountIdx].ui32TransactionId, &psDecStrCtx->sStrDecdPictList);
                                if (psDecodedPict)
                                {
                                    ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_FALSE);
                                    IMG_ASSERT(ui32Result == IMG_SUCCESS);
                                    if (ui32Result != IMG_SUCCESS)
                                    {
                                        return ui32Result;
                                    }
                                }
                                psCtxData->asDpb[ui32MinCountIdx].ui32TransactionId = 0;
                            }
                        }
                    }

                    IMG_ASSERT(ui32NumPicsDisplayed == ui32NumDisplayPics);
                    break;
                }
#endif /* HAS_VC1 */
#ifdef HAS_HEVC
                case VDEC_STD_HEVC:
                {
                    HEVCFW_sContextData *psCtx = (HEVCFW_sContextData *)
                        psDecStrCtx->psLastBePictDecRes->sFwCtxBuf.pvCpuVirt;
                    HEVCFW_sDecodedPictureBuffer * psDpb;

                    IMG_BOOL bFound = IMG_TRUE;
                    HEVCFW_DpbIdx iIdx;
                    HEVCFW_Poc iMinPOCVal;
                    HEVCFW_DpbIdx iDpbIdx;
                    IMG_UINT8 ui8NumDisplayPics = 0;
                    IMG_UINT8 ui8NumPicsDisplayed = 0;
                    DECODER_sDecodedPict* psDisplayPict = IMG_NULL;

                    // Update the fw context for analysing the dpb in order
                    // to display or release any outstanding picture
                    UPDATE_HOST((&psDecStrCtx->psLastBePictDecRes->sFwCtxBuf),
                                !decoder_IsFakeMTX(psDecStrCtx->psDecCtx, 0));

                    psDpb = &psCtx->sDpb;

                    // Determine how many display pictures reside in the DPB.
                    for (iIdx = 0; iIdx < HEVCFW_MAX_DPB_SIZE; ++iIdx)
                    {
                        HEVCFW_sPictureInDpb * psDpbPic = &psDpb->asPictures[iIdx];
                        if (psDpbPic->bValid && psDpbPic->bNeededForOutput)
                        {
                            ++ui8NumDisplayPics;
                        }
                    }

                    while (bFound)
                    {
                        HEVCFW_sPictureInDpb * psDpbPic;
                        iMinPOCVal = 0x7fffffff;
                        iDpbIdx = HEVCFW_DPB_IDX_INVALID;
                        bFound = IMG_FALSE;

                        // Loop over the DPB to find the first in order
                        for (iIdx = 0; iIdx < HEVCFW_MAX_DPB_SIZE; ++iIdx)
                        {
                            psDpbPic = &psDpb->asPictures[iIdx];
                            if (psDpbPic->bValid &&
                                (psDpbPic->bNeededForOutput || bDiscardRefs))
                            {
                                if (psDpbPic->sPicture.iPicOrderCntVal < iMinPOCVal)
                                {
                                    iMinPOCVal = psDpbPic->sPicture.iPicOrderCntVal;
                                    iDpbIdx = iIdx;
                                    bFound = IMG_TRUE;
                                }
                            }
                        }

                        if (!bFound)
                        {
                            break;
                        }

                        psDpbPic = &psDpb->asPictures[iDpbIdx];

                        if (psDpbPic->bNeededForOutput)
                        {
                            DEBUG_REPORT(REPORT_MODULE_DECODER,
                                "[USERSID=0x%08X] [TID=0x%08X] DISPLAY",
                                psDecStrCtx->sConfig.ui32UserStrId,
                                psDpbPic->sPicture.ui32TransactionId);
                            IMG_ASSERT(psDpbPic->sPicture.ui32TransactionId != 0xffffffff);

                            psDisplayPict = decoder_GetDecodedPict(
                                                psDpbPic->sPicture.ui32TransactionId,
                                                &psDecStrCtx->sStrDecdPictList);

                            if (psDisplayPict && psDisplayPict->psPicture &&
                                psDisplayPict->psPicture->psDecPictInfo)
                            {
                                psDisplayPict->psPicture->psDecPictInfo->eBufferType =
                                                                IMG_BUFFERTYPE_FRAME;
                            }
                            else
                            {
                                IMG_ASSERT(psDisplayPict);
                                IMG_ASSERT(psDisplayPict && psDisplayPict->psPicture);
                                IMG_ASSERT(psDisplayPict && psDisplayPict->psPicture && psDisplayPict->psPicture->psDecPictInfo);
                            }

                            ++ui8NumPicsDisplayed;
                            ui32Result = decoder_PictureDisplay(
                                    psDecStrCtx,
                                    GET_STREAM_PICTURE_ID(psDpbPic->sPicture.ui32TransactionId),
                                    ui8NumPicsDisplayed == ui8NumDisplayPics);
                            IMG_ASSERT(ui32Result == IMG_SUCCESS);
                            if (ui32Result != IMG_SUCCESS)
                            {
                                return ui32Result;
                            }
                            psDpbPic->bNeededForOutput = IMG_FALSE;
                        }

                        if (bDiscardRefs)
                        {
                            psDecodedPict = decoder_GetDecodedPict(
                                    psDpbPic->sPicture.ui32TransactionId,
                                    &psDecStrCtx->sStrDecdPictList);

                            if (psDecodedPict)
                            {
                                ui32Result = decoder_DecodedPictureDestroy(
                                        psDecStrCtx, psDecodedPict, IMG_FALSE);
                                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                                if (ui32Result != IMG_SUCCESS)
                                {
                                    return ui32Result;
                                }
                            }

                            psDpbPic->bValid = IMG_FALSE;
                        }
                    }

                    IMG_ASSERT(ui8NumPicsDisplayed == ui8NumDisplayPics);
                    break;
                }
#endif /* HAS_HEVC */

                default:
                    break;
            }
        }
    }
    else
#endif
    {
        IMG_ASSERT(psDecodedPict == IMG_NULL);
    }

    if (bDiscardRefs)
    {
        while (!DQ_empty(&psDecStrCtx->sStrDecdPictList))
        {
            DECODER_sDecodedPict * psNonDecodedPict = DQ_first(&psDecStrCtx->sStrDecdPictList);
            REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
                "[USERSID=0x%08X] Decoded picture list contains item ID:0x%08x when DPB is empty",
                psDecStrCtx->sConfig.ui32UserStrId, psNonDecodedPict->ui32TransactionId);
            ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psNonDecodedPict, IMG_FALSE);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }
        IMG_ASSERT(DQ_empty(&psDecStrCtx->sStrDecdPictList));

        if (psDecStrCtx->psLastBePictDecRes)
        {
#ifndef IMG_KERNEL_MODULE
            DECODER_sCoreContext * psDecCoreCtx;
            // so synchronise on core 0.
            psDecCoreCtx = decoder_CoreGetContext(psDecStrCtx->psDecCtx, 0);
            IMG_ASSERT(psDecCoreCtx != IMG_NULL);
            if(psDecCoreCtx == IMG_NULL)
            {
                return IMG_ERROR_FATAL;
            }

            // Synchronise before memseting last context structure.
            HWCTRL_SyncPDumpContexts(psDecCoreCtx->hHwCtx);
#endif
            // Clear the firmware context so that reference pictures are no longer referred to.
            IMG_MEMSET(psDecStrCtx->psLastBePictDecRes->sFwCtxBuf.pvCpuVirt, 0, psDecStrCtx->psLastBePictDecRes->sFwCtxBuf.ui32BufSize);
            UPDATE_DEVICE((&psDecStrCtx->psLastBePictDecRes->sFwCtxBuf), IMG_TRUE);
        }
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              DECODER_StreamFlush

******************************************************************************/
IMG_RESULT
DECODER_StreamFlush(
    IMG_HANDLE hDecStrCtx,
    IMG_BOOL bDiscardRefs
)
{
    DECODER_sStrContext * psDecStrCtx;
    IMG_RESULT ui32Result;

    psDecStrCtx = decoder_StreamGetContext(hDecStrCtx);

    ui32Result = decoder_StreamFlush(psDecStrCtx, bDiscardRefs);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              DECODER_StreamReleaseBuffers

******************************************************************************/
IMG_RESULT
DECODER_StreamReleaseBuffers(
    IMG_HANDLE hDecStrCtx
)
{
    DECODER_sStrContext * psDecStrCtx;
    DECODER_sDecodedPict * psDecodedPict;
    IMG_RESULT ui32Result;

    psDecStrCtx = decoder_StreamGetContext(hDecStrCtx);

    // Decoding queue should be empty since we are stopped.
    IMG_ASSERT(LST_empty(&psDecStrCtx->sPendStrUnitList));

    // Destroy all pictures in the decoded list
    psDecodedPict = DQ_first(&psDecStrCtx->sStrDecdPictList);
    while (psDecodedPict)
    {
        ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_TRUE);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        psDecodedPict = DQ_first(&psDecStrCtx->sStrDecdPictList);
    }

    // if and only if the output buffers were used for reference.
    //IMG_ASSERT("Stream context must be cleared on an output buffer release" == IMG_NULL);

    if (psDecStrCtx->psLastBePictDecRes)
    {
#ifndef IMG_KERNEL_MODULE
        DECODER_sCoreContext * psDecCoreCtx;
        // so synchronise on core 0.
        psDecCoreCtx = decoder_CoreGetContext(psDecStrCtx->psDecCtx, 0);
        IMG_ASSERT(psDecCoreCtx != IMG_NULL);
        if(psDecCoreCtx == IMG_NULL)
        {
            return IMG_ERROR_FATAL;
        }

        // Synchronise before memseting last context structure.
        HWCTRL_SyncPDumpContexts(psDecCoreCtx->hHwCtx);
#endif
        // Clear the firmware context so that reference pictures are no longer referred to.
        IMG_MEMSET(psDecStrCtx->psLastBePictDecRes->sFwCtxBuf.pvCpuVirt, 0, psDecStrCtx->psLastBePictDecRes->sFwCtxBuf.ui32BufSize);
        UPDATE_DEVICE((&psDecStrCtx->psLastBePictDecRes->sFwCtxBuf), IMG_TRUE);
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              decoder_StreamReferenceResourceDestroy

******************************************************************************/
static IMG_RESULT
decoder_StreamReferenceResourceDestroy(
    IMG_VOID  * pvItem,
    IMG_VOID  * pvFreeCbParam
)
{
    DECODER_sPictRefRes * psPictRefRes = pvItem;
    IMG_RESULT ui32Result;

    IMG_ASSERT(RESOURCE_ItemIsAvailable(&psPictRefRes->ui32RefCount));

    // Free memory (device-based) to store fw contexts for stream.
    ui32Result = MMU_FreeMem(&psPictRefRes->sFwCtrlBuf);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    IMG_FREE(psPictRefRes);

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              decoder_StreamReferenceResourceCreate

******************************************************************************/
static IMG_RESULT
decoder_StreamReferenceResourceCreate(
    DECODER_sStrContext   * psDecStrCtx,
    IMG_VOID              * pvFreeCbParam
)
{
    DECODER_sPictRefRes * psPictRefRes;
    IMG_BOOL bFwCtrlBuf = IMG_FALSE;
    IMG_RESULT ui32Result;
    VXDIO_sMemPool sInsecureMemPool;

    sInsecureMemPool.eMemPoolId = psDecStrCtx->psDecCtx->eInsecurePool;
    sInsecureMemPool.eMemPoolType = VXDIO_MEMPOOL_INSECURE;

    /* Allocate the firmware context buffer info structure. */
    VDEC_MALLOC(psPictRefRes);
    IMG_ASSERT(psPictRefRes);
    if (psPictRefRes == IMG_NULL)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "[USERSID=0x%08X] Failed to allocate memory for stream reference resource",
                psDecStrCtx->sConfig.ui32UserStrId);
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psPictRefRes);

    /* Allocate the firmware context buffer to contain data required for subsequent picture. */
    ui32Result = MMU_StreamMalloc(psDecStrCtx->hMmuStrHandle,
                                  MMU_HEAP_STREAM_BUFFERS,
                                  sInsecureMemPool, //FW Control always in insecure memory
                                  sizeof(VDECFW_sBufferControl),
                                  DEV_MMU_PAGE_ALIGNMENT,
                                  &psPictRefRes->sFwCtrlBuf);
    IMG_ASSERT(IMG_SUCCESS == ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        goto err_out_of_memory;
    }
    bFwCtrlBuf = IMG_TRUE;

    // Clear the context data in preparation for first time use by the firmware.
    IMG_MEMSET(psPictRefRes->sFwCtrlBuf.pvCpuVirt, 0, psPictRefRes->sFwCtrlBuf.ui32BufSize);
    UPDATE_DEVICE((&psPictRefRes->sFwCtrlBuf), IMG_TRUE);

    psPictRefRes->ui32RefCount = 1;

    ui32Result = RESOURCE_ListAdd(&psDecStrCtx->sRefResList,
                      psPictRefRes,
                      0,
                      &psPictRefRes->ui32RefCount);
    if (IMG_SUCCESS != ui32Result)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "[USERSID=0x%08X] Failed to add resource",
            psDecStrCtx->sConfig.ui32UserStrId);
    }

    return IMG_SUCCESS;

err_out_of_memory:
    if (psPictRefRes)
    {
        if (bFwCtrlBuf)
        {
            MMU_FreeMem(&psPictRefRes->sFwCtrlBuf);
        }

        IMG_FREE(psPictRefRes);
        psPictRefRes = IMG_NULL;
    }

    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
        "[USERSID=0x%08X] Failed to allocate device memory for stream reference resources",
                psDecStrCtx->sConfig.ui32UserStrId);

    return IMG_ERROR_OUT_OF_MEMORY;
}



/*!
******************************************************************************

 @Function              decoder_StreamDecodeResourceDestroy

******************************************************************************/
static IMG_RESULT
decoder_StreamDecodeResourceDestroy(
    IMG_VOID * pvItem,
    IMG_VOID * pvFreeCbParam
)
{
    DECODER_sPictDecRes * psPictDecRes = pvItem;
    IMG_RESULT ui32Result;

    IMG_ASSERT(RESOURCE_ItemIsAvailable(&psPictDecRes->ui32RefCount));

    // Free memory (device-based) to store fw contexts for stream.
    ui32Result = MMU_FreeMem(&psPictDecRes->sFwCtxBuf);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

#ifdef HAS_H264
    if (psPictDecRes->sH264SgmBuf.hMemory)
    {
        // Free memory (device-based) to store SGM.
        ui32Result = MMU_FreeMem(&psPictDecRes->sH264SgmBuf);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }
#endif /* HAS_H264 */

#ifdef HAS_MPEG4
    if (psPictDecRes->sMPEG4FEVLRBackup.hMemory)
    {
        // Free memory (device-based) to store FE VLR Backup.
        ui32Result = MMU_FreeMem(&psPictDecRes->sMPEG4FEVLRBackup);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }
#endif /* HAS_MPEG4 */

    IMG_FREE(psPictDecRes);

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              decoder_StreamDecodeResourceCreate

******************************************************************************/
static IMG_RESULT
decoder_StreamDecodeResourceCreate(
    DECODER_sStrContext * psDecStrCtx
)
{
    DECODER_sPictDecRes * psPictDecRes;
    IMG_BOOL bFwCtxBuf = IMG_FALSE;
    IMG_RESULT ui32Result;
    VXDIO_sMemPool sMemPool;
    VXDIO_sMemPool sInsecureMemPool;
#ifdef HAS_H264
    IMG_BOOL bH264SgmBuf = IMG_FALSE;
#endif /* HAS_H264 */
#ifdef HAS_MPEG4
    IMG_BOOL bMPEG4FEVLRBackup = IMG_FALSE;
#endif /* HAS_MPEG4 */

    sMemPool.eMemPoolId = (psDecStrCtx->psDecCtx->psDevConfig->bSecureMemoryAvailable && psDecStrCtx->sConfig.bSecureStream) ?
        psDecStrCtx->psDecCtx->eSecurePool : psDecStrCtx->psDecCtx->eInsecurePool;
    sMemPool.eMemPoolType = (psDecStrCtx->psDecCtx->psDevConfig->bSecureMemoryAvailable && psDecStrCtx->sConfig.bSecureStream) ?
        VXDIO_MEMPOOL_SECURE : VXDIO_MEMPOOL_INSECURE;

    sInsecureMemPool.eMemPoolId = psDecStrCtx->psDecCtx->eInsecurePool;
    sInsecureMemPool.eMemPoolType = VXDIO_MEMPOOL_INSECURE;

    /* Allocate the firmware context buffer info structure. */
    VDEC_MALLOC(psPictDecRes);
    IMG_ASSERT(psPictDecRes);
    if (psPictDecRes == IMG_NULL)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "[USERSID=0x%08X] Failed to allocate memory for stream decode resource",
                psDecStrCtx->sConfig.ui32UserStrId);
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psPictDecRes);

    /* Allocate the firmware context buffer to contain
       data required for subsequent picture. */
    ui32Result = MMU_StreamMalloc(psDecStrCtx->hMmuStrHandle,
                                  MMU_HEAP_STREAM_BUFFERS,
                                  sInsecureMemPool, //FW Context always in insecure memory
                                  sizeof(DECODER_uFwContexts),
                                  DEV_MMU_PAGE_ALIGNMENT,
                                  &psPictDecRes->sFwCtxBuf);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto err_out_of_memory;
    }
    bFwCtxBuf = IMG_TRUE;

    // Clear the context data in preparation for first time use by the firmware.
    IMG_MEMSET(psPictDecRes->sFwCtxBuf.pvCpuVirt, 0, psPictDecRes->sFwCtxBuf.ui32BufSize);
    UPDATE_DEVICE((&psPictDecRes->sFwCtxBuf), IMG_TRUE);

    switch (psDecStrCtx->sConfig.eVidStd)
    {
#ifdef HAS_H264
    case VDEC_STD_H264:
        /* Allocate the SGM buffer */
        ui32Result = MMU_StreamMalloc(psDecStrCtx->hMmuStrHandle,
                                      MMU_HEAP_STREAM_BUFFERS,
                                      sMemPool, //Secure if Secure Content and secure allocation is possible
                                      H264_SGM_BUFFER_BYTES_PER_MB * H264_SGM_MAX_MBS,
                                      DEV_MMU_PAGE_ALIGNMENT,
                                      &psPictDecRes->sH264SgmBuf);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto err_out_of_memory;
        }
        bH264SgmBuf = IMG_TRUE;

        if (!psDecStrCtx->psDecCtx->psDevConfig->bSecureMemoryAvailable || !psDecStrCtx->sConfig.bSecureStream)
        {
            // Clear the SGM data.
            IMG_MEMSET(psPictDecRes->sH264SgmBuf.pvCpuVirt, 0, psPictDecRes->sH264SgmBuf.ui32BufSize);
            UPDATE_DEVICE((&psPictDecRes->sH264SgmBuf), IMG_TRUE);
        }
        break;
#endif /* HAS_H264 */
#ifdef HAS_MPEG4
    case VDEC_STD_MPEG4:
    case VDEC_STD_H263:
    case VDEC_STD_SORENSON:
        /* Allocate buffer to backup not coded mpeg4 flags */
        ui32Result = MMU_StreamMalloc(psDecStrCtx->hMmuStrHandle,
                                      MMU_HEAP_STREAM_BUFFERS,
                                      sMemPool, //Secure if Secure Content and secure allocation is possible
                                      MPEG4_FE_VRL_NOT_CODED,
                                      DEV_MMU_PAGE_ALIGNMENT,
                                      &psPictDecRes->sMPEG4FEVLRBackup);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto err_out_of_memory;
        }
        bMPEG4FEVLRBackup = IMG_TRUE;

        if (!psDecStrCtx->psDecCtx->psDevConfig->bSecureMemoryAvailable || !psDecStrCtx->sConfig.bSecureStream)
        {
            // Clear the MPEG4 FE VLR data.
            IMG_MEMSET(psPictDecRes->sMPEG4FEVLRBackup.pvCpuVirt, 0, psPictDecRes->sMPEG4FEVLRBackup.ui32BufSize);
            UPDATE_DEVICE((&psPictDecRes->sMPEG4FEVLRBackup), IMG_TRUE);
        }
        break;
#endif /* HAS_MPEG4 */

    default:
        break;
    }

    psPictDecRes->ui32RefCount = 1;

    ui32Result = RESOURCE_ListAdd(&psDecStrCtx->sDecResList,
                                  psPictDecRes,
                                  0,
                                  &psPictDecRes->ui32RefCount);

    if (IMG_SUCCESS != ui32Result)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
               "[USERSID=0x%08X] Failed to add resource",
               psDecStrCtx->sConfig.ui32UserStrId);
    }


    return IMG_SUCCESS;

err_out_of_memory:
    if (psPictDecRes)
    {
        if (bFwCtxBuf)
        {
            MMU_FreeMem(&psPictDecRes->sFwCtxBuf);
        }
#ifdef HAS_H264
        if (bH264SgmBuf)
        {
            MMU_FreeMem(&psPictDecRes->sH264SgmBuf);
        }
#endif /* HAS_H264 */
#ifdef HAS_MPEG4
        if (bMPEG4FEVLRBackup)
        {
            MMU_FreeMem(&psPictDecRes->sMPEG4FEVLRBackup);
        }
#endif /* HAS_MPEG4 */
        IMG_FREE(psPictDecRes);
        psPictDecRes = IMG_NULL;
    }

    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
           "[USERSID=0x%08X] Failed to allocate device memory for stream decode resources",
           psDecStrCtx->sConfig.ui32UserStrId);

    return IMG_ERROR_OUT_OF_MEMORY;
}



/*!
******************************************************************************

 @Function              DECODER_StreamGetStatus

******************************************************************************/
IMG_RESULT
DECODER_StreamGetStatus(
    IMG_HANDLE hDecStrCtx,
    VDECDD_sDecStrStatus * psDecStrStatus
)
{
    DECODER_sStrContext   * psDecStrCtx;
    DECODER_sDecodedPict  * psDecodedPict;
    DECODER_sDecStrUnit   * psDecStrUnit;
    DECODER_sCoreContext  * psDecCoreCtx;
    IMG_RESULT              ui32Result;
    IMG_UINT32              ui32Item;
    IMG_UINT32              i;
    HWCTRL_sState           asCoreState[VDECDD_MSVDX_CORE_MAX];

    psDecStrCtx = decoder_StreamGetContext(hDecStrCtx);

    // Obtain the loading and free slots on most available core.
    decoder_GetCoreAndLoad(psDecStrCtx->psDecCtx,
                           psDecStrCtx->sDecStrStatus.ui32Features,
                           &psDecStrCtx->sDecStrStatus.ui32MinAvailLoad,
                           &psDecStrCtx->sDecStrStatus.ui32MinLoad,
                           IMG_NULL,
                           IMG_NULL);

    // Obtain the state of each core.
    psDecCoreCtx = LST_first(&psDecStrCtx->psDecCtx->sCoreList);
    while (psDecCoreCtx)
    {
        IMG_UINT32 aui32NumFreeSlots[VDEC_MAX_PIXEL_PIPES];
        IMG_UINT32 aui32PipeLoad[VDEC_MAX_PIXEL_PIPES];

        ui32Result = HWCTRL_GetCoreStatus(psDecCoreCtx->hHwCtx,
                                          aui32NumFreeSlots,
                                          aui32PipeLoad,
                                          &asCoreState[psDecCoreCtx->ui32CoreNum]);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        psDecCoreCtx = LST_next(psDecCoreCtx);
    }

    // Obtain the display and release list of first unprocessed picture in decoded list
    psDecStrCtx->sDecStrStatus.ui32DisplayPics = 0;
    psDecStrCtx->sDecStrStatus.ui32ReleasePics = 0;
    psDecodedPict = DQ_first(&psDecStrCtx->sStrDecdPictList);
    while (psDecodedPict)
    {
        // if this is the first unprocessed picture
        if (!psDecodedPict->bProcessed)
        {
            IMG_UINT32 ui32Idx;
            VDECFW_sBufferControl * psBufCtrl = (VDECFW_sBufferControl *)psDecodedPict->psPictRefRes->sFwCtrlBuf.pvCpuVirt;

            //Update the fw context for analysing the upcoming display picture (for dumping we need to know which is the next picture coming for display)
            UPDATE_HOST((&psDecodedPict->psPictRefRes->sFwCtrlBuf), !decoder_IsFakeMTX(psDecStrCtx->psDecCtx, GET_CORE_ID(psDecodedPict->ui32TransactionId)));

            // Get display pictures
            ui32Idx = psDecodedPict->ui32DisplayIdx;
            ui32Item = psDecStrCtx->sDecStrStatus.ui32DisplayPics;
            while (ui32Idx < psBufCtrl->ui32DisplayListLength &&
                   ui32Item < VDECFW_MAX_NUM_PICTURES)
            {
                psDecStrCtx->sDecStrStatus.aui32NextDisplayItems[ui32Item] = psBufCtrl->aui32DisplayList[ui32Idx];
                psDecStrCtx->sDecStrStatus.aui32NextDisplayItemParent[ui32Item] = psDecodedPict->ui32TransactionId;
                ui32Idx++;
                ui32Item++;
            }
            psDecStrCtx->sDecStrStatus.ui32DisplayPics = ui32Item;

            // Get release pictures
            ui32Idx = psDecodedPict->ui32ReleaseIdx;
            ui32Item = psDecStrCtx->sDecStrStatus.ui32ReleasePics;
            while (ui32Idx < psBufCtrl->ui32ReleaseListLength &&
                   ui32Item < VDECFW_MAX_NUM_PICTURES)
            {
                psDecStrCtx->sDecStrStatus.aui32NextReleaseItems[ui32Item] = psBufCtrl->aui32ReleaseList[ui32Idx];
                psDecStrCtx->sDecStrStatus.aui32NextReleaseItemParent[ui32Item] = psDecodedPict->ui32TransactionId;
                ui32Idx++;
                ui32Item++;
            }
            psDecStrCtx->sDecStrStatus.ui32ReleasePics = ui32Item;
            break;
        }

        if (psDecodedPict != DQ_last(&psDecStrCtx->sStrDecdPictList))
        {
            psDecodedPict = DQ_next(psDecodedPict);
        }
        else
        {
            psDecodedPict = IMG_NULL;
        }
    }

    // Get list of held decoded pictures.
    ui32Item = 0;
    psDecodedPict = DQ_first(&psDecStrCtx->sStrDecdPictList);
    while (psDecodedPict)
    {
        psDecStrCtx->sDecStrStatus.aui32DecodedPicts[ui32Item] = psDecodedPict->ui32TransactionId;
        ui32Item++;

        if (psDecodedPict != DQ_last(&psDecStrCtx->sStrDecdPictList))
        {
            psDecodedPict = DQ_next(psDecodedPict);
        }
        else
        {
            psDecodedPict = IMG_NULL;
        }
    }
    IMG_ASSERT(ui32Item == psDecStrCtx->sDecStrStatus.ui32NumPictDecoded);
    for(i=0;i<VDECDD_MSVDX_CORE_MAX;i++)
    {
        VXDIO_sState * psCoreState = &asCoreState[i].sCoreState;

        psDecStrCtx->sDecStrStatus.asCoreStatus[i].ui32MTX_PC                 = psCoreState->sEPRuntimeStatus.ui32MTX_PC;
        psDecStrCtx->sDecStrStatus.asCoreStatus[i].ui32MTX_PCX                = psCoreState->sEPRuntimeStatus.ui32MTX_PCX;
        psDecStrCtx->sDecStrStatus.asCoreStatus[i].ui32MTX_ENABLE             = psCoreState->sEPRuntimeStatus.ui32MTX_ENABLE;
        psDecStrCtx->sDecStrStatus.asCoreStatus[i].ui32MTX_STATUS_BITS        = psCoreState->sEPRuntimeStatus.ui32MTX_STATUS_BITS;
        psDecStrCtx->sDecStrStatus.asCoreStatus[i].ui32MTX_FAULT0             = psCoreState->sEPRuntimeStatus.ui32MTX_FAULT0;
        psDecStrCtx->sDecStrStatus.asCoreStatus[i].ui32MTX_A0StP              = psCoreState->sEPRuntimeStatus.ui32MTX_A0StP;
        psDecStrCtx->sDecStrStatus.asCoreStatus[i].ui32MTX_A0FrP              = psCoreState->sEPRuntimeStatus.ui32MTX_A0FrP;
        psDecStrCtx->sDecStrStatus.asCoreStatus[i].ui32DMA_COUNT[0]           = psCoreState->sEPRuntimeStatus.ui32DMA_COUNT[0];
        psDecStrCtx->sDecStrStatus.asCoreStatus[i].ui32DMA_COUNT[1]           = psCoreState->sEPRuntimeStatus.ui32DMA_COUNT[1];
        psDecStrCtx->sDecStrStatus.asCoreStatus[i].ui32DMA_COUNT[2]           = psCoreState->sEPRuntimeStatus.ui32DMA_COUNT[2];
        psDecStrCtx->sDecStrStatus.asCoreStatus[i].ui32DMA_SETUP[0]           = psCoreState->sEPRuntimeStatus.ui32DMA_SETUP[0];
        psDecStrCtx->sDecStrStatus.asCoreStatus[i].ui32DMA_SETUP[1]           = psCoreState->sEPRuntimeStatus.ui32DMA_SETUP[1];
        psDecStrCtx->sDecStrStatus.asCoreStatus[i].ui32DMA_SETUP[2]           = psCoreState->sEPRuntimeStatus.ui32DMA_SETUP[2];
        psDecStrCtx->sDecStrStatus.asCoreStatus[i].ui32DMA_PERIPHERAL_ADDR[0] = psCoreState->sEPRuntimeStatus.ui32DMA_PERIPHERAL_ADDR[0];
        psDecStrCtx->sDecStrStatus.asCoreStatus[i].ui32DMA_PERIPHERAL_ADDR[1] = psCoreState->sEPRuntimeStatus.ui32DMA_PERIPHERAL_ADDR[1];
        psDecStrCtx->sDecStrStatus.asCoreStatus[i].ui32DMA_PERIPHERAL_ADDR[2] = psCoreState->sEPRuntimeStatus.ui32DMA_PERIPHERAL_ADDR[2];
    }

    // Get list of decoding pictures
    ui32Item = 0;
    psDecStrUnit = LST_first(&psDecStrCtx->sPendStrUnitList);
    while (psDecStrUnit)
    {
        if (psDecStrUnit->psStrUnit->eStrUnitType == VDECDD_STRUNIT_PICTURE_START)
        {
            HWCTRL_sState * psCoreState = &asCoreState[psDecStrUnit->psDecCoreCtx->ui32CoreNum];
            VDECDD_sDecPictStatus * psDecPictStat = &psDecStrCtx->sDecStrStatus.asDecPictStatus[ui32Item];

            psDecPictStat->ui32TransactionId = psDecStrUnit->psDecPict->ui32TransactionId;

            psDecPictStat->ui32DMACStatus = -1;

            IMG_MEMCPY(psDecPictStat->aui8FWControlMsg,
                       psCoreState->sFwMsgStatus.aui8ControlFenceID,
                       sizeof(psDecPictStat->aui8FWControlMsg));
            IMG_MEMCPY(psDecPictStat->aui8FWDecodeMsg,
                       psCoreState->sFwMsgStatus.aui8DecodeFenceID,
                       sizeof(psDecPictStat->aui8FWDecodeMsg));
            IMG_MEMCPY(psDecPictStat->aui8FWCompletionMsg,
                       psCoreState->sFwMsgStatus.aui8CompletionFenceID,
                       sizeof(psDecPictStat->aui8FWCompletionMsg));

            IMG_MEMCPY(psDecPictStat->aui8HostControlMsg,
                       psCoreState->sHostMsgStatus.aui8ControlFenceID,
                       sizeof(psDecPictStat->aui8HostControlMsg));
            IMG_MEMCPY(psDecPictStat->aui8HostDecodeMsg,
                       psCoreState->sHostMsgStatus.aui8DecodeFenceID,
                       sizeof(psDecPictStat->aui8HostDecodeMsg));
            IMG_MEMCPY(psDecPictStat->aui8HostCompletionMsg,
                       psCoreState->sHostMsgStatus.aui8CompletionFenceID,
                       sizeof(psDecPictStat->aui8HostCompletionMsg));

            // Find the last checkpoint of each group for current decoding picture.
            psDecPictStat->eFwCheckPoint = -1;
            for (i = VDECFW_CHECKPOINT_FW_END; i >= VDECFW_CHECKPOINT_FW_START; i--)
            {
                // If the transaction has already been processed by this checkpoint mark this as the most
                // advanced point the transaction has reached and stop tracing back through the system.
                if (psCoreState->sCoreState.sFwState.asPipeState[0].aui32CheckPoint[i] >= psDecStrUnit->psDecPict->ui32TransactionId)
                {
                    psDecPictStat->eFwCheckPoint = i;
                    psDecPictStat->ui32DMACStatus = psCoreState->sCoreState.sFwState.asPipeState[0].aui32DMACStatus[0];
                    break;
                }
            }
            psDecPictStat->eFeHwCheckPoint = -1;
            psDecPictStat->ui32FeMbX = -1;
            psDecPictStat->ui32FeMbY = -1;
            for (i = VDECFW_CHECKPOINT_FE_END; i >= VDECFW_CHECKPOINT_FE_START; i--)
            {
                // If the transaction has already been processed by this checkpoint mark this as the most
                // advanced point the transaction has reached and stop tracing back through the system.
                if (psCoreState->sCoreState.sFwState.asPipeState[0].aui32CheckPoint[i] >= psDecStrUnit->psDecPict->ui32TransactionId)
                {
                    psDecPictStat->eFeHwCheckPoint = i;
                    //if (psDecPictStat->eFeHwCheckPoint != VDECFW_CHECKPOINT_FE_END)
                    {
                        // Only store the last processed MB while the picture has not been completed.
                        psDecPictStat->ui32FeMbX = psCoreState->sCoreState.sFwState.asPipeState[0].sFeMb.ui32X;
                        psDecPictStat->ui32FeMbY = psCoreState->sCoreState.sFwState.asPipeState[0].sFeMb.ui32Y;
                    }
                    break;
                }
            }
            psDecPictStat->eBeHwCheckPoint = -1;
            psDecPictStat->ui32BeMbX = -1;
            psDecPictStat->ui32BeMbY = -1;
            for (i = VDECFW_CHECKPOINT_BE_END; i >= VDECFW_CHECKPOINT_BE_START; i--)
            {
                // If the transaction has already been processed by this checkpoint mark this as the most
                // advanced point the transaction has reached and stop tracing back through the system.
                if (psCoreState->sCoreState.sFwState.asPipeState[0].aui32CheckPoint[i] >= psDecStrUnit->psDecPict->ui32TransactionId)
                {
                    psDecPictStat->eBeHwCheckPoint = i;
                    //if (psDecPictStat->eBeHwCheckPoint != VDECFW_CHECKPOINT_BE_END)
                    {
                        // Only store the last processed MB while the picture has not been completed.
                        psDecPictStat->ui32BeMbX = psCoreState->sCoreState.sFwState.asPipeState[0].sBeMb.ui32X;
                        psDecPictStat->ui32BeMbY = psCoreState->sCoreState.sFwState.asPipeState[0].sBeMb.ui32Y;
                    }
                    break;
                }
            }

            ui32Item++;
        }
        psDecStrUnit = LST_next(psDecStrUnit);
    }
    IMG_ASSERT(ui32Item == psDecStrCtx->sDecStrStatus.ui32NumPictDecoding);

    *psDecStrStatus = psDecStrCtx->sDecStrStatus;

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              decoder_StreamProcessUnit

******************************************************************************/
static IMG_RESULT
decoder_StreamProcessUnit(
    DECODER_sStrContext * psDecStrCtx,
    VDECDD_sStrUnit * psStrUnit,
    IMG_BOOL * pbDone
)
{
    DECODER_sDecStrUnit * psDecStrUnit;
    DECODER_sCoreContext * psDecCoreCtx = IMG_NULL;
    DECODER_sDecPict * psDecPict = IMG_NULL;
    IMG_BOOL bProcessed = IMG_FALSE;
    IMG_RESULT ui32Result;

    switch (psStrUnit->eStrUnitType)
    {
    case VDECDD_STRUNIT_SEQUENCE_END:
    case VDECDD_STRUNIT_ANONYMOUS:
    case VDECDD_STRUNIT_CLOSED_GOP:
    case VDECDD_STRUNIT_PICTURE_PORTENT:
    case VDECDD_STRUNIT_STOP:
    case VDECDD_STRUNIT_FENCE:
        // Nothing more to do so mark the stream unit as processed.
        bProcessed = IMG_TRUE;
        break;

    case VDECDD_STRUNIT_SEQUENCE_START:
        {
            IMG_UINT32 ui32MaxNumActivePict;

            // Determine how many decoded pictures can be held for reference in
            // the decoder for this stream.
            ui32Result = VDECDDUTILS_RefPictGetMaxNum(&psDecStrCtx->sConfig,
                                                      &psStrUnit->psSequHdrInfo->sComSequHdrInfo,
                                                      &ui32MaxNumActivePict);
            if (IMG_SUCCESS != ui32Result)
            {
                return ui32Result;
            }

            // Double for field coding.
            ui32MaxNumActivePict *= 2;

            // Ensure that there are enough resource to have pictures filling all slots on all cores.
            ui32MaxNumActivePict += psDecStrCtx->psDecCtx->ui32NumCores * psDecStrCtx->psDecCtx->psDevConfig->ui32NumSlotsPerPipe * psDecStrCtx->psDecCtx->ui32NumPipes;

            // Increase decoder stream resources if necessary.
            while (psDecStrCtx->ui32NumRefRes < ui32MaxNumActivePict)
            {
                ui32Result = decoder_StreamReferenceResourceCreate(psDecStrCtx, IMG_NULL);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }
                psDecStrCtx->ui32NumRefRes++;
            }
        }

        // Nothing more to do so mark the stream unit as processed.
        bProcessed = IMG_TRUE;
        break;

    case VDECDD_STRUNIT_PICTURE_START:
        if (psStrUnit->bDecode)
        {
            ui32Result = decoder_GetCoreAndLoad(psDecStrCtx->psDecCtx,
                                                psStrUnit->ui32Features,
                                                IMG_NULL,
                                                IMG_NULL,
                                                &psDecCoreCtx,
                                                &psDecStrCtx->ui8Pipe);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            // Prepare and submit picture to decode.
            ui32Result = decoder_PictureDecode(
                            psDecCoreCtx,
                            psDecStrCtx,
                            psStrUnit,
                            &psDecPict);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
            DEBUG_REPORT(REPORT_MODULE_DECODER,
                "[USERSID=0x%08X] [TID=0x%08X] START pipe: %x",
                psDecStrCtx->sConfig.ui32UserStrId,
                psDecStrCtx->ui32LastFeTransactionId, psDecStrCtx->ui8Pipe);
        }
        else
        {
            bProcessed = IMG_TRUE;
        }
        break;

    case VDECDD_STRUNIT_PICTURE_FRAG:
        if (psStrUnit->bDecode)
        {
            ui32Result = decoder_PictureSubmitMoreData(psDecStrCtx, psStrUnit);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
            DEBUG_REPORT(REPORT_MODULE_DECODER,
                "[USERSID=0x%08X] [TID=0x%08X] FRAG",
                psDecStrCtx->sConfig.ui32UserStrId,
                psDecStrCtx->ui32LastFeTransactionId);
        }
        else
        {
            bProcessed = IMG_TRUE;
        }
        break;

    case VDECDD_STRUNIT_PICTURE_END:
        if (psStrUnit->bDecode)
        {
            ui32Result = decoder_PictureFinalize(psDecStrCtx, psStrUnit);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
            DEBUG_REPORT(REPORT_MODULE_DECODER,
                "[USERSID=0x%08X] [TID=0x%08X] END",
                psDecStrCtx->sConfig.ui32UserStrId,
                psDecStrCtx->ui32LastFeTransactionId);
        }
        else
        {
            bProcessed = IMG_TRUE;
        }
        break;

    default:
        IMG_ASSERT(IMG_FALSE);
        break;
    }

    // If this or any preceding stream unit(s) could not be
    // completely processed, add this unit to the queue.
    if (!LST_empty(&psDecStrCtx->sPendStrUnitList) || !bProcessed)
    {
        // Add unit to stream decode list.
        VDEC_MALLOC(psDecStrUnit);
        IMG_ASSERT(psDecStrUnit);
        if (psDecStrUnit == IMG_NULL)
        {
            REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                "[USERSID=0x%08X] Failed to allocate memory for Decoder stream unit wrapper",
                psDecStrCtx->sConfig.ui32UserStrId);
            return IMG_ERROR_OUT_OF_MEMORY;
        }

        VDEC_BZERO(psDecStrUnit);
        psDecStrUnit->psStrUnit = psStrUnit;
        psDecStrUnit->psDecCoreCtx = psDecCoreCtx;

        // make PICTURE_START owner of psDecPict
        if (psDecPict != IMG_NULL)
        {
            IMG_ASSERT(psStrUnit->eStrUnitType == VDECDD_STRUNIT_PICTURE_START);
            psDecStrUnit->psDecPict = psDecPict;
        }

        LST_add(&psDecStrCtx->sPendStrUnitList, psDecStrUnit);

        decoder_KickListService(psDecStrCtx, psStrUnit);
    }
    else
    {
        *pbDone = IMG_TRUE;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              DECODER_StreamProcessUnit

******************************************************************************/
IMG_RESULT
DECODER_StreamProcessUnit(
    IMG_HANDLE hDecStrCtx,
    VDECDD_sStrUnit * psStrUnit
)
{
    DECODER_sStrContext * psDecStrCtx = decoder_StreamGetContext(hDecStrCtx);
    IMG_BOOL bProcessed = IMG_FALSE;
    IMG_RESULT ui32Result;

    // Process the stream unit
    ui32Result = decoder_StreamProcessUnit(psDecStrCtx, psStrUnit, &bProcessed);
    if (ui32Result != IMG_SUCCESS)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "[USERSID=0x%08X] Failed to process stream unit of type [UTYPE=0x%08X]",
            psDecStrCtx->sConfig.ui32UserStrId, psStrUnit->eStrUnitType);
        return ui32Result;
    }

    if (bProcessed)
    {
        // If there is nothing being decoded for this stream immediately
        // handle the unit (non-picture so doesn't need decoding).
        // Report that this unit has been processed.
        ui32Result = psDecStrCtx->psDecCtx->pfnCompCallback(
            DECODER_CB_UNIT_PROCESSED,
            psDecStrCtx->psDecCtx->pvCompInitUserData,
            IMG_NULL,
            psDecStrCtx->pvUserData,
            psStrUnit);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              DECODER_StreamFlushInput

******************************************************************************/
IMG_RESULT
DECODER_StreamFlushInput(
    IMG_HANDLE      hDecServiceInt,
    IMG_VOID     ** ppvStrUserIntData
)
{
    IMG_RESULT              ui32Result;
    DECODER_sStrContext   * psDecStrCtx;
    DECODER_sDecStrUnit   * psDecStrUnit;
    IMG_BOOL                bPictStart = IMG_FALSE;

    psDecStrCtx = (DECODER_sStrContext*)hDecServiceInt;

    *ppvStrUserIntData = psDecStrCtx->pvUserIntData;

    // Peek the first stream unit
    psDecStrUnit = LST_first(&psDecStrCtx->sPendStrUnitList);
    if ((psDecStrUnit==IMG_NULL) ||
        (psDecStrUnit->psStrUnit->eStrUnitType==VDECDD_STRUNIT_PICTURE_START))
    {
        bPictStart = IMG_TRUE;
    }

    // Process all units from the pending stream list until the next picture start.
    while (!bPictStart)
    {
        // Actually remove the unit now from the pending stream list.
        LST_remove(&psDecStrCtx->sPendStrUnitList, psDecStrUnit);

        DEBUG_REPORT(REPORT_MODULE_DECODER, "[Stream Unit: %d] LATE SERVICE", psDecStrUnit->psStrUnit->eStrUnitType);

        // Report that this unit has been processed.
        ui32Result = psDecStrCtx->psDecCtx->pfnCompCallback(
            DECODER_CB_UNIT_PROCESSED,
            psDecStrCtx->psDecCtx->pvCompInitUserData,
            IMG_NULL,
            psDecStrCtx->pvUserData,
            psDecStrUnit->psStrUnit);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        // Destroy the Decoder stream unit wrapper.
        IMG_FREE(psDecStrUnit);

        // Peek at the next stream unit.
        psDecStrUnit = LST_first(&psDecStrCtx->sPendStrUnitList);
        if ((psDecStrUnit==IMG_NULL) ||
            (psDecStrUnit->psStrUnit->eStrUnitType==VDECDD_STRUNIT_PICTURE_START))
        {
            bPictStart = IMG_TRUE;
        }
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              DECODER_StreamIsIdle

******************************************************************************/
IMG_BOOL
DECODER_StreamIsIdle(
    IMG_HANDLE hDecStrCtx
)
{
    DECODER_sStrContext * psDecStrCtx;

    psDecStrCtx = decoder_StreamGetContext(hDecStrCtx);
    IMG_ASSERT(psDecStrCtx);

    return LST_empty(&psDecStrCtx->sPendStrUnitList);
}



/*!
******************************************************************************

 @Function              decoder_StreamDestroy

******************************************************************************/
static IMG_RESULT
decoder_StreamDestroy(
    DECODER_sStrContext * psDecStrCtx
)
{
    DECODER_sDecStrUnit * psDecStrUnit;
    DECODER_sDecodedPict * psDecodedPict;
    IMG_UINT32 i;
    IMG_RESULT ui32Result;

    // Required for getting segments from decode picture to free
    DECODER_sDecPictSeg * psDecPictSeg;

    // Decrement the stream count
    psDecStrCtx->psDecCtx->ui32StrCnt--;


    // Ensure that there are no pictures for this stream outstanding
    // on any decoder cores.
    // This should not be removed, it is important to see it if it ever happens.
    // In practice we see it many times with Application Timeout.
    IMG_ASSERT(LST_empty(&psDecStrCtx->sPendStrUnitList));

    // At this point all resources for the stream are guaranteed to not be used
    // and no further hardware interrupts will be received.

    // Destroy all stream units submitted for processing.
    psDecStrUnit = LST_removeHead(&psDecStrCtx->sPendStrUnitList);
    while (psDecStrUnit)
    {
        // If the unit was submitted for decoding (picture)...
        if (psDecStrUnit->psDecPict)
        {
            // Explicitly remove picture from core decode queue and destroy.
            IMG_ASSERT(psDecStrUnit->psDecCoreCtx);
            ui32Result = HWCTRL_RemoveFromPicList(psDecStrUnit->psDecCoreCtx->hHwCtx,
                                               psDecStrUnit->psDecPict);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
            // Free decoder picture
            IMG_FREE(psDecStrUnit->psDecPict->psFirstFieldFwMsg);
            psDecStrUnit->psDecPict->psFirstFieldFwMsg = IMG_NULL;
            IMG_FREE(psDecStrUnit->psDecPict->psSecondFieldFwMsg);
            psDecStrUnit->psDecPict->psSecondFieldFwMsg = IMG_NULL;

            // Free all the segments of the picture
            psDecPictSeg = LST_removeHead(&psDecStrUnit->psDecPict->sDecPictSegList);
            while(psDecPictSeg)
            {
                IMG_FREE(psDecPictSeg);
                psDecPictSeg = IMG_NULL;

                psDecPictSeg = LST_removeHead(&psDecStrUnit->psDecPict->sDecPictSegList);
            }

            IMG_ASSERT(psDecStrUnit->psDecPict->psDecStrCtx == psDecStrCtx);

            psDecStrCtx->sDecStrStatus.ui32NumPictDecoding--;

            ui32Result = decoder_PictureDestroy(psDecStrCtx,
                                      GET_STREAM_PICTURE_ID(psDecStrUnit->psDecPict->ui32TransactionId),
                                                IMG_TRUE);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            IMG_FREE(psDecStrUnit->psDecPict);
            psDecStrUnit->psDecPict = IMG_NULL;
        }

        // Report that the picture has been decoded and
        // have all non-reference elements released.
        ui32Result = psDecStrCtx->psDecCtx->pfnCompCallback(
            DECODER_CB_UNIT_PROCESSED,
            psDecStrCtx->psDecCtx->pvCompInitUserData,
            IMG_NULL,
            psDecStrCtx->pvUserData,
            psDecStrUnit->psStrUnit);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        // Free the picture container
        IMG_FREE(psDecStrUnit);
        psDecStrUnit = IMG_NULL;

        psDecStrUnit = LST_removeHead(&psDecStrCtx->sPendStrUnitList);
    }

    // Destroy all pictures in the decoded list
    psDecodedPict = DQ_first(&psDecStrCtx->sStrDecdPictList);
    while (psDecodedPict)
    {
        ui32Result = decoder_DecodedPictureDestroy(psDecStrCtx, psDecodedPict, IMG_TRUE);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        psDecodedPict = DQ_first(&psDecStrCtx->sStrDecdPictList);
    }

    // Ensure all picture queues are empty.
    IMG_ASSERT(LST_empty(&psDecStrCtx->sPendStrUnitList));
    IMG_ASSERT(DQ_empty(&psDecStrCtx->sStrDecdPictList));

#ifdef VDEC_USE_PVDEC
    // Free memory to store stream context buffer.
    ui32Result = MMU_FreeMem(&psDecStrCtx->sPvdecFwCtxBuf);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    // Free memory to store stream context PTD.
    ui32Result = MMU_FreeMem(&psDecStrCtx->sPtdBufInfo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }
#endif


    // Release any fw contexts held by stream.
    if (psDecStrCtx->psPrevFePictDecRes)
    {
        RESOURCE_ItemReturn(&psDecStrCtx->psPrevFePictDecRes->ui32RefCount);
    }
    if (psDecStrCtx->psCurFePictDecRes)
    {
        RESOURCE_ItemReturn(&psDecStrCtx->psCurFePictDecRes->ui32RefCount);
    }
    if (psDecStrCtx->psLastBePictDecRes)
    {
        RESOURCE_ItemReturn(&psDecStrCtx->psLastBePictDecRes->ui32RefCount);
    }

    // Remove the device resources used for decoding and the two
    for (i = 0; i < psDecStrCtx->ui32NumDecRes + 2; i++)
    {
        ui32Result = RESOURCE_ListEmpty(&psDecStrCtx->sDecResList,
                                        IMG_FALSE,
                                        decoder_StreamDecodeResourceDestroy,
                                        IMG_NULL);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }
    IMG_ASSERT(LST_empty(&psDecStrCtx->sDecResList));


    // Remove all stream decode resources.
    ui32Result = RESOURCE_ListEmpty(&psDecStrCtx->sRefResList,
                                     IMG_FALSE,
                                     decoder_StreamReferenceResourceDestroy,
                                     IMG_NULL);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }
    IMG_ASSERT(LST_empty(&psDecStrCtx->sRefResList));

    IDGEN_DestroyContext(psDecStrCtx->hPictIdGen);

    ui32Result = IDGEN_FreeId(psDecStrCtx->psDecCtx->hStrIdGen,psDecStrCtx->ui32StrId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    LST_remove(&psDecStrCtx->psDecCtx->sStreamList, psDecStrCtx);

    IMG_FREE(psDecStrCtx);
    psDecStrCtx = IMG_NULL;

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              DECODER_StreamDestroy

******************************************************************************/
IMG_RESULT
DECODER_StreamDestroy(
    IMG_HANDLE hDecStrCtx
)
{
    IMG_RESULT ui32Result;

    ui32Result = decoder_StreamDestroy(decoder_StreamGetContext(hDecStrCtx));
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              decoder_GetRequiredCoreFeatures

 @Description

 This function obtains the core features.

 @Input     psStreamConfig  : Pointer to stream configuration.

 @Input     psOutputConfig  : Pointer to output configuration.

 @Output    peFeatures  : Pointer to core features.

 @Return    IMG_RESULT  : This function returns either IMG_SUCCESS or an
                          error code.

******************************************************************************/
static IMG_RESULT
decoder_GetRequiredCoreFeatures(
    const VDEC_sStrConfigData   * psStreamConfig,
    const VDEC_sStrOutputConfig * psOutputConfig,
    IMG_UINT32                  * pui32Features
)
{
    IMG_UINT32 ui32Features = 0;

    /* Check Video Standard. */
    switch (psStreamConfig->eVidStd)
    {
    case VDEC_STD_MPEG2:
        ui32Features = VDECDD_COREFEATURE_MPEG2;
        break;

    case VDEC_STD_MPEG4:
    case VDEC_STD_H263:
    case VDEC_STD_SORENSON:
        ui32Features = VDECDD_COREFEATURE_MPEG4;
        break;

    case VDEC_STD_H264:
        ui32Features = VDECDD_COREFEATURE_H264;
        break;

    case VDEC_STD_VC1:
        ui32Features = VDECDD_COREFEATURE_VC1;
        break;

    case VDEC_STD_AVS:
        ui32Features = VDECDD_COREFEATURE_AVS;
        break;

    case VDEC_STD_REAL:
        ui32Features = VDECDD_COREFEATURE_REAL;
        break;

    case VDEC_STD_JPEG:
        ui32Features = VDECDD_COREFEATURE_JPEG;
        break;

    case VDEC_STD_VP6:
        ui32Features = VDECDD_COREFEATURE_VP6;
        break;

    case VDEC_STD_VP8:
        ui32Features = VDECDD_COREFEATURE_VP8;
        break;

    case VDEC_STD_HEVC:
        ui32Features = VDECDD_COREFEATURE_HEVC;
        break;

    default:
        IMG_ASSERT(IMG_FALSE);
        break;
    }

    if (psOutputConfig)
    {
        if (psOutputConfig->eRotMode != VDEC_ROTATE_0)
        {
            ui32Features |= VDECDD_COREFEATURE_ROTATION;
        }

        if (psOutputConfig->bScale)
        {
            ui32Features |= VDECDD_COREFEATURE_SCALING;

            if (psOutputConfig->bForceOold)
            {
                ui32Features |= VDECDD_COREFEATURE_SCALING_WITH_OOLD;
            }
        }
    }

    *pui32Features = ui32Features;

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              DECODER_CheckSupport

******************************************************************************/
static IMG_BOOL decoder_IsSupportedByAtLeastOnePipe(IMG_BOOL *aFeatures, IMG_UINT32 ui32NumPipes)
{
    IMG_UINT32 i;
    IMG_ASSERT(ui32NumPipes <= VDEC_MAX_PIXEL_PIPES);

    for(i = 0; i < ui32NumPipes;i++)
    {
        if(aFeatures[i])
        {
            return IMG_TRUE;
        }
    }

    return IMG_FALSE;
}

/*!
******************************************************************************

 @Function              DECODER_CheckSupport

******************************************************************************/
IMG_RESULT
DECODER_CheckSupport(
    IMG_HANDLE                      hDecCtx,
    const VDEC_sStrConfigData     * psStrConfig,
    const VDEC_sStrOutputConfig   * psOutputConfig,
    const VDECDD_sDdPictBuf       * psDispPictBuf,
    const VDEC_sPictRendInfo      * psReqPictRendInfo,
    const VDEC_sComSequHdrInfo    * psComSequHdrInfo,
    const BSPP_sPictHdrInfo       * psPictHdrInfo,
    const VDEC_sComSequHdrInfo    * psPrevComSequHdrInfo,
    const BSPP_sPictHdrInfo       * psPrevPictHdrInfo,
    VDEC_sUnSupportedFlags        * psUnsupported,
    IMG_UINT32                    * pui32Features
)
{
    DECODER_sContext *          psDecCtx = (DECODER_sContext*)hDecCtx;
    DECODER_sCoreContext      * psDecCoreCtx;
    VXD_sCoreProps            * psCoreProps;
    const VDEC_sPictRendInfo  * psDispPictRendInfo = IMG_NULL;
    IMG_RESULT                  ui32Result;

    // Ensure input parameters are valid.
    IMG_ASSERT(hDecCtx);
    IMG_ASSERT(psStrConfig);
    IMG_ASSERT(psUnsupported);

    if(hDecCtx == IMG_NULL || psStrConfig == IMG_NULL ||
        psUnsupported == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    if (psDispPictBuf)
    {
        psDispPictRendInfo = &psDispPictBuf->sRendInfo;
    }

    ui32Result = IMG_ERROR_GENERIC_FAILURE;
    // Validate compatibility between the supplied configuration/state
    // and the master core only at the moment (assumed to have superset of features).
    // Some features may not be present on any slave cores which might
    // cause poor utilisation of hardware.
    for (psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
         psDecCoreCtx;
         psDecCoreCtx = LST_next(psDecCoreCtx))
    {
        if (!psDecCoreCtx->bMaster)
        {
            continue;
        }

        VDEC_BZERO(psUnsupported);

        psCoreProps = &psDecCoreCtx->sCoreProps;
        IMG_ASSERT(psCoreProps);

        ui32Result = IMG_ERROR_NOT_SUPPORTED;

        if (psStrConfig)
        {
            // Check that the video standard is supported.
            switch (psStrConfig->eVidStd)
            {
            case VDEC_STD_AVS:
                if (!decoder_IsSupportedByAtLeastOnePipe(psCoreProps->abAvs, psCoreProps->ui32NumPixelPipes) )
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: VIDEO STANDARD (AVS)",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32StrConfig |= VDECDD_UNSUPPORTED_STRCONFIG_STD;
                }
                break;

            case VDEC_STD_H263:
                /* h263 is included in mpeg4 */
                if (!decoder_IsSupportedByAtLeastOnePipe(psCoreProps->abMpeg4, psCoreProps->ui32NumPixelPipes) )
                {
                    IMG_WARN_ONCE("UNSUPPORTED: VIDEO STANDARD [H263]\n");
                    psUnsupported->ui32StrConfig |= VDECDD_UNSUPPORTED_STRCONFIG_STD;
                }
                break;

            case VDEC_STD_H264:
                if (!decoder_IsSupportedByAtLeastOnePipe(psCoreProps->abH264, psCoreProps->ui32NumPixelPipes))
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: VIDEO STANDARD (H.264)",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32StrConfig |= VDECDD_UNSUPPORTED_STRCONFIG_STD;
                }
                if (psComSequHdrInfo &&
                    (H264_PROFILE_MVC_HIGH == psComSequHdrInfo->ui32CodecProfile ||
                     H264_PROFILE_MVC_STEREO == psComSequHdrInfo->ui32CodecProfile) &&
                     psComSequHdrInfo->ui32NumViews > VDEC_H264_MVC_MAX_VIEWS )
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[SW]: NUMBER OF VIEWS",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32SequHdr |= VDECDD_UNSUPPORTED_SEQUHDR_NUM_OF_VIEWS;
                }
#ifndef ENABLE_SEPARATE_COLOUR_PLANES
                if(psComSequHdrInfo && psComSequHdrInfo->bSeparateChromaPlanes)
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[SW]: SEPARATE COLOUR PLANE SUPPORT NOT ENABLED",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32SequHdr |= VDECDD_UNSUPPORTED_SEQUHDR_SEP_COLOUR_PLANE;
                }
#endif
                break;

            case VDEC_STD_JPEG:
                if (!decoder_IsSupportedByAtLeastOnePipe(psCoreProps->abJpeg, psCoreProps->ui32NumPixelPipes) )
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: VIDEO STANDARD (JPEG)",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32StrConfig |= VDECDD_UNSUPPORTED_STRCONFIG_STD;
                }
                break;

            case VDEC_STD_MPEG2:
                if (!decoder_IsSupportedByAtLeastOnePipe(psCoreProps->abMpeg2, psCoreProps->ui32NumPixelPipes) )
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: VIDEO STANDARD (MPEG2)",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32StrConfig |= VDECDD_UNSUPPORTED_STRCONFIG_STD;
                }
                break;

            case VDEC_STD_MPEG4:
                if (!decoder_IsSupportedByAtLeastOnePipe(psCoreProps->abMpeg4, psCoreProps->ui32NumPixelPipes))
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: VIDEO STANDARD (MPEG4)",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32StrConfig |= VDECDD_UNSUPPORTED_STRCONFIG_STD;
                }
                break;

            case VDEC_STD_REAL:
                if (!decoder_IsSupportedByAtLeastOnePipe(psCoreProps->abReal, psCoreProps->ui32NumPixelPipes) )
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: VIDEO STANDARD (REAL)",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32StrConfig |= VDECDD_UNSUPPORTED_STRCONFIG_STD;
                }
                break;

            case VDEC_STD_VC1:
                if (!decoder_IsSupportedByAtLeastOnePipe(psCoreProps->abVc1, psCoreProps->ui32NumPixelPipes) )
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: VIDEO STANDARD (VC-1)",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32StrConfig |= VDECDD_UNSUPPORTED_STRCONFIG_STD;
                }
                break;

            case VDEC_STD_VP6:
                if (!decoder_IsSupportedByAtLeastOnePipe(psCoreProps->abVp6, psCoreProps->ui32NumPixelPipes))
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: VIDEO STANDARD (VP6)",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32StrConfig |= VDECDD_UNSUPPORTED_STRCONFIG_STD;
                }
                break;

            case VDEC_STD_VP8:
                if (!decoder_IsSupportedByAtLeastOnePipe(psCoreProps->abVp8, psCoreProps->ui32NumPixelPipes) )
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: VIDEO STANDARD (VP8)",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32StrConfig |= VDECDD_UNSUPPORTED_STRCONFIG_STD;
                }
                break;

            case VDEC_STD_SORENSON:
                if (!decoder_IsSupportedByAtLeastOnePipe(psCoreProps->abSorenson, psCoreProps->ui32NumPixelPipes))
                {
                    IMG_WARN_ONCE("UNSUPPORTED: VIDEO STANDARD [SORENSON]\n");
                    psUnsupported->ui32StrConfig |= VDECDD_UNSUPPORTED_STRCONFIG_STD;
                }
                break;

            case VDEC_STD_HEVC:
                if (!decoder_IsSupportedByAtLeastOnePipe(psCoreProps->abHEVC, psCoreProps->ui32NumPixelPipes) )
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                           "[USERSID=0x%08X] UNSUPPORTED[HW]: VIDEO STANDARD (HEVC)",
                           psStrConfig->ui32UserStrId);
                    psUnsupported->ui32StrConfig |= VDECDD_UNSUPPORTED_STRCONFIG_STD;
                }
                if (psPictHdrInfo && psPictHdrInfo->sHEVCPictHdrInfo.bRangeExtPresent)
                {
                    if ((psPictHdrInfo->sHEVCPictHdrInfo.bIsFullRangeExt && // full support
                        !decoder_IsSupportedByAtLeastOnePipe(psCoreProps->bHevcRangeExt, psCoreProps->ui32NumPixelPipes)) ||
                        (!psPictHdrInfo->sHEVCPictHdrInfo.bIsFullRangeExt && // partial support
                        psCoreProps->asVidStdProps[psStrConfig->eVidStd].eMaxChromaFormat < PIXEL_FORMAT_444))
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                               "[USERSID=0x%08X] UNSUPPORTED[HW]: HEVC RANGE EXTENSIONS",
                               psStrConfig->ui32UserStrId);
                        psUnsupported->ui32PictHdr |= VDECDD_UNSUPPORTED_PICTHDR_HEVC_RANGE_EXT;
                    }
                }
                break;

            default:
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: VIDEO STANDARD (UNKNOWN)",
                        psStrConfig->ui32UserStrId);
                psUnsupported->ui32StrConfig |= VDECDD_UNSUPPORTED_STRCONFIG_STD;
                break;
            }
        }

        if (psOutputConfig)
        {
            // Ensure that each display feature is supported by the hardware.
            if (psOutputConfig->eRotMode != VDEC_ROTATE_0 && !decoder_IsSupportedByAtLeastOnePipe(psCoreProps->abRotationSupport, psCoreProps->ui32NumPixelPipes))
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                    "[USERSID=0x%08X] UNSUPPORTED[HW]: ROTATION",
                    psStrConfig->ui32UserStrId);
                psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_ROTATION;
            }

            if (psOutputConfig->bScale && !decoder_IsSupportedByAtLeastOnePipe(psCoreProps->abScalingSupport, psCoreProps->ui32NumPixelPipes))
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                    "[USERSID=0x%08X] UNSUPPORTED[HW]: SCALING",
                    psStrConfig->ui32UserStrId);
                psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_SCALING;
            }
            if (psComSequHdrInfo)
            {

                /*if ((psComSequHdrInfo->sPixelInfo.eChromaFormatIdc != psOutputConfig->sPixelInfo.eChromaFormatIdc) &&
                    (psComSequHdrInfo->sPixelInfo.eChromaFormatIdc != PIXEL_FORMAT_420) &&
                    (psOutputConfig->sPixelInfo.eChromaFormatIdc != PIXEL_FORMAT_422))

                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[SW]: UP/DOWN-SAMPLING",
                        psStrConfig->ui32UserStrId);
                        psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_UP_DOWNSAMPLING;
                }*/
                //Validate display pixel format
                switch(psOutputConfig->sPixelInfo.eChromaFormatIdc)
                {
                case PIXEL_FORMAT_MONO:

                    if(psComSequHdrInfo->sPixelInfo.eChromaFormatIdc != PIXEL_FORMAT_MONO)
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                            "[USERSID=0x%08X] UNSUPPORTED[HW]: INVALID CODED-DISPLAY PIXEL FORMAT COMBINATION",
                            psStrConfig->ui32UserStrId);
                            psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_PIXFORMAT;
                    }
                    break;

                case PIXEL_FORMAT_420:

                    if(psComSequHdrInfo->sPixelInfo.eChromaFormatIdc == PIXEL_FORMAT_MONO)
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                            "[USERSID=0x%08X] UNSUPPORTED[HW]: TRANSFORM PIXEL FORMAT FROM 400 TO 420",
                            psStrConfig->ui32UserStrId);
                        psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_PIXFORMAT;
                    }
                    break;

                case PIXEL_FORMAT_422:

                    if(psComSequHdrInfo->sPixelInfo.eChromaFormatIdc == PIXEL_FORMAT_420)
                    {
                        if(!psCoreProps->bChromaUpsample)
                        {
                            REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                                "[USERSID=0x%08X] UNSUPPORTED[HW]: CHROMA UPSAMPLING",
                                psStrConfig->ui32UserStrId);
                            psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_PIXFORMAT;
                        }
                        else if(psOutputConfig->sPixelInfo.ui32NoPlanes > 1)
                        {
                            REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                                "[USERSID=0x%08X] UNSUPPORTED[HW]: REQUESTED NUMBER OF PLANES FOR 422 UPSAMPLING",
                                psStrConfig->ui32UserStrId);
                            psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_PIXFORMAT;
                        }
                    }
                    else if(psComSequHdrInfo->sPixelInfo.eChromaFormatIdc == PIXEL_FORMAT_MONO)
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                            "[USERSID=0x%08X] UNSUPPORTED[HW]: TRANSFORM PIXEL FORMAT FROM 400 TO 420",
                            psStrConfig->ui32UserStrId);
                    }
                    break;

                case PIXEL_FORMAT_444:

                    if(psComSequHdrInfo->sPixelInfo.eChromaFormatIdc != PIXEL_FORMAT_444)
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                            "[USERSID=0x%08X] UNSUPPORTED[HW]: CHROMA UPSAMPLING TO 444",
                            psStrConfig->ui32UserStrId);
                        psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_PIXFORMAT;
                    }

#if 0
                    else if((psOutputConfig->sPixelInfo.ui32NoPlanes != 0) ||
                            (psOutputConfig->sPixelInfo.ui32NoPlanes != 2) ||
                            (psOutputConfig->sPixelInfo.ui32NoPlanes != 3))
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                            "[USERSID=0x%08X] UNSUPPORTED[HW]: INVALID NUMBER OF PLANES[%d] FOR 444",
                            psStrConfig->ui32UserStrId,
                            psOutputConfig->sPixelInfo.ui32NoPlanes);
                        psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_PIXFORMAT;
                    }
#endif
                    break;
                default:
                    break;
                }

                if (psOutputConfig->bScale)
                {
                    if (psComSequHdrInfo->sOrigDisplayRegion.ui32TopOffset ||
                        psComSequHdrInfo->sOrigDisplayRegion.ui32LeftOffset)
                    {
                        IMG_WARN_ONCE("Cannot scale correctly with top or left crop");
                    }
                }
            }

            // Validate combintation of display features.
            if (psOutputConfig->bScale && psOutputConfig->bForceOold && !psCoreProps->bScalingWithOold)
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                    "[USERSID=0x%08X] UNSUPPORTED[HW]: SCALING WITH OOLD",
                    psStrConfig->ui32UserStrId);
                psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_SCALING_WITH_OOLD;
            }
            if (psOutputConfig->eRotMode != VDEC_ROTATE_0 && psOutputConfig->bScale)
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                    "[USERSID=0x%08X] UNSUPPORTED[HW]: ROTATION & SCALING",
                    psStrConfig->ui32UserStrId);
                psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_ROTATION_WITH_SCALING;
            }

            if(psComSequHdrInfo)
            {
                if((psOutputConfig->eRotMode != VDEC_ROTATE_0) &&
                    ( (psOutputConfig->sPixelInfo.eChromaFormatIdc != psComSequHdrInfo->sPixelInfo.eChromaFormatIdc) ||
                    (psOutputConfig->sPixelInfo.ui32BitDepthY != psComSequHdrInfo->sPixelInfo.ui32BitDepthY) ||
                    (psOutputConfig->sPixelInfo.ui32BitDepthC != psComSequHdrInfo->sPixelInfo.ui32BitDepthC)))
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: ROTATION AND DOWNSAMPLING",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_DOWNSAMPLING_WITH_ROTATION;
                }
                if((psOutputConfig->eRotMode != VDEC_ROTATE_0) &&
                    (psOutputConfig->sPixelInfo.eMemoryPacking != psComSequHdrInfo->sPixelInfo.eMemoryPacking))
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: ROTATION WITH 10 BIT PACKED FORMAT",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_ROTATION_WITH_10BIT_PACKED;
                }
            }

            if(psComSequHdrInfo)
            {
                if (psOutputConfig->eRotMode != VDEC_ROTATE_0)
                {
                    if( ( (psOutputConfig->sPixelInfo.eChromaFormatIdc == PIXEL_FORMAT_422) &&
                          (!((psComSequHdrInfo->sPixelInfo.eChromaFormatIdc == PIXEL_FORMAT_422) && (psOutputConfig->eRotMode == VDEC_ROTATE_180))) &&
                          (!((psComSequHdrInfo->sPixelInfo.eChromaFormatIdc == PIXEL_FORMAT_444) && (psOutputConfig->sPixelInfo.ui32NoPlanes == 3))) )  ||

                        ( (psOutputConfig->sPixelInfo.eChromaFormatIdc == PIXEL_FORMAT_444) && (psOutputConfig->sPixelInfo.ui32NoPlanes != 3) ) )
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                            "[USERSID=0x%08X] UNSUPPORTED[HW]: ROTATION WITH HIGH COLOUR DISPLAY PIXEL FORMAT",
                            psStrConfig->ui32UserStrId);
                        psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_ROTATION_WITH_HIGH_COLOUR;
                    }

                }
            }


            if (psOutputConfig->sScaledPictSize.ui32Width % 2 ||
                psOutputConfig->sScaledPictSize.ui32Height % 2)
            {
                // Must scale to even number of pixels in width and height.
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: SCALING TO AN ODD PIXEL RESOLUTION [%dx%d]",
                        psStrConfig->ui32UserStrId,
                        psOutputConfig->sScaledPictSize.ui32Width,
                        psOutputConfig->sScaledPictSize.ui32Height);
                psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_SCALING_SIZE;
            }

            if (psStrConfig &&
                (psOutputConfig->sPixelInfo.ui32BitDepthY > psCoreProps->asVidStdProps[psStrConfig->eVidStd].ui32MaxLumaBitDepth ||
                 psOutputConfig->sPixelInfo.ui32BitDepthY < 8 || psOutputConfig->sPixelInfo.ui32BitDepthY == 9))
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: DISPLAY PICTURE LUMA BIT DEPTH %d [RANGE: 8->%d for %s]",
                        psStrConfig->ui32UserStrId,
                        psOutputConfig->sPixelInfo.ui32BitDepthY,
                        psCoreProps->asVidStdProps[psStrConfig->eVidStd].ui32MaxLumaBitDepth,
                        gapszVidStd[psStrConfig->eVidStd]);
                psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_PIXFORMAT;
            }

			if(psComSequHdrInfo)
			{
				if (psComSequHdrInfo->sPixelInfo.eChromaFormatIdc != PIXEL_FORMAT_MONO &&
					(psOutputConfig->sPixelInfo.ui32BitDepthC > psCoreProps->asVidStdProps[psStrConfig->eVidStd].ui32MaxChromaBitDepth ||
					psOutputConfig->sPixelInfo.ui32BitDepthC < 8 || psOutputConfig->sPixelInfo.ui32BitDepthC == 9))
				{
					REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
						"[USERSID=0x%08X] UNSUPPORTED[HW]: DISPLAY PICTURE CHROMA BIT DEPTH %d [RANGE: 8->%d for %s]",
						psStrConfig->ui32UserStrId,
						psOutputConfig->sPixelInfo.ui32BitDepthC,
						psCoreProps->asVidStdProps[psStrConfig->eVidStd].ui32MaxChromaBitDepth,
						gapszVidStd[psStrConfig->eVidStd]);
					psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_PIXFORMAT;
				}
			}

            // Validate display configuration against existing stream configuration.
            if (psStrConfig->eVidStd == VDEC_STD_JPEG)
            {
                if (psOutputConfig->eRotMode != VDEC_ROTATE_0)
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: ROTATION WITH JPEG",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_X_WITH_JPEG;
                }
                if (psOutputConfig->bScale)
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: SCALING WITH JPEG",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_X_WITH_JPEG;
                }
                if (psOutputConfig->bForceOold)
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: OOLD WITH JPEG",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_X_WITH_JPEG;
                }
            }

            if (psComSequHdrInfo && psOutputConfig->bScale)
            {
                if (psCoreProps->BRN29797 && psComSequHdrInfo->sPixelInfo.eChromaFormatIdc == PIXEL_FORMAT_MONO)
                {
                    // Cannot scale monochrome bitstreams (BRN29797).
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: Cannot scale monochrome bitstreams (BRN29797)",
                        psStrConfig->ui32UserStrId);
                    psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_SCALING_MONOCHROME;
                }
            }
        }

        if (psDispPictRendInfo)
        {
            if (psReqPictRendInfo)
            {
                // Picture size declared in buffer must be at least as large as that required by bitstream/output config.
                if (!VDEC_SIZE_GE(psDispPictRendInfo->sRendPictSize, psReqPictRendInfo->sRendPictSize))
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_INFO,
                            "[USERSID=0x%08X] Picture size of output picture buffer [%dx%d] is not large enough for sequence [%dx%d]",
                            psStrConfig->ui32UserStrId,
                            psDispPictRendInfo->sRendPictSize.ui32Width, psDispPictRendInfo->sRendPictSize.ui32Height,
                            psReqPictRendInfo->sRendPictSize.ui32Width, psReqPictRendInfo->sRendPictSize.ui32Height);
                    psUnsupported->ui32OutputBufConfig |= VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_PICTURE_SIZE;
                }

                // Size of each plane must be at least as large as that required.
                if (psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Size < psReqPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Size)
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_INFO,
                            "[USERSID=0x%08X] Y plane of output picture buffer [%d bytes] is not large enough for bitstream/config [%d bytes]",
                            psStrConfig->ui32UserStrId,
                            psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Size,
                            psReqPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Size);
                    psUnsupported->ui32OutputBufConfig |= VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_Y_SIZE;
                }

                // Stride of each plane must be at least as large as that required.
                if (psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride < psReqPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride)
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_INFO,
                            "[USERSID=0x%08X] Y stride of output picture buffer [%d bytes] is not large enough for bitstream/config [%d bytes]",
                            psStrConfig->ui32UserStrId,
                            psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride,
                            psReqPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride);
                    psUnsupported->ui32OutputBufConfig |= VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_Y_STRIDE;
                }

                // Size of each plane must be at least as large as that required.
                if (psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Size < psReqPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Size)
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_INFO,
                            "[USERSID=0x%08X] UV plane of output picture buffer [%d bytes] is not large enough for bitstream/config [%d bytes]",
                            psStrConfig->ui32UserStrId,
                            psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Size,
                            psReqPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Size);
                    psUnsupported->ui32OutputBufConfig |= VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_UV_SIZE;
                }

                // Stride of each plane must be at least as large as that required.
                if (psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Stride < psReqPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Stride)
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_INFO,
                            "[USERSID=0x%08X] UV stride of output picture buffer [%d bytes] is not large enough for bitstream/config [%d bytes]",
                            psStrConfig->ui32UserStrId,
                            psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Stride,
                            psReqPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Stride);
                    psUnsupported->ui32OutputBufConfig |= VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_UV_STRIDE;
                }
            }

            if (psCoreProps->bExtendedStrides || psCoreProps->b64ByteFixedStrides)
            {
                if ((psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride % VDEC_MSVDX_EXT_STRIDE_ALIGNMENT) != 0)
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: Y STRIDE [%d] must be a multiple of %d bytes",
                        psStrConfig->ui32UserStrId,
                        psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride,
                        VDEC_MSVDX_EXT_STRIDE_ALIGNMENT);
                    psUnsupported->ui32OutputBufConfig |= VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_64BYTE_STRIDE;
                }
                if ((psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Stride % VDEC_MSVDX_EXT_STRIDE_ALIGNMENT) != 0)
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: UV STRIDE [%d] must be a multiple of %d bytes",
                        psStrConfig->ui32UserStrId,
                        psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Stride,
                        VDEC_MSVDX_EXT_STRIDE_ALIGNMENT);
                    psUnsupported->ui32OutputBufConfig |= VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_64BYTE_STRIDE;
                }
                if ((psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_V].ui32Stride % VDEC_MSVDX_EXT_STRIDE_ALIGNMENT) != 0)
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: V STRIDE [%d] must be a multiple of %d bytes",
                        psStrConfig->ui32UserStrId,
                        psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_V].ui32Stride,
                        VDEC_MSVDX_EXT_STRIDE_ALIGNMENT);
                    psUnsupported->ui32OutputBufConfig |= VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_64BYTE_STRIDE;
                }
            }

            if (!psCoreProps->bExtendedStrides)
            {
                IMG_UINT32 ui32RowStrideCode;

                IMG_ASSERT(psStrConfig);

                ui32RowStrideCode = VDECDDUTILS_GetStrideCode(
                                        psStrConfig->eVidStd,
                                        psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride);
                if (ui32RowStrideCode == -1)
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: Y STRIDE [%d] not in fixed set (extended strides not supported).",
                        psStrConfig->ui32UserStrId,
                        psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride);
                    psUnsupported->ui32OutputBufConfig |= VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_FIXED_STRIDE;
                }

                if (psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Size)
                {
                    ui32RowStrideCode = VDECDDUTILS_GetStrideCode(
                                            psStrConfig->eVidStd,
                                            psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Stride);
                    if (ui32RowStrideCode == -1)
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                            "[USERSID=0x%08X] UNSUPPORTED[HW]: UV STRIDE [%d] not in fixed set (extended strides not supported).",
                            psStrConfig->ui32UserStrId,
                            psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Stride);
                        psUnsupported->ui32OutputBufConfig |= VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_FIXED_STRIDE;
                    }
                }
                if (psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_V].ui32Size)
                {
                    ui32RowStrideCode = VDECDDUTILS_GetStrideCode(
                                            psStrConfig->eVidStd,
                                            psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_V].ui32Stride);
                    if (ui32RowStrideCode == -1)
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                            "[USERSID=0x%08X] UNSUPPORTED[HW]: V STRIDE [%d] not in fixed set (extended strides not supported).",
                            psStrConfig->ui32UserStrId,
                            psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_V].ui32Stride);
                        psUnsupported->ui32OutputBufConfig |= VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_FIXED_STRIDE;
                    }
                }

                if (!psCoreProps->b64ByteFixedStrides &&
                    psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride == 384)
                {
                    // to be the same as 64-byte strides except for this value 384 (replaced 352).
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: Y STRIDE [%d] not in fixed set (use 352 or larger)",
                        psStrConfig->ui32UserStrId,
                        psDispPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride);
                    psUnsupported->ui32OutputBufConfig |= VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_FIXED_STRIDE;
                }
            }

            if (psReqPictRendInfo)
            {
                if (psOutputConfig)
                {
                    if (psOutputConfig->sPixelInfo.ui32NoPlanes <= 2)
                    {
                        // V plane only required when chroma is separated.
                        IMG_ASSERT(psReqPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_V].ui32Size == 0);
                    }

                    if (psOutputConfig->sPixelInfo.ui32NoPlanes <= 3)
                    {
                        // Alpha planes should not be required.
                        IMG_ASSERT(psReqPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_A].ui32Size == 0);
                    }
                }

                // Size of buffer must be at least as large as that required.
                if (psDispPictRendInfo->ui32RenderedSize < psReqPictRendInfo->ui32RenderedSize)
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_INFO,
                            "[USERSID=0x%08X] Output picture buffer [%d bytes] is not large enough for bitstream/config [%d bytes]",
                            psStrConfig->ui32UserStrId,
                            psDispPictRendInfo->ui32RenderedSize,
                            psReqPictRendInfo->ui32RenderedSize);
                    psUnsupported->ui32OutputBufConfig |= VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_BUFFER_SIZE;
                }
            }

            if (psOutputConfig)
            {
                if (psOutputConfig->bScale)
                {
                    /* ...the picture size has to be at least the scaled picture size. */
                    if (!VDEC_SIZE_GE(psDispPictRendInfo->sRendPictSize, psOutputConfig->sScaledPictSize))
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                            "[USERSID=0x%08X] Picture buffers [%dx%d] must be allocated at least as large as the scaled picture size [%dx%d]",
                            psStrConfig->ui32UserStrId,
                            psDispPictRendInfo->sRendPictSize.ui32Width,
                            psDispPictRendInfo->sRendPictSize.ui32Height,
                            psOutputConfig->sScaledPictSize.ui32Width,
                            psOutputConfig->sScaledPictSize.ui32Height);
                        psUnsupported->ui32OutputBufConfig |= VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_PICTURE_SIZE;
                    }
                }
                else if (psComSequHdrInfo)
                {
                    if (VDEC_SIZE_LT(psDispPictRendInfo->sRendPictSize, psComSequHdrInfo->sMaxFrameSize))
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_INFO,
                            "[USERSID=0x%08X] Buffers [%dx%d] must be large enough to contain the maximum frame size [%dx%d] when not scaling",
                            psStrConfig->ui32UserStrId,
                            psDispPictRendInfo->sRendPictSize.ui32Width, psDispPictRendInfo->sRendPictSize.ui32Height,
                            psComSequHdrInfo->sMaxFrameSize.ui32Width, psComSequHdrInfo->sMaxFrameSize.ui32Height);
                        psUnsupported->ui32OutputBufConfig |= VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_PICTURE_SIZE;
                    }
                }
            }
        }

        if (psComSequHdrInfo)
        {
            if ((psComSequHdrInfo->sMaxFrameSize.ui32Width > MAX_PLATFORM_SUPPORTED_WIDTH) ||
                (psComSequHdrInfo->sMaxFrameSize.ui32Height > MAX_PLATFORM_SUPPORTED_HEIGHT))
            {
#if 0
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: FRAME HEIGHT %dpx or WIDTH %dpx are over maximum allowed value [%d, %d]",
                        psStrConfig->ui32UserStrId,
                        psComSequHdrInfo->sMaxFrameSize.ui32Width,
                        psComSequHdrInfo->sMaxFrameSize.ui32Height,
                        MAX_PLATFORM_SUPPORTED_WIDTH,
                        MAX_PLATFORM_SUPPORTED_HEIGHT);
#endif
                psUnsupported->ui32SequHdr |= VDECDD_UNSUPPORTED_SEQUHDR_SIZE;
            }

            if (psComSequHdrInfo->bInterlacedFrames)
            {
                // Coded height should be rounded to pairs of MBs in order to store field pictures.
                if (psComSequHdrInfo->sMaxFrameSize.ui32Height != VDEC_ALIGN_SIZE(psComSequHdrInfo->sMaxFrameSize.ui32Height, 2 * VDEC_MB_DIMENSION))
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: CODED HEIGHT %dpx not a multiple pair of MBs required for interlaced frame material [%dpx]",
                        psStrConfig->ui32UserStrId,
                        psComSequHdrInfo->sMaxFrameSize.ui32Height,
                        VDEC_ALIGN_SIZE(psComSequHdrInfo->sMaxFrameSize.ui32Height, 2 * VDEC_MB_DIMENSION));
                    psUnsupported->ui32SequHdr |= VDECDD_UNSUPPORTED_SEQUHDR_CODED_HEIGHT;
                }
            }

            if (psComSequHdrInfo->sPixelInfo.ui32BitDepthY > psCoreProps->asVidStdProps[psStrConfig->eVidStd].ui32MaxLumaBitDepth ||
                psComSequHdrInfo->sPixelInfo.ui32BitDepthY < 8 || psComSequHdrInfo->sPixelInfo.ui32BitDepthY == 9)
            {
                /*REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                    "[USERSID=0x%08X] UNSUPPORTED[HW]: CODED PICTURE LUMA BIT DEPTH %d [RANGE: 8->%d for %s]",
                    psStrConfig->ui32UserStrId,
                    psComSequHdrInfo->sPixelInfo.ui32BitDepthY,
                    psCoreProps->asVidStdProps[psStrConfig->eVidStd].ui32MaxLumaBitDepth,
                    gapszVidStd[psStrConfig->eVidStd]);*/
                psUnsupported->ui32SequHdr |= VDECDD_UNSUPPORTED_SEQUHDR_PIXFORMAT_BIT_DEPTH;
            }

            if (psComSequHdrInfo->sPixelInfo.eChromaFormatIdc != PIXEL_FORMAT_MONO &&
                (psComSequHdrInfo->sPixelInfo.ui32BitDepthC > psCoreProps->asVidStdProps[psStrConfig->eVidStd].ui32MaxChromaBitDepth ||
                psComSequHdrInfo->sPixelInfo.ui32BitDepthC < 8 || psComSequHdrInfo->sPixelInfo.ui32BitDepthC == 9))
            {
                /*REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                    "[USERSID=0x%08X] UNSUPPORTED[HW]: CODED PICTURE CHROMA BIT DEPTH %d [RANGE: 8->%d for %s]",
                    psStrConfig->ui32UserStrId,
                    psComSequHdrInfo->sPixelInfo.ui32BitDepthC,
                    psCoreProps->asVidStdProps[psStrConfig->eVidStd].ui32MaxChromaBitDepth,
                    gapszVidStd[psStrConfig->eVidStd]);*/
                psUnsupported->ui32SequHdr |= VDECDD_UNSUPPORTED_SEQUHDR_PIXFORMAT_BIT_DEPTH;
            }

            if (psComSequHdrInfo->sPixelInfo.eChromaFormatIdc != PIXEL_FORMAT_MONO &&
                psComSequHdrInfo->sPixelInfo.ui32BitDepthY != psComSequHdrInfo->sPixelInfo.ui32BitDepthC)
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                    "[USERSID=0x%08X] UNSUPPORTED[HW]: CODED PICTURE MIXED BIT DEPTH [%d vs %d]",
                    psStrConfig->ui32UserStrId,
                    psComSequHdrInfo->sPixelInfo.ui32BitDepthY,
                    psComSequHdrInfo->sPixelInfo.ui32BitDepthC);
                psUnsupported->ui32SequHdr |= VDECDD_UNSUPPORTED_SEQUHDR_PIXFORMAT_BIT_DEPTH;
            }

            if (psComSequHdrInfo->sPixelInfo.eChromaFormatIdc > psCoreProps->asVidStdProps[psStrConfig->eVidStd].eMaxChromaFormat)
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                    "[USERSID=0x%08X] UNSUPPORTED[HW]: CODED PIXEL FORMAT IDC %s [MAX = %s for %s]",
                    psStrConfig->ui32UserStrId,
                    psComSequHdrInfo->sPixelInfo.eChromaFormatIdc < VDEC_ARRAY_SIZE(acPixelFormatIdcNames) ?
                        acPixelFormatIdcNames[psComSequHdrInfo->sPixelInfo.eChromaFormatIdc] : "Invalid",
                    acPixelFormatIdcNames[psCoreProps->asVidStdProps[psStrConfig->eVidStd].eMaxChromaFormat],
                    gapszVidStd[psStrConfig->eVidStd]);
                psUnsupported->ui32SequHdr |= VDECDD_UNSUPPORTED_SEQUHDR_PIXEL_FORMAT;
            }

            if (psComSequHdrInfo->sPixelInfo.eChromaFormatIdc == PIXEL_FORMAT_INVALID)
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                    "[USERSID=0x%08X] UNSUPPORTED[SW]: UNKNOWN CODED PIXEL FORMAT",
                    psStrConfig->ui32UserStrId);
                psUnsupported->ui32SequHdr |= VDECDD_UNSUPPORTED_SEQUHDR_PIXEL_FORMAT;
            }
        }

        if (psPictHdrInfo && psComSequHdrInfo)
        {
            IMG_UINT32 ui32CodedCmdWidth;
            IMG_UINT32 ui32CodedCmdHeight;
            IMG_UINT32 ui32MinWidth = psCoreProps->asVidStdProps[psStrConfig->eVidStd].ui32MinWidth;
            IMG_UINT32 ui32MinHeight = VDEC_ALIGN_SIZE(psCoreProps->asVidStdProps[psStrConfig->eVidStd].ui32MinHeight, (psPictHdrInfo->bField) ? 2*VDEC_MB_DIMENSION : VDEC_MB_DIMENSION);
            IMG_UINT32 ui32PictSizeInMbs;
            IMG_UINT32 ui32MaxHeight = psCoreProps->asVidStdProps[psStrConfig->eVidStd].ui32MaxHeight;
            IMG_UINT32 ui32MaxWidth = psCoreProps->asVidStdProps[psStrConfig->eVidStd].ui32MaxWidth;
            IMG_UINT32 ui32MaxMBs = psCoreProps->asVidStdProps[psStrConfig->eVidStd].ui32MaxMacroblocks;

            /* For JPEG, max picture size of four plane images is 16k*16k. */
            if (psStrConfig->eVidStd == VDEC_STD_JPEG)
            {
                if (psComSequHdrInfo->sPixelInfo.ui32NoPlanes >= 4)
                {
                    ui32MaxWidth = (ui32MaxWidth > 16*1024) ? 16*1024 : ui32MaxWidth;
                    ui32MaxHeight = (ui32MaxHeight > 16*1024) ? 16*1024 : ui32MaxHeight;
                }
            }

            ui32CodedCmdWidth = VDEC_ALIGN_SIZE(psPictHdrInfo->sCodedFrameSize.ui32Width, VDEC_MB_DIMENSION);
            ui32CodedCmdHeight = VDEC_ALIGN_SIZE(psPictHdrInfo->sCodedFrameSize.ui32Height,
                                                (psPictHdrInfo->bField) ? 2*VDEC_MB_DIMENSION : VDEC_MB_DIMENSION);

            ui32PictSizeInMbs = (ui32CodedCmdWidth * ui32CodedCmdHeight) / (VDEC_MB_DIMENSION * VDEC_MB_DIMENSION);

            if ((psStrConfig->eVidStd == VDEC_STD_H264 &&
                ui32MaxMBs && ui32PictSizeInMbs > ui32MaxMBs) ||
                ui32CodedCmdWidth > ui32MaxWidth ||
                ui32CodedCmdHeight > ui32MaxHeight)
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: CODED PICTURE SIZE %dx%d [MAX: %dx%d or %d MBs]",
                        psStrConfig->ui32UserStrId,
                        ui32CodedCmdWidth, ui32CodedCmdHeight,
                        ui32MaxWidth, ui32MaxHeight, ui32MaxMBs);
                psUnsupported->ui32PictHdr |= VDECDD_UNSUPPORTED_PICTHDR_RESOLUTION;
            }

            if (psPictHdrInfo->sCodedFrameSize.ui32Width < ui32MinWidth ||
                psPictHdrInfo->sCodedFrameSize.ui32Height < ui32MinHeight)
            {
                IMG_WARN_ONCE("[USERSID=0x%08X] UNSUPPORTED[HW]: CODED PICTURE SIZE %dx%d [MIN: %dx%d]",
                              psStrConfig->ui32UserStrId,
                              psPictHdrInfo->sCodedFrameSize.ui32Width,
                              psPictHdrInfo->sCodedFrameSize.ui32Height,
                              ui32MinWidth, ui32MinHeight);
            }

            if (psStrConfig->eVidStd == VDEC_STD_MPEG4 ||
                psStrConfig->eVidStd == VDEC_STD_H263 ||
                psStrConfig->eVidStd == VDEC_STD_SORENSON)
            {
                if (ui32CodedCmdWidth > 2048 || ui32CodedCmdHeight > 2048)
                {
                    REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: CODED PICTURE SIZE %dx%d [MAX: %d] FOR EITHER DIMENSION FOR MPEG4",
                        psStrConfig->ui32UserStrId,
                        ui32CodedCmdWidth, ui32CodedCmdHeight,
                        2048);
                    psUnsupported->ui32PictHdr |= VDECDD_UNSUPPORTED_PICTHDR_RESOLUTION;
                }
                if (ui32CodedCmdWidth < 96 && psCoreProps->BRN40493)
                {
                   REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                        "[USERSID=0x%08X] UNSUPPORTED[HW]: CODED PICTURE WIDTH %d PRE-EMERALD HW DOES NOT SUPPORT MPEG4 STREAMS LESS THAN 96px WIDTH (BRN40493)",
                        psStrConfig->ui32UserStrId,
                        ui32CodedCmdWidth);
                   psUnsupported->ui32PictHdr |= VDECDD_UNSUPPORTED_PICTHDR_RESOLUTION;
                }
            }

            if (psPictHdrInfo->sPictSgmData.ui32Id != BSPP_INVALID && (psPictHdrInfo->sCodedFrameSize.ui32Width > 1280))
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                    "[USERSID=0x%08X] UNSUPPORTED[HW]: SGM & coded frame width > 1280",
                    psStrConfig->ui32UserStrId);
                psUnsupported->ui32PictHdr |= VDECDD_UNSUPPORTED_PICTHDR_OVERSIZED_SGM;
            }

            if (psPictHdrInfo->bDiscontinuousMbs)
            {

                DEBUG_REPORT(REPORT_MODULE_DECODER,
                            "Stream has Diccontineous Macroblocks");
            }

            if (psOutputConfig)
            {
                if (psOutputConfig->bScale)
                {
                    IMG_UINT32 ui32DisplayCmdWidth;
                    IMG_UINT32 ui32DisplayCmdHeight;

                    ui32DisplayCmdWidth = psPictHdrInfo->sDispInfo.sEncDispRegion.ui32Width +
                                              psPictHdrInfo->sDispInfo.sEncDispRegion.ui32LeftOffset;
                    ui32DisplayCmdHeight = psPictHdrInfo->sDispInfo.sEncDispRegion.ui32Height +
                                              psPictHdrInfo->sDispInfo.sEncDispRegion.ui32TopOffset;

                    // Scaling to a larger size than the display picture.
                    if (psOutputConfig->sScaledPictSize.ui32Width > ui32DisplayCmdWidth ||
                        psOutputConfig->sScaledPictSize.ui32Height > ui32DisplayCmdHeight)
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                            "[USERSID=0x%08X] UNSUPPORTED[HW]: UPSCALING [%dx%d] to [%dx%d]",
                            psStrConfig->ui32UserStrId,
                            ui32DisplayCmdWidth,
                            ui32DisplayCmdHeight,
                            psOutputConfig->sScaledPictSize.ui32Width,
                            psOutputConfig->sScaledPictSize.ui32Height);
                        psUnsupported->ui32PictHdr |= VDECDD_UNSUPPORTED_PICTHDR_UPSCALING;
                    }

                    if (ui32DisplayCmdWidth < 64UL || ui32DisplayCmdHeight < 64UL)
                    {
                        // Cannot scale when original display resolution is less than 4x4 MBs.
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                            "[USERSID=0x%08X] UNSUPPORTED[HW]: Cannot scale down from [%dx%d]. MIN [64x64]",
                            psStrConfig->ui32UserStrId,
                            ui32DisplayCmdWidth, ui32DisplayCmdHeight);
                        psUnsupported->ui32PictHdr |= VDECDD_UNSUPPORTED_PICTHDR_SCALING_ORIGINALSIZE;
                    }

                    if (psOutputConfig->sScaledPictSize.ui32Width % 2)
                    {
                        // Must scale to even number of pixels in width.
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                                "[USERSID=0x%08X] UNSUPPORTED[HW]: SCALING WIDTH MUST BE MULTIPLE OF 2 [%dx%d]",
                                psStrConfig->ui32UserStrId,
                                psOutputConfig->sScaledPictSize.ui32Width,
                                psOutputConfig->sScaledPictSize.ui32Height);
                        psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_PICTHDR_SCALING_SIZE;
                    }

                    if (psOutputConfig->sScaledPictSize.ui32Height % (psPictHdrInfo->bField?4:2))
                    {
                        // Must scale to even number of pixels in field height (even pair in frame height).
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                                "[USERSID=0x%08X] UNSUPPORTED[HW]: SCALING HEIGHT MUST BE MULTIPLE OF 2 OR FIELD-CODED 4 [%dx%d]",
                                psStrConfig->ui32UserStrId,
                                psOutputConfig->sScaledPictSize.ui32Width,
                                psOutputConfig->sScaledPictSize.ui32Height);
                        psUnsupported->ui32StrOutputConfig |= VDECDD_UNSUPPORTED_PICTHDR_SCALING_SIZE;
                    }

                    if( (((1UL << (psCoreProps->ui32ScalingPrecision + 3)) - 1) * psOutputConfig->sScaledPictSize.ui32Width < ((1UL << psCoreProps->ui32ScalingPrecision) * ui32DisplayCmdWidth) ) ||
                        (((1UL << (psCoreProps->ui32ScalingPrecision + 3)) - 1) * psOutputConfig->sScaledPictSize.ui32Height < ((1UL << psCoreProps->ui32ScalingPrecision) * ui32DisplayCmdHeight) ))
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                            "[USERSID=0x%08X] UNSUPPORTED[HW]: Cannot scale down that far [%dx%d] to [%dx%d]",
                            psStrConfig->ui32UserStrId,
                            ui32DisplayCmdWidth,
                            ui32DisplayCmdHeight,
                            psOutputConfig->sScaledPictSize.ui32Width,
                            psOutputConfig->sScaledPictSize.ui32Height);
                        psUnsupported->ui32PictHdr |= VDECDD_UNSUPPORTED_PICTHDR_SCALING_SIZE;
                    }

                    if (psCoreProps->BRN32651 && (psPictHdrInfo->sCodedFrameSize.ui32Width % 2))
                    {
                        // When this workaround is required the hardware will not generate
                        // correct output to match against golden with odd input width.
                        IMG_WARN_ONCE("[USERSID=0x%08X] UNSUPPORTED[HW]: Scaled output may slightly mismatch. Odd pixel width (BRN32651)",psStrConfig->ui32UserStrId);
                    }

                    // When display picture height is 2048, vertical start position must
                    // be set to zero (in scaler_setup.c) to avoid overflow when calculating
                    // last pixel position (BRN29870).
                    if (psCoreProps->BRN29870 && ui32DisplayCmdHeight == 2048)
                    {
                        IMG_WARN_ONCE("[USERSID=0x%08X] UNSUPPORTED[HW]: Scaled output may slightly mismatch. 2048px display picture width (BRN29870)",psStrConfig->ui32UserStrId);
                    }

                    if (psCoreProps->BRN29871 &&
                        psStrConfig->eVidStd == VDEC_STD_MPEG2 &&
                        ui32DisplayCmdHeight <= (ui32CodedCmdHeight - 16))
                    {
                        IMG_WARN_ONCE("[USERSID=0x%08X] UNSUPPORTED[HW]: Scaled output may slightly mismatch. MPEG2 stream with display height at least 1MB less than coded height (BRN29871)",psStrConfig->ui32UserStrId);

                        // Application should:
                        // 1. increase display height by +4 and
                        // 2. increase size of scaled output size by +6 before calculating the vertical pitch.
                        // Clip height of scaled output by 6 pixels which will remove the 4 additional pixels in
                        // the display picture height and 2 pixels which may have used invalid data inot the bottom 2 rows filtered.
                    }

                    if ((psCoreProps->BRN30178 || psCoreProps->BRN30306) &&
                        (psStrConfig->eVidStd == VDEC_STD_MPEG2 || psStrConfig->eVidStd == VDEC_STD_MPEG4 ||
                        psStrConfig->eVidStd == VDEC_STD_H263 || psStrConfig->eVidStd == VDEC_STD_SORENSON))
                    {
                        if ((ui32DisplayCmdHeight == (ui32CodedCmdHeight - 15)) ||
                            (ui32DisplayCmdHeight == (ui32CodedCmdHeight - 14)))
                        {
                            IMG_WARN_ONCE("[USERSID=0x%08X] UNSUPPORTED[HW]: Scaled output may slightly mismatch. MPEG2/4 stream with display height close to 1MB less than coded height (BRN30178/BRN30306)",psStrConfig->ui32UserStrId);

                            // Application should:
                            // 1. increase the display picture height to make it exactly 4 pixels into the last whole MB
                            //    defined by coded height (i.e. +3/+2 respectively) and
                            // 2. increase size of scaled output size by +4 before calculating the vertical pitch.
                            // Clip height of scaled output by 4 pixels which will remove the 2 additional pixels in
                            // the display picture height and 2 pixels which may have used invalid data inot the bottom 2 rows filtered.
                        }
                    }

                    if (psCoreProps->BRN30095)
                    {
                        if ((ui32DisplayCmdWidth == (ui32CodedCmdWidth - 13)) ||
                            (ui32DisplayCmdWidth == (ui32CodedCmdWidth - 12)))
                        {
                            IMG_WARN_ONCE("[USERSID=0x%08X] UNSUPPORTED[HW]: Scaled output may slightly mismatch. Display width close to 1MB less than coded width (BRN30095)", psStrConfig->ui32UserStrId);

                            // No intention to workaround.
                        }
                    }
                }

                if (psComSequHdrInfo)
                {
                    if (psOutputConfig->eRotMode != VDEC_ROTATE_0 &&
                        (psPictHdrInfo->bField || psComSequHdrInfo->bFieldCodedMBlocks ||
                        (psStrConfig->eVidStd == VDEC_STD_VC1 && psPictHdrInfo->sVC1PictHdrInfo.bInterlacedFrame)))
                    {
                        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                            "[USERSID=0x%08X] UNSUPPORTED[HW]: ROTATION OF FIELD CODED PICTURE",
                            psStrConfig->ui32UserStrId);
                        psUnsupported->ui32PictHdr |= VDECDD_UNSUPPORTED_OUTPUTCONFIG_ROTATION_WITH_FIELDS;
                    }
                }
            }

            decoder_GetRequiredCoreFeatures(psStrConfig, psOutputConfig, pui32Features);
        }

        if (psUnsupported->ui32StrConfig == 0 &&
            psUnsupported->ui32StrOutputConfig == 0 &&
            psUnsupported->ui32OutputBufConfig == 0 &&
            //psUnsupported->ui32SequHdr == 0 &&
            psUnsupported->ui32PictHdr == 0)
        {
            ui32Result = IMG_SUCCESS;
            break;
        }
    }

error:
    return ui32Result;
}



/*!
******************************************************************************

 @Function              DECODER_StreamCreate

******************************************************************************/
IMG_RESULT
DECODER_StreamCreate(
    IMG_HANDLE              hDecCtx,
    VDEC_sStrConfigData     sStrConfig,
    IMG_HANDLE            * phMmuStrHandle,
    IMG_VOID              * pvStrUserData,
    IMG_VOID              * pvStrUserIntData,
    IMG_HANDLE            * phDecStrCtx
)
{
    DECODER_sContext *     psDecCtx = (DECODER_sContext*)hDecCtx;
    DECODER_sStrContext *  psDecStrCtx;
    IMG_UINT32             ui32I;
    IMG_RESULT             ui32Result;
    VXDIO_sMemPool         sInsecureMemPool;

    /* Check input parameters. */
    IMG_ASSERT(IMG_NULL != hDecCtx);
    if(hDecCtx == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    if(psDecCtx->ui32StrCnt >= MAX_CONCURRENT_STREAMS)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "Device has too many concurrent streams. Number of Concurrent streams allowed: %d.",
            MAX_CONCURRENT_STREAMS);
        return IMG_ERROR_DEVICE_UNAVAILABLE;
    }
    
    sInsecureMemPool.eMemPoolId = psDecCtx->eInsecurePool;
    sInsecureMemPool.eMemPoolType = VXDIO_MEMPOOL_INSECURE;

    VDEC_MALLOC(psDecStrCtx);
    IMG_ASSERT(psDecStrCtx);
    if (psDecStrCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "[USERSID=0x%08X] Failed to allocate memory for Decoder stream context",
            sStrConfig.ui32UserStrId);
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    // Increment the stream counter
    psDecCtx->ui32StrCnt++;

    // Initialise the context structure to NULL. Any non-zero
    // default values should be set at this point.
    VDEC_BZERO(psDecStrCtx);
    psDecStrCtx->sConfig = sStrConfig;
    psDecStrCtx->pvUserData = pvStrUserData;
    psDecStrCtx->pvUserIntData = pvStrUserIntData;
    psDecStrCtx->psDecCtx = psDecCtx;

    psDecStrCtx->ui32NextDecPictId = 1;
    psDecStrCtx->ui32NextPictIdExpected = 1;

    ui32Result = IDGEN_AllocId(psDecCtx->hStrIdGen, psDecStrCtx, &psDecStrCtx->ui32StrId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }
    IMG_ASSERT(psDecStrCtx->ui32StrId > 0);

    LST_init(&psDecStrCtx->sPendStrUnitList);
    DQ_init(&psDecStrCtx->sStrDecdPictList);
    LST_init(&psDecStrCtx->sRefResList);
    LST_init(&psDecStrCtx->sDecResList);

    ui32Result = IDGEN_CreateContext(DECODER_MAX_PICT_ID + 1, /* IDGEN will allocate ids < DECODER_MAX_PICT_ID while we need <= DECODER_MAX_PICT_ID so add 1 */
                        DECODER_MAX_CONCURRENT_PICT,
                        IMG_TRUE,   /* We need incrementing Ids */
                        &psDecStrCtx->hPictIdGen);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    /* Create an MMU context for this stream. */
    ui32Result = MMU_StreamCreate(psDecCtx->hMmuDevHandle,
                                  &psDecStrCtx->hMmuStrHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

#ifdef VDEC_USE_PVDEC
    // Allocate memory to store stream context PTD.
    ui32Result = MMU_StreamMalloc(psDecStrCtx->hMmuStrHandle,
                                  MMU_HEAP_STREAM_BUFFERS,
                                  sInsecureMemPool,    //MMU Page table always in insicure memory
                                  sizeof(IMG_UINT32),
                                  DEV_MMU_PAGE_ALIGNMENT,
                                  &psDecStrCtx->sPtdBufInfo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    // Obtain PTD physical address
    MMU_StreamWritePtdToMem(psDecStrCtx->hMmuStrHandle,
                            &psDecStrCtx->sPtdBufInfo);
#else
    // Obtain PTD physical address
    MMU_StreamWritePtdToMem(psDecStrCtx->hMmuStrHandle,
                            &psDecStrCtx->sPtdBufInfo);
#endif
#ifdef VDEC_USE_PVDEC
    /* Allocate the PVDEC firmware context buffer */
    ui32Result = MMU_StreamMalloc(psDecStrCtx->hMmuStrHandle,
            MMU_HEAP_STREAM_BUFFERS,
            sInsecureMemPool,
            CONTEXT_BUFF_SIZE,
            DEV_MMU_PAGE_ALIGNMENT,
            &psDecStrCtx->sPvdecFwCtxBuf);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    // Clear the context data in preparation for first time use by the firmware.
    IMG_MEMSET(psDecStrCtx->sPvdecFwCtxBuf.pvCpuVirt, 0, psDecStrCtx->sPvdecFwCtxBuf.ui32BufSize);
    UPDATE_DEVICE((&psDecStrCtx->sPvdecFwCtxBuf), IMG_TRUE);
#endif /* VDEC_USE_PVDEC */
    // Create enough device resources to hold last context on
    // front and back-end for stream.
    psDecStrCtx->ui32NumDecRes = psDecStrCtx->psDecCtx->ui32NumCores * psDecStrCtx->psDecCtx->psDevConfig->ui32NumSlotsPerPipe * psDecStrCtx->psDecCtx->ui32NumPipes;
    for (ui32I = 0; ui32I < psDecStrCtx->ui32NumDecRes + 2; ui32I++)
    {
        ui32Result = decoder_StreamDecodeResourceCreate(psDecStrCtx);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }
    }

    LST_add(&psDecCtx->sStreamList, psDecStrCtx);

    *phDecStrCtx = (IMG_HANDLE)psDecStrCtx;
    *phMmuStrHandle = psDecStrCtx->hMmuStrHandle;

    return IMG_SUCCESS;

    /* Roll back in case of errors. */
error:
    DECODER_StreamDestroy((IMG_HANDLE)psDecStrCtx);

    return ui32Result;
}


#ifdef USE_REAL_FW

#ifdef WIN32
    /*! DMAC_LinkElement alignment not required under Windows. */
#   define DMAC_ALIGN_16_BYTE
#else
    /*! DMAC_LinkElement must be 16-byte alligned */
#   define DMAC_ALIGN_16_BYTE       __attribute__ ((aligned (16)))
#endif

/*! Hardware defined of fields of linked list element */
typedef struct
{
    IMG_UINT32  ui32DMAWord_0;      /*!< Word 0 of DMA linked-list. */
    IMG_UINT32  ui32DMAWord_1;      /*!< Word 1 of DMA linked-list. */
    IMG_UINT32  ui32DMAWord_2;      /*!< Word 2 of DMA linked-list. */
    IMG_UINT32  ui32DMAWord_3;      /*!< Word 3 of DMA linked-list. */
    IMG_UINT32  ui32DMAWord_4;      /*!< Word 4 of DMA linked-list. */
    IMG_UINT32  ui32DMAWord_5;      /*!< Word 5 of DMA linked-list. */
    IMG_UINT32  ui32DMAWord_6;      /*!< Word 6 of DMA linked-list. */
    IMG_UINT32  ui32DMAWord_7;      /*!< Word 7 of DMA linked-list. */
} DMAC_LinkElement DMAC_ALIGN_16_BYTE;

/*!
******************************************************************************

 @Function              decoder_GetFirmware

 @Description

 This function provides relevant firmware text, data, and relocation buffers
 according to configuration.

 Usage: only once during initialization, before RESOURCE_Create() and
        decoder_CoreEnumerate() calls.

 @Input     hMmuDevHandle           : MMU device context handle.

 @Input     psDevConfig             : Device configuration

 @Input     sMemPool                : Memory pool to use for allocations.

 @Input     abSupportedStandards    : Array of supported standards.

 @Output    psFw                    : Pointer to structure with firmware
                                      buffers configuration.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

 ******************************************************************************/
static IMG_RESULT
decoder_GetFirmware(
    IMG_HANDLE                  hMmuDevHandle,
    const VDECDD_sDdDevConfig * psDevConfig,
    VXDIO_sMemPool              sMemPool,
    IMG_BOOL                    abSupportedStandards[],
    MSVDXIO_sFw               * psFw
)
{
    IMG_RESULT  ui32Result = IMG_SUCCESS;
    IMG_UINT32  ui32Size;
#ifndef VDEC_USE_PVDEC
    IMG_UINT32  ui32I;
#endif /* VDEC_USE_PVDEC */

    VDEC_BZERO(psFw);

    /* Get the base firmware info. */
    ui32Result = VDECFW_GetBaseFirmware(&psFw->sFwBaseBinInfo,
                                        psDevConfig->bSingleStreamFw,
                                        psDevConfig->bOoldFw,
                                        psDevConfig->eSingleStreamStd);
    IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
               "Unable to obtain base firmware");
        return ui32Result;
    }

    /* Allocate buffer for firmware base text and data */
    ui32Size = (psFw->sFwBaseBinInfo.ui32TextBufSize + psFw->sFwBaseBinInfo.ui32DataSize) * sizeof(IMG_UINT32);

    if (ui32Size)
    {
        /* Start of MTX data section is aligned to 8 bytes. Align buffer size,
         * so potential 1 word gap between text and data can be filled: that's necessary
         * for DMA linked list operation (buffer has to be continuous) */
        ui32Size = VDEC_ALIGN_SIZE(ui32Size, 8);
        ui32Result = MMU_DeviceMalloc(hMmuDevHandle,
                                      MMU_HEAP_DEVICE_BUFFERS,
                                      sMemPool, //Secure if Secure allocation is possible
                                      ui32Size,
                                      DEV_MMU_PAGE_ALIGNMENT,
                                      &psFw->sFwBaseBufInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        ui32Result = MMU_DeviceMalloc(hMmuDevHandle,
                                      MMU_HEAP_DEVICE_BUFFERS,
                                      sMemPool, //Secure if Secure allocation is possible
                                      sizeof(VDECFW_sPsrModInfo) * VDECFW_CODEC_MAX,
                                      DEV_MMU_PAGE_ALIGNMENT,
                                      &psFw->sPsrModInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        /* Allocate buffer for DMA linked list */
        ui32Result = MMU_DeviceMalloc(hMmuDevHandle,
                                      MMU_HEAP_DEVICE_BUFFERS,
                                      sMemPool, //Secure if Secure allocation is possible
                                      sizeof(DMAC_LinkElement)*VDEC_DMAC_LL_BUFS_COUNT,
                                      DEV_MMU_PAGE_ALIGNMENT,
                                      &psFw->sDmaLLBufInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }

    /* Don't set modules info in single stream mode */
    if (psDevConfig->bSingleStreamFw)
    {
        return IMG_SUCCESS;
    }

    /*All parser modules for PVDEC are in blob, this is just for MSVDX*/
#ifndef VDEC_USE_PVDEC
    for (ui32I = 0; ui32I < VDEC_STD_MAX; ui32I++)
    {
        VDEC_eVidStd eStd = ui32I;

        if (abSupportedStandards[ui32I])
        {
            ui32Result = VDECFW_GetStdFirmware(&psFw->asFwBinModInfo[ui32I],
                                               ui32I,
                                               psDevConfig->bOoldFw);
            IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                   "Unable to obtain standard specific firmware");
                return ui32Result;
            }

            /* Allocate buffers for firmware modules text and data */
            if (psFw->asFwBinModInfo[eStd].ui32TextBufSize != 0)
            {
                IMG_UINT32 ui32DataSize = psFw->asFwBinModInfo[eStd].ui32DataSize;
#ifdef USE_FW_RELOC_INFO_PACKING
                ui32DataSize += psFw->asFwBinModInfo[eStd].ui32PackedRelocInfoSize;
#endif /* USE_FW_RELOC_INFO_PACKING */
                ui32DataSize *= sizeof(IMG_UINT32);

                ui32Result = MMU_DeviceMalloc(hMmuDevHandle,
                                              MMU_HEAP_DEVICE_BUFFERS,
                                              sMemPool, //Secure if Secure allocation is possible
                                              psFw->asFwBinModInfo[eStd].ui32TextBufSize * sizeof(IMG_UINT32),
                                              DEV_MMU_PAGE_ALIGNMENT,
                                              &psFw->asFwTextBufInfo[eStd]);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }

                ui32Result = MMU_DeviceMalloc(hMmuDevHandle,
                                              MMU_HEAP_DEVICE_BUFFERS,
                                              sMemPool, //Secure if Secure allocation is possible
                                              ui32DataSize,
                                              DEV_MMU_PAGE_ALIGNMENT,
                                              &psFw->asFwDataBufInfo[eStd]);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }
            }
        }
    }
#endif /*VDEC_USE_PVDEC*/

    return ui32Result;
}


/*!
******************************************************************************

 @Function              decoder_DestroyFirmware

 @Description


 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

 ******************************************************************************/
static IMG_RESULT
decoder_DestroyFirmware(
    MSVDXIO_sFw     * psFw
)
{
    IMG_UINT32      ui32I;
    IMG_UINT32      ui32Result;

    if (psFw->sFwBaseBufInfo.hMemory)
    {
        ui32Result = MMU_FreeMem(&psFw->sFwBaseBufInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        psFw->sFwBaseBufInfo.hMemory = IMG_NULL;
    }

    if (psFw->sPsrModInfo.hMemory)
    {
        ui32Result = MMU_FreeMem(&psFw->sPsrModInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        psFw->sPsrModInfo.hMemory = IMG_NULL;
    }

    if (psFw->sDmaLLBufInfo.hMemory)
    {
        ui32Result = MMU_FreeMem(&psFw->sDmaLLBufInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        psFw->sDmaLLBufInfo.hMemory = IMG_NULL;
    }

    for (ui32I = 0; ui32I < VDEC_STD_MAX; ui32I++)
    {
        if (psFw->asFwTextBufInfo[ui32I].hMemory)
        {
            ui32Result = MMU_FreeMem(&psFw->asFwTextBufInfo[ui32I]);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error;
            }

            psFw->asFwTextBufInfo[ui32I].hMemory = IMG_NULL;
        }

        if (psFw->asFwDataBufInfo[ui32I].hMemory)
        {
            ui32Result = MMU_FreeMem(&psFw->asFwDataBufInfo[ui32I]);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error;
            }

            psFw->asFwDataBufInfo[ui32I].hMemory = IMG_NULL;
        }
    }

    return IMG_SUCCESS;;

error:
    return ui32Result;
}

#endif /* USE_REAL_FW */

#ifdef STACK_USAGE_TEST
/*!
******************************************************************************

 @Function        DECODER_StackTest

 @Description    This function represents the entry point to Stack Usage Test.
                It calls the related HWCTRL function if the test is required.

 @Return        IMG_RESULT : This function returns either IMG_SUCCESS or an
                error code.

 ******************************************************************************/
IMG_RESULT DECODER_StackTest(
    IMG_HANDLE      hDecCtx
)
{
    IMG_RESULT ui32Result;
    DECODER_sContext * psDecCtx = (DECODER_sContext*)hDecCtx;

    /* If contex is not NULL and initialised and the test is required */
    if((IMG_NULL != psDecCtx)
    && (IMG_TRUE == psDecCtx->bInitialised)
    && (IMG_TRUE == psDecCtx->psDevConfig->bStackUsageTest))
    {
        DECODER_sCoreContext * psDecCoreCtx;

        /* Stream list should be empty */
        IMG_ASSERT(LST_empty(&psDecCtx->sStreamList));

        /* Remove and free all core context structures */
        psDecCoreCtx = LST_first(&psDecCtx->sCoreList);

        /* call HWCTRL function to get stack usage */
        ui32Result = HWCTRL_checkStackUsage(psDecCoreCtx->hHwCtx);
    }
    else
    {
        /* do not execute Stack Usage Test */
        /* return SUCCESS */
        ui32Result = IMG_SUCCESS;
    }

    return ui32Result;
}
#endif


/*!
******************************************************************************

 @Function              DECODER_Deinitialise

******************************************************************************/
IMG_RESULT DECODER_Deinitialise(
    IMG_HANDLE      hDecCtx
)
{
    DECODER_sContext * psDecCtx = (DECODER_sContext*)hDecCtx;
    IMG_RESULT ui32Result;

    if (psDecCtx && psDecCtx->bInitialised)
    {
        DECODER_sCoreContext * psDecCoreCtx;

        // Stream list should be empty.
        IMG_ASSERT(LST_empty(&psDecCtx->sStreamList));

        // Remove and free all core context structures
        psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
        while (psDecCoreCtx)
        {
            DECODER_sDecPict * psDecPict;

            // All cores should now be idle since there are no connections/streams.
            ui32Result = HWCTRL_PeekHeadPicList(psDecCoreCtx->hHwCtx, &psDecPict);
            IMG_ASSERT(ui32Result != IMG_SUCCESS);

            /* Power Off the core */
            ui32Result = HWCTRL_PowerOff(psDecCoreCtx->hHwCtx);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);

#ifdef USE_REAL_FW
            if (psDecCtx->sFw.sFwBaseBufInfo.hMemory)
            {
                /* Destroy firmware. */
                ui32Result = decoder_DestroyFirmware(&psDecCtx->sFw);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }
            }
#endif /* USE_REAL_FW */

            RESOURCES_Destroy(psDecCoreCtx->hResources);
            psDecCoreCtx = LST_next(psDecCoreCtx);
        }
        /* Free ptd buffer */
        ui32Result = MMU_FreeMem(&psDecCtx->sPtdBufInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        /* Destroy a device MMU context. */
        ui32Result = MMU_DeviceDestroy(psDecCtx->hMmuDevHandle);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        // Remove and free all core context structures
        psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
        while (psDecCoreCtx)
        {
            if(psDecCoreCtx->bAPM)
            {
                // Do a resume to shut down properly. Do not lock, it has been already locked previously
                DMANKM_ResumeDevice(psDecCoreCtx->psDecCtx->hDevHandle, IMG_FALSE);
                psDecCoreCtx->bAPM = IMG_FALSE;

            }
            HWCTRL_Deinitialise(psDecCoreCtx->hHwCtx);
            LST_remove(&psDecCtx->sCoreList, psDecCoreCtx);

            IMG_FREE(psDecCoreCtx);
            psDecCoreCtx = IMG_NULL;

            psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
        }

        IMG_ASSERT(psDecCtx->psDevConfig);
        if (psDecCtx->psDevConfig)
        {
            IMG_FREE((IMG_VOID*)psDecCtx->psDevConfig);
        }

        IDGEN_DestroyContext(psDecCtx->hStrIdGen);

        psDecCtx->pfnCompCallback = IMG_NULL;
        psDecCtx->pvCompInitUserData = IMG_NULL;

#ifdef FW_PERFORMANCE_LOGGING
#ifndef SYSBRG_BRIDGING
        PERFLOG_Deinitialise();
#endif
#endif
        psDecCtx->bInitialised = IMG_FALSE;

        IMG_FREE(psDecCtx);
    }
    else
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
            "Decoder has not been initialised so cannot be de-initialised");
        return IMG_ERROR_NOT_INITIALISED;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              DECODER_Replay

******************************************************************************/
IMG_RESULT DECODER_Replay(
    IMG_HANDLE      hDecCtx
)
{
    DECODER_sContext * psDecCtx = (DECODER_sContext*)hDecCtx;
    DECODER_sCoreContext *  psDecCoreCtx;
    IMG_RESULT ui32Result;
    DECODER_sDecPict * psDecPict;

    /* Check input parameters. */
    IMG_ASSERT(IMG_NULL != hDecCtx);

    psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
    while (psDecCoreCtx)
    {
        if (IMG_SUCCESS == HWCTRL_PeekHeadPicList(psDecCoreCtx->hHwCtx, &psDecPict))
        {
            if(psDecCoreCtx->bAPM)
            {
                DMANKM_ResumeDevice(psDecCoreCtx->psDecCtx->hDevHandle, IMG_TRUE);
                psDecCoreCtx->bAPM = IMG_FALSE;
            }

            ui32Result = HWCTRL_CoreReplay(psDecCoreCtx->hHwCtx);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }

        psDecCoreCtx = LST_next(psDecCoreCtx);
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              DECODER_ResetCores

******************************************************************************/
IMG_RESULT DECODER_ResetCores(
    IMG_HANDLE      hDecCtx
)
{
    DECODER_sContext * psDecCtx = (DECODER_sContext*)hDecCtx;
    DECODER_sCoreContext *  psDecCoreCtx;
    IMG_RESULT ui32Result;

    /* Check input parameters. */
    IMG_ASSERT(IMG_NULL != hDecCtx);

    psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
    while (psDecCoreCtx)
    {
        ui32Result = HWCTRL_PowerOff(psDecCoreCtx->hHwCtx);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        psDecCoreCtx = LST_next(psDecCoreCtx);
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              DECODER_PowerOff

******************************************************************************/
IMG_RESULT
DECODER_PowerOff(
    IMG_HANDLE          hDecCtx,
    IMG_BOOL            bForceAll
)
{
    DECODER_sContext *      psDecCtx = (DECODER_sContext *)hDecCtx;
    DECODER_sCoreContext *  psDecCoreCtx;
    IMG_UINT32  ui32Result;

    /* Check input parameters. */
    IMG_ASSERT(IMG_NULL != hDecCtx);
    if(hDecCtx == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
    while (psDecCoreCtx)
    {
        DECODER_sDecPict * psDecPict;
        ui32Result = IMG_SUCCESS;

        if(!bForceAll)
        {
            // Peek the head of the core decode queue to determine whether this
            // picture needs to be processed. If nothing, we can shut it down
            ui32Result = HWCTRL_PeekHeadPicList(psDecCoreCtx->hHwCtx, &psDecPict);
        }

        // If we are focing the cores to be turned off (PPM), or we have nothing on the core (APM)
        // Powering Off/On when we have one core. Need to change the interface to SYSDEVKM_ApmDeviceSuspend
        // to take Core ID as well to suspend all.
        if( (bForceAll || (ui32Result != IMG_SUCCESS)) && (psDecCtx->ui32NumCores == 1) )
        {
            // PrePower down steps
            ui32Result = HWCTRL_PowerOff(psDecCoreCtx->hHwCtx);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error;
            }
            if(!bForceAll && !psDecCoreCtx->bAPM)
            {
                // We are actively going down.
                DMANKM_SuspendDevice(psDecCoreCtx->psDecCtx->hDevHandle);
                psDecCoreCtx->bAPM = IMG_TRUE;
            }
        }

        psDecCoreCtx = LST_next(psDecCoreCtx);
    }

    return IMG_SUCCESS;

error:

    return ui32Result;
}


/*!
******************************************************************************

 @Function              DECODER_PrePowerOff

******************************************************************************/
IMG_RESULT
DECODER_PrePowerOff(
    IMG_HANDLE          hDecCtx
)
{
    IMG_UINT32  ui32Result;

    /* Check input parameters. */
    IMG_ASSERT(IMG_NULL != hDecCtx);

    ui32Result = DECODER_PowerOff(hDecCtx,IMG_TRUE);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

#if defined(VDEC_PM_EVENTS_INJECTION) && defined(VDEC_MSVDX_HARDWARE)
    {
        IMG_UINT32      ui32Offset;
        IMG_UINT32      ui32VecRamVal = 0;
        DECODER_sCoreContext *  psDecCoreCtx;
        DECODER_sContext *      psDecCtx = (DECODER_sContext *)hDecCtx;

        //clear VLR for each core
        psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
        while (psDecCoreCtx)
        {
            for (ui32Offset = 0; ui32Offset < VLR_SIZE; ui32Offset += 4)
            {
                MSVDXIO_VLRWriteWords(IMG_NULL, REGION_VLRFE_REGSPACE, ui32Offset, 1, &ui32VecRamVal );
            }

            psDecCoreCtx = LST_next(psDecCoreCtx);
        }
    }
#endif // VDEC_PM_EVENTS_INJECTION && VDEC_MSVDX_HARDWARE

    DEBUG_REPORT(REPORT_MODULE_DECODER,
                 "Decoder has performed pre power off operations");

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              DECODER_PostPowerOn

******************************************************************************/
IMG_RESULT
DECODER_PostPowerOn(
    IMG_HANDLE          hDecCtx
)
{
    DECODER_sContext *      psDecCtx = (DECODER_sContext *)hDecCtx;
    DECODER_sCoreContext *  psDecCoreCtx;
    IMG_RESULT ui32Result;
    DECODER_sDecPict * psDecPict;

    /* Check input parameters. */
    IMG_ASSERT(IMG_NULL != hDecCtx);

    psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
    while (psDecCoreCtx)
    {
        if (IMG_SUCCESS == HWCTRL_PeekHeadPicList(psDecCoreCtx->hHwCtx, &psDecPict))
        {
            ui32Result = HWCTRL_CoreReplay(psDecCoreCtx->hHwCtx);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }

        psDecCoreCtx = LST_next(psDecCoreCtx);
    }

    //IMG_ASSERT(IMG_FALSE);

    DEBUG_REPORT(REPORT_MODULE_DECODER,
                 "Decoder has performed post power on operations");

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              DECODER_CoreServiceTimerExpiry

******************************************************************************/
IMG_RESULT
DECODER_CoreServiceTimerExpiry(
    IMG_HANDLE  hDecCtx,
    IMG_UINT32  ui32CoreNum
)
{
    DECODER_sContext *      psDecCtx = (DECODER_sContext *)hDecCtx;
    DECODER_sCoreContext *  psDecCoreCtx;

    /* Check input parameters. */
    IMG_ASSERT(IMG_NULL != hDecCtx);

    psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
    while (psDecCoreCtx)
    {
        // find the effected core
        if ((psDecCoreCtx->ui32CoreNum == ui32CoreNum) && HWCTRL_HwStateIsLockUp(psDecCoreCtx->hHwCtx))
        {
            DECODER_CoreReset(hDecCtx, ui32CoreNum, RESET_DWR);

            DEBUG_REPORT(REPORT_MODULE_DECODER,
                         "Decoder has Serviced a Service Time Expiry");

            break;
        }

        psDecCoreCtx = LST_next(psDecCoreCtx);
    }

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              DECODER_CoreReset

******************************************************************************/
IMG_RESULT
DECODER_CoreReset(
    IMG_HANDLE  hDecCtx,
    IMG_UINT32  ui32CoreNum,
    VDECDD_eResetReason eReason
)
{

    IMG_UINT32  ui32Result = IMG_SUCCESS;
    DECODER_sContext *      psDecCtx = (DECODER_sContext *)hDecCtx;
    DECODER_sCoreContext *  psDecCoreCtx;

    /* Check input parameters. */
    IMG_ASSERT(IMG_NULL != hDecCtx);

    DEBUG_REPORT(REPORT_MODULE_DECODER,
                 "Decoder has started servicing a reset (reason=%d, core=%d)", eReason, ui32CoreNum);

    psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
    while (psDecCoreCtx)
    {
        if ((psDecCoreCtx->ui32CoreNum == ui32CoreNum))
        {
            ui32Result = HWCTRL_PowerOff(psDecCoreCtx->hHwCtx);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error;
            }

            // Throw away the picture
            ui32Result = HWCTRL_DiscardHeadPicList(psDecCoreCtx->hHwCtx);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error;
            }

            // Post a replay here
            ui32Result = HWCTRL_PostCoreReplay(psDecCoreCtx->hHwCtx);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error;
            }

            break;
        }

        psDecCoreCtx = LST_next(psDecCoreCtx);
    }

error:
    DEBUG_REPORT(REPORT_MODULE_DECODER,
                 "Decoder has serviced a reset (reason=%d, core=%d)", eReason, ui32CoreNum);

    return ui32Result;
}

/*!
******************************************************************************

 @Function              DECODER_CoreReplay

******************************************************************************/
IMG_RESULT
DECODER_CoreReplay(
    IMG_HANDLE  hDecCtx,
    IMG_UINT32  ui32CoreNum
)
{

    IMG_UINT32  ui32Result;
    DECODER_sContext *      psDecCtx = (DECODER_sContext *)hDecCtx;
    DECODER_sCoreContext *  psDecCoreCtx;

    /* Check input parameters. */
    IMG_ASSERT(IMG_NULL != hDecCtx);

    psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
    while (psDecCoreCtx)
    {
        // find the effected core
        if (psDecCoreCtx->ui32CoreNum == ui32CoreNum)
        {
            DECODER_sDecPict * psDecPict;
            ui32Result = IMG_SUCCESS;

            if (IMG_SUCCESS == HWCTRL_PeekHeadPicList(psDecCoreCtx->hHwCtx, &psDecPict))
            {
                if(psDecCoreCtx->bAPM)
                {
                    DMANKM_ResumeDevice(psDecCoreCtx->psDecCtx->hDevHandle, IMG_TRUE);
                    psDecCoreCtx->bAPM = IMG_FALSE;
                }
                ui32Result = HWCTRL_CoreReplay(psDecCoreCtx->hHwCtx);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }

            }
            break;
        }

        psDecCoreCtx = LST_next(psDecCoreCtx);
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              DECODER_CoreServiceInterrupt

******************************************************************************/
IMG_RESULT
DECODER_CoreServiceInterrupt(
    IMG_HANDLE      hDecServiceInt,
    IMG_VOID     ** ppvStrUserIntData
)
{
    IMG_RESULT ui32Result = IMG_SUCCESS;
    IMG_BOOL    bPictureDone = IMG_TRUE;

    // Picture processing done interrupt.
    if (bPictureDone)
    {
        IMG_BOOL bHeadOfQueue = IMG_TRUE;
        DECODER_sCoreContext * psDecCoreCtx;
        DECODER_sStrContext * psDecStrCtx;
        DECODER_sDecStrUnit * psDecStrUnit;
        DECODER_sDecPict * psDecPict = IMG_NULL;
        IMG_BOOL bPictStart = IMG_FALSE;
        VDECDD_eStrUnitType eStrUnitType;

        psDecCoreCtx = (DECODER_sCoreContext*)hDecServiceInt;

        // Peek the head of the core decode queue to determine whether this
        // picture needs to be processed.
#ifdef VDEC_USE_PVDEC
        if(psDecCoreCtx->sCoreProps.ui32NumPixelPipes != 1)
        {
            //multipipe: picture may have been decoded out of order
            ui32Result = HWCTRL_GetDecodedPicture(psDecCoreCtx->hHwCtx, &psDecPict);
        }
        else
#endif /* VDEC_USE_PVDEC */
        {
            //one pipe: decoded picture always at head
            ui32Result = HWCTRL_PeekHeadPicList(psDecCoreCtx->hHwCtx, &psDecPict);
        }
        IMG_ASSERT(ui32Result == IMG_SUCCESS && psDecPict);
        if (ui32Result != IMG_SUCCESS || psDecPict == IMG_NULL)
        {
            return IMG_SUCCESS;
        }

        // Try and locate the stream context in the list of active streams.
        psDecStrCtx = LST_first(&psDecCoreCtx->psDecCtx->sStreamList);
        while (psDecStrCtx)
        {
            if (psDecStrCtx == psDecPict->psDecStrCtx)
            {
                break;
            }

            psDecStrCtx = LST_next(psDecStrCtx);
        }

        // If the stream is not in the list of active streams then it must have been destroyed.
        // This interrupt should be ignored.
        if (psDecStrCtx != psDecPict->psDecStrCtx)
        {
            return IMG_SUCCESS;
        }

        // Retrieve the picture from the head of the core decode queue
        // primarily to obtain the correct stream context.
#ifdef VDEC_USE_PVDEC
        if(psDecCoreCtx->sCoreProps.ui32NumPixelPipes != 1)
        {
            //multipipe: picture may have been decoded out of order
            ui32Result = HWCTRL_RemoveFromPicList(psDecCoreCtx->hHwCtx, psDecPict);
        }
        else
#endif /* VDEC_USE_PVDEC */
        {
            //one pipe: decoded picture always at head
            ui32Result = HWCTRL_RemoveHeadPicList(psDecCoreCtx->hHwCtx, &psDecPict);
        }
        IMG_ASSERT(psDecPict);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS || psDecPict == IMG_NULL)
        {
            return IMG_ERROR_GENERIC_FAILURE;
        }

        // Store the stream context of the picture that has been decoded.
        psDecStrCtx = psDecPict->psDecStrCtx;
        IMG_ASSERT(IMG_NULL != psDecStrCtx);

        if(IMG_NULL != psDecStrCtx)
        {
            *ppvStrUserIntData = psDecStrCtx->pvUserIntData;

            // Peek the first stream unit and validate against core queue to ensure that
            // this really is the next picture for the stream.
            psDecStrUnit = LST_first(&psDecStrCtx->sPendStrUnitList);
            if (IMG_NULL != psDecStrUnit)
            {
                if(psDecStrUnit->psDecPict != psDecPict)
                {
                    //DECODER_sDecStrUnit * psPrevDecStrUnit = IMG_NULL;
                    bHeadOfQueue = IMG_FALSE;

                    // For pictures to be decoded out-of-order there must be
                    // more than one decoder core.
                    IMG_ASSERT(psDecStrCtx->psDecCtx->ui32NumCores > 1 || psDecStrCtx->psDecCtx->ui32NumPipes > 1);
                    while (psDecStrUnit)
                    {
                        psDecStrUnit = LST_next(psDecStrUnit);
                        if (psDecStrUnit->psDecPict == psDecPict)
                        {
                            break;
                        }
                    }
                }
                IMG_ASSERT(psDecStrUnit != IMG_NULL);
                if(psDecStrUnit == IMG_NULL)
                {
                    return IMG_ERROR_FATAL;
                }
                IMG_ASSERT(psDecStrUnit->psDecPict == psDecPict);
                IMG_ASSERT(psDecStrUnit->psStrUnit->eStrUnitType == VDECDD_STRUNIT_PICTURE_START);
            }

            // Process all units from the pending stream list until the next picture start.
            while (psDecStrUnit && !bPictStart)
            {
                // Actually remove the unit now from the pending stream list.
                LST_remove(&psDecStrCtx->sPendStrUnitList, psDecStrUnit);

                if(psDecStrUnit->psStrUnit)
                {
                    eStrUnitType = psDecStrUnit->psStrUnit->eStrUnitType;

                    if (eStrUnitType == VDECDD_STRUNIT_PICTURE_START)
                    {
                        VDECDD_sPicture * psPicture;
                        DECODER_sStrContext * psDecStrCtx = psDecPict->psDecStrCtx;

                        psDecStrCtx->sDecStrStatus.ui32NumPictDecoding--;
                        psDecStrCtx->sDecStrStatus.ui32TotalPictDecoded++;

                        ui32Result = IDGEN_GetHandle(psDecStrCtx->hPictIdGen,
                            GET_STREAM_PICTURE_ID(psDecStrUnit->psDecPict->ui32TransactionId),
                            (IMG_VOID **)&psPicture);
                        IMG_ASSERT(ui32Result == IMG_SUCCESS);
                        if (ui32Result != IMG_SUCCESS ||
                            psPicture == IMG_NULL)
                        {
                            REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                                   "[USERSID=0x%08X] Failed to find picture from ID",
                                   psDecStrCtx->sConfig.ui32UserStrId);
                            return IMG_ERROR_INVALID_ID;
                        }

                        IMG_ASSERT(psPicture == psDecStrUnit->psStrUnit->pvDdPictData);

                        // Hold a reference to the last context on the BE
                        if (psDecStrCtx->psLastBePictDecRes &&
                            HAS_X_PASSED_Y(psPicture->ui32PictId, GET_STREAM_PICTURE_ID(psDecStrCtx->psLastBePictDecRes->ui32TransactionId), 1 << FWIF_NUMBITS_STREAM_PICTURE_ID))
                        {
                            // Return previous last FW context.
                            RESOURCE_ItemReturn(&psDecStrCtx->psLastBePictDecRes->ui32RefCount);
#ifndef IMG_KERNEL_MODULE
                            if(RESOURCE_ItemIsAvailable(&psDecStrCtx->psLastBePictDecRes->ui32RefCount))
                            {
                                RESOURCE_ListRemove(&psDecStrCtx->sDecResList, psDecStrCtx->psLastBePictDecRes);
                                RESOURCE_ListAdd(&psDecStrCtx->sDecResList, psDecStrCtx->psLastBePictDecRes, 0, &psDecStrCtx->psLastBePictDecRes->ui32RefCount);
                            }
#endif
                        }

                        if (psDecStrCtx->psLastBePictDecRes == IMG_NULL ||
                            (psDecStrCtx->psLastBePictDecRes &&
                            HAS_X_PASSED_Y(psPicture->ui32PictId, GET_STREAM_PICTURE_ID(psDecStrCtx->psLastBePictDecRes->ui32TransactionId), 1 << FWIF_NUMBITS_STREAM_PICTURE_ID)))
                        {
                            // Hold onto last FW context.
                            psDecStrCtx->psLastBePictDecRes = psDecPict->psCurPictDecRes;
                            RESOURCE_ItemUse(&psDecStrCtx->psLastBePictDecRes->ui32RefCount);
                        }

                        RESOURCE_ItemReturn(&psDecPict->psCurPictDecRes->ui32RefCount);
#ifndef IMG_KERNEL_MODULE
                        if(RESOURCE_ItemIsAvailable(&psDecPict->psCurPictDecRes->ui32RefCount))
                        {
                            RESOURCE_ListRemove(&psDecStrCtx->sDecResList, psDecPict->psCurPictDecRes);
                            RESOURCE_ListAdd(&psDecStrCtx->sDecResList, psDecPict->psCurPictDecRes, 0, &psDecPict->psCurPictDecRes->ui32RefCount);
                        }
#endif
                        DEBUG_REPORT(REPORT_MODULE_DECODER,
                            "[USERSID=0x%08X] [TID=0x%08X] DECODED",
                            psDecStrCtx->sConfig.ui32UserStrId,
                            psDecPict->ui32TransactionId);

#if defined(FW_PERFORMANCE_LOGGING) && defined(VDEC_USE_PVDEC)
                        if(psDecCoreCtx->psDecCtx &&
                           psDecCoreCtx->psDecCtx->psDevConfig &&
                           psDecCoreCtx->psDecCtx->psDevConfig->bPerformanceLog)
                        {
                            //Dumping out Deva style XPL file here
                            ui32Result = decoder_SavePerfData(psDecStrUnit);
                            IMG_ASSERT(ui32Result == IMG_SUCCESS);
                            if (ui32Result != IMG_SUCCESS)
                            {
                                return ui32Result;
                            }
                        }
#endif /* defined(FW_PERFORMANCE_LOGGING) && defined(VDEC_USE_PVDEC) */

                        ui32Result = decoder_PictureDecoded(psDecStrCtx,
                                                            psPicture,
                                                            psDecPict->psFirstFieldFwMsg,
                                                            psDecPict->psSecondFieldFwMsg,
                                                            psDecPict->psPictRefRes,
                                                            psDecPict->ui32TransactionId);

                        IMG_ASSERT(ui32Result == IMG_SUCCESS);
                        if (ui32Result != IMG_SUCCESS)
                        {
                            return ui32Result;
                        }

                        RESOURCE_PictureDetach(&psDecCoreCtx->hResources,psDecPict);

                        // Free the segments from the decode picture
                        decoder_CleanBitStrSegments(&psDecPict->sDecPictSegList);
                        // Free decoder picture
                        IMG_FREE(psDecPict);
                        psDecPict = IMG_NULL;

                        bPictStart = (!bHeadOfQueue) ? IMG_TRUE : IMG_FALSE;
                    }
                    else
                    {
                        IMG_ASSERT(psDecStrUnit->psDecPict == IMG_NULL);
                    }

                    // Report that this unit has been processed.
                    ui32Result = psDecStrCtx->psDecCtx->pfnCompCallback(
                        DECODER_CB_UNIT_PROCESSED,
                        psDecStrCtx->psDecCtx->pvCompInitUserData,
                        IMG_NULL,
                        psDecStrCtx->pvUserData,
                        psDecStrUnit->psStrUnit);
                    IMG_ASSERT(ui32Result == IMG_SUCCESS);
                    if (ui32Result != IMG_SUCCESS)
                    {
                        return ui32Result;
                    }

                    // Destroy the Decoder stream unit wrapper.
                    IMG_FREE(psDecStrUnit);

                    // Peek at the next stream unit.
                    psDecStrUnit = LST_first(&psDecStrCtx->sPendStrUnitList);
                    if (psDecStrUnit)
                    {
                        bPictStart = (psDecStrUnit->psStrUnit->eStrUnitType == VDECDD_STRUNIT_PICTURE_START && psDecStrUnit->psDecPict != psDecPict);
                    }
                }
            }
        }
        else
        {
            ui32Result = IMG_ERROR_FATAL;
        }
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              decoder_MmuDeviceCallback

 @Description

 This function handles the VDECDD MMU device callback event.

 @Input     eEvent   : VDECDD MMU device callback event.

 @Input     pvDecCtx : Pointer to Decoder context.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

 ******************************************************************************/
static IMG_RESULT
decoder_MmuDeviceCallback(
    VDECDDMMU_eEvent    eEvent,
    IMG_VOID          * pvDecCtx
)
{
    DECODER_sContext      * psDecCtx = pvDecCtx;
    DECODER_sCoreContext  * psDecCoreCtx;
    IMG_RESULT              ui32Result;

    switch (eEvent)
    {
    case VDECDDMMU_EVENT_FLUSH_CACHE:
        // Cache will be flushed whenever a PTD or PTE is validated/invalidated (normally at start-up/shutdown).
        // Since memory could have been "seen" by multiple cores (frames scheduled on different cores) the cache
        // of all MMUs must be invalidated. Loop over all cores and flush MMU cache.
        psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
        while (psDecCoreCtx)
        {
            ui32Result = HWCTRL_CoreFlushMmuCache(psDecCoreCtx->hHwCtx);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            psDecCoreCtx = LST_next(psDecCoreCtx);
        }
        break;

    default:
        break;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              decoder_CoreEnumerate

 @Description

 This function enumerates a decoder core and returns its handle.

 Usage: before calls to other DECODE_Core or DECODE_Stream functions.

 @Input     psDecCtx : Pointer to Decoder context.

 @Input     ui32CoreNum : Core number.

 @Input     psDevConfig : Device configuration.

 @Output    pui32NumCores : Pointer to store number of cores. Only populated
                            for core number 0.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

 ******************************************************************************/
static IMG_RESULT
decoder_CoreEnumerate(
    DECODER_sContext          * psDecCtx,
    IMG_UINT32                  ui32CoreNum,
    const VDECDD_sDdDevConfig * psDevConfig,
    IMG_UINT32                * pui32NumCores,
    IMG_UINT32                * pui32NumPipes
)
{
    DECODER_sCoreContext  * psDecCoreCtx;
    HWCTRL_sRendec          sRendec;
    VXDIO_sDdBufInfo        asRendecBufInfo[2];
    IMG_UINT32              ui32Result;
    VXDIO_sMemPool          sSecurePool;
    VXDIO_sMemPool          sInsecureMemPool;
    IMG_UINT32              ui32PtdAlignment = DEV_MMU_PAGE_ALIGNMENT;

    /* Create the core. */
    VDEC_MALLOC(psDecCoreCtx);
    if (psDecCoreCtx == IMG_NULL)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "Failed to allocate memory for Decoder core context");
        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto error;
    }
    VDEC_BZERO(psDecCoreCtx);

    psDecCoreCtx->psDecCtx = psDecCtx;
    psDecCoreCtx->ui32CoreNum = ui32CoreNum;

    // Initialise the hwctrl block here
    ui32Result = HWCTRL_Initialise(psDecCoreCtx,
                                   psDecCtx->pvCompInitUserData,
                                   ui32CoreNum,
                                   psDevConfig,
                                   &psDecCoreCtx->sCoreProps,
                                   &sRendec,
                                   &psDecCoreCtx->hHwCtx);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    decoder_SetFeatureFlags(&psDecCoreCtx->sCoreProps, &psDecCoreCtx->ui32CoreFeatures, psDecCoreCtx->aui32PipeFeatures);

    sSecurePool.eMemPoolId = psDecCtx->eSecurePool;
    sSecurePool.eMemPoolType = VXDIO_MEMPOOL_SECURE;

    sInsecureMemPool.eMemPoolId = psDecCtx->eInsecurePool;
    sInsecureMemPool.eMemPoolType = VXDIO_MEMPOOL_INSECURE;

    // Perform device setup for master core.
    if (ui32CoreNum == VDECDD_MSVDX_CORE_MASTER)
    {
#ifndef IMG_KERNEL_MODULE
#define MAX_BYTES 1024
        IMG_CHAR acComment[MAX_BYTES];
        IMG_INT32 i32NumBytes;

        i32NumBytes = snprintf(acComment,
           MAX_BYTES,
           "INFO:\t[%s]\n"
           "-- INFO:\tAPM:%s\n"
           "-- INFO:\tCores:%u\n"
           "-- INFO:\tSlots:%u\n"
           "-- INFO:\tLevel:%s\n"
           "-- INFO:\tDWR:%ums\n"
           "-- INFO:\tFakeMTX:%s\n"
           "-- INFO:\tFEWDT:%u\n"
           "-- INFO:\tBEWDT:%u\n"
           "-- INFO:\tPSRWDT:%u\n"
           "-- INFO:\tRendec:%u bytes\n"
           "-- INFO:\tLockstep:%s\n"
           "-- INFO:\tPerfLog:%s\n"
           "-- INFO:\tOptimised:%s\n"
           "-- INFO:\tMemStallMin:%u\n"
           "-- INFO:\tMemStallMax:%u\n"
           "-- INFO:\tMemStallRatio:%u\n"
           "-- INFO:\tTiling:%s",
           "Device Configuration",
           (psDecCtx->psDevConfig->bAPM) ? "y" : "n",
           psDecCtx->ui32NumCores,
           psDecCtx->psDevConfig->ui32NumSlotsPerPipe,
           apszDecodeLevels[psDecCtx->psDevConfig->eDecodeLevel],
           psDecCtx->psDevConfig->ui32DwrPeriod,
           (psDecCtx->psDevConfig->bFakeMtx) ? "y" : "n",
           psDecCtx->psDevConfig->ui32FeWdtPeriod,
           psDecCtx->psDevConfig->ui32BeWdtPeriod,
           psDecCtx->psDevConfig->ui32PSRWdtPeriod,
           psDecCtx->psDevConfig->ui32RendecSize,
           (psDecCtx->psDevConfig->bLockStepDecode) ? "y" : "n",
           (psDecCtx->psDevConfig->bPerformanceLog) ? "y" : "n",
           (psDecCtx->psDevConfig->bOptimisedPerformance) ? "y" : "n",
           psDecCtx->psDevConfig->ui32MemoryStallingMin * 32,
           psDecCtx->psDevConfig->ui32MemoryStallingMax * 32,
           psDecCtx->psDevConfig->ui32MemoryStallingRatio * 10,
           (psDecCtx->psDevConfig->eTileScheme == VDEC_TS0_256x16) ? "0" :
           (psDecCtx->psDevConfig->eTileScheme == VDEC_TS1_512x8) ? "1" : "None");

        IMG_ASSERT(i32NumBytes > 0 && i32NumBytes < MAX_BYTES);

        // Write device configuration to master core.
        ui32Result = HWCTRL_PdumpComment(psDecCoreCtx->hHwCtx, acComment);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }
#endif

        psDecCoreCtx->bMaster = IMG_TRUE;
        IMG_ASSERT(psDecCoreCtx->sCoreProps.ui32NumCores <= VDECDD_MSVDX_CORE_MAX);
        if (pui32NumCores)
        {
            *pui32NumCores = psDecCoreCtx->sCoreProps.ui32NumCores;
        }
        if (pui32NumPipes)
        {
            *pui32NumPipes = psDecCoreCtx->sCoreProps.ui32NumPixelPipes;
        }

#ifdef VDEC_USE_PVDEC
        /* DEVA PVDEC FW requires PTD to be 64k aligned. */
        ui32PtdAlignment = 0x10000;
#endif /* VDEC_USE_PVDEC */
        /* Create a device MMU context. */
        ui32Result = MMU_DeviceCreate(psDecCoreCtx->sCoreProps.eMmuType,
                                      psDevConfig->eTileScheme,
                                      decoder_MmuDeviceCallback,
                                      sInsecureMemPool,
                                      psDecCtx,
                                      ui32PtdAlignment,
                                      &psDecCtx->hMmuDevHandle);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

#ifdef USE_REAL_FW
        /* Obtain firmware */
        ui32Result = decoder_GetFirmware(psDecCtx->hMmuDevHandle,
                                         psDevConfig,
                                         psDevConfig->bSecureMemoryAvailable ? sSecurePool : sInsecureMemPool,
                                         psDecCtx->abSupportedStandards,
                                         &psDecCtx->sFw);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }
#endif /* USE_REAL_FW */

        // Allocate memory to store stream context PTD.
        ui32Result = MMU_DeviceMalloc(psDecCtx->hMmuDevHandle,
                                      MMU_HEAP_DEVICE_BUFFERS,
                                      sInsecureMemPool,    //MMU Page table directory base address container always in insecure memory
                                      (MAX_CONCURRENT_STREAMS + 1) * sizeof(IMG_UINT32),    // Stream Ids start from 1. 0 is reserved for device PTD.
                                      DEV_MMU_PAGE_ALIGNMENT,
                                      &psDecCtx->sPtdBufInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        // Obtain PTD physical address
        ui32Result = MMU_DeviceWritePtdToMem(psDecCtx->hMmuDevHandle,
                                             &psDecCtx->sPtdBufInfo,
                                             &psDecCtx->sPtdInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }
    }

#ifndef IMG_KERNEL_MODULE
    ui32Result = HWCTRL_PdumpComment(psDecCoreCtx->hHwCtx, "<+ResourceCreate>");
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }
#endif

    // Create core resources.
    ui32Result = RESOURCE_Create(psDecCtx->hMmuDevHandle,
                                 &psDecCoreCtx->sCoreProps,
                                 &sRendec,
                                 psDecCtx->psDevConfig->ui32NumSlotsPerPipe * psDecCtx->ui32NumPipes,
                                 psDecCtx->psDevConfig->bSecureMemoryAvailable ? sSecurePool : sInsecureMemPool,
                                 sInsecureMemPool,
                                 asRendecBufInfo,
                                 &psDecCoreCtx->hResources);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

#ifndef IMG_KERNEL_MODULE
    ui32Result = HWCTRL_PdumpComment(psDecCoreCtx->hHwCtx, "<-ResourceCreate>");
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }
#endif

    ui32Result = HWCTRL_Configure(psDecCoreCtx->hHwCtx,
                                  &psDecCtx->sFw,
                                  asRendecBufInfo,
                                  &psDecCtx->sPtdBufInfo,
                                  &psDecCtx->sPtdInfo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    psDecCoreCtx->bEnumerated = IMG_TRUE;

    psDecCoreCtx->bAPM = IMG_FALSE;
    // make sure apm-ppm flags are reset
    DMANKM_ResetPowerManagementFlag(psDecCoreCtx->psDecCtx->hDevHandle);

    LST_add(&psDecCtx->sCoreList, psDecCoreCtx);

    return IMG_SUCCESS;

error:
    if (psDecCoreCtx)
    {
        IMG_UINT32 ui32DeinitResult = IMG_SUCCESS;

#ifdef USE_REAL_FW
        if (psDecCtx->sFw.sFwBaseBufInfo.hMemory)
        {
            /* Destroy firmware. */
            ui32DeinitResult = decoder_DestroyFirmware(&psDecCtx->sFw);
            if (ui32DeinitResult != IMG_SUCCESS)
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                    "decoder_DestroyFirmware() failed to tidy-up after error");
            }
        }
#endif /* USE_REAL_FW */

        if (psDecCoreCtx->hResources)
        {
            ui32DeinitResult = RESOURCES_Destroy(psDecCoreCtx->hResources);
            if (ui32DeinitResult != IMG_SUCCESS)
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                    "RESOURCES_Destroy() failed to tidy-up after error");
            }
        }

        IMG_FREE(psDecCoreCtx);
        psDecCoreCtx = IMG_NULL;
    }

    return ui32Result;
}



/*!
******************************************************************************

 @Function              DECODER_HandleInterrupt

******************************************************************************/
IMG_RESULT DECODER_HandleInterrupt(
    VDECDD_sDdDevContext *        psDdDevContext
)
{
    DECODER_sContext * psDecCtx;
    DECODER_sCoreContext * psDecCoreCtx;
    IMG_UINT32 ui32Result;

    /* Check input parameters. */
    IMG_ASSERT(psDdDevContext);
    if (psDdDevContext == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    psDecCtx = (DECODER_sContext *)psDdDevContext->hDecoderContext;

    // Determine which core this interrupt is for.
    psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
    while (psDecCoreCtx)
    {
        HWCTRL_HandleInterrupt(psDecCoreCtx->hHwCtx,psDdDevContext);
        psDecCoreCtx = LST_next(psDecCoreCtx);
    }

    return IMG_SUCCESS;

error:
    return ui32Result;
}



/*!
******************************************************************************

 @Function              DECODER_GetLoad

******************************************************************************/
IMG_RESULT DECODER_GetLoad(
    IMG_HANDLE          hDecCtx,
    IMG_UINT32          ui32CoreFeatures,
    IMG_UINT32        * pui32AvailLoad,
    IMG_UINT32        * pui32MinLoad
)
{
    DECODER_sContext  * psDecCtx = (DECODER_sContext*)hDecCtx;
    IMG_RESULT          ui32Result;

    ui32Result = decoder_GetCoreAndLoad(psDecCtx,
                                        ui32CoreFeatures,
                                        pui32AvailLoad,
                                        pui32MinLoad,
                                        IMG_NULL,
                                        IMG_NULL);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              DECODER_IsSupportedFeature

******************************************************************************/
IMG_RESULT DECODER_IsSupportedFeature(
    IMG_HANDLE          hDecCtx,
    VDEC_eFeature       eFeature,
    IMG_BOOL          * pbSupported
)
{
    DECODER_sContext * psDecCtx = (DECODER_sContext*)hDecCtx;
    DECODER_sCoreContext * psDecCoreCtx;
    IMG_BOOL bSupported = IMG_FALSE;

    /* Check input parameters. */
    IMG_ASSERT(IMG_NULL != hDecCtx);
    if(hDecCtx == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Ensure that Decoder component is initialised. */
    IMG_ASSERT(psDecCtx->bInitialised);

    /* Loop over all cores checking for support. */
    psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
    while (psDecCoreCtx)
    {
        // Determine whether the required core attribute
        // is present to support requested feature
        switch(eFeature)
        {
        case VDEC_FEATURE_H264:
                    bSupported |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_H264) ? IMG_TRUE : IMG_FALSE;
            break;

        case VDEC_FEATURE_MPEG2:
                    bSupported |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_MPEG2) ? IMG_TRUE : IMG_FALSE;
            break;

        case VDEC_FEATURE_MPEG4:
                    bSupported |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_MPEG4) ? IMG_TRUE : IMG_FALSE;
            break;

        case VDEC_FEATURE_VC1:
                    bSupported |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_VC1) ? IMG_TRUE : IMG_FALSE;
            break;

        case VDEC_FEATURE_AVS:
                    bSupported |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_AVS) ? IMG_TRUE : IMG_FALSE;
            break;

        case VDEC_FEATURE_REAL:
                    bSupported |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_REAL) ? IMG_TRUE : IMG_FALSE;
            break;

        case VDEC_FEATURE_JPEG:
                    bSupported |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_JPEG) ? IMG_TRUE : IMG_FALSE;
            break;

        case VDEC_FEATURE_VP6:
                    bSupported |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_VP6) ? IMG_TRUE : IMG_FALSE;
            break;

        case VDEC_FEATURE_VP8:
                    bSupported |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_VP8) ? IMG_TRUE : IMG_FALSE;
            break;

        case VDEC_FEATURE_HEVC:
                    bSupported |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_HEVC) ? IMG_TRUE : IMG_FALSE;
            break;

        case VDEC_FEATURE_HD_DECODE:
                    bSupported |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_HD_DECODE) ? IMG_TRUE : IMG_FALSE;
            break;

        case VDEC_FEATURE_ROTATION:
                    bSupported |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_ROTATION) ? IMG_TRUE : IMG_FALSE;
            break;

        case VDEC_FEATURE_SCALING:
                    bSupported |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_SCALING) ? IMG_TRUE : IMG_FALSE;
            break;

        case VDEC_FEATURE_SCALING_WITH_OOLD:
                    bSupported |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_SCALING_WITH_OOLD) ? IMG_TRUE : IMG_FALSE;
            break;

        case VDEC_FEATURE_EXTENDED_STRIDES:
                    bSupported |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_EXTENDED_STRIDES) ? IMG_TRUE : IMG_FALSE;
            break;

        default:
            IMG_ASSERT(IMG_FALSE);
            break;
        }

        psDecCoreCtx = LST_next(psDecCoreCtx);
    }

    *pbSupported = bSupported;

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              DECODER_SupportedFeatures

******************************************************************************/
IMG_RESULT DECODER_SupportedFeatures(
    IMG_HANDLE          hDecCtx,
    VDEC_sFeatures    * psFeatures
)
{
    DECODER_sContext * psDecCtx = (DECODER_sContext*)hDecCtx;
    DECODER_sCoreContext * psDecCoreCtx;

    /* Check input parameters. */
    IMG_ASSERT(IMG_NULL != hDecCtx);
    if(hDecCtx == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Ensure that Decoder component is initialised. */
    IMG_ASSERT(psDecCtx->bInitialised);

    /* Loop over all cores checking for support. */
    psDecCoreCtx = LST_first(&psDecCtx->sCoreList);
    while (psDecCoreCtx)
    {
        // Determine whether the required core attribute
        // is present to support requested feature
        psFeatures->bFeatureH264 |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_H264) ? IMG_TRUE : IMG_FALSE;
        psFeatures->bFeatureMPEG2 |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_MPEG2) ? IMG_TRUE : IMG_FALSE;
        psFeatures->bFeatureMPEG4 |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_MPEG4) ? IMG_TRUE : IMG_FALSE;
        psFeatures->bFeatureVC1 |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_VC1) ? IMG_TRUE : IMG_FALSE;
        psFeatures->bFeatureAVS |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_AVS) ? IMG_TRUE : IMG_FALSE;
        psFeatures->bFeatureREAL |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_REAL) ? IMG_TRUE : IMG_FALSE;
        psFeatures->bFeatureJPEG |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_JPEG) ? IMG_TRUE : IMG_FALSE;
        psFeatures->bFeatureVP6 |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_VP6) ? IMG_TRUE : IMG_FALSE;
        psFeatures->bFeatureVP8 |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_VP8) ? IMG_TRUE : IMG_FALSE;
        psFeatures->bFeatureHD |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_HD_DECODE) ? IMG_TRUE : IMG_FALSE;
        psFeatures->bFeatureRotation |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_ROTATION) ? IMG_TRUE : IMG_FALSE;
        psFeatures->bFeatureScaling |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_SCALING) ? IMG_TRUE : IMG_FALSE;
        psFeatures->bFeatureHEVC |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_HEVC) ? IMG_TRUE : IMG_FALSE;
        psFeatures->bFeatureScalingWithOOLD |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_SCALING_WITH_OOLD) ? IMG_TRUE : IMG_FALSE;
        psFeatures->bFeatureScalingExtendedStrides |= (psDecCoreCtx->ui32CoreFeatures & VDECDD_COREFEATURE_EXTENDED_STRIDES) ? IMG_TRUE : IMG_FALSE;

        psDecCoreCtx = LST_next(psDecCoreCtx);
    }
    return IMG_SUCCESS;
}


static const VDECDD_sDdDevConfig sDefaultDeviceConfig =
{
    VDECDD_DECODELEVEL_MAX,      /* eDecodeLevel;            */
    CORE_NUM_DECODE_SLOTS,       /* ui32NumSlotsPerPipe;     */
    IMG_FALSE,                   /* bAPM;                    */
    IMG_FALSE,                   /* bFakeMtx;                */
    4*1024*1024,                 /* ui32RendecSize;          */
    IMG_FALSE,                   /* bLockStepDecode;         */
    IMG_FALSE,                   /* bSecureMemoryAvailable;  */
    IMG_FALSE,                   /* bPerformanceLog;         */
    IMG_TRUE,                    /* bOptimisedPerformance;   */
    0,                           /* ui32MemoryStallingMin;   */
    0,                           /* ui32MemoryStallingMax;   */
    0,                           /* ui32MemoryStallingRatio; */
    CORE_DEFAULT_DWR_PERIOD,     /* ui32DwrPeriod;           */
    CORE_DEFAULT_DWR_JPEG_RETRY, /* ui32DwrJPEGRetry;        */
    CORE_DEFAULT_FE_TIMEOUT,     /* ui32FeWdtPeriod;         */
    CORE_DEFAULT_BE_TIMEOUT,     /* ui32BeWdtPeriod;         */
    CORE_DEFAULT_PSR_TIMEOUT,    /* ui32PSRWdtPeriod;        */
    IMG_FALSE,                   /* bCoreDump;               */
    IMG_FALSE,                   /* bPost;                   */
    IMG_FALSE,                   /* bStackUsageTest;         */
    IMG_FALSE,                   /* bSingleStreamFw;         */
    VDEC_STD_H264,               /* eSingleStreamStd;        */
    IMG_FALSE,                   /* bOoldFw;                 */
    VDEC_TS0_256x16,             /* eTileScheme;             */
    IMG_FALSE,                   /* bCSim;                   */
    IMG_FALSE,                   /* bPdumpAndRes;            */
};



/*!
******************************************************************************

 @Function              decoder_SetDeviceConfig

******************************************************************************/
static IMG_RESULT decoder_SetDeviceConfig(
    const VDECDD_sDdDevConfig   ** ppsDdDevConfig
)
{
    VDECDD_sDdDevConfig   * psDevConfig;
    DBGOPT_sValue           sVal;
    DBGOPT_eType            eType;

    IMG_ASSERT(ppsDdDevConfig);

    // Allocate device configuration structure.
    VDEC_MALLOC(psDevConfig);
    IMG_ASSERT(psDevConfig);
    if (psDevConfig == IMG_NULL)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
            "Failed to allocate memory for device configuration");
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psDevConfig);

    // Set the default device configuration.
    *psDevConfig = sDefaultDeviceConfig;

#ifdef SECURE_MEDIA_SUPPORT
    psDevConfig->bSecureMemoryAvailable = IMG_TRUE;
#endif

#ifdef VDEC_TARGET_CEDARVIEW
    psDevConfig->bAPM = IMG_FALSE;
#endif

#ifdef FW_PERFORMANCE_LOGGING
    // Override with values provided to DBGOPT
    if (DBGOPTKM_GetSize("PerformanceLog", DBGOPT_TYPE_BOOL) &&
        DBGOPTKM_Get("PerformanceLog", IMG_NULL, &sVal))
    {
        psDevConfig->bPerformanceLog = sVal.bVal;
    }
#endif

    // Override with values provided to DBGOPT
    if (DBGOPTKM_GetSize("APM", DBGOPT_TYPE_BOOL) &&
        DBGOPTKM_Get("APM", IMG_NULL, &sVal))
    {
        psDevConfig->bAPM = sVal.bVal;
    }
    if (DBGOPTKM_GetSize("CoreDecodeSlots", DBGOPT_TYPE_NUMBER) &&
        DBGOPTKM_Get("CoreDecodeSlots", IMG_NULL, &sVal))
    {
        IMG_ASSERT(sVal.ui32Val <= psDevConfig->ui32NumSlotsPerPipe);
        if (sVal.ui32Val < psDevConfig->ui32NumSlotsPerPipe)
        {
            psDevConfig->ui32NumSlotsPerPipe = sVal.ui32Val;
        }
    }
    if (DBGOPTKM_GetSize("DecodeLevel", DBGOPT_TYPE_STRING) &&
        DBGOPTKM_Get("DecodeLevel", &eType, &sVal))
    {
        if (strncmp(sVal.pszVal, "scheduler", 32) == 0)
        {
            psDevConfig->eDecodeLevel = VDECDD_DECODELEVEL_SCHEDULER;
        }
        else if (strncmp(sVal.pszVal, "decoder", 32) == 0)
        {
            psDevConfig->eDecodeLevel = VDECDD_DECODELEVEL_DECODER;
        }
        else if (strncmp(sVal.pszVal, "fw", 32) == 0)
        {
            psDevConfig->eDecodeLevel = VDECDD_DECODELEVEL_FWHDRPARSING;
        }
        else if (strncmp(sVal.pszVal, "fehw", 32) == 0)
        {
            psDevConfig->eDecodeLevel = VDECDD_DECODELEVEL_FEHWDECODING;
        }
        else if (strncmp(sVal.pszVal, "all", 32) == 0)
        {
            psDevConfig->eDecodeLevel = VDECDD_DECODELEVEL_MAX;
        }
        else
        {
            REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                   "Invalid decode level [\"%s\"] using default \"all\"",
                   sVal.pszVal);
        }

#ifndef VDEC_MSVDX_HARDWARE
        // Without hardware clip the decode level to decoder.
        if (psDevConfig->eDecodeLevel > VDECDD_DECODELEVEL_DECODER)
        {
            psDevConfig->eDecodeLevel = VDECDD_DECODELEVEL_DECODER;
        }
#endif
    }
    if (DBGOPTKM_GetSize("DWRPeriod", DBGOPT_TYPE_NUMBER) &&
        DBGOPTKM_Get("DWRPeriod", IMG_NULL, &sVal))
    {
        psDevConfig->ui32DwrPeriod = sVal.ui32Val;
    }
    if (DBGOPTKM_GetSize("CoreDump", DBGOPT_TYPE_BOOL) &&
        DBGOPTKM_Get("CoreDump", IMG_NULL, &sVal))
    {
        psDevConfig->bCoreDump = sVal.bVal;
    }
#ifdef POST_TEST
    /* update POST request flag */
    if (DBGOPTKM_GetSize("Post", DBGOPT_TYPE_BOOL) &&
        DBGOPTKM_Get("Post", IMG_NULL, &sVal))
    {
        psDevConfig->bPost = sVal.bVal;
    }
#endif
#ifdef STACK_USAGE_TEST
    /* update STACK USAGE TEST request flag */
    if (DBGOPTKM_GetSize("StackUsageTest", DBGOPT_TYPE_BOOL) &&
        DBGOPTKM_Get("StackUsageTest", IMG_NULL, &sVal))
    {
        psDevConfig->bStackUsageTest = sVal.bVal;
    }
#endif
    if (DBGOPTKM_GetSize("DWRJPEGRetry", DBGOPT_TYPE_NUMBER) &&
        DBGOPTKM_Get("DWRJPEGRetry", IMG_NULL, &sVal))
    {
        psDevConfig->ui32DwrJPEGRetry = sVal.ui32Val;
    }
    if (DBGOPTKM_GetSize("FakeMtx", DBGOPT_TYPE_BOOL) &&
        DBGOPTKM_Get("FakeMtx", IMG_NULL, &sVal))
    {
        psDevConfig->bFakeMtx = sVal.bVal;
    }
    if (DBGOPTKM_GetSize("RendecSize", DBGOPT_TYPE_NUMBER) &&
        DBGOPTKM_Get("RendecSize", IMG_NULL, &sVal))
    {
        psDevConfig->ui32RendecSize = sVal.ui32Val;
    }
    if (DBGOPTKM_GetSize("LockStepDecode", DBGOPT_TYPE_BOOL) &&
        DBGOPTKM_Get("LockStepDecode", IMG_NULL, &sVal))
    {
        psDevConfig->bLockStepDecode = sVal.bVal;
    }
    if (DBGOPTKM_GetSize("DisableDecodeOpt", DBGOPT_TYPE_BOOL) &&
        DBGOPTKM_Get("DisableDecodeOpt", IMG_NULL, &sVal))
    {
        psDevConfig->bOptimisedPerformance = !sVal.bVal;
    }
    if (DBGOPTKM_GetSize("MemoryStallingMin", DBGOPT_TYPE_NUMBER) &&
        DBGOPTKM_GetSize("MemoryStallingMax", DBGOPT_TYPE_NUMBER) &&
        DBGOPTKM_GetSize("MemoryStallingRatio", DBGOPT_TYPE_NUMBER))
    {
        DBGOPT_sValue   sMin, sMax, sRatio;

        DBGOPTKM_Get("MemoryStallingMin", IMG_NULL, &sMin);
        psDevConfig->ui32MemoryStallingMin = sMin.ui32Val;

        DBGOPTKM_Get("MemoryStallingMax", IMG_NULL, &sMax);
        psDevConfig->ui32MemoryStallingMax = sMax.ui32Val;

        DBGOPTKM_Get("MemoryStallingRatio", IMG_NULL, &sRatio);
        psDevConfig->ui32MemoryStallingRatio = sRatio.ui32Val;
    }
    if (DBGOPTKM_GetSize("FeWdtPeriod", DBGOPT_TYPE_NUMBER) &&
        DBGOPTKM_Get("FeWdtPeriod", IMG_NULL, &sVal))
    {
        psDevConfig->ui32FeWdtPeriod = sVal.ui32Val;
    }
    if (DBGOPTKM_GetSize("PSRWdtPeriod", DBGOPT_TYPE_NUMBER) &&
        DBGOPTKM_Get("PSRWdtPeriod", IMG_NULL, &sVal))
    {
        psDevConfig->ui32PSRWdtPeriod = sVal.ui32Val;
    }
    if (DBGOPTKM_GetSize("BeWdtPeriod", DBGOPT_TYPE_NUMBER) &&
        DBGOPTKM_Get("BeWdtPeriod", IMG_NULL, &sVal))
    {
        psDevConfig->ui32BeWdtPeriod = sVal.ui32Val;
    }
    if (DBGOPTKM_GetSize("CSim", DBGOPT_TYPE_BOOL) &&
        DBGOPTKM_Get("CSim", IMG_NULL, &sVal))
    {
        psDevConfig->bCSim = sVal.bVal;
    }

    if (DBGOPTKM_GetSize("MMUTilingScheme", DBGOPT_TYPE_NUMBER) &&
        DBGOPTKM_Get("MMUTilingScheme", IMG_NULL, &sVal))
    {
        switch(sVal.ui32Val)
        {
        case 0:
            psDevConfig->eTileScheme = VDEC_TS0_256x16;
            break;
        case 1:
            psDevConfig->eTileScheme = VDEC_TS1_512x8;
            break;
        default:
            IMG_ASSERT(IMG_FALSE);
        }
    }

#ifndef IMG_KERNEL_MODULE
    if (DBGOPTKM_GetSize("PdumpRes", DBGOPT_TYPE_BOOL) &&
        DBGOPTKM_Get("PdumpRes", IMG_NULL, &sVal))
    {
        psDevConfig->bPdumpAndRes = sVal.bVal;
    }
#endif


#ifdef USE_REAL_FW
#ifdef INCLUDE_SINGLE_STANDARD_FW
    if (DBGOPTKM_GetSize("SingleStreamFw", DBGOPT_TYPE_BOOL) &&
        DBGOPTKM_Get("SingleStreamFw", IMG_NULL, &sVal))
    {
        psDevConfig->bSingleStreamFw = sVal.bVal;
    }
    if (DBGOPTKM_GetSize("SingleStreamFwVidStd", DBGOPT_TYPE_NUMBER) &&
        DBGOPTKM_Get("SingleStreamFwVidStd", IMG_NULL, &sVal))
    {
        psDevConfig->eSingleStreamStd = sVal.ui32Val;
    }
#endif
    if (DBGOPTKM_GetSize("OoldFirmware", DBGOPT_TYPE_BOOL) &&
        DBGOPTKM_Get("OoldFirmware", IMG_NULL, &sVal))
    {
        psDevConfig->bOoldFw = sVal.bVal;
    }
#endif

    *ppsDdDevConfig =  psDevConfig;

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              DECODER_Initialise

******************************************************************************/
IMG_RESULT DECODER_Initialise(
    IMG_VOID *              pvInitUserData,
    VDECDD_pfnCompCallback  pfnCallback,
    SYS_eMemPool            eInsecurePool,
    SYS_eMemPool            eSecureMemPool,
    VDECDD_sDdDevConfig   * psDdDevConfig,
    IMG_UINT32            * pui32NumCores,
    IMG_UINT32            * pui32NumPipes,
    IMG_HANDLE *            phDecCtx
)
{
    DECODER_sContext  * psDecCtx = (DECODER_sContext*)*phDecCtx;
    IMG_UINT32          i;
    IMG_RESULT          ui32Result;

    if (psDecCtx == IMG_NULL)
    {
        VDEC_MALLOC(psDecCtx);
        IMG_ASSERT(psDecCtx);
        if (psDecCtx == IMG_NULL)
        {
            REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                "Failed to allocate memory for Decoder context");
            return IMG_ERROR_OUT_OF_MEMORY;
        }
        VDEC_BZERO(psDecCtx);

        *phDecCtx = psDecCtx;
    }

    /*! Determine which standards are supported. */
    VDEC_BZERO(&psDecCtx->abSupportedStandards);
#ifdef HAS_AVS
    psDecCtx->abSupportedStandards[VDEC_STD_AVS]      = IMG_TRUE;
#endif /* HAS_AVS */
#ifdef HAS_H264
    psDecCtx->abSupportedStandards[VDEC_STD_H264]     = IMG_TRUE;
#endif /* HAS_H264 */
#ifdef HAS_MPEG2
    psDecCtx->abSupportedStandards[VDEC_STD_MPEG2]    = IMG_TRUE;
#endif /* HAS_MPEG2 */
#ifdef HAS_MPEG4
    psDecCtx->abSupportedStandards[VDEC_STD_MPEG4]    = IMG_TRUE;
    psDecCtx->abSupportedStandards[VDEC_STD_H263]     = IMG_TRUE;
    psDecCtx->abSupportedStandards[VDEC_STD_SORENSON] = IMG_TRUE;
#endif /* HAS_MPEG4 */
#ifdef HAS_VC1
    psDecCtx->abSupportedStandards[VDEC_STD_VC1]      = IMG_TRUE;
#endif /* HAS_VC1 */
#ifdef HAS_AVS
    psDecCtx->abSupportedStandards[VDEC_STD_AVS]      = IMG_TRUE;
#endif /* HAS_VC1 */
#ifdef HAS_REAL
    psDecCtx->abSupportedStandards[VDEC_STD_REAL]     = IMG_TRUE;
#endif /* HAS_REAL */
#ifdef HAS_JPEG
    psDecCtx->abSupportedStandards[VDEC_STD_JPEG]     = IMG_TRUE;
#endif /* HAS_JPEG */
#ifdef HAS_VP6
    psDecCtx->abSupportedStandards[VDEC_STD_VP6]      = IMG_TRUE;
#endif /* HAS_VP6 */
#ifdef HAS_VP8
    psDecCtx->abSupportedStandards[VDEC_STD_VP8]      = IMG_TRUE;
#endif /* HAS_VP8 */
#ifdef HAS_VC1
    psDecCtx->abSupportedStandards[VDEC_STD_VC1]      = IMG_TRUE;
#endif /* HAS_VC1 */
#ifdef HAS_HEVC
    psDecCtx->abSupportedStandards[VDEC_STD_HEVC]     = IMG_TRUE;
#endif /* HAS_HEVC */

    if (!psDecCtx->bInitialised)
    {
        /* Check input parameters. */
        IMG_ASSERT(pfnCallback);

        /* Store the input data. */
        psDecCtx->pfnCompCallback = pfnCallback;
        psDecCtx->pvCompInitUserData = pvInitUserData;
        psDecCtx->hDevHandle = ((VDECDD_sDdDevContext *)pvInitUserData)->hDevHandle;

        /* Initialise the context lists. */
        LST_init(&psDecCtx->sStreamList);
        LST_init(&psDecCtx->sCoreList);

        ui32Result = IDGEN_CreateContext(MAX_CONCURRENT_STREAMS, 64, IMG_FALSE, &psDecCtx->hStrIdGen);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        /* Make sure POOL API is initialised */
        ui32Result = POOL_Initialise();
        if(ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        ui32Result = decoder_SetDeviceConfig(&psDecCtx->psDevConfig);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        psDecCtx->eInsecurePool = eInsecurePool;
        psDecCtx->eSecurePool =
            psDecCtx->psDevConfig->bSecureMemoryAvailable ? eSecureMemPool : eInsecurePool;

        /* Enumerate the master core. */
        ui32Result = decoder_CoreEnumerate(psDecCtx,
                                           VDECDD_MSVDX_CORE_MASTER,
                                           psDecCtx->psDevConfig,
                                           &psDecCtx->ui32NumCores,
                                           &psDecCtx->ui32NumPipes);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }


        /* Enumerate each slave core on the device. */
        for (i = VDECDD_MSVDX_CORE_SLAVE1; i < psDecCtx->ui32NumCores; i++)
        {
            ui32Result = decoder_CoreEnumerate(psDecCtx, i, psDecCtx->psDevConfig, IMG_NULL,  IMG_NULL);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error;
            }
        }

#ifdef FW_PERFORMANCE_LOGGING
        ui32Result = PERFLOG_Initialise();
        if(ui32Result != IMG_SUCCESS)
        {
            REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
                    "Failed to initialise performance log");
        }

        ui32Result = PERFLOG_Open();
        if(ui32Result != IMG_SUCCESS)
        {
            REPORT(REPORT_MODULE_DECODER, REPORT_WARNING,
                    "Failed to open performance log file");
        }
#endif

        if (psDdDevConfig)
        {
            *psDdDevConfig = *psDecCtx->psDevConfig;
        }
        if (pui32NumCores)
        {
            *pui32NumCores = psDecCtx->ui32NumCores;
        }
        if (pui32NumPipes)
        {
            *pui32NumPipes = psDecCtx->ui32NumPipes;
        }

        psDecCtx->bInitialised = IMG_TRUE;
    }

    return IMG_SUCCESS;

error:
    if (*phDecCtx)
    {
        if (psDecCtx->bInitialised)
        {
            IMG_UINT32 ui32DeinitResult;

            /* Undo the initialisation. */
            ui32DeinitResult = DECODER_Deinitialise(*phDecCtx);
            if (ui32DeinitResult != IMG_SUCCESS)
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                    "DECODER_Deinitialise() failed to tidy-up after error");
            }
        }
        else
        {
            IMG_FREE(*phDecCtx);
            *phDecCtx = IMG_NULL;
        }
    }

    return ui32Result;
}


