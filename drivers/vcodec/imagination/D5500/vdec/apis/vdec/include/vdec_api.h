/*!
 *****************************************************************************
 *
 * @File       vdec_api.h
 * @Title      VXD High-Level Decode API (VDEC)
 * @Description    This file contains the structure and function prototypes
 *  for the VXD High-Level Decode API (VDEC).
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

#ifndef __VDEC_API_H__
#define __VDEC_API_H__

#include "img_defs.h"
#include "vdec.h"
#include "system.h"
#include "lst.h"
#include <vxd_config.h>

#include "pixel_api.h"

#include "page_alloc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TEST_ONE_DEVICE_ALLOC_SPS
#define TEST_ONE_DEVICE_ALLOC_PPS

#define VDEC_MAX_PANSCAN_WINDOWS    4          /*!< Maximum Pan Scan Windows.         */

#define VPS_SLOTS           (16)  // Only for HEVC
#define SEQUENCE_SLOTS      (64)  // 32 sequence slots + 32 subsequence slots
#define PPS_SLOTS           (256)
#define MAX_PICS_IN_SYSTEM  (64)        // Arbitrary number, balances the trade-off between resource need and run-ahead of the bspp
                                        // This needs to be increased to around 120 while decoding certains H264 streams from DB (such as 9766)
                                        // on FPGA as these have large number of PPSs. All PPS slots are occupied by valid PPSs and subsequent
                                        // PPS are dropped which results in wrong PPS being passed to firmware

#define MAX_VPSS            (MAX_PICS_IN_SYSTEM + VPS_SLOTS)
#define MAX_SEQUENCES       (MAX_PICS_IN_SYSTEM + SEQUENCE_SLOTS)
#define MAX_PPSS            (MAX_PICS_IN_SYSTEM + PPS_SLOTS)


/*!
******************************************************************************
 This type defines the set of available device features.
 @brief  Device Features
******************************************************************************/
typedef enum
{
    VDEC_FEATURE_MPEG2,             /*!< MPEG2 (includes MPEG1).                         */
    VDEC_FEATURE_MPEG4,             /*!< MPEG4 (includes H263 and Sorenson Spark).       */
    VDEC_FEATURE_H264,              /*!< H264.                                           */
    VDEC_FEATURE_VC1,               /*!< VC1 (includes WMV9).                            */
    VDEC_FEATURE_AVS,               /*!< AVS.                                            */
    VDEC_FEATURE_REAL,              /*!< RealVideo (RV30 and RV40).                      */
    VDEC_FEATURE_JPEG,              /*!< JPEG.                                           */
    VDEC_FEATURE_VP6,               /*!< On2 VP6.                                        */
    VDEC_FEATURE_VP8,               /*!< On2 VP8.                                        */
    VDEC_FEATURE_HEVC,              /*!< HEVC.                                           */

    VDEC_FEATURE_HD_DECODE,         /*!< Supports HD decode.                             */
    VDEC_FEATURE_ROTATION,          /*!< Supports Rotation.                              */
    VDEC_FEATURE_SCALING,           /*!< Supports scaling.                               */
    VDEC_FEATURE_SCALING_WITH_OOLD, /*!< Supports scaling with out-of-loop de-blocking.  */

    VDEC_FEATURE_EXTENDED_STRIDES,  /*!< Supports extended strides.                      */

    VDEC_FEATURE_MAX                /*!< Max feature ID.                                 */

} VDEC_eFeature;

typedef struct
{
    IMG_BOOL bValid;
    IMG_BOOL bFeatureMPEG2;
    IMG_BOOL bFeatureMPEG4;
    IMG_BOOL bFeatureH264;
    IMG_BOOL bFeatureVC1;
    IMG_BOOL bFeatureAVS;
    IMG_BOOL bFeatureREAL;
    IMG_BOOL bFeatureJPEG;
    IMG_BOOL bFeatureVP6;
    IMG_BOOL bFeatureVP8;
    IMG_BOOL bFeatureHEVC;
    IMG_BOOL bFeatureHD;
    IMG_BOOL bFeatureRotation;
    IMG_BOOL bFeatureScaling;
    IMG_BOOL bFeatureScalingWithOOLD;
    IMG_BOOL bFeatureScalingExtendedStrides;
} VDEC_sFeatures;

/*!
******************************************************************************
 This type defines the VDEC events.
 @brief  VDEC Callback Events
******************************************************************************/
typedef enum
{
    VDEC_EVENT_STREAM_STOPPED,          /*!< The stream has stopped decoding in response to reaching a
                                             stop point (#VDEC_eStopPoint), a fence (VDEC_StreamInsertFence()),
                                             or when client intervention is required. Refer to #VDEC_eStopFlags
                                             to find out more about stream stop status.

                                             NOTE: pvParam parameter contains the tag if fence triggered (#VDEC_STOPSTATUS_FENCE).  */

    VDEC_EVENT_BSTRBUF_EMPTY,           /*!< Used to pass/return a bit stream buffers when they are empty.

                                             NOTE: pvBufCbParam is valid for this event.

                                             NOTE: pvParam parameter contains the address of a #VDEC_sBufInfo
                                             Information must be copied from this structure before returning from the
                                             callback function.                                                                     */

    VDEC_EVENT_PICTBUF_FULL,            /*!< A picture has been decoded.

                                             NOTE: pvBufCbParam is valid for this event.

                                             NOTE: pvParam parameter contains the address of #VDEC_sDecPictInfo.
                                             Information must be copied from this structure before returning from the
                                             callback function.                                                                     */

    VDEC_EVENT_STREAM_FLUSHED,          /*!< The stream has been flushed of all display pictures in response to
                                             asynchronous function VDEC_StreamFlushOutput.                                          */

    VDEC_EVENT_MAX,                     /*!< Max. events.                                                                           */

} VDEC_eEvent;


/*!
******************************************************************************
 This type defines the video standard.
 @brief  VDEC Video Standards
******************************************************************************/
typedef enum
{
    VDEC_STD_UNDEFINED = 0,   /*!< Video standard not defined.                */
    VDEC_STD_MPEG2,           /*!< MPEG2 (includes MPEG1).                    */
    VDEC_STD_MPEG4,           /*!< MPEG4.                                     */
    VDEC_STD_H263,            /*!< H263.                                      */
    VDEC_STD_H264,            /*!< H264.                                      */
    VDEC_STD_VC1,             /*!< VC1 (includes WMV9).                       */
    VDEC_STD_AVS,             /*!< AVS.                                       */
    VDEC_STD_REAL,            /*!< RealVideo (RV30 and RV40).                 */
    VDEC_STD_JPEG,            /*!< JPEG.                                      */
    VDEC_STD_VP6,             /*!< On2 VP6.                                   */
    VDEC_STD_VP8,             /*!< On2 VP8.                                   */
    VDEC_STD_SORENSON,        /*!< Sorenson Spark.                            */
    VDEC_STD_HEVC,            /*!< HEVC.                                      */

    VDEC_STD_MAX,             /*!< Max. video standard.                       */

} VDEC_eVidStd;


/*!
******************************************************************************
 This type defines the bitstream format. Should be done at the start of decoding.
 @brief  VDEC Bitstream Format
******************************************************************************/
typedef enum
{
    VDEC_BSTRFORMAT_UNDEFINED = 0,              /*!< Bitstream format not defined.                                                              */
    VDEC_BSTRFORMAT_ELEMENTARY,                 /*!< Elementary stream (also use for ES-level extracted from simple encapsulation i.e. MPG).    */
                                                /*!< Default when no parsing done in the app, like test apps.                                   */
    VDEC_BSTRFORMAT_DEMUX_BYTESTREAM,           /*!< Data appears in logical units, like frame boundary and data is expected to be with SCP.    */
                                                /*!< Streamer Header/Configuration info could be out-of-band and\or inband.                     */
                                                /*!< Default when parsing is done by the app, like gStreamer or Stagefrieght Demuxers.          */
    VDEC_BSTRFORMAT_DEMUX_SIZEDELIMITED,        /*!< Data appears in logical units, like frame boundary or NAL units and No SCP is expected.    */
                                                /*!< Streamer Header/Configuration info is out-of-band.                                         */
                                                /*!< Used when parsing is done by the app, like gStreamer Demuxers.                             */
    VDEC_BSTRFORMAT_MAX,                        /*!< Max. bitstream format.                                                                     */

} VDEC_eBstrFormat;


/*!
******************************************************************************
 This type defines the Type of payload. Could change with every buffer.
 @brief  VDEC Bitstream Element Type
******************************************************************************/
typedef enum
{
    VDEC_BSTRELEMENT_UNDEFINED = 0,                 /*!< Bitstream element undefined.                                               */
    VDEC_BSTRELEMENT_UNSPECIFIED,                   /*!< Do not know the content of the buffer. Most probably start-code delimited.     */
    VDEC_BSTRELEMENT_CODEC_CONFIG,                  /*!< Buffer contains Stream Header/Codec Config.   */
    VDEC_BSTRELEMENT_PICTURE_DATA,                  /*!< Encoded data (size delimited).                                             */
    VDEC_BSTRELEMENT_MAX,                           /*!< Max. bitstream element.                                                    */

} VDEC_eBstrElementType;


#define BSPP_ERROR_MASK ((VDEC_ERROR_BSPP_DATA_REMAINS - 1) ^ ((VDEC_ERROR_BSPP_UNRECOVERABLE << 1) - 1))   /*!< BSPP Error Mask        */
#define PSR_ERROR_MASK  ((VDEC_ERROR_PSR_TIMEOUT - 1) ^ ((VDEC_ERROR_PSR_PROCESS_NOT_NORMAL << 1) - 1))     /*!< Parser Error Mask      */
#define FEHW_ERROR_MASK ((VDEC_ERROR_FEHW_TIMEOUT - 1) ^ ((VDEC_ERROR_FEHW_DECODE << 1) - 1))               /*!< Front End Error Mask   */
#define BEHW_ERROR_MASK (VDEC_ERROR_BEHW_TIMEOUT - 1)                                                       /*!< Back End Error Mask    */
#define DWR_ERROR_MASK  VDEC_ERROR_SERVICE_TIMER_EXPIRY
#define MISSING_REFERENCES_ERROR_MASK  (VDEC_ERROR_MISSING_REFERENCES)

/*!
******************************************************************************
 This type defines the error , error in parsing, error in decoding etc.
 @brief  VDEC parsing/decoding error  Information
******************************************************************************/
typedef enum
{
    VDEC_ERROR_NONE                                 = (0     ),    /*!< No error encountered.                                          */
    VDEC_ERROR_BSPP                                 = (1 << 0),    /*!< Error encounter in BSPP component ,                            */

    VDEC_ERROR_PSR_TIMEOUT                          = (1 << 1),    /*!< Firmware header parsing timeout                                */
    VDEC_ERROR_PSR_SR_ERROR                         = (1 << 2),    /*!< Firnware header parsing sr error,                              */
    VDEC_ERROR_PSR_PROCESS_NOT_NORMAL               = (1 << 3),    /*!< Firmware parser not followed all the required steps            */

    VDEC_ERROR_SR_ERROR                             = (1 << 4),    /*!< Hardware Shift Register error                                  */
    // Mask group: #FEHW_ERROR_MASK
    VDEC_ERROR_FEHW_TIMEOUT                         = (1 << 5),    /*!< Front-end hardware decoding timeout                            */
    VDEC_ERROR_FEHW_DECODE                          = (1 << 6),    /*!< Front-end hardware decoding error                              */

    VDEC_ERROR_BEHW_TIMEOUT                         = (1 << 7),    /*!< Back-end hardware decoding timeout                             */

    VDEC_ERROR_SERVICE_TIMER_EXPIRY                 = (1 << 8),    /*!< MSVDX Service Time Expiry                                      */

    VDEC_ERROR_MISSING_REFERENCES                   = (1 << 9),    /*!< Picture may have corruption because of missing references      */

    VDEC_ERROR_MAX                                  = (1 << 10),

} VDEC_eErrorType;

/*!
******************************************************************************
 This type defines the warning , warning in parsing, warning in decoding etc.
 @brief  VDEC parsing/decoding warning  Information
******************************************************************************/
typedef enum
{
    VDEC_WARNING_NONE                                   = (0     ),     /*!< No warning encountered.                                                */
    VDEC_WARNING_BSPP_AUX_DATA                          = (1 << 0),     /*!< Error in Auxiliary data Parsing,treated as warning in driver level     */
    VDEC_WARNING_BSPP_DATA_REMAINS                      = (1 << 1),     /*!< Error in parsing, more data remains after parsing                      */
    VDEC_WARNING_BSPP_INVALID_VALUE                     = (1 << 2),     /*!< Error in parsing, parsed codeword is invalid                           */
    VDEC_WARNING_BSPP_DECODE                            = (1 << 3),     /*!< Error in parsing, parsing error                                        */
    VDEC_WARNING_BSPP_NO_REF_FRAME                      = (1 << 4),     /*!< Error in parsing, no reference frrame is available for decoding        */
    VDEC_WARNING_BSPP_IDR_FRAME_LOSS                    = (1 << 5),     /*!< Error in parsing, IDR frame loss detected                              */
    VDEC_WARNING_BSPP_NONIDR_FRAME_LOSS                 = (1 << 6),     /*!< Error in parsing, non IDR frame loss detected                          */
    VDEC_WARNING_MAX                                    = (1 << 7),

} VDEC_eWarningType;

/*!
******************************************************************************
 This type defines the correction , correction in parsing, warning in decoding etc.
 @brief  VDEC parsing/decoding correction  Information
******************************************************************************/
typedef enum
{
    VDEC_CORRECTION_NONE                                = (0     ),     /*!< No Correction applied .                                          */
    VDEC_CORRECTION_BSPP_VSHREPLACED                    = (1 << 0),     /*!< Applied correction in VSH data by replacing the currpted with previous VSH */
    VDEC_CORRECTION_BSPP_VALIDVALUE                     = (1 << 1),     /*!< Clampped the parsed invalid value in BSPP                              */
    VDEC_CORRECTION_BSPP_CONCEALEDDATA                  = (1 << 2),     /*!< concealed the currpted data unit with previous parsed data unit        */

    VDEC_CORRECTION_MAX                                 = (1 << 3),

} VDEC_eCorrectionType;
/*!
******************************************************************************
 This type defines how VDEC behaves when encountering an error during processing.
 @brief  VDEC Error Handling
******************************************************************************/
typedef enum
{
    VDEC_ERROR_HANDLING_IGNORE_ALL       = (0   ),  /*!< Ignore all errors and try to proceed anyway.  */
    VDEC_ERROR_HANDLING_STOP_ON_SEQUENCE = (1<<0),  /*!< Stop on VSH errors.
                                                         NOTE: The #VDEC_STOPSTATUS_BITSTREAM_ERROR stop flag will be set
                                                         in the #VDEC_sStopInfo and VSH error flags will be indicated
                                                         in the #VDEC_sBitstreamErrorInfo.ui32SequenceError.               */
    VDEC_ERROR_HANDLING_STOP_ON_PICTURE  = (1<<1),  /*!< Stop on picture errors.
                                                         NOTE: The #VDEC_STOPSTATUS_BITSTREAM_ERROR stop flag will be set
                                                         in the #VDEC_sStopInfo and picture error flags will be indicated
                                                         in the #VDEC_sBitstreamErrorInfo.ui32PictureError.                */
    VDEC_ERROR_HANDLING_STOP_ON_ALL      = (1<<2),  /*!< Stop on all errors.
                                                         NOTE: The #VDEC_STOPSTATUS_BITSTREAM_ERROR stop flag will be set
                                                         in the #VDEC_sStopInfo and error flags will be indicated
                                                         in the #VDEC_sBitstreamErrorInfo.                                 */

} VDEC_eErrorHandling;


/*!
******************************************************************************
 This enumeration defines the colour plane indices.
 @brief  Colour Plane Indices
*****************************************************************************/
typedef enum
{
    VDEC_PLANE_VIDEO_Y   = 0,   //!< Luma base address for the picture, Y
    VDEC_PLANE_VIDEO_YUV = 0,   //!< Luma base address for the picture, Y,Cr,Cb
    VDEC_PLANE_VIDEO_U   = 1,   //!< Chroma1 base address, Cr, or invalid
    VDEC_PLANE_VIDEO_UV  = 1,   //!< Chroma1 base address, Cr,Cb, or invalid
    VDEC_PLANE_VIDEO_V   = 2,   //!< Chroma2 base address, Cb or invalid
    VDEC_PLANE_VIDEO_A   = 3,   //!< Alpha base address

    VDEC_PLANE_LIGHT_R   = 0,
    VDEC_PLANE_LIGHT_G   = 1,
    VDEC_PLANE_LIGHT_B   = 2,

    VDEC_PLANE_INK_C     = 0,
    VDEC_PLANE_INK_M     = 1,
    VDEC_PLANE_INK_Y     = 2,
    VDEC_PLANE_INK_K     = 3,

    VDEC_PLANE_MAX       = 4,

} VDEC_eColourPlanes;


/*!
******************************************************************************
 This type defines the "play" mode.
 @brief  Play Mode
******************************************************************************/
typedef enum
{
    VDEC_PLAYMODE_PARSE_ONLY,           /*!< Parse bitstream ONLY, discard bit stream data.  */
    VDEC_PLAYMODE_NORMAL_DECODE,        /*!< Normal parse and decode.                         */

    VDEC_PLAYMODE_MAX,                  /*!< Max. play mode.                                  */

} VDEC_ePlayMode;


/*!
******************************************************************************
 This type defines the stop point.
 @brief  Stop Point
******************************************************************************/
typedef enum
{
    VDEC_STOPPOINT_UNDEFINED,               /*!< No stop point defined. Driver will only stop when client intervention is 
                                                 required (see #VDEC_eStopFlags for reasons).                                   */
    VDEC_STOPPOINT_NOW,                     /*!< Stop now (immediately). Driver will stop as quickly as possible. Any Stream 
                                                 Units that have been submitted to the Decoder will be allowed to complete. 
                                                 This may take a couple of frame periods.                                       */
    VDEC_STOPPOINT_SEQUENCE_START,          /*!< Stop at next change of sequence, where the header is new or different from the 
                                                 last.                                                                          */
    VDEC_STOPPOINT_CLOSED_GOP,              /*!< Stop at next closed GOP (inc. start of sequence). Closed GOP which marks the 
                                                 point where subsequent pictures dont refer to any earlier in the bitstream. 
                                                 This will be coincident with any change of sequence encountered.               */
    VDEC_STOPPOINT_NEW_DISPLAY_RESOLUTION,  /*!< Stop at a change of display resolution (always start of sequence & closed GOP).*/
    VDEC_STOPPOINT_SEQUENCE_END,            /*!< Stop at end of sequence (if signalled in bitstream).                           */
    VDEC_STOPPOINT_PICTURE_END,             /*!< Stop at end of every picture.                                                  */

    VDEC_STOPPOINT_MAX,                     /*!< Max. stop point.                                                               */

} VDEC_eStopPoint;


/*!
******************************************************************************
 This type defines the stopped status flags. Stop flags are obtained through
 VDEC_StreamGetStopFlags().
 @brief  Stopped Status Flags
******************************************************************************/
typedef enum
{
    VDEC_STOPSTATUS_SEQUENCE_START          = (1<<0),  /*!< Start of a new sequence of pictures whose properties match those defined in current sequence
                                                            header obtained through VDEC_StreamGetSequHdrInfo(). This information is required to determine
                                                            the correct picture buffer size and layout which *must* be altered when stop flags
                                                            #VDEC_STOPSTATUS_PICTBUF_SIZE_INVALID or VDEC_STOPSTATUS_PICTBUF_CONFIG_INVALID respectively are
                                                            signalled.                                                                                          */

    VDEC_STOPSTATUS_CLOSED_GOP              = (1<<1),  /*!< Closed GOP encountered where subsequent pictures don't refer to previous reference images
                                                            (which were automatically discarded). Normal glitch-free playback (#VDEC_PLAYMODE_NORMAL_DECODE)
                                                            can be resumed from this point <i>if</i> valid sequence header present.
                                                            In some standards where closed GOP signalling is done via optional/not always preset header elements
                                                            I frames will be used as closed GOP signalling points. This insures resilient operation.           */

    VDEC_STOPSTATUS_SEQUENCE_END            = (1<<2),  /*!< All pictures from the current sequence have been decoded, displayed and references released.
                                                            Sequence start with closed GOP must follow for normal glitch-free playback
                                                            (#VDEC_PLAYMODE_NORMAL_DECODE).                                                                     */

    VDEC_STOPSTATUS_PICTURE_END             = (1<<3),  /*!< Picture has been decoded.                                                                           */






    VDEC_STOPSTATUS_RECONFIGURE             = (1<<4),  /*!< Reconfiguration of output (picture buffers and/or transformations) is required due to
                                                            incompatibility with stream properties. If this coincides with a closed GOP the stream will have
                                                            automatically been flushed; all display pictures returned and all references released.
                                                            To determine whether output configuration or picture buffers need to be modified service the
                                                            following flags:
                                                                a. #VDEC_STOPSTATUS_OUTPUT_CONFIG_INVALID,
                                                                b. #VDEC_STOPSTATUS_PICTBUF_CONFIG_INVALID,
                                                                c. #VDEC_STOPSTATUS_PICTBUF_SIZE_INVALID                                                        */

    VDEC_STOPSTATUS_OUTPUT_CONFIG_INVALID   = (1<<5),   /*!< Output configuration is not compatible with the stream state. Resubmit a valid configuration
                                                             using VDEC_StreamSetOutputConfig() whilst paying careful attention the current sequence
                                                             properties obtained through VDEC_StreamGetSequHdrInfo().                                           */

    VDEC_STOPSTATUS_PICTBUF_CONFIG_INVALID  = (1<<6),   /*!< Picture buffers are not configured properly for normal playback with the current sequence and output
                                                             configuration. If #VDEC_STOPSTATUS_PICTBUF_SIZE_INVALID is also signalled the buffers must be
                                                             re-allocated and mapped using steps described with that flag. Otherwise just reconfigure the picture
                                                             buffers using the following steps:
                                                                1. Obtain latest sequence header information with VDEC_StreamGetSequHdrInfo(),
                                                                2. Determine the correct size of picture buffers currently required (#VDEC_PictBufGetConfig()),
                                                                3. Provide new picture buffer configuration (along with desired output configuration) via
                                                                   VDEC_StreamSetOutputConfig().
                                                                4. Resume playback (#VDEC_StreamPlay()).                                                        */

    VDEC_STOPSTATUS_PICTBUF_SIZE_INVALID    = (1<<7),   /*!< Mapped picture buffers are not large enough to decode the current sequence and output
                                                             configuration. Suggested steps are:
                                                                1. Flush any output buffers using VDEC_StreamFlushOutput() to ensure that all decoded buffers
                                                                   have been displayed. If not at a closed GOP these pictures may not be in the correct sequence
                                                                   and future pictures also not have the correct references. If the client has another mechanism
                                                                   for handling out-of-order pictures with rotation/scaling applied (i.e. correct the
                                                                   rotation/scaling of "old" pictures to match the new display) buffer remapping can be avoided
                                                                   by allocating buffers to support rotation VDEC_PictBufGetConfig(bAllocRotation).
                                                                2. Release old output buffers with #VDEC_StreamReleaseBufs(eBufType = #VDEC_BUFTYPE_PICTURE),
                                                                3. Unmap (#VDEC_StreamUnmapBuf()) old picture buffers (and free with #VDECEXT_BufFree() if internal),
                                                                4. Determine the correct size of picture buffers currently required (#VDEC_PictBufGetConfig()),
                                                                5. Allocate (#VDECEXT_BufMalloc()) and map (#VDEC_StreamMapBuf()) new buffers,
                                                                6. Resume playback (#VDEC_StreamPlay()).                                                        */

    VDEC_STOPSTATUS_PICTBUF_NUM_MAPPED_INVALID = (1<<8),/*!< Sequence requires more image buffers than have been mapped. This will only be signalled if
                                                             stopping for one of the other reasons                                                              */
    VDEC_STOPSTATUS_MIN_NUM_PICTBUFS_INCREASED  = (1<<9),

    VDEC_STOPSTATUS_DISPLAY_RESOLUTION_CHANGED = (1<<10),/*!< Frame display resolution has changed.                                                              */

    VDEC_STOPSTATUS_NO_REFERENCE_IMAGES     = (1<<11),  /*!< No reference images are held (e.g. after signal of
                                                                 a. #VDEC_STOPSTATUS_CLOSED_GOP,
                                                                 b. #VDEC_STOPSTATUS_SEQUENCE_END or
                                                                 c. #VDEC_StreamFlushOutput(bDiscardRefs = IMG_TRUE)
                                                                 d. #VDEC_StreamReleaseBufs(eBufType = VDEC_BUFTYPE_PICTURE)).
                                                             This status is persistent until the next request to play. Immediate playback is permitted but
                                                             may result in image corruption (non-intra pictures) if not at a closed GOP. Suggested steps are:
                                                                 1. Resume playback in parse-only mode until a closed GOP is located:
                                                                            \n#VDEC_StreamPlay(ePlayMode = #VDEC_PLAYMODE_PARSE_ONLY,
                                                                                               eStopPoint = #VDEC_STOPPOINT_CLOSED_GOP),
                                                                 2. Repeat 1. until stopped and flags indicate #VDEC_STOPSTATUS_CLOSED_GOP,
                                                                 3. Resume normal playback: #VDEC_StreamPlay(ePlayMode = #VDEC_PLAYMODE_NORMAL_DECODE)          */
    VDEC_STOPSTATUS_FENCE                   = (1<<12),  /*!< Stopped at fence.                                                                                  */
    VDEC_STOPSTATUS_BITSTREAM_ERROR         = (1<<13),  /*!< Error was encountered while parsing the bitstream. More specific info can be found in the log.     */
    VDEC_STOPSTATUS_UNSUPPORTED             = (1<<14),  /*!< Bitstream has unsupported feature(s)                                                               */
    VDEC_STOPSTATUS_SEMANTICS_ERROR         = (1<<15),  /*!< Stream units (or data carried by these) are incorrect and cannot be recovered.                     */

} VDEC_eStopFlags;


/*!
******************************************************************************
 This type defines the buffer type categories.
 @brief  Buffer Types
******************************************************************************/
typedef enum
{
    VDEC_BUFTYPE_BITSTREAM,         /*!< Bitstream buffer.                      */
    VDEC_BUFTYPE_PICTURE,           /*!< Picture buffer.                        */
    VDEC_BUFTYPE_ALL,               /*!< Both bitstream and picture buffers.    */

    VDEC_BUFTYPE_MAX,               /*!< Max. buffer type.                      */

} VDEC_eBufType;


/*!
******************************************************************************
 This type defines the decoded picture state.
 @brief  Decoded Picture State
******************************************************************************/
typedef enum
{
    VDEC_PICT_STATE_NOT_DECODED,        /*!< Not decoded.                             */
    VDEC_PICT_STATE_DECODED,            /*!< Picture decoded.                         */
    VDEC_PICT_STATE_TERMINATED,         /*!< Picture decode terminated due to error.  */

    VDEC_PICT_STATE_MAX                 /*!< Max state.                               */

} VDEC_ePictState;


/*!
******************************************************************************
 This type defines the rotation modes.
 @brief  Rotation Modes
******************************************************************************/
typedef enum
{
    VDEC_ROTATE_0 = 0,                  /*!< Output is generated in the default orientation.  */
    VDEC_ROTATE_90,                     /*!< Output is generated rotated 90 degrees.          */
    VDEC_ROTATE_180,                    /*!< Output is generated rotated 180 degrees.         */
    VDEC_ROTATE_270,                    /*!< Output is generated rotated 270 degrees.         */

    VDEC_ROTATE_MAX                     /*!< Max. rotation mode.                              */

} VDEC_eRotMode;


/*!
******************************************************************************
 This enumeration defines the VDEC tiling schemes.
 @brief  Tiling Schemes
******************************************************************************/
typedef enum
{
    VDEC_TS_NONE = 0,
    VDEC_TS0_256x16,
    VDEC_TS1_512x8,

    VDEC_TS_MAX,

} VDEC_eTileScheme;


/*!
******************************************************************************
 This type defines the type for a buffer to be imported
 @brief  Imported buffer type
******************************************************************************/
typedef enum
{
    VDEC_IMPORTBUFTYPE_USERALLOC,       /*!< Allocated in user mode */
    VDEC_IMPORTBUFTYPE_ANDROIDNATIVE,   /*!< Android native buffer  */

} VDEC_eImportBufType;




/*!
******************************************************************************
 This structure contains the VDEC API version and build information.
 @brief  VDEC Version Information
******************************************************************************/
typedef struct
{
    IMG_UINT32  ui32Major;              /*!< The major part of the version number.     */
    IMG_UINT32  ui32Minor;              /*!< The minor part of the version number.     */
    IMG_UINT32  ui32Revision;           /*!< The revision part of the version number.  */
    IMG_UINT32  ui32Build;              /*!< The build number.                         */

} VDEC_sVersion;


/*!
******************************************************************************
 This structure describes the VDEC picture dimensions.
 @brief  VDEC Picture Size
******************************************************************************/
typedef struct
{
    IMG_UINT32  ui32Width;   /*!< The picture width (in pixels).  */
    IMG_UINT32  ui32Height;  /*!< The picture height (in lines).  */

} VDEC_sPictSize;


/*!
******************************************************************************
 This structure describes the VDEC Display Rectangle.
 @brief  VDEC Display Rectangle
******************************************************************************/
typedef struct
{
    IMG_UINT32      ui32TopOffset;              /*!< Offset (in lines) from origin (0,0) to top of rectangle.   */
    IMG_UINT32      ui32LeftOffset;             /*!< Offset (in pixels) from origin (0,0) to left of rectangle. */
    IMG_UINT32      ui32Width;                  /*!< Width (in pixels) of rectangle.                            */
    IMG_UINT32      ui32Height;                 /*!< Height (in lines) of rectangle.                            */

} VDEC_sRect;


/*!
******************************************************************************
 This structure describes the VDEC Pan Scan Window.
 @brief  VDEC Pan Scan Window
******************************************************************************/
typedef struct
{
    IMG_UINT32      ui32TopOffset;              /*!< Offset (in 1/16th lines) from origin (0,0) to top of rectangle.   */
    IMG_UINT32      ui32LeftOffset;             /*!< Offset (in 1/16th pixels) from origin (0,0) to left of rectangle. */
    IMG_UINT32      ui32Width;                  /*!< Width (in 1/16th pixels) of rectangle.                            */
    IMG_UINT32      ui32Height;                 /*!< Height (in 1/16th lines) of rectangle.                            */

} VDEC_sWindow;


/*!
******************************************************************************
 This structure contains the stream configuration details.
 @brief  VDEC Stream Configuration Information
 ******************************************************************************/
typedef struct
{
    VDEC_eVidStd        eVidStd;                /*!< The video standard.                                    */
    VDEC_eBstrFormat    eBstrFormat;            /*!< Bitstream format.                                      */
    IMG_UINT32          ui32UserStrId;          /*!< Arbitrary stream id assigned by the client.            */

    IMG_BOOL            bUpdateYUV;             /*!< Update the pixel data from the device memory
                                                     (when not shared with host).                           */
    IMG_BOOL            bLowLatencyMode;        /*!< Process each bitstream buffer immediately without
                                                     waiting for the rest of the picture.                   */
    IMG_BOOL            bBandwidthEfficient;    /*!< Minimises bandwidth at the expense of memory.          */
    IMG_BOOL            bSecureStream;          /*!< Flag to indicate that the stream needs to get
                                                     handled in secure memory (if available).               */
    IMG_BOOL            bDisableMvc;            /*!< If set mvc extension will be ignored.                  */
    IMG_BOOL            bFullScan;              /*!< All bitstream data units (e.g. NALs) should be
                                                     detected by the pre-parser since non-picture data
                                                     (SPS/PPS/SEI) may occur after the first video slice
                                                     in the group of buffers provided for a picture.
                                                     NOTE: CPU utilisation might significantly increase and
                                                     impact performance.                                    */
    IMG_BOOL            bImmediateDecode;       /*!< Signaling to start Decode immediately from next picture.*/
    IMG_BOOL            bIntraFrmAsClosedGop;   /*!< To turn on/off considering I-Frames as ClosedGop boundaries. */

} VDEC_sStrConfigData;


/*!
******************************************************************************
 This structure contains information required to configure the picture buffers.
 @brief  Picture Buffer Configuration
******************************************************************************/
typedef struct
{
    IMG_UINT32              ui32CodedWidth;                         /*!< Coded frame width (in pixels) of picture in *decoded* orientation. */
    IMG_UINT32              ui32CodedHeight;                        /*!< Coded frame height (in lines) of picture in *decoded* orientation. */
    IMG_ePixelFormat        ePixelFormat;                           /*!< Pixel format of picture within buffer.                             */
    IMG_UINT32              aui32Stride[IMG_MAX_NUM_PLANES];        /*!< Image stride (in bytes) of planes, could be different for different planes*/
    VDEC_eTileScheme        eTileScheme;                            /*!< Tiling scheme used for rendering picture.                          */
    IMG_BOOL                bByteInterleave;                        /*!< Indicates whether 128-byte interleaving is applied to tiling.      */
    IMG_UINT32              ui32BufSize;                            /*!< Buffer size (in bytes).                                            */
    IMG_BOOL                bPacked;                                /*!< Indicates that chroma plane is immediately adjacent to luma plane.
                                                                         Offset (in bytes) is determined by (ui32Stride * ui32CodedHeight)  */
    IMG_UINT32              aui32ChromaOffset[IMG_MAX_NUM_PLANES];  /*!< Offset (in bytes) to each chroma plane (required when !bPacked).   */

} VDEC_sPictBufConfig;


/*!
******************************************************************************
 This structure contains information relating to a buffer.
 @brief  Buffer Information
******************************************************************************/
typedef struct
{
    SYSBRG_POINTER(IMG_VOID, pvCpuLinearAddr);  /*!< The CPU linear address - which can be used to access the buffer.   */
    IMG_UINT32  ui32ExtImportId;       /*!< The buffer "external import" id.                                    */

    VDEC_sPictBufConfig sPictBufConfig; /*!< Picture buffer configuration (only used by for images)             */

    /* *** NOTE: The following are fields used internally within VDEC... */

    IMG_UINT32  ui32BufSize;            /*!< The size of the buffer (in bytes).  */
    SYSBRG_HANDLE(hBufMallocHandle);            /*!< The buffer allocation handle.       */
    SYSBRG_HANDLE(hBufMapHandle);               /*!< The buffer mapping handle.          */

} VDEC_sBufInfo;

/*!
******************************************************************************
 This structure contains information relating to a buffer.
 @brief  Buffer Information
******************************************************************************/
typedef struct
{
    VDEC_sBufInfo   sBufInfo;            /*!< Buffer info (cointainer)              */
    IMG_UINT32  ui32BufElementNum;       /*!< How many elements are in this buffer  */
    IMG_UINT32  ui32BufElementSize;      /*!< Size of each element                  */
} VDEC_sBufArrayInfo;

/*!
******************************************************************************
 This structure contains information related to a picture plane.
 @brief  Picture Plane Information
******************************************************************************/
typedef struct
{
    IMG_UINT32  ui32Offset;  /*!< The offset of the plane within the buffer (in bytes).  */
    IMG_UINT32  ui32Stride;  /*!< The stride the plane (in bytes).                       */
    IMG_UINT32  ui32Size;    /*!< The size the plane (in bytes).                         */

} VDEC_sPlaneInfo;


/*!
******************************************************************************
 This structure describes the rendered region of a picture buffer (i.e. where
 the image data is written.
 @brief  Picture Buffer Render Information
******************************************************************************/
typedef struct
{
    IMG_UINT32          ui32RenderedSize;             /*!< The total size of pictures rendered area (in bytes).
                                                           Zero indicates that this structure is not populated.             */
    VDEC_sPlaneInfo     asPlaneInfo[VDEC_PLANE_MAX];  /*!< The array of info about all the picture planes.
                                                           NOTE: If the plane size is 0, the plane is not used
                                                           for the chosen output pixel format.                              */
    VDEC_sPictSize      sRendPictSize;                /*!< The maximum picture dimensions supported by this render region.  */

} VDEC_sPictRendInfo;


/*!
******************************************************************************
 This structure defines the properties of a coded picture for which to define
 the render information.
 @brief  Picture Buffer Render Configuration
******************************************************************************/
typedef struct
{
    VDEC_sPictSize      sCodedPictSize;         /*!< Coded picture dimensions (original orientation, 0 degrees) for which
                                                     to calculate render layout.                                            */
    IMG_BOOL            bPacked;                /*!< Chroma plane must be adjacent to Luma (no padding or chroma offset).
                                                     NOTE: this is not compatible with bAllocRotation.                      */
    VDEC_eTileScheme    eTileScheme;            /*!< Tiling scheme to use in decoding this buffer. VDEC_TS0_256x16 is most
                                                     suited to video (larger than decode unit 16x16 pixel MB).              */
    IMG_BOOL            bUseExtendedStrides;    /*!< Force use of extended strides (aligned to 64 bytes) for image
                                                     buffers to ensure that the minimum buffer size is used. NOTE: this
                                                     must be supported by the hardware (see VDEC_IsSupportedFeature()).     */

} VDEC_sPictRendConfig;


/*!
******************************************************************************
 This structure contains the VDEC picture display properties.
 @brief  VDEC Picture Display Properties
******************************************************************************/
typedef struct
{
    VDEC_sRect          sEncDispRegion;                                 /*!< Region specified in encoded bitstream to crop coded picture for display.   */
    VDEC_sRect          sDispRegion;                                    /*!< Region to display within buffer which is equivalent to calling
                                                                             VDEC_SequGetDisplayRegion() with the sequence information and output
                                                                             configuration used in decoding the picture.                                */

     IMG_BOOL           bTopFieldFirst;                                 /*!< Top field was first to be decoded.                                         */

    IMG_UINT32          ui32MaxFrmRepeat;                               /*!< Maximum number of times the frame can be repeated.                         */
    IMG_UINT32          bRepeatFirstField;                              /*!< Repeat first field.                                                        */
    IMG_UINT32          ui32NumPanScanWindows;                          /*!< Number of Pan Scan Windows in frame.                                       */
    VDEC_sWindow        asPanScanWindows[VDEC_MAX_PANSCAN_WINDOWS];     /*!< Pan Scan windows.                                                          */

} VDEC_sPictDispInfo;


/*!
******************************************************************************
 This structure describes the decoded picture attributes (relative to the
 encoded, where necessary, e.g. rotation angle).
 @brief  Stream Output Configuration
******************************************************************************/
typedef struct
{
    PIXEL_sPixelInfo    sPixelInfo;         /*!< Pixel format information.                                              */

    VDEC_eRotMode       eRotMode;           /*!< Picture orientation.                                                   */
    IMG_BOOL            bScale;             /*!< Scaling indicator. When set to IMG_TRUE the decoded picture will be
                                                 down-scaled to the size defined by #sScaledPictSize.                   */
    IMG_BOOL            bForceOold;         /*!< Force applying out-of-loop de-blocking.                                */
    VDEC_sPictSize      sScaledPictSize;    /*!< Scaled picture size. Only relevant if #bScale is set to IMG_TRUE.      */

} VDEC_sStrOutputConfig;


/*!
******************************************************************************
 This structure contains the Color Space Description that may be present in SequenceDisplayExtn(MPEG2),
 VUI parameters(H264), Visual Object(MPEG4) for the application to use.
 @brief  Stream Color Space Properties
******************************************************************************/
typedef struct
{
    IMG_BOOL     bIsPresent;                                 /*!< Will indicate whether stream had this ColorSpace information. */
    IMG_UINT8    ui8ColourPrimaries;                      /*!< To specify value of colour_primaries, 8 uimsbf 
                                                                - may not be used by app, added for completeness */
    IMG_UINT8    ui8TransferCharacteristics;              /*!< To specify value of transfer_characteristics, 8 uimsbf 
                                                               - may not be used by app, added for completeness */
    IMG_UINT8    ui8MatrixCoefficients;                   /*!< To specify value of matrix_coefficients, 8 uimsbf */
} VDEC_sColorSpaceDesc;


/*!
******************************************************************************
 This structure contains common (standard agnostic) sequence header information,
 which is required for image buffer allocation and display.
 @brief  Sequence Header Information (common)
******************************************************************************/
typedef struct
{
    IMG_UINT32              ui32CodecProfile;    /*!< Codec profile as encoded in the bitstream                                                 */
    IMG_UINT32              ui32CodecLevel;      /*!< Codec level as encoded in the bitstream                                                   */

    IMG_UINT32              ui32Bitrate;         /*!< Bitrate in kbps (kilo-bits per second)                                                    */
    IMG_FLOAT               fFrameRate;          /*!< Frame rate fps (frames per second)                                                        */
    IMG_UINT32              ui32FrameRateNum;    /*!< Frame rate numerator                                                        */
    IMG_UINT32              ui32FrameRateDen;    /*!< Frame rate denominator                                                        */

    IMG_UINT32              ui32AspectRatioNum;  /*!< Aspect ratio numerator (width)                                                            */
    IMG_UINT32              ui32AspectRatioDen;  /*!< Aspect ratio denominator (height)                                                         */

    IMG_BOOL                bInterlacedFrames;   /*!< Interlaced frames may be present in the sequence (picture buffer allocation)              */
    PIXEL_sPixelInfo        sPixelInfo;          /*!< Pixel format information for all coded frames in the sequence (picture buffer allocation) */
    VDEC_sPictSize          sMaxFrameSize;       /*!< Maximum frame size for the sequence. Individual frames may differ in size but none
                                                      will exceed these dimensions (picture buffer allocation). This is rounded up to whole MBs */
    VDEC_sPictSize          sFrameSize;          /*!< Frame size for the sequence as defined in the bitstream without any alignment.
                                                      This is MIGHT BE NOT rounded up to whole MBs/CTUs                                         */

    IMG_BOOL                bFieldCodedMBlocks;  /*!< Interlaced macroblocks *may* be present in the sequence                                   */

    IMG_UINT32              ui32MinPicBufNum;    /*!< Minimum number of picture buffers required for decoding a non-conformant stream           */
    IMG_BOOL                bPictureReordering;  /*!< Decode and display order may not be the same (i.e. pictures re-ordered for display)       */

    IMG_BOOL                bPostProcessing;     /*!< Out-of-loop post processing (e.g. OOLD, VC-1 range mapping) might be applied to decoded
                                                      pictures. These buffers would then not be suitable for reference                          */

    VDEC_sRect              sOrigDisplayRegion;  /*!< Region to display within buffer                                                           */

    IMG_UINT32              ui32NumViews;        /*!< Number of views                                                                           */

    IMG_UINT32              ui32MaxReorderPicts; /*!< Indicates the maximum number of re-ordered pictures (H.264 Only). This value will be used
                                                       to constrain the DPB size when non-zero. Otherwise the worst case DPB will be assumed
                                                       which is governed by the sequence profile, level and frame resolution.                   */
    IMG_BOOL                bSeparateChromaPlanes;  /*!< Indicates whether Y,U and V are encoded in separate planes                             */

    IMG_BOOL                bNotDpbFlush;        /*!< Indicates whether or not DPB flush is needed                                              */

    VDEC_sColorSpaceDesc    sColorSpaceInfo;     /*!< Contains Color Space Information for the stream for Codecs which support it. */

} VDEC_sComSequHdrInfo;


/*!
******************************************************************************
 This union contains all the video standard-specific codec configuration structures.

 @brief  Codec Configuration
******************************************************************************/
typedef struct
{
    IMG_UINT32          ui32DefaultHeight;          /*!< Default frame height.      */
    IMG_UINT32          ui32DefaultWidth;           /*!< Default frame width.       */
} VDEC_sCodecConfig;


/*!
******************************************************************************
 This structure contains VXD hardware signatures.
 @brief  VXD Hardware signatures
******************************************************************************/
typedef struct
{
    IMG_BOOL    bFirstFieldReceived;
    IMG_UINT32  ui32CrcShiftRegFE;      /*!< VEC FE shift register CRC                                                 */

    IMG_UINT32  ui32CrcVecCommand;      /*!< VEC Command CRC (VEC_COMMAND_SIGNATURE)                                   */
    IMG_UINT32  ui32CrcVecIxform;       /*!< VEC Inverse Transform CRC (VDEB_VEC_IXFORM_SIGNATURE)                     */

    IMG_UINT32  ui32CrcVdmcPixRecon;    /*!< VDMC Pixel Reconstruction CRC (VDEB_VDMC_PIXEL_RECONSTRUCTION_SIGNATURE)  */

    IMG_UINT32  ui32VdebScaleWriteData; /*!< VDEB Scale Write Data CRC (VDEB_SCALE_WDATA_SIGNATURE)                    */
    IMG_UINT32  ui32VdebScaleAddr;      /*!< VDEB Scale Address CRC (VDEB_SCALE_ADDR_SIGNATURE)                        */

    IMG_UINT32  ui32VdebBBWriteData;    /*!< VDEB Burst B Write Data CRC (VDEB_BURSTB_WDATA_SIGNATURE)                 */
    IMG_UINT32  ui32VdebBBAddr;         /*!< VDEB Burst B Address CRC (VDEB_BURSTB_ADDR_SIGNATURE)                     */
    IMG_UINT32  ui32VdebSysMemAddr;     /*!< VDEB System Memory Address CRC (VDEB_SYS_MEM_ADDR_SIGNATURE)              */
    IMG_UINT32  ui32VdebSysMemWriteData;/*!< VDEC System Memory Write Data CRC (VDEB_SYS_MEM_WDATA)                    */

} VDEC_sPictHwCrc;

/*!
******************************************************************************
 This structure contains the Decoded attributes
 @brief Decoded attributes
******************************************************************************/
typedef struct
{
    IMG_BOOL                    bFirstFieldReceived;
    IMG_UINT32                  ui32FEError;            /*!< Flags to indicate presence of detected errors during the decoding of this picture
                                                        (#VDECFW_eMsgFlagDecodedFeError).                                                               */
    IMG_UINT32                  ui32NoBEDWT;            /*!< No of BEWDT events                                                                         */
    IMG_BOOL                    bDWRFired;              /*!< Signals that DWR fired during the decoding of this picture                                 */

} VDEC_sPictDecoded;

typedef struct
{
    IMG_eBufferType         ePicType;
    SYSBRG_UINT64           pvPictTagParam;
    SYSBRG_UINT64           pvSideBandInfo;
    VDEC_sPictHwCrc         sPictHwCrc;         /*!< VXD hardware signatures for this picture.              */
} VDEC_sPictTagContainer;

/*!
******************************************************************************
 This structure contains decoded picture information for display.
 @brief  Decoded Picture Information
******************************************************************************/
typedef struct
{
    VDEC_ePictState         ePictState;         /*!< Decoded picture state.                                */
    IMG_eBufferType         eBufferType;        /*!< Buffer type (frame, pair, top, bottom)                */

    IMG_UINT32              ui32ErrorFlags;     /*!< Flags word to indicate error in parsing and
                                                     decoding - see #VDEC_eErrorType.                       */

    VDEC_sPictTagContainer  sFirstFieldTagContainer; /*!< A pointer to client specific data, First Field.
                                                     This value was set with bitstream buffer in call to
                                                     VDEC_StreamSubmitBstrBuf().                            */

    VDEC_sPictTagContainer  sSecondFieldTagContainer; /*!< A pointer to client specific data, Second Field.
                                                      This value was set with bitstream buffer in call to
                                                      VDEC_StreamSubmitBstrBuf().                           */

    VDEC_sStrOutputConfig   sOutputConfig;      /*!< Output properties of decoded image.                    */

    VDEC_sPictRendInfo      sRendInfo;          /*!< Picture buffer decoded information structure.          */

    VDEC_sPictDispInfo      sDispInfo;          /*!< Display information for decoded image.                 */

    IMG_BOOL                bLastInSequence;    /*!< This is the last displayed image in sequence.
                                                     NOTE: This flag will only be set when bForceEos
                                                     is set on submission of last bitstream buffer
                                                     in sequence (VDEC_StreamSubmitBstrBuf()).              */
    IMG_UINT32              ui32DecodeId;       /*!< Picture id according to decode order.                  */

    IMG_UINT32              ui32IdForHWCrcCheck;/*!< Picture id used for indexing inside the HWCrc file.
                                                     Workaround because currently HWCrc files do not contain
                                                     CRC for skip pictures */
    IMG_UINT16              ui16ViewID;         /*!< View id of current picture                             */

    IMG_UINT32              ui32TimeStamp;       /*!< timestamp parsed by firmware (parsed in RV).            */

} VDEC_sDecPictInfo;


typedef struct
{
    IMG_UINT32  ui32SequenceHdrId;
    IMG_UINT32  ui32PPSId;
    IMG_UINT32  ui32SecondPPSId;

} VDEC_sDecPictAuxInfo;


/*!
******************************************************************************
 This type defines the bitstream processing error info.
 @brief  Bitstream Processing Error Info
******************************************************************************/
typedef struct
{
    IMG_UINT32  ui32SequenceError;  /*!< Error in parsing sequence related bitstream units. */
    IMG_UINT32  ui32PictureError;   /*!< Error in parsing picture related bitstream units.  */
    IMG_UINT32  ui32OtherError;     /*!< Error in parsing other bitstream units.            */

} VDEC_sBitstreamErrorInfo;


/*!
******************************************************************************
 This type defines the information about why the system is stopped.
 @brief  Stop Info
******************************************************************************/
typedef struct
{
    IMG_UINT32                  ui32StopFlags;        /*!< Stopped status flags as defined in #VDEC_eStopFlags.                  */
    VDEC_sBitstreamErrorInfo    sBitstreamErrorInfo;  /*!< Bitstream error flags.
                                                         NOTE: These flags are only valid if #VDEC_STOPSTATUS_BITSTREAM_ERROR
                                                               stop flag is set.                                               */
    IMG_UINT32                  ui32Error;            /*!< Result code for any error.                                            */

} VDEC_sStopInfo;





/*!
******************************************************************************

 @Function              VDEC_GetVersion

 @Description

 This function provides the VDEC software version and build number.

 @Output   psVersion : A pointer to a #VDEC_sVersion structure in which
                       the version information is returned.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_GetVersion(
    VDEC_sVersion *  psVersion
);


/*!
******************************************************************************

 @Function              VDEC_IsSupportedFeature

 @Description

 This function is used to check whether a requested feature is supported.

 NOTE: Feature combinations are not validated by this call. Please refer to the
 VXD Technical Reference Manual.

 @Input    eFeature    : Feature of device (see #VDEC_eFeature).

 @Output   pbSupported : Pointer to feature supported flag.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_IsSupportedFeature(
    VDEC_eFeature  eFeature,
    IMG_BOOL *     pbSupported
);


/*!
******************************************************************************

 @Function              VDEC_pfnEventCallback

 @Description

 This is the prototype for event callback functions.

 NOTE: The use of pvParam is dependent upon the event - see #VDEC_eEvent
 for details.

 @Input    eEvent       : The event (see #VDEC_eEvent).

 @Input    pvStrCbParam : A pointer client defined stream data as defined
                          in the call to VDEC_StreamCreate().

 @Input    pvBufCbParam : A pointer client defined buffer data as defined
                          in the call to VDEC_StreamMapBuf().

                          NOTE: Only valid for certain events.

 @Input    pvParam      : A pointer to event specific data - see #VDEC_eEvent.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
typedef IMG_RESULT ( * VDEC_pfnEventCallback) (
    VDEC_eEvent  eEvent,
    IMG_VOID *   pvStrCbParam,
    IMG_VOID *   pvBufCbParam,
    IMG_VOID *   pvParam
);


/*!
******************************************************************************

 @Function              VDEC_StreamCreate

 @Description

 This function is used to create a stream.

 @Input    psStrConfigData  : A pointer to a #VDEC_sStrConfigData structure.

 @Input    pfnEventCallback : A pointer to the client callback function.

 @Input    pvStrCbParam     : A pointer to client defined stream data or IMG_NULL.

 @Output   phStrHandle      : A pointer used to return the stream handle.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamCreate(
    VDEC_sStrConfigData *  psStrConfigData,
    VDEC_pfnEventCallback  pfnEventCallback,
    IMG_VOID *             pvStrCbParam,
    IMG_HANDLE *           phStrHandle
);


/*!
******************************************************************************

 @Function              VDEC_StreamDestroy

 @Description

 This function is used to destroy a stream.

 NOTE: Should only be called when VDEC is in the "stopped" state (after receipt
 of event #VDEC_EVENT_STREAM_STOPPED).

 @Input    hStrHandle : The stream handle.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamDestroy(
    IMG_HANDLE  hStrHandle
);


/*!
******************************************************************************

 @Function              VDEC_StreamPlay

 @Description

 This function is used to start playing in the mode as defined by #VDEC_ePlayMode.
 Pictures submitted in bitstream buffers will be scheduled for decoding (subject
 to resource availability) or discarded (when #VDEC_PLAYMODE_PARSE_ONLY).
 If no valid sequence header is present (e.g. start of stream) use parse-only
 mode (#VDEC_PLAYMODE_PARSE_ONLY) to locate the first sequence
 (#VDEC_STOPPOINT_SEQUENCE_START). Refer to stop flags (#VDEC_eStopFlags) for
 information about how to handle stop conditions.

 @Input    hStrHandle        : The stream handle.

 @Input    ePlayMode         : Sets the "play" mode.

 @Input    eStopPoint        : Sets the decode stop point.

 @Input    ui32StopPointQual : Use to qualify the stop point.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamPlay(
    IMG_HANDLE       hStrHandle,
    VDEC_ePlayMode   ePlayMode,
    VDEC_eStopPoint  eStopPoint,
    IMG_UINT32       ui32StopPointQual
);


/*!
******************************************************************************

 @Function              VDEC_StreamStop

 @Description

 This function makes a request for the driver to stop decoding (or discarding
 when #VDEC_PLAYMODE_PARSE_ONLY) at a particular point (#VDEC_eStopPoint) in
 the bitstream. Event #VDEC_EVENT_STREAM_STOPPED will be generated once the
 driver is stopped. This request *might* be pre-empted by an implicit driver stop
 (e.g. for client intervention with #VDEC_STOPSTATUS_RECONFIGURE), ignored if
 eStopPoint = VDEC_STOPPOINT_NOW and another stop is already being processed
 (return code: IMG_ERROR_BUSY), or override previous requests (if they are not
 already handled/met). Consequently, the stopped flags (#VDEC_eStopFlags) should
 be carefully examined to determine the appropriate action. All subsequent requests
 will be ignored up until playback is resumed. Any stop requests made after the
 stopped event (#VDEC_EVENT_STREAM_STOPPED) will be benign and are permitted due
 to event queuing latency in the application code.

 @Input    hStrHandle        : The stream handle.

 @Input    eStopPoint        : Sets the decode stop point.

 @Input    ui32StopPointQual : Use to qualify the stop point.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamStop(
    IMG_HANDLE       hStrHandle,
    VDEC_eStopPoint  eStopPoint,
    IMG_UINT32       ui32StopPointQual
);


/*!
******************************************************************************

 @Function              VDEC_StreamGetStopInfo

 @Description

 This function is used to obtained the stopped status information.

 NOTE: This information will only be valid while VDEC is in the "stopped" state.
 Stop information will not be updated with further API activity until the
 subsequent "stopped" event #VDEC_EVENT_STREAM_STOPPED is received.

 @Input    hStrHandle : The stream handle.

 @Output   psStopInfo : A pointer used to return the stopped status flags
                        as defined in #VDEC_eStopFlags plus additional info.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamGetStopInfo(
    IMG_HANDLE        hStrHandle,
    VDEC_sStopInfo *  psStopInfo
);


/*!
******************************************************************************

 @Function              VDEC_StreamMapBuf

 @Description

 This function is used to map a buffer into the device MMU. This is, however,
 not mapped into the KM and shouldn't not be access by kernel when bridging.
 If (eBufType == VDEC_BUFTYPE_PICTURE) then make sure that sPictBufConfig
 if correctly populated within VDEC_sBufInfo.

 NOTE: The buffer must have been allocated in a way that allows the memory to
 be mapped in the device's MMU.

 @Input    hStrHandle   : The stream handle.

 @Input    pvBufCbParam : A pointer to client defined buffer data or IMG_NULL.

 @Input    eBufType     : Type of buffer to be mapped.

 @Modified psBufInfo    : A pointer to a #VDEC_sBufInfo structure
                          used to return buffer information.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamMapBuf(
    IMG_HANDLE            hStrHandle,
    IMG_VOID            * pvBufCbParam,
    VDEC_eBufType         eBufType,
    VDEC_sBufInfo       * psBufInfo
);


/*!
******************************************************************************

 @Function              VDEC_StreamUnmapBuf

 @Description

 This function is used to unmap a buffer from the device MMU.

 NOTE: Buffers should not be unmapped if they are currently "held" by VDEC:
    1. Bitstream buffer being decoded (VDEC_StreamSubmitBstrBuf() without receiving
       #VDEC_EVENT_BSTRBUF_EMPTY) or
    2. Picture buffer queued for decoding into (VDEC_StreamFillPictBuf() without
       receiving #VDEC_EVENT_PICTBUF_FULL) or
    3. Picture buffer used for reference (filled buffer returned with
       VDEC_sDecPictInfo.bReference).

 @Input    hBufMapHandle  : The buffer map handle.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamUnmapBuf(
    IMG_HANDLE  hBufMapHandle
);


/*!
******************************************************************************

 @Function              VDEC_StreamGetSequHdrInfo

 @Description

 This function is used to obtain the current sequence header information.

 @Input     hStrHandle       : The stream handle.

 @Output    psComSequHdrInfo : A pointer to a #VDEC_sComSequHdrInfo
                               structure used to return sequence header information.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamGetSequHdrInfo(
    IMG_HANDLE              hStrHandle,
    VDEC_sComSequHdrInfo *  psComSequHdrInfo
);


/*!
******************************************************************************

 @Function              VDEC_StreamSetCodecConfig

 @Description

 This function is used to set the codec configuration and must be used (if defined)
 before submitting buffers with VDEC_StreamSubmitBstrBuf().

 @Input     hStrHandle       : The stream handle.

 @Input     psCodecConfig    : A pointer to union #VDEC_sCodecConfig which
                               contains the video standard-specific
                               codec configuration structures.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamSetCodecConfig(
    IMG_HANDLE              hStrHandle,
    VDEC_sCodecConfig     * psCodecConfig
);


/*!
******************************************************************************

 @Function              VDEC_StreamSetNumBstrBuf

 @Description

 This function is used to specify the maximum number of bitstream buffers in use
 so that VDEC can notify when it holds all buffers but is still unable to decode.

 @Input    hStrHandle        : The stream handle.

 @Input    ui32MaxNumBstrBuf : Maximum number of bitstream buffers in use.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamSetNumBstrBuf(
    IMG_HANDLE  hStrHandle,
    IMG_UINT32  ui32MaxNumBstrBuf
);


/*!
******************************************************************************

 @Function              VDEC_StreamSubmitBstrBuf

 @Description

 This function is used to submit different categories of bitstream data (defined
 by #VDEC_eBstrElementType). Bitstream unit parsing (into pictures etc.) will take
 place in the context of this call and queued ready for scheduling on the decoder.

 @Input    hStrContext : The stream handle.

 @Input    psBufInfo : A pointer to a #VDEC_sBufInfo structure containing the
                       buffer information.

 @Input    ui32DataSize : The size of the data in the buffer (in bytes).

 @Input    eBstrElementType : Bitstream element type. Indicates the category
                              of data present in the buffer. This will be
                              interpreted by the BSPP according to #VDEC_eBstrFormat
                              supplied in the stream configuration (#VDEC_sStrConfigData).

 @Input    bElementEnd : This is the last buffer containing data for the current
                         bitstream element.

 @Input    bForceEop   : Set to IMG_TRUE if the client is able to determine
                         that the bitstream data in this buffer is the end of
                         one picture and that the next buffer to be submitted
                         will be the start of the next picture. Otherwise IMG_FALSE.
                         NOTE: If set to IMG_TRUE then the picture will be presented
                         to the decoder without waiting for the next buffer to
                         be submitted in order to determine the picture boundary.

 @Input    pvPictTagParam : A pointer to client specific data (e.g. PTS: presentation
                            time stamp) that will be returned with the *first* picture
                            in *decode* order (#VDEC_sDecPictInfo.pvPictTagParam in pvParam
                            of event callback #VDEC_EVENT_PICTBUF_FULL).

 @Input    bForceEos : This is the last buffer of current sequence of pictures. An
                       indication will be present with the last displayed image
                       (#VDEC_sDecPictInfo.bLastInSequence). If the stream is stopped
                       without processing any more bitstream (i.e. via immediate insertion of fence)
                       the end of sequence will be signalled in the stop flags (#VDEC_eStopFlags).

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.
                        IMG_ERROR_UNEXPECTED_STATE will be returned if VDEC_StreamSetCodecConfig()
                        has not been called and the video standard requires this information.

******************************************************************************/
extern IMG_RESULT VDEC_StreamSubmitBstrBuf(
    IMG_HANDLE              hStrContext,
    VDEC_sBufInfo *         psBufInfo,
    IMG_UINT32              ui32DataSize,
    VDEC_eBstrElementType   eBstrElementType,
    IMG_BOOL                bElementEnd,
    IMG_BOOL                bForceEop,
    IMG_VOID *              pvPictTagParam,
    IMG_BOOL                bForceEos
);


/*!
******************************************************************************

 @Function              VDEC_StreamInsertFence

 @Description

 This function is used to insert a fence in the bistream immediately *after* the
 last "whole" unit (e.g. picture) submitted. VDEC generates event #VDEC_EVENT_STREAM_STOPPED
 once all preceding units have been processed (or discarded when #VDEC_PLAYMODE_PARSE_ONLY).
 Use stop flag #VDEC_STOPSTATUS_FENCE (see #VDEC_eStopFlags) and pvParam (pvTagParam)
 from #VDEC_EVENT_STREAM_STOPPED to determine that/which fence caused the stop.
 If the fence should follow all the data in the last bitstream buffer submitted
 first call VDEC_StreamFlushInput().

 @Input    hStrHandle : The stream handle.

 @Input    pvTagParam : A pointer to client specific data returned via
                        pvParam in #VDEC_EVENT_STREAM_STOPPED callback.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamInsertFence(
    IMG_HANDLE  hStrHandle,
    IMG_VOID *  pvTagParam
);


/*!
******************************************************************************

 @Function              VDEC_StreamSetOutputConfig

 @Description

 This function is used to set the properties of the decoded picture.

 NOTE: The stream MUST be in the stopped state (after receipt of
 event #VDEC_EVENT_STREAM_STOPPED).

 @Input    hStrHandle        : The stream handle.

 @Input    psStrOutputConfig : A pointer to a #VDEC_sStrOutputConfig
                               structure containing the output configuration.

 @Input    psPictBufConfig     : A pointer to picture buffer configuration.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamSetOutputConfig(
    IMG_HANDLE               hStrHandle,
    VDEC_sStrOutputConfig *  psStrOutputConfig,
    VDEC_sPictBufConfig   *  psPictBufConfig
);


/*!
******************************************************************************

 @Function              VDEC_StreamFillPictBuf

 @Description

 This function is used to submit or return a picture buffer to allow it to
 be re-used.

 @Input    psBufInfo : A pointer to a #VDEC_sBufInfo structure
                       containing the buffer information.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamFillPictBuf(
    VDEC_sBufInfo *  psBufInfo
);


/*!
******************************************************************************

 @Function              VDEC_StreamFlushInput

 @Description

 This synchronous function forces all outstanding bitstream buffers (held by the
 BSPP) to be submitted for decoding, otherwise it will have no effect.
 VDEC_StreamInsertFence() should be subsequently used to determine when all
 the stream units have been processed by the driver.

 @Input    hStrHandle : The stream handle.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamFlushInput(
    IMG_HANDLE  hStrHandle
);


/*!
******************************************************************************

 @Function              VDEC_StreamFlushOutput

 @Description

 This asynchronous function forces all remaining pictures to be displayed
 via event #VDEC_EVENT_PICTBUF_FULL and may result in a visual discontinuity
 if subsequent pictures are processed before the next closed GOP. Decoded
 pictures held for reference can be optionally discarded. If references are no
 longer held follow instruction listed for #VDEC_STOPSTATUS_NO_REFERENCE_IMAGES.
 Wait for event #VDEC_EVENT_STREAM_FLUSHED to ensure that all display pictures
 have been flushed.

 NOTE: The stream MUST be in the stopped state.

 @Input    hStrHandle : The stream handle.

 @Input    bDiscardRefs : Indicate that driver should drop references.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamFlushOutput(
    IMG_HANDLE  hStrHandle,
    IMG_BOOL    bDiscardRefs
);


/*!
******************************************************************************

 @Function              VDEC_StreamReleaseBufs

 @Description

 This function is used to release all buffers of the specified type (VDEC_eBufType)
 held by VDEC. Afterwards the client is free to discard or re-use the released buffers.

 NOTE: Should only be called when VDEC is in the "stopped" state.

 @Input    hStrHandle : The stream handle.

 @Input    eBufType   : Indicates the type of buffers to be returned/released.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamReleaseBufs(
    IMG_HANDLE     hStrHandle,
    VDEC_eBufType  eBufType
);


/*!
******************************************************************************

 @Function              VDEC_StreamSetBehaviourOnErrors

 @Description

 This function allows for defining how VDEC behaves on stream processing errors.

 @Input    hStrHandle     : The stream handle.

 @Input    eErrorHandling : Defines how to behave on errors.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamSetBehaviourOnErrors(
    IMG_HANDLE           hStrHandle,
    VDEC_eErrorHandling  eErrorHandling
);


/*!
******************************************************************************

 @Function              VDEC_PictBufGetNum

 @Description

 This function is used to determine the minimum required number of picture
 buffers. For very high resolution streams (where parallelism across cores is
 required for frame-rate) at least one extra buffer is required for each
 additional core. To ensure that the pipeline is kept full (best utilisation)
 additional buffers should be allocated in line with the following calculation:

   VDEC_PictBufGetNum() + ((num_cores * slots_per_core) - 1) + display_pipeline_length

 If this number is profile dependent the worst case value will be provided.

 NOTE: This function is NOT dependent upon the current state of configuration
 of the VDEC stream APIs.

 @Input    psStrConfigData   : A pointer to a #VDEC_sStrConfigData structure.

 @Input    psComSequHdrInfo  : A #VDEC_sComSequHdrInfo structure used to
                               calculate the required number of buffers

 @Input    psStrOutputConfig : A pointer to a #VDEC_sStrOutputConfig
                               structure containing the output configuration.

 @Output   pui32NumBufs      : A pointer used to return the number of buffers.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_PictBufGetNum(
    VDEC_sStrConfigData *    psStrConfigData,
    VDEC_sComSequHdrInfo *   psComSequHdrInfo,
    VDEC_sStrOutputConfig *  psStrOutputConfig,
    IMG_UINT32 *             pui32NumBufs
);


/*!
******************************************************************************

 @Function              VDEC_PictBufGetConfig

 @Description

 This function is used to obtain the picture buffer configuration required for
 decoding. It can be provided to VDEC via VDEC_StreamMapBuf() when mapping
 output picture buffers or when setting output configuration via
 VDEC_StreamSetOutputConfig(). The configuration takes into account scaling/rotation
 transformations etc. from the psStrOutputConfig but cropping is left up to the
 client.

 NOTE: This function is NOT dependent upon the current state of configuration
 of the VDEC stream APIs.

 @Input    psStrConfigData   : A pointer to a #VDEC_sStrConfigData structure.

 @Input    psPictRendConfig  : A pointer to buffer allocation information.

 @Input    bAllocRotation    : If set to IMG_TRUE, it is assumed that rotation
                               will be required somewhere in the bitstream.
                               The allocated buffer size takes this possibility
                               into account to avoid re-allocation.

 @Input    psStrOutputConfig : A pointer to a #VDEC_sStrOutputConfig
                               structure containing the output configuration.

 @Output   psPictBufConfig   : A pointer to a #VDEC_sPictBufConfig structure
                               used to return the picture buffer information.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_PictBufGetConfig(
    const VDEC_sStrConfigData   * psStrConfigData,
    const VDEC_sPictRendConfig  * psPictRendConfig,
    IMG_BOOL                      bAllocRotation,
    const VDEC_sStrOutputConfig * psStrOutputConfig,
    VDEC_sPictBufConfig         * psPictBufConfig
);


/*!
******************************************************************************

 @Function              VDEC_SequGetDisplayRegion

 @Description

 This function is used to obtain the displayable region within each frame in
 the sequence.

 @Input    psComSequHdrInfo  : A #VDEC_sComSequHdrInfo structure used to
                               obtain the coded and original display size

 @Input    psStrOutputConfig : A pointer to a #VDEC_sStrOutputConfig
                               structure containing the output configuration.

 @Output   psDisplayRegion   : A pointer to return the display region of each
                               frame in this sequence.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_SequGetDisplayRegion(
    VDEC_sComSequHdrInfo  * psComSequHdrInfo,
    VDEC_sStrOutputConfig * psStrOutputConfig,
    VDEC_sRect            * psDisplayRegion
);

/*!
******************************************************************************

 @Function              VDEC_StreamGetDefragmentedBuffer

 @Description

 This function is used to get a buffer from the Defragmented buffer pool.
 These buffers (belonging to vdec_api) are used to reconstruct buffer data
 from non-consecutive coded picture data (picture spanned across multiple buffers)
 in the case of VP8 multi-partition pictures.

 @Input    hStrHandle     : The stream handle.

 @Input    ui32DataSize   : Size of the buffer being required.

 @Output   ppsBufInfo     : A pointer to pointer to a #VDEC_sBufInfo structure
                            used to return buffer information.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDEC_StreamGetDefragmentedBuffer(
    const IMG_HANDLE            hStrHandle,
    const IMG_UINT32            ui32DataSize,
    VDEC_sBufInfo **            ppsBufInfo
);

/*!
******************************************************************************

 @Function              VDECEXT_PictBufGetInfo

 @Description

 This function is used to get the buffer information based on the stream
 and output configuration.

 @Input    psStrConfigData   : A pointer to stream configuration information.

 @Input    psPictBufConfig   : A pointer to picture buffer configuration.

 @Input    psComSequHdrInfo : A pointer to a #VDEC_sComSequHdrInfo
                               structure used to calculate render region.

 @Output   psPictRendInfo  : A pointer used to return the internal picture
                               buffer information.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECEXT_PictBufGetInfo(
    const VDEC_sStrConfigData   * psStrConfigData,
    const VDEC_sPictBufConfig   * psPictBufConfig,
    const VDEC_sComSequHdrInfo  * psComSequHdrInfo,
    VDEC_sPictRendInfo          * psPictRendInfo
);


/*!
******************************************************************************

 @Function              VDECEXT_BufMalloc

 @Description

 This function is used to allocate a device buffer - suitable for mapping
 into the devices MMU.

 @Input    ui32BufSize : The size of the buffer (in bytes).

 @Input    eMemAttrib  : The memory attributes.

 @Modified psBufInfo   : A pointer to a #VDEC_sBufInfo structure
                         used to return buffer information.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECEXT_BufMalloc(
    IMG_UINT32       ui32BufSize,
    SYS_eMemAttrib   eMemAttrib,
    VDEC_sBufInfo *  psBufInfo
);


/*!
******************************************************************************

 @Function              VDECEXT_BufFree

 @Description

 This function is used to free a buffer.

 NOTE: The buffer should NOTE be freed until it's been unmapped.

 @Input    hBufMallocHandle : The buffer allocation handle.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECEXT_BufFree(
    IMG_HANDLE  hBufMallocHandle
);


/*!
******************************************************************************

 @Function              VDECEXT_BufImport

 @Description

 This function is used to import a device buffer - suitable for mapping
 into the devices MMU.

 @Input    ui32BufSize  : Buffer size

 @Input    hExternalBuf : Handle to external buffer

 @Input    eImpBufType  : Type of buffer to be imported

 @Input    eMemAttrib   : The memory attributes.

 @Output   psBufInfo    : A pointer to a #VDEC_sBufInfo structure
                          used to return buffer information.

 @Return   IMG_RESULT   : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECEXT_BufImport(
    IMG_UINT32            ui32BufSize,
    IMG_HANDLE            hExternalBuf,
    PALLOC_eImportBufType ePallocImpBufType,
    SYS_eMemAttrib        eMemAttrib,
    VDEC_sBufInfo *       psBufInfo
);


/*!
******************************************************************************

 @Function              VDECEXT_StreamPrintStatus

 @Description

 This function is used to print the stream status to the console.

 @Input    hStrHandle : The stream handle.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECEXT_StreamPrintStatus(
    IMG_HANDLE  hStrHandle
);


#ifdef __cplusplus
}
#endif

#endif /* __VDEC_API_H__   */



