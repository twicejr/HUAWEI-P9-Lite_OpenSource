/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __BSP_DFS_TRAINING_H__
#define __BSP_DFS_TRAINING_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */
#include <product_config.h>
#include <soc_memmap_comm.h>

#ifndef __ASSEMBLY__
#define DFS_CHIP_FLOW_STAMP_NUM     (10)
typedef enum tagPLL_DIV_CTRL {
    DDR_FREQ_111 = 0,
    DDR_FREQ_133,
    DDR_FREQ_166,
    DDR_FREQ_200,
    DDR_FREQ_266,
    DDR_FREQ_333,
    DDR_FREQ_400,
    DDR_FREQ_450,
    DDR_FREQ_533,

    DDR_FREQ_MAX
}PLL_DIV_CTRL;

struct dfs_training
{
    unsigned int ddr_freq;

    unsigned int ddr_reg_ACADDRBDL0;
    unsigned int ddr_reg_ACADDRBDL1;
    unsigned int ddr_reg_ACADDRBDL2;
    unsigned int ddr_reg_ACADDRBDL3;
    unsigned int ddr_reg_ACADDRBDL4;
    unsigned int ddr_reg_ADDRPHBOUND;
    unsigned int ddr_reg_DXNWDQNBDL0[4];
    unsigned int ddr_reg_DXNWDQNBDL1[4];
    unsigned int ddr_reg_DXNWDQNBDL2[4];
    unsigned int ddr_reg_DXNRDQNBDL0[2][4];
    unsigned int ddr_reg_DXNRDQNBDL1[2][4];
    unsigned int ddr_reg_DXNOEBDL[4];
    unsigned int ddr_reg_DXNRDQSDLY[4];
    unsigned int ddr_reg_DXNWDQSDLY[4];
    unsigned int ddr_reg_DXNWDQDLY[4];
    unsigned int ddr_reg_DXNWLSL[4];
    unsigned int ddr_reg_DXNGDS[4];
    unsigned int ddr_reg_DXNRDQSGDLY[2][4];
};

struct ddrc_timing
{
    unsigned int timing0;
    unsigned int timing1;
    unsigned int timing2;
    unsigned int timing3;
    unsigned int timing4;
    unsigned int timing5;
    unsigned int timing6;
    unsigned int timing7;
    unsigned int dramtimer0;
    unsigned int dramtimer1;
    unsigned int dramtimer2;
    unsigned int dramtimer3;
    unsigned int dramtimer4;
    unsigned int dramtimer5;
    unsigned int misc;
    unsigned int modereg01;
    unsigned int modereg23;
    unsigned int dmsel;
    unsigned int ioctrl3;
};
typedef struct tcm_dfs_training
{
    struct dfs_training TRAINING[DDR_FREQ_MAX];
    struct ddrc_timing TIMING[DDR_FREQ_MAX];
    unsigned int dfs_chip_flow_stamp[DFS_CHIP_FLOW_STAMP_NUM];
}TCM_DFS_TRAINING;
#endif

#define DFS_DDR_TRAINING_DATA_ADDR  (RTX_KERNEL_ENTRY + DFS_DDR_TRANING_DATA_OFFSET)

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif    /*  __BSP_DFS_TRAINING_H__ */
