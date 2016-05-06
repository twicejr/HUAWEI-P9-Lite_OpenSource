/*
* NoC. (NoC Mntn Module.)
*
* Copyright (c) 2016 Huawei Technologies CO., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*/

#ifndef __HISI_NOC_DUMP_H
#define __HISI_NOC_DUMP_H

#include "hisi_noc.h"

#define NOC_L_D_PRT pr_err

#define NOC_DUMP_ERRPRO_BUS_NUM      MAX_NOC_NODES_NR	/*9 */
#define NOC_DUMP_ERRPRO_OFF_NUM      7

#define NOC_DUMP_SYNC_LEN            4
#define NOC_DUMP_NOC_LEN             4
#define NOC_DUMP_NOC_NODE_NAME_LEN   24


#define NOC_DUMP_SYNC_HEAD1        0xFFFF0001
#define NOC_DUMP_SYNC_HEAD2        0x87654321
#define NOC_DUMP_NODE_EN_F         0xF0F0F0F0
#define NOC_DUMP_TAIL_NR           0xA55AA55A

#define NOC_TMOUT_MSK_INT_STAT0    0x1BFB2FB
#define NOC_TMOUT_MSK_SCPERSTS6    0x605
#define IS_NOC_TMOUT_HAPPEN(int_sts0, scper_sts6)\
				((int_sts0 & NOC_TMOUT_MSK_INT_STAT0) ||\
				(scper_sts6 & NOC_TMOUT_MSK_SCPERSTS6))

struct hisi_noc_bus_node_info {
	struct noc_node **noc_node_pptr;
	unsigned int noc_node_idx;
};

/* Stucture For Recording Hisi NoC Dump Info.*/
struct hisi_noc_dump_info {
	struct hisi_noc_bus_node_info noc_bus_node_info;
	struct hisi_noc_device *noc_device_ptr;
};

struct noc_dump_data {
	u32 sync[NOC_DUMP_SYNC_LEN];
	struct {
		u32 uPERI_STAT2;
		u32 uSCPERSTATUS6;
	} NopendingTrans;
	struct {
		u32 uNOC_POWER_IDLEREQ;
		u32 uNOC_POWER_IDLEACK;
		u32 uNOC_POWER_IDLE;
	} LmHand;
	struct {
		u32 uPERI_INT0_STAT;
		u32 uSCPERSTATUS6;
	} TimeoutSts;
	struct {
		u32 uPERI_CTRL19;
	} AddrInter;
	u32 NoCBusNodeIdx;
	struct {
		/* Node Name For PC NoC Parse Tool. */
		char node_name[NOC_DUMP_NOC_NODE_NAME_LEN];
		u32 en;
		u32 data[NOC_DUMP_ERRPRO_OFF_NUM];
	} ErrorProbe[NOC_DUMP_ERRPRO_BUS_NUM];
	u32 tail[NOC_DUMP_NOC_LEN];
};

/*
Function: noc_dump_init
Description: noc dump function registers to black-box module,
			so noc dump can be processed before reset
input: none
output: 0->success
*/
extern int noc_dump_init(void);
#endif
