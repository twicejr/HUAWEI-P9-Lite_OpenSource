/*
 * blackbox header file (blackbox: kernel run data recorder.)
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __BB_INNER_H__
#define __BB_INNER_H__

#include <linux/types.h>
#include <linux/list.h>

#include <linux/hisi/rdr_pub.h>

#define PATH_MAXLEN         128
#define TIME_MAXLEN         8
#define DATA_MAXLEN         14
#define DATATIME_MAXLEN     24	/* 14+8 +2, 2: '-'+'\0' */
#define PATH_MEMDUMP        "memorydump"
#define RDR_BIN             "bbox.bin"
#define RDX_BIN             "bbox_aft.bin"
#define DFX_BIN             "dfx.bin"
#define ROOT_UID		0
#define SYSTEM_GID		1000
#define DIR_LIMIT		0770
#define FILE_LIMIT		0660

#define RDR_DUMP_LOG_START  0x20120113
#define RDR_DUMP_LOG_DONE   0x20140607
#define RDR_PROC_EXEC_START 0xff115501
#define RDR_PROC_EXEC_DONE  0xff123059
#define RDR_REBOOT_DONE     0xff1230ff

#define RDR_PRODUCT_VERSION "PRODUCT_VERSION_STR"
#define RDR_PRODUCT "PRODUCT_NAME"	/* "hi3630_udp" */
#define BBOX_MODID_LAST_SAVE_NOT_DONE	0x8100fffe
#define RDR_MODID_AP_ABNORMAL_REBOOT	0x8100ffff
#define RDR_REBOOT_REASON_LEN 24
/*BBOX_COMMON_CALLBACK for public callback tags */
#define BBOX_COMMON_CALLBACK 0x1ull
#define BBOX_CALLBACK_MASK 0x3ull

#define BBOX_RT_PRIORITY    98

struct cmdword {
	unsigned char name[24];
	unsigned int num;
};

struct rdr_syserr_param_s {
	struct list_head syserr_list;
	u32 modid;
	u32 arg1;
	u32 arg2;
};

struct rdr_module_ops_s {
	struct list_head s_list;
	u64 s_core_id;
	struct rdr_module_ops_pub s_ops;
};

struct blackbox_modid_list {
	unsigned int modid_span_little;
	unsigned int modid_span_big;
	char *modid_str;
};

void rdr_callback(struct rdr_exception_info_s *p_exce_info, u32 mod_id,
		  char *logpath);
struct rdr_exception_info_s *rdr_get_exception_info(u32 modid);
void rdr_print_one_exc(struct rdr_exception_info_s *e);

u64 rdr_notify_module_dump(u32 modid, struct rdr_exception_info_s *e_info,
			   char *path);
u64 rdr_notify_onemodule_dump(u32 modid, u64 core, u32 type,
			      u64 formcore, char *path);
u64 rdr_get_cur_regcore(void);

u64 rdr_get_dump_result(u32 modid);
int rdr_save_history_log(struct rdr_exception_info_s *p, char *date,
			 bool is_save_done);
int rdr_save_history_log_for_undef_exception(struct rdr_syserr_param_s *p);

void rdr_notify_module_reset(u32 modid, struct rdr_exception_info_s *e_info);

int rdr_create_exception_path(struct rdr_exception_info_s *e,
			      char *path, char *date);
int rdr_create_epath_bc(u64 core, char *path);

void rdr_count_size(void);

int rdr_dump_init(void);
void rdr_dump_exit(void);
bool rdr_init_done(void);

typedef void (*parse_record_t) (u64 *data, u32 len);

/* kernel function. */
extern int inquiry_rtc_init_ok(void);

/*
 * func name: rdr_savebuf2fs
 * append(save) data to path.
 * func args:
 *  char*  path,			path of save file.
 *  void*  buf,             save data.
 *  u32 len,            data lenght.
 * return
 *	>=len fail
 *	==len success
 */
int rdr_savebuf2fs(char *path, char *name, void *buf, u32 len, u32 is_append);

/*
 * func name: rdr_get_exception_core
 * get exception core str for core id.
 * func args:
 *    u64 coreid
 * return value
 *	NULL  error
 *	!NULL core str.
 */
char *rdr_get_exception_core(u64 coreid);

/*
 * func name: rdr_get_exception_core
 * get exception core str for core id.
 * func args:
 *    u64 coreid
 * return value
 *	NULL  error
 *	!NULL core str.
 */
char *rdr_get_exception_type(u64 coreid);

/*
 * func name: rdr_wait_partition
 * .
 * func args:
 *  char*  path,			path of watit file.
 *  u32 timeouts,       time out.
 * return
 *	<0 fail
 *	0  success
 */

bool rdr_syserr_list_empty(void);

int rdr_wait_partition(char *path, int timeouts);
void rdr_get_builddatetime(u8 *out);
char *rdr_get_timestamp(void);
u64 rdr_get_tick(void);
int rdr_get_suspend_state(void);
int rdr_get_reboot_state(void);
int rdr_set_saving_state(int state);

int rdr_common_early_init(void);
int rdr_common_init(void);
u64 rdr_reserved_phymem_addr(void);
u64 rdr_reserved_phymem_size(void);
int rdr_get_dumplog_timeout(void);
u64 rdr_get_logsize(void);
RDR_NVE rdr_get_nve(void);

void rdr_save_last_baseinfo(char *logpath);
void rdr_save_cur_baseinfo(char *logpath);

void rdr_field_dumplog_done(void);
void rdr_field_reboot_done(void);
void rdr_field_procexec_done(void);
void rdr_field_baseinfo_reinit(void);

int rdr_get_sr_state(void);
int rdr_get_reboot_state(void);

int rdr_bootcheck_thread_body(void *arg);
u32 get_reboot_reason_map_size(void);
char *rdr_get_reboot_reason(void);
u32 rdr_get_reboot_type(void);

char *blackbox_get_modid_str(u32 modid);
int bbox_chown(const char *path, uid_t user, gid_t group, bool recursion);
void bbox_save_done(char *logpath, u32 step);
void rdr_record_reboot_times2mem(void);
void rdr_reset_reboot_times(void);
void rdr_record_erecovery_reason(void);
int rdr_record_reboot_times2file(void);
u32 rdr_get_reboot_times(void);
#endif /* End #define __BB_INNER_H__ */
