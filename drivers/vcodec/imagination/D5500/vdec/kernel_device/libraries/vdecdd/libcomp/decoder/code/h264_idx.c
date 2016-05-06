/*!
 *****************************************************************************
 *
 * @File       h264_idx.c
 * @Title      h264 vlc index table
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

/* format is: inital_opcode, initial_width, address */
/* for each table in gui16H264VlcTableData[] */

#include <img_types.h>

extern IMG_UINT16 gaui16h264VlcIndexData[][3];
extern const IMG_UINT8 gui8h264VlcIndexSize;

IMG_UINT16 gaui16h264VlcIndexData[38][3] = {
	{2,	5,	0},		/* NumCoeffTrailingOnes_Table9-5_nC_0-1.out */
	{0,	3,	76},		/* NumCoeffTrailingOnes_Table9-5_nC_2-3.out */
	{0,	3,	160},		/* NumCoeffTrailingOnes_Table9-5_nC_4-7.out */
	{0,	2,	231},		/* NumCoeffTrailingOnesFixedLen.out */
	{2,	2,	244},		/* NumCoeffTrailingOnesChromaDC_YUV420.out */
	{2,	5,	261},		/* NumCoeffTrailingOnesChromaDC_YUV422.out */
	{2,	5,	301},		/* TotalZeros_00.out */
	{0,	2,	326},		/* TotalZeros_01.out */
	{0,	2,	345},		/* TotalZeros_02.out */
	{0,	2,	363},		/* TotalZeros_03.out */
	{0,	2,	379},		/* TotalZeros_04.out */
	{0,	2,	394},		/* TotalZeros_05.out */
	{0,	2,	406},		/* TotalZeros_06.out */
	{0,	1,	418},		/* TotalZeros_07.out */
	{0,	1,	429},		/* TotalZeros_08.out */
	{0,	1,	438},		/* TotalZeros_09.out */
	{2,	2,	446},		/* TotalZeros_10.out */
	{2,	2,	452},		/* TotalZeros_11.out */
	{2,	1,	456},		/* TotalZeros_12.out */
	{0,	0,	459},		/* TotalZeros_13.out */
	{0,	0,	461},		/* TotalZeros_14.out */
	{2,	2,	463},		/* TotalZerosChromaDC_YUV420_00.out */
	{2,	1,	467},		/* TotalZerosChromaDC_YUV420_01.out */
	{0,	0,	470},		/* TotalZerosChromaDC_YUV420_02.out */
	{0,	0,	472},		/* Run_00.out */
	{2,	1,	474},		/* Run_01.out */
	{0,	1,	477},		/* Run_02.out */
	{0,	1,	481},		/* Run_03.out */
	{1,	1,	487},		/* Run_04.out */
	{0,	2,	494},		/* Run_05.out */
	{0,	2,	502},		/* Run_06.out */
    {2, 4,  520},       /* TotalZerosChromaDC_YUV422_00.out */
    {2, 2,  526},       /* TotalZerosChromaDC_YUV422_01.out */
    {0, 1,  530},       /* TotalZerosChromaDC_YUV422_02.out */
    {1, 2,  534},       /* TotalZerosChromaDC_YUV422_03.out */
    {0, 0,  538},       /* TotalZerosChromaDC_YUV422_04.out */
    {0, 0,  540},       /* TotalZerosChromaDC_YUV422_05.out */
    {0, 0,  542},       /* TotalZerosChromaDC_YUV422_06.out */
};

const IMG_UINT8	gui8h264VlcIndexSize = 38;

/* EOF */
