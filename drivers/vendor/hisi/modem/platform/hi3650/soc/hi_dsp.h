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

#ifndef __DSP_H__
#define __DSP_H__

#include <product_config.h>
#include <ptable_com.h>
#include <bsp_memmap.h>

#ifdef __cplusplus
extern "C" {
#endif


#define CONFIG_G_POWER_OPTIMIZE

#define BBE_TCM_ADDR (HI_BBE16DMEM_BASE_ADDR)
#define BBE_TCM_SIZE (0x00100000) /* 1 MB */

/* MUTI */
/*--------------*-- 256KB
 *    TDS-I     *
 *--------------*-- 256KB
 *    TDS-D     *
 *--------------*-- 256KB
 *    LTE-I     *
 *--------------*-- 256KB
 *    LTE-D     *
 *--------------*-- 260KB
 *    PUB-I     *
 *--------------*-- 252KB
 *    PUB-D     *
 *--------------*-- BBE_TCM_ADDR
 */
#define LPHY_BBE16_PUB_DTCM_LOAD_ADDR (LPHY_PUB_DTCM_BASE)
#define LPHY_BBE16_PUB_DTCM_LOAD_SIZE (LPHY_PUB_DTCM_SIZE)
#define LPHY_BBE16_MOD_DTCM_LOAD_ADDR (LPHY_PRV_DTCM_BASE)
#define LPHY_BBE16_MOD_DTCM_LOAD_SIZE (LPHY_PRV_DTCM_SIZE)

#define LPHY_BBE16_PUB_ITCM_LOAD_ADDR (LPHY_PUB_ITCM_BASE)
#define LPHY_BBE16_PUB_ITCM_LOAD_SIZE (LPHY_PUB_ITCM_SIZE)
#define LPHY_BBE16_MOD_ITCM_LOAD_ADDR (LPHY_PRV_ITCM_BASE)
#define LPHY_BBE16_MOD_ITCM_LOAD_SIZE (LPHY_PRV_ITCM_SIZE)

#define BBE_DDR_PUB_DTCM_ADDR (DDR_TLPHY_IMAGE_ADDR)
#define BBE_DDR_PUB_ITCM_ADDR (BBE_DDR_PUB_DTCM_ADDR + LPHY_BBE16_PUB_DTCM_LOAD_SIZE)

#define LPHY_BBE16_MUTI_IMAGE_OFFSET    (0)
#define LPHY_BBE16_MUTI_IMAGE_SIZE (LPHY_TOTAL_IMG_SIZE)

#define TPHY_BBE16_CFG_DATA_OFFSET  (LPHY_BBE16_MUTI_IMAGE_OFFSET + LPHY_BBE16_MUTI_IMAGE_SIZE)
#define TPHY_BBE16_CFG_DATA_SIZE    (0x00040000)    /* 256KB */

/* HiFi2 */
#define HIFI_TCM_ADDR (0xFFFFFFFF)
#define HIFI_TCM_SIZE (0xFFFFFFFF)


#ifdef __cplusplus
}
#endif

#endif
