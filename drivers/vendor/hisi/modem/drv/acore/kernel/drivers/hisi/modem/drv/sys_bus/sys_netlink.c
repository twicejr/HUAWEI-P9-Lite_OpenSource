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
#include <net/sock.h>
#include <linux/wait.h>
#include <linux/skbuff.h>
#include <linux/netlink.h>

#define NETLINK_TEST		22

struct sock *sys_nl_sock;


DEFINE_MUTEX(sys_nl_mutex);

void sys_send_msg(u32 pid)
{
    struct sk_buff *skb;
    struct nlmsghdr *nlhdr;
    int ret;
    char str[100] = "hello app\n";

    skb = alloc_skb(NLMSG_SPACE(1024), GFP_ATOMIC);
    if(!skb)
    {
        printk("%s allocate failed\n", __func__);
        return;
    }

    nlhdr = nlmsg_put(skb,0,0,0,1024,0);
    NETLINK_CB(skb).portid = 0;
    memcpy(NLMSG_DATA(nlhdr), str, sizeof(str));
    printk("kernel going to send\n");

    ret = netlink_unicast(sys_nl_sock, skb, pid, MSG_DONTWAIT);
    if(ret < 0)
    {
        printk("kernel cannot unicast skb\n");
        return;
    }
    printk("kernel send is ok\n");
}


void sys_rcv_msg (struct sk_buff *skb)
{
    struct nlmsghdr *nlh;
    int type;
    char *data;
    u32 pid;

    printk("skb len:%d\n",skb->len);

    /* 获取 netlink 消息 */
    nlh = nlmsg_hdr(skb);

    /* 检查 netlink 消息是否合法 */
    if (!NLMSG_OK(nlh, skb->len))
    {
        printk("wrong skb len:%d\n", skb->len);
        return;
    }

    type = nlh->nlmsg_type;
    printk("message type : %d\n", type);

    switch(type)
    {
        case 12:
            data = nlmsg_data(nlh);
            printk("kernel rcv : %s: %s\n", __func__, data);

            //send back
            pid = nlh->nlmsg_pid;
            sys_send_msg(pid );
            //NETLINK_CB(skb).portid = nlh->nlmsg_pid;
            //NETLINK_CB(skb).dst_group = 1;/* unicast */
            //netlink_unicast(sys_nl_sock, skb, pid, 0);
            //printk("kernel send ok\n");
            break;
        default:
            printk("type error\n");
            break;
    }
    kfree_skb(skb);
    printk("sys_rcv_msg end\n");
}


static void sys_nl_rcv_msg(struct sk_buff *skb)
{
	printk("sys nl rcv msg\n");
    mutex_lock(&sys_nl_mutex);
    sys_rcv_msg(skb);
    mutex_unlock(&sys_nl_mutex);
}

struct netlink_kernel_cfg sys_cfg = {
    .input  = sys_nl_rcv_msg,
};

static int __init sys_netlink_init(void)
{
    sys_nl_sock = netlink_kernel_create(&init_net, NETLINK_TEST, &sys_cfg);
    if (!sys_nl_sock)
    {
		return -1;
    }
    return 0;
}

module_init(sys_netlink_init);
