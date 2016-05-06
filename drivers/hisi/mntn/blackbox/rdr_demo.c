/*
 * rdr demo for module. (RDR: kernel run data recorder.)
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

static struct semaphore rdr_soc_sem;
struct rdr_register_module_result current_info;
static pfn_cb_dump_done pfn_cb_dumpdone;
static u64 current_core_id = RDR_TEEOS;
static u32 g_modid;

void rdr_syserr_test(u32 modid, u32 arg1, u32 arg2)
{
	BB_PRINT_START();
	rdr_system_error(modid, arg1, arg2);
	BB_PRINT_END();
}

void fn_dump(u32 modid, u32 etype, u64 coreid,
	     char *pathname, pfn_cb_dump_done pfn_cb)
{
	BB_PRINT_DBG(" ====================================\n");
	BB_PRINT_DBG(" modid:          [0x%x]\n", modid);
	BB_PRINT_DBG(" coreid:         [0x%llx]\n", coreid);
	BB_PRINT_DBG(" exce tpye:      [0x%x]\n", etype);
	BB_PRINT_DBG(" path name:      [%s]\n", pathname);
	BB_PRINT_DBG(" dump start:     [0x%llx]\n", current_info.log_addr);
	BB_PRINT_DBG(" dump len:       [%d]\n", current_info.log_len);
	BB_PRINT_DBG(" nve:            [0x%llx]\n", current_info.nve);
	BB_PRINT_DBG(" callback:       [0x%p]\n", pfn_cb);
	BB_PRINT_DBG(" ====================================\n");
	pfn_cb_dumpdone = pfn_cb;
	g_modid = modid;
	up(&rdr_soc_sem);
}

void fn_reset(u32 modid, u32 etype, u64 coreid)
{
	BB_PRINT_DBG(" ====================================\n");
	BB_PRINT_DBG(" modid:          [0x%x]\n", modid);
	BB_PRINT_DBG(" coreid:         [0x%llx]\n", coreid);
	BB_PRINT_DBG(" exce tpye:      [0x%x]\n", etype);
	BB_PRINT_DBG(" ====================================\n");
	if (1)			/* reset error */
		rdr_system_error(0x83000011, 0, 0);
}

int rdr_register_core(void)
{
	struct rdr_module_ops_pub s_module_ops;
	int ret = -1;

	BB_PRINT_START();

	s_module_ops.ops_dump = fn_dump;
	s_module_ops.ops_reset = fn_reset;

	ret = rdr_register_module_ops(current_core_id, &s_module_ops,
				    &current_info);

	BB_PRINT_END();
	return ret;
}

int register_exception(void)
{
	struct rdr_exception_info_s einfo;
	int ret = -1;

	memset(&einfo, 0, sizeof(struct rdr_exception_info_s));
	einfo.e_modid = 0x83000001;
	einfo.e_process_priority = RDR_ERR;
	einfo.e_reboot_priority = RDR_REBOOT_WAIT;
	einfo.e_notify_core_mask = RDR_TEEOS | RDR_AP;
	einfo.e_reset_core_mask = RDR_TEEOS;
	einfo.e_reentrant = RDR_REENTRANT_DISALLOW;
	einfo.e_exce_type = RDR_EXCE_WD;
	einfo.e_from_core = RDR_TEEOS;
	memcpy(einfo.e_from_module, "RDR_DEMO_TEST", sizeof("RDR_DEMO_TEST"));
	memcpy(einfo.e_desc, "RDR_DEMO_TEST for teeos wd issue.",
	       sizeof("RDR_DEMO_TEST for teeos wd issue."));
	ret = rdr_register_exception(&einfo);

	memset(&einfo, 0, sizeof(struct rdr_exception_info_s));
	einfo.e_modid = 0x83000011;
	einfo.e_process_priority = RDR_ERR;
	einfo.e_reboot_priority = RDR_REBOOT_NOW;
	einfo.e_notify_core_mask = RDR_TEEOS | RDR_AP;
	einfo.e_reset_core_mask = RDR_AP;
	einfo.e_reentrant = RDR_REENTRANT_DISALLOW;
	einfo.e_exce_type = RDR_EXCE_WD;
	einfo.e_from_core = RDR_TEEOS;
	memcpy(einfo.e_from_module, "RDR_DEMO_TEST", sizeof("RDR_DEMO_TEST"));
	memcpy(einfo.e_desc, "RDR_DEMO_TEST for teeos reset failed issue.",
	       sizeof("RDR_DEMO_TEST for teeos reset failed issue."));
	ret = rdr_register_exception(&einfo);

	memset(&einfo, 0, sizeof(struct rdr_exception_info_s));
	einfo.e_modid = 0x83000020;
	einfo.e_modid_end = 0x83000100;
	einfo.e_process_priority = RDR_OTHER;
	einfo.e_reboot_priority = RDR_REBOOT_WAIT;
	einfo.e_notify_core_mask = 0xffffffff;
	einfo.e_reset_core_mask = 0;
	einfo.e_reentrant = RDR_REENTRANT_ALLOW;
	einfo.e_exce_type = RDR_EXCE_INITIATIVE;
	einfo.e_from_core = RDR_TEEOS;
	memcpy(einfo.e_from_module, "RDR_DEMO_TEST", sizeof("RDR_DEMO_TEST"));
	memcpy(einfo.e_desc, "RDR_DEMO_TEST for teeos ordinary issue.",
	       sizeof("RDR_DEMO_TEST for teeos ordinary issue."));
	ret = rdr_register_exception(&einfo);

	return ret;
}

static int rdr_soc_thread_body(void *arg)
{
	BB_PRINT_START();
	while (1) {
		if (down_interruptible(&rdr_soc_sem)) {
			return -1;
		}
		BB_PRINT_DBG(" ==============dump alllog start==============\n");
		BB_PRINT_DBG(" ... ... ... ... ... ... ... ... ... ... ... .\n");
		msleep(1000);
		BB_PRINT_DBG(" ==============dump alllog e n d==============\n");
		if (pfn_cb_dumpdone != NULL) {
			pfn_cb_dumpdone(g_modid, current_core_id);
		}
	}
}

int demo_init_early(void)
{
	int ret = 0;
	/* register module */
	ret = rdr_register_core();
	if (ret != 0)
		return ret;
	/* regitster exception */
	ret = register_exception();
	return ret;
}

int rdr_demo_init(void)
{
	BB_PRINT_START();

	/* if (0 > demo_init_early())  return -1; */
	demo_init_early();
	sema_init(&rdr_soc_sem, 0);
	if (!kthread_run(rdr_soc_thread_body, NULL, "rdr_soc_thread")) {
		BB_PRINT_ERR("create thread rdr_main_thread faild.\n")
		    return -1;
	}
	BB_PRINT_END();
	return 0;
}
