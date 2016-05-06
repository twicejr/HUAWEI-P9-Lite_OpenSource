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

#include <linux/string.h>
#include <linux/delay.h>
#include <osl_list.h>
#include <bsp_icc.h>
#include <bsp_reset.h>
#include "console.h"
#include "virtshell.h"

int syslog_recv_fun(char ch)
{
	return 0;
}

int shell_start(struct console * con)
{
	return 0;
}

int cshell_mode_reset_cb(DRV_RESET_CB_MOMENT_E eparam, int usrdata)
{
	int i = 0;
	int ret = 0;
	struct console *pos = NULL;

	switch(eparam)
	{
		case MDRV_RESET_CB_BEFORE:
			/* Disable all ccore agent console */
			list_for_each_entry(pos, &agent_consoles, next)
			{
				if(CON_CCORE == pos->coreid)
					ret += con_disable(pos);
			}
	
			break;
		case MDRV_RESET_CB_AFTER:
			/* connect to ccore again */
			for(i = 0; i < virtshl_ctrl_info.h16id_num; i++)
			{
				struct virtshl_icc_h16id * hid = NULL;
				struct virtshl_icc_l16id * lid = NULL;

				hid = &virtshl_ctrl_info.h16ids[i];
				if(hid->target_coreid != CON_CCORE)
					continue;
				list_for_each_entry(lid, &hid->virtchn_list, subchn_list)
				{
					if(CON_CURCORE == lid->owner_coreid && (lid->chn_id & 0xFF) != 0)
					{
						struct virtshl_ctrl_cmd ctrl_cmd;
						int sent_sz = 0;

						memcpy(ctrl_cmd.cmd_magic, VIRTSHL_CMD_MAGIC, VIRTSHL_CMD_MAGIC_LEN);
						ctrl_cmd.cmd_type = VCMD_CONNECT;
						ctrl_cmd.local_coreid = CON_CURCORE;
						ctrl_cmd.target_coreid = CON_CCORE;
						ctrl_cmd.entire_iccid = lid->chn_id;
						ctrl_cmd.acknowledge = 0;

						do{
							sent_sz = bsp_icc_send(ctrl_cmd.target_coreid, (hid->h16id << 16) | 0, (unsigned char*)&ctrl_cmd, sizeof(ctrl_cmd));
							if(sent_sz != sizeof(ctrl_cmd))
								udelay(100);
						}while(sent_sz != sizeof(ctrl_cmd));

						con_enable(lid->con);
					}
				}
			}

			break;
		default:
			break;
	}

	return ret;
}

