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

#include <linux/string.h>
#include <linux/delay.h>
#include <osl_cache.h>
#include <osl_thread.h>
#include <linux/slab.h>
#include <linux/semaphore.h>

#include <hi_ipf.h>
#include <bsp_om.h>
#include <psam_balong.h>
#include <bsp_ipf.h>
#include <../ipf/ipf_balong.h>

#ifdef CONFIG_MODULE_BUSSTRESS
#include <bsp_busstress.h>
#endif
//dts
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>

#define PACKET_VALUE 0x5a
#define NON_STRAIGHT_P_V 0x00

typedef int (*psam_thread_fn)(void *pdata);

#pragma pack(push) 
#pragma pack(1)

typedef struct _IPHDR
{
    unsigned int TOL:16;
    unsigned int TOS:8;
    unsigned int HeaderLen:4;
    unsigned int Vers:4; 
    unsigned int offset:13;
    unsigned int MF:1;
    unsigned int DF:1;
    unsigned int ReservFlag:1;
    unsigned int ID:16;
    unsigned int Checksum:16;
    unsigned int Prot:8;
    unsigned int TTL:8;    
    unsigned int SourceAddr;
    unsigned int DestAddr;
}ETH_TEST_IPHDR_T;

typedef struct _IP_PACKET_FORMAT
{
    /* IP头 */
    ETH_TEST_IPHDR_T     stSCTPHdr;

    /* UDP头 */
    unsigned int DstPort:16;
    unsigned int SrcPort:16;
    unsigned int Checksum:16;
    unsigned int Length:16; 
}ETH_TEST_IP_PACKET_FORMAT_T;
#pragma pack(pop)

typedef enum tagPSAM_ADQ_CONFIG_E
{
    CONFIG_AD = 0,
    STOP_CONFIG_AD = 1
}PSAM_ADQ_CONFIG_E;

//
unsigned int deb_test = 0;
#define PSAM_TEST_PRINT(fmt,...)     \
do{\
	if(deb_test){\
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM, fmt,##__VA_ARGS__);\
	}\
}while(0);
#define PSAM_TEST_ERR(fmt,...)     \
do{\
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM, fmt,##__VA_ARGS__);\
}while(0);

//
static PSAM_AD_DESC_S ADdlshort[PSAM_DLAD0_DESC_SIZE];
static PSAM_AD_DESC_S ADdllong[PSAM_DLAD1_DESC_SIZE];
static unsigned char  * g_pu8STDlData = NULL;
static unsigned char * g_STDlData_long = NULL;
static unsigned char * g_STDlData_mid = NULL;
static int psam_dl_confirm = 0;

PSAM_ADQ_CONFIG_E psam_config_ad_flag = CONFIG_AD;

unsigned int psam_u32DlError=0;
unsigned int psam_u32DlFltError=0;
unsigned int psam_u32DlTotalDataNum = 0;
unsigned int psam_u32DlTotalBDNum = 0;

unsigned int psam_st_DlError=0;
unsigned int psam_st_DlFltError=0;
unsigned int psam_st_Dl_rd_full_times = 0;
unsigned int psam_st_DlTotalDataNum = 0;
unsigned int cipher_st_DlTotalBDNum = 0;
unsigned int psam_st_DlTotalBDNum = 0;

unsigned int psam_kfree_cnt = 0;
unsigned int psam_kmalloc_long_cnt = 0;
unsigned int psam_kmalloc_short_cnt = 0;

unsigned int long_ad_cnt = 0;
unsigned int short_ad_cnt = 0;

struct semaphore psam_dl_task_sem_id;
struct semaphore psam_dl_int_sem_id;
static unsigned int psam_test_acore_init = 0;

extern struct psam_device *g_psam_device;

void psam_test_debug_switch(unsigned int num)
{
	deb_test = num;
}
static void stmmac_EthTestBuildIpHdr(ETH_TEST_IP_PACKET_FORMAT_T *pstPkt, unsigned int ulLen)
{
	pstPkt->stSCTPHdr.Vers = 4;
    pstPkt->stSCTPHdr.HeaderLen = 5;
    pstPkt->stSCTPHdr.TOS = 3;
    pstPkt->stSCTPHdr.TOL = ulLen;
    pstPkt->stSCTPHdr.ID = 1;
    pstPkt->stSCTPHdr.ReservFlag = 0;
    pstPkt->stSCTPHdr.DF = 0;
    pstPkt->stSCTPHdr.MF = 0;
    pstPkt->stSCTPHdr.offset = 0;
    pstPkt->stSCTPHdr.TTL = 128;
    pstPkt->stSCTPHdr.Prot = 17; /* UDP */
    pstPkt->stSCTPHdr.Checksum = 0xEC3A;
    pstPkt->stSCTPHdr.SourceAddr = 0xACA84649;
    pstPkt->stSCTPHdr.DestAddr = 0x0202014E;

    pstPkt->SrcPort = 5088;
    pstPkt->DstPort = 2923;
    pstPkt->Checksum = 0;
    pstPkt->Length = pstPkt->stSCTPHdr.TOL;
}

int psam_CmpDMAData(unsigned char* p1, unsigned char* p2, unsigned int u32Len)
{
    unsigned int i = 0;
    for(i=0; i<u32Len; i++)
    {
        if(*(unsigned char*)(p1+i) != *(unsigned char*)(p2+i))
        {
            return -1;
        }
    }
    return 0;
}

int psam_dl_init(void)
{
//用脚本直接在ccore调用，应为dallas v722的安全缘故，现在没法在acore使用reset
#if 0
	if(!psam_srset()){
		psam_reinit_regs();
		psam_test_acore_init = 1;
		return OK;
	}
	return ERROR;
#else
	//ccore reset psam cause sec
	psam_reinit_regs();
	psam_test_acore_init = 1;
	return OK;
#endif
}

int psam_st_dl_acore_init(void)
{
	int ret;
	unsigned int i;
	void * p_vir_addr;
	void * p_addr;

	if(psam_test_acore_init == 1)
    {
	   return 0;
	}
	
 	ret= psam_dl_init();
    if(ret != OK)
    {
	    IPF_PRINT("psam_st_acore init error :%d\n",__LINE__);
	    return ERROR;
    }
	
	for(i=0; i < PSAM_DLAD0_DESC_SIZE-1; i++)
	{    	
    	ADdlshort[i].u32OutPtr0 = (unsigned int)NULL;    
		p_vir_addr = kmalloc(438, GFP_KERNEL);    
		if(!p_vir_addr)
		//ADdlshort[i].u32OutPtr1 = (unsigned int)p_vir_addr;


		{
	    	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"ad short mem malloc failed. line:%d\n",__LINE__);
	        goto error1;
		}
		memset(p_vir_addr,0xdd,438);
		ADdlshort[i].u32OutPtr0 = dma_map_single(g_psam_device->dev, p_vir_addr, 438, DMA_TO_DEVICE); 
		ADdlshort[i].u32OutPtr1 = ADdlshort[i].u32OutPtr0; 
		psam_kmalloc_short_cnt++;
	}
	
	for(i=0; i < PSAM_DLAD1_DESC_SIZE-1; i++)
	{
    	ADdllong[i].u32OutPtr0 = (unsigned int)NULL;
		p_vir_addr = kmalloc(1500, GFP_KERNEL);  
		if(!p_vir_addr)
    	//ADdllong[i].u32OutPtr1 = (unsigned int)p_vir_addr;    

		{
	    	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"ad short mem malloc failed. line:%d\n",__LINE__);
	        goto error1;
		}
		memset(p_vir_addr,0xdd,1500);
		ADdllong[i].u32OutPtr0 = dma_map_single(g_psam_device->dev, p_vir_addr, 1500, DMA_TO_DEVICE);;   
		ADdllong[i].u32OutPtr1 = ADdllong[i].u32OutPtr0; 
		psam_kmalloc_long_cnt++;
	}

	ret = mdrv_ipf_config_dlad(IPF_AD_0,PSAM_DLAD0_DESC_SIZE-PSAM_ADQ_RESERVE_NUM,&ADdlshort[0]);
	if(ret != 0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"config ad short error. line :%d ret = %x\n",__LINE__, ret);
		return -1;
	}    

	ret = mdrv_ipf_config_dlad(IPF_AD_1,PSAM_DLAD1_DESC_SIZE-PSAM_ADQ_RESERVE_NUM,&ADdllong[0]);
	if(ret != 0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"config ad long error. line :%d ret = %x\n",__LINE__, ret);
		return -1;
	}
    return 0;

error1:
	for(i=0; i < PSAM_DLAD0_DESC_SIZE-1; i++)
	{
		if(!(ADdlshort[i].u32OutPtr1))
		{
			kfree((unsigned int *)(ADdlshort[i].u32OutPtr1));
		}
	}

	for(i=0; i < PSAM_DLAD0_DESC_SIZE-1; i++)
	{
		if(!(ADdllong[i].u32OutPtr1))
		{
			kfree((unsigned int *)(ADdllong[i].u32OutPtr1));
		}
	}

	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"test acore dl init malloc failed!\n");
	
	return -1;
}

int psam_st_dl_flush_Ad(IPF_ADQ_EMPTY_E eAdqEmptyDl)
{
	int ret;  
	unsigned int i;
	void * p_vir_addr;
	
	if(CONFIG_AD !=  psam_config_ad_flag)
	{
		return 0;
	}

	if(IPF_EMPTY_ADQ0 == eAdqEmptyDl)
	{
		for(i=0; i < PSAM_DLAD0_DESC_SIZE-1; i++)
		{    	
	    	ADdlshort[i].u32OutPtr0 = (unsigned int)NULL;    
			p_vir_addr = kmalloc(438, GFP_ATOMIC);   
			if(!p_vir_addr)
			//ADdlshort[i].u32OutPtr1 = (unsigned int)p_vir_addr;


			{
		    	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," TESTERROR    IPF_ST_DL_INIT ADMEMmallocfail:%d\n",__LINE__);
		        goto error1;
			}
			memset(p_vir_addr,0xdd,438);
			ADdlshort[i].u32OutPtr0 = dma_map_single(g_psam_device->dev, p_vir_addr, 438, DMA_TO_DEVICE);;  
			ADdlshort[i].u32OutPtr1 = ADdlshort[i].u32OutPtr0;
			psam_kmalloc_short_cnt++;
		}
		ret = mdrv_ipf_config_dlad(IPF_AD_0,PSAM_DLAD0_DESC_SIZE-PSAM_ADQ_RESERVE_NUM,&ADdlshort[0]);
		if(ret != 0)
		{
			bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," TESTERROR    IPF_ST_UL_FlashAD :%d ret = %x\n",__LINE__, ret);
			return -1;
		}
	}
	else if(IPF_EMPTY_ADQ1 == eAdqEmptyDl)
	{
		for(i=0; i < PSAM_DLAD1_DESC_SIZE-1; i++)
		{
	    	ADdllong[i].u32OutPtr0 = (unsigned int)NULL;
			p_vir_addr = kmalloc(1500, GFP_ATOMIC);  
			if(!p_vir_addr)
	    	//ADdllong[i].u32OutPtr1 = (unsigned int)p_vir_addr;    

			{
		        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," TESTERROR    IPF_ST_DL_INIT ADMEMmallocfail:%d\n",__LINE__);
		        goto error1;
			}
			memset(p_vir_addr,0xdd,1500);
			ADdllong[i].u32OutPtr0 = dma_map_single(g_psam_device->dev, p_vir_addr, 1500, DMA_TO_DEVICE); 
			ADdllong[i].u32OutPtr1 = ADdllong[i].u32OutPtr0; 
			psam_kmalloc_long_cnt++;
		}
		ret = mdrv_ipf_config_dlad(IPF_AD_1,PSAM_DLAD1_DESC_SIZE-PSAM_ADQ_RESERVE_NUM,&ADdllong[0]);
		if(ret != 0)
		{
			bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," TESTERROR    IPF_ST_UL_FlashAD :%d ret = %x\n",__LINE__, ret);
			return -1;
		}
	}
	else
	{
		return -1;
	}
	
	return 0;
error1:
	for(i=0; i < PSAM_DLAD0_DESC_SIZE-1; i++)
	{
		if(!(ADdlshort[i].u32OutPtr1))
		{
			kfree((unsigned int *)(ADdlshort[i].u32OutPtr1));
		}
	}

	for(i=0; i < PSAM_DLAD0_DESC_SIZE-1; i++)
	{
		if(!(ADdllong[i].u32OutPtr1))
		{
			kfree((unsigned int *)(ADdllong[i].u32OutPtr1));
		}
	}

	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"test acore flush ad malloc failed!\n");
	
	return -1;
}


int psam_st_dl_stress_flush_Ad(IPF_ADQ_EMPTY_E eAdqEmptyDl)
{

	int ret;  
	unsigned int i;
	void * p_vir_addr;
	
	if(CONFIG_AD !=  psam_config_ad_flag)
	{
		return 0;
	}

	if(IPF_EMPTY_ADQ0 == eAdqEmptyDl)
	{
		ret = mdrv_ipf_config_dlad(IPF_AD_0,PSAM_DLAD0_DESC_SIZE-PSAM_ADQ_RESERVE_NUM,&ADdlshort[0]);
		if(ret != 0)
		{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," TESTERROR    IPF_ST_UL_FlashAD :%d ret = %x\n",__LINE__, ret);
		return -1;
		}
	}
	else if(IPF_EMPTY_ADQ1 == eAdqEmptyDl)
	{
		ret = mdrv_ipf_config_dlad(IPF_AD_1,PSAM_DLAD1_DESC_SIZE-PSAM_ADQ_RESERVE_NUM,&ADdllong[0]);
		if(ret != 0)
		{
			bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," TESTERROR    IPF_ST_UL_FlashAD :%d ret = %x\n",__LINE__, ret);
			return -1;
		}
	}
	else
	{
		return -1;
	}
	
	return 0;
}

void psam_print_ch1_Ad_num(void)
{
	HI_IPF_CH1_ADQ0_STAT_T ad0_stat;
	HI_IPF_CH1_ADQ1_STAT_T ad1_stat;
	ad0_stat.u32 = readl(g_psam_device->regs + HI_PSAM_ADQ0_STAT_OFFSET);
	ad1_stat.u32 = readl(g_psam_device->regs + HI_PSAM_ADQ1_STAT_OFFSET);

	if((ad0_stat.bits.dl_adq0_buf_epty == 1)&&(ad0_stat.bits.dl_adq0_buf_full == 1))
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"\r CH1_AD0_BUF_FLAG_ERROR.\n");
	}
	else if(ad0_stat.bits.dl_adq0_buf_full == 1)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"\r CH1_AD0_BUF_NUM 2,2 unused AD in AD_Buff.\n");
	}
	else if(ad0_stat.bits.dl_adq0_buf_epty == 1)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"\r CH1_AD0_BUF_NUM 0,0 unused AD in AD_Buff.\n");
	}
	else
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"\r CH1_AD0_BUF_NUM 1,1 unused AD in AD_Buff.\n");
	}
	
	if((ad1_stat.bits.dl_adq1_buf_epty == 1)&&(ad1_stat.bits.dl_adq1_buf_full == 1))
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"\r CH1_AD1_BUF_FLAG_ERROR.\n");
	}
	else if(ad1_stat.bits.dl_adq1_buf_full == 1)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"\r CH1_AD1_BUF_NUM 2,2 unused AD in AD_Buff.\n");
	}
	else if(ad1_stat.bits.dl_adq1_buf_epty == 1)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"\r CH1_AD1_BUF_NUM 0,0 unused AD in AD_Buff.\n");
	}
	else
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"\r CH1_AD1_BUF_NUM 1,1 unused AD in AD_Buff.\n");
	}
	return;
}

#ifdef CONFIG_MODULE_BUSSTRESS
int psam_dl_int_cb(void)
{
	//bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"--- acore intrrupt\n");
    up(&psam_dl_int_sem_id);
    return OK;
}
int psam_dl_task_1(void)
{
	unsigned int u32Num = PSAM_DLRD_DESC_SIZE;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int u32RecivedData = 0;
	int ret = 0;
	unsigned int *p = NULL;
	unsigned int *q = NULL;
	IPF_RD_DESC_S stRd[PSAM_DLRD_DESC_SIZE];
	static unsigned int 	tmp = 0;
	
	/*处理RD*/
	while(1)
	{
		down(&psam_dl_int_sem_id);
		
		u32Num = PSAM_DLRD_DESC_SIZE;
		mdrv_ipf_get_dlrd(&u32Num, stRd);

		if(u32Num == 64)
			psam_st_Dl_rd_full_times++;
#if 0	
		for(j = 0; j < u32Num; j++)
		{	
			//cihper的usrfiled1==0, 用这样来区分直通、非直通的数据包
			if(stRd[j].u32UsrField2 != 0){
				if((stRd[j].u32UsrField2 - tmp) != 1){
					//bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"cipher cnt error, cur is %d, pre is %d\n",stRd[j].u32UsrField2,tmp);
				}
				tmp = stRd[j].u32UsrField2;
			}
			
			stRd[j].u16UsrField1==200?(psam_st_DlTotalBDNum++):(cipher_st_DlTotalBDNum++);

			dma_unmap_single(g_psam_device->dev, (void*)(stRd[j].u32UsrField3), stRd[j].u16PktLen, DMA_FROM_DEVICE);

			if(0 == stRd[j].u32OutPtr)
			{
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"stRd[%d].u32OutPtr =%x !return error\n",j,stRd[j].u32OutPtr);
				return -1;
			}

			if(stRd[j].u16PktLen == 50){
				//short packet 50
				ret = psam_CmpDMAData(g_pu8STDlData, (unsigned char *)stRd[j].u32UsrField3, stRd[j].u16PktLen);
				q = (unsigned int *)g_pu8STDlData;
			}
			else if(stRd[j].u16PktLen == 500){
				//mid packet 1000
				ret = psam_CmpDMAData(g_STDlData_mid, (unsigned char *)stRd[j].u32UsrField3, stRd[j].u16PktLen);
				q = (unsigned int *)g_STDlData_mid;
			}
			else{
				//long packet 1500
				ret = psam_CmpDMAData(g_STDlData_long, (unsigned char *)stRd[j].u32UsrField3, stRd[j].u16PktLen);
				q = (unsigned int *)g_STDlData_long;
			}
			u32RecivedData += stRd[j].u16PktLen;

			/*数据比对*/
			if(0 != ret){
				psam_st_DlError++;
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"cipher cnt error, cur is %d\n",stRd[j].u32UsrField2);
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"stRd[%d].u32OutPtr =%x stRd[%d].u16PktLen =%u \n",j,stRd[j].u32OutPtr,j,stRd[j].u16PktLen);
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"stRd[%d].u32OutPtr =%x stRd[%d].u16UsrField1 =%u \n",j,stRd[j].u32OutPtr,j,stRd[j].u16UsrField1);

				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"g_pu8STDlData,u32Num = %u\n",u32Num);
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"===================================\n");
				p=q;
				for(i=0; i<10; i+=4)
				{
					bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"0x%08x	0x%08x	  0x%08x	0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
				}
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"0x%08x	0x%08x\n", *(p+i), *(p+i+1));
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"Err stRd[%d].u32OutPtr =%x\n",j,stRd[j].u32OutPtr);
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"===================================\n");
				p=(unsigned int *)stRd[j].u32OutPtr;
				for(i=0; i<10; i+=4)
				{
					bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"0x%08x	0x%08x	  0x%08x	0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
				}
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"0x%08x	0x%08x\n", *(p+i), *(p+i+1));
			}
			if(stRd[j].u16Result == 0x3f){
				psam_st_DlFltError++;
			}
			
			if(stRd[j].u16PktLen <= 438){
				memset((unsigned int *)stRd[j].u32UsrField3, 0x00, 438);
				*((unsigned int *)stRd[j].u32UsrField3) = stRd[j].u32UsrField2;
			}
			else{
				memset((unsigned int *)stRd[j].u32UsrField3, 0x00, 1500);
				*((unsigned int *)stRd[j].u32UsrField3) = stRd[j].u32UsrField2;
			}
			
			kfree((unsigned int *)(stRd[j].u32UsrField3));
			psam_kfree_cnt++;
		}
#endif		
		//mdelay(200);
		u32RecivedData = u32RecivedData/1024;
		psam_st_DlTotalDataNum += u32RecivedData;

		up(&psam_dl_task_sem_id);
	}
}

int psam_st_dl_init_stress(void)
{
    sema_init(&psam_dl_task_sem_id, 0);
    sema_init(&psam_dl_int_sem_id, 0);

    kthread_run((psam_thread_fn)psam_dl_task_1, NULL, "psam_dl_task");  

    return OK;
}
#endif

int psam_dl_int_cb_001(void)
{
	unsigned int j;
	unsigned int u32AD0Num;
	unsigned int u32AD1Num;
	unsigned int u32Num = PSAM_DLRD_DESC_SIZE;
	IPF_RD_DESC_S stRd[PSAM_DLRD_DESC_SIZE];
	
	mdrv_ipf_get_dlrd(&u32Num, stRd);

	PSAM_TEST_ERR("Data transfer Num:%d \n",u32Num);
	
	for(j = 0; j < u32Num; j++)
	{				
		kfree(phys_to_virt(stRd[j].u32UsrField3));
	}
	
	psam_print_ch1_Ad_num();

	mdrv_ipf_get_dlad_num(&u32AD0Num, &u32AD1Num);
	PSAM_TEST_PRINT("Data transfer success! Num: %u \n AD0Num:%u AD1Num:%d \n",u32Num,u32AD0Num,u32AD1Num);
    return 0;
}

int psam_dl_int_cb_002(void)
{
	unsigned int i,j;
	unsigned int u32AD0Num;
	unsigned int u32AD1Num;
	unsigned int u32Num = PSAM_DLRD_DESC_SIZE;
	int ret = 0;
	IPF_RD_DESC_S stRd[PSAM_DLRD_DESC_SIZE];
	unsigned int* p = NULL;
	unsigned int dl_error = 0;
	
	mdrv_ipf_get_dlrd(&u32Num, stRd);

	PSAM_TEST_ERR("Data transfer Num:%d \n",u32Num);
	
	for(j = 0; j < u32Num; j++)
	{	
		PSAM_TEST_PRINT("stRd[%d].u32OutPtr =%x\n",j,phys_to_virt(stRd[j].u32OutPtr));
		if(NULL == (unsigned int *)phys_to_virt(stRd[j].u32OutPtr))
		{
			PSAM_TEST_PRINT("stRd[%d].u32OutPtr =NULL !\n",i);
			return -1;
		}
		
		dma_unmap_single(g_psam_device->dev, (void*)(stRd[j].u32UsrField3), stRd[j].u16PktLen, DMA_FROM_DEVICE);

		ret = psam_CmpDMAData(g_pu8STDlData, (unsigned char *)phys_to_virt(stRd[j].u32UsrField3), stRd[j].u16PktLen);
		
		/*数据比对*/
		if(0 != ret)
		{
		    PSAM_TEST_PRINT("\r the %d rd compare failed!\n",j);
		    PSAM_TEST_PRINT("g_pu8STDlData\n");
		    PSAM_TEST_PRINT("===================================\n");
		    p=(unsigned int *)g_pu8STDlData;
		    for(i=0; i < (stRd[j].u16PktLen)/sizeof(unsigned int) - 1; i+=4)
		    {
		        PSAM_TEST_PRINT("0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
		    }
		    PSAM_TEST_PRINT("0x%08x    0x%08x\n", *(p+i), *(p+i+1));
		    PSAM_TEST_PRINT("stRd[%d].u32OutPtr\n",j);
            PSAM_TEST_PRINT("===================================\n");
            PSAM_TEST_PRINT("stRd[%d].u32OutPtr =%x\n",j,phys_to_virt(stRd[j].u32OutPtr));
		    p=(unsigned int *)phys_to_virt(stRd[j].u32OutPtr);
		    for(i=0; i < (stRd[j].u16PktLen)/sizeof(unsigned int) - 1; i+=4)
		    {
		        PSAM_TEST_PRINT("0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
		    }
		    PSAM_TEST_PRINT("0x%08x    0x%08x\n", *(p+i), *(p+i+1));
			psam_dl_confirm = ERROR;
			goto out;
		}	
	}
out:
	
	mdrv_ipf_get_dlad_num(&u32AD0Num, &u32AD1Num);
	if (j == u32Num) {
		PSAM_TEST_PRINT("Data transfer success! Num: %d \n AD0Num:%d AD1Num:%d \n",j,u32AD0Num,u32AD1Num);
	}
	for (j = 0; j < u32Num; j++ ) {
		kfree(phys_to_virt(stRd[j].u32UsrField3));
	}

	return 0;
}

int psam_dl_int_cb_003(void)
{
	unsigned int i,j;
	unsigned int u32AD0Num;
	unsigned int u32AD1Num;
	unsigned int u32Num = PSAM_DLRD_DESC_SIZE;
	int ret = 0;
	IPF_RD_DESC_S stRd[PSAM_DLRD_DESC_SIZE];
	unsigned int* p = NULL;
	unsigned int dl_error = 0;
	
	mdrv_ipf_get_dlrd(&u32Num, stRd);

	PSAM_TEST_ERR("Data transfer Num:%d \n",u32Num);
	
	for(j = 0; j < u32Num; j++)
	{	
		PSAM_TEST_PRINT("stRd[%d].u32OutPtr =%x stRd[%d].u16PktLen =%u \n",j,stRd[j].u32OutPtr,j,stRd[j].u16PktLen);
		if(NULL == (unsigned int *)phys_to_virt(stRd[j].u32OutPtr))
		{
			PSAM_TEST_PRINT("stRd[%d].u32OutPtr =NULL !\n",j);
			return -1;
		}

		dma_unmap_single(g_psam_device->dev, (void*)(stRd[j].u32UsrField3), stRd[j].u16PktLen, DMA_FROM_DEVICE);
		
		ret = psam_CmpDMAData(g_pu8STDlData, (unsigned char *)phys_to_virt(stRd[j].u32UsrField3), stRd[j].u16PktLen);
		
		/*数据比对*/
		if(0 != ret)
		{
		    PSAM_TEST_PRINT("Comp error \n");
		    PSAM_TEST_PRINT("g_pu8STDlData\n");
		    PSAM_TEST_PRINT("===================================\n");
		    p=(unsigned int *)g_pu8STDlData;
		    for(i=0; i < (stRd[j].u16PktLen)/sizeof(unsigned int) - 1; i+=4)
		    {
		        PSAM_TEST_PRINT("0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
		    }
		    PSAM_TEST_PRINT("0x%08x    0x%08x\n", *(p+i), *(p+i+1));
		    PSAM_TEST_PRINT("stRd[%d].u32OutPtr\n",j);
            PSAM_TEST_PRINT("===================================\n");
            PSAM_TEST_PRINT("stRd[%d].u32OutPtr =%x\n",j,phys_to_virt(stRd[j].u32OutPtr));
		    p=(unsigned int *)phys_to_virt(stRd[j].u32OutPtr);
		    for(i=0; i < (stRd[j].u16PktLen)/sizeof(unsigned int) - 1; i+=4)
		    {
		        PSAM_TEST_PRINT("0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
		    }
		    PSAM_TEST_PRINT("0x%08x    0x%08x\n", *(p+i), *(p+i+1));
			psam_dl_confirm = ERROR;
			goto out;
		}	
	}

out:
	mdrv_ipf_get_dlad_num(&u32AD0Num, &u32AD1Num);
	if (j == u32Num) {
		PSAM_TEST_PRINT("Data transfer success! Num: %d \n AD0Num:%d AD1Num:%d \n",j,u32AD0Num,u32AD1Num);
	}
	for (j = 0; j < u32Num; j++ ) {
		kfree(phys_to_virt(stRd[j].u32UsrField3));
	}
	
	return 0;
}

int psam_dl_int_cb_004(void)
{
	unsigned int j;
	unsigned int u32AD0Num;
	unsigned int u32AD1Num;
	unsigned int u32Num = PSAM_DLRD_DESC_SIZE;
	IPF_RD_DESC_S stRd[PSAM_DLRD_DESC_SIZE];
	unsigned int dl_error = 0;
	
	mdrv_ipf_get_dlrd(&u32Num, stRd);

	PSAM_TEST_ERR("Data transfer Num:%d \n",u32Num);
	
	for(j = 0; j < u32Num; j++)
	{	
		
		/*过滤结果*/
		if(stRd[j].u16Result == 0x3f)
		{
			PSAM_TEST_PRINT("stRd[%d].u16Result error ! value is 0x%x \n",j,stRd[j].u16Result);
			dl_error++;
			psam_dl_confirm = ERROR;
		}			
		kfree(phys_to_virt(stRd[j].u32UsrField3));
	}

	mdrv_ipf_get_dlad_num(&u32AD0Num, &u32AD1Num);

	PSAM_TEST_PRINT("Data filter error Num:%d \n",dl_error);
	PSAM_TEST_PRINT("Data transfer success! Num: %d \n AD0Num:%d AD1Num:%d \n",j,u32AD0Num,u32AD1Num);
    return 0;
}

int ipf_dl_test_int_cb(void)
{
    unsigned int u32Num = PSAM_DLRD_DESC_SIZE;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int u32RecivedData = 0;
    unsigned int u32AD0Num = 0;
    unsigned int u32AD1Num = 0;
    int ret = 0;
    unsigned int *p = NULL;
    IPF_RD_DESC_S stRd[PSAM_DLRD_DESC_SIZE];
    unsigned int	u32AD0wptr;
    unsigned int	u32AD1wptr;
	
	/*处理RD*/
    mdrv_ipf_get_dlrd(&u32Num, stRd);
    for(j = 0; j < u32Num; j++)
    {	
		dma_unmap_single(g_psam_device->dev, (void*)(stRd[j].u32UsrField3), stRd[j].u16PktLen, DMA_FROM_DEVICE);

		if(0 == phys_to_virt(stRd[j].u32OutPtr))
		{
	    	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"stRd[%d].u32OutPtr =%x !return error\n",j,phys_to_virt(stRd[j].u32OutPtr));
			return -1;
		}

		ret = psam_CmpDMAData(g_pu8STDlData, (unsigned char *)phys_to_virt(stRd[j].u32UsrField3), stRd[j].u16PktLen);
		u32RecivedData += stRd[j].u16PktLen;
		/*数据比对*/
		if(0 != ret)
		{
			psam_u32DlError++;
			
		    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"g_pu8STDlData,u32Num = %u\n",u32Num);
		    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"===================================\n");
		    p=(unsigned int *)g_pu8STDlData;
		    for(i=0; i<4; i+=4)
		    {
		        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
		    }
		    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"0x%08x    0x%08x\n", *(p+i), *(p+i+1));
          	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"Err stRd[%d].u32OutPtr =%x\n",j,phys_to_virt(stRd[j].u32OutPtr));
          	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"===================================\n");
		    p=(unsigned int *)phys_to_virt(stRd[j].u32OutPtr);
		    for(i=0; i<4; i+=4)
		    {
		        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
		    }
		    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"0x%08x    0x%08x\n", *(p+i), *(p+i+1));
		}
		
		if(stRd[j].u16Result == 0x3f)
		{
			psam_u32DlFltError++;
		}	
		
		if(stRd[j].u16PktLen <= 438){
			memset((unsigned int *)phys_to_virt(stRd[j].u32UsrField3), 0x00, 438);
			*((unsigned int *)phys_to_virt(stRd[j].u32UsrField3)) = stRd[j].u32UsrField2;
		}
		else{
			memset((unsigned int *)phys_to_virt(stRd[j].u32UsrField3), 0x00, 1500);
			*((unsigned int *)phys_to_virt(stRd[j].u32UsrField3)) = stRd[j].u32UsrField2;
		}
		
		kfree(phys_to_virt(stRd[j].u32UsrField3));
    }
	u32RecivedData = u32RecivedData/1024;
	/*统计结果*/
	psam_u32DlTotalDataNum += u32RecivedData;
	psam_u32DlTotalBDNum += u32Num;
	ret = mdrv_ipf_get_dlad_num(&u32AD0Num,&u32AD1Num);

	if(IPF_SUCCESS != ret){
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," TESTERROR    mdrv_ipf_get_dlad_num :%d\n",__LINE__);
	}
	
	return 0;
}



/////////////////////////////////////////////////////////////////////////////
//////////////////////////////*非直通测试用例*///////////////////////
/////////////////////////////////////////////////////////////////////////////
int bsp_psam_st_packet(void)
{	
	unsigned long u16Len =1000;
	g_pu8STDlData = kmalloc(u16Len,GFP_KERNEL);
	if(g_pu8STDlData == NULL)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"301 init cacheDmaMalloc :%d\n",__LINE__);
		return -1;
	}
	
	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T *)g_pu8STDlData, u16Len);
	memset(g_pu8STDlData + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), NON_STRAIGHT_P_V, u16Len - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
	return 0;
}

//接收两个包，一长一短，不做比较检查。
int bsp_psam_st_001_init(void)
{
    int ret = 0;

    ret = psam_st_dl_acore_init();
    if(ret != 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"300 init psam_st_dl_acore_init :%d\n",__LINE__);
        return -1;
    }
    
    ret = ipf_register_wakeup_dlcb(psam_dl_int_cb_001);
    if(ret != 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"300 init psam BSP_IPF_RegisterWakeupDlCb :%d\n",__LINE__);
        return -1;
    }   
	
    ret = psam_register_adq_empty_dlcb((adq_emtpy_cb_t)psam_st_dl_flush_Ad);
    if(ret != 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"300 init bsp_psam_register_Adq_empty_dl_cb :%d\n",__LINE__);
        return -1;
    }   
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," C core could start dl cases\n");

    return 0;
}

/* 1个TTF结点，配1个BD */
int bsp_psam_st_002_init(void)
{
    int ret = 0;
	
    ret = psam_st_dl_acore_init();
    if(ret != 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"301 init IPF_ST_DL_INIT :%d\n",__LINE__);
        return -1;
    }
    
    ret = ipf_register_wakeup_dlcb(psam_dl_int_cb_002);
    if(ret != IPF_SUCCESS)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"301 init BSP_IPF_RegisterWakeupDlCb :%d\n",__LINE__);
        return -1;
    }   
	
    ret = psam_register_adq_empty_dlcb((adq_emtpy_cb_t)psam_st_dl_flush_Ad);
    if(ret != IPF_SUCCESS)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"301 init BSP_IPF_RegisterWakeupDlCb :%d\n",__LINE__);
        return -1;
    }   
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," C core could start dl cases\n");

    return 0;
}

/* 5个TTF结点，配1个BD */
int bsp_psam_st_003_init(void)
{    
    int ret = 0;
    
    ret = psam_st_dl_acore_init();
    if(ret != 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"302 init IPF_ST_DL_INIT :%d\n",__LINE__);
        return -1;
    }
    
    ret = ipf_register_wakeup_dlcb(psam_dl_int_cb_003);
    if(ret != IPF_SUCCESS)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"302 init BSP_IPF_RegisterWakeupDlCb :%d\n",__LINE__);
        return -1;
    }   
	
    ret = psam_register_adq_empty_dlcb((adq_emtpy_cb_t)psam_st_dl_flush_Ad);
    if(ret != IPF_SUCCESS)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"302 init BSP_IPF_RegisterWakeupDlCb :%d\n",__LINE__);
        return -1;
    }   
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," C core could start dl cases \n");
	
    return 0;

}

/*3031: 5个TTF结点，配61个BD 仅搬移，每个bd有一个链5个ttf*/
int bsp_psam_st_004_init(void)
{
    return bsp_psam_st_003_init();
}

/*3032: 5个TTF结点，配30个BD 过滤搬移，每个bd带有个练5个ttf*/
int bsp_psam_st_005_init(void)
{
    return bsp_psam_st_003_init();
}

/* 5个TTF结点，配60个BD , 只过滤，不做比较 */
int bsp_psam_st_006_init(void)
{    
    int ret = 0;
    ret = psam_st_dl_acore_init();
    if(ret != 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"304 init IPF_ST_DL_INIT :%d\n",__LINE__);
        return -1;
    }
    
    ret = ipf_register_wakeup_dlcb(psam_dl_int_cb_004);
    if(ret != IPF_SUCCESS)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"304 init BSP_IPF_RegisterWakeupDlCb :%d\n",__LINE__);
        return -1;
    }   
    ret = psam_register_adq_empty_dlcb((adq_emtpy_cb_t)psam_st_dl_flush_Ad);
    if(ret != IPF_SUCCESS)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"304 init BSP_IPF_RegisterWakeupDlCb :%d\n",__LINE__);
        return -1;
    }   
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," C core could start dl cases\n");
    
    return 0;
}

int bsp_psam_st_unpacket(void)
{ 
	kfree(g_pu8STDlData);
	return 0;
}

/*下行压力测试A核准备函数*/
int bsp_psam_st_007_init(void)
{
    int ret = 0;
    unsigned int u16Len = 500;
	
    g_pu8STDlData = kmalloc(u16Len,GFP_KERNEL);
    if(g_pu8STDlData == NULL)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"310 init cacheDmaMalloc :%d\n",__LINE__);
        return -1;
    }

	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T *)g_pu8STDlData, u16Len);
	memset(g_pu8STDlData + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), NON_STRAIGHT_P_V, u16Len - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
    
    ret = psam_st_dl_acore_init();
    if(ret != 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"310 init IPF_ST_UL_INIT :%d\n",__LINE__);
        return -1;
    }

    ret = ipf_register_wakeup_dlcb(ipf_dl_test_int_cb);
    if(ret != IPF_SUCCESS)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"310 init BSP_IPF_RegisterWakeupDlCb :%d\n",__LINE__);
        return -1;
    }    
	
    ret = psam_register_adq_empty_dlcb((adq_emtpy_cb_t)psam_st_dl_flush_Ad);
    if(ret != IPF_SUCCESS)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"310 init BSP_IPF_RegisterAdqEmptyDlCb :%d\n",__LINE__);
        return -1;
    }

    ret = bsp_ipf_config_timeout(0x65);//配置超时时间，指什么超时? 相邻rd的间隔
    if(ret != IPF_SUCCESS)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"310 init bsp_ipf_config_timeout :%d\n",__LINE__);
        return -1;
    }

    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"C core could start dl cases\n");

    return 0;   
}

void bsp_psam_st_007_result(void)
{
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," psam_u32DlError(BDs) :%d\n",psam_u32DlError);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," psam_u32DlFltError(BDs) :%d\n",psam_u32DlFltError);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," psam_u32DlTotalDataNum(KB) :%d\n",psam_u32DlTotalDataNum);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," psam_u32DlTotalBDNum(BDs) :%d\n",psam_u32DlTotalBDNum);
}

//对比ad 短包数据正确性
int psam_dl_straight_cb_101(void)
{
	return psam_dl_int_cb_002();
}

//对比ad长包数据正确性
int psam_dl_straight_cb_102(void)
{
	unsigned int i,j;
	unsigned int u32AD0Num;
	unsigned int u32AD1Num;
	unsigned int u32Num = PSAM_DLRD_DESC_SIZE;
	int ret = 0;
	IPF_RD_DESC_S stRd[PSAM_DLRD_DESC_SIZE];
	unsigned int* p = NULL;
	unsigned int* q = NULL;
	
	mdrv_ipf_get_dlrd(&u32Num, stRd);

	PSAM_TEST_ERR("Data transfer Num:%d \n",u32Num);
	
	for(j = 0; j < u32Num; j++)
	{	
		PSAM_TEST_PRINT("phy stRd[%d].u32UsrField3=%llx\n",j,stRd[j].u32UsrField3);
		PSAM_TEST_PRINT("vir stRd[%d].u32OutPtr =%llx\n",j,phys_to_virt(stRd[j].u32OutPtr));
		if(NULL == (unsigned int *)phys_to_virt(stRd[j].u32OutPtr))
		{
			PSAM_TEST_PRINT("stRd[%d].u32OutPtr =NULL !\n",i);
			return -1;
		}

		dma_unmap_single(g_psam_device->dev, (void*)(stRd[j].u32UsrField3), stRd[j].u16PktLen, DMA_FROM_DEVICE);

		if(stRd[j].u16PktLen == 50){
			//short packet 50
			ret = psam_CmpDMAData(g_pu8STDlData, (unsigned char *)phys_to_virt(stRd[j].u32UsrField3), stRd[j].u16PktLen);
			q = (unsigned int *)g_pu8STDlData;
		}
		else{
			//long packet 1500
			ret = psam_CmpDMAData(g_STDlData_long, (unsigned char *)phys_to_virt(stRd[j].u32UsrField3), stRd[j].u16PktLen);
			q = (unsigned int *)g_STDlData_long;
		}
		
		/*数据比对*/
		if(0 != ret)
		{
		    PSAM_TEST_PRINT("\n\r Data transfer unmatch! Num:%d \n",j);
		    PSAM_TEST_PRINT("Comp error \n");
		    PSAM_TEST_PRINT("g_pu8STDlData\n");
		    PSAM_TEST_PRINT("===================================\n");
		    p=q;
		    for(i=0; i<(stRd[j].u16PktLen / 4); i+=4)
		    {
		        PSAM_TEST_PRINT("0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
		    }
		    PSAM_TEST_PRINT("0x%08x    0x%08x\n", *(p+i), *(p+i+1));
		    PSAM_TEST_PRINT("stRd[%d].u32OutPtr\n",j);
                  PSAM_TEST_PRINT("===================================\n");
                  PSAM_TEST_PRINT("stRd[%d].u32OutPtr =%x\n",j,phys_to_virt(stRd[j].u32OutPtr));
		    p=(unsigned int *)phys_to_virt(stRd[j].u32OutPtr);
		    for(i=0; i<(stRd[j].u16PktLen / 4); i+=4)
		    {
		        PSAM_TEST_PRINT("0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
		    }
		    PSAM_TEST_PRINT("0x%08x    0x%08x\n", *(p+i), *(p+i+1));
			psam_dl_confirm = ERROR;
			goto out;
		}	
	}
out:
	
	mdrv_ipf_get_dlad_num(&u32AD0Num, &u32AD1Num);
	if (j == u32Num) {
		PSAM_TEST_PRINT("Data transfer success! Num: %d \n AD0Num:%d AD1Num:%d \n",j,u32AD0Num,u32AD1Num);
	}
	for (j = 0; j < u32Num; j++ ) {
		kfree(phys_to_virt(stRd[j].u32UsrField3));
	}

	return 0;
}

int psam_dl_straight_cb_103(void)
{
	unsigned int u32Num = PSAM_DLRD_DESC_SIZE;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int u32RecivedData = 0;
    int ret = 0;
    unsigned int *p = NULL;
	unsigned int *q = NULL;
    IPF_RD_DESC_S stRd[PSAM_DLRD_DESC_SIZE];
	static unsigned int 	tmp = 0;
	
	/*处理RD*/
    mdrv_ipf_get_dlrd(&u32Num, stRd);
	
	if(u32Num == 64)
		psam_st_Dl_rd_full_times++;
	
    for(j = 0; j < u32Num; j++)
    {	
		//cihper的usrfiled1==0, 用这样来区分直通、非直通的数据包
		if(stRd[j].u32UsrField2 != 0){
			if((stRd[j].u32UsrField2 - tmp) != 1){
				PSAM_TEST_PRINT("cipher cnt error, cur is %d, pre is %d\n",stRd[j].u32UsrField2,tmp);
			}
			tmp = stRd[j].u32UsrField2;
		}
		
		stRd[j].u16UsrField1==200?(psam_st_DlTotalBDNum++):(cipher_st_DlTotalBDNum++);

		dma_unmap_single(g_psam_device->dev, (void*)(stRd[j].u32UsrField3), stRd[j].u16PktLen, DMA_FROM_DEVICE);

		if(0 == stRd[j].u32OutPtr)
		{
	    	PSAM_TEST_PRINT("stRd[%d].u32OutPtr =%x !return error\n",j,stRd[j].u32OutPtr);
			return -1;
		}

		if(stRd[j].u16PktLen == 50){
			//short packet 50
			ret = psam_CmpDMAData(g_pu8STDlData, (unsigned char *)phys_to_virt(stRd[j].u32UsrField3), stRd[j].u16PktLen);
			q = (unsigned int *)g_pu8STDlData;
		}
		else if(stRd[j].u16PktLen == 500){
			//mid packet 500
			ret = psam_CmpDMAData(g_STDlData_mid, (unsigned char *)phys_to_virt(stRd[j].u32UsrField3), stRd[j].u16PktLen);
			q = (unsigned int *)g_STDlData_mid;
		}
		else{
			//long packet 1500
			ret = psam_CmpDMAData(g_STDlData_long, (unsigned char *)phys_to_virt(stRd[j].u32UsrField3), stRd[j].u16PktLen);
			q = (unsigned int *)g_STDlData_long;
		}
		u32RecivedData += stRd[j].u16PktLen;

		/*数据比对*/
		if(0 != ret){
			psam_st_DlError++;
			PSAM_TEST_PRINT("cipher cnt error, cur is %d\n",stRd[j].u32UsrField2);
			PSAM_TEST_PRINT("stRd[%d].u32OutPtr =%x stRd[%d].u16PktLen =%u \n",j,stRd[j].u32OutPtr,j,stRd[j].u16PktLen);
			PSAM_TEST_PRINT("stRd[%d].u32OutPtr =%x stRd[%d].u16UsrField1 =%u \n",j,stRd[j].u32OutPtr,j,stRd[j].u16UsrField1);

			PSAM_TEST_PRINT("g_pu8STDlData,u32Num = %u\n",u32Num);
		    PSAM_TEST_PRINT("===================================\n");
		    p=q;
		    for(i=0; i<10; i+=4)
		    {
		        PSAM_TEST_PRINT("0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
		    }
		    PSAM_TEST_PRINT("0x%08x    0x%08x\n", *(p+i), *(p+i+1));
          	PSAM_TEST_PRINT("Err stRd[%d].u32OutPtr =%x\n",j,stRd[j].u32OutPtr);
          	PSAM_TEST_PRINT("===================================\n");
		    p=(unsigned int *)stRd[j].u32OutPtr;
		    for(i=0; i<10; i+=4)
		    {
		        PSAM_TEST_PRINT("0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
		    }
		    PSAM_TEST_PRINT("0x%08x    0x%08x\n", *(p+i), *(p+i+1));
		}
		if(stRd[j].u16Result == 0x3f){
			psam_st_DlFltError++;
		}
#if 0
		if(stRd[j].u16PktLen <= 438){
			memset((unsigned int *)phys_to_virt(stRd[j].u32UsrField3), 0x00, 438);
			*((unsigned int *)stRd[j].u32UsrField3) = stRd[j].u32UsrField2;
		}
		else{
			memset((unsigned int *)stRd[j].u32UsrField3, 0x00, 1500);
			*((unsigned int *)stRd[j].u32UsrField3) = stRd[j].u32UsrField2;
		}
#endif	
		kfree(phys_to_virt(stRd[j].u32UsrField3));
		psam_kfree_cnt++;
    }
	
	//mdelay(200);
	u32RecivedData = u32RecivedData/1024;
	psam_st_DlTotalDataNum += u32RecivedData;
	
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
//////////////////////////////*直通测试用例*//////////////////////////
/////////////////////////////////////////////////////////////////////////////
int bsp_psam_straight_packet(void)
{
	unsigned int u16Len = 50;
	unsigned int u16Len_L = 1500;
		
	g_pu8STDlData = kmalloc(u16Len,GFP_KERNEL);
	if(g_pu8STDlData == NULL)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"101 init cacheDmaMalloc :%d\n",__LINE__);
		return -1;
	}
	
	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T *)g_pu8STDlData, u16Len);
	memset(g_pu8STDlData + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), PACKET_VALUE, u16Len - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));

		
	g_STDlData_long = kmalloc(u16Len_L,GFP_KERNEL);
	if(g_STDlData_long == NULL)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"102 init cacheDmaMalloc :%d\n",__LINE__);
		return -1;
	}
	
	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T *)g_STDlData_long, u16Len_L);
	memset(g_STDlData_long + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), PACKET_VALUE, u16Len_L - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
	return 0;
}

/*注意cipher测试直通之前需要调用ipf下行初始化函数*/
/*200个50的短数据包，测试数据搬移是否有问题*/
int bsp_psam_straight_101_init(void)
{
    int ret = 0;
	
	ret = psam_st_dl_acore_init();
    if(ret != 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"101 init psam_st_dl_acore_init :%d\n",__LINE__);
        return -1;
    }
    
    ret = ipf_register_wakeup_dlcb(psam_dl_straight_cb_102);
    if(ret != 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"101 init psam BSP_IPF_RegisterWakeupDlCb :%d\n",__LINE__);
        return -1;
    }
	
    ret = psam_register_adq_empty_dlcb((adq_emtpy_cb_t)psam_st_dl_flush_Ad);
    if(ret != 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"101 init bsp_psam_register_Adq_empty_dl_cb :%d\n",__LINE__);
        return -1;
    }   
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"C core cipher could start dl cases\n");

    
    return 0;
}

//receive 200 long ad packets and check correct
int bsp_psam_straight_102_init(void)
{
	int ret = 0;
	
	ret = psam_st_dl_acore_init();
	if(ret != 0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"102 init psam_st_dl_acore_init :%d\n",__LINE__);
		return -1;
	}
	
	ret = ipf_register_wakeup_dlcb(psam_dl_straight_cb_102);
	if(ret != 0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"102 init psam BSP_IPF_RegisterWakeupDlCb :%d\n",__LINE__);
		return -1;
	}
	
	ret = psam_register_adq_empty_dlcb((adq_emtpy_cb_t)psam_st_dl_flush_Ad);
	if(ret != 0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"102 init bsp_psam_register_Adq_empty_dl_cb :%d\n",__LINE__);
		return -1;
	}	
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"C core cipher could start dl cases\n");
	
	return 0;

}

//200 packets,  iv_sel = 0, iv_num = 0
int bsp_psam_straight_103_init(void)
{
	int ret = 0;
	
	ret = psam_st_dl_acore_init();
	if(ret != 0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"103 init psam_st_dl_acore_init :%d\n",__LINE__);
		return -1;
	}
	
	ret = ipf_register_wakeup_dlcb(psam_dl_straight_cb_102);
	if(ret != 0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"103 init psam BSP_IPF_RegisterWakeupDlCb :%d\n",__LINE__);
		return -1;
	}
	
	ret = psam_register_adq_empty_dlcb((adq_emtpy_cb_t)psam_st_dl_flush_Ad);
	if(ret != 0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"103 init bsp_psam_register_Adq_empty_dl_cb :%d\n",__LINE__);
		return -1;
	}	
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"C core cipher could start dl cases\n");

	return 0;
}

int bsp_psam_straight_unpacket(void)
{ 
	kfree(g_pu8STDlData);
	kfree(g_STDlData_long); 
	return 0;
}


//200 packets,  iv_sel = 1, iv_num = 0
int bsp_psam_straight_104_init(void)
{
	return bsp_psam_straight_102_init();
}

//200 packets,  iv_sel = 1, iv_num = 1
int bsp_psam_straight_105_init(void)
{
	return bsp_psam_straight_102_init();
}


/* packets of 50, 500, 1500
** psam_dl_rpt1_switch 1/0  	-enable/disable ipf dl rd wakeup int
** mdrv_cipher_purge_chan 5  	-reset cipher psam direct channel
*/
int bsp_psam_straight_106_init(void)
{
	int ret = 0;
	int u16Len = 50;
	int u16Len_m = 500;
	int u16Len_l = 1500;
	
	g_pu8STDlData = kmalloc(u16Len,GFP_KERNEL);
	if(g_pu8STDlData == NULL)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"110 init cacheDmaMalloc :%d\n",__LINE__);
		return -1;
	}

	g_STDlData_mid = kmalloc(u16Len_m,GFP_KERNEL);
	if(g_STDlData_mid == NULL)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"110 init cacheDmaMalloc :%d\n",__LINE__);
		return -1;
	}

	g_STDlData_long = kmalloc(u16Len_l,GFP_KERNEL);
	if(g_STDlData_long == NULL)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"110 init cacheDmaMalloc :%d\n",__LINE__);
		return -1;
	}
	
	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T *)g_pu8STDlData, u16Len);
	memset(g_pu8STDlData + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), PACKET_VALUE, u16Len - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));

	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T *)g_STDlData_mid, u16Len_m);
	memset(g_STDlData_mid + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), NON_STRAIGHT_P_V, u16Len_m - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
	
	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T *)g_STDlData_long, u16Len_l);
	memset(g_STDlData_long + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), 0x5b, u16Len_l - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));

	ret = psam_st_dl_acore_init();
    if(ret != 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"110 init IPF_ST_UL_INIT :%d\n",__LINE__);
        return -1;
    }

    ret = ipf_register_wakeup_dlcb(psam_dl_straight_cb_103);
    if(ret != IPF_SUCCESS)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"110 init BSP_IPF_RegisterWakeupDlCb :%d\n",__LINE__);
        return -1;
    }    
	
    ret = psam_register_adq_empty_dlcb((adq_emtpy_cb_t)psam_st_dl_flush_Ad);
    if(ret != IPF_SUCCESS)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"110 init BSP_IPF_RegisterAdqEmptyDlCb :%d\n",__LINE__);
        return -1;
    }

    ret = bsp_ipf_config_timeout(0x65);//配置超时时间，指什么超时? 相邻rd的间隔
    if(ret != IPF_SUCCESS)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"110 init bsp_ipf_config_timeout :%d\n",__LINE__);
        return -1;
    }

    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," C core cipher could start dl cases\n");
	return 0;
}

void bsp_psam_straight_106_result(void)
{
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," psam_st_DlError(BDs) :%d\n",psam_st_DlError);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," psam_st_DlFltError(BDs) :%d\n",psam_st_DlFltError);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," psam_st_DlTotalDataNum(KB) :%d\n",psam_st_DlTotalDataNum);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," cipher_st_DlTotalBDNum(BDs) :%d\n",cipher_st_DlTotalBDNum);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," psam_st_DlTotalBDNum(BDs) :%d\n",psam_st_DlTotalBDNum);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," psam_st_Dl_rd_full_times :%d\n",psam_st_Dl_rd_full_times);
	
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," psam_kfree_cnt :%d\n",psam_kfree_cnt);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," psam_kmalloc_long_cnt :%d\n",psam_kmalloc_long_cnt);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," psam_kmalloc_short_cnt :%d\n",psam_kmalloc_short_cnt);
}

int bsp_psam_dl_confirm(void)
{
	int tmp = 0;
	tmp = psam_dl_confirm;
	psam_dl_confirm = 0;
	
	return tmp;
}

#ifdef CONFIG_MODULE_BUSSTRESS
/*ipf dl stress test for auto test*/
int psam_dl_stress_test_stat = 0;
unsigned int psam_dl_test_cnt = 0;
void show_psam_dl_test_cnt(void)
{
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"psam_dl_test_cnt:%d\n",psam_dl_test_cnt);
}
void psam_dl_stress_test_routine(void)
{
	while(psam_dl_stress_test_stat)
	{
		down(&psam_dl_task_sem_id);
		psam_dl_test_cnt++;
	}
}
void set_psam_dl_test_stat(int run_or_stop)
{
	psam_dl_stress_test_stat = run_or_stop;
}
	
int psam_dl_stress_test_init(void)
{
	int ret = 0;
	struct mdrv_ipf_ops wake_empty_cb;
	
	int u16Len = 50;
	int u16Len_m = 500;
	int u16Len_l = 1500;
	
	g_pu8STDlData = kmalloc(u16Len,GFP_KERNEL);
	if(g_pu8STDlData == NULL)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"110 init cacheDmaMalloc :%d\n",__LINE__);
		return -1;
	}

	g_STDlData_mid = kmalloc(u16Len_m,GFP_KERNEL);
	if(g_STDlData_mid == NULL)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"110 init cacheDmaMalloc :%d\n",__LINE__);
		return -1;
	}

	g_STDlData_long = kmalloc(u16Len_l,GFP_KERNEL);
	if(g_STDlData_long == NULL)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"110 init cacheDmaMalloc :%d\n",__LINE__);
		return -1;
	}
	
	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T *)g_pu8STDlData, u16Len);
	memset(g_pu8STDlData + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), PACKET_VALUE, u16Len - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));

	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T *)g_STDlData_mid, u16Len_m);
	memset(g_STDlData_mid + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), NON_STRAIGHT_P_V, u16Len_m - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
	
	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T *)g_STDlData_long, u16Len_l);
	memset(g_STDlData_long + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), 0x5b, u16Len_l - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
	
	ret = psam_st_dl_acore_init();
	if(ret != OK)
	{
	    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
	    return ERROR;
	}
	ret = psam_st_dl_init_stress();
	if(ret != OK)
	{
	    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM," TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
	    return ERROR;
	}

	wake_empty_cb.rx_complete_cb = psam_dl_int_cb;
	wake_empty_cb.adq_empty_cb = psam_st_dl_stress_flush_Ad;
	mdrv_ipf_register_ops(&wake_empty_cb);
	
	psam_dl_test_cnt = 0;
	set_psam_dl_test_stat(1);
	kthread_run((psam_thread_fn)psam_dl_stress_test_routine, NULL, "psam_dl_stest_task");

	return OK;
}

int psam_dl_stress_test_start(void)
{
	return psam_dl_stress_test_init();
}

void psam_dl_stress_test_stop(void)
{
	set_psam_dl_test_stat(0);
	msleep(2000);
}
#endif

#ifdef __cplusplus
}
#endif

