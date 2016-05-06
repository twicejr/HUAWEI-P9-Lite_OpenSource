#ifdef __cplusplus
extern "C" {
#endif

#include <bsp_busstress.h>
#include <ipf_balong_test.h>

#define BDNUM   IPF_DLBD_DESC_SIZE

struct tagIPF_AD_DESC_S ad_ul_short[IPF_ULAD0_DESC_SIZE];
struct tagIPF_AD_DESC_S ad_ul_long[IPF_ULAD1_DESC_SIZE];

unsigned int ipf_ul_stress_test_cnt = 0;
unsigned int ipf_ul_stress_test_task_id = 0;
unsigned int ipf_ul_stress_test_switch = 0;
unsigned int g_ipf_busstress_test_ok_cnt = 0;
unsigned int g_ipf_busstress_test_fail_cnt = 0;

unsigned int ipf_dl_stress_test_cnt = 0;
unsigned int ipf_dl_stress_test_task_id = 0;
unsigned int ipf_dl_stress_test_switch = 0;

OSAL_SEM_ID g_IpfUlTaskSemId;
OSAL_SEM_ID g_IpfUlIntSemId;

unsigned int ipf_ul_taskid = 0;
unsigned int ul_total_bd_num= 0;

int ipf_task_delay_ticks = 0;

int ipf_st_init(void)
{
    IPF_COMMON_PARA_S stCommPara;
    int s32Ret = 0;

    /*初始化时IP过滤的参数配置*/
    stCommPara.bEspSpiDisable = 1;      /* ESP SPI是否参与匹配控制信号 */
    stCommPara.bAhSpiDisable = 1;       /* AH SPI是否参与匹配控制信号 */
    stCommPara.bEspAhSel= 0;           /* 0选ESP，1选AH */
    stCommPara.bIpv6NextHdSel = 0;
    stCommPara.eMaxBurst = IPF_BURST_16;       /* BURST最大长度 */
    stCommPara.bSpWrrModeSel = 0;
    stCommPara.bSpPriSel = 0;          /* SP优先级选择 */
    stCommPara.bFltAddrReverse = 1;        /* 配置为0,地址为大端 */
    stCommPara.bFilterSeq = 0;         /* 过滤器配置顺序指示 */
    stCommPara.bAdReport = 0; /*上报AD第二个字指针*/
#ifdef IPF_NO_FILTER_TEST
    stCommPara.bMultiFilterChainEn = 0;/*单寄存器链模式*/
    stCommPara.bMultiModeEn = 0;/*静态业务模式*/
#endif
    stCommPara.bMultiFilterChainEn = 1;/*多寄存器链模式*/
    stCommPara.bMultiModeEn = 1;/*动态业务模式*/
	
    s32Ret = mdrv_ipf_init(&stCommPara) ;
    if (s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("mdrv_ipf_init failed :%d   s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }
    
    return OK;
}


int ipf_ul_st_flush_ad(IPF_ADQ_EMPTY_E eAdqEmptyUl)
{
	int s32Ret;  
	
	if(IPF_EMPTY_ADQ0 == eAdqEmptyUl)
	{
		s32Ret = mdrv_ipf_config_ulad(IPF_AD_0,IPF_ULAD0_DESC_SIZE - 4,&ad_ul_short[0]);
		if(s32Ret != IPF_SUCCESS)
		{
			IPF_PRINT("TEST ERROR BSP_IPF_ConfigDlAd :%d s32ret = %x\n",__LINE__, s32Ret);
			return s32Ret;
		}
	}
	else if(IPF_EMPTY_ADQ1 == eAdqEmptyUl)
	{
		s32Ret = mdrv_ipf_config_ulad(IPF_AD_1,IPF_ULAD1_DESC_SIZE - 4,&ad_ul_long[0]);

		if(s32Ret != IPF_SUCCESS)
		{
			IPF_PRINT("TEST ERROR mdrv_ipf_config_ulad:%d s32ret = %x\n",__LINE__, s32Ret);
			return s32Ret;
		}
	}
	else
	{
		return ERROR;
	}
	return OK;
}

int ipf_ul_st_init(void)
{	
    IPF_CHL_CTRL_S stCtrl;
    IPF_FILTER_CONFIG_S stUlFilterInfo[50];
    int s32Ret = 0;
    unsigned int i = 0;

	for(i=0; i < IPF_ULAD0_DESC_SIZE; i++)
	{
		ad_ul_short[i].u32OutPtr0 = (unsigned int)osl_cachedma_malloc(404);
		ad_ul_short[i].u32OutPtr1 = ad_ul_short[i].u32OutPtr0;
		if((unsigned int)NULL == ad_ul_short[i].u32OutPtr0)
		{
			IPF_PRINT("osl_cachedma_malloc failed :%d\n",__LINE__);
			return ERROR;
		}
	}
	for(i=0; i < IPF_ULAD1_DESC_SIZE; i++)
	{
		ad_ul_long[i].u32OutPtr0 = (unsigned int)osl_cachedma_malloc(1500);
		ad_ul_long[i].u32OutPtr1 = ad_ul_long[i].u32OutPtr0;
		if((unsigned int)NULL == ad_ul_long[i].u32OutPtr0)
		{
			IPF_PRINT("osl_cachedma_malloc failed :%d\n",__LINE__);
			goto error1;
		}
	}
	
    s32Ret = mdrv_ipf_config_ulad(IPF_AD_0,IPF_ULAD0_DESC_SIZE - 4,&ad_ul_short[0]);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("mdrv_ipf_config_ulad failed :%d s32Ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }    

    s32Ret = mdrv_ipf_config_ulad(IPF_AD_1,IPF_ULAD1_DESC_SIZE - 4,&ad_ul_long[0]);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("mdrv_ipf_config_ulad failed :%d s32Ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }    

    memset_s(stUlFilterInfo, 50*sizeof(IPF_FILTER_CONFIG_S), 0x0, 50*sizeof(IPF_FILTER_CONFIG_S));

    for(i=0;i<24;i++)
    {
        stUlFilterInfo[i].u32FilterID = i;
        stUlFilterInfo[i].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = 0xffffffff;
    }
    
    stUlFilterInfo[24].u32FilterID = 172;
    stUlFilterInfo[24].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = 0x23C01;
    *(unsigned int*)(stUlFilterInfo[24].stMatchInfo.u8SrcAddr) = 0xACA84649;
    *(unsigned int*)(stUlFilterInfo[24].stMatchInfo.u8DstAddr) = 0x0202014E;
    *(unsigned int*)(stUlFilterInfo[24].stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
    stUlFilterInfo[24].stMatchInfo.unSrcPort.Bits.u16SrcPortLo = 1;
    stUlFilterInfo[24].stMatchInfo.unSrcPort.Bits.u16SrcPortHi = 5100;
    stUlFilterInfo[24].stMatchInfo.unDstPort.Bits.u16DstPortLo = 10;
    stUlFilterInfo[24].stMatchInfo.unDstPort.Bits.u16DstPortHi = 5100;
    stUlFilterInfo[24].stMatchInfo.unTrafficClass.u32TrafficClass  = 3|(0xFF<<8);
    stUlFilterInfo[24].stMatchInfo.u32LocalAddressMsk = 0x00;
    stUlFilterInfo[24].stMatchInfo.unNextHeader.u32Protocol = 1;
    stUlFilterInfo[24].stMatchInfo.unFltCodeType.Bits.u16Type = 2;
    stUlFilterInfo[24].stMatchInfo.unFltCodeType.Bits.u16Code = 3;
    stUlFilterInfo[24].stMatchInfo.u32FltSpi = 4;

    s32Ret = ipf_st_init();
    if(s32Ret != OK)
    {
        IPF_PRINT("ipf_st_init failed :%d\n",__LINE__);
        return s32Ret;
    }

    stCtrl.bDataChain = 0;
    stCtrl.bEndian = 1; /* 小端 */
    stCtrl.eIpfMode = IPF_MODE_FILTERANDTRANS;
    stCtrl.u32WrrValue = 0;
    s32Ret = mdrv_ipf_config_ulchan(&stCtrl);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("mdrv_ipf_config_ulchan failed :%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }

    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_ULFC, stUlFilterInfo, 25);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("mdrv_ipf_set_filter failed :%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }
	
    s32Ret = mdrv_ipf_set_filter(IPF_MODEM1_ULFC, stUlFilterInfo, 25);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("mdrv_ipf_set_filter failed :%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }

    s32Ret = mdrv_ipf_enable_chan(IPF_CHANNEL_UP, 1);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("mdrv_ipf_enable_chan failed :%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }
	
    return OK;
	
error1:
	IPF_PRINT("ipf_ul_st_init error!");
	do
	{
		i--;
		osl_cachedma_free((void *)ad_ul_short[i].u32OutPtr0);
	}while(i);
	
	return s32Ret;
}

int ipf_ul_int_cb()
{
    OSAL_SemGive(g_IpfUlIntSemId);
    return OK;
}

void ipf_ul_task_1(void)
{
    unsigned int u32Num = 0;
    IPF_RD_DESC_S stRd[IPF_ULRD_DESC_SIZE];
    unsigned int i = 0;
    unsigned int u32AD0Num,u32AD1Num;
    int s32Ret;
    while(1)
    { 
        memset_s(stRd, sizeof(IPF_RD_DESC_S) * IPF_ULRD_DESC_SIZE, 0x0, sizeof(IPF_RD_DESC_S) * IPF_ULRD_DESC_SIZE);
        u32Num = IPF_ULRD_DESC_SIZE;
        osl_sem_down(&g_IpfUlIntSemId);

        mdrv_ipf_get_ulrd(&u32Num, stRd);

        ul_total_bd_num += u32Num;

	    s32Ret = mdrv_ipf_get_ulad_num(&u32AD0Num,&u32AD1Num);
	    if(IPF_SUCCESS != s32Ret)
	    {
	        IPF_PRINT("mdrv_ipf_get_ulad_num :%d\n",__LINE__);
	        return;
	    }
	    if(u32AD0Num > 10)
	    {
	        s32Ret = mdrv_ipf_config_ulad(IPF_AD_0,u32AD0Num,&ad_ul_short[0]);
	        if(IPF_SUCCESS != s32Ret)
	        {
	            IPF_PRINT("mdrv_ipf_config_ulad0 :%d\n",__LINE__);
	        }
	        for(i=0;i < u32AD0Num;i++)
	        {
	            memset_s((unsigned int*)ad_ul_short[i].u32OutPtr1, 404, 0, 404);
	        }
	    }
	    if(u32AD1Num > 10)
	    {
	        s32Ret = mdrv_ipf_config_ulad(IPF_AD_1,u32AD1Num,&ad_ul_long[0]);
	        if(IPF_SUCCESS != s32Ret)
	        {
	            IPF_PRINT("mdrv_ipf_config_ulad1 :%d\n",__LINE__);
	        }
	        for(i=0;i < u32AD1Num;i++)
	        {
	            memset_s((unsigned int*)ad_ul_long[i].u32OutPtr1, 1500, 0, 1500);
	        }

	    }
        osl_sem_up(&g_IpfUlTaskSemId);
    }
}

int ipf_ul_st_init_stress(void)
{
	osl_sem_init(0,&g_IpfUlIntSemId);
    if(!g_IpfUlIntSemId)
    {
        IPF_PRINT("osl_sem_init :%d\n",__LINE__);
        return ERROR;
    }

	osl_sem_init(0,&g_IpfUlTaskSemId);
    if(!g_IpfUlTaskSemId)
    {
        IPF_PRINT("osl_sem_init :%d\n",__LINE__);
        return ERROR;
    }
	osl_task_init("IpfUlTask1", 32, 20000, (OSL_TASK_FUNC)ipf_ul_task_1, 0, &ipf_ul_taskid);
    return OK;
}

/*ipf ul stress test for auto test*/
int ipf_ul_stress_test_routine()
{
	/*while(get_test_switch_stat(IPF_UL))*/
	while(ipf_ul_stress_test_switch)
	{
	    osl_sem_down(&g_IpfUlTaskSemId);
	    ipf_ul_stress_test_cnt++;
	}
	return OK;
}

int ipf_ul_stress_test_init(int task_priority)
{
	int s32Ret = 0;

	/*set_test_switch_stat(IPF_UL,TEST_RUN);*/
	ipf_ul_stress_test_switch = 1;

	s32Ret = ipf_ul_st_init();
	if(s32Ret != OK)
	{
	    IPF_PRINT("ipf_ul_st_init :%d\n",__LINE__);
	    return ERROR;
	}
	
	s32Ret = ipf_ul_st_init_stress();
	if(s32Ret != OK)
	{
	    IPF_PRINT("ipf_ul_st_init_stress :%d\n",__LINE__);
	    return ERROR;
	}
	
	s32Ret = ipf_register_wakeup_ulcb(ipf_ul_int_cb);
	if(s32Ret != IPF_SUCCESS)
	{
	    IPF_PRINT("ipf_register_wakeup_ulcb :%d\n",__LINE__);
	    return ERROR;
	}
	s32Ret = ipf_register_adq_empty_ulcb(ipf_ul_st_flush_ad);
	if(s32Ret != IPF_SUCCESS)
	{
	    IPF_PRINT("ipf_register_adq_empty_ulcb :%d\n",__LINE__);
	    return ERROR;
	}

	ipf_ul_stress_test_cnt = 0;

	osl_task_init("ipf ul stress task", task_priority, 0x2000, (OSL_TASK_FUNC)ipf_ul_stress_test_routine, 0,&ipf_ul_stress_test_task_id);
	if(ipf_ul_stress_test_task_id == IPF_ERROR)
	{
		IPF_PRINT("taskSpawn ipfUlTask fail.\n");
		return ERROR;
	}

	IPF_PRINT("ipf upload stress test start successfully!\n");
	
	return OK;
}

int ipf_ul_stress_test_start(int task_priority)
{
	return ipf_ul_stress_test_init(task_priority);
}

void ipf_ul_stress_test_result(void)
{
	IPF_PRINT(" ul_total_bd_num(BDs) :%d\n",ul_total_bd_num);
}

void ipf_ul_stress_test_stop()
{
    /*set_test_switch_stat(IPF_UL,TEST_STOP);*/
	ipf_ul_stress_test_switch = 0;
    while(BSP_OK == osl_task_check(ipf_ul_stress_test_task_id))
    {
        osl_task_delay(100);
    }  
    osl_sem_delete((struct semaphore *)&g_IpfUlIntSemId);
    osl_sem_delete((struct semaphore *)&g_IpfUlTaskSemId);
    osl_task_delete(&ipf_ul_taskid);
}

/*ipf dl stress test*/
int ipf_dl_st_init(void)
{
    IPF_CHL_CTRL_S stCtrl;
    IPF_FILTER_CONFIG_S stDlFilterInfo[50];
    int s32Ret = 0;
    unsigned int i = 0;
	
    memset_s(stDlFilterInfo, 50*sizeof(IPF_FILTER_CONFIG_S), 0x0, 50*sizeof(IPF_FILTER_CONFIG_S));
    for(i=0;i<49;i++)
    {
        stDlFilterInfo[i].u32FilterID = i;
        stDlFilterInfo[i].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = 0xffffffff;
    }
    
    stDlFilterInfo[49].u32FilterID = 172;
    stDlFilterInfo[49].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = 0x23C01;
    *(unsigned int*)(stDlFilterInfo[49].stMatchInfo.u8SrcAddr) = 0xACA84649;
    *(unsigned int*)(stDlFilterInfo[49].stMatchInfo.u8DstAddr) = 0x0202014E;
    *(unsigned int*)(stDlFilterInfo[49].stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
    stDlFilterInfo[49].stMatchInfo.unSrcPort.Bits.u16SrcPortLo = 1;
    stDlFilterInfo[49].stMatchInfo.unSrcPort.Bits.u16SrcPortHi = 5100;
    stDlFilterInfo[49].stMatchInfo.unDstPort.Bits.u16DstPortLo = 10;
    stDlFilterInfo[49].stMatchInfo.unDstPort.Bits.u16DstPortHi = 5100;
    stDlFilterInfo[49].stMatchInfo.unTrafficClass.u32TrafficClass  = 3|(0xFF<<8);
    stDlFilterInfo[49].stMatchInfo.u32LocalAddressMsk = 0x00;
    stDlFilterInfo[49].stMatchInfo.unNextHeader.u32Protocol = 1;
    stDlFilterInfo[49].stMatchInfo.unFltCodeType.Bits.u16Type = 2;
    stDlFilterInfo[49].stMatchInfo.unFltCodeType.Bits.u16Code = 3;
    stDlFilterInfo[49].stMatchInfo.u32FltSpi = 4;

    s32Ret = ipf_st_init();
    if(s32Ret != OK)
    {
        IPF_PRINT("ipf_st_init return failed :%d\n",__LINE__);
        return s32Ret;
    }

    stCtrl.bDataChain = 1;
    stCtrl.bEndian = 1; /* 小端 */
    stCtrl.eIpfMode = IPF_MODE_FILTERONLY;
    stCtrl.u32WrrValue = 0;
    s32Ret = mdrv_ipf_config_dlchan(&stCtrl);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("mdrv_ipf_config_dlchan return failed  :%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }

    s32Ret = mdrv_ipf_set_filter(IPF_MODEM0_DLFC, stDlFilterInfo, 50);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("mdrv_ipf_set_filter return failed :%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }

    s32Ret = mdrv_ipf_enable_chan(IPF_CHANNEL_DOWN, 1);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("mdrv_ipf_enable_chan return failed  :%d s32ret = %x\n",__LINE__, s32Ret);
        return s32Ret;
    }

    return OK;
}


int ipf_dl_stress_test_routine(void *para)
{
    IPF_CONFIG_DLPARAM_S stDlPara[IPF_DLBD_DESC_SIZE];
    int s32Ret = 0;
    StreamIPv4Header stIPHeader;
    StreamUDP stUDP;
    unsigned int i = 0;
    unsigned char* pu8IPData;
    unsigned char* pu8IPData1;
    unsigned char* pu8IPData2;
    unsigned char* pu8IPData3;
    unsigned char* pu8IPData4;
    unsigned int u32Len = 200;
    TTF_MEM_ST stSrcTtf[5];
    unsigned int u32CDNum = 0;
    unsigned int u32BDNum = 0;
	int dtime = *((int *)para);
	
    pu8IPData = (unsigned char*)osl_cachedma_malloc(u32Len);
    if(pu8IPData == NULL)
    {
        IPF_PRINT("cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

    pu8IPData1 = (unsigned char*)osl_cachedma_malloc(u32Len);
    if(pu8IPData1 == NULL)
    {
        IPF_PRINT("cacheDmaMalloc :%d\n",__LINE__);
        goto error4;
    }
    pu8IPData2 = (unsigned char*)osl_cachedma_malloc(u32Len);
    if(pu8IPData2 == NULL)
    {
        IPF_PRINT("cacheDmaMalloc :%d\n",__LINE__);
        goto error3;
    }
    pu8IPData3 = (unsigned char*)osl_cachedma_malloc(u32Len);
    if(pu8IPData3 == NULL)
    {
        IPF_PRINT("cacheDmaMalloc :%d\n",__LINE__);
        goto error2;
    }
    pu8IPData4 = (unsigned char*)osl_cachedma_malloc(u32Len);
    if(pu8IPData4 == NULL)
    {
        IPF_PRINT("cacheDmaMalloc :%d\n",__LINE__);
        goto error1;
    }
    stIPHeader.Vers = 4;
    stIPHeader.HeaderLen = 5;
    stIPHeader.TOS = 3;
    stIPHeader.TOL = u32Len;
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

    memset_s(pu8IPData, u32Len, 0x0, u32Len);
    memcpy_s(pu8IPData, sizeof(StreamIPv4Header), &stIPHeader, sizeof(StreamIPv4Header));
    memcpy_s(pu8IPData+sizeof(StreamIPv4Header), sizeof(StreamUDP), &stUDP, sizeof(StreamUDP));

    stSrcTtf[0].usUsed = 200;
    stSrcTtf[0].pData = pu8IPData;
    stSrcTtf[0].pNext = &stSrcTtf[1];

    stSrcTtf[1].usUsed = 200;
    stSrcTtf[1].pData = pu8IPData1;
    stSrcTtf[1].pNext = &stSrcTtf[2];

    stSrcTtf[2].usUsed = 100;
    stSrcTtf[2].pData = pu8IPData2;
    stSrcTtf[2].pNext = &stSrcTtf[3];

    stSrcTtf[3].usUsed = 200;
    stSrcTtf[3].pData = pu8IPData3;
    stSrcTtf[3].pNext = &stSrcTtf[4];

    stSrcTtf[4].usUsed = 200;
    stSrcTtf[4].pData = pu8IPData4;
    stSrcTtf[4].pNext = NULL;
 
    /*while(get_test_switch_stat(IPF_DL))*/
	while(ipf_dl_stress_test_switch)
    {
		u32BDNum = mdrv_ipf_get_dlbd_num(&u32CDNum);
		if(u32BDNum < IPF_DLBD_DESC_SIZE-4)
		{
		    osl_task_delay(dtime);
		    continue;
		} 
		else
		{
			for(i=0;i < u32BDNum - 1;i++)
			{
			    stDlPara[i].u32Data = (unsigned int)stSrcTtf;
			    stDlPara[i].u16UsrField1= 200+i;
			    stDlPara[i].u16Len= 900;
			    /*设中断，仅搬移*/
			    stDlPara[i].u16Attribute= 0x28; 
			}	
			stDlPara[u32BDNum - 2].u16Attribute= 0x29; 

			mdrv_ipf_set_dbuf_para(TTF_OFFSET_OF_T(TTF_MEM_ST, pData),TTF_OFFSET_OF_T(TTF_MEM_ST, usUsed),\
							   TTF_OFFSET_OF_T(TTF_MEM_ST, pNext));
			s32Ret = mdrv_ipf_config_dlbd(u32BDNum - 1, stDlPara);
			if(s32Ret != IPF_SUCCESS)    
			{
				IPF_PRINT("mdrv_ipf_config_dlbd :%d\n",__LINE__);
				g_ipf_busstress_test_fail_cnt++;
				goto error0;
			} 
			g_ipf_busstress_test_ok_cnt++;
		}
    }	
    return OK;
error0:
    osl_cachedma_free(pu8IPData4);
error1:
    osl_cachedma_free(pu8IPData3);
error2:
    osl_cachedma_free(pu8IPData2);
error3:
    osl_cachedma_free(pu8IPData1);
error4:
    osl_cachedma_free(pu8IPData);
    return ERROR;
}

int ipf_dl_stress_test_start(int task_priority,int dtime)
{
	int s32Ret = 0;
	ipf_task_delay_ticks = dtime;

	/*set_test_switch_stat(IPF_DL,TEST_RUN);*/
	ipf_dl_stress_test_switch = 1;
	
	s32Ret = ipf_dl_st_init();
	
	if(s32Ret != OK)
    {
        IPF_PRINT("ipf_dl_st_init :%d\n",__LINE__);
        return ERROR;
    }

	osl_task_init("ipf dl stress task", task_priority, 0x2000, (OSL_TASK_FUNC)ipf_dl_stress_test_routine, (void *)&ipf_task_delay_ticks, &ipf_dl_stress_test_task_id);
	if(ipf_dl_stress_test_task_id == IPF_ERROR)
	{
		IPF_PRINT("taskSpawn ipf dl stress task fail.\n");
		return ERROR;
	}    
    return OK;
}
int ipf_dl_stress_test_stop()
{
	/*set_test_switch_stat(IPF_DL,TEST_STOP);*/
	ipf_dl_stress_test_switch = 0;
	while(BSP_OK == osl_task_check(ipf_dl_stress_test_task_id))
	{
	    osl_task_delay(100);
	}	
	return OK;
}

int ipf_dl_stress_debug(void)
{
	IPF_PRINT("Number of IPF stress test failed:%d\n", g_ipf_busstress_test_fail_cnt);
	IPF_PRINT("Number of IPF stress test succeeded:%d\n", g_ipf_busstress_test_ok_cnt);
	return OK;
}

#ifdef __cplusplus
}
#endif

