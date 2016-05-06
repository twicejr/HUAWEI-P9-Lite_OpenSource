/*
 * rdr unit test . (RDR: kernel run data recorder.)
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/stat.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/slab.h>

#include <linux/hisi/rdr_pub.h>

#include "rdr_print.h"
#include "rdr_inner.h"
#include "rdr_field.h"

static struct semaphore rdr_module_sem_ap;
struct rdr_register_module_result current_info_ap;
static pfn_cb_dump_done pfn_cb_dumpdone_ap;
static u64 current_core_id_ap;
static u32 g_modid_ap;
void fn_dump_ap(u32 modid, u32 etype, u64 coreid,
		char *pathname, pfn_cb_dump_done pfn_cb)
{
	if (current_core_id_ap != coreid) {
		BB_PRINT_DBG(" coreid does not match.\n");
		return;
	}
	BB_PRINT_DBG(" ====================================\n");
	BB_PRINT_DBG(" modid:          [0x%x]\n", modid);
	BB_PRINT_DBG(" coreid:         [0x%llx]\n", coreid);
	BB_PRINT_DBG(" exce tpye:      [0x%x]\n", etype);
	BB_PRINT_DBG(" path name:      [%s]\n", pathname);
	BB_PRINT_DBG(" dump start:     [0x%llx]\n", current_info_ap.log_addr);
	BB_PRINT_DBG(" dump len:       [%d]\n", current_info_ap.log_len);
	BB_PRINT_DBG(" nve:            [0x%llx]\n", current_info_ap.nve);
	BB_PRINT_DBG(" callback:       [0x%p]\n", pfn_cb);
	BB_PRINT_DBG(" ====================================\n");
	pfn_cb_dumpdone_ap = pfn_cb;
	g_modid_ap = modid;
	up(&rdr_module_sem_ap);
}

void fn_reset_ap(u32 modid, u32 etype, u64 coreid)
{
	BB_PRINT_DBG(" ====================================\n");
	BB_PRINT_DBG(" modid:          [0x%x]\n", modid);
	BB_PRINT_DBG(" coreid:         [0x%llx]\n", coreid);
	BB_PRINT_DBG(" exce tpye:      [0x%x]\n", etype);
	BB_PRINT_DBG(" ====================================\n");
}

void rdr_system_error_all(void)
{
	BB_PRINT_START();
	rdr_system_error(0, 0, 0);
	rdr_system_error(0x80000000, 0, 0);
	rdr_system_error(0x81000000, 0, 0);
	rdr_system_error(0x82000000, 0, 0);
	rdr_system_error(0x83000000, 0, 0);
	rdr_system_error(0x84000000, 0, 0);
	rdr_system_error(0x85000000, 0, 0);
	rdr_system_error(0x86000000, 0, 0);
	rdr_system_error(0x87000000, 0, 0);
	rdr_system_error(0x88000000, 0, 0);
	rdr_system_error(0x89000000, 0, 0);
	rdr_system_error(0x81000000, 0, 0);
	rdr_system_error(0x82000000, 0, 0);
	rdr_system_error(0x83000000, 0, 0);
	rdr_system_error(0x84000000, 0, 0);
	rdr_system_error(0x85000000, 0, 0);
	rdr_system_error(0x86000000, 0, 0);
	rdr_system_error(0x87000000, 0, 0);
	rdr_system_error(0x88000000, 0, 0);
	rdr_system_error(0, 0, 0);
	BB_PRINT_END();
	return;
}

void register_exception_for_test(u32 modid_start, u32 modid_end)
{
	static int loop;
	struct rdr_exception_info_s einfo;

	einfo.e_modid = modid_start;
	einfo.e_modid_end = modid_end;
	einfo.e_process_priority = RDR_OTHER;
	einfo.e_reboot_priority = RDR_REBOOT_NO;
	einfo.e_notify_core_mask = 0x0fffffff;
	einfo.e_reset_core_mask = 0x0;
	einfo.e_reentrant = loop % 2;
	einfo.e_exce_type = 0x1;
	einfo.e_from_core = loop % RDR_CORE_MAX;
	memcpy(einfo.e_from_module, "RDR_UT_TEST", sizeof("RDR_UT_TEST"));
	memcpy(einfo.e_desc, "RDR_UT_TEST for rdr_register_exception_ap_type",
	       sizeof("RDR_UT_TEST for rdr_register_exception_ap_type"));

	einfo.e_reserve_u32 = loop * 128;
	einfo.e_reserve_p = &einfo;
	einfo.e_callback = 0;

	rdr_register_exception(&einfo);
	loop++;
	return;
}

void register_exception_ap(u32 modid)
{
	register_exception_for_test(modid, modid + 0x100);
	return;
}

void register_exception_ap_all(void)
{
	BB_PRINT_START();
	register_exception_ap(0);
	register_exception_ap(0x80000000);
	register_exception_ap(0x81000000);
	register_exception_ap(0x82000000);
	register_exception_ap(0x83000200);
	register_exception_ap(0x84000000);
	register_exception_ap(0x85000000);
	register_exception_ap(0x86000000);
	register_exception_ap(0x87000000);
	BB_PRINT_END();
	return;
}

void rdr_register_core_ap(u64 coreid)
{
	struct rdr_module_ops_pub s_module_ops;
	struct rdr_register_module_result retinfo;
	int ret = 0;

	BB_PRINT_START();

	s_module_ops.ops_dump = fn_dump_ap;
	s_module_ops.ops_reset = fn_reset_ap;

	ret = rdr_register_module_ops(coreid, &s_module_ops, &retinfo);
	if (ret < 0) {
		BB_PRINT_ERR("rdr_register_module_ops fail, ret = [%d]\n", ret);
	}

	current_info_ap.log_addr = retinfo.log_addr;
	current_info_ap.log_len = retinfo.log_len;
	current_info_ap.nve = retinfo.nve;

	current_core_id_ap = coreid;
	BB_PRINT_END();
	return;
}

int rdr_large_kmalloc_test(u32 xMB)
{
	int ret = 0;
	int i;
	void **kmalloc_addr;
	BB_PRINT_ERR("[%s]: try to malloc [%d]MB>>>>\n", __func__, xMB);
	if (xMB >= 10000) {
		BB_PRINT_ERR("[%d]MB is too big to accept!\n", xMB);
		ret = -1;
		goto end;
	} else {
		kmalloc_addr = kmalloc(xMB * sizeof(void *), GFP_KERNEL);
		if (NULL == kmalloc_addr) {
			BB_PRINT_ERR("kmalloc kmalloc_addr failed!\n");
			ret = -1;
			goto end;
		}

		for (i = 0; i < xMB;) {
			kmalloc_addr[i] = kmalloc(0x100000, GFP_KERNEL);
			if (NULL == kmalloc_addr[i]) {
				BB_PRINT_ERR("kmalloc [%d]MB failed!\n", i);
				ret = -1;
				break;
			}
			i++;
		}

		while ((--i) >= 0) {
			kfree(kmalloc_addr[i]);
		}
		kfree(kmalloc_addr);
	}
end:
	if (0 == ret) {
		BB_PRINT_ERR("[%s]: success to malloc [%d]MB ; <<<<\n",
			     __func__, xMB);
	} else {
		BB_PRINT_ERR("[%s]: fail to malloc [%d]MB ; <<<<\n", __func__,
			     xMB);
	}
	return ret;
}

void rdr_register_core_for_test(u64 coreid)
{
	rdr_register_core_ap(coreid);
}

static int rdr_module_thread_body_ap(void *arg)
{
	BB_PRINT_START();
	while (1) {
		if (down_interruptible(&rdr_module_sem_ap)) {
			return -1;
		}
		BB_PRINT_DBG
		    (" ==============dump alllog start==============\n");
		BB_PRINT_DBG
		    (" ... ... ... ... ... ... ... ... ... ... ... .\n");
		msleep(1000);
		BB_PRINT_DBG
		    (" ==============dump alllog e n d==============\n");
		if (pfn_cb_dumpdone_ap != NULL) {
			pfn_cb_dumpdone_ap(g_modid_ap, current_core_id_ap);
		}
	}
}

extern int rdr_demo_init(void);
int rdr_debug_init(void)
{
	BB_PRINT_START();
	sema_init(&rdr_module_sem_ap, 0);
	if (!kthread_run(rdr_module_thread_body_ap, NULL, "rdr_module_thread")) {
		BB_PRINT_ERR("create thread rdr_main_thread faild.\n")
		    return -1;
	}
	/* rdr_register_core_ap(RDR_AP); */
	rdr_demo_init();
	BB_PRINT_END();
	return 0;
}
