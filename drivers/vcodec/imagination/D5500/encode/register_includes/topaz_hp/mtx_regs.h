/*!
 *****************************************************************************
 *
 * @File       mtx_regs.h
 * @Title      Register definition header file
 * @Description    This header file contains register definitions.
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

#ifndef _REGCONV_H_mtx_regs_h
#define _REGCONV_H_mtx_regs_h

#ifdef __cplusplus 
#include "img_types.h"
#include "systemc_utils.h"
#endif 


/* Register CR_MTX_ENABLE */
#define MTX_CR_MTX_ENABLE           0x0000
#define MASK_MTX_MTX_ENABLE         0x00000001
#define SHIFT_MTX_MTX_ENABLE        0
#define REGNUM_MTX_MTX_ENABLE       0x0000
#define SIGNED_MTX_MTX_ENABLE       0

#define MASK_MTX_MTX_TOFF           0x00000002
#define SHIFT_MTX_MTX_TOFF          1
#define REGNUM_MTX_MTX_TOFF         0x0000
#define SIGNED_MTX_MTX_TOFF         0

#define MASK_MTX_MTX_TSTOPPED       0x00000004
#define SHIFT_MTX_MTX_TSTOPPED      2
#define REGNUM_MTX_MTX_TSTOPPED     0x0000
#define SIGNED_MTX_MTX_TSTOPPED     0

#define MASK_MTX_MTX_STEP_REC       0x000000F0
#define SHIFT_MTX_MTX_STEP_REC      4
#define REGNUM_MTX_MTX_STEP_REC     0x0000
#define SIGNED_MTX_MTX_STEP_REC     0

#define MASK_MTX_MTX_ARCH           0x00000800
#define SHIFT_MTX_MTX_ARCH          11
#define REGNUM_MTX_MTX_ARCH         0x0000
#define SIGNED_MTX_MTX_ARCH         0

#define MASK_MTX_MTX_TCAPS          0x0000F000
#define SHIFT_MTX_MTX_TCAPS         12
#define REGNUM_MTX_MTX_TCAPS        0x0000
#define SIGNED_MTX_MTX_TCAPS        0

#define MASK_MTX_MTX_MIN_REV        0x00FF0000
#define SHIFT_MTX_MTX_MIN_REV       16
#define REGNUM_MTX_MTX_MIN_REV      0x0000
#define SIGNED_MTX_MTX_MIN_REV      0

#define MASK_MTX_MTX_MAJ_REV        0xFF000000
#define SHIFT_MTX_MTX_MAJ_REV       24
#define REGNUM_MTX_MTX_MAJ_REV      0x0000
#define SIGNED_MTX_MTX_MAJ_REV      0

/* Register CR_MTX_STATUS */
#define MTX_CR_MTX_STATUS           0x0008
#define MASK_MTX_MTX_CF_C           0x00000001
#define SHIFT_MTX_MTX_CF_C          0
#define REGNUM_MTX_MTX_CF_C         0x0008
#define SIGNED_MTX_MTX_CF_C         0

#define MASK_MTX_MTX_CR_O           0x00000002
#define SHIFT_MTX_MTX_CR_O          1
#define REGNUM_MTX_MTX_CR_O         0x0008
#define SIGNED_MTX_MTX_CR_O         0

#define MASK_MTX_MTX_CF_N           0x00000004
#define SHIFT_MTX_MTX_CF_N          2
#define REGNUM_MTX_MTX_CF_N         0x0008
#define SIGNED_MTX_MTX_CF_N         0

#define MASK_MTX_MTX_CF_Z           0x00000008
#define SHIFT_MTX_MTX_CF_Z          3
#define REGNUM_MTX_MTX_CF_Z         0x0008
#define SIGNED_MTX_MTX_CF_Z         0

#define MASK_MTX_MTX_LSM_STEP       0x00000700
#define SHIFT_MTX_MTX_LSM_STEP      8
#define REGNUM_MTX_MTX_LSM_STEP     0x0008
#define SIGNED_MTX_MTX_LSM_STEP     0

#define MASK_MTX_MTX_HREASON        0x000C0000
#define SHIFT_MTX_MTX_HREASON       18
#define REGNUM_MTX_MTX_HREASON      0x0008
#define SIGNED_MTX_MTX_HREASON      0

/* Register CR_MTX_KICK */
#define MTX_CR_MTX_KICK             0x0080
#define MASK_MTX_MTX_KICK           0x0000FFFF
#define SHIFT_MTX_MTX_KICK          0
#define REGNUM_MTX_MTX_KICK         0x0080
#define SIGNED_MTX_MTX_KICK         0

/* Register CR_MTX_KICKI */
#define MTX_CR_MTX_KICKI            0x0088
#define MASK_MTX_MTX_KICKI          0x0000FFFF
#define SHIFT_MTX_MTX_KICKI         0
#define REGNUM_MTX_MTX_KICKI        0x0088
#define SIGNED_MTX_MTX_KICKI        0

/* Register CR_MTX_FAULT0 */
#define MTX_CR_MTX_FAULT0           0x0090
#define MASK_MTX_REQ_SB             0x000000FF
#define SHIFT_MTX_REQ_SB            0
#define REGNUM_MTX_REQ_SB           0x0090
#define SIGNED_MTX_REQ_SB           0

#define MASK_MTX_REQ_RN_W           0x00000100
#define SHIFT_MTX_REQ_RN_W          8
#define REGNUM_MTX_REQ_RN_W         0x0090
#define SIGNED_MTX_REQ_RN_W         0

#define MASK_MTX_REQ_STATE          0x00000C00
#define SHIFT_MTX_REQ_STATE         10
#define REGNUM_MTX_REQ_STATE        0x0090
#define SIGNED_MTX_REQ_STATE        0

#define MASK_MTX_REQ_LD_DEST        0x00FF0000
#define SHIFT_MTX_REQ_LD_DEST       16
#define REGNUM_MTX_REQ_LD_DEST      0x0090
#define SIGNED_MTX_REQ_LD_DEST      0

#define MASK_MTX_REQ_LD_REG         0xF8000000
#define SHIFT_MTX_REQ_LD_REG        27
#define REGNUM_MTX_REQ_LD_REG       0x0090
#define SIGNED_MTX_REQ_LD_REG       0

/* Register CR_MTX_REGISTER_READ_WRITE_DATA */
#define MTX_CR_MTX_REGISTER_READ_WRITE_DATA 0x00F8
/* Register CR_MTX_REGISTER_READ_WRITE_REQUEST */
#define MTX_CR_MTX_REGISTER_READ_WRITE_REQUEST 0x00FC
#define MASK_MTX_MTX_USPECIFIER     0x0000000F
#define SHIFT_MTX_MTX_USPECIFIER    0
#define REGNUM_MTX_MTX_USPECIFIER   0x00FC
#define SIGNED_MTX_MTX_USPECIFIER   0

#define MASK_MTX_MTX_RSPECIFIER     0x00000070
#define SHIFT_MTX_MTX_RSPECIFIER    4
#define REGNUM_MTX_MTX_RSPECIFIER   0x00FC
#define SIGNED_MTX_MTX_RSPECIFIER   0

#define MASK_MTX_MTX_RNW            0x00010000
#define SHIFT_MTX_MTX_RNW           16
#define REGNUM_MTX_MTX_RNW          0x00FC
#define SIGNED_MTX_MTX_RNW          0

#define MASK_MTX_MTX_DREADY         0x80000000
#define SHIFT_MTX_MTX_DREADY        31
#define REGNUM_MTX_MTX_DREADY       0x00FC
#define SIGNED_MTX_MTX_DREADY       0

/* Register CR_MTX_RAM_ACCESS_DATA_EXCHANGE */
#define MTX_CR_MTX_RAM_ACCESS_DATA_EXCHANGE 0x0100
/* Register CR_MTX_RAM_ACCESS_DATA_TRANSFER */
#define MTX_CR_MTX_RAM_ACCESS_DATA_TRANSFER 0x0104
/* Register CR_MTX_RAM_ACCESS_CONTROL */
#define MTX_CR_MTX_RAM_ACCESS_CONTROL 0x0108
#define MASK_MTX_MTX_MCMR           0x00000001
#define SHIFT_MTX_MTX_MCMR          0
#define REGNUM_MTX_MTX_MCMR         0x0108
#define SIGNED_MTX_MTX_MCMR         0

#define MASK_MTX_MTX_MCMAI          0x00000002
#define SHIFT_MTX_MTX_MCMAI         1
#define REGNUM_MTX_MTX_MCMAI        0x0108
#define SIGNED_MTX_MTX_MCMAI        0

#define MASK_MTX_MTX_MCM_ADDR       0x000FFFFC
#define SHIFT_MTX_MTX_MCM_ADDR      2
#define REGNUM_MTX_MTX_MCM_ADDR     0x0108
#define SIGNED_MTX_MTX_MCM_ADDR     0

#define MASK_MTX_MTX_MCMID          0x0FF00000
#define SHIFT_MTX_MTX_MCMID         20
#define REGNUM_MTX_MTX_MCMID        0x0108
#define SIGNED_MTX_MTX_MCMID        0

/* Register CR_MTX_RAM_ACCESS_STATUS */
#define MTX_CR_MTX_RAM_ACCESS_STATUS 0x010C
#define MASK_MTX_MTX_MTX_MCM_STAT   0x00000001
#define SHIFT_MTX_MTX_MTX_MCM_STAT  0
#define REGNUM_MTX_MTX_MTX_MCM_STAT 0x010C
#define SIGNED_MTX_MTX_MTX_MCM_STAT 0

/* Register CR_MTX_SOFT_RESET */
#define MTX_CR_MTX_SOFT_RESET       0x0200
#define MASK_MTX_MTX_RESET          0x00000001
#define SHIFT_MTX_MTX_RESET         0
#define REGNUM_MTX_MTX_RESET        0x0200
#define SIGNED_MTX_MTX_RESET        0

/* Register CR_MTX_SYSC_CDMAC */
#define MTX_CR_MTX_SYSC_CDMAC       0x0340
#define MASK_MTX_LENGTH             0x0000FFFF
#define SHIFT_MTX_LENGTH            0
#define REGNUM_MTX_LENGTH           0x0340
#define SIGNED_MTX_LENGTH           0

#define MASK_MTX_ENABLE             0x00010000
#define SHIFT_MTX_ENABLE            16
#define REGNUM_MTX_ENABLE           0x0340
#define SIGNED_MTX_ENABLE           0

#define MASK_MTX_RNW                0x00020000
#define SHIFT_MTX_RNW               17
#define REGNUM_MTX_RNW              0x0340
#define SIGNED_MTX_RNW              0

#define MASK_MTX_BURSTSIZE          0x07000000
#define SHIFT_MTX_BURSTSIZE         24
#define REGNUM_MTX_BURSTSIZE        0x0340
#define SIGNED_MTX_BURSTSIZE        0

/* Register CR_MTX_SYSC_CDMAA */
#define MTX_CR_MTX_SYSC_CDMAA       0x0344
#define MASK_MTX_CDMAA_ADDRESS      0x03FFFFFC
#define SHIFT_MTX_CDMAA_ADDRESS     2
#define REGNUM_MTX_CDMAA_ADDRESS    0x0344
#define SIGNED_MTX_CDMAA_ADDRESS    0

/* Register CR_MTX_SYSC_CDMAS0 */
#define MTX_CR_MTX_SYSC_CDMAS0      0x0348
#define MASK_MTX_DONOTHING          0x00000001
#define SHIFT_MTX_DONOTHING         0
#define REGNUM_MTX_DONOTHING        0x0348
#define SIGNED_MTX_DONOTHING        0

#define MASK_MTX_DMAREQUEST         0x00000010
#define SHIFT_MTX_DMAREQUEST        4
#define REGNUM_MTX_DMAREQUEST       0x0348
#define SIGNED_MTX_DMAREQUEST       0

#define MASK_MTX_RAMNUMBER          0x00000F00
#define SHIFT_MTX_RAMNUMBER         8
#define REGNUM_MTX_RAMNUMBER        0x0348
#define SIGNED_MTX_RAMNUMBER        0

#define MASK_MTX_COUNT              0xFFFF0000
#define SHIFT_MTX_COUNT             16
#define REGNUM_MTX_COUNT            0x0348
#define SIGNED_MTX_COUNT            0

/* Register CR_MTX_SYSC_CDMAS1 */
#define MTX_CR_MTX_SYSC_CDMAS1      0x034C
#define MASK_MTX_CDMAS1_ADDRESS     0x03FFFFFC
#define SHIFT_MTX_CDMAS1_ADDRESS    2
#define REGNUM_MTX_CDMAS1_ADDRESS   0x034C
#define SIGNED_MTX_CDMAS1_ADDRESS   0

/* Register CR_MTX_SYSC_CDMAT */
#define MTX_CR_MTX_SYSC_CDMAT       0x0350
#define MASK_MTX_TRANSFERDATA       0xFFFFFFFF
#define SHIFT_MTX_TRANSFERDATA      0
#define REGNUM_MTX_TRANSFERDATA     0x0350
#define SIGNED_MTX_TRANSFERDATA     0

/* Register TXTIMER */
#define MTX_CR_MTX_TXTIMER			0x00000010

/* Register TIMER_DIV */
#define MTX_CR_MTX_SYSC_TIMER_DIV	0x00000208
#define MASK_MTX_TIMER_EN			0x00010000
#define MASK_MTX_TIMER_DIV			0x00000FFF

/*
	Byte range covering the group MTX_CORE file
*/

#define MTX_MTX_CORE_REGISTERS_START		0x00000000
#define MTX_MTX_CORE_REGISTERS_END  		0x00000353

/*
	Byte range covering the whole register file
*/

#define MTX_REGISTERS_START		0x00000000
#define MTX_REGISTERS_END  		0x00000353
#define MTX_REG_DEFAULT_TABLE struct {\
			IMG_UINT16 uRegOffset;\
			IMG_UINT32 uRegDefault;\
			IMG_UINT32 uRegMask;\
			bool bReadonly;\
			const char* pszName;\
		} MTX_Defaults[] = {\
	{0x0000, 0x00000000, 0xFFFFF8F7, 0, "CR_MTX_ENABLE" } ,\
	{0x0008, 0x00000000, 0x000C070F, 0, "CR_MTX_STATUS" } ,\
	{0x0080, 0x00000000, 0x0000FFFF, 0, "CR_MTX_KICK" } ,\
	{0x0088, 0x00000000, 0x0000FFFF, 0, "CR_MTX_KICKI" } ,\
	{0x0090, 0x00000000, 0xF8FF0DFF, 0, "CR_MTX_FAULT0" } ,\
	{0x00F8, 0x00000000, 0x00000000, 0, "CR_MTX_REGISTER_READ_WRITE_DATA" } ,\
	{0x00FC, 0x00000000, 0x8001007F, 0, "CR_MTX_REGISTER_READ_WRITE_REQUEST" } ,\
	{0x0100, 0x00000000, 0x00000000, 0, "CR_MTX_RAM_ACCESS_DATA_EXCHANGE" } ,\
	{0x0104, 0x00000000, 0x00000000, 0, "CR_MTX_RAM_ACCESS_DATA_TRANSFER" } ,\
	{0x0108, 0x00000000, 0x0FFFFFFF, 0, "CR_MTX_RAM_ACCESS_CONTROL" } ,\
	{0x010C, 0x00000000, 0x00000001, 0, "CR_MTX_RAM_ACCESS_STATUS" } ,\
	{0x0200, 0x00000000, 0x00000001, 0, "CR_MTX_SOFT_RESET" } ,\
	{0x0340, 0x00000000, 0x0703FFFF, 0, "CR_MTX_SYSC_CDMAC" } ,\
	{0x0344, 0x00000000, 0x03FFFFFC, 0, "CR_MTX_SYSC_CDMAA" } ,\
	{0x0348, 0x00000001, 0xFFFF0F11, 1, "CR_MTX_SYSC_CDMAS0" } ,\
	{0x034C, 0x00000000, 0x03FFFFFC, 1, "CR_MTX_SYSC_CDMAS1" } ,\
	{0x0350, 0x00000000, 0xFFFFFFFF, 0, "CR_MTX_SYSC_CDMAT" } ,\
{ 0 }}

#define MTX_REGS_INIT(uBase) \
	{ \
		int n;\
		MTX_REG_DEFAULT_TABLE;\
		for (n = 0; n < sizeof(MTX_Defaults)/ sizeof(MTX_Defaults[0] ) -1; n++)\
		{\
			RegWriteNoTrap(MTX_Defaults[n].uRegOffset + uBase, MTX_Defaults[n].uRegDefault); \
		}\
	}
#endif
