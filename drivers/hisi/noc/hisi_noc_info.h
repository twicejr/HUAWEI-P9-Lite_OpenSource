#ifndef __HISI_NOC_INFO_H
#define __HISI_NOC_INFO_H

#include <linux/module.h>
#include <linux/bitops.h>
#include <linux/io.h>
/*
* NoC. (NoC Mntn Module.)
*
* Copyright (c) 2016 Huawei Technologies CO., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*/

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/device.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/syscore_ops.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/vmalloc.h>
#include <linux/sched.h>
#include <linux/debugfs.h>
#include <linux/io.h>
#include <linux/string.h>
#include <linux/hisi/util.h>

#include "hisi_noc.h"

#define ARRAY_END_FLAG 0xffffffff

typedef struct datapath_routid_addr {
	int init_flow;
	int targ_flow;
	int targ_subrange;
	u64 init_localaddr;
} ROUTE_ID_ADDR_STRU;

/* keep target route id, initiator flow id etc*/
struct noc_bus_info {
	char *name;
	unsigned int initflow_mask;
	unsigned int initflow_shift;

	unsigned int targetflow_mask;
	unsigned int targetflow_shift;

	unsigned int targ_subrange_mask;
	unsigned int seq_id_mask;

	char **initflow_array;
	unsigned int initflow_array_size;

	char **targetflow_array;
	unsigned int targetflow_array_size;

	const ROUTE_ID_ADDR_STRU *routeid_tbl;
	unsigned int routeid_tbl_size;
};

struct noc_mid_info {
	unsigned int idx;	/*Bus Id: 0*/
	int init_flow;
	int mask;
	int mid_val;
	char *mid_name;
};

struct noc_arr_info {
	const struct noc_bus_info *ptr;
	unsigned int len;
};

/*for backup noc_errorprobe info*/
struct noc_errorprobe_backup_info {
	unsigned int bus_id;
	int init_flow;
	char *nodename;
};

/*for modemnoc_initflow array*/
struct noc_busid_initflow {
	unsigned int bus_id;
	int init_flow;
};

extern const struct noc_bus_info noc_buses_info[];
extern struct noc_mid_info noc_mid[];

void noc_set_buses_info(void);

/*
Function: noc_get_mid_info
Description: noc get mid_info
input: none
output: none
return: noc_mid_info pointer
*/
struct noc_mid_info *noc_get_mid_info(void);

/*
Function: noc_get_buses_info
Description: get noc_bus_info
input: none
output: none
return: noc_arr_info pointer
*/
struct noc_arr_info *noc_get_buses_info(void);

/*
Function: noc_get_bus_info
Description: get noc_bus_info from bus_id
input: int bus_id -> bus id input
output: none
return: noc_bus_info
*/
extern const struct noc_bus_info *noc_get_bus_info(int bus_id);
extern unsigned int hisi_noc_get_bus_info_num(void);

extern void hisi_get_modemnoc_initflow_nodename(
	struct noc_busid_initflow **modemnoc_initflow, char ***modemnoc_nodename);

#endif
