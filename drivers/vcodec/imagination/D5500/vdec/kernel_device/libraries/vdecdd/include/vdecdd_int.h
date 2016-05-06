/*!
 *****************************************************************************
 *
 * @File       vdecdd_int.h
 * @Title      VDECDD Internal Structures etc.
 * @Description    This file contains the VDECDD Internal Structures etc.
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

#ifndef __VDECDD_INT_H__
#define __VDECDD_INT_H__

#include "img_defs.h"
#include "vdec_api.h"
#include "vdecdd.h"
#include "vdecdd_utils.h"
#include "vdecdd_mmu_defs.h"

#ifdef __cplusplus
extern "C" {
#endif


#define VDECDD_STREAM_TYPE_ID    (0xB0B00001)    /*!< RMAN type for streams.          */
#define VDECDD_BUFMAP_TYPE_ID    (0xB0B00002)    /*!< RMAN type for buffer mappings.  */

/*!
******************************************************************************
 This type defines the Component Callback groups.
 @brief  VDEDD Component Callback Groups
******************************************************************************/
typedef enum
{
    VDECDD_CBGRP_PLANT     = 0x01000000,        /*!< Base of Plant CB events.      */
    VDECDD_CBGRP_SCHEDULER = 0x02000000,        /*!< Base of Scheduler CB events.  */
    VDECDD_CBGRP_DECODER   = 0x04000000,        /*!< Base of Decoder CB events.    */

} VDECDD_eCompCallbackGroups;


/*!
******************************************************************************
 This type defines the level up to (and including) which to decode.
 NOTE: The ordering of these levels is critical and should not be amended without
 caution. An array of strings (apszDecodeLevels in core_api.c) maps onto this enum and
 should be kept in sync
 @brief  VDECDD Decode Levels
******************************************************************************/
typedef enum
{
    VDECDD_DECODELEVEL_SCHEDULER = 0,       /*!< Stream is processed down to the Scheduler (VXD not required).  */
    VDECDD_DECODELEVEL_DECODER,             /*!< Stream is processed down to the Decoder (VXD not required).    */
    VDECDD_DECODELEVEL_FWHDRPARSING,        /*!< Stream is processed down to the firmware
                                                 slice-level but no hardware decoding takes place.              */
    VDECDD_DECODELEVEL_FEHWDECODING,        /*!< Stream is processed at the Front-end but skipped on the
                                                 back-end.                                                      */
    VDECDD_DECODELEVEL_MAX,                 /*!< Stream is fully processed (decoded).                           */

} VDECDD_eDecodeLevel;


/*!
******************************************************************************
 This type contains core feature flags.
 @brief  Core Feature Flags
******************************************************************************/
typedef enum
{
    VDECDD_COREFEATURE_MPEG2             = (1<<0),   /*!< MPEG2 (includes MPEG1).                         */
    VDECDD_COREFEATURE_MPEG4             = (1<<1),   /*!< MPEG4 (includes H263 and Sorenson Spark).       */
    VDECDD_COREFEATURE_H264              = (1<<2),   /*!< H264.                                           */
    VDECDD_COREFEATURE_VC1               = (1<<3),   /*!< VC1 (includes WMV9).                            */
    VDECDD_COREFEATURE_AVS               = (1<<4),   /*!< AVS.                                            */
    VDECDD_COREFEATURE_REAL              = (1<<5),   /*!< RealVideo (RV30 and RV40).                      */
    VDECDD_COREFEATURE_JPEG              = (1<<6),   /*!< JPEG.                                           */
    VDECDD_COREFEATURE_VP6               = (1<<7),   /*!< On2 VP6.                                        */
    VDECDD_COREFEATURE_VP8               = (1<<8),   /*!< On2 VP8.                                        */
    VDECDD_COREFEATURE_HEVC              = (1<<9),   /*!< HEVC.                                           */

    VDECDD_COREFEATURE_HD_DECODE         = (1<<10),  /*!< Supports HD decode.                             */
    VDECDD_COREFEATURE_ROTATION          = (1<<11),  /*!< Supports Rotation.                              */
    VDECDD_COREFEATURE_SCALING           = (1<<12),  /*!< Supports scaling.                               */
    VDECDD_COREFEATURE_SCALING_WITH_OOLD = (1<<13),  /*!< Supports scaling with out-of-loop de-blocking.  */
    VDECDD_COREFEATURE_EXTENDED_STRIDES  = (1<<14),  /*!< Supports extended strides.                      */

} VDECDD_eCoreFeatureFlags;


/*!
******************************************************************************
 This type defines unsupported stream configuration features.
 @brief  Unsupported Stream Configuration Flags
******************************************************************************/
typedef enum
{
    VDECDD_UNSUPPORTED_STRCONFIG_STD          = (1 << 0),       /*!< Video standard unsupported or unrecognised.    */
    VDECDD_UNSUPPORTED_STRCONFIG_BSTRFORMAT   = (1 << 1),       /*!< Currently unused.                              */

} VDEC_eUnSupportedStrConfig;


/*!
******************************************************************************
 This type defines unsupported output configuration features.
 @brief  Unsupported Output Configuration Flags
******************************************************************************/
typedef enum
{
    VDECDD_UNSUPPORTED_OUTPUTCONFIG_ROTATION                  = (1 << 0),       /*!< Rotation is not supported.                         */
    VDECDD_UNSUPPORTED_OUTPUTCONFIG_ROTATION_WITH_FIELDS      = (1 << 1),       /*!< Rotation is not supported with field coded
                                                                                     pictures or field coded MBs.                       */
    VDECDD_UNSUPPORTED_OUTPUTCONFIG_ROTATION_WITH_SCALING     = (1 << 2),       /*!< Rotation and scaling are not supported together.   */
    VDECDD_UNSUPPORTED_OUTPUTCONFIG_SCALING                   = (1 << 3),       /*!< Scaling is not supported.                          */
    VDECDD_UNSUPPORTED_OUTPUTCONFIG_UP_DOWNSAMPLING           = (1 << 4),       /*!< Up/down-sampling combination is not supported
                                                                                     (only valid conversion is 420 --> 422).            */
    VDECDD_UNSUPPORTED_OUTPUTCONFIG_SCALING_WITH_OOLD         = (1 << 5),       /*!< Scaling is not supported with Out of Loop
                                                                                     deblocking.                                        */
    VDECDD_UNSUPPORTED_OUTPUTCONFIG_SCALING_MONOCHROME        = (1 << 6),       /*!< Scaling of monochrome stream is not supported.     */
    VDECDD_UNSUPPORTED_OUTPUTCONFIG_SCALING_SIZE              = (1 << 7),       /*!< Scale size is not supported.                       */
    VDECDD_UNSUPPORTED_OUTPUTCONFIG_X_WITH_JPEG               = (1 << 8),       /*!< Feature is not supported with JPEG (might be one
                                                                                     of rotation, scaling or OOLD).                     */
    VDECDD_UNSUPPORTED_OUTPUTCONFIG_SCALESIZE                 = (1 << 9),       /*!< Unused.                                            */
    VDECDD_UNSUPPORTED_OUTPUTCONFIG_PIXFORMAT                 = (1 << 10),      /*!< Pixel format cannot be generated from native
                                                                                     stream format with hardware.                       */
    VDECDD_UNSUPPORTED_OUTPUTCONFIG_ROTATION_WITH_HIGH_COLOUR = (1 << 11),      /*!< .                                                  */
    VDECDD_UNSUPPORTED_OUTPUTCONFIG_DOWNSAMPLING_WITH_ROTATION = (1 << 12),     /*!< .                                                  */
    VDECDD_UNSUPPORTED_OUTPUTCONFIG_ROTATION_WITH_10BIT_PACKED = (1 << 13),     /*!< .                                                  */

} VDEC_eUnSupportedOutputConfig;


/*!
******************************************************************************
 This type defines unsupported output configuration features.
 @brief  Unsupported Output Configuration Flags
******************************************************************************/
typedef enum
{
    VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_EXTENDED_STRIDE  = (1 << 0),        /*!< Unused.                                                 */
    VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_64BYTE_STRIDE    = (1 << 1),        /*!< Stride must be a multiple of 64 bytes.                  */
    VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_FIXED_STRIDE     = (1 << 2),        /*!< Stride not found amongst the (fixed) video strides
                                                                                supported by VXD.                                       */
    VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_PICTURE_SIZE     = (1 << 3),        /*!< Picture dimensions declared for buffer are not large
                                                                                enough for bitstream (sequence) or output configuration.*/
    VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_BUFFER_SIZE      = (1 << 4),        /*!< Buffer size not large enough for bitstream (sequence)
                                                                                or output configuration.                                */
    VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_Y_SIZE           = (1 << 5),        /*!< Y plane of output buffer is not large enough for
                                                                                bitstream (sequence) or output configuration.           */
    VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_UV_SIZE          = (1 << 6),        /*!< UV plane of output buffer is not large enough for
                                                                                bitstream (sequence) or output configuration.           */
    VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_Y_STRIDE         = (1 << 7),        /*!< Y stride of output buffer is not large enough for
                                                                                bitstream (sequence) or output configuration.           */
    VDECDD_UNSUPPORTED_OUTPUTBUFCONFIG_UV_STRIDE        = (1 << 8),        /*!< UV stride of output buffer is not large enough for
                                                                                bitstream (sequence) or output configuration.           */

} VDEC_eUnSupportedOutputBufferConfig;


/*!
******************************************************************************
 This type defines unsupported sequence header features.
 @brief  Unsupported Sequence Header Flags
******************************************************************************/
typedef enum
{
    VDECDD_UNSUPPORTED_SEQUHDR_PIXFORMAT_BIT_DEPTH  = (1 << 0),     /*!< Bit-depth (luma and/or chroma) of pixel format is unsupported. */
    VDECDD_UNSUPPORTED_SEQUHDR_SCALING              = (1 << 1),     /*!< Unused.                                                        */
    VDECDD_UNSUPPORTED_SEQUHDR_PIXEL_FORMAT         = (1 << 2),     /*!< Pixel format (including sub-sampling) is unsupported.          */
    VDECDD_UNSUPPORTED_SEQUHDR_NUM_OF_VIEWS         = (1 << 3),     /*!< Number of MVC views unsupported by driver.                     */
    VDECDD_UNSUPPORTED_SEQUHDR_CODED_HEIGHT         = (1 << 4),     /*!< Coded height of frames not supported. This includes height of
                                                                         frame for interlaced material not a multiple pair of MBs.      */
    VDECDD_UNSUPPORTED_SEQUHDR_SEP_COLOUR_PLANE     = (1 << 5),     /*!< H264 separate colour plane support not enabled                 */
    VDECDD_UNSUPPORTED_SEQUHDR_SIZE                 = (1 << 6),     /*!< Unsupported width or height                                    */
} VDEC_eUnSupportedSequHdr;


/*!
******************************************************************************
 This type defines unsupported picture header features.
 @brief  Unsupported Picture Header Flags
******************************************************************************/
typedef enum
{
    VDECDD_UNSUPPORTED_PICTHDR_UPSCALING            = (1 << 0),     /*!< Scaled picture size is larger than the display picture.    */
    VDECDD_UNSUPPORTED_PICTHDR_OVERSIZED_SGM        = (1 << 1),     /*!< Slice Group Map present in a frame wider than 1280 pixels. */
    VDECDD_UNSUPPORTED_PICTHDR_DISCONTINUOUS_MBS    = (1 << 2),     /*!< Unused.                                                    */
    VDECDD_UNSUPPORTED_PICTHDR_RESOLUTION           = (1 << 3),     /*!< Coded frame size is outside range supported by VXD.
                                                                         Includes MPEG4 larger than 2K in either dimension and
                                                                         pre-Emerald cores not supporting MPEG4 streams less than
                                                                         6MB in width.                                              */
    VDECDD_UNSUPPORTED_PICTHDR_SCALING_ORIGINALSIZE = (1 << 4),     /*!< Scaling down from original size not supported. Includes
                                                                         scaling down from < 6 MB in either dimension.              */
    VDECDD_UNSUPPORTED_PICTHDR_SCALING_SIZE         = (1 << 5),     /*!< Scaled frame size unsupported. Must be a multiple of two
                                                                         pixels in width and two/four (field) pixels in height.
                                                                         Other restrictions exist. See source                       */
    VDECDD_UNSUPPORTED_PICTHDR_HEVC_RANGE_EXT       = (1 << 6),     /*!< . */

} VDEC_eUnSupportedPictHdr;


/*!
******************************************************************************
 This structure contains unsupported feature flags.
 @brief  Unsupported Feature Flags
******************************************************************************/
typedef struct
{
    IMG_UINT32 ui32StrConfig;           /*!< Unsupported stream configuration           */
    IMG_UINT32 ui32StrOutputConfig;     /*!< Unsupported output configuration           */
    IMG_UINT32 ui32OutputBufConfig;     /*!< Unsupported output buffer configuration    */
    IMG_UINT32 ui32SequHdr;             /*!< Unsupported sequence header                */
    IMG_UINT32 ui32PictHdr;             /*!< Unsupported picture header                 */

} VDEC_sUnSupportedFlags;

/*!
******************************************************************************
 This structure contains configuration relating to a device.
 @brief  Device Configuration
******************************************************************************/
typedef struct
{
    VDECDD_eDecodeLevel     eDecodeLevel;               /*!< Level in device to which decoding should take place.       */
    IMG_UINT32              ui32NumSlotsPerPipe;        /*!< The number of decoding slots per pipe, which defines the
                                                             number of pictures that can be scheduled to a pipe at any
                                                             one time.                                                  */

    IMG_BOOL                bAPM;                       /*!< Indicates whether Active Power Management is enabled
                                                             for the device. Power is removed from the core when
                                                             there is nothing to decode.                                */
    IMG_BOOL                bFakeMtx;                   /*!< Indicates whether firmware is executed on host. Otherwise
                                                             firmware runs on embedded MTX processor.                   */
    IMG_UINT32              ui32RendecSize;             /*!< Total size of rendec buffers (in bytes).                   */
    IMG_BOOL                bLockStepDecode;            /*!< Indicates that the front-end should not start decoding
                                                             the next picture until the current one is complete
                                                             on the BE.                                                 */
    IMG_BOOL                bSecureMemoryAvailable;     /*!< Indicates that Secure Memory can be allocated on the device*/
    IMG_BOOL                bPerformanceLog;            /*!< Indicates that a performance log should be generated.      */
    IMG_BOOL                bOptimisedPerformance;      /*!< Indicates that performance should be optimised.            */
    IMG_UINT32              ui32MemoryStallingMin;      /*!< Minimum memory stalling latency.                           */
    IMG_UINT32              ui32MemoryStallingMax;      /*!< Maximum memory stalling latency.                           */
    IMG_UINT32              ui32MemoryStallingRatio;    /*!< Integer from 0 to 10 to represent the percentage of
                                                             transactions to stall in 10% steps.                        */

    IMG_UINT32              ui32DwrPeriod;              /*!< Device watch timeout period (in ms). This timer runs on
                                                             the host and periodically monitors activity on the device. */
    IMG_UINT32              ui32DwrJPEGRetry;           /*!< Retry count of device watch timer (JPEG only).             */
    IMG_UINT32              ui32FeWdtPeriod;            /*!< Front-end hardware watchdog timeout period (clocks?)       */
    IMG_UINT32              ui32BeWdtPeriod;            /*!< Back-end hardware watchdog timeout period (clocks?)        */
    IMG_UINT32              ui32PSRWdtPeriod;           /*!< Parser hardware watchdog timeout period (mtx clocks)       */

    IMG_BOOL                bCoreDump;                  /*!< Indicates whether the core state should be logged when
                                                             lock-up is detected.                                       */

    IMG_BOOL                bPost;                      /*!< Indicates whether we need to do POST.                      */
    IMG_BOOL                bStackUsageTest;            /*!< Indicates whether we need to do Stack Usage Test.          */

    IMG_BOOL                bSingleStreamFw;            /*!< Indicates whether single-stream firmware should be used.
                                                             Base and parser components are loaded together.            */
    VDEC_eVidStd            eSingleStreamStd;           /*!< Video standard of single-stream firmware.                  */
    IMG_BOOL                bOoldFw;                    /*!< Indicates whether out-of-loop firmware should be used.     */

    // This will not be overriden by DBGOPT.
    VDEC_eTileScheme        eTileScheme;                /*!< Tile scheme used for image buffers.                        */

    IMG_BOOL                bCSim;                      /*!< Indicates whether platform is CSIM.                        */
    IMG_BOOL                bPdumpAndRes;               /*!< Indicates that pdumping is enabled and image buffer
                                                             data should be captured.                                   */

} VDECDD_sDdDevConfig;


/*!
******************************************************************************
 This structure contains the device context.
 @brief  VDECDD Device Context
 ******************************************************************************/
typedef struct
{
    IMG_HANDLE              hDevHandle;         /*!< Device handle.                                         */

    LST_T                   sConnList;          /*!< List of connections.                                   */
    LST_T                   sCoreMsgList;       /*!< List of pending core messages.                         */

    IMG_HANDLE              hSchedulerContext;  /*!< Scheduler context.                                     */
    IMG_HANDLE              hDecoderContext;    /*!< Decoder context.                                       */

    VDECDD_eDecodeLevel     eDecodeLevel;       /*!< Indicates how far down stack the decoding takes place. */

    LST_T                   sHwMsgList;         /*!< List of core messages pre-allocated for alerting the
                                                     core_api queue to a picture done interrupt. These avoid
                                                     asynchronous messages allocating memory in interrupt
                                                     context which is not permissible in the KM.            */

    SYS_eMemPool            eSecurePool;        /*!< Secure memory pool                                     */
    SYS_eMemPool            eInsecurePool;      /*!< Insecure memory pool                                   */

} VDECDD_sDdDevContext;


/*!
******************************************************************************
 This structure contains the device connection context.
 @brief  VDECDD Connection Context
 ******************************************************************************/
typedef struct
{
    LST_LINK;               /*!< List link (allows the structure to be part of a MeOS list).    */

    VDECDD_sDdDevContext *  psDdDevContext;     /*!< Device context.                            */

    LST_T                   sStreamList;        /*!< List of streams.                           */
    IMG_HANDLE              hResBHandle;        /*!< Resource bucket.                           */

    IMG_UINT32              ui32ConnId;         /*!< Connection Id.                             */

} VDECDD_sDdConnContext;

typedef enum {
    RESET_MMUPF,
    RESET_DWR,
} VDECDD_eResetReason;

/*!
******************************************************************************
 This type defines the stream state.
 @brief  VDEDD Stream State
******************************************************************************/
typedef enum
{
    VDECDD_STRSTATE_STOPPED = 0x00,  /*!< Stream stopped.     */
    VDECDD_STRSTATE_PLAYING,         /*!< Stream playing.     */
    VDECDD_STRSTATE_STOPPING,        /*!< Stream stopping.    */

    VDECDD_STRSTATE_MAX,             /*!< Max. stream state.  */

} VDECDD_eDdStrState;


/*!
******************************************************************************
 This structure contains the mapped output buffer configuration.
 @brief  VDECDD Mapped Output Buffer Configuration
 ******************************************************************************/
typedef struct
{
    IMG_UINT32          ui32BufSize;            /*!< Size (in bytes) of mapped output buffer.       */
    IMG_UINT32          ui32NumBufs;            /*!< Number of buffers mapped into the device.      */

    VDEC_eTileScheme    eTileScheme;            /*!< Tiling scheme declared for the mapped buffers. */
    IMG_BOOL            bByteInterleave;        /*!< Indicates whether byte interleaving is
                                                     to be used (only for tiled buffers).           */

} VDECDD_sMapBufInfo;


/*!
******************************************************************************
 This structure contains the information about the picture buffer
 and its structure.
 @brief  VDECDD Picture Buffer Info
 ******************************************************************************/
typedef struct
{
    VDECDD_sDdBufMapInfo *  psPictBuf;          /*!< Picture buffer information.                */
    VDEC_sPictRendInfo      sRendInfo;          /*!< Picture buffer structure information.      */
    VDEC_sPictBufConfig     sBufConfig;         /*!< Picture buffer configuration.              */

} VDECDD_sDdPictBuf;


/*!
******************************************************************************
 This structure contains the information required to check for Decoder support.
 Only pointers that are non-null will be used in validation.
 @brief  VDECDD Support Check Information
 ******************************************************************************/
typedef struct
{
    // Inputs
    const VDEC_sComSequHdrInfo  * psComSequHdrInfo;     /*!< Pointer to common sequence header information.         */
    const VDEC_sStrOutputConfig * psOutputConfig;       /*!< Pointer to output configuration information.           */
    const VDECDD_sDdPictBuf     * psDispPictBuf;        /*!< Pointer to display picture buffer information.         */
    const BSPP_sPictHdrInfo     * psPictHdrInfo;        /*!< Pointer to picture header information.                 */

    // Outputs
    IMG_UINT32                    ui32StopFlags;        /*!< Stop flags set as a result of the support check.       */
    VDEC_sUnSupportedFlags        sUnSupportedFlags;    /*!< Flags to indicate unsupported features/state.          */
    IMG_UINT32                    ui32Features;         /*!< Stream features of any current unsuccessful picture
                                                             to schedule as defined by #VDECDD_eCoreFeatureFlags.   */

} VDECDD_sSuppCheck;


/*!
******************************************************************************
 This structure contains the information required to check Decoder load.
 @brief  VDECDD Load Check Information
 ******************************************************************************/
typedef struct
{
    // Inputs
    IMG_UINT32 ui32Features;        /*!< Features of the picture that is next to be scheduled.      */

    // Outputs
    IMG_UINT32 ui32AvailLoad;       /*!< Load value of least loaded core able to decode picture
                                         *with slots available for decoding*.                       */
    IMG_UINT32 ui32MinLoad;         /*!< Load value of least loaded core able to decode picture.    */

} VDECDD_sLoadCheck;


/*!
******************************************************************************
 This structure contains the stream context.
 @brief  VDECDD Stream Context
 ******************************************************************************/
typedef struct
{
    LST_LINK;                  /*!< List link (allows the structure to be part of a MeOS list).                  */

    IMG_UINT32                 ui32StrId;                  /*!< Stream ID.                                       */

    IMG_HANDLE                 hResBHandle;                /*!< Resource bucket handle for this stream.          */
    IMG_HANDLE                 hResHandle;                 /*!< Resource handle for this stream.                 */
    VDECDD_sDdConnContext *    psDdConnContext;            /*!< Connection context.                              */
    VDEC_sStrConfigData        sStrConfigData;             /*!< Stream configuration data.                       */
    IMG_VOID *                 pvStrCbParam;               /*!< Callback client define stream data.              */

    IMG_HANDLE                 hEventHandle;               /*!< Handle for sync object for callbacks wait        */
    LST_T                      sEventCbList;               /*!< List of event callback.                          */
    IMG_BOOL                   bPreempt;                   /*!< IMG_TRUE to preempt and cancel callback wait.    */

    VDECDD_eDdStrState         eDdStrState;                /*!< Stream state.                                    */
    IMG_HANDLE                 hDestroyedEvent;            /*!< Handle to destroyed event object (only valid when
                                                                destroying.                                      */

    IMG_HANDLE                 hMmuStrHandle;              /*!< MMU stream handle.                               */

    IMG_HANDLE                 hPlantContext;              /*!< Plant stream context handle.                     */
    IMG_HANDLE                 hSchedulerContext;          /*!< Scheduler stream context handle.                 */
    IMG_HANDLE                 hDecoderContext;            /*!< Decoder stream context handle .                  */

    VDEC_ePlayMode             ePlayMode;                  /*!< Play mode.                                       */
    VDEC_eStopPoint            eStopPoint;                 /*!< Stop point.                                      */
    IMG_UINT32                 ui32StopPointQual;          /*!< Stop point qualifier.                            */

    VDEC_sStopInfo             sStopInfo;                  /*!< Latest stop info.                                */
    VDEC_sComSequHdrInfo       sComSequHdrInfo;            /*!< Latest VSH.                                      */
    VDECDD_sDdPictBuf          sDispPictBuf;               /*!< Template for display picture buffer. All mapped
                                                                output buffers will have these properties.       */
    VDECDD_sMapBufInfo         sMapBufInfo;                /*!< Information about mapped output buffers.         */
    VDEC_sStrOutputConfig      sOutputConfig;              /*!< Latest output configuration.                     */
    IMG_BOOL                   bStrOutputConfigured;       /*!< Indicates if the output/display configuration
                                                                is set in case it was required by stop flags.    */

    VDEC_sComSequHdrInfo       sPrevComSequHdrInfo;        /*!< Previous VSH (for error handling).               */
    BSPP_sPictHdrInfo          sPrevPictHdrInfo;           /*!< Previous picture header (for error handling).    */
    IMG_HANDLE                 hStatusDgFile;              /*!< Handle to status debug file                      */

} VDECDD_sDdStrContext;


/*!
******************************************************************************
 This structure contains the map info.
 @brief  VDECDD Map Info
 ******************************************************************************/
struct VDECDD_tag_sDdBufMapInfo
{
    LST_LINK;               /*!< List link (allows the structure to be part of a MeOS list).     */

    IMG_HANDLE              hResHandle;        /*!< Resource handle.                             */
    IMG_HANDLE              hExtImportHandle;  /*!< The buffer "external import" handle.         */
    VDECDD_sDdStrContext *  psDdStrContext;    /*!< Pointer to stream context.                   */
    IMG_VOID *              pvBufCbParam;      /*!< A pointer to client specific data.           */
    VDEC_eBufType           eBufType;          /*!< Type of buffer mapped.                       */
    MMU_eHeapId             eMmuHeapId;        /*!< VDECDD MMU Heap in which buffers is mapped.  */
    VXDIO_sDdBufInfo        sDdBufInfo;        /*!< Buffer info for this mapping.                */
};


/*!
******************************************************************************
 This structure contains a set of sequence resources required at all the
 interim stages of decoding it as it flows around the internals. It originates
 in the plant.
 @brief   Sequence Resources (stream)
******************************************************************************/
typedef struct
{
    LST_LINK; /*!< List link (allows the structure to be part of a MeOS list) */

#ifdef HAS_HEVC
    VDECDD_sDdBufMapInfo *pasGencBuffers[4];    /*!< GENC buffers */
    VDECDD_sDdBufMapInfo *psIntraBuffer;    /*!< GENC buffers */
    VDECDD_sDdBufMapInfo *psAuxBuffer;    /*!< GENC buffers */
#endif
#ifdef HAS_VP8
#ifdef VDEC_USE_PVDEC
    VDECDD_sDdBufMapInfo *pasSecondPartitionProb[4];     /*!< Second partition probabilities */
#endif
    VDECDD_sDdBufMapInfo *psMbFlagsBuffer;           /*!< MB flags buffer */
    VDECDD_sDdBufMapInfo *psSegmentIDBuffer;         /*!< Segment ID buffer */
    VDECDD_sDdBufMapInfo *psFirstPartitionBuffer;    /*!< First partition buffer */
    VDECDD_sDdBufMapInfo *psCurrentPictureBuffer;    /*!< Current picture buffer */
#endif
#ifdef HAS_VP6
    VDECDD_sDdBufMapInfo *psPicBuffer;               /*!< Current picture buffer */
#endif
#ifdef HAS_VC1
    VDECDD_sDdBufMapInfo *psMSBBuffer;               /*!< MSB buffer */
    VDECDD_sDdBufMapInfo *pasBitPlaneBuffers[3];     /*!< Bitplane buffers */
#endif


    IMG_UINT32 ui32RefCount;  /*!< Ref. counter (number of users) of sequence resources
                                   NOTE: Internal buffer reference counters are not used
                                   for buffers allocated as sequence resources. */
} VDECDD_sSeqResInt;


/*!
******************************************************************************
 This structure contains a set of picture resources required at all the
 interim stages of decoding it as it flows around the internals. It originates
 in the plant.
 @brief   Picture Resources (stream)
******************************************************************************/
typedef struct
{
    LST_LINK;               /*!< List link (allows the structure to be part of a MeOS list).                       */

    VDECDD_sDdPictBuf *     psDdPictBuf;   /*!< Auxiliary picture buffer. Needed if display buffer is not used
                                                for reference (e.g. rotation).                                     */
    VDECDD_sDdBufMapInfo *  psMBParamBuf;  /*!< MB Parameter buffer.                                               */
#ifdef HAS_MPEG4
    VDECDD_sDdBufMapInfo *  psDP0Buf;      /*!< MPEG4 Data Partition0                                              */
    VDECDD_sDdBufMapInfo *  psDP1Buf;      /*!< MPEG4 Data Partition1                                              */
#endif /* HAS_MPEG4 */
#ifdef HAS_HEVC
    VDECDD_sDdBufMapInfo  * psGencFragmentBuffer; /*!< GENC fragment buffer */
#endif /* HAS_HEVC */
#if defined(HAS_HEVC) || defined(HAS_VC1) || defined(HAS_VP6) || defined(HAS_VP8)
    VDECDD_sSeqResInt     * psSeqResInt;          /*!< Sequence resources (GENC buffers) */
#endif /*  HAS_HEVC || HAS_VC1 || HAS_VP6 || HAS_VP8 */
    IMG_UINT32              ui32RefCount;  /*!< Reference counter (number of users) of these picture resources.
                                                NOTE: Internal buffer reference counters are not used for buffers
                                                      allocated as picture resources.                              */

} VDECDD_sPictResInt;


/*!
******************************************************************************
 This structure contains a set of resources representing a picture
 at all the stages of processing it.
 @brief   Picture
 ******************************************************************************/
typedef struct
{
    IMG_UINT32            ui32PictId;        /*!< Unique and incrementing stream-based picture ID.      */
    IMG_BOOL              bLastPictInSeq;    /*!< Last picture in a sequence.                           */

    VDECDD_sPictResInt *  psPictResInt;      /*!< Internal picture resources.                           */
    VDECDD_sDdPictBuf     sDisplayPictBuf;   /*!< Picture buffer from client used for display.          */

    VDEC_sStrOutputConfig sOutputConfig;     /*!< Stream output configuration to be applied to picture. */

    VDEC_sDecPictInfo *   psDecPictInfo;     /*!< Decoded picture data.                                 */

    VDEC_sDecPictAuxInfo  sDecPictAuxInfo;

} VDECDD_sPicture;

/*!
******************************************************************************

 @Function              VDECDD_pfnCompCallback

 @Description

 This function prototype defines the callback from the internal components.

 @Input    i32Reason      : Specifies the reason for the callback.

 @Input    pvInitUserData : Pointer to component-wide user data (provided at initialisation).

 @Input    pvCoreUserData : Pointer to core user data.

 @Input    pvStrUserData  : Pointer to stream user data.

 @Input    pvData         : Pointer to component data.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
typedef IMG_RESULT
(* VDECDD_pfnCompCallback)(
    IMG_INT32   i32Reason,
    IMG_VOID *  pvInitUserData,
    IMG_VOID *  pvCoreUserData,
    IMG_VOID *  pvStrUserData,
    IMG_VOID *  pvData
);


extern IMG_CHAR * gapszVidStd[];


#ifdef __cplusplus
}
#endif

#endif /* __VDECDD_INT_H__   */
