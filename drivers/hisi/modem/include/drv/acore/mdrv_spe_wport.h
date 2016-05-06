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


#ifndef __MDRV_SPE_WPORT_H__
#define __MDRV_SPE_WPORT_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <linux/if_ether.h>
#include <linux/netdevice.h>

/* ioctl cmd code */
#define SPE_WPORT_IOCTL_SET_RX_CB       0xF001
#define SPE_WPORT_IOCTL_SET_MAC         0xF002
#define SPE_WPORT_IOCTL_SET_PUSH_CB     0xF003
#define SPE_WPORT_IOCTL_SET_RECYCLE_CB  0xF004
#define SPE_WPORT_IOCTL_DIAG_UPLOAD     0xF005

typedef struct spe_flow_stat_s
{
    u32 port_enable[SPE_PORT_NUM];
    u32 td_input_bps[SPE_PORT_NUM];
    u32 rd_output_bps[SPE_PORT_NUM];
	u32 td_ptr_a[SPE_PORT_NUM];
    u32 td_using_num[SPE_PORT_NUM];
	u32 rd_ptr_a[SPE_PORT_NUM];
    u32 rd_using_num[SPE_PORT_NUM];
	u32 td_ful_h[SPE_PORT_NUM];
	u32 td_empty_h[SPE_PORT_NUM];
	u32 rd_ful_h[SPE_PORT_NUM];
	u32 rd_empty_h[SPE_PORT_NUM];
	u32 td_ful_s[SPE_PORT_NUM];
	u32 rd_ful_s[SPE_PORT_NUM];
} spe_flow_stat_t;

/* macro tools */
#define mdrv_spe_set_skb_ipv4(skb)      ((skb)->protocol = htons(ETH_P_IP))
#define mdrv_spe_set_skb_ipv6(skb)      ((skb)->protocol = htons(ETH_P_IPV6))

/* used for ioctl cmd: SPE_WPORT_IOCTL_SET_RX_CB */
typedef void (*spe_wport_rx_cb_t)(int port, struct sk_buff *skb);

/* used for ioctl cmd: SPE_WPORT_IOCTL_SET_PUSH_CB */
typedef void (*spe_wport_push_cb_t)(void);

/* used for ioctl cmd: SPE_WPORT_IOCTL_SET_RECYCLE_CB */
typedef int (*spe_wport_recycle_cb_t)(struct sk_buff *skb);

/* used for mdrv_spe_wport_open */
typedef struct spe_wport_attr
{
    int is_bypass_mode;
    int is_ipf_port;
    struct net_device* net_dev;
} spe_wport_attr_t;


int mdrv_spe_wport_open(spe_wport_attr_t *attr);

void mdrv_spe_wport_close(int port);

int mdrv_spe_wport_xmit(int port, struct sk_buff *skb);

void mdrv_spe_wport_recycle(struct sk_buff *skb);

int mdrv_spe_wport_ioctl(int port, unsigned int cmd, void* param);

int mdrv_spe_usb_eth_is_bypass(int eth_id);


#ifdef __cplusplus
}
#endif
#endif/* __MDRV_SPE_WPORT_H__ */

