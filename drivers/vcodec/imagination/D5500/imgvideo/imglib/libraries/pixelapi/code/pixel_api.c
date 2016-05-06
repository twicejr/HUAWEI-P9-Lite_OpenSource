/*!
 *****************************************************************************
 *
 * @File       pixel_api.c
 * @Description    This file contains generic pixel manipulation utility functions.
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

#ifdef PIXEL_USE_SORT
#ifndef IMG_KERNEL_MODULE
#include <stdlib.h>
#else // IMG_KERNEL_MODULE
#include "sort_km.h"
#endif
#endif

#include <img_types.h>
#include <img_defs.h>
#include <img_errors.h>
#include <img_pixfmts.h>
#include <img_structs.h>

#include "pixel_api.h"
#include "pixel_api_internals.h"
#include "system.h"

#define NUM_OF_FORMATS 103

#ifdef PIXEL_USE_SORT
/**
 * @brief the array of pixel formats (NUM_OF_FORMATS elements) - sorted by information rather pixel enum
 * @note sorted by initSearch()
 *
 * A second array is required to sort the formats using the other attributes.
 */
static PIXEL_sPixelInfo asInfoFormats[NUM_OF_FORMATS];
#endif

/**
 * @brief Pointer to the default format in the asPixelFormats array - default format is an invalid format
 * @note pointer set by initSearch()
 *
 * This pointer is also used to know if the arrays were sorted
 */
static PIXEL_sPixelInfo *pDefaultFormat = NULL;
/**
 * @brief Actual array storing the pixel formats information.
 *
 * @warning if PIXEL_USE_SORT is defined this array is sorted by pixel enum
 */
static PIXEL_sPixelInfo asPixelFormats[NUM_OF_FORMATS] =
{
  //{ePixelFormat,                  eChromaInterleaved, bChromaFormat,        eMemoryPacking,       eChromaFormatIdc,   ui32BitDepthY,  ui32BitDepthC,      ui32NoPlanes},
    {IMG_PIXFMT_PL12Y8,             PIXEL_INVALID_CI,   PIXEL_MONOCHROME,     PIXEL_BIT8_MP,        PIXEL_FORMAT_MONO,  8,              PIXEL_INVALID_BDC,  1           },
    {IMG_PIXFMT_PL12Y10,            PIXEL_INVALID_CI,   PIXEL_MONOCHROME,     PIXEL_BIT10_MP,       PIXEL_FORMAT_MONO,  10,             PIXEL_INVALID_BDC,  1           },
    {IMG_PIXFMT_PL12Y10_MSB,        PIXEL_INVALID_CI,   PIXEL_MONOCHROME,     PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_MONO,  10,             PIXEL_INVALID_BDC,  1           },
    {IMG_PIXFMT_PL12Y10_LSB,        PIXEL_INVALID_CI,   PIXEL_MONOCHROME,     PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_MONO,  10,             PIXEL_INVALID_BDC,  1           },
    {IMG_PIXFMT_PL12IMC2,           PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_420,   8,              8,                  2           },

    {IMG_PIXFMT_411PL111YUV8,       PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_411,   8,              8,                  3           },
    {IMG_PIXFMT_411PL12YUV8,        PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_411,   8,              8,                  2           },
    {IMG_PIXFMT_411PL12YVU8,        PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_411,   8,              8,                  2           },

    {IMG_PIXFMT_420PL8YUV8,         PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_420,   8,              8,                  3           },
    {IMG_PIXFMT_420PL8YUV10,        PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_420,   10,             10,                 3           },
    {IMG_PIXFMT_420PL111YUV10_MSB,  PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_420,   10,             10,                 3           },
    {IMG_PIXFMT_420PL111YUV10_LSB,  PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_420,   10,             10,                 3           },
    {IMG_PIXFMT_420PL111Y8UV10,     PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_420,   8,              10,                 3           },
    {IMG_PIXFMT_420PL111Y8UV10_MSB, PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_420,   8,              10,                 3           },
    {IMG_PIXFMT_420PL111Y8UV10_LSB, PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_420,   8,              10,                 3           },
    {IMG_PIXFMT_420PL111Y10UV8,     PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_420,   10,             8,                  3           },
    {IMG_PIXFMT_420PL111Y10UV8_MSB, PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_420,   10,             8,                  3           },
    {IMG_PIXFMT_420PL111Y10UV8_LSB, PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_420,   10,             8,                  3           },
    {IMG_PIXFMT_420PL12YUV8,        PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_420,   8,              8,                  2           },
    {IMG_PIXFMT_420PL12YVU8,        PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_420,   8,              8,                  2           },
    {IMG_PIXFMT_420PL12YUV10,       PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_420,   10,             10,                 2           },
    {IMG_PIXFMT_420PL12YVU10,       PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_420,   10,             10,                 2           },
    {IMG_PIXFMT_420PL12YUV10_MSB,   PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_420,   10,             10,                 2           },
    {IMG_PIXFMT_420PL12YVU10_MSB,   PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_420,   10,             10,                 2           },
    {IMG_PIXFMT_420PL12YUV10_LSB,   PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_420,   10,             10,                 2           },
    {IMG_PIXFMT_420PL12YVU10_LSB,   PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_420,   10,             10,                 2           },
    {IMG_PIXFMT_420PL12Y8UV10,      PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_420,   8,              10,                 2           },
    {IMG_PIXFMT_420PL12Y8VU10,      PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_420,   8,              10,                 2           },
    {IMG_PIXFMT_420PL12Y8UV10_MSB,  PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_420,   8,              10,                 2           },
    {IMG_PIXFMT_420PL12Y8VU10_MSB,  PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_420,   8,              10,                 2           },
    {IMG_PIXFMT_420PL12Y8UV10_LSB,  PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_420,   8,              10,                 2           },
    {IMG_PIXFMT_420PL12Y8VU10_LSB,  PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_420,   8,              10,                 2           },
    {IMG_PIXFMT_420PL12Y10UV8,      PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_420,   10,             8,                  2           },
    {IMG_PIXFMT_420PL12Y10VU8,      PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_420,   10,             8,                  2           },
    {IMG_PIXFMT_420PL12Y10UV8_MSB,  PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_420,   10,             8,                  2           },
    {IMG_PIXFMT_420PL12Y10VU8_MSB,  PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_420,   10,             8,                  2           },
    {IMG_PIXFMT_420PL12Y10UV8_LSB,  PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_420,   10,             8,                  2           },
    {IMG_PIXFMT_420PL12Y10VU8_LSB,  PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_420,   10,             8,                  2           },
    {IMG_PIXFMT_422PL8YUV8,         PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_422,   8,              8,                  3           },
    {IMG_PIXFMT_422PL8YUV10,        PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_422,   10,             10,                 3           },
    {IMG_PIXFMT_422PL111YUV10_MSB,  PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_422,   10,             10,                 3           },
    {IMG_PIXFMT_422PL111YUV10_LSB,  PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_422,   10,             10,                 3           },
    {IMG_PIXFMT_422PL111Y8UV10,     PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_422,   8,              10,                 3           },
    {IMG_PIXFMT_422PL111Y8UV10_MSB, PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_422,   8,              10,                 3           },
    {IMG_PIXFMT_422PL111Y8UV10_LSB, PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_422,   8,              10,                 3           },
    {IMG_PIXFMT_422PL111Y10UV8,     PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_422,   10,             8,                  3           },
    {IMG_PIXFMT_422PL111Y10UV8_MSB, PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_422,   10,             8,                  3           },
    {IMG_PIXFMT_422PL111Y10UV8_LSB, PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_422,   10,             8,                  3           },
    {IMG_PIXFMT_422PL12YUV8,        PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_422,   8,              8,                  2           },
    {IMG_PIXFMT_422PL12YVU8,        PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_422,   8,              8,                  2           },
    {IMG_PIXFMT_422PL12YUV10,       PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_422,   10,             10,                 2           },
    {IMG_PIXFMT_422PL12YVU10,       PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_422,   10,             10,                 2           },
    {IMG_PIXFMT_422PL12YUV10_MSB,   PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_422,   10,             10,                 2           },
    {IMG_PIXFMT_422PL12YVU10_MSB,   PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_422,   10,             10,                 2           },
    {IMG_PIXFMT_422PL12YUV10_LSB,   PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_422,   10,             10,                 2           },
    {IMG_PIXFMT_422PL12YVU10_LSB,   PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_422,   10,             10,                 2           },
    {IMG_PIXFMT_422PL12Y8UV10,      PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_422,   8,              10,                 2           },
    {IMG_PIXFMT_422PL12Y8VU10,      PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_422,   8,              10,                 2           },
    {IMG_PIXFMT_422PL12Y8UV10_MSB,  PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_422,   8,              10,                 2           },
    {IMG_PIXFMT_422PL12Y8VU10_MSB,  PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_422,   8,              10,                 2           },
    {IMG_PIXFMT_422PL12Y8UV10_LSB,  PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_422,   8,              10,                 2           },
    {IMG_PIXFMT_422PL12Y8VU10_LSB,  PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_422,   8,              10,                 2           },
    {IMG_PIXFMT_422PL12Y10UV8,      PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_422,   10,             8,                  2           },
    {IMG_PIXFMT_422PL12Y10VU8,      PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_422,   10,             8,                  2           },
    {IMG_PIXFMT_422PL12Y10UV8_MSB,  PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_422,   10,             8,                  2           },
    {IMG_PIXFMT_422PL12Y10VU8_MSB,  PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_422,   10,             8,                  2           },
    {IMG_PIXFMT_422PL12Y10UV8_LSB,  PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_422,   10,             8,                  2           },
    {IMG_PIXFMT_422PL12Y10VU8_LSB,  PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_422,   10,             8,                  2           },
    {IMG_PIXFMT_444PL111YUV8,       PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_444,   8,              8,                  3           },
    {IMG_PIXFMT_444PL111YUV10,      PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_444,   10,             10,                 3           },
    {IMG_PIXFMT_444PL111YUV10_MSB,  PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_444,   10,             10,                 3           },
    {IMG_PIXFMT_444PL111YUV10_LSB,  PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_444,   10,             10,                 3           },
    {IMG_PIXFMT_444PL111Y8UV10,     PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_444,   8,              10,                 3           },
    {IMG_PIXFMT_444PL111Y8UV10_MSB, PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_444,   8,              10,                 3           },
    {IMG_PIXFMT_444PL111Y8UV10_LSB, PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_444,   8,              10,                 3           },
    {IMG_PIXFMT_444PL111Y10UV8,     PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_444,   10,             8,                  3           },
    {IMG_PIXFMT_444PL111Y10UV8_MSB, PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_444,   10,             8,                  3           },
    {IMG_PIXFMT_444PL111Y10UV8_LSB, PIXEL_INVALID_CI,   PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_444,   10,             8,                  3           },
    {IMG_PIXFMT_444PL12YUV8,        PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_444,   8,              8,                  2           },
    {IMG_PIXFMT_444PL12YVU8,        PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_444,   8,              8,                  2           },
    {IMG_PIXFMT_444PL12YUV10,       PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_444,   10,             10,                 2           },
    {IMG_PIXFMT_444PL12YVU10,       PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_444,   10,             10,                 2           },
    {IMG_PIXFMT_444PL12YUV10_MSB,   PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_444,   10,             10,                 2           },
    {IMG_PIXFMT_444PL12YVU10_MSB,   PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_444,   10,             10,                 2           },
    {IMG_PIXFMT_444PL12YUV10_LSB,   PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_444,   10,             10,                 2           },
    {IMG_PIXFMT_444PL12YVU10_LSB,   PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_444,   10,             10,                 2           },
    {IMG_PIXFMT_444PL12Y8UV10,      PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_444,   8,              10,                 2           },
    {IMG_PIXFMT_444PL12Y8VU10,      PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_444,   8,              10,                 2           },
    {IMG_PIXFMT_444PL12Y8UV10_MSB,  PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_444,   8,              10,                 2           },
    {IMG_PIXFMT_444PL12Y8VU10_MSB,  PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_444,   8,              10,                 2           },
    {IMG_PIXFMT_444PL12Y8UV10_LSB,  PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_444,   8,              10,                 2           },
    {IMG_PIXFMT_444PL12Y8VU10_LSB,  PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_444,   8,              10,                 2           },
    {IMG_PIXFMT_444PL12Y10UV8,      PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_444,   10,             8,                  2           },
    {IMG_PIXFMT_444PL12Y10VU8,      PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MP,       PIXEL_FORMAT_444,   10,             8,                  2           },
    {IMG_PIXFMT_444PL12Y10UV8_MSB,  PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_444,   10,             8,                  2           },
    {IMG_PIXFMT_444PL12Y10VU8_MSB,  PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_MSB_MP,   PIXEL_FORMAT_444,   10,             8,                  2           },
    {IMG_PIXFMT_444PL12Y10UV8_LSB,  PIXEL_UV_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_444,   10,             8,                  2           },
    {IMG_PIXFMT_444PL12Y10VU8_LSB,  PIXEL_VU_ORDER,     PIXEL_MULTICHROME,    PIXEL_BIT10_LSB_MP,   PIXEL_FORMAT_444,   10,             8,                  2           },
    {IMG_PIXFMT_YUYV8888,           PIXEL_UV_ORDER |
                                    PIXEL_YAYB_ORDER,   PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_422,   8,              8,                  1           },
    {IMG_PIXFMT_YVYU8888,           PIXEL_VU_ORDER |
                                    PIXEL_YAYB_ORDER,   PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_422,   8,              8,                  1           },
    {IMG_PIXFMT_UYVY8888,           PIXEL_UV_ORDER |
                                    PIXEL_AYBY_ORDER,   PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_422,   8,              8,                  1           },
    {IMG_PIXFMT_VYUY8888,           PIXEL_VU_ORDER |
                                    PIXEL_AYBY_ORDER,   PIXEL_MULTICHROME,    PIXEL_BIT8_MP,        PIXEL_FORMAT_422,   8,              8,                  1           },

    {IMG_PIXFMT_UNDEFINED,          PIXEL_INVALID_CI,   0,                    0,                    PIXEL_FORMAT_INVALID,0,             0,                  0           }
};


/**
 * @brief Array containing string lookup of pixel format IDC.
 *
 * @warning this must be kept in step with PIXEL_FormatIdc.
 */
IMG_CHAR acPixelFormatIdcNames[6][16] =
{
    "Monochrome",
    "4:1:1",
    "4:2:0",
    "4:2:2",
    "4:4:4",
    "Invalid",
};

IMGVIDEO_EXPORT_SYMBOL(acPixelFormatIdcNames)

/**
 * @brief Array containing string lookup of pixel memory packing.
 *
 * @warning this must be kept in step with PIXEL_eMemoryPacking.
 */
IMG_CHAR acPixelMemoryPackingNames[4][64] =
{
    "8-bit (no packing)",
    "10-bit in MSB of 16b word",
    "10-bit in LSB of 16b word",
    "10-bit packed 3 to one 32b double word",
};
IMGVIDEO_EXPORT_SYMBOL(acPixelMemoryPackingNames)


/**
 * @brief Array containing string lookup of pixel chroma interleaving.
 *
 * @warning this must be kept in step with PIXEL_eChromaInterleaved.
 */
IMG_CHAR acPixelChromaInterleavedNames[5][16] =
{
    "Invalid",
    "UV order",
    "VU order",
    "YAYB order",
    "AYBY order",
};

IMGVIDEO_EXPORT_SYMBOL(acPixelChromaInterleavedNames)

static int PIXEL_ComparePixelFormats(const void * inA, const void * inB)
{
    return  ((PIXEL_sPixelInfo*)inA)->ePixelFormat - ((PIXEL_sPixelInfo*)inB)->ePixelFormat;
}

/**
 * @brief Search a pixel format based on its attributes rather than its format enum
 * @warning use PIXEL_ComparePixelFormats to search by enum
 */
static int PIXEL_ComparePixelInfo(
    const void * inA,
    const void * inB
)
{
    int result = 0;
    const PIXEL_sPixelInfo *fmtA = (PIXEL_sPixelInfo*)inA;
    const PIXEL_sPixelInfo *fmtB = (PIXEL_sPixelInfo*)inB;

    //if ( (result = fmtA->ePixelFormat - fmtB->ePixelFormat) != 0 ) return result;

    if( (result = fmtA->eChromaFormatIdc - fmtB->eChromaFormatIdc) != 0) return result;

    if( (result = fmtA->eMemoryPacking - fmtB->eMemoryPacking) != 0) return result;

    if( (result = fmtA->eChromaInterleaved - fmtB->eChromaInterleaved) != 0) return result;

    if( (result = fmtA->ui32BitDepthY - fmtB->ui32BitDepthY) != 0) return result;

    if( (result = fmtA->ui32BitDepthC - fmtB->ui32BitDepthC) != 0) return result;

    if( (result = fmtA->ui32NoPlanes - fmtB->ui32NoPlanes) != 0) return result;

    return result;
}

static IMG_VOID pixel_InitSearch(IMG_VOID)
{
    static IMG_UINT32 ui32SearchInitialized = 0;

    ui32SearchInitialized++;
    if(1 == ui32SearchInitialized)
    {
        if(IMG_NULL == pDefaultFormat)
        {
            IMG_INT32 ui32I = 0;

#ifdef PIXEL_USE_SORT
            IMG_MEMCPY(asInfoFormats, asPixelFormats, NUM_OF_FORMATS * sizeof(PIXEL_sPixelInfo));

            qsort(asPixelFormats, NUM_OF_FORMATS, sizeof(PIXEL_sPixelInfo), &PIXEL_ComparePixelFormats);
            qsort(asInfoFormats, NUM_OF_FORMATS, sizeof(PIXEL_sPixelInfo), &PIXEL_ComparePixelInfo);
#endif

            ui32I = NUM_OF_FORMATS - 1;
            while(ui32I >= 0)
            {
                if(IMG_PIXFMT_UNDEFINED == asPixelFormats[ui32I].ePixelFormat)
                {
                    pDefaultFormat = &(asPixelFormats[ui32I]);
                    break;
                }
            }
            IMG_ASSERT(IMG_NULL != pDefaultFormat);
        }
    }
    else
    {
        ui32SearchInitialized--;
    }
}

static PIXEL_sPixelInfo* pixel_SearchFormat(
    const PIXEL_sPixelInfo *key,
    IMG_BOOL8               bEnumOnly
)
{
    PIXEL_sPixelInfo *formatFound = IMG_NULL;
    int (*compar)(const void *, const void *);

    if ( bEnumOnly == IMG_TRUE )
    {
        compar = &PIXEL_ComparePixelFormats;
    }
    else
    {
        compar = &PIXEL_ComparePixelInfo;
    }

#ifdef PIXEL_USE_SORT
    {
        PIXEL_sPixelInfo *arrayToUse = asPixelFormats;
        if ( bEnumOnly == IMG_FALSE ) arrayToUse = asInfoFormats;

        formatFound = (PIXEL_sPixelInfo*) bsearch(key, arrayToUse, NUM_OF_FORMATS, sizeof(PIXEL_sPixelInfo), compar);
    }
#else
    {
        IMG_UINT32 ui32I;

        for(ui32I = 0; ui32I < NUM_OF_FORMATS; ui32I++)
        {
            if(compar(key, &asPixelFormats[ui32I]) == 0)
            {
                formatFound = &asPixelFormats[ui32I];
                break;
            }
        }
    }
#endif

    return formatFound;
}

/**
 * @brief Set a pixel format info structure to the default.
 * @warning This MODIDIFES the pointer therefore you shouldn't call it on pointer you got from the library!
 */
static IMG_VOID pixel_PixelInfoDefaults(
    PIXEL_sPixelInfo *toDefault
)
{
    if(IMG_NULL == pDefaultFormat)
    {
        pixel_InitSearch();
    }

    IMG_MEMCPY(toDefault, pDefaultFormat, sizeof(PIXEL_sPixelInfo));
}


IMG_ePixelFormat PIXEL_GetPixelFormat(
    PIXEL_FormatIdc eChromaFormatIdc,
    PIXEL_eChromaInterleaved eChromaInterleaved,
    PIXEL_eMemoryPacking eMemoryPacking,
    IMG_UINT32 ui32BitDepthY,
    IMG_UINT32 ui32BitDepthC,
    IMG_UINT32 ui32NoPlanes
)
{
    IMG_UINT32 ui32internalNoPlanes = (ui32NoPlanes == 0 || ui32NoPlanes > 4)? 2 : ui32NoPlanes;
    PIXEL_sPixelInfo key;
    PIXEL_sPixelInfo *formatFound = NULL;

    /*We want to use invalid eChromaFormatIdc*/
    //IMG_ASSERT(eChromaFormatIdc==PIXEL_FORMAT_MONO ||
             //  eChromaFormatIdc==PIXEL_FORMAT_411  ||
    //           eChromaFormatIdc==PIXEL_FORMAT_420  ||
    //           eChromaFormatIdc==PIXEL_FORMAT_422  ||
    //           eChromaFormatIdc==PIXEL_FORMAT_444 );

    if (eChromaFormatIdc!=PIXEL_FORMAT_MONO &&
        eChromaFormatIdc!=PIXEL_FORMAT_411  &&
        eChromaFormatIdc!=PIXEL_FORMAT_420  &&
        eChromaFormatIdc!=PIXEL_FORMAT_422  &&
        eChromaFormatIdc!=PIXEL_FORMAT_444)
    {
        return IMG_PIXFMT_UNDEFINED;
    }

    IMG_ASSERT(ui32BitDepthY>=8 && ui32BitDepthY<=10);   // valid bit depth 8, 9, 10, or 16/0 for 422
    if (eChromaFormatIdc!=PIXEL_FORMAT_MONO)
    {
        IMG_ASSERT(ui32BitDepthC>=8 && ui32BitDepthC<=10);   // valid bit depth 8, 9, 10, or 16/0 for 422
    }

    // valid bit depth 8, 9, 10, or 16/0 for 422
    if (ui32BitDepthY < 8 || ui32BitDepthY > 10)
    {
        return IMG_PIXFMT_UNDEFINED;
    }

    // valid bit depth 8, 9, 10, or 16/0 for 422
    if (ui32BitDepthC < 8 || ui32BitDepthC > 10)
    {
        return IMG_PIXFMT_UNDEFINED;
    }

    key.ePixelFormat = IMG_PIXFMT_UNDEFINED;
    key.eChromaFormatIdc = eChromaFormatIdc;
    key.eChromaInterleaved = eChromaInterleaved;
    key.eMemoryPacking = eMemoryPacking;
    key.ui32BitDepthY = ui32BitDepthY;
    key.ui32BitDepthC = ui32BitDepthC;
    key.ui32NoPlanes = ui32internalNoPlanes;

    //9 and 10 bits formats are handled in the same way, and there is only one entry in the PixelFormat table
    if(key.ui32BitDepthY == 9)
    {
        key.ui32BitDepthY = 10;
    }
    //9 and 10 bits formats are handled in the same way, and there is only one entry in the PixelFormat table
    if(key.ui32BitDepthC == 9)
    {
        key.ui32BitDepthC = 10;
    }

    pixel_InitSearch();

    // do not search by format
    if( (formatFound = pixel_SearchFormat(&key, IMG_FALSE)) == NULL )
    {
        return IMG_PIXFMT_UNDEFINED;
    }

    return formatFound->ePixelFormat;
}

IMGVIDEO_EXPORT_SYMBOL(PIXEL_GetPixelFormat)
static IMG_RESULT pixel_GetInternalPixelInfo(
    PIXEL_sPixelInfo  * psPixelInfo,
    PIXEL_sInfo       * psPixelBufInfo
)
{
    if ((psPixelInfo->ui32BitDepthY == 8) && (psPixelInfo->ui32BitDepthC == 8))
    {
        psPixelBufInfo->ui32PixelsInBOP = 16;
    }
    else if (psPixelInfo->eMemoryPacking == PIXEL_BIT10_MP)
    {
        psPixelBufInfo->ui32PixelsInBOP = 12;
    }
    else
    {
        psPixelBufInfo->ui32PixelsInBOP = 8;
    }

    if (psPixelInfo->ui32BitDepthY == 8)
    {
        psPixelBufInfo->ui32YBytesInBOP = psPixelBufInfo->ui32PixelsInBOP;
    }
    else
    {
        psPixelBufInfo->ui32YBytesInBOP = 16;
    }

    if (psPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_MONO)
    {
        psPixelBufInfo->ui32UVBytesInBOP = 0;
    }
    else if (psPixelInfo->ui32BitDepthC == 8) // For now it considers interleaved, may be modified later if not interleaved
    {
        psPixelBufInfo->ui32UVBytesInBOP = psPixelBufInfo->ui32PixelsInBOP;

        //To support IMG_PIXFMT_YUYV8888 format for 422 upsampling. Maybe need a better solution
        if((psPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_422) && (psPixelInfo->ui32NoPlanes == 1))
        {
            psPixelBufInfo->ui32UVBytesInBOP = 0;
            psPixelBufInfo->ui32PixelsInBOP = 8;
        }
    }
    else
    {
        psPixelBufInfo->ui32UVBytesInBOP = 16;
    }

    if (psPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_444)
    {
        psPixelBufInfo->ui32UVBytesInBOP *= 2;
    }

    if (psPixelInfo->eChromaInterleaved == PIXEL_INVALID_CI) // split UV buffer if not interleaved
    {
        psPixelBufInfo->ui32UVBytesInBOP /= 2;
        psPixelBufInfo->ui32VBytesInBOP = psPixelBufInfo->ui32UVBytesInBOP;
    }
    else
    {
        psPixelBufInfo->ui32VBytesInBOP = 0;
    }

    psPixelBufInfo->ui32AlphaBytesInBOP = 0;

    if (psPixelInfo->ui32NoPlanes == 1)
    {
        psPixelBufInfo->bIsPlanar = IMG_FALSE;
    }
    else
    {
        psPixelBufInfo->bIsPlanar = IMG_TRUE;
    }

    if (psPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_420)
    {
        psPixelBufInfo->bUVHeightHalved = IMG_TRUE;
    }
    else
    {
        psPixelBufInfo->bUVHeightHalved = IMG_FALSE;
    }

    if (psPixelInfo->eChromaFormatIdc == PIXEL_FORMAT_444) // For now it considers interleaved, may be modified later if not interleaved
    {
        psPixelBufInfo->ui32UVStrideRatioTimes4 = 8;
    }
    else
    {
        psPixelBufInfo->ui32UVStrideRatioTimes4 = 4;
    }
    if (psPixelInfo->eChromaInterleaved == PIXEL_INVALID_CI)
    {
        psPixelBufInfo->ui32UVStrideRatioTimes4 /= 2;
    }

    psPixelBufInfo->bHasAlpha = IMG_FALSE;

    return IMG_SUCCESS;
}

static IMG_RESULT pixel_YUVGetDescriptor(
    PIXEL_sInfo        * psInfo,
    IMG_sPixelFormatDesc  * psDesc
)
{
    psDesc->ui32BOPDenom = psInfo->ui32PixelsInBOP;
    psDesc->ui32HDenom = ((psInfo->ui32UVStrideRatioTimes4 == 2) || !psInfo->bIsPlanar) ? 2 : 1;
    psDesc->ui32VDenom = (psInfo->bUVHeightHalved || !psInfo->bIsPlanar) ? 2 : 1;

    psDesc->abPlanes[0] = IMG_TRUE;
    psDesc->aui32BOPNumer[0] = psInfo->ui32YBytesInBOP;
    psDesc->aui32HNumer[0] = psDesc->ui32HDenom;
    psDesc->aui32VNumer[0] = psDesc->ui32VDenom;

    psDesc->abPlanes[1] = psInfo->bIsPlanar;
    psDesc->aui32BOPNumer[1] = psInfo->ui32UVBytesInBOP;
    psDesc->aui32HNumer[1] = (psDesc->ui32HDenom * psInfo->ui32UVStrideRatioTimes4) / 4;
    psDesc->aui32VNumer[1] = 1;

    psDesc->abPlanes[2] = (psInfo->ui32VBytesInBOP > 0) ? IMG_TRUE : IMG_FALSE;
    psDesc->aui32BOPNumer[2] = psInfo->ui32VBytesInBOP;
    psDesc->aui32HNumer[2] = (psInfo->ui32VBytesInBOP > 0) ? 1 : 0;
    psDesc->aui32VNumer[2] = (psInfo->ui32VBytesInBOP > 0) ? 1 : 0;

    psDesc->abPlanes[3] = psInfo->bHasAlpha;
    psDesc->aui32BOPNumer[3] = psInfo->ui32AlphaBytesInBOP;
    psDesc->aui32HNumer[3] = psDesc->ui32HDenom;
    psDesc->aui32VNumer[3] = psDesc->ui32VDenom;

    return IMG_SUCCESS;
}

IMG_RESULT PIXEL_YUVGetDescriptor(
    PIXEL_sPixelInfo        * psPixelInfo,
    IMG_sPixelFormatDesc  * psDesc
)
{
    PIXEL_sInfo  sInfo;
    IMG_UINT32 ui32Result;

// Temp code to validate the internal pixel representation
#if 1
    PIXEL_sInfo * psOldInfo = IMG_NULL;
    IMG_ePixelFormat ePixelFormat = PIXEL_GetPixelFormat(
                    psPixelInfo->eChromaFormatIdc,
                    psPixelInfo->eChromaInterleaved,
                    psPixelInfo->eMemoryPacking,
                    psPixelInfo->ui32BitDepthY,
                    psPixelInfo->ui32BitDepthC,
                    psPixelInfo->ui32NoPlanes);

    // Validate the output from new function.
    if (ePixelFormat != IMG_PIXFMT_UNDEFINED)
    {
        psOldInfo = PIXEL_GetBufferInfoFromPixelColourFormat(ePixelFormat);
    }
#endif

    ui32Result = pixel_GetInternalPixelInfo(psPixelInfo, &sInfo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

#if 1
    if (psOldInfo)
    {
        IMG_ASSERT(psOldInfo->bHasAlpha == sInfo.bHasAlpha);
        IMG_ASSERT(psOldInfo->bIsPlanar == sInfo.bIsPlanar);
        IMG_ASSERT(psOldInfo->bUVHeightHalved == sInfo.bUVHeightHalved);
        IMG_ASSERT(psOldInfo->ui32AlphaBytesInBOP == sInfo.ui32AlphaBytesInBOP);
        IMG_ASSERT(psOldInfo->ui32PixelsInBOP == sInfo.ui32PixelsInBOP);
        IMG_ASSERT(psOldInfo->ui32UVBytesInBOP == sInfo.ui32UVBytesInBOP);
        IMG_ASSERT(psOldInfo->ui32UVStrideRatioTimes4 == sInfo.ui32UVStrideRatioTimes4);
        IMG_ASSERT(psOldInfo->ui32VBytesInBOP == sInfo.ui32VBytesInBOP);
        IMG_ASSERT(psOldInfo->ui32YBytesInBOP == sInfo.ui32YBytesInBOP);
    }
#endif

    ui32Result = pixel_YUVGetDescriptor(&sInfo, psDesc);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    return IMG_SUCCESS;
}

IMGVIDEO_EXPORT_SYMBOL(PIXEL_YUVGetDescriptor)
PIXEL_sPixelInfo * PIXEL_GetPixelInfo(const IMG_ePixelFormat ePixelFormat)
{
    PIXEL_sPixelInfo key;
    PIXEL_sPixelInfo *formatFound = NULL;

    pixel_InitSearch();
    pixel_PixelInfoDefaults(&key);
    key.ePixelFormat = ePixelFormat;

    if(IMG_NULL == (formatFound = pixel_SearchFormat(&key, IMG_TRUE)))
    {
        return pDefaultFormat;
    }

    return formatFound;
}

IMGVIDEO_EXPORT_SYMBOL(PIXEL_GetPixelInfo)
/*****************************************************************************/

PIXEL_sInfo *  PIXEL_GetBufferInfoFromPixelColourFormat    ( IMG_ePixelFormat    ePixelColourFormat )
{
    pixel_sPixelInfoTable *        psPixelInfoTableEntry    = IMG_NULL;

    psPixelInfoTableEntry = pixel_GetPixelInfoFromPixelColourFormat ( ePixelColourFormat );
    IMG_ASSERT ( psPixelInfoTableEntry != IMG_NULL );

    return &(psPixelInfoTableEntry->sInfo);
}

#define FACT_SPEC_FORMAT_NUM_PLANES 4
#define FACT_SPEC_FORMAT_PLANE_UNUSED 0xf
#define FACT_SPEC_FORMAT_PLANE_CODE_BITS 4
#define FACT_SPEC_FORMAT_PLANE_CODE_MASK 3
#define FACT_SPEC_FORMAT_MIN_FACT_VAL 1

IMG_RESULT PIXEL_GetFormatDesc(IMG_ePixelFormat ePixelFormat, IMG_sPixelFormatDesc* psDesc)
{
    if ((ePixelFormat >= IMG_PIXFMT_ARBPLANAR8) &&
        (ePixelFormat <= IMG_PIXFMT_ARBPLANAR8_LAST))
    {
        IMG_UINT32 i;
        IMG_UINT16 ui16Spec;

        psDesc->ui32BOPDenom = 1;
        psDesc->ui32HDenom = 1;
        psDesc->ui32VDenom = 1;

        ui16Spec = (ePixelFormat - IMG_PIXFMT_ARBPLANAR8) & 0xffff;
        for (i=0; i<FACT_SPEC_FORMAT_NUM_PLANES; i++)
        {
            IMG_UINT8 ui8Code = (ui16Spec >> FACT_SPEC_FORMAT_PLANE_CODE_BITS*(FACT_SPEC_FORMAT_NUM_PLANES - 1 - i)) & 0xf;
            psDesc->aui32BOPNumer[i] = 1;
            psDesc->aui32HNumer[i] = ((ui8Code >> 2) & FACT_SPEC_FORMAT_PLANE_CODE_MASK) + FACT_SPEC_FORMAT_MIN_FACT_VAL;
            psDesc->aui32VNumer[i] = (ui8Code & FACT_SPEC_FORMAT_PLANE_CODE_MASK) + FACT_SPEC_FORMAT_MIN_FACT_VAL;
            if ((i == 0) || (ui8Code != FACT_SPEC_FORMAT_PLANE_UNUSED))
            {
                psDesc->abPlanes[i] = IMG_TRUE;
                psDesc->ui32HDenom = psDesc->ui32HDenom > psDesc->aui32HNumer[i] ?
                    psDesc->ui32HDenom : psDesc->aui32HNumer[i];
                psDesc->ui32VDenom = psDesc->ui32VDenom > psDesc->aui32VNumer[i] ?
                    psDesc->ui32VDenom : psDesc->aui32VNumer[i];
            }
            else
            {
                psDesc->abPlanes[i] = IMG_FALSE;
            }
        }
    }
    else
    {
        PIXEL_sInfo* psInfo = PIXEL_GetBufferInfoFromPixelColourFormat(ePixelFormat);
        pixel_YUVGetDescriptor(psInfo, psDesc);
    }

    return IMG_SUCCESS;
}

IMGVIDEO_EXPORT_SYMBOL(PIXEL_GetFormatDesc)
IMG_RESULT PIXEL_GenPixFormat(IMG_ePixelFormat *pePixelFormat, IMG_sPixelFormatDesc* psFormatDesc)
{
    IMG_UINT16 ui16Spec = 0, ui16i;
    IMG_UINT8 ui8Code;

    for (ui16i = 0; ui16i < FACT_SPEC_FORMAT_NUM_PLANES; ui16i++)
    {
        if (psFormatDesc->abPlanes[ui16i] != IMG_TRUE)
        {
            ui8Code = FACT_SPEC_FORMAT_PLANE_UNUSED;
        }
        else
        {
            ui8Code = (((psFormatDesc->aui32HNumer[ui16i] - FACT_SPEC_FORMAT_MIN_FACT_VAL) & FACT_SPEC_FORMAT_PLANE_CODE_MASK) << 2) |
                ((psFormatDesc->aui32VNumer[ui16i] - FACT_SPEC_FORMAT_MIN_FACT_VAL) & FACT_SPEC_FORMAT_PLANE_CODE_MASK);
        }
        ui16Spec |= (ui8Code << FACT_SPEC_FORMAT_PLANE_CODE_BITS*(FACT_SPEC_FORMAT_NUM_PLANES - 1 - ui16i));
    }

    *pePixelFormat = IMG_PIXFMT_ARBPLANAR8 | ui16Spec;

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(PIXEL_GenPixFormat)



static PIXEL_sInfo *
pixel_GetPixel(
    PIXEL_sGetSetCB   * psGetSetCB,
    IMG_UINT32          ui32X,
    IMG_UINT32          ui32Y
)
{
    PIXEL_sInfo   * psBufInfo = IMG_NULL;
    IMG_UINT32      u32UvY;
    IMG_UINT32      ui32UvImageStride;

    // Not checking psGetSetCB because it should have been validated by the external-facing functions

    PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat, psBufInfo);
    IMG_ASSERT(psBufInfo);
    if (psBufInfo == IMG_NULL)
    {
        goto error;
    }

    /**** NOTE API is deliberately not serially re-entrant due to performance */

    /* Check x and y are valid */
    IMG_ASSERT(ui32X < psGetSetCB->ui32ImageWidth);
    IMG_ASSERT(ui32Y < psGetSetCB->ui32ImageHeight);

    IMG_ASSERT(psBufInfo->ui32PixelsInBOP <= PIXEL_MAX_YUV_COMPONENTS);

    /* Copy user settings into internal storage */
    psGetSetCB->pvYBufAddr = psGetSetCB->pvYBufBaseAddr;
    psGetSetCB->pvUVBufAddr = psGetSetCB->pvUVBufBaseAddr;
    psGetSetCB->pvVBufAddr = psGetSetCB->pvVBufBaseAddr;
    psGetSetCB->pvAlphaBufAddr = psGetSetCB->pvAlphaBufBaseAddr;
    psGetSetCB->ui32InternalImageHeight = psGetSetCB->ui32ImageHeight;
    psGetSetCB->ui32InternalYImageStride = psGetSetCB->ui32YImageStride;
    psGetSetCB->ui32BufPixelNo = ui32X - (ui32X % psBufInfo->ui32PixelsInBOP);
    psGetSetCB->ui32BufLineNo = ui32Y + 1;

    /* Initialise Y buffer address */
    psGetSetCB->pvYBufAddr = psGetSetCB->pvYBufAddr + (ui32Y * psGetSetCB->ui32InternalYImageStride);
    psGetSetCB->pvYBufAddr += ((ui32X / psBufInfo->ui32PixelsInBOP) * psBufInfo->ui32YBytesInBOP);

    /* If half height...*/
    if (psBufInfo->bUVHeightHalved)
    {
        u32UvY = ui32Y / 2;
    }
    else
    {
        u32UvY = ui32Y;
    }

    /* If half stride...*/
    /*if (psBufInfo->bUVStrideHalved)
    {
        ui32UvImageStride = psGetSetCB->ui32InternalYImageStride / 2;
    }
    else
    {
        ui32UvImageStride = psGetSetCB->ui32InternalYImageStride;
    }*/
    ui32UvImageStride = (psGetSetCB->ui32InternalYImageStride * psBufInfo->ui32UVStrideRatioTimes4) / 4;

    /* If planar...*/
    if (psBufInfo->bIsPlanar)
    {
        /* Calculate the initialise UV address...*/
        psGetSetCB->pvUVBufAddr = psGetSetCB->pvUVBufAddr + ( u32UvY * ui32UvImageStride );
        psGetSetCB->pvUVBufAddr += ((ui32X / psBufInfo->ui32PixelsInBOP) * psBufInfo->ui32UVBytesInBOP);

        /* If separate V, calculate initialise V address...*/
        if ( psGetSetCB->pvVBufAddr != IMG_NULL )
        {
            psGetSetCB->pvVBufAddr = psGetSetCB->pvVBufAddr + ( u32UvY * ui32UvImageStride );
            psGetSetCB->pvVBufAddr += ((ui32X / psBufInfo->ui32PixelsInBOP) * psBufInfo->ui32UVBytesInBOP);
        }
    }

    /* Initialise Alpha buffer address for planar alpha formats */
    if ( psBufInfo->bHasAlpha )
    {
        psGetSetCB->pvAlphaBufAddr = psGetSetCB->pvAlphaBufAddr + (ui32Y * psGetSetCB->ui32InternalYImageStride);
        psGetSetCB->pvAlphaBufAddr += ((ui32X / psBufInfo->ui32PixelsInBOP) * psBufInfo->ui32AlphaBytesInBOP);
    }

error:
    return psBufInfo;
}


IMG_RESULT  PIXEL_GetPixel(
    PIXEL_sGetSetCB   * psGetSetCB,
    IMG_UINT32          ui32X,
    IMG_UINT32          ui32Y,
    IMG_UINT32        * pui32YorR,
    IMG_UINT32        * pui32UorG,
    IMG_UINT32        * pui32VorB,
    IMG_UINT32        * pui32Alpha
)
{
    PIXEL_sInfo   * psBufInfo;
    IMG_UINT32      ui32Result;

    IMG_ASSERT(psGetSetCB);
    IMG_ASSERT(pui32YorR);
    IMG_ASSERT(pui32UorG);
    IMG_ASSERT(pui32VorB);
    IMG_ASSERT(pui32Alpha);
    if (psGetSetCB == IMG_NULL ||
        pui32YorR == IMG_NULL ||
        pui32UorG == IMG_NULL ||
        pui32VorB == IMG_NULL ||
        pui32Alpha == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    psBufInfo = pixel_GetPixel(psGetSetCB, ui32X, ui32Y);
    IMG_ASSERT(psBufInfo);
    if (psBufInfo == IMG_NULL)
    {
        ui32Result = IMG_ERROR_GENERIC_FAILURE;
        goto error;
    }

    /* De-block the block-of-pixels */
    pixel_DeblockNextBOPs(psGetSetCB);

    /* Return the pixel YUV and Alpha */
    psGetSetCB->ui32PixelIndex = (ui32X % psBufInfo->ui32PixelsInBOP);
    *pui32YorR = psGetSetCB->ui32Y[psGetSetCB->ui32PixelIndex];
    *pui32UorG = psGetSetCB->ui32U[psGetSetCB->ui32PixelIndex];
    *pui32VorB = psGetSetCB->ui32V[psGetSetCB->ui32PixelIndex];
    *pui32Alpha = psGetSetCB->ui32Alpha[psGetSetCB->ui32PixelIndex];

    /* Return success */
    return IMG_SUCCESS;

error:
    return ui32Result;
}

IMG_UINT32 PIXEL_GetPixelGroup(
    PIXEL_sGetSetCB   * psGetSetCB,
    IMG_UINT32          ui32X,
    IMG_UINT32          ui32Y,
    IMG_UINT32        * pui32YorR,
    IMG_UINT32        * pui32UorG,
    IMG_UINT32        * pui32VorB,
    IMG_UINT32        * pui32Alpha,
    IMG_UINT32          ui32MaxPixels
)
{
    PIXEL_sInfo   * psBufInfo;
    IMG_UINT32      ui32PixelCount = 0;
    IMG_UINT32      ui32Result;

    IMG_ASSERT(psGetSetCB);
    IMG_ASSERT(pui32YorR);
    IMG_ASSERT(pui32UorG);
    IMG_ASSERT(pui32VorB);
    IMG_ASSERT(pui32Alpha);
    if (psGetSetCB == IMG_NULL ||
        pui32YorR == IMG_NULL ||
        pui32UorG == IMG_NULL ||
        pui32VorB == IMG_NULL ||
        pui32Alpha == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    psBufInfo = pixel_GetPixel(psGetSetCB, ui32X, ui32Y);
    IMG_ASSERT(psBufInfo);
    if (psBufInfo == IMG_NULL)
    {
        ui32Result = IMG_ERROR_GENERIC_FAILURE;
        goto error;
    }

    /* De-block the block-of-pixels */
    pixel_DeblockNextBOPs(psGetSetCB);

    /* Return the pixel YUV and Alpha */
    psGetSetCB->ui32PixelIndex = (ui32X % psBufInfo->ui32PixelsInBOP);
    while (
                (psGetSetCB->ui32PixelIndex < psBufInfo->ui32PixelsInBOP) &&
                (psGetSetCB->ui32PixelIndex < ui32MaxPixels)
                )
    {
        pui32YorR[ui32PixelCount]      = psGetSetCB->ui32Y[psGetSetCB->ui32PixelIndex];
        pui32UorG[ui32PixelCount]      = psGetSetCB->ui32U[psGetSetCB->ui32PixelIndex];
        pui32VorB[ui32PixelCount]      = psGetSetCB->ui32V[psGetSetCB->ui32PixelIndex];
        pui32Alpha[ui32PixelCount++]   = psGetSetCB->ui32Alpha[psGetSetCB->ui32PixelIndex++];
    }

error:
    return ui32PixelCount;
}


IMG_RESULT  PIXEL_GetFirstPixel(
    PIXEL_sGetSetCB   * psGetSetCB,
    IMG_UINT32        * pui32Y,
    IMG_UINT32        * pui32U,
    IMG_UINT32        * pui32V,
    IMG_UINT32        * pui32Alpha
)
{
    PIXEL_sInfo   * psBufInfo = IMG_NULL;
    IMG_UINT32      ui32Result;

    IMG_ASSERT(psGetSetCB);
    IMG_ASSERT(pui32Y);
    IMG_ASSERT(pui32U);
    IMG_ASSERT(pui32V);
    IMG_ASSERT(pui32Alpha);
    if (psGetSetCB == IMG_NULL ||
        pui32Y == IMG_NULL ||
        pui32U == IMG_NULL ||
        pui32V == IMG_NULL ||
        pui32Alpha == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat, psBufInfo);
    IMG_ASSERT(psBufInfo);
    if (psBufInfo == IMG_NULL)
    {
        ui32Result = IMG_ERROR_GENERIC_FAILURE;
        goto error;
    }

    /**** NOTE API is deliberately not serially re-entrant due to performance */

    IMG_ASSERT(psBufInfo->ui32PixelsInBOP <= PIXEL_MAX_YUV_COMPONENTS);

    /* Copy user settings into internal storage */
    psGetSetCB->pvYBufAddr = psGetSetCB->pvYBufBaseAddr;
    psGetSetCB->pvUVBufAddr = psGetSetCB->pvUVBufBaseAddr;
    psGetSetCB->pvVBufAddr = psGetSetCB->pvVBufBaseAddr;
    psGetSetCB->pvAlphaBufAddr = psGetSetCB->pvAlphaBufBaseAddr;
    psGetSetCB->ui32InternalImageHeight = psGetSetCB->ui32ImageHeight;
    psGetSetCB->ui32InternalYImageStride = psGetSetCB->ui32YImageStride;

    if (psGetSetCB->eMode == PIXEL_MODE_FIELD_1)
    {
        psGetSetCB->pvYBufAddr += psGetSetCB->ui32InternalYImageStride;
        psGetSetCB->pvUVBufAddr += PIXEL_GET_UV_STRIDE(psGetSetCB);
        if (psGetSetCB->pvVBufAddr != IMG_NULL)
        {
            psGetSetCB->pvVBufAddr += PIXEL_GET_UV_STRIDE(psGetSetCB);
        }
        psGetSetCB->pvAlphaBufAddr += psGetSetCB->ui32InternalYImageStride;
    }
    psGetSetCB->pvLineYBufAddr = psGetSetCB->pvYBufAddr;
    psGetSetCB->pvLineUVBufAddr = psGetSetCB->pvUVBufAddr;
    psGetSetCB->pvLineVBufAddr = psGetSetCB->pvVBufAddr;
    psGetSetCB->pvLineAlphaBufAddr = psGetSetCB->pvAlphaBufAddr;

    if (
        (psGetSetCB->eMode == PIXEL_MODE_FIELD_0) ||
        (psGetSetCB->eMode == PIXEL_MODE_FIELD_1)
        )
    {
        psGetSetCB->ui32InternalYImageStride <<= 1;
        psGetSetCB->ui32InternalImageHeight >>= 1;
    }
    psGetSetCB->ui32BufPixelNo = 0;
    psGetSetCB->ui32BufLineNo = 1;
    psGetSetCB->bEndOfImageHit = IMG_FALSE;

    /* De-block the first block-of-pixels */
    pixel_DeblockNextBOPs(psGetSetCB);

    /* Return the first pixel YUV and Alpha */
    *pui32Y = psGetSetCB->ui32Y[psGetSetCB->ui32PixelIndex];
    *pui32U = psGetSetCB->ui32U[psGetSetCB->ui32PixelIndex];
    *pui32V = psGetSetCB->ui32V[psGetSetCB->ui32PixelIndex];
    *pui32Alpha = psGetSetCB->ui32Alpha[psGetSetCB->ui32PixelIndex];

    /* Update the index and no of pixels...*/
    psGetSetCB->ui32PixelIndex++;
    psGetSetCB->ui32BufPixelNo++;

    /* Return success */
    return IMG_SUCCESS;

error:
    return ui32Result;
}


IMG_RESULT  PIXEL_GetNextPixel(
    PIXEL_sGetSetCB   * psGetSetCB,
    IMG_UINT32        * pui32Y,
    IMG_UINT32        * pui32U,
    IMG_UINT32        * pui32V,
    IMG_UINT32        * pui32Alpha
)
{
    PIXEL_sInfo   * psBufInfo = IMG_NULL;
    IMG_UINT32      ui32Result;

    IMG_ASSERT(psGetSetCB);
    IMG_ASSERT(pui32Y);
    IMG_ASSERT(pui32U);
    IMG_ASSERT(pui32V);
    IMG_ASSERT(pui32Alpha);
    if (psGetSetCB == IMG_NULL ||
        pui32Y == IMG_NULL ||
        pui32U == IMG_NULL ||
        pui32V == IMG_NULL ||
        pui32Alpha == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat, psBufInfo);
    IMG_ASSERT(psBufInfo);
    if (psBufInfo == IMG_NULL)
    {
        ui32Result = IMG_ERROR_GENERIC_FAILURE;
        goto error;
    }

    /**** NOTE API is deliberately not serially re-entrant due to performance */

    /* If we have reached the end of this line...*/
    if (psGetSetCB->ui32BufPixelNo >= psGetSetCB->ui32ImageWidth)
    {
        /* If we have not reached the end of the image...*/
        if (psGetSetCB->ui32BufLineNo < psGetSetCB->ui32InternalImageHeight)
        {
            /* Move to the next line...*/
            psGetSetCB->pvYBufAddr      = psGetSetCB->pvLineYBufAddr + psGetSetCB->ui32InternalYImageStride;
            psGetSetCB->pvLineYBufAddr  = psGetSetCB->pvYBufAddr;

            /* For planar formats where the UV height is half the Y height... */
            if ( psBufInfo->bIsPlanar && psBufInfo->bUVHeightHalved )
            {
                if ( psGetSetCB->ui32BufLineNo & 0x0001 )
                {
                    /* If the new line number is odd, replicate previous line's UV data */
                    psGetSetCB->pvUVBufAddr = psGetSetCB->pvLineUVBufAddr;
                    if (psGetSetCB->pvVBufAddr != IMG_NULL)
                    {
                        psGetSetCB->pvVBufAddr = psGetSetCB->pvLineVBufAddr;
                    }
                }

                else
                {
                    /* If the new line number is even, move to next UV line */
                    psGetSetCB->pvUVBufAddr     =   psGetSetCB->pvLineUVBufAddr + PIXEL_GET_UV_STRIDE(psGetSetCB);
                    psGetSetCB->pvLineUVBufAddr =   psGetSetCB->pvUVBufAddr;
                    if (psGetSetCB->pvVBufAddr != IMG_NULL)
                    {
                        psGetSetCB->pvVBufAddr     =   psGetSetCB->pvLineVBufAddr + PIXEL_GET_UV_STRIDE(psGetSetCB);
                        psGetSetCB->pvLineVBufAddr =   psGetSetCB->pvVBufAddr;
                    }
                }
            }
            /* For planar formats where the UV height is the same as the Y height... */
            else if ( psBufInfo->bIsPlanar )
            {
                psGetSetCB->pvUVBufAddr     = psGetSetCB->pvLineUVBufAddr + PIXEL_GET_UV_STRIDE(psGetSetCB);
                psGetSetCB->pvLineUVBufAddr = psGetSetCB->pvUVBufAddr;
                if (psGetSetCB->pvVBufAddr != IMG_NULL)
                {
                    psGetSetCB->pvVBufAddr     = psGetSetCB->pvLineVBufAddr + PIXEL_GET_UV_STRIDE(psGetSetCB);
                    psGetSetCB->pvLineVBufAddr = psGetSetCB->pvVBufAddr;
                }
            }

            /* For alpha planar formats */
            if ( psBufInfo->bHasAlpha )
            {
                psGetSetCB->pvAlphaBufAddr      = psGetSetCB->pvLineAlphaBufAddr + psGetSetCB->ui32InternalYImageStride;
                psGetSetCB->pvLineAlphaBufAddr  = psGetSetCB->pvAlphaBufAddr;
            }

            psGetSetCB->ui32BufPixelNo  = 0;
            psGetSetCB->ui32BufLineNo++;

            /* De-block the next block-of-pixels */
            pixel_DeblockNextBOPs(psGetSetCB);
        }
        else
        {
            if ( psGetSetCB->bEndOfImageHit == IMG_FALSE )
            {
                /* A single read beyond the end of the image will prompt a non 'IMG_SUCCESS' return value */
                psGetSetCB->bEndOfImageHit = IMG_TRUE;
                return PIXEL_END_OF_IMAGE_REACHED;
            }
            else
            {
                /* Any more than a single read beyond the end of the image will cause an assert */
                IMG_ASSERT(IMG_FALSE);
            }
        }
    }
    /* If we have reached the end of the block-of-pixels...*/
    else if (psGetSetCB->ui32PixelIndex >= psBufInfo->ui32PixelsInBOP)
    {
        /* De-block the next block-of-pixels */
        pixel_DeblockNextBOPs(psGetSetCB);
    }

    /* Return the next pixel YUV and Alpha*/
    *pui32Y = psGetSetCB->ui32Y[psGetSetCB->ui32PixelIndex];
    *pui32U = psGetSetCB->ui32U[psGetSetCB->ui32PixelIndex];
    *pui32V = psGetSetCB->ui32V[psGetSetCB->ui32PixelIndex];
    *pui32Alpha = psGetSetCB->ui32Alpha[psGetSetCB->ui32PixelIndex];

    /* Update the index and no of pixels...*/
    psGetSetCB->ui32PixelIndex++;
    psGetSetCB->ui32BufPixelNo++;

    /* Return success */
    return IMG_SUCCESS;

error:
    return ui32Result;
}


IMG_RESULT
PIXEL_GetEnd(
    PIXEL_sGetSetCB   * psGetSetCB
)
{
    /* This function is included for reasons of symmetry    */
    /* ('SETEnd' is required, so the user could validly        */
    /* expect to have to call 'GETEnd' as well).            */

    return IMG_SUCCESS;
}


IMG_RESULT  PIXEL_SetPixel(
    PIXEL_sGetSetCB   * psGetSetCB,
    IMG_UINT32          ui32X,
    IMG_UINT32          ui32Y,
    IMG_UINT32          ui32YorR,
    IMG_UINT32          ui32UorG,
    IMG_UINT32          ui32VorB,
    IMG_UINT32          ui32Alpha
)
{
    PIXEL_sInfo   * psBufInfo;
    IMG_VOID      * pvYBufAddr;
    IMG_VOID      * pvUVBufAddr;
    IMG_VOID      * pvVBufAddr;
    IMG_VOID      * pvAlphaBufAddr;
    IMG_UINT32      ui32Result;

    IMG_ASSERT(psGetSetCB);
    if (psGetSetCB == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    psBufInfo = pixel_GetPixel(psGetSetCB, ui32X, ui32Y);
    IMG_ASSERT(psBufInfo);
    if (psBufInfo == IMG_NULL)
    {
        ui32Result = IMG_ERROR_GENERIC_FAILURE;
        goto error;
    }

    /* Save the addresses...*/
    pvYBufAddr      = psGetSetCB->pvYBufAddr;
    pvUVBufAddr     = psGetSetCB->pvUVBufAddr;
    pvVBufAddr      = psGetSetCB->pvVBufAddr;
    pvAlphaBufAddr  = psGetSetCB->pvAlphaBufAddr;

    /* De-block the block-of-pixels */
    pixel_DeblockNextBOPs(psGetSetCB);

    /* Return the pixel YUV and Alpha */
    psGetSetCB->ui32PixelIndex = (ui32X % psBufInfo->ui32PixelsInBOP);
    psGetSetCB->ui32Y[psGetSetCB->ui32PixelIndex] = ui32YorR;
    psGetSetCB->ui32U[psGetSetCB->ui32PixelIndex] = ui32UorG;
    psGetSetCB->ui32V[psGetSetCB->ui32PixelIndex] = ui32VorB;
    psGetSetCB->ui32Alpha[psGetSetCB->ui32PixelIndex] = ui32Alpha;

    /* Restore the addresses */
    psGetSetCB->pvYBufAddr      = pvYBufAddr;
    psGetSetCB->pvUVBufAddr     = pvUVBufAddr;
    psGetSetCB->pvVBufAddr      = pvVBufAddr;
    psGetSetCB->pvAlphaBufAddr  = pvAlphaBufAddr;

    /* Block the block-of-pixels */
    pixel_BlockNextBOPs(psGetSetCB);

    /* Return success */
    return IMG_SUCCESS;

error:
    return ui32Result;
}


IMG_UINT32 PIXEL_SetPixelGroup(
    PIXEL_sGetSetCB   * psGetSetCB,
    IMG_UINT32          ui32X,
    IMG_UINT32          ui32Y,
    IMG_UINT32        * pui32YorR,
    IMG_UINT32        * pui32UorG,
    IMG_UINT32        * pui32VorB,
    IMG_UINT32        * pui32Alpha,
    IMG_UINT32          ui32MaxPixels
)
{
    PIXEL_sInfo   * psBufInfo;
    IMG_VOID      * pvYBufAddr;
    IMG_VOID      * pvUVBufAddr;
    IMG_VOID      * pvVBufAddr;
    IMG_VOID      * pvAlphaBufAddr;
    IMG_UINT32      ui32PixelCount = 0;
    IMG_UINT32      ui32Result;

    IMG_ASSERT(psGetSetCB);
    IMG_ASSERT(pui32YorR);
    IMG_ASSERT(pui32UorG);
    IMG_ASSERT(pui32VorB);
    IMG_ASSERT(pui32Alpha);
    if (psGetSetCB == IMG_NULL ||
        pui32YorR == IMG_NULL ||
        pui32UorG == IMG_NULL ||
        pui32VorB == IMG_NULL ||
        pui32Alpha == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    psBufInfo = pixel_GetPixel(psGetSetCB, ui32X, ui32Y);
    IMG_ASSERT(psBufInfo);
    if (psBufInfo == IMG_NULL)
    {
        ui32Result = IMG_ERROR_GENERIC_FAILURE;
        goto error;
    }

    /* Save the addresses...*/
    pvYBufAddr      = psGetSetCB->pvYBufAddr;
    pvUVBufAddr     = psGetSetCB->pvUVBufAddr;
    pvVBufAddr      = psGetSetCB->pvVBufAddr;
    pvAlphaBufAddr  = psGetSetCB->pvAlphaBufAddr;

    /* De-block the block-of-pixels */
    pixel_DeblockNextBOPs(psGetSetCB);

    /* Return the pixel YUV and Alpha */
    psGetSetCB->ui32PixelIndex = (ui32X % psBufInfo->ui32PixelsInBOP);
    while (
                (psGetSetCB->ui32PixelIndex < psBufInfo->ui32PixelsInBOP) &&
                (psGetSetCB->ui32PixelIndex < ui32MaxPixels)
                )
    {
        psGetSetCB->ui32Y[psGetSetCB->ui32PixelIndex]       = pui32YorR[ui32PixelCount];
        psGetSetCB->ui32U[psGetSetCB->ui32PixelIndex]       = pui32UorG[ui32PixelCount];
        psGetSetCB->ui32V[psGetSetCB->ui32PixelIndex]       = pui32VorB[ui32PixelCount];
        psGetSetCB->ui32Alpha[psGetSetCB->ui32PixelIndex++] = pui32Alpha[ui32PixelCount++];
    }

    /* Restore the addresses */
    psGetSetCB->pvYBufAddr      = pvYBufAddr;
    psGetSetCB->pvUVBufAddr     = pvUVBufAddr;
    psGetSetCB->pvVBufAddr      = pvVBufAddr;
    psGetSetCB->pvAlphaBufAddr  = pvAlphaBufAddr;

    /* Block the block-of-pixels */
    pixel_BlockNextBOPs(psGetSetCB);

error:
    return ui32PixelCount;
}


IMG_RESULT  PIXEL_SetFirstPixel(
    PIXEL_sGetSetCB   * psGetSetCB,
    IMG_UINT32          ui32Y,
    IMG_UINT32          ui32U,
    IMG_UINT32          ui32V,
    IMG_UINT32          ui32Alpha
)
{
    PIXEL_sInfo   * psBufInfo = IMG_NULL;
    IMG_UINT32      ui32Result;

    IMG_ASSERT(psGetSetCB);
    if (psGetSetCB == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat, psBufInfo);
    IMG_ASSERT(psBufInfo);
    if (psBufInfo == IMG_NULL)
    {
        ui32Result = IMG_ERROR_GENERIC_FAILURE;
        goto error;
    }

    IMG_ASSERT(psBufInfo->ui32PixelsInBOP <= PIXEL_MAX_YUV_COMPONENTS);

    /* Copy user settings into internal storage */
    psGetSetCB->pvYBufAddr = psGetSetCB->pvYBufBaseAddr;
    psGetSetCB->pvUVBufAddr = psGetSetCB->pvUVBufBaseAddr;
    psGetSetCB->pvVBufAddr = psGetSetCB->pvVBufBaseAddr;
    psGetSetCB->pvAlphaBufAddr = psGetSetCB->pvAlphaBufBaseAddr;
    psGetSetCB->ui32InternalImageHeight = psGetSetCB->ui32ImageHeight;
    psGetSetCB->ui32InternalYImageStride = psGetSetCB->ui32YImageStride;

    if (psGetSetCB->eMode == PIXEL_MODE_FIELD_1)
    {
        psGetSetCB->pvYBufAddr += psGetSetCB->ui32InternalYImageStride;
        psGetSetCB->pvUVBufAddr += PIXEL_GET_UV_STRIDE(psGetSetCB);
        if (psGetSetCB->pvVBufAddr != IMG_NULL)
        {
            psGetSetCB->pvVBufAddr += PIXEL_GET_UV_STRIDE(psGetSetCB);
        }
        psGetSetCB->pvAlphaBufAddr += psGetSetCB->ui32InternalYImageStride;
    }
    psGetSetCB->pvLineYBufAddr = psGetSetCB->pvYBufAddr;
    psGetSetCB->pvLineUVBufAddr = psGetSetCB->pvUVBufAddr;
    if (psGetSetCB->pvVBufAddr != IMG_NULL)
    {
        psGetSetCB->pvLineVBufAddr = psGetSetCB->pvVBufAddr;
    }
    psGetSetCB->pvLineAlphaBufAddr = psGetSetCB->pvAlphaBufAddr;

    if (
        (psGetSetCB->eMode == PIXEL_MODE_FIELD_0) ||
        (psGetSetCB->eMode == PIXEL_MODE_FIELD_1)
        )
    {
        psGetSetCB->ui32InternalYImageStride <<= 1;
        psGetSetCB->ui32InternalImageHeight >>= 1;
    }
    psGetSetCB->ui32BufPixelNo = 0;
    psGetSetCB->ui32BufLineNo = 1;
    psGetSetCB->ui32PixelIndex = 0;
    psGetSetCB->bEndOfImageHit = IMG_FALSE;

    /* Save the first pixel YUV and Alpha */
    psGetSetCB->ui32Y[psGetSetCB->ui32PixelIndex] = ui32Y;
    psGetSetCB->ui32U[psGetSetCB->ui32PixelIndex] = ui32U;
    psGetSetCB->ui32V[psGetSetCB->ui32PixelIndex] = ui32V;
    psGetSetCB->ui32Alpha[psGetSetCB->ui32PixelIndex] = ui32Alpha;

    /* Update the index and no of pixels...*/
    psGetSetCB->ui32PixelIndex++;
    psGetSetCB->ui32BufPixelNo++;

    /* Return success */
    return IMG_SUCCESS;

error:
    return ui32Result;
}


IMG_RESULT  PIXEL_SetNextPixel(
    PIXEL_sGetSetCB   * psGetSetCB,
    IMG_UINT32          ui32Y,
    IMG_UINT32          ui32U,
    IMG_UINT32          ui32V,
    IMG_UINT32          ui32Alpha
)
{
    PIXEL_sInfo   * psBufInfo = IMG_NULL;
    IMG_UINT32      ui32Result;

    IMG_ASSERT(psGetSetCB);
    if (psGetSetCB == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat, psBufInfo);
    IMG_ASSERT(psBufInfo);
    if (psBufInfo == IMG_NULL)
    {
        ui32Result = IMG_ERROR_GENERIC_FAILURE;
        goto error;
    }

    /**** NOTE API is deliberately not serially re-entrant due to performance */

    /* If we have reached the end of this line...*/
    if (psGetSetCB->ui32BufPixelNo >= psGetSetCB->ui32ImageWidth)
    {
        /* If we have not reached the end of the image...*/
        if (psGetSetCB->ui32BufLineNo < psGetSetCB->ui32InternalImageHeight)
        {
            /* Block the next block-of-pixels */
            pixel_BlockNextBOPs(psGetSetCB);

            /* Move to the next line...*/
            psGetSetCB->pvYBufAddr      = psGetSetCB->pvLineYBufAddr + psGetSetCB->ui32InternalYImageStride;
            psGetSetCB->pvLineYBufAddr  = psGetSetCB->pvYBufAddr;

            /* If we're using a planar format and the UV height is half the Y height... */
            if ( psBufInfo->bUVHeightHalved == IMG_TRUE)
            {
                if ( psGetSetCB->ui32BufLineNo & 0x0001 )
                {
                    /* If the new line number is odd, replicate previous line's UV data */
                    psGetSetCB->pvUVBufAddr     =   psGetSetCB->pvLineUVBufAddr;
                    if (psGetSetCB->pvVBufAddr != IMG_NULL)
                    {
                         psGetSetCB->pvVBufAddr     =   psGetSetCB->pvLineVBufAddr;
                    }
                }
                else
                {
                    /* If the new line number is even, move to next UV line */
                    psGetSetCB->pvUVBufAddr     =   psGetSetCB->pvLineUVBufAddr + PIXEL_GET_UV_STRIDE(psGetSetCB);
                    psGetSetCB->pvLineUVBufAddr =   psGetSetCB->pvUVBufAddr;
                    if (psGetSetCB->pvVBufAddr != IMG_NULL)
                    {
                        psGetSetCB->pvVBufAddr     =   psGetSetCB->pvLineVBufAddr + PIXEL_GET_UV_STRIDE(psGetSetCB);
                        psGetSetCB->pvLineVBufAddr =   psGetSetCB->pvVBufAddr;
                    }
                }
            }
            else if ( psBufInfo->bIsPlanar )
            {
                psGetSetCB->pvUVBufAddr     = psGetSetCB->pvLineUVBufAddr + PIXEL_GET_UV_STRIDE(psGetSetCB);
                psGetSetCB->pvLineUVBufAddr = psGetSetCB->pvUVBufAddr;
                if (psGetSetCB->pvVBufAddr != IMG_NULL)
                {
                    psGetSetCB->pvVBufAddr     = psGetSetCB->pvLineVBufAddr + PIXEL_GET_UV_STRIDE(psGetSetCB);
                    psGetSetCB->pvLineVBufAddr = psGetSetCB->pvVBufAddr;
                }
            }

            /* For alpha planar formats */
            if ( psBufInfo->bHasAlpha )
            {
                psGetSetCB->pvAlphaBufAddr      = psGetSetCB->pvLineAlphaBufAddr + psGetSetCB->ui32InternalYImageStride;
                psGetSetCB->pvLineAlphaBufAddr  = psGetSetCB->pvAlphaBufAddr;
            }

            psGetSetCB->ui32BufPixelNo  = 0;
            psGetSetCB->ui32BufLineNo++;
            psGetSetCB->ui32PixelIndex  = 0;
        }
        else
        {
            if ( psGetSetCB->bEndOfImageHit == IMG_FALSE )
            {
                /* A single read beyond the end of the image will prompt a non 'IMG_SUCCESS' return value */
                psGetSetCB->bEndOfImageHit = IMG_TRUE;
                return PIXEL_END_OF_IMAGE_REACHED;
            }
            else
            {
                /* Any more than a single read beyond the end of the image will cause an assert */
                IMG_ASSERT(IMG_FALSE);
            }
        }
    }
    /* If we have reached the end of the block-of-pixels...*/
    else if (psGetSetCB->ui32PixelIndex >= psBufInfo->ui32PixelsInBOP)
    {
        /* Block the next block-of-pixels */
        pixel_BlockNextBOPs(psGetSetCB);
    }

    /* Save the next pixel YUV and Alpha */
    psGetSetCB->ui32Y[psGetSetCB->ui32PixelIndex] = ui32Y;
    psGetSetCB->ui32U[psGetSetCB->ui32PixelIndex] = ui32U;
    psGetSetCB->ui32V[psGetSetCB->ui32PixelIndex] = ui32V;
    psGetSetCB->ui32Alpha[psGetSetCB->ui32PixelIndex] = ui32Alpha;

    /* Update the index and no of pixels...*/
    psGetSetCB->ui32PixelIndex++;
    psGetSetCB->ui32BufPixelNo++;

    /* Return success */
    return IMG_SUCCESS;

error:
    return ui32Result;
}


IMG_RESULT  PIXEL_SetEnd(
    PIXEL_sGetSetCB   * psGetSetCB
)
{
    IMG_UINT32  ui32Result;

    /**** NOTE API is deliberately not serially re-enterant due to performance */

    IMG_ASSERT(psGetSetCB);
    if (psGetSetCB == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    /* If there are pixels to block...*/
    if (psGetSetCB->ui32BufPixelNo != 0)
    {
        /* Block the next block-of-pixels */
        pixel_BlockNextBOPs(psGetSetCB);
    }

    return IMG_SUCCESS;

error:
    return ui32Result;
}
