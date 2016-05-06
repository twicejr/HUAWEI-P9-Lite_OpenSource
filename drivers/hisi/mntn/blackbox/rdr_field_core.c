/*
 * blackbox. (kernel run data recorder.)
 *
 * Copyright (c) 2013 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/io.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <linux/of.h>

#include <linux/hisi/rdr_pub.h>
#include "rdr_inner.h"
#include "rdr_print.h"
#include "rdr_field.h"

static struct rdr_struct_s *pbb;
static struct rdr_struct_s *tmp_pbb;

u64 rdr_area_mem_addr[RDR_AREA_MAXIMUM + 1];
u32 rdr_area_mem_size[RDR_AREA_MAXIMUM] = {
	0,			/* 6, 有多少个核可以分配到内存 */
	0,			/* 0x180000, CP */
	0,			/* 0x20000, TEE */
	0,			/* 0x20000, HIFI */
	0,			/* 0x20000, LPM3 */
	0,			/* 0x20000, IOM3 */
};

void rdr_set_area_info(int index, u32 size)
{
	rdr_area_mem_size[index] = size;
}

struct rdr_struct_s *rdr_get_pbb(void)
{
	return pbb;
}

struct rdr_struct_s *rdr_get_tmppbb(void)
{
	return tmp_pbb;
}

void rdr_clear_tmppbb(void)
{
	if (tmp_pbb) {
		vfree(tmp_pbb);
		tmp_pbb = NULL;
	}
}

u64 rdr_get_pbb_size(void)
{
	return rdr_reserved_phymem_size();
}

int rdr_get_areainfo(enum RDR_AREA_LIST area,
		     struct rdr_register_module_result *retinfo)
{
	if (area >= RDR_AREA_MAXIMUM) {
		return -1;
	}

	retinfo->log_addr = pbb->area_info[area].offset;
	retinfo->log_len = pbb->area_info[area].length;

	return 0;
}

void rdr_field_baseinfo_init(void)
{
	BB_PRINT_START();
	pbb->base_info.modid = 0;
	pbb->base_info.arg1 = 0;
	pbb->base_info.arg2 = 0;
	pbb->base_info.e_core = 0;
	pbb->base_info.e_type = 0;
	pbb->base_info.start_flag = 0;
	pbb->base_info.savefile_flag = 0;
	pbb->base_info.reboot_flag = 0;
	memset(pbb->base_info.e_module, 0, MODULE_NAME_LEN);
	memset(pbb->base_info.e_desc, 0, STR_EXCEPTIONDESC_MAXLEN);
	memset(pbb->base_info.datetime, 0, DATATIME_MAXLEN);
	BB_PRINT_END();
	return;
}

void rdr_field_baseinfo_reinit(void)
{
	BB_PRINT_START();
	pbb->base_info.modid = 0;
	pbb->base_info.arg1 = 0;
	pbb->base_info.arg2 = 0;
	pbb->base_info.e_core = 0;
	pbb->base_info.e_type = 0;
	pbb->base_info.start_flag = RDR_PROC_EXEC_START;
	pbb->base_info.savefile_flag = RDR_DUMP_LOG_START;
	/* memset(pbb->base_info.e_module, 0, MODULE_NAME_LEN); */
	/* memset(pbb->base_info.e_desc, 0, STR_EXCEPTIONDESC_MAXLEN); */
	memset(pbb->base_info.datetime, 0, DATATIME_MAXLEN);
	BB_PRINT_END();
	return;
}

void rdr_field_areainfo_init(void)
{
	int index;
	for (index = 0; index < RDR_AREA_MAXIMUM; index++) {
		pbb->area_info[index].offset = rdr_area_mem_addr[index];
		pbb->area_info[index].length = rdr_area_mem_size[index];
	}
}

void rdr_field_dumplog_done(void)
{
	pbb->base_info.savefile_flag = RDR_DUMP_LOG_DONE;
}

void rdr_field_procexec_done(void)
{
	pbb->base_info.start_flag = RDR_PROC_EXEC_DONE;
}

void rdr_field_reboot_done(void)
{
	pbb->base_info.reboot_flag = RDR_REBOOT_DONE;
}

void rdr_field_top_init(void)
{
	u8 buildtime[RDR_BUILD_DATE_TIME_LEN];

	BB_PRINT_START();

	rdr_get_builddatetime(buildtime);
	pbb->top_head.magic = FILE_MAGIC;
	pbb->top_head.version = RDR_VERSION;

	rdr_get_builddatetime(pbb->top_head.build_time);
	memcpy(pbb->top_head.product_name, RDR_PRODUCT,
	       strlen(RDR_PRODUCT) > 16 ? 16 : strlen(RDR_PRODUCT));
	memcpy(pbb->top_head.product_version, RDR_PRODUCT_VERSION,
	       strlen(RDR_PRODUCT_VERSION) >
	       16 ? 16 : strlen(RDR_PRODUCT_VERSION));

	BB_PRINT_END();
	return;
}

int rdr_field_init(void)
{
	int ret = 0;
	int index;
	u32 last = 0;
	unsigned int fpga_flag = 0;
	struct device_node *np;

	BB_PRINT_START();

	pbb = hisi_bbox_map(rdr_reserved_phymem_addr(),
			  rdr_reserved_phymem_size());
	if (NULL == pbb) {
		BB_PRINT_PN("hisi_bbox_map pbb faild.");
		ret = -1;
		goto out;
	}

	tmp_pbb = vmalloc(rdr_reserved_phymem_size());
	if (NULL == tmp_pbb) {
		BB_PRINT_PN("vmalloc tmp_pbb faild.");
		ret = -1;
		hisi_bbox_unmap(pbb);
		pbb = NULL;
		goto out;
	}

	rdr_show_base_info(1);	/* show pbb */
	memcpy(tmp_pbb, pbb, rdr_reserved_phymem_size());
	rdr_show_base_info(0);	/* show tmpbb */

	np = of_find_compatible_node(NULL, NULL, "hisilicon,hisifb");
	if (!np) {
		printk("NOT FOUND device node 'hisilicon,hisifb'!\n");
		return -ENXIO;
	}
	ret = of_property_read_u32(np, "fpga_flag", &fpga_flag);
	if (ret) {
		printk("failed to get fpga_flag resource.\n");
		return -ENXIO;
	}
	/* if the power_up of phone is the first time,
	 * need clear bbox memory.
	 */
	if ((AP_S_COLDBOOT == rdr_get_reboot_type()) && (1 != fpga_flag)) {
		memset(pbb, 0, rdr_reserved_phymem_size());
	} else {
		memset(pbb, 0, RDR_BASEINFO_SIZE);
	}

	last = rdr_area_mem_size[0];
	rdr_area_mem_addr[last] = rdr_reserved_phymem_addr()
	    + rdr_reserved_phymem_size();
	for (index = last - 1; index > 0; index--) {
		rdr_area_mem_addr[index] = rdr_area_mem_addr[index + 1]
		    - rdr_area_mem_size[index];
	}
	rdr_area_mem_addr[0] = rdr_reserved_phymem_addr() + RDR_BASEINFO_SIZE;
	rdr_area_mem_size[0] = rdr_area_mem_addr[1] - RDR_BASEINFO_SIZE -
		rdr_reserved_phymem_addr();

	rdr_field_top_init();
	rdr_field_baseinfo_init();
	rdr_field_areainfo_init();
	BB_PRINT_END();
out:
	return ret;
}

void rdr_field_exit(void)
{
}

void rdr_save_args(u32 modid, u32 arg1, u32 arg2)
{
	BB_PRINT_START();
	pbb->base_info.modid = modid;
	pbb->base_info.arg1 = arg1;
	pbb->base_info.arg2 = arg2;

	/*pbb->base_info.savefile_flag = 0;
	   pbb->base_info.start_flag = 0; */
	BB_PRINT_END();
}

void rdr_fill_edata(struct rdr_exception_info_s *e, char *date)
{
	BB_PRINT_START();
	pbb->base_info.e_core = e->e_from_core;
	pbb->base_info.e_type = e->e_exce_type;
	memcpy(pbb->base_info.datetime, date, DATATIME_MAXLEN);
	memcpy(pbb->base_info.e_module, e->e_from_module, MODULE_NAME_LEN);
	memcpy(pbb->base_info.e_desc, e->e_desc, STR_EXCEPTIONDESC_MAXLEN);
	BB_PRINT_END();
}

void rdr_show_base_info(int flag)
{
	struct rdr_struct_s *p = NULL;
	int index;

	if (1 == flag) {
		p = rdr_get_pbb();
	} else {
		p = rdr_get_tmppbb();
	}

	if (NULL == p) {
		return;
	}

	if (p->top_head.magic != FILE_MAGIC) {
		BB_PRINT_PN("[%s]: rdr_struct_s information is not initialized, no need to print it's content!\n",
		     __func__);
		return;
	}

	p->base_info.datetime[DATATIME_MAXLEN - 1] = '\0';
	p->base_info.e_module[MODULE_NAME_LEN - 1] = '\0';
	p->base_info.e_desc[STR_EXCEPTIONDESC_MAXLEN - 1] = '\0';
	p->top_head.build_time[RDR_BUILD_DATE_TIME_LEN - 1] = '\0';
	BB_PRINT_PN("========= print baseinfo start =========\n");
	BB_PRINT_PN("modid        :[0x%x]\n", p->base_info.modid);
	BB_PRINT_PN("arg1         :[0x%x]\n", p->base_info.arg1);
	BB_PRINT_PN("arg2         :[0x%x]\n", p->base_info.arg2);
	BB_PRINT_PN("coreid       :[0x%x]\n", p->base_info.e_core);
	BB_PRINT_PN("reason       :[0x%x]\n", p->base_info.e_type);
	BB_PRINT_PN("e data       :[%s]\n", p->base_info.datetime);
	BB_PRINT_PN("e module     :[%s]\n", p->base_info.e_module);
	BB_PRINT_PN("e desc       :[%s]\n", p->base_info.e_desc);
	BB_PRINT_PN("e start_flag :[%d]\n", p->base_info.start_flag);
	BB_PRINT_PN("e save_flag  :[%d]\n", p->base_info.savefile_flag);
	BB_PRINT_PN("========= print baseinfo e n d =========\n");

	BB_PRINT_PN("========= print top head start =========\n");
	BB_PRINT_PN("maigc        :[0x%x]\n", p->top_head.magic);
	BB_PRINT_PN("version      :[0x%x]\n", p->top_head.version);
	BB_PRINT_PN("area num     :[0x%x]\n", p->top_head.area_number);
	BB_PRINT_PN("reserve      :[0x%x]\n", p->top_head.reserve);
	BB_PRINT_PN("buildtime    :[%s]\n",   p->top_head.build_time);
	BB_PRINT_PN("========= print top head e n d =========\n");

	BB_PRINT_PN("========= print areainfo start =========\n");
	for (index = 0; index < RDR_AREA_MAXIMUM; index++) {
		BB_PRINT_PN("area[%d] addr[0x%llx] size[0x%x]\n",
			index, pbb->area_info[index].offset,
			pbb->area_info[index].length);
	}
	BB_PRINT_PN("========= print areainfo e n d =========\n");
}
