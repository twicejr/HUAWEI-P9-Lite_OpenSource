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

#ifndef _BSP_PMU_H_
#define _BSP_PMU_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "product_config.h"
#include "osl_types.h"

#if defined(__OS_RTOSCK__) || defined(__OS_VXWORKS__)
#include "mdrv_pmu.h"
#endif

#ifdef __FASTBOOT__
#include <boot/boot.h>
#include "types.h"
#endif

#include <hi_pmu.h>

/*PMU申请的总大小是3*1024*/
#define SHM_PMU_OCP_INFO_SIZE 0x10
#define SHM_PMU_NPREG_SIZE 0x10
#define SHM_PMU_OCP_INFO_ADDR ((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_PMU)
#define SHM_MEM_PMU_NPREG_ADDR (SHM_PMU_OCP_INFO_ADDR + SHM_PMU_OCP_INFO_SIZE)

/*pmu状态宏定义，给om调用*/
#define PMU_STATE_OK    0
#define PMU_STATE_UNDER_VOL (1 << 0)
#define PMU_STATE_OVER_VOL  (1 << 1)
#define PMU_STATE_OVER_CUR  (1 << 2)
#define PMU_STATE_OVER_TEMP (1 << 3)

#ifdef __KERNEL__

/*PMU 32K CLK 枚举类型 */
typedef enum  _pmu_clk_e
{
    PMU_32K_CLK_A = 0,   /*SOC睡眠时钟，其他模块不能使用*/
    PMU_32K_CLK_B,       /**/
#if defined(CONFIG_PMIC_HI6551)
    PMU_32K_CLK_C,       /*只有hi6551中有该路时钟*/
#endif
    PMU_32K_CLK_MAX
}pmu_clk_e;

/*给使用pmu中断的模块调用*/
typedef void (*pmufuncptr)(void *);

/* ioshare */
typedef enum _pmic_ioshare_e
{
    GPIO_FUNC0 = 1,
    GPIO_FUNC1,
    GPIO_FUNC2,
    DR1_FUNC,
    DR2_FUNC,
    DR3_FUNC = 6,
    
    SIM0_HPD,
    SIM1_HPD,
    AUXDAC1_SSI,
    HKADC10_FUNC,
    HKADC11_FUNC0 = 11,
    HKADC11_FUNC1,
    PMIC_IOSHARE_E_MAX,
}pmic_ioshare_e;

#endif

#ifdef __KERNEL__
/*函数声明*/
/*****************************************************************************
 函 数 名  : bsp_pmu_get_boot_state
 功能描述  :系统启动时检查pmu寄存器状态，
                确认是否是由pmu引起的重启
 输入参数  : void
 输出参数  : reset.log
 返 回 值  : pmu问题或ok
 调用函数  :
 被调函数  :系统可维可测
*****************************************************************************/
int bsp_pmu_get_boot_state(void);

/*****************************************************************************
 函 数 名  : bsp_pmu_32k_clk_enable
 功能描述  : 开启pmu中32k时钟
 输入参数  : clk_id:32k时钟枚举值
 输出参数  : 无
 返 回 值  : 开启成功或失败
 调用函数  :
 被调函数  :
*****************************************************************************/
int bsp_pmu_32k_clk_enable(pmu_clk_e clk_id);
/*****************************************************************************
 函 数 名  : bsp_pmu_32k_clk_disable
 功能描述  : 关闭pmu中32k时钟
 输入参数  : clk_id:32k时钟枚举值
 输出参数  : 无
 返 回 值  : 关闭成功或失败
 调用函数  :
 被调函数  :
*****************************************************************************/
int bsp_pmu_32k_clk_disable(pmu_clk_e clk_id);
/*****************************************************************************
 函 数 名  : bsp_pmu_32k_clk_is_enabled
 功能描述  : 查询pmu中32k时钟是否开启
 输入参数  : clk_id:32k时钟枚举值
 输出参数  : 无
 返 回 值  : 开启或关闭
 调用函数  :
 被调函数  :
*****************************************************************************/
int bsp_pmu_32k_clk_is_enabled(pmu_clk_e clk_id);
/*****************************************************************************
 函 数 名  : bsp_pmu_xo_clk_enable
 功能描述  : 开启pmu中xo时钟
 输入参数  : 
 输出参数  : 无
 返 回 值  : 开启成功或失败
 调用函数  :
 被调函数  :
*****************************************************************************/
int bsp_pmu_xo_clk_enable(int clk_id);
/*****************************************************************************
 函 数 名  : bsp_pmu_xo_clk_disable
 功能描述  : 关闭pmu中xo时钟
 输入参数  : 
 输出参数  : 无
 返 回 值  : 关闭成功或失败
 调用函数  :
 被调函数  :
*****************************************************************************/
int bsp_pmu_xo_clk_disable(int clk_id);
/*****************************************************************************
 函 数 名  : bsp_pmu_xo_clk_is_enabled
 功能描述  : 查询pmu中xo时钟是否开启
 输入参数  :
 输出参数  : 无
 返 回 值  : 开启或关闭
 调用函数  :
 被调函数  :
*****************************************************************************/
int bsp_pmu_xo_clk_is_enabled(int clk_id);

/*****************************************************************************
 函 数 名  : bsp_pmu_version_get
 功能描述  : 获取usb是否插拔状态
 输入参数  : void
 输出参数  : 无
 返 回 值  : usb插入或拔出:1:插入;0:拔出
 调用函数  :
 被调函数  : 开关机模块
*****************************************************************************/
bool bsp_pmu_usb_state_get(void);
/*****************************************************************************
 函 数 名  : bsp_pmu_irq_callback_register
 功能描述  : 注册中断处理回调函数
 输入参数  : irq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  : 包含在pmu内部的中断模块
*****************************************************************************/
void bsp_pmu_irq_mask(unsigned int irq);
/*****************************************************************************
 函 数 名  : bsp_pmu_irq_callback_register
 功能描述  : 注册中断处理回调函数
 输入参数  : irq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  : 包含在pmu内部的中断模块
*****************************************************************************/
void bsp_pmu_irq_unmask(unsigned int irq);
/*****************************************************************************
 函 数 名  : bsp_pmu_irq_callback_register
 功能描述  : 注册中断处理回调函数
 输入参数  : irq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  : 包含在pmu内部的中断模块
*****************************************************************************/
int bsp_pmu_irq_is_masked(unsigned int irq);
/*****************************************************************************
 函 数 名  : bsp_pmu_key_state_get
 功能描述  : 获取按键是否按下状态
 输入参数  : void
 输出参数  : 无
 返 回 值  : 按键是否按下:1:按下；0:未按下
 调用函数  :
 被调函数  : 开关机模块
*****************************************************************************/
bool bsp_pmu_key_state_get(void);
/*****************************************************************************
 函 数 名  : bsp_pmu_irq_callback_register
 功能描述  : 注册中断处理回调函数
 输入参数  : irq
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  : 包含在pmu内部的中断模块
*****************************************************************************/
int bsp_pmu_irq_callback_register(unsigned int irq,pmufuncptr routine,void *data);

/*****************************************************************************
 函 数 名  : bsp_pmu_sim_debtime_set
 功能描述  : 设置SIM卡中断去抖时间，单位是us。
 输入参数  : uctime:设置的去抖时间(范围是(120,600),step:30;)
 输出参数  : 设置成功或失败
 返 回 值  : 无
 调用函数  :
 被调函数  : sim卡模块
*****************************************************************************/
int bsp_pmu_sim_debtime_set(u32 uctime);
void bsp_pmu_ldo22_res_enable(void);
void bsp_pmu_ldo22_res_disable(void);
//unsigned int bsp_pmu_irq_inner_id_get(pmu_int_mod_e mod);
int bsp_pmic_ioshare_status_get(pmic_ioshare_e id);

#endif

#if defined(__OS_RTOSCK__) || defined(__OS_VXWORKS__) || defined(__CMSIS_RTOS)
/*****************************************************************************
 函 数 名  : bsp_pmu_init
 功能描述  : 系统启动初始化pmu相关信号量
 输入参数  : void 输出参数  : 无
 返 回 值  : 无
 调用函数  :被调函数  :ccore和mcore系统初始化相关函数
*****************************************************************************/
void bsp_pmu_init(void);
int bsp_sim_upres_disable(u32 sim_id);
#endif

#if defined(__OS_RTOSCK__) || defined(__OS_VXWORKS__)
s32 bsp_pmu_apt_enable(void);
s32 bsp_pmu_apt_disable(void);
s32 bsp_pmu_apt_status_get(void);
s32 bsp_pmu_parf_exc_check(void);
void bsp_pmu_dcxo_fre_compensate(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value);
#endif

/*fastboot、a、c、mcore都提供*/
/*****************************************************************************
 函 数 名  : bsp_pmu_version_get
 功能描述  : 获取pmu版本号
 输入参数  : void
 输出参数  : 无
 返 回 值  : pmu版本号
 调用函数  :
 被调函数  : 集成hso，msp调用
*****************************************************************************/
char* bsp_pmu_version_get(void);


/*判断ddr是否被改写的魔幻数*/
#define SHM_PMU_VOLTTABLE_MAGIC_START_DATA   0xc7c7c7c7
#define SHM_PMU_VOLTTABLE_MAGIC_END_DATA     0xa6a6a6a6
/*错误码定义*/
#define BSP_PMU_ERROR   -1
#define BSP_PMU_OK      0
#define BSP_PMU_NO_PMIC      0x2001/*系统没有PMU芯片*/
#define BSP_PMU_PARA_ERROR      0x2002/*无效参数值*/
#define BSP_PMU_VOLTTABLE_ERROR      0x2003/*DDR被改写，table表被破坏*/

/*om log*/
/*PMU om log 枚举类型 */
typedef enum  _pmu_om_log_e
{
    PMU_OM_LOG_START = 0,   /*PMU om log*/
    PMU_OM_LOG_RESET,
    PMU_OM_LOG_EXC,       /*wifi clk */
    PMU_OM_LOG_END
}pmu_om_log_e;
#define PMU_OM_LOG            "/modem_log/log/pmu_om.log"
/*debug*/

/*函数声明*/
#if defined(__CMSIS_RTOS)
int bsp_pmu_suspend(void);
int bsp_pmu_resume(void);
int bsp_pmu_sdio_suspend(void);
int bsp_pmu_sdio_resume(void);
void bsp_pmu_volt_state_save(void);
#endif

void bsp_pmu_rfclk_enable(u32 rf_id);
void bsp_pmu_rfclk_disable(u32 rf_id);
int bsp_pmu_rfclk_is_enabled(u32 rf_id);
unsigned int bsp_pmu_get_rtc_value(void);
u32 bsp_pmic_get_base_addr(void);
void bsp_pmic_reg_write(u32 addr, u32 value);
void bsp_pmic_reg_read(u32 addr, u32 *pValue);
void bsp_pmic_reg_write_mask(u32 addr, u32 value, u32 mask);
int bsp_pmic_reg_show(u32 addr);

typedef void (*PMU_OCP_FUNCPTR)(int);
int bsp_pmu_ocp_register(int volt_id,PMU_OCP_FUNCPTR func);


#ifdef __cplusplus
}
#endif

#endif /* end #define _BSP_PMU_H_*/
