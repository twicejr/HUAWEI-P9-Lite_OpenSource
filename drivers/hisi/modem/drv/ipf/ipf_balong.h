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

#ifndef _IPF_BALONG_H_
#define _IPF_BALONG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mdrv_ipf.h"
#include "mdrv_sysboot_commmon.h"
#include "bsp_ipf.h"
#include <linux/memblock.h>

#ifndef CONFIG_IPF_PROPERTY_MBB
#include "global_ddr_map.h"
#define MODEM_START_ADDR	HISI_RESERVED_MODEM_PHYMEM_BASE
#define MODEM_START_SIZE	HISI_RESERVED_MODEM_PHYMEM_SIZE
#else
#define MODEM_START_ADDR	DDR_MCORE_ADDR
#define MODEM_START_SIZE	DDR_MCORE_SIZE
#endif

#define IPF_ULADQ_PLEN_TH                 404
#define IPF_ADQ_RESERVE_NUM                 3
/* IPF transfer time recorder start */
#define IPF_MAX_STAMP_ORDER             32
#define IPF_MAX_TIME_LIMIT              (19200000*10)
#define IPF_FLS_MASK                    (31)
#define IPF_PWC_DOWN                    (0)
#define PERI_CRG_4K						0x00001000

//#define CONFIG_MODULE_BUSSTRESS

typedef struct tagIPF_TIMESTAMP_INFO_S
{
    unsigned int diff_order_cnt[IPF_MAX_STAMP_ORDER];
    unsigned int cnt_sum;
    unsigned int diff_sum;
    unsigned int diff_max;
    unsigned int overflow;
}IPF_TIMESTAMP_INFO_S;


typedef struct tagIPF_MATCH_INFO_S{
    unsigned char u8SrcAddr[16];
    unsigned char u8DstAddr[16];
    unsigned char u8DstMsk[16];
    union{
        struct{
        	unsigned int u16SrcPortLo:16;
        	unsigned int u16SrcPortHi:16;
        }Bits;
	    unsigned int u32SrcPort;
    } unSrcPort;
    union{
        struct
        {
            unsigned int u16DstPortLo:16;
        	unsigned int u16DstPortHi:16;
        }Bits;
    	unsigned int u32DstPort;
    } unDstPort;
    union{
        struct
        {
            unsigned int u8TrafficClass:8;
        	unsigned int u8TrafficClassMask:8;
        	unsigned int u16Reserve:16;
        }Bits;
    	unsigned int u32TrafficClass;
    }unTrafficClass;
    unsigned int u32LocalAddressMsk;
    union{
    	unsigned int u32NextHeader;
    	unsigned int u32Protocol;
    }unNextHeader;
    unsigned int u32FlowLable;
    union{
        struct{
            unsigned int u16Type:16;
        	unsigned int u16Code:16;
        }Bits;
    	unsigned int u32CodeType;
    } unFltCodeType;
    union{
        struct{
            unsigned int u16NextIndex:16;
        	unsigned int u16FltPri:16;
        }Bits;
    	unsigned int u32FltChain;
    } unFltChain;
    unsigned int u32FltSpi;
    union{
    	struct{
    		unsigned int FltEn:1;
    		unsigned int FltType:1;
    		unsigned int Resv1:2;
            unsigned int FltSpiEn:1;
            unsigned int FltCodeEn:1;
            unsigned int FltTypeEn:1;
            unsigned int FltFlEn:1;
            unsigned int FltNhEn:1;
            unsigned int FltTosEn:1;
            unsigned int FltRPortEn:1;
            unsigned int FltLPortEn:1;
            unsigned int FltRAddrEn:1;
            unsigned int FltLAddrEn:1;
            unsigned int Resv2:2;
            unsigned int FltBid:6;
            unsigned int Resv3:10;
    	}Bits;
    	unsigned int u32FltRuleCtrl;
    }unFltRuleCtrl;
}IPF_MATCH_INFO_S;

typedef struct tagIPF_FILTER_CONFIG_S
{
    unsigned int u32FilterID;
    IPF_MATCH_INFO_S stMatchInfo;
} IPF_FILTER_CONFIG_S;

typedef struct tagIPF_PWRCTL_FILTER_INFO_S
{
	unsigned int u32Flag;
	IPF_CHANNEL_TYPE_E eChnType;
	unsigned int u32FilterNum;
	IPF_FILTER_CONFIG_S *pstFilterInfo;
}IPF_PWRCTL_FILTER_INFO_S;


typedef struct ipf_ctx {
	void * regs;
    unsigned int irq;
	struct device *dev;
	struct clk *clk;
	void*	bd_phy;
	void*	bd_virt;
	void*	cd_virt;
	void*	cd_phy;
	void*	rd_virt;
	void*	rd_phy;
	void*	ad_phy[IPF_AD_MAX];
	void*	ad_virt[IPF_AD_MAX];
	unsigned int ipf_version;
	IPF_LIMIT_ADDR_S *limit_addr;
	struct ipf_debug* status;
	unsigned int ipf_rst_leave;
	unsigned int not_get_space;
} ipf_ctx_t;

static __inline__ unsigned int ipf_readl(void *addr)
{
    return readl(addr);
}
static __inline__ void ipf_writel(unsigned int val, void *addr)
{
    writel(val, addr);
}
/*ipf test file needs these fucs*/
int ipf_init(void);
int bsp_ipf_set_pktlen(unsigned int u32MaxLen, unsigned int u32MinLen);
void bsp_ipf_help(void);
int bsp_ipf_dump_bdinfo(IPF_CHANNEL_TYPE_E eChnType);
int bsp_ipf_dump_rdinfo(IPF_CHANNEL_TYPE_E eChnType);
int bsp_ipf_dump_adinfo(IPF_CHANNEL_TYPE_E eChnType, unsigned int u32AdType);
int bsp_ipf_info(IPF_CHANNEL_TYPE_E eChnType);
void bsp_ipf_mem(void);
int bsp_ipf_config_timeout(unsigned int u32Timeout);
int ipf_register_wakeup_dlcb(BSP_IPF_WakeupDlCb pFnWakeupDl);
int ipf_register_ul_bd_empty(ipf_bd_empty bd_handle);
void bsp_ipf_set_control_flag_for_ccore_reset(IPF_FORRESET_CONTROL_E eResetFlag);
unsigned long bsp_ipf_ad0_info(unsigned long * ad0_addr);
unsigned long bsp_ipf_ad1_info(unsigned long * ad1_addr);
int bsp_ipf_reset_ccore_cb(DRV_RESET_CB_MOMENT_E eparam, int userdata);

#ifdef __cplusplus
}
#endif

#endif /*s_IPC_BALONG_H_*/

