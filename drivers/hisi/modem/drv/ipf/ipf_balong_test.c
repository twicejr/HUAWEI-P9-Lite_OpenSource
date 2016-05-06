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

#ifdef __cplusplus
extern "C" {
#endif

#include "ipf_balong_test.h"

#define	AD_WPTR_MASK	0xff

unsigned char* g_ul_long_data = NULL;
unsigned char* g_ul_short_data = NULL;
unsigned int g_ul_packet_flag = 0;

unsigned int debug_test = 0;
#define IPF_TEST_PRINT(fmt,...)     \
do{\
	if(debug_test){\
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, fmt,##__VA_ARGS__);\
	}\
}while(0);

#define IPF_TEST_ERR(fmt,...)     \
do{\
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, fmt,##__VA_ARGS__);\
}while(0);

typedef enum tagIPF_ADQ_CONFIG_E
{
    CONFIG_AD = 0,
    STOP_CONFIG_AD = 1
}IPF_ADQ_CONFIG_E;

StreamIPv4Header ipf_ipv4_head;
StreamUDP ipf_udp;

IPF_ADQ_CONFIG_E ipf_config_ad_flag = CONFIG_AD;

static int ipf_dl_confirm = 0;
unsigned int g_u32DlError=0;
unsigned int g_u32DlFltError=0;
unsigned int g_u32DlTotalDataNum = 0;
unsigned int g_u32DlTotalBDNum = 0;
struct tagIPF_AD_DESC_S ADdlshort[IPF_DLAD0_DESC_SIZE];
struct tagIPF_AD_DESC_S ADdllong[IPF_DLAD1_DESC_SIZE];

int g_u32IpfStAllInit = 0;
int g_u32IpfStUlInit = 0;

int g_u32IpfStDlInit = 0;
static int acore_reset_ipf = 0;
static int acore_dl_test_init = 0;

int IPF_ST_DL_FlushAD(IPF_ADQ_EMPTY_E eAdqEmptyDl);

void ipf_test_debug_switch(unsigned int num)
{
	debug_test = num;
}

void ipf_set_acore_reset_flag(unsigned int flag)
{
	acore_reset_ipf = flag;
}

void ipf_ad_config_flag(IPF_ADQ_CONFIG_E flag)
{
	ipf_config_ad_flag = flag;
	if(STOP_CONFIG_AD == ipf_config_ad_flag)
	{
		IPF_TEST_PRINT("Stop adq config at this core. \n");
	}
	else
	{
		IPF_TEST_PRINT("Restore adq config at this core. \n");
		IPF_ST_DL_FlushAD(IPF_AD_0);
		IPF_ST_DL_FlushAD(IPF_AD_1);
	}
}

struct task_struct * g_IpfDlTaskId;
unsigned char  * g_pu8STDlData = NULL;

/*CH1为下行通道，故编到Acore*/
void print_CH1_BUFFED_AD_Num(void)
{
	HI_IPF_CH1_ADQ0_STAT_T ad0_stat;
	HI_IPF_CH1_ADQ1_STAT_T ad1_stat;
	ad0_stat.u32 = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_STAT_OFFSET);
	ad1_stat.u32 = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_STAT_OFFSET);

	if((ad0_stat.bits.dl_adq0_buf_epty == 1)&&(ad0_stat.bits.dl_adq0_buf_full == 1))
	{
		IPF_TEST_PRINT("\r CH1_AD0_BUF_FLAG_ERROR.\n");
	}
	else if(ad0_stat.bits.dl_adq0_buf_full == 1)
	{
		IPF_TEST_PRINT("\r CH1_AD0_BUF_NUM 2,2 unused AD in AD_Buff.\n");
	}
	else if(ad0_stat.bits.dl_adq0_buf_epty == 1)
	{
		IPF_TEST_PRINT("\r CH1_AD0_BUF_NUM 0,0 unused AD in AD_Buff.\n");
	}
	else
	{
		IPF_TEST_PRINT("\r CH1_AD0_BUF_NUM 1,1 unused AD in AD_Buff.\n");
	}
	
	if((ad1_stat.bits.dl_adq1_buf_epty == 1)&&(ad1_stat.bits.dl_adq1_buf_full == 1))
	{
		IPF_TEST_PRINT("\r CH1_AD1_BUF_FLAG_ERROR.\n");
	}
	else if(ad1_stat.bits.dl_adq1_buf_full == 1)
	{
		IPF_TEST_PRINT("\r CH1_AD1_BUF_NUM 2,2 unused AD in AD_Buff.\n");
	}
	else if(ad1_stat.bits.dl_adq1_buf_epty == 1)
	{
		IPF_TEST_PRINT("\r CH1_AD1_BUF_NUM 0,0 unused AD in AD_Buff.\n");
	}
	else
	{
		IPF_TEST_PRINT("\r CH1_AD1_BUF_NUM 1,1 unused AD in AD_Buff.\n");
	}
	return;
}

int CmpDMAData(unsigned int* p1, unsigned int* p2, unsigned int u32Len)
{
    unsigned int i = 0;
    for(i=0; i<u32Len/sizeof(unsigned int); i++)
    {
        if(*(unsigned int*)(p1+i) != *(unsigned int*)(p2+i))
        {
            return ERROR;
        }
    }
    return 0;
}

unsigned int get_ul_ip_pkt(void)
{
	unsigned int long_len;
	unsigned int short_len;
	StreamIPv4Header stIPHeader;
	StreamUDP stUDP;
	long_len = LONG_DATA;
	short_len = SHORT_DATA;
	g_ul_short_data = (unsigned char*)kmalloc(short_len,GFP_KERNEL);
    if(g_ul_short_data == NULL)
    {
        IPF_TEST_ERR("malloc failed :%d\n",__LINE__);
        return ERROR;
    }
	g_ul_long_data = (unsigned char*)kmalloc(long_len,GFP_KERNEL);
    if(g_ul_long_data == NULL)
    {
        IPF_TEST_ERR("malloc failed :%d\n",__LINE__);
        return ERROR;
    }
	stIPHeader.Vers = 4;
    stIPHeader.HeaderLen = 5;
    stIPHeader.TOS = 3;
    stIPHeader.TOL = short_len;
    stIPHeader.ID = 1;
    stIPHeader.ReservFlag = 0;
    stIPHeader.DF = 0;
    stIPHeader.MF = 0;
    stIPHeader.offset = 0;
    stIPHeader.TTL = 128;
    stIPHeader.Prot = 17; /* UDP */
    stIPHeader.Checksum = 0x438C;
    stIPHeader.SourceAddr = 0xACA84649;
    stIPHeader.DestAddr = 0x0202014E;
    stUDP.SrcPort = 5088;
    stUDP.DstPort = 2923;
    stUDP.Checksum = 0;
    stUDP.Length = stIPHeader.TOL - sizeof(StreamIPv4Header);
	memset(g_ul_short_data, T_UL_VALUE, short_len);
    memcpy(g_ul_short_data, &stIPHeader, sizeof(StreamIPv4Header));
    memcpy(g_ul_short_data + sizeof(StreamIPv4Header), &stUDP, sizeof(StreamUDP));	
	stIPHeader.TOL = long_len;
	stUDP.Length = stIPHeader.TOL - sizeof(StreamIPv4Header);
	stIPHeader.Checksum = 0x3EDC;
	memset(g_ul_long_data, T_UL_VALUE, long_len);
    memcpy(g_ul_long_data, &stIPHeader, sizeof(StreamIPv4Header));
    memcpy(g_ul_long_data + sizeof(StreamIPv4Header), &stUDP, sizeof(StreamUDP));
	return IPF_SUCCESS;
}

int free_ul_ip_pkt(void)
{
	if(g_ul_short_data != NULL)
	{
		kfree(g_ul_short_data);
		g_ul_short_data = NULL;
	}

	if(g_ul_long_data != NULL)
	{
		kfree(g_ul_long_data);
		g_ul_long_data = NULL;
	}

	g_ul_packet_flag = 0;

	if(g_pu8STDlData != NULL){
		kfree(g_pu8STDlData);
		g_pu8STDlData = NULL;
	}
	return IPF_SUCCESS;
}

int IpfDlIntSTCb(void)
{
    print_CH1_BUFFED_AD_Num();
    return OK;
}

/*用于验证AD_BUFF的有效性*/
int IpfDlIntCb300(void)
{
	unsigned int u32AD0Num;
	unsigned int u32AD1Num;
	unsigned int u32Num = IPF_DLRD_DESC_SIZE;
	IPF_RD_DESC_S stRd[IPF_DLRD_DESC_SIZE];
	
	mdrv_ipf_get_dlrd(&u32Num, stRd);

	IPF_TEST_PRINT("Data transfer Num:%d \n",u32Num);
	
	print_CH1_BUFFED_AD_Num();

	mdrv_ipf_get_dlad_num(&u32AD0Num, &u32AD1Num);
	IPF_TEST_PRINT("Data transfer success! Num: %u \n AD0Num:%u AD1Num:%d \n",u32Num,u32AD0Num,u32AD1Num);
	
	IPF_TEST_ERR("Data transfer success\n");

    return OK;
}

int IpfDlIntCb301(void)
{
	unsigned int i,j;
	unsigned int u32AD0Num;
	unsigned int u32AD1Num;
	unsigned int u32Num = IPF_DLRD_DESC_SIZE;
	int s32Ret = 0;
	IPF_RD_DESC_S stRd[IPF_DLRD_DESC_SIZE];
	unsigned int* p = NULL;
	
	mdrv_ipf_get_dlrd(&u32Num, stRd);

	IPF_TEST_PRINT("Data transfer Num:%d \n",u32Num);
	
	for(j = 0; j < u32Num; j++)
	{	
		if(NULL == (unsigned int *)stRd[j].u32OutPtr)
		{
			return ERROR;
		}
		s32Ret = CmpDMAData((unsigned int *)g_pu8STDlData, (unsigned int *)(phys_to_virt(stRd[j].u32OutPtr)), stRd[j].u16PktLen);
		
		/*数据比对*/
		if(0 != s32Ret)
		{
		    IPF_TEST_ERR("\r Data transfer unmatch! Num:%d \n",j,0,0,0,0,0,0);
		    IPF_TEST_PRINT("Comp error \n");
		    IPF_TEST_PRINT("g_pu8STDlData\n");
		    IPF_TEST_PRINT("===================================\n");
		    p=(unsigned int *)g_pu8STDlData;
		    for(i=0; i<25; i++)
		    {
		        IPF_TEST_PRINT("0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
		        i = i+4;
		    }
		    IPF_TEST_PRINT("0x%08x    0x%08x\n", *(p+i), *(p+i+1));
		    IPF_TEST_PRINT("stRd[%d].u32OutPtr\n",j);
            IPF_TEST_PRINT("===================================\n");
            IPF_TEST_PRINT("stRd[%d].u32OutPtr =%x\n",j,stRd[j].u32OutPtr);
		    p=(unsigned int *)phys_to_virt(stRd[j].u32OutPtr);
		    for(i=0; i<25; i++)
		    {
		        IPF_TEST_PRINT("0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
		        i = i+4;
		    }
		    IPF_TEST_PRINT("0x%08x    0x%08x\n", *(p+i), *(p+i+1));
			ipf_dl_confirm = ERROR;
		}			
	}

	mdrv_ipf_get_dlad_num(&u32AD0Num, &u32AD1Num);
	IPF_TEST_PRINT("Data transfer success! Num: %d \n AD0Num:%d AD1Num:%d \n",j,u32AD0Num,u32AD1Num);
	IPF_TEST_ERR("Data transfer success!\n");

    return OK;
}

int IpfDlIntCb302(void)
{
	unsigned int i,j;
	unsigned int u32AD0Num;
	unsigned int u32AD1Num;
	unsigned int u32Num = IPF_DLRD_DESC_SIZE;
	int s32Ret = 0;
	unsigned int origin_flag = 0;
	IPF_RD_DESC_S stRd[IPF_DLRD_DESC_SIZE];
	
	mdrv_ipf_get_dlrd(&u32Num, stRd);

	IPF_TEST_PRINT("Data transfer Num:%d \n",u32Num);
	
	for(j = 0; j < u32Num; j++)
	{	
		IPF_TEST_PRINT("stRd[%d].u32OutPtr =%x stRd[%d].u16PktLen =%u \n",j,stRd[j].u32OutPtr,j,stRd[j].u16PktLen);
		if(NULL == (unsigned int *)stRd[j].u32OutPtr)
		{
			IPF_TEST_ERR("stRd[%d].u32OutPtr =NULL !\n",j);
			return ERROR;
		}
		s32Ret = CmpDMAData((unsigned int *)g_pu8STDlData, (unsigned int *)(phys_to_virt(stRd[j].u32OutPtr)), stRd[j].u16PktLen);
		
		/*数据比对*/
		if(0 != s32Ret)
		{
			if(!origin_flag) {
				IPF_TEST_ERR("Comp error \n");
				IPF_TEST_PRINT("=============g_pu8STDlData============\n");
				print_hex_dump(KERN_ERR,"g_pu8STDlData: ", DUMP_PREFIX_NONE, 16,
						4,(void *)g_pu8STDlData, stRd[j].u16PktLen, false);
				IPF_TEST_PRINT("==================END=================\n");
				origin_flag = 1;
			} 
			IPF_TEST_PRINT("=============stRd[%d].u32OutPtr============\n", j);
			print_hex_dump(KERN_ERR,"u32OutPtr: ", DUMP_PREFIX_NONE, 16, 
				4,(void *)(phys_to_virt(stRd[j].u32OutPtr)), stRd[j].u16PktLen,  false);
			IPF_TEST_PRINT("==================END=================\n");
		    IPF_TEST_PRINT("Comp error \n");
		    IPF_TEST_PRINT("g_pu8STDlData\n");
		    IPF_TEST_PRINT("===================================\n");
			unsigned int *p;
		    p=(unsigned int *)g_pu8STDlData;
		    for(i=0; i<200; i++)
		    {
		        IPF_TEST_PRINT("0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
		        i = i+4;
		    }
		    IPF_TEST_PRINT("0x%08x    0x%08x\n", *(p+i), *(p+i+1));
		    IPF_TEST_PRINT("stRd[%d].u32OutPtr\n",j);
            IPF_TEST_PRINT("===================================\n");
            IPF_TEST_PRINT("stRd[%d].u32OutPtr =%x\n",j,stRd[j].u32OutPtr);
		    p=(unsigned int *)phys_to_virt(stRd[j].u32OutPtr);
		    for(i=0; i<200; i++)
		    {
		        IPF_TEST_PRINT("0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
		        i = i+4;
		    }
		    IPF_TEST_PRINT("0x%08x    0x%08x\n", *(p+i), *(p+i+1));
            g_u32DlError++;
			ipf_dl_confirm = ERROR;
		}			
	}

	mdrv_ipf_get_dlad_num(&u32AD0Num, &u32AD1Num);
	IPF_TEST_PRINT("Data transfer success! Num: %d \n AD0Num:%d AD1Num:%d \n",j,u32AD0Num,u32AD1Num);
	IPF_TEST_ERR("Data transfer success!\n");

	return OK;
}

int IpfDlIntCb304(void)
{
	unsigned int j;
	unsigned int u32AD0Num;
	unsigned int u32AD1Num;
	unsigned int u32Num = IPF_DLRD_DESC_SIZE;
	IPF_RD_DESC_S stRd[IPF_DLRD_DESC_SIZE];
	
	mdrv_ipf_get_dlrd(&u32Num, stRd);

	IPF_TEST_PRINT("Data transfer Num:%d \n",u32Num);
	
	for(j = 0; j < u32Num; j++)
	{	
		/*过滤结果*/
		if(stRd[j].u16Result == 0x3f)
		{
			IPF_TEST_ERR("stRd[%d].u16Result ERROR ! value is 0x%x \n",j,stRd[j].u16Result);
			g_u32DlError++;
			ipf_dl_confirm = ERROR;
		}			
	}

	mdrv_ipf_get_dlad_num(&u32AD0Num, &u32AD1Num);
	
	IPF_TEST_PRINT("Data transfer success! Num: %d \n AD0Num:%d AD1Num:%d \n",j,u32AD0Num,u32AD1Num);
	IPF_TEST_ERR("Data transfer success!\n");
    return OK;
}

int IpfDltestIntCb(void)
{
    unsigned int u32Num = IPF_DLRD_DESC_SIZE;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int u32RecivedData = 0;
    unsigned int u32AD0Num = 0;
    unsigned int u32AD1Num = 0;
    int s32Ret = 0;
    unsigned int *p = NULL;
    IPF_RD_DESC_S stRd[IPF_DLRD_DESC_SIZE];
    unsigned int	u32AD0wptr;
    unsigned int	u32AD1wptr;
	/*处理RD*/
    mdrv_ipf_get_dlrd(&u32Num, stRd);
#if 1
    for(j = 0; j < u32Num; j++)
    {	
	    /*IPF_TEST_PRINT("stRd[%d].u32OutPtr =%x stRd[%d].u16PktLen =%u \n",j,stRd[j].u32OutPtr,j,stRd[j].u16PktLen);*/
		dma_map_single(g_ipf_ctx.dev, phys_to_virt(stRd[j].u32OutPtr), stRd[j].u16PktLen, DMA_FROM_DEVICE);

		if(0 == stRd[j].u32OutPtr)
		{
			IPF_TEST_ERR("stRd[%d].u32OutPtr =%x !return ERROR\n",j,stRd[j].u32OutPtr);
			return ERROR;
		}
		s32Ret = CmpDMAData((unsigned int *)g_pu8STDlData, (unsigned int *)(phys_to_virt(stRd[j].u32OutPtr)), stRd[j].u16PktLen);
		u32RecivedData += stRd[j].u16PktLen;
		/*数据比对*/
		if(0 != s32Ret)
		{
			g_u32DlError++;
			/*if(0 == g_u32DlError%2247)*/
			if(0)
			{
			    IPF_TEST_PRINT("g_pu8STDlData,u32Num = %u\n",u32Num);
			    IPF_TEST_PRINT("===================================\n");
			    p=(unsigned int *)g_pu8STDlData;
			    for(i=0; i<4; i++)
			    {
			        IPF_TEST_PRINT("0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
			        i = i+4;
			    }
			    IPF_TEST_PRINT("0x%08x    0x%08x\n", *(p+i), *(p+i+1));
                IPF_TEST_PRINT("Err stRd[%d].u32OutPtr =%x\n",j,stRd[j].u32OutPtr);
                IPF_TEST_PRINT("===================================\n");
			    p=phys_to_virt(stRd[j].u32OutPtr);
				
			    for(i=0; i<4; i++)
			    {
			        IPF_TEST_PRINT("0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
			        i = i+4;
			    }
			    IPF_TEST_PRINT("0x%08x    0x%08x\n", *(p+i), *(p+i+1));
			}
		}
		if(stRd[j].u16Result == 0x3f)
		{
			g_u32DlFltError++;
		}	
    }
#endif
	u32RecivedData = u32RecivedData/1024;
	/*统计结果*/
	g_u32DlTotalDataNum += u32RecivedData;
	g_u32DlTotalBDNum += u32Num;
	s32Ret = mdrv_ipf_get_dlad_num(&u32AD0Num,&u32AD1Num);

	if(IPF_SUCCESS != s32Ret)
	{
		IPF_TEST_ERR(" mdrv_ipf_get_dlad_num :%d\n",__LINE__);
	}
	
    if(u32AD0Num > 10)
    {
		u32AD0wptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_WPTR_OFFSET );
		if((IPF_ULAD0_DESC_SIZE -u32AD0wptr) >= u32AD0Num)
		{
	    	s32Ret = mdrv_ipf_config_dlad(IPF_AD_0,u32AD0Num,&ADdlshort[u32AD0wptr]);
	        if(IPF_SUCCESS != s32Ret)
			{
				IPF_TEST_ERR("BSP_IPF_ConfigUlAd0 :%d\n",__LINE__);
			}
		}
		else
		{
			s32Ret = mdrv_ipf_config_dlad(IPF_AD_0,(IPF_ULAD0_DESC_SIZE-u32AD0wptr),&ADdlshort[u32AD0wptr]);
			if(IPF_SUCCESS != s32Ret)
			{
				IPF_TEST_ERR("BSP_IPF_ConfigUlAd0 :%d\n",__LINE__);
			}
			s32Ret = mdrv_ipf_config_dlad(IPF_AD_0,(u32AD0Num-(IPF_ULAD0_DESC_SIZE-u32AD0wptr)),&ADdlshort[0]);
			if(IPF_SUCCESS != s32Ret)
			{
				IPF_TEST_ERR("BSP_IPF_ConfigUlAd0 :%d\n",__LINE__);
			}
		}
    }
    if(u32AD1Num > 10)
    {
		u32AD1wptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_WPTR_OFFSET );
		if((IPF_DLAD1_DESC_SIZE-u32AD1wptr) >= u32AD1Num)
		{
			s32Ret = mdrv_ipf_config_dlad(IPF_AD_1,u32AD1Num,&ADdllong[u32AD1wptr]);
			if(IPF_SUCCESS != s32Ret)
			{
				IPF_TEST_ERR(" BSP_IPF_ConfigUlAd1 :%d\n",__LINE__);
				IPF_TEST_ERR(" u32AD1Num = %u   u32AD1wptr = %u \n",u32AD1Num,u32AD1wptr);
			    return ERROR;
			}
		}
		else
		{
			s32Ret = mdrv_ipf_config_dlad(IPF_AD_1,(IPF_DLAD1_DESC_SIZE-u32AD1wptr),&ADdllong[u32AD1wptr]);
			if(IPF_SUCCESS != s32Ret)
			{
				IPF_TEST_ERR("BSP_IPF_ConfigUlAd1 :%d\n",__LINE__);
				return ERROR;
			}
			s32Ret = mdrv_ipf_config_dlad(IPF_AD_1,(u32AD1Num-(IPF_DLAD1_DESC_SIZE-u32AD1wptr)),&ADdllong[0]);
			if(IPF_SUCCESS != s32Ret)
			{
				IPF_TEST_ERR("BSP_IPF_ConfigUlAd1 :%d\n",__LINE__);
				return ERROR;
			}
		}
    }
	return OK;
}

int IPF_ST_DL_FlushAD(IPF_ADQ_EMPTY_E eAdqEmptyDl)
{
	int s32Ret;  
	if(CONFIG_AD !=  ipf_config_ad_flag)
	{
		return OK;
	}
	if(IPF_EMPTY_ADQ0 == eAdqEmptyDl)
	{
		s32Ret = mdrv_ipf_config_dlad(IPF_AD_0,IPF_DLAD0_DESC_SIZE-IPF_ADQ_RESERVE_NUM,&ADdlshort[0]);
		if(s32Ret != IPF_SUCCESS)
		{
			IPF_TEST_ERR("IPF_ST_UL_FlashAD :%d s32ret = %x\n",__LINE__, s32Ret);
			return ERROR;
		}
	}
	else if(IPF_EMPTY_ADQ1 == eAdqEmptyDl)
	{
		s32Ret = mdrv_ipf_config_dlad(IPF_AD_1,IPF_DLAD1_DESC_SIZE-IPF_ADQ_RESERVE_NUM,&ADdllong[0]);
		if(s32Ret != IPF_SUCCESS)
		{
			IPF_TEST_ERR("IPF_ST_UL_FlashAD :%d s32ret = %x\n",__LINE__, s32Ret);
			return ERROR;
		}
	}
	else
	{
		return ERROR;
	}
	return OK;
}

int IPF_ST_DL_FlushOneAD(unsigned int AD0Num, unsigned int AD1Num)
{
    int s32Ret;  
    if(CONFIG_AD !=  ipf_config_ad_flag)
    {
        return OK;
    }

    s32Ret = mdrv_ipf_config_dlad(IPF_AD_0,AD0Num,&ADdlshort[0]);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("TEST ERROR mdrv_ipf_config_dlad :%d s32ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

    s32Ret = mdrv_ipf_config_dlad(IPF_AD_1,AD1Num,&ADdllong[0]);

	if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("TEST ERROR BSP_IPF_ConfigUlAd:%d s32ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }
	return OK;
}


int IPF_ST_DL_ACore_INIT(void)
{
	int s32Ret;
	unsigned int i;
	void * p_vir_addr;

	if(acore_dl_test_init){
		return OK;
	}
	
	ipf_ipv4_head.Vers = 4;
    ipf_ipv4_head.HeaderLen = 5;
    ipf_ipv4_head.TOS = 3;
    ipf_ipv4_head.TOL = 1000;
    ipf_ipv4_head.ID = 1;
    ipf_ipv4_head.ReservFlag = 0;
    ipf_ipv4_head.DF = 0;
    ipf_ipv4_head.MF = 0;
    ipf_ipv4_head.offset = 0;
    ipf_ipv4_head.TTL = 128;
    ipf_ipv4_head.Prot = 17; /* UDP */
    ipf_ipv4_head.Checksum = 0xEC3A;
    ipf_ipv4_head.SourceAddr = 0xACA84649;
    ipf_ipv4_head.DestAddr = 0x0202014E;

    ipf_udp.SrcPort = 5088;
    ipf_udp.DstPort = 2923;
    ipf_udp.Checksum = 0;
    ipf_udp.Length = ipf_ipv4_head.TOL;

	if(!acore_reset_ipf){
		s32Ret = bsp_ipf_srest();
		if(s32Ret != IPF_SUCCESS){
			IPF_TEST_ERR(" TESTERROR    bsp_ipf_srest :%d s32Ret = %x\n",__LINE__, s32Ret);
			return IPF_ERROR;
		}
		else{
			acore_reset_ipf = 1;
		}
	}

	for(i=0; i < (IPF_DLAD0_DESC_SIZE - IPF_ADQ_RESERVE_NUM); i++)
	{    	
		p_vir_addr = kmalloc(438, GFP_KERNEL); 
		if(p_vir_addr == NULL)
		{
			IPF_TEST_ERR(" malloc failed:%d\n",__LINE__);
			goto error1;
		}
		
		memset(p_vir_addr,0x0,438);
		ADdlshort[i].u32OutPtr0 = (unsigned int)dma_map_single(g_ipf_ctx.dev, p_vir_addr, 438, DMA_FROM_DEVICE);
		ADdlshort[i].u32OutPtr1 = ADdlshort[i].u32OutPtr0;
	}
	
	for(i=0; i < (IPF_DLAD1_DESC_SIZE - IPF_ADQ_RESERVE_NUM); i++)
	{
		p_vir_addr = kmalloc(1500, GFP_KERNEL);  
		if(p_vir_addr == NULL)
		{
			IPF_TEST_ERR(" malloc failed:%d\n",__LINE__);
			goto error2;
		}
		
		memset(p_vir_addr,0x0,1500);
		ADdllong[i].u32OutPtr0 = (unsigned int)dma_map_single(g_ipf_ctx.dev, p_vir_addr ,1500,DMA_FROM_DEVICE);        
    	ADdllong[i].u32OutPtr1 = ADdllong[i].u32OutPtr0;   
	}
	
	s32Ret = mdrv_ipf_config_dlad(IPF_AD_0,IPF_DLAD0_DESC_SIZE-IPF_ADQ_RESERVE_NUM,&ADdlshort[0]);
	if(s32Ret != IPF_SUCCESS)
	{
		IPF_TEST_ERR("mdrv_ipf_config_dlad :%d s32Ret = %x\n",__LINE__, s32Ret);
		return IPF_ERROR;
	}    
	s32Ret = mdrv_ipf_config_dlad(IPF_AD_1,IPF_DLAD1_DESC_SIZE-IPF_ADQ_RESERVE_NUM,&ADdllong[0]);
	if(s32Ret != IPF_SUCCESS)
	{
		IPF_TEST_ERR("mdrv_ipf_config_dlad :%d s32Ret = %x\n",__LINE__, s32Ret);
		return IPF_ERROR;
	}
	acore_dl_test_init = 1;
    return OK;

error1:
	do
	{
		i--;
		kfree(phys_to_virt(ADdlshort[i].u32OutPtr0));
	}while(i);
	return ERROR;

error2:
	do
	{
		i--;
		kfree(phys_to_virt(ADdllong[i].u32OutPtr0));
	}while(i);
	
	for(i=0; i < IPF_DLAD0_DESC_SIZE - IPF_ADQ_RESERVE_NUM; i++)
	{
		kfree(phys_to_virt(ADdlshort[i].u32OutPtr0));
	}
	return ERROR;
}

/****************************************
* 0   两核各自都用的测试用例
* 1   先执行M核后执行A核用例
* 2   C   核的测试用例
* 3   先执行A核后执行M核用例
* x2x   压力测试用例
****************************************/
/*检验是否Init成功*/
int  BSP_IPF_AINIT(void)
{
	int ret;
	IPF_TEST_PRINT("Start call acore init \n");
	ret = ipf_init();
	return ret;
}

/* test bsp_ipf_config_timeout */
int BSP_IPF_ST_config_timeout(void)
{
    unsigned int u32Timeout = 0;
    unsigned int u32OldTime = 0;
    int s32ret = 0;

    u32OldTime = ipf_readl(g_ipf_ctx.regs + HI_IPF_TIME_OUT_OFFSET);

    s32ret = bsp_ipf_config_timeout(u32Timeout);
    if(s32ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_TEST_ERR("bsp_ipf_config_timeout :%d\n",__LINE__);
        goto error;
    }

    u32Timeout = 1;
    s32ret = bsp_ipf_config_timeout(u32Timeout);
    if(s32ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("bsp_ipf_config_timeout :%d\n",__LINE__);
        goto error;
    }

    if(*(unsigned int*)(g_ipf_ctx.regs +HI_IPF_TIME_OUT_OFFSET) != 0x10001)
    {
        IPF_TEST_ERR("bsp_ipf_config_timeout :%d\n",__LINE__);
        goto error;
    }

    u32Timeout = 0xffff;
    s32ret = bsp_ipf_config_timeout(u32Timeout);
    if(s32ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("bsp_ipf_config_timeout :%d\n",__LINE__);
        goto error;
    }
	

    if(*(unsigned int*)(g_ipf_ctx.regs +HI_IPF_TIME_OUT_OFFSET) != 0x1ffff)
    {
        IPF_TEST_ERR("bsp_ipf_config_timeout :%d\n",__LINE__);
        goto error;
    }

    u32Timeout = 0x10000;
    s32ret = bsp_ipf_config_timeout(u32Timeout);
    if(s32ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_TEST_ERR("bsp_ipf_config_timeout :%d\n",__LINE__);
        goto error;
    }

    ipf_writel(u32OldTime, g_ipf_ctx.regs + HI_IPF_TIME_OUT_OFFSET);
    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);
    return OK;
error:
    ipf_writel(u32OldTime, g_ipf_ctx.regs + HI_IPF_TIME_OUT_OFFSET);
    return ERROR;
}


int BSP_IPF_ST_set_pkt_len(void)
{
    int s32Ret;
    unsigned int u32MaxLen = 0;
    unsigned int u32MinLen = 0;

    s32Ret = bsp_ipf_set_pktlen(u32MaxLen,u32MinLen);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("BSP_IPF_SetPktLen1 :%d\n",__LINE__);
        return ERROR;
    }

    u32MaxLen = 0x5;
    u32MinLen = 0x6;
    s32Ret = bsp_ipf_set_pktlen(u32MaxLen,u32MinLen);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_TEST_ERR("BSP_IPF_SetPktLen2 :%d\n",__LINE__);
        return ERROR;
    }

    u32MaxLen = 0x345;
    u32MinLen = 0x123;
    s32Ret = bsp_ipf_set_pktlen(u32MaxLen,u32MinLen);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("BSP_IPF_SetPktLen3 :%d\n",__LINE__);
        return ERROR;
    }
    if(*(unsigned int*)(g_ipf_ctx.regs +HI_IPF_PKT_LEN_OFFSET) != 0x3450123)
    {
        IPF_TEST_ERR("BSP_IPF_SetPktLen4 :%d\n",__LINE__);
        return ERROR;
    }

    u32MaxLen = 1500;
    u32MinLen = 40;
    s32Ret = bsp_ipf_set_pktlen(u32MaxLen,u32MinLen);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("BSP_IPF_SetPktLen5 :%d\n",__LINE__);
        return ERROR;
    }
    
    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);
    return OK;
}


int BSP_IPF_ST_003(void)
{
    bsp_ipf_help();
    bsp_ipf_dump_bdinfo(0);
    bsp_ipf_dump_bdinfo(1);
    bsp_ipf_dump_rdinfo(0);
    bsp_ipf_dump_rdinfo(1);
    bsp_ipf_dump_adinfo(0,0);
    bsp_ipf_dump_adinfo(0,1);
    bsp_ipf_dump_adinfo(1,0);
    bsp_ipf_dump_adinfo(1,1);
    bsp_ipf_info(0);
    bsp_ipf_info(1);
    bsp_ipf_mem();
    return IPF_SUCCESS;
}

int BSP_IPF_ST_AD_config_test(void)
{
    int s32Ret;
    unsigned int i;
	unsigned int ad_wptr = 0;
	unsigned long ad0_addr;
	unsigned long ad1_addr;
	IPF_AD_DESC_S *TempAD;
	void *tmp;
	
	for(i=0; i < IPF_DLAD0_DESC_SIZE; i++)
	{
		tmp = kmalloc(438,GFP_KERNEL);
		ADdlshort[i].u32OutPtr0 = (unsigned int)virt_to_phys(tmp);
		ADdlshort[i].u32OutPtr1 = ADdlshort[i].u32OutPtr0;

		if(NULL == (unsigned int *)ADdlshort[i].u32OutPtr0)	{
			IPF_TEST_ERR(" TESTERROR    IPF_ST_UL_INIT ADMEMmallocfail:%d\n",__LINE__);
			goto error1;
		}
	}
	
	for(i=0; i < IPF_DLAD1_DESC_SIZE; i++)
	{
    	tmp = kmalloc(1500,GFP_KERNEL);
		ADdllong[i].u32OutPtr0 = (unsigned int)virt_to_phys(tmp);
		ADdllong[i].u32OutPtr1 = ADdllong[i].u32OutPtr0;

		if(NULL == (unsigned int *)ADdllong[i].u32OutPtr0){
			IPF_TEST_ERR(" TESTERROR    IPF_ST_UL_INIT ADMEMmallocfail:%d\n",__LINE__);
			goto error2;
		}
	}
	
	ad_wptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_WPTR_OFFSET);
	ad_wptr &= AD_WPTR_MASK;
    s32Ret = mdrv_ipf_config_dlad(IPF_AD_0,IPF_DLAD0_DESC_SIZE-IPF_ADQ_RESERVE_NUM,&ADdlshort[0]);
    if(s32Ret != IPF_SUCCESS){
        IPF_TEST_ERR(" TESTERROR7    BSP_IPF_ConfigUlAd :%d\n",__LINE__);
        return ERROR;
    }
	
	bsp_ipf_ad0_info(&ad0_addr);
	TempAD = (IPF_AD_DESC_S*)(ad0_addr);
	for(i=0; i < IPF_DLAD0_DESC_SIZE-IPF_ADQ_RESERVE_NUM;i++)
	{
		if(ADdlshort[i].u32OutPtr0 != TempAD[ad_wptr].u32OutPtr0)	{
			IPF_TEST_ERR("Short AD compare err!\t");
			IPF_TEST_ERR("AD num:%#X MEM:%#X\t",i,ADdlshort[i].u32OutPtr0);
			IPF_TEST_ERR("AD %#X\n", TempAD[ad_wptr].u32OutPtr0);
		}
		ad_wptr = ((ad_wptr + 1) < IPF_DLAD0_DESC_SIZE)? (ad_wptr + 1) : 0;
	}
    IPF_TEST_ERR(" BSP_IPF_ST_005_TEST7 comp %d\n",__LINE__);
		
	ad_wptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_WPTR_OFFSET);
	ad_wptr &= AD_WPTR_MASK;
    s32Ret = mdrv_ipf_config_dlad(IPF_AD_1,IPF_DLAD1_DESC_SIZE-IPF_ADQ_RESERVE_NUM,&ADdllong[0]);
    if(s32Ret != IPF_SUCCESS){
        IPF_TEST_ERR(" TESTERROR8    BSP_IPF_ConfigUlAd :%d\n",__LINE__);
        return ERROR;
    }

	bsp_ipf_ad1_info(&ad1_addr);
	TempAD = (IPF_AD_DESC_S*)(ad1_addr);
	for(i=0; i < IPF_DLAD1_DESC_SIZE-IPF_ADQ_RESERVE_NUM;i++)
	{

		if(ADdllong[i].u32OutPtr0 != TempAD[ad_wptr].u32OutPtr0){
			IPF_TEST_ERR("Long AD compare err!\t");
			IPF_TEST_ERR("AD num:%#X MEM:%#X\t",i,ADdllong[i].u32OutPtr0);
			IPF_TEST_ERR("AD %#X\n", TempAD[ad_wptr].u32OutPtr0);
		}
		ad_wptr = ((ad_wptr + 1) < IPF_DLAD1_DESC_SIZE)? (ad_wptr + 1) : 0;
	}
    IPF_TEST_PRINT(" BSP_IPF_ST_005_TEST8 comp %d\n",__LINE__);
		
	for(i=0; i < IPF_DLAD0_DESC_SIZE; i++)
		kfree(phys_to_virt(ADdlshort[i].u32OutPtr0));

	for(i=0; i < IPF_DLAD1_DESC_SIZE; i++)
		kfree(phys_to_virt(ADdllong[i].u32OutPtr0));

    s32Ret = mdrv_ipf_config_dlad(IPF_AD_0,IPF_ULAD0_DESC_SIZE,&ADdlshort[0]);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA){
        IPF_TEST_ERR(" TESTERROR1   BSP_IPF_ConfigUlAd:%d\n",__LINE__);
        return ERROR;
    }
	
    s32Ret = mdrv_ipf_config_dlad(IPF_AD_1,IPF_ULAD1_DESC_SIZE,&ADdllong[0]);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA){
        IPF_TEST_ERR(" TESTERROR2    BSP_IPF_ConfigUlAd:%d\n",__LINE__);
        return ERROR;
    }
	
    s32Ret = mdrv_ipf_config_dlad(IPF_AD_0,1,NULL);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA){
        IPF_TEST_ERR(" TESTERROR3    BSP_IPF_ConfigUlAd:%d\n",__LINE__);
        return ERROR;
    }
	
    s32Ret = mdrv_ipf_config_dlad(IPF_AD_1,1,NULL);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA){
        IPF_TEST_ERR(" TESTERROR4    BSP_IPF_ConfigUlAd:%d\n",__LINE__);
        return ERROR;
    }
	
    s32Ret = mdrv_ipf_config_dlad(IPF_AD_0,0,&ADdlshort[0]);
    if(s32Ret != IPF_SUCCESS){
        IPF_TEST_ERR(" TESTERROR5    BSP_IPF_ConfigUlAd :%d\n",__LINE__);
        return ERROR;
    }
	
    s32Ret = mdrv_ipf_config_dlad(IPF_AD_1,0,&ADdllong[0]);
    if(s32Ret != IPF_SUCCESS){
        IPF_TEST_ERR(" TESTERROR6    BSP_IPF_ConfigUlAd :%d\n",__LINE__);
        return ERROR;
    }
	

	    return OK;
error1:
	do
	{
		i--;
		kfree(phys_to_virt(ADdlshort[i].u32OutPtr0));
	}while(i);
	return ERROR;
error2:
	do
	{
		i--;
		kfree(phys_to_virt(ADdllong[i].u32OutPtr0));
	}while(i);
	
	for(i=0; i < IPF_ULAD0_DESC_SIZE; i++)
	{
		kfree(phys_to_virt(ADdlshort[i].u32OutPtr0));
	}
	return ERROR;

    IPF_TEST_PRINT("%s : SUCCESS\n",__FUNCTION__);
}

/****************************
***1xx UL start test*****
*****************************/
int BSP_IPF_ST_100(void)
{
    IPF_CONFIG_ULPARAM_S stUlPara[2];
    unsigned int u32Num = 0;
    int s32Ret = 0;
    void *pBuff;

	if(!g_ul_packet_flag){
		s32Ret = get_ul_ip_pkt();

		if(s32Ret != OK){
			IPF_TEST_ERR("ipf get packet failed!\n");
        	return ERROR;
    	}
		g_ul_packet_flag = 1;
	}
	
    u32Num = mdrv_ipf_get_ulbd_num();
    if(u32Num <  2) {
        IPF_TEST_PRINT("Only %d BD!\n",__LINE__, u32Num);
        return ERROR;
    }

    pBuff = (void *)dma_map_single(g_ipf_ctx.dev, (void *)g_ul_long_data, LONG_DATA, DMA_TO_DEVICE);        
    stUlPara[0].u32Data = (unsigned int)(unsigned long)pBuff;
    stUlPara[0].u16Len = LONG_DATA;
    stUlPara[0].u16UsrField1 = 0;
    stUlPara[0].u32UsrField2 = 0;
    stUlPara[0].u32UsrField3 = 0x102;
    /*链0只搬移无中断*/
    stUlPara[0].u16Attribute = 0x14;
	
    pBuff = (void *)dma_map_single(g_ipf_ctx.dev, (void *)g_ul_short_data, SHORT_DATA, DMA_TO_DEVICE);        
    stUlPara[1].u32Data = (unsigned int)(unsigned long)pBuff;
    stUlPara[1].u16Len = SHORT_DATA;
    stUlPara[1].u16UsrField1 = 0;
    stUlPara[1].u32UsrField2 = 0;
    stUlPara[1].u32UsrField3 = 0x102;
    /*链0只搬移,中断*/
    stUlPara[1].u16Attribute = 0x15;
	
    s32Ret = mdrv_ipf_config_ulbd(2, stUlPara);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
        return IPF_ERROR;
    }

    return OK;    
}

/*发送函数*/
int BSP_IPF_ST_101(void)
{
    IPF_CONFIG_ULPARAM_S stUlPara[IPF_ULBD_DESC_SIZE];
    unsigned int u32Num = 0;
    unsigned int u32UlBdprt = 0;
    int s32Ret = 0;
    unsigned int i = 0;
    void* pBuff;

	if(!g_ul_packet_flag){
		s32Ret = get_ul_ip_pkt();
		if(s32Ret != OK){
			IPF_TEST_ERR("ipf get packet failed!\n");
	        return ERROR;						
		}
		g_ul_packet_flag = 1;
	}
    u32Num = mdrv_ipf_get_ulbd_num();
    
    u32UlBdprt = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_BDQ_WPTR_OFFSET);
    IPF_TEST_PRINT("BDQ_WPTR IS %d \n",u32UlBdprt);
	
    u32UlBdprt = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_BDQ_RPTR_OFFSET);
    IPF_TEST_PRINT("BDQ_RPTR IS %d \n",u32UlBdprt);


    if(u32Num != IPF_ULBD_DESC_SIZE)
    {
        IPF_TEST_ERR("mdrv_ipf_get_ulbd_num :%d u32Num = %d\n",__LINE__, u32Num);

    }

    pBuff = (void *)dma_map_single(g_ipf_ctx.dev, (void *)g_ul_long_data, LONG_DATA, DMA_TO_DEVICE);        
    stUlPara[0].u32Data = (unsigned int)(unsigned long)pBuff;
    stUlPara[0].u16Len = LONG_DATA;
    stUlPara[0].u16UsrField1 = 0;
    stUlPara[0].u32UsrField2 = 0;
    stUlPara[0].u32UsrField3= 0x101;
    /*链0只搬移无中断*/
    stUlPara[0].u16Attribute = 0x14;
	
    for(i = 1; i < IPF_ULBD_DESC_SIZE; i++)
    {
        memcpy(&stUlPara[i], &stUlPara[0], sizeof(IPF_CONFIG_ULPARAM_S));
        stUlPara[i].u16UsrField1 = i;
    }
    stUlPara[IPF_ULBD_DESC_SIZE-1].u32UsrField3 = 1;
    stUlPara[31].u16Attribute= 0x15;

    /*调用ConfigUpFilter*/
    s32Ret = mdrv_ipf_config_ulbd(34, stUlPara);

    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
        return IPF_ERROR;
    }    
	
    return OK;    
}


int BSP_IPF_ST_102(void)
{
    IPF_CONFIG_ULPARAM_S stUlPara[2];
    unsigned int u32Num = 0;
    int s32Ret = 0;
    void *pBuff;
	if(!g_ul_packet_flag){
			s32Ret = get_ul_ip_pkt();
			if(s32Ret != OK){
				IPF_TEST_ERR("ipf get packet failed!\n");
				return ERROR;						
			}
			g_ul_packet_flag = 1;
	}

    u32Num = mdrv_ipf_get_ulbd_num();
    if(u32Num !=  IPF_ULBD_DESC_SIZE)
    {
        IPF_TEST_ERR(" mdrv_ipf_get_ulbd_num :%d u32Num = %d\n",__LINE__, u32Num);
    }

    pBuff = (void *)dma_map_single(g_ipf_ctx.dev, (void *)g_ul_long_data, LONG_DATA, DMA_TO_DEVICE);        
    stUlPara[0].u32Data = (unsigned int)(unsigned long)pBuff;
    stUlPara[0].u16Len = LONG_DATA;
    stUlPara[0].u16UsrField1 = 0;
    stUlPara[0].u32UsrField2 = 0;
    stUlPara[0].u32UsrField3 = 0x102;
    /*链0只搬移无中断*/
    stUlPara[0].u16Attribute = 0x14;
	
    pBuff = (void *)dma_map_single(g_ipf_ctx.dev, (void *)g_ul_short_data, SHORT_DATA, DMA_TO_DEVICE);        
    stUlPara[1].u32Data = (unsigned int)pBuff;
    stUlPara[1].u16Len = SHORT_DATA;
    stUlPara[1].u16UsrField1 = 0;
    stUlPara[1].u32UsrField2 = 0;
    stUlPara[1].u32UsrField3 = 0x102;
    /*链0只搬移无中断*/
    stUlPara[1].u16Attribute = 0x14;
	
    s32Ret = mdrv_ipf_config_ulbd(2, stUlPara);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

    u32Num = mdrv_ipf_get_ulbd_num();
    if(u32Num != IPF_ULBD_DESC_SIZE - 1)
    {
        IPF_TEST_ERR("mdrv_ipf_get_ulbd_num :%d u32Num = %d\n",__LINE__, u32Num);
    }

    stUlPara[0].u16UsrField1 = 1;
    stUlPara[0].u32UsrField3 = 3;
    /*链0过滤搬移，设中断。*/
    stUlPara[0].u16Attribute = 0x11;

    s32Ret = mdrv_ipf_config_ulbd(1, stUlPara);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

    return OK;    
}

/*
*step1. call this fuction
*step2. run any dl case
*step3. check pmlog
*/
int ipf_test_pm_om_dl(void)
{
	int ret;
	if (!g_ipf_ctx.status) {
		ret = -1;
		goto out;
	}
	g_ipf_ctx.status->resume_with_intr++;

out:
	IPF_TEST_PRINT("%s %s\n", __FUNCTION__, ret ? "failed" : "success");
	return ret;
}


int BSP_IPF_ST_102sn(unsigned int u32sendnum)
{
    IPF_CONFIG_ULPARAM_S stUlPara[IPF_ULBD_DESC_SIZE];
    unsigned int u32Num = 0;
    unsigned int i = 0;
    int s32Ret = 0;
    void *pBuff;
	if(!g_ul_packet_flag){
		s32Ret = get_ul_ip_pkt();

		if(s32Ret != OK){
			IPF_TEST_ERR("ipf get packet failed!\n");
			return ERROR;						
		}
		g_ul_packet_flag = 1;
	}
    u32Num = mdrv_ipf_get_ulbd_num();
    if(u32Num !=  IPF_ULBD_DESC_SIZE)
    {
        IPF_TEST_ERR(" mdrv_ipf_get_ulbd_num :%d u32Num = %d\n",__LINE__, u32Num);
    }

    pBuff = (void *)dma_map_single(g_ipf_ctx.dev, (void *)g_ul_short_data, SHORT_DATA, DMA_TO_DEVICE);        
	for(i=0;i<IPF_ULBD_DESC_SIZE;i++)
	{
	    stUlPara[i].u32Data = (unsigned int)(unsigned long)pBuff;
	    stUlPara[i].u16Len = SHORT_DATA;
	    stUlPara[i].u16UsrField1 = 0;
	    stUlPara[i].u32UsrField2 = 0;
	    stUlPara[i].u32UsrField3 = 0x102;
	    /*链0只搬移无中断*/
	    stUlPara[i].u16Attribute = 0x14;
	}		
    stUlPara[u32sendnum-2].u16Attribute = 0x15;
    s32Ret = mdrv_ipf_config_ulbd(u32sendnum, stUlPara);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

    return OK;    
}

/*发送函数 34 短包设定中断*/
int BSP_IPF_ST_103(void)
{
    IPF_CONFIG_ULPARAM_S stUlPara[IPF_ULBD_DESC_SIZE];
    unsigned int u32Num = 0;
    unsigned int i = 0;
    int s32Ret = 0;
    void *pBuff;
	if(!g_ul_packet_flag){
		s32Ret = get_ul_ip_pkt();

		if(s32Ret != OK){
			IPF_TEST_ERR("ipf get packet failed!\n");
			return ERROR;						
		}
		g_ul_packet_flag = 1;
	}
    u32Num = mdrv_ipf_get_ulbd_num();
    if(u32Num !=  IPF_ULBD_DESC_SIZE)
    {
        IPF_TEST_ERR(" mdrv_ipf_get_ulbd_num :%d u32Num = %d\n",__LINE__, u32Num);
    }

    pBuff = (void *)dma_map_single(g_ipf_ctx.dev, (void *)g_ul_short_data, SHORT_DATA, DMA_TO_DEVICE);        
    for(i=0;i<IPF_ULBD_DESC_SIZE;i++)
    {
        stUlPara[i].u32Data = (unsigned int)pBuff;
        stUlPara[i].u16Len = SHORT_DATA;
        stUlPara[i].u16UsrField1 = 0;
        stUlPara[i].u32UsrField2 = 0;
        stUlPara[i].u32UsrField3 = 0x102;
        /*链0只搬移无中断*/
        stUlPara[i].u16Attribute = 0x14;
    }		
    stUlPara[31].u16Attribute = 0x15;
    s32Ret = mdrv_ipf_config_ulbd(34, stUlPara);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

    return OK;    
}

/*发送函数 34 短包设定中断，34 短包不设定中断  103、104一起执行会引起阻塞*/
int BSP_IPF_ST_104(void)
{
    IPF_CONFIG_ULPARAM_S stUlPara[IPF_ULBD_DESC_SIZE];
    unsigned int u32Num = 0;
    unsigned int u32UlBdprt = 0;
    int s32Ret = 0;
    unsigned int i = 0;
    void* pBuff;
	if(!g_ul_packet_flag){
		s32Ret = get_ul_ip_pkt();

		if(s32Ret != OK){
			IPF_TEST_ERR("ipf get packet failed!\n");
			return ERROR;						
		}
		g_ul_packet_flag = 1;
	}
    u32Num = mdrv_ipf_get_ulbd_num();
    if(u32Num != IPF_ULBD_DESC_SIZE)
    {
        IPF_TEST_ERR("mdrv_ipf_get_ulbd_num :%d u32Num = %d\n",__LINE__, u32Num);
    }
    
    u32UlBdprt = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_BDQ_WPTR_OFFSET);
    IPF_TEST_PRINT("BDQ_WPTR IS %d \n",u32UlBdprt);
	
    u32UlBdprt = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_BDQ_RPTR_OFFSET);
    IPF_TEST_PRINT("BDQ_RPTR IS %d \n",u32UlBdprt);

    pBuff = (void *)dma_map_single(g_ipf_ctx.dev, (void *)g_ul_short_data, SHORT_DATA, DMA_TO_DEVICE);        
    stUlPara[0].u32Data = (unsigned int)pBuff;
    stUlPara[0].u16Len = SHORT_DATA;
    stUlPara[0].u16UsrField1 = 0;
    stUlPara[0].u32UsrField2 = 0;
    stUlPara[0].u32UsrField3= 0x101;
    /*链0只搬移无中断*/
    stUlPara[0].u16Attribute = 0x14;
	
    for(i = 1; i < IPF_ULBD_DESC_SIZE; i++)
    {
        memcpy(&stUlPara[i], &stUlPara[0], sizeof(IPF_CONFIG_ULPARAM_S));
        stUlPara[i].u16UsrField1 = i;
    }
    stUlPara[IPF_ULBD_DESC_SIZE-1].u32UsrField3 = 1;
    stUlPara[31].u16Attribute= 0x15;

    /*调用ConfigUpFilter，设定终端上报位*/
    s32Ret = mdrv_ipf_config_ulbd(34, stUlPara);

    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
        return IPF_ERROR;
    }    
    /*调用ConfigUpFilter，没有设定终端上报位*/
    s32Ret = mdrv_ipf_config_ulbd(34, stUlPara);

    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
        return IPF_ERROR;
    }    
    return OK;    
}

/*发送函数 34 短包设定中断，34 短包不设定中断*/
int BSP_IPF_ST_105(void)
{
    IPF_CONFIG_ULPARAM_S stUlPara[IPF_ULBD_DESC_SIZE];
    unsigned int u32Num = 0;
    unsigned int u32UlBdprt = 0;
    int s32Ret = 0;
    unsigned int i = 0;
    void* pBuff;
	if(!g_ul_packet_flag){
		s32Ret = get_ul_ip_pkt();
		if(s32Ret != OK){
			IPF_TEST_ERR("ipf get packet failed!\n");
			return ERROR;						
		}
		g_ul_packet_flag = 1;
	}

    u32Num = mdrv_ipf_get_ulbd_num();
    
    u32UlBdprt = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_BDQ_WPTR_OFFSET);
    IPF_TEST_PRINT("BDQ_WPTR IS %d \n",u32UlBdprt);
	
    u32UlBdprt = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_BDQ_RPTR_OFFSET);
    IPF_TEST_PRINT("BDQ_RPTR IS %d \n",u32UlBdprt);


    if(u32Num != IPF_ULBD_DESC_SIZE)
    {
        IPF_TEST_ERR("mdrv_ipf_get_ulbd_num :%d u32Num = %d\n",__LINE__, u32Num);

    }

    pBuff = (void *)dma_map_single(g_ipf_ctx.dev, (void *)g_ul_short_data, SHORT_DATA, DMA_TO_DEVICE);        
    stUlPara[0].u32Data = (unsigned int)pBuff;
    stUlPara[0].u16Len = SHORT_DATA;
    stUlPara[0].u16UsrField1 = 0;
    stUlPara[0].u32UsrField2 = 0;
    stUlPara[0].u32UsrField3= 0x101;
    /*链0只搬移无中断*/
    stUlPara[0].u16Attribute = 0x14;
	
    for(i = 1; i < IPF_ULBD_DESC_SIZE; i++)
    {
        memcpy(&stUlPara[i], &stUlPara[0], sizeof(IPF_CONFIG_ULPARAM_S));
        stUlPara[i].u16UsrField1 = i;
    }
    stUlPara[IPF_ULBD_DESC_SIZE-1].u32UsrField3 = 1;
    stUlPara[31].u16Attribute= 0x15;

    /*调用ConfigUpFilter，设定终端上报位*/
    s32Ret = mdrv_ipf_config_ulbd(30, stUlPara);

    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
        return IPF_ERROR;
    }    
    /*调用ConfigUpFilter，没有设定终端上报位*/
    s32Ret = mdrv_ipf_config_ulbd(30, stUlPara);

    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
        return IPF_ERROR;
    }    
    return OK;    
}

/*以下代码测试过滤搬移*/
int BSP_IPF_ST_111(void)
{
    IPF_CONFIG_ULPARAM_S stUlPara[IPF_ULBD_DESC_SIZE];
    unsigned int u32Num = 0;
    int s32Ret = 0;
    unsigned int i = 0;
    void *pBuff;
	
	if(!g_ul_packet_flag){
		s32Ret = get_ul_ip_pkt();
		if(s32Ret != OK){
			IPF_TEST_ERR("ipf get packet failed!\n");
			return ERROR;						
		}
		g_ul_packet_flag = 1;
	}	
    u32Num = mdrv_ipf_get_ulbd_num();
    if(u32Num != IPF_ULBD_DESC_SIZE)
    {
        IPF_TEST_ERR(" mdrv_ipf_get_ulbd_num :%d u32Num = %d\n",__LINE__, u32Num);

    }

    pBuff = (void *)dma_map_single(g_ipf_ctx.dev, (void *)g_ul_long_data, LONG_DATA, DMA_TO_DEVICE);        
    stUlPara[0].u32Data = (unsigned int)pBuff;
    stUlPara[0].u16Len = LONG_DATA;
    stUlPara[0].u16UsrField1 = 0;
    stUlPara[0].u32UsrField2 = 0;
    stUlPara[0].u32UsrField3 = 0x102;
    stUlPara[0].u16Attribute = 0x10;
	
    for(i = 1; i < IPF_ULBD_DESC_SIZE; i++)
    {
        memcpy(&stUlPara[i], &stUlPara[0], sizeof(IPF_CONFIG_ULPARAM_S));
        stUlPara[i].u16UsrField1 = 0;
        stUlPara[i].u16Attribute = 0x10;
    }
    for(i = 10; i < IPF_ULBD_DESC_SIZE-10; i++)
    {
        memcpy(&stUlPara[i], &stUlPara[0], sizeof(IPF_CONFIG_ULPARAM_S));
        stUlPara[i].u16UsrField1 = 0;
        stUlPara[i].u16Attribute = 0x10;
    }

    stUlPara[IPF_ULBD_DESC_SIZE-5].u32UsrField3= 1;
    stUlPara[IPF_ULBD_DESC_SIZE-5].u16Attribute= 0x11;
	
    s32Ret = mdrv_ipf_config_ulbd(IPF_ULBD_DESC_SIZE-5, stUlPara);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

    return OK;
}

int BSP_IPF_ST_112(void)
{
    IPF_CONFIG_ULPARAM_S stUlPara[1];
    unsigned int u32Num = 0;
    int s32Ret = 0;
    void *pBuff;

	if(!g_ul_packet_flag){
		s32Ret = get_ul_ip_pkt();
		if(s32Ret != OK){
			IPF_TEST_ERR("ipf get packet failed!\n");
			return ERROR;						
		}
		g_ul_packet_flag = 1;
	}	
    u32Num = mdrv_ipf_get_ulbd_num();
    if(u32Num !=  IPF_ULBD_DESC_SIZE)
    {
        IPF_TEST_ERR(" mdrv_ipf_get_ulbd_num :%d u32Num = %d\n",__LINE__, u32Num);
    }

    pBuff = (void *)dma_map_single(g_ipf_ctx.dev, (void *)g_ul_long_data, LONG_DATA, DMA_TO_DEVICE);        
    stUlPara[0].u32Data = (unsigned int)pBuff;
    stUlPara[0].u16Len = LONG_DATA;
    stUlPara[0].u16UsrField1 = 0;
    stUlPara[0].u32UsrField2 = 0;
    stUlPara[0].u32UsrField3 = 0x102;
    stUlPara[0].u16Attribute= 0x10;
	
    s32Ret = mdrv_ipf_config_ulbd(1, stUlPara);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("%d TESTERROR    mdrv_ipf_config_ulbd : s32Ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

    u32Num = mdrv_ipf_get_ulbd_num();
    if(u32Num != IPF_ULBD_DESC_SIZE - 1)
    {
        IPF_TEST_ERR(" %d mdrv_ipf_get_ulbd_num : u32Num = %d\n",__LINE__, u32Num);
    }

    stUlPara[0].u16UsrField1 = 1;
    stUlPara[0].u32UsrField3 = 3;
    stUlPara[0].u16Attribute= 0x11;
	
    s32Ret = mdrv_ipf_config_ulbd(1, stUlPara);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR("%d  TESTERROR    mdrv_ipf_config_ulbd :s32Ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

    return OK;
}

int BSP_IPF_ST_113(void)
{
    IPF_CONFIG_ULPARAM_S stUlPara[IPF_ULBD_DESC_SIZE];
    unsigned int u32Num = 0;
    int s32Ret = 0;
    unsigned int i = 0;
    void *pBuff;

	if(!g_ul_packet_flag){
		s32Ret = get_ul_ip_pkt();
		if(s32Ret != OK){
			IPF_TEST_ERR("ipf get packet failed!\n");
			return ERROR;						
		}
		g_ul_packet_flag = 1;
	}	
    u32Num = mdrv_ipf_get_ulbd_num();
    if(u32Num != IPF_ULBD_DESC_SIZE)
    {
        IPF_TEST_ERR("mdrv_ipf_get_ulbd_num :%d u32Num = %d\n",__LINE__, u32Num);

    }        

    pBuff = (unsigned int *)dma_map_single(g_ipf_ctx.dev, (void *)g_ul_long_data, LONG_DATA, DMA_TO_DEVICE);        
    stUlPara[0].u32Data = (unsigned int)pBuff;
    stUlPara[0].u16Len = LONG_DATA;
    stUlPara[0].u16UsrField1 = 0;
    stUlPara[0].u32UsrField2 = 0;
    stUlPara[0].u32UsrField3 = 0x102;
    stUlPara[0].u16Attribute = 0x10;
    for(i = 1; i < IPF_ULBD_DESC_SIZE; i++)
    {
        memcpy(&stUlPara[i], &stUlPara[0], sizeof(IPF_CONFIG_ULPARAM_S));
        stUlPara[i].u16UsrField1 = i;
        stUlPara[i].u16Attribute = 0x10;

    }
    stUlPara[31].u16Attribute = 0x11;
    stUlPara[IPF_ULBD_DESC_SIZE-1].u16Attribute = 0x11;
    s32Ret = mdrv_ipf_config_ulbd(32, stUlPara);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

    u32Num = mdrv_ipf_get_ulbd_num();
    if(u32Num < (IPF_ULBD_DESC_SIZE - 32))
    {
        IPF_TEST_ERR(" mdrv_ipf_get_ulbd_num :%d u32Num = %d\n",__LINE__, u32Num);
    }

    stUlPara[IPF_ULBD_DESC_SIZE-1].u32UsrField3 = 3;
    s32Ret = mdrv_ipf_config_ulbd(IPF_ULBD_DESC_SIZE - 32, &stUlPara[32]);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

    s32Ret = bsp_ipf_config_timeout(50);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_PRINT(" TESTERROR    bsp_ipf_config_timeout :%d\n",__LINE__);
        return ERROR;
    }
    return OK;
}

int BSP_IPF_UlSend(void)
{
    IPF_CONFIG_ULPARAM_S stUlPara[IPF_ULBD_DESC_SIZE];
    unsigned int u32BDNum = 0;
    unsigned int i = 0;
    unsigned int j = 10000;
    int s32Ret = 0;
    unsigned char* pu8Data = NULL;
    unsigned short u16Len = 640;
    StreamIPv4Header stIPHeader;
    StreamUDP stUDP;
    void *pBuff;

    pu8Data = (unsigned char*)kmalloc(u16Len,GFP_KERNEL);
    if(pu8Data == NULL)
    {
        IPF_TEST_ERR(" TESTERROR    malloc :%d\n",__LINE__);
        return ERROR;
    }

    stIPHeader.Vers = 4;
    stIPHeader.HeaderLen = 5;
    stIPHeader.TOS = 3;
    stIPHeader.TOL = u16Len;
    stIPHeader.ID = 1;
    stIPHeader.ReservFlag = 0;
    stIPHeader.DF = 0;
    stIPHeader.MF = 0;
    stIPHeader.offset = 0;
    stIPHeader.TTL = 128;
    stIPHeader.Prot = 17; /* UDP */
    stIPHeader.Checksum = 0xEC3A;
    stIPHeader.SourceAddr = 0xACA84649;
    stIPHeader.DestAddr = 0x0202014E;

    stUDP.SrcPort = 5088;
    stUDP.DstPort = 2923;
    stUDP.Checksum = 0;
    stUDP.Length = stIPHeader.TOL;
        
    memset(pu8Data, T_UL_VALUE, u16Len);
    memcpy(pu8Data, &stIPHeader, sizeof(StreamIPv4Header));
    memcpy(pu8Data+sizeof(StreamIPv4Header), &stUDP, sizeof(StreamUDP));
	
    pBuff = (void *)dma_map_single(g_ipf_ctx.dev, (void *)pu8Data, u16Len, DMA_TO_DEVICE);  
    for(i=0;i<IPF_ULBD_DESC_SIZE;i++)
    {
        stUlPara[i].u32Data = (unsigned int)pBuff;
        stUlPara[i].u16Len = u16Len-i*9;
        stUlPara[i].u16UsrField1 = 0;
        stUlPara[i].u32UsrField2 = 0;
        stUlPara[i].u32UsrField3 = 0x102;
        /*链0只搬移无中断*/
        stUlPara[i].u16Attribute = 0x10;
    }		

    while(j>0)
    {
        u32BDNum = mdrv_ipf_get_ulbd_num();
        if(u32BDNum > 20)
        {
            stUlPara[u32BDNum-3].u16Attribute = 0x11;
            s32Ret = mdrv_ipf_config_ulbd(u32BDNum-2, stUlPara);
			mdelay(20);
            if(s32Ret != IPF_SUCCESS)
            {
                IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
                kfree(pu8Data);
                return ERROR;
            }
            j--;
        }
    }
    return OK;    
}

/*上行数传测试，规避队头阻塞版本*/
int BSP_IPF_UlSend122(void)
{
    IPF_CONFIG_ULPARAM_S stUlPara[IPF_ULBD_DESC_SIZE];
    unsigned int u32BDNum = 0;
    unsigned int i = 0;
    int s32Ret = 0;
    unsigned char* pu8Data = NULL;
    unsigned short u16Len = 640;
    StreamIPv4Header stIPHeader;
    StreamUDP stUDP;
    void *pBuff;
    unsigned int j = 10000;

    pu8Data = (unsigned char*)kmalloc(u16Len,GFP_KERNEL);
    if(pu8Data == NULL)
    {
        IPF_TEST_ERR(" TESTERROR    malloc :%d\n",__LINE__);
        return ERROR;
    }

    stIPHeader.Vers = 4;
    stIPHeader.HeaderLen = 5;
    stIPHeader.TOS = 3;
    stIPHeader.TOL = u16Len;
    stIPHeader.ID = 1;
    stIPHeader.ReservFlag = 0;
    stIPHeader.DF = 0;
    stIPHeader.MF = 0;
    stIPHeader.offset = 0;
    stIPHeader.TTL = 128;
    stIPHeader.Prot = 17; /* UDP */
    stIPHeader.Checksum = 0xEC3A;
    stIPHeader.SourceAddr = 0xACA84649;
    stIPHeader.DestAddr = 0x0202014E;

    stUDP.SrcPort = 5088;
    stUDP.DstPort = 2923;
    stUDP.Checksum = 0;
    stUDP.Length = stIPHeader.TOL;
       
    memset(pu8Data, T_UL_VALUE, u16Len);
    memcpy(pu8Data, &stIPHeader, sizeof(StreamIPv4Header));
    memcpy(pu8Data+sizeof(StreamIPv4Header), &stUDP, sizeof(StreamUDP));
	
    pBuff = (void *)dma_map_single(g_ipf_ctx.dev, (void *)pu8Data, u16Len, DMA_TO_DEVICE);  
    for(i=0;i<IPF_ULBD_DESC_SIZE;i++)
    {
        stUlPara[i].u32Data = (unsigned int)pBuff;
        stUlPara[i].u16Len = u16Len-i*9;
        stUlPara[i].u16UsrField1 = 0;
        stUlPara[i].u32UsrField2 = 0;
        stUlPara[i].u32UsrField3 = 0x102;
        /*链0只搬移无中断*/
        stUlPara[i].u16Attribute = 0x10;
    }		

    while(j>0)
    {
        u32BDNum = mdrv_ipf_get_uldesc_num();
        if(u32BDNum > 1)
        {
            stUlPara[u32BDNum-1].u16Attribute = 0x11;
            s32Ret = mdrv_ipf_config_ulbd(u32BDNum, stUlPara);
            if(s32Ret != IPF_SUCCESS)
            {
                IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
                kfree(pu8Data);
                return ERROR;
            }
            j--;
        }

       else if(u32BDNum == 1)
        {
            stUlPara[u32BDNum-1].u16Attribute = 0x11;
            s32Ret = mdrv_ipf_config_ulbd(u32BDNum, stUlPara);
            if(s32Ret != IPF_SUCCESS)
            {
                IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
                kfree(pu8Data);
                return ERROR;
            }
            j--;
        }
    }
    return OK;    
}

int BSP_IPF_ST_121(void)
{
    /*起一个进程，不停地发东西*/
    g_IpfDlTaskId = kthread_run((IPFTHREADFN)BSP_IPF_UlSend, NULL, "IpfUlTask");  
    return OK;
}

int BSP_IPF_ST_122(void)
{
    /*起一个进程，不停地发东西*/
    g_IpfDlTaskId = kthread_run((IPFTHREADFN)BSP_IPF_UlSend122, NULL, "IpfUlTask");  
    return OK;
}

/*dpm测试*/
#ifdef CONFIG_PM
int BSP_IPF_ST_130(void)
{
    dpm_suspend_start(PMSG_SUSPEND);
    dpm_suspend_end(PMSG_SUSPEND);
    dpm_resume_start(PMSG_RESUME);
    dpm_resume_end(PMSG_RESUME);
    return OK;
}
#endif

/*发送函数*/
int BSP_IPF_ST_131(void)
{
    IPF_CONFIG_ULPARAM_S stUlPara[IPF_ULBD_DESC_SIZE];
    unsigned int u32Num = 0;
    int s32Ret = 0;
    unsigned char* pu8Data = NULL;
    unsigned short u16Len = 1200;
    unsigned int i;
    void* pBuff;

    u32Num = mdrv_ipf_get_ulbd_num();
    if(u32Num != IPF_ULBD_DESC_SIZE)
    {
        IPF_TEST_ERR("mdrv_ipf_get_ulbd_num :%d u32Num = %d\n",__LINE__, u32Num);
    }

    pu8Data = (unsigned char*)kmalloc(u16Len,GFP_KERNEL);
    if(pu8Data == NULL)
    {
        IPF_TEST_ERR(" TESTERROR    malloc :%d\n",__LINE__);
        return ERROR;
    }
 
    memset(pu8Data, T_UL_VALUE, u16Len);
    memcpy(pu8Data, &ipf_ipv4_head, sizeof(StreamIPv4Header));
    memcpy(pu8Data+sizeof(StreamIPv4Header), &ipf_udp, sizeof(StreamUDP));

    IPF_TEST_PRINT("sizeof(StreamIPv4Header) = %d  sizeof(StreamUDP) = %d \n", 
                      sizeof(StreamIPv4Header), sizeof(StreamUDP));

    pBuff = (void *)dma_map_single(g_ipf_ctx.dev, (void *)pu8Data, u16Len, DMA_TO_DEVICE);        
    stUlPara[0].u32Data = (unsigned int)pBuff;
    stUlPara[0].u16Len = u16Len;
    stUlPara[0].u16UsrField1 = 0;
    stUlPara[0].u32UsrField2 = 0;
    stUlPara[0].u32UsrField3= 0x101;
    stUlPara[0].u16Attribute = 0x11;
	
    for(i = 1; i < IPF_ULBD_DESC_SIZE; i++)
    {
        memcpy(&stUlPara[i], &stUlPara[0], sizeof(IPF_CONFIG_ULPARAM_S));
        stUlPara[i].u16UsrField1 = i;
    }
    stUlPara[1].u16Len = 200;

    /*调用ConfigUpFilter*/
    s32Ret = mdrv_ipf_config_ulbd(2, stUlPara);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
        kfree(pu8Data);
        return IPF_ERROR;
    }    
	
    return OK;    
}
int BSP_IPF_ST_131_n(unsigned int n)
{	
	int ret;
	unsigned int ad0_rptr_last,ad0_rptr_current,ad1_rptr_last,ad1_rptr_current;
	ad0_rptr_last = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_ADQ0_RPTR_OFFSET);
	ad1_rptr_last = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_ADQ1_RPTR_OFFSET);
	while(n>0)
	{
		ret = BSP_IPF_ST_131();
		mdelay(2);
		ad0_rptr_current = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_ADQ0_RPTR_OFFSET);
		ad1_rptr_current = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_ADQ1_RPTR_OFFSET);
		if((IPF_ULAD0_DESC_SIZE-1) == ad0_rptr_last)
		{
			if(0 != ad0_rptr_current)
			{
				IPF_TEST_ERR(" TESTERROR AD0 add error\n");
				return IPF_ERROR;
			}
		}
		else if(ad0_rptr_current != ad0_rptr_last+1)
		{
			IPF_TEST_ERR(" TESTERROR AD0 add error\n");
			return IPF_ERROR;
		}
		ad0_rptr_last = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_ADQ0_RPTR_OFFSET);
		
		if((IPF_ULAD1_DESC_SIZE-1) == ad1_rptr_last)
		{
			if(0 != ad1_rptr_current)
			{
				IPF_TEST_ERR(" TESTERROR AD1 add error\n");
				return IPF_ERROR;
			}
		}
		else if(ad1_rptr_current != ad1_rptr_last+1)
		{
			IPF_TEST_ERR(" TESTERROR AD1 add error\n");
			return IPF_ERROR;
		}
		ad1_rptr_last = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_ADQ1_RPTR_OFFSET);
		n--;
	}
	return IPF_SUCCESS;
}

/****************************
***3xx DL init test*****
*****************************/
int BSP_IPF_ST_300_INIT(void)
{
    int s32Ret = 0;
    unsigned int u16Len = 1000;
	struct mdrv_ipf_ops wake_empty_cb;

	if(g_pu8STDlData != NULL){
		kfree(g_pu8STDlData);
		g_pu8STDlData = NULL;
	}
	
    g_pu8STDlData = kmalloc(u16Len,GFP_KERNEL);
    if(g_pu8STDlData == NULL)
    {
        IPF_TEST_ERR("cache dma malloc failed:%d\n",__LINE__);
        return ERROR;
    }

    s32Ret = IPF_ST_DL_ACore_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR("IPF_ST_DL_ACore_INIT return failed:%d\n",__LINE__);
        return ERROR;
    }

    memset((unsigned int *)g_pu8STDlData, T_DL_VALUE, u16Len);
    memcpy((unsigned int *)g_pu8STDlData, &ipf_ipv4_head, sizeof(StreamIPv4Header));
    memcpy(g_pu8STDlData+sizeof(StreamIPv4Header), &ipf_udp, sizeof(StreamUDP));

	wake_empty_cb.rx_complete_cb = IpfDlIntCb300;
	wake_empty_cb.adq_empty_cb = IPF_ST_DL_FlushAD;
	mdrv_ipf_register_ops(&wake_empty_cb);

	IPF_TEST_ERR(" ul ccore init ok\n");
    return OK;
}

int BSP_IPF_ST_301_INIT(void)
{
    int s32Ret = 0;
    unsigned int u16Len = 1000;
	struct mdrv_ipf_ops wake_empty_cb;

	if(g_pu8STDlData != NULL){
		kfree(g_pu8STDlData);
		g_pu8STDlData = NULL;
	}
	
    g_pu8STDlData = kmalloc(u16Len,GFP_KERNEL);
    if(g_pu8STDlData == NULL)
    {
        IPF_TEST_ERR("cache dma malloc failed:%d\n",__LINE__);
        return ERROR;
    }
	
    s32Ret = IPF_ST_DL_ACore_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR("IPF_ST_DL_ACore_INIT alloc failed:%d\n",__LINE__);
        return ERROR;
    }

	memset((unsigned int *)g_pu8STDlData, T_DL_VALUE, u16Len);
	memcpy((unsigned int *)g_pu8STDlData, &ipf_ipv4_head, sizeof(StreamIPv4Header));
	memcpy(g_pu8STDlData+sizeof(StreamIPv4Header), &ipf_udp, sizeof(StreamUDP));

	wake_empty_cb.rx_complete_cb = IpfDlIntCb301;
	wake_empty_cb.adq_empty_cb = IPF_ST_DL_FlushAD;
	mdrv_ipf_register_ops(&wake_empty_cb);

	IPF_TEST_ERR(" ul ccore init ok\n");
    return OK;
}

int BSP_IPF_ST_302_INIT(void)
{    
    int s32Ret = 0;
    unsigned int u16Len = 1000;
    unsigned int u32Len = 200;
	struct mdrv_ipf_ops wake_empty_cb;
	
	if(g_pu8STDlData != NULL){
		kfree(g_pu8STDlData);
		g_pu8STDlData = NULL;
	}
	
    g_pu8STDlData = kmalloc(u16Len,GFP_KERNEL);
    if(g_pu8STDlData == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

    s32Ret = IPF_ST_DL_ACore_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR(" TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
        return ERROR;
    }

    memset((unsigned int *)g_pu8STDlData, T_DL_VALUE, u16Len);
    memcpy((unsigned int *)g_pu8STDlData, &ipf_ipv4_head, sizeof(StreamIPv4Header));
    memcpy(g_pu8STDlData+sizeof(StreamIPv4Header), &ipf_udp, sizeof(StreamUDP));

	wake_empty_cb.rx_complete_cb = IpfDlIntCb302;
	wake_empty_cb.adq_empty_cb = IPF_ST_DL_FlushAD;
	mdrv_ipf_register_ops(&wake_empty_cb);
	
    IPF_TEST_ERR(" ul ccore init ok\n");
    return OK;
}

int BSP_IPF_ST_303_INIT(void)
{
    return BSP_IPF_ST_302_INIT();
}

int BSP_IPF_ST_304_INIT(void)
{    
    int s32Ret = 0;
	struct mdrv_ipf_ops wake_empty_cb;
    s32Ret = IPF_ST_DL_ACore_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR(" TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
        return ERROR;
    }

	wake_empty_cb.rx_complete_cb = IpfDlIntCb304;
	wake_empty_cb.adq_empty_cb = IPF_ST_DL_FlushAD;
	mdrv_ipf_register_ops(&wake_empty_cb);
    IPF_TEST_ERR(" ul ccore init ok\n");
  
    return OK;
}

int bsp_ipf_dl_confirm(void)
{
	int tmp = 0;
	tmp = ipf_dl_confirm;
	ipf_dl_confirm = 0;
	
	return tmp;
}

void BSP_IPF_ST_321_Result(void)
{
		IPF_TEST_PRINT(" g_u32DlError(BDs) :%d\n",g_u32DlError);
		IPF_TEST_PRINT(" g_u32DlFltError(BDs) :%d\n",g_u32DlFltError);
		IPF_TEST_PRINT(" g_u32DlTotalDataNum(KB) :%d\n",g_u32DlTotalDataNum);
		IPF_TEST_PRINT(" g_u32DlTotalBDNum(BDs) :%d\n",g_u32DlTotalBDNum);
}

/*下行压力测试A核准备函数*/
int BSP_IPF_ST_321_INIT(void)
{
    int s32Ret = 0;
    unsigned int u16Len = 1000;
    unsigned char* pu8IPData;
    unsigned char* pu8IPData1;
    unsigned char* pu8IPData2;
    unsigned char* pu8IPData3;
    unsigned char* pu8IPData4;
    unsigned int u32Len = 200;
	struct mdrv_ipf_ops wake_empty_cb;

	if(g_pu8STDlData != NULL)
		kfree(g_pu8STDlData);
	
    g_pu8STDlData = kmalloc(u16Len,GFP_KERNEL);
    if(g_pu8STDlData == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

    pu8IPData = (unsigned char*)kmalloc(u32Len,GFP_KERNEL);
    if(pu8IPData == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error1;
    }

    pu8IPData1 = (unsigned char*)kmalloc(u32Len,GFP_KERNEL);
    if(pu8IPData1 == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error2;
    }
	
    pu8IPData2 = (unsigned char*)kmalloc(u32Len,GFP_KERNEL);
    if(pu8IPData2 == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error3;
    }
	
    pu8IPData3 = (unsigned char*)kmalloc(u32Len,GFP_KERNEL);
    if(pu8IPData3 == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error4;
    }
	
    pu8IPData4 = (unsigned char*)kmalloc(u32Len,GFP_KERNEL);
    if(pu8IPData4 == NULL)
    {
        IPF_TEST_ERR(" TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error5;
    }

	ipf_set_acore_reset_flag(1);
    s32Ret = IPF_ST_DL_ACore_INIT();
    if(s32Ret != OK)
    {
        IPF_TEST_ERR(" TESTERROR    IPF_ST_UL_INIT :%d\n",__LINE__);
        return ERROR;
    }

	memset(pu8IPData, T_DL_VALUE, u32Len);
    memcpy(pu8IPData, &ipf_ipv4_head, sizeof(StreamIPv4Header));
    memcpy(pu8IPData+sizeof(StreamIPv4Header), &ipf_udp, sizeof(StreamUDP));
    memset(pu8IPData1, T_DL_VALUE, u32Len);
    memset(pu8IPData2, T_DL_VALUE, u32Len);
    memset(pu8IPData3, T_DL_VALUE, u32Len);
    memset(pu8IPData4, T_DL_VALUE, u32Len);

    memset((unsigned int *)g_pu8STDlData, T_DL_VALUE, u16Len);
    memcpy((unsigned int *)g_pu8STDlData, &ipf_ipv4_head, sizeof(StreamIPv4Header));
    memcpy(g_pu8STDlData+sizeof(StreamIPv4Header), &ipf_udp, sizeof(StreamUDP));
    memcpy(g_pu8STDlData+sizeof(StreamIPv4Header)+u32Len, pu8IPData1, u32Len);
    memcpy(g_pu8STDlData+sizeof(StreamIPv4Header)+u32Len*2, pu8IPData2, u32Len);
    memcpy(g_pu8STDlData+sizeof(StreamIPv4Header)+u32Len*3, pu8IPData3, u32Len);
    memcpy(g_pu8STDlData+sizeof(StreamIPv4Header)+u32Len*4, pu8IPData4, u32Len);
	
	wake_empty_cb.rx_complete_cb = IpfDltestIntCb;
	wake_empty_cb.adq_empty_cb = IPF_ST_DL_FlushAD;
	mdrv_ipf_register_ops(&wake_empty_cb);
    s32Ret = bsp_ipf_config_timeout(0x65);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_TEST_ERR(" TESTERROR    bsp_ipf_config_timeout :%d\n",__LINE__);
        return ERROR;
    }

    IPF_TEST_ERR(" ul ccore init ok\n");
	kfree(pu8IPData1);
	kfree(pu8IPData2);
	kfree(pu8IPData3);
	kfree(pu8IPData4);
    return OK;
error5:
	kfree(pu8IPData3);
error4:
	kfree(pu8IPData2);
error3:
	kfree(pu8IPData1);
error2:
	kfree(pu8IPData);
error1:
	kfree(g_pu8STDlData);
    return ERROR;
   
}

//5xx ccore rest
/*ipf数传复位回调测试，
检测内存使用情况，查看能否正常释放
在用例中反复分配和释放内存，
注意覆场景(回退个数，回退到0之前)
用例使用开关AD的方式调整AD读写指针*/
IPF_AD_DESC_S ad0_buffer[IPF_DLAD0_DESC_SIZE];
IPF_AD_DESC_S ad1_buffer[IPF_DLAD1_DESC_SIZE];
IPF_AD_DESC_S ad_result_buffer[IPF_DLAD0_DESC_SIZE];

void print_ad_status(void)
{
	unsigned int current_ad_wptr,current_ad_rptr,current_ad_offset,current_ad_state;

	/*打印下行AD读写指针位置，确定预读状态*/
	current_ad_wptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_WPTR_OFFSET);
	current_ad_rptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_RPTR_OFFSET);
	current_ad_state = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_STAT_OFFSET);
	if(current_ad_state & IPF_ADQ_BUF_EPT_MASK)
	{
		current_ad_offset = 0; 
	}
	else if(current_ad_state & IPF_ADQ_BUF_FULL_MASK)
	{
		current_ad_offset = 2; 
	}
	else
	{
		current_ad_offset = 1;    
	}

	IPF_TEST_PRINT(" ADQ0	current_ad_wptr =%u	current_ad_rptr = %u	current_ad_offset = %u \n",current_ad_wptr, current_ad_rptr, current_ad_offset);

	current_ad_wptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_WPTR_OFFSET);
	current_ad_rptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_RPTR_OFFSET);
	current_ad_state = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_STAT_OFFSET);
	if(current_ad_state & IPF_ADQ_BUF_EPT_MASK)
	{
		current_ad_offset = 0; 
	}
	else if(current_ad_state & IPF_ADQ_BUF_FULL_MASK)
	{
		current_ad_offset = 2; 
	}
	else
	{
		current_ad_offset = 1;    
	}

	IPF_TEST_PRINT(" ADQ1	current_ad_wptr =%u	current_ad_rptr = %u	current_ad_offset = %u \n",current_ad_wptr, current_ad_rptr, current_ad_offset);
}


/*ipf数传复位回调测试，初始化ipf
用于测试数传停止是否成功*/
void BSP_IPF_ST_501_INIT(unsigned int reset_flag)
{
	if(0 == reset_flag)
	{
		bsp_ipf_set_control_flag_for_ccore_reset(IPF_FORRESET_CONTROL_ALLOW);
		IPF_TEST_PRINT("\r eanble ipf transfer. \n");
	}
	else
	{
		bsp_ipf_set_control_flag_for_ccore_reset(IPF_FORRESET_CONTROL_FORBID);
		IPF_TEST_PRINT("\r eanble ipf transfer. \n");
	}
}

/*ipf数传复位回调测试，
用于测试数传停止是否成功
进行数传，预期返回失败*/
void BSP_IPF_ST_501_ACORE(void)
{
    IPF_CONFIG_ULPARAM_S stUlPara[IPF_ULBD_DESC_SIZE];	
    int s32Ret;
    /*调用ConfigUpFilter*/
    s32Ret = mdrv_ipf_config_ulbd(5, stUlPara);

    if(s32Ret != BSP_ERR_IPF_CCORE_RESETTING)
    {
        IPF_TEST_ERR(" TESTERROR    mdrv_ipf_config_ulbd :%d s32Ret = %x\n",__LINE__, s32Ret);
    }
    else
    {
        IPF_TEST_PRINT(" SUCCESS \n");
    }
}

int BSP_IPF_ST_502(unsigned int target_ad_wptr, unsigned int target_ad_rptr, unsigned int ad_len)
{

	unsigned int u32ADCtrl[IPF_CHANNEL_MAX] = {0,0};
	unsigned int i;
	int ret;
	unsigned int ad_num=0;
	unsigned int ad0_addr;
	unsigned int ad0_size;
	unsigned int ad1_addr;
	unsigned int ad1_size;
	

	for(i=0; i<IPF_DLAD0_DESC_SIZE; i++)
	{
		ad0_buffer[i].u32OutPtr0= i+0xf0000;
		ad0_buffer[i].u32OutPtr1= i*2+0xf0000;
	}
	for(i=0; i<IPF_DLAD0_DESC_SIZE; i++)
	{
		ad1_buffer[i].u32OutPtr0 = i+0xff0000;
		ad1_buffer[i].u32OutPtr1 = i*2+0xff0000;
	}

	/*禁止下行AD，即将下行通道调整为v7r1模式，清空ad队列*/
	u32ADCtrl[IPF_CHANNEL_DOWN] = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH1_ADQ_CTRL_OFFSET);
	u32ADCtrl[IPF_CHANNEL_DOWN] &= IPF_ADQ_EN_MASK;
	u32ADCtrl[IPF_CHANNEL_DOWN] |= (IPF_NONE_ADQ_EN);

	/*关闭ADQ通道，用于防止产生ADQ预取*/
	ipf_writel(u32ADCtrl[IPF_CHANNEL_DOWN], g_ipf_ctx.regs + HI_IPF_CH1_ADQ_CTRL_OFFSET);

	/*清空ad队列*/
	ad0_size = bsp_ipf_ad0_info(&ad0_addr);
	ad1_size = bsp_ipf_ad1_info(&ad1_addr);
	memset((void *)ad0_addr, 0xFFFFFFFF, ad0_size);
	memset((void *)ad1_addr, 0xFFFFFFFF, ad1_size);

	/*reset unreset ipf*/
	ipf_writel(1, g_ipf_ctx.regs + HI_IPF_SRST_OFFSET); 

	ipf_writel(0, g_ipf_ctx.regs + HI_IPF_SRST_OFFSET); 

	
	/*打印当前AD队列情况*/
	print_ad_status();
	
	/*将AD读写指针配置为特定值*/
	ipf_writel(target_ad_wptr, g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_WPTR_OFFSET);
	ipf_writel(target_ad_rptr, g_ipf_ctx.regs + HI_IPF_CH1_ADQ0_RPTR_OFFSET);
	ipf_writel(target_ad_wptr, g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_WPTR_OFFSET);
	ipf_writel(target_ad_rptr, g_ipf_ctx.regs + HI_IPF_CH1_ADQ1_RPTR_OFFSET);
	
	/*允许下行AD*/
	u32ADCtrl[IPF_CHANNEL_UP] |= (IPF_BOTH_ADQ_EN);
	u32ADCtrl[IPF_CHANNEL_DOWN] |= (IPF_BOTH_ADQ_EN);
	ipf_writel(u32ADCtrl[IPF_CHANNEL_UP], g_ipf_ctx.regs + HI_IPF_CH0_ADQ_CTRL_OFFSET);
	ipf_writel(u32ADCtrl[IPF_CHANNEL_DOWN], g_ipf_ctx.regs + HI_IPF_CH1_ADQ_CTRL_OFFSET);
	

	/*通过configAD给代码配入特定个数个AD，每个ad填入特定值，记录填入的ad数*/
	ret = mdrv_ipf_config_dlad(IPF_AD_0, ad_len, ad0_buffer);
	if(IPF_SUCCESS != ret)
	{
		IPF_TEST_ERR("BSP_IPF_ConfigDlAd0 fail \n");
		return IPF_ERROR;
	}

	ret = mdrv_ipf_config_dlad(IPF_AD_1, ad_len, ad1_buffer);
	if(IPF_SUCCESS != ret)
	{
		IPF_TEST_ERR("BSP_IPF_ConfigDlAd1 fail \n");
		return IPF_ERROR;
	}

	/*打印下行AD读写指针位置，确定预读状态*/
	print_ad_status();
	
	/*调用底软接口获取需要释放的ad*/
	ret = mdrv_ipf_get_used_dlad(IPF_AD_0, &ad_num, ad_result_buffer);
	if(IPF_SUCCESS != ret)
	{
		IPF_TEST_ERR("BSP_IPF_GetUsedDlAd0 fail \n");
		return IPF_ERROR;
	}

	/*与configad配给ipf的ad进行比较，查看是否正确*/

	if(ad_num != ad_len)
	{
		IPF_TEST_PRINT("AD0 num get unequal to AD num set. \n ad_get_num is %u; ad_set_num is %u; \n", ad_num, ad_len);
	}
	for(i=0; i<ad_num; i++)
	{
		if((ad_result_buffer[i].u32OutPtr0 != ad0_buffer[i].u32OutPtr0)
			||(ad_result_buffer[i].u32OutPtr1 != ad0_buffer[i].u32OutPtr1))
		{
			IPF_TEST_PRINT("ad0_buffer[%u].u32OutPtr0 = %u; ad_result_buffer[%u].u32OutPtr0 = %u \n",i,ad0_buffer[i].u32OutPtr0,i,ad_result_buffer[i].u32OutPtr0);
			IPF_TEST_PRINT("ad0_buffer[%u].u32OutPtr1 = %u; ad_result_buffer[%u].u32OutPtr1 = %u \n",i,ad0_buffer[i].u32OutPtr1,i,ad_result_buffer[i].u32OutPtr1);
		}
	}

	/*调用底软接口获取需要释放的ad*/
	ret = mdrv_ipf_get_used_dlad(IPF_AD_1, &ad_num, ad_result_buffer);
	if(IPF_SUCCESS != ret)
	{
		IPF_TEST_ERR("BSP_IPF_GetUsedDlAd1 fail \n");
		return IPF_ERROR;
	}
	
	/*与configad配给ipf的ad进行比较，查看是否正确*/

	if(ad_num != ad_len)
	{
		IPF_TEST_PRINT("AD1 num get unequal to AD num set. \n ad_get_num is %u; ad_set_num is %u; \n", ad_num, ad_len);
	}
	for(i=0; i<ad_num; i++)
	{
		if((ad_result_buffer[i].u32OutPtr0 != ad1_buffer[i].u32OutPtr0)
			||(ad_result_buffer[i].u32OutPtr1 != ad1_buffer[i].u32OutPtr1))
		{
			IPF_TEST_PRINT("ad1_buffer[%u].u32OutPtr0 = %u; ad_result_buffer[%u].u32OutPtr0 = %u \n",i,ad1_buffer[i].u32OutPtr0,i,ad_result_buffer[i].u32OutPtr0);
			IPF_TEST_PRINT("ad1_buffer[%u].u32OutPtr1 = %u; ad_result_buffer[%u].u32OutPtr1 = %u \n",i,ad1_buffer[i].u32OutPtr1,i,ad_result_buffer[i].u32OutPtr1);
		}
	}
	return IPF_SUCCESS;
}

/*ipf数传复位回调测试，
模拟复位全流程，本函数停止数传
reset、unreset ipf
调用Acore ipf接口回调重新初始化acore ipf
*/
void BSP_IPF_ST_503(void)
{
	bsp_ipf_set_control_flag_for_ccore_reset(IPF_FORRESET_CONTROL_FORBID);
	/*省略了释放内存的步骤是因为
	1.相关函数已经在case 502中充分测试过了
	2.释放内存是为了防止内存泄露，用例中不用考虑这种场景*/

	/*reset unreset ipf*/
	ipf_writel(1, g_ipf_ctx.regs + HI_IPF_SRST_OFFSET); 

	ipf_writel(0, g_ipf_ctx.regs + HI_IPF_SRST_OFFSET); 

	
	/*run ipf acore reg reinit*/
	bsp_ipf_set_control_flag_for_ccore_reset(IPF_FORRESET_CONTROL_ALLOW);

	mdrv_ipf_reinit_dlreg();


	IPF_TEST_PRINT( "\r run ipf_init on ccore shell then run testcase 321 and 121\n");
}

/*module_param(g_ipftestdebug, int, 0);*/

#ifdef __cplusplus
}
#endif

