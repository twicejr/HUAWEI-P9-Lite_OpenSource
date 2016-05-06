#ifdef __cplusplus
extern "C" {
#endif

#include <bsp_busstress.h>
#include "ipf_balong_test.h"

struct tagIPF_AD_DESC_S ad_dl_short[IPF_DLAD0_DESC_SIZE];
struct tagIPF_AD_DESC_S ad_dl_long[IPF_DLAD1_DESC_SIZE];
unsigned char* ul_long_data;
unsigned char* ul_short_data;
unsigned int ul_packet_flag;

/*ipf ul stress test*/
IPF_CONFIG_ULPARAM_S g_stUlPara[IPF_ULBD_DESC_SIZE];
unsigned int g_u32Num = 0;

int ipf_ul_stress_test_stat = 0;
int ipf_ul_stress_succeed = 0;
int ipf_ul_stress_failed = 0;

/*ipf dl stress test for auto test*/
int ipf_dl_stress_test_stat = 0;
unsigned int ipf_dl_test_cnt = 0;
unsigned int dl_total_bd_num = 0;

struct semaphore g_IpfDlTaskSemId;
struct semaphore g_IpfDlIntSemId;
osl_sem_id ipf_stress_ul;
struct task_struct *ipf_dl_taskid;

unsigned int ipf_ul_ip_pkt(void)
{
	unsigned int long_len;
	unsigned int short_len;
	StreamIPv4Header stIPHeader;
	StreamUDP stUDP;
	long_len = LONG_DATA;
	short_len = SHORT_DATA;
	ul_short_data = (unsigned char*)kmalloc(short_len,GFP_KERNEL);
    if(ul_short_data == NULL)
    {
        IPF_PRINT("malloc failed :%d\n",__LINE__);
        return ERROR;
    }
	ul_long_data = (unsigned char*)kmalloc(long_len,GFP_KERNEL);
    if(ul_long_data == NULL)
    {
        IPF_PRINT("malloc failed :%d\n",__LINE__);
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
	memset(ul_short_data, T_UL_VALUE, short_len);
    memcpy(ul_short_data, &stIPHeader, sizeof(StreamIPv4Header));
    memcpy(ul_short_data + sizeof(StreamIPv4Header), &stUDP, sizeof(StreamUDP));	
	stIPHeader.TOL = long_len;
	stUDP.Length = stIPHeader.TOL - sizeof(StreamIPv4Header);
	stIPHeader.Checksum = 0x3EDC;
	memset(ul_long_data, T_UL_VALUE, long_len);
    memcpy(ul_long_data, &stIPHeader, sizeof(StreamIPv4Header));
    memcpy(ul_long_data + sizeof(StreamIPv4Header), &stUDP, sizeof(StreamUDP));
	return IPF_SUCCESS;
}

int ipf_dl_st_acore_init(void)
{
	int s32Ret;
	unsigned int i;
	void * p_vir_addr;

	for(i=0; i < IPF_DLAD0_DESC_SIZE; i++)
	{    	
		p_vir_addr = kmalloc(438, GFP_KERNEL); 
		if(p_vir_addr == NULL)
		{
			IPF_PRINT(" malloc failed:%d\n",__LINE__);
			goto error1;
		}
		
		memset(p_vir_addr,0x0,438);
		ad_dl_short[i].u32OutPtr0 = (unsigned int)dma_map_single(g_ipf_ctx.dev, p_vir_addr, 438, DMA_FROM_DEVICE);
		ad_dl_short[i].u32OutPtr1 = ad_dl_short[i].u32OutPtr0;
	}
	
	for(i=0; i < IPF_DLAD1_DESC_SIZE; i++)
	{
		p_vir_addr = kmalloc(1500, GFP_KERNEL);  
		if(p_vir_addr == NULL)
		{
			IPF_PRINT(" malloc failed:%d\n",__LINE__);
			goto error1;
		}
		
		memset(p_vir_addr,0x0,1500);
		ad_dl_long[i].u32OutPtr0 = (unsigned int)dma_map_single(g_ipf_ctx.dev, p_vir_addr ,1500,DMA_FROM_DEVICE);        
    	ad_dl_long[i].u32OutPtr1 = ad_dl_long[i].u32OutPtr0;   
	}
	
	s32Ret = mdrv_ipf_config_dlad(IPF_AD_0,IPF_DLAD0_DESC_SIZE-2,&ad_dl_short[0]);
	if(s32Ret != IPF_SUCCESS)
	{
		IPF_PRINT("mdrv_ipf_config_dlad :%d s32Ret = %x\n",__LINE__, s32Ret);
		return IPF_ERROR;
	}    
	s32Ret = mdrv_ipf_config_dlad(IPF_AD_1,IPF_DLAD1_DESC_SIZE-2,&ad_dl_long[0]);
	if(s32Ret != IPF_SUCCESS)
	{
		IPF_PRINT("mdrv_ipf_config_dlad :%d s32Ret = %x\n",__LINE__, s32Ret);
		return IPF_ERROR;
	}
    return OK;

error1:
	do
	{
		i--;
		kfree(phys_to_virt(ad_dl_short[i].u32OutPtr0));
	}while(i);
	return ERROR;

	do
	{
		i--;
		kfree(phys_to_virt(ad_dl_long[i].u32OutPtr0));
	}while(i);
	for(i=0; i < IPF_DLAD0_DESC_SIZE; i++)
	{
		kfree(phys_to_virt(ad_dl_short[i].u32OutPtr0));
	}
	return ERROR;
}

int ipf_dl_st_flush_ad(IPF_ADQ_EMPTY_E eAdqEmptyDl)
{
	int s32Ret;  

	if(IPF_EMPTY_ADQ0 == eAdqEmptyDl)
	{
		s32Ret = mdrv_ipf_config_dlad(IPF_AD_0,IPF_DLAD0_DESC_SIZE-4,&ad_dl_short[0]);
		if(s32Ret != IPF_SUCCESS)
		{
			IPF_PRINT("IPF_ST_UL_FlashAD :%d s32ret = %x\n",__LINE__, s32Ret);
			return ERROR;
		}
	}
	else if(IPF_EMPTY_ADQ1 == eAdqEmptyDl)
	{
		s32Ret = mdrv_ipf_config_dlad(IPF_AD_1,IPF_DLAD1_DESC_SIZE-4,&ad_dl_long[0]);
		if(s32Ret != IPF_SUCCESS)
		{
			IPF_PRINT("IPF_ST_UL_FlashAD :%d s32ret = %x\n",__LINE__, s32Ret);
			return ERROR;
		}
	}
	else
	{
		return ERROR;
	}
	return OK;
}

void ipf_ul_stress_bd_empty_handle(void)
{
	osl_sem_up(&ipf_stress_ul);
}

int ipf_ul_stress_test_routine(void)
{
    int s32Ret = 0;
    unsigned int i = 0;
    unsigned char* pBuff = NULL;
    unsigned int u32StressSendNum = 60;
    IPF_PRINT("ipf_ul_stress_test_routine running\n");
				        
	pBuff = (unsigned char *)dma_map_single(g_ipf_ctx.dev, 
						(void *)ul_long_data, LONG_DATA, DMA_TO_DEVICE); 
	g_stUlPara[0].u32Data = (unsigned int)pBuff;
	g_stUlPara[0].u16Len = LONG_DATA;
	g_stUlPara[0].u16Attribute = 0x28;
	
    for(i = 1; i < IPF_ULBD_DESC_SIZE; i++)
    {
        memcpy(&g_stUlPara[i], &g_stUlPara[0], sizeof(IPF_CONFIG_ULPARAM_S));
        g_stUlPara[i].u16UsrField1 = i;
    }
    g_stUlPara[u32StressSendNum-1].u16Attribute= 0x29;
	
    while(ipf_ul_stress_test_stat)
    {
	    g_u32Num = mdrv_ipf_get_ulbd_num();
		osl_sem_down(&ipf_stress_ul);

	    s32Ret = mdrv_ipf_config_ulbd(u32StressSendNum, g_stUlPara);
	    if(s32Ret != IPF_SUCCESS) {
			ipf_ul_stress_failed++;
	        return ERROR;
	    }
		ipf_ul_stress_succeed++;
    }
    return OK;    
}

void ipf_ul_test_stat_set(int run_or_stop)
{
	ipf_ul_stress_test_stat = run_or_stop;
}

int ipf_ul_stress_test_start(int interval)
{
	int s32Ret;
	int int_mask;
	
	ipf_register_ul_bd_empty(ipf_ul_stress_bd_empty_handle);	
	ipf_ul_test_stat_set(1);
	int_mask = ipf_readl(g_ipf_ctx.regs + HI_IPF_INT_MASK1_OFFSET);
	ipf_writel(int_mask | BIT(9), g_ipf_ctx.regs + HI_IPF_INT_MASK1_OFFSET);
	if(!ul_packet_flag){
		s32Ret = ipf_ul_ip_pkt();
		if(s32Ret != OK){
			IPF_PRINT("ipf get packet failed!\n");
	        return ERROR;						
		}
		ul_packet_flag = 1;
	}
	osl_sem_init(SEM_FULL, &ipf_stress_ul);
	kthread_run((IPFTHREADFN)ipf_ul_stress_test_routine,NULL,"ipf_ul_stress_task");
	IPF_PRINT("test start !\n");
}

void ipf_ul_stress_test_stop(void)
{
	ipf_ul_test_stat_set(0);
	msleep(2000);
}
void ipf_ul_stress_debug(void)
{
	IPF_PRINT("UL stress test succeed:  %d\n", ipf_ul_stress_succeed);
	IPF_PRINT("UL stress test failed:   %d\n", ipf_ul_stress_failed);
	IPF_PRINT("UL stress test bd empty: %d\n", g_ipf_ctx.status->bd_epty_intr);
}

int ipf_dl_int_cb(void)
{
    up(&g_IpfDlIntSemId);
    return OK;
}

void ipf_dl_task_1(void)
{
    unsigned int u32Num = 0;
    IPF_RD_DESC_S stRd[IPF_ULRD_DESC_SIZE];
    unsigned int i = 0;
    unsigned int u32AD0Num,u32AD1Num,u32AD0wptr,u32AD1wptr;
    int s32Ret = 0;
    while(1)
    { 
        memset(stRd, 0x0, sizeof(IPF_RD_DESC_S) * IPF_ULRD_DESC_SIZE);
        u32Num = IPF_ULRD_DESC_SIZE;
        down(&g_IpfDlIntSemId);

        mdrv_ipf_get_dlrd(&u32Num, stRd);
        dl_total_bd_num += u32Num;
		
		s32Ret = mdrv_ipf_get_dlad_num(&u32AD0Num, &u32AD1Num);
        if(s32Ret)
		{
      		IPF_PRINT("Get dl ad num fail :%d\n",__LINE__);
        }

        if(u32AD0Num > 10)
	    {
			u32AD0wptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_ADQ0_WPTR_OFFSET );
	        if((IPF_ULAD0_DESC_SIZE -u32AD0wptr) >= u32AD0Num) {
	            s32Ret = mdrv_ipf_config_dlad(IPF_AD_0,u32AD0Num,&ad_dl_short[u32AD0wptr]);
	            if(s32Ret) {
					IPF_PRINT("BSP_IPF_ConfigUlAd0 :%d\n",__LINE__);
	            }
	        }
        	else {
	            s32Ret = mdrv_ipf_config_dlad(IPF_AD_0,(IPF_ULAD0_DESC_SIZE-u32AD0wptr),&ad_dl_short[u32AD0wptr]);
	            if(s32Ret){
					IPF_PRINT("BSP_IPF_ConfigUlAd0 :%d\n",__LINE__);
	            }
	            s32Ret = mdrv_ipf_config_dlad(IPF_AD_0,(u32AD0Num-(IPF_ULAD0_DESC_SIZE-u32AD0wptr)),&ad_dl_short[0]);
	            if(s32Ret){
					IPF_PRINT("BSP_IPF_ConfigUlAd0 :%d\n",__LINE__);
	            }
	        }
	        for(i=0;i < u32AD0Num;i++){
	            memset(phys_to_virt(ad_dl_short[u32AD0wptr].u32OutPtr1), 1, 438);
				u32AD0wptr = ((u32AD0wptr + 1) < IPF_DLAD0_DESC_SIZE)? (u32AD0wptr + 1) : 0;		
	        }
    	}
    	if(u32AD1Num > 10){
			u32AD1wptr = ipf_readl(g_ipf_ctx.regs + HI_IPF_CH0_ADQ1_WPTR_OFFSET );
			if((IPF_ULAD1_DESC_SIZE - u32AD1wptr) >= u32AD1Num){
	        	s32Ret = mdrv_ipf_config_dlad(IPF_AD_1,u32AD1Num,&ad_dl_long[u32AD1wptr]);
		        if(s32Ret){
					IPF_PRINT("BSP_IPF_ConfigUlAd1 :%d\n",__LINE__);
					IPF_PRINT("u32AD1Num = %u   u32AD1wptr = %u \n",u32AD1Num,u32AD1wptr);
				    return;
		      	 }
			} else {
	        	s32Ret = mdrv_ipf_config_dlad(IPF_AD_1,(IPF_ULAD1_DESC_SIZE-u32AD1wptr),&ad_dl_long[u32AD1wptr]);
		        if(s32Ret){
					IPF_PRINT("BSP_IPF_ConfigUlAd1 :%d\n",__LINE__);
				    return;
				}
	        	s32Ret = mdrv_ipf_config_dlad(IPF_AD_1,(u32AD1Num-(IPF_ULAD1_DESC_SIZE-u32AD1wptr)),&ad_dl_long[0]);
				if(s32Ret){
					IPF_PRINT("BSP_IPF_ConfigUlAd1 :%d\n",__LINE__);
				    return;
				}
			}
	        for(i=0;i < u32AD1Num;i++){
	            memset(phys_to_virt(ad_dl_long[u32AD1wptr].u32OutPtr1), 2, 1500);
				u32AD1wptr = ((u32AD1wptr + 1) < IPF_DLAD0_DESC_SIZE)? (u32AD1wptr + 1) : 0;		
	        }
	    }
        up(&g_IpfDlTaskSemId);
    }
}

int ipf_dl_st_init_stress(void)
{
    sema_init(&g_IpfDlTaskSemId, 0);
    sema_init(&g_IpfDlIntSemId, 0);

    ipf_dl_taskid = kthread_run((IPFTHREADFN)ipf_dl_task_1, NULL, "ipf_dl_task");  

    return OK;
}

void ipf_dl_test_cnt_show(void)
{
	printk("ipf_dl_test_cnt:%d\n",ipf_dl_test_cnt);
	printk("dl_total_bd_num:%d\n",dl_total_bd_num);
}

void ipf_dl_stress_test_routine(void)
{
	while(ipf_dl_stress_test_stat)
	{
		down(&g_IpfDlTaskSemId);
		ipf_dl_test_cnt++;
	}
}

void ipf_dl_test_stat_set(int run_or_stop)
{
	ipf_dl_stress_test_stat = run_or_stop;
}
	
int ipf_dl_stress_test_init(void)
{
	int s32Ret = 0;
	struct mdrv_ipf_ops wake_empty_cb;

	s32Ret = ipf_dl_st_acore_init();
	if(s32Ret != OK)
	{
	    IPF_PRINT("ipf_dl_st_acore_init :%d\n",__LINE__);
	    return ERROR;
	}
	s32Ret = ipf_dl_st_init_stress();
	if(s32Ret != OK)
	{
	    IPF_PRINT("IPF_ST_DL_INIT :%d\n",__LINE__);
	    return ERROR;
	}

	wake_empty_cb.rx_complete_cb = ipf_dl_int_cb;
	wake_empty_cb.adq_empty_cb = ipf_dl_st_flush_ad;
	mdrv_ipf_register_ops(&wake_empty_cb);
	ipf_dl_test_cnt = 0;
	
	ipf_dl_test_stat_set(1);
	kthread_run((IPFTHREADFN)ipf_dl_stress_test_routine,NULL,"ipf_dl_stress_task");
	return OK;
}

int ipf_dl_stress_test_start(void)
{
	return ipf_dl_stress_test_init();
}

void ipf_dl_stress_test_stop(void)
{
	ipf_dl_test_stat_set(0);
	msleep(2000);
}

EXPORT_SYMBOL(ipf_ul_stress_test_start);
EXPORT_SYMBOL(ipf_dl_stress_test_start);
EXPORT_SYMBOL(ipf_dl_stress_test_init);

#ifdef __cplusplus
}
#endif

