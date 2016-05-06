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

#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/printk.h>
#include "ringbuffer.h"
#include "con_platform.h"
#include "console.h"
#include "uart_dev.h"

#define LOGBUFSZ 4096
#define CMDBUFSZ 1024

void uartfile_starttx(struct console * con);
unsigned int con_rx_char(char *ch);

struct uart_ldisc con_ldisc;

struct console uartfile_con =
{
	.name = "uartfilecon",
	.data = &con_ldisc,
	.start_tx = uartfile_starttx,
	.start_shell = shell_start,
	.coreid = CON_CCORE,
	.inflags = CON_INFLG_UART,
	.icchn = NULL,
	.predecessor = NULL
};
struct uart_ldisc con_ldisc =
{
	.bind_con = &uartfile_con
};

static unsigned char cmdbuf[CMDBUFSZ] = {0};
static unsigned char logbuf[LOGBUFSZ] = {0};
struct semaphore recv_tsk_sem;

int send_cmd_ccore(char* func_name, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
#define TMP_CMD_BUF_SIZE 256
	static unsigned char tmp_cmd_buf[TMP_CMD_BUF_SIZE];

	if((strlen(func_name) - 1) >  (TMP_CMD_BUF_SIZE - 6 * 9 - 1 - 2))
	{
		printk("[ACSHELL] func_name is too long\n");
		return -1;
	}

	memset(tmp_cmd_buf, 0, TMP_CMD_BUF_SIZE);
	snprintf(tmp_cmd_buf, TMP_CMD_BUF_SIZE, "%s 0x%X,0x%X,0x%X,0x%X,0x%X,0x%X\r\n", func_name + 1, arg1, arg2, arg3, arg4, arg5, arg6);

	return con_ldisc.bind_con->rx(con_ldisc.bind_con, (unsigned char *)tmp_cmd_buf, strlen(tmp_cmd_buf));
}
EXPORT_SYMBOL(send_cmd_ccore);

void uartfile_starttx(struct console * con)
{
	up(&recv_tsk_sem);
}

int uartfile_log_recv_func(void * data)
{
	static unsigned char tmpbuf[1024] = {0,};
	int len = 0;

	/* coverity[no_escape] */
	while(1)
	{
		down(&recv_tsk_sem);

		len = 0;
		while(((len < (sizeof(tmpbuf) - 1))) && (con_ldisc.bind_con->tx(con_ldisc.bind_con, &tmpbuf[len], 1) > 0))
		{
			if('\n' == tmpbuf[len])
			{
				tmpbuf[++len] = 0;
				printk("%s", tmpbuf);
				len = 0;
			}
			else
			{
				len++;
			}
		}
	}

	return 0;
}

int uart_dev_init(void)
{
	struct task_struct * tsk_hdl = NULL;

	sema_init(&recv_tsk_sem, 0);
	con_ring_init(&uartfile_con.logbuf, logbuf, LOGBUFSZ);
	con_ring_init(&uartfile_con.cmdbuf, cmdbuf, CMDBUFSZ);
	con_register(&uartfile_con);
	tsk_hdl = kthread_run(uartfile_log_recv_func, NULL, "uartfile_recv_thread");

	return 0;
}

module_init(uart_dev_init);
