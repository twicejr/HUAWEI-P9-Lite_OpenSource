#ifndef __BALONG_CON_VIRTSHELL_H_
#define __BALONG_CON_VIRTSHELL_H_

#include <osl_sem.h>
#include <osl_thread.h>
#include <osl_spinlock.h>
#include <osl_list.h>

#define VIRTSHL_ERR_NOT_CTRLCMD   2
#define VIRTSHL_ERR_NO_MEM        3
#define VIRTSHL_ERR_ICC_REG_EVENT 4
#define VIRTSHL_ERR_TSK_INIT      5


#define VIRTSHL_SEND_TSK_PRIORITY 35
#define VIRTSHL_SEND_TSK_STACKSZ 1024

#define VIRTSHL_MAX_PACKAGE_LEN 256
#define VIRTSHL_MAX_H16ID_NUM 1


enum virtshl_ctrl_cmd_type
{
	VCMD_CONNECT,
	VCMD_DISCONNECT,
	VCMD_CONEC_ACK,
	VCMD_DISCONEC_ACK
};

enum virtshl_ack_type
{
	VACK_NA = 0,
	VACK_SUCC,
	VACK_FAIL
};

#define VIRTSHL_CMD_MAGIC "vconcmd"
#define VIRTSHL_CMD_MAGIC_LEN 8

struct virtshl_ctrl_cmd
{
	unsigned char cmd_magic[VIRTSHL_CMD_MAGIC_LEN];
	unsigned int cmd_type;
	unsigned int target_coreid;
	unsigned int local_coreid;
	unsigned int entire_iccid;
	unsigned int acknowledge;
};

struct virtshl_icc_l16id
{
	unsigned int target_coreid;
	unsigned int owner_coreid;
	unsigned int chn_id;
	unsigned int hid_idx;
	struct console * con;
	struct list_head subchn_list;
	struct list_head slist;/* ÃüÃû */
	struct list_head rlist;
};

struct virtshl_icc_h16id
{
	unsigned int target_coreid;
	unsigned int local_coreid;
	unsigned int h16id;
	struct list_head virtchn_list;
	unsigned short next_l16id;
	unsigned short reserved;
};

struct virtshl_module_ctr
{
	OSL_TASK_ID send_tsk_id;
	OSL_TASK_ID recv_tsk_id;
	struct semaphore send_tsk_sem;
	struct semaphore recv_tsk_sem;
	struct list_head slist;
	struct list_head rlist;
	spinlock_t slist_lock;
	spinlock_t rlist_lock;
	struct virtshl_icc_h16id * h16ids;
	unsigned int h16id_num;
};

extern struct virtshl_module_ctr virtshl_ctrl_info;

unsigned int establish_icc_chn(unsigned int target_core, struct console * con);
int virtshl_start_shell(struct console * con);
int virtshl_init(void);

#endif
