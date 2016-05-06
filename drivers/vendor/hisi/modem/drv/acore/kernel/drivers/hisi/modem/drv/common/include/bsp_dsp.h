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

#ifndef __BSP_DSP_H__
#define __BSP_DSP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <bsp_shared_ddr.h>
#if defined(__OS_VXWORKS__) || defined(__OS_RTOSCK__)
#include <bsp_dpm.h>
#endif



#define DSP_IMAGE_NAME "DSP"
#define DSP_IMAGE_STATE_OK (0x5312ABCD)

#define SAVE_TCM_BEGIN (0x12345678)
#define SAVE_TCM_END  (0x90abcdef)


#define HIFI_MEM_BEGIN_CHECK32_DATA (0x55AA55AA)
#define HIFI_MEM_END_CHECK32_DATA   (0xAA55AA55)

#define HIFI_SEC_MAX_NUM            (32)
#define HIFI_DYNAMIC_SEC_MAX_NUM    (HIFI_SEC_MAX_NUM)

#define HIFI_SHARE_MEMORY_ADDR      (SHM_BASE_ADDR + SHM_OFFSET_HIFI)
#define HIFI_SHARE_MEMORY_SIZE      (SHM_SIZE_HIFI)


/*****************************************************************************
 实 体 名  : DRV_HIFI_IMAGE_SEC_TYPE_ENUM
 功能描述  : 镜像段类型
*****************************************************************************/
enum DRV_HIFI_IMAGE_SEC_TYPE_ENUM {
    DRV_HIFI_IMAGE_SEC_TYPE_CODE = 0,        /* 代码 */
    DRV_HIFI_IMAGE_SEC_TYPE_DATA,            /* 数据 */
    DRV_HIFI_IMAGE_SEC_TYPE_BUTT,
};

/*****************************************************************************
 实 体 名  : DRV_HIFI_IMAGE_SEC_LOAD_ENUM
 功能描述  : 镜像段加载属性
*****************************************************************************/
enum DRV_HIFI_IMAGE_SEC_LOAD_ENUM {
    DRV_HIFI_IMAGE_SEC_LOAD_STATIC = 0,      /* 单次加载, 即解复位前加载 */
    DRV_HIFI_IMAGE_SEC_LOAD_DYNAMIC,         /* 多次加载, 由其他机制加载 */
    DRV_HIFI_IMAGE_SEC_UNLOAD,               /* 不需要底软加载 */
    DRV_HIFI_IMAGE_SEC_LOAD_BUTT,
};

/*****************************************************************************
 实 体 名  : DRV_HIFI_IMAGE_SEC_STRU
 功能描述  : 镜像段定义
*****************************************************************************/
struct drv_hifi_image_sec
{
    unsigned short                      sn;              /* 编号 */
    unsigned char                       type;            /* 类型 */
    unsigned char                       load_attib;      /* 加载属性 */
    unsigned long                       src_offset;      /* 在文件中的偏移, bytes */
    unsigned long                       des_addr;        /* 加载目的地址, bytes */
    unsigned long                       size;            /* 段长度, bytes */
};

/*****************************************************************************
 实 体 名  : drv_hifi_image_head
 功能描述  : 镜像文件头定义
*****************************************************************************/
struct drv_hifi_image_head
{
    char                                time_stamp[24]; /* 镜像编译时间 */
    unsigned long                       image_size;     /* 镜像文件大小, bytes */
    unsigned int                        sections_num;   /* 文件包含段数目 */
    struct drv_hifi_image_sec           sections[HIFI_SEC_MAX_NUM];    /* 段信息, 共sections_num个 */
};

/*****************************************************************************
 实 体 名  : drv_hifi_sec_addr_info
 功能描述  : Hifi动态加载段地址结构
*****************************************************************************/
struct drv_hifi_sec_addr
{
    unsigned int  sec_source_addr;  /*段的源地址*/
    unsigned int  sec_length;       /*段的长度*/
    unsigned int  sec_dest_addr;    /*段的目的地址*/
};

/*****************************************************************************
 实 体 名  : drv_hifi_sec_load_info
 功能描述  : Hifi动态加载段结构
*****************************************************************************/
#define HIFI_SEC_DATA_LENGTH (SHM_SIZE_HIFI \
                               - HIFI_DYNAMIC_SEC_MAX_NUM*sizeof(struct drv_hifi_sec_addr) \
                               - 3*sizeof(unsigned int))

struct drv_hifi_sec_load_info
{
    unsigned int             sec_magic;         /*段信息开始的保护字*/
    unsigned int             sec_num;           /*段的个数*/
    struct drv_hifi_sec_addr sec_addr_info[HIFI_DYNAMIC_SEC_MAX_NUM]; /*段的地址信息*/
    char                     sec_data[HIFI_SEC_DATA_LENGTH];          /*段信息*/
};

struct dsp_pm_om_qos_log {
    unsigned int load_start;
    unsigned int load_end;
    unsigned int msp_store;
    unsigned int dpm_store;
    unsigned int dsp_store;
    unsigned int dsp_store_end;
    unsigned int poweroff;
    unsigned int poweron;
    unsigned int dpm_wait_store_ok;
    unsigned int dpm_restore;
    unsigned int dsp_restore;
    unsigned int msp_restore;
    unsigned int msp_restore_ok;
};

struct dsp_dump_proc_flag
{
    unsigned int dsp_dump_flag;         /* 异常流程中，记录dsp保存tcm的过程标志 */
};

#ifndef CONFIG_DSP
#ifdef __KERNEL__
static inline int his_load_tldsp_image(void)
{
    return 0;
}
#endif

static inline int bsp_bbe_load_muti(void)
{
    return 0;
}

static inline int bsp_bbe_run(void)
{
    return 0;
}

static inline int bsp_bbe_stop(void)
{
    return 0;
}

static inline int bsp_bbe_power_on(void)
{
    return 0;
}

static inline int bsp_bbe_power_off(void)
{
    return 0;
}

static inline int bsp_bbe_power_status(void)
{
    return 0;
}

static inline int bsp_bbe_power_up(void)
{
    return 0;
}

static inline int bsp_bbe_power_down(void)
{
    return 0;
}


static inline int bsp_bbe_unreset(void)
{
    return 0;
}

static inline int bsp_bbe_reset(void)
{
    return 0;
}

static inline int bsp_bbe_clock_enable(void)
{
    return 0;
}

static inline int bsp_bbe_clock_disable(void)
{
    return 0;
}

static inline int bsp_bbe_is_power_on(void)
{
    return 0;
}

static inline int bsp_bbe_is_clock_enable(void)
{
    return 0;
}

static inline void bsp_dsp_init(void)
{
    return;
}

static inline int bsp_dsp_dfs_pll_status(void)
{
    return 0;
}

static inline int bsp_dsp_dfs_pll_enable(void)
{
    return 0;
}

static inline int bsp_dsp_dfs_pll_disable(void)
{
    return 0;
}

static inline int bsp_msp_bbe_store(void)
{
    return 0;
}
static inline int bsp_msp_bbe_restore(void)
{
    return 0;
}

static inline int bsp_msp_wait_edma_ok(void)
{
    return 0;
}

static inline int bsp_dsp_pll_status(void)
{
    return 0;
}

static inline int bsp_dsp_store_tcm(void)
{
    return 0;
}
#else
#ifdef __KERNEL__
int his_load_tldsp_image(void);
#endif

int bsp_bbe_load_muti(void);

int bsp_bbe_is_muti_loaded(void);

int bsp_bbe_run(void);

int bsp_bbe_is_run(void);

int bsp_bbe_stop(void);

int bsp_bbe_store(void);

int bsp_bbe_wait_store_ok(void);

int bsp_bbe_restore(void);

int bsp_bbe_wait_restore_ok(void);

int bsp_bbe_clock_enable(void);

int bsp_bbe_clock_disable(void);

int bsp_bbe_unreset(void);

int bsp_bbe_reset(void);

int bsp_bbe_is_unreset(void);

int bsp_bbe_power_on(void);

int bsp_bbe_power_off(void);

int bsp_bbe_is_clock_enable(void);

int bsp_bbe_is_power_on(void);

int bsp_bbe_power_status(void);

int bsp_bbe_power_up(void);

int bsp_bbe_power_down(void);

int bsp_bbe_waiti_enable(void);

void bsp_bbe_refclk_enable(void);

void bsp_bbe_refclk_disable(void);

void bsp_bbe_peri_refclk_enable(void);

void bsp_bbe_peri_refclk_disable(void);

int bsp_bbe_is_tcm_accessible(void);

int bsp_dsp_clock_enable(void);

int bsp_dsp_clock_disable(void);

int bsp_dsp_unreset(void);

int bsp_dsp_reset(void);

int bsp_dsp_pll_status(void);

int bsp_dsp_pll_enable(void);

int bsp_dsp_pll_disable(void);

void bsp_bbe_chose_pll(u32 flag);

int bsp_dsp_dfs_pll_status(void);

int bsp_dsp_dfs_pll_enable(void);

int bsp_dsp_dfs_pll_disable(void);

int bsp_msp_bbe_store(void);

int bsp_msp_bbe_is_stored(void);

int bsp_msp_bbe_restore(void);

int bsp_msp_bbe_is_restored(void);

int bsp_msp_wait_edma_ok(void);

int bsp_msp_is_edma_ok(void);

int bsp_bbe_tcm_accessible(void);

#if defined(__OS_VXWORKS__) || defined(__OS_RTOSCK__)
int bsp_bbe_dpm_prepare(struct dpm_device *dev);

int bsp_bbe_dpm_suspend_late(struct dpm_device *dev);

int bsp_bbe_dpm_resume_early(struct dpm_device *dev);

int bsp_bbe_dpm_complete(struct dpm_device *dev);
#endif

int bsp_dsp_is_hifi_exist(void);


int bsp_dsp_info(void);
void bsp_dsp_init(void);


#endif

int bsp_hifi_run(void);

int bsp_hifi_stop(void);

int bsp_hifi_restore(void);

int bsp_load_modem(void);
int bsp_load_modem_dsp(void);

/* the interface below is just for myself */

extern void drv_hifi_fill_mb_info(unsigned int addr);
int bsp_dsp_store_tcm(void);
void bsp_hifi_init(void);



#ifdef __cplusplus
}
#endif

#endif

