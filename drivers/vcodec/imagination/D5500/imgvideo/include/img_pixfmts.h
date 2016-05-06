/*!
 *****************************************************************************
 *
 * @File       img_pixfmts.h
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

#ifndef __IMG_PIXFMTS__
#define __IMG_PIXFMTS__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Old pixel format definition
 *
 * @note These definitions are different in HW documentation (current to HW doc):
 * @li PL8 is defined as PL111
 * @li PL12 is sometime used wrongly for monochrome formats instead of PL_Y
 * 
 */
typedef enum
{
	    IMG_PIXFMT_CLUT1        =   0,              //!< 1-bit palettised.
        IMG_PIXFMT_CLUT2        =   1,              //!< 2-bit palettised.
        IMG_PIXFMT_CLUT4        =   2,              //!< 4-bit palettised.
        IMG_PIXFMT_I4A4         =   3,				//!< 4-bit palettised + 4-bit alpha.
        IMG_PIXFMT_I8A8         =   4,				//!< 8-bit palettised + 8-bit alpha.
	    IMG_PIXFMT_A8I8         =   51,				//!< 8-bit palettised + 8-bit alpha.    
	    IMG_PIXFMT_RGB8         =   5,              //!< 8-bit palettised.
        IMG_PIXFMT_RGB332       =   6,              //!< 8-bit RGB (R=3, G=3, B=2).
        IMG_PIXFMT_RGB555       =   7,              //!< 15-bit RGB (R=5, G=5, B=5).
        IMG_PIXFMT_ARGB4444     =   8,              //!< 16-bit RGB (R=4, G=4, B=4) + 4-bit alpha(ARGB).
        IMG_PIXFMT_ABGR4444     =   57,             //!< 16-bit BGR (B=4, G=4, R=4) + 4-bit alpha(ABGR).
        IMG_PIXFMT_RGBA4444     =   58,             //!< 16-bit RGB (R=4, G=4, B=4) + 4-bit alpha(RGBA).
        IMG_PIXFMT_BGRA4444     =   59,             //!< 16-bit BGR (B=4, G=4, R=4) + 4-bit alpha(BGRA).
        IMG_PIXFMT_ARGB1555     =   9,              //!< 16-bit RGB (R=5, G=5, B=5) + 1-bit alpha(ARGB).
        IMG_PIXFMT_ABGR1555     =   60,             //!< 16-bit RGB (R=5, G=5, B=5) + 1-bit alpha(ABGR).
        IMG_PIXFMT_RGBA5551     =   61,             //!< 16-bit RGB (R=5, G=5, B=5) + 1-bit alpha(RGBA).
        IMG_PIXFMT_BGRA5551     =   62,             //!< 16-bit RGB (R=5, G=5, B=5) + 1-bit alpha(BGRA).
        IMG_PIXFMT_RGB565       =   10,             //!< 16-bit RGB (R=5, G=6, B=5).
        IMG_PIXFMT_BGR565       =   63,             //!< 16-bit BGR (B=5, G=6, R=5).
        IMG_PIXFMT_RGB888       =   11,             //!< 24-bit RGB (packed).
	    IMG_PIXFMT_RSGSBS888	=	68,				//!< 24 bit signed RGB values.
        IMG_PIXFMT_ARGB8888     =   12,             //!< 24-bit RGB + 8-bit alpha.
        IMG_PIXFMT_ABGR8888     =   41,				//!< 24-bit RGB + 8-bit alpha (ABGR).
        IMG_PIXFMT_BGRA8888     =   42,				//!< 24-bit RGB + 8-bit alpha (BGRA).
        IMG_PIXFMT_RGBA8888		=   56,				//!< 24-bit RGB + 8-bit alpha (RGBA).
        IMG_PIXFMT_ARGB8332     =   43,				//!< 16-bit RGB (R=3, G=3, B=2) + 8-bit alpha.
        IMG_PIXFMT_ARGB8161616  =   64,				//!< 56-bit RGB (R=16, G=16, B=16) + 8 bit alpha.
	    IMG_PIXFMT_ARGB2101010  =   67,				//!< 30-bit RGB + 2 bit alpha

        IMG_PIXFMT_UYVY8888     =   13,             //!< YUV 4:2:2 8-bit per component.
        IMG_PIXFMT_VYUY8888     =   14,				//!< YUV 4:2:2 8-bit per component.
        IMG_PIXFMT_YVYU8888     =   15,				//!< YUV 4:2:2 8-bit per component.
        IMG_PIXFMT_YUYV8888     =   16,				//!< YUV 4:2:2 8-bit per component.
        IMG_PIXFMT_UYVY10101010 =   17,             //!< YUV 4:2:2 10-bit per component.
        IMG_PIXFMT_VYAUYA8888   =   18,             //!< YUV 4:2:2:4 8-bit per component.
        IMG_PIXFMT_YUV101010    =   19,             //!< YUV 4:4:4 10-bit per component.
        IMG_PIXFMT_AYUV4444     =   20,             //!< 12-bit YUV 4:4:4 + 4-bit alpha.
        IMG_PIXFMT_YUV888       =   21,             //!< 24-bit YUV (packed).
        IMG_PIXFMT_AYUV8888     =   22,             //!< 24-bit YUV 4:4:4 + 8-bit alpha.
        IMG_PIXFMT_AYUV2101010  =   23,             //!< 30-bit YUV 4:4:4 + 2-bit alpha.

	    IMG_PIXFMT_411PL111YUV8	=	120,			//!< Planar 8b 411 (1/4 UV horizontal, 1/1 vertically - Y, U and V are in separate planes)
	    IMG_PIXFMT_411PL12YUV8	=	121,			//!< Planar 8b 411 UV interleaved
	    IMG_PIXFMT_411PL12YVU8  =   24,             //!< Planar 8-bit 4:1:1 format. UV interleaved

        IMG_PIXFMT_420PL12YUV8  =   25,             //!< Planar 8-bit 4:2:0 format.
        IMG_PIXFMT_420PL12YVU8  =   26,             //!< Planar 8-bit 4:2:0 format - as per YUV8 but with reversed U and V samples.
        IMG_PIXFMT_422PL12YUV8  =   27,             //!< Planar 8-bit 4:2:2 format.
        IMG_PIXFMT_422PL12YVU8  =   28,             //!< Planar 8-bit 4:2:2 format - as per YUV8 but with reversed U and V samples.

	    /**
	     * @note Eq. name in hardware documentation is PL111
	     */
        IMG_PIXFMT_420PL8YUV8   =   47,             //!< Planar 8-bit 4:2:0 format - (Y, U and V are in separate planes).
	    /**
	     * @note Eq. name in hardware documentation is PL111
	     */
        IMG_PIXFMT_422PL8YUV8   =   48,             //!< Planar 8-bit 4:2:2 format - (Y, U and V are in separate planes).
    	
	    IMG_PIXFMT_420PL12YUV8_A8 =   31,           //!< Planar 8-bit 4:2:0 format + 8-bit alpha.
        IMG_PIXFMT_422PL12YUV8_A8 =   32,           //!< Planar 8-bit 4:2:2 format + 8-bit alpha.

	    /**
	     * @note Eq. name in hardware documentation is PL_Y8
	     */
        IMG_PIXFMT_PL12Y8       =   33,             //!< Y only 8 bit
    	
        IMG_PIXFMT_PL12YV8      =   35,             //!< Planar 8-bit 4:2:0 (Y data, followed by U data, followed by V data)
        IMG_PIXFMT_PL12IMC2     =   36,             //!< Planar 8-bit 4:2:0 (Y data, followed by line of U, line of V, interleaved)

        IMG_PIXFMT_A4           =   37,             //!< Alpha only 4 bit
        IMG_PIXFMT_A8           =   38,             //!< Alpha only 8 bit
        IMG_PIXFMT_YUV8         =   39,             //!< 8-bit palettised.
        IMG_PIXFMT_CVBS10       =   40,             //!< Composite video (CVBS) data stored by the UCC for YC separation.

        
	    IMG_PIXFMT_PL12YV12     =   44,				//!< YV12 Planar 8-bit 4:2:0 (Y data, followed by U data, followed by V data)					
    	
	    #if ((!defined (METAG) && !defined (MTXG)) || defined (__linux__))	/* Floats are not allowed in embedded systems */
		    IMG_PIXFMT_F16			=	52,				//!< Single channel 16 bit IEEE floating point format
		    IMG_PIXFMT_F32			=	53,				//!< Single channel 32 bit IEEE floating point format
		    IMG_PIXFMT_F16F16F16F16	=	65,				//!< Quad channel 16 bit IEEE floating point format
	    #endif
    	
	    IMG_PIXFMT_L16			=	54,				//!< Y only 16 bit
	    IMG_PIXFMT_L32			=	55,				//!< Y only 32 bit
    	
	    IMG_PIXFMT_Y1			=	66,				//!< Y 1 bit (black/white)

	    IMG_PIXFMT_444PL111YUV8 = 69,				//!< 444 YUV 8 bits
    	
	    IMG_PIXFMT_444PL12YUV8 = 137,				//!< 444 YUV 8 bits. Byte interleaved in UV buffer.
	    IMG_PIXFMT_444PL12YVU8 = 138,				//!< 444 YUV 8 bits. Byte interleaved in VU buffer.
    	
	    /*
	     * 10b formats
	     */

	    /**
	     * @note Eq. name in hardware documentation is PL_Y10
	     */
        IMG_PIXFMT_PL12Y10      =   34,				//!< Y only 10 bit. Hardware packed 3 pixels on 32 bits (starting from least significant bits).
	    IMG_PIXFMT_PL12Y10_LSB      =  96,			//!< Y only 10 bit. Unpakced on 16 bits (least significant bits)
	    IMG_PIXFMT_PL12Y10_MSB      =  97,			//!< Y only 10 bit. Unpakced on 16 bits (most significant bits)

	    /**
	     * @note Eq. name in hardware documentation is PL111
	     */
        IMG_PIXFMT_420PL8YUV10  =   49,             //!< Planar 10-bit 4:2:0 format - (Y, U and V are in separate planes). Hardware packed 3 pixels on 32 bits (starting from least significant bits).
	    IMG_PIXFMT_420PL111YUV10_LSB = 71,			//!< 420 YUV 10 bits. Unpakced on 16 bits (least significant bits). @see IMG_PIXFMT_420PL8YUV10
	    IMG_PIXFMT_420PL111YUV10_MSB = 72,			//!< 420 YUV 10 bits. Unpakced on 16 bits (most significant bits). @see IMG_PIXFMT_420PL8YUV10
    	
	    IMG_PIXFMT_420PL12YUV10 = 29,				//!< 420 YUV 10 bits - UV interleaved. Hardware packed 3 pixels on 32 bits (starting from least significant bits)
	    IMG_PIXFMT_420PL12YUV10_LSB = 74,			//!< 420 YUV 10 bits - UV interleaved. Unpakced on 16 bits (least significant bits)
	    IMG_PIXFMT_420PL12YUV10_MSB = 75,			//!< 420 YUV 10 bits - UV interleaved. Unpakced on 16 bits (most significant bits)
    	
	    IMG_PIXFMT_420PL12YVU10 = 45,				//!< 420 YVU 10 bits - VU interleaved. Hardware packed 3 pixels on 32 bits (starting from least significant bits)
	    IMG_PIXFMT_420PL12YVU10_LSB = 77,			//!< 420 YVU 10 bits - VU interleaved. Unpakced on 16 bits (least significant bits)
	    IMG_PIXFMT_420PL12YVU10_MSB = 78,			//!< 420 YVU 10 bits - VU interleaved. Unpakced on 16 bits (most significant bits)
    	
	    /**
	     * @note Eq. name in hardware documentation is PL111
	     */
        IMG_PIXFMT_422PL8YUV10  =   50,             //!< Planar 10-bit 4:2:2 format - (Y, U and V are in separate planes). Hardware packed 3 pixels on 32 bits (starting from least significant bits).
	    IMG_PIXFMT_422PL111YUV10_LSB = 122,			//!< Planar 10b 422. Unpakced on 16 bits (least significant bits)
	    IMG_PIXFMT_422PL111YUV10_MSB = 123,			//!< Planar 10b 422. Unpakced on 16 bits (most significant bits)
    	
	    IMG_PIXFMT_422PL12YUV10 = 30,				//!< 422 YUV 10 bits - UV interleaved. Hardware packed 3 pixels on 32 bits (starting from least significant bits)
	    IMG_PIXFMT_422PL12YUV10_LSB = 80,			//!< 422 YUV 10 bits - UV interleaved. Unpakced on 16 bits (least significant bits)
	    IMG_PIXFMT_422PL12YUV10_MSB = 81,			//!< 422 YUV 10 bits - UV interleaved. Unpakced on 16 bits (most significant bits)
    	
	    IMG_PIXFMT_422PL12YVU10 = 46,				//!< 422 YVU 10 bits - VU interleaved. Hardware packed 3 pixels on 32 bits (starting from least significant bits)
	    IMG_PIXFMT_422PL12YVU10_LSB = 83,			//!< 422 YVU 10 bits - VU interleaved. Unpakced on 16 bits (least significant bits)
	    IMG_PIXFMT_422PL12YVU10_MSB = 84,			//!< 422 YVU 10 bits - VU interleaved. Unpakced on 16 bits (most significant bits)
    	
	    IMG_PIXFMT_444PL111YUV10 = 85,				//!< 444 YUV 10 bits. Hardware packed 3 pixels on 32 bits (starting from least significant bits)
	    IMG_PIXFMT_444PL111YUV10_LSB = 86,			//!< 444 YUV 10 bits. Unpakced on 16 bits (least significant bits)
	    IMG_PIXFMT_444PL111YUV10_MSB = 87,			//!< 444 YUV 10 bits. Unpakced on 16 bits (most significant bits)
    	
	    IMG_PIXFMT_444PL12YUV10 = 139,				//!< 444 YUV 10 bits - UV interleaved. Hardware packed 3 pixels on 32 bits (starting from least significant bits)
	    IMG_PIXFMT_444PL12YUV10_LSB = 141,			//!< 444 YUV 10 bits - UV interleaved. Unpakced on 16 bits (least significant bits)
	    IMG_PIXFMT_444PL12YUV10_MSB = 142,			//!< 444 YUV 10 bits - UV interleaved. Unpakced on 16 bits (most significant bits)
    	
	    IMG_PIXFMT_444PL12YVU10 = 140,				//!< 444 YUV 10 bits - VU interleaved. Hardware packed 3 pixels on 32 bits (starting from least significant bits)
	    IMG_PIXFMT_444PL12YVU10_LSB = 143,			//!< 444 YUV 10 bits - VU interleaved. Unpakced on 16 bits (least significant bits)
	    IMG_PIXFMT_444PL12YVU10_MSB = 144,			//!< 444 YUV 10 bits - VU interleaved. Unpakced on 16 bits (most significant bits)
    	
	    /*
	     * mixed 8b and 10b formats
	     */

	    IMG_PIXFMT_420PL12Y8UV10 = 88,				//!< 420 YUV - Y 8b - UV interleaved on 10b. Chroma is hardware packed 3 pixels on 32 bits (starting from least significant bits)
	    IMG_PIXFMT_420PL12Y8UV10_LSB = 98,			//!< 420 YUV - Y 8b - UV interleaved on 10b. Chroma is unpacked on 16 bits (least significant bits)
	    IMG_PIXFMT_420PL12Y8UV10_MSB = 99,			//!< 420 YUV - Y 8b - UV interleaved on 10b. Chroma is unpacked on 16 bits (most significant bits)

	    IMG_PIXFMT_420PL12Y8VU10 = 89,				//!< 420 YVU - Y 8b - VU interleaved on 10b. Chroma is hardware packed 3 pixels on 32 bits (starting from least significant bits)
        IMG_PIXFMT_420PL12Y8VU10_LSB = 100,			//!< 420 YUV - Y 8b - VU interleaved on 10b. Chroma is unpacked on 16 bits (least significant bits)
        IMG_PIXFMT_420PL12Y8VU10_MSB = 101,			//!< 420 YUV - Y 8b - VU interleaved on 10b. Chroma is unpacked on 16 bits (most significant bits)

        IMG_PIXFMT_420PL111Y8UV10 = 70,             //!< Planar 8-bit luma 10-bit chroma 4:2:0. - (Y, U and V are in separate planes).
        IMG_PIXFMT_420PL111Y8UV10_LSB = 127,        //!< Same as IMG_PIXFMT_420PL111Y8UV10 but with 16-bit packing.
        IMG_PIXFMT_420PL111Y8UV10_MSB = 125,        //!< Same as IMG_PIXFMT_420PL111Y8UV10 but with 16-bit packing.

        IMG_PIXFMT_422PL12Y8UV10 = 90,				//!< 422 YUV - Y 8b - UV interleaved on 10b. Chroma is hardware packed 3 pixels on 32 bits (starting from least significant bits)
        IMG_PIXFMT_422PL12Y8UV10_LSB = 102,			//!< 422 YUV - Y 8b - UV interleaved on 10b. Chroma is unpacked on 16 bits (least significant bits)
	    IMG_PIXFMT_422PL12Y8UV10_MSB = 103,			//!< 422 YUV - Y 8b - UV interleaved on 10b. Chroma is unpacked on 16 bits (most significant bits)

	    IMG_PIXFMT_422PL12Y8VU10 = 91,				//!< 422 YVU - Y 8b - VU interleaved on 10b. Chroma is hardware packed 3 pixels on 32 bits (starting from least significant bits)
	    IMG_PIXFMT_422PL12Y8VU10_LSB = 104,			//!< 422 YVU - Y 8b - VU interleaved on 10b. Chroma is unpacked on 16 bits (least significant bits)
	    IMG_PIXFMT_422PL12Y8VU10_MSB = 105,			//!< 422 YVU - Y 8b - VU interleaved on 10b. Chroma is unpacked on 16 bits (most significant bits)
    	
	    IMG_PIXFMT_444PL12Y8UV10 = 151,				//!< 444 YUV - Y 8b - UV interleaved on 10b. Chroma is hardware packed 3 pixels on 32 bits (starting from least significant bits)
	    IMG_PIXFMT_444PL12Y8UV10_LSB = 153,			//!< 444 YUV - Y 8b - UV interleaved on 10b. Chroma is unpacked on 16 bits (least significant bits)
	    IMG_PIXFMT_444PL12Y8UV10_MSB = 154,			//!< 444 YUV - Y 8b - UV interleaved on 10b. Chroma is unpacked on 16 bits (most significant bits)

	    IMG_PIXFMT_444PL12Y8VU10 = 152,				//!< 444 YVU - Y 8b - VU interleaved on 10b. Chroma is hardware packed 3 pixels on 32 bits (starting from least significant bits)
	    IMG_PIXFMT_444PL12Y8VU10_LSB = 155,			//!< 444 YVU - Y 8b - VU interleaved on 10b. Chroma is unpacked on 16 bits (least significant bits)
	    IMG_PIXFMT_444PL12Y8VU10_MSB = 156,			//!< 444 YVU - Y 8b - VU interleaved on 10b. Chroma is unpacked on 16 bits (most significant bits)

        /*
         * mixed Y 10b, UV 8b
         */

	    IMG_PIXFMT_420PL12Y10UV8 = 92,				//!< 420 YUV - Y 10b - UV interleaved on 8b. Luma is hardware packed 3 pixels on 32 bits (starting from least significant bits)
	    IMG_PIXFMT_420PL12Y10UV8_LSB = 106,			//!< 420 YUV - Y 10b - UV interleaved on 8b. Luma is unpacked on 16 bits (least significant bits)
	    IMG_PIXFMT_420PL12Y10UV8_MSB = 107,			//!< 420 YUV - Y 10b - UV interleaved on 8b. Luma is unpacked on 16 bits (most significant bits)

	    IMG_PIXFMT_420PL12Y10VU8 = 93,				//!< 420 YVU - Y 10b - VU interleaved on 8b. Luma is hardware packed 3 pixels on 32 bits (starting from least significant bits)
	    IMG_PIXFMT_420PL12Y10VU8_LSB = 108,			//!< 420 YVU - Y 10b - VU interleaved on 8b. Luma is unpacked on 16 bits (least significant bits)
        IMG_PIXFMT_420PL12Y10VU8_MSB = 109,			//!< 420 YVU - Y 10b - VU interleaved on 8b. Luma is unpacked on 16 bits (most significant bits)

        IMG_PIXFMT_420PL111Y10UV8 = 129,            //!< Planar 10-bit luma 8-bit chroma 4:2:0. - (Y, U and V are in separate planes).
        IMG_PIXFMT_420PL111Y10UV8_LSB = 133,        //!< Same as IMG_PIXFMT_420PL111Y10UV8 but with 16-bit packing.
        IMG_PIXFMT_420PL111Y10UV8_MSB = 131,        //!< Same as IMG_PIXFMT_420PL111Y10UV8 but with 16-bit packing.

        IMG_PIXFMT_422PL12Y10UV8 = 94,				//!< 422 YUV - Y 10b - UV interleaved on 8b. Luma is hardware packed 3 pixels on 32 bits (starting from least significant bits)
        IMG_PIXFMT_422PL12Y10UV8_LSB = 110,			//!< 422 YUV - Y 10b - UV interleaved on 8b. Luma is unpacked on 16 bits (least significant bits)
	    IMG_PIXFMT_422PL12Y10UV8_MSB = 111,			//!< 422 YUV - Y 10b - UV interleaved on 8b. Luma is unpacked on 16 bits (most significant bits)

	    IMG_PIXFMT_422PL12Y10VU8 = 95,				//!< 422 YVU - Y 10b - VU interleaved on 8b. Luma is hardware packed 3 pixels on 32 bits (starting from least significant bits)
	    IMG_PIXFMT_422PL12Y10VU8_LSB = 112,			//!< 422 YVU - Y 10b - VU interleaved on 8b. Luma is unpacked on 16 bits (least significant bits)
	    IMG_PIXFMT_422PL12Y10VU8_MSB = 113,			//!< 422 YVU - Y 10b - VU interleaved on 8b. Luma is unpacked on 16 bits (least significant bits)

	    IMG_PIXFMT_444PL111Y10UV8 = 114,			//!< 444 YUV - Y 10b - U and V 8b. Luma is hardware packed 3 pxiels on 32 bits (starting from the least signigicant bits)
	    IMG_PIXFMT_444PL111Y10UV8_LSB = 115,		//!< 444 YUV - Y 10b - U and V 8b. Luma is unpacked on 16 bits (least significant bits)
	    IMG_PIXFMT_444PL111Y10UV8_MSB = 116,		//!< 444 YUV - Y 10b - U and V 8b. Luma is unpacked on 16 bits (most significant bits)

	    IMG_PIXFMT_444PL111Y8UV10 = 117,			//!< 444 YUV - Y 8b - U and V 10b. Chroma is hardware packed 3 pxiels on 32 bits (starting from the least signigicant bits)
	    IMG_PIXFMT_444PL111Y8UV10_LSB = 118,		//!< 444 YUV - Y 8b - U and V 10b. Chroma is unpacked on 16 bits (least significant bits)
	    IMG_PIXFMT_444PL111Y8UV10_MSB = 119,		//!< 444 YUV - Y 8b - U and V 10b. Chroma is unpacked on 16 bits (most significant bits)
    	
	    IMG_PIXFMT_444PL12Y10UV8 = 145,				//!< 444 YUV - Y 10b - UV interleaved on 8b. Luma is hardware packed 3 pixels on 32 bits (starting from least significant bits)
	    IMG_PIXFMT_444PL12Y10UV8_LSB = 147,			//!< 444 YUV - Y 10b - UV interleaved on 8b. Luma is unpacked on 16 bits (least significant bits)
	    IMG_PIXFMT_444PL12Y10UV8_MSB = 148,			//!< 444 YUV - Y 10b - UV interleaved on 8b. Luma is unpacked on 16 bits (most significant bits)

	    IMG_PIXFMT_444PL12Y10VU8 = 146,				//!< 444 YVU - Y 10b - VU interleaved on 8b. Luma is hardware packed 3 pixels on 32 bits (starting from least significant bits)
	    IMG_PIXFMT_444PL12Y10VU8_LSB = 149,			//!< 444 YVU - Y 10b - VU interleaved on 8b. Luma is unpacked on 16 bits (least significant bits)
	    IMG_PIXFMT_444PL12Y10VU8_MSB = 150,			//!< 444 YVU - Y 10b - VU interleaved on 8b. Luma is unpacked on 16 bits (least significant bits)
    	
        IMG_PIXFMT_422PL111Y8UV10 = 124,            //!< Planar 8-bit luma 10-bit chroma 4:2:2. - (Y, U and V are in separate planes).
        IMG_PIXFMT_422PL111Y8UV10_MSB = 126,        //!< Same as IMG_PIXFMT_422PL111Y8UV10 but with 16-bit packing.
        IMG_PIXFMT_422PL111Y8UV10_LSB = 128,        //!< Same as IMG_PIXFMT_422PL111Y8UV10 but with 16-bit packing.

        IMG_PIXFMT_422PL111Y10UV8 = 130,            //!< Planar 10-bit luma 8-bit chroma 4:2:2. - (Y, U and V are in separate planes).
        IMG_PIXFMT_422PL111Y10UV8_LSB = 134,        //!< Same as IMG_PIXFMT_422PL111Y10UV8 but with 16-bit packing.
        IMG_PIXFMT_422PL111Y10UV8_MSB = 132,        //!< Same as IMG_PIXFMT_422PL111Y10UV8 but with 16-bit packing.

        /*
        * 12b formats
        */
        IMG_PIXFMT_420PL8YUV12 = 160,   			//!< Planar 12-bit 4:2:0 format. - (Y, U and V are in separate planes).
        IMG_PIXFMT_422PL8YUV12 = 161,    			//!< Planar 12-bit 4:2:2 format. - (Y, U and V are in separate planes).
        IMG_PIXFMT_444PL8YUV12 = 162,    			//!< Planar 12-bit 4:4:4 format. - (Y, U and V are in separate planes).

        /*
        * 14b formats
        */
        IMG_PIXFMT_420PL8YUV14 = 163,    			//!< Planar 14-bit 4:2:0 format. - (Y, U and V are in separate planes).
        IMG_PIXFMT_422PL8YUV14 = 164,    			//!< Planar 14-bit 4:2:2 format. - (Y, U and V are in separate planes).
        IMG_PIXFMT_444PL8YUV14 = 165,    			//!< Planar 14-bit 4:4:4 format. - (Y, U and V are in separate planes).

        /*
        * 16b formats
        */
        IMG_PIXFMT_420PL8YUV16 = 166,    			//!< Planar 16-bit 4:2:0 format. - (Y, U and V are in separate planes).
        IMG_PIXFMT_422PL8YUV16 = 167,    			//!< Planar 16-bit 4:2:2 format. - (Y, U and V are in separate planes).
        IMG_PIXFMT_444PL8YUV16 = 168,    			//!< Planar 16-bit 4:4:4 format. - (Y, U and V are in separate planes).

	    /*
	     * other formats
	     */
    	
	    IMG_PIXFMT_UNDEFINED = 255,					//!< This format is considered invalid - used for default values into structures.

	    IMG_PIXFMT_ARBPLANAR8		= 65536,		//!< 8-bit samples with up to four planes. Lower 16-bits of pixel format encodes subsampling factors. Colour-space is not specified.
	    IMG_PIXFMT_ARBPLANAR8_LAST	= IMG_PIXFMT_ARBPLANAR8+0xffff
	
} IMG_ePixelFormat;

#ifdef __cplusplus
}
#endif

#endif // __IMG_PIXFMTS__
