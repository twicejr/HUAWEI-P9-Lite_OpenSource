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

#include <securec.h>
#include <mdrv_memory.h>
#include <osl_generic.h>
#include <osl_spinlock.h>
#include <osl_module.h>
#include <bsp_nvim.h>
#include <bsp_ipc.h>
#include <bsp_hardtimer.h>
#include <bsp_modem_log.h>
#include <bsp_pm_om.h>
#include "pm_om_platform.h"
#include "pm_om_debug.h"

struct pm_om_ctrl g_pmom_ctrl;
u32 g_pm_om_magic_tbl[PM_OM_MOD_ID_MAX]={
	PM_OM_MAGIC_PMA ,
	PM_OM_MAGIC_PMC ,
	PM_OM_MAGIC_PMM ,
	PM_OM_MAGIC_DPM ,
	PM_OM_MAGIC_ABB ,
	PM_OM_MAGIC_BBP ,
	PM_OM_MAGIC_DSP ,
	PM_OM_MAGIC_PMU ,
	PM_OM_MAGIC_WAKE,
	PM_OM_MAGIC_CPUF,
	PM_OM_MAGIC_CCLK,
	PM_OM_MAGIC_REGU,
	PM_OM_MAGIC_ACLK,
	PM_OM_MAGIC_AIPC,
	PM_OM_MAGIC_CIPC,
	PM_OM_MAGIC_AIPF,
	PM_OM_MAGIC_CIPF,
	PM_OM_MAGIC_AOSA,
	PM_OM_MAGIC_COSA,
	PM_OM_MAGIC_CMSP,
	PM_OM_MAGIC_NVA,
	PM_OM_MAGIC_NVC,
	PM_OM_MAGIC_ADPPOWER,
	PM_OM_MAGIC_AICC,
	PM_OM_MAGIC_CICC,
	PM_OM_MAGIC_ARFILE,
	PM_OM_MAGIC_PMLG,
	PM_OM_MAGIC_TCXO
};
u32 ring_buffer_in(struct ring_buffer *rb, void *data, u32 len)
{
	/* 首先拷贝 rb->write到buffer末尾的一段数据 */
	u32 left = min(len,  rb->size - rb->write);
	(void)memcpy_s((void *)(rb->buf + rb->write), rb->size, (void *)data, left);/*lint !e124 */

	/* 接着将剩余待写入数据 (如果还有的话)从buffer的开始位置拷贝 */
	(void)memcpy_s((void *)rb->buf, rb->size, (void *)(data + left), len - left);/*lint !e124 */

	rb->write += len;
	rb->write %= (rb->size);

	return len;
}

u32 ring_buffer_in_with_header(
	struct ring_buffer *rb,
	void *head,
	u32 head_len,
	void *data,
	u32 data_len)
{
	u32 len = 0;

	len  = ring_buffer_in(rb, head, head_len);
	len += ring_buffer_in(rb, data, data_len);
	return len;
}

int pm_om_log_out(u32 mod_id, u32 typeid, u32 data_len , void *data)
{
	struct pm_om_log_header log_head;
	u32  head_len  = sizeof(log_head);
	u32  left_size = 0;
	int  ret       = PM_OM_OK;
	unsigned long flags = 0;
	u32  consuming_time = 0;
	UNUSED(flags);

	/* 记录log过长会影响DRX寻呼(栈上变量) */
	if (data_len > PM_OM_LOG_MAX_LEN)
	{
		return PM_OM_ERR_LEN_LIMIT;
	}

	if (g_pmom_ctrl.log.init_flag != PM_OM_INIT_MAGIC)
	{
		return PM_OM_ERR_INIT;
	}

	if (pm_om_log_mod_is_off(g_pmom_ctrl.log.smem->nv_cfg.mod_sw_bitmap, mod_id))
	{
		return PM_OM_ERR_MOD_OFF;
	}

	/* 操作ring buffer之前, 先将核间指针取到本核 */
	g_pmom_ctrl.log.rb.write     = g_pmom_ctrl.log.smem->mem_info.write;
	g_pmom_ctrl.log.rb.read      = g_pmom_ctrl.log.smem->mem_info.read;

	log_head.typeid    = typeid;
	log_head.length    = data_len;
	log_head.timestamp = bsp_get_slice_value();
	log_head.magic     = g_pm_om_magic_tbl[mod_id];

	pm_om_spin_lock(&g_pmom_ctrl.log.lock, flags);
	log_head.sn        = (g_pmom_ctrl.log.smem->sn)++;

	/* 出现log覆盖: 抛弃新数据 */
	left_size = bsp_ring_buffer_writable_size(&g_pmom_ctrl.log.rb);
	if ((head_len + data_len) > left_size)
	{
		g_pmom_ctrl.log.buf_is_full = 1;
		goto out;
	}
	else
	{
		g_pmom_ctrl.log.buf_is_full = 0;
	}

	(void)ring_buffer_in_with_header(&g_pmom_ctrl.log.rb, (void *)&log_head, head_len, data, data_len);

	/* 数据写入之后更新核间ring buffer 写指针 */
	g_pmom_ctrl.log.smem->mem_info.write = g_pmom_ctrl.log.rb.write;
	cache_sync();
	
out:
	consuming_time = pm_om_log_time_rec(log_head.timestamp);

	/* bsp_ipc_spin_unlock可保证调用cache_sync冲出write buffer */
	pm_om_spin_unlock((&g_pmom_ctrl.log.lock), flags);

	/* 写入数据超过log水线,唤醒acore写文件 */
	if (bsp_ring_buffer_readable_size(&g_pmom_ctrl.log.rb) >= g_pmom_ctrl.log.threshold && !g_pmom_ctrl.log.buf_is_full)
	{
		(void)pm_om_fwrite_trigger();
	}

	pm_om_log_time_print(consuming_time);
	return ret;
}

struct pm_om_ctrl *pm_om_ctrl_get(void)
{
	return &g_pmom_ctrl;
}

int bsp_pm_log(u32 mod_id, u32 data_len , void *data)
{
	return pm_om_log_out(mod_id, 0, data_len, data);
}

int bsp_pm_log_type(u32 mod_id, u32 type, u32 data_len , void *data)
{
	return pm_om_log_out(mod_id, type, data_len, data);
}

void *bsp_pm_log_addr_get(void)
{
	if (g_pmom_ctrl.log.init_flag != PM_OM_INIT_MAGIC)
	{
		pmom_pr_err("pm om not init\n");
		return NULL;
	}
	return (void *)g_pmom_ctrl.log.rb.buf;
}

void *bsp_pm_dump_get(u32 mod_id, u32 len)
{
	struct pm_om_head_entry *entry = NULL;
	void *dump_area = NULL;
	u32 reg_cnt = g_pmom_ctrl.dump.region_cnt;
	u32 i = 0;
	char *name = (char *)&(g_pm_om_magic_tbl[mod_id]);
	unsigned long flags = 0;
	UNUSED(flags);

	len = OSL_ROUND_UP(len, 4);
	pmom_pr_debug("[%c%c%c%c]=len\n", name[0], name[1], name[2], name[3], len);

	if (g_pmom_ctrl.dump.init_flag != PM_OM_INIT_MAGIC)
	{
		pmom_pr_err("not init\n");
		return NULL;
	}

	entry = g_pmom_ctrl.dump.cfg? g_pmom_ctrl.dump.cfg->entry_tbl: NULL;
	if (NULL == entry)
	{
		pmom_pr_err("no dump memory\n");
		return NULL;
	}

	for (i = 0; i < reg_cnt; i++)
	{
		if (g_pm_om_magic_tbl[mod_id] == entry[i].magic)
		{
			return (void *)entry[i].offset;
		}
	}

	if (len + (u32)(g_pmom_ctrl.dump.sub_region - g_pmom_ctrl.dump.base) > PM_OM_DUMP_SIZE)
	{
		pmom_pr_err("dump exhaust\n");
		return NULL;
	}

	if (reg_cnt >= PM_OM_MOD_ID_MAX)
	{
		pmom_pr_err("num(%d)>max(%d)", reg_cnt, PM_OM_MOD_ID_MAX);
		return NULL;
	}

	spin_lock_irqsave(&g_pmom_ctrl.dump.lock, flags);

	entry[reg_cnt].magic  = g_pm_om_magic_tbl[mod_id]; /*lint !e661 !e662 */
	entry[reg_cnt].len    = len;                      /*lint !e661 !e662 */
	entry[reg_cnt].offset = (long)g_pmom_ctrl.dump.sub_region; /*lint !e661 !e662 */

	dump_area = (void *)g_pmom_ctrl.dump.sub_region;
	g_pmom_ctrl.dump.sub_region += len;
	g_pmom_ctrl.dump.region_cnt++;

	spin_unlock_irqrestore(&g_pmom_ctrl.dump.lock, flags);

	return dump_area;
}

int bsp_pm_om_log_init(void)
{
	DRV_PM_OM_CFG_STRU nv_cfg;
	unsigned long flags = 0;
	BSP_DDR_SECT_QUERY_S socp_sect_query;
	BSP_DDR_SECT_INFO_S socp_sect_info = {BSP_DDR_SECT_TYPE_SOCP, };
	struct pm_om_platform *platform = NULL;
	UNUSED(flags);

	(void)memset_s((void *)&nv_cfg, sizeof(nv_cfg), 0, sizeof(nv_cfg));
	(void)memset_s((void *)&g_pmom_ctrl.log, sizeof(g_pmom_ctrl.log), 0, sizeof(g_pmom_ctrl.log));

	/* 当前debug和platform主要和log强相关, dump比较独立 */
	g_pmom_ctrl.platform = NULL;
	g_pmom_ctrl.debug = NULL;

	spin_lock_init(&g_pmom_ctrl.log.lock);

	if(NV_OK != bsp_nvm_read(NV_ID_DRV_PM_OM, (u8*)&(nv_cfg), sizeof(nv_cfg)))
	{
		pmom_pr_err("nv[0x%x] read fail\n", NV_ID_DRV_PM_OM);
	}

	g_pmom_ctrl.log.smem = (struct pm_om_smem_cfg *)PM_OM_LOG_AREA;
	if (PM_OM_USE_NORMAL_DDR == nv_cfg.mem_ctrl && PM_OM_PROT_MAGIC2 == g_pmom_ctrl.log.smem->file_head.reserved)
	{
		/* 使用socp的1M往后的内存 */
		socp_sect_query.enSectType = BSP_DDR_SECT_TYPE_SOCP;
		(void)mdrv_get_fix_ddr_addr(&socp_sect_query, &socp_sect_info);
		g_pmom_ctrl.log.smem = (struct pm_om_smem_cfg *)((unsigned long)socp_sect_info.pSectVirtAddr + PM_OM_SOCP_OFFSET);
	}

	g_pmom_ctrl.log.rb.buf       = (char *)((long)g_pmom_ctrl.log.smem + (long)sizeof(struct pm_om_smem_cfg));
	g_pmom_ctrl.log.rb.size      = g_pmom_ctrl.log.smem->mem_info.size;
	g_pmom_ctrl.log.rb.read      = 0;
	g_pmom_ctrl.log.rb.write     = 0;
	g_pmom_ctrl.log.threshold    = (g_pmom_ctrl.log.smem->nv_cfg.log_threshold[PM_OM_CPUID] * g_pmom_ctrl.log.rb.size)/100;

	(void)pm_om_platform_init();
	platform = (struct pm_om_platform *)g_pmom_ctrl.platform;

	(void)pm_om_debug_init();

	if (g_pmom_ctrl.log.smem->nv_cfg.mod_sw_bitmap)
	{
		if (PM_OM_PROT_MAGIC1 == g_pmom_ctrl.log.smem->mem_info.magic)
		{
			pm_om_spin_lock(&g_pmom_ctrl.log.lock, flags);
			g_pmom_ctrl.log.smem->mem_info.magic = PM_OM_PROT_MAGIC2;
			pm_om_spin_unlock(&g_pmom_ctrl.log.lock, flags);
			if (platform)
			{
				platform->log_info.mem_is_ok = 1; /*[false alarm]*/
			}
			g_pmom_ctrl.log.init_flag = PM_OM_INIT_MAGIC;
		}
		else if (PM_OM_PROT_MAGIC2 == g_pmom_ctrl.log.smem->mem_info.magic)
		{
			g_pmom_ctrl.log.init_flag = PM_OM_INIT_MAGIC;
			pm_om_spin_lock(&g_pmom_ctrl.log.lock, flags);
			if (platform)
			{
				platform->log_info.mem_is_ok = 1; /*[false alarm]*/
			}
			pm_om_spin_unlock(&g_pmom_ctrl.log.lock, flags);
		}
	}

	pmom_pr_err("ok\n");

	return 0;
}

int bsp_pm_om_dump_init(void)
{
	long base_addr = 0;

	(void)memset_s((void *)&g_pmom_ctrl.dump, sizeof(g_pmom_ctrl.dump), 0, sizeof(g_pmom_ctrl.dump));

	spin_lock_init(&g_pmom_ctrl.dump.lock);

	g_pmom_ctrl.dump.base = (void *)bsp_dump_register_field(PM_OM_DUMP_ID, "PM_OM", 0, 0, PM_OM_DUMP_SIZE, 0);
	if (NULL == g_pmom_ctrl.dump.base)
	{
		goto err_ret; /*lint !e801 */
	}

	g_pmom_ctrl.dump.sub_region = g_pmom_ctrl.dump.base;

	g_pmom_ctrl.dump.cfg = (struct pm_om_dump_cfg *)g_pmom_ctrl.dump.base;
	g_pmom_ctrl.dump.cfg->file_head.magic    = (u32)PM_OM_MAGIC_PMDP;
	g_pmom_ctrl.dump.cfg->file_head.len      = PM_OM_DUMP_SIZE;
	g_pmom_ctrl.dump.cfg->file_head.version  = 1;
	g_pmom_ctrl.dump.cfg->file_head.reserved = PM_OM_PROT_MAGIC2;

	g_pmom_ctrl.dump.sub_region += sizeof(*(g_pmom_ctrl.dump.cfg));

	base_addr = (long)g_pmom_ctrl.dump.sub_region;
	g_pmom_ctrl.dump.sub_region = (char *)OSL_ROUND_UP(base_addr, 4);

	(void)memset_s((void *)g_pmom_ctrl.dump.cfg->entry_tbl, sizeof(g_pmom_ctrl.dump.cfg->entry_tbl),
		0, sizeof(g_pmom_ctrl.dump.cfg->entry_tbl));

	g_pmom_ctrl.dump.init_flag = PM_OM_INIT_MAGIC;
	pmom_pr_err("ok\n");

	return PM_OM_OK;

err_ret:
	g_pmom_ctrl.dump.cfg = NULL;
	pmom_pr_err("alloc mem fail\n");
	return PM_OM_ERR;
}

arch_initcall_sync(bsp_pm_om_dump_init);/*lint !e19 */
module_init(bsp_pm_om_log_init);        /*lint !e19 */
EXPORT_SYMBOL(bsp_pm_log_type);         /*lint !e19 */
EXPORT_SYMBOL(bsp_pm_log);              /*lint !e19 */
EXPORT_SYMBOL(pm_om_ctrl_get);          /*lint !e19 */
EXPORT_SYMBOL(bsp_pm_log_addr_get);     /*lint !e19 */
EXPORT_SYMBOL(bsp_pm_dump_get);         /*lint !e19 */
