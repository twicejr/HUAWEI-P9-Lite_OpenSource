/*
 * Copyright (c) 2011 Hisilicon Technologies Co., Ltd. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>
#include <linux/errno.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/clk.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/completion.h>
#include <linux/firmware.h>
#include <linux/input.h>
#include <linux/delay.h>
#include <linux/cpufreq.h>
#include <linux/cpu.h>
#include <linux/cpumask.h>
#include <linux/types.h>
#include <linux/cpumask.h>
#include <linux/ipps.h>
#include <asm/smp_twd.h>
#include <linux/delay.h>

#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_irq.h>
#include <linux/of_device.h>
#include <linux/of_address.h>

#include <linux/mm.h>

#ifdef CONFIG_IPPS_PARAM_ALTERNATIVE
#include "ipps_para.h"
#endif

#define MODULE_NAME		"ipps-v2"
#define DEFAULT_FW_NAME		"ipps/ipps-v2.bin"

#define MCU_TIMEOUT		msecs_to_jiffies(2000)


#define RAM_SIZE		SZ_32K

#define PC_OVERFLOW		(0x100)
#define WDG_TIMEOUT		(0x200)
#define MCU_ERR_IRQ		(PC_OVERFLOW | WDG_TIMEOUT)
#define DEFAULT_INT_MASK	(0x3FF)

#define MCU_DISABLE		0x0
#define MCU_ENABLE		0x01

#define TRIM_REF_VALUE		(0x42)
#define PROFILE_BLOCK_SIZE      (0x100)

#define MCU_CMD_HALT		(0x81)

#define MCU_CMD_GPU_OP_ON	(0x82)
#define MCU_CMD_GPU_OP_OFF	(0x83)
#define MCU_CMD_CPU_OP_ON	(0x84)
#define MCU_CMD_CPU_OP_OFF	(0x85)
#define MCU_CMD_DDR_OP_ON	(0x86)
#define MCU_CMD_DDR_OP_OFF	(0x87)

#define MCU_FUNC_CMD(obj, cmd)	\
	(((obj & IPPS_OBJ_CPU) ? 0x50 : ((obj & IPPS_OBJ_GPU) ? 0x58 : 0x60))\
	 + ((cmd & IPPS_DVFS_AVS_ENABLE) >> 2))

#define MCU_CMD_CPU_PROFILE(n)	(0x10 + (n & 0x0f))
#define MCU_CMD_GPU_PROFILE(n)	(0x20 + (n & 0x07))
#define MCU_CMD_DDR_PROFILE(n)	(0x30 + (n & 0x07))
#define MCU_CMD_POLICY(n)	(0x40 + (n & 0x0f))
#define MCU_CMD_TEMP_ON		(0x71)
#define MCU_CMD_TEMP_OFF	(0x70)

#define	REG_SECRAM_IOSIZE	PAGE_ALIGN(0x14000)

/* used to save mcu irq state */
static unsigned int state;

static void noboot_cpu_enter_wfe(void *info);
static struct tasklet_struct mcu_tasklet;
static void mcu_irq_tasklet(unsigned long data);

union param {
	struct {
		u32 min:8;
		u32 max:8;
		u32 safe:8;
		u32 max1:8;
	} freq;
	struct {
		u32 safe:8;
		u32 alarm:8;
		u32 reset:8;
		u32 cold:8;
	} temp;
	u32 ul32;
};

struct profile {
	u32 freq:16;
	u32 dummy[63];
};

struct cpu_profile {
	u32 freq:16;
	u32 avspara0_2;
	u32 avs_para5_2:4;
	u32 avs_minvol_2:6;
	u32 avs_maxvol_2:6;
	u32 avs_para5_4:4;
	u32 avs_minvol_4:6;
	u32 avs_maxvol_4:6;
	u32 avspara0_4;
	u32 clkprofile0;
	u32 clkprofile1:16;
	u32 rm_para:8;
	u32 vol:8;
	u32 dummy[58];
};

DEFINE_SPINLOCK(mcureg_lock);
#if 0
#define readl_one(addr) \
({ u32 __v;   \
	unsigned long flags;  \
	spin_lock_irqsave(&mcureg_lock, flags);  \
	__v = readl(addr);  \
	spin_unlock_irqrestore(&mcureg_lock, flags);  \
	__v; })


#define writel_one(reg, addr) \
({	unsigned long flags;  \
	spin_lock_irqsave(&mcureg_lock, flags);  \
	writel((reg), (addr)); dsb(); \
	spin_unlock_irqrestore(&mcureg_lock, flags); })
#endif

static inline u32 readl_one(void __iomem *addr)
{	u32 val;
	unsigned long flags;
	spin_lock_irqsave(&mcureg_lock, flags);
	val = readl(addr);
	spin_unlock_irqrestore(&mcureg_lock, flags);
	return val;
}

static inline void writel_one(u32 reg, void __iomem *addr)
{
	unsigned long flags;
	spin_lock_irqsave(&mcureg_lock, flags);
	writel((reg), (addr));
	dsb();
	spin_unlock_irqrestore(&mcureg_lock, flags);
}

#define CPU_RUNTIME_OFFSET	(0x5000)
#define GPU_RUNTIME_OFFSET	(0x5004)
#define DDR_RUNTIME_OFFSET	(0x5008)
#define CUR_POLICY_OFFSET	(0x500C)

#define CPU_PARAM_OFFSET	(0x5010)
#define CPU_MAX_OFFSET		(0x5011)
#define CPU_MAX1_OFFSET		(0x5013)
#define GPU_PARAM_OFFSET	(0x5014)
#define DDR_PARAM_OFFSET	(0x5018)
#define TEMP_PARAM_OFFSET	(0x501C)

#define CPU_STATUS_OFFSET	(0x5020)
#define GPU_STATUS_OFFSET	(0x5024)
#define DDR_STATUS_OFFSET	(0x5028)
#define TEMP_STATUS_OFFSET	(0x502C)
#define HPM_VALUE_OFFSET	(0x5066)
#define TRIM_VOLT_OFFSET	(0x5067)
#define UPDATE_OFFSET		(0x5800)

#define CPU_PROFILE_OFFSET	(0x6000)
#define	GPU_PROFILE_OFFSET	(0x7000)
#define DDR_PROFILE_OFFSET	(0x7800)

#define CFG_OFFSET		(0xF000)
#define INT_STAT_OFFSET		(0xF004)
#define INT_MASK_OFFSET		(0xF008)
#define DEBUG_OFFSET		(0xF00C)

int max_freq_array[] = {1200000, 1399999, 1400000, 1500000, 1508000, 1200000};

struct ipps2 {
	void __iomem		*mmio;
	struct resource         *res;
	unsigned int		irq;
	struct clk		*clk;
	struct mutex		lock;
	struct completion	done;
	u8			shadow[RAM_SIZE];
	struct ipps_device	*idev;
};

struct cmd_proc {
	struct device *dev;
	enum ipps_cmd_type cmd;
	unsigned int object;
	void *data;
	int ret;
};
struct sysreg_base_addr sysreg_base;

/*map system registers*/
static void map_sysregs(void)
{
	struct device_node *np;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,pmctrl");
	sysreg_base.pmctrl_base = of_iomap(np, 0);
	if (WARN_ON(!sysreg_base.pmctrl_base))
		return;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	sysreg_base.sysctrl_base = of_iomap(np, 0);
	if (WARN_ON(!sysreg_base.sysctrl_base))
		return;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,pctrl");
	sysreg_base.pctrl_base = of_iomap(np, 0);
	if (WARN_ON(!sysreg_base.pctrl_base))
		return;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,secram");
	sysreg_base.secram_base = of_iomap(np, 0);
	if (WARN_ON(!sysreg_base.secram_base))
		return;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,ddrcfg");
	sysreg_base.ddrcfg_base = of_iomap(np, 0);
	if (WARN_ON(!sysreg_base.ddrcfg_base))
		return;

	np = of_find_compatible_node(NULL, NULL, "arm,cortex-a9-gic");
	sysreg_base.gic_cpu_base = of_iomap(np, 1);
	if (WARN_ON(!sysreg_base.gic_cpu_base))
		return;
}




static unsigned int
freq_to_index(struct ipps2 *ipps2, unsigned int offset, unsigned int freq)
{
	struct profile *p = (struct profile *)&(ipps2->shadow[offset]);
	unsigned int index = 0;

	while (p && p[index].freq != 0) {
		if (be16_to_cpu(p[index].freq) * 1000 >= freq)
			break;
		index++;
	}

	if (index && p[index].freq == 0)
		index--;

	return index;
}

static unsigned int
index_to_freq(struct ipps2 *ipps2, unsigned int offset, unsigned int index)
{
	struct profile *p = (struct profile *)&(ipps2->shadow[offset]);

	return be16_to_cpu(p[index].freq)*1000;
}


int mcu_command(struct ipps2 *ipps2, u8 cmd)
{
	struct ipps_device *idev = ipps2->idev;
	int ret = 0;
	int i = 100;

	while ((readl_one(ipps2->mmio + CFG_OFFSET) != MCU_ENABLE) && i--) {
		if (readl_one(ipps2->mmio + CFG_OFFSET) == MCU_DISABLE)
			return -1;

		msleep(1);
	}

	writel_one((cmd << 8) | MCU_ENABLE, ipps2->mmio + CFG_OFFSET);
	if ((cmd & 0x80)
		&& !wait_for_completion_timeout(&ipps2->done, MCU_TIMEOUT)) {
		writel_one(MCU_ENABLE, ipps2->mmio + CFG_OFFSET);
		dev_warn(idev->dev, "WARN: MCU CMD TIMEOUT [%x]\nSTATUS DUMP:\n"
			"%08x\t%08x\t%08x\t%08x\n%08x\t%08x\t%08x\t%08x\n%08x\t%08x\t%08x\t%08x\nPC:%08x CFG:%08x INT:%08x\n",
			cmd,
			readl_one(ipps2->mmio + 0x5000),
			readl_one(ipps2->mmio + 0x5004),
			readl_one(ipps2->mmio + 0x5008),
			readl_one(ipps2->mmio + 0x500C),
			readl_one(ipps2->mmio + 0x5010),
			readl_one(ipps2->mmio + 0x5014),
			readl_one(ipps2->mmio + 0x5018),
			readl_one(ipps2->mmio + 0x501C),
			readl_one(ipps2->mmio + 0x5020),
			readl_one(ipps2->mmio + 0x5024),
			readl_one(ipps2->mmio + 0x5028),
			readl_one(ipps2->mmio + 0x502C),
			readl_one(ipps2->mmio + DEBUG_OFFSET),
			readl_one(ipps2->mmio + CFG_OFFSET),
			readl_one(ipps2->mmio + INT_STAT_OFFSET));
		ret = -ETIMEDOUT;
	}
	return ret;
}

static int
mcu_cmd_proc(struct device *dev, enum ipps_cmd_type cmd,
	     unsigned int object, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct ipps2 *ipps2 = platform_get_drvdata(pdev);
	int ret;
	u8 mcu_cmd;

	mutex_lock(&ipps2->lock);
	mcu_cmd = 0;
	switch (cmd) {
	case IPPS_GET_FREQS_TABLE:
	{
		struct cpufreq_frequency_table *table = (struct cpufreq_frequency_table *)data;
		struct profile *profile = NULL;
		union param *param = NULL;
		int index = 0;

		if (object & IPPS_OBJ_CPU) {
			profile = (struct profile *)&(ipps2->shadow[CPU_PROFILE_OFFSET]);
			param = (union param *)&(ipps2->shadow[CPU_PARAM_OFFSET]);
		} else if (object & IPPS_OBJ_GPU) {
			profile = (struct profile *)&(ipps2->shadow[GPU_PROFILE_OFFSET]);
			param = (union param *)&(ipps2->shadow[GPU_PARAM_OFFSET]);
		} else if (object & IPPS_OBJ_DDR) {
			profile = (struct profile *)&(ipps2->shadow[DDR_PROFILE_OFFSET]);
			param = (union param *)&(ipps2->shadow[DDR_PARAM_OFFSET]);
		}

		while (profile && profile[index].freq != 0 && index <= param->freq.max) {
			table->index = index;
			table->frequency = be16_to_cpu(profile[index].freq) * 1000;
			table++;
			index++;
		}
		table->index = index;
		table->frequency = CPUFREQ_TABLE_END;
		break;
	}

	case IPPS_GET_CUR_FREQ:
		if (object & IPPS_OBJ_CPU)
			*(unsigned int *)data = index_to_freq(ipps2, CPU_PROFILE_OFFSET, readl_one(ipps2->mmio + CPU_RUNTIME_OFFSET) & 0x0f);
		else if (object & IPPS_OBJ_GPU)
			*(unsigned int *)data = index_to_freq(ipps2, GPU_PROFILE_OFFSET, readl_one(ipps2->mmio + GPU_RUNTIME_OFFSET) & 0x0f);
		else if (object & IPPS_OBJ_DDR)
			*(unsigned int *)data = index_to_freq(ipps2, DDR_PROFILE_OFFSET, readl_one(ipps2->mmio + DDR_RUNTIME_OFFSET) & 0x0f);
		break;

	case IPPS_SET_CUR_FREQ:
		if (object & IPPS_OBJ_CPU)
			mcu_cmd = MCU_CMD_CPU_PROFILE(freq_to_index(ipps2, CPU_PROFILE_OFFSET, *(unsigned int *)data));
		else if (object & IPPS_OBJ_GPU)
			mcu_cmd = MCU_CMD_GPU_PROFILE(freq_to_index(ipps2, GPU_PROFILE_OFFSET, *(unsigned int *)data));
		else if (object & IPPS_OBJ_DDR)
			mcu_cmd = MCU_CMD_DDR_PROFILE(freq_to_index(ipps2, DDR_PROFILE_OFFSET, *(unsigned int *)data));
		break;

	case IPPS_GET_CUR_POLICY:
		*(unsigned int *)data = readl_one(ipps2->mmio + CUR_POLICY_OFFSET) & 0xFF;
		break;

	case IPPS_SET_CUR_POLICY:
		writel_one(*(unsigned int *)data, ipps2->mmio + CUR_POLICY_OFFSET);
		ipps2->shadow[CUR_POLICY_OFFSET] = *(u8 *)data;
		break;

	case IPPS_GET_PARAM:
	{
		struct ipps_param *param = (struct ipps_param *)data;
		union param *p = (union param *)&(ipps2->shadow[CPU_PARAM_OFFSET]);
		if (object & IPPS_OBJ_CPU) {
			param->cpu.min_freq = index_to_freq(ipps2, CPU_PROFILE_OFFSET, p->freq.min);
			param->cpu.max_freq = index_to_freq(ipps2, CPU_PROFILE_OFFSET, p->freq.max);
			param->cpu.safe_freq = index_to_freq(ipps2, CPU_PROFILE_OFFSET, p->freq.safe);
		}
		p++;
		if (object & IPPS_OBJ_GPU) {
			param->gpu.min_freq = index_to_freq(ipps2, GPU_PROFILE_OFFSET, p->freq.min);
			param->gpu.max_freq = index_to_freq(ipps2, GPU_PROFILE_OFFSET, p->freq.max);
			param->gpu.safe_freq = index_to_freq(ipps2, GPU_PROFILE_OFFSET, p->freq.safe);
		}
		p++;
		if (object & IPPS_OBJ_DDR) {
			param->ddr.min_freq = index_to_freq(ipps2, DDR_PROFILE_OFFSET, p->freq.min);
			param->ddr.max_freq = index_to_freq(ipps2, DDR_PROFILE_OFFSET, p->freq.max);
			param->ddr.safe_freq = index_to_freq(ipps2, DDR_PROFILE_OFFSET, p->freq.safe);
		}
		p++;
		if (object & IPPS_OBJ_TEMP) {
			param->temp.safe = p->temp.safe * 200/255 - 40;
			param->temp.alarm = p->temp.alarm * 200/255 - 40;
			param->temp.reset = p->temp.reset * 200/255 - 40;
		}
		break;
	}

	case IPPS_SET_PARAM:
	{
		struct ipps_param *param = (struct ipps_param *) data;
		union param *p = (union param *)&(ipps2->shadow[CPU_PARAM_OFFSET]);
		if (object & IPPS_OBJ_CPU) {
			if (param->cpu.block_freq != 0) {
				p->freq.min = freq_to_index(ipps2, CPU_PROFILE_OFFSET, param->cpu.block_freq);
				p->freq.max = p->freq.min;
			} else {
				p->freq.min = freq_to_index(ipps2, CPU_PROFILE_OFFSET, param->cpu.min_freq);
				p->freq.max = freq_to_index(ipps2, CPU_PROFILE_OFFSET, param->cpu.max_freq);
			}
			p->freq.safe = freq_to_index(ipps2, CPU_PROFILE_OFFSET, param->cpu.safe_freq);
			writel_one(p->ul32, ipps2->mmio + CPU_PARAM_OFFSET);
		}
		p++;
		if (object & IPPS_OBJ_GPU) {
			if (param->gpu.block_freq != 0) {
				p->freq.min = freq_to_index(ipps2, GPU_PROFILE_OFFSET, param->gpu.block_freq);
				p->freq.max = p->freq.min;
			} else {
				p->freq.min = freq_to_index(ipps2, GPU_PROFILE_OFFSET, param->gpu.min_freq);
				p->freq.max = freq_to_index(ipps2, GPU_PROFILE_OFFSET, param->gpu.max_freq);
			}
			p->freq.safe = freq_to_index(ipps2, GPU_PROFILE_OFFSET, param->gpu.safe_freq);
			writel_one(p->ul32, ipps2->mmio + GPU_PARAM_OFFSET);
		}
		p++;
		if (object & IPPS_OBJ_DDR) {
			if (param->ddr.block_freq != 0) {
				p->freq.min = freq_to_index(ipps2, DDR_PROFILE_OFFSET, param->ddr.block_freq);
				p->freq.max = p->freq.min;
			} else {
				p->freq.min = freq_to_index(ipps2, DDR_PROFILE_OFFSET, param->ddr.min_freq);
				p->freq.max = freq_to_index(ipps2, DDR_PROFILE_OFFSET, param->ddr.max_freq);
			}
			p->freq.safe = freq_to_index(ipps2, DDR_PROFILE_OFFSET, param->ddr.safe_freq);
			writel_one(p->ul32, ipps2->mmio + DDR_PARAM_OFFSET);
		}
		p++;
		if (object & IPPS_OBJ_TEMP) {
			p->temp.safe = (param->temp.safe + 40) / 200 * 255;
			p->temp.alarm = (param->temp.alarm + 40) / 200 * 255;
			p->temp.reset = (param->temp.reset + 40) / 200 * 255;
			writel_one(p->ul32, ipps2->mmio + TEMP_PARAM_OFFSET);
		}
		break;
	}

	case IPPS_GET_MODE:
		if (object & IPPS_OBJ_CPU)
			*(unsigned int *)data = readl_one(ipps2->mmio + CPU_STATUS_OFFSET) & 0x01 ? IPPS_ENABLE : IPPS_DISABLE;
		else if (object & IPPS_OBJ_GPU)
			*(unsigned int *)data = readl_one(ipps2->mmio + GPU_STATUS_OFFSET) & 0x01 ? IPPS_ENABLE : IPPS_DISABLE;
		else if (object & IPPS_OBJ_DDR)
			*(unsigned int *)data = readl_one(ipps2->mmio + DDR_STATUS_OFFSET) & 0x01 ? IPPS_ENABLE : IPPS_DISABLE;
		else if (object & IPPS_OBJ_TEMP)
			*(unsigned int *)data = readl_one(ipps2->mmio + TEMP_STATUS_OFFSET) & 0x01 ? IPPS_ENABLE : IPPS_DISABLE;
		break;

	case IPPS_SET_MODE:
		if (object & IPPS_OBJ_CPU)
			mcu_cmd = (*(unsigned int *)data == IPPS_ENABLE) ? MCU_CMD_CPU_OP_ON : MCU_CMD_CPU_OP_OFF;
		else if (object & IPPS_OBJ_GPU)
			mcu_cmd = (*(unsigned int *)data == IPPS_ENABLE) ? MCU_CMD_GPU_OP_ON : MCU_CMD_GPU_OP_OFF;
		else if (object & IPPS_OBJ_DDR)
			mcu_cmd = (*(unsigned int *)data == IPPS_ENABLE) ? MCU_CMD_DDR_OP_ON : MCU_CMD_DDR_OP_OFF;
		else if (object & IPPS_OBJ_TEMP)
			mcu_cmd = (*(unsigned int *)data == IPPS_ENABLE) ? MCU_CMD_TEMP_ON : MCU_CMD_TEMP_OFF;

		break;

	case IPPS_GET_FUNC:
		if (object & IPPS_OBJ_DDR)
			*(unsigned int *)data = readl_one(ipps2->mmio + DDR_STATUS_OFFSET) & IPPS_DFS_ENABLE;
		else if (object & IPPS_OBJ_CPU)
			*(unsigned int *)data = readl_one(ipps2->mmio + CPU_STATUS_OFFSET) & IPPS_DVFS_AVS_ENABLE;
		else if (object & IPPS_OBJ_GPU)
			*(unsigned int *)data = readl_one(ipps2->mmio + GPU_STATUS_OFFSET) & IPPS_DVFS_AVS_ENABLE;

		break;

	case IPPS_SET_FUNC:
		if (object & IPPS_OBJ_CPU) {
			mcu_cmd = MCU_FUNC_CMD(IPPS_OBJ_CPU, *(unsigned char *)data);
			ipps2->shadow[CPU_STATUS_OFFSET] &= ~IPPS_DVFS_AVS_ENABLE;
			ipps2->shadow[CPU_STATUS_OFFSET] |= *(unsigned char *)data;
		} else if  (object & IPPS_OBJ_GPU) {
			mcu_cmd = MCU_FUNC_CMD(IPPS_OBJ_GPU, *(unsigned char *)data);
			ipps2->shadow[GPU_STATUS_OFFSET] &= ~IPPS_DVFS_AVS_ENABLE;
			ipps2->shadow[GPU_STATUS_OFFSET] |= *(unsigned char *)data;
		} else if (object & IPPS_OBJ_DDR) {
			mcu_cmd = MCU_FUNC_CMD(IPPS_OBJ_DDR, *(unsigned char *)data);
			ipps2->shadow[DDR_STATUS_OFFSET] &= ~IPPS_DFS_ENABLE;
			ipps2->shadow[DDR_STATUS_OFFSET] |= *(unsigned char *)data;
		}
		break;

	case IPPS_CAPACITY_LIMIT:
	{
		int *param = (int *)data;
		union param *p = (union param *)&(ipps2->shadow[CPU_PARAM_OFFSET]);
		if (object & IPPS_OBJ_CPU) {
			if (*param == 1) {
				if (p->freq.max > 0x07 && p->freq.max1 == 0x08) {
					p->freq.max1 = p->freq.max + 1;
					writel_one(p->ul32, ipps2->mmio + CPU_PARAM_OFFSET);
				}
			} else if (p->freq.max > 0x07 && p->freq.max1 != 0x08) {
				p->freq.max1 = 0x08;
				writel_one(p->ul32, ipps2->mmio + CPU_PARAM_OFFSET);
			}
		}
	}

	default:
		break;
	}
	if (mcu_cmd)
		ret = mcu_command(ipps2, mcu_cmd);
	else
		ret = 0;
	mutex_unlock(&ipps2->lock);
	return ret;
}

static void mcu_enable(struct ipps2 *ipps2)
{
	int i;
	struct ipps_device *idev = ipps2->idev;

	unsigned long *src = (unsigned long *)ipps2->shadow;
	unsigned long *dst = (unsigned long *)ipps2->mmio;
	mutex_lock(&ipps2->lock);

	writel_one(MCU_DISABLE, ipps2->mmio + CFG_OFFSET);

	/*if dvfsen==1 it's pull back, we use curr firmware*/
	if ((readl(sysreg_base.pmctrl_base + 0x100) & 0x1) != 0x1) {
		for (i = 0; i < RAM_SIZE; i += 4)
			writel_one(*src++, dst++);
	}

	writel_one(0, ipps2->mmio + INT_STAT_OFFSET);
	writel_one(DEFAULT_INT_MASK, ipps2->mmio + INT_MASK_OFFSET);
	writel(0x0000000F, sysreg_base.pctrl_base + 0x174); /* Clear HW resource lock */
	writel_one(MCU_ENABLE, ipps2->mmio + CFG_OFFSET);

	idev->command = mcu_cmd_proc;

	tasklet_init(&mcu_tasklet, mcu_irq_tasklet, (unsigned long)ipps2);

	mutex_unlock(&ipps2->lock);
}

static void mcu_disable(struct ipps2 *ipps2)
{
	struct ipps_device *idev = ipps2->idev;

	mutex_lock(&ipps2->lock);

	tasklet_kill(&mcu_tasklet);

	idev->command = NULL;

	mcu_command(ipps2, MCU_CMD_HALT);

	writel_one(0, ipps2->mmio + INT_MASK_OFFSET);
	writel_one(MCU_DISABLE, ipps2->mmio + CFG_OFFSET);
	mutex_unlock(&ipps2->lock);
}


static void noboot_cpu_enter_wfe(void *info)
{
	register int flage = 0;
	unsigned int cpu = smp_processor_id();

	void __iomem *seram_addr = sysreg_base.secram_base
				+ REG_SECRAM_IOSIZE - 0x100 - (cpu << 2);
	void __iomem *sec_core_addr = sysreg_base.secram_base
				+ REG_SECRAM_IOSIZE - 0xF0;

	/*  close gic and wfe */
	writel_relaxed(0, sysreg_base.gic_cpu_base);
	dsb();

	__asm__ __volatile__(
		"PLI        [pc, #0]\n"
		"PLI        [pc, #28]\n"
		"PLI        [pc, #56]\n"
	);
	writel(0xdead, seram_addr);

	dsb();
	do {
		flage = readl_relaxed(sec_core_addr);
		if (flage)
			wfe();
	} while (flage);

	/* enable gic cpu ctrl */
	writel_relaxed(1, sysreg_base.gic_cpu_base);
	dsb();
}

static void mcu_irq_tasklet(unsigned long data)
{
	struct ipps2 *ipps2 = (struct ipps2 *)data;
	struct ipps_device *idev = ipps2->idev;

	if (state & MCU_ERR_IRQ) {
		dev_err(idev->dev, "%s%s mcu dump: [cfg]0x%04X, [int]0x%04X, [intmask]0x%04X, [dbg]0x%04X\n",
			state & PC_OVERFLOW ? "PC overflow\n" : "",
			state & WDG_TIMEOUT ? "watchdog timeout\n" : "",
			readl_one(ipps2->mmio + CFG_OFFSET),
			state,
			readl_one(ipps2->mmio + INT_MASK_OFFSET),
			readl_one(ipps2->mmio + DEBUG_OFFSET));
		dev_warn(idev->dev, "STATUS DUMP:\n"
			"%08x\t%08x\t%08x\t%08x\n%08x\t%08x\t%08x\t%08x\n%08x\t%08x\t%08x\t%08x\n",
			readl_one(ipps2->mmio + 0x5000),
			readl_one(ipps2->mmio + 0x5004),
			readl_one(ipps2->mmio + 0x5008),
			readl_one(ipps2->mmio + 0x500C),
			readl_one(ipps2->mmio + 0x5010),
			readl_one(ipps2->mmio + 0x5014),
			readl_one(ipps2->mmio + 0x5018),
			readl_one(ipps2->mmio + 0x501C),
			readl_one(ipps2->mmio + 0x5020),
			readl_one(ipps2->mmio + 0x5024),
			readl_one(ipps2->mmio + 0x5028),
			readl_one(ipps2->mmio + 0x502C));
		BUG_ON(1);
	} else {
		int irqflage = 0;
		int cpu_num = 0;
		register int flage;
		int cpu;
		int i;
		void __iomem *sctl_addr;
		int timeout = 1000;
		void __iomem *sec_core_addr;
		struct cpumask targets;

		if ((state & 0xff) == 0x80) {
			for (i = 0; i < CONFIG_NR_CPUS; i++)
				writel(0, sysreg_base.secram_base + REG_SECRAM_IOSIZE - 0x100 - (i << 2));

			/* set states to tell secondary core in deep sleep. */
			sec_core_addr = sysreg_base.secram_base + REG_SECRAM_IOSIZE - 0xF0;
			writel(0x23FE, sec_core_addr);

			/* send IPI to force the other cpu enter WFE */
			cpumask_copy(&targets, cpu_active_mask);
			cpumask_clear_cpu(smp_processor_id(), &targets);
			smp_call_function_many(&targets,
				noboot_cpu_enter_wfe, NULL, false);

			/* disable gic cpu ctrl */
			writel_relaxed(0, sysreg_base.gic_cpu_base);
			dsb();

			do {
				cpu_num = 0;
				irqflage = 0;
				flage = 0;
				/* FIXME: This should be done in userspace --RR */
				for_each_cpu((cpu), cpu_active_mask) {
					cpu_num++;
					if (cpu == 0)
						continue;

					if (cpu_active(cpu)) {
						flage = readl(sysreg_base.secram_base + REG_SECRAM_IOSIZE - 0x100 - (cpu << 2));
						if (flage == 0xdead)
							irqflage |= 1 << cpu;
					}
				}
				flage = 0;
				for (i = 1; i < cpu_num; i++)
					flage |= 1 << i;
				if (flage == irqflage)
					break;
				else {
					udelay(10);
					timeout--;
				}
			} while ((flage != irqflage) && timeout > 0);

			sctl_addr = sysreg_base.sysctrl_base + 0x318;
			if (timeout > 0) {
				__asm__ __volatile__(
					"PLI		[pc, #0]\n"
					"PLI		[pc, #28]\n"
					"PLI		[pc, #56]\n"
				);

				writel(2, sctl_addr);

				dsb();
				do {
					flage = readl_relaxed(sctl_addr);
					if (flage)
						wfe();
				} while (flage);
			} else {
				dev_warn(idev->dev, "WARN: CPU BUSY! cpu num[%d], flag[0x%x] irqflag[0x%x]\n",
							cpu_num, flage, irqflage);
				writel(4, sctl_addr);
			}
			/* tell secondary cores out wfe. */
			writel(0, sec_core_addr);

			/* enable gic cpu ctrl */
			writel_relaxed(1, sysreg_base.gic_cpu_base);
			dsb();
			sev();

		} else if (state & 0x80) {
			complete(&ipps2->done);
		} else {
			dev_warn(idev->dev, "MCU send undefine irq [%x]\n",
					state);
		}
	}
}



static irqreturn_t mcu_irq(int irq, void *args)
{
	struct ipps2 *ipps2 = (struct ipps2 *)args;

	state = readl_one(ipps2->mmio + INT_STAT_OFFSET);
	writel_one(0, ipps2->mmio + INT_STAT_OFFSET);

	/* Clear HW resource lock */
	writel(0x0000000F, sysreg_base.pctrl_base + 0x174);

	/* schedule the tasklet to do real work */
	tasklet_hi_schedule(&mcu_tasklet);

	return IRQ_HANDLED;
}

/*get hpm_vol_val from cmdline*/
#define HEX_STRING_MAX (10)
int hpm_vol_val;
int get_str_len(char *str)
{
	int count = 0;
	char *p = str;

	while ((*p != ',') && (*p != '\0'))     {
		count++;
		p++;
	}

	return count;
}

static int __init early_parse_hpm_cmdline(char *p)
{
	char tmpbuf[HEX_STRING_MAX + 1];
	char *endptr = NULL;
	int str_len;

	memset(tmpbuf, 0, HEX_STRING_MAX + 1);

	str_len = get_str_len(p);
	memcpy(tmpbuf, p, str_len);
	tmpbuf[str_len] = '\0';
	hpm_vol_val = simple_strtoull(tmpbuf, &endptr, 10);

	pr_info(KERN_INFO "hpm_value = %d.\n", hpm_vol_val);

	return 0;
}
early_param("hpm_value", early_parse_hpm_cmdline);

int get_hpm_vol_val(void)
{
	return hpm_vol_val;
}
#if 0
static void trim_patch(struct ipps2 *ipps2, int hpm_value)
{
	int offset, i = 0;
	struct cpu_profile *p;
	offset = hpm_value - TRIM_REF_VALUE;

	if (offset > 0) {
		offset++;
		if (offset > 8)
			offset = 8;

		dev_info(ipps2->idev->dev, "trim voltage offset: %dmv\n",
			((offset * 900) >> 7));

		p = (struct cpu_profile *)&(ipps2->shadow[CPU_PROFILE_OFFSET]);
		for (i = 0; i <= ipps2->shadow[CPU_MAX_OFFSET]; i++) {
			p[i].avs_maxvol_2 += offset;
			p[i].avs_maxvol_4 += offset;
			p[i].vol += offset;
		}

	}
}
#endif

int cpu_max_freq;

static int __init early_parse_cpumaxfreq_cmdline(char *p)
{
	char tmpbuf[HEX_STRING_MAX + 1];
	char *endptr = NULL;
	int str_len;

	memset(tmpbuf, 0, HEX_STRING_MAX + 1);

	str_len = get_str_len(p);
	memcpy(tmpbuf, p, str_len);
	tmpbuf[str_len] = '\0';
	cpu_max_freq = simple_strtoull(tmpbuf, &endptr, 10);

	pr_info("cpu_maxfreq = %d.\n", cpu_max_freq);

	return 0;
}
early_param("cpu_maxfreq", early_parse_cpumaxfreq_cmdline);

int get_cpu_max_freq(void)
{
	return cpu_max_freq;
}

static void cpu_profile_adjust(struct ipps2 *ipps2)
{
	int max_freq, index, index_freq;
	unsigned int cpu_level, cpu_iddq, efuse_version, date, update_level;
	unsigned long efuse0, efuse2, efuse3;
	union param *p;

#ifdef CONFIG_CPU_MAX_FREQ
	max_freq = CONFIG_CPU_MAX_FREQ;
#else
	efuse0 = readl(sysreg_base.pctrl_base + 0x1DC);
	efuse_version = (efuse0 >> 29) & 0x07;

	max_freq = 1200000;
	if (efuse_version == 1) {
		efuse2 = readl(sysreg_base.pctrl_base + 0x1D4);
		efuse3 = readl(sysreg_base.pctrl_base + 0x1D0);

		cpu_level = (efuse0 >> 18) & 0x3F;
		cpu_iddq = ((efuse2 & 0x01) << 7) | (efuse3 >> 25);
		date = (efuse2 >> 17) & 0x1FFF;
		dev_info(ipps2->idev->dev, "efuse info:%d,%d,%d,%d\n", efuse_version, cpu_level, cpu_iddq, date);
		if (date > 0x1952) {   /* date 2012-10-18, after is B40, before is B30*/
			if ((cpu_level == 8) && (cpu_iddq <= 40))
				max_freq = max_freq_array[4]; /* 1508000 */
			else if ((cpu_level == 7) && (cpu_iddq <= 40))
				max_freq = max_freq_array[3]; /* 1500000 */
			else if ((cpu_level >= 3) && (cpu_level <= 8) && (cpu_iddq <= 50))
				max_freq = max_freq_array[1]; /*1400000 - 1*/
			else
				max_freq = max_freq_array[0]; /*1200000 */
		} else {
			if ((cpu_level >= 5) && (cpu_level <= 7) && (cpu_iddq <= 35))
				max_freq = max_freq_array[2]; /* 1400+ */
			else if ((cpu_iddq <= 40) && (cpu_level >= 3) && (cpu_level <= 7))
				max_freq = max_freq_array[1]; /* 1400000 - 1 */
			else
				max_freq = max_freq_array[0]; /* 1200000 */
		}
	} else if (efuse_version >= 2) {
		cpu_level = (efuse0 >> 22) & 0x0F;
		update_level = (efuse0 >> 26) & 0x07;
		dev_info(ipps2->idev->dev, "efuse info:%d,%d,%d\n", efuse_version, cpu_level, update_level);
		if (update_level > 2)
			index = cpu_level - (update_level - 2);
		else
			index = cpu_level + update_level;

		index--;
		if (index < 0)
			index = 0;

		if (index > (ARRAY_SIZE(max_freq_array) - 1))
			index = ARRAY_SIZE(max_freq_array) - 1;

		max_freq = max_freq_array[index];
	} else {
		max_freq = get_cpu_max_freq();
		/* FIXED ME: max_freq should passed by fastboot */
		max_freq = 1200000;

		if (max_freq == 1400) {
			max_freq = 1400000 - 1;
			dev_info(ipps2->idev->dev, "set max cpufreq 1.4G according to NV\n");
		} else {
			max_freq = 1200000; /* Default 1200M */
			dev_info(ipps2->idev->dev, "set max cpufreq 1.2G according to NV\n");
		}
	}
#endif
	index = freq_to_index(ipps2, CPU_PROFILE_OFFSET, max_freq);
	index_freq = index_to_freq(ipps2, CPU_PROFILE_OFFSET, index);
	p = (union param *)&(ipps2->shadow[CPU_PARAM_OFFSET]);
	if (max_freq >= index_freq) {
		p->freq.max = index;
		p->freq.max1 = index + 1;
	} else {
		p->freq.max = index;
		p->freq.max1 = index;
	}

#ifdef CONFIG_TRIM_VOL
	trim_patch(ipps2, get_hpm_vol_val());
#endif
}

static void firmware_request_complete(const struct firmware *fw,
							 void *context)
{
	struct device *dev = (struct device *)context;
	struct platform_device *pdev = to_platform_device(dev);
	struct ipps2 *ipps2 = platform_get_drvdata(pdev);
	struct ipps_device *idev;
	unsigned long ddr_type;
	int ret;

	dev_err(dev, "just enter firmware_request_complete\n");
	if (NULL == fw || fw->size != RAM_SIZE) {
		if (NULL == fw)
			dev_err(dev, "fw is NULL\n");
		dev_err(dev, "cannot get firmware\n");
		goto exit;
	}

	idev = ipps_alloc_device(sizeof(struct ipps_device));
	if (NULL == idev) {
		dev_err(dev, "cannot alloc idev memory\n");
		goto exit;
	}

	idev->dev = dev;

	ipps2->idev = idev;

	memcpy((void *)ipps2->shadow, (void *)fw->data, RAM_SIZE);

#ifdef CONFIG_IPPS_PARAM_ALTERNATIVE
		memcpy((void *)ipps2->shadow+CPU_RUNTIME_OFFSET, (void *)common, sizeof(common));
		memcpy((void *)ipps2->shadow+CPU_PROFILE_OFFSET, (void *)cpu_profile, sizeof(cpu_profile));
		memcpy((void *)ipps2->shadow+GPU_PROFILE_OFFSET, (void *)gpu_profile, sizeof(gpu_profile));
		memcpy((void *)ipps2->shadow+DDR_PROFILE_OFFSET, (void *)ddr_profile, sizeof(ddr_profile));
		cpu_profile_adjust(ipps2);
#endif

	ddr_type = readl(sysreg_base.ddrcfg_base+0x1C);
	dev_info(dev, "DDR type:%lx\n", ddr_type);
	if ((ddr_type & 0x700) == 0x200)	{
		idev->object = IPPS_OBJ_CPU | IPPS_OBJ_GPU | IPPS_OBJ_DDR | IPPS_OBJ_TEMP;
	} else {
		idev->object = IPPS_OBJ_CPU | IPPS_OBJ_GPU | IPPS_OBJ_TEMP;
		ipps2->shadow[DDR_STATUS_OFFSET] = 0x0;
	}

	mcu_enable(ipps2);

	ret = ipps_register_device(idev);
	if (ret) {
		dev_err(dev, "cannot register ipps device\n");
		goto exit;
	}

	dev_err(dev, "just exit firmware_request_complete, ret = %d\n", ret);
exit:
	release_firmware(fw);

}


/* stop no dev release warning */
static void ipps2_release(struct device *dev)
{
}

int ipps2_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ipps2 *ipps2;
	struct resource *res;

	int ret;

	/* stop no dev release warning */
	dev->release = ipps2_release;

	ipps2 = devm_kzalloc(&pdev->dev, sizeof(struct ipps2), GFP_KERNEL);
	if (!ipps2) {
		dev_err(dev, "cannot get memory\n");
		return -ENOMEM;
	}

	ipps2->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(ipps2->clk)) {
		dev_err(dev, "cannot get mcu clock\n");
		ret = PTR_ERR(ipps2->clk);
		return ret;
	}
	platform_set_drvdata(pdev, ipps2);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(dev, "cannot find register resource\n");
		ret = -EINVAL;
		return ret;
	}

	ipps2->res = devm_request_mem_region(&pdev->dev, res->start, resource_size(res), dev_name(dev));
	if (!ipps2->res) {
		dev_err(dev, "cannot reserve registers\n");
		ret = -ENOENT;
		return ret;
	}

	ipps2->mmio = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	if (!ipps2->mmio) {
		dev_err(dev, "cannot map registers\n");
		ret = -ENXIO;
		return ret;
	}

	ret = platform_get_irq(pdev, 0);
	if (ret < 0) {
		dev_err(&pdev->dev, "cannot find IRQ\n");
		return ret;
	}

	ipps2->irq = ret;

	ret = devm_request_irq(&pdev->dev, ret, mcu_irq, IRQF_DISABLED, dev_name(dev), ipps2);
	if (ret < 0) {
		dev_err(dev, "cannot claim IRQ\n");
		return ret;
	}

	init_completion(&ipps2->done);
	mutex_init(&ipps2->lock);
	clk_prepare_enable(ipps2->clk);

	/*map all the necessary system registers for the driver*/
	map_sysregs();

	ret = request_firmware_nowait(THIS_MODULE, FW_ACTION_HOTPLUG,
			DEFAULT_FW_NAME,
			dev,
			GFP_KERNEL,
			dev,
			firmware_request_complete);

	if (ret) {
		dev_err(dev, "cannot load firmware\n");
		return ret;
	}

	return 0;
}


static int ipps2_remove(struct platform_device *pdev)
{
	struct ipps2 *ipps2 = platform_get_drvdata(pdev);
	struct ipps_device *idev = ipps2->idev;

	if (idev) {
		if (idev->command)
			mcu_disable(ipps2);

		ipps_unregister_device(ipps2->idev);
		ipps_dealloc_device(ipps2->idev);
	}

	free_irq(ipps2->irq, ipps2);
	iounmap(ipps2->mmio);

	release_resource(ipps2->res);
	kfree(ipps2->res);

	clk_disable(ipps2->clk);
	clk_put(ipps2->clk);

	kfree(ipps2);

	return 0;
}


#ifdef CONFIG_PM_SLEEP
static int ipps2_suspend(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct ipps2 *ipps2 = platform_get_drvdata(pdev);
	struct ipps_device *idev = ipps2->idev;
	pr_info("ipps2_suspend+");
	if (idev && idev->command)
		mcu_disable(ipps2);
	pr_info("ipps2_suspend-");

	return 0;
}

static int ipps2_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct ipps2 *ipps2 = platform_get_drvdata(pdev);
	struct ipps_device *idev = ipps2->idev;

	pr_info("ipps2_resume+");
	if (idev && NULL == idev->command)
		mcu_enable(ipps2);
	pr_info("ipps2_resume-");

	return 0;
}
static SIMPLE_DEV_PM_OPS(ipps2_pm_ops, ipps2_suspend, ipps2_resume);
#endif

#ifdef CONFIG_OF
static const struct of_device_id mcu_match[] = {
	{ .compatible = "hisilicon,hi3620-mcu" },
	{},
};
MODULE_DEVICE_TABLE(of, mcu_match);
#endif

static struct platform_driver ipps2_driver = {
	.probe		= ipps2_probe,
	.remove		= ipps2_remove,
	.driver = {
		.name = MODULE_NAME,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(mcu_match),
#ifdef CONFIG_PM_SLEEP
		.pm	= &ipps2_pm_ops,
#endif
		.shutdown = (void(*)(struct device *dev))(ipps2_suspend),
	},
};

static int __init ipps2_init(void)
{
	return platform_driver_register(&ipps2_driver);
}

void __exit ipps2_exit(void)
{
	platform_driver_unregister(&ipps2_driver);
}

module_init(ipps2_init);
module_exit(ipps2_exit);

MODULE_DESCRIPTION("ipps v2 driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" MODULE_NAME);
MODULE_AUTHOR("Hisilicon");
MODULE_FIRMWARE(DEFAULT_FW_NAME);
MODULE_FIRMWARE(DEFAULT_FW_NAME_ES);
