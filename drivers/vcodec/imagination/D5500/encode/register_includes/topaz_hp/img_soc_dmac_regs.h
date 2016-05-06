/*!
 *****************************************************************************
 *
 * @File       img_soc_dmac_regs.h
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

#ifndef _REGCONV_H_img_soc_dmac_regs_h
#define _REGCONV_H_img_soc_dmac_regs_h

#ifdef __cplusplus 
#include "img_types.h"
#include "systemc_utils.h"
#endif 


/* Register DMAC_SETUP_0 */
#define IMG_SOC_DMAC_SETUP_0        0x0000
#define MASK_IMG_SOC_START_ADDRESS_00 0xFFFFFFFF
#define SHIFT_IMG_SOC_START_ADDRESS_00 0
#define REGNUM_IMG_SOC_START_ADDRESS_00 0x0000
#define SIGNED_IMG_SOC_START_ADDRESS_00 0

/* Register DMAC_COUNT_0 */
#define IMG_SOC_DMAC_COUNT_0        0x0004
#define MASK_IMG_SOC_CNT_00         0x0000FFFF
#define SHIFT_IMG_SOC_CNT_00        0
#define REGNUM_IMG_SOC_CNT_00       0x0004
#define SIGNED_IMG_SOC_CNT_00       0

#define MASK_IMG_SOC_EN_00          0x00010000
#define SHIFT_IMG_SOC_EN_00         16
#define REGNUM_IMG_SOC_EN_00        0x0004
#define SIGNED_IMG_SOC_EN_00        0

#define MASK_IMG_SOC_ENABLE_2D_MODE_00 0x00020000
#define SHIFT_IMG_SOC_ENABLE_2D_MODE_00 17
#define REGNUM_IMG_SOC_ENABLE_2D_MODE_00 0x0004
#define SIGNED_IMG_SOC_ENABLE_2D_MODE_00 0
#define IMG_SOC_ENABLE_2D_MODE_00_ENABLED		0x00000001
#define IMG_SOC_ENABLE_2D_MODE_00_DISABLED		0x00000000

#define MASK_IMG_SOC_LIST_EN_00     0x00040000
#define SHIFT_IMG_SOC_LIST_EN_00    18
#define REGNUM_IMG_SOC_LIST_EN_00   0x0004
#define SIGNED_IMG_SOC_LIST_EN_00   0

#define MASK_IMG_SOC_SRST_00        0x00080000
#define SHIFT_IMG_SOC_SRST_00       19
#define REGNUM_IMG_SOC_SRST_00      0x0004
#define SIGNED_IMG_SOC_SRST_00      0

#define MASK_IMG_SOC_DREQ_00        0x00100000
#define SHIFT_IMG_SOC_DREQ_00       20
#define REGNUM_IMG_SOC_DREQ_00      0x0004
#define SIGNED_IMG_SOC_DREQ_00      0

#define MASK_IMG_SOC_LIST_FIN_CTL_00 0x00400000
#define SHIFT_IMG_SOC_LIST_FIN_CTL_00 22
#define REGNUM_IMG_SOC_LIST_FIN_CTL_00 0x0004
#define SIGNED_IMG_SOC_LIST_FIN_CTL_00 0

#define MASK_IMG_SOC_PI_00          0x03000000
#define SHIFT_IMG_SOC_PI_00         24
#define REGNUM_IMG_SOC_PI_00        0x0004
#define SIGNED_IMG_SOC_PI_00        0
#define IMG_SOC_PI_00_1		0x00000002
#define IMG_SOC_PI_00_2		0x00000001
#define IMG_SOC_PI_00_4		0x00000000

#define MASK_IMG_SOC_DIR_00         0x04000000
#define SHIFT_IMG_SOC_DIR_00        26
#define REGNUM_IMG_SOC_DIR_00       0x0004
#define SIGNED_IMG_SOC_DIR_00       0

#define MASK_IMG_SOC_PW_00          0x18000000
#define SHIFT_IMG_SOC_PW_00         27
#define REGNUM_IMG_SOC_PW_00        0x0004
#define SIGNED_IMG_SOC_PW_00        0

#define MASK_IMG_SOC_TRANSFER_IEN_00 0x20000000
#define SHIFT_IMG_SOC_TRANSFER_IEN_00 29
#define REGNUM_IMG_SOC_TRANSFER_IEN_00 0x0004
#define SIGNED_IMG_SOC_TRANSFER_IEN_00 0

#define MASK_IMG_SOC_BSWAP_00       0x40000000
#define SHIFT_IMG_SOC_BSWAP_00      30
#define REGNUM_IMG_SOC_BSWAP_00     0x0004
#define SIGNED_IMG_SOC_BSWAP_00     0

#define MASK_IMG_SOC_LIST_IEN_00    0x80000000
#define SHIFT_IMG_SOC_LIST_IEN_00   31
#define REGNUM_IMG_SOC_LIST_IEN_00  0x0004
#define SIGNED_IMG_SOC_LIST_IEN_00  0

/* Register DMAC_PERIPH_0 */
#define IMG_SOC_DMAC_PERIPH_0       0x0008
#define MASK_IMG_SOC_EXT_SA_00      0x0000000F
#define SHIFT_IMG_SOC_EXT_SA_00     0
#define REGNUM_IMG_SOC_EXT_SA_00    0x0008
#define SIGNED_IMG_SOC_EXT_SA_00    0

#define MASK_IMG_SOC_BURST_00       0x07000000
#define SHIFT_IMG_SOC_BURST_00      24
#define REGNUM_IMG_SOC_BURST_00     0x0008
#define SIGNED_IMG_SOC_BURST_00     0

#define MASK_IMG_SOC_INCR_00        0x08000000
#define SHIFT_IMG_SOC_INCR_00       27
#define REGNUM_IMG_SOC_INCR_00      0x0008
#define SIGNED_IMG_SOC_INCR_00      0

#define MASK_IMG_SOC_ACC_DEL_00     0xE0000000
#define SHIFT_IMG_SOC_ACC_DEL_00    29
#define REGNUM_IMG_SOC_ACC_DEL_00   0x0008
#define SIGNED_IMG_SOC_ACC_DEL_00   0

/* Register DMAC_IRQ_STAT_0 */
#define IMG_SOC_DMAC_IRQ_STAT_0     0x000C
#define MASK_IMG_SOC_TRANSFER_FIN_00 0x00020000
#define SHIFT_IMG_SOC_TRANSFER_FIN_00 17
#define REGNUM_IMG_SOC_TRANSFER_FIN_00 0x000C
#define SIGNED_IMG_SOC_TRANSFER_FIN_00 0

#define MASK_IMG_SOC_LIST_INT_00    0x00100000
#define SHIFT_IMG_SOC_LIST_INT_00   20
#define REGNUM_IMG_SOC_LIST_INT_00  0x000C
#define SIGNED_IMG_SOC_LIST_INT_00  0
#define IMG_SOC_LIST_INT_00_ENABLE		0x00000001		/* The last linked-list element processed initiated an interrupt.  If LIST_IEN is set
 for the channel, an interrupt will be generated on the IRQ line until this bit is cleared, */
#define IMG_SOC_LIST_INT_00_DISABLE		0x00000000		/* last linked list element processed did not initiate an interrupt. */

#define MASK_IMG_SOC_LIST_FIN_00    0x00200000
#define SHIFT_IMG_SOC_LIST_FIN_00   21
#define REGNUM_IMG_SOC_LIST_FIN_00  0x000C
#define SIGNED_IMG_SOC_LIST_FIN_00  0

/* Register DMAC_2D_MODE_0 */
#define IMG_SOC_DMAC_2D_MODE_0      0x0010
#define MASK_IMG_SOC_ROW_LENGTH_00  0x000003FF
#define SHIFT_IMG_SOC_ROW_LENGTH_00 0
#define REGNUM_IMG_SOC_ROW_LENGTH_00 0x0010
#define SIGNED_IMG_SOC_ROW_LENGTH_00 0

#define MASK_IMG_SOC_LINE_ADDR_OFFSET_00 0x000FFC00
#define SHIFT_IMG_SOC_LINE_ADDR_OFFSET_00 10
#define REGNUM_IMG_SOC_LINE_ADDR_OFFSET_00 0x0010
#define SIGNED_IMG_SOC_LINE_ADDR_OFFSET_00 0

#define MASK_IMG_SOC_REP_COUNT_00   0x7FF00000
#define SHIFT_IMG_SOC_REP_COUNT_00  20
#define REGNUM_IMG_SOC_REP_COUNT_00 0x0010
#define SIGNED_IMG_SOC_REP_COUNT_00 0

/* Register DMAC_PERIPHERAL_ADDR_0 */
#define IMG_SOC_DMAC_PERIPHERAL_ADDR_0 0x0014
#define MASK_IMG_SOC_ADDR_00        0x007FFFFF
#define SHIFT_IMG_SOC_ADDR_00       0
#define REGNUM_IMG_SOC_ADDR_00      0x0014
#define SIGNED_IMG_SOC_ADDR_00      0

/* Register DMAC_PER_HOLD_0 */
#define IMG_SOC_DMAC_PER_HOLD_0     0x0018
#define MASK_IMG_SOC_PER_HOLD_00    0x0000007F
#define SHIFT_IMG_SOC_PER_HOLD_00   0
#define REGNUM_IMG_SOC_PER_HOLD_00  0x0018
#define SIGNED_IMG_SOC_PER_HOLD_00  0

/* Register DMAC_SETUP_1 */
#define IMG_SOC_DMAC_SETUP_1        0x0020
#define MASK_IMG_SOC_START_ADDRESS_01 0xFFFFFFFF
#define SHIFT_IMG_SOC_START_ADDRESS_01 0
#define REGNUM_IMG_SOC_START_ADDRESS_01 0x0020
#define SIGNED_IMG_SOC_START_ADDRESS_01 0

/* Register DMAC_COUNT_1 */
#define IMG_SOC_DMAC_COUNT_1        0x0024
#define MASK_IMG_SOC_CNT_01         0x0000FFFF
#define SHIFT_IMG_SOC_CNT_01        0
#define REGNUM_IMG_SOC_CNT_01       0x0024
#define SIGNED_IMG_SOC_CNT_01       0

#define MASK_IMG_SOC_EN_01          0x00010000
#define SHIFT_IMG_SOC_EN_01         16
#define REGNUM_IMG_SOC_EN_01        0x0024
#define SIGNED_IMG_SOC_EN_01        0

#define MASK_IMG_SOC_ENABLE_2D_MODE_01 0x00020000
#define SHIFT_IMG_SOC_ENABLE_2D_MODE_01 17
#define REGNUM_IMG_SOC_ENABLE_2D_MODE_01 0x0024
#define SIGNED_IMG_SOC_ENABLE_2D_MODE_01 0
#define IMG_SOC_ENABLE_2D_MODE_01_ENABLED		0x00000001
#define IMG_SOC_ENABLE_2D_MODE_01_DISABLED		0x00000000

#define MASK_IMG_SOC_LIST_EN_01     0x00040000
#define SHIFT_IMG_SOC_LIST_EN_01    18
#define REGNUM_IMG_SOC_LIST_EN_01   0x0024
#define SIGNED_IMG_SOC_LIST_EN_01   0

#define MASK_IMG_SOC_SRST_01        0x00080000
#define SHIFT_IMG_SOC_SRST_01       19
#define REGNUM_IMG_SOC_SRST_01      0x0024
#define SIGNED_IMG_SOC_SRST_01      0

#define MASK_IMG_SOC_DREQ_01        0x00100000
#define SHIFT_IMG_SOC_DREQ_01       20
#define REGNUM_IMG_SOC_DREQ_01      0x0024
#define SIGNED_IMG_SOC_DREQ_01      0

#define MASK_IMG_SOC_LIST_FIN_CTL_01 0x00400000
#define SHIFT_IMG_SOC_LIST_FIN_CTL_01 22
#define REGNUM_IMG_SOC_LIST_FIN_CTL_01 0x0024
#define SIGNED_IMG_SOC_LIST_FIN_CTL_01 0

#define MASK_IMG_SOC_PI_01          0x03000000
#define SHIFT_IMG_SOC_PI_01         24
#define REGNUM_IMG_SOC_PI_01        0x0024
#define SIGNED_IMG_SOC_PI_01        0
#define IMG_SOC_PI_01_1		0x00000002
#define IMG_SOC_PI_01_2		0x00000001
#define IMG_SOC_PI_01_4		0x00000000

#define MASK_IMG_SOC_DIR_01         0x04000000
#define SHIFT_IMG_SOC_DIR_01        26
#define REGNUM_IMG_SOC_DIR_01       0x0024
#define SIGNED_IMG_SOC_DIR_01       0

#define MASK_IMG_SOC_PW_01          0x18000000
#define SHIFT_IMG_SOC_PW_01         27
#define REGNUM_IMG_SOC_PW_01        0x0024
#define SIGNED_IMG_SOC_PW_01        0

#define MASK_IMG_SOC_TRANSFER_IEN_01 0x20000000
#define SHIFT_IMG_SOC_TRANSFER_IEN_01 29
#define REGNUM_IMG_SOC_TRANSFER_IEN_01 0x0024
#define SIGNED_IMG_SOC_TRANSFER_IEN_01 0

#define MASK_IMG_SOC_BSWAP_01       0x40000000
#define SHIFT_IMG_SOC_BSWAP_01      30
#define REGNUM_IMG_SOC_BSWAP_01     0x0024
#define SIGNED_IMG_SOC_BSWAP_01     0

#define MASK_IMG_SOC_LIST_IEN_01    0x80000000
#define SHIFT_IMG_SOC_LIST_IEN_01   31
#define REGNUM_IMG_SOC_LIST_IEN_01  0x0024
#define SIGNED_IMG_SOC_LIST_IEN_01  0

/* Register DMAC_PERIPH_1 */
#define IMG_SOC_DMAC_PERIPH_1       0x0028
#define MASK_IMG_SOC_EXT_SA_01      0x0000000F
#define SHIFT_IMG_SOC_EXT_SA_01     0
#define REGNUM_IMG_SOC_EXT_SA_01    0x0028
#define SIGNED_IMG_SOC_EXT_SA_01    0

#define MASK_IMG_SOC_BURST_01       0x07000000
#define SHIFT_IMG_SOC_BURST_01      24
#define REGNUM_IMG_SOC_BURST_01     0x0028
#define SIGNED_IMG_SOC_BURST_01     0

#define MASK_IMG_SOC_INCR_01        0x08000000
#define SHIFT_IMG_SOC_INCR_01       27
#define REGNUM_IMG_SOC_INCR_01      0x0028
#define SIGNED_IMG_SOC_INCR_01      0

#define MASK_IMG_SOC_ACC_DEL_01     0xE0000000
#define SHIFT_IMG_SOC_ACC_DEL_01    29
#define REGNUM_IMG_SOC_ACC_DEL_01   0x0028
#define SIGNED_IMG_SOC_ACC_DEL_01   0

/* Register DMAC_IRQ_STAT_1 */
#define IMG_SOC_DMAC_IRQ_STAT_1     0x002C
#define MASK_IMG_SOC_TRANSFER_FIN_01 0x00020000
#define SHIFT_IMG_SOC_TRANSFER_FIN_01 17
#define REGNUM_IMG_SOC_TRANSFER_FIN_01 0x002C
#define SIGNED_IMG_SOC_TRANSFER_FIN_01 0

#define MASK_IMG_SOC_LIST_INT_01    0x00100000
#define SHIFT_IMG_SOC_LIST_INT_01   20
#define REGNUM_IMG_SOC_LIST_INT_01  0x002C
#define SIGNED_IMG_SOC_LIST_INT_01  0
#define IMG_SOC_LIST_INT_01_ENABLE		0x00000001		/* The last linked-list element processed initiated an interrupt.  If LIST_IEN is set
 for the channel, an interrupt will be generated on the IRQ line until this bit is cleared, */
#define IMG_SOC_LIST_INT_01_DISABLE		0x00000000		/* last linked list element processed did not initiate an interrupt. */

#define MASK_IMG_SOC_LIST_FIN_01    0x00200000
#define SHIFT_IMG_SOC_LIST_FIN_01   21
#define REGNUM_IMG_SOC_LIST_FIN_01  0x002C
#define SIGNED_IMG_SOC_LIST_FIN_01  0

/* Register DMAC_2D_MODE_1 */
#define IMG_SOC_DMAC_2D_MODE_1      0x0030
#define MASK_IMG_SOC_ROW_LENGTH_01  0x000003FF
#define SHIFT_IMG_SOC_ROW_LENGTH_01 0
#define REGNUM_IMG_SOC_ROW_LENGTH_01 0x0030
#define SIGNED_IMG_SOC_ROW_LENGTH_01 0

#define MASK_IMG_SOC_LINE_ADDR_OFFSET_01 0x000FFC00
#define SHIFT_IMG_SOC_LINE_ADDR_OFFSET_01 10
#define REGNUM_IMG_SOC_LINE_ADDR_OFFSET_01 0x0030
#define SIGNED_IMG_SOC_LINE_ADDR_OFFSET_01 0

#define MASK_IMG_SOC_REP_COUNT_01   0x7FF00000
#define SHIFT_IMG_SOC_REP_COUNT_01  20
#define REGNUM_IMG_SOC_REP_COUNT_01 0x0030
#define SIGNED_IMG_SOC_REP_COUNT_01 0

/* Register DMAC_PERIPHERAL_ADDR_1 */
#define IMG_SOC_DMAC_PERIPHERAL_ADDR_1 0x0034
#define MASK_IMG_SOC_ADDR_01        0x007FFFFF
#define SHIFT_IMG_SOC_ADDR_01       0
#define REGNUM_IMG_SOC_ADDR_01      0x0034
#define SIGNED_IMG_SOC_ADDR_01      0

/* Register DMAC_PER_HOLD_1 */
#define IMG_SOC_DMAC_PER_HOLD_1     0x0038
#define MASK_IMG_SOC_PER_HOLD_01    0x0000007F
#define SHIFT_IMG_SOC_PER_HOLD_01   0
#define REGNUM_IMG_SOC_PER_HOLD_01  0x0038
#define SIGNED_IMG_SOC_PER_HOLD_01  0

/* Register DMAC_SETUP_2 */
#define IMG_SOC_DMAC_SETUP_2        0x0040
#define MASK_IMG_SOC_START_ADDRESS_02 0xFFFFFFFF
#define SHIFT_IMG_SOC_START_ADDRESS_02 0
#define REGNUM_IMG_SOC_START_ADDRESS_02 0x0040
#define SIGNED_IMG_SOC_START_ADDRESS_02 0

/* Register DMAC_COUNT_2 */
#define IMG_SOC_DMAC_COUNT_2        0x0044
#define MASK_IMG_SOC_CNT_02         0x0000FFFF
#define SHIFT_IMG_SOC_CNT_02        0
#define REGNUM_IMG_SOC_CNT_02       0x0044
#define SIGNED_IMG_SOC_CNT_02       0

#define MASK_IMG_SOC_EN_02          0x00010000
#define SHIFT_IMG_SOC_EN_02         16
#define REGNUM_IMG_SOC_EN_02        0x0044
#define SIGNED_IMG_SOC_EN_02        0

#define MASK_IMG_SOC_ENABLE_2D_MODE_02 0x00020000
#define SHIFT_IMG_SOC_ENABLE_2D_MODE_02 17
#define REGNUM_IMG_SOC_ENABLE_2D_MODE_02 0x0044
#define SIGNED_IMG_SOC_ENABLE_2D_MODE_02 0
#define IMG_SOC_ENABLE_2D_MODE_02_ENABLED		0x00000001
#define IMG_SOC_ENABLE_2D_MODE_02_DISABLED		0x00000000

#define MASK_IMG_SOC_LIST_EN_02     0x00040000
#define SHIFT_IMG_SOC_LIST_EN_02    18
#define REGNUM_IMG_SOC_LIST_EN_02   0x0044
#define SIGNED_IMG_SOC_LIST_EN_02   0

#define MASK_IMG_SOC_SRST_02        0x00080000
#define SHIFT_IMG_SOC_SRST_02       19
#define REGNUM_IMG_SOC_SRST_02      0x0044
#define SIGNED_IMG_SOC_SRST_02      0

#define MASK_IMG_SOC_DREQ_02        0x00100000
#define SHIFT_IMG_SOC_DREQ_02       20
#define REGNUM_IMG_SOC_DREQ_02      0x0044
#define SIGNED_IMG_SOC_DREQ_02      0

#define MASK_IMG_SOC_LIST_FIN_CTL_02 0x00400000
#define SHIFT_IMG_SOC_LIST_FIN_CTL_02 22
#define REGNUM_IMG_SOC_LIST_FIN_CTL_02 0x0044
#define SIGNED_IMG_SOC_LIST_FIN_CTL_02 0

#define MASK_IMG_SOC_PI_02          0x03000000
#define SHIFT_IMG_SOC_PI_02         24
#define REGNUM_IMG_SOC_PI_02        0x0044
#define SIGNED_IMG_SOC_PI_02        0
#define IMG_SOC_PI_02_1		0x00000002
#define IMG_SOC_PI_02_2		0x00000001
#define IMG_SOC_PI_02_4		0x00000000

#define MASK_IMG_SOC_DIR_02         0x04000000
#define SHIFT_IMG_SOC_DIR_02        26
#define REGNUM_IMG_SOC_DIR_02       0x0044
#define SIGNED_IMG_SOC_DIR_02       0

#define MASK_IMG_SOC_PW_02          0x18000000
#define SHIFT_IMG_SOC_PW_02         27
#define REGNUM_IMG_SOC_PW_02        0x0044
#define SIGNED_IMG_SOC_PW_02        0

#define MASK_IMG_SOC_TRANSFER_IEN_02 0x20000000
#define SHIFT_IMG_SOC_TRANSFER_IEN_02 29
#define REGNUM_IMG_SOC_TRANSFER_IEN_02 0x0044
#define SIGNED_IMG_SOC_TRANSFER_IEN_02 0

#define MASK_IMG_SOC_BSWAP_02       0x40000000
#define SHIFT_IMG_SOC_BSWAP_02      30
#define REGNUM_IMG_SOC_BSWAP_02     0x0044
#define SIGNED_IMG_SOC_BSWAP_02     0

#define MASK_IMG_SOC_LIST_IEN_02    0x80000000
#define SHIFT_IMG_SOC_LIST_IEN_02   31
#define REGNUM_IMG_SOC_LIST_IEN_02  0x0044
#define SIGNED_IMG_SOC_LIST_IEN_02  0

/* Register DMAC_PERIPH_2 */
#define IMG_SOC_DMAC_PERIPH_2       0x0048
#define MASK_IMG_SOC_EXT_SA_02      0x0000000F
#define SHIFT_IMG_SOC_EXT_SA_02     0
#define REGNUM_IMG_SOC_EXT_SA_02    0x0048
#define SIGNED_IMG_SOC_EXT_SA_02    0

#define MASK_IMG_SOC_BURST_02       0x07000000
#define SHIFT_IMG_SOC_BURST_02      24
#define REGNUM_IMG_SOC_BURST_02     0x0048
#define SIGNED_IMG_SOC_BURST_02     0

#define MASK_IMG_SOC_INCR_02        0x08000000
#define SHIFT_IMG_SOC_INCR_02       27
#define REGNUM_IMG_SOC_INCR_02      0x0048
#define SIGNED_IMG_SOC_INCR_02      0

#define MASK_IMG_SOC_ACC_DEL_02     0xE0000000
#define SHIFT_IMG_SOC_ACC_DEL_02    29
#define REGNUM_IMG_SOC_ACC_DEL_02   0x0048
#define SIGNED_IMG_SOC_ACC_DEL_02   0

/* Register DMAC_IRQ_STAT_2 */
#define IMG_SOC_DMAC_IRQ_STAT_2     0x004C
#define MASK_IMG_SOC_TRANSFER_FIN_02 0x00020000
#define SHIFT_IMG_SOC_TRANSFER_FIN_02 17
#define REGNUM_IMG_SOC_TRANSFER_FIN_02 0x004C
#define SIGNED_IMG_SOC_TRANSFER_FIN_02 0

#define MASK_IMG_SOC_LIST_INT_02    0x00100000
#define SHIFT_IMG_SOC_LIST_INT_02   20
#define REGNUM_IMG_SOC_LIST_INT_02  0x004C
#define SIGNED_IMG_SOC_LIST_INT_02  0
#define IMG_SOC_LIST_INT_02_ENABLE		0x00000001		/* The last linked-list element processed initiated an interrupt.  If LIST_IEN is set
 for the channel, an interrupt will be generated on the IRQ line until this bit is cleared, */
#define IMG_SOC_LIST_INT_02_DISABLE		0x00000000		/* last linked list element processed did not initiate an interrupt. */

#define MASK_IMG_SOC_LIST_FIN_02    0x00200000
#define SHIFT_IMG_SOC_LIST_FIN_02   21
#define REGNUM_IMG_SOC_LIST_FIN_02  0x004C
#define SIGNED_IMG_SOC_LIST_FIN_02  0

/* Register DMAC_2D_MODE_2 */
#define IMG_SOC_DMAC_2D_MODE_2      0x0050
#define MASK_IMG_SOC_ROW_LENGTH_02  0x000003FF
#define SHIFT_IMG_SOC_ROW_LENGTH_02 0
#define REGNUM_IMG_SOC_ROW_LENGTH_02 0x0050
#define SIGNED_IMG_SOC_ROW_LENGTH_02 0

#define MASK_IMG_SOC_LINE_ADDR_OFFSET_02 0x000FFC00
#define SHIFT_IMG_SOC_LINE_ADDR_OFFSET_02 10
#define REGNUM_IMG_SOC_LINE_ADDR_OFFSET_02 0x0050
#define SIGNED_IMG_SOC_LINE_ADDR_OFFSET_02 0

#define MASK_IMG_SOC_REP_COUNT_02   0x7FF00000
#define SHIFT_IMG_SOC_REP_COUNT_02  20
#define REGNUM_IMG_SOC_REP_COUNT_02 0x0050
#define SIGNED_IMG_SOC_REP_COUNT_02 0

/* Register DMAC_PERIPHERAL_ADDR_2 */
#define IMG_SOC_DMAC_PERIPHERAL_ADDR_2 0x0054
#define MASK_IMG_SOC_ADDR_02        0x007FFFFF
#define SHIFT_IMG_SOC_ADDR_02       0
#define REGNUM_IMG_SOC_ADDR_02      0x0054
#define SIGNED_IMG_SOC_ADDR_02      0

/* Register DMAC_PER_HOLD_2 */
#define IMG_SOC_DMAC_PER_HOLD_2     0x0058
#define MASK_IMG_SOC_PER_HOLD_02    0x0000007F
#define SHIFT_IMG_SOC_PER_HOLD_02   0
#define REGNUM_IMG_SOC_PER_HOLD_02  0x0058
#define SIGNED_IMG_SOC_PER_HOLD_02  0

/* Register DMAC_SETUP_3 */
#define IMG_SOC_DMAC_SETUP_3        0x0060
#define MASK_IMG_SOC_START_ADDRESS_03 0xFFFFFFFF
#define SHIFT_IMG_SOC_START_ADDRESS_03 0
#define REGNUM_IMG_SOC_START_ADDRESS_03 0x0060
#define SIGNED_IMG_SOC_START_ADDRESS_03 0

/* Register DMAC_COUNT_3 */
#define IMG_SOC_DMAC_COUNT_3        0x0064
#define MASK_IMG_SOC_CNT_03         0x0000FFFF
#define SHIFT_IMG_SOC_CNT_03        0
#define REGNUM_IMG_SOC_CNT_03       0x0064
#define SIGNED_IMG_SOC_CNT_03       0

#define MASK_IMG_SOC_EN_03          0x00010000
#define SHIFT_IMG_SOC_EN_03         16
#define REGNUM_IMG_SOC_EN_03        0x0064
#define SIGNED_IMG_SOC_EN_03        0

#define MASK_IMG_SOC_ENABLE_2D_MODE_03 0x00020000
#define SHIFT_IMG_SOC_ENABLE_2D_MODE_03 17
#define REGNUM_IMG_SOC_ENABLE_2D_MODE_03 0x0064
#define SIGNED_IMG_SOC_ENABLE_2D_MODE_03 0
#define IMG_SOC_ENABLE_2D_MODE_03_ENABLED		0x00000001
#define IMG_SOC_ENABLE_2D_MODE_03_DISABLED		0x00000000

#define MASK_IMG_SOC_LIST_EN_03     0x00040000
#define SHIFT_IMG_SOC_LIST_EN_03    18
#define REGNUM_IMG_SOC_LIST_EN_03   0x0064
#define SIGNED_IMG_SOC_LIST_EN_03   0

#define MASK_IMG_SOC_SRST_03        0x00080000
#define SHIFT_IMG_SOC_SRST_03       19
#define REGNUM_IMG_SOC_SRST_03      0x0064
#define SIGNED_IMG_SOC_SRST_03      0

#define MASK_IMG_SOC_DREQ_03        0x00100000
#define SHIFT_IMG_SOC_DREQ_03       20
#define REGNUM_IMG_SOC_DREQ_03      0x0064
#define SIGNED_IMG_SOC_DREQ_03      0

#define MASK_IMG_SOC_LIST_FIN_CTL_03 0x00400000
#define SHIFT_IMG_SOC_LIST_FIN_CTL_03 22
#define REGNUM_IMG_SOC_LIST_FIN_CTL_03 0x0064
#define SIGNED_IMG_SOC_LIST_FIN_CTL_03 0

#define MASK_IMG_SOC_PI_03          0x03000000
#define SHIFT_IMG_SOC_PI_03         24
#define REGNUM_IMG_SOC_PI_03        0x0064
#define SIGNED_IMG_SOC_PI_03        0
#define IMG_SOC_PI_03_1		0x00000002
#define IMG_SOC_PI_03_2		0x00000001
#define IMG_SOC_PI_03_4		0x00000000

#define MASK_IMG_SOC_DIR_03         0x04000000
#define SHIFT_IMG_SOC_DIR_03        26
#define REGNUM_IMG_SOC_DIR_03       0x0064
#define SIGNED_IMG_SOC_DIR_03       0

#define MASK_IMG_SOC_PW_03          0x18000000
#define SHIFT_IMG_SOC_PW_03         27
#define REGNUM_IMG_SOC_PW_03        0x0064
#define SIGNED_IMG_SOC_PW_03        0

#define MASK_IMG_SOC_TRANSFER_IEN_03 0x20000000
#define SHIFT_IMG_SOC_TRANSFER_IEN_03 29
#define REGNUM_IMG_SOC_TRANSFER_IEN_03 0x0064
#define SIGNED_IMG_SOC_TRANSFER_IEN_03 0

#define MASK_IMG_SOC_BSWAP_03       0x40000000
#define SHIFT_IMG_SOC_BSWAP_03      30
#define REGNUM_IMG_SOC_BSWAP_03     0x0064
#define SIGNED_IMG_SOC_BSWAP_03     0

#define MASK_IMG_SOC_LIST_IEN_03    0x80000000
#define SHIFT_IMG_SOC_LIST_IEN_03   31
#define REGNUM_IMG_SOC_LIST_IEN_03  0x0064
#define SIGNED_IMG_SOC_LIST_IEN_03  0

/* Register DMAC_PERIPH_3 */
#define IMG_SOC_DMAC_PERIPH_3       0x0068
#define MASK_IMG_SOC_EXT_SA_03      0x0000000F
#define SHIFT_IMG_SOC_EXT_SA_03     0
#define REGNUM_IMG_SOC_EXT_SA_03    0x0068
#define SIGNED_IMG_SOC_EXT_SA_03    0

#define MASK_IMG_SOC_BURST_03       0x07000000
#define SHIFT_IMG_SOC_BURST_03      24
#define REGNUM_IMG_SOC_BURST_03     0x0068
#define SIGNED_IMG_SOC_BURST_03     0

#define MASK_IMG_SOC_INCR_03        0x08000000
#define SHIFT_IMG_SOC_INCR_03       27
#define REGNUM_IMG_SOC_INCR_03      0x0068
#define SIGNED_IMG_SOC_INCR_03      0

#define MASK_IMG_SOC_ACC_DEL_03     0xE0000000
#define SHIFT_IMG_SOC_ACC_DEL_03    29
#define REGNUM_IMG_SOC_ACC_DEL_03   0x0068
#define SIGNED_IMG_SOC_ACC_DEL_03   0

/* Register DMAC_IRQ_STAT_3 */
#define IMG_SOC_DMAC_IRQ_STAT_3     0x006C
#define MASK_IMG_SOC_TRANSFER_FIN_03 0x00020000
#define SHIFT_IMG_SOC_TRANSFER_FIN_03 17
#define REGNUM_IMG_SOC_TRANSFER_FIN_03 0x006C
#define SIGNED_IMG_SOC_TRANSFER_FIN_03 0

#define MASK_IMG_SOC_LIST_INT_03    0x00100000
#define SHIFT_IMG_SOC_LIST_INT_03   20
#define REGNUM_IMG_SOC_LIST_INT_03  0x006C
#define SIGNED_IMG_SOC_LIST_INT_03  0
#define IMG_SOC_LIST_INT_03_ENABLE		0x00000001		/* The last linked-list element processed initiated an interrupt.  If LIST_IEN is set
 for the channel, an interrupt will be generated on the IRQ line until this bit is cleared, */
#define IMG_SOC_LIST_INT_03_DISABLE		0x00000000		/* last linked list element processed did not initiate an interrupt. */

#define MASK_IMG_SOC_LIST_FIN_03    0x00200000
#define SHIFT_IMG_SOC_LIST_FIN_03   21
#define REGNUM_IMG_SOC_LIST_FIN_03  0x006C
#define SIGNED_IMG_SOC_LIST_FIN_03  0

/* Register DMAC_2D_MODE_3 */
#define IMG_SOC_DMAC_2D_MODE_3      0x0070
#define MASK_IMG_SOC_ROW_LENGTH_03  0x000003FF
#define SHIFT_IMG_SOC_ROW_LENGTH_03 0
#define REGNUM_IMG_SOC_ROW_LENGTH_03 0x0070
#define SIGNED_IMG_SOC_ROW_LENGTH_03 0

#define MASK_IMG_SOC_LINE_ADDR_OFFSET_03 0x000FFC00
#define SHIFT_IMG_SOC_LINE_ADDR_OFFSET_03 10
#define REGNUM_IMG_SOC_LINE_ADDR_OFFSET_03 0x0070
#define SIGNED_IMG_SOC_LINE_ADDR_OFFSET_03 0

#define MASK_IMG_SOC_REP_COUNT_03   0x7FF00000
#define SHIFT_IMG_SOC_REP_COUNT_03  20
#define REGNUM_IMG_SOC_REP_COUNT_03 0x0070
#define SIGNED_IMG_SOC_REP_COUNT_03 0

/* Register DMAC_PERIPHERAL_ADDR_3 */
#define IMG_SOC_DMAC_PERIPHERAL_ADDR_3 0x0074
#define MASK_IMG_SOC_ADDR_03        0x007FFFFF
#define SHIFT_IMG_SOC_ADDR_03       0
#define REGNUM_IMG_SOC_ADDR_03      0x0074
#define SIGNED_IMG_SOC_ADDR_03      0

/* Register DMAC_PER_HOLD_3 */
#define IMG_SOC_DMAC_PER_HOLD_3     0x0078
#define MASK_IMG_SOC_PER_HOLD_03    0x0000007F
#define SHIFT_IMG_SOC_PER_HOLD_03   0
#define REGNUM_IMG_SOC_PER_HOLD_03  0x0078
#define SIGNED_IMG_SOC_PER_HOLD_03  0

/* Register DMAC_SOFT_RESET */
#define IMG_SOC_DMAC_SOFT_RESET     0x0080

/* Table DMAC */

/* Register DMAC_SETUP */
#define IMG_SOC_DMAC_SETUP(X)       (0x0000 + (32 * (X)))
#define MASK_IMG_SOC_START_ADDRESS  0xFFFFFFFF
#define SHIFT_IMG_SOC_START_ADDRESS 0
#define REGNUM_IMG_SOC_START_ADDRESS 0x0000
#define SIGNED_IMG_SOC_START_ADDRESS 0

/* Register DMAC_COUNT */
#define IMG_SOC_DMAC_COUNT(X)       (0x0004 + (32 * (X)))
#define MASK_IMG_SOC_CNT            0x0000FFFF
#define SHIFT_IMG_SOC_CNT           0
#define REGNUM_IMG_SOC_CNT          0x0004
#define SIGNED_IMG_SOC_CNT          0

#define MASK_IMG_SOC_EN             0x00010000
#define SHIFT_IMG_SOC_EN            16
#define REGNUM_IMG_SOC_EN           0x0004
#define SIGNED_IMG_SOC_EN           0

#define MASK_IMG_SOC_ENABLE_2D_MODE 0x00020000
#define SHIFT_IMG_SOC_ENABLE_2D_MODE 17
#define REGNUM_IMG_SOC_ENABLE_2D_MODE 0x0004
#define SIGNED_IMG_SOC_ENABLE_2D_MODE 0
#define IMG_SOC_ENABLE_2D_MODE_ENABLED		0x00000001
#define IMG_SOC_ENABLE_2D_MODE_DISABLED		0x00000000

#define MASK_IMG_SOC_LIST_EN        0x00040000
#define SHIFT_IMG_SOC_LIST_EN       18
#define REGNUM_IMG_SOC_LIST_EN      0x0004
#define SIGNED_IMG_SOC_LIST_EN      0

#define MASK_IMG_SOC_SRST           0x00080000
#define SHIFT_IMG_SOC_SRST          19
#define REGNUM_IMG_SOC_SRST         0x0004
#define SIGNED_IMG_SOC_SRST         0

#define MASK_IMG_SOC_DREQ           0x00100000
#define SHIFT_IMG_SOC_DREQ          20
#define REGNUM_IMG_SOC_DREQ         0x0004
#define SIGNED_IMG_SOC_DREQ         0

#define MASK_IMG_SOC_LIST_FIN_CTL   0x00400000
#define SHIFT_IMG_SOC_LIST_FIN_CTL  22
#define REGNUM_IMG_SOC_LIST_FIN_CTL 0x0004
#define SIGNED_IMG_SOC_LIST_FIN_CTL 0

#define MASK_IMG_SOC_PI             0x03000000
#define SHIFT_IMG_SOC_PI            24
#define REGNUM_IMG_SOC_PI           0x0004
#define SIGNED_IMG_SOC_PI           0
#define IMG_SOC_PI_1		0x00000002
#define IMG_SOC_PI_2		0x00000001
#define IMG_SOC_PI_4		0x00000000

#define MASK_IMG_SOC_DIR            0x04000000
#define SHIFT_IMG_SOC_DIR           26
#define REGNUM_IMG_SOC_DIR          0x0004
#define SIGNED_IMG_SOC_DIR          0

#define MASK_IMG_SOC_PW             0x18000000
#define SHIFT_IMG_SOC_PW            27
#define REGNUM_IMG_SOC_PW           0x0004
#define SIGNED_IMG_SOC_PW           0

#define MASK_IMG_SOC_TRANSFER_IEN   0x20000000
#define SHIFT_IMG_SOC_TRANSFER_IEN  29
#define REGNUM_IMG_SOC_TRANSFER_IEN 0x0004
#define SIGNED_IMG_SOC_TRANSFER_IEN 0

#define MASK_IMG_SOC_BSWAP          0x40000000
#define SHIFT_IMG_SOC_BSWAP         30
#define REGNUM_IMG_SOC_BSWAP        0x0004
#define SIGNED_IMG_SOC_BSWAP        0

#define MASK_IMG_SOC_LIST_IEN       0x80000000
#define SHIFT_IMG_SOC_LIST_IEN      31
#define REGNUM_IMG_SOC_LIST_IEN     0x0004
#define SIGNED_IMG_SOC_LIST_IEN     0

/* Register DMAC_PERIPH */
#define IMG_SOC_DMAC_PERIPH(X)      (0x0008 + (32 * (X)))
#define MASK_IMG_SOC_EXT_SA         0x0000000F
#define SHIFT_IMG_SOC_EXT_SA        0
#define REGNUM_IMG_SOC_EXT_SA       0x0008
#define SIGNED_IMG_SOC_EXT_SA       0

#define MASK_IMG_SOC_BURST          0x07000000
#define SHIFT_IMG_SOC_BURST         24
#define REGNUM_IMG_SOC_BURST        0x0008
#define SIGNED_IMG_SOC_BURST        0

#define MASK_IMG_SOC_INCR           0x08000000
#define SHIFT_IMG_SOC_INCR          27
#define REGNUM_IMG_SOC_INCR         0x0008
#define SIGNED_IMG_SOC_INCR         0

#define MASK_IMG_SOC_ACC_DEL        0xE0000000
#define SHIFT_IMG_SOC_ACC_DEL       29
#define REGNUM_IMG_SOC_ACC_DEL      0x0008
#define SIGNED_IMG_SOC_ACC_DEL      0

/* Register DMAC_IRQ_STAT */
#define IMG_SOC_DMAC_IRQ_STAT(X)    (0x000C + (32 * (X)))
#define MASK_IMG_SOC_TRANSFER_FIN   0x00020000
#define SHIFT_IMG_SOC_TRANSFER_FIN  17
#define REGNUM_IMG_SOC_TRANSFER_FIN 0x000C
#define SIGNED_IMG_SOC_TRANSFER_FIN 0

#define MASK_IMG_SOC_LIST_INT       0x00100000
#define SHIFT_IMG_SOC_LIST_INT      20
#define REGNUM_IMG_SOC_LIST_INT     0x000C
#define SIGNED_IMG_SOC_LIST_INT     0
#define IMG_SOC_LIST_INT_ENABLE		0x00000001		/* The last linked-list element processed initiated an interrupt.  If LIST_IEN is set for
 the channel, an interrupt will be generated on the IRQ line until this bit is cleared, */
#define IMG_SOC_LIST_INT_DISABLE		0x00000000		/* last linked list element processed did not initiate an interrupt. */

#define MASK_IMG_SOC_LIST_FIN       0x00200000
#define SHIFT_IMG_SOC_LIST_FIN      21
#define REGNUM_IMG_SOC_LIST_FIN     0x000C
#define SIGNED_IMG_SOC_LIST_FIN     0

/* Register DMAC_2D_MODE */
#define IMG_SOC_DMAC_2D_MODE(X)     (0x0010 + (32 * (X)))
#define MASK_IMG_SOC_ROW_LENGTH     0x000003FF
#define SHIFT_IMG_SOC_ROW_LENGTH    0
#define REGNUM_IMG_SOC_ROW_LENGTH   0x0010
#define SIGNED_IMG_SOC_ROW_LENGTH   0

#define MASK_IMG_SOC_LINE_ADDR_OFFSET 0x000FFC00
#define SHIFT_IMG_SOC_LINE_ADDR_OFFSET 10
#define REGNUM_IMG_SOC_LINE_ADDR_OFFSET 0x0010
#define SIGNED_IMG_SOC_LINE_ADDR_OFFSET 0

#define MASK_IMG_SOC_REP_COUNT      0x7FF00000
#define SHIFT_IMG_SOC_REP_COUNT     20
#define REGNUM_IMG_SOC_REP_COUNT    0x0010
#define SIGNED_IMG_SOC_REP_COUNT    0

/* Register DMAC_PERIPHERAL_ADDR */
#define IMG_SOC_DMAC_PERIPHERAL_ADDR(X) (0x0014 + (32 * (X)))
#define MASK_IMG_SOC_ADDR           0x007FFFFF
#define SHIFT_IMG_SOC_ADDR          0
#define REGNUM_IMG_SOC_ADDR         0x0014
#define SIGNED_IMG_SOC_ADDR         0

/* Register DMAC_PER_HOLD */
#define IMG_SOC_DMAC_PER_HOLD(X)    (0x0018 + (32 * (X)))
#define MASK_IMG_SOC_PER_HOLD       0x0000007F
#define SHIFT_IMG_SOC_PER_HOLD      0
#define REGNUM_IMG_SOC_PER_HOLD     0x0018
#define SIGNED_IMG_SOC_PER_HOLD     0

/* Number of entries in table DMAC */

#define IMG_SOC_DMAC_SIZE_UINT32    31
#define IMG_SOC_DMAC_NUM_ENTRIES    4

/*
	Byte range covering the group DMAC file
*/

#define IMG_SOC_DMAC_REGISTERS_START		0x00000000
#define IMG_SOC_DMAC_REGISTERS_END  		0x00000083

/*
	Byte range covering the whole register file
*/

#define IMG_SOC_REGISTERS_START		0x00000000
#define IMG_SOC_REGISTERS_END  		0x00000083
#define IMG_SOC_REG_DEFAULT_TABLE struct {\
			IMG_UINT16 uRegOffset;\
			IMG_UINT32 uRegDefault;\
			IMG_UINT32 uRegMask;\
			bool bReadonly;\
			const char* pszName;\
		} IMG_SOC_Defaults[] = {\
	{0x0000, 0x00000000, 0xFFFFFFFF, 0, "DMAC_SETUP_0" } ,\
	{0x0004, 0x00000000, 0xFF5FFFFF, 0, "DMAC_COUNT_0" } ,\
	{0x0008, 0x00000000, 0xEF00000F, 0, "DMAC_PERIPH_0" } ,\
	{0x000C, 0x00000000, 0x00320000, 0, "DMAC_IRQ_STAT_0" } ,\
	{0x0010, 0x00000000, 0x7FFFFFFF, 0, "DMAC_2D_MODE_0" } ,\
	{0x0014, 0x00000000, 0x007FFFFF, 0, "DMAC_PERIPHERAL_ADDR_0" } ,\
	{0x0018, 0x00000007, 0x0000007F, 0, "DMAC_PER_HOLD_0" } ,\
	{0x0020, 0x00000000, 0xFFFFFFFF, 0, "DMAC_SETUP_1" } ,\
	{0x0024, 0x00000000, 0xFF5FFFFF, 0, "DMAC_COUNT_1" } ,\
	{0x0028, 0x00000000, 0xEF00000F, 0, "DMAC_PERIPH_1" } ,\
	{0x002C, 0x00000000, 0x00320000, 0, "DMAC_IRQ_STAT_1" } ,\
	{0x0030, 0x00000000, 0x7FFFFFFF, 0, "DMAC_2D_MODE_1" } ,\
	{0x0034, 0x00000000, 0x007FFFFF, 0, "DMAC_PERIPHERAL_ADDR_1" } ,\
	{0x0038, 0x00000007, 0x0000007F, 0, "DMAC_PER_HOLD_1" } ,\
	{0x0040, 0x00000000, 0xFFFFFFFF, 0, "DMAC_SETUP_2" } ,\
	{0x0044, 0x00000000, 0xFF5FFFFF, 0, "DMAC_COUNT_2" } ,\
	{0x0048, 0x00000000, 0xEF00000F, 0, "DMAC_PERIPH_2" } ,\
	{0x004C, 0x00000000, 0x00320000, 0, "DMAC_IRQ_STAT_2" } ,\
	{0x0050, 0x00000000, 0x7FFFFFFF, 0, "DMAC_2D_MODE_2" } ,\
	{0x0054, 0x00000000, 0x007FFFFF, 0, "DMAC_PERIPHERAL_ADDR_2" } ,\
	{0x0058, 0x00000007, 0x0000007F, 0, "DMAC_PER_HOLD_2" } ,\
	{0x0060, 0x00000000, 0xFFFFFFFF, 0, "DMAC_SETUP_3" } ,\
	{0x0064, 0x00000000, 0xFF5FFFFF, 0, "DMAC_COUNT_3" } ,\
	{0x0068, 0x00000000, 0xEF00000F, 0, "DMAC_PERIPH_3" } ,\
	{0x006C, 0x00000000, 0x00320000, 0, "DMAC_IRQ_STAT_3" } ,\
	{0x0070, 0x00000000, 0x7FFFFFFF, 0, "DMAC_2D_MODE_3" } ,\
	{0x0074, 0x00000000, 0x007FFFFF, 0, "DMAC_PERIPHERAL_ADDR_3" } ,\
	{0x0078, 0x00000007, 0x0000007F, 0, "DMAC_PER_HOLD_3" } ,\
	{0x0080, 0x00000000, 0x00000000, 0, "DMAC_SOFT_RESET" } ,\
{ 0 }}

#define IMG_SOC_REGS_INIT(uBase) \
	{ \
		int n;\
		IMG_SOC_REG_DEFAULT_TABLE;\
		for (n = 0; n < sizeof(IMG_SOC_Defaults)/ sizeof(IMG_SOC_Defaults[0] ) -1; n++)\
		{\
			RegWriteNoTrap(IMG_SOC_Defaults[n].uRegOffset + uBase, IMG_SOC_Defaults[n].uRegDefault); \
		}\
	}
#endif
