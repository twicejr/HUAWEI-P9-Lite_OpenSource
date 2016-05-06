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
#include <linux/string.h>
#include <linux/kallsyms.h>
#include <linux/tty.h>
#include <product_config.h>
#include <bsp_cshell.h>

#define ES_TTY_MAJOR		220
#define ES_TTY_MINORS		1
#define ES_TTY_IOCTL_SIGN	0xCAFA0000
#define ES_TTY_IOCTL_CALL	0xCAFA0001
#define VALID_SIGN(tty_termios)	((ES_TTY_MAJOR<<24) | C_BAUD(tty_termios))

typedef struct shell_tty_call_arg {
	int sign_word;
	char *func_name;
	union {
		int args[6];
		struct {
			int arg1;
			int arg2;
			int arg3;
			int arg4;
			int arg5;
			int arg6;
		};
	};
}shell_tty_call_arg, *p_shell_tty_call_arg;

typedef int (*call_ptr)(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);

static struct tty_driver *shell_tty_drv;
static struct tty_port shell_tty_port;
static int shell_call(char* func_name, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);

static int shell_open(struct tty_struct *tty, struct file *filp)
{
	return 0;
}

static void shell_close(struct tty_struct *tty, struct file *filp)
{

}

static int shell_ioctl(struct tty_struct *tty, unsigned int cmd, unsigned long arg)
{
	p_shell_tty_call_arg call_arg = NULL;

    printk(KERN_DEBUG "received shell ioctl cmd=0x%02x\n, arg=0x%02lx\n",cmd,arg);
        
	switch (cmd)
	{
	case ES_TTY_IOCTL_SIGN:
		return VALID_SIGN(tty);

	case ES_TTY_IOCTL_CALL:
		call_arg = (p_shell_tty_call_arg) arg;
		if (call_arg->sign_word & ~VALID_SIGN(tty)) {
			printk("Unallowed call\n");
			return -EPERM;
		}

		return shell_call(call_arg->func_name, 
				call_arg->arg1, 
				call_arg->arg2, 
				call_arg->arg3, 
				call_arg->arg4,
				call_arg->arg5,
				call_arg->arg6);

	default:
		printk("shell_ioctl unknown cmd\n");
		break;
	}

	return -ENOIOCTLCMD;
}

static struct tty_operations shell_ops = {
    .open  = shell_open,
    .close = shell_close,
    .ioctl = shell_ioctl,
};
static const struct tty_port_operations shell_port_ops = {
};


int shell_init(void ) //clean warning
{
	printk("Enter ecall init\n");

    shell_tty_drv = alloc_tty_driver(ES_TTY_MINORS);
    if (!shell_tty_drv) {
        printk("Cannot alloc shell tty driver\n");
        return -1;
    }

    shell_tty_drv->owner = THIS_MODULE;
    shell_tty_drv->driver_name = "es_serial";
    shell_tty_drv->name = "es_tty";
    shell_tty_drv->major = ES_TTY_MAJOR;
    shell_tty_drv->minor_start = 0;
    shell_tty_drv->type = TTY_DRIVER_TYPE_SERIAL;
    shell_tty_drv->subtype = SERIAL_TYPE_NORMAL;
    shell_tty_drv->flags = TTY_DRIVER_REAL_RAW;
    shell_tty_drv->init_termios = tty_std_termios;
    shell_tty_drv->init_termios.c_cflag = B921600 | CS8 | CREAD | HUPCL | CLOCAL;

	tty_set_operations(shell_tty_drv, &shell_ops);
	tty_port_init(&shell_tty_port);
	shell_tty_port.ops = &shell_port_ops;
	tty_port_link_device(&shell_tty_port, shell_tty_drv, 0);
    if (tty_register_driver(shell_tty_drv)) {
        printk("Error registering shell tty driver\n");
        put_tty_driver(shell_tty_drv);
        return -1;
    }

	printk("Finish ecall init\n");

	return 0;	
}

static int shell_call(char* func_name, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
	int result = -1;
	call_ptr address;

	if (!func_name)
		goto call_error_input;

#ifdef CONFIG_CSHELL
	if('^' == func_name[0])
	{
		return send_cmd_ccore(func_name, arg1, arg2, arg3, arg4, arg5, arg6);
	}
#endif

	address = (call_ptr) kallsyms_lookup_name(func_name);
	if (!address)
		goto call_no_symbol;

	result = address(arg1, arg2, arg3, arg4, arg5, arg6);

	printk("Call %s return, value = 0x%x\n", func_name, result);
	return result;

call_error_input:
	printk("Error input, value = -1\n");

call_no_symbol:
	printk("Invalid function, value = -1\n");
	return -1;
}

module_init(shell_init)
