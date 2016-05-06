/*!
 *****************************************************************************
 *
 * @File       xpltags.h
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

#ifndef _DE_XPLTAGS_H_
#define _DE_XPLTAGS_H_

/*******************************/
/* List of supported tag types */
enum XPL_TAG_TYPES
{
    // Generic:
    RANGE_BEGIN   = 0,
    RANGE_END,
    DATA_ITEM,
    TIMING_POINT

    // DE Specific:

} ;
/*******************************/

/***********************************/
/* List of supported timing ranges */
enum XPL_TIMING_RANGES
{
    // Generic:
    FE                    = 0,
    BE,
    FRAME_DECODE,

    // VIDDEC Specific:
    FE_SETUP_1_2          = 0x065,
    PARSE_HEADER_SETUP_REG_2_5,
    PICMAN_4_5,
    FW_SAVED_3_4,
    FE_1STSLICE_5_6,
    FE_DECODE_2_7,
    BE_1STSLICE_8_9,
    BE_DECODE_8_10,
    SYNC_TIME,
    PARSE_SLICE_HEADER,
    SETUP_REGISTERS,
    PARSE_AND_SETUP_REG,
    PARSER_LOAD,
    MTX_LOAD,
    TOTAL_HW_FE_SUM_5_6,
    TOTAL_HW_FE_SUM_8_9,
    TOTAL_1_10,
    TOTAL_SETUP_VLC,

    RECORD               = 0x080,

    // DE Specific:
    SETUP                = 0x100,
    SLICE_DECODE,
    H264_SLICE_HEADER_DECODE,
    BE_SETUP,
    BE_SYNC,
    HDR_PARSE,
} ;
/***********************************/

/********************************/
/* List of supported data items */
enum XPL_DATA_ITEMS
{
    // Generic:
    PIC_DATA        = 0,
    CORE_FREQ,
    TEST_ID,

    SLICE_NUM,
    SLICE_TYPE,
    FRAME_BITSTREAM_BIT_SIZE,
    FRAME_CODED_WIDTH,
    FRAME_CODED_HEIGHT,
    FRAME_CODED_SIZE,

    // DE Specific:
    HW_CRC          = 0x100,
    SLICE_FLAGS,
    SLICE_BYTES,
    APP_CMD_TYPE,
    PANIC_FE_STATUS,
    PANIC_BE_STATUS,
    PANIC_TRIGGER,
    THREAD_ID,
    TICKS_PER_MS,
    DECODE_CONFIG,
    FRAME_ID,
    CORE_ID,

    FE_TICKS,
    BE_TICKS,

    SYNC_ID,
    SYNC_COMMAND
} ;
/********************************/

/***********************************/
/* List of supported timing points */
enum XPL_TIMING_POINTS
{
    // Generic:

    // DE Specific:
    RENDER   = 0x100,
    SUBMIT,
    NOTIFY,
    EXECUTE

} ;
/***********************************/

/*****************************/
/* List of Decode Config IDs */
enum CONFIG_IDs
{
    CFG_H264_VLD_SHORT_SLICE = 0x0,
    CFG_H264_VLD_LONG_SLICE,
    CFG_MPEG2_MC             = 0x10,
    CFG_MPEG2_MC_DEBUG,
    CFG_MPEG2_IDCT,
    CFG_MPEG2_VLD            = 0x20,
    CFG_MPEG4_VLD            = 0x30,
    CFG_VC1_MC               = 0x40,
    CFG_VC1_VLD              = 0x50,
    CFG_VP6_VLD              = 0x60,
    CFG_REAL_VLD             = 0x70,
    CFG_VP8_VLD              = 0x80,
    CFG_JPEG_VLD             = 0x90,
    CFG_ROTATE               = 0xa0
};
/*****************************/

#endif
