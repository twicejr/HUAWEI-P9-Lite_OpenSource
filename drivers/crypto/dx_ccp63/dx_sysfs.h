/***************************************************************
*  Copyright 2014 (c) Discretix Technologies Ltd.              *
*  This software is protected by copyright, international      *
*  treaties and various patents. Any copy, reproduction or     *
*  otherwise use of this software must be authorized in a      *
*  license agreement and include this Copyright Notice and any *
*  other notices specified in the license agreement.           *
*  Any redistribution in binary form must be authorized in the *
*  license agreement and include this Copyright Notice and     *
*  any other notices specified in the license agreement and/or *
*  in materials provided with the binary distribution.         *
****************************************************************/

/* \file dx_sysfs.h
   Discretix sysfs APIs
 */

#ifndef __DX_SYSFS_H__
#define __DX_SYSFS_H__

#include <asm/timex.h>

/* forward declaration */
struct dx_drvdata;

enum stat_phase {
	STAT_PHASE_0 = 0,
	STAT_PHASE_1,
	STAT_PHASE_2,
	STAT_PHASE_3,
	STAT_PHASE_4,
	STAT_PHASE_5,
	STAT_PHASE_6,
	MAX_STAT_PHASES,
};
enum stat_op {
	STAT_OP_TYPE_NULL = 0,
	STAT_OP_TYPE_ENCODE,
	STAT_OP_TYPE_DECODE,
	STAT_OP_TYPE_SETKEY,
	STAT_OP_TYPE_GENERIC,
	MAX_STAT_OP_TYPES,
};

int dx_sysfs_init(struct kobject *sys_dev_obj, struct dx_drvdata *drvdata);
void dx_sysfs_fini(void);
void update_host_stat(unsigned int op_type, unsigned int phase, cycles_t result);
void update_cc_stat(unsigned int op_type, unsigned int phase, unsigned int elapsed_cycles);
void display_all_stat_db(void);

#endif /*__DX_SYSFS_H__*/
