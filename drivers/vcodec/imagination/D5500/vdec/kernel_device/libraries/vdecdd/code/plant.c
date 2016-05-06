/*!
 *****************************************************************************
 *
 * @File       plant.c
 * @Title      VDECDD Plant Component
 * @Description    This file contains the Plant Component implementation
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

#include "img_defs.h"
#include "vdec_api.h"
#include "vdecdd_utils.h"
#include "vdecdd_int.h"
#include "vdecdd_mmu.h"
#include "core_api.h"
#include "resource.h"
#include "plant.h"
#include "lst.h"
#include "report_api.h"

#define GENC_BUFF_COUNT 4
#define BITPLANE_BUFF_COUNT 3

#if defined(HAS_HEVC) || defined(HAS_VC1) || defined(HAS_VP6) || defined(HAS_VP8)
#define SEQ_RES_NEEDED
#endif

/*!
******************************************************************************
 This structure contains stream configuration within the plant. This relates to
 stream specific information such as resolution, picture format and pixel format
 that are required to allocate memory for the stream resources.

 @brief  Plant Stream Configuration

******************************************************************************/
typedef struct
{
    IMG_UINT32 ui32TBD;   //!< TDB.

} PLANT_sStrConfig;


/*!
******************************************************************************
 This structure contains the picture buffer size info.
 @brief  Picture Resource Info
******************************************************************************/
typedef struct
{
    IMG_UINT32         ui32MBParamsBufSize;  /*!< The size of currently allocated MB parameters buffers (if in use). 0 otherwise.      */

#if defined(HAS_MPEG4) || defined(HAS_HEVC)
    union
    {
#ifdef HAS_MPEG4
        struct
        {
    IMG_UINT32         ui32DPBufSize;        /*!< Size of Data Partition MPEG4 Buffer */
        } sMpeg4BufSize;
#endif
#ifdef HAS_HEVC
        struct
        {
            IMG_UINT32         ui32GencFragmentBufferSize; /*!< Size of GENC fragment buffer for HEVC */
        } sHEVCBufSize;
#endif
    };
#endif

} PLANT_sPictBufSizeInfo;

/*!
******************************************************************************
 This structure contains the picture resource info.
 @brief  Picture Resource Info
******************************************************************************/
typedef struct
{
    IMG_UINT32         ui32PictResNum;       /*!< The number of picture resources that are allocated for this stream.                  */

    VDEC_sPictRendInfo  sAuxPictRendInfo;    /*!< The size and structure of currently allocated auxiliary picture buffers (if in use). 0 otherwise.  */
    VDEC_sPictBufConfig sAuxPictBufConfig;   /*!< Aux Picture buffer configuration.                                                     */

    PLANT_sPictBufSizeInfo sSizeInfo;        /*!< Picture buffer size info.                                                     */

} PLANT_sPictResInfo;



/*!
******************************************************************************
 This structure contains the sequence resource info.
 @brief  Sequence Resource Info
******************************************************************************/
typedef struct
{
    union
    {
#ifdef HAS_HEVC
        struct
        {
            IMG_UINT32         ui32GencBufferSize;           /*!< Size of GEN buffers for HEVC */
            IMG_UINT32         ui32IntraBufferSize;           /*!< Size of GEN buffers for HEVC */
            IMG_UINT32         ui32AuxBufferSize;           /*!< Size of GEN buffers for HEVC */
        } sHEVCBufSize;
#endif
#ifdef HAS_VP8
        struct
        {
#ifdef VDEC_USE_PVDEC
            IMG_UINT32         ui32SecondPartitionProbSize;      /*!< Size of second partition probabilities buffer */
#endif
            IMG_UINT32         ui32MBFlagsBufferSize;        /*!< Size of MB flags buffer for VP8 */
            IMG_UINT32         ui32FirstPartitionBufferSize; /*!< Size of first partition buffer for VP8 */
            IMG_UINT32         ui32CurPictBufferSize;        /*!< Size of current picture buffer for VP8 */
            IMG_UINT32         ui32SegmentIDBufferSize;      /*!< Size of segmnet ID buffer for VP8 */
        } sVP8BufSize;
#endif
#ifdef HAS_VP6
        struct
        {
            IMG_UINT32         ui32PicBufferSize;            /*!< Size of current picture buffer for VP6 */
        } sVP6BufSize;
#endif
#ifdef HAS_VC1
        struct
        {
            IMG_UINT32         ui32MSBBufferSize;            /*!< Size of MSB buffer for VC1 */
            IMG_UINT32         ui32BitplaneBufferSize;       /*!< Size of bitplane buffers for VC1 */
        } sVC1BufSize;
#endif
#ifndef SEQ_RES_NEEDED
       IMG_UINT32 ui32Dummy; /* ANSI C forbids empty struct/union declaration  */
#endif
    };
} PLANT_sSeqResInfo;

typedef struct
{
    LST_LINK;           /*!< List link (allows the structure to be part of a MeOS list).                            */

    VDECDD_sDdPictBuf   * psPictBuf;        // Pointer to aux picture buffer.
    VDECDD_sPictResInt  * psPictResInt;      // Pointer to internal resource which owns aux picture buffer.

} PLANT_sDetachedAuxPict;


typedef struct PLANT_sStdSpecOperations_tag PLANT_sStdSpecOperations;

/*!
******************************************************************************
 This structure contains the stream context.
 @brief  Plant Stream Context
******************************************************************************/
typedef struct
{
    LST_LINK;           /*!< List link (allows the structure to be part of a MeOS list).                            */

    IMG_VOID *              pvUserData;            /*!< Callback user data from component.                                    */
    VDEC_sStrConfigData     sConfig;               /*!< Global stream configuration.                                          */

    IMG_HANDLE              hMmuStrHandle;         /*!<                                                                       */

    LST_T                   sPictResList;          /*!< List of active picture resources that are allocated for this stream.  */
    LST_T                   sOldPictResList;       /*!< List of picture resources that are allocated for this stream but no
                                                     longer suitable for new pictures.                                     */
#ifdef SEQ_RES_NEEDED
    LST_T                   sSeqResList;           /*!< List of active sequence resources that are allocated for this stream. */
    LST_T                   sOldSeqResList;        /*!< List of sequence resources that are allocated for this stream but no
                                                        longer suitable for new sequence(s).                                  */
#endif /* SEQ_RES_NEEDED */

    LST_T                   sPictBufList;          /*!< List of picture buffers that have been removed from active internal resources.  */

    PLANT_sPictResInfo      sPictResInfo;          /*!< Current picture resource info.                                        */
    PLANT_sSeqResInfo       sSeqResInfo;           /*!< Current sequence resource info.                                       */

    VDECDD_sDdPictBuf       sReconPictBuf;         /*!< Reconstructed picture buffer.                                         */
    VDEC_sPictSize          sCodedPictSize;        /*!< Coded picture size of last reconfiguration.                           */

    PLANT_sStdSpecOperations * psStdSpecOps;       /*!< Standard specific operations.                                         */

} PLANT_sStreamContext;


/*!
******************************************************************************
 This structure contains the MB parameters buffer allocation info.
 @brief  MB Parameters Buffer Allocation Info
******************************************************************************/
typedef struct
{
    IMG_BOOL    bAllocMBParamBuffers;   /*!< Flag to indicate allocation of MB parameters buffers.            */
    IMG_UINT32  ui32MBParamSize;        /*!< Number of bytes required for each MB parameters data.            */
    IMG_UINT32  ui32OverallocateMbNum;  /*!< (BRN26832) Number of MBs to overallocate MB parameters buffers.  */

} PLANT_sMBParamAllocInfo;


struct PLANT_sStdSpecOperations_tag
{
    IMG_RESULT (*pfAllocPictureBuffers)(PLANT_sStreamContext * psPltStrCtx,                 /*!< Allocates standard specific picture buffers.  */
                                        VDECDD_sPictResInt   * psPictResInt,
                                        VXDIO_sMemPool         sMemPool,
                                        PLANT_sPictResInfo   * psPictResInfo);              /*!< Frees standard specific picture buffers.  */
    IMG_RESULT (*pfFreePictureResource)(VDECDD_sPictResInt * psPicResInt);
    IMG_RESULT (*pfAllocSequenceBuffers)(PLANT_sStreamContext * psPltStrCtx,                /*!< Allocates standard specific sequence buffers.  */
                                         VDECDD_sSeqResInt   *  psSeqResInt,
                                         VXDIO_sMemPool         sMemPool,
                                         PLANT_sSeqResInfo   *  psSeqResInfo);
    IMG_RESULT (*pfFreeSequenceResource)(VDECDD_sSeqResInt * psSeqResInt);                  /*!< Frees standard specific sequence buffers.  */
    IMG_RESULT (*pfBufsGetSize)(PLANT_sStreamContext      * psPltStrCtx,                    /*!< Returns buffer's sizes (common and standard specific).  */
                                const VDEC_sComSequHdrInfo * psSeqHdrInfo,
                                VDEC_sPictSize             * psMaxPictSize,
                                PLANT_sPictBufSizeInfo     * psSizeInfo,
                                PLANT_sSeqResInfo          * psSeqResInfo,
                                IMG_BOOL                   * pbResourceNeeded);
    IMG_BOOL   (*pfIsStreamResourceSuitable)(PLANT_sPictResInfo          * psPictResInfo,   /*!< Checks whether resource is still suitable.  */
                                             PLANT_sPictResInfo          * psOldPictResInfo,
                                             PLANT_sSeqResInfo           * psSeqResInfo,
                                             PLANT_sSeqResInfo           * psOldSeqResInfo);
};

static IMG_BOOL                bInitialised = IMG_FALSE;   /*!< Indicates whether component is initialised.  */
static VDECDD_pfnCompCallback  pfnCompCallback;            /*!< Callback from component to return output.    */
static IMG_VOID *              pvCompInitUserData;         /*!< Callback user data from component.           */
static VDECDD_sDdDevConfig     gsDevConfig;                /*!< Device configuration.                        */
static IMG_UINT32              gui32NumCores;              /*!< Number of cores on device.                   */
static IMG_UINT32              gui32NumPipes;              /*!< Number of cores on device.                   */
static LST_T                   sStreamList;                /*!< List of stream context structures.           */


static PLANT_sMBParamAllocInfo asMBParamAllocInfo[VDEC_STD_MAX - 1] =
{
    /*                AllocFlag    MBParamSize    Overalloc     */
    /* MPEG2    */  { IMG_TRUE,    0xc8,          0             },
    /* MPEG4    */  { IMG_TRUE,    0xc8,          0             },
    /* H263     */  { IMG_TRUE,    0xc8,          0             },
    /* H264     */  { IMG_TRUE,    0x80,          0             },
    /* VC1      */  { IMG_TRUE,    0x80,          (4096*2)/0x80 },
    /* AVS      */  { IMG_TRUE,    0x80,          0             },
    /* REAL     */  { IMG_TRUE,    0x80,          0             },
    /* JPEG     */  { IMG_FALSE,   0x00,          0             },
    /* VP6      */  { IMG_TRUE,    0x80,          0             },
    /* VP8      */  { IMG_TRUE,    0x80,          0             },
    /* SORENSON */  { IMG_TRUE,    0xc8,          0             },
    /* HEVC     */  { IMG_TRUE,    0x40,          0             },
};

#ifdef HAS_MPEG4
static IMG_RESULT plant_FreeMpeg4PictureResource( VDECDD_sPictResInt * psPicResInt);
static IMG_RESULT plant_Mpeg4BufsGetSize(PLANT_sStreamContext       * psPltStrCtx,
                                         const VDEC_sComSequHdrInfo * psSeqHdrInfo,
                                         VDEC_sPictSize             * psMaxPictSize,
                                         PLANT_sPictBufSizeInfo     * psSizeInfo,
                                         PLANT_sSeqResInfo          * psSeqResInfo,
                                         IMG_BOOL                   * pbResourceNeeded);
static IMG_BOOL plant_IsMpeg4StreamResourceSuitable(PLANT_sPictResInfo          * psPictResInfo,
                                                    PLANT_sPictResInfo          * psOldPictResInfo,
                                                    PLANT_sSeqResInfo           * psSeqResInfo,
                                                    PLANT_sSeqResInfo           * psOldSeqResInfo);
static IMG_RESULT plant_AllocMpeg4SpecificPictBuffers(PLANT_sStreamContext * psPltStrCtx,
                                                      VDECDD_sPictResInt   * psPictResInt,
                                                      VXDIO_sMemPool         sMemPool,
                                                      PLANT_sPictResInfo   * psPictResInfo);
#endif

#ifdef HAS_HEVC
static IMG_RESULT plant_FreeHevcPictureResource(VDECDD_sPictResInt * psPicResInt);
static IMG_RESULT plant_FreeHevcSequenceResource(VDECDD_sSeqResInt * psSeqResInt);
static IMG_RESULT plant_HevcBufsGetSize(PLANT_sStreamContext       * psPltStrCtx,
                                        const VDEC_sComSequHdrInfo * psSeqHdrInfo,
                                        VDEC_sPictSize             * psMaxPictSize,
                                        PLANT_sPictBufSizeInfo     * psSizeInfo,
                                        PLANT_sSeqResInfo          * psSeqResInfo,
                                        IMG_BOOL                   * pbResourceNeeded);
static IMG_BOOL plant_IsHevcStreamResourceSuitable(PLANT_sPictResInfo          * psPictResInfo,
                                                   PLANT_sPictResInfo          * psOldPictResInfo,
                                                   PLANT_sSeqResInfo           * psSeqResInfo,
                                                   PLANT_sSeqResInfo           * psOldSeqResInfo);
static IMG_RESULT plant_AllocHevcSpecificSeqBuffers(PLANT_sStreamContext * psPltStrCtx,
                                                    VDECDD_sSeqResInt   *  psSeqResInt,
                                                    VXDIO_sMemPool         sMemPool,
                                                    PLANT_sSeqResInfo   *  psSeqResInfo);
static IMG_RESULT plant_AllocHevcSpecificPictBuffers(PLANT_sStreamContext * psPltStrCtx,
                                                     VDECDD_sPictResInt   * psPictResInt,
                                                     VXDIO_sMemPool         sMemPool,
                                                     PLANT_sPictResInfo   * psPictResInfo);
#endif

#ifdef HAS_VP8
static IMG_RESULT plant_VP8BufsGetSize(PLANT_sStreamContext       * psPltStrCtx,
                                       const VDEC_sComSequHdrInfo * psSeqHdrInfo,
                                       VDEC_sPictSize             * psMaxPictSize,
                                       PLANT_sPictBufSizeInfo     * psSizeInfo,
                                       PLANT_sSeqResInfo          * psSeqResInfo,
                                       IMG_BOOL                   * pbResourceNeeded);
static IMG_RESULT plant_FreeVP8SequenceResource(VDECDD_sSeqResInt * psSeqResInt);
static IMG_RESULT plant_AllocVP8SpecificSeqBuffers(PLANT_sStreamContext * psPltStrCtx,
                                                   VDECDD_sSeqResInt   *  psSeqResInt,
                                                   VXDIO_sMemPool         sMemPool,
                                                    PLANT_sSeqResInfo   *  psSeqResInfo);
static IMG_BOOL plant_IsVP8StreamResourceSuitable(PLANT_sPictResInfo          * psPictResInfo,
                                                  PLANT_sPictResInfo          * psOldPictResInfo,
                                                  PLANT_sSeqResInfo           * psSeqResInfo,
                                                  PLANT_sSeqResInfo           * psOldSeqResInfo);
#endif

#ifdef HAS_VP6
static IMG_BOOL plant_IsVP6StreamResourceSuitable(PLANT_sPictResInfo          * psPictResInfo,
                                                  PLANT_sPictResInfo          * psOldPictResInfo,
                                                  PLANT_sSeqResInfo           * psSeqResInfo,
                                                  PLANT_sSeqResInfo           * psOldSeqResInfo);
static IMG_RESULT plant_VP6BufsGetSize(PLANT_sStreamContext       * psPltStrCtx,
                                       const VDEC_sComSequHdrInfo * psSeqHdrInfo,
                                       VDEC_sPictSize             * psMaxPictSize,
                                       PLANT_sPictBufSizeInfo     * psSizeInfo,
                                       PLANT_sSeqResInfo          * psSeqResInfo,
                                       IMG_BOOL                   * pbResourceNeeded);
static IMG_RESULT plant_FreeVP6SequenceResource(VDECDD_sSeqResInt * psSeqResInt);

static IMG_RESULT plant_AllocVP6SpecificSeqBuffers(PLANT_sStreamContext * psPltStrCtx,
                                                   VDECDD_sSeqResInt   *  psSeqResInt,
                                                   VXDIO_sMemPool         sMemPool,
                                                   PLANT_sSeqResInfo   *  psSeqResInfo);
#endif
#ifdef HAS_VC1
static IMG_BOOL plant_IsVC1StreamResourceSuitable(PLANT_sPictResInfo          * psPictResInfo,
                                                  PLANT_sPictResInfo          * psOldPictResInfo,
                                                  PLANT_sSeqResInfo           * psSeqResInfo,
                                                  PLANT_sSeqResInfo           * psOldSeqResInfo);
static IMG_RESULT plant_VC1BufsGetSize(PLANT_sStreamContext       * psPltStrCtx,
                                       const VDEC_sComSequHdrInfo * psSeqHdrInfo,
                                       VDEC_sPictSize             * psMaxPictSize,
                                       PLANT_sPictBufSizeInfo     * psSizeInfo,
                                       PLANT_sSeqResInfo          * psSeqResInfo,
                                       IMG_BOOL                   * pbResourceNeeded);
static IMG_RESULT plant_FreeVC1SequenceResource(VDECDD_sSeqResInt * psSeqResInt);

static IMG_RESULT plant_AllocVC1SpecificSeqBuffers(PLANT_sStreamContext * psPltStrCtx,
                                                   VDECDD_sSeqResInt   *  psSeqResInt,
                                                   VXDIO_sMemPool         sMemPool,
                                                   PLANT_sSeqResInfo   *  psSeqResInfo);

#endif

static IMG_RESULT plant_CommonBufsGetSize(PLANT_sStreamContext       * psPltStrCtx,
                                          const VDEC_sComSequHdrInfo * psSeqHdrInfo,
                                          VDEC_sPictSize             * psMaxPictSize,
                                          PLANT_sPictBufSizeInfo     * psSizeInfo,
                                          PLANT_sSeqResInfo          * psSeqResInfo,
                                          IMG_BOOL                   * pbResourceNeeded);

static IMG_RESULT plant_GetMBNum(IMG_UINT32                 ui32Width,
                                 IMG_UINT32                 ui32Height);


static PLANT_sStdSpecOperations asStdSpecOps[VDEC_STD_MAX - 1] =
{
    /*                AllocPicture    FreePicture    AllocSeq    FreeSeq    BufsGetSize    IsStreamResourceSuitable   */
#ifdef HAS_MPEG2
    /* MPEG2    */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  plant_CommonBufsGetSize,      IMG_NULL},
#else
    /* MPEG2    */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  IMG_NULL,      IMG_NULL},
#endif
#ifdef HAS_MPEG4
    /* MPEG4    */  { plant_AllocMpeg4SpecificPictBuffers,
                      plant_FreeMpeg4PictureResource,
                      IMG_NULL,
                      IMG_NULL,
                      plant_Mpeg4BufsGetSize,
                      plant_IsMpeg4StreamResourceSuitable},
#else
    /* MPEG4    */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  IMG_NULL,      IMG_NULL},
#endif
#ifdef HAS_MPEG4
    /* H263     */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  plant_CommonBufsGetSize,      IMG_NULL},
#else
    /* H263    */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  IMG_NULL,      IMG_NULL},
#endif
#ifdef HAS_H264
    /* H264     */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  plant_CommonBufsGetSize,      IMG_NULL},
#else
    /* H264    */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  IMG_NULL,      IMG_NULL},
#endif
#ifdef HAS_VC1
    /* VC1      */  { IMG_NULL,
                      IMG_NULL,
                      plant_AllocVC1SpecificSeqBuffers,
                      plant_FreeVC1SequenceResource,
                      plant_VC1BufsGetSize,
                      plant_IsVC1StreamResourceSuitable},
#else
    /* VC1    */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  IMG_NULL,      IMG_NULL},
#endif
#ifdef HAS_AVS
    /* AVS      */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  plant_CommonBufsGetSize,      IMG_NULL},
#else
    /* AVS    */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  IMG_NULL,      IMG_NULL},
#endif
#ifdef HAS_REAL
    /* REAL     */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  plant_CommonBufsGetSize,      IMG_NULL},
#else
    /* REAL    */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  IMG_NULL,      IMG_NULL},
#endif
#ifdef HAS_JPEG
    /* JPEG     */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  plant_CommonBufsGetSize,      IMG_NULL},
#else
    /* JPEG    */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  IMG_NULL,      IMG_NULL},
#endif
#ifdef HAS_VP6
    /* VP6      */  { IMG_NULL,
                      IMG_NULL,
                      plant_AllocVP6SpecificSeqBuffers,
                      plant_FreeVP6SequenceResource,
                      plant_VP6BufsGetSize,
                      plant_IsVP6StreamResourceSuitable},
#else
    /* VP6    */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  IMG_NULL,      IMG_NULL},
#endif
#ifdef HAS_VP8
    /* VP8      */  { IMG_NULL,
                      IMG_NULL,
                      plant_AllocVP8SpecificSeqBuffers,
                      plant_FreeVP8SequenceResource,
                      plant_VP8BufsGetSize,
                      plant_IsVP8StreamResourceSuitable},
#else
    /* VP8    */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  IMG_NULL,      IMG_NULL},
#endif
#ifdef HAS_MPEG4
    /* SORENSON */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  plant_CommonBufsGetSize,      IMG_NULL},
#else
    /* SORENSON    */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  IMG_NULL,      IMG_NULL},
#endif
#ifdef HAS_HEVC
    /* HEVC     */  { plant_AllocHevcSpecificPictBuffers,
                      plant_FreeHevcPictureResource,
                      plant_AllocHevcSpecificSeqBuffers,
                      plant_FreeHevcSequenceResource,
                      plant_HevcBufsGetSize,
                      plant_IsHevcStreamResourceSuitable},
#else
    /* HEVC    */  { IMG_NULL,       IMG_NULL,      IMG_NULL,   IMG_NULL,  IMG_NULL,      IMG_NULL},
#endif

};

/*!
******************************************************************************
 This macro allocates device buffer.
******************************************************************************/
#define PLANT_ALLOC_RES_BUFF(_buf, _size, _mmuHandle, _memPool, _result)   \
do{                                                                        \
    VDEC_MALLOC(_buf);                                                     \
    IMG_ASSERT(IMG_NULL != _buf);                                          \
    if(IMG_NULL != _buf)                                                   \
    {                                                                      \
        VDEC_BZERO(_buf);                                                  \
        (_buf)->eMmuHeapId = MMU_HEAP_STREAM_BUFFERS;                      \
        (_result) = MMU_StreamMalloc(_mmuHandle,                           \
                                        (_buf)->eMmuHeapId,                \
                                        _memPool,                          \
                                        _size,                             \
                                        DEV_MMU_PAGE_ALIGNMENT,            \
                                        &(_buf)->sDdBufInfo);              \
        IMG_ASSERT(IMG_SUCCESS == (_result));                              \
    }                                                                      \
    else                                                                   \
    {                                                                      \
        (_result) = IMG_ERROR_OUT_OF_MEMORY;                               \
    }                                                                      \
}while(0);

/*!
******************************************************************************

 @Function              plant_StreamGetContext

 @Description

 This function returns the stream context structure for the given stream handle.

 @Return    PLANT_sStreamContext : This function returns a pointer to the stream
                                   context structure or IMG_NULL if not found.

******************************************************************************/
static PLANT_sStreamContext * plant_StreamGetContext(
    IMG_HANDLE  hPltStrCtx
)
{
    return (PLANT_sStreamContext *)hPltStrCtx;
}


#ifdef HAS_MPEG4
/*!
******************************************************************************

 @Function              plant_FreeMpeg4PictureResource

******************************************************************************/
static IMG_RESULT plant_FreeMpeg4PictureResource(
    VDECDD_sPictResInt * psPicResInt
)
{
    IMG_RESULT      ui32LocalResult;
    IMG_RESULT      ui32Result = IMG_SUCCESS;

    if (IMG_NULL != psPicResInt->psDP0Buf)
    {
        ui32LocalResult = MMU_FreeMem(&psPicResInt->psDP0Buf->sDdBufInfo);
        IMG_ASSERT(ui32LocalResult == IMG_SUCCESS);
        if (IMG_SUCCESS != ui32LocalResult)
        {
            REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                    "MMU_Free for DP0 buffer failed with error %u", ui32Result);
            ui32Result = ui32LocalResult;
        }
        IMG_FREE(psPicResInt->psDP0Buf);
        psPicResInt->psDP0Buf = IMG_NULL;
    }

    if (IMG_NULL != psPicResInt->psDP1Buf)
    {
        ui32LocalResult = MMU_FreeMem(&psPicResInt->psDP1Buf->sDdBufInfo);
        IMG_ASSERT(ui32LocalResult == IMG_SUCCESS);
        if (IMG_SUCCESS != ui32LocalResult)
        {
            REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                    "MMU_Free for DP1 buffer failed with error %u", ui32Result);
            ui32Result = ui32LocalResult;
        }
        IMG_FREE(psPicResInt->psDP1Buf);
        psPicResInt->psDP1Buf = IMG_NULL;
    }

    return ui32Result;
}

/*!
******************************************************************************

 @Function              plant_Mpeg4BufsGetSize

******************************************************************************/
static IMG_RESULT plant_Mpeg4BufsGetSize(
    PLANT_sStreamContext       * psPltStrCtx,
    const VDEC_sComSequHdrInfo * psSeqHdrInfo,
    VDEC_sPictSize             * psMaxPictSize,
    PLANT_sPictBufSizeInfo     * psSizeInfo,
    PLANT_sSeqResInfo          * psSeqResInfo,
    IMG_BOOL                   * pbResourceNeeded
)
{
    VDEC_eVidStd eVidStd = psPltStrCtx->sConfig.eVidStd;
    IMG_UINT32 ui32StdIdx = eVidStd - 1;

    /* calculate size of buffers common for all standards */
    plant_CommonBufsGetSize(psPltStrCtx,
                            psSeqHdrInfo,
                            psMaxPictSize,
                            psSizeInfo,
                            psSeqResInfo,
                            pbResourceNeeded);

    /* calculate size of mpeg4 specific  buffers*/
    if (asMBParamAllocInfo[ui32StdIdx].bAllocMBParamBuffers)
    {
        *pbResourceNeeded = IMG_TRUE;
        /* Calculate the number of MBs needed for current video sequence settings. */
        psSizeInfo->sMpeg4BufSize.ui32DPBufSize = 16 * plant_GetMBNum(psMaxPictSize->ui32Width, psMaxPictSize->ui32Height);
    }
    else
    {
        psSizeInfo->sMpeg4BufSize.ui32DPBufSize = 0;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              plant_IsMpeg4StreamResourceSuitable

******************************************************************************/
static IMG_BOOL plant_IsMpeg4StreamResourceSuitable(
    PLANT_sPictResInfo          * psPictResInfo,
    PLANT_sPictResInfo          * psOldPictResInfo,
    PLANT_sSeqResInfo           * psSeqResInfo,
    PLANT_sSeqResInfo           * psOldSeqResInfo
)
{
    return (psPictResInfo->sSizeInfo.sMpeg4BufSize.ui32DPBufSize <= psOldPictResInfo->sSizeInfo.sMpeg4BufSize.ui32DPBufSize);
}

static IMG_RESULT plant_AllocMpeg4SpecificPictBuffers(
    PLANT_sStreamContext * psPltStrCtx,
    VDECDD_sPictResInt   * psPictResInt,
    VXDIO_sMemPool         sMemPool,
    PLANT_sPictResInfo   * psPictResInfo)
{
    IMG_RESULT      ui32Result;
    IMG_UINT32 ui32DPBufSize = psPictResInfo->sSizeInfo.sMpeg4BufSize.ui32DPBufSize;

    /* If Data Partition buffers are needed... */
    if (ui32DPBufSize > 0)
    {
        /* Allocate the DP0 buffer info structure. */
        PLANT_ALLOC_RES_BUFF(psPictResInt->psDP0Buf,
                             ui32DPBufSize,
                             psPltStrCtx->hMmuStrHandle,
                             sMemPool,
                             ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            return IMG_ERROR_OUT_OF_MEMORY;
        }

        /* Allocate the DP1 buffer info structure. */
        PLANT_ALLOC_RES_BUFF(psPictResInt->psDP1Buf,
                             ui32DPBufSize,
                             psPltStrCtx->hMmuStrHandle,
                             sMemPool,
                             ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            return IMG_ERROR_OUT_OF_MEMORY;
        }
    }

    return IMG_SUCCESS;
}
#endif /* HAS_MPEG4  */

#ifdef HAS_HEVC
/*!
******************************************************************************

 @Function              plant_FreeHevcPictureResource

******************************************************************************/
static IMG_RESULT plant_FreeHevcPictureResource(
    VDECDD_sPictResInt * psPicResInt
)
{
    IMG_RESULT      ui32Result = IMG_SUCCESS;

    if (IMG_NULL != psPicResInt->psGencFragmentBuffer)
    {
        ui32Result = MMU_FreeMem(&psPicResInt->psGencFragmentBuffer->sDdBufInfo);
        if (IMG_SUCCESS != ui32Result)
        {
            REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                    "MMU_Free for Genc Fragment buffer failed with error %u", ui32Result);
        }
        IMG_FREE(psPicResInt->psGencFragmentBuffer);
        psPicResInt->psGencFragmentBuffer = IMG_NULL;
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              plant_FreeHevcSequenceResource

******************************************************************************/
static IMG_RESULT plant_FreeHevcSequenceResource(
    VDECDD_sSeqResInt * psSeqResInt
)
{
    IMG_UINT32 ui32i;
    IMG_RESULT ui32Result = IMG_SUCCESS;

    for (ui32i = 0; ui32i < GENC_BUFF_COUNT; ++ui32i)
    {
        if (IMG_NULL != psSeqResInt->pasGencBuffers[ui32i])
        {
            ui32Result = MMU_FreeMem(&psSeqResInt->pasGencBuffers[ui32i]->sDdBufInfo);
            if (IMG_SUCCESS != ui32Result)
            {
                REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                       "MMU_Free for GENC buffer %u failed with error %u",
                       ui32i, ui32Result);
            }
            IMG_FREE(psSeqResInt->pasGencBuffers[ui32i]);
            psSeqResInt->pasGencBuffers[ui32i] = 0;
        }
    }

    if (IMG_NULL != psSeqResInt->psIntraBuffer)
    {
        ui32Result = MMU_FreeMem(&psSeqResInt->psIntraBuffer->sDdBufInfo);
        if (IMG_SUCCESS != ui32Result)
        {
            REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                    "MMU_Free for GENC buffer %u failed with error %u",
                    ui32i, ui32Result);
        }
        IMG_FREE(psSeqResInt->psIntraBuffer);
        psSeqResInt->psIntraBuffer = 0;
    }

    if (IMG_NULL != psSeqResInt->psAuxBuffer)
    {
        ui32Result = MMU_FreeMem(&psSeqResInt->psAuxBuffer->sDdBufInfo);
        if (IMG_SUCCESS != ui32Result)
        {
            REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                    "MMU_Free for GENC buffer %u failed with error %u",
                    ui32i, ui32Result);
        }
        IMG_FREE(psSeqResInt->psAuxBuffer);
        psSeqResInt->psAuxBuffer = 0;
    }

    return ui32Result;
}

/*!
******************************************************************************

 @Function              plant_HevcBufsGetSize

******************************************************************************/
static IMG_RESULT plant_HevcBufsGetSize(
    PLANT_sStreamContext       * psPltStrCtx,
    const VDEC_sComSequHdrInfo * psSeqHdrInfo,
    VDEC_sPictSize             * psMaxPictSize,
    PLANT_sPictBufSizeInfo     * psSizeInfo,
    PLANT_sSeqResInfo          * psSeqResInfo,
    IMG_BOOL                   * pbResourceNeeded
)
{
    VDEC_eVidStd eVidStd = psPltStrCtx->sConfig.eVidStd;
    IMG_UINT32 ui32StdIdx = eVidStd - 1;

    *pbResourceNeeded = IMG_TRUE;
    /* Reset the MB parameters buffer size. */
    psSizeInfo->ui32MBParamsBufSize = 0;

    if (asMBParamAllocInfo[ui32StdIdx].bAllocMBParamBuffers)
    {
        /* shall be == 64 (0x40)*/
        const IMG_UINT32 ui32Align = asMBParamAllocInfo[ui32StdIdx].ui32MBParamSize;
        const IMG_UINT32 ui32DpbWidth =
            (psMaxPictSize->ui32Width + ui32Align * 2 - 1) / ui32Align * 2;
        const IMG_UINT32 ui32PicHeight =
            (psMaxPictSize->ui32Height + ui32Align - 1) / ui32Align;
        const IMG_UINT32 ui32PicWidth =
            (psMaxPictSize->ui32Width + ui32Align - 1) / ui32Align;

        /* calculating for worst case: max frame size, B-frame */
        psSizeInfo->ui32MBParamsBufSize =
            (ui32Align * 2) * ui32PicWidth * ui32PicHeight +
            ui32Align * ui32DpbWidth * ui32PicHeight;

        /* Adjust the buffer size for MSVDX. */
        VDECDDUTILS_BufMsvdxAdjustSize(&psSizeInfo->ui32MBParamsBufSize);
    }

    {
        const static IMG_UINT16
            aui16MaxSliceSegments[HEVC_LEVEL_MAJOR_NUM][HEVC_LEVEL_MINOR_NUM] =
        {
            /* level: 1.0  1.1  1.2  */
                    { 16,    0,   0, },
            /* level: 2.0  2.1  2.2  */
                    { 16,   20,   0, },
            /* level: 3.0  3.1  3.2  */
                    { 30,   40,   0, },
            /* level: 4.0  4.1  4.2  */
                    { 75,   75,   0, },
            /* level: 5.0  5.1  5.2  */
                    { 200, 200, 200, },
            /* level: 6.0  6.1  6.2  */
                    { 600, 600, 600, }
        };

        const static IMG_UINT8
            aui8MaxTileCols[HEVC_LEVEL_MAJOR_NUM][HEVC_LEVEL_MINOR_NUM] =
        {
            /* level: 1.0  1.1  1.2  */
                    {   1,   0,   0, },
            /* level: 2.0  2.1  2.2  */
                    {   1,   1,   0, },
            /* level: 3.0  3.1  3.2  */
                    {   2,   3,   0, },
            /* level: 4.0  4.1  4.2  */
                    {   5,   5,   0, },
            /* level: 5.0  5.1  5.2  */
                    {  10,  10,  10, },
            /* level: 6.0  6.1  6.2  */
                    {  20,  20,  20, }
        };

        const static IMG_UINT32 HEVC_LEVEL_IDC_MIN = 30;
        const static IMG_UINT32 HEVC_LEVEL_IDC_MAX = 186;
        const static IMG_UINT32 GENC_ALIGNMENT = 0x1000;

        const static IMG_UINT32 ui32MbSize = 16;
        const static IMG_UINT32 ui32MaxMbRowsInCtu = 4;
        const static IMG_UINT32 ui32BytesPerFragmentPointer = 16;

        const IMG_UINT32 ui32MaxTileHeightInMbs =
            psSeqHdrInfo->sMaxFrameSize.ui32Height / ui32MbSize;

        IMG_UINT8 ui8LevelMaj = psSeqHdrInfo->ui32CodecLevel / 30;
        IMG_UINT8 ui8LevelMin = (psSeqHdrInfo->ui32CodecLevel % 30) / 3;

        if (psSeqHdrInfo->ui32CodecLevel > HEVC_LEVEL_IDC_MAX
            || psSeqHdrInfo->ui32CodecLevel < HEVC_LEVEL_IDC_MIN)
        {
            ui8LevelMaj = 6;
            ui8LevelMin = 2;
        }

        /* if we are somehow able to deliver more information here (CTU size,
           number of tile columns/rows) then memory usage could be reduced */
        {
            const IMG_UINT16 ui16MaxSliceSegments =
                aui16MaxSliceSegments[ui8LevelMaj - 1][ui8LevelMin];
            const IMG_UINT8 ui8MaxTileCols =
                aui8MaxTileCols[ui8LevelMaj - 1][ui8LevelMin];

            IMG_UINT32 * pui32GencFragmentBufferSize = &psSizeInfo->sHEVCBufSize.ui32GencFragmentBufferSize;
            IMG_UINT32 * pui32GencBufferSize = &psSeqResInfo->sHEVCBufSize.ui32GencBufferSize;

            *pui32GencFragmentBufferSize =
                ui32BytesPerFragmentPointer
                * (psSeqHdrInfo->sMaxFrameSize.ui32Height / ui32MbSize
                   * ui8MaxTileCols
                   + ui16MaxSliceSegments - 1) * ui32MaxMbRowsInCtu;

            /* GencBufferSize formula is taken from TRM and found by HW * CSIM teams for a sensible streams
             * i.e. size_of_stream < size_of_output_YUV. In videostream data base it's possible to find pathological
             * Argon streams that do not fulfill this sensible requirement. eg. #58417, #58419, #58421, #58423.
             * To make a #58417 stream running the formula below should be change
             * from (2 * 384) *... ---> (3 * 384) *...
             * This solution is applied by DEVA.*/
            *pui32GencBufferSize =
                2 * 384
                * psSeqHdrInfo->sMaxFrameSize.ui32Width / ui32MbSize
                * ui32MaxTileHeightInMbs / 4;

            *pui32GencBufferSize =
                VDEC_ALIGN_SIZE(*pui32GencBufferSize, GENC_ALIGNMENT);
            *pui32GencFragmentBufferSize =
                VDEC_ALIGN_SIZE(*pui32GencFragmentBufferSize, GENC_ALIGNMENT);

            DEBUG_REPORT(REPORT_MODULE_PLANT,
                         "Sizes for GENC in HEVC: 0x%X (frag), 0x%X (x4)",
                         *pui32GencFragmentBufferSize,
                         *pui32GencBufferSize);
        }
    }

    psSeqResInfo->sHEVCBufSize.ui32IntraBufferSize = 4 * psSeqHdrInfo->sMaxFrameSize.ui32Width;
    if(psSeqHdrInfo->sPixelInfo.eMemoryPacking != PIXEL_BIT8_MP)
    {
        psSeqResInfo->sHEVCBufSize.ui32IntraBufferSize *= 2;
    }
    psSeqResInfo->sHEVCBufSize.ui32AuxBufferSize = (512 * 1024);

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              plant_IsHevcStreamResourceSuitable

******************************************************************************/
static IMG_BOOL plant_IsHevcStreamResourceSuitable(
    PLANT_sPictResInfo          * psPictResInfo,
    PLANT_sPictResInfo          * psOldPictResInfo,
    PLANT_sSeqResInfo           * psSeqResInfo,
    PLANT_sSeqResInfo           * psOldSeqResInfo
)
{
    return (psSeqResInfo->sHEVCBufSize.ui32GencBufferSize <= psOldSeqResInfo->sHEVCBufSize.ui32GencBufferSize
            && psSeqResInfo->sHEVCBufSize.ui32IntraBufferSize <= psOldSeqResInfo->sHEVCBufSize.ui32IntraBufferSize
            && psSeqResInfo->sHEVCBufSize.ui32AuxBufferSize <= psOldSeqResInfo->sHEVCBufSize.ui32AuxBufferSize
            && psPictResInfo->sSizeInfo.sHEVCBufSize.ui32GencFragmentBufferSize <= psOldPictResInfo->sSizeInfo.sHEVCBufSize.ui32GencFragmentBufferSize);
}

/*!
******************************************************************************

 @Function              plant_AllocHevcSpecificPictBuffers

******************************************************************************/
static IMG_RESULT plant_AllocHevcSpecificSeqBuffers(
    PLANT_sStreamContext * psPltStrCtx,
    VDECDD_sSeqResInt   *  psSeqResInt,
    VXDIO_sMemPool         sMemPool,
    PLANT_sSeqResInfo   *  psSeqResInfo)
{
    IMG_UINT32 ui32I;
    IMG_RESULT ui32Result = IMG_SUCCESS;

    /* Allocate GENC buffers */
    for (ui32I = 0; ui32I < GENC_BUFF_COUNT; ++ui32I)
    {
        /* Allocate the GENC buffer info structure. */
        PLANT_ALLOC_RES_BUFF(psSeqResInt->pasGencBuffers[ui32I],
                             psSeqResInfo->sHEVCBufSize.ui32GencBufferSize,
                             psPltStrCtx->hMmuStrHandle,
                             sMemPool,
                             ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            return IMG_ERROR_OUT_OF_MEMORY;
        }
    }

    /* Allocate the intra buffer info structure. */
    PLANT_ALLOC_RES_BUFF(psSeqResInt->psIntraBuffer,
                        psSeqResInfo->sHEVCBufSize.ui32IntraBufferSize,
                        psPltStrCtx->hMmuStrHandle,
                        sMemPool,
                        ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    /* Allocate the aux buffer info structure. */
    PLANT_ALLOC_RES_BUFF(psSeqResInt->psAuxBuffer,
                        psSeqResInfo->sHEVCBufSize.ui32AuxBufferSize,
                        psPltStrCtx->hMmuStrHandle,
                        sMemPool,
                        ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              plant_AllocHevcSpecificPictBuffers

******************************************************************************/
static IMG_RESULT plant_AllocHevcSpecificPictBuffers(
    PLANT_sStreamContext * psPltStrCtx,
    VDECDD_sPictResInt   * psPictResInt,
    VXDIO_sMemPool         sMemPool,
    PLANT_sPictResInfo   * psPictResInfo)
{
    IMG_RESULT ui32Result;

    /* Allocate the GENC fragment buffer. */
    PLANT_ALLOC_RES_BUFF(psPictResInt->psGencFragmentBuffer,
                         psPictResInfo->sSizeInfo.sHEVCBufSize.ui32GencFragmentBufferSize,
                         psPltStrCtx->hMmuStrHandle,
                         sMemPool,
                         ui32Result);

   return ui32Result;
}

#endif /* HAS_HEVC  */

#ifdef HAS_VP8
/*!
******************************************************************************

 @Function              plant_IsVP8StreamResourceSuitable

******************************************************************************/
static IMG_BOOL plant_IsVP8StreamResourceSuitable(
    PLANT_sPictResInfo          * psPictResInfo,
    PLANT_sPictResInfo          * psOldPictResInfo,
    PLANT_sSeqResInfo           * psSeqResInfo,
    PLANT_sSeqResInfo           * psOldSeqResInfo
)
{
    return (psSeqResInfo->sVP8BufSize.ui32MBFlagsBufferSize <= psOldSeqResInfo->sVP8BufSize.ui32MBFlagsBufferSize &&
        psSeqResInfo->sVP8BufSize.ui32FirstPartitionBufferSize <= psOldSeqResInfo->sVP8BufSize.ui32FirstPartitionBufferSize &&
        psSeqResInfo->sVP8BufSize.ui32CurPictBufferSize <= psOldSeqResInfo->sVP8BufSize.ui32CurPictBufferSize &&
        psSeqResInfo->sVP8BufSize.ui32SegmentIDBufferSize <= psOldSeqResInfo->sVP8BufSize.ui32SegmentIDBufferSize);
}

/*!
******************************************************************************

 @Function              plant_VP8BufsGetSize

******************************************************************************/
static IMG_RESULT plant_VP8BufsGetSize(
    PLANT_sStreamContext       * psPltStrCtx,
    const VDEC_sComSequHdrInfo * psSeqHdrInfo,
    VDEC_sPictSize             * psMaxPictSize,
    PLANT_sPictBufSizeInfo     * psSizeInfo,
    PLANT_sSeqResInfo          * psSeqResInfo,
    IMG_BOOL                   * pbResourceNeeded
)
{
#define VP8_SEC_PROB_SIZE 300
    IMG_INT32 ui32MaxMBWidth = (VDEC_ALIGN_SIZE(psMaxPictSize->ui32Width, VDEC_MB_DIMENSION) / VDEC_MB_DIMENSION);
    IMG_INT32 ui32MaxMBHeight = (VDEC_ALIGN_SIZE(psMaxPictSize->ui32Height,VDEC_MB_DIMENSION) / VDEC_MB_DIMENSION);
    IMG_INT32 ui32MaxMBSize = (ui32MaxMBWidth + 4) * ui32MaxMBHeight;

    /* calculate size of buffers common for all standards except HEVC*/
    plant_CommonBufsGetSize(psPltStrCtx,
                            psSeqHdrInfo,
                            psMaxPictSize,
                            psSizeInfo,
                            psSeqResInfo,
                            pbResourceNeeded);

    *pbResourceNeeded = IMG_TRUE;

    /* calculate size of vp8 specific buffers*/
#ifdef VDEC_USE_PVDEC
    psSeqResInfo->sVP8BufSize.ui32SecondPartitionProbSize = VP8_SEC_PROB_SIZE;
#endif
    psSeqResInfo->sVP8BufSize.ui32MBFlagsBufferSize = ((VDEC_MB_DIMENSION + 4) * 1024);
    psSeqResInfo->sVP8BufSize.ui32FirstPartitionBufferSize = ui32MaxMBSize * 64;
    psSeqResInfo->sVP8BufSize.ui32CurPictBufferSize = ui32MaxMBSize * 64;
    psSeqResInfo->sVP8BufSize.ui32SegmentIDBufferSize = ui32MaxMBSize / 4;

    return IMG_SUCCESS;
#undef VP8_SEC_PROB_SIZE
}

/*!
******************************************************************************

 @Function              plant_FreeVP8SequenceResource

******************************************************************************/
static IMG_RESULT plant_FreeVP8SequenceResource(
    VDECDD_sSeqResInt * psSeqResInt
)
{
    IMG_RESULT      ui32LocalResult;
    IMG_RESULT      ui32Result = IMG_SUCCESS;

#ifdef VDEC_USE_PVDEC
    IMG_UINT32      ui32I;
    for(ui32I = 0; ui32I < gui32NumPipes; ui32I++)
    {
        if (IMG_NULL != psSeqResInt->pasSecondPartitionProb[ui32I])
        {
            ui32LocalResult = MMU_FreeMem(&psSeqResInt->pasSecondPartitionProb[ui32I]->sDdBufInfo);
        IMG_ASSERT(ui32LocalResult == IMG_SUCCESS);
        if (IMG_SUCCESS != ui32LocalResult)
        {
            REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                    "MMU_Free for MB flags buffer failed with error %u", ui32Result);
            ui32Result = ui32LocalResult;
        }

            IMG_FREE(psSeqResInt->pasSecondPartitionProb[ui32I]);
            psSeqResInt->pasSecondPartitionProb[ui32I] = IMG_NULL;
        }
    }
#endif

    if (IMG_NULL != psSeqResInt->psMbFlagsBuffer)
    {
        ui32LocalResult = MMU_FreeMem(&psSeqResInt->psMbFlagsBuffer->sDdBufInfo);
            IMG_ASSERT(ui32LocalResult == IMG_SUCCESS);
            if (IMG_SUCCESS != ui32LocalResult)
            {
                REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                        "MMU_Free for MB flags buffer failed with error %u", ui32Result);
                ui32Result = ui32LocalResult;
            }
        IMG_FREE(psSeqResInt->psMbFlagsBuffer);
        psSeqResInt->psMbFlagsBuffer = IMG_NULL;
        }

    if (IMG_NULL != psSeqResInt->psSegmentIDBuffer)
    {
        ui32LocalResult = MMU_FreeMem(&psSeqResInt->psSegmentIDBuffer->sDdBufInfo);
            IMG_ASSERT(ui32LocalResult == IMG_SUCCESS);
            if (IMG_SUCCESS != ui32LocalResult)
            {
                REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                        "MMU_Free for Segment ID buffer failed with error %u", ui32Result);
                ui32Result = ui32LocalResult;
            }
        IMG_FREE(psSeqResInt->psSegmentIDBuffer);
        psSeqResInt->psSegmentIDBuffer = IMG_NULL;
    }

    if (IMG_NULL != psSeqResInt->psFirstPartitionBuffer)
    {
        ui32LocalResult = MMU_FreeMem(&psSeqResInt->psFirstPartitionBuffer->sDdBufInfo);
        IMG_ASSERT(ui32LocalResult == IMG_SUCCESS);
        if (IMG_SUCCESS != ui32LocalResult)
        {
            REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                    "MMU_Free for First Partition buffer failed with error %u", ui32Result);
            ui32Result = ui32LocalResult;
        }
        IMG_FREE(psSeqResInt->psFirstPartitionBuffer);
        psSeqResInt->psFirstPartitionBuffer = IMG_NULL;
    }

    if (IMG_NULL != psSeqResInt->psCurrentPictureBuffer)
    {
        ui32LocalResult = MMU_FreeMem(&psSeqResInt->psCurrentPictureBuffer->sDdBufInfo);
        IMG_ASSERT(ui32LocalResult == IMG_SUCCESS);
        if (IMG_SUCCESS != ui32LocalResult)
    {
            REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                    "MMU_Free for Current Picture buffer failed with error %u", ui32Result);
            ui32Result = ui32LocalResult;
        }
        IMG_FREE(psSeqResInt->psCurrentPictureBuffer);
        psSeqResInt->psCurrentPictureBuffer = IMG_NULL;
    }

    return ui32Result;
}

/*!
******************************************************************************

 @Function              plant_AllocVP8SpecificSeqBuffers

******************************************************************************/
static IMG_RESULT plant_AllocVP8SpecificSeqBuffers(
    PLANT_sStreamContext * psPltStrCtx,
    VDECDD_sSeqResInt   *  psSeqResInt,
    VXDIO_sMemPool         sMemPool,
    PLANT_sSeqResInfo   *  psSeqResInfo)
    {
    IMG_RESULT ui32Result = IMG_SUCCESS;

#ifdef VDEC_USE_PVDEC
    IMG_UINT32      ui32I;

    for(ui32I = 0; ui32I < gui32NumPipes; ui32I++)
    {
    /* Allocate the Second partition probabilities buffer. */
        PLANT_ALLOC_RES_BUFF(psSeqResInt->pasSecondPartitionProb[ui32I],
                             psSeqResInfo->sVP8BufSize.ui32SecondPartitionProbSize,
                         psPltStrCtx->hMmuStrHandle,
                         sMemPool,
                         ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    }
#endif

    /* Allocate the MBFlag buffer info structure. */
    PLANT_ALLOC_RES_BUFF(psSeqResInt->psMbFlagsBuffer,
                         psSeqResInfo->sVP8BufSize.ui32MBFlagsBufferSize,
                         psPltStrCtx->hMmuStrHandle,
                         sMemPool,
                         ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    PLANT_ALLOC_RES_BUFF(psSeqResInt->psSegmentIDBuffer,
                             psSeqResInfo->sVP8BufSize.ui32SegmentIDBufferSize,
                         psPltStrCtx->hMmuStrHandle,
                         sMemPool,
                         ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            return IMG_ERROR_OUT_OF_MEMORY;
        }

    PLANT_ALLOC_RES_BUFF(psSeqResInt->psFirstPartitionBuffer,
                         psSeqResInfo->sVP8BufSize.ui32FirstPartitionBufferSize,
                         psPltStrCtx->hMmuStrHandle,
                         sMemPool,
                         ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    PLANT_ALLOC_RES_BUFF(psSeqResInt->psCurrentPictureBuffer,
                         psSeqResInfo->sVP8BufSize.ui32CurPictBufferSize,
                         psPltStrCtx->hMmuStrHandle,
                         sMemPool,
                         ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    return IMG_SUCCESS;
}
#endif /* HAS_VP8  */

#ifdef HAS_VP6
/*!
******************************************************************************

 @Function              plant_IsVP6StreamResourceSuitable

******************************************************************************/
static IMG_BOOL plant_IsVP6StreamResourceSuitable(
    PLANT_sPictResInfo          * psPictResInfo,
    PLANT_sPictResInfo          * psOldPictResInfo,
    PLANT_sSeqResInfo           * psSeqResInfo,
    PLANT_sSeqResInfo           * psOldSeqResInfo
)
{
    return (psSeqResInfo->sVP6BufSize.ui32PicBufferSize <= psOldSeqResInfo->sVP6BufSize.ui32PicBufferSize);
}

/*!
******************************************************************************

 @Function              plant_VP6BufsGetSize

******************************************************************************/
static IMG_RESULT plant_VP6BufsGetSize(
    PLANT_sStreamContext       * psPltStrCtx,
    const VDEC_sComSequHdrInfo * psSeqHdrInfo,
    VDEC_sPictSize             * psMaxPictSize,
    PLANT_sPictBufSizeInfo     * psSizeInfo,
    PLANT_sSeqResInfo          * psSeqResInfo,
    IMG_BOOL                   * pbResourceNeeded
)
{
    IMG_INT32 ui32MaxMBWidth = (VDEC_ALIGN_SIZE(psMaxPictSize->ui32Width, VDEC_MB_DIMENSION) / VDEC_MB_DIMENSION);
    IMG_INT32 ui32MaxMBHeight = (VDEC_ALIGN_SIZE(psMaxPictSize->ui32Height,VDEC_MB_DIMENSION) / VDEC_MB_DIMENSION);
    IMG_INT32 ui32MaxMBSize = (ui32MaxMBWidth + 4) * ui32MaxMBHeight;

    /* calculate size of buffers common for all standards except HEVC*/
    plant_CommonBufsGetSize(psPltStrCtx,
                            psSeqHdrInfo,
                            psMaxPictSize,
                            psSizeInfo,
                            psSeqResInfo,
                            pbResourceNeeded);

    *pbResourceNeeded = IMG_TRUE;

    /* calculate size of vp8 specific buffers*/
    psSeqResInfo->sVP6BufSize.ui32PicBufferSize = ui32MaxMBSize * 64;

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              plant_FreeVP6SequenceResource

******************************************************************************/
static IMG_RESULT plant_FreeVP6SequenceResource(
    VDECDD_sSeqResInt * psSeqResInt
)
{
    IMG_RESULT      ui32LocalResult;
    IMG_RESULT      ui32Result = IMG_SUCCESS;

    if (IMG_NULL != psSeqResInt->psPicBuffer)
    {
        ui32LocalResult = MMU_FreeMem(&psSeqResInt->psPicBuffer->sDdBufInfo);
        IMG_ASSERT(ui32LocalResult == IMG_SUCCESS);
        if (IMG_SUCCESS != ui32LocalResult)
        {
            REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                    "MMU_Free for Pic buffer failed with error %u", ui32Result);
            ui32Result = ui32LocalResult;
        }
        IMG_FREE(psSeqResInt->psPicBuffer);
        psSeqResInt->psPicBuffer = IMG_NULL;
    }

    return ui32Result;
}

/*!
******************************************************************************

 @Function              plant_AllocVP6SpecificSeqBuffers

******************************************************************************/
static IMG_RESULT plant_AllocVP6SpecificSeqBuffers(
    PLANT_sStreamContext * psPltStrCtx,
    VDECDD_sSeqResInt   *  psSeqResInt,
    VXDIO_sMemPool         sMemPool,
    PLANT_sSeqResInfo   *  psSeqResInfo)
{
    IMG_RESULT ui32Result = IMG_SUCCESS;

    /* Allocate the Pic buffer info structure. */
    PLANT_ALLOC_RES_BUFF(psSeqResInt->psPicBuffer,
                         psSeqResInfo->sVP6BufSize.ui32PicBufferSize,
                         psPltStrCtx->hMmuStrHandle,
                         sMemPool,
                         ui32Result);

    return ui32Result;
}
#endif /* HAS_VP6  */

#ifdef HAS_VC1
/*!
******************************************************************************

 @Function              plant_IsVC1StreamResourceSuitable

******************************************************************************/
static IMG_BOOL plant_IsVC1StreamResourceSuitable(
    PLANT_sPictResInfo          * psPictResInfo,
    PLANT_sPictResInfo          * psOldPictResInfo,
    PLANT_sSeqResInfo           * psSeqResInfo,
    PLANT_sSeqResInfo           * psOldSeqResInfo
)
{
    return (psSeqResInfo->sVC1BufSize.ui32MSBBufferSize <= psOldSeqResInfo->sVC1BufSize.ui32MSBBufferSize &&
          psSeqResInfo->sVC1BufSize.ui32BitplaneBufferSize <= psOldSeqResInfo->sVC1BufSize.ui32BitplaneBufferSize);
}

/*!
******************************************************************************

 @Function              plant_VC1BufsGetSize

******************************************************************************/
static IMG_RESULT plant_VC1BufsGetSize(
    PLANT_sStreamContext       * psPltStrCtx,
    const VDEC_sComSequHdrInfo * psSeqHdrInfo,
    VDEC_sPictSize             * psMaxPictSize,
    PLANT_sPictBufSizeInfo     * psSizeInfo,
    PLANT_sSeqResInfo          * psSeqResInfo,
    IMG_BOOL                   * pbResourceNeeded
)
{
#define VC1_MSB_PER_MB 64           /* TRM 4.3.11 */

    IMG_INT32 ui32MaxMBWidth = (VDEC_ALIGN_SIZE(psMaxPictSize->ui32Width, VDEC_MB_DIMENSION) / VDEC_MB_DIMENSION);
    IMG_INT32 ui32MaxMBHeight = (VDEC_ALIGN_SIZE(psMaxPictSize->ui32Height,VDEC_MB_DIMENSION) / VDEC_MB_DIMENSION);
    IMG_INT32 ui32MaxMBSize = (ui32MaxMBWidth + 4) * ui32MaxMBHeight;

    /* calculate size of buffers common for all standards except HEVC*/
    plant_CommonBufsGetSize(psPltStrCtx,
                            psSeqHdrInfo,
                            psMaxPictSize,
                            psSizeInfo,
                            psSeqResInfo,
                            pbResourceNeeded);

    *pbResourceNeeded = IMG_TRUE;

    /* calculate size of vc1 specific buffers*/
    psSeqResInfo->sVC1BufSize.ui32MSBBufferSize = ui32MaxMBSize * VC1_MSB_PER_MB;
    psSeqResInfo->sVC1BufSize.ui32BitplaneBufferSize = (ui32MaxMBWidth+16)*ui32MaxMBHeight;

    return IMG_SUCCESS;
#undef VC1_MSB_PER_MB
}

/*!
******************************************************************************

 @Function              plant_FreeVC1SequenceResource

******************************************************************************/
static IMG_RESULT plant_FreeVC1SequenceResource(
    VDECDD_sSeqResInt * psSeqResInt
)
{
    IMG_RESULT      ui32LocalResult;
    IMG_RESULT      ui32Result = IMG_SUCCESS;
    IMG_UINT32      ui32I;

    if (IMG_NULL != psSeqResInt->psMSBBuffer)
    {
        ui32LocalResult = MMU_FreeMem(&psSeqResInt->psMSBBuffer->sDdBufInfo);
        IMG_ASSERT(ui32LocalResult == IMG_SUCCESS);
        if (IMG_SUCCESS != ui32LocalResult)
        {
            REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                    "MMU_Free for MSB buffer failed with error %u", ui32Result);
            ui32Result = ui32LocalResult;
        }
        IMG_FREE(psSeqResInt->psMSBBuffer);
        psSeqResInt->psMSBBuffer = IMG_NULL;
    }


    for(ui32I = 0; ui32I < BITPLANE_BUFF_COUNT; ui32I++)
    {
        if (IMG_NULL != psSeqResInt->pasBitPlaneBuffers[ui32I])
        {
            ui32LocalResult = MMU_FreeMem(&psSeqResInt->pasBitPlaneBuffers[ui32I]->sDdBufInfo);
            IMG_ASSERT(ui32LocalResult == IMG_SUCCESS);
            if (IMG_SUCCESS != ui32LocalResult)
            {
                REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                       "MMU_Free for Bitplane %d buffer failed with error %u", ui32I, ui32Result);
                ui32Result = ui32LocalResult;
            }
            IMG_FREE(psSeqResInt->pasBitPlaneBuffers[ui32I]);
            psSeqResInt->pasBitPlaneBuffers[ui32I] = IMG_NULL;
        }
    }

    return ui32Result;
}

/*!
******************************************************************************

 @Function              plant_AllocVC1SpecificSeqBuffers

******************************************************************************/
static IMG_RESULT plant_AllocVC1SpecificSeqBuffers(
    PLANT_sStreamContext * psPltStrCtx,
    VDECDD_sSeqResInt   *  psSeqResInt,
    VXDIO_sMemPool         sMemPool,
    PLANT_sSeqResInfo   *  psSeqResInfo)
{
    IMG_RESULT ui32Result = IMG_SUCCESS;
    IMG_UINT32 ui32I;

    /* Allocate the Pic buffer info structure. */
    PLANT_ALLOC_RES_BUFF(psSeqResInt->psMSBBuffer,
                         psSeqResInfo->sVC1BufSize.ui32MSBBufferSize,
                         psPltStrCtx->hMmuStrHandle,
                         sMemPool,
                         ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    for(ui32I = 0; ui32I < BITPLANE_BUFF_COUNT; ui32I++)
    {
        PLANT_ALLOC_RES_BUFF(psSeqResInt->pasBitPlaneBuffers[ui32I],
                     psSeqResInfo->sVC1BufSize.ui32BitplaneBufferSize,
                     psPltStrCtx->hMmuStrHandle,
                     sMemPool,
                     ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            return IMG_ERROR_OUT_OF_MEMORY;
        }
    }

    return ui32Result;
}
#endif /* HAS_VC1  */

static IMG_RESULT plant_FreeCommonPictureResource(
    VDECDD_sPictResInt * psPicResInt
)
{
    IMG_RESULT      ui32Result = IMG_SUCCESS;
    IMG_RESULT      ui32LocalResult;

    if (IMG_NULL != psPicResInt->psDdPictBuf )
    {
        if(IMG_NULL != psPicResInt->psDdPictBuf->psPictBuf)
        {
            ui32LocalResult = MMU_FreeMem(&psPicResInt->psDdPictBuf->psPictBuf->sDdBufInfo);
            IMG_ASSERT(ui32LocalResult == IMG_SUCCESS);
            if (IMG_SUCCESS != ui32LocalResult)
            {
                REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                        "MMU_Free for Pict buffer failed with error %u", ui32Result);
                ui32Result = ui32LocalResult;
            }
            IMG_FREE(psPicResInt->psDdPictBuf->psPictBuf);
            IMG_FREE(psPicResInt->psDdPictBuf);
            psPicResInt->psDdPictBuf = IMG_NULL;
        }
        else
        {
            IMG_FREE(psPicResInt->psDdPictBuf);
            psPicResInt->psDdPictBuf = IMG_NULL;
        }
    }


    if (IMG_NULL != psPicResInt->psMBParamBuf)
    {
        ui32LocalResult = MMU_FreeMem(&psPicResInt->psMBParamBuf->sDdBufInfo);
        IMG_ASSERT(ui32LocalResult == IMG_SUCCESS);
        if (IMG_SUCCESS != ui32LocalResult)
        {
            REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                    "MMU_Free for MBParam buffer failed with error %u", ui32Result);
            ui32Result = ui32LocalResult;
        }
        IMG_FREE(psPicResInt->psMBParamBuf);
        psPicResInt->psMBParamBuf = IMG_NULL;
    }

    return ui32Result;
}

/*!
******************************************************************************

 @Function              plant_FreePictureResource

******************************************************************************/
static IMG_RESULT plant_FreePictureResource(
    PLANT_sStreamContext *  psPltStrCtx,
    VDECDD_sPictResInt * psPicResInt
)
{
    IMG_RESULT      ui32Result = IMG_SUCCESS;
    IMG_RESULT      ui32LocalResult;
    ui32LocalResult = plant_FreeCommonPictureResource(psPicResInt);
    ui32Result = (ui32LocalResult != IMG_SUCCESS ? ui32LocalResult : ui32Result);

    IMG_ASSERT(psPltStrCtx->psStdSpecOps);
    if(psPltStrCtx->psStdSpecOps->pfFreePictureResource)
    {
        psPltStrCtx->psStdSpecOps->pfFreePictureResource(psPicResInt);
    }

#ifdef SEQ_RES_NEEDED
    if (psPicResInt)
    {
        if (psPicResInt->psSeqResInt)
        {
            RESOURCE_ItemReturn(&psPicResInt->psSeqResInt->ui32RefCount);
            psPicResInt->psSeqResInt = 0;
        }
            }
#endif /* SEQ_RES_NEEDED */

    if(ui32Result == IMG_SUCCESS)
    {
        IMG_FREE(psPicResInt);
        }

    return ui32Result;
    }



/*!
******************************************************************************

 @Function              plant_FreeSequenceResource

******************************************************************************/
#ifdef SEQ_RES_NEEDED
static IMG_VOID plant_FreeSequenceResource(
    PLANT_sStreamContext *  psPltStrCtx,
    VDECDD_sSeqResInt * psSeqResInt
)
{
    IMG_ASSERT(psPltStrCtx->psStdSpecOps);
    if(psPltStrCtx->psStdSpecOps->pfFreeSequenceResource)
    {
        psPltStrCtx->psStdSpecOps->pfFreeSequenceResource(psSeqResInt);
    }

    IMG_FREE(psSeqResInt);
}
#endif /* SEQ_RES_NEEDED */


static IMG_RESULT
plant_ReattachPictBuf(
    PLANT_sStreamContext  * psPltStrCtx,
    VDECDD_sPictResInt    * psPictResInt
)
{
    PLANT_sDetachedAuxPict * psDetachedAuxPict;
    IMG_BOOL bFound = IMG_FALSE;

    if (LST_empty(&psPltStrCtx->sPictBufList))
    {
        // Since there are no pictures to re-attach just return.
        return IMG_SUCCESS;
    }

    // Re-attach picture buffer if it was removed.
    psDetachedAuxPict = LST_first(&psPltStrCtx->sPictBufList);
    while (psDetachedAuxPict)
    {
        if (psPictResInt == psDetachedAuxPict->psPictResInt)
        {
            // Reattach and remove from pict buf list.
            psPictResInt->psDdPictBuf = psDetachedAuxPict->psPictBuf;

            LST_remove(&psPltStrCtx->sPictBufList, psDetachedAuxPict);
            IMG_FREE(psDetachedAuxPict);
            psDetachedAuxPict = IMG_NULL;
            bFound = IMG_TRUE;
            break;
        }

        psDetachedAuxPict = LST_next(psDetachedAuxPict);
    }

    if (!bFound)
    {
        IMG_ASSERT(psPictResInt->psDdPictBuf);
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              plant_PrintBufferConfig

******************************************************************************/
static IMG_RESULT
plant_PrintBufferConfig(
    IMG_BOOL                      bNewRecon,
    const VDEC_sStrOutputConfig * psOutputConfig,
    const VDEC_sPictRendInfo    * psReconPictBufInfo,
    const VDEC_sPictBufConfig   * psReconPictBufConfig,
    const VDEC_sPictRendInfo    * psAuxPictBufInfo,
    const VDEC_sPictRendInfo    * psDisplayPictBufInfo,
    const VDEC_sPictBufConfig   * psDisplayPictBufConfig
)
{
    DEBUG_REPORT(REPORT_MODULE_PLANT, "======================================================");

    if (bNewRecon)
    {
        if (psAuxPictBufInfo->ui32RenderedSize)
        {
            // Aux buffer definition means that this configuration is only for recon.
            DEBUG_REPORT(REPORT_MODULE_PLANT, "Recon Buffer Configuration");
            DEBUG_REPORT(REPORT_MODULE_PLANT, "---------------------------");
        }
        else
        {
            // No aux buffer definition means that display buffer also defines recon configuration.
            DEBUG_REPORT(REPORT_MODULE_PLANT, "Display/Recon Buffer Configuration");
            DEBUG_REPORT(REPORT_MODULE_PLANT, "----------------------------------");
        }

        VDECDDUTILS_PrintBufferProperties(psOutputConfig,
                                          psReconPictBufInfo,
                                          psReconPictBufConfig);

        DEBUG_REPORT(REPORT_MODULE_PLANT, "======================================================");
    }

    if (!bNewRecon || psAuxPictBufInfo->ui32RenderedSize)
    {
        DEBUG_REPORT(REPORT_MODULE_PLANT, "Display Buffer Configuration");
        DEBUG_REPORT(REPORT_MODULE_PLANT, "---------------------------");

        VDECDDUTILS_PrintBufferProperties(psOutputConfig,
                                          psDisplayPictBufInfo,
                                          psDisplayPictBufConfig);

        DEBUG_REPORT(REPORT_MODULE_PLANT, "======================================================");
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              plant_StreamResourceDeprecate

******************************************************************************/
static IMG_RESULT plant_StreamResourceDeprecate(
    PLANT_sStreamContext *  psPltStrCtx
)
{
    VDECDD_sPictResInt * psPicResInt;
    IMG_RESULT           ui32Result;

    /* Free all "old" picture resources since these should now be unused. */
    psPicResInt = LST_first(&psPltStrCtx->sOldPictResList);
    while (psPicResInt)
    {
        if (psPicResInt->ui32RefCount != 0)
        {
            REPORT(REPORT_MODULE_PLANT, REPORT_WARNING,
                "[USERSID=0x%08X] Internal resource should be unused since it has been deprecated before",
                psPltStrCtx->sConfig.ui32UserStrId);

            psPicResInt = LST_next(psPicResInt);
        }
        else
        {
            VDECDD_sPictResInt * psPicResIntToRemove = psPicResInt;
            psPicResInt = LST_next(psPicResInt);

            LST_remove(&psPltStrCtx->sOldPictResList, psPicResIntToRemove);
            ui32Result = plant_FreePictureResource(psPltStrCtx, psPicResIntToRemove);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }
    }

    /* Move all "active" picture resources to the "old" list if they are still in use. */
    psPicResInt = LST_removeHead(&psPltStrCtx->sPictResList);
    while (psPicResInt)
    {
        // Instruct other blocks to stop using resource.
        ui32Result = pfnCompCallback(
            PLANT_CB_PICTURE_RESOURCE_REMOVE,
            pvCompInitUserData,
            IMG_NULL,
            psPltStrCtx->pvUserData,
            psPicResInt);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }


        // Re-attach picture buffer if it was removed.
        ui32Result = plant_ReattachPictBuf(psPltStrCtx, psPicResInt);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }

        /* If the active resource is not being used, free now.
           Otherwise add to the old list to be freed later. */
        if (psPicResInt->ui32RefCount == 0)
        {
            ui32Result = plant_FreePictureResource(psPltStrCtx, psPicResInt);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }
        else
        {
            LST_add(&psPltStrCtx->sOldPictResList, psPicResInt);
        }

        psPicResInt = LST_removeHead(&psPltStrCtx->sPictResList);
    }

    /* Reset the resource configuration. */
    VDEC_BZERO(&psPltStrCtx->sPictResInfo);

#ifdef SEQ_RES_NEEDED
    {
        VDECDD_sSeqResInt * psSeqResInt;

        /* Free all "old" sequence resources since these should now be unused. */
        psSeqResInt = LST_first(&psPltStrCtx->sOldSeqResList);
        while (psSeqResInt)
        {
            if (psSeqResInt->ui32RefCount != 0)
            {
                REPORT(REPORT_MODULE_PLANT, REPORT_WARNING,
                    "[USERSID=0x%08X] Internal sequence resource should be unused "
                    "since it has been deprecated before",
                    psPltStrCtx->sConfig.ui32UserStrId);

                psSeqResInt = LST_next(psSeqResInt);
            }
            else
            {
                VDECDD_sSeqResInt * psSeqResIntToRemove = psSeqResInt;
                psSeqResInt = LST_next(psSeqResInt);

                LST_remove(&psPltStrCtx->sOldSeqResList, psSeqResIntToRemove);
                plant_FreeSequenceResource(psPltStrCtx, psSeqResIntToRemove);
            }
        }

        /* Move all "active" sequence resources to the "old" list if they are still in use. */
        psSeqResInt = LST_removeHead(&psPltStrCtx->sSeqResList);
        while (psSeqResInt)
        {
            /* If the active resource is not being used, free now.
               Otherwise add to the old list to be freed later. */
            psSeqResInt->ui32RefCount == 0 ?
                plant_FreeSequenceResource(psPltStrCtx, psSeqResInt) :
                LST_add(&psPltStrCtx->sOldSeqResList, psSeqResInt);

            psSeqResInt = LST_removeHead(&psPltStrCtx->sSeqResList);
        }

        /* Reset the resource configuration. */
        VDEC_BZERO(&psPltStrCtx->sSeqResInfo);
    }
#endif /* SEQ_RES_NEEDED */

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              plant_StreamResourceDestroy

******************************************************************************/
static IMG_RESULT plant_StreamResourceDestroy(
    PLANT_sStreamContext *  psPltStrCtx
)
{
    VDECDD_sPictResInt * psPicResInt;
    IMG_RESULT           ui32Result;

    /* Remove any "active" picture resources allocated for this stream. */
    psPicResInt = LST_removeHead(&psPltStrCtx->sPictResList);
    while (psPicResInt)
    {
        // Re-attach picture buffer if it was removed.
        ui32Result = plant_ReattachPictBuf(psPltStrCtx, psPicResInt);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }

        ui32Result = plant_FreePictureResource(psPltStrCtx, psPicResInt);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        psPicResInt = LST_removeHead(&psPltStrCtx->sPictResList);
    }

    /* Remove any "old" picture resources allocated for this stream. */
    psPicResInt = LST_removeHead(&psPltStrCtx->sOldPictResList);
    while (psPicResInt)
    {
        ui32Result = plant_FreePictureResource(psPltStrCtx, psPicResInt);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        psPicResInt = LST_removeHead(&psPltStrCtx->sOldPictResList);
    }

    /* Reset the resource configuration. */
    VDEC_BZERO(&psPltStrCtx->sPictResInfo);

#ifdef SEQ_RES_NEEDED
    {
        VDECDD_sSeqResInt * psSeqResInt;

        /* Remove any "active" sequence resources allocated for this stream. */
        psSeqResInt = LST_removeHead(&psPltStrCtx->sSeqResList);
        while (psSeqResInt)
        {
            plant_FreeSequenceResource(psPltStrCtx, psSeqResInt);
            psSeqResInt = LST_removeHead(&psPltStrCtx->sSeqResList);
        }

        /* Remove any "old" sequence resources allocated for this stream. */
        psSeqResInt = LST_removeHead(&psPltStrCtx->sOldSeqResList);
        while (psSeqResInt)
        {
            plant_FreeSequenceResource(psPltStrCtx, psSeqResInt);
            psSeqResInt = LST_removeHead(&psPltStrCtx->sOldSeqResList);
        }

        /* Reset the resource configuration. */
        VDEC_BZERO(&psPltStrCtx->sSeqResInfo);
    }
#endif /* SEQ_RES_NEEDED */

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              plant_StreamDestroy

******************************************************************************/
static IMG_RESULT plant_StreamDestroy(
    PLANT_sStreamContext *  psPltStrCtx
)
{
    IMG_RESULT ui32Result;

    ui32Result = plant_StreamResourceDestroy(psPltStrCtx);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    LST_remove(&sStreamList, psPltStrCtx);

    IMG_FREE(psPltStrCtx);
    psPltStrCtx = IMG_NULL;

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              plant_GetMBNum

******************************************************************************/
static IMG_RESULT plant_GetMBNum(
    IMG_UINT32                 ui32Width,
    IMG_UINT32                 ui32Height
)
{
    /* Calculate the number of MBs needed for current video sequence settings. */
    IMG_UINT32    ui32WidthMB  = VDEC_ALIGN_SIZE(ui32Width, VDEC_MB_DIMENSION) / VDEC_MB_DIMENSION;
    IMG_UINT32    ui32HeightMB = VDEC_ALIGN_SIZE(ui32Height, 2 * VDEC_MB_DIMENSION) / VDEC_MB_DIMENSION;

    return ui32WidthMB * ui32HeightMB;
}

/*!
******************************************************************************

 @Function              plant_AdditionalBufsGetSize

******************************************************************************/
static IMG_RESULT plant_CommonBufsGetSize(
    PLANT_sStreamContext       * psPltStrCtx,
    const VDEC_sComSequHdrInfo * psSeqHdrInfo,
    VDEC_sPictSize             * psMaxPictSize,
    PLANT_sPictBufSizeInfo     * psSizeInfo,
    PLANT_sSeqResInfo          * psSeqResInfo,
    IMG_BOOL                   * pbResourceNeeded
)
{
    VDEC_eVidStd eVidStd = psPltStrCtx->sConfig.eVidStd;
    IMG_UINT32 ui32StdIdx = eVidStd - 1;
    IMG_UINT32 ui32MBNum = 0;

    if (psPltStrCtx->sConfig.eVidStd >= VDEC_STD_MAX)
    {
        return IMG_ERROR_GENERIC_FAILURE;
    }

    /* Reset the MB parameters buffer size. */
    psSizeInfo->ui32MBParamsBufSize = 0;

    if (asMBParamAllocInfo[ui32StdIdx].bAllocMBParamBuffers)
    {
        *pbResourceNeeded = IMG_TRUE;

        /* Calculate the number of MBs needed for current video sequence settings. */
        ui32MBNum = plant_GetMBNum(psMaxPictSize->ui32Width, psMaxPictSize->ui32Height);

        /* Calculate the final number of MBs needed. */
        ui32MBNum += asMBParamAllocInfo[ui32StdIdx].ui32OverallocateMbNum;

        /* Calculate the MB params buffer size. */
        psSizeInfo->ui32MBParamsBufSize = ui32MBNum * asMBParamAllocInfo[ui32StdIdx].ui32MBParamSize;

        /* Adjust the buffer size for MSVDX. */
        VDECDDUTILS_BufMsvdxAdjustSize(&psSizeInfo->ui32MBParamsBufSize);

        if(psSeqHdrInfo->bSeparateChromaPlanes)
        {
            psSizeInfo->ui32MBParamsBufSize *= 3;
        }
        }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              core_UseDisplayAsRecon

 @Description

 All reconstructed pictures within a closed GOP must have the same properties
 (inc. stride, no scaling, zero-rotation etc.). If the output configuration
 matches the decode properties and the display buffer is compatible with the
 reconstructed configuration display buffers can be used instead of internally
 allocated aux picture buffers. Internal resources will still be required until
 there are no references held.

 @Input     psComSeqHdrInfo : Pointer to sequence header information.

 @Input     psOutputConfig : Pointer to stream output configuration.

 @Input     psReconPictBuf : Pointer to reconstructed picture buffer.

 @Input     psDispPictBuf  : Pointer to display picture buffer.

 @Return    IMG_BOOL

******************************************************************************/
static IMG_BOOL
plant_UseDisplayAsRecon(
    const VDEC_sComSequHdrInfo  * psComSeqHdrInfo,
    const VDEC_sStrOutputConfig * psOutputConfig,
    const VDECDD_sDdPictBuf     * psReconPictBuf,
    const VDECDD_sDdPictBuf     * psDispPictBuf
)
{
    IMG_BOOL bNoTransformationRequired = IMG_FALSE;
    IMG_BOOL bCompatibleLayout = IMG_TRUE;

    if ( IMG_FALSE == VDECDDUTILS_IsSecondaryOutputRequired( psComSeqHdrInfo, psOutputConfig ) )
    {
        bNoTransformationRequired = IMG_TRUE;
    }

    // Determine whether the layout is compatible if reconstructed picture is already defined.
    if (psReconPictBuf->sRendInfo.ui32RenderedSize != 0)
    {
        // Picture render size should be the same.
        if (VDEC_SIZE_NE(psDispPictBuf->sRendInfo.sRendPictSize, psReconPictBuf->sRendInfo.sRendPictSize))
        {
            bCompatibleLayout = IMG_FALSE;
        }

        // Picture stride should be the same for all planes.
        if (psDispPictBuf->sRendInfo.asPlaneInfo[0].ui32Stride != psReconPictBuf->sRendInfo.asPlaneInfo[0].ui32Stride ||
            psDispPictBuf->sRendInfo.asPlaneInfo[1].ui32Stride != psReconPictBuf->sRendInfo.asPlaneInfo[1].ui32Stride ||
            psDispPictBuf->sRendInfo.asPlaneInfo[2].ui32Stride != psReconPictBuf->sRendInfo.asPlaneInfo[2].ui32Stride ||
            psDispPictBuf->sRendInfo.asPlaneInfo[3].ui32Stride != psReconPictBuf->sRendInfo.asPlaneInfo[3].ui32Stride)
        {
            bCompatibleLayout = IMG_FALSE;
        }

        // Tiling scheme should be the same
        if (psDispPictBuf->sBufConfig.eTileScheme == psReconPictBuf->sBufConfig.eTileScheme)
        {
            // Same byte interleaved setting should be used.
            // Convert to actual bools by comparing with zero.
            if ((psDispPictBuf->sBufConfig.bByteInterleave > 0) != (psReconPictBuf->sBufConfig.bByteInterleave > 0))
            {
                bCompatibleLayout = IMG_FALSE;
            }
        }
        else
        {
            bCompatibleLayout = IMG_FALSE;
        }
    }

    return bNoTransformationRequired && bCompatibleLayout;
}



/*!
******************************************************************************

 @Function              plant_PictResGetInfo

******************************************************************************/
static IMG_RESULT plant_PictResGetInfo(
    PLANT_sStreamContext        * psPltStrCtx,
    const VDEC_sComSequHdrInfo  * psComSeqHdrInfo,
    const VDEC_sStrOutputConfig * psOutputConfig,
    const VDECDD_sDdPictBuf     * psDispPictBuf,
    PLANT_sPictResInfo          * psPictResInfo,
    PLANT_sSeqResInfo           * psSeqResInfo
)
{
    VDEC_sPictSize  sCodedPictSize;
    IMG_BOOL        bResourceNeeded = IMG_FALSE;
    IMG_RESULT      ui32Result;

    /* Reset the picture resource info. */
    VDEC_BZERO(psPictResInfo);

    sCodedPictSize = psComSeqHdrInfo->sMaxFrameSize;

    // Determine whether the output picture buffers are suitable to double-up as reconstructed/reference.
    // It would be desirable (band-width and memory saving) to use output buffers both for reference and display.
    // It might only now be possible because the display buffers again have the same basic properties as the references.
    // For example, rotation angle may have returned to normal from perpendicular (where stride and orientation were
    // different to reference) and cannot be mixed.
    if (!plant_UseDisplayAsRecon(psComSeqHdrInfo, psOutputConfig, &psPltStrCtx->sReconPictBuf, psDispPictBuf))
    {
        IMG_BOOL bMatchDisplay = psPltStrCtx->sConfig.bBandwidthEfficient;

        if ((VDEC_STD_VC1 == psPltStrCtx->sConfig.eVidStd) &&
            psComSeqHdrInfo->bPostProcessing &&
            psOutputConfig->eRotMode == VDEC_ROTATE_0 &&
            !psOutputConfig->bScale)
        {
            // IPGear30189: VC-1 streams with post-processing signalled at the sequence level
            // must have internal image buffers allocated with the same properties as the display.
            // The post-processing feature may be disabled for some frames and, since the scaler
            // might be missing, their data cannot be written using the alternate output path.
            // Subsequently the recon path must be used which requires that these image buffers
            // are suitable for reference (must match references stored in internal image buffers
            // when post-processing was enabled for previous pictures).
            bMatchDisplay = IMG_TRUE;
        }

        // Since the display pictures cannot be used for reference/reconstructed,
        // determine the auxiliary picture buffer layout.
        if (psPltStrCtx->sReconPictBuf.sRendInfo.ui32RenderedSize == 0)
        {
            if (bMatchDisplay)
            {
                VDEC_sPictBufConfig sBufConfig = psDispPictBuf->sBufConfig;

                // Rotate picture back to zero degrees by swapping width and height.
                if (psOutputConfig->eRotMode == VDEC_ROTATE_90 ||
                    psOutputConfig->eRotMode == VDEC_ROTATE_270)
                {
                    IMG_UINT32 ui32Width = sBufConfig.ui32CodedWidth;
                    sBufConfig.ui32CodedWidth = sBufConfig.ui32CodedHeight;
                    sBufConfig.ui32CodedHeight = ui32Width;
                }

                // For bandwidth efficiency just use the external buffer properties
                // without any transformations (rotation/scaling etc.).
                VDECDDUTILS_ConvertBufferConfig(&psPltStrCtx->sConfig,
                                                &sBufConfig,
                                                psComSeqHdrInfo,
                                                &psPictResInfo->sAuxPictRendInfo);

                psPictResInfo->sAuxPictBufConfig = sBufConfig;
            }
            else
            {
                VDEC_sPictRendConfig    sPictRendConfig;
                VDEC_sStrOutputConfig   sAuxStrOutputConfig;

                // Reset the auxiliary output config (all transformations are turned off)
                // and apply the current bitstream settings.
                VDEC_BZERO(&sAuxStrOutputConfig);
                sAuxStrOutputConfig.sPixelInfo = psComSeqHdrInfo->sPixelInfo;

                // Reset and populate the picture render region configuration.
                VDEC_BZERO(&sPictRendConfig);
                sPictRendConfig.sCodedPictSize = sCodedPictSize;
#ifdef VDEC_TARGET_CEDARVIEW
                sPictRendConfig.bUseExtendedStrides = IMG_FALSE;
#else
                sPictRendConfig.bUseExtendedStrides = 1;
#endif
                // IPGear 29610 - VC1 AP streams
                if ((psPltStrCtx->sConfig.eVidStd == VDEC_STD_VC1) // only VC1
                    && (psComSeqHdrInfo->bPostProcessing)          // range mapping enabled.
                    && (!psOutputConfig->bForceOold)               // no oold
                    && (!psOutputConfig->bScale)                   // no scaling
                    && (psOutputConfig->eRotMode == VDEC_ROTATE_0))// no rotation.
                {
                    sPictRendConfig.sCodedPictSize.ui32Width = psDispPictBuf->sBufConfig.aui32Stride[VDEC_PLANE_VIDEO_Y];
                    sPictRendConfig.sCodedPictSize.ui32Height = sCodedPictSize.ui32Height;
                }

                // When the reconstructed picture buffer information is not yet set
                // calculate the optimal (memory usage) auxiliary layout based on
                // current bitstream properties.
                ui32Result = VDECDDUTILS_PictBufGetInfo(&psPltStrCtx->sConfig,
                                                        &sPictRendConfig,
                                                        &sAuxStrOutputConfig,
                                                        &psPictResInfo->sAuxPictRendInfo);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }

                ui32Result = VDECDDUTILS_PictBufGetConfig(&psPltStrCtx->sConfig,
                                                          &sPictRendConfig,
                                                          IMG_FALSE,
                                                          &sAuxStrOutputConfig,
                                                          &psPictResInfo->sAuxPictBufConfig);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }
            }
        }
        else
        {
            // Auxiliary picture buffers must adhere to the current reconstructed layout
            // so just take on the reconstructed picture buffer information.
            // Since the picture size, pixel format and stride must be the same there is not
            // much scope for making this buffer layout anymore memory efficient.
            psPictResInfo->sAuxPictRendInfo = psPltStrCtx->sReconPictBuf.sRendInfo;
            psPictResInfo->sAuxPictBufConfig = psPltStrCtx->sReconPictBuf.sBufConfig;
        }
    }

    IMG_ASSERT(psPltStrCtx->psStdSpecOps);
    if(psPltStrCtx->psStdSpecOps->pfBufsGetSize)
    {
        psPltStrCtx->psStdSpecOps->pfBufsGetSize(psPltStrCtx,
                                        psComSeqHdrInfo,
                                        &sCodedPictSize,
                                                 &psPictResInfo->sSizeInfo,
                                                 psSeqResInfo,
                                                 &bResourceNeeded);
    }
    /* If any picture resources are needed... */
    if ((psPictResInfo->sAuxPictRendInfo.ui32RenderedSize > 0) || bResourceNeeded)
    {
        IMG_UINT32 ui32MaxRefPicNum;

        /* Calculate the number of reference buffers required. */
        ui32Result = VDECDDUTILS_RefPictGetMaxNum(&psPltStrCtx->sConfig, psComSeqHdrInfo, &ui32MaxRefPicNum);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }

        /* Return the number of resources required:
         * the number of reference buffers plus the current picture buffer. */
        psPictResInfo->ui32PictResNum = ui32MaxRefPicNum + 1;

        /* Allow the device to be fully-loaded with resources for maximum hardware utilisation. */
        psPictResInfo->ui32PictResNum += gui32NumPipes * gsDevConfig.ui32NumSlotsPerPipe - 1;                       // Master core.
        psPictResInfo->ui32PictResNum += ((gui32NumCores - 1) * gsDevConfig.ui32NumSlotsPerPipe * gui32NumPipes);   // Slave cores.
        psPictResInfo->ui32PictResNum++;
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              plant_IsStreamResourceSuitable

******************************************************************************/
static IMG_BOOL plant_IsStreamResourceSuitable(
    PLANT_sStreamContext        * psPltStrCtx,
    const VDEC_sComSequHdrInfo  * psComSeqHdrInfo,
    const VDEC_sStrOutputConfig * psOutputConfig,
    const VDECDD_sDdPictBuf     * psDispPictBuf,
    PLANT_sPictResInfo          * psPictResInfo,
    PLANT_sSeqResInfo           * psSeqResInfo
)
{
    IMG_RESULT              ui32Result;
    PLANT_sPictResInfo      sAuxPictResInfo;
    PLANT_sPictResInfo    * psAuxPictResInfo;
    PLANT_sSeqResInfo       sSeqResInfo;

    /* If resource info is needed externally, just use it. Otherwise use internal structure. */
    if (IMG_NULL != psPictResInfo)
    {
        psAuxPictResInfo = psPictResInfo;
    }
    else
    {
        psAuxPictResInfo = &sAuxPictResInfo;
    }

    if (IMG_NULL == psSeqResInfo)
    {
        psSeqResInfo = &sSeqResInfo;
    }

    /* Get the resource info for current settings. */
    ui32Result = plant_PictResGetInfo(
                        psPltStrCtx,
                        psComSeqHdrInfo,
                        psOutputConfig,
                        psDispPictBuf,
                        psAuxPictResInfo,
                        psSeqResInfo);
    IMG_ASSERT(IMG_SUCCESS == ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        return IMG_FALSE;
    }

    /* Check the auxiliary buffer size against the size of currently allocated auxiliary buffers. */
    if (psAuxPictResInfo->sAuxPictRendInfo.ui32RenderedSize > psPltStrCtx->sPictResInfo.sAuxPictRendInfo.ui32RenderedSize)
    {
        return IMG_FALSE;
    }

    /* Check the size against the size of currently allocated MB parameters buffers. */
    if (psAuxPictResInfo->sSizeInfo.ui32MBParamsBufSize > psPltStrCtx->sPictResInfo.sSizeInfo.ui32MBParamsBufSize)
    {
        return IMG_FALSE;
    }

    IMG_ASSERT(psPltStrCtx->psStdSpecOps);
    if(psPltStrCtx->psStdSpecOps->pfIsStreamResourceSuitable)
    {
        if (!psPltStrCtx->psStdSpecOps->pfIsStreamResourceSuitable(psAuxPictResInfo, &psPltStrCtx->sPictResInfo, psSeqResInfo, &psPltStrCtx->sSeqResInfo))
        {
            return IMG_FALSE;
        }
    }

    /* Check the number of picture resources required against the current number. */
    if (psAuxPictResInfo->ui32PictResNum > psPltStrCtx->sPictResInfo.ui32PictResNum)
    {
        return IMG_FALSE;
    }

    return IMG_TRUE;
}


/*!
******************************************************************************

 @Function              plant_DoResourceRealloc

******************************************************************************/
static IMG_BOOL plant_DoResourceRealloc(
    PLANT_sStreamContext *  psPltStrCtx,
    PLANT_sPictResInfo *    psPictResInfo,
    PLANT_sSeqResInfo     * psSeqResInfo
)
{
    IMG_ASSERT(psPltStrCtx->psStdSpecOps);
    /* If buffer sizes are sufficient and only the greater number of resources is needed... */
    if ((psPltStrCtx->sPictResInfo.sSizeInfo.ui32MBParamsBufSize >= psPictResInfo->sSizeInfo.ui32MBParamsBufSize) &&
        (psPltStrCtx->sPictResInfo.sAuxPictRendInfo.ui32RenderedSize >= psPictResInfo->sAuxPictRendInfo.ui32RenderedSize) &&
        ((psPltStrCtx->psStdSpecOps->pfIsStreamResourceSuitable) ?
        psPltStrCtx->psStdSpecOps->pfIsStreamResourceSuitable(psPictResInfo, &psPltStrCtx->sPictResInfo, psSeqResInfo, &psPltStrCtx->sSeqResInfo): IMG_TRUE) &&
        (psPltStrCtx->sPictResInfo.ui32PictResNum < psPictResInfo->ui32PictResNum))
    {
        /* ...full internal resource reallocation is not required. */
        return IMG_FALSE;
    }

    /* Otherwise request full internal resource reallocation. */
    return IMG_TRUE;
}



/*!
******************************************************************************

 @Function              PLANT_Initialise

 ******************************************************************************/
IMG_RESULT PLANT_Initialise(
    IMG_VOID *              pvInitUserData,
    VDECDD_pfnCompCallback  pfnCallback,
    VDECDD_sDdDevConfig     sDdDevConfig,
    IMG_UINT32              ui32NumCores,
    IMG_UINT32              ui32NumPipes
)
{
    IMG_RESULT ui32Result = IMG_SUCCESS;

    if (!bInitialised)
    {
        IMG_ASSERT(pfnCallback);
        IMG_ASSERT(pvInitUserData);
        pfnCompCallback = pfnCallback;
        pvCompInitUserData = pvInitUserData;

        gsDevConfig = sDdDevConfig;
        gui32NumCores = ui32NumCores;
        gui32NumPipes = ui32NumPipes;

        LST_init(&sStreamList);

        bInitialised = IMG_TRUE;
    }
    else
    {
        REPORT(REPORT_MODULE_PLANT, REPORT_WARNING,
            "Plant already initialised");
        ui32Result = IMG_ERROR_ALREADY_INITIALISED;
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              PLANT_Deinitialise

******************************************************************************/
IMG_RESULT PLANT_Deinitialise(
    IMG_VOID
)
{
    IMG_RESULT ui32Result = IMG_SUCCESS;

    if (bInitialised)
    {
        // Stream lists should be empty.
        IMG_ASSERT(LST_empty(&sStreamList));

        pfnCompCallback = IMG_NULL;
        pvCompInitUserData = IMG_NULL;

        bInitialised = IMG_FALSE;
    }
    else
    {
        REPORT(REPORT_MODULE_PLANT, REPORT_WARNING,
            "Plant not initialised");
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              PLANT_StreamCreate

******************************************************************************/
IMG_RESULT PLANT_StreamCreate(
    VDEC_sStrConfigData *  psStrConfig,
    IMG_HANDLE             hMmuStrHandle,
    IMG_VOID *             pvStrUserData,
    IMG_HANDLE *           phPltStrCtx
)
{
    PLANT_sStreamContext * psPltStrCtx;
    IMG_RESULT ui32Result = IMG_SUCCESS;

    IMG_ASSERT(bInitialised);
    if (!bInitialised)
    {
        REPORT(REPORT_MODULE_PLANT, REPORT_WARNING,
            "[USERSID=0x%08X] Plant not initialised",
            psStrConfig->ui32UserStrId);
        ui32Result = IMG_ERROR_NOT_INITIALISED;
        return ui32Result;
    }

    VDEC_MALLOC(psPltStrCtx);
    IMG_ASSERT(psPltStrCtx);
    if(psPltStrCtx == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    // Initialise the context structure to NULL. Any non-zero
    // default values should be set at this point.
    VDEC_BZERO(psPltStrCtx);
    psPltStrCtx->sConfig = *psStrConfig;
    psPltStrCtx->pvUserData = pvStrUserData;
    psPltStrCtx->hMmuStrHandle = hMmuStrHandle;
    LST_init(&psPltStrCtx->sPictResList);
    LST_init(&psPltStrCtx->sOldPictResList);
#ifdef SEQ_RES_NEEDED
    LST_init(&psPltStrCtx->sSeqResList);
    LST_init(&psPltStrCtx->sOldSeqResList);
#endif /* SEQ_RES_NEEDED */
    LST_init(&psPltStrCtx->sPictBufList);

    LST_add(&sStreamList, psPltStrCtx);

    psPltStrCtx->psStdSpecOps = &asStdSpecOps[psStrConfig->eVidStd - 1];

    *phPltStrCtx = (IMG_HANDLE)psPltStrCtx;

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              PLANT_StreamDestroy

******************************************************************************/
IMG_RESULT PLANT_StreamDestroy(
    IMG_HANDLE  hPltStrCtx
)
{
    PLANT_sStreamContext * psPltStrCtx;
    IMG_RESULT ui32Result = IMG_SUCCESS;

    IMG_ASSERT(bInitialised);
    if (!bInitialised)
    {
        REPORT(REPORT_MODULE_PLANT, REPORT_WARNING,
            "Plant not initialised");
        ui32Result = IMG_ERROR_NOT_INITIALISED;
        return ui32Result;
    }

    psPltStrCtx = plant_StreamGetContext(hPltStrCtx);

    ui32Result = plant_StreamDestroy(psPltStrCtx);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    return IMG_SUCCESS;
}

static IMG_RESULT plant_AllocCommonPictBuffers(
    PLANT_sStreamContext * psPltStrCtx,
    VDECDD_sPictResInt   * psPictResInt,
    VXDIO_sMemPool         sMemPool,
    PLANT_sPictResInfo   * psPictResInfo)
{
    IMG_RESULT ui32Result;

    /* If MB params buffers are needed... */
    if (psPictResInfo->sSizeInfo.ui32MBParamsBufSize > 0)
    {
        /* Allocate the MB parameters buffer info structure. */
        PLANT_ALLOC_RES_BUFF(psPictResInt->psMBParamBuf,
                             psPictResInfo->sSizeInfo.ui32MBParamsBufSize,
                             psPltStrCtx->hMmuStrHandle,
                             sMemPool,
                             ui32Result);

        if (IMG_SUCCESS != ui32Result)
        {
            return IMG_ERROR_OUT_OF_MEMORY;
        }
    }

    /* If auxiliary picture buffers are needed... */
    if (psPictResInfo->sAuxPictRendInfo.ui32RenderedSize > 0)
    {
        /* Allocate the auxiliary picture buffer info structure. */
        VDEC_MALLOC(psPictResInt->psDdPictBuf);
        IMG_ASSERT(IMG_NULL != psPictResInt->psDdPictBuf);
        if(IMG_NULL == psPictResInt->psDdPictBuf)
        {
            return IMG_ERROR_OUT_OF_MEMORY;
        }
        VDEC_BZERO(psPictResInt->psDdPictBuf);

        PLANT_ALLOC_RES_BUFF(psPictResInt->psDdPictBuf->psPictBuf,
                             psPictResInfo->sAuxPictRendInfo.ui32RenderedSize,
                             psPltStrCtx->hMmuStrHandle,
                             sMemPool,
                             ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            return IMG_ERROR_OUT_OF_MEMORY;
        }
        psPictResInt->psDdPictBuf->sRendInfo = psPictResInfo->sAuxPictRendInfo;
        psPictResInt->psDdPictBuf->sBufConfig = psPictResInfo->sAuxPictBufConfig;
    }

    return ui32Result;
}

/*!
******************************************************************************

 @Function              PLANT_StreamResourceCreate

******************************************************************************/
IMG_RESULT PLANT_StreamResourceCreate(
    IMG_HANDLE                    hPltStrCtx,
    IMG_BOOL                      bClosedGOP,
    VXDIO_sMemPool                sMemPool,
    const VDEC_sComSequHdrInfo  * psComSeqHdrInfo,
    const VDEC_sStrOutputConfig * psOutputConfig,
    const VDECDD_sDdPictBuf     * psDispPictBuf
)
{
    PLANT_sStreamContext * psPltStrCtx;
    VDECDD_sPictResInt * psPictResInt = IMG_NULL;
    VDECDD_sSeqResInt  * psSeqResInt = IMG_NULL;
    IMG_RESULT ui32Result = IMG_SUCCESS;
    IMG_UINT32 i, startCnt = 0;
    PLANT_sPictResInfo sPictResInfo;
    PLANT_sSeqResInfo sSeqResInfo;

    IMG_ASSERT(bInitialised);
    if (!bInitialised)
    {
        REPORT(REPORT_MODULE_PLANT, REPORT_WARNING,
            "Plant not initialised");
        return IMG_ERROR_NOT_INITIALISED;
    }

    /* Get the PLANT stream context. */
    psPltStrCtx = plant_StreamGetContext(hPltStrCtx);
#ifdef SEQ_RES_NEEDED
    psSeqResInt = LST_first(&psPltStrCtx->sSeqResList);
#endif /* SEQ_RES_NEEDED */
    // Clear the reconstructed picture buffer layout if the previous references are no longer used.
    // Only under these circumstances should the bitstream resolution change.
    if (bClosedGOP)
    {
        VDEC_BZERO(&psPltStrCtx->sReconPictBuf.sRendInfo);
        VDEC_BZERO(&psPltStrCtx->sCodedPictSize);
    }
    else
    {
        if (VDEC_SIZE_NE(psPltStrCtx->sCodedPictSize, psComSeqHdrInfo->sMaxFrameSize))
        {
            IMG_ASSERT(IMG_FALSE);
            REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                "[USERSID=0x%08X] Coded picture size changed within the closed GOP (i.e. mismatched references)",
                psPltStrCtx->sConfig.ui32UserStrId);
        }
    }

    /* If current buffers are not suitable for specified VSH/Output config... */
    if (!plant_IsStreamResourceSuitable(hPltStrCtx, psComSeqHdrInfo, psOutputConfig, psDispPictBuf, &sPictResInfo, &sSeqResInfo))
    {
        /* If full internal resource reallocation is needed... */
        if (plant_DoResourceRealloc(psPltStrCtx, &sPictResInfo, &sSeqResInfo))
        {
            /* Mark all the active resources as deprecated and
               free-up where no longer used. */
            plant_StreamResourceDeprecate(psPltStrCtx);
        }
        else
        {
            /* Use current buffer size settings. */
            sPictResInfo.sSizeInfo = psPltStrCtx->sPictResInfo.sSizeInfo;
            sPictResInfo.sAuxPictRendInfo = psPltStrCtx->sPictResInfo.sAuxPictRendInfo;
            sPictResInfo.sAuxPictBufConfig = psPltStrCtx->sPictResInfo.sAuxPictBufConfig;
            sSeqResInfo = psPltStrCtx->sSeqResInfo;

            /* Set start counter to only allocate the number of resources that are missing. */
            startCnt = psPltStrCtx->sPictResInfo.ui32PictResNum;
        }

#ifdef SEQ_RES_NEEDED
        /* allocate sequence resources */
        {
            VDEC_MALLOC(psSeqResInt);
            IMG_ASSERT(IMG_NULL != psSeqResInt);
            if(IMG_NULL == psSeqResInt)
            {
                goto err_out_of_memory;
            }
            VDEC_BZERO(psSeqResInt);
            LST_add(&psPltStrCtx->sSeqResList, psSeqResInt);

            IMG_ASSERT(psPltStrCtx->psStdSpecOps);
            if(psPltStrCtx->psStdSpecOps->pfAllocSequenceBuffers)
            {
                ui32Result = psPltStrCtx->psStdSpecOps->pfAllocSequenceBuffers(psPltStrCtx,
                                                                               psSeqResInt,
                                                                               sMemPool,
                                                                               &sSeqResInfo);
                if(ui32Result != IMG_SUCCESS)
                {
                        goto err_out_of_memory;
                    }
                    }
                }
#endif

        /* Allocate resources for current settings. */
        for (i = startCnt; i < sPictResInfo.ui32PictResNum; i++)
        {
            /* Allocate the picture resources structure. */
            VDEC_MALLOC(psPictResInt);
            IMG_ASSERT(IMG_NULL != psPictResInt);
            if(IMG_NULL == psPictResInt)
            {
                goto err_out_of_memory;
            }
            VDEC_BZERO(psPictResInt);

            /* Allocate picture buffers common for all standards. */
            ui32Result = plant_AllocCommonPictBuffers(psPltStrCtx,
                                                      psPictResInt,
                                                      sMemPool,
                                                      &sPictResInfo);
            if(ui32Result != IMG_SUCCESS)
                {
                    goto err_out_of_memory;
                }

            /* Allocate standard specific picture buffers. */
            IMG_ASSERT(psPltStrCtx->psStdSpecOps);
            if(psPltStrCtx->psStdSpecOps->pfAllocPictureBuffers)
                {
                ui32Result = psPltStrCtx->psStdSpecOps->pfAllocPictureBuffers(psPltStrCtx,
                                                                              psPictResInt,
                                                                              sMemPool,
                                                                              &sPictResInfo);
                if(ui32Result != IMG_SUCCESS)
            {
                    goto err_out_of_memory;
                }
                }

            LST_add(&psPltStrCtx->sPictResList, psPictResInt);
            psPltStrCtx->sPictResInfo.ui32PictResNum++;
        }
    }

    // Set the reconstructed picture buffer information.
    {
        PLANT_sDetachedAuxPict    * psDetachedAuxPict;
        VDEC_sPictRendInfo          sRendInfo;
        VDEC_sPictBufConfig         sBufConfig;

        if (sPictResInfo.sAuxPictRendInfo.ui32RenderedSize == 0)
        {
            sRendInfo = psDispPictBuf->sRendInfo;
            sBufConfig = psDispPictBuf->sBufConfig;

            // Temporarily remove all aux picture buffers from internal resources
            // to ensure that the Decoder uses the display buffers for reference.
            psPictResInt = LST_first(&psPltStrCtx->sPictResList);
            while (psPictResInt)
            {
                if (psPictResInt->psDdPictBuf)
                {
                    VDEC_MALLOC(psDetachedAuxPict);
                    IMG_ASSERT(psDetachedAuxPict);
                    if (psDetachedAuxPict == IMG_NULL)
                    {
                        goto err_out_of_memory;
                    }

                    psDetachedAuxPict->psPictBuf = psPictResInt->psDdPictBuf;
                    psDetachedAuxPict->psPictResInt = psPictResInt;

                    LST_add(&psPltStrCtx->sPictBufList, psDetachedAuxPict);

                    // Clear the aux picture buffer pointer.
                    psPictResInt->psDdPictBuf = IMG_NULL;
                }

                psPictResInt = LST_next(psPictResInt);
            }
        }
        else
        {
            PLANT_sDetachedAuxPict * psNextDetachedAuxPict = IMG_NULL;

            sRendInfo = sPictResInfo.sAuxPictRendInfo;
            sBufConfig = sPictResInfo.sAuxPictBufConfig;

            // Ensure that all internal resources have picture buffers attached.
            // If these were previously removed, re-attach.
            psDetachedAuxPict = LST_first(&psPltStrCtx->sPictBufList);
            while (psDetachedAuxPict)
            {
                psNextDetachedAuxPict = LST_next(psDetachedAuxPict);

                psPictResInt = LST_first(&psPltStrCtx->sPictResList);
                while (psPictResInt)
                {
                    if (psPictResInt == psDetachedAuxPict->psPictResInt)
                    {
                        // Reattach and remove from pict buf list.
                        psPictResInt->psDdPictBuf = psDetachedAuxPict->psPictBuf;
                        LST_remove(&psPltStrCtx->sPictBufList, psDetachedAuxPict);
                        IMG_FREE(psDetachedAuxPict);
                        psDetachedAuxPict = IMG_NULL;
                        break;
                    }

                    psPictResInt = LST_next(psPictResInt);
                }

                IMG_ASSERT(psDetachedAuxPict == IMG_NULL);

                psDetachedAuxPict = psNextDetachedAuxPict;
            }
        }

        plant_PrintBufferConfig(
            (psPltStrCtx->sReconPictBuf.sRendInfo.ui32RenderedSize == 0)
                ? IMG_TRUE : IMG_FALSE,
            psOutputConfig,
            &sRendInfo,
            &sBufConfig,
            &sPictResInfo.sAuxPictRendInfo,
            &psDispPictBuf->sRendInfo,
            &psDispPictBuf->sBufConfig);

        // Set the reconstructed buffer properties if they
        // may have been changed.
        if (psPltStrCtx->sReconPictBuf.sRendInfo.ui32RenderedSize == 0)
        {
            psPltStrCtx->sReconPictBuf.sRendInfo = sRendInfo;
            psPltStrCtx->sReconPictBuf.sBufConfig = sBufConfig;
            psPltStrCtx->sCodedPictSize = psComSeqHdrInfo->sMaxFrameSize;
        }
        else
        {
            if (IMG_MEMCMP(&sRendInfo, &psPltStrCtx->sReconPictBuf.sRendInfo, sizeof(sRendInfo)))
            {
                // Reconstructed picture buffer information has changed during a closed GOP.
                IMG_ASSERT("Reconstructed picture buffer information cannot change within a GOP" == IMG_NULL);
                REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
                        "[USERSID=0x%08X] Reconstructed picture buffer information cannot change within a GOP.",
                        psPltStrCtx->sConfig.ui32UserStrId);
            }
        }
    }

    if (sPictResInfo.sAuxPictRendInfo.ui32RenderedSize == 0)
    {
        // Preserve the old aux picture buffer info it is was not used this time.
        sPictResInfo.sAuxPictRendInfo = psPltStrCtx->sPictResInfo.sAuxPictRendInfo;
    }

    /* Store the current resource config. */
    psPltStrCtx->sPictResInfo = sPictResInfo;
    psPltStrCtx->sSeqResInfo = sSeqResInfo;

    // Push all resources out of plant
    psPictResInt = LST_first(&psPltStrCtx->sPictResList);
    while (psPictResInt)
    {
        // Increment the reference count to indicate that this resource is also
        // held by plant until it is added to the Scheduler list. If the the
        // resource has not just been created it might already be in circulation.
        RESOURCE_ItemUse(&psPictResInt->ui32RefCount);

        // In case when current buffers are suitable for new output, we need to
        // update all resources with the new info, since it may have changed.
        if (psPictResInt->psDdPictBuf)
        {
            psPictResInt->psDdPictBuf->sRendInfo = psPltStrCtx->sReconPictBuf.sRendInfo;
            psPictResInt->psDdPictBuf->sBufConfig = psPltStrCtx->sReconPictBuf.sBufConfig;
        }

        /* attach sequence resources */
#ifdef SEQ_RES_NEEDED
        RESOURCE_ItemUse(&psSeqResInt->ui32RefCount);
        psPictResInt->psSeqResInt = psSeqResInt;
#endif /* SEQ_RES_NEEDED */

        ui32Result = pfnCompCallback(
            PLANT_CB_PICTURE_RESOURCE_ADD,
            pvCompInitUserData,
            IMG_NULL,
            psPltStrCtx->pvUserData,
            psPictResInt);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }

        psPictResInt = LST_next(psPictResInt);
    }

    return IMG_SUCCESS;

    /* Handle out of memory errors. */
err_out_of_memory:
    /* Free resources being currently allocated. */
    if (IMG_NULL != psPictResInt)
    {
        plant_FreeCommonPictureResource(psPictResInt);

        if(psPltStrCtx->psStdSpecOps->pfFreePictureResource)
        {
            psPltStrCtx->psStdSpecOps->pfFreePictureResource(psPictResInt);
            }

        IMG_FREE(psPictResInt);
    }

#ifdef SEQ_RES_NEEDED
    if (IMG_NULL != psSeqResInt)
    {
        if(psPltStrCtx->psStdSpecOps->pfFreeSequenceResource)
        {
            psPltStrCtx->psStdSpecOps->pfFreeSequenceResource(psSeqResInt);
                }

        IMG_ASSERT(LST_last(&psPltStrCtx->sSeqResList) == psSeqResInt);
        LST_remove(&psPltStrCtx->sSeqResList, psSeqResInt);

        IMG_FREE(psSeqResInt);
    }
#endif /* SEQ_RES_NEEDED */

    /* Free all the other resources. */
    plant_StreamResourceDestroy(psPltStrCtx);

    REPORT(REPORT_MODULE_PLANT, REPORT_ERR,
            "[USERSID=0x%08X] Plant not able to allocate stream resources due to lack of memory",
            psPltStrCtx->sConfig.ui32UserStrId);

    return IMG_ERROR_OUT_OF_MEMORY;
}


/*!
******************************************************************************

 @Function              PLANT_StreamResourceDestroy

******************************************************************************/
IMG_RESULT PLANT_StreamResourceDestroy(
    IMG_HANDLE  hPltStrCtx
)
{
    PLANT_sStreamContext * psPltStrCtx;
    IMG_RESULT ui32Result = IMG_SUCCESS;

    IMG_ASSERT(bInitialised);
    if (!bInitialised)
    {
        REPORT(REPORT_MODULE_PLANT, REPORT_WARNING,
            "Plant not initialised");
        ui32Result = IMG_ERROR_NOT_INITIALISED;
        return ui32Result;
    }

    psPltStrCtx = plant_StreamGetContext(hPltStrCtx);

    ui32Result = plant_StreamResourceDestroy(psPltStrCtx);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);

    return ui32Result;
}

/*!
******************************************************************************

 @Function              PLANT_IsStreamResourceSuitable

******************************************************************************/
IMG_BOOL PLANT_IsStreamResourceSuitable(
    IMG_HANDLE                      hPltStrCtx,
    const VDEC_sComSequHdrInfo    * psComSeqHdrInfo,
    const VDEC_sStrOutputConfig   * psOutputConfig,
    const VDECDD_sDdPictBuf       * psDispPictBuf
)
{
    PLANT_sStreamContext * psPltStrCtx;

    /* Check if PLANT is initialised. */
    IMG_ASSERT(bInitialised);
    if (!bInitialised)
    {
        return IMG_FALSE;
    }

    /* Get the PLANT stream context. */
    psPltStrCtx = plant_StreamGetContext(hPltStrCtx);

    /* Check the suitability of internal resources. */
    return plant_IsStreamResourceSuitable(psPltStrCtx, psComSeqHdrInfo, psOutputConfig, psDispPictBuf, IMG_NULL, IMG_NULL);
}
