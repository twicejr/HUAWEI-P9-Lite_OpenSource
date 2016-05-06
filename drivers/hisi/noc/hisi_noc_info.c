/*
* NoC. (NoC Mntn Module.)
*
* Copyright (c) 2016 Huawei Technologies CO., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*/

#include <linux/module.h>
#include <linux/bitops.h>
#include <linux/io.h>
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

#include "hisi_noc_info.h"
#include "hisi_noc.h"

static struct noc_arr_info noc_buses_i;
static struct noc_mid_info *pt_mid_info;

/**********************************************************
Function: noc_set_bus_info
Description:  Get NoC Bus Info.
Input:  NA
Output: NA
Return: NA
***********************************************************/
void noc_set_buses_info(void)
{
	noc_buses_i.ptr = noc_buses_info;
	noc_buses_i.len = hisi_noc_get_bus_info_num();
	pt_mid_info = noc_mid;
}

/*
Function: noc_get_mid_info
Description: noc get mid_info
input: none
output: none
return: noc_mid_info pointer
*/
struct noc_mid_info *noc_get_mid_info(void)
{
	return pt_mid_info;
}

/*
Function: noc_get_buses_info
Description: get noc_bus_info
input: none
output: none
return: noc_arr_info pointer
*/
struct noc_arr_info *noc_get_buses_info(void)
{
	return &noc_buses_i;
}

/*
Function: noc_get_bus_info
Description: get noc_bus_info from bus_id
input: int bus_id -> bus id input
output: none
return: noc_bus_info
*/
const struct noc_bus_info *noc_get_bus_info(int bus_id)
{
	const struct noc_bus_info *noc_bus = NULL;

	if (bus_id < noc_buses_i.len) {
		noc_bus = noc_buses_i.ptr;
		noc_bus += bus_id;
	}

	return noc_bus;
}

/**********************************************************
Function: noc_find_addr_from_routeid
Description:  Get NoC Error Address By Route-id Table.
Input:  unsigned int idx -- Bus Id;
		int initflow -- Access Init Flow
		int targetflow -- Access Target Flow
		int targetsubrange -- Target Subrange
Output: NA
Return: u64 -- NoC Error Local Address
***********************************************************/
u64 noc_find_addr_from_routeid(unsigned int idx, int initflow, int targetflow,
			       int targetsubrange)
{
	unsigned int i;
	unsigned int count;
	const ROUTE_ID_ADDR_STRU *pastTbl;

	if (idx >= hisi_noc_get_bus_info_num())
		return 0;

	pastTbl = noc_buses_i.ptr[idx].routeid_tbl;
	count   = noc_buses_i.ptr[idx].routeid_tbl_size;

	for (i = 0; i < count; i++) {
		if ((pastTbl[i].targ_flow == targetflow) &&
		    (pastTbl[i].targ_subrange == targetsubrange))

			return pastTbl[i].init_localaddr;
	}

	return 0;
}

