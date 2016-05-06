/*
* Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
* foss@huawei.com
*
* If distributed as part of the Linux kernel, the following license terms
* apply:
*
* * This program is free software; you can redistribute it and/or modify
* * it under the terms of the GNU General Public License version 2 and 
* * only version 2 as published by the Free Software Foundation.
* *
* * This program is distributed in the hope that it will be useful,
* * but WITHOUT ANY WARRANTY; without even the implied warranty of
* * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* * GNU General Public License for more details.
* *
* * You should have received a copy of the GNU General Public License
* * along with this program; if not, write to the Free Software
* * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
*
* Otherwise, the following license terms apply:
*
* * Redistribution and use in source and binary forms, with or without
* * modification, are permitted provided that the following conditions
* * are met:
* * 1) Redistributions of source code must retain the above copyright
* *    notice, this list of conditions and the following disclaimer.
* * 2) Redistributions in binary form must reproduce the above copyright
* *    notice, this list of conditions and the following disclaimer in the
* *    documentation and/or other materials provided with the distribution.
* * 3) Neither the name of Huawei nor the names of its contributors may 
* *    be used to endorse or promote products derived from this software 
* *    without specific prior written permission.
* 
* * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*/

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
