/*!
 *****************************************************************************
 *
 * @File       vxd_config.h
 * @Title      VXD Platform configuration
 * @Description    platform specific configuration values. this file contains
 *  values specifically for the img fpga platform.
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


#define MAX_PLATFORM_SUPPORTED_HEIGHT 4096
#define MAX_PLATFORM_SUPPORTED_WIDTH 4096
#define MAX_PLATFORM_SUPPORTED_PIXELS //(4096*2160) // (4096*4096) // (3840*2160))

#define MAX_CONCURRENT_STREAMS 16

/*
*****************************************************************************
 H\W Core Information
*****************************************************************************/

#define NUM_CORES_H265      1   /*!< Number of Decoder Cores for H.265 */
#define NUM_CORES_H264      1   /*!< Number of Decoder Cores for H.264 */
#define NUM_CORES_MPEG4     1   /*!< Number of Decoder Cores for MPEG4 */
#define NUM_CORES_MPEG2     1   /*!< Number of Decoder Cores for MPEG2 */
#define NUM_CORES_VC1       1   /*!< Number of VC1 Decoder for VC1     */
#define NUM_CORES_VP6       1   /*!< Number of VP6 Decoder for VP6     */
#define NUM_CORES_VP8       1   /*!< Number of VP8 Decoder for VP8     */
#define NUM_CORES_REAL      1   /*!< Number of REAL Decoder for REAL   */
#define NUM_CORES_JPEG      1   /*!< Number of JPEG Decoder for JPEG   */
#define NUM_CORES_AVS       1   /*!< Number of JPEG Decoder for AVS   */


#define NUM_SLOTS_PER_CORE  2   /*!< Default number of slots (pictures) in each core.*/

#define HAS_AVS         //!< Enable AVS support
#define HAS_H264        //!< Enable H.264 support
#ifdef VDEC_USE_PVDEC
#define HAS_HEVC        //!< Enable HEVC support (D5500 only)
#endif
#define HAS_JPEG        //!< Enable JPEG support
#define HAS_MPEG2       //!< Enable MPEG2 support
#define HAS_MPEG4       //!< Enable MPEG4 support
#define HAS_REAL        //!< Enable Real Video support
#define HAS_VC1         //!< Enable VC-1/WMV9 support
#define HAS_VP6         //!< Enable VP6 support
#define HAS_VP8         //!< Enable VP8 support


/*
*****************************************************************************
 Video Input OMX Port Defaults
*****************************************************************************/

#define VIDEO_INPUT_BUFFER_SIZE         (1024 * 1024 * 6)    /*!< 6 MB:Default Video Input Minumum Buffer Size is 1.5M.Modify 6 M for 4K video. Min 1 MB considering conformance */
#define VIDEO_INPUT_BUFFERS_MINIMUM     4          /*!< Default Video Input Minumum Buffer Count */
#define VIDEO_INPUT_BUFFERS_ACTUAL      4          /*!< Default Video Input Actual Buffer Count*/

/**************************************************************************/

/*
*****************************************************************************
 Android Specific Flags
*****************************************************************************/
#if defined(ANDROID)
/* Usage flags for native input buffers: set to sw r/w for the moment for debugging */
#define GRALLOC_USAGE_FLAGS_INPUT   GRALLOC_USAGE_SW_READ_OFTEN // (GRALLOC_USAGE_SW_READ_OFTEN | GRALLOC_USAGE_SW_WRITE_OFTEN)
/* Usage flags for native ouput buffers: set to sw r/w for the moment for debugging */
#define GRALLOC_USAGE_FLAGS_OUTPUT  GRALLOC_USAGE_SW_READ_OFTEN// (GRALLOC_USAGE_SW_READ_OFTEN | GRALLOC_USAGE_SW_WRITE_OFTEN)
#endif
