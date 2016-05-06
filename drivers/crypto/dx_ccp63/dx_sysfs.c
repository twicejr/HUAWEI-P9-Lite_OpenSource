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

#include <linux/kernel.h>
#include <asm/timex.h>
#include "dx_config.h"
#include "dx_driver.h"
#include "sep_ctx.h"
#include "dx_sysfs.h"


#ifdef ENABLE_CYCLE_COUNT

struct stat_item {
	unsigned int min;
	unsigned int max;
	cycles_t sum;
	unsigned int count;
};

struct stat_name {
	const char *op_type_name;
	const char *stat_phase_name[MAX_STAT_PHASES];
};

static struct stat_name stat_name_db[MAX_STAT_OP_TYPES] = 
{
	{
		/* STAT_OP_TYPE_NULL */
		.op_type_name = "NULL",
		.stat_phase_name = {NULL},
	},
	{
		.op_type_name = "Encode",
		.stat_phase_name[STAT_PHASE_0] = "Init and sanity checks",
		.stat_phase_name[STAT_PHASE_1] = "Map buffers", 
		.stat_phase_name[STAT_PHASE_2] = "Create sequence", 
		.stat_phase_name[STAT_PHASE_3] = "Send Request",
		.stat_phase_name[STAT_PHASE_4] = "HW-Q push",
		.stat_phase_name[STAT_PHASE_5] = "Sequence completion",
		.stat_phase_name[STAT_PHASE_6] = "HW cycles",
	},
	{	.op_type_name = "Decode",
		.stat_phase_name[STAT_PHASE_0] = "Init and sanity checks",
		.stat_phase_name[STAT_PHASE_1] = "Map buffers", 
		.stat_phase_name[STAT_PHASE_2] = "Create sequence", 
		.stat_phase_name[STAT_PHASE_3] = "Send Request",
		.stat_phase_name[STAT_PHASE_4] = "HW-Q push",
		.stat_phase_name[STAT_PHASE_5] = "Sequence completion",
		.stat_phase_name[STAT_PHASE_6] = "HW cycles",
	},
	{ 	.op_type_name = "Setkey",
		.stat_phase_name[STAT_PHASE_0] = "Init and sanity checks",
		.stat_phase_name[STAT_PHASE_1] = "Copy key to ctx",
		.stat_phase_name[STAT_PHASE_2] = "Create sequence",
		.stat_phase_name[STAT_PHASE_3] = "Send Request",
		.stat_phase_name[STAT_PHASE_4] = "HW-Q push",
		.stat_phase_name[STAT_PHASE_5] = "Sequence completion",
		.stat_phase_name[STAT_PHASE_6] = "HW cycles",
	},
	{
		.op_type_name = "Generic",
		.stat_phase_name[STAT_PHASE_0] = "Interrupt",
		.stat_phase_name[STAT_PHASE_1] = "ISR-to-Tasklet",
		.stat_phase_name[STAT_PHASE_2] = "Tasklet start-to-end",
		.stat_phase_name[STAT_PHASE_3] = "Tasklet:user_cb()",
		.stat_phase_name[STAT_PHASE_4] = "Tasklet:dx_X_complete() - w/o X_complete()",
		.stat_phase_name[STAT_PHASE_5] = "",
		.stat_phase_name[STAT_PHASE_6] = "HW cycles",
	}
};

/*
 * Structure used to create a directory 
 * and its attributes in sysfs.
 */
struct sys_dir {
	struct kobject *sys_dir_kobj;
	struct attribute_group sys_dir_attr_group;
	struct attribute **sys_dir_attr_list;
	int num_of_attrs;
	struct dx_drvdata *drvdata; /* Associated driver context */
};

/* top level directory structures */
struct sys_dir sys_top_dir;

static DEFINE_SPINLOCK(stat_lock);

/* List of DBs */
static struct stat_item stat_host_db[MAX_STAT_OP_TYPES][MAX_STAT_PHASES];
static struct stat_item stat_cc_db[MAX_STAT_OP_TYPES][MAX_STAT_PHASES];


static void init_db(struct stat_item item[MAX_STAT_OP_TYPES][MAX_STAT_PHASES])
{
	unsigned int i, j;

	/* Clear db */
	for (i=0; i<MAX_STAT_OP_TYPES; i++) {
		for (j=0; j<MAX_STAT_PHASES; j++) {
			item[i][j].min = 0xFFFFFFFF;
			item[i][j].max = 0;
			item[i][j].sum = 0;
			item[i][j].count = 0;
		}
	}
}

static void update_db(struct stat_item *item, unsigned int result)
{
	item->count++;
	item->sum += result;
	if (result < item->min)
		item->min = result;
	if (result > item->max )
		item->max = result;
}

static void display_db(struct stat_item item[MAX_STAT_OP_TYPES][MAX_STAT_PHASES])
{
	unsigned int i, j;
	uint64_t avg;

	for (i=STAT_OP_TYPE_ENCODE; i<MAX_STAT_OP_TYPES; i++) {
		for (j=0; j<MAX_STAT_PHASES; j++) {	
			if (item[i][j].count > 0) {
				avg = (uint64_t)item[i][j].sum;
				do_div(avg, item[i][j].count);
				DX_LOG_ERR("%s, %s: min=%d avg=%d max=%d sum=%lld count=%d\n", 
					stat_name_db[i].op_type_name, stat_name_db[i].stat_phase_name[j], 
					item[i][j].min, (int)avg, item[i][j].max, (long long)item[i][j].sum, item[i][j].count);
			}
		}
	}
}


/**************************************
 * Attributes show functions section  *
 **************************************/

static struct dx_drvdata *sys_get_drvdata(void)
{
	/* TODO: supporting multiple SeP devices would require avoiding
	 * global "top_dir" and finding associated "top_dir" by traversing
	 * up the tree to the kobject which matches one of the top_dir's */
	return sys_top_dir.drvdata;
}

static ssize_t dx_sys_fw_ver_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	struct dx_drvdata *drvdata = sys_get_drvdata();
	return sprintf(buf,
		"ROM_VER=0x%08X\nFW_VER=0x%08X\n",
		drvdata->rom_ver, drvdata->fw_ver);
}

static ssize_t dx_sys_stats_host_db_clear(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
{
	init_db(stat_host_db);
	return count;
}

static ssize_t dx_sys_stats_cc_db_clear(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
{
	init_db(stat_cc_db);
	return count;
}

static ssize_t dx_sys_stat_host_db_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	int i, j, buf_len;
	char line[512];
	uint32_t min_cyc, max_cyc;
	uint64_t avg;

	buf_len = sprintf(buf,
		"phase\t\t\t\t\t\t\tmin[cy]\tavg[cy]\tmax[cy]\t#samples\n");

	for (i=STAT_OP_TYPE_ENCODE; i<MAX_STAT_OP_TYPES; i++) {
		for (j=0; j<MAX_STAT_PHASES-1; j++) {
			if (stat_host_db[i][j].count > 0) {
				avg = (uint64_t)stat_host_db[i][j].sum;
				do_div(avg, stat_host_db[i][j].count);
				min_cyc = stat_host_db[i][j].min;
				max_cyc = stat_host_db[i][j].max;
			} else {
				avg = min_cyc = max_cyc = 0;
			}
			buf_len += sprintf(line,
				"%s::%s\t\t\t\t\t%6u\t%6u\t%6u\t%7u\n",
				stat_name_db[i].op_type_name,
				stat_name_db[i].stat_phase_name[j],
				min_cyc, (unsigned int)avg, max_cyc,
				stat_host_db[i][j].count);
			strcat(buf, line);
		}
	}
	return buf_len;
}

static ssize_t dx_sys_stat_cc_db_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	int i, buf_len;
	char line[256];
	uint32_t min_cyc, max_cyc;
	uint64_t avg;

	buf_len = sprintf(buf,
		"phase\tmin[cy]\tavg[cy]\tmax[cy]\t#samples\n");

	for (i=STAT_OP_TYPE_ENCODE; i<MAX_STAT_OP_TYPES; i++) {
		if (stat_cc_db[i][STAT_PHASE_6].count > 0) {
			avg = (uint64_t)stat_cc_db[i][STAT_PHASE_6].sum;
			do_div(avg, stat_cc_db[i][STAT_PHASE_6].count);
			min_cyc = stat_cc_db[i][STAT_PHASE_6].min;
			max_cyc = stat_cc_db[i][STAT_PHASE_6].max;
		} else {
			avg = min_cyc = max_cyc = 0;
		}
		buf_len += sprintf(line,
			"%s\t%6u\t%6u\t%6u\t%7u\n",
			stat_name_db[i].op_type_name,
			min_cyc,
			(unsigned int)avg,
			max_cyc,
			stat_cc_db[i][STAT_PHASE_6].count);
		strcat(buf, line);
	}
	return buf_len;
}

/********************************************************
 *		SYSFS objects				*
 ********************************************************/

/* TOP LEVEL ATTRIBUTES */
static struct kobj_attribute dx_sys_top_level_attrs[] = {
	__ATTR(fw_ver, 0444, dx_sys_fw_ver_show, NULL),
	__ATTR(stats_host, 0666, dx_sys_stat_host_db_show, dx_sys_stats_host_db_clear),
	__ATTR(stats_cc, 0666, dx_sys_stat_cc_db_show, dx_sys_stats_cc_db_clear),
};

void update_host_stat(unsigned int op_type, unsigned int phase, cycles_t result)
{
	unsigned long flags;

	spin_lock_irqsave(&stat_lock, flags);
	update_db(&(stat_host_db[op_type][phase]), (unsigned int)result);
	spin_unlock_irqrestore(&stat_lock, flags);
}

void update_cc_stat(
	unsigned int op_type,
	unsigned int phase,
	unsigned int elapsed_cycles)
{
	update_db(&(stat_cc_db[op_type][phase]), elapsed_cycles);
}

void display_all_stat_db(void)
{
	DX_LOG_ERR("\n=======    CYCLE COUNT STATS    =======\n"); 
	display_db(stat_host_db);
	DX_LOG_ERR("\n======= CC HW CYCLE COUNT STATS =======\n"); 
	display_db(stat_cc_db);
}

static int sys_init_dir(struct sys_dir *sys_dir, struct dx_drvdata *drvdata,
		 struct kobject *parent_dir_kobj, const char *dir_name,
		 struct kobj_attribute *attrs, int num_of_attrs)
{
	int i;

	memset(sys_dir, 0, sizeof(struct sys_dir));

	sys_dir->drvdata = drvdata;

	/* initialize directory kobject */
	sys_dir->sys_dir_kobj =
		kobject_create_and_add(dir_name, parent_dir_kobj);

	if (!(sys_dir->sys_dir_kobj))
		return -ENOMEM;
	/* allocate memory for directory's attributes list */
	sys_dir->sys_dir_attr_list =
		kzalloc(sizeof(struct attribute *) * (num_of_attrs + 1),
				GFP_KERNEL);

	if (!(sys_dir->sys_dir_attr_list)) {
		kobject_put(sys_dir->sys_dir_kobj);
		return -ENOMEM;
	}

	sys_dir->num_of_attrs = num_of_attrs;

	/* initialize attributes list */
	for (i = 0; i < num_of_attrs; ++i)
		sys_dir->sys_dir_attr_list[i] = &(attrs[i].attr);

	/* last list entry should be NULL */
	sys_dir->sys_dir_attr_list[num_of_attrs] = NULL;

	sys_dir->sys_dir_attr_group.attrs = sys_dir->sys_dir_attr_list;

	return sysfs_create_group(sys_dir->sys_dir_kobj,
			&(sys_dir->sys_dir_attr_group));
}

static void sys_free_dir(struct sys_dir *sys_dir)
{
	if (!sys_dir)
		return;

	kfree(sys_dir->sys_dir_attr_list);

	if (sys_dir->sys_dir_kobj != NULL)
		kobject_put(sys_dir->sys_dir_kobj);
}

int dx_sysfs_init(struct kobject *sys_dev_obj, struct dx_drvdata *drvdata)
{
	int retval;

	/* Init. statistics */
	init_db(stat_host_db);
	init_db(stat_cc_db);

	DX_LOG_ERR("setup sysfs under %s\n", sys_dev_obj->name);

	/* Initialize top directory */
	retval = sys_init_dir(&sys_top_dir, drvdata, sys_dev_obj,
				"dx_info", dx_sys_top_level_attrs,
				sizeof(dx_sys_top_level_attrs) /
				sizeof(struct kobj_attribute));
	return retval;
}

void dx_sysfs_fini()
{
	sys_free_dir(&sys_top_dir);
}

#endif /*ENABLE_CYCLE_COUNT*/

