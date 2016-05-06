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

#ifndef __SOC_TIMER_H__
#define __SOC_TIMER_H__

#include <hi_base.h>
#include <hi_timer.h>
#include <hi_bbp_systime.h>
#include <bsp_memmap.h>
#include <soc_interrupts.h>
#ifdef __KERNEL__
#include <soc_clk_app.h>
#include <soc_memmap_app.h>
#include <soc_interrupts_app.h>
#elif defined(__VXWORKS__)||defined(__OS_RTOSCK__)
#include <soc_clk_mdm.h>
#include <soc_memmap_mdm.h>
#include <soc_interrupts_mdm.h>
#else
#include <soc_clk.h>
#endif


/*封装udelay延时函数使用的timer基址,后续更换为 ap sys cnt*/
//#define UDELAY_TIMER_ADDR   0xe0300000/*timer1*/
#define UDELAY_TIMER_CLK    1920000

#define CCORE_SYS_TIMER_CLK              HI_TIMER_CLK
#define CCORE_SYS_TIMER_BASE_ADDR        0xE0300000
#define CCORE_SYS_TIMER_INT_LVL          52
//#define UDELAY_CURTIME_ADDR   (UDELAY_TIMER_ADDR+0X1008)


#define TIMER_STAMP_ADDR        (HI_BBP_SYSTIME_BASE_ADDR_VIRT+HI_BBP_SYSTIME_ABS_TIMER_L_OFFSET)
#define TIMER_STAMP_ADDR_PHY    (HI_BBP_SYSTIME_BASE_ADDR +HI_BBP_SYSTIME_ABS_TIMER_L_OFFSET)

/* TimerXRIS中断屏蔽位*/
#define CLK_DEF_TC_INTENABLE	(1<<5)       /* 1：不屏蔽该中断*/
#define CLK_DEF_TC_INTDISABLE	(0<<5)  /* 0：屏蔽该中断 */

/* 定时器的计数模式位*/
#define CLK_DEF_TC_PERIODIC	(1<<6)          /* 1：user-defined count mode*/
#define CLK_DEF_TC_FREERUN	0               /* 0：free-running mode*/

/* 定时器使能位*/
#define CLK_DEF_TC_ENABLE	(1<<7 )    /* 1：Timer使能*/
#define	CLK_DEF_TC_DISABLE	0     /* 0：Timer禁止*/

/*定时器计数器位数*/
#define CLK_DEF_TC_COUNT32BIT	(1<<1)    /* 1：32bit*/
#define	CLK_DEF_TC_COUNT16BIT	0     /* 0：16bit*/

/* 用户时钟使能*/
#define CLK_DEF_ENABLE   (CLK_DEF_TC_PERIODIC | CLK_DEF_TC_INTENABLE | CLK_DEF_TC_ENABLE|CLK_DEF_TC_COUNT32BIT)
/* 用户时钟去使能*/
#define CLK_DEF_DISABLE  (CLK_DEF_TC_PERIODIC | CLK_DEF_TC_INTDISABLE | CLK_DEF_TC_DISABLE|CLK_DEF_TC_COUNT32BIT)

#ifndef __ASSEMBLY__

#ifdef __KERNEL__
static __inline__  void soc_cache_sync(void)
{
	mb();
}
#elif defined(__OS_VXWORKS__)||defined(__OS_RTOSCK__)

extern void osL2CacheSync(void);
static __inline__ void SOC_DWB(void) /* drain write buffer */
{
//    asm volatile ( "mcr p15, 0, r0, c7, c10, 4;");
    asm volatile ( "dsb;" );
}
static __inline__  void soc_cache_sync(void)
{
    SOC_DWB();	
#ifdef CONFIG_BALONG_L2CACHE
    osL2CacheSync();
#endif
}
#endif
static inline void soc_writel(unsigned val, unsigned long addr)
{
    soc_cache_sync();
    (*(volatile unsigned *) (addr)) = (val);
}

static inline unsigned soc_readl(unsigned long addr)
{
    return (*(volatile unsigned *) (addr));
}


static inline void systimer_int_clear(unsigned long addr)
{
	soc_writel(0x1,addr+0xc);
}

/*v7r2 timer使能存在写延时*/
static inline unsigned int systimer_check_enable_success(void)
{
	unsigned int readValueTmp=0,u32Times=100,i=0;
        do
        {
            readValueTmp = soc_readl(CCORE_SYS_TIMER_BASE_ADDR+0x8);
            readValueTmp = readValueTmp&0x10;
            i++;
        }while((!readValueTmp)&&(i<u32Times));
	return i;
}
/*只在无drx timer平台上需要操作
 *k3v3 stamp and udelay全部使用ap侧提供timer*/
static inline void init_timer_stamp(void)
{
	return;
}

static inline void __set_timer_rate(void)
{
	/*disable clk*//*timer 0_0,19.2M */
	soc_writel(0x1,HI_SYSCTRL_BASE_ADDR_VIRT+0x1C);
	soc_writel(0X1,HI_SYSCTRL_BASE_ADDR_VIRT+0x47C);
	/*enable clk*/
	soc_writel(0x1,HI_SYSCTRL_BASE_ADDR_VIRT+0x18);
}

static inline void acore_clocksource_enable_and_mask_int(unsigned addr)
{
	soc_writel(CLK_DEF_ENABLE | CLK_DEF_TC_INTDISABLE,addr+0x8);
}

#endif
#define TIMER_ARM_FEATURE

#define platform_set_timer_rate() __set_timer_rate()

#define ARM_ODD_LOAD_OFFSET          0x20
#define ARM_ODD_VALUE_OFFSET        0x24
#define ARM_ODD_CTRL_OFFSET           0x28
#define ARM_ODD_INTCLR_OFFSET       0x2C
#define ARM_ODD_INTRIS_OFFSET        0x30
#define ARM_ODD_INTMIS_OFFSET       0x34
#define ARM_ODD_BGLOAD_OFFSET     0x38
		
#define ARM_EVEN_LOAD_OFFSET          0x0
#define ARM_EVEN_VALUE_OFFSET        0x4
#define ARM_EVEN_CTRL_OFFSET           0x8
#define ARM_EVEN_INTCLR_OFFSET       0xC
#define ARM_EVEN_INTRIS_OFFSET        0x10
#define ARM_EVEN_INTMIS_OFFSET       0x14
#define ARM_EVEN_BGLOAD_OFFSET     0x18

#endif/*__SOC_TIMER_H__*/

