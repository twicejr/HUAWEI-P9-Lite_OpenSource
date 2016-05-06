/*!
 *****************************************************************************
 *
 * @File       pixel_api_internals.c
 * @Description    This file contains internal functions used by the generic
 *  pixel manipulation library.
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

#include <img_types.h>
#include <img_defs.h>
#include <img_errors.h>
#include <img_pixfmts.h>

#include "pixel_api.h"
#include "pixel_api_internals.h"

#if defined PIXEL_LIB_INCLUDE_PIXEL_NAME_IN_INFO_STRUCT
	#define PIXNAME(x) #x##,
#else
	#define PIXNAME(x)/* Pixel name support not enabled */
#endif

/*!
******************************************************************************

 This type allows a 32 bit IEEE floating point value to be viewed as raw bits

******************************************************************************/
typedef union
{
	IMG_FLOAT	fx;
	IMG_UINT32	ui32x;

} IMG_uFLUINT32;

pixel_sPixelInfoTable PIXEL_asPixelInfo [] =
{
	/* Pixel colour format				Name								    Pixels	YBytes	UVBytes	VBytes  AlphaBytes	IsPlanar?	UV height	UV stride		HasAlpha?	*/
	/*																		    in BOP	in BOP	in BOP	in BOP  in BOP					Halved?		Ratio Times 4					*/	
	{IMG_PIXFMT_CLUT1,				{	PIXNAME(IMG_PIXFMT_CLUT1)			    8,		1,      0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
	{IMG_PIXFMT_CLUT2,          	{	PIXNAME(IMG_PIXFMT_CLUT2)			    4,		1,      0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
    {IMG_PIXFMT_CLUT4,				{	PIXNAME(IMG_PIXFMT_CLUT4)			    32,		16,		0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,      		IMG_FALSE}	},
    {IMG_PIXFMT_I4A4,				{	PIXNAME(IMG_PIXFMT_I4A4)			    16,		16,		0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,      		IMG_FALSE}	},
    {IMG_PIXFMT_I8A8,				{	PIXNAME(IMG_PIXFMT_I8A8)			    8,		16,		0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,      		IMG_FALSE}	},
    {IMG_PIXFMT_A8I8,				{	PIXNAME(IMG_PIXFMT_A8I8)			    8,		16,		0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,	        	IMG_FALSE}	},
	{IMG_PIXFMT_RGB8,				{	PIXNAME(IMG_PIXFMT_RGB8)			    16,		16,     0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
                                																																	
    {IMG_PIXFMT_RGB332,         	{	PIXNAME(IMG_PIXFMT_RGB332)			    16,		16,     0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,	        	IMG_FALSE}	},
    {IMG_PIXFMT_RGB555,         	{	PIXNAME(IMG_PIXFMT_RGB555)			    8,		16,     0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
    {IMG_PIXFMT_ARGB4444,       	{	PIXNAME(IMG_PIXFMT_ARGB4444)		    8,		16,     0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
	{IMG_PIXFMT_ABGR4444,       	{	PIXNAME(IMG_PIXFMT_ABGR4444)		    8,		16,     0,		0,		0,      	IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
	{IMG_PIXFMT_RGBA4444,       	{	PIXNAME(IMG_PIXFMT_RGBA4444)		    8,		16,     0,		0,		0,      	IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
	{IMG_PIXFMT_BGRA4444,       	{	PIXNAME(IMG_PIXFMT_BGRA4444)		    8,		16,     0,		0,		0,      	IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
    {IMG_PIXFMT_ARGB1555,       	{	PIXNAME(IMG_PIXFMT_ARGB1555)		    8,		16,     0,		0,		0,      	IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
	{IMG_PIXFMT_ABGR1555,       	{	PIXNAME(IMG_PIXFMT_ABGR1555)		    8,		16,     0,		0,		0,	        IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
	{IMG_PIXFMT_RGBA5551,       	{	PIXNAME(IMG_PIXFMT_RGBA5551)		    8,		16,     0,		0,		0,	        IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
	{IMG_PIXFMT_BGRA5551,       	{	PIXNAME(IMG_PIXFMT_BGRA5551)		    8,		16,     0,		0,		0,	        IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
    {IMG_PIXFMT_RGB565,         	{	PIXNAME(IMG_PIXFMT_RGB565)			    8,		16,     0,		0,		0,	        IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
	{IMG_PIXFMT_BGR565,         	{	PIXNAME(IMG_PIXFMT_BGR565)			    8,		16,     0,		0,		0,	        IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
    {IMG_PIXFMT_RGB888,				{	PIXNAME(IMG_PIXFMT_RGB888)			    4,		12,     0,		0,		0,	        IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
    {IMG_PIXFMT_ARGB8888,			{	PIXNAME(IMG_PIXFMT_ARGB8888)		    4,		16,     0,		0,		0,	        IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},	
	{IMG_PIXFMT_ABGR8888,			{	PIXNAME(IMG_PIXFMT_ABGR8888)		    4,		16,     0,		0,		0,	        IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
	{IMG_PIXFMT_BGRA8888,			{	PIXNAME(IMG_PIXFMT_BGRA8888)		    4,		16,     0,		0,		0,	        IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
	{IMG_PIXFMT_RGBA8888,			{	PIXNAME(IMG_PIXFMT_RGBA8888)		    4,		16,     0,		0,		0,	        IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
	{IMG_PIXFMT_ARGB8332,       	{	PIXNAME(IMG_PIXFMT_ARGB8332)		    8,		16,     0,		0,		0,	        IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},
	{IMG_PIXFMT_ARGB8161616,       	{	PIXNAME(IMG_PIXFMT_ARGB8161616)		    4,		28,     0,		0,		0,	        IMG_FALSE,	IMG_FALSE,	4,		        IMG_FALSE}	},

    {IMG_PIXFMT_UYVY8888,			{	PIXNAME(IMG_PIXFMT_UYVY8888)		    8,		16,     0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_VYUY8888,			{	PIXNAME(IMG_PIXFMT_VYUY8888)		    8,		16,		0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_YVYU8888,			{	PIXNAME(IMG_PIXFMT_YVYU8888)		    8,		16,		0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_YUYV8888,			{	PIXNAME(IMG_PIXFMT_YUYV8888)		    8,		16,		0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_UYVY10101010,		{	PIXNAME(IMG_PIXFMT_UYVY10101010)	    6,		16,     0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_VYAUYA8888,			{	PIXNAME(IMG_PIXFMT_VYAUYA8888)		    16,		48,     0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_YUV101010,			{	PIXNAME(IMG_PIXFMT_YUV101010)		    4,		16,     0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_AYUV4444,			{	PIXNAME(IMG_PIXFMT_AYUV4444)		    8,		16,     0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_YUV888,				{	PIXNAME(IMG_PIXFMT_YUV888)			    4,		12,     0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_AYUV8888,			{	PIXNAME(IMG_PIXFMT_AYUV8888)		    4,		16,     0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_AYUV2101010,		{	PIXNAME(IMG_PIXFMT_AYUV2101010)		    4,		16,		0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_A4,					{	PIXNAME(IMG_PIXFMT_A4)				    32,		16,	    0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_A8,					{	PIXNAME(IMG_PIXFMT_A8)				    16,		16,     0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_YUV8,				{	PIXNAME(IMG_PIXFMT_YUV8)			    16,		16,     0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
	{IMG_PIXFMT_PL12Y8,				{	PIXNAME(IMG_PIXFMT_PL12Y8)			    16,		16,		0,		0,		0,			IMG_FALSE,	IMG_FALSE,	2,        		IMG_FALSE}	},
                                																																	
	/* Pixel colour format													    Pixels	YBytes	UVBytes	VBytes  AlphaBytes	IsPlanar?	UV height	UV stride		HasAlpha?	*/
	/*																		    in BOP	in BOP	in BOP	in BOP  in BOP					Halved?		Ratio Times 4	        	*/
	{IMG_PIXFMT_411PL12YVU8,    	{	PIXNAME(IMG_PIXFMT_411PL12YVU8)		    16,		16,		8,		0,		0,			IMG_TRUE,	IMG_FALSE,	2,      		IMG_FALSE}	},
                                																																	
    {IMG_PIXFMT_420PL12YUV8_A8, 	{	PIXNAME(IMG_PIXFMT_420PL12YUV8_A8)	    16,		16,		16,		0,		16,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_TRUE }	},
    {IMG_PIXFMT_422PL12YUV8_A8, 	{	PIXNAME(IMG_PIXFMT_422PL12YUV8_A8)	    16,		16,		16,		0,		16,			IMG_TRUE,	IMG_FALSE,	4,        		IMG_TRUE }	},
    {IMG_PIXFMT_PL12Y10,        	{	PIXNAME(IMG_PIXFMT_PL12Y10)			    12,		16,		0,		0,		0,			IMG_FALSE,	IMG_FALSE,	2,        		IMG_FALSE}	},
    {IMG_PIXFMT_PL12YV8,        	{	PIXNAME(IMG_PIXFMT_PL12YV8)			    16,		16,		8,		0,		0,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_PL12IMC2,       	{	PIXNAME(IMG_PIXFMT_PL12IMC2)		    16,		16,		8,		0,		0,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_CVBS10,				{	PIXNAME(IMG_PIXFMT_CVBS10)			    12,		16,		0,		0,		0,			IMG_TRUE,	IMG_FALSE,	4,        		IMG_FALSE}	},
	                            																																	
    /* Pixel colour format													    Pixels	YBytes	UVBytes	VBytes  AlphaBytes	IsPlanar?	UV height	UV stride		HasAlpha?	*/
	/*																		    in BOP	in BOP	in BOP	in BOP  in BOP					Halved?		Ratio Times 4				*/
    {IMG_PIXFMT_420PL8YUV8,	    	{	PIXNAME(IMG_PIXFMT_420PL8YUV8)		    16,		16,		8,		8,		0,			IMG_TRUE,	IMG_TRUE,	2,      		IMG_FALSE}	},
    {IMG_PIXFMT_420PL8YUV10,		{	PIXNAME(IMG_PIXFMT_420PL8YUV10)		    12,		16,		8,		8,		0,			IMG_TRUE,	IMG_TRUE,	2,      		IMG_FALSE}	},
    {IMG_PIXFMT_420PL111YUV10_MSB,  {   PIXNAME(IMG_PIXFMT_420PL111YUV10_MSB)   8,      16,     8,      8,      0,          IMG_TRUE,   IMG_TRUE,   2,              IMG_FALSE}  },
    {IMG_PIXFMT_420PL111Y8UV10,     {   PIXNAME(IMG_PIXFMT_420PL111Y8UV10)      12,     12,     8,      8,      0,          IMG_TRUE,   IMG_TRUE,   2,              IMG_FALSE}  },
    {IMG_PIXFMT_420PL111Y8UV10_MSB, {   PIXNAME(IMG_PIXFMT_420PL111Y8UV10_MSB)  8,      8,      8,      8,      0,          IMG_TRUE,   IMG_TRUE,   2,              IMG_FALSE}  },
    {IMG_PIXFMT_420PL111Y10UV8,     {   PIXNAME(IMG_PIXFMT_420PL111Y10UV8)      12,     16,     6,      6,      0,          IMG_TRUE,   IMG_TRUE,   2,              IMG_FALSE}  },
    {IMG_PIXFMT_420PL111Y10UV8_MSB, {   PIXNAME(IMG_PIXFMT_420PL111Y10UV8_MSB)  8,      16,     4,      4,      0,          IMG_TRUE,   IMG_TRUE,   2,              IMG_FALSE}  },

    {IMG_PIXFMT_420PL12YUV8,		{	PIXNAME(IMG_PIXFMT_420PL12YUV8)		    16,		16,		16,     0,		0,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_420PL12YVU8,    	{	PIXNAME(IMG_PIXFMT_420PL12YVU8)		    16,		16,		16,     0,		0,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_420PL12YUV10,   	{	PIXNAME(IMG_PIXFMT_420PL12YUV10)	    12,		16,		16,		0,		0,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_420PL12YVU10,   	{	PIXNAME(IMG_PIXFMT_420PL12YVU10)	    12,		16,		16,		0,		0,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_FALSE}	},
	{IMG_PIXFMT_420PL12YUV10_MSB,	{	PIXNAME(IMG_PIXFMT_420PL12YUV10_MSB)    8,	    16,		16,		0,		0,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_FALSE}	},
	{IMG_PIXFMT_420PL12YVU10_MSB,	{	PIXNAME(IMG_PIXFMT_420PL12YVU10_MSB)    8,	    16,		16,		0,		0,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_420PL12Y8UV10,      {   PIXNAME(IMG_PIXFMT_420PL12Y8UV10)       12,     12,     16,     0,      0,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_420PL12Y8VU10,      {   PIXNAME(IMG_PIXFMT_420PL12Y8VU10)       12,     12,     16,     0,      0,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_420PL12Y8UV10_MSB,  {   PIXNAME(IMG_PIXFMT_420PL12Y8UV10_MSB)   8,      8,      16,     0,      0,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_420PL12Y8VU10_MSB,  {   PIXNAME(IMG_PIXFMT_420PL12Y8VU10_MSB)   8,      8,      16,     0,      0,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_420PL12Y10UV8,      {   PIXNAME(IMG_PIXFMT_420PL12Y10UV8)       12,     16,     12,     0,      0,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_420PL12Y10VU8,      {   PIXNAME(IMG_PIXFMT_420PL12Y10VU8)       12,     16,     12,     0,      0,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_420PL12Y10UV8_MSB,  {   PIXNAME(IMG_PIXFMT_420PL12Y10UV8_MSB)   8,      16,     8,      0,      0,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_420PL12Y10VU8_MSB,  {   PIXNAME(IMG_PIXFMT_420PL12Y10VU8_MSB)   8,      16,     8,      0,      0,			IMG_TRUE,	IMG_TRUE,	4,        		IMG_FALSE}	},

    {IMG_PIXFMT_422PL8YUV8,	    	{	PIXNAME(IMG_PIXFMT_422PL8YUV8)		    16,		16,		8,		8,		0,			IMG_TRUE,	IMG_FALSE,	2,      		IMG_FALSE}	},
    {IMG_PIXFMT_422PL8YUV10,		{	PIXNAME(IMG_PIXFMT_422PL8YUV10)		    12,		16,		8,		8,		0,			IMG_TRUE,	IMG_FALSE,	2,      		IMG_FALSE}	},
    {IMG_PIXFMT_422PL111YUV10_MSB,  {   PIXNAME(IMG_PIXFMT_422PL111YUV10_MSB)   8,      16,     8,      8,      0,          IMG_TRUE,   IMG_FALSE,  2,              IMG_FALSE}  },
    {IMG_PIXFMT_422PL111Y8UV10,     {   PIXNAME(IMG_PIXFMT_422PL111Y8UV10)      12,     12,     8,      8,      0,          IMG_TRUE,   IMG_FALSE,  2,              IMG_FALSE}  },
    {IMG_PIXFMT_422PL111Y8UV10_MSB, {   PIXNAME(IMG_PIXFMT_422PL111Y8UV10_MSB)  8,      8,      8,      8,      0,          IMG_TRUE,   IMG_FALSE,  2,              IMG_FALSE}  },
    {IMG_PIXFMT_422PL111Y10UV8,     {   PIXNAME(IMG_PIXFMT_422PL111Y10UV8)      12,     16,     6,      6,      0,          IMG_TRUE,   IMG_FALSE,  2,              IMG_FALSE}  },
    {IMG_PIXFMT_422PL111Y10UV8_MSB, {   PIXNAME(IMG_PIXFMT_422PL111Y10UV8_MSB)  8,      16,     4,      4,      0,          IMG_TRUE,   IMG_FALSE,  2,              IMG_FALSE}  },

    {IMG_PIXFMT_422PL12YUV8,    	{	PIXNAME(IMG_PIXFMT_422PL12YUV8)		    16,		16,		16,		0,		0,			IMG_TRUE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_422PL12YVU8,		{	PIXNAME(IMG_PIXFMT_422PL12YVU8)		    16,		16,		16,     0,		0,			IMG_TRUE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_422PL12YUV10,		{	PIXNAME(IMG_PIXFMT_422PL12YUV10)	    12,		16,		16,		0,		0,			IMG_TRUE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_422PL12YVU10,		{	PIXNAME(IMG_PIXFMT_422PL12YVU10)	    12,		16,		16,		0,		0,			IMG_TRUE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_422PL12YUV10_MSB,	{	PIXNAME(IMG_PIXFMT_422PL12YUV10_MSB)    8,	    16,		16,		0,		0,			IMG_TRUE,	IMG_FALSE,	4,        		IMG_FALSE}	},
	{IMG_PIXFMT_422PL12YVU10_MSB,	{	PIXNAME(IMG_PIXFMT_422PL12YVU10_MSB)    8,	    16,		16,		0,		0,			IMG_TRUE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_422PL12Y8UV10,      {   PIXNAME(IMG_PIXFMT_422PL12Y8UV10)       12,     12,     16,     0,      0,			IMG_TRUE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_422PL12Y8VU10,      {   PIXNAME(IMG_PIXFMT_422PL12Y8VU10)       12,     12,     16,     0,      0,			IMG_TRUE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_422PL12Y8UV10_MSB,  {   PIXNAME(IMG_PIXFMT_422PL12Y8UV10_MSB)   8,      8,      16,     0,      0,			IMG_TRUE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_422PL12Y8VU10_MSB,  {   PIXNAME(IMG_PIXFMT_422PL12Y8VU10_MSB)   8,      8,      16,     0,      0,			IMG_TRUE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_422PL12Y10UV8,      {   PIXNAME(IMG_PIXFMT_422PL12Y10UV8)       12,     16,     12,     0,      0,			IMG_TRUE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_422PL12Y10VU8,      {   PIXNAME(IMG_PIXFMT_422PL12Y10VU8)       12,     16,     12,     0,      0,			IMG_TRUE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_422PL12Y10UV8_MSB,  {   PIXNAME(IMG_PIXFMT_422PL12Y10UV8_MSB)   8,      16,     8,      0,      0,			IMG_TRUE,	IMG_FALSE,	4,        		IMG_FALSE}	},
    {IMG_PIXFMT_422PL12Y10VU8_MSB,  {   PIXNAME(IMG_PIXFMT_422PL12Y10VU8_MSB)   8,      16,     8,      0,      0,			IMG_TRUE,	IMG_FALSE,	4,        		IMG_FALSE}	},

    {IMG_PIXFMT_444PL111YUV8,       {   PIXNAME(IMG_PIXFMT_444PL111YUV8)        16,     16,     16,     16,     0,          IMG_TRUE,   IMG_FALSE,  4,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL111YUV10,      {   PIXNAME(IMG_PIXFMT_444PL111YUV10)       12,     16,     16,     16,     0,          IMG_TRUE,   IMG_FALSE,  4,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL111YUV10_MSB,  {   PIXNAME(IMG_PIXFMT_444PL111YUV10_MSB)   8,      16,     16,     16,     0,          IMG_TRUE,   IMG_FALSE,  4,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL111Y8UV10,     {   PIXNAME(IMG_PIXFMT_444PL111Y8UV10)      12,     12,     16,     16,     0,          IMG_TRUE,   IMG_FALSE,  4,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL111Y8UV10_MSB, {   PIXNAME(IMG_PIXFMT_444PL111Y8UV10_MSB)  8,      8,      16,     16,     0,          IMG_TRUE,   IMG_FALSE,  4,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL111Y10UV8,     {   PIXNAME(IMG_PIXFMT_444PL111Y10UV8)      12,     16,     12,     12,     0,          IMG_TRUE,   IMG_FALSE,  4,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL111Y10UV8_MSB, {   PIXNAME(IMG_PIXFMT_444PL111Y10UV8_MSB)  8,      16,     8,      8,      0,          IMG_TRUE,   IMG_FALSE,  4,              IMG_FALSE}  },
 
    {IMG_PIXFMT_444PL12YUV8,        {   PIXNAME(IMG_PIXFMT_444PL12YUV8)         16,     16,     32,     0,      0,          IMG_TRUE,   IMG_FALSE,  8,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL12YVU8,        {   PIXNAME(IMG_PIXFMT_444PL12YVU8)         16,     16,     32,     0,      0,          IMG_TRUE,   IMG_FALSE,  8,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL12YUV10,       {   PIXNAME(IMG_PIXFMT_444PL12YUV10)        12,     16,     32,     0,      0,          IMG_TRUE,   IMG_FALSE,  8,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL12YVU10,       {   PIXNAME(IMG_PIXFMT_444PL12YVU10)        12,     16,     32,     0,      0,          IMG_TRUE,   IMG_FALSE,  8,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL12YUV10_MSB,   {   PIXNAME(IMG_PIXFMT_444PL12YUV10_MSB)    8,      16,     32,     0,      0,          IMG_TRUE,   IMG_FALSE,  8,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL12YVU10_MSB,   {   PIXNAME(IMG_PIXFMT_444PL12YVU10_MSB)    8,      16,     32,     0,      0,          IMG_TRUE,   IMG_FALSE,  8,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL12Y8UV10,      {   PIXNAME(IMG_PIXFMT_444PL12Y8UV10)       12,     12,     32,     0,      0,          IMG_TRUE,   IMG_FALSE,  8,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL12Y8VU10,      {   PIXNAME(IMG_PIXFMT_444PL12Y8VU10)       12,     12,     32,     0,      0,          IMG_TRUE,   IMG_FALSE,  8,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL12Y8UV10_MSB,  {   PIXNAME(IMG_PIXFMT_444PL12Y8UV10_MSB)   8,      8,      32,     0,      0,          IMG_TRUE,   IMG_FALSE,  8,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL12Y8VU10_MSB,  {   PIXNAME(IMG_PIXFMT_444PL12Y8VU10_MSB)   8,      8,      32,     0,      0,          IMG_TRUE,   IMG_FALSE,  8,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL12Y10UV8,      {   PIXNAME(IMG_PIXFMT_444PL12Y10UV8)       12,     16,     24,     0,      0,          IMG_TRUE,   IMG_FALSE,  8,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL12Y10VU8,      {   PIXNAME(IMG_PIXFMT_444PL12Y10VU8)       12,     16,     24,     0,      0,          IMG_TRUE,   IMG_FALSE,  8,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL12Y10UV8_MSB,  {   PIXNAME(IMG_PIXFMT_444PL12Y10UV8_MSB)   8,      16,     16,     0,      0,          IMG_TRUE,   IMG_FALSE,  8,              IMG_FALSE}  },
    {IMG_PIXFMT_444PL12Y10VU8_MSB,  {   PIXNAME(IMG_PIXFMT_444PL12Y10VU8_MSB)   8,      16,     16,     0,      0,          IMG_TRUE,   IMG_FALSE,  8,              IMG_FALSE}  },

    {IMG_PIXFMT_PL12Y10_MSB,        {   PIXNAME(IMG_PIXFMT_PL12Y10_MSB)         8,      16,     0,      0,      0,          IMG_FALSE,  IMG_FALSE,  2,              IMG_FALSE}  },

	/* Pixel colour format													    Pixels	YBytes	UVBytes	VBytes  AlphaBytes	IsPlanar?	UV height	UV stride		HasAlpha?	*/
	/*																		    in BOP	in BOP	in BOP	in BOP  in BOP					Halved?		Ratio Times 4				*/
	#if (!defined (METAG) && !defined (MTXG)&& !defined(IMG_KERNEL_MODULE))
	{IMG_PIXFMT_F16,       			{	PIXNAME(IMG_PIXFMT_F16)				    4,		8,		0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
	{IMG_PIXFMT_F32,       			{	PIXNAME(IMG_PIXFMT_F32)				    2,		8,		0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
	#endif
	{IMG_PIXFMT_L16,       			{	PIXNAME(IMG_PIXFMT_L16)				    4,		8,		0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
	{IMG_PIXFMT_L32,       			{	PIXNAME(IMG_PIXFMT_L16)				    2,		8,		0,		0,		0,			IMG_FALSE,	IMG_FALSE,	4,        		IMG_FALSE}	},
};                                   							
                                   							
                                     
pixel_sPixelInfoTable *	pixel_GetPixelInfoFromPixelColourFormat ( IMG_ePixelFormat	ePixelColourFormat )
{
	IMG_UINT32				ui32i;
	IMG_BOOL				bFoundIt					= IMG_FALSE;
	pixel_sPixelInfoTable *	psThisPixelInfoTableEntry	= IMG_NULL;	

	for (ui32i=0; ui32i<(sizeof(PIXEL_asPixelInfo)/sizeof(pixel_sPixelInfoTable)); ui32i++)
	{
		if ( ePixelColourFormat == PIXEL_asPixelInfo[ui32i].ePixelColourFormat )
		{
			/* There must only be one entry per pixel colour format in the table */
			IMG_ASSERT ( bFoundIt == IMG_FALSE );
			bFoundIt = IMG_TRUE;
			psThisPixelInfoTableEntry = &PIXEL_asPixelInfo[ui32i]; 

			/* We deliberately do NOT break here - scan rest of table to ensure there are not duplicate entries */
		}		
	}

	return psThisPixelInfoTableEntry;
}

#if (!defined (METAG) && !defined (MTXG)&& !defined(IMG_KERNEL_MODULE))	/* Floats are not allowed in embedded systems */
	#define	FLOAT_SIGN_WIDTH		1
	#define	FLOAT_SIGN_SHIFT		31
	#define	FLOAT_SIGN_MASK			(((1 << FLOAT_SIGN_WIDTH) - 1) << FLOAT_SIGN_SHIFT)
	#define	FLOAT_EXPONENT_WIDTH	8
	#define	FLOAT_EXPONENT_SHIFT	23
	#define	FLOAT_EXPONENT_MASK		(((1 << FLOAT_EXPONENT_WIDTH) - 1) << FLOAT_EXPONENT_SHIFT)
	#define	FLOAT_EXPONENT_OFFSET	127
	#define	FLOAT_MANTISSA_WIDTH	23
	#define	FLOAT_MANTISSA_SHIFT	0
	#define	FLOAT_MANTISSA_MASK		(((1 << FLOAT_MANTISSA_WIDTH) - 1) << FLOAT_MANTISSA_SHIFT)
	
	#define	FLOAT16_SIGN_WIDTH		1
	#define	FLOAT16_SIGN_SHIFT		15
	#define	FLOAT16_SIGN_MASK		(((1 << FLOAT16_SIGN_WIDTH) - 1) << FLOAT16_SIGN_SHIFT)
	#define	FLOAT16_EXPONENT_WIDTH	5
	#define	FLOAT16_EXPONENT_SHIFT	10
	#define	FLOAT16_EXPONENT_MASK	(((1 << FLOAT16_EXPONENT_WIDTH) - 1) << FLOAT16_EXPONENT_SHIFT)
	#define	FLOAT16_EXPONENT_OFFSET	15
	#define	FLOAT16_MANTISSA_WIDTH	10
	#define	FLOAT16_MANTISSA_SHIFT	0
	#define	FLOAT16_MANTISSA_MASK	(((1 << FLOAT16_MANTISSA_WIDTH) - 1) << FLOAT16_MANTISSA_SHIFT)

	/*****************************************************************************
	 Function Name	: ConvertIEEE32ToFloat16
	 Inputs			: fFloat, bRoundToNearestEven 
	 Outputs		: none
	 Returns		: dwFloat16
	 Globals Used	: none
	 Description	: Converts a IEEE 32 bit floating point number into a Float16, 
					  if bRoundToNearestEven is true than rounding to nearest even 
					  is applied else round to zero.
	*****************************************************************************/
	IMG_UINT16 ConvertIEEE32ToFloat16( IMG_FLOAT fIEEE32, IMG_BOOL bRoundToNearestEven )
	{
		IMG_UINT32		ui32Sign;
		IMG_UINT32		ui32Exponent;
		IMG_UINT32		ui32Mantissa;
		IMG_INT32		i32Exponent, i32OrigExponent;
		IMG_UINT16		ui16Float;
		IMG_uFLUINT32	uFloat;
		IMG_UINT32		ui32MantissaShiftedOut;
		IMG_UINT32		ui32ExpMantissa = 0;
		IMG_BOOL		bExpMantissaUsed = IMG_FALSE;
	
		uFloat.fx = fIEEE32;
	
		/*
			Unpack the sign, exponent and mantissa from the float
		*/
		ui32Sign		= (uFloat.ui32x & FLOAT_SIGN_MASK) >> FLOAT_SIGN_SHIFT;
		ui32Exponent	= (uFloat.ui32x & FLOAT_EXPONENT_MASK) >> FLOAT_EXPONENT_SHIFT;
		ui32Mantissa	= (uFloat.ui32x & FLOAT_MANTISSA_MASK) >> FLOAT_MANTISSA_SHIFT;
	
		if (ui32Exponent == ((1 << FLOAT_EXPONENT_WIDTH) - 1))
		{
			ui32Exponent = (1 << FLOAT16_EXPONENT_WIDTH) - 1;
			if (ui32Mantissa != 0)
			{
				/*
					Convert a NaN to a NaN
				*/
				ui32Mantissa = (1 << FLOAT16_MANTISSA_WIDTH) - 1;
			}
			else
			{
				/*
					Convert infinity to infinity
				*/
				ui32Mantissa = 0;
			}
		}
		else
		{
			if (ui32Exponent == 0)
			{
				/*
					Convert zeros and denormalised numbers to zero
				*/
				ui32Exponent	= 0;
				ui32Mantissa	= 0;
			}
			else
			{
				i32Exponent = (IMG_INT32) ui32Exponent - (FLOAT_EXPONENT_OFFSET - FLOAT16_EXPONENT_OFFSET);
				if (i32Exponent <= 0)
				{
					/*
						Convert underflows to denormalised numbers
					*/
					ui32ExpMantissa = ui32Mantissa;
					i32OrigExponent = i32Exponent;
					ui32Exponent	= 0;
					ui32Mantissa	>>= (FLOAT_MANTISSA_WIDTH - FLOAT16_MANTISSA_WIDTH + 1);
					ui32Mantissa	|= (1 << (FLOAT16_MANTISSA_WIDTH - 1));
					while ((i32Exponent < 0) && ui32Mantissa)
					{
						i32Exponent++;
						ui32Mantissa >>= 1;
					}
	
					if (bRoundToNearestEven)
					{
						if ((FLOAT_MANTISSA_WIDTH - FLOAT16_MANTISSA_WIDTH - i32OrigExponent) <= FLOAT_MANTISSA_WIDTH)
						{
							ui32MantissaShiftedOut = (ui32ExpMantissa | (1 << FLOAT_MANTISSA_WIDTH)) & ((1 << (FLOAT_MANTISSA_WIDTH - FLOAT16_MANTISSA_WIDTH + 1 - i32OrigExponent)) - 1);
							if ( ( ui32MantissaShiftedOut & ~((1 << (FLOAT_MANTISSA_WIDTH - FLOAT16_MANTISSA_WIDTH - i32OrigExponent)) - 1) ) != 0 )
							{
								/* round */
								ui32Mantissa ++;
							}
							if ( ui32MantissaShiftedOut == (IMG_UINT32)( ~((1 << (FLOAT_MANTISSA_WIDTH - FLOAT16_MANTISSA_WIDTH - i32OrigExponent)) - 1) & ((1 << (FLOAT_MANTISSA_WIDTH - FLOAT16_MANTISSA_WIDTH + 1 - i32OrigExponent)) - 1) ) )
							{
								/* if halfway round to nearest even */
								ui32Mantissa &= ~0x1;
							}
						}
					}
				}
				else
				{
					if (i32Exponent >= ((1 << FLOAT16_EXPONENT_WIDTH) - 1))
					{
						/*
							Convert overflows to the maximum value
						*/
						ui32Exponent	= (1 << FLOAT16_EXPONENT_WIDTH) - 2;
						ui32Mantissa	= (1 << FLOAT16_MANTISSA_WIDTH) - 1;
					}
					else
					{
						/*
							Convert normalised numbers
						*/
						ui32Exponent	-= (FLOAT_EXPONENT_OFFSET - FLOAT16_EXPONENT_OFFSET);
						if (bRoundToNearestEven)
						{
							ui32MantissaShiftedOut = ui32Mantissa & ((1 << (FLOAT_MANTISSA_WIDTH - FLOAT16_MANTISSA_WIDTH)) - 1);
							ui32Mantissa	>>= (FLOAT_MANTISSA_WIDTH - FLOAT16_MANTISSA_WIDTH);
							ui32ExpMantissa = ((ui32Exponent << FLOAT16_EXPONENT_SHIFT) & FLOAT16_EXPONENT_MASK) |
												((ui32Mantissa << FLOAT16_MANTISSA_SHIFT) & FLOAT16_MANTISSA_MASK);
							if ( ( ui32MantissaShiftedOut & ~((1 << (FLOAT_MANTISSA_WIDTH - FLOAT16_MANTISSA_WIDTH - 1)) - 1) ) != 0 )
							{
								/* round */
								ui32ExpMantissa++;
							}
							if ( ui32MantissaShiftedOut == ( ~((1 << (FLOAT_MANTISSA_WIDTH - FLOAT16_MANTISSA_WIDTH - 1)) - 1) & ((1 << (FLOAT_MANTISSA_WIDTH - FLOAT16_MANTISSA_WIDTH)) - 1) ) )
							{
								/* if halfway round to nearest even */
								ui32ExpMantissa &= ~0x1;
							}
							bExpMantissaUsed = IMG_TRUE;
						}
						else
						{
							ui32Mantissa	>>= (FLOAT_MANTISSA_WIDTH - FLOAT16_MANTISSA_WIDTH);
						}
					}
				}
			}
		}
	
		/*
			Pack the sign, exponent and mantissa for the float16
		*/
		if (bExpMantissaUsed)
		{
			ui16Float	= ((ui32Sign << FLOAT16_SIGN_SHIFT) & FLOAT16_SIGN_MASK) |
							ui32ExpMantissa;
		}
		else
		{
			ui16Float	= ((ui32Sign << FLOAT16_SIGN_SHIFT) & FLOAT16_SIGN_MASK) |
							((ui32Exponent << FLOAT16_EXPONENT_SHIFT) & FLOAT16_EXPONENT_MASK) |
							((ui32Mantissa << FLOAT16_MANTISSA_SHIFT) & FLOAT16_MANTISSA_MASK);
		}
	
		return ui16Float;
	}
	
	/******************************************************************************
	 * Function Name: ConvertF16ToIEEE32
	 *
	 * Inputs       : 16 bit float	
	 * Outputs      : -
	 * Returns      : 32 bit ieee float
	 * Globals Used : -
	 *
	 * Description  : converts 16bit IEEE float to 32 IEEE float
	 * Pre-condition: -
	 *****************************************************************************/
	IMG_FLOAT ConvertF16ToIEEE32( IMG_UINT16 ui16Input )
	{
		IMG_BOOL			bSign;
		IMG_UINT32			ui32Mantissa, ui32Exponent;
		IMG_uFLUINT32		ufl32IEEE;
	
		/*
			get the sign, exponent and mantissa values from the raw texel data.
			sign is the top bit,
			exponent is bits 14->10
			mantissa is bits 9->0
		*/
		bSign			= ((ui16Input & 0x8000) == 0x8000);
		ui32Exponent	= ((ui16Input >> 10) & 0x1F);
		ui32Mantissa	= (ui16Input & 0x3FF);
	
		if(ui32Exponent == 0x0)
		{
			if (ui32Mantissa == 0)
			{
				ufl32IEEE.ui32x = 0;
			}
			else
			{
				/* denormal */
				ui32Exponent = ui32Exponent + 127 - 14;
				while ((ui32Mantissa & (1 << 10)) == 0)
				{
					ui32Exponent --;
					ui32Mantissa <<= 1;
				}
				ufl32IEEE.ui32x = ((ui32Exponent & 0xff) << 23) | ((ui32Mantissa << 13) & 0x007fffff);
			}
		}
		else if(ui32Exponent == 0x1F)
		{
			/* F16 NAN is mapped to an IEEE NAN */
			ufl32IEEE.ui32x = (0xff << 23) | (ui32Mantissa << 13);
		}
		else
		{
			/* exponent is 5bits biased with 0 being represented by 0xF	*/
			ufl32IEEE.ui32x = ((((IMG_INT32)ui32Exponent) - 15 + 127) & 0xff) << 23;
			ufl32IEEE.ui32x |= ui32Mantissa << 13;
		}
	
		ufl32IEEE.ui32x |= bSign ? 0x80000000 : 0;
	
		return ufl32IEEE.fx;
	}
#endif

/*******************************************************************************************************/
/*******************************************************************************************************/

/**********************/
/* Blocking functions */
/**********************/

/*!
******************************************************************************
@Function               pixel_BlockCLUT
******************************************************************************/
static
IMG_UINT32
pixel_BlockCLUT(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32numColBits,
    IMG_UINT32              ui32numAlphaBits,
    IMG_BOOL				bAlphaMostSignificant,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32  n;
    IMG_UINT32  word;
    IMG_UINT32	ui32Cycles;
    IMG_UINT32	ui32ThisShift;
    IMG_UINT32	ui32ThisColour;
    IMG_UINT32	ui32ThisAlpha;

	IMG_ASSERT ( ((ui32numColBits+ui32numAlphaBits)%2) == 0 );
	
    word = 0;
    ui32Cycles = (32 / (ui32numColBits+ui32numAlphaBits));
    
	for (n = 0; n < ui32Cycles; n++)
	{
        //#undef BIT_ORDER_IS_LSB_TO_MSB
		//#ifdef BIT_ORDER_IS_LSB_TO_MSB        		
        	ui32ThisShift = (n * (ui32numColBits+ui32numAlphaBits));
        //#else
	    //    ui32ThisShift = ((ui32Cycles-n-1)*(ui32numColBits+ui32numAlphaBits));        
        //#endif
        
        ui32ThisColour = psGetSetCB->ui32Y[(ui32Index+n)];
        
		if (ui32numColBits < 10)
		{
			ui32ThisColour >>= (10 - ui32numColBits);
		}
		else
		{
			ui32ThisColour <<= (ui32numColBits - 10);
			ui32ThisColour |= ui32ThisColour >> 10;
		}
		
		
		ui32ThisAlpha  = psGetSetCB->ui32Alpha[(ui32Index+n)];
		
		if (ui32numAlphaBits > 0)
		{
			if (ui32numAlphaBits < 10)
			{
				ui32ThisAlpha >>= (10 - ui32numAlphaBits);
			}
			else
			{
				ui32ThisAlpha <<= (ui32numAlphaBits - 10);
				ui32ThisAlpha |= ui32ThisAlpha >> 10;
			}
		}


    	if ( bAlphaMostSignificant == IMG_TRUE )
    	{
    		if ( ui32numAlphaBits > 0 )
    		{
				word |= ui32ThisAlpha << (ui32ThisShift + ui32numColBits);
			}
			word |= ui32ThisColour << ui32ThisShift;
    	}
    	else
    	{
        	word |= ui32ThisColour << (ui32ThisShift + ui32numAlphaBits);
        	
        	if ( ui32numAlphaBits > 0)
        	{
				word |= ui32ThisAlpha << ui32ThisShift;
			}
    	}   
    } 
    
    return word; 	
}

/*!
******************************************************************************
@Function               pixel_BlockA4
******************************************************************************/
static
IMG_UINT32
pixel_BlockA4(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =  ((psGetSetCB->ui32Alpha[ui32Index + 0] >> 2) & 0x0f) <<  0;
    ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index + 1] >> 2) & 0x0f) <<  4;
    ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index + 2] >> 2) & 0x0f) <<  8;
    ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index + 3] >> 2) & 0x0f) << 12;
    ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index + 4] >> 2) & 0x0f) << 16;
    ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index + 5] >> 2) & 0x0f) << 20;
    ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index + 6] >> 2) & 0x0f) << 24;
    ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index + 7] >> 2) & 0x0f) << 28;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockA8
******************************************************************************/
static
IMG_UINT32
pixel_BlockA8(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =   (psGetSetCB->ui32Alpha[ui32Index]   >> 2) & 0xff;
    ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index+1] >> 2) & 0xff) << 8;
    ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index+2] >> 2) & 0xff) << 16;
    ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index+3] >> 2) & 0xff) << 24;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockRGB555AndARGB1555
******************************************************************************/
static
IMG_UINT32
pixel_BlockRGB555AndARGB1555(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =  ((psGetSetCB->ui32Y[ui32Index]      & 0x3FF) >> 5) << 10;
    ui32Word |= ((psGetSetCB->ui32U[ui32Index]      & 0x3FF) >> 5) <<  5;
    ui32Word |= ((psGetSetCB->ui32V[ui32Index]      & 0x3FF) >> 5) <<  0;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index + 1]  & 0x3FF) >> 5) << 26;
    ui32Word |= ((psGetSetCB->ui32U[ui32Index + 1]  & 0x3FF) >> 5) << 21;
    ui32Word |= ((psGetSetCB->ui32V[ui32Index + 1]  & 0x3FF) >> 5) << 16;

	if (psGetSetCB->ePixelColourFormat == IMG_PIXFMT_ARGB1555)
    {
        ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index]      & 0x3FF) >> 9) << 15;
        ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index + 1]  & 0x3FF) >> 9) << 31;
    }

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockARGB4444
******************************************************************************/
static
IMG_UINT32
pixel_BlockARGB4444(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =  ((psGetSetCB->ui32Alpha[ui32Index]  & 0x3FF) >> 6) << 12;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index]      & 0x3FF) >> 6) <<  8;
    ui32Word |= ((psGetSetCB->ui32U[ui32Index]      & 0x3FF) >> 6) <<  4;
    ui32Word |= ((psGetSetCB->ui32V[ui32Index]      & 0x3FF) >> 6) <<  0;

    ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index + 1]  & 0x3FF) >> 6) << 28;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index + 1]      & 0x3FF) >> 6) << 24;
    ui32Word |= ((psGetSetCB->ui32U[ui32Index + 1]      & 0x3FF) >> 6) << 20;
    ui32Word |= ((psGetSetCB->ui32V[ui32Index + 1]      & 0x3FF) >> 6) << 16;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockRGB565
******************************************************************************/
static
IMG_UINT32
pixel_BlockRGB565(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word  = ((psGetSetCB->ui32Y[ui32Index]      & 0x3FF) >> 5) << 11;
    ui32Word |= ((psGetSetCB->ui32U[ui32Index]      & 0x3FF) >> 4) <<  5;
    ui32Word |= ((psGetSetCB->ui32V[ui32Index]      & 0x3FF) >> 5) <<  0;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index + 1]  & 0x3FF) >> 5) << 27;
    ui32Word |= ((psGetSetCB->ui32U[ui32Index + 1]  & 0x3FF) >> 4) << 21;
    ui32Word |= ((psGetSetCB->ui32V[ui32Index + 1]  & 0x3FF) >> 5) << 16;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockRGB332
******************************************************************************/
static
IMG_UINT32
pixel_BlockRGB332(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_INT32               n;
    IMG_UINT32              ui32Word = 0;

    for (n = 3; n >= 0; n--)
    {
        ui32Word <<= 8;
        ui32Word |= ((psGetSetCB->ui32Y[ui32Index + n] >> 2) & 0xe0);
        ui32Word |= ((psGetSetCB->ui32U[ui32Index + n] >> 5) & 0x1c);
        ui32Word |= ((psGetSetCB->ui32V[ui32Index + n] >> 8) & 0x03);
    }

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockARGB8888
******************************************************************************/
static
IMG_UINT32
pixel_BlockARGB8888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =  ((psGetSetCB->ui32Alpha[ui32Index]  & 0x3FF) >> 2) << 24;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index]      & 0x3FF) >> 2) << 16;
    ui32Word |= ((psGetSetCB->ui32U[ui32Index]      & 0x3FF) >> 2) <<  8;
    ui32Word |= ((psGetSetCB->ui32V[ui32Index]      & 0x3FF) >> 2) <<  0;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockABGR8888
******************************************************************************/
static
IMG_UINT32
pixel_BlockABGR8888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =  ((psGetSetCB->ui32Alpha[ui32Index]  & 0x3FF) >> 2) << 24;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index]      & 0x3FF) >> 2) <<  0;
    ui32Word |= ((psGetSetCB->ui32U[ui32Index]      & 0x3FF) >> 2) <<  8;
    ui32Word |= ((psGetSetCB->ui32V[ui32Index]      & 0x3FF) >> 2) << 16;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockBGRA8888
******************************************************************************/
static
IMG_UINT32
pixel_BlockBGRA8888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =  ((psGetSetCB->ui32Alpha[ui32Index]  & 0x3FF) >> 2) <<  0;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index]      & 0x3FF) >> 2) <<  8;
    ui32Word |= ((psGetSetCB->ui32U[ui32Index]      & 0x3FF) >> 2) << 16;
    ui32Word |= ((psGetSetCB->ui32V[ui32Index]      & 0x3FF) >> 2) << 24;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockARGB8332
******************************************************************************/
static
IMG_UINT32
pixel_BlockARGB8332(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_INT32               n;
    IMG_UINT32              ui32Word = 0;

    for (n = 1; n >= 0; n--)
    {
        ui32Word <<= 16;
		ui32Word |= (((psGetSetCB->ui32Alpha[ui32Index + n] >> 2) << 8) & 0xff00);
        ui32Word |= ((psGetSetCB->ui32Y[ui32Index + n] >> 2) & 0xe0);
        ui32Word |= ((psGetSetCB->ui32U[ui32Index + n] >> 5) & 0x1c);
        ui32Word |= ((psGetSetCB->ui32V[ui32Index + n] >> 8) & 0x03);
    }

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockYUV101010
******************************************************************************/
static
IMG_UINT32
pixel_BlockYUV101010(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =   psGetSetCB->ui32V[ui32Index] & 0x3FF;
    ui32Word |= (psGetSetCB->ui32U[ui32Index] & 0x3FF) << 10;
    ui32Word |= (psGetSetCB->ui32Y[ui32Index] & 0x3FF) << 20;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockAYUV4444
******************************************************************************/
static
IMG_UINT32
pixel_BlockAYUV4444(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =  ((psGetSetCB->ui32V[ui32Index]          >> 6) & 0xF) <<  0;
    ui32Word |= ((psGetSetCB->ui32U[ui32Index]          >> 6) & 0xF) <<  4;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index]          >> 6) & 0xF) <<  8;
    ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index]      >> 6) & 0xF) << 12;
    ui32Word |= ((psGetSetCB->ui32V[ui32Index + 1]      >> 6) & 0xF) << 16;
    ui32Word |= ((psGetSetCB->ui32U[ui32Index + 1]      >> 6) & 0xF) << 20;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index + 1]      >> 6) & 0xF) << 24;
    ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index + 1]  >> 6) & 0xF) << 28;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockAYUV8888
******************************************************************************/
static
IMG_UINT32
pixel_BlockAYUV8888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =  (psGetSetCB->ui32V[ui32Index] >> 2) & 0xFF;
    ui32Word |= ((psGetSetCB->ui32U[ui32Index] >> 2) & 0xFF) << 8;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index] >> 2) & 0xFF) << 16;
    ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index] >>2) & 0xFF) << 24;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockUYVY8888
******************************************************************************/
static
IMG_UINT32
pixel_BlockUYVY8888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =   (psGetSetCB->ui32U[ui32Index] >> 2) & 0xFF;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index] >> 2) & 0xFF) << 8;
    ui32Word |= ((psGetSetCB->ui32V[ui32Index] >> 2) & 0xFF) << 16;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index + 1] >> 2) & 0xFF) << 24;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockVYUY8888
******************************************************************************/
static
IMG_UINT32
pixel_BlockVYUY8888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =   (psGetSetCB->ui32V[ui32Index] >> 2) & 0xFF;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index] >> 2) & 0xFF) << 8;
    ui32Word |= ((psGetSetCB->ui32U[ui32Index] >> 2) & 0xFF) << 16;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index + 1] >> 2) & 0xFF) << 24;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockYVYU8888
******************************************************************************/
static
IMG_UINT32
pixel_BlockYVYU8888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =   (psGetSetCB->ui32Y[ui32Index] >> 2) & 0xFF;
    ui32Word |= ((psGetSetCB->ui32V[ui32Index] >> 2) & 0xFF) << 8;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index + 1] >> 2) & 0xFF) << 16;
    ui32Word |= ((psGetSetCB->ui32U[ui32Index] >> 2) & 0xFF) << 24;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockYUYV8888
******************************************************************************/
static
IMG_UINT32
pixel_BlockYUYV8888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =   (psGetSetCB->ui32Y[ui32Index] >> 2) & 0xFF;
    ui32Word |= ((psGetSetCB->ui32U[ui32Index] >> 2) & 0xFF) << 8;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index + 1] >> 2) & 0xFF) << 16;
    ui32Word |= ((psGetSetCB->ui32V[ui32Index] >> 2) & 0xFF) << 24;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockVYAUYA8888
******************************************************************************/
static
void
pixel_BlockVYAUYA8888(
    PIXEL_sGetSetCB *psGetSetCB
    )
{
	IMG_UINT8 *				pDstData;
    IMG_UINT32				offset;
	IMG_UINT32				ui32Val				= 0;
    IMG_UINT32				yIndex				= 0;
    IMG_UINT32				uIndex				= 0;
    IMG_UINT32				vIndex				= 0;
    IMG_UINT32				aIndex				= 0;
	PIXEL_sInfo	*			psBufInfo			= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

	IMG_ASSERT((psBufInfo->ui32YBytesInBOP % 6) == 0);

    pDstData = (IMG_UINT8 *)PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvYBufAddr);

    yIndex = uIndex = vIndex = aIndex = 0;
	for (offset = 0; offset < psBufInfo->ui32YBytesInBOP; offset++)
    {
        switch (offset % 6)
        {
            case 0:
                /* V component */
                ui32Val = psGetSetCB->ui32V[vIndex];
                vIndex += 2;
                break;
            case 1:
                /* Y component */
                ui32Val = psGetSetCB->ui32Y[yIndex++];
                break;
            case 2:
                /* A component */
                ui32Val = psGetSetCB->ui32Alpha[aIndex++];
                break;
            case 3:
                /* U component */
                ui32Val = psGetSetCB->ui32U[uIndex];
                uIndex += 2;
                break;
            case 4:
                /* Y component */
                ui32Val = psGetSetCB->ui32Y[yIndex++];
                break;
            case 5:
                /* A component */
                ui32Val = psGetSetCB->ui32Alpha[aIndex++];
                break;
        }
        *pDstData++ = ui32Val >> 2;
    }
}

/*!
******************************************************************************
@Function               pixel_BlockPL12IMC2
******************************************************************************/
static
void
pixel_BlockPL12IMC2(
    PIXEL_sGetSetCB *psGetSetCB
    )
{
    IMG_UINT32				offset;
    IMG_UINT8 *				pDstData;
	PIXEL_sInfo	*			psBufInfo			= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

    // copy the Y data
    pDstData = (IMG_UINT8 *) PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvYBufAddr);
	for (offset = 0; offset < psBufInfo->ui32YBytesInBOP; offset++)
    {
        *pDstData++ = (psGetSetCB->ui32Y[offset]) >> 2;
    }

    // copy the U data
    pDstData = (IMG_UINT8 *) PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvUVBufAddr);
	for (offset = 0; offset < psBufInfo->ui32UVBytesInBOP; offset++)
    {
        *pDstData++ = (psGetSetCB->ui32U[offset]) >> 2;
    }

    // copy the V data
    pDstData = (IMG_UINT8 *) PIXEL_TWIDDLE_ADDRESS(psGetSetCB,(psGetSetCB->pvUVBufAddr + PIXEL_GET_UV_STRIDE(psGetSetCB)));
    for (offset = 0; offset < psBufInfo->ui32UVBytesInBOP; offset++)
    {
        *pDstData++ = (psGetSetCB->ui32V[offset]) >> 2;
    }
}


/*!
******************************************************************************
@Function               pixel_BlockPL12YV12
******************************************************************************/
static
void
pixel_BlockPL12YV12(    
	PIXEL_sGetSetCB *         psGetSetCB
)
{
	IMG_UINT32				offset;
    IMG_UINT8 *				pDstData;
	PIXEL_sInfo	*			psBufInfo			= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

    // copy the Y data
    pDstData = (IMG_UINT8 *) PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvYBufAddr);
	for (offset = 0; offset < psBufInfo->ui32YBytesInBOP; offset++)
    {
        *pDstData++ = (psGetSetCB->ui32Y[offset]) >> 2;
    }

    // copy the U data
    pDstData = (IMG_UINT8 *) PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvUVBufAddr);
	for (offset = 0; offset < psBufInfo->ui32UVBytesInBOP; offset++)
    {
        *pDstData++ = (psGetSetCB->ui32U[offset*2]) >> 2;
    }

    // copy the V data
    pDstData = (IMG_UINT8 *) PIXEL_TWIDDLE_ADDRESS(psGetSetCB,(psGetSetCB->pvUVBufAddr + + PIXEL_GET_UV_STRIDE(psGetSetCB) *  PIXEL_GET_UV_HEIGHT(psGetSetCB)));
    for (offset = 0; offset < psBufInfo->ui32UVBytesInBOP; offset++)
    {
        *pDstData++ = (psGetSetCB->ui32V[offset*2]) >> 2;
    }
}


/*!
******************************************************************************
@Function               pixel_BlockPL8YUV8
******************************************************************************/
static
void
pixel_BlockPL8YUV8(    
	PIXEL_sGetSetCB *         psGetSetCB
)
{
	IMG_UINT32				offset;
    IMG_UINT8 *				pDstData;
	PIXEL_sInfo	*			psBufInfo			= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

    // copy the Y data
    pDstData = (IMG_UINT8 *) PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvYBufAddr);
	for (offset = 0; offset < psBufInfo->ui32YBytesInBOP; offset++)
    {
        *pDstData++ = (psGetSetCB->ui32Y[offset]) >> 2;
    }

    // copy the U data
    pDstData = (IMG_UINT8 *) PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvUVBufAddr);
	for (offset = 0; offset < psBufInfo->ui32UVBytesInBOP; offset++)
    {
        *pDstData++ = (psGetSetCB->ui32U[offset*2]) >> 2;
    }

    // copy the V data
    IMG_ASSERT(psGetSetCB->pvVBufAddr != IMG_NULL);
    if(psGetSetCB->pvVBufAddr == IMG_NULL)
    {
        return;
    }

    pDstData = (IMG_UINT8 *) PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvVBufAddr);
    for (offset = 0; offset < psBufInfo->ui32UVBytesInBOP; offset++)
    {
        *pDstData++ = (psGetSetCB->ui32V[offset*2]) >> 2;
    }
}


/*!
******************************************************************************
@Function               pixel_BlockAYUV2101010
******************************************************************************/
static
IMG_UINT32
pixel_BlockAYUV2101010(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =   psGetSetCB->ui32V[ui32Index] & 0x3FF;
    ui32Word |= (psGetSetCB->ui32U[ui32Index] & 0x3FF) << 10;
    ui32Word |= (psGetSetCB->ui32Y[ui32Index] & 0x3FF) << 20;
    ui32Word |= ((psGetSetCB->ui32Alpha[ui32Index] & 0x3FF) >> 8) << 30;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockCVBS10
******************************************************************************/
static
IMG_UINT32
pixel_BlockCVBS10(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =   psGetSetCB->ui32Y[ui32Index]     & 0x3FF;
    ui32Word |= (psGetSetCB->ui32Y[ui32Index + 1] & 0x3FF) << 10;
    ui32Word |= (psGetSetCB->ui32Y[ui32Index + 2] & 0x3FF) << 20;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_Block420PL12YUV8And422PL12YUV8
******************************************************************************/
static
IMG_VOID
pixel_Block420PL12YUV8And422PL12YUV8(
    PIXEL_sGetSetCB   *psGetSetCB,
    IMG_UINT32      *pui32Word,
    IMG_UINT32      *pui32UVWord,
    IMG_UINT32      ui32Index
    )
{
    /* Block Y components */
    *pui32Word = ((psGetSetCB->ui32Y[ui32Index] >> 2) & 0xFF) ;
    *pui32Word |= ((psGetSetCB->ui32Y[ui32Index + 1] >> 2) & 0xFF) << 8;
    *pui32Word |= ((psGetSetCB->ui32Y[ui32Index + 2] >> 2) & 0xFF) << 16;
    *pui32Word |= ((psGetSetCB->ui32Y[ui32Index + 3] >> 2) & 0xFF) << 24;

    /* Block UV components */
    *pui32UVWord = ((psGetSetCB->ui32V[ui32Index] >> 2) & 0xFF) ;
    *pui32UVWord |= ((psGetSetCB->ui32U[ui32Index] >> 2) & 0xFF) << 8;
    *pui32UVWord |= ((psGetSetCB->ui32V[ui32Index + 2] >> 2) & 0xFF) << 16;
    *pui32UVWord |= ((psGetSetCB->ui32U[ui32Index + 2] >> 2) & 0xFF) << 24;
}

/*!
******************************************************************************
@Function               pixel_Block420PL12YVU8And422PL12YVU8
******************************************************************************/
static
IMG_VOID
pixel_Block420PL12YVU8And422PL12YVU8(
    PIXEL_sGetSetCB   *psGetSetCB,
    IMG_UINT32      *pui32Word,
    IMG_UINT32      *pui32UVWord,
    IMG_UINT32      ui32Index
    )
{
    /* Block Y components */
    *pui32Word = ((psGetSetCB->ui32Y[ui32Index] >> 2) & 0xFF) ;
    *pui32Word |= ((psGetSetCB->ui32Y[ui32Index + 1] >> 2) & 0xFF) << 8;
    *pui32Word |= ((psGetSetCB->ui32Y[ui32Index + 2] >> 2) & 0xFF) << 16;
    *pui32Word |= ((psGetSetCB->ui32Y[ui32Index + 3] >> 2) & 0xFF) << 24;

    /* Block UV components */
    *pui32UVWord = ((psGetSetCB->ui32U[ui32Index] >> 2) & 0xFF) ;
    *pui32UVWord |= ((psGetSetCB->ui32V[ui32Index] >> 2) & 0xFF) << 8;
    *pui32UVWord |= ((psGetSetCB->ui32U[ui32Index + 2] >> 2) & 0xFF) << 16;
    *pui32UVWord |= ((psGetSetCB->ui32V[ui32Index + 2] >> 2) & 0xFF) << 24;
}

/*!
******************************************************************************
@Function               pixel_Block420PL12YUV8_A8And422PL12YUV8_A8
******************************************************************************/
static
IMG_VOID
pixel_Block420PL12YUV8_A8And422PL12YUV8_A8(
    PIXEL_sGetSetCB   *psGetSetCB,
    IMG_UINT32      *pui32Word,
    IMG_UINT32      *pui32UVWord,
    IMG_UINT32      *pui32AlphaWord,
    IMG_UINT32      ui32Index
    )
{
    /* Block Y components */
    *pui32Word = ((psGetSetCB->ui32Y[ui32Index] >> 2) & 0xFF) ;
    *pui32Word |= ((psGetSetCB->ui32Y[ui32Index + 1] >> 2) & 0xFF) << 8;
    *pui32Word |= ((psGetSetCB->ui32Y[ui32Index + 2] >> 2) & 0xFF) << 16;
    *pui32Word |= ((psGetSetCB->ui32Y[ui32Index + 3] >> 2) & 0xFF) << 24;

    /* Block UV components */
    *pui32UVWord = ((psGetSetCB->ui32V[ui32Index] >> 2) & 0xFF) ;
    *pui32UVWord |= ((psGetSetCB->ui32U[ui32Index] >> 2) & 0xFF) << 8;
    *pui32UVWord |= ((psGetSetCB->ui32V[ui32Index + 2] >> 2) & 0xFF) << 16;
    *pui32UVWord |= ((psGetSetCB->ui32U[ui32Index + 2] >> 2) & 0xFF) << 24;

    /* Block Alpha components */
    *pui32AlphaWord = ((psGetSetCB->ui32Alpha[ui32Index] >> 2) & 0xFF) ;
    *pui32AlphaWord |= ((psGetSetCB->ui32Alpha[ui32Index + 1] >> 2) & 0xFF) << 8;
    *pui32AlphaWord |= ((psGetSetCB->ui32Alpha[ui32Index + 2] >> 2) & 0xFF) << 16;
    *pui32AlphaWord |= ((psGetSetCB->ui32Alpha[ui32Index + 3] >> 2) & 0xFF) << 24;
}

/*!
******************************************************************************
@Function               pixel_Block411PL12YVU8
******************************************************************************/
static
IMG_VOID
pixel_Block411PL12YVU8(
    PIXEL_sGetSetCB   *psGetSetCB,
    IMG_UINT32      *pui32WordA,
	IMG_UINT32      *pui32WordB,
    IMG_UINT32      *pui32UVWord,
    IMG_UINT32      ui32Index
    )
{
    /* Block Y components */
    *pui32WordA = ((psGetSetCB->ui32Y[ui32Index] >> 2) & 0xFF) ;
    *pui32WordA |= ((psGetSetCB->ui32Y[ui32Index + 1] >> 2) & 0xFF) << 8;
    *pui32WordA |= ((psGetSetCB->ui32Y[ui32Index + 2] >> 2) & 0xFF) << 16;
    *pui32WordA |= ((psGetSetCB->ui32Y[ui32Index + 3] >> 2) & 0xFF) << 24;

    *pui32WordB = ((psGetSetCB->ui32Y[ui32Index + 4] >> 2) & 0xFF) ;
    *pui32WordB |= ((psGetSetCB->ui32Y[ui32Index + 5] >> 2) & 0xFF) << 8;
    *pui32WordB |= ((psGetSetCB->ui32Y[ui32Index + 6] >> 2) & 0xFF) << 16;
    *pui32WordB |= ((psGetSetCB->ui32Y[ui32Index + 7] >> 2) & 0xFF) << 24;

    /* Block UV components */
    *pui32UVWord = ((psGetSetCB->ui32U[ui32Index] >> 2) & 0xFF) ;
    *pui32UVWord |= ((psGetSetCB->ui32V[ui32Index] >> 2) & 0xFF) << 8;
    *pui32UVWord |= ((psGetSetCB->ui32U[ui32Index + 4] >> 2) & 0xFF) << 16;
    *pui32UVWord |= ((psGetSetCB->ui32V[ui32Index + 4] >> 2) & 0xFF) << 24;
}

/*!
******************************************************************************
@Function               pixel_BlockPL12Y8
******************************************************************************/
static
IMG_UINT32
pixel_BlockPL12Y8(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =  (psGetSetCB->ui32Y[ui32Index] >> 2) & 0xFF;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index + 1] >> 2) & 0xFF) << 8;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index + 2] >> 2) & 0xFF) << 16;
    ui32Word |= ((psGetSetCB->ui32Y[ui32Index + 3] >> 2) & 0xFF) << 24;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockPL12Y10
******************************************************************************/
static
IMG_UINT32
pixel_BlockPL12Y10(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32              ui32Index
    )
{
    IMG_UINT32              ui32Word;

    ui32Word =  psGetSetCB->ui32Y[ui32Index] & 0x3FF;
    ui32Word |= (psGetSetCB->ui32Y[ui32Index + 1] & 0x3FF) << 10;
    ui32Word |= (psGetSetCB->ui32Y[ui32Index + 2] & 0x3FF) << 20;

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockL16
******************************************************************************/
static
IMG_UINT32
pixel_BlockL16(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32				  ui32Index
    )
{
    IMG_UINT32              ui32Word;

	/* To convert from internal 10 bit format to 16 bit format, shift the 10 bits up 6 places, and then */
	/* duplicate the six most significant bits in the bottom six bits.									*/
    ui32Word =  (((psGetSetCB->ui32Y[ui32Index] & 0x3FF) << 6) + ((psGetSetCB->ui32Y[ui32Index] & 0x3F) >> 4));
    ui32Word |=  ((((psGetSetCB->ui32Y[ui32Index+1] & 0x3FF) << 6) + ((psGetSetCB->ui32Y[ui32Index+1] & 0x3F) >> 4)) << 16);

    return ui32Word;
}

/*!
******************************************************************************
@Function               pixel_BlockL32
******************************************************************************/
static
IMG_UINT32
pixel_BlockL32(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32				  ui32Index
    )
{
    IMG_UINT32              ui32Word;

	/* To convert from internal 10 bit format to 32 bit format, duplicate the 10 bits three times	*/
	/* and then fill the bottom two bits with the most significant two bits from the original ten.	*/	
    ui32Word =  (((psGetSetCB->ui32Y[ui32Index] & 0x3FF) << 22) + 
				 ((psGetSetCB->ui32Y[ui32Index] & 0x3FF) << 12) +
				 ((psGetSetCB->ui32Y[ui32Index] & 0x3FF) << 2) +
				 ((psGetSetCB->ui32Y[ui32Index] & 0x3)));

    return ui32Word;
}

#if (!defined (METAG) && !defined (MTXG)&& !defined(IMG_KERNEL_MODULE))
	/*!
	******************************************************************************
	@Function               pixel_BlockF32
	******************************************************************************/
	static
	IMG_UINT32
	pixel_BlockF32(
	    PIXEL_sGetSetCB *         psGetSetCB,
	    IMG_UINT32				  ui32Index
	    )
	{
	    IMG_UINT32              ui32Word;
		IMG_uFLUINT32			uWord;
	
		uWord.fx = (IMG_FLOAT) (psGetSetCB->ui32Y[ui32Index] & 0x3FF);
		ui32Word = uWord.ui32x;
	
		return ui32Word;
	}

	/*!
	******************************************************************************
	@Function               pixel_BlockF16
	******************************************************************************/
	static
	IMG_UINT32
	pixel_BlockF16(
	    PIXEL_sGetSetCB *         psGetSetCB,
	    IMG_UINT32				  ui32Index
	    )
	{
	    IMG_UINT32              ui32Word;
		IMG_FLOAT				fWord;
		IMG_UINT16				ui16Word0, ui16Word1;
	
		fWord = (IMG_FLOAT) (((psGetSetCB->ui32Y[ui32Index] & 0x3FF) << 6) + (psGetSetCB->ui32Y[ui32Index] & 0x3F));
		ui16Word0 = ConvertIEEE32ToFloat16(fWord,IMG_TRUE);
	
		fWord = (IMG_FLOAT) (((psGetSetCB->ui32Y[ui32Index+1] & 0x3FF) << 6) + (psGetSetCB->ui32Y[ui32Index+1] & 0x3F));
		ui16Word1 = ConvertIEEE32ToFloat16(fWord,IMG_TRUE);
	
		ui32Word = (ui16Word1 << 16) + ui16Word0;
	
		return ui32Word;
	}
#endif

/*!
******************************************************************************
@Function               pixel_BlockNextBOPs

@Description
This function blocks the next block-of-pixels.
******************************************************************************/
IMG_VOID
pixel_BlockNextBOPs(
    PIXEL_sGetSetCB *         psGetSetCB
    )
{
    IMG_UINT32              ui32Word0 = 0;
    IMG_UINT32              ui32Word1 = 0;
    IMG_UINT32              ui32Word2 = 0;
    IMG_UINT32              ui32Word3 = 0;

    IMG_UINT32              ui32UVWord0 = 0;
    IMG_UINT32              ui32UVWord1 = 0;
    IMG_UINT32              ui32UVWord2 = 0;
    IMG_UINT32              ui32UVWord3 = 0;

    IMG_UINT32              ui32AlphaWord0 = 0;
    IMG_UINT32              ui32AlphaWord1 = 0;
    IMG_UINT32              ui32AlphaWord2 = 0;
    IMG_UINT32              ui32AlphaWord3 = 0;
    IMG_UINT32	*			ptr;
	PIXEL_sInfo	*			psBufInfo			= IMG_NULL;
    IMG_BOOL                bDone = IMG_FALSE;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

    /* Branch on pixel format...*/
	switch (psGetSetCB->ePixelColourFormat)
    {
        case IMG_PIXFMT_CLUT1:
            ui32Word0 = pixel_BlockCLUT(psGetSetCB, 1, 0, IMG_FALSE, 0);
            break;

        case IMG_PIXFMT_CLUT2:
            ui32Word0 = pixel_BlockCLUT(psGetSetCB, 2, 0, IMG_FALSE, 0);
            ui32Word1 = pixel_BlockCLUT(psGetSetCB, 2, 0, IMG_FALSE, 16);
            break;

        case IMG_PIXFMT_CLUT4:
            ui32Word0 = pixel_BlockCLUT(psGetSetCB, 4, 0, IMG_FALSE, 0);
            ui32Word1 = pixel_BlockCLUT(psGetSetCB, 4, 0, IMG_FALSE, 8);
            ui32Word2 = pixel_BlockCLUT(psGetSetCB, 4, 0, IMG_FALSE, 16);
            ui32Word3 = pixel_BlockCLUT(psGetSetCB, 4, 0, IMG_FALSE, 24);
            break;
            
        case IMG_PIXFMT_I4A4:
            ui32Word0 = pixel_BlockCLUT(psGetSetCB, 4, 4, IMG_FALSE, 0);
            ui32Word1 = pixel_BlockCLUT(psGetSetCB, 4, 4, IMG_FALSE, 4);
            ui32Word2 = pixel_BlockCLUT(psGetSetCB, 4, 4, IMG_FALSE, 8);
            ui32Word3 = pixel_BlockCLUT(psGetSetCB, 4, 4, IMG_FALSE, 12);
            break;     
            
        case IMG_PIXFMT_I8A8:
            ui32Word0 = pixel_BlockCLUT(psGetSetCB, 8, 8, IMG_FALSE, 0);
            ui32Word1 = pixel_BlockCLUT(psGetSetCB, 8, 8, IMG_FALSE, 2);
            ui32Word2 = pixel_BlockCLUT(psGetSetCB, 8, 8, IMG_FALSE, 4);
            ui32Word3 = pixel_BlockCLUT(psGetSetCB, 8, 8, IMG_FALSE, 6);
            break; 

        case IMG_PIXFMT_A8I8:
            ui32Word0 = pixel_BlockCLUT(psGetSetCB, 8, 8, IMG_TRUE, 0);
            ui32Word1 = pixel_BlockCLUT(psGetSetCB, 8, 8, IMG_TRUE, 2);
            ui32Word2 = pixel_BlockCLUT(psGetSetCB, 8, 8, IMG_TRUE, 4);
            ui32Word3 = pixel_BlockCLUT(psGetSetCB, 8, 8, IMG_TRUE, 6);
            break; 

        case IMG_PIXFMT_RGB8:
            ui32Word0 = pixel_BlockCLUT(psGetSetCB, 8, 0, IMG_FALSE, 0);
            ui32Word1 = pixel_BlockCLUT(psGetSetCB, 8, 0, IMG_FALSE, 4);
            ui32Word2 = pixel_BlockCLUT(psGetSetCB, 8, 0, IMG_FALSE, 8);
            ui32Word3 = pixel_BlockCLUT(psGetSetCB, 8, 0, IMG_FALSE, 12);
            break;

        case IMG_PIXFMT_RGB555:
        case IMG_PIXFMT_ARGB1555:
            /*! 15-bit RGB (R=5, G=5, B=5).             */
            /*! 16-bit RGB (R=5, G=5, B=5) + 1-bit alpha.*/
            ui32Word0 = pixel_BlockRGB555AndARGB1555 (psGetSetCB, 0);
            ui32Word1 = pixel_BlockRGB555AndARGB1555 (psGetSetCB, 2);
            ui32Word2 = pixel_BlockRGB555AndARGB1555 (psGetSetCB, 4);
            ui32Word3 = pixel_BlockRGB555AndARGB1555 (psGetSetCB, 6);
            break;

        case IMG_PIXFMT_ARGB4444:
            /*! 16-bit RGB (R=4, G=4, B=4) + 4-bit alpha.*/
            ui32Word0 = pixel_BlockARGB4444 (psGetSetCB, 0);
            ui32Word1 = pixel_BlockARGB4444 (psGetSetCB, 2);
            ui32Word2 = pixel_BlockARGB4444 (psGetSetCB, 4);
            ui32Word3 = pixel_BlockARGB4444 (psGetSetCB, 6);
            break;

		case IMG_PIXFMT_ARGB8332:
            /*! 16-bit RGB (R=3, G=3, B=2) + 8-bit alpha.*/
            ui32Word0 = pixel_BlockARGB8332 (psGetSetCB, 0);
            ui32Word1 = pixel_BlockARGB8332 (psGetSetCB, 2);
            ui32Word2 = pixel_BlockARGB8332 (psGetSetCB, 4);
            ui32Word3 = pixel_BlockARGB8332 (psGetSetCB, 6);
            break;

        case IMG_PIXFMT_RGB565:
            /*! 16-bit RGB (R=5, G=6, B=5).             */
            ui32Word0 = pixel_BlockRGB565 (psGetSetCB, 0);
            ui32Word1 = pixel_BlockRGB565 (psGetSetCB, 2);
            ui32Word2 = pixel_BlockRGB565 (psGetSetCB, 4);
            ui32Word3 = pixel_BlockRGB565 (psGetSetCB, 6);
            break;

        case IMG_PIXFMT_RGB332:
            /*! 8-bit RGB (R=3, G=3, B=2).              */
            ui32Word0 = pixel_BlockRGB332(psGetSetCB, 0);
            ui32Word1 = pixel_BlockRGB332(psGetSetCB, 4);
            ui32Word2 = pixel_BlockRGB332(psGetSetCB, 8);
            ui32Word3 = pixel_BlockRGB332(psGetSetCB, 12);
            break;

        case IMG_PIXFMT_RGB888:
        case IMG_PIXFMT_YUV888:
            /* Compact RGB 4:4:4 8-bit values */
            /* Y==R, U==G, V==B */
            ui32Word0 =   (psGetSetCB->ui32V[0] & 0x3FF) >> 2;
            ui32Word0 |= ((psGetSetCB->ui32U[0] & 0x3FF) >> 2) << 8;
            ui32Word0 |= ((psGetSetCB->ui32Y[0] & 0x3FF) >> 2) << 16;
            ui32Word0 |= ((psGetSetCB->ui32V[1] & 0x3FF) >> 2) << 24;

            ui32Word1 =   (psGetSetCB->ui32U[1] & 0x3FF) >> 2;
            ui32Word1 |= ((psGetSetCB->ui32Y[1] & 0x3FF) >> 2) << 8;
            ui32Word1 |= ((psGetSetCB->ui32V[2] & 0x3FF) >> 2) << 16;
            ui32Word1 |= ((psGetSetCB->ui32U[2] & 0x3FF) >> 2) << 24;

            ui32Word2 =   (psGetSetCB->ui32Y[2] & 0x3FF) >> 2;
            ui32Word2 |= ((psGetSetCB->ui32V[3] & 0x3FF) >> 2) << 8;
            ui32Word2 |= ((psGetSetCB->ui32U[3] & 0x3FF) >> 2) << 16;
            ui32Word2 |= ((psGetSetCB->ui32Y[3] & 0x3FF) >> 2) << 24;
            break;

        case IMG_PIXFMT_ARGB8888:
            /*! 24-bit RGB + 8-bit alpha.               */
            ui32Word0 = pixel_BlockARGB8888 (psGetSetCB, 0);
            ui32Word1 = pixel_BlockARGB8888 (psGetSetCB, 1);
            ui32Word2 = pixel_BlockARGB8888 (psGetSetCB, 2);
            ui32Word3 = pixel_BlockARGB8888 (psGetSetCB, 3);
            break;

		case IMG_PIXFMT_ABGR8888:
            /*! 24-bit RGB + 8-bit alpha.               */
            ui32Word0 = pixel_BlockABGR8888 (psGetSetCB, 0);
            ui32Word1 = pixel_BlockABGR8888 (psGetSetCB, 1);
            ui32Word2 = pixel_BlockABGR8888 (psGetSetCB, 2);
            ui32Word3 = pixel_BlockABGR8888 (psGetSetCB, 3);
            break;

		case IMG_PIXFMT_BGRA8888:
            /*! 24-bit RGB + 8-bit alpha.               */
            ui32Word0 = pixel_BlockBGRA8888 (psGetSetCB, 0);
            ui32Word1 = pixel_BlockBGRA8888 (psGetSetCB, 1);
            ui32Word2 = pixel_BlockBGRA8888 (psGetSetCB, 2);
            ui32Word3 = pixel_BlockBGRA8888 (psGetSetCB, 3);
            break;

        case IMG_PIXFMT_UYVY10101010:
            /* Compact the YUV 4:2:2 ten bit values */
            ui32Word0 = (psGetSetCB->ui32V[0] & 0x3FF);
            ui32Word0 |= (psGetSetCB->ui32Y[0] & 0x3FF) << 10;
            ui32Word0 |= (psGetSetCB->ui32U[0] & 0x3FF) << 20;

            ui32Word1 = (psGetSetCB->ui32Y[1] & 0x3FF);
            ui32Word1 |= (psGetSetCB->ui32V[2] & 0x3FF) << 10;
            ui32Word1 |= (psGetSetCB->ui32Y[2] & 0x3FF) << 20;

            ui32Word2 = (psGetSetCB->ui32U[2] & 0x3FF);
            ui32Word2 |= (psGetSetCB->ui32Y[3] & 0x3FF) << 10;
            ui32Word2 |= (psGetSetCB->ui32V[4] & 0x3FF) << 20;


            ui32Word3 = (psGetSetCB->ui32Y[4] & 0x3FF);
            ui32Word3 |= (psGetSetCB->ui32U[4] & 0x3FF) << 10;
            ui32Word3 |= (psGetSetCB->ui32Y[5] & 0x3FF) << 20;
            break;

        case IMG_PIXFMT_YUV101010:
            /* Compact the YUV 4:4:4 ten bit values */
            ui32Word0 = pixel_BlockYUV101010 (psGetSetCB, 0);
            ui32Word1 = pixel_BlockYUV101010 (psGetSetCB, 1);
            ui32Word2 = pixel_BlockYUV101010 (psGetSetCB, 2);
            ui32Word3 = pixel_BlockYUV101010 (psGetSetCB, 3);
            break;

        case IMG_PIXFMT_AYUV4444:
            /* Compact the YUVA 4:4:4 4-bit values */
            ui32Word0 = pixel_BlockAYUV4444 (psGetSetCB, 0);
            ui32Word1 = pixel_BlockAYUV4444 (psGetSetCB, 2);
            ui32Word2 = pixel_BlockAYUV4444 (psGetSetCB, 4);
            ui32Word3 = pixel_BlockAYUV4444 (psGetSetCB, 6);
            break;

        case IMG_PIXFMT_UYVY8888:
            /*! YUV 4:2:2 8-bit per component.          */
            ui32Word0 = pixel_BlockUYVY8888(psGetSetCB, 0);
            ui32Word1 = pixel_BlockUYVY8888(psGetSetCB, 2);
            ui32Word2 = pixel_BlockUYVY8888(psGetSetCB, 4);
            ui32Word3 = pixel_BlockUYVY8888(psGetSetCB, 6);
            break;
            
        case IMG_PIXFMT_VYUY8888:
            /*! YUV 4:2:2 8-bit per component.          */
            ui32Word0 = pixel_BlockVYUY8888(psGetSetCB, 0);
            ui32Word1 = pixel_BlockVYUY8888(psGetSetCB, 2);
            ui32Word2 = pixel_BlockVYUY8888(psGetSetCB, 4);
            ui32Word3 = pixel_BlockVYUY8888(psGetSetCB, 6);
            break;
            
        case IMG_PIXFMT_YVYU8888:
            /*! YUV 4:2:2 8-bit per component.          */
            ui32Word0 = pixel_BlockYVYU8888(psGetSetCB, 0);
            ui32Word1 = pixel_BlockYVYU8888(psGetSetCB, 2);
            ui32Word2 = pixel_BlockYVYU8888(psGetSetCB, 4);
            ui32Word3 = pixel_BlockYVYU8888(psGetSetCB, 6);
            break;                        

        case IMG_PIXFMT_YUYV8888:
            /*! YUV 4:2:2 8-bit per component.          */
            ui32Word0 = pixel_BlockYUYV8888(psGetSetCB, 0);
            ui32Word1 = pixel_BlockYUYV8888(psGetSetCB, 2);
            ui32Word2 = pixel_BlockYUYV8888(psGetSetCB, 4);
            ui32Word3 = pixel_BlockYUYV8888(psGetSetCB, 6);
            break; 

        case IMG_PIXFMT_VYAUYA8888:
            /* Compact the YUVA 4:2:2:4 8-bit values. */
            pixel_BlockVYAUYA8888(psGetSetCB);
            bDone = IMG_TRUE;
            break;

        case IMG_PIXFMT_PL12IMC2:
            /* Compact the YUV 4:2:0 8-bit values. */
            pixel_BlockPL12IMC2(psGetSetCB);
            bDone = IMG_TRUE;
            break;
		
		case IMG_PIXFMT_PL12YV12:
			pixel_BlockPL12YV12(psGetSetCB);
            bDone = IMG_TRUE;
			break;

        case IMG_PIXFMT_AYUV8888:
            /* Compact the YUVA 4:4:4 8-bit values */
            ui32Word0 = pixel_BlockAYUV8888 (psGetSetCB, 0);
            ui32Word1 = pixel_BlockAYUV8888 (psGetSetCB, 1);
            ui32Word2 = pixel_BlockAYUV8888 (psGetSetCB, 2);
            ui32Word3 = pixel_BlockAYUV8888 (psGetSetCB, 3);
            break;

        case IMG_PIXFMT_AYUV2101010:
            /* Compact the YUVA 4:4:4 ten bit values */
            ui32Word0 = pixel_BlockAYUV2101010 (psGetSetCB, 0);
            ui32Word1 = pixel_BlockAYUV2101010 (psGetSetCB, 1);
            ui32Word2 = pixel_BlockAYUV2101010 (psGetSetCB, 2);
            ui32Word3 = pixel_BlockAYUV2101010 (psGetSetCB, 3);
            break;

        case IMG_PIXFMT_CVBS10:
            /* Compact the CVBS10 values */
            ui32Word0 = pixel_BlockCVBS10 (psGetSetCB, 0);
            ui32Word1 = pixel_BlockCVBS10 (psGetSetCB, 3);
            ui32Word2 = pixel_BlockCVBS10 (psGetSetCB, 6);
            ui32Word3 = pixel_BlockCVBS10 (psGetSetCB, 9);
            break;

        case IMG_PIXFMT_A4:
            ui32Word0 = pixel_BlockA4 (psGetSetCB, 0);
            ui32Word1 = pixel_BlockA4 (psGetSetCB, 4);
            ui32Word2 = pixel_BlockA4 (psGetSetCB, 8);
            ui32Word3 = pixel_BlockA4 (psGetSetCB, 12);
            break;

        case IMG_PIXFMT_A8:
            ui32Word0 = pixel_BlockA8 (psGetSetCB, 0);
            ui32Word1 = pixel_BlockA8 (psGetSetCB, 4);
            ui32Word2 = pixel_BlockA8 (psGetSetCB, 8);
            ui32Word3 = pixel_BlockA8 (psGetSetCB, 12);
            break;

        case IMG_PIXFMT_420PL12YUV10:
        case IMG_PIXFMT_422PL12YUV10:
            /*! Compact the YUV 4:2:X 10-bit values */
            ui32Word0 = (psGetSetCB->ui32Y[0] & 0x3FF);
            ui32Word0 |= (psGetSetCB->ui32Y[1] & 0x3FF) << 10;
            ui32Word0 |= (psGetSetCB->ui32Y[2] & 0x3FF) << 20;

            ui32Word1 = (psGetSetCB->ui32Y[3] & 0x3FF);
            ui32Word1 |= (psGetSetCB->ui32Y[4] & 0x3FF) << 10;
            ui32Word1 |= (psGetSetCB->ui32Y[5] & 0x3FF) << 20;

            ui32Word2 = (psGetSetCB->ui32Y[6] & 0x3FF);
            ui32Word2 |= (psGetSetCB->ui32Y[7] & 0x3FF) << 10;
            ui32Word2 |= (psGetSetCB->ui32Y[8] & 0x3FF) << 20;

            ui32Word3 = (psGetSetCB->ui32Y[9] & 0x3FF);
            ui32Word3 |= (psGetSetCB->ui32Y[10] & 0x3FF) << 10;
            ui32Word3 |= (psGetSetCB->ui32Y[11] & 0x3FF) << 20;

            ui32UVWord0 = (psGetSetCB->ui32V[0] & 0x3FF);
            ui32UVWord0 |= (psGetSetCB->ui32U[0] & 0x3FF) << 10;
            ui32UVWord0 |= (psGetSetCB->ui32V[2] & 0x3FF) << 20;

            ui32UVWord1 = (psGetSetCB->ui32U[2] & 0x3FF);
            ui32UVWord1 |= (psGetSetCB->ui32V[4] & 0x3FF) << 10;
            ui32UVWord1 |= (psGetSetCB->ui32U[4] & 0x3FF) << 20;

            ui32UVWord2 = (psGetSetCB->ui32V[6] & 0x3FF);
            ui32UVWord2 |= (psGetSetCB->ui32U[6] & 0x3FF) << 10;
            ui32UVWord2 |= (psGetSetCB->ui32V[8] & 0x3FF) << 20;

            ui32UVWord3 = (psGetSetCB->ui32U[8] & 0x3FF);
            ui32UVWord3 |= (psGetSetCB->ui32V[10] & 0x3FF) << 10;
            ui32UVWord3 |= (psGetSetCB->ui32U[10] & 0x3FF) << 20;

            break;

        case IMG_PIXFMT_420PL12YVU10:
        case IMG_PIXFMT_422PL12YVU10:
            /*! Compact the YUV 4:2:X 10-bit values */
            ui32Word0 = (psGetSetCB->ui32Y[0] & 0x3FF);
            ui32Word0 |= (psGetSetCB->ui32Y[1] & 0x3FF) << 10;
            ui32Word0 |= (psGetSetCB->ui32Y[2] & 0x3FF) << 20;

            ui32Word1 = (psGetSetCB->ui32Y[3] & 0x3FF);
            ui32Word1 |= (psGetSetCB->ui32Y[4] & 0x3FF) << 10;
            ui32Word1 |= (psGetSetCB->ui32Y[5] & 0x3FF) << 20;

            ui32Word2 = (psGetSetCB->ui32Y[6] & 0x3FF);
            ui32Word2 |= (psGetSetCB->ui32Y[7] & 0x3FF) << 10;
            ui32Word2 |= (psGetSetCB->ui32Y[8] & 0x3FF) << 20;

            ui32Word3 = (psGetSetCB->ui32Y[9] & 0x3FF);
            ui32Word3 |= (psGetSetCB->ui32Y[10] & 0x3FF) << 10;
            ui32Word3 |= (psGetSetCB->ui32Y[11] & 0x3FF) << 20;

            ui32UVWord0 = (psGetSetCB->ui32U[0] & 0x3FF);
            ui32UVWord0 |= (psGetSetCB->ui32V[0] & 0x3FF) << 10;
            ui32UVWord0 |= (psGetSetCB->ui32U[2] & 0x3FF) << 20;

            ui32UVWord1 = (psGetSetCB->ui32V[2] & 0x3FF);
            ui32UVWord1 |= (psGetSetCB->ui32U[4] & 0x3FF) << 10;
            ui32UVWord1 |= (psGetSetCB->ui32V[4] & 0x3FF) << 20;

            ui32UVWord2 = (psGetSetCB->ui32U[6] & 0x3FF);
            ui32UVWord2 |= (psGetSetCB->ui32V[6] & 0x3FF) << 10;
            ui32UVWord2 |= (psGetSetCB->ui32U[8] & 0x3FF) << 20;

            ui32UVWord3 = (psGetSetCB->ui32V[8] & 0x3FF);
            ui32UVWord3 |= (psGetSetCB->ui32U[10] & 0x3FF) << 10;
            ui32UVWord3 |= (psGetSetCB->ui32V[10] & 0x3FF) << 20;

            break;

        case IMG_PIXFMT_420PL8YUV8:
        case IMG_PIXFMT_422PL8YUV8:
           	pixel_BlockPL8YUV8(psGetSetCB);
            bDone = IMG_TRUE;
            break;

        case IMG_PIXFMT_420PL8YUV10:
        case IMG_PIXFMT_422PL8YUV10:
            /*! Compact the YUV 4:2:X 10-bit values */
            ui32Word0 = (psGetSetCB->ui32Y[0] & 0x3FF);
            ui32Word0 |= (psGetSetCB->ui32Y[1] & 0x3FF) << 10;
            ui32Word0 |= (psGetSetCB->ui32Y[2] & 0x3FF) << 20;

            ui32Word1 = (psGetSetCB->ui32Y[3] & 0x3FF);
            ui32Word1 |= (psGetSetCB->ui32Y[4] & 0x3FF) << 10;
            ui32Word1 |= (psGetSetCB->ui32Y[5] & 0x3FF) << 20;

            ui32Word2 = (psGetSetCB->ui32Y[6] & 0x3FF);
            ui32Word2 |= (psGetSetCB->ui32Y[7] & 0x3FF) << 10;
            ui32Word2 |= (psGetSetCB->ui32Y[8] & 0x3FF) << 20;

            ui32Word3 = (psGetSetCB->ui32Y[9] & 0x3FF);
            ui32Word3 |= (psGetSetCB->ui32Y[10] & 0x3FF) << 10;
            ui32Word3 |= (psGetSetCB->ui32Y[11] & 0x3FF) << 20;

            ui32UVWord0 = (psGetSetCB->ui32U[0] & 0x3FF);
            ui32UVWord0 |= (psGetSetCB->ui32U[2] & 0x3FF) << 10;
            ui32UVWord0 |= (psGetSetCB->ui32U[4] & 0x3FF) << 20;

            ui32UVWord1 = (psGetSetCB->ui32U[6] & 0x3FF);
            ui32UVWord1 |= (psGetSetCB->ui32U[8] & 0x3FF) << 10;
            ui32UVWord1 |= (psGetSetCB->ui32U[10] & 0x3FF) << 20;

            ui32UVWord2 = (psGetSetCB->ui32V[0] & 0x3FF);
            ui32UVWord2 |= (psGetSetCB->ui32V[2] & 0x3FF) << 10;
            ui32UVWord2 |= (psGetSetCB->ui32V[4] & 0x3FF) << 20;

            ui32UVWord3 = (psGetSetCB->ui32V[6] & 0x3FF);
            ui32UVWord3 |= (psGetSetCB->ui32V[8] & 0x3FF) << 10;
            ui32UVWord3 |= (psGetSetCB->ui32V[10] & 0x3FF) << 20;

            break;

        case IMG_PIXFMT_420PL12YUV8:
        case IMG_PIXFMT_422PL12YUV8:
            /*! Compact the YUV 4:2:X 8-bit values */
            pixel_Block420PL12YUV8And422PL12YUV8(psGetSetCB, &ui32Word0, &ui32UVWord0, 0);
            pixel_Block420PL12YUV8And422PL12YUV8(psGetSetCB, &ui32Word1, &ui32UVWord1, 4);
            pixel_Block420PL12YUV8And422PL12YUV8(psGetSetCB, &ui32Word2, &ui32UVWord2, 8);
            pixel_Block420PL12YUV8And422PL12YUV8(psGetSetCB, &ui32Word3, &ui32UVWord3, 12);
            break;
            
        case IMG_PIXFMT_420PL12YVU8:
        case IMG_PIXFMT_422PL12YVU8:
            /*! Compact the YVU 4:2:X 8-bit values */
            pixel_Block420PL12YVU8And422PL12YVU8(psGetSetCB, &ui32Word0, &ui32UVWord0, 0);
            pixel_Block420PL12YVU8And422PL12YVU8(psGetSetCB, &ui32Word1, &ui32UVWord1, 4);
            pixel_Block420PL12YVU8And422PL12YVU8(psGetSetCB, &ui32Word2, &ui32UVWord2, 8);
            pixel_Block420PL12YVU8And422PL12YVU8(psGetSetCB, &ui32Word3, &ui32UVWord3, 12);
            break;   
            
        case IMG_PIXFMT_411PL12YVU8:
            /*! Compact the YVU 4:1:1 8-bit values */
            pixel_Block411PL12YVU8(psGetSetCB, &ui32Word0, &ui32Word1, &ui32UVWord0, 0);
			pixel_Block411PL12YVU8(psGetSetCB, &ui32Word2, &ui32Word3, &ui32UVWord1, 8);
            break;                     

        case IMG_PIXFMT_420PL12YUV8_A8:
        case IMG_PIXFMT_422PL12YUV8_A8:
            /*! Compact the AYUV 4:2:X 8-bit values */
            pixel_Block420PL12YUV8_A8And422PL12YUV8_A8(psGetSetCB, &ui32Word0, &ui32UVWord0, &ui32AlphaWord0, 0);
            pixel_Block420PL12YUV8_A8And422PL12YUV8_A8(psGetSetCB, &ui32Word1, &ui32UVWord1, &ui32AlphaWord1, 4);
            pixel_Block420PL12YUV8_A8And422PL12YUV8_A8(psGetSetCB, &ui32Word2, &ui32UVWord2, &ui32AlphaWord2, 8);
            pixel_Block420PL12YUV8_A8And422PL12YUV8_A8(psGetSetCB, &ui32Word3, &ui32UVWord3, &ui32AlphaWord3, 12);
            break;

        case IMG_PIXFMT_YUV8:
            /* Compact the YUV 8:8:8:8 8-bit values */
            ui32Word0 = pixel_BlockCLUT(psGetSetCB, 8, 0, IMG_FALSE, 0);
            ui32Word1 = pixel_BlockCLUT(psGetSetCB, 8, 0, IMG_FALSE, 4);
            ui32Word2 = pixel_BlockCLUT(psGetSetCB, 8, 0, IMG_FALSE, 8);
            ui32Word3 = pixel_BlockCLUT(psGetSetCB, 8, 0, IMG_FALSE, 12);
            break;

        case IMG_PIXFMT_PL12Y8:
            /*! Compact the Y only 8-bit values */
            ui32Word0 = pixel_BlockPL12Y8(psGetSetCB, 0);
            ui32Word1 = pixel_BlockPL12Y8(psGetSetCB, 4);
            ui32Word2 = pixel_BlockPL12Y8(psGetSetCB, 8);
            ui32Word3 = pixel_BlockPL12Y8(psGetSetCB, 12);
            break;

        case IMG_PIXFMT_PL12Y10:
            /*! Compact the Y only 10-bit values */
            ui32Word0 = pixel_BlockPL12Y10(psGetSetCB, 0);
            ui32Word1 = pixel_BlockPL12Y10(psGetSetCB, 3);
            ui32Word2 = pixel_BlockPL12Y10(psGetSetCB, 6);
            ui32Word3 = pixel_BlockPL12Y10(psGetSetCB, 9);
            break;

		case IMG_PIXFMT_L16:
			ui32Word0 = pixel_BlockL16(psGetSetCB, 0);
			ui32Word1 = pixel_BlockL16(psGetSetCB, 2);
			break;

		case IMG_PIXFMT_L32:
			ui32Word0 = pixel_BlockL32(psGetSetCB, 0);
			ui32Word1 = pixel_BlockL32(psGetSetCB, 1);
			break;

		#if (!defined (METAG) && !defined (MTXG)&& !defined(IMG_KERNEL_MODULE))
			case IMG_PIXFMT_F32:
				ui32Word0 = pixel_BlockF32(psGetSetCB, 0);
				ui32Word1 = pixel_BlockF32(psGetSetCB, 1);
				break;

			case IMG_PIXFMT_F16:
				ui32Word0 = pixel_BlockF16(psGetSetCB, 0);
				ui32Word1 = pixel_BlockF16(psGetSetCB, 2);
				break;
		#endif

		default:
            /* Pixel format not recognised */
            IMG_ASSERT(IMG_FALSE);
            break;
    }

	if (!bDone)
    {
        ptr = (IMG_UINT32 *)PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvYBufAddr);

        /* Save required no. of words */
		switch (psBufInfo->ui32YBytesInBOP)
        {
            case 16:
                ptr[0] = ui32Word0;
                ptr[1] = ui32Word1;
                ptr[2] = ui32Word2;
                ptr[3] = ui32Word3;
                break;
            case 12:
                ptr[0] = ui32Word0;
                ptr[1] = ui32Word1;
                ptr[2] = ui32Word2;
                break;
            case 8:
                ptr[0] = ui32Word0;
                ptr[1] = ui32Word1;
                break;
            case 4:
                ptr[0] = ui32Word0;
                break;
            default:
                /* Size not recognised */
                IMG_ASSERT(IMG_FALSE);
        }

		if ( psBufInfo->bIsPlanar )
        {
            ptr = (IMG_UINT32 *)PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvUVBufAddr);

            /* Save required no. of UV words */
			switch (psBufInfo->ui32UVBytesInBOP)
            {
                case 16:
                    ptr[0] = ui32UVWord0;
                    ptr[1] = ui32UVWord1;
                    ptr[2] = ui32UVWord2;
                    ptr[3] = ui32UVWord3;
                    break;
                case 8:
                    ptr[0] = ui32UVWord0;
                    ptr[1] = ui32UVWord1;
                    break;
                default:
                    /* Size not recognised */
                    IMG_ASSERT(IMG_FALSE);
            }
            if (psGetSetCB->pvVBufAddr != IMG_NULL)
            {
                ptr = (IMG_UINT32 *)PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvVBufAddr);

                /* Save required no. of UV words */
			    switch (psBufInfo->ui32UVBytesInBOP)
                {
                    case 8:
                        ptr[0] = ui32UVWord2;
                        ptr[1] = ui32UVWord3;
                        break;
                    default:
                        /* Size not recognised */
                        IMG_ASSERT(IMG_FALSE);
                }
            }
        }

		if ( psBufInfo->bHasAlpha )
        {
            ptr = (IMG_UINT32 *)PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvAlphaBufAddr);

            /* Save required no. of Alpha words */
			switch (psBufInfo->ui32AlphaBytesInBOP)
            {
                case 16:
                    ptr[0] = ui32AlphaWord0;
                    ptr[1] = ui32AlphaWord1;
                    ptr[2] = ui32AlphaWord2;
                    ptr[3] = ui32AlphaWord3;
                    break;
                default:
                    /* Size not recognised */
                    IMG_ASSERT(IMG_FALSE);
            }
        }
    }

    psGetSetCB->ui32PixelIndex  = 0;
	psGetSetCB->pvYBufAddr      += psBufInfo->ui32YBytesInBOP;
	psGetSetCB->pvUVBufAddr     += psBufInfo->ui32UVBytesInBOP;
    if (psGetSetCB->pvVBufAddr != IMG_NULL)
    {
	    psGetSetCB->pvVBufAddr     += psBufInfo->ui32UVBytesInBOP;
    }
	psGetSetCB->pvAlphaBufAddr  += psBufInfo->ui32AlphaBytesInBOP;
}

/*******************************************************************************************************/
/*******************************************************************************************************/

/*************************/
/* De-blocking functions */
/*************************/

/*!
******************************************************************************
@Function               pixel_DeblockCLUT
******************************************************************************/
static
IMG_VOID
pixel_DeblockCLUT(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word,
    IMG_UINT32              numColBits,
    IMG_UINT32				numAlphaBits,
    IMG_BOOL				bAlphaMostSignificant
    )
{
    IMG_UINT32		n;
    IMG_UINT32		w;
    IMG_UINT32		word;
    IMG_UINT32		ui32Cycles;
    IMG_UINT32		ui32ThisPixel;
	IMG_UINT32		numWords;
    IMG_UINT32		offset				= 0;
    IMG_UINT32		ColMask				= (1 << numColBits) - 1;
    IMG_UINT32		AlphaMask			= (1 << numAlphaBits) - 1;
	PIXEL_sInfo *		psBufInfo			= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

	IMG_ASSERT ( ((numColBits+numAlphaBits)%2) == 0 );
	
    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        ui32Cycles = (32 / (numColBits+numAlphaBits));
        
    	for (n = 0; n < ui32Cycles; n++)
    	{
	        //#undef BIT_ORDER_IS_LSB_TO_MSB
			//#ifdef BIT_ORDER_IS_LSB_TO_MSB        		
	        	ui32ThisPixel = word >> (n * (numColBits+numAlphaBits));
	        //#else
		     //   ui32ThisPixel = word >> ((ui32Cycles-n-1)*(numColBits+numAlphaBits));        
	        //#endif
    	
	    	if ( bAlphaMostSignificant == IMG_TRUE )
	    	{
	   	        psGetSetCB->ui32Y[offset]       = ui32ThisPixel & ColMask;
	        	ui32ThisPixel >>= numColBits;
	        	if ( numAlphaBits > 0 )
	        	{
	        		psGetSetCB->ui32Alpha[offset]   = ui32ThisPixel & AlphaMask;
	        	}
	        	else
	        	{
	        		psGetSetCB->ui32Alpha[offset]   = 0x3ff;	
	        	}        		
	    	}
	    	else
	    	{
	    		if ( numAlphaBits > 0 )
	    		{
	    			psGetSetCB->ui32Alpha[offset]   = ui32ThisPixel & AlphaMask;
	        		ui32ThisPixel >>= numAlphaBits;
	        	}
	        	else
	        	{
	        		psGetSetCB->ui32Alpha[offset] 	= 0x3ff;	
	        	}
	        	
				psGetSetCB->ui32Y[offset]       = ui32ThisPixel & ColMask;
	    	}

			/* Scale the colour component to 10 bits */
			if (numColBits < 10)
			{
	   			psGetSetCB->ui32Y[offset]       = (psGetSetCB->ui32Y[offset])<<(10-numColBits);
				psGetSetCB->ui32Y[offset]       |= (psGetSetCB->ui32Y[offset])>>numColBits;
			}
			else
			{
				psGetSetCB->ui32Y[offset]       = (psGetSetCB->ui32Y[offset])>>(numColBits-10);
			}
			
			/* If using alpha, scale alpha to 10 bits */
			if ( numAlphaBits > 0 )
			{
				if (numAlphaBits < 10)
				{
	   				psGetSetCB->ui32Alpha[offset]       = (psGetSetCB->ui32Alpha[offset])<<(10-numAlphaBits);
					psGetSetCB->ui32Alpha[offset]       |= (psGetSetCB->ui32Alpha[offset])>>numAlphaBits;
				}
				else
				{
					psGetSetCB->ui32Alpha[offset]       = (psGetSetCB->ui32Alpha[offset])>>(numAlphaBits-10);
				}
			}
			offset++;
	    }  	
    }

	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockA4
******************************************************************************/
static
IMG_VOID
pixel_DeblockA4(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32		w;
    IMG_UINT32		word;
	IMG_UINT32		numWords;
    IMG_UINT32		offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Y [offset]      = 0x00; // No pixel color information (alpha only format)
        psGetSetCB->ui32Alpha[offset++] = ((word >>  0) & 0x0f) << 2;
        psGetSetCB->ui32Y [offset]      = 0x00; // No pixel color information (alpha only format)
        psGetSetCB->ui32Alpha[offset++] = ((word >>  4) & 0x0f) << 2;
        psGetSetCB->ui32Y [offset]      = 0x00; // No pixel color information (alpha only format)
        psGetSetCB->ui32Alpha[offset++] = ((word >>  8) & 0x0f) << 2;
        psGetSetCB->ui32Y [offset]      = 0x00; // No pixel color information (alpha only format)
        psGetSetCB->ui32Alpha[offset++] = ((word >> 12) & 0x0f) << 2;

        psGetSetCB->ui32Y [offset]      = 0x00; // No pixel color information (alpha only format)
        psGetSetCB->ui32Alpha[offset++] = ((word >> 16) & 0x0f) << 2;
        psGetSetCB->ui32Y [offset]      = 0x00; // No pixel color information (alpha only format)
        psGetSetCB->ui32Alpha[offset++] = ((word >> 20) & 0x0f) << 2;
        psGetSetCB->ui32Y [offset]      = 0x00; // No pixel color information (alpha only format)
        psGetSetCB->ui32Alpha[offset++] = ((word >> 24) & 0x0f) << 2;
        psGetSetCB->ui32Y [offset]      = 0x00; // No pixel color information (alpha only format)
        psGetSetCB->ui32Alpha[offset++] = ((word >> 28) & 0x0f) << 2;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockA8
******************************************************************************/
static
IMG_VOID
pixel_DeblockA8(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32		w;
    IMG_UINT32		word;
	IMG_UINT32		numWords;
    IMG_UINT32		offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Y [offset]      = 0x00; // No pixel color information (alpha only format)
        psGetSetCB->ui32Alpha[offset++] = ((word >>  0) & 0xff) << 2;
        psGetSetCB->ui32Y [offset]      = 0x00; // No pixel color information (alpha only format)
        psGetSetCB->ui32Alpha[offset++] = ((word >>  8) & 0xff) << 2;
        psGetSetCB->ui32Y [offset]      = 0x00; // No pixel color information (alpha only format)
        psGetSetCB->ui32Alpha[offset++] = ((word >> 16) & 0xff) << 2;
        psGetSetCB->ui32Y [offset]      = 0x00; // No pixel color information (alpha only format)
        psGetSetCB->ui32Alpha[offset++] = ((word >> 24) & 0xff) << 2;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}


/*!
******************************************************************************
@Function               pixel_DeblockRGB8
********* *********************************************************************/
static IS_NOT_USED IMG_VOID pixel_DeblockRGB8(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
)
{
    IMG_UINT32		w;
    IMG_UINT32		word;
	IMG_UINT32		numWords;
    IMG_UINT32		offset		= 0;
	PIXEL_sInfo *	psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];

        psGetSetCB->ui32Y [offset]      = ((word >>  0) & 0xff) << 2;
		psGetSetCB->ui32U [offset]      = ((word >>  0) & 0xff) << 2;
		psGetSetCB->ui32V [offset]      = ((word >>  0) & 0xff) << 2;
		psGetSetCB->ui32Y[offset]       |= ((psGetSetCB->ui32Y[offset] >> 8));
		psGetSetCB->ui32U[offset]       |= ((psGetSetCB->ui32U[offset] >> 8));
		psGetSetCB->ui32V[offset]       |= ((psGetSetCB->ui32V[offset] >> 8));
        psGetSetCB->ui32Alpha[offset]	= 0x00;
		offset++;

		psGetSetCB->ui32Y [offset]      = ((word >>  8) & 0xff) << 2;
		psGetSetCB->ui32U [offset]      = ((word >>  8) & 0xff) << 2;
		psGetSetCB->ui32V [offset]      = ((word >>  8) & 0xff) << 2;
		psGetSetCB->ui32Y[offset]       |= ((psGetSetCB->ui32Y[offset] >> 8));
		psGetSetCB->ui32U[offset]       |= ((psGetSetCB->ui32U[offset] >> 8));
		psGetSetCB->ui32V[offset]       |= ((psGetSetCB->ui32V[offset] >> 8));
        psGetSetCB->ui32Alpha[offset]	= 0x00;
		offset++;

		psGetSetCB->ui32Y [offset]      = ((word >>  16) & 0xff) << 2;
		psGetSetCB->ui32U [offset]      = ((word >>  16) & 0xff) << 2;
		psGetSetCB->ui32V [offset]      = ((word >>  16) & 0xff) << 2;
		psGetSetCB->ui32Y[offset]       |= ((psGetSetCB->ui32Y[offset] >> 8));
		psGetSetCB->ui32U[offset]       |= ((psGetSetCB->ui32U[offset] >> 8));
		psGetSetCB->ui32V[offset]       |= ((psGetSetCB->ui32V[offset] >> 8));
        psGetSetCB->ui32Alpha[offset]	= 0x00;
		offset++;

		psGetSetCB->ui32Y [offset]      = ((word >>  24) & 0xff) << 2;
		psGetSetCB->ui32U [offset]      = ((word >>  24) & 0xff) << 2;
		psGetSetCB->ui32V [offset]      = ((word >>  24) & 0xff) << 2;
		psGetSetCB->ui32Y[offset]       |= ((psGetSetCB->ui32Y[offset] >> 8));
		psGetSetCB->ui32U[offset]       |= ((psGetSetCB->ui32U[offset] >> 8));
		psGetSetCB->ui32V[offset]       |= ((psGetSetCB->ui32V[offset] >> 8));
        psGetSetCB->ui32Alpha[offset]	= 0x00;
		offset++;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockRGB555AndARGB1555
******************************************************************************/
static
IMG_VOID
pixel_DeblockRGB555AndARGB1555(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32		n;
    IMG_UINT32		w;
    IMG_UINT32		word;
	IMG_UINT32		numWords;
    IMG_UINT32		offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        for (n = 0; n < 2; n++)
        {
            psGetSetCB->ui32Y[offset] = ((word >> 10) & 0x1F) << 5;
            psGetSetCB->ui32U[offset] = ((word >>  5) & 0x1F) << 5;
            psGetSetCB->ui32V[offset] = ((word >>  0) & 0x1F) << 5;
            psGetSetCB->ui32Y[offset] |= psGetSetCB->ui32Y[offset] >> 5;
            psGetSetCB->ui32U[offset] |= psGetSetCB->ui32U[offset] >> 5;
            psGetSetCB->ui32V[offset] |= psGetSetCB->ui32V[offset] >> 5;
            if (psGetSetCB->ePixelColourFormat == IMG_PIXFMT_ARGB1555)
            {
                psGetSetCB->ui32Alpha[offset] = (word & 0x8000) ? 0x3ff : 0;
            }
            else
            {
                psGetSetCB->ui32Alpha[offset] = 0x3ff;
            }
            offset++;
            word >>= 16;
        }
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockARGB4444
******************************************************************************/
static
IMG_VOID
pixel_DeblockARGB4444(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32		n;
    IMG_UINT32		w;
    IMG_UINT32		word;
	IMG_UINT32		numWords;
    IMG_UINT32		offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        for (n = 0; n < 2; n++)
        {
            psGetSetCB->ui32Alpha[offset]   = ((word >> 12) & 0xF) << 6;
            psGetSetCB->ui32Y[offset]       = ((word >>  8) & 0xF) << 6;
            psGetSetCB->ui32U[offset]       = ((word >>  4) & 0xF) << 6;
            psGetSetCB->ui32V[offset]       = ((word >>  0) & 0xF) << 6;
            psGetSetCB->ui32Alpha[offset]   |= ((psGetSetCB->ui32Alpha[offset] >> 4) | (psGetSetCB->ui32Alpha[offset] >> 8));
            psGetSetCB->ui32Y[offset]       |= ((psGetSetCB->ui32Y[offset] >> 4)     | (psGetSetCB->ui32Y[offset] >> 8));
            psGetSetCB->ui32U[offset]       |= ((psGetSetCB->ui32U[offset] >> 4)     | (psGetSetCB->ui32U[offset] >> 8));
            psGetSetCB->ui32V[offset]       |= ((psGetSetCB->ui32V[offset] >> 4)     | (psGetSetCB->ui32V[offset] >> 8));
            offset++;
            word >>= 16;
        }
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockRGB565
******************************************************************************/
static
IMG_VOID
pixel_DeblockRGB565(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32		n;
    IMG_UINT32		w;
    IMG_UINT32		word;
	IMG_UINT32		numWords;
    IMG_UINT32		offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        for (n = 0; n < 2; n++)
        {
            psGetSetCB->ui32Alpha[offset]   = 0x3ff;
            psGetSetCB->ui32Y[offset]       = ((word >> 11) & 0x1F) << 5;
            psGetSetCB->ui32U[offset]       = ((word >>  5) & 0x3F) << 4;
            psGetSetCB->ui32V[offset]       = ((word >>  0) & 0x1F) << 5;
            psGetSetCB->ui32Y[offset]       |= psGetSetCB->ui32Y[offset] >> 5;
            psGetSetCB->ui32U[offset]       |= psGetSetCB->ui32U[offset] >> 6;
            psGetSetCB->ui32V[offset]       |= psGetSetCB->ui32V[offset] >> 5;
            offset++;
            word >>= 16;
        }
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockRGB332
******************************************************************************/
static
IMG_VOID
pixel_DeblockRGB332(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    static IMG_UINT32       rgbLookup2[] = { 0x000, 0x155, 0x2aa, 0x3ff };
    static IMG_UINT32       rgbLookup3[] = { 0x000, 0x092, 0x124, 0x1b6, 0x249, 0x2db, 0x36d, 0x3ff };

    IMG_UINT32  	n;
    IMG_UINT32  	w;
    IMG_UINT32  	word;
	IMG_UINT32  	numWords;
    IMG_UINT32  	offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        for (n = 0; n < 4; n++)
        {
            psGetSetCB->ui32Y[offset]       = rgbLookup3[(word >> 5) & 7];
            psGetSetCB->ui32U[offset]       = rgbLookup3[(word >> 2) & 7];
            psGetSetCB->ui32V[offset]       = rgbLookup2[(word >> 0) & 3];
            psGetSetCB->ui32Alpha[offset]   = 0x3FF;
            word >>= 8;
            offset++;
        }
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockRGB888
******************************************************************************/
static IMG_VOID
pixel_DeblockRGB888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32		n;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

    psGetSetCB->ui32V[0] = ((pui32Word[0] >>  0) & 0xff) << 2;
    psGetSetCB->ui32U[0] = ((pui32Word[0] >>  8) & 0xff) << 2;
    psGetSetCB->ui32Y[0] = ((pui32Word[0] >> 16) & 0xff) << 2;

    psGetSetCB->ui32V[1] = ((pui32Word[0] >> 24) & 0xff) << 2;
    psGetSetCB->ui32U[1] = ((pui32Word[1] >>  0) & 0xff) << 2;
    psGetSetCB->ui32Y[1] = ((pui32Word[1] >>  8) & 0xff) << 2;

    psGetSetCB->ui32V[2] = ((pui32Word[1] >> 16) & 0xff) << 2;
    psGetSetCB->ui32U[2] = ((pui32Word[1] >> 24) & 0xff) << 2;
    psGetSetCB->ui32Y[2] = ((pui32Word[2] >>  0) & 0xff) << 2;

    psGetSetCB->ui32V[3] = ((pui32Word[2] >>  8) & 0xff) << 2;
    psGetSetCB->ui32U[3] = ((pui32Word[2] >> 16) & 0xff) << 2;
    psGetSetCB->ui32Y[3] = ((pui32Word[2] >> 24) & 0xff) << 2;

    for (n = 0; n < 4; n++)
    {
        psGetSetCB->ui32Y[n]    |= psGetSetCB->ui32Y[n] >> 8;
        psGetSetCB->ui32U[n]    |= psGetSetCB->ui32U[n] >> 8;
        psGetSetCB->ui32V[n]    |= psGetSetCB->ui32V[n] >> 8;
        psGetSetCB->ui32Alpha[n] = 0x3FF;
    }
	IMG_ASSERT(n == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockARGB8888
******************************************************************************/
static
IMG_VOID
pixel_DeblockARGB8888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32		w;
    IMG_UINT32		word;
	IMG_UINT32		numWords;
    IMG_UINT32		offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Alpha[offset]   = ((word >> 24) & 0xFF) << 2;
        psGetSetCB->ui32Y[offset]       = ((word >> 16) & 0xFF) << 2;
        psGetSetCB->ui32U[offset]       = ((word >>  8) & 0xFF) << 2;
        psGetSetCB->ui32V[offset]       = ((word >>  0) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   |= psGetSetCB->ui32Alpha[offset]    >> 8;
        psGetSetCB->ui32Y[offset]       |= psGetSetCB->ui32Y[offset]        >> 8;
        psGetSetCB->ui32U[offset]       |= psGetSetCB->ui32U[offset]        >> 8;
        psGetSetCB->ui32V[offset]       |= psGetSetCB->ui32V[offset]        >> 8;
        offset++;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockABGR8888
******************************************************************************/
static
IMG_VOID
pixel_DeblockABGR8888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32		w;
    IMG_UINT32		word;
	IMG_UINT32		numWords;
    IMG_UINT32		offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Alpha[offset]   = ((word >> 24) & 0xFF) << 2;
        psGetSetCB->ui32Y[offset]       = ((word >> 0) & 0xFF) << 2;
        psGetSetCB->ui32U[offset]       = ((word >> 8) & 0xFF) << 2;
        psGetSetCB->ui32V[offset]       = ((word >> 16) & 0xFF) << 2;        
		psGetSetCB->ui32Alpha[offset]   |= psGetSetCB->ui32Alpha[offset]    >> 8;
        psGetSetCB->ui32Y[offset]       |= psGetSetCB->ui32Y[offset]        >> 8;
        psGetSetCB->ui32U[offset]       |= psGetSetCB->ui32U[offset]        >> 8;
        psGetSetCB->ui32V[offset]       |= psGetSetCB->ui32V[offset]        >> 8;
        offset++;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockBGRA8888
******************************************************************************/
static
IMG_VOID
pixel_DeblockBGRA8888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32		w;
    IMG_UINT32		word;
	IMG_UINT32		numWords;
    IMG_UINT32		offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Alpha[offset]   = ((word >> 0) & 0xFF) << 2;
        psGetSetCB->ui32Y[offset]       = ((word >> 8) & 0xFF) << 2;
        psGetSetCB->ui32U[offset]       = ((word >> 16) & 0xFF) << 2;
        psGetSetCB->ui32V[offset]       = ((word >> 24) & 0xFF) << 2;
		psGetSetCB->ui32Alpha[offset]   |= psGetSetCB->ui32Alpha[offset]    >> 8;
        psGetSetCB->ui32Y[offset]       |= psGetSetCB->ui32Y[offset]        >> 8;
        psGetSetCB->ui32U[offset]       |= psGetSetCB->ui32U[offset]        >> 8;
        psGetSetCB->ui32V[offset]       |= psGetSetCB->ui32V[offset]        >> 8;
        offset++;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockARGB8332
******************************************************************************/
static
IMG_VOID
pixel_DeblockARGB8332(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    static IMG_UINT32       rgbLookup2[] = { 0x000, 0x155, 0x2aa, 0x3ff };
    static IMG_UINT32       rgbLookup3[] = { 0x000, 0x092, 0x124, 0x1b6, 0x249, 0x2db, 0x36d, 0x3ff };

    IMG_UINT32  	n;
    IMG_UINT32  	w;
    IMG_UINT32  	word;
	IMG_UINT32  	numWords;
    IMG_UINT32  	offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
		for (n = 0; n < 2; n++)
        {
			psGetSetCB->ui32Alpha[offset]   = ((word >> 8) & 0xF) << 2;
			psGetSetCB->ui32Alpha[offset]   |= (psGetSetCB->ui32Alpha[offset])>>8;
            
			psGetSetCB->ui32Y[offset]       = rgbLookup3[(word >> 5) & 7];
            psGetSetCB->ui32U[offset]       = rgbLookup3[(word >> 2) & 7];
            psGetSetCB->ui32V[offset]       = rgbLookup2[(word >> 0) & 3];
			word >>= 16;
            offset++;
        }
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockYUV101010
******************************************************************************/
static
IMG_VOID
pixel_DeblockYUV101010(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32		w;
    IMG_UINT32		word;
	IMG_UINT32		numWords;
    IMG_UINT32		offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32V[offset]       = (word >>  0) & 0x3FF;
        psGetSetCB->ui32U[offset]       = (word >> 10) & 0x3FF;
        psGetSetCB->ui32Y[offset]       = (word >> 20) & 0x3FF;
        psGetSetCB->ui32Alpha[offset]   = 0x3FF;
        offset++;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockAYUV4444
******************************************************************************/
static
IMG_VOID
pixel_DeblockAYUV4444(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32  	n;
    IMG_UINT32  	w;
    IMG_UINT32  	word;
	IMG_UINT32  	numWords;
    IMG_UINT32  	offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        for (n = 0; n < 2; n++)
        {
            psGetSetCB->ui32Alpha[offset]   = ((word >> 12) & 0xf) ;
            psGetSetCB->ui32Alpha[offset]   |= ((psGetSetCB->ui32Alpha[offset] >> 4) | (psGetSetCB->ui32Alpha[offset] >> 8));

            psGetSetCB->ui32Y[offset]       = ((word >>  8) & 0xf) << 6;
            psGetSetCB->ui32U[offset]       = ((word >>  4) & 0xf) << 6;
            psGetSetCB->ui32V[offset]       = ((word >>  0) & 0xf) << 6;
            psGetSetCB->ui32Y[offset]       |= ((psGetSetCB->ui32Y[offset] >> 4) | (psGetSetCB->ui32Y[offset] >> 8));
            psGetSetCB->ui32U[offset]       |= ((psGetSetCB->ui32U[offset] >> 4) | (psGetSetCB->ui32U[offset] >> 8));
            psGetSetCB->ui32V[offset]       |= ((psGetSetCB->ui32V[offset] >> 4) | (psGetSetCB->ui32V[offset] >> 8));
            word >>= 16;
            offset++;
        }
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockAYUV8888
******************************************************************************/
static
IMG_VOID
pixel_DeblockAYUV8888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32		w;
    IMG_UINT32		word;
	IMG_UINT32		numWords;
    IMG_UINT32		offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32V[offset]       = ((word >>  0) & 0xFF) << 2;
        psGetSetCB->ui32U[offset]       = ((word >>  8) & 0xFF) << 2;
        psGetSetCB->ui32Y[offset]       = ((word >> 16) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   = ((word >> 24) & 0xFF) << 2;

        psGetSetCB->ui32Y[offset]       |= psGetSetCB->ui32Y[offset] >> 8;
        psGetSetCB->ui32U[offset]       |= psGetSetCB->ui32U[offset] >> 8;
        psGetSetCB->ui32V[offset]       |= psGetSetCB->ui32V[offset] >> 8;
        psGetSetCB->ui32Alpha[offset]   |= psGetSetCB->ui32Alpha[offset] >> 8;
        offset++;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockUYVY8888
******************************************************************************/
static
IMG_VOID
pixel_DeblockUYVY8888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32		n;
    IMG_UINT32		w;
    IMG_UINT32		word;
	IMG_UINT32		numWords;
    IMG_UINT32		offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32U[offset]       = ((word >>  0) & 0xFF) << 2;
        psGetSetCB->ui32Y[offset]       = ((word >>  8) & 0xFF) << 2;
        psGetSetCB->ui32V[offset]       = ((word >> 16) & 0xFF) << 2;
        psGetSetCB->ui32Y[offset + 1]   = ((word >> 24) & 0xFF) << 2;

        // replicate U and V values to go from 4:2:2 to 4:4:4
        psGetSetCB->ui32U[offset + 1]   = psGetSetCB->ui32U[offset];
        psGetSetCB->ui32V[offset + 1]   = psGetSetCB->ui32V[offset];

        // copy top 2 bits down into the lower 2 bits
        for (n = offset; n < offset + 2; n++)
        {
            psGetSetCB->ui32Y[n]    |= psGetSetCB->ui32Y[n] >> 8;
            psGetSetCB->ui32U[n]    |= psGetSetCB->ui32U[n] >> 8;
            psGetSetCB->ui32V[n]    |= psGetSetCB->ui32V[n] >> 8;
            psGetSetCB->ui32Alpha[n] = 0x3FF;
        }
        offset += 2;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockVYUY8888
******************************************************************************/
static
IMG_VOID
pixel_DeblockVYUY8888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32		n;
    IMG_UINT32		w;
    IMG_UINT32		word;
	IMG_UINT32		numWords;
    IMG_UINT32		offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32V[offset]       = ((word >>  0) & 0xFF) << 2;
        psGetSetCB->ui32Y[offset]       = ((word >>  8) & 0xFF) << 2;
        psGetSetCB->ui32U[offset]       = ((word >> 16) & 0xFF) << 2;
        psGetSetCB->ui32Y[offset + 1]   = ((word >> 24) & 0xFF) << 2;

        // replicate U and V values to go from 4:2:2 to 4:4:4
        psGetSetCB->ui32U[offset + 1]   = psGetSetCB->ui32U[offset];
        psGetSetCB->ui32V[offset + 1]   = psGetSetCB->ui32V[offset];

        // copy top 2 bits down into the lower 2 bits
        for (n = offset; n < offset + 2; n++)
        {
            psGetSetCB->ui32Y[n]    |= psGetSetCB->ui32Y[n] >> 8;
            psGetSetCB->ui32U[n]    |= psGetSetCB->ui32U[n] >> 8;
            psGetSetCB->ui32V[n]    |= psGetSetCB->ui32V[n] >> 8;
            psGetSetCB->ui32Alpha[n] = 0x3FF;
        }
        offset += 2;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockYVYU8888
******************************************************************************/
static
IMG_VOID
pixel_DeblockYVYU8888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32		n;
    IMG_UINT32		w;
    IMG_UINT32		word;
	IMG_UINT32		numWords;
    IMG_UINT32		offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Y[offset]       = ((word >>  0) & 0xFF) << 2;
        psGetSetCB->ui32V[offset]       = ((word >>  8) & 0xFF) << 2;
        psGetSetCB->ui32Y[offset+1]     = ((word >> 16) & 0xFF) << 2;
        psGetSetCB->ui32U[offset]		= ((word >> 24) & 0xFF) << 2;

        // replicate U and V values to go from 4:2:2 to 4:4:4
        psGetSetCB->ui32U[offset + 1]   = psGetSetCB->ui32U[offset];
        psGetSetCB->ui32V[offset + 1]   = psGetSetCB->ui32V[offset];

        // copy top 2 bits down into the lower 2 bits
        for (n = offset; n < offset + 2; n++)
        {
            psGetSetCB->ui32Y[n]    |= psGetSetCB->ui32Y[n] >> 8;
            psGetSetCB->ui32U[n]    |= psGetSetCB->ui32U[n] >> 8;
            psGetSetCB->ui32V[n]    |= psGetSetCB->ui32V[n] >> 8;
            psGetSetCB->ui32Alpha[n] = 0x3FF;
        }
        offset += 2;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockYUYV8888
******************************************************************************/
static
IMG_VOID
pixel_DeblockYUYV8888(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32		n;
    IMG_UINT32		w;
    IMG_UINT32		word;
	IMG_UINT32		numWords;
    IMG_UINT32		offset		= 0;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Y[offset]       = ((word >>  0) & 0xFF) << 2;
        psGetSetCB->ui32U[offset]       = ((word >>  8) & 0xFF) << 2;
        psGetSetCB->ui32Y[offset+1]     = ((word >> 16) & 0xFF) << 2;
        psGetSetCB->ui32V[offset]		= ((word >> 24) & 0xFF) << 2;

        // replicate U and V values to go from 4:2:2 to 4:4:4
        psGetSetCB->ui32U[offset + 1]   = psGetSetCB->ui32U[offset];
        psGetSetCB->ui32V[offset + 1]   = psGetSetCB->ui32V[offset];

        // copy top 2 bits down into the lower 2 bits
        for (n = offset; n < offset + 2; n++)
        {
            psGetSetCB->ui32Y[n]    |= psGetSetCB->ui32Y[n] >> 8;
            psGetSetCB->ui32U[n]    |= psGetSetCB->ui32U[n] >> 8;
            psGetSetCB->ui32V[n]    |= psGetSetCB->ui32V[n] >> 8;
            psGetSetCB->ui32Alpha[n] = 0x3FF;
        }
        offset += 2;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockUYVY101010
******************************************************************************/
static
IMG_VOID
pixel_DeblockUYVY101010(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32              n;

    psGetSetCB->ui32V[0] = pui32Word[0] & 0x3FF;
    psGetSetCB->ui32Y[0] = (pui32Word[0] >> 10) & 0x3FF;
    psGetSetCB->ui32U[0] = (pui32Word[0] >> 20) & 0x3FF;

    psGetSetCB->ui32Y[1] = pui32Word[1] & 0x3FF;
    psGetSetCB->ui32V[2] = (pui32Word[1] >> 10) & 0x3FF;
    psGetSetCB->ui32Y[2] = (pui32Word[1] >> 20) & 0x3FF;

    psGetSetCB->ui32U[2] = pui32Word[2] & 0x3FF;
    psGetSetCB->ui32Y[3] = (pui32Word[2] >> 10) & 0x3FF;
    psGetSetCB->ui32V[4] = (pui32Word[2] >> 20) & 0x3FF;

    psGetSetCB->ui32Y[4] = pui32Word[3] & 0x3FF;
    psGetSetCB->ui32U[4] = (pui32Word[3] >> 10) & 0x3FF;
    psGetSetCB->ui32Y[5] = (pui32Word[3] >> 20) & 0x3FF;

    for (n = 0; n < 6; n += 2)
    {
        // fill in the alpha channel
        psGetSetCB->ui32Alpha[n]     = 0x3FF;
        psGetSetCB->ui32Alpha[n + 1] = 0x3FF;
        // Replicate the U and V to get YUV 4:4:4
        psGetSetCB->ui32U[n + 1] = psGetSetCB->ui32U[n];
        psGetSetCB->ui32V[n + 1] = psGetSetCB->ui32V[n];
    }
}

/*!
******************************************************************************
@Function               pixel_DeblockVYAUYA8888
******************************************************************************/
static
IMG_VOID
pixel_DeblockVYAUYA8888(
    PIXEL_sGetSetCB *psGetSetCB
    )
{
    IMG_UINT32		offset;
	IMG_UINT32		ui32Val;
	IMG_UINT8 *		pSrcData;
    IMG_UINT32		yIndex		= 0;
    IMG_UINT32		uIndex		= 0;
    IMG_UINT32		vIndex		= 0;
    IMG_UINT32		aIndex		= 0;    
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

	IMG_ASSERT((psBufInfo->ui32YBytesInBOP % 6) == 0);

    pSrcData = (IMG_UINT8 *)PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvYBufAddr);

    yIndex = uIndex = vIndex = aIndex = 0;
	for (offset = 0; offset < psBufInfo->ui32YBytesInBOP; offset++)
    {
        ui32Val = *pSrcData++;
        ui32Val <<= 2;              /* promote from 8 bit to 10 bit */
        ui32Val |= ui32Val >> 8;    /* copy top 2 bits to bottom 2 bits */
        switch (offset % 6)
        {
            case 0:
                /* V component */
                psGetSetCB->ui32V[vIndex++]     = ui32Val;
                psGetSetCB->ui32V[vIndex++]     = ui32Val;
                break;
            case 1:
                /* Y component */
                psGetSetCB->ui32Y[yIndex++]     = ui32Val;
                break;
            case 2:
                /* A component */
                psGetSetCB->ui32Alpha[aIndex++] = ui32Val;
                break;
            case 3:
                /* U component */
                psGetSetCB->ui32U[uIndex++]     = ui32Val;
                psGetSetCB->ui32U[uIndex++]     = ui32Val;
                break;
            case 4:
                /* Y component */
                psGetSetCB->ui32Y[yIndex++]     = ui32Val;
                break;
            case 5:
                /* A component */
                psGetSetCB->ui32Alpha[aIndex++] = ui32Val;
                break;
        }
    }
	IMG_ASSERT(yIndex == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockPL12IMC2
******************************************************************************/
static
void
pixel_DeblockPL12IMC2(
    PIXEL_sGetSetCB *psGetSetCB
    )
{
    IMG_UINT32      val;
    IMG_UINT32      offset;
    IMG_UINT8 *     pSrcData;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

    // copy the Y data
    pSrcData = (IMG_UINT8 *) PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvYBufAddr);
	for (offset = 0; offset < psBufInfo->ui32YBytesInBOP; offset++)
    {
        val = *pSrcData++;
        val <<= 2;              // promote from 8 bit to 10 bit
        val |= val >> 8;        // copy top 2 bits to bottom 2 bits
        psGetSetCB->ui32Y[offset] = val;
    }

    // copy the U data
    pSrcData = (IMG_UINT8 *) PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvUVBufAddr);
	for (offset = 0; offset < psBufInfo->ui32UVBytesInBOP; offset++)
    {
        val = *pSrcData++;
        val <<= 2;              // promote from 8 bit to 10 bit
        val |= val >> 8;        // copy top 2 bits to bottom 2 bits
        psGetSetCB->ui32U[offset] = val;
    }

    // copy the V data
    pSrcData = (IMG_UINT8 *) PIXEL_TWIDDLE_ADDRESS(psGetSetCB,(psGetSetCB->pvUVBufAddr + PIXEL_GET_UV_STRIDE(psGetSetCB)));
	for (offset = 0; offset < psBufInfo->ui32UVBytesInBOP; offset++)
    {
        val = *pSrcData++;
        val <<= 2;              // promote from 8 bit to 10 bit
        val |= val >> 8;        // copy top 2 bits to bottom 2 bits
        psGetSetCB->ui32V[offset] = val;
    }
}

/*!
******************************************************************************
@Function               pixel_DeblockPL12YV12
******************************************************************************/
static
void
pixel_DeblockPL12YV12(    
	PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{

	IMG_UINT32      val;
    IMG_UINT32      offset;
    IMG_UINT8 *     pSrcData;
	PIXEL_sInfo *		psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

    // copy the Y data
    pSrcData = (IMG_UINT8 *) PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvYBufAddr);
	for (offset = 0; offset < psBufInfo->ui32YBytesInBOP; offset++)
    {
        val = *pSrcData++;
        val <<= 2;              // promote from 8 bit to 10 bit
        val |= val >> 8;        // copy top 2 bits to bottom 2 bits
        psGetSetCB->ui32Y[offset] = val;
		psGetSetCB->ui32Alpha[offset] = 0x3FF;
    }

	// copy the U data
    pSrcData = (IMG_UINT8 *) PIXEL_TWIDDLE_ADDRESS(psGetSetCB, psGetSetCB->pvUVBufAddr);
	for (offset = 0; offset < psBufInfo->ui32UVBytesInBOP*2; offset+=2)
    {
        val = *pSrcData++;
        val <<= 2;              // promote from 8 bit to 10 bit
        val |= val >> 8;        // copy top 2 bits to bottom 2 bits
        psGetSetCB->ui32U[offset] = val;
		psGetSetCB->ui32U[offset+1] = val;	//replicate data
    }

	// copy the V data
    pSrcData = (IMG_UINT8 *) PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvUVBufAddr + PIXEL_GET_UV_STRIDE(psGetSetCB) *  PIXEL_GET_UV_HEIGHT(psGetSetCB));
	for (offset = 0; offset < psBufInfo->ui32UVBytesInBOP*2; offset+=2)
    {
        val = *pSrcData++;
        val <<= 2;              // promote from 8 bit to 10 bit
        val |= val >> 8;        // copy top 2 bits to bottom 2 bits
        psGetSetCB->ui32V[offset] = val;
		psGetSetCB->ui32V[offset+1] = val;	//replicate data
    }
}

/*!
******************************************************************************
@Function               pixel_DeblockAYUV2101010
******************************************************************************/
static
IMG_VOID
pixel_DeblockAYUV2101010(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    static IMG_UINT32 alphaLookup[] = { 0x000, 0x155, 0x2aa, 0x3ff };

    IMG_UINT32  w;
    IMG_UINT32  word;
	IMG_UINT32  numWords;
    IMG_UINT32  offset = 0;
	PIXEL_sInfo *	psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Alpha[offset]   = alphaLookup[((word >> 30) & 0x3)];
        psGetSetCB->ui32Y[offset]       = ((word >> 20) & 0x3FF);
        psGetSetCB->ui32U[offset]       = ((word >> 10) & 0x3FF);
        psGetSetCB->ui32V[offset]       = ((word >>  0) & 0x3FF);
        offset++;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockCVBS10
******************************************************************************/
static
IMG_VOID
pixel_DeblockCVBS10(
    PIXEL_sGetSetCB *         psGetSetCB,
    IMG_UINT32 *            pui32Word
    )
{
    IMG_UINT32  w;
    IMG_UINT32  word;
	IMG_UINT32  numWords;
    IMG_UINT32  offset = 0;
	PIXEL_sInfo *	psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Y[offset++] = (word >>  0) & 0x3FF;
        psGetSetCB->ui32Y[offset++] = (word >> 10) & 0x3FF;
        psGetSetCB->ui32Y[offset++] = (word >> 20) & 0x3FF;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_Deblock42XPL12YUV10
******************************************************************************/
static
IMG_VOID
pixel_Deblock42XPL12YUV10(
    PIXEL_sGetSetCB       *psGetSetCB,
    IMG_UINT32 *        pui32Word,
    IMG_UINT32 *        pui32UVWord
    )
{
    IMG_UINT32  n;
    IMG_UINT32  w;
    IMG_UINT32  word;
    IMG_UINT32  offset;
    IMG_UINT32  numWords;
	PIXEL_sInfo *	psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

    // Deblock Alpha and Y components
    offset = 0;
	numWords = psBufInfo->ui32YBytesInBOP >> 2;
    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = (word >>  0) & 0x3FF;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = (word >> 10) & 0x3FF;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = (word >> 20) & 0x3FF;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);

	IMG_ASSERT(psBufInfo->ui32UVBytesInBOP == 16);

    // Deblock the U and V components
    psGetSetCB->ui32V[0]    = (pui32UVWord[0] >>  0) & 0x3FF;
    psGetSetCB->ui32U[0]    = (pui32UVWord[0] >> 10) & 0x3FF;
    psGetSetCB->ui32V[2]    = (pui32UVWord[0] >> 20) & 0x3FF;

    psGetSetCB->ui32U[2]    = (pui32UVWord[1] >>  0) & 0x3FF;
    psGetSetCB->ui32V[4]    = (pui32UVWord[1] >> 10) & 0x3FF;
    psGetSetCB->ui32U[4]    = (pui32UVWord[1] >> 20) & 0x3FF;

    psGetSetCB->ui32V[6]    = (pui32UVWord[2] >>  0) & 0x3FF;
    psGetSetCB->ui32U[6]    = (pui32UVWord[2] >> 10) & 0x3FF;
    psGetSetCB->ui32V[8]    = (pui32UVWord[2] >> 20) & 0x3FF;

    psGetSetCB->ui32U[8]    = (pui32UVWord[3] >>  0) & 0x3FF;
    psGetSetCB->ui32V[10]   = (pui32UVWord[3] >> 10) & 0x3FF;
    psGetSetCB->ui32U[10]   = (pui32UVWord[3] >> 20) & 0x3FF;

    /* Replicate the U and V */
    for (n = 0; n < 12; n+=2)
    {
        psGetSetCB->ui32U[n + 1] = psGetSetCB->ui32U[n];
        psGetSetCB->ui32V[n + 1] = psGetSetCB->ui32V[n];
    }
}

/*!
******************************************************************************
@Function               pixel_Deblock42XPL8YUV10
******************************************************************************/
static
IMG_VOID
pixel_Deblock42XPL8YUV10(
    PIXEL_sGetSetCB       *psGetSetCB,
    IMG_UINT32 *        pui32Word,
    IMG_UINT32 *        pui32UVWord
    )
{
    IMG_UINT32  n;
    IMG_UINT32  w;
    IMG_UINT32  word;
    IMG_UINT32  offset;
    IMG_UINT32  numWords;
	PIXEL_sInfo *	psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

    // Deblock Alpha and Y components
    offset = 0;
	numWords = psBufInfo->ui32YBytesInBOP >> 2;
    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = (word >>  0) & 0x3FF;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = (word >> 10) & 0x3FF;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = (word >> 20) & 0x3FF;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);

	IMG_ASSERT(psBufInfo->ui32UVBytesInBOP == 8);

    // Deblock the U and V components
    psGetSetCB->ui32U[0]    = (pui32UVWord[0] >>  0) & 0x3FF;
    psGetSetCB->ui32U[2]    = (pui32UVWord[0] >> 10) & 0x3FF;
    psGetSetCB->ui32U[4]    = (pui32UVWord[0] >> 20) & 0x3FF;

    psGetSetCB->ui32U[6]    = (pui32UVWord[1] >>  0) & 0x3FF;
    psGetSetCB->ui32U[8]    = (pui32UVWord[1] >> 10) & 0x3FF;
    psGetSetCB->ui32U[10]   = (pui32UVWord[1] >> 20) & 0x3FF;

    psGetSetCB->ui32V[0]    = (pui32UVWord[2] >>  0) & 0x3FF;
    psGetSetCB->ui32V[2]    = (pui32UVWord[2] >> 10) & 0x3FF;
    psGetSetCB->ui32V[4]    = (pui32UVWord[2] >> 20) & 0x3FF;

    psGetSetCB->ui32V[6]    = (pui32UVWord[3] >>  0) & 0x3FF;
    psGetSetCB->ui32V[8]    = (pui32UVWord[3] >> 10) & 0x3FF;
    psGetSetCB->ui32V[10]   = (pui32UVWord[3] >> 20) & 0x3FF;

    /* Replicate the U and V */
    for (n = 0; n < 12; n+=2)
    {
        psGetSetCB->ui32U[n + 1] = psGetSetCB->ui32U[n];
        psGetSetCB->ui32V[n + 1] = psGetSetCB->ui32V[n];
    }
}

/*!
******************************************************************************
@Function               pixel_Deblock42XPL12YVU10
******************************************************************************/
static
IMG_VOID
pixel_Deblock42XPL12YVU10(
    PIXEL_sGetSetCB       *psGetSetCB,
    IMG_UINT32 *        pui32Word,
    IMG_UINT32 *        pui32UVWord
    )
{
    IMG_UINT32  n;
    IMG_UINT32  w;
    IMG_UINT32  word;
    IMG_UINT32  offset;
    IMG_UINT32  numWords;
	PIXEL_sInfo *	psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

    // Deblock Alpha and Y components
    offset = 0;
	numWords = psBufInfo->ui32YBytesInBOP >> 2;
    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = (word >>  0) & 0x3FF;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = (word >> 10) & 0x3FF;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = (word >> 20) & 0x3FF;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);

	IMG_ASSERT(psBufInfo->ui32UVBytesInBOP == 16);

    // Deblock the U and V components
    psGetSetCB->ui32U[0]    = (pui32UVWord[0] >>  0) & 0x3FF;
    psGetSetCB->ui32V[0]    = (pui32UVWord[0] >> 10) & 0x3FF;
    psGetSetCB->ui32U[2]    = (pui32UVWord[0] >> 20) & 0x3FF;

    psGetSetCB->ui32V[2]    = (pui32UVWord[1] >>  0) & 0x3FF;
    psGetSetCB->ui32U[4]    = (pui32UVWord[1] >> 10) & 0x3FF;
    psGetSetCB->ui32V[4]    = (pui32UVWord[1] >> 20) & 0x3FF;

    psGetSetCB->ui32U[6]    = (pui32UVWord[2] >>  0) & 0x3FF;
    psGetSetCB->ui32V[6]    = (pui32UVWord[2] >> 10) & 0x3FF;
    psGetSetCB->ui32U[8]    = (pui32UVWord[2] >> 20) & 0x3FF;

    psGetSetCB->ui32V[8]    = (pui32UVWord[3] >>  0) & 0x3FF;
    psGetSetCB->ui32U[10]   = (pui32UVWord[3] >> 10) & 0x3FF;
    psGetSetCB->ui32V[10]   = (pui32UVWord[3] >> 20) & 0x3FF;

    /* Replicate the U and V */
    for (n = 0; n < 12; n+=2)
    {
        psGetSetCB->ui32U[n + 1] = psGetSetCB->ui32U[n];
        psGetSetCB->ui32V[n + 1] = psGetSetCB->ui32V[n];
    }
}

/*!
******************************************************************************
@Function               pixel_Deblock42XPL12YUV8
******************************************************************************/
static
IMG_VOID
pixel_Deblock42XPL12YUV8(
    PIXEL_sGetSetCB       *psGetSetCB,
    IMG_UINT32 *        pui32Word,
    IMG_UINT32 *        pui32UVWord
    )
{
    IMG_UINT32  n;
    IMG_UINT32  w;
    IMG_UINT32  word;
    IMG_UINT32  offset;
    IMG_UINT32  numWords;
	PIXEL_sInfo *	psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

    // Deblock Alpha and Y components
    offset = 0;
	numWords = psBufInfo->ui32YBytesInBOP >> 2;
    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >>  0) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >>  8) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >> 16) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >> 24) & 0xFF) << 2;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);

    // Deblock UV components
    offset = 0;
	numWords = psBufInfo->ui32UVBytesInBOP >> 2;
    for (w = 0; w < numWords; w++)
    {
        word = pui32UVWord[w];
        for (n = 0; n < 2; n++)
        {
            psGetSetCB->ui32V[offset]   = ((word >>  0) & 0xFF) << 2;
            psGetSetCB->ui32U[offset]   = ((word >>  8) & 0xFF) << 2;
            offset++;
            // replicate UV components
            psGetSetCB->ui32V[offset]   = psGetSetCB->ui32V[offset - 1];
            psGetSetCB->ui32U[offset]   = psGetSetCB->ui32U[offset - 1];
            offset++;
            word >>= 16;
        }
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_Deblock42XPL8YUV8
******************************************************************************/
static
IMG_VOID
pixel_Deblock42XPL8YUV8(
    PIXEL_sGetSetCB       *psGetSetCB,
    IMG_UINT32 *        pui32Word,
    IMG_UINT32 *        pui32UVWord
    )
{
    IMG_UINT32  w;
    IMG_UINT32  word;
    IMG_UINT32  offset;
    IMG_UINT32  numWords;
	PIXEL_sInfo *	psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

    // Deblock Alpha and Y components
    offset = 0;
	numWords = psBufInfo->ui32YBytesInBOP >> 2;
    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >>  0) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >>  8) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >> 16) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >> 24) & 0xFF) << 2;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);

    // Deblock UV components
    offset = 0;
	numWords = psBufInfo->ui32UVBytesInBOP >> 2;
    IMG_ASSERT(numWords == 2);
    for (w = 0; w < numWords; w++)
    {
        word = pui32UVWord[w];
        psGetSetCB->ui32U[offset]     = ((word >>  0) & 0xFF) << 2;
        psGetSetCB->ui32U[offset+1] = psGetSetCB->ui32U[offset];
        offset += 2;
        psGetSetCB->ui32U[offset]     = ((word >>  8) & 0xFF) << 2;
        psGetSetCB->ui32U[offset+1] = psGetSetCB->ui32U[offset];
        offset += 2;
        psGetSetCB->ui32U[offset]     = ((word >> 16) & 0xFF) << 2;
        psGetSetCB->ui32U[offset+1] = psGetSetCB->ui32U[offset];
        offset += 2;
        psGetSetCB->ui32U[offset]     = ((word >> 24) & 0xFF) << 2;
        psGetSetCB->ui32U[offset+1] = psGetSetCB->ui32U[offset];
        offset += 2;
    }
    offset = 0;
    for (w = 2; w < (numWords+2); w++)
    {
        word = pui32UVWord[w];
        psGetSetCB->ui32V[offset]     = ((word >>  0) & 0xFF) << 2;
        psGetSetCB->ui32V[offset+1] = psGetSetCB->ui32V[offset];
        offset += 2;
        psGetSetCB->ui32V[offset]     = ((word >>  8) & 0xFF) << 2;
        psGetSetCB->ui32V[offset+1] = psGetSetCB->ui32V[offset];
        offset += 2;
        psGetSetCB->ui32V[offset]     = ((word >> 16) & 0xFF) << 2;
        psGetSetCB->ui32V[offset+1] = psGetSetCB->ui32V[offset];
        offset += 2;
        psGetSetCB->ui32V[offset]     = ((word >> 24) & 0xFF) << 2;
        psGetSetCB->ui32V[offset+1] = psGetSetCB->ui32V[offset];
        offset += 2;
    }
}

/*!
******************************************************************************
@Function               pixel_Deblock411PL12YVU8
******************************************************************************/
static
IMG_VOID
pixel_Deblock411PL12YVU8(
    PIXEL_sGetSetCB       *psGetSetCB,
    IMG_UINT32 *        pui32Word,
    IMG_UINT32 *        pui32UVWord
    )
{
    IMG_UINT32  n;
    IMG_UINT32  w;
    IMG_UINT32  word;
    IMG_UINT32  offset;
    IMG_UINT32  numWords;
	PIXEL_sInfo *	psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

    // Deblock Alpha and Y components
    offset = 0;
	numWords = psBufInfo->ui32YBytesInBOP >> 2;
    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >>  0) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >>  8) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >> 16) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >> 24) & 0xFF) << 2;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);

    // Deblock UV components
    offset = 0;
	numWords = psBufInfo->ui32UVBytesInBOP >> 2;
    for (w = 0; w < numWords; w++)
    {
        word = pui32UVWord[w];
        for (n = 0; n < 2; n++)
        {
            psGetSetCB->ui32U[offset]   = ((word >>  0) & 0xFF) << 2;
            psGetSetCB->ui32V[offset]   = ((word >>  8) & 0xFF) << 2;
            offset++;
            // replicate UV components
            psGetSetCB->ui32V[offset]   = psGetSetCB->ui32V[offset - 1];
            psGetSetCB->ui32U[offset]   = psGetSetCB->ui32U[offset - 1];
            offset++;
            psGetSetCB->ui32V[offset]   = psGetSetCB->ui32V[offset - 1];
            psGetSetCB->ui32U[offset]   = psGetSetCB->ui32U[offset - 1];
            offset++;
            psGetSetCB->ui32V[offset]   = psGetSetCB->ui32V[offset - 1];
            psGetSetCB->ui32U[offset]   = psGetSetCB->ui32U[offset - 1];
            offset++;                        
            
            word >>= 16;
        }
    }
    IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_Deblock42XPL12YVU8
******************************************************************************/
static
IMG_VOID
pixel_Deblock42XPL12YVU8(
    PIXEL_sGetSetCB       *psGetSetCB,
    IMG_UINT32 *        pui32Word,
    IMG_UINT32 *        pui32UVWord
    )
{
    IMG_UINT32  n;
    IMG_UINT32  w;
    IMG_UINT32  word;
    IMG_UINT32  offset;
    IMG_UINT32  numWords;
	PIXEL_sInfo *	psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

    // Deblock Alpha and Y components
    offset = 0;
	numWords = psBufInfo->ui32YBytesInBOP >> 2;
    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >>  0) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >>  8) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >> 16) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >> 24) & 0xFF) << 2;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);

    // Deblock UV components
    offset = 0;
	numWords = psBufInfo->ui32UVBytesInBOP >> 2;
    for (w = 0; w < numWords; w++)
    {
        word = pui32UVWord[w];
        for (n = 0; n < 2; n++)
        {
            psGetSetCB->ui32U[offset]   = ((word >>  0) & 0xFF) << 2;
            psGetSetCB->ui32V[offset]   = ((word >>  8) & 0xFF) << 2;
            offset++;
            // replicate UV components
            psGetSetCB->ui32V[offset]   = psGetSetCB->ui32V[offset - 1];
            psGetSetCB->ui32U[offset]   = psGetSetCB->ui32U[offset - 1];
            offset++;
            word >>= 16;
        }
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_Deblock42XPL8YVU8
******************************************************************************/
static IS_NOT_USED IMG_VOID pixel_Deblock42XPL8YVU8(
    PIXEL_sGetSetCB *   psGetSetCB,
    IMG_UINT32 *        pui32Word,
    IMG_UINT32 *        pui32UVWord
)
{
    IMG_UINT32  n;
    IMG_UINT32  w;
    IMG_UINT32  word;
    IMG_UINT32  offset;
    IMG_UINT32  numWords;
	PIXEL_sInfo *	psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

    // Deblock Alpha and Y components
    offset = 0;
	numWords = psBufInfo->ui32YBytesInBOP >> 2;
    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >>  0) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >>  8) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >> 16) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset]   = 0x3ff;
        psGetSetCB->ui32Y[offset++]     = ((word >> 24) & 0xFF) << 2;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);

    // Deblock UV components
    offset = 0;
	numWords = psBufInfo->ui32UVBytesInBOP >> 2;
    for (w = 0; w < numWords; w++)
    {
        word = pui32UVWord[w];
        for (n = 0; n < 2; n++)
        {
            psGetSetCB->ui32U[offset]   = ((word >>  0) & 0xFF) << 2;
            psGetSetCB->ui32V[offset]   = ((word >>  8) & 0xFF) << 2;
            offset++;
            // replicate UV components
            psGetSetCB->ui32V[offset]   = psGetSetCB->ui32V[offset - 1];
            psGetSetCB->ui32U[offset]   = psGetSetCB->ui32U[offset - 1];
            offset++;
            word >>= 16;
        }
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_Deblock42XPL12YUV8_A8
******************************************************************************/
static
IMG_VOID
pixel_Deblock42XPL12YUV8_A8(
    PIXEL_sGetSetCB       *psGetSetCB,
    IMG_UINT32 *        pui32Word,
    IMG_UINT32 *        pui32UVWord,
    IMG_UINT32 *        pui32AlphaWord
    )
{
    IMG_UINT32  n;
    IMG_UINT32  w;
    IMG_UINT32  word;
    IMG_UINT32  offset;
    IMG_UINT32  numWords;
	PIXEL_sInfo *	psBufInfo	= IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);

    // Deblock Y components
    offset = 0;
	numWords = psBufInfo->ui32YBytesInBOP >> 2;
    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Y[offset++]     = ((word >>  0) & 0xFF) << 2;
        psGetSetCB->ui32Y[offset++]     = ((word >>  8) & 0xFF) << 2;
        psGetSetCB->ui32Y[offset++]     = ((word >> 16) & 0xFF) << 2;
        psGetSetCB->ui32Y[offset++]     = ((word >> 24) & 0xFF) << 2;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);

    // Deblock UV components
    offset = 0;
	numWords = psBufInfo->ui32UVBytesInBOP >> 2;
    for (w = 0; w < numWords; w++)
    {
        word = pui32UVWord[w];
        for (n = 0; n < 2; n++)
        {
            psGetSetCB->ui32V[offset]   = ((word >>  0) & 0xFF) << 2;
            psGetSetCB->ui32U[offset]   = ((word >>  8) & 0xFF) << 2;
            offset++;
            // replicate UV components
            psGetSetCB->ui32V[offset]   = psGetSetCB->ui32V[offset - 1];
            psGetSetCB->ui32U[offset]   = psGetSetCB->ui32U[offset - 1];
            offset++;
            word >>= 16;
        }
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);

    // Deblock Alpha components
    offset = 0;
	numWords = psBufInfo->ui32AlphaBytesInBOP >> 2;
    for (w = 0; w < numWords; w++)
    {
        word = pui32AlphaWord[w];
        psGetSetCB->ui32Alpha[offset++]     = ((word >>  0) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset++]     = ((word >>  8) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset++]     = ((word >> 16) & 0xFF) << 2;
        psGetSetCB->ui32Alpha[offset++]     = ((word >> 24) & 0xFF) << 2;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockPL12Y8
******************************************************************************/
static
IMG_VOID
pixel_DeblockPL12Y8(
    PIXEL_sGetSetCB       *psGetSetCB,
    IMG_UINT32 *        pui32Word
    )
{
    IMG_UINT32  w;
    IMG_UINT32  word;
	IMG_UINT32  numWords;
	PIXEL_sInfo *	psBufInfo	= IMG_NULL;
    IMG_UINT32  offset		= 0;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Y[offset++] = (word >> 0) & 0xFF;
        psGetSetCB->ui32Y[offset++] = (word >> 8) & 0xFF;
        psGetSetCB->ui32Y[offset++] = (word >> 16) & 0xFF;
        psGetSetCB->ui32Y[offset++] = (word >> 24) & 0xFF;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockPL12Y10
******************************************************************************/
static
IMG_VOID
pixel_DeblockPL12Y10(
    PIXEL_sGetSetCB       *psGetSetCB,
    IMG_UINT32 *        pui32Word
    )
{
    IMG_UINT32  w;
    IMG_UINT32  word;
	IMG_UINT32  numWords;
	PIXEL_sInfo *	psBufInfo	= IMG_NULL;
    IMG_UINT32  offset		= 0;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Y[offset++] = (word >>  0) & 0x3FF;
        psGetSetCB->ui32Y[offset++] = (word >> 10) & 0x3FF;
        psGetSetCB->ui32Y[offset++] = (word >> 20) & 0x3FF;
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockL16
******************************************************************************/
static
IMG_VOID
pixel_DeblockL16(
    PIXEL_sGetSetCB     *psGetSetCB,
    IMG_UINT32 *        pui32Word
    )
{
    IMG_UINT32  w;
    IMG_UINT32  word;
	IMG_UINT32  numWords;
	PIXEL_sInfo *	psBufInfo	= IMG_NULL;
    IMG_UINT32  offset		= 0;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Y[offset++] = (((word >> 0) >> 6) & 0x3FF);
        psGetSetCB->ui32Y[offset++] = (((word >> 16) >> 6) & 0x3FF);
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

/*!
******************************************************************************
@Function               pixel_DeblockL32
******************************************************************************/
static
IMG_VOID
pixel_DeblockL32(
    PIXEL_sGetSetCB     *psGetSetCB,
    IMG_UINT32 *        pui32Word
    )
{
    IMG_UINT32  w;
    IMG_UINT32  word;
	IMG_UINT32  numWords;
	PIXEL_sInfo *	psBufInfo	= IMG_NULL;
    IMG_UINT32  offset		= 0;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
	numWords = psBufInfo->ui32YBytesInBOP >> 2;

    for (w = 0; w < numWords; w++)
    {
        word = pui32Word[w];
        psGetSetCB->ui32Y[offset++] = ((word >> 22) & 0x3FF);
    }
	IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
}

#if (!defined (METAG) && !defined (MTXG)&& !defined(IMG_KERNEL_MODULE))
	/*!
	******************************************************************************
	@Function               pixel_DeblockF32
	******************************************************************************/
	static
	IMG_VOID
	pixel_DeblockF32(
	    PIXEL_sGetSetCB     *psGetSetCB,
	    IMG_UINT32 *        pui32Word
	    )
	{
	    IMG_UINT32		w;
		IMG_UINT32		numWords;
		IMG_uFLUINT32	uWord;
		PIXEL_sInfo *	psBufInfo	= IMG_NULL;
	    IMG_UINT32		offset		= 0;
	
		PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
		numWords = psBufInfo->ui32YBytesInBOP >> 2;
	
	    for (w = 0; w < numWords; w++)
	    {
			uWord.ui32x = pui32Word[w];
			psGetSetCB->ui32Y[offset++] = (((IMG_UINT32) uWord.fx) & 0x3FF);
	    }
		IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
	}
	
	/*!
	******************************************************************************
	@Function               pixel_DeblockF16
	******************************************************************************/
	static
	IMG_VOID
	pixel_DeblockF16(
	    PIXEL_sGetSetCB     *psGetSetCB,
	    IMG_UINT32 *        pui32Word
	    )
	{
	    IMG_UINT32		w;
	    IMG_UINT32		word;
		IMG_UINT32		numWords;
		IMG_UINT16		ui16Word;
		IMG_FLOAT		fWord;
		PIXEL_sInfo *	psBufInfo	= IMG_NULL;
	    IMG_UINT32		offset		= 0;
	
		PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
		numWords = psBufInfo->ui32YBytesInBOP >> 2;
	
	    for (w = 0; w < numWords; w++)
	    {
			word = pui32Word[w];
	
			ui16Word = (IMG_UINT16) (word & 0xFFFF);
			fWord = ConvertF16ToIEEE32(ui16Word);
			psGetSetCB->ui32Y[offset++] = ((((IMG_UINT32) fWord) >> 6) & 0x3FF);
	
			ui16Word = (IMG_UINT16) ((word & 0xFFFF0000) >> 16);
			fWord = ConvertF16ToIEEE32(ui16Word);
			psGetSetCB->ui32Y[offset++] = ((((IMG_UINT32) fWord) >> 6) & 0x3FF);
	    }
		IMG_ASSERT(offset == psBufInfo->ui32PixelsInBOP);
	}
#endif

/*!
******************************************************************************
@Function               pixel_DeblockNextBOPs

@Description
This function de-blocks the next block-of-pixels.
******************************************************************************/
IMG_VOID
pixel_DeblockNextBOPs(
    PIXEL_sGetSetCB *         psGetSetCB
    )
{
    IMG_UINT32              ui32Word[4];
    IMG_UINT32              ui32UVWord[4];
    IMG_UINT32              ui32AlphaWord[4];
    IMG_UINT32				*ptr;
	PIXEL_sInfo *			psBufInfo = IMG_NULL;

	PIXEL_GET_PIXEL_INFO(psGetSetCB->ePixelColourFormat,psBufInfo);
    ptr = (IMG_UINT32 *)PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvYBufAddr);

    /* Load required no. of words */
	switch (psBufInfo->ui32YBytesInBOP)
    {
        case 4:
            IMG_ASSERT(psGetSetCB->ePixelColourFormat == IMG_PIXFMT_CLUT1);
            ui32Word[0] = ptr[0];
            break;
        case 8:
            ui32Word[0] = ptr[0];
            ui32Word[1] = ptr[1];
            break;
        case 12:
            IMG_ASSERT( (psGetSetCB->ePixelColourFormat == IMG_PIXFMT_RGB888) ||
                        (psGetSetCB->ePixelColourFormat == IMG_PIXFMT_YUV888) );
            ui32Word[0] = ptr[0];
            ui32Word[1] = ptr[1];
            ui32Word[2] = ptr[2];
            break;
        case 16:
            ui32Word[0] = ptr[0];
            ui32Word[1] = ptr[1];
            ui32Word[2] = ptr[2];
            ui32Word[3] = ptr[3];
            break;
        case 48:
            IMG_ASSERT(psGetSetCB->ePixelColourFormat == IMG_PIXFMT_VYAUYA8888);
            break;
        default:
            /* Size not recognised */
            IMG_ASSERT(IMG_FALSE);
    }

    /* Load UV words if planar */
	if (psBufInfo->bIsPlanar)
    {
        ptr = (IMG_UINT32 *)PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvUVBufAddr);

		switch (psBufInfo->ui32UVBytesInBOP)
        {

            case 8:
                ui32UVWord[0] = ptr[0];
                ui32UVWord[1] = ptr[1];
                break;
            case 16:
                ui32UVWord[0] = ptr[0];
                ui32UVWord[1] = ptr[1];
                ui32UVWord[2] = ptr[2];
                ui32UVWord[3] = ptr[3];
                break;
            default:
                /* Size not recognised */
                IMG_ASSERT(IMG_FALSE);
        }
        if (psGetSetCB->pvVBufAddr != IMG_NULL)
        {
            ptr = (IMG_UINT32 *)PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvVBufAddr);

		    switch (psBufInfo->ui32UVBytesInBOP)
            {

                case 8:
                    ui32UVWord[2] = ptr[0];
                    ui32UVWord[3] = ptr[1];
                    break;
                default:
                    /* Size not recognised */
                    IMG_ASSERT(IMG_FALSE);
            }
        }
    }

    /* Load Alpha words if planar alpha */
	if (psBufInfo->bHasAlpha)
    {
        ptr = (IMG_UINT32 *)PIXEL_TWIDDLE_ADDRESS(psGetSetCB,psGetSetCB->pvAlphaBufAddr);

		switch (psBufInfo->ui32AlphaBytesInBOP)
        {

            case 16:
                ui32AlphaWord[0] = ptr[0];
                ui32AlphaWord[1] = ptr[1];
                ui32AlphaWord[2] = ptr[2];
                ui32AlphaWord[3] = ptr[3];
                break;
            default:
                /* Size not recognised */
                IMG_ASSERT(IMG_FALSE);
        }
    }

    switch (psGetSetCB->ePixelColourFormat)
    {
        case IMG_PIXFMT_CLUT1:          pixel_DeblockCLUT(psGetSetCB, ui32Word, 1, 0, IMG_FALSE);                     break;
        case IMG_PIXFMT_CLUT2:          pixel_DeblockCLUT(psGetSetCB, ui32Word, 2, 0, IMG_FALSE);                     break;
        case IMG_PIXFMT_CLUT4:          pixel_DeblockCLUT(psGetSetCB, ui32Word, 4, 0, IMG_FALSE);                     break;
        case IMG_PIXFMT_RGB8:           pixel_DeblockCLUT(psGetSetCB, ui32Word, 8, 0, IMG_FALSE);                     break;
        case IMG_PIXFMT_YUV8:           pixel_DeblockCLUT(psGetSetCB, ui32Word, 8, 0, IMG_FALSE);                     break;
       	case IMG_PIXFMT_I4A4:			pixel_DeblockCLUT(psGetSetCB, ui32Word, 4, 4, IMG_FALSE);                     break;
        case IMG_PIXFMT_I8A8:			pixel_DeblockCLUT(psGetSetCB, ui32Word, 8, 8, IMG_FALSE);                     break;
		case IMG_PIXFMT_A8I8:			pixel_DeblockCLUT(psGetSetCB, ui32Word, 8, 8, IMG_TRUE);                      break;
        case IMG_PIXFMT_RGB332:         pixel_DeblockRGB332(psGetSetCB, ui32Word);                                    break;
		case IMG_PIXFMT_ARGB8332:       pixel_DeblockARGB8332(psGetSetCB, ui32Word);                                  break;
        case IMG_PIXFMT_RGB565:         pixel_DeblockRGB565(psGetSetCB, ui32Word);                                    break;
        case IMG_PIXFMT_RGB555:         // fall through to next case
        case IMG_PIXFMT_ARGB1555:       pixel_DeblockRGB555AndARGB1555(psGetSetCB, ui32Word);                         break;
        case IMG_PIXFMT_ARGB4444:       pixel_DeblockARGB4444(psGetSetCB, ui32Word);                                  break;
        case IMG_PIXFMT_YUV888:         // fall through to next case
        case IMG_PIXFMT_RGB888:         pixel_DeblockRGB888(psGetSetCB, ui32Word);                                    break;
        case IMG_PIXFMT_ARGB8888:       pixel_DeblockARGB8888(psGetSetCB, ui32Word);                                  break;
		case IMG_PIXFMT_ABGR8888:       pixel_DeblockABGR8888(psGetSetCB, ui32Word);                                  break;
        case IMG_PIXFMT_BGRA8888:       pixel_DeblockBGRA8888(psGetSetCB, ui32Word);                                  break;
		case IMG_PIXFMT_AYUV4444:       pixel_DeblockAYUV4444(psGetSetCB, ui32Word);                                  break;
        case IMG_PIXFMT_UYVY8888:       pixel_DeblockUYVY8888(psGetSetCB, ui32Word);                                  break;
		case IMG_PIXFMT_VYUY8888:       pixel_DeblockVYUY8888(psGetSetCB, ui32Word);                                  break;
		case IMG_PIXFMT_YVYU8888:       pixel_DeblockYVYU8888(psGetSetCB, ui32Word);                                  break;        	
		case IMG_PIXFMT_YUYV8888:       pixel_DeblockYUYV8888(psGetSetCB, ui32Word);                                  break;        	
        case IMG_PIXFMT_YUV101010:      pixel_DeblockYUV101010(psGetSetCB, ui32Word);                                 break;
        case IMG_PIXFMT_UYVY10101010:   pixel_DeblockUYVY101010(psGetSetCB, ui32Word);                                break;
        case IMG_PIXFMT_VYAUYA8888:     pixel_DeblockVYAUYA8888(psGetSetCB);                                          break;
        case IMG_PIXFMT_AYUV8888:       pixel_DeblockAYUV8888(psGetSetCB, ui32Word);                                  break;
        case IMG_PIXFMT_AYUV2101010:    pixel_DeblockAYUV2101010(psGetSetCB, ui32Word);                               break;
        case IMG_PIXFMT_CVBS10:         pixel_DeblockCVBS10(psGetSetCB, ui32Word);                                    break;
        case IMG_PIXFMT_A4:             pixel_DeblockA4(psGetSetCB, ui32Word);                                        break;
        case IMG_PIXFMT_A8:             pixel_DeblockA8(psGetSetCB, ui32Word);                                        break;

        case IMG_PIXFMT_420PL8YUV8:     // fall through to next case
        case IMG_PIXFMT_422PL8YUV8:     pixel_Deblock42XPL8YUV8(psGetSetCB, ui32Word, ui32UVWord);                   break;

        case IMG_PIXFMT_420PL12YUV8:    // fall through to next case
        case IMG_PIXFMT_422PL12YUV8:    pixel_Deblock42XPL12YUV8(psGetSetCB, ui32Word, ui32UVWord);                   break;

        case IMG_PIXFMT_422PL12YVU8:	// fall through to next case
        case IMG_PIXFMT_420PL12YVU8:	pixel_Deblock42XPL12YVU8(psGetSetCB, ui32Word, ui32UVWord);                   break;

        case IMG_PIXFMT_411PL12YVU8:	pixel_Deblock411PL12YVU8(psGetSetCB, ui32Word, ui32UVWord);                   break;

        case IMG_PIXFMT_420PL12YUV8_A8: // fall through to next case
        case IMG_PIXFMT_422PL12YUV8_A8: pixel_Deblock42XPL12YUV8_A8(psGetSetCB, ui32Word, ui32UVWord, ui32AlphaWord); break;

        case IMG_PIXFMT_420PL8YUV10:    // fall through to next case
        case IMG_PIXFMT_422PL8YUV10:    pixel_Deblock42XPL8YUV10(psGetSetCB, ui32Word, ui32UVWord);                  break;

        case IMG_PIXFMT_420PL12YUV10:   // fall through to next case
        case IMG_PIXFMT_422PL12YUV10:   pixel_Deblock42XPL12YUV10(psGetSetCB, ui32Word, ui32UVWord);                  break;

        case IMG_PIXFMT_420PL12YVU10:   // fall through to next case
        case IMG_PIXFMT_422PL12YVU10:   pixel_Deblock42XPL12YVU10(psGetSetCB, ui32Word, ui32UVWord);                  break;

        case IMG_PIXFMT_PL12Y8:         pixel_DeblockPL12Y8(psGetSetCB, ui32Word);                                    break;
        case IMG_PIXFMT_PL12Y10:        pixel_DeblockPL12Y10(psGetSetCB, ui32Word);                                   break;
        case IMG_PIXFMT_PL12IMC2:       pixel_DeblockPL12IMC2(psGetSetCB);                                            break;
		
		case IMG_PIXFMT_PL12YV12:		pixel_DeblockPL12YV12(psGetSetCB, ui32Word);                                  break;	

		#if (!defined (METAG) && !defined (MTXG)&& !defined(IMG_KERNEL_MODULE))
			case IMG_PIXFMT_F16:			pixel_DeblockF16(psGetSetCB, ui32Word);										  break;
			case IMG_PIXFMT_F32:			pixel_DeblockF32(psGetSetCB, ui32Word);										  break;
		#endif
		case IMG_PIXFMT_L16:			pixel_DeblockL16(psGetSetCB, ui32Word);										  break;
		case IMG_PIXFMT_L32:			pixel_DeblockL32(psGetSetCB, ui32Word);										  break;

        default:                        IMG_ASSERT(IMG_FALSE);      // Pixel format not recognised
            break;
    }

    psGetSetCB->ui32PixelIndex  = 0;
	psGetSetCB->pvYBufAddr      += psBufInfo->ui32YBytesInBOP;
	psGetSetCB->pvUVBufAddr     += psBufInfo->ui32UVBytesInBOP;
    if (psGetSetCB->pvVBufAddr != IMG_NULL)
    {
	    psGetSetCB->pvVBufAddr      += psBufInfo->ui32UVBytesInBOP;
    }
	psGetSetCB->pvAlphaBufAddr  += psBufInfo->ui32AlphaBytesInBOP;
}
