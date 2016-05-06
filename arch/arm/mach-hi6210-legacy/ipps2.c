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
#include <mach/platform.h>
#include <mach/irqs.h>
#include <linux/ipps.h>
#include <mach/boardid.h>
#include <asm/hardware/gic.h>
#include <asm/smp_twd.h>
#include <linux/delay.h>

#include "ipps_para.h"
#include "ipps_profile.h"
#include "pwrctrl_multi_def.h"
#include "pwrctrl_multi_dfs.h"
#include <mach/pwrctrl/pwrctrl_dfs.h>
#include <mach/pwrctrl/pwrctrl_common.h>


#define MODULE_NAME			"ipps-v2"
#define DEFAULT_FW_NAME		"ipps/ipps-v2.bin"
#define ES_FW_NAME			"ipps/ipps-v2-es.bin"

#define MCA_DEBUG printk

#define MCU_TIMEOUT			msecs_to_jiffies(2000)

#define PC_OVERFLOW			(0x100)
#define WDG_TIMEOUT			(0x200)
#define MCU_ERR_IRQ			(PC_OVERFLOW | WDG_TIMEOUT)
#define DEFAULT_INT_MASK	(0x3FF)

#define MCU_DISABLE		0x0
#define MCU_ENABLE		0x01

#define TRIM_REF_VALUE			(0x42)
#define PROFILE_BLOCK_SIZE      (0x100)

#define MCU_CMD_HALT		(0x81)

#define MCU_CMD_GPU_OP_ON			(0x82)
#define MCU_CMD_GPU_OP_OFF		(0x83)
#define MCU_CMD_CPU_OP_ON			(0x84)
#define MCU_CMD_CPU_OP_OFF		(0x85)
#define MCU_CMD_DDR_OP_ON			(0x86)
#define MCU_CMD_DDR_OP_OFF		(0x87)

#define MCU_FUNC_CMD(obj, cmd) 	(((obj & IPPS_OBJ_CPU) ? 0x50 : ((obj & IPPS_OBJ_GPU) ? 0x58 : 0x60))  + ((cmd & IPPS_DVFS_AVS_ENABLE) >> 2))

#define MCU_CMD_CPU_PROFILE(n)		(0x10 + (n & 0x0f))
#define MCU_CMD_GPU_PROFILE(n)	(0x20 + (n & 0x07))
#define MCU_CMD_DDR_PROFILE(n)	(0x30 + (n & 0x07))
#define MCU_CMD_POLICY(n)		(0x40 + (n & 0x0f))
#define MCU_CMD_TEMP_ON		(0x71)
#define MCU_CMD_TEMP_OFF	(0x70)

enum mca_cmd_type {
	MCA_GET_FREQS_TABLE,
	MCA_GET_CUR_FREQ,
	MCA_SET_CUR_FREQ,
	MCA_GET_CUR_POLICY,
	MCA_SET_CUR_POLICY,
	MCA_GET_PARAM,
	MCA_SET_PARAM,
	MCA_GET_MODE,
	MCA_SET_MODE,
	MCA_GET_FUNC,
	MCA_SET_FUNC,
	MCA_GET_CUR_PROFILE,
	MCA_SET_CUR_PROFILE,
	MCA_CAPACITY_LIMIT,
};

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
	u32 dummy[(POLICY_EACH_FREQ_SIZE / 4) - 1];
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

#define readl_one(addr) \
({ u32 __v;   \
	unsigned long flags;  \
	spin_lock_irqsave(&mcureg_lock, flags);  \
	__v = readl(addr);  \
	spin_unlock_irqrestore(&mcureg_lock, flags);  \
	__v; })


#define writel_one(reg, addr) \
({ 	unsigned long flags;  \
	spin_lock_irqsave(&mcureg_lock, flags);  \
	writel((reg), (addr)); dsb(); \
	spin_unlock_irqrestore(&mcureg_lock, flags);})

#define CPU_INIT_PARAM_OFFSET	(0x10)
#define CPU_INIT_MAX_OFFSET		(0x11)
#define CPU_INIT_MAX1_OFFSET    (0x13)
#define GPU_INIT_PARAM_OFFSET	(0x14)
#define DDR_INIT_PARAM_OFFSET	(0x18)
#define TEMP_INIT_PARAM_OFFSET	(0x1C)
#define BUS_INIT_PARAM_OFFSET	(0x20)

#define CPU_RUNTIME_OFFSET	(0x100)
#define GPU_RUNTIME_OFFSET	(0x104)
#define DDR_RUNTIME_OFFSET	(0x108)
#define CUR_POLICY_OFFSET	(0x10C)

#define CPU_PARAM_OFFSET	(0x110)
#define CPU_MAX_OFFSET		(0x111)
#define CPU_MAX1_OFFSET		(0x113)
#define GPU_PARAM_OFFSET	(0x114)
#define DDR_PARAM_OFFSET	(0x118)
#define TEMP_PARAM_OFFSET	(0x11C)
#define BUS_PARAM_OFFSET	(0x120)

#define CPU_STATUS_OFFSET	(0x160)
#define GPU_STATUS_OFFSET	(0x164)
#define DDR_STATUS_OFFSET	(0x168)
#define TEMP_STATUS_OFFSET	(0x16C)
#define CPU_MODE_OFFSET	    (0x170)
#define GPU_MODE_OFFSET	    (0x174)
#define DDR_MODE_OFFSET	    (0x178)
#define TEMP_MODE_OFFSET	(0x17C)
#define CUR_CPU_PROFILE_OFFSET	(0x180)
#define CUR_GPU_PROFILE_OFFSET	(0x184)
#define CUR_DDR_PROFILE_OFFSET	(0x188)
#define HPM_VALUE_OFFSET	(0x206)
#define TRIM_VOLT_OFFSET	(0x207)
#define UPDATE_OFFSET		(0x900)

#define CPU_PROFILE_OFFSET	(0x1000)
#define CPU_PROFILE_TOTAL_SIZE	(0x1000)
#define GPU_PROFILE_OFFSET	(CPU_PROFILE_OFFSET + CPU_PROFILE_TOTAL_SIZE)
#define GPU_PROFILE_TOTAL_SIZE	(0x800)
#define DDR_PROFILE_OFFSET	(GPU_PROFILE_OFFSET + GPU_PROFILE_TOTAL_SIZE)
#define DDR_PROFILE_TOTAL_SIZE     (0x1000)
#define BUS_PROFILE_OFFSET	(DDR_PROFILE_OFFSET + DDR_PROFILE_TOTAL_SIZE)
#define BUS_PROFILE_TOTAL_SIZE	(0x800)

#define CPU_SPEC_PROFILE_OFFSET	(BUS_PROFILE_OFFSET + BUS_PROFILE_TOTAL_SIZE)
#define CPU_SPEC_PROFILE_SIZE   	(0x1000)
#define GPU_SPEC_PROFILE_OFFSET	(CPU_SPEC_PROFILE_OFFSET + CPU_SPEC_PROFILE_SIZE)
#define GPU_SPEC_PROFILE_SIZE 	       (0x1000)
#define DDR_SPEC_PROFILE_OFFSET	(GPU_SPEC_PROFILE_OFFSET + GPU_SPEC_PROFILE_SIZE)
#define DDR_SPEC_PROFILE_SIZE   	(0x1000)

#define RAM_REERVERD_SIZE 0x200
#define RAM_SIZE			(DDR_SPEC_PROFILE_OFFSET + DDR_SPEC_PROFILE_SIZE + RAM_REERVERD_SIZE)

int max_freq_array[] = {1200000,1399999,1400000,1500000,1508000,1200000};

struct ipps2 {
	void __iomem			*mmio;
	struct resource         *res;
	unsigned int			irq;
	struct clk				*clk;
	struct mutex			lock;
	struct completion		done;
	u8						shadow[RAM_SIZE];
	struct ipps_device		*idev;
};

struct cmd_proc {
	struct device *dev;
	enum ipps_cmd_type cmd;
	unsigned int object;
	void *data;
	int ret;
};

static unsigned int freq_to_index(struct ipps2 *ipps2, unsigned int offset, unsigned int freq)
{
	struct profile *p = (struct profile *)&(ipps2->shadow[offset]);
	unsigned int index = 0;

	while (p && p[index].freq != 0) {
		if (be16_to_cpu(p[index].freq)*1000 >= freq) break;
		index++;
	}

	if (index && p[index].freq == 0) index--;

    printk(KERN_INFO "freq:%d index:%d offset:0x%x\n", freq, index, offset);

	return index;
}

static unsigned int index_to_freq(struct ipps2 *ipps2, unsigned int offset, unsigned int index)
{
	struct profile *p = (struct profile *)&(ipps2->shadow[offset]);

	return be16_to_cpu(p[index].freq)*1000;
}

get_func_handle mca_get_func_handle[MCA_OBJ_NUM] = {
    [MCA_OBJ_CPU] = acpu_get_func_handle,
    [MCA_OBJ_GPU] = gpu_get_func_handle,
    [MCA_OBJ_DDR] = ddr_get_func_handle,
    [MCA_OBJ_BUS] = bus_get_func_handle,
};

set_func_handle mca_set_func_handle[MCA_OBJ_NUM] = {
    [MCA_OBJ_CPU] = acpu_set_func_handle,
    [MCA_OBJ_GPU] = gpu_set_func_handle,
    [MCA_OBJ_DDR] = ddr_set_func_handle,
    [MCA_OBJ_BUS] = bus_set_func_handle,
};

cur_profile_handle mca_cur_profile_handle[MCA_OBJ_NUM] = {
    [MCA_OBJ_CPU] = acpu_cur_profile_handle,
    [MCA_OBJ_GPU] = gpu_cur_profile_handle,
    [MCA_OBJ_DDR] = ddr_cur_profile_handle,
};

set_policy_handle mca_set_policy_handle[MCA_OBJ_NUM] = {
    [MCA_OBJ_CPU] = acpu_set_policy_handle,
    [MCA_OBJ_GPU] = gpu_set_policy_handle,
    [MCA_OBJ_DDR] = ddr_set_policy_handle,
};

set_profile_handle mca_set_profile_handle[MCA_OBJ_NUM] = {
    [MCA_OBJ_CPU] = acpu_set_profile_handle,
    [MCA_OBJ_GPU] = gpu_set_profile_handle,
    [MCA_OBJ_DDR] = ddr_set_profile_handle,
};

set_freq_handle mca_set_freq_handle[MCA_OBJ_NUM][MCA_PARAM_NUM] = {
    [MCA_OBJ_CPU] = {
        [MCA_PARAM_MAX] = acpu_maxfreq_handle,
        [MCA_PARAM_MIN] = acpu_minfreq_handle,
        [MCA_PARAM_LOCK] = acpu_lockfreq_handle,
        [MCA_PARAM_SAFE] = acpu_safefreq_handle,
    },
    [MCA_OBJ_GPU] = {
        [MCA_PARAM_MAX] = gpu_maxfreq_handle,
        [MCA_PARAM_MIN] = gpu_minfreq_handle,
        [MCA_PARAM_LOCK] = gpu_lockfreq_handle,
        [MCA_PARAM_SAFE] = gpu_safefreq_handle,
    },
    [MCA_OBJ_DDR] = {
        [MCA_PARAM_MAX] = ddr_maxfreq_handle,
        [MCA_PARAM_MIN] = ddr_minfreq_handle,
        [MCA_PARAM_LOCK] = ddr_lockfreq_handle,
        [MCA_PARAM_SAFE] = ddr_safefreq_handle,
    },
    [MCA_OBJ_BUS] = {
        [MCA_PARAM_MAX] = bus_maxfreq_handle,
        [MCA_PARAM_MIN] = bus_minfreq_handle,
        [MCA_PARAM_LOCK] = bus_lockfreq_handle,
        [MCA_PARAM_SAFE] = bus_safefreq_handle,
    },
};

int mcu_set_param_handle(struct ipps2 *ipps2, unsigned int object, unsigned int param_type, struct ipps_freq *ipps_freq);

bool is_vaild_profile(struct ipps2 *ipps2, unsigned int object, unsigned int profile_id)
{
	union param *param = NULL;
	bool ret = TRUE;
	
	if (object & IPPS_OBJ_CPU)
	{
		param = (union param *)&(ipps2->shadow[CPU_INIT_PARAM_OFFSET]);
	}
	else if (object & IPPS_OBJ_GPU)
	{
		param = (union param *)&(ipps2->shadow[GPU_INIT_PARAM_OFFSET]);
	}
	else if (object & IPPS_OBJ_DDR)
	{
		param = (union param *)&(ipps2->shadow[DDR_INIT_PARAM_OFFSET]);
	}

	if(profile_id > param->freq.max || profile_id < param->freq.min)
	{
		/*printk(KERN_ERR "%s obj:%d profile id(%d) invalid, valid rang %d~%d\n", __FUNCTION__, object, profile_id, param->freq.min, param->freq.max);*/
		ret = FALSE;
	}
	
	return ret;	
}

int mcu_command(struct ipps2 *ipps2, u8 cmd, unsigned int object, unsigned int cmd_type, void *data, unsigned int len)
{
	struct ipps_device *idev = ipps2->idev;
	int ret = 0;
	int i = 100;

    PRINT_PWC_DBG(PWC_SWITCH_DEBPT, "%s cmd:%d object:%d cmd_type:%d len:%d\n", __FUNCTION__,
        cmd, object, cmd_type, len);
    switch (cmd) {
		case MCA_GET_CUR_FREQ:
        {
   		    int profile_id;

		    ret = mca_cur_profile_handle[object](&profile_id);
		    if(ret != 0)
		    {
		        break;
		    }
			*(unsigned int *)data = profile_id;

			break;
        }
		case MCA_SET_CUR_FREQ:
			break;

		case MCA_GET_CUR_POLICY:
			break;

		case MCA_SET_CUR_POLICY:

            ret = mca_set_policy_handle[object](data, len);

			break;

        case MCA_GET_CUR_PROFILE:
			break;

		case MCA_SET_CUR_PROFILE:

            ret = mca_set_profile_handle[object](data, len);

			break;

		case MCA_GET_PARAM:
			break;

		case MCA_SET_PARAM:

		    ret = mca_set_freq_handle[object][cmd_type](*((int *)data));

			break;

		case MCA_GET_MODE:

			break;

		case MCA_SET_MODE:

			break;

		case MCA_GET_FUNC:
		{
		    int func;

		    ret = mca_get_func_handle[object](&func);
            if(ret != 0)
		    {
		        break;
		    }
			*(unsigned int *)data = func;

			break;
		}

		case MCA_SET_FUNC:
		{
		    int func;

            func = *(unsigned int *)data;
		    ret = mca_set_func_handle[object](func);
            if(ret != 0)
		    {
		        break;
		    }

			break;
		}
		case MCA_CAPACITY_LIMIT:
            break;
		default:
		    printk(KERN_NOTICE "%s unsupport cmd:%d\n", __FUNCTION__, cmd);
			break;
	}

   PRINT_PWC_DBG(PWC_SWITCH_DEBPT, "%s ret:%d\n", __FUNCTION__, ret);
	return ret;
}

static int mcu_cmd_proc(struct device *dev, enum ipps_cmd_type cmd, unsigned int object, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct ipps2 *ipps2 = platform_get_drvdata(pdev);
	int ret = 0;
	u8 mcu_cmd;
    
    PRINT_PWC_DBG(PWC_SWITCH_DEBPT,"%s cmd:%d object:%d\n", __FUNCTION__, cmd, object);
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
			}
			else if (object & IPPS_OBJ_GPU) {
				profile = (struct profile *)&(ipps2->shadow[GPU_PROFILE_OFFSET]);
				param = (union param *)&(ipps2->shadow[GPU_PARAM_OFFSET]);
			}
			else if (object & IPPS_OBJ_DDR) {
				profile = (struct profile *)&(ipps2->shadow[DDR_PROFILE_OFFSET]);
				param = (union param *)&(ipps2->shadow[DDR_PARAM_OFFSET]);
			}
			else if (object & IPPS_OBJ_BUS) {
				profile = (struct profile *)&(ipps2->shadow[BUS_PROFILE_OFFSET]);
				param = (union param *)&(ipps2->shadow[BUS_PARAM_OFFSET]);
			}

			while (profile && profile[index].freq != 0 && index <= param->freq.max) {
				table->index = index;
				table->frequency = be16_to_cpu(profile[index].freq)*1000;
				table++;
				index++;
			}
			table->index = index;
			table->frequency = CPUFREQ_TABLE_END;
			break;
		}

		case IPPS_GET_CUR_FREQ:
		{
		    int profile_id;
			
		    ret = mcu_command(ipps2, MCA_GET_CUR_FREQ, (object >> 1), 0, &profile_id, sizeof(int));

            if(ret != 0)
            {
                break;
            }

			if (object & IPPS_OBJ_CPU)
			{
				if(!is_vaild_profile(ipps2, object, profile_id))
				{
					*(unsigned int *)data = 0;
				}
				else
				{
					*(unsigned int *)data = index_to_freq(ipps2, CPU_PROFILE_OFFSET, profile_id);
				}	
			}
			else if (object & IPPS_OBJ_GPU)
			{
				if(!is_vaild_profile(ipps2, object, profile_id))
				{
					*(unsigned int *)data = 0;
				}
				else
				{
					*(unsigned int *)data = index_to_freq(ipps2, GPU_PROFILE_OFFSET, profile_id);
				}	
			}
			else if (object & IPPS_OBJ_DDR)
			{
				if(!is_vaild_profile(ipps2, object, profile_id))
				{
					*(unsigned int *)data = 0;
				}
				else
				{
					*(unsigned int *)data = index_to_freq(ipps2, DDR_PROFILE_OFFSET, profile_id);
				}	
			}
			break;
        }

		case IPPS_SET_CUR_FREQ:
		{
		#if 0
			if (object & IPPS_OBJ_CPU)
				mcu_cmd = MCU_CMD_CPU_PROFILE(freq_to_index(ipps2, CPU_PROFILE_OFFSET, *(unsigned int *)data));
			else if (object & IPPS_OBJ_GPU)
				mcu_cmd = MCU_CMD_GPU_PROFILE(freq_to_index(ipps2, GPU_PROFILE_OFFSET, *(unsigned int *)data));
			else if (object & IPPS_OBJ_DDR)
				mcu_cmd = MCU_CMD_DDR_PROFILE(freq_to_index(ipps2, DDR_PROFILE_OFFSET, *(unsigned int *)data));
        #endif
			break;
		}

		case IPPS_GET_CUR_POLICY:
			*(unsigned int *)data = (*(unsigned int *)&ipps2->shadow[CUR_POLICY_OFFSET]) & 0xFF;
			break;

		case IPPS_SET_CUR_POLICY:
		{
            struct profile *profile = NULL;
			union param *param = NULL;
			int index = 0;
			u32 policy_id;
            u8 *temp_buf;
            u8 *buf;
            u8 *buf_head;

            policy_id = *(u32*)data;

                     printk(KERN_INFO "set policy, policy id:%d\n", policy_id);
                     
			if (object & IPPS_OBJ_CPU) {
				profile = (struct profile *)&(ipps2->shadow[CPU_PROFILE_OFFSET]);
				param = (union param *)&(ipps2->shadow[CPU_INIT_PARAM_OFFSET]);
				object = MCA_OBJ_CPU;
			}
			else if (object & IPPS_OBJ_GPU) {
				profile = (struct profile *)&(ipps2->shadow[GPU_PROFILE_OFFSET]);
				param = (union param *)&(ipps2->shadow[GPU_INIT_PARAM_OFFSET]);
				object = MCA_OBJ_GPU;
			}
			else if (object & IPPS_OBJ_DDR) {
				profile = (struct profile *)&(ipps2->shadow[DDR_PROFILE_OFFSET]);
				param = (union param *)&(ipps2->shadow[DDR_INIT_PARAM_OFFSET]);
				object = MCA_OBJ_DDR;
			}

            buf = (u8 *)kmalloc(((param->freq.max + 1) * POLICY_LEN), GFP_KERNEL);

            if(NULL == buf)
            {
                printk(KERN_ERR "%s %d alloc mem failed!!!\n", __FUNCTION__, __LINE__);
                ret = -1;
                break;
            }

            buf_head = buf;
			while (profile && profile[index].freq != 0 && index <= param->freq.max) {
				temp_buf = (u8 *)&profile[index];
				temp_buf += (POLICY_HEAD_LEN + POLICY_LEN * policy_id);
				memcpy(buf, temp_buf, POLICY_LEN);

				buf += POLICY_LEN;
				index++;
			}

            ret = mcu_command(ipps2, MCA_SET_CUR_POLICY, object, 0, (void *)buf_head, ((param->freq.max + 1) * POLICY_LEN));

            if(ret != 0)
            {
                kfree(buf_head);
                break;
            }

			*(u32*)&ipps2->shadow[CUR_POLICY_OFFSET] = *(u32*)data;
			kfree(buf_head);
			break;
        }

        case IPPS_GET_CUR_PROFILE:
            if (object & IPPS_OBJ_CPU) {
				*(unsigned int *)data = (*(unsigned int *)&ipps2->shadow[CUR_CPU_PROFILE_OFFSET]) & 0xFF;
			}
			else if (object & IPPS_OBJ_GPU) {
				*(unsigned int *)data = (*(unsigned int *)&ipps2->shadow[CUR_GPU_PROFILE_OFFSET]) & 0xFF;
			}
			else if (object & IPPS_OBJ_DDR) {
				*(unsigned int *)data = (*(unsigned int *)&ipps2->shadow[CUR_DDR_PROFILE_OFFSET]) & 0xFF;
			}

			break;

		case IPPS_SET_CUR_PROFILE:
		{
            unsigned char *profile = NULL;
			union param *param = NULL;
			int offset = 0;
			u32 profile_id;
			u32 profile_size;


            profile_id = *(u32*)data;

			if (object & IPPS_OBJ_CPU) {
				profile = (unsigned char *)&(ipps2->shadow[CPU_SPEC_PROFILE_OFFSET]);
				param = (union param *)&(ipps2->shadow[CPU_INIT_PARAM_OFFSET]);
				offset = CUR_CPU_PROFILE_OFFSET;
				object = MCA_OBJ_CPU;
				profile_size = CPU_PROFILE_SIZE;
			}
			else if (object & IPPS_OBJ_GPU) {
				profile = (unsigned char *)&(ipps2->shadow[GPU_SPEC_PROFILE_OFFSET]);
				param = (union param *)&(ipps2->shadow[GPU_INIT_PARAM_OFFSET]);
				offset = CUR_GPU_PROFILE_OFFSET;
				object = MCA_OBJ_GPU;
				profile_size = GPU_PROFILE_SIZE;
			}
			else if (object & IPPS_OBJ_DDR) {
				profile = (unsigned char *)&(ipps2->shadow[DDR_SPEC_PROFILE_OFFSET]);
				param = (union param *)&(ipps2->shadow[DDR_INIT_PARAM_OFFSET]);
				offset = CUR_DDR_PROFILE_OFFSET;
				object = MCA_OBJ_DDR;
				profile_size = DDR_PROFILE_SIZE;
			}

            ret = mcu_command(ipps2, MCA_SET_CUR_PROFILE, object, 0, (void *)(profile + profile_id * profile_size), profile_size);

            if(ret != 0)
            {
                break;
            }

			*(u32*)&ipps2->shadow[offset] = *(u32*)data;
			break;
        }

		case IPPS_GET_PARAM:
		{
		    struct ipps_param_stru *param_stru = (struct ipps_param_stru *)data;
			struct ipps_param *param = param_stru->ipps_param;
			unsigned int param_type = param_stru->param_type;
			union param *p;

			if (object & IPPS_OBJ_CPU) {
			    p = (union param *)&(ipps2->shadow[CPU_PARAM_OFFSET]);
				param->cpu.min_freq = index_to_freq(ipps2, CPU_PROFILE_OFFSET, p->freq.min);
				param->cpu.max_freq = index_to_freq(ipps2, CPU_PROFILE_OFFSET, p->freq.max);
				param->cpu.safe_freq = index_to_freq(ipps2, CPU_PROFILE_OFFSET, p->freq.safe);
			}
			p++;
			if (object & IPPS_OBJ_GPU) {
			    p = (union param *)&(ipps2->shadow[GPU_PARAM_OFFSET]);
				param->gpu.min_freq = index_to_freq(ipps2, GPU_PROFILE_OFFSET, p->freq.min);
				param->gpu.max_freq = index_to_freq(ipps2, GPU_PROFILE_OFFSET, p->freq.max);
				param->gpu.safe_freq = index_to_freq(ipps2, GPU_PROFILE_OFFSET, p->freq.safe);
			}
			p++;
			if (object & IPPS_OBJ_DDR) {
			    p = (union param *)&(ipps2->shadow[DDR_PARAM_OFFSET]);
				param->ddr.min_freq = index_to_freq(ipps2, DDR_PROFILE_OFFSET, p->freq.min);
				param->ddr.max_freq = index_to_freq(ipps2, DDR_PROFILE_OFFSET, p->freq.max);
				param->ddr.safe_freq = index_to_freq(ipps2, DDR_PROFILE_OFFSET, p->freq.safe);
			}
			p++;
			if (object & IPPS_OBJ_BUS) {
			    p = (union param *)&(ipps2->shadow[BUS_PARAM_OFFSET]);
				param->bus.min_freq = index_to_freq(ipps2, BUS_PROFILE_OFFSET, p->freq.min);
				param->bus.max_freq = index_to_freq(ipps2, BUS_PROFILE_OFFSET, p->freq.max);
				param->bus.safe_freq = index_to_freq(ipps2, BUS_PROFILE_OFFSET, p->freq.safe);
			}
			p++;
			if (object & IPPS_OBJ_TEMP) {
				param->temp.safe = p->temp.safe * 200/255 - 40;
				param->temp.alarm= p->temp.alarm * 200/255 - 40;
				param->temp.reset = p->temp.reset * 200/255 - 40;
			}
			break;
		}

		case IPPS_SET_PARAM:
		{
			struct ipps_param_stru *param_stru = (struct ipps_param_stru *)data;
			struct ipps_param *param = param_stru->ipps_param;
			unsigned int param_type = param_stru->param_type;
            union param *p;

			if (object & IPPS_OBJ_CPU) {
                p = (union param *)&(ipps2->shadow[CPU_PARAM_OFFSET]);
			    ret = mcu_set_param_handle(ipps2, MCA_OBJ_CPU, param_type, &param->cpu);

                if(ret != 0)
                {
                    break;
                }

				p->freq.min = freq_to_index(ipps2, CPU_PROFILE_OFFSET, param->cpu.min_freq);
				p->freq.max = freq_to_index(ipps2, CPU_PROFILE_OFFSET, param->cpu.max_freq);
				p->freq.safe = freq_to_index(ipps2, CPU_PROFILE_OFFSET, param->cpu.safe_freq);
			}
			p++;
			if (object & IPPS_OBJ_GPU) {
                p = (union param *)&(ipps2->shadow[GPU_PARAM_OFFSET]);
			    ret = mcu_set_param_handle(ipps2, MCA_OBJ_GPU, param_type, &param->gpu);

                if(ret != 0)
                {
                    break;
                }

				p->freq.min = freq_to_index(ipps2, GPU_PROFILE_OFFSET, param->gpu.min_freq);
				p->freq.max = freq_to_index(ipps2, GPU_PROFILE_OFFSET, param->gpu.max_freq);
				p->freq.safe = freq_to_index(ipps2, GPU_PROFILE_OFFSET, param->gpu.safe_freq);
			}
			p++;
			if (object & IPPS_OBJ_DDR) {
                p = (union param *)&(ipps2->shadow[DDR_PARAM_OFFSET]);
                ret = mcu_set_param_handle(ipps2, MCA_OBJ_DDR, param_type, &param->ddr);

                if(ret != 0)
                {
                    break;
                }

				p->freq.min = freq_to_index(ipps2, DDR_PROFILE_OFFSET, param->ddr.min_freq);
				p->freq.max = freq_to_index(ipps2, DDR_PROFILE_OFFSET, param->ddr.max_freq);
				p->freq.safe = freq_to_index(ipps2, DDR_PROFILE_OFFSET, param->ddr.safe_freq);
			}
			p++;
			if (object & IPPS_OBJ_BUS) {
                p = (union param *)&(ipps2->shadow[BUS_PARAM_OFFSET]);
                ret = mcu_set_param_handle(ipps2, MCA_OBJ_BUS, param_type, &param->bus);

                if(ret != 0)
                {
                    break;
                }

				p->freq.min = freq_to_index(ipps2, BUS_PROFILE_OFFSET, param->bus.min_freq);
				p->freq.max = freq_to_index(ipps2, BUS_PROFILE_OFFSET, param->bus.max_freq);
				p->freq.safe = freq_to_index(ipps2, BUS_PROFILE_OFFSET, param->bus.safe_freq);
			}
			p++;
			if (object & IPPS_OBJ_TEMP) {
				p->temp.safe = (param->temp.safe + 40) / 200 * 255;
				p->temp.alarm = (param->temp.alarm + 40) / 200 * 255;
				p->temp.reset = (param->temp.reset + 40) / 200 * 255;
			}
			break;
		}

		case IPPS_GET_MODE:
		{
			if (object & IPPS_OBJ_CPU)
				*(unsigned int *)data = ipps2->shadow[CPU_MODE_OFFSET] & 0x01 ? IPPS_ENABLE : IPPS_DISABLE;
			else if (object & IPPS_OBJ_GPU)
				*(unsigned int *)data = ipps2->shadow[GPU_MODE_OFFSET] & 0x01 ? IPPS_ENABLE : IPPS_DISABLE;
			else if (object & IPPS_OBJ_DDR)
				*(unsigned int *)data = ipps2->shadow[DDR_MODE_OFFSET] & 0x01 ? IPPS_ENABLE : IPPS_DISABLE;
			else if (object & IPPS_OBJ_TEMP)
				*(unsigned int *)data = ipps2->shadow[TEMP_MODE_OFFSET] & 0x01 ? IPPS_ENABLE : IPPS_DISABLE;
			break;
		}

		case IPPS_SET_MODE:
		{
			if (object & IPPS_OBJ_CPU) {
				ipps2->shadow[CPU_MODE_OFFSET] = (*(unsigned int *)data == IPPS_ENABLE) ? MCU_CMD_CPU_OP_ON : MCU_CMD_CPU_OP_OFF;
			} else if (object & IPPS_OBJ_GPU) {
				ipps2->shadow[GPU_MODE_OFFSET] = (*(unsigned int *)data == IPPS_ENABLE) ? MCU_CMD_GPU_OP_ON : MCU_CMD_GPU_OP_OFF;
			} else if (object & IPPS_OBJ_DDR) {
				ipps2->shadow[DDR_MODE_OFFSET] = (*(unsigned int *)data == IPPS_ENABLE) ? MCU_CMD_DDR_OP_ON : MCU_CMD_DDR_OP_OFF;
			} else if (object & IPPS_OBJ_TEMP) {
				ipps2->shadow[TEMP_MODE_OFFSET] = (*(unsigned int *)data == IPPS_ENABLE) ? MCU_CMD_TEMP_ON : MCU_CMD_TEMP_OFF;
			}
			break;
		}

		case IPPS_GET_FUNC:
		{
		    unsigned int func = PWC_FUNC_INVALID;
            unsigned int temp_func = 0;

			if (object & IPPS_OBJ_DDR) {
				//*(unsigned int *)data = ipps2->shadow[DDR_STATUS_OFFSET] & IPPS_DFS_ENABLE;
                object = MCA_OBJ_DDR;
			} else if (object & IPPS_OBJ_CPU) {
				//*(unsigned int *)data = ipps2->shadow[CPU_STATUS_OFFSET] & IPPS_DVFS_AVS_ENABLE;
				object = MCA_OBJ_CPU;
			} else if (object & IPPS_OBJ_GPU) {
				//*(unsigned int *)data = ipps2->shadow[GPU_STATUS_OFFSET] & IPPS_DVFS_AVS_ENABLE;
				object = MCA_OBJ_GPU;
			}

            ret = mcu_command(ipps2, MCA_GET_FUNC, object, 0, &func, sizeof(unsigned int));

            if(ret != 0)
            {
                break;
            }

            if(func & PWC_FUNC_DFS_ENABLE)
            {
                temp_func |= IPPS_DFS_ENABLE;
            }

            if(func & PWC_FUNC_AVS_ENABLE)
            {
                temp_func |= IPPS_AVS_ENABLE;
            }

            if(func & PWC_FUNC_DVFS_DISABLE)
            {
                temp_func |= IPPS_DVFS_AVS_DISABLE;
            }

            *(unsigned int *)data = temp_func;

			break;
		}

		case IPPS_SET_FUNC:
		{
		    unsigned int func = PWC_FUNC_INVALID;
            unsigned int temp_func;
            temp_func = *(unsigned int *)data;

            if(temp_func & IPPS_DFS_ENABLE)
            {
                func = PWC_FUNC_DFS_ENABLE;
            }

            if(temp_func & IPPS_AVS_ENABLE)
            {
                if(PWC_FUNC_INVALID != func)
                    func |= PWC_FUNC_AVS_ENABLE;
                else
                    func = PWC_FUNC_AVS_ENABLE;
            }

            if(PWC_FUNC_INVALID == func)
            {
                if(temp_func != IPPS_DVFS_AVS_DISABLE)
                {
                    ret = -1;
                    break;
                }
                else
                {
                    func = PWC_FUNC_DVFS_DISABLE;
                }
            }

			if (object & IPPS_OBJ_CPU) {

			    ret = mcu_command(ipps2, MCA_SET_FUNC, MCA_OBJ_CPU, 0, &func, sizeof(unsigned int));

                if(ret != 0)
                {
                    break;
                }

				ipps2->shadow[CPU_STATUS_OFFSET] &= ~IPPS_DVFS_AVS_ENABLE;
				ipps2->shadow[CPU_STATUS_OFFSET] |= *(unsigned int *)data;
			} else if  (object & IPPS_OBJ_GPU) {

				ret = mcu_command(ipps2, MCA_SET_FUNC, MCA_OBJ_GPU, 0, &func, sizeof(unsigned int));

                if(ret != 0)
                {
                    break;
                }

				ipps2->shadow[GPU_STATUS_OFFSET] &= ~IPPS_DVFS_AVS_ENABLE;
				ipps2->shadow[GPU_STATUS_OFFSET] |= *(unsigned int *)data;
			} else if (object & IPPS_OBJ_DDR) {

				ret = mcu_command(ipps2, MCA_SET_FUNC, MCA_OBJ_DDR, 0, &func, sizeof(unsigned int));

                if(ret != 0)
                {
                    break;
                }

				ipps2->shadow[DDR_STATUS_OFFSET] &= ~IPPS_DFS_ENABLE;
				ipps2->shadow[DDR_STATUS_OFFSET] |= *(unsigned int *)data;
			}
			break;
		}

		case IPPS_CAPACITY_LIMIT:
		{
			int *param = (int *)data;
			union param *p = (union param *)&(ipps2->shadow[CPU_PARAM_OFFSET]);
			if (object & IPPS_OBJ_CPU) {
				if (*param == 1) {
					if (p->freq.max > 0x07 && p->freq.max1 == 0x08) {
						p->freq.max1 = p->freq.max + 1;
					}
				} else if (p->freq.max > 0x07 && p->freq.max1 != 0x08) {
					p->freq.max1 = 0x08;
				}
			}
		}

		default:
			break;
	}

	mutex_unlock(&ipps2->lock);
	PRINT_PWC_DBG(PWC_SWITCH_DEBPT, "%s ret:%d\n", __FUNCTION__, ret);
	return ret;
}

static void mcu_enable(struct ipps2 *ipps2)
{
	struct ipps_device *idev = ipps2->idev;

	mutex_lock(&ipps2->lock);

    /*mca_init();*/
	idev->command = mcu_cmd_proc;

	mutex_unlock(&ipps2->lock);
}

static void mcu_disable(struct ipps2 *ipps2)
{
	struct ipps_device *idev = ipps2->idev;

	mutex_lock(&ipps2->lock);

	idev->command = NULL;

	mutex_unlock(&ipps2->lock);
}

int mcu_set_param_handle(struct ipps2 *ipps2, unsigned int object, unsigned int param_type, struct ipps_freq *ipps_freq)
{
    unsigned int freq = 0;
    unsigned int mca_param_type;
    int ret;

    printk(KERN_INFO "object:0x%x param_type:0x%x\n", object, param_type);
    printk(KERN_INFO "max:%d min:%d block:%d\n", ipps_freq->max_freq, ipps_freq->min_freq, ipps_freq->block_freq);
    if(IPPS_PARAM_MAX == param_type) {
        freq = ipps_freq->max_freq;
        mca_param_type = MCA_PARAM_MAX;
    }else if(IPPS_PARAM_MIN == param_type) {
        freq = ipps_freq->min_freq;
        mca_param_type = MCA_PARAM_MIN;
    }else if(IPPS_PARAM_LOCK == param_type) {
        printk(KERN_INFO "param_type is IPPS_PARAM_LOCK\n");
        if(ipps_freq->block_freq != UNLOCK_FREQ) {
            if (MCA_OBJ_CPU == object) {
                freq = freq_to_index(ipps2, CPU_PROFILE_OFFSET, ipps_freq->block_freq);
            } else if (MCA_OBJ_GPU == object) {
                freq = freq_to_index(ipps2, GPU_PROFILE_OFFSET, ipps_freq->block_freq);
            } else if (MCA_OBJ_DDR == object) {
                freq = freq_to_index(ipps2, DDR_PROFILE_OFFSET, ipps_freq->block_freq);
            }
        } else {
            freq = UNLOCK_PROFILE;
        }
        mca_param_type = MCA_PARAM_LOCK;
    }else if(IPPS_PARAM_SAFE == param_type) {
        freq = ipps_freq->safe_freq;
        mca_param_type = MCA_PARAM_SAFE;
    }

	ret = mcu_command(ipps2, MCA_SET_PARAM, object, mca_param_type, &freq, sizeof(unsigned int));

    return ret;
}

extern void __iomem *gic_cpu_base_addr;

static irqreturn_t mcu_irq(int irq, void *args)
{
#if 0
	struct ipps2 *ipps2 = (struct ipps2 *)args;
	struct ipps_device *idev = ipps2->idev;
	unsigned int state;

	state = readl_one(ipps2->mmio + INT_STAT_OFFSET);
	writel_one(0, ipps2->mmio + INT_STAT_OFFSET);
	writel(0x0000000F, IO_ADDRESS(REG_BASE_PCTRL) + 0x174); /* Clear HW resource lock */
	if (state & MCU_ERR_IRQ) {
		dev_err(idev->dev,"%s%s"
			"mcu dump: [cfg]0x%04X, [int]0x%04X, [intmask]0x%04X, [dbg]0x%04X\n",
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

		/*writel(MCU_DISABLE, ipps2->mmio + CFG_OFFSET);
		writel(0, ipps2->mmio + INT_STAT_OFFSET);
		writel(MCU_ENABLE, ipps2->mmio + CFG_OFFSET);*/

	} else {
		int irqflage = 0;
		int cpu_num = 0;
		register int flage;
		int cpu;
		int i;
		register unsigned long sctl_addr;
		int timeout = 1000;
		unsigned long sec_core_addr;

		if ((state & 0xff) == 0x80) {
			for ( i = 0; i < CONFIG_NR_CPUS; i++) {
				writel(0, REG_BASE_SECRAM_VIRT + REG_SECRAM_IOSIZE - 0x100 - (i << 2));
			}

			/* set states to tell secondary core in deep sleep. */
			sec_core_addr = REG_BASE_SECRAM_VIRT + REG_SECRAM_IOSIZE - 0xF0;
			writel(0x23FE, sec_core_addr);

			/* mcu */
			for_each_cpu((cpu), cpu_active_mask) {
				if (cpu == 0)
					continue;

				if (cpu_active(cpu))
					gic_raise_softirq(cpumask_of(cpu), 8);
			}

			// disable gic cpu ctrl
			writel_relaxed(0, gic_cpu_base_addr);
			dsb();

			do {
				cpu_num = 0;
				irqflage = 0;
				flage = 0;
				/* FIXME: This should be done in userspace --RR */
				for_each_cpu((cpu), cpu_active_mask) {
					cpu_num ++;
					if (cpu == 0)
						continue;

					if (cpu_active(cpu)) {
						flage = readl(REG_BASE_SECRAM_VIRT + REG_SECRAM_IOSIZE - 0x100 - (cpu << 2));
						if (flage == 0xdead) {
							irqflage |= 1 << cpu;
						}
					}
				}
				flage = 0;
				for ( i = 1; i < cpu_num; i++) {
					flage |= 1 << i;
				}
				if(flage == irqflage){
					break;
				}
				else {
					udelay(10);
					timeout--;
				}
			} while((flage != irqflage) && timeout > 0);

			sctl_addr = IO_ADDRESS(REG_BASE_SCTRL) + 0x318;
			if(timeout > 0) {

			__asm__ __volatile__(
				"PLI		[pc, #0]\n"
				"PLI		[pc, #28]\n"
				"PLI		[pc, #56]\n"
			);

				writel(2, sctl_addr);

				dsb();
				do {
					flage = readl_relaxed(sctl_addr);
					if(flage) {
						wfe();
					}
				} while(flage);
			} else {
				dev_warn(idev->dev,"WARN: CPU BUSY! cpu num[%d], flag[0x%x] irqflag[0x%x]\n",
							cpu_num, flage, irqflage);
				writel(4, sctl_addr);
			}

			/* tell secondary cores out wfe. */
			writel(0, sec_core_addr);

			// enable gic cpu ctrl
			writel_relaxed(1, gic_cpu_base_addr);
			dsb();
			sev();

		} else if (state & 0x80) {
			complete(&ipps2->done);
		}
		else {
			dev_warn(idev->dev,"MCU send undefine irq [%x]\n",state);
		}
	}
#endif
	return IRQ_HANDLED;
}

extern int get_hpm_vol_val(void);

static void trim_patch(struct ipps2 *ipps2, int hpm_value)
{
	int offset,i = 0;
	struct cpu_profile *p;
	offset = hpm_value - TRIM_REF_VALUE;

	if (offset > 0) {
		offset++;
		if(offset > 8) {
			offset = 8;
		}
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

extern int get_cpu_max_freq(void);

void profile_adjust(struct ipps2 *ipps2, int param_type, int freq_num)
{
    union param *p;
#if 0
	int max_freq,index,index_freq;
	unsigned int cpu_level, cpu_iddq, efuse_version, date, update_level;
	unsigned long efuse0, efuse2, efuse3;
	union param *p;

#ifdef  CONFIG_CPU_MAX_FREQ
	max_freq = CONFIG_CPU_MAX_FREQ;
#else
	efuse0 = readl(IO_ADDRESS(REG_BASE_PCTRL)+0x1DC);
	efuse_version = (efuse0 >> 29) & 0x07;

	max_freq = 1200000;
	if (efuse_version == 1) {
		efuse2 = readl(IO_ADDRESS(REG_BASE_PCTRL)+0x1D4);
		efuse3 = readl(IO_ADDRESS(REG_BASE_PCTRL)+0x1D0);

		cpu_level = (efuse0 >> 18) & 0x3F;
		cpu_iddq = ((efuse2 & 0x01) << 7) | (efuse3 >> 25);
		date = (efuse2 >> 17) & 0x1FFF;
		dev_info(ipps2->idev->dev, "efuse info:%d,%d,%d,%d\n", efuse_version, cpu_level, cpu_iddq, date);
		if (date > 0x1952) {   /* date 2012-10-18, after is B40, before is B30*/
			if ((cpu_level == 8) && (cpu_iddq <= 40)) {
				max_freq = max_freq_array[4];//1508000;
			} else if ((cpu_level == 7) && (cpu_iddq <= 40)) {
				max_freq = max_freq_array[3];//1500000;
			} else if ((cpu_level >= 3) && (cpu_level <= 8) && (cpu_iddq <= 50)) {
				max_freq = max_freq_array[1];//1400000 - 1;
			} else {
				max_freq = max_freq_array[0];//1200000;
			}
		} else {
			if ((cpu_level >= 5) && (cpu_level <= 7) && (cpu_iddq <= 35)) {
				max_freq = max_freq_array[2];//1400000;	/* 1400+ */
			} else if ((cpu_iddq <= 40) && (cpu_level >= 3) && (cpu_level <= 7)) {
				max_freq = max_freq_array[1];//1400000 - 1;
			} else {
				max_freq = max_freq_array[0];//1200000;
			}
		}
	} else if (efuse_version >= 2) {
		cpu_level = (efuse0 >> 22) & 0x0F;
		update_level = (efuse0 >> 26) & 0x07;
		dev_info(ipps2->idev->dev, "efuse info:%d,%d,%d\n", efuse_version, cpu_level, update_level);
		if (update_level > 2) {
			index = cpu_level - (update_level - 2);
		} else {
			index = cpu_level + update_level;
		}
		index--;
		if (index < 0) {
			index = 0;
		}
		if (index > (ARRAY_SIZE(max_freq_array) - 1)) {
			index = ARRAY_SIZE(max_freq_array) - 1;
		}
		max_freq = max_freq_array[index];
	} else {
		max_freq = get_cpu_max_freq();
		if (max_freq == 1400) {
			max_freq = 1400000 - 1;
			dev_info(ipps2->idev->dev, "set max cpufreq 1.4G according to NV\n");
		}
		else {
			max_freq = 1200000; /* Default 1200M */
			dev_info(ipps2->idev->dev, "set max cpufreq 1.2G according to NV\n");
		}
	}
#endif
#endif
#if 0
	index = freq_to_index(ipps2, CPU_PROFILE_OFFSET, max_freq);
	index_freq = index_to_freq(ipps2,CPU_PROFILE_OFFSET,index);
#endif
	p = (union param *)&(ipps2->shadow[param_type]);
	p->freq.max = p->freq.max1 = (freq_num - 1);
	p->freq.min = p->freq.safe = 0;
	printk("\ntype:0x%x max:%d min:%d\n", param_type, p->freq.max, p->freq.min);
#if 0
	if(max_freq >= index_freq) {
		p->freq.max = index;
		p->freq.max1 = index + 1;
	} else {
		p->freq.max = index;
		p->freq.max1 = index;
	}


#ifdef  CONFIG_TRIM_VOL
	trim_patch(ipps2, get_hpm_vol_val());
#endif
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

	idev = ipps_alloc_device(sizeof(struct ipps_device));
	if (NULL == idev) {
		dev_err(dev, "cannot alloc idev memory\n");
		return;
	}

	idev->dev = dev;

	ipps2->idev = idev;

	memset((void *)ipps2->shadow, 0x0, RAM_SIZE);

	/*memcpy((void *)ipps2->shadow+CPU_RUNTIME_OFFSET, (void *)common, sizeof(common));*/
	memcpy((void *)ipps2->shadow+CPU_PROFILE_OFFSET, (void *)cpu_profile, sizeof(cpu_profile));
	memcpy((void *)ipps2->shadow+GPU_PROFILE_OFFSET, (void *)gpu_profile, sizeof(gpu_profile));
	memcpy((void *)ipps2->shadow+DDR_PROFILE_OFFSET, (void *)ddr_profile, sizeof(ddr_profile));
	profile_adjust(ipps2, CPU_PARAM_OFFSET, (sizeof(cpu_profile) / sizeof(struct cpu_profile)));

    idev->object = IPPS_OBJ_CPU | IPPS_OBJ_GPU | IPPS_OBJ_DDR | IPPS_OBJ_TEMP;

	mcu_enable(ipps2);

	ret = ipps_register_device(idev);
	if (ret) {
		dev_err(dev, "cannot register ipps device\n");
		return;
	}

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
    struct ipps_device *idev;
	int ret = -ENOMEM;

	/* stop no dev release warning */
	dev->release = ipps2_release;

    dev_err(dev, "ipps2_probe...\n");

	ipps2 = (struct ipps2 *)kzalloc(sizeof(struct ipps2), GFP_KERNEL);
	if (!ipps2) {
		dev_err(dev, "cannot get memory\n");
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, ipps2);

	mutex_init(&ipps2->lock);

	idev = ipps_alloc_device(sizeof(struct ipps_device));
	if (NULL == idev) {
		dev_err(dev, "cannot alloc idev memory\n");
		goto exit;
	}

	idev->dev = dev;
	ipps2->idev = idev;

       if((sizeof(cpu_profile) > CPU_PROFILE_TOTAL_SIZE) || (sizeof(gpu_profile) > GPU_PROFILE_TOTAL_SIZE) || \
            (sizeof(ddr_profile) > DDR_PROFILE_TOTAL_SIZE) || (sizeof(bus_profile) > BUS_PROFILE_TOTAL_SIZE) || \
            (sizeof(cpu_profile_all) > CPU_SPEC_PROFILE_SIZE) || (sizeof(gpu_profile_all) > GPU_SPEC_PROFILE_SIZE) || \
            (sizeof(ddr_profile_all) > DDR_SPEC_PROFILE_SIZE))
       {
            dev_err(dev, "error mem size exceed!!!\n");
            goto exit;
       }
       
	memset((void *)ipps2->shadow, 0xA5, RAM_SIZE);
	memcpy((void *)ipps2->shadow+CPU_PROFILE_OFFSET, (void *)cpu_profile, sizeof(cpu_profile));
	memcpy((void *)ipps2->shadow+GPU_PROFILE_OFFSET, (void *)gpu_profile, sizeof(gpu_profile));
	memcpy((void *)ipps2->shadow+DDR_PROFILE_OFFSET, (void *)ddr_profile, sizeof(ddr_profile));
	memcpy((void *)ipps2->shadow+BUS_PROFILE_OFFSET, (void *)bus_profile, sizeof(bus_profile));
	memcpy((void *)ipps2->shadow+CPU_SPEC_PROFILE_OFFSET, (void *)cpu_profile_all, sizeof(cpu_profile_all));
	memcpy((void *)ipps2->shadow+GPU_SPEC_PROFILE_OFFSET, (void *)gpu_profile_all, sizeof(gpu_profile_all));
	memcpy((void *)ipps2->shadow+DDR_SPEC_PROFILE_OFFSET, (void *)ddr_profile_all, sizeof(ddr_profile_all));
       memset((void *)ipps2->shadow+CUR_CPU_PROFILE_OFFSET, 0x0, sizeof(unsigned int));
	memset((void *)ipps2->shadow+CUR_GPU_PROFILE_OFFSET, 0x0, sizeof(unsigned int));
	memset((void *)ipps2->shadow+CUR_DDR_PROFILE_OFFSET, 0x0, sizeof(unsigned int));
	profile_adjust(ipps2, CPU_INIT_PARAM_OFFSET, (sizeof(cpu_profile) / sizeof(cpu_profile[0])));
	profile_adjust(ipps2, DDR_INIT_PARAM_OFFSET, (sizeof(ddr_profile) / sizeof(ddr_profile[0])));
	profile_adjust(ipps2, GPU_INIT_PARAM_OFFSET, (sizeof(gpu_profile) / sizeof(gpu_profile[0])));
	profile_adjust(ipps2, BUS_INIT_PARAM_OFFSET, (sizeof(bus_profile) / sizeof(bus_profile[0])));
	profile_adjust(ipps2, CPU_PARAM_OFFSET, (sizeof(cpu_profile) / sizeof(cpu_profile[0])));
	profile_adjust(ipps2, DDR_PARAM_OFFSET, (sizeof(ddr_profile) / sizeof(ddr_profile[0])));
	profile_adjust(ipps2, GPU_PARAM_OFFSET, (sizeof(gpu_profile) / sizeof(gpu_profile[0])));
	profile_adjust(ipps2, BUS_PARAM_OFFSET, (sizeof(bus_profile) / sizeof(bus_profile[0])));

       idev->object = IPPS_OBJ_CPU | IPPS_OBJ_GPU | IPPS_OBJ_DDR | IPPS_OBJ_TEMP | IPPS_OBJ_BUS;

	mcu_enable(ipps2);

	ret = ipps_register_device(idev);
	if (ret) {
		dev_err(dev, "cannot register ipps device\n");
		goto exit;
	}

	return 0;

exit:
    dev_err(dev, "ipps_probe failed. error code:0x%x\n", ret);
	return ret;
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

	kfree(ipps2);

	return 0;
}


#ifdef CONFIG_PM_SLEEP
static int ipps2_suspend(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct ipps2 *ipps2 = platform_get_drvdata(pdev);
	struct ipps_device *idev = ipps2->idev;
	printk(KERN_INFO "ipps2_suspend+");
	if(idev && idev->command)
		mcu_disable(ipps2);
	printk(KERN_INFO "ipps2_suspend-");

	return 0;
}

static int ipps2_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct ipps2 *ipps2 = platform_get_drvdata(pdev);
	struct ipps_device *idev = ipps2->idev;

	printk(KERN_INFO "ipps2_resume+");
	if(idev && NULL == idev->command)
		mcu_enable(ipps2);
	extern void acpu_pm_test();	
       acpu_pm_test();	
	printk(KERN_INFO "ipps2_resume-");

	return 0;
}
static SIMPLE_DEV_PM_OPS(ipps2_pm_ops, ipps2_suspend, ipps2_resume);
#endif

static struct platform_driver ipps2_driver = {
	.probe		= ipps2_probe,
	.remove		= __devexit_p(ipps2_remove),
	.driver = {
		.name = MODULE_NAME,
		.owner = THIS_MODULE,
#ifdef CONFIG_PM_SLEEP
		.pm	= &ipps2_pm_ops,
#endif
		.shutdown = (void(*)(struct device *dev))(ipps2_suspend),
	},
};

static struct resource ipps2_resources[] = {
	{
		.start = 0,
		.end = 0,
		.flags = IORESOURCE_MEM,
	},
};

static struct platform_device ipps2_device = {
	.id = 0,
	.name = "ipps-v2",
	.resource = ipps2_resources,
	.num_resources = ARRAY_SIZE(ipps2_resources),
};

extern int trial_version;
static int __init ipps2_init(void)
{
    int ret;

    if (trial_version)
        return 0;

    ret = platform_driver_register(&ipps2_driver);

    if (ret) {
		pr_err("%s: platform_device_register failed, ret:%d.\n",
			__func__, ret);
		return ret;
	}

	ret = platform_device_register(&ipps2_device);
	if (ret) {
		pr_err("%s: platform_device_register failed, ret:%d.\n",
			__func__, ret);
        platform_driver_unregister(&ipps2_driver);
		return ret;
	}

	return ret;
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
