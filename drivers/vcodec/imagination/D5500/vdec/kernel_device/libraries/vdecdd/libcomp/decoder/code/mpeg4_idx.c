/*!
 *****************************************************************************
 *
 * @File       mpeg4_idx.c
 * @Title      mpeg4 vlc index tables
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
/* for each table in gui16mpeg4_tablesVlcTableData[] */

#include <img_types.h>

extern IMG_UINT16 gaui16mpeg4VlcIndexData[17][3];
extern const IMG_UINT8 gui8mpeg4VlcIndexSize;

IMG_UINT16 gaui16mpeg4VlcIndexData[17][3] = {
	{2,	5,	0},		/* B6_mcbpc_i_s_vops_piece.out */
	{2,	5,	11},		/* B7_mcbpc_p_s_vops_update.out */
	{0,	3,	40},		/* B8_cbpy_intra.out */
	{0,	3,	63},		/* B8_cbpy_inter.out */
	{2,	1,	84},		/* B3_modb.out */
	{2,	3,	87},		/* B4_mb_type.out */
	{1,	1,	92},		/* 6_33_dbquant.out */
	{2,	5,	95},		/* B12_mvd.out */
	{0,	1,	137},		/* B13_dct_dc_size_luminance.out */
	{0,	1,	154},		/* B14_dct_dc_size_chrominance.out */
	{0,	3,	170},		/* B16_intra_tcoeff.out */
	{0,	3,	286},		/* B17_inter_tcoeff.out */
	{0,	3,	392},		/* B23_rvlc_tcoeff_0.out */
	{0,	3,	659},		/* B23_rvlc_tcoeff_1.out */
	{1,	5,	926},		/* B29_MVDs.out */
	{1,	5,	945},		/* B30_MVDs.out */
	{1,	1,	963},		/* B31_conv_ratio.out */
};

const IMG_UINT8 gui8mpeg4VlcIndexSize = 17;

/* EOF */
