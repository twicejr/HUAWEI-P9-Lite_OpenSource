/*
* NoC. (NoC Mntn Module.)
*
* Copyright (c) 2016 Huawei Technologies CO., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*/

#ifndef __HISI_NOC_DBG_H
#define __HISI_NOC_DBG_H

#include "hisi_noc.h"
#include <soc_cfg_sys_noc_bus_interface.h>

struct noc_reg_dbg {
	char *p_reg_name;
	char *node_name;
	uint reg_len;		/* reg length, 8bit/16bit/32bit */
	uint offset;
	uint rw_flag;		/* bit0 rd, bit1 wr */
};
#define NOC_B_R               0x01
#define NOC_B_W              0x02
#define NOC_B_RW            (NOC_B_R|NOC_B_W)

#define NOC_CMD_CELL_SIZE 64

enum e_noc_dbg_cmd {
	E_NOC_DBG_CMD_RD_REG = 0,
	E_NOC_DBG_CMD_WR_REG,
	E_NOC_DBG_CMD_PKT_ENABLE,
	E_NOC_DBG_CMD_PKT_DISABLE,
	E_NOC_DBG_CMD_TRANS_ENABLE,
	E_NOC_DBG_CMD_TRANS_DISABLE,
	E_NOC_DBG_CMD_INVALID
};
struct noc_dbg_cmd_lookup {
	const char *str;
	enum e_noc_dbg_cmd cmd;
};
#ifdef CONFIG_DEBUG_FS
/*
Function: noc_dbg_creat_node
Description: noc debug function nodes creat
input: none
output: none
return: 0->success -1->failed
*/
extern int noc_dbg_creat_node(void);
#endif
#endif
